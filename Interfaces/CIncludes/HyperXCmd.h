/*
    HyperXCmd.h
    Definition file for HyperCard XCMDs and XFCNs in C.
    Copyright Apple Computer, Inc.  1987-1991
    All rights reserved
    This file is used in these builds: ROM System

			
				Change History (most recent first):
			
		 <5>	 2/17/92	MH		This is now the same as what's shipping to developers.  Some
									function prototypes have been corrected, including changing
									extended arguments to extended80.
		 <4>	  8/8/91	JL		Update copyright
		 <3>	 3/13/91	JL		Checked in MPW version.  Hypercard version 2.0 final.
			
				To Do:
*/


#ifndef	__HYPERXCMD__
#define	__HYPERXCMD__


/* Unlike the old days, we have to make sure we have some definitions first… */

#ifndef  __TYPES__
#include <Types.h>
#endif

#ifndef __EVENTS__
#include <Events.h>
#endif

#ifndef __TEXTEDIT__
#include <TextEdit.h>
#endif

#ifndef __MENUS__
#include <Menus.h>
#endif

#ifndef __STANDARDFILE__
#include <StandardFile.h>
#endif



/* result codes */
#define xresSucc				0
#define xresFail				1
#define xresNotImp				2

/* XCMDBlock constants for event.what... */
#define xOpenEvt				1000	/* the first event after you are created */
#define xCloseEvt				1001	/* your window is being forced close (Quit?) */
#define xGiveUpEditEvt			1002	/* you are losing Edit... */
#define xGiveUpSoundEvt			1003	/* you are losing the sound channel... */
#define xHidePalettesEvt		1004	/* someone called HideHCPalettes */
#define xShowPalettesEvt		1005	/* someone called ShowHCPalettes */
#define xEditUndo				1100	/* Edit——Undo */
#define xEditCut				1102	/* Edit——Cut */
#define xEditCopy				1103	/* Edit——Copy */
#define xEditPaste				1104	/* Edit——Paste */
#define xEditClear				1105	/* Edit——Clear */
#define xSendEvt				1200	/* script has sent you a message (text) */
#define xSetPropEvt				1201	/* set a window property */
#define xGetPropEvt				1202	/* get a window property */
#define xCursorWithin			1300	/* cursor is within the window */
#define xMenuEvt				1400	/* user has selected an item in your menu */
#define xMBarClickedEvt			1401	/* a menu is about to be shown--update if needed */

#define xShowWatchInfoEvt		1501	/* for variable and message watchers */
#define xScriptErrorEvt			1502	/* place the insertion point */
#define xDebugErrorEvt			1503	/* user clicked "Debug" at a complaint */
#define xDebugStepEvt			1504	/* hilite the line */
#define xDebugTraceEvt			1505	/* same as step but tracing */
#define xDebugFinishedEvt		1506	/* script ended */

#define paletteProc				2048	/* Windoid with grow box */
#define palNoGrowProc			2052	/* standard Windoid defproc */
#define palZoomProc				2056	/* Windoid with zoom and grow */
#define palZoomNoGrow			2060	/* Windoid with zoom and no grow */
#define hasZoom					8
#define hasTallTBar				2
#define toggleHilite			1


#define maxCachedChecks			16		/* maximum number of checkpoints in a script */


/* paramCount is set to these constants when first calling special XThings */
#define xMessageWatcherID		= -2;
#define xVariableWatcherID		= -3;
#define xScriptEditorID			= -4;
#define xDebuggerID				= -5;

/* XTalkObjectPtr->objectKind values */
#define stackObj				1
#define bkgndObj				2
#define cardObj					3
#define fieldObj				4
#define buttonObj				5


typedef struct XCmdBlock *XCmdPtr; 
struct XCmdBlock {
	short paramCount;		 /* If = -1 then new use for XWindoids */
	Handle params[16];
	Handle returnValue;
	Boolean passFlag;

	Ptr entryPoint;			 /* to call back to HyperCard */
	short request;
	short result;
	long inArgs[8];
	long outArgs[4];
};

typedef struct XWEventInfo *XWEventInfoPtr; 
struct XWEventInfo {
	EventRecord event;
	WindowPtr eventWindow;
	long eventParams[9];
	Handle eventResult;
};

typedef struct XTalkObject *XTalkObjectPtr;
struct XTalkObject {
	short objectKind;		/* stack, bkgnd, card, field, or button */
	long stackNum;			/* reference number of the source stack */
	long bkgndID;
	long cardID;
	long buttonID;
	long fieldID;
};


