#
#	File:		IOPrimitives.make
#
#	Contains:	Makefile for IOPrimitives.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM3>	12/13/93	PN		Roll in KAOs and Horror changes to support Malcom and AJ
#									machines.
#	   <SM2>	  8/4/93	JDR		updated dependencies for ADBPrimitives.a, SndPrimitives.a and
#									PowerMgrPrimitives.a to include SoundPrivate.a



IOPrimitivesObjs	=					"{ObjDir}PowerMgrPrimitives.a.o"			¶
										"{ObjDir}ImmgPrimitives.a.o"				¶
										"{ObjDir}ADBPrimitives.a.o"					¶
										"{ObjDir}ClockPRAMPrimitives.a.o"			¶
										"{ObjDir}backlightprim.a.o"					¶
										"{ObjDir}backlightinput.c.o"									¶
										"{ObjDir}backlightcpu.c.o"										¶
										"{ObjDir}backlightGenRout.c.o"									¶
										"{ObjDir}PWM.c.o"												¶
										"{ObjDir}SndPrimitives.a.o"

"{LibDir}IOPrimitives.lib"		Ä		{IOPrimitivesObjs}
	Lib {StdLibOpts} {IOPrimitivesObjs} -o "{Targ}"


"{ObjDir}ADBPrimitives.a.o"			Ä	"{ObjDir}StandardEqu.d"						¶
										"{IntAIncludes}HardwarePrivateEqu.a"		¶
										"{IntAincludes}UniversalEqu.a"				¶
										"{IntAincludes}SoundPrivate.a"				¶
										"{IntAincludes}PowerPrivEqu.a"				¶
										"{IntAincludes}EgretEqu.a"					¶
										"{IntAincludes}IopEqu.a"					¶
										"{IntAincludes}AppleDeskBusPriv.a"			¶
										"{IntAincludes}IOPrimitiveEqu.a"			¶
										"{IOPrimitivesDir}ADBPrimitives.a"
	Asm {StdAOpts} -o "{Targ}" "{IOPrimitivesDir}ADBPrimitives.a"


"{ObjDir}ClockPRAMPrimitives.a.o"	Ä	"{ObjDir}StandardEqu.d"						¶
										"{IntAIncludes}HardwarePrivateEqu.a"		¶
										"{IntAIncludes}UniversalEqu.a"				¶
										"{IntAIncludes}PowerPrivEqu.a"				¶
										"{IntAIncludes}EgretEqu.a"					¶
										"{IntAIncludes}IOPrimitiveEqu.a"			¶
										"{IOPrimitivesDir}ClockPRAMPrimitives.a"
	Asm {StdAOpts} -o "{Targ}" "{IOPrimitivesDir}ClockPRAMPrimitives.a"


"{ObjDir}PowerMgrPrimitives.a.o"	Ä	"{ObjDir}StandardEqu.d"						¶
										"{IntAIncludes}HardwarePrivateEqu.a"		¶
										"{IntAincludes}SoundPrivate.a"				¶
										"{IntAIncludes}UniversalEqu.a"				¶
										"{IntAIncludes}PowerPrivEqu.a"				¶
										"{IntAIncludes}MMUEqu.a"					¶
										"{IntAIncludes}IOPrimitiveEqu.a"			¶
										"{IntAIncludes}DockingEqu.a"				¶
										"{AIncludes}ShutDown.a"						¶
										"{IOPrimitivesDir}PowerMgrPrimitives.a"
	Asm {StdAOpts} -o "{Targ}" "{IOPrimitivesDir}PowerMgrPrimitives.a"

"{ObjDir}ImmgPrimitives.a.o"		Ä	"{ObjDir}StandardEqu.d"				¶
										"{IntAIncludes}HardwarePrivateEqu.a"		¶
										"{IntAIncludes}UniversalEqu.a"				¶
										"{AIncludes}ROMEqu.a"						¶
										"{IntAIncludes}IOPrimitiveEqu.a"			¶
										"{AIncludes}IntModemMgrEqu.a"				¶
										"{IntAIncludes}IntModemMgrPrivEqu.a"		¶
										"{IntAIncludes}PowerPrivEqu.a"				¶
										"{AIncludes}Sound.a"
	Asm {StdAOpts} -o "{Targ}" "{IOPrimitivesDir}ImmgPrimitives.a"

"{ObjDir}backlightprim.a.o" 		Ä	"{BackLightDir}backlightprim.a"				¶
										"{AIncludes}SysEqu.a"						¶
										"{AIncludes}SysErr.a"						¶
										"{AIncludes}Traps.a"						¶
										"{IntAIncludes}powerprivequ.a"				¶
										"{IntAIncludes}HardwarePrivateEqu.a"		¶
										"{BackLightDir}backlightequ.a"
	Asm -o {Targ} "{BackLightDir}backlightprim.a" {StdAOpts}

"{ObjDir}SndPrimitives.a.o"			Ä	"{ObjDir}StandardEqu.d"						¶
										"{IntAIncludes}HardwarePrivateEqu.a"		¶
										"{IntAincludes}SoundPrivate.a"				¶
										"{IntAIncludes}IOPrimitiveEqu.a"			¶
										"{IntAIncludes}UniversalEqu.a"				¶
										"{IOPrimitivesDir}SndPrimitives.a"
	Asm {StdAOpts} -o "{Targ}" "{IOPrimitivesDir}SndPrimitives.a"

"{ObjDir}PWM.c.o" 			Ä	"{BackLightDir}backlight.h"							¶
								"{BackLightDir}PowerMgr.h"							¶
								"{BackLightDir}PWM.c"
	C -o {Targ} "{BackLightDir}PWM.c" {StdCOpts}

"{ObjDir}backlightGenRout.c.o" 		Ä	"{BackLightDir}backlight.h"					¶
										"{BackLightDir}PowerMgr.h"					¶
										"{BackLightDir}backlightGenRout.c"
	C -o {Targ} "{BackLightDir}backlightGenRout.c" {StdCOpts}
"{ObjDir}backlightinput.c.o" 		Ä	"{CIncludes}SysEqu.h"						¶
										"{CIncludes}memory.h"						¶
										"{CIncludes}errors.h"						¶
										"{BackLightDir}backlightinput.c"			¶
										"{BackLightDir}backlight.h"					¶
										"{BackLightDir}PowerMgr.h"
	C -o {Targ} "{BackLightDir}backlightinput.c" {StdCOpts}

"{ObjDir}backlightcpu.c.o" 			Ä	"{CIncludes}SysEqu.h"						¶
										"{CIncludes}memory.h"						¶
										"{CIncludes}errors.h"						¶
										"{BackLightDir}backlightcpu.c"				¶
										"{BackLightDir}backlight.h"					¶
										"{BackLightDir}PowerMgr.h"
	C -o {Targ} "{BackLightDir}backlightcpu.c" {StdCOpts}
