/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)jstring.c	2.4);

#include <dmd.h>
#include <font.h>

/*extern Font defont;*/
/*extern Point PtCurrent;*/
/*extern Point string();*/
#undef jstring
Point jstring(s)
#define jstring Sjstring
	register char *s;
{
	return PtCurrent=string(&defont,s,&display,PtCurrent,F_XOR);
}
