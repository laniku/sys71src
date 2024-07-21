#
#	File:		OS.make
#
#	Contains:	make file for OS library
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	  <SM13>	12/13/93	PN		Roll in KAOs and Horror changes to support Malcom and AJ
#									machines.
#	  <SM12>	11/10/93	fau		Update from SuperMunggio <SMG2>.
#	  <SMG2>	  9/1/93	chp		Fix up InterruptHandlers dependencies again.
#	  <SM11>	  9/9/93	pdw		Added slots.a to dependencies.
#	   <SM9>	  9/1/93	SKH		Added PwrControlsPatches.a to the OS.lib.  After Kaos stops changing
#									these patches will be removed and rolled into PowerMgr.a
#	   <SM8>	08-03-93	jmp		Added ROMEqu.a to the UniversalTables.a dependency list.
#	   <SM7>	 7/21/93	ECH		Removed ProcessManagerSegmentTweaks.a.o from OS.lib dependencies.
#	   <SM6>	 6/15/93	kc		Added back the MagicData, and checked in the file.
#	   <SM5>	 6/14/93	SAM		Commented out the magicdata stuff to fix the build (magicdata.a
#									is not in the project).
#	   <SM4>	 6/14/93	kc		Roll in Ludwig.
#	   <LW3>	 4/28/93	RB		Put back MagicData.a, since it got lost in the rewrite of the
#									make files.
#	   <LW2>	 3/16/93	chp		Removed build rules for DMAMgr (obsolete). Fixed
#									InterruptHandlers build where many dependencies were omitted.
#	   <SM3>	 5/30/93	SAM		Moved ROM_EM to Tidbits.
#	   <SM2>	 4/11/93	chp		Fixed InterruptHandlers build. Many dependencies were omitted.
#	   <SM3>	 12/1/92	ejb		include RTDrvr.make file
#	   <SM2>	11/11/92	RB		Added rules for ROM_EM.


StartDir		=	{OSDir}StartMgr:
IOPrimitivesDir	=	{OSDir}IOPrimitives:
MMUDir			=	{OSDir}MMU:
PowerMgrDir		=	{OSDir}PowerMgr:
SlotMgrDir		=	{OSDir}SlotMgr:
TrapDispDir		=	{OSDir}TrapDispatcher:
SCSIDir			=	{OSDir}SCSIMgr:
SCSI4pt3Dir		=	{OSDir}SCSIMgr4pt3:
HFSDir			=	{OSDir}HFS:
PPCDir			=	{OSDir}PPC:
ADBDir			=	{OSDir}ADBMgr:
TimeMgrDir		=	{OSDir}TimeMgr:
MemoryMgrDir	=	{OSDir}MemoryMgr:
BeepDir			=	{OSDir}Beep:
FPEmulationDir	=	{OSDir}FPUEmulation:
GestaltDir		=	{OSDir}Gestalt:
KeyboardDir		=	{OSDir}Keyboard:
NetBootDir		=	{OSDir}NetBoot:
VDigDir			=	{OSDir}VDig:
I2CDir			=	{OSDir}I2C:
RealTimeDir		=	{OSDir}RealTime:

#include {StartDir}StartMgr.make
#include {IOPrimitivesDir}IOPrimitives.make
#include {MMUDir}MMU.make
#include {PowerMgrDir}PowerMgr.make
#include {SlotMgrDir}SlotMgr.make
#include {TrapDispDir}TrapDispatcher.make
#include {SCSIDir}SCSIMgr.make
#include {SCSI4pt3Dir}SCSIMgr4pt3.make
#include {HFSDir}HFS.make
#include {PPCDir}PPC.make
#include {ADBDir}ADBMgr.make
#include {TimeMgrDir}TimeMgr.make
#include {MemoryMgrDir}MemoryMgr.make
#include {BeepDir}Beep.make
#include {FPEmulationDir}FPEmulation.make
#include {GestaltDir}Gestalt.make
#include {KeyboardDir}Keyboard.make
#include {NetBootDir}NetBoot.make
#include {VDigDir}VDig.make
#include {I2CDir}I2C.make
#include {RealTimeDir}RealTime.make


