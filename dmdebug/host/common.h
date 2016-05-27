/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
HVERSION(common,@(#)common.h	2.5);
*/


typedef long	MLONG;
typedef short	MSHORT;
typedef char	MBYTE;

#include <stdio.h>
#include <ctype.h>
#include "../protocol.h"
#include "dmdoffsets.h"

MLONG peekshort(), peekbyte(), peeklong(), longfromjerq(), shortfromjerq();
void  pokeshort(), pokebyte(), pokelong(), jerqdo(), addr_desc();
char  *jerqkbd(), *peeknstr();
unsigned char ofetch();

char *fmtstring(), *fmtchar(), *fmtbyte(), *fmtshortstr(),
	*display(), *doh(), *fmtdot(), *fmtxref(), *graphopnames();

char *calloc(), *realloc(), *talloc(), *fmt(), *fmtreturn();
void free();

char *sofile(), *soline(), *fsoline(), *basename(), *srcline();

char *strcpy(), *strcat(), *strncpy(), *strncat();
int strncmp();

long lseek();
long scrhit(), snap(), m_key(), table();
char *readuser();

long	rvalue(), hostrvalue();
MLONG locate();

char *mcctype();

#define assert(e) { if( !(e) ) { wrap( 1 ); } }

extern	int oflag, hatebs, sccsflg;
extern	char *missing;

#define flush() fflush( stdout )

int setbpt(), clrbpt();
int quitc(), newc(), breakptmenu(), goc(), haltc(), stmtstepc();
int localsc(), stkframec(), tracebackc(), globalsc();


typedef struct Menu{
	char	**item;		/* string array, ending with 0 */
} Menu;

#define FLEX	4
#define	FLEX_SZ	8+FLEX
