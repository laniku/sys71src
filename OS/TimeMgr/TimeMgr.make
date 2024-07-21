#
#	File:		TimeMgr.make
#
#	Contains:	Makefile for the Time Manager.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#

TimeMgrObjs	=					"{ObjDir}TimeMgr.a.o"								¶
								"{ObjDir}TimeMgrPatch.a.o"


"{LibDir}TimeMgr.lib"			Ä	{TimeMgrObjs}
	Lib {StdLibOpts} -o "{Targ}" {TimeMgrObjs}


"{ObjDir}TimeMgr.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{TimeMgrDir}TimeMgr.a"
	Asm {StdAOpts} -o "{Targ}" "{TimeMgrDir}TimeMgr.a"


"{ObjDir}TimeMgrPatch.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{TimeMgrDir}TimeMgrPatch.a"
	Asm {StdAOpts} -o "{Targ}" "{TimeMgrDir}TimeMgrPatch.a"

