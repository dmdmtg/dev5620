#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	@(#)makefile	2.9
########
#
#	libmj makefile
#
########
#
#	Standard Macros
#
########
DMD = /usr/local/dmd
AUX_CLEAN = 
INC = $(DMD)/include
MAKE.LO = make.lo
MAKE.ROOT = $(DMD)/make.root
MKGEN = mkgen
SGSX = 

INC_LIST	=\
	-I$(INC)

CLEAN = .c.o arc.o circle.o comm.o cosdeg.o data.o disc.o discture.o \
	elarc.o eldisc.o eldiscture.o ellipse.o exit.o fgets.o font.o \
	fopen.o get.o getfont.o jarc.o jcircle.o jdisc.o jelarc.o \
	jeldisc.o jellipse.o masks.o popen.o printf.o put.o rdwr.o \
	texture16.o

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
MLORDER=$(DMD)/bin/m32lorder
MSTRIP=$(DMD)/bin/m32strip

########
#
#	make.lo
#
########

TITLE = libmj makefile
PRODUCTS = libmj.a

LCLCFLAGS= # -O 
MAKEARG= -$(MAKEFLAGS) 
CLEAN= $(OBJ) libmj.a 
OBJ=arc.o cosdeg.o disc.o discture.o exit.o fgets.o getfont.o \
	font.o fopen.o jarc.o jcircle.o circle.o jdisc.o \
	jelarc.o elarc.o jeldisc.o eldisc.o eldiscture.o jellipse.o ellipse.o \
	masks.o popen.o printf.o rdwr.o get.o \
	put.o comm.o data.o texture16.o
CFILES=arc.c circle.c comm.c cosdeg.c data.c disc.c discture.c\
	elarc.c eldisc.c eldiscture.c ellipse.c exit.c fgets.c font.c \
	fopen.c get.c getfont.c jarc.c jcircle.c jdisc.c \
	jelarc.c jeldisc.c jellipse.c masks.c popen.c \
	printf.c put.c rdwr.c texture16.c

.c.o:
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c $<
	$(MSTRIP) -l $<

libmj.a: $(OBJ)
	$(MAR) cr libmj.a `$(MLORDER) $(OBJ) | tsort`

save:
	-cp $(DMDLIB)/libmj.a olibmj.a

install:	$(DMDLIB)/libmj.a

strip:
	-rm -f $(DMDLIB)/libmj.a

$(DMDLIB)/libmj.a:	libmj.a
	cp libmj.a $(DMDLIB)/libmj.a


########
#
#	All dependencies and rules not explicitly stated
#	(including header and nested header dependencies)
#
########

arc.o:	arc.c
arc.o:	$(INC)/dmd.h
arc.o:	$(INC)/dmdproc.h # nested include from mpx.h
arc.o:	$(INC)/layer.h # nested include from mpx.h
arc.o:	$(INC)/mpx.h # nested include from dmd.h
arc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c arc.c
	$(MSTRIP) -l arc.o

circle.o:	circle.c
circle.o:	$(INC)/dmd.h
circle.o:	$(INC)/dmdproc.h # nested include from mpx.h
circle.o:	$(INC)/layer.h # nested include from mpx.h
circle.o:	$(INC)/mpx.h # nested include from dmd.h
circle.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c circle.c
	$(MSTRIP) -l circle.o

comm.o:	comm.c
comm.o:	$(INC)/dmd.h
comm.o:	$(INC)/dmdio.h
comm.o:	$(INC)/dmdproc.h # nested include from mpx.h
comm.o:	$(INC)/layer.h # nested include from mpx.h
comm.o:	$(INC)/mpx.h # nested include from dmd.h
comm.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c comm.c
	$(MSTRIP) -l comm.o

cosdeg.o:	cosdeg.c
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c cosdeg.c
	$(MSTRIP) -l cosdeg.o

data.o:	data.c
data.o:	$(INC)/dmd.h
data.o:	$(INC)/dmdio.h
data.o:	$(INC)/dmdproc.h # nested include from mpx.h
data.o:	$(INC)/layer.h # nested include from mpx.h
data.o:	$(INC)/mpx.h # nested include from dmd.h
data.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c data.c
	$(MSTRIP) -l data.o

disc.o:	disc.c
disc.o:	$(INC)/dmd.h
disc.o:	$(INC)/dmdproc.h # nested include from mpx.h
disc.o:	$(INC)/layer.h # nested include from mpx.h
disc.o:	$(INC)/mpx.h # nested include from dmd.h
disc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c disc.c
	$(MSTRIP) -l disc.o

