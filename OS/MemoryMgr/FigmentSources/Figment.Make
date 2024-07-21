#
#	File:		Figment.make
#
#	Contains:	Makefile for the Figment Memory Manager.
#
#	Written by:	Kurt Clark and Brian Topping
#
#	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM4>	10/15/93	BT		Change MemoryMgrPriv.h to be found in Internal interfaces.
#	   <SM3>	 7/21/93	BT		Radar #1100608. remove "internal_debugging" in favor of
#									FeatureSet option hasFigmentInternalDebugging.
#	   <SM2>	 6/10/93	BT		Remove small_freeBlock_headers and has_cache_type_cpu defines
#									from MMCOptions. This is for PDM, others may want the cache
#									stuff later.
#	   <SM1>	 5/21/93	kc		Move the figment make stuff into Figment.Make.
#		 <3>	 5/20/93	BT		Update sources to conditionally compile Figment under the build
#									flag "hasNewHeapMgr".
#		 <2>	 5/18/93	BT		Added Figment to build
				
#
# These are options for Figment
#

MMCOptions = 	-d quadLongWordAligned

MMAOptions =	-i "{MemoryMgrDir}"			¶
				-d patchedIn=0

FigMemoryMgrObjs 				=	"{ObjDir}MemMgrGlue.a.o"						¶
									"{ObjDir}MemMgr.c.o"							¶
									"{ObjDir}MemMgrInternal.c.o"					¶
									"{ObjDir}MemMgrHeap.c.o"						¶
									"{ObjDir}MemMgrUtils.c.o"						¶
									"{ObjDir}ProcessMgrHeap.c.o"					¶
									"{ObjDir}MemMgrBoot.a.o"						¶
									"{ObjDir}MemMgrUtils.a.o"						¶
			 						"{ObjDir}MemMgrDebug.c.o"						¶
									"{ObjDir}"QTMemory.c.o


"{LibDir}Figment.lib"			Ä	{FigMemoryMgrObjs} {MemoryMgrObjs}
 	Lib {StdLibOpts} -o "{Targ}" {FigMemoryMgrObjs}


"{ObjDir}MemMgrBoot.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}QuickDraw.a"						¶
									"{IntAIncludes}ColorEqu.a"						¶
									"{AIncludes}Palettes.a"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{AIncludes}HardwareEqu.a"						¶
									"{AIncludes}fsequ.a"							¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{MemoryMgrDir}MemoryMgrPriv.a"					¶
									"{FigmentDir}MemMgrBoot.a"
	Asm {StdAOpts} {MMAOptions} -o "{Targ}" "{FigmentDir}MemMgrBoot.a"


"{ObjDir}MemMgrGlue.a.o"	Ä		"{FigmentDir}MemMgrGlue.a"
	Asm {StdAOpts} {MMAOptions} -o "{Targ}" "{FigmentDir}MemMgrGlue.a"


"{ObjDir}MemMgrUtils.a.o"	Ä			"{FigmentDir}MemMgrUtils.a"
	Asm {StdAOpts} {MMAOptions} -o "{Targ}" "{FigmentDir}MemMgrUtils.a"


"{ObjDir}"MemMgrHeap.c.o		Ä	"{FigmentDir}MemMgr.h"							¶
									"{IntCIncludes}MemoryMgrPriv.h"					¶
									"{FigmentDir}MemoryRoutines.h"					¶
									"{FigmentDir}MemMgrDebug.h"						¶
									"{FigmentDir}MemMgrHeap.c"
	C {StdCOpts} {MMCOptions} -o "{Targ}" "{FigmentDir}MemMgrHeap.c"


"{ObjDir}"MemMgr.c.o			Ä	"{FigmentDir}MemMgr.h"							¶
									"{IntCIncludes}MemoryMgrPriv.h"					¶
									"{FigmentDir}MemoryRoutines.h"					¶
									"{FigmentDir}MemMgrDebug.h"						¶
									"{FigmentDir}MemMgr.c"
	C {StdCOpts} {MMCOptions} -o "{Targ}" "{FigmentDir}MemMgr.c"

"{ObjDir}"MemMgrInternal.c.o	Ä	"{FigmentDir}MemMgr.h"							¶
									"{IntCIncludes}MemoryMgrPriv.h"					¶
									"{FigmentDir}MemoryRoutines.h"					¶
									"{FigmentDir}MemMgrDebug.h"						¶
									"{FigmentDir}MemMgrInternal.c"
	C {StdCOpts} {MMCOptions} -o "{Targ}" "{FigmentDir}MemMgrInternal.c"


"{ObjDir}"ProcessMgrHeap.c.o	Ä	"{FigmentDir}MemMgr.h"							¶
									"{IntCIncludes}MemoryMgrPriv.h"					¶
									"{FigmentDir}MemoryRoutines.h"					¶
									"{FigmentDir}MemMgrDebug.h"						¶
									"{FigmentDir}ProcessMgrHeap.c"
	C {StdCOpts} {MMCOptions} -o "{Targ}" "{FigmentDir}ProcessMgrHeap.c"


"{ObjDir}"MemMgrUtils.c.o		Ä	"{FigmentDir}MemMgr.h"							¶
									"{IntCIncludes}MemoryMgrPriv.h"					¶
									"{FigmentDir}MemoryRoutines.h"					¶
									"{FigmentDir}MemMgrDebug.h"						¶
									"{FigmentDir}MemMgrUtils.c"
	C {StdCOpts} {MMCOptions} -o "{Targ}" "{FigmentDir}MemMgrUtils.c"


"{ObjDir}"MemMgrDebug.c.o		Ä	"{FigmentDir}MemMgr.h"							¶
									"{IntCIncludes}MemoryMgrPriv.h"					¶
									"{FigmentDir}MemoryRoutines.h"					¶
									"{FigmentDir}MemMgrDebug.h"						¶
									"{FigmentDir}MemMgrDebug.c"
	C {StdCOpts} {MMCOptions} -o "{Targ}" "{FigmentDir}MemMgrDebug.c"

"{ObjDir}"QTMemory.c.o		Ä		"{FigmentDir}MemMgr.h"							¶
									"{IntCIncludes}MemoryMgrPriv.h"					¶
									"{FigmentDir}MemoryRoutines.h"					¶
									"{FigmentDir}MemMgrGlue.a"						¶
									"{FigmentDir}QTMemory.c"
	C {StdCOpts} {MMCOptions} -o "{Targ}" "{FigmentDir}QTMemory.c"
