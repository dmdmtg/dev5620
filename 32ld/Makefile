#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	@(#)32ld:makefile	2.14
########
#
#	32ld makefile
#
########
#
#	Standard Macros
#
########
DMD = /usr/local/dmd
AUX_CLEAN = 
CC = $(SGS)cc
CC_CMD = $(CC) -c $(PPDEFS) $(CFLAGS) $(INC_LIST)
EXTRACFLAGS = -O
CFLAGS = $(EXTRACFLAGS) -DDMD=\"$(DMD)\"
DEFS = 
INC = ../include
MAKE.LO = make.lo
MAKE.ROOT = $(DMD)/make.root
MKGEN = mkgen
PPDEFS = $(DEFS)
SGSINC = ../include/sgs
SGS = $(SGSX)
SGSX = 

INC_LIST= -I.  -I$(INC) -I$(SGSINC) -I$(DMD)/include

CLEAN = pcheck.o proto.o

all:
install:	all

##########
#
#	make.root
#
##########

DMDBIN=$(DMD)/bin
DMDLIB=$(DMD)/lib
DMDSRC=$(DMD)/src
DMDINCLUDE=../include
UINC=/usr/include
DMDDEMO=$(DMD)/demo
MCC=$(DMD)/bin/$(DMDXE)dmdcc
MLD=m32ld
MAR=ar
MLORDER=m32lorder

########
#
#	make.lo
#
########

TITLE = 32ld makefile
PRODUCTS = 32ld 32version 32reloc

MAKEARG= -$(MAKEFLAGS) 

MLORDER=m32lorder
CLEAN = *.o 32ld 32reloc 32version

all:		32ld 32version 32reloc

32ld:		32ld.o proto.o pcheck.o ver.o
		$(CC) -o 32ld 32ld.o proto.o pcheck.o ver.o $(CFLAGS) $(DMD)/lib/libwindows.a

32reloc:	32reloc.o
		$(CC) -o 32reloc 32reloc.o $(CFLAGS)

32version:	32version.o 
		$(CC) -o 32version 32version.o $(CFLAGS) $(DMD)/lib/libwindows.a

save:
		-cp $(DMDBIN)/32ld o32ld
		-cp $(DMDBIN)/32reloc o32reloc

install:	$(DMDBIN)/32ld $(DMDBIN)/32reloc $(DMDBIN)/32version
strip:
		-rm -f $(DMDBIN)/32ld $(DMDBIN)/32reloc $(DMDBIN)/32version

$(DMDBIN)/32ld: 32ld
		cp 32ld $(DMDBIN)/32ld

$(DMDBIN)/32reloc: 32reloc
		cp 32reloc $(DMDBIN)/32reloc

$(DMDBIN)/32version: 32version
		cp 32version $(DMDBIN)/32version


32ld.o:	
	$(CC_CMD) 32ld.c

32reloc.o:	
	$(CC_CMD) 32reloc.c

32version.o:	
	$(CC_CMD) 32version.c


########
#
#	All dependencies and rules not explicitly stated
#	(including header and nested header dependencies)
#
########

32ld.o:	32ld.c
32ld.o:	/usr/include/errno.h
32ld.o:	proto.h
32ld.o:	/usr/include/signal.h
32ld.o:	/usr/include/stdio.h
pcheck.o:	pcheck.c
	$(CC_CMD) pcheck.c

proto.o:	proto.c
proto.o:	proto.h
proto.o:	/usr/include/signal.h
proto.o:	/usr/include/stdio.h
	$(CC_CMD) proto.c

ver.o:	ver.c
	$(CC_CMD) ver.c

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
