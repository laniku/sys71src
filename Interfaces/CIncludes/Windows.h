
/************************************************************

Created: Saturday, July 27, 1991 at 7:34 PM
 Windows.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1992
  All rights reserved.


	Change History (most recent first):

		<17>	 7/28/92	DCL		Moving applicationFloatKind & systemFloatKind constants out of
									the public eye and into the private Layers header file. At the
									request of TechPubs, and with assistance from Dean, Greg and
									Kenny.
		<16>	 7/13/92	DCL		Changed prototype of DragGrayRgn boundsRect to limitRect to
									match Inside Mac. (as requested by NIIM writers)
		<15>	 5/11/92	JH		#1029361 <KST>: Adding to new Window kinds for floating windows.
		<14>	 7/31/91	JL		Updated Copyright.
		<13>	 1/27/91	LN		Checked in Database generate file from DSG.
		<11>	11/26/90	JL		Checked in GetNewCWindow Ptr parameter to a void *
		<10>	11/13/90	JL		Bad checkIn of last version.
		 <9>	11/13/90	JL		Put formal parameters back in functions.
		 <8>	 11/4/90	dba		got rid of some extraneous parameter names; made some parameters
									void* instead of Ptr; used constStr255Parameter
		 <7>	10/30/90	dba		make smaller version of GetGrayRgn() (using #define)
		 <6>	10/24/90	JL		Changed all #defines to anonymous enums.
		 <5>	10/18/90	VL		Fixed the comment <4>. No code change.
		 <4>	10/18/90	VL		(jsm) Added new variant for movable modal dialog (5).
** <3>	JAL 10/09/1990 Added Inline to GetGrayRgn.
** <2>	JAL 02/15/1990 Changed AuxWinHndl to AuxWinHandle to match I.M.
** 1.4	EMT 12/11/1989 Moved all layer stuff to Layers.h.
** 1.3	EMT 06/27/1989 Added auxiliary lists to layer record.
** 1.2	CCH 05/15/1989 Submitted from System project.
** 1.0	EMT 05/13/1989 Added layer stuff.

************************************************************/


#ifndef __WINDOWS__
#define __WINDOWS__

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif

#ifndef __EVENTS__
#include <Events.h>
#endif

#ifndef __CONTROLS__
#include <Controls.h>
#endif


enum {

 documentProc = 0,
 dBoxProc = 1,
 plainDBox = 2,
 altDBoxProc = 3,
 noGrowDocProc = 4,
 movableDBoxProc = 5,
 zoomDocProc = 8,
 zoomNoGrow = 12,
 rDocProc = 16,
 dialogKind = 2,
 userKind = 8,

/*FindWindow Result Codes*/
 inDesk = 0,
 inMenuBar = 1,
 inSysWindow = 2,
 inContent = 3,
 inDrag = 4,
 inGrow = 5,
 inGoAway = 6,
 inZoomIn = 7,
 inZoomOut = 8
};
enum {

/*window messages*/
 wDraw = 0,
 wHit = 1,
 wCalcRgns = 2,
 wNew = 3,
 wDispose = 4,
 wGrow = 5,
 wDrawGIcon = 6,

/*defProc hit test codes*/
 wNoHit = 0,
 wInContent = 1,
 wInDrag = 2,
 wInGrow = 3,
 wInGoAway = 4,
 wInZoomIn = 5,
 wInZoomOut = 6,
 deskPatID = 16,

/*Window Part Identifiers which correlate color table entries with window elements*/
 wContentColor = 0,
 wFrameColor = 1,
 wTextColor = 2,
 wHiliteColor = 3,
 wTitleBarColor = 4
};


typedef pascal void (*DragGrayRgnProcPtr)(void);

struct WindowRecord {
 GrafPort port;
 short windowKind;
 Boolean visible;
 Boolean hilited;
 Boolean goAwayFlag;
 Boolean spareFlag;
 RgnHandle strucRgn;
 RgnHandle contRgn;
 RgnHandle updateRgn;
 Handle windowDefProc;
 Handle dataHandle;
 StringHandle titleHandle;
 short titleWidth;
 ControlHandle controlList;
 struct WindowRecord *nextWindow;
 PicHandle windowPic;
 long refCon;
};

typedef struct WindowRecord WindowRecord;
typedef WindowRecord *WindowPeek;

