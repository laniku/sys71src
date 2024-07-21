/* Lists.c
 *
 *	This form of glue requires linking to Interface.o, which seems
 *	goofy because we have glue jumping to glue. Someday it should
 *	be rewritten to go right to the correct trap.
 *
 *	Modifications:
 *		18 Jan 88	KLH	lclick & lnew need explicit return statement for new c.
 *		11 Feb 88	KLH	Changed C headers to work with new C compiler:
 *						Changed to using standard glue in Interface.o, so
 *						much glue removed from CInterface.o.
 *						List manager changes include sending all mixed case
 *						calls to ROM or Interface.o. For calls passing Cells
 *						by reference (as they had been) we added the following
 *						calls:
 *									laddtocell
 *									lclrcell
 *									ldraw
 *									lfind
 *									lgetcell
 *									lnew
 *									lrect
 *									lsetcell
 *									lsetselect
 *	*** MPW 3.0d4 ***
 */


#include <types.h>
#include <quickdraw.h>
#include <windows.h>
#include <lists.h>

void laddtocell(dataPtr, dataLen, theCell, lHandle)
 Ptr dataPtr;
 short dataLen;
 Cell *theCell;
 ListHandle lHandle;
{
	LAddToCell(dataPtr, dataLen, *theCell, lHandle);
}

void lcellsize(cSize, lHandle)
 Point *cSize;
 ListHandle lHandle;
{
	LCellSize(*cSize, lHandle);
}

Boolean lclick(pt, modifiers, lHandle)
 Point *pt;
 short modifiers;
 ListHandle lHandle;
{
	return LClick(*pt, modifiers, lHandle);
}

void lclrcell(theCell, lHandle)
 Cell *theCell;
 ListHandle lHandle;
{
 	LClrCell(*theCell, lHandle);
}

void ldraw(theCell, lHandle)
 Cell *theCell;
 ListHandle lHandle;
{
	LDraw(*theCell, lHandle);
}

void lfind( offset, len, theCell, lHandle)
 short *len, *offset;
 Cell *theCell;
 ListHandle lHandle;
{
	LFind( offset, len, *theCell, lHandle);
}

void lgetcell(dataPtr,  dataLen, theCell, lHandle)
 Ptr dataPtr;
 short *dataLen;
 Cell *theCell;
 ListHandle lHandle;
{
	LGetCell(dataPtr,  dataLen, *theCell, lHandle);
}

ListHandle  lnew(rView, dataBounds, cSize, theProc, theWindow, drawIt, HasGrow, ScrollHoriz, ScrollVert)
 Rect *rView, *dataBounds;
 Point *cSize;
 short theProc;
 WindowPtr theWindow;
 Boolean drawIt;
 Boolean HasGrow;
 Boolean ScrollHoriz;
 Boolean ScrollVert;
{
	return LNew(rView, dataBounds, *cSize, theProc, theWindow, drawIt, HasGrow, ScrollHoriz, ScrollVert);
}

void lrect( cellRect, theCell, lHandle)
 Rect *cellRect;
 Cell *theCell;
 ListHandle lHandle;
{
	LRect( cellRect, *theCell, lHandle);
}

void lsetcell(dataPtr, dataLen, theCell, lHandle)
 Ptr dataPtr;
 short dataLen;
 Cell *theCell;
 ListHandle lHandle;
{
	LSetCell(dataPtr, dataLen, *theCell, lHandle);
}

void lsetselect(setIt, theCell, lHandle)
 Boolean setIt;
 Cell *theCell;
 ListHandle lHandle;
{
	LSetSelect(setIt, *theCell, lHandle);
}
