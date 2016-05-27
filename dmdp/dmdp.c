/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)dmdp.c	2.6);
#include <dmd.h>
#include <setup.h>
#define point2layer
#define reshape
#define Cursswitch
#include <pandora.h>
#define MAINFILE
#include "dmdp.h"
#include "printer.h"

int rm_msg;

Word Icon[] = {
0x0007C000,0x00000000, 0x00083000,0x00000000,
0x00100C00,0x00000000, 0x00200200,0x00000000,
0x00400101,0x80000000, 0x00800083,0xC0000000,
0x01000046,0x60000000, 0x0200002C,0x30000000,
0x04000418,0x18000000, 0x08000408,0x0C000000,
0x10000404,0x06000000, 0x20001C02,0x03400000,
0x40001011,0x11A00000, 0xF8101028,0x88C00000,
0x06087040,0x44600000, 0x019440A0,0x22300000,
0x00424100,0x12180000, 0x00250280,0x0C0C0000,
0x00108409,0x08060000, 0x00094A12,0x10030000,
0x00043024,0x20038000, 0x00024848,0x40078000,
0x00070090,0x800D8000, 0x000C8021,0x00198000,
0x00184042,0x00318000, 0x00302084,0x00618000,
0x00701008,0x00C98000, 0x00780810,0x019D8000,
0x006C0420,0x03098000, 0x00662240,0x06030000,
0x00631180,0x0C060000, 0x00618900,0x188C0000,
0x0060C600,0x30180000, 0x00606000,0x62300000,
0x00603000,0xC0600000, 0x00309801,0x88C00000,
0x0019CC03,0x01800000, 0x000C8606,0x03000000,
0x0006030C,0x86000000, 0x00030198,0x8C000000,
0x000180F0,0x98000000, 0x0000C064,0x30000000,
0x00006064,0x60000000, 0x00003064,0xC0000000,
0x00001861,0x80000000, 0x00000C63,0x00000000,
0x00000666,0x00000000, 0x0000036C,0x00000000,
0x000001F8,0x00000000, 0x000000F0,0x00000000,
};

Bitmap pmap = {
	Icon,
	2,
	0, 0, 49, 50
};

main(argc, argv)
int argc;
char *argv[];
{
	register struct Printers *rPr;
	register int pollret;
	register int prntnum;
	register int i;
	register int *rstate;

#ifdef DEBUG
	Delay = 0;
	debugflg = 0;
#endif

	if(VALPPRNT == 3) Sop = 1; /* look in bram to see if send only port */
	   else Sop = 0;

	Sop8bits = 0;

	prntnum = argv[1][0] & 0xF;  /* atoi - max of 9 drivers */

	if(prntnum != 0) {  /* transparent is always number 0 */
		Transparent = 0;

		Pr = rPr = &Printers[prntnum-1];

		Center = 1;
		Docopy = 0;
		Hdpi = rPr->hdpiinit;
		Vdpi = rPr->vdpiinit;
		Prntquality = rPr->qualinit;
		Paperwidth = rPr->paperinit;

		Prntwidth = (rPr->hdpl)[Hdpi][Paperwidth];
		Prntlength = (rPr->vdpl)[Vdpi];

#ifdef DEBUG
		sudebug();
#endif

		for(i=2 ; i < argc ; ++i)
			Setuptext[i+4] = argv[i];

		(*(rPr->initsession))();
	}
	   else {
		Transparent = 1;

		Maintext[0] = Maintext[1];
		Maintext[1] = Maintext[2];
		Maintext[2] = Maintext[3];
#ifdef DEBUG
		Maintext[3] = Maintext[4];
		Maintext[4] = Maintext[5];
		Maintext[5] = Maintext[6];
		Maintext[6] = Maintext[7];
		Maintext[7] = Maintext[8];
#endif
	   }


	rm_msg = 0;
	Request = MOUSE|RCV|KBD|ALARM;
	request(Request);
	State = MAINMENU;
	rstate = &(P->state);
	if( !((*rstate & RESHAPED) && !(*rstate & MOVED)) )
		dispicon();

	while(State == MAINMENU) {
		pollret = poll(MOUSE);
		if(Transparent) /* Screen not available */
			if(pollret >= 0) ++pollret;
		switch(pollret) {
		case 0: /* Screen */
			State = SCRNSEL;
			scrnsel();
			rm_msg = 1;
			break;
		case 1: /* Host */
			State = HOSTON;
			host();
			rm_msg = 1;
			break;
		case 2: /* Exit */
			if(lexit())
				State = EXITSTATE;
			break;
#ifdef DEBUG
		case 3:
			ringbell();
			break;
		case 4:
			debugflg = 1;
			dispicon();
			break;
		case 5:
			debugflg = 0;
			rectf(&display, Drect, F_CLR);
			dispicon();
			break;
		case 6:
			++Delay;
			if(debugflg) lprintf("Delay = %D\n", Delay);
			break;
		case 7:
			Delay += 10;
			if(debugflg) lprintf("Delay = %D\n", Delay);
			break;
		case 8:
			--Delay;
			if(debugflg) lprintf("Delay = %D\n", Delay);
			break;
		case 9:
			Delay -= 10;
			if(debugflg) lprintf("Delay = %D\n", Delay);
			break;
#endif
		}
	}
}

poll(waittype)
register int waittype;
{
	register int *rstate;

	while(kbdchar() != -1)
		ringbell();

	rstate = &(P->state);
	if(*rstate & RESHAPED) {
		if(!(*rstate & MOVED)) {
			dispicon();
			msg(WASRESHAPED);
		}
		*rstate &= ~(RESHAPED|MOVED);
	}

	if(waittype) wait(waittype|KBD);

	if(own()&MOUSE) {
		if(waittype ? button3() : bttn3()) {
			if(rm_msg) {
				rm_msg = 0;
				msg(RMMSG);
			}
			return( menuhit(menus[State], 3) );
		}
		else if(waittype ? button2() : bttn2())
			setup_menu();
		else if(waittype && button1()) {
			Request &= ~MOUSE;
			request(Request);
			sleep(2); /* let control process it */
			Request |= MOUSE;
			request(Request);
		}
	}

	return(-2);
}

dispicon()
{
	Rectangle r;

#ifdef DEBUG
	if(debugflg) lprintf("++++ PRINTER ICON +++++\n");
	   else
#endif
	bitblt(&pmap, pmap.rect, &display, 
		Pt( (((Drect.corner.x - Drect.origin.x)-50)/2)+Drect.origin.x,
		max((((Drect.corner.y - Drect.origin.y)-68)/2),0)+Drect.origin.y ),
		F_OR);
}


Texture16 rusure = {
	0X0000, 0X0EA0, 0X0AA0, 0X08A0,
	0X08A0, 0X08E0, 0X0000, 0X0000,
	0XEAEE, 0X8AAA, 0XEA8E, 0X2A88,
	0XEE8E, 0X0000, 0X0000, 0X0000,
};

lexit()
{
	register Texture16 *prev;
	register int lexit;

	prev = Cursswitch(&rusure);
	while(!bttn123());
	lexit = bttn3();
	while(bttn123());
	Cursswitch(prev);
	return(lexit);
}

