
{
Created: Tuesday, July 30, 1991 at 2:11 PM
 Controls.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1992
  All rights reserved

	Change History (most recent first):

		 <8>	 11/7/92	JDR		Added the PopupPrivateData record.
		 <7>	  4/6/92	DCL		For New Inside Mac: Adding fancy new improved names for old
									crusty routines. #1025005
		 <6>	 7/30/91	JL		Updated Copyright.
		 <5>	1/29/91		jal		<LN> checked in database generated file from DSG.
		 <4>	12/14/90	dba		<JDR> add calc messages for 32-bit clean CDEFs; use
									popupMenuProc name to match Pascal
		 <3>	 11/4/90	dba		add UpdateControls (synonym for UpdtControl)
		 <2>	 9/15/90	PWD		Moved popup constants here from CTBUtilities.p.  <kaz> <crz>
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Controls;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingControls}
{$SETC UsingControls := 1}

{$I+}
{$SETC ControlsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingQuickdraw}
{$I $$Shell(PInterfaces)Quickdraw.p}
{$ENDC}
{$IFC UNDEFINED UsingMenus}
{$I $$Shell(PInterfaces)Menus.p}
{$ENDC}
{$SETC UsingIncludes := ControlsIncludes}

CONST
pushButProc = 0;
checkBoxProc = 1;
radioButProc = 2;
useWFont = 8;
scrollBarProc = 16;
inButton = 10;
inCheckBox = 11;
inUpButton = 20;
inDownButton = 21;
inPageUp = 22;
inPageDown = 23;
inThumb = 129;

popupMenuProc = 1008;				{ 63 * 16 }
popupFixedWidth = $0001;			{ popup menu CDEF variation codes }
popupUseAddResMenu = $0004;
popupUseWFont = $0008;
popupTitleBold = $00000100;			{ Popup Title characteristics }
popupTitleItalic = $00000200;
popupTitleUnderline = $00000400;
popupTitleOutline = $00000800;
popupTitleShadow = $00001000;
popupTitleCondense = $00002000;
popupTitleExtend = $00004000;
popupTitleNoStyle = $00008000;
popupTitleLeftJust = $00000000;
popupTitleCenterJust = $00000001;
popupTitleRightJust = $000000FF;

{
axis constraints for DragGrayRgn call}
noConstraint = 0;
hAxisOnly = 1;
vAxisOnly = 2;

{
control messages}
drawCntl = 0;
testCntl = 1;
calcCRgns = 2;
initCntl = 3;
dispCntl = 4;
posCntl = 5;
thumbCntl = 6;
dragCntl = 7;
autoTrack = 8;
calcCntlRgn = 10;
calcThumbRgn = 11;

cFrameColor = 0;
cBodyColor = 1;
cTextColor = 2;
cThumbColor = 3;
popupMenuCDEFproc = popupMenuProc;	{ synonym for compatibility }

TYPE
ControlPtr = ^ControlRecord;
ControlHandle = ^ControlPtr;
ControlRecord = PACKED RECORD
 nextControl: ControlHandle;
 contrlOwner: WindowPtr;
 contrlRect: Rect;
 contrlVis: Byte;
 contrlHilite: Byte;
 contrlValue: INTEGER;
 contrlMin: INTEGER;
 contrlMax: INTEGER;
 contrlDefProc: Handle;
 contrlData: Handle;
 contrlAction: ProcPtr;
 contrlRfCon: LONGINT;
 contrlTitle: Str255;
 END;

PopupPrivateDataPtr = ^PopupPrivateData;
PopupPrivateDataHandle = ^PopupPrivateDataPtr;
PopupPrivateData = RECORD
 mHandle: MenuHandle;				{popup menu handle}
 mID: INTEGER;						{popup menu ID}
 END;


CCTabPtr = ^CtlCTab;
CCTabHandle = ^CCTabPtr;
CtlCTab = RECORD
 ccSeed: LONGINT;					{reserved}
 ccRider: INTEGER;					{see what you have done - reserved}
 ctSize: INTEGER;					{usually 3 for controls}
 ctTable: ARRAY [0..3] OF ColorSpec;
 END;

