/*
	File:		CommToolboxPriv.h

	Contains:	Internal interface to the CommResource Mgr and the CommToolbox Utilities

	Written by:	Byron Han, Jerry Godes

	Copyright:	© 1988-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<33>	 8/27/91	JSM		Cleanup header, remove Pre70 stuff.
		<32>	 8/20/91	BH		move CRMReserveRF into public interfaces
		<31>	  8/9/91	JNG		Moved CRMReleaseRF into main interfaces
		<30>	 6/25/91	JNG		Move CRMIsDriverOpen into CommResources.h
		<29>	 6/18/91	BH		rename choose messages
		<28>	  1/9/91	kaz		<jng> Changing ModemStringType and PrinterStringType to STR# to
									include driver names. Changing ChooseIDStrID from -32512 to
									-32510.
		<27>	12/21/90	JL		changed constStrxxParameter to ConstStrxxxParam to match change
									in Types.h
		<26>	12/13/90	JNG		Use the System Icon LDEF <kaz>
		<25>	 11/4/90	dba		miscellaneous cleanup, including using (void) instead of (),
									more care about const, including use of constStr255Parameter,
									getting rid of extraneous parameter names, getting rid of stuff
									on lines after #endif (not acceptable for ANSI standard), etc.
		<24>	 11/1/90	fjs		add defines for the color icons associated with the serial ports
		<23>	 10/5/90	kaz		Removing _CTBKeystrokeFilter references. <jng>
		<22>	 10/2/90	kaz		Adding CRMAppRec to keep track of the processes that init the
									Term, FT, or Conn Mgrs; renamed reserved to appList to CTBBlock;
									added bitfields for initialized mgrs; added prototypes for
									handling the app list; fixed spelling of some messages. <jng>
		<21>	 9/10/90	gbm		don’t you just hate it when boneheads check in files that they
									obviously haven’t compiled... I do :)
		<20>	 9/10/90	JNG		Have ResFileRec contain canonical form of file name; Add in new
									resources for choose
		<19>	 8/23/90	kaz		Added GetMemErr(), GetResErr() macros.
		<18>	 8/15/90	kaz		Added PlaceWindow() prototype
		<17>	  8/6/90	kaz		Renaming GoodDrawOutlineButton(); added DoGrayOutline().
		<16>	 5/24/90	kaz		Combined GetIndfinf & GetIndflst; added Getflst()
		<15>	 5/22/90	kaz		Updated FontInfoRec to have a textMode;  Merged FontInfoRec &
									TextState; renamed Parse_finf and Parse_flst; added routines to
									Get & Set TextState
		<14>	 4/11/90	kaz		Added CmdPeriod Prototype
		<13>	 3/22/90	BBH		moved getglobals macro here from CommResourceMgr.c
	    <12>	 3/20/90	kaz		Merging in changes from 1.0
	   								- struct for accessing QD globals
									- new routines in CommToolboxUtilityRoutines
		<11>	 3/18/90	BBH		keep IconPrivateBlock's unused field for Tools 1.0
									compatibility.  Sorry for the flip flops
		<10>	 3/18/90	BBH		remove change to IconPrivateBlock
		 <9>	 3/18/90	BBH		returned hasSM (renamed unused) to IconPrivateBlock since the
									tools assume that the procID is the second word in the
									IconPrivateBlock data structure (this uncovered the bug in
									ReaLDEF!)
		 <8>	 3/16/90	BBH		added CTB_VersionType
		 <7>	 3/16/90	BBH		added Menus.h to include list to support GetMenuItem routine in
									CommToolboxUtilityRoutines.c
		 <6>	 3/16/90	BBH		added FontInfoRec, parse_finf, parse_flst,
									GoodDrawOutlineButton, FindMenuItem
		 <5>	 3/15/90	BBH		add proper include in case they were not         included before
									(Memory and Resources and         Dialogs)
		<4+>	 3/15/90	BBH		add OSUtils to include list, fix typos
		 <4>	 3/15/90	BBH		add proper include in case they were not included before (Memory
									and Resources and Dialogs)
		 <3>	 3/14/90	BBH		added min system heap resource (temporary until ptch's go in)
		 <2>	 3/14/90	BBH		Merged in CommResourcePriv.h, CTBPrivate.h, and CTBCoreIntf.h
		 <1>	 3/14/90	BBH		first checked in
*/

#ifndef __CommToolboxPriv__
#define __CommToolboxPriv__

