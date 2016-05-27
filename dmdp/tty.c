/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)tty.c	2.3);
#include <dmd.h>
#include "printer.h"

static int indent; /* amount to indent set in ginit() and used in slice() */

ttyinit()
{
	/*
	 * 5310/5320 talks 7 bits + odd parity
	*/
	if(Sop)
		Sop8bits = 1;
}

ttyginit(xbits, ybits)
int xbits, ybits;
{
	register int fill;
	register int i;

	Prntheads = Vdpi ? 12 : 6;

	shipnchar("\r\n");

	/*
	 * vertical center is done as a series of graphic linefeeds in
	 * graphics mode. This is done because I don't want to change
	 * lines/page. Horizontal center is done in ttyslice() by
	 * skipping indent bits.
	*/
	if(Center) {
		shipnchar("\033P2q");
		fill = (Prntlength - ybits ) / (Vdpi ? 24 : 12);
		for(i=0 ; i<fill ; ++i)
			shipchar('-');
		shipnchar("\033\\");
		shipchar('\r'); /* shifts printout to the right without this */
		
		indent = (Prntwidth - xbits ) / 2;
	}
	   else
		indent = 0;

	/*
	 * go into proper graphics mode
	*/
	switch( (Hdpi<<1)|Vdpi ) {
	case 0:
		shipnchar("\033P9q");     /* low horizontal - low vertical */
		break;
	case 1:
		shipnchar("\033P\0359q"); /* low horizontal - high vertical */
		break;
	case 2:
		shipnchar("\033P0q");     /* high horizontal - low vertical */
		break;
	case 3:
		shipnchar("\033P\0350q"); /* high horizontal - high vertical */
		break;
	}

	if(Sop) return(Center?160:50);
	   else return(0);
}

/*
 * In high density two lines of data are sent for each slice - first the
 * even lines than the odd. The printer steps half a wire distance between
 * the two lines.
*/
ttyslice(xbits, slicesize)
short xbits, slicesize;
{
	register int i, j;
	/*
	 * delay[density][line_length]
	*/
	static short delay[4][5] = {
		75,  105, 145, 185, 190,
		140, 210, 300, 380, 400,
		50,  100, 115, 145, 185,
		110, 165, 220, 270, 375
		};

	/*
	 * One pass for low density - two for high
	*/
	for(j=0 ; j<=Vdpi ; ++j) {
		/*
		 * if Center, skip indent bits
		*/
		if(indent) {
			shipchar('!');
			shipnchar( ito4c(indent) );
			shipchar((char)0x3f);
		}
		/*
		 * send out a line of bits
		*/
		for (i=0; i<xbits; i++) {
			if( bookkeep() )
				return;
			switch(Vdpi) {
			case 0:
				buildchar(i, slicesize, 0, 1);
				break;
			case 1:
				switch(j) {
				case 0: /* first pass - even scan lines */
					buildchar(i, slicesize, 0, 2);
					break;
				case 1: /* second pass - odd scan lines */
					buildchar(i, slicesize, 1, 2);
					break;
				}
				break;
			}
		}
		/*
		 * In high density the printer interpets the first one of
		 * these to be half step
		*/
		shipchar('-');
	}

	if(Sop)
		return( delay[(Hdpi<<1)|Vdpi][min((xbits+indent)/200, 4)] );
	   else
		return(0);
}

/*
 * build a character in X position hbit, with Y length slicesize, starting
 * at Y position init, increment incr. General routine to stuff bits
 * into a byte in low or high density format
*/
buildchar(hbit, slicesize, init, incr)
int hbit, slicesize;
int init, incr;
{
	register int c, i, j;

	for (c=0, i=init, j=0; i<slicesize ; i+=incr, ++j) {
		if (isbitset(Pt(hbit,i)))
			c |= (1 << j);
	}
	c += 0x3f;
	shipchar((char) c);
}

/*
 * exit graphics mode
*/
ttygend()
{
	shipnchar("\033\\");
	if(Center) shipchar('\f');
	   else shipnchar("\r\n\n");
}

ttytinit()
{
	if(Prntquality)
		shipnchar("\033[5m");
}

ttytext(c, column)
int c;		/* the character just printed */
int column;	/* column position of that character */
{
	register int delay;    /* temp storage for delay */
	register int cperline; /* characters per line */
	/*
	 * delays[print_quality][line_length]
	*/
	static short delays[2][6] = {
		17, 25, 35, 42, 55,  70,
		35, 55, 75, 90, 120, 150
		};

	switch ((char)c) {
	case '\r':
		/*
		 * end of line delay - watch for when line wraps because
		 * it requires extra delay
		*/
		delay = delays[Prntquality][min(column/20, 5)];
		cperline = Paperwidth ? 132 : 80;
		if(column >= cperline)
			delay = (delay * ((column/cperline)+1));
		return(delay);
	case '\b':
		return(25);
	case '\f':
		return(160);
	}

	return(0);
}

ttytend()
{
	if(Prntquality)
		shipnchar("\033[m");
}
