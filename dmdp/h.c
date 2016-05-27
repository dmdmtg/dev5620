/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)h.c	2.6);
#define PANDORA   /* so dmdproc.h lets me see states */
#include <dmd.h>
#define whichproc
#define cbufavail
#define passchar
#define point2layer
#include <pandora.h>
#include "dmdp.h"
#include "printer.h"

int startline;
int column;
char escapeseq[] = "\033[?\0i";
int escseqno;
int prevchar;

host()
{
	register struct Proc *rTarget;
	register struct Printers *rPr;
	register int tmp;
	register int i;
	register int c;

	msg("Host: Select Layer");
	if((Target=point2layer()) == PNULL) {
		State = MAINMENU;
		msg(RMMSG);
		return;
	}

	rTarget = Target;
	rPr = Pr;

	if(rTarget->state & PIPETO) {
		State = MAINMENU;
		msg("Host: Input Already Diverted");
		return;
	}

	P->state |= LOCKLAYER;
	if(rTarget != P)
		rTarget->state |= (whichproc(P->layer) << 16) & PIPETO;
	while(rcvchar() != -1);

	rectf(rTarget->layer, rTarget->rect, F_XOR);
	nap(20);
	rectf(rTarget->layer, rTarget->rect, F_XOR);

hostsel:
	msg("Host: Printer Off");
	escseqno = 0;

	while(State == HOSTON) {
		/* must poll for CPU to watch for layer deleted */
		switch( poll(CPU) ) { /* Onmenu */
		case 0:  /* Printer On - start printing */
			escflush();
			State = HOSTPRINTING;
			msg("Host: Printer On");
			continue;
		case 1: /* Main Menu */
			State = MAINMENU;
			msg(RMMSG);
			continue;
		}

		if(target_insane(rTarget)) {
			State = MAINMENU;
			msg("Host: Selected Layer Deleted");
			break;
		}

		while( (own()&RCV) && gotroom(rTarget) ) {
			c = rcvchar();
			if((c == '\033' || escseqno) && !Transparent) {
				if(doescape(c)) {
					State = HOSTPRINTING;
					msg("Host: Printer On");
				}
				break;
			}
			mypasschar(c, rTarget);
		}
	}

	if(State == HOSTPRINTING) {
		Request |= PSEND;
		if( !(request(Request) & PSEND) ) { /* for future compatibility */
			State = MAINMENU;
			msg("Host: Printer Not Available");
		}
		   else {
			if(!Transparent)
				(*(rPr->inittext))();
			startline = realtime();
			column = 0;
			prevchar = 0;
		   }
	}
	while(State == HOSTPRINTING) {
		/* must poll for CPU to watch for layer deleted */
		switch( poll(CPU) ) { /* Offmenu */
		case 0:  /* Printer Off - stop printing */
			State = HOSTON;
			escflush();
			if(!Transparent)
				(*(rPr->endtext))();
			Request &= ~PSEND;
			request(Request);
			goto hostsel;
		case 1:  /* Main Menu */
			State = MAINMENU;
			if(!Transparent)
				(*(rPr->endtext))();
			Request &= ~PSEND;
			request(Request);
			msg(RMMSG);
			continue;
		}

		if(target_insane(rTarget)) {
			State = MAINMENU;
			msg("Host: Print Layer Deleted");
			continue;
		}

		if(Sop) {
			if( !(own()&ALARM) ) continue;
		}
		   else {
			if( !(own()&PSEND) ) continue;
		   }

		if( (own()&RCV) && gotroom(rTarget) ) {
			c = rcvchar();
			if(!Transparent) {
				/* translate \033\033 to \033 */
				if(c == '\033' && escseqno == 1) {
					++column;
					hostchar(c);
					escseqno = 0;
				}
				if(c == '\033' || escseqno) {
					if(doescape(c)) {
						State = HOSTON;
						if(!Transparent)
							(*(rPr->endtext))();
						Request &= ~PSEND;
						request(Request);
						goto hostsel;
					}
					continue;
				}
			}
			mypasschar(c, rTarget);
			if(c != '\t' || Transparent) {
				++column;
				hostchar(c);
				if(c == '\n' || c == '\r') {
					startline = realtime();
					column = 0;
				}
			}
			   else { /* expand the tab */
				tmp = (column|7) + 1;
				for( ; column < tmp ; ++column)
					hostchar(' ');
			   }
		}
	}

	if(rTarget != P) {
	if(!target_insane(rTarget)) {
		escflush();
		for(i=0 ; i<12 ; ++i) { /* try more than once before giving up */
			if(target_insane(rTarget)) break;
			if(P->nchars <= cbufavail(rTarget)) {
				while((c=rcvchar()) != -1)
					mypasschar(c, rTarget);
				break;
			}
			wait(CPU);
		}
	}
	rTarget->state &= ~PIPETO;
	}
	P->state &= ~LOCKLAYER;
	while(rcvchar() != -1);
	sendchar((int)'\n');  /* to get prompt when dmdp exits */
}

doescape(c)
int c;
{

	escapeseq[3] = (State == HOSTON) ? '4' : '9';

	if(c == escapeseq[escseqno]) {
		++escseqno;
		if(escseqno < 5) { /* don't know yet */
			return(0);
		}
		   else {   /* this is a printer on/off sequence */
			escseqno = 0;
			return(1);
		   }
	}

	/* else not a printer on/off sequence, so recover */
	escflush();
	mypasschar(c, Target);
	if(State == HOSTPRINTING && c != '\033') {
		++column;
		hostchar(c);
	}

	return(0);
}

escflush()
{

	register int i;
	register int c;

	for(i=0 ; i<escseqno ; ++i) {
		c = escapeseq[i];
		mypasschar(c, Target);
		if(State == HOSTPRINTING && i) { /* if i == 0 then c == \033 - don't
						  pass ESC to the printer */
			++column;
			hostchar(c);
		}
	}

	escseqno = 0;
}

/*
 * returns true if selected layer has at least 10 characters of
 * buffer left - otherwise don't mess with the layer because this
 * much room must be assured for escape sequences.
*/
gotroom(target)
struct Proc *target;
{

	if(target == P)
		return(1);

	if(cbufavail(target) > 10)
		return(1);
	   else
		return(0);
}

mypasschar(c, target)
struct Proc *target;
{

	if(target == P)
		return;

	passchar(c, target);
}

hostchar(c)
register int c;
{
	register int delay;

#ifdef	DEBUG
	/*
	if(debugflg) lprintf("%c", c);
	*/
#endif	DEBUG

	shipchar(c);

	if(Sop && !Transparent) {
		if(c == '\n' && prevchar != '\r') /* handle possible -onlcr stty */
			c = '\r';
		delay = (*(Pr->textdelay))(c, column);
		if(delay) {
			if(c == '\r') {
#ifdef				DEBUG
				if(debugflg)
					lprintf("elapsed = %D\n",
						realtime() - startline);
#endif				DEBUG
				alarm( max(delay - (realtime() - startline), 0) );
			}
			   else
				alarm(delay);
		}
	}

	prevchar = c;
}
