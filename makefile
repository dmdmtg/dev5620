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
### Standard Defines ###

###############################################################################
# Change only DMD
###############################################################################
#
DMD=/usr/local/dmd
#
###############################################################################
# EXTRACFLAGS is for any extra cc options for compiling and linking for
#  a particular unix platform
###############################################################################
#
EXTRACFLAGS=-O
# Use the following for Solaris
# EXTRACFLAGS=-O -DUSE_SYSVR4LIKE -lsocket -lnsl
# Use the following for HP-PA
# EXTRACFLAGS=-O -D_CLASSIC_TYPES
#
###############################################################################
# REXEC is used by programs that allow a remote host invocation
###############################################################################
#
REXEC=/usr/ucb/rsh
#
###############################################################################
# DMDTERM is used only by programs that compile for 5620 or 630 terminals
###############################################################################
#
# DMDTERM=DMD630
DMDTERM=DMD5620
#
###############################################################################
# The following defines should NOT be changed
###############################################################################
#
DMDBIN=$(DMD)/bin
DMDLIB=$(DMD)/lib
DMDSRC=../src
DMDINC=$(DMD)/include
DMDCCSINC=$(DMD)/include/sgs
DMDXT=$(DMD)/xt
DMDLOAD=32ld
MCC=$(DMD)/bin/dmdcc $(CMSFLG)
MAR=$(DMD)/bin/dmdar
MSTRIP=$(DMD)/bin/m32strip
MLORDER=$(DMD)/bin/m32lorder
MODE775=755
MODE664=644

### Specific Defines ###
MAKE_ARGS=	$(MFLAGS) DMD="$(DMD)" DMDBIN="$(DMDBIN)" DMDLIB="$(DMDLIB)" \
		DMDSRC="$(DMDSRC)" DMDINC="$(DMDINC)" DMDCCSINC="$(DMDCCSINC)" \
		MCC="$(MCC)" MAR="$(MAR)" MSTRIP="$(MSTRIP)" \
		MLORDER="$(MLORDER)" MODE775="$(MODE775)" MODE664="$(MODE664)" \
		DMDTERM="$(DMDTERM)" DMDLOAD="$(DMDLOAD)" REXEC="$(REXEC)" \
		EXTRACFLAGS="$(EXTRACFLAGS)"

PRODUCTS=	include sgs lib misc 32ld jx man dmdp \
		icon jim icons

### Standard Targets ###

default:	build

all:		$(PRODUCTS)

build:	mkdirs
		@set -x; p=`pwd`; for d in $(PRODUCTS); do \
		    cd $$p/$$d; \
		    case $$d in \
			include|sgs|lib) \
			    make $(MAKE_ARGS) install;; \
			*)  make $(MAKE_ARGS) ;; \
		    esac; \
		done

install:	mkdirs
		@set -x; p=`pwd`; for d in $(PRODUCTS); do \
		    cd $$p/$$d; make $(MAKE_ARGS) install; \
		done

mkdirs:
		-mkdir $(DMD)
		-chmod $(MODE775) $(DMD)
		-mkdir $(DMDBIN)
		-chmod $(MODE775) $(DMDBIN)
		-mkdir $(DMDLIB)
		-chmod $(MODE775) $(DMDLIB)
		-mkdir $(DMDINC)
		-chmod $(MODE775) $(DMDINC)
		-mkdir $(DMDCCSINC)
		-chmod $(MODE775) $(DMDCCSINC)

$(PRODUCTS):	FRC
		cd $@; make $(MAKE_ARGS)

clobber:	clean
clean:
		@set -x; p=`pwd`; for d in $(PRODUCTS); do \
		    cd $$p/$$d; make $(MAKE_ARGS) clean; \
		done

### Additional Dependencies ###
FRC:
