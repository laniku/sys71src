{
	File:		Dictionary.p

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <2>	10/22/92	KST		Make the .p file consistent with .h file per technical writer's
									request.
		 <1>	 5/27/92	hsK		first checked in

}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Dictionary;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingDictionary}
{$SETC UsingDictionary := 1}

{$I+}
{$SETC DictionaryIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingFiles}
{$I $$Shell(PInterfaces)Files.p}
{$ENDC}
{$SETC UsingIncludes := DictionaryIncludes}

CONST

{ Dictionary data insertion modes }	
kInsert 				= 	0;			{Only insert the input entry if there is nothing in the dictionary that matches the key.}
kReplace 				= 	1;			{Only replace the entries which match the key with the input entry.}
kInsertOrReplace 		= 	2;			{Insert the entry if there is nothing in the dictionary which matches the key.}
										{If there is already matched entries, replace the existing matched entries with the input entry.}

{ Key attribute constants }
kIsCaseSensitive			=	$10;	{case sensitive = 16}
kIsNotDiacriticalSensitive	=	$20;	{diac not sensitive = 32}


{ Registered attribute type constants }
kNoun					=	-1;
kVerb					=	-2;
kAdjective				=	-3;
kAdverb					=	-4;


TYPE

InsertMode		= INTEGER;				{#2}
AttributeType	= INTEGER;				{#2}


{ Dictionary information record }
DictionaryInformation = RECORD
	dictionaryFSSpec: FSSpec;
 	numberOfRecords: LONGINT;
 	currentGarbageSize: LONGINT;
 	script: ScriptCode;
 	maximumKeyLength: INTEGER;
 	keyAttributes: Byte;
	END;
	
{ Dictionary Manager routines }
FUNCTION InitializeDictionary( 	theFsspecPtr: FSSpecPtr;
								maximumKeyLength: INTEGER;
								keyAttributes: Byte;
								script: ScriptCode): OSErr;
 INLINE $303C,$0500,$AA53;

FUNCTION OpenDictionary( 	theFsspecPtr: FSSpecPtr;
							accessPermission: SignedByte;
							VAR dictionaryReference: LONGINT): OSErr;
 INLINE $303C,$0501,$AA53;

FUNCTION CloseDictionary( dictionaryReference: LONGINT): OSErr;
 INLINE $303C,$0202,$AA53;

FUNCTION InsertRecordToDictionary( 	dictionaryReference: LONGINT;
									key: Str255;
									recordDataHandle: Handle;
									whichMode: InsertMode): OSErr;			{#2}
 INLINE $303C,$0703,$AA53;

FUNCTION DeleteRecordFromDictionary( 	dictionaryReference: LONGINT;
										key: Str255): OSErr;
 INLINE $303C,$0404,$AA53;

FUNCTION FindRecordInDictionary( 	dictionaryReference: LONGINT;
									key: Str255;
									requestedAttributeTablePointer: Ptr;
									recordDataHandle: Handle): OSErr;
 INLINE $303C,$0805,$AA53;

FUNCTION FindRecordByIndexInDictionary( dictionaryReference: LONGINT;
										recordIndex: LONGINT;
										requestedAttributeTablePointer: Ptr;
										VAR recordKey: Str255;
										recordDataHandle: Handle): OSErr;
 INLINE $303C,$0A06,$AA53;

FUNCTION GetDictionaryInformation( 	dictionaryReference: LONGINT;
									VAR theDictionaryInformation: DictionaryInformation): OSErr;
 INLINE $303C,$0407,$AA53;

FUNCTION CompactDictionary( dictionaryReference: LONGINT): OSErr;
 INLINE $303C,$0208,$AA53;



{$ENDC} { UsingDictionary }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}


