/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)norm.c	2.3);

norm(x,y,z)
{
	return (sqrt(x*x + y*y + z*z));
}

sqrtryz(x,y,z)
{
	register long sumsq;

	sumsq = x*x - y*y - z*z;
	if (sumsq <= 0)
		return 0;
	return ( sqrt(sumsq) );
}
