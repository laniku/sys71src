#
#	File:		VideoDrivers.make
#
#	Contains:	Makefile for Video.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM7>	11/10/93	fau		Update from SuperMunggio <SMG2>.
#	  <SMG2>	10/27/93	fau		Added support for the ATI card on TNT.
#	   <SM6>	09-23-93	jmp		Added GestaltEqu.a to SonoraÕs dependency list.
#	   <SM5>	  9/9/93	pdw		Added slots.a to dependencies.
#	   <SM4>	08-03-93	jmp		Added various necessary dependencies that werenÕt previously
#									spelled out.
#	   <SM3>	 6/14/93	kc		Roll in Ludwig.
#	   <LW5>	 5/19/93	fau		Added CivicPict2 to the DeclVideo.rsrc and made Rez use a -t and
#									-c options.
#	   <LW4>	 4/30/93	fau		Added CivicPict to the DeclDataVideo.rsrc
#	   <LW3>	 4/27/93	fau		W/r to Bug #1081554, I updated the dependencies of the video
#									drivers to include the actual source files!
#	   <LW2>	 2/16/93	fau		Added CivicPrimaryInit dependency to CivicDriver.
#	   <SM2>	 3/31/93	kc		Delete duplicate definition of VideoDir.
#	   <SM2>	01-12-93	jmp		Added support for CSC.

SonicDir						=	{DeclDir}DeclNet:Sonic:
VideoDriverDir					=	{Sources}Drivers:Video:
ApolloVideoDir					=	{VideoDir}Apollo:
CivicVideoDir					=	{VideoDir}Civic:
CSCVideoDir						=	{VideoDir}CSC:
DAFBVideoDir					=	{VideoDir}DAFB:
DBLiteVideoDir					=	{VideoDir}DBLite:
RBVVideoDir						=	{VideoDir}RBV:
SonoraVideoDir					=	{VideoDir}Sonora:
TimVideoDir						=	{VideoDir}Tim:
V8VideoDir						=	{VideoDir}V8:
ATIVideoDir						=	{VideoDir}ATI:

CommonHeaders					=	"{ObjDir}StandardEqu.d"					¶
									"{IntAIncludes}HardwarePrivateEqu.a"	¶
									"{AIncludes}ROMEqu.a"					¶
									"{AIncludes}Video.a"					¶
									"{IntAIncludes}SlotMgrEqu.a"			¶
									"{AIncludes}Slots.a"					¶
									"{IntAIncludes}UniversalEqu.a"			¶
									"{IntAIncludes}DepVideoEqu.a"	

#
#	Video Resource
#

"{RsrcDir}DeclDataVideo.rsrc"	Ä	"{VideoDir}VideoDrivers.r"				¶
									"{RsrcDir}ApolloDriver.rsrc"			¶
									"{RsrcDir}CivicDeclVideo.rsrc"			¶
									"{RsrcDir}CivicDriver.rsrc"				¶
									"{RsrcDir}CivicPict.rsrc"				¶
									"{RsrcDir}CivicPict2.rsrc"				¶
									"{RsrcDir}CivicPrimaryInit.rsrc"		¶
									"{RsrcDir}CSCDeclVideo.rsrc"			¶
									"{RsrcDir}CSCDriver.rsrc"				¶
									"{RsrcDir}CSCPrimaryInit.rsrc"			¶
									"{RsrcDir}DAFBDriver.rsrc"				¶
									"{RsrcDir}DBLiteDriver.rsrc"			¶
									"{RsrcDir}RBVDriver.rsrc"				¶
									"{RsrcDir}SonoraDriver.rsrc"			¶
									"{RsrcDir}SonoraDeclVideo.rsrc"			¶
									"{RsrcDir}SonoraPrimaryInit.rsrc"		¶
									"{RsrcDir}TimDriver.rsrc"				¶
									"{RsrcDir}V8Driver.rsrc"				¶
									"{RsrcDir}ATIDeclVideo.rsrc"			¶
									"{RsrcDir}ATIDeclMonitors.rsrc"			¶
									"{RsrcDir}ATIDriver.rsrc"				¶
									"{RsrcDir}ATIPrimaryInit.rsrc"
	Rez -t rsrc -c RSED {StdROpts} -s {RsrcDir} "{VideoDir}VideoDrivers.r" -o "{Targ}"

#
#	Apollo Video Driver
#
"{RsrcDir}ApolloDriver.rsrc"	Ä	"{ObjDir}ApolloDriver.a.o"		
	Link {StdLOpts} {StdAlign} -rt decl=10 "{ObjDir}ApolloDriver.a.o" -o "{RsrcDir}ApolloDriver.rsrc"

"{ObjDir}ApolloDriver.a.o"		Ä 	"{ApolloVideoDir}ApolloDriver.a"		¶
									{CommonHeaders}
	Asm {StdAOpts} -o "{ObjDir}ApolloDriver.a.o" "{ApolloVideoDir}ApolloDriver.a"

#
#	Civic Video Driver
#
CivicHeaders					=	{CommonHeaders}
				
"{RsrcDir}CivicDeclVideo.rsrc"	Ä	"{CivicVideoDir}CivicDeclVideo.r"		¶
									"{IntRIncludes}DepVideoEqu.r"			¶
									"{IntRIncludes}HardwarePrivateEqu.r"	¶
									"{IntRIncludes}InternalOnlyEqu.r"		¶
									"{IntRIncludes}Quickdraw.r"				¶
									"{IntRIncludes}ROMLink.r"
	Rez -t rsrc -c RSED {StdROpts} "{CivicVideoDir}CivicDeclVideo.r" -o "{RsrcDir}CivicDeclVideo.rsrc"

"{RsrcDir}CivicDriver.rsrc"		Ä	"{ObjDir}CivicDriver.a.o"				¶
									"{ObjDir}CivicPrimaryInit.a.o"		
	Link {StdLOpts} {StdAlign} -rt decl=20 "{ObjDir}CivicDriver.a.o" -o "{RsrcDir}CivicDriver.rsrc"

"{ObjDir}CivicDriver.a.o"		Ä 	"{CivicVideoDir}CivicDriver.a"			¶
									"{ObjDir}CivicPrimaryInit.a.o"			¶
									{CivicHeaders}	
	Asm {StdAOpts} -o "{ObjDir}CivicDriver.a.o" "{CivicVideoDir}CivicDriver.a"

"{RsrcDir}CivicPrimaryInit.rsrc" Ä	"{ObjDir}CivicPrimaryInit.a.o"		
	Link {StdLOpts} {StdAlign} -rt decl=30 "{ObjDir}CivicPrimaryInit.a.o" -o "{RsrcDir}CivicPrimaryInit.rsrc"

"{ObjDir}CivicPrimaryInit.a.o"	Ä 	"{CivicVideoDir}CivicPrimaryInit.a"		¶
										{CivicHeaders}	
	Asm {StdAOpts} -o "{ObjDir}CivicPrimaryInit.a.o" "{CivicVideoDir}CivicPrimaryInit.a"

"{RsrcDir}CivicPict.rsrc"		Ä	"{ObjDir}CivicPict.a.o"		
	Link {StdLOpts} {StdAlign} -rt decl=32 "{ObjDir}CivicPict.a.o" -o "{RsrcDir}CivicPict.rsrc"

"{ObjDir}CivicPict.a.o"			Ä 	"{CivicVideoDir}CivicPict.a"
	Asm {StdAOpts} -o "{ObjDir}CivicPict.a.o" "{CivicVideoDir}CivicPict.a"

"{RsrcDir}CivicPict2.rsrc"		Ä	"{ObjDir}CivicPict2.a.o"		
	Link {StdLOpts} {StdAlign} -rt decl=33 "{ObjDir}CivicPict2.a.o" -o "{RsrcDir}CivicPict2.rsrc"

