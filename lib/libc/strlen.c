/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)strlen.c	2.3);

/*LINTLIBRARY*/
/*
 * Returns the number of
 * non-NULL bytes in string argument.
 */

int
strlen(s)
register char *s;
{
	register char *s0 = s + 1;

	while (*s++ != '\0')
		;
	return (s - s0);
}
