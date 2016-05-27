/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
HVERSION(traps,@(#)traps.h	2.3);
*/

#define HALTED  1
#define ACTIVE  2
#define TRAPPED 3
#define ERRORED 4
#define BREAKPTED 5
#define STEPPED 6

#define BPTS 32		/* < 256 */

#define BPT_TRAP 0x73
#define TRACE_TRAP 0x0b
#define TRAP_BITS ( BPT_TRAP|TRACE_TRAP )
#define	SAVEINST 0x10

#define PSW_TRACE 0x00020000	/* this is the trace enable bit in the psw */

#define ROM 1

#define MAXTRAP 10
