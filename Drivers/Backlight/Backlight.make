#
#	File:		Backlight.make
#
#	Contains:	Makefile for Backlight.
#
#	Written by:	ricardo batista
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM2>	12/13/93	PN		Roll in KAOs and Horror changes to support Malcom and AJ
#									machines
#	   <SM2>	 2/11/93	CSS		Update from Horror.  Add "backlightinput.c.o" and
#									"backlightcpu.c.o" to the build.
#		 <1>	12/18/92	RB		first checked in
#	   <SM1>	11/14/92	rb		New today

#___________________________________________________________________________________________________
# Backlight driver

BL_DRVR_OBJ		=	"{ObjDir}backlight.c.o"											¶
					"{ObjDir}backlight.a.o"											

"{ObjDir}backlight.a.o" 	Ä	"{AIncludes}SysEqu.a"								¶
								"{AIncludes}SysErr.a"								¶
								"{BackLightDir}backlight.a"
	Asm -o {Targ} "{BackLightDir}backlight.a" {StdAOpts}

"{ObjDir}backlight.c.o" 	Ä	"{BackLightDir}backlight.h"							¶
								"{BackLightDir}PowerMgr.h"							¶
								"{CIncludes}SysEqu.h"								¶
								"{CIncludes}memory.h"								¶
								"{CIncludes}OSEvents.h"								¶
								"{CIncludes}devices.h"								¶
								"{CIncludes}errors.h"								¶
								"{CIncludes}retrace.h"								¶
								"{CIncludes}Shutdown.h"								¶
								"{BackLightDir}backlight.c"
	C -o {Targ} "{BackLightDir}backlight.c" {StdCOpts}


"{ObjDir}register.c.o" 		Ä	"{BackLightDir}backlight.h"							¶
								"{BackLightDir}PowerMgr.h"							¶
								"{BackLightDir}register.c"
	C -o {Targ} "{BackLightDir}register.c" {StdCOpts}


"{RsrcDir}Backlight.DRVW"	Ä	{BL_DRVR_OBJ}
	Link -o {Targ} -rt "DRVW"=-16511 -sg backlight 									¶
								"{Libraries}DRVRRuntime.o"							¶
								{BL_DRVR_OBJ}										

"{RsrcDir}Backlight.RSRC"	Ä	{BL_DRVR_OBJ}										¶
								"{RsrcDir}Backlight.DRVW"							¶
								"{BackLightDir}backlight.r"
	Rez -o {Targ} {StdROpts} "{BackLightDir}backlight.r"							¶
								-d Obj="¶"{RsrcDir}Backlight.DRVW¶""


