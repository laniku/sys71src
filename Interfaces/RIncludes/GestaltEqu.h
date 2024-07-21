/*
	File:		GestaltEqu.h

	Contains:	Gestalt include file

	Written by:	Carl C. Hewitt		November 30th, 1988

	Copyright:	© 1988-1993 by Apple Computer, Inc.  All rights reserved.

	Change History (most recent first):

	   <SM6>	 11/8/93	JRH		Added gestaltPowerBookDuo250 and gestaltPowerBookDuo270C.
	   <SM5>	 8/16/93	BG		Updated machinetype list so that it only has RELEASED machines
									in it. Unreleased machines go in GestaltPriv.r.
	   <SM4>	 6/14/93	kc		Roll in Ludwig.
		 <2>	 4/20/93	fau		#1079789: Bug # 1079789:  Added Cyclone40, Tempest25, and
									Tempest33 to the equates.
	   <SM3>	 7/28/92	WS		add realtime manager attribute for gestalt call
	   <SM1>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H3>	 4/13/92	SWC		Updated the list of machine types.
		<H2>	11/12/91	jmp		Just brought this ancient file slightly more up-to-date.
		<2.6>	 7/16/89	CSL		Rolling Reality source for Aurora.  Original Reality
									version is 2.6, 2.7. Original comments are below:
		{2.7}	 7/16/89	CCH		NEEDED FOR AURORA AND 6.0.4: Added gestaltFirstSlotNumber
									selector. Added additional information to gestaltHardwareAttr
									selector. Added gestaltAMU to gestaltMMUType selector.
									Added gestaltParityAttr selector.
		{2.6}	 7/10/89	CCH		NEEDED FOR AURORA: Removed gestaltFirstSlotNumber selector.
		<2.5>	 6/30/89	CCH		Added gestaltLowMemorySize selector.
		<2.4>	 6/26/89	CCH		Added gestaltFirstSlotNumber selector.
		<2.3>	  6/9/89	CCH		Changes: Changed a/ux selector to be version-based.
									Added gestaltAddressingModeAttr, gestaltAUXVersion,
									gestaltSlotAttr, gestaltSoundAttr, gestaltTimeMgrVersion,
									GestaltRBVAddr, gestaltHardwareAttr, gestaltNuBusSlotCount
									selectors.  Made result equates for attribute selectors bit
									numbers instead of masks.
		<2.2>	 5/25/89	CCH		Revised Gestalt equates to be more consistent.
		<2.1>	 5/23/89	CCH		Added several new gestalt function codes.
		<2.0>	 5/18/89	CCH		Changed equate naming convention to "gestalt" prefix.
									Started using character constants for values. Removed all
									return values for "unknown", except for one.
		<1.9>	 4/20/89	CCH		Added new equate for virtual RAM size.
		<1.8>	 4/16/89	CCH		Changed equate prefix from "G" to "z".
		<1.7>	  4/3/89	CCH		Added equates for portable and ISO keyboards. Changed names
									of some equates.
		<1.6>	 3/30/89	CCH		Took out GROMSize.
		<1.5>	 3/16/89	CCH		Changed G24BitQD to z8BitQD.
		<1.4>	 3/16/89	CCH		Moved definitions of special codes to GestaltPriv.h.
		<1.3>	  3/6/89	CCH		Changed MAXINT to 0x7FFFFFFF.
		<1.2>	  3/2/89	CCH		Changed MMU equates per design review decisions.
		<1.1>	 2/23/89	CCH		Added new Gestalt equates.
		<1.0>	 2/21/89	CCH		Adding to EASE for the first time.
*/



/************************
 *	Gestalt error codes
 ************************/
#define	gestaltUnknownErr			-5550			/* value returned if Gestalt doesn't know the answer */
#define	gestaltUndefSelectorErr		-5551			/* undefined selector was passed to Gestalt */
#define	gestaltDupSelectorErr		-5552			/* tried to add an entry that already existed */
#define	gestaltLocationErr			-5553			/* gestalt function ptr wasn't in sysheap */
	
/**************************
 *	Environment Selectors
 **************************/
#define	gestaltVersion				'vers'			/* gestalt version */

