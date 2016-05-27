/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
HVERSION(dmdp, @(#)dmdp.h	2.6);
/*
 * DEFINES
*/

/* program states */
#define	MAINMENU	0
#define SCRNSEL		1
#define SCRNSTART	2
#define SCRNPRINTING	3
#define SCRNPAUSED	4
#define HOSTON		5
#define HOSTPRINTING	6
#define SCRNABORT	7
#define EXITSTATE	8

/* arguements to msg */
#define	RMMSG		(char *)0
#define WASRESHAPED	(char *)1

#define PNULL	(struct Proc *)0


/*
 * GLOBAL VARIABLES
*/

#ifdef MAINFILE

#ifdef DEBUG
int debugflg;
int Delay;
#endif

int State;
int Lockdmd;
struct Proc *Target;
Bitmap Screen = {(Word *)(0x700000L), 25, 0, 0, XMAX, YMAX};
Bitmap *Sp;
Rectangle Srect;
Rectangle SaveSrect;
Bitmap *Offscreen;
struct Printers *Pr;
char Sop;
char Sop8bits;
char Transparent;
char Center;
char Docopy;
char Hdpi;
char Vdpi;
char Prntquality;
char Paperwidth;
char Prntheads;
short Prntwidth;
short Prntlength;
int Request;


/*
 * menus
*/

char *Maintext[] = {
	"Screen",
	"  Host  ", /* menu looks better spread out a little */
	"Exit",
#ifdef DEBUG
	"-------",
	"Debug",
	"No Debug",
	"Inc Delay",
	"+10",
	"Dec Delay",
	"+10",
#endif
	NULL
};

Menu Mainmenu = {Maintext};

char *Sseltext[] = {
	"Select Layer",
	"Sweep Rectangle",
	"Whole Screen",
	"Main Menu",
	NULL
};

Menu Sselmenu = {Sseltext};

char *Sstrttext[] = {
	"Print",
	"Main Menu",
	NULL
};

Menu Sstrtmenu = {Sstrttext};

char *Sprtext[] = {
	"Pause",
	"Continue",
	"Main Menu",
	NULL
};

Menu Sprmenu = {Sprtext};

char *Ontext[] = {
	"Printer On",
	"Main Menu",
	NULL
};

Menu Onmenu = {Ontext};

char *Offtext[] = {
	"Printer Off",
	"Main Menu",
	NULL
};

Menu Offmenu = {Offtext};

Menu *menus[] = {
	&Mainmenu,
	&Sselmenu,
	&Sstrtmenu,
	&Sprmenu,
	&Sprmenu,
	&Onmenu,
	&Offmenu
};

char *Setuptext[] = {
	" Show Printer Page...(S)",
	" Reshape To Page.....(S)",
	">Center..............(S)",
	" No Center...........(S)",
	" Offscreen Copy......(S)",
	">No Offscreen Copy...(S)",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

Menu Setupmenu = {Setuptext};

#else /* externs of above globals */

#ifdef DEBUG
extern int debugflg;
extern int Delay;
#endif

extern int State;
extern int Lockdmd;
extern struct Proc *Target;
extern Bitmap Screen;
extern Bitmap *Sp;
extern Rectangle Srect;
extern Rectangle SaveSrect;
extern Bitmap *Offscreen;
extern struct Printers *Pr;
extern char Sop;
extern char Sop8bits;
extern char Transparent;
extern char Center;
extern char Docopy;
extern char Hdpi;
extern char Vdpi;
extern char Prntquality;
extern char Paperwidth;
extern char Prntheads;
extern short Prntwidth;
extern short Prntlength;
extern int Request;

#endif
