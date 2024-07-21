
{
Created: Saturday, July 27, 1991 at 11:53 PM
 StandardFile.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1990-1991
  All rights reserved
    This file is used in these builds: BigBang Sys606

	Change History (most recent first):

		<11>	 7/31/91	JL		Updated Copyright.
		<10>	 1/28/91	LN		Checked in Database Generated File from DSG.
		 <9>	12/11/90	ngk		fix type of sfScript to be ScriptCode
		 <8>	 8/22/90	ngk		add sfLockWarnDialogRefCon
		 <7>	  8/8/90	ngk		Fix dialogs IDs of new get and put
		 <6>	  8/8/90	ngk		Capitalize GoTo, get type definition for ModalFilterProcPtr from
									Dialogs.p
		 <5>	  7/2/90	ngk		Added refcon constants
		 <4>	  6/8/90	ngk		Changed yourDataPtr to yourDataPtr. Added constants for new
									dialog layout.
		 <3>	 2/25/90	ngk		Added new hook constants. Changed names of new calls with
									selectors 5 - 8. New calls also now return the script code of
									file chosen.
		 <2>	  2/7/90	ngk		fix comments
		 <1>	  2/7/90	ngk		pulled all of StandardFile stuff out of Packages.p into here.

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT StandardFile;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingStandardFile}
{$SETC UsingStandardFile := 1}

{$I+}
{$SETC StandardFileIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingDialogs}
{$I $$Shell(PInterfaces)Dialogs.p}
{$ENDC}
{$IFC UNDEFINED UsingFiles}
{$I $$Shell(PInterfaces)Files.p}
{$ENDC}
{$SETC UsingIncludes := StandardFileIncludes}

CONST

{ resource IDs and item offsets of pre-7.0 dialogs }
putDlgID = -3999;
putSave = 1;
putCancel = 2;
putEject = 5;
putDrive = 6;
putName = 7;

getDlgID = -4000;
getOpen = 1;
getCancel = 3;
getEject = 5;
getDrive = 6;
getNmList = 7;
getScroll = 8;

{ resource IDs and item offsets of 7.0 dialogs }
sfPutDialogID = -6043;
sfGetDialogID = -6042;
sfItemOpenButton = 1;
sfItemCancelButton = 2;
sfItemBalloonHelp = 3;
sfItemVolumeUser = 4;
sfItemEjectButton = 5;
sfItemDesktopButton = 6;
sfItemFileListUser = 7;
sfItemPopUpMenuUser = 8;
sfItemDividerLinePict = 9;
sfItemFileNameTextEdit = 10;
sfItemPromptStaticText = 11;
sfItemNewFolderUser = 12;


{ pseudo-item hits for use in DlgHook }
sfHookFirstCall = -1;
sfHookCharOffset = $1000;
sfHookNullEvent = 100;
sfHookRebuildList = 101;
sfHookFolderPopUp = 102;
sfHookOpenFolder = 103;


{ the following are only in system 7.0+ }
sfHookOpenAlias = 104;
sfHookGoToDesktop = 105;
sfHookGoToAliasTarget = 106;
sfHookGoToParent = 107;
sfHookGoToNextDrive = 108;
sfHookGoToPrevDrive = 109;
sfHookChangeSelection = 110;
sfHookSetActiveOffset = 200;
sfHookLastCall = -2;

{ the refcon field of the dialog record during a
 modalfilter or dialoghook contains one of the following }
sfMainDialogRefCon = 'stdf';
sfNewFolderDialogRefCon = 'nfdr';
sfReplaceDialogRefCon = 'rplc';
sfStatWarnDialogRefCon = 'stat';
sfLockWarnDialogRefCon = 'lock';
sfErrorDialogRefCon = 'err ';

TYPE
SFReply = RECORD
 good: BOOLEAN;
 copy: BOOLEAN;
 fType: OSType;
 vRefNum: INTEGER;
 version: INTEGER;
 fName: Str63;
 END;

StandardFileReply = RECORD
 sfGood: BOOLEAN;
 sfReplacing: BOOLEAN;
 sfType: OSType;
 sfFile: FSSpec;
 sfScript: ScriptCode;
 sfFlags: INTEGER;
 sfIsFolder: BOOLEAN;
 sfIsVolume: BOOLEAN;
 sfReserved1: LONGINT;
 sfReserved2: INTEGER;
 END;


DlgHookProcPtr = ProcPtr;			{ FUNCTION Hook(item: INTEGER; theDialog: DialogPtr): INTEGER; }
FileFilterProcPtr = ProcPtr;		{ FUNCTION FileFilter(PB: CInfoPBPtr): BOOLEAN; }

{ the following also include an extra parameter of "your data pointer" }
DlgHookYDProcPtr = ProcPtr;			{ FUNCTION  Hook(item: INTEGER; theDialog: DialogPtr; yourDataPtr: Ptr): INTEGER; }
ModalFilterYDProcPtr = ProcPtr;		{ FUNCTION  Filter(theDialog: DialogPtr; VAR theEvent: EventRecord; VAR itemHit: INTEGER; yourDataPtr: Ptr): BOOLEAN; }
FileFilterYDProcPtr = ProcPtr;		{ FUNCTION  FileFilter(PB: CInfoPBPtr; yourDataPtr: Ptr): BOOLEAN; }
ActivateYDProcPtr = ProcPtr;		{ PROCEDURE Activate(theDialog; DialogPtr; itemNo: INTEGER; activating: BOOLEAN; yourDataPtr: Ptr); }

SFTypeList = ARRAY [0..3] OF OSType;

PROCEDURE SFPutFile(where: Point;
                    prompt: Str255;
                    origName: Str255;
                    dlgHook: DlgHookProcPtr;
                    VAR reply: SFReply);
 INLINE $3F3C,$0001,$A9EA;

PROCEDURE SFGetFile(where: Point;
                    prompt: Str255;
                    fileFilter: FileFilterProcPtr;
                    numTypes: INTEGER;
                    typeList: SFTypeList;
                    dlgHook: DlgHookProcPtr;
                    VAR reply: SFReply);
 INLINE $3F3C,$0002,$A9EA;

PROCEDURE SFPPutFile(where: Point;
                     prompt: Str255;
                     origName: Str255;
                     dlgHook: DlgHookProcPtr;
                     VAR reply: SFReply;
                     dlgID: INTEGER;
                     filterProc: ModalFilterProcPtr);
 INLINE $3F3C,$0003,$A9EA;

PROCEDURE SFPGetFile(where: Point;
                     prompt: Str255;
                     fileFilter: FileFilterProcPtr;
                     numTypes: INTEGER;
                     typeList: SFTypeList;
                     dlgHook: DlgHookProcPtr;
                     VAR reply: SFReply;
                     dlgID: INTEGER;
                     filterProc: ModalFilterProcPtr);
 INLINE $3F3C,$0004,$A9EA;

PROCEDURE StandardPutFile(prompt: Str255;
                          defaultName: Str255;
                          VAR reply: StandardFileReply);
 INLINE $3F3C,$0005,$A9EA;

PROCEDURE StandardGetFile(fileFilter: FileFilterProcPtr;
                          numTypes: INTEGER;
                          typeList: SFTypeList;
                          VAR reply: StandardFileReply);
 INLINE $3F3C,$0006,$A9EA;

PROCEDURE CustomPutFile(prompt: Str255;
                        defaultName: Str255;
                        VAR reply: StandardFileReply;
                        dlgID: INTEGER;
                        where: Point;
                        dlgHook: DlgHookYDProcPtr;
                        filterProc: ModalFilterYDProcPtr;
                        activeList: Ptr;
                        activateProc: ActivateYDProcPtr;
                        yourDataPtr: UNIV Ptr);
 INLINE $3F3C,$0007,$A9EA;

PROCEDURE CustomGetFile(fileFilter: FileFilterYDProcPtr;
                        numTypes: INTEGER;
                        typeList: SFTypeList;
                        VAR reply: StandardFileReply;
                        dlgID: INTEGER;
                        where: Point;
                        dlgHook: DlgHookYDProcPtr;
                        filterProc: ModalFilterYDProcPtr;
                        activeList: Ptr;
                        activateProc: ActivateYDProcPtr;
                        yourDataPtr: UNIV Ptr);
 INLINE $3F3C,$0008,$A9EA;


{ 
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
 }



{$ENDC} { UsingStandardFile }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

