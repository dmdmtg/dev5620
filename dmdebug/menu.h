/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
HVERSION(menu,@(#)menu.h	2.4);
*/

#define M_FLEX	4
#define M_MENUS 8
#define M_ITEMS 64
#define M_SHIFT 32		/* can't have \b appear in a menu msg! */

#define M_SLOT ((char *) 1)

#define M_SLOTLEN (15+M_FLEX)

#define M_MAIN 1

#define M_MEMORY 2

#define M_SCRATCH 3

#define M_CALLRET 4

#define M_NUMERIC 5

#define M_BVSIZE 256

extern int hinumeric, lonumeric;
extern char bitvector[M_BVSIZE/8];

typedef struct NewMenu{
	char	**item;			/* string array, ending with 0 */
	short	prevhit;		/* retained from previous call */
	short	prevtop;		/* also retained from previous call */
	char	*(*generator)();	/* used if item == 0 */
} NewMenu;


char *limitsgen(), *bvgen();
