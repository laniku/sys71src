#
#	File:		ADBMgr.make
#
#	Contains:	Makefile for ADB.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#

"{LibDir}ADBMgr.lib"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}HardwareEqu.a"						¶
									"{IntAIncludes}IOPEqu.a"						¶
									"{IntAIncludes}EgretEqu.a"						¶
									"{IntAIncludes}AppleDeskBusPriv.a"				¶
									"{IntAIncludes}ScriptPriv.a"					¶
									"{IntAIncludes}UniversalEqu.a"					¶
									"{ADBDir}ADBMgr.a"
	Asm {StdAOpts} -o "{Targ}" "{ADBDir}ADBMgr.a"