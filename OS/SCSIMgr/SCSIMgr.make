#
#	File:		SCSIMgr.make
#
#	Contains:	Makefile for main code image.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc.  All rights reserved.
#
#	Change History (most recent first):
#
#	   <SM5>	  2/8/93	CSS		Rollin Horror. Add SCSIMgr96BIOS.a, SCSIMgrHW96BIOS.a
#									SCSIMgrInit96BIOS.a, SCSIMgrInitDB.a, and SCSIMgrDB.a to the
#									build.
#	   <SM4>	  2/1/93	PN		Adding scsiLateLoad.a into the build
#	   <SM3>	11/30/92	SWC		Changed SCSIEqu.a->SCSI.a.
#	   <SM2>	11/20/92	SWC		Added dependencies for SCSIDiskMode.a.
#

SCSIObjects =		"{ObjDir}scsiboot.a.o"											¶
					"{ObjDir}SCSIDiskMode.a.o"										¶
					"{ObjDir}scsimgr96.a.o"											¶
					"{ObjDir}scsimgrPSC.a.o"										¶
					"{ObjDir}scsimgrhw.a.o"											¶
					"{ObjDir}scsimgrhw96.a.o"										¶
					"{ObjDir}scsimgrhwPSC.a.o"										¶
					"{ObjDir}scsimgrinit.a.o"										¶
					"{ObjDir}scsimgrinit96.a.o"										¶
					"{ObjDir}scsimgrinitPSC.a.o"									¶
					"{ObjDir}scsimgrinitflags.a.o"									¶
					"{ObjDir}scsimgrnew.a.o"										¶
					"{ObjDir}scsimgrold.a.o"										¶
					"{ObjDir}scsiLateLoad.a.o"										¶
					"{ObjDir}SCSILinkPatch.a.o"										¶
					"{ObjDir}SCSIMgr96BIOS.a.o"										¶
					"{ObjDir}SCSIMgrHW96BIOS.a.o"									¶
					"{ObjDir}SCSIMgrInit96BIOS.a.o"									¶
					"{ObjDir}SCSIMgrInitDB.a.o"										¶
					"{ObjDir}SCSIMgrDB.a.o"											¶
					
"{LibDir}SCSI.lib"	Ä	{SCSIObjects}
	Lib {StdLibOpts} -o "{Targ}" {SCSIObjects}


"{ObjDir}SCSIBoot.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{AIncludes}HardwareEqu.a"						¶
									"{AIncludes}SCSI.a"								¶
									"{SCSIDir}SCSIBoot.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIBoot.a"


"{ObjDir}SCSIDiskMode.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{AIncludes}SCSI.a"								¶
									"{IntAIncludes}PowerPrivEqu.a"					¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{AIncludes}Video.a"							¶
									"{IntAIncludes}DockingEqu.a"					¶
									"{IntAIncludes}SCSIDiskModeEqu.a"				¶
									"{SCSIDir}SCSIDiskMode.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIDiskMode.a"


"{ObjDir}SCSIMgrHW.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}SCSI.a"								¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{IntAIncludes}SCSIPriv.a"						¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{AIncludes}HardwareEqu.a"						¶
									"{SCSIDir}SCSIMgrHW.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgrHW.a"


"{ObjDir}SCSILinkPatch.a.o"		Ä 	"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{IntAIncludes}SCSIPriv.a"						¶
									"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}SCSI.a"								¶
									"{SCSIDir}SCSILinkPatch.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSILinkPatch.a"


"{ObjDir}SCSIMgrHW96.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}PowerPrivEqu.a"					¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{Aincludes}SCSI.a"								¶
									"{IntAIncludes}SCSIPriv.a"						¶
									"{IntAIncludes}SCSIEqu96.a"						¶
									"{SCSIDir}SCSIMgrHW96.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgrHW96.a"



"{ObjDir}SCSIMgrHWPSC.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{Aincludes}SCSI.a"								¶
									"{IntAIncludes}SCSIPriv.a"						¶
									"{IntAIncludes}SCSIEqu96.a"						¶
									"{IntAIncludes}MC680x0.a"						¶
									 "{SCSIDir}SCSIMgrHWPSC.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgrHWPSC.a"


"{ObjDir}SCSIMgrInit.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}SCSI.a"								¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{IntAIncludes}SCSIPriv.a"						¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{AIncludes}GestaltEqu.a"						¶
									"{AIncludes}HardwareEqu.a"						¶
									"{IntAIncludes}SCSIEqu96.a"						¶
									"{SCSIDir}SCSIMgrInit.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgrInit.a" -l -lo "{ObjDir}SCSIMgrInit.a.lst"


"{ObjDir}SCSIMgrInit96.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}HardwareEqu.a"						¶
									"{Aincludes}SCSI.a"								¶
									"{IntAIncludes}SCSIPriv.a"						¶
									"{IntAIncludes}PowerPrivEqu.a"					¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{IntAIncludes}SCSIEqu96.a"						¶
									"{SCSIDir}SCSIMgrInit96.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgrInit96.a"


"{ObjDir}SCSIMgrInitPSC.a.o"	Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{Aincludes}SCSI.a"								¶
									"{IntAIncludes}SCSIPriv.a"						¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{IntAIncludes}SCSIEqu96.a"						¶
									"{SCSIDir}SCSIMgrInitPSC.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgrInitPSC.a"


"{ObjDir}SCSIMgrInitFlags.a.o"	Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}SCSI.a"								¶
									"{AIncludes}GestaltEqu.a"						¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{AIncludes}HardwareEqu.a"						¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{SCSIDir}SCSIMgrInitFlags.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgrInitFlags.a"


"{ObjDir}SCSIEqu96.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{Aincludes}SCSI.a"								¶
									"{IntAIncludes}SCSIPriv.a"						¶
									"{IntAIncludes}PowerPrivEqu.a"					¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{SCSIDir}SCSIEqu96.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIEqu96.a"


"{ObjDir}SCSIMgrPSC.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{Aincludes}SCSI.a"								¶
									"{IntAIncludes}SCSIPriv.a"						¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{IntAIncludes}MC680x0.a"						¶
									"{IntAIncludes}SCSIEqu96.a"						¶
									"{SCSIDir}SCSIMgrPSC.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgrPSC.a"

"{ObjDir}SCSIMgr96.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{Aincludes}SCSI.a"								¶
									"{IntAIncludes}SCSIPriv.a"						¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{IntAIncludes}MC680x0.a"						¶
									"{IntAIncludes}SCSIEqu96.a"						¶
									"{SCSIDir}SCSIMgr96.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgr96.a"

"{ObjDir}SCSIMgrNew.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}SCSI.a"	 							¶
									"{IntAIncludes}SCSIPriv.a"						¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{AIncludes}HardwareEqu.a"						¶
									"{IntAIncludes}SCSIEqu96.a"						¶
									"{SCSIDir}SCSIMgrNew.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgrNew.a"


"{ObjDir}SCSIMgrOld.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}SCSI.a"								¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{IntAIncludes}SCSIPriv.a"						¶
									"{AIncludes}HardwareEqu.a"						¶
									"{SCSIDir}SCSIMgrOld.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgrOld.a"

"{ObjDir}scsiLateLoad.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{IntAIncludes}SCSIPriv.a"						¶
									"{AIncludes}FSEqu.a"							¶
									"{SCSIDir}scsiLateLoad.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}scsiLateLoad.a"

"{ObjDir}SCSIMgr96BIOS.a.o"			Ä	"{ObjDir}StandardEqu.d"						¶
										"{AIncludes}HardwareEqu.a"					¶
										"{Aincludes}SCSI.a"							¶
										"{IntAIncludes}SCSIPriv.a"					¶
										"{IntAIncludes}PowerPrivEqu.a"				¶
										"{IntAIncludes}UniversalEqu.a"				¶
										"{IntAIncludes}SCSIEqu96.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgr96BIOS.a"

"{ObjDir}SCSIMgrHW96BIOS.a.o"		Ä	"{ObjDir}StandardEqu.d"						¶
										"{IntAIncludes}PowerPrivEqu.a"				¶
										"{IntAIncludes}UniversalEqu.a"				¶
										"{Aincludes}SCSI.a"							¶
										"{IntAIncludes}SCSIPriv.a"					¶
										"{IntAIncludes}SCSIEqu96.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgrHW96BIOS.a"


"{ObjDir}SCSIMgrInit96BIOS.a.o"		Ä	"{ObjDir}StandardEqu.d"						¶
										"{AIncludes}HardwareEqu.a"					¶
										"{Aincludes}SCSI.a"							¶
										"{IntAIncludes}SCSIPriv.a"					¶
										"{IntAIncludes}PowerPrivEqu.a"				¶
										"{IntAIncludes}UniversalEqu.a"				¶
										"{IntAIncludes}SCSIEqu96.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgrInit96BIOS.a"

"{ObjDir}SCSIMgrInitDB.a.o"			Ä	"{ObjDir}StandardEqu.d"						¶
										"{AIncludes}HardwareEqu.a"					¶
										"{Aincludes}SCSI.a"							¶
										"{IntAIncludes}SCSIPriv.a"					¶
										"{IntAIncludes}PowerPrivEqu.a"				¶
										"{IntAIncludes}UniversalEqu.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgrInitDB.a"

"{ObjDir}SCSIMgrDB.a.o"				Ä	"{ObjDir}StandardEqu.d"						¶
										"{AIncludes}HardwareEqu.a"					¶
										"{Aincludes}SCSI.a"							¶
										"{IntAIncludes}SCSIPriv.a"					¶
										"{IntAIncludes}PowerPrivEqu.a"				¶
										"{IntAIncludes}UniversalEqu.a"
	Asm {StdAOpts} -o "{Targ}" "{SCSIDir}SCSIMgrDB.a"
