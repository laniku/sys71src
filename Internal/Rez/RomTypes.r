/*
	File:		ROMTypes.r

	Contains:	The resource type declartions that are used to describe
				the layout of a ROM for the RomLayout tool.
				
				These types are duplicated in RomTypes.h

					rcod -	Rom Code		Where to place code resources.
					rdcl -	DeclData		Where to place the declaration ROM(s).
					rrhd -	Resource Header	Where to locate the ROM resource header.
					rrsc -	Resource		What rom resources to include and
											where to find them.
					rtim -	Time Stamp		Where to add a time stamp.
					rref -	Reference		Where to fixup a reference.
					rcks -	Check Sum		Where to add a check sum.
					rsiz -	Size			What size is the rom image.

	Written by:	Kurt Clark.

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM5>	  2/6/94	kc		Added 'rraa' type for absolute address rom resources.
	   <SM4>	10/26/93	kc		Add rrmp for Risc Rom Map
	   <SM3>	 3/31/93	kc		Add rmap resource type to allow the user to tell the RomLayout
									tool to print ROM maps for various resoruces. Update some of the
									other formats to work with the new RomLayout tool.
	   <SM2>	11/23/92	kc		Add RomBase.
*/

#ifndef  __RomTypes__
#define __RomTypes__
#else

#define kFormatVersion	0x01
#define kComboSize 		0x08
#define kkResourceAttr	0x58

/*
	The following macro allows us to specify filenames using 
	the format:

		{ObjDir},	<--	Shell variable for pathname.
		"Rom.Rsrc"	<-- File name.
	
*/

#define ObjDir $$shell("ObjDir")

#define RsrcDir $$shell("RsrcDir")

#define MiscDir $$shell("MiscDir")

#define TidbitsDir $$shell("TidbitsDir")

#define TextDir $$shell("TextDir")

#define filename 	begin:								\
						array [1] {						\
							string;						\
						};								\
						cstring;						\
					end:								\
					fill bit [ $800 - (end - begin) ];

#define filename2 	begin2:								\
						array [1] {						\
							string;						\
						};								\
						cstring;						\
					end2:								\
					fill bit [ $800 - (end2 - begin2) ];

#define filename3 	begin3:								\
						array [1] {						\
							string;						\
						};								\
						cstring;						\
					end3:								\
					fill bit [ $800 - (end3 - begin3) ];


/*
	Rom Code Block
*/
type 'rcod' {
	
	longint = kFormatVersion;
	
	filename;						/* Resource file name */
	
	literal longint;				/* Resource type */
	
	integer;						/* Resource id */

	longint kDynamicAddress = -1;	/* Address */
};


/*
	Declaration Rom
*/
type 'rdcl' {
	
	longint = kFormatVersion;
		
	filename;						/* Data filename */

	longint kDynamicAddress = -1;	/* Address */
};


/*
	Rom Resource Header
*/
type 'rrhd' {
	
	longint = kFormatVersion;

	longint kDynamicAddress = -1;	/* Address */

	longint;						/* Fixup Address */
};


/*
	Rom Resource
*/
type 'rrsc' {
	
	longint = kFormatVersion;

	longint;							/* Link time conditional */
	
	byte;								/* Combo bit field (first byte) */
	
	fill byte[ kComboSize - 1 ];		/* Unused combo bytes */
	
	filename;							/* Name of file containing resource */
	
	longint = $$CountOf(RsrcList);		/* Number of entries */
	
	array RsrcList {					/* Entries for ROM resources */

		literal longint;				/* Resource type */
	
		longint = $$CountOf(IDList);	/* Count of IDs */
		
		array IDList {					/* Id's of this type */
		
			integer;					/* Resource id */
		};
	};
};


/*
	Rom Resource Absolute Address
*/
type 'rraa' {
	
	longint = kFormatVersion;

	longint;							/* Link time conditional */
	
	byte;								/* Combo bit field (first byte) */
	
	fill byte[ kComboSize - 1 ];		/* Unused combo bytes */
	
	filename;							/* Name of file containing resource */
	
	literal longint;					/* Resource type */
		
	integer;							/* Resource id */

	longint kDynamicAddress;			/* Resource address */
};


/*
	Rom Time Stamp
*/
type 'rtim' {
	
	longint = kFormatVersion;

	literal longint;				/* Fixup Resource type */
	
	integer;						/* Fixup Resource id */

	longint kDynamicAddress;		/* Fixup address */
};


/*
	Rom Reference
*/
type 'rref' {
	
	longint = kFormatVersion;
	
	literal longint;				/* Referenced Resource type */
	
	integer;						/* Referenced Resource id */

	longint;						/* Referenced address */

	literal longint;				/* Fixup Resource type */
	
	integer;						/* Fixup Resource id */

	longint;						/* Fixup address */
};


/*
	Rom Check Sum
*/
type 'rcks' {
	
	longint = kFormatVersion;

	longint;						/* Starting address */
	
	longint;						/* Ending address */
	
	literal longint;				/* Fixup Resource type */
	
	integer;						/* Fixup Resource id */

	longint;						/* Slice address */

	longint;						/* Checksum address */
};


/*
	Rom Size
*/
type 'rsiz' {
	
	longint = kFormatVersion;

	longint;						/* Size */
};


/*
	Rom Base
*/
type 'rbas' {
	
	longint = kFormatVersion;

	longint;						/* Base */
};


/*
	Rom Map
*/
type 'rmap' {
	
	longint = kFormatVersion;
	
	literal longint;				/* Resource type */
	
	integer;						/* Resource id */

	filename2;						/* Name of file containing the link map */

	filename3;						/* Name of file containing the symbol table */
};


/*
	Risc Rom Map
*/
type 'rrmp' {
	
	longint = kFormatVersion;
	
	literal longint;				/* Resource type */
	
	integer;						/* Resource id */

	filename2;						/* Name of file containing the link map */
};

#endif __RomTypes__
