/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)main.c	2.11);
*/

#define MPXTERM
#include <dmd.h>
#include "states.h"
#include "../menu.h"
#include "../protocol.h"
#include "../traps.h"
#include "../isp.h"

#define	IpProc(x)	(*Cast(struct Proc *, x))
#define	debug()		IpProc(55)()			/*'debug'*/

		/* work around sgs error - change with new sgs ?!!!!!! */
#define CHARMINUS1 (char) 0x00ff


typedef long MLONG;

enum updown { UP, DOWN };
enum updown bptsw = UP;

long	loc, limit, longfromhost(), addrfromhost();

struct Proc *p = 0;
int enabled = 0;
int anticipate = 0;
char	*txt;		/*starting text address */
char	bptsave[BPTS];	/* instruction at breakpointed location */
char	*bptloc[BPTS];		/* moved from joff/traps.h */

	/* operand length table for 32a index=mmmmx (x =1 if rrrr=15) */
short	lentab[32]={1,1,1,1,1,1,1,1,1,5,1,3,1,2,1,5,5,5,5,5,3,3,3,3,2,2,
			2,2,4,5,1,1};

extern int buttmenu[4];


long hatebs()
{
	int i;
	static prev = ERRORED;

	if( !p ) return prev = ERRORED;
	if( !(p->state&BUSY) || p->text != txt ){
		if( prev != ERRORED ){
			lprintf( "\ndmd process deleted/reloaded\n" );
			lprintf( "\007no layer\r" );
			for( i = 0; i < BPTS; ++i ) bptloc[i] = 0;
			p = 0;
			bptsw = UP;
		}
		return prev = ERRORED;
	}
	if( !(p->state&ZOMBIE) ) return prev = ACTIVE;
	if( !p->traploc ) return prev = HALTED;
	switch(((* p->traptype ) & TRAP_BITS)){
		case BPT_TRAP:		return prev = BREAKPTED;
		case TRACE_TRAP:	return prev = STEPPED;
		default:		return prev = TRAPPED;
	}
}

long aligneven( a )
long a;
{
	return a&1 ? a+1 : a;
}

long alignmod4( a )
long a;
{
	return a&3 ? (a|3)+1 : a;
}

long read( a )
long a;
{
	if( a > HI_ADDR ) return LO_ADDR;
	if( a >= LO_ADDR  && a <= HI_ADDR ) return a;
	if( a >= LO_ROM   && a <= HI_ROM  ) return a;
	if( a >= LO_DUAR  && a <= HI_DUAR ) return a;
	if( a >= LO_PIO   && a <= HI_PIO  ) return a;
	if( a >= LO_MOUS  && a <= HI_MOUS ) return a;
	if( a >= LO_DISP  && a <= HI_DISP ) return a;
	if( a >= LO_BRAM  && a <= HI_BRAM ) return a;
	return LO_ADDR;
}

long write( a )
long a;
{
	if( a == (long) DADDR ) return a;
	if( a > HI_ADDR ) return LO_ADDR;
	if( a >= LO_ADDR  && a <= HI_ADDR ) return a;
	if( a >= LO_DUAR  && a <= HI_DUAR ) return a;
	if( a >= LO_PIO   && a <= HI_PIO  ) return a;
	if( a >= LO_MOUS  && a <= HI_MOUS ) return a;
	if( a >= LO_DISP  && a <= HI_DISP ) return a;
	if( a >= LO_BRAM  && a <= HI_BRAM ) return a;
	return LO_ADDR;
}

#define mlong(x) (*(long *) read(alignmod4(x)))	
#define mshort(x) (*(short *) read(aligneven(x)))

main(){
	request( RCV|KBD|SEND|MOUSE );
	lprintf("Initializing...\n");
	m_init();
	joff();
}	

joff()
{
	register long reg, i;
	long fp, function, retaddr;
	long *lptr;
	char *cptr, nreg;
	char c;

	for( ;; ){
		while( (c = charfromhost()) != ESCAPE ) put( c );
		switch( c = charfromhost() ){
		case DO_INVOKE:	invokef();
				break;
		case DO_WRAP:	exit();
		case DO_KBD:	choosecursor();
				line();
				dmcursor();
			 	break;
		case M_MENU:
		case M_ITEM:
		case M_HIT:
		case M_NULL:
		case M_BUTT:
		case M_CONFIRM:
		case M_PENDULUM:
		case M_LIMITS:
		case M_BITVEC:
		case M_SUGGEST:
				menuop(c); break;
		case G_BITMAP:
		case G_RECTANGLE:
		case G_TEXTURE:
		case G_16TEXTURE:
		case G_POINT:
				graphop(c); break;
		case PEEK_PCBREG:
			longtohost( p->pcb.fp );
			longtohost( p->pcb.ap );
			longtohost( p->pcb.pc );
			longtohost( p->pcb.sp_lower );
			break;
		case PEEK_PCAPFP:
			lptr = (long *)addrfromhost();
			longtohost( *lptr++ );
			longtohost( *lptr++ );
			longtohost( *lptr );
			break;
		case PEEK_SAVE:
			cptr = (char *)addrfromhost();
			if( *cptr++ != SAVEINST ||
			   (nreg = *cptr) < 0x43 || nreg > 0x49)
				sendchar( BADTRACE );
			else
				sendchar( 0x49 - nreg );
			break;
		case PEEK_LONG:
			loc = addrfromhost();
			if( loc > INDEX_BASE && loc <= LAST_INDEX )
				switch( loc ){
				case PROC_INDEX:
					longtohost(p); break;
				case TYPE_INDEX:
					longtohost((long) *p->traptype); break;
				case TLOC_INDEX:
					longtohost(*p->traploc); break;
				case HATEBS_INDEX:
					longtohost( hatebs() ); break;
				case ARGV_INDEX:
					longtohost(((struct udata *)
							p->data)->argv);
					break;
				}
			else
				longtohost( mlong(loc) );
			break;
		case PEEK_SHORT:
			shorttohost( mshort( addrfromhost() ) ); break;
		case PEEK_BYTE:
			sendchar( *(char *) read(addrfromhost())); break;
		case POKE_LONG:
			reg = write(alignmod4( addrfromhost()));
			* (long *) reg = longfromhost();
			break;
		case POKE_SHORT:
			reg = write(aligneven( addrfromhost()));
			* (short *) reg = (short) shortfromhost();
			break;
		case POKE_BYTE:
			reg = write(addrfromhost());
			* (char *) reg = (char) charfromhost();
			break;
		case PEEK_STR:
			reg = read(addrfromhost());
			strntohost( (char *) reg, charfromhost() ); break;
		case DO_DEBUG:
			lprintf("\007use mouse to select layer\r");
			choosecursor();
			p = debug();
			if( p == P ) p = 0;
			if( p ){
				txt = p->text;
				for( i = 2; i; --i ){
					rectf( p->layer, p->layer->rect, F_XOR );
					nap( 20 );
				}
			}
			bptsw = DOWN;
			enabled = limit = 0;
			dmcursor();
			longtohost(p);
			break;
		case DO_BPTS:
			loc = addrfromhost();
			setbpt(charfromhost());
			break;
		case DO_BPTC:
			clrbpt(charfromhost()); break;
		case DO_FUNC:
			function = addrfromhost();	break;
		case DO_HALT:
			halt();	break;
		case DO_ACT:
			run();	break;
		case DO_LIMIT:
			limit = addrfromhost(); break;
		case DO_SING:
			single(limit);	break;
		case DO_ENABLE:
			enabled = 1;	break;
		case DO_DISABLE:
			enabled = 0; break;
		case DO_ANTIC:
			anticipate = 1; break;	
		default: put( c );
		}
	}
}

run()
{
	switch( hatebs() ){
		case ERRORED:
		case TRAPPED:
		case ACTIVE: return;
 		case HALTED: break;
		case BREAKPTED:
			single(0);
			if( hatebs() != STEPPED ) return;
		case STEPPED:
			p->state |= RUN;   /* trap() in mpx does sw(0) */
	}
	laybpts();
	p->state &= ~ZOMBIE;
	p->traploc = 0;
}

halt()
{
	if( hatebs() != ACTIVE ) return;
	p->state |= ZOMBIE;
	liftbpts();
}

letrun()
{
	p->state &= ~ZOMBIE;
	p->state |= RUN;	/* trap() in mpx does sw(0) */
	p->traploc = 0;
	do
		wait( CPU );
	while( hatebs() == ACTIVE );
}

trapped( t )
{
  	return p->state&ZOMBIE && p->traploc && 
		(((*p->traptype) & TRAP_BITS) == t);
}

call_step( pc )
long pc;
{
	long	oldsp = p->pcb.sp;
	int	afterjsr = pc + CALLLEN((char *) pc);
	char	save = *(char *) afterjsr;

	for( ;; ){
		*(char *) afterjsr = TRAP_BPT;
		traceoff();
		letrun();
		if( hatebs() != ERRORED )
			*(char *) afterjsr = save;
		if( !trapped(BPT_TRAP) )
			return;
		*p->traploc -= 1;
		*p->traptype ^= 0x00000078;	/* chng bkpt to trace */ 
		traceon();
		if( p->pcb.sp > oldsp ){	/* called recursively! */
			single( 0 );
			continue;
		}
		return;
	}
}

traceon()
{
	if (p->traploc)
		*p->traptype |= PSW_TRACE;
	else
		(p->pcb.psw) |= PSW_TRACE;
}

traceoff()
{
	if (p->traploc)
		*p->traptype &= ~PSW_TRACE;
	else
		(p->pcb.psw) &= ~PSW_TRACE;
}
	
single(limit)
register long limit;
{
	register char *startpc, *pc;

	switch( hatebs() ){
		default:	return;
		case BREAKPTED: *p->traploc -= 1;	/* bkpt is one byte */
		case STEPPED:	traceon(); break;
	}
	pc = startpc = *p->traploc;
	for( ;; ){
		if( limit && IS_JSR(*(char *)(pc)) )
			call_step( pc );
		else
			letrun();
		if( trapped( TRACE_TRAP) ){
			pc = *p->traploc;
			if( pc >= startpc && pc < (char *)limit ) continue;
		}
		traceoff();
		return;
	}
}

#define CBUFSZ 128

line()
{
	static char buf[CBUFSZ];
	static int i = 0;
	register char c;
	
	if( anticipate ){
		buf[i] = '\0';
		lprintf( "%s", buf );
		anticipate = 0;
	} else i = 0;
	for( ;; ){
		put( '_' );
		while( (c = kbdchar()) == CHARMINUS1 ){
			if( P->state & (RESHAPED|MOVED) ) put( '_' );
			if( enabled && p->state&ZOMBIE && limit-- > 1 ){
				liftbpts();
				run();
			} else if( enabled && (!(p->state&BUSY) ||
					     p->text !=txt || p->state&ZOMBIE )){
				put( '\v' );
				liftbpts();
				sendchar( ESCAPE );
				sendchar( DO_EVENT );
				sendchar( '\r' );
				anticipate = 1;
				enabled = 0;
				return;
			}
			if( (own()&MOUSE) && relbtn1() && (freehit(2) || freehit(3)) ){
				put( '\v' );
				sendchar( '\r' );
				anticipate = 1;
				return;
			}
			sleep( 6 );
		}
		lprintf( "\b_\b" );
		if( c == '\r' || c == '\n' ) break;
		if( c != '\b' && i < CBUFSZ )
			put( buf[i++] = c );
		else if( i > 0 ) lprintf( "\b%c\b", buf[--i] );
	}
	sendnchars( i, buf );
	sendchar( '\r' );
}

hosterr()
{
	lprintf( "host communication error!\n" );
}


laybpt(i)
{
	if( !bptloc[i] || hatebs() == ERRORED ) return;
	if (*bptloc[i] == TRAP_BPT)
	    lprintf( "breakpoint TRAP already in place: %D \n", bptloc[i] );
	bptsave[i] = *bptloc[i];	/* save instruction at bpt location */
	*bptloc[i] = TRAP_BPT;		/* put BPT trap code in memory */
}

liftbpt(i)
{
	if (!bptloc[i] || hatebs() == ERRORED)
		return;
	
	if (*bptloc[i] != TRAP_BPT)
		lprintf("breakpoint TRAP has been modified: %D\n", bptloc[i]);

	*bptloc[i] = bptsave[i];	/* restore original instruction */
}


laybpts()
{
	register int i;

	if( bptsw == DOWN || hatebs() == ERRORED ) return;
	for( i = 0; i < BPTS; ++i) laybpt(i);
	bptsw = DOWN;
}

liftbpts()
{
	register int i;

	if( bptsw == UP || hatebs() == ERRORED ) return;
	for( i = 0; i < BPTS; ++i ) liftbpt(i);
	bptsw = UP;
}


setbpt( i )
{
	bptloc[i] = (char *) write(loc);
	if( bptsw == DOWN ) laybpt( i );
}

clrbpt( i )
{
	if( bptsw == DOWN ) liftbpt( i );
	bptloc[i] = 0;
}

#define ARGSPACE 100

invokef()
{
	static struct Arg { char args[ARGSPACE]; } a;
	static struct Ret { char rets[ARGSPACE]; } r;
	static union Func {
		long (*scalar)();
		struct Ret (*retstr) ();
		long start;
	} f;
	register long adf;
	register z = p->state&ZOMBIE;
	register enum updown b = bptsw;

	p->state |= ZOMBIE;
	if( b == DOWN ) liftbpts();
	switch( adf = addrfromhost() ){
		case I_DATA:
			longtohost( (*f.scalar)(a) );
			break;
		case I_STRUCT:
			r = (*f.retstr)(a) ;
			longtohost(r.rets);
			break;
		default:
			f.start = adf;
			longtohost( a.args );
			break;
	}
	if( b == DOWN ) laybpts();
	if( !z ) p->state &= ~ZOMBIE;
}
