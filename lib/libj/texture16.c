/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)texture16.c	2.5);

#include <dmd.h>

void
texture16(b,r,t,c)
Bitmap *b;
Rectangle r;
Texture16 * t;
int c;
{
	Texture local;
	register short *dest = (short *)&local;
	register short *ssrc  = (short *)t;
	register int    i;

	i = 16;
	do {
		*dest = *ssrc;
		*(dest + 1) = *ssrc;
		*((int *)(dest +32)) = *((int *)dest);
		ssrc++;
		dest += 2;
	} while ( --i > 0 );
	texture(b,r,&local,c);
}
