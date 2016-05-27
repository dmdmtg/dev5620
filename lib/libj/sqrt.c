/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)sqrt.c	2.3);

#define MAXROOT 0xb504
sqrt(x)
        register long x;
{
        register long high = MAXROOT;
        register long low=0;
        register long current = MAXROOT/2;

        if(x<=0)
                return 0;
        if (x >= MAXROOT * MAXROOT)
                return(MAXROOT);
        
        while (high > low + 1)
        {
                if (current * current == x)
                        return (current);
                if (current * current > x)
                {
                        high = current;
                }
                else
                {
                        low = current;
                }
                current = (high + low)>>1;
        }
        return (current);
}
