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
#	   <SM5>	12/13/93	PN		Roll in Kaos and Horror to add support for AJ and Malcom
#									machines
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

VSCVideoDir						=	{DeclDir}VSCDeclData:

CommonHeaders					=	"{ObjDir}StandardEqu.d"					¶
									"{IntAIncludes}HardwarePrivateEqu.a"	¶
									"{AIncludes}ROMEqu.a"					¶
									"{AIncludes}Video.a"					¶
									"{IntAIncludes}SlotMgrEqu.a"			¶
									"{AIncludes}Slots.a"					¶
									"{IntAIncludes}UniversalEqu.a"			¶
									"{IntAIncludes}DepVideoEqu.a"	
				
#
#	DeclData
#

"{RsrcDir}VSCDriver.rsrc"		Ä	"{ObjDir}VSCDeclData.a.o" "{VSCVideoDir}VSCDeclData.make"				
	link {StdLOpts} {StdAlign} -rt decl=1 "{ObjDir}VSCDeclData.a.o" -o "{RsrcDir}VSCDriver.rsrc"

"{ObjDir}VSCDeclData.a.o"			Ä 	"{VSCVideoDir}VSCDriver.a"		¶
									"{VSCVideoDir}VSCPrimaryInit.a"		¶
									"{VSCVideoDir}VSCDockingHandler.a"	¶
									"{VSCVideoDir}VSCDeclData.a"		¶
									{CommonHeaders}
	Asm {StdAOpts} -o "{ObjDir}VSCDeclData.a.o" "{VSCVideoDir}VSCDeclData.a"


