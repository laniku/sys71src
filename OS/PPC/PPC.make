#
#	File:		PPC.make
#
#	Contains:	Makefile to build the PPC manager.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992 by Apple Computer, Inc.  All rights reserved.
#
#	Change History (most recent first):
#
#	   <SM3>	 12/2/92	kc		Added " || Exit 1" to commands with a double dependency.
#	   <SM2>	11/30/92	SWC		Changed ATalkEqu.a->AppleTalk.a.


PPCObjects		=	"{ObjDir}PPCInstall.a.o"										¶
					"{ObjDir}PPCUtilities.c.o"										¶
					"{ObjDir}PPCDispatcher.a.o"										¶
					"{ObjDir}PPCLoader.c.o"											¶
					"{ObjDir}PPCInit.c.o"											¶
					"{ObjDir}PPCUtil.a.o"											¶
					"{ObjDir}PPCEntry.c.o"											¶
					"{ObjDir}PPCPort.c.o"											¶
					"{ObjDir}PPCSession.c.o"										¶
					"{ObjDir}PPCLocal.c.o"											¶
					"{ObjDir}PPCNetwork.c.o"										¶
					"{ObjDir}PPCAuth.c.o"											¶
					"{ObjDir}PPCDsp.c.o"											¶
					"{ObjDir}PPCNBP.c.o"											¶
					"{ObjDir}BTreeCGlue.a.o"										¶
					"{ObjDir}BTIntf.a.o"											¶
					"{ObjDir}PPCBrowserPackEntry.a.o"								¶
					"{ObjDir}PromptForUser.a.o"										¶
					"{ObjDir}PromptForUser.c.o"										¶
					"{PPCDir}maindes.o"

PPCBrowserObjs =	"{ObjDir}PPCBrowser.a.o"										¶
					"{ObjDir}PPCBrowser.c.o"										¶
					"{CLibraries}StdCLib.o"											¶
					"{IfObjDir}interface.o"											


"{LibDir}PPC.lib"	Ä	{PPCObjects}
	Lib {StdLibOpts} -o "{Targ}" {PPCObjects}


"{RsrcDir}PPC.rsrc"	ÄÄ	{PPCBrowserObjs}
	Link {StdLOpts} {StdAlign} -o "{Targ}" {PPCBrowserObjs} -m BrowsePackEntry -rt PACK=9 || Exit 1


"{RsrcDir}PPC.rsrc"	ÄÄ	"{RIncludes}Types.r"										¶
						"{RIncludes}SysTypes.r"										¶
						"{RIncludes}BalloonTypes.r"									¶
						"{PPCDir}PPCBrowser.r"
	Rez  {StdROpts} -o "{Targ}" "{PPCDir}PPCBrowser.r" -a || Exit 1


"{ObjDir}BTIntf.a.o"			Ä 	"{AIncludes}Traps.a"							¶
									"{AIncludes}ToolUtils.a"						¶
									"{IntAIncludes}BTreeEqu.a"						¶
									"{PPCDir}BTIntf.a"
	Asm {StdAOpts} -o "{Targ}" "{PPCDir}BTIntf.a"


"{ObjDir}BTreeCGlue.a.o"		Ä "{PPCDir}BTreeCGlue.a"
	Asm {StdAOpts} -o "{Targ}" "{PPCDir}BTreeCGlue.a"


"{ObjDir}PPCAuth.c.o"			Ä 	"{PPCDir}PPCCommon.h"							¶
									"{PPCDir}UserGroup.h"							¶
									"{CIncludes}Types.h"							¶
 									"{CIncludes}Files.h"							¶
 									"{CIncludes}Memory.h"							¶
 									"{CIncludes}Errors.h"							¶
									"{CIncludes}Resources.h"						¶
 									"{CIncludes}ToolUtils.h"						¶
 									"{IntCIncludes}BTEqu.h"							¶
 									"{CIncludes}OSUtils.h"							¶
 									"{CIncludes}Devices.h"							¶
									"{CIncludes}AppleTalk.h"						¶
									"{CIncludes}ADSP.h"								¶
									"{CIncludes}PPCToolbox.h"						¶
									"{PPCDir}PPCAuth.c"
	C {StdCOpts} -o "{Targ}" "{PPCDir}PPCAuth.c"


"{ObjDir}PPCDispatcher.a.o"		Ä 	"{AIncludes}Traps.a"							¶
									"{AIncludes}ToolUtils.a"						¶
									"{AIncludes}PPCToolbox.a"						¶
									"{PPCDir}PPCDispatcher.a"
	Asm {StdAOpts} -o "{Targ}" "{PPCDir}PPCDispatcher.a"


"{ObjDir}PPCDsp.c.o"			Ä 	"{PPCDir}PPCCommon.h"							¶
									"{PPCDir}UserGroup.h"							¶
									"{CIncludes}Types.h"							¶
 									"{CIncludes}Files.h"							¶
 									"{CIncludes}Memory.h"							¶
 									"{CIncludes}Errors.h"							¶
									"{CIncludes}Resources.h"						¶
 									"{CIncludes}ToolUtils.h"						¶
 									"{IntCIncludes}BTEqu.h"							¶
 									"{CIncludes}OSUtils.h"							¶
 									"{CIncludes}Devices.h"							¶
									"{CIncludes}AppleTalk.h"						¶
									"{CIncludes}ADSP.h"								¶
									"{CIncludes}PPCToolbox.h"						¶
									"{PPCDir}PPCDsp.c"
	C {StdCOpts} -o "{Targ}" "{PPCDir}PPCDsp.c"


"{ObjDir}PPCEntry.c.o"			Ä 	"{PPCDir}PPCCommon.h"							¶
									"{PPCDir}UserGroup.h"							¶
									"{CIncludes}Types.h"							¶
 									"{CIncludes}Files.h"							¶
 									"{CIncludes}Memory.h"							¶
 									"{CIncludes}Errors.h"							¶
									"{CIncludes}Resources.h"						¶
 									"{CIncludes}ToolUtils.h"						¶
 									"{IntCIncludes}BTEqu.h"							¶
 									"{CIncludes}OSUtils.h"							¶
 									"{CIncludes}Devices.h"							¶
									"{CIncludes}AppleTalk.h"						¶
									"{CIncludes}ADSP.h"								¶
									"{CIncludes}PPCToolbox.h"						¶
									"{PPCDir}PPCEntry.c"
	C {StdCOpts} -o "{Targ}" "{PPCDir}PPCEntry.c"


"{ObjDir}PPCInit.c.o"			Ä 	"{PPCDir}PPCCommon.h"							¶
									"{PPCDir}UserGroup.h"							¶
									"{CIncludes}Types.h"							¶
 									"{CIncludes}Files.h"							¶
 									"{CIncludes}Memory.h"							¶
 									"{CIncludes}Errors.h"							¶
									"{CIncludes}Resources.h"						¶
 									"{CIncludes}ToolUtils.h"						¶
 									"{IntCIncludes}BTEqu.h"							¶
 									"{CIncludes}OSUtils.h"							¶
 									"{CIncludes}Devices.h"							¶
									"{CIncludes}AppleTalk.h"						¶
									"{CIncludes}ADSP.h"								¶
									"{CIncludes}PPCToolbox.h"						¶
									"{PPCDir}PPCInit.c"
	C {StdCOpts} -o "{Targ}" "{PPCDir}PPCInit.c"


"{ObjDir}PPCLoader.c.o"			Ä 	"{PPCDir}PPCCommon.h"							¶
									"{PPCDir}UserGroup.h"							¶
									"{CIncludes}Types.h"							¶
 									"{CIncludes}Files.h"							¶
 									"{CIncludes}Memory.h"							¶
 									"{CIncludes}Errors.h"							¶
									"{CIncludes}Resources.h"						¶
 									"{CIncludes}ToolUtils.h"						¶
 									"{IntCIncludes}BTEqu.h"							¶
 									"{CIncludes}OSUtils.h"							¶
 									"{CIncludes}Devices.h"							¶
									"{CIncludes}AppleTalk.h"						¶
									"{CIncludes}ADSP.h"								¶
									"{CIncludes}PPCToolbox.h"						¶
									"{PPCDir}PPCLoader.c"
	C {StdCOpts} -o "{Targ}" "{PPCDir}PPCLoader.c"


