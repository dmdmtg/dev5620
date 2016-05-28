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
#include    <stdio.h>
#include    "filehdr.h"
#include    "ldfcn.h"

int
ldfhread(ldptr, filehead)

LDFILE    *ldptr;
FILHDR    *filehead; 

{
    extern int		vldldptr( );

    if (vldldptr(ldptr) == SUCCESS) {
	if (FSEEK(ldptr, 0L, BEGINNING) != -1) {
	    if (FREAD(filehead, FILHSZ, 1, ldptr) == 1) {
	    	return(SUCCESS);
	    }
	}
    }

    return(FAILURE);
}

static char ID[ ] = "@(#) ldfhread.c: 1.1 1/7/82";
