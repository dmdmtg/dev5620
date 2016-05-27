/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


/* static char _jim_sccsid[]="@(#)jim.h	1.1.1.1	(5/10/87)"; */

typedef unsigned long	Ulong;
typedef unsigned long	Posn;
extern char	*homedir;
extern char	*alloc();
extern char	*brk();
extern char	*gcalloc();
extern char	*gcrealloc();
extern char	*sbrk();
extern char	*charstar();
extern char	*jerqname();
extern long	min();
#define	gcnew(p, n)	((void)gcalloc((Ulong)(n)*sizeof((p)[0]), (long **)&(p)))
#define	gcrenew(p, n)	((void)gcrealloc((char *)p, ((Ulong)(n)*sizeof((p)[0]))))
#define	MAXFILES	256	/* 255 real files, 0 for unallocated */
