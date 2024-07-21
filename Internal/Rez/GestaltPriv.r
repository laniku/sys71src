/*
	File:		GestaltPriv.r

	Contains:	Private Rez definitions for Gestalt

	Written by:	Scott Boyd

	Copyright:	© 1991, 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM7>	11/10/93	fau		Added gestalt for TNTProto1.
	   <SM6>	 11/9/93	RLE		added gestalts for 603-based PowerBooks
	   <SM5>	 11/9/93	KW		added gestalts for STP machines
	   <SM4>	 11/8/93	JRH		Removed gestaltDBLite33, gestaltDBLite16, and gestaltEscher33.
									gestaltEscher25 is now gestaltYeagerFSTN.
	   <SM3>	  9/1/93	BG		Added an gestaltPDM alias.
	   <SM2>	 8/16/93	BG		Updated machinetype list to something more current.
		 <2>	 8/28/91	JSM		Cleanup header.
		 <1>	 2/11/91	stb		first checked in
		 <0>	 2/11/91	stb		BAC:  derived from GestaltEqu.h

*/

#ifndef __GESTALT.R__
#define __GESTALT.R__


/************************
 *	  Gestalt error codes
 ************************/
#define	gestaltUnknownErr -5550				/* value returned if Gestalt doesn't know the answer */
#define	gestaltUndefSelectorErr -5551		/* undefined selector was passed to Gestalt */
#define	gestaltDupSelectorErr -5552			/* tried to add an entry that already existed */
#define	gestaltLocationErr -5553 			/* gestalt function ptr wasn't in sysheap */

/**************************
 *	  Environment Selectors
 **************************/

#define gestaltVersion 'vers'				/* gestalt version */
#define gestaltAddressingModeAttr 'addr'	/* addressing mode attributes */

#define	gestalt32BitAddressing 0 			/* using 32-bit addressing mode */
#define	gestalt32BitSysZone 1				/* 32-bit compatible system zone */
#define	gestalt32BitCapable 2				/* Machine is 32-bit capable */

#define gestaltAliasMgrAttr 'alis'			/* Alias Mgr Attributes */

#define	gestaltAliasMgrPresent 0 			/* True if the Alias Mgr is present */

#define gestaltAppleTalkVersion 'atlk'		/* appletalk version */
#define gestaltAUXVersion 'a/ux'			/*a/ux version, if present */
#define gestaltConnMgrAttr 'conn'			/* connection mgr attributes	*/

#define	gestaltConnMgrPresent 0
#define	gestaltConnMgrCMSearchFix 1			/* Fix to CMAddSearch?	   */

#define gestaltCRMAttr 'crm '				/* comm resource mgr attributes */

#define	gestaltCRMPresent 0

#define gestaltCTBVersion 'ctbv'			/* CommToolbox version */
#define gestaltDBAccessMgrAttr 'dbac'		/* Database Access Mgr attributes */

#define	gestaltDBAccessMgrPresent 0			/* True if Database Access Mgr present */

#define gestaltDITLExtAttr 'ditl'			/* AppenDITL, etc. calls from CTB */

#define	gestaltDITLExtPresent 0				/* True if calls are present */

#define gestaltEasyAccessAttr 'easy'		/* Easy Access attributes */

#define	gestaltEasyAccessOff 0,				/* if Easy Access present but off (no icon) */
#define	gestaltEasyAccessOn 1				/* if Easy Access "On" */
#define	gestaltEasyAccessSticky 2			/* if Easy Access "Sticky" */
#define	gestaltEasyAccessLocked 3			/* if Easy Access "Locked" */

#define gestaltEditionMgrAttr 'edtn'		/* Edition Mgr attributes */

#define	gestaltEditionMgrPresent 0			/* True if Edition Mgr present */

#define gestaltAppleEventsAttr 'evnt'		/* Apple Events attributes */

#define	gestaltAppleEventsPresent 0			/* True if Apple Events present */

#define gestaltFindFolderAttr 'fold'		/* Folder Mgr attributes */

#define	gestaltFindFolderPresent 0			/* True if Folder Mgr present */


#define gestaltFontMgrAttr 'font'			/* Font Mgr attributes */

#define	gestaltOutlineFonts 0				/* True if Outline Fonts supported */

#define gestaltFPUType 'fpu '				/* fpu type */

#define	gestaltNoFPU 0						/* no FPU */
#define	gestalt68881 1						/* 68881 FPU */
#define	gestalt68882 2						/* 68882 FPU */
#define	gestalt68040FPU 3					/* 68040 built-in FPU */

#define gestaltFSAttr 'fs  '				/* file system attributes */

