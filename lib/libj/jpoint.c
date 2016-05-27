/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)jpoint.c	2.5);

#include <dmd.h>
#undef jpoint

void
jpoint(p, f)
#define jpoint Sjpoint
	Point p;
{
	point(&display, p, f);
}
