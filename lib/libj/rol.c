/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)rol.c	2.3);


/*    text
 *    global rol
 *    rol:
 *      mov.w   4(%sp), %d0
 *      mov.w   6(%sp), %d1
 *      rol.w   %d1, %d0
 *      rts
 *    
 *    global ror
 *    ror:
 *      mov.w   4(%sp), %d0
 *      mov.w   6(%sp), %d1
 *      ror.w   %d1, %d0
 *      rts
 */
rol(rodata,sftcnt)
int rodata,sftcnt;
{
        sftcnt %= (8 * sizeof(int));
        return((rodata<<sftcnt)|(rodata>>((8 * sizeof(int))-sftcnt)));
}
ror(rodata,sftcnt)
int rodata,sftcnt;
{
        sftcnt %= (8 * sizeof(int));
        return((rodata>>sftcnt)|(rodata<<((8 * sizeof(int))-sftcnt)));
}
