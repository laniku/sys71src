/*
	File:		LowMem.h
	
	Contains:	Prototypes for low memory accessor functions
	
	Written by:	Dean Yu and Fred Monroe
	
	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.
	
	Change History (most recent first):
	
	   <SM2>	 12/1/93	JDR		update from Reality
		 <6>	 12/1/93	JDR		ResLoad is a Byte, not a word, and it's treated as a Boolean.
		 <5>	  8/2/93	DTY		Sync up with NuReality again.
		 <4>	  7/8/93	JSM		TimeSCSIDB is at $B24, not $DA6.
		 <3>	  7/7/93	JSM		MenuCInfo is at $D50, not $D5C.
		 <2>	 6/30/93	JSM		Make macro versions of LMGetDAStrings and LMSetDAStrings
									parallel to the function definitions. I'm assuming a 0 base
									(i.e. the param text strings are indexed 0 to 3, not 1 to 4).
		 <1>	 6/25/93	DTY		first checked in

	NuReality Change History:
	
		 <4>	 6/24/93	EPT		<EPT, JRG> Moved low-mem macros from various other public
									headers into this file and added LM accessor macros for
									platforms that don’t use code fragments.
		 <3>	 6/10/93	jrc		(with DTY) Fix some naming problems.
		 <2>	 6/10/93	jrc		(with JCM) Split into public and private.

	To Do:
	
		Go through and make sure we're handling getting/setting low memory arrays correctly, in both
		the function and macro cases.
*/


#ifndef __LOWMEM__
#define __LOWMEM__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __CONTROLS__
#include <Controls.h>
#endif

#ifndef __EVENTS__
#include <Events.h>
#endif

#ifndef __FILES__
#include <Files.h>
#endif

#ifndef __FONTS__
#include <Fonts.h>
#endif

#ifndef __MEMORY__
#include <Memory.h>
#endif

#ifndef __MENUS__
#include <Menus.h>
#endif

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif

#ifndef __WINDOWS__
#include <Windows.h>
#endif 

