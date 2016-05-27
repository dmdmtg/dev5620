#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	@(#)jx:makefile	2.9
########
#
#	jx makefile
#
########
#
#	Standard Macros
#
########
DMD = /usr/local/dmd
AUX_CLEAN = 
CC = $(SGS)cc
INC = ../include
MAKE.LO = make.lo
MAKE.ROOT = $(DMD)/make.root
MKGEN = mkgen
SGS = $(SGSX)
SGSX = 

INC_LIST = -I.  -I$(INC) -I$(DMD)/include

CLEAN =

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
MCC=$(DMD)/bin/$(DMDXE)dmdcc

UINC=$(ROOT)/usr/include

DMDDEMO=$(DMD)/demo
MLD=$(DMD)/bin/m32ld
MAR=$(DMD)/bin/dmdar
MLORDER=$(DMD)/bin/m32lorder

########
#
#	make.lo
#
########

TITLE = jx makefile
PRODUCTS = jx sysint
MAKEARG= -$(MAKEFLAGS) 

MLORDER=$(DMD)/bin/m32lorder
CLEAN = *.o sysint jx

CFILES=	$(DMDSRC)/lib/libj/put.c $(DMDSRC)/lib/libj/printf.c \
	$(DMDSRC)/lib/libj/comm.c $(DMDSRC)/lib/libj/fopen.c \
	$(DMDSRC)/lib/libj/rdwr.c $(DMDSRC)/lib/libj/data.c \
	$(DMDSRC)/lib/libj/get.c $(DMDSRC)/lib/libj/popen.c \
	$(DMDSRC)/lib/libj/exit.c

EXTRACFLAGS=-O
CFLAGS=$(INC_LIST) -DDMD5620 $(EXTRACFLAGS)

all: jx sysint

jx: jx.c ver.c
	$(CC) -o jx jx.c ver.c $(CFLAGS) $(DMD)/lib/libwindows.a

sysint: sysint.c comm.h
	$(CC) -o sysint sysint.c $(CFLAGS)

save:
	-cp $(DMDBIN)/jx ojx
	-cp $(DMDLIB)/sysint osysint

install:	jx sysint $(DMDBIN)/jx $(DMDLIB)/sysint 
strip:
		-rm -f $(DMDBIN)/jx $(DMDLIB)/sysint 

$(DMDBIN)/jx:	jx
	cp jx $(DMDBIN)/jx

$(DMDLIB)/sysint:	sysint
	cp sysint $(DMDLIB)/sysint


########
#
#	All dependencies and rules not explicitly stated
#	(including header and nested header dependencies)
#
########

jx:	$(UINC)/sys/ioctl.h
jx:	$(UINC)/stdio.h
#jx:	$(UINC)/sys/termio.h # nested include from termio.h
#jx:	$(UINC)/termio.h
sysint:	comm.h
sysint:	$(UINC)/sgtty.h
sysint:	$(UINC)/stdio.h
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