discture.o:	discture.c
discture.o:	$(INC)/dmd.h
discture.o:	$(INC)/dmdproc.h # nested include from mpx.h
discture.o:	$(INC)/layer.h # nested include from mpx.h
discture.o:	$(INC)/mpx.h # nested include from dmd.h
discture.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c discture.c
	$(MSTRIP) -l discture.o

elarc.o:	elarc.c
elarc.o:	$(INC)/dmd.h
elarc.o:	$(INC)/dmdproc.h # nested include from mpx.h
elarc.o:	$(INC)/layer.h # nested include from mpx.h
elarc.o:	$(INC)/mpx.h # nested include from dmd.h
elarc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c elarc.c
	$(MSTRIP) -l elarc.o

eldisc.o:	eldisc.c
eldisc.o:	$(INC)/dmd.h
eldisc.o:	$(INC)/dmdproc.h # nested include from mpx.h
eldisc.o:	$(INC)/layer.h # nested include from mpx.h
eldisc.o:	$(INC)/mpx.h # nested include from dmd.h
eldisc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c eldisc.c
	$(MSTRIP) -l eldisc.o

eldiscture.o:	eldiscture.c
eldiscture.o:	$(INC)/dmd.h
eldiscture.o:	$(INC)/dmdproc.h # nested include from mpx.h
eldiscture.o:	$(INC)/layer.h # nested include from mpx.h
eldiscture.o:	$(INC)/mpx.h # nested include from dmd.h
eldiscture.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c eldiscture.c
	$(MSTRIP) -l eldiscture.o

ellipse.o:	ellipse.c
ellipse.o:	$(INC)/dmd.h
ellipse.o:	$(INC)/dmdproc.h # nested include from mpx.h
ellipse.o:	$(INC)/layer.h # nested include from mpx.h
ellipse.o:	$(INC)/mpx.h # nested include from dmd.h
ellipse.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c ellipse.c
	$(MSTRIP) -l ellipse.o

exit.o:	exit.c
exit.o:	$(INC)/dmd.h
exit.o:	$(INC)/dmdio.h
exit.o:	$(INC)/dmdproc.h # nested include from mpx.h
exit.o:	$(INC)/layer.h # nested include from mpx.h
exit.o:	$(INC)/mpx.h # nested include from dmd.h
exit.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c exit.c
	$(MSTRIP) -l exit.o

fgets.o:	fgets.c
fgets.o:	$(INC)/dmd.h
fgets.o:	$(INC)/dmdio.h
fgets.o:	$(INC)/dmdproc.h # nested include from mpx.h
fgets.o:	$(INC)/layer.h # nested include from mpx.h
fgets.o:	$(INC)/mpx.h # nested include from dmd.h
fgets.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c fgets.c
	$(MSTRIP) -l fgets.o

font.o:	font.c
font.o:	$(INC)/font.h
font.o:	$(INC)/dmd.h
font.o:	$(INC)/dmdio.h
font.o:	$(INC)/dmdproc.h # nested include from mpx.h
font.o:	$(INC)/layer.h # nested include from mpx.h
font.o:	$(INC)/mpx.h # nested include from dmd.h
font.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c font.c
	$(MSTRIP) -l font.o

fopen.o:	fopen.c
fopen.o:	$(INC)/dmd.h
fopen.o:	$(INC)/dmdio.h
fopen.o:	$(INC)/dmdproc.h # nested include from mpx.h
fopen.o:	$(INC)/layer.h # nested include from mpx.h
fopen.o:	$(INC)/mpx.h # nested include from dmd.h
fopen.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c fopen.c
	$(MSTRIP) -l fopen.o

get.o:	get.c
get.o:	$(INC)/dmd.h
get.o:	$(INC)/dmdio.h
get.o:	$(INC)/dmdproc.h # nested include from mpx.h
get.o:	$(INC)/layer.h # nested include from mpx.h
get.o:	$(INC)/mpx.h # nested include from dmd.h
get.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c get.c
	$(MSTRIP) -l get.o

getfont.o:	$(INC)/font.h
getfont.o:	getfont.c
getfont.o:	$(INC)/dmd.h
getfont.o:	$(INC)/dmdio.h
getfont.o:	$(INC)/dmdproc.h # nested include from mpx.h
getfont.o:	$(INC)/layer.h # nested include from mpx.h
getfont.o:	$(INC)/mpx.h # nested include from dmd.h
getfont.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c getfont.c
	$(MSTRIP) -l getfont.o

jarc.o:	jarc.c
jarc.o:	$(INC)/dmd.h
jarc.o:	$(INC)/dmdproc.h # nested include from mpx.h
jarc.o:	$(INC)/layer.h # nested include from mpx.h
jarc.o:	$(INC)/mpx.h # nested include from dmd.h
jarc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c jarc.c
	$(MSTRIP) -l jarc.o

