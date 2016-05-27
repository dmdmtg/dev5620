/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)user.c	2.2);
*/

#include "user.h"

int	dotty;
long	dot;
int	dotfmt;
int	radix;
long	snarfdot;
int	snarfdotty;
int	dotstrlen;

struct ramnl dotstab[2];

char 	userline[128];
int 	lexindex;
