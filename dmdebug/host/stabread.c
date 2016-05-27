/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)stabread.c	2.11);
*/

#include "common.h"
#include "stab.h"

long	lseek();
extern	long patchaddr;

#define MAXREAD 250

#define MAXSECT	13
short	sects[MAXSECT] = { N_ABS, N_ABS, N_UNDF };

#define OLDTYPE(x) sects[x->n_scnum+2] |\
	(x->n_sclass == C_EXT || x->n_sclass == C_STAT ? N_EXT: 0)


char	s1class[] = {
	0,		/* C_NULL */
	S_LSYM,		/* C_AUTO	automatic variable */
	S_GSYM,		/* C_EXT	external symbol    */
	S_STSYM,	/* C_STAT	static             */
	S_RSYM,		/* C_REG	register variable  */
	-1,		/* C_EXTDEF	external definition*/
	-1,		/* C_LABEL	label              */
	-1,		/* C_ULABEL	undefined label    */
	S_SSYM,		/* C_MOS	member of structure*/
	S_PSYM,		/* C_ARG	function argument  */
	S_BSTR,		/* C_STRTAG	structure tag      */
	S_SSYM,		/* C_MOU	member of union    */
	S_BSTR,		/* C_UNTAG	union tag          */
	-1,		/* C_TPDEF	type definition    */
	S_STSYM,	/* C_USTATIC	undefined static   */
	S_BENUM,	/* C_ENTAG	enumeration tag    */
	S_ENUM,		/* C_MOE	member of enumeration */
	S_RSYM,		/* C_REGPARM	register parameter    */
	-1,		/* C_FIELD	bit field             */
};

char	s2class[] = {
	S_LBRAC,	/* C_BLOCK	.bb .eb code check for RBRAC */
	S_BFUN,		/* C_FCN	.bf .ef code check for EFUN */
	S_ESTR,		/* C_EOS	end of structure */
	S_SO,		/* C_FILE	file name */
	S_SLINE		/* C_LINE	source line */
};


char
oldsclass( c )
char	c;
{
	return( c < C_BLOCK? s1class[c] : s2class[c - C_BLOCK]);
}


stabfree( stab )
register struct stable *stab;
{
	int i;

	if( stab->base ) free( stab->base );
	if( stab->strtab ) free( stab->strtab );
	if( stab->fd ) close( stab->fd );
	stab->base = 0;
	stab->fd = 0;
	stab->size = 0;
	stab->strtab = 0;
	stab->strtaboff = 0;
	stab->strtabsz = 0;
	for( i = 0; i < 0xFF; ++i )
		stab->threader[i] = stab->tmpthread[i] = 0;
	stab->fheader.f_magic = 0;
	stab->fheader.f_nscns = 0;
	stab->fheader.f_timdat = 0;
	stab->fheader.f_symptr = 0;
	stab->fheader.f_nsyms = 0;
	stab->fheader.f_opthdr = 0;
	stab->fheader.f_flags = 0;

	stab->aheader.magic = 0;
	stab->aheader.vstamp = 0;
	stab->aheader.tsize = 0;
	stab->aheader.dsize = 0;
	stab->aheader.bsize = 0;
	stab->aheader.entry = 0;
	stab->aheader.text_start = 0; 
	stab->aheader.data_start = 0;
 
	stab->text = 0;
	stab->data = 0;
	stab->bss = 0;
	stab->mtime = 0;
}

time_t mtime( fd )
{
	struct stat buf;

	fstat( fd, &buf );
	return buf.mtime;
}

off_t f_size( fd )
{
	struct stat buf;

	fstat( fd, &buf );
	return buf.st_size;
}

char *
addname( stab, name)
struct	stable *stab;
char	*name;
{
	char *np;
	np = stab->strtab + stab->strtaboff;
	strcpy( np, name);
	stab->strtaboff += strlen( name ) + 1;
	return( np );
}

char	*
symname( stab, sym)
struct	stable	*stab;
SYMENT *sym;
{
	char	buf[9];

	if( sym->_n._n_n._n_zeroes == 0L )
		return( stab->strtab + sym->_n._n_n._n_offset );
	else {
		strncpy( buf, sym->_n._n_name, 8);
		buf[8] = 0;
		return( addname( stab, buf ) );
	}
}

