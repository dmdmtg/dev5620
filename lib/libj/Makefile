#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#	@(#)Makefile	2.6
########
#
#	libj makefile
#
########
#
#	Standard Macros
#
########
DMD=/usr/local/dmd
AUX_CLEAN = 
INC = $(DMD)/include
MAKE.LO = make.lo
MAKE.ROOT = $(DMD)/make.root
MKGEN = mkgen
SGSX = 

INC_LIST	= -I$(INC)

CLEAN = Jrect.o arc.o arith.o atan2.o circle.o comm.o cosdeg.o data.o \
	defont.o disc.o discture.o display.o elarc.o eldisc.o \
	eldiscture.o ellipse.o exit.o fgets.o font.o fopen.o get.o \
	getfont.o introutine.o jarc.o jcircle.o jdisc.o jelarc.o \
	jeldisc.o jellipse.o jpoint.o jstring.o min.o norm.o popen.o \
	printf.o put.o rdwr.o rect.o rol.o sqrt.o string.o texture16.o wait.o

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


TITLE = libj makefile
PRODUCTS = libj.a


MAKEARG= -$(MAKEFLAGS) 

MLORDER=$(DMD)/bin/m32lorder
LCLCFLAGS=-J
CLEAN= $(OBJ) libj.a


CC_CMD =	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c

OBJ=atan2.o cosdeg.o sqrt.o exit.o fgets.o getfont.o font.o fopen.o \
	introutine.o jarc.o arc.o jcircle.o circle.o jdisc.o disc.o \
	discture.o jelarc.o elarc.o jeldisc.o eldisc.o eldiscture.o jellipse.o ellipse.o \
	jpoint.o jstring.o min.o norm.o popen.o printf.o rdwr.o get.o put.o \
	comm.o data.o Jrect.o rol.o string.o defont.o wait.o arith.o display.o \
	rect.o texture16.o
CFILES= arc.c atan2.c circle.c comm.c cosdeg.c data.c disc.c discture.c \
	display.c ellipse.c exit.c fgets.c fopen.c get.c introutine.c \
	jarc.c jcircle.c jdisc.c jellipse.c jpoint.c Jrect.c jstring.c min.c \
	popen.c printf.c put.c rdwr.c sqrt.c string.c getfont.c font.c defont.c \
	eldisc.c jeldisc.c width.c rect.s texture16.c

.c.o:
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c $<
	$(MSTRIP) -l $<

.s.o:
	$(MCC) -c -g $<
	$(MSTRIP) -l $<

libj.a: $(OBJ)
	rm -f libj.a
	$(MAR) cr libj.a `$(MLORDER) $(OBJ) | tsort`
	$(MAR) ma texture16.o libj.a arith.o display.o

min.o: 	min.s
	$(MCC) -g -c min.s
	$(MSTRIP) -l min.o

arith.o: arith.s
	$(MCC) -g -c arith.s
	$(MSTRIP) -l arith.o

rect.o: rect.s
	$(MCC) -g -c rect.s
	$(MSTRIP) -l rect.o

save:
	-cp $(DMDLIB)/libj.a olibj.a

install: $(DMDLIB)/libj.a

strip:
	-rm -f $(DMDLIB)/libj.a

$(DMDLIB)/libj.a : libj.a
	cp libj.a $(DMDLIB)/libj.a


########
#
#	All dependencies and rules not explicitly stated
#	(including header and nested header dependencies)
#
########

Jrect.o:	Jrect.c
Jrect.o:	$(INC)/dmd.h
Jrect.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c Jrect.c
	$(MSTRIP) -l Jrect.o

arc.o:	arc.c
arc.o:	$(INC)/dmd.h
arc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c arc.c
	$(MSTRIP) -l arc.o

atan2.o:	atan2.c
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c atan2.c
	$(MSTRIP) -l atan2.o

circle.o:	circle.c
circle.o:	$(INC)/dmd.h
circle.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c circle.c
	$(MSTRIP) -l circle.o

comm.o:	comm.c
comm.o:	$(INC)/dmd.h
comm.o:	$(INC)/dmdio.h
comm.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c comm.c
	$(MSTRIP) -l comm.o

cosdeg.o:	cosdeg.c
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c cosdeg.c
	$(MSTRIP) -l cosdeg.o

data.o:	data.c
data.o:	$(INC)/dmd.h
data.o:	$(INC)/dmdio.h
data.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c data.c
	$(MSTRIP) -l data.o

defont.o:	defont.c
defont.o:	$(INC)/font.h
defont.o:	$(INC)/dmd.h
defont.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c defont.c
	$(MSTRIP) -l defont.o

disc.o:	disc.c
disc.o:	$(INC)/dmd.h
disc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c disc.c
	$(MSTRIP) -l disc.o

discture.o:	discture.c
discture.o:	$(INC)/dmd.h
discture.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c discture.c
	$(MSTRIP) -l discture.o

display.o:	display.c
display.o:	$(INC)/dmd.h
display.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c display.c
	$(MSTRIP) -l display.o

elarc.o:	elarc.c
elarc.o:	$(INC)/dmd.h
elarc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c elarc.c
	$(MSTRIP) -l elarc.o

