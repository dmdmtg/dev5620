/* */
/*									*/
/*	Copyright (c) 1987,1988,1989,1990,1991,1992   AT&T		*/
/*			All Rights Reserved				*/
/*									*/
/*	  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T.		*/
/*	    The copyright notice above does not evidence any		*/
/*	   actual or intended publication of such source code.		*/
/*									*/
/* */
static char ID[] = "@(#) dump.c: 1.3 2/27/84";
#include "system.h"

#if DEBUG
#include <stdio.h>
#include "structs.h"
#include "extrns.h"
/*eject*/
dmpacts()
{
	register ACTITEM *p;
	register REGION *r;
	register MEMTYPE *m;

	if( (m = (MEMTYPE *) memlist.head) )
		fprintf(stderr, "\n\nMEMLIST\n\n");
	while (m) {
		fprintf(stderr, "name=%-8.8s  orig=%08.2lx  len=%08.2lx  attr=%04.2x\n",
			m->mtname, m->mtorig, m->mtlength, m->mtattr);
		m = m->mtnext;
		}
	if( (r = (REGION *) reglist.head) )
		fprintf(stderr, "\n\nREGLIST\n\n");
	while (r) {
		fprintf(stderr, "name=%-8.8s  orig=%08.2lx  len=%08.2lx  vaddr=%08.2lx\n",
			r->rgname, r->rgorig, r->rglength, r->rgvaddr);
		r = r->rgnext;
		}

	if( (p = (ACTITEM *) ldfilist.head) )
		fprintf(stderr, "\n\nLDFILLIST\n\n");
	while (p) {
		fprintf(stderr, "load file %s\n", p->ldlbry.aifilnam);
		p=p->ldlbry.ainext;
		}

	if( (p = (ACTITEM *) bldoutsc.head) )
		fprintf(stderr, "\n\nBLDOUTSC\n\n");
	while (p) {
		dmpsecspc(p);
		p = p->dfnscn.ainext;
		}

}
/*eject*/
dmpsecspc(p)
ACTITEM *p;
{
	register ACTITEM *q;

	if (p->dfnscn.aitype == AIDFNGRP)
		fprintf(stderr, "GROUP:  owner=(%.8s)  block=%06.2lx\n",
			p->dfnscn.aiowname, p->dfnscn.aiblock);
	else
		fprintf(stderr, "section %.8s:  fill=%06.2x  owner=(%.8s)  block=%06.2lx  attown=%06.2x\n",
			p->dfnscn.ainame,p->dfnscn.aifill,p->dfnscn.aiowname,
			p->dfnscn.aiblock, p->dfnscn.aiattown);

	q = (ACTITEM *) p->dfnscn.sectspec.head;
	while (q) {
		if (q->dfnscn.aitype == AIDFNSCN)
			dmpsecspc(q);
		else if (q->dfnscn.aitype == AIADFILE) {
			fprintf(stderr, "\tadd file %s\n", q->adfile.aifilnam);
			}
		else if (q->dfnscn.aitype == AIADDSCN)
			fprintf(stderr, "\tadd %s(%.8s)  fill=%06.2x\n",
			     q->addscn.aiscfile, q->addscn.ainame, q->addscn.aifill);
		q = q->dfnscn.ainext;
		}
}
/*eject*/
dump_mem()
{

/*
 * List the configured memory, available memory, and the
 * regions and the pointers between them.
 * Strictly for debugging purposes.
 */

	register MEMTYPE *mp;
	register REGION *rp;
	register ANODE *ap;

	fprintf(stderr, "\n\n\tCONFIGURED MEMORY\n");
	fprintf(stderr, "addr\torigin\tlength\thead\ttail\tattr\tname\n");
	for( mp = (MEMTYPE *) memlist.head; mp; mp = mp->mtnext )
		fprintf(stderr, "%4x\t%6lx\t%6lx\t%4x\t%4x\t%x\t%.8s\n",
			mp,mp->mtorig,mp->mtlength,
			mp->mtaddrhd,mp->mtaddrtl,
			mp->mtattr,mp->mtname);

	fprintf(stderr, "\n\tREGIONS\n");
	fprintf(stderr, "addr\torigin\tlength\thead\ttail\tname\n");
	for( rp = (REGION *) reglist.head; rp; rp = rp->rgnext )
		fprintf(stderr, "%4x\t%6lx\t%6lx\t%4x\t%4x\t%.8s\n",
			rp,rp->rgorig,rp->rglength,rp->rgaddrhd,
			rp->rgaddrtl,rp->rgname);

	fprintf(stderr, "\n\tAVAIL NODES\n");
	fprintf(stderr, "addr\tprev\tnext\taddr\tsize\ttype\tmemp\tregp\toutsect\n");
	for( ap = (ANODE *) avlist.head; ap; ap = ap->adnext ) {
		fprintf(stderr, "%4x\t%4x\t%4x\t%6lx\t%6lx\t%4x\t%4x\t%4x",
			ap,ap->adprev, ap->adnext, ap->adpaddr,ap->adsize,
			ap->adtype,ap->admemp,ap->adregp);
		if(ap->adtype != ADAVAIL)
			fprintf(stderr, "\t%.8s",ap->adscnptr->oshdr.s_name);
		fprintf(stderr, "\n");
		}

	fflush(stderr);
}
/*eject*/
dmp_own(aip)
ACTITEM *aip;
{
	fprintf(stderr, "\nOwner:  %.8s\nOutsec:  %.8s, size %x, vaddr %x, paddr %lx\n",
	aip->dfownr.ainamown,aip->dfownr.aioutsec->oshdr.s_name,aip->dfownr.aioutsec->oshdr.s_size,
	aip->dfownr.aioutsec->oshdr.s_vaddr,aip->dfownr.aioutsec->oshdr.s_paddr);

	fflush(stderr);
}





dmp_att(aip)
ACTITEM *aip;
{
	fprintf(stderr, "Attown:  %x\nOutsec:  %.8s, size %x\n",
	aip->ownatr.aiownatt,aip->ownatr.aioutsec->oshdr.s_name,
	aip->ownatr.aioutsec->oshdr.s_size);

	fflush(stderr);
}
/*eject*/
dmp_outsects()
{
	register OUTSECT *p, *q;

	for( p = (OUTSECT *) outsclst.head; p; p = p->osnext ) {
		if (p->oshdr.s_flags & STYP_GROUP) {
			fprintf(stderr, "GROUP: size %lx, paddr %lx, vaddr %lx\n",
				p->oshdr.s_size, p->oshdr.s_paddr, 
				p->oshdr.s_vaddr);
			for( q = (OUTSECT *) p->osinclhd; q; q = q->osnext ) {
				fprintf(stderr, "  %.8s: size %lx, paddr %lx, vaddr %lx\n",
					q->oshdr.s_name, q->oshdr.s_size,  
					q->oshdr.s_paddr, q->oshdr.s_vaddr);
				}
			}
		else
			fprintf(stderr, "%.8s: size %lx, paddr %lx, vaddr %lx\n",
				p->oshdr.s_name, p->oshdr.s_size,  
				p->oshdr.s_paddr, p->oshdr.s_vaddr);
		}
}
#endif
