/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)s.c	2.7);
#define PANDORA
#include <dmd.h>
#define whichproc
#define point2layer
#define whichaddr
#define Jcursinhibit
#define Jcursallow
#include <pandora.h>
#include "dmdp.h"

struct Proc *halted;
Rectangle SaveLrect;
int Savestate;

struct Proc *Srectinlayer();

scrnsel()
{

	msg("Screen: Select Print Area");
	while(State == SCRNSEL) {
		switch(poll(MOUSE)) {
		case 0: /* Select Layer */
			msg("Screen: Select Layer");
			Lockdmd = 0;
			if((Target=point2layer()) == PNULL) {
				msg("Screen: Select Print Area");
				continue;
			}
			Sp = (Bitmap *)Target->layer;
			SaveSrect = Target->rect;
			if(Target != P) {
				halted = Target;
				Target->state |= ZOMBIE;
			}
			break;
		case 1: /* Sweep Rectangle */
			msg("Screen: Sweep Rectangle");
			SaveSrect = getrect();
			if(SaveSrect.corner.x - SaveSrect.origin.x < 25 ||
			   SaveSrect.corner.y - SaveSrect.origin.y < 25) {
				msg("Screen: Select Print Area");
				continue;
			}
			if(Target=Srectinlayer()) {
				Lockdmd = 0;
				Sp = (Bitmap *)Target->layer;
				if(Target != P) {
					halted = Target;
					Target->state |= ZOMBIE;
				}
			}
			   else {
				Lockdmd = 1;
				Sp = &Screen;
				halted = PNULL;
			   }
			break;
		case 2: /* Whole Screen */
			Lockdmd = 1;
			Target = PNULL;
			Sp = &Screen;
			SaveSrect = Jrect;
			halted = PNULL;
			break;
		case 3: /* Main Menu */
			State = MAINMENU;
			msg(RMMSG);
			continue;
		default:
			continue;
		}

		Srect = SaveSrect;
		if(Target != PNULL) {
			SaveLrect = Target->rect;
			Savestate = Target->state & (RESHAPED|MOVED);
			Target->state &= ~(RESHAPED|MOVED);
		}
		clipSrect();
		P->state |= LOCKLAYER;
		rectf(Sp, Srect, F_XOR);
		State = SCRNSTART;
		scrnstart();
		if(!Offscreen) restore();
	}
}

scrnstart()
{

	register struct Proc *stipproc;
	register char *tmp;
	register int pollret;
	Rectangle rtmp;

	msg("Screen: Start Print");
	while(State == SCRNSTART) {
		pollret = poll(Lockdmd ? 0 : CPU); /* cannot poll(MOUSE) because
					must watch for layer deleted even when
					not current */
		if( rect_changed() ) continue;
		switch(pollret) {
		case 0: /* Print */
			break;
		case 1: /* Main Menu */
			State = MAINMENU;
			rectf(Sp, Srect, F_XOR);
			msg(RMMSG);
			continue;
		default:
			continue;
		}

		Request |= PSEND;
		if( !(request(Request) & PSEND) ) { /* for future compatibility */
			State = MAINMENU;
			rectf(Sp, Srect, F_XOR);
			msg("Screen: Printer Not Available");
			continue;
		}

		State = SCRNPRINTING;

		if(Docopy) {
			rtmp.corner = sub(Srect.corner, Srect.origin);
			rtmp.origin = Pt(0,0);
			if(Offscreen=balloc(rtmp)) {
				Jcursinhibit();
				bitblt(Sp, Srect, Offscreen, Pt(0,0), F_STORE);
				Jcursallow();
				rectf(Sp, Srect, F_XOR);
				Sp = Offscreen;
				Srect = rtmp;
				Target = PNULL;
				Lockdmd = 0;
				restore();
			}
		} else
			Offscreen = (Bitmap *)0;
		printbitmap();
		Request &= ~PSEND;
		request(Request);
		if(Offscreen) bfree(Offscreen);
	}
}

