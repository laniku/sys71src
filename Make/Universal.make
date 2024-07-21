#
#	File:		Universal.make
#
#	Contains:	Makefile for the SuperMario ROM.
#
#	Written by:	Kurt Clark
#
#	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	  <SM39>	  2/1/94	chp		Simplify the build command for the ÒCleanÓ target: wildcard
#									substitution is sloppy if there is no match and seems to result
#									in :Obj:Interface: getting deleted.
#	  <SM38>	 12/2/93	rab		Changed ROMVersion to $0006É
#	  <SM37>	11/19/93	chp		Add BuildResults Text directories to the Delete list in the
#									ÒCleanÓ target.
#	  <SM36>	 11/9/93	rab		Changed ROMVersion to $0005 for the new Universal release.
#	  <SM35>	 11/8/93	SAM		Enabled hasROMGibbly for the "universal" build.
#	  <SM34>	 9/25/93	SAM		Removed hasHMC (PDM's memory controller) from the "universal"
#									ROM feature list.
#	  <SM33>	 9/22/93	kc		Turn on symbols.
#	  <SM32>	  9/2/93	KH		change hasSCSIDiskMode to hasSCSIDiskModeFeature
#	  <SM31>	 7/28/93	kc		Turn on figment.
#	  <SM30>	 7/28/93	kc		Bump the version to $04 and add -mf option to RomLayout.
#	  <SM29>	 7/21/93	RC		back out <sm 28>
#	  <SM27>	  7/1/93	BT		Add hasCacheTypeCPU for Figment. This turns on cache flushing at
#									the appropriate points in the new memory manager.
#	  <SM26>	 6/28/93	PN		Fix comments
#	  <SM25>	 6/28/93	PN		Add feature hasMACE to the list
#	  <SM24>	 6/24/93	CSS		Update to ROMVersion $03.
#	  <SM23>	 6/14/93	kc		Roll in Ludwig.
#	  <SM22>	  6/1/93	CSS		Update to ROMVersion $02.
#	  <SM21>	 5/30/93	SAM		Moved ROM_EM to Tidbits.
#	  <SM20>	 5/21/93	CSS		Add international features: hasDoubleByte, Script_Char_Extra,
#									hasPenFraction, hasFullKerning, hasGlyphState.
#	  <SM19>	 5/18/93	CSS		Update to ROMVersion $01.
#	  <SM18>	  5/5/93	CSS		Update ROMVersion to $00. The last build was $AF (or Alpha 15).
#									Rather than do $B0 (or beta 0), since we are not following a
#									normal Alpha/Beta/GM schedule, I will call this release $00 and
#									the subsequent releases $01,... This to avoid implying that
#									SuperMario is actually beta.
#	  <SM17>	 4/20/93	CSS		Update version to a15. Next version update we will call $20 as
#									this one is called $af and we aren't actually in a alpha/beta
#									cycle with the Universal ROM.
#	  <SM16>	  4/6/93	CSS		Changed release version to a14.
#	  <SM15>	  4/1/93	kc		Add {ResourceDir}RomResources.r to RomLayout.Rsrc dependency.
#	  <SM14>	  4/1/93	kc		Delete RomResources.rsrc from dependency list.
#	  <SM13>	  4/1/93	kc		Add dependency to RomLayout.Rsrc
#	  <SM12>	 3/31/93	kc		Add TextDir and StdCPOpts.
#		<11>	 3/31/93	IH		Set up standard equates define for fasttraps
#	  <SM10>	 3/19/93	CSS		Remove Sadism.rsrc from the build as this stuff is junk.
#	   <SM9>	 3/11/93	PN		Put Sane.rsrc back for Pack 7
#	   <SM8>	  3/8/93	PN		From the conversation with Jon Okada. We should use InSane for
#									NonFPU pack 4 and 5 from now on.
#	   <SM7>	  3/5/93	PN		Stop and exit whenever ROMLayout fails
#	   <SM6>	 2/28/93	chp		Update from Ludwig. <LW6>
#	   <SM5>	 2/23/93	CSS		Fix header.
#	   <SM4>	 2/22/93	kc		Fix misspelling of ResourceDir.
#	   <SM3>	 2/22/93	CSS		Correct spelling of Universal.make in heading.
#	   <SM2>	 2/22/93	CSS		Correct spelling of Resource (from Resoruce).
#	  <SM30>	 2/15/93	kc		Add AppleTalk.ROM.RSRC.
#	  <SM29>	 2/10/93	RB		Changed release version to a13.
#	  <SM28>	  2/2/93	GMR		Added hasSwim3 feature.
#	   <LW6>	12/29/92	chp		Removed SerialIOP.rsrc from the build. All traditional serial
#									resources are now found in Serial.rsrc.
#	  <SM27>	12/29/92	RB		Added the feature hasSysSevenResources, which should have been
#									set here last week.
#	  <SM26>	12/29/92	HY		Remove hasNewSoundMgr feature flag.  Reverting back to 7.1 sound mgr.
#	  <SM25>	12/23/92	kc		Remove DSPHardware from the build.
#	  <SM24>	12/18/92	RB		Added the backlight driver and its make file.
#	  <SM23>	12/17/92	RB		Added some of the new features. Added the SuperMario sub-release
#									version. LC930 is the first release, Cyclone is 2, etc.
#	  <SM22>	12/15/92	CSS		Add dictionary manager to the project.
#	  <SM21>	12/11/92	chp		Reinstated resource names. (Woof, woof.)
#	  <SM20>	12/11/92	chp		By popular demand, Macsbug symbols are reinstated.
#	  <SM19>	12/11/92	chp		Changed C and Pascal standard options to suppress MacsBug
#									symbols and to generate 68020 code.
#	  <SM18>	12/11/92	kc		Remove the post build beeps.
#	  <SM17>	12/10/92	FU		Added DSPHardware.c to the list of resource files
#	  <SM16>	 12/9/92	DH		Added new I2C component.
#	  <SM15>	12-04-92	jmp		Added VSCDeclData to the list of things to make.
#	  <SM14>	 12/3/92	RB		Added the feature has2MegROMOrMore.
#	  <SM13>	 12/2/92	kc		Add RomBase Variable. Set ROMRelease to 1.0A8. Set Commands
#									variable to {ToolDir}. Add Clean Target that deletes all of the
#									objects, libraries and resources.
#	  <SM12>	 12/1/92	ejb		 add RTDrvr.rsrc dependency to resource files
#	  <SM11>	11/30/92	EH		Add hasPratt for the Blackbird memory controller chip.
#	  <SM10>	11/30/92	kc		Remove -d forRomulator.
#	   <SM9>	11/29/92	PW		Removed the COUSIN_ITT feature (hasAsyncSCSI is all we need).
#	   <SM8>	11/25/92	chp		Override the Make tool default dependencies for .a.o, .c.o, and
#									.p.o files so that {StdXOpts} are passed to the assembler or
#									compiler when applying default rules.
#	   <SM7>	11/24/92	RB		Use the feature hasROM_EM so it can be easily taken out.
#	   <SM6>	11/23/92	kc		Update to work with the new build script.
#	   <SM5>	11/14/92	kc		Change link option used to name segment from -sg to -sn.
#	   <SM4>	11/12/92	kc		Add variables used by the dsp tools.
#	   <SM4>	11/12/92	CSS		Fix problem with Tidbits directory and removed StandardEqu.make
#									as this is in the MainCode.make file.  Also, fix problems with 
#									build of ROM_EM.rsrc.
#	   <SM3>	11/11/92	RB		Added the feature hasNewSoundMgr and hasDSP, hasSCSIDiskMode,
#									hasAsyncSCSI, hasAppleTalkInROM, hasNewAge, hasVideoIn,
#									COUSIN_ITT Added standard RIncludes and ROM_EM.
#	   <SM2>	 11/3/92	mal		(kc) Add MAOpts and MCOpts.
#

BuildDir		=	{Sources}BuildResults:Universal:
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

ROMVersion		=	$0006

MAOpts			=	-d TRUE=1 -d FALSE=0 -d Alignment=16 -d CPU=40 -d ROMRelease={ROMVersion} -wb -d SubRelease=2
MCOpts			=	-d TRUE=1 -d FALSE=0 -d Alignment=16 -d CPU=40 -d ROMRelease={ROMVersion} -b3		¶
					-mbg full -mc68020
MPOpts			=	-mbg full -mc68020

RomBase			=	$40800000

Features		=	hasROMGibbly							¶
					hasCacheTypeCPU							¶
					hasSCSIDiskModeFeature					¶
					hasSysSevenResources					¶
					hasVMinROM								¶
					hasYMCA									¶
					hasCPUIDRegister						¶
					has2MegROMOrMore						¶
					hasAppleTalkInROM						¶
					hasNewAge								¶
					hasVideoIn								¶
					hasMace									¶
					hasAsyncSCSI							¶
					hasDSP									¶
					BadBlockSparingEnabled					¶
					CubeE									¶
					IopADB									¶
					OssADB									¶
					PwrMgrADB								¶
					SystemSevenOrLater						¶
					SystemSixOrLater						¶
					ViaADB									¶
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
					hasDJMEMC								¶
					hasDataAccessMgr						¶
					hasDoubleByte							¶
					hasEDisk								¶
					hasEclipseVIA2							¶
					hasEditionMgr							¶
					hasEgret								¶
					hasExtendedCharacterSet					¶
					hasFMC									¶
					hasFullKerning							¶
					hasGDU									¶
					hasGlyphState							¶
					hasIdle 								¶
					hasIopScc								¶
					hasIopSwim								¶
					hasJaws 								¶
					hasLCDScreen							¶
					hasMDU									¶
					hasMMU									¶
					hasMSC									¶
					hasMac2VIA2 							¶
					hasNetBoot								¶
					hasNewHeapMgr							¶
					hasNiagra								¶
					hasOrwell								¶
					hasOss									¶
					hasPenFraction							¶
					hasPratt								¶
					hasProtectedPRAM						¶
					hasSCSI96								¶
					hasSWIM2								¶
					hasSwim3								¶
					hasSlotMgr								¶
					hasSonora								¶
					hasSplineFonts							¶
					hasVDAC									¶
					hasVIAClock								¶
					hasVISA2								¶
					hasVISADecoder							¶
					hasWaimeaVIA2							¶
					isUniversal								¶
					hasPSC									¶
					hasPwrControls							¶
					hasPwrMgrClock							¶
					hasRBV									¶
					hasSlotMgr								¶
					hasSplineFonts							¶
					hasVIAClock 							¶
					hasWaimeaVIA2							¶
					NewBuildSystem							¶
					isUniversal								¶
					onHafMac								¶
					onMac32 								¶
					onNuMac 								¶
					Script_Char_Extra						¶
					ForROM

#
# If you add a file to "ResourceFiles", you MUST add 'rrsc' entries to RomResources.r
# to get the rsrc's pulled out of your resource and into the ROM image.
# See "{ImageDir}RomMondo" & "{RsrcDir}RomResources.rsrc" targets.
#
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
					"{RsrcDir}EDisk.rsrc"					¶
					"{RsrcDir}EditionMgr.rsrc"				¶
					"{MiscDir}Ethernet.rsrc" 				¶
					"{RsrcDir}Gibbly.rsrc"					¶
					"{RsrcDir}HelpMgr.rsrc"					¶
					"{RsrcDir}InSane.rsrc"					¶
					"{RsrcDir}InSaneNFPU.rsrc"				¶
					"{RsrcDir}I2CC.rsrc"					¶
					"{RsrcDir}I2CT.rsrc"					¶
					"{RsrcDir}ListMgr.rsrc"					¶
					"{RsrcDir}MACEecfg.rsrc"				¶
					"{RsrcDir}MainCode.Rsrc"				¶
					"{RsrcDir}MenuMgr.rsrc"					¶
					"{RsrcDir}MiscROMRsrcs.rsrc" 			¶
					"{RsrcDir}NetBoot.rsrc"					¶
					"{RsrcDir}NewAge.rsrc"					¶
					"{RsrcDir}PPC.rsrc"						¶
					"{RsrcDir}PictUtilities.rsrc"			¶
					"{RsrcDir}ROMApple2Fonts.rsrc"			¶
					"{RsrcDir}ROMFonts.rsrc" 				¶
					"{RsrcDir}RTDrvr.rsrc"					¶
					"{RsrcDir}RTMgr.rsrc"					¶
					"{RsrcDir}RTSnd.rsrc"					¶
					"{RsrcDir}RTSndIn.rsrc"					¶
					"{RsrcDir}RomLayout.Rsrc"				¶
					"{RsrcDir}SCCIOP.rsrc"					¶
					"{RsrcDir}SWIMIOP.rsrc"					¶
					"{RsrcDir}Sane.rsrc" 					¶
					"{RsrcDir}Serial.rsrc"					¶
					"{RsrcDir}SerialDMA.rsrc"				¶
					"{RsrcDir}Sony.rsrc" 					¶
					"{RsrcDir}SoundMgr.rsrc" 				¶
					"{RsrcDir}StandardFile.rsrc" 			¶
					"{RsrcDir}StdSndInput.rsrc"				¶
					"{RsrcDir}StdSndMidput.rsrc" 			¶
					"{RsrcDir}StdSndPlayer.rsrc" 			¶
					"{RsrcDir}StdSndOutput.rsrc" 			¶
					"{RsrcDir}VDigC.rsrc"					¶
					"{RsrcDir}VDigT.rsrc"					¶
					"{MiscDir}VM.RSRC"						¶
#					"{RsrcDir}VSCDeclData"					¶
					"{RsrcDir}WindowMgr.rsrc"				¶
					"{RsrcDir}ZoundBlueInputAdaptor.rsrc"	¶
					"{RsrcDir}kbd.rsrc"						


RomMondo						Ä	FeatureSet "{ImageDir}RomMondo"
	beep 1300,3,25 0,1,0  1200,3,25 0,1,0 1100,3,25 0,1,0  1000,3,25 


"{ImageDir}RomMondo"			Ä	{ResourceFiles}
	"{ToolDir}ROMLayout" -mf "{RsrcDir}RomLayout.Rsrc" -o "{Targ}" -log "{ImageDir}RomInfo" || Exit {Status}


LinkRomImage					Ä	# target for partial builds
	"{ToolDir}ROMLayout" -mf "{RsrcDir}RomLayout.Rsrc" -o "{ImageDir}RomMondo" -log "{ImageDir}RomInfo"


FeatureSet						Ä
	Set FeatureSet	"`{MakeDir}FeatureList "{Features}" "{Overrides}" `" ; Export FeatureSet
	Set Commands			"{ToolDir},{Commands}"
	Set ObjDir				"{ObjDir}"		; Export ObjDir
	Set RsrcDir				"{RsrcDir}"		; Export RsrcDir
	Set TextDir				"{TextDir}"		; Export TextDir
	Set	MiscDir				"{MiscDir}"		; Export MiscDir
	Set	TidbitsDir			"{TidbitsDir}"	; Export TidbitsDir
	Set ROMBuildTime 		"`Date -n`"		; Export ROMBuildTime
	Set AIncludes			"{AIncludes}"
	Set CIncludes			"{CIncludes}"
	Set PInterfaces			"{PInterfaces}"
	Set RIncludes			"{RIncludes}"	
	Set	Libraries			"{Libraries}"
	Set	CLibraries			"{CLibraries}"
	Set	PLibraries			"{PLibraries}" 
	Set StdAOpts			"{MAOpts} {FeatureSet} -i {IntAIncludes} {AOpts} -i {ObjDir} -sym on,nolines,notypes,novars"
	Set StdCOpts			"{MCOpts} {FeatureSet} -i {IntCIncludes} {COpts} -r -sym on,nolines,notypes,novars"
	Set StdCPOpts			"{MCPOpts} {FeatureSet} -i {IntCIncludes} {COpts}"
	Set StdPOpts			"{MPOpts} {FeatureSet} -i {IntPInterfaces} {POpts} -r"
	Set StdROpts			"{FeatureSet} {ROpts} -i {IntRIncludes} -i {RIncludes}"
	Set	DSP3210_Temp		"{ObjDir}"		; Export DSP3210_Temp
	Set	DSP3210_Tools		"{ToolDir}"		; Export DSP3210_Tools
	Set DSP3210_Aux 		"{ToolDir}"		; Export DSP3210_Aux
	Set DSP3210_Includes 	"{ToolDir}"		; Export DSP3210_Includes
	Set DSP3210_Libraries 	"{ToolDir}"		; Export DSP3210_Libraries
	Set DSP3210_AsmPP 		d32cpp			; Export DSP3210_AsmPP
	Set StdLOpts			"{LOpts} -mf -t rsrc -c RSED -sg Main"
	Set StdLibOpts			"{LibOpts} -mf -sym on,nolines,notypes,novars"
	Set StdAlign			"{Align} -ac 16 -ad 16"
	Set StdVOpts			"{VOpts}"
	Set StdEquAOpts			"`{MakeDir}CreateStdEquAOptions "{FeatureSet}"`"	; Export StdEquAOpts

"{RsrcDir}RomLayout.Rsrc"		Ä	"{MakeDir}UniversalLayout.r" "{ResourceDir}RomResources.r" "{IntRIncludes}RomTypes.r"
	Rez	{StdROpts} "{MakeDir}UniversalLayout.r" -i "{ResourceDir}" -o "{targ}" -d RomBase={RomBase}


Clean							Ä
	Delete -i `Files -f -r -o -s "{BuildDir}"` ³ Dev:Null


# Following are essentially the default rules from the Make tool, modified to use
# {StdAOpts}, {StdCOpts}, and {StdPOpts} as they are defined in this file.
# These options are supersets of the default {AOpts}, {COpts}, and {POpts}.

.a.o							Ä	.a
	{Asm} {StdAOpts} -o {Targ} {DepDir}{Default}.a

.c.o							Ä	.c
	{C} {StdCOpts} -o {Targ} {DepDir}{Default}.c

.cp.o							Ä	.c
	{CPlus} {StdCPOpts} -o {Targ} {DepDir}{Default}.cp

.p.o							Ä	.p
	{Pascal} {StdPOpts} -o {Targ} {DepDir}{Default}.p


#include {ToolSrcDir}Tools.make

#include {MakeDir}MainCode.make

#include {DeclDir}DeclData.make

#include {DriverDir}Drivers.make

#include {ResourceDir}Resources.make
