/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)graphics.c	2.7);
*/

#include "dmd.h"
#include "../protocol.h"

/*
Bitmap physical = { (Word *) 0x700000, 25, 0, 0, XMAX, YMAX };
*/

Bitmap bs =  { (Word *) 0, 1, 0, 0, 32, 32 };

extern Rectangle scrolling;

/*
goutline( r )
Rectangle r;
{
	segment( &dphysical, r.origin, Pt(r.origin.x,--r.corner.y), F_XOR );
	segment( &dphysical, Pt(--r.corner.x,r.origin.y), r.origin, F_XOR );
	segment( &dphysical, Pt(r.origin.x,r.corner.y), r.corner, F_XOR );
	segment( &dphysical, r.corner, Pt(r.corner.x,r.origin.y), F_XOR );
}
*/

int StartFocus = 45;

Focus(r)
Rectangle r;
{
	register i;
	outline(r);
	while( !bttn123() ){
		for( i = StartFocus; i>=0 && !bttn123(); --i ){
			outline(inset(r,-i));
			nap(2);
			outline(inset(r,-i));
		}
		for( i = 1; i<=5 && !bttn123(); ++i )
			sleep(4);
	}
	outline(r);
}


#define  POINTNAP 30

graphop( c )
char c;
{
	long a, addrfromhost();
	Rectangle r, clipped;
	Bitmap *b;
	Point shift, p;
	int n, i;
	Texture16 *ocurs;

	a = addrfromhost();
	wait( MOUSE );
	switch( c ){
	default: hosterr();
	case G_POINT:
		p = *(Point *) a;
		Focus(Rpt(p,p));
		return;
	case G_16TEXTURE:
		ocurs = cursswitch( a );
		while( !bttn123() ) wait(MOUSE);
		cursswitch(ocurs);
		return;
	case G_RECTANGLE:
		r = *(Rectangle *)a;
		if( rectclip(&r,Rect(0,0,XMAX,YMAX)) )
			Focus(r);
		return;
	case G_BITMAP:
		b = (Bitmap *) a;
		break;
	case G_TEXTURE:
		b = &bs;
		b->base = (Word *) a;
	}

	/* The following code is executed for Bitmaps and 32-bit Textures */

	cursswitch( 0L );
	while( !bttn123() ){
		shift = sub( mouse.xy, div(add(b->rect.corner,b->rect.origin),2) );
		r = raddp( b->rect, shift );
		outline(r);
		nap(2);
		outline(r);
	}
	if( bttn23() && rectclip( &r, scrolling ) ){
		clipped = rsubp( r, shift );
		bitblt(b, clipped, &display, r.origin, F_STORE);
	}
	while( bttn123() ) {};
	dmcursor();
}