#ifndef __RESOURCES__
#include <Resources.h>
#endif

#ifndef __MEMORY__
#include <Memory.h>
#endif

#ifndef __DIALOGS__
#include <Dialogs.h>
#endif

#ifndef __MENUS__
#include <Menus.h>
#endif

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif

#ifndef __FILES__
#include <Files.h>
#endif

#ifndef __PROCESSES__
#include <Processes.h>
#endif

//	the resource types and resource ID's to be used by the CommToolbox
/* the following 7 resources are temporary to be merged into ptch code */
#define		CTB_InstallType			'INIT'
#define		CTB_InstallID			29

#define		CTB_DispatcherType		'proc'			/* this used to be ctbd -32512 */
#define		CTB_DispatcherID		-32509

#define		CTB_GestaltProcType		'proc'			/* this used to be ctbg -32510 */
#define		CTB_GestaltProcID		-32508

#define		CTB_PatchType			'ctbp'			/* this used to be type ctb∂ */
#define		CTB_Patch1				-32512			/* allocate low memory */
#define		CTB_Patch2				-32511			/* register builtin ports */
#define		CTB_Patch3				-32510			/* perform gestalt installation */
/* end temporary */

#define		CTB_ConnectionMgrType	'cmtb'
#define		CTB_FileTransferMgrType	'cmtb'
#define		CTB_TerminalMgrType		'cmtb'
#define		CTB_CTBUtilitiesType	'cmtb'
#define		CTB_CommResourceMgrType	'cmtb'

#define		CTB_ConnectionMgrID		-32512
#define		CTB_FileTransferMgrID	-32511
#define		CTB_TerminalMgrID		-32510
#define		CTB_CTBUtilitiesID		-32509
#define		CTB_CommResourceMgrID	-32508

#define		CTB_VersionType			'ctb '			// used to be ctbv -32512
#define		CTB_VersionID			-32512

#define		CTB_KeyclickType		'snd '			/* this used to be ctb$ -32511 */
#define		CTB_KeyclickID			-32512

#define		CTB_ChooseType			'proc'			/* this used to be choo -32512 */
#define		CTB_ChooseID			-32512

#define		CTB_DITLPackType		'proc'			/* this used to be ditl -32512 */
#define		CTB_DITLPackID			-32511

#define		CTB_NuLookupType		'proc'			/* this used to be nlup -32510 */
#define		CTB_NuLookupID			-32510

#define		CTB_NuLookupParmsType	'flst'			/* this used to be parm -32510 */
#define		CTB_NuLookupParmsID		-32510

#define		CTB_ModemIconType		'ICN#'			/* this used to be ctbi -32512 */
#define		CTB_Modem4ColorIconType 'icl4'
#define		CTB_Modem8ColorIconType 'icl8'
#define		CTB_ModemIconID			-32512

#define		CTB_PrinterIconType		  'ICN#'		/* this used to be ctbi -32511 */
#define		CTB_Printer4ColorIconType 'icl4'
#define		CTB_Printer8ColorIconType 'icl8'
#define		CTB_PrinterIconID		  -32511

#define 	CTB_ModemStringType		'STR#'			/* this used to be ctbs -32512 */
#define		CTB_ModemStringID		-32512

#define		CTB_PrinterStringType	'STR#'			/* this used to be ctbs -32511 */
#define		CTB_PrinterStringID		-32511

#define		CTB_CommFolderNameType	'STR '			/* this used to be ctbs -32510 */
#define		CTB_CommFolderNameID	-32510

#define		CTB_MarkerType			'ctb '			/* lets CTB6 installer scripts know CTB7 is installed */
#define		CTB_CTB6MarkerID		0
#define		CTB_CTB7MarkerID		1

#define		CTB_ChooseDLOGID		-32512
#define		CTB_ChoosehdlgID		-32512
#define		CTB_ChoosedctbID		-32512
#define		CTB_ChooseDITLID		-32512
#define		CTB_ChooseSTRsID		-32510
#define		CTB_ChooseLDEFID		-32512
#define		CTB_ChoosehmnuID		-32512
#define		CTB_ChoosefinfID		-32512
#define		CTB_ChooseflstID		-32512			/* preferred over finf */
#define		CTB_ChooseCNTLID		-32512
#define		CTB_ChooseMENUID		-32512

#define		CTB_ChooseConfirmDLOGID	-32511
#define		CTB_ChooseConfirmDITLID	-32511

