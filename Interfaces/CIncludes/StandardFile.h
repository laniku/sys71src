
/************************************************************

Created: Saturday, July 27, 1991 at 6:57 PM
 StandardFile.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1990-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		<15>	 7/31/91	JL		Updated Copyright.
		<14>	 1/28/91	LN		Checked in Database generate file from DSG. Grouping enums into
									groups of 20. Listed function parameters vertically - like
									pascal.
		<12>	11/14/90	JL		Put formal parameter names back. Took out prompt parameter for
									StandardGetFile
		<11>	 11/4/90	dba		got rid of some extraneous parameter names; used
									constStr255Parameter
		<10>	10/24/90	JL		Changing #Defines to anonymous enums.
		 <9>	 8/22/90	ngk		add sfLockWarnDialogRefCon
		 <8>	  8/8/90	ngk		Capitalize GoTo. Fix Dialog ID's of new get and put.
		 <7>	  7/2/90	ngk		Changed sfScript from short to ScriptCode
		 <6>	  7/2/90	ngk		Added refcon constants.
		 <5>	 6/10/90	JSM		Added include of Dialogs.h.
		 <4>	  6/8/90	ngk		Changed yourDataPtr to yourDataPtr. Added constants for new
									dialog layout.
		 <3>	03/07/90	JAL		Took out ModalFilterProc since it is already in Dialogs.h
		 <2>	 2/25/90	ngk		Updated to new interface for new calls (selectors 5-8)
		 <1>	  2/7/90	ngk		Moved all Standard file definitions out of Packages.h into here.

************************************************************/


#ifndef __STANDARDFILE__
#define __STANDARDFILE__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __DIALOGS__
#include <Dialogs.h>
#endif

#ifndef __FILES__
#include <Files.h>
#endif


enum {


/* resource IDs and item offsets of pre-7.0 dialogs */
 putDlgID = -3999,
 putSave = 1,
 putCancel = 2,
 putEject = 5,
 putDrive = 6,
 putName = 7,

 getDlgID = -4000,
 getOpen = 1,
 getCancel = 3,
 getEject = 5,
 getDrive = 6,
 getNmList = 7,
 getScroll = 8,

/* resource IDs and item offsets of 7.0 dialogs */
 sfPutDialogID = -6043,
 sfGetDialogID = -6042,
 sfItemOpenButton = 1,
 sfItemCancelButton = 2,
 sfItemBalloonHelp = 3,
 sfItemVolumeUser = 4,
 sfItemEjectButton = 5
};
enum {
 sfItemDesktopButton = 6,
 sfItemFileListUser = 7,
 sfItemPopUpMenuUser = 8,
 sfItemDividerLinePict = 9,
 sfItemFileNameTextEdit = 10,
 sfItemPromptStaticText = 11,
 sfItemNewFolderUser = 12,


/* pseudo-item hits for use in DlgHook */
 sfHookFirstCall = -1,
 sfHookCharOffset = 0x1000,
 sfHookNullEvent = 100,
 sfHookRebuildList = 101,
 sfHookFolderPopUp = 102,
 sfHookOpenFolder = 103,


/* the following are only in system 7.0+ */
 sfHookOpenAlias = 104,
 sfHookGoToDesktop = 105,
 sfHookGoToAliasTarget = 106,
 sfHookGoToParent = 107,
 sfHookGoToNextDrive = 108,
 sfHookGoToPrevDrive = 109,
 sfHookChangeSelection = 110
};
enum {
 sfHookSetActiveOffset = 200,
 sfHookLastCall = -2

/* the refcon field of the dialog record during a
 modalfilter or dialoghook contains one of the following */

#define sfMainDialogRefCon 'stdf'
#define sfNewFolderDialogRefCon 'nfdr'
#define sfReplaceDialogRefCon 'rplc'
#define sfStatWarnDialogRefCon 'stat'
#define sfLockWarnDialogRefCon 'lock'
#define sfErrorDialogRefCon 'err '
};

struct SFReply {
 Boolean good;
 Boolean copy;
 OSType fType;
 short vRefNum;
 short version;
 Str63 fName;
};

typedef struct SFReply SFReply;

struct StandardFileReply {
 Boolean sfGood;
 Boolean sfReplacing;
 OSType sfType;
 FSSpec sfFile;
 ScriptCode sfScript;
 short sfFlags;
 Boolean sfIsFolder;
 Boolean sfIsVolume;
 long sfReserved1;
 short sfReserved2;
};

typedef struct StandardFileReply StandardFileReply;


typedef pascal short (*DlgHookProcPtr)(short item, DialogPtr theDialog);
typedef pascal Boolean (*FileFilterProcPtr)(ParmBlkPtr PB);

