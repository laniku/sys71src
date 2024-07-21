#
#	File:		Interface.Make
#
#	Contains:	Makefile that builds Interface.o.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc.  All rights reserved.
#
#	Change History (most recent first):
#
#	   <SM3>	11/10/93	chp		OSTraps.a.o needed a dependency on StandardEqu.d to make the
#									build work for certain targets.
#	   <SM2>	 8/13/93	kc		Delete obsolete entry points in the ConnectionMgrExtensions.o.
#	   <SM3>	11/30/92	SWC		Changed PackMacs.a->Packages.a, QuickEqu.a->QuickDraw.a.
#	   <SM2>	11/11/92	RB		Changed packages.a to PackagesGlue.a

IfAOpts			= {StdAOpts}
IfCOpts			= {StdCOpts}


CTDir			=	{ToolBoxDir}CommToolbox:
CTGlueDir		= 	{Sources}Libs:CommToolboxSrcs:
CTRsrcDir		=	{CTDir}CommResourceMgr:
CTCnctDir		=	{CTDir}ConnectionMgr:
CTFileTransDir	=	{CTDir}FileTransferMgr:
CTTermDir		=	{CTDir}TerminalMgr:

InterfaceObjs							=	"{IfObjDir}"Copyright.a.o					¶
											"{IfObjDir}"OSTraps.a.o						¶
											"{IfObjDir}"BitMapToRegion.a.o 				¶
											"{IfObjDir}"HFSGlue.c.o						¶
											"{IfObjDir}"FoldersGlue.c.o					¶
											"{IfObjDir}"ToolTraps.a.o					¶
											"{IfObjDir}"EnvironsGlue.a.o				¶
											"{IfObjDir}"GestaltGlue.a.o					¶
											"{IfObjDir}"PackTraps.a.o					¶
											"{IfObjDir}"ListTraps.a.o					¶
											"{IfObjDir}"PrintCalls.a.o					¶
											"{IfObjDir}"Graf3DAsm.a.o					¶
											"{IfObjDir}"SlotTraps.a.o					¶
											"{IfObjDir}"Strings.a.o						¶
											"{IfObjDir}"nAppleTalk.a.o					¶
											"{IfObjDir}"ENet.a.o						¶
											"{IfObjDir}"piMAIN.a.o						¶
											"{IfObjDir}"controls.a.o					¶
											"{IfObjDir}"desk.a.o						¶
											"{IfObjDir}"devices.a.o						¶
											"{IfObjDir}"dialogs.a.o						¶
											"{IfObjDir}"files.a.o						¶
											"{IfObjDir}"fonts.a.o						¶
											"{IfObjDir}"GetPhysical.a.o					¶
											"{IfObjDir}"lists.c.o						¶
											"{IfObjDir}"menus.a.o						¶
											"{IfObjDir}"osutils.a.o						¶
											"{IfObjDir}"PackagesGlue.a.o				¶
											"{IfObjDir}"quickdraw.a.o					¶
											"{IfObjDir}"resources.a.o					¶
											"{IfObjDir}"segload.a.o						¶
											"{IfObjDir}"textedit.a.o					¶
											"{IfObjDir}"toolutils.a.o					¶
											"{IfObjDir}"ppcGlue.a.o						¶
											"{IfObjDir}"windows.a.o						¶
											"{IfObjDir}CommResourceMgrGlue.a.o"			¶
											"{IfObjDir}CommToolboxCoreGlue.a.o"			¶
											"{IfObjDir}CommToolboxUtilitiesGlue.a.o"	¶
											"{IfObjDir}ConnectionMgrGlue.a.o"			¶
											"{IfObjDir}FileTransferMgrGlue.a.o"			¶
											"{IfObjDir}TerminalMgrGlue.a.o"				¶
											"{IfObjDir}ConnectionMgrExtensions.o" 		¶
											"{IfObjDir}FileTransferMgrExtensions.o"		¶
											"{IfObjDir}TerminalMgrExtensions.o"			¶
											"{IfObjDir}CommResourceMgrExtensions.o"		¶
											"{IfObjDir}Power.a.o"


ConnectionMgrExtensionsObjs				=	"{IfObjDir}ConnectionMgrExtensionsGlue.a.o"	¶
											"{IfObjDir}ConnectionMgrExtensions.c.o"


FileTransferMgrExtensionsObjs			=	"{IfObjDir}FileXferMgrExtensionsGlue.a.o"	¶
											"{IfObjDir}FileTransferMgrExtensions.c.o"


TerminalMgrExtensionsObjs				=	"{IfObjDir}TerminalMgrExtensionsGlue.a.o"	¶
											"{IfObjDir}TerminalMgrExtensions.c.o"


CommResourceMgrExtensionsObjs			=	"{IfObjDir}CommRsrcMgrExtensionsGlue.a.o"	¶
											"{IfObjDir}CommResourceMgrExtensions.c.o"



"{IfObjDir}Interface.o"		 			Ä	{InterfaceObjs}
	Lib {StdLibOpts} -o "{IfObjDir}Interface.o" -rn HOPENRESFILEGLUE=HOPENRESFILE -rn HCREATERESFILEGLUE=HCREATERESFILE {InterfaceObjs}


"{IfObjDir}ConnectionMgrExtensions.o"	Ä	{ConnectionMgrExtensionsObjs}
	Lib {StdLibOpts} -o "{Targ}"	{ConnectionMgrExtensionsObjs}							¶
								-dn CDEFEXECUTEDEF										¶
								-dn __CMGETERRORSTRING									¶
								-dn __CMNEWIOPB											¶
								-dn __CMDISPOSEIOPB										¶
								-dn __CMPBREAD											¶
								-dn __CMPBWRITE											¶
								-dn __CMPBIOKILL										


"{IfObjDir}FileTransferMgrExtensions.o"	Ä	{FileTransferMgrExtensionsObjs}
	Lib {StdLibOpts} -o "{Targ}"	{FileTransferMgrExtensionsObjs}							¶
								-dn FDEFEXECUTEFDEF										¶
								-dn __FTGETERRORSTRING									¶
								-dn __FTSEND											¶
								-dn __FTRECEIVE								


"{IfObjDir}TerminalMgrExtensions.o"			Ä	{TerminalMgrExtensionsObjs}
	Lib {StdLibOpts} -o "{Targ}"	{TerminalMgrExtensionsObjs}								¶
								-dn TDEFEXECUTEDEF										¶
								-dn __TMGETERRORSTRING						


"{IfObjDir}CommResourceMgrExtensions.o"		Ä	{CommResourceMgrExtensionsObjs}
	Lib {StdLibOpts} -o "{Targ}"	{CommResourceMgrExtensionsObjs}							¶
								-dn __CRMGETTOOLRESOURCE								¶
								-dn __CRMRELEASETOOLRESOURCE							¶
								-dn __CRMPARSECAPSRESOURCE								¶
								-dn __CRMGETTOOLNAMEDRESOURCE				


"{IfObjDir}ConnectionMgrExtensions.c.o"	Ä	"{CIncludes}CTBUtilities.h"					¶
											"{CIncludes}Connections.h"					¶
											"{CIncludes}ConnectionTools.h"				¶
											"{CIncludes}CommResources.h"				¶
											"{IntCIncludes}ConnectionsPriv.h"			¶
											"{IntCIncludes}CommToolboxPriv.h"			¶
											"{CTCnctDir}ConnectionMgrUtilities.c"		¶
											"{CTCnctDir}ConnectionMgrExtensions.c"
	C {IfCOpts} -i "{CTCnctDir}" -o "{Targ}" "{CTCnctDir}ConnectionMgrExtensions.c"


