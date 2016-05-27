/*
 *	static char *ID_pathsh = "@(#) paths.h: 1.7 4/24/83";
 *
 *
 *	Pathnames for m32
 */

/*
 *	Directory containing libraries and executable files
 *	(e.g. assembler pass 1)
 */
#ifndef DMD
#define DMD "/u/dwd/5620layers"
#endif
#define LIBDIR	"/u/dwd/5620layers/lib"
#define LLIBDIR1 "/u/dwd/5620layers/sgs/usr/lib"
#define NDELDIRS 2

/*
 *	Directory containing executable ("bin") files
 */
#define BINDIR	"/u/dwd/5620layers/bin"

/*
 *	Directory containing include ("header") files for building tools
 */
#define INCDIR	"/u/dwd/5620layers/include/sgs"

/*
 *	Directory for "temp"  files
 */
#define TMPDIR	"/tmp"

/*
 *	Default name of output object file
 */
#define A_OUT	"m32a.out"

/*
 *	The following pathnames will be used by the "cc" command
 *
 *	m32 cross compiler
 */
#define CPP	"/u/dwd/5620layers/lib/cpp"
/*
 *	Directory containing include ("header") files for users' use
 */
#define INCLDIR	"-I/tmp"
#define COMP	"/u/dwd/5620layers/lib/comp"
#define C0	"/u/dwd/5620layers/lib/front"
#define C1	"/u/dwd/5620layers/lib/back"
#define OPTIM	"/u/dwd/5620layers/lib/optim"
/*
 *	m32 cross assembler
 */
#define AS	"/u/dwd/5620layers/bin/m32as"
#define AS1	"/u/dwd/5620layers/lib/m32as1"	/* assembler pass 1 */
#define AS2	"/u/dwd/5620layers/lib/m32as2"	/* assembler pass 2 */
#define M4	"/usr/bin/m4"			/* macro preprocessor */
#define CM4DEFS	"/u/dwd/5620layers/lib/cm4defs"	/* C interface macros */
#define CM4TVDEFS "/u/dwd/5620layers/lib/cm4tvdefs"	/* C macros with 'tv' call */
/*
 *	m32 link editor
 */
#define LD	"/u/dwd/5620layers/bin/m32ld"
#define LD2	"/u/dwd/5620layers/lib/m32ld2"	/* link editor pass 2 */
#define CRT0	"/u/dwd/5620layers/lib/crt0.o"	/* C run time startoff */
#define MCRT0	"/u/dwd/5620layers/lib/mcrt0.o"	/* Profile run time startoff */
#define FCRT0	"/u/dwd/5620layers/lib/fcrt0.o"	/* Float Pt. run time startoff */
#define FMCRT0	"/u/dwd/5620layers/lib/fmcrt0.o"	/* Profiled Float Pt. run time startoff */
#define TVCRT0	"/u/dwd/5620layers/lib/tvcrt0.o"	/* C run time startoff for tv */

/*
 *	Test versions of comp, optim, as, ld - for developers only
 */
#define	NCOMP	""
#define NOPTIM	""
#define NAS	""
#define NAS1	""
#define NAS2	""
#define NLD	""
#define NLD2	""

/*
 *	Backup versions of comp, optim, as, ld - for developers only
 */
#define OCOMP	"/u/dwd/5620layers/lib/comp.back"
#define OC0	"/u/dwd/5620layers/lib/front.back"
#define OC1	"/u/dwd/5620layers/lib/back.back"
#define OOPTIM	"/u/dwd/5620layers/lib/optim.back"
#define OAS	"/u/dwd/5620layers/bin/m32as.back"
#define OAS1	"/u/dwd/5620layers/lib/m32as1.back"
#define OAS2	"/u/dwd/5620layers/lib/m32as2.back"
#define OLD	"/u/dwd/5620layers/bin/m32ld.back"
#define OLD2	"/u/dwd/5620layers/bin/m32ld2.back"