OSObjs	= 							"{ObjDir}clock.a.o"								¶
									"{ObjDir}CrsrDev.a.o"							¶
									"{ObjDir}CudaMgr.a.o"							¶
									"{ObjDir}DeferredTaskMgr.a.o"					¶
									"{ObjDir}DeviceMgr.a.o"							¶
									"{ObjDir}DockingMgr.a.o"						¶
									"{ObjDir}EgretMgr.a.o"							¶
									"{ObjDir}HwPriv.a.o"							¶
									"{ObjDir}I2C.a.o"							¶
									"{ObjDir}Universal.a.o"							¶
									"{ObjDir}InterruptHandlers.a.o"					¶
									"{ObjDir}IOPMgr.a.o"							¶
									"{ObjDir}OSEventMgr.a.o"						¶
									"{ObjDir}queue.a.o"								¶
									"{ObjDir}sysUtil.a.o"							¶
									"{ObjDir}VerticalRetraceMgr.a.o"				¶
									"{ObjDir}MiscPatches.a.o"						¶
									"{ObjDir}MagicData.a.o"							¶
									"{ObjDir}PowerMgr.o"							¶
									"{ObjDir}PwrControlsPatches.o"					¶
									"{ObjDir}VMPatches.a.o"							¶
									"{ObjDir}Dispatch.a.o"							¶
									"{ObjDir}UniversalTables.a.o"


"{LibDir}OS.lib"				Ä	{OSObjs}
	Lib {StdLibOpts}	{OSObjs} -o "{Targ}"


"{ObjDir}clock.a.o"				Ä	"{OSDir}clock.a"								¶
									"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{IntAIncludes}IOPrimitiveEqu.a"				¶
									"{IntAIncludes}UniversalEqu.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}clock.a"


"{ObjDir}CrsrDev.a.o"			Ä	"{OSDir}CrsrDev.a"								¶
									"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}EgretEqu.a"						¶
									"{IntAIncludes}IOPEqu.a"						¶
									"{IntAIncludes}AppleDeskBusPriv.a"				¶
									"{IntAIncludes}CrsrDevEqu.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}CrsrDev.a"


"{ObjDir}CudaMgr.a.o"			Ä	"{OSDir}CudaMgr.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}CudaMgr.a"


"{ObjDir}DeferredTaskMgr.a.o"	Ä	"{OSDir}DeferredTaskMgr.a"						¶
									"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}HardwareEqu.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}DeferredTaskMgr.a"


"{ObjDir}DeviceMgr.a.o"			Ä	"{OSDir}DeviceMgr.a"							¶
									"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}HardwareEqu.a"						¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{AIncludes}ROMEqu.a"							¶
									"{AIncludes}Slots.a"							¶
									"{AIncludes}FSEqu.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}DeviceMgr.a"


"{ObjDir}DispatchHelper.a.o"	Ä 	"{ObjDir}StandardEqu.d"							¶
									"{OSDir}DispatchHelper.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}DispatchHelper.a"

"{ObjDir}DispTable.a.o"			Ä	"{OSDir}DispTable.a"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{AIncludes}HardwareEqu.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}DispTable.a"


"{ObjDir}DockingMgr.a.o"		Ä	"{OSDir}DockingMgr.a"							¶
									"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{IntAIncludes}PowerPrivEqu.a"					¶
									"{AIncludes}ROMEqu.a"							¶
									"{AIncludes}Slots.a"							¶
									"{AIncludes}SCSI.a"								¶
									"{IntAIncludes}SCSIPriv.a"						¶
									"{IntAIncludes}DockingEqu.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}DockingMgr.a"


"{ObjDir}EgretMgr.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}InternalOnlyEqu.a"				¶
									"{AIncludes}HardwareEqu.a"						¶
									"{IntAIncludes}IOPEqu.a"						¶
									"{IntAIncludes}AppleDeskBusPriv.a"				¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{IntAIncludes}EgretEqu.a"						¶
									"{OSDir}EgretMgr.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}EgretMgr.a"


