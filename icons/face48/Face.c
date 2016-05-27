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
#include <sgtty.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#define ICONSIZE 48
#define ICONBYTES (ICONSIZE*(ICONSIZE/8))
#define ICONWORDS (ICONSIZE*(ICONSIZE/16))
#define ICONPATH "/usr/dmd/icon/face48/"
#define	ICONLEN	strlen(ICONPATH)
char iconfile[100]=ICONPATH;

main(argc, argv)
	char *argv[];
{
	register i;
	struct sgttyb modes;
	if(argc==1){
		fprintf(stderr, "usage: face moniker ...\n");
		return 1;
	}
	if(system("32ld Catalog.m")){
		fprintf(stderr, "face: 32ld errors\n");
		return 1;
	}
	ioctl(1, TIOCGETP, &modes);
	modes.sg_flags|=RAW;
	ioctl(1, TIOCSETP, &modes);
	for(i=1; i<argc; i++){
		char *strrchr(), *p=strrchr(argv[i], '/');
		if(p)
			p++;	/* skip / */
		else
			p=argv[i];
		if(p[0]!='.'){
			write(1, p, strlen(p)+1);
			sendicon(argv[i]);
		}
	}
	getchar();
	modes.sg_flags&=~RAW;
	ioctl(1, TIOCSETP, &modes);
}

HexToDec(Hex)
int Hex;
{
	if ((Hex>='0') && (Hex<='9')) return(Hex-'0');
	if ((Hex>='A') && (Hex<='F')) return(10+Hex-'A');
	if ((Hex>='a') && (Hex<='f')) return(10+Hex-'a');
	return(-1);
}
sendicon(p)
	char *p;
{
	FILE *icon;
	struct stat statbuf;
	char buf[6], IconBuf[ICONBYTES];
	char *ip;
	int i,val;

	if(p[0]=='/')
		ip=p;
	else{
		strncpy(iconfile+ICONLEN, p, 100-ICONLEN);
		ip=iconfile;
	}
	if (stat(ip, &statbuf)<0){
		strncpy(iconfile+ICONLEN, "unknown", 100-ICONLEN);
		ip=iconfile;
	}
	if ((icon = fopen(ip, "r")) != NULL)
		for (i=0; i<ICONBYTES; i+=2) {
			do; while (getc(icon)!='x');
			val = HexToDec(getc(icon))<<4; val |= HexToDec(getc(icon));
			IconBuf[i]=val;
			val = HexToDec(getc(icon))<<4; val |= HexToDec(getc(icon));
			IconBuf[i+1]=val;
		}
	fclose(icon);
	write(1, IconBuf, ICONBYTES);
}
