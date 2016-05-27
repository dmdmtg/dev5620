/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)circle.c	2.4);

#include <dmd.h>
#define lpoint
#include <pandora.h>

/*	Form a circle of radius r centered at x1,y1
 *	The boundary is a sequence of vertically, horizontally,
 *	or diagonally adjacent points that minimize 
 *	abs(x^2+y^2-r^2).
 *
 *	The circle is guaranteed to be symmetric about
 *	the horizontal, vertical, and diagonal axes
 */
void
circle(b,p,r,f)
	Bitmap *b;
	Point p;
{
	int x1=p.x;
	register y1=p.y;
	register eps = 0;	/* x^2 + y^2 - r^2 */
	register dxsq = 1;		/* (x+dx)^2-x^2*/
	register dysq = 1 - 2*r;
	register exy;
	int x0 = x1;
	register y0 = y1 - r;
	
	y1 += r;
	
	if (f == F_XOR) {	/* endpoints coincide */
		lpoint(b,Pt(x0,y0),f);
		lpoint(b,Pt(x0,y1),f);
	}
	else {
		cursinhibit();
	}
	while(y1 > y0) {
		lpoint(b,Pt(x0,y0),f);
		lpoint(b,Pt(x0,y1),f);
		lpoint(b,Pt(x1,y0),f);
		lpoint(b,Pt(x1,y1),f);
		exy = eps + dxsq + dysq;
		if(-exy <= eps+dxsq) {
			y1--;
			y0++;
			eps += dysq;
			dysq += 2;
		}
		if(exy <= -eps) {
			x1++;
			x0--;
			eps += dxsq;
			dxsq += 2;
		}
	}
	lpoint(b,Pt(x0,y0),f);
	lpoint(b,Pt(x1,y0),f);
	if(f!=F_XOR)
		cursallow();
}
