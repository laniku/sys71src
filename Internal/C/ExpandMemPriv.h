/************************************************************

	File:		ExpandMemPriv.h

	Contains:	C language definitions for Expandmem low mem globals
	
	Warning:	Be sure to check that this is up to date with SysPrivateEqu.a 

	Written by:	Nick Kledzik

	Copyright:	© 1990-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	  <SM31>	 1/14/94	ged		Added the jSWModemSoundVector field to ExpandMem to support
									software modem sound using different modems (initially for
									Blackbird).
	  <SM30>	11/11/93	fau		aek		Added Expansion Manager Globals Ptr. Bumped version number
									to	132.
	  <SM29>	 9/12/93	SAM		Changed emFigmentGlobals to emHeapUtilsGlobals which is more
									accurate.
	  <SM28>	 9/12/93	joe		Synced up with SysPrivateEqu.a...added emFigmentGlobals and
									bumped version to 131.
	  <SM27>	  6/7/93	CSS		Add expandmem to stash the control handle during thumb dragging.
									Also, sync with Reality:
		<70>	 5/20/93	KWR		Added emSpeechRecognitionGlobals, macros and bumped the version number
		<69>	 5/20/93	PKE		Change names for obsolete fields emNumer, emDenom to emUnused1,
									emUnused2.
	  <SM26>	05/19/93	HY		Added emIDEGlobals and updated emCurVersion.
	  <SM25>	 4/22/93	CSS		Updated from Reality (except UniversalProcPtrs). (Also updated
									the comments from GS below). Comments follow:
		<66>	 3/29/93	DTY		Add emAuxiliaryWindowHashTable and emAuxiliaryControlHashTable.
		<65>	 3/26/93	YK		Add emHasMultiScript.  This flag will be true if non-Roman
									script system is installed, but still be zero until the Procee
									Mgr is initialized.  Most of the code for multi lingual support
									can be skipped by checking this value.
		<64>	 3/25/93	DTY		Fix typo.
		<63>	 3/25/93	DTY		Add field to store PixMapHandle used for drawing defproc
									gadgets.
		<62>	 3/18/93	SES		Steven Swenson - added a longword of storage for the Internal
									Modem Manager and bumped the version number.
		<61>	 3/11/93	ngk		Rename emUsed2 to emWindowMgrFlags
	  <SM24>	 4/11/93	chp		Add accessor macros for the new emDMADispGlobs field.
	  <SM21>	 3/10/93	GS		Getting in touch with Reality....
		<66>	 3/29/93	DTY		Add emAuxiliaryWindowHashTable and emAuxiliaryControlHashTable.
		<65>	 3/26/93	YK		Add emHasMultiScript.  This flag will be true if non-Roman
									script system is installed, but still be zero until the Procee
									Mgr is initialized.  Most of the code for multi lingual support
									can be skipped by checking this value.
		<64>	 3/25/93	DTY		Fix typo.
		<63>	 3/25/93	DTY		Add field to store PixMapHandle used for drawing defproc
									gadgets.
		<62>	 3/18/93	SES		Steven Swenson - added a longword of storage for the Internal
									Modem Manager and bumped the version number.
		<61>	 3/11/93	ngk		Rename emUsed2 to emWindowMgrFlags
	  <SM20>	 2/20/93	SAM		Added emDMADispGlobs for DMAManager/Dispatcher globals.
	  <SM19>	 1/27/93	PN		Add emStartTicks extended memory global for "startticks" in
									ListMgrPack
		<SM1>	12/09/92	HI		Added emIsDragging field to be used as a flag to determine
									whether OSEventAvail was called from DragTheRgn or not. The
									flag is set by DragTheRgn only. OSEventAvail uses this flag
									to bypass the HelpMgr patch code if called from DragTheRgn.
									(Hoon Im)
		<52>	10/28/92	DTY		Fix macros for emProcessMgrExists.
		<51>	10/28/92	JMF		Added emButtonManagerGlobals in the emUnused1 spot and added
									emSerialManagerGlobals in the first long of three in the 
									emUnused3 spot.
		<50>	10/27/92	JDR		Deleted unnecessary include of Memory.h.
		<49>	10/26/92	DTY		Create Get/Set macro pairs for each ExpandMem global. These
									macros help to isolate code from the actual globals, and should
									be used to access ExpandMem fields from now on. Also changed
									emUnused4 to be emWorldScriptIIPrintingGlobals.
		<48>	10/15/92	aen		Went back again and changed 'fndr' names to 'emFndr' for
									Brian and Dean
		<47>	10/14/92	gs		Steal a long word from emUnused1 for FSCommon Library.
		<46>	10/14/92	aen		Went back and put version <>'s beside stuff I changed.
		<45>	10/14/92	aen		Added fndrDeskRgn, fndrDeskRgnTracking, fndrDeskRgnChange and
									bumped the version number to 0x129 (Andy Nicholas)
		<44>	 10/8/92	KST		emUnused4 is now used by WS II printing stuff.
		<43>	 7/21/92	bbm		Add emNetBootGlobals for Network Booting and Appletalk stuff.
									(see Steve Roth)
		<42>	  7/6/92	gbm		Add the emDragGlobals entry (for Finder’s drag-o-matically cool
									stuff)
		<41>	  7/6/92	PN		Take out emCommToolBoxTable and emBigModel and put them in
									CTBBlock
		<40>	  7/6/92	JSM		Remove emPrinterPortCache, it’s no longer needed by the Icon
									Utilities.
		<39>	  7/1/92	PN		Adding emCommToolboxTable and emBigModel for SuperMario
		<38>	 6/25/92	PN		Add emRectRgn for SuperMario
		<37>	  6/4/92	JSM		Add emPPCPromptForUserGlobals from SuperMario.
		<36>	 5/11/92	JSM		#1029437 <DC>: Add emProcessMgrExists, set by the Process Mgr
									after it installs itself. This lets other parts of system
									software that want to call routines that require the Process Mgr
									(like _BeginSystemMode or _GetNextHighLevelEvent) to easily
									check if the boot process is far enough along yet instead of
									calling Gestalt all the time. Add emScrollSpeedGlobals from
									SuperMario. Renumber emUnused fields. Don’t update the
									emCurVersion field, it’s kind of stupid to always do this during
									development builds.
		<35>	 4/23/92	TN		Replaced emUnused4 with emResrvMemSemaphore for MemoryMgr roll
									in (as part of SuperMario).
		<34>	 4/17/92	PKE		#1027387,<DTY>: Rename emItlDirectGetIntl to emItlDontUnlockYet
		<33>	 4/13/92	YK		Rename unused fields that were used by InputUtils.  I thought
									they were renamed and used by TSM…
		<32>	 4/10/92	JSM		Tweak a comment from the last revision.
		<31>	  4/9/92	RLM		Bump the version number too, even though our size didn't change…
		<30>	  4/9/92	RLM		Moved emDialogGlobals to an emUnused slot, also updated from
									SuperMario…
		<29>	  4/7/92	JSM		Split up emPackGlobals to show unused areas since we really
									don’t use very much of this block.  emUnused fields should be
									used before adding on to ExpandMem again.
		<28>	 3/19/92	DC		Added the printerPortCache for bug fix to Icon Utilities
		<27>	  3/2/92	DTY		Add entry for LowMemoryPrintingPatchGlobals
		<26>	 2/25/92	DC		Fixed my GetExpandMem macro. It was intended to be used as in
									"GetExpandMem()->emVersion". It is now fixed such that that will
									work.
		<25>	 2/12/92	DTY		Add emOpenFontFiles, a counter of how many font files in the
									Fonts folder are open. We want to keep a cap on this number.
									It’s currently 128.
		<24>	 1/19/92	DTY		Add emAppleTalkInactiveOnBoot. This is set in BeforePatches.a.
									Other parts of the boot process, and the Chooser look at this to
									determine whether or not to use network resources.
		<23>	12/09/91	HY		Added emFFSwapMMUMode ptr to ExpandMem. Needed for Foster Farms
									ROM (030 LC). Also bumped version number to 0x0121.
		<22>	11/26/91	GMR		Added CursorGlobal ptr to ExpandMem.
		<21>	11/20/91	DC		Add GetExpandMem() macro for retrieving the the ExpandMem
									handle.  Added ExpandMemHndl and ExpandMemPtr types.
		<20>	 11/2/91	DTY		Add emScanOverrideMaps to allow programs like ResEdit to turn
									off resource overriding.
		<19>	 11/1/91	DTY		Silly me. I need to remember the override map, too.
		<18>	 11/1/91	DTY		Rename emTopOverrideMap to emLastOverridenMap to reflect it’s
									new use.
		<17>	10/28/91	DTY		Add emResourceCache for more resource override stuff.
		<16>	10/24/91	sam		Added Tsunami Printing Manager global to ExpandMemRec.
		<15>	10/23/91	YK		Adding a handle and a counter to ExpandMemRec for InputUtils
									Package
		<14>	10/17/91	DTY		Added emTopOverrrideMap for Resource Override stuff.
		<13>	 10/8/91	JH		Adding pack count global for Dictionary Manager and ProcHelper
		<12>	 10/8/91	JH		Adding a handle for Dictionary Manager Package.
		<11>	 10/8/91	BBM		One of the 7.0.1 team misunderstood the allocation process. He
									allocated an expandmem global from the forked off regatta
									sources, without checking to see if it was already allocated. It
									was. The Tsunami projects global gets smashed by 7.0.1. Since
									Tsunami didn’t ship with the new printers, we were lucky this
									time. Move the Tsunami global past the two globals that 7.0.1
									allocated and bump the version number.  (also added a comment to
									warn about changing cache size)
		<10>	 8/29/91	DC		Changed emIconCluts to indicate that it is a ptr to the icon
									globals in stead of a global.
		 <9>	 8/27/91	JSM		Cleanup header.
		 <8>	  6/4/91	DFH		Added emMessageManagerGlobals.
		 <7>	 3/13/91	RLC		stb,#83253 - Add a new expandmem (emMinSysHeapFreeSpace) so that
									SaveBits() can accurately judge how much free system heap space
									should be left after allocating from the system heap.
		 <6>	  2/7/91	djw		<hjr> Add new field in ExpandmemRec for SndPrimitives - a
									pointer to a vector table of sound primitives.
		 <5>	 1/30/91	VL		dba, #Whiteboard7.0b4q6HowDoYouLikeThisBugNumberChris?: Add one
									more field ancestorRgnsCalced to ExpandMem for PaintOne and
									PaintBehind.
		 <4>	 1/14/91	KIP		<dba> add vectors for jSetupSoundInterrupt,
									jSuspendSoundInterrupt, jResumeSoundInterrupt and
									jAcknowledgeSoundInterrupt.
		 <3>	12/14/90	dnf		add jSCSIFreeHook vector
		 <2>	 10/2/90	DFH		Added jSyncWait, jAfterFSQHook, jCmdDone, and jDispatchNext.
		 <1>	  9/6/90	ngk		first checked in
		 <0>	  9/6/90	ngk		Converted from {IntAIncludes}SysPrivateEqu.a

************************************************************/
		
