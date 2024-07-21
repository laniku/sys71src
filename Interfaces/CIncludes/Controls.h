
/************************************************************

Created: Tuesday, July 30, 1991 at 2:09 PM
 Controls.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1992
  All rights reserved


	Change History (most recent first):

		<SM2>	 11/16/92	CSS		Update from Reality:
									<16>	 11/7/92	JDR		Added the PopupPrivateData record.
		<SM1>	 10/26/92	CSS		Changes for allowing traps to be expanded inline rather than
									use trap dispatcher.
		<15>	 6/26/92	DCL		Miner Formatting Changes. Digging deep for things to do. Getting
									the file ready for ETO 8.
		<14>	 6/11/92	DCL		Cleanup minor formatting to match Interface Stacks. Happy Happy
									Joy Joy.
		<13>	  4/6/92	DCL		For New Inside Mac: Adding fancy new improved names for old
									crusty routines. #1025005
		<12>	 7/30/91	JL		Updated Copyright.
		<11>	 1/30/91	JL		Grouped enums into groups of 20
		<10>	 1/25/91	stb		JDR: adjust popupTitle… to explicitly 4 bytes long
		 <8>	 11/8/90	JL		Changed all #defines to anonymous enums
		 <7>	 11/4/90	dba		used constStr255Parameter; got rid of some extraneous parameter
									names; added UpdateControls (synonym for UpdtControl)
		 <6>	 9/15/90	PWD		Changed popupMenuProc to popupMenuCDEFProc. <kaz> <crz>
		 <5>	 9/15/90	PWD		Renamed popupUseCQD to popupReserved.<kaz> <crz>
		 <4>	  3/8/90	BBH		added calcCntlRgn and calcThumbRgn per TechNote 2xx or something
									(compatibility and 32bit cleanliness)
		 <3>	  3/5/90	BBH		added popup control stuff

************************************************************/


#ifndef __CONTROLS__
#define __CONTROLS__

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif

#ifndef __MENUS__
#include <Menus.h>
#endif

#ifndef	__ROMFastTrapsIncluded__
#include "ROMFastTraps.h"
#endif

enum {

 pushButProc = 0,
 checkBoxProc = 1,
 radioButProc = 2,
 useWFont = 8,
 scrollBarProc = 16,
 inButton = 10,
 inCheckBox = 11,
 inUpButton = 20,
 inDownButton = 21,
 inPageUp = 22,
 inPageDown = 23,
 inThumb = 129,

 popupMenuProc = 1008,		/* 63 * 16 */
 inLabel = 1,
 inMenu = 2,
 inTriangle = 4
};

enum { popupFixedWidth  = 1 << 0, popupReserved   = 1 << 1, popupUseAddResMenu = 1 << 2,
  popupUseWFont  = 1 << 3};

enum { popupTitleBold  = 1 << 8, popupTitleItalic = 1 << 9, popupTitleUnderline = 1 << 10,
  popupTitleOutline = 1 << 11, popupTitleShadow = 1 << 12, popupTitleCondense = 1 << 13,
  popupTitleExtend = 1 << 14, popupTitleNoStyle = 1 << 15};


enum {

 popupTitleLeftJust = 0x00000000,
 popupTitleCenterJust = 0x00000001,
 popupTitleRightJust = 0x000000FF,

/*
axis constraints for DragGrayRgn call*/
 noConstraint = 0,
 hAxisOnly = 1,
 vAxisOnly = 2,

/*
control messages*/
 drawCntl = 0,
 testCntl = 1,
 calcCRgns = 2,
 initCntl = 3,
 dispCntl = 4,
 posCntl = 5,
 thumbCntl = 6,
 dragCntl = 7,
 autoTrack = 8,
 calcCntlRgn = 10,
 calcThumbRgn = 11,

 cFrameColor = 0,
 cBodyColor = 1,
 cTextColor = 2
};
enum {
 cThumbColor = 3
};

