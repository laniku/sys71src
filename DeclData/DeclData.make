#
#	File		DeclData.make
#
#	Contains:	Makefile for Declaration ROM.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM5>	12/13/93	PN		Roll in Kaos and Horrors code to support AJ and Malcom machines.
#	   <SM4>	  9/9/93	pdw		Added slots.a to dependencies.
#	   <SM3>	08-03-93	jmp		Added various necessary dependencies that werenÕt previously
#									spelled out.
#	   <SM2>	  3/4/93	dwc		Added DeclDataPDMMace definition for PDM ENET.
#		 <1>	 2/21/93	kc		first checked in
#	   <SM2>	12-04-92	jmp		Added the rules for building VSC (Keystone) DeclData.

EthernetDir	=	{DeclDir}DeclNet:
SonicDir	=	{EthernetDir}Sonic:
MaceDir		=	{EthernetDir}Mace:
VideoDir	=	{DeclDir}DeclVideo:
GammaDir	=	{VideoDir}Gamma:
PDMMaceDir	=	{MaceDir}PDMMaceEnet:

#include {MaceDir}Mace.Make
#include {SonicDir}Sonic.Make
#include {VideoDir}VideoDrivers.Make
#include {PDMMaceDir}PDMEnet.Make

DeclResources =	"{RsrcDir}DeclData.rsrc"					¶
				"{RsrcDir}PrimaryInit.rsrc"					¶
				"{RsrcDir}SecondaryInit.rsrc"				¶
				"{RsrcDir}SuperInit.rsrc"					¶
				"{RsrcDir}DeclDataMace.rsrc"				¶
				"{RsrcDir}DeclDataPDMMace.rsrc"				¶
				"{RsrcDir}DeclDataSonic.rsrc"				¶
				"{RsrcDir}DeclDataVideo.rsrc"				¶
				"{RsrcDir}Gamma.rsrc"				

DeclHeaders	=	"{ObjDir}StandardEqu.d"						¶
				"{AIncludes}GestaltEqu.a"					¶
				"{AIncludes}ShutDown.a"						¶
				"{AIncludes}ROMEqu.a"						¶
				"{AIncludes}Video.a"						¶
				"{IntAIncludes}DockingEqu.a"				¶
				"{IntAIncludes}EgretEqu.a"					¶
				"{IntAIncludes}GestaltPrivateEqu.a"			¶
				"{IntAIncludes}HardwarePrivateEqu.a"		¶
				"{IntAIncludes}IOPrimitiveEqu.a"			¶
				"{IntAIncludes}PowerPrivEqu.a"				¶
				"{AIncludes}Slots.a"							¶
				"{IntAIncludes}SlotMgrEqu.a"				¶
				"{IntAIncludes}UniversalEqu.a"				¶
				"{IntAIncludes}DepVideoEqu.a"				¶
				"{SonicDir}SonicEqu.a"

#
#	DeclData
#
"{RsrcDir}DeclData"				Ä	{DeclResources} "{RsrcDir}RomLink"
	"{RsrcDir}RomLink"	{DeclResources} -o "{Targ}"


"{RsrcDir}DeclData.rsrc"		Ä	"{RIncludes}Types.r"					¶
									"{IntRIncludes}DepVideoEqu.r"			¶
									"{IntRIncludes}HardwarePrivateEqu.r"	¶
									"{IntRIncludes}InternalOnlyEqu.r"		¶
									"{IntRIncludes}QuickDraw.r"				¶
									"{IntRIncludes}ROMLink.r"				¶
									"{DeclDir}DeclData.r"
	Rez {StdROpts} "{DeclDir}DeclData.r" -o "{Targ}"


# The ROMLinkHeaderBuilder tool is not used.
#"{IntRIncludes}ROMLink.r" 		Ä	"{RsrcDir}ROMLinkHeaderBuilder"
#	"{RsrcDir}ROMLinkHeaderBuilder" > {Targ} #This is kinky


#
#	PrimaryInit
#
"{RsrcDir}PrimaryInit.rsrc"		Ä 	"{ObjDir}PrimaryInit.a.o"
	Link {StdLOpts} {StdAlign} -rt decl=200 "{ObjDir}PrimaryInit.a.o" -o "{Targ}"


"{ObjDir}PrimaryInit.a.o"		Ä	"{DeclDir}PrimaryInit.a"	¶
									{DeclHeaders}					
	Asm {StdAOpts} -d ForEclipseROM=0,sonic32=1,ctlpad=0,mmu=1  -i "{SonicDir}" "{DeclDir}PrimaryInit.a" -o "{Targ}" 


#
#	SecondaryInit
#
"{RsrcDir}SecondaryInit.rsrc"	Ä	"{ObjDir}SecondaryInit.a.o"
	Link {StdLOpts} {StdAlign} -rt decl=210 "{ObjDir}SecondaryInit.a.o" -o "{Targ}"


"{ObjDir}SecondaryInit.a.o"		Ä	"{DeclDir}SecondaryInit.a" 	¶
									{DeclHeaders}					
	Asm {StdAOpts} -d ForEclipseROM=0,sonic32=1,ctlpad=0,mmu=1 -i "{SonicDir}" "{DeclDir}SecondaryInit.a" -o "{Targ}" 

#
#	SuperInit
#

"{RsrcDir}SuperInit.rsrc"		Ä 	"{ObjDir}SuperInit.a.o"
	Link {StdLOpts} {StdAlign} -rt decl=220 "{ObjDir}SuperInit.a.o" -o "{Targ}"

					
"{ObjDir}SuperInit.a.o"			Ä	"{DeclDir}SuperInit.a" 		¶
									{DeclHeaders}					
	Asm {StdAOpts} -d ForEclipseROM=0,sonic32=1,ctlpad=0,mmu=1 -i "{SonicDir}" "{DeclDir}SuperInit.a" -o "{Targ}" 

#
#	Ethernet
#

"{ObjDir}Loopback.c.o"		Ä	"{EthernetDir}Loopback.c"			¶
								"{CIncludes}TextUtils.h"			¶
								"{CIncludes}Memory.h"				¶
								"{CIncludes}Devices.h"				¶
								"{CIncludes}Files.h"				¶
								"{CIncludes}AppleTalk.h"			¶
								"{CIncludes}OSUtils.h"			
	C {StdCOpts} -b -o "{Targ}" "{EthernetDir}Loopback.c"

#
#	Gamma Resource
#

"{RsrcDir}Gamma.rsrc"	Ä	"{RIncludes}Types.r"		¶
							"{IntRIncludes}ROMLink.r"	¶
							"{GammaDir}Gamma.r"
	Rez {StdROpts} "{GammaDir}Gamma.r" -o "{Targ}"


