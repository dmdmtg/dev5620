/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)disc.c	2.5);

#include <dmd.h>

/*	Fill a disc of radius r centered at x1,y1
 *	The boundary is a sequence of vertically, horizontally,
 *	or diagonally adjacent points that minimize 
 *	abs(x^2+y^2-r^2).
 *
 *	The circle is guaranteed to be symmetric about
 *	the horizontal, vertical, and diagonal axes
 */
void
disc(b, p, r, f)
	Bitmap *b;
	Point p;
{
	register x1=p.x, y1=p.y;
	register eps = 0;	/* x^2 + y^2 - r^2 */
	int dxsq = 1;		/* (x+dx)^2-x^2*/
	int dysq = 1 - 2*r;
	int exy;
	register x0 = x1;
	register y0 = y1 - r;
	x1++;		/* to offset dmd's half-open lines*/
	y1 += r;
	if(f!=F_XOR)
		cursinhibit();
	while(y1 > y0) {
		exy = eps + dxsq + dysq;
		if(-exy <= eps+dxsq) {
			rectf(b, Rect(x0, y0, x1, y0+1), f);
			rectf(b, Rect(x0, y1, x1, y1+1), f);
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
	rectf(b, Rect(x0, y0, x1, y0+1), f);
	if(f!=F_XOR)
		cursallow();
}
