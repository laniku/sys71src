/************************************************************

Created: Tuesday, January 8, 1991 at 1:03 PM
    Dialogs.h
    C Interface to the Macintosh Libraries


		Copyright Apple Computer, Inc.	 1985-1991
        All rights reserved

	Change History (most recent first):

		<SM3>	   12/8/92	CSS		Update from Reality:
									<19> 12/8/92 JSM	SoundProcPtr takes a short, not a void.
		<SM2>	  11/16/92	CSS		Update from Reality:
									<18> 11/7/92 JDR	Added the now publicly defined routines, StdFilterProc,
														GetStdFilterProc, SetDialogDefaultItem, SetDialogCancelItem,
														SetDialogTracksCursor.
		<SM1>	  10/26/92	CSS		Changes to allow traps to be expanded inline rather than
									called through the trap dispatcher.
		<17>	  4/6/92	DCL		For New Inside Mac: Adding fancy new improved names for old
									crusty routines. And getting rid of CouldDialog, FreeDialog,
									CouldAlert, FreeAlert. #1025005
		<16>	 7/24/91	JL		Updated copyright notice. Adjusted file to match database.
		<15>	 6/25/91	JNG		Move DITL Manipulation calls from CTBUtilities.h
		<14>	 1/27/91	LN		Checked in Database generate file from DSG. Added DisposeDialog
									as a synonym for DisposDialog
		<12>	12/12/90	JL		Put formal parameter names back.
		<11>	 12/3/90	RLC		<ksm> Remove the private interfaces.
		<10>	 11/7/90	JL		Changed all #defines to anonymous enums
		 <9>	 11/4/90	dba		got rid of some extraneous parameter names; made some parameters
									void* instead of Ptr; used constStr255Parameter; added
									UpdateDialog (synonym for UpdtDialog)
		 <8>	10/30/90	dba		make smaller version of GetAlrtStage
		 <7>	  10/9/90	JAL		Added Inline to SetDAFont.
		 <6>	  7/2/90	KSM		Remove MarkWindowAsModal.
		 <5>	 6/28/90	KSM		Add more new calls.
		 <4>	  6/8/90	KSM		Add new DialogMgr dispatched routines.
************************************************************/


#ifndef __DIALOGS__
#define __DIALOGS__

#ifndef __WINDOWS__
#include <Windows.h>
#endif

#ifndef __TEXTEDIT__
#include <TextEdit.h>
#endif

#ifndef	__ROMFastTrapsIncluded__
#include "ROMFastTraps.h"
#endif

enum {

    ctrlItem = 4,
    btnCtrl = 0,
    chkCtrl = 1,
    radCtrl = 2,
    resCtrl = 3,
    statText = 8,
    editText = 16,
    iconItem = 32,
    picItem = 64,
    userItem = 0,
    itemDisable = 128,
    ok = 1,
    cancel = 2,
    stopIcon = 0,
    noteIcon = 1,
    cautionIcon = 2
};

/*	Dialog Item List Manipulation Constants	*/
typedef short DITLMethod;

enum {

	overlayDITL = 0,
	appendDITLRight = 1,
	appendDITLBottom = 2
};

typedef short StageList;


typedef WindowPtr DialogPtr;
typedef pascal void (*ResumeProcPtr)(void);
typedef pascal void (*SoundProcPtr)(short soundNumber);
typedef pascal Boolean (*ModalFilterProcPtr)(DialogPtr theDialog, EventRecord *theEvent, short *itemHit);

struct DialogRecord {
    WindowRecord window;
    Handle items;
    TEHandle textH;
    short editField;
    short editOpen;
    short aDefItem;
};

typedef struct DialogRecord DialogRecord;
typedef DialogRecord *DialogPeek;

struct DialogTemplate {
    Rect boundsRect;
    short procID;
    Boolean visible;
    Boolean filler1;
    Boolean goAwayFlag;
    Boolean filler2;
    long refCon;
    short itemsID;
    Str255 title;
};

typedef struct DialogTemplate DialogTemplate;
typedef DialogTemplate *DialogTPtr, **DialogTHndl;

struct AlertTemplate {
    Rect boundsRect;
    short itemsID;
    StageList stages;
};

typedef struct AlertTemplate AlertTemplate;
typedef AlertTemplate *AlertTPtr, **AlertTHndl;


