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
#	BELLMAC-32 CC MAKEFILE
#
#	@(#) makefile: 1.6 5/17/83
#
SGS=m32
CC=cc
DMD = /usr/local/dmd
EXTRACFLAGS = -O
CFLAGS = -DDMD=\"$(DMD)\" $(FFLAG) $(EXTRACFLAGS)
ARCH=AR32WR
# define PASS to "ONEPASS" for a one process compiler
# define PASS to be DUMMY for a two process compiler
PASS=ONEPASS
DEFLIST=-D$(ARCH) -DM32 -D$(PASS)
INCLIST=-I$(M32INC) -I$(USRINC)
ENV=
FFLAG=
CC_CMD=$(CC) $(CFLAGS) $(DEFLIST) $(INCLIST) $(ENV)
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
COMCMD= $(BASE)/cmd/common
#
all:		$(SGS)cc
#
$(SGS)cc:	cc.o 
	$(CC_CMD) -o $(SGS)cc cc.o

cc.o:	$(M32INC)/paths.h $(M32INC)/sgs.h $(COMCMD)/cc.c
	$(CC_CMD) -c $(COMCMD)/cc.c

#
save:		$(BINDIR)/$(SGS)cc
	-rm -f $(BINDIR)/$(SGS)cc.back
	cp $(BINDIR)/$(SGS)cc $(BINDIR)/$(SGS)cc.back
#
install:	$(BINDIR)/$(SGS)cc
#
$(BINDIR)/$(SGS)cc:	$(SGS)cc
	-rm -f $(BINDIR)/$(SGS)cc
	cp $(SGS)cc $(BINDIR)/$(SGS)cc
	-$(STRIP_CMD) $(BINDIR)/$(SGS)cc
#
stripit:	uninstall
uninstall:
	-rm -f $(BINDIR)/$(SGS)cc
#
shrink: clean
clean:
	rm -f $(SGS)cc *.o
#
lint:		$(M32INC)/paths.h $(M32INC)/sgs.h $(COMCMD)/cc.c
	$(LINT_CMD) $(DEFLIST) $(INCLIST) $(COMCMD)/cc.c
