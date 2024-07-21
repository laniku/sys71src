{
	File:		TextUtils.p
	 Pascal Interface to the Macintosh Libraries

	Copyright:	© 1985-1992 by Apple Computer, Inc.
	All rights reserved.

	Change History (most recent first):

		<14>	10/16/92	PKE		For new IM: Change reserved field name in NBreakTable to length,
									reflecting its real usage.
		<13>	 6/26/92	DCL		Miner Formatting Changes. Digging deep for things to do. Getting
									the file ready for ETO 8.
		<12>	 5/29/92	DCL		Moved DateTime stuff to OSUtils and Intl stuff to IntlResources
		<11>	  5/7/92	DCL		NIIM: Movin date & time Stuff from DateTime to TextUtils.
		<10>	  5/6/92	DCL		NIIM: Moved KeyTrans back from TextUtils to Events.
		 <9>	  5/5/92	DCL		For New Inside Mac: removing 'sc' prefixes from some calls,
									moving some calls from script to TextUtils, and moving some from
									TextUtils & QuickDraw to QuickdrawText. Weeeeeeee!
		 <8>	 4/17/92	DCL		For New Inside Mac: Mo' Better Call Names. Str -> String, Secs
									-> Seconds. Sorry, no more Secs.
		 <7>	 4/15/92	DCL		For New Inside Mac: Moved StyledLineBreakCode from script to
									TextUtils.
		 <6>	 4/15/92	DCL		For New Inside Mac: Moved many definitions from Script to
									TextUtils and QuickDraw. And added new synonyms. #1025005
		 <5>	  4/6/92	DCL		For New Inside Mac: Moved declarations from Script.[aph] to
									TextUtils.[aph]. #1025005
		 <4>	  4/1/92	DCL		Fix the calls from xxxxIntlxxxx to xxxxxxxxxIntl.
		 <3>	 3/30/92	DCL		New Improved Names for New Improved Inside Mac.
		<2+>	 3/26/92	DCL	For New Inside Mac:  Added New Improved Better Names for the
									same old calls.  #1025005
		 <2>	 3/26/92	DCL	For New IM: Moved many declarations and routines from
									Packages.[ph] to TextUtils.[ph]
		 <1>	 3/12/92	DCL	first checked in

}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT TextUtils;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingTextUtils}
{$SETC UsingTextUtils := 1}

{$I+}
{$SETC TextUtilsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingScript}
{$I $$Shell(PInterfaces)Script.p}
{$ENDC}
{$IFC UNDEFINED UsingOSUtils}
{$I $$Shell(PInterfaces)OSUtils.p}
{$ENDC}
{$SETC UsingIncludes := TextUtilsIncludes}

CONST

{ Constants for truncWhere argument in TruncString and TruncText }

truncEnd = 0;									{ Truncate at end }
truncMiddle = $4000;							{ Truncate in middle }
smTruncEnd = 0;									{ Truncate at end    obsolete }
smTruncMiddle = $4000;							{ Truncate in middle     obsolete }

{ Constants for TruncString and TruncText results }

notTruncated = 0;								{ No truncation was necessary }
truncated = 1;									{ Truncation performed }
truncErr = -1;									{ General error }
smNotTruncated = 0;								{ No truncation was necessary obsolete }
smTruncated = 1;								{ Truncation performed    obsolete }
smTruncErr = -1;								{ General error      obsolete }

fVNumber = 0;									{first version of NumFormatString}

{ String2Date status values }

fatalDateTime = $8000;							{String2Date and String2Time mask to a fatal error}
longDateFound = 1;								{String2Date mask to long date found}
leftOverChars = 2;								{String2Date & Time mask to warn of left over characters}
sepNotIntlSep = 4;								{String2Date & Time mask to warn of non-standard separators}
fieldOrderNotIntl = 8;							{String2Date & Time mask to warn of non-standard field order}
extraneousStrings = 16;							{String2Date & Time mask to warn of unparsable strings in text}
tooManySeps = 32;								{String2Date & Time mask to warn of too many separators}
sepNotConsistent = 64;							{String2Date & Time mask to warn of inconsistent separators}
tokenErr = $8100;								{String2Date & Time mask for 'tokenizer err encountered'}
cantReadUtilities = $8200;
dateTimeNotFound = $8400;
dateTimeInvalid = $8800;


{ Special language code values for Language Order }

systemCurLang = -2;								{ current (itlbLang) lang for system script }
systemDefLang = -3;								{ default (table) lang for system script }
currentCurLang = -4;							{ current (itlbLang) lang for current script }
currentDefLang = -5;							{ default lang for current script }
scriptCurLang = -6;								{ current (itlbLang) lang for specified script }
scriptDefLang = -7;								{ default language for a specified script }
iuSystemCurLang = -2;							{ <obsolete> current (itlbLang) lang for system script }
iuSystemDefLang = -3;							{ <obsolete> default (table) lang for system script }
iuCurrentCurLang = -4;							{ <obsolete> current (itlbLang) lang for current script }
iuCurrentDefLang = -5;							{ <obsolete> default lang for current script }
iuScriptCurLang = -6;							{ <obsolete> current (itlbLang) lang for specified script }
iuScriptDefLang = -7;							{ <obsolete> default language for a specified script }


TYPE
StyledLineBreakCode = (smBreakWord,smBreakChar,smBreakOverflow);

FormatClass = (fPositive,fNegative,fZero);

FormatResultType = (fFormatOK,fBestGuess,fOutOfSynch,fSpuriousChars,fMissingDelimiter,
 fExtraDecimal,fMissingLiteral,fExtraExp,fFormatOverflow,fFormStrIsNAN,
 fBadPartsTable,fExtraPercent,fExtraSeparator,fEmptyFormatString);


NumFormatString = PACKED RECORD
 fLength: Byte;
 fVersion: Byte;
 data: PACKED ARRAY [0..253] OF SignedByte;		{private data}
 END;


NumFormatStringRec = NumFormatString;

FVector = RECORD
 start: INTEGER;
 length: INTEGER;
 END;


TripleInt = ARRAY [0..2] OF FVector;			{ index by [fPositive..fZero] }

ScriptRunStatus = RECORD
 script: SignedByte;
 variant: SignedByte;
 END;


{ New types for System 7.0:                
  type for truncWhere parameter in new TruncString, TruncText }

TruncCode = INTEGER;

DateForm = (shortDate,longDate,abbrevDate);


StringToDateStatus = INTEGER;
String2DateStatus = INTEGER;

DateCachePtr = ^DateCacheRecord;
DateCacheRecord = PACKED RECORD
 hidden: ARRAY [0..255] OF INTEGER;				{only for temporary use}
 END;

BreakTablePtr = ^BreakTable;
BreakTable = RECORD
 charTypes: ARRAY [0..255] OF SignedByte;
 tripleLength: INTEGER;
 triples: ARRAY [0..0] OF INTEGER;
 END;

NBreakTablePtr = ^NBreakTable;
NBreakTable = RECORD
 flags1: SignedByte;
 flags2: SignedByte;
 version: INTEGER;
 classTableOff: INTEGER;
 auxCTableOff: INTEGER;
 backwdTableOff: INTEGER;
 forwdTableOff: INTEGER;
 doBackup: INTEGER;
 length: INTEGER;								{length of NBreakTable}			{<14>}
 charTypes: ARRAY [0..255] OF SignedByte;
 tables: ARRAY [0..0] OF INTEGER;
 END;


PROCEDURE IUDateString(dateTime: LONGINT;longFlag: DateForm;VAR result: Str255);
 INLINE $4267,$A9ED;
PROCEDURE DateString(dateTime: LONGINT;longFlag: DateForm;VAR result: Str255;
 intlHandle: Handle);
 INLINE $3F3C,$000E,$A9ED;
PROCEDURE IUDatePString(dateTime: LONGINT;longFlag: DateForm;VAR result: Str255;
 intlHandle: Handle);
 INLINE $3F3C,$000E,$A9ED;
PROCEDURE IUTimeString(dateTime: LONGINT;wantSeconds: BOOLEAN;VAR result: Str255);
 INLINE $3F3C,$0002,$A9ED;
PROCEDURE TimeString(dateTime: LONGINT;wantSeconds: BOOLEAN;VAR result: Str255;
 intlHandle: Handle);
 INLINE $3F3C,$0010,$A9ED;
PROCEDURE IUTimePString(dateTime: LONGINT;wantSeconds: BOOLEAN;VAR result: Str255;
 intlHandle: Handle);
 INLINE $3F3C,$0010,$A9ED;
PROCEDURE LongDateString(VAR dateTime: LongDateTime;longFlag: DateForm;
 VAR result: Str255;intlHandle: Handle);
 INLINE $3F3C,$0014,$A9ED;
PROCEDURE IULDateString(VAR dateTime: LongDateTime;longFlag: DateForm;VAR result: Str255;
 intlHandle: Handle);
 INLINE $3F3C,$0014,$A9ED;
PROCEDURE LongTimeString(VAR dateTime: LongDateTime;wantSeconds: BOOLEAN;
 VAR result: Str255;intlHandle: Handle);
 INLINE $3F3C,$0016,$A9ED;
PROCEDURE IULTimeString(VAR dateTime: LongDateTime;wantSeconds: BOOLEAN;
 VAR result: Str255;intlHandle: Handle);
 INLINE $3F3C,$0016,$A9ED;
FUNCTION InitDateCache(theCache: DateCachePtr): OSErr;
 INLINE $2F3C,$8204,$FFF8,$A8B5;
FUNCTION StringToDate(textPtr: Ptr;textLen: LONGINT;theCache: DateCachePtr;
 VAR lengthUsed: LONGINT;VAR dateTime: LongDateRec): StringToDateStatus;
 INLINE $2F3C,$8214,$FFF6,$A8B5;
FUNCTION String2Date(textPtr: Ptr;textLen: LONGINT;theCache: DateCachePtr;
 VAR lengthUsed: LONGINT;VAR dateTime: LongDateRec): String2DateStatus;
 INLINE $2F3C,$8214,$FFF6,$A8B5;
FUNCTION StringToTime(textPtr: Ptr;textLen: LONGINT;theCache: DateCachePtr;
 VAR lengthUsed: LONGINT;VAR dateTime: LongDateRec): StringToDateStatus;
 INLINE $2F3C,$8214,$FFF4,$A8B5;
FUNCTION String2Time(textPtr: Ptr;textLen: LONGINT;theCache: DateCachePtr;
 VAR lengthUsed: LONGINT;VAR dateTime: LongDateRec): String2DateStatus;
 INLINE $2F3C,$8214,$FFF4,$A8B5;

FUNCTION EqualString(str1: Str255;str2: Str255;caseSens: BOOLEAN;diacSens: BOOLEAN): BOOLEAN;
PROCEDURE UpperString(VAR theString: Str255;diacSens: BOOLEAN);
PROCEDURE UprString(VAR theString: Str255;diacSens: BOOLEAN);
FUNCTION RelString(str1: Str255;str2: Str255;caseSens: BOOLEAN;diacSens: BOOLEAN): INTEGER;

FUNCTION GetString(stringID: INTEGER): StringHandle;
 INLINE $A9BA;
FUNCTION Munger(h: Handle;offset: LONGINT;ptr1: Ptr;len1: LONGINT;ptr2: Ptr;
 len2: LONGINT): LONGINT;
 INLINE $A9E0;
PROCEDURE SetString(theString: StringHandle;strNew: Str255);
 INLINE $A907;
FUNCTION NewString(theString: Str255): StringHandle;
 INLINE $A906;
PROCEDURE GetIndString(VAR theString: Str255;strListID: INTEGER;index: INTEGER);


{ The next four calls will be obsolete.  Use the similar Pstring call and pass a NIL handle. }
FUNCTION IUMagString(aPtr: Ptr;bPtr: Ptr;aLen: INTEGER;bLen: INTEGER): INTEGER;
 INLINE $3F3C,$000A,$A9ED;
FUNCTION IUMagIDString(aPtr: Ptr;bPtr: Ptr;aLen: INTEGER;bLen: INTEGER): INTEGER;
 INLINE $3F3C,$000C,$A9ED;
FUNCTION IUCompString(aStr: Str255;bStr: Str255): INTEGER;
FUNCTION IUEqualString(aStr: Str255;bStr: Str255): INTEGER;

PROCEDURE StringToNum(theString: Str255;VAR theNum: LONGINT);
PROCEDURE NumToString(theNum: LONGINT;VAR theString: Str255);

FUNCTION CompareText(aPtr: Ptr;bPtr: Ptr;aLen: INTEGER;bLen: INTEGER;itl2Handle: Handle): INTEGER;
 INLINE $3F3C,$001A,$A9ED;
FUNCTION IUMagPString(aPtr: Ptr;bPtr: Ptr;aLen: INTEGER;bLen: INTEGER;itl2Handle: Handle): INTEGER;
 INLINE $3F3C,$001A,$A9ED;
FUNCTION IdenticalText(aPtr: Ptr;bPtr: Ptr;aLen: INTEGER;bLen: INTEGER;
 itl2Handle: Handle): INTEGER;
 INLINE $3F3C,$001C,$A9ED;
FUNCTION IUMagIDPString(aPtr: Ptr;bPtr: Ptr;aLen: INTEGER;bLen: INTEGER;
 itl2Handle: Handle): INTEGER;
 INLINE $3F3C,$001C,$A9ED;
FUNCTION CompareString(aStr: Str255;bStr: Str255;itl2Handle: Handle): INTEGER;
FUNCTION IUCompPString(aStr: Str255;bStr: Str255;itl2Handle: Handle): INTEGER;
FUNCTION IdenticalString(aStr: Str255;bStr: Str255;itl2Handle: Handle): INTEGER;
FUNCTION IUEqualPString(aStr: Str255;bStr: Str255;itl2Handle: Handle): INTEGER;
FUNCTION ScriptOrder(script1: ScriptCode;script2: ScriptCode): INTEGER;
 INLINE $3F3C,$001E,$A9ED;
FUNCTION IUScriptOrder(script1: ScriptCode;script2: ScriptCode): INTEGER;
 INLINE $3F3C,$001E,$A9ED;
FUNCTION LanguageOrder(language1: LangCode;language2: LangCode): INTEGER;
 INLINE $3F3C,$0020,$A9ED;
FUNCTION IULangOrder(language1: LangCode;language2: LangCode): INTEGER;
 INLINE $3F3C,$0020,$A9ED;
FUNCTION TextOrder(aPtr: Ptr;bPtr: Ptr;aLen: INTEGER;bLen: INTEGER;aScript: ScriptCode;
 bScript: ScriptCode;aLang: LangCode;bLang: LangCode): INTEGER;
 INLINE $3F3C,$0022,$A9ED;
FUNCTION IUTextOrder(aPtr: Ptr;bPtr: Ptr;aLen: INTEGER;bLen: INTEGER;aScript: ScriptCode;
 bScript: ScriptCode;aLang: LangCode;bLang: LangCode): INTEGER;
 INLINE $3F3C,$0022,$A9ED;
FUNCTION StringOrder(aStr: Str255;bStr: Str255;aScript: ScriptCode;bScript: ScriptCode;
 aLang: LangCode;bLang: LangCode): INTEGER;
FUNCTION IUStringOrder(aStr: Str255;bStr: Str255;aScript: ScriptCode;bScript: ScriptCode;
 aLang: LangCode;bLang: LangCode): INTEGER;

PROCEDURE FindWord(textPtr: Ptr;textLength: INTEGER;offset: INTEGER;leadingEdge: BOOLEAN;
 breaks: BreakTablePtr;VAR offsets: OffsetTable);
 INLINE $2F3C,$8012,$001A,$A8B5;

PROCEDURE FindWordBreaks(textPtr: Ptr;textLength: INTEGER;offset: INTEGER;
 leadingEdge: BOOLEAN;breaks: BreakTablePtr;VAR offsets: OffsetTable;script: ScriptCode);
 INLINE $2F3C,$C012,$001A,$A8B5;

PROCEDURE UprText(textPtr: Ptr;len: INTEGER);
 INLINE $301F,$205F,$A054;
PROCEDURE LwrText(textPtr: Ptr;len: INTEGER);
 INLINE $301F,$205F,$A056;


{   New for 7.0  
 }
PROCEDURE LowerText(textPtr: Ptr;len: INTEGER);
 INLINE $301F,$205F,$A056;
PROCEDURE StripText(textPtr: Ptr;len: INTEGER);
 INLINE $301F,$205F,$A256;
PROCEDURE UpperText(textPtr: Ptr;len: INTEGER);
 INLINE $301F,$205F,$A456;
PROCEDURE StripUpperText(textPtr: Ptr;len: INTEGER);
 INLINE $301F,$205F,$A656;

FUNCTION StyledLineBreak(textPtr: Ptr;textLen: LONGINT;textStart: LONGINT;
 textEnd: LONGINT;flags: LONGINT;VAR textWidth: Fixed;VAR textOffset: LONGINT): StyledLineBreakCode;
 INLINE $2F3C,$821C,$FFFE,$A8B5;

FUNCTION StringToFormatRec(inString: Str255;partsTable: NumberParts;VAR outString: NumFormatString): FormatStatus;
 INLINE $2F3C,$820C,$FFEC,$A8B5;
FUNCTION Str2Format(inString: Str255;partsTable: NumberParts;VAR outString: NumFormatString): FormatStatus;
 INLINE $2F3C,$820C,$FFEC,$A8B5;
FUNCTION FormatRecToString(myCanonical: NumFormatString;partsTable: NumberParts;
 VAR outString: Str255;VAR positions: TripleInt): FormatStatus;
 INLINE $2F3C,$8210,$FFEA,$A8B5;
FUNCTION Format2Str(myCanonical: NumFormatString;partsTable: NumberParts;
 VAR outString: Str255;VAR positions: TripleInt): FormatStatus;
 INLINE $2F3C,$8210,$FFEA,$A8B5;
FUNCTION ExtendedToString(x: Extended80;myCanonical: NumFormatString;partsTable: NumberParts;
 VAR outString: Str255): FormatStatus;
 INLINE $2F3C,$8210,$FFE8,$A8B5;
FUNCTION FormatX2Str(x: Extended80;myCanonical: NumFormatString;partsTable: NumberParts;
 VAR outString: Str255): FormatStatus;
 INLINE $2F3C,$8210,$FFE8,$A8B5;
FUNCTION StringToExtended(source: Str255;myCanonical: NumFormatString;partsTable: NumberParts;
 VAR x: Extended80): FormatStatus;
 INLINE $2F3C,$8210,$FFE6,$A8B5;
FUNCTION FormatStr2X(source: Str255;myCanonical: NumFormatString;partsTable: NumberParts;
 VAR x: Extended80): FormatStatus;
 INLINE $2F3C,$8210,$FFE6,$A8B5;

FUNCTION FindScriptRun(textPtr: Ptr;textLen: LONGINT;VAR lenUsed: LONGINT): ScriptRunStatus;
 INLINE $2F3C,$820C,$0026,$A8B5;

PROCEDURE NFindWord(textPtr: Ptr;textLength: INTEGER;offset: INTEGER;leadingEdge: BOOLEAN;
 nbreaks: NBreakTablePtr;VAR offsets: OffsetTable);
 INLINE $2F3C,$8012,$FFE2,$A8B5;
FUNCTION TruncString(width: INTEGER;VAR theString: Str255;truncWhere: TruncCode): INTEGER;
 INLINE $2F3C,$8208,$FFE0,$A8B5;
FUNCTION TruncText(width: INTEGER;textPtr: Ptr;VAR length: INTEGER;truncWhere: TruncCode): INTEGER;
 INLINE $2F3C,$820C,$FFDE,$A8B5;
FUNCTION ReplaceText(baseText: Handle;substitutionText: Handle;key: Str15): INTEGER;
 INLINE $2F3C,$820C,$FFDC,$A8B5;

PROCEDURE LowercaseText(textPtr: Ptr;len: INTEGER;script: ScriptCode);
 INLINE $3F3C,$0000,$2F3C,$800A,$FFB6,$A8B5;
PROCEDURE StripDiacritics(textPtr: Ptr;len: INTEGER;script: ScriptCode);
 INLINE $3F3C,$0200,$2F3C,$800A,$FFB6,$A8B5;
PROCEDURE UppercaseText(textPtr: Ptr;len: INTEGER;script: ScriptCode);
 INLINE $3F3C,$0400,$2F3C,$800A,$FFB6,$A8B5;
PROCEDURE UppercaseStripDiacritics(textPtr: Ptr;len: INTEGER;script: ScriptCode);
 INLINE $3F3C,$0600,$2F3C,$800A,$FFB6,$A8B5;


{$ENDC} { UsingTextUtils }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

