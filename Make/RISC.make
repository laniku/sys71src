#
#	File:		RISC.make
#
#	Contains:	Makefile for the RISC ROM.
#
#	Written by:	Kurt Clark
#
#	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	  <SM76>	 1/31/94	GS		Update Version for TNT D4c1 build.
#	  <SM75>	 1/10/94	chp		TNT D3C1 build. Simplify the build command for the ÒCleanÓ
#									target: wildcard substitution is sloppy if there is no match and
#									seems to result in :Obj:Interface: getting deleted.
#	  <SM74>	 12/2/93	chp		TNT D2C1 build.
#	  <SM73>	11/19/93	chp		Add BuildResults Text directories to the Delete list in the
#									ÒCleanÓ target.
#	  <SM72>	11/10/93	fau		Added a 'hasGrandCentral' feature (TNT's Interrupt Controller)
#									and revved the release to D1C1 for TNT's D1 release.
#	  <SM71>	 11/9/93	KW		PDM build flags are NO longer always true.  PDM must include
#									them on the build line
#	  <SM70>	 11/3/93	RC		Changed rev for fc1 build, make PDM flags true by default,
#									turned off symbols
#	  <SM69>	10/20/93	BT		#1118912; for some reason hasRISCV0ResMgrPatches is not in here.
#									Add it.
#	  <SM68>	10/15/93	SAM		Turning on forPDMProto by default.
#	  <SM67>	10/14/93	pdw		Added a dependency on AppleTalk.ROM.rsrc.
#	  <SM66>	 10/6/93	RC		Bump rev up to B2E1
#	  <SM65>	 9/30/93	IH		Add hasDisplayMgrWindows feature to PDM. This allows the display
#									manager in the gibbly without patching out the window manager on
#									PDM. Having it in ROM and on Disk are okay. Make sure that the
#									gibbly is built with hasDisplayMgr before turning it off in ROM
#									or you will be making unimplemented trap calls from the window
#									manager.
#	  <SM64>	 9/28/93	SAM		From mc900ftjesus.
#	  <MC10>	 9/27/93	SAM		Removed VMinROM cuz its not. Turned symbols off cuz its slowww.
#	   <MC9>	 9/26/93	pdw		Changed alignment to 8 which makes a little more sense than 16
#									but not as much sense as 64 but since that doesn't work, 8 it
#									is.  Why not 4?  I thought there might be a little better bus
#									utilization if things were on 8 byte alignment.
#	  <SM63>	 9/22/93	kc		Turn on symbols.
#	  <SM62>	 9/13/93	RC		Bump Rev to A5E1
#	  <SM61>	  9/2/93	SKH		change hasSCSIDiskMode to hasSCSIDiskModeFeature
#	  <SM60>	 8/23/93	RC		bumping rev again
#	  <SM59>	 8/23/93	RC		bump Rev level to A4C1
#	  <SM58>	 8/20/93	RC		bumbed up rev level
#	  <SM57>	 8/11/93	RC		Rev Version Number
#	  <SM56>	  8/9/93	JDR		remove -w from StdCOpts so we can really get warning messages
#									when asked for
#	  <SM55>	 7/31/93	SAM		Added -mf option to ROMLayout calls.
#	  <SM54>	 7/21/93	RC		Changed Power_PC_Native_Components to SupportNativeComponents
#	  <SM53>	 7/21/93	SAM		Been smokin' too much crack.  Really, lose the -bigseg for the C
#									compiler.
#	  <SM52>	 7/21/93	SAM		Removed the -bigSeg option from the C stdoptions
#	  <SM51>	 7/20/93	SAM		Set the CPU type to 020 for PDM.  Enable full optization for the
#									C compiler and set the I/O buffer block size to the max (for
#									faster builds).
#	  <SM50>	 7/18/93	RC		Upping Rev Level to A3E3
#	  <SM49>	 7/14/93	RC		added hasAMIC feature flag and changed Rel level to A3E2
#	  <SM48>	  7/7/93	RC		turned on Native components Mgr support in RISC and turned of
#									warnings in the C comiples, due to warnings in the
#									ThingManager.c which I could not kill in the code
#	  <SM47>	 6/30/93	RC		Added cyclone vdigs back in
#	  <SM46>	 6/29/93	RC		Stipped out the cyclone MACEecfg resources which were doing
#									nothing for PDM
#	  <SM45>	 6/24/93	RC		Bumped Rev to a2e1, took out cyclone vdigs from RISC build, took
#									out non-PDM Ethernet.rsrc
#	  <SM44>	 6/14/93	kc		Add Maceecfg.rsrc to dependency.
#	  <SM43>	 6/11/93	RC		eliminated the use of all DSP tools to build any part of the
#									Risc ROM
#	  <SM42>	 5/30/93	SAM		Moved ROM_EM to Tidbits.
#	  <SM41>	 5/29/93	RC		Release num change
#	  <SM40>	 5/26/93	RC		Bumped Rev to D9C1 and I also added the feature flags to turn on
#									the international support, so that Double Byte TrueType would
#									work.
#	  <SM39>	 5/20/93	BT		Update build to only include Figment under conditional compile
#									flag "hasNewHeapMgr". This is included here as a standard build
#									feature.
#	  <SM38>	 5/10/93	SAM		Bumping version to d7c4.
#	  <SM37>	  5/9/93	RC		new rom rev (d7c3)
#	  <SM36>	  5/3/93	RC		going to D7c1 build
#	  <SM35>	 4/20/93	SAM		Added a type and creator to the Rez line that builds
#									RISCLayout.rsrc, just cuz.
#	  <SM34>	 4/15/93	RC		Rev version to D6C2 (didn't pass w/ C1)
#	  <SM33>	  4/9/93	RC		uping rev version to D6 C1
#		<32>	  4/8/93	IH		Re-introduce Display Manager as RISC feature.
#	  <SM31>	  4/8/93	RC		Making PDM ROM build easier and Smurf build harder (I care a lot
#									less about Smurf)
#	  <SM30>	  4/7/93	RC		Move hasCAppleTalkInROM to build command, so Smurf will build
#									correctly
#	  <SM29>	  4/2/93	BT		Shouldn't have Display Manager as a feature until it works!
#									Remove hasDisplayMgr from features.
#	  <SM28>	  4/1/93	kc		Fix last check in comment.
#	  <SM27>	  4/1/93	kc		Add {ResourceDir}RomResources.r to RomLayout.Rsrc dependency.
#	  <SM26>	  4/1/93	kc		Delete RomResources.rsrc from dependency list.
#	  <SM25>	  4/1/93	kc		Add dependency to RomLayout.Rsrc
#	  <SM24>	 3/31/93	kc		Add TextDir and StdCPOpts.
#		<23>	 3/31/93	IH		Add hasDisplayMgr to Risc features.
#	  <SM22>	 3/24/93	dwc		Re-enable CAppleTalk to use patched AT58.
#	  <SM21>	 3/24/93	dwc		Disabled hasCAppleTalkInROM to avoid a conflict with ENET.
#	  <SM19>	 3/22/93	RC		D6E1 version timed
#	  <SM18>	 3/19/93	CSS		Remove Sadism.rsrc from the build as this stuff is junk.
#	  <SM17>	 3/16/93	SAM		Removed a ÒfeatureÓ that should never have been in the ROM.
#	  <SM16>	 3/14/93	RC		Upped rev to D5C2
#	  <SM15>	 3/11/93	RC		Ready for D5C1 Version of the Risc Rom
#	  <SM14>	 3/10/93	RC		One last fix to keep Sane happy to the end of the build (I added
#									the SANE.rsrc which is expected by the ROMResource.r
#	  <SM13>	  3/9/93	RC		Sorry about undoing the last rev, but I was facked out by
#									GoNative
#	  <SM12>	  3/9/93	RC		Took out InSaneNFPU resource
#	  <SM11>	  3/8/93	RC		Increament ROM Release version to D5E3
#	  <SM10>	  3/8/93	PN		Change Sane.rsrc to InSaneNFPU.rsrc
#	   <SM9>	  3/8/93	RC		Turned on C version of AppleTalk
#	   <SM8>	  3/5/93	RC		Uped the version of the ROM to D5E2
#	   <SM7>	  3/4/93	RC		Took out hasPSC from RISC build
#	   <SM6>	  3/2/93	SAM		Removed SerialIOP.rsrc.
#	   <SM5>	  3/2/93	RC		Changed Build Version to D5E1 (Development version 5,
#									Engineering Build 1
#	   <SM4>	 2/22/93	RC		Took out hasLCDScreen feature
#	   <SM3>	 2/22/93	RC		Added I2c Resources
#	   <SM2>	 2/22/93	CSS		Correct spelling of Resource (from Resoruce).
#	  <SM13>	  2/6/93	RC		Cleaned up Features list a little
#	  <SM12>	  2/4/93	RC		Added PDMMaceDir define to make file
#	  <SM11>	  2/4/93	dwc		Add PDM ENET driver rsrc.
#	  <SM10>	  2/2/93	GMR		Added hasSwim3 feature.
#	   <SM9>	 1/19/93	RC		Getting ready to build D4 ROM and I want the Release number to
#									reflect this. 10D3 -> 10D4
#	   <SM8>	 1/10/93	RC		Added Emulator Acceleration Resource
#	   <SM7>	12/29/92	HY		Removed hasNewSoundMgr feature flag. Reverting back to 7.1 snd mgr.
#	   <SM6>	12/23/92	RC		GoNativeResource added back in
#	   <SM5>	12/17/92	RC		Made sure that the New ROM has the correct - ROMRelease=$10D3
#	   <SM4>	12/17/92	RB		Added the variable subRelease and the features hasCPUIDRegister,
#									hasHMC.
#	   <SM3>	12/12/92	RC		Copied Craig's changes to the SuperMario make file to the RISC
#									file so we will not need Runtime.o also
#	   <SM2>	12/11/92	kc		Remove the post build beeps.
#