#ifdef __cplusplus
extern "C" {
#endif
pascal void InitDialogs(ResumeProcPtr resumeProc)
    = {__GenToolboxTrapCode(0xA97B)}; 
pascal void ErrorSound(SoundProcPtr soundProc)
    = {__GenToolboxTrapCode(0xA98C)}; 
pascal DialogPtr NewDialog(void *wStorage,const Rect *boundsRect,ConstStr255Param title,
    Boolean visible,short procID,WindowPtr behind,Boolean goAwayFlag,long refCon,
    Handle itmLstHndl)
    = {__GenToolboxTrapCode(0xA97D)}; 
DialogPtr newdialog(void *wStorage,const Rect *boundsRect,char *title,Boolean visible,
    short procID,WindowPtr behind,Boolean goAwayFlag,long refCon,Handle itmLstHndl); 
pascal DialogPtr GetNewDialog(short dialogID,void *dStorage,WindowPtr behind)
    = {__GenToolboxTrapCode(0xA97C)}; 
pascal void CloseDialog(DialogPtr theDialog)
    = {__GenToolboxTrapCode(0xA982)}; 
pascal void DisposDialog(DialogPtr theDialog)
    = {__GenToolboxTrapCode(0xA983)}; 
pascal void DisposeDialog(DialogPtr theDialog)
    = {__GenToolboxTrapCode(0xA983)}; 
pascal void ParamText(ConstStr255Param param0,ConstStr255Param param1,ConstStr255Param param2,
    ConstStr255Param param3)
    = {__GenToolboxTrapCode(0xA98B)}; 
pascal void ModalDialog(ModalFilterProcPtr filterProc,short *itemHit)
    = {__GenToolboxTrapCode(0xA991)}; 
pascal Boolean IsDialogEvent(const EventRecord *theEvent)
    = {__GenToolboxTrapCode(0xA97F)}; 
pascal Boolean DialogSelect(const EventRecord *theEvent,DialogPtr *theDialog,
    short *itemHit)
    = {__GenToolboxTrapCode(0xA980)}; 
pascal void DrawDialog(DialogPtr theDialog)
    = {__GenToolboxTrapCode(0xA981)}; 
pascal void UpdateDialog(DialogPtr theDialog,RgnHandle updateRgn)
    = {__GenToolboxTrapCode(0xA978)}; 
pascal void UpdtDialog(DialogPtr theDialog,RgnHandle updateRgn)
    = {__GenToolboxTrapCode(0xA978)}; 
pascal short Alert(short alertID,ModalFilterProcPtr filterProc)
    = {__GenToolboxTrapCode(0xA985)}; 
pascal short StopAlert(short alertID,ModalFilterProcPtr filterProc)
    = {__GenToolboxTrapCode(0xA986)}; 
pascal short NoteAlert(short alertID,ModalFilterProcPtr filterProc)
    = {__GenToolboxTrapCode(0xA987)}; 
pascal short CautionAlert(short alertID,ModalFilterProcPtr filterProc)
    = {__GenToolboxTrapCode(0xA988)}; 
pascal void GetDialogItem(DialogPtr theDialog,short itemNo,short *itemType,Handle *item,
    Rect *box)
    = {__GenToolboxTrapCode(0xA98D)}; 
pascal void GetDItem(DialogPtr theDialog,short itemNo,short *itemType,Handle *item,
    Rect *box)
    = {__GenToolboxTrapCode(0xA98D)}; 
pascal void SetDialogItem(DialogPtr theDialog,short itemNo,short itemType,Handle item,
    const Rect *box)
    = {__GenToolboxTrapCode(0xA98E)}; 
pascal void SetDItem(DialogPtr theDialog,short itemNo,short itemType,Handle item,
    const Rect *box)
    = {__GenToolboxTrapCode(0xA98E)}; 
pascal void HideDialogItem(DialogPtr theDialog,short itemNo)
    = {__GenToolboxTrapCode(0xA827)}; 
pascal void HideDItem(DialogPtr theDialog,short itemNo)
    = {__GenToolboxTrapCode(0xA827)}; 
pascal void ShowDialogItem(DialogPtr theDialog,short itemNo)
    = {__GenToolboxTrapCode(0xA828)}; 
pascal void ShowDItem(DialogPtr theDialog,short itemNo)
    = {__GenToolboxTrapCode(0xA828)}; 
pascal void SelectDialogItemText(DialogPtr theDialog,short itemNo,short strtSel,short endSel)
    = {__GenToolboxTrapCode(0xA97E)}; 
pascal void SelIText(DialogPtr theDialog,short itemNo,short strtSel,short endSel)
    = {__GenToolboxTrapCode(0xA97E)}; 
pascal void GetDialogItemText(Handle item,Str255 text)
    = {__GenToolboxTrapCode(0xA990)}; 
pascal void GetIText(Handle item,Str255 text)
    = {__GenToolboxTrapCode(0xA990)}; 
pascal void SetDialogItemText(Handle item,ConstStr255Param text)
    = {__GenToolboxTrapCode(0xA98F)}; 
pascal void SetIText(Handle item,ConstStr255Param text)
    = {__GenToolboxTrapCode(0xA98F)}; 
pascal short FindDialogItem(DialogPtr theDialog,Point thePt)
    = {__GenToolboxTrapCode(0xA984)}; 
pascal short FindDItem(DialogPtr theDialog,Point thePt)
    = {__GenToolboxTrapCode(0xA984)}; 
pascal DialogPtr NewColorDialog(void *dStorage,const Rect *boundsRect,ConstStr255Param title,
    Boolean visible,short procID,WindowPtr behind,Boolean goAwayFlag,long refCon,
    Handle items)
    = {__GenToolboxTrapCode(0xAA4B)}; 
pascal DialogPtr NewCDialog(void *dStorage,const Rect *boundsRect,ConstStr255Param title,
    Boolean visible,short procID,WindowPtr behind,Boolean goAwayFlag,long refCon,
    Handle items)
    = {__GenToolboxTrapCode(0xAA4B)}; 
DialogPtr newcolordialog(void *dStorage,const Rect *boundsRect,char *title,
    Boolean visible,short procID,WindowPtr behind,Boolean goAwayFlag,long refCon,
    Handle items); 
DialogPtr newcdialog(void *dStorage,const Rect *boundsRect,char *title,
    Boolean visible,short procID,WindowPtr behind,Boolean goAwayFlag,long refCon,
    Handle items); 
#define GetAlertStage() (* (short*) 0x0A9A)
#define GetAlrtStage() (* (short*) 0x0A9A)
pascal void ResetAlertStage(void)
    = {0x4278,0x0A9A}; 
pascal void ResetAlrtStage(void)
    = {0x4278,0x0A9A}; 
pascal void DialogCut(DialogPtr theDialog); 
pascal void DlgCut(DialogPtr theDialog); 
pascal void DialogPaste(DialogPtr theDialog); 
pascal void DlgPaste(DialogPtr theDialog); 
pascal void DialogCopy(DialogPtr theDialog); 
pascal void DlgCopy(DialogPtr theDialog); 
pascal void DialogDelete(DialogPtr theDialog); 
pascal void DlgDelete(DialogPtr theDialog); 
pascal void SetDialogFont(short fontNum)
    = {0x31DF,0x0AFA}; 
pascal void SetDAFont(short fontNum)
    = {0x31DF,0x0AFA}; 
void paramtext(char *param0,char *param1,char *param2,char *param3); 
void getdialogitemtext(Handle item,char *text); 
void getitext(Handle item,char *text); 
void setdialogitemtext(Handle item,char *text); 
void setitext(Handle item,char *text); 
short finddialogitem(DialogPtr theDialog,Point *thePt); 
short findditem(DialogPtr theDialog,Point *thePt); 

pascal void	AppendDITL(DialogPtr theDialog,Handle theHandle,DITLMethod method);
pascal short CountDITL(DialogPtr theDialog);
pascal void	ShortenDITL(DialogPtr theDialog,short numberItems);
pascal Boolean StdFilterProc(DialogPtr theDialog, EventRecord* event, short* itemHit);
pascal OSErr GetStdFilterProc(ModalFilterProcPtr *theProc)
	= {0x303C,0x0203,0xAA68};
pascal OSErr SetDialogDefaultItem(DialogPtr theDialog, short newItem)
	= {0x303C,0x0304,0xAA68};
pascal OSErr SetDialogCancelItem(DialogPtr theDialog, short newItem)
	= {0x303C,0x0305, 0xAA68};
pascal OSErr SetDialogTracksCursor(DialogPtr theDialog, Boolean tracks)
	= {0x303C,0x0306,0xAA68};

#ifdef __cplusplus
}
#endif

#endif
