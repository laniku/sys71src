/*
	File:		RomLayout.r

	Contains:	This file describes the layout of the DBLite ROM.
	
	Written by:	Kurt Clark.

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM4>	12/13/93	PN		Roll in KAOs and Horror changes to support Malcom and AJ
									machines. This is a make file for 603 PowerBook.
	   <SM3>	  9/1/93	SKH		Commented out the rref #128, because none of the other ROMs have one.
	   								It doesn't seem to be needed anymore.
	   <SM2>	 3/31/93	kc		Include RomResoruces.r, add rmap record and change some of the
									other records to use the format used by the new RomLayout tool.
	   <SM1>	 2/22/93	CSS		Fixed to work with new location of build stuff.
	   <SM1>	 2/11/93	CSS		Checkin work done by Ricardo and Kurt for dbLite support.
	   <SM2>	11/23/92	kc		Add RomBase.
*/

#include "RomTypes.r"

#include "RomResources.r"

#define RomSize		0x00300000
#define StartOfRom	0x00000000
#define EndOfRom	RomSize
#define	EndOfSlotE	0x002e0000

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

resource 'rcod' (129, "VSCDecl Data") {

	{RsrcDir},			/* Path Name */
	
	"VSCDriver.rsrc",	/* File Name */
	
	'decl',				/* Resource Type */  
	
	1,					/* Resource ID */
	
	-EndOfSlotE			/* ROM Address */
};

resource 'rdcl' (129, "Decl Data") {

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

#if 0
resource 'rref' (128, "Address to ROM rsrc header") {
	
	"Resource Header",	/* Referenced name */

	0x00000000,			/* Referenced address */

	"Main Code Image",	/* Fixup name */

	0x0000001A;			/* Fixup address */
};
#endif

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

