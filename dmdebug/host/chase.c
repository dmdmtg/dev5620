/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)chase.c	2.5);
*/

#include "common.h"
#include "expr.h"
#include "user.h"
#include "frame.h"

char *ops( c )
{
	switch( c ){
	case '>' : return "->";
	case '.' : return ".";
	case '*' : return "*";
	default  : wrap(1);
	}
	return "";
}

char *fmtminiexp( e )
struct expr *e;
{
	char *left, *right;

	if( !e ) return "<nil>";
	switch( (int) e->e_tag ){
	case E_SYM:
		return fmt( "%s", e->e_sym->n_name );
	case E_ID:
		return e->e_id;
	case E_CONST: return fmt( "%d", e->e_rvalue );
	case E_UNARY :
		assert( e->e_op == '*' );
		return fmt( "*%s", fmtminiexp(e->e_left) );
	case E_BINARY:
		left = fmtminiexp(e->e_left);
		if( e->e_op == '(' )
			return fmt("%s(%s)", left, fmtminiexp(e->e_right->e_left));
		right = fmtminiexp(e->e_right);
		if( e->e_left->e_op == '*' ) left = fmt( "(%s)", left );
		if( e->e_op == '[' )
			return fmt( "%s[%s]", left, right);
		return fmt( "%s%s%s", left, ops(e->e_op), right);
	default: wrap( 1 );
	}
	return "";
}

char *fmttypminiexp( e )
struct expr *e;
{
	struct ramnl s[2];

	s[0].n_desc = e->e_mcc;
	s[1] = *e->e_tyid;
	return fmt( "%s: %s", mcctype(&s[0]), fmtminiexp(e) );
}

#define estr fmtminiexp(e)
#define typestr fmttypminiexp(e)

chasesym( s )
struct ramnl *s;
{
	chase( enode( E_SYM, s ) );
}

chase( e )
struct expr *e;
{
	if( !eval(e) ) return;
	switch( e->e_mcc & C_TMASK ){
	case PTR:
		chaseptr( e );
		return;
	case FTN:
		printf( "%s=<function?>\n", typestr );
		return;
	case ARY:
		chaseary( e );
		return;
	case 0:
		switch( e->e_mcc ){
		case UNIONTY:
		case STRTY:
			chasestrty( e );
			return;
		case ENUMTY:
			chaseenumty( e );
			return;
		case CHAR:
			printf( "%s=%s=%d\n", typestr, fmtchar((char)e->e_rvalue),
				(char) e->e_rvalue );
			return;
		case UCHAR:
			printf( "%s=%s=%u\n", typestr, fmtchar((char)e->e_rvalue), e->e_rvalue );
			return;
		case SHORT:
			printf( "%s=%d\n", typestr, e->e_rvalue );
			return;
		case USHORT:
			printf( "%s=%u\n", typestr, e->e_rvalue );
			return;
		case INT:
		case LONG:
			printf( "%s=%ld\n", typestr, e->e_rvalue );
			return;
		case UNSIGNED:
		case ULONG:
			printf( "%s=%lu\n", typestr, e->e_rvalue );
			return;
		case DOUBLE:
		default:
			printf( "%s=<unimplemented>\n", typestr );
			return;
		}
	}
}

chaseenumty( e )
struct expr *e;
{
	struct ramnl *s = e->e_tyid;

	assert( e->e_mcc == ENUMTY );
	if( s->n_name[0] == '\0' ){
		enumerr( e );
		return;
	}
	s = lookup( table(s), S_BENUM, s->n_name, 0 );
	if( !s ){
		enumerr( e );
		return;
	}
	for( ++s; s->n_other != S_EENUM; ++s )
		if( s->n_other == S_ENUM && s->n_value == e->e_rvalue ){
			printf( "%s=%s\n", typestr, s->n_name );
			return;
	}
	enumerr( e );
}

enumerr( e )
struct expr *e;
{
	printf( "%s=%d\n", typestr, e->e_rvalue );
}

chaseptr( e )
struct expr *e;
{
	long bt = DECREF( e->e_mcc ), r = e->e_rvalue;
	struct ramnl *s;

	assert( ISPTR(e->e_mcc) );
	printf( "%s=%s", typestr, doh(r) );
	if( !inmemory(r) ){
		if( r ) printf( " (not a valid address)" );
		putchar( '\n' );
		return;
	}
	if( ISFTN(bt) ){
		if( (s = lookup(USER_MPX,S_GSYM,0,e->e_rvalue ))
		 && s->n_value == e->e_rvalue )
			printf( "=%s()", s->n_name );
		putchar( '\n' );
		return;
	}
	putchar( '\n' );
	if( bt == STRTY )
		chptrstrty( e );
	else
		chaseary( e );
}

chptrstrty( e )
struct expr *e;
{
	int op;
	struct expr *arg, *fun;

	for( ;; ){
		switch( op = selectfield( e, '>' ) ){
		case -1: return;
		case  0:
			e = enode( E_UNARY, '*', e );
			printf( "%s=", estr );
			exprc( e );
			e = e->e_left;
			break;
		case '[':
			chaseary( e );
			break;
		default:
			if( graphopnames(op) )
				g_addr_desc( e->e_rvalue, op );
			else{
				arg = enode( E_BINARY, e, ',', 0 );
				fun = enode( E_ID, ((struct ramnl *) op)->n_name );
				chase( enode(E_BINARY, fun, '(', arg));
			}
		}
	}
}

