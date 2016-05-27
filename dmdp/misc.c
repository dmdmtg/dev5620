/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)misc.c	2.6);
#define PANDORA
#include <dmd.h>
#include <font.h>
#include "dmdp.h"

char *
ito4c(nbits) /* create 4 char string from integer value */
int nbits;
{
	static char s[5];
	register int i;
	
	s[0]=s[1]=s[2]=s[3]='0'; s[4]='\0';
	for ( i=3 ; i >= 0 ; i--) {
		s[i]+=nbits-((nbits/10)*10);
		nbits /= 10;
	}
	return s;
}

shipchar(c)
char c;
{
	register fudge, i, b;

	/*
	* Send only port - variable Sop8bits set
	*
	* Some printers need the parity bit as a mark, otherwise it
	* gets a framming error.  This can be done by making sure that the
	* data character has odd parity so the duart will turn on the parity byte
	*
	* In other words, this makes the output from the send only port look
	* like 7 bits + odd parity
	*/
	if(Sop8bits) {
		for(i=0,fudge=0,b=c; i<7 ; i++) {
			if(b & 0x01)
				fudge++;
			b >>= 1;
		}
		if((fudge&0x01)==0)
			c |= 0x80;
	}
	while( !psendchar(c) ) /* psendchar may return 0 on error in the future */
		;
}

shipnchar(c)
register char *c;
{
	for (; c && *c; c++)
		shipchar(*c);
}

msg(s)
char *s;
{
	static char savestr[34];
	static int msgup = 0;

	switch((int)s) {
	case RMMSG:
	case WASRESHAPED:
		if(msgup) {
			dispstr(savestr);
			backgnd();
		}
		if(s == RMMSG)
			msgup = 0;	
		break;
	default:
		if(msgup)
			dispstr(savestr);
		   else
			backgnd();
		strcpy(savestr, s);
		dispstr(savestr);
		msgup = 1;
		break;
	}
}

dispstr(s)
char *s;
{
	Point drawpt;

	drawpt.x = Drect.origin.x + 2;
	drawpt.y = Drect.corner.y - defont.height - 1;
	string(&defont, s, &display, drawpt, F_XOR);
}

backgnd()
{
	Rectangle msgrect;

	msgrect = Drect;
	msgrect.origin.y = msgrect.corner.y - defont.height - 4;

	rectf(&display, msgrect, F_XOR);
}

target_insane(Target)
struct Proc *Target;
{

	if( (Target->state&BUSY) && Target->traploc == (char **) 0 )
		return(0);
	   else
		return(1);
}
