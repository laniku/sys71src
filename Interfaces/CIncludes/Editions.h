
/************************************************************

Created: Saturday, July 27, 1991 at 3:02 PM
 Editions.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1989-1991
  All rights reserved
	This file is used in these builds: BigBang


	Change History (most recent first):

		<26>	 7/30/91	JL		Updated Copyright.
		<25>	 6/17/91	JL		Checked in official MPW 3.2Ä version. Temporarily lost comments
									in NewSubscriberReply and NewPublisherReply; will be restored
									later. Took () off of kFormatLengthUnknown constant. Added
									inclusion of Dialogs to match Pascal file. Updated creation
									date. Temporarily lost updated copyright date; will be restored.
		<24>	  2/5/91	stb		ngk: correct some parameter names
		<23>	 1/30/91	JL		Checked in database generated file from DSG.  Grouped enums into
									packs of 20.
		<22>	 1/25/91	stb		JDR: change short to ScriptCode to match .p
		<21>	12/14/90	dba		<JDR> use void* wherever we had UNIV Ptr in the Pascal; use
									const in a few more places where we forgot; get rid of useless
									const for a handle
		<20>	 11/7/90	JL		Changed all #defines to anonymous enums
		<19>	10/10/90	VL		ngk, Added auto-include of Dialogs and Events.
		<18>	 10/9/90	JAL		MPW-ized this file so I could compare with it easier.
		<17>	 9/13/90	ngk		Changed file types for editions to be all lowercase.
		<16>	  8/2/90	ngk		Capitalize T in GoToPublisher. Changed updateMode constants to
										reflect new titles in options dialog.  Show sample buffer
									for section events.
		<15>	  7/3/90	ngk		Added new hooks and refcon constants for dialogs.
		<14>	 6/18/90	ngk		Changed CanonicalFIleSpec to FSSpec.
		<13>	 5/29/90	ngk		Add new types for edition files
		<13>	 5/29/90	ngk		Added new Finder types for edition files. Added format mask for
										NewSubscriberReply and bit constants for it.
		<12>	  5/4/90	ngk		Removed FindEditionContainerDialog.
		<11>	 4/11/90	ngk		Renamed callBackPtr to yourDataPtr. Renamed fields in
										EditionOpenerParamBlock.
		<10>	 3/30/90	ngk		Fix bug in CreateEditionContainerFile selector number.
		 <9>	 3/25/90	ngk		Moved script from PublisherReply into EditionContainerSpec.
									Added comments to Reply records. Changed some parameter names to
									match Pascal interface.
		 <8>	 3/20/90	ngk		Add constants for new AppleEvent format section events. Added
									script code to NewPublisherReply and CreateEditionContainerFile.
									Changed standard section resource type to 'sect' from 'dpsr'
		 <7>	 3/17/90	ngk		Fix selector number bugs.
		 <4>	 1/22/90	ngk		Added kFormatLengthUnknown
		 <3>	 1/11/90	ngk		Changed SectionType from enum to constants
		 <2>	  1/7/90	ngk		Fix comments. Renumbered routines for 7.0A3 build. Removed REZ
									conditionals. Moved error codes to Errors.h
		 <1>	  1/7/90	ngk		First checked in to BBS
		<1.8>	11/21/89	ngk		Changed int to short in a couple of places
		<1.7>	11/13/89	ngk		Changed SectionInfoDialog to SectionOptionsDialog. Removed //
									comments.
		<1.6>	 11/2/89	ngk		Moved EPPC stuff to its own header file
		<1.5>	10/10/89	ngk		Added Rez ability and new AcceptHighLevelEvent
		<1.4>	 10/4/89	ngk		Changed const UpdateMode values back to #define. ANSI C sucks.
									Renamed NewEditionFile to CreateEditionContainerFile.
		<1.3>	 10/2/89	ngk		Upgraded to Alpha Zero API
		<1.2>	 9/19/89	ngk		Added DeletePublicationFile, changed FileSpec to
									CanonicalFileSpec added filterProc to PublishAsDialog and
									SubscribeToDialog
		<1.1>	 8/29/89	ngk		Now uses PubSpecs and has warning codes. PublishAs and
									SubscribeTo use reply records.
		<1.0>	 6/24/89	ngk		Submitted for first time
************************************************************/


