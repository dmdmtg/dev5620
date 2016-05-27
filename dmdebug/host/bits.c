/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
VERSION(@(#)bits.c	2.3);
*/

#include	"dis.h"

#define		OPLEN	35	/* maximum length of a single operand	*/
static	char	operand[4][OPLEN];
#define	NOTFLOAT	0
#define	FPSINGLE	1
#define	FPDOUBLE	2
static	int	fpflag;		/* floating point instruction */
long	get_operand();
long	get_bjmp_oprnd();
long	get_hjmp_oprnd();
long	get_macro();
unsigned short gethalf();
char 	*strcpy();

long
disassemble(loc, addr, result)
char *result;
long loc, addr;
{
	extern struct instable opcodetbl[];
	extern struct formtable adrmodtbl[];
	long  getword();
	struct instable *cp;
	register i;
	static char *format[] = {
		"%s",
		"%s	%s",
		"%s	%s,%s",
		"%s	%s,%s,%s",
		"%s	%s,%s,%s,%s"
	};

	for (i=0; i<4; i++)
		operand[i][0] = '\0';
	fpflag = NOTFLOAT; 
	i = get1byte(loc++);
	cp = &opcodetbl[i];
	switch (cp->class) {

	/* ignore 8 bits of insignificant data   	 */
	case NOOP8:
		get1byte(loc++);
		break;

	/* ignore 16 bits of insignificant data   */
	case NOOP16:
		gethalf(loc);
		loc += 2;
		break;

	/* m32a simulator i/o EXTOPs. */
	case EXT:
		sprintf(operand[0], "%#x",  get1byte(loc));
		loc++;
		break;

	/* instructions with no operands */
	case OPRNDS0:
		break;

	/* instructions with 1 operand */
	case OPRNDS1:
	case JUMP:
		loc = get_operand(loc, operand[0]);
		break;

	/* instructions with 2 operands */
	case SFPOPS2:
		fpflag = FPSINGLE;
		goto o2;
	case DFPOPS2:
		fpflag = FPDOUBLE;
	case OPRNDS2:
	o2:
		loc = get_operand(loc, operand[0]);
		loc = get_operand(loc, operand[1]);
		break;

	/* instructions with 3 operands */
	case SFPOPS3:
		fpflag = FPSINGLE;
		goto o3;
	case DFPOPS3:
		fpflag = FPDOUBLE;
	case OPRNDS3:
	o3:
		loc = get_operand(loc, operand[0]);
		loc = get_operand(loc, operand[1]);
		loc = get_operand(loc, operand[2]);
		break;

	/* instructions with 4 operands */
	case OPRNDS4:
		loc = get_operand(loc, operand[0]);
		loc = get_operand(loc, operand[1]);
		loc = get_operand(loc, operand[2]);
		loc = get_operand(loc, operand[3]);
		break;
 
	/* jump instructions with a one byte offset */
	case JUMP1:
		loc = get_bjmp_oprnd(loc, addr, operand[0]);
		break;

	/* jump instructions with a two byte offset */
	case JUMP2:
		loc = get_hjmp_oprnd(loc, addr, operand[0]);
		break;

	/* Support Processor Instruction  "SPOP";  Opcode is  */
	/* followed by 32 bit "id" similar to an immediate word */
	/* but has no byte descriptor.   	 */
	case SPRTOP0:
		sprintf(operand[0], "&%#lx", getword(loc));
		loc += 4;
		break;

	/* Support Processor Instructions "SPOPRS", "SPOPRD",   */
	/* "SPOPRT", "SPOPWS", "SPOPWD", and "SPOPWT".  The */
	/* opcode is followed by a 32 bit support processor "id"*/
	/* similar to an immediate word but with no byte  */
	/* descriptor. Following the "id" is one normal operand */
	/* with a byte descriptor.   	 */
	case SPRTOP1:
		sprintf(operand[0], "&%#lx", getword(loc));
		loc += 4;
		loc = get_operand(loc, operand[1]);
		break;

	/* Support Processor Instructions "SPOPS2", "SPOPD2",   */
	/* "SPOPT2".  These are three operand instructions.  The */
	/* opcode is followed by a 32 bit support processor "id"*/
	/* similar to an immediate word with no byte  */
	/* descriptor. Following the "id" are 2 normal operands */
	case SPRTOP2:
		sprintf(operand[0], "&%#lx", getword(loc));
		loc += 4;
		loc = get_operand(loc, operand[1]);
		loc = get_operand(loc, operand[2]);
		break;

	/* an invalid op code (there aren't too many) */
	case UNKNOWN:
		break;

	/* This special case handles the macro rom instructions */
	case MACRO:
		loc = get_macro(loc, operand[0]);
		break;

	default:
		printf("case from instruction table not found\n");
/*		exit(4);  */
		return( 0 );
	} /* end switch */
	for (i=0; i<4; i++)
		if (*operand[i]=='\0')
			break;
	sprintf(result, format[i], cp->name, operand[0], operand[1],
	   operand[2], operand[3]);
	return(loc);
}
/*
 * Determine the type of address mode for this operand and
 * place the resultant operand text to be printed in the array
 * whose address was passed to this function
 */

long
get_operand(loc, result)
long loc;
char *result;
{
	extern struct formtable adrmodtbl[]; /* from tables.c */
	struct formtable  *tp;
	long t;
	int i;

	i = get1byte(loc++);
	tp = &adrmodtbl[i];
	switch (tp->typ) {

	/* type = immediate numbers 0 to 63 (IM6)  */
	/* type = immediate numbers -16 to -1 (IM4)  */
	/* type = register (R) and register deferred (RDF) */
	/* type = register and displacement of 0 to 14 (R4) */
	case IM4:
	case IM6:
	case R:
	case RDF:
	case R4:
		sprintf(result, "%s", tp->name);
		return(loc);

	/* type = immediate operand in following byte (IMB) */
	case IMB:
		sprintf(result, "&%#x", get1byte(loc));
		return(++loc);

	/* type = register + byte displacement (BDB)  */
	case BDB:
		sprintf(result, "%#x%s", get1byte(loc), tp->name);
		return(++loc);

	/* type = register + byte displacement deferred (BDBDF) */
	case BDBDF:
		sprintf(result, "*%#x%s", get1byte(loc), tp->name);
		return(++loc);

	/* type = immediate operand in following half word (IMH) */
	case IMH:
		sprintf(result,"&%#x", gethalf(loc));
		return(loc+=2);

	/* type = register + half word displacement (BDH)  */
	case BDH:
		sprintf(result, "%#x%s", gethalf(loc), tp->name);
		return(loc+=2);

	/* type = register + half word displacement deferred (BDHDF) */
	case BDHDF:
		sprintf(result, "*%#x%s", gethalf(loc), tp->name);
		return(loc+=2);

	/* type = immediate operand in following word (IMW)  */
	/* type = immediate operand in following doubleword (IMD) */
	case IMD:
		if (fpflag == NOTFLOAT) {
			/* code from case BDB */
			sprintf(result, "%#x%s", get1byte(loc), tp->name);
			return(++loc);
			}
	case IMW:
		t = getword(loc);
		loc += 4;
		switch (fpflag) {

		case NOTFLOAT:
		case FPSINGLE:
			sprintf(result, "&%#lx", t);
			return(loc);;

		case FPDOUBLE:
			sprintf(result, "&%#lx:%#lx", t, getword(loc));
			return(loc += 4);
		}
		return(loc);

	/* type = register + word displacement (BDW)  */
	/* type = absolute address (ABAD)   */
	case BDW:
	case ABAD:
		sprintf(result, "%#lx%s", getword(loc), tp->name);
		return(loc += 4);

	/* type = register + word displacement deferred (BDWDF) */
	/* type = absolute address deferred (ABADDF)  */
	case BDWDF:
	case ABADDF:
		sprintf(result, "*%#lx%s", getword(loc), tp->name);
		return(loc += 4);

	/* type = expanded operand   */
	/* Data from the address modes table indicates */
	/* {Signed/Unsigned BYTE/HALFword/WORD}  */
	/* followed by the operand.   */
	case EXPSB:
	case EXPUB:
	case EXPSH:
	case EXPUH:
	case EXPSW:
	case EXPUW:
		sprintf(result,"%s", tp->name);
		return(get_operand(loc, result+strlen(result)));

	default:
		printf("\ndis: invalid general addressing mode (%x)\n", i);
/*		exit(1);  */
	} /* end switch */
	return(loc);
}

/*
 * byte jump operand
 */
long
get_bjmp_oprnd(loc, addr, result)
long loc, addr;
char *result;
{
	long t;

	t = get1byte(loc);
	if (t & 0x80) {
		t = (-t) &0xFF;
		sprintf(result, "-%#lx <%lx>", t, addr-t);
	} else {
		sprintf(result, "%#lx <%lx>", t, addr+t);
	}
	return(loc += 1);
}

/*
 * halfword jump operand
 */

long
get_hjmp_oprnd(loc, addr, result)
long loc, addr;
char *result;
{
	long t;

	t = gethalf(loc);
	if (t & 0x8000) {
		t = (-t) & 0xFFFF;
		sprintf(result, "-%#lx  <%lx>", t, addr-t);
	} else {
		sprintf(result, "%#lx  <%lx>", t, addr+t);
	}
	return(loc += 2);
}


/*
 * Get the next byte and use that as the index of the
 * macro rom instruction.
 */

long
get_macro(loc, result)
char *result;
long loc;
{
	static struct romlist {
		short romcode;
		char *romstring;
	} romlist[] = {
		0x9,"MVERNO",
		0xd,"ENBVJMP",
		0x13,"DISVJMP",
		0x19,"MOVBLW",
		0x1f,"STREND",
		0x2f,"INTACK",
		0x35,"STRCPY",
		0x3c,"SLFTST",
		0x45,"RETG",
		0x61,"GATE",
		0xac,"CALLPS",
		0xc8,"RETPS",
		0,""
	};
	register struct romlist *rpt;
	register t;

	t = get1byte(loc);
	loc++;
	for( rpt = romlist; rpt->romcode != 0; rpt++) {
		if (t == rpt->romcode) {
			strcpy(result, rpt->romstring);
			return(loc);
		}
	}
	sprintf(result,"MACRO %#x", t);
	return(loc);
}

unsigned short
gethalf(loc)
long loc;
{
	register unsigned short t;

	t = get1byte(loc);
	t |= get1byte(loc+1)<<8;
	return(t);
}

long getword(loc)
long loc;
{
	register long t;

	t = get1byte(loc);
	t |= get1byte(loc+1)<<8;
	t |= get1byte(loc+2)<<16;
	t |= get1byte(loc+3)<<24;
	return(t);
}


