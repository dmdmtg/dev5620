/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)get.c	2.5);

#include <dmd.h>
#include <dmdio.h>
#define _SYSREAD	5

getchar()
{
	return(getc(stdin));
}

getc(f)
register FILE *f;
{
	register int c;

	if (f->count == 0) {
		f->count = _read(fileno(f),f->base,BUFSIZ);
		if (f->count == 0)
			return(EOF);
		f->cp = f->base;
	}
	f->count--;
	c = *f->cp++;
	c &= 0xff;
	return(c);
}

_read(i,buf,n)
char *buf;
{
	tag(_SYSREAD);
	jputshort(i);
	jflush();
	return(jgetbuf(buf,n));
}
