/*
	File:		TextUtils.h

	Contains:	C Interface to the Macintosh Libraries

	Written by:	Don Louv

	Copyright:	© 1985-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM6>	 8/17/93	JDR		update from Reality
		<19>	  8/2/93	DTY		Move EqualString inlines into TextUtilsPriv.h.
		<18>	 3/20/93	ngk		Fix to <17>, Stupid _CmpString returns 0 if strings are equal,
									so need to NOT result in inline (glue used to do this for you).
		<17>	 3/19/93	DTY		Add InlineEqualString, CaseSensitiveEqualString,
									MarkSensitiveEqualString, and CaseAndMarkSensitiveEqualString in
									a further effort to reduce glue required by the system.
		<16>	10/16/92	PKE		For new IM: Change reserved field name in NBreakTable to length,
									reflecting its real usage.
		<15>	 8/28/92	DCL		Fixed enums with commas before the closing brace. MPW now
									complains.
		<14>	 6/11/92	DCL		Cleanup & formatting to match Interface Stacks. Happy Happy Joy
									Joy.
		<13>	 5/29/92	DCL		Moved DateTime stuff to OSUtils, and intl stuff to
									IntlResources.
		<12>	  5/7/92	DCL		NIIM: Movin date & time Stuff from DateTime to TextUtils.
		<11>	  5/6/92	DCL		NIIM: Moved KeyTrans back from TextUtils to Events.
		<10>	  5/5/92	DCL		For New Inside Mac: removing 'sc' prefixes from some calls,
									moving some calls from script to TextUtils, and moving some from
									TextUtils & QuickDraw to QuickdrawText. Weeeeeeee!
		 <9>	 4/28/92	KST		Get rid of the compiler warning.
		 <8>	 4/17/92	DCL		For New Inside Mac: Mo' Better Call Names. Str -> String, Secs
									-> Seconds. Sorry, no more Secs.
		 <7>	 4/15/92	DCL		For New Inside Mac: Moved StyledLineBreakCode from script to
									TextUtils.
		 <6>	 4/15/92	DCL		For New Inside Mac: Moved many definitions from Script to
									TextUtils. And added new synonyms. #1025005
		 <5>	  4/6/92	DCL		For New Inside Mac: Moved declarations from Script.[aph] to
									TextUtils.[aph]. #1025005
		 <4>	  4/1/92	DCL		Fix the calls from xxxxIntlxxxx to xxxxxxxxxIntl.
		 <3>	 3/30/92	DCL		New and Improved routine names for New Improved Inside Mac.
									#1025005
		<2+>	 3/26/92	DCL	Moved IUMetric here.  I slipped and dropped it in DateTime.
									Need better mousegrips.
		 <2>	 3/26/92	DCL	For New IM: Moved many declarations and routines from
									Packages.[ph] to TextUtils.[ph]
		 <1>	 3/12/92	DCL	first checked in

*/



#ifndef __TEXTUTILS__
#define __TEXTUTILS__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __SCRIPT__
#include <Script.h>
#endif

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif


enum {
// New constants for System 7.0:   		<#9>

/*  Constants for truncWhere argument in TruncString and TruncText */
 truncEnd = 0,						/* Truncate at end */
 truncMiddle = 0x4000,			/* Truncate in middle */
 smTruncEnd = 0,					/* Truncate at end    obsolete */
 smTruncMiddle = 0x4000,		/* Truncate in middle     obsolete */

/* Constants for TruncString and TruncText results */
 notTruncated = 0,				/* No truncation was necessary */
 truncated = 1,					/* Truncation performed */
 truncErr = -1,					/* General error */
 smNotTruncated = 0,				/* No truncation was necessary	obsolete */
 smTruncated = 1,					/* Truncation performed				obsolete */
 smTruncErr = -1					/* General error						obsolete */
};

