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
#  @(#) makefile: 1.4 2/3/84
#
#
SGS=	m32
OWN=	bin		#file owner
GRP=	bin		#file group
PROT=	755		#protections
BASE=	../..
ROOT=	$(BASE)

BINDIR=	$(ROOT)/bin
LIBDIR=	$(ROOT)/lib
COMINC=	.
PCC2COM= ../common
# Directory for sdb.h
SDBINC=	.

FLEX=	-DFLEXNAMES

CC=	cc
LINT=	lint
YACC=	yacc
LFLAGS=	-p
DMD = /usr/local/dmd
CLFAGS= -O -DDMD=\"$(DMD)\"
INCLIST= -I. -I$(PCC2COM) -I$(SDBINC)
DEFLIST= -DM32B -DNODBG -DNOSIMPSTR
ODEFLIST=	$(FLEX)
LDFLAGS=
YFLAGS=
#
STRIP=strip
SPFLAGS=
STRIP_CMD=$(STRIP) $(SPFLAGS)
EXTRACFLAGS=-O 
CFLAGS=$(EXTRACFLAGS)
#

CC_CMD=	$(CC) -c $(CFLAGS) $(INCLIST) $(DEFLIST) $(ODEFLIST)
YACC_CMD=	$(YACC) $(YFLAGS)

# use M as a short-hand for the awkward PCC2COM
# (M for Machine independent part)

M=	$(PCC2COM)


OFILES= cgram.o xdefs.o scan.o pftn.o trees.o optim.o local.o reader.o\
	local2.o debug.o match.o allo.o comm1.o table.o cost.o cgen.o\
	optdir.o 
CFILES=	$M/cgram.c $M/xdefs.c $M/scan.c $M/pftn.c $M/cgen.c $M/cost.c \
	$M/trees.c $M/optim.c local.c $M/reader.c \
	local2.c debug.c $M/match.c $M/allo.c $M/comm1.c \
	table.c optdir.c

build:	comp

#-------------------------

comp:	$(OFILES)
		$(CC) $(CFLAGS) $(LDFLAGS) -o comp $(OFILES)

# sty:		$M/manifest.h $M/sty.y macdefs.h $M/mfile2.h $M/dope.h
#		-@echo "Expect 3 reduce/reduce conflicts"
#		$(YACC_CMD) $M/sty.y
#		cc $(CFLAGS) $(LDFLAGS) -I. -I$M -o sty y.tab.c $(BSDLIB)
#		rm y.tab.c

trees.o:	$M/manifest.h macdefs.h $M/mfile1.h $(SDBINC)/sdb.h $M/trees.c
		$(CC_CMD) $M/trees.c

optim.o:	$M/manifest.h macdefs.h $M/mfile1.h $(SDBINC)/sdb.h $M/optim.c
		$(CC_CMD) $M/optim.c

pftn.o:		$M/manifest.h macdefs.h $M/mfile1.h $(SDBINC)/sdb.h $M/pftn.c
		$(CC_CMD) $M/pftn.c

local.o:	$M/manifest.h macdefs.h $M/mfile1.h $(SDBINC)/sdb.h
		$(CC_CMD) -I$M local.c

scan.o:		$M/manifest.h macdefs.h $M/mfile1.h $(SDBINC)/sdb.h $M/scan.c
		$(CC_CMD) $M/scan.c

xdefs.o:	$M/manifest.h $M/mfile1.h $(SDBINC)/sdb.h macdefs.h $M/xdefs.c
		$(CC_CMD) $M/xdefs.c

cgram.o:	$M/manifest.h $M/mfile1.h $(SDBINC)/sdb.h macdefs.h $M/cgram.c
		$(CC_CMD) -DYYDEBUG=1 $M/cgram.c

$M/cgram.c:	$M/cgram.y
		-@echo "Expect 6 shift/reduce conflicts"
		$(YACC_CMD) $M/cgram.y
		mv y.tab.c $M/cgram.c

COMMON=		$M/common $M/dope.h
comm1.o:	$M/manifest.h $M/mfile1.h $(SDBINC)/sdb.h $(COMMON) macdefs.h \
			$M/comm1.c
		$(CC_CMD) $M/comm1.c

table.o:	$M/manifest.h $M/mfile2.h macdefs.h table.c
		$(CC_CMD) -I$M table.c

# table.c:	sty stin
#		-@echo "Expect 2 \"... may be covered by ...\" messages"
#		./sty <stin >table.c

cost.o:		$M/manifest.h $M/mfile2.h macdefs.h $M/cost.c
		$(CC_CMD) $M/cost.c

cgen.o:		$M/manifest.h $M/mfile2.h macdefs.h $M/cgen.c
		$(CC_CMD) $M/cgen.c

reader.o:	$M/manifest.h $M/mfile2.h macdefs.h $M/reader.c
		$(CC_CMD) $M/reader.c

local2.o:	$M/manifest.h $M/mfile2.h macdefs.h
		$(CC_CMD) -I$M local2.c

debug.o:	$M/mfile1.h macdefs.h $(COMINC)/storclass.h
		$(CC_CMD) -I$M debug.c

match.o:	$M/manifest.h $M/mfile2.h macdefs.h $M/match.c $(SDBINC)/sdb.h
		$(CC_CMD) $M/match.c

allo.o:		$M/manifest.h $M/mfile2.h macdefs.h $M/allo.c
		$(CC_CMD) $M/allo.c

optdir.o:	$M/mfile1.h macdefs.h $M/manifest.h $(COMINC)/storclass.h
		$(CC_CMD) -I$M optdir.c

#-------------------------

install:	comp
		-rm -f $(LIBDIR)/comp
		cp comp $(LIBDIR)
		-$(STRIP_CMD) $(LIBDIR)/comp
		chmod $(PROT) $(LIBDIR)/comp
#		chgrp $(GRP) $(LIBDIR)/comp
#		chown $(OWN) $(LIBDIR)/comp

#--------------------------

save:	$(LIBDIR)/comp
	-rm -f $(LIBDIR)/comp
	cp $(LIBDIR)/comp $(LIBDIR)/comp.back

#--------------------------

stripit:	uninstall
uninstall:
		-rm -f $(LIBDIR)/comp

#--------------------------

shrink:	clobber

clean:
	-rm -f $(OFILES)

#--------------------------

clobber:	clean
		-rm -f comp sty $M/cgram.c

#--------------------------

lint:	$(CFILES)
	$(LINT) $(LFLAGS) -I. -I$M -I$(SDBINC) $(CFILES) >lint.out
