/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)menu.c	1.2);
#define Cursswitch()
#include <pandora.h>


/* WARNING: "jim.h" includes "menu.h" which
	changes Texture to Texture16... */

#include "jim.h"
static unsigned char menupos[MAXFILES];
static int nnames=1;		/* 1 for DIAG, initially there */
char	*name[MAXFILES+1];
char	*gnamegen();
Menu generic = {
	0,
	0,
	0,
	gnamegen
};
char *lnames[] = {
	"cut",
	"paste",
	"snarf",
/*	"look",
	"<mux>", */
	0,	/* will be search string */
	0,	/* will be unix string */
	0,
};
Menu locmenu = {
	lnames
};

Rectangle newgetrect();			/* ***** getrect kludge */

keepsearch(which){	/* icky routine */
	static char searchstring[11];
	static char unixstring[11];
	static seenunix=0;
	char *p=searchstring;
	char *cmd=diag->frame->str.s;
	int n=SEARCH;
	if(which==0){	/* search */
		if(lnames[UNIX]==0 && seenunix)
			lnames[UNIX]=unixstring;
	}else{	/* unix */
		if(lnames[UNIX] || (lnames[SEARCH] && !seenunix))
			n=UNIX;
		p=unixstring;
		if(*cmd=='*')
			cmd++;
		seenunix=1;
	}
	movstring(10, cmd, lnames[n]=p);
	p[min(10, diag->frame->str.n)]=0;
}
Text *
textoffile(f)
	register unsigned f;
{
	register Text *t;
	for(t=text; t; t=t->next)
		if(f==t->file)
			break;
	return t;
}
setchar(f, n, c)
	unsigned f;
{
	name[menupos[f]][n]=c;
}
delmenu(f)
	register f;
{
	register m=menupos[f];
	register char *x;
	register i;
	/* don't free it; save needless alloc() thrashing (see insmenu) */
	x=name[m];		/* save the allocated string... */
	for(i=m; i<nnames-1; i++)
		name[i]=name[i+1];
	name[--nnames]=x;	/* ... and put it at the end */
	for(i=1; i<MAXFILES; i++)
		if(menupos[i]>m)
			--menupos[i];
	menupos[f]=0;
}
insmenu(f, s)
	register f;
	register char *s;
{
	register i, m;
	register char **p;
	register char *x;
	for(m=1; m<nnames && strcmp(name[m]+3, s)<0; m++)	/* +3 skips '*  */
		;
	x=name[nnames];		/* a previously allocated string (maybe) */
	for(i=nnames-1; i>=m; i--)
		name[i+1]=name[i];
	for(i=1; i<MAXFILES; i++)
		if(menupos[i]>=m)
			++menupos[i];
	menupos[f]=m;
	p=name+m;
	if((*p=x)==0){
		if((*p=alloc(3+NAMELEN+2))==0)	/* '* name_\0 */
			panic("insmenu");
	}
	strcpy(*p+3, s);
	strcat(*p+3, "\240");	/* 0240 == 0x80|' ' */	
	++nnames;
}
strcmp(s, t)
	register char *s, *t;
{
	while(*s==*t++)
		if(*s==0)
			return 0;
		else
			s++;
	if(*s==0240)
		return -t[-1];
	return *s-t[-1];
}
setname(f, s)
	register f;
	register char *s;
{
	register exists;
	char buf[3];
	if((exists=menupos[f])){	/* assignment = */
		movstring(3, name[menupos[f]], buf);
		delmenu(f);
	}else
		movstring(3, "   ", buf);	
	insmenu(f, s);
	movstring(3, buf, name[menupos[f]]);
}
inittags(f)
{
	if(f)
		movstring(3, "   ", name[menupos[f]]);
}
modified(t, mod)
	register Text *t;
{
	if(t && t!=diag)
		setchar(t->file, PRIME, " '"[mod]);
}
/*ARGSUSED*/
menulocal(t, pt, but)
	register Text *t;
	Point pt;
	int but;
{
	register Frame *f=t->frame;
	String hold;
	int hit=menuhit(&locmenu,2);
	if(t->selecthuge && CUT<=hit && hit<=EXCH){
		mesg("sorry; can't edit huge selection\n", 1);
		buttons(UP);
		return;
	}
	switch(hit) {
	case CUT:
		Send(O_CUT, 0, 0, "");
		cut(t, TRUE, t==diag? diagclr : F_CLR);
		break;
	case PASTE:
		if(snarfbuf.n<=0)
			break;
		if(snarfhuge){
			mesg("sorry; can't paste with huge snarf buffer\n", 1);
			return;
		}
		/*
		 * Because selection of source and dest can
		 * be done in arb. order, must send selection.
		 */
		Send(O_SELECT, f->s1, 2, data2(f->s2-f->s1));
		Send(O_PASTE1, 0, 0, (char *)0);
		cut(t, FALSE, t==diag? diagclr : F_CLR);
		/*
		 * PASTE goes in two parts because cut() can call loadfile();
		 */
		Send(O_PASTE2, 0, 0, (char *)0);
		if(snarfhuge){
			move(t, Pt(0, f->scrolly), B2);
		}else{
			frinsert(f, &snarfbuf, f->s1);
			f->s2=f->s1+snarfbuf.n;
			t->selecthuge=0;
			selectf(f, F_XOR);
		}
		break;
	case SNARF:
		if(f->s2>f->s1){
			Send(O_SNARF, 0, 0, "");
			snarf(&f->str, f->s1, f->s2, &snarfbuf);
		}
		break;
/*
	case EXCH:
		hold.s=0;
		hold.n=hold.size=0;
		getmuxbuf(&hold);
		setmuxbuf(&snarfbuf);
		snarf(&hold, 0, hold.n, &snarfbuf);
		gcfree(hold.s);
		sendsnarf();
		break;
*/
	case -1:
		break;
	default:
		if(worktext){
			/* hit-SEARCH: -2: look for text; 0: prev search; 1: prev unix */
			send(worktext->file, O_SEARCH, hit-SEARCH, 0, (char *)0);
			waitunix(&diagdone);
		}
		break;
	}
}
char *
gnamegen(i){
	static char *gmenu[]={"new", "reshape", "close", "write"};
	if(i<=WRITE)
		return gmenu[i];
	if(i>=nnames+WRITE)
		return 0;
	return name[i-WRITE];	/* DIAG is not in menu */
}
/*ARGSUSED*/
menugeneric(t, pt, but)
	Text *t;
	Point pt;
	int but;
{
	menughit(t, menuhit(&generic, 3), 0);
}
menughit(t, hit, remote)
	Text *t;
	register unsigned hit;
{
	Rectangle r;
	register i;
	if(remote)
		hit=menupos[hit]+WRITE;
	switch(hit){
	case -1:	/* no hit */
		break;
	case NEW:
		/* ask Unix for a file number */
		send(0, O_FILENAME, 0, 0, (char *)0);
		waitunix(&filedone);
		if(filedone>=0){
			hit=filedone;
			goto Get_it;
		}
		break;
	case RESHAPE:
	case CLOSE:
	case WRITE:
		cursswitch(&bullseye);
		buttons(DOWN);
		t=textofpoint(mouse.xy);
		if(!bttn12() && t && t!=diag) switch(hit){
		case WRITE:
			send(t->file, O_WRITE, 0, 0, (char *)0);
			waitunix(&diagdone);
			break;
		case CLOSE:
			send(t->file, O_CLOSE, 0, 0, (char *)0);
			break;
		case RESHAPE:
			buttons(UP);
			if(userrect(&r)){
				if(worktext){
					setchar(worktext->file, STARDOT, '*');
					Rectf(worktext->frame->scrollrect, F_XOR);
				}
				ontop(t);
				Rectf(t->frame->totalrect, F_CLR);
				frsetrects(t->frame, r);
				dodraw(t);
				if(current==worktext)
					current=t;
				if(current==diag)
					curse(t->frame);
				worktext=t;
				setchar(t->file, STARDOT, '.');
			}
			break;
		}
		cursswitch((Texture *)0);
		break;
	default:	/* must be a file; get it */
		hit-=WRITE;	/* reduce to file number */
		for(i=1; i<MAXFILES; i++)
			if(menupos[i]==hit)
				break;
		hit=i;
	Get_it:
		t=textoffile(hit);
		if(t==0){	/* get it */
			if(userrect(&r) == 0){
				buttons(UP);
				return;
			}
			t=txalloc(r);
			t->file=hit;
			workintext(t);
			if(current==diag)
				curse(t->frame);
			setchar(hit, STARDOT, '*');
			seek(t, Pt(0, 0), 0);
		}
		if(current==diag){
			rXOR(diag->frame->rect);
			curse(diag->frame);		/* on */
			curse(worktext->frame);	/* off */
		}
		workintext(t);
		current=t;
		setchar(hit, STARDOT, '.');
		break;
	}
	buttons(UP);	
}
userrect(rp)
	register Rectangle *rp;
{
/*	*rp=getrect();		***** getrect kludge (ugh) */
	*rp=newgetrect();
	if(rp->corner.x && rp->corner.x-rp->origin.x<=1 && rp->corner.y-rp->origin.y<=1)
		*rp=Drect;
	return rectclip(rp, screenrect)
	   && (rp->corner.x-rp->origin.x)>100 && (rp->corner.y-rp->origin.y)>40;
}
extern int move(), seek(), menugeneric(), menulocal(), txselect();
int (*butfunc[3][3])()={
	txselect,	menulocal, menugeneric,
	move,		seek,	 move,
	(int (*)())opnull, (int (*)())opnull,  (int (*)())opnull
};
char whichbut[]={	/* depends on def'n of bttn1(), etc. */
	B1, B3, B2, B2, B1, B1, B1, B1
};
whichrect(t, pt)
	register Text *t;
	Point pt;
{
	if(ptinrect(pt, t->frame->scrollrect))
		return SCROLLBAR;
	return FRAMERECT;
}
buttonhit(pt, but)
	Point pt;
	register but;
{
	register Text *t=textofpoint(pt);
	but=whichbut[but&7];
	/* icky special case to make scroll bar always active */
	if(t && t==worktext && ptinrect(pt, t->frame->scrollrect)){
		if(current!=t)
			curse(t->frame);
		(*(but==B2? seek : move))(t, pt, but);
		if(current!=t)
			curse(t->frame);
	}else if(but==B1 && t!=current){
		if(t==diag || current==diag)
			rXOR(diag->frame->rect);
		/* get the cursor right first */
		if(current==diag || (current==worktext && t==diag)){
			curse(diag->frame);
			curse(worktext->frame);
		}
		if(t==diag)
			diagclr=F_OR;
		else if(t){
			if(t!=worktext)
				workintext(t);
			diagclr=F_CLR;
		}
		current=t;
		buttons(UP);
	}else{
		if(current==0 && but!=B3)
			return;	/* nothing to do */
		(*butfunc[whichrect(current, pt)][but])(current, pt, but); 
	}
}

#ifdef OLDSOFTWARE
#define scale(x, inmin, inmax, outmin, outmax)\
	(outmin + muldiv(x-inmin,outmax-outmin,inmax-inmin))

#define bound(x, low, high) min(high, max( low, x ))

#define SPACING		14
#define DISPLAY		16
#define CHARWIDTH	9
#define DELTA		6
#define BARWIDTH	18

static char **table;
static char *
tablegen(i)
{
	return table[i];
}

static Bitmap screen;

menuhit(m, but)
register Menu *m;
{
	register int width, i, j, top, newtop, hit, newhit, items, lines, length;
	Point p, q, savep, baro, barc;
	Rectangle sr, tr, mr;	/* scroll, text, menu */
	register Bitmap *b;
	register char *s, *(*generator)(), *from, *to, fill[64];

#define sro sr.origin
#define src sr.corner
#define tro tr.origin
#define trc tr.corner
#define mro mr.origin
#define mrc mr.corner

	screen.base=addr(&display, Pt(0, 0));
	screen.width=XMAX/WORDSIZE;
	screen.rect=Jrect;

	generator = (table=m->item) ? tablegen : m->generator;
	p = mouse.xy;
	for(length = items = 0; s=(*generator)(items); ++items)
		length = max(length, strlen(s));
	if(items == 0){
		while(bttn(but));
		return -1;
	}
	width = length*CHARWIDTH+10;
	sro.x = sro.y = src.x = tro.x = mro.x = mro.y = 0;
	if(items <= DISPLAY)
		lines = items;
	else{
		lines = DISPLAY;
		tro.x = src.x = BARWIDTH;
		sro.x = sro.y = 1;
	}
#define ASCEND 2
	tro.y = ASCEND;
	mrc = trc = add(tro, Pt(width, min(items, lines)*SPACING));
	src.y = mrc.y-1;
	newtop = bound(m->prevtop, 0, items-lines);
	p.y -= bound(m->prevhit, 0, lines-1)*SPACING+SPACING/2;
	p.x = bound(p.x-(src.x+width/2), 0, XMAX-mrc.x);
	p.y = bound(p.y, 0, YMAX-mrc.y);
	sr = raddp(sr, p);
	tr = raddp(tr, p);
	mr = raddp(mr, p);
	b = balloc(mr);
	cursinhibit();
	if(b)
		bitblt(&screen, mr, b, mro, F_STORE);
	rectf(&screen, mr, F_OR);
	cursallow();
PaintMenu:
	cursinhibit();
	rectf(&screen, inset(mr, 1), F_CLR);
	cursallow();
	top = newtop;
	if(items > DISPLAY){
		baro.y = scale(top, 0, items, sro.y, src.y);
		baro.x = sr.origin.x;
		barc.y = scale(top+DISPLAY, 0, items, sro.y, src.y);
		barc.x = sr.corner.x;
		rectf(&screen, Rpt(baro,barc), F_XOR);
	}
	for(p=tro, i=top; i < min(top+lines, items); ++i){
		q = p;
		from = generator(i);
		for(to = &fill[0]; *from; ++from)
			if(*from & 0x80)
				for(j=length-(strlen(from+1)+(to-&fill[0])); j-->0;)
					*to++ = *from & 0x7F;
			else
				*to++ = *from;
		*to = '\0';
		q.x += (width-jstrwidth(fill))/2;
		string(&defont, fill, &screen, q, F_XOR);
		p.y += SPACING;
	}
	savep = mouse.xy;
	for(newhit = hit = -1; bttn(but); nap(2)){
		if(ptinrect(p = mouse.xy, sr)){
			if(ptinrect(savep,tr)){
				p.y = (baro.y+barc.y)/2;
				cursset(p);
			}
			newtop = scale(p.y, sro.y, src.y, 0, items);
			newtop = bound(newtop-DISPLAY/2, 0, items-DISPLAY);
			if(newtop != top)
/* ->->-> */			goto PaintMenu;
		}else if(ptinrect(savep,sr)){
			register dx, dy;
			if(abs(dx = p.x-savep.x) < DELTA)
				dx = 0;
			if(abs(dy = p.y-savep.y) < DELTA)
				dy = 0;
			if(abs(dy) >= abs(dx))
				dx = 0;
			else
				dy = 0;
			cursset(p = add(savep, Pt(dx,dy)));
		}
		savep = p;
		newhit = -1;
		if(ptinrect(p, tr)){
			newhit = bound((p.y-tro.y)/SPACING, 0, lines-1);
			if(newhit!=hit && hit>=0
			 && abs(tro.y+SPACING*newhit+SPACING/2-p.y) > SPACING/3)
				newhit = hit;
		}
		if(newhit != hit){
			flip(tr, hit);
			flip(tr, hit = newhit);
		}
		if(newhit==0 && top>0){
			newtop = top-1;
			p.y += SPACING;
			cursset(p);
/* ->->-> */		goto PaintMenu;
		}
		if(newhit==DISPLAY-1 && top<items-lines){
			newtop = top+1;
			p.y -= SPACING;
			cursset(p);
/* ->->-> */		goto PaintMenu;
		}
	}
	if(b){
		cursinhibit();
		screenswap(b, b->rect, b->rect);
		cursallow();
		bfree(b);
	}
	if(hit>=0){
		m->prevhit = hit;
		m->prevtop = top;
		return hit+top;
	}else
		return -1;
}

