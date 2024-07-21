#
#	File		MainCode.Make
#
#	Contains:	Makefile for main code image.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	  <SM12>	11/11/93	fau		<aek>  Added the Expansion Bus Manager to the libraries.
#	  <SM11>	 7/20/93	SAM		Removed ProcessMgrSegmentTweaks.a.  It was redundant.
#		<10>	  4/8/93	IH		Re-introduce Display Manager.
#	   <SM9>	  4/7/93	CSS		Don't echo {StdEquAOpts} in lines to build standardequ.d.
#	   <SM8>	  4/4/93	RC		Comment out DisplayMgr (I believe that it is inclued twice (once
#									in ToolBox.lib and once directly into MainCode)
#	   <SM7>	  4/1/93	kc		Re-enable the Display Manager.
#	   <SM6>	  4/1/93	kc		Back out Ian's change.
#	   <SM5>	 3/31/93	kc		Change the path of the VectorLog file to use TextDir and change
#									the -map parameter for the Linker to -l.
#	   <SM4>	 3/31/93	IH		Add Display Manager objects.
#	   <SM3>	 3/16/93	SAM		Added TrapsPrivate.a to the list of dependencies for
#									StandardEqu.a.  Sorry about that full build (hee hee).
#	   <SM2>	 2/22/93	RC		Turned off Warnings
#	   <SM8>	 12/8/92	RC		Included GoNativeROMLib.o to the MainCodeLibs
#	   <SM7>	 12/2/92	kc		Change Vectorization stuff to use new Macros.
#	   <SM6>	11/23/92	kc		Change VOpts to StdVOpts.
#	   <SM5>	11/14/92	kc		Change link option used to name segment from -sg to -sn.
#	   <SM4>	11/12/92	kc		Remove Sadism.lib. Change Link command to write the link map to
#									the data fork of the resoruce file.
#	   <SM3>	11/11/92	RB		Added rules for ROM_EM. Changed the output of the linking of
#									ROM, it was erasing Maincode.rsrc

OSDir		=	{Sources}OS:
ToolBoxDir	=	{Sources}ToolBox:
PatchDir	=	{Sources}Patches:
ColorQDDir	=	{Sources}QuickDraw:
IfSrcDir	=	{Sources}Libs:InterfaceSrcs:
LibraryDir	=	{Sources}Libs:Libraries:

#include {OSDir}OS.make
#include {ToolBoxDir}Toolbox.make
#include {ColorQDDir}ColorQD.make
#include {IfSrcDir}Interface.make


MainCodeLibs = 												¶
				"{LibDir}StartMgr.lib"						¶
				"{ObjDir}VectorTableInit.a.o"				¶
				"{LibDir}IOPrimitives.lib"					¶
				"{LibDir}MMU.lib"							¶
				"{LibDir}OS.lib"							¶
				"{MiscDir}GoNativeROMLib.o"					¶
				"{LibDir}SlotMgr.lib"						¶
				"{LibDir}SCSI.lib"							¶
				"{LibDir}SCSI4pt3.lib"						¶
				"{LibDir}HFS.lib"							¶
				"{LibDir}PPC.lib"							¶
				"{LibDir}ADBMgr.lib"						¶
				"{LibDir}TimeMgr.lib"						¶
				"{LibDir}Toolbox.lib"						¶
				"{LibDir}CommToolboxPatch.Lib"				¶
				"{LibDir}MemoryMgr.lib"						¶
				"{LibDir}AliasMgr.lib"						¶
				"{LibDir}ComponentMgr.lib"					¶
				"{LibDir}DataAccessMgr.lib"					¶
				"{LibDir}EditionMgr.lib"					¶
				"{LibDir}ExpansionBusMgr.lib"				¶
				"{LibDir}HelpMgr.lib"						¶
				"{LibDir}SoundMgr.lib"						¶
				"{LibDir}Gestalt.lib"						¶
				"{LibDir}IconUtils.lib"						¶
				"{LibDir}NotificationMgr.lib"				¶
				"{LibDir}PictUtilities.lib"					¶
				"{LibDir}ToolboxEventMgr.lib"				¶
				"{LibDir}ControlMgr.lib"					¶
				"{LibDir}DisplayMgr.lib"					¶
				"{LibDir}WindowMgr.lib"						¶
				"{LibDir}MenuMgr.lib"						¶
#															¶
#	DispatchHelper and DialogMgr.lib need to be colocated	¶
#															¶
				"{ObjDir}DispatchHelper.a.o"				¶
				"{LibDir}DialogMgr.lib"						¶
#															¶
#	ResourceMgr.lib and ScriptMgr.lib need to be colocated	¶
#															¶
				"{LibDir}ResourceMgr.lib"					¶
				"{LibDir}ScriptMgr.lib"						¶
				"{LibDir}CQD.lib"							¶
				"{LibDir}TextServicesMgr.lib"				¶
				"{LibDir}FontMgr.lib"						¶
				"{LibDir}RomInterface.Lib"					¶
				"{LibDir}RomStandardLib.lib"				¶
				"{LibDir}StartTest.lib"						¶
				"{LibDir}VideoDriver.lib"					¶
				"{ObjDir}WallyWorld.a.o"					¶
				"{ObjDir}FPEmulation.a.o"					¶
				"{LibDir}Beep.lib"							¶