"{ObjDir}HwPriv.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{AIncludes}HardwareEqu.a"						¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{OSDir}HwPriv.a"									
	Asm {StdAOpts} -o "{Targ}" "{OSDir}HwPriv.a"

"{ObjDir}I2C.a.o"					Ä	"{ObjDir}StandardEqu.d"				¶
										"{IntAIncludes}HardwarePrivateEqu.a"		¶
										"{IntAIncludes}UniversalEqu.a"				¶
										"{AIncludes}ROMEqu.a"						¶
										"{IntAIncludes}i2cEqu.a"
	Asm {StdAOpts} -o "{Targ}" "{I2CDir}I2C.a"

"{ObjDir}InterruptHandlers.a.o"	Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{IntAIncludes}SysPrivateEqu.a"					¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{IntAIncludes}IOPrimitiveEqu.a"				¶
									"{AIncludes}Shutdown.a"							¶
									"{IntAIncludes}PowerPrivEqu.a"					¶
									"{IntAIncludes}EgretEqu.a"						¶
									"{IntAIncludes}PSCEqu.a"						¶
									"{IntAIncludes}AMICEqu.a"						¶
									"{IntAIncludes}GrandCentralPriv.a"				¶
									"{OSDir}InterruptHandlers.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}InterruptHandlers.a"


"{ObjDir}IOPMgr.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}HardwareEqu.a"						¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{IntAIncludes}IOPequ.a"						¶
									"{OSDir}IOPMgr.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}IOPMgr.a"

"{ObjDir}OverPatch.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}Slots.a"							¶
									"{AIncludes}ROMEqu.a"							¶
									"{AIncludes}Video.a"							¶
									"{OSDir}OverPatch.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}OverPatch.a"

"{ObjDir}MagicData.a.o"			Ä	"{OSDir}MagicData.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}MagicData.a"

"{ObjDir}OSEventMgr.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{AIncludes}HardwareEqu.a"						¶
									"{OSDir}OSEventMgr.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}OSEventMgr.a"


"{ObjDir}Queue.a.o"				Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}HardwareEqu.a"						¶
									"{OSDir}Queue.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}Queue.a"


"{ObjDir}sysUtil.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}GestaltEqu.a"						¶
									"{IntAIncludes}IOPrimitiveEqu.a"				¶
									"{IntAIncludes}ReliabilityEqu.a"				¶
									"{IntAIncludes}UniversalEqu.a"					¶
									 "{OSDir}sysUtil.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}sysUtil.a"


"{ObjDir}Universal.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{AIncludes}HardwareEqu.a"						¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{AIncludes}Slots.a"							¶
									"{OSDir}Universal.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}Universal.a" -i "{OSDir}StartMgr"


"{ObjDir}UniversalTables.a.o"		Ä	"{ObjDir}StandardEqu.d"						¶
										"{IntAIncludes}HardwarePrivateEqu.a"		¶
										"{IntAIncludes}UniversalEqu.a"				¶
										"{AIncludes}Slots.a"						¶
										"{IntAincludes}DepVideoEqu.a"				¶
										"{AIncludes}ROMEqu.a"						¶
										"{OSDir}UniversalTables.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}UniversalTables.a" -i "{OSDir}IoPrimitives:"


"{ObjDir}VerticalRetraceMgr.a.o" Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}Slots.a"							¶
									"{IntAIncludes}SlotMgrEqu.a"					¶
									"{AIncludes}HardwareEqu.a"						¶
									"{OSDir}VerticalRetraceMgr.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}VerticalRetraceMgr.a"


"{ObjDir}WallyWorld.a.o"			Ä	"{AIncludes}Private.a"						¶
										"{IntAIncludes}HardwarePrivateEqu.a"		¶
										"{IntAIncludes}UniversalEqu.a"				¶
										"{OSDir}WallyWorld.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}WallyWorld.a"


"{ObjDir}VMPatches.a.o"			Ä	"{OSDir}VMPatches.a"
	Asm {StdAOpts} -o "{Targ}" "{OSDir}VMPatches.a"
