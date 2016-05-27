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
STD=	bats bighex bigweave black chainmail checks cobblestone crabcan1 \
	crabcan2 crabcan3 crabtweed darkgrey dashes diag1:3 diag2:2 diag3:1 \
	diagweave eight1 eight2 el ellipse escherfish16 escherfish8 fence1 \
	fence2 fence3 fishes freckles grey greysun hex horbar1:1 inversegrey \
	ironcoat kapow lightgrey money plaid4:4 plaid8:8 six small+bighex \
	smallhex smile snake spiral squareknot stars stars1 texture.icon \
	tweed tweed+cross tweed+plus2:2 tweed+plus4:3 tweed+plus4:4 \
	tweed+plus5:5 tweeddish ubalu ubalu2 vampire verbar1:1 verbar1:3 \
	verbar2:2 verbar3:1 verbar4:4 vertigo vibration weave weave2 white \
	wiggly yin-yang
all:

build:	install

install:
	-mkdir $(DMD)/icons/texture16
	-chmod $(MODE775) $(DMD)/icons/texture16
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/icons/texture16/$$i" || \
		    cp "$$i" "$(DMD)/icons/texture16/$$i";  \
		chmod $(MODE664) "$(DMD)/icons/texture16/$$i";  \
	done
clean:
