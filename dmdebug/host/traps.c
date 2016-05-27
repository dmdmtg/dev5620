/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)traps.c	2.11);
*/

#include "common.h"
#include "../traps.h"
#include "user.h"
#include "../isp.h"
#include "frame.h"
#include "../menu.h"

MLONG bptloc[BPTS];

struct ramnl *bptsym[BPTS];
char bptscript[128];

setbptscript( s )
char *s;
{
	if( !s ) bptscript[0] = 0;
	else strcpy( bptscript, s );
}

/*	Return number of active breakpoints	*/

bptct()
{
	int ct = 0, i;

	for( i = 0; i < BPTS; ++i ) if( bptloc[i] ) ++ct;
	return ct;
}


bptstmt( file, line, setorclear )
char *file;
void (*setorclear)();
{
	struct ramnl *sline;

	if( !( sline = fileline( file, line ) ) ) return;
	(*setorclear)( sline->n_value, sline );
}

bptfunc( id, s_type, setorclear )
char *id;
void (*setorclear)();
{
	struct ramnl *b; 

	if( !(b = lookup( USER_MPX, s_type, id, 0 ))){
		if( lookup( USER_MPX, S_TEXT, id, 0 ) ){
			printf( ".bc and .br require -g tables\n" );
			printf( "use the .bi command\n" );
			return;
		}
		printf( "not found: %s\n", id );
		return;
	}
	(*setorclear)( b->n_value, b );
}

setbpt( loc, s )
MLONG loc;
struct ramnl *s;
{
	int i, bfree = -1;

	if( !loc ){
		printf( "cannot breakpoint (pc=%d)\n", loc );
		return 0;
	}
	for( i = 0; i < BPTS; ++i ){
		if( bptloc[i] == loc ){
			printf( "breakpoint already set (pc=%s)\n", doh(loc) );
			return 0;
		}
		if( bptloc[i] == 0 ) bfree = i;
	}
	if( bfree < 0 ){
		printf( "all %d breakpoints in use\n", BPTS );
		return 0;
	}
	if( region( USER, loc ) != N_TEXT )
		printf( "warning: breakpoint has been set outside user text!\n" );
	bptloc[bfree] = loc;
	bptsym[bfree] = s;
	addr_desc( loc, DO_BPTS );
	putchar( bfree );
	return 1;
}

clrhbpts()
{
	register int i;

	for( i = 0; i < BPTS; ++i ){
		bptloc[i] = 0;
		bptsym[i] = 0;
	}
}

clrbpt( loc )
MLONG loc;
{
	int i;
	
	for( i = 0; i < BPTS; ++i ) if( bptloc[i] == loc ){
		bptloc[i] = 0;
		bptsym[i] = 0;
		jerqdo( DO_BPTC );
		putchar( i );
		return 1;
	}
	printf( "breakpoint not set (pc=%s)\n", doh(loc) );
	return 0;
}

verifybpts()
{
	int i, ct = 0;
	struct ramnl *s;

	for( i = 0; i < BPTS; ++i ){
		if( bptloc[i] ){
			if( !(s = bptsym[i]) )
				printf( "%2d:      pc=%s\n", ++ct, doh(bptloc[i]));
			else
				switch( s->n_other ){
				default:
					wrap( 1 );
				case S_BFUN:
					printf( "%2d: call %s()\n", ++ct, s->n_name );
			      	break;
				case S_EFUN:
					printf( "%2d: ret  %s()\n", ++ct, s->n_name );
			      	break;
				case S_SLINE:
					printf( "%2d: stmt %s\n", ++ct, soline(s->n_value) );
			      	break;
				}
		}
	}
	if( ct == 0 ) printf( "no breakpoints\n" );
}


clrbpts()
{
	int i;

	for( i = 0; i < BPTS; ++i ) if( bptloc[i] ) clrbpt( bptloc[i] );
}

