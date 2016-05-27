/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)lprintf.c	2.3);
#include <dmd.h>
#include <font.h>

#define BLANK (strwidth( &defont, " " ) )

static Rectangle Trect;

char	put( c )
register char	c;
{
	register blank = BLANK;
	static Point p;
	static curpos = 0;
	static Rectangle drect;
	char	s[2];

	s[0] = c;
	s[1] = '\0';
	if ( !eqrect( drect, Trect )) {
		/**
		P->state &= ~RESHAPED;
		**/
		drect = Trect;
		put( '\f' );
	}

	switch ( c ) {
	case '\b':	
		if ( curpos ) { 
			p.x -= blank; 
			--curpos; 
		} 
		break;
	case '\f':	
		p.x = Trect.origin.x + 4; 
		p.y = Trect.origin.y + 4; 
		rectf(&display, Drect, F_CLR);
		/*
		stipple(Trect);
		*/
		break;
	case '\n':	
		p.y += defont.height;
	case '\r':	
		p.x = Trect.origin.x + 4; 
		curpos = 0;
		if ( p.y < Trect.corner.y - defont.height ) 
			break;
		scroll();
		p.y -= defont.height;
		break;
	case '\t':	
		put( ' ' );
		while ( curpos % 8 ) 
			put( ' ' );
		break;
	case '\v':	
		put( '\r' );
		/*
		stipple(Rect(p.x, p.y, Trect.corner.x, p.y + defont.height));
		*/
		/*while( p.x+BLANK < Trect.corner.x )
			p = string( &defont, " ", &display, p, F_STORE );
		put( '\r' );*/
		break;
	default:	
		s[0] &= 0x7F;
		p = string( &defont, s, &display, p, F_XOR );
		++curpos;
		if ( p.x + blank > Trect.corner.x ) 
			put( '\n' );
	}
	return c;
}


scroll()
{
	Rectangle s;
	Point d;

	s = Trect;
	s.origin.y += (defont.height + 4);
	d = Trect.origin ;
	d.y += 4;
	bitblt( &display, s, &display, d, F_STORE );
	s = Trect; 
	s.origin.y = s.corner.y - defont.height;
	rectf(&display, s, F_CLR);
	/*
	stipple( s );
	*/
}


lprintf( fmt, x )
char	*fmt;
int	*x;
{
	register c;
	char	*s;

	Trect = Drect;
	Trect.corner.y = Drect.corner.y - defont.height - 8;

	while ( (c = *fmt++) ) {
		if ( c != '%') 
			put(c);
		else {
			c = *fmt++;
			if (c == 'D' ) 
				decimal( *(long *) & x );
			else if (c == 'c') 
				put( x );
			else if (c == 's') {
				s = *(char **) & x;
				while ( c = *s++) 
					put(c);
			}
		}
	}
}


decimal( n )
register long	n;
{
	register long	a;

	if (n < 0 ) {
		put('-');
		n = -n;
	}
	if (a = n / 10) 
		decimal(a);
	put("0123456789"[n%10]);
}


