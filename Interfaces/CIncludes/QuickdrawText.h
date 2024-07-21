/*
	File:		QuickdrawText.h

	Contains:	C Interface to the Macintosh Libraries

	Written by:	Don Louv

	Copyright:	© 1983-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <4>	  8/4/92	DCL		Changed the textLen parameter to textLength in the prototypes
									for PortionText, VisibleLength, PixelToChar & CharToPixel.
		 <3>	 6/11/92	DCL		Cleanup minor formatting to match Interface Stacks. Happy Happy
									Joy Joy.
		 <2>	 5/29/92	DCL		Moved StdText from QuickDraw to QuickDrawText and fixed up some
									comments.
		 <1>	  5/5/92	DCL		first checked in

*/

#ifndef __QUICKDRAWTEXT__
#define __QUICKDRAWTEXT__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __INTLRESOURCES__
#include <IntlResources.h>
#endif


enum{
/* CharToPixel directions */
 leftCaret = 0,						/*Place caret for left block*/
 rightCaret = -1,					/*Place caret for right block*/
 hilite = 1,						/*Direction is SysDirection*/

 smLeftCaret = 0,					/*Place caret for left block          obsolete */
 smRightCaret = -1,					/*Place caret for right block      obsolete */
 smHilite = 1,						/*Direction is TESysJust              obsolete */

/*Constants for styleRunPosition argument in PortionLine, DrawJustified,
 MeasureJustified, CharToPixel, and PixelToChar.*/
 onlyStyleRun = 0,				/* This is the only style run on the line */
 leftStyleRun = 1,				/* This is leftmost of multiple style runs on the line */
 rightStyleRun = 2,				/* This is rightmost of multiple style runs on the line */
 middleStyleRun = 3,				/* There are multiple style runs on the line and this 
 is neither the leftmost nor the rightmost. */
 smOnlyStyleRun = 0,				/*      obsolete */
 smLeftStyleRun = 1,				/*      obsolete */
 smRightStyleRun = 2,			/*      obsolete */
 smMiddleStyleRun = 3			/*      obsolete */
};

/* type for styleRunPosition parameter in PixelToChar etc. */
typedef short JustStyleCode;

struct FontInfo {
 short ascent;
 short descent;
 short widMax;
 short leading;
};

typedef struct FontInfo FontInfo;

typedef short FormatOrder[1];
typedef FormatOrder *FormatOrderPtr;
typedef short FormatStatus;

#ifdef __cplusplus
extern "C" {
#endif
pascal short Pixel2Char(Ptr textBuf,short textLen,short slop,short pixelWidth,
 Boolean *leadingEdge)
 = {0x2F3C,0x820E,0x0014,0xA8B5}; 
pascal short Char2Pixel(Ptr textBuf,short textLen,short slop,short offset,
 short direction)
 = {0x2F3C,0x820C,0x0016,0xA8B5}; 
 
pascal short PixelToChar(Ptr textBuf,long textLength,Fixed slop,Fixed pixelWidth,
 Boolean *leadingEdge,Fixed *widthRemaining,JustStyleCode styleRunPosition,
 Point numer,Point denom)
 = {0x2F3C,0x8222,0x002E,0xA8B5}; 
pascal short NPixel2Char(Ptr textBuf,long textLen,Fixed slop,Fixed pixelWidth,
 Boolean *leadingEdge,Fixed *widthRemaining,JustStyleCode styleRunPosition,
 Point numer,Point denom)
 = {0x2F3C,0x8222,0x002E,0xA8B5}; 
pascal short CharToPixel(Ptr textBuf,long textLength,Fixed slop,long offset,
 short direction,JustStyleCode styleRunPosition,Point numer,Point denom)
 = {0x2F3C,0x821C,0x0030,0xA8B5}; 
pascal short NChar2Pixel(Ptr textBuf,long textLen,Fixed slop,long offset,
 short direction,JustStyleCode styleRunPosition,Point numer,Point denom)
 = {0x2F3C,0x821C,0x0030,0xA8B5}; 
pascal void DrawJustified(Ptr textPtr,long textLength,Fixed slop,JustStyleCode styleRunPosition,
 Point numer,Point denom)
 = {0x2F3C,0x8016,0x0032,0xA8B5}; 
pascal void NDrawJust(Ptr textPtr,long textLength,Fixed slop,JustStyleCode styleRunPosition,
 Point numer,Point denom)
 = {0x2F3C,0x8016,0x0032,0xA8B5}; 
pascal void MeasureJustified(Ptr textPtr,long textLength,Fixed slop,Ptr charLocs,
 JustStyleCode styleRunPosition,Point numer,Point denom)
 = {0x2F3C,0x801A,0x0034,0xA8B5}; 
pascal void NMeasureJust(Ptr textPtr,long textLength,Fixed slop,Ptr charLocs,
 JustStyleCode styleRunPosition,Point numer,Point denom)
 = {0x2F3C,0x801A,0x0034,0xA8B5}; 
pascal Fixed PortionLine(Ptr textPtr,long textLen,JustStyleCode styleRunPosition,
 Point numer,Point denom)
 = {0x2F3C,0x8412,0x0036,0xA8B5}; 
pascal Fixed NPortionText(Ptr textPtr,long textLen,JustStyleCode styleRunPosition,
 Point numer,Point denom)
 = {0x2F3C,0x8412,0x0036,0xA8B5}; 

pascal void HiliteText(Ptr textPtr,short textLength,short firstOffset,short secondOffset,
 OffsetTable offsets)
 = {0x2F3C,0x800E,0x001C,0xA8B5}; 
pascal void DrawJust(Ptr textPtr,short textLength,short slop)
 = {0x2F3C,0x8008,0x001E,0xA8B5}; 
pascal void MeasureJust(Ptr textPtr,short textLength,short slop,Ptr charLocs)
 = {0x2F3C,0x800C,0x0020,0xA8B5}; 

pascal Fixed PortionText(Ptr textPtr,long textLength)
 = {0x2F3C,0x8408,0x0024,0xA8B5}; 
pascal long VisibleLength(Ptr textPtr,long textLength)
 = {0x2F3C,0x8408,0x0028,0xA8B5}; 
pascal void GetFormatOrder(FormatOrderPtr ordering,short firstFormat,short lastFormat,
 Boolean lineRight,Ptr rlDirProc,Ptr dirParam)
 = {0x2F3C,0x8012,0xFFFC,0xA8B5}; 


pascal void TextFont(short font)
 = 0xA887; 
pascal void TextFace(short face)
 = 0xA888; 
pascal void TextMode(short mode)
 = 0xA889; 
pascal void TextSize(short size)
 = 0xA88A; 
pascal void SpaceExtra(Fixed extra)
 = 0xA88E; 
pascal void DrawChar(short ch)
 = 0xA883; 
pascal void DrawString(ConstStr255Param s)
 = 0xA884; 
pascal void DrawText(const void *textBuf,short firstByte,short byteCount)
 = 0xA885; 
pascal short CharWidth(short ch)
 = 0xA88D; 
pascal short StringWidth(ConstStr255Param s)
 = 0xA88C; 
pascal short TextWidth(const void *textBuf,short firstByte,short byteCount)
 = 0xA886; 
pascal void MeasureText(short count,const void *textAddr,void *charLocs)
 = 0xA837; 
pascal void GetFontInfo(FontInfo *info)
 = 0xA88B; 
pascal void CharExtra(Fixed extra)
 = 0xAA23; 

pascal void StdText(short count,const void *textAddr,Point numer,Point denom)
 = 0xA882; 
void stdtext(short count,const void *textAddr,Point *numer,Point *denom); 
pascal short StdTxMeas(short byteCount,const void *textAddr,Point *numer,
 Point *denom,FontInfo *info)
 = 0xA8ED; 



#ifdef __cplusplus
}
#endif

#endif
