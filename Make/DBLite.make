#
#	File:		DBLite.make
#
#	Contains:	Makefile for the DBLite ROM.
#
#	Written by:	Kurt Clark
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	  <SM13>	12/14/93	PN		Enalble Gibbly in ROM
#	  <SM12>	12/13/93	PN		Roll in KAOs and Horror changes to support Malcom and AJ
#									machines. This is a make file for 603 PowerBook.
#	  <SM11>	 9/27/93	PN		Turn on Figment flag to bring dblite to the 90s
#	  <SM10>	 9/23/93	PN		Change feature and delete extra resources to make 1 Meg ROM
#	   <SM9>	  9/1/93	SKH		Remove SerialIOP reference
#	   <SM8>	 5/30/93	SAM		Moved ROM_EM to Tidbits.
#	   <SM7>	  4/1/93	kc		Add {ResourceDir}RomResources.r to RomLayout.Rsrc dependency.
#	   <SM6>	  4/1/93	kc		Delete RomResources.rsrc from dependency list.
#	   <SM5>	  4/1/93	kc		Add dependency to RomLayout.Rsrc
#	   <SM4>	 3/31/93	kc		Add TextDir and StdCPOpts.
#	   <SM3>	  3/9/93	CSS		Add InSaneNFPU.rsrc to the build and remove Sane.rsrc
#									from the build.
#	   <SM2>	  3/2/93	CSS		More fixes to get this damn thing to work.
#	   <SM1>	 2/22/93	CSS		Checkin in new place and fix some variables per
#									similar changes to the LC930.make file.
#	   <SM1>	 2/11/93	CSS		Checkin from work done by Kurt and Ricardo.
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


BuildDir		=	{Sources}BuildResults:DBLite:
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


MAOpts			=	-d TRUE=1 -d FALSE=0 -d Alignment=16 -d CPU=20 -d ROMRelease=$10D1 -wb -d SubRelease=30 -blksize 62
MCOpts			=	-d TRUE=1 -d FALSE=0 -d Alignment=16 -d CPU=20 -d ROMRelease=$10D1 -b3 -mc68020 -mbg full -blksize 62
MPOpts			=	-mbg full -mc68020

RomBase			=	$40000000

# add DBLite for Duo ROM
Features		=	BlackBirdDebug							¶
					hasCacheTypeCPU							¶
					hasSCSIDiskModeFeature					¶
					hasSysSevenResources					¶
					hasCPUIDRegister						¶
					has2MegROMOrMore						¶
					hasAppleTalkInROM						¶
					BadBlockSparingEnabled					¶
					CubeE									¶
					SupportNativeComponents					¶
					hasMixedMode							¶
					nonSerializedIO							¶
					PwrMgrADB								¶
					SystemSevenOrLater						¶
					SystemSixOrLater						¶
					ViaADB									¶
					IopADB									¶
					forADBKeyboards 						¶
					forAppleTalk20							¶
					forLocalizability						¶
					has040MMU								¶
					hasADBKeyLayouts						¶
					hasASC									¶
					hasAliasMgr 							¶
					hasApple2Fonts							¶
					hasAppleEventMgr						¶
					hasBalloonHelp							¶
					hasBattery								¶
					hasCommToolbox							¶
					hasCQD									¶
					hasDAFB									¶
					hasDataAccessMgr						¶
					hasDoubleByte							¶
					hasEDisk								¶
					hasEditionMgr							¶
					hasEgret								¶
					hasExtendedCharacterSet					¶
					hasIdle 								¶
					hasJaws 								¶
					hasLCDScreen							¶
					hasMMU									¶
					hasMSC									¶
					hasMac2VIA2 							¶
					hasNetBoot								¶
					hasNewHeapMgr							¶
					hasNiagra								¶
					hasPratt								¶
					hasProtectedPRAM						¶
					hasSCSI96								¶
					hasSWIM2								¶
					hasSlotMgr								¶
					hasSplineFonts							¶
					hasVDAC									¶
					isUniversal								¶
					hasPwrControls							¶
					hasPwrMgrClock							¶
					hasRBV									¶
					hasSplineFonts							¶
					hasVIAClock 							¶
					NewBuildSystem							¶
					isUniversal								¶
					onHafMac								¶
					onMac32 								¶
					onNuMac 								¶
					hasROMGibbly 							¶
					ForROM


