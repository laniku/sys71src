/*
	File:		LC930Layout.r

	Contains:	This file describes the layout of the LC930 ROM.
	
	Written by:	Kurt Clark.

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	 3/31/93	kc		Include RomResoruces.r, add rmap record and change some of the
									other records to use the format used by the new RomLayout tool.
	   <SM2>	11/23/92	kc		Add RomBase.
*/

#include "RomTypes.r"

#include "RomResources.r"

#define RomSize		0x00100000
#define StartOfRom	0x00000000
#define EndOfRom	RomSize

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

