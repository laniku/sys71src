{
	File:		CommToolboxPriv.p

	Contains:	Internal interface to the CommResource Mgr and the CommToolbox Utilities

	Written by:	Byron Han
				Jerry Godes

	Copyright:	© 1988-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<25>	 8/27/91	JSM		Cleanup header, remove Pre70 stuff.
		<24>	 8/20/91	BH		move CRMReserveRF into public interfaces
		<23>	  8/9/91	JNG		Moved CRMReleaseRF into main interfaces
		<22>	 6/25/91	JNG		Move CRMIsDriverOpen to CommResources.p
		<21>	 6/18/91	BH		rename choose constants
		<21>	 6/18/91	BH		rename choose constants
		<20>	  1/9/91	kaz		<jng> Changing ModemStringType and PrinterStringType to STR# to
									include driver names. Changing ChooseIDStrID from -32512 to
									-32510.
		<19>	12/13/90	JNG		Use the System IconLDEF<kaz>
		<18>	 11/1/90	fjs		add new constants for the color icon types
		<17>	10/16/90	kaz		Adding CRMAppRec to keep track of the processes that init the
									TM, FT, or CM; renamed reserved to appList in CTBBlock; added
									bitfields for initialized mgrs; added prototypes for handling
									the app list; Removed _CTBKeystrokeFilter references; Renamed
									CRMStruct to CRMResourceCount.  <jng>
  	                                Term, FT, or Conn Mgrs; renamed reserved to appList to CTBBlock;
									added bitfields for initialized mgrs; added prototypes for
									handling the app list; fixed spelling of some messages.
									Removing _CTBKeystrokeFilter references. Renamed CRMStruct to
									CRMResourceCount.  <jng>
		<16>	 10/5/90	PN		Restore the project
		<15>	 9/10/90	JNG		Have ResFileRec contain canonical form of file name; Add in new
									resources for choose
		<14>	 8/15/90	kaz		Added PlaceWindow() prototype
		<13>	  8/6/90	kaz		Renaming GoodDrawOutlineButton; adding DoGrayOutline.
		<12>	 5/24/90	kaz		Combined GetIndflst and GetIndfinf; added Getflst()
		<11>	 5/22/90	kaz		Updated 'flst' and FontInfoRec to include a txMode field; merged
									FontInfoRec & TextState records; added Get and SetTextState
									(like GetPenState)
		<10>	 4/11/90	kaz		Added CmdPeriod() Prototype
		<8+>	 3/20/90	kaz		Merging in stuff from 1.0
									- struct for accessing QD globals
									- new routines in CommToolboxUtilityRoutines
		 <8>	 3/18/90	BBH		keep unused in IconPrivateBlock for Tools 1.0 compatibility with
									the Icon LDEF (unused was hasSM)
		 <7>	 3/16/90	BBH		added CTB_VersionType
		 <6>	 3/16/90	BBH		added MIN and MAX interfaces to CommToolboxUtilityRoutines.c
		 <5>	 3/16/90	BBH		added DoTheIcon, parse_finf, and parse_flst, FindMenuItem and
									GoodDrawOutlineButton
		 <4>	 3/15/90	BBH		fix selector typos
		 <3>	 3/14/90	BBH		added DITL package selectors
		 <2>	 3/14/90	BBH		integrate CRMPrivate.p CTBCoreIntf.p CTBPrivate.p and add
									resource type for min system heap size (temporary until ptch's
									are installed)
		 <1>	 3/14/90	BBH		first checked in

}

{$IFC UNDEFINED UsingIncludes}
	{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
UNIT CommToolboxPriv;
    INTERFACE
{$ENDC}

{$I+}
{$SETC CommToolboxInc := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingProcesses}
{$I $$Shell(PInterfaces)Processes.p}
{$ENDC}
{$SETC UsingIncludes := CommToolboxInc}

{$IFC UNDEFINED CommToolboxPriv}
{$SETC CommToolboxPriv := 1}

{	This file contains the resource types and resource ID's to be used by the CommToolbox }

{ the following 6 resources are temporary to be merged into ptch code }
CONST
	CTB_InstallType			=	'INIT';
	CTB_InstallID			=	29;
	
	CTB_DispatcherType		=	'proc';			{ this used to be ctbd -32512 }
	CTB_DispatcherID		=	-32509;
	
	CTB_GestaltProcType		=	'proc';			{ this used to be ctbg -32510 }
	CTB_GestaltProcID		=	-32508;
	
	CTB_PatchType			=	'ctbp';			{ this used to be type ctb¶ }
	CTB_Patch1				=	-32512;			{ allocate low memory }
	CTB_Patch2				=	-32511;			{ register builtin ports }
	CTB_Patch3				=	-32510;			{ perform gestalt installation }

	{ end temporary }
	
	CTB_ConnectionMgrType	=	'cmtb';
	CTB_FileTransferMgrType	=	'cmtb';
	CTB_TerminalMgrType		=	'cmtb';
	CTB_CTBUtilitiesType	=	'cmtb';
	CTB_CommResourceMgrType	=	'cmtb';
	
	CTB_ConnectionMgrID		=	-32512;
	CTB_FileTransferMgrID	=	-32511;
	CTB_TerminalMgrID		=	-32510;
	CTB_CTBUtilitiesID		=	-32509;
	CTB_CommResourceMgrID	=	-32508;
	
	CTB_VersionType			=	'ctb ';			{ this used to be ctbv -32512}
	CTB_VersionID			=	-32512;
	
	CTB_KeyclickType		=	'snd ';			{ this used to be ctb$ -32511 }
	CTB_KeyclickID			=	-32512;
	
	CTB_ChooseType			=	'proc';			{ this used to be choo -32512 }
	CTB_ChooseID			=	-32512;
	
	CTB_DITLPackType		=	'proc';			{ this used to be ditl -32512 }
	CTB_DITLPackID			=	-32511;
	
	CTB_NuLookupType		=	'proc';			{ this used to be nlup -32510 }
	CTB_NuLookupID			=	-32510;
	
	CTB_NuLookupParmsType	=	'flst';			{ this used to be parm -32510 }
	CTB_NuLookupParmsID		=	-32510;
	
	CTB_ModemIconType		=	'ICN#';			{ this used to be ctbi -32512 }
	CTB_Modem4ColorIconType =	'icl4';
	CTB_Modem8ColorIconType =	'icl8';
	CTB_ModemIconID			=	-32512;
	
	CTB_PrinterIconType		=	'ICN#';			{ this used to be ctbi -32511 }
	CTB_Printer4ColorIconType = 'icl4';
	CTB_Printer8ColorIconType = 'icl8';
	CTB_PrinterIconID		=	-32511;
	
	CTB_ModemStringType		=	'STR#';			{ this used to be ctbs -32512 }
	CTB_ModemStringID		=	-32512;
	
	CTB_PrinterStringType	=	'STR#';			{ this used to be ctbs -32511 }
	CTB_PrinterStringID		=	-32511;
	
	CTB_CommFolderNameType	=	'STR ';			{ this used to be ctbs -32510 }
	CTB_CommFolderNameID	=	-32510;
	
	CTB_MarkerType			=	'ctb ';			{ lets CTB6 installer scripts know CTB7 is installed }
	CTB_CTB6MarkerID		=	0;
	CTB_CTB7MarkerID		=	1;
	
	CTB_ChooseDLOGID		=	-32512;
	CTB_ChoosehdlgID		=	-32512;
	CTB_ChoosedctbID		=	-32512;
	CTB_ChooseDITLID		=	-32512;
	CTB_ChooseSTRsID		=	-32510;
	CTB_ChooseLDEFID		=	-32512;
	CTB_ChoosehmnuID		=	-32512;
	CTB_ChoosefinfID		=	-32512;
	CTB_ChooseflstID		=	-32512;			{ preferred over finf }
	CTB_ChooseCNTLID		=	-32512;			
	CTB_ChooseMENUID		=	-32512;
	
	CTB_ChooseConfirmDLOGID	=	-32511;
	CTB_ChooseConfirmDITLID	=	-32511;

	CTB_ChooseUnavailableDLOGID	=	-32509;
	CTB_ChooseUnavailableDITLID	=	-32509;
	
	CTB_NulookuphdlgID		=	-32510;
	CTB_NulookupDLOGID		=	-32510;
	CTB_NulookupdctbID		=	-32510;
	CTB_NulookupDITLID		=	-32510;
	CTB_NulookupSTRsID		=	-32510;
	CTB_NulookupLDEFID		=	-32510;
	
	CTB_PopupCDEFType		=	'CDEF';
	CTB_PopupCDEFID			=	63;
	
	{ added since CTB6 }
	CTB_PopupTriangleType	=	'PICT';
	CTB_PopupTriangleID		=	-8224;		{ owned by cdef 63 }
	
	CTB_PopupExpandType		=	'proc';		{ this expands menuwidth }
	CTB_PopupExpandID		=	-8224;		{ owned by cdef 63 }

{	CommRsrcMgr 	}
	CTBBlockVersion = 1;
	
	cmInUse					= 1;			{ values for cmtbFlags bitfield	}
	tmInUse					= 2;
	ftInUse					= 4;
	
{	CommToolboxCore }	
	CMSel			=	0;					{ manager selectors }
	TMSel			=	1;
	FTSel			=	2;
	
	BndType			=	0;					{ tool res selectors	}
	DefType			=	1;
	ValType			=	2;
	SetType			=	3;
	ScrType			=	4;
	LocType			=	5;
	
	CTBNoTools		=	8;					{ common error code }
	

{ Common Tool Messages }
	CTBInitMsg				=	0;
	CTBDisposeMsg			=	1;
	CTBSuspendMsg			=	2;
	CTBResumeMsg			=	3;
	CTBMenuMsg				=	4;
	CTBEventMsg				=	5;
	CTBActivateMsg			=	6;
	CTBDeactivateMsg		=	7;
	CTBGetErrorStringMsg	=	8; { except for connection manager since I BBH f*cked up }
	
	CTBIdleMsg		=	50;
	CTBResetMsg		=	51;
	CTBAbortMsg		=	52;
	
	CTBValidateMsg	=	0;
	CTBDefaultMsg	=	1;

	CTBPreflightMsg	=	0;
	CTBSetupMsg		=	1;
	CTBItemMsg		=	2;
	CTBFilterMsg	=	3;
	CTBCleanupMsg	=	4;
	
	CTBGetMsg		=	0;
	CTBSetMsg		=	1;
	
	CTB2EnglishMsg	=	0;
	CTB2IntlMsg		=	1;
		
{	CommToolboxUtilities privates }
	ChooseCM 	=	0;
	ChooseTM	=	1;
	ChooseFT	=	2;
	
{	ChooseRec messages	}
	{	
		ctbChooseNoChangelHandle means bring up dialog to select tool or configure tool, 
			but only return the toolName and the new configPtr (i.e. do not dispose of 
			old handle or create new one
	
		ctbChooseNoDialog means change to the toolName and config sent in without bringing 
			up the dialog
	
		ctbChooseNoChangleTool means popup only contains current tool (cannot change tool)
	}
	ctbChooseNoChangeHandle	=	1;
	ctbChooseNoDialog		=	2;
	ctbChooseNoChangeTool	=	4;

{	DITL package selectors	}
	AppendMsg		=		1;
	CountMsg		=		2;
	ShortenMsg		=		3;


TYPE
{	CommResourceMgr privates }
	ResourceMapHandlePtr = ^ResourceMapHandle;
	ResourceMapHandle = ^ResourceMapPtr;
	ResourceMapPtr = ^ResourceMapRecord;
	ResourceMapRecord = RECORD
		theHeader 	:	ARRAY[0..3] OF LONGINT;
		next		:	ResourceMapHandle;
		refNum		:	INTEGER;
	END;
		
	CRMToolContextPtr = ^CRMToolContext;			{NOTE::: ifthis changes change CRMToolPreflight/}
													{		 CRMToolPostflight}
	CRMToolContext	=	PACKED RECORD
		oldProcID	:	INTEGER;
		oldHidden	:	ResourceMapHandle;
		toolProcID	:	INTEGER;
		wasBelow	:	BOOLEAN;
	END;
	
	DispatchCodePtr = ^DispatchCode;
	DispatchCode = PACKED RECORD
		instruction:	INTEGER;
		table:			ARRAY[0..18] OF LONGINT;
		CTBrefnum:		INTEGER;
		big:			INTEGER;
	END;
	
	ResFileRecHdl 	=	^ResFileRecPtr;
	ResFileRecPtr 	= 	^ResFileRec;
	ResFileRec 		=	PACKED RECORD
		theName		:	FSSpec;			{ Canonical File Specification }
		refNum		:	INTEGER;		{ resource file reference number }
		resMap		:	ResourceMapHandle;	{ handle to master resource map }
		pZone		:	THz;			{ zone where resource map resides }
		useCount	:	LONGINT;		{ use count in the current heap }
		special		:	CRMToolContext;	{ context saved for setup }
		reserved	:	LONGINT;
		next		:	ResFileRecHdl;	{ next in the chain }
	END;
	
	{ Tracks individual resources	}
	CRMResourceCountPtr	= ^CRMResourceCount;
	CRMResourceCount	= RECORD
		next		:	CRMResourceCountPtr;	{ next in chain		}
		theHandle	:	LONGINT;				{ resource to track	}
		useCount	:	LONGINT;				{ # of times used	}
		refNum		:	INTEGER;				{ what is this for?	}
	END;

	CRMAppRecPtr	= 	^CRMAppRec;
	CRMAppRec		= 	RECORD
		aProcess	:	ProcessSerialNumber;	{ unique process id	}
		cmtbFlags	:	INTEGER;				{ bit field for TM, FT, CM	}
		reserved	:	LONGINT;			
		next		:	CRMAppRecPtr;			{ next in chain		}
	END;
	
	CTBGlobalPtr 	= 	^CTBBlockPtr;
	
	CTBBlockPtr 	= 	^CTBBlock;
	CTBBlock 		= 	RECORD
		version		:	INTEGER;
		CRMQueue 	: 	QHdrPtr;
		resList		:	LONGINT;
		private		:	INTEGER;
		appList		:	CRMAppRecPtr;			{ list of apps that call FT, TM, CM	}
		resFiles	:	ResFileRecHdl;
		toolResChain:	ResourceMapHandle;
		
		secret		:	ARRAY[0..15] OF LONGINT;
	END;
	

{	CommToolboxCore }
	CoreHandle		=	^CorePtr;
	CorePtr			=	^CoreRecord;
	CoreRecord		=	RECORD
		procID		:	INTEGER;
		
		flags		:	LONGINT;
		errCode		:	OSErr;
		
		refCon		:	LONGINT;
		userData	:	LONGINT;

		defProc		:	ProcPtr;

		config		:	Ptr;
		oldConfig	:	Ptr;

		reserved0	:	LONGINT;
		reserved1	:	LONGINT;
		reserved2	:	LONGINT;
	END;

{	CommToolboxUtilities privates }
	{ IconLDEF Cell Data	}
	CellDataH = ^CellDataP;
	CellDataP = ^CellDataBlock;
	CellDataBlock = RECORD
		icon : PACKED ARRAY[0..31] OF LONGINT;
		mask : PACKED ARRAY[0..31] OF LONGINT;
		title : STR255;
	END;
	
	{ CommToolboxUtilityRoutines	}
	GrafWorldPtr	= ^GrafWorld;
	GrafWorld 		= RECORD				{ Accessing QD Globals	}
		privates		: PACKED ARRAY [0..75] of BYTE;
		randSeed		: LONGINT;
		screenBits		: BitMap;
		arrow			: Cursor;
		dkGray, ltGray,
		gray, black,
		white			: Pattern;
		thePort			: GrafPtr;
	END;
	
	{System IconLDEF data}
	NewCellDataBlock = RECORD
		cHand	: Handle;
		cFont	: integer;
		cFace	: Style;
		cSize	: integer;
		cName	: Str255;
	END;
	NewCellDataBlockP = ^NewCellDataBlock;
	NewCellDataBlockH = ^NewCellDataBlockP;

	{ CommToolboxLDEF private storage	}
	IconPrivateH = ^IconPrivateP;
	IconPrivateP = ^IconPrivateBlock;
	IconPrivateBlock = RECORD
		unused		: BOOLEAN;		{ has to be here for CTB 1.0 compatibility }
		procID		: INTEGER;		{ res ref num of tool		}
		tempData	: NewCellDataBlockH; {Data for new IconLDEF }
	END;
	
	{ choose data structures }
	ChooseRecPtr 	=	^ChooseRec;
	ChooseRec		=	RECORD
		reserved	:	LONGINT;
		msg			:	LONGINT;
		idleProc	:	ProcPtr;
		filterProc	:	ProcPtr;
		newTool		:	Str63;
		newConfig	:	Ptr;
		eventProc	:	ProcPtr;
	END;
	
	{ For accessing 'finf' and 'flst' resources, etc	}
	TextState		=	RECORD
		theFont		: INTEGER;
		theFace		: Style;
		theSize		: INTEGER;
		theMode		: INTEGER;
	END;
	
{	CommResourceMgr routines }
FUNCTION	CRMOpenRFPerm(fName: STR63; vRefNum: INTEGER; dirID: LONGINT): INTEGER;			
													{ returns refnum.  res map put in sysheap }
													
FUNCTION	CRMGetRFCount(refNum: INTEGER): INTEGER;{ returns usage count }

FUNCTION	CRMCountFiles(fType: OSType; vRefNum: INTEGER; dirID: LONGINT): INTEGER;
														{ # files with given type }
FUNCTION	CRMGetIndFile(VAR fName: STR63; fType: OSType;	
					vRefNum: INTEGER; dirID: LONGINT; index: INTEGER): OSErr;
														{ return index_th file of given type }
PROCEDURE	CRMToolPreflight(procID: INTEGER; VAR crmContext: CRMToolContext);
PROCEDURE	CRMToolPostflight(crmContext: CRMToolContext);


{$IFC UNDEFINED COMMRESOURCEMGR}
FUNCTION	CRMParseRefNum(refNum: INTEGER; VAR fName: STR63; VAR vRefNum: INTEGER): OSErr;
													{ given file refnum, return fName and WD }
													
FUNCTION	CRMCreateCommunications(VAR vRefNum: INTEGER;
					VAR dirID: LONGINT): OSErr;			{ creates folder named Communications in system folder }
														{ find folder named Communications in blessed folder }
PROCEDURE	CRMDumpResChain;
FUNCTION 	CRMCheckTool(fName: STR63; fType: OSType;	
					vRefNum: INTEGER; dirID: LONGINT) : Boolean;  {is fName the correct fType?}
{$ENDC}										

{ CRM App List Handling Rotuines	}
FUNCTION	TrackManagers(mgrID: INTEGER): INTEGER;
FUNCTION	FindApp(aProcess: ProcessSerialNumber): CRMAppRecPtr;
FUNCTION	AddApp(aProcess: ProcessSerialNumber): CRMAppRecPtr;
PROCEDURE	RemoveApp(theApp: CRMAppRecPtr);

{	CommToolboxCore }
FUNCTION 	InitManager(selector: Integer) : OSErr;
PROCEDURE 	CTBGetToolName(procID : INTEGER; VAR name : STR255; MgrSel: INTEGER);
FUNCTION	CTBGetProcID(name: STR255; MgrSel: INTEGER): INTEGER;
FUNCTION	CTBGetVersion(hCore: CoreHandle; MgrSel: INTEGER): Handle;


FUNCTION 	CTBValidate(hCore : CoreHandle; MgrSel: INTEGER) : Boolean;
PROCEDURE 	CTBDefault(VAR ConfigPtr : Ptr; procID : integer; 
						allocate : Boolean; MgrSel: INTEGER);

FUNCTION 	CTBSetupPreflight(procID: INTEGER; VAR magicCookie: LONGINT; MgrSel: INTEGER):Handle;
PROCEDURE 	CTBSetupSetup(procID: INTEGER; theConfig: Ptr; count: INTEGER; theDialog: DialogPtr;
						VAR magicCookie: LONGINT; MgrSel: INTEGER);
FUNCTION 	CTBSetupFilter(procID: INTEGER; theConfig: Ptr; count: INTEGER; 
						theDialog: DialogPtr; VAR theEvent: EventRecord; VAR theItem: INTEGER;
						VAR magicCookie: LONGINT; MgrSel: INTEGER) : Boolean;
PROCEDURE 	CTBSetupItem(procID: INTEGER; theConfig: Ptr; count: INTEGER; theDialog :DialogPtr;
						VAR item: INTEGER; VAR magicCookie: LONGINT; MgrSel: INTEGER);
PROCEDURE 	CTBSetupCleanup(procID: INTEGER; theConfig: Ptr; count: INTEGER; theDialog: DialogPtr;
						VAR magicCookie: LONGINT; MgrSel: INTEGER);
PROCEDURE 	CTBSetupXCleanup(procID: INTEGER; theConfig: Ptr; count: INTEGER; theDialog: DialogPtr;
						OKed: BOOLEAN; VAR magicCookie: LONGINT; MgrSel: INTEGER);
PROCEDURE	CTBSetupPostflight(procID: INTEGER; MgrSel: INTEGER);

FUNCTION 	CTBGetConfig(hCore: CoreHandle; MgrSel: INTEGER) : Ptr;
FUNCTION 	CTBSetConfig(hCore: CoreHandle; thePtr: Ptr; MgrSel: INTEGER) : INTEGER;

FUNCTION	CTBIntlToEnglish(hCore: CoreHandle; inputPtr: Ptr; VAR outputPtr: Ptr; 
					language : INTEGER; MgrSel: INTEGER) : INTEGER;
FUNCTION 	CTBEnglishToIntl(hCore: CoreHandle; inputPtr: Ptr; VAR outputPtr: Ptr; 
					language : INTEGER; MgrSel: INTEGER) : INTEGER;

FUNCTION 	CTBChoose(VAR hCore:CoreHandle; where: Point; idleProc:ProcPtr; MgrSel: INTEGER) : INTEGER;
FUNCTION 	CTBPChoose(VAR hCore:CoreHandle; where: Point; VAR cRec:ChooseRec; MgrSel: INTEGER) : INTEGER;

{	CommToolboxUtilityRoutines }
FUNCTION 	CRMGetAResource(theType : ResType; procID: Integer) : Handle;
FUNCTION 	FindMenuItem(hMenu: MenuHandle; theItem: Str255): INTEGER;
FUNCTION 	GetIndflst(hInfo: Handle; oldStyle: BOOLEAN; 
								index: INTEGER; VAR finfInfo: TextState): OSErr;
PROCEDURE 	DoSolidOutline(pDialog: DialogPtr; theItem: INTEGER);
PROCEDURE 	DoGrayOutline(pDialog: DialogPtr; theItem: INTEGER);
PROCEDURE 	DoTheIcon(theIcon: Ptr; destRect: Rect; selected: BOOLEAN);
FUNCTION 	MIN(a, b: LONGINT): LONGINT;
FUNCTION 	MAX(a, b: LONGINT): LONGINT;
PROCEDURE 	GetTextState(VAR txState: TextState);
PROCEDURE 	SetTextState(txState: TextState);
PROCEDURE 	Getflst(procID, resourceID, finfIndex: INTEGER;
											VAR finfInfo: TextState);
FUNCTION 	GetQDGlobals: GrafWorldPtr;
PROCEDURE 	GetItemRect(pDialog: DialogPtr; itemNo: INTEGER; VAR theRect: Rect);
PROCEDURE 	SetUserItemProc(pDialog: DialogPtr; itemNo: INTEGER; theProc: ProcPtr);
PROCEDURE	PCopyString(srcStr: Str32; VAR destStr: Str32);
FUNCTION 	CmdPeriod(theEvent: EventRecord): BOOLEAN;
FUNCTION    PlaceWindow(theParent: WindowPtr;childHeight,childWidth: INTEGER): Point;

{$ENDC}    { CommToolboxPriv }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}


