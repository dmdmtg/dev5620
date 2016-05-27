#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	 jim host makefile - @(#)makefile	1.2


DMD=/usr/local/dmd
DMDBIN=$(DMD)/bin
DMDLIB=$(DMD)/lib
DMDSRC=$(DMD)/src
DMDINCLUDE=$(DMD)/include

LCLCFLAGS=
EXTRACFLAGS=-O
CFLAGS= -I$(DMD)/include -DDMD=\"$(DMD)\" -DDMD5620 $(EXTRACFLAGS)

CFILES=alloc.c file.c gcalloc.c jim.c msgs.c pattern.c string.c unix.c 
FILES=alloc.o file.o gcalloc.o jim.o msgs.o pattern.o string.o unix.o 

jim:	$(FILES)
	@HOSTAGENT=""; set -x; \
	for F in $(DMD)/lib/libwindows.a $(DMD)/lib/hostagent.o \
					/usr/lib/libwindows.a ; do \
		if [ -f "$$F" ]; then HOSTAGENT=$$F; fi; done; \
	$(CC) $(FILES) -o jim $$HOSTAGENT $(CFLAGS)

ftest:	ftest.o string.o file.o
	$(CC) -o ftest ftest.o string.o file.o

lint:
	lint -h -u -x $(CFILES) 2>&1 | buffer

pr:
	@pr -n file.h msgs.h $(CFILES) | lp -t'Unix Jim' -omode=lh

clean:	
	rm -f *.o jim

clobber:	clean

save:
	cp $(DMDBIN)/jim ojim

unsave:	ojim
	cp ojim $(DMDBIN)/jim

install:	$(DMDBIN)/jim $(DMDBIN)/jimunpack

$(DMDBIN)/jim:	jim
	cp jim $(DMDBIN)/jim

$(DMDBIN)/jimunpack:	jimunpack.sh
	cp jimunpack.sh $(DMDBIN)/jimunpack
	chmod 755 $(DMDBIN)/jimunpack



$(FILES):	jim.h
file.o jim.o pattern.o string.o unix.o:	file.h
jim.o msgs.o:	msgs.h
