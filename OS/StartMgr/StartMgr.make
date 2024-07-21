#
#	File:		StartMgr.make
#
#	Contains:	Makefile for main code image.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM9>	11/10/93	chp		Made StartInit.a.o dependent on RISC.make so version changes get
#									rebuilt.
#	   <SM8>	10/14/93	pdw		Added some dependencies.
#	   <SM7>	  9/9/93	pdw		Fixed up dependencies - slots.a and some others.
#	   <SM6>	  8/4/93	JDR		USTNonCritTsts.a depends on SoundPrivate.a
#	   <SM5>	  8/4/93	JDR		Integrate sound manager 3.0 project.
#	   <SM4>	 7/21/93	SAM		Bdah, ah, put ExceptionSupport.a back in.
#	   <SM3>	 7/20/93	SAM		Remove build rules for ExceptionSupport.a and
#									StartSystemPatches.a.
#	   <SM2>	 6/14/93	kc		Roll in Ludwig.
#	   <LW2>	  5/3/93	chp		Added SuperMario.make to StartInit.a.o dependency list since
#									StartInit.a.o depends explicitly on variables defined in the
#									makefile.
#	   <SM3>	 12/9/92	mal		Updated StartInit.a's dependencies.
#	   <SM2>	 12/2/92	kc		Added " || Exit 1" to commands with a double dependency.

StartMgrObjs			=	"{ObjDir}StartTop.a.o"								¶
							"{ObjDir}StartInit.a.o"								¶
							"{ObjDir}StartSearch.a.o"							¶
							"{ObjDir}StartBoot.a.o"								¶
							"{ObjDir}StartFail.a.o"								¶
							"{ObjDir}StartErr.a.o"								¶
							"{ObjDir}StartAlert.a.o"


StartTestObjs			=	"{ObjDir}USTStartTest.a.o"							¶
							"{ObjDir}ExceptionSupport.a.o"						¶
							"{ObjDir}UTEKernel.c.o"								¶
							"{ObjDir}SONIC_Test.c.o"							¶
							"{ObjDir}SizeMem.a.o"


Boot3Objects			=	"{ObjDir}Boot3.a.o"									¶
							"{ObjDir}DispatchPatch.a.o"


"{RsrcDir}Gibbly.rsrc"		ÄÄ	"{StartDir}Gibbly.r"
	Rez {StdROpts} -a -o "{targ}" -d ROMBuildTime="{ROMBuildTime}" "{StartDir}Gibbly.r" || Exit 1

"{RsrcDir}Gibbly.rsrc"		ÄÄ	{Boot3Objects}
	Link {StdLOpts} {StdAlign} -o "{Targ}" {Boot3Objects} -rt 'boot=3' -ra =resSysHeap,resLocked || Exit 1

"{LibDir}StartMgr.lib"		Ä	{StartMgrObjs}
	Lib {StdLibOpts}	{StartMgrObjs} -o "{Targ}"


"{LibDir}StartTest.lib"		Ä	{StartTestObjs}
	Lib {StdLibOpts}	{StartTestObjs} -o "{Targ}"


"{ObjDir}StartAlert.a.o"	Ä	"{ObjDir}StandardEqu.d"							¶
								"{AIncludes}HardwareEqu.a"						¶
								"{StartDir}StartAlert.a"
	Asm {StdAOpts} -o "{Targ}" "{StartDir}StartAlert.a"


"{ObjDir}StartBoot.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
								"{IntAIncludes}HardwarePrivateEqu.a"			¶
								"{IntAIncludes}UniversalEqu.a"					¶
								"{AIncludes}FixMath.a"							¶
								"{AIncludes}Slots.a"							¶
								"{IntAIncludes}SlotMgrEqu.a"					¶
								"{AIncludes}ROMEqu.a"							¶
								"{IntAIncludes}ColorEqu.a"						¶
								"{AIncludes}Aliases.a"							¶
								"{AIncludes}Displays.a"							¶
								"{IntAIncludes}DisplaysPriv.a"					¶
								"{AIncludes}GestaltEqu.a"						¶
								"{IntAIncludes}AtalkPrivateEQU.a"				¶
								"{IntAIncludes}EDiskEqu.a"						¶
								"{IntAIncludes}MMUEqu.a"						¶
								"{IntAincludes}BootEqu.a"						¶
								"{StartDir}StartBoot.a"
	Asm {StdAOpts} -o "{Targ}" "{StartDir}StartBoot.a"


"{ObjDir}StartErr.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
								"{IntAIncludes}HardwarePrivateEqu.a"			¶
								"{IntAIncludes}UniversalEqu.a"					¶
								"{IntAIncludes}MMUEqu.a"						¶
								"{IntAincludes}BootEqu.a"						¶
								"{StartDir}StartErr.a"
	Asm {StdAOpts} -o "{Targ}" "{StartDir}StartErr.a"


