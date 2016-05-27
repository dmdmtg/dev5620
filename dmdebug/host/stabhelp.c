/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)stabhelp.c	2.4);
*/

#include "common.h"
#include "stab.h"

int helpmode;

ramnldump( p )
struct ramnl *p;
{
	if( !p ) return;
	if( table(p) && table(p) < 0xFF ) printf("%s ", stabtab[table(p)]->name);
	printf( "%s %*.*s %5s %5s %7d %o=%d %s\n", sofile(p),
		FLEX_SZ+6, FLEX_SZ+6, p->n_name,
		ntypenames[p->n_type], sdbnames[p->n_other], p->n_value,
		p->n_desc, p->n_desc, 
		p->n_other ? mcctype(p) : "" );
}

stabdump( stab )
struct stable *stab;
{
	int i, n, ct;
	struct filehdr *fh = &stab->fheader;
	struct aouthdr *ah = &stab->aheader;
	struct ramnl *s;

	if( !stab ) return;
	printf( "%s from %s\n", stab->name, stab->path );
	if( stab->rom ) printf( "rom %d\n", stab->rom );
	printf( "magic 0%o text %d data %d bss %d textorg %d start %d\n",
	    fh->f_magic, ah->tsize, ah->dsize, ah->bsize, ah->entry, stab->text );
	printf( "syms %d => %d\n", fh->f_nsyms, stab->size );
	for( i = 1, n = 0; sdbnames[i]; ++i ){
	    for( ct = 0, s = stab->threader[i]; s; s = s->n_thread ) ++ct;
	    if( ct ) printf( "%c%5s:%4d", (n++)%6 ? ' ' : '\n', sdbnames[i], ct );
	}
	for( i = 1; ntypenames[i]; ++i ){
	    for( ct = 0, s = stab->threader[S_shift(i)]; s; s = s->n_thread ) ++ct;
	    if( ct ) printf( "%c%5s:%4d", (n++)%6 ? ' ' : '\n', ntypenames[i], ct );
	}
	putchar( '\n' );
}

stabstats(){
	int i;

	for( i = 1; stabtab[i]; ++i ) stabdump( stabtab[i] );
}

#define IS_DIM(s) (s->n_other == S_DIM )

#define eqnl( a, b )\
    (!strcmp(a->n_name, b->n_name)\
	&& a->n_desc==b->n_desc\
	    && (IS_DIM(a)&&IS_DIM(b) ? 1 : a->n_value==b->n_value) )

eqdef( a, b )
struct ramnl *a, *b;
{
	for( ; a->n_other != S_ESTR && a->n_other != S_EENUM; ++a, ++b ){
		if( IS_DIM(a) && !IS_DIM(b) ){ --b; continue; }
		if( IS_DIM(b) && !IS_DIM(a) ){ --a; continue; }
		if( !eqnl( a, b ) ){
			if( helpmode ){	
				ramnldump(a);
				ramnldump(b);
			}
			return 0;
		}
	}
	return eqnl( a, b );
}

verify( stab, begin )
struct stable *stab;
{
	struct ramnl *l, *s;
	int limit = 10, t;

	for( s = stab->threader[begin]; s; s = s->n_thread )
		for( t = 1; stabtab[t]; ++t ){
			l = lookup( t, begin, s->n_name, 0 );
			if( l && !eqdef( l, s ) ){
				if( limit-- == 0 ){
					printf( "further inconsistencies.\n" );
					return;
				}
				printf( "inconsistent: %s from ", s->n_name );
				printf( "%s (%s) and ", sofile(s), stab->name );
				printf( "%s (%s)\n", sofile(l), stabtab[table(l)]->name );
			}
		}
}

stabhelp(id, class )
char *id, *class;
{
	struct ramnl *s = 0;
	long c;
	char comm[128];
	
	if( c = nameindex( sdbnames, class ) )
		s = lookup( USER_MPX, c, id, 0 );
	if( c = nameindex( ntypenames, class ) )
		s = lookup( USER_MPX, S_shift(c), id, 0 );
	if( !s ){
		printf( "not found: %s %s\n", id, class );
		return;
	}
	if( !oflag ){
		m_menu( 0, 2 ); 
		m_menu( 0, 3 );
	}
	for( ;; ){
		ramnldump( s );
		strcpy( comm, "+|-|*|/|q ? " );
		readuser( comm ); 
		printf( "\r+|-|*|/|q ? %s\r", comm );
		switch( comm[0] ){
		case '\0': 
		case '+' : if( s ) ++s; break;
		case '-' : if( s ) --s; break;
		case '*' : if( s ) s = s->n_thread; break;
		case '/' : for( s = s->n_thread;
					s && !idmatch( id, s->n_name );
						s = s->n_thread ){}
			break;
		default: return;
		}
	}
}
	
zvc(){
	helpmode = !helpmode;
}
