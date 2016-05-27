/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef	MPX_H
#define	MPX_H	MPX_H
/*
#include <sccsid.h>
HVERSION(mpx,@(#)mpx.h	2.6);
*/

#ifndef	LAYER_H
#include <layer.h>
#endif

#ifndef	JERQPROC_H
#include <dmdproc.h>
#endif

#undef BonW
#undef WonB


extern Bitmap *Jdisplayp;
extern struct Mouse mouse;
#define	display	(*Jdisplayp)
#define PtCurrent P->curpt
typedef	int (*ptr_fint)();

#define button(i)	(clipbttn() & (8 >> i))
#define button1()	(clipbttn() & 4)
#define button2()	(clipbttn() & 2)
#define button3()	(clipbttn() & 1)
#define button12()	(clipbttn() & 6)
#define button13()	(clipbttn() & 5)
#define button23()	(clipbttn() & 3)
#define button123()	(clipbttn() & 7)

/* WARNING: These are ``magic'' numbers.  They shouldn't change, because all
 * layers programs and libmj will be broken.	    
 */

#define	P	(*((struct Proc	**)0x0071d700))
#define	Sys	((ptr_fint *)0x0071d700)


/*
 * Cast	macros
 */
#define	Cast(t,	x)	((t (*)())Sys[x])
#define	IPoint(x)	(*Cast(Point, x))
#define	IRectangle(x)	(*Cast(Rectangle, x))
#define	Iint(x)		(*Cast(int, x))
#define	Ilong(x)	(*Cast(long, x))
#define	Ishort(x)	(*Cast(short, x))
#define	IpBitmap(x)	(*Cast(Bitmap *, x))
#define	IpTexture16(x)	(*Cast(Texture16 *, x))
#define	IpLayer(x)	(*Cast(Layer *,	x))
#define	IpWord(x)	(*Cast(Word *, x))
#define	Ipchar(x)	(*Cast(char *, x))
#define	Ivoid(x)	(*Cast(void, x))
#define	IpProc(x)	(*Cast(struct Proc *, x))
#define I_Ref(t,i)	(*(t *)Sys[i])		/* Indirect reference */
#define P_Array(t,i)	((t *)Sys[i])		/* pointer to array */
#define D_Ref(t,i)	(*(t *)&Sys[i])		/* Direct reference */



#ifdef MPXINDIRECT
/* This is to permit passing rom routine address to another function */

#define	add		IPoint(2)
#define	addr		IpWord(3)
#define	alloc		Ipchar(4)
#define	balloc		IpBitmap(5)
#define	bfree		Ivoid(6)
#define	bitblt		Ivoid(7)
#define	cursallow	Ivoid(8)
#define	cursinhibit	Ivoid(9)
#define	cursswitch	IpTexture16(10)
#define	div		IPoint(12)
#define	eqrect		Iint(13)
#define	exit		Ivoid(14)
#define	free		Ivoid(15)
#define	inset		IRectangle(16)
#define	jline		Ivoid(18)
#define	jlineto		Ivoid(19)
#define	jmove		Ivoid(20)
#define	jmoveto		Ivoid(21)
#define	jpoint		Ivoid(22)
#define	jrectf		Ivoid(23)
#define	jsegment	Ivoid(24)
#define	jstring		IPoint(25)
#define	jtexture	Ivoid(26)
#define	kbdchar		Iint(27)
#define	nap		Ivoid(28)
#define	point		Ivoid(29)
#define	rectf		Ivoid(30)
#define	segment		Ivoid(31)
#define	sleep		Ivoid(32)
#define	texture		Ivoid(33)
#define	menuhit		Iint(34)
#define	mul		IPoint(35)
#define	own		Iint(37)
#define	ptinrect	Iint(38)
#define	raddp		IRectangle(39)
#define	rcvchar		Iint(40)
#define	rectXrect	Iint(41)
#define	rectclip	Iint(42)
#define	request		Iint(43)
#define	rsubp		IRectangle(44)
#define	screenswap	Ivoid(45)
#define	sendchar	Iint(46)
#define	sendnchars	Ivoid(47)
#define	string		IPoint(48)
#define	strwidth	Iint(49)
#define	sub		IPoint(50)
#define	sw		Ivoid(51)
#define	wait		Iint(53)
#define	gcalloc		Ipchar(56)
#define	gcfree		Ivoid(57)
#define	getrect		IRectangle(58)
#define	alarm		Ivoid(59)
#define	transform	IPoint(64)
#define	rtransform	IRectangle(65)
#define	realtime	Ilong(66)
#define	cursset		Ivoid(69)
#define jstrwidth	Iint(74)
#define bttns		Ivoid(92)
#define canon		IRectangle(93)
#define itox		Ipchar(117)
#define max		Iint(123)
#define min		Iint(124)
#define outline		Ivoid(137)
#define version		Iint(164)
#define ringbell	Ivoid(165)
#define psendchar	Iint(192)
#define polyf		Iint(214)
#define ptinpoly	Iint(216)
#define	clipbttn	Iint(217)
#define abs		Iint(223)
#define pfkey		Iint(224) /* bramgetstr */
#define ceil		Ishort(225)
#define eqpt		Iint(226)
#define floor		Ishort(227)
#define strlen		Iint(228)
#define Pt		IPoint(229)
#define Rect		IRectangle(230)
#define Rpt		IRectangle(231)
#define botbits		P_Array(long, 232)
#define topbits		P_Arraylong, 233)
#define physical	I_Ref(Bitmap,234) /* display */
#define qsort		Ivoid(235)


#else
/* This section will do the parameter passing check, historical. */

#define	add(p, q)	IPoint(2)(p, q)
#define	addr(b,	p)	IpWord(3)(b, p)
#define	alloc(u)	Ipchar(4)(u)	/*'Ualloc'*/
#define	balloc(r)	IpBitmap(5)(r)	/*'Uballoc'*/
#define	bfree(p)	Ivoid(6)(p)
#define	bitblt(sb, r, db, p, f)	Ivoid(7)(sb, r,	db, p, f)	/*'Ubitblt'*/
#define	cursallow()	Ivoid(8)()	/*'Ucursallow'*/
#define	cursinhibit()	Ivoid(9)()	/*'Ucursinhibit'*/
#define	cursswitch(c)	IpTexture16(10)(c)	/*'Ucursswitch'*/
#define	div(p, n)	IPoint(12)(p, n)
#define	eqrect(r, s)	Iint(13)(r, s)
#define	exit()		Ivoid(14)()	/*'Uexit'*/
#define	free(p)		Ivoid(15)(p)
#define	inset(r, n)	IRectangle(16)(r, n)
#define	jline(p, f)	Ivoid(18)(p, f)	/*'Ujline'*/
#define	jlineto(p, f)	Ivoid(19)(p, f)	/*'Ujlineto'*/
#define	jmove(p)	Ivoid(20)(p)	/*'Ujmove'*/
#define	jmoveto(p)	Ivoid(21)(p)	/*'Ujmoveto'*/
#define	jpoint(p, f)	Ivoid(22)(p, f)	/*'Ujpoint'*/
#define	jrectf(r, f)	Ivoid(23)(r, f)	/*'Ujrectf'*/
#define	jsegment(p, q, f)	Ivoid(24)(p, q,	f)	/*'Ujsegment'*/
#define	jstring(s)	IPoint(25)(s)	/*'Ujstring'*/
#define	jtexture(r, m, f)	Ivoid(26)(r, m,	f)	/*'Ujtexture'*/
#define	kbdchar()		Iint(27)()		/*'Ukbdchar'*/
#define	nap(s)		Ivoid(28)(s)
#define	point(l, p, f)	Ivoid(29)(l, p,	f)	/*'Upoint'*/
#define	rectf(l, r, f)	Ivoid(30)(l, r,	f)	/*'Urectf'*/
#define	segment(l, p, q, f)	Ivoid(31)(l, p,	q, f)	/*'Usegment'*/
#define	sleep(s)	Ivoid(32)(s)
#define	texture(l, r, m, f)	Ivoid(33)(l, r,	m, f)	/*'Utexture'*/
#define	menuhit(m, n)	Iint(34)(m, n)
#define	mul(p, n)	IPoint(35)(p, n)
#define	own()		Iint(37)()	/*'Uown'*/
#define	ptinrect(p, r)	Iint(38)(p, r)
#define	raddp(r, p)	IRectangle(39)(r, p)
#define	rcvchar()	Iint(40)()	/*'Urcvchar'*/
#define	rectXrect(r, s)	Iint(41)(r, s)
#define	rectclip(pr, r)	Iint(42)(pr, r)
#define	request(r)	Iint(43)(r)	/*'Urequest'*/
#define	rsubp(r, p)	IRectangle(44)(r, p)
#define	screenswap(b, r, s)	Ivoid(45)(b, r,	s)	/*'Uscreenswap'*/
#define	sendchar(c)	Iint(46)(c)	/*'Usendchar'*/
#define	sendnchars(n, p)	Ivoid(47)(n,p)
#define	string(F, s, b,	p, f)	IPoint(48)(F, s, b, p, f)
#define	strwidth(F, s)	Iint(49)(F,s)
#define	sub(p, q)	IPoint(50)(p, q)
#define	sw(n)		Ivoid(51)(n)
#define	wait(n)		Iint(53)(n)	/*'Uwait'*/
#define	gcalloc(n, w)	Ipchar(56)(n, w, P)	/*'realgcalloc'*/
#define	gcfree(s)	Ivoid(57)(s)
#define	getrect()	IRectangle(58)()
#define	alarm(n)	Ivoid(59)(n)
#define	transform(p)	IPoint(64)(p)
#define	rtransform(p)	IRectangle(65)(p)
#define	realtime()	Ilong(66)()
#define	cursset(p)	Ivoid(69)(p)
#define jstrwidth(s)	Iint(74)(s)
#define bttns(a)		Iint(92)(a)
#define canon(x, y)		IRectangle(93)(x, y)
#define itox(n,s)		Ipchar(117)(n,s)
#define max(a, b)		Iint(123)(a, b)
#define min(a, b)		Iint(124)(a, b)
#define outline(r)		Ivoid(137)(r)
#define version()		Iint(164)()
#define ringbell()		Ivoid(165)()
#define psendchar(c)		Iint(192)(c)
#define polyf(b,p,n,t,f)	Iint(214)(b,p,n,t,f)
#define ptinpoly(p,q,n)		Iint(216)(p,q,n)
#define	clipbttn()		Iint(217)()
#define abs(a)			Iint(223)(a)
#define pfkey(a, b, c)		Iint(224)(a, b, c) /* bramgetstr */
#define ceil(a, b)		Ishort(225)(a, b)
#define eqpt(a, b)		Iint(226)(a, b)
#define floor(a, b)		Ishort(227)(a, b)
#define strlen(a)		Iint(228)(a)
#define Pt(a, b)		IPoint(229)(a, b)
#define Rect(a, b, c, d)	IRectangle(230)(a, b, c, d)
#define Rpt(a, b)		IRectangle(231)(a, b)
#define botbits			P_Array(long, 232)
#define topbits			P_Array(long, 233)
#define physical		I_Ref(Bitmap,234) /* actual display */
#define qsort(a,b,c,d)		Ivoid(235)(a,b,c,d)


#endif

#define C_crosshair		(*((Texture16 *)Sys[193]))
#define C_clock			(*((Texture16 *)Sys[194]))
#define C_move			(*((Texture16 *)Sys[195]))
#define C_skull			(*((Texture16 *)Sys[198]))
#define C_sweep			(*((Texture16 *)Sys[199]))
#define C_target		(*((Texture16 *)Sys[200]))
#define C_confirm		(*((Texture16 *)Sys[201]))
#define C_cup			(*((Texture16 *)Sys[202]))
#define C_deadmouse		(*((Texture16 *)Sys[203]))

#define T_background		(*((Texture *)Sys[207]))
#define T_darkgrey		(*((Texture *)Sys[208]))
#define T_grey			(*((Texture *)Sys[209]))
#define T_lightgrey		(*((Texture *)Sys[210]))
#define T_white			(*((Texture *)Sys[211]))
#define T_black			(*((Texture *)Sys[212]))
#define T_checks		(*((Texture *)Sys[213]))

#endif	MPX_H
