/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)context.c	2.10);
*/

#include "common.h"
#include "frame.h"
#include "user.h"
#include "../traps.h"

char *mcctype( s )
struct ramnl *s;
{
	char *buffer = talloc(32);
	int t = s->n_desc;

	for( t >>= BTSHIFT; t; t >>= TSHIFT )
		strcat( buffer,  &("*\0\0()\0[]\0"[(t&3)*3-3]) );
	strcat( buffer, basetypenames[s->n_desc&BTMASK] );
	if( (++s)->n_other == S_TYID )
		sprintf( &buffer[strlen(buffer)], " %s", s->n_name );
	return buffer;
}

char *display( s, f )
struct ramnl *s;
struct frame *f;
{
	char   *d = talloc(32);
	MLONG  p = locate( s, f );
	MSHORT  e;
	int		r = (s->n_other == S_RSYM);

	if( !p ) return "<location error>";
	switch( s->n_other ){
		case S_BFUN:
			snarfdot = s->n_value;
			snarfdotty = 0;
			return fmt( "%s()", doh(s->n_value) );
		case S_GSYM:
		case S_STSYM:
		case S_RSYM:
		case S_PSYM:
		case S_LSYM:
		case S_SSYM:
			break;
		case 0:
			return ntypenames[ s->n_type>>1 ];
		default:
			return "<storage class error>";
	}
	switch( s->n_desc & C_TMASK ){
	case PTR:
		if( s->n_desc != PTR+CHAR )
			return doh(peeklong(p));
		else
			return fmtstring( peeklong( p ) );
	case FTN:
			return "<function>";
	case ARY:
		snarfdot = p;
		switch( DECREF(s->n_desc) ){
		default:
			snarfdotty = 0;			break;
		case CHAR:
		case UCHAR:
			snarfdotty = BYTEDOT;	break;
		case SHORT:
		case USHORT:
			snarfdotty = SHORTDOT;	break;
		case ENUMTY:
		case INT:
		case UNSIGNED:
		case LONG:
		case ULONG:
			snarfdotty = LONGDOT;	break;
		}
		return DECREF(s->n_desc)==CHAR ? fmtstring(p) : doh(p);
	case 0:
		switch( s->n_desc & BTMASK ){
		default:
			return "<unimplemented>";
		case UCHAR:
			return fmt( "%u", peekbyte( r ? p+3 : p ) );
		case CHAR:
			return fmtchar( (char) peekbyte( r ? p+3 : p ) );
		case SHORT:
			return fmt( "%d", (MSHORT) peekshort( r ? p+2 : p ) );
		case USHORT:
			return fmt( "%u", (MSHORT) peekshort( r ? p+2 : p ) );
		case INT:
		case LONG:
			return fmt( "%ld", peeklong(p) );
		case UNSIGNED:
		case ULONG:
			return fmt( "%lu", peeklong(p) );
		case ENUMTY:
			if( (++s)->n_other != S_TYID ) return missing;
			if( s->n_name[0] == '\0' ) return "<anonymous enum>";
			s = lookup( table(s), S_BENUM, s->n_name, 0 );
			if( !s ) return "<enum error>";
			e = peeklong(p);
			for( ++s; s->n_other != S_EENUM; ++s )
			    if( s->n_other == S_ENUM && s->n_value == e )
					return strcpy( d, s->n_name);
			sprintf( d, "<enum %d>", e );
			return d;
		case UNIONTY:
		case STRTY:
#define	WIDTH 1024
			(d = talloc(WIDTH))[0] = '{';
			if( (++s)->n_other != S_TYID )	return missing;
			if( s->n_name[0] == '\0' )	return "<anonymous struct>";
			s = lookup( table(s), S_BSTR, s->n_name, 0 );
			if( !s ) return "<struct error>";
			for( ++s; s->n_other != S_ESTR && strlen(d) < WIDTH-12; ){
				sprintf( &d[strlen(d)], "%0.*s=", FLEX_SZ, s->n_name );
				s->n_value += p;
				strncat( d, display(s, 0), WIDTH - strlen(d) - 12 );
				s->n_value -= p;
				for( ++s; s->n_other == S_TYID
						|| s->n_other == S_DIM; ++s ){}
				if( s->n_other == S_SSYM ) strcat( d, "," );
			}
		 	return strcat( d, "}" );
		}
	}
	ramnldump( s );
	return "<internal error in display()>";
}

localsc()
{
	long	rslp = IV(S_RSYM, S_STSYM, S_LSYM, S_PSYM);
	long h = 1000;
	struct frame *f = train;
	struct ramnl	*s;

	assert( hatebs != ACTIVE );
	if( !visible( f->sline, rslp, "*", 0 ) ){
		printf( "no locals in %s()\n", f->fname );
		return;
	}
	for( ;; ){
		scratch();
		for( s = f->sline; s = visible( s, rslp, "*", 0 ); ){
		scrins(
			fmt( "%0.*s\240%s", FLEX_SZ, s->n_name, storagenames[s->n_other]), s );
		}
		if( (h = scrhit(h)) == -1 ) return;
		chasesym( (struct ramnl *)h );
	}
}


