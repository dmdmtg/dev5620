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
#	BELLMAC-32 LD MASTER MAKEFILE
#
#	@(#) makefile: 1.16 3/1/84
#
# Architectures:
#
#	AR16WR = DEC 11/45-70
#	AR32WR = VAX 11/780
#	AR32W  = 3B family, IBM 370
#
# Specify the version of UN*X beng used:
#
#	TS  :	BTL UN*X TS
#
MAKE=make
SGS=m32
CC=cc
DMD= /usr/local/dmd
EXTRACFLAGS=-O
CFLAGS=-c -DDMD=\"$(DMD)\" $(EXTRACFLAGS)
ARCH=AR32WR
B10=
SYS=TS
FFLAG=
#	Set ARFORMAT to PORTAR for portable archive format (post 5.0)
#	Set ARFORMAT to OLDAR for pre-5.0 archive format
ARFORMAT=PORTAR
DBO=FBO
ENV=
FLEX= -DFLEXNAMES
SDP= NOSDP
#
CCPARMS=CC="$(CC)" CFLAGS="$(CFLAGS)" B10="$(B10)" \
	ARFORMAT="$(ARFORMAT)" DBO="$(DBO)" ENV="$(ENV)" \
	VERSION="$(VERSION)" FFLAG="$(FFLAG)"
SGSPARMS=MAKE="$(MAKE)" SGS="$(SGS)" ARCH="$(ARCH)" SYS="$(SYS)" \
	 FLEX="$(FLEX)"
DIRPARMS=BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" ROOT="$(ROOT)"
LIBPARMS=LIBS="$(LIBS)" LIBES="$(LIBES)"
#
#	Internal Directories
#
BASE= ../..
BINDIR= $(BASE)/xenv/m32/bin
LIBDIR= $(BASE)/xenv/m32/lib
#
#	External Directories
#
ROOT=
VERSION=
#
LIBES= -ll
LIBS=
#
#
# Make ld
#
all:		oneproc.mk twoproc.mk
		$(MAKE) $(CCPARMS) $(SGSPARMS) $(DIRPARMS) $(LIBPARMS) SDP=$(SDP) -f oneproc.mk

#
ld:		oneproc.mk twoproc.mk
		$(MAKE) $(CCPARMS) $(SGSPARMS) $(DIRPARMS) $(LIBPARMS) -f oneproc.mk ld
#
ld2:		twoproc.mk
		echo "Can't make ld2 in one process ld"
#
#
#
# File and administrative commands
install:	oneproc.mk twoproc.mk
		$(MAKE) $(CCPARMS) $(SGSPARMS) $(DIRPARMS) $(LIBPARMS) SDP=$(SDP) -f oneproc.mk install

#
#
save:		oneproc.mk twoproc.mk
		$(MAKE) $(SGSPARMS) $(DIRPARMS) -f oneproc.mk save
#
uninstall:	oneproc.mk twoproc.mk
		$(MAKE) $(SGSPARMS) $(DIRPARMS) -f oneproc.mk uninstall
#
clean:		shrink
shrink:		oneproc.mk twoproc.mk
		$(MAKE) $(SGSPARMS) -f oneproc.mk shrink
