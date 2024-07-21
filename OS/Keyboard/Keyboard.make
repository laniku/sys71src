#
#	File:		Keyboard.make
#
#	Contains:	Makefile for the Keyboard resources.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#

"{RsrcDir}Kbd.rsrc"				Ä	"{KeyboardDir}Kbd.r"
	Rez {StdROpts} -o "{Targ}" "{KeyboardDir}Kbd.r"