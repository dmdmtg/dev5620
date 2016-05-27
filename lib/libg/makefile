#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	@(#)makefile	2.6
DMD = /usr/local/dmd
DMDBIN=$(DMD)/bin
DMDLIB=$(DMD)/lib
MAR=$(DMD)/bin/dmdar
DMDAS=$(DMD)/bin/m32as

all:	libg.a

libg.a: libg.s
	$(DMDAS) -m libg.s
	$(MAR) cr libg.a libg.o

install:	$(DMDLIB)/m32/libg.a

strip:
		-rm -f $(DMDLIB)/m32/libg.a

$(DMDLIB)/m32/libg.a:	libg.a
	-mkdir $(DMDLIB)/m32
	cp  libg.a $(DMDLIB)/m32/libg.a

clean:
	rm -f *.o libg.a

clobber: clean
	rm -f libg.a
	
