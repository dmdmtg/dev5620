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
#include	<stdio.h>
#include	"filehdr.h"
#include	"scnhdr.h"
#include	"ldfcn.h"

int
ldnlseek(ldptr, sectname)

LDFILE	*ldptr;
char 	*sectname; 

{
	extern	int	ldnshread( );
	extern	int	fseek( );

	SCNHDR	shdr;

	if (ldnshread(ldptr, sectname, &shdr) == SUCCESS) {
		if (shdr.s_nlnno != 0) {
		    if (FSEEK(ldptr, shdr.s_lnnoptr, BEGINNING) != -1) {
			    return(SUCCESS);
		    }
		}
	}

	return(FAILURE);
}

static char ID[ ] = "@(#) ldnlseek.c: 1.1 1/7/82";
