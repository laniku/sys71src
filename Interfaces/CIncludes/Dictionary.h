/*
	File:		Dictionary.h

	Written by:	Hae-Sung Kim

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <2>	  6/3/92	DCL		Cleanup to meet Interface Standards.
		 <1>	 5/27/92	hsK		first checked in

*/

#ifndef __DICTIONARY__
#define __DICTIONARY__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __FILES__
#include <Files.h>
#endif

/*------------------------------------------------------------------------------------------
	Constant definitions.
------------------------------------------------------------------------------------------ */

/* Dictionary data insertion modes. */

enum {
 kInsert = 0,			/* Only insert the input entry if there is nothing in the dictionary that matches the key. */
 kReplace = 1,			/* Only replace the entries which match the key with the input entry. */
 kInsertOrReplace = 2	/* Insert the entry if there is nothing in the dictionary which matches the key. */
						/* If there is already matched entries, replace the existing matched entries with the input entry. */
};
typedef short InsertMode;

/* Key attribute constants.		*/

#define		kIsCaseSensitive			0x10		/* case sensitive = 16		*/
#define		kIsNotDiacriticalSensitive	0x20		/* diac not sensitive = 32	*/

/* Registered attribute type constants.	*/

enum {
 kNoun		=	-1,
 kVerb		=	-2,
 kAdjective	=	-3,
 kAdverb	=	-4
};
typedef short AttributeType;

/* ------------------------------------------------------------------------------------------

	Type definitions.

------------------------------------------------------------------------------------------ */

/* Dictionary information record.	*/

struct DictionaryInformation{
	FSSpec			dictionaryFSSpec;
	long			numberOfRecords;
	long			currentGarbageSize;
	ScriptCode		script;	
	short			maximumKeyLength;
	unsigned char	keyAttributes;
};

typedef struct DictionaryInformation DictionaryInformation;



/* --------------------------------------------------------------------------------------

	Function ProtoTypes.

-------------------------------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

pascal OSErr InitializeDictionary(FSSpecPtr theFsspecPtr, short maximumKeyLength, 
 unsigned char keyAttributes, ScriptCode script )
= { 0x303C,0x0500,0xAA53 };

pascal OSErr OpenDictionary( FSSpecPtr theFsspecPtr,
 char accessPermission,
 long *dictionaryReference )
= { 0x303C,0x0501,0xAA53 };

pascal OSErr CloseDictionary( long dictionaryReference )
= { 0x303C,0x0202,0xAA53 };
 
pascal OSErr InsertRecordToDictionary( long dictionaryReference, 
 ConstStr255Param key, 
 Handle recordDataHandle, 
 InsertMode whichMode )
= { 0x303C,0x0703,0xAA53 };

pascal OSErr DeleteRecordFromDictionary( long dictionaryReference, 
 ConstStr255Param key )
= { 0x303C,0x0404,0xAA53 };
 
pascal OSErr FindRecordInDictionary( long dictionaryReference, 
 ConstStr255Param key, 
 Ptr requestedAttributeTablePointer, 
 Handle recordDataHandle )
= { 0x303C,0x0805,0xAA53 };

pascal OSErr FindRecordByIndexInDictionary( long dictionaryReference, 
 long recordIndex, 
 Ptr requestedAttributeTablePointer, 
 Str255 recordKey,
 Handle recordDataHandle )
= { 0x303C,0x0A06,0xAA53 };

pascal OSErr GetDictionaryInformation( long dictionaryReference,
 DictionaryInformation *theDictionaryInformation)
= { 0x303C,0x0407,0xAA53 };

pascal OSErr CompactDictionary( long dictionaryReference )
= { 0x303C,0x0208,0xAA53 };

#ifdef __cplusplus
}
#endif

#endif __Dictionary__