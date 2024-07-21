{************************************************************
	Terminals.p
	Pascal Interface to the Terminal Manager

		Copyright Apple Computer, Inc. 1988-1991
		All rights reserved
		
    This file is used in these builds: Mac32 HcMac MacPP BigBang Sys606

	Change History (most recent first):

		 <8>	 8/28/91	CH		Updated interface headers for consistency.
		 <7>	 8/20/91	BH		remove TMSetupCleanup from public interfaces
		 <6>	 7/25/91	JL		Checked in database generated file from DSG.  Added
									TerminalSendProcPtr - > TerminalChooseIdleProcPtr and utilized
									them to match C file
		 <5>	 6/25/91	JNG		Added tmConfigChanged
		 <4>	 6/18/91	BH		remove TMPChoose
		 <3>	  2/4/91	JL		Changed Includes to Include from PInterfaces directory of the
									Shell
		 <2>	 8/28/90	kaz		Change TermPointer to TermPtr
		 <1>	 3/14/90	BBH		first checked in

	To Do:
************************************************************}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT Terminals;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingTerminals}
{$SETC UsingTerminals := 1}

{$I+}
{$SETC TerminalsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingDialogs}
{$I $$Shell(PInterfaces)Dialogs.p}
{$ENDC}
{$IFC UNDEFINED UsingCTBUtilities}
{$I $$Shell(PInterfaces)CTBUtilities.p}
{$ENDC}
{$IFC UNDEFINED UsingConnections}
{$I $$Shell(PInterfaces)Connections.p}
{$ENDC}
{$SETC UsingIncludes := TerminalsIncludes}

CONST

{ current Terminal Manager version }
curTMVersion			=	2;

{ current Terminal Manager Environment Record version }
curTermEnvRecVers		=	0;

{ error codes    }
tmGenericError			=	-1;
tmNoErr					=	0;
tmNotSent				=	1;
tmEnvironsChanged		=	2;
tmNotSupported			=	7;
tmNoTools				=	8;

TYPE
TMErr = OSErr;

CONST

{ TMFlags }
tmInvisible				=	$00000001;
tmSaveBeforeClear		=	$00000002;
tmNoMenus				=	$00000004;
tmAutoScroll			=	$00000008;
tmConfigChanged			=	$00000010;

TYPE
{  TMFlags   }
TMFlags				=	LONGINT;


CONST

{ TMSelTypes & TMSearchTypes }
selTextNormal			=	$0001;
selTextBoxed			=	$0002;
selGraphicsMarquee		=	$0004;
selGraphicsLasso		=	$0008;
tmSearchNoDiacrit		=	$0100;	{These are only for TMSearchTypes}
tmSearchNoCase			=	$0200;	{These are only for TMSearchTypes}

TYPE
{  TMSelTypes & TMSearchTypes  }
TMSearchTypes		=	INTEGER;


TMSelTypes			=	INTEGER;

CONST

{ TMCursorTypes }
cursorText				=	1;
cursorGraphics			=	2;

TYPE
TMCursorTypes		=	INTEGER;


CONST

{ TMTermTypes }
tmTextTerminal			=	$0001;
tmGraphicsTerminal		=	$0002;

TYPE
{  TMTermTypes   }
TMTermTypes			=	INTEGER;
	

TermDataBlockPtr	= ^TermDataBlock;
TermDataBlockH		= ^TermDataBlockPtr;
TermDataBlock		=	RECORD
	flags: 		TMTermTypes;
	theData: 	Handle;
	auxData: 	Handle;
	reserved: 	LONGINT;
 END;

TermEnvironPtr		=	^TermEnvironRec;
TermEnvironRec		=	RECORD
	version:	INTEGER;
	termType:	TMTermTypes;
	textRows:	INTEGER;
	textCols:	INTEGER;
	cellSize:	Point;
	graphicSize:	Rect;
	slop:	Point;
	auxSpace:	Rect;
 END;	
	
