/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
HVERSION(pandora,@(#)pandora.h	2.10);
*/

/*
 * System calls
 */
#ifdef  jinit
#undef  jinit
#define	jinit()		Ivoid(17)()	/*'Ujinit'*/
#endif
#ifdef  cbufavail
#undef  cbufavail
#define cbufavail(t)	Iint(221)(t)
#endif
#ifdef  passchar
#undef  passchar
#define passchar(c, t)	Ivoid(222)(c, t)
#endif
#ifdef  dellayer
#undef  dellayer
#define	dellayer(l)	Iint(11)(l)
#endif
#ifdef  clippt
#undef  clippt
#define clippt(p,f)	Iint(95)(p,f)
#endif
#ifdef  newlayer
#undef  newlayer
#define	newlayer(r)	IpLayer(36)(r)
#endif
#ifdef  tolayer
#undef  tolayer
#define tolayer(l)	Ivoid(73)(l)
#endif
#ifdef  upfront
#undef  upfront
#define	upfront(l)	Iint(52)(l)
#endif
#ifdef  stipple
#undef  stipple
#define	stipple(r)	Ivoid(54)(r, 1)	/*'clear'*/
#endif
#ifdef  debug
#undef  debug
#define	debug()		IpProc(55)()
#endif
#ifdef  lpoint
#undef  lpoint
#define	lpoint(b, p, f)	Ivoid(60)(b, p,	f)
#endif
#ifdef  lrectf
#undef  lrectf
#define	lrectf(b, r, f)	Ivoid(61)(b, r,	f)
#endif
#ifdef  lsegment
#undef  lsegment
#define	lsegment(b, p, q, f)	Ivoid(62)(b, p,	q, f)
#endif
#ifdef  ltexture
#undef  ltexture
#define	ltexture(b, r, t, f)	Ivoid(63)(b, r,	t, f)
#endif
#ifdef  Jcursinhibit
#undef  Jcursinhibit
#define	Jcursinhibit()	Ivoid(67)()	/*'cursinhibit'*/
#endif
#ifdef  Jcursallow
#undef  Jcursallow
#define	Jcursallow()	Ivoid(68)()	/*'cursallow'*/
#endif
#ifdef  newproc
#undef  newproc
#define	newproc(f)	IpProc(70)(f)
#endif
#ifdef  mpxnewwind
#undef  mpxnewwind
#define	mpxnewwind(p,c)	Ivoid(71)(p,c)
#endif
#ifdef  newwindow
#undef  newwindow
#define	newwindow(f)	Ivoid(72)(f)
#endif
#ifdef  Bottom
#undef  Bottom
#define Bottom()		Iint(75)()
#endif
#ifdef  Control
#undef  Control
#define Control()		Ivoid(76)()
#endif
#ifdef  Current
#undef  Current
#define Current()		Iint(77)()
#endif
#ifdef  Delete
#undef  Delete
#define Delete()		Iint(78)()
#endif
#ifdef  Exit
#undef  Exit
#define Exit()			Iint(79)()
#endif
#ifdef  Move
#undef  Move
#define Move()			Iint(80)()
#endif
#ifdef  New
#undef  New
#define New()			Iint(81)()
#endif
#ifdef  Psend
#undef  Psend
#define Psend(a, b, c, d)	Iint(82)(a, b, c, d)
#endif
#ifdef  Reply
#undef  Reply
#define Reply(x)		Ivoid(83)(x)
#endif
#ifdef  Reshape
#undef  Reshape
#define Reshape()		Iint(84)()
#endif
#ifdef  Retry
#undef  Retry
#define Retry()			Iint(85)()
#endif
#ifdef  Sw
#undef  Sw
#define Sw()			Iint(86)()
#endif
#ifdef  Top
#undef  Top
#define Top()			Iint(87)()
#endif
#ifdef  _start
#undef  _start
#define _start()		Ivoid(88)()
#endif
#ifdef  agent
#undef  agent
#define agent(a)		Iint(89)(a)
#endif
#ifdef  bldargs
#undef  bldargs
#define bldargs(x, y)		Iint(90)(x, y)
#endif
#ifdef  boot
#undef  boot
#define boot()			Iint(91)()
#endif
#ifdef  canon
#undef  canon
#define canon(x, y)		IRectangle(93)(x, y)
#endif
#ifdef  checkrect
#undef  checkrect
#define checkrect(r)		IRectangle(94)(r)
#endif
#ifdef  clockroutine
#undef  clockroutine
#define clockroutine()		Iint(96)()
#endif
#ifdef  control
#undef  control
#define control()		Iint(97)()
#endif
#ifdef  copy
#undef  copy
#define copy(s)			Iint(98)(s)
#endif
#ifdef  crc
#undef  crc
#define crc(s, n)		Iint(99)(s, n)
#endif
#ifdef  curse
#undef  curse
#define curse(c)		Iint(100)(c)
#endif
#ifdef  delproc
#undef  delproc
#define delproc(p)		Iint(101)(p)
#endif
#ifdef  demux
#undef  demux
#define demux()			Iint(102)()
#endif
#ifdef  dobutton
#undef  dobutton
#define dobutton(b)		Iint(103)(b)
#endif
#ifdef  doctl
#undef  doctl
#define doctl(s, n)		Iint(104)(s, n)
#endif
#ifdef  error
#undef  error
#define error(x, y)		Iint(105)(x, y)
#endif
#ifdef  excep_norm
#undef  excep_norm
#define excep_norm()		Iint(106)()
#endif
#ifdef  excep_proc
#undef  excep_proc
#define excep_proc()		Iint(107)()
#endif
#ifdef  excep_stack
#undef  excep_stack
#define excep_stack()		Iint(108)()
#endif
#ifdef  exec
#undef  exec
#define exec(f)			Iint(109)(f)
#endif
#ifdef  execsw
#undef  execsw
#define execsw()		Iint(110)()
#endif
#ifdef  freemem
#undef  freemem
#define freemem(p)		Iint(111)(p)
#endif
#ifdef  getanum
#undef  getanum
#define getanum(a,b,c)		Iint(112)(a,b,c)
#endif
#ifdef  getchar
#undef  getchar
#define getchar()		Iint(113)()
#endif
#ifdef  getlong
#undef  getlong
#define getlong()		Iint(114)()
#endif
#ifdef  givemouse
#undef  givemouse
#define givemouse(p,u)		Iint(115)(p,u)
#endif
#ifdef  host_int
#undef  host_int
#define host_int()		Ivoid(116)()
#endif
#ifdef  key_int
#undef  key_int
#define key_int()		Ivoid(119)()
#endif
#ifdef  lscroll
#undef  lscroll
#define lscroll(a, b, c)	Iint(120)(a, b, c)
#endif
#ifdef  lscrolx
#undef  lscrolx
#define lscrolx(a,b)		Iint(121)(a,b)
#endif
#ifdef  main
#undef  main
#define main()			Iint(122)()
#endif
#ifdef  move
#undef  move
#define move(l, p)		Iint(125)(l, p)
#endif
#ifdef  mpxcore
#undef  mpxcore
#define mpxcore(w)		Iint(126)(w)
#endif
#ifdef  mpxdelwind
#undef  mpxdelwind
#define mpxdelwind(w)		Iint(127)(w)
#endif
#ifdef  mpxkbdchar
#undef  mpxkbdchar
#define mpxkbdchar(c)		Iint(128)(c)
#endif
#ifdef  mpxkbdflush
#undef  mpxkbdflush
#define mpxkbdflush()		Iint(129)()
#endif
#ifdef  mpxsendchar
#undef  mpxsendchar
#define mpxsendchar(c, p)	Iint(130)(c, p)
#endif
#ifdef  mpxublk
#undef  mpxublk
#define mpxublk(p)		Iint(131)(p)
#endif
#ifdef  msvid_int
#undef  msvid_int
#define msvid_int()		Ivoid(132)()
#endif
#ifdef  newline
#undef  newline
#define newline(c)		Iint(133)(c)
#endif
#ifdef  nlcount
#undef  nlcount
#define nlcount(a)		Iint(134)(a)
#endif
#ifdef  numbers
#undef  numbers
#define numbers(a,b,c)		Iint(135)(a,b,c)
#endif
#ifdef  out_int
#undef  out_int
#define out_int()		Ivoid(136)()
#endif
#ifdef  pinit
#undef  pinit
#define pinit(c)		Iint(138)(c)
#endif
#ifdef  precv
#undef  precv
#define precv(c)		Ivoid(139)(c)
#endif
#ifdef  psend
#undef  psend
#define psend(a, b, c, d)	Iint(140)(a, b, c, d)
#endif
#ifdef  pt
#undef  pt
#define pt(p)			IPoint(141)(p)
#endif
#ifdef  ptimeout
#undef  ptimeout
#define ptimeout(a)		Iint(142)(a)
#endif
#ifdef  readchar
#undef  readchar
#define readchar(x)		Iint(143)(x)
#endif
#ifdef  RECT
#undef  RECT
#define RECT(r)			IRectangle(144)(r)
#endif
#ifdef  recvchars
#undef  recvchars
#define recvchars(l, p, n)	Iint(145)(l, p, n)
#endif
#ifdef  reshape
#undef  reshape
#define reshape(l, r)		Iint(146)(l, r)
#endif
#ifdef  restart
#undef  restart
#define restart(a, b)		Iint(147)(a, b)
#endif
#ifdef  sendpkt
#undef  sendpkt
#define sendpkt(p, n)		Iint(148)(p, n)
#endif
#ifdef  setdata
#undef  setdata
#define setdata(p)		Iint(149)(p)
#endif
#ifdef  shade
#undef  shade
#define shade(l)		Iint(150)(l)
#endif
#ifdef  shutdown
#undef  shutdown
#define shutdown(p)		Iint(151)(p)
#endif
#ifdef  switcher
#undef  switcher
#define switcher()		Iint(152)()
#endif
#ifdef  trap
#undef  trap
#define trap(a,b)		Iint(153)(a,b)
#endif
#ifdef  whichbutton
#undef  whichbutton
#define whichbutton()		Iint(154)()
#endif
#ifdef  whichlayer
#undef  whichlayer
#define whichlayer()		IpLayer(155)()
#endif
#ifdef  whichproc
#undef  whichproc
#define whichproc(l) 		Iint(156)(l)
#endif
#ifdef  windowproc
#undef  windowproc
#define windowproc()		Iint(157)()
#endif
#ifdef  windowstart
#undef  windowstart
#define windowstart()		Iint(158)()
#endif
#ifdef  writec
#undef  writec
#define writec( a, b, c)	Iint(159)( a, b, c)
#endif
#ifdef  zombexec
#undef  zombexec
#define zombexec(f)		Iint(160)(f)
#endif
#ifdef  zombsw
#undef  zombsw
#define zombsw()		Iint(161)()
#endif
#ifdef  swinit
#undef  swinit
#define swinit()		Iint(162)()
#endif
#ifdef  Free_RAM		
#undef  Free_RAM		
#define Free_RAM		((int *)Sys[163])
#endif
#ifdef  sysrun
#undef  sysrun
#define sysrun(a)		Ivoid(166)(a)
#endif
#ifdef  kbdproc			
#undef  kbdproc			
#define kbdproc			D_Ref(struct Proc *,168)
#endif
#ifdef  debugger		
#undef  debugger		
#define debugger		D_Ref(struct Proc *,169)
#endif
#ifdef  second			
#undef  second			
#define second			D_Ref(short,170)
#endif
#ifdef  ticks			
#undef  ticks			
#define ticks			D_Ref(short,171)
#endif
#ifdef  ticks0			
#undef  ticks0			
#define ticks0			D_Ref(long,172)
#endif
#ifdef  proctab			
#undef  proctab			
#define proctab			P_Array(struct Proc,173)
#endif
#ifdef  pconvs			
#undef  pconvs			
#define pconvs			P_Array(struct Pchannel,174)
#endif
#ifdef  pconfig			
#undef  pconfig			
#define pconfig			I_Ref(struct Pconfig,175)
#endif
#ifdef  menufn			
#undef  menufn			
#define menufn			((int (**)())Sys[176])
#endif
#ifdef  windowmenu		
#undef  windowmenu		
#define windowmenu		I_Ref(struct Menu,177)
#endif
#ifdef  usermouse		
#undef  usermouse		
#define usermouse		D_Ref(short,178)
#endif
#ifdef  kbdlist			
#undef  kbdlist			
#define kbdlist			P_Array(char,179)
#endif
#ifdef  kbdlistp		
#undef  kbdlistp		
#define kbdlistp		D_Ref(char *,180)
#endif
#ifdef  hst_init		
#undef  hst_init		
#define hst_init		D_Ref(short,181)
#endif
#ifdef  menutext		
#undef  menutext		
#define menutext		P_Array(char *,185)
#endif
#ifdef  sendbusy		
#undef  sendbusy		
#define sendbusy		D_Ref(short,186)
#endif
#ifdef  rebootflag		
#undef  rebootflag		
#define rebootflag		D_Ref(short,188)
#endif
#ifdef  last			
#undef  last			
#define last			D_Ref(struct Proc *,189)
#endif
#ifdef  patchedspot		
#undef  patchedspot		
#define patchedspot		D_Ref(char *,190)
#endif
#ifdef  patch			
#undef  patch			
#define patch			D_Ref(char,191)
#endif

/* Vector table entries 193 - 213 are textures defined in mpx.h */

#ifdef  point2layer
#undef  point2layer
#define point2layer()	IpProc(218)()
#endif
#ifdef  whichaddr
#undef  whichaddr
#define whichaddr(l) 	IpProc(219)(l)
#endif
#ifdef  downback
#undef  downback
#define downback(lp)	Iint(220)(lp)
#endif
#ifdef  checkbram
#undef  checkbram
#define checkbram()	Iint(236)()
#endif
#ifdef  Cursswitch
#undef  Cursswitch
#define Cursswitch(a)	IpTexture16(237)(a)
#endif
#ifdef  layerop
#undef  layerop
#define layerop(a, b, c, d, e, f)	Iint(238)(a, b, c, d, e, f)
#endif
#ifdef  lbitblt
#undef  lbitblt
#define lbitblt(a, b, c, d, e)		Ivoid(239)(a, b, c, d, e)
#endif
#ifdef  lblt
#undef  lblt
#define lblt(a, b, c, d, e)		Iint(240)(a, b, c, d, e)
#endif
#ifdef  qclear
#undef  qclear
#define qclear(a)	Iint(241)(a)
#endif
#ifdef  qgetc
#undef  qgetc
#define qgetc(a)	Iint(242)(a)
#endif
#ifdef  qputc
#undef  qputc
#define qputc(a, b)	Iint(243)(a, b)
#endif
#ifdef  setbram
#undef  setbram
#define setbram()	Iint(244)()
#endif
#ifdef  spl0
#undef  spl0
#define spl0()		Iint(245)()
#endif
#ifdef  spl4
#undef  spl4
#define spl4()		Iint(246)()
#endif
#ifdef  spl7
#undef  slp7
#define spl7()		Iint(247)()
#endif
#ifdef  splx
#undef  slpx
#define splx(a)		Iint(248)(a)
#endif
#ifdef  allocendp
#undef  allocendp	
#define allocendp	I_Ref(char *,249)
#endif
#ifdef  allocstartp
#undef  allocstartp	
#define allocstartp	I_Ref(char *,250)
#endif
#ifdef  ENDAREA	
#undef 	ENDAREA
#define ENDAREA		I_Ref(long *,251)
#endif
#ifdef  maxaddr
#undef 	maxaddr	
#define maxaddr		P_Array(long,252)
#endif
#ifdef  realmouse
#undef 	realmouse	
#define realmouse	I_Ref(struct Mouse,253)
#endif
#ifdef  nextlong
#undef 	nextlong	
#define nextlong	I_Ref(long *,254)
#endif
