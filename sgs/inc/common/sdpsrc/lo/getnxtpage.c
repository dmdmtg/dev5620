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
/*
 * static char ID_gnxpagc[] = "@(#) getnxtpage.c: 1.1 1/7/82";
 */

long getnxtpage(spacenbr)
int spacenbr;
{
	register long pagenbr;

	pagenbr = global_frames[spacenbr].maxpage;

	if( ++pagenbr == SPSIZE )
		return( (long) fatal("SDP page limit reached") );

	global_frames[spacenbr].maxpage = pagenbr;

	return( pagenbr );
}
