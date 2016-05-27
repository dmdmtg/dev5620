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
STD=	acsnet adm ap bart bbc bgs bin bwk chaos cow daemon dan davef dectalk \
	dmr ecc jdj jerq ken mailerdaemon mandrill ojb owl1 owl2 owl3 rob root \
	ross sys turkey unknown uucp
all:

build:	install

install:
	-mkdir $(DMD)/icons/face48
	-chmod $(MODE775) $(DMD)/icons/face48
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/icons/face48/$$i" || \
		    cp "$$i" "$(DMD)/icons/face48/$$i";  \
		chmod $(MODE664) "$(DMD)/icons/face48/$$i";  \
	done
clean:
