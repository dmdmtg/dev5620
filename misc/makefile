#ident	"@(#)attwin:cmd/layers/misc/makefile	1.3"
#
#		Copyright 1985 AT&T
#

CC = cc
DMD = /usr/local/dmd
INC = -I$(DMD)/include
EXTRACFLAGS=-O
CFLAGS =$(EXTRACFLAGS)
MODE775=755
MAKEARGS=	$(MFLAGS) DMD=$(DMD)

all:

install:	all
	-mkdir $(DMD)/misc
	rm -f $(DMD)/misc/5620.termcap
	cp 5620.termcap $(DMD)/misc
	chmod 444 $(DMD)/misc/5620.termcap

clean: clobber

clobber:

strip:
