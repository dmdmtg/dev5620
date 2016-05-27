/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
HVERSION(protocol,@(#)protocol.h	2.5);
*/

#define ESCAPE		033
#define STATELINE	007

#define PEEK_LONG	'L'
#define PEEK_SHORT	'W'
#define PEEK_BYTE	'B'
#define PEEK_STR	'S'
#define PEEK_SAVE	'X'
#define PEEK_PCBREG	'Y'
#define PEEK_PCAPFP	'Z'

#define BADTRACE	'B'

#define	INDEX_BASE	0L
#define PROC_INDEX	(1+INDEX_BASE)
#define HATEBS_INDEX	(2+INDEX_BASE)
#define TYPE_INDEX	(3+INDEX_BASE)
#define TLOC_INDEX	(4+INDEX_BASE)
#define ARGV_INDEX	(5+INDEX_BASE)
#define LAST_INDEX	(5+INDEX_BASE)

#define POKE_LONG	'l'
#define POKE_SHORT	'w'
#define POKE_BYTE	'b'

#define DO_BPTS 	's'
#define DO_BPTC		'c'

#define DO_WRAP		004
#define DO_DEBUG	'N'
#define DO_VIDEO	'V'
#define DO_ACT		'R'
#define DO_HALT		'H'
#define DO_SING		'1'
#define DO_KBD		'K'
#define DO_ANTIC	'A'
#define DO_STACK	'p'
#define DO_FUNC		'f'
#define DO_DELTAS	'd'
#define DO_ENABLE	'E'
#define DO_DISABLE	'D'
#define DO_EVENT	'e'
#define DO_INVOKE	'I'
#define DO_LIMIT	'g'


#define LO_ROM  0
#define HI_ROM	0x03ffff
#define LO_DUAR	0x200003
#define HI_DUAR	0x20003f
#define LO_PIO	0x300003
#define HI_PIO	0x30007f
#define LO_MOUS	0x400000
#define HI_MOUS 0x400003
#define LO_DISP 0x500000
#define HI_DISP 0x500001
#define LO_BRAM 0x600002
#define HI_BRAM	0x601ffe
#define LO_ADDR 0x700000
#define HI_ADDR 0x7fffff


#define M_MENU		'm'
#define M_ITEM		'i'
#define M_HIT		'h'
#define M_NULL		'z'
#define M_BUTT		'n'
#define M_CONFIRM	'C'
#define M_PENDULUM	'P'
#define M_LIMITS	'#'
#define	M_BITVEC	'|'
#define M_SUGGEST	'@'

#define G_BITMAP	':'
#define G_RECTANGLE	']'
#define G_TEXTURE	'_'
#define G_16TEXTURE	'-'
#define G_POINT		'.'


#define I_DATA		1
#define I_ADDR		2
#define I_STRUCT   	3