BuildDir		=	{Sources}BuildResults:RISC:
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


MAOpts			=	-d TRUE=1 -d FALSE=0 -d Alignment=8 -d CPU=20 -d ROMRelease=$D4C1 -wb -d SubRelease=3 -blksize 62
MCOpts			=	-d TRUE=1 -d FALSE=0 -d Alignment=8 -d CPU=20 -d ROMRelease=$D4C1 -b3 -mbg full -mc68020 -blksize 62 -opt full
MPOpts			=	-mbg full -mc68020

RomBase			=	$40800000

Features		=	hasRISCV0ResMgrPatches					¶
					hasDoubleByte							¶
					hasAMIC									¶
					SupportNativeComponents					¶
					Script_Char_Extra						¶
					hasPenFraction							¶
					hasFullKerning							¶
					hasGlyphState							¶
					hasNewHeapMgr							¶
					hasPDMMaceEnet							¶
					hasAppleTalkInROM						¶
					hasMixedMode							¶
					nonSerializedIO							¶
					hasSCSIDiskModeFeature					¶
					hasSysSevenResources					¶
					hasDataAccessPACK						¶
					hasYMCA									¶
					hasCPUIDRegister						¶
					hasHMC									¶
					has2MegROMOrMore						¶
					hasVideoIn								¶
					hasAsyncSCSI							¶
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
					hasDisplayMgr 							¶
					hasDisplayMgrWindows 					¶
					hasEDisk								¶
					hasEclipseVIA2							¶
					hasEditionMgr							¶
					hasEgret								¶
					hasExtendedCharacterSet					¶
					hasFMC									¶
					hasGDU									¶
					hasGlue									¶
					hasGrandCentral							¶
					hasIdle 								¶
					hasIopScc								¶
					hasIopSwim								¶
					hasJaws 								¶
					hasMDU									¶
					hasMMU									¶
					hasMSC									¶
					hasMac2VIA2 							¶
					hasNetBoot								¶
					hasNiagra								¶
					hasOrwell								¶
					hasOss									¶
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
					hasPwrControls							¶
					hasPwrMgrClock							¶
					hasRBV									¶
					hasSplineFonts							¶
					hasVIAClock 							¶
					hasWaimeaVIA2							¶
					NewBuildSystem							¶
					isUniversal								¶
					onHafMac								¶
					onMac32 								¶
					onNuMac 								¶
					ForROM


ResourceFiles	=	"{RsrcDir}ATBoot.RSRC"					¶
					"{MiscDir}AppleTalk.ROM.rsrc"			¶
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
					"{RsrcDir}Gibbly.rsrc"					¶
					"{MiscDir}GoNativeResources"			¶
					"{MiscDir}EmulatorAccelerations.rsrc"	¶
					"{RsrcDir}HelpMgr.rsrc"					¶
					"{RsrcDir}InSane.rsrc"					¶
					"{RsrcDir}I2CC.rsrc"					¶
					"{RsrcDir}I2CT.rsrc"					¶
					"{RsrcDir}ListMgr.rsrc"					¶
					"{RsrcDir}MainCode.Rsrc"				¶
					"{RsrcDir}MenuMgr.rsrc"					¶
					"{RsrcDir}MiscROMRsrcs.rsrc" 			¶
					"{RsrcDir}NetBoot.rsrc"					¶
					"{RsrcDir}PDMENET.rsrc"					¶
					"{RsrcDir}PPC.rsrc"						¶
					"{RsrcDir}PictUtilities.rsrc"			¶
					"{RsrcDir}ROMApple2Fonts.rsrc"			¶
					"{RsrcDir}ROMFonts.rsrc" 				¶
					"{RsrcDir}RomLayout.Rsrc"				¶
					"{RsrcDir}SCCIOP.rsrc"					¶
					"{RsrcDir}SWIMIOP.rsrc"					¶
					"{RsrcDir}InSaneNFPU.rsrc" 				¶
					"{RsrcDir}Sane.rsrc" 					¶
					"{RsrcDir}Serial.rsrc"					¶
					"{RsrcDir}SerialDMA.rsrc"				¶
					"{RsrcDir}Sony.rsrc" 					¶
					"{RsrcDir}SoundMgr.rsrc" 				¶
					"{RsrcDir}StandardFile.rsrc" 			¶
					"{RsrcDir}VDigC.rsrc"					¶
					"{RsrcDir}VDigT.rsrc"					¶
					"{MiscDir}VM.RSRC"						¶
					"{RsrcDir}WindowMgr.rsrc"				¶
					"{RsrcDir}kbd.rsrc"


RomMondo						Ä	FeatureSet "{ImageDir}RomMondo"


"{ImageDir}RomMondo"			Ä	{ResourceFiles}
	RomLayout	-mf "{RsrcDir}RomLayout.Rsrc" -o "{Targ}" -log "{ImageDir}RomInfo"


LinkRomImage					Ä	# target for partial builds
	RomLayout	-mf "{RsrcDir}RomLayout.Rsrc" -o "{ImageDir}RomMondo" -log "{ImageDir}RomInfo"


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
	Set StdAOpts			"{MAOpts} {FeatureSet} -i {IntAIncludes} {AOpts} -i {ObjDir}"
	Set StdCOpts			"{MCOpts} {FeatureSet} -i {IntCIncludes} {COpts}"
	Set StdCPOpts			"{MCPOpts} {FeatureSet} -i {IntCIncludes} {COpts}"
	Set StdPOpts			"{MPOpts} {FeatureSet} {POpts} -i {IntPInterfaces} -r"
	Set StdROpts			"{FeatureSet} {ROpts} -i {IntRIncludes} -i {RIncludes}"
	Set StdLOpts			"{LOpts} -mf -t rsrc -c RSED -sg Main"
	Set StdLibOpts			"{LibOpts} -mf"
	Set StdAlign			"{Align} -ac 16 -ad 16"
	Set StdVOpts			"{VOpts}"
	Set StdEquAOpts			"`{MakeDir}CreateStdEquAOptions "{FeatureSet}"`"	; Export StdEquAOpts


"{RsrcDir}RomLayout.Rsrc"		Ä	"{MakeDir}RiscLayout.r" "{ResourceDir}RomResources.r" "{IntRIncludes}RomTypes.r"
	Rez	{StdROpts} "{MakeDir}RiscLayout.r" -i "{ResourceDir}" -o "{targ}" -d RomBase={RomBase} -c RSED -t rsrc


Clean							Ä
	Delete -i `Files -f -r -o -s "{BuildDir}"` ³ Dev:Null


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
