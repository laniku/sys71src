/*
	File:		DateTime.h

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 4/22/92	FM		first checked in
		 <4>	 4/17/92	DCL		For New Inside Mac: Mo' Better Call Names. Str -> String, Secs
									-> Seconds. Sorry, no more Secs.
		 <3>	  4/1/92	DCL		Fix the calls from xxxxIntlxxxx to xxxxxxxxxIntl.
		 <2>	 3/30/92	DCL		For New Inside Mac: Added New Improved Better Names for the same
									old calls. #1025005
		 <1>	 3/26/92	DCL		first checked in
		 <0>	 3/12/92	DCL		Moved all the DateTime stuff from OSUtils, packages
		 								and Script

*/


#ifndef __DATETIME__
#define __DATETIME__

#ifndef __TYPES__
#include <Types.h>
#endif

struct DateTimeRec {
 short year;
 short month;
 short day;
 short hour;
 short minute;
 short second;
 short dayOfWeek;
};


enum {shortDate,longDate,abbrevDate};
typedef unsigned char DateForm;

typedef struct DateTimeRec DateTimeRec;

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
 dateTimeInvalid = 0x8800,

/* Date equates */
 smallDateBit = 31,					/*Restrict valid date/time to range of Time global*/
 togChar12HourBit = 30,				/*If toggling hour by char, accept hours 1..12 only*/
 togCharZCycleBit = 29,				/*Modifier for togChar12HourBit: accept hours 0..11 only*/
 togDelta12HourBit = 28,			/*If toggling hour up/down, restrict to 12-hour range (am/pm)*/
 genCdevRangeBit = 27,				/*Restrict date/time to range used by genl CDEV*/
 validDateFields = -1,
 maxDateField = 10,

 eraMask = 0x0001,
 yearMask = 0x0002,
 monthMask = 0x0004,
 dayMask = 0x0008,
 hourMask = 0x0010,
 minuteMask = 0x0020,
 secondMask = 0x0040,
 dayOfWeekMask = 0x0080,
 dayOfYearMask = 0x0100,
 weekOfYearMask = 0x0200,
 pmMask = 0x0400,
 dateStdMask = 0x007F				/*default for ValidDate flags and ToggleDate TogglePB.togFlags*/
};

enum {mdy,dmy,ymd,myd,dym,ydm};
typedef unsigned char DateOrders;

enum {
 zeroCycle = 1,					/*0:00 AM/PM format*/
 longDay = 0,					/*day of the month*/
 longWeek = 1,					/*day of the week*/
 longMonth = 2,					/*month of the year*/
 longYear = 3,					/*year*/
 supDay = 1,					/*suppress day of month*/
 supWeek = 2,					/*suppress day of week*/
 supMonth = 4,					/*suppress month*/
 supYear = 8,					/*suppress year*/
 dayLdingZ = 32,
 mntLdingZ = 64,
 century = 128,
 secLeadingZ = 32,
 minLeadingZ = 64,
 hrLeadingZ = 128
};

enum {eraField,yearField,monthField,dayField,hourField,minuteField,secondField,
 dayOfWeekField,dayOfYearField,weekOfYearField,pmField,res1Field,res2Field,
 res3Field};
typedef unsigned char LongDateField;

typedef short ToggleResults;
typedef short StringToDateStatus;
typedef short String2DateStatus;

struct DateCacheRecord {
 short hidden[256];					/*only for temporary use*/
};

typedef struct DateCacheRecord DateCacheRecord;
typedef DateCacheRecord *DateCachePtr;


typedef comp LongDateTime;

union LongDateCvt {
 comp c;
 struct {
  long lHigh;
  long lLow;
  } hl;
};

typedef union LongDateCvt LongDateCvt;

union LongDateRec {
 struct {
  short era;
  short year;
  short month;
  short day;
  short hour;
  short minute;
  short second;
  short dayOfWeek;
  short dayOfYear;
  short weekOfYear;
  short pm;
  short res1;
  short res2;
  short res3;
  } ld;
 short list[14];					/*Index by LongDateField!*/
 struct {
  short eraAlt;
  DateTimeRec oldDate;
  } od;
};

typedef union LongDateRec LongDateRec;


typedef char DateDelta;

struct TogglePB {
 long togFlags;						/*caller normally sets low word to dateStdMask=$7F*/
 ResType amChars;					/*from 'itl0', but uppercased*/
 ResType pmChars;					/*from 'itl0', but uppercased*/
 long reserved[4];
};

typedef struct TogglePB TogglePB;


