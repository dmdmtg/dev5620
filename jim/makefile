#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#ident	"@(#)makefile	1.5"

DMD = /usr/local/dmd
DMDBIN=$(DMD)/bin
DMDLIB=$(DMD)/lib
DMDSRC=$(DMD)/src
DMDINCLUDE=$(DMD)/include
EXTRACFLAGS=-O

all:	jim

jim:
	cd host; make ${MFLAGS} DMD="$(DMD)" EXTRACFLAGS="$(EXTRACFLAGS)"
	cd frame; make ${MFLAGS} DMD="$(DMD)"
	cd term; make ${MFLAGS} DMD="$(DMD)"

clean:
	cd host; make clean
	cd frame; make clean
	cd term; make clean

clobber:
	cd host; make clobber
	cd frame; make clobber
	cd term; make clobber

cpio:
	ls makefile jim.1 host/makefile host/*.[hc] \
		term/makefile term/*.[hc] frame/makefile frame/*.[hc] \
		 | cpio -ocdm > jim.cpio

save:
	cd host; make save
	cd frame; make save
	cd term; make save

install:
	cd host; make ${MFLAGS} DMD="$(DMD)" EXTRACFLAGS="$(EXTRACFLAGS)" install
	cd frame; make ${MFLAGS} DMD="$(DMD)" install
	cd term; make ${MFLAGS} DMD="$(DMD)" install

strip:
	rm -f $(DMDBIN)/jim $(DMDLIB)/jim.m
	

