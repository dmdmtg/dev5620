/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)stack.c	2.8);
*/

#include "common.h"
#include "frame.h"
#include "user.h"

MLONG	ptregsave;
struct	frame *oldframe = 0;

struct ramnl *findsave( b )
struct ramnl *b;
{
	register struct ramnl *s = b;

	while( !ISFTN( (--s)->n_desc ) ){}
	return s;
}

struct frame *framechain( modes )
{
	register struct	frame 	*p;
	struct	frame	*c;
	struct  ramnl 	*b;
	MLONG	slb;
	struct  ramnl 	*save;
	int		sav0, sav1;
	struct	frame	*user    = 0;
	int		verbose  = modes&VERBOSE_CHAIN;
	int		mpx      = modes&MPX_CHAIN;
	int		full     = modes&FULL_CHAIN;
	int		prntcontext;

	prntcontext = mpx|verbose;

	while( oldframe && oldframe != &sentinel ){
		free( oldframe );
		oldframe = oldframe->caller;
	}
	assert( p = (struct frame *) calloc( 1, sizeof *p ) );
	oldframe = p;

	jerqdo( PEEK_PCBREG );
	p->fp = longfromjerq();
	p->ap = longfromjerq();
	p->pc = longfromjerq();
	slb   = longfromjerq();

	while( p->fp - 36 >= slb ){
		p->fname = p->so = NULL;
		p->sline = NULL;
		p->bfun = b = lookup(USER_MPX, S_BFUN, 0, p->pc );
/* printf("b %d %s pc %d\n", b, b? b->n_name: "", p->pc); */
		if( !b ) break;
		if( !strcmp( b->n_name, "trap" ) ){	/*	for trap */
			ptregsave = p->ap - 12;
			addr_desc( p->fp - 28, PEEK_LONG );	/* fp */
			addr_desc( p->fp - 32, PEEK_LONG );	/* ap */
			addr_desc( p->ap - 20, PEEK_LONG );	/* pc */
			p->fp = longfromjerq();
			p->ap = longfromjerq();
			p->pc = longfromjerq() - 1;
			p->bfun = b = lookup(USER_MPX, S_BFUN, 0, p->pc );
/* printf("b %d %s pc %d\n", b, b? b->n_name: "", p->pc); */
			if( !b ) break;
		}
		p->sline = region(USER, p->pc) ? lookup( USER, S_SLINE, 0, p->pc ) : NULL;
		p->so = sofile( b );
		p->fname = b->n_name;

		save = findsave(b);
		p->function = save->n_value;
		addr_desc( save->n_value, PEEK_SAVE );
		if( (p->regsave = getchar()) == BADTRACE ){
			printf("Bad traceback ");
			return p;
		}
		p->visible = 1;
		if( prntcontext ){
			context( p, REGS_CONTEXT|LINE_CONTEXT );
			putchar( '\n' );
		}
		if( !user && region(USER, p->function) == N_TEXT ){
			user = p;
			if( !full ){
				p->caller = &sentinel;
				return user;
			}
		}
		assert( c = (struct frame *) calloc( 1, sizeof *c ) );

		addr_desc( p->fp - 36, PEEK_PCAPFP );
		c->pc = longfromjerq();
		c->ap = longfromjerq();
		c->fp = longfromjerq();
		p->caller = c;
		c->callee = p;
		p = c;
	}
	return user ? user : p;
}

dumpframe( p )
struct frame *p;
{
	printf( "fp: %ld ap: %ld pc: %ld fname: %s ", p->fp, p->ap, p->pc, p->fname ); 
	printf( "function: %d\n", p->function );
	printf( "regbase: %ld regsave: %d\n", p->fp-24, p->regsave );
	if( p->sline ) ramnldump( p->sline );
	if( p->so ) printf("src file %s\n", p->so);
	if( p->bfun ) ramnldump( p->bfun );
}