struct ramnl *
addsym( stab, name, type, other, desc, value)
struct	stable *stab;
char	*name;
char	type;
char	other;
unsigned short desc;
long	value;
{
	register struct ramnl *r;
	int	t;

	r = stab->index;
	r->n_name = name;
	r->n_type = type;
	r->n_other = other;
	r->n_desc = desc;
	r->n_value = value;
	r->n_thread = 0;
	t = other ? other : S_shift(type);
	if( stab->threader[t] ){
		stab->tmpthread[t]->n_thread = r;
		stab->tmpthread[t] = r;
	} else {
		stab->threader[t] = stab->tmpthread[t] = r;
	}
	stab->index++;
	return r;
}


stabread( stab, mode )
struct stable *stab;
{
	struct	filehdr fheader;
	struct	aouthdr aheader;
	struct	scnhdr	sheader;
	LINENO	line;
	char	*funcname, *structname, *name, *typname;
	SYMENT	*asym;
	register	SYMENT	*sym;
	SYMENT	sym1;
	int parmoffset;
	struct	ramnl *s;
#ifdef vax || tahoe || sun || accel || alliant
#else
	SYMENT	symentry;
	AUXENT	auxentry;
#endif
	register	AUXENT	*aux;
	long	isym, lsym, nsyms;
	long	numslines;
	char	sc;			/* storage class */	
	unsigned short	dtype;		/* used for plucking derived types */
	int	btyp;
	int	ai;			/* array dimension index */
	long	strtabsz;
	char	ot;			/* type */
	int		fd, lnfd, stfd;
	long	lnfptr;
	int	psize;
	int		i, h;		/* orig joff var */
	char	     input[128];			/* orig joff var */
	MLONG	     offset;				/* orig joff var */
	char	*cast;

	for( ;; mode |= INTERACT ){
		strcpy( input, stab->path );
		if( (mode&INTERACT) && !oflag ){
			printf("argv[0] = %s\n", stab->path );
			scratch();
			scrapp( "argv[0]", "" );
			scrapp( "keyboard", 0 );
			scrapp( "none", "<none>" );
			printf( "symbol tables?" );
			switch( h = scrhit(0) ){
			case -1:
					strcpy( input, "<none>" );
					break;
			case 0:
				strcpy( input, "\vsymbol table object file? " );
				m_menu( 0, 3 ); 
				readuser( input );
				putchar( '\n' );
				break;
			default:
				strcpy( input, h );
			}
			putchar( '\v' );
		}
		if( !strcmp( input, "<none>" ) ){
			stabfree( stab );
			return;
		}
		if( !strcmp( input, "" ) )
			strcpy( input, stab->path );
		if( (fd = open( input, 0 )) < 0 ){
			printf( "cannot open: %s \n", input );
			continue;
		}
		if( stab->size && !strcmp( input, stab->path ) &&
		    stab->mtime == mtime( fd )){
			close( fd );
			offset = peeklong(peeklong(PROC_INDEX)+DMD_TEXT)-stab->text;
			if( stab->text && offset ){
				for( i = 0; i < stab->size; ++i ){
					switch( stab->base[i].n_type & ~N_EXT ){
					case N_TEXT:
					case N_BSS:
					case N_DATA:
						stab->base[i].n_value += offset;
					}
				}
				getprocinfo( stab );
			}
			return;
		}
		lseek( fd, 0L, 0 );
		read( fd, (char *) &fheader, sizeof(struct	filehdr) );
		read( fd, (char *) &aheader, sizeof(struct aouthdr) );
		if( fheader.f_magic != FBOMAGIC ){
			printf( "not compiled for DMD: %s\n", input );
			close( fd );
			continue;
		}
		if( !fheader.f_nsyms ){
			printf( "no symbols: %s\n", input );
			close( fd );
			continue;
		}
		break;
	}

	stfd = open( input, 0);
	lnfd = open( input, 0);

/*	Get sections - text, data, bss */

	numslines = 0;
	for( i = 0; i < fheader.f_nscns; i++){
		read( fd, (char *)&sheader, sizeof(struct scnhdr) );
		if( !strncmp( sheader.s_name, ".text", 5) )
			patchaddr = sheader.s_paddr;
		numslines += sheader.s_nlnno;
		if( i == 0 )
			lnfptr = sheader.s_lnnoptr;
		sheader.s_flags &= (STYP_TEXT|STYP_DATA|STYP_BSS);
		sects[i+3] = sheader.s_flags==STYP_TEXT ? N_TEXT :
					( sheader.s_flags==STYP_DATA ? N_DATA : N_BSS );
	}

