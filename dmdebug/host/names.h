/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
HVERSION(names,@(#)names.h	2.3);
*/

extern char * basetypenames[];
extern char * storagenames[];
extern char * regnames[];
extern char * ntypenames[];
extern char * sdbnames[];
extern char * rtrapnames[];
extern char * ptrapnames[];
extern char * strapnames[];
extern char * ntrapnames[];
extern char * hatebsnames[];
extern char * dottynames[];


struct	traptypes {
	char	**tname;
	short	tcnt;
};

extern struct traptypes trapnames[];