#ifndef __EXPANDMEMPRIV__
#define __EXPANDMEMPRIV__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __SYSEQU__
#include <SysEqu.h>
#endif

#ifndef __QUICKDRAW__
#include <QuickDraw.h>
#endif

#define GetExpandMem()	(*((ExpandMemPtr *)ExpandMem))
#define emCurVersion	0x0133			// version	<SM21/LW3><62><SM27><SM30>
#define emItlCacheSize	16				// bytes in cache.  WARNING, you cann’t change this
										// without distroying all fixed offsets from
										// emItlNeedUnlock on.  Don’t do it!

/*___________________________________________________________________________

 Extended Low Memory area available on all machines
 
*/

struct ExpandMemRec  
{
	short		emVersion; 				//			ds.w	1 				; version of expanded memory
	long		emSize;					//			ds.l	1 				; length of em
	Ptr			emIntlGlobals; 			//			ds.l	1 				; international globals pointer
	long		emKeyDeadState;			//			ds.l	1 				; Key1Trans, Key2Trans dead state
	long		emKeyCache;				//			ds.l	1 				; KCHR keyboard cache
	long		emIntlDef;				//			ds.l	1				; Reserved for Intl
	char		emFirstKeyboard;		//			ds.b	1				; flag byte
	char		emAlign;				//			ds.b	1				; long-align until we need this storage
	char		emItlCache[emItlCacheSize];	//		ds.b	emItlCacheSize	; reserve room for cache
	char		emItlNeedUnlock;		//			ds.b	1				; for pack6
	char		emItlDontUnlockYet;		//			ds.b	1				; for pack6						<34>
	short		emItlFiller;			//			ds.b	2				; Reserved room
	char		emScriptsInstalled;		//			ds.b	1				; number of installed scripts
	char		fill1;
	short		emTwoCursorsFlag;		//			ds.w	1				; indicates split cursor and if emCursor2Rect is high cursor
	Rect		emCursor2Rect;			//			ds.w	4				; top, left, bottom, right edges of split cursor: initialized to 0
	char		emFmtOrderHFlag;		//			ds.b	1				; flag to indicate a handle was allocated
	char		fill2;
	long		emDirection;			//			ds.l	1				; direction param for C2P for both offsets
	char		emMeasureLine;			//			ds.b	1				; flag that says to measure the whole line
	char		fill3;
	long		emCleanWordBrk;			//			ds.l	1				; storage for 32-bit clean defWordBrk address
	char		emNewFont;				//			ds.b	1				; textStyle.tsFont: the only field I fill in
	char		fill4;
	short		emNewStyle[4];			//			ds.w	4				; SetRsrved params: flag.b, textStylePtr.l, mode.w
	Handle		emBufferHandle;			//			ds.l	1				; handle for text buffering
	char		emUnsynchedFlag;		//			ds.b	1				; indicates unsynched keyboard and font
	char		emTExtra[3];			//			ds.b	3				; extra TE bytes
	short		emBufferLen;			//			ds.w	1				; length of text in buffer
	long		emSERDVars;				//			ds.l	1				; Serial Driver Globals
	long		emGestalt;				//			ds.l	1				; Gestalt Globals
	long		emLayoutGlobals;		//			ds.l	1				; Layout Mgr Globals
	long		emTSMGlobals;			//			ds.l	1				; Text-Service Mgr Globals
	long		emSplineKey;			//			ds.l	1				; Bass Fonts Globals
	long		emSnarfGlobals;			//			ds.l	1				; Snarf Man
	long		emLAPGlobals;			//			ds.l	1				; AppleTalk globals
	long		emLMgrGlobals;			//			ds.l	1				; LAP Mgr globals
	long		emHelpGlobals;			//			ds.l	1				; Help Mgr Globals
	long		emPPCGlobals;			//			ds.l	1				; PPC Mgr globals
	long		emDataPub;				//			ds.l	1				; Data Publications globals
	long		emReliability;			//			ds.l	1				; Reliability manager globals
	long		emjRunSlotHandlrs;		//			ds.l	1				; for slot mgrs
	long		emFolderCache;			//			ds.l	1				; used by Folder Manager
	