typedef struct CheckPts *CheckPtPtr;
typedef CheckPtPtr *CheckPtHandle; 
struct CheckPts {
	short checks[maxCachedChecks];
};

#ifdef __cplusplus
extern "C" {
#endif

/****  HyperTalk Utilities  ****/
pascal Handle EvalExpr(XCmdPtr paramPtr, StringPtr expr);
pascal void SendCardMessage(XCmdPtr paramPtr, StringPtr msg);
pascal void SendHCMessage(XCmdPtr paramPtr, StringPtr msg);
pascal void RunHandler(XCmdPtr paramPtr, Handle handler);

/****  Memory Utilities  ****/
pascal Handle GetGlobal(XCmdPtr paramPtr, StringPtr globName);
pascal void SetGlobal(XCmdPtr paramPtr, StringPtr globName, Handle globValue);
pascal void ZeroBytes(XCmdPtr paramPtr, Ptr dstPtr, long longCount);

/****  String Utilities  ****/
pascal void ScanToReturn(XCmdPtr paramPtr, Ptr *scanPtr);
pascal void ScanToZero(XCmdPtr paramPtr, Ptr *scanPtr);
pascal Boolean StringEqual(XCmdPtr paramPtr, StringPtr str1, StringPtr str2);
pascal long StringLength(XCmdPtr paramPtr, Ptr strPtr);
pascal Ptr StringMatch(XCmdPtr paramPtr, StringPtr pattern, Ptr target);
pascal void ZeroTermHandle(XCmdPtr paramPtr, Handle hndl);								

/****  String Conversions  ****/
pascal void BoolToStr(XCmdPtr paramPtr, Boolean bool, StringPtr str);
pascal void ExtToStr(XCmdPtr paramPtr, extended80 num, StringPtr str);
pascal void LongToStr(XCmdPtr paramPtr, long posNum, StringPtr str);
pascal void NumToHex(XCmdPtr paramPtr, long num, short nDigits, StringPtr str);
pascal void NumToStr(XCmdPtr paramPtr, long num, StringPtr str);
pascal Handle PasToZero(XCmdPtr paramPtr, StringPtr str);
pascal void PointToStr(XCmdPtr paramPtr, Point pt, StringPtr str);						
pascal void RectToStr(XCmdPtr paramPtr, Rect *rct, StringPtr str);						
pascal void ReturnToPas(XCmdPtr paramPtr, Ptr zeroStr, StringPtr pasStr);
pascal Boolean StrToBool(XCmdPtr paramPtr, StringPtr str);
pascal extended80 StrToExt(XCmdPtr paramPtr, StringPtr str);
pascal long StrToLong(XCmdPtr paramPtr, StringPtr str);
pascal long StrToNum(XCmdPtr paramPtr, StringPtr str);
pascal void StrToPoint(XCmdPtr paramPtr, StringPtr str, Point *pt);						
pascal void StrToRect(XCmdPtr paramPtr, StringPtr str, Rect *rct);						
pascal void ZeroToPas(XCmdPtr paramPtr, Ptr zeroStr, StringPtr pasStr);

/****  Field Utilities  ****/
pascal Handle GetFieldByID(XCmdPtr paramPtr, Boolean cardFieldFlag, short fieldID);
pascal Handle GetFieldByName(XCmdPtr paramPtr, Boolean cardFieldFlag, StringPtr fieldName);
pascal Handle GetFieldByNum(XCmdPtr paramPtr, Boolean cardFieldFlag, short fieldNum);
pascal void SetFieldByID(XCmdPtr paramPtr, Boolean cardFieldFlag, short fieldID,
	Handle fieldVal);
pascal void SetFieldByName(XCmdPtr paramPtr, Boolean cardFieldFlag,
	StringPtr fieldName, Handle fieldVal);
pascal void SetFieldByNum(XCmdPtr paramPtr, Boolean cardFieldFlag, short fieldNum,
	Handle fieldVal);
pascal TEHandle GetFieldTE(XCmdPtr paramPtr, Boolean cardFieldFlag, short fieldID,
	short fieldNum, StringPtr fieldNamePtr);													
pascal void SetFieldTE(XCmdPtr paramPtr, Boolean cardFieldFlag, short fieldID,
	short fieldNum, StringPtr fieldNamePtr, TEHandle fieldTE);									

/****  Miscellaneous Utilities  ****/  /* ALL NEW */
pascal void BeginXSound(XCmdPtr paramPtr, WindowPtr window);
pascal void EndXSound(XCmdPtr paramPtr);
pascal Boolean GetFilePath(XCmdPtr paramPtr, StringPtr fileName, short numTypes, SFTypeList typeList,
	Boolean askUser, OSType *fileType, StringPtr fullName);
pascal void GetXResInfo(XCmdPtr paramPtr, short *resFile, short *resID, ResType *rType, StringPtr name);
pascal void Notify(XCmdPtr paramPtr);
pascal void SendHCEvent(XCmdPtr paramPtr, EventRecord *event);
pascal void SendWindowMessage(XCmdPtr paramPtr, WindowPtr windPtr, 
	StringPtr windowName, Handle msg);
pascal WindowPtr FrontDocWindow(XCmdPtr paramPtr);
pascal long StackNameToNum(XCmdPtr paramPtr, StringPtr stackName);
pascal short ShowHCAlert(XCmdPtr paramPtr, short dlgID, StringPtr promptStr);

/****  Creating and Disposing XWindoids  ****/  /* ALL NEW */
pascal WindowPtr NewXWindow(XCmdPtr paramPtr, Rect *boundsRect, StringPtr title, 
   Boolean visible, short procID, Boolean color, Boolean floating);
pascal WindowPtr GetNewXWindow(XCmdPtr paramPtr, ResType templateType, short 
   templateID, Boolean color, Boolean floating);
pascal void CloseXWindow(XCmdPtr paramPtr, WindowPtr window);

/****  XWindoid Utilities  ****/  /* ALL NEW */
pascal void HideHCPalettes(XCmdPtr paramPtr);
pascal void ShowHCPalettes(XCmdPtr paramPtr);
pascal void RegisterXWMenu(XCmdPtr paramPtr, WindowPtr window, MenuHandle menu, Boolean registering);
pascal void SetXWIdleTime(XCmdPtr paramPtr, WindowPtr window, long interval);
pascal void XWHasInterruptCode(XCmdPtr paramPtr, WindowPtr window, Boolean haveCode);
pascal void XWAlwaysMoveHigh(XCmdPtr paramPtr, WindowPtr window, Boolean moveHigh);
pascal void XWAllowReEntrancy(XCmdPtr paramPtr, WindowPtr window, Boolean allowSysEvts, Boolean allowHCEvts);

/****  Text Editing Utilities  ****/  /* ALL NEW */
pascal void BeginXWEdit(XCmdPtr paramPtr, WindowPtr window);
pascal void EndXWEdit(XCmdPtr paramPtr, WindowPtr window);
pascal Ptr HCWordBreakProc(XCmdPtr paramPtr);
pascal void PrintTEHandle(XCmdPtr paramPtr, TEHandle hTE, StringPtr header);

/****  Script Editor support  ****/  /* ALL NEW */
pascal CheckPtHandle GetCheckPoints(XCmdPtr paramPtr);
pascal void SetCheckPoints(XCmdPtr paramPtr, CheckPtHandle checkLines);
pascal void FormatScript(XCmdPtr paramPtr, Handle scriptHndl, long *insertionPoint, Boolean quickFormat);
pascal void SaveXWScript(XCmdPtr paramPtr, Handle scriptHndl);
pascal void GetObjectName(XCmdPtr paramPtr, XTalkObjectPtr object, StringPtr objName);
pascal void GetObjectScript(XCmdPtr paramPtr, XTalkObjectPtr object, Handle *scriptHndl);
pascal void SetObjectScript(XCmdPtr paramPtr, XTalkObjectPtr object, Handle scriptHndl);

/****  Debugging Tools support  ****/  /* ALL NEW */
pascal void AbortScript(XCmdPtr paramPtr);
pascal void GoScript(XCmdPtr paramPtr);
pascal void StepScript(XCmdPtr paramPtr, Boolean stepInto);
pascal void CountHandlers(XCmdPtr paramPtr, short *handlerCount);
pascal void GetHandlerInfo(XCmdPtr paramPtr, short handlerNum, StringPtr handlerName, 
								  StringPtr objectName, short *varCount);
pascal void GetVarInfo(XCmdPtr paramPtr, short handlerNum, short varNum, StringPtr varName, 
							  Boolean *isGlobal, StringPtr varValue, Handle varHndl);
pascal void SetVarValue(XCmdPtr paramPtr, short handlerNum, short varNum, Handle varHndl);
pascal Handle GetStackCrawl(XCmdPtr paramPtr);
pascal void TraceScript(XCmdPtr paramPtr, Boolean traceInto);

#ifdef __cplusplus
}
#endif


#endif
