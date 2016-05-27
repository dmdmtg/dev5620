#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	 @(#)makefile	2.17

DMD=/usr/local/dmd
DMDBIN=$(DMD)/bin
DMDLIB=$(DMD)/lib
DMDSRC=$(DMD)/src
DMDINCLUDE=$(DMD)/include


LCLCFLAGS= -Wp,-T -W0,-XT -g
BSTATIC=
CFLAGS= -I. -I$(DMD)/include -DDMD=\"$(DMD)\" $(BSTATIC)

SRCS= 	stabread.c names.c environ.c alloc.c stabsearch.c main.c \
	joff.c jerq.c format.c stack.c gram.c context.c \
	stabhelp.c traps.c menu.c menus.c scratch.c expr.c chase.c \
	srctext.c zdc.c graphics.c functions.c user.c tables.c bits.c snap.c

OBJS= 	stabread.o names.o environ.o alloc.o stabsearch.o main.o \
	joff.o jerq.o format.o stack.o gram.o context.o \
	stabhelp.o traps.o menu.o menus.o scratch.o expr.o chase.o \
	srctext.o zdc.o graphics.o functions.o user.o tables.o bits.o snap.o

dmdebug:	$(OBJS)
	@HOSTAGENT=""; set -x; \
	for F in $(DMD)/lib/libwindows.a $(DMD)/lib/hostagent.o; do \
		if [ -f "$$F" ]; then HOSTAGENT=$$F; fi; done; \
	$(CC) $(CFLAGS) -o dmdebug $(OBJS) $$HOSTAGENT

lint:	$(SRCS)
	lint -abch $(CFLAGS) $(SRCS)
	rm -f gram.c
.c.o:
	$(CC) $(CFLAGS) -c $<

menus.c:	../menus.c
	cp ../menus.c menus.c

menus.o:	../menu.h

clean:	clobber

clobber:
	rm -f *.o dmdebug

save:
	-cp $(DMDBIN)/dmdebug odmdebug

install:	$(DMDBIN)/dmdebug

$(DMDBIN)/dmdebug:	dmdebug
	cp dmdebug $(DMDBIN)/dmdebug

common.h:	../protocol.h
alloc.o chase.o context.o environ.o expr.o format.o functions.o:	../protocol.h
gram.o graphics.o jerq.o joff.o main.o menu.o menus.o scratch.o:	../protocol.h
srctext.o stabhelp.o stabread.o stabsearch.o stack.o traps.o y.tab.o zdc.o:	../protocol.h
alloc.o chase.o context.o environ.o expr.o format.o functions.o snap.o:	common.h
gram.o graphics.o jerq.o joff.o main.o menu.o menus.o scratch.o:	common.h
srctext.o stabhelp.o stabread.o stabsearch.o stack.o traps.o y.tab.o zdc.o:	common.h

stab.h:	a.out.h
chase.o expr.o gram.o y.tab.o:	expr.h 
chase.o context.o expr.o joff.o menu.o srctext.o stack.o traps.o stabsearch.o:	frame.h 
context.o stab.h:	mcc.h 
names.o stab.h:	names.h 
stab.h:	sdb.h 
main.o stabhelp.o stabread.o stabsearch.o user.h:	stab.h 
chase.o context.o expr.o functions.o gram.o joff.o menu.o srctext.o stack.o traps.o y.tab.o user.c:	user.h 
traps.o:	../isp.h 
menu.o menus.o scratch.o traps.o:	../menu.h 
context.o expr.o gram.o joff.o menu.o srctext.o traps.o y.tab.o:	../traps.h 

newa.out.h:	stabread.c

nlist.h filehdr.h aouthdr.h scnhdr.h reloc.h linenum.h syms.h:	newa.out.h

storclass.h:	syms.h

tables.o bits.o:	dis.h
