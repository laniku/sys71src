{
	File:		EditionsPrivate.p

	Contains:	All private Edition Manger constants and record definitions

	Written by:	Nick Kledzik

	Copyright:	© 1989-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<12>	 8/27/91	JSM		Cleanup header.
		<11>	 1/14/91	ngk		add lots of comments
		<10>	  7/2/90	ngk		Removed 'publ'. Added fields to PubCB. Added Bits for bTSTs.
		 <9>	 5/31/90	ngk		Moved last edition used to preference file. Changed name of em
									globals and type to a pointer. Added traps for HXXXResFile.
		 <8>	  4/7/90	ngk		Define DyanmicArray(sic), FailInfo. Expanded edition file
									header. Added rangelock area to PubCB.
		 <7>	 3/17/90	ngk		Added DrawPreview to private routines.
		 <6>	 3/10/90	ngk		Change VolumeServices to use GetVolParms attribute. Removed
									dialogCodeH. Fixed selector for GetCurrentAppRefNum.
		 <5>	 2/25/90	ngk		Fix up constants that go in nextSection field.
		 <4>	 1/22/90	ngk		Added blockSize to SIOCB. Added symbolic names for standard
									openers.
		 <3>	  1/8/90	ngk		Added GetCurrentAppRefNum routine.
		 <2>	  1/6/90	ngk		renamed from dpInternalTypes to EditionsPrivate and moved to BBX
		 <1>	  1/6/90	ngk		rearranged PubCBs and expanded SectIOCB to suppport
		 							the I/O bottlenecks.
	   <2.3>	11/13/89	ngk		removed some constants
	   <2.2>	 11/4/89	ngk		Changed AppRefNum to be a handle to apps globals
	   <2.1>	10/25/89	ngk		Added some internal routine definitions.
	   <2.0>	10/13/89	ngk		Added dialogCodeH to EdtnMgrGlobals for handle to dialog code
									resource.
	   <1.9>	10/13/89	ngk		Added GotoInfo for goto after launching publisher
	   <1.8>	10/10/89	ngk		Changed AppRefNum to use ProcessSerialNumbers
	  <¥1.7>	 10/2/89	ngk		Added fdType and wakeUpTime to PubCB. Added wakeUpTime to
									header. Added new file type 'pub2'
	   <1.6>	 9/18/89	ngk		Changed FileSpec to CanonicalFileSpec. Change meaning of
									SectionType bits.
	   <1.5>	  9/7/89	ngk		Added lastVolMod and lastDirMod to support way cool polling
	   <1.4>	 8/29/89	ngk		Defined qUseAppName to simplify AppRefNum. Defined constants for
									open deny access modes. Removed app field from SIOCBrecord.
									Redid VolumeServices. Changed semantics of openCount to IOCount
									to be number of sections within Open/CloseEdition. Change
									pubCB.openAccess to openMode. Removed pubCB.publisherIOCB
	   <1.3>	  8/8/89	ngk		Added bit array of "volume services" to PubCB instaed of simple
									"shared". LastPubliation is now a PubSpec instead of a FileSpec.
									Added cNodeID field to PubCB, incase file is moved while in use.
									Made PubCB list a real circular-doublely-links list via
									PubCBLink. Added A6Link for use by dialogs in globals.
	   <1.2>	 6/11/89	ngk		made FormatList private, accessed procedurally through
									HasFormatEdition changed publication file format to seperate
									format list and allocation table reorganized variable size
									structures to have an initial and max size
	   <1.1>	 5/29/89	ngk		Changed PubControlBlock to use separate handle to Usage Info
									Changed SectionRecord to be longword aligned Added
									oldExitToShell to PerAppGlobals
	   <1.0>	 5/19/89	ngk		Submitted for first time

}

UNIT EditionsPrivate;

{===================================== EditionsPrivate INTERFACE ====================================}

INTERFACE

USES	
	Memory, Types, Editions;

{$SETC qUseAppName = FALSE }

CONST		
	kMaxGotoWait				=	 180;	{ max time to wait for publisher to register }
	kMaxAppLaunchTime			=	 300;	{ max time to wait for app to launch }
	
	kPollPeriod					=	1200;	{ 1200 ticks = 20 secs }
	
	kNoMoreSections				= 0;		{ put this in .nextSection field when it is last one }
	
	{ mask }
	kCanReadEditions			=	$01;
	kCanWriteEditions			=	$02;
	kDoNotAllowMultipleWriters	=	$04;	{ not fully implemented }
	kWarnIfMultipleWriters		=	$08;	
	kNotifyWhenSectionsRegister	=	$10;	{ not fully implemented }
	{ bits }
	kCanReadEditionsBit				=	0;
	kCanWriteEditionsBit			=	1;
	kDoNotAllowMultipleWritersBit	=	2;	
	kWarnIfMultipleWritersBit		=	3;	
	kNotifyWhenSectionsRegisterBit	=	4;	


	notThePublisherErr = -1;	{ ### this needs to be made public someday }

	{ stSubscriber	=	kCanReadEditions }
	{ stPublisher	=	kCanWriteEditions + kWarnIfMultipleWriters }

	{ resID of alias to last edition used }
	rLastEditionUsedString		= -5786;	{ name of file in preference folder with alias }
	rLastEditionAliasID			= 0;		{ res ID of alias in preference file }
	
	{ bogus values returned as default Opener and FormatIO procs }
	kStandardOpenerProcPtr		=	0;
	kStandardFormatIOProcPtr	=	0;
	kBogusFormatIOProcPtr		=	1;

TYPE
	pHandle			=	^Handle;
	pInteger		=	^INTEGER;
	pLongint		=	^LONGINT;
	pRect			=	^Rect;	


{====================================== Global Data ========================================}

TYPE
	{ the control blocks for each edition are kept in a circular, doubly linked list. }
	PubCBLinkHandle		=	^PubCBLinkPtr;
	PubCBLinkPtr		=	^PubCBLink;
	PubCBLink			=	RECORD
								nextPubCB:		PubCBLinkHandle;	{ for double linked list of PCBs }
								prevPubCB:		PubCBLinkHandle;	{ for double linked list of PCBs }
							END;


	{ each element if the fialure handler stack is a FailInfo. Each is a }
	{ local variable in the stackframe of the routine that installs the }
	{ handler.  They are linked together to make a stack.  }
	FailInfoPtr			=	^FailInfo;
	FailInfo			=	RECORD
								regs:			ARRAY [1..11] OF LONGINT;	{ registers A2-A7/D3-D7 saved here }
								returnTo: 		LONGINT;					{ location to jump to on exception }
								errorPtr:		^OSErr;						{ place to store OSErr that caused exception }
								nextInfo:		FailInfoPtr;				{ next handler in stack }
							END;

	{ When an app calls GotoPublisherSection and the publisher document }
	{ is not open, the 'odoc' AppleEvent is posted and then a GotoInfo }
	{ is created.  When the app finally opens the document and registers }
	{ the sections, each section is checked against the GotoInfo to see }
	{ if it is the publisher.  If it is the SectionScrollEvent can then }
	{ be sent. It can not be done earlier, because the SectionScrollEvent }
	{ requires the publisher section handle as the parameter, and that }
	{ does not exist until it is registered. }
	GotoInfoHandle		=	^GotoInfoPtr;			
	GotoInfoPtr			=	^GotoInfo;			
	GotoInfo			=	RECORD
								timeOut:				TimeStamp;	
								publisherDocVRefNum:	INTEGER;
								publisherDocID:			LONGINT;
								editionVRefNum:			INTEGER;
								editionID:				LONGINT;
								sectionID:				LONGINT;
							END;

	{ "global" information is needed for each application, as well as, for }
	{ the entire edition manager.  The information is kept for each application }
	{ as a relocatable block in the system heap.  The blocks are linked together }
	{ in a singly linked list.  The handle to a block is called a 'AppRefNum'. }
	PerAppGlobalsHandle		=	^PerAppGlobalsPtr;			
	PerAppGlobalsPtr		=	^PerAppGlobals;			
	PerAppGlobals			=	RECORD
									nextApp:				PerAppGlobalsHandle;		{ next PerAppGlobals in list }
									appPSN:					ProcessSerialNumber;		{ PSN of app (for event posting) }
									signature:				OSType;						{ fdCreator of app (for event posting) }
									sectionHandleListHead:	SectionHandle;				{ head of list of registered sections }
									emulator: 				EditionOpenerProcPtr;		{ EditionOpener for this app }
									initVersion:			INTEGER;					{ version of e.m. app wants to use }
									{$IFC qUseAppName}
									appName:				PACKED ARRAY [0..31] of byte; { name of app (for debugging) }
									{$ENDC}	
								END;
	AppRefNum				=	PerAppGlobalsHandle;				

 
 	
 	{ A variable length array, used in lots of places.  }
	DyanmicArrayHandle	=	^DyanmicArrayPtr;	
	DyanmicArrayPtr		=	^DyanmicArray;	
	DyanmicArray		=	RECORD
								{header:		some bytes}
								pad:			INTEGER;	{ long align }
								slotSize:		INTEGER;
								maxSlots:		INTEGER;
								lastUsedSlot:	INTEGER;
								{slots:			ARRAY [0..0] OF SignedBytes;}
							END;
							

{====================================== EditionFile I/O ========================================}

CONST
	kBadPosition		=	-1;		{ for uninitialized mark }
	kClosedFileRefNum	=	0;		{ for RefNum of unopened file }
	kMapVersion			=	1;		{ current publication file version }
	kInitialAllocCount	= 	4;		{ initial space for entries in pub map }
	kMaxAllocCount		= 	1000;	{ maximum space for entries in pub map }
	kInitialFormats		=	8;		{ initial space for formats }
	kMaxFormats			=	64;		{ maximum space for formats }
	kSync				=	FALSE;	{ used in PB file system calls }
	
	kHasMultipleFormatsBit = 7;		{ in FinderFlags bit that means edition has multiple }
									{ known formats, such as TEXT and PICT }

	dmDenyOtherWriters	=	$20;	{ open deny modes }	
	dmDenyOtherReaders	=	$10;
	dmRequestWritePerm	=	$02;
	dmRequestReadPerm	=	$01;
	dmNotOpen			=	$00;
	{ open deny modes bits }	
	dmDenyOtherWritersBit	=	5;	
	dmDenyOtherReadersBit	=	4;
	dmRequestWritePermBit	=	1;
	dmRequestReadPermBit	=	0;

	kSubscriberLockRetries			= 10;
	kPublisherLockRetries			= 10;
	kTicksBetweenPublisherRetries	= 10;
	
	kPublisherRangeLockStart	= 0;
	kPublisherRangeLockLength	= 256;
	kSubscriberRangeLockStart	= 128;
	kSubscriberRangeLockMask	= kPublisherRangeLockLength
									-kPublisherRangeLockStart
									-kSubscriberRangeLockStart-1; {=127}
	
TYPE
	{ The header of an edition file is 256 bytes.  The first 20 bytes are described }
	{ in EditionFileMinHeader.  The following 206 bytes are used for range locking. }
	EditionFileMinHeader	=	RECORD
									version:			LONGINT;
									formatsOffset:		LONGINT;	{ word count, then array of Format }
									formatsLength:		LONGINT;
									mapOffset:			LONGINT;	{ word count, then array of AllocationRecord }
									mapLength:			LONGINT;
								END;
CONST
	kEditionFileMinHeaderSize	= SizeOf(EditionFileMinHeader);

TYPE
	EditionFileHeader	=	RECORD
									minimalHeader:		EditionFileMinHeader;
									pad:				PACKED ARRAY [kEditionFileMinHeaderSize..kSubscriberRangeLockStart-1] OF SignedByte;
									rangeLockArea:		PACKED ARRAY [kSubscriberRangeLockStart..kPublisherRangeLockLength] OF SignedByte;
								END;

							
	{ When a section opens an edition for reading or writing, it is returned }
	{ an "EditionRefNum".  Internally, this is called a SIOCBHandle. }
	SIOCBHandle			=	^SIOCBPtr;
	SIOCBPtr			=	^SIOCBRecord;
	SIOCBRecord 		=	RECORD { Section I/O Control Block, a.k.a EditionRefNum }
								ioRefNum:	LONGINT;			{ refNum to pass to EditionIOProcPtr }
								ioProc:		FormatIOProcPtr;	{ EditionIOProcPtr to call }
								section:	SectionHandle;		{ section that started this I/O }
								blockSize:	Size;				{ min size to write format (not yet implemented) }
								{ Following this is a DyanmicArrayHandle of FormatPositionInfo's. }
								{ It is used to keep track of the current mark for each EditionRefNum. }
							END;
	
	FormatPositionInfoPtr = ^FormatPositionInfo;
	FormatPositionInfo	=	RECORD
								format:	FormatType;
								mark:	LONGINT;
								index:	LONGINT;
								length:	Size;
							END;
							
	
	{ An edition file contains a list of formats that it contains.  This is }
	{ a cache.  All the information could be reconstructed from the allocation }
	{ map, but doint so would be slow. }
	FormatPtr 			= ^Format;
	Format				=	RECORD
								theType:	FormatType;
								theLength:	LONGINT;	
							END;
	FormatListHandle	=	DyanmicArrayHandle;


	{ An edition file allocation map consists of an array of AllocationRecords. }
	{ Each record secifies the logical use of a physical, contiguous range of the file. }
	{ If the publisher completely wrote each format before moving on to the next, 
	{ then there will only be one AllocationRecord for each format. }
	AllocationRecordPtr = ^AllocationRecord;
	AllocationRecord =	RECORD
							theType:		FormatType;
							logicalStart:	LONGINT;
							logicalLen:		LONGINT;
							fileOffset:		LONGINT;
						END;

	AllocationMapHandle	=	DyanmicArrayHandle;




{====================================== PubControlBlock ========================================}

CONST
	kInitialApps 		=	2;		{ initial space allocated in TotalAppUsage }
	kBadVRefNum			= 	0;		{ vRefNum in control block set to this if it is unmounted }
	
TYPE
	VolumeAttributes	=	LONGINT;
	
	EachAppsUsagePtr	=	^EachAppsUsage;
	EachAppsUsage		= 	RECORD
								app:		AppRefnum;	{ which Application }
								useCount:	INTEGER;	{ # of registered sections for this pub & App }
								IOCount:	INTEGER;	{ # of sections doing I/O on this pub through this App }
							END;
		
	TotalAppUsageHandle	=	^TotalAppUsagePtr;
	TotalAppUsagePtr	=	^TotalAppUsage;
	TotalAppUsage		=	RECORD
								totalUseCount:	INTEGER;		{ cache of total number of sections using the control block }
								totalIOCount:	INTEGER;		{ cache of total number of sections doing I/O on this container }
							END;


	PubCBHandle			=	^PubCBPtr;
	PubCBPtr			=	^PubCBRecord;
	PubCBRecord 		=	RECORD { Publication Control Block }
								links:			PubCBLink;			{ for double linked list of PCBs }
								usageInfo:		TotalAppUsageHandle;{ usage info or NIL if not an edition file }
								volumeInfo:		VolumeAttributes;	{ info about volume container is on }
								pubCNodeID:		LONGINT;			{ fileID of container file }
								lastVolMod:		Timestamp;			{ last known volume mod date }
								lastDirMod:		Timestamp;			{ last known folder mod date }
								oldPubCB:		PubCBHandle;		{ or NIL if publisher is not writting }
								publisherApp:	AppRefNum;			{ or NIL if no publisher registered }
								publisher:		SectionHandle;		{ or NIL if no publisher registered }
								publisherAlias:	AliasHandle;		{ or NIL if publisher is not writting}
								publisherCount:	INTEGER;			{ number of register publishers }
								publisherKind:	SectionType;		{ the kind of publisher we have }
								fileMissing:	BOOLEAN;			{ the file is known to be non-existent }
								fileRefNum:		INTEGER;			{ or kClosedFile if closed }
								openMode: 		INTEGER;			{ read-only, read/write, map in memory }
								fileMark:		LONGINT;			{ cache of logical EOF when writing }
								rangeLockStart:	INTEGER;			{ 0 or offset into edition file of current lock }
								rangeLockLen:	INTEGER;			{ 0 or length of current rangelock }
								allocMap:		AllocationMapHandle;{ map of file when open }
								formats:		FormatListHandle;	{ formats from file when open }
								info:			EditionInfoRecord;	{ could be trimmed back to end of filename }
							END;


	EdtnMgrGlobalsPtrPtr	=	^EdtnMgrGlobalsPtr;
	EdtnMgrGlobalsPtr		=	^EdtnMgrGlobals;				
	EdtnMgrGlobals			=	RECORD
									pubCBlinks:			PubCBLink;				{ for double linked list of PCBs }
									perAppListHead:		PerAppGlobalsHandle;	{ for list of apps using edition mgr }
									nextPollTime:		LONGINT;				{ tickcount til next poll should happen }
									A6Link:				LONGINT;				{ used by dialogs to find stack frame }
									gotoHere:			GotoInfoHandle;			{ info needed after open-doc posted, until }
																				{ app registers the publisher }
									failureHandler:		FailInfoPtr;			{ top of failure handler stack }
									lastEditionUsed:	PubCBHandle;			{ if NIL then use alias in preference folder }
									volumeNotifyCode:	ARRAY [1..3] OF INTEGER;{ glue code to do a PACK trap from volNotice }
								END;
							
{====================================== Internal Routines ========================================}


	FUNCTION EditionMgrVolumeNotifier(volNoticeBlkPtr: {VolumeNoticeBlkPtr}Ptr): OSErr;
		INLINE $303C, $02F4, $A82D;

	FUNCTION DrawPreview(theData: Handle; theFormat: FormatType; previewRect: Rect): OSErr;
		INLINE $303C, $06F6, $A82D;

	FUNCTION GetCurrentAppRefNum(VAR thisApp: AppRefNum): OSErr;
		INLINE $303C, $02F8, $A82D;

	FUNCTION PostSectionEvent(sectionH: SectionHandle; toApp: AppRefNum; classID: ResType): OSErr;
		INLINE $303C, $06FA, $A82D;

	FUNCTION EditionMgrBackGroundTask: OSErr;
		INLINE $303C, $00FC, $A82D;

	FUNCTION QuitEditionPack: OSErr;
		INLINE $303C, $00FE, $A82D;


						
END. { EditionsPrivate }