#define	gestaltFullExtFSDispatching 0		/* has really cool new HFSDispatch dispatcher */
#define	gestaltHasFSSpecCalls 1				/* has FSSpec calls    */
#define	gestaltHasFileSystemManager 2		/* has a file system manager */

#define gestaltFXfrMgrAttr 'fxfr'			/* file transfer manager attributes */

#define	gestaltFXfrMgrPresent 0

#define gestaltHardwareAttr 'hdwr'			/* hardware attributes */

#define	gestaltHasVIA1 0 					/* VIA1 exists */
#define	gestaltHasVIA2 1 					/* VIA2 exists */
#define	gestaltHasASC 3						/* Apple Sound Chip exists */
#define	gestaltHasSCC 4						/* SCC exists */
#define	gestaltHasSCSI 7 					/* SCSI exists */
#define	gestaltHasSoftPowerOff 19			/* Capable of software power off */

#define gestaltHelpMgrAttr 'help'			/* Help Mgr Attributes */

#define	gestaltHelpMgrPresent 0				/* true if help mgr is present */

#define gestaltKeyboardType 'kbd '			/* keyboard type */

#define	gestaltMacKbd 1
#define	gestaltMacAndPad 2
#define	gestaltMacPlusKbd 3
#define	gestaltExtADBKbd 4

#define	gestaltStdADBKbd 5
#define	gestaltPrtblADBKbd 6
#define	gestaltPrtblISOKbd 7
#define	gestaltStdISOADBKbd 8
#define	gestaltExtISOADBKbd 9
#define	gestaltADBKbdII 10
#define	gestaltADBISOKbdII 11

#define gestaltLowMemorySize 'lmem' 		/* size of low memory area */
#define gestaltLogicalRAMSize 'lram'		/* logical ram size */
#define gestaltMiscAttr 'misc'				/* miscellaneous attributes */

#define	gestaltScrollingThrottle 0			/* true if scrolling throttle on */
#define	gestaltSquareMenuBar 2				/* true if menu bar is square */

#define gestaltMMUType 'mmu '				/* mmu type */

#define	gestaltNoMMU 0						/* no MMU */
#define	gestaltAMU 1 						/* address management unit */
#define	gestalt68851 2						/* 68851 PMMU */
#define	gestalt68030MMU 3					/* 68030 built-in MMU */
#define	gestalt68040MMU 4					/* 68040 built-in MMU */

#define gestaltStdNBPAttr 'nlup'			/* standard nbp attributes */

#define	gestaltStdNBPPresent 0

#define gestaltNotificationMgrAttr 'nmgr'	/* notification manager attributes */

#define	gestaltNotificationPresent 0 		/* notification manager exists */

#define gestaltNuBusConnectors 'sltc'		/* bitmap of NuBus connectors*/
#define gestaltOSAttr 'os  '				/* o/s attributes */

#define	gestaltSysZoneGrowable 0 			/* system heap is growable */
#define	gestaltLaunchCanReturn 1 			/* can return from launch */
#define	gestaltLaunchFullFileSpec 2			/* can launch from full file spec */
#define	gestaltLaunchControl 3				/* launch control support available */
#define	gestaltTempMemSupport 4				/* temp memory support */
#define	gestaltRealTempMemory 5				/* temp memory handles are real */
#define	gestaltTempMemTracked 6				/* temporary memory handles are tracked */
#define	gestaltIPCSupport 7					/* IPC support is present */
#define	gestaltSysDebuggerSupport 8			/* system debugger support is present */

#define gestaltOSTable 'ostt'				/*	OS trap table base	*/
#define gestaltToolboxTable 'tbtt'			/*	OS trap table base	*/
#define gestaltExtToolboxTable 'xttt'		/* Extended Toolbox trap table base */
#define gestaltLogicalPageSize 'pgsz'		/* logical page size */
#define gestaltPowerMgrAttr 'powr'			/* power manager attributes */

#define	gestaltPMgrExists 0
#define	gestaltPMgrCPUIdle 1
#define	gestaltPMgrSCC 2
#define	gestaltPMgrSound 3

#define gestaltPPCToolboxAttr 'ppc '		/* PPC toolbox attributes */

/*
 * PPC will return the combination of following bit fields.
 * e.g. gestaltPPCSupportsRealTime +gestaltPPCSupportsIncoming + gestaltPPCSupportsOutGoing
 * indicates PPC is cuurently is only supports real time delivery
 * and both incoming and outgoing network sessions are allowed.
 * By default local real time delivery is supported as long as PPCInit has been called.*/


