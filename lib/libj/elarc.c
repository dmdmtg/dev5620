/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)elarc.c	2.5);

#include	<dmd.h>

#define HUGE 017777777777
#define	sgn(x)	((x)<0? -1 : (x)==0? 0 : 1)

#define	POINT	FIvoid(74)

/*static*/ struct dist {
	Point s;
	Point m;
	long e;
} d1, d2;

static void
test(x, p)
	Point x;
	register struct dist *p;
{
	register long dx = x.x - p->s.x;
	register long dy = x.y - p->s.y;
	register long e = dx*dx+dy*dy;

	if(e <= p->e) {
		p->m = x;
		p->e = e;
	}
}

static void
survey(bp, x, f)
	Bitmap *bp;
	Point x;
	Code f;
{
	test(x, &d1);
	test(x, &d2);
}
/*
 * elarc(bp,p0,a,b,p1,p2,f) draws in bitmap bp an arc of the ellipse
 * centered at p0 with half-axes a,b extending counterclockwise
 * from a point near p1 to a point near p2
 * args reversed because ellip1 draws clockwise 
 */
void
elarc(bp,p0,a,b,p1,p2,f)
	Bitmap *bp;
	Point p0, p1, p2;
	Code f;
{
	if(f!=F_XOR)
		cursinhibit();
	if(a==0)
		segment(bp, Pt(p0.x, p1.y), Pt(p0.x, p2.y), f);
	else if(b==0)
		segment(bp, Pt(p1.x, p0.y), Pt(p2.x, p0.y), f);
	else {
		int sx1;
		int sy1;
		int sx2;
		int sy2;

		d1.s = sub(p1, p0);
		d2.s = sub(p2, p0);
		sx1 = sgn(d1.s.x);
		sy1 = sgn(d1.s.y);
		sx2 = sgn(d2.s.x);
		sy2 = sgn(d2.s.y);
		d1.s.x *= sx1;
		d1.s.y *= sy1;
		d2.s.x *= sx2;
		d2.s.y *= sy2;
		d1.e = d2.e = HUGE;
		survey(bp, Pt(0, b), f);
		ellip1(bp, Pt(0, 0), a, b, survey, Pt(0,b), Pt(a, 0), f);
		if(!eqpt(d1.m, d2.m))
			POINT(bp, d1.m, f);
		ellip1(bp, p0, a, b, POINT,
			Pt(d1.m.x*sx1, d1.m.y*sy1), Pt(d2.m.x*sx2, d2.m.y*sy2), f);
	}
	if(f!=F_XOR)
		cursallow();
}
