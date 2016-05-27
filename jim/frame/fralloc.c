/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)fralloc.c	1.2);
#include "frame.h"
Frame *
fralloc(r, m)
	Rectangle r;
{
	register Frame *t=(Frame *)alloc(sizeof(Frame));
	if(t){
		strzero(&t->str);
		t->margin=m;
		frsetrects(t, r);
	}
	return t;
}
frsetrects(f, r)
	register Frame *f;
	Rectangle r;
{
	f->totalrect=r;
	f->rect=inset(r, f->margin);
	f->rect.corner.y-=(f->rect.corner.y-f->rect.origin.y)%newlnsz;
	f->scrollrect=f->rect;
	f->scrollrect.origin.x+=2;
	f->scrollrect.corner.x=f->scrollrect.origin.x+SCROLLWIDTH;
	f->rect.origin.x+=3*SCROLLWIDTH/2;
	f->nlines=(f->rect.corner.y-f->rect.origin.y)/newlnsz;
	setcpl(f, 0, f->nlines-1);
}
frinit(t)
	register Frame *t;
{
	clear(t->totalrect, 1);
	border(P->layer, t->totalrect, t->margin, F_OR);
	strzero(&t->str);
	t->s1=t->s2=0;
	setcpl(t, 0, t->nlines-1);
}
frfree(f)
	register Frame *f;
{
	if(f==0 || f->str.s==0)
		return;
	gcfree(f->str.s);
	free(f);
}

int doubleclickOK;

frselect(f, pt)
	register Frame *f;
	Point pt;
{
	register fix, var, oldvar;
	if(f->s1 != f->s2){
		selectf(f, F_XOR);
		f->nullsel=0;	/* no double clicks this time */
	}
	fix=charofpt(f, pt);	/* fixed point */
	oldvar=fix;		/* moving point tracks mouse */
	var=fix;
	while(bttn1()){
		if(var!=oldvar){
			f->s1=oldvar;
			f->s2=var;
			order(f);
			selectf(f, F_XOR);
			oldvar=var;
		}
		var=charofpt(f, mouse.xy);
	}
	f->s1=fix;
	f->s2=oldvar;
	order(f);
	if(doubleclickOK && f->nullsel && f->s2==f->s1 && f->lastch==f->s1){
		f->nullsel=0;
		matchit(f);
		selectf(f, F_XOR);
		doubleclickOK=0;
	}else{
		doubleclickOK=f->nullsel=f->s2==f->s1;
		f->lastch=f->s1;
	}
}
order(f)
	register Frame *f;
{
	register a;
	if(f->s1 > f->s2){
		a=f->s1;
		f->s1=f->s2;
		f->s2=a;
	}
}
static char ltbrack[]="([{<";		/* sorry, only one match per char */
static char rtbrack[]=")]}>";
static char same[]="\n'`\"";		/* match in either direction */
extern char *index();
matchit(f)
	register Frame *f;
{
	register i,n=0;
	register c;
	register char *s = f->str.s;
	int ch,me,N = f->str.n;
	if (f->s1>0 && (i=index(ltbrack, me=s[f->s1-1])-ltbrack)>=0) {
		ch = rtbrack[i];
		for (i = f->s1; i<N && !((c=s[i])==ch && n==0); i++)
			if (c==me)
				n++;
			else if (c==ch)
				n--;
		if (c==ch && n==0)
			f->s2=i;
	}
	else if (f->s2<N && (i=index(rtbrack, me=s[f->s2])-rtbrack)>=0) {
		ch = ltbrack[i];
		for (i = f->s2-1; i>=0 && !((c=s[i])==ch && n==0); i--)
			if (c==me)
				n++;
			else if (c==ch)
				n--;
		if (c==ch && n==0)
			f->s1=i+1;
	}
	else if ((f->s1==0 && (me='\n')) || (i=index(same, me=s[f->s1-1])-same)>=0) {
		for (i = f->s1; i<N && (c=s[i])!=me; i++)
			;
		if (c==me || (me=='\n' && i==N))
			f->s2=i;
	}
	else if ((f->s2==N && (me='\n')) || (i=index(same, me=s[f->s2])-same)>=0) {
		for (i = f->s2-1; i>0 && (c=s[i])!=me; i--)
			;
		if (c==me)
			f->s1=i+1;
		else if (me=='\n' && i==0)
			f->s1=0;
	}
	else {
		for (i=f->s1; i>0 && isalnum(s[i-1]); i--)
			;
		f->s1=i;
		for (i=f->s2; i<N && isalnum(s[i]); i++)
			;
		f->s2=i;
	}
}

isalnum(c)
register char c;
{
	return (c>='0' && c<='9') ||
		(c>='a' && c<='z') ||
		(c>='A' && c<='Z') ||
		c=='_';
}

clear(r, inh)
	Rectangle r;
{
	if(inh)
		cursinhibit();
	rectf(&display, r, F_CLR);
	if(inh)
		cursallow();
}
border(b, r, i, c)	/* no flashing! */
	register Bitmap *b;
	Rectangle r;
	register i;
	Code c;
{
	rectf(b, Rect(r.origin.x, r.origin.y, r.corner.x, r.origin.y+i), c);
	rectf(b, Rect(r.origin.x, r.corner.y-i, r.corner.x, r.corner.y), c);
	rectf(b, Rect(r.origin.x, r.origin.y+i, r.origin.x+i, r.corner.y-i), c);
	rectf(b, Rect(r.corner.x-i, r.origin.y+i, r.corner.x, r.corner.y-i), c);
}
