#
#	File:		TrapDispatcher.make
#
#	Contains:	Makefile for TrapDispatcher.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#

"{ObjDir}Dispatch.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}HardwarePrivateEqu.a"			¶
									"{AIncludes}HardwareEqu.a"						¶
									"{TrapDispDir}Dispatch.a"
	Asm {StdAOpts} -o "{Targ}" "{TrapDispDir}Dispatch.a"