	ProcPtr		vDoErase;				//	ds.l	1
	ProcPtr		vCaretDisplay;			//	ds.l	1				; Used by TextEdit for vectors
	ProcPtr		vGetLRPosition;			//	ds.l	1				;   to patch Rom
	ProcPtr		vGetRLPosition;			//	ds.l	1
	ProcPtr		vOnLineEnd;				//	ds.l	1
	ProcPtr		vCaretInsideRun;		//	ds.l	1
	ProcPtr		vSetDirection;			//	ds.l	1
	ProcPtr		vGetDirection;			//	ds.l	1
	ProcPtr		vGetStylesInOrder;		//	ds.l	1
	ProcPtr		vteGetFormatOrder;		//	ds.l	1
	ProcPtr		vGetWidth;				//	ds.l	1
	ProcPtr		vGetCurScript;			//	ds.l	1
	ProcPtr		vOnSameLine;			//	ds.l	1
	ProcPtr		vMeasureWidth;			//	ds.l	1
	ProcPtr		vMeasureWholeRun;		//	ds.l	1
	ProcPtr		vHiliteLineEnds;		//	ds.l	1
	ProcPtr		vInvrtRectangle;		//	ds.l	1
	ProcPtr		vPixelWidths;			//	ds.l	1
	ProcPtr		vTEBufferText;			//	ds.l	1
	ProcPtr		vDumpBuffer;			//	ds.l	1
	ProcPtr		vCursorMovement;		//	ds.l	1
	ProcPtr		vTestRunDirection;		//	ds.l	1
	ProcPtr		vBufferChar;			//	ds.l	1
	ProcPtr		vSetFont2Keyboard;		//	ds.l	1
	ProcPtr		vSetKeyboard2Font;		//	ds.l	1
	ProcPtr		vStyleGuts;				//	ds.l	1
	ProcPtr		vConcatRuns;			//	ds.l	1
	
	long		resourceMgrDirID;		//			ds.l	1				; dirID one-shot for Resource Mgr
	long		emLAPAGlobals;			//			ds.l	1				; LAP Mgr (router) globals
	long		emMailGlobals;			//			ds.l	1				; AppleMail globals
	long		emADASGlobals;			//			ds.l	1				; ADAS globals
	
	long		emELAPGlobals;			//			ds.l	1				; EtherTalk LAP globals
	
	long		soundMgrGlobals;		//			ds.l	1				; one global for ALL machines
	
	long		emWindowListGlobals;	//			ds.l	1				; <29> globals for layerless windowing

	long		emDragGlobals;			//			ds.l	1				; <42> globals for Finder drag stuff

	long		emFSCommon;				//			ds.l	1				; <47> globals for FSCommon Library Modules

	long		emButtonMgrGlobals;		//			ds.l	1				; <29><51> globals for Button Manager (Not emUnused1 anymore)

	short		emPack8Globals;			//			ds.w	1				; <29> globals for Apple Event Manager package
	short		emPack9Globals;			//			ds.w	1				; <29> globals for PPC Browser package

	short		emProcessMgrExists;		//			ds.w	1				; <36> true when Process Mgr is running

	short		emPack11Globals;		//			ds.w	1				; <29> globals for Edition Manager package

	short		emWindowMgrFlags;		//			ds.w	1				; <61> flags to speed CheckUpdateIn (previously emUnused2)

	short		emPack13Globals;		//			ds.w	1				; <29> globals for Data Access Manager package
	short		emPack14Globals;		//			ds.w	1				; <29> globals for Balloon Help package

	long		emResrvMemSemaphore;	//			ds.l	1				; <35> semaphore for ResrvMem moved to here.

	short		emPack15Globals;		//			ds.w	1				; <29> globals for Picture Utilities package

	long		emSerialMgrGlobals;		//			ds.l	1				; <51> globals for Serial Manager (one long out of emUnused3)
	long		emLanguagePackGlobals;	//			ds.l	1				; <53> globals for LanguagePackExtension (one long out of emUnused3)
	
	long		emStartTicks;			//			ds.l	1				; PN global used by ListMgrPack

	long		emRectRgn;				//			ds.l	1				; <SM10> global used by WindowMgr routine <PN>

	long		emPPCPromptForUserGlobals;	//		ds.l	1				; <37> global used by PPC’s PromptForUser routine

	long		emScrollSpeedGlobals;	//			ds.l	1				; <36> global used by scroll speed throttling

	long		emDialogGlobals;		//			ds.l	1				; <30> Dialog Manager Globals

	long		emAppleEvents;			//			ds.l	1				; Apple Events (switched for each application)
	
	Rect		sysErrorUpdateRect;		//			ds.w	4				; rectangle for updating after SysError box goes away
	
	Ptr			emItlSysCachePtr;		//			ds.l	1				; pointer to system itl cache				
	Ptr			emScriptMapPtr;			//			ds.l	1				; pointer to script mapping/sorting data	
	Ptr			emLangMapPtr;			//			ds.l	1				; pointer to language mapping/sorting data	
	
	long		emUnused1;				//			ds.l	1				; was emNumer (obsolete), now unused				<69>
	long		emUnused2;				//			ds.l	1				; was emDenom (obsolete), now unused				<69>
	Ptr			emIconCluts;			//			ds.l	1				; Ptr to global icon info				
	Handle		emScriptAppGlobals;		//			ds.l	1				; Handle to application-specific script globals	>
	long		emAppleEventsGlobal;	//			ds.l	1				; Apple Events/Apple Scripts global pointer (not switched) 
	Handle		emEditionMgrPerApp;		//			ds.l	1				; EditionMgr global (switched) 

// Note: These vectors are not used by the local file system.  They exist to provide a cleaner interface
// to AppleShare and FileShare.  Thus, you can't change these vectors and assume that you're patching
// the file system. (This may change, however, so don't patch them expecting to only affect AppleShare and 
// FileShare, either).
	long		jSyncWait;				//			ds.l	1				; points to the top of the HFS sync call spin loop
	long		jAfterFSQHook;			//			ds.l	1				; points into FSQueue just after return from calling fsQueueHook
	long		jCmdDone;				//			ds.l	1				; points to the top of File System Command Done processing
	long		jDispatchNext;			//			ds.l	1				; points into CmdDone where it checks for another call to process
	long		jSCSIFreeHook;			//			ds.l	1				; vector called by SCSI Mgr every time it frees the bus
										//									; this vector is used by the File System to complete SCSI Busy deferrals 

// routines to manage the sound interrupt source

	ProcPtr		jSetupSoundInterrupt;
	ProcPtr		jSuspendSoundInterrupt;
	ProcPtr		jResumeSoundInterrupt;
	ProcPtr		jAcknowledgeSoundInterrupt;
	
// flag for PaintOne and PaintBehind

	short		emAncestorRgnsCalced;
	
	long		emSndPrimitives;		//			ds.l	1				; points to a vector table of sound primitive routines
	
	long		emMinSysHeapFreeSpace;	//			ds.l	1				; contains a minimum memory value for sysheap free after allocations <7>

	long		emHwPrivTable;			//			ds.l	1				; Ptr to a jump table for HwPriv's selectors						<11>
	long		emKeyTMTaskPtr;			//			ds.l	1				; Ptr to a TimeMgr task that Eclipse Keyswitch uses to shut down	<11>

	long		emMessageManagerGlobals[3];	//		ds.l	3				; global information for Message Manager

// Handle for Dictionary package
	Handle		emDictionaryMgrPackHandle;		//	ds.l	1				;handle to the package code
	short		emDictionaryMgrUseCount;		//	ds.w	1

	long		emWorldScriptIIPrintingGlobals;	//	ds.l	1				; <44> it is now used by WS II printing stuff, so don't use it
	short		emHasMultiScript;				//	ds.w	1				;  true when non-Roman script system is installed.  (but false until the Process Mgr is initialized)

// Resource Override stuff
	Handle		emResourceCache;				//	ds.l	1				; Information for _CountResources and _GetIndResource
	short		emLastMapOverridden;			//	ds.w	1				; Reference number of last map that was overriden
	short		emOverrideMapRefNum;			//	ds.w	1				; Reference number of override map
	Boolean		emScanOverrideMaps;				//	ds.w					; Boolean determining whether or nor override maps are scanned for resources
// Tsunami Printing Manager Non-Swapped globals
	long		emPrintingGlobals;				//	ds.l	1				; Tsunami Printing Manager non-swapped printing globals
// Cursor Dev global pointer
	long		emCursorGlobals;				//	ds.l	1				; Ptr to new CursorDev globals				<22>

	long		emButtonIntGlobals;				//	ds.l	1				; Ptr to Button Interrupt globals. previously Ptr to "real" SwapMMUMode routine					

	short		emAppleTalkInactiveOnBoot;		//	ds.w	1				; True if AppleTalk was off when the machine booted. <24>		

	short		emOpenFontFiles;				//	ds.w	1				; Count of open font files in the Fonts folder. <25>

	Handle		emLowMemoryPrintingGlobals;		//	ds.l	1				; Globals used by LowMemoryPrintingPatches	<27>

	Handle		emNetBootGlobals;				//	ds.l	1				; Handle to globals used by emNetBootGlobals for Network Booting and Appletalk stuff.	<43>

	Handle		emFndrDeskRgn;					//  ds.l	1				; Handle to region maintained by Bungee Finder if fndrDeskRgnTracking is true <45> <48>

	short		emFndrDeskRgnTracking;			//  ds.w	1				; If true, the Bungee Finder will keep an up-to-date region handle in fndrDeskRgn of the icons on the desktop <45> <48>

	short		emFndrDeskRgnChange;			//  ds.w	1				; Always incremented by the Bungee Finder for every change made to the desktop <45> <48>

	Ptr			emDisplayManagerGlobals;		//	ds.l	1				; Pointer to globals used by Display Manager

	long		emTranslationMgrGlobals;		//	ds.l	1				; Pointer to globals used by Translation Manager (Macintosh Easy Open)

	Handle		emTingeInfo;					//	ds.l	1				; Handle to tinge information for the Tinge Manager

	char		emIsDragging;					//	ds.b	1				; Set within DragTheRgn and cleared before exiting; if true, HelpMgr
	char		emIsDraggingSlop[3];			//	ds.b	3				; patch in OSEventAvail is bypassed.			<SM1>

	long		emRenoGlobals;					//	ds.l	1				; Ptr to Reno Globals							<LW2>

	long		emDMADispatchGlobals;			//	ds.l	1				; DMA dispatch globals ptr	<SM20>

	long		emInternalModemMgrGlobals;		//	ds.l	1				; Internal modem manager globals 				<62>

	Handle		emGadgetPixMap;					//	ds.l	1				; PixMapHandle used by defprocs to draw gadgets

	Ptr			emAuxiliaryWindowHashTable;		//	ds.l	1				; Pointer to hash table of auxiliary window records
	Ptr			emAuxiliaryControlHashTable;	//	ds.l	1				; Pointer to hash table of auxiliary control records

	long		emIDEGlobals;					//  ds.l	1				; IDE driver globals							<SM26>

	void		*emSpeechRecognitionGlobals;	//	ds.l	1				; <70> Ptr to Speech Recognition Globals

	long		emControlHandle;				//  ds.l	1				; control handle used in _DragTheRgn when the thumb is being dragged so we can send a draw thumb outline message. <SM27> CSS

	long		emHeapUtilsGlobals;				//	ds.l	1				; Heap Utilities Manager globals

