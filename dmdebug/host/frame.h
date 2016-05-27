/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
HVERSION(frame,@(#)frame.h	2.4);
*/

struct frame {
	MLONG		fp;
	MLONG		ap;
	MLONG		pc;
	MLONG		function;
	MLONG		regsave;
	char		*fname;
	struct ramnl	*sline;
	char		*so;
	struct ramnl	*bfun;
	struct frame	*caller;
	struct frame	*callee;
	int		visible;
};

struct frame *framechain();
extern	struct frame *train;
extern	struct frame sentinel;
extern	MLONG	ptregsave;

#define REGS_CONTEXT 1
#define LINE_CONTEXT 2
#define AUTO_CONTEXT 4
#define FULL_CONTEXT (AUTO_CONTEXT|REGS_CONTEXT|LINE_CONTEXT)

#define VERBOSE_CHAIN 1
#define MPX_CHAIN  2
#define FULL_CHAIN 4
