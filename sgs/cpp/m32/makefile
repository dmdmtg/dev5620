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
#	Cpp Makefile
#
#  @(#) makefile: 1.2 3/1/84
#
SGS	=
#
# the two variables NEW_MACH and NEW_SYS are used to create new instances
# of cpp by giving new machine and/or system names to cpp.c.  These
# should be used with PD_MACH=D_newmach and PD_SYS=D_newsys.
# NEW_MACH and NEW_SYS are used (just as SGSINC is) as a string in cpp.c
#
PD_MACH	= D_nomach
PD_SYS	= D_unix
NEW_MACH =
NEW_SYS	=
#
#	External Directories
#
ROOT	=
SGSBASE	= ../..
LIBDIR	= $(DMD)/lib
USRINC	= $(DMD)/include
INCDIR	= $(USRINC)/sgs
#
#	Internal Directories
#
CPPCOM	= $(SGSBASE)/cpp/common
#
#	Compilation Parameters
#
CC	= cc
DMD= /usr/local/dmd
EXTRACFLAGS = -O
CFLAGS	= -DDMD=\"$(DMD)\" $(EXTRACFLAGS)
FLEX	= -DFLEXNAMES
DEFLIST	= $(FLEX) 
ENVPARMS = -DSGSINC=\"$(INCDIR)\" -DUSRINC=\"$(USRINC)\" -DPD_MACH=$(PD_MACH) -DPD_SYS=$(PD_SYS)
ENV	=
LDFLAGS	=
LIBES	=
#
#	Lint Parameters
#
LINT	= lint
LINTFLAGS = -p
O	= o
#
#	Other Commands
#
SH	= sh
YACC	= yacc
YFLAGS	= -d
STRIP	= strip
SPFLAGS	=
CP	= cp
RM	= rm
PRINT	= pr
PRFLAGS	= -n
LP	= lp
#
PROT	= 755
GRP	= bin
OWN	= bin
#
FRC	=
#
#	Files making up cpp
#
OBJECTS	= cpp.$O cpy.$O rodata.$O yylex.$O strchr.$O
SOURCE	= $(CPPCOM)/cpy.y $(CPPCOM)/yylex.c $(CPPCOM)/cpp.c $(CPPCOM)/strchr.c
#
all:	cpp
#
cpp:	$(OBJECTS) $(FRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o cpp $(OBJECTS) $(LIBES)
#
y.tab.h cpy.c : $(CPPCOM)/cpy.y $(FRC)
	$(YACC) $(YFLAGS) $(CPPCOM)/cpy.y
	$(SH) $(CPPCOM)/:yyfix >rodata.c; \
	mv y.tab.c cpy.c
#
strchr.$O:	$(CPPCOM)/strchr.c
	$(CC) $(CFLAGS) -c $(CPPCOM)/strchr.c
cpy.$O:	cpy.c $(FRC)
	$(CC) $(CFLAGS) $(DEFLIST) $(ENV) -c cpy.c
#
yylex.$O: $(CPPCOM)/yylex.c y.tab.h $(FRC)
	$(CC) $(CFLAGS) $(DEFLIST) $(ENV) -I. -c $(CPPCOM)/yylex.c
#
cpp.$O: $(CPPCOM)/cpp.c $(FRC)
	$(CC) $(CFLAGS) $(DEFLIST) $(ENVPARMS) $(NEW_SYS) $(NEW_MACH) $(ENV) -c $(CPPCOM)/cpp.c
#
rodata.$O: cpy.c $(FRC)
	$(CC) $(CFLAGS) $(DEFLIST) $(ENV) -S rodata.c
	$(SH) $(CPPCOM)/:rofix rodata.s; \
	$(CC) $(CFLAGS) -c rodata.s
#
shrink:	clobber
#
clean :
	$(RM) -f rodata.s $(OBJECTS)
#
clobber: clean
	$(RM) -f cpp
#
install : $(LIBDIR)/$(SGS)cpp
#
$(LIBDIR)/$(SGS)cpp:	cpp
	$(RM) -f $(LIBDIR)/cpp
	$(CP) cpp $(LIBDIR)/cpp
	$(STRIP) $(LIBDIR)/cpp
	chmod $(PROT) $(LIBDIR)/cpp
#	chgrp $(GRP) $(LIBDIR)/cpp
#	chown $(OWN) $(LIBDIR)/cpp
#
save:
	$(RM) -f $(LIBDIR)/$(SGS)cpp.back
	$(CP) $(LIBDIR)/$(SGS)cpp $(LIBDIR)/$(SGS)cpp.back
#
stripit:	uninstall
uninstall:
	$(RM) -f $(LIBDIR)/cpp
#
lint:	$(SOURCE)
	$(LINT) $(LINTFLAGS) $(DEFLIST) $(SOURCE)
#
listing:	$(SOURCE) 
	$(PRINT) $(PRFLAGS) $(SOURCE) $(CPPCOM)/:yyfix $(CPPCOM)/:rofix | $(LP)
#
FRC:
