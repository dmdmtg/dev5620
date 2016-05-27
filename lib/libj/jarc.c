/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)jarc.c	2.5);

#include <dmd.h>
void
jarc(p0, p1, p2, f)
	Point p0, p1, p2;
	Code f;
{
	arc(&display, p0, p1, p2, f);
}