TMSelection			=	RECORD
	CASE INTEGER OF
		1: (selRect:	Rect);
		2: (selRgnHandle:	RgnHandle;
			filler:	LONGINT);
		END;

{    TMTermTypes     }
TermPtr				=	^TermRecord;
TermHandle			=	^TermPtr;
TermRecord			=	RECORD
	procID:	INTEGER;
	flags:		TMFlags;
	errCode:	TMErr;
	refCon:		LONGINT;
	userData:	LONGINT;
	defProc:	ProcPtr;
	config:		Ptr;
	oldConfig:	Ptr;
	environsProc:	ProcPtr;
	reserved1:	LONGINT;
	reserved2:	LONGINT;
	tmPrivate:	Ptr;
	sendProc:	ProcPtr;
	breakProc:	ProcPtr;
	cacheProc:	ProcPtr;
	clikLoop:	ProcPtr;
	owner:		WindowPtr;
	termRect:	Rect;
	viewRect:	Rect;
	visRect:	Rect;
	lastIdle:	LONGINT;
	selection:	TMSelection;
	selType:	TMSelTypes;
	mluField:	LONGINT;
 END;


{	application routines type definitions }
TerminalSendProcPtr = ProcPtr;
TerminalBreakProcPtr = ProcPtr;
TerminalCacheProcPtr = ProcPtr;
TerminalSearchCallBackProcPtr = ProcPtr;
TerminalClikLoopProcPtr = ProcPtr;
TerminalEnvironsProcPtr = ProcPtr;
TerminalChooseIdleProcPtr = ProcPtr;

FUNCTION 	InitTM: TMErr;
FUNCTION 	TMGetVersion(hTerm: TermHandle): Handle;
FUNCTION 	TMGetTMVersion: INTEGER;

FUNCTION  	TMNew(termRect: Rect;viewRect: Rect;flags: TMFlags;procID: INTEGER;
			owner: WindowPtr;sendProc: TerminalSendProcPtr;cacheProc: TerminalCacheProcPtr;
			breakProc: TerminalBreakProcPtr;clikLoop: TerminalClikLoopProcPtr;environsProc: TerminalEnvironsProcPtr;
			refCon: LONGINT;userData: LONGINT): TermHandle;
			
PROCEDURE 	TMDispose(hTerm: TermHandle);

PROCEDURE 	TMKey(hTerm: TermHandle;theEvent: EventRecord);
PROCEDURE 	TMUpdate(hTerm: TermHandle;visRgn: RgnHandle);
PROCEDURE 	TMPaint(hTerm: TermHandle;theTermData: TermDataBlock;theRect: Rect);
PROCEDURE 	TMActivate(hTerm: TermHandle;activate: BOOLEAN);
PROCEDURE 	TMResume(hTerm: TermHandle;resume: BOOLEAN);
PROCEDURE 	TMClick(hTerm: TermHandle;theEvent: EventRecord);
PROCEDURE 	TMIdle(hTerm: TermHandle);

FUNCTION  	TMStream(hTerm: TermHandle;theBuffer: Ptr;theLength: LONGINT;flags: CMFlags): LONGINT;
FUNCTION  	TMMenu(hTerm: TermHandle;menuID: INTEGER;item: INTEGER): BOOLEAN;

PROCEDURE 	TMReset(hTerm: TermHandle);
PROCEDURE 	TMClear(hTerm: TermHandle);

PROCEDURE 	TMResize(hTerm: TermHandle;newViewRect: Rect);

FUNCTION  	TMGetSelect(hTerm: TermHandle;theData: Handle;VAR theType: ResType): LONGINT;
PROCEDURE 	TMGetLine(hTerm: TermHandle;lineNo: INTEGER;VAR theTermData: TermDataBlock);
PROCEDURE 	TMSetSelection(hTerm: TermHandle;theSelection: TMSelection;selType: TMSelTypes);

