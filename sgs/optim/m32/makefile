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
# 	@(#) makefile: 1.6 3/3/84
#
#	WE32000 OPTIMIZER MAKEFILE
#
#
SGS=m32
CC=cc
#
DMD= /usr/local/dmd
EXTRACFLAGS=-O
CFLAGS=-c -DDMD=\"$(DMD)\" $(EXTRACFLAGS)
XMAXPC=\"50\"
ARCH=AR32W
DEFLIST=-D$(ARCH) -DM32
INCLIST= -I. -I$(COMOPT) -I$(M32INC) -I$(USRINC)
ENV=
CC_CMD=$(CC) $(CFLAGS) $(DEFLIST) $(INCLIST) $(ENV)
LINT_CMD= lint $(LFLAGS) $(DEFLIST) $(INCLIST) $(ENV)
#
LD=$(CC)
LDFLAGS=
LD_CMD=$(LD) $(LDFLAGS)
#
STRIP=strip
SPFLAGS=
STRIP_CMD=$(STRIP) $(SPFLAGS)
#
LINT=lint
LFLAGS=-abch -DDMD=\"$(DMD)\" -DMAXPC=$(XMAXPC)
ROOT=
VERSION=
#
#	Internal Directories
#
BASE= ../..
BINDIR= $(BASE)/xenv/m32/bin
LIBDIR= $(BASE)/xenv/m32/lib
M32INC= $(BASE)/inc/m32
COMOPT= $(BASE)/optim/common
USRINC=$(ROOT)/usr/$(VERSION)include
#
OBJECTS= optim.o inter.o local.o \
	optutil.o peep.o w1opt.o w2opt.o w3opt.o func.o
SRC= ../common/optim.c ../common/inter.c local.c \
	optutil.c peep.c w1opt.c w2opt.c w3opt.c func.c
#
all:		optim
#
lint:	FRC
	$(LINT_CMD) $(SRC)
optim:		$(OBJECTS)
		$(LD_CMD) -o optim $(OBJECTS)
#
optim.o:	$(COMOPT)/optim.h defs $(COMOPT)/optim.c
		$(CC_CMD) $(COMOPT)/optim.c
#
inter.o:	$(COMOPT)/optim.h defs $(COMOPT)/inter.c
		$(CC_CMD) $(COMOPT)/inter.c
#
local.o:	$(M32INC)/sgs.h $(M32INC)/paths.h $(COMOPT)/optim.h defs local.c
		$(CC_CMD) local.c
#
optutil.o:	defs $(COMOPT)/optim.h optutil.c
		$(CC_CMD) optutil.c
#
peep.o:		defs $(COMOPT)/optim.h peep.c
		$(CC_CMD) peep.c
#
w1opt.o:	optutil.h defs $(COMOPT)/optim.h w1opt.c
		$(CC_CMD) w1opt.c
#
w2opt.o:	optutil.h defs $(COMOPT)/optim.h w2opt.c
		$(CC_CMD) w2opt.c
#
w3opt.o:	optutil.h defs $(COMOPT)/optim.h w3opt.c
		$(CC_CMD) w3opt.c
#
func.o:		optutil.h defs $(COMOPT)/optim.h func.c
		$(CC_CMD) -DMAXPC=$(XMAXPC) func.c
#
install:	$(LIBDIR)/optim
#
$(LIBDIR)/optim:	optim
		-rm -f $(LIBDIR)/optim
		cp optim $(LIBDIR)/optim
		-$(STRIP_CMD) $(LIBDIR)/optim
#
save:		$(LIBDIR)/optim
		-rm -f $(LIBDIR)/optim.back
		cp $(LIBDIR)/optim $(LIBDIR)/optim.back
#
stripit:	uninstall
uninstall:
		-rm -f $(LIBDIR)/optim
#
shrink:		clean
clobber:	clean
clean:
		-rm -f $(OBJECTS)
		-rm -f optim
FRC:
