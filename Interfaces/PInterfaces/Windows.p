
{
Created: Sunday, July 28, 1991 at 12:25 AM
 Windows.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1992
  All rights reserved.


	Change History (most recent first):

		 <8>	 7/28/92	DCL		Moving applicationFloatKind & systemFloatKind constants out of
									the public eye and into the private Layers header file. At the
									request of TechPubs, and with assistance from Dean, Greg and
									Kenny.
		 <7>	 7/13/92	DCL		Changed prototype of DragGrayRgn boundsRect to limitRect to
									match Inside Mac. (as requested by NIIM writers)
		 <6>	 6/26/92	DCL		<KST>: Adding to new Window kinds for floating windows. ...and
									Miner Formatting Changes. Digging deep for things to do.
		 <5>	 7/31/91	JL		Updated Copyright.
		 <4>	 1/27/91	LN		Checked in Database generate file from DSG. Removed some Inside
									Mac comments.
		 <3>	10/18/90	VL		(jsm) Added new variant for movable modal dialog (5).

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Windows;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingWindows}
{$SETC UsingWindows := 1}

{$I+}
{$SETC WindowsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingQuickdraw}
{$I $$Shell(PInterfaces)Quickdraw.p}
{$ENDC}
{$IFC UNDEFINED UsingEvents}
{$I $$Shell(PInterfaces)Events.p}
{$ENDC}
{$IFC UNDEFINED UsingControls}
{$I $$Shell(PInterfaces)Controls.p}
{$ENDC}
{$SETC UsingIncludes := WindowsIncludes}

CONST
documentProc = 0;
dBoxProc = 1;
plainDBox = 2;
altDBoxProc = 3;
noGrowDocProc = 4;
movableDBoxProc = 5;
zoomDocProc = 8;
zoomNoGrow = 12;
rDocProc = 16;
dialogKind = 2;
userKind = 8;

{FindWindow Result Codes}
inDesk = 0;
inMenuBar = 1;
inSysWindow = 2;
inContent = 3;
inDrag = 4;
inGrow = 5;
inGoAway = 6;
inZoomIn = 7;
inZoomOut = 8;

{window messages}
wDraw = 0;
wHit = 1;
wCalcRgns = 2;
wNew = 3;
wDispose = 4;
wGrow = 5;
wDrawGIcon = 6;

{defProc hit test codes}
wNoHit = 0;
wInContent = 1;
wInDrag = 2;
wInGrow = 3;
wInGoAway = 4;
wInZoomIn = 5;
wInZoomOut = 6;
deskPatID = 16;

{Window Part Identifiers which correlate color table entries with window elements}
wContentColor = 0;
wFrameColor = 1;
wTextColor = 2;
wHiliteColor = 3;
wTitleBarColor = 4;

TYPE
WindowPeek = ^WindowRecord;
WindowRecord = RECORD
 port: GrafPort;
 windowKind: INTEGER;
 visible: BOOLEAN;
 hilited: BOOLEAN;
 goAwayFlag: BOOLEAN;
 spareFlag: BOOLEAN;
 strucRgn: RgnHandle;
 contRgn: RgnHandle;
 updateRgn: RgnHandle;
 windowDefProc: Handle;
 dataHandle: Handle;
 titleHandle: StringHandle;
 titleWidth: INTEGER;
 controlList: ControlHandle;
 nextWindow: WindowPeek;
 windowPic: PicHandle;
 refCon: LONGINT;
 END;

CWindowPeek = ^CWindowRecord;
CWindowRecord = RECORD
 port: CGrafPort;
 windowKind: INTEGER;
 visible: BOOLEAN;
 hilited: BOOLEAN;
 goAwayFlag: BOOLEAN;
 spareFlag: BOOLEAN;
 strucRgn: RgnHandle;
 contRgn: RgnHandle;
 updateRgn: RgnHandle;
 windowDefProc: Handle;
 dataHandle: Handle;
 titleHandle: StringHandle;
 titleWidth: INTEGER;
 controlList: ControlHandle;
 nextWindow: CWindowPeek;
 windowPic: PicHandle;
 refCon: LONGINT;
 END;

WStateDataPtr = ^WStateData;
WStateDataHandle = ^WStateDataPtr;
WStateData = RECORD
 userState: Rect;			{user state}
 stdState: Rect;			{standard state}
 END;

AuxWinPtr = ^AuxWinRec;
AuxWinHandle = ^AuxWinPtr;
AuxWinRec = RECORD
 awNext: AuxWinHandle;		{handle to next AuxWinRec}
 awOwner: WindowPtr;		{ptr to window }
 awCTable: CTabHandle;		{color table for this window}
 dialogCItem: Handle;		{handle to dialog manager structures}
 awFlags: LONGINT;			{reserved for expansion}
 awReserved: CTabHandle;	{reserved for expansion}
 awRefCon: LONGINT;			{user Constant}
 END;

WCTabPtr = ^WinCTab;
WCTabHandle = ^WCTabPtr;
WinCTab = RECORD
 wCSeed: LONGINT;			{reserved}
 wCReserved: INTEGER;		{reserved}
 ctSize: INTEGER;			{usually 4 for windows}
 ctTable: ARRAY [0..4] OF ColorSpec;
 END;


PROCEDURE InitWindows;
 INLINE $A912;
PROCEDURE GetWMgrPort(VAR wPort: GrafPtr);
 INLINE $A910;
FUNCTION NewWindow(wStorage: Ptr;boundsRect: Rect;title: Str255;visible: BOOLEAN;
 theProc: INTEGER;behind: WindowPtr;goAwayFlag: BOOLEAN;refCon: LONGINT): WindowPtr;
 INLINE $A913;
FUNCTION GetNewWindow(windowID: INTEGER;wStorage: Ptr;behind: WindowPtr): WindowPtr;
 INLINE $A9BD;
PROCEDURE CloseWindow(theWindow: WindowPtr);
 INLINE $A92D;
PROCEDURE DisposeWindow(theWindow: WindowPtr);
 INLINE $A914;
PROCEDURE GetWTitle(theWindow: WindowPtr;VAR title: Str255);
 INLINE $A919;
PROCEDURE SelectWindow(theWindow: WindowPtr);
 INLINE $A91F;
PROCEDURE HideWindow(theWindow: WindowPtr);
 INLINE $A916;
PROCEDURE ShowWindow(theWindow: WindowPtr);
 INLINE $A915;
PROCEDURE ShowHide(theWindow: WindowPtr;showFlag: BOOLEAN);
 INLINE $A908;
PROCEDURE HiliteWindow(theWindow: WindowPtr;fHilite: BOOLEAN);
 INLINE $A91C;
PROCEDURE BringToFront(theWindow: WindowPtr);
 INLINE $A920;
PROCEDURE SendBehind(theWindow: WindowPtr;behindWindow: WindowPtr);
 INLINE $A921;
FUNCTION FrontWindow: WindowPtr;
 INLINE $A924;
PROCEDURE DrawGrowIcon(theWindow: WindowPtr);
 INLINE $A904;
PROCEDURE MoveWindow(theWindow: WindowPtr;hGlobal: INTEGER;vGlobal: INTEGER;
 front: BOOLEAN);
 INLINE $A91B;
PROCEDURE SizeWindow(theWindow: WindowPtr;w: INTEGER;h: INTEGER;fUpdate: BOOLEAN);
 INLINE $A91D;
PROCEDURE ZoomWindow(theWindow: WindowPtr;partCode: INTEGER;front: BOOLEAN);
 INLINE $A83A;
PROCEDURE InvalRect(badRect: Rect);
 INLINE $A928;
PROCEDURE InvalRgn(badRgn: RgnHandle);
 INLINE $A927;
PROCEDURE ValidRect(goodRect: Rect);
 INLINE $A92A;
