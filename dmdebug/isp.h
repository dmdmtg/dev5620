/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
HVERSION(isp,@(#)isp.h	2.3);
*/

#define	TRAP_BPT	0x2e	/* breakpoint instruction */

		/* tricky length calculation for BELLMAC */

#define OPRLEN(y)  lentab[((y & 0xf0)>>3) + ((y & 0x0f) == 0x0f) ]

#define CALLLEN(x) 1 +OPRLEN(*(x+1)) + OPRLEN(*(x+1+OPRLEN(*(x+1))))

#define IS_JSR(x) ( (x) == 0x2c )
