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
#! /bin/sh
#	@(#)dmdp.sh	2.3

if [ ! "$1" ]
then
	echo Printer type not specified
	exit
fi

DOWNLOAD=${DMD=DmD}/lib/dmdp.m

case $1 in
transparent)
	${DMD=DmD}/bin/32ld $DOWNLOAD 0
	;;
5310)
	${DMD=DmD}/bin/32ld $DOWNLOAD 1 \
		" 75 Horizontal DPI...(S)" \
		">150 Horizontal DPI..(S)" \
		" 72 Vertical DPI.....(S)" \
		">144 Vertical DPI....(S)" \
		">Draft Quality.......(H)" \
		" Final Quality.......(H)"
	;;
5320)
	${DMD=DmD}/bin/32ld $DOWNLOAD 1 \
		" 75 Horizontal DPI...(S)" \
		">150 Horizontal DPI..(S)" \
		" 72 Vertical DPI.....(S)" \
		">144 Vertical DPI....(S)" \
		">Draft Quality.......(H)" \
		" Final Quality.......(H)" \
		">Narrow Paper.......(SH)" \
		" Wide Paper.........(SH)"
	;;
8510b)
	${DMD=DmD}/bin/32ld $DOWNLOAD 2 \
		">80 Horizontal DPI...(S)" \
		" 96 Horizontal DPI...(S)" \
		" 136 Horizontal DPI..(S)" \
		">72 Vertical DPI.....(S)" \
		">Draft Quality......(SH)" \
		" Final Quality......(SH)"
	;;
thinkjet)
	${DMD=DmD}/bin/32ld $DOWNLOAD 3 \
		">96 Horizontal DPI...(S)" \
		" 192 Horizontal DPI..(S)" \
		">96 Vertical DPI.....(S)" \
		">Draft Quality.......(H)" \
		" Final Quality.......(H)"
	;;
*)
	echo Printer type $1 not supported
	;;
esac
