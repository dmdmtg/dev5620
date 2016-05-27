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
#
#
DMD=/usr/local/dmd
MODE664=644
MODE775=755
MAKEARGS= $(MFLAGS) DMD="$(DMD)" MODE664="$(MODE664)" MODE775="$(MODE775)"

all:

lint:

build:

strip:	FRC
	-rm -rf $(DMD)/icons

install: FRC
	-mkdir $(DMD)/icons
	-chmod $(MODE775) $(DMD)/icons
	cd 16x16; make $(MAKEARGS) install
	cd face48; make $(MAKEARGS) install
	cd large; make $(MAKEARGS) install
	cd texture16; make $(MAKEARGS) install
clean:
	cd 16x16; make $(MAKEARGS) clean
	cd face48; make $(MAKEARGS) clean
	cd large; make $(MAKEARGS) clean
	cd texture16; make $(MAKEARGS) clean
FRC:
