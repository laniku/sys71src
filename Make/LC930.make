#
#	File:		LC930.make
#
#	Contains:	Makefile for the LC930 ROM.
#
#	Written by:	Kurt Clark
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	  <SM10>	 7/12/93	PN		Add hasCPUIDRegister feature
#	   <SM9>	  7/6/93	PN		Change InSane.rsrc to InSaneNFPU.rsrc
#	   <SM8>	  7/6/93	PN		Remove SerialIOP.rsrc
#	   <SM7>	 5/30/93	SAM		Moved ROM_EM to Tidbits.
#	   <SM6>	  4/1/93	kc		Add {ResourceDir}RomResources.r to RomLayout.Rsrc dependency.
#	   <SM5>	  4/1/93	kc		Delete RomResources.rsrc from dependency list.
#	   <SM4>	  4/1/93	kc		Add dependency to RomLayout.Rsrc
#	   <SM3>	 3/31/93	kc		Add TextDir and StdCPOpts.
#	   <SM2>	 2/22/93	CSS		Correct spelling of Resource (from Resoruce).
#	   <SM10>	01/07/93	HY		Bump ROMRelease version to 10A4.
#	   <SM9>	12/17/92	RB		Added the variable subRelease.
#	   <SM8>	12/14/92	rab		Add Craig's changes. Changed C and Pascal standard options to
#									generate 68020 code.
#	   <SM7>	12/03/92	HY		Removed hasPwrControls, PwrMgrADB, and hasMSC feature flag.
#									Changed version number of ROMRelease to 1.0A2.
#	   <SM6>	 12/2/92	kc		Add RomBase Variable. Set ROMRelease to 1.0A8. Set Commands
#									variable to {ToolDir}. Add Clean Target that deletes all of the
#									objects, libraries and resources.
#	   <SM5>	11/30/92	kc		Remove -d forRomulator. Added SM10 from supermario.make.
#
#	   <SM5>	11/30/92	kc		Remove -d forRomulator. Added SM10 from supermario.make.
#	   <SM10>	11/25/92	chp		Override the Make tool default dependencies for .a.o, .c.o, and
#									.p.o files so that {StdXOpts} are passed to the assembler or
#									compiler when applying default rules.
#	   <SM3>	11/17/92	HY		Changed ROMRelease number from 1234 to 4307 (1.0D3)
#	   <SM4>	11/23/92	kc		Update to work with the new build script.
#	   <SM2>	11/17/92	kc		Remove unused features and change standard alignment.


BuildDir		=	{Sources}BuildResults:LC930:
ImageDir		=	{BuildDir}Image:
RsrcDir			=	{BuildDir}Rsrc:
LibDir			=	{BuildDir}Lib:
ObjDir			=	{BuildDir}Obj:
TextDir			=	{BuildDir}Text:
IfObjDir		=	{ObjDir}Interface:
MakeDir			=	{Sources}Make:
ResourceDir		=	{Sources}Resources:
DeclDir			=	{Sources}DeclData:
ToolDir			=	{Sources}Tools:
ToolSrcDir		=	{Sources}Tools:ToolSource:
MiscDir			=	{Sources}Misc:
TidbitsDir		=	{Sources}Tidbits:
DriverDir		=	{Sources}Drivers:


AIncludes		=	{Sources}Interfaces:AIncludes:
CIncludes		=	{Sources}Interfaces:CIncludes:
PInterfaces		=	{Sources}Interfaces:PInterfaces:
RIncludes		=	{Sources}Interfaces:RIncludes:
IntAIncludes	=	{Sources}Internal:Asm:
IntCIncludes	=	{Sources}Internal:C:
IntPInterfaces	=	{Sources}Internal:Pascal:
IntRIncludes	=	{Sources}Internal:Rez:
Libraries		=	{Sources}Libs:Libraries:
CLibraries		=	{Sources}Libs:CLibraries:
PLibraries		=	{Sources}Libs:PLibraries:


MAOpts			=	-d TRUE=1 -d FALSE=0 -d Alignment=4 -d CPU=30 -d ROMRelease=$10A4 -wb -d SubRelease=1
MCOpts			=	-d TRUE=1 -d FALSE=0 -d Alignment=4 -d CPU=30 -d ROMRelease=$10A4 -b3 ¶
					-mbg full -mc68020
MPOpts			=	-mbg full -mc68020

RomBase			=	$40A00000

Features		=	LC930									¶
					hasSysSevenResources					¶
					Supports24Bit							¶
					BadBlockSparingEnabled					¶
					hasCPUIDRegister						¶
					CubeE									¶
					IopADB									¶
					SystemSevenOrLater						¶
					SystemSixOrLater						¶
					ViaADB									¶
					forADBKeyboards 						¶
					forAppleTalk20							¶
					forLocalizability						¶
					hasADBKeyLayouts						¶
					hasASC									¶
					hasAliasMgr 							¶
					hasApple2Fonts							¶
					hasAppleEventMgr						¶
					hasBalloonHelp							¶
					hasCommToolbox							¶
					hasCQD									¶
					hasDAFB									¶
					hasDataAccessMgr						¶
					hasEDisk								¶
					hasEditionMgr							¶
					hasEgret								¶
					hasExtendedCharacterSet					¶
					hasMDU									¶
					hasMMU									¶
					hasMac2VIA2 							¶
					hasProtectedPRAM						¶
					hasSWIM2								¶
					hasSlotMgr								¶
					hasSplineFonts							¶
					hasVDAC									¶
					hasVIAClock								¶
					hasVISA2								¶
					hasVISADecoder							¶
					isUniversal								¶
					hasRBV									¶
					NewBuildSystem							¶
					onHafMac								¶
					onMac32 								¶
					onNuMac 								¶
					ForROM


ResourceFiles	=	"{RsrcDir}ATBoot.RSRC"					¶
					"{RsrcDir}AppleEventMgr.rsrc"			¶
					"{RsrcDir}CQD.rsrc"						¶
					"{RsrcDir}ColorPicker.rsrc"				¶
					"{RsrcDir}CommToolbox.rsrc"				¶
					"{RsrcDir}ControlMgr.rsrc"				¶
					"{RsrcDir}DataAccessMgr.rsrc"			¶
					"{RsrcDir}DictionaryMgr.rsrc"			¶
					"{RsrcDir}DeclData"						¶
					"{RsrcDir}EDisk.rsrc"					¶
					"{RsrcDir}EditionMgr.rsrc"				¶
					"{MiscDir}Ethernet.rsrc" 				¶
					"{RsrcDir}Gibbly.rsrc"					¶
					"{RsrcDir}HelpMgr.rsrc"					¶
					"{RsrcDir}InSaneNFPU.rsrc"				¶
					"{RsrcDir}ListMgr.rsrc"					¶
					"{RsrcDir}MainCode.Rsrc"				¶
					"{RsrcDir}MenuMgr.rsrc"					¶
					"{RsrcDir}MiscROMRsrcs.rsrc" 			¶
					"{RsrcDir}NetBoot.rsrc"					¶
					"{RsrcDir}PPC.rsrc"						¶
					"{RsrcDir}PictUtilities.rsrc"			¶
					"{RsrcDir}ROMApple2Fonts.rsrc"			¶
					"{RsrcDir}ROMFonts.rsrc" 				¶
					"{RsrcDir}RomLayout.Rsrc"				¶
					"{RsrcDir}SCCIOP.rsrc"					¶
					"{RsrcDir}SWIMIOP.rsrc"					¶
					"{RsrcDir}Sane.rsrc" 					¶
					"{RsrcDir}Serial.rsrc"					¶
					"{RsrcDir}SerialDMA.rsrc"				¶
					"{RsrcDir}Sony.rsrc" 					¶
					"{RsrcDir}SoundMgr.rsrc"	 			¶
					"{RsrcDir}StandardFile.rsrc" 			¶
					"{RsrcDir}StdSndInput.rsrc"				¶
					"{RsrcDir}StdSndMidput.rsrc" 			¶
					"{RsrcDir}StdSndOutput.rsrc" 			¶
					"{MiscDir}VM.RSRC"						¶
					"{RsrcDir}WindowMgr.rsrc"				¶
					"{RsrcDir}kbd.rsrc"						


RomMondo						Ä	FeatureSet "{ImageDir}RomMondo"
	Beep;Beep;Beep


"{ImageDir}RomMondo"			Ä	{ResourceFiles}
	RomLayout	"{RsrcDir}RomLayout.Rsrc" -o "{Targ}" -log "{ImageDir}RomInfo"


