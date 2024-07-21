#
#	File:		makefile
#
#	Contains:	Contents.
#
#	Written by:	Writers.
#
#	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	  <SM11>	 1/31/94	DCB		
#	  <SM10>	 1/31/94	DCB		Added STP and BlackBird defines.
#	   <SM9>	 1/14/94	DCB		Changing to script system INIT
#	   <SM8>	11/23/93	DCB		Record options should be the same as for ROM. Also default to no
#									debugger to prevent SCM from accidentally building with the trap
#									there. Paul - I will do the key down thing real soon now.
#	   <SM7>	11/22/93	pdw		Rolling in from <MCxx>.
#	   <SM6>	11/22/93	pdw		Added forSTP601v1 define.  (Is this the same as forSTP601?)
#	   <SM5>	11/19/93	chp		Remove the FORTNTDEBUG flag, which I detest and have already
#									removed from the SCSI Manager.
#	   <SM4>	11/17/93	DCB		Updating so this works with the stuff Craiger checked in.
#	   <SM3>	10/29/93	DCB		Removing RISC dependencies from the makefile.
#	   <MC4>	10/28/93	pdw		Got rid of nonSerialized/forPDM dependencies.
#	   <SM2>	10/14/93	pdw		Rolled in from MC.
#	   <MC3>	10/12/93	pdw		Added support for Synchronous data transfers, rewrote State
#									Machine, message handling etc.
#	   <MC2>	 9/26/93	pdw		Added forIttInit.
#		 <1>	 9/13/93	pdw		first checked in
#		 <6>	 9/11/92	PW		Made friendly to multiple build enviroments
#		 <5>	 6/17/92	CB		Made friendly to multiple build enviroments
#		 <4>	 6/17/92	PW		Removed testTool stuff
#		 <3>	 6/16/92	PW		Added HALc96PSC.a
#
#

#	File:	MakeFile
# 	Paul Wolf
#	2/16/89
#

# For SuperMario, default to non-PDM build

forPDMProto		= 0
nonSerializedIO	= 1

forIttInit		= 1

#						touch Recorder.a
TAPE_LENGTH			= 1024
RECORD_NONCACHABLE	= 1
StopRecordOnFull	= 0
#						touch SCSIGlue.a ; touch XPTSCSIXlate.a ; touch XPT.a
CALL_RECORD_ON	= 1
#						touch SIMMachine.a ; touch HALc96Routines.a
STACK_RECORD_ON	= 0
#						touch HALc96equ.a
RECORD_ON		= 0
ERR_RECORD_ON 	= 1
RECORD_rCMD		= 0
DEBUGGING		= 0
noSCSIInts		= 0
#						touch SCSIDebug.h ; touch XPT.c
forceSyncAlways	= 0
#						touch IttInit.a
useINITDebugger	= 0


AandCoptions	=	¶
	-d forPDMProto={forPDMProto} ¶
	-d forIttInit={forIttInit} ¶
	-d Include_Debugger_Names=1 ¶
	-d forceSyncAlways={forceSyncAlways} ¶
	-d nonSerializedIO={nonSerializedIO} ¶
	-d noSCSIInts={noSCSIInts} ¶
	-d StopRecordOnFull={StopRecordOnFull} ¶
	-d CALL_RECORD_ON={CALL_RECORD_ON} ¶
	-d DEBUGGING={DEBUGGING} ¶
	-d RECORD_NONCACHABLE={RECORD_NONCACHABLE} ¶
	-d RECORD_ON={RECORD_ON} ¶
	-d RECORD_rCMD={RECORD_rCMD} ¶
	-d STACK_RECORD_ON={STACK_RECORD_ON} ¶
	-d TAPE_LENGTH={TAPE_LENGTH} ¶
	-d useINITDebugger={useINITDebugger}


itt		=	"{sources}os:scsimgr4pt3:"

SCSI4pt3Dir		= "{itt}"
SCSIMgr4pt3		= "{itt}"
intaincludes	= "{sources}Internal:Asm:"
aincludes		= "{sources}Interfaces:AIncludes:"
intcincludes	= "{sources}Internal:C:"
cincludes		= "{sources}Interfaces:cincludes:"
libraries		= "{sources}BuildResults:Universal:Obj:Interface:"
objects			= "{sources}BuildResults:Universal:Obj:"

toolname	= cousin

initname	= ".IttInit"


S		=	{itt}

O		=	{objects}

ObjDir	=	{O}

dest	=	{itt}

#IntAIncludes	= {sources}Internal:Asm:


BootObjects = 	{O}BootItt.c.o			¶
				{O}BootItt.a.o			
				
XPTObjects =	{O}SCSIGlue.a.o			¶
				{O}XPT.c.o				¶
				{O}XPT.a.o				¶
				{O}XPToldCall.c.o		¶
				{O}XPTfunctions.c.o		¶
				{O}XPTSCSIXlate.a.o		¶
				{O}Queue.a.o			

SIMObjects =	{O}SIMCore.c.o			¶
				{O}SIMCore.a.o			¶
				{O}SIMQ.c.o 			¶
				{O}SIMmachine.c.o 		¶
				{O}SIMmachine.a.o 		¶
				{O}QueueUtils.a.o		¶
				{O}Timeout.c.o			¶
				{O}Timeout.a.o
				
HALObjects =	{O}HALc96.a.o			¶
				{O}HALc96Data.a.o		¶
				{O}HALc96BIOS.a.o		¶
				{O}HALc96Routines.a.o	¶
				{O}HALc96Init.a.o		¶
				{O}HALc96.c.o			¶
				{O}HALc96HWInit.a.o		¶
				{O}HALc96DMA.a.o		¶
				{O}HALc96AMIC.a.o		¶
				{O}HALc96PSC.a.o		¶
				{O}HALc96GC.c.o			¶
				{O}HALc96AMIC.c.o		¶
				{O}HALc96PSC.c.o		¶
				{O}HALc96GC.a.o

InitObjects	=	{O}IttInit.a.o			¶
				{HALObjects}			¶
				{O}Recorder.a.o			¶
				{O}InitItt.c.o			¶
				{XPTObjects}  			¶
				{SIMObjects}			¶
				{BootObjects}


ALL		Ä		"{dest}{initname}"	{BootObjects}		#"{dest}{toolname}"	


"LinkedXPT"	Ä	{XPTObjects}
	echo " =>> linking the XPT"
	link 							¶
		{XPTObjects}				¶
#		{Libraries}Interface.o		¶
	-o "{Targ}" 					¶
	-ra =resSysHeap,resLocked 		¶
	-rt INIT=96 					¶
	-t "scri" 						¶
	-c "woof"

"LinkedSIM"	Ä	{SIMObjects}
	echo " =>> linking the SIM"
	link 							¶
		{SIMObjects}				¶
#		{Libraries}Interface.o		¶
	-o "{Targ}" 					¶
	-ra =resSysHeap,resLocked 		¶
	-rt INIT=96 					¶
	-t "scri" 						¶
	-c "woof"

"LinkedHAL"	Ä	{HALObjects}
	echo " =>> linking the HAL"
	link 							¶
		{HALObjects}				¶
#		{Libraries}Interface.o		¶
	-o "{Targ}" 					¶
	-ra =resSysHeap,resLocked 		¶
	-rt INIT=96 					¶
	-t "scri" 						¶
	-c "woof"

"{dest}{initname}"	Ä	{InitObjects}
	echo " =>> linking the INIT"
	set exit 1
	set libraries "{sources}BuildResults:Universal:Obj:Interface:"
	link 							¶
		{InitObjects}				¶
		{Libraries}Interface.o		¶
#		{Libraries}Runtime.o		¶
#		-sn "Main=%A5Init"				¶
#		-sn "_DataInit=%A5Init"			¶
#		-sn "INTENV=%A5Init"			¶
	-o "{Targ}" 					¶
	-ra =resSysHeap,resLocked 		¶
	-rt INIT=96 					¶
	-t "scri" 						¶
	-c "woof"
	echo "data ¶'sysz¶' ¶(0¶) ¶{ ¶$¶"0010 0000¶" ¶}¶;" | rez -a -o "{Targ}" 


"{ObjDir}BootItt.a.o"		Ä	"{IntAIncludes}HardwarePrivateEqu.a"	¶
								"{itt}Debug.a"			¶
								"{AIncludes}SCSI.a"					¶
								"{itt}ACAM.a"

"{ObjDir}HALc96.a.o"		Ä	"{AIncludes}HardwareEqu.a"			¶
								"{IntAIncludes}UniversalEqu.a"			¶
								"{itt}Debug.a"			¶
								"{AIncludes}SCSI.a"					¶
								"{itt}SCSIEqu53c96.a"			¶
								"{itt}ACAM.a"			¶
								"{itt}SIMCoreEqu.a"			¶
								"{itt}HALc96equ.a"

"{ObjDir}HALc96AMIC.a.o"	Ä	"{AIncludes}HardwareEqu.a"			¶
								"{IntAIncludes}UniversalEqu.a"			¶
								"{itt}Debug.a"			¶
								"{AIncludes}SCSI.a"					¶
								"{itt}SCSIEqu53c96.a"			¶
								"{itt}ACAM.a"			¶
								"{itt}SIMCoreEqu.a"			¶
								"{itt}HALc96equ.a"

"{ObjDir}HALc96Data.a.o"	Ä	"{AIncludes}HardwareEqu.a"			¶
								"{IntAIncludes}UniversalEqu.a"			¶
								"{itt}Debug.a"			¶
								"{AIncludes}SCSI.a"					¶
								"{IntAIncludes}SCSIPriv.a"			¶
								"{itt}SCSIEqu53c96.a"			¶
								"{itt}ACAM.a"			¶
								"{itt}SIMCoreEqu.a"			¶
								"{itt}XPTEqu.a"			¶
								"{itt}HALc96equ.a"

"{ObjDir}HALc96DMA.a.o"		Ä	"{IntAIncludes}HardwarePrivateEqu.a"	¶
								"{AIncludes}HardwareEqu.a"			¶
								"{IntAIncludes}UniversalEqu.a"			¶
								"{itt}Debug.a"			¶
								"{AIncludes}SCSI.a"					¶
								"{itt}SCSIEqu53c96.a"		¶
								"{itt}ACAM.a"			¶
								"{itt}SIMCoreEqu.a"			¶
								"{itt}HALc96equ.a"

"{ObjDir}HALc96HWInit.a.o"	Ä	"{IntAIncludes}HardwarePrivateEqu.a"	¶
								"{IntAIncludes}UniversalEqu.a"			¶
								"{itt}Debug.a"			¶
								"{AIncludes}SCSI.a"					¶
								"{itt}SCSIEqu53c96.a"			¶
								"{itt}HALc96equ.a"

"{ObjDir}HALc96Init.a.o"	Ä	"{AIncludes}HardwareEqu.a"			¶
								"{IntAIncludes}UniversalEqu.a"			¶
								"{itt}Debug.a"			¶
								"{AIncludes}SCSI.a"					¶
								"{itt}SCSIEqu53c96.a"			¶
								"{IntAIncludes}SCSIPriv.a"			¶
								"{itt}HALc96equ.a"			¶
								"{itt}ACAM.a"

"{ObjDir}HALc96BIOS.a.o"	Ä	"{IntAIncludes}HardwarePrivateEqu.a"			¶
								"{IntAIncludes}UniversalEqu.a"			¶
								"{IntAIncludes}MC680x0.a"			¶
								"{IntAIncludes}SCSIPriv.a"			¶
								"{itt}Debug.a"			¶
								"{AIncludes}SCSI.a"					¶
								"{itt}SCSIEqu53c96.a"			¶
								"{itt}ACAM.a"			¶
								"{itt}SIMCoreEqu.a"			¶
								"{itt}HALc96equ.a"

"{ObjDir}HALc96GC.a.o"		Ä	"{itt}HALc96GC.a"						¶
								"{AIncludes}DBDMA.a"					¶
								"{itt}HALc96equ.a"						¶
								"{IntAIncludes}GrandCentralPriv.a"

"{ObjDir}HALc96GC.c.o"		Ä	"{itt}HALc96GC.c"				¶
								"{itt}SIMCorePriv.h"			¶
								"{CIncludes}SCSI.h"						¶
								"{itt}SIMCore.h"				¶
								"{CIncludes}Memory.h"					¶
								"{CIncludes}Timer.h"					¶
								"{CIncludes}OSUtils.h"					¶
								"{itt}ACAM.h"					¶
								"{CIncludes}Types.h"					¶
								"{CIncludes}Traps.h"					¶
								"{itt}HALc96.h"

"{ObjDir}HALc96PSC.a.o"		Ä	"{AIncludes}HardwareEqu.a"			¶
								"{IntAIncludes}UniversalEqu.a"			¶
								"{itt}Debug.a"			¶
								"{AIncludes}SCSI.a"					¶
								"{itt}SCSIEqu53c96.a"			¶
								"{itt}ACAM.a"			¶
								"{itt}SIMCoreEqu.a"			¶
								"{itt}HALc96equ.a"			¶
								"{IntAIncludes}PSCequ.a"

"{ObjDir}HALc96Routines.a.o" Ä	"{IntAIncludes}HardwarePrivateEqu.a"	¶
								"{IntAIncludes}UniversalEqu.a"			¶
								"{IntAIncludes}DeferredTaskEqu.a"			¶
								"{IntAIncludes}MC680x0.a"			¶
								"{itt}Debug.a"			¶
								"{itt}ACAM.a"			¶
								"{AIncludes}SCSI.a"					¶
								"{itt}XPTEqu.a"			¶
								"{itt}SCSIEqu53c96.a"			¶
								"{itt}SIMCoreEqu.a"			¶
								"{itt}HALc96equ.a"

"{ObjDir}IttInit.a.o"		Ä	"{IntAIncludes}HardwarePrivateEqu.a"	¶
								"{IntAIncludes}UniversalEqu.a"			¶
								"{AIncludes}SCSI.a"					¶
								"{IntAIncludes}SCSIPriv.a"			¶
								"{itt}Debug.a"			¶
								"{itt}ACAM.a"			¶
								"{itt}XPTEqu.a"

"{ObjDir}Recorder.a.o"		Ä	"{AIncludes}HardwareEqu.a"			¶
								"{itt}Debug.a"						¶
								"{AIncludes}SCSI.a"					¶
								"{IntAIncludes}SCSIPriv.a"			¶
								"{itt}HALc96equ.a"					¶
								"{itt}XPTEqu.a"

"{ObjDir}SCSIGlue.a.o"		Ä	"{IntAIncludes}HardwarePrivateEqu.a"	¶
								"{IntAIncludes}UniversalEqu.a"			¶
								"{itt}Debug.a"			¶
								"{itt}ACAM.a"			¶
								"{AIncludes}SCSI.a"					¶
								"{IntAIncludes}SCSIPriv.a"			¶
								"{itt}XPTEqu.a"

"{ObjDir}SIMmachine.a.o"	Ä	"{AIncludes}HardwareEqu.a"			¶
								"{IntAIncludes}UniversalEqu.a"			¶
								"{IntAIncludes}DeferredTaskEqu.a"			¶
								"{itt}Debug.a"			¶
								"{itt}ACAM.a"

"{ObjDir}timeout.a.o"		Ä	"{AIncludes}HardwareEqu.a"			¶
								"{itt}Debug.a"			¶
								"{itt}ACAM.a"

"{ObjDir}XPT.a.o"			Ä	"{IntAIncludes}HardwarePrivateEqu.a"	¶
								"{IntAIncludes}UniversalEqu.a"			¶
								"{AIncludes}SCSI.a"					¶
								"{IntAIncludes}SCSIPriv.a"			¶
								"{itt}Debug.a"			¶
								"{itt}ACAM.a"			¶
								"{itt}XPTEqu.a"

"{ObjDir}XPTSCSIXlate.a.o"	Ä	"{AIncludes}HardwareEqu.a"			¶
								"{IntAIncludes}UniversalEqu.a"			¶
								"{itt}Debug.a"			¶
								"{AIncludes}SCSI.a"					¶
								"{IntAIncludes}SCSIPriv.a"			¶
								"{itt}ACAM.a"

"{ObjDir}BootItt.c.o"		Ä	"{CIncludes}Devices.h"		¶
								"{CIncludes}Types.h"		¶
								"{CIncludes}Packages.h"		¶
								"{CIncludes}Traps.h"		¶
								"{IntCIncludes}TrapsPrivate.h"	¶
								"{CIncludes}Memory.h"		¶
								"{CIncludes}SysEqu.h"		¶
								"{CIncludes}SCSIStandard.h"	¶
								"{CIncludes}SCSI.h"			¶
								"{CIncludes}OSUtils.h"		¶
								"{CIncludes}Devices.h"		¶
								"{CIncludes}Slots.h"		¶
								"{CIncludes}Start.h"		¶
								"{itt}ACAM.h"		¶
								"{itt}XPT.h"		¶
								"{itt}XPTpriv.h"	¶
								"{itt}BootItt.h"

"{ObjDir}HALc96.c.o"		Ä	"{CIncludes}Types.h"		¶
								"{CIncludes}Memory.h"		¶
								"{CIncludes}SCSIStandard.h"	¶
								"{CIncludes}SCSI.h"			¶
								"{itt}ACAM.h"		¶
								"{itt}SIMCore.h"	¶
								"{itt}SIMCorePriv.h" ¶
								"{itt}HALc96.h"

"{ObjDir}HALc96PSC.c.o"		Ä	"{CIncludes}Types.h"		¶
								"{CIncludes}Memory.h"		¶
								"{CIncludes}SCSI.h"			¶
								"{CIncludes}SCSIStandard.h"	¶
								"{itt}ACAM.h"		¶
								"{itt}SimCore.h"		¶
								"{itt}HALc96.h"		¶
								"{itt}SIMCorePriv.h"

"{ObjDir}HALc96AMIC.c.o"	Ä	"{CIncludes}Types.h"		¶
								"{CIncludes}Memory.h"		¶
								"{CIncludes}Traps.h"		¶
								"{IntCIncludes}TrapsPrivate.h"	¶
								"{CIncludes}SCSI.h"			¶
								"{CIncludes}SCSIStandard.h"	¶
								"{itt}ACAM.h"		¶
								"{itt}SimCore.h"		¶
								"{itt}HALc96.h"		¶
								"{itt}SIMCorePriv.h"

"{ObjDir}InitItt.c.o"		Ä	"{CIncludes}Memory.h"		¶
								"{CIncludes}SCSIStandard.h"	¶
								"{itt}ACAM.h"		¶
								"{itt}XPT.h"		¶
								"{itt}SIMCore.h"		¶
								"{itt}HALc96.h"		¶
								"{itt}SCSIGlue.h"		¶
								"{CIncludes}GestaltEqu.h"		¶
								"{itt}XPTPriv.h"

"{ObjDir}SampleSCSI.c.o"	Ä	"{CIncludes}SCSI.h"			¶
								"{CIncludes}types.h"		¶
								"{CIncludes}stdio.h"		¶
								"{CIncludes}memory.h"		¶
								"{itt}ACAM.h"

"{ObjDir}SIMCore.c.o"		Ä	"{CIncludes}Types.h"		¶
								"{CIncludes}Memory.h"		¶
								"{CIncludes}SCSIStandard.h"	¶
								"{CIncludes}SCSI.h"			¶
								"{CIncludes}Errors.h"		¶
								"{itt}ACAM.h"		¶
								"{itt}XPT.h"		¶
								"{itt}SIMCore.h"		¶
								"{itt}SIMCorePriv.h"		¶
								"{itt}SIMQ.h"		¶
								"{itt}SCSIGlue.h"		¶
								"{itt}Recorder.h"

"{ObjDir}SIMmachine.c.o"	Ä	"{CIncludes}Types.h"		¶
								"{CIncludes}Memory.h"		¶
								"{CIncludes}SCSIStandard.h"	¶
								"{CIncludes}SCSI.h"			¶
								"{itt}ACAM.h"		¶
								"{itt}XPT.h"		¶
								"{itt}CUtils.h"		¶
								"{itt}SCSIGlue.h"		¶
								"{itt}SIMCore.h"		¶
								"{itt}SIMCorePriv.h"		¶
								"{itt}SIMQ.h"		¶
								"{itt}Recorder.h"

