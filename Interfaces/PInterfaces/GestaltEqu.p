{************************************************************
    GestaltEqu.p
    Pascal Interface to the Macintosh Libraries

        Copyright Apple Computer, Inc.    1988-1992
        All rights reserved
		
	Change History (most recent first):

	  <SM15>	 11/8/93	JRH		Added gestaltPowerBookDuo250 and gestaltPowerBookDuo270C.
	  <SM14>	10/28/93	SAM		Roll in <MC3> from mc900ftjesus.
	   <MC3>	10/28/93	SAM		Changed gestaltNativeCPUtype equates (making each cpu type take
									a range of 256 per architecture).
	  <SM13>	09-24-93	jmp		Rolled in various equates from the Excelsior sources.
	  <SM12>	 8/16/93	BG		Updated machinetype list to something more current.
	  <SM11>	  8/4/93	JDR		synch with Sound Mgr project.
		<10>	  8/4/93	IH		#1101633,1098397,1101795,1101636,1102280 <KON>: Fix 1102280. Add
									CloseView and Display Manager gestalt selectors.
	   <SM9>	 6/14/93	kc		Roll in Ludwig.
	   <LW2>	 4/29/93	fau		Bug #1081636:  Update from Reality:  changed some of the
									gestaltSoundattr bit assignments and added some others to allow
									more useful encoding of sound hardware information.
	   <SM8>	 2/11/93	SAM		Added Emulated MMU type
	   <SM7>	12/13/92	SAM		Added gestaltSysArchitecture and gestaltNativeCPUType.
	   <SM6>	 7/29/92	CSS		Update from Reality:
	   								<54> 7/28/92 JDR	<DCL> Added Sound Mgr 3.0 flags.
	   <SM5>	 7/28/92	WS		add realtime manager attribute for gestalt call
		<53>	 7/23/92	DTY		Remove inline from last change, since Gestalt is register based,
									and Pascal doesnÕt have #pragma parameters.
		<52>	 7/15/92	DCL		Adding SystemSevenOrLater inline for the Gestalt call.  Added
									TSM selector.
		<51>	  6/5/92	DC		Add the selector for checking for the presence of icon
									utilities.
		<50>	  6/2/92	JSM		#1031451 <csd>: Add gestaltPowerBook145.
		<49>	 5/27/92	KIP		#1030293,<JDR>: Add gestaltPlayAndRecord bit for sound
									attributes.
		<48>	 5/27/92	DCL		Moved gestaltQuadra950 into the public consciousness.
		<47>	  4/9/92	JSM		#1026795,<DTY>: Add gestaltMacLCII.
		<46>	 12/3/91	SAM		Added gestaltHasSCSI961 and gestaltHasSCSI962 bits to the 'hdwr'
									selector.
		<45>	 12/3/91	JL		SAM: Added support for Fall '91 CPUs and keyboards. Also added
									gestaltHasUniversalROM as per assembly file..
		<44>	11/21/91	YK		Removed selectors for input utilities.
		<43>	 11/1/91	KSM		Added gestaltHelpMgrExtensions.
		<42>	10/30/91	YK		Added selectors for Dictionary Mgr, Input Utilities and
									Component Mgr.
		<41>	 8/28/91	CH		Updated interface headers for consistency.
		<40>	 8/22/91	gbm		(really csd) Added gestaltAliasMgrSupportsRemoteAppletalk
		<39>	 7/24/91	JL		Updated copyright. Adjusted file to match database.
		<38>	 6/26/91	BH		added gestaltFXfrMgrMultiFile
		<37>	 6/26/91	BH		added selectors for CTB11 stuff (errorstring for CM, TM, FT,
									CRMPersistentFix, CRMToolRsrcCalls)
		<36>	 6/26/91	BH		added gestaltCRMPersistentFix constant
		<35>	 6/14/91	JL		Checked in official MPW 3.2Ä version. Added kMachineNameStrID
									constant to be consistent with the C header.
		<34>	  2/7/91	KON		CEL: BRC# Gang of 5: Remove equate for gestaltOriginalQD1.
		<33>	  2/4/91	gbm		JDR, #gbm-0003: Add the gestaltQuickdrawFeatures selector
		<32>	 1/29/91	JAL		Checked in Database generated file from DSG.
		<31>	 1/15/91	gbm		(bbm) Add new hardware attribute, gestaltHasSoftPowerOff
		<30>	12/14/90	JDR		(KIP) adding Gestalt selector gestaltHasSoundInputDevice and
									renaming gestaltSoundInputPresent.
		<29>	 12/5/90	gbm		<dba> Add two file system selectors: one for FSSpec calls
									existing, and another for file system manager existing
		<28>	 12/3/90	EMT		<GSM> Fix comments for PPCToolbox
		<27>	11/16/90	KON		Add equates for QuickDraw versions 1.1, 1.2, 1.3, and
									OriginalQD1 [smc]
		<26>	11/15/90	SMB		Added another TextEdit version, gestaltTE5, for the new
									TextWidthHook.
		<25>	 11/8/90	EMT		<stb>Fix comments and spelling errors for PPCToolBox. Remove
									masks that are not applicable for system 7.0
		<24>	10/8/90		JAL		Added SoundIOMgrPresent and SoundInputPresent to match C Interfaces.
		<23>	 9/14/90	gbm		SamÕs compiler must be broken.
		<22>	 9/14/90	SAM		Added final machine names for IIsi, LC, and Classic
		<21>	 9/10/90	gbm		add file system attribute selector, gestaltFSAttr
		<20>	 8/30/90	PP		gestaltFolderMgrAttr is gestaltFindFolderAttr.
									gestaltFolderMgrPresent is gestaltFindFolderPresent.
		<19>	 8/14/90	JWK		NEEDED FOR SIXPACK: Added NuBus and Serial selectors.
		<18>	 8/13/90	gbm		add selectors for trap table bases
		<17>	  8/6/90	kaz		Removed CommToolbox refs to xxErrorString and cmMultiAsyncIO;
									renumbered cmSearchFix.
	   <15+>	 7/25/90	RLC		Add gestaltEasyAccessAttr & result codes.
		<15>	 6/25/90	kaz		Removed 'ctbm', 'ctbu'. Added 'ditl'.
		<14>	 6/23/90	kaz		Fixed typo to 'term', and 'fxfr'.
		<13>	 6/11/90	CCH		Moved standard file selector in from GestaltEqu.a.
		<12>	 6/10/90	kaz		Ported CommToolbox stuff from .a EQU
		<11>	  5/2/90	PKE		Fixed <10> by adding semicolon after gestaltSquareMenuBar
									definition.
		<10>	  5/1/90	CCH		Added gestaltSquareMenuBar response bit to gestaltMiscAttr.
		 <9>	 4/11/90	dba		add machineicon selector
		 <8>	  4/9/90	S		Included PPC Gestalt Selectors.
		 <7>	 3/29/90	JNG		Make this compile (forgotten semi after CommToolbox selector)
		 <6>	 3/28/90	CCH		Added MacIIfx equate and Comm toolbox selector.
		 <4>	  3/6/90	CCH		Updated to latest equates.
		 <3>	  1/9/90	ngk		change gestaltEditionMgr to gestaltEditionMgrAttr
		 <2>	  1/5/90	CCH		NEEDED FOR 6.0.5: Added RPU and Orwell bits to hardware
									selector, added slot selectors back in temporarily, and added
									equate for 68040 FPU.
		 <1>	  1/2/90	CCH		Changed name from GestaltIntf.p.
	   <1.6>	12/15/89	CCH		Updated Gestalt Equates, added some new 7.0 selectors.
	   <1.5>	 8/24/89	CCH		Changed gestaltOSAttr to be 'os '.
	   <1.4>	  8/9/89	CCH		NEEDED FOR 6.0.4: Changed return values for gestaltQuickdrawType
									to be version based, and changed the selector name to
									gestaltQuickdrawVersion.
	   <1.3>	  8/8/89	SMB		NEEDED FOR 6.0.4: added definitions for gestaltTextEditVersion
	   <1.2>	  8/7/89	PKE		NEEDED FOR 6.0.4, since this interface will be used instead of
									Gestalt.p: - Added gestaltScriptMgrVersion, gestaltScriptCount
									selectors (for Script Manager) - Added gestaltTextEditVersion
									selector (for TextEdit)
	   <1.1>	  8/3/89	DAF		FOR 6.0.4 BUILD - Stupid EASE screwed up the pascal comments
	   <1.0>	  8/3/89	DAF		FOR 6.0.4 BUILD - Converted C header so Pascal can use Gestalt.

	To Do:
************************************************************}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
    UNIT GestaltEqu;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingGestaltEqu}
{$SETC UsingGestaltEqu := 1}

