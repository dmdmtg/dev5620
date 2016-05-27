/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
 *	VERSION() is used to identify a C module's sccs id.
 *		(the number in parens is the sccs id of the
 *		"include" component of this delivery).
 *	HVERSION() is now obsolete
 *
 */
#ifdef lint
#define VERSION(x);
#define HVERSION(n,x);
#else
#define VERSION(x) static char _2Vsccsid[]="x(1.98)";
#define HVERSION(n,x);
#endif

/*
 *		NOTE: sccsid.h needs to be admin'd whenever headers
 *		get turned over.  Do this in the pdeliver script
 *		as follows:
 *
 *		su - sccs -c "admin -ft`pprs -d:I: include` include:sccsid.h"
 *
 */
