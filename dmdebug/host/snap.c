/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)snap.c	2.3);
*/

#include "common.h"

long snap(a)
long a;
{
	long i, nloc, disassemble();
	char v[128];

	nloc = disassemble(a, a, v);
	for( i = 0; v[i]; ++i ) if( !isprint(v[i]) ) v[i] = ' ';
	printf("%s: %s\n", doh(a), v);
	return nloc;
}

get1byte(loc)
long loc;
{
	return peekbyte(loc);
}