"{IfObjDir}ConnectionMgrExtensionsGlue.a.o"	Ä	"{AIncludes}Traps.a"					¶
												"{AIncludes}GestaltEqu.a"				¶
												"{IntAIncludes}GestaltPrivateEqu.a"		¶
												"{IntAIncludes}CommToolboxPriv.a"		¶
												"{CTGlueDir}ConnectionMgrExtensionsGlue.a"
	Asm {IfAOpts} -o "{Targ}" "{CTGlueDir}ConnectionMgrExtensionsGlue.a"


"{IfObjDir}FileTransferMgrExtensions.c.o"	Ä	"{CIncludes}CTBUtilities.h"				¶
												"{CIncludes}FileTransfers.h"			¶
												"{CIncludes}FileTransferTools.h"		¶
												"{CIncludes}CommResources.h"			¶
												"{IntCIncludes}CommToolboxPriv.h"		¶
												"{CTFileTransDir}FileTransferMgrUtilities.c" ¶
												"{CTFileTransDir}FileTransferMgrExtensions.c"
	C {IfCOpts} -o "{Targ}" -i "{CTFileTransDir}" "{CTFileTransDir}FileTransferMgrExtensions.c"


	
"{IfObjDir}TerminalMgrExtensionsGlue.a.o"	Ä	"{AIncludes}Traps.a"					¶
												"{IntAIncludes}CommToolboxPriv.a"		¶
												"{CTGlueDir}TerminalMgrExtensionsGlue.a"
	Asm {IfAOpts} -o "{Targ}" "{CTGlueDir}TerminalMgrExtensionsGlue.a"


"{IfObjDir}TerminalMgrExtensions.c.o"		Ä	"{CIncludes}CTBUtilities.h"				¶
												"{CIncludes}Terminals.h"				¶
												"{CIncludes}TerminalTools.h"			¶
												"{CIncludes}CommResources.h"			¶
												"{IntCIncludes}CommToolboxPriv.h"		¶
												"{CTTermDir}TerminalMgrUtilities.c"	¶
												"{CTTermDir}TerminalMgrExtensions.c"
	C {IfCOpts} -i "{CTTermDir}" -o "{Targ}" "{CTTermDir}TerminalMgrExtensions.c"


"{IfObjDir}CommRsrcMgrExtensionsGlue.a.o"	Ä	"{AIncludes}Traps.a"					¶
												"{IntAIncludes}CommToolboxPriv.a"		¶
												"{CTGlueDir}CommRsrcMgrExtensionsGlue.a"
	Asm {IfAOpts} -o "{Targ}" "{CTGlueDir}CommRsrcMgrExtensionsGlue.a"


"{IfObjDir}CommResourceMgrGlue.a.o"			Ä	"{CTGlueDir}CommResourceMgrGlue.a"
	Asm {IfAOpts} -o "{Targ}" "{CTGlueDir}CommResourceMgrGlue.a"


"{IfObjDir}CommToolboxCoreGlue.a.o"			Ä	"{CTGlueDir}CommToolboxCoreGlue.a"
	Asm {IfAOpts} -o "{Targ}" "{CTGlueDir}CommToolboxCoreGlue.a"


"{IfObjDir}CommToolboxUtilitiesGlue.a.o"	Ä	"{CTGlueDir}CommToolboxUtilitiesGlue.a"
	Asm {IfAOpts} -o "{Targ}" "{CTGlueDir}CommToolboxUtilitiesGlue.a"


"{IfObjDir}ConnectionMgrGlue.a.o"			Ä	"{CTGlueDir}ConnectionMgrGlue.a"
	Asm {IfAOpts} -o "{Targ}" "{CTGlueDir}ConnectionMgrGlue.a"


"{IfObjDir}FileTransferMgrGlue.a.o"			Ä	"{CTGlueDir}FileTransferMgrGlue.a"
	Asm {IfAOpts} -o "{Targ}" "{CTGlueDir}FileTransferMgrGlue.a"