enum {
 fVNumber = 0,						/*first version of NumFormatString*/

/* Special language code values for Language Order */
 systemCurLang = -2,				/* current (itlbLang) lang for system script */
 systemDefLang = -3,				/* default (table) lang for system script */
 currentCurLang = -4,			/* current (itlbLang) lang for current script */
 currentDefLang = -5,			/* default lang for current script */
 scriptCurLang = -6,				/* current (itlbLang) lang for specified script */
 scriptDefLang = -7				/* default language for a specified script */
};
enum {
 iuSystemCurLang = -2,			/* <obsolete> current (itlbLang) lang for system script */
 iuSystemDefLang = -3,			/* <obsolete> default (table) lang for system script */
 iuCurrentCurLang = -4,			/* <obsolete> current (itlbLang) lang for current script */
 iuCurrentDefLang = -5,			/* <obsolete> default lang for current script */
 iuScriptCurLang = -6			/* <obsolete> current (itlbLang) lang for specified script */
};
enum {
 iuScriptDefLang = -7			/* <obsolete> default language for a specified script */
};


enum {smBreakWord,smBreakChar,smBreakOverflow};
typedef unsigned char StyledLineBreakCode;

enum {fPositive,fNegative,fZero};
typedef unsigned char FormatClass;

enum {fFormatOK,fBestGuess,fOutOfSynch,fSpuriousChars,fMissingDelimiter,
 fExtraDecimal,fMissingLiteral,fExtraExp,fFormatOverflow,fFormStrIsNAN,
 fBadPartsTable,fExtraPercent,fExtraSeparator,fEmptyFormatString};
typedef unsigned char FormatResultType;


struct NumFormatString {
 char fLength;
 char fVersion;
 char data[254];					/*private data*/
};

typedef struct NumFormatString NumFormatString;
typedef struct NumFormatString NumFormatStringRec;

struct FVector {
 short start;
 short length;
};

typedef struct FVector FVector;


typedef FVector TripleInt[3];		/* index by [fPositive..fZero] */

struct ScriptRunStatus {
 char script;
 char variant;
};

typedef struct ScriptRunStatus ScriptRunStatus;


/* New types for System 7.0:

  type for truncWhere parameter in new TruncString, TruncText */
typedef short TruncCode;


enum {shortDate,longDate,abbrevDate};
typedef unsigned char DateForm;

enum {
/* String2Date status values */
 fatalDateTime = 0x8000,			/*String2Date and String2Time mask to a fatal error*/
 longDateFound = 1,					/*String2Date mask to long date found*/
 leftOverChars = 2,					/*String2Date & Time mask to warn of left over characters*/
 sepNotIntlSep = 4,					/*String2Date & Time mask to warn of non-standard separators*/
 fieldOrderNotIntl = 8,				/*String2Date & Time mask to warn of non-standard field order*/
 extraneousStrings = 16,			/*String2Date & Time mask to warn of unparsable strings in text*/
 tooManySeps = 32,					/*String2Date & Time mask to warn of too many separators*/
 sepNotConsistent = 64,				/*String2Date & Time mask to warn of inconsistent separators*/
 tokenErr = 0x8100,					/*String2Date & Time mask for 'tokenizer err encountered'*/
 cantReadUtilities = 0x8200,
 dateTimeNotFound = 0x8400,
 dateTimeInvalid = 0x8800

};



typedef short StringToDateStatus;
typedef short String2DateStatus;

struct DateCacheRecord {
 short hidden[256];					/*only for temporary use*/
};

typedef struct DateCacheRecord DateCacheRecord;
typedef DateCacheRecord *DateCachePtr;


struct BreakTable {
 char charTypes[256];
 short tripleLength;
 short triples[1];
};

typedef struct BreakTable BreakTable;
typedef BreakTable *BreakTablePtr;

/* New NBreakTable for System 7.0: */
struct NBreakTable {
 signed char flags1;
 signed char flags2;
 short version;
 short classTableOff;
 short auxCTableOff;
 short backwdTableOff;
 short forwdTableOff;
 short doBackup;
 short length;								/* length of NBreakTable */	/*<16>*/
 char charTypes[256];
 short tables[1];
};

typedef struct NBreakTable NBreakTable;
typedef NBreakTable *NBreakTablePtr;