PROCEDURE ValidRgn(goodRgn: RgnHandle);
 INLINE $A929;
PROCEDURE BeginUpdate(theWindow: WindowPtr);
 INLINE $A922;
PROCEDURE EndUpdate(theWindow: WindowPtr);
 INLINE $A923;
PROCEDURE SetWRefCon(theWindow: WindowPtr;data: LONGINT);
 INLINE $A918;
FUNCTION GetWRefCon(theWindow: WindowPtr): LONGINT;
 INLINE $A917;
PROCEDURE SetWindowPic(theWindow: WindowPtr;pic: PicHandle);
 INLINE $A92E;
FUNCTION GetWindowPic(theWindow: WindowPtr): PicHandle;
 INLINE $A92F;
FUNCTION CheckUpdate(VAR theEvent: EventRecord): BOOLEAN;
 INLINE $A911;
PROCEDURE ClipAbove(window: WindowPeek);
 INLINE $A90B;
PROCEDURE SaveOld(window: WindowPeek);
 INLINE $A90E;
PROCEDURE DrawNew(window: WindowPeek;update: BOOLEAN);
 INLINE $A90F;
PROCEDURE PaintOne(window: WindowPeek;clobberedRgn: RgnHandle);
 INLINE $A90C;
PROCEDURE PaintBehind(startWindow: WindowPeek;clobberedRgn: RgnHandle);
 INLINE $A90D;
PROCEDURE CalcVis(window: WindowPeek);
 INLINE $A909;
PROCEDURE CalcVisBehind(startWindow: WindowPeek;clobberedRgn: RgnHandle);
 INLINE $A90A;
FUNCTION GrowWindow(theWindow: WindowPtr;startPt: Point;bBox: Rect): LONGINT;
 INLINE $A92B;
FUNCTION FindWindow(thePoint: Point;VAR theWindow: WindowPtr): INTEGER;
 INLINE $A92C;
FUNCTION PinRect(theRect: Rect;thePt: Point): LONGINT;
 INLINE $A94E;
FUNCTION DragGrayRgn(theRgn: RgnHandle;startPt: Point;limitRect: Rect;
 slopRect: Rect;axis: INTEGER;actionProc: ProcPtr): LONGINT;
 INLINE $A905;
FUNCTION TrackBox(theWindow: WindowPtr;thePt: Point;partCode: INTEGER): BOOLEAN;
 INLINE $A83B;
PROCEDURE GetCWMgrPort(VAR wMgrCPort: CGrafPtr);
 INLINE $AA48;
PROCEDURE SetWinColor(theWindow: WindowPtr;newColorTable: WCTabHandle);
 INLINE $AA41;
FUNCTION GetAuxWin(theWindow: WindowPtr;VAR awHndl: AuxWinHandle): BOOLEAN;
 INLINE $AA42;
PROCEDURE SetDeskCPat(deskPixPat: PixPatHandle);
 INLINE $AA47;
FUNCTION NewCWindow(wStorage: Ptr;boundsRect: Rect;title: Str255;visible: BOOLEAN;
 procID: INTEGER;behind: WindowPtr;goAwayFlag: BOOLEAN;refCon: LONGINT): WindowPtr;
 INLINE $AA45;
FUNCTION GetNewCWindow(windowID: INTEGER;wStorage: Ptr;behind: WindowPtr): WindowPtr;
 INLINE $AA46;
FUNCTION GetWVariant(theWindow: WindowPtr): INTEGER;
 INLINE $A80A;
FUNCTION GetGrayRgn: RgnHandle;
 INLINE $2EB8,$09EE;
PROCEDURE SetWTitle(theWindow: WindowPtr;title: Str255);
 INLINE $A91A;
FUNCTION TrackGoAway(theWindow: WindowPtr;thePt: Point): BOOLEAN;
 INLINE $A91E;
PROCEDURE DragWindow(theWindow: WindowPtr;startPt: Point;boundsRect: Rect);
 INLINE $A925;


{$ENDC} { UsingWindows }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

