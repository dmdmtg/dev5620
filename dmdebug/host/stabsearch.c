/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)stabsearch.c	2.5);
*/

#include "common.h"
#include "stab.h"
#include "frame.h"

char	*srcnfnd = "<src not found>";
char	*missing = "<missing tables>";

region( tab, a )
MLONG a;
{
	struct stable *stab = stabtab[tab];
/* printf("enter region with %d\n", a); */
	if( (tab == MPX) && a >= LO_ROM && a <= HI_ROM ) return N_ABS;
	if( !stab || !stab->base || a < stab->text) return 0;
	if( a >= stab->text && a < stab->text+stab->aheader.tsize )
		return N_TEXT;
	if( a >= stab->data && a < stab->data+stab->aheader.dsize )
		return N_DATA;
	if( a >= stab->bss  && a < stab->bss +stab->aheader.bsize )
		return N_BSS;
/* printf("exit of region\n"); */
	return 0;
}

idmatch( a, b )
char *a, *b;
{
	return *a=='*' || ((*a==*b) && !strcmp(a, b));
}

nfidmatch( a, b )
char *a, *b;
{
	return *a=='*' || ((*a==*b) && !strncmp(a, b, 8));
}

#define IDMATCH(a,b) ( *(a)=='*' || ((*(a)==*(b)) && !strcmp((a), (b))) )

struct ramnl *lookup( tables, class, id, addr )
long tables, class;
char *id;
MLONG addr;
{
	struct ramnl *b = 0, *s;
	struct stable *t;
	long h, tab;

	for( ; t = stabtab[tab = tables & 0xFF]; tables >>= 8 ){
	    if( t->base && ( !addr || region( tab, addr ) ) ){
		for( h = class; h; h >>= 8 ){
		    for( s = t->threader[h&0xFF]; s; s = s->n_thread ){
			if( !id && s->n_value <= addr
				&& ( !b || s->n_value > b->n_value ) ) b = s;
			else if( id && IDMATCH( id, s->n_name ) ) return s;
		    }
		}
	    }
	}
	return b;
}


char *basename( path )
char *path;
{
	char *strrchr(), *lsi = strrchr( path, '/' );
	return lsi ? lsi+1 : path; 
}

char *sofile( s )
struct ramnl *s;
{
	struct ramnl *base = stabtab[table(s)]->base;

	if( base == NULL ) return missing;
	while( s > base && s->n_other != S_SO ) --s;
	return s->n_other != S_SO ? srcnfnd : s->n_name;
}

struct ramnl *
sline1( b )
struct ramnl *b;
{
	for( b++; b->n_other != S_EFUN; b++)
		if( b->n_other == S_SLINE)
			return b;
	return NULL;
}

char *fsoline( f )
struct	frame *f;
{
	register struct ramnl *p, *s;
	int index = 1;
	long	offset;
	char	*coffset;

	s = f->sline;
	if( s ){
		offset = f->pc - s->n_value;
		for( p = s-1; p->n_other != S_SO; --p ) if( p->n_other == S_SLINE ){
			if( p->n_desc == s->n_desc ) ++index; 
			if( p->n_desc < s->n_desc ) break;
		}
		coffset = offset == 0 ? "" : ( offset > 0 ? fmt("+%s", doh(offset)) : fmt("-%s", doh(-1*offset)) );
		return fmt( "%s:%d%s%s", f->so, s->n_desc,
				index>1 ? fmt( ".%d", index ) : "", coffset);
	}
	if( f->so )
		return f->so;
	else
		return missing;
}

char *soline( l )
MLONG l;
{
	struct ramnl *p, *s = lookup( USER_MPX, S_SLINE, 0, l );
	MLONG offset = s ? l - s->n_value : 0;
	int index = 1;
	char	*coffset;

	if( !s ){
	    if( s = lookup( USER_MPX, S_GSYM, 0, l ) ) /* BFUN -> GSYM */
			return fmt( "%s:<pc=%s>", basename(sofile(s)), doh(l) );
	    return missing;
	}
	for( p = s-1; p->n_other != S_SO; --p ) if( p->n_other == S_SLINE ){
		if( p->n_desc == s->n_desc ) ++index; 
		if( p->n_desc < s->n_desc ) break;
	}
	coffset = offset == 0 ? "" : ( offset > 0 ? fmt("+%s", doh(offset)) : fmt("-%s", doh(-1*offset)) );
	return fmt( "%s:%d%s%s", basename(sofile(s)), s->n_desc,
			index>1 ? fmt( ".%d", index ) : "", coffset);
}

struct ramnl *visible( s, class, id, addr )	/* now also gives file statics */
struct ramnl *s;
long class;
char *id;
MLONG addr;
{
	int nest = 0;
	long h;

	if( !s ) return 0;
	for( ++s; s->n_other != S_SO; ){
	    switch( s->n_other ){
	    case S_BFUN:  nest = 1000000; break;		/* infinity */
	    case S_EFUN:  nest = 0; break;
	    case S_LBRAC: ++nest; break;
	    case S_RBRAC: if( nest ) --nest; break;
	    default:
	        if(!nest) for( h = class; h; h >>= 8 ) if(s->n_other == (h&0xFF))
			if( !id && s->n_value == addr ) return s;
			else if( id && IDMATCH( id, s->n_name ) ) return s;
	    }
	    if( table(++s) == USER_MPX ) break;		/* off end - not found */
	}
	return 0;
}

long
table( s )
struct ramnl *s;
{
	int i;

	if( !s ) return 0;
	for( i = 1; stabtab[i]; ++i )
		if( s >= stabtab[i]->base && s < stabtab[i]->base+stabtab[i]->size )
			return i;
	return USER_MPX;
}

unsigned char ofetch( a )
MLONG a;
{	
	static thetable;
	int t;
	unsigned char b;
	struct	stable *stab;

	if( a >= INDEX_BASE && a <= LAST_INDEX ) return 0;
	for( t = 1; stabtab[t]; ++t ) if( region( t, a ) ){
		stab = stabtab[t];
		if( t != thetable )
			printf( "fetching from %s\n", stab->path );
		thetable = t;
		lseek( stab->fd, a - stab->text + stab->aheader.text_start, 0);
		read( stab->fd, &b, 1 );
		return b;
	}
	printf( "invalid address: %s\n", doh(a) );
	return 0;
}
	    
