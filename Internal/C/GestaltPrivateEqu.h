/*
	File:		GestaltPrivateEqu.h

	Contains:	Private Gestalt information.

	Written by:	Jim Reekes

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	  <SM24>	 12/2/93	JDR		Updated gestaltBugFixAttrsTwo, and gestaltBugFixAttrsThree.
	  <SM23>	11/22/93	pdw		Got rid of Trailing comma warning on gestaltM280.
	  <SM22>	11/12/93	ged		Oops, fixed the last checkin.
	  <SM21>	11/12/93	ged		Added gestaltSingerSnd to response list for gestaltSoundHardware
									selector.
	  <SM20>	11/10/93	fau		Update from SuperMunggio <SMG2>.
	  <SMG2>	10/26/93	fau		Added TNTProto1 gestalt equ.
	  <SM19>	 11/9/93	RLE		added gestalts for 603-based PowerBooks
	  <SM18>	 11/9/93	KW		forgot commas.
	  <SM17>	 11/9/93	KW		added gestalts for STP machines
	  <SM16>	 11/8/93	JRH		Removed gestaltDBLite33, gestaltDBLite16, and gestaltEscher33.
									gestaltEscher25 is now gestaltYeagerFSTN.
	  <SM15>	 8/16/93	BG		Update machinetype values to something closer to current.
	  <SM14>	  6/6/93	BT		Add gestaltEightToSixteenMegBlockMoveFix,
									gestaltReleaseTheFontFlagFix, gestaltMSFlightSimDrawCrsrFix, and
									gestaltRISCV0ResMgrPatches
	  <SM13>	 4/16/93	gs		Add gestaltMtCheckFix to 'bugz' bits for fix in MountVol when
									scanning Catalog and Extents files.
	  <SM12>	 4/11/93	chp		Added SerialDMA HAL selector 'shal'.
	  <SM11>	  4/8/93	KW		changing gestaltCyclone40 -->78 and gestaltTempest33 --> 79
	  <SM10>	  4/8/93	CSS		Update GestaltGlobals from Reality and bump the Gestalt version
									number so that I can add the field EDiskSize.  This is
									necessary, because when VM is install the boot globals
									unavailable so the routine get EDiskSize doesn't function
									properly.
									<19>	  4/4/93	ngk		Remove unused fields in GestaltGlobals.
									<18>	 3/30/93	JDR		Added gestaltMoveHHiExtraStackSpace
									<17>	 3/29/93	ngk		To support GestaltValues, change table to be an array of
																GestaltEntry's. Bump gestaltVers to 3. Add slotsUsed to
																GestaltGlobals to reduce calls to GetHandleSize.
									<16>	 3/10/93	mgl		Add gestaltMultiLayerSupport bit to gestaltOSAttr.
									<15>	  3/4/93	JK		Added bug bit for PMgrOp fix to support MIDI on PowerBooks.
									<14>	 2/26/93	mgl		Change the bit number for gestaltExtendedDebuggerSupport. OCE
																had been using bit 10 for gestaltBgndMouseDownSupport for
																sometime, but hadn't merged into Reality until now.
									<13>	12/21/92	JSM		Add GestaltProcPtr.
									<12>	12/19/92	mgl		Added gestaltExtendedDebuggerSupport bit to gestaltOSAttr for
																extended debugger support in the Process Manager.
									<11>	12/15/92	JDR		Removed gestaltPowerBook145, since it's already in Gestalt.h.
																Removed gestaltFosterFarms because it's already in Gestalt.h as
																gestaltMacLCII.
									<10>	 12/9/92	RLE		update machine type information for new machines
	   <SM9>	  4/5/93	jb		Added gestaltAwacsSnd constant for PDM, also added gestaltPDM
									machineType constant.
	   <SM8>	 3/31/93	rab		Removed two change mark comments that were breaking the build.
	   <SM7>	 3/31/93	CSS		Added gestaltMoveHHiExtraStackSpace and gestaltPMgrMIDIFix
	   								in "bugy" selector (from Reality).
	   <SM6>	 12/7/92	CSS		Update from Reality:
									 <9> 12/4/92 KIP	remove trailing comma from enums to avoid syntax error message
														in Think C.
									 <8> 12/4/92 KIP	Add sndIntRestoreFix fix for Scruffy.
									 <7> 12/3/92 csd	Added bug fix selectors for the January 93 tune up. Also fixed
														the places where both define and = were used.
	   <SM5>	 12/4/92	fau		Added gestaltTempest33 and gestaltCyclone40.  Changed
									gestaltCyclone to gestaltCyclone33 and gestaltTempest to
									gestaltTempest25.
	   <SM4>	 12/3/92	fau		Added a gestaltTempest.
		 <6>	 8/19/92	JDR		gestaltColumbia was defined twice.
		 <5>	  8/7/92	JDR		Changed gestaltHeadphonePluggedIn into
									gestaltQuickTimeUsesNewSoundMgrCalls.
		 <4>	  8/3/92	CSS		Add some pre-released machines from SuperMario.
		 <3>	  8/1/92	JDR		Added flag gestaltQuickTimeUsesNewSoundMgrCalls.
		 <2>	 7/18/92	JDR		Syntax changes so I could include this with Think C.
		 <1>	 7/17/92	JDR		first checked in

*/


#ifndef __GESTALTPRIVEQU__
#define __GESTALTPRIVEQU__

#ifndef __TYPES__
#include <Types.h>
#endif

// Gestalt function
typedef pascal OSErr (*GestaltProcPtr)(OSType selector,long *response);

#define gestaltVers		4					/* gestalt version (is this an oxymoron?) */


// each entry in the Gestalt table looks like this
struct GestaltEntry {
	OSType			selector;			
	unsigned long	value;					// ProcPtr or value
	short			flags;					// currently only bit is gestaltFlagIsValueMask
};
typedef struct GestaltEntry GestaltEntry;
typedef struct GestaltEntry *GestaltEntryPtr;

#define gestaltFlagIsValueMask	1			// bit in flags that means value is not ProcPtr

// Gestalt's global data structure
struct GestaltGlobals {
	Handle 			tableH;					/* handle to table of GestaltEntry */
	long 			slotsUsed;				/* number of entries in table */
	long 			maxSlots;				/* GetHandleSize(tableH)/sizeof(GestaltEntry) */
	unsigned long	memSize;				/* amount of memory in this machine */
	unsigned long	realTop;				/* adjusted memory size */
	short			machType;				/* machine type */
	char			fpu;					/* fpu type */
	char			mmu; 					/* mmu type */
	long			parityStatus;			/* parity status */
	long			myScratch;				/* scratch area */
	char			emu68k;					/* 68k emulator installed flag */
	char			nativeCPU;				/* native cpu type */
	long			nativePageSize;			/* native page size */
	long			ediskSize;				/* edisk size <SM10> CSS */
};
typedef struct GestaltGlobals GestaltGlobals;
typedef struct GestaltGlobals *GestaltGlobalsPtr;

#define kInitialEntryCount	80		// initial number of slots at boot time
#define kEntryGrowCount		16		// number of slots to add each time more is needed


// Private Gestalt selectors
#define gestaltLongHandle	'tabl'			/* returns handle to proc table */
#define gestaltATalkVersion	'atkv'			/* Returns 4-byte AppleTalk version even if AppleTalk is off. */
#define gestaltAtlkIntLevel	'aint'			/* Returns desired AppleTalk interrupt mask level in a long */
#define gestaltGraphicsVersion	'grfx'		/* Skia’s Gestalt selector */

//----------------------------------------------------------------------------------
//	gestaltBugFixAttrs
//
//	This selector, and others like it in the future, indicate the presence or absence
//	of certain bug fixes (one bit for each one).  The reason they exist is so we can
//	ship system extensions that fix important bugs, and then have future systems
//	or other extensions indicate that they have already fixed a bug (so the extension
//	will stop trying to fix it).  Yea, I know.  Pretty goofy. -gbm
//
//	I’ve taken the liberty of allocating several selectors here, for future expansion.
//----------------------------------------------------------------------------------
enum {
	gestaltBugFixAttrs = 'bugz',

	gestaltFixPrinting = 0,
	gestaltResponderCrashFix = 1,
	gestaltResponderVersionFix = 2,
	gestaltPurgeFonts = 3,
	gestaltAliasMgrFix = 4,
	gestaltSCSIFix = 5,
	gestaltKeyboardFix = 6,
	gestaltTrueTypeFix = 7,
	gestaltFixedMicroseconds = 8,
	gestaltSaveLastSPExtra = 9,
	gestaltVMCursorTaskFix = 10,
	gestaltDietPatches = 11,
	gestaltBackgroundPrintingPatch = 12,
	gestaltNoPreferredAlertPatch = 13,
	gestaltAllocPtrPatches = 14,
	gestaltEPPCConnectionTableFix = 15,
	gestaltDAHandlerPatch = 16,
	gestaltLaunchFix = 17,
	gestaltDeathNoticePatches = 18,
	gestaltBacklightFix = 19,
	gestaltPrintDriverFix = 20,
	gestaltPMSegmentTweaks = 21,
	gestaltWDEFZeroFix = 22,
	gestaltPACKSixFix = 23,
	gestaltResolveFileIDRefFix = 24,
	gestaltDisappearingFolderFix = 25,
	gestaltPowerBookSerialFix = 26,
	gestaltPowerBookSleepQFix = 27,
	gestaltPowerBookFloppyEjectFix = 28,
	gestaltPowerBookSleepFPUFix = 29,
	gestaltPowerBookRestFPUFix = 30,
	gestaltMtCheckFix				= 31,

	gestaltBugFixAttrsTwo = 'bugy',

	gestaltEgretSCCFix						= 0,
	gestaltEgretRdTimeFix					= 1,
	gestaltEgretIRQPatch					= 2,
	gestaltEgretTickHandlerFix				= 3,
	gestaltSCSIFastAckFix					= 4,
	gestaltAFEHomeResFileFix				= 5,
	gestaltPowerOffDelayFix					= 6,
	gestaltSndIntRestoreFix					= 7,
	gestaltPMgrMIDIFix 						= 8,
	gestaltMoveHHiExtraStackSpace			= 9,
	gestaltMMUOverwriteByQuadraRAMDiskFix	= 10,
	gestaltTerrorADBReInitFix				= 11,
	gestaltCentrisOnBoardGreenVGASyncFix	= 12,
	gestaltGetIndResourceSysMapHandleFix	= 13,
	gestaltCentrisBluishWhiteFix			= 14,
	gestaltCentrisFlashWhileScrollingFix	= 15,
	gestaltEightToSixteenMegBlockMoveFix	= 16,
	gestaltReleaseTheFontFlagFix			= 17,
	gestaltMSFlightSimDrawCrsrFix			= 18,
	gestaltRISCV0ResMgrPatches				= 19,
	gestaltSCSIBusyBugFix					= 20,
	gestaltHFSDeferredTaskStackSwitch		= 21,
	gestaltTETrashExpandMemRecVersionField	= 22,
	gestaltDartPMgrOpTimeoutBadBranchFix	= 23,	/* <28>	System Update 3.0 bug fixes */
	gestaltPwrBookLowPwrNotificationFix		= 24,	/* <28>	"							*/
	gestaltBlockMoveDataPatch				= 25,	/* <28>	"							*/
	gestaltFSpExchangeFilesCompatibilityFix	= 26,	/* <28>	"							*/
	gestaltSyncReadCacheFlushFix			= 27,	/* <29>	"							*/
	gestaltUpdateResFileFlushIfSystemFix	= 28,	/* <29>	"							*/
	gestaltMacPlusSizeResourceFix			= 29,	/* <29>	"							*/
	gestaltProcessMgrIdleTimeToRemovedDriverFix	= 30,	/* <29>	"							*/
	gestaltAboutThisMacSystemSizeBarFix		= 31,	/* <30> "							*/
	
	gestaltBugFixAttrsThree = 'bugx',
	
	gestaltPartialResourceRangeCheckFix		= 1		/* <33> SU 3.0 */
};


// private results for various selectors

enum {
// gestaltFontMgrAttr
	gestaltPartialFonts = 1,			/* Has partial TrueType */
	gestaltDiskCachedFonts = 2			/* Has disk based font cache */
};

enum {
// gestaltHardwareAttr
	gestaltHasRBV = 2,					/* RBV exists */
	gestaltHasOSS = 5,					/* OSS exists */
	gestaltHasSCSIDMA = 6,				/* SCSI DMA exists */
	gestaltHasSWIMIOP = 8,				/* SWIM IOP exists */
	gestaltHasSCCIOP = 9,				/* SCC IOP exists */
	gestaltHasFMC = 10,					/* Fitch memory controller exists */
	gestaltHasIWM = 11,					/* IWM/SWIM exists */
	gestaltHasPWM = 12,					/* PWM disk speed buffer exists */
	gestaltHasSoundBuffer = 13,			/* RAM-based sound buffer exists */
	gestaltHasVDAC = 14,				/* Video D/A converter and CLUT exists */
	gestaltHasPGC = 15,					/* Parity Generation Chip exists (Mac IIci) */
	gestaltHasRPU = 16,					/* Random Parity Unit exists (Zone 5) */
	gestaltHasOrwell = 17,				/* Orwell memory controller exists (Eclipse) */
	gestaltHasVISA = 18,				/* Has VISA RBV equivalent */
//	gestaltHasSoftPowerOff = 19,		/* Has software poweroff •• Public •• */
	gestaltHasSonic = 20,				/* Has Sonic Ethernet hardware */
//	gestaltHasSCSI961 = 21,				/* Has SCSI96_1 •• Public •• */
//	gestaltHasSCSI962 = 22,				/* Has SCSI96_2 •• Public •• */
	gestaltHasDAFB = 23,				/* Has DAFB Video hardware */
//	gestaltHasUniversalROM = 24,		/* Does we gots a Universal ROM? •• Public •• */
	gestaltHasJaws = 25,				/* Has Jaws Memory Controller */
	gestaltNeedsRESET = 26				/* need hard RESET to restart the machine */
};

enum {
// gestaltMachineType (Pre-released Machines)

	gestaltCarnation 		= 28,
	gestaltCarnation33 		= 28,
	gestaltColumbia 		= 31,
	gestaltQuadra650 		= 36,			
	gestaltPenlite	 		= 39,			
	gestaltVail16 			= 40,			
	gestaltCarnation25 		= 41,			
	gestaltCarnation16 		= 42,			
	gestaltCyclone33 		= 43,			
	gestaltBrazil16L 		= 44,			
	gestaltBrazil16F 		= 46,			
	gestaltBrazil32F 		= 47,			
	gestaltBrazilC 			= 48,
	gestaltWombat40         = 51,
	gestaltQuadra610		= 53,
	gestaltBrazil32cF		= 55,
	gestaltWombat20			= 58,
	gestaltWombat40F		= 59,
	gestaltRiscQuadra700	= 61,
	gestaltVail33			= 62,		/* Route 66 (LC III @ 33MHz) */
	gestaltWLCD33			= 63,	
	gestaltPDM66F			= 64,		/* Cold Fusion 66MHz */
	gestaltPDM80F			= 65,		/* Cold Fusion 80MHz */
	gestaltPDM100F			= 66,		/* Cold Fusion 100MHz */
	gestaltTNTProto1		= 67,		/* TNT Proto #1 */
	gestaltTesseractF		= 68,		/* Tesseract in Fridge 66MHz */
	gestaltTesseractC		= 69,		/* Tesseract in Unknown box 66MHz */
	gestaltJust930			= 70,		/* 930, whatever that was */
	gestaltHokusai			= 71,		/* Color portable 33MHz */
	gestaltBlackbird		= 72,		/* Color 040 portable ??MHz */
	gestaltBlackbirdLC		= 73,		/* Color 040 portable 16MHz */
	gestaltPDMEvt1			= 74,		/* PDM in QFC - ••• EVT1 Units ONLY ••• */
/*	gestaltPDM				= 74,*/
	gestaltPDMEvt2			= 75,
	gestaltYeagerFSTN		= 76,		/* LC040 Duo with FSTN <SM16> */
	gestaltTempest33		= 79,
	gestaltHook33			= 80,		/* LC 520 (Hook) 33MHz */
	gestaltSlice25			= 81,		/*  Color Classic (Slice) 25MHz */
	gestaltRiscCentris650	= 82,		/* Centris 650 w/Smurf card */
	gestaltSlice33			= 83,		/* Color Classic (Slice) 33MHz */
	gestaltNorad			= 84,		/* Powerbook 160 33MHz */
	gestaltBudMan			= 85,		/* DBLite w/SWIM II and TouchPad 25MHz */
	gestaltPrimus20			= 86,		/* Primus (LC/040) 20MHz */
	gestaltOptimus20		= 87,		/* Optimus (Hook/040) 20MHz */
	gestaltHookTV			= 88,		/* Hook+TV 32MHz */
	gestaltLC475			= 89,		/* Primus 25MHz */
	gestaltPrimus33			= 90,		/* Primus 33MHz */
	gestaltOptimus25		= 91,		/* Optimus 25MHz */
	gestaltLC575			= 92,		/* Optimus 33MHz */
	gestaltAladdin20		= 93,		/* Aladdin (LC/040 in ELB case) 20MHz */
	gestaltQuadra605		= 94,		/* Aladdin 25MHz */
	gestaltAladdin33		= 95,		/* Aladdin 33MHz */
	gestaltMalcolm25		= 96,		/* cost-reduced WLCD w/Primus chipset 25MHz */
	gestaltMalcolm33		= 97,		/* Malcolm 33MHz */
	gestaltSlimus25			= 98,		/* Color Classic/040 25MHz */
	gestaltSlimus33			= 99,		/* Slimus 33MHz */
	gestaltPDM66WLCD		= 100,		/* PDM in WLCD 66MHz */
	gestaltPDM80WLCD		= 101,		/* PDM in WLCD 80MHz */
	gestaltYeagerG			= 102,		/* Grayscale Portable Duo 040LC 25 MHz */
	gestaltYeagerC			= 103,		/* Color Portable Duo 040LC 25 MHz */
	gestaltRiscQuadra900	= 104,		/* Quadra900 w/Smurf card */
	gestaltRiscQuadra950	= 105,		/* Quadra950 w/Smurf card */ 
	gestaltRiscCentris610	= 106,		/* Centris610 w/Smurf card */
	gestaltRiscQuadra800	= 107,		/* Quadra800 w/Smurf card */
	gestaltRiscQuadra610	= 108,		/* Quadra610 w/Smurf card */
	gestaltRiscQuadra650	= 109,		/* Quadra650 w/Smurf card */
	gestaltRiscTempest		= 110,		/* Tempest w/Smurf card */
	gestaltPDM50L			= 111,		/* Carl Sagan (Cold Fusion in Lego) 50MHz */
	gestaltPDM66L			= 112,		/* Carl Sagan 66MHz */
	gestaltPDM80L			= 113,		/* Carl Sagan 80MHz */
	gestaltBlackbirdBFD		= 114,		/* Blackbird (66/33MHz 040LC, VIA1&2, Pratt, PGE, 256 color 10.X" TFT LCD, 1 direct slot) */
	gestaltJedi				= 115,		/* Jedi (33MHz, 030, low cost AIO powerbook, MSC, IDE, floppy ) */
	gestaltSTPQ700			= 116,		/* Q700 with STP card */
	gestaltSTPQ900			= 117,		/* Q900 with STP card */
	gestaltSTPQ950			= 118,		/* Q950 with STP card */	
	gestaltSTPC610			= 119,		/* C610 with STP card */
	gestaltSTPC650			= 120,		/* C650 with STP card */
	gestaltSTPQ610			= 121,		/* Q610 with STP card */
	gestaltSTPQ650			= 122,		/* Q650 with STP card */	
	gestaltSTPQ800			= 123,		/* Q800 with STP card */
	gestaltAJ				= 124,		/* AJ (66 MHz 603, duo powerbook) */
	gestaltAJ80				= 125,		/* AJ (80 MHz 603, duo powerbook) */ 
	gestaltMalcolmBB		= 126,		/* Malcolm (yep, same name as WLCD II)(66 MHz 603 upgrade to Blackbird) */
	gestaltMalcolmBB80		= 127,		/* Malcolm (yep, same name as WLCD II)(80 MHz 603 upgrade to Blackbird) */
	gestaltM2				= 128,		/* M2 (66 MHz 603, duo powerbook) */
	gestaltM280				= 129		/* M2 (80 MHz 603, duo powerbook) */
};

enum {
// gestaltMiscAttr
	gestaltBootGlobals = 1     			/* this machine has boot globals */
};

enum {
// gestaltOSAttr
	gestaltSkiaGlobalsSwitched = 9,		/* Process Manager switches Skia globals on context switches */
	gestaltExtendedDebuggerSupport = 11, /* Process Manager has fixes and new calls for debuggers <12> */
	gestaltMultiLayerSupport = 12
};

enum {
// gestaltResourceMgrAttr
	gestaltResourceOverrides = 1		/* can do resource override stuff */
};

enum {
#define gestaltSerialHALType 'shal'		/* serial HAL resource ID for this machine */
	gestaltSHALPSC = 1,					/* PSC HAL (Cyclone, Tempest) */
	gestaltSHALAMIC = 2					/* AMIC HAL (PDM) */
};

enum {
// gestaltSoundAttr
	gestaltQuickTimeUsesNewSoundMgrCalls = 2	/* QuickTime can use new SoundParamBlock */
												/* was named gestaltHeadphonePluggedIn but */
												/* that's impossible to detect */
};

// this returns the component OSType necessary to use the built-in sound hardware
enum {
#define gestaltSoundHardware 'snhw'		/* Get the built-in Sound Hardware */
	gestaltClassicSnd = 'clas',			/* Classic sound (i.e. Mac Plus) */
	gestaltASCSnd = 'asc ',				/* Apple Sound Chip sound hardware */
	gestaltDSPSnd = 'dsp ',				/* Digital Signal Processing sound hardware */
	gestaltAwacsSnd = 'awac',			/* Awacs audio codec */
	gestaltSingerSnd = 'sing'			/* Singer/Whitney sound subsystem */
};


#endif
