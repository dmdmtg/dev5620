/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)getfont.c	2.4);

#include	<dmd.h>
#include	<font.h>
#include	<dmdio.h>

#undef	getc		/* don't want one in vector table! */

/*static*/ FILE *inf;

static
cget()
{
	return(getc(inf));
}

Font *
getfont(s)
	char *s;
{
	Font *f;

	if((inf = fopen(s, "r")) == (FILE *)0)
	{
		return((Font *)0);
	}

	f = infont(cget);
	fclose(inf);
	return(f);
}
