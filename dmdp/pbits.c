/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)pbits.c	2.5);
#include <dmd.h>
#include <dmdio.h>
#define Jcursinhibit
#define Jcursallow
#include <pandora.h>
#include "dmdp.h"
#include "printer.h"

Bitmap *prntbuf;
Point sorigin;

int not_changed;
int startslice;

printbitmap()
{
	register short ybits;
	register short xbits;
	register Bitmap *slice;
	register short slicesize;
	register short i;
	register int delay;
	Rectangle prect;

	ybits=Srect.corner.y-Srect.origin.y;
	xbits=Srect.corner.x-Srect.origin.x;
	not_changed = 1;


	msg("Screen: Printing");

	delay = (*(Pr->initgraphics))(xbits, ybits);
	if(Sop) alarm(delay);

	if(!Offscreen) {
		slice = balloc(Rect(0, 0, Srect.corner.x-Srect.origin.x, Prntheads));
		if(!slice) {
			State=MAINMENU;
			msg("Screen: No Memory in DMD");
			rectf(Sp, Srect, F_XOR);
		}
		sorigin = Pt(0,0);
		prntbuf = slice;
	}
	   else {
		slice = 0;
		prntbuf = Offscreen;
	   }

	if(Sop) layback();
	rect_changed();

	for (i=0; i<=ybits && State == SCRNPRINTING ; i+=Prntheads ) {
		slicesize = min(ybits-i, Prntheads);
		prect.origin.x = Srect.origin.x;
		prect.origin.y = Srect.origin.y+i;
		prect.corner.x = Srect.corner.x;
		prect.corner.y = Srect.origin.y+i+slicesize;
		rectf(Sp,prect,F_XOR);
		if(!Offscreen) {
			Jcursinhibit();
			bitblt(Sp, prect, slice, Pt(0,0), F_STORE);
			Jcursallow();
		}
		   else
			sorigin = prect.origin;
		startslice = realtime();
		delay = (*(Pr->prntslice))(xbits, slicesize);
		if(State != SCRNPRINTING) continue;
#ifdef DEBUG
		if(debugflg)
			lprintf("scrn: delay = %D\n", realtime() - startslice);
#endif
		if(Sop) {
			alarm( max(delay - (realtime() - startslice), 0) );
			layback();
		}
		rect_changed();
	}

	if(State == SCRNABORT) {
		prect.origin.x = Srect.origin.x;
		prect.origin.y = Srect.origin.y+i;
		prect.corner.x = Srect.corner.x;
		prect.corner.y = Srect.corner.y;
		rectf(Sp,prect,F_XOR);
	}

	(*(Pr->endgraphics))();

	if(slice)
		bfree(slice);

	if(State != MAINMENU) {
		State = MAINMENU;
		msg(RMMSG);
	}
}

/*
 * Called by the print drivers:
 *
 * watches for ^S from printer (for compatibility if we get flow control
 *	in the future) with own&PSEND
 * lets go of cpu to be nice
 * allows menus to go up
 * checks print area hasn't changed (rect_changed)
*/
bookkeep()
{
	static int callcount = 0;

	/*
	 * own()&PSEND will not be true if the printer blocked with ^S
	*/
	if(!Sop)
		while( !(own()&PSEND) && State==SCRNPRINTING )
			prntpoll(Lockdmd ? 0 : (MOUSE|PSEND) );

	/*
	 * only give up cpu every 80'th call - Don't make
	 * the drivers worry about these timing problems - giving up
	 * more often would cause other layers to hog too much -
	 * giving up less often makes the menu slow in appearing
	*/
	if(++callcount >= 80)
		callcount = 0;
	   else
		return( (State==MAINMENU) || (State==SCRNABORT) );

	/*
	 * poll for menus
	*/
	prntpoll(Lockdmd ? 0 : CPU);

	/*
	 * just saying don't look for rect_changed if you
	 * already found out it did - don't make the printer drivers
	 * worry about this - they can just finish the line and
	 * printbitmap will strighten things out
	*/
	if(not_changed)
		if(rect_changed())
			not_changed = 0;

	return( (State==MAINMENU) || (State==SCRNABORT) );
}

/*
 * kick your feet back and take a rest - do timing for Sop
*/
layback()
{
	do {
		prntpoll(Lockdmd ? 0 : (MOUSE|ALARM) );
	} while(!(own()&ALARM));
}

prntpoll(pollfor)
int pollfor;
{

	/*
	 * don't display menu if in process of aborting
	*/
	if(State == SCRNABORT || State == MAINMENU) {
		if(!Lockdmd) wait(CPU);
		return;
	}

	do {
		switch(poll(pollfor)) {
		case 0: /* Pause */
			State = SCRNPAUSED;
			msg("Screen: Printing Paused");
			pollfor = Lockdmd ? 0 : MOUSE;
			break;
		case 1: /* Continue */
			if(State != SCRNPRINTING) {
				State = SCRNPRINTING;
				msg("Screen: Printing");
			}
			break;
		case 2: /* Main Menu */
			State = SCRNABORT;
			break;
		}
	} while(State == SCRNPAUSED);
}

isbitset(pt)
Point pt;
{
	return((*addr(prntbuf, add(sorigin,pt)) >> (WORDSIZE-(pt.x%WORDSIZE)-1)) & 1);
}
