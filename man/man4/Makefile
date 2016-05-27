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
MDIR=	$(DMD)/man/man4
MODE664=644
SRCS=	dmda.out.4

all:

clean:

install: all
	-mkdir $(MDIR)
	cp $(SRCS) $(MDIR)
	chmod $(MODE664) $(MDIR)/*
