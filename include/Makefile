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
MODE775=755
MODE664=644
STD=	blit.h blitio.h dmd.h dmdio.h dmdproc.h duart.h font.h jerq.h\
	jerqio.h jerqproc.h kbd.h keycodes.h layer.h line.h mpx.h \
	msgs.h pandora.h queue.h quiet.h sa.h sccsid.h setup.h
SYS=	sccsid.h 2681.h xt.h xtproto.h
SGSINC= a.out.h aouthdr.h bool.h filehdr.h ldfcn.h linenum.h patch.h paths.h \
	reloc.h scnhdr.h sdp2.h sdp3.h sgs.h sgsmacros.h storclass.h syms.h \
	ctype.h tv.h
all:

build:	install

strip:
	-rm -rf $(DMD)/include

install:
	-mkdir $(DMD)/include
	-chmod $(MODE775) $(DMD)/include
	-mkdir $(DMD)/include/sys
	-chmod $(MODE775) $(DMD)/include/sys
	-mkdir $(DMD)/include/sgs
	-chmod $(MODE775) $(DMD)/include/sgs
	-for i in ${STD}; do \
		cmp -s $$i $(DMD)/include/$$i || \
		    cp $$i $(DMD)/include/$$i; \
		chmod $(MODE664) $(DMD)/include/$$i; \
	done
	-(cd sys; for i in ${SYS}; do \
		cmp -s $$i $(DMD)/include/sys/$$i || \
		    cp $$i $(DMD)/include/sys/$$i; \
		chmod $(MODE664) $(DMD)/include/sys/$$i; \
	done)
	-(cd sgs; rm -f paths.new; \
		sed 's,BASEPATH,$(DMD),' paths.base >paths.new; \
		if cmp -s paths.new paths.h; \
		then \
			rm -f paths.new; \
		else \
			rm -f paths.h; mv paths.new paths.h; \
		fi; \
		for i in ${SGSINC}; do \
		    cmp -s $$i $(DMD)/include/sgs/$$i || \
			cp $$i $(DMD)/include/sgs/$$i; \
		    chmod $(MODE664) $(DMD)/include/sgs/$$i; \
	done)
clean:
