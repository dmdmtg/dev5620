/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
HVERSION(sgs, @(#)sgs.h	2.3);

/*
 * static char *ID_sgsh = "@(#) sgs.h: 1.5 6/29/82 (modified for DMD 7/25/83)"
 *  This is a whittled down copy of sgs.h from the SGS.  It has been modified
 *  to allow our object delivery and use of the DMDSGS variable
 */

#define	SGS	"m32"

/*	The symbol FBOMAGIC is defined in filehdr.h	*/

#define MAGIC	FBOMAGIC
#define TVMAGIC (MAGIC+1)

#define ISMAGIC(x)	(( x) ==  MAGIC)


#ifdef ARTYPE
#define	ISARCHIVE(x)	(( x) ==  ARTYPE)
#define BADMAGIC(x)	((((x) >> 8) < 7) && !ISMAGIC(x) && !ISARCHIVE(x))
#endif


/*
 *	When a UNIX aout header is to be built in the optional header,
 *	the following magic numbers can appear in that header:
 *
 *		AOUT1MAGIC : default
 */

#define AOUT1MAGIC 0407
#define AOUT2MAGIC 0410



/*
 * MAXINT defines the maximum integer for printf.c
 */

#define MAXINT	2147483647

#define	SGSNAME	"dmd"
#define	RELEASE	"Release 2.3 11/1/84 for (DMD)"