"{IfObjDir}TerminalMgrGlue.a.o"	Ä	"{CTGlueDir}TerminalMgrGlue.a"
	Asm {IfAOpts} -o "{Targ}" "{CTGlueDir}TerminalMgrGlue.a"


"{IfObjDir}FileXferMgrExtensionsGlue.a.o"	Ä	"{CTGlueDir}FileXferMgrExtensionsGlue.a"
	Asm {IfAOpts} -o "{Targ}" "{CTGlueDir}FileXferMgrExtensionsGlue.a"


"{IfObjDir}CommResourceMgrExtensions.c.o"	Ä	"{CIncludes}Resources.h"				¶
												"{CIncludes}Memory.h"					¶
												"{CIncludes}CTBUtilities.h"				¶
												"{CIncludes}CommResources.h"			¶
												"{IntCIncludes}CommToolboxPriv.h"		¶
												"{CTRsrcDir}CommResourceMgrExtensions.c"
	C {IfCOpts} -i "{CTRsrcDir}" -o "{Targ}" "{CTRsrcDir}CommResourceMgrExtensions.c"


"{IfObjDir}"Copyright.a.o					Ä	"{IfSrcDir}Copyright.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}Copyright.a"


"{IfObjDir}"OSUTILS.a.o					Ä	"{IfSrcDir}OSUTILS.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}OSUTILS.a"


"{IfObjDir}"CONTROLS.a.o					Ä	"{IfSrcDir}CONTROLS.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}CONTROLS.a"


"{IfObjDir}"PrintCalls.a.o					Ä	"{IfSrcDir}PrintCalls.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}PrintCalls.a"


"{IfObjDir}"ToolTraps.a.o					Ä	"{IfSrcDir}ToolTraps.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}ToolTraps.a"


"{IfObjDir}"EnvironsGlue.a.o					Ä	"{IfSrcDir}EnvironsGlue.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}EnvironsGlue.a"


"{IfObjDir}"GestaltGlue.a.o					Ä	"{IfSrcDir}GestaltGlue.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}GestaltGlue.a"


"{IfObjDir}"PackTraps.a.o					Ä	"{IfSrcDir}PackTraps.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}PackTraps.a"


"{IfObjDir}"ListTraps.a.o					Ä	"{IfSrcDir}ListTraps.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}ListTraps.a"


"{IfObjDir}"Graf3DAsm.a.o					Ä	"{IfSrcDir}Graf3DAsm.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}Graf3DAsm.a"


"{IfObjDir}"SlotTraps.a.o					Ä	"{IfSrcDir}SlotTraps.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}SlotTraps.a"


"{IfObjDir}"Strings.a.o						Ä	"{IfSrcDir}Strings.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}Strings.a"


"{IfObjDir}"nAppleTalk.a.o					Ä	"{IfSrcDir}nAppleTalk.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}nAppleTalk.a"


"{IfObjDir}"ENet.a.o						Ä	"{IfSrcDir}ENet.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}ENet.a"


"{IfObjDir}"piMAIN.a.o						Ä	"{IfSrcDir}piMAIN.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}piMAIN.a"


"{IfObjDir}"desk.a.o						Ä	"{IfSrcDir}desk.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}desk.a"


"{IfObjDir}"devices.a.o						Ä	"{IfSrcDir}devices.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}devices.a"


"{IfObjDir}"files.a.o						Ä	"{IfSrcDir}files.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}files.a"


"{IfObjDir}"fonts.a.o						Ä	"{IfSrcDir}fonts.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}fonts.a"


"{IfObjDir}"GetPhysical.a.o					Ä	"{IfSrcDir}GetPhysical.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}GetPhysical.a"


"{IfObjDir}"lists.c.o						Ä	"{IfSrcDir}lists.c"
	C {IfCOpts} -o "{Targ}" "{IfSrcDir}lists.c"