#define gestaltAddressingModeAttr	'addr'			/* addressing mode attributes */
#define gestalt32BitAddressing		0				/* using 32-bit addressing mode */
#define gestalt32BitSysZone			1				/* 32-bit compatible system zone */

#define	gestaltAppleTalkVersion		'atlk'			/* appletalk version */

#define	gestaltAUXVersion			'a/ux'			/* a/ux version, if present */
#define	gestaltAUXNotPresent		0

#define	gestaltFPUType				'fpu '			/* fpu type */
#define	gestaltNoFPU				0
#define	gestalt68881				1
#define	gestalt68882				2
#define gestalt68040FPU				3

#define	gestaltHardwareAttr			'hdwr'			/* hardware attributes */
#define	gestaltHasVIA1				0				/* VIA1 exists */
#define	gestaltHasVIA2				1				/* VIA2 exists */
#define	gestaltHasRBV				2				/* RBV exists */
#define	gestaltHasASC				3				/* Apple Sound Chip exists */
#define	gestaltHasSCC				4				/* SCC exists */
#define	gestaltHasOSS				5				/* OSS exists */
#define	gestaltHasSCSIDMA			6				/* SCSI DMA exists */
#define	gestaltHasSCSI				7				/* SCSI exists */
#define	gestaltHasSWIMIOP			8				/* SWIM IOP exists */
#define	gestaltHasSCCIOP			9				/* SCC IOP exists */
#define	gestaltHasFMC				10				/* Fitch memory controller exists */
#define	gestaltHasIWM				11				/* IWM/SWIM exists */
#define	gestaltHasPWM				12				/* PWM disk speed buffer exists */
#define	gestaltHasSoundBuffer		13				/* RAM-based sound buffer exists */
#define	gestaltHasVDAC				14				/* Video D/A converter and CLUT exists */
#define	gestaltHasPGC				15				/* Parity Generation Chip exists */

#define	gestaltKeyboardType			'kbd '			/* keyboard type */
#define	gestaltMacKbd				1
#define	gestaltMacAndPad			2
#define	gestaltMacPlusKbd			3
#define	gestaltExtADBKbd			4
#define	gestaltStdADBKbd			5
#define	gestaltPrtblADBKbd			6
#define	gestaltPrtblIntlKbd			7
#define	gestaltStdIntlADBKbd		8
#define	gestaltExtIntlADBKbd		9
#define gestaltADBKbdII				10
#define gestaltADBISOKbdII			11
#define gestaltPwrBkADBKbd			12
#define gestaltPwrBkISOKbd			13

#define	gestaltLowMemorySize		'lmem'			/* size of low memory area */

#define	gestaltLogicalRAMSize		'lram'			/* logical ram size */

#define	gestaltMMUType				'mmu '			/* mmu type */
#define	gestaltNoMMU				0				/* no MMU */
#define	gestaltAMU					1				/* address management unit */
#define	gestalt68851				2				/* 68851 PMMU */
#define	gestalt68030MMU				3				/* 68030 built-in MMU */
#define gestalt68040MMU				4				/* 68040 built-in MMU */

#define gestaltNuBusSlotCount		'nubs'			/* count of logical NuBus slots present */

#define	gestaltOSAttr				'osa '			/* o/s attributes */
#define	gestaltSysZoneGrowable		0				/* system heap is growable */
#define	gestaltLaunchCanReturn		1				/* can return from launch */
#define	gestaltLaunchFullFileSpec	2				/* can launch from full file spec */
#define	gestaltLaunchControl		3				/* launch control support available */
#define	gestaltTempMemSupport		4				/* temp memory support */
#define	gestaltRealTempMemory		5				/* temp memory handles are real */
#define	gestaltTempMemTracked		6				/* temporary memory handles are tracked */
#define	gestaltIPCSupport			7				/* IPC support is present */
#define	gestaltSysDebuggerSupport	8				/* system debugger support is present */

#define	gestaltLogicalPageSize		'pgsz'			/* logical page size */

#define	gestaltPowerMgrAttr			'powr'			/* power manager attributes */
#define	gestaltPMgrExists			0
#define	gestaltPMgrCPUIdle			1
#define	gestaltPMgrSCC				2
#define	gestaltPMgrSound			3

#define	gestaltProcessorType		'proc'			/* processor type */
#define	gestalt68000				1
#define	gestalt68010				2
#define	gestalt68020				3
#define	gestalt68030				4
#define gestalt68040				5

