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
 * static char ID_ftlc[] = "@(#) fatal.c: 1.1 1/7/82";
 */

fatal(msg)
char *msg;
{

	lderror(2, 0, NULL, msg);

	return( -1 );
}
