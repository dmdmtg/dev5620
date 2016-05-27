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

#include <jerq.h>
#include <jerqio.h>
#include <font.h>


char FNAME[50];

getstr(s,p)
char *s;
Point p;
{
   char c,*t;
   static char str[]="x";
   t = s;
   for (;;) {
     wait(KBD);
     if (((c=kbdchar()) == '\r') || (c == '\n')) {
       *s = '\0';
       return;
     }
     if (c == '\b') {
       if (s>t) {
         str[0] = *(--s);
         string(&defont,str,&display,(p = sub(p,Pt(9,0))),F_XOR);
       }
     } else {
       if (s-t<50) {
         *s++ = (str[0] = c);
         p = string(&defont,str,&display,p,F_XOR);
       }
     }
   }
}

GetFNAME()
{
   Point p;
   p = string(&defont,"Texture16: ",&display,add(Drect.origin,Pt(15,5)),F_XOR);
   getstr(FNAME,p);
   p = string(&defont,"Texture16: ",&display,add(Drect.origin,Pt(15,5)),F_XOR);
   string(&defont,FNAME,&display,p,F_XOR);
}

int hex(ch)
{
   if ((ch>='0') && (ch<='9')) return(ch-'0');
   return(10+ch-'A');
}

int scanhex(fp)
FILE *fp;
{
   int ch;
   while((ch=getc(fp)) != '0');
   getc(fp); /* 'x' */
   return(4096*hex(getc(fp))+256*hex(getc(fp))+16*hex(getc(fp))+hex(getc(fp)));
}

OpLoad(tex,filename)
Texture16 *tex;
char *filename;
{
   FILE *fp;
   int ch,i,j;
   fp = fopen(filename,"r");
   if (fp == ((FILE *) 0)) return(0);
   ch = getc(fp);
   while ((ch!='{')&&(ch!=EOF)) ch=getc(fp);
   for (i=0; i<16; i++) {tex->bits[i] = scanhex(fp); getc(fp);}
   fclose(fp);
}

OpRead(tex)
Texture16 *tex;
{
   GetFNAME();
   if (!FNAME[0]) return(0);
   OpLoad(tex,FNAME);
}

main()
{
   Texture16 t;
   request(KBD|MOUSE);
   while (!bttn123()) {
     OpRead(&t);
     rectf(&display,Drect,F_CLR);
     texture16(&display,Rpt(Pt(Drect.origin.x,Drect.origin.y+32),Drect.corner),
             &t,F_XOR);
   }
   exit();
}
