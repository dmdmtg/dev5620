/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)exit.c	2.5);

#include <dmd.h>
#include <dmdio.h>
#define _SYSEXIT	4

void
exit()
{
	register int i;
	register FILE *f;
	for (i = 1, f = &_iob[1]; i < _NFILE; i++, f++)
		fclose(f);
	tag(_SYSEXIT);
	jputshort(i);
	jflush();
	jgetshort();
	reboot();
}
