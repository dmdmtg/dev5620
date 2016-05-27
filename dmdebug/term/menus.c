/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)menus.c	2.3);
*/

#include "common.h"
#include "../menu.h"

char *m_main[] =
	{ M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT,
	  M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, 0 };

char *m_scratch[] =
	{ M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT,
	  M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT,
	  M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT,
	  M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT,
	  M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT,
	  M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT,
	  M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT,
	  M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT,
	  0 };

char *m_callret[] = { M_SLOT, M_SLOT, M_SLOT, M_SLOT, 0 };

char *m_memory[] =
	{ M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT,
	  M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, M_SLOT, 0 };

static char digits[10];
static int index;

int hinumeric, lonumeric;
char bitvector[M_BVSIZE/8];


static pic9( n )
long n;
{
	if(n/10) pic9(n/10);
	digits[index++] = "0123456789"[n%10];
}

char *decimal(i)
long i;
{
/*	if( i < 0 ) return 0;			allow negative */
	digits[0] = ' ';
	index = 1;
	if( i < 0 ){
		digits[index++] = '-';
		i = -i;
	}
	pic9((long)i);
	digits[index++] = ' ';
	digits[index] = '\0';
	return digits;
}

bvpos(n)		/* used on host and jerq! */
{
	register i;

	for( i = 0; i < M_BVSIZE; ++i )
		if( (bitvector[i/8]>>(i%8)) & 1 ){
			if( n-- == 0 ) return i;
		}
	return -1;
}

char *bvgen(i)
{
	i = bvpos(i);
	return i < 0 ? (char *)0 : decimal((long) i);
}

char *limitsgen(i)
{
	if( i > hinumeric-lonumeric ) return 0;
	return decimal((long)(i+lonumeric));
}


NewMenu menus[] = { {0},
	{m_main}, {m_memory}, {m_scratch}, {m_callret}, { 0, 0 }, {0} }; 

int currmenu, currbutt, buttmenu[4];

char m_strings[100][M_SLOTLEN+1];

m_init()
{
	register m, i, s = 0;

	for( m = 1; menus[m].item; ++m )
		for( i = 0; menus[m].item[i]; ++i )
			menus[m].item[i] = &(m_strings[s++][0]);
}
