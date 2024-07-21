
{
Created: Tuesday, January 29, 1991 at 6:35 PM
 Editions.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1989-1991
  All rights reserved
    This file is used in these builds: Mac32 HcMac MacPP BigBang Sys606

	Change History (most recent first):

		<22>	 7/30/91	JL		Updated Copyright.
		<21>	  2/4/91	JL		Remove parens from around kFormatLengthUnknown; change the param
									success back to successful; change parameter name length back to
									formatSize; change buffPtr: Ptr to buffPtr: UNIV Ptr
		<20>	1/29/91		JAL		Checked in Database generated file from MPW.
		<19>	12/14/90	dba		<JDR> make pointers for buffer be UNIV Ptr
		<17>	 9/14/90	ngk		Change file types for edition files. edtP -> edtp, edtT -> edtt
		<16>	  8/2/90	ngk		Capitalize T in GoToPublisher. Changed updateMode constants to
	   								reflect new titles in options dialog.  Show sample buffer
									for section events.
		<15>	  7/2/90	ngk		Added new hooks and refcon constants for dialogs.
		<14>	 6/20/90	ngk		Changed CanonicalFileSpec to FSSpec.
		<13>	 5/31/90	ngk		Added new Finder types for edition files. Add format mask for
	   								NewSubscriberReply and bit constants for it.  Use ScriptCode
									instead of INTEGER where appropriate.
		<12>	  5/4/90	ngk		Removed FindEditionContainerDialog.
		<11>	  4/7/90	ngk		Renamed callBackPtr to yourDataPtr. Renamed fields in
	   								EditionOpenerParamBlock.  Changed sectionDocument to be a
									CanonicalFileSpecPtr to make using NIL easier.
		<10>	 3/25/90	ngk		Moved script from PublisherReply into EditionContainerSpec
		 <9>	 3/20/90	ngk		Added some comments about section events
		 <8>	 3/20/90	ngk		Add constants for new AppleEvent format section events. Added
									script code to NewPublisherReply and CreateEditionContainerFile.
									Changed standard section resource type to 'sect' from 'dpsr'
		 <7>	 3/10/90	ngk		Fixed bug in selector numbers of dialog routines and
									CreateEditionContainerFile. Removed auto-include of EPPC unit.
		 <4>	 1/22/90	ngk		remove get, save, and dispose section
		 <3>	  1/7/90	ngk		Removed get, save, and dispose section
									Added kFormatLengthUnknown
		 <2>	  1/6/90	ngk		Moved error codes to Errors.p Made a SectionOptionsReply. Added
									I/O bottleNecks. Added previewFormat field to NewPublisherReply.
									Made dialogs expandable. Renumbered routines.
		 <1>	  1/6/90	ngk		first checked into BBS
	   <2.3>	11/13/89	ngk		Changed SectionInfoDialog to SectionOptionsDialog
	   <2.2>	 11/2/89	ngk		Moved EPPC stuff into its own interface file
	   <2.1>	10/24/89	ngk		Added dependency on Process.p
	   <2.0>	10/10/89	ngk		Updated to new ePPC records and routines
	   <1.9>	 10/4/89	ngk		Renamed NewEditionFile to CreateEditionContainerFile.
	   <1.8>	 10/2/89	ngk		Updated to Alpha Zero API
	   <1.7>	 9/18/89	ngk		Added DeletePublication
	   <1.6>	 8/29/89	ngk		Now uses PubSpecs and has warning codes. PublishAs and
									SubscribeTo use reply records.
	   <1.5>	  8/8/89	ngk		Added comments about new HighLevelEvent usage
	   <1.4>	 6/15/89	ngk		added rUnsavedPublishers alert ID temporarily added IPC
									interface stuff
	   <1.3>	 6/11/89	ngk		Added HasEditionFormat routine Added more comments
	   <1.2>	 5/31/89	ngk		More fixes for Alias Manager integration
	   <1.1>	 5/31/89	ngk		Bumped package version, since integrating with Aliases
	   <1.0>	 5/29/89	ngk		Combined DataPub.p and DataPubTypes.p

}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Editions;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingEditions}
{$SETC UsingEditions := 1}

{$I+}
{$SETC EditionsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingMemory}
{$I $$Shell(PInterfaces)Memory.p}
{$ENDC}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingFiles}
{$I $$Shell(PInterfaces)Files.p}
{$ENDC}
{$IFC UNDEFINED UsingAliases}
{$I $$Shell(PInterfaces)Aliases.p}
{$ENDC}
{$SETC UsingIncludes := EditionsIncludes}

