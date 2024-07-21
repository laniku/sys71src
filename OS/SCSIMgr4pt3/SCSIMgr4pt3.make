#
#	File:		SCSIMgr4pt3.make
#
#	Contains:	Makefile for SCSIMgr4pt3.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	  <SM14>	 1/28/94	chp		Roll in salient portions of “makefile” to allow the Itt
#									debugging extension to be build entirely within the SuperMario
#									environment. Add a CleanSCSI target; this is used like Build ROM
#									Clean, but removes only the SCSIMgr4pt3 object files.
#	  <SMG3>	 9/29/93	chp		Add Grand Central HBA to the build.
#	  <SMG2>	 9/22/93	chp		Add UniversalEqu.a to dependency list for HALc96Routines.
#	  <SM12>	10/14/93	pdw		<MC> roll-in.
#	   <MC4>	10/12/93	pdw		Whoot theh it is. Fixed the build.
#	   <MC3>	10/12/93	pdw		Added support for Synchronous data transfers, rewrote State
#									Machine, message handling etc.
#	   <MC2>	 9/26/93	pdw		Added start.h to XPT.c dep.
#	  <SM11>	  9/9/93	pdw		Lots of little changes.  Name changes, temporary cache_bug
#									stuff.
#	  <SM10>	 7/17/93	pdw		Added HALc96AMIC.c to build.
#	   <SM9>	 6/29/93	pdw		Once again, changing SCSIMgr4pt3 to SCSI4pt3Dir.  AAArrrggghh!
#	   <SM8>	 6/29/93	pdw		Updating dependencies.
#	   <SM7>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
#									stack switching mechanism.  Adding support for Cold Fusion.
#									Rearranging HW/SW Init code. Some code optimizations.
#	   <SM6>	 5/29/93	PW		Changing SCSIMgr4pt3Dir to SCSI4pt3Dir.
#	   <SM5>	 5/29/93	PW		Updating to match state of sources.
#	   <SM4>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
#									from Ludwig stuff.
#	   <SM3>	  4/8/93	DCB		Added Halc96BIOS.a to support Wombats.
#	   <SM2>	 3/20/93	PW		Added HALc96DMA.a and HALc96AMIC.a.


SCSI4pt3Objects =				"{ObjDir}BootItt.a.o"				∂
								"{ObjDir}HALc96.a.o"				∂
								"{ObjDir}HALc96Data.a.o"			∂
								"{ObjDir}HALc96HWInit.a.o"			∂
								"{ObjDir}HALc96Init.a.o"			∂
								"{ObjDir}HALc96DMA.a.o"				∂
								"{ObjDir}HALc96AMIC.a.o"			∂
								"{ObjDir}HALc96BIOS.a.o"			∂
								"{ObjDir}HALc96GC.a.o"				∂
								"{ObjDir}HALc96PSC.a.o"				∂
								"{ObjDir}HALc96Routines.a.o"		∂
								"{ObjDir}QueueUtils.a.o"			∂
								"{ObjDir}Recorder.a.o"				∂
								"{ObjDir}SCSIGlue.a.o"				∂
								"{ObjDir}SIMmachine.a.o"			∂
								"{ObjDir}timeout.a.o"				∂
								"{ObjDir}XPT.a.o"					∂
								"{ObjDir}XPTSCSIXlate.a.o"			∂
								"{ObjDir}BootItt.c.o"				∂
								"{ObjDir}HALc96.c.o"				∂
								"{ObjDir}HALc96AMIC.c.o"			∂
								"{ObjDir}HALc96GC.c.o"				∂
								"{ObjDir}HALc96PSC.c.o"				∂
								"{ObjDir}InitItt.c.o"				∂
								"{ObjDir}SIMCore.c.o"				∂
								"{ObjDir}SIMCore.a.o"				∂
								"{ObjDir}SIMmachine.c.o"			∂
								"{ObjDir}SIMQ.c.o"					∂
								"{ObjDir}Timeout.c.o"				∂
								"{ObjDir}XPT.c.o"					∂
								"{ObjDir}XPTfunctions.c.o"			∂
								"{ObjDir}XPToldCall.c.o"


"{LibDir}SCSI4pt3.lib"	ƒ	{SCSI4pt3Objects}
	Lib {StdLibOpts} ∂
