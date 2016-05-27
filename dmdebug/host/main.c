/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)main.c	2.5);
*/

#include "common.h"
#include "stab.h"
#include <signal.h>
#include <sys/jioctl.h>
#include <sys/wait.h>

int oflag, hatebs;
int sccsflg = 0;

struct stable userstab;
struct stable mpxstab;
struct stable *stabtab[4] = { NULL, &userstab, &mpxstab, NULL};

char deftsyms[80] = ""; /* default symbols overide target command line*/

#define TERMIDSIZE 9
static	char termid[TERMIDSIZE+1];


main( argc, argv)
char *argv[];
{
	int	i;
	char	download[256], loader[256];
	char	*node;		/* base of DMD structure*/
	extern	char *getenv();
#ifdef USE_SYSV_WAIT
	int	status;
#else
	union wait status;
#endif
	int	w, pid;
	int	c;
	extern	char *optarg;
	extern	int optind;
	extern	int opterr;

#define argstr() ( argv[i][2] ? &argv[i][2] : argv[++i] )

#ifdef USE_HOSTAGENT
	if (!inlayers()) {
#else
	if(ioctl(1, JMPX, 0) == -1) {
#endif
		fprintf(stderr,"%s - error - %s runs only under layers\n",
			argv[0],argv[0]);
		exit( -1 );
	}
	if (((node = getenv("DMD")) == (char *)0) || (*node == '\0'))
		node = DMD;

	settty();

	strcpy(download,node);
	strcat(download,"/lib/dmdebug.m");
	strcpy(loader,node);
	strcat(loader,"/bin/32ld");

	stabtab[USER]->name = "user";
	stabtab[MPX]->name = "mpx";
	stabtab[USER]->magic = MAGREL;
	stabtab[MPX]->magic = MAGABS;
	stabtab[MPX]->rom = LO_ROM;
	strcpy( stabtab[USER]->path, "dmda.out" );
	strcpy( stabtab[MPX]->path, node);
	strcat( stabtab[MPX]->path, "/lib/layersys/lsym.");

	/* Get rom version */

	getromid( termid );
	strncat( stabtab[MPX]->path, &termid[3], 5);

	/* read and interpret the arguments */

	opterr = 1;
	while( (c = getopt( argc, argv, "l:t:m:u:s")) != EOF){
		switch( c ){
		case 'l':  strcpy( loader, optarg);		break;
		case 't':  strcpy( download, optarg);		break;
		case 'm':  strcpy( stabtab[MPX]->path, optarg);	break;
		case 'u':  strcpy( deftsyms, optarg);		break;
		case 's':  sccsflg = 1;				break;
		case '?':  useerr();
		}
	}

	if( access( stabtab[MPX]->path, 4) == -1 ){
		fprintf(stderr,"error opening file: '%s'\n",stabtab[MPX]->path);
		fprintf(stderr, "5620 Software - Firmware mismatch:  See the Compatibility\n\r");
		fprintf(stderr, "Chart supplied with the Terminal Owner's Manual\n\r");
		fprintf(stderr, "(or in the 5620 Application Development System Release Description)\n\r");
		fprintf(stderr, " for instructions on how to proceed.\n\r");
		wrap( -1 );
	}

	/* download the terminal JOFF */

	if( (pid = vfork()) == 0 ) {
		(void) execl("/bin/sh", "sh", "-c",
			fmt ("%s %s", loader, download), 0);
		_exit(127);
	}

	m_init();

	while((w = wait(&status)) != pid && w != -1)
		;
	if( w == -1 || 
#ifdef USE_SYSV_WAIT
			status != 0)
#else
			status.w_status != 0)
#endif
		wrap( -1 );

	joff();
	return(1);
}

useerr()
{ 
	fprintf( stderr,
	"use: dmdebug [-u symbols] [-m layersys] [-t dmdebug.m] [-l 32ld] \n");
	wrap( -1 );
}
