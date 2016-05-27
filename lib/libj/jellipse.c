/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)jellipse.c	2.5);

#include <dmd.h>

void
jellipse(p,a,b,f)
	Point p;
	int a, b, f;
{
	ellipse(&display, p, a, b, f);
}
