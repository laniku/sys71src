/************************************************************

Created: Sunday, January 6, 1991 at 9:27 PM
    GestaltEqu.h
    C Interface to the Macintosh Libraries


        Copyright Apple Computer, Inc.    1988-1992
        All rights reserved

	Change History (most recent first):

	  <SM25>	 11/8/93	JRH		Added gestaltPowerBookDuo250 and gestaltPowerBookDuo270C.
	  <SM24>	10/28/93	SAM		Those double sided C comments...
	  <SM23>	10/28/93	SAM		Roll in <MC4> from mc900ftjesus.
	   <MC4>	10/28/93	SAM		Changed gestaltNativeCPUtype equates (making each cpu type take
									a range of 256 per architecture).
	  <SM22>	10/14/93	pdw		Added 'scsi' selector and bits.
	  <SM21>	09-24-93	jmp		Rolled in various equates from the Excelsior sources.
	  <SM20>	 8/16/93	BG		Update machinetype values to something closer to current.
	  <SM19>	  8/4/93	JDR		synch with Sound Mgr project.
		<18>	  8/4/93	IH		#1101633,1098397,1101795,1101636,1102280 <KON>: Fix 1102280. Add
									CloseView and Display Manager gestalt selectors.
	  <SM17>	 7/21/93	RC		back out <sm 15>
		<15>	  7/2/93	IH		Partial update from Reality: update Gestalt prototypes to
									include SelectorFunctionProcPtr. Moved most new equates into SM.
									Did not update format changes (spacing of defines etc). Did not
									update error numbers (which probably belong in errors.h)
	  <SM14>	 6/14/93	kc		Roll in Ludwig.
	   <LW2>	 4/29/93	fau		Bug #1081636:  Update from Reality:  changed some of the
									gestaltSoundattr bit assignments and added some others to allow
									more useful encoding of sound hardware information.
	  <SM13>	 2/11/93	SAM		Added Emulated MMU type.
	  <SM12>	12/13/92	SAM		Added gestaltNativeCPUtype and gestaltSysArchitecture.
									Straightened out this file a bit.
	   <SM11>	 11/10/92	CSS		Update from Reality:
	   								<60> 10/28/92 JDR	Added inline versions of ReplaceGestalt and NewGestalt for the
														SystemSevenOrLater includes.
	   <SM10>	 8/28/92	CSS		Update from Reality:
	   								<59> 8/28/92 DCL	Fixed enums with commas before the closing brace. MPW now
														complains.
	   <SM9>	 7/29/92	CSS		Update from Reality:
	   								<58> 7/28/92 JDR	<DCL> Added Sound Mgr 3.0 flags.
	   <SM8>	 7/28/92	WS		add realtime manager attribute for gestalt call
	   <SM7>	 7/20/92	CSS		Removed stuff that is now definced in GestaltEquPriv.a.
	   <SM6>	 7/15/92	RB		Added the gestalt result for Classic hardware.
	   <SM5>	 7/14/92	RB		Added the selector and types associated with sound hardware.
	   <SM4> 	 6/11/92	CSS		Roll-in changes from Reality:
	   								<57> 6/5/92	DC		Add the selector for checking for the presence of icon
														utilities.
									<56> 6/2/92	JSM		#1031451 <csd>: Add gestaltPowerBook145.
									<55> 5/27/92 KIP	#1030293,<JDR>: Add gestaltPlayAndRecord bit for sound
														attributes.
									<54> 5/27/92 DCL	Moved gestaltQuadra950 into the public consciousness.
									<53> 4/9/92	JSM		#1026795,<DTY>: Add gestaltMacLCII.
	   <SM3>	 5/20/92	KW		Added defs from Pandora P3.  Somewhat nervous about different
									format.
	   <SM2>	 5/17/92	kc		Added gestaltQuadra950.
		<52>	  1/7/92	KST		Added gestaltTSMgrVersion.
		<51>	 12/3/91	SAM		Updated 'hdwr' selector to include hasSCSIc961(2).
		<50>	 12/3/91	JL		SAM: Added support for Fall '91 CPUs and keyboards. Also added
									gestaltHasUniversalROM as per assembly file.
		<49>	11/21/91	YK		Deleted the selector for input utilities.
		<48>	 11/1/91	KSM		Added gestaltHelpMgrExtensions.
		<47>	10/30/91	YK		Corrected previous change.
		<46>	10/30/91	YK		Added selectors for Dictionary Mgr, Input Utilities and
									Component Mgr.
		<45>	 8/22/91	gbm		(really csd) Added gestaltAliasMgrSupportsRemoteAppletalk
		<44>	 7/24/91	JL		Updated copyright. Adjusted file to match database.
		<43>	 6/26/91	BH		gestaltFXfrMgrMultiFile
		<42>	 6/26/91	BH		added selectors for CTB11 stuff (errorstring for CM, TM, FT,
									CRMToolRsrcCalls)
		<41>	 6/26/91	BH		added gestaltCRMPersistentFix constant
		<40>	 6/14/91	JL		Checked in official MPW 3.2Ä version. Also updated copyright
									date; will restore later. Changed kMachineNameStrID from a
									#define to an enum. Temporarily lost comment. Adjust enum
									grouping to match DSG Database.
		<39>	  2/7/91	KON		CEL: BRC# Gang of 5: Remove equate for gestaltOriginalQD1.
		<38>	  2/5/91	stb		gs: add kMachineNameStrID
		<37>	  2/4/91	gbm		JDR, #gbm-0003: Add the gestaltQuickdrawFeatures selector
		<36>	 1/30/91	JL		Checked in database generated file from dsg.
		<35>	 1/15/91	gbm		(bbm) Add new hardware attribute, gestaltHasSoftPowerOff
		<34>	12/14/90	JDR		(KIP) adding Gestalt selector gestaltHasSoundInputDevice and
									renaming gestaltSoundInputPresent.
		<33>	12/14/90	dba		<JDR> change SystemSevenOrBetter to SystemSevenOrLater
		<32>	 12/5/90	gbm		<dba> Add two file system selectors: one for FSSpec calls
									existing, and another for file system manager existing
		<31>	 12/3/90	EMT		<GSM> Fix comments
		<30>	11/16/90	KON		My shell trashed this file.
		<28>	11/15/90	SMB		Added another TextEdit version, gestaltTE5, for the new
									TextWidthHook.
		<27>	 11/8/90	EMT		<stb>Fix comments and spelling errors for PPCToolBox. Remove
									equates that are not applicable for 7.0
		<26>	10/21/90	gbm
		<26>	 10/9/90	JAL		Changed #pragma parameter to new MPW 3.2 C way.
		<25>	 10/8/90	JDR		Use #pragma parameter for the Gestalt call on
									SystemSevenOrBetter.
	   								This avoids lots of unnecessary glue for System 7 builds.
		<24>	 9/14/90	SAM		Added final machine names for IIsi, LC, and Classic.
		<23>	 9/10/90	gbm		add file system attributes selector, gestaltFSAttr... (actually,
									I did it in change <22>, but somehow the checkin comment got a
									little munged...)
		<22>	 9/10/90	gbm		.
		<21>	 8/30/90	PP		gestaltFolderMgrAttr is gestaltFindFolderAttr.
									gestaltFolderMgrPresent is gestaltFindFolderPresent.
		<20>	 8/14/90	JWK		Cleaned up comments.
		<19>	 8/14/90	JWK		NEEDED FOR SIXPACK: Added NuBus and Serial selectors.
		<18>	 8/13/90	gbm		add selectors for trap table bases
		<17>	  8/6/90	kaz		Removed CommToolbox refs to xxErrorString and cmMultiAsyncIO;
									renumbered cmSearchFix.
		<16>	 7/26/90	RLC		Add gestaltEasyAccessAttr & result codes #defines.
		<15>	 6/25/90	kaz		Removed 'ctbm', 'ctbu'. Added 'ditl'.
		<14>	 6/23/90	kaz		Fixed typo for 'term', and 'fxfr'.
		<13>	 6/18/90	NC		Add selectors for sound I/O manager
		<12>	 6/11/90	CCH		Moved standard file selector in from GestaltEqu.a.
		<11>	 6/10/90	kaz		Ported CommToolbox stuff from .a file
		<10>	  5/1/90	CCH		Added gestaltSquareMenuBar response bit to gestaltMiscAttr.
		 <9>	 4/11/90	dba		add machineicon selector
		 <8>	  4/9/90	S		Included PPC Gestalt Selections.
		 <7>	 3/28/90	CCH		Added Mac IIfx equate and comm toolbox selector.
		 <5>	  3/6/90	CCH		Updated to latest equates from GestaltEqu.a
		 <4>	  1/9/90	ngk		Changed gestaltEditionMgr to gestaltEditionMgrAttr
		 <3>	  1/7/90	ngk		Moved include of types.h to before function declarations
		 <2>	  1/5/90	CCH		NEEDED FOR 6.0.5:  Added conditional to allow inclusion into Rez
									files. Added RPU and Orwell bits to hardware selector, added
									slot selectors back in temporarily, and added equate for 68040
									FPU.
		 <1>	  1/3/90	CCH		Changed name to GestaltEqu.h.
	   <3.2>	12/15/89	CCH		Updated Gestalt Equates, added some new 7.0 selectors.
	   <3.1>	 8/24/89	CCH		Changed gestaltOSAttr to be 'os  '.
	   <3.0>	  8/9/89	CCH		NEEDED FOR 6.0.4: Changed return values for
	   								gestaltQuickdrawType to be version based, and changed
									the selector name to gestaltQuickdrawVersion.
	   <2.9>	  8/8/89	SMB		NEEDED FOR 6.0.4: Added definitions for gestaltTextEditVersion.
	   <2.8>	  8/5/89	PKE		NEEDED FOR 6.0.4:
	   									- Added gestaltScriptMgrVersion, gestaltScriptCount
										  selectors (for Script Manager)
										- Added gestaltTextEditVersion selector (for TextEdit)
	   <2.7>	 7/16/89	CCH		NEEDED FOR AURORA AND 6.0.4:
	   									- Added gestaltFirstSlotNumber selector.
	   									- Added additional information to gestaltHardwareAttr
										  selector.
	   									- Added gestaltAMU to gestaltMMUType selector.
	   									- Added gestaltParityAttr selector.
	   <2.6>	 7/10/89	CCH		NEEDED FOR AURORA:
	   									- Removed gestaltFirstSlotNumber selector.
	   <2.5>	 6/30/89	CCH		Added gestaltLowMemorySize selector.
	   <2.4>	 6/26/89	CCH		Added gestaltFirstSlotNumber selector.
	   <2.3>	  6/9/89	CCH		Changes:
	   									- Changed a/ux selector to be version-based.
	   									- Added gestaltAddressingModeAttr, gestaltAUXVersion,
										  gestaltSlotAttr, gestaltSoundAttr, gestaltTimeMgrVersion,
										  GestaltRBVAddr, gestaltHardwareAttr, gestaltNuBusSlotCount
										  selectors.
	   									- Made result equates for attribute selectors bit numbers
										  instead of masks.
	   <2.2>	 5/25/89	CCH		Revised Gestalt equates to be more consistent.
	   <2.1>	 5/23/89	CCH		Added several new gestalt function codes.
	   <2.0>	 5/18/89	CCH		Changed equate naming convention to "gestalt" prefix.
	   									- Started using character constants for values.
	   									- Removed all return values for "unknown", except for one.
	   <1.9>	 4/20/89	CCH		Added new equate for virtual RAM size.
	   <1.8>	 4/16/89	CCH		Changed equate prefix from "G" to "z".
	   <1.7>	  4/3/89	CCH		Added equates for portable and ISO keyboards. Changed names of
									some equates.
	   <1.6>	 3/30/89	CCH		Took out GROMSize.
	   <1.5>	 3/16/89	CCH		Changed G24BitQD to z8BitQD.
	   <1.4>	 3/16/89	CCH		Moved definitions of special codes to GestaltPriv.h.
	   <1.3>	  3/6/89	CCH		Changed MAXINT to 0x7FFFFFFF.
	   <1.2>	  3/2/89	CCH		Changed MMU equates per design review decisions.
	   <1.1>	 2/23/89	CCH		Added new Gestalt equates.
	   <1.0>	 2/21/89	CCH		Adding to EASE for the first time.

************************************************************/


