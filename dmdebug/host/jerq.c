/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)jerq.c	2.3);
*/

#include "common.h"

void jerqdo( r )
{
	assert( !oflag );
	putchar( ESCAPE );
	putchar( r );
	flush();
}

char *jerqkbd( s )
char *s;
{
	char c;
	int i;

	assert( !oflag );
	jerqdo( DO_KBD );
	i = 0;
	for( c = getchar(); c != '\n' && c != '\r'; c = getchar() )
		if( c != '\b' )
			s[i++] = c;
		else
			assert( i-- );
	s[i] = '\0';
	return s;
}

void addr_desc( a, s ) MLONG a;
{
	char buf[8];
	
	assert( !oflag );
	flush();
	buf[0] =  ESCAPE;
	buf[1] = s;
	buf[2] = a>>24;
	buf[3] = a>>16;
	buf[4] = a>>8;
	buf[5] = a;
	write( 1, buf, 6 ); 
}

MLONG shiftfromjerq(i)
{
	long l = 0;

	assert( !oflag );
	while( i-- ) l = (l<<8) | (0xFF & getchar() );
	return l;
}

MLONG shifttojerq(x,n)
MLONG x;
{
	assert(!oflag);
	if( n > 3 ) putchar(x>>24);
	if( n > 2 ) putchar(x>>16);
	if( n > 1 ) putchar(x>>8);
	putchar(x);
}

MLONG longfromjerq()	{ return shiftfromjerq(4); }

MLONG shortfromjerq()	{ return shiftfromjerq(2); }

longtojerq(x)		{ shifttojerq(x,4); }

shorttojerq(x)		{ shifttojerq(x,2); }

MLONG peekbyte( b )
MLONG b;
{
	if( oflag ) return ofetch( b );
	addr_desc( b, PEEK_BYTE );
	return 0xFF & (MLONG) getchar();
}

MLONG peekshort( w )
MLONG w;
{
	if( oflag ) return (ofetch(w+1)<<8) | ofetch(w);
	addr_desc( w, PEEK_SHORT );
	return shortfromjerq();
}

MLONG peeklong( l )
MLONG l;
{
	if( oflag ) return (ofetch(l)<<16) | ofetch(l+2);
	addr_desc( l, PEEK_LONG );
	return longfromjerq();
}

char *peeknstr( s, n )
MLONG s;
{
	int  i = 0;
	char *buf = talloc(n+1);

	addr_desc( s, PEEK_STR );
	assert( n < 256 );
	putchar( n );
	flush();
	while( buf[i++] = getchar()){}
	return buf;
}

pokebwl( s, n, i, l )
MLONG n, i;
{

	assert( !oflag );
	addr_desc(n, s);
	shifttojerq( i, l );
}

void pokelong( a, i ) MLONG a, i; { pokebwl( POKE_LONG, a, i, 4 ); }
 	
void pokeshort( a, i ) MLONG a, i; { pokebwl( POKE_SHORT, a, i, 2 ); }

void pokebyte( a, i ) MLONG a, i; { pokebwl( POKE_BYTE, a, i, 1 ); }
