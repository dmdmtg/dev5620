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
#	@(#)makefile	1.4

#***************************************************************************
#                                                                          *
#			UNIX Archive (ar) makefile			   *
#									   *
#***************************************************************************

ROOT	=
BINDIR	= $(ROOT)/bin
BASE	= ../..
COMI	= $(BASE)/inc/common
CDIR	= $(BASE)/ar/common
FLEX	= -DFLEXNAMES
ARFORMAT= PORTAR

STRIP	= strip
LP	= lp

LIBLD	= $(BASE)/libld/m32/libld.a

CFILES = $(CDIR)/ar.c

HFILES = $(COMI)/ar.h $(COMI)/filehdr.h $(COMI)/syms.h 

DMD	= /usr/local/dmd
EXTRACFLAGS=-O
CFLAGS =  -DDMD=\"$(DMD)\" $(EXTRACFLAGS)
DEFLIST	= $(FLEX) -D$(ARFORMAT)
INCLIST	= -I$(COMI)


all:	ar


ar:	$(CFILES) $(HFILES) $(LIBLD)
	$(CC) $(DEFLIST) $(INCLIST) $(CFILES) -o ar $(LIBLD) $(CFLAGS)

install:	ar
	cp ar $(BINDIR)/dmdar
	$(STRIP) $(BINDIR)/dmdar

stripit:	uninstall
uninstall:
	-rm -f $(BINDIR)/dmdar

listing:
	pr -n makefile $(HFILES) $(CFILES) | $(LP)
	@echo "files sent to lineprinter"

clean: 
	-rm -f ar

flow:
	cflow $(PPFLAGS) $(CFILES) > $(OUTFIL)

flowr:
	cflow -r $(PPFLAGS) $(CFILES) > $(OUTFIL)

shrink:		clobber

clobber:	clean
	-rm -f ar