LinkRomImage					Ä	# target for partial builds
	RomLayout "{RsrcDir}RomLayout.Rsrc" -o "{ImageDir}RomMondo" -log "{ImageDir}RomInfo"


FeatureSet						Ä
	Set FeatureSet	"`{MakeDir}FeatureList "{Features}" "{Overrides}" `" ; Export FeatureSet
	Set Commands			"{ToolDir},{Commands}"
	Set ObjDir				"{ObjDir}"		; Export ObjDir
	Set RsrcDir				"{RsrcDir}"		; Export RsrcDir
	Set TextDir				"{TextDir}"		; Export TextDir
	Set	MiscDir				"{MiscDir}"		; Export MiscDir
	Set	TidbitsDir			"{TidbitsDir}"	; Export TidbitsDir
	Set ROMBuildTime	 	"`Date -n`"		; Export ROMBuildTime
	Set AIncludes			"{AIncludes}"
	Set CIncludes			"{CIncludes}"
	Set PInterfaces			"{PInterfaces}"
	Set RIncludes			"{RIncludes}"	
	Set	Libraries			"{Libraries}"
	Set	CLibraries			"{CLibraries}"
	Set	PLibraries			"{PLibraries}" 
	Set StdAOpts			"{MAOpts} {FeatureSet} -i {IntAIncludes} {AOpts} -i {ObjDir}"
	Set StdCOpts			"{MCOpts} {FeatureSet} -i {IntCIncludes} {COpts}"
	Set StdCPOpts			"{MCPOpts} {FeatureSet} -i {IntCIncludes} {COpts}"
	Set StdPOpts			"{MPOpts} {FeatureSet} {POpts} -i {IntPInterfaces} -r"
	Set StdROpts			"{FeatureSet} {ROpts} -i {IntRIncludes} -i {RIncludes}"
	Set	DSP3210_Temp		"{ObjDir}"		; Export DSP3210_Temp
	Set	DSP3210_Tools		"{ToolDir}"		; Export DSP3210_Tools
	Set DSP3210_Aux 		"{ToolDir}"		; Export DSP3210_Aux
	Set DSP3210_Includes 	"{ToolDir}"		; Export DSP3210_Includes
	Set DSP3210_Libraries 	"{ToolDir}"		; Export DSP3210_Libraries
	Set DSP3210_AsmPP 		d32cpp			; Export DSP3210_AsmPP
	Set StdLOpts			"{LOpts} -mf -t rsrc -c RSED -sg Main"
	Set StdLibOpts			"{LibOpts} -mf"
	Set StdAlign			"{Align} -ac 4 -ad 4"
	Set StdVOpts			"{VOpts}"

"{RsrcDir}RomLayout.Rsrc"		Ä	"{MakeDir}LC930Layout.r" "{ResourceDir}RomResources.r" "{IntRIncludes}RomTypes.r"
	Rez	{StdROpts} "{MakeDir}LC930Layout.r" -i "{ResourceDir}" -o "{targ}" -d RomBase={RomBase}


Clean							Ä
	Delete -n -i "{ImageDir}"Å
	Delete -n -i "{RsrcDir}"Å
	Delete -n -i "{LibDir}"Å
	Delete -n -i "{ObjDir}"Å
	Delete -n -i "{IfObjDir}"Å


# Following are essentially the default rules from the Make tool, modified to use
# {StdAOpts}, {StdCOpts}, and {StdPOpts} as they are defined in this file.
# These options are supersets of the default {AOpts}, {COpts}, and {POpts}.

.a.o							Ä	.a
	{Asm} {StdAOpts} -o {Targ} {DepDir}{Default}.a

.c.o							Ä	.c
	{C} {StdCOpts} -o {Targ} {DepDir}{Default}.c

.p.o							Ä	.p
	{Pascal} {StdPOpts} -o {Targ} {DepDir}{Default}.p

.cp.o							Ä	.c
	{CPlus} {StdCPOpts} -o {Targ} {DepDir}{Default}.cp


#include {ToolSrcDir}Tools.make

#include {MakeDir}MainCode.make

#include {DeclDir}DeclData.make

#include {DriverDir}Drivers.make

#include {ResourceDir}Resources.make