"{ObjDir}PPCLocal.c.o"			Ä 	"{PPCDir}PPCCommon.h"							¶
									"{PPCDir}UserGroup.h"							¶
									"{CIncludes}Types.h"							¶
 									"{CIncludes}Files.h"							¶
 									"{CIncludes}Memory.h"							¶
 									"{CIncludes}Errors.h"							¶
									"{CIncludes}Resources.h"						¶
 									"{CIncludes}ToolUtils.h"						¶
 									"{IntCIncludes}BTEqu.h"							¶
 									"{CIncludes}OSUtils.h"							¶
 									"{CIncludes}Devices.h"							¶
									"{CIncludes}AppleTalk.h"						¶
									"{CIncludes}ADSP.h"								¶
									"{CIncludes}PPCToolbox.h"						¶
									"{PPCDir}PPCLocal.c"
	C {StdCOpts} -o "{Targ}" "{PPCDir}PPCLocal.c"


"{ObjDir}PPCNbp.c.o"			Ä 	"{PPCDir}PPCCommon.h"							¶
									"{PPCDir}UserGroup.h"							¶
									"{CIncludes}Types.h"							¶
 									"{CIncludes}Files.h"							¶
 									"{CIncludes}Memory.h"							¶
 									"{CIncludes}Errors.h"							¶
									"{CIncludes}Resources.h"						¶
 									"{CIncludes}ToolUtils.h"						¶
 									"{IntCIncludes}BTEqu.h"							¶
 									"{CIncludes}OSUtils.h"							¶
 									"{CIncludes}Devices.h"							¶
									"{CIncludes}AppleTalk.h"						¶
									"{CIncludes}ADSP.h"								¶
									"{CIncludes}PPCToolbox.h"						¶
									"{PPCDir}PPCNbp.c"
	C {StdCOpts} -o "{Targ}" "{PPCDir}PPCNbp.c"


"{ObjDir}PPCNetwork.c.o"		Ä 	"{PPCDir}PPCCommon.h"							¶
									"{PPCDir}UserGroup.h"							¶
									"{CIncludes}Types.h"							¶
 									"{CIncludes}Files.h"							¶
 									"{CIncludes}Memory.h"							¶
 									"{CIncludes}Errors.h"							¶
									"{CIncludes}Resources.h"						¶
 									"{CIncludes}ToolUtils.h"						¶
 									"{IntCIncludes}BTEqu.h"							¶
 									"{CIncludes}OSUtils.h"							¶
 									"{CIncludes}Devices.h"							¶
									"{CIncludes}AppleTalk.h"						¶
									"{CIncludes}ADSP.h"								¶
									"{CIncludes}PPCToolbox.h"						¶
									"{PPCDir}PPCNetwork.c"
	C {StdCOpts} -o "{Targ}" "{PPCDir}PPCNetwork.c"


"{ObjDir}PPCInstall.a.o"		Ä	"{PPCDir}PPCInstall.a"							¶
									"{ObjDir}StandardEqu.d"		 					¶
									"{AIncludes}GestaltEqu.a"						¶
									"{AIncludes}ShutDown.a"							
	Asm {StdAOpts} -o "{Targ}" "{PPCDir}PPCInstall.a"


"{ObjDir}PPCPort.c.o"			Ä	"{PPCDir}PPCCommon.h"							¶
									"{PPCDir}UserGroup.h"							¶
									"{CIncludes}Types.h"							¶
 									"{CIncludes}Files.h"							¶
 									"{CIncludes}Memory.h"							¶
 									"{CIncludes}Errors.h"							¶
									"{CIncludes}Resources.h"						¶
 									"{CIncludes}ToolUtils.h"						¶
 									"{IntCIncludes}BTEqu.h"							¶
 									"{CIncludes}OSUtils.h"							¶
 									"{CIncludes}Devices.h"							¶
									"{CIncludes}AppleTalk.h"						¶
									"{CIncludes}ADSP.h"								¶
									"{CIncludes}PPCToolbox.h"						¶
									"{PPCDir}PPCPort.c"
	C {StdCOpts} -o "{Targ}" "{PPCDir}PPCPort.c"


"{ObjDir}PPCSession.c.o"		Ä 	"{PPCDir}PPCCommon.h"							¶
									"{PPCDir}UserGroup.h"							¶
									"{CIncludes}Types.h"							¶
 									"{CIncludes}Files.h"							¶
 									"{CIncludes}Memory.h"							¶
 									"{CIncludes}Errors.h"							¶
									"{CIncludes}Resources.h"						¶
 									"{CIncludes}ToolUtils.h"						¶
 									"{IntCIncludes}BTEqu.h"							¶
 									"{CIncludes}OSUtils.h"							¶
 									"{CIncludes}Devices.h"							¶
									"{CIncludes}AppleTalk.h"						¶
									"{CIncludes}ADSP.h"								¶
									"{CIncludes}PPCToolbox.h"						¶
									"{PPCDir}PPCSession.c"
	C {StdCOpts} -o "{Targ}" "{PPCDir}PPCSession.c"


"{ObjDir}StoreAndForward.c.o"	Ä 	"{PPCDir}PPCCommon.h"							¶
									"{CIncludes}Types.h"							¶
 									"{CIncludes}Files.h"							¶
 									"{CIncludes}Memory.h"							¶
 									"{CIncludes}Errors.h"							¶
									"{CIncludes}Resources.h"						¶
 									"{CIncludes}ToolUtils.h"						¶
 									"{IntCIncludes}BTEqu.h"							¶
 									"{CIncludes}OSUtils.h"							¶
 									"{CIncludes}Devices.h"							¶
									"{CIncludes}AppleTalk.h"						¶
									"{CIncludes}ADSP.h"								¶
									"{CIncludes}PPCToolbox.h"						¶
									"{PPCDir}StoreAndForward.c"
	C {StdCOpts} -o "{Targ}" "{PPCDir}StoreAndForward.c"


"{ObjDir}PPCUtilities.c.o"		Ä 	"{PPCDir}PPCCommon.h"							¶
									"{PPCDir}PPCUtilities.c"
	C {StdCOpts} -o "{Targ}" "{PPCDir}PPCUtilities.c"


"{ObjDir}PPCUtil.a.o"			Ä 	"{AIncludes}Traps.a"							¶
									"{AIncludes}ToolUtils.a"						¶
									"{AIncludes}PPCToolbox.a"						¶
									"{AIncludes}QuickDraw.a"						¶
									"{PPCDir}PPCUtil.a"
	Asm {StdAOpts} -o "{Targ}" "{PPCDir}PPCUtil.a"


"{ObjDir}PromptForUser.a.o"		Ä 	"{AIncludes}Traps.a"							¶
									"{AIncludes}QuickDraw.a"						¶
									"{AIncludes}SysErr.a"							¶
									"{AIncludes}ToolUtils.a"						¶
									"{AIncludes}FSEqu.a"							¶
									"{AIncludes}AppleTalk.a"						¶
									"{PPCDir}PromptForUserEqu.a"					¶
									"{PPCDir}PromptForUser.a"
	Asm {StdAOpts} -o "{Targ}" "{PPCDir}PromptForUser.a"


"{ObjDir}PPCBrowserPackEntry.a.o" Ä "{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}DispatchHelperPriv.a"			¶
									"{PPCDir}PPCBrowserPackEntry.a"
	Asm {StdAOpts} -o "{Targ}" "{PPCDir}PPCBrowserPackEntry.a"


"{ObjDir}PPCBrowser.a.o"		Ä 	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}Packages.a"							¶
									"{PPCDir}PPCBrowser.a"
	Asm {StdAOpts} -o "{Targ}" "{PPCDir}PPCBrowser.a"


"{ObjDir}PPCBrowser.c.o"		Ä 	"{PPCDir}PPCBrowserPriv.h"						¶
									"{CIncludes}Types.h"							¶
 									"{CIncludes}stdio.h"							¶
									"{CIncludes}Resources.h"						¶
									"{CIncludes}Files.h"							¶
 									"{CIncludes}ToolUtils.h"						¶
 									"{CIncludes}Memory.h"							¶
 									"{CIncludes}Errors.h"							¶
 									"{CIncludes}Packages.h"							¶
 									"{CIncludes}Lists.h"							¶
									"{IntCIncludes}IntlUtilsPriv.h"					¶
									"{CIncludes}PPCToolbox.h"						¶
									"{PPCDir}PPCBrowser.c"
	C {StdCOpts} -o "{Targ}" "{PPCDir}PPCBrowser.c"


"{ObjDir}PromptForUser.c.o"		Ä 	"{PPCDir}PromptForUser.c"
	C {StdCOpts} -o "{Targ}" "{PPCDir}PromptForUser.c"
