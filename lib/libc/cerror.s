#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	@(#)cerror.s	2.2
# C return sequence which
# sets errno, returns -1.
#
	global cerror
	comm errno,2

cerror:
	mov.w	%d0,errno
	mov.l	&-1,%d0
	unlk	%fp
	rts