struct CWindowRecord {
 CGrafPort port;
 short windowKind;
 Boolean visible;
 Boolean hilited;
 Boolean goAwayFlag;
 Boolean spareFlag;
 RgnHandle strucRgn;
 RgnHandle contRgn;
 RgnHandle updateRgn;
 Handle windowDefProc;
 Handle dataHandle;
 StringHandle titleHandle;
 short titleWidth;
 ControlHandle controlList;
 struct CWindowRecord *nextWindow;
 PicHandle windowPic;
 long refCon;
};

typedef struct CWindowRecord CWindowRecord;
typedef CWindowRecord *CWindowPeek;

struct WStateData {
 Rect userState;				/*user state*/
 Rect stdState;					/*standard state*/
};

typedef struct WStateData WStateData;
typedef WStateData *WStateDataPtr, **WStateDataHandle;

struct AuxWinRec {
 struct AuxWinRec **awNext;		/*handle to next AuxWinRec*/
 WindowPtr awOwner;				/*ptr to window */
 CTabHandle awCTable;			/*color table for this window*/
 Handle dialogCItem;			/*handle to dialog manager structures*/
 long awFlags;					/*reserved for expansion*/
 CTabHandle awReserved;			/*reserved for expansion*/
 long awRefCon;					/*user Constant*/
};

typedef struct AuxWinRec AuxWinRec;
typedef AuxWinRec *AuxWinPtr, **AuxWinHandle;

struct WinCTab {
 long wCSeed;					/*reserved*/
 short wCReserved;				/*reserved*/
 short ctSize;					/*usually 4 for windows*/
 ColorSpec ctTable[5];
};

typedef struct WinCTab WinCTab;
typedef WinCTab *WCTabPtr, **WCTabHandle;


#ifdef __cplusplus
extern "C" {
#endif
pascal void InitWindows(void)
 = 0xA912; 
pascal void GetWMgrPort(GrafPtr *wPort)
 = 0xA910; 
pascal WindowPtr NewWindow(void *wStorage,const Rect *boundsRect,ConstStr255Param title,
 Boolean visible,short theProc,WindowPtr behind,Boolean goAwayFlag,long refCon)
 = 0xA913; 
pascal WindowPtr GetNewWindow(short windowID,void *wStorage,WindowPtr behind)
 = 0xA9BD; 
pascal void CloseWindow(WindowPtr theWindow)
 = 0xA92D; 
pascal void DisposeWindow(WindowPtr theWindow)
 = 0xA914; 
void setwtitle(WindowPtr theWindow,char *title); 
pascal void GetWTitle(WindowPtr theWindow,Str255 title)
 = 0xA919; 
pascal void SelectWindow(WindowPtr theWindow)
 = 0xA91F; 
pascal void HideWindow(WindowPtr theWindow)
 = 0xA916; 
pascal void ShowWindow(WindowPtr theWindow)
 = 0xA915; 
pascal void ShowHide(WindowPtr theWindow,Boolean showFlag)
 = 0xA908; 
pascal void HiliteWindow(WindowPtr theWindow,Boolean fHilite)
 = 0xA91C; 
pascal void BringToFront(WindowPtr theWindow)
 = 0xA920; 
pascal void SendBehind(WindowPtr theWindow,WindowPtr behindWindow)
 = 0xA921; 
pascal WindowPtr FrontWindow(void)
 = 0xA924; 
pascal void DrawGrowIcon(WindowPtr theWindow)
 = 0xA904; 
pascal void MoveWindow(WindowPtr theWindow,short hGlobal,short vGlobal,
 Boolean front)
 = 0xA91B; 
pascal void SizeWindow(WindowPtr theWindow,short w,short h,Boolean fUpdate)
 = 0xA91D; 
pascal void ZoomWindow(WindowPtr theWindow,short partCode,Boolean front)
 = 0xA83A; 
pascal void InvalRect(const Rect *badRect)
 = 0xA928; 
pascal void InvalRgn(RgnHandle badRgn)
 = 0xA927; 
pascal void ValidRect(const Rect *goodRect)
 = 0xA92A; 
pascal void ValidRgn(RgnHandle goodRgn)
 = 0xA929; 
pascal void BeginUpdate(WindowPtr theWindow)
 = 0xA922; 
pascal void EndUpdate(WindowPtr theWindow)
 = 0xA923; 
pascal void SetWRefCon(WindowPtr theWindow,long data)
 = 0xA918; 
pascal long GetWRefCon(WindowPtr theWindow)
 = 0xA917; 
pascal void SetWindowPic(WindowPtr theWindow,PicHandle pic)
 = 0xA92E; 
pascal PicHandle GetWindowPic(WindowPtr theWindow)
 = 0xA92F; 
pascal Boolean CheckUpdate(EventRecord *theEvent)
 = 0xA911; 
pascal void ClipAbove(WindowPeek window)
 = 0xA90B; 
pascal void SaveOld(WindowPeek window)
 = 0xA90E; 
pascal void DrawNew(WindowPeek window,Boolean update)
 = 0xA90F; 
pascal void PaintOne(WindowPeek window,RgnHandle clobberedRgn)
 = 0xA90C; 
pascal void PaintBehind(WindowPeek startWindow,RgnHandle clobberedRgn)
 = 0xA90D; 
pascal void CalcVis(WindowPeek window)
 = 0xA909; 
pascal void CalcVisBehind(WindowPeek startWindow,RgnHandle clobberedRgn)
 = 0xA90A; 
pascal long GrowWindow(WindowPtr theWindow,Point startPt,const Rect *bBox)
 = 0xA92B; 
Boolean trackgoaway(WindowPtr theWindow,Point *thePt); 
pascal short FindWindow(Point thePoint,WindowPtr *theWindow)
 = 0xA92C; 
short findwindow(Point *thePoint,WindowPtr *theWindow); 
pascal long PinRect(const Rect *theRect,Point thePt)
 = 0xA94E; 
pascal long DragGrayRgn(RgnHandle theRgn,Point startPt,const Rect *limitRect,
 const Rect *slopRect,short axis,DragGrayRgnProcPtr actionProc)
 = 0xA905; 
pascal Boolean TrackBox(WindowPtr theWindow,Point thePt,short partCode)
 = 0xA83B; 
pascal void GetCWMgrPort(CGrafPtr *wMgrCPort)
 = 0xAA48; 
void getwtitle(WindowPtr theWindow,char *title); 
pascal void SetWinColor(WindowPtr theWindow,WCTabHandle newColorTable)
 = 0xAA41; 
pascal Boolean GetAuxWin(WindowPtr theWindow,AuxWinHandle *awHndl)
 = 0xAA42; 
long growwindow(WindowPtr theWindow,Point *startPt,const Rect *bBox); 
pascal void SetDeskCPat(PixPatHandle deskPixPat)
 = 0xAA47; 
WindowPtr newwindow(void *wStorage,const Rect *boundsRect,char *title,Boolean visible,
 short theProc,WindowPtr behind,Boolean goAwayFlag,long refCon); 
pascal WindowPtr NewCWindow(void *wStorage,const Rect *boundsRect,ConstStr255Param title,
 Boolean visible,short procID,WindowPtr behind,Boolean goAwayFlag,long refCon)
 = 0xAA45; 
WindowPtr newcwindow(void *wStorage,const Rect *boundsRect,char *title,
 Boolean visible,short procID,WindowPtr behind,Boolean goAwayFlag,long refCon); 
pascal WindowPtr GetNewCWindow(short windowID,void *wStorage,WindowPtr behind)
 = 0xAA46; 
pascal short GetWVariant(WindowPtr theWindow)
 = 0xA80A; 
long pinrect(const Rect *theRect,Point *thePt); 
#define GetGrayRgn() (* (RgnHandle*) 0x09EE)
pascal void SetWTitle(WindowPtr theWindow,ConstStr255Param title)
 = 0xA91A; 
Boolean trackbox(WindowPtr theWindow,Point *thePt,short partCode); 
pascal Boolean TrackGoAway(WindowPtr theWindow,Point thePt)
 = 0xA91E; 
pascal void DragWindow(WindowPtr theWindow,Point startPt,const Rect *boundsRect)
 = 0xA925; 
long draggrayrgn(RgnHandle theRgn,Point *startPt,const Rect *boundsRect,
 const Rect *slopRect,short axis,DragGrayRgnProcPtr actionProc); 
void dragwindow(WindowPtr theWindow,Point *startPt,const Rect *boundsRect); 
#ifdef __cplusplus
}
#endif

#endif