"{ObjDir}SIMQ.c.o"			Ä	"{CIncludes}Types.h"		¶
								"{CIncludes}Memory.h"		¶
								"{CIncludes}SCSIStandard.h"	¶
								"{CIncludes}SCSI.h"			¶
								"{itt}ACAM.h"				¶
								"{itt}CUtils.h"				¶
								"{itt}XPT.h"				¶
								"{itt}SIMCore.h"			¶
								"{itt}SIMCorePriv.h"		¶
								"{itt}SIMQ.h"				¶
								"{itt}QueueUtils.h"			¶
								"{itt}Recorder.h"

"{ObjDir}Timeout.c.o"		Ä	"{CIncludes}Types.h"		¶
								"{CIncludes}Packages.h"		¶
								"{CIncludes}Memory.h"		¶
								"{CIncludes}SCSIStandard.h"	¶
								"{CIncludes}SCSI.h"			¶
								"{itt}ACAM.h"		¶
								"{itt}SIMCore.h"		¶
								"{itt}SIMCorePriv.h"		¶
								"{itt}SIMQ.h"

"{ObjDir}XPT.c.o"			Ä	"{CIncludes}Types.h"		¶
								"{CIncludes}Memory.h"		¶
								"{CIncludes}OSUtils.h"		¶
								"{CIncludes}Errors.h"		¶
								"{CIncludes}SCSIStandard.h"	¶
								"{CIncludes}SCSI.h"			¶
								"{CIncludes}Slots.h"		¶
								"{itt}ACAM.h"				¶
								"{itt}SCSIGlue.h"		¶
								"{itt}SIMCore.h"		¶
								"{itt}BootItt.h"		¶
								"{itt}XPT.h"			¶
								"{itt}XPTpriv.h"		¶
								"{itt}Recorder.h"

"{ObjDir}XPTfunctions.c.o"	Ä	"{CIncludes}Types.h"		¶
								"{CIncludes}Memory.h"		¶
								"{itt}ACAM.h"		¶
								"{itt}XPT.h"

"{ObjDir}XPToldCall.c.o"	Ä	"{CIncludes}Types.h"		¶
								"{CIncludes}Memory.h"		¶
								"{CIncludes}OSUtils.h"		¶
								"{CIncludes}SCSIStandard.h"	¶
								"{CIncludes}SCSI.h"			¶
								"{itt}ACAM.h"		¶
								"{itt}CUtils.h"		¶
								"{itt}XPT.h"		¶
								"{itt}XPTpriv.h"

ourAOptions	=	-i "{sources}Internal:Asm:" -i "{objects}" ¶
	-case obj ¶
	{AandCoptions}

AOptions	=	{ourAOptions} ¶
	-d TRUE=1 -d FALSE=0 ¶
	-d hasAsyncSCSI=TRUE ¶
	-d Alignment=16 -d CPU=20 -d ROMRelease=$A3E3 -d SubRelease=3  ¶
	-blksize 62 -d hasCacheTypeCPU=FALSE -d hasAMIC=TRUE -d SupportNativeComponents=TRUE ¶
	-d hasRISCV0ResMgrPatches=FALSE -d hasNewHeapMgr=TRUE -d hasPDMMaceEnet=TRUE ¶
	-d hasMace=FALSE -d hasMixedMode=TRUE -d kHasNewFloppyDriver=FALSE ¶
	-d hasSCSIDiskMode=TRUE -d hasDataAccessPACK=TRUE -d hasSysSevenResources=TRUE ¶
	-d hasVMinROM=TRUE -d has2MegROMOrMore=TRUE -d hasCAppleTalkInROM=FALSE ¶
	-d hasAppleTalkInROM=TRUE -d hasNewAge=FALSE -d hasVideoIn=TRUE ¶
	-d hasDSP=FALSE -d hasNewSoundMgr=FALSE -d BadBlockSparingEnabled=TRUE -d CubeE=TRUE ¶
	-d ForROM=TRUE -d IopADB=TRUE -d LC930=FALSE -d NewBuildSystem=TRUE -d OssADB=TRUE ¶
	-d PadForOverpatch=FALSE -d PwrMgrADB=TRUE -d ROMFastTraps=FALSE -d ROMinRAM=FALSE ¶
	-d Supports24Bit=FALSE -d SystemSevenOrLater=TRUE -d SystemSixOrLater=TRUE ¶
	-d TheFuture=FALSE -d ViaADB=TRUE -d forADBKeyboards=TRUE -d forAppleTalk20=TRUE ¶
	-d forCyclone=FALSE -d forLocalizability=TRUE -d forNonADBKeyboards=FALSE ¶
	-d forRomulator=FALSE -d forSmurf=FALSE -d has040MMU=TRUE ¶
	-d hasADBKeyLayouts=TRUE -d hasASC=TRUE -d hasAliasMgr=TRUE -d hasApple2Fonts=TRUE ¶
	-d hasAppleEventMgr=TRUE -d hasBalloonHelp=TRUE -d hasBattery=TRUE -d hasCQD=TRUE ¶
	-d hasCommToolbox=TRUE -d hasCPUIDRegister=TRUE -d hasDAFB=TRUE -d hasDisplayMgr=TRUE ¶
	-d hasDJMEMC=TRUE -d hasDataAccessMgr=TRUE -d hasEDisk=TRUE -d hasEclipseVIA2=TRUE ¶
	-d hasEditionMgr=TRUE -d hasEgret=TRUE -d hasExtendedCharacterSet=TRUE -d hasFMC=TRUE ¶
	-d hasGDU=TRUE -d hasGlue=TRUE -d hasHarpoVIA=FALSE -d hasHMC=TRUE -d hasIdle=TRUE ¶
	-d hasIopScc=TRUE -d hasIopSwim=TRUE -d hasJaws=TRUE -d hasLCDScreen=FALSE -d hasMDU=TRUE ¶
	-d hasMMU=TRUE -d hasMSC=TRUE -d hasMac2VIA2=TRUE -d hasMagic=FALSE -d hasNetBoot=TRUE ¶
	-d hasNiagra=TRUE -d hasNonADBKeyLayouts=FALSE -d hasNormandy=FALSE -d hasOrwell=TRUE ¶
	-d hasOss=TRUE -d hasPSC=FALSE -d hasPictureUtilities=FALSE -d hasPortableKeyLayouts=FALSE ¶
	-d hasPowerMgr=FALSE -d hasPratt=TRUE -d hasProtectedPRAM=TRUE -d hasPwrControls=TRUE ¶
	-d hasPwrMgrClock=TRUE -d hasRBV=TRUE -d hasSCSI96=TRUE -d hasSWIM2=TRUE -d hasSwim3=TRUE ¶
	-d hasSlotMgr=TRUE -d hasSonora=TRUE -d hasSplineFonts=TRUE -d hasTrueType2Byte=FALSE ¶
	-d hasVDAC=TRUE -d hasVIAClock=TRUE -d hasVISA2=TRUE -d hasVISADecoder=TRUE ¶
	-d hasWaimeaVIA2=TRUE -d hasYMCA=TRUE -d isUniversal=TRUE ¶
	-d onHafMac=TRUE -d onMac32=TRUE -d onNuMac=TRUE -d pre70=FALSE ¶
	-d forSTP601=FALSE -d forSTP601v1=FALSE -d BLACKBIRDDEBUG=FALSE


COptions =	-mbg full -opt full -mc68020 -b -r -warnings on -i "{sources}Internal:C:" -i "{objects}" ¶
	-d ForROM=1 ¶
	{AandCoptions}


{O}		Ä	{S}
 
.a.o		Ä	.a		Debug.a		ACAM.a
	echo "  => Assembling  {Default}.a"
	set intaincludes "{sources}Internal:Asm:" ; set aincludes "{sources}Interfaces:AIncludes:"
	{Asm}	{AOptions}	{DepDir}{Default}.a  -o {TargDir}{Default}.a.o
	

.c.o		Ä	.c		ACAM.h
	echo '  => C-Compiling  {Default}.c'
	set intcincludes "{sources}Internal:C:"  ; set cincludes "{sources}Interfaces:cincludes:"
	{C} {COptions}  {DepDir}{Default}.c  -o {TargDir}{Default}.c.o -r
		