pcstepped( pc )
MLONG pc;
{
	struct ramnl *s = lookup( USER_MPX, S_BFUN, 0, pc );

	if( !train || !s ){
		train = 0;
		return;
	}
	while( train->callee ) train = train->callee;
	while( train ){
		if( train->bfun == s ){
			train->pc = pc;
			train->sline = lookup( USER_MPX, S_SLINE, 0, pc );
			return;
		}
		train = train->caller;
	}
	train = 0;
}

char	*invttype = "Invalid trap type";
		
hatebsmsg()
{
	long i;
	int	isc, ft;
	char *tname;
	MLONG traploc, pc;
	struct ramnl *s;
	char	*sop;

	if( oflag ){
		printf( "offline mode\n" );
		return;
	}

	hatebs = peeklong( HATEBS_INDEX );
	putchar( STATELINE );
	switch( hatebs ){
	default:
		printf( "internal error" );
		break;
	case ACTIVE:
		printf( "running" );
		break;
	case TRAPPED:
		i = peeklong(TYPE_INDEX);
		ft = i&0x3;
		isc = (i>>3)&0x0f;
		tname = isc < trapnames[ft].tcnt ?
			trapnames[ft].tname[isc] : invttype ;
		printf( "trap: %s: ", tname );
		context( train = framechain( 0 ), 0 );
		sop = fsoline( train );
		if( sop != missing )
			printf(" in %s", sop );
		break;
	case HALTED:
		printf( "halt: " );
		context( train = framechain( 0 ), 0 );
		sop = fsoline( train );
		if( sop != missing )
			printf(" in %s", sop );
		break;
	case STEPPED:
		pc = peeklong(TLOC_INDEX);
		pcstepped( pc );
		printf( "stepped: %s %s", soline(pc), srcline(pc) );
		break;
	case ERRORED:
		printf( "no layer" );
		clrhbpts();
		break;
	case BREAKPTED:
		traploc = peeklong(TLOC_INDEX) - 1;
		for( i = 0; i < BPTS; ++i )
			if( traploc == bptloc[i] ) break;
		if( i >= BPTS ) printf( "unexpected " );
		if( i >= BPTS || !(s = bptsym[i]) ){
			printf( "break: %s pc=%s", soline(traploc), doh(traploc) );
			train = framechain( 0 );
		} else {
			switch( s->n_other ){
			case S_SLINE:
				printf( "break: %s  %s", soline(s->n_value),
					srcline(s->n_value) );
				train = framechain( 0 );
				break;
			case S_BFUN:
				printf( "call: " );
				context( train = framechain( 0 ), 0 );
				printf(" in %s", fsoline( train ) );
				break;
			case S_EFUN:
/*				assert( s = lookup( table(s), II(S_GSYM,S_STSYM), s->n_name, 0 ) ); */
				assert( s = lookup( table(s), S_GSYM, s->n_name, 0 ) );
				train = framechain( 0 );
				printf( "return: %s from ",  fmtreturn(s) );
				context( train, 0 );
				printf(" in %s", fsoline( train ) );
				break;
			default:
				wrap( 1 );
			}
		}
		putchar( '\r' );
		stream(bptscript);
	}
	putchar( '\r' );
}



haltc()		/*	Halt an active process */
{
	if( hatebs != ACTIVE ) return;
	jerqdo( DO_HALT );
	hatebsmsg();
	jerqdo( DO_DISABLE );
}
	
goc(n)		/* Activate a halted process */
{
	if( n <= 0 ) return;
	switch( hatebs ){
		case ERRORED:
		case ACTIVE:
		case TRAPPED: return;
	}
	addr_desc( n, DO_LIMIT );
	jerqdo( DO_ACT );
	hatebs = ACTIVE;
	printf( "%crunning", STATELINE );
	if( n>1 ) printf( " (for %d breaks)", n );
	putchar( '\r' );
	train = 0;
	jerqdo( DO_ENABLE );
	if( n > 1 ) jerqdo( DO_ANTIC );
}

MLONG
singletrap()
{
	switch( peeklong( HATEBS_INDEX ) ){
	default:
		hatebsmsg();
		return 0;
	case HALTED:
		printf( "Single step may only be used when halted at a trap.\n" );
		printf( "Set a breakpoint. Go. Wait for trap. THEN single step.\n");
		return 0;
	case STEPPED:
		return peeklong(TLOC_INDEX);
	case BREAKPTED:
		return (peeklong(TLOC_INDEX) - 1);
	}
}

singlestep()
{
	MLONG p = peeklong( PROC_INDEX );
	MLONG fp;

	fp = peeklong( p+DMD_FP );
	jerqdo( DO_SING );
	if( (hatebs = peeklong( HATEBS_INDEX )) != STEPPED ){
		hatebsmsg();
		train = 0;
		return 0;
	}
	if( fp != peeklong( p+DMD_FP ) )
		train = 0;
	return 1;
}

singlec( instct )
{
	if( !instct ) return;
	if( !singletrap() ) return;
	addr_desc( 0, DO_LIMIT );
	while( instct-- )
		if( !singlestep() )
			return;

	{	MLONG savedot = dot;
		int savedotty = dotty;

		putchar( STATELINE );
		printf( "pc " );
		dotty = INSTDOT;
		dot = peeklong(TLOC_INDEX);
		showdot();
		dot = savedot;
		dotty = savedotty;
		putchar( '\r' );
	}
	jerqdo( DO_ANTIC );
}


MLONG next_stmt( pc )
MLONG pc;
{
	struct ramnl *s = lookup( USER, S_SLINE, 0, pc );
	
	if( !s ) return 0;
	do {
		s = s->n_thread;
	} while( s && s->n_value <= pc );
	if( !s ) return pc+100;		/* last statement in program! */
	return s->n_value;
}

cinglec( instct )
{
	MLONG pc;

	if( !instct ) return;
	while( instct-- ){
		if( !(pc = singletrap()) )
			return;
		if( !next_stmt( pc ) ){
			printf( "no tables for statement step\n" );
			return;
		}
		addr_desc( next_stmt(pc), DO_LIMIT );
		if( !singlestep() )
			return;
		pc = peeklong(TLOC_INDEX);
		if( !( lookup( USER, S_SLINE, 0, pc ) ) ){
			printf( "unexpected pc=%s\n", doh(pc) );
			hatebsmsg();
			return;
		}
	}
	hatebsmsg();
	jerqdo( DO_ANTIC );
}

char *fmtreturn(s)
struct ramnl *s;
{
	static struct ramnl fake[2];
	fake[0].n_desc = DECREF(s->n_desc);
	fake[0].n_other = S_RSYM;
	fake[0].n_value = ptregsave;
	fake[1] = *(s+1);			/* let display worry about it */
	switch( s->n_desc & BTMASK ){
	default:
		return "<C type err>";
	case VOID:
		return "<void>";
	case ENUMTY:
	case UCHAR:
	case CHAR:
	case USHORT:
	case SHORT:
	case UNSIGNED:
	case INT:
	case LONG:
	case ULONG:
		break;
	case STRTY:
		if( ISPTR(fake[0].n_desc) ) break;
		fake[0].n_other = S_GSYM;
		fake[0].n_value = peeklong( ptregsave );
	}
	return display( &fake[0], 0 );
}

#define CLEARALL	0
#define LISTALL		1
#define STMTLEVEL	2
#define CLEARSTMT	3
#define CLEARBOTH	4
#define SETBOTH		5

breakptmenu()
{
	struct ramnl *s, *bfun;
	int ct, hit = 0;

	scratch();
	if( !(s = bfun = lookup( USER, S_BFUN, "*", 0 ) ) ){
		printf( "missing tables\n" );
		return;
	}
	for( ;; ){
		scratch();
		for( s = bfun; s; s = s->n_thread )
			scrsort( fmt("%0.*s()\240", FLEX_SZ, s->n_name), s );
		ct = bptct();
		scrins( fmt( "clear all" ), CLEARALL );
		scrins( fmt( "list  [%d]", ct ), LISTALL );
		scrins( "stmt bpts", STMTLEVEL );
		switch( (long) (s = (struct ramnl *) (hit = scrhit(hit)) ) ){
		case -1:
			return;
		case LISTALL:
			verifybpts();
			break;
		case CLEARALL:
			if( menuconfirm() ){
				clrbpts();
				return;
			}
			break;
		case STMTLEVEL:
			stmtbptmenu();
			break;
		default:
			breakfunc( s );
		}
	}
}


breakfunc( b )
struct ramnl *b;
{
	struct ramnl *e;
	long i, call = 0, ret = 0, differ;

	m_menu( M_CALLRET, 0 );				
	assert( e = lookup( USER, S_EFUN, b->n_name, 0 ) );
	differ = b->n_value != e->n_value;
	for( i = 0; i < BPTS; ++i )
		if( bptsym[i] == b )
			call = 1;
		else
			if( bptsym[i] == e )
				ret = 1;
	i = 0;
	m_item( i++, call&&!ret ? ">call  " : " call  ", b );
	if( differ )
		m_item( i++, ret&&!call ? ">return" : " return", e );
	if( differ )
		m_item( i++, call&&ret ? ">both  " : " both  ", SETBOTH );
	m_item( i++, !call&&!ret ? ">none  " : " none  ", CLEARBOTH );
	m_null( i );
	if( (i = menuforce(M_CALLRET)) == -1 ) return;
	if( call )
		clrbpt( b->n_value );
	if( ret )
		clrbpt( e->n_value );
	switch( i = m_key(i) ){
	case CLEARBOTH:
		break;
	case SETBOTH:
		setbpt( b->n_value, b );
		setbpt( e->n_value, e );
		break;
	default:
		setbpt( ((struct ramnl *) i)->n_value, i );	/* i is (struct ramnl *) */
	}
}

struct ramnl *lastsline(s)
register struct ramnl *s;
{
	struct ramnl *stop, *sline = 0;

	assert( s->n_other == S_SO );
	stop = s->n_thread ? s->n_thread : stabtab[table(s)]->index;
	for( ++s; s < stop ; ++s )
		if( s->n_other == S_SLINE )
			sline = s;
	return sline;
}

struct ramnl *linemap[M_BVSIZE];

stmtbitvec(s)
struct ramnl *s;
{
	struct ramnl *last = lastsline(s);
	int i;

	if( last == 0 ) return 0;
	for( i = 0; i < M_BVSIZE; ++i ) linemap[i] = 0;
	for( ; s <= last; ++s ) if( s->n_other == S_SLINE
		 && s->n_desc < M_BVSIZE && !linemap[s->n_desc] )
			linemap[s->n_desc] = s;
	return 1;
}

stmtbptmenu()
{
	struct ramnl *so, *fso;
	int n, hit;

	if( !(fso = lookup(USER,S_SO,"*",0)) ) return;
	while( 1 ){
		scratch();
		for( so = fso; so; so = so->n_thread ){
			scrsort( basename(so->n_name), so );
		}
		if( (hit = scrhit(0)) == -1 ) return;
		so = (struct ramnl *) hit;
		if( !stmtbitvec(so) ){
			printf("no stmt bpt lines in %s\n", so->n_name);
			continue;
		}
		while( 1 ){
			if( (n = bv_force(linemap)) != -1 ) breakline(n);
			else break;
		}
	}
}

#define REACH	15
#define SHOW	4
#define STMTSET	(-2)
#define STMTCLR	(-3)
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))


breakline( n )
{
	MLONG	pc;
	int	i, ct;
	int	set = 0;
	struct ramnl *b = linemap[n];

	assert( b && b->n_other == S_SLINE );
	pc = b->n_value;
	printf( "%s %s\n", soline(pc), srcline(pc) );
	for( i = 0; i < BPTS; ++i ){
		if( bptsym[i] == b ){
			set = 1;
			break;
		}
	}
	scratch();
	scrapp( fmt( "%cbreak %d", set?'>':' ', b->n_desc ), STMTSET );
	scrapp( fmt( "%cclear %d", set?' ':'>', b->n_desc ), STMTCLR );
	switch( i = scrhit(0) ){
	case STMTSET:
		if( !set ) setbpt( b->n_value, b );
		break;
	case STMTCLR:
		if( set ) clrbpt( b->n_value );
		break;
	default:
		break;
	}
}

