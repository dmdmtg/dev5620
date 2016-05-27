/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)citoh.c	2.3);
#include <dmd.h>
#include "printer.h"

extern char *ito4c();

citohinit()
{
}

citohginit(xbits, ybits)
int xbits, ybits;
{
	register int fill;
	register int i;

	Prntheads = 8;

	shipnchar("\r\n");

	/* reset the printer */
	shipnchar("\033c1");

	/* set print quality */
	switch(Prntquality) {
	case 0: /* draft - bidirection - single strike */
		shipnchar("\033<\033\"");
		break;
	case 1: /* final - unidirection - single strike */
		shipnchar("\033>\033\"");
		break;
	}

	/* set vertical density */
	shipnchar("\033T16");
	/* set horizontal density */
	switch(Hdpi) {
	case 0: /* 80 dpi */
		shipnchar("\033N");
		break;
	case 1: /* 96 dpi */
		shipnchar("\033E");
		break;
	case 2: /* 136 dpi */
		shipnchar("\033Q");
		break;
	}

	/*
	 * vertical centering is done by sending line feeds
	 * horizontal centering done by setting the printers margins
	*/
	if(Center) {
		fill = (Prntlength - ybits) / 16;
		for(i=0 ; i < fill ; ++i)
			shipchar('\n');

		fill = (Prntwidth - xbits) / 16;
		if(fill) {
			shipnchar("\033L");
			shipnchar( &(ito4c(fill))[1] );
		}
	}
		
	if(Sop) return(Center?200:50);
	   else return(0);
}

citohslice(xbits, slicesize)
short xbits, slicesize;
{
	register int i, j;
	register int c;
	register int stop = 0;
	static short delays[7][4] = {
		28, 55, 79,  84,
		37, 55, 79,  103,
		30, 55, 79,  103,
		0,  0,  0,   0,
		44, 69, 99,  104,
		50, 87, 124, 143,
		45, 73, 103, 125
		};

	/* go into graphics mode */
	shipnchar("\033S");
	shipnchar( ito4c(xbits) );

	for (i=0; i<xbits; i++) {
		if( bookkeep() )
			stop = 1; /* must print remainder of line in
					     graphics mode */
		if(!stop) {
			for (c=0, j=0; j<slicesize ; j++) {
				if (isbitset(Pt(i,j)))
					c |= (1 << j);
			}
			shipchar((char) c);
		}
		   else
			shipchar('\0');
	}

	shipnchar("\r\n");
	if(Sop)
		return(delays[(Prntquality<<2)|Hdpi][min(xbits/200, 3)]);
	   else
		return(0);
}

citohgend()
{
	if(Center) shipchar('\f');
}

citohtinit()
{
	/* reset printer */
	shipnchar("\033c1");
	/* set print quality */
	switch(Prntquality) {
	case 0: /* draft - bidirection single strike*/
		shipnchar("\033<\033\"");
		break;
	case 1: /* final - unidirection bold */
		shipnchar("\033>\033!");
		break;
	}
}

citohtext(c, column)
int c, column;
{
	register int delay;
	static short delays[2][4] = {
		15, 32, 40,  50,
		59, 80, 117, 155
		};

	switch ((char)c) {
	case '\r':
		/*
		 * end of line delay - watch for when line wraps because
		 * this requires extra delay
		*/
		delay = delays[Prntquality][min(column/20, 3)];
		delay = (delay * ((column/80)+1) );
		return(delay);
	case '\f':
		return(350);
	}

	return(0);
}

citohtend()
{
}