CONST

{ resource types  }
rSectionType = 'sect';						{ ResType of saved SectionRecords }

{ section types }
stSubscriber = $01;
stPublisher = $0A;

sumAutomatic = 0;							{ subscriber update mode - Automatically     }
sumManual = 1;								{ subscriber update mode - Manually }
pumOnSave = 0;								{ publisher update mode - OnSave            }
pumManual = 1;								{ publisher update mode - Manually }

kPartsNotUsed = 0;
kPartNumberUnknown = -1;					{ misc }

kPreviewWidth = 120;
kPreviewHeight = 120;

kPublisherDocAliasFormat = 'alis';
kPreviewFormat = 'prvw';
kFormatListFormat = 'fmts';

{ bits for formatsMask }
kPICTformatMask = 1;
kTEXTformatMask = 2;
ksndFormatMask = 4;

{ Finder types for edition files }
kPICTEditionFileType = 'edtp';
kTEXTEditionFileType = 'edtt';
ksndEditionFileType = 'edts';
kUnknownEditionFileType = 'edtu';

{ pseudo-item hits for dialogHooks 
 the first if for NewPublisher or NewSubscriber Dialogs }
emHookRedrawPreview = 150;

{ the following are for SectionOptions Dialog }
emHookCancelSection = 160;
emHookGoToPublisher = 161;
emHookGetEditionNow = 162;
emHookSendEditionNow = 162;
emHookManualUpdateMode = 163;
emHookAutoUpdateMode = 164;

{ the refcon field of the dialog record during a modalfilter 
 or dialoghook contains one the following }
emOptionsDialogRefCon = 'optn';
emCancelSectionDialogRefCon = 'cncl';
emGoToPubErrDialogRefCon = 'gerr';
kFormatLengthUnknown = -1;

TYPE
SectionType = SignedByte;					{ one byte, stSubscriber or stPublisher }
TimeStamp = LONGINT;						{ seconds since 1904 }
FormatType = PACKED ARRAY [1..4] OF CHAR;	{ similar to ResType as used by scrap mgr }
EditionRefNum = Handle;						{ used in Edition I/O }
{ update modes }
UpdateMode = INTEGER;						{ sumAutomatic, pumSuspend, etc }

