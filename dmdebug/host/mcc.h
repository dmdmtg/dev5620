/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
HVERSION(mcc,@(#)mcc.h	2.4);
*/


#define TNULL PTR      /* pointer to UNDEF */
#define TVOID FTN	/* function returning UNDEF (for void) */
#define UNDEF		0
#define VOID		0
#define FARG		1
#define CHAR		2
#define SHORT		3
#define INT		4
#define LONG		5
#define FLOAT		6
#define DOUBLE		7
#define STRTY		8
#define UNIONTY	9
#define ENUMTY		10
#define MOETY		11
#define UCHAR		12
#define USHORT		13
#define UNSIGNED	14
#define ULONG		15

#define ASG 1+
#define UNARY 2+
#define NOASG (-1)+
#define NOUNARY (-2)+

#define PTR  0020		/* changed to be compatible with coff */
#define FTN  0040		/* changed to be compatible with coff */
#define ARY  0060		/* changed to be compatible with coff */

#define BTMASK 017		/* changed to be compatible with coff */
#define BTSHIFT 4		/* changed to be compatible with coff */
#define TSHIFT 2
#define C_TMASK 060	/* changed to be compatible with coff */
#define ISPTR(x) ((x&C_TMASK)==PTR)
#define ISFTN(x)  ((x&C_TMASK)==FTN)  /* is x a function type */
#define ISARY(x)   ((x&C_TMASK)==ARY)   /* is x an array type */
#define INCREF(x) (((x&~BTMASK)<<TSHIFT)|PTR|(x&BTMASK))
#define DECREF(x) (((x>>TSHIFT)&~BTMASK)|(x&BTMASK))

