/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)discture.c	2.4);

#include <dmd.h>
#define ltexture
#include <pandora.h>

/*	Fill a disc of radius r centered at x1,y1
 *	The boundary is a sequence of vertically, horizontally,
 *	or diagonally adjacent points that minimize 
 *	abs(x^2+y^2-r^2).
 *
 *	The circle is guaranteed to be symmetric about
 *	the horizontal, vertical, and diagonal axes
 */
void
discture(b, p, r, t, f)
	Bitmap *b;
	Point p;
	Texture *t;
{
	int	eps, exy, dxsq, dysq;
	register x0, y0, x1, y1;

	x0 = x1 = p.x;
	x1++;
	y0 = y1 = p.y;
	y0 -= r;
	y1 += r;
	dxsq = 1;
	dysq = 1 - 2*r;
	eps = 0;

	if(f!=F_XOR)
		cursinhibit();
	while(y1 > y0) {
		exy = eps + dxsq + dysq;
		if(-exy <= eps+dxsq) {
			ltexture(b, Rect(x0, y0, x1, y0+1), t, f);
			ltexture(b, Rect(x0, y1, x1, y1+1), t, f);
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
	ltexture(b, Rect(x0, y0, x1, y0+1), t, f);
	if(f!=F_XOR)
		cursallow();
}