#define	gestaltPPCToolboxPresent 0x0000		/* PPC Toolbox is present  Requires PPCInit to be called */
#define	gestaltPPCSupportsRealTime 0x1000	/* PPC Supports real-time delivery */
#define	gestaltPPCSupportsIncoming 0x0001	/* PPC will deny incoming network requests */
#define	gestaltPPCSupportsOutGoing 0x0002	/* PPC will deny outgoing network requests */

#define gestaltProcessorType 'proc' 		/* processor type */

#define	gestalt68000 1
#define	gestalt68010 2
#define	gestalt68020 3
#define	gestalt68030 4
#define	gestalt68040 5

#define gestaltParityAttr 'prty'			/* parity attributes */

#define	gestaltHasParityCapability 0 		/* has ability to check parity */
#define	gestaltParityEnabled 1				/* parity checking enabled */

#define gestaltQuickdrawVersion 'qd  '		/* quickdraw version */

#define	gestaltOriginalQD 0x000				/* original 1-bit QD */
#define	gestalt8BitQD 0x100					/* 8-bit color QD */
#define	gestalt32BitQD 0x200 				/* 32-bit color QD */
#define	gestalt32BitQD11 0x210				/* 32-bit color QDv1.1 */
#define	gestalt32BitQD12 0x220				/* 32-bit color QDv1.2 */
#define	gestalt32BitQD13 0x230				/* 32-bit color QDv1.3 */

#define	gestaltQuickdrawFeatures	'qdrw'	/* quickdraw features */
#define	gestaltHasColor 0					/* color quickdraw present */
#define	gestaltHasDeepGWorlds 1				/* GWorlds can be deeper than 1-bit */
#define	gestaltHasDirectPixMaps 2			/* PixMaps can be direct (16 or 32 bit) */
#define	gestaltHasGrayishTextOr 3			/* supports text mode grayishTextOr */

#define gestaltPhysicalRAMSize 'ram '		/* physical RAM size */
#define gestaltPopupAttr 'pop!' 			/* popup cdef attributes */

#define	gestaltPopupPresent 0

#define gestaltResourceMgrAttr 'rsrc'		/* Resource Mgr attributes */

#define	gestaltPartialRsrcs 0				/* True if partial resources exist */

#define gestaltScriptMgrVersion 'scri'		/* Script Manager version number	<08/05/89 pke> */
#define gestaltScriptCount 'scr#'			/* number of active script systems	  <08/05/89 pke> */
#define gestaltSerialAttr 'ser '			/* Serial attributes */

#define	gestaltHasGPIaToDCDa 0				/* GPIa connected to DCDa*/
#define	gestaltHasGPIaToRTxCa 1				/* GPIa connected to RTxCa clock input*/
#define	gestaltHasGPIbToDCDb 2				/* GPIb connected to DCDb */

#define gestaltSoundAttr 'snd ' 			/* sound attributes */

#define	gestaltStereoCapability 0			/* sound hardware has stereo capability */
#define	gestaltStereoMixing 1				/* stereo mixing on external speaker */
#define	gestaltSoundIOMgrPresent 3			/* The Sound I/O Manager is present */
#define	gestaltBuiltInSoundInput 4			/* built-in Sound Input hardware is present */
#define	gestaltHasSoundInputDevice 5 		/* Sound Input device available */

#define gestaltStandardFileAttr 'stdf'		/* Standard File attributes */

#define	gestaltStandardFile58 0				/* True if selectors 5-8 (StandardPutFile-CustomGetFile) are supported */

#define gestaltTextEditVersion 'te  '		/* TextEdit version number			  <08/05/89 pke> */

#define	gestaltTE1 1 						/* TextEdit in MacIIci ROM <8Aug89smb> */
#define	gestaltTE2 2							/* TextEdit with 6.0.4 Script Systems on MacIIci (Script bug fixes for MacIIci) <8Aug89smb> */
#define	gestaltTE3 3 						/* TextEdit with 6.0.4 Script Systems all but MacIIci <8Aug89smb> */
#define	gestaltTE4 4 						/* TextEdit in System 7.0 */
#define	gestaltTE5 5 						/* TextWidthHook available in TextEdit */

#define gestaltTermMgrAttr 'term'			/* terminal mgr attributes */

#define	gestaltTermMgrPresent 0

#define gestaltTimeMgrVersion 'tmgr'		/* time mgr version */

#define	gestaltStandardTimeMgr 1 			/* standard time mgr is present */
#define	gestaltRevisedTimeMgr 2				/* revised time mgr is present */
#define	gestaltExtendedTimeMgr 3 			/* extended time mgr is present */

#define gestaltVMAttr 'vm  '				/* virtual memory attributes */

