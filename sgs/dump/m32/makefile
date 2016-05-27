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
#	BELLMAC-32 DUMP MAKEFILE
#
#	@(#) makefile: 1.9 9/15/83
#
SGS=m32
CC=cc
DMD= /usr/local/dmd
EXTRACFLAGS=-O
CFLAGS=-c -DDMD=\"$(DMD)\" $(EXTRACFLAGS)
ARCH=AR32WR
#	Set ARFORMAT to "PORTAR" for portable archive format (post 5.0)
ARFORMAT=PORTAR
#	Set FLEX to -DFLEXNAMES for flexnames (post 6.0)
FLEX= -DFLEXNAMES
DEFLIST=-D$(ARCH) -D$(ARFORMAT) $(FLEX)
INCLIST=-I$(COMINC) -I$(COMDUMP) -I$(M32INC) -I$(USRINC)
ENV=
CC_CMD=$(CC) $(CFLAGS) $(DEFLIST) $(INCLIST) $(ENV)
FFLAG=
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
ROOT=
VERSION=
USRINC= $(ROOT)/usr/$(VERSION)include
#
#
#	Internal Directories
BASE= ../..
BINDIR= $(BASE)/xenv/m32/bin
COMDUMP= $(BASE)/dump/common
COMINC= $(BASE)/inc/common
M32INC= $(BASE)/inc/m32
#
LIBLD	= $(BASE)/libld/m32/libld.a
#
OBJECTS= main.o setflags.o openobject.o process.o fcns.o strchr.o
#
all:	dump
#
dump:	$(OBJECTS) $(LIBLD)
	$(LD_CMD) -o dump $(OBJECTS) $(LIBLD)
#
main.o:	$(COMDUMP)/main.c $(COMINC)/filehdr.h $(COMINC)/ldfcn.h $(COMDUMP)/filedefs.h \
	 $(COMDUMP)/dumpmap.h $(M32INC)/sgs.h
	$(CC_CMD) $(COMDUMP)/main.c
#
setflags.o:	$(COMDUMP)/setflags.c $(COMDUMP)/flagdefs.h $(M32INC)/sgs.h
	$(CC_CMD) $(COMDUMP)/setflags.c
#
strchr.o:	$(COMDUMP)/strchr.c
	$(CC) $(CFLAGS) $(COMDUMP)/strchr.c
#
openobject.o:	$(COMDUMP)/openobject.c $(COMINC)/filehdr.h $(COMINC)/ldfcn.h \
	       $(M32INC)/sgs.h $(COMDUMP)/filedefs.h
	$(CC_CMD) $(COMDUMP)/openobject.c
#
process.o:	$(COMDUMP)/process.c $(COMINC)/filehdr.h $(COMINC)/ldfcn.h $(M32INC)/sgs.h\
	    $(COMDUMP)/filedefs.h $(COMDUMP)/process.h $(COMDUMP)/flagdefs.h
	$(CC_CMD) $(COMDUMP)/process.c
#
fcns.o:	$(COMDUMP)/fcns.c $(COMINC)/filehdr.h $(COMINC)/scnhdr.h $(COMINC)/reloc.h \
	 $(COMINC)/linenum.h $(COMINC)/syms.h $(COMINC)/storclass.h $(COMINC)/ldfcn.h \
	 $(M32INC)/sgs.h
	$(CC_CMD) $(COMDUMP)/fcns.c
#
save:	$(BINDIR)/$(SGS)dump
	-rm -f $(BINDIR)/$(SGS)dump.back
	cp $(BINDIR)/$(SGS)dump $(BINDIR)/$(SGS)dump.back
#
install:	$(BINDIR)/$(SGS)dump
#
$(BINDIR)/$(SGS)dump:	dump
	-rm -f $(BINDIR)/$(SGS)dump
	cp dump $(BINDIR)/$(SGS)dump
	-$(STRIP_CMD) $(BINDIR)/$(SGS)dump
#
stripit:	uninstall
uninstall:
	-rm -f $(BINDIR)/$(SGS)dump
#
lint:	$(COMDUMP)/main.c $(COMDUMP)/setflags.c $(COMDUMP)/openobject.c \
	$(COMDUMP)/process.c $(COMDUMP)/fcns.c \
	$(COMDUMP)/dumpmap.h \
	$(COMINC)/filehdr.h $(COMINC)/ldfcn.h $(COMDUMP)/filedefs.h \
	$(M32INC)/sgs.h $(COMDUMP)/flagdefs.h $(M32INC)/paths.h \
	$(COMINC)/syms.h $(COMINC)/storclass.h $(COMINC)/linenum.h \
	$(COMINC)/scnhdr.h $(COMINC)/reloc.h
	$(LINT_CMD) $(DEFLIST) $(INCLIST) $(COMDUMP)/*.c
#
clean:	shrink
shrink:
	-rm -f $(OBJECTS) dump
