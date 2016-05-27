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
 * static char ID_instrh[] = "@(#) instr.h: 1.2 2/27/84";
 */

#if PERF_DATA
extern long	SDP_read, SDP_write,
		LD_lock, LD_unlock;

extern long	nwalks, nfwalks, ncolisns, maxchain;

extern long	allocspc;

extern long ttime;
extern struct tbuffer {
	long proc_user_time;
	long proc_system_time;
	long child_user_time;
	long child_system_time;
	} ptimes;
#endif
