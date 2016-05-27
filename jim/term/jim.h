/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
HVERSION(jim, @(#)jim.h	1.2);
#include "../frame/frame.h"
#include "msgs.h"
#include "menu.h"

typedef struct Text{
	Frame	*frame;
	unsigned char file;	/* Which file associated with frame */
	char	obscured;	/* Whether another frame covers part of this */
	int	selecthuge;	/* selection is bigger than visible */
	struct Text *next;	/* linked back to front */
}Text;
extern Rectangle diagrect;
extern int diagclr;
extern short newlnsz;
extern Text *current;	/* which guy we are typing at (can be diag) */
extern Text *worktext;	/* which guy we are working on (never diag) */
extern Text *text;	/* list of text frames */
extern Texture bullseye;
extern Texture deadmouse;
extern String typein;
extern int diagdone;
extern int diagnewline;
extern int snarfhuge;
extern Text *diag;	/* separate from the rest */
extern Text *txalloc();

#define	PRIME		0
#define	STARDOT		1

#define	INFINITY	32767
#define	M		2

Text	*textoffile(), *textofpoint();

extern Rectangle screenrect;
#define	UP	0
#define	DOWN	1
#define	MAXFILES	256
extern unsigned char menupos[];
extern int iodone, diagdone, scrolllines, filedone;
