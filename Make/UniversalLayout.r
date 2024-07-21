/*
	File:		UniversalLayout.r

	Contains:	A generic ROM description used by the RomLayout tool to create
				a ROM image.
	
	Written by:	Kurt Clark.

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM4>	 6/14/93	kc		Bump DeclSize to 176k
	   <SM3>	 3/31/93	kc		Include RomResoruces.r, add rmap record and change some of the
									other records to use the format used by the new RomLayout tool.
	   <SM2>	  3/5/93	PN		Grow Mike Puckets DeclData size.
	   <SM3>	12-04-92	jmp		Added a 'rdcl' resource for the VSC (Keystone) DeclData.
	   <SM2>	11/23/92	kc		Add RomBase.
*/

#include "RomTypes.r"

#include "RomResources.r"

#define RomSize		0x00200000
#define StartOfRom	0x00000000
#define EndOfRom	RomSize

#if 0	This is a hack for BlackBird that will go away when we get Mike's new virtual slot manager

#define VSCBoundry	0x00002000				/* The VSC DeclData must be on an 8K boundry. 	*/
#define DeclSize	(VSCBoundry*22)			/* Give DeclData 176K for now.			 		*/
#define EndOfVSC	(RomSize-DeclSize)		/* Where VSCDeclData lives.						*/

#endif

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

resource 'rdcl' (128, "DeclData") {

	{RsrcDir},			/* Path Name */
	
	"DeclData",			/* File Name */
	
	EndOfRom			/* ROM Address */
};

#if 0

resource 'rdcl' (129, "VSC DeclData") {

	{RsrcDir},			/* Path Name */
	
	"VSCDeclData",		/* File Name */
	
	EndOfVSC			/* ROM Address */
};

#endif

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