#define	gestaltVMPresent 0					/* true if virtual memory is present */

/*************************
 *	  Info-only selectors
 ************************/

#define gestaltMachineType 'mach'			/* machine type */

#define gestaltCarnation33				28
#define gestaltColumbia					31
#define gestaltQuadra650				36
#define gestaltPenlite					39
#define gestaltVail16					40
#define gestaltCarnation25				41
#define gestaltCarnation16				42
#define gestaltCyclone33				43
#define gestaltBrazil16L				44
#define gestaltBrazil16F				46
#define gestaltBrazil32F				47
#define gestaltBrazilC					48
#define gestaltWombat40					51
#define gestaltQuadra610				53
#define gestaltBrazil32cF				55
#define gestaltWombat20					58
#define gestaltWombat40F				59
#define gestaltRiscQuadra700			61
#define gestaltVail33					62
#define gestaltWLCD33					63
#define gestaltPDM66F					64
#define gestaltPDM80F					65
#define gestaltPDM100F					66
#define gestaltTNTProto1				67
#define gestaltTesseractF				68
#define gestaltTesseractC				69
#define gestaltJust930					70
#define gestaltHokusai					71
#define gestaltBlackbird				72
#define gestaltBlackbirdLC				73
#define gestaltPDMEvt1					74
#define gestaltPDMEvt2					75
#define gestaltPDM50WLCD				gestaltPDMEvt2
#define gestaltYeagerFSTN				76
#define gestaltTempest33				79
#define gestaltHook33					80
#define gestaltSlice25					81
#define gestaltRiscCentris650			82
#define gestaltSlice33					83
#define gestaltNorad					84
#define gestaltBudMan					85
#define gestaltPrimus20					86
#define gestaltOptimus20				87
#define gestaltHookTV					88
#define gestaltLC475					89
#define gestaltPrimus33					90
#define gestaltOptimus25				91
#define gestaltLC575					92
#define gestaltAladdin20				93
#define gestaltQuadra605				94
#define gestaltAladdin33				95
#define gestaltMalcolm25				96
#define gestaltMalcolm33				97
#define gestaltSlimus25					98
#define gestaltSlimus33					99
#define gestaltPDM66WLCD				100
#define gestaltPDM80WLCD				101
#define gestaltYeagerG					102
#define gestaltYeagerC					103
#define gestaltRiscQuadra900			104
#define gestaltRiscQuadra950			105
#define gestaltRiscCentris610			106
#define gestaltRiscQuadra800			107
#define gestaltRiscQuadra610			108
#define gestaltRiscQuadra650			109
#define gestaltRiscTempest				110
#define gestaltPDM50L					111
#define gestaltPDM66L					112
#define gestaltPDM80L					113
#define gestaltBlackbirdBFD				114			/* Blackbird (66/33MHz 040LC, VIA1&2, Pratt, PGE, 256 color 10.X" TFT LCD, 1 direct slot) */
#define gestaltJedi						115			/* Jedi (33MHz, 030, low cost AIO powerbook, MSC, IDE, floppy ) */
#define gestaltSTPQ700					116			/* Q700 with STP card */
#define gestaltSTPQ900					117			/* Q900 with STP card */
#define gestaltSTPQ950					118			/* Q950 with STP card */	
#define gestaltSTPC610					119			/* C610 with STP card */
#define gestaltSTPC650					120			/* C650 with STP card */
#define gestaltSTPQ610					121			/* Q610 with STP card */
#define gestaltSTPQ650					122			/* Q650 with STP card */	
#define gestaltSTPQ800					123			/* Q800 with STP card */
#define gestaltAJ						124			/* AJ (66 MHz 603, duo powerbook) */
#define gestaltAJ80						125			/* AJ (80 MHz 603, duo powerbook)  */
#define gestaltMalcolmBB				126			/* Malcolm (yep, same name as WLCD II)(66 MHz 603 upgrade to Blackbird) */
#define gestaltMalcolmBB80				127			/* Malcolm (yep, same name as WLCD II)(80 MHz 603 upgrade to Blackbird) */
#define gestaltM2						128			/* M2 (66 MHz 603, duo powerbook) */
#define gestaltM280						129			/* M2 (80 MHz 603, duo powerbook) */


#define gestaltMachineIcon 'micn'			/* machine icon */
#define gestaltROMSize 'rom '				/* rom size */
#define gestaltROMVersion 'romv'			/* rom version */
#define gestaltSystemVersion 'sysv' 		/* system version*/
#define kMachineNameStrID -16395			/* use the index returned from gestaltMachineType on this STR# */

#endif	__GESTALT.R__
