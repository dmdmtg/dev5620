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
MODE775=755
MODE664=644
MDIR=	$(DMD)/man
DIRS=	man1 man3 man4 man5

all:	subdir

strip:

subdir: FRC
	for i in $(DIRS); do \
		(cd $$i; make $(MFLAGS) DMD=$(DMD) MODE775="$(MODE775)" MODE664="$(MODE664)"); \
	done

install: all
	-mkdir $(MDIR) 
	-chmod $(MODE775) $(MDIR)
	for i in $(DIRS); do \
		(cd $$i; make $(MFLAGS) MODE664="$(MODE664)" MODE775="$(MODE775)" DMD=$(DMD) install); \
	done

clean: FRC
	for i in $(DIRS); do \
		(cd $$i; make $(MFLAGS) clean); \
	done

FRC:
