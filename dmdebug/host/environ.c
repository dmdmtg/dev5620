/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)environ.c	2.2);
*/


#include "common.h"
#include <signal.h>
#include <sgtty.h>

/*#include <sys/ioctl.h>*/

static struct sgttyb savetty;
static struct sgttyb worktty;
static int donesetty = 0;

#define SENDTERMID "\033[c"
#define TERM_DMD "\033[?8;7;"
#define TERMIDSIZE 9


wrap( clean ){
	if( !oflag ) jerqdo( DO_WRAP );
	resettty();
	if( clean > 0 )
		abort();
	else
		exit( clean );
}

static char stdoutbuf[BUFSIZ];

settty()
{
	if( signal( SIGINT, SIG_IGN ) != SIG_IGN ) signal( SIGINT, wrap );
	if( ioctl( 1, TIOCGETP, &savetty ) == -1 ){
		printf("ioctl received error on TIOCGETP\n");
		wrap( -1 );
	}
	worktty = savetty;
	worktty.sg_flags = RAW | ANYP;
	tcseta( &worktty );
	if( !oflag ){
		 setbuf( stdout, stdoutbuf );
	}
	donesetty = 1;
}

tcseta( t )
struct sgttyb *t;
{
	int rc;

	rc = ioctl( 1, TIOCSETP, t );
	if( rc == -1 ){
		printf("ioctl received error on TIOCSETP\n");
		wrap( -1 );
	}
}


resettty()
{
	if( donesetty )
		tcseta( &savetty );
	donesetty = 0;
}

getromid( buf )
char	*buf;
{
	int cnt, nr;

	write( 1, SENDTERMID, 3);

	cnt = 0;
	while (cnt < TERMIDSIZE){
		nr = read( 0, buf+cnt, TERMIDSIZE-cnt );
		if(nr > 0)
			cnt += nr;
	}
}
