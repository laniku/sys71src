/************************************************************
	Terminals.h
	C Interface to the Terminal Manager

		Copyright Apple Computer, Inc. 1988-1991
		All rights reserved

    This file is used in these builds: Mac32 HcMac MacPP

	Change History (most recent first):

		<16>	  4/1/92	DCL		Fixed TerminalEnvironsProcPtr. #1024102
		<15>	 8/28/91	CH		Updated interface headers for consistency.
		<14>	 8/20/91	BH		remove TMSetupCleanup from public interfaces
		<13>	 7/25/91	JL		Checked in database generated file from DSG.  Changed #defines
									to enums.  Changed enum types to unsigned.
		<12>	  7/2/91	BH		added application callback type definitions
		<11>	 6/25/91	JNG		Added tmConfigChanged
		<10>	 6/18/91	BH		remove TMPChoose
		 <9>	 6/17/91	JL		Checked in official MPW 3.2Ä version. Added and deleted blank
									lines to match shipped version.
		 <8>	 1/29/91	JL		Put parameter names back in.
		 <6>	 11/4/90	dba		got rid of some extraneous parameter names; made some parameters
									void* instead of Ptr; used constStr255Parameter
		 <4>	 10/9/90	JAL		Updated CPLUSPLUS constraints.
		 <4>	 10/3/90	kaz		Changing // comments for ANSI compatibility. <jng>
		 <3>	 8/28/90	kaz		Changed TermPointer to TermPtr.
		 <2>	 3/14/90	BBH		fix includes
		 <1>	 3/12/90	BBH		first checked in
************************************************************/


#ifndef __TERMINALS__
#define __TERMINALS__

#ifndef __DIALOGS__
#include <Dialogs.h>
#endif

#ifndef __CTBUTILITIES__
#include <CTBUtilities.h>
#endif

#ifndef __CONNECTIONS__
#include <Connections.h>
#endif


enum {


/* current Terminal Manager version 	*/
 curTMVersion = 2,

/* current Terminal Manager Environment Record version 	*/
 curTermEnvRecVers = 0,

/* error codes    */
 tmGenericError = -1,
 tmNoErr = 0,
 tmNotSent = 1,
 tmEnvironsChanged = 2,
 tmNotSupported = 7,
 tmNoTools = 8
};

typedef	OSErr TMErr;

enum {tmInvisible 		= 1 << 0,tmSaveBeforeClear 	= 1 << 1,tmNoMenus 			= 1 << 2,
	tmAutoScroll 		= 1 << 3,tmConfigChanged		= 1 << 4};
typedef unsigned long TMFlags;

enum {selTextNormal 		= 1 << 0,selTextBoxed 		= 1 << 1,selGraphicsMarquee 	= 1 << 2,
	selGraphicsLasso 	= 1 << 3,tmSearchNoDiacrit 	= 1 << 8	/*	These are only for TMSearchTypes	*/,
	tmSearchNoCase 		= 1 << 9};
typedef unsigned short TMSearchTypes;


typedef short TMSelTypes;

enum {cursorText = 1,cursorGraphics = 2};
typedef unsigned short TMCursorTypes;

enum {tmTextTerminal 		= 1 << 0,tmGraphicsTerminal 	= 1 << 1};
typedef unsigned short TMTermTypes;


struct TermDataBlock {
	TMTermTypes		flags;
	Handle			theData;
	Handle			auxData;
	long			reserved;
};

typedef struct TermDataBlock TermDataBlock;
typedef TermDataBlock *TermDataBlockPtr, **TermDataBlockH;

struct TermEnvironRec {
	short			version;
	TMTermTypes		termType;
	short			textRows;
	short			textCols;
	Point			cellSize;
	Rect			graphicSize;
	Point			slop;
	Rect			auxSpace;
};

typedef struct TermEnvironRec TermEnvironRec;
typedef TermEnvironRec *TermEnvironPtr;

union TMSelection {
	Rect			selRect;
	RgnHandle		selRgnHandle;
};

typedef union TMSelection TMSelection;

/*    TMTermTypes     */
struct TermRecord {
		short			procID;
		TMFlags			flags;
		TMErr			errCode;
		long			refCon;
		long			userData;
		ProcPtr			defProc;
		Ptr				config;
		Ptr				oldConfig;
		ProcPtr			environsProc;
		long			reserved1;
		long			reserved2;
		Ptr				tmPrivate;
		ProcPtr			sendProc;
		ProcPtr			breakProc;
		ProcPtr			cacheProc;
		ProcPtr			clikLoop;
		WindowPtr		owner;
		Rect			termRect;
		Rect			viewRect;
		Rect			visRect;
		long			lastIdle;
		TMSelection		selection;
		TMSelTypes		selType;
		long			mluField;
};

typedef struct TermRecord TermRecord;
typedef TermRecord *TermPtr, **TermHandle;


/*	application routines type definitions */
typedef pascal long  	(*TerminalSendProcPtr) (Ptr thePtr, long theSize, long refCon, CMFlags flags);
typedef pascal void  	(*TerminalBreakProcPtr) (long duration, long refCon);
typedef pascal long  	(*TerminalCacheProcPtr) (long refCon, TermDataBlock theTermData);
typedef pascal void  	(*TerminalSearchCallBackProcPtr) (TermHandle hTerm, short refNum, Rect foundRect);
typedef pascal Boolean	(*TerminalClikLoopProcPtr) (long refCon);
typedef pascal CMErr  	(*TerminalEnvironsProcPtr) (long refCon, ConnEnvironRec *theEnvirons);
typedef pascal void  	(*TerminalChooseIdleProcPtr) (void);

