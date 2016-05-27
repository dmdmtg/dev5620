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
/* #ident	"@(#)pkg.ccs:archtst.c	1.1" */
#
#include	<stdio.h>
main()
/*
 *	Test the byte ordering characteristic of this machine.
 *	Output is a single word to standard output.
 *
 *	AR32W - 32 bit machine, with the loworder byte being the
 *	most significant. 3B and MC68K is of this type.
 *
 *	AR32WR - 32 bit machine, with the loworder byte being the
 *	least significant. VAX is of this type.
 *
 *	AR16WR - 16 bit machine, where 32 bit entities are stored as
 *	two 16 bit words with the low order byte being first in each
 *	word, but the first word being the most significant.
 *	pdp11 is of this type.
 */
{
	union {
		long l;
		char c[4];
	} ar32w, ar32wr, ar16wr;

	if (sizeof(ar32w.l) != sizeof(ar32w.c)) {
		fprintf(stderr, "Long is not 4 characters!\n");
		exit(1);
	}
	strncpy(ar32w.c, "\01\02\03\04", 4);
	strncpy(ar32wr.c, "\04\03\02\01", 4);
	strncpy(ar16wr.c, "\02\01\04\03", 4);
	if (0x01020304L == ar32w.l) printf("FBO");
	else if (0x01020304L == ar32wr.l) printf("RBO");
	else if (0x01020304L == ar16wr.l) printf("RBO");
	else {
		fprintf(stderr, "Too strange byte order!\n");
		exit(2);
	}
	return 0;
}
