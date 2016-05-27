/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
HVERSION(stab,@(#)stab.h	2.3);
*/

#include <sys/types.h>
#include <sys/stat.h>
#include "a.out.h"
#include "mcc.h"
#include "sdb.h"
#include "names.h"

#include "newa.out.h"

struct ramnl {
	char		*n_name;
	char		n_type;
	char		n_other;
	unsigned short 	n_desc;
	long		n_value;
	struct ramnl	*n_thread;
};

struct stable{
	char		*name;		/* Should never change */
	long		magic;		/* Expected magic - need not be */
	long		rom;

	char		path[128];	/* Changes */
	struct ramnl	*base;
	struct ramnl	*index;
	int		size;
	struct ramnl	*threader[0x100];
	struct ramnl	*tmpthread[0x100];
	struct	filehdr fheader;
	struct	aouthdr	aheader;
	long		proc;
	long		text;
	long		data;
	long		bss;
	time_t		mtime;
	int		fd;
	char		*strtab;
	long		strtaboff;
	long		strtabsz;
};

struct ramnl *lookup(), *visible(), *fileline(), *sline1();


#define MAGREL 0406
#define MAGABS 0407

#define II( a,b )			( a | (  b << 8 ) )
#define III( a,b,c )			( a | ( II( b,c ) << 8 ) )
#define IV( a,b,c,d )			( a | ( III( b,c,d ) << 8 ) )

#define S_shift( x ) ( S_MAX + (x) )

#define S_ETEXT S_shift( N_TEXT|N_EXT )
#define S_EDATA S_shift( N_DATA|N_EXT )
#define S_EBSS  S_shift( N_BSS|N_EXT )
#define S_EABS  S_shift( N_ABS|N_EXT )


#define S_TEXT S_shift( N_TEXT )
#define S_DATA S_shift( N_DATA )
#define S_BSS  S_shift( N_BSS )

#define LDE IV( S_EBSS, S_ETEXT, S_EDATA, S_EABS )
#define LDL III( S_TEXT, S_DATA, S_BSS )

#define USER        1
#define MPX         2
#define USER_MPX    II( USER, MPX )

#define INTERACT 1

extern	struct stable *stabtab[4];

int fstat();
