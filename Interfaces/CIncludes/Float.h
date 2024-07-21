/************************************************************

	Float.h
	Characteristics of floating-point types
	
	Copyright Apple Computer,Inc.  1987-1991
	All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <2>	  8/8/91	JL		Update copyright

	To Do:
************************************************************/


#ifndef __FLOAT__
#define __FLOAT__


#define	DBL_DIG				15
#define	DBL_MANT_DIG		53
#define	DBL_MAX_10_EXP		308
#define	DBL_MAX_EXP			1024
#define	DBL_MIN_10_EXP		(-307)
#define	DBL_MIN_EXP			(-1021)

#define	FLT_DIG				7
#define	FLT_MANT_DIG		24
#define	FLT_MAX_10_EXP		38
#define	FLT_MAX_EXP			128
#define	FLT_MIN_10_EXP		(-37)
#define	FLT_MIN_EXP			(-125)

#define	FLT_RADIX			2
#define	FLT_ROUNDS			1

#define	LDBL_DIG			19
#define	LDBL_MANT_DIG		64
#define	LDBL_MAX_10_EXP		4932
#define	LDBL_MAX_EXP		16384
#define	LDBL_MIN_10_EXP		(-4931)
#define	LDBL_MIN_EXP		(-16382)

#define	DBL_EPSILON			(*(double *)_DBL_EPSILON)
#define DBL_MAX				(*(double *)_DBL_MAX)
#define DBL_MIN				(*(double *)_DBL_MIN)
#define	FLT_EPSILON			(*(float *)_FLT_EPSILON)
#define FLT_MAX				(*(float *)_FLT_MAX)
#define FLT_MIN				(*(float *)_FLT_MIN)

#ifdef mc68881

#define	LDBL_EPSILON		(*(long double *)_LDBL_EPSILON)
#define LDBL_MAX			(*(long double *)_LDBL_MAX)
#define LDBL_MIN			(*(long double *)_LDBL_MIN)

#else

#define	LDBL_EPSILON		(*(long double *)(_LDBL_EPSILON+1))
#define LDBL_MAX			(*(long double *)(_LDBL_MAX+1))
#define LDBL_MIN			(*(long double *)(_LDBL_MIN+1))

#endif

extern int _DBL_EPSILON[];
extern int _DBL_MAX[];
extern int _DBL_MIN[];
extern int _FLT_EPSILON[];
extern int _FLT_MAX[];
extern int _FLT_MIN[];
extern short _LDBL_EPSILON[];
extern short _LDBL_MAX[];
extern short _LDBL_MIN[];

#endif