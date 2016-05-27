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
 * static char ID_dlstc[] = "@(#) delist.c: 1.1 1/7/82";
 */

delist(framenbr)
int framenbr;
{

	register int partnbr;

	partnbr = manager[framenbr].partition;

	if( num_linked[partnbr] == 0 )
		return( fatal("no free frames in partition") );

	if( manager[framenbr].forward == INVALID )
		return( fatal("attempt to unlink an unlinked frame") );

	if( num_linked[partnbr] == 1 )
		lru[partnbr] = mru[partnbr] = NOFRAMES;
	else if( framenbr == lru[partnbr] ) {
		lru[partnbr] = manager[lru[partnbr]].forward;
		manager[lru[partnbr]].backward = LAMDA;
		}
	else if( framenbr == mru[partnbr] ) {
		mru[partnbr] = manager[mru[partnbr]].backward;
		manager[mru[partnbr]].forward = LAMDA;
		}
	else {
		manager[manager[framenbr].backward].forward = 
			manager[framenbr].forward;
		manager[manager[framenbr].forward].backward =
			manager[framenbr].backward;
		}

	manager[framenbr].forward  = INVALID;
	manager[framenbr].backward = INVALID;

	num_linked[partnbr]--;

	return(SUCCESS);
}
