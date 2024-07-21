#
#	File:		EDisk.make
#
#	Contains:	Makefile for EDisk.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM2>	11/14/92	kc		Change link option used to name segment from -sg to -sn.


"{RsrcDir}EDisk.rsrc"			Ä	"{ObjDir}EDiskDriver.a.o"
	Link {StdLOpts} {StdAlign} -o "{Targ}"  -sn Main=".EDisk" -rt DRVR=48 "{ObjDir}EDiskDriver.a.o"


"{ObjDir}EDiskDriver.a.o"			Ä	"{ObjDir}StandardEqu.d"							¶
									"{AIncludes}HardwareEqu.a"						¶
									"{AIncludes}SonyEqu.a"							¶
									"{IntAIncludes}EDiskEqu.a"						¶
									"{EDiskDir}EDiskDriver.a"
	Asm {StdAOpts} -o "{Targ}" "{EDiskDir}EDiskDriver.a" -d SonyNonPortable=1
