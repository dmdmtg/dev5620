/* */
/*									*/
/*	Copyright (c) 1987,1988,1989,1990,1991,1992   AT&T		*/
/*			All Rights Reserved				*/
/*									*/
/*	  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T.		*/
/*	    The copyright notice above does not evidence any		*/
/*	   actual or intended publication of such source code.		*/
/*									*/
/* */
static char ID[] = "@(#) fatal.c: 1.1 3/16/82";
#include <stdio.h>
#include "sdp.h"

char	*llaerrfile = "stderr" ;
int	mesg_flag = MESGON ;

FATAL(msg,v1,v2,v3,v4,v5,v6,v7)
char	*msg ;
int	v1 ;
int	v2 ;
int	v3 ;
int	v4 ;
int	v5 ;
int	v6 ;
int	v7 ;
{
	static FILE	*fp = NULL ;

	if (fp == NULL){
		if(strcmp(llaerrfile,"stderr") == 0)
			fp = stderr ;
		else if( (fp = fopen(llaerrfile,"w")) == NULL )
			exit(-2) ;
	}else{
		if(mesg_flag == MESGON)
			fprintf(fp,msg,v1,v2,v3,v4,v5,v6,v7) ;
	}
}
