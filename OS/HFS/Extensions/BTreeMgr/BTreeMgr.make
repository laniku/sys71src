#
#	File:		BTreeMgr.make
#
#	Contains:	Makefile to build the B-Tree library.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM1>	12/14/92	CSS		Checkout to add BTreeGlue.a build which is required by DictionaryMgr.rsrc.


BTreeMgrObjects	=	"{ObjDir}BTreeAlloc.a.o"	¶
					"{ObjDir}BTreeFuncs.a.o"	¶
					"{ObjDir}BTreeMaint1.a.o"	¶
					"{ObjDir}BTreeMaint2.a.o"	¶
					"{ObjDir}BTreeQueue.a.o"	¶
					"{ObjDir}BTreeSvcs.a.o"	


"{LibDir}BTreeMgr.lib"			Ä	{BTreeMgrObjects}
	Lib {StdLibOpts} -o "{Targ}" {BTreeMgrObjects}


"{ObjDir}BTreeAlloc.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}BtreeEqu.a"						¶
									"{HFSBTreeDir}BtreePrivate.a"					¶
									"{HFSBTreeDir}BTreeAlloc.a"
	Asm {StdAOpts} -o "{Targ}" "{HFSBTreeDir}BTreeAlloc.a"


"{ObjDir}BTreeFuncs.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}BTreeEqu.a"						¶
									"{AIncludes}Processes.a"						¶
									"{IntAIncludes}FileMgrPrivate.a"				¶
									"{HFSBTreeDir}BTreePrivate.a"					¶
									"{HFSExtensionsDir}DTDBMgrPriv.a"				¶
									"{HFSBTreeDir}BTreeFuncs.a"
	Asm {StdAOpts} -o "{Targ}" "{HFSBTreeDir}BTreeFuncs.a" -i "{HFSExtensionsDir}"


"{ObjDir}BTreeMaint1.a.o"		Ä	"{ObjDir}StandardEqu.d"							¶
									"{HFSBTreeDir}BTreeMaint1.a"
	Asm {StdAOpts} -o "{Targ}" "{HFSBTreeDir}BTreeMaint1.a"


"{ObjDir}BTreeMaint2.a.o"		Ä 	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}BtreeEqu.a"						¶
									"{HFSBTreeDir}BtreePrivate.a"					¶
									"{HFSBTreeDir}BTreeMaint2.a"
	Asm {StdAOpts} -o "{Targ}" "{HFSBTreeDir}BTreeMaint2.a"


"{ObjDir}BTreeQueue.a.o"		Ä 	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}BTreeEqu.a"						¶
									"{IntAIncludes}FileMgrPrivate.a"				¶
									"{AIncludes}HardwareEqu.a"						¶
									"{HFSBTreeDir}BtreePrivate.a"					¶
									"{HFSBTreeDir}BTreeQueue.a"
	Asm {StdAOpts} -o "{Targ}" "{HFSBTreeDir}BTreeQueue.a"


"{ObjDir}BTreeSvcs.a.o"			Ä 	"{ObjDir}StandardEqu.d"							¶
									"{IntAIncludes}BTreeEqu.a"						¶
									"{HFSBTreeDir}BtreePrivate.a"					¶
									"{HFSBTreeDir}BTreeSvcs.a"
	Asm {StdAOpts} -o "{Targ}" "{HFSBTreeDir}BTreeSvcs.a"

#--- the following is added for the dictionary managers use - css

{ObjDir}BTreeGlue.a.o			Ä	{HFSBTreeDir}BTreeGlue.a
	Asm {StdAOpts} -o "{Targ}" {HFSBTreeDir}BTreeGlue.a

