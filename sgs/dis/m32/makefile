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
#	BELLMAC-32 DISASSEMBLER MAKEFILE
#
#	@(#) makefile: 1.11 9/15/83
#
SGS=m32
CC=cc
DMD= /usr/local/dmd
EXTRACFLAGS=-O
CFLAGS=-c -DDMD=\"$(DMD)\" $(EXTRACFLAGS)
ARCH=AR32W
#	Set ARFORMAT to "PORTAR" for portable archive format (post 5.0)
ARFORMAT=PORTAR
#	Set FLEX to -DFLEXNAMES for flexnames (post 6.0)
FLEX= -DFLEXNAMES
DBO=RBO
B20=
DEFLIST=-D$(ARCH) -DM32 -D$(DBO) -D$(ARFORMAT) $(FLEX)
INCLIST=-I$(M32INC) -I$(COMINC) -I. -I$(COMDIS) -I$(USRINC)
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
#	Internal Directories
#
BASE= ../..
BINDIR= $(BASE)/xenv/m32/bin
M32INC= $(BASE)/inc/m32
COMINC= $(BASE)/inc/common
COMDIS= $(BASE)/dis/common
#
#	External Directories
#
ROOT=
VERSION=
USRINC=$(ROOT)/usr/$(VERSION)include
#
LIBLD	= $(BASE)/libld/m32/libld.a
#
OBJECTS=dis_main.o dis_utls.o bits.o tables.o dis_extn.o lists.o
#
#
all:	dis
#
dis:	$(OBJECTS) $(LIBLD)
	$(LD_CMD) -o dis $(OBJECTS) $(LIBLD)
#
dis_extn.o:	dis.h $(COMDIS)/dis_extn.c $(COMINC)/scnhdr.h $(COMINC)/filehdr.h \
	$(COMINC)/ldfcn.h $(COMINC)/linenum.h $(COMINC)/syms.h \
	$(COMINC)/storclass.h $(COMDIS)/structs.h
	$(CC_CMD) $(COMDIS)/dis_extn.c
dis_main.o:	dis.h $(COMDIS)/dis_main.c $(COMINC)/filehdr.h $(COMINC)/ldfcn.h \
	$(M32INC)/paths.h $(M32INC)/sgs.h $(COMINC)/scnhdr.h $(COMINC)/syms.h\
	$(COMINC)/storclass.h $(COMINC)/linenum.h $(COMDIS)/structs.h
	$(CC_CMD) $(COMDIS)/dis_main.c
dis_utls.o:	dis.h $(COMDIS)/dis_utls.c $(COMINC)/filehdr.h $(COMINC)/ldfcn.h \
	$(COMINC)/scnhdr.h $(COMINC)/syms.h $(COMINC)/linenum.h $(COMINC)/storclass.h \
	$(M32INC)/sgs.h $(COMDIS)/structs.h
	$(CC_CMD) $(B20) $(COMDIS)/dis_utls.c
lists.o:	dis.h $(COMDIS)/lists.c $(COMDIS)/structs.h \
	$(COMINC)/ldfcn.h $(COMINC)/scnhdr.h $(COMINC)/linenum.h \
	$(COMINC)/syms.h $(COMINC)/storclass.h $(M32INC)/paths.h \
	$(M32INC)/sgs.h
	$(CC_CMD) $(COMDIS)/lists.c
bits.o:		dis.h bits.c $(COMINC)/filehdr.h $(COMINC)/ldfcn.h \
	$(COMINC)/scnhdr.h $(M32INC)/sgs.h
	$(CC_CMD) $(B20) bits.c
tables.o:	dis.h tables.c
	$(CC_CMD) tables.c
#
install:	$(BINDIR)/$(SGS)dis
#
$(BINDIR)/$(SGS)dis:	dis
	-rm -f $(BINDIR)/$(SGS)dis
	cp dis $(BINDIR)/$(SGS)dis
	-$(STRIP_CMD) $(BINDIR)/$(SGS)dis
#
save:		$(BINDIR)/$(SGS)dis
	-rm -f $(BINDIR)/$(SGS)dis.back
	cp $(BINDIR)/$(SGS)dis $(BINDIR)/$(SGS)dis.back
#
stripit:	uninstall
uninstall:
	-rm -f $(BINDIR)/$(SGS)dis
#
clean:	shrink
shrink:
	-rm -f $(OBJECTS) dis
#
lint:
	$(LINT_CMD) $(DEFLIST) $(INCLIST) $(COMDIS)/*.c