setup_menu()
{
	register int menuret;
	register struct Printers *rPr;

	if(Transparent) return;

	if(!(State==MAINMENU || State==SCRNSEL || State==SCRNSTART || State==HOSTON))
		return;

	rPr = Pr;
	menuret = menuhit(&Setupmenu, 2);
	switch(menuret) {
	case -1:
	case -2:
		break;
	case 0: /* Show Printer Page */
		showpage();
		break;
	case 1: /* Reshape to Page */
		pagereshape();
		break;
	case 2: /* Center */
		Setuptext[3][0] = ' ';
		Center = 1;
		Setuptext[2][0] = '>';
		break;
	case 3: /* No Center */
		Setuptext[2][0] = ' ';
		Center = 0;
		Setuptext[3][0] = '>';
		break;
	case 4: /* Offscreen Copy */
		Setuptext[5][0] = ' ';
		Docopy = 1;
		Setuptext[4][0] = '>';
		break;
	case 5: /* No Offscreen Copy */
		Setuptext[4][0] = ' ';
		Docopy = 0;
		Setuptext[5][0] = '>';
		break;
	default: /* printer specific setup options */
		if(menuret < (rPr->firstvdpi+6)) {  /* Horizontal DPI */
			Setuptext[Hdpi + 6][0] = ' ';
			Hdpi = menuret - 6;
			Prntwidth = (rPr->hdpl)[Hdpi][Paperwidth];
			if(State == SCRNSTART) redisp();
		}
		else if(menuret < (rPr->firstqual+6)) {  /* Vertical DPI */
			Setuptext[Vdpi + (rPr->firstvdpi+6)][0] = ' ';
			Vdpi = menuret - (rPr->firstvdpi+6);
			Prntlength = (rPr->vdpl)[Vdpi];
		}
		else if(menuret < (rPr->firstwidth+6)) {  /* Print Quality */
			Setuptext[Prntquality + (rPr->firstqual+6)][0] = ' ';
			Prntquality = menuret - (rPr->firstqual+6);
		}
		else {				    /* Paper Size */
			Setuptext[Paperwidth + (rPr->firstwidth+6)][0] = ' ';
			Paperwidth = menuret - (rPr->firstwidth+6);
			Prntwidth = (rPr->hdpl)[Hdpi][Paperwidth];
			if(State == SCRNSTART) redisp();
		}

		Setuptext[menuret][0] = '>';
		break;
	}
#ifdef DEBUG
	sudebug();
#endif
}

Texture16 erase = {
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
};

showpage()
{
	Point p, op, dp;
	Point savemouse;
	register int notfirst;

	savemouse = mouse.xy;
	dp = Pt( min(Prntwidth, XMAX), min(Prntlength, YMAX) );
	Cursswitch(&erase);

	for(notfirst=0 ; !bttn123() ; notfirst=1) {
		if(notfirst) outline(Rpt(p, add(p, dp)));
		nap(2);
		op = p;
		p = sub(mouse.xy, Pt(8,8)); /* mouse.xy clipped at Pt(8,8) */
                if (p.x + dp.x >= XMAX) 
                        p.x = XMAX - dp.x; 
                if (p.y + dp.y >= YMAX) 
                        p.y = YMAX - dp.y; 
		if(notfirst) outline(Rpt(op, add(op, dp))); 
		cursset( add(p, Pt(8,8)) );
        } 
	while (bttn123());
        cursset(savemouse);
	Cursswitch((Texture16 *)0);
}

pagereshape()
{
	register struct Proc *target;
	Rectangle r;

	if((target=point2layer()) != PNULL) {
		r = target->layer->rect;

		if(Prntwidth >= XMAX-16) {
			r.origin.x = 8;
			r.corner.x = XMAX-9;
		}
		else if(r.origin.x + Prntwidth <= XMAX-9) {
			r.corner.x = r.origin.x + Prntwidth;
		}
		else {
			r.corner.x = XMAX-9;
			r.origin.x = (XMAX-9) - Prntwidth;
		}
		
		if(Prntlength >= YMAX-16) {
			r.origin.y = 9;
			r.corner.y = YMAX-9;
		}
		else if(r.origin.y + Prntlength <= YMAX-9) {
			r.corner.y = r.origin.y + Prntlength;
		}
		else {
			r.corner.y = YMAX-9;
			r.origin.y = (YMAX-9) - Prntlength;
		}

		reshape(target->layer, r);
	}
}

redisp()
{

	if( rect_changed() ) return;

	rectf(Sp, Srect, F_XOR);
	Srect = SaveSrect;
	clipSrect();
	rectf(Sp, Srect, F_XOR);

}

#ifdef DEBUG
sudebug()
{
	if(!debugflg) return;
	lprintf("Center = %D\n", Center);
	lprintf("Hdpi = %D\n", Hdpi);
	lprintf("Vdpi = %D\n", Vdpi);
	lprintf("Prntquality = %D\n", Prntquality);
	lprintf("Paperwidth = %D\n", Paperwidth);
	lprintf("Prntwidth = %D\n", Prntwidth);
	lprintf("Prntlength = %D\n", (Pr->vdpl)[Vdpi]);
	lprintf("\n");
}
#endif
