#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	 @(#)makefile	2.12

DMD=/usr/dmd
DMDBIN=$(DMD)/bin
DMDLIB=$(DMD)/lib
DMDSRC=$(DMD)/src
DMDINCLUDE=$(DMD)/include
BSTATIC=

all:	dmdebug

dmdebug:
	cd host; make ${MFLAGS} DMD="$(DMD)" BSTATIC="$(BSTATIC)"
	cd term; make ${MFLAGS} DMD="$(DMD)"

clean:
	cd host; make ${MFLAGS} clean
	cd term; make ${MFLAGS} clean

clobber:	clean

save:
	cd host; make ${MFLAGS} save
	cd term; make ${MFLAGS} save

strip:
	-rm -f $(DMDBIN)/dmdebug
	-rm -f $(DMDLIB)/dmdebug.m
install:
	cd host; make ${MFLAGS} install DMD="$(DMD)"
	cd term; make ${MFLAGS} install DMD="$(DMD)"

