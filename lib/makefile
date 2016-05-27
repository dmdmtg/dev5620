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

DMD=/usr/local/dmd
DMDBIN=$(DMD)/bin
DMDLIB=$(DMD)/lib
DMDSRC=$(DMD)/src
DMDINC=$(DMD)/include
DMDCCSINC=$(DMD)/include/sgs
MCC=$(DMD)/bin/dmdcc $(CMSFLG)
MAR=$(DMD)/bin/dmdar
MSTRIP=$(DMD)/bin/m32strip
MLORDER=$(DMD)/bin/m32lorder
MODE775=755
MODE664=644
CFLAGS=-O

### Specific Defines ###
MAKE_ARGS=	$(MFLAGS) DMD="$(DMD)" DMDBIN="$(DMDBIN)" DMDLIB="$(DMDLIB)" \
		DMDSRC="$(DMDSRC)" DMDINC="$(DMDINC)" DMDCCSINC="$(DMDCCSINC)" \
		MCC="$(MCC)" MAR="$(MAR)" MSTRIP="$(MSTRIP)" \
		CFLAGS="$(CFLAGS)" MLORDER="$(MLORDER)" MODE775="$(MODE775)" \
		MODE664="$(MODE664)"

PRODUCTS= startup libc libg libj libmj libsys layersys

### Standard Targets ###

all:		$(PRODUCTS)

build:		install

install:
		-mkdir $(DMDLIB)
		-chmod $(MODE775) $(DMDLIB)
		@set -x; p=`pwd`; for d in $(PRODUCTS); do \
		    cd $$p/$$d; make $(MAKE_ARGS) install; \
		done

$(PRODUCTS):	FRC
		cd $@; make $(MAKE_ARGS)

clobber:	clean
clean:
		@set -x; p=`pwd`; for d in $(PRODUCTS); do \
		    cd $$p/$$d; make $(MAKE_ARGS) clean; \
		done

### Additional Dependencies ###
FRC:
