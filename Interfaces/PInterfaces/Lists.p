
{
Created: Saturday, July 27, 1991 at 9:39 PM
 Lists.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <4>	 7/30/91	JL		Updated Copyright.
		 <3>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <2>	 11/4/90	dba		shorten the inline for LActivate
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Lists;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingLists}
{$SETC UsingLists := 1}

{$I+}
{$SETC ListsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingControls}
{$I $$Shell(PInterfaces)Controls.p}
{$ENDC}
{$IFC UNDEFINED UsingMemory}
{$I $$Shell(PInterfaces)Memory.p}
{$ENDC}
{$SETC UsingIncludes := ListsIncludes}

CONST
lDoVAutoscroll = 2;
lDoHAutoscroll = 1;
lOnlyOne = -128;
lExtendDrag = 64;
lNoDisjoint = 32;
lNoExtend = 16;
lNoRect = 8;
lUseSense = 4;
lNoNilHilite = 2;
lInitMsg = 0;
lDrawMsg = 1;
lHiliteMsg = 2;
lCloseMsg = 3;

TYPE
Cell = Point;

DataPtr = ^DataArray;
DataHandle = ^DataPtr;

DataArray = PACKED ARRAY [0..32000] OF CHAR;

ListPtr = ^ListRec;
ListHandle = ^ListPtr;
ListRec = RECORD
 rView: Rect;
 port: GrafPtr;
 indent: Point;
 cellSize: Point;
 visible: Rect;
 vScroll: ControlHandle;
 hScroll: ControlHandle;
 selFlags: SignedByte;
 lActive: BOOLEAN;
 lReserved: SignedByte;
 listFlags: SignedByte;
 clikTime: LONGINT;
 clikLoc: Point;
 mouseLoc: Point;
 lClikLoop: ProcPtr;
 lastClick: Cell;
 refCon: LONGINT;
 listDefProc: Handle;
 userHandle: Handle;
 dataBounds: Rect;
 cells: DataHandle;
 maxIndex: INTEGER;
 cellArray: ARRAY [1..1] OF INTEGER;
 END;


FUNCTION LNew(rView: Rect;dataBounds: Rect;cSize: Point;theProc: INTEGER;
 theWindow: WindowPtr;drawIt: BOOLEAN;hasGrow: BOOLEAN;scrollHoriz: BOOLEAN;
 scrollVert: BOOLEAN): ListHandle;
 INLINE $3F3C,$0044,$A9E7;
PROCEDURE LDispose(lHandle: ListHandle);
 INLINE $3F3C,$0028,$A9E7;
FUNCTION LAddColumn(count: INTEGER;colNum: INTEGER;lHandle: ListHandle): INTEGER;
 INLINE $3F3C,$0004,$A9E7;
FUNCTION LAddRow(count: INTEGER;rowNum: INTEGER;lHandle: ListHandle): INTEGER;
 INLINE $3F3C,$0008,$A9E7;
PROCEDURE LDelColumn(count: INTEGER;colNum: INTEGER;lHandle: ListHandle);
 INLINE $3F3C,$0020,$A9E7;
PROCEDURE LDelRow(count: INTEGER;rowNum: INTEGER;lHandle: ListHandle);
 INLINE $3F3C,$0024,$A9E7;
FUNCTION LGetSelect(next: BOOLEAN;VAR theCell: Cell;lHandle: ListHandle): BOOLEAN;
 INLINE $3F3C,$003C,$A9E7;
FUNCTION LLastClick(lHandle: ListHandle): Cell;
 INLINE $3F3C,$0040,$A9E7;
FUNCTION LNextCell(hNext: BOOLEAN;vNext: BOOLEAN;VAR theCell: Cell;lHandle: ListHandle): BOOLEAN;
 INLINE $3F3C,$0048,$A9E7;
FUNCTION LSearch(dataPtr: Ptr;dataLen: INTEGER;searchProc: ProcPtr;VAR theCell: Cell;
 lHandle: ListHandle): BOOLEAN;
 INLINE $3F3C,$0054,$A9E7;
PROCEDURE LSize(listWidth: INTEGER;listHeight: INTEGER;lHandle: ListHandle);
 INLINE $3F3C,$0060,$A9E7;
PROCEDURE LDoDraw(drawIt: BOOLEAN;lHandle: ListHandle);
 INLINE $3F3C,$002C,$A9E7;
PROCEDURE LScroll(dCols: INTEGER;dRows: INTEGER;lHandle: ListHandle);
 INLINE $3F3C,$0050,$A9E7;
PROCEDURE LAutoScroll(lHandle: ListHandle);
 INLINE $3F3C,$0010,$A9E7;
PROCEDURE LUpdate(theRgn: RgnHandle;lHandle: ListHandle);
 INLINE $3F3C,$0064,$A9E7;
PROCEDURE LActivate(act: BOOLEAN;lHandle: ListHandle);
 INLINE $4267,$A9E7;
PROCEDURE LCellSize(cSize: Point;lHandle: ListHandle);
 INLINE $3F3C,$0014,$A9E7;
FUNCTION LClick(pt: Point;modifiers: INTEGER;lHandle: ListHandle): BOOLEAN;
 INLINE $3F3C,$0018,$A9E7;
PROCEDURE LAddToCell(dataPtr: Ptr;dataLen: INTEGER;theCell: Cell;lHandle: ListHandle);
 INLINE $3F3C,$000C,$A9E7;
PROCEDURE LClrCell(theCell: Cell;lHandle: ListHandle);
 INLINE $3F3C,$001C,$A9E7;
PROCEDURE LGetCell(dataPtr: Ptr;VAR dataLen: INTEGER;theCell: Cell;lHandle: ListHandle);
 INLINE $3F3C,$0038,$A9E7;
PROCEDURE LFind(VAR offset: INTEGER;VAR len: INTEGER;theCell: Cell;lHandle: ListHandle);
 INLINE $3F3C,$0034,$A9E7;
PROCEDURE LRect(VAR cellRect: Rect;theCell: Cell;lHandle: ListHandle);
 INLINE $3F3C,$004C,$A9E7;
PROCEDURE LSetCell(dataPtr: Ptr;dataLen: INTEGER;theCell: Cell;lHandle: ListHandle);
 INLINE $3F3C,$0058,$A9E7;
PROCEDURE LSetSelect(setIt: BOOLEAN;theCell: Cell;lHandle: ListHandle);
 INLINE $3F3C,$005C,$A9E7;
PROCEDURE LDraw(theCell: Cell;lHandle: ListHandle);
 INLINE $3F3C,$0030,$A9E7;


{$ENDC} { UsingLists }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

