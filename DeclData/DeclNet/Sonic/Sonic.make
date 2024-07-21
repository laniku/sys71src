#
#	File:		Sonic.make
#
#	Contains:	Makefile for Sonic.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#

"{RsrcDir}DeclDataSonic.rsrc" Ä	"{ObjDir}SonicEnet.a.o"				¶
								"{ObjDir}Sonic.a.o"					¶
								"{ObjDir}Loopback.c.o"				¶
								"{IfObjDir}interface.o"		
	Link {StdLOpts} {StdAlign} -rt decl=1 -o "{Targ}"	"{ObjDir}SonicEnet.a.o"	¶
								"{ObjDir}Sonic.a.o"					¶
								"{ObjDir}Loopback.c.o"				¶
								"{IfObjDir}interface.o"


"{ObjDir}SonicEnet.a.o"		Ä	"{SonicDir}SonicEnet.a"				¶
								"{SonicDir}SonicEqu.a"				¶
								"{SonicDir}VersionEclipse.a"		¶
								"{EthernetDir}AtalkMacros.a"		¶
								"{EthernetDir}ENETEqu.a"			¶
								"{AIncludes}GestaltEqu.a"			¶
								"{AIncludes}Slots.a"				¶
								"{AIncludes}SysEqu.a"				¶
								"{AIncludes}SysErr.a"				¶
								"{AIncludes}ToolUtils.a"				¶
								"{AIncludes}Traps.a"				
	Asm {StdAOpts} -d ForEclipseROM=0,sonic32=1,ctlpad=0,mmu=1 -i "{SonicDir}" -i "{EthernetDir}" -o "{Targ}" "{SonicDir}SonicEnet.a"


"{ObjDir}Sonic.a.o"			Ä	"{SonicDir}Sonic.a"					¶
								"{SonicDir}SonicEqu.a"				
	Asm {StdAOpts} -d sonic32=1,mmu=1 -i "{SonicDir}" -i "{EthernetDir}" -o "{Targ}" "{SonicDir}Sonic.a"
