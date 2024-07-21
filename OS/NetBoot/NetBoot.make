#
#	File:		NetBoot.make
#
#	Contains:	Makefile for ATBoot.rsrc NetBoot.rsrc.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM2>	 6/14/93	kc		Roll in Ludwig.
#	   <LW3>	  4/8/93	fau		Removed netlmgrboot.a.o from the dependencies.  Change the
#									ATBOOT driver res-id to 60 (the last change is not really needed
#									because that driver is now loaded through a drvrInstall, instead
#									of through an open.
#	   <SM3>	12/11/92	chp		Removed runtime library routines not needed when compiled for
#									68020 or better.
#	   <SM2>	11/11/92	RB		Add "{ObjDir}StandardEqu.d"

ATBootObj 	= 			"{ObjDir}ATBoot.a.o"		¶
						"{ObjDir}BootUtils.a.o" 	¶
						"{ObjDir}GetServer.c.o"		¶
						"{ObjDir}NewProto.a.o"		¶
						"{ObjDir}Hash.c.o"			¶
						"{ObjDir}Hash.a.o"			¶
						"{ObjDir}ATBoot.c.o"		¶
						"{IfObjDir}interface.o"		¶
						"{CLibraries}"StdCLib.o 		



NetBootOBJ =			"{ObjDir}netBoot.a.o" 		¶
						"{ObjDir}BootUtils.a.o" 	¶
						"{ObjDir}netBoot.c.o"		¶
						"{IfObjDir}interface.o"



XONetBootOBJ	= 		"{ObjDir}ForXO.a.o"			¶
						"{ObjDir}NetBoot.a.o" 		¶
						"{ObjDir}NetBoot.c.o" 		¶
						"{ObjDir}BootUtils.a.o" 	¶
						"{ObjDir}ATBoot.a.o"		¶
						"{ObjDir}GetServer.c.o"		¶
						"{ObjDir}NewProto.a.o"		¶
						"{ObjDir}Hash.c.o"			¶
						"{ObjDir}Hash.a.o"			¶
						"{ObjDir}ATBoot.c.o"		¶
						"{ObjDir}NetBootlmgr.a.o"	¶
						"{IfObjDir}interface.o"


"{RsrcDir}ATBoot.rsrc"		Ä	{ATBootObj} 
	Link {StdLOpts} {StdAlign} -o "{Targ}"				¶
		-t rsrc -c 'RSED'				¶
		-rt DRVR=60 					¶
		-sn Main='.ATBoot' 				¶
		-ma MAIN='.ATBoot' 				¶
		-sn STDCLIB='.ATBoot' 			¶
		-m ATBOOT 						¶
		{ATBootObj}


"{RsrcDir}NetBoot.rsrc"		Ä	{NetBootOBJ}
	Link {StdLOpts} {StdAlign} -o "{Targ}"				¶
		-t rsrc -c 'RSED'				¶
		-rt DRVR=49						¶
		-sn Main='.netBOOT' 			¶
		-ma MAIN='.netBoot' 			¶
		-m NETBOOT 						¶
		{NetBootObj}		


"{RsrcDir}XONetBoot.rsrc"	Ä	{XONetBootOBJ}
	Link {StdLOpts} {StdAlign} -t APPL -c '????' 	¶
		-t rsrc -c 'RSED'				¶
		-rt INIT=1						¶
		-sn Main='InstallNetBoot' 		¶
		-ma MAIN='InstallNetBoot' 		¶
		-m INSTALLNETBOOT 				¶
		{XONetBootOBJ}				


"{ObjDir}netBoot.a.o"		Ä	"{NetBootDir}netBoot.a"				¶
								"{NetBootDir}NetBootEqu.a"
	Asm {StdAOpts} -o "{Targ}" -w -wb -d &ForRam=0 "{NetBootDir}netBoot.a"


"{ObjDir}BootUtils.a.o" 	Ä	"{NetBootDir}BootUtils.a"
	Asm {StdAOpts} -o "{Targ}" -w -wb -d &ForRam=0 "{NetBootDir}BootUtils.a"


"{ObjDir}ForXO.a.o"			Ä	"{NetBootDir}forXO.a"
	Asm {StdAOpts} -o "{Targ}" -w -wb -d &ForRam=0 "{NetBootDir}ForXO.a"


"{ObjDir}ATBoot.a.o"		Ä	"{ObjDir}StandardEqu.d"				¶
								"{NetBootDir}NetBootEqu.a"			¶
								"{NetBootDir}ATBoot.a"
	Asm {StdAOpts} -o "{Targ}" -w -wb -d &ForRam=0 "{NetBootDir}ATBoot.a"


"{ObjDir}NewProto.a.o"		Ä	"{NetBootDir}NewProto.a"			¶
								"{NetBootDir}ATBootEqu.a"
	Asm {StdAOpts} -o "{Targ}" -d &ForRam=0 "{NetBootDir}NewProto.a"


"{ObjDir}Hash.a.o"			Ä	"{NetBootDir}Hash:Hash.a"
	Asm {StdAOpts} -o "{Targ}" -case on -d &ForRam=0 "{NetBootDir}Hash:Hash.a"


"{ObjDir}NetBootlmgr.a.o"	Ä 	"{NetBootDir}netBootlmgr.a" 		¶
								"{ObjDir}StandardEqu.d"				¶
								"{AIncludes}"AppleTalk.a 			¶
								"{IntAIncludes}"ATalkPrivateEQU.a
	Asm {StdAOpts} -o "{Targ}" -d ATLK=0 -d &ForRam=0 "{NetBootDir}NetBootlmgr.a" -i "{NetBootDir}ATIncludes:"


"{ObjDir}netBoot.c.o"		Ä	"{NetBootDir}netBoot.c"				¶
								"{NetBootDir}netBoot.h"
	C {StdCOpts} -o "{Targ}" -b2 "{NetBootDir}netBoot.c"


"{ObjDir}ATBoot.c.o"		Ä	"{NetBootDir}ATBoot.c"				¶
								"{NetBootDir}ATBootEqu.h"
	C {StdCOpts} -o "{Targ}" -i "{NetBootDir}" -b2 -sym off "{NetBootDir}ATBoot.c"


"{ObjDir}GetServer.c.o"		Ä	"{NetBootDir}GetServer.c"			¶
								"{NetBootDir}ATBootEqu.h"
	C {StdCOpts} -o "{Targ}" -i "{NetBootDir}" -b2 -sym off "{NetBootDir}GetServer.c"


"{ObjDir}Hash.c.o"			Ä	"{NetBootDir}Hash:Hash.c"			¶
								"{NetBootDir}ATBootEqu.h"
	C {StdCOpts} -o "{Targ}" -i "{NetBootDir}" -b2 -sym off "{NetBootDir}Hash:Hash.c"
