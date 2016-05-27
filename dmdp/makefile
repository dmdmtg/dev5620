#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	@(#)makefile	2.11
########
#
#	makefile for dmdp
#
########
#
#	Standard Macros
#
########
DMD = /usr/local/dmd
MACHINE = all
INC=$(DMD)/include
MAKE.HI = make.hi
MAKE.ROOT = $(DMD)/make.root
MAKE_CMD = $(MAKE) $(MKFLAGS) $(MKGEN_ENV) $(ENV)
MKGEN = mkgen
MKGEN_ENV = "MAKE=$(MAKE)" "MKFLAGS=$(MKFLAGS)" "MKGEN=$(MKGEN)"\
	"TARGET=$(TARGET)" "MACHINE=$(MACHINE)" "ENV=$(ENV)"
TARGET = all

########
#
#	make.root
#
########

DMDBIN=$(DMD)/bin
DMDLIB=$(DMD)/lib
DMDSRC=$(DMD)/src
DMDINCLUDE=$(DMD)/include
UINC=$(ROOT)/usr/include
DMDDEMO=$(DMD)/demo
MCC=$(DMD)/bin/$(DMDXE)dmdcc
MLD=$(DMD)/bin/m32ld
MAR=$(DMD)/bin/dmdar
MLORDER=$(DMD)/bin/m32lorder

OBJS = printer.o tty.o citoh.o hp.o
BINOBJS = dmdp.o h.o s.o pbits.o misc.o 

CLEAN = dmdp.m dmdp.o h.o pbits.o misc.o printer.o tty.o citoh.o hp.o s.o dmdp

PRODUCTS= dmdp dmdcat

all:
install:	all

all : dmdp.m

.c.o:
	$(MCC) -c $< # -O

#############
# FOR DEBUG
#.c.o:
#	$(MCC) -DDEBUG -c -g $<
#
#dmdp.m : $(OBJS) lprintf.o
#	$(MCC)  $(OBJS) lprintf.o -o dmdp.m
#############

dmdp.m : $(OBJS) $(BINOBJS)
	$(MCC) $(BINOBJS) $(OBJS) -o dmdp.m

install:	$(DMDLIB)/dmdp.m $(DMDBIN)/dmdp $(DMDBIN)/dmdcat
strip:
		-rm -f $(DMDLIB)/dmdp.m $(DMDBIN)/dmdp $(DMDBIN)/dmdcat

$(DMDLIB)/dmdp.m:	dmdp.m
	cp dmdp.m $(DMDLIB)/dmdp.m

$(DMDBIN)/dmdp:		dmdp
	cp dmdp  $(DMDBIN)/dmdp
	$(CH)-chmod 755 $(DMDBIN)/dmdp

dmdp:	dmdp.sh
	sed -e s+DmD+"$(DMD)"+g dmdp.sh > dmdp

$(DMDBIN)/dmdcat:	dmdcat
	cp dmdcat $(DMDBIN)/dmdcat
	$(CH)-chmod 755 $(DMDBIN)/dmdcat

clean:	
	rm -f $(CLEAN)

clobber:	clean

########
#
#	All dependencies and rules not explicitly stated
#	(including header and nested header dependencies)
#
########

citoh.o:	$(INC)/sccsid.h
citoh.o:	$(INC)/dmd.h
citoh.o:	printer.h
dmdp.o:		$(INC)/sccsid.h
dmdp.o:		$(INC)/dmd.h
dmdp.o:		$(INC)/setup.h
dmdp.o:		printer.h
h.o:		$(INC)/sccsid.h
h.o:		$(INC)/dmd.h
h.o:		printer.h
hp.o:		$(INC)/sccsid.h
hp.o:		$(INC)/dmd.h
hp.o:		printer.h
lprintf.o:	$(INC)/sccsid.h
lprintf.o:	$(INC)/dmd.h
lprintf.o:	$(INC)/font.h
misc.o:		$(INC)/sccsid.h
misc.o:		$(INC)/dmd.h
misc.o:		$(INC)/font.h
pbits.o:	$(INC)/sccsid.h
pbits.o:	$(INC)/dmd.h
pbits.o:	$(INC)/blitio.h
pbits.o:	printer.h
printer.o:	$(INC)/sccsid.h
printer.o:	printer.h
s.o:		$(INC)/sccsid.h
s.o:		$(INC)/dmd.h
tty.o:		$(INC)/sccsid.h
tty.o:		$(INC)/dmd.h
tty.o:	printer.h
