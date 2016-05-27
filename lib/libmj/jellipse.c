/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)jellipse.c	2.4);

#include <dmd.h>
extern Point Jtransform();
void
jellipse(p,a,b,f)
	Point p;
	int a, b, f;
{
	ellipse(&display, transform(p),
		muldiv(a, Drect.corner.x-Drect.origin.x, XMAX),
		muldiv(b, Drect.corner.y-Drect.origin.y, YMAX),
		f);
}
