/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)font.c	2.5);

#include <dmd.h>
#include <dmdio.h>
#include <font.h>
#define ISIZE(n)	((n+1)*sizeof(Fontchar))

/*
 * read a font from an input stream
 * 	<font header>
 *	<f->info>
 *	<f->bits>	no bitmap header!!
 *
 * WARNING! This code believes it knows what the Font structure looks like
 */

Font *
infont(inch)
	register char (*inch)();
{
/*
 * Following line changed for the DMD!
 *
 */
	short n;
	register Font *f;
	register Bitmap *b;

	if(ninch(2,&n,inch))
		return((Font *)0);
	if((f = (Font *) alloc(sizeof(Font)+ISIZE(n))) == (Font *)0)
		return(f);
	f->n = n-1;
	if(ninch(6,2 + (char *)f,inch))	/* 6 == sizeof(height+ascent+unused) */
		goto err;
	if(ninch(ISIZE(n),f->info,inch))
		goto err;
	if((b = balloc(Rect(0,0,f->info[n].x,f->height))) == (Bitmap *)0)
		goto err;
	f->bits = b;
	/*
	 * Following line changed for DMD 
	 *
	 */
	if(ninch(4*f->height*b->width,b->base,inch))
		goto berr;
	return(f);

	berr:
		bfree(f->bits);
	err:
		free(f);
	return((Font *)0);
}

static
ninch(n,s,inch)
	register n;
	register char *s,(*inch)();
{
	register x;

	do {
		*s++ = x = (*inch)();
		if(x == -1)
			return(1);
	} while (--n > 0);
	return(0);
}

ffree(f)
	register Font *f;
{
	if (f != (Font *) NULL) {
		bfree(f->bits);
		free(f);
	}
}

outfont(f,ouch)
	register Font *f;
	register (*ouch)();
{
	register Bitmap *b = f->bits;

	f->n++;
	if(
		nouch(8,f,ouch) ||
		nouch(ISIZE(f->n),f->info,ouch) ||
		nouch(4*f->height*b->width,b->base,ouch)
	)
	{
		f->n--;
		return(-1);
	}
	else
	{
		f->n--;
		return(0);
	}
}

static
nouch(n,s,ouch)
	register n,(*ouch)();
	register char *s;
{
	do {
		if((*ouch)(*s++) == -1)
			return(-1);
	} while (--n > 0);
	return(0);
}
