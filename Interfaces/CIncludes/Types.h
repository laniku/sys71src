/*
	File:		Types.h

	Contains:	C Interface to the Macintosh Libraries

	Written by:	Apple Computer, Inc.

	Copyright:	© 1985-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM6>	11/10/93	fau		Update from SuperMunggio <SMG2>.
	  <SMG2>	 9/29/93	chp		Add common unsigned types: uchar, ushort, ulong, uint.
	   <SM5>	  8/5/93	JDR		sync with Reality, moved NumVersion from Files.h
		<15>	 8/28/92	DCL		Fixed enums with commas before the closing brace. MPW now
									complains.
		<14>	 6/11/92	DCL		Cleanup & formatting to match Interface Stacks. Happy Happy Joy
									Joy.
		<13>	  5/5/92	DCL		For New Inside Mac: Moved definition(s) of 'style' to Types to
									break a circular dependancy. It won't work in QDText (the
									NIIM-correct place for it)  Yuk.  Someday we've got to find a
									better place.
		<12>	 2/17/92	MH		Changed noErr back to #define.  Turned out that changing it to
									an enum  <11> was the wrong thing to do for some end users, even
									though it was not problem for the Blue Build.     ---AND---
									Moved def of extended80 here from SANE.h and expanded the
									defintion so that it is defined as extended when mc68881 is off.
									This type is now used in several different interface files where
									extended used to be used. The extended type varies with the
									setting of mc68881, but toolbox and os interactions must use an
									80 bit  rather than 96 bit type.
		<11>	11/11/91	MH		redefine noErr as an enum intead of #define. To match errors in
									errors.h, and provide better type checking.
		<10>	 7/31/91	JL		Updated Copyright.
		 <9>	 1/27/91	LN		Checked in Database generate file from DSG. Added
									SystemSevenOrLater and SystemSixOrLater flags and rearranged
									file.
		 <8>	  1/3/91	JDR		(dba) Adding Str32 type for AppleTalk.h
		 <6>	12/14/90	dba		<JDR> add Ptr types to match Pascal
		 <5>	 11/4/90	dba		get rid of useless const in front of the StringPtr in the Length
									inline for C++ (it is impossible to make an inline that takes
									const strings, but returns a non-const unsigned char reference
									for the length); added constStr63Parameter, constStr32Parameter,
									constStr31Parameter, constStr27Parameter, constStr15Parameter;
									changed DebugStr, SysBreakStr, and SysBreakFunc to take const
									parameter
		 <4>	  10/9/90	JAL		Changed length definition.
		 <3>	  7/2/90	PKE		Moved definition of LangCode here from Packages.h.
		 <2>	 5/29/90	ngk		Added definition of ScriptCode, was in Packages.
		 <1>	12/17/89	CCH		Adding for the first time into BBS.
	   <1.1>	 11/9/88	CCH		Fixed headers and removed projector resource.
	   <1.0>	 11/9/88	CCH		Adding to EASE.

*/

#ifndef __TYPES__
#define __TYPES__


#ifndef SystemSevenOrLater
#define SystemSevenOrLater 0
#endif

#ifndef SystemSixOrLater
#define SystemSixOrLater SystemSevenOrLater
#endif

#ifndef NULL
#define NULL 0
#endif
#define nil 0

#define noErr 0			/*All is well*/

/* common aliases for C unsigned types */
typedef unsigned char	uchar;
typedef unsigned short	ushort;
typedef unsigned long	ulong;
typedef unsigned int	uint;

typedef unsigned char Byte;
typedef char SignedByte;
typedef char *Ptr;
typedef Ptr *Handle;	/*  pointer to a master pointer */

typedef long Fixed;		/* fixed point arithmatic type */
typedef Fixed *FixedPtr;
typedef long Fract;
typedef Fract *FractPtr;
#ifdef mc68881
struct extended80 {
 short w[5];
};
typedef struct extended80 extended80;
#else
typedef extended extended80;
#endif

enum {false,true};
typedef unsigned char Boolean;

enum {v,h};
typedef unsigned char VHSelect;

typedef long (*ProcPtr)();
typedef ProcPtr *ProcHandle;

typedef unsigned char Str255[256],Str63[64],Str32[33],Str31[32],Str27[28],Str15[16],*StringPtr,**StringHandle;

#ifdef __cplusplus
inline unsigned char &Length(StringPtr string) { return (*string); }
#else
#define Length(string) (*(unsigned char *)(string))
#endif

typedef const unsigned char *ConstStr255Param;
typedef ConstStr255Param ConstStr63Param,ConstStr32Param,ConstStr31Param,
 ConstStr27Param,ConstStr15Param;

typedef short OSErr;	/* error code */
typedef unsigned long OSType;
typedef OSType *OSTypePtr;
typedef unsigned long ResType;
typedef ResType *ResTypePtr;
typedef unsigned char Style;
typedef short ScriptCode;
typedef short LangCode;


struct Point {
 short v;
 short h;
};

typedef struct Point Point;
typedef Point *PointPtr;

struct Rect {
 short top;
 short left;
 short bottom;
 short right;
};

typedef struct Rect Rect;
typedef Rect *RectPtr;

enum {
 normal = 0,
 bold = 1,
 italic = 2,
 underline = 4,
 outline = 8,
 shadow = 0x10,
 condense = 0x20,
 extend = 0x40
};

/* Numeric version part of 'vers' resource */
struct NumVersion {
 unsigned char majorRev;			/*1st part of version number in BCD*/
 unsigned char minorAndBugRev;		/*2nd & 3rd part of version number share a byte*/
 unsigned char stage;				/*stage code: dev, alpha, beta, final*/
 unsigned char nonRelRev;			/*revision level of non-released version*/
};

typedef struct NumVersion NumVersion;

/* 'vers' resource format */
struct VersRec {
 NumVersion numericVersion;			/*encoded version number*/
 short countryCode;					/*country code from intl utilities*/
 Str255 shortVersion;				/*version number string - worst case*/
 Str255 reserved;					/*longMessage string packed after shortVersion*/
};

typedef struct VersRec VersRec;
typedef VersRec *VersRecPtr, **VersRecHndl;

#ifdef __cplusplus
extern "C" {
#endif

pascal void Debugger(void)
 = 0xA9FF;
pascal void DebugStr(ConstStr255Param aStr)
 = 0xABFF;
pascal void Debugger68k(void)
 = 0xA9FF;
pascal void DebugStr68k(ConstStr255Param aStr)
 = 0xABFF;

void debugstr(char *aStr);
pascal void SysBreak(void)
 = {0x303C, 0xFE16, 0xA9C9};
pascal void SysBreakStr(ConstStr255Param debugStr)
 = {0x303C, 0xFE15, 0xA9C9};
pascal void SysBreakFunc(ConstStr255Param debugFunc)
 = {0x303C, 0xFE14, 0xA9C9};
#ifdef __cplusplus
}
#endif

#endif
