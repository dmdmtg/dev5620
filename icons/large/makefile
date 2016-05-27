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
STD=	banana bigswitch1 bigswitch2 boss clef clef1 cube cube1 cube2 digital \
	digital1 font fourarrows guitar homarauder letter letters menucursor \
	menucursors nfont nosmoking note1-1 note1-16 note1-2 note1-32 note1-4 \
	note1-8 note3-16 note3-32 note3-4 note3-8 pacman2 pacmen skull \
	smallclef smallclef1 strawberry sweepcursor switches tinynumbers \
	toggle1 toggle2 toggle3
all:

build:	install

install:
	-mkdir $(DMD)/icons/large
	-chmod $(MODE775) $(DMD)/icons/large
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/icons/large/$$i" || \
		    cp "$$i" "$(DMD)/icons/large/$$i";  \
		chmod $(MODE664) "$(DMD)/icons/large/$$i";  \
	done
clean:
