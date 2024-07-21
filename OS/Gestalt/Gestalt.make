#
#	File:		Gestalt.make
#
#	Contains:	Makefile for Gestalt.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#		<SM2>	  4/8/93	CSS		Update dependencies so that changing include files will cause
#									things to build.



GestaltObjs		=					"{ObjDir}GestaltFunction.a.o"					¶
									"{ObjDir}GestaltLookup.c.o"						¶
									"{ObjDir}GestaltExtensions.a.o"
									
"{LibDir}Gestalt.lib"			Ä	{GestaltObjs}
	Lib {StdLibOpts} -o "{Targ}" {GestaltObjs}


"{ObjDir}GestaltFunction.a.o"	Ä 	"{ObjDir}StandardEqu.d"		 					¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{AIncludes}SANEMacs881.a"						¶
									"{IntAIncludes}MMUEqu.a"						¶
									"{AIncludes}GestaltEqu.a"						¶
									"{IntAIncludes}GestaltPrivateEqu.a" 			¶
									"{IntAIncludes}InternalOnlyEqu.a"				¶
									"{IntAIncludes}EDiskEqu.a"						¶
									"{IntAIncludes}BootEqu.a"						¶
									"{GestaltDir}GestaltFunction.a"
	Asm {StdAOpts} -o "{Targ}" "{GestaltDir}GestaltFunction.a"


"{ObjDir}GestaltExtensions.a.o"	Ä 	"{ObjDir}StandardEqu.d"		 					¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{AIncludes}GestaltEqu.a"						¶
									"{IntAIncludes}GestaltPrivateEqu.a" 			¶
									"{IntAIncludes}SysPrivateEqu.a"					¶
									"{IntAIncludes}InternalOnlyEqu.a"				¶
									"{GestaltDir}GestaltExtensions.a"
	Asm {StdAOpts} -o "{Targ}" "{GestaltDir}GestaltExtensions.a"


"{ObjDir}GestaltLookup.c.o"		Ä 	"{CIncludes}GestaltEqu.h" 						¶
									"{CIncludes}Types.h"							¶
									"{CIncludes}Errors.h"							¶
									"{CIncludes}Memory.h"							¶
									"{CIncludes}SysEqu.h"							¶
									"{IntCIncludes}ExpandMemPriv.h"					¶
									"{IntCIncludes}GestaltPrivateEqu.h"				¶
									"{GestaltDir}GestaltLookup.c"
	C {StdCOpts} -o "{Targ}" "{GestaltDir}GestaltLookup.c"

