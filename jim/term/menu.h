/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
HVERSION(menu, @(#)menu.h	1.2);
#define CONTROLmenu 0
#define EDITmenu 1

#define NEW	0
#define RESHAPE	1
#define CLOSE	2
#define	WRITE	3

#define CUT	0
#define PASTE	1
#define SNARF	2
/*
#define LOOK	3
#define	EXCH	4
#define	SEARCH	5
#define	UNIX	6
*/
#define SEARCH	3
#define UNIX	4
#define LOOK	5
#define	EXCH	5



#define WHITEfield 1
#define BLACKfield 0
#define	FRAMERECT	0
#define	SCROLLBAR	1
#define	NOTHING		2
#define	B1		0
#define	B2		1
#define	B3		2

#define	NAMELEN		25

#ifdef OLDSOFTWARE

typedef struct nMenu {
	char 	**item;		/* string array, ending with 0 */
	short	prevhit;	/* retained from previous call */
	short	prevtop;	/* also retained from previous call */
	char	*(*generator)();/* used if item == 0 */
} nMenu;

#define	Menu	nMenu
#undef	menuhit
#undef	jline
#undef	getrect
Rectangle	getrect();

#endif

#define Texture	Texture16