#ifdef __cplusplus
extern "C" {
#endif


pascal void IUDateString(long dateTime,DateForm longFlag,Str255 result)
 = {0x4267,0xA9ED};
void iudatestring(long dateTime,DateForm longFlag,char *result);
pascal void DateString(long dateTime,DateForm longFlag,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x000E,0xA9ED};
void datestring(long dateTime,DateForm longFlag,char *result,Handle intlHandle);
pascal void IUDatePString(long dateTime,DateForm longFlag,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x000E,0xA9ED};
void iudatepstring(long dateTime,DateForm longFlag,char *result,Handle intlHandle);
pascal void IUTimeString(long dateTime,Boolean wantSeconds,Str255 result)
 = {0x3F3C,0x0002,0xA9ED};
void iutimestring(long dateTime,Boolean wantSeconds,char *result);
pascal void TimeString(long dateTime,Boolean wantSeconds,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x0010,0xA9ED};
void timestring(long dateTime,Boolean wantSeconds,char *result,Handle intlHandle);
pascal void IUTimePString(long dateTime,Boolean wantSeconds,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x0010,0xA9ED};
void iutimepstring(long dateTime,Boolean wantSeconds,char *result,Handle intlHandle);

pascal void LongDateString(LongDateTime *dateTime,DateForm longFlag,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x0014,0xA9ED};
void longdatestring(LongDateTime *dateTime,DateForm longFlag,char *result,
 Handle intlHandle);
pascal void IULDateString(LongDateTime *dateTime,DateForm longFlag,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x0014,0xA9ED};
void iuldatestring(LongDateTime *dateTime,DateForm longFlag,char *result,
 Handle intlHandle);
pascal void LongTimeString(LongDateTime *dateTime,Boolean wantSeconds,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x0016,0xA9ED};
void longtimestring(LongDateTime *dateTime,Boolean wantSeconds,char *result,
 Handle intlHandle);
pascal void IULTimeString(LongDateTime *dateTime,Boolean wantSeconds,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x0016,0xA9ED};
void iultimestring(LongDateTime *dateTime,Boolean wantSeconds,char *result,
 Handle intlHandle);

pascal OSErr InitDateCache(DateCachePtr theCache)
 = {0x2F3C,0x8204,0xFFF8,0xA8B5};
pascal StringToDateStatus StringToDate(Ptr textPtr,long textLen,DateCachePtr theCache,
 long *lengthUsed,LongDateRec *dateTime)
 = {0x2F3C,0x8214,0xFFF6,0xA8B5};
pascal String2DateStatus String2Date(Ptr textPtr,long textLen,DateCachePtr theCache,
 long *lengthUsed,LongDateRec *dateTime)
 = {0x2F3C,0x8214,0xFFF6,0xA8B5};
pascal StringToDateStatus StringToTime(Ptr textPtr,long textLen,DateCachePtr theCache,
 long *lengthUsed,LongDateRec *dateTime)
 = {0x2F3C,0x8214,0xFFF4,0xA8B5};
pascal String2DateStatus String2Time(Ptr textPtr,long textLen,DateCachePtr theCache,
 long *lengthUsed,LongDateRec *dateTime)
 = {0x2F3C,0x8214,0xFFF4,0xA8B5};

pascal Boolean EqualString(ConstStr255Param str1,ConstStr255Param str2,
 Boolean caseSens,Boolean diacSens);
Boolean equalstring(char *str1,char *str2,Boolean caseSens,Boolean diacSens);
pascal void UpperString(Str255 theString,Boolean diacSens);
void upperstring(char *theString,Boolean diacSens);
pascal void UprString(Str255 theString,Boolean diacSens);
void uprstring(char *theString,Boolean diacSens);
pascal short RelString(ConstStr255Param str1,ConstStr255Param str2,Boolean caseSens,
 Boolean diacSens);
short relstring(char *str1,char *str2,Boolean caseSens,Boolean diacSens);

pascal StringHandle GetString(short stringID)
 = 0xA9BA;
pascal long Munger(Handle h,long offset,const void *ptr1,long len1,const void *ptr2,
 long len2)
 = 0xA9E0;
pascal void SetString(StringHandle theString,ConstStr255Param strNew)
 = 0xA907;
void setstring(StringHandle theString,char *strNew);
pascal StringHandle NewString(ConstStr255Param theString)
 = 0xA906;
StringHandle newstring(char *theString);
pascal void GetIndString(Str255 theString,short strListID,short index);
void getindstring(char *theString,short strListID,short index);

/* following four will be obsolete. Use equivalent PString call and pass a NIL handle */

pascal short IUMagString(const void *aPtr,const void *bPtr,short aLen,short bLen)
 = {0x3F3C,0x000A,0xA9ED};
pascal short IUMagIDString(const void *aPtr,const void *bPtr,short aLen,
 short bLen)
 = {0x3F3C,0x000C,0xA9ED};
pascal short IUCompString(ConstStr255Param aStr,ConstStr255Param bStr);
short iucompstring(char *aStr,char *bStr);
pascal short IUEqualString(ConstStr255Param aStr,ConstStr255Param bStr);
short iuequalstring(char *aStr,char *bStr);

pascal void StringToNum(ConstStr255Param theString,long *theNum);
void stringtonum(char *theString,long *theNum);
pascal void NumToString(long theNum,Str255 theString);
void numtostring(long theNum,char *theString);

pascal short CompareText(const void *aPtr,const void *bPtr,short aLen,
 short bLen,Handle itl2Handle)
 = {0x3F3C,0x001A,0xA9ED};
pascal short IUMagPString(const void *aPtr,const void *bPtr,short aLen,
 short bLen,Handle itl2Handle)
 = {0x3F3C,0x001A,0xA9ED};
pascal short IdenticalText(const void *aPtr,const void *bPtr,short aLen,
 short bLen,Handle itl2Handle)
 = {0x3F3C,0x001C,0xA9ED};
pascal short IUMagIDPString(const void *aPtr,const void *bPtr,short aLen,
 short bLen,Handle itl2Handle)
 = {0x3F3C,0x001C,0xA9ED};
pascal short CompareString(ConstStr255Param aStr,ConstStr255Param bStr,
 Handle itl2Handle);
short comparestring(char *aStr,char *bStr,Handle intlHandle);
pascal short IUCompPString(ConstStr255Param aStr,ConstStr255Param bStr,
 Handle itl2Handle);
short iucomppstring(char *aStr,char *bStr,Handle intlHandle);
pascal short IdenticalString(ConstStr255Param aStr,ConstStr255Param bStr,
 Handle itl2Handle);
short identicalstring(char *aStr,char *bStr,Handle intlHandle);
pascal short IUEqualPString(ConstStr255Param aStr,ConstStr255Param bStr,
 Handle itl2Handle);
short iuequalpstring(char *aStr,char *bStr,Handle intlHandle);
pascal short ScriptOrder(ScriptCode script1,ScriptCode script2)
 = {0x3F3C,0x001E,0xA9ED};
pascal short IUScriptOrder(ScriptCode script1,ScriptCode script2)
 = {0x3F3C,0x001E,0xA9ED};
pascal short LanguageOrder(LangCode language1,LangCode language2)
 = {0x3F3C,0x0020,0xA9ED};
pascal short IULangOrder(LangCode language1,LangCode language2)
 = {0x3F3C,0x0020,0xA9ED};
pascal short TextOrder(const void *aPtr,const void *bPtr,short aLen,short bLen,
 ScriptCode aScript,ScriptCode bScript,LangCode aLang,LangCode bLang)
 = {0x3F3C,0x0022,0xA9ED};
pascal short IUTextOrder(const void *aPtr,const void *bPtr,short aLen,short bLen,
 ScriptCode aScript,ScriptCode bScript,LangCode aLang,LangCode bLang)
 = {0x3F3C,0x0022,0xA9ED};
pascal short StringOrder(ConstStr255Param aStr,ConstStr255Param bStr,
 ScriptCode aScript,ScriptCode bScript,LangCode aLang,LangCode bLang);
pascal short IUStringOrder(ConstStr255Param aStr,ConstStr255Param bStr,
 ScriptCode aScript,ScriptCode bScript,LangCode aLang,LangCode bLang);
short iustringorder(char *aStr,char *bStr,ScriptCode aScript,ScriptCode bScript,
 LangCode aLang,LangCode bLang);

pascal void FindWord(Ptr textPtr,short textLength,short offset,Boolean leadingEdge,
 BreakTablePtr breaks,OffsetTable offsets)
 = {0x2F3C,0x8012,0x001A,0xA8B5};

pascal void FindWordBreaks(Ptr textPtr,short textLength,short offset,Boolean leadingEdge,
 BreakTablePtr breaks,OffsetTable offsets,ScriptCode script)
 = {0x2F3C,0xC012,0x001A,0xA8B5};

pascal void UprText(Ptr textPtr,short len)
 = {0x301F,0x205F,0xA054};
pascal void LwrText(Ptr textPtr,short len)
 = {0x301F,0x205F,0xA056};

/*  New for 7.0  */
pascal void LowerText(Ptr textPtr,short len)
 = {0x301F,0x205F,0xA056};
pascal void StripText(Ptr textPtr,short len)
 = {0x301F,0x205F,0xA256};
pascal void UpperText(Ptr textPtr,short len)
 = {0x301F,0x205F,0xA456};
pascal void StripUpperText(Ptr textPtr,short len)
 = {0x301F,0x205F,0xA656};

pascal StyledLineBreakCode StyledLineBreak(Ptr textPtr,long textLen,long textStart,
 long textEnd,long flags,Fixed *textWidth,long *textOffset)
 = {0x2F3C,0x821C,0xFFFE,0xA8B5};

pascal FormatStatus StringToFormatRec(ConstStr255Param inString,const NumberParts *partsTable,
 NumFormatString *outString)
 = {0x2F3C,0x820C,0xFFEC,0xA8B5};
pascal FormatStatus Str2Format(ConstStr255Param inString,const NumberParts *partsTable,
 NumFormatString *outString)
 = {0x2F3C,0x820C,0xFFEC,0xA8B5};
pascal FormatStatus FormatRecToString(const NumFormatString *myCanonical,const NumberParts *partsTable,
 Str255 outString,TripleInt positions)
 = {0x2F3C,0x8210,0xFFEA,0xA8B5};
pascal FormatStatus Format2Str(const NumFormatString *myCanonical,const NumberParts *partsTable,
 Str255 outString,TripleInt positions)
 = {0x2F3C,0x8210,0xFFEA,0xA8B5};
pascal FormatStatus ExtendedToString(extended80 x,const NumFormatString *myCanonical,
 const NumberParts *partsTable,Str255 outString)
 = {0x2F3C,0x8210,0xFFE8,0xA8B5};
pascal FormatStatus FormatX2Str(extended80 x,const NumFormatString *myCanonical,
 const NumberParts *partsTable,Str255 outString)
 = {0x2F3C,0x8210,0xFFE8,0xA8B5};
pascal FormatStatus StringToExtended(ConstStr255Param source,const NumFormatString *myCanonical,
 const NumberParts *partsTable,extended80 *x)
 = {0x2F3C,0x8210,0xFFE6,0xA8B5};
pascal FormatStatus FormatStr2X(ConstStr255Param source,const NumFormatString *myCanonical,
 const NumberParts *partsTable,extended80 *x)
 = {0x2F3C,0x8210,0xFFE6,0xA8B5};

pascal ScriptRunStatus FindScriptRun(Ptr textPtr,long textLen,long *lenUsed)
 = {0x2F3C,0x820C,0x0026,0xA8B5};

pascal void NFindWord(Ptr textPtr,short textLength,short offset,Boolean leadingEdge,
 NBreakTablePtr nbreaks,OffsetTable offsets)
 = {0x2F3C,0x8012,0xFFE2,0xA8B5};
pascal short TruncString(short width,Str255 theString,TruncCode truncWhere)
 = {0x2F3C,0x8208,0xFFE0,0xA8B5};
pascal short TruncText(short width,Ptr textPtr,short *length,TruncCode truncWhere)
 = {0x2F3C,0x820C,0xFFDE,0xA8B5};
pascal short ReplaceText(Handle baseText,Handle substitutionText,Str15 key)
 = {0x2F3C,0x820C,0xFFDC,0xA8B5};


pascal void LowercaseText(Ptr textPtr,short len,ScriptCode script)					/*<60>*/
	= {0x3F3C,0x0000,0x2F3C,0x800A,0xFFB6,0xA8B5};

pascal void StripDiacritics(Ptr textPtr,short len,ScriptCode script)					/*<60>*/
	= {0x3F3C,0x0200,0x2F3C,0x800A,0xFFB6,0xA8B5};

pascal void UppercaseText(Ptr textPtr,short len,ScriptCode script)					/*<60>*/
	= {0x3F3C,0x0400,0x2F3C,0x800A,0xFFB6,0xA8B5};

pascal void UppercaseStripDiacritics(Ptr textPtr,short len,ScriptCode script)				/*<60>*/
	= {0x3F3C,0x0600,0x2F3C,0x800A,0xFFB6,0xA8B5};



#ifdef __cplusplus
}
#endif

#endif