"{ObjDir}StartFail.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
								"{AIncludes}HardwareEqu.a"						¶
								"{AIncludes}Slots.a"							¶
								"{IntAIncludes}SlotMgrEqu.a"					¶
								"{AIncludes}ROMEqu.a"							¶
								"{AIncludes}Video.a"							¶
								"{StartDir}StartFail.a"
	Asm {StdAOpts} -o "{Targ}" "{StartDir}StartFail.a"


"{ObjDir}StartTop.a.o"		Ä	"{StartDir}StartTop.a"
	Asm {StdAOpts} -o "{Targ}" "{StartDir}StartTop.a"


"{ObjDir}StartInit.a.o"		Ä	"{MakeDir}Universal.make"						¶
								"{MakeDir}RISC.make"							¶
								"{ObjDir}StandardEqu.d"							¶
								"{IntAIncludes}HardwarePrivateEqu.a"			¶
								"{MemoryMgrDir}MemoryMgrPriv.a"					¶
								"{AIncludes}SCSI.a"								¶
								"{IntAIncludes}MMUEqu.a"						¶
								"{IntAincludes}BootEqu.a"						¶
								"{AIncludes}ROMEqu.a"							¶
								"{AIncludes}Slots.a"							¶
								"{IntAIncludes}SlotMgrEqu.a"					¶
								"{AIncludes}Video.a"							¶
								"{IntAincludes}DepVideoEqu.a"					¶
								"{IntAIncludes}ColorEqu.a"						¶
								"{IntAIncludes}UniversalEqu.a"					¶
								"{IntAIncludes}ReliabilityEqu.a"				¶
								"{IntAIncludes}EgretEqu.a"						¶
								"{IntAIncludes}EDiskEqu.a"						¶
								"{IntAIncludes}SCSIEqu96.a"						¶
								"{IntAIncludes}PowerPrivEqu.a"					¶
								"{IntAIncludes}PSCEqu.a"						¶
								"{AIncludes}GestaltEqu.a"						¶
								"{IntAIncludes}GestaltPrivateEqu.a"				¶
								"{AIncludes}AppleTalk.a"						¶
								"{IntAIncludes}AtalkPrivateEQU.a"				¶
								"{StartDir}StartInit.a"
# Both part of StandardEqu.d
#								"{AIncludes}FSEqu.a"							¶
#								"{AIncludes}FSPrivate.a"						¶
	Asm {StdAOpts} -o "{Targ}" "{StartDir}StartInit.a" -i "{MemoryMgrDir}"


"{ObjDir}StartSearch.a.o"	Ä	"{ObjDir}StandardEqu.d"							¶
								"{IntAIncludes}HardwarePrivateEqu.a"			¶
								"{IntAIncludes}UniversalEqu.a"					¶
								"{AIncludes}Devices.a"							¶
								"{IntAIncludes}PowerPrivEqu.a"					¶
								"{AIncludes}Slots.a"							¶
								"{IntAIncludes}SlotMgrEqu.a"					¶
								"{AIncludes}ROMEqu.a"							¶
								"{AIncludes}SCSI.a"								¶
								"{StartDir}StartSearch.a"
	Asm {StdAOpts} -o "{Targ}" "{StartDir}StartSearch.a"


"{ObjDir}SizeMem.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
								"{IntAIncludes}HardwarePrivateEqu.a"			¶
								"{AIncludes}HardwareEqu.a"						¶
								"{IntAIncludes}UniversalEqu.a"					¶
								"{StartDir}STEqu.a"								¶
								"{IntAIncludes}MMUEqu.a"						¶
								"{IntAincludes}BootEqu.a"						¶
								"{StartDir}SizeMem.a"
	Asm {StdAOpts} -o "{Targ}" "{StartDir}SizeMem.a"


"{ObjDir}USTStartTest.a.o"	Ä	"{StartDir}STEqu.a"								¶
								"{AIncludes}HardwareEqu.a"						¶
								"{IntAIncludes}BootEqu.a"						¶
								"{ObjDir}StandardEqu.d"							¶
								"{IntAIncludes}HardwarePrivateEqu.a"			¶
								"{IntAIncludes}SoundPrivate.a"					¶
								"{IntAIncludes}MMUEqu.a"						¶
								"{IntAIncludes}UniversalEqu.a"					¶
								"{IntAIncludes}PowerPrivEqu.a"					¶
								"{IntAIncludes}EgretEqu.a"						¶
								"{IntAIncludes}SCSIEqu96.a"						¶
								"{IntAIncludes}IOPrimitiveEqu.a"				¶
								"{StartDir}USTStartUp.a"						¶
								"{StartDir}USTCritTests.a"						¶
								"{StartDir}USTNonCritTsts.a"					¶
								"{StartDir}USTPostProc.a"						¶
								"{StartDir}USTPram.a"							¶
								"{StartDir}USTTestMgr.a"						¶
								"{StartDir}USTMacros.a"							¶
								"{StartDir}USTSubtests.a"						¶
								"{StartDir}USTEnvirons.a"						¶
								"{StartDir}SubtestController.a"					¶
								"{StartDir}GenericInterface.a"					¶
								"{StartDir}StdMacros.a"							¶
								"{StartDir}USTStartTest.a"
	Asm {StdAOpts} -o "{Targ}" "{StartDir}USTStartTest.a"