#define		CTB_ChooseUnavailableDLOGID	-32509
#define		CTB_ChooseUnavailableDITLID	-32509

#define		CTB_NulookuphdlgID		-32510
#define		CTB_NulookupDLOGID		-32510
#define		CTB_NulookupdctbID		-32510
#define		CTB_NulookupDITLID		-32510
#define		CTB_NulookupSTRsID		-32510
#define		CTB_NulookupLDEFID		-32510

#define		CTB_PopupCDEFType		'CDEF'
#define		CTB_PopupCDEFID			63

/* added since CTB6 */
#define		CTB_PopupTriangleType	'PICT'
#define		CTB_PopupTriangleID		-8224		/* owned by cdef 63 */

#define		CTB_PopupExpandType		'proc'		/* this expands menuwidth */
#define		CTB_PopupExpandID		-8224		/* owned by cdef 63 */


//		Communications Resource Manager
/////////////////////////////////////////////////////////////////////////////////////////////
// 	partial declaration of resource map handle
typedef struct ResourceMapRecord {
	long		theHeader[4];
	struct ResourceMapRecord
				**next;
	short		refNum;
} ResourceMapRecord, *ResourceMapPtr, **ResourceMapHandle, ***ResourceMapHandlePtr;


//	structures used by CRM for manipulating the resource map chain
typedef struct CRMToolContext {  		/* NOTE	if this structure changes,
												CRMToolPreflight/Postflight
												have to change as well 		*/
	short				oldProcID;
	ResourceMapHandle	oldHidden;		// old resfile just below system file
	short				toolProcID;
	Boolean				wasBelow;				// were we already below the system map?
} CRMToolContext, *CRMToolContextPtr;


//	structures used to manage resource files
typedef struct ResFileRec {
	FSSpec				theName;				/* Canonical File id */
	short				refNum;					/* resource file reference number */
	ResourceMapHandle							/* the resource map */
						resMap;
	THz					pZone;					/* zone the resource map resides in */
	long				useCount;				/* number times opened/closed */
	CRMToolContext		special;				/* special context for CTBSetupPreflight/Postflight */
	long				reserved;				/* who knows what */
	struct ResFileRec **next;					/* next in the chain */
} ResFileRec, *ResFileRecPtr, **ResFileRecHdl;

//	data structure used to keep track of resources (useCount etc)
typedef struct CRMResourceCount {
	struct CRMResourceCount	*next;
	long		theHandle;
	long		useCount;
	short		refnum;
} CRMResourceCount, *CRMResourceCountPtr;

// bit field for cmtbFlags below
#define		cmInUse			1
#define		ftInUse			1 << (CTB_FileTransferMgrID - CTB_ConnectionMgrID)
#define		tmInUse			1 << (CTB_TerminalMgrID - CTB_ConnectionMgrID)

// data struct to keep a list of processes that have inited a mgr
typedef struct CRMAppRec {
	ProcessSerialNumber		aProcess;
	short					cmtbFlags;	// tmInUse, etc.
	long					reserved;
	struct CRMAppRec		*next;
} CRMAppRec, *CRMAppRecPtr;

//	commtoolbox dispatcher format
typedef struct DispatchCode {
	short		instruction;			// bra.s @OK
	long		table[19];				// table of manager pointers
	short		CTBrefnum;				// ignored
	short		big;					// ignored
}	DispatchCode, *DispatchCodePtr;


//	CommToolbox Globals pointed to by 0xBB4
#define		CTBBlockVersion		1

typedef struct CTBBlock {
	short				version;		// should be CTBBlockVersion
	QHdrPtr				CRMQueue;		// queue of devices being managed
	long				resList;		// queue of resources being managed
	short				private;		// What is this?
	CRMAppRecPtr		appList;		// List o' processes that call us
	ResFileRec			**resFiles;		// queue of files being managed
	ResourceMapHandle	toolResChain;	// ?????

	long				secret[16];
} CTBBlock, *CTBBlockPtr;

#define		CRMGetGlobals		(* (CTBBlockPtr *) CommToolboxGlobals)
#define		GetMemErr()			MemError()
#define		GetResErr()			*((short *) ResErr)

/*	internal CommResourceMgr routines */
pascal short	CRMOpenRFPerm(ConstStr63Param fName, short vRefNum, long dirID);
pascal short	CRMGetRFCount(short refNum);
pascal OSErr	CRMParseRefNum(short refNum, Str63 fName, short *vRefNum);

pascal OSErr	CRMCreateCommunications(short *vRefNum, long *dirID);
pascal short	CRMCountFiles(OSType fType, short vRefNum, long dirID);
pascal OSErr	CRMGetIndFile(Str63 fName, OSType fType, short vRefNum, long dirID, short index);
pascal Boolean	CRMCheckTool(ConstStr63Param fName, OSType fType, short vRefNum, long dirID);

pascal void		CRMDumpResChain(void);

pascal void 	CRMToolPreflight(short procID, CRMToolContext *);
pascal void		CRMToolPostflight(const CRMToolContext *);

/* CRM App List Handling Routines	*/
pascal short	TrackManagers(short mgrID);
CRMAppRecPtr 	FindApp(const ProcessSerialNumber *);
CRMAppRecPtr 	AddApp(const ProcessSerialNumber *);
void 			RemoveApp(CRMAppRecPtr);

//	CommToolbox Utilities

// Choose
/* Choose private data	structures */
typedef struct ChooseRec {
	long	reserved;
	long	msg;					// one of {ctbChooseNoChangeHandle, ctbChooseNoDialog, ctbChooseNoChangeTool}
	ProcPtr	idleProc;
	ProcPtr	filterProc;
	Str63	newTool;
	Ptr		newConfig;
	ProcPtr	eventProc;
} ChooseRec, *ChooseRecPtr;

/* ChooseRec messages */
#define		ctbChooseNoChangeHandle		1
#define		ctbChooseNoDialog			2
#define		ctbChooseNoChangeTool		4

/*	 messages to the choo resource */
#define 	ChooseCM 	0
#define		ChooseTM	1
#define		ChooseFT	2


// 	ICON LDEF data structures
/* IconLDEF cell data		*/
typedef struct CellDataBlock {
	long	icon[32];
	long	mask[32];
	Str255	title;
} CellDataBlock, *CellDataP, **CellDataH;

typedef struct NewCellDataBlock { /* Structure of new icon ldef's Data */
	Handle	cHand;
	short	cFont;
	Style	cFace;
	Str255	cName;
} NewCellDataBlock, *NewCellDataBlockP, **NewCellDataBlockH;

/* CommToolboxLDEF private data	*/
typedef struct IconPrivateBlock {
	Boolean		unused;					// has to be here for CTB 1.0 compatibility
	short		procID;					/* res refnum for the tool	*/
	NewCellDataBlockH tempData;				/* Data for new IconLDEF */
} IconPrivateBlock, *IconPrivateP, **IconPrivateH;


// generic structure for converting finf and flst resources
typedef struct TextState {
	short		theFont;
	Style		theFace;
	short		theSize;
	short		theMode;
} TextState, *TextStatePtr;

// Accessing QD Globals
typedef	struct	{
	char		privates[76];
	long 		randSeed;
	BitMap 		screenBits;
	Cursor 		arrow;
	Pattern 	dkGray;							// we really care only for the patterns
	Pattern 	ltGray;
	Pattern 	gray;
	Pattern 	black;
	Pattern 	white;
	GrafPtr 	thePort;
}	GrafWorld, *GrafWorldPtr;

//	routines in CommToolboxUtilityRoutines
pascal short	FindMenuItem(MenuHandle, ConstStr255Param);
pascal OSErr	GetIndflst(Handle hInfo, Boolean oldStyle,
										short index, TextState *finfInfo);
pascal void 	DoSolidOutline(DialogPtr pDialog, short theItem);
pascal void 	DoGrayOutline(DialogPtr pDialog, short theItem);
pascal void		DoTheIcon(Ptr theIcon, const Rect *destRect, Boolean selected);
pascal GrafWorldPtr GetQDGlobals(void);
pascal void 	GetItemRect(DialogPtr, short, Rect *);
pascal void 	SetUserItemProc(DialogPtr, short, ProcPtr);
pascal void 	PCopyString(ConstStr255Param, Str255);
pascal Boolean 	CmdPeriod(EventRecord *);
pascal void		GetTextState(TextState *txState);
pascal void		SetTextState(TextState *txState);
pascal void 	Getflst(short procID, short resourceID,
										short finfIndex, TextState *finfInfo);
pascal Point 	PlaceWindow(WindowPtr theParent,short childHeight,short childWidth);

