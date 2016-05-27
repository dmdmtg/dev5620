/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)zdc.c	2.2);
*/

#include "common.h"
#define DADDR 0x500000

zdc( addr, duration )
MLONG addr;
{
	if( addr < 0 || addr >= 1024 || duration < 0 || duration > 60 ){
		printf( "use .zd 0<=k<=1024 0<=t<=60\n" );
		return;
	}
	pokeshort( DADDR, (( (addr*156)/100 )*25));
	flush();
	sleep( duration );
	pokeshort( DADDR, 0 );
}
