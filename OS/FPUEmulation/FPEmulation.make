#
#	File:		FPUEmulation.make
#
#	Contains:	Makefile for the FPU emulation library for the 040.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#

"{ObjDir}FPEmulation.a.o"	Ä	"{AIncludes}SysEqu.a"							¶
								"{FPEmulationDir}"BinDec.a						¶
								"{FPEmulationDir}"BugFix.a						¶
								"{FPEmulationDir}"Constants.a					¶
								"{FPEmulationDir}"DecBin.a						¶
								"{FPEmulationDir}"DoFunc.a						¶
								"{FPEmulationDir}"FPSP.h						¶
								"{FPEmulationDir}"FPEmulation.a					¶
								"{FPEmulationDir}"FPSPMain.a					¶
								"{FPEmulationDir}"GenExcept.a					¶
								"{FPEmulationDir}"GetEM.a						¶
								"{FPEmulationDir}"GetOp.a						¶
								"{FPEmulationDir}"Hyperbolic.a					¶
								"{FPEmulationDir}"Int.a							¶
								"{FPEmulationDir}"InvTrig.a						¶
								"{FPEmulationDir}"KernelEx.a					¶
								"{FPEmulationDir}"Log.a							¶
								"{FPEmulationDir}"MoveCR.a						¶
								"{FPEmulationDir}"Power.a						¶
								"{FPEmulationDir}"RemMod.a						¶
								"{FPEmulationDir}"ResFunc.a						¶
								"{FPEmulationDir}"Round.a						¶
								"{FPEmulationDir}"Scale.a						¶
								"{FPEmulationDir}"Trig.a						¶
								"{FPEmulationDir}"Util.a						¶
								"{FPEmulationDir}"XBSUN.a						¶
								"{FPEmulationDir}"XFLine.a						¶
								"{FPEmulationDir}"XOpErr.a						¶
								"{FPEmulationDir}"XOvfl.a						¶
								"{FPEmulationDir}"XSNAN.a						¶
								"{FPEmulationDir}"XStore.a						¶
								"{FPEmulationDir}"XUnfl.a						¶
								"{FPEmulationDir}"XUnImp.a						¶
								"{FPEmulationDir}"XUnSupp.a						¶
								"{FPEmulationDir}"FPEmulation.a
	Asm {StdAOpts} -o "{Targ}" "{FPEmulationDir}FPEmulation.a"
