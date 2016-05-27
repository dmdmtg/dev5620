/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)jinit.c	2.4);

#include <jerq.h>
#include <setup.h>
jinit(){
	extern int freeram;
	register long i;

	*DADDR = 0;
	qinit();
	aciainit(baud_speeds[VALBAUD]); 	/* arguement only needed if setup option */
	binit();
	kbdinit();
	cursinit();
	i = (maxaddr[VALMAXADDR] * 2 + (long)(&freeram))/3;	/* split mem 2:1 alloc:gcalloc*/
	allocinit(&freeram, (int *) (i & 0xfffffffc ));	/* make multiple of 4 */
	gcinit();
	spl0();
	sleep(120);	/* wait for 32ld to exit */
}
