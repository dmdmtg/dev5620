#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	 Jim term makefile - @(#)makefile	1.2
#
#
DMD = /usr/local/dmd
DMDBIN=$(DMD)/bin
DMDLIB=$(DMD)/lib
DMDSRC=$(DMD)/src
DMDINCLUDE=$(DMD)/include

MCC=$(DMDBIN)/$(DMDXE)dmdcc
LCLCFLAGS= -g -s
DMDCFLAGS=
DMDLD=$(DMDBIN)/32ld

F=../frame
CFILES=main.c frame.c menu.c msgs.c string.c $F/deltext.c $F/fralloc.c $F/frameop.c $F/instext.c $F/ptofchar.c
FILES=main.o frame.o menu.o msgs.o string.o $F/frame.a

jim.m:	$(FILES) $F/frame.a
	$(MCC) -o jim.m $(FILES)


.c.o:
	$(MCC) $(DMDCFLAGS) $(LCLCFLAGS) -c $<

clean:
	rm -f *.o jim.m

clobber:	clean
	rm -f jim.m

save:
	-cp $(DMDLIB)/jim.m ojim.m

unsave:	ojim.m
	-cp ojim.m $(DMDLIB)/jim.m

install:	$(DMDLIB)/jim.m

$(DMDLIB)/jim.m:	jim.m
	$(DMD)/bin/m32cprs jim.m $(DMDLIB)/jim.m

pr:
	pr -n jim.h menu.h msgs.h $F/frame.h $(CFILES) | lp -t'Terminal Jim' -omode=hl

lint:
	lint -Dvoid=int -I$(DMD)/include -DMPX $(CFILES) -llibj 2>&1 



$(FILES): $F/frame.h $(DMD)/include/jerq.h $(DMD)/include/jerqproc.h
main.o frame.o menu.o:	jim.h
jim.h:	$F/frame.h menu.h msgs.h
.PRECIOUS:	frame.a
