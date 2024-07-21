/************************************************************

Created: Saturday, July 27, 1991 at 7:22 PM
 ToolUtils.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1992
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		<14>	11/13/92	JDR		Sorry, that last check in should have been "Fixed GetIndPattern
									to use Pattern * like I knew it should."  Reflects changes made
									necessary for getting rid of the dangerous pattern from
									QuickDraw.h.
		<13>	11/13/92	JDR		Fixed GetIndPattern to use ConstPatternParam like I knew it
									should.
		<12>	10/16/92	JDR		Int64Bit.loLong is an unsigned long.
		<11>	 3/12/92	DCL		For New Inside Mac Text volume: Moved GetString, Munger,
									SetString, NewString, GetIndString to the new file:
									TextUtils.[ph]
		<10>	 7/31/91	JL		Updated Copyright.
		 <9>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <7>	11/14/90	JL		Put formal parameter names back.
		 <6>	 11/4/90	dba		got rid of some extraneous parameter names; made some parameters
									void* instead of Ptr; added more use of const in parameters;
									used constStr255Parameter
		 <5>	10/24/90	JL		Changed all #defines to anonymous enums.
		 <4>	10/9/90		JAL	Added inline for ScreenRes
		 <3>	03/02/90	JAL	Changed GetIndPattern(Pattern *thePat
									to GetIndPattern(Pattern thePat
************************************************************/


#ifndef __TOOLUTILS__
#define __TOOLUTILS__

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif

#ifndef __TEXTUTILS__
#include <TextUtils.h>
#endif

enum {

 sysPatListID = 0,
 iBeamCursor = 1,
 crossCursor = 2,
 plusCursor = 3,
 watchCursor = 4
};

struct Int64Bit {
 long hiLong;
 unsigned long loLong;
};

typedef struct Int64Bit Int64Bit;


#ifdef __cplusplus
extern "C" {
#endif
pascal Fixed FixRatio(short numer,short denom)
 = 0xA869; 
pascal Fixed FixMul(Fixed a,Fixed b)
 = 0xA868; 
pascal short FixRound(Fixed x)
 = 0xA86C; 
pascal void PackBits(Ptr *srcPtr,Ptr *dstPtr,short srcBytes)
 = 0xA8CF; 
pascal void UnpackBits(Ptr *srcPtr,Ptr *dstPtr,short dstBytes)
 = 0xA8D0; 
pascal Boolean BitTst(const void *bytePtr,long bitNum)
 = 0xA85D; 
pascal void BitSet(void *bytePtr,long bitNum)
 = 0xA85E; 
pascal void BitClr(void *bytePtr,long bitNum)
 = 0xA85F; 
pascal long BitAnd(long value1,long value2)
 = 0xA858; 
pascal long BitOr(long value1,long value2)
 = 0xA85B; 
pascal long BitXor(long value1,long value2)
 = 0xA859; 
pascal long BitNot(long value)
 = 0xA85A; 
pascal long BitShift(long value,short count)
 = 0xA85C; 
pascal short HiWord(long x)
 = 0xA86A; 
pascal short LoWord(long x)
 = 0xA86B; 
pascal void LongMul(long a,long b,Int64Bit *result)
 = 0xA867; 
pascal Handle GetIcon(short iconID)
 = 0xA9BB; 
pascal void PlotIcon(const Rect *theRect,Handle theIcon)
 = 0xA94B; 
pascal PatHandle GetPattern(short patternID)
 = 0xA9B8; 
pascal CursHandle GetCursor(short cursorID)
 = 0xA9B9; 
pascal PicHandle GetPicture(short pictureID)
 = 0xA9BC; 
pascal Fixed SlopeFromAngle(short angle)
 = 0xA8BC; 
pascal short AngleFromSlope(Fixed slope)
 = 0xA8C4; 
pascal long DeltaPoint(Point ptA,Point ptB)
 = 0xA94F; 
pascal void ShieldCursor(const Rect *shieldRect,Point offsetPt)
 = 0xA855; 
pascal void ScreenRes(short *scrnHRes,short *scrnVRes)
 = {0x225F,0x32B8,0x0102,0x225F,0x32B8,0x0104}; 
pascal void GetIndPattern(Pattern *thePat,short patternListID,short index); 
void shieldcursor(const Rect *shieldRect,Point *offsetPt); 
long deltapoint(Point *ptA,Point *ptB); 
#ifdef __cplusplus
}
#endif

#endif
