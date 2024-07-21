#
#	File		Mace.Make
#
#	Contains:	Makefile for Mace.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc.  All rights reserved.
#
#	Change History (most recent first):
#
#	   <SM2>	 6/14/93	kc		Roll in Ludwig.
#	   <LW3>	 3/16/93	chp		Added a dependency on SysPrivateEqu.a for Mace.a.o.
#	   <LW2>	 1/27/93	mal		Add MACE ecfg rsrc.
#	   <SM2>	11/30/92	SWC		Changed TimeEqu.a->Timer.a.
#

"{RsrcDir}DeclDataMace.rsrc" Ä 	"{ObjDir}MaceEnet.a.o"				¶
								"{ObjDir}Mace.a.o"					¶
								"{ObjDir}Loopback.c.o"				¶
								"{IfObjDir}interface.o"		
	Link {StdLOpts} {StdAlign} -rt decl=1 -o "{Targ}"				¶
								"{ObjDir}MaceEnet.a.o"				¶
								"{ObjDir}Mace.a.o"					¶
								"{ObjDir}Loopback.c.o"				¶
								"{IfObjDir}interface.o"

"{RsrcDir}MACEecfg.rsrc"	Ä 	{MaceDir}MACEecfg.r
	Rez {StdROpts} -t rsrc -c RSED "{MaceDir}MACEecfg.r" -o "{Targ}"


"{ObjDir}Enet61.rsrc"		Ä	"{ObjDir}MaceEnet.a.o"				¶
								"{ObjDir}Mace.a.o"					¶
								"{ObjDir}Loopback.c.o"				
	Link {StdLOpts} {StdAlign} -rt enet=61 -o "{Targ}"				¶
		-sn Main="Cyclone MACE Ethernet Driver" 					¶
		-ra "Cyclone MACE Ethernet Driver"=resSysHeap,resPurgeable,resLocked	¶
								"{ObjDir}MaceEnet.a.o"				¶
								"{ObjDir}Mace.a.o"					¶
								"{ObjDir}Loopback.c.o"				¶
								"{IfObjDir}interface.o"


"{ObjDir}MaceEnet.a.o"		Ä	"{MaceDir}MaceEnet.a"				¶
								"{MaceDir}MaceEqu.a"				¶
								"{MaceDir}VersionMaceEnet.a"		¶
								"{EthernetDir}AtalkMacros.a"		¶
								"{EthernetDir}ENETEqu.a"			¶
								"{EthernetDir}SNMPLAP.a"			¶
								"{AIncludes}GestaltEqu.a"			¶
								"{AIncludes}Slots.a"				¶
								"{AIncludes}SysEqu.a"				¶
								"{AIncludes}SysErr.a"				¶
								"{AIncludes}Timer.a"				¶
								"{AIncludes}Traps.a"				¶
								"{IntAIncludes}HardwarePrivateEqu.a"¶
								"{IntAIncludes}InternalOnlyEqu.a"	¶
								"{IntAIncludes}PSCEqu.a"			¶
								"{IntAIncludes}UniversalEqu.a"		
	Asm {StdAOpts} -i "{MaceDir}" -i "{EthernetDir}" -o "{Targ}" "{MaceDir}MaceEnet.a"


"{ObjDir}Mace.a.o"			Ä	"{MaceDir}Mace.a"					¶
								"{MaceDir}MaceEqu.a"				¶
								"{EthernetDir}AtalkMacros.a"		¶
								"{EthernetDir}ENETEqu.a"			¶
								"{EthernetDir}SNMPLAP.a"			¶
								"{AIncludes}GestaltEqu.a"			¶
								"{AIncludes}SysEqu.a"				¶
								"{AIncludes}SysErr.a"				¶
								"{AIncludes}Traps.a"				¶
								"{IntAIncludes}SysPrivateEqu.a"		¶
								"{IntAIncludes}HardwarePrivateEqu.a"¶
								"{IntAIncludes}InternalOnlyEqu.a"	¶
								"{IntAIncludes}PSCEqu.a"			¶
								"{IntAIncludes}UniversalEqu.a"		
	Asm {StdAOpts} -i "{MaceDir}" -i "{EthernetDir}" -o "{Targ}" "{MaceDir}Mace.a"
