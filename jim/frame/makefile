#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	 Jim frame makefile - @(#)makefile	1.3
#
#
DMD = /usr/local/dmd
DMDBIN=$(DMD)/bin
DMDLIB=$(DMD)/lib
DMDSRC=$(DMD)/src
DMDINCLUDE=$(DMD)/include

MCC=$(DMDBIN)/$(DMDXE)dmdcc
MAR=$(DMD)/bin/dmdar
LCLCFLAGS= -g -s
DMDCFLAGS=
DMDLD=$(DMDBIN)/32ld

FILES=deltext.o fralloc.o frameop.o instext.o ptofchar.o
CFILES=deltext.c fralloc.c frameop.c instext.c ptofchar.c

frame.a:	$(FILES)
	$(MAR) uv frame.a $(FILES)

.c.o:
	$(MCC) $(DMDCFLAGS) $(LCLCFLAGS) -c $<

print:
	@pr -n frame.h $(CFILES) | lp -omode=hl -t'Jim Frame'

lint:
	lint -I$(DMD)/include -DMPX $(CFILES) -llibj 2>&1 

$(FILES):	frame.h

clean:
	rm -f *.o frame.a

clobber:	clean

save:
	-cp frame.a oframe.a

unsave:	oframe.a
	-cp oframe.a frame.a

install:	frame.a

.PRECIOUS:	frame.a
