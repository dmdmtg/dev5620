/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)put.c	2.5);

#include <dmd.h>
#include <dmdio.h>
#define _SYSWRITE	3
#undef putc
#undef putchar

putchar(c)
{
	putc(c,stdout);
}

putc(c,f)
register FILE *f;
{
	register i = 0;

	*f->cp++ = c;
	if (--f->count == 0 || ((c == '\n') && isatty(f)))
		i = fflush(f);
	return(i);
}

fflush(f)
register FILE *f;
{
	register int n, r;

	if ((f->flag & _IOWRT) && ((n = f->cp - f->base) > 0))
		r = _write(fileno(f),f->base,n);
	f->cp = f->base;
	f->count = BUFSIZ;
	return((r == n) - 1);
}

puts(s)
register char *s;
{
	fputs(s,stdout);
}

fputs(s,f)
register char *s;
register FILE *f;
{
	register int c;
	while (c = *s++)
		putc(c,f);
}

_write(fd,buf,n)
char *buf;
{
	tag(_SYSWRITE);
	jputshort(fd);
	jputbuf(buf,n);
	return(jgetshort());
}