restore()
{

	if(Target != PNULL)
		Target->state |= Savestate;
	if(halted)
		halted->state &= ~ZOMBIE;
	P->state &= ~LOCKLAYER;
}

clipSrect()
{
	Srect.corner.x = Srect.origin.x +
		min(Prntwidth, Srect.corner.x-Srect.origin.x);
}

/*
 * used for when printing screen layers
 * handles delete, reshape or move on print area
 * also takes care of resetting global variables on move - so this must
 *   be called before doing any bitblt or rectf off (to) screen if a wait()
 *   has been done
*/
rect_changed()
{
	register struct Proc *rTarget;
	register int *rstate;
	Rectangle r;

	rTarget = Target;
	if(rTarget != PNULL) {
		if(target_insane(rTarget)) { /* if delete */
			State = MAINMENU;
			msg("Screen: Layer Deleted");
			return(1);
		}

		/* Handling MOVE and RESHAPE is really messy as you can see -
		   all of this is possible because throughout the printout Target
		   has it's ZOMBIE bit set so it cannot modify it's own MOVE
		   and RESHAPE bits */
		rstate = &(rTarget->state);
		if(*rstate & RESHAPED) {
			if(!(*rstate & MOVED)) { /* if reshape */
				Savestate &= ~MOVED;  /* Move -> Reshape - call it reshape */
				*rstate &= ~MOVED;
				State = MAINMENU;
				msg("Screen: Layer Reshaped");
				return(1);
			}
			   else  { /* Move ok - reset Srect - assume if area the
				    same layer was moved */
				/* reset layer pointer - this changes with move */
				Sp = (Bitmap *)rTarget->layer;
				r = rTarget->rect;
				Srect = Rpt(
				 add(r.origin, sub(Srect.origin, SaveLrect.origin)),
				 add(r.corner, sub(Srect.corner, SaveLrect.corner)));
				SaveSrect = Srect;
				SaveLrect = r;
				/* if not previously reshaped call it a move
					(else let it stay as a reshape) */
				if( !((Savestate&RESHAPED) && !(Savestate&MOVED)) )
					Savestate |= (RESHAPED|MOVED);
				*rstate &= ~(RESHAPED|MOVED);
			   }
		}
	}
	return(0);
}

/*
 * Are the 4 corners of Srect in an unobscured layer?
 *
 * Return the address of proctab entry if so, else 0
*/
struct Proc *
Srectinlayer()
{
	Layer *ptinlayer();
	register Layer *lp;

	lp = ptinlayer(SaveSrect.origin);
	if(!lp)
		return(PNULL);

	if(ptinlayer(SaveSrect.corner) != lp ||
	   ptinlayer( Pt(SaveSrect.origin.x, SaveSrect.corner.y) ) != lp ||
	   ptinlayer( Pt(SaveSrect.corner.x, SaveSrect.origin.y) ) != lp )
		return(PNULL);

	return( whichaddr(whichproc(lp)) );
}


/*
 * use lfront from Firm[] - it is not in Sys[] - below is from <sa.h>
*/
#define	Firm		((int	*)0x200)
#define	DCast(t, x)	(*((t *)Firm[x]))
#define	DIpLayer(x)	DCast(Layer *, x)
#define lfront		DIpLayer(139)

/*
 * Firm[] is in a different place with v1.1 -> v2.0 download Patch
 * special case it
*/
#define	PFirm		((int	*)0x71db00)
#define	PDCast(t, x)	(*((t *)PFirm[x]))
#define	PDIpLayer(x)	PDCast(Layer *, x)
#define Plfront		PDIpLayer(139)

Layer *
ptinlayer(p)
Point p;
{
	register Layer *lp;

	lp = (version() == 0x080706) ? Plfront : lfront;
	for (; lp; lp = lp->back)
		if (ptinrect(p, lp->rect))
			return(lp);
	return(0);
}