//	CommToolbox Utilities Core
/* Common Tool Messages */
#define	CTBInitMsg 			0
#define	CTBDisposeMsg 		1

#define	CTBSuspendMsg		2
#define	CTBResumeMsg		3

#define	CTBMenuMsg			4
#define	CTBEventMsg			5

#define CTBActivateMsg	    6
#define CTBDeactivateMsg 	7

/* except for connection manager since I BBH f*cked up */
#define CTBGetErrorStringMsg 8

#define CTBIdleMsg 50
#define	CTBResetMsg 51
#define CTBAbortMsg 52


#define	CTBValidateMsg	0
#define	CTBDefaultMsg	1

// case these later
#define CTBPreflightMsg	0
#define CTBSetupMsg		1
#define CTBItemMsg		2
#define CTBFilterMsg	3
#define CTBCleanupMsg	4


#define CTBGetMsg		0
#define CTBSetMsg		1

#define CTB2EnglishMsg	0
#define CTB2IntlMsg		1

// DITL package selectors
#define	AppendMsg		1
#define CountMsg		2
#define ShortenMsg		3


typedef struct CoreRecord {				// looks pretty common to ConnRecord, TermRecord, FTRecord
	short	procID;

	long	flags;
	OSErr	errCode;

	long	refCon;
	long	userData;

	ProcPtr	defProc;

	Ptr		config;
	Ptr		oldConfig;

	long	reserved0;
	long	reserved1;
	long	reserved2;
} CoreRecord, *CorePtr, **CoreHandle;

pascal short InitManager(short selector);

/* core setup misceallaneous routines */
pascal void CTBGetToolName(short procID, Str255 name, short mgrSel);
pascal short CTBGetProcID(ConstStr255Param name, short mgrSel);
pascal Handle CTBGetVersion(CoreHandle, short mgrSel);

/* core validate  routines */
pascal Boolean CTBValidate(CoreHandle, short mgrSel);
pascal void CTBDefault(Ptr *config, short procID, Boolean allocate, short mgrSel);

/* core setup routines */
pascal Handle CTBSetupPreflight(short procID, long *magicCookie, short mgrSel);

pascal Boolean CTBSetupFilter(short procID, Ptr theConfig, short count, DialogPtr, EventRecord *,
	short *theItem, long *magicCookie, short mgrSel);

pascal void CTBSetupSetup(short procID, Ptr theConfig, short count, DialogPtr, long *magicCookie,
	short mgrSel);

pascal void CTBSetupItem(short procID, Ptr theConfig, short count, DialogPtr, short *item,
	long *magicCookie, short mgrSel);

pascal void CTBSetupCleanup(short procID, Ptr theConfig, short count, DialogPtr, long *magicCookie,
	short mgrSel);
pascal void CTBSetupXCleanup(short procID, Ptr theConfig, short count, DialogPtr, Boolean OKed,
	long *magicCookie, short mgrSel);

pascal void CTBSetupPostflight(short procID, short mgrSel);


/* core scripting routines */
pascal Ptr CTBGetConfig(CoreHandle, short mgrSel);

pascal short CTBSetConfig(CoreHandle, Ptr thePtr, short mgrSel);


/* core localization routines */
pascal short CTBIntlToEnglish(CoreHandle,
						Ptr inputPtr, Ptr *outputPtr, short language, short mgrSel);

pascal short CTBEnglishToIntl(CoreHandle,
						Ptr inputPtr, Ptr *outputPtr, short language, short mgrSel);

/* core choose routines */
pascal short CTBChoose(CoreHandle *, Point where, ProcPtr idleProc, short mgrSel);
pascal short CTBPChoose(CoreHandle *, Point where, ChooseRec *, short mgrSel);


/* core utility routines - these reside in CommToolboxUtilityRoutines.c */
pascal Handle CRMGetAResource(ResType, short procID);


//	Note that SetupStruct has been renamed CM/FT/TMSetupStruct but the core routines
//		use SetupStruct so the next line could very well have been #def SetupStruct TMSetupStruct

#define SetupStruct	CMSetupStruct

//	selectors for the various code routines
#define	CMSel			0
#define	TMSel			1
#define FTSel			2

// 	selectors for the tool res types
#define		BndType			0
#define		DefType			1
#define		ValType			2
#define		SetType			3
#define		ScrType			4
#define		LocType			5

//	common error code for no tools in response to InitXXX()
#define CTBNoTools		8


#endif