struct ControlRecord {
 struct ControlRecord **nextControl;
 WindowPtr contrlOwner;
 Rect contrlRect;
 unsigned char contrlVis;
 unsigned char contrlHilite;
 short contrlValue;
 short contrlMin;
 short contrlMax;
 Handle contrlDefProc;
 Handle contrlData;
 ProcPtr contrlAction;
 long contrlRfCon;
 Str255 contrlTitle;
};

typedef struct ControlRecord ControlRecord;
typedef ControlRecord *ControlPtr, **ControlHandle;

struct PopupPrivateData {
 MenuHandle mHandle;		/*popup menu handle*/
 short mID;					/*popup menu ID*/
};

typedef struct PopupPrivateData PopupPrivateData;
typedef PopupPrivateData *PopupPrivateDataPtr, **PopupPrivateDataHandle;


struct CtlCTab {
 long ccSeed;				/*reserved*/
 short ccRider;				/*see what you have done - reserved*/
 short ctSize;				/*usually 3 for controls*/
 ColorSpec ctTable[4];
};

typedef struct CtlCTab CtlCTab;
typedef CtlCTab *CCTabPtr, **CCTabHandle;

struct AuxCtlRec {
 Handle acNext;				/*handle to next AuxCtlRec*/
 ControlHandle acOwner;		/*handle for aux record's control*/
 CCTabHandle acCTable;		/*color table for this control*/
 short acFlags;				/*misc flag byte*/
 long acReserved;			/*reserved for use by Apple*/
 long acRefCon;				/*for use by application*/
};

typedef struct AuxCtlRec AuxCtlRec;
typedef AuxCtlRec *AuxCtlPtr, **AuxCtlHandle;


#ifdef __cplusplus
extern "C" {
#endif
pascal ControlHandle NewControl(WindowPtr theWindow,const Rect *boundsRect,
 ConstStr255Param title,Boolean visible,short value,short min,short max,
 short procID,long refCon)
 = {__GenToolboxTrapCode(0xA954)}; 
pascal void SetControlTitle(ControlHandle theControl,ConstStr255Param title)
 = {__GenToolboxTrapCode(0xA95F)}; 
pascal void SetCTitle(ControlHandle theControl,ConstStr255Param title)
 = {__GenToolboxTrapCode(0xA95F)}; 
pascal void GetControlTitle(ControlHandle theControl,Str255 title)
 = {__GenToolboxTrapCode(0xA95E)}; 
pascal void GetCTitle(ControlHandle theControl,Str255 title)
 = {__GenToolboxTrapCode(0xA95E)}; 
pascal ControlHandle GetNewControl(short controlID,WindowPtr owner)
 = {__GenToolboxTrapCode(0xA9BE)}; 
pascal void DisposeControl(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA955)}; 
pascal void KillControls(WindowPtr theWindow)
 = {__GenToolboxTrapCode(0xA956)}; 
pascal void HideControl(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA958)}; 
pascal void ShowControl(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA957)}; 
pascal void DrawControls(WindowPtr theWindow)
 = {__GenToolboxTrapCode(0xA969)}; 
pascal void Draw1Control(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA96D)}; 
pascal void HiliteControl(ControlHandle theControl,short hiliteState)
 = {__GenToolboxTrapCode(0xA95D)}; 
pascal void UpdateControls(WindowPtr theWindow,RgnHandle updateRgn)
 = {__GenToolboxTrapCode(0xA953)}; 
pascal void UpdtControl(WindowPtr theWindow,RgnHandle updateRgn)
 = {__GenToolboxTrapCode(0xA953)}; 
pascal void MoveControl(ControlHandle theControl,short h,short v)
 = {__GenToolboxTrapCode(0xA959)}; 
pascal void SizeControl(ControlHandle theControl,short w,short h)
 = {__GenToolboxTrapCode(0xA95C)}; 
pascal void SetControlValue(ControlHandle theControl,short theValue)
 = {__GenToolboxTrapCode(0xA963)}; 
pascal void SetCtlValue(ControlHandle theControl,short theValue)
 = {__GenToolboxTrapCode(0xA963)}; 