"{ObjDir}ExceptionSupport.a.o" Ä "{StartDir}ExceptionSupport.a"					¶
								"{StartDir}ExceptionSupport.a"					¶
								"{StartDir}STDMacros.a"							¶
								"{StartDir}USTMacros.a"
	Asm {StdAOpts} -o "{Targ}" "{StartDir}IncludeExceptionSupport.a"


"{ObjDir}UTEKernel.c.o"				Ä	"{StartDir}UnivTestEnv:BitWalk.c"			¶
										"{StartDir}UnivTestEnv:ExceptionSupport.c"	¶
										"{StartDir}UnivTestEnv:GenericInterface.c"	¶
										"{StartDir}UnivTestEnv:Heap.c"				¶
										"{StartDir}UnivTestEnv:List.c"				¶
										"{StartDir}UnivTestEnv:SubtestController.c"	¶
										"{StartDir}UnivTestEnv:TestController.c"	¶
										"{StartDir}UnivTestEnv:UTEKernel.c"			¶
										"{StartDir}UnivTestEnv:68KOpCodes.h"		¶
										"{StartDir}UnivTestEnv:BitWalk.h"			¶
										"{StartDir}UnivTestEnv:CTETypes.h"			¶
										"{StartDir}UnivTestEnv:ExceptionSupport.h"	¶
										"{StartDir}UnivTestEnv:GenericInterface.h"	¶
										"{StartDir}UnivTestEnv:GenericTypes.h"		¶
										"{StartDir}UnivTestEnv:Heap.h"				¶
										"{StartDir}UnivTestEnv:List.h"				¶
										"{StartDir}UnivTestEnv:SubtestController.h"	¶
										"{StartDir}UnivTestEnv:TestController.h"
	C {StdCOpts} -o "{Targ}" "{StartDir}UnivTestEnv:UTEKernel.c"


"{ObjDir}SONIC_Test.c.o"			Ä	"{StartDir}UnivTestEnv:SONIC_Test.c"		¶
										"{StartDir}UnivTestEnv:SupportFunctions.h"	¶
										"{StartDir}UnivTestEnv:CTETypes.h"			¶
										"{StartDir}UnivTestEnv:IDDefs.h"			¶
										"{StartDir}UnivTestEnv:SONIC_Common.h"		¶
										"{StartDir}UnivTestEnv:SONIC_BitMarch.c"	¶
										"{StartDir}UnivTestEnv:SONIC_BitMarch.h"	¶
										"{StartDir}UnivTestEnv:SONIC_CAMDMA.c"		¶
										"{StartDir}UnivTestEnv:SONIC_CAMDMA.h"		¶
										"{StartDir}UnivTestEnv:SONIC_Loopback.c"	¶
										"{StartDir}UnivTestEnv:SONIC_Loopback.h"	¶
										"{StartDir}UnivTestEnv:SONIC_Interrupt.h"	¶
										"{StartDir}UnivTestEnv:SONIC_Interrupt.c"	¶
										"{StartDir}UnivTestEnv:SONIC_Test.h"
	C {StdCOpts} -o "{Targ}" "{StartDir}UnivTestEnv:SONIC_Test.c" -i "{StartDir}UnivTestEnv:"


"{ObjDir}Boot3.a.o"				Ä	"{IntAIncludes}LinkedPatchMacros.a"				¶
									"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}Folders.a"							¶
									"{AIncludes}TextServices.a"						¶
									"{IntAIncludes}BootEqu.a"						¶
									"{IntAIncludes}ScriptPriv.a"					¶
									"{StartDir}Boot3.a"
	Asm {StdAOpts} -d SONYNONPORTABLE=1 -o "{Targ}" "{StartDir}Boot3.a"


"{ObjDir}DispatchPatch.a.o"		Ä 	"{ObjDir}StandardEqu.d"							¶
									"{TrapDispDir}DispatchPatch.a"
	Asm {StdAOpts} -o "{targ}" "{TrapDispDir}DispatchPatch.a"