#ifdef __cplusplus
extern "C" {
#endif

#if USESCODEFRAGMENTS

extern short LMGetScrVRes(void);
extern void LMSetScrVRes(short ScrVResValue);
extern short LMGetScrHRes(void);
extern void LMSetScrHRes(short ScrHResValue);
extern Ptr LMGetMemTop(void);
extern void LMSetMemTop(Ptr MemTopValue);
extern Ptr LMGetBufPtr(void);
extern void LMSetBufPtr(Ptr BufPtrValue);
extern Ptr LMGetHeapEnd(void);
extern void LMSetHeapEnd(Ptr HeapEndValue);
extern THz LMGetTheZone(void);
extern void LMSetTheZone(THz TheZoneValue);
extern Ptr LMGetUTableBase(void);
extern void LMSetUTableBase(Ptr UTableBaseValue);
extern unsigned char LMGetCPUFlag(void);
extern void LMSetCPUFlag(unsigned char CPUFlagValue);
extern Ptr LMGetApplLimit(void);
extern void LMSetApplLimit(Ptr ApplLimitValue);
extern short LMGetSysEvtMask(void);
extern void LMSetSysEvtMask(short SysEvtMaskValue);
extern QHdrPtr LMGetEventQueue(void);
extern void LMSetEventQueue(QHdrPtr EventQueueValue);
extern long LMGetRndSeed(void);
extern void LMSetRndSeed(long RndSeedValue);
extern unsigned char LMGetSEvtEnb(void);
extern void LMSetSEvtEnb(unsigned char SEvtEnbValue);
extern QHdrPtr LMGetVBLQueue(void);
extern void LMSetVBLQueue(QHdrPtr VBLQueueValue);
extern long LMGetTicks(void);
extern void LMSetTicks(long TicksValue);
extern short LMGetKeyThresh(void);
extern void LMSetKeyThresh(short KeyThreshValue);
extern short LMGetKeyRepThresh(void);
extern void LMSetKeyRepThresh(short KeyRepThreshValue);
extern UniversalProcPtr LMGetLvl2DT(short vectorNumber);
extern void LMSetLvl2DT(UniversalProcPtr Lvl2DTValue, short vectorNumber);
extern Ptr LMGetVIA(void);
extern void LMSetVIA(Ptr VIAValue);
extern Ptr LMGetSCCRd(void);
extern void LMSetSCCRd(Ptr SCCRdValue);
extern Ptr LMGetSCCWr(void);
extern void LMSetSCCWr(Ptr SCCWrValue);
extern Ptr LMGetScratch20(void);
extern void LMSetScratch20(Ptr Scratch20Value);
extern SysPPtr LMGetSPValid(void);
extern void LMSetSPValid(unsigned char SPValidValue);
extern unsigned char LMGetSPATalkA(void);
extern void LMSetSPATalkA(unsigned char SPATalkAValue);
extern unsigned char LMGetSPATalkB(void);
extern void LMSetSPATalkB(unsigned char SPATalkBValue);
extern unsigned char LMGetSPConfig(void);
extern void LMSetSPConfig(unsigned char SPConfigValue);
extern short LMGetSPPortA(void);
extern void LMSetSPPortA(short SPPortAValue);
extern short LMGetSPPortB(void);
extern void LMSetSPPortB(short SPPortBValue);
extern long LMGetSPAlarm(void);
extern void LMSetSPAlarm(long SPAlarmValue);
extern short LMGetSPFont(void);
extern void LMSetSPFont(short SPFontValue);
extern unsigned char LMGetSPKbd(void);
extern void LMSetSPKbd(unsigned char SPKbdValue);
extern unsigned char LMGetSPPrint(void);
extern void LMSetSPPrint(unsigned char SPPrintValue);
extern unsigned char LMGetSPVolCtl(void);
extern void LMSetSPVolCtl(unsigned char SPVolCtlValue);
extern unsigned char LMGetSPClikCaret(void);
extern void LMSetSPClikCaret(unsigned char SPClikCaretValue);
extern unsigned char LMGetSPMisc2(void);
extern void LMSetSPMisc2(unsigned char SPMisc2Value);
extern long LMGetTime(void);
extern void LMSetTime(long TimeValue);
extern short LMGetBootDrive(void);
extern void LMSetBootDrive(short BootDriveValue);
extern short LMGetSFSaveDisk(void);
extern void LMSetSFSaveDisk(short SFSaveDiskValue);
extern short LMGetKbdLast(void);
extern void LMSetKbdLast(short KbdLastValue);
extern unsigned char LMGetKbdType(void);
extern void LMSetKbdType(unsigned char KbdTypeValue);
extern short LMGetMemErr(void);
extern void LMSetMemErr(short MemErrValue);
extern unsigned char LMGetSdVolume(void);
extern void LMSetSdVolume(unsigned char SdVolumeValue);
extern Ptr LMGetSoundPtr(void);
extern void LMSetSoundPtr(Ptr SoundPtrValue);
extern Ptr LMGetSoundBase(void);
extern void LMSetSoundBase(Ptr SoundBaseValue);
extern unsigned char LMGetSoundLevel(void);
extern void LMSetSoundLevel(unsigned char SoundLevelValue);
extern short LMGetCurPitch(void);
extern void LMSetCurPitch(short CurPitchValue);
extern short LMGetROM85(void);
extern void LMSetROM85(short ROM85Value);
extern unsigned char LMGetPortBUse(void);
extern void LMSetPortBUse(unsigned char PortBUseValue);
extern THz LMGetSysZone(void);
extern void LMSetSysZone(THz SysZoneValue);
extern THz LMGetApplZone(void);
extern void LMSetApplZone(THz ApplZoneValue);
extern Ptr LMGetROMBase(void);
extern void LMSetROMBase(Ptr ROMBaseValue);
extern Ptr LMGetRAMBase(void);
extern void LMSetRAMBase(Ptr RAMBaseValue);
extern Ptr LMGetDSAlertTab(void);
extern void LMSetDSAlertTab(Ptr DSAlertTabValue);
extern UniversalProcPtr LMGetExtStsDT(short vectorNumber);
extern void LMSetExtStsDT(UniversalProcPtr ExtStsDTValue, short vectorNumber);
extern Ptr LMGetABusVars(void);
extern void LMSetABusVars(Ptr ABusVarsValue);
extern StringPtr LMGetFinderName(void);
extern void LMSetFinderName(StringPtr FinderNameValue);
extern long LMGetDoubleTime(void);
extern void LMSetDoubleTime(long DoubleTimeValue);
extern long LMGetCaretTime(void);
extern void LMSetCaretTime(long CaretTimeValue);
extern unsigned char LMGetScrDmpEnb(void);
extern void LMSetScrDmpEnb(unsigned char ScrDmpEnbValue);
extern long LMGetBufTgFNum(void);
extern void LMSetBufTgFNum(long BufTgFNumValue);
extern short LMGetBufTgFFlg(void);
extern void LMSetBufTgFFlg(short BufTgFFlgValue);
extern short LMGetBufTgFBkNum(void);
extern void LMSetBufTgFBkNum(short BufTgFBkNumValue);
extern long LMGetBufTgDate(void);
extern void LMSetBufTgDate(long BufTgDateValue);
extern QHdrPtr LMGetDrvQHdr(void);
extern void LMSetDrvQHdr(QHdrPtr DrvQHdrValue);
extern long LMGetLo3Bytes(void);
extern void LMSetLo3Bytes(long Lo3BytesValue);
extern long LMGetMinStack(void);
extern void LMSetMinStack(long MinStackValue);
extern long LMGetDefltStack(void);
extern void LMSetDefltStack(long DefltStackValue);
extern Handle LMGetGZRootHnd(void);
extern void LMSetGZRootHnd(Handle GZRootHndValue);
extern Ptr LMGetFCBSPtr(void);
extern void LMSetFCBSPtr(Ptr FCBSPtrValue);
extern Ptr LMGetDefVCBPtr(void);
extern void LMSetDefVCBPtr(Ptr DefVCBPtrValue);
extern QHdrPtr LMGetVCBQHdr(void);
extern void LMSetVCBQHdr(QHdrPtr VCBQHdrValue);
extern long LMGetCurDirStore(void);
extern void LMSetCurDirStore(long CurDirStoreValue);
extern UniversalProcPtr LMGetToExtFS(void);
extern void LMSetToExtFS(UniversalProcPtr ToExtFSValue);
extern short LMGetFSFCBLen(void);
extern void LMSetFSFCBLen(short FSFCBLenValue);
extern Rect LMGetDSAlertRect(void);
extern void LMSetDSAlertRect(Rect DSAlertRectValue);
extern Ptr LMGetScrnBase(void);
extern void LMSetScrnBase(Ptr ScrnBaseValue);
extern GDHandle LMGetMainDevice(void);
extern void LMSetMainDevice(GDHandle MainDeviceValue);
extern GDHandle LMGetDeviceList(void);
extern void LMSetDeviceList(GDHandle DeviceListValue);
extern Ptr LMGetQDColors(void);
extern void LMSetQDColors(Ptr QDColorsValue);
extern Handle LMGetWidthListHand(void);
extern void LMSetWidthListHand(Handle WidthListHandValue);
extern short LMGetJournalRef(void);
extern void LMSetJournalRef(short JournalRefValue);
extern short LMGetCrsrThresh(void);
extern void LMSetCrsrThresh(short CrsrThreshValue);
extern UniversalProcPtr LMGetJFetch(void);
extern void LMSetJFetch(UniversalProcPtr JFetchValue);
extern UniversalProcPtr LMGetJStash(void);
extern void LMSetJStash(UniversalProcPtr JStashValue);
extern UniversalProcPtr LMGetJIODone(void);
extern void LMSetJIODone(UniversalProcPtr JIODoneValue);
extern short LMGetCurApRefNum(void);
extern void LMSetCurApRefNum(short CurApRefNumValue);
extern Ptr LMGetCurrentA5(void);
extern void LMSetCurrentA5(Ptr CurrentA5Value);
extern Ptr LMGetCurStackBase(void);
extern void LMSetCurStackBase(Ptr CurStackBaseValue);
extern StringPtr LMGetCurApName(void);
extern void LMSetCurApName(StringPtr CurApNameValue);
extern short LMGetCurJTOffset(void);
extern void LMSetCurJTOffset(short CurJTOffsetValue);
extern short LMGetCurPageOption(void);
extern void LMSetCurPageOption(short CurPageOptionValue);
extern unsigned char LMGetHiliteMode(void);
extern void LMSetHiliteMode(unsigned char HiliteModeValue);
extern short LMGetPrintErr(void);
extern void LMSetPrintErr(short PrintErrValue);
extern long LMGetScrapSize(void);
extern void LMSetScrapSize(long ScrapSizeValue);
extern Handle LMGetScrapHandle(void);
extern void LMSetScrapHandle(Handle ScrapHandleValue);
extern short LMGetScrapCount(void);
extern void LMSetScrapCount(short ScrapCountValue);
extern short LMGetScrapState(void);
extern void LMSetScrapState(short ScrapStateValue);
extern StringPtr LMGetScrapName(void);
extern void LMSetScrapName(StringPtr ScrapNameValue);
extern Handle LMGetROMFont0(void);
extern void LMSetROMFont0(Handle ROMFont0Value);
extern short LMGetApFontID(void);
extern void LMSetApFontID(short ApFontIDValue);
extern Ptr LMGetToolScratch(void);
extern void LMSetToolScratch(Ptr ToolScratchValue);
extern WindowPeek LMGetWindowList(void);
extern void LMSetWindowList(WindowPeek WindowListValue);
extern short LMGetSaveUpdate(void);
extern void LMSetSaveUpdate(short SaveUpdateValue);
extern short LMGetPaintWhite(void);
extern void LMSetPaintWhite(short PaintWhiteValue);
extern GrafPtr LMGetWMgrPort(void);
extern void LMSetWMgrPort(GrafPtr WMgrPortValue);
extern RgnHandle LMGetOldStructure(void);
extern void LMSetOldStructure(RgnHandle OldStructureValue);
extern RgnHandle LMGetOldContent(void);
extern void LMSetOldContent(RgnHandle OldContentValue);
extern RgnHandle LMGetGrayRgn(void);
extern void LMSetGrayRgn(RgnHandle GrayRgnValue);
extern RgnHandle LMGetSaveVisRgn(void);
extern void LMSetSaveVisRgn(RgnHandle SaveVisRgnValue);
extern UniversalProcPtr LMGetDragHook(void);
extern void LMSetDragHook(UniversalProcPtr DragHookValue);
extern long LMGetOneOne(void);
extern void LMSetOneOne(long OneOneValue);
extern long LMGetMinusOne(void);
extern void LMSetMinusOne(long MinusOneValue);
extern Handle LMGetMenuList(void);
extern void LMSetMenuList(Handle MenuListValue);
extern short LMGetMBarEnable(void);
extern void LMSetMBarEnable(short MBarEnableValue);
extern short LMGetMenuFlash(void);
extern void LMSetMenuFlash(short MenuFlashValue);
extern short LMGetTheMenu(void);
extern void LMSetTheMenu(short TheMenuValue);
extern UniversalProcPtr LMGetMBarHook(void);
extern void LMSetMBarHook(UniversalProcPtr MBarHookValue);
extern UniversalProcPtr LMGetMenuHook(void);
extern void LMSetMenuHook(UniversalProcPtr MenuHookValue);
extern Pattern LMGetDragPattern(void);
extern void LMSetDragPattern(Pattern DragPatternValue);
extern Pattern LMGetDeskPattern(void);
extern void LMSetDeskPattern(Pattern DeskPatternValue);
extern Handle LMGetTopMapHndl(void);
extern void LMSetTopMapHndl(Handle TopMapHndlValue);
extern Handle LMGetSysMapHndl(void);
extern void LMSetSysMapHndl(Handle SysMapHndlValue);
extern short LMGetSysMap(void);
extern void LMSetSysMap(short SysMapValue);
extern short LMGetCurMap(void);
extern void LMSetCurMap(short CurMapValue);
extern Boolean LMGetResLoad(void);
extern void LMSetResLoad(Boolean ResLoadValue);
extern short LMGetResErr(void);
extern void LMSetResErr(short ResErrValue);
extern unsigned char LMGetFScaleDisable(void);
extern void LMSetFScaleDisable(unsigned char FScaleDisableValue);
extern WindowPeek LMGetCurActivate(void);
extern void LMSetCurActivate(WindowPeek CurActivateValue);
extern WindowPeek LMGetCurDeactive(void);
extern void LMSetCurDeactive(WindowPeek CurDeactiveValue);
extern UniversalProcPtr LMGetDeskHook(void);
extern void LMSetDeskHook(UniversalProcPtr DeskHookValue);
extern UniversalProcPtr LMGetTEDoText(void);
extern void LMSetTEDoText(UniversalProcPtr TEDoTextValue);
extern UniversalProcPtr LMGetTERecal(void);
extern void LMSetTERecal(UniversalProcPtr TERecalValue);
extern Ptr LMGetApplScratch(void);
extern void LMSetApplScratch(Ptr ApplScratchValue);
extern WindowPeek LMGetGhostWindow(void);
extern void LMSetGhostWindow(WindowPeek GhostWindowValue);
extern UniversalProcPtr LMGetResumeProc(void);
extern void LMSetResumeProc(UniversalProcPtr ResumeProcValue);
extern short LMGetANumber(void);
extern void LMSetANumber(short ANumberValue);
extern short LMGetACount(void);
extern void LMSetACount(short ACountValue);
extern UniversalProcPtr LMGetDABeeper(void);
extern void LMSetDABeeper(UniversalProcPtr DABeeperValue);
extern StringHandle LMGetDAStrings(short whichString);
extern void LMSetDAStrings(StringHandle DAStringsValue, short whichString);
extern short LMGetTEScrpLength(void);
extern void LMSetTEScrpLength(short TEScrpLengthValue);
extern Handle LMGetTEScrpHandle(void);
extern void LMSetTEScrpHandle(Handle TEScrpHandleValue);
extern StringPtr LMGetSysResName(void);
extern void LMSetSysResName(StringPtr SysResNameValue);
extern Handle LMGetAppParmHandle(void);
extern void LMSetAppParmHandle(Handle AppParmHandleValue);
extern short LMGetDSErrCode(void);
extern void LMSetDSErrCode(short DSErrCodeValue);
extern UniversalProcPtr LMGetResErrProc(void);
extern void LMSetResErrProc(UniversalProcPtr ResErrProcValue);
extern short LMGetDlgFont(void);
extern void LMSetDlgFont(short DlgFontValue);
extern Ptr LMGetWidthPtr(void);
extern void LMSetWidthPtr(Ptr WidthPtrValue);
extern Ptr LMGetATalkHk2(void);
extern void LMSetATalkHk2(Ptr ATalkHk2Value);
extern short LMGetTopMenuItem(void);
extern void LMSetTopMenuItem(short TopMenuItemValue);
extern short LMGetAtMenuBottom(void);
extern void LMSetAtMenuBottom(short AtMenuBottomValue);
extern Handle LMGetWidthTabHandle(void);
extern void LMSetWidthTabHandle(Handle WidthTabHandleValue);
extern long LMGetMenuDisable(void);
extern void LMSetMenuDisable(long MenuDisableValue);
extern unsigned char LMGetROMMapInsert(void);
extern void LMSetROMMapInsert(unsigned char ROMMapInsertValue);
extern unsigned char LMGetTmpResLoad(void);
extern void LMSetTmpResLoad(unsigned char TmpResLoadValue);
extern Ptr LMGetIntlSpec(void);
extern void LMSetIntlSpec(Ptr IntlSpecValue);
extern unsigned char LMGetWordRedraw(void);
extern void LMSetWordRedraw(unsigned char WordRedrawValue);
extern short LMGetSysFontFam(void);
extern void LMSetSysFontFam(short SysFontFamValue);
extern short LMGetSysFontSize(void);
extern void LMSetSysFontSize(short SysFontSizeValue);
extern short LMGetMBarHeight(void);
extern void LMSetMBarHeight(short MBarHeightValue);
extern short LMGetTESysJust(void);
extern void LMSetTESysJust(short TESysJustValue);
extern Handle LMGetLastFOND(void);
extern void LMSetLastFOND(Handle LastFONDValue);
extern unsigned char LMGetFractEnable(void);
extern void LMSetFractEnable(unsigned char FractEnableValue);
extern unsigned char LMGetMMU32Bit(void);
extern void LMSetMMU32Bit(unsigned char MMU32BitValue);
extern GDHandle LMGetTheGDevice(void);
extern void LMSetTheGDevice(GDHandle TheGDeviceValue);
extern AuxWinHandle LMGetAuxWinHead(void);
extern void LMSetAuxWinHead(AuxWinHandle AuxWinHeadValue);
extern short LMGetTimeDBRA(void);
extern void LMSetTimeDBRA(short TimeDBRAValue);
extern short LMGetTimeSCCDB(void);
extern void LMSetTimeSCCDB(short TimeSCCDBValue);
extern UniversalProcPtr LMGetJVBLTask(void);
extern void LMSetJVBLTask(UniversalProcPtr JVBLTaskValue);
extern Handle LMGetSynListHandle(void);
extern void LMSetSynListHandle(Handle SynListHandleValue);
extern MCTableHandle LMGetMenuCInfo(void);
extern void LMSetMenuCInfo(MCTableHandle MenuCInfoValue);
extern QHdrPtr LMGetDTQueue(void);
extern void LMSetDTQueue(QHdrPtr DTQueueValue);
extern UniversalProcPtr LMGetJDTInstall(void);
extern void LMSetJDTInstall(UniversalProcPtr JDTInstallValue);
extern RGBColor *LMGetHiliteRGB(void);
extern void LMSetHiliteRGB(RGBColor*);
extern short LMGetTimeSCSIDB(void);
extern void LMSetTimeSCSIDB(short TimeSCSIDBValue);
extern QElemPtr LMGetFSQHead(void);

#else

#define LMGetScrVRes()	(* (short *) 0x0102)
#define LMSetScrVRes(ScrVResValue)	((* (short *) 0x0102) = ScrVResValue)
#define LMGetScrHRes()	(* (short *) 0x0104)
#define LMSetScrHRes(ScrHResValue)	((* (short *) 0x0104) = ScrHResValue)
#define LMGetMemTop()	(* (Ptr *) 0x0108)
#define LMSetMemTop(MemTopValue)	((* (Ptr *) 0x0108) = MemTopValue)
#define LMGetBufPtr()	(* (Ptr *) 0x010C)
#define LMSetBufPtr(BufPtrValue)	((* (Ptr *) 0x010C) = BufPtrValue)
#define LMGetHeapEnd()	(* (Ptr *) 0x0114)
#define LMSetHeapEnd(HeapEndValue)	((* (Ptr *) 0x0114) = HeapEndValue)
#define LMGetTheZone()	(* (THz *) 0x0118)
#define LMSetTheZone(TheZoneValue)	((* (THz *) 0x0118) = TheZoneValue)
#define LMGetUTableBase()	(* (Ptr *) 0x011C)
#define LMSetUTableBase(UTableBaseValue)	((* (Ptr *) 0x011C) = UTableBaseValue)
#define LMGetCPUFlag()	(* (unsigned char *) 0x012F)
#define LMSetCPUFlag(CPUFlagValue)	((* (unsigned char *) 0x012F) = CPUFlagValue)
#define LMGetApplLimit()	(* (Ptr *) 0x0130)
#define LMSetApplLimit(ApplLimitValue)	((* (Ptr *) 0x0130) = ApplLimitValue)
#define LMGetSysEvtMask()	(* (short *) 0x0144)
#define LMSetSysEvtMask(SysEvtMaskValue)	((* (short *) 0x0144) = SysEvtMaskValue)
#define LMGetEventQueue()	( (QHdrPtr) 0x014A)
#define LMSetEventQueue(EventQueueValue)	((* (QHdrPtr) 0x014A) = *(QHdrPtr)EventQueueValue)
#define LMGetRndSeed()	(* (long *) 0x0156)
#define LMSetRndSeed(RndSeedValue)	((* (long *) 0x0156) = RndSeedValue)
#define LMGetSEvtEnb()	(* (unsigned char *) 0x015C)
#define LMSetSEvtEnb(SEvtEnbValue)	((* (unsigned char *) 0x015C) = SEvtEnbValue)
#define LMGetVBLQueue()	( (QHdrPtr) 0x0160)
#define LMSetVBLQueue(VBLQueueValue)	((* (QHdrPtr) 0x0160) = *(QHdrPtr)VBLQueueValue)
#define LMGetTicks()	(* (long *) 0x016A)
#define LMSetTicks(TicksValue)	((* (long *) 0x016A) = TicksValue)
#define LMGetKeyThresh()	(* (short *) 0x018E)
#define LMSetKeyThresh(KeyThreshValue)	((* (short *) 0x018E) = KeyThreshValue)
#define LMGetKeyRepThresh()	(* (short *) 0x0190)
#define LMSetKeyRepThresh(KeyRepThreshValue)	((* (short *) 0x0190) = KeyRepThreshValue)
#define LMGetLvl2DT()	(* (UniversalProcPtr *) 0x01B2)
#define LMSetLvl2DT(Lvl2DTValue)	((* (UniversalProcPtr *) 0x01B2) = Lvl2DTValue)
#define LMGetVIA()	(* (Ptr *) 0x01D4)
#define LMSetVIA(VIAValue)	((* (Ptr *) 0x01D4) = VIAValue)
#define LMGetSCCRd()	(* (Ptr *) 0x01D8)
#define LMSetSCCRd(SCCRdValue)	((* (Ptr *) 0x01D8) = SCCRdValue)
#define LMGetSCCWr()	(* (Ptr *) 0x01DC)
#define LMSetSCCWr(SCCWrValue)	((* (Ptr *) 0x01DC) = SCCWrValue)
#define LMGetScratch20()	(* (unsigned char *) 0x01E4)
#define LMSetScratch20(Scratch20Value)	((* (unsigned char *) 0x01E4) = Scratch20Value)
#define LMGetSPValid()	(* (unsigned char *) 0x01F8)
#define LMSetSPValid(SPValidValue)	((* (unsigned char *) 0x01F8) = SPValidValue)
#define LMGetSPATalkA()	(* (unsigned char *) 0x01F9)
#define LMSetSPATalkA(SPATalkAValue)	((* (unsigned char *) 0x01F9) = SPATalkAValue)
#define LMGetSPATalkB()	(* (unsigned char *) 0x01FA)
#define LMSetSPATalkB(SPATalkBValue)	((* (unsigned char *) 0x01FA) = SPATalkBValue)
#define LMGetSPConfig()	(* (unsigned char *) 0x01FB)
#define LMSetSPConfig(SPConfigValue)	((* (unsigned char *) 0x01FB) = SPConfigValue)
#define LMGetSPPortA()	(* (short *) 0x01FC)
#define LMSetSPPortA(SPPortAValue)	((* (short *) 0x01FC) = SPPortAValue)
#define LMGetSPPortB()	(* (short *) 0x01FE)
#define LMSetSPPortB(SPPortBValue)	((* (short *) 0x01FE) = SPPortBValue)
#define LMGetSPAlarm()	(* (long *) 0x0200)
#define LMSetSPAlarm(SPAlarmValue)	((* (long *) 0x0200) = SPAlarmValue)
#define LMGetSPFont()	(* (short *) 0x0204)
#define LMSetSPFont(SPFontValue)	((* (short *) 0x0204) = SPFontValue)
#define LMGetSPKbd()	(* (unsigned char *) 0x0206)
#define LMSetSPKbd(SPKbdValue)	((* (unsigned char *) 0x0206) = SPKbdValue)
#define LMGetSPPrint()	(* (unsigned char *) 0x0207)
#define LMSetSPPrint(SPPrintValue)	((* (unsigned char *) 0x0207) = SPPrintValue)
#define LMGetSPVolCtl()	(* (unsigned char *) 0x0208)
#define LMSetSPVolCtl(SPVolCtlValue)	((* (unsigned char *) 0x0208) = SPVolCtlValue)
#define LMGetSPClikCaret()	(* (unsigned char *) 0x0209)
#define LMSetSPClikCaret(SPClikCaretValue)	((* (unsigned char *) 0x0209) = SPClikCaretValue)
#define LMGetSPMisc2()	(* (unsigned char *) 0x020B)
#define LMSetSPMisc2(SPMisc2Value)	((* (unsigned char *) 0x020B) = SPMisc2Value)
#define LMGetTime()	(* (long *) 0x020C)
#define LMSetTime(TimeValue)	((* (long *) 0x020C) = TimeValue)
#define LMGetBootDrive()	(* (short *) 0x0210)
#define LMSetBootDrive(BootDriveValue)	((* (short *) 0x0210) = BootDriveValue)
#define LMGetSFSaveDisk()	(* (short *) 0x0214)
#define LMSetSFSaveDisk(SFSaveDiskValue)	((* (short *) 0x0214) = SFSaveDiskValue)
#define LMGetKbdLast()	(* (short *) 0x0218)
#define LMSetKbdLast(KbdLastValue)	((* (short *) 0x0218) = KbdLastValue)
#define LMGetKbdType()	(* (unsigned char *) 0x021E)
#define LMSetKbdType(KbdTypeValue)	((* (unsigned char *) 0x021E) = KbdTypeValue)
#define LMGetMemErr()	(* (short *) 0x0220)
#define LMSetMemErr(MemErrValue)	((* (short *) 0x0220) = MemErrValue)
#define LMGetSdVolume()	(* (unsigned char *) 0x0260)
#define LMSetSdVolume(SdVolumeValue)	((* (unsigned char *) 0x0260) = SdVolumeValue)
#define LMGetFinder()	(* (unsigned char *) 0x0261)
#define LMSetFinder(FinderValue)	((* (unsigned char *) 0x0261) = FinderValue)
#define LMGetSoundPtr()	(* (Ptr *) 0x0262)
#define LMSetSoundPtr(SoundPtrValue)	((* (Ptr *) 0x0262) = SoundPtrValue)
#define LMGetSoundBase()	(* (Ptr *) 0x0266)
#define LMSetSoundBase(SoundBaseValue)	((* (Ptr *) 0x0266) = SoundBaseValue)
#define LMGetSoundLevel()	(* (unsigned char *) 0x027F)
#define LMSetSoundLevel(SoundLevelValue)	((* (unsigned char *) 0x027F) = SoundLevelValue)
#define LMGetCurPitch()	(* (short *) 0x0280)
#define LMSetCurPitch(CurPitchValue)	((* (short *) 0x0280) = CurPitchValue)
#define LMGetROM85()	(* (short *) 0x028E)
#define LMSetROM85(ROM85Value)	((* (short *) 0x028E) = ROM85Value)
#define LMGetPortBUse()	(* (unsigned char *) 0x0291)
#define LMSetPortBUse(PortBUseValue)	((* (unsigned char *) 0x0291) = PortBUseValue)
#define LMGetSysZone()	(* (THz *) 0x02A6)
#define LMSetSysZone(SysZoneValue)	((* (THz *) 0x02A6) = SysZoneValue)
#define LMGetApplZone()	(* (THz *) 0x02AA)
#define LMSetApplZone(ApplZoneValue)	((* (THz *) 0x02AA) = ApplZoneValue)
#define LMGetROMBase()	(* (Ptr *) 0x02AE)
#define LMSetROMBase(ROMBaseValue)	((* (Ptr *) 0x02AE) = ROMBaseValue)
#define LMGetRAMBase()	(* (Ptr *) 0x02B2)
#define LMSetRAMBase(RAMBaseValue)	((* (Ptr *) 0x02B2) = RAMBaseValue)
#define LMGetDSAlertTab()	(* (Ptr *) 0x02BA)
#define LMSetDSAlertTab(DSAlertTabValue)	((* (Ptr *) 0x02BA) = DSAlertTabValue)
#define LMGetExtStsDT()	(* (UniversalProcPtr *) 0x02BE)
#define LMSetExtStsDT(ExtStsDTValue)	((* (UniversalProcPtr *) 0x02BE) = ExtStsDTValue)
#define LMGetABusVars()	(* (Ptr *) 0x02D8)
#define LMSetABusVars(ABusVarsValue)	((* (Ptr *) 0x02D8) = ABusVarsValue)
#define LMGetFinderName()	(* (Str15 *) 0x02E0)
#define LMSetFinderName(FinderNameValue)	((* (Str15 *) 0x02E0) = FinderNameValue)
#define LMGetDoubleTime()	(* (long *) 0x02F0)
#define LMSetDoubleTime(DoubleTimeValue)	((* (long *) 0x02F0) = DoubleTimeValue)
#define LMGetCaretTime()	(* (long *) 0x02F4)
#define LMSetCaretTime(CaretTimeValue)	((* (long *) 0x02F4) = CaretTimeValue)
#define LMGetScrDmpEnb()	(* (unsigned char *) 0x02F8)
#define LMSetScrDmpEnb(ScrDmpEnbValue)	((* (unsigned char *) 0x02F8) = ScrDmpEnbValue)
#define LMGetBufTgFNum()	(* (long *) 0x02FC)
#define LMSetBufTgFNum(BufTgFNumValue)	((* (long *) 0x02FC) = BufTgFNumValue)
#define LMGetBufTgFFlg()	(* (short *) 0x0300)
#define LMSetBufTgFFlg(BufTgFFlgValue)	((* (short *) 0x0300) = BufTgFFlgValue)
#define LMGetBufTgFBkNum()	(* (short *) 0x0302)
#define LMSetBufTgFBkNum(BufTgFBkNumValue)	((* (short *) 0x0302) = BufTgFBkNumValue)
#define LMGetBufTgDate()	(* (long *) 0x0304)
#define LMSetBufTgDate(BufTgDateValue)	((* (long *) 0x0304) = BufTgDateValue)
#define LMGetDrvQHdr()	( (QHdrPtr) 0x0308)
#define LMSetDrvQHdr(DrvQHdrValue)	((* (QHdrPtr) 0x0308) = *(QHdrPtr)DrvQHdrValue)
#define LMGetLo3Bytes()	(* (long *) 0x031A)
#define LMSetLo3Bytes(Lo3BytesValue)	((* (long *) 0x031A) = Lo3BytesValue)
#define LMGetMinStack()	(* (long *) 0x031E)
#define LMSetMinStack(MinStackValue)	((* (long *) 0x031E) = MinStackValue)
#define LMGetDefltStack()	(* (long *) 0x0322)
#define LMSetDefltStack(DefltStackValue)	((* (long *) 0x0322) = DefltStackValue)
#define LMGetGZRootHnd()	(* (Handle *) 0x0328)
#define LMSetGZRootHnd(GZRootHndValue)	((* (Handle *) 0x0328) = GZRootHndValue)
#define LMGetFCBSPtr()	(* (Ptr *) 0x034E)
#define LMSetFCBSPtr(FCBSPtrValue)	((* (Ptr *) 0x034E) = FCBSPtrValue)
#define LMGetDefVCBPtr()	(* (Ptr *) 0x0352)
#define LMSetDefVCBPtr(DefVCBPtrValue)	((* (Ptr *) 0x0352) = DefVCBPtrValue)
#define LMGetVCBQHdr()	( (QHdrPtr) 0x0356)
#define LMSetVCBQHdr(VCBQHdrValue)	((* (QHdrPtr) 0x0356) = *(QHdrPtr)VCBQHdrValue)
#define LMGetCurDirStore()	(* (long *) 0x0398)
#define LMSetCurDirStore(CurDirStoreValue)	((* (long *) 0x0398) = CurDirStoreValue)
#define LMGetToExtFS()	(* (UniversalProcPtr *) 0x03F2)
#define LMSetToExtFS(ToExtFSValue)	((* (UniversalProcPtr *) 0x03F2) = ToExtFSValue)
#define LMGetFSFCBLen()	(* (short *) 0x03F6)
#define LMSetFSFCBLen(FSFCBLenValue)	((* (short *) 0x03F6) = FSFCBLenValue)
#define LMGetDSAlertRect()	(* (Rect *) 0x03F8)
#define LMSetDSAlertRect(DSAlertRectValue)	((* (Rect *) 0x03F8) = DSAlertRectValue)
#define LMGetScrnBase()	(* (Ptr *) 0x0824)
#define LMSetScrnBase(ScrnBaseValue)	((* (Ptr *) 0x0824) = ScrnBaseValue)
#define LMGetMainDevice()	(* (GDHandle *) 0x08A4)
#define LMSetMainDevice(MainDeviceValue)	((* (GDHandle *) 0x08A4) = MainDeviceValue)
#define LMGetDeviceList()	(* (GDHandle *) 0x08A8)
#define LMSetDeviceList(DeviceListValue)	((* (GDHandle *) 0x08A8) = DeviceListValue)
#define LMGetQDColors()	(* (Ptr *) 0x08B0)
#define LMSetQDColors(QDColorsValue)	((* (Ptr *) 0x08B0) = QDColorsValue)
#define LMGetWidthListHand()	(* (Handle *) 0x08E4)
#define LMSetWidthListHand(WidthListHandValue)	((* (Handle *) 0x08E4) = WidthListHandValue)
#define LMGetJournalRef()	(* (short *) 0x08E8)
#define LMSetJournalRef(JournalRefValue)	((* (short *) 0x08E8) = JournalRefValue)
#define LMGetCrsrThresh()	(* (short *) 0x08EC)
#define LMSetCrsrThresh(CrsrThreshValue)	((* (short *) 0x08EC) = CrsrThreshValue)
#define LMGetJFetch()	(* (UniversalProcPtr *) 0x08F4)
#define LMSetJFetch(JFetchValue)	((* (UniversalProcPtr *) 0x08F4) = JFetchValue)
#define LMGetJStash()	(* (UniversalProcPtr *) 0x08F8)
#define LMSetJStash(JStashValue)	((* (UniversalProcPtr *) 0x08F8) = JStashValue)
#define LMGetJIODone()	(* (UniversalProcPtr *) 0x08FC)
#define LMSetJIODone(JIODoneValue)	((* (UniversalProcPtr *) 0x08FC) = JIODoneValue)
#define LMGetCurApRefNum()	(* (short *) 0x0900)
#define LMSetCurApRefNum(CurApRefNumValue)	((* (short *) 0x0900) = CurApRefNumValue)
#define LMGetCurrentA5()	(* (Ptr *) 0x0904)
#define LMSetCurrentA5(CurrentA5Value)	((* (Ptr *) 0x0904) = CurrentA5Value)
#define LMGetCurStackBase()	(* (Ptr *) 0x0908)
#define LMSetCurStackBase(CurStackBaseValue)	((* (Ptr *) 0x0908) = CurStackBaseValue)
#define LMGetCurApName()	(* (Str31 *) 0x0910)
#define LMSetCurApName(CurApNameValue)	((* (Str31 *) 0x0910) = CurApNameValue)
#define LMGetCurJTOffset()	(* (short *) 0x0934)
#define LMSetCurJTOffset(CurJTOffsetValue)	((* (short *) 0x0934) = CurJTOffsetValue)
#define LMGetCurPageOption()	(* (short *) 0x0936)
#define LMSetCurPageOption(CurPageOptionValue)	((* (short *) 0x0936) = CurPageOptionValue)
#define LMGetHiliteMode()	(* (unsigned char *) 0x0938)
#define LMSetHiliteMode(HiliteModeValue)	((* (unsigned char *) 0x0938) = HiliteModeValue)
#define LMGetPrintErr()	(* (short *) 0x0944)
#define LMSetPrintErr(PrintErrValue)	((* (short *) 0x0944) = PrintErrValue)
#define LMGetScrapSize()	(* (long *) 0x0960)
#define LMSetScrapSize(ScrapSizeValue)	((* (long *) 0x0960) = ScrapSizeValue)
#define LMGetScrapHandle()	(* (Handle *) 0x0964)
#define LMSetScrapHandle(ScrapHandleValue)	((* (Handle *) 0x0964) = ScrapHandleValue)
#define LMGetScrapCount()	(* (short *) 0x0968)
#define LMSetScrapCount(ScrapCountValue)	((* (short *) 0x0968) = ScrapCountValue)
#define LMGetScrapState()	(* (short *) 0x096A)
#define LMSetScrapState(ScrapStateValue)	((* (short *) 0x096A) = ScrapStateValue)
#define LMGetScrapName()	(* (StringPtr *) 0x096C)
#define LMSetScrapName(ScrapNameValue)	((* (StringPtr *) 0x096C) = ScrapNameValue)
#define LMGetROMFont0()	(* (Handle *) 0x0980)
#define LMSetROMFont0(ROMFont0Value)	((* (Handle *) 0x0980) = ROMFont0Value)
#define LMGetApFontID()	(* (short *) 0x0984)
#define LMSetApFontID(ApFontIDValue)	((* (short *) 0x0984) = ApFontIDValue)
#define LMGetToolScratch()	(* (unsigned char *) 0x09CE)
#define LMSetToolScratch(ToolScratchValue)	((* (unsigned char *) 0x09CE) = ToolScratchValue)
#define LMGetWindowList()	(* (WindowPeek *) 0x09D6)
#define LMSetWindowList(WindowListValue)	((* (WindowPeek *) 0x09D6) = WindowListValue)
#define LMGetSaveUpdate()	(* (short *) 0x09DA)
#define LMSetSaveUpdate(SaveUpdateValue)	((* (short *) 0x09DA) = SaveUpdateValue)
#define LMGetPaintWhite()	(* (short *) 0x09DC)
#define LMSetPaintWhite(PaintWhiteValue)	((* (short *) 0x09DC) = PaintWhiteValue)
#define LMGetWMgrPort()	(* (GrafPtr *) 0x09DE)
#define LMSetWMgrPort(WMgrPortValue)	((* (GrafPtr *) 0x09DE) = WMgrPortValue)
#define LMGetOldStructure()	(* (RgnHandle *) 0x09E6)
#define LMSetOldStructure(OldStructureValue)	((* (RgnHandle *) 0x09E6) = OldStructureValue)
#define LMGetOldContent()	(* (RgnHandle *) 0x09EA)
#define LMSetOldContent(OldContentValue)	((* (RgnHandle *) 0x09EA) = OldContentValue)
#define LMGetGrayRgn()	(* (RgnHandle *) 0x09EE)
#define LMSetGrayRgn(GrayRgnValue)	((* (RgnHandle *) 0x09EE) = GrayRgnValue)
#define LMGetSaveVisRgn()	(* (RgnHandle *) 0x09F2)
#define LMSetSaveVisRgn(SaveVisRgnValue)	((* (RgnHandle *) 0x09F2) = SaveVisRgnValue)
#define LMGetDragHook()	(* (UniversalProcPtr *) 0x09F6)
#define LMSetDragHook(DragHookValue)	((* (UniversalProcPtr *) 0x09F6) = DragHookValue)
#define LMGetOneOne()	(* (long *) 0x0A02)
#define LMSetOneOne(OneOneValue)	((* (long *) 0x0A02) = OneOneValue)
#define LMGetMinusOne()	(* (long *) 0x0A06)
#define LMSetMinusOne(MinusOneValue)	((* (long *) 0x0A06) = MinusOneValue)
#define LMGetMenuList()	(* (Handle *) 0x0A1C)
#define LMSetMenuList(MenuListValue)	((* (Handle *) 0x0A1C) = MenuListValue)
#define LMGetMBarEnable()	(* (short *) 0x0A20)
#define LMSetMBarEnable(MBarEnableValue)	((* (short *) 0x0A20) = MBarEnableValue)
#define LMGetMenuFlash()	(* (short *) 0x0A24)
#define LMSetMenuFlash(MenuFlashValue)	((* (short *) 0x0A24) = MenuFlashValue)
#define LMGetTheMenu()	(* (short *) 0x0A26)
#define LMSetTheMenu(TheMenuValue)	((* (short *) 0x0A26) = TheMenuValue)
#define LMGetMBarHook()	(* (UniversalProcPtr *) 0x0A2C)
#define LMSetMBarHook(MBarHookValue)	((* (UniversalProcPtr *) 0x0A2C) = MBarHookValue)
#define LMGetMenuHook()	(* (UniversalProcPtr *) 0x0A30)
#define LMSetMenuHook(MenuHookValue)	((* (UniversalProcPtr *) 0x0A30) = MenuHookValue)
#define LMGetDragPattern()	(* (Pattern *) 0x0A34)
#define LMSetDragPattern(DragPatternValue)	((* (Pattern *) 0x0A34) = DragPatternValue)
#define LMGetDeskPattern()	(* (Pattern *) 0x0A3C)
#define LMSetDeskPattern(DeskPatternValue)	((* (Pattern *) 0x0A3C) = DeskPatternValue)
#define LMGetTopMapHndl()	(* (Handle *) 0x0A50)
#define LMSetTopMapHndl(TopMapHndlValue)	((* (Handle *) 0x0A50) = TopMapHndlValue)
#define LMGetSysMapHndl()	(* (Handle *) 0x0A54)
#define LMSetSysMapHndl(SysMapHndlValue)	((* (Handle *) 0x0A54) = SysMapHndlValue)
#define LMGetSysMap()	(* (short *) 0x0A58)
#define LMSetSysMap(SysMapValue)	((* (short *) 0x0A58) = SysMapValue)
#define LMGetCurMap()	(* (short *) 0x0A5A)
#define LMSetCurMap(CurMapValue)	((* (short *) 0x0A5A) = CurMapValue)
#define LMGetResLoad()	(* (Boolean *) 0x0A5E)
#define LMSetResLoad(ResLoadValue)	((* (Boolean *) 0x0A5E) = ResLoadValue)
#define LMGetResErr()	(* (short *) 0x0A60)
#define LMSetResErr(ResErrValue)	((* (short *) 0x0A60) = ResErrValue)
#define LMGetFScaleDisable()	(* (unsigned char *) 0x0A63)
#define LMSetFScaleDisable(FScaleDisableValue)	((* (unsigned char *) 0x0A63) = FScaleDisableValue)
#define LMGetCurActivate()	(* (WindowPeek *) 0x0A64)
#define LMSetCurActivate(CurActivateValue)	((* (WindowPeek *) 0x0A64) = CurActivateValue)
#define LMGetCurDeactive()	(* (WindowPeek *) 0x0A68)
#define LMSetCurDeactive(CurDeactiveValue)	((* (WindowPeek *) 0x0A68) = CurDeactiveValue)
#define LMGetDeskHook()	(* (UniversalProcPtr *) 0x0A6C)
#define LMSetDeskHook(DeskHookValue)	((* (UniversalProcPtr *) 0x0A6C) = DeskHookValue)
#define LMGetTEDoText()	(* (UniversalProcPtr *) 0x0A70)
#define LMSetTEDoText(TEDoTextValue)	((* (UniversalProcPtr *) 0x0A70) = TEDoTextValue)
#define LMGetTERecal()	(* (UniversalProcPtr *) 0x0A74)
#define LMSetTERecal(TERecalValue)	((* (UniversalProcPtr *) 0x0A74) = TERecalValue)
#define LMGetApplScratch()	(* (unsigned char *) 0x0A78)
#define LMSetApplScratch(ApplScratchValue)	((* (unsigned char *) 0x0A78) = ApplScratchValue)
#define LMGetGhostWindow()	(* (WindowPeek *) 0x0A84)
#define LMSetGhostWindow(GhostWindowValue)	((* (WindowPeek *) 0x0A84) = GhostWindowValue)
#define LMGetResumeProc()	(* (UniversalProcPtr *) 0x0A8C)
#define LMSetResumeProc(ResumeProcValue)	((* (UniversalProcPtr *) 0x0A8C) = ResumeProcValue)
#define LMGetANumber()	(* (short *) 0x0A98)
#define LMSetANumber(ANumberValue)	((* (short *) 0x0A98) = ANumberValue)
#define LMGetACount()	(* (short *) 0x0A9A)
#define LMSetACount(ACountValue)	((* (short *) 0x0A9A) = ACountValue)
#define LMGetDABeeper()	(* (UniversalProcPtr *) 0x0A9C)
#define LMSetDABeeper(DABeeperValue)	((* (UniversalProcPtr *) 0x0A9C) = DABeeperValue)
#define LMGetDAStrings(whichString) (* (((StringHandle *) 0x0AA0) + whichString))
#define LMSetDAStrings(DAStringsValue, whichString) ((* (((StringHandle *) 0x0AA0) + whichString)) = DAStringsValue)
#define LMGetTEScrpLength()	(* (short *) 0x0AB0)
#define LMSetTEScrpLength(TEScrpLengthValue)	((* (short *) 0x0AB0) = TEScrpLengthValue)
#define LMGetTEScrpHandle()	(* (Handle *) 0x0AB4)
#define LMSetTEScrpHandle(TEScrpHandleValue)	((* (Handle *) 0x0AB4) = TEScrpHandleValue)
#define LMGetSysResName()	(* (Str15 *) 0x0AD8)
#define LMSetSysResName(SysResNameValue)	((* (Str15 *) 0x0AD8) = SysResNameValue)
#define LMGetAppParmHandle()	(* (Handle *) 0x0AEC)
#define LMSetAppParmHandle(AppParmHandleValue)	((* (Handle *) 0x0AEC) = AppParmHandleValue)
#define LMGetDSErrCode()	(* (short *) 0x0AF0)
#define LMSetDSErrCode(DSErrCodeValue)	((* (short *) 0x0AF0) = DSErrCodeValue)
#define LMGetResErrProc()	(* (UniversalProcPtr *) 0x0AF2)
#define LMSetResErrProc(ResErrProcValue)	((* (UniversalProcPtr *) 0x0AF2) = ResErrProcValue)
#define LMGetDlgFont()	(* (short *) 0x0AFA)
#define LMSetDlgFont(DlgFontValue)	((* (short *) 0x0AFA) = DlgFontValue)
#define LMGetWidthPtr()	(* (Ptr *) 0x0B10)
#define LMSetWidthPtr(WidthPtrValue)	((* (Ptr *) 0x0B10) = WidthPtrValue)
#define LMGetATalkHk2()	(* (Ptr *) 0x0B18)
#define LMSetATalkHk2(ATalkHk2Value)	((* (Ptr *) 0x0B18) = ATalkHk2Value)
#define LMGetTopMenuItem()	(* (short *) 0x0B26)
#define LMSetTopMenuItem(TopMenuItemValue)	((* (short *) 0x0B26) = TopMenuItemValue)
#define LMGetAtMenuBottom()	(* (short *) 0x0B28)
#define LMSetAtMenuBottom(AtMenuBottomValue)	((* (short *) 0x0B28) = AtMenuBottomValue)
#define LMGetWidthTabHandle()	(* (Handle *) 0x0B2A)
#define LMSetWidthTabHandle(WidthTabHandleValue)	((* (Handle *) 0x0B2A) = WidthTabHandleValue)
#define LMGetMenuDisable()	(* (long *) 0x0B54)
#define LMSetMenuDisable(MenuDisableValue)	((* (long *) 0x0B54) = MenuDisableValue)
#define LMGetROMMapInsert()	(* (unsigned char *) 0x0B9E)
#define LMSetROMMapInsert(ROMMapInsertValue)	((* (unsigned char *) 0x0B9E) = ROMMapInsertValue)
#define LMGetTmpResLoad()	(* (unsigned char *) 0x0B9F)
#define LMSetTmpResLoad(TmpResLoadValue)	((* (unsigned char *) 0x0B9F) = TmpResLoadValue)
#define LMGetIntlSpec()	(* (Ptr *) 0x0BA0)
#define LMSetIntlSpec(IntlSpecValue)	((* (Ptr *) 0x0BA0) = IntlSpecValue)
#define LMGetWordRedraw()	(* (unsigned char *) 0x0BA5)
#define LMSetWordRedraw(WordRedrawValue)	((* (unsigned char *) 0x0BA5) = WordRedrawValue)
#define LMGetSysFontFam()	(* (short *) 0x0BA6)
#define LMSetSysFontFam(SysFontFamValue)	((* (short *) 0x0BA6) = SysFontFamValue)
#define LMGetSysFontSize()	(* (short *) 0x0BA8)
#define LMSetSysFontSize(SysFontSizeValue)	((* (short *) 0x0BA8) = SysFontSizeValue)
#define LMGetMBarHeight()	(* (short *) 0x0BAA)
#define LMSetMBarHeight(MBarHeightValue)	((* (short *) 0x0BAA) = MBarHeightValue)
#define LMGetTESysJust()	(* (short *) 0x0BAC)
#define LMSetTESysJust(TESysJustValue)	((* (short *) 0x0BAC) = TESysJustValue)
#define LMGetLastFOND()	(* (Handle *) 0x0BC2)
#define LMSetLastFOND(LastFONDValue)	((* (Handle *) 0x0BC2) = LastFONDValue)
#define LMGetFractEnable()	(* (unsigned char *) 0x0BF4)
#define LMSetFractEnable(FractEnableValue)	((* (unsigned char *) 0x0BF4) = FractEnableValue)
#define LMGetMMU32Bit()	(* (unsigned char *) 0x0CB2)
#define LMSetMMU32Bit(MMU32BitValue)	((* (unsigned char *) 0x0CB2) = MMU32BitValue)
#define LMGetTheGDevice()	(* (GDHandle *) 0x0CC8)
#define LMSetTheGDevice(TheGDeviceValue)	((* (GDHandle *) 0x0CC8) = TheGDeviceValue)
#define LMGetAuxWinHead()	(* (AuxWinHandle *) 0x0CD0)
#define LMSetAuxWinHead(AuxWinHeadValue)	((* (AuxWinHandle *) 0x0CD0) = AuxWinHeadValue)
#define LMGetTimeDBRA()	(* (short *) 0x0D00)
#define LMSetTimeDBRA(TimeDBRAValue)	((* (short *) 0x0D00) = TimeDBRAValue)
#define LMGetTimeSCCDB()	(* (short *) 0x0D02)
#define LMSetTimeSCCDB(TimeSCCDBValue)	((* (short *) 0x0D02) = TimeSCCDBValue)
#define LMGetJVBLTask()	(* (UniversalProcPtr *) 0x0D28)
#define LMSetJVBLTask(JVBLTaskValue)	((* (UniversalProcPtr *) 0x0D28) = JVBLTaskValue)
#define LMGetSynListHandle()	(* (Handle *) 0x0D32)
#define LMSetSynListHandle(SynListHandleValue)	((* (Handle *) 0x0D32) = SynListHandleValue)
#define LMGetMenuCInfo()	(* (MCTableHandle *) 0x0D50)
#define LMSetMenuCInfo(MenuCInfoValue)	((* (MCTableHandle *) 0x0D50) = MenuCInfoValue)
#define LMGetDTQueue()	((QHdrPtr) 0x0D92)
#define LMSetDTQueue(DTQueueValue)	((* (QHdrPtr) 0x0D92) = *(QHdrPtr)DTQueueValue)
#define LMGetJDTInstall()	(* (UniversalProcPtr *) 0x0D9C)
#define LMSetJDTInstall(JDTInstallValue)	((* (UniversalProcPtr *) 0x0D9C) = JDTInstallValue)
#define LMGetHiliteRGB()	( (RGBColor *) 0x0DA0)
#define LMSetHiliteRGB(HiliteRGBValue)	((* (RGBColor *) 0x0DA0) = *(RGBColor*)HiliteRGBValue)
#define LMGetTimeSCSIDB()	(* (short *) 0x0B24)
#define LMSetTimeSCSIDB(TimeSCSIDBValue)	((* (short *) 0x0B24) = TimeSCSIDBValue)
#define LMGetFSQHead() ((QHdrPtr) 0x0362)

#endif

#ifdef __cplusplus
}
#endif

#endif
