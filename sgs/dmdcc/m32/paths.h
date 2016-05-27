/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
HVERSION(paths, @(#)paths.h	2.4);

/*
 *	static char *ID_pathsh = "@(#) paths.h: 1.7 4/24/83";
 * This is a whittled down copy of the official SGS file paths.h.  It
 * has been modified to use DMDSGS and support object deliveries.
 *
 *	Pathnames for m32
 */

/*
 *	Directory for "temp"  files
 */
#define TMPDIR	"/tmp"


/*
 *	The following pathnames will be used by the "cc" command
 *
 *	m32 cross compiler
 */
#define CPP	"/lib/cpp"
/*
 *	Directory containing include ("header") files for users' use
 */
#ifdef u3b5
#define COMP	"/lib/comp"
#else
#define COMP	"/lib/comp"
#endif
#ifdef u3b5
#define OPTIM	"/lib/optim"
#else
#define OPTIM	"/lib/optim"
#endif
/*
 *	m32 cross assembler
 */
#define M4	"/usr/bin/m4"			/* macro preprocessor */
/*
 *	m32 link editor
 */

#define AS	"/bin/m32as"
#define LD	"/bin/m32ld"