#		-sn "Main=%A5Init"				∂
#		-sn "_DataInit=%A5Init"			∂
#		-sn "INTENV=%A5Init"			∂
		-o "{Targ}" {SCSI4pt3Objects}


"{ObjDir}BootItt.a.o"		ƒ	"{ObjDir}StandardEqu.d"		∂
								"{SCSI4pt3Dir}Debug.a"		∂
								"{AIncludes}SCSI.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{SCSI4pt3Dir}BootItt.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}BootItt.a"


"{ObjDir}HALc96.a.o"		ƒ	"{AIncludes}SysEqu.a"		∂
								"{AIncludes}SysErr.a"		∂
								"{SCSI4pt3Dir}Debug.a"		∂
								"{AIncludes}SCSI.a"		∂
								"{SCSI4pt3Dir}SCSIEqu53c96.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{SCSI4pt3Dir}SIMCoreEqu.a"		∂
								"{SCSI4pt3Dir}HALc96equ.a"		∂
								"{SCSI4pt3Dir}HALc96.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}HALc96.a"


"{ObjDir}HALc96AMIC.a.o"		ƒ	"{SCSI4pt3Dir}Debug.a"		∂
								"{AIncludes}SCSI.a"		∂
								"{SCSI4pt3Dir}SCSIEqu53c96.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{SCSI4pt3Dir}SIMCoreEqu.a"		∂
								"{SCSI4pt3Dir}HALc96equ.a"		∂
								"{SCSI4pt3Dir}HALc96AMIC.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}HALc96AMIC.a"


"{ObjDir}HALc96BIOS.a.o"		ƒ	"{AIncludes}SysErr.a"		∂
								"{AIncludes}SysEqu.a"		∂
								"{IntAIncludes}HardwarePrivateEqu.a"		∂
								"{IntAIncludes}MC680x0.a"		∂
								"{SCSI4pt3Dir}Debug.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{AIncludes}SCSI.a"		∂
								"{SCSI4pt3Dir}XPTEqu.a"		∂
								"{SCSI4pt3Dir}SCSIEqu53c96.a"		∂
								"{SCSI4pt3Dir}SIMCoreEqu.a"		∂
								"{SCSI4pt3Dir}HALc96equ.a"		∂
								"{SCSI4pt3Dir}HALc96BIOS.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}HALc96BIOS.a"


"{ObjDir}HALc96Data.a.o"		ƒ	"{AIncludes}SysErr.a"		∂
								"{SCSI4pt3Dir}Debug.a"		∂
								"{AIncludes}SCSI.a"		∂
								"{SCSI4pt3Dir}SCSIEqu53c96.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{SCSI4pt3Dir}SIMCoreEqu.a"		∂
								"{SCSI4pt3Dir}XPTEqu.a"		∂
								"{SCSI4pt3Dir}HALc96equ.a"		∂
								"{SCSI4pt3Dir}HALc96Data.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}HALc96Data.a"


"{ObjDir}HALc96DMA.a.o"		ƒ	"{AIncludes}SysErr.a"		∂
								"{SCSI4pt3Dir}Debug.a"		∂
								"{AIncludes}SCSI.a"		∂
								"{SCSI4pt3Dir}SCSIEqu53c96.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{SCSI4pt3Dir}SIMCoreEqu.a"		∂
								"{SCSI4pt3Dir}HALc96equ.a"		∂
								"{SCSI4pt3Dir}HALc96DMA.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}HALc96DMA.a"


"{ObjDir}HALc96GC.a.o"		ƒ	"{SCSI4pt3Dir}HALc96GC.a"				∂
								"{AIncludes}DBDMA.a"					∂
								"{SCSI4pt3Dir}HALc96equ.a"				∂
								"{IntAIncludes}GrandCentralPriv.a"
	Asm -case on {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}HALc96GC.a"


"{ObjDir}HALc96HWInit.a.o"		ƒ	"{ObjDir}StandardEqu.d"		∂
								"{IntAIncludes}HardwarePrivateEqu.a"		∂
								"{IntAIncludes}UniversalEqu.a"		∂
								"{SCSI4pt3Dir}Debug.a"		∂
								"{AIncludes}SCSI.a"		∂
								"{SCSI4pt3Dir}SCSIEqu53c96.a"		∂
								"{SCSI4pt3Dir}HALc96equ.a"		∂
								"{SCSI4pt3Dir}HALc96HWInit.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}HALc96HWInit.a"