globalsc()
{
	long	h = 0;
	struct  ramnl *s;

	for( ;; ){
		scratch();
		for( s = lookup( USER, S_GSYM, "*", 0 ); s; s = s->n_thread ){
			if( !lookup( USER, S_BFUN, s->n_name, 0 ) ){
				scrsort( fmt( "%0.*s\240%s", FLEX_SZ,
					s->n_name, storagenames[s->n_other]), s );
			}
		}
		if( (h = scrhit(h)) == -1 ) return;
		chasesym( (struct ramnl *)h );
	}
}


stkframec()
{
	struct frame *f;
	long i, ct = 0;

	if( train == 0 ){
		jerqmenu( M_PENDULUM, 1 );
		train = framechain(FULL_CHAIN);
		jerqmenu( M_PENDULUM, 0 );
		if( !train ) return;
	}
	for( f = train; f; f = f->caller ){
		if( f == &sentinel ){
			jerqmenu( M_PENDULUM, 1 );
			train = framechain(FULL_CHAIN);
			jerqmenu( M_PENDULUM, 0 );
			if( !train ) return;
			break;
		}
	}
	for( f = train; f->callee; f = f->callee ) {}
	scratch();
	for( ; f; f = f->caller ){
		if( f->visible ){
			scrapp( fmt( "%s()", f->fname ), f );
			++ct;
		}
	}
	if( ct == 0 ){
		printf( "empty traceback.\n" );
		return;
	}
	switch(i = scrhit(0) ){
		case -1: return;
		default: context( train = (struct frame *) i,
						REGS_CONTEXT|LINE_CONTEXT );
			 putchar( '\n' );
	}
}
	
context( f, mode )
struct frame *f;
{
	long	sl = IV(S_RSYM, S_STSYM, S_LSYM, S_PSYM);
	struct ramnl	*s, *psym, *rsym;
	int		psymct = 0;

	if( !f ){
		printf( "<context not determined>" );
		return;
	}
	if( !f->bfun ){
		printf( "pc=%s", doh(f->pc) );
		return;
	}
	if( mode&LINE_CONTEXT && ( f->sline || f->so ) )
		printf( "%s in ", fsoline( f ) );
	printf( "%s(", f->fname);
	for( psym = f->bfun; psym->n_other != S_EFUN; ++psym ){
		if( psym->n_other == S_PSYM ){
			rsym = 0;
			if( (psym-1)->n_other == S_RSYM ) rsym = psym-1;
			if( (psym-1)->n_other == S_TYID &&
			    (psym-2)->n_other == S_RSYM ) rsym = psym-2;
			if( psymct++ > 0 ) putchar( ',' );
			printf( "%s=%s", psym->n_name, display( psym, f ) );
			if( rsym && (mode&REGS_CONTEXT) )
				printf( "/reg %s=%s", rsym->n_name, display( rsym, f));
		}
	}
	printf( ")" );
	if( !(mode&AUTO_CONTEXT) ) return;
	putchar( '\n' );
	if( f->sline )
		for( s = f->sline; s = visible( s, sl, "*", 0 ); )
			printf( "%s=%s\n", s->n_name, display( s, f ) );
}

MLONG locate( s, f )
struct ramnl *s;
struct frame *f;
{
	long	r, nr, pcbaddr;
	struct ramnl *g;
	
	switch( s->n_other ){
	case S_BFUN: return s->n_value;
	case S_SSYM: assert( !f ); return s->n_value;
	case S_GSYM:
		if( s->n_value ) return s->n_value;
		if(g = lookup( USER_MPX, S_EBSS, s->n_name, 0 )) return g->n_value;
		return 0;
	case S_STSYM: return( s->n_value );
	case S_PSYM: assert( f ); return( f->ap + s->n_value );
	case S_LSYM: assert( f ); return( f->fp + s->n_value );
	case S_RSYM:
		r = s->n_value;
		if( r > 15 )  return r;
		pcbaddr = peeklong( PROC_INDEX );
		if( r > 8 ){
			if( r == 11 ) return pcbaddr+DMD_SPU;
			if( r == 12 ) return pcbaddr+DMD_SPL;
			if( r == 13 ) return pcbaddr+DMD_SP;
			if( r == 15 ) return pcbaddr;		/* psw */
			if( f && f->callee ){
				if( r == 9 )  return f->callee->fp - 28;
				if( r == 10 ) return f->callee->ap - 32;
				if( r == 14 ) return f->callee->pc - 36;
			} else {
				if( r == 9  ) return pcbaddr+DMD_FP;
				if( r == 10 ) return pcbaddr+DMD_AP;
				if( r == 14 ) return pcbaddr+DMD_PC;
			}
		}
		nr = 9 - r;
		if( f ){
		  while( f = f->callee ){
			if( nr <= f->regsave )
				return ( f->fp-24 + ( (r + f->regsave - 9)*4 ) );
			} /* regbase is always      fp-24 */
		}
		return( pcbaddr + DMD_REG + r*4 );
	case 0: return s->n_value;
	}
	return 0;
} 

