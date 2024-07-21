/*
	File:		RiscLayout.r

	Contains:	This file describes the layout of the RISC ROM.
	
	Written by:	Kurt Clark.

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM5>	10/26/93	kc		Added native link map descriptions.
	   <SM4>	04-01-93	jmp		Corrected typo in in previous check-in.
	   <SM3>	04-01-93	jmp		Fixed the 'rrhd' resource format.
	   <SM2>	 3/31/93	kc		Include RomResoruces.r, add rmap record and change some of the
									other records to use the format used by the new RomLayout tool.
	   <SM2>	11/23/92	kc		Add RomBase.
*/

#include "RomTypes.r"

#include "RomResources.r"

#define RomSize		0x00300000
#define StartOfRom	0x00000000
#define EndOfRom	RomSize

/*
	hacked from GoNativeResourceIDs.h
*/
/*  ncod */	
 
#define	kCodeFragmentMgrResourceNum			0
#define	kMixedModeResourceNum				1
#define	kProcessMgrSupportResourceNum		8

/* nlib */

#define	kInterfaceLibResourceNum			5
#define	kPrivateInterfaceLibResourceNum		6
#define kMathLibResourceNum					9
#define kStdCLibResourceNum					10
#define kNQDResourceNum						11
#define	kFMSwapFontResourceNum				15
#define kStdTextResourceNum					16
#define kResourceMgrResourceNum				17
#define kQuickdrawTextResourceNum			18
#define kMemoryMgrResourceNum				19
#define kFontDispatchResourceNum			20

resource 'rsiz' (128, "Size of ROM Image") {

	RomSize;			/* Size of the ROM */
};

resource 'rbas' (128, "Base address of ROM Image") {

	RomBase;			/* Base address of the ROM */
};

resource 'rcod' (128, "Main Code Image") {

	{RsrcDir},			/* Path Name */
	
	"MainCode.rsrc",	/* File Name */
	
	'ZROM',				/* Resource Type */  
	
	0x0080,				/* Resource ID */
	
	StartOfRom			/* ROM Address */
};

resource 'rrhd' (128, "Resource Header") {

	kDynamicAddress,	/* Address */
	
	0x0000001A;			/* Fixup address */

};

resource 'rdcl' (128, "Decl Data") {

	{RsrcDir},			/* Path Name */
	
	"DeclData",			/* File Name */
	
	EndOfRom			/* ROM Address */
};

resource 'rcks' (128, "ROM Check Sum") {

	StartOfRom + 4,			/* Calculate checksum from */
	
	EndOfRom,			/* start of rom to end of rom */
	
	'ZROM',				/* Fixup Resource Type */  
	
	0x0080,				/* Fixup Resource ID */
	
	0x00000030,			/* Slice Checksum offset */
	
	0x00000000			/* Checksum offset */
};

resource 'rref' (129, "Size of ROM in bytes") {
	
	'ZROM',				/* Referenced Resource Type */  
	
	0x0080,				/* Referenced Resource ID */

	EndOfRom,			/* Referenced address */
	
	'ZROM',				/* Fixup Resource Type */  
	
	0x0080,				/* Fixup Resource ID */

	0x00000040;			/* Fixup address */
};

resource 'rmap' (128, "main code link map") {
	
	'ZROM',				/* Resource Type */
	
	0x0080,				/* Resource ID */
	
	{TextDir},			/* LinkMap Path Name */
	
	"MainCode.map",		/* LinkMap File Name */
	
	{TextDir},			/* Symbol Path Name */
	
	"MainCode.Sym"		/* Symbol File Name */
};

resource 'rrmp' (128, "native code fragment manager map") {
	
	'ncod',							/* Resource Type */
	
	kCodeFragmentMgrResourceNum,	/* Resource ID */
	
	{TextDir},						/* LinkMap Path Name */
	
	"CodeFragmentMgr.map", 			/* LinkMap File Name */
};

resource 'rrmp' (129, "native mixed mode manager map") {
	
	'ncod',							/* Resource Type */
	
	kMixedModeResourceNum,			/* Resource ID */
	
	{TextDir},						/* LinkMap Path Name */
	
	"MixedMode.map", 				/* LinkMap File Name */
};

resource 'rrmp' (130, "native process manager support map") {
	
	'ncod',							/* Resource Type */
	
	kProcessMgrSupportResourceNum,	/* Resource ID */
	
	{TextDir},						/* LinkMap Path Name */
	
	"ProcessMgrSupport.map", 		/* LinkMap File Name */
};

resource 'rrmp' (131, "native math lib map") {
	
	'nlib',							/* Resource Type */
	
	kMathLibResourceNum,			/* Resource ID */
	
	{TextDir},						/* LinkMap Path Name */
	
	"MathLib.map", 					/* LinkMap File Name */
};

resource 'rrmp' (132, "native standard c lib map") {
	
	'nlib',							/* Resource Type */
	
	kStdCLibResourceNum,			/* Resource ID */
	
	{TextDir},						/* LinkMap Path Name */
	
	"StdCLib.map", 					/* LinkMap File Name */
};

resource 'rrmp' (133, "native quick draw map") {
	
	'nlib',							/* Resource Type */
	
	kNQDResourceNum,				/* Resource ID */
	
	{TextDir},						/* LinkMap Path Name */
	
	"NQD.map", 						/* LinkMap File Name */
};

resource 'rrmp' (134, "native fm swap font map") {
	
	'nlib',							/* Resource Type */
	
	kFMSwapFontResourceNum,			/* Resource ID */
	
	{TextDir},						/* LinkMap Path Name */
	
	"FMSwapFont.map", 				/* LinkMap File Name */
};

resource 'rrmp' (135, "native standard text map") {
	
	'nlib',							/* Resource Type */
	
	kStdTextResourceNum,			/* Resource ID */
	
	{TextDir},						/* LinkMap Path Name */
	
	"StdText.map",					/* LinkMap File Name */
};

resource 'rrmp' (136, "native resource manager map") {
	
	'nlib',							/* Resource Type */
	
	kResourceMgrResourceNum,		/* Resource ID */
	
	{TextDir},						/* LinkMap Path Name */
	
	"CResourceMgr.map",				/* LinkMap File Name */
};

resource 'rrmp' (137, "native quickdraw text map") {
	
	'nlib',							/* Resource Type */
	
	kQuickdrawTextResourceNum,		/* Resource ID */
	
	{TextDir},						/* LinkMap Path Name */
	
	"QuickdrawText.map", 			/* LinkMap File Name */
};

resource 'rrmp' (138, "native memory manager map") {
	
	'nlib',							/* Resource Type */
	
	kMemoryMgrResourceNum,			/* Resource ID */
	
	{TextDir},						/* LinkMap Path Name */
	
	"MemoryMgr.map", 				/* LinkMap File Name */
};

resource 'rrmp' (139, "native font dispatch map") {
	
	'nlib',							/* Resource Type */
	
	kFontDispatchResourceNum,		/* Resource ID */
	
	{TextDir},						/* LinkMap Path Name */
	
	"FontDispatch.map", 			/* LinkMap File Name */
};