#ifdef __cplusplus
extern "C" {
#endif
pascal TMErr 	InitTM(void);
pascal Handle 	TMGetVersion(TermHandle hTerm);
pascal short 	TMGetTMVersion(void);

pascal TermHandle TMNew(const Rect *termRect,const Rect *viewRect,TMFlags flags,
 short procID,WindowPtr owner,TerminalSendProcPtr sendProc,TerminalCacheProcPtr cacheProc,
 TerminalBreakProcPtr breakProc,TerminalClikLoopProcPtr clikLoop,TerminalEnvironsProcPtr environsProc,
 long refCon,long userData);

pascal void 	TMDispose(TermHandle hTerm);

pascal void 	TMKey(TermHandle hTerm,const EventRecord *theEvent);
pascal void 	TMUpdate(TermHandle hTerm,RgnHandle visRgn);
pascal void 	TMPaint(TermHandle hTerm,const TermDataBlock *theTermData,const Rect *theRect);
pascal void 	TMActivate(TermHandle hTerm,Boolean activate);
pascal void 	TMResume(TermHandle hTerm,Boolean resume);
pascal void 	TMClick(TermHandle hTerm,const EventRecord *theEvent);
pascal void 	TMIdle(TermHandle hTerm);

pascal long 	TMStream(TermHandle hTerm,void *theBuffer,long theLength,CMFlags flags);
pascal Boolean 	TMMenu(TermHandle hTerm,short menuID,short item);

pascal void 	TMReset(TermHandle hTerm);
pascal void 	TMClear(TermHandle hTerm);

pascal void		TMResize(TermHandle hTerm,const Rect *newViewRect);

pascal long 	TMGetSelect(TermHandle hTerm,Handle theData,ResType *theType);
pascal void 	TMGetLine(TermHandle hTerm,short lineNo,TermDataBlock *theTermData);
pascal void 	TMSetSelection(TermHandle hTerm,const TMSelection *theSelection,
 TMSelTypes selType);

pascal void 	TMScroll(TermHandle hTerm,short dh,short dv);

pascal Boolean 	TMValidate(TermHandle hTerm);
pascal void 	TMDefault(Ptr *theConfig,short procID,Boolean allocate);

pascal Handle 	TMSetupPreflight(short procID,long *magicCookie);
pascal void 	TMSetupSetup(short procID,const void *theConfig,short count,
 DialogPtr theDialog,long *magicCookie);
pascal Boolean 	TMSetupFilter(short procID,const void *theConfig,short count,
 DialogPtr theDialog,EventRecord *theEvent,short *theItem,long *magicCookie);
pascal void 	TMSetupItem(short procID,const void *theConfig,short count,
 DialogPtr theDialog,short *theItem,long *magicCookie);
pascal void 	TMSetupXCleanup(short procID,const void *theConfig,short count,
 DialogPtr theDialog,Boolean OKed,long *magicCookie);
pascal void 	TMSetupPostflight(short procID);

pascal Ptr 		TMGetConfig(TermHandle hTerm);
pascal short 	TMSetConfig(TermHandle hTerm,const void *thePtr);

pascal OSErr 	TMIntlToEnglish(TermHandle hTerm,const void *inputPtr,Ptr *outputPtr,
 short language);
pascal OSErr 	TMEnglishToIntl(TermHandle hTerm,const void *inputPtr,Ptr *outputPtr,
 short language);

pascal void 	TMGetToolName(short id,Str255 name);
pascal short 	TMGetProcID(ConstStr255Param name);

pascal void 	TMSetRefCon(TermHandle hTerm,long refCon);
pascal long 	TMGetRefCon(TermHandle hTerm);

pascal void 	TMSetUserData(TermHandle hTerm,long userData);
pascal long 	TMGetUserData(TermHandle hTerm);

pascal short 	TMAddSearch(TermHandle hTerm,ConstStr255Param theString,const Rect *where,
							TMSearchTypes searchType,TerminalSearchCallBackProcPtr callBack);
pascal void 	TMRemoveSearch(TermHandle hTerm,short refnum);
pascal void 	TMClearSearch(TermHandle hTerm);

pascal Point 	TMGetCursor(TermHandle hTerm,TMCursorTypes cursType);

pascal TMErr 	TMGetTermEnvirons(TermHandle hTerm,TermEnvironRec *theEnvirons);

pascal short 	TMChoose(TermHandle *hTerm,Point where,TerminalChooseIdleProcPtr idleProc);

pascal void 	TMEvent(TermHandle hTerm,const EventRecord *theEvent);

pascal Boolean 	TMDoTermKey(TermHandle hTerm,ConstStr255Param theKey);
pascal short 	TMCountTermKeys(TermHandle hTerm);
pascal void 	TMGetIndTermKey(TermHandle hTerm,short id,Str255 theKey);

pascal void		TMGetErrorString(TermHandle hTerm,short id,Str255 errMsg);
#ifdef __cplusplus
}
#endif

#endif