"{ObjDir}HALc96Init.a.o"		ƒ	"{SCSI4pt3Dir}Debug.a"		∂
								"{AIncludes}SCSI.a"		∂
								"{SCSI4pt3Dir}SCSIEqu53c96.a"		∂
								"{SCSI4pt3Dir}HALc96equ.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{SCSI4pt3Dir}HALc96Init.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}HALc96Init.a"


"{ObjDir}HALc96PSC.a.o"		ƒ	"{ObjDir}StandardEqu.d"		∂
								"{AIncludes}HardwareEqu.a"		∂
								"{IntAIncludes}UniversalEqu.a"		∂
								"{SCSI4pt3Dir}Debug.a"		∂
								"{AIncludes}SCSI.a"		∂
								"{SCSI4pt3Dir}SCSIEqu53c96.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{SCSI4pt3Dir}SIMCoreEqu.a"		∂
								"{SCSI4pt3Dir}HALc96equ.a"		∂
								"{IntAIncludes}PSCequ.a"		∂
								"{SCSI4pt3Dir}HALc96PSC.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}HALc96PSC.a"


"{ObjDir}HALc96Routines.a.o"		ƒ	"{ObjDir}StandardEqu.d"		∂
								"{IntAIncludes}HardwarePrivateEqu.a"		∂
								"{IntAIncludes}UniversalEqu.a"			∂
								"{IntAIncludes}MC680x0.a"		∂
								"{SCSI4pt3Dir}Debug.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{AIncludes}SCSI.a"		∂
								"{SCSI4pt3Dir}XPTEqu.a"		∂
								"{SCSI4pt3Dir}SCSIEqu53c96.a"		∂
								"{SCSI4pt3Dir}SIMCoreEqu.a"		∂
								"{SCSI4pt3Dir}HALc96equ.a"		∂
								"{SCSI4pt3Dir}HALc96Routines.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}HALc96Routines.a"


"{ObjDir}IttInit.a.o"		ƒ	"{ObjDir}StandardEqu.d"		∂
								"{IntAIncludes}HardwarePrivateEqu.a"		∂
								"{IntAIncludes}UniversalEqu.a"		∂
								"{AIncludes}SCSI.a"		∂
								"{SCSI4pt3Dir}Debug.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{SCSI4pt3Dir}XPTEqu.a"		∂
								"{SCSI4pt3Dir}IttInit.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}IttInit.a"


"{ObjDir}QueueUtils.a.o"		ƒ	"{ObjDir}StandardEqu.d"		∂
								"{SCSI4pt3Dir}Debug.a"		∂
								"{SCSI4pt3Dir}QueueUtils.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}QueueUtils.a"


"{ObjDir}Recorder.a.o"		ƒ	"{ObjDir}StandardEqu.d"		∂
								"{SCSI4pt3Dir}Debug.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{SCSI4pt3Dir}XPTEqu.a"		∂
								"{SCSI4pt3Dir}Recorder.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}Recorder.a"


"{ObjDir}SCSIGlue.a.o"		ƒ	"{ObjDir}StandardEqu.d"		∂
								"{IntAIncludes}HardwarePrivateEqu.a"		∂
								"{IntAIncludes}UniversalEqu.a"		∂
								"{SCSI4pt3Dir}Debug.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{AIncludes}SCSI.a"			∂
								"{SCSI4pt3Dir}XPTEqu.a"		∂
								"{SCSI4pt3Dir}SCSIGlue.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}SCSIGlue.a"


"{ObjDir}SIMmachine.a.o"		ƒ	"{AIncludes}SysEqu.a"	∂
								"{AIncludes}Traps.a"		∂
								"{SCSI4pt3Dir}Debug.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{SCSI4pt3Dir}HALc96equ.a"	∂
								"{SCSI4pt3Dir}SIMmachine.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}SIMmachine.a"


