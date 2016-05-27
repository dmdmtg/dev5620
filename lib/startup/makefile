#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	@(#)makefile	2.8
########
#
#	lib makefile
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

INC_LIST	=

CLEAN =\
	.c.o\
	jpcbs.o

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
MAR=$(DMD)/bin/dmdar
MLORDER=m32lorder
DMDAS=$(DMD)/bin/m32as

########
#
#	make.lo
#
########

TITLE = lib makefile
PRODUCTS = mpxmap jxmap 

MAKEARG= -$(MAKEFLAGS) 
FRC=FRC
MLFLAGS=-m -L$(DMDLIB)
MCFLAGS=-O

LCLCFLAGS=-J
OBJ=jpcbs.o crtm.o
CFILES=jpcbs.c
SFILES=crtm.s
CLEAN=jpcbs.o jxmap mpxmap crtm.o

.c.o:
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -c $<

all:	$(OBJ) mpxmap jxmap installation

mpxmap: $(FRC)
	@echo "SECTIONS {" > mpxmap
	@echo "	.text  : { ${DMD}/lib/crtm.o (.text) }" >> mpxmap 
	@echo "	.data  : { ${DMD}/lib/crtm.o (.data) }" >> mpxmap 
	@echo "	.bss   : {}" >> mpxmap 
	@echo "}" >> mpxmap

jxmap:	$(FRC)
	@echo "${DMD}/lib/jpcbs.o" >jxmap
	@echo "SECTIONS {" >>jxmap
	@echo "	GROUP 0x71c050: {" >>jxmap
	@echo "		.pcbs: {${DMD}/lib/jpcbs.o(.data)}" >>jxmap
	@echo "		.stacks: {${DMD}/lib/jpcbs.o(.bss)}" >>jxmap
	@echo "		.text :	{}" >>jxmap
	@echo "		.data  : {}" >>jxmap
	@echo "		.bss : {}" >>jxmap
	@echo "		.dummy: {freeram=.;}" >> jxmap
	@echo "	         }" >>jxmap
	@echo "}" >>jxmap

crtm.o:	crtm.s
	$(DMDAS) -m  crtm.s

$(FRC):


save:
	cp jpcbs.o ojpcbs.o

installation: 
# these must be installed even if NOT doing MAKE INSTALL...
	cp jpcbs.o crtm.o mpxmap jxmap $(DMDLIB)

strip:
	rm $(DMDLIB)/jpcbs.o $(DMDLIB)/crtm.o $(DMDLIB)/mpxmap $(DMDLIB)/jxmap

install:
	@echo "src/lib install always done at build time"

########
#
#	All dependencies and rules not explicitly stated
#	(including header and nested header dependencies)
#
########

jpcbs.o:	jpcbs.c
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -c jpcbs.c
#		This code to get length for .bss in
#		new SGS?????
	$(MLD) -r -a jpcbs.o -o jpcbs.out 2>/dev/null
	mv jpcbs.out jpcbs.o

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
		rm -f $(DMDLIB)/jxmap
		rm -f $(DMDLIB)/mpxmap

makefile:	$(MAKE.LO) $(MAKE.ROOT)
		$(MKGEN) >make.out
		if [ -s make.out ]; then mv make.out makefile; fi

makefile_all:	makefile

install: 	# rules, if any, specified above
