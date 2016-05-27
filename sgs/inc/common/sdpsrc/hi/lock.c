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
 * static char ID_lckc[] = "@(#) lock.c: 1.1 1/7/82";
 */

char *lock(itemid, partnbr, permissions)
ITEMID itemid;
int    partnbr, permissions;
{

	register int framenbr, spacenbr;

	spacenbr = XTRCTSP(itemid);
	if( open_spacenumbers[spacenbr] != YES )
		return( (char *) fatal("attempt to access unopened address space") );
	if( XTRCTPN(itemid) > global_frames[spacenbr].maxpage )
		return( (char *) fatal("attempt to read unallocated page") );

	LD_lock++;
#if DEBUG
	if( dflag > 15 )
		fprintf( stderr, "  lock %08lx ", itemid );
#endif

	if( (framenbr = sojourn((itemid & ~BYTEMASK), partnbr, YES)) < 0 )
		return( (char *) fatal("unable to obtain frame for item") );

	if( manager[framenbr].lock_count++ == 0 )
		if( delist(framenbr) < 0 )
			return( (char *) fatal("unable to delist frame for item") );

	if( permissions == WRTN )
		manager[framenbr].ref_chng = WRTN;

	return( (char *) (((int) manager[framenbr].frame_pntr) + XTRCTBY(itemid)) );

}