AuxCtlPtr = ^AuxCtlRec;
AuxCtlHandle = ^AuxCtlPtr;
AuxCtlRec = RECORD
 acNext: AuxCtlHandle;				{handle to next AuxCtlRec}
 acOwner: ControlHandle;			{handle for aux record's control}
 acCTable: CCTabHandle;				{color table for this control}
 acFlags: INTEGER;					{misc flag byte}
 acReserved: LONGINT;				{reserved for use by Apple}
 acRefCon: LONGINT;					{for use by application}
 END;


FUNCTION NewControl(theWindow: WindowPtr;boundsRect: Rect;title: Str255;
 visible: BOOLEAN;value: INTEGER;min: INTEGER;max: INTEGER;procID: INTEGER;
 refCon: LONGINT): ControlHandle;
 INLINE $A954;
PROCEDURE SetControlTitle(theControl: ControlHandle;title: Str255);
 INLINE $A95F;
PROCEDURE SetCTitle(theControl: ControlHandle;title: Str255);
 INLINE $A95F;
PROCEDURE GetControlTitle(theControl: ControlHandle;VAR title: Str255);
 INLINE $A95E;
PROCEDURE GetCTitle(theControl: ControlHandle;VAR title: Str255);
 INLINE $A95E;
FUNCTION GetNewControl(controlID: INTEGER;owner: WindowPtr): ControlHandle;
 INLINE $A9BE;
PROCEDURE DisposeControl(theControl: ControlHandle);
 INLINE $A955;
PROCEDURE KillControls(theWindow: WindowPtr);
 INLINE $A956;
PROCEDURE HideControl(theControl: ControlHandle);
 INLINE $A958;
PROCEDURE ShowControl(theControl: ControlHandle);
 INLINE $A957;
PROCEDURE DrawControls(theWindow: WindowPtr);
 INLINE $A969;
PROCEDURE Draw1Control(theControl: ControlHandle);
 INLINE $A96D;
PROCEDURE HiliteControl(theControl: ControlHandle;hiliteState: INTEGER);
 INLINE $A95D;
PROCEDURE UpdateControls(theWindow: WindowPtr;updateRgn: RgnHandle);
 INLINE $A953;
PROCEDURE UpdtControl(theWindow: WindowPtr;updateRgn: RgnHandle);
 INLINE $A953;
PROCEDURE MoveControl(theControl: ControlHandle;h: INTEGER;v: INTEGER);
 INLINE $A959;
PROCEDURE SizeControl(theControl: ControlHandle;w: INTEGER;h: INTEGER);
 INLINE $A95C;
PROCEDURE SetControlValue(theControl: ControlHandle;theValue: INTEGER);
 INLINE $A963;
PROCEDURE SetCtlValue(theControl: ControlHandle;theValue: INTEGER);
 INLINE $A963;
FUNCTION GetControlValue(theControl: ControlHandle): INTEGER;
 INLINE $A960;
FUNCTION GetCtlValue(theControl: ControlHandle): INTEGER;
 INLINE $A960;
PROCEDURE SetControlMinimum(theControl: ControlHandle;minValue: INTEGER);
 INLINE $A964;
PROCEDURE SetCtlMin(theControl: ControlHandle;minValue: INTEGER);
 INLINE $A964;
FUNCTION GetControlMinimum(theControl: ControlHandle): INTEGER;
 INLINE $A961;
FUNCTION GetCtlMin(theControl: ControlHandle): INTEGER;
 INLINE $A961;
PROCEDURE SetControlMaximum(theControl: ControlHandle;maxValue: INTEGER);
 INLINE $A965;
PROCEDURE SetCtlMax(theControl: ControlHandle;maxValue: INTEGER);
 INLINE $A965;
FUNCTION GetControlMaximum(theControl: ControlHandle): INTEGER;
 INLINE $A962;
FUNCTION GetCtlMax(theControl: ControlHandle): INTEGER;
 INLINE $A962;
PROCEDURE SetControlReference(theControl: ControlHandle;data: LONGINT);
 INLINE $A95B;
PROCEDURE SetCRefCon(theControl: ControlHandle;data: LONGINT);
 INLINE $A95B;
FUNCTION GetControlReference(theControl: ControlHandle): LONGINT;
 INLINE $A95A;
FUNCTION GetCRefCon(theControl: ControlHandle): LONGINT;
 INLINE $A95A;
PROCEDURE SetControlAction(theControl: ControlHandle;actionProc: ProcPtr);
 INLINE $A96B;
PROCEDURE SetCtlAction(theControl: ControlHandle;actionProc: ProcPtr);
 INLINE $A96B;
FUNCTION GetControlAction(theControl: ControlHandle): ProcPtr;
 INLINE $A96A;
FUNCTION GetCtlAction(theControl: ControlHandle): ProcPtr;
 INLINE $A96A;
PROCEDURE DragControl(theControl: ControlHandle;startPt: Point;limitRect: Rect;
 slopRect: Rect;axis: INTEGER);
 INLINE $A967;
FUNCTION TestControl(theControl: ControlHandle;thePt: Point): INTEGER;
 INLINE $A966;
FUNCTION TrackControl(theControl: ControlHandle;thePoint: Point;actionProc: ProcPtr): INTEGER;
 INLINE $A968;
FUNCTION FindControl(thePoint: Point;theWindow: WindowPtr;VAR theControl: ControlHandle): INTEGER;
 INLINE $A96C;
PROCEDURE SetControlColor(theControl: ControlHandle;newColorTable: CCTabHandle);
 INLINE $AA43;
PROCEDURE SetCtlColor(theControl: ControlHandle;newColorTable: CCTabHandle);
 INLINE $AA43;
FUNCTION GetAuxiliaryControlRecord(theControl: ControlHandle;VAR acHndl: AuxCtlHandle): BOOLEAN;
 INLINE $AA44;
FUNCTION GetAuxCtl(theControl: ControlHandle;VAR acHndl: AuxCtlHandle): BOOLEAN;
 INLINE $AA44;
FUNCTION GetControlVariant(theControl: ControlHandle): INTEGER;
 INLINE $A809;
FUNCTION GetCVariant(theControl: ControlHandle): INTEGER;
 INLINE $A809;


{$ENDC} { UsingControls }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

