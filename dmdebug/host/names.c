/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)names.c	2.2);
*/

#include "names.h"

char * dottynames[] = {
	"<error>",
	"byte",
	"short",
	"long",
	"instr",
	"struct",
	"enum",
	"string"
};

char * basetypenames[] = {
	"undef",
	"farg",
	"char",
	"short",
	"int",
	"long",
	"float",
	"double",
	"struct",
	"union",
	"enum",
	"moe",
	"uchar",
	"ushort",
	"unsigned",
	"ulong",
	"void",
	0
};

char * storagenames[] = {
	"err",
	"glb",
	"sta",
	"com",
	"reg",
	"lcl",
	"arg",
	0
};

char * regnames[] = {
	"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8",
	"fp", "ap", "spu", "spl", "sp", "pc", "psw", 0
};

char * ntypenames[] = {
	"UNDF",
	"EUNDF",
	"ABS",
	"EABS",
	"TEXT",
	"ETEXT",
	"DATA",
	"EDATA",
	"BSS",
	"EBSS",
	"CTXT",
	"ECTXT",
	"RDAT",
	"ERDAT",
	"COMM",
	"ECOMM",
	0
};
	
char *sdbnames[] = {
	"0",
	"GSYM",
	"STSYM",
	"LCSYM",
	"RSYM",
	"LSYM",
	"PSYM",
	"BSTR",
	"ESTR",
	"SSYM",
	"BENUM",
	"EENUM",
	"ENUM",
	"BCOMM",
	"ECOMM",
	"ECOML",
	"LBRAC",
	"RBRAC",
	"BFUN",
	"ENTRY",
	"SLINE",
	"SO",
	"SOL",
	"FNAME",
	"LENG",
	"EFUN",
	"DLINE",
	"0x1b",
	"0x1c",
	"0x1d",
	"0x1e",
	"0x1f",
	"NARGS",
	"TYID",
	"DIM",
	0
};

char *ntrapnames[] = {
	"Integer zero divide",
	"Trace trap",
	"Illegal opcode",
	"Reserved opcode",
	"Invalid descriptor",
	"External memory fault",
	"Gate vector fault",
	"Illegal level change",
	"Reserved data type",
	"Integer overflow",
	"Privileged opcode",
	"Invalid trap type",
	"Invalid trap type",
	"Invalid trap type",
	"Breakpoint trap",
	"Privileged register",
};

char *strapnames[] = {
	"Stack bound",
	"Stack fault",
	"Invalid trap type",
	"Interrupt ID fetch",
};

char *ptrapnames[] = {
	"Old PCB fault",
	"Gate PCB fault",
	"Invalid trap type",
	"Invalid trap type",
	"New PCB fault"
};

char *rtrapnames[] = {
	"Old PCB fault",
	"System data",
	"Interrupt stack fault",
	"External reset",
	"New PCB fault",
	"Invalid trap type",
	"Gate vector fault"
};

struct	traptypes trapnames[4] = {
	{ rtrapnames, 7 },
	{ ptrapnames, 5 },
	{ strapnames, 4 },
	{ ntrapnames, 16}
};

char *hatebsnames[] = {
	"<internal error>",
	"halted at ",
	"running",
	"halted by ",
	"inconsistent state",
	"break at ",
	"stepped at"
};

nameindex( l, id )		/* assumes you don't search for [0] */
char *l[], *id;
{	int i;

	for( i = 1; l[i]; ++i ) if( !strcmp( l[i], id ) ) return i;
	return 0;
}
