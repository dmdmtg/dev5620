#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

# @(#)makefile	2.15
#
########
#
#	icon makefile
#
########
#
#	Standard Macros
#
########
AUX_CLEAN = 
DMD = /usr/local/dmd
ICONDIR=$(DMD)/icons
INC = $(DMD)/include
MAKE.LO = make.lo
MAKE.ROOT = $(DMD)/make.root
MKGEN = mkgen

INC_LIST	=\
	-I$(INC)

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
DMDINCLUDE=$(DMD)/include
UINC=$(ROOT)/usr/include
DMDDEMO=$(DMD)/demo
MCC=$(DMD)/bin/$(DMDXE)dmdcc
MLD=$(DMD)/bin/m32ld
MAR=ar
MLORDER=$(DMD)/bin/m32lorder

########
#
#	make.lo
#
########

TITLE = icon makefile
PRODUCTS = icon icon.m


MAKEARG= -$(MAKEFLAGS) 

MLORDER=$(DMD)/bin/m32lorder
LCLCFLAGS=-g -O
DMDICON=$(DMD)/icon
DMDBIN=$(DMD)/bin
DBIN=$(DMD)/bin
DLIB=$(DMD)/lib
UINC = $(ROOT)/usr/include 
MCFLAGS= -s

all:	icon.m	icon

icon.m:	icon.c 
	$(MCC) $(MCFLAGS) -DICONDIR=\"$(ICONDIR)\" -o icon.m icon.c 


icon:	icon.sh
	sed -e s+DmD+"$(DMD)"+g icon.sh > icon

install:	$(DMDLIB)/icon.m $(DMDBIN)/icon

strip:
	-rm -f $(DMDLIB)/icon.m $(DMDBIN)/icon

$(DMDLIB)/icon.m:	icon.m
	cp icon.m $(DMDLIB)/icon.m

$(DMDBIN)/icon:	icon
	cp icon $(DMDBIN)/icon
	$(CH)-chmod 755 $(DMDBIN)/icon

########
#
#	All dependencies and rules not explicitly stated
#	(including header and nested header dependencies)
#
########

icon.m:	$(INC)/font.h
icon.m:	$(INC)/dmd.h
icon.m:	$(INC)/dmdio.h
icon.m:	$(INC)/dmdproc.h # nested include from mpx.h
icon.m:	$(INC)/layer.h # nested include from mpx.h
icon.m:	$(INC)/mpx.h # nested include from dmd.h
icon.m:	$(INC)/pandora.h # needed for call to stipple
icon.m:	$(INC)/sys/2681.h # nested include from dmd.h
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
		rm -f $(PRODUCTS)

clobber:	clean
		rm -f $(PRODUCTS)

makefile:	$(MAKE.LO) $(MAKE.ROOT)
		$(MKGEN) >make.out
		if [ -s make.out ]; then mv make.out makefile; fi

makefile_all:	makefile

install: 	# rules, if any, specified above