ResourceFiles	=	"{MiscDir}AppleTalk.ROM.RSRC"			¶
					"{RsrcDir}AppleEventMgr.rsrc"			¶
					"{RsrcDir}ATBoot.RSRC"					¶
					"{RsrcDir}Backlight.rsrc"				¶
					"{RsrcDir}CQD.rsrc"						¶
					"{RsrcDir}ColorPicker.rsrc"				¶
					"{RsrcDir}CommToolbox.rsrc"				¶
					"{RsrcDir}ControlMgr.rsrc"				¶
					"{RsrcDir}DataAccessMgr.rsrc"			¶
					"{RsrcDir}DictionaryMgr.rsrc"			¶
					"{RsrcDir}DeclData"						¶
					"{RsrcDir}VSCDriver.rsrc"				¶
					"{RsrcDir}EDisk.rsrc"					¶
					"{RsrcDir}EditionMgr.rsrc"				¶
					"{MiscDir}Ethernet.rsrc" 				¶
					"{RsrcDir}Gibbly.rsrc"					¶
					"{MiscDir}GoNativeResources"			¶
					"{MiscDir}EmulatorAccelerations.rsrc"	¶
					"{RsrcDir}HelpMgr.rsrc"					¶
					"{RsrcDir}InSane.rsrc"					¶
					"{RsrcDir}InSaneNFPU.rsrc" 				¶
					"{RsrcDir}Sane.rsrc" 					¶
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
					"{RsrcDir}Serial.rsrc"					¶
					"{RsrcDir}Sony.rsrc" 					¶
					"{RsrcDir}SoundMgr.rsrc"	 			¶
					"{RsrcDir}StandardFile.rsrc" 			¶
					"{MiscDir}VM.RSRC"						¶
					"{RsrcDir}WindowMgr.rsrc"				¶
					"{RsrcDir}kbd.rsrc"						


RomMondo						Ä	FeatureSet "{ImageDir}RomMondo"
	Beep;Beep;Beep


"{ImageDir}RomMondo"			Ä	{ResourceFiles}
	RomLayout	-mf "{RsrcDir}ROMLayout.Rsrc" -o "{Targ}" -log "{ImageDir}RomInfo"


LinkRomImage					Ä	# target for partial builds
	RomLayout -mf "{RsrcDir}ROMLayout.Rsrc" -o "{ImageDir}RomMondo" -log "{ImageDir}RomInfo"


FeatureSet						Ä
	Set FeatureSet			"`{MakeDir}FeatureList "{Features}" "{Overrides}" `" ; Export FeatureSet
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
	Set StdAOpts			"{MAOpts} {FeatureSet} -i {IntAIncludes} {AOpts} -i {ObjDir} -sym on,nolines,notypes,novars"
	Set StdCOpts			"{MCOpts} {FeatureSet} -i {IntCIncludes} {COpts} -sym on,nolines,notypes,novars"
	Set StdCPOpts			"{MCPOpts} {FeatureSet} -i {IntCIncludes} {COpts}"
	Set StdPOpts			"{MPOpts} {FeatureSet} {POpts} -i {IntPInterfaces} -r"
	Set StdROpts			"{FeatureSet} {ROpts} -i {IntRIncludes} -i {RIncludes}"
	Set StdLOpts			"{LOpts} -mf -t rsrc -c RSED -sg Main"
	Set StdLibOpts			"{LibOpts} -mf -sym on,nolines,notypes,novars"
	Set StdAlign			"{Align} -ac 16 -ad 16"
	Set StdVOpts			"{VOpts}"
	Set StdEquAOpts			"`{MakeDir}CreateStdEquAOptions "{FeatureSet}"`"	; Export StdEquAOpts

"{RsrcDir}ROMLayout.Rsrc"		Ä	"{MakeDir}DBLiteLayout.r" "{ResourceDir}RomResources.r" "{IntRIncludes}RomTypes.r"
	Rez	{StdROpts} "{MakeDir}DBLiteLayout.r" -i "{ResourceDir}" -o "{targ}" -d RomBase={RomBase} -c RSED -t rsrc
	
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

#include {DeclDir}VSCDeclData:VSCDeclData.make
 
#include {DriverDir}Drivers.make

#include {ResourceDir}Resources.make