#ifndef __GESTALTEQU__
#define __GESTALTEQU__

#ifndef __TYPES__
#include <Types.h>
#endif


enum {


/************************
 *    Gestalt error codes
 ************************/
    gestaltUnknownErr		= -5550,		/* value returned if Gestalt doesn't know the answer */
    gestaltUndefSelectorErr = -5551,		/* undefined selector was passed to Gestalt */
    gestaltDupSelectorErr	= -5552,		/* tried to add an entry that already existed */
    gestaltLocationErr		= -5553,		/* gestalt function ptr wasn't in sysheap */

/**************************
 *    Environment Selectors
 **************************/

#define gestaltVersion 'vers'               /* gestalt version */
#define gestaltAddressingModeAttr 'addr'    /* addressing mode attributes */

    gestalt32BitAddressing = 0,             /* using 32-bit addressing mode */
    gestalt32BitSysZone = 1,                /* 32-bit compatible system zone */
    gestalt32BitCapable = 2,                /* Machine is 32-bit capable */

#define gestaltAliasMgrAttr 'alis'          /* Alias Mgr Attributes */

    gestaltAliasMgrPresent = 0,             /* True if the Alias Mgr is present */
	gestaltAliasMgrSupportsRemoteAppletalk = 1,	/* True if the Alias Mgr knows about Remote Appletalk */

#define gestaltAppleTalkVersion	'atlk'		/* appletalk version */
#define gestaltAUXVersion		'a/ux'		/*a/ux version, if present */
#define gestaltCloseViewAttr	'BSDa'		/* CloseView attributes */

	gestaltCloseViewEnabled	 = 0,			/* Closeview enabled (dynamic bit - returns current state) */
	gestaltCloseViewDisplayMgrFriendly = 1,	/* Closeview compatible with Display Manager (FUTURE) */

#define gestaltConnMgrAttr		'conn'		/* connection mgr attributes    */

    gestaltConnMgrPresent = 0,
    gestaltConnMgrCMSearchFix = 1,          /* Fix to CMAddSearch?     */
	gestaltConnMgrErrorString = 2,			/* has CMGetErrorString() */
	gestaltConnMgrMultiAsyncIO = 3,			/* CMNewIOPB, CMDisposeIOPB, CMPBRead, CMPBWrite, CMPBIOKill */
	
#define gestaltComponentMgr 	'cpnt'		/* Component Mgr version */

#define gestaltTSMgrVersion 	'tsmv'		/* Text Services Mgr version, if present */

#define gestaltNativeCPUtype	'cput'		/* Native CPU type 								   <SM12><MC4>  */
	// 68000 Architecture //
	gestaltCPU68000		= 0x000,			/* Various 68k CPUs...											*/
	gestaltCPU68010		= 0x001,
	gestaltCPU68020		= 0x002,
	gestaltCPU68030		= 0x003,
	gestaltCPU68040		= 0x004,
	// PowerPC Architecture //
	gestaltCPU601		= 0x101,			/* IBM 601 														*/
	gestaltCPU603		= 0x103,
	gestaltCPU604		= 0x104,

#define gestaltCRMAttr			'crm '		/* comm resource mgr attributes */