chasestrty( e )
struct expr *e;
{
	int op, i, n;
	struct expr *arg, *fun;
	MLONG argarea;		/* use arg area for scratch space */

	for( ;; ){
		switch( op = selectfield( e, '.' ) ){
		case -1: return;
		case  0:
			printf( "%s=", estr );
			exprc( e );
			break;
		default:
			if( graphopnames(op) ){
			    if( e->e_hostr ){
				e->e_hostr = 0;
				n = emccsize(e);
				addr_desc(0,DO_INVOKE);
				argarea = longfromjerq();
				for( i = 0; i < n; ++i )
				   pokebyte(argarea+i, *(char*)(e->e_lvalue+i));
				e->e_lvalue = argarea;
			    }
			    g_addr_desc( e->e_lvalue, op );
			}
			else{
				arg = enode( E_BINARY, e, ',', 0 );
				fun = enode( E_ID, ((struct ramnl *) op)->n_name );
				chase( enode(E_BINARY, fun, '(', arg));
			}
		}
	}
}

selectfield( e, op )
struct expr *e;
{
	struct ramnl *s = e->e_tyid, *is;
	struct expr *eid;
	char *field, *strname;
	long i = 0;
	int	gop;

	strname = s->n_name;
	if( strname[0] == '\0' ){
		printf("forward structure reference\n");
		s = lookup( USER, S_BSTR, "*", 0 );
		assert(s);
		scratch();
		for( ; s; s = s->n_thread )
			scrsort( fmt( "%-*.*s", FLEX_SZ, FLEX_SZ, s->n_name ), s );
		if( ( i = scrhit(0) ) == -1 ) return ptrstrtyerr( e );
		s = (struct ramnl *) i;
		e->e_tyid->n_name = s->n_name; /* may need to generate tyid on fly*/
	} else {
		s = lookup( table(s), S_BSTR, strname, 0 );
		if( !s ) return ptrstrtyerr( e );
	}
	for( ;; ){
		scratch();
		if( op == '>' ) scrapp( "~[ ? ]", '[' );
		if( op == '>' ) scrapp( "*~", '*' );
		scrapp( fmt( "%0.*s{~}", FLEX_SZ, s->n_name), 0 );
		for( is = s+1; is->n_other != S_ESTR; ++is ){
			if( is->n_other == S_SSYM )
				scrapp( fmt("~%s%0.*s", ops(op), FLEX_SZ, is->n_name), is );
		}
		if( gop = strop( strname ) )
			scrapp( graphopnames(gop), gop );
		mapscrapp( strname, op=='>' ? INCREF(STRTY) : STRTY );
		printf( "%s ?", typestr );
		i = scrhit( i );
		putchar( '\v' );
		switch( i ){
		case '*':						/* *~ */
			chase( enode( E_UNARY, '*', e ) );
			continue;
		case  0 :						/* {~} */
		case '[':						/* ~[?] */
		case -1 :						/* none */
			return i;
		}
		if( graphopnames(i) )				/* %graphics(~) */
			return i;
		if( ((struct ramnl*) i)->n_other == S_BFUN )		/* f(~) */
			return i;
		field = fmt( "%s", ((struct ramnl *)i)->n_name );	/* ->, . */
		eid = enode( E_ID, field );
		chase( enode( E_BINARY, e, op, eid ) );
	}
}

ptrstrtyerr( e )
struct expr *e;
{
	printf( "%s=<structure error>\n", estr );
	return -1;
}


#define LO (-4)
#define HI 128
#define LOOPLENGTH 32
#define SINGLE_SUB 1
#define LOOP_SUB 2
#define FULL_STRING 3
chaseary( e )
struct expr *e;
{
	long i, lo, hi, p;
	struct expr *sub;

	scratch();
	scrapp( "~[ ? ]", SINGLE_SUB );
	scrapp( "for( ? ) ~[]", LOOP_SUB );
	if( e->e_mcc == (ARY|CHAR) || e->e_mcc == (PTR|CHAR) ){
		p = e->e_mcc == (ARY|CHAR) ? e->e_lvalue : e->e_rvalue;
		scrapp( fmtshortstr(p), FULL_STRING );
	}
	printf( "%s ?", typestr );
	i = scrhit(0);
	putchar( '\v' );
	switch( i ){
	default: return;
	case FULL_STRING:
		printf( "%s=%s\n", estr, fmtstring(p) );
		return;
	case SINGLE_SUB:
		for(;;) {
			printf( "%s[ ? ]", estr );
			i = m_range(LO,HI,LO-1);
			putchar( '\v' );
			if( i == LO-1 ) return;
			chase( enode( E_BINARY, e, '[', enode(E_CONST,i) ) );
		}
	case LOOP_SUB:
		for( ;; ){
			printf( "for($i= ? ;...) %s[$i]", estr );
			lo = m_range(LO,HI,LO-1);
			putchar( '\v' );
			if( lo == LO-1 ) return;
			printf( "\vfor($i=%d;$i<= ? ;++$i) %s[$i]", lo, estr );
			hi = m_range(lo,lo+LOOPLENGTH,lo-1);
			putchar( '\v' );
			if( hi == lo-1 ) return;
			sub = enode(E_BINARY, e, '[', enode(E_CONST, 0));
			for( i = lo; i <= hi; ++i ){
				sub->e_right->e_rvalue = i;
				printf( "%s=", fmtminiexp(sub) );
				exprc( sub );
			}
		}
	}
}


