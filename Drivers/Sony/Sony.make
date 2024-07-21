#
#	File:		Sony.make
#
#	Contains:	Makefile for the Sony Driver.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	  <SMG2>	  9/1/93	chp		Added a new dependency on AMICEqu for SonySWIM3.
#	   <SM4>	 2/15/93	rab		Added SonyMFM.a and SonyRawTrack.a files to the dependancies.
#	   <SM3>	  2/5/93	GMR		Added SonySWIM3.a file, for PDM support.
#	   <SM2>	11/14/92	kc		Change link option used to name segment from -sg to -sn.

"{ObjDir}SonyHdr.a.o"		Ä		"{ObjDir}StandardEqu.d"						¶
									"{AIncludes}SonyEqu.a"						¶
									"{IntAIncludes}HardwarePrivateEqu.a"		¶
									"{AIncludes}HardwareEqu.a"					¶
									"{IntAIncludes}UniversalEqu.a"				¶
									"{AIncludes}FSEqu.a"						¶
									"{IntAIncludes}IOPEqu.a"					¶
									"{IntAIncludes}AMICEqu.a"					¶
									"{SonyDir}Sony.a"							¶
									"{SonyDir}SonyFormat.a"						¶
									"{SonyDir}SonyRead.a"						¶
									"{SonyDir}SonyRwt.a"						¶
									"{SonyDir}SonyUtil.a"						¶
									"{SonyDir}SonyIcon.a"						¶
									"{SonyDir}SonyWrite.a"						¶
									"{SonyDir}SonyHdr.a"						¶
									"{SonyDir}SonySWIM3.a"						¶
									"{SonyDir}SonyIOP.a"						¶
									"{SonyDir}SonyMFM.a"						¶
									"{SonyDir}SonyRawTrack.a"					¶
									"{SonyDir}SonyDup.a"						
	Asm {StdAOpts} -o "{Targ}" "{SonyDir}SonyHdr.a" -d supportsMFM=1 -d SonyNonPortable=1


"{RsrcDir}Sony.rsrc"		Ä		"{ObjDir}SonyHdr.a.o"
	Link {StdLOpts} {StdAlign} -o "{Targ}" "{ObjDir}SonyHdr.a.o" -sn Main=".Sony" -rt DRVR=4