    gestaltCRMPresent = 0,
	gestaltCRMPersistentFix = 1, 			/* fix for persistent tools */
	gestaltCRMToolRsrcCalls = 2, 			/* has CRMGetToolResource/ReleaseToolResource */
	
#define gestaltCTBVersion		'ctbv'		/* CommToolbox version */
#define gestaltDBAccessMgrAttr	'dbac'		/* Database Access Mgr attributes */

    gestaltDBAccessMgrPresent = 0,          /* True if Database Access Mgr present */

#define gestaltDITLExtAttr		'ditl'		/* AppenDITL, etc. calls from CTB */

    gestaltDITLExtPresent = 0,              /* True if calls are present */

#define gestaltDisplayMgrAttr	'dply'		/* Display Manager attributes */
	
	gestaltDisplayMgrPresent = 0,			/* True if Display Mgr is present */

#define gestaltDisplayMgrVers	'dplv'		/* Display Manager version */
#define gestaltEasyAccessAttr	'easy'		/* Easy Access attributes */

    gestaltEasyAccessOff = 0,               /* if Easy Access present, but off (no icon) */
    gestaltEasyAccessOn = 1                 /* if Easy Access "On" */
};
enum {
	gestaltEasyAccessSticky = 2, 			/* if Easy Access "Sticky" */
    gestaltEasyAccessLocked = 3,            /* if Easy Access "Locked" */

#define gestaltEditionMgrAttr	'edtn'		/* Edition Mgr attributes */

    gestaltEditionMgrPresent = 0,           /* True if Edition Mgr present */
	gestaltEditionMgrTranslationAware = 1,	/* True if edition manager is translation manager aware */

#define gestaltAppleEventsAttr	'evnt'		/* Apple Events attributes */

    gestaltAppleEventsPresent = 0,          /* True if Apple Events present */

#define gestaltFinderAttr		'fndr'		/* Finder attributes */

	gestaltFinderDropEvent = 0,				/* Finder recognizes drop event */
	gestaltFinderMagicPlacement = 1,		/* Finder supports magic icon placement */
	gestaltFinderCallsAEProcess = 2,		/* Finder calls AEProcessAppleEvent */
	gestaltOSLCompliantFinder = 3,			/* Finder is scriptable and recordable */
	gestaltFinderSupports4GBVolumes = 4,	/* Finder correctly handles 4GB volumes */
	gestaltFinderHandlesCFMFailures = 5,	/* Finder handles Code Fragment Manager errors  */

#define gestaltFindFolderAttr	'fold'		/* Folder Mgr attributes */

	gestaltFindFolderPresent = 0, 			/* True if Folder Mgr present */

#define gestaltFontMgrAttr		'font'		/* Font Mgr attributes */

    gestaltOutlineFonts = 0,                /* True if Outline Fonts supported */

#define gestaltFPUType			'fpu '		/* fpu type */

    gestaltNoFPU = 0,                       /* no FPU */
    gestalt68881 = 1,                       /* 68881 FPU */
    gestalt68882 = 2,                       /* 68882 FPU */
    gestalt68040FPU = 3,                    /* 68040 built-in FPU */

#define gestaltFSAttr			'fs  '      /* file system attributes */

    gestaltFullExtFSDispatching = 0,        /* has really cool new HFSDispatch dispatcher */
    gestaltHasFSSpecCalls = 1,              /* has FSSpec calls    */
    gestaltHasFileSystemManager = 2,        /* has a file system manager */

#define gestaltFXfrMgrAttr		'fxfr'		/* file transfer manager attributes */

    gestaltFXfrMgrPresent = 0,
	gestaltFXfrMgrMultiFile = 1,			/* supports FTSend and FTReceive */
	gestaltFXfrMgrErrorString = 2, 			/* supports FTGetErrorString */
	
#define gestaltHardwareAttr		'hdwr'		/* hardware attributes */

    gestaltHasVIA1 = 0,						/* VIA1 exists */
    gestaltHasVIA2 = 1,						/* VIA2 exists */
    gestaltHasASC = 3,						/* Apple Sound Chip exists */
    gestaltHasSCC = 4						/* SCC exists */
};
enum {
	gestaltHasSCSI			=	7,			/* SCSI exists */
    gestaltHasSoftPowerOff	=	19,			/* Capable of software power off */
	gestaltHasSCSI961		=	21,			/* 53C96 SCSI controller on internal bus */
	gestaltHasSCSI962		=	22,			/* 53C96 SCSI controller on external bus */
 	gestaltHasUniversalROM	=	24,			/* Do we have a Universal ROM? */

#define gestaltHelpMgrAttr		'help'		/* Help Mgr Attributes */

    gestaltHelpMgrPresent = 0,				/* true if help mgr is present */
    gestaltHelpMgrExtensions = 1,			/* true if help mgr extensions are installed */

#define gestaltKeyboardType		'kbd '		/* keyboard type */

    gestaltMacKbd = 1,
    gestaltMacAndPad = 2,
    gestaltMacPlusKbd = 3,
	gestaltExtADBKbd = 4,
    gestaltStdADBKbd = 5,
    gestaltPrtblADBKbd = 6,
    gestaltPrtblISOKbd = 7,
    gestaltStdISOADBKbd = 8,
    gestaltExtISOADBKbd = 9,
    gestaltADBKbdII = 10,
    gestaltADBISOKbdII = 11,
 	gestaltPwrBookADBKbd = 12,
 	gestaltPwrBookISOADBKbd = 13,
	gestaltAppleAdjustKeypad = 14,			/*<70>*/
	gestaltAppleAdjustADBKbd = 15,			/*<70>*/
	gestaltAppleAdjustISOKbd = 16,			/*<70>*/


#define gestaltLowMemorySize	'lmem'		/* size of low memory area */
#define gestaltLogicalRAMSize	'lram'		/* logical ram size */
#define gestaltMiscAttr 		'misc'		/* miscellaneous attributes */

    gestaltScrollingThrottle = 0,			/* true if scrolling throttle on */
    gestaltSquareMenuBar = 2				/* true if menu bar is square */
};
enum {

#define gestaltMMUType			'mmu '		/* mmu type */

    gestaltNoMMU 	= 0,					/* no MMU */
    gestaltAMU 		= 1,					/* address management unit */
    gestalt68851 	= 2,					/* 68851 PMMU */
    gestalt68030MMU = 3,					/* 68030 built-in MMU */
	gestalt68040MMU = 4,					/* 68040 built-in MMU */
	gestaltEMMU1 	= 5,					/* Emulated MMU type 1  <SM13> */

#define gestaltStdNBPAttr		'nlup'		/* standard nbp attributes */

    gestaltStdNBPPresent = 0,

#define gestaltNotificationMgrAttr 'nmgr'	/* notification manager attributes */

    gestaltNotificationPresent = 0,			/* notification manager exists */

#define gestaltNuBusConnectors	'sltc'		/* bitmap of NuBus connectors*/

#define gestaltNuBusSlotCount	'nubs'		/* count of logical NuBus slots present <SM3> */

#define gestaltOSAttr			'os  '		/* o/s attributes */

    gestaltSysZoneGrowable = 0,             /* system heap is growable */
    gestaltLaunchCanReturn = 1,             /* can return from launch */
    gestaltLaunchFullFileSpec = 2,          /* can launch from full file spec */
	gestaltLaunchControl = 3, 				/* launch control support available */
    gestaltTempMemSupport = 4,              /* temp memory support */
    gestaltRealTempMemory = 5,              /* temp memory handles are real */
    gestaltTempMemTracked = 6,              /* temporary memory handles are tracked */
    gestaltIPCSupport = 7,                  /* IPC support is present */
    gestaltSysDebuggerSupport = 8,          /* system debugger support is present */
	/* gestaltSkiaGlobalsSwitched is #9. I don't know why it is not here */
	gestaltBgndMouseDownSupport = 10,		/* Background mouse down support is present */

#define gestaltOSTable			'ostt'		/*  OS trap table base  */
#define gestaltToolboxTable		'tbtt'		/*  OS trap table base  */
#define gestaltExtToolboxTable	'xttt'		/* Extended Toolbox trap table base */

#define gestaltPCXAttr			'pcxg'		/* PC Exchange attributes */
	gestaltPCXHas8and16BitFAT = 0,			/* PC Exchange supports both 8 and 16 bit FATs */
	gestaltPCXHasProDOS = 1,				/* PC Exchange supports ProDOS */

#define gestaltLogicalPageSize	'pgsz'		/* logical page size */
#define gestaltPowerMgrAttr		'powr'      /* power manager attributes */