	stabfree( stab );
	stab->fheader = fheader;
	stab->aheader = aheader;
	if( oflag )
		stab->fd = fd;
	strcpy( stab->path, input );
	stab->mtime = mtime( fd );
	getprocinfo( stab );

	/*	Allocate storage and read in string table	*/

	i = fheader.f_symptr + (fheader.f_nsyms*SYMESZ);
	strtabsz = 0;
	if( f_size(fd) - i > 0 ){
		lseek( fd, i, 0);
		read( fd, &strtabsz, 4 );
	}
	stab->strtabsz = strtabsz + ((fheader.f_nsyms/2)*8);
	if( (stab->strtab = calloc( stab->strtabsz, 1)) == NULL ){
		printf("Unable to allocate string table storage\n");
		wrap( -1 );
	}
	if( strtabsz ){
		lseek( fd, -4, 1);
		read( fd, stab->strtab, strtabsz);
	}
	stab->strtaboff = strtabsz;

	/*	Allocate storage for ramnl entries		*/

	stab->size = fheader.f_nsyms;
	if( stab != stabtab[MPX] )
		stab->size += numslines;
	stab->base = stab->index = (struct ramnl *) calloc( stab->size, sizeof(struct ramnl) );
	if( !stab->base ){
		printf( "Unable to allocate symbol table storage\n" );
		wrap( -1 );
	}

	/* Allocate storage for a block of symbol entries */

#ifdef vax
	sym = asym = (SYMENT *)calloc( MAXREAD+1, SYMESZ);
	if( !asym ){
		printf( "Unable to allocate symbol table buffer\n");
		wrap( -1 );
	}
#else
	sym = &symentry;
#endif
	/* Position file at start of symbol table */

	lseek( fd, fheader.f_symptr, 0);
	lnfptr = 0;

	/*	Process symbol table entries			*/

	aux = NULL;
	for( isym=lsym= 0; isym < fheader.f_nsyms; isym++){
#ifdef vax
		if( isym == 0 || isym > lsym ){
			if( fheader.f_nsyms - isym < MAXREAD ){
				nsyms = fheader.f_nsyms - isym;
				lsym = fheader.f_nsyms - 1;
			} else {
				nsyms = MAXREAD;
				lsym = isym + MAXREAD - 1;
			}
			read( fd, asym, nsyms*SYMESZ);
			sym = asym;
		} else {
			cast = (char *)sym;
			cast += 18;
			if( aux!=NULL )
				cast += 18;
			sym = (SYMENT *)cast;
		}
		if( sym->n_numaux ){
			cast = (char *)sym;
			cast += 18;
			aux = (AUXENT *)cast;
			if( isym == lsym ){
				read( fd, (AUXENT *)aux, AUXESZ);
				lsym++;
			}
			isym++;
		} else aux = NULL;
#else
		aux = NULL;
		read( fd, (SYMENT *)sym, SYMESZ);
		if( sym->n_numaux ){
			aux = &auxentry;
			read( fd, (AUXENT *)aux, AUXESZ);
			isym++;
		}
#endif

REGPARM_ARG:
		ot = OLDTYPE(sym);
		btyp = BTYPE( sym->n_type );
		if( btyp == T_NULL ){
			switch( sym->n_sclass ){
			case C_FILE:		/* .file */
				addsym( stab, addname(stab,aux->x_file.x_fname),
						(char)N_TEXT, (char)S_SO,(ushort)T_NULL, sym->n_value);
				continue;

			case C_FCN:		/* .bf or .ef */
				sc = sym->_n._n_name[1] == 'b' ? S_BFUN: S_EFUN;
				addsym( stab, funcname, (char)N_TEXT, sc,
					(ushort)T_NULL, sym->n_value + stab->text );

				if( sc == S_BFUN && stab != stabtab[MPX] && lnfptr ){
					lseek( lnfd, lnfptr+LINESZ, 0);
					read( lnfd, &line, LINESZ);
					while( line.l_lnno ){
						addsym( stab, "", (char)N_TEXT, (char)S_SLINE,
							(ushort)line.l_lnno + aux->x_sym.x_misc.x_lnsz.x_lnno - 1,
							(long)line.l_addr.l_paddr + stab->text );
						read( lnfd, &line, LINESZ);
					}
					lnfptr = 0;
				}
				parmoffset = 0;
				continue;

			case C_BLOCK:		/* .bb or .eb */
				continue;
			case C_EOS:		/* .eos */
				addsym( stab, structname, (char)N_ABS, (char)S_ESTR,
					(ushort)STRTY, (long)aux->x_sym.x_misc.x_lnsz.x_size);
				continue;
			case C_STAT:
			case C_EXT:
				if( !(sym->n_type&C_TMASK) )
					continue;
			}
		}
		switch( sym->n_sclass ){
		case C_NULL:
		case C_EXTDEF:
		case C_LABEL:
		case C_ULABEL:
		case C_TPDEF:
		case C_FIELD:
		case C_ALIAS:
			continue;	/* not used */

		case C_STAT:
		case C_EXT:
			sym->n_value += stab->text;
			break;
		}
		name = symname( stab, sym);
		if( !strcmp( name, _TARGET ) )
			continue;
		if( sccsflg==0 && sym->n_sclass==C_STAT &&
			btyp == T_CHAR && T_ISARY(sym->n_type) &&
		    name[0]=='_' && name[1]=='2' && name[2]=='V') continue;
		if( T_ISTAG( sym->n_sclass ) )
			structname = name;
		s = addsym( stab, name, ot, oldsclass( sym->n_sclass),
			sym->n_type, sym->n_value);
		if( !T_ISTAG(sym->n_sclass) && T_ISSUE(btyp) ){
			if( aux ){
				lseek( stfd, fheader.f_symptr+aux->x_sym.x_tagndx*SYMESZ, 0);
				read( stfd, &sym1, SYMESZ );
				typname = symname( stab, &sym1);
			} else
				typname = "";
			addsym( stab, typname, (char)N_ABS,(char)S_TYID, 0, 0);
		}
		dtype = sym->n_type;
		if( T_ISFCN( dtype ) ){
			funcname = name;
			if( stab != stabtab[MPX] )
				lnfptr = aux->x_sym.x_fcnary.x_fcn.x_lnnoptr;
		}
		ai = 0;
		while( dtype&N_TMASK ){
			if( T_ISARY( dtype ) )
				addsym( stab, "", ot, (char)S_DIM,
				 (ushort)aux->x_sym.x_fcnary.x_ary.x_dimen[ai++], 0);
			dtype = DT_DECREF( dtype );
		}
		if( sym->n_sclass == C_ARG || sym->n_sclass == C_REGPARM ){
			psize = mccsize(s->n_desc,s+1,0);
			if( sym->n_sclass == C_REGPARM ){
				sym->n_sclass = C_ARG;
				sym->n_value = psize < 4 ? parmoffset + (4 - psize):
						parmoffset;
				goto REGPARM_ARG;
			} else {
				parmoffset += psize;
				parmoffset = parmoffset&3 ? (parmoffset|3)+1 : parmoffset;
			}
		}
	}