	Ptr			emExpansionBusGlobals;			//	ds.l	1				; Ptr to Expansion Manager globals
	
	ProcPtr		jSWModemSoundVector;			//	ds.l	1				; Vector to control routine for software modem sound
};

typedef struct ExpandMemRec	ExpandMemRec;
typedef ExpandMemRec *ExpandMemPtr;

#define	GetExpandMemVersion()							(GetExpandMem())->emVersion
#define	SetExpandMemVersion(version)					(GetExpandMem())->emVersion = version
#define	GetExpandMemSize()								(GetExpandMem())->emSize
#define	SetExpandMemSize(size)							(GetExpandMem())->emSize = size
#define	GetExpandMemIntlGlobals()						(GetExpandMem())->emIntlGlobals
#define	SetExpandMemIntlGlobals(intlGlobals)			(GetExpandMem())->emIntlGlobals = intlGlobals
#define GetExpandMemKeyDeadState()						(GetExpandMem())->emKeyDeadState
#define	SetExpandMemKeyDeadState(keyDeadState)			(GetExpandMem())->emKeyDeadState = keyDeadState
#define	GetExpandMemKeyCache()							(GetExpandMem())->emKeyCache
#define SetExpandMemKeyCache(keyCache)					(GetExpandMem())->emKeyCache = keyCache
#define	GetExpandMemIntlDef()							(GetExpandMem())->emIntlDef
#define SetExpandMemIntlDef(intlDef)					(GetExpandMem())->emIntlDef = intlDef
#define	GetExpandMemFirstKeyboard						(GetExpandMem())->emFirstKeyboard
#define SetExpandMemFirstKeyboard(firstKeyboard)		(GetExpandMem())->emFirstKeyboard = firstKeyboard
// emAlign
#define	GetExpandMemItlCache(cacheIndex)				(GetExpandMem())->emItlCache[cacheIndex]
#define	SetExpandMemItlCache(cacheIndex, itlCache)		(GetExpandMem())->emItlCache[cacheIndex] = itlCache
#define	GetExpandMemItlNeedUnlock()						(GetExpandMem())->emItlNeedUnlock
#define	SetExpandMemItlNeedUnlock(itlNeedUnlock)		(GetExpandMem())->emItlNeedUnlock = itlNeedUnlock
#define	GetExpandMemItlDontUnlockYet()					(GetExpandMem())->emItlDontUnlockYet
#define SetExpandMemItlDontUnlockYet(itlDontUnlockYet)	(GetExpandMem())->emItlDontUnlockYet = itlDontUnlockYet
// emFiller
#define	GetExpandMemScriptsInstalled()					(GetExpandMem())->emScriptsInstalled
#define SetExpandMemScriptsInstalled(scriptsInstalled)	(GetExpandMem())->emScriptsInstalled = scriptsInstalled
// fill1
#define	GetExpandMemTwoCursorsFlag()					(GetExpandMem())->emTwoCursorsFlag
#define	SetExpandMemTwoCursorsFlag(twoCursorsFlag)		(GetExpandMem())->emTwoCursorsFlag = twoCursorsFlag
#define	GetExpandMemCursor2Rect()						(GetExpandMem())->emCursor2Rect
#define	SetExpandMemCursor2Rect(cursor2Rect)			(GetExpandMem())->emCursor2Rect = cursor2Rect
#define	GetExpandMemFmtOrderHFlag()						(GetExpandMem())->emFmtOrderHFlag
#define	SetExpandMemFmtOrderHFlag(fmtOrderHFlag)		(GetExpandMem())->emFmtOrderHFlag = fmtOrderHFlag
// fill2
#define	GetExpandMemDirection()							(GetExpandMem())->emDirection
#define	SetExpandMemDirection(direction)				(GetExpandMem())->emDirection = direction
#define	GetExpandMemMeasureLine()						(GetExpandMem())->emMeasureLine
#define SetExpandMemMeasureLine(measureLine)			(GetExpandMem())->emMeasureLine = measureLine
// fill3
#define	GetExpandMemCleanWordBreak()					(GetExpandMem())->emCleanWordBreak
#define SetExpandMemCleanWordBreak(cleanWordBreak)		(GetExpandMem())->emCleanWordBreak = cleanWordBreak
#define	GetExpandMemNewFont()							(GetExpandMem())->emNewFont
#define	SetExpandMemNewFont(newFont)					(GetExpandMem())->emNewFont = newFont
// fill4
#define	GetExpandMemNewStyleFlag()						(GetExpandMem())->emNewStyle[1]
#define SetExpandMemNewStyleFlag(newStyleFlag)			(GetExpandMem())->emNewStyle[1] = newStyleFlag
#define	GetExpandMemNewStyleTextStylePtr()				(*((long *) &((GetExpandMem())->emNewStyle[2])))
#define SetExpandMemNewStyleTextStylePtr(textStylePtr)	(*((long *) &((GetExpandMem())->emNewStyle[2]))) = textStylePtr
#define	GetExpandMemNewStyleMode()						(GetExpandMem())->emNewStyle[4]
#define SetExpandMemNewStyleMode(newStyleMode)			(GetExpandMem())->emNewStyle[4] = newStyleMode
#define	GetExpandMemBufferHandle()						(GetExpandMem())->emBufferHandle
#define	SetExpandMemBufferHandle(bufferHandle)			(GetExpandMem())->emBufferHandle = bufferHandle
#define	GetExpandMemUnsynchedFlag()						(GetExpandMem())->emUnsynchedFlag
#define SetExpandMemUnsynchedFlag(unsynchedFlag)		(GetExpandMem())->emUnsynchedFlag = unsynchedFlag
#define	GetExpandMemTExtra(extraIndex)					(GetExpandMem())->emTExtra[extraIndex]
#define SetExpandMemTExtra(extraIndex, extraValue)		(GetExpandMem())->emTExtra[extraIndex] = extraValue
#define GetExpandMemBufferLen()							(GetExpandMem())->emBufferLen
#define SetExpandMemBufferLen(bufferLen)				(GetExpandMem())->emBufferLen = bufferLen
#define GetExpandMemSERDVars()							(GetExpandMem())->emSERDVars
#define SetExpandMemSERDVars(serdVars)					(GetExpandMem())->emSERDVars = serdVars
#define GetExpandMemGestalt()							(GetExpandMem())->emGestalt
#define SetExpandMemGestalt(gestalt)					(GetExpandMem())->emGestalt = gestalt
#define GetExpandMemLayoutGlobals()						(GetExpandMem())->emLayoutGlobals
#define SetExpandMemLayoutGlobals(layoutGlobals)		(GetExpandMem())->emLayoutGlobals = layoutGlobals
#define GetExpandMemTSMGlobals()						(GetExpandMem())->emTSMGlobals
#define SetExpandMemTSMGlobals(tsmGlobals)				(GetExpandMem())->emTSMGlobals = tsmGlobals
#define GetExpandMemSplineKey()							(GetExpandMem())->emSplineKey
#define SetExpandMemSplineKey(splineKey)				(GetExpandMem())->emSplineKey = splineKey
#define	GetExpandMemSnarfGlobals()						(GetExpandMem())->emSnarfGlobals
#define	SetExpandMemSnarfGlobals(snarfGlobals)			(GetExpandMem())->emSnarfGlobals = snarfGlobals
#define GetExpandMemLAPGlobals()						(GetExpandMem())->emLAPGlobals
#define SetExpandMemLAPGlobals(lapGlobals)				(GetExpandMem())->emLAPGlobals = lapGlobals
#define	GetExpandMemLMgrGlobals()						(GetExpandMem())->emLMgrGlobals
#define	SetExpandMemLMgrGlobals(lmgrGlobals)			(GetExpandMem())->emLMgrGlobals = lmgrGlobals
#define	GetExpandMemHelpGlobals()						(GetExpandMem())->emHelpGlobals
#define	SetExpandMemHelpGlobals(helpGlobals)			(GetExpandMem())->emHelpGlobals = helpGlobals
#define	GetExpandMemPPCGlobals()						(GetExpandMem())->emPPCGlobals
#define	SetExpandMemPPCGlobals(ppcGlobals)				(GetExpandMem())->emPPCGlobals = ppcGlobals
#define	GetExpandMemDataPub()							(GetExpandMem())->emDataPub
#define	SetExpandMemDataPub(dataPub)					(GetExpandMem())->emDataPub = dataPub
#define	GetExpandMemReliability()						(GetExpandMem())->emReliability
#define	SetExpandMemReliability(reliability)			(GetExpandMem())->emReliability = reliability
#define	GetExpandMemjRunSlotHandlrs()					(GetExpandMem())->emjRunSlotHandlrs
#define	SetExpandMemjRunSlotHandlrs(jRunSlotHandlrs)	(GetExpandMem())->emjRunSlotHandlrs = jRunSlotHandlrs
#define	GetExpandMemFolderCache()						(GetExpandMem())->emFolderCache
#define	SetExpandMemFolderCache(folderCache)			(GetExpandMem())->emFolderCache = folderCache

#define	GetExpandMemResourceMgrDirID()					(GetExpandMem())->resourceMgrDirID
#define	SetExpandMemResourceMgrDirID(resourceMgrDirID)	(GetExpandMem())->resourceMgrDirID = resourceMgrDirID
#define	GetExpandMemLAPAGlobals()						(GetExpandMem())->emLAPAGlobals
#define	SetExpandMemLAPAGlobals(lapaGlobals)			(GetExpandMem())->emLAPAGlobals = lapaGlobals
#define	GetExpandMemMailGlobals()						(GetExpandMem())->emMailGlobals
#define	SetExpandMemMailGlobals(mailGlobals)			(GetExpandMem())->emMailGlobals = mailGlobals
#define	GetExpandMemADASGlobals()						(GetExpandMem())->emADASGlobals
#define	SetExpandMemADASGlobals(adasGlobals)			(GetExpandMem())->emADASGlobals = adasGlobals
#define	GetExpandMemELAPGlobals()						(GetExpandMem())->emELAPGlobals
#define	SetExpandMemELAPGlobals(elapGlobals)			(GetExpandMem())->emELAPGlobls = elapGlobals
#define	GetExpandMemSoundMgrGlobals()					(GetExpandMem())->soundMgrGlobals
#define	SetExpandMemSoundMgrGlobals(soundMgrGlobals)	(GetExpandMem())->soundMgrGlobals = soundMgrGlobals
#define	GetExpandMemWindowListGlobals()					(GetExpandMem())->emWindowListGlobals
#define	SetExpandMemWindowListGlobals(windowListGlobals)	(GetExpandMem())->emWindowListGlobals = windowListGlobals
#define	GetExpandMemDragGlobals()						(GetExpandMem())->emDragGlobals
#define	SetExpandMemDragGlobals(dragGlobals)			(GetExpandMem())->emDragGlobals = dragGlobals
#define	GetExpandMemFSCommon()							(GetExpandMem())->emFSCommon
#define	SetExpandMemFSCommon(fsCommon)					(GetExpandMem())->emFSCommon = fsCommon
#define	GetExpandMemButtonMgrGlobals()					(GetExpandMem())->emButtonMgrGlobals					//<51>
#define	SetExpandMemButtonMgrGlobals(btnMgrGlobals)		(GetExpandMem())->emButtonMgrGlobals = btnMgrGlobals	//<51>
#define	GetExpandMemPack8Globals()						(GetExpandMem())->emPack8Globals
#define	SetExpandMemPack8Globals(pack8Globals)			(GetExpandMem())->emPack8Globals = pack8Globals
#define	GetExpandMemPack9Globals()						(GetExpandMem())->emPack9Globals
#define	SetExpandMemPack9Globals(pack9Globals)			(GetExpandMem())->emPack9Globals = pack9Globals
#define	GetExpandMemProcessMgrExists()					(GetExpandMem())->emProcessMgrExists
#define	SetExpandMemProcessMgrExists(processMgrExists)	(GetExpandMem())->emProcessMgrExists = processMgrExists
#define	GetExpandMemPack11Globals()						(GetExpandMem())->emPack11Globals
#define	SetExpandMemPack11Globals(pack11Globals)		(GetExpandMem())->emPack11Globals = pack11Globals
#define	GetExpandMemPack13Globals()						(GetExpandMem())->emPack13Globals
#define	SetExpandMemPack13Globals(pack13Globals)		(GetExpandMem())->emPack13Globals = pack13Globals
#define	GetExpandMemPack14Globals()						(GetExpandMem())->emPack14Globals
#define	SetExpandMemPack14Globals(pack14Globals)		(GetExpandMem())->emPack14Globals = pack14Globals
#define	GetExpandMemResrvMemSemaphore()					(GetExpandMem())->emResrvMemSemaphore
#define	SetExpandMemResrvMemSemaphore(resrvMemSemaphore)	(GetExpandMem())->emResrvMemSemaphore = resrvMemSemaphore
#define	GetExpandMemPack15Globals()						(GetExpandMem())->emPack15Globals
#define	SetExpandMemPack15Globals(pack13Globals)		(GetExpandMem())->emPack15Globals = pack15Globals
#define	GetExpandMemSerialMgrGlobals()					(GetExpandMem())->emSerialMgrGlobals					//<51>
#define	SetExpandMemSerialMgrGlobals(serMgrGlobals)		(GetExpandMem())->emSerialMgrGlobals = serMgrGlobals	//<51>
#define	GetExpandMemLanguagePackGlobals()				(GetExpandMem())->emLanguagePackGlobals							//<53>
#define	SetExpandMemLanguagePackGlobals(langPackGlobals)	(GetExpandMem())->emLanguagePackGlobals = langPackGlobals	//<53>
// emUnused3
#define	GetExpandMemRectRgn()							(GetExpandMem())->emRectRgn
#define	SetExpandMemRectRgn(rectRgn)					(GetExpandMem())->emRectRgn = rectRgn
#define	GetExpandMemPPCPromptForUserGlobals()			(GetExpandMem())->emPPCPromptForUserGlobals
#define	SetExpandMemPPCPromptForUserGlobals(ppcPrompForUserGlobals)	(GetExpandMem())->emPPCPromptForUserGlobals = ppcPromptForUserGlobals
#define	GetExpandMemScrollSpeedGlobals()				(GetExpandMem())->emScrollSpeedGlobals
#define	SetExpandMemScrollSpeedGlobals(scrollSpeedGlobals)	(GetExpandMem())->emScrollSpeedGlobals = scrollSpeedGlobals
#define	GetExpandMemDialogGlobals()						(GetExpandMem())->emDialogGlobals
#define	SetExpandMemDialogGlobals(dialogGlobals)		(GetExpandMem())->emDialogGlobals = dialogGlobals
#define	GetExpandMemAppleEvents()						(GetExpandMem())->emAppleEvents
#define	SetExpandMemAppleEvents(appleEvents)			(GetExpandMem())->emAppleEvents = appleEvents
#define	GetExpandMemSysErrorUpdateRect()				(GetExpandMem())->emSysErrorUpdateRect
#define	SetExpandMemSysErrorUpdateRect(sysErrorUpdateRect)	(GetExpandMem())->emSysErrorUpdateRect = sysErrorUpdateRect
#define	GetExpandMemItlSysCachePtr()					(GetExpandMem())->emItlSysCachePtr
#define	SetExpandMemItlSysCachePtr(itlSysCachePtr)		(GetExpandMem())->emItlSysCachePtr = itlSysCachePtr
#define	GetExpandMemScriptMapPtr()						(GetExpandMem())->emScriptMapPtr
#define	SetExpandMemScriptMapPtr(scriptMapPtr)			(GetExpandMem())->emScriptMapPtr = scriptMapPtr
#define	GetExpandMemLangMapPtr()						(GetExpandMem())->emLangMapPtr
#define	SetExpandMemLangMapPtr(langMapPtr)				(GetExpandMem())->emLangMapPtr = langMapPtr
#define	GetExpandMemNumer()								(GetExpandMem())->emNumer
#define	SetExpandMemNumer(numer)						(GetExpandMem())->emNumer = numer
#define	GetExpandMemDenom()								(GetExpandMem())->emDenom
#define	SetExpandMemDenom(denom)						(GetExpandMem())->emDenom = denom
#define	GetExpandMemIconCluts()							(GetExpandMem())->emIconCluts
#define	SetExpandMemIconCluts(iconCluts)				(GetExpandMem())->emIconCluts = iconCluts
#define	GetExpandMemScriptAppGlobals()					(GetExpandMem())->emScriptAppGlobals
#define	SetExpandMemScriptAppGlobals(scriptAppGlobals)	(GetExpandMem())->emScriptAppGlobals = scriptAppGlobals
#define	GetExpandMemAppleEventsGlobal()					(GetExpandMem())->emAppleEventsGlobal
#define	SetExpandMemAppleEventsGlobal(appleEventsGlobal)	(GetExpandMem())->emAppleEventsGlobal = appleEventsGlobal
#define	GetExpandMemEditionMgrPerApp()					(GetExpandMem())->emEditionMgrPerApp
#define	SetExpandMemEditionMgrPerApp(editionMgrPerApp)	(GetExpandMem())->emEditionMgrPerApp = editionMgrPerApp