#ifndef __EDITIONS__
#define __EDITIONS__

#ifndef __MEMORY__
#include <Memory.h>
#endif

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __FILES__
#include <Files.h>
#endif

#ifndef __ALIASES__
#include <Aliases.h>
#endif

#ifndef __DIALOGS__
#include <Dialogs.h>
#endif


enum {


/* resource types  */

#define rSectionType 'sect'				/* ResType of saved SectionRecords */

/* section types */

 stSubscriber = 0x01,
 stPublisher = 0x0A,

 sumAutomatic = 0,						/* subscriber update mode - Automatically     */
 sumManual = 1,							/* subscriber update mode - Manually */
 pumOnSave = 0,							/* publisher update mode - OnSave            */
 pumManual = 1,							/* publisher update mode - Manually */

 kPartsNotUsed = 0,
 kPartNumberUnknown = -1,				/* misc */

 kPreviewWidth = 120,
 kPreviewHeight = 120,


#define kPublisherDocAliasFormat 'alis'
#define kPreviewFormat 'prvw'
#define kFormatListFormat 'fmts'

/* bits for formatsMask */

 kPICTformatMask = 1,
 kTEXTformatMask = 2,
 ksndFormatMask = 4,

/* Finder types for edition files */

#define kPICTEditionFileType 'edtp'
#define kTEXTEditionFileType 'edtt'
#define ksndEditionFileType 'edts'
#define kUnknownEditionFileType 'edtu'

/* pseudo-item hits for dialogHooks 
 the first if for NewPublisher or NewSubscriber Dialogs */

 emHookRedrawPreview = 150,

/* the following are for SectionOptions Dialog */
 emHookCancelSection = 160,
 emHookGoToPublisher = 161,
 emHookGetEditionNow = 162,
 emHookSendEditionNow = 162,
 emHookManualUpdateMode = 163,
 emHookAutoUpdateMode = 164
};
enum {

/* the refcon field of the dialog record during a modalfilter 
 or dialoghook contains one the following */

#define emOptionsDialogRefCon 'optn'
#define emCancelSectionDialogRefCon 'cncl'
#define emGoToPubErrDialogRefCon 'gerr'

 kFormatLengthUnknown = -1
};

typedef char SectionType;				/* one byte, stSubscriber or stPublisher */
typedef unsigned long TimeStamp;		/* seconds since 1904 */
typedef unsigned long FormatType;		/* similar to ResType */
typedef Handle EditionRefNum;			/* used in Edition I/O */
/* update modes */
typedef short UpdateMode;				/* sumAutomatic, pumSuspend, etc */

struct SectionRecord {
 SignedByte version;					/* always 0x01 in system 7.0 */
 SectionType kind;						/* stSubscriber or stPublisher */
 UpdateMode mode;						/* auto or manual */
 TimeStamp mdDate;						/* last change in document */
 long sectionID;						/* app. specific, unique per document */
 long refCon;							/* application specific */
 AliasHandle alias;						/* handle to Alias Record */
 long subPart;							/* which part of container file */
 struct SectionRecord **nextSection;	/* for linked list of app's Sections */
 Handle controlBlock;					/* used internally */
 EditionRefNum refNum;					/* used internally */
};

typedef struct SectionRecord SectionRecord;
typedef SectionRecord *SectionPtr, **SectionHandle;

struct EditionContainerSpec {
 FSSpec theFile;
 ScriptCode theFileScript;
 long thePart;
 Str31 thePartName;
 ScriptCode thePartScript;
};

typedef struct EditionContainerSpec EditionContainerSpec;
typedef EditionContainerSpec *EditionContainerSpecPtr;

struct EditionInfoRecord {
 TimeStamp crDate;						/* date EditionContainer was created */
 TimeStamp mdDate;						/* date of last change */
 OSType fdCreator;						/* file creator */
 OSType fdType;							/* file type */
 EditionContainerSpec container;		/* the Edition */
};

typedef struct EditionInfoRecord EditionInfoRecord;

struct NewPublisherReply {
 Boolean canceled;						/* O */
 Boolean replacing ;
 Boolean usePart;						/* I */
 Handle preview;						/* I */
 FormatType previewFormat;				/* I */
 EditionContainerSpec container;		/* I/O */
};

typedef struct NewPublisherReply NewPublisherReply;

struct NewSubscriberReply {
 Boolean canceled;						/* O */
 unsigned char formatsMask;
 EditionContainerSpec container;		/*I/O*/
};

typedef struct NewSubscriberReply NewSubscriberReply;

struct SectionOptionsReply {
 Boolean canceled;						/* O */
 Boolean changed;						/* O */
 SectionHandle sectionH;				/* I */
 ResType action;						/* O */
};

typedef struct SectionOptionsReply SectionOptionsReply;


typedef pascal Boolean (*ExpModalFilterProcPtr) (DialogPtr theDialog, EventRecord *theEvent,
 short itemOffset, short *itemHit, Ptr yourDataPtr);
typedef pascal short (*ExpDlgHookProcPtr) (short itemOffset,
  short itemHit, DialogPtr theDialog, Ptr yourDataPtr);

enum {ioHasFormat,ioReadFormat,ioNewFormat,ioWriteFormat};
typedef unsigned char FormatIOVerb;


struct FormatIOParamBlock {
 long ioRefNum;
 FormatType format;
 long formatIndex;
 unsigned long offset;
 Ptr buffPtr;
 unsigned long buffLen;
};

typedef struct FormatIOParamBlock FormatIOParamBlock;


typedef pascal short (*FormatIOProcPtr) (FormatIOVerb selector, FormatIOParamBlock *PB);

enum {eoOpen,eoClose,eoOpenNew,eoCloseNew,eoCanSubscribe};
typedef unsigned char EditionOpenerVerb;


struct EditionOpenerParamBlock {
 EditionInfoRecord info;
 SectionHandle sectionH;
 FSSpecPtr document;
 OSType fdCreator;
 long ioRefNum;
 FormatIOProcPtr ioProc;
 Boolean success;
 unsigned char formatsMask;
};

typedef struct EditionOpenerParamBlock EditionOpenerParamBlock;


typedef pascal short (*EditionOpenerProcPtr) (EditionOpenerVerb selector, FormatIOParamBlock *PB);




/* 
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
 tempID    28  the SectionHandle <-- this is want you want*/


#define sectionEventMsgClass 'sect'
#define sectionReadMsgID 'read'
#define sectionWriteMsgID 'writ'
#define sectionScrollMsgID 'scrl'
#define sectionCancelMsgID 'cncl'

