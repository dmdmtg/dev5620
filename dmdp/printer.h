/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
HVERSION(printer, @(#)printer.h	2.4);

int ttyinit();
int ttyginit();
int ttyslice();
int ttygend();
int ttytinit();
int ttytext();
int ttytend();

int citohinit();
int citohginit();
int citohslice();
int citohgend();
int citohtinit();
int citohtext();
int citohtend();

int hpinit();
int hpginit();
int hpslice();
int hpgend();
int hptinit();
int hptext();
int hptend();

struct Printers {
	char firstvdpi;
	char firstqual;
	char firstwidth;
	char hdpiinit;
	char vdpiinit;
	char qualinit;
	char paperinit;
	int (*initsession)();
	int (*initgraphics)();
	int (*prntslice)();
	int (*endgraphics)();
	int (*inittext)();
	int (*textdelay)();
	int (*endtext)();
	short hdpl[4][2];
	short vdpl[2];
	};

extern struct Printers Printers[];
extern char Sop8bits;
extern char Prntheads;
extern char Sop;
extern char Center;
extern char Hdpi;
extern char Vdpi;
extern char Prntquality;
extern char Paperwidth;
extern short Prntwidth;
extern short Prntlength;
