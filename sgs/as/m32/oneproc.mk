#
#	WE32000 AS MAKEFILE
#
#	@(#) oneproc.mk: 1.10 3/5/84
#
SGS=m32
CC=cc
CFLAGS=-O -c
ARCH=AR32W
DBO=FBO
PCCALL=CALLPCREL
#	Set FLEX to -DFLEXNAMES for flexnames (post 6.0)
FLEX= -DFLEXNAMES
DEFLIST=-D$(ARCH) -D$(DBO) -DONEPROC -D$(PCCALL) $(FLEX) -D$(MAC)
INCLIST=-I. -I$(COMAS) -I$(COMINC) -I$(M32INC) -I$(USRINC)
ENV=
CC_CMD=$(CC) $(CFLAGS) $(DEFLIST) $(INCLIST) $(ENV)
#
LD=$(CC)
LDFLAGS=$(FFLAG)
LD_CMD=$(LD) $(LDFLAGS)
#
B30=
#
YACC=yacc
YFLAGS=-d
YACC_CMD=$(YACC) $(YFLAGS)
#
STRIP=strip
SPFLAGS=
STRIP_CMD=$(STRIP) $(SPFLAGS)
#
LINT=lint
LINTFLAGS=-p
LINT_CMD=$(LINT) $(LINTFLAGS)
#
#	Internal Directories
#
BASE= ../..
M32INC= $(BASE)/inc/m32
COMAS= $(BASE)/as/common
COMINC= $(BASE)/inc/common
BINDIR= $(BASE)/xenv/m32/bin
LIBDIR= $(BASE)/xenv/m32/lib
#
#	External Directories
#
ROOT=
VERSION=
USRINC=$(ROOT)/usr/$(VERSION)include
#
LIBM=-lm
#
OFILES=pass0.o instab.o parse.o gencode.o pass1.o strings.o symbols.o \
	code.o expand1.o expand2.o errors.o addr2.o float.o \
	pass2.o addr1.o codeout.o getstab.o obj.o symlist.o swagen.o
#
CFILES=$(COMAS)/pass0.c \
	parse.c $(COMAS)/code.c $(COMAS)/errors.c gencode.c \
	swagen.c $(COMAS)/instab.c \
	$(COMAS)/pass1.c $(COMAS)/strings.c $(COMAS)/symbols.c \
	$(COMAS)/expand1.c expand2.c float.c \
	$(COMAS)/addr1.c addr2.c $(COMAS)/codeout.c \
	$(COMAS)/getstab.c $(COMAS)/pass2.c $(COMAS)/obj.c \
	$(COMAS)/symlist.c
#
HFILES=$(COMAS)/codeout.h gendefs.h instab.h \
	ops.out $(COMAS)/symbols.h \
	$(M32INC)/paths.h $(COMAS)/expand.h expand2.h parse.h \
	$(COMINC)/reloc.h $(COMINC)/syms.h $(COMINC)/storclass.h\
	$(COMINC)/filehdr.h $(COMINC)/scnhdr.h $(COMINC)/linenum.h \
	$(M32INC)/sgs.h
#
all	: as
#
as	: $(OFILES)
		$(LD_CMD) -o as $(OFILES) $(LIBM)
#
pass0.o		: $(COMAS)/pass0.c pass0.h $(M32INC)/paths.h $(M32INC)/sgs.h systems.h
		$(CC_CMD) $(COMAS)/pass0.c
#
parse.o		: parse.c $(COMAS)/symbols.h $(COMINC)/filehdr.h instab.h systems.h\
		 gendefs.h $(COMINC)/storclass.h $(M32INC)/sgs.h
		$(CC_CMD) $(B30) -DYYDEBUG=0 parse.c
#
parse.c parse.h	: parse.y
		$(YACC_CMD) parse.y
		mv y.tab.c parse.c
		mv y.tab.h parse.h
#
code.o		: $(COMAS)/code.c $(COMAS)/symbols.h $(COMAS)/codeout.h gendefs.h systems.h
		$(CC_CMD) $(COMAS)/code.c
#
errors.o	: $(COMAS)/errors.c gendefs.h systems.h
		$(CC_CMD) $(COMAS)/errors.c
#
pass1.o		: $(COMAS)/pass1.c $(M32INC)/paths.h $(COMAS)/symbols.h gendefs.h systems.h
		$(CC_CMD) $(COMAS)/pass1.c
#
strings.o	: $(COMAS)/strings.c gendefs.h systems.h
		$(CC_CMD) $(COMAS)/strings.c
#
instab.o	: $(COMAS)/instab.c instab.h ops.out \
		  $(COMAS)/symbols.h parse.h systems.h
		$(CC_CMD) $(COMAS)/instab.c
#
gencode.o	: gencode.c $(COMAS)/symbols.h instab.h systems.h \
		  parse.h gendefs.h $(COMAS)/expand.h expand2.h
		$(CC_CMD) gencode.c
#
swagen.o	: swagen.c $(COMAS)/symbols.h instab.h systems.h \
		  parse.h gendefs.h $(COMAS)/expand.h expand2.h
		$(CC_CMD) swagen.c
#
expand1.o	: $(COMAS)/expand1.c $(COMAS)/expand.h $(COMAS)/symbols.h gendefs.h systems.h
		$(CC_CMD) $(COMAS)/expand1.c
#
expand2.o	: expand2.c $(COMAS)/expand.h expand2.h $(COMAS)/symbols.h systems.h
		$(CC_CMD) expand2.c
#
float.o		: float.c instab.h $(COMAS)/symbols.h systems.h 
		$(CC_CMD) float.c
#
addr1.o		: $(COMAS)/addr1.c $(COMINC)/reloc.h $(COMINC)/syms.h \
		  $(COMINC)/storclass.h $(COMINC)/linenum.h $(COMINC)/filehdr.h \
		  gendefs.h $(COMAS)/symbols.h $(COMAS)/codeout.h systems.h
		$(CC_CMD) $(COMAS)/addr1.c
#
addr2.o		: addr2.c $(COMINC)/reloc.h $(COMINC)/storclass.h systems.h \
		  $(COMINC)/syms.h gendefs.h $(COMAS)/symbols.h \
		  $(COMAS)/codeout.h instab.h
		$(CC_CMD) addr2.c
#
codeout.o	: $(COMAS)/codeout.c $(COMAS)/symbols.h $(COMAS)/codeout.h gendefs.h systems.h
		$(CC_CMD) $(COMAS)/codeout.c
#
getstab.o	: $(COMAS)/getstab.c gendefs.h $(COMAS)/symbols.h systems.h
		$(CC_CMD) $(COMAS)/getstab.c
#
pass2.o		: $(COMAS)/pass2.c gendefs.h $(COMAS)/symbols.h systems.h
		$(CC_CMD) $(COMAS)/pass2.c
#
obj.o		: $(COMAS)/obj.c $(COMINC)/filehdr.h $(COMINC)/linenum.h instab.h \
		$(COMINC)/reloc.h $(COMINC)/scnhdr.h $(COMINC)/syms.h $(COMINC)/storclass.h \
		$(COMAS)/symbols.h $(COMAS)/codeout.h gendefs.h $(M32INC)/sgs.h systems.h
		$(CC_CMD) $(COMAS)/obj.c
#
symlist.o	: $(COMAS)/symlist.c $(COMAS)/symbols.h $(COMINC)/syms.h \
		  $(COMINC)/storclass.h gendefs.h systems.h
		$(CC_CMD) $(COMAS)/symlist.c
#
symbols.o	: $(COMAS)/symbols.c $(COMAS)/symbols.h symbols2.h systems.h
		$(CC_CMD) $(COMAS)/symbols.c
#
lint.out	: $(CFILES) $(HFILES) 
		$(LINT_CMD) $(DEFLIST) $(INCLIST) $(CFILES) >lint.out
		wc -l lint.out
#
install		: $(BINDIR)/$(SGS)as $(LIBDIR)/cm4defs $(LIBDIR)/cm4tvdefs
#
$(BINDIR)/$(SGS)as:	as
		-rm -f $(BINDIR)/$(SGS)as
		cp as $(BINDIR)/$(SGS)as
		-$(STRIP_CMD) $(BINDIR)/$(SGS)as
$(LIBDIR)/cm4defs:	cm4defs
		-rm -f $(LIBDIR)/cm4defs
		cp cm4defs $(LIBDIR)/cm4defs
$(LIBDIR)/cm4tvdefs:	cm4tvdefs
		-rm -f $(LIBDIR)/cm4tvdefs
		cp cm4tvdefs $(LIBDIR)/cm4tvdefs
#
save		: $(BINDIR)/$(SGS)as $(LIBDIR)/cm4defs $(LIBDIR)/cm4tvdefs
		-rm -f $(BINDIR)/$(SGS)as.back
		cp $(BINDIR)/$(SGS)as $(BINDIR)/$(SGS)as.back
		-rm -f $(LIBDIR)/cm4defs.back $(LIBDIR)/cm4tvdefs.back
		cp $(LIBDIR)/cm4defs $(LIBDIR)/cm4defs.back
		cp $(LIBDIR)/cm4tvdefs $(LIBDIR)/cm4tvdefs.back
#
stripit:	uninstall
uninstall	:
		-rm -f $(BINDIR)/$(SGS)as
		-rm -f $(LIBDIR)/cm4defs $(LIBDIR)/cm4tvdefs
#
shrink		:
		-rm -f $(OFILES) parse.c parse.h y.output lint.out
		-rm -f as
#
listall		: $(CFILES) $(HFILES)
		pr -f $(HFILES) $(CFILES) | lp