{$I+}
{$SETC GestaltEquIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := GestaltEquIncludes}

CONST

{***********************
 *    Gestalt error codes
 ***********************}
gestaltUnknownErr = -5550;              { value returned if Gestalt doesn't know the answer }
gestaltUndefSelectorErr = -5551;        { undefined selector was passed to Gestalt }
gestaltDupSelectorErr = -5552;          { tried to add an entry that already existed }
gestaltLocationErr = -5553;             { gestalt function ptr wasn't in sysheap }

{*************************
 *    Environment Selectors
 *************************}
gestaltVersion = 'vers';                { gestalt version }
gestaltAddressingModeAttr = 'addr';     { addressing mode attributes }
gestalt32BitAddressing = 0;             { using 32-bit addressing mode }
gestalt32BitSysZone = 1;                { 32-bit compatible system zone }
gestalt32BitCapable = 2;                { Machine is 32-bit capable }
gestaltAliasMgrAttr = 'alis';           { Alias Mgr Attributes }
gestaltAliasMgrPresent = 0;             { True if the Alias Mgr is present }
gestaltAliasMgrSupportsRemoteAppletalk = 1; { True if the Alias Mgr knows about Remote Appletalk }
gestaltAppleTalkVersion = 'atlk';       { appletalk version }
gestaltAUXVersion = 'a/ux';             {a/ux version, if present }
gestaltCloseViewAttr = 'BSDa';			{CloseView attributes}
gestaltCloseViewEnabled	= 0;			{Closeview enabled (dynamic bit - returns current state)}
gestaltCloseViewDisplayMgrFriendly = 1;	{Closeview compatible with Display Manager (FUTURE)}
gestaltConnMgrAttr = 'conn';            { connection mgr attributes    }
gestaltConnMgrPresent = 0;
gestaltConnMgrCMSearchFix = 1;          { Fix to CMAddSearch?     }
gestaltConnMgrErrorString = 2; 			{ has CMGetErrorString() }
gestaltConnMgrMultiAsyncIO = 3; 		{ CMNewIOPB, CMDisposeIOPB, CMPBRead, CMPBWrite, CMPBIOKill }
gestaltComponentMgr = 'cpnt';			{ Component Mgr version }
gestaltTSMgrVersion = 'tsmv';			{ Text Services Mgr version, if present }
gestaltCRMAttr = 'crm ';                { comm resource mgr attributes }
gestaltCRMPresent = 0;
gestaltCRMPersistentFix = 1;			{ fix for persistent tools }
gestaltCRMToolRsrcCalls = 2;			{ has CRMGetToolResource/ReleaseToolResource }

gestaltNativeCPUtype =	'cput';			{ The native CPU type								<SM7><MC3>	}
										
gestaltCPU68000		= 0;				{ 68000 Architecture }
gestaltCPU68010		= 1;
gestaltCPU68020		= 2;
gestaltCPU68030		= 3;
gestaltCPU68040		= 4;
										{ PowerPC Architecture }
gestaltCPU601		= 257;				{ IBM 601 }
gestaltCPU603		= 259;
gestaltCPU604		= 260;

gestaltCTBVersion = 'ctbv';             { CommToolbox version }
gestaltDBAccessMgrAttr = 'dbac';        { Database Access Mgr attributes }
gestaltDBAccessMgrPresent = 0;          { True if Database Access Mgr present }
gestaltDITLExtAttr = 'ditl';            { AppenDITL, etc. calls from CTB }
gestaltDITLExtPresent = 0;              { True if calls are present }
gestaltDisplayMgrAttr = 'dply';			{Display Manager attributes}
gestaltDisplayMgrPresent = 0;			{True if Display Mgr is present}
gestaltDisplayMgrVers = 'dplv';			{Display Manager version}
gestaltEasyAccessAttr = 'easy';         { Easy Access attributes }
gestaltEasyAccessOff = 0;               { if Easy Access present, but off (no icon) }
gestaltEasyAccessOn = 1;                { if Easy Access "On" }
gestaltEasyAccessSticky = 2;            { if Easy Access "Sticky" }
gestaltEasyAccessLocked = 3;            { if Easy Access "Locked" }
gestaltEditionMgrAttr = 'edtn';         { Edition Mgr attributes }
gestaltEditionMgrPresent = 0;           { True if Edition Mgr present }
gestaltAppleEventsAttr = 'evnt';        { Apple Events attributes }
gestaltAppleEventsPresent = 0;          { True if Apple Events present }
gestaltFindFolderAttr = 'fold';         { Folder Mgr attributes }
gestaltFindFolderPresent = 0;           { True if Folder Mgr present }
gestaltFontMgrAttr = 'font';            { Font Mgr attributes }
gestaltOutlineFonts = 0;                { True if Outline Fonts supported }
gestaltFPUType = 'fpu ';                { fpu type }
gestaltNoFPU = 0;                       { no FPU }
gestalt68881 = 1;                       { 68881 FPU }
gestalt68882 = 2;                       { 68882 FPU }
gestalt68040FPU = 3;                    { 68040 built-in FPU }
gestaltFSAttr = 'fs  ';                 { file system attributes }
gestaltFullExtFSDispatching = 0;        { has really cool new HFSDispatch dispatcher }
gestaltHasFSSpecCalls = 1;              { has FSSpec calls    }
gestaltHasFileSystemManager = 2;        { has a file system manager }
gestaltFXfrMgrAttr = 'fxfr';            { file transfer manager attributes }
gestaltFXfrMgrPresent = 0;
gestaltFXfrMgrMultiFile = 1;			{ supports FTSend and FTReceive }
gestaltFXfrMgrErrorString = 2;			{ supports FTGetErrorString }
gestaltHardwareAttr = 'hdwr';           { hardware attributes }
gestaltHasVIA1 = 0;                     { VIA1 exists }
gestaltHasVIA2 = 1;                     { VIA2 exists }
gestaltHasASC = 3;                      { Apple Sound Chip exists }
gestaltHasSCC = 4;                      { SCC exists }
gestaltHasSCSI = 7;                     { SCSI exists }
gestaltHasSoftPowerOff = 19;            { Capable of software power off }
gestaltHasSCSI961 = 21;					{ 53C96 SCSI controller on internal bus }
gestaltHasSCSI962 = 22;					{ 53C96 SCSI controller on external bus }
gestaltHasUniversalROM = 24;			{ Do we have a Universal ROM?}
gestaltHelpMgrAttr = 'help';            { Help Mgr Attributes }
gestaltHelpMgrPresent = 0;              { true if help mgr is present }
gestaltHelpMgrExtensions = 1;           { true if help mgr extensions are installed }
gestaltKeyboardType = 'kbd ';           { keyboard type }
gestaltMacKbd = 1;
gestaltMacAndPad = 2;
gestaltMacPlusKbd = 3;
gestaltExtADBKbd = 4;
gestaltStdADBKbd = 5;
gestaltPrtblADBKbd = 6;
gestaltPrtblISOKbd = 7;
gestaltStdISOADBKbd = 8;
gestaltExtISOADBKbd = 9;
gestaltADBKbdII = 10;
gestaltADBISOKbdII = 11;
gestaltPwrBookADBKbd = 12;
gestaltPwrBookISOADBKbd = 13;
gestaltLowMemorySize = 'lmem';          { size of low memory area }
gestaltLogicalRAMSize = 'lram';         { logical ram size }
gestaltMiscAttr = 'misc';               { miscellaneous attributes }
gestaltScrollingThrottle = 0;           { true if scrolling throttle on }
gestaltSquareMenuBar = 2;               { true if menu bar is square }

gestaltMMUType = 'mmu '; 				{ mmu type }
gestaltNoMMU 	= 0; 					{ no MMU }
gestaltAMU 		= 1; 					{ address management unit }
gestalt68851 	= 2; 					{ 68851 PMMU }
gestalt68030MMU = 3; 					{ 68030 built-in MMU }
gestalt68040MMU = 4; 					{ 68040 built-in MMU }
gestaltEMMU1 	= 5;					{ Emulated MMU <SM18> }

gestaltStdNBPAttr = 'nlup';             { standard nbp attributes }
gestaltStdNBPPresent = 0;
gestaltNotificationMgrAttr = 'nmgr';    { notification manager attributes }
gestaltNotificationPresent = 0;         { notification manager exists }
gestaltNuBusConnectors = 'sltc';        { bitmap of NuBus connectors}
gestaltOSAttr = 'os  ';                 { o/s attributes }
gestaltSysZoneGrowable = 0;             { system heap is growable }
gestaltLaunchCanReturn = 1;             { can return from launch }
gestaltLaunchFullFileSpec = 2;          { can launch from full file spec }
gestaltLaunchControl = 3;               { launch control support available }
gestaltTempMemSupport = 4;              { temp memory support }
gestaltRealTempMemory = 5;              { temp memory handles are real }
gestaltTempMemTracked = 6;              { temporary memory handles are tracked }
gestaltIPCSupport = 7;                  { IPC support is present }
gestaltSysDebuggerSupport = 8;          { system debugger support is present }
gestaltOSTable = 'ostt';                {  OS trap table base  }
gestaltToolboxTable = 'tbtt';           {  OS trap table base  }
gestaltExtToolboxTable = 'xttt';        { Extended Toolbox trap table base }
gestaltLogicalPageSize = 'pgsz';        { logical page size }
gestaltPowerMgrAttr = 'powr';           { power manager attributes }
gestaltPMgrExists = 0;
gestaltPMgrCPUIdle = 1;
gestaltPMgrSCC = 2;
gestaltPMgrSound = 3;
gestaltPPCToolboxAttr = 'ppc ';         { PPC toolbox attributes }

{
 * PPC will return the combination of following bit fields.
 * e.g. gestaltPPCSupportsRealTime +gestaltPPCSupportsIncoming + gestaltPPCSupportsOutGoing
 * indicates PPC is cuurently is only supports real time delivery
 * and both incoming and outgoing network sessions are allowed.
 * By default local real time delivery is supported as long as PPCInit has been called.}

gestaltPPCToolboxPresent = $0000;       { PPC Toolbox is present  Requires PPCInit to be called }
gestaltPPCSupportsRealTime = $1000;     { PPC Supports real-time delivery }
gestaltPPCSupportsIncoming = $0001;     { PPC will deny incoming network requests }
gestaltPPCSupportsOutGoing = $0002;     { PPC will deny outgoing network requests }
gestaltProcessorType = 'proc';          { processor type }
gestalt68000 = 1;
gestalt68010 = 2;
gestalt68020 = 3;
gestalt68030 = 4;
gestalt68040 = 5;
gestaltParityAttr = 'prty';             { parity attributes }
gestaltHasParityCapability = 0;         { has ability to check parity }
gestaltParityEnabled = 1;               { parity checking enabled }
gestaltQuickdrawVersion = 'qd  ';       { quickdraw version }
gestaltOriginalQD = $000;               { original 1-bit QD }
gestalt8BitQD = $100;                   { 8-bit color QD }
gestalt32BitQD = $200;                  { 32-bit color QD }
gestalt32BitQD11 = $210;                { 32-bit color QDv1.1 }
gestalt32BitQD12 = $220;                { 32-bit color QDv1.2 }
gestalt32BitQD13 = $230;                { 32-bit color QDv1.3 }
gestaltQuickdrawFeatures = 'qdrw';		{ quickdraw features }
gestaltHasColor = 0;					{ color quickdraw present }
gestaltHasDeepGWorlds = 1;				{ GWorlds can be deeper than 1-bit }
gestaltHasDirectPixMaps = 2;			{ PixMaps can be direct (16 or 32 bit) }
gestaltHasGrayishTextOr = 3;			{ supports text mode grayishTextOr }
gestaltSupportsMirroring = 4;			{ Supports video mirroring via the Display Manager. }
gestaltPhysicalRAMSize = 'ram ';        { physical RAM size }
gestaltPopupAttr = 'pop!';              { popup cdef attributes }
gestaltPopupPresent = 0;
gestaltResourceMgrAttr = 'rsrc';        { Resource Mgr attributes }
gestaltPartialRsrcs = 0;                { True if partial resources exist }
gestaltScriptMgrVersion = 'scri';       { Script Manager version number    <08/05/89 pke> }
gestaltScriptCount = 'scr#';            { number of active script systems    <08/05/89 pke> }
gestaltSerialAttr = 'ser ';             { Serial attributes }
gestaltHasGPIaToDCDa = 0;               { GPIa connected to DCDa}
gestaltHasGPIaToRTxCa = 1;              { GPIa connected to RTxCa clock input}
gestaltHasGPIbToDCDb = 2;               { GPIb connected to DCDb }
gestaltSoundAttr = 'snd ';              { sound attributes }
gestaltStereoCapability = 0;            { sound hardware has stereo capability }
gestaltStereoMixing = 1;                { stereo mixing on external speaker }
gestaltSoundIOMgrPresent = 3;           { The Sound I/O Manager is present }
gestaltBuiltInSoundInput = 4;           { built-in Sound Input hardware is present }
gestaltHasSoundInputDevice = 5;         { Sound Input device available }
gestaltPlayAndRecord = 6;				{ built-in hardware can play and record simultaneously }
gestalt16BitSoundIO = 7;				{ sound hardware can play and record 16-bit samples }						{ LW2 }
gestaltStereoInput = 8;					{ sound hardware can record stereo }										{ LW2 }
gestaltLineLevelInput = 9;				{ sound input port requires line level }									{ LW2 }
										{ the following bits are not defined prior to Sound Mgr 3.0 }
gestaltSndPlayDoubleBuffer = 10;		{ SndPlayDoubleBuffer available, set by Sound Mgr 3.0 and later }				{ LW2 }
gestaltMultiChannels = 11;				{ multiple channel support, set by Sound Mgr 3.0 and later }				{ LW2 }
gestalt16BitAudioSupport = 12;			{ 16 bit audio data supported, set by Sound Mgr 3.0 and later }				{ LW2 }
gestaltStandardFileAttr = 'stdf';       { Standard File attributes }
gestaltStandardFile58 = 0;              { True if selectors 5-8 (StandardPutFile-CustomGetFile) are supported }

gestaltSysArchitecture =	'sysa';		{ System architecture								<SM7>	}
gestalt68k 		=	1;					{ Motorola MC68k architecture 	}
gestaltPowerPC	=	2;					{ IBM PowerPC architecture		}

gestaltTextEditVersion = 'te  ';        { TextEdit version number            <08/05/89 pke> }
gestaltTE1 = 1;                         { TextEdit in MacIIci ROM <8Aug89smb> }
gestaltTE2 = 2;                         { TextEdit with 6.0.4 Script Systems on MacIIci (Script bug fixes for MacIIci) <8Aug89smb> }
gestaltTE3 = 3;                         { TextEdit with 6.0.4 Script Systems all but MacIIci <8Aug89smb> }
gestaltTE4 = 4;                         { TextEdit in System 7.0 }
gestaltTE5 = 5;                         { TextWidthHook available in TextEdit }
gestaltTermMgrAttr = 'term';            { terminal mgr attributes }
gestaltTermMgrPresent = 0;
gestaltTermMgrErrorString = 2;
gestaltTimeMgrVersion = 'tmgr';         { time mgr version }
gestaltStandardTimeMgr = 1;             { standard time mgr is present }
gestaltRevisedTimeMgr = 2;              { revised time mgr is present }
gestaltExtendedTimeMgr = 3;             { extended time mgr is present }
gestaltVMAttr = 'vm  ';                 { virtual memory attributes }
gestaltVMPresent = 0;                   { true if virtual memory is present }
gestaltDictionaryMgrAttr = 'dict';		{ Dictionary Manager attributes }
gestaltDictionaryMgrPresent = 0;
gestaltIconUtilities = 'icon';			{ Icon Utilities attributes }
gestaltIconUtilitiesPresent = 0; 		{ true if icon utilities are present }
gestaltRealtimeMgrAttr = 'rtmr';		{ realtime manager attributes <SM1> WS}
gestaltRealtimeMgrPresent = 0; 			{ true if realtime manager are present <SM1> WS}

{************************
 *    Info-only selectors
 ***********************}
gestaltMachineType = 'mach';            { machine type }
kMachineNameStrID = -16395;
gestaltClassic			= 1;
gestaltMacXL			= 2;
gestaltMac512KE			= 3;
gestaltMacPlus			= 4;
gestaltMacSE			= 5;
gestaltMacII			= 6;
gestaltMacIIx			= 7;
gestaltMacIIcx			= 8;
gestaltMacSE030			= 9;
gestaltPortable			= 10;
gestaltMacIIci			= 11;
gestaltMacIIfx			= 13;
gestaltMacClassic		= 17;
gestaltMacIIsi			= 18;
gestaltMacLC			= 19;
gestaltQuadra900		= 20;
gestaltPowerBook170		= 21;
gestaltQuadra700		= 22;
gestaltClassicII		= 23;
gestaltPowerBook100		= 24;
gestaltPowerBook140		= 25;
gestaltQuadra950		= 26;
gestaltMacLCIII			= 27;
gestaltPowerBookDuo210	= 29;
gestaltCentris650		= 30;
gestaltPowerBookDuo230	= 32;
gestaltPowerBook180		= 33;
gestaltPowerBook160		= 34;
gestaltQuadra800		= 35;
gestaltMacLCII			= 37;
gestaltPowerBookDuo250	= 38;
gestaltMacIIvx			= 45;
gestaltColorClassic		= 49;
gestaltPowerbook180c	= 50;
gestaltCentris610		= 52;
gestaltPowerBook145		= 54;
gestaltLC520			= 56;
gestaltCentris660AV		= 60;
gestaltPowerBookDuo270C = 77;
gestaltQuadra840AV		= 78;

gestaltMachineIcon = 'micn';            { machine icon }
gestaltROMSize = 'rom ';                { rom size }
gestaltROMVersion = 'romv';             { rom version }
gestaltSystemVersion = 'sysv';          { system version}

FUNCTION Gestalt(selector: OSType;VAR response: LONGINT): OSErr;
FUNCTION NewGestalt(selector: OSType;gestaltFunction: ProcPtr): OSErr;
FUNCTION ReplaceGestalt(selector: OSType;gestaltFunction: ProcPtr;VAR oldGestaltFunction: ProcPtr): OSErr;


{$ENDC}    { UsingGestaltEqu }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}