SectionPtr = ^SectionRecord;
SectionHandle = ^SectionPtr;
SectionRecord = RECORD
 version: SignedByte;						{ always 0x01 in system 7.0 }
 kind: SectionType;							{ stSubscriber or stPublisher }
 mode: UpdateMode;							{ auto or manual }
 mdDate: TimeStamp;							{ last change in document }
 sectionID: LONGINT;						{ app. specific, unique per document }
 refCon: LONGINT;							{ application specific }
 alias: AliasHandle;						{ handle to Alias Record }
 subPart: LONGINT;							{ which part of container file }
 nextSection: SectionHandle;				{ for linked list of app's Sections }
 controlBlock: Handle;						{ used internally }
 refNum: EditionRefNum;						{ used internally }
 END;

EditionContainerSpecPtr = ^EditionContainerSpec;
EditionContainerSpec = RECORD
 theFile: FSSpec;
 theFileScript: ScriptCode;
 thePart: LONGINT;
 thePartName: Str31;
 thePartScript: ScriptCode;
 END;

EditionInfoRecord = RECORD
 crDate: TimeStamp;							{ date EditionContainer was created }
 mdDate: TimeStamp;							{ date of last change }
 fdCreator: OSType;							{ file creator }
 fdType: OSType;							{ file type }
 container: EditionContainerSpec;			{ the Edition }
 END;

NewPublisherReply = RECORD
 canceled: BOOLEAN;							{ O }
 replacing : BOOLEAN;
 usePart: BOOLEAN;							{ I }
 preview: Handle;							{ I }
 previewFormat: FormatType;					{ I }
 container: EditionContainerSpec;			{ I/O }
 END;

NewSubscriberReply = RECORD
 canceled: BOOLEAN;							{ O }
 formatsMask: SignedByte;
 container: EditionContainerSpec;			{I/O}
 END;

SectionOptionsReply = RECORD
 canceled: BOOLEAN;							{ O }
 changed: BOOLEAN;							{ O }
 sectionH: SectionHandle;					{ I }
 action: ResType;							{ O }
 END;


ExpModalFilterProcPtr = ProcPtr;			{ FUNCTION Filter(theDialog: DialogPtr; VAR theEvent: EventRecord; itemOffset: INTEGER; VAR itemHit: INTEGER; yourDataPtr: Ptr): BOOLEAN; }
ExpDlgHookProcPtr = ProcPtr;				{ FUNCTION Hook(itemOffset, item: INTEGER; theDialog: DialogPtr; yourDataPtr: Ptr): INTEGER; }

FormatIOVerb = (ioHasFormat,ioReadFormat,ioNewFormat,ioWriteFormat);


FormatIOParamBlock = RECORD
 ioRefNum: LONGINT;
 format: FormatType;
 formatIndex: LONGINT;
 offset: LONGINT;
 buffPtr: Ptr;
 buffLen: LONGINT;
 END;


FormatIOProcPtr = ProcPtr;					{ FUNCTION IO(selector: FormatIOVerb; VAR PB: FormatIOParamBlock): OSErr; }

EditionOpenerVerb = (eoOpen,eoClose,eoOpenNew,eoCloseNew,eoCanSubscribe);


EditionOpenerParamBlock = RECORD
 info: EditionInfoRecord;
 sectionH: SectionHandle;
 document: FSSpecPtr;
 fdCreator: OSType;
 ioRefNum: LONGINT;
 ioProc: FormatIOProcPtr;
 success: BOOLEAN;
 formatsMask: SignedByte;
 END;


EditionOpenerProcPtr = ProcPtr;				{ FUNCTION Opener(selector: EditionOpenerVerb; VAR PB: EditionOpenerParamBlock): OSErr; }

CONST

{ 
 Section events now arrive in the message buffer using the AppleEvent format.
 The direct object parameter is an aeTemporaryIDParamType ('tid '). The temporary
 ID's type is rSectionType ('sect') and the 32-bit value is a SectionHandle.
 The following is a sample buffer
 
 name   offset contents
 ----   ------ --------
 
 header   0  'aevt'
 majorVersion 4  0x01
 minorVersion 6  0x01
 endOfMetaData 8  ';;;;' 
 directObjKey 12  '----' 
 paramType  16  'tid ' 
 paramLength  20  0x0008 
 tempIDType  24  'sect' 
 tempID    28  the SectionHandle <-- this is want you want}

sectionEventMsgClass = 'sect';
sectionReadMsgID = 'read';
sectionWriteMsgID = 'writ';
sectionScrollMsgID = 'scrl';
sectionCancelMsgID = 'cncl';

FUNCTION InitEditionPack: OSErr;
 INLINE $3F3C,$0011,$303C,$0100,$A82D;
FUNCTION NewSection(container: EditionContainerSpec;
                    sectionDocument: FSSpecPtr;
                    kind: SectionType;
                    sectionID: LONGINT;
                    initalMode: UpdateMode;
                    VAR sectionH: SectionHandle): OSErr;
 INLINE $303C,$0A02,$A82D;
FUNCTION RegisterSection(sectionDocument: FSSpec;
                         sectionH: SectionHandle;
                         VAR aliasWasUpdated: BOOLEAN): OSErr;
 INLINE $303C,$0604,$A82D;
FUNCTION UnRegisterSection(sectionH: SectionHandle): OSErr;
 INLINE $303C,$0206,$A82D;
FUNCTION IsRegisteredSection(sectionH: SectionHandle): OSErr;
 INLINE $303C,$0208,$A82D;
FUNCTION AssociateSection(sectionH: SectionHandle;
                          newSectionDocument: FSSpecPtr): OSErr;
 INLINE $303C,$040C,$A82D;
FUNCTION CreateEditionContainerFile(editionFile: FSSpec;
                                    fdCreator: OSType;
                                    editionFileNameScript: ScriptCode): OSErr;
 INLINE $303C,$050E,$A82D;
FUNCTION DeleteEditionContainerFile(editionFile: FSSpec): OSErr;
 INLINE $303C,$0210,$A82D;
FUNCTION OpenEdition(subscriberSectionH: SectionHandle;
                     VAR refNum: EditionRefNum): OSErr;
 INLINE $303C,$0412,$A82D;
FUNCTION OpenNewEdition(publisherSectionH: SectionHandle;
                        fdCreator: OSType;
                        publisherSectionDocument: FSSpecPtr;
                        VAR refNum: EditionRefNum): OSErr;
 INLINE $303C,$0814,$A82D;
FUNCTION CloseEdition(whichEdition: EditionRefNum;
                      successful: BOOLEAN): OSErr;
 INLINE $303C,$0316,$A82D;
FUNCTION EditionHasFormat(whichEdition: EditionRefNum;
                          whichFormat: FormatType;
                          VAR formatSize: Size): OSErr;
 INLINE $303C,$0618,$A82D;
FUNCTION ReadEdition(whichEdition: EditionRefNum;
                     whichFormat: FormatType;
                     buffPtr: UNIV Ptr;
                     VAR buffLen: Size): OSErr;
 INLINE $303C,$081A,$A82D;
FUNCTION WriteEdition(whichEdition: EditionRefNum;
                      whichFormat: FormatType;
                      buffPtr: UNIV Ptr;
                      buffLen: Size): OSErr;
 INLINE $303C,$081C,$A82D;
FUNCTION GetEditionFormatMark(whichEdition: EditionRefNum;
                              whichFormat: FormatType;
                              VAR currentMark: LONGINT): OSErr;
 INLINE $303C,$061E,$A82D;
FUNCTION SetEditionFormatMark(whichEdition: EditionRefNum;
                              whichFormat: FormatType;
                              setMarkTo: LONGINT): OSErr;
 INLINE $303C,$0620,$A82D;
FUNCTION GetEditionInfo(sectionH: SectionHandle;
                        VAR editionInfo: EditionInfoRecord): OSErr;
 INLINE $303C,$0422,$A82D;
FUNCTION GoToPublisherSection(container: EditionContainerSpec): OSErr;
 INLINE $303C,$0224,$A82D;
FUNCTION GetLastEditionContainerUsed(VAR container: EditionContainerSpec): OSErr;
 INLINE $303C,$0226,$A82D;
FUNCTION GetStandardFormats(container: EditionContainerSpec;
                            VAR previewFormat: FormatType;
                            preview: Handle;
                            publisherAlias: Handle;
                            formats: Handle): OSErr;
 INLINE $303C,$0A28,$A82D;
FUNCTION GetEditionOpenerProc(VAR opener: EditionOpenerProcPtr): OSErr;
 INLINE $303C,$022A,$A82D;
FUNCTION SetEditionOpenerProc(opener: EditionOpenerProcPtr): OSErr;
 INLINE $303C,$022C,$A82D;
FUNCTION CallEditionOpenerProc(selector: EditionOpenerVerb;
                               VAR PB: EditionOpenerParamBlock;
                               routine: EditionOpenerProcPtr): OSErr;
 INLINE $303C,$052E,$A82D;
FUNCTION CallFormatIOProc(selector: FormatIOVerb;
                          VAR PB: FormatIOParamBlock;
                          routine: FormatIOProcPtr): OSErr;
 INLINE $303C,$0530,$A82D;
FUNCTION NewSubscriberDialog(VAR reply: NewSubscriberReply): OSErr;
 INLINE $303C,$0232,$A82D;
FUNCTION NewSubscriberExpDialog(VAR reply: NewSubscriberReply;
                                where: Point;
                                expansionDITLresID: INTEGER;
                                dlgHook: ExpDlgHookProcPtr;
                                filterProc: ExpModalFilterProcPtr;
                                yourDataPtr: UNIV Ptr): OSErr;
 INLINE $303C,$0B34,$A82D;
FUNCTION NewPublisherDialog(VAR reply: NewPublisherReply): OSErr;
 INLINE $303C,$0236,$A82D;
FUNCTION NewPublisherExpDialog(VAR reply: NewPublisherReply;
                               where: Point;
                               expansionDITLresID: INTEGER;
                               dlgHook: ExpDlgHookProcPtr;
                               filterProc: ExpModalFilterProcPtr;
                               yourDataPtr: UNIV Ptr): OSErr;
 INLINE $303C,$0B38,$A82D;
FUNCTION SectionOptionsDialog(VAR reply: SectionOptionsReply): OSErr;
 INLINE $303C,$023A,$A82D;
FUNCTION SectionOptionsExpDialog(VAR reply: SectionOptionsReply;
                                 where: Point;
                                 expansionDITLresID: INTEGER;
                                 dlgHook: ExpDlgHookProcPtr;
                                 filterProc: ExpModalFilterProcPtr;
                                 yourDataPtr: UNIV Ptr): OSErr;
 INLINE $303C,$0B3C,$A82D;


{$ENDC} { UsingEditions }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

