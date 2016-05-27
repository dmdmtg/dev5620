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
#	BELLMAC-32 INCLUDE MAKEFILE
#
#	@(#) makefile: 1.5 4/21/83
#
#
#	Internal Directories
#
BASE= ../..
BINDIR=$(BASE)/xenv/m32/bin
LIBDIR=$(BASE)/xenv/m32/lib
INCDIR=$(BASE)/xenv/m32/inc
COMINC= $(BASE)/inc/common
#
paths.h: 	paths.base FRC
		@set -x; rm -f paths.new; \
		sed 's,BASEPATH,$(DMD),' paths.base >paths.new; \
		if cmp paths.new paths.h >/dev/null 2>&1; \
		then \
			rm -f paths.new; \
		else \
			rm -f paths.h; mv paths.new paths.h; \
		fi
		
FRC:
	
install:

XX		: $(INCDIR)/filehdr.h $(INCDIR)/ldfcn.h $(INCDIR)/linenum.h \
		$(INCDIR)/sgsmacros.h $(INCDIR)/reloc.h $(INCDIR)/scnhdr.h \
		$(INCDIR)/sdp2.h $(INCDIR)/sdp3.h $(INCDIR)/storclass.h \
		$(INCDIR)/syms.h $(INCDIR)/paths.h \
		$(INCDIR)/aouthdr.h $(INCDIR)/ar.h \
		$(INCDIR)/bool.h $(INCDIR)/patch.h \
		$(INCDIR)/sgs.h $(INCDIR)/tv.h
#
$(INCDIR)/aouthdr.h: $(COMINC)/aouthdr.h
		-rm -f $(INCDIR)/aouthdr.h
		cp $(COMINC)/aouthdr.h $(INCDIR)/aouthdr.h
$(INCDIR)/ar.h: $(COMINC)/ar.h
		-rm -f $(INCDIR)/ar.h
		cp $(COMINC)/ar.h $(INCDIR)/ar.h
$(INCDIR)/bool.h: $(COMINC)/bool.h
		-rm -f $(INCDIR)/bool.h
		cp $(COMINC)/bool.h $(INCDIR)/bool.h
$(INCDIR)/patch.h: $(COMINC)/patch.h
		-rm -f $(INCDIR)/patch.h
		cp $(COMINC)/patch.h $(INCDIR)/patch.h
$(INCDIR)/filehdr.h: $(COMINC)/filehdr.h
		-rm -f $(INCDIR)/filehdr.h
		cp $(COMINC)/filehdr.h $(INCDIR)/filehdr.h
$(INCDIR)/ldfcn.h: $(COMINC)/ldfcn.h
		-rm -f $(INCDIR)/ldfcn.h
		cp $(COMINC)/ldfcn.h $(INCDIR)/ldfcn.h
$(INCDIR)/scnhdr.h: $(COMINC)/scnhdr.h
		-rm -f $(INCDIR)/scnhdr.h
		cp $(COMINC)/scnhdr.h $(INCDIR)/scnhdr.h
$(INCDIR)/syms.h: $(COMINC)/syms.h
		-rm -f $(INCDIR)/syms.h
		cp $(COMINC)/syms.h $(INCDIR)/syms.h
$(INCDIR)/reloc.h: $(COMINC)/reloc.h
		-rm -f $(INCDIR)/reloc.h
		cp $(COMINC)/reloc.h $(INCDIR)/reloc.h
$(INCDIR)/linenum.h: $(COMINC)/linenum.h
		-rm -f $(INCDIR)/linenum.h
		cp $(COMINC)/linenum.h $(INCDIR)/linenum.h
$(INCDIR)/storclass.h: $(COMINC)/storclass.h
		-rm -f $(INCDIR)/storclass.h
		cp $(COMINC)/storclass.h $(INCDIR)/storclass.h
$(INCDIR)/sgsmacros.h: $(COMINC)/sgsmacros.h
		-rm -f $(INCDIR)/sgsmacros.h
		cp $(COMINC)/sgsmacros.h $(INCDIR)/sgsmacros.h
$(INCDIR)/sdp2.h: $(COMINC)/sdp2.h
		-rm -f $(INCDIR)/sdp2.h
		cp $(COMINC)/sdp2.h $(INCDIR)/sdp2.h
$(INCDIR)/sdp3.h: $(COMINC)/sdp3.h
		-rm -f $(INCDIR)/sdp3.h
		cp $(COMINC)/sdp3.h $(INCDIR)/sdp3.h
$(INCDIR)/sgs.h: sgs.h
		-rm -f $(INCDIR)/sgs.h
		cp sgs.h $(INCDIR)/sgs.h
$(INCDIR)/tv.h: tv.h
		-rm -f $(INCDIR)/tv.h
		cp tv.h $(INCDIR)/tv.h
$(INCDIR)/paths.h: paths.h
		-rm -f $(INCDIR)/paths.h
		cp paths.h $(INCDIR)/paths.h
#
save:			$(INCDIR)/filehdr.h $(INCDIR)/ldfcn.h $(INCDIR)/scnhdr.h \
	$(INCDIR)/syms.h $(INCDIR)/reloc.h $(INCDIR)/linenum.h $(INCDIR)/sgs.h \
	$(INCDIR)/storclass.h $(INCDIR)/tv.h $(INCDIR)/paths.h $(INCDIR)/sdp2.h \
	$(INCDIR)/sgsmacros.h $(INCDIR)/sdp3.h
		-rm -f $(INCDIR)/filehdr.h.back
		cp $(INCDIR)/filehdr.h $(INCDIR)/filehdr.h.back
		-rm -f $(INCDIR)/ldfcn.h.back
		cp $(INCDIR)/ldfcn.h $(INCDIR)/ldfcn.h.back
		-rm -f $(INCDIR)/scnhdr.h.back
		cp $(INCDIR)/scnhdr.h $(INCDIR)/scnhdr.h.back
		-rm -f $(INCDIR)/syms.h.back
		cp $(INCDIR)/syms.h $(INCDIR)/syms.h.back
		-rm -f $(INCDIR)/reloc.h.back
		cp $(INCDIR)/reloc.h $(INCDIR)/reloc.h.back
		-rm -f $(INCDIR)/linenum.h.back
		cp $(INCDIR)/linenum.h $(INCDIR)/linenum.h.back
		-rm -f $(INCDIR)/storclass.h.back
		cp $(INCDIR)/storclass.h $(INCDIR)/storclass.h.back
		-rm -f $(INCDIR)/sgs.h.back
		cp $(INCDIR)/sgs.h $(INCDIR)/sgs.h.back
		-rm -f $(INCDIR)/tv.h.back
		cp $(INCDIR)/tv.h $(INCDIR)/tv.h.back
		-rm -f $(INCDIR)/paths.h.back
		cp $(INCDIR)/paths.h $(INCDIR)/paths.h.back
		-rm -f $(INCDIR)/sgsmacros.h.back
		cp $(INCDIR)/sgsmacros.h $(INCDIR)/sgsmacros.h.back
		-rm -f $(INCDIR)/sdp2.h.back
		cp $(INCDIR)/sdp2.h $(INCDIR)/sdp2.h.back
		-rm -f $(INCDIR)/sdp3.h.back
		cp $(INCDIR)/sdp3.h $(INCDIR)/sdp3.h.back
#
stripit:	uninstall
uninstall:
		-rm -f $(INCDIR)/filehdr.h
		-rm -f $(INCDIR)/ldfcn.h
		-rm -f $(INCDIR)/scnhdr.h
		-rm -f $(INCDIR)/syms.h
		-rm -f $(INCDIR)/reloc.h
		-rm -f $(INCDIR)/linenum.h
		-rm -f $(INCDIR)/storclass.h
		-rm -f $(INCDIR)/sgs.h
		-rm -f $(INCDIR)/tv.h
		-rm -f $(INCDIR)/paths.h
		-rm -f $(INCDIR)/sgsmacros.h
		-rm -f $(INCDIR)/sdp2.h
		-rm -f $(INCDIR)/sdp3.h
#
shrink		:
