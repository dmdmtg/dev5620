/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)jcircle.c	2.4);

#include <dmd.h>
extern Point Jtransform();
void
jcircle(p,r,f)
	Point p;
{
	circle(&display,transform(p),
		muldiv(r, Drect.corner.x-Drect.origin.x, XMAX),f);
}