    gestaltPMgrExists = 0,
    gestaltPMgrCPUIdle = 1,
    gestaltPMgrSCC = 2,
    gestaltPMgrSound = 3
};
enum {

#define gestaltPPCToolboxAttr	'ppc '		/* PPC toolbox attributes */

/*
 * PPC will return the combination of following bit fields.
 * e.g. gestaltPPCSupportsRealTime +gestaltPPCSupportsIncoming + gestaltPPCSupportsOutGoing
 * indicates PPC is cuurently is only supports real time delivery
 * and both incoming and outgoing network sessions are allowed.
 * By default local real time delivery is supported as long as PPCInit has been called.*/


    gestaltPPCToolboxPresent   = 0x0000,	/* PPC Toolbox is present  Requires PPCInit to be called */
    gestaltPPCSupportsRealTime = 0x1000,	/* PPC Supports real-time delivery */
    gestaltPPCSupportsIncoming = 0x0001,	/* PPC will deny incoming network requests */
    gestaltPPCSupportsOutGoing = 0x0002,	/* PPC will deny outgoing network requests */

#define gestaltProcessorType	'proc'		/* processor type */

	gestalt68000 = 1,
    gestalt68010 = 2,
    gestalt68020 = 3,
    gestalt68030 = 4,
    gestalt68040 = 5,

#define gestaltParityAttr		'prty'		/* parity attributes */

    gestaltHasParityCapability = 0,			/* has ability to check parity */
	gestaltParityEnabled = 1,				/* parity checking enabled */

#define gestaltQuickdrawVersion	'qd  '		/* quickdraw version */

    gestaltOriginalQD = 0x000,              /* original 1-bit QD */
    gestalt8BitQD = 0x100,                  /* 8-bit color QD */
    gestalt32BitQD = 0x200,                 /* 32-bit color QD */
    gestalt32BitQD11 = 0x210,               /* 32-bit color QDv1.1 */
    gestalt32BitQD12 = 0x220,               /* 32-bit color QDv1.2 */
    gestalt32BitQD13 = 0x230,               /* 32-bit color QDv1.3 */

#define	gestaltQuickdrawFeatures 'qdrw'		/* quickdraw features */

	gestaltHasColor = 0,					/* color quickdraw present */
	gestaltHasDeepGWorlds = 1,				/* GWorlds can be deeper than 1-bit */
	gestaltHasDirectPixMaps = 2 			/* PixMaps can be direct (16 or 32 bit) */
};
enum {
	gestaltHasGrayishTextOr	= 3,			/* supports text mode grayishTextOr */
	gestaltSupportsMirroring = 4,			/* Supports video mirroring via the Display Manager. */

#define gestaltPhysicalRAMSize	'ram '		/* physical RAM size */
#define	gestaltRBVAddr			'rbv '		/* RBV base address <SM3> */
#define	gestaltSCCReadAddr		'sccr'		/* scc read base address <SM3> */
#define	gestaltSCCWriteAddr		'sccw'		/* scc read base address <SM3> */

#define gestaltPopupAttr		'pop!' 		/* popup cdef attributes */

    gestaltPopupPresent = 0,

#define gestaltResourceMgrAttr	'rsrc'		/* Resource Mgr attributes */

    gestaltPartialRsrcs = 0,				/* True if partial resources exist */

#define gestaltScrapMgrAttr		'scra'		/* Scrap Manager attributes */
	gestaltScrapMgrTranslationAware = 0,	/* True if scrap manager is translation aware */
	gestaltTranslationMgrHintOrder = 1,		/* True if hint order reversal in effect */

#define gestaltScriptMgrVersion	'scri'		/* Script Manager version number    <08/05/89 pke> */
#define gestaltScriptCount		'scr#'		/* number of active script systems    <08/05/89 pke> */
#define gestaltSerialAttr		'ser '		/* Serial attributes */

    gestaltHasGPIaToDCDa = 0,               /* GPIa connected to DCDa*/
	gestaltHasGPIaToRTxCa = 1, 				/* GPIa connected to RTxCa clock input*/
    gestaltHasGPIbToDCDb = 2,               /* GPIb connected to DCDb */


#define	gestaltSlotAttr			'slot'		/* slot attributes <SM3> */
#define	gestaltSlotMgrExists		0		/* true is slot mgr exists <SM3> */
#define	gestaltNuBusPresent			1		/* NuBus slots are present <SM3> */
#define	gestaltSESlotPresent		2		/* SE PDS slot present <SM3> */
#define	gestaltSE30SlotPresent		3		/* SE/30 slot present <SM3> */
#define	gestaltPortableSlotPresent	4		/* Portable's slot present <SM3> */

#define	gestaltFirstSlotNumber	'slt1'		/* returns first physical slot */

#define gestaltSoundAttr		'snd '		/* sound attributes */

    gestaltStereoCapability = 0,            /* sound hardware has stereo capability */
    gestaltStereoMixing = 1,                /* stereo mixing on external speaker */
	gestaltSoundIOMgrPresent = 3,           /* The Sound I/O Manager is present */
	gestaltBuiltInSoundInput = 4, 			/* built-in Sound Input hardware is present */
    gestaltHasSoundInputDevice = 5,         /* Sound Input device available */
	gestaltPlayAndRecord = 6,				/* built-in hardware can play and record simultaneously */
    gestalt16BitSoundIO = 7,				/* sound hardware can play and record 16-bit samples */
    gestaltStereoInput = 8,					/* sound hardware can record stereo */
    gestaltLineLevelInput = 9,				/* sound input port requires line level */
											/* the following bits are not defined prior to Sound Mgr 3.0 */
	gestaltSndPlayDoubleBuffer = 10,		/* SndPlayDoubleBuffer available, set by Sound Mgr 3.0 and later */
	gestaltMultiChannels = 11,				/* multiple channel support, set by Sound Mgr 3.0 and later */
	gestalt16BitAudioSupport = 12,			/* 16 bit audio data supported, set by Sound Mgr 3.0 and later */

#define gestaltSpeechAttr 'ttsc'			/* Speech Manager attributes */
	gestaltSpeechMgrPresent = 0,			/* bit set indicates that Speech Manager exists */

#define gestaltStandardFileAttr	'stdf'		/* Standard File attributes */

    gestaltStandardFile58 = 0,              /* True if selectors 5-8 (StandardPutFile-CustomGetFile) are supported */
	gestaltStandardFileTranslationAware	=1,	/* True if standard file is translation manager aware */
	gestaltStandardFileHasColorIcons = 2,	/* True if standard file has 16x16 color icons */

#define gestaltSysArchitecture	'sysa'		/* Native System Architecture								<SM12>	*/
	gestalt68k		= 1,					/* Motorola MC68k architecture										*/
	gestaltPowerPC	= 2,					/* IBM PowerPC architecture											*/

#define gestaltTextEditVersion 'te  '       /* TextEdit version number            <08/05/89 pke> */

    gestaltTE1 = 1,                         /* TextEdit in MacIIci ROM <8Aug89smb> */
    gestaltTE2 = 2,                          /* TextEdit with 6.0.4 Script Systems on MacIIci (Script bug fixes for MacIIci) <8Aug89smb> */
    gestaltTE3 = 3,                         /* TextEdit with 6.0.4 Script Systems all but MacIIci <8Aug89smb> */
    gestaltTE4 = 4,                         /* TextEdit in System 7.0 */
    gestaltTE5 = 5,                         /* TextWidthHook available in TextEdit */

#define gestaltTermMgrAttr		'term'		/* terminal mgr attributes */

    gestaltTermMgrPresent = 0,
	gestaltTermMgrErrorString = 2,
	
#define gestaltTimeMgrVersion	'tmgr'		/* time mgr version */

    gestaltStandardTimeMgr = 1              /* standard time mgr is present */
};
enum {
    gestaltRevisedTimeMgr = 2,              /* revised time mgr is present */
    gestaltExtendedTimeMgr = 3,             /* extended time mgr is present */

#define	gestaltVIA1Addr			'via1'		/* via 1 base address <SM3> */
#define	gestaltVIA2Addr			'via2'		/* via 2 base address <SM3> */

#define gestaltVMAttr			'vm  '		/* virtual memory attributes */

    gestaltVMPresent = 0,                   /* true if virtual memory is present */
	gestaltVMNotInstalled = 0,				/* <SM3> */

#define gestaltTranslationAttr 'xlat'		/* Translation Manager attributes */
	gestaltTranslationMgrExists = 0,		/* True if translation manager exists */

#define gestaltDictionaryMgrAttr 'dict'		/* Dictionary Manager attributes */

	gestaltDictionaryMgrPresent = 0,		/* Dictionary Manager attributes */

#define gestaltIconUtilities	'icon'		/* Icon Utilities attributes	<SM4> CSS */

	gestaltIconUtilitiesPresent = 0,		/* true if icon utilities are present <SM4> CSS*/

#define gestaltRealtimeMgrAttr	'rtmr'		/* Realtime manager attributes		<SM8> WS	*/

	gestaltRealtimeMgrPresent = 0,			/* true if the Realtime maanger is present <SM8> WS 	*/


#define	gestaltSoundHardware	'snhw'		/* Get the Sound Hardware				<SM5> rb */
#define	gestaltASC				'asc '		/* component type of Apple Sound Chip	<SM5> rb */
#define	gestaltDSP				'dsp '		/* component type of Digital Signal Processing <SM5> rb */
#define	gestaltClassicSound		'clas'		/* Macintosh Classic sound				<SM6> rb */

#define gestaltSCSI				'scsi'		/* SCSI Manager attributes */

	gestaltAsyncSCSI			=	0,		/* Supports Asynchronous SCSI */
	gestaltAsyncSCSIINROM		=	1,		/* Async scsi is in ROM (available for booting) */
	gestaltSCSISlotBoot			=	2		/* ROM supports Slot-style PRAM for SCSI boots (PDM and later) */

};

/*************************
 *    Info-only selectors
 ************************/

enum {
#define gestaltMachineType		'mach'		/* machine type */

    kMachineNameStrID = -16395,
	gestaltClassic = 1,
    gestaltMacXL = 2,
    gestaltMac512KE = 3,
    gestaltMacPlus = 4,
    gestaltMacSE = 5,
    gestaltMacII = 6,
    gestaltMacIIx = 7,
	gestaltMacIIcx = 8,
    gestaltMacSE030 = 9,
    gestaltPortable = 10,
    gestaltMacIIci = 11,
    gestaltMacIIfx = 13,
    gestaltMacClassic = 17,
    gestaltMacIIsi = 18,
    gestaltMacLC = 19
};
enum {
	gestaltQuadra900 		= 20,
	gestaltPowerBook170 	= 21,
	gestaltQuadra700 		= 22,
	gestaltClassicII		= 23,
	gestaltPowerBook100 	= 24,
	gestaltPowerBook140 	= 25,
	gestaltQuadra950 		= 26,
	gestaltMacLCIII			= 27,
	gestaltPowerBookDuo210	= 29,
	gestaltCentris650		= 30,
	gestaltPowerBookDuo230	= 32,
	gestaltPowerBook180		= 33,
	gestaltPowerBook160		= 34,
	gestaltQuadra800		= 35,
	gestaltMacLCII 			= 37,
	gestaltPowerBookDuo250	= 38,			
	gestaltMacIIvx			= 45,
	gestaltColorClassic		= 49,
	gestaltPowerbook180c	= 50,
	gestaltCentris610		= 52,
	gestaltPowerBook145		= 54,
	gestaltLC520			= 56,
	gestaltCentris660AV		= 60,
	gestaltPowerBookDuo270C	= 77,
	gestaltQuadra840AV		= 78
	
#define gestaltMachineIcon		'micn'		/* machine icon */
#define gestaltROMSize			'rom '		/* rom size */
#define gestaltROMVersion		'romv'		/* rom version */
#define gestaltSystemVersion 	'sysv'		/* system version*/
};

#pragma procname SelectorFunction
typedef pascal OSErr (*SelectorFunctionProcPtr)(OSType selector, long *response);

#ifdef __cplusplus
extern "C" {
#endif
#if SystemSevenOrLater

#pragma parameter __D0 Gestalt(__D0,__A1)
pascal OSErr Gestalt(OSType selector,long *response)
    = {0xA1AD,0x2288};

#pragma parameter __D0 NewGestalt(__D0,__A0)
pascal OSErr NewGestalt(OSType selector,SelectorFunctionProcPtr gestaltFunction)
    = {0xA3AD};

#pragma parameter __D0 ReplaceGestalt(__D0,__A0,__A1)
pascal OSErr ReplaceGestalt(OSType selector,SelectorFunctionProcPtr gestaltFunction,SelectorFunctionProcPtr *oldGestaltFunction)
	= {0x2F09, 0xA5AD, 0x225F, 0x2288};

#else

pascal OSErr Gestalt(OSType selector,long *response);
pascal OSErr NewGestalt(OSType selector,SelectorFunctionProcPtr gestaltFunction);
pascal OSErr ReplaceGestalt(OSType selector,SelectorFunctionProcPtr gestaltFunction,SelectorFunctionProcPtr *oldGestaltFunction);

#endif

#ifdef __cplusplus
}
#endif

#endif