#define	GetExpandMemAncestorRgnsCalced()				(GetExpandMem())->emAncestorRgnsCalced
#define	SetExpandMemAncestorRgnsCalced(ancestorRgnsCalced)	(GetExpandMem())->emAncestorRgnsCalced = ancestorRgnsCalced
#define	GetExpandMemSndPrimitives()						(GetExpandMem())->emSndPrimitives
#define	SetExpandMemSndPrimitives(sndPrimitives)		(GetExpandMem())->emSndPrimitives = sndPrimitives
#define	GetExpandMemMinSysHeapFreeSpace()				(GetExpandMem())->emMinSysHeapFreeSpace
#define	SetExpandMemMinSysHeapFreeSpace(minSysHeapFreeSpace)	(GetExpandMem())->emMinSysHeapFreeSpace = minSysHeapFreeSpace
#define	GetExpandMemHwPrivTable()						(GetExpandMem())->emHwPrivTable
#define	SetExpandMemHwPrivTable(hwPrivTable)			(GetExpandMem())->emHwPrivTable = hwPrivTable
#define	GetExpandMemKeyTMTaskPtr()						(GetExpandMem())->emKeyTMTaskPtr
#define	SetExpandMemKeyTMTaskPtr(keyTMTaskPtr)			(GetExpandMem())->emKeyTMTaskPtr = keyTMTaskPtr
#define	GetExpandMemMessageManagerGlobals(index)		(GetExpandMem())->emMessageManagerGlobals[index]
#define	SetExpandMemMessageManagerGlobals(index, messageManagerGlobals)	(GetExpandMem())->emMessageManagerGlobals[index] = messageManagerGlobals
#define	GetExpandMemDictionaryMgrPackHandle()			(GetExpandMem())->emDictionaryMgrPackHandle
#define	SetExpandMemDictionaryMgrPackHandle(dictionaryMgrPackHandle)	(GetExpandMem())->emDictionaryMgrPackHandle = dictionaryMgrPackHandle
#define	GetExpandMemDictionaryMgrUseCount()				(GetExpandMem())->emDictionaryMgrUseCount
#define	SetExpandMemDictionaryMgrUseCount(dictionaryMgrUseCount)	(GetExpandMem())->emDictionaryMgrUseCount = dictionaryMgrUseCount
#define	GetExpandMemWorldScriptIIPrintingGlobals()		(GetExpandMem())->emWorldScriptIIPrintingGlobals
#define	SetExpandMemWorldScriptIIPrintingGlobals(worldScriptIIPrintingGlobals)	(GetExpandMem())->emWorldScriptIIPrintingGlobals = worldScriptIIPrintingGlobals
#define	GetExpandMemHasMultiScript()					(GetExpandMem())->emHasMultiScript
#define	SetExpandMemHasMultiScript(hasMultiScript)		(GetExpandMem())->emHasMultiScript = hasMultiScript
#define	GetExpandMemResourceCache()						(GetExpandMem())->emResourceCache
#define	SetExpandMemResourceCache(resourceCache)		(GetExpandMem())->emResourceCache = resourceCache
#define	GetExpandMemLastMapOverridden()					(GetExpandMem())->emLastMapOverridden
#define	SetExpandMemLastMapOverridden(lastMapOverridden)	(GetExpandMem())->emLastMapOverridden = lastMapOverridden
#define	GetExpandMemOverrideMapRefNum()					(GetExpandMem())->emOverrideMapRefNum
#define	SetExpandMemOverrideMapRefNum(overrideMapRefNum)	(GetExpandMem())->emOverrideMapRefNum = overrideMapRefNum
#define	GetExpandMemScanOverrideMaps()					(GetExpandMem())->emScanOverrideMaps
#define	SetExpandMemScanOverrideMaps(scanOverrideMaps)	(GetExpandMem())->emScanOverrideMaps = scanOverrideMaps
#define	GetExpandMemPrintingGlobals()					(GetExpandMem())->emPrintingGlobals
#define	SetExpandMemPrintingGlobals(printingGlobals)	(GetExpandMem())->emPrintingGlobals = printingGlobals
#define	GetExpandMemCursorGlobals()						(GetExpandMem())->emCursorGlobals
#define	SetExpandMemCursorGlobals(cursorGlobals)		(GetExpandMem())->emCursorGlobals = cursorGlobals
#define	GetExpandMemFFSwapMMUMode()						(GetExpandMem())->emFFSwapMMUMode
#define	SetExpandMemFFSwapMMUMode(ffSwapMMUMode)		(GetExpandMem())->emFFSwapMMUMode = ffSwapMMUMode
#define	GetExpandMemAppleTalkInactiveOnBoot()			(GetExpandMem())->emAppleTalkInactiveOnBoot
#define	SetExpandMemAppleTalkInactiveOnBoot(appleTalkInactiveOnBoot)	(GetExpandMem())->emAppleTalkInactiveOnBoot = appleTalkInactiveOnBoot
#define	GetExpandMemOpenFontFiles()						(GetExpandMem())->emOpenFontFiles
#define	SetExpandMemOpenFontFiles(openFontFiles)		(GetExpandMem())->emOpenFontFiles = openFontFiles
#define	GetExpandMemLowMemoryPrintingGlobals()			(GetExpandMem())->emLowMemoryPrintingGlobals
#define	SetExpandMemLowMemoryPrintingGlobals(lowMemoryPrintingGlobals)	(GetExpandMem())->emLowMemoryPrintingGlobals = lowMemoryPrintingGlobals
#define	GetExpandMemNetBootGlobals()					(GetExpandMem())->emNetBootGlobals
#define	SetExpandMemNetBootGlobals(netBootGlobals)		(GetExpandMem())->emNetBootGlobals = netBootGlobals
#define	GetExpandMemFndrDeskRgn()						(GetExpandMem())->emFndrDeskRgn
#define	SetExpandMemFndrDeskRgn(fndrDeskRgn)			(GetExpandMem())->emFndrDeskRgn = fndrDeskRgn
#define	GetExpandMemFndrDeskRgnTracking()				(GetExpandMem())->emFndrDeskRgnTracking
#define	SetExpandMemFndrDeskRgnTracking(fndrDeskRgnTracking)	(GetExpandMem())->emFndrDeskRgnTracking = fndrDeskRgnTracking
#define	GetExpandMemFndrDeskRgnChange()					(GetExpandMem())->emFndrDeskRgnChange
#define	SetExpandMemFndrDeskRgnChange(fndrDeskRgnChange)	(GetExpandMem())->emFndrDeskRgnChange = fndrDeskRgnChange
#define	GetExpandMemDisplayManagerGlobals()					(GetExpandMem())->emDisplayManagerGlobals
#define	SetExpandMemDisplayManagerGlobals(displayGlobals)	(GetExpandMem())->emDisplayManagerGlobals = displayGlobals
#define	GetExpandMemTranslationMgrGlobals()					(GetExpandMem())->emTranslationMgrGlobals
#define	SetExpandMemTranslationMgrGlobals(tmGlobals)		(GetExpandMem())->emTranslationMgrGlobals = tmGlobals
#define GetExpandMemTingeInfo()							(GetExpandMem())->emTingeInfo
#define SetExpandMemTingeInfo(tingeInfo)				(GetExpandMem())->emTingeInfo = (Handle) tingeInfo
#define GetExpandMemIsDragging()						(GetExpandMem())->emIsDragging
#define SetExpandMemIsDragging(isDragging)				(GetExpandMem())->emIsDragging = isDragging
#define	GetExpandMemRenoGlobals()						(GetExpandMem())->emRenoGlobals
#define SetExpandMemRenoGlobals(renoGlobals)			(GetExpandMem())->emRenoGlobals = renoGlobals
#define GetExpandMemDMADispatchGlobals()				(GetExpandMem())->emDMADispatchGlobals
#define SetExpandMemDMADispatchGlobals(dmaDispatchGlobals)	(GetExpandMem())->emDMADispatchGlobals) = emDMADispatchGlobals
#define GetExpandMemInternalModemMgrGlobals()			(GetExpandMem())->emInternalModemMgrGlobals
#define SetExpandMemInternalModemMgrGlobals(modemMgrGlobals) (GetExpandMem())->emInternalModemMgrGlobals = modemMgrGlobals
#define GetExpandMemGadgetPixMap()						(GetExpandMem())->emGadgetPixMap
#define SetExpandMemGadgetPixMap(gadgetPixMap)			(GetExpandMem())->emGadgetPixMap = (Handle) gadgetPixMap
#define GetAuxiliaryWindowHashTable()					(GetExpandMem())->emAuxiliaryWindowHashTable
#define SetAuxiliaryWindowHashTable(windowHashTable)	(GetExpandMem())->emAuxiliaryWindowHashTable = windowHashTable
#define GetAuxiliaryControlHashTable()					(GetExpandMem())->emAuxiliaryControlHashTable
#define SetAuxiliaryControlHashTable(controlHashTable)	(GetExpandMem())->emAuxiliaryControlHashTable = controlHashTable
#define GetSpeechRecognitionGlobals()					(GetExpandMem())->emSpeechRecognitionGlobals
#define SetSpeechRecognitionGlobals(asrToolbox)			(GetExpandMem())->emSpeechRecognitionGlobals = asrToolbox
#define GetExpandMemExpansionBusGlobals()				(GetExpandMem())->emExpansionBusGlobals
#define SetExpandMemExpansionBusGlobals(emGblPtr)		(GetExpandMem())->emExpansionBusGlobals = emGblPtr
#endif