PROCEDURE 	TMScroll(hTerm: TermHandle;dh: INTEGER;dv: INTEGER);

FUNCTION  	TMValidate(hTerm: TermHandle): BOOLEAN;
PROCEDURE 	TMDefault(VAR theConfig: Ptr;procID: INTEGER;allocate: BOOLEAN);

FUNCTION  	TMSetupPreflight(procID: INTEGER;VAR magicCookie: LONGINT): Handle;
PROCEDURE 	TMSetupSetup(procID: INTEGER;theConfig: Ptr;count: INTEGER;theDialog: DialogPtr;
			VAR magicCookie: LONGINT);
FUNCTION  	TMSetupFilter(procID: INTEGER;theConfig: Ptr;count: INTEGER;theDialog: DialogPtr;
			VAR theEvent: EventRecord;VAR theItem: INTEGER;VAR magicCookie: LONGINT): BOOLEAN;
PROCEDURE 	TMSetupItem(procID: INTEGER;theConfig: Ptr;count: INTEGER;theDialog: DialogPtr;
			VAR theItem: INTEGER;VAR magicCookie: LONGINT);
PROCEDURE 	TMSetupXCleanup(procID: INTEGER;theConfig: Ptr;count: INTEGER;
 theDialog: DialogPtr;OKed: BOOLEAN;VAR magicCookie: LONGINT);
PROCEDURE 	TMSetupPostflight(procID: INTEGER);

FUNCTION  	TMGetConfig(hTerm: TermHandle): Ptr;
FUNCTION  	TMSetConfig(hTerm: TermHandle;thePtr: Ptr): INTEGER;

FUNCTION  	TMIntlToEnglish(hTerm: TermHandle;inputPtr: Ptr;VAR outputPtr: Ptr;
			language: INTEGER): OSErr;
FUNCTION  	TMEnglishToIntl(hTerm: TermHandle;inputPtr: Ptr;VAR outputPtr: Ptr;
			language: INTEGER): OSErr;
			
PROCEDURE 	TMGetToolName(id: INTEGER;VAR name: Str255);
FUNCTION  	TMGetProcID(name: Str255): INTEGER;

PROCEDURE 	TMSetRefCon(hTerm: TermHandle;refCon: LONGINT);
FUNCTION 	TMGetRefCon(hTerm: TermHandle): LONGINT;

PROCEDURE 	TMSetUserData(hTerm: TermHandle;userData: LONGINT);
FUNCTION 	TMGetUserData(hTerm: TermHandle): LONGINT;

FUNCTION 	TMAddSearch(hTerm: TermHandle;theString: Str255;where: Rect;searchType: TMSearchTypes;
			callBack: TerminalSearchCallBackProcPtr): INTEGER;
PROCEDURE 	TMRemoveSearch(hTerm: TermHandle;refnum: INTEGER);
PROCEDURE 	TMClearSearch(hTerm: TermHandle);

FUNCTION  	TMGetCursor(hTerm: TermHandle;cursType: TMCursorTypes): Point;

FUNCTION  	TMGetTermEnvirons(hTerm: TermHandle;VAR theEnvirons: TermEnvironRec): TMErr;

FUNCTION 	TMChoose(VAR hTerm: TermHandle;where: Point;idleProc: TerminalChooseIdleProcPtr): INTEGER;

PROCEDURE 	TMEvent(hTerm: TermHandle;theEvent: EventRecord);

FUNCTION	TMDoTermKey(hTerm: TermHandle;theKey: Str255): BOOLEAN;
FUNCTION	TMCountTermKeys(hTerm: TermHandle): INTEGER;
PROCEDURE	TMGetIndTermKey(hTerm: TermHandle;id: INTEGER;VAR theKey: Str255);

PROCEDURE	TMGetErrorString(hTerm: TermHandle;id: INTEGER;VAR errMsg: Str255);


{$ENDC} { UsingTerminals }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

