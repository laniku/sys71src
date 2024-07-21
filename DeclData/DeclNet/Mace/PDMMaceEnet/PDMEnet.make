#	Contains:	Makefile for PDM MACE Ethernet driver.
#
#	Written by:	Dave Calvert
#
#	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM6>	  3/5/93	dwc		Changed DeclDataPDMMace.rsrc ID to be unique from
#									DeclDataMace.rsrc.
#	   <SM3>	  3/4/93	dwc		Added DeclDataPDMMace definition for PDM ENET.
#	   <SM2>	 2/25/93	dwc		Re-enable loopbacktests and include Interface.o for them.
#	   <SM2>	  2/4/93	RC		Took out Loopback.c.o link and fixed {make} to {makedir}
#


#===============================================================================
#	Create DeclData Resource for PDM Declaration ROM
#===============================================================================
"{RsrcDir}DeclDataPDMMace.rsrc"		Ä	"{ObjDir}PDMMaceEnet.a.o"					¶
								"{ObjDir}PDMMace.a.o"								¶
								"{ObjDir}Loopback.c.o"								¶
								"{IfObjDir}interface.o"		
	Link {StdLOpts} {StdAlign} -rt decl=1 -o "{Targ}"								¶
								"{ObjDir}PDMMaceEnet.a.o"							¶
								"{ObjDir}PDMMace.a.o"								¶
								"{ObjDir}Loopback.c.o"								¶
								"{IfObjDir}Interface.o"

"{RsrcDir}PDMENET.rsrc"		Ä	"{ObjDir}PDMMaceEnet.a.o"							¶
								"{ObjDir}PDMMace.a.o"								¶
								"{PDMMaceDir}PDMEnet.make"							¶
								"{ObjDir}Loopback.c.o"								¶
								"{IfObjDir}Interface.o"
	Link -t rsrc -c RSED -sn Main="PDM MACE Ethernet Driver" 						¶
				-ra "PDM MACE Ethernet Driver"=resSysHeap,resPurgeable,resLocked 	¶
				-rt enet=57 -o {Targ}												¶
				"{ObjDir}PDMMaceEnet.a.o"											¶
				"{ObjDir}PDMMace.a.o"												¶
				"{ObjDir}Loopback.c.o"												¶
				"{IfObjDir}Interface.o"

"{RsrcDir}PDMENET57.rsrc"		Ä	"{ObjDir}PDMMaceEnet.a.o"						¶
								"{ObjDir}PDMMace.a.o"								¶
#								"{ObjDir}Loopback.c.o"								¶
								"{PDMMaceDir}PDMEnet.make"
	Link -t rsrc -c RSED -sn Main="PDM MACE Ethernet Driver" 						¶
				-ra "PDMENET"=resSysHeap,resPurgeable,resLocked 					¶
				-rt enet=57 -o {Targ}												¶
				"{ObjDir}PDMMaceEnet.a.o"											¶
#				"{ObjDir}Loopback.c.o"												¶
				"{ObjDir}PDMMace.a.o"

#===============================================================================
#	Assemble Stuff
#===============================================================================


"{ObjDir}PDMMace.a.o"		Ä	"{PDMMaceDir}PDMMace.a"								¶
								"{PDMMaceDir}PDMMaceEqu.a"							¶
								"{IntAIncludes}AMICEqu.a"							¶
								"{IntAIncludes}UniversalEqu.a"						¶
								"{EthernetDir}ATalkMacros.a"						¶
								"{PDMMaceDir}PDMEnet.make"
	Asm {StdAOpts} {Defs}  -i "{PDMMaceDir}" -i "{EthernetDir}" -o "{Targ}" "{PDMMaceDir}PDMMace.a"

"{ObjDir}PDMMaceEnet.a.o"	Ä	"{PDMMaceDir}PDMMaceEnet.a"							¶
								"{PDMMaceDir}PDMMaceEqu.a"							¶
								"{PDMMaceDir}VersionPDMMaceEnet.a"					¶
								"{EthernetDir}802Equ.a"								¶
								"{EthernetDir}ATalkMacros.a"						¶
								"{EthernetDir}ENETEqu.a"							¶
								"{EthernetDir}SNMPLAP.a"							¶
								"{IntAIncludes}UniversalEqu.a"						¶
								"{IntAIncludes}AMICEqu.a"							¶
								"{AIncludes}GestaltEqu.a"							¶
								"{AIncludes}SysEqu.a"								¶
								"{AIncludes}SysErr.a"								¶
								"{AIncludes}Traps.a"								¶
								"{AIncludes}Slots.a"								¶
								"{PDMMaceDir}PDMEnet.make"
	Asm {StdAOpts} {Defs} -i "{PDMMaceDir}" -i "{EthernetDir}" -o "{Targ}" "{PDMMaceDir}PDMMaceEnet.a"

