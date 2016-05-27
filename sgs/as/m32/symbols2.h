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
 *	static char *ID_symbl2 = "@(#) symbols2.h: 1.3 12/10/83";
*/

/*
 *	NINSTRS	= number of legal assembler instructions (from ops.out)
 *	NHASH	= the size of the hash symbol table
 *	NSYMS	= the number of symbols allowed in a user program
 */

#if	FLOAT
#define	NINSTRS	394
#else
#define	NINSTRS	358
#endif

#if	pdp11
#define NHASH	1693
#else
#define	NHASH	4999
#endif

#define	NSYMS	(NHASH - NINSTRS)
