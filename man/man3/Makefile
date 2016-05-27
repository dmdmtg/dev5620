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
DMD=	/usr/local/dmd
MDIR=	$(DMD)/man/man3
MODE664=644

SRCS=	addr.3 agent.3 alloc.3 atoi.3 balloc.3 bitblt.3 bits.3 buttons.3 \
	canon.3 circle.3 ctype.3 cursor.3 ellipse.3 eq.3 exit.3 \
	gcalloc.3 getfont.3 getrect.3 globals.3 hagent.3 indirect.3 \
	inset.3 integer.3 itox.3 jcircle.3 jellipse.3 \
	jmove.3 jpoint.3 jrectf.3 jsegment.3 jstring.3 jtexture.3 \
	kbdchar.3 menuhit.3 muldiv.3 norm.3 outline.3 parms.3 pfkey.3 point.3 \
	polygon.3 psendchar.3 ptarith.3 ptinrect.3 qsort.3 rand.3 rcvchar.3 \
	realtime.3 rectarith.3 rectclip.3 rectf.3 rectxrect.3 resources.3 \
	ringbell.3 rol.3 screenswap.3 segment.3 sendchar.3 sleep.3 sqrt.3 \
	state.3 string.3 stringc.3 strlen.3 structures.3 strwidth.3 \
	texture.3 texture16.3 transform.3 trig.3 version.3 xtproto.3

all:

clean:

install: all
	-mkdir $(MDIR)
	cp $(SRCS) $(MDIR)
	chmod $(MODE664) $(MDIR)/*
