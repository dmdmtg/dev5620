#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

# @(#)makefile	2.10
########
#
#	libc makefile
#
########
#
#	Standard Macros
#
########
DMD = /usr/local/dmd
AUX_CLEAN = 
MAKE.LO = make.lo
MAKE.ROOT = $(DMD)/make.root
MKGEN = mkgen
SGSX = 

INC_LIST	=

CLEAN = .c.o .s.o abs.o atoi.o atol.o chrtab.o ctype.o index.o qsort.o rand.o \
	rindex.o strcat.o strchr.o strrchr.o strcmp.o strcpy.o strlen.o \
	strncat.o strncmp.o strncpy.o swab.o

all:
install:	all

#	@(#)makefile	2.10
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
MSTRIP=$(DMD)/bin/m32strip

########
#
#	make.lo
#
########

TITLE = libc makefile
PRODUCTS = libc.a


MAKEARG= -$(MAKEFLAGS) 

MLORDER=$(DMD)/bin/m32lorder
LCLCFLAGS=-O -J
CLEAN=$(OBJ) libc.a

OBJ=abs.o atoi.o atol.o chrtab.o ctype.o index.o qsort.o rand.o rindex.o strcat.o strchr.o strrchr.o strcmp.o strcpy.o strlen.o strncat.o strncmp.o strncpy.o swab.o

.c.o:
	$(MCC) $(MCFLAGS) -g -c $<
	$(MSTRIP) -l $<

.s.o:
	$(MCC) -c -g $<
	$(MSTRIP) -l $<

libc.a:	abs.o atoi.o atol.o chrtab.o ctype.o index.o qsort.o rand.o rindex.o strcat.o strchr.o strrchr.o strcmp.o strcpy.o strlen.o strncat.o strncmp.o strncpy.o swab.o
	$(MAR) cr libc.a `$(MLORDER) $(OBJ) | tsort`

install:	$(DMDLIB)/libc.a

strip: 
	-rm -f $(DMDLIB)/libc.a

$(DMDLIB)/libc.a:	libc.a
	cp libc.a $(DMDLIB)/libc.a


########
#
#	All dependencies and rules not explicitly stated
#	(including header and nested header dependencies)
#
########

abs.o:	$(DMDINCLUDE)/sa.h
abs.o:	abs.c
	$(MCC) $(MCFLAGS) -g -c abs.c
	$(MSTRIP) -l abs.o

atoi.o:	atoi.c
atoi.o:	$(ROOT)/usr/include/ctype.h
	$(MCC) $(MCFLAGS) -g -c atoi.c
	$(MSTRIP) -l atoi.o

atol.o:	atol.c
atol.o:	$(ROOT)/usr/include/ctype.h
	$(MCC) $(MCFLAGS) -g -c atol.c
	$(MSTRIP) -l atol.o

chrtab.o:	chrtab.c
	$(MCC) $(MCFLAGS) -g -c chrtab.c
	$(MSTRIP) -l chrtab.o

ctype.o:	ctype.c
ctype.o:	$(ROOT)/usr/include/ctype.h
	$(MCC) $(MCFLAGS) -g -c ctype.c
	$(MSTRIP) -l ctype.o

index.o:	index.c
	$(MCC) $(MCFLAGS) -g -c index.c
	$(MSTRIP) -l index.o

qsort.o:	$(DMDINCLUDE)/sa.h
qsort.o:	qsort.c
	$(MCC) $(MCFLAGS) -g -c qsort.c
	$(MSTRIP) -l qsort.o

rand.o:	rand.c
	$(MCC) $(MCFLAGS) -g -c rand.c
	$(MSTRIP) -l rand.o

rindex.o:	rindex.c
	$(MCC) $(MCFLAGS) -g -c rindex.c
	$(MSTRIP) -l rindex.o

strcat.o:	strcat.c
	$(MCC) $(MCFLAGS) -g -c strcat.c
	$(MSTRIP) -l strcat.o

strchr.o:	strchr.c
	$(MCC) $(MCFLAGS) -g -c strchr.c
	$(MSTRIP) -l strchr.o

strrchr.o:	strrchr.c
	$(MCC) $(MCFLAGS) -g -c strrchr.c
	$(MSTRIP) -l strrchr.o

strcmp.o:	strcmp.c
	$(MCC) $(MCFLAGS) -g -c strcmp.c
	$(MSTRIP) -l strcmp.o

strcpy.o:	strcpy.c
	$(MCC) $(MCFLAGS) -g -c strcpy.c
	$(MSTRIP) -l strcpy.o

strlen.o:	$(DMDINCLUDE)/sa.h
strlen.o:	strlen.c
	$(MCC) $(MCFLAGS) -g -c strlen.c
	$(MSTRIP) -l strlen.o

strncat.o:	strncat.c
	$(MCC) $(MCFLAGS) -g -c strncat.c
	$(MSTRIP) -l strncat.o

strncmp.o:	strncmp.c
	$(MCC) $(MCFLAGS) -g -c strncmp.c
	$(MSTRIP) -l strncmp.o

strncpy.o:	strncpy.c
	$(MCC) $(MCFLAGS) -g -c strncpy.c
	$(MSTRIP) -l strncpy.o

swab.o:	swab.c
	$(MCC) $(MCFLAGS) -g -c swab.c
	$(MSTRIP) -l swab.o

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

all:		$(PRODUCTS)

clean:
		rm -f $(CLEAN) $(AUX_CLEAN)

clobber:	clean
		rm -f $(PRODUCTS)

makefile:	$(MAKE.LO) $(MAKE.ROOT)
		$(MKGEN) >make.out
		if [ -s make.out ]; then mv make.out makefile; fi

makefile_all:	makefile

install: 	# rules, if any, specified above
