{
	File:		IntlResources.p
	 Pascal Interface to the Macintosh Libraries

	Copyright:	© 1983-1992 by Apple Computer, Inc.
	All rights reserved.

	Change History (most recent first):

		 <4>	10/16/92	PKE		For New IM: Add timeCycle constants and Itl1ExtRec.
		 <3>	 6/26/92	DCL		Miner Formatting Changes. Digging deep for things to do. Getting
									the file ready for ETO 8.
		 <2>	 5/29/92	DCL		Moved int0, itl3 & itl4 resource constants from TextUtils and
									Script.
		 <1>	  5/5/92	DCL		first checked in

}



{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT IntlResources;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingIntlResources}
{$SETC UsingIntlResources := 1}

{$I+}
{$SETC IntlResourcesIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := IntlResourcesIncludes}

CONST

{ Bits in the itlcFlags byte.}
itlcShowIcon = 7;											{Show icon even if only one script}
itlcDualCaret = 6;											{Use dual caret for mixed direction text}

{ Bits in the itlcSysFlags word.}
itlcSysDirection = 15;										{System direction - left to right/right to left}

{ the NumberParts indices }
tokLeftQuote = 1;
tokRightQuote = 2;
tokLeadPlacer = 3;
tokLeader = 4;
tokNonLeader = 5;
tokZeroLead = 6;
tokPercent = 7;
tokPlusSign = 8;
tokMinusSign = 9;
tokThousands = 10;
tokSeparator = 12;											{11 is a reserved field}
tokEscape = 13;
tokDecPoint = 14;
tokEPlus = 15;
tokEMinus = 16;
tokMaxSymbols = 31;

curNumberPartsVersion = 1;									{current version of NumberParts record}

currSymLead = 16;
currNegSym = 32;
currTrailingZ = 64;
currLeadingZ = 128;

timeCycle24 = 0;											{ time sequence 0:00 - 23:59 }					{<4>}
timeCycleZero = 1;											{ time sequence 0:00-11:59, 0:00 - 11:59 }		{<4>}
timeCycle12 = 255;											{ time sequence 12:00 - 11:59, 12:00 - 11:59 }	{<4>}

zeroCycle = 1;												{old name for timeCycleZero}


longDay = 0;												{day of the month}
longWeek = 1;												{day of the week}
longMonth = 2;												{month of the year}
longYear = 3;												{year}
supDay = 1;													{suppress day of month}
supWeek = 2;												{suppress day of week}
supMonth = 4;												{suppress month}
supYear = 8;												{suppress year}
dayLdingZ = 32;
mntLdingZ = 64;
century = 128;
secLeadingZ = 32;
minLeadingZ = 64;
hrLeadingZ = 128;

{ Date Orders }
mdy = 0;
dmy = 1;
ymd = 2;
myd = 3;
dym = 4;
ydm = 5;



TYPE

OffPair = RECORD
    offFirst: INTEGER;
    offSecond: INTEGER;
    END;


OffsetTable = ARRAY [0..2] OF OffPair;


Intl0Ptr = ^Intl0Rec;
Intl0Hndl = ^Intl0Ptr;
Intl0Rec = PACKED RECORD
    decimalPt: CHAR;										{decimal point character}
    thousSep: CHAR;											{thousands separator character}
    listSep: CHAR;											{list separator character}
    currSym1: CHAR;											{currency symbol}
    currSym2: CHAR;
    currSym3: CHAR;
    currFmt: Byte;											{currency format flags}
    dateOrder: Byte;										{order of short date elements: mdy, dmy, etc.}
    shrtDateFmt: Byte;										{format flags for each short date element}
    dateSep: CHAR;											{date separator character}
    timeCycle: Byte;										{time cycle: 0=>0..23, 1=>0..11, 255=> 1..12}
    timeFmt: Byte;											{format flags for each time element}
    mornStr: PACKED ARRAY [1..4] OF CHAR;					{trailing string for AM if 12-hour cycle}
    eveStr: PACKED ARRAY [1..4] OF CHAR;					{trailing string for PM if 12-hour cycle}
    timeSep: CHAR;											{time separator character}
    time1Suff: CHAR;										{trailing string for AM if 24-hour cycle}
    time2Suff: CHAR;
    time3Suff: CHAR;
    time4Suff: CHAR;
    time5Suff: CHAR;										{trailing string for PM if 24-hour cycle}
    time6Suff: CHAR;
    time7Suff: CHAR;
    time8Suff: CHAR;
    metricSys: Byte;										{255 if metric, 0 if inches etc.}
    intl0Vers: INTEGER;										{region code (hi byte) and version (lo byte)}
    END;