"{IfObjDir}"menus.a.o						Ä	"{IfSrcDir}menus.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}menus.a"


"{IfObjDir}"PackagesGlue.a.o				Ä	"{IfSrcDir}PackagesGlue.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}PackagesGlue.a"


"{IfObjDir}"quickdraw.a.o					Ä	"{IfSrcDir}quickdraw.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}quickdraw.a"


"{IfObjDir}"resources.a.o					Ä	"{IfSrcDir}resources.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}resources.a"


"{IfObjDir}"segload.a.o						Ä	"{IfSrcDir}segload.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}segload.a"


"{IfObjDir}"textedit.a.o					Ä	"{IfSrcDir}textedit.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}textedit.a"


"{IfObjDir}"toolutils.a.o					Ä	"{IfSrcDir}toolutils.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}toolutils.a"


"{IfObjDir}"windows.a.o						Ä	"{IfSrcDir}windows.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}windows.a"


"{IfObjDir}"Power.a.o						Ä	"{IfSrcDir}Power.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}Power.a"


"{IfObjDir}"OSTraps.a.o						Ä	"{AIncludes}QuickDraw.a"				¶
												"{AIncludes}Traps.a"					¶
												"{AIncludes}SysEqu.a"					¶
												"{AIncludes}HardwareEqu.a"				¶
												"{AIncludes}Packages.a"					¶
												"{AIncludes}Printing.a"					¶
												"{AIncludes}SaneMacs.a"					¶
												"{AIncludes}SysErr.a"					¶
												"{AIncludes}FSEqu.a"					¶
												"{AIncludes}Private.a"					¶
												"{AIncludes}ToolUtils.a"				¶
												"{AIncludes}Slots.a"					¶
												"{ObjDir}"StandardEqu.d					¶
												"{IfSrcDir}OSTraps.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}OSTraps.a"


"{IfObjDir}"BitMapToRegion.a.o				Ä	"{AIncludes}QuickDraw.a"				¶
												"{AIncludes}Traps.a"					¶
												"{AIncludes}SysEqu.a"					¶
												"{AIncludes}HardwareEqu.a"				¶
												"{AIncludes}Packages.a"					¶
												"{AIncludes}Printing.a"					¶
												"{AIncludes}SaneMacs.a"					¶
												"{AIncludes}SysErr.a"					¶
												"{AIncludes}FSEqu.a"					¶
												"{AIncludes}Private.a"					¶
												"{AIncludes}ToolUtils.a"					¶
												"{AIncludes}Slots.a"					¶
												"{IfSrcDir}BitMapToRegion.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}BitMapToRegion.a"


"{IfObjDir}PPCGlue.a.o"						Ä	"{AIncludes}Traps.a"					¶
												"{AIncludes}SysEqu.a"					¶
												"{AIncludes}ToolUtils.a"					¶
												"{AIncludes}PPCToolbox.a"				¶
												"{IfSrcDir}PPCGlue.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}PPCGlue.a"


"{IfObjDir}HFSGlue.c.o"						Ä	"{IfSrcDir}HFSGlue.c"
	C {IfCOpts} -o "{Targ}" "{IfSrcDir}HFSGlue.c"


"{IfObjDir}FoldersGlue.c.o"					Ä	"{CIncludes}Folders.h"					¶
												"{CIncludes}GestaltEqu.h"				¶
												"{CIncludes}SysEqu.h"					¶
												"{CIncludes}Errors.h"					¶
												"{CIncludes}Files.h"					¶
												"{IfSrcDir}FoldersGlue.c"
	C {IfCOpts} -o "{Targ}" "{IfSrcDir}FoldersGlue.c"


"{IfObjDir}dialogs.a.o"						Ä	"{IntAIncludes}DialogsPriv.a"			¶
												"{IfSrcDir}dialogs.a"
	Asm {IfAOpts} -o "{Targ}" "{IfSrcDir}dialogs.a"
