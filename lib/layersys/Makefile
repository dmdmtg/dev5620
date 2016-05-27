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
# Doing a make install builds $(DMD)/include
#
#
DMD=/usr/local/dmd
MODE664=644
MODE775=755
STD=	lsys.8\;7\;5 lsys.8\;7\;3 

all:

build:	install

install:
	-mkdir $(DMD)/lib
	-chmod $(MODE775) $(DMD)/lib
	-mkdir $(DMD)/lib/layersys
	-chmod $(MODE775) $(DMD)/lib/layersys
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/lib/layersys/$$i" || \
		    cp "$$i" "$(DMD)/lib/layersys/$$i";  \
		chmod $(MODE664) "$(DMD)/lib/layersys/$$i";  \
	done
clean:
