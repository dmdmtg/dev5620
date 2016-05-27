/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)atan2.c	2.3);

static qatan2();
atan2(xx, yy){
	register x, y;
	x=abs(xx);
	y=abs(yy);
	if(xx>=0 && yy>=0)
		return(qatan2(x, y));
	if(xx<0 && yy<0)
		return(180+qatan2(x, y));
	if(xx<0 && yy>0)
		return(180-qatan2(x, y));
	return(360-qatan2(x, y));
}
static
qatan2(x, y)
	register x, y;
{
	if(x<y)
		return(90-(45*((long)x)/y));
	if(y==0)
		return(0);
	return(45*((long)y)/x);
}