	stab->size = stab->index - stab->base;
	if( (char *)stab->base != realloc( stab->base, stab->size*sizeof( struct ramnl ) ) ){
		printf("Deallocation of symbol table storage failed\n");
		wrap( -1 );
	}

	stab->strtabsz = stab->strtaboff;
	if( stab->strtab != realloc( stab->strtab, stab->strtabsz ) ){
		printf("Deallocation of string table storage failed\n");
		wrap( -1 );
	}
#ifdef vax
	free( asym );
#endif
	if( !oflag ){
		close( fd );
		close( stfd );
		close( lnfd );
	}

	verify( stab, S_BSTR );
	verify( stab, S_BENUM );
}

threadP( stab )
struct stable *stab;
{
	static struct ramnl P[3];
	static char	names[3][8];
	int	i;

	if( !P[0].n_name )
		for( i=0; i<3; i++)
			P[i].n_name = names[i];
	if( stab->threader[S_GSYM] == &P[0] ) return;
	P[0].n_other = S_GSYM;
	strcpy( P[0].n_name, "P" );
	P[0].n_value = PROC_INDEX;
	P[0].n_desc = PTR+STRTY;
	P[1].n_other = S_TYID;
	strcpy( P[1].n_name, "Proc" );
	P[0].n_thread = stab->threader[S_GSYM];
	stab->threader[S_GSYM] = &P[0];
}


getprocinfo( stab )
struct stable *stab;
{
	register long	paddr;

	stab->proc = paddr = peeklong( PROC_INDEX );
	if( stab == stabtab[MPX] )
		stab->text = LO_ROM;
	else
		stab->text = peeklong( paddr+DMD_TEXT );
	stab->data = stab->text + stab->aheader.tsize;
	stab->bss  = stab->data + stab->aheader.dsize;
}

