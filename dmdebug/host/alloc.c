/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)alloc.c	2.2);
*/

#include "common.h"
#include <varargs.h>

static struct list {
	char        *user;
	struct list *link;
};

static struct list *track = 0;

tfree()
{
	while( track ){
		free( track->user );
		free( track );
		track = track->link;
	}
}

char *talloc( n )
{
	struct list *p = (struct list *) calloc( 1, sizeof *p );

	assert( p && ( p->user = (char *) calloc( 1, n ) ) );
	p->link = track;
	track = p;
	return p->user;
}

char *fmt( f, va_alist)
char *f;
va_dcl
{
	va_list args;
	char s[1024];
	int	len;

	va_start(args);
	vsprintf( s, f, args);
	va_end(args);
	len = strlen(s);
	assert( len < 1024 );
	return strcpy( talloc( len+1 ), s );
}
