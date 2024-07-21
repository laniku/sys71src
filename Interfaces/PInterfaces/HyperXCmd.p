{
    HyperXCmd.p
    Definition file for HyperCard XCMDs and XFCNs in Pascal.

    Copyright Apple Computer, Inc.  1987-1991
    All rights reserved
    This file is used in these builds: ROM System

			
				Change History (most recent first):
			
		 <6>	 2/17/92	MH		Changed refs to extended to Extended80
		 <5>	  8/8/91	JL		Updated Copyright.
		 <4>	 3/13/91	JL		Checked in MPW version.  HyperCard version 2.0 final.
			
				To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
    UNIT HyperXCmd;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingHyperXCmd}
{$SETC UsingHyperXCmd := 1}

{$I+}
{$SETC HyperXCmdIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingEvents}
{$I $$Shell(PInterfaces)Events.p}
{$ENDC}
{$IFC UNDEFINED UsingTextEdit}
{$I $$Shell(PInterfaces)TextEdit.p}
{$ENDC}
{$IFC UNDEFINED UsingMenus}
{$I $$Shell(PInterfaces)Menus.p}
{$ENDC}
{$IFC UNDEFINED UsingStandardFile}
{$I $$Shell(PInterfaces)StandardFile.p}
{$ENDC}
{$SETC UsingIncludes := HyperXCmdIncludes}