"{ObjDir}CivicPict2.a.o"		Ä 	"{CivicVideoDir}CivicPict2.a"
	Asm {StdAOpts} -o "{ObjDir}CivicPict2.a.o" "{CivicVideoDir}CivicPict2.a"

#
#	CSC Video Code
#
"{RsrcDir}CSCDeclVideo.rsrc"	Ä	"{CSCVideoDir}CSCDeclVideo.r"			¶
									"{IntRIncludes}DepVideoEqu.r"			¶
									"{IntRIncludes}HardwarePrivateEqu.r"	¶
									"{IntRIncludes}InternalOnlyEqu.r"		¶
									"{IntRIncludes}Quickdraw.r"				¶
									"{IntRIncludes}ROMLink.r"
	Rez {StdROpts} "{CSCVideoDir}CSCDeclVideo.r" -o "{RsrcDir}CSCDeclVideo.rsrc"

"{RsrcDir}CSCDriver.rsrc"		Ä	"{ObjDir}CSCDriver.a.o"					¶
									"{ObjDir}CSCPrimaryInit.a.o"		
	Link {StdLOpts} {StdAlign} -rt decl=6000 "{ObjDir}CSCDriver.a.o" -o "{RsrcDir}CSCDriver.rsrc"

"{ObjDir}CSCDriver.a.o"			Ä 	"{CSCVideoDir}CSCDriver.a"				¶
									{CommonHeaders}
	Asm {StdAOpts} -o "{ObjDir}CSCDriver.a.o" "{CSCVideoDir}CSCDriver.a"

"{RsrcDir}CSCPrimaryInit.rsrc"	Ä	"{ObjDir}CSCPrimaryInit.a.o"		
	Link {StdLOpts} {StdAlign} -rt decl=6030 "{ObjDir}CSCPrimaryInit.a.o" -o "{RsrcDir}CSCPrimaryInit.rsrc"

"{ObjDir}CSCPrimaryInit.a.o"	Ä 	"{CSCVideoDir}CSCPrimaryInit.a"			¶
									{CommonHeaders}
	Asm {StdAOpts} -d ForEclipseROM=0,sonic32=1,ctlpad=0,mmu=1 -i "{DeclDir}DeclNet:Sonic:" -o "{ObjDir}CSCPrimaryInit.a.o" "{CSCVideoDir}CSCPrimaryInit.a" 

#
#	DAFB Video Driver
#
"{RsrcDir}DAFBDriver.rsrc"		Ä	"{ObjDir}DAFBDriver.a.o"			
	Link {StdLOpts} {StdAlign} -rt decl=40 "{ObjDir}DAFBDriver.a.o" -o "{RsrcDir}DAFBDriver.rsrc"

"{ObjDir}DAFBDriver.a.o"		Ä 	"{DAFBVideoDir}DAFBDriver.a"			¶
									{CommonHeaders}
	Asm {StdAOpts} -o "{ObjDir}DAFBDriver.a.o" "{DAFBVideoDir}DAFBDriver.a"

#
#	DBLite Video Driver
#
"{RsrcDir}DBLiteDriver.rsrc"	Ä	"{ObjDir}DBLiteDriver.a.o"		
	Link {StdLOpts} {StdAlign} -rt decl=50 "{ObjDir}DBLiteDriver.a.o" -o "{RsrcDir}DBLiteDriver.rsrc"

"{ObjDir}DBLiteDriver.a.o"		Ä 	"{DBLiteVideoDir}DBLiteDriver.a"		¶
									{CommonHeaders}
	Asm {StdAOpts} -o "{ObjDir}DBLiteDriver.a.o" "{DBLiteVideoDir}DBLiteDriver.a"

#
#	RBV Video Driver
#
"{RsrcDir}RBVDriver.rsrc"		Ä	"{ObjDir}RBVDriver.a.o"				
	Link {StdLOpts} {StdAlign} -rt decl=60 "{ObjDir}RBVDriver.a.o" -o "{RsrcDir}RBVDriver.rsrc"

