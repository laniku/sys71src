/************************************************************

Created: Wednesday, September 27, 1989 at 2:58 PM
	SANE.h
	C Interface to the Macintosh Libraries


	Copyright Apple Computer, Inc.	1985-1991
	All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <4>	 2/17/92	MH		Move def on extended80 to types.h, and include types.h
		 <3>	  8/8/91	JL		Updated copyright

	26 Oct 89 - Jon Okada
		Removed initialization of IEEEDEFAULTENV for -mc68881 mode
		  (deferred to CLib881.o); declared IEEEDEFAULTENV extern.
		Installed #include of Math.h.
		Removed declarations of sqrt, log, exp, tan, cos, sin, and
		  atan (deferred to Math.h).
		Changed declarations of functions power and inf to macro
		  definitions using pow and __inf.

************************************************************/


#ifndef __SANE__
#define __SANE__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __MATH__
#include <Math.h>
#endif

#ifdef mc68881

/* specific to the MC68881 SANE library */

#define INEXACT ((exception)(8))
#define DIVBYZERO ((exception)(16))
#define UNDERFLOW ((exception)(32))
#define OVERFLOW ((exception)(64))
#define INVALID ((exception)(128))
#define CURINEX1 ((exception)(256))
#define CURINEX2 ((exception)(512))
#define CURDIVBYZERO ((exception)(1024))
#define CURUNDERFLOW ((exception)(2048))
#define CUROVERFLOW ((exception)(4096))
#define CUROPERROR ((exception)(8192))
#define CURSIGNAN ((exception)(16384))
#define CURBSONUNOR ((exception)(32768))

#else

/* specific to the software SANE library */

#define INVALID ((exception)(1))
#define UNDERFLOW ((exception)(2))
#define OVERFLOW ((exception)(4))
#define DIVBYZERO ((exception)(8))
#define INEXACT ((exception)(16))
#define IEEEDEFAULTENV ((environment)(0))	/*IEEE-default floating-point environment*/

#endif										/* mc68881 */

/* The common interface to the SANE library */

/* Decimal Representation Constants */

#define SIGDIGLEN 20						/* significant decimal digits */
#define DECSTROUTLEN 80 					/* max length for dec2str output */

/* Decimal Formatting Styles */

#define FLOATDECIMAL ((char)(0))
#define FIXEDDECIMAL ((char)(1))

/* Ordering Relations */

#define GREATERTHAN ((relop)(0))
#define LESSTHAN ((relop)(1))
#define EQUALTO ((relop)(2))
#define UNORDERED ((relop)(3))

/* Inquiry Classes */

#define SNAN ((numclass)(0))
#define QNAN ((numclass)(1))
#define INFINITE ((numclass)(2))
#define ZERONUM ((numclass)(3))
#define NORMALNUM ((numclass)(4))
#define DENORMALNUM ((numclass)(5))

/* Rounding Directions */

#define TONEAREST ((rounddir)(0))
#define UPWARD ((rounddir)(1))
#define DOWNWARD ((rounddir)(2))
#define TOWARDZERO ((rounddir)(3))

/* Rounding Precisions */

#define EXTPRECISION ((roundpre)(0))
#define DBLPRECISION ((roundpre)(1))
#define FLOATPRECISION ((roundpre)(2))

#ifdef mc68881

typedef long exception;

struct environment {
	long FPCR;
	long FPSR;
};

typedef struct environment environment;

extern environment IEEEDEFAULTENV;

struct trapvector {
	void (*unordered)();
	void (*inexact)();
	void (*divbyzero)();
	void (*underflow)();
	void (*operror)();
	void (*overflow)();
	void (*signan)();
};

typedef struct trapvector trapvector;
#else

typedef short exception;
typedef short environment;
typedef struct {short w[6];} extended96;

struct mischaltinfo {
	unsigned short haltexceptions;
	unsigned short pendingCCR;
	long pendingD0;
};

typedef struct mischaltinfo mischaltinfo;
typedef pascal void (*haltvector)(mischaltinfo *misc, void *src2, void *src, void *dst, short opcode);
#endif

typedef short relop;						/* relational operator */
typedef short numclass; 					/* inquiry class */
typedef short rounddir; 					/* rounding direction */
typedef short roundpre; 					/* rounding precision */

struct decimal {
	char sgn;								/*sign 0 for +, 1 for -*/
	char unused;
	short exp;								/*decimal exponent*/
	struct{
		unsigned char length;
		unsigned char text[SIGDIGLEN];		/*significant digits */
		unsigned char unused;
		}sig;
};

typedef struct decimal decimal;
struct decform {
	char style; 							/*FLOATDECIMAL or FIXEDDECIMAL*/
	char unused;
	short digits;
};

typedef struct decform decform;
#ifdef __cplusplus
extern "C" {
#endif

#ifdef mc68881

struct trapvector gettrapvector(void);
void settrapvector(const trapvector *v);
void x96tox80(const extended *x,extended80 *x80);
void x80tox96(const extended80 *x80,extended *x);

#else

haltvector gethaltvector(void); 
void sethaltvector(haltvector v);
void x96tox80(const extended96 *x96,extended *x);
void x80tox96(const extended *x,extended96 *x96);

#endif

void num2dec(const decform *f,extended x,decimal *d);
extended dec2num(const decimal *d); 
void dec2str(const decform *f,const decimal *d,char *s);
void str2dec(const char *s,short *ix,decimal *d,short *vp); 
extended remainder(extended x,extended y,short *quo);
extended rint(extended x);
extended scalb(short n,extended x); 
extended logb(extended x);
extended copysign(extended x,extended y);
extended nextfloat(extended x,extended y);
extended nextdouble(extended x,extended y); 
extended nextextended(extended x,extended y);
extended log2(extended x);
extended log1(extended x);
extended exp2(extended x);
extended exp1(extended x);

#define power(x,y) pow(x,y)

extended ipower(extended x,short i);
extended compound(extended r,extended n);
extended annuity(extended r,extended n);
extended randomx(extended *x);
numclass classfloat(extended x);
numclass classdouble(extended x);
numclass classcomp(extended x); 
numclass classextended(extended x); 
long signnum(extended x);
void setexception(exception e,long s);
long testexception(exception e);
void sethalt(exception e,long s);
long testhalt(exception e); 
void setround(rounddir r);
rounddir getround(void);
void setprecision(roundpre p);
roundpre getprecision(void);
void setenvironment(environment e); 
void getenvironment(environment *e);
void procentry(environment *e); 
void procexit(environment e);
relop relation(extended x,extended y);
extended nan(unsigned char c);

#define inf() __inf()

extended pi(void);
#ifdef __cplusplus
}
#endif

#endif
