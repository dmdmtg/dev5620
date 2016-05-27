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
#	WE32000 AS MASTER MAKEFILE
#
#	@(#) makefile: 1.14 3/5/84
#
# Architectures:
#
#	AR16WR = DEC 11/45-70
#	AR32WR = VAX 11/780
#	AR32W  = 3B family, IBM 370
#
MAKE=make
SGS=m32
CC=cc
DMD = /usr/local/dmd
EXTRACFLAGS = -O
CFLAGS = -c -DDMD=\"$(DMD)\" $(EXTRACFLAGS)
ARCH=AR32W
LDFLAGS=
B30=
DBO=RBO
#	Set MAC to ABWRMAC if it is 32A,32B SGS and RESTORE fix is needed
#	Set MAC to ABWORMAC if it is 32A,32B SGS and RESTORE fix is not needed
#	Set MAC to BMAC if it is 32B SGS
MAC=ABWORMAC
PCCALL=CALLPCREL
FLEX=-DFLEXNAMES
#
CCPARMS=CC="$(CC)" CFLAGS="$(CFLAGS)" B30="$(B30)" FFLAG="$(FFLAG)" \
	 ENV="$(ENV)" VERSION="$(VERSION)"
SGSPARMS=MAKE="$(MAKE)" SGS="$(SGS)" ARCH="$(ARCH)" DBO=$(DBO) \
	 FLEX="$(FLEX)" MAC="$(MAC)"
DIRPARMS=BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" ROOT="$(ROOT)"
#
#
#	Internal Directories
#
BASE= ../..
BINDIR= $(BASE)/xenv/m32/bin
LIBDIR= $(BASE)/xenv/m32/lib
ROOT=
VERSION=
#
all	:	threeproc.mk oneproc.mk
	   $(MAKE) $(CCPARMS) $(SGSPARMS) $(DIRPARMS) LDFLAGS="$(LDFLAGS)" -f oneproc.mk
#
as1:	threeproc.mk
		echo "Can't $(MAKE) as1 in one process as"
#
as2:	threeproc.mk
	echo "Can't $(MAKE) as2 in one process as"
#
install	:	threeproc.mk oneproc.mk
		$(MAKE) $(CCPARMS) $(SGSPARMS) $(DIRPARMS) -f oneproc.mk install
#
save	:	threeproc.mk oneproc.mk
		$(MAKE) $(CCPARMS) $(SGSPARMS) $(DIRPARMS) -f oneproc.mk save
#
stripit:	uninstall
uninstall:	threeproc.mk oneproc.mk
		$(MAKE) $(CCPARMS) $(SGSPARMS) $(DIRPARMS) -f oneproc.mk uninstall
#
shrink	:	threeproc.mk oneproc.mk
		$(MAKE) $(SGSPARMS) -f oneproc.mk shrink
clean:
		rm -f *.o as