pascal short GetControlValue(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA960)}; 
pascal short GetCtlValue(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA960)}; 
pascal void SetControlMinimum(ControlHandle theControl,short minValue)
 = {__GenToolboxTrapCode(0xA964)}; 
pascal void SetCtlMin(ControlHandle theControl,short minValue)
 = {__GenToolboxTrapCode(0xA964)}; 
pascal short GetControlMinimum(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA961)}; 
pascal short GetCtlMin(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA961)}; 
pascal void SetControlMaximum(ControlHandle theControl,short maxValue)
 = {__GenToolboxTrapCode(0xA965)}; 
pascal void SetCtlMax(ControlHandle theControl,short maxValue)
 = {__GenToolboxTrapCode(0xA965)}; 
pascal short GetControlMaximum(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA962)}; 
pascal short GetCtlMax(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA962)}; 
pascal void SetControlReference(ControlHandle theControl,long data)
 = {__GenToolboxTrapCode(0xA95B)}; 
pascal void SetCRefCon(ControlHandle theControl,long data)
 = {__GenToolboxTrapCode(0xA95B)}; 
pascal long GetControlReference(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA95A)}; 
pascal long GetCRefCon(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA95A)}; 
pascal void SetControlAction(ControlHandle theControl,ProcPtr actionProc)
 = {__GenToolboxTrapCode(0xA96B)}; 
pascal void SetCtlAction(ControlHandle theControl,ProcPtr actionProc)
 = {__GenToolboxTrapCode(0xA96B)}; 
pascal ProcPtr GetControlAction(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA96A)}; 
pascal ProcPtr GetCtlAction(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA96A)}; 
pascal void DragControl(ControlHandle theControl,Point startPt,const Rect *limitRect,
 const Rect *slopRect,short axis)
 = {__GenToolboxTrapCode(0xA967)}; 
pascal short TestControl(ControlHandle theControl,Point thePt)
 = {__GenToolboxTrapCode(0xA966)}; 
pascal short TrackControl(ControlHandle theControl,Point thePoint,ProcPtr actionProc)
 = {__GenToolboxTrapCode(0xA968)}; 
pascal short FindControl(Point thePoint,WindowPtr theWindow,ControlHandle *theControl)
 = {__GenToolboxTrapCode(0xA96C)}; 
pascal void SetControlColor(ControlHandle theControl,CCTabHandle newColorTable)
 = {__GenToolboxTrapCode(0xAA43)}; 
pascal void SetCtlColor(ControlHandle theControl,CCTabHandle newColorTable)
 = {__GenToolboxTrapCode(0xAA43)}; 
pascal Boolean GetAuxiliaryControlRecord(ControlHandle theControl,AuxCtlHandle *acHndl)
 = {__GenToolboxTrapCode(0xAA44)}; 
pascal Boolean GetAuxCtl(ControlHandle theControl,AuxCtlHandle *acHndl)
 = {__GenToolboxTrapCode(0xAA44)}; 
pascal short GetControlVariant(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA809)}; 
pascal short GetCVariant(ControlHandle theControl)
 = {__GenToolboxTrapCode(0xA809)}; 
void dragcontrol(ControlHandle theControl,Point *startPt,const Rect *limitRect,
 const Rect *slopRect,short axis); 
ControlHandle newcontrol(WindowPtr theWindow,const Rect *boundsRect,char *title,
 Boolean visible,short value,short min,short max,short procID,long refCon); 
short findcontrol(Point *thePoint,WindowPtr theWindow,ControlHandle *theControl); 
void getcontroltitle(ControlHandle theControl,char *title); 
void getctitle(ControlHandle theControl,char *title); 
void setcontroltitle(ControlHandle theControl,char *title); 
void setctitle(ControlHandle theControl,char *title); 
short trackcontrol(ControlHandle theControl,Point *thePoint,ProcPtr actionProc); 
short testcontrol(ControlHandle theControl,Point *thePt); 

#ifdef __cplusplus
}
#endif

#endif
