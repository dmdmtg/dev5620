/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)hp.c	2.4);
#include <dmd.h>
#include "printer.h"

/*
 * The thinkjet printer cannot talk 8 bits + even parity and has trouble
 * with 7 bits + odd parity. 7 bits + odd parity is used but the driver
 * has to play some games to get it to work. The main problem is that
 * line length in graphics is sent as a two byte binary number which is
 * not possible with 7 bits + odd parity. The low level hp code strips
 * the parity bit, and graphics is implemented by making sure that line
 * length (xbits in graphics) never has the 8'th bit set. Round the
 * number up if necessary and fill in with nulls.
*/

static int indent; /* horizontal indent if Center requested */

/*
 * delays for text
*/
static short tdelays[2][4] = {
	26, 33, 40, 49,
	44, 60, 80, 100
	};
	

hpinit()
{
	if(Sop)
		Sop8bits = 1;
}

hpginit(xbits, ybits)
int xbits, ybits;
{
	register int fill;
	register int i;

	if(Sop) Prntheads = 7;
	   else Prntheads = 8;

	shipnchar("\r\n");

	indent = 0;

	/*
	 * vertical center is done with a series on linefeeds
	 *
	 * set indent so hpslice can do horizontal centering
	*/
	if(Center) {
		shipnchar("\0332");
		fill = (Prntlength - ybits) / 32;
		for(i=0 ; i<fill; ++i)
			shipchar('\n');

		indent = (Prntwidth - xbits) / (Hdpi ? 32 : 16);
	}

	/*
	 * step 7 "wires" with send only port because only 7 of the wires
	 * are being used because of the parity bit.
	*/
	if(Sop)
		shipnchar("\033A\7");
	  else
		shipnchar("\033A\8");

	if(Sop) return(Center?210:90);
	   else return(0);
}

hpslice(xbits, slicesize)
short xbits, slicesize;
{
	register short hpbits;
	register int i, j;
	register int c;
	register int stop = 0;
	register int delay;
	static short delays[2][4] = {
		70, 112, 165, 175,
		92, 149, 186, 228
		};

	/*
	 * horizontal center with spaces
	*/
	if(Center)
		for(i=0 ; i<indent ; ++i)
			shipchar(' ');

	/*
	 * go into graphics mode
	*/
	shipchar('\033');
	switch (Hdpi) {  
	case 0:
		shipchar('K');
		break;
	case 1:
		shipchar('L');
		break;
	}
	/*
	 * make sure the 8'th bit is not set - round up if necessary
	*/
	hpbits = xbits;
	if(Sop && (xbits & 0x80))
		hpbits = (hpbits & ~0xFF) + 0x100;
	/*
	 * send length as a two byte binary number
	*/
	shipchar((char)(hpbits & 0xFF));
	shipchar((char)((hpbits >> 8) & 0xFF));

	/*
	 * print the slice
	*/
	for (i=0; i<xbits; i++) {
		if( bookkeep() )
			stop = 1;
		if(!stop) {
			for (c=0, j=0; j<slicesize ; j++) {
				if (isbitset(Pt(i,j)))
					c |= (1 << ((Sop?6:7) - j));
			}
			shipchar((char) c);
		}
		   else
			shipchar('\0');
	}
	/*
	 * if it was necessary to round up, fill in with nulls - the printer
	 * just eats the nulls
	*/
	for(i=xbits ; i<hpbits ; ++i) {
		bookkeep();
		shipchar('\0');
	}

	shipnchar("\r\n");

	if(Sop) {
		delay = delays[Hdpi][min(xbits/200, 3)];
		if(indent)
			delay += tdelays[0][min(indent/20, 3)];

		alarm((delay*2)/3);
		while( !(own()&ALARM) )
			if( bookkeep() ) break;

		return(delay);
	}
	   else
		return(0);
}

hpgend()
{
	shipnchar("\033@");
	if(Center) shipchar('\f');
	   else shipnchar("\r\n");
}

hptinit()
{
	shipnchar("\033@");
	if(Prntquality)
		shipnchar("\033U1\033E");
}

hptext(c, column)
int c;
int column;
{
	register int delay;
	
	switch ((char)c) {
	case '\r':
		/*
		 * watch for line wrap
		*/
		delay = tdelays[Prntquality][min(column/20, 3)];
		delay = (delay * ((column/80)+1));
		return(delay);
	case '\b':
		return(12);
	case '\f':
		return(350);
	}

	return(0);
}

hptend()
{
	if(Prntquality)
		shipnchar("\033U0\033F");
}
