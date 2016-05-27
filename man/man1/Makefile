# 
#									
#	Copyright (c) 1987,1988,1989,1990,1991,1992   AT&T		
#			All Rights Reserved				
#									
#	  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T.		
#	    The copyright notice above does not evidence any		
#	   actual or intended publication of such source code.		
#									
# 
DMD=	/usr/local/dmd
MODE664=644
MDIR=	$(DMD)/man/man1
SRCS=	dmdcat.1 dmdcc.1 dmdebug.1 m32ld.1 \
	icon.1 jim.1 jim.recover.1 jx.1 \
	m32as.1 m32conv.1 m32cprs.1 m32dis.1 m32dump.1 \
	m32ld.1 m32list.1 m32lorder.1 m32nm.1 m32size.1 m32strip.1

all:

clean:

install: all
	-mkdir $(MDIR)
	cp $(SRCS) $(MDIR)
	chmod $(MODE664) $(MDIR)/*