#define	gestaltParityAttr			'prty'			/* parity attributes */
#define	gestaltHasParityCapability	0				/* has ability to check parity */
#define	gestaltParityEnabled		1				/* parity checking enabled */

#define	gestaltQuickdrawType		'qd  '			/* quickdraw type */
#define	gestaltOriginalQD			0
#define	gestalt8BitQD				1
#define	gestalt32BitQD				2

#define	gestaltPhysicalRAMSize		'ram '			/* physical RAM size */
#define	gestaltRBVAddr				'rbv '			/* RBV base address */
#define	gestaltSCCReadAddr			'sccr'			/* scc read base address */
#define	gestaltSCCWriteAddr			'sccw'			/* scc read base address */

#define	gestaltSlotAttr				'slot'			/* slot attributes */
#define	gestaltSlotMgrExists		0				/* true is slot mgr exists */
#define	gestaltNuBusPresent			1				/* NuBus slots are present */
#define	gestaltSESlotPresent		2				/* SE PDS slot present */
#define	gestaltSE30SlotPresent		3				/* SE/30 slot present */
#define	gestaltPortableSlotPresent	4				/* Portable's slot present */

#define	gestaltFirstSlotNumber		'slt1'			/* returns first physical slot */

#define	gestaltSoundAttr			'snd '			/* sound attributes */
#define	gestaltStereoCapability		0				/* sound hardware has stereo capability */
#define	gestaltStereoMixing			1				/* stereo mixing on external speaker */
#define	gestaltHeadphonePluggedIn	2				/* a headphone is plugged into the jack */

#define	gestaltTimeMgrVersion		'tmgr'			/* time mgr version */
#define	gestaltStandardTimeMgr		1				/* standard time mgr is present */
#define	gestaltRevisedTimeMgr		2				/* revised time mgr is present */
#define	gestaltExtendedTimeMgr		3				/* extended time mgr is present */

#define	gestaltVIA1Addr				'via1'			/* via 1 base address */
#define	gestaltVIA2Addr				'via2'			/* via 2 base address */

#define	gestaltVMAttr				'vm  '			/* virtual memory attributes */
#define	gestaltVMNotInstalled		0

#define	gestaltRealtimeMgrAttr		'rtmr'			/* realtime manager attribute	<SM2> WS	*/
#define	gestaltRealtimeMgrPresent	0

/*************************
 *	Info-only selectors
 ************************/
#define	gestaltMachineType			'mach'			/* machine type */
#define	gestaltClassic			 1
#define	gestaltMacXL			 2
#define	gestaltMac512KE			 3
#define	gestaltMacPlus			 4
#define	gestaltMacSE			 5
#define	gestaltMacII			 6
#define	gestaltMacIIx			 7
#define	gestaltMacIIcx			 8
#define	gestaltMacSE030			 9
#define	gestaltPortable			10
#define	gestaltMacIIci			11
#define	gestaltMacIIfx			13
#define	gestaltMacClassic		17
#define	gestaltMacIIsi			18
#define	gestaltMacLC			19
#define gestaltQuadra900		20
#define gestaltPowerBook170		21
#define gestaltQuadra700		22
#define gestaltClassicII		23
#define gestaltPowerBook100		24
#define gestaltPowerBook140		25
#define gestaltQuadra950		26
#define gestaltMacLCIII			27
#define gestaltPowerBookDuo210	29
#define gestaltCentris650		30
#define gestaltPowerBookDuo230	32
#define gestaltPowerBook180		33
#define gestaltPowerBook160		34
#define gestaltQuadra800		35
#define gestaltMacLCII			37
#define gestaltPowerBookDuo250	38
#define gestaltMacIIvx			45
#define gestaltColorClassic		49
#define gestaltPowerbook180c	50
#define gestaltCentris610		52
#define gestaltPowerBook145		54
#define gestaltLC520			56
#define gestaltCentris660AV		60
#define gestaltPowerBookDuo270C	77
#define gestaltQuadra840AV		78

#define	gestaltROMSize				'rom '			/* rom size */
#define	gestaltROMVersion			'romv'			/* rom version */
#define	gestaltSystemVersion		'sysv'			/* system version*/

