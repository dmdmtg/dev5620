/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)display.c	2.4);

#include <dmd.h>
#undef display
Bitmap display = { 
	(Word *)(0x700000), 			/* bitmap.base */
	25, 					/* width in 32 bit words */
	0, 					/* bitmap.rect.origin.x */
	0, 					/* bitmap.rect.origin.y */
	XMAX, 					/* bitmap.rect.corner.x */
	YMAX 					/* bitmap.rect.corner.y */
};
