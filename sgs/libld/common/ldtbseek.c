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
#include	"ldfcn.h"

int
ldtbseek(ldptr)

LDFILE		*ldptr;

{
    extern int		fseek( );

    extern int		vldldptr( );

    if (vldldptr(ldptr) == SUCCESS) {
	if (HEADER(ldptr).f_symptr != 0L) {
	    if (FSEEK(ldptr, HEADER(ldptr).f_symptr, BEGINNING) != -1) {
		return(SUCCESS);
	    }
	}
    }

    return(FAILURE);
}

static char ID[ ] = "@(#) ldtbseek.c: 1.1 1/7/82";
