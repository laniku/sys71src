#
#	File:		MMU.Make
#
#	Contains:	Makefile for the MMU stuff.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM2>	  8/4/93	JDR		MMU.a depends on SoundPrivate.a.

MMUObjs 		=					"{ObjDir}MMU.a.o"								¶
									"{ObjDir}MMUTables.a.o"							¶
									"{ObjDir}GetReal.a.o"

"{LibDir}MMU.lib"				Ä	{MMUObjs}
	Lib {StdLibOpts} {MMUObjs} -o "{Targ}"



"{ObjDir}MMU.a.o"				Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{IntAIncludes}SoundPrivate.a"					¶
									"{AIncludes}HardwareEqu.a"						¶
									"{IntAIncludes}MMUEqu.a"						¶
									"{IntAIncludes}BootEqu.a"						¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{MMUDir}MMU.a"
	Asm {StdAOpts} -o "{Targ}"	"{MMUDir}MMU.a"


"{ObjDir}MMUTables.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{IntAIncludes}MmuEqu.a"						¶
									"{IntAIncludes}BootEqu.a"						¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{AIncludes}EDiskEqu.a"							¶
									"{MMUDir}MMUTables.a"
	Asm {StdAOpts} -o "{Targ}"	"{MMUDir}MMUTables.a"


"{ObjDir}GetReal.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}HardwareEqu.a"						¶
									"{IntAIncludes}MMUEqu.a"						¶
									"{AIncludes}GestaltEqu.a"						¶
									"{MMUDir}GetReal.a"
	Asm {StdAOpts} -o "{Targ}"	"{MMUDir}GetReal.a"