jcircle.o:	jcircle.c
jcircle.o:	$(INC)/dmd.h
jcircle.o:	$(INC)/dmdproc.h # nested include from mpx.h
jcircle.o:	$(INC)/layer.h # nested include from mpx.h
jcircle.o:	$(INC)/mpx.h # nested include from dmd.h
jcircle.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c jcircle.c
	$(MSTRIP) -l jcircle.o

jdisc.o:	jdisc.c
jdisc.o:	$(INC)/dmd.h
jdisc.o:	$(INC)/dmdproc.h # nested include from mpx.h
jdisc.o:	$(INC)/layer.h # nested include from mpx.h
jdisc.o:	$(INC)/mpx.h # nested include from dmd.h
jdisc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c jdisc.c
	$(MSTRIP) -l jdisc.o

jelarc.o:	jelarc.c
jelarc.o:	$(INC)/dmd.h
jelarc.o:	$(INC)/dmdproc.h # nested include from mpx.h
jelarc.o:	$(INC)/layer.h # nested include from mpx.h
jelarc.o:	$(INC)/mpx.h # nested include from dmd.h
jelarc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c jelarc.c
	$(MSTRIP) -l jelarc.o

jeldisc.o:	jeldisc.c
jeldisc.o:	$(INC)/dmd.h
jeldisc.o:	$(INC)/dmdproc.h # nested include from mpx.h
jeldisc.o:	$(INC)/layer.h # nested include from mpx.h
jeldisc.o:	$(INC)/mpx.h # nested include from dmd.h
jeldisc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c jeldisc.c
	$(MSTRIP) -l jeldisc.o

jellipse.o:	jellipse.c
jellipse.o:	$(INC)/dmd.h
jellipse.o:	$(INC)/dmdproc.h # nested include from mpx.h
jellipse.o:	$(INC)/layer.h # nested include from mpx.h
jellipse.o:	$(INC)/mpx.h # nested include from dmd.h
jellipse.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c jellipse.c
	$(MSTRIP) -l jellipse.o

masks.o:	masks.c
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c masks.c
	$(MSTRIP) -l masks.o

popen.o:	$(INC)/dmd.h
popen.o:	$(INC)/dmdio.h
popen.o:	$(INC)/dmdproc.h # nested include from mpx.h
popen.o:	$(INC)/layer.h # nested include from mpx.h
popen.o:	$(INC)/mpx.h # nested include from dmd.h
popen.o:	popen.c
popen.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c popen.c
	$(MSTRIP) -l popen.o

printf.o:	$(INC)/dmd.h
printf.o:	$(INC)/dmdio.h
printf.o:	$(INC)/dmdproc.h # nested include from mpx.h
printf.o:	$(INC)/layer.h # nested include from mpx.h
printf.o:	$(INC)/mpx.h # nested include from dmd.h
printf.o:	printf.c
printf.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c printf.c
	$(MSTRIP) -l printf.o

put.o:	$(INC)/dmd.h
put.o:	$(INC)/dmdio.h
put.o:	$(INC)/dmdproc.h # nested include from mpx.h
put.o:	$(INC)/layer.h # nested include from mpx.h
put.o:	$(INC)/mpx.h # nested include from dmd.h
put.o:	put.c
put.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c put.c
	$(MSTRIP) -l put.o

rdwr.o:	$(INC)/dmd.h
rdwr.o:	$(INC)/dmdio.h
rdwr.o:	$(INC)/dmdproc.h # nested include from mpx.h
rdwr.o:	$(INC)/layer.h # nested include from mpx.h
rdwr.o:	$(INC)/mpx.h # nested include from dmd.h
rdwr.o:	rdwr.c
rdwr.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c rdwr.c
	$(MSTRIP) -l rdwr.o

texture16.o:	$(INC)/dmd.h
texture16.o:	$(INC)/dmdproc.h # nested include from mpx.h
texture16.o:	$(INC)/layer.h # nested include from mpx.h
texture16.o:	$(INC)/mpx.h # nested include from dmd.h
texture16.o:	$(INC)/sys/2681.h # nested include from dmd.h
texture16.o:	texture16.c
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c texture16.c
	$(MSTRIP) -l texture16.o

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
		rm -f $(PRODUCTS)

makefile:	$(MAKE.LO) $(MAKE.ROOT)
		$(MKGEN) >make.out
		if [ -s make.out ]; then mv make.out makefile; fi

makefile_all:	makefile

install: 	# rules, if any, specified above
