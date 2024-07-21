#
#	File:		NewAge.make
#
#	Contains:	Makefile for the NewAge Driver.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM2>	 6/14/93	kc		Roll in Ludwig.
#	   <LW2>	 2/16/93	WS		Add PSCEqu.a to dependencies.
#	   <SM2>	11/20/92	RB		Changed SndLOpts to StdLOpts


"{RsrcDir}NewAge.rsrc"				Ä	"{ObjDir}NewAgeDrvr.a.o"
	Link {StdLOpts} {StdAlign} -o "{Targ}" -rt DRVR=04 -sn Main=".NewAge" "{ObjDir}NewAgeDrvr.a.o"


"{ObjDir}NewAgeDrvr.a.o"		Ä	"{ObjDir}StandardEqu.d"					¶
									"{NewAgeDir}NewAgeEqu.a"				¶
									"{NewAgeDir}NewAgeDrvr.a"				¶
									"{IntAIncludes}PSCEqu.a"
	Asm {StdAOpts} -i "{NewAgeDir}" -w -o "{Targ}" "{NewAgeDir}NewAgeDrvr.a"
