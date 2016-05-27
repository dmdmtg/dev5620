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
#	BELLMAC-32 LORDER MAKEFILE
#
#	@(#) makefile: 1.5 5/17/83
#
SGS=m32
SED=/bin/sed
SEDFLAGS=-e
SED_CMD=$(SED) $(SEDFLAGS)
#
#	Internal Directories
#
BASE= ../..
BINDIR= $(BASE)/xenv/m32/bin
COMLORDER= $(BASE)/lorder/common
#
all:		lorder
#
lorder:		$(COMLORDER)/lorder FRC
		@set -x; rm -f lorder.new; \
		$(SED_CMD) "s,BASEPATH,$(DMD),;s/SGS/$(SGS)/" \
				$(COMLORDER)/lorder > lorder.new; \
		if cmp lorder lorder.new >/dev/null 2>&1; \
		then \
			rm -f lorder.new; \
		else \
			rm -f lorder; mv lorder.new lorder; \
		fi

FRC:

#
install:	$(BINDIR)/$(SGS)lorder
#
$(BINDIR)/$(SGS)lorder:	lorder
		-rm -f $(BINDIR)/$(SGS)lorder
		cp lorder $(BINDIR)/$(SGS)lorder
		chmod 0755 $(BINDIR)/$(SGS)lorder
#
save:		$(BINDIR)/$(SGS)lorder
		-rm -f $(BINDIR)/$(SGS)lorder.back
		cp $(BINDIR)/$(SGS)lorder $(BINDIR)/$(SGS)lorder.back
#
stripit:	uninstall
uninstall:
		-rm -f $(BINDIR)/$(SGS)lorder
#
clean:		shrink
shrink:		
		-rm -f lorder
