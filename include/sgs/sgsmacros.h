/* */
/*									*/
/*	Copyright (c) 1987,1988,1989,1990,1991,1992   AT&T		*/
/*			All Rights Reserved				*/
/*									*/
/*	  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T.		*/
/*	    The copyright notice above does not evidence any		*/
/*	   actual or intended publication of such source code.		*/
/*									*/
/* */
/*
 * static char ID_mcroh[] = "@(#) sgsmacros.h: 1.2 5/27/83";
 */

#define MAXLDIRS	8
#define COMF77		"(common)"

#define max(a,b)		(a<b ? b: a)
#define min(a,b)		(a>b ? b: a)

#define size(str)		(strlen(str) + 1)

#define equal(a,b,l)		(strncmp(a,b,l) == 0)

#define copy(a,b,l)		strncpy(a,b,l)

