# 
#									
#	Copyright (c) 1987,1988,1989,1990,1991,1992   AT&T		
#			All Rights Reserved				
#									
#	  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T.		
#	    The copyright notice above does not evidence any		
#	   actual or intended publication of such source code.		
#									
# 
#
#	WE-32000 GLOBAL MAKEFILE
#
#	@(#) template.mk: 1.23 4/6/84
#
DMD=/usr/local/dmd
#	SGS indicates the prefix to be applied to the installed commands.
SGS=m32
#
#	The following macros define the various installation directories.
#	Note that if relative pathnames are used, they must allow for the
#	"cd" issued prior to each make.
#
#	BASE is the directory under which all the sgs source lives
BASE=.
#
#	BINDIR is the directory for installing executable ("bin") files.
#	It should correspond to the same directory as specified in AS and LD
#	in paths.h.
BINDIR=$(DMD)/bin
BINROOT=$(DMD)
#
#	LIBDIR is the directory for installing libraries and executable
#	files not intended for direct user execution (e.g., assembler pass1).
#	It should correspond to the same directory as specified in COMP,
#	OPTIM, AS1, and AS2 in paths.h.
LIBDIR=$(DMD)/lib
#
#	MANDIR is the directory for installing manual pages for the commands
#	installed in BINDIR.
MANDIR=$(DMD)/man
INCROOT=$(DMD)/include
INCDIR=$(DMD)/include/sgs
#
#	Specify the byte order for this SGS instance.
#		FBO = Forward Byte Order (3B20, IBM)
#		RBO = Reverse Byte Order (DEC)
DBO=`$(BASE)/../../dbotst`
#
#	If host machine is running a pre-5.0 release of UNIX
#	then set Archive Format to "OLDAR".
#	Starting with the 5.0 UNIX release the Archive Format
#	should be set to "PORTAR".
#	If building a 5.0 release on a host that is running
#	6.0, then set ARFORMAT to PORT5AR.
#
ARFORMAT=PORTAR
#
#	Starting with the 6.0 release of UNIX,
#	if flexnames feature is desired, then set FLEX
#	to -DFLEXNAMES.
#	If host machine is running a pre-6.0 release of UNIX
#	then set FLEX to null (ie. FLEX= ).
#
FLEX=-DFLEXNAMES
#
#	MAC parameter specifies the set of software workarounds
#	to be produced by the new sgs.
#	MAC=ABWORMAC produces sgs for 32A and 32B chips.
#	MAC=BMAC produces sgs for 32B  o n l y.
#
MAC=ABWORMAC
#	This is the machine ID field. The valid values are
#	D_u3b5 or D_u3b2.
MACH=D_u3b5
#
#	The following parameter specifies the default include directory
#	for cpp. If not defined the value will be /usr/include.
#
USRINC=$(DMD)/include
#
#	ARCH indicates the architecture of the host machine
#		AR16WR=11/70, AR32WR=vax, AR32W=ibm, 3b20, etc
ARCH=`$(BASE)/../../archtst`
#
#
MAKE=make
CC=cc
FFLAG=
ENV=
ROOT=
VERSION=
LIBLD=$(BASE)/libld/m32/libld.a
EXTRACFLAGS=-O
#
#
ENVPARMS=MAKE="$(MAKE)" SGS="$(SGS)" ARCH="$(ARCH)" \
	DBO="$(DBO)" ARFORMAT="$(ARFORMAT)" FLEX="$(FLEX)"

CCPARMS=CC="$(CC)" FFLAG="$(FFLAG)" ENV="$(ENV)" ROOT="$(ROOT)" \
	VERSION="$(VERSION)" DMD="$(DMD)" EXTRACFLAGS="$(EXTRACFLAGS)"
DIRPARMS=BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)"
#
#
all: archtst dbotst inc libld ar sdp comp2 cpp cmd optim as ld compress \
	convert dis dump list lorder nm size strip dmdcc

