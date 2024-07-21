#
#	File:		VDig.make
#
#	Contains:	Makefile for VDig.
#
#	Written by:	Chas. Spillar
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM6>	 8/17/93	BG		Added a small amount of cheese required by Make to be a good
#									citizen.  I broke the source file dependencies out but if any of
#									those dependencies become true, there was nothing that HAPPENED
#									to cause those dependencies to  go away.  Added SetFile -m .
#									{Targ} to each of the source file dependencies to make sure that
#									the .c.o dependencies don't get re-built more than once.
#	   <SM5>	 8/17/93	BG		Fix dependencies for VDigC.c.o and its accompanying files.
#	   <SM4>	 6/14/93	kc		Roll in Ludwig (for real this time).
#	   <SM3>	  6/3/93	kc		Backout last checkin until I am ready to checkin everything.
#	   <SM2>	  6/3/93	kc		Roll in Ludwig.
#	   <LW6>	 4/15/93	DH		For b5 build; took out Runtime.o and CSANEL.o that were no
#									longer needed.
#	   <LW5>	  4/5/93	fau		Added a dependency on DepVideo.h.
#	   <LW4>	  1/4/93	fau		Added support for the VDigUtils.c file.
#	   <LW3>	12/23/92	fau		Changed code resource to be the official -16729.
#	   <LW2>	12/15/92	chp		Modified for new paths to Interface.o, Runtime.o, and
#									CSANELib.o.
#	   <SM2>	11/14/92	kc		Change link option used to name segment from -sg to -sn.
#	   <SM1>	 9/17/92	CSS		first checked in to SuperMario
#
#

# Do not change the order of VDigCObjects.

VDigCObjects						=	"{ObjDir}VDigC.c.o"				¶
										"{ObjDir}VDigUtils.c.o"			¶
										"{ObjDir}IICTest.a.o"			¶
										"{IfObjDir}Interface.o"			



"{RsrcDir}VDigT.rsrc"				ÄÄ	"{VDigDir}Cyclone_VDig.r"		¶
										"{RIncludes}Types.r"			¶
										"{RIncludes}MPWTypes.r"			¶
										"{RIncludes}ImageCodec.r"
	Rez {StdROpts} -o "{Targ}" "{VDigDir}Cyclone_VDig.r" || Exit 1


"{RsrcDir}VDigC.rsrc"				ÄÄ	{VDigCObjects}
	Link {StdLOpts} {StdAlign} -o "{Targ}" -rt code=-16729 -m MAIN -sn Main="Cyclone_VDig" -rn {VDigCObjects} || Exit 1


"{ObjDir}VDigUtils.c.o" 			Ä 	"{VDigDir}VDigUtils.c"			¶
										"{VDigDir}Cyclone.c"
	C {StdCOpts} -o "{Targ}" {VDigDir}VDigUtils.c -b2 

"{ObjDir}VDigC.c.o" 				Ä 	"{VDigDir}Cyclone.c"			¶
										"{VDigDir}VDigUtils.c"
	C {StdCOpts} -o "{Targ}" {VDigDir}Cyclone.c -b2 


"{ObjDir}IICTest.a.o" 				Ä	"{VDigDir}IICTest.a"
	Asm {StdAOpts} -o "{Targ}" "{VDigDir}IICTest.a"

#	Identify dependencies for the source files as well					<SM5>
#	(BTW - why is "EgretEqu.h" local to {VDigDir}?  It should be in {CIncludes})

"{VDigDir}Cyclone.c"				Ä	"{CIncludes}Devices.h"				¶
										"{CIncludes}Files.h"				¶
										"{CIncludes}FixMath.h"				¶
										"{CIncludes}GestaltEqu.h"			¶
										"{IntCIncludes}GestaltPrivateEqu.h"	¶
										"{CIncludes}Math.h"					¶
										"{CIncludes}Memory.h"				¶
										"{CIncludes}Resources.h"			¶
										"{CIncludes}RomDefs.h"				¶
										"{CIncludes}Slots.h"				¶
										"{CIncludes}ToolUtils.h"			¶
										"{CIncludes}Components.h"			¶
										"{CIncludes}QTComponents.h"			¶
										"{VDigDir}EgretEqu.h"				¶
										"{VDigDir}I2C.h"					¶
										"{VDigDir}philips.h"				¶
										"{VDigDir}Cyclone.h"				¶
										"{VDigDir}CycloneDigi.h"			¶
										"{IntCIncludes}DepVideo.h"
	SetFile -m . {Targ}


"{VDigDir}VDigUtils.c"				Ä	"{CIncludes}Devices.h"				¶
										"{IntCIncludes}DepVideo.h"			¶
										"{CIncludes}Palettes.h"				¶
										"{CIncludes}RomDefs.h"				¶
										"{CIncludes}Slots.h"				¶
										"{CIncludes}ToolUtils.h"			¶
										"{CIncludes}Video.h"				¶
										"{VDigDir}Cyclone.h"
	SetFile -m . {Targ}

"{VDigDir}IICTest.a"				Ä	"{AIncludes}SysEqu.a"				¶
										"{AIncludes}SysErr.a"				¶
										"{AIncludes}ToolUtils.a"			¶
										"{AIncludes}Traps.a"
	SetFile -m . {Targ}

#	"I just LOVE nested #include files. (NOT!)"

"{VDigDir}Cyclone.h"				Ä	"{VDigDir}Philips.h"				¶
										"{CIncludes}Quickdraw.h"			¶
										"{CIncludes}QuickTimeComponents.h"
	SetFile -m . {Targ}
