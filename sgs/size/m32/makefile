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
#	BELLMAC-32 SIZE MAKEFILE
#
#	@(#) makefile: 1.10 9/15/83
#
SGS=m32
CC=cc
DMD= /usr/local/dmd
EXTRACFLAGS=-O
CFLAGS=-c -DDMD=\"$(DMD)\" $(EXTRACFLAGS)
ARCH=AR32WR
#	Set ARFORMAT to "PORTAR" for portable archive format (post 5.0)
#	Set ARFORMAT to OLDAR for pre-5.0 archive format
ARFORMAT=PORTAR
#	Set FLEX to -DFLEXNAMES for flexnames (post 6.0)
FLEX= -DFLEXNAMES
DEFLIST=-D$(ARCH) -D$(ARFORMAT) -DUNIX $(FLEX)
INCLIST=-I$(M32INC) -I$(COMINC) -I$(COMSIZE) -I$(USRINC)
ENV=
CC_CMD=$(CC) $(CFLAGS) $(DEFLIST) $(INCLIST) $(ENV)
#
LD=$(CC)
LDFLAGS=$(FFLAG)
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
#	External Directories
#
ROOT=
VERSION=
USRINC= $(ROOT)/usr/$(VERSION)include
#
#	Internal Directories
#
BASE= ../..
BINDIR= $(BASE)/xenv/m32/bin
LIBDIR= $(BASE)/xenv/m32/lib
M32INC= $(BASE)/inc/m32
COMSIZE= $(BASE)/size/common
COMINC= $(BASE)/inc/common
#
LIBLD	= $(BASE)/libld/m32/libld.a
OBJECTS = main.o process.o fcns.o
#
all:	size
size:	$(OBJECTS) $(LIBLD)
	$(LD_CMD) -o size $(OBJECTS) $(LIBLD)
#
main.o:	$(COMINC)/filehdr.h $(COMINC)/ldfcn.h $(M32INC)/sgs.h $(COMSIZE)/defs.h \
	$(COMSIZE)/main.c
	$(CC_CMD) $(COMSIZE)/main.c
#
process.o:	$(COMINC)/filehdr.h $(COMINC)/scnhdr.h $(COMINC)/ldfcn.h \
		$(COMSIZE)/process.h $(COMSIZE)/defs.h $(COMSIZE)/process.c \
		$(M32INC)/sgs.h
	$(CC_CMD) $(COMSIZE)/process.c
#
fcns.o:	$(COMINC)/filehdr.h $(COMINC)/scnhdr.h $(COMINC)/ldfcn.h \
	$(M32INC)/sgs.h $(COMSIZE)/defs.h $(COMSIZE)/fcns.c
	$(CC_CMD) $(COMSIZE)/fcns.c
#
save:	$(BINDIR)/$(SGS)size
	-rm -f $(BINDIR)/$(SGS)size.back
	cp $(BINDIR)/$(SGS)size $(BINDIR)/$(SGS)size.back
#
install:	$(BINDIR)/$(SGS)size
#
$(BINDIR)/$(SGS)size:	size
	-rm -f $(BINDIR)/$(SGS)size
	cp size $(BINDIR)/$(SGS)size
	-$(STRIP_CMD) $(BINDIR)/$(SGS)size
#
stripit:	uninstall
uninstall:
	-rm -f $(BINDIR)/$(SGS)size
#
clean:	shrink
shrink:
	-rm -f $(OBJECTS) size
#
lint:	$(COMSIZE)/main.c $(COMSIZE)/process.c $(COMSIZE)/fcns.c \
	$(COMINC)/filehdr.h $(COMINC)/ldfcn.h $(COMINC)/scnhdr.h \
	$(M32INC)/sgs.h $(COMSIZE)/process.h $(COMSIZE)/defs.h
	$(LINT_CMD) $(DEFLIST) $(INCLIST) $(COMSIZE)/*.c