static
flip(r,n)
	Rectangle r;
{
	if(n<0)
		return;
	++r.origin.x;
	r.corner.y = (r.origin.y += SPACING*n-1) + SPACING;
	--r.corner.x;
	rectf(&screen, r, F_XOR);
}

#undef canon
Rectangle
canon(p1, p2)
	Point p1, p2;
{
	Rectangle r;
	r.origin.x = min(p1.x, p2.x);
	r.origin.y = min(p1.y, p2.y);
	r.corner.x = max(p1.x, p2.x);
	r.corner.y = max(p1.y, p2.y);
	return(r);
}
Point
jline(p, dp)
	Point p, dp;
{
	dp.x+=p.x;
	dp.y+=p.y;
	segment(&display, p, dp, F_XOR);
	return dp;
}
#undef outline
outline(r)
	Rectangle  r;
{
	register dx=r.corner.x-r.origin.x-1, dy=r.corner.y-r.origin.y-1;
	Point p;
	p=jline(r.origin, Pt(dx, 0));
	p=jline(p, Pt(0, dy));
	p=jline(p, Pt(-dx,0));
	(void)jline(p, Pt(0,-dy));
}
#endif

/***** kludge to change getrect to return more info */
static Texture boxcurs = {
	0x43FF, 0xE001, 0x7001, 0x3801, 0x1D01, 0x0F01, 0x8701, 0x8F01,
	0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0xFFFF,
};

/* if I use the FW bttns(), it looks at the global mouse structure,
	not my udata... */
#undef bttns
bttns(updown) 
{
	do; 
	while ((bttn123() != 0) != updown)
		;
}


/*#undef getrect*/
Rectangle
newgetrect(){
	Rectangle r;
	Point p1, p2;
	Texture *oldcurs = Cursswitch(&boxcurs);
	bttns(UP);
	bttns(DOWN);
	if(!bttn3()){
		r.origin.x=r.origin.y=r.corner.x=r.corner.y=0;
		bttns(UP);
		goto Return;
	}
	p1=mouse.xy;
	p2=p1;
	r=canon(p1, p2);
	outline(r);
	for(; bttn3(); nap(3)){
		outline(r);
		p2=mouse.xy;
		r=canon(p1, p2);
		outline(r);
	}
	outline(r);	/* undraw for the last time */
    Return:
	Cursswitch(oldcurs);
	return r;
}
/***** end of kludge to change getrect to return more info */