Intl1Ptr = ^Intl1Rec;
Intl1Hndl = ^Intl1Ptr;
Intl1Rec = PACKED RECORD
    days: ARRAY [1..7] OF Str15;							{day names}
    months: ARRAY [1..12] OF Str15;							{month names}
    suppressDay: Byte;										{255 for no day, or flags to suppress any element}
    lngDateFmt: Byte;										{order of long date elements}
    dayLeading0: Byte;										{255 for leading 0 in day number}
    abbrLen: Byte;											{length for abbreviating names}
    st0: PACKED ARRAY [1..4] OF CHAR;						{separator strings for long date format}
    st1: PACKED ARRAY [1..4] OF CHAR;
    st2: PACKED ARRAY [1..4] OF CHAR;
    st3: PACKED ARRAY [1..4] OF CHAR;
    st4: PACKED ARRAY [1..4] OF CHAR;
    intl1Vers: INTEGER;										{region code (hi byte) and version (lo byte)}
    localRtn: ARRAY [0..0] OF INTEGER;						{now a flag for opt extension}
    END;

Itl1ExtRec = RECORD											{fields for optional itl1 extension}	{<4>}
	base: Intl1Rec;											{un-extended Intl1Rec}
	version: INTEGER;
	format: INTEGER;
	calendarCode: INTEGER;									{calendar code for this itl1 resource}
	extraDaysTableOffset: LONGINT;							{offset in itl1 to extra days table}
	extraDaysTableLength: LONGINT;							{length of extra days table}
	extraMonthsTableOffset: LONGINT;						{offset in itl1 to extra months table}
	extraMonthsTableLength: LONGINT;						{length of extra months table}
	abbrevDaysTableOffset: LONGINT;							{offset in itl1 to abbrev days table}
	abbrevDaysTableLength: LONGINT;							{length of abbrev days table}
	abbrevMonthsTableOffset: LONGINT;						{offset in itl1 to abbrev months table}
	abbrevMonthsTableLength: LONGINT;						{length of abbrev months table}
	extraSepsTableOffset: LONGINT;							{offset in itl1 to extra seps table}
	extraSepsTableLength: LONGINT;							{length of extra seps table}
	tables: ARRAY [0..0] OF INTEGER;						{the tables; variable-length}
	END;

UntokenTablePtr = ^UntokenTable;
UntokenTableHandle = ^UntokenTablePtr;
UntokenTable = RECORD
    len: INTEGER;
    lastToken: INTEGER;
    index: ARRAY [0..255] OF INTEGER;						{index table; last = lastToken}
    END;



WideChar = RECORD
    CASE BOOLEAN OF
      TRUE:
        (a: PACKED ARRAY [0..1] OF CHAR);					{0 is the high order character}
      FALSE:
        (b: INTEGER);
    END;

WideCharArr = RECORD
    size: INTEGER;
    data: PACKED ARRAY [0..9] OF WideChar;
    END;

NumberPartsPtr = ^NumberParts;
NumberParts = RECORD
    version: INTEGER;
    data: ARRAY [1..31] OF WideChar;						{index by [tokLeftQuote..tokMaxSymbols]}
    pePlus: WideCharArr;
    peMinus: WideCharArr;
    peMinusPlus: WideCharArr;
    altNumTable: WideCharArr;
    reserved: PACKED ARRAY [0..19] OF CHAR;
    END;



Itl4Ptr = ^Itl4Rec;
Itl4Handle = ^Itl4Ptr;
Itl4Rec = RECORD
    flags: INTEGER;											{reserved}
    resourceType: LONGINT;									{contains 'itl4'}
    resourceNum: INTEGER;									{resource ID}
    version: INTEGER;										{version number}
    resHeader1: LONGINT;									{reserved}
    resHeader2: LONGINT;									{reserved}
    numTables: INTEGER;										{number of tables, one-based}
    mapOffset: LONGINT;										{offset to table that maps byte to token}
    strOffset: LONGINT;										{offset to routine that copies canonical string}
    fetchOffset: LONGINT;									{offset to routine that gets next byte of character}
    unTokenOffset: LONGINT;									{offset to table that maps token to canonical string}
    defPartsOffset: LONGINT;								{offset to default number parts table}
    resOffset6: LONGINT;									{reserved}
    resOffset7: LONGINT;									{reserved}
    resOffset8: LONGINT;									{reserved}
    END;

{ New NItl4Rec for System 7.0: }

