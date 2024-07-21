
/************************************************************

Created: Saturday, July 27, 1991 at 4:25 PM
 Lists.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <7>	 7/30/91	JL		Updated Copyright.
		 <6>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <5>	11/28/90	JL		Put formal parameter names back.
		 <4>	 11/7/90	JL		Changed all #defines to anonymous enums
		 <3>	 11/4/90	dba		got rid of some extraneous parameter names; made some parameters
									void* instead of Ptr; added more use of const in parameters

************************************************************/


#ifndef __LISTS__
#define __LISTS__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __CONTROLS__
#include <Controls.h>
#endif

#ifndef __MEMORY__
#include <Memory.h>
#endif


enum {

 lDoVAutoscroll = 2,
 lDoHAutoscroll = 1,
 lOnlyOne = -128,
 lExtendDrag = 64,
 lNoDisjoint = 32,
 lNoExtend = 16,
 lNoRect = 8,
 lUseSense = 4,
 lNoNilHilite = 2,
 lInitMsg = 0,
 lDrawMsg = 1,
 lHiliteMsg = 2,
 lCloseMsg = 3
};

typedef Point Cell;

typedef char DataArray[32001],*DataPtr,**DataHandle;
typedef pascal short (*SearchProcPtr)(Ptr aPtr, Ptr bPtr, short aLen, short bLen);

struct ListRec {
 Rect rView;
 GrafPtr port;
 Point indent;
 Point cellSize;
 Rect visible;
 ControlHandle vScroll;
 ControlHandle hScroll;
 char selFlags;
 Boolean lActive;
 char lReserved;
 char listFlags;
 long clikTime;
 Point clikLoc;
 Point mouseLoc;
 ProcPtr lClikLoop;
 Cell lastClick;
 long refCon;
 Handle listDefProc;
 Handle userHandle;
 Rect dataBounds;
 DataHandle cells;
 short maxIndex;
 short cellArray[1];
};

typedef struct ListRec ListRec;
typedef ListRec *ListPtr, **ListHandle;


#ifdef __cplusplus
extern "C" {
#endif
ListHandle lnew(Rect *rView,Rect *dataBounds,Point *cSize,short theProc,
 WindowPtr theWindow,Boolean drawIt,Boolean hasGrow,Boolean scrollHoriz,
 Boolean scrollVert); 
pascal ListHandle LNew(const Rect *rView,const Rect *dataBounds,Point cSize,
 short theProc,WindowPtr theWindow,Boolean drawIt,Boolean hasGrow,Boolean scrollHoriz,
 Boolean scrollVert)
 = {0x3F3C,0x0044,0xA9E7}; 
pascal void LDispose(ListHandle lHandle)
 = {0x3F3C,0x0028,0xA9E7}; 
pascal short LAddColumn(short count,short colNum,ListHandle lHandle)
 = {0x3F3C,0x0004,0xA9E7}; 
pascal short LAddRow(short count,short rowNum,ListHandle lHandle)
 = {0x3F3C,0x0008,0xA9E7}; 
pascal void LDelColumn(short count,short colNum,ListHandle lHandle)
 = {0x3F3C,0x0020,0xA9E7}; 
pascal void LDelRow(short count,short rowNum,ListHandle lHandle)
 = {0x3F3C,0x0024,0xA9E7}; 
pascal Boolean LGetSelect(Boolean next,Cell *theCell,ListHandle lHandle)
 = {0x3F3C,0x003C,0xA9E7}; 
pascal Cell LLastClick(ListHandle lHandle)
 = {0x3F3C,0x0040,0xA9E7}; 
pascal Boolean LNextCell(Boolean hNext,Boolean vNext,Cell *theCell,ListHandle lHandle)
 = {0x3F3C,0x0048,0xA9E7}; 
pascal Boolean LSearch(const void *dataPtr,short dataLen,SearchProcPtr searchProc,
 Cell *theCell,ListHandle lHandle)
 = {0x3F3C,0x0054,0xA9E7}; 
pascal void LSize(short listWidth,short listHeight,ListHandle lHandle)
 = {0x3F3C,0x0060,0xA9E7}; 
pascal void LDoDraw(Boolean drawIt,ListHandle lHandle)
 = {0x3F3C,0x002C,0xA9E7}; 
pascal void LScroll(short dCols,short dRows,ListHandle lHandle)
 = {0x3F3C,0x0050,0xA9E7}; 
pascal void LAutoScroll(ListHandle lHandle)
 = {0x3F3C,0x0010,0xA9E7}; 
pascal void LUpdate(RgnHandle theRgn,ListHandle lHandle)
 = {0x3F3C,0x0064,0xA9E7}; 
pascal void LActivate(Boolean act,ListHandle lHandle)
 = {0x4267,0xA9E7}; 
pascal void LCellSize(Point cSize,ListHandle lHandle)
 = {0x3F3C,0x0014,0xA9E7}; 
pascal Boolean LClick(Point pt,short modifiers,ListHandle lHandle)
 = {0x3F3C,0x0018,0xA9E7}; 
pascal void LAddToCell(const void *dataPtr,short dataLen,Cell theCell,ListHandle lHandle)
 = {0x3F3C,0x000C,0xA9E7}; 
pascal void LClrCell(Cell theCell,ListHandle lHandle)
 = {0x3F3C,0x001C,0xA9E7}; 
pascal void LGetCell(void *dataPtr,short *dataLen,Cell theCell,ListHandle lHandle)
 = {0x3F3C,0x0038,0xA9E7}; 
pascal void LFind(short *offset,short *len,Cell theCell,ListHandle lHandle)
 = {0x3F3C,0x0034,0xA9E7}; 
pascal void LRect(Rect *cellRect,Cell theCell,ListHandle lHandle)
 = {0x3F3C,0x004C,0xA9E7}; 
pascal void LSetCell(const void *dataPtr,short dataLen,Cell theCell,ListHandle lHandle)
 = {0x3F3C,0x0058,0xA9E7}; 
pascal void LSetSelect(Boolean setIt,Cell theCell,ListHandle lHandle)
 = {0x3F3C,0x005C,0xA9E7}; 
pascal void LDraw(Cell theCell,ListHandle lHandle)
 = {0x3F3C,0x0030,0xA9E7}; 
void ldraw(Cell *theCell,ListHandle lHandle); 
Boolean lclick(Point *pt,short modifiers,ListHandle lHandle); 
void lcellsize(Point *cSize,ListHandle lHandle); 
#ifdef __cplusplus
}
#endif

#endif