#ifdef __cplusplus
extern "C" {
#endif
pascal OSErr InitEditionPack(void)
 = {0x3F3C,0x0011,0x303C,0x0100,0xA82D}; 
pascal OSErr NewSection(const EditionContainerSpec *container,
                        const FSSpec *sectionDocument,
                        SectionType kind,
                        long sectionID,
                        UpdateMode initalMode,
                        SectionHandle *sectionH)
 = {0x303C,0x0A02,0xA82D}; 
pascal OSErr RegisterSection(const FSSpec *sectionDocument,
                             SectionHandle sectionH,
                             Boolean *aliasWasUpdated)
 = {0x303C,0x0604,0xA82D}; 
pascal OSErr UnRegisterSection(SectionHandle sectionH)
 = {0x303C,0x0206,0xA82D}; 
pascal OSErr IsRegisteredSection(SectionHandle sectionH)
 = {0x303C,0x0208,0xA82D}; 
pascal OSErr AssociateSection(SectionHandle sectionH,
                              const FSSpec *newSectionDocument)
 = {0x303C,0x040C,0xA82D}; 
pascal OSErr CreateEditionContainerFile(const FSSpec *editionFile,
                                        OSType fdCreator,
                                        ScriptCode editionFileNameScript)
 = {0x303C,0x050E,0xA82D}; 
pascal OSErr DeleteEditionContainerFile(const FSSpec *editionFile)
 = {0x303C,0x0210,0xA82D}; 
pascal OSErr OpenEdition(SectionHandle subscriberSectionH,
                         EditionRefNum *refNum)
 = {0x303C,0x0412,0xA82D}; 
pascal OSErr OpenNewEdition(SectionHandle publisherSectionH,
                            OSType fdCreator,
                            const FSSpec *publisherSectionDocument,
                            EditionRefNum *refNum)
 = {0x303C,0x0814,0xA82D}; 
pascal OSErr CloseEdition(EditionRefNum whichEdition,
                          Boolean successful)
 = {0x303C,0x0316,0xA82D}; 
pascal OSErr EditionHasFormat(EditionRefNum whichEdition,
                              FormatType whichFormat,
                              Size *formatSize)
 = {0x303C,0x0618,0xA82D}; 
pascal OSErr ReadEdition(EditionRefNum whichEdition,
                         FormatType whichFormat,
                         void *buffPtr,
                         Size *buffLen)
 = {0x303C,0x081A,0xA82D}; 
pascal OSErr WriteEdition(EditionRefNum whichEdition,
                          FormatType whichFormat,
                          const void *buffPtr,
                          Size buffLen)
 = {0x303C,0x081C,0xA82D}; 
pascal OSErr GetEditionFormatMark(EditionRefNum whichEdition,
                                  FormatType whichFormat,
                                  unsigned long *currentMark)
 = {0x303C,0x061E,0xA82D}; 
pascal OSErr SetEditionFormatMark(EditionRefNum whichEdition,
                                  FormatType whichFormat,
                                  unsigned long setMarkTo)
 = {0x303C,0x0620,0xA82D}; 
pascal OSErr GetEditionInfo(const SectionHandle sectionH,
                            EditionInfoRecord *editionInfo)
 = {0x303C,0x0422,0xA82D}; 
pascal OSErr GoToPublisherSection(const EditionContainerSpec *container)
 = {0x303C,0x0224,0xA82D}; 
pascal OSErr GetLastEditionContainerUsed(EditionContainerSpec *container)
 = {0x303C,0x0226,0xA82D}; 
pascal OSErr GetStandardFormats(const EditionContainerSpec *container,
                                FormatType *previewFormat,
                                Handle preview,
                                Handle publisherAlias,
                                Handle formats)
 = {0x303C,0x0A28,0xA82D}; 
pascal OSErr GetEditionOpenerProc(EditionOpenerProcPtr *opener)
 = {0x303C,0x022A,0xA82D}; 
pascal OSErr SetEditionOpenerProc(EditionOpenerProcPtr opener)
 = {0x303C,0x022C,0xA82D}; 
pascal OSErr CallEditionOpenerProc(EditionOpenerVerb selector,
                                   EditionOpenerParamBlock *PB,
                                   EditionOpenerProcPtr routine)
 = {0x303C,0x052E,0xA82D}; 
pascal OSErr CallFormatIOProc(FormatIOVerb selector,
                              FormatIOParamBlock *PB,
                              FormatIOProcPtr routine)
 = {0x303C,0x0530,0xA82D}; 
pascal OSErr NewSubscriberDialog(NewSubscriberReply *reply)
 = {0x303C,0x0232,0xA82D}; 
pascal OSErr NewSubscriberExpDialog(NewSubscriberReply *reply,
                                    Point where,
                                    short expansionDITLresID,
                                    ExpDlgHookProcPtr dlgHook,
                                    ExpModalFilterProcPtr filterProc,
                                    void *yourDataPtr)
 = {0x303C,0x0B34,0xA82D}; 
pascal OSErr NewPublisherDialog(NewPublisherReply *reply)
 = {0x303C,0x0236,0xA82D}; 
pascal OSErr NewPublisherExpDialog(NewPublisherReply *reply,
                                   Point where,
                                   short expansionDITLresID,
                                   ExpDlgHookProcPtr dlgHook,
                                   ExpModalFilterProcPtr filterProc,
                                   void *yourDataPtr)
 = {0x303C,0x0B38,0xA82D}; 
pascal OSErr SectionOptionsDialog(SectionOptionsReply *reply)
 = {0x303C,0x023A,0xA82D}; 
pascal OSErr SectionOptionsExpDialog(SectionOptionsReply *reply,
                                     Point where,
                                     short expansionDITLresID,
                                     ExpDlgHookProcPtr dlgHook,
                                     ExpModalFilterProcPtr filterProc,
                                     void *yourDataPtr)
 = {0x303C,0x0B3C,0xA82D}; 
#ifdef __cplusplus
}
#endif

#endif
