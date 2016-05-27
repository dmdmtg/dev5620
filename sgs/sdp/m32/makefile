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
#	COMMON SDP LIBRARY MAKEFILE
#
#	@(#) makefile: 1.5 3/7/84
#
SGS	= 
#
CC	= cc
DMD= /usr/local/dmd
EXTRACFLAGS=-O
CFLAGS	= -DDMD=\"$(DMD)\" $(EXTRACFLAGS)
MESG	= SHORT
OPTS	= SWEET
SWAP	= LRU
# for 3bcc command also include -DTHREEB
DEFLIST	= -D$(MESG) -D$(OPTS) -D$(SWAP) 
INCLIST	= -I$(SDPCOM)
ENV	= 
FRC	=
CC_CMD	= $(CC) -c $(CFLAGS) $(DEFLIST) $(INCLIST) $(ENV)
#
AR	= ar
ARFLAGS	= r
AR_CMD	= $(AR) $(ARFLAGS)
#
CP	= cp
RM	= rm
#
LINT	= lint
LINTFLAGS = -p
O	= o
#
PRINT	= pr
PRFLAGS	= -n
LP	= lp
LPFLAGS	=
#
#	External Directories
#
ROOT 	= 
LIBDIR	=  $(ROOT)/lib
#
#	Internal Directories
#
SGSBASE	= ../..
SDPCOM	= $(SGSBASE)/sdp/common
#
HFILES	= $(SDPCOM)/sdp.h $(SDPCOM)/define2.h $(SDPCOM)/define3.h
SOURCE	= $(SDPCOM)/allot.c $(SDPCOM)/change.c $(SDPCOM)/chstack.c \
	  $(SDPCOM)/connect.c $(SDPCOM)/copy.c $(SDPCOM)/destroy.c \
	  $(SDPCOM)/disconnect.c $(SDPCOM)/generate.c $(SDPCOM)/hist.c \
	  $(SDPCOM)/house.c $(SDPCOM)/redeem.c $(SDPCOM)/stats.c \
	  $(SDPCOM)/sync.c $(SDPCOM)/unuse.c $(SDPCOM)/use.c $(SDPCOM)/vacate.c\
	  $(SDPCOM)/pop_id.c $(SDPCOM)/push_id.c $(SDPCOM)/fault.c \
	  $(SDPCOM)/rdSPACE.c $(SDPCOM)/readpage.c $(SDPCOM)/search.c \
	  $(SDPCOM)/switch.c $(SDPCOM)/writeframe.c $(SDPCOM)/wtSPACE.c \
	  $(SDPCOM)/audit.c $(SDPCOM)/globals.c $(SDPCOM)/sdplib.c \
	  $(SDPCOM)/fatal.c
#
OBJECTS	=  allot.$O change.$O chstack.$O \
	connect.$O copy.$O destroy.$O \
	disconnect.$O generate.$O hist.$O \
	house.$O redeem.$O stats.$O \
	sync.$O unuse.$O use.$O \
	vacate.$O pop_id.$O push_id.$O \
	fault.$O rdSPACE.$O readpage.$O \
	search.$O switch.$O writeframe.$O \
	wtSPACE.$O audit.$O globals.$O \
	sdplib.$O fatal.$O
#
all:	sdp.a
#
sdp.a:	$(OBJECTS) $(FRC)
	$(RM) -f sdp.a
	$(AR_CMD) sdp.a $(OBJECTS)
	ranlib sdp.a 2>/dev/null || true
#
allot.$O:	$(SDPCOM)/allot.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/allot.c
#
audit.$O:	$(SDPCOM)/audit.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/audit.c
#
change.$O:	$(SDPCOM)/change.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/change.c
#
chstack.$O:	$(SDPCOM)/chstack.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h  $(FRC)\
		$(SDPCOM)/define2.h
	$(CC_CMD) $(SDPCOM)/chstack.c
#
connect.$O:	$(SDPCOM)/connect.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/connect.c
#
copy.$O:	$(SDPCOM)/copy.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h  $(FRC)\
		$(SDPCOM)/define2.h
	$(CC_CMD) $(SDPCOM)/copy.c
#
destroy.$O:	$(SDPCOM)/destroy.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h  $(FRC)\
		$(SDPCOM)/define2.h
	$(CC_CMD) $(SDPCOM)/destroy.c
#
disconnect.$O:	$(SDPCOM)/disconnect.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/disconnect.c
#
fatal.$O:	$(SDPCOM)/fatal.c $(SDPCOM)/sdp.h $(FRC)
	$(CC_CMD) $(SDPCOM)/fatal.c
#
fault.$O:	$(SDPCOM)/fault.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/fault.c
#
globals.$O:	$(SDPCOM)/globals.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h  $(FRC)\
		$(SDPCOM)/define2.h
	$(CC_CMD) $(SDPCOM)/globals.c
#
generate.$O:	$(SDPCOM)/generate.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/generate.c
#
hist.$O: 	$(SDPCOM)/hist.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/hist.c
#
house.$O:	$(SDPCOM)/house.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/house.c
#
pop_id.$O:	$(SDPCOM)/pop_id.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/pop_id.c
#
push_id.$O:	$(SDPCOM)/push_id.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/push_id.c
#
rdSPACE.$O:	$(SDPCOM)/rdSPACE.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h  $(FRC)\
		$(SDPCOM)/define2.h
	$(CC_CMD) $(SDPCOM)/rdSPACE.c
#
readpage.$O:	$(SDPCOM)/readpage.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/readpage.c
#
redeem.$O:	$(SDPCOM)/redeem.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/redeem.c
#
sdplib.$O:	$(SDPCOM)/sdplib.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h  $(FRC) \
		$(SDPCOM)/define2.h
	$(CC_CMD) $(SDPCOM)/sdplib.c
#
search.$O:	$(SDPCOM)/search.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/search.c
#
stats.$O:	$(SDPCOM)/stats.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/stats.c
#
switch.$O:	$(SDPCOM)/switch.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/switch.c
#
sync.$O: 	$(SDPCOM)/sync.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/sync.c
#
unuse.$O:	$(SDPCOM)/unuse.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/unuse.c
#
use.$O:  	$(SDPCOM)/use.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/use.c
#
vacate.$O:	$(SDPCOM)/vacate.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/vacate.c
#
writeframe.$O:	$(SDPCOM)/writeframe.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/writeframe.c
#
wtSPACE.$O:	$(SDPCOM)/wtSPACE.c $(SDPCOM)/sdp.h $(SDPCOM)/define3.h $(FRC)
	$(CC_CMD) $(SDPCOM)/wtSPACE.c
#
#
install:	$(LIBDIR)/sdp.a
#
$(LIBDIR)/sdp.a:	sdp.a
	$(RM) -f $(LIBDIR)/sdp.a
	$(CP) sdp.a $(LIBDIR)/sdp.a
#
save:
	$(RM) -f $(LIBDIR)/sdp.a.back
	$(CP) $(LIBDIR)/sdp.a $(LIBDIR)/sdp.a.back
#
stripit:	uninstall
uninstall:
	$(RM) -f $(LIBDIR)/sdp.a
#
shrink:
	$(RM) -f $(OBJECTS) sdp.a
#
clean:	shrink
#
clobber:	clean
	$(RM) -f sdp.a
#
lint:	$(HFILES) $(SOURCE)
	$(LINT) $(LINTFLAGS) $(DEFLIST) $(INCLIST) $(SOURCE)
#
listing:	$(HFILES) $(SOURCE)
	$(PRINT) $(PRFLAGS) $(HFILES) $(SOURCE) | $(LP) $(LPFLAGS)
#
FRC:
