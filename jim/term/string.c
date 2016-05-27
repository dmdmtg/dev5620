/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)string.c	1.2);
#include "../frame/frame.h"

#define	MAXROOM	1024	/* maximum extra number of chars after strinsure() */

char *
GCalloc(n, p)
	int n;
	char **p;
{
	while(gcalloc((unsigned long)n, p)==0){
		mesg("out of memory; clean up bitmaps and hit a button\n");
		for(;;){
			sleep(30);
			wait(MOUSE);
			if(bttn123())
				break;
		}
		mesg("trying again\n", TRUE);
	}
}
strinsure(p, n)
	register String *p;
	register short n;
{
	register i;
	char *old;
	if (p->size < n) {	/* p needs to grow */
		for (i = 1; i < n; i <<= 1)
			;
		if(i > n+MAXROOM)
			i = n+MAXROOM;
		if(p->s==0)
			old=0;
		else{
			GCalloc(p->n, &old);
			movstring(p->n, p->s, old);
			gcfree(p->s);
		}
		GCalloc(i, &p->s);
		if(old){
			movstring(p->n, old, p->s);
			gcfree(old);
		}
		p->size = i;
	}
}
#define	MINCHARS 64	/* for efficiency; min size of a string we'll alloc */
strzero(p)
	String *p;
{
	if(p->s && p->size>MINCHARS){
		p->n=0;
		p->size=0;	/* forces strinsure to free the old stuff */
	}
	strinsure(p, MINCHARS);
	p->n = 0;
}
straddc(p, c)
	register String *p;
	char c;
{
	strinsure(p, p->n+1);
	p->s[p->n++] = c;
}
snarf(p, i, j, q)
	register String *p, *q;
	register short i, j;
{
	register n=j-i;
	strinsure(q, n);
	movstring(n, p->s+i, q->s);
	q->n=n;
}
strinsert(p, i, q)
	register String *p, *q;
	register short i;
{
	strinsure(p, p->n+q->n);
	movstring(i-p->n, p->s+p->n, p->s+p->n+q->n);
	movstring(q->n, q->s, p->s+i);
	p->n += q->n;
}
strdelete(p, i, j)
	register String *p;
	register short i, j;
{
	register n = j-i;
	movstring(p->n-j, p->s+j, p->s+i);
	p->n -= n;
}
movstring(i, s, d)
	register short i;
	register char *s, *d;
{
	if (i > 0)
		do
			*d++ = *s++;
		while (--i > 0);
	else {
		if (i++ < 0)		/* transfer -i chars in loop */
			do
				*--d = *--s;
			while (i++ < 0);
	}
}

getmuxbuf(s)
	register String *s;
{
}

setmuxbuf(s)
	String *s;
{
}
