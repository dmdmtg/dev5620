/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)menu.c	2.8);
*/

#include "dmd.h"
#include "../menu.h"
#include "../protocol.h"

extern int currmenu, currbutt, buttmenu[4];

extern NewMenu menus[];

Texture16 icon3 = {
	 0x1FF8, 0x1008, 0x1008, 0x1008,
	 0x1FF8, 0x1FF8, 0x1FF8, 0x1FC0,
	 0x101E, 0x101C, 0x101E, 0x1FD7,
	 0x1002, 0x1008, 0x1008, 0x1FF8,
};
Texture16 icon2 = {
	 0x0FFC, 0x0804, 0x0804, 0x0804,
	 0x0FFC, 0x0FFC, 0x0FFC, 0x0E1C,
	 0x08C4, 0x09E4, 0x08C4, 0x0EDC,
	 0x08C4, 0x0804, 0x0804, 0x0FFC,
};
Texture16 icon23 = {
	 0x1FF8, 0x1008, 0x1008, 0x1008,
	 0x1FF8, 0x1FF8, 0x1FF8, 0x1C00,
	 0x119E, 0x13DC, 0x119E, 0x1D97,
	 0x1182, 0x1008, 0x1008, 0x1FF8,
};

/*
Texture16 deadmouse = {
	 0x0000, 0x0000, 0x0000, 0x0000,
	 0x0000, 0x000C, 0x0082, 0x0441,
	 0xFFE1, 0x5FF1, 0x3FFE, 0x17F0,
	 0x03E0, 0x0000, 0x0000, 0x0000,
};
Texture16 ok = {
	 0x1C44, 0x2248, 0x2250, 0x2270,
	 0x2248, 0x1C44, 0x0000, 0x0380,
	 0x0440, 0x0440, 0x0080, 0x0100,
	 0x0100, 0x0100, 0x0000, 0x0100,
};

Texture16 coffee = {
	 0x0000, 0x0380, 0x0400, 0x03E0,
	 0x0010, 0x07E0, 0x1FFC, 0x1002,
	 0x101A, 0x101A, 0x1002, 0x103C,
	 0x1810, 0x0FE0, 0x0000, 0x3FFC,
};
*/

dmcursor()
{
	cursswitch( &C_deadmouse );
}

pendulum;

waitrcvchar()
{
	int c;

	while( (c = rcvchar()) == -1 ){
		if( pendulum ) cursswitch( &C_cup );
		wait(RCV);
	}
	return c;
}


menuop( c )
unsigned char c;
{
	register char *s;
	register int  i, z, b;

	switch( c ){
	case M_BUTT:
		buttmenu[currbutt = charfromhost()-M_SHIFT] = currmenu;
		return;
	case M_PENDULUM:
		if( !(pendulum = charfromhost()-M_SHIFT) ) dmcursor();
		return;
	case M_MENU:
		currmenu = charfromhost()-M_SHIFT;
		return;
	case M_ITEM:
		if( (c = charfromhost()-M_SHIFT) >= M_ITEMS ) hosterr();
		if( !menus[currmenu].item[c] ) hosterr();
		s = &menus[currmenu].item[c][0];
		while( c = charfromhost() ) *(s++) = c;
		*s = '\0';
		return;
	case M_NULL:
		if( (c = charfromhost()-M_SHIFT) > M_ITEMS ) hosterr();
		for( z = 0; z <= M_ITEMS; ++z )
			if( !menus[currmenu].item[z] ){
				s = menus[currmenu].item[c];
				menus[currmenu].item[c] = 0;
				menus[currmenu].item[z] = s;
				return;
			}
		hosterr( "null" );
	case M_SUGGEST:
		menus[currmenu].prevtop = addrfromhost();	
		menus[currmenu].prevhit = 0;
		return;
	case M_HIT:
		b = charfromhost()-M_SHIFT;
		wait( MOUSE );
		cursswitch( b == 3 ? &icon3 : &icon2 );
		while( !bttn123() ) wait(MOUSE);
		cursswitch(0L);
		shorttohost( (bttn(b)? menuhit(&menus[buttmenu[b]],b):-1)
				+ M_SHIFT);
		while( bttn123() ) {};
		dmcursor();
		return;
	case M_CONFIRM:
		cursswitch(&C_confirm);
		while( !bttn123() ) wait(MOUSE);
		sendchar( bttn3() );
		while( bttn123() ) wait(MOUSE);
		dmcursor();
		return;
	case M_LIMITS:
		lonumeric = longfromhost();
		hinumeric = longfromhost();
		menus[M_NUMERIC].generator = limitsgen;
		return;
	case M_BITVEC:
		for( i = 0; i < M_BVSIZE/8; ++i )
			bitvector[i] = charfromhost();
		menus[M_NUMERIC].generator = bvgen;
		break;
	default: 
		hosterr();
	}
}

freehit(b)
{
	register int m;

	if( buttmenu[b] && bttn(b) ){
		cursswitch( 0L );
		if( (m= menuhit(&menus[buttmenu[b]], b)) != -1 ){
			sendchar( ESCAPE );
			sendchar( M_HIT );
			shorttohost( m+M_SHIFT );
			sendchar( b+M_SHIFT );
			dmcursor();
			return 1;
		}
		choosecursor();
	}
	return 0;
}

relbtn1()
{
	Texture16 *sc;

	if( bttn1() ){
		sc = cursswitch(0L);
		request(RCV|KBD|SEND);
		sleep(1);
		request(RCV|KBD|SEND|MOUSE);
		while( bttn1() ){}
		cursswitch(sc);
	}
	return 1;
}

choosecursor()
{
	cursswitch( buttmenu[2]&&buttmenu[3] ? &icon23 : &C_deadmouse );
}
