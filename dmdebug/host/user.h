/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
HVERSION(user,@(#)user.h	2.3);
*/


#include "stab.h"

#define BYTEDOT   1
#define	SHORTDOT  2
#define	LONGDOT   3
#define	INSTDOT   4
#define	STRUCTDOT 5
#define	ENUMDOT   6
#define	STRINGDOT 7

#define PLUSONE  8
#define MINUSONE 9
#define INDIRECT 10
#define XREF	 11
#define DECIMAL	 12
#define HEX	 13
#define OCTAL	 14
#define ASCII	 15
#define SNARF	 16
#define DOTOPS	 16


extern	int	dotty;
extern	long	dot;
extern	int	dotfmt;
extern	int	radix;
extern	long	snarfdot;
extern	int	snarfdotty;
extern	int	dotstrlen;

extern	struct ramnl dotstab[2];

extern	char 	userline[128];
extern	int 	lexindex;
