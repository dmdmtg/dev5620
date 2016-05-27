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
 * static char ID_codouth[] = "@(#) codeout.h: 1.5 11/11/83";
 */

#if ONEPROC
#define TBUFSIZE 512
#else
#define TBUFSIZE 10
#endif

typedef struct {
	long cvalue;
#if VAX
	unsigned char caction;
	unsigned char cnbits;
	int cindex;
#else
	unsigned short caction;
	unsigned short cindex;
	unsigned short cnbits;
#endif
} codebuf;

typedef struct symentag {
	long stindex;
	long fcnlen;
	long fwdindex;
	struct symentag *stnext;
} stent;

typedef struct {
	long relval;
	char *relname;
	short reltype;
} prelent;