"{ObjDir}SIMCore.a.o"		ƒ	"{SCSI4pt3Dir}Debug.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{SCSI4pt3Dir}SIMCoreEqu.a"	∂
								"{SCSI4pt3Dir}HALc96equ.a"	∂
								"{SCSI4pt3Dir}SIMCore.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}SIMCore.a"


"{ObjDir}timeout.a.o"		ƒ	"{SCSI4pt3Dir}Debug.a"		∂
								"{SCSI4pt3Dir}timeout.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}timeout.a"


"{ObjDir}XPT.a.o"		ƒ	"{ObjDir}StandardEqu.d"		∂
								"{SCSI4pt3Dir}Debug.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{SCSI4pt3Dir}XPTEqu.a"		∂
								"{SCSI4pt3Dir}XPT.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}XPT.a"


"{ObjDir}XPTSCSIXlate.a.o"		ƒ	"{ObjDir}StandardEqu.d"		∂
								"{SCSI4pt3Dir}Debug.a"		∂
								"{AIncludes}SCSI.a"		∂
								"{SCSI4pt3Dir}ACAM.a"		∂
								"{SCSI4pt3Dir}XPTEqu.a"		∂
								"{SCSI4pt3Dir}HALc96equ.a"		∂
								"{SCSI4pt3Dir}XPTSCSIXlate.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSI4pt3Dir}XPTSCSIXlate.a"


"{ObjDir}BootItt.c.o"		ƒ	"{CIncludes}Devices.h"		∂
								"{CIncludes}Types.h"		∂
								"{CIncludes}Traps.h"		∂
								"{IntCIncludes}TrapsPrivate.h"	∂
								"{CIncludes}Packages.h"		∂
								"{CIncludes}Memory.h"		∂
								"{CIncludes}SysEqu.h"		∂
								"{CIncludes}SCSIStandard.h"		∂
								"{CIncludes}SCSI.h"		∂
								"{CIncludes}OSUtils.h"		∂
								"{CIncludes}Devices.h"		∂
								"{CIncludes}Slots.h"		∂
								"{CIncludes}Start.h"		∂
								"{SCSI4pt3Dir}StandardGlue.h"		∂
								"{SCSI4pt3Dir}SCSIDebug.h"		∂
								"{SCSI4pt3Dir}ACAM.h"		∂
								"{SCSI4pt3Dir}XPT.h"		∂
								"{SCSI4pt3Dir}XPTpriv.h"		∂
								"{SCSI4pt3Dir}BootItt.h"		∂
								"{SCSI4pt3Dir}BootItt.c"
	C {StdCOpts} -o "{Targ}" "{SCSI4pt3Dir}BootItt.c"


"{ObjDir}HALc96.c.o"		ƒ	"{CIncludes}Types.h"		∂
								"{CIncludes}Memory.h"		∂
								"{CIncludes}Errors.h"		∂
								"{CIncludes}SCSIStandard.h"		∂
								"{CIncludes}SCSI.h"		∂
								"{SCSI4pt3Dir}ACAM.h"		∂
								"{SCSI4pt3Dir}XPT.h"		∂
								"{SCSI4pt3Dir}XPTpriv.h"		∂
								"{SCSI4pt3Dir}SIMCore.h"		∂
								"{SCSI4pt3Dir}SIMCorePriv.h"		∂
								"{SCSI4pt3Dir}HALc96.h"		∂
								"{SCSI4pt3Dir}HALc96.c"
	C {StdCOpts} -o "{Targ}" "{SCSI4pt3Dir}HALc96.c"


"{ObjDir}HALc96AMIC.c.o"	ƒ	"{CIncludes}Types.h"		∂
								"{CIncludes}Traps.h"		∂
								"{IntCIncludes}TrapsPrivate.h"	∂
								"{CIncludes}Memory.h"		∂
								"{CIncludes}Errors.h"		∂
								"{CIncludes}SCSI.h"		∂
								"{CIncludes}SCSIStandard.h"		∂
								"{SCSI4pt3Dir}ACAM.h"		∂
								"{SCSI4pt3Dir}SIMCore.h"		∂
								"{SCSI4pt3Dir}HALc96.h"		∂
								"{SCSI4pt3Dir}SIMCorePriv.h"		∂
								"{SCSI4pt3Dir}HALc96AMIC.c"
	C {StdCOpts} -o "{Targ}" "{SCSI4pt3Dir}HALc96AMIC.c"


"{ObjDir}HALc96GC.c.o"		ƒ	"{SCSI4pt3Dir}HALc96GC.c"				∂
								"{SCSI4pt3Dir}SIMCorePriv.h"			∂
								"{CIncludes}SCSI.h"						∂
								"{SCSI4pt3Dir}SIMCore.h"				∂
								"{CIncludes}Memory.h"					∂
								"{CIncludes}Timer.h"					∂
								"{CIncludes}OSUtils.h"					∂
								"{SCSI4pt3Dir}ACAM.h"					∂
								"{CIncludes}Types.h"					∂
								"{CIncludes}Traps.h"					∂
								"{SCSI4pt3Dir}HALc96.h"
	C {StdCOpts} -o "{Targ}" "{SCSI4pt3Dir}HALc96GC.c"


"{ObjDir}HALc96PSC.c.o"		ƒ	"{CIncludes}Types.h"		∂
								"{CIncludes}Memory.h"		∂
								"{CIncludes}Errors.h"		∂
								"{CIncludes}SCSI.h"		∂
								"{CIncludes}SCSIStandard.h"		∂
								"{SCSI4pt3Dir}ACAM.h"		∂
								"{SCSI4pt3Dir}SIMCore.h"		∂
								"{SCSI4pt3Dir}HALc96.h"		∂
								"{SCSI4pt3Dir}SIMCorePriv.h"		∂
								"{SCSI4pt3Dir}HALc96PSC.c"
	C {StdCOpts} -o "{Targ}" "{SCSI4pt3Dir}HALc96PSC.c"


"{ObjDir}InitItt.c.o"		ƒ	"{CIncludes}SysEqu.h"		∂
								"{CIncludes}Memory.h"		∂
								"{CIncludes}Start.h"		∂
								"{CIncludes}SCSIStandard.h"		∂
								"{CIncludes}GestaltEqu.h"		∂
								"{IntCIncludes}GestaltPrivateEqu.h"		∂
								"{IntCIncludes}GrandCentralPriv.h"		∂
								"{SCSI4pt3Dir}SCSIDebug.h"		∂
								"{SCSI4pt3Dir}ACAM.h"		∂
								"{SCSI4pt3Dir}XPT.h"		∂
								"{SCSI4pt3Dir}SIMCore.h"		∂
								"{SCSI4pt3Dir}HALc96.h"		∂
								"{SCSI4pt3Dir}SCSIGlue.h"		∂
								"{SCSI4pt3Dir}XPTPriv.h"		∂
								"{SCSI4pt3Dir}InitItt.c"
	C {StdCOpts} -o "{Targ}" "{SCSI4pt3Dir}InitItt.c"


"{ObjDir}SIMCore.c.o"		ƒ	"{CIncludes}Types.h"					∂
								"{CIncludes}Traps.h"					∂
								"{CIncludes}Errors.h"					∂
								"{CIncludes}Memory.h"					∂
								"{CIncludes}Timer.h"					∂
								"{CIncludes}SCSI.h"						∂
								"{CIncludes}SCSIStandard.h"				∂
								"{SCSI4pt3Dir}ACAM.h"					∂
								"{SCSI4pt3Dir}XPT.h"					∂
								"{SCSI4pt3Dir}CUtils.h"					∂
								"{SCSI4pt3Dir}SIMCore.h"				∂
								"{SCSI4pt3Dir}SIMCorePriv.h"			∂
								"{SCSI4pt3Dir}SIMQ.h"					∂
								"{SCSI4pt3Dir}SCSIGlue.h"				∂
								"{SCSI4pt3Dir}HALc96.h"					∂
								"{SCSI4pt3Dir}SCSIDebug.h"				∂
								"{SCSI4pt3Dir}Recorder.h"				∂
								"{SCSI4pt3Dir}SIMCore.c"
	C {StdCOpts} -o "{Targ}" "{SCSI4pt3Dir}SIMCore.c"