#ifdef __cplusplus
extern "C" {
#endif


#pragma parameter __D0 ReadDateTime(__A0)
pascal OSErr ReadDateTime(unsigned long *time)
 = 0xA039; 
#pragma parameter GetDateTime(__A0)
pascal void GetDateTime(unsigned long *secs)
 = {0x20B8,0x020C}; 
#pragma parameter __D0 SetDateTime(__D0)
pascal OSErr SetDateTime(unsigned long time)
 = 0xA03A; 
#pragma parameter SetTime(__A0)
pascal void SetTime(const DateTimeRec *d)
 = {0xA9C7,0xA03A}; 
#pragma parameter GetTime(__A0)
pascal void GetTime(DateTimeRec *d)
 = {0x2038,0x020C,0xA9C6}; 
pascal void DateToSeconds(const DateTimeRec *d,unsigned long *secs); 
pascal void Date2Secs(const DateTimeRec *d,unsigned long *secs); 
#pragma parameter SecondsToDate(__D0,__A0)
pascal void SecondsToDate(unsigned long secs,DateTimeRec *d)
 = 0xA9C6; 
#pragma parameter Secs2Date(__D0,__A0)
pascal void Secs2Date(unsigned long secs,DateTimeRec *d)
 = 0xA9C6; 

pascal void DateString(long dateTime,DateForm longFlag,Str255 result)
 = {0x4267,0xA9ED}; 
pascal void IUDateString(long dateTime,DateForm longFlag,Str255 result)
 = {0x4267,0xA9ED}; 
pascal void DateStringIntl(long dateTime,DateForm longFlag,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x000E,0xA9ED}; 
pascal void IUDatePString(long dateTime,DateForm longFlag,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x000E,0xA9ED}; 
pascal void TimeString(long dateTime,Boolean wantSeconds,Str255 result)
 = {0x3F3C,0x0002,0xA9ED}; 
pascal void IUTimeString(long dateTime,Boolean wantSeconds,Str255 result)
 = {0x3F3C,0x0002,0xA9ED}; 
pascal void TimeStringIntl(long dateTime,Boolean wantSeconds,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x0010,0xA9ED}; 
pascal void IUTimePString(long dateTime,Boolean wantSeconds,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x0010,0xA9ED}; 
void datestring(long dateTime,DateForm longFlag,char *result); 
void iudatestring(long dateTime,DateForm longFlag,char *result); 
void datestringintl(long dateTime,DateForm longFlag,char *result,Handle intlHandle); 
void iudatepstring(long dateTime,DateForm longFlag,char *result,Handle intlHandle); 
void timestring(long dateTime,Boolean wantSeconds,char *result); 
void iutimestring(long dateTime,Boolean wantSeconds,char *result); 
void timestringintl(long dateTime,Boolean wantSeconds,char *result,Handle intlHandle); 
void iutimepstring(long dateTime,Boolean wantSeconds,char *result,Handle intlHandle); 

pascal void LongDateStringIntl(LongDateTime *dateTime,DateForm longFlag,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x0014,0xA9ED}; 
pascal void IULDateString(LongDateTime *dateTime,DateForm longFlag,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x0014,0xA9ED}; 
pascal void LongTimeStringIntl(LongDateTime *dateTime,Boolean wantSeconds,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x0016,0xA9ED}; 
pascal void IULTimeString(LongDateTime *dateTime,Boolean wantSeconds,Str255 result,
 Handle intlHandle)
 = {0x3F3C,0x0016,0xA9ED}; 
void longdatestringintl(LongDateTime *dateTime,DateForm longFlag,char *result,
 Handle intlHandle); 
void iuldatestring(LongDateTime *dateTime,DateForm longFlag,char *result,
 Handle intlHandle); 
void longtimestringintl(LongDateTime *dateTime,Boolean wantSeconds,char *result,
 Handle intlHandle); 
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
pascal void LongDateToSeconds(const LongDateRec *lDate,LongDateTime *lSecs)
 = {0x2F3C,0x8008,0xFFF2,0xA8B5}; 
pascal void LongDate2Secs(const LongDateRec *lDate,LongDateTime *lSecs)
 = {0x2F3C,0x8008,0xFFF2,0xA8B5}; 
pascal void SecondsToLongDate(LongDateTime *lSecs,LongDateRec *lDate)
 = {0x2F3C,0x8008,0xFFF0,0xA8B5}; 
pascal void LongSecs2Date(LongDateTime *lSecs,LongDateRec *lDate)
 = {0x2F3C,0x8008,0xFFF0,0xA8B5}; 
pascal ToggleResults ToggleDate(LongDateTime *lSecs,LongDateField field,
 DateDelta delta,short ch,const TogglePB *params)
 = {0x2F3C,0x820E,0xFFEE,0xA8B5}; 

pascal short ValidDate(const LongDateRec *vDate,long flags,LongDateTime *newSecs)
 = {0x2F3C,0x820C,0xFFE4,0xA8B5}; 



#ifdef __cplusplus
}
#endif

#endif
