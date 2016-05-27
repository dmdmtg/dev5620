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
#	BELLMAC-32 COMPRESS MAKEFILE
#
#	@(#) makefile: 1.11 4/6/84
#
SGS=m32
CC=cc
DMD= /usr/local/dmd
EXTRACFLAGS=-O
CFLAGS=-c -DDMD=\"$(DMD)\" $(EXTRACFLAGS)
ARCH=AR32WR
#	Set FLEX to -DFLEXNAMES for flexnames (post 6.0)
FLEX= -DFLEXNAMES
DEFLIST=-D$(ARCH) -DTS $(FLEX)
INCLIST=-I$(COMCPRS) -I$(COMINC) -I$(SDPINC) -I$(USRINC)
ENV=
CC_CMD=$(CC) $(CFLAGS) $(DEFLIST) $(INCLIST) $(ENV)
#
LD=$(CC)
LDFLAGS=
LD_CMD=$(LD) $(LDFLAGS)
#
STRIP=strip
SPFLAGS=
STRIP_CMD=$(STRIP) $(SPFLAGS)
#
LINT=lint
LINTFLAGS=-p
LINT_CMD=$(LINT) $(LINTFLAGS)
#
#	Internal Directories
#
BASE= ../..
BINDIR= $(BASE)/xenv/m32/bin
LIBDIR= $(BASE)/xenv/m32/lib
COMINC= $(BASE)/inc/common
M32INC= $(BASE)/inc/m32
COMCPRS= $(BASE)/compress/common
SDPINC= $(BASE)/sdp/common
ROOT=
VERSION=
USRINC=$(ROOT)/usr/$(VERSION)include
#
LIBSDP	= $(BASE)/sdp/m32/sdp.a
LIBLD	= $(BASE)/libld/m32/libld.a
LIBLIST=$(LIBLD) $(LIBSDP)
OBJECTS= tstc.o pass1.o mid.o pass2.o copy.o
#
#
all:	cprs
#
cprs:	$(OBJECTS) $(LIBLIST)
	$(LD_CMD) -o cprs $(OBJECTS) $(LIBLIST)
#
tstc.o:	$(COMINC)/filehdr.h $(COMINC)/storclass.h $(COMINC)/syms.h \
	$(COMINC)/ldfcn.h $(COMCPRS)/tstc.c $(COMCPRS)/sdp1.h $(SDPINC)/sdp.h
	$(CC_CMD) $(COMCPRS)/tstc.c
#
pass1.o:	$(COMINC)/filehdr.h $(COMINC)/storclass.h $(COMINC)/syms.h \
		$(COMINC)/ldfcn.h $(COMCPRS)/tagitem.h $(COMCPRS)/pass1.c \
		$(SDPINC)/sdp.h $(COMCPRS)/sdp1.h
	$(CC_CMD) $(COMCPRS)/pass1.c
#
mid.o:	$(COMINC)/storclass.h $(COMINC)/syms.h $(COMCPRS)/tagitem.h \
	$(COMCPRS)/mid.c $(COMCPRS)/sdp1.h $(SDPINC)/sdp.h
	$(CC_CMD) $(COMCPRS)/mid.c
#
pass2.o:	$(COMINC)/filehdr.h $(COMINC)/storclass.h $(COMINC)/syms.h \
		$(COMINC)/scnhdr.h $(COMINC)/linenum.h $(COMINC)/reloc.h \
		$(COMINC)/ldfcn.h $(COMCPRS)/tagitem.h $(COMCPRS)/pass2.c
	$(CC_CMD) $(COMCPRS)/pass2.c
#
copy.o:	$(COMINC)/filehdr.h $(COMINC)/scnhdr.h $(COMINC)/reloc.h \
	$(COMINC)/storclass.h $(COMINC)/syms.h $(COMINC)/linenum.h \
	$(COMINC)/ldfcn.h $(COMCPRS)/copy.c
	$(CC_CMD) $(COMCPRS)/copy.c
#
#
install:	$(BINDIR)/$(SGS)cprs
#
$(BINDIR)/$(SGS)cprs:	cprs
	-rm -f $(BINDIR)/$(SGS)cprs
	cp cprs $(BINDIR)/$(SGS)cprs
	-$(STRIP_CMD) $(BINDIR)/$(SGS)cprs
#
save:	$(BINDIR)/$(SGS)cprs
	-rm -f $(BINDIR)/$(SGS)cprs.back
	cp $(BINDIR)/$(SGS)cprs $(BINDIR)/$(SGS)cprs.back
#
stripit:	uninstall
uninstall:
	-rm -f $(BINDIR)/$(SGS)cprs
#
clean:	shrink
shrink:
	-rm -f $(OBJECTS) cprs
#
lint:	$(COMINC)/filehdr.h $(COMINC)/ldfcn.h $(COMINC)/linenum.h \
	$(COMINC)/reloc.h $(COMINC)/scnhdr.h $(COMINC)/storclass.h \
	$(COMINC)/syms.h $(COMCPRS)/tagitem.h \
	$(M32INC)/paths.h $(COMCPRS)/tstc.c $(COMCPRS)/pass1.c \
	$(COMCPRS)/mid.c $(COMCPRS)/pass2.c $(COMCPRS)/copy.c
	$(LINT_CMD) $(DEFLIST) $(INCLIST) $(COMCPRS)/*.c
