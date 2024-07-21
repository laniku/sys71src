/************************************************************

Created: Monday, May 7, 1990 at 8:55 PM
	FixMath.h
	C Interface to the Macintosh Libraries


	Copyright Apple Computer, Inc.	1985-1991
	All rights reserved

	Change History (most recent first):

	   <SM3>	  8/4/93	JDR		Sync with Reality and Sound Mgr.
		 <7>	 3/10/93	JDR		Added kFix1.
		 <6>	  8/8/91	JL		Update copyright
		 <5>	10/26/90	JDR		Made the Frac2x, Fix2x, X2Fix, and X2Frac traps in-line only for
									the non-mc68881 mode. Otherwise it has to be glue to the FPU
									libraries. (see JPO for more info)
		 <4>	 10/5/90	JDR		Frac2X, Fix2X, X2Fix, and X2Frac are now inlines. They use to be
									a jsr to the SANE glue which was not only the wrong file for it,
									but is only called the trap with the autopop bit set, very
									silly.

CHANGE LOG:
	19 Oct 90  JPO  Made Frac2x, Fix2x, X2Fix, and X2Frac
					  in-line trap calls in non-mc68881 mode.

************************************************************/


#ifndef __FIXMATH__
#define __FIXMATH__

#ifndef __TYPES__
#include <Types.h>
#endif

enum {
	fixed1				= (long)0x00010000,
	fract1				= (long)0x40000000,
	positiveInfinity	= (long)0x7FFFFFFF,
	negativeInfinity	= (long)0x80000000
};

#ifdef __cplusplus
extern "C" {
#endif

pascal Fract Fix2Frac(Fixed x)
	= 0xA841;
pascal long Fix2Long(Fixed x)
	= 0xA840;
pascal Fixed Long2Fix(long x)
	= 0xA83F;
pascal Fixed Frac2Fix(Fract x)
	= 0xA842;
pascal Fract FracMul(Fract x,Fract y)
	= 0xA84A;
pascal Fixed FixDiv(Fixed x,Fixed y)
	= 0xA84D;
pascal Fract FracDiv(Fract x,Fract y)
	= 0xA84B;
pascal Fract FracSqrt(Fract x)
	= 0xA849;
pascal Fract FracSin(Fixed x)
	= 0xA848;
pascal Fract FracCos(Fixed x)
	= 0xA847;
pascal Fixed FixATan2(long x,long y)
	= 0xA818;
	

#ifdef mc68881

pascal extended Frac2X(Fract x);
pascal extended Fix2X(Fixed x);
pascal Fixed X2Fix(extended x);
pascal Fract X2Frac(extended x);

#else

pascal extended Frac2X(Fract x)
	= 0xA845;
pascal extended Fix2X(Fixed x)
	= 0xA843;
pascal Fixed X2Fix(extended x)
	= 0xA844;
pascal Fract X2Frac(extended x)
	= 0xA846;

#endif


#ifdef __cplusplus
}
#endif

#endif
