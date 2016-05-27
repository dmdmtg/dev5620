/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
HVERSION(aout,@(#)a.out.h	2.3);
*/


#define	N_UNDF	0
#define	N_ABS	02
#define	N_TEXT	04
#define	N_DATA	06
#define	N_BSS	010
#define N_CTEXT	012
#define N_RDATA	014
#define N_COMM	016
#define	N_EXT	01	/* external bit, or'ed in */
#define N_TYPE	036
#define N_FN	036
#define N_MORE	040
#define N_REG	0100	/* place holder of some sort */
#define	X2WDS	020	/* long (2-word) quantity */
