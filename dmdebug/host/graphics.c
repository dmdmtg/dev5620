/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)graphics.c	2.3);
*/

#include "common.h"

strop( id )
char *id;
{
	if( idmatch( id, "Bitmap" ) )	return G_BITMAP;
	if( idmatch( id, "Layer" ) )	return G_BITMAP;
	if( idmatch( id, "Point" ) )	return G_POINT;
	if( nfidmatch( id, "Rectangle") )	return G_RECTANGLE;
	if( idmatch( id, "Texture" )  )	return G_TEXTURE;
	if( nfidmatch( id, "Texture16") ) return G_16TEXTURE;
	return 0;
}

char *graphopnames( op )
{
	switch( op ){
	case G_BITMAP:		return "%bitblt(~)";
	case G_POINT:		return "%point(~)";
	case G_TEXTURE:		return "%texture(~)";
	case G_16TEXTURE:	return "%texture16(~)";
	case G_RECTANGLE:	return "%outline(~)";
	default:		return (char *)0;
	}
}

g_addr_desc( a, s )
MLONG a;
{
	if( !inmemory(a) ){
		printf( "%s cannot be applied at this address: %s\n",
			graphopnames( s ), doh(a) );
		return;
	}
	addr_desc( a, s );
}