"{ObjDir}RBVDriver.a.o"			Ä 	"{RBVVideoDir}RBVDriver.a"				¶
									{CommonHeaders}
	Asm {StdAOpts} -o "{ObjDir}RBVDriver.a.o" "{RBVVideoDir}RBVDriver.a"

#
#	Sonora Video Driver
#
SonoraHeaders					=	"{IntAIncludes}AMICEqu.a"				¶
									"{IntAIncludes}EgretEqu.a"				¶
									"{AIncludes}GestaltEqu.a"				¶
									"{IntAIncludes}IOPrimitiveEqu.a"		¶
									"{SonicDir}SonicEqu.a"					¶
									{CommonHeaders}

"{RsrcDir}SonoraDeclVideo.rsrc"	Ä	"{SonoraVideoDir}SonoraDeclVideo.r"		¶
									"{IntRIncludes}DepVideoEqu.r"			¶
									"{IntRIncludes}HardwarePrivateEqu.r"	¶
									"{IntRIncludes}InternalOnlyEqu.r"		¶
									"{IntRIncludes}Quickdraw.r"				¶
									"{IntRIncludes}ROMLink.r"
	Rez {StdROpts} "{SonoraVideoDir}SonoraDeclVideo.r" -o "{RsrcDir}SonoraDeclVideo.rsrc"

"{RsrcDir}SonoraDriver.rsrc"	Ä	"{ObjDir}SonoraDriver.a.o"
	Link {StdLOpts} {StdAlign} -rt decl=70 "{ObjDir}SonoraDriver.a.o" -o "{RsrcDir}SonoraDriver.rsrc"

"{ObjDir}SonoraDriver.a.o"		Ä 	"{SonoraVideoDir}SonoraDriver.a"		¶
									{SonoraHeaders}
	Asm {StdAOpts} -o "{ObjDir}SonoraDriver.a.o" "{SonoraVideoDir}SonoraDriver.a"

"{RsrcDir}SonoraPrimaryInit.rsrc" Ä	"{ObjDir}SonoraPrimaryInit.a.o"		
	Link {StdLOpts} {StdAlign} -rt decl=80 "{ObjDir}SonoraPrimaryInit.a.o" -o "{RsrcDir}SonoraPrimaryInit.rsrc"

"{ObjDir}SonoraPrimaryInit.a.o"	Ä 	"{SonoraVideoDir}SonoraPrimaryInit.a" 	¶
									{SonoraHeaders}
	Asm {StdAOpts} -d ForEclipseROM=0,sonic32=1,ctlpad=0,mmu=1 -i "{SonicDir}" -o "{ObjDir}SonoraPrimaryInit.a.o" "{SonoraVideoDir}SonoraPrimaryInit.a"

#
#	Tim Video Driver
#
"{RsrcDir}TimDriver.rsrc" 		Ä	"{ObjDir}TimDriver.a.o"					
	Link {StdLOpts} {StdAlign} -rt decl=90 "{ObjDir}TimDriver.a.o" -o "{RsrcDir}TimDriver.rsrc"

"{ObjDir}TimDriver.a.o"			Ä 	"{TimVideoDir}TimDriver.a"				¶
									{CommonHeaders}
	Asm {StdAOpts} -o "{ObjDir}TimDriver.a.o" "{TimVideoDir}TimDriver.a"

#
#	V8 Video Driver
#
"{RsrcDir}V8Driver.rsrc" 		Ä	"{ObjDir}V8Driver.a.o"		
	Link {StdLOpts} {StdAlign} -rt decl=100 "{ObjDir}V8Driver.a.o" -o "{RsrcDir}V8Driver.rsrc"

"{ObjDir}V8Driver.a.o"			Ä 	"{V8VideoDir}V8Driver.a"				¶
									{CommonHeaders}
	Asm {StdAOpts} -o "{ObjDir}V8Driver.a.o" "{V8VideoDir}V8Driver.a"

#
#	ATI Video Driver
#
ATIHeaders						=	"{ATIVideoDir}ATIDrvr.h"				¶
									"{ATIVideoDir}ATIStdTypes.h"			¶
									"{ATIVideoDir}ATIVideo.h"				¶
									"{ATIVideoDir}ATI.h"					¶
									"{ATIVideoDir}Diamond.h"				¶
									{CommonHeaders}

"{RsrcDir}ATIDeclVideo.rsrc"	Ä	"{ATIVideoDir}ATIDeclVideo.r"			¶
									"{ATIVideoDir}ATIDeclMonitors.r"		¶
									"{IntRIncludes}DepVideoEqu.r"			¶
									"{IntRIncludes}HardwarePrivateEqu.r"	¶
									"{IntRIncludes}InternalOnlyEqu.r"		¶
									"{IntRIncludes}Quickdraw.r"				¶
									"{IntRIncludes}ROMLink.r"
	Rez {StdROpts} "{ATIVideoDir}ATIDeclVideo.r" -o "{RsrcDir}ATIDeclVideo.rsrc"

#===================================================================
# Build the supported monitors file
#===================================================================
"{RsrcDir}ATIDeclMonitors.rsrc" Ä	"{ATIVideoDir}ATIDeclMonitors.r"			¶
									"{ATIVideoDir}ATIDefROM.r"					¶
									"{ATIVideoDir}ATIDeclVideo.r"
	Rez {StdROpts} "{ATIVideoDir}ATIDeclMonitors.r" -o "{RsrcDir}ATIDeclMonitors.rsrc"

#===================================================================
# Build the ATI Primary INIT file
#===================================================================
"{RsrcDir}ATIPrimaryInit.rsrc" Ä	"{ObjDir}ATIPrimaryInit.a.o"			¶
									"{ObjDir}ATIPrimaryInit.c.o"			¶
									"{ObjDir}PCIUtil.c.o"					¶
									"{ObjDir}Diamond.c.o"
	Link {StdLOpts} {StdAlign} -rt decl=110 				¶
					"{ObjDir}ATIPrimaryInit.a.o"			¶
					"{ObjDir}ATIPrimaryInit.c.o"			¶
					"{ObjDir}PCIUtil.c.o"					¶
					"{ObjDir}Diamond.c.o"					¶
					-o "{RsrcDir}ATIPrimaryInit.rsrc"

"{ObjDir}ATIPrimaryInit.a.o"	Ä	"{ATIVideoDir}ATIPrimaryInit.a"
	asm {StdAOpts} -o "{ObjDir}ATIPrimaryInit.a.o" "{ATIVideoDir}ATIPrimaryInit.a"

"{ObjDir}ATIPrimaryInit.c.o"	Ä	"{ATIVideoDir}ATIPrimaryInit.c" {ATIHeaders}
	C {StdCOpts} -o "{ObjDir}ATIPrimaryInit.c.o" "{ATIVideoDir}ATIPrimaryInit.c"

"{ObjDir}Diamond.c.o"	Ä	"{ATIVideoDir}Diamond.c" {ATIHeaders}
	C {StdCOpts} -o "{ObjDir}Diamond.c.o" "{ATIVideoDir}Diamond.c"


#===================================================================
# Build the ATI driver
#===================================================================
"{RsrcDir}ATIDriver.rsrc"	Ä		"{ObjDir}ATIDrvr.a.o"				¶
									"{ObjDir}ATIDrvr.c.o"				¶
									"{ObjDir}ATISlotUtils.c.o"			¶
									"{ObjDir}ATIVideoImp.c.o"			¶
									"{ObjDir}ATIDrvrImp.c.o"			¶
									"{ObjDir}PCIUtil.c.o"
	Link {StdLOpts} {StdAlign} -rt decl=112 					¶
					"{ObjDir}ATIDrvr.a.o"						¶
					"{ObjDir}ATIDrvr.c.o"						¶
					"{ObjDir}ATIDrvrImp.c.o"					¶
					"{ObjDir}ATISlotUtils.c.o"					¶
					"{ObjDir}ATIVideoImp.c.o"					¶
					"{ObjDir}PCIUtil.c.o"						¶
					-o "{RsrcDir}ATIDriver.rsrc"

