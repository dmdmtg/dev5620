/* */
/*									*/
/*	Copyright (c) 1987,1988,1989,1990,1991,1992   AT&T		*/
/*			All Rights Reserved				*/
/*									*/
/*	  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T.		*/
/*	    The copyright notice above does not evidence any		*/
/*	   actual or intended publication of such source code.		*/
/*									*/
/* */
static char ID[] = "@(#) switch.c: 1.1 3/16/82";
#include "sdp.h"
#include "define3.h"


int
rem_frame(environ,frame)
struct ENVIRON *environ ;
int frame ;
{
	register struct MANAGER	*manager ;

	manager = environ->manp ;
	manager[manager[frame].backward].forward = manager[frame].forward ;
	manager[manager[frame].forward].backward = manager[frame].backward ;
	manager[frame].forward = manager[frame].backward = END ;
	return(frame) ;
}

ins_frame(environ,frame,position)
struct ENVIRON *environ ;
int frame, position ;
{
	register struct MANAGER	*manager ;

	manager = environ->manp ;
	manager[manager[position].backward].forward = frame ;
	manager[frame].backward = manager[position].backward ;
	manager[position].backward = frame ;
	manager[frame].forward = position ;
	return ;
}
