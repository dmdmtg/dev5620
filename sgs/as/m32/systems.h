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
 *	static char ID[] = "@(#) systems.h: 1.6 5/4/84";
 */

/*
 *	SYSTEMS.H FOR M32
 */

#define DEBUG	0
#define TRANVEC 0
#define DCODGEN 0
#define M4ON	1
#define FLOAT	1
#define MACRO	0

#if ABWRMAC
#define ER21FIX 1
#define ER16FIX 1
#define EXPFIX 1
#define MLDVFIX 1
#define M32RSTFIX 1
#define CHIPFIX 1
#endif

#if ABWORMAC

#define ER21FIX 1
#define ER16FIX 1
#define EXPFIX 1
#define MLDVFIX 1
#define CHIPFIX 1
#endif

#if BMAC
#define EXPFIX 1
#define MLDVFIX 1
#endif
