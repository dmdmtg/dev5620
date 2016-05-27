/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)data.c	2.5);

#include <dmd.h>
#include <dmdio.h>

char _sibuf[BUFSIZ], _sobuf[BUFSIZ], _sebuf[BUFSIZ];

struct	_iobuf	_iob[_NFILE] ={
	{ 0, _sibuf, _sibuf, _IOREAD, 0},
	{ BUFSIZ, _sobuf, _sobuf, _IOWRT+_IOTTY, 1},
	{ BUFSIZ, _sebuf, _sebuf, _IOWRT+_IOTTY, 2},
};
/*
 * Ptr to end of buffers
 */
struct	_iobuf	*_lastbuf ={ &_iob[_NFILE] };