archtst:	archtst.c
	cc archtst.c -o archtst $(EXTRACFLAGS)

dbotst:	dbotst.c
	cc dbotst.c -o dbotst $(EXTRACFLAGS)

inc:	FRC
	cd $(BASE)/inc/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
libld:	FRC
	cd $(BASE)/libld/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
ar:	FRC
	cd $(BASE)/ar/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
sdp:	FRC
	cd $(BASE)/sdp/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
comp2:	FRC
	cd $(BASE)/comp2/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
cpp:	FRC
	cd $(BASE)/cpp/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) PD_SYS=D_unix \
		PD_MACH=$(MACH) USRINC=$(USRINC) INCDIR=$(INCDIR)
cmd:	FRC
	cd $(BASE)/cmd/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
optim:	FRC
	cd $(BASE)/optim/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
as:	FRC
	cd $(BASE)/as/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) MAC=$(MAC)
ld:	FRC
	cd $(BASE)/ld/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
compress:	FRC
	cd $(BASE)/compress/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
convert:	FRC
	cd $(BASE)/convert/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
dis:	FRC
	cd $(BASE)/dis/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
dump:	FRC
	cd $(BASE)/dump/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
list:	FRC
	cd $(BASE)/list/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
lorder:	FRC
	cd $(BASE)/lorder/m32; $(MAKE) ${MFLAGS} $(ENVPARMS)
nm:	FRC
	cd $(BASE)/nm/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
size:	FRC
	cd $(BASE)/size/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
strip:	FRC
	cd $(BASE)/strip/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
dmdcc:	FRC
	cd $(BASE)/dmdcc/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS)
doc:	FRC
	cd $(BASE)/doc/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) MANDIR=$(MANDIR)
FRC:
#
first:
	-mkdir $(BINROOT) 
	-mkdir $(BINDIR) 
	-mkdir $(LIBDIR)
	-mkdir $(MANDIR)
	-mkdir $(INCROOT)
	-mkdir $(INCDIR)
#
install: all first
	cd $(BASE)/libld/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/ar/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/sdp/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/comp2/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/cpp/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/cmd/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/optim/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/as/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/ld/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/compress/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/convert/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/dis/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/dump/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/list/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/lorder/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) install
	cd $(BASE)/nm/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/size/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/strip/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
	cd $(BASE)/dmdcc/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(CCPARMS) $(DIRPARMS) install
#	cd $(BASE)/doc/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) MANDIR=$(MANDIR) install
#
save:
	cd $(BASE)/libld/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/sdp/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) save
	cd $(BASE)/ar/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/comp2/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/cpp/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/cmd/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/optim/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/as/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/ld/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/compress/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/convert/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/dis/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/dump/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/list/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/lorder/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/nm/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/size/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
	cd $(BASE)/strip/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) save
#	cd $(BASE)/doc/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) MANDIR=$(MANDIR) save
#
stripit:	uninstall
uninstall:
	cd $(BASE)/libld/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/sdp/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/ar/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/comp2/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/cpp/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/cmd/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/optim/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/as/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/ld/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/compress/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/convert/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/dis/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/dump/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/list/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/lorder/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/nm/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/size/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/strip/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
	cd $(BASE)/dmdcc/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) uninstall
#	cd $(BASE)/doc/m32; $(MAKE) ${MFLAGS} $(ENVPARMS) $(DIRPARMS) MANDIR=$(MANDIR) uninstall
#
clean:	shrink
shrink:
	cd $(BASE)/libld/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/ar/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/sdp/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/comp2/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/cpp/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/cmd/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/optim/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/as/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/ld/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/compress/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/convert/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/dis/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/dump/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/list/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/lorder/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/nm/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/size/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/strip/m32; $(MAKE) ${MFLAGS} shrink
	cd $(BASE)/dmdcc/m32; $(MAKE) ${MFLAGS} shrink
#	cd $(BASE)/doc/m32; $(MAKE) ${MFLAGS} shrink
	rm -f archtst dbotst