eldisc.o:	eldisc.c
eldisc.o:	$(INC)/dmd.h
eldisc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c eldisc.c
	$(MSTRIP) -l eldisc.o

eldiscture.o:	eldiscture.c
eldiscture.o:	$(INC)/dmd.h
eldiscture.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c eldiscture.c
	$(MSTRIP) -l eldiscture.o

ellipse.o:	ellipse.c
ellipse.o:	$(INC)/dmd.h
ellipse.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c ellipse.c
	$(MSTRIP) -l ellipse.o

exit.o:	exit.c
exit.o:	$(INC)/dmd.h
exit.o:	$(INC)/dmdio.h
exit.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c exit.c
	$(MSTRIP) -l exit.o

fgets.o:	fgets.c
fgets.o:	$(INC)/dmd.h
fgets.o:	$(INC)/dmdio.h
fgets.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c fgets.c
	$(MSTRIP) -l fgets.o

font.o:	font.c
font.o:	$(INC)/font.h
font.o:	$(INC)/dmd.h
font.o:	$(INC)/dmdio.h
font.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c font.c
	$(MSTRIP) -l font.o

fopen.o:	fopen.c
fopen.o:	$(INC)/dmd.h
fopen.o:	$(INC)/dmdio.h
fopen.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c fopen.c
	$(MSTRIP) -l fopen.o

get.o:	get.c
get.o:	$(INC)/dmd.h
get.o:	$(INC)/dmdio.h
get.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c get.c
	$(MSTRIP) -l get.o

getfont.o:	$(INC)/font.h
getfont.o:	getfont.c
getfont.o:	$(INC)/dmd.h
getfont.o:	$(INC)/dmdio.h
getfont.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c getfont.c
	$(MSTRIP) -l getfont.o

introutine.o:	introutine.c
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c introutine.c
	$(MSTRIP) -l introutine.o

jarc.o:	jarc.c
jarc.o:	$(INC)/dmd.h
jarc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c jarc.c
	$(MSTRIP) -l jarc.o

jcircle.o:	jcircle.c
jcircle.o:	$(INC)/dmd.h
jcircle.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c jcircle.c
	$(MSTRIP) -l jcircle.o

jdisc.o:	jdisc.c
jdisc.o:	$(INC)/dmd.h
jdisc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c jdisc.c
	$(MSTRIP) -l jdisc.o

jelarc.o:	jelarc.c
jelarc.o:	$(INC)/dmd.h
jelarc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c jelarc.c
	$(MSTRIP) -l jelarc.o

jeldisc.o:	jeldisc.c
jeldisc.o:	$(INC)/dmd.h
jeldisc.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c jeldisc.c
	$(MSTRIP) -l jeldisc.o

jellipse.o:	jellipse.c
jellipse.o:	$(INC)/dmd.h
jellipse.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c jellipse.c
	$(MSTRIP) -l jellipse.o

jpoint.o:	$(INC)/dmd.h
jpoint.o:	jpoint.c
jpoint.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c jpoint.c
	$(MSTRIP) -l jpoint.o

jstring.o:	$(INC)/font.h
jstring.o:	$(INC)/dmd.h
jstring.o:	jstring.c
jstring.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c jstring.c
	$(MSTRIP) -l jstring.o

norm.o:	norm.c
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c norm.c
	$(MSTRIP) -l norm.o

popen.o:	$(INC)/dmd.h
popen.o:	$(INC)/dmdio.h
popen.o:	popen.c
popen.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c popen.c
	$(MSTRIP) -l popen.o

printf.o:	$(INC)/dmd.h
printf.o:	$(INC)/dmdio.h
printf.o:	printf.c
printf.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c printf.c
	$(MSTRIP) -l printf.o

put.o:	$(INC)/dmd.h
put.o:	$(INC)/dmdio.h
put.o:	put.c
put.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c put.c
	$(MSTRIP) -l put.o

rdwr.o:	$(INC)/dmd.h
rdwr.o:	$(INC)/dmdio.h
rdwr.o:	rdwr.c
rdwr.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c rdwr.c
	$(MSTRIP) -l rdwr.o

rol.o:	rol.c
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c rol.c
	$(MSTRIP) -l rol.o

sqrt.o:	sqrt.c
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c sqrt.c
	$(MSTRIP) -l sqrt.o

string.o:	$(INC)/font.h
string.o:	$(INC)/dmd.h
string.o:	string.c
string.o:	$(INC)/sys/2681.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c string.c
	$(MSTRIP) -l string.o

texture16.o:	$(INC)/dmd.h
texture16.o:	$(INC)/sys/2681.h # nested include from dmd.h
texture16.o:	texture16.c
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c texture16.c
	$(MSTRIP) -l texture16.o

wait.o:	$(INC)/dmd.h
wait.o:	$(INC)/queue.h
wait.o:	$(INC)/sys/2681.h # nested include from dmd.h
wait.o:	wait.c
	$(MCC) $(MCFLAGS) $(LCLCFLAGS) -g -c wait.c
	$(MSTRIP) -l wait.o

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