"{ObjDir}ATIDrvr.a.o"		Ä	"{ATIVideoDir}ATIDrvr.a" ¶
								"{ATIVideoDir}ATIHdr.a"
	Asm {StdAOpts} -case on -o "{ObjDir}ATIDrvr.a.o" "{ATIVideoDir}ATIDrvr.a"

"{ObjDir}ATIDrvr.c.o"		Ä	"{ATIVideoDir}ATIDrvr.c" {ATIHeaders}
	C {StdCOpts} -o "{ObjDir}ATIDrvr.c.o" "{ATIVideoDir}ATIDrvr.c"

"{ObjDir}ATIDrvrImp.c.o" Ä	"{ATIVideoDir}ATIDrvrImp.c" {ATIHeaders}
	C {StdCOpts} -o "{ObjDir}ATIDrvrImp.c.o" "{ATIVideoDir}ATIDrvrImp.c"

"{ObjDir}ATISlotUtils.c.o"	Ä	"{ATIVideoDir}ATISlotUtils.c" {ATIHeaders}
	C {StdCOpts} -o "{ObjDir}ATISlotUtils.c.o" "{ATIVideoDir}ATISlotUtils.c"

"{ObjDir}ATIVideoImp.c.o" Ä	"{ATIVideoDir}ATIVideoImp.c" {ATIHeaders}
	C {StdCOpts} -o "{ObjDir}ATIVideoImp.c.o" "{ATIVideoDir}ATIVideoImp.c"

#===================================================================
# Build the extras
#===================================================================

"{ObjDir}PCIUtil.c.o"		Ä	"{ATIVideoDir}PCIUtil.c" {ATIHeaders}
	C {StdCOpts} -o "{ObjDir}PCIUtil.c.o" "{ATIVideoDir}PCIUtil.c"


#
#	The following should be in the video drivers folder.
#

VideoDriverObjs 				=	"{ObjDir}JMFBDriver.a.o"				¶
									"{ObjDir}JMFBPrimaryInit.a.o"			¶
									"{ObjDir}TFBDriver.a.o"					¶
									"{ObjDir}TFBPrimaryInit.a.o"


"{LibDir}VideoDriver.lib"		Ä	{VideoDriverObjs}
	Lib {LibOpts} {VideoDriverObjs} -o "{Targ}"


"{ObjDir}JMFBDriver.a.o"		Ä	"{VideoDriverDir}JMFBDepVideoEqu.a"		¶
									"{VideoDriverDir}JMFBDriver.a"			¶
									"{IntAIncludes}ComVideoEqu.a"
	Asm {StdAOpts} -o "{Targ}" "{VideoDriverDir}JMFBDriver.a"


"{ObjDir}JMFBPrimaryInit.a.o"	Ä	"{VideoDriverDir}JMFBDepVideoEqu.a"		¶
									"{VideoDriverDir}JMFBPrimaryInit.a"		¶
									"{IntAIncludes}ComVideoEqu.a"
	Asm {StdAOpts} -o "{Targ}" "{VideoDriverDir}JMFBPrimaryInit.a"


"{ObjDir}TFBDriver.a.o"			Ä	"{VideoDriverDir}TFBDepVideoEqu.a"		¶
									"{VideoDriverDir}TFBDriver.a"			¶
									"{IntAIncludes}ComVideoEqu.a"
	Asm {StdAOpts} -o "{Targ}" "{VideoDriverDir}TFBDriver.a"


"{ObjDir}TFBPrimaryInit.a.o"	Ä	"{VideoDriverDir}TFBDepVideoEqu.a"		¶
									"{VideoDriverDir}TFBPrimaryInit.a"		¶
									"{IntAIncludes}ComVideoEqu.a"
	Asm {StdAOpts} -o "{Targ}" "{VideoDriverDir}TFBPrimaryInit.a"


