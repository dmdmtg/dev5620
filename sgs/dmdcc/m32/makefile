#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	@(#)makefile	2.11
#
#	DMD VERSION OF BELLMAC-32 CC MAKEFILE
#
#	@(#) makefile: 1.4 6/29/82 (modified 7/2/83 for DMD)
#
DMD=/usr/local/dmd
SGS=m32
EXTRACFLAGS=-O
CFLAGS=$(EXTRACFLAGS)
CC_FLAGS= $(CFLAGS) -I../../../include -DDMD=\"$(DMD)\"
ARCH=AR32W
# define PASS to "ONEPASS" for a one process compiler
# define PASS to "DUMMY" for a two process compiler
PASS=ONEPASS
DEFLIST=-D$(ARCH) -DM32 -D$(PASS)
INCLIST=-I$(INC) -I$(USRINC)
INC=.
ENV=
CC_CMD=$(CC) $(CC_FLAGS) $(DEFLIST) $(INCLIST) $(ENV)
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
DMDBIN=$(DMD)/bin
DMDLIB=$(DMD)/lib
DMDINC=$(DMD)/include
BINDIR=$(DMDBIN)
LIBDIR=$(DMDLIB)
#
#	Internal Directories
#
COMS=.
USRINC=$(ROOT)/usr/include
#
all:		dmdcc
#
dmdcc:	cc.o 
	$(CC_CMD) -o dmdcc cc.o

cc.o:	$(INC)/paths.h $(INC)/sgs.h $(COMS)/cc.c
	$(CC_CMD) -c $(COMS)/cc.c 

#
save:		$(BINDIR)/dmdcc
	-rm -f $(BINDIR)/dmdcc.back
	cp $(BINDIR)/dmdcc $(BINDIR)/dmdcc.back
#
install:	$(BINDIR)/dmdcc
#
$(BINDIR)/dmdcc:	dmdcc
	-rm -f $(BINDIR)/dmdcc
	cp dmdcc $(BINDIR)/dmdcc
	-$(STRIP_CMD) $(BINDIR)/dmdcc

#
stripit:	uninstall
uninstall:
	-rm -f $(BINDIR)/dmdcc
#
shrink:
	-rm -f dmdcc *.o
#
lint:		$(INC)/paths.h $(INC)/sgs.h $(COMS)/cc.c 
	$(LINT_CMD) $(DEFLIST) $(INCLIST) $(COMS)/cc.c

makefile:
	echo "makefile not rebuilt"

makefile_all:
	echo "makefile not rebuilt"

clean: 
	-rm -f dmdcc *.o

clobber:	 clean