"{ObjDir}SIMmachine.c.o"		ƒ	"{CIncludes}Types.h"		∂
								"{CIncludes}Memory.h"		∂
								"{CIncludes}Errors.h"		∂
								"{CIncludes}SCSIStandard.h"		∂
								"{CIncludes}SCSI.h"		∂
								"{SCSI4pt3Dir}ACAM.h"		∂
								"{SCSI4pt3Dir}XPT.h"		∂
								"{SCSI4pt3Dir}XPTpriv.h"		∂
								"{SCSI4pt3Dir}CUtils.h"		∂
								"{SCSI4pt3Dir}SCSIGlue.h"		∂
								"{SCSI4pt3Dir}SIMCore.h"		∂
								"{SCSI4pt3Dir}SIMCorePriv.h"		∂
								"{SCSI4pt3Dir}SIMQ.h"		∂
								"{SCSI4pt3Dir}SCSIDebug.h"		∂
								"{SCSI4pt3Dir}Recorder.h"		∂
								"{SCSI4pt3Dir}SIMmachine.c"
	C {StdCOpts} -o "{Targ}" "{SCSI4pt3Dir}SIMmachine.c"


"{ObjDir}SIMQ.c.o"		ƒ	"{CIncludes}Types.h"		∂
								"{CIncludes}Memory.h"		∂
								"{CIncludes}Errors.h"		∂
								"{CIncludes}SCSIStandard.h"		∂
								"{CIncludes}SCSI.h"		∂
								"{SCSI4pt3Dir}ACAM.h"		∂
								"{SCSI4pt3Dir}CUtils.h"		∂
								"{SCSI4pt3Dir}QueueUtils.h"		∂
								"{SCSI4pt3Dir}XPT.h"		∂
								"{SCSI4pt3Dir}XPTpriv.h"		∂
								"{SCSI4pt3Dir}SIMCore.h"		∂
								"{SCSI4pt3Dir}SIMCorePriv.h"		∂
								"{SCSI4pt3Dir}SIMQ.h"		∂
								"{SCSI4pt3Dir}SCSIDebug.h"		∂
								"{SCSI4pt3Dir}Recorder.h"		∂
									"{SCSI4pt3Dir}SIMQ.c"
	C {StdCOpts} -o "{Targ}" "{SCSI4pt3Dir}SIMQ.c"


"{ObjDir}Timeout.c.o"		ƒ	"{CIncludes}Types.h"		∂
								"{CIncludes}Packages.h"		∂
								"{CIncludes}Memory.h"		∂
								"{CIncludes}SCSIStandard.h"		∂
								"{CIncludes}SCSI.h"		∂
								"{SCSI4pt3Dir}ACAM.h"		∂
								"{SCSI4pt3Dir}Recorder.h"		∂
								"{SCSI4pt3Dir}SIMCore.h"		∂
								"{SCSI4pt3Dir}SIMCorePriv.h"		∂
								"{SCSI4pt3Dir}SIMQ.h"		∂
								"{SCSI4pt3Dir}Timeout.c"
	C {StdCOpts} -o "{Targ}" "{SCSI4pt3Dir}Timeout.c"


"{ObjDir}XPT.c.o"		ƒ	"{CIncludes}Types.h"		∂
								"{CIncludes}Memory.h"		∂
								"{CIncludes}OSUtils.h"		∂
								"{CIncludes}Errors.h"		∂
								"{CIncludes}SCSIStandard.h"		∂
								"{CIncludes}SCSI.h"		∂
								"{CIncludes}Slots.h"		∂
								"{SCSI4pt3Dir}ACAM.h"		∂
								"{SCSI4pt3Dir}SCSIDebug.h"		∂
								"{SCSI4pt3Dir}SCSIGlue.h"		∂
								"{SCSI4pt3Dir}SIMCore.h"		∂
								"{SCSI4pt3Dir}BootItt.h"		∂
								"{SCSI4pt3Dir}XPT.h"		∂
								"{SCSI4pt3Dir}XPTpriv.h"		∂
								"{SCSI4pt3Dir}Recorder.h"		∂
								"{SCSI4pt3Dir}XPT.c"
	C {StdCOpts} -o "{Targ}" "{SCSI4pt3Dir}XPT.c"


"{ObjDir}XPTfunctions.c.o"		ƒ	"{CIncludes}Types.h"		∂
								"{CIncludes}Memory.h"		∂
								"{SCSI4pt3Dir}ACAM.h"		∂
								"{SCSI4pt3Dir}XPT.h"		∂
								"{SCSI4pt3Dir}XPTfunctions.c"
	C {StdCOpts} -o "{Targ}" "{SCSI4pt3Dir}XPTfunctions.c"


"{ObjDir}XPToldCall.c.o"		ƒ	"{CIncludes}Types.h"		∂
								"{CIncludes}Memory.h"		∂
								"{CIncludes}OSUtils.h"		∂
								"{CIncludes}SCSIStandard.h"		∂
								"{CIncludes}SCSI.h"		∂
								"{SCSI4pt3Dir}ACAM.h"		∂
								"{SCSI4pt3Dir}SCSIDebug.h"		∂
								"{SCSI4pt3Dir}CUtils.h"		∂
								"{SCSI4pt3Dir}XPT.h"		∂
								"{SCSI4pt3Dir}XPTpriv.h"		∂
								"{SCSI4pt3Dir}XPToldCall.c"
	C {StdCOpts} -o "{Targ}" "{SCSI4pt3Dir}XPToldCall.c"



#	……………………………………………………………………………………………………………………………………………………………………………………………………………………
#
#	Use optional target dependencies for building Itt as a script system extension:
#
#	Build -p -d forIttInit=TRUE RISC "{Sources}BuildResults:RISC:Image:IttExtension"
#
#	……………………………………………………………………………………………………………………………………………………………………………………………………………………


IttExtension =			IttExtension

BootIttObjects = 		{ObjDir}BootItt.c.o			∂
						{ObjDir}BootItt.a.o			

XPTObjects =			{ObjDir}SCSIGlue.a.o		∂
						{ObjDir}XPT.c.o				∂
						{ObjDir}XPT.a.o				∂
						{ObjDir}XPToldCall.c.o		∂
						{ObjDir}XPTfunctions.c.o	∂
						{ObjDir}XPTSCSIXlate.a.o	∂
						{ObjDir}Queue.a.o			

SIMObjects =			{ObjDir}SIMCore.c.o			∂
						{ObjDir}SIMCore.a.o			∂
						{ObjDir}SIMQ.c.o 			∂
						{ObjDir}SIMmachine.c.o 		∂
						{ObjDir}SIMmachine.a.o 		∂
						{ObjDir}QueueUtils.a.o		∂
						{ObjDir}Timeout.c.o			∂
						{ObjDir}Timeout.a.o

HALObjects =			{ObjDir}HALc96.c.o			∂
						{ObjDir}HALc96.a.o			∂
						{ObjDir}HALc96Data.a.o		∂
						{ObjDir}HALc96BIOS.a.o		∂
						{ObjDir}HALc96Routines.a.o	∂
						{ObjDir}HALc96Init.a.o		∂
						{ObjDir}HALc96HWInit.a.o	∂
						{ObjDir}HALc96DMA.a.o		∂
						{ObjDir}HALc96AMIC.a.o		∂
						{ObjDir}HALc96PSC.a.o		∂
						{ObjDir}HALc96GC.c.o		∂
						{ObjDir}HALc96AMIC.c.o		∂
						{ObjDir}HALc96PSC.c.o		∂
						{ObjDir}HALc96GC.a.o


IttExtensionObjects =	{ObjDir}IttInit.a.o			∂
						{HALObjects}				∂
						{ObjDir}Recorder.a.o		∂
						{ObjDir}InitItt.c.o			∂
						{XPTObjects}  				∂
						{SIMObjects}				∂
						{BootIttObjects}


"{ImageDir}{IttExtension}"		ƒƒ	{SCSI4pt3Dir}SCSIMgr4pt3.make {IttExtensionObjects}
	Link {IttExtensionObjects} {IfObjDir}Interface.o											∂
		-rt 'INIT'=96 -sg IttExtension -ra IttExtension=resSysHeap,resLocked					∂
		-o {Targ} -t 'scri' -c 'woof'

"{ImageDir}{IttExtension}"		ƒƒ	{SCSI4pt3Dir}SCSIMgr4pt3.make
	Echo 'data '∂''sysz'∂'' (0) {$"00100000"};' | Rez -append -o {Targ} 


CleanSCSI						ƒ
	Delete -i {IttExtensionObjects} "{ImageDir}{IttExtension}" ≥ Dev:Null
