#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	 @(#)makefile	2.15
#
#
DMD=/usr/local/dmd
DMDBIN=$(DMD)/bin
DMDLIB=$(DMD)/lib
DMDSRC=$(DMD)/src
DMDINCLUDE=$(DMD)/include

MCC=$(DMDBIN)/$(DMDXE)dmdcc
LCLCFLAGS= -g
DMDCFLAGS= -s
DMDLD=$(DMDBIN)/32ld


OBJS=	main.o lprintf.o host.o menu.o menus.o graphics.o

.c.o:
	$(MCC) $(DMDCFLAGS) -c $<

dmdebug.m:	$(OBJS)
	$(MCC) $(DMDCFLAGS) -o dmdebug.m $(OBJS)


menus.c: ../menus.c
	cp ../menus.c menus.c

clean: clobber

clobber:
	rm -f dmdebug.m *.o

save:
	-cp $(DMDLIB)/dmdebug.m odmdebug.m

install:	$(DMDLIB)/dmdebug.m

$(DMDLIB)/dmdebug.m:	dmdebug.m
	cp dmdebug.m $(DMDLIB)/dmdebug.m

host.o main.o menu.o lprintf.o graphics.o:../protocol.h
main.o : ../traps.h ../isp.h
menu.o menus.o: ../menu.h