/* the following also include an extra parameter of "your data pointer" */
typedef pascal short (*DlgHookYDProcPtr)(short item, DialogPtr theDialog, void *yourDataPtr);
typedef pascal Boolean (*ModalFilterYDProcPtr)(DialogPtr theDialog, EventRecord *theEvent, short *itemHit, void *yourDataPtr);
typedef pascal Boolean (*FileFilterYDProcPtr)(ParmBlkPtr PB, void *yourDataPtr);
typedef pascal void (*ActivateYDProcPtr)(DialogPtr theDialog, short itemNo, Boolean activating, void *yourDataPtr);

typedef OSType SFTypeList[4];

#ifdef __cplusplus
extern "C" {
#endif
pascal void SFPutFile(Point where,
                      ConstStr255Param prompt,
                      ConstStr255Param origName,
                      DlgHookProcPtr dlgHook,
                      SFReply *reply)
 = {0x3F3C,0x0001,0xA9EA}; 

pascal void SFGetFile(Point where,
                      ConstStr255Param prompt,
                      FileFilterProcPtr fileFilter,
                      short numTypes,
                      SFTypeList typeList,
                      DlgHookProcPtr dlgHook,
                      SFReply *reply)
 = {0x3F3C,0x0002,0xA9EA}; 

pascal void SFPPutFile(Point where,
                       ConstStr255Param prompt,
                       ConstStr255Param origName,
                       DlgHookProcPtr dlgHook,
                       SFReply *reply,
                       short dlgID,
                       ModalFilterProcPtr filterProc)
 = {0x3F3C,0x0003,0xA9EA}; 

pascal void SFPGetFile(Point where,
                       ConstStr255Param prompt,
                       FileFilterProcPtr fileFilter,
                       short numTypes,
                       SFTypeList typeList,
                       DlgHookProcPtr dlgHook,
                       SFReply *reply,
                       short dlgID,
                       ModalFilterProcPtr filterProc)
 = {0x3F3C,0x0004,0xA9EA}; 

pascal void StandardPutFile(ConstStr255Param prompt,
                            ConstStr255Param defaultName,
                            StandardFileReply *reply)
 = {0x3F3C,0x0005,0xA9EA}; 

pascal void StandardGetFile(FileFilterProcPtr fileFilter,
                            short numTypes,
                            SFTypeList typeList,
                            StandardFileReply *reply)
 = {0x3F3C,0x0006,0xA9EA}; 

pascal void CustomPutFile(ConstStr255Param prompt,
                          ConstStr255Param defaultName,
                          StandardFileReply *reply,
                          short dlgID,
                          Point where,
                          DlgHookYDProcPtr dlgHook,
                          ModalFilterYDProcPtr filterProc,
                          short *activeList,
                          ActivateYDProcPtr activateProc,
                          void *yourDataPtr)
 = {0x3F3C,0x0007,0xA9EA}; 

pascal void CustomGetFile(FileFilterYDProcPtr fileFilter,
                          short numTypes,
                          SFTypeList typeList,
                          StandardFileReply *reply,
                          short dlgID,
                          Point where,
                          DlgHookYDProcPtr dlgHook,
                          ModalFilterYDProcPtr filterProc,
                          short *activeList,
                          ActivateYDProcPtr activateProc,
                          void *yourDataPtr)
 = {0x3F3C,0x0008,0xA9EA}; 

void sfpputfile(Point *where,char *prompt,char *origName,DlgHookProcPtr dlgHook,
 SFReply *reply,short dlgID,ModalFilterProcPtr filterProc); 
void sfgetfile(Point *where,char *prompt,FileFilterProcPtr fileFilter,short numTypes,
 SFTypeList typeList,DlgHookProcPtr dlgHook,SFReply *reply); 
void sfpgetfile(Point *where,char *prompt,FileFilterProcPtr fileFilter,
 short numTypes,SFTypeList typeList,DlgHookProcPtr dlgHook,SFReply *reply,
 short dlgID,ModalFilterProcPtr filterProc); 
void sfputfile(Point *where,char *prompt,char *origName,DlgHookProcPtr dlgHook,
 SFReply *reply); 

/* 
 
  New StandardFile routine comments:
 
  activeList is pointer to array of integer (16-bits).
  first integer is length of list.
  following integers are possible activatable DITL items, in
  the order that the tab key will cycle through.  The first
  in the list is the item made active when dialog is first shown.
 
  activateProc is a pointer to a procedure like:
 
   PROCEDURE MyActivateProc(theDialog:  DialogPtr;
          itemNo:  INTEGER;
          activating: BOOLEAN;
          yourDataPtr: Ptr);
 
  The activateProc is called with activating=FALSE on the itemNo
  about to deactivate then with activating=TRUE on the itemNo
  about to become the active item. (like activate event)
 
  yourDataPtr is a nice little extra that makes life easier without
  globals.  CustomGetFile & CustomPPutFile when calling any of their
  call back procedures, pushes the extra parameter of yourDataPtr on
  the stack.
 
  In addition the filterProc in CustomGetFile & CustomPPutFile is called
  before before SF does any mapping, instead of after.
*/


#ifdef __cplusplus
}
#endif

#endif
