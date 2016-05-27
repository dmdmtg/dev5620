/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
HVERSION(dmdoffsets,@(#)dmdoffsets.h	2.3);
*/

/*	This file will contain constants used to determine the
	addresses of certain fields in the Proc structure
*/

#define DMD_PC		4		/* pc offset */
#define	DMD_SP		8		/* sp offset */
#define DMD_SPL		12		/* sp lower limit */
#define DMD_SPU		16		/* sp upper limit */
#define DMD_AP		20		/* argument pointer */
#define DMD_FP		24		/* frame pointer */
#define DMD_REG		28		/* base of registers */
#define DMD_TEXT	68		/* base of text */
#define DMD_DATA	72		/* base of data */
#define DMD_BSS		76		/* base of bss */