#															¶
#	Keep DispTable at end									¶
#															¶
				"{ObjDir}DispTable.a.o"												
#
# end of ROM
#


#
#	Main Code Image Resource
#
"{RsrcDir}MainCode.Rsrc"		Ä	"{LibDir}MainCode.Lib"
	Delete "{Targ}" · Dev:Null || Set Status 0
	Link {StdLOpts} {StdAlign} -rt ZROM=128 -br 020 -sg zrom -l -m MYROM ¶
		"{LibDir}MainCode.Lib" -o "{Targ}" > "{TextDir}MainCode.map"

#
#	Vectorization
#
"{LibDir}MainCode.Lib"			Ä	{MainCodeLibs} "{ObjDir}VectorTablePatch.a.o"
	"{ToolDir}Vectorize" -w -v "{ObjDir}VectorTablePatch.a.o" -log "{TextDir}MainCode.Sym" {StdVOpts} -o "{Targ}" {MainCodeLibs}

"{ObjDir}VectorTablePatch.a.o"	Ä	"{Sources}Make:VectorTable.a" "{IntAIncludes}VectorTablePatch.a"
	Asm -case on {StdAOpts} -o "{Targ}" "{IntAIncludes}VectorTablePatch.a" -d &VectorTable="¶'{Sources}Make:VectorTable.a¶'" -d ROMBASE={RomBase}

"{ObjDir}VectorTableInit.a.o"	Ä	"{Sources}Make:VectorTable.a" "{IntAIncludes}VectorTableInit.a"
	Asm -case on {StdAOpts} -o "{Targ}" "{IntAIncludes}VectorTableInit.a" -d &VectorTable="¶'{Sources}Make:VectorTable.a¶'" -d ROMBASE={RomBase}

#
#	Patches
#

"{ObjDir}MiscPatches.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}ResourceMgrPriv.a"				¶
									"{IntAIncludes}BTreeEqu.a"						¶
									"{IntAIncludes}MMUEqu.a"						¶
									"{IntAIncludes}BootEqu.a"						¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{IntAIncludes}FileMgrPrivate.a"				¶
									"{IntAIncludes}ScriptPriv.a"					¶
									"{AIncludes}GestaltEqu.a"						¶
									"{IntAIncludes}GestaltPrivateEqu.a" 			¶
									"{IntAIncludes}EditionsPrivate.a"				¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{AIncludes}DatabaseAccess.a"					¶
									"{PatchDir}MiscPatches.a"
	Asm {StdAOpts} -o "{Targ}" "{PatchDir}MiscPatches.a"


"{LibDir}RomStandardLib.lib"	Ä	"{LibraryDir}StandardLib.o"						¶
									"{IfSrcDir}DuplicateModules.rom"
	Lib {StdLibOpts} -o "{Targ}" "{LibraryDir}StandardLib.o" -df "{IfSrcDir}DuplicateModules.rom"


"{LibDir}RomInterface.Lib"		Ä	"{IfObjDir}Interface.o"							¶
									"{IfSrcDir}DuplicateModules.rom"
	Lib {StdLibOpts} -o "{Targ}" "{IfObjDir}Interface.o" -df "{IfSrcDir}DuplicateModules.rom"

#	Precompiled headers are not free.
#
#	There is a double define problem in StandardEqu.d such that
#	if we define ROMFastTraps when we build StandardEqu.d, we cannot
#	build with any different settings.  If ROMFastTraps is set to a
#	different value in a later build we puke (ie we have to do a full build).
#
#	It would be nice to be able to avoid full builds although the
#	Traps.a files will use the stale setting of ROMFastTraps
#
"{ObjDir}StandardEqu.d"			Ä	"{AIncludes}FSEqu.a"							¶
									"{AIncludes}FSPrivate.a"						¶
									"{AIncludes}Private.a"							¶
									"{AIncludes}QuickDraw.a"						¶
									"{AIncludes}SANEMacs.a"							¶
									"{AIncludes}Script.a"							¶
									"{AIncludes}SysEqu.a"							¶
									"{IntAIncludes}SysPrivateEqu.a"					¶
									"{AIncludes}SysErr.a"							¶
									"{AIncludes}ToolUtils.a"						¶
									"{AIncludes}Traps.a"							¶
									"{AIncludes}Timer.a"							¶
									"{IntAIncludes}InternalOnlyEqu.a"				¶
									"{IntAIncludes}TrapsPrivate.a"					¶
									"{IntAIncludes}StandardEqu.a"					¶
									"{AIncludes}Power.a"
	Asm {StdEquAOpts} -o Dev:Null "{IntAIncludes}StandardEqu.a" -i "{IntAIncludes}"
	Move -y StandardEqu.d "{Targ}"

