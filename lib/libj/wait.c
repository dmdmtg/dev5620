/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)wait.c	2.4);

#include <dmd.h>
#include "queue.h"

#undef own
own()
#define own Sown
{
	register got=MOUSE|SEND|CPU;
	if(KBDQUEUE.c_cc>0)
		got|=KBD;
	if(RCVQUEUE.c_cc>0)
		got|=RCV;
	return got;
}
#undef wait
wait(r)
#define wait Swait
{
	register u;
	do; while((u=(own()&r))==0);
	return u;
}
