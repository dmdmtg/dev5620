/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sccsid.h>
VERSION(@(#)cc.c	2.6);

#define	PARGS	if(debug){printf("%s: ",CC);for(j=0;j<na;j++)printf(" %s",av[j]);printf("\n");}

/*===================================================================*/
/*                                                                   */
/*                 DMDCC Command                                     */
/*	NOTE: this is the dmd version of the cc command		     */
/*                                                                   */
/*                                                                   */
/*-------------------------------------------------------------------*/
/*                                                                   */
/*     The cc command parses the command line to set up command      */
/*     lines for and exec whatever processes (preprocessor,          */
/*     compiler, optimizer, assembler, link editor) are required.    */
/*                                                                   */
/*===================================================================*/

#ifdef sun
#ifndef bsd
#define bsd
#endif
#endif

#ifdef bsd
#define fork vfork
#endif

#include	<stdio.h>
#include	<signal.h>
#include	<sgs.h>
#include	<paths.h>
#include <sys/wait.h>


#define LAYERCRT0	"/lib/crtm.o"
#define JXCRT0		"/lib/l.o"
#define FULL	1
#define REL	0

/* performance statistics */

#ifdef PERF

#define	STATS( s )	if (stat == 1) {			\
				stats[ii].module = s;		\
				stats[ii].ttim = ttime;		\
				stats[ii++].perform = ptimes;	\
				if (ii > 25)			\
					pexit();		\
			}

FILE	*perfile;
long	ttime;
struct	tbuffer {
	long	proc_user_time;
	long	proc_system_time;
	long	child_user_time;
	long	child_system_time;
	} ptimes;
extern	long	times();
struct	perfstat {
	char	*module;
	long	ttim;
	struct	tbuffer	perform;
	} stats[30];
int	ii = 0;
int	stat = 0;

#endif
extern char *strcat(), *strcpy();


/* CC command version */

#ifdef	N3B
#define	CC	"n3bcc"
#endif

#ifdef	U3B
#define	CC	"u3bcc"
#endif

#ifdef	M32
#define	CC	"m32cc"
#undef A_OUT
#define A_OUT	"dmda.out"
#endif

#ifdef	b16
#define	CC	"b16cc"
#endif


/* C command */

#ifdef N3B
#define	SGSF	"/n3B"
#endif

#ifdef U3B
#define	SGSF	"/u3b"
#endif

#ifdef M32
#define	SGSF	"/m32"
#endif

#ifdef b16
#define	SGSF	"/b16"
#endif


/* tool names */

#define	N_CP	"cpp"

#ifdef ONEPASS
#define	N_C0	"comp"
#else
#define	N_C0	"front"
#define	N_C1	"back"
#endif

#define	N_C2	"optim"

#ifdef N3B
#define	N_AS	"n3bas"
#define	N_LD	"n3bldp"
#endif

#ifdef U3B
#define	N_AS	"as"
#define	N_LD	"ld"
#endif

#ifdef M32
#define	N_AS	"as"
#define	N_LD	"ld"
#endif

#ifdef b16
#define	N_AS	"b16as"
#define	N_LD	"b16ld"
#endif


/* number of args always passed to ld; used to determine whether
 * or not to run ld when no files are given */

#ifdef	N3B
#define	MINLDARGS	2
#endif

#ifdef	U3B
#define	MINLDARGS	3
#endif

#ifdef	M32
#define	MINLDARGS	4
#endif

#ifdef	b16
#define	MINLDARGS	2
#endif


/* tool indexes */

#define	Xcp	0
#define	Xc0	1
#define	Xc1	2
#define	Xc2	3
#define	Xas	4
#define	Xld	5


/* option string for getopt() */

#ifdef N3B
#define OPTSTR	"cpOSW:t:EPB:go:D:I:U:C1:2:d:VQR:l:rsu:xmniL:N#"
#endif

#ifdef U3B
#define	OPTSTR	"cpfOSW:t:EPB:go:D:I:U:C1:2:d:VQR:l:rsu:xmniL:N#"
#endif
#ifdef M32
#define	OPTSTR	"cpfOSW:t:EPB:go:D:I:U:C1:2:d:VQv:R:l:rsu:xmniL:N#J"
#endif

#ifdef b16
#define	OPTSTR	"cpOSW:t:EPB:gGo:D:I:U:1:2:d:VQl:rsu:xmniL:N#"
#endif


#define	NPASS	6


/* file names */

char	*cpp_out,	/* output of preprocessor */
	*c_in,		/* compiler input */
	*c_out,		/* compiler output */
	*as_in,		/* assembler input */
	*as_out,	/* assembler output */
	*ld_out = NULL,	/* link editor output (object file) */
	*tmp1 = NULL,	/* temporaries */
	*tmp2 = NULL,
	*tmp3 = NULL,
	*tmp4 = NULL;


/* default path names */

char	*passcp = CPP,
#ifdef ONEPASS
	*passc0 = COMP,
#else
	*passc0 = C0,
	*passc1 = C1,
#endif
	*passc2 = OPTIM,
	*passas = AS,
#if N3B
	*passld = LDP;
#else
	*passld = LD;
#endif


/* flags: ?flag corresponds to ? option */

int	cflag	= 0,	/* compile and assemble only to .o; no load */
	Oflag	= 0,	/* optimizer request */
#if N3B
	OAflag	= 0,	/* use optimizer unconditionally */
#endif
	Sflag	= 0,	/* leave assembly output in .s file */
	dflag	= 0,	/* dump compiler and assembler input (debug) */
	Eflag	= 0,	/* preprocess only, output to stdout */
	Pflag	= 0,	/* preprocess only, output to file.i */
	eflag	= 0,	/* error count */
	debug	= 0,	/* cc command debug flag (prints command lines) */
#if U3B || M32
	dsflag	= 1,	/* turn off symbol attribute output in compiler */
	dlflag	= 1,	/* turn of line number output in compiler */
	jxflag  = 0,	/* true if compiling a standalone program */
	mpxflag = 1,	/* true if compiling for layers (default) */
#else
	dsflag	= 0,
	dlflag	= 0,
#endif
#if U3B || M32 || b16
	pflag	= 0,	/* profile request */
#endif
#if U3B || M32
	gflag	= 0,	/* include libg.a on load line */
	fflag	= 0,	/* floating point interpreter	*/
#endif
#ifdef TV
	tvflag	= 0,	/* transfer vector addressing */
#endif
	Fdebug	= 0,	/* compiler (front) debug flags present */
	Bdebug	= 0;	/* compiler (back) debug flags present */


/* lists */

char	**av,		/* args to execvp */
	**clist,	/* names of files to be compiled or assembled */
	**list[NPASS];	/* option list for each pass (cpp, comp, ... , ld) */
int	nlist[NPASS],	/* option count for each pass */
	nc	= 0,	/* current number of names in clist */
	nxo	= 0;	/* number of .o files in list[Xld] */


#if N3B || U3B || M32
char	*crt;		/* name of run-time startoff */
#ifdef TV
char	*tvcrt	= TVCRT0;	/* name of run-time startoff */
#endif
#endif

#if M32
char	dmddir[256],	/* pathnames (to be determined) for various files */
	crtdir[128],
	incdir[128],
	libdir[128],
	mapdir[128];

char	gpath[256];	/* path name to libg.a */
#endif M32

/* interface for getopt() */

extern	int	optind,		/* arg list index */
		optopt;		/* current option char */
extern	char	*optarg;	/* current option argument */


/* functions */

char	getsuf(),
	*setsuf(),
	*stralloc(),
	*strtok(),
	*strcpy(),
	*copy(),
	*mktemp();
int	callsys(),
	dump(),
	nodup(),
	cunlink(),
	idexit(),
	move();

int	sfile;			/* indicates current file in clist is .s */
int	as_escapes;		/* indicates whether the current .c file */
				/* has assembler escapes in it		 */


main (argc, argv)
	int argc;
	char *argv[];
{
	int	c;		/* current option char from getopt() */
	char	*t;		/* char ptr temporary */
	int	i;		/* loop counter, array index */
	char	*chpass = NULL,	/* list of substitute pass names for -B */
		*newpath = NULL;	/* path prefix for substitute passes from -B */
	char	*optstr = OPTSTR;
	int	cur_arg;

#ifdef M32
	getdmd(dmddir);
	strcpy(crtdir,dmddir);
	incdir [0] = '-';
	incdir [1] = 'I';
	strcpy(&(incdir[2]),dmddir);
	strcat(incdir,"/include");
	libdir [0] = '-';
	libdir [1] = 'L';
	strcpy(&(libdir[2]),dmddir);
	strcpy(mapdir,dmddir);
#endif
#ifdef PERF
	if ((perfile = fopen("cc.perf.info", "r")) != NULL) {
		fclose(perfile);
		stat = 1;
	}
#endif

#ifdef N3B
	c = sizeof(char *) * (argc + 20) - 1;	/* dimension arrays */
#else
	c = sizeof(char *) * (argc + 6) - 1;	/* dimension arrays */
#endif
	for (i = 0; i < NPASS; i++) {
		nlist[i] = 0;
		list[i] = (char **) stralloc(c);
	}
	clist = (char **) stralloc(c);
	av = (char **) stralloc(c + 15 * sizeof(char *));

	setbuf(stdout, (char *) NULL);	/* unbuffered output */

	while (optind < argc) {
		cur_arg = optind;
		c = getopt(argc, argv, optstr);
strtcase:	switch (c) {

		case 'c':	/* produce .o files only */
			cflag++;
			break;

		case 'p':	/* profile */
#if U3B || b16
			pflag++;
#if U3B
			crt = MCRT0;
#endif
#else
			fprintf(stderr, "no profile yet: -p ignored\n");
#endif
			break;

#if U3B || M32
		case 'f':	/* floating point interpreter */
			fprintf(stderr, "-f option ignored on DMD\n");
			break;
#endif

		case 'O':	/* invoke optimizer */
#ifndef sparc
#if N3B
			if (strcmp( argv[cur_arg], "-OA" ) == 0) {
				OAflag++;
				Oflag++;
				c = getopt (argc, argv, "A");
			} else
#endif
				Oflag++;
#endif
			break;
#if M32
		case 'J':	/* DMD standalone */
			jxflag++;
			mpxflag = 0;
			crt = strcat(crtdir,JXCRT0);
			break;
#endif

		case 'S':	/* produce assembly code only */
			Sflag++;
			cflag++;
			break;

		case 'W':
			if (optarg[1] != ','
				|| ((t = strtok(optarg, ",")) != optarg)) {
				error("Invalid subargument: -W%s\n", optarg);
				break;
			}
			if ((i = getXpass((c = *t), "-W")) == -1) {
				error("Invalid subargument: -W%s\n", optarg);
				break;
			}
			while ((t = strtok(NULL, ",")) != NULL) {
				if (nlist[i] >= argc+1) {
					error("Too many args for pass -W%c",c);
					break; /* loop */
				}
				list[i][nlist[i]] = stralloc(strlen(t) + 1);
				list[i][nlist[i]][1] = '\0';
				strcat(list[i][nlist[i]++], t);
			}
			break;

		case 't':
			switch (optarg[0]) {
#ifdef TV
			case 'v':	/* transfer vectors */
				tvflag++;
				list[Xc0][nlist[Xc0]++] =
#ifndef ONEPASS
				list[Xc1][nlist[Xc1]++] =
#endif
				list[Xas][nlist[Xas]++] =
				list[Xld][nlist[Xld]++] = "-tv";
				break;
#endif

			case 'd':	/* dump compiler and assembler input */
				dflag++;
				break;

			case 'c':	/* developer's compiler */
				passc0 = optarg + 1;
				break;

			case 'o':	/* developer's optimizer */
				passc2 = optarg + 1;
				break;

			default:
				if (chpass != NULL)
					error("-t overwrites earlier option\n",
						(char *) NULL);
				chpass = optarg;
				if (chpass[0] == 0)
					chpass = "012p";
				break;
			} /* end switch */
			break;

		case 'E':	/* run only cpp, output to stdout */
			Eflag++;
			list[Xcp][nlist[Xcp]++] = "-E";
			cflag++;
			break;

		case 'P':	/* run only cpp, output to file.i */
			Pflag++;
			list[Xcp][nlist[Xcp]++] = "-P";
			cflag++;
			break;

#if U3B || N3B || M32
		case 'C':	/* tell cpp to leave comments in (lint) */
			list[Xcp][nlist[Xcp]++] = "-C";
			break;
#endif

		case 'B':	/* substitute path name */
			if (newpath != NULL)
				error("-B overwrites earlier option",
					(char *) NULL);
			newpath = optarg;
			if (newpath[0] == '\0')
				newpath = "/lib/o";
			break;

		case 'g':	/* turn on symbols and line numbers */
			dsflag = dlflag = 0;
#if U3B || M32
			gflag++;
#endif
			break;

#ifdef b16
		case 'G':	/* for mini-unix convenience */
			list[Xc0][nlist[Xc0]++] = "-G";
			break;
#endif

		case 'o':	/* object file name */
			if (optarg[0]) {
				ld_out = optarg;
				if (((c = getsuf(ld_out)) == 'c') ||
					(c == 'i') || (c == 's') || (c == 'o')){
					error("Illegal suffix: -o %s", ld_out);
					exit(17);
				}
			}
			break;

		case 'D':
		case 'I':
		case 'U':
#if N3B
			if (optarg[0] != '-') {
#endif
				list[Xcp][nlist[Xcp]] = stralloc(strlen(optarg)+2);
				list[Xcp][nlist[Xcp]] [0] = '-';
				list[Xcp][nlist[Xcp]] [1] = c;
				list[Xcp][nlist[Xcp]] [2] = '\0';
				strcat(list[Xcp][nlist[Xcp]++], optarg);
#if N3B
			} else {
				list[Xcp][nlist[Xcp]] = stralloc( 2 );
				list[Xcp][nlist[Xcp]] [0] = '-';
				list[Xcp][nlist[Xcp]] [1] = c;
				list[Xcp][nlist[Xcp]++] [2] = '\0';
				list[Xcp][nlist[Xcp]] = stralloc( strlen(optarg) );
				strcpy( list[Xcp][nlist[Xcp]++], optarg );
			}
#endif
			break;

		case '1':	/* debug flags to front */
			Fdebug++;
			list[Xc0][nlist[Xc0]] = stralloc(strlen(optarg) + 1);
			list[Xc0][nlist[Xc0]] [0] = '-';
			list[Xc0][nlist[Xc0]] [1] = '\0';
			strcat(list[Xc0][nlist[Xc0]++], optarg);
			break;

		case '2':	/* debug flags to back */
			Bdebug++;
#ifdef ONEPASS
			c = Xc0;
#else
			c = Xc1;
#endif
			list[c][nlist[c]] = stralloc(strlen(optarg) + 1);
			list[c][nlist[c]] [0] = '-';
			list[c][nlist[c]] [1] = '\0';
			strcat(list[c][nlist[c]++], optarg);
			break;

		case 'd':
			for (t = optarg; *t; t++)
				if (*t == 's')	/* -ds: no sym tab output */
					dsflag++;
				else if (*t == 'l') /* -dl: no line num */
					dlflag++;
				else
					error("bad option -d%c", *t);
			break;

		case 'V':	/* version flag or ld VS flag */
			if (optarg[0] == 'S' && optarg[1] == '\0')
				goto ldopt;
			list[Xc0][nlist[Xc0]++] =
			list[Xc2][nlist[Xc2]++] =
			list[Xas][nlist[Xas]++] =
			list[Xld][nlist[Xld]++] = "-V";
			fprintf(stderr, "%s: command -%s\n",
				SGSNAME, RELEASE);
			break;

		case 'Q':	/* warn for non-call use of tv symbols */
#ifdef TV
			list[Xas][nlist[Xas]++] = "-Q";
#endif
			break;

#if M32
		case 'v':	/* M32 version (type) flag */
			fprintf(stderr, "old flag: -v%s ignored\n", optarg);
			break;
#endif

#if N3B || U3B
		case 'R':	/* select run-time startoff */
			if (optarg[1] == '\0') { 
				fixcrt(crt, optarg[0]);
#ifdef TV
				fixcrt(tvcrt, optarg[0]);
#endif
			}
			else {
				crt = optarg;
#ifdef TV
				tvcrt = optarg;
#endif
			}
			break;
#endif

		case 'i':	/* ld: -i or -ild */
#if N3B || b16
			/* if there is an "ld" following the "-i", pass
			 * this on to the link editor and go to the next
			 * argument.
			 */
			if (strcmp( argv[cur_arg], "-ild" ) == 0) {
				list[Xld][nlist[Xld]++] = "-ild";
				c = getopt( argc, argv, "l:" );
			} else
#endif
				list[Xld][nlist[Xld]++] = "-i";
			break;
		case 'L':	/* ld: alternate lib path prefix */
		case 'u':	/* ld: enter sym arg as undef in sym tab */
		case 'l':	/* ld: include library */
		case 'r':	/* ld: no complaint on unres. reloc ent. */
		case 's':	/* ld: line num and sym info stripped */
		case 'x':	/* ld: do not preserve local syms in out st */
		case 'm':	/* ld: print out memory map */
		case 'n':	/* ld: text portion r/o and shared */
		case 'N':	/* ld: data immediately following text */
		case '?':	/* opt char not in optstr; pass to ld */
ldopt:			for (t = optstr; *t && *t!=optopt; t++);
			if (*t && *++t==':')
				i = 1; /* loader option has an arg */
			else
				i = 0; /* no arg or unrecognized option */
			t = stralloc( (i ? strlen(optarg) + 3 : 3) );
			t[0] = '-';
			t[1] = optopt;
			t[2] = '\0';
			if (i) strcat(t, optarg);
			if (nlist[Xld] >= argc+1) {
				free(t);
				error("Too many ld options", (char *) NULL);
				break;
			}
			list[Xld][nlist[Xld]++] = t;
			break;
		case '#':	/* cc command debug flag */
			debug++;
			break;
		case EOF:	/* file argument */
			t = argv[optind++]; /* -> file name */
filearg:		if (((c = getsuf(t)) == 'c') ||
				(c == 'i') || (c == 's') || Eflag) {
				clist[nc++] = t;
				t = setsuf(t, 'o');
			}
			if (nodup(list[Xld], t)) {
				list[Xld][nlist[Xld]++] = t;
				if (getsuf(t) == 'o')
					nxo++;
			}
			break;
		} /* end case */
	} /* end while */

#if M32
	if (mpxflag)
		crt = strcat(crtdir,LAYERCRT0);
#endif

	if (nc == 0) {	/* no files to compile or assemble */
		if (!eflag)
			link();
		dexit();
	}

	if (!(Pflag || Eflag)) /* more than just the preprocessor is
			        * running, so temp files are required */
		mktemps();

	if (eflag)
		dexit();

	if (signal(SIGHUP, SIG_IGN) == SIG_DFL)
		signal(SIGHUP, idexit);
	if (signal(SIGINT, SIG_IGN) == SIG_DFL)
		signal(SIGINT, idexit);
	if (signal(SIGTERM, SIG_IGN) == SIG_DFL)
		signal(SIGTERM, idexit);

	/* undefines for N3B */
#ifdef N3B
	list[Xcp][nlist[Xcp]++] = "-Uos";
	list[Xcp][nlist[Xcp]++] = "-Utss";
	list[Xcp][nlist[Xcp]++] = "-Updp11";
	list[Xcp][nlist[Xcp]++] = "-Uunix";
	list[Xcp][nlist[Xcp]++] = "-Uu370";
	list[Xcp][nlist[Xcp]++] = "-Uvax";
	list[Xcp][nlist[Xcp]++] = "-Umert";
	list[Xcp][nlist[Xcp]++] = "-Uibm";
	list[Xcp][nlist[Xcp]++] = "-URES";
	list[Xcp][nlist[Xcp]++] = "-UPWB";
	list[Xcp][nlist[Xcp]++] = "-URT";
	list[Xcp][nlist[Xcp]++] = "-UTS";
	list[Xcp][nlist[Xcp]++] = "-Uu3b";
	list[Xcp][nlist[Xcp]++] = "-DDMERT";
#endif

	/* set up alternate passes defined by -B and -t options */
	if (chpass != NULL && newpath == NULL)
		newpath = "/lib/n";
	if (newpath != NULL) {
		if (chpass == NULL)
			chpass = "012p";
		for (t = chpass; *t; t++)
			switch (*t) {
			case 'p':
				passcp = stralloc(strlen(newpath) + 4);
				strcpy(passcp, newpath);
				strcat(passcp, N_CP);
				break;

			case '0': /* compiler, pass 1 */
				passc0 = stralloc(strlen(newpath) + 6);
				strcpy(passc0, newpath);
				strcat(passc0, N_C0);
				break;

#ifndef ONEPASS
			case '1': /* compiler, pass2 */
				passc1 = stralloc(strlen(newpath) + 5);
				strcpy(passc1, newpath);
				strcat(passc1, N_C1);
				break;
#else
			case '1': /* ignore 1 since there is no such pass */
				break;
#endif

			case '2': /* optimizer */
				passc2 = stralloc(strlen(newpath) + 6);
				strcpy(passc2, newpath);
				strcat(passc2, N_C2);
				break;

			case 'a': /* assembler */
				passas = stralloc(strlen(newpath) + 6);
				strcpy(passas, newpath);
				strcat(passas, N_AS);
				break;

			case 'l': /* linkage editor */
				passld = stralloc(strlen(newpath) + 6);
				strcpy(passld, newpath);
				strcat(passld, N_LD);
				break;

			default: /* error */
				fprintf(stderr, "Bad option -t%c\n", *t);
				break;

			} /* end switch */
	} /* end if */

	/* process each file (name) in clist */

	for (i = 0; i < nc; i++) {
		if (nc > 1)
			printf("%s:\n", clist[i]);
		sfile = (getsuf(clist[i]) == 's');
		as_escapes = 0;
#if N3B || U3B || M32
		if (sfile && !Eflag && !Pflag) {
			as_in = clist[i];
			assemble(i);
			continue;
		}
#endif
		if (getsuf(clist[i]) == 'i')
			cpp_out = clist[i];
		else if (!preprocess(i))
			continue;
		if (!compile(i))
			continue;
#if N3B
		if (OAflag)
			optimize(i);
		else if (Oflag && as_escapes) {
			printf("-O ignored for %s because of asm()\n", clist[i]);
			if (Sflag) {
				as_in = setsuf( clist[i], 's' );
				move( c_out, as_in );
			}
		} else if (Oflag)
#else
		if (Oflag)
#endif
			optimize(i);
		if (!Sflag)
			assemble(i);
	} /* end loop */
	if (!eflag)
		link();

	dexit();
}


/*===================================================================*/
/*								     */
/*                   PREPROCESSOR                                    */
/*                                                                   */
/*===================================================================*/

preprocess (i)
	int i; /* clist index of filename */
{
	int j;
	int na = 0;
	/* build argv argument to callsys */
	av[na++] = N_CP;
#if M32
#ifdef u3b
	av[na++] = "-Uu3b";
#endif
#ifdef vax
	av[na++] = "-Uvax";
#endif
#ifdef sun
	av[na++] = "-Usun";
#endif
#ifdef tahoe
	av[na++] = "-Utahoe";
#endif
#ifdef accel
	av[na++] = "-Uaccel";
#endif
#ifdef gould
	av[na++] = "-Ugould";
#endif
#ifdef alliant
	av[na++] = "-Ualliant";
#endif
#endif

	av[na++] = clist[i];
	av[na++] = cpp_out
		 = Eflag ? "-" :
			 (Pflag ? setsuf(clist[i], 'i') : tmp1);
	for (j = 0; j < nlist[Xcp]; j++)
		av[na++] = list[Xcp][j];
#if M32
	av[na++] = incdir;
	if (mpxflag)
		av[na++] = "-DMPX";
#endif M32
	
#if N3B
	av[na++] = INCLDIR;
#endif N3B
#ifdef b16
	av[na++] = INCDIR;
	if (sfile && tvflag)
		av[na++] = "-DB16TV";
	if (sfile)
		av[na++] = "-P";
#endif
	av[na] = 0;	/* terminate arg list */

	PARGS;

	if (callsys(REL, passcp, av)) {
		cflag++;
		eflag++;
		return(0);
	}
	if (Pflag || Eflag)
		return(0);
#ifdef b16
	if (sfile) {
		as_in = cpp_out;
		assemble(i);
		return(0);
	}
#endif
	return(1);
}


/*===================================================================*/
/*                                                                   */
/*                  COMPILER (single pass or pass one)               */
/*                                                                   */
/*===================================================================*/

compile (i)
	int i;
{
	int j;
	int na = 0;
	int front_ret;

	if (dflag)
		dump(cpp_out);

	av[na++] = N_C0;
	av[na++] = "-i";
	av[na++] = cpp_out;
	av[na++] = "-o";
#ifdef ONEPASS
	av[na++] = c_out = as_in
		 = (Sflag && !Oflag) ? setsuf(clist[i], 's') : tmp2;
#else
	av[na++] = c_in = tmp2;
#endif
	av[na++] = "-f";
	av[na++] = clist[i];
	if (dsflag)
		av[na++] = "-ds";
	if (dlflag)
		av[na++] = "-dl";
#if U3B || b16 || M32
	if (pflag)
		av[na++] = "-p";
#endif
	for (j = 0; j < nlist[Xc0]; j++)
		av[na++] = list[Xc0][j];
	av[na] = 0;

	PARGS;

#ifdef u3b5
	front_ret = callsys(FULL,  passc0, av );
#else
	front_ret = callsys(REL,  passc0, av );
#endif
	if (front_ret == 1) 	/* COMP or FRONT returns 1 for assembler escapes */
		as_escapes++;
	else if (front_ret > 1) {
		cflag++;
		eflag++;
		return(0);
	}

#ifdef PERF
	STATS("compiler ");
#endif

#ifndef ONEPASS
	if (Fdebug) {
		dump(c_in);
		cflag++;
		return(0);
	}
#endif
#ifndef ONEPASS
	return(comp2(i)); /* compiler, pass 2 */
#else
	return(1);
#endif
}


/*===================================================================*/
/*                                                                   */
/*                    COMPILER (pass two)                            */
/*                                                                   */
/*===================================================================*/

#ifndef ONEPASS
comp2 (i)
	int i;
{
	int j;
	int na = 0;

	av[na++] = N_C1;
	av[na++] = "-i";
	av[na++] = c_in;
	av[na++] = "-o";
	av[na++] = c_out = as_in
		 = (Sflag && !Oflag) ? setsuf(clist[i], 's') : tmp3;
	for (j = 0; j < nlist[Xc1]; j++)
		av[na++] = list[Xc1][j];
	av[na] = 0;

	PARGS;

#ifdef u3b5
	if (callsys(FULL, passc1, av)) {
#else
	if (callsys(REL, passc1, av)) {
#endif
		cflag++;
		eflag++;
		if (Sflag)
			cunlink(c_out);
		return(0);
	}

#ifdef PERF
	STATS("comp.back");
#endif

	if (Bdebug) {
		dump(c_out);
		cflag++;
		return(0);
	}
	return(1);
}
#endif /* ONEPASS */


/*===================================================================*/
/*                                                                   */
/*                      OPTIMIZER                                    */
/*                                                                   */
/*===================================================================*/

optimize (i)
	int i;
{
	int j;
	int na = 0;

	av[na++] = N_C2;
	av[na++] = "-I";
	av[na++] = c_out;
	av[na++] = "-O";
	av[na++] = as_in
		 = Sflag ? setsuf(clist[i], 's') : tmp4;
	for (j = 0; j < nlist[Xc2]; j++)
		av[na++] = list[Xc2][j];
	av[na] = 0;

	PARGS;

#ifdef u3b5
	if (callsys(FULL, passc2, av)) {
#else
	if (callsys(REL, passc2, av)) {
#endif
		if (Sflag) {
			if (move(c_out, as_in)) { /* move failed */
				cunlink(c_out);
				return(0);
			}
		}
		else {
			cunlink(as_in);
			as_in = c_out;
		}
		printf("Optimizer failed, -O ignored for %s\n", clist[i]);
	}

#ifdef PERF
	STATS("optimizer");
#endif

	return(1);
}


/*===================================================================*/
/*                                                                   */
/*                    ASSEMBLER                                      */
/*                                                                   */
/*===================================================================*/

assemble (i)
	int i;
{
	int j;
	int na = 0;

	if (dflag)
		dump(as_in);

	av[na++] = N_AS;
#if N3B
	if (!sfile && !as_escapes)	/* for DMERT -m means don't invoke M4 */
		av[na++] = "-m";
#endif
#if N3B || U3B || M32
	if (dlflag)
		av[na++] = "-dl";
#endif
#ifdef U3B
	av[na++] = "-A";	/* alignment flag */
#endif
	for (j = 0; j < nlist[Xas]; j++)
		av[na++] = list[Xas][j];
	av[na++] = "-o";
	av[na++] = as_out = setsuf(clist[i], 'o');
	av[na++] = as_in;
	av[na] = 0;

	PARGS;

	if (callsys(REL, passas, av)) {
		cflag++;
		eflag++;
		cunlink(as_out);
		return(0);
	}

#ifdef PERF
	STATS("assembler");
#endif

	return(1);
}


/*===================================================================*/
/*                                                                   */
/*                LINKAGE EDITOR                                     */
/*                                                                   */
/*===================================================================*/

link ()
{
	int j;
	int na = 0;

	if (!cflag) {
		av[na++] = N_LD;
		av[na++] = "-o";
		if (ld_out == NULL) 
			ld_out = A_OUT;
		av[na++] = ld_out;
#ifdef b16
		if (pflag)
			av[na++] = MCRT0;
#endif
#if N3B || M32
	/*	av[na++] = "-X"; */
#if !N3B
#ifdef TV
		if (tvflag)
			av[na++] = tvcrt;
		else
#endif TV
		av[na++] = crt;		/* always assign some crt	*/
#endif !N3B
#endif N3B || M32

#ifdef U3B
		av[na++] = crt;
#endif
#if b16 || U3B || M32
		if (pflag)
			av[na++] = "-L/lib/libp";	/* use profiled libraries */
#endif
#if M32
		av[na++] = strcat(libdir,"/lib");
		if (jxflag)
			av[na++] = strcat(mapdir,"/lib/jxmap");
		else 
			av[na++] = strcat(mapdir,"/lib/mpxmap");
#endif
		for (j = 0; j < nlist[Xld]; j++) /* app files, opts, and libs */
			av[na++] = list[Xld][j];
#if U3B
		av[na++] = "-lc";
#endif
#if M32
		if (jxflag)
		{
			av[na++] = "-lj";
			av[na++] = "-lsys";
		}
		else {
			av[na++] = "-r";
			av[na++] = "-a";
			av[na++] = "-lmj";
		}
		av[na++] = "-lj";
		av[na++] = "-lc";

#endif
#if b16
		av[na++] = "-l";
#endif
#if U3B || M32
		if (gflag)
		{
#ifdef u3b5
			strcpy(gpath, "/usr/lib/libg.a");
#else
			strcpy(gpath, dmddir);
			strcat(gpath, "/lib/m32/libg.a");
#endif
			av[na++] = gpath;
		}
#endif
		av[na] = 0;

		if (na > MINLDARGS) { /* if file given or
						   * flag set by user */
			PARGS;
			eflag |= callsys(REL, passld, av);
		}

#if M32
		if (mpxflag)
		{
			mpxmagic(ld_out);
		}
#endif
		if ((nc == 1) && (nxo == 1) && (eflag == 0))
			/* delete .o file if single file compiled and loaded */
			cunlink(setsuf(clist[0], 'o'));

#ifdef PERF
		STATS("link edit");
#endif

	}
}
			
#define ERR -1
#include <fcntl.h>
mpxmagic(ldout)
char *ldout;
{
	int fd;
	char *ptr;
	short svalue;

	if ((fd = open (ldout,O_WRONLY)) == ERR)
	{	fprintf(stderr,"Cannot open %s to write magic number\n",ldout);
		exit(1);
	}

	svalue = 0x5620;
	ptr = (char *) &svalue;

	if (lseek(fd,22,0) == ERR)
	{
		fprintf(stderr,"cannot seek to write magic number\n");
		exit(1);
	}
	if (write(fd,ptr,2) == ERR)
	{
		fprintf(stderr,"Cannot write %s\n",ldout);
		exit(1);
	}
}

idexit()
{
	signal(SIGINT, idexit);
	signal(SIGTERM, idexit);
	eflag = 100;
	dexit();
}

dexit()
{
	if (!Pflag) {
		if (Oflag)
			cunlink(tmp4);
		if (!Sflag)
			cunlink(tmp3);
		cunlink(tmp2);
		cunlink(tmp1);
	}
#ifdef PERF
	if (eflag == 0)
		pwrap();
#endif
	exit(eflag);
}

error(s, x, y)
	char *s, *x, *y;
{
	fprintf(Eflag ? stderr : stdout , s, x, y);
	putc('\n', Eflag ? stderr : stdout);
	cflag++;
	eflag++;
}




char
getsuf(as)
	char as[];
{
	register int c;
	register char *s;
	register int t;

	s = as;
	c = 0;
	while (t = *s++)
		if (t == '/')
			c = 0;
		else
			c++;
	s -= 3;
	if ((c <= 14) && (c > 2) && (*s++ == '.'))
		return(*s);
	return(0);
}

char *
setsuf(as, ch)
	char as[];
{
	register char *s, *s1;

	s = s1 = copy(as);
	while (*s)
		if (*s++ == '/')
			s1 = s;
	s[-1] = ch;
	return(s1);
}

char fullpath[256];	/* full path to program to be executed by callsys */
int
callsys(type, f, v)
	int type;
	char f[], *v[];
{
	register int pid, w;
	int status;

	fflush(stdout);
	fflush(stderr);

	if (debug >= 2) {	/* user specified at least two #'s */
		printf("%s: process: %s\n", CC, f);
		if (debug >= 3)	/* 3 or more #'s:  don't exec anything */
			return(0);
	}

#ifdef PERF
	ttime = times(&ptimes);
#endif
	/*
	for (w=0; w<256; w++)
		fullpath[w] = 0;
	*/
	if (type == REL)
		strcpy(fullpath,dmddir);
	else
		fullpath[0] = '\0';
	strcat(fullpath,f);

	if ((pid = fork()) == 0) {
		execvp(fullpath, v);
		fprintf(stderr,"Can't exec %s\n", fullpath);
		exit(100);
	}
	else
		if (pid == -1) {
			fprintf(stderr,"Process table full - try again later\n");
			eflag = 100;
			dexit();
		}
	while ((w = wait(&status)) != pid && w != -1) ;

#ifdef PERF
	ttime = times(&ptimes) - ttime;
#endif

	if (w == -1) {
		fprintf(stderr,"Lost %s - No child process!\n", fullpath);
		eflag = w;
		dexit();
	}
	else {
		if (((w = status & 0xff) != 0) && (w != SIGALRM)) {
			if (w != SIGINT) {
				fprintf(stderr, "Fatal error in %s\n", fullpath);
				fprintf(stderr,"Status %x\n",status);
			}
			eflag = status;
			dexit();
		}
	}
	return((status >> 8) & 0xff);
}

int
nodup(l, os)
	char **l, *os;
{
	register char *t, *s;
	register int c;

	s = os;
	if (getsuf(s) != 'o')
		return(1);
	while(t = *l++) {
		while(c = *s++)
			if (c != *t++)
				break;
		if ((*t == '\0') && (c == '\0'))
			return(0);
		s = os;
	}
	return(1);
}

int
cunlink(f)
	char *f;
{
	if (f == NULL)
		return(0);
	return(unlink(f));
}

int
move(from, to)
	char *from, *to;
{
	av[0] = "mv";
	av[1] = from;
	av[2] = to;
	av[3] = 0;
	if (callsys(FULL, "mv", av)) {
		error("Can't move %s to %s", from, to);
		return(1);
	}
	return(0);
}

dump(f)
	char *f;
{
	register int ch;

	if (freopen(f, "r", stdin) == NULL) {
		fprintf(stderr, "Can't reopen %s\n", f);
		return;
	}
	while ((ch = getchar()) != EOF)
		putchar(ch);
}

#if N3B || U3B || M32
fixcrt(path,chr) char * path; char chr; {

	char * fpath;

	fpath = path;
	while (*path != '\0')
		path++;
	while (strncmp(path,"crt",3) && path != fpath)
		path--;
	if (path == fpath) {
		fprintf(stderr, "Can't modify run-time start-off\n");
		return;
		}
	path += 3;
	*path = chr;
	}
#endif

char *
copy(s)
	register char *s;
{
	register char *ns;

	ns = stralloc(strlen(s));
	return(strcpy(ns, s));
}

char *
stralloc(n)
	int n;
{
	char *malloc();
	register char *s;

	s = malloc(n+1);
	if (s == NULL) {
		error("out of space", (char *) NULL);
		dexit();
	}
	return(s);
}

mktemps()
{
	char * s;
	int i;

	i = sizeof(TMPDIR) + sizeof(SGSF) - 2;
	s = stralloc(i + 10);
	strcpy(s, TMPDIR);
	strcat(s, SGSF);
	strcat(s, "1XXXXXX");
	tmp1 = copy(mktemp(s));
	(tmp2 = copy(tmp1))[i] = '2';
	(tmp3 = copy(tmp1))[i] = '3';
	(tmp4 = copy(tmp1))[i] = '4';
}

getXpass(c, opt)
	char	c,
		*opt;
{
	switch (c) {
	case '0':
	case '1':
	case '2':
		return(c - '0' + 1);
	case 'p':
		return(Xcp);
	case 'a':
		return(Xas);
	case 'l':
		return(Xld);
	default:
		error("Unrecognized pass name: '%s%c", opt, c);
		return(-1);
	}
}

#ifdef PERF
pexit()
{
	fprintf(stderr, "Too many files for performance stats\n");
	dexit();
}
#endif

#ifdef PERF
pwrap()
{
	int	i;

	if ((perfile = fopen("cc.perf.info", "r")) == NULL)
		dexit();
	fclose(perfile);
	if ((perfile = fopen("cc.perf.info", "a")) == NULL)
		dexit();
	for (i = ii-1; i > 0; i--) {
		stats[i].perform.proc_user_time -= stats[i-1].perform.proc_user_time;
		stats[i].perform.proc_system_time -= stats[i-1].perform.proc_system_time;
		stats[i].perform.child_user_time -= stats[i-1].perform.child_user_time;
		stats[i].perform.child_system_time -= stats[i-1].perform.child_system_time;
	}
	for (i = 0; i < ii; i++)
		fprintf(perfile, "%s\t%07ld\t%07ld\t%07ld\t%07ld\t%07ld\n",
			stats[i].module,stats[i].ttim,stats[i].perform);
	fclose(perfile);
}
#endif
extern char *getenv();
getdmd(str)
char *str;
{
	char *enpt;

	if (((enpt = getenv("DMD")) == (char *)0) || (*enpt == '\0'))
		strcpy(str,DMD);
	else
		strcpy(str,enpt);
	return;
}
