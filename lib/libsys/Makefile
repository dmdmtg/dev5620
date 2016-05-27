#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	@(#)Makefile	2.6
########
#
#	libsys makefile
#
########
#
#	Standard Macros
#
########
DMD=/usr/local/dmd
AUX_CLEAN = 
INC = $(DMD)/include
MAKE.LO = make.lo
MAKE.ROOT = $(DMD)/make.root
MKGEN = mkgen
SGSX = 

INC_LIST	=\
	-I$(INC)

CLEAN =\
	excep.o\
	jinit.o

all:	all1 all2

##########
#
#	make.root
#
##########

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

########
#
#	make.lo
#
########

TITLE = libsys makefile
PRODUCTS = libsys.a l.o

MAKEARG= -$(MAKEFLAGS) DMDBIN=$(DMDBIN) DMDLIB=$(DMDLIB) DMDSRC=$(DMDSRC)\
	DMDINCLUDE=$(DMDINCLUDE) DMDSGS=$(DMDSGS) DMDDEMO=$(DMDDEMO)\
	MCC=$(MCC) MCFLAGS=$(MCFLAGS) MLD=$(MLD) MAR=$(MAR)

LCLCFLAGS=-J
CLEAN=$(OBJ) libsys.a l.o

OBJ=excep.o jinit.o 
CFILES=excep.c jinit.c 

.c.o:
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -c $<

.s.o:
	$(MCC) -c $<

all1:	libsys.a l.o

libsys.a: $(OBJ)
	rm -f libsys.a
	$(MAR) cr libsys.a `$(MLORDER) $(OBJ) | tsort`

save:
	-cp $(DMDLIB)/libsys.a olibsys.a

install: $(DMDLIB)/libsys.a $(DMDLIB)/l.o

strip:
	-rm -f $(DMDLIB)/libsys.a $(DMDLIB)/l.o

$(DMDLIB)/libsys.a:	libsys.a
	cp libsys.a $(DMDLIB)/libsys.a

$(DMDLIB)/l.o:	l.o
	cp l.o $(DMDLIB)/l.o

########
#
#	All dependencies and rules not explicitly stated
#	(including header and nested header dependencies)
#
########

excep.o:	excep.c
excep.o:	$(INC)/font.h
excep.o:	$(INC)/jerq.h
excep.o:	$(INC)/kbd.h
excep.o:	$(INC)/setup.h
excep.o:	$(INC)/sys/2681.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -c excep.c

jinit.o:	$(INC)/jerq.h
jinit.o:	jinit.c
jinit.o:	$(INC)/setup.h
jinit.o:	$(INC)/sys/2681.h # nested include from jerq.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -c jinit.c

l.o:	l.s
	$(MCC) -c l.s

########
#
#	Standard Targets
#
#	all		builds all the products specified by PRODUCTS
#	clean		removes all temporary files (ex. installable object)
#	clobber		"cleans", and then removes $(PRODUCTS)
#	makefile	regenerates makefile
#	install		installs products; user defined in make.lo 
#
########

all2:		$(PRODUCTS)

clean:
		rm -f $(CLEAN) $(AUX_CLEAN)

clobber:	clean
		rm -f $(PRODUCTS)

makefile:	$(MAKE.LO) $(MAKE.ROOT)
		$(MKGEN) >make.out
		if [ -s make.out ]; then mv make.out makefile; fi

makefile_all:	makefile

install2: 	# rules, if any, specified above