CONST
  { result codes }
  xresSucc = 0;
  xresFail = 1;
  xresNotImp = 2;

  { XCMDBlock constants for event.what... }
  xOpenEvt              = 1000;         { the first event after you are created }
  xCloseEvt             = 1001;         { your window is being forced close (Quit?) }
  xGiveUpEditEvt        = 1002;         { you are losing Edit... }
  xGiveUpSoundEvt	= 1003;		{ someone else is requesting HyperCard's sound channel }
  xHidePalettesEvt	= 1004;		{ someone called HideHCPalettes }
  xShowPalettesEvt	= 1005;		{ someone called ShowHCPalettes }
  xEditUndo		= 1100;		{ Edit——Undo }
  xEditCut		= 1102;		{ Edit——Cut }
  xEditCopy		= 1103;		{ Edit——Copy }
  xEditPaste		= 1104;		{ Edit——Paste }
  xEditClear		= 1105;		{ Edit——Clear }
  xSendEvt		= 1200;		{ script has sent you a message (text) }
  xSetPropEvt		= 1201;		{ set a window property }
  xGetPropEvt		= 1202;		{ get a window property }
  xCursorWithin		= 1300;		{ cursor is within the window }
  xMenuEvt		= 1400;		{ user has selected an item in your menu }
  xMBarClickedEvt	= 1401;		{ a menu is about to be shown--update if needed }

  xShowWatchInfoEvt	= 1501;		{ for variable and message watchers }
  xScriptErrorEvt	= 1502;		{ place the insertion point }
  xDebugErrorEvt	= 1503;		{ user clicked "Debug" at a complaint }
  xDebugStepEvt		= 1504;		{ hilite the line }
  xDebugTraceEvt	= 1505;		{ same as step but tracing }
  xDebugFinishedEvt	= 1506;		{ script ended }

  paletteProc		= 2048;		{ Windoid with grow box }
  palNoGrowProc		= 2052;		{ standard Windoid defproc } 
  palZoomProc		= 2056;		{ Windoid with zoom and grow }
  palZoomNoGrow		= 2060;		{ Windoid with zoom and no grow }
  hasZoom		=    8;
  hasTallTBar		=    2;
  toggleHilite		=    1;
  
  maxCachedChecks	= 16;		{ maximum number of checkpoints in a script }

  { paramCount is set to these constants when first calling special XThings }
  xMessageWatcherID	= -2;
  xVariableWatcherID	= -3;
  xScriptEditorID	= -4;
  xDebuggerID		= -5;

  { XTalkObjectPtr^.objectKind values }
  stackObj	= 1;
  bkgndObj	= 2;
  cardObj	= 3;
  fieldObj	= 4;
  buttonObj	= 5;

  { selectors for ShowHCAlert's dialogs (shown as buttonID:buttonText) }
  errorDlgID		= 1;	{ 1:OK (default) }
  confirmDlgID		= 2;	{ 1:OK (default) and 2:Cancel }
  confirmDelDlgID	= 3;	{ 1:Cancel (default) and 2:Delete }
  yesNoCancelDlgID	= 4;	{ 1:Yes (default), 2:Cancel, and 3:No }


TYPE
  XCmdPtr   = ^XCmdBlock;
  XCmdBlock = RECORD
		paramCount:	INTEGER; { If = -1 then new use for XWindoids }
		params:		ARRAY[1..16] OF Handle;
		returnValue: 	Handle; 
		passFlag:	BOOLEAN;
		
		entryPoint:	ProcPtr; { to call back to HyperCard }
		request:	INTEGER;
		result:		INTEGER;
		inArgs:		ARRAY[1..8] OF LongInt;
		outArgs:	ARRAY[1..4] OF LongInt;
	      END;

  XWEventInfoPtr = ^XWEventInfo;
  XWEventInfo	 = RECORD
		     event:	  EventRecord;
		     eventWindow: WindowPtr;
		     eventParams: ARRAY[1..9] OF LongInt;
		     eventResult: Handle;
		   END;
		  
  XTalkObjectPtr = ^XTalkObject;
  XTalkObject = RECORD
		  objectKind:   INTEGER;	{ stack, bkgnd, card, field, or button }
		  stackNum:	LongInt;	{ reference number of the source stack }
		  bkgndID:	LongInt;
		  cardID:	LongInt;
		  buttonID:	LongInt;
		  fieldID:	LongInt;
		END;

  CheckPtHandle = ^CheckPtPtr;
  CheckPtPtr	= ^CheckPts;
  CheckPts	= RECORD
                    checks: ARRAY[1..maxCachedChecks] OF INTEGER;
		  END;


(****  HyperTalk Utilities  ****)
FUNCTION  EvalExpr(paramPtr: XCmdPtr; expr: Str255): Handle;
PROCEDURE SendCardMessage(paramPtr: XCmdPtr; msg: Str255);
PROCEDURE SendHCMessage(paramPtr: XCmdPtr; msg: Str255);
PROCEDURE RunHandler(paramPtr: XCmdPtr; handler: Handle);

(****  Memory Utilities  ****)
FUNCTION  GetGlobal(paramPtr: XCmdPtr; globName: Str255): Handle;
PROCEDURE SetGlobal(paramPtr: XCmdPtr; globName: Str255; globValue: Handle);
PROCEDURE ZeroBytes(paramPtr: XCmdPtr; dstPtr: Ptr;longCount: LongInt);

(****  String Utilities  ****)
PROCEDURE ScanToReturn(paramPtr: XCmdPtr; VAR scanPtr: Ptr);
PROCEDURE ScanToZero(paramPtr: XCmdPtr; VAR scanPtr: Ptr);
FUNCTION  StringEqual(paramPtr: XCmdPtr; str1,str2: Str255): BOOLEAN;
FUNCTION  StringLength(paramPtr: XCmdPtr; strPtr: Ptr): LongInt;
FUNCTION  StringMatch(paramPtr: XCmdPtr; pattern: Str255; target: Ptr): Ptr;
PROCEDURE ZeroTermHandle(paramPtr: XCmdPtr; hndl: Handle);	

(****  String Conversions  ****)
PROCEDURE BoolToStr(paramPtr: XCmdPtr; bool: BOOLEAN; VAR str: Str255);
PROCEDURE ExtToStr(paramPtr: XCmdPtr; num: Extended80; VAR str: Str255);
PROCEDURE LongToStr(paramPtr: XCmdPtr; posNum: LongInt; VAR str: Str255);
PROCEDURE NumToHex(paramPtr: XCmdPtr; num: LongInt; nDigits: INTEGER; VAR str: Str255);
PROCEDURE NumToStr(paramPtr: XCmdPtr; num: LongInt; VAR str: Str255);
FUNCTION  PasToZero(paramPtr: XCmdPtr; str: Str255): Handle;
PROCEDURE PointToStr(paramPtr: XCmdPtr; pt: Point; VAR str: Str255);
PROCEDURE RectToStr(paramPtr: XCmdPtr; rct: Rect; VAR str: Str255);
PROCEDURE ReturnToPas(paramPtr: XCmdPtr; zeroStr: Ptr; VAR pasStr: Str255);
FUNCTION  StrToBool(paramPtr: XCmdPtr; str: Str255): BOOLEAN;
FUNCTION  StrToExt(paramPtr: XCmdPtr; str: Str255): Extended80;
FUNCTION  StrToLong(paramPtr: XCmdPtr; str: Str255): LongInt;
FUNCTION  StrToNum(paramPtr: XCmdPtr; str: Str255): LongInt;
PROCEDURE StrToPoint(paramPtr: XCmdPtr; str: Str255; VAR pt: Point);
PROCEDURE StrToRect(paramPtr: XCmdPtr; str: Str255; VAR rct: Rect);
PROCEDURE ZeroToPas(paramPtr: XCmdPtr; zeroStr: Ptr; VAR pasStr: Str255);

(****  Field Utilities  ****)
FUNCTION  GetFieldByID(paramPtr: XCmdPtr; cardFieldFlag: BOOLEAN; fieldID: INTEGER): Handle;
FUNCTION  GetFieldByName(paramPtr: XCmdPtr; cardFieldFlag: BOOLEAN; fieldName: Str255): Handle;
FUNCTION  GetFieldByNum(paramPtr: XCmdPtr; cardFieldFlag: BOOLEAN; fieldNum: INTEGER): Handle;
PROCEDURE SetFieldByID(paramPtr: XCmdPtr; cardFieldFlag: BOOLEAN; fieldID: INTEGER; fieldVal: Handle);
PROCEDURE SetFieldByName(paramPtr: XCmdPtr; cardFieldFlag: BOOLEAN; fieldName: Str255; fieldVal: Handle);
PROCEDURE SetFieldByNum(paramPtr: XCmdPtr; cardFieldFlag: BOOLEAN; fieldNum: INTEGER; fieldVal: Handle);
FUNCTION  GetFieldTE(paramPtr: XCmdPtr; cardFieldFlag: BOOLEAN; fieldID,fieldNum: INTEGER;
		     fieldNamePtr: StringPtr): TEHandle;
PROCEDURE SetFieldTE(paramPtr: XCmdPtr; cardFieldFlag: BOOLEAN; fieldID,fieldNum: INTEGER;
		     fieldNamePtr: StringPtr; fieldTE: TEHandle);

(****  Miscellaneous Utilities  ****)
PROCEDURE BeginXSound(paramPtr: XCmdPtr; window: WindowPtr);			
PROCEDURE EndXSound(paramPtr: XCmdPtr);				
FUNCTION  GetFilePath(paramPtr: XCmdPtr; fileName: Str255; numTypes: INTEGER; typeList: SFTypeList;
		      askUser: BOOLEAN; VAR fileType: OSType; VAR fullName: Str255): BOOLEAN;
PROCEDURE GetXResInfo(paramPtr: XCmdPtr; VAR resFile: INTEGER; VAR resID: INTEGER;
		      VAR rType: ResType; VAR name: Str255);
PROCEDURE Notify(paramPtr: XCmdPtr);
PROCEDURE SendHCEvent(paramPtr: XCmdPtr; event: EventRecord);	
PROCEDURE SendWindowMessage(paramPtr: XCmdPtr; windPtr: WindowPtr;
			    windowName: Str255; msg: Str255);
FUNCTION  FrontDocWindow(paramPtr: XCmdPtr): WindowPtr;
FUNCTION  StackNameToNum(paramPtr: XCmdPtr; stackName: Str255): LongInt;
FUNCTION  ShowHCAlert(paramPtr: XCMDPtr; dlgID: INTEGER; promptStr: Str255): INTEGER;

(****  Creating and Disposing XWindoids  ****)
FUNCTION  NewXWindow(paramPtr: XCmdPtr; boundsRect: Rect; title: Str255; visible: BOOLEAN;
		     procID: INTEGER; color: BOOLEAN; floating: BOOLEAN): WindowPtr;		
FUNCTION  GetNewXWindow(paramPtr: XCmdPtr; templateType: ResType; templateID: INTEGER;
			color: BOOLEAN; floating: BOOLEAN): WindowPtr;		
PROCEDURE CloseXWindow(paramPtr: XCmdPtr; window: WindowPtr);	

(****  XWindoid Utilities  ****)
PROCEDURE HideHCPalettes(paramPtr: XCmdPtr);
PROCEDURE ShowHCPalettes(paramPtr: XCmdPtr);
PROCEDURE RegisterXWMenu(paramPtr: XCmdPtr; window: WindowPtr; menu: MenuHandle; registering: BOOLEAN);
PROCEDURE SetXWIdleTime(paramPtr: XCmdPtr; window: WindowPtr; interval: LongInt);
PROCEDURE XWHasInterruptCode(paramPtr: XCmdPtr; window: WindowPtr; haveCode: BOOLEAN);
PROCEDURE XWAlwaysMoveHigh(paramPtr: XCmdPtr; window: WindowPtr; moveHigh: BOOLEAN);
PROCEDURE XWAllowReEntrancy(paramPtr: XCmdPtr; window: WindowPtr; allowSysEvts: BOOLEAN; allowHCEvts: BOOLEAN);

(****  Text Editing Utilities  ****)
PROCEDURE BeginXWEdit(paramPtr: XCmdPtr; window: WindowPtr);			
PROCEDURE EndXWEdit(paramPtr: XCmdPtr; window: WindowPtr);				
FUNCTION  HCWordBreakProc(paramPtr: XCmdPtr): ProcPtr;		
PROCEDURE PrintTEHandle(paramPtr: XCmdPtr; hTE: TEHandle; header: StringPtr);

(****  Script Editor support  ****)
FUNCTION  GetCheckPoints(paramPtr: XCmdPtr): CheckPtHandle;	
PROCEDURE SetCheckPoints(paramPtr: XCmdPtr; checkLines: CheckPtHandle);
PROCEDURE FormatScript(paramPtr: XCmdPtr; scriptHndl: Handle; 
		       VAR insertionPoint: LongInt; quickFormat: BOOLEAN);
PROCEDURE SaveXWScript(paramPtr: XCmdPtr; scriptHndl: Handle);	
PROCEDURE GetObjectName(paramPtr: XCmdPtr; object: XTalkObjectPtr; VAR objName: Str255);
PROCEDURE GetObjectScript(paramPtr: XCmdPtr; object: XTalkObjectPtr; VAR scriptHndl: Handle);
PROCEDURE SetObjectScript(paramPtr: XCmdPtr; object: XTalkObjectPtr; scriptHndl: Handle);

(****  Debugging Tools support  ****)
PROCEDURE AbortScript(paramPtr: XCmdPtr);
PROCEDURE GoScript(paramPtr: XCmdPtr);
PROCEDURE StepScript(paramPtr: XCmdPtr; stepInto: BOOLEAN);
PROCEDURE CountHandlers(paramPtr: XCmdPtr; VAR handlerCount: INTEGER);
PROCEDURE GetHandlerInfo(paramPtr: XCmdPtr; handlerNum: INTEGER; VAR handlerName: Str255;
			 VAR objectName: Str255; VAR varCount: INTEGER);
PROCEDURE GetVarInfo(paramPtr: XCmdPtr; handlerNum: INTEGER; varNum: INTEGER;
		     VAR varName: Str255; VAR isGlobal: BOOLEAN; VAR varValue: Str255;
		     varHndl: Handle);
PROCEDURE SetVarValue(paramPtr: XCmdPtr; handlerNum: INTEGER; varNum: INTEGER;
		      varHndl: Handle);
FUNCTION  GetStackCrawl(paramPtr: XCmdPtr): Handle;
PROCEDURE TraceScript(paramPtr: XCmdPtr; traceInto: BOOLEAN);


{$ENDC}    { UsingHyperXCmd }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}
