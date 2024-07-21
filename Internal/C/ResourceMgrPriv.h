/*
	File:		ResourceMgrPriv.h

	Contains:	C Interfaces to private Resource Manager stuff

	Written by:	Dean Yu

	Copyright:	© 1991-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<11>	 6/10/92	DTY		Add structures defining the format of a resource map.
		<10>	 5/14/92	DTY		#000000: Add interface for CloseResFileUnderSystemMap.
		 <9>	  5/8/92	DTY		#1029162: Let the caller pass in the desired permission to
									OpenResFileUnderSystemMap.
		 <8>	 1/30/92	DTY		Add defines for preventFileFromBeingClosedBit and
									preventFileFromBeingClosedMask.
		 <7>	12/17/91	DTY		Add selector for _ResolveIDConflicts.
		 <6>	 12/6/91	DTY		Add selector for _OpenResFileUnderSystemMap.
		 <5>	 11/8/91	DTY		Touch this file to force everybody to rebuild some Process
									Manager files so they get the correct selectors.
		 <4>	 11/5/91	DTY		Add interfaces for InsertFontMap, MakeOverrideMap,
									SetOverrideAttributes, GetOverrideAttributes, and
									SetScanOverride routines. Change GetMap and
									IsThisASystemResourceMap to negative selectors since these are
									really private routines.  Switch mask values for
									DontCountOrIndexDuplicates and TwoDeep to match the bit
									definitions.
		 <3>	 11/1/91	DTY		Add interface for IsThisASystemResourceMap().
		 <2>	10/23/91	DTY		Rename GetSystemOverrideMap to GetOverrideMap and let it take a
									handle parameter, and add GetMap.
		 <1>	10/23/91	DTY		first checked in
*/

#ifndef __RESOURCEMGRPRIVATE__
#define __RESOURCEMGRPRIVATE__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __FILES__
#include <Files.h>
#endif

// The resource header is the data contained in the first 16 bytes of the resource fork.
// A copy of the header can be found in the resource map in memory.

struct ResourceHeader {
	unsigned long	resourceDataOffset;				// Offset to the resource data from beginning of the file.
	unsigned long	resourceMapOffset;				// Offset to the resource map from the beginning of the file.
	unsigned long	resourceDataLength;				// Total length of resource data
	unsigned long	resourceMapLength;				// Total length of resource map.
};
typedef struct ResourceHeader ResourceHeader, *ResourceHeaderPtr;

// For each resource type in a resource file, the resource map contains a type entry
// which specifies the resource type, how many resources there are of this type, and
// the offset from the beginning of the type list to the reference list for this type

struct TypeEntry {
	ResType			tType;							// The resource type
	unsigned short	tCount;							// Number of resources of this type, minus 1
	unsigned short	tOffset;						// Offset to resource reference list for this resource type.
};
typedef struct TypeEntry TypeEntry, *TypeEntryPtr;

// For each resource in a resource file, the resource map contains a reference entry
// which specifies the resource ID, the offset to the resource’s name (if any), the
// offset to the actual resource data from the beginning of the resource data, and
// the handle to the resource data in memory, if it’s loaded.

struct ReferenceEntry {
	short			rID;							// Resource ID
	unsigned short	rNameOffset;					// Offset to resource name.  (-1 if no name)
	union {
		unsigned char	rAttr;						// Attributes for this resource
		unsigned long	rDataLocation;				// Offset from beginning of resource data to length of dadta for this resource.
	} rAttrData;
	Handle			rHandle;						// Resource handle.  (0 if resource is not loaded)
};
typedef struct ReferenceEntry ReferenceEntry, *ReferenceEntryPtr;

// The resource map describes all of the resources in a file, with a list of type entries,
// reference entries, and a list of resource names.  It also contains the file reference
// number of the resource file, and some attributes.
//
// I’ve split the resource map into two structs, the ResourceMapHeader, which contains
// information that is in an empty resource map (a resource map that contains no resources)
// and the ResourceMap proper, which contains fields which describe type entries, reference
// entries, and the name list.

struct ResourceMapHeader {
	ResourceHeader		mHeader;					// Copy of the resource header
	struct ResourceMap	**mNext;					// Handle to next resource map
	unsigned short		mRefNum;					// File reference number of this resource file
	unsigned char		mAttr;						// Map attributes (read only, compact, changed)
	unsigned char		mInMemoryAttr;				// Override attributes & decompression bit
	unsigned short		mTypes;						// Offset from start of resource map to type list (typically 0x1C)
	unsigned short		mNames;						// Offset from start of resource map to name list
};
typedef struct ResourceMapHeader ResourceMapHeader, *ResourceMapHeaderPtr, **ResourceMapHeaderHandle;

struct ResourceMap {
	ResourceMapHeader	mapHeader;					// Header information for the resource map
	unsigned short		typeCount;					// Number of resource types in this map, minus 1
	TypeEntry			typeList[0];				// Type entries for all the types in this resource file
	ReferenceEntry		referenceList[0];			// Reference entries for all resources in this file
	char				nameList[0];				// String of resource names
};
typedef struct ResourceMap ResourceMap, *ResourceMapPtr, **ResourceMapHandle;

#define	kOverrideNextMapMask			2
#define	kDontCountOrIndexDuplicatesMask	4
#define	kTwoDeepMask					8
#define	kPreventFileFromBeingClosedMask	16

pascal void		CloseResFileUnderSystemMap(short refNum)
 = {0x70FC,0xA822};
 
pascal Boolean	ResolveIDConflicts(short refNum)
 = {0x70FD,0xA822};
 
pascal short	OpenResFileUnderSystemMap(FSSpec *fileSpec, SignedByte permission)
 = {0x70FE,0xA822};
 
pascal Boolean	IsThisASystemResourceMap(Handle resourceMap)
 = {0x70FF,0xA822};
 
pascal Handle	GetMap(short refNum)
 = {0x7000,0xA822};

pascal void		MakeOverrideMap(Handle mapToOverride)
 = {0x7004,0xA822};
 
pascal void		InsertOverrideMap(Handle overrideMap, Handle mapToOverride)
 = {0x7005,0xA822};

pascal Handle	GetOverrideMap(Handle resourceMap)
 = {0x7006,0xA822}; 

pascal void		SetScanOverride(Boolean scanOverrideMap)
 = {0x7007,0xA822};

pascal SignedByte	GetOverrideAttributes(Handle resourceMap)
 = {0x7008,0xA822};

pascal void		SetOverrideAttributes(Handle resourceMap, SignedByte attributeBits)
 = {0x7009,0xA822};

#endif