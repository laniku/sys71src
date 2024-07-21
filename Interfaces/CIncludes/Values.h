/************************************************************

Created: Monday, November 21, 1988 at 10:37 AM
	Values.h
	C Interface to the Macintosh Libraries



	Copyright Apple Computer, Inc.	1985-1991
	All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <5>	  8/8/91	JL		update copyright
		10 Oct 90	JAL	removed HUGE_VAL.
		27 May 87	KLH	added HUGE_VAL.
		*** MPW 2.1d1 ***
		9 Oct 87	KLH HIBITS & MAXSHORT "((" taken out on conversion to C++
						put back in.

	To Do:
************************************************************/


#ifndef __VALUES__
#define __VALUES__

#ifndef __SANE__
#include <SANE.h>
#endif

#define BITSPERBYTE 8
#define BITS(type) (BITSPERBYTE * (int)sizeof(type))
#define HIBITS ((short)(1<<BITS(short)-1))
#define HIBITI (1<<BITS(int)-1)
#define HIBITL (1L<<BITS(long)-1)
#define MAXSHORT ((short)~HIBITS)
#define MAXINT (~HIBITI)
#define MAXLONG (~HIBITL)
#define MAXEXTENDED nextextended(inf(),0.0)
#define MAXDOUBLE nextdouble(inf(),0.0)
#define MAXFLOAT nextfloat(inf(),0.0)
#define MINEXTENDED scalb(XMINEXP-1,1.0)
#define MINDOUBLE scalb(DMINEXP-1,1.0)
#define MINFLOAT scalb(FMINEXP-1,1.0)
#define _IEEE 1
#define _XEXPLEN 15
#define _DEXPLEN 11
#define _FEXPLEN 8
#define _HIDDENBIT 1
#define _XHIDDENBIT 0
#define XMINEXP (-16382)
#define DMINEXP (-1021)
#define FMINEXP (-125)
#define XMAXEXP 16384
#define DMAXEXP 1024
#define FMAXEXP 128
#define _LENBASE 1
#define _EXPBASE (1<<_LENBASE)
#define XSIGNIF 64
#define DSIGNIF 53
#define FSIGNIF 24
#define XMAXPOWTWO scalb(XSIGNIF-1,1.0)
#define DMAXPOWTWO scalb(DSIGNIF-1,1.0)
#define FMAXPOWTWO scalb(FSIGNIF-1,1.0)
#define LN_MAXDOUBLE log(MAXDOUBLE)
#define LN_MINDOUBLE log(MINDOUBLE)
#define MAXCOMP (scalb(63,1.0)-1.0)

#endif
