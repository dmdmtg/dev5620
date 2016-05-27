/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)printer.c	2.1);
#include "printer.h"

struct Printers Printers[] = {

/* 5310/20 */	2, 4, 6,
/*** 1 ***/	1, 1, 0, 0,

		ttyinit,
		ttyginit,
		ttyslice,
		ttygend,
		ttytinit,
		ttytext,
		ttytend,

		594,  986,
		1188, 1972,
		0,    0,
		0,    0,

		756,
		1512,

/* 8510b */	3, 4, 6,
/*** 2 ***/	0, 0, 0, 0,

		citohinit,
		citohginit,
		citohslice,
		citohgend,
		citohtinit,
		citohtext,
		citohtend,

		640,  0,
		768,  0,
		1088, 0,
		0,    0,

		756,
		0,

/* thinkjet */	2, 3, 5,
/*** 3 ***/	0, 0, 0, 0,

		hpinit,
		hpginit,
		hpslice,
		hpgend,
		hptinit,
		hptext,
		hptend,

		638,  0,
		1280, 0,
		0,    0,
		0,    0,

		1008,
		0
		};
