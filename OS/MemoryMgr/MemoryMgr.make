#
#	File:		MemoryMgr.make
#
#	Contains:	Makefile for the Memory Manager.
#
#	Written by:	Kurt Clark, Chas Spillar, Tim Nichols and Brian Topping
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM4>	 5/21/93	kc		Move the figment make stuff into Figment.Make.
#	   <SM3>	 5/20/93	BT		Update sources to conditionally compile Figment under the build
#									flag "hasNewHeapMgr".
#	   <SM2>	 5/18/93	BT		Added Figment to build


FigmentDir = {MemoryMgrDir}FigmentSources:

#include {FigmentDir}Figment.Make


MemoryMgrObjs 					=	"{ObjDir}MemoryMgr.a.o"							¶
									"{ObjDir}MemoryMgrExtensions.a.o"				¶
									"{ObjDir}MemoryMgrInternal.a.o"					¶
									"{ObjDir}BlockMove.a.o"


"{LibDir}MemoryMgr.lib"			Ä	"{LibDir}Figment.lib" {MemoryMgrObjs}
	If "{FeatureSet}" =~ /Å'hasNewHeapMgr=True'Å/
	 	Lib {StdLibOpts} -o "{Targ}" "{LibDir}Figment.lib" {MemoryMgrObjs}
	Else
	 	Lib {StdLibOpts} -o "{Targ}" {MemoryMgrObjs}
	End


"{ObjDir}BlockMove.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{MemoryMgrDir}BlockMove.a"
	Asm {StdAOpts} -o "{Targ}" "{MemoryMgrDir}BlockMove.a"


"{ObjDir}MemoryMgr.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}QuickDraw.a"						¶
									"{IntAIncludes}ColorEqu.a"						¶
									"{AIncludes}Palettes.a"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{AIncludes}HardwareEqu.a"						¶
									"{AIncludes}fsequ.a"							¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{MemoryMgrDir}MemoryMgrPriv.a"					¶
									"{MemoryMgrDir}MemoryMgr.a"
	Asm {StdAOpts} -o "{Targ}" "{MemoryMgrDir}MemoryMgr.a"


"{ObjDir}MemoryMgrExtensions.a.o"	Ä	"{ObjDir}StandardEqu.d"						¶
									"{MemoryMgrDir}MemoryMgrPriv.a"					¶
									"{MemoryMgrDir}MemoryMgrExtensions.a"
	Asm {StdAOpts} -o "{Targ}" "{MemoryMgrDir}MemoryMgrExtensions.a"


"{ObjDir}MemoryMgrInternal.a.o"	Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{AIncludes}HardwareEqu.a"						¶
									"{MemoryMgrDir}MemoryMgrPriv.a"					¶
									"{MemoryMgrDir}MemoryMgrInternal.a"
	Asm {StdAOpts} -o "{Targ}" "{MemoryMgrDir}MemoryMgrInternal.a"