NItl4Ptr = ^NItl4Rec;
NItl4Handle = ^NItl4Ptr;
NItl4Rec = RECORD
    flags: INTEGER;											{reserved}
    resourceType: LONGINT;									{contains 'itl4'}
    resourceNum: INTEGER;									{resource ID}
    version: INTEGER;										{version number}
    format: INTEGER;										{format code}
    resHeader: INTEGER;										{reserved}
    resHeader2: LONGINT;									{reserved}
    numTables: INTEGER;										{number of tables, one-based}
    mapOffset: LONGINT;										{offset to table that maps byte to token}
    strOffset: LONGINT;										{offset to routine that copies canonical string}
    fetchOffset: LONGINT;									{offset to routine that gets next byte of character}
    unTokenOffset: LONGINT;									{offset to table that maps token to canonical string}
    defPartsOffset: LONGINT;								{offset to default number parts table}
    whtSpListOffset: LONGINT;								{offset to white space code list}
    resOffset7: LONGINT;									{reserved}
    resOffset8: LONGINT;									{reserved}
    resLength1: INTEGER;									{reserved}
    resLength2: INTEGER;									{reserved}
    resLength3: INTEGER;									{reserved}
    unTokenLength: INTEGER;									{length of untoken table}
    defPartsLength: INTEGER;								{length of default number parts table}
    whtSpListLength: INTEGER;								{length of white space code list}
    resLength7: INTEGER;									{reserved}
    resLength8: INTEGER;									{reserved}
    END;

TableDirectoryRecord = RECORD
    tableSignature: OSType;									{4 byte long table name }
    reserved: LONGINT;										{Reserved for internal use }
    tableStartOffset: LONGINT;								{Table start offset in byte}
    tableSize: LONGINT;										{Table size in byte}
    END;

Itl5Record = RECORD
    versionNumber: Fixed;									{itl5 resource version number }
    numberOfTables: INTEGER;								{Number of tables it contains }
    reserved: ARRAY [0..2] OF INTEGER;						{Reserved for internal use }
    tableDirectory: ARRAY [0..0] OF TableDirectoryRecord;	{Table directory records }
    END;

RuleBasedTrslRecord = RECORD
    sourceType: INTEGER;									{Transliterate target type for the LHS of the rule }
    targetType: INTEGER;									{Transliterate target type for the RHS of the rule }
    formatNumber: INTEGER;									{Transliterate resource format number }
    propertyFlag: INTEGER;									{Transliterate property flags }
    numberOfRules: INTEGER;									{Number of rules following this field }
    END;



ItlcRecord = RECORD
    itlcSystem: INTEGER;									{default system script}
    itlcReserved: INTEGER;									{reserved}
    itlcFontForce: SignedByte;								{default font force flag}
    itlcIntlForce: SignedByte;								{default intl force flag}
    itlcOldKybd: SignedByte;								{MacPlus intl keybd flag}
    itlcFlags: SignedByte;									{general flags}
    itlcIconOffset: INTEGER;								{keyboard icon offset; not used in 7.0}
    itlcIconSide: SignedByte;								{keyboard icon side; not used in 7.0}
    itlcIconRsvd: SignedByte;								{rsvd for other icon info}
    itlcRegionCode: INTEGER;								{preferred verXxx code}
    itlcSysFlags: INTEGER;									{flags for setting system globals}
    itlcReserved4: ARRAY [0..31] OF SignedByte;				{for future use}
    END;

ItlbRecord = RECORD
    itlbNumber: INTEGER;									{itl0 id number}
    itlbDate: INTEGER;										{itl1 id number}
    itlbSort: INTEGER;										{itl2 id number}
    itlbFlags: INTEGER;										{Script flags}
    itlbToken: INTEGER;										{itl4 id number}
    itlbEncoding: INTEGER;									{itl5 ID # (optional; char encoding)}
    itlbLang: INTEGER;										{current language for script }
    itlbNumRep: SignedByte;									{number representation code}
    itlbDateRep: SignedByte;								{date representation code }
    itlbKeys: INTEGER;										{KCHR id number}
    itlbIcon: INTEGER;										{ID # of SICN or kcs#/kcs4/kcs8 suite.}
    END;

{ New ItlbExtRecord structure for System 7.0 }

ItlbExtRecord = RECORD
    base: ItlbRecord;										{un-extended ItlbRecord}
    itlbLocalSize: LONGINT;									{size of script's local record}
    itlbMonoFond: INTEGER;									{default monospace FOND ID}
    itlbMonoSize: INTEGER;									{default monospace font size}
    itlbPrefFond: INTEGER;									{preferred FOND ID}
    itlbPrefSize: INTEGER;									{preferred font size}
    itlbSmallFond: INTEGER;									{default small FOND ID}
    itlbSmallSize: INTEGER;									{default small font size}
    itlbSysFond: INTEGER;									{default system FOND ID}
    itlbSysSize: INTEGER;									{default system font size}
    itlbAppFond: INTEGER;									{default application FOND ID}
    itlbAppSize: INTEGER;									{default application font size}
    itlbHelpFond: INTEGER;									{default Help Mgr FOND ID}
    itlbHelpSize: INTEGER;									{default Help Mgr font size}
    itlbValidStyles: Style;									{set of valid styles for script}
    itlbAliasStyle: Style;									{style (set) to mark aliases}
    END;

{$ENDC} { UsingIntlResources }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}

