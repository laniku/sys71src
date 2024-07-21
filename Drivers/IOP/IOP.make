#
#	File:		IOP.make
#
#	Contains:	Makefile for IOP stuff.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM2>	 11/9/93	KW		changed scciop link rules


"{RsrcDir}SWIMIOP.rsrc"		Ä	"{ObjDir}SWIMIOP.BIN"								¶
								"{RsrcDir}MakeIOPCRes"
	"{RsrcDir}MakeIOPCRes" -r "{Targ}" -s 16384 -i 1 -o 1 -b "{ObjDir}SWIMIOP.BIN"


"{RsrcDir}SCCIOP.rsrc"		Ä	"{ObjDir}SCCIOP.BIN"								¶
								"{RsrcDir}MakeIOPCRes"
	"{RsrcDir}MakeIOPCRes" -r "{Targ}" -s 3072 -i 0 -o 1 -b "{ObjDir}SCCIOP.BIN"


"{ObjDir}SWIMIOP.BIN"		Ä	"{ObjDir}SWIMIOP.load"
	MakeBinIIGS "{ObjDir}SWIMIOP.load" -o "{Targ}"


"{ObjDir}SCCIOP.BIN"		Ä	"{ObjDir}SCCIOP.load"
	MakeBinIIGS "{ObjDir}SCCIOP.load" -o "{Targ}"


"{ObjDir}SWIMIOP.load"		Ä	"{ObjDir}IOPKernel.aii.obj"							¶
								"{ObjDir}SWIMIOP.aii.obj"							¶
								"{ObjDir}ADBDriver.aii.obj"							¶
								"{ObjDir}SWIMDriver.aii.obj"
	LinkIIGS -s -l -w -lseg SWIMIOP -o "{Targ}" -apw > "{ObjDir}SWIMIOP.map"		¶
		-org $0001	"{ObjDir}IOPKernel.aii.obj"(@zdata)								¶
					"{ObjDir}SWIMIOP.aii.obj"(@zdata)								¶
					"{ObjDir}ADBDriver.aii.obj"(@zdata)								¶
					"{ObjDir}SWIMDriver.aii.obj"(@zdata)							¶
					"{ObjDir}IOPKernel.aii.obj"(@zcode)								¶
					"{ObjDir}SWIMIOP.aii.obj"(@zcode)								¶
					"{ObjDir}ADBDriver.aii.obj"(@zcode)								¶
					"{ObjDir}SWIMDriver.aii.obj"(@zcode)							¶
		-org $0400	"{ObjDir}IOPKernel.aii.obj"(@PageData)							¶
					"{ObjDir}SWIMIOP.aii.obj"(@PageData)							¶
					"{ObjDir}ADBDriver.aii.obj"(@PageData)							¶
					"{ObjDir}SWIMDriver.aii.obj"(@PageData)							¶
					"{ObjDir}IOPKernel.aii.obj"(@data)								¶
					"{ObjDir}SWIMIOP.aii.obj"(@data)								¶
					"{ObjDir}ADBDriver.aii.obj"(@data)								¶
					"{ObjDir}SWIMDriver.aii.obj"(@data)								¶
		-org $5000 	"{ObjDir}IOPKernel.aii.obj"(@code)								¶
					"{ObjDir}SWIMIOP.aii.obj"(@code)								¶
					"{ObjDir}ADBDriver.aii.obj"(@code)								¶
					"{ObjDir}SWIMDriver.aii.obj"(@code)								¶
		-org $7700	"{ObjDir}IOPKernel.aii.obj"(@PageConsts)						¶
					"{ObjDir}SWIMIOP.aii.obj"(@PageConsts)							¶
					"{ObjDir}ADBDriver.aii.obj"(@PageConsts)						¶
					"{ObjDir}SWIMDriver.aii.obj"(@PageConsts)						¶
					"{ObjDir}IOPKernel.aii.obj"(@WordConsts)						¶
					"{ObjDir}SWIMIOP.aii.obj"(@WordConsts)							¶
					"{ObjDir}ADBDriver.aii.obj"(@WordConsts)						¶
					"{ObjDir}SWIMDriver.aii.obj"(@WordConsts)						¶
					"{ObjDir}IOPKernel.aii.obj"(@constants)							¶
					"{ObjDir}SWIMIOP.aii.obj"(@constants)							¶
					"{ObjDir}ADBDriver.aii.obj"(@constants)							¶
					"{ObjDir}SWIMDriver.aii.obj"(@constants)						¶
		-org $7FE5	"{ObjDir}IOPKernel.aii.obj"(@vectors)


"{ObjDir}SCCIOP.load"		Ä	"{ObjDir}SCCIOP.aii.obj"
	LinkIIGS -s -l -w -lseg SCCIOP -o "{Targ}" -apw > "{ObjDir}SCCIOP.map"			¶
			 -org $0001	"{ObjDir}SCCIOP.aii.obj"(@IOPOS)							¶
			 -org $0400 "{ObjDir}SCCIOP.aii.obj"(@Main)								¶
			 -org $7ffa "{ObjDir}SCCIOP.aii.obj"(@Vectors)

#						"{ObjDir}SCCIOP.aii.obj"									¶
#

"{ObjDir}IOPKernel.aii.obj"		Ä	"{IOPDir}IOPDefs.aii"							¶
									"{IOPDir}IOPKernel.aii"
	AsmIIGS -o "{Targ}" "{IOPDir}IOPKernel.aii"



"{ObjDir}SWIMIOP.aii.obj"		Ä	"{IOPDir}IOPDefs.aii"							¶
									"{IOPDir}SWIMDefs.aii"							¶
									"{IOPDir}SWIMIOP.aii"
	AsmIIGS -o "{Targ}" "{IOPDir}SWIMIOP.aii"



"{ObjDir}SWIMDriver.aii.obj"	Ä	"{IOPDir}IOPDefs.aii"							¶
									"{IOPDir}SWIMDefs.aii"							¶
									"{IOPDir}SWIMDriver.aii"
	AsmIIGS -o "{Targ}" "{IOPDir}SWIMDriver.aii"



"{ObjDir}ADBDriver.aii.obj"		Ä	"{IOPDir}IOPDefs.aii"							¶
									"{IOPDir}SWIMDefs.aii"							¶
									"{IOPDir}ADBDriver.aii"
	AsmIIGS -o "{Targ}" "{IOPDir}ADBDriver.aii"



"{ObjDir}SCCIOP.aii.obj"		Ä	"{IOPDir}SCCIOPEqu.aii"							¶
									"{IOPDir}SCCIOPSysEqu.aii"						¶
									"{IOPDir}SCCIOP.aii"
	AsmIIGS -o "{Targ}" "{IOPDir}SCCIOP.aii"
