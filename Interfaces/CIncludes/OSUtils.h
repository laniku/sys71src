
/************************************************************

Created: Saturday, July 27, 1991 at 5:07 PM
 OSUtils.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1992
  All rights reserved

	Dont use:
	-SetUpA5
	-RestoreA5
	Instead:
	SetUpA5 --> myA5 = SetCurrentA5()
	RestoreA5 --> oldA5 = SetA5(myA5)

	Change History (most recent first):

		<SM1>	 10/26/92	CSS		Conditionalize SwapMMUMode to generate no code when
									we don't support 24 bit mode.
		<20>	 8/13/92	JDR		Add Deferred Task structure.
		<19>	 5/29/92	DCL		Moved DateTime stuff from TextUtils to OSUtils.
		<18>	  5/7/92	DCL		NIIM: Movin date & time Stuff back from DateTime to OSUtils.
		<17>	 4/16/92	DCL		For New Inside Mac: Moved Read&WriteLocation from Script to
									OSUtils.
		<16>	 3/26/92	DCL		For New Inside Mac:  Moved all of the Date & Time stuff to the
									New DateTime include file.    #1025005
		<15>	 3/12/92	DCL		For New Inside Mac Text volume: Moved KeyTrans, EqualString,
									RelString, Compare String, UprString, UpperString to the new
									TextUtils.[ph]
		<14>	 3/10/92	DTY		Strike three for Don: Change second #pragma parameter Secs2Date
									to be #pragma parameter SecsToDate.
		<13>	 3/10/92	DCL		For New Improved Inside Mac: Added Call names without Abbrevs.:
									SecsToDate (Secs2Date) and DateToSecs (Date2Secs). Affected
									Files: OSUtils.[ph], SysEqu.a, Traps.[aph].
		<12>	 7/30/91	JL		Updated Copyright.
		<11>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <9>	12/14/90	dba		<JDR> change SystemSixOrBetter to SystemSixOrLater
		 <8>	11/28/90	JL		Put formal parameter names back.
		 <7>	 11/7/90	JL		Changed all #defines to anonymous enums
		 <6>	 11/4/90	dba		made some parameters void* instead of Ptr; added more use of
									const in parameters; make a smaller GetMMUMode with #define; got
									rid of some extraneous parameter names; added
									GetToolboxTrapAddress, SetToolboxTrapAddress; used
									constStr255Parameter
		<5>	10/21/90	gbm		(with dba) Made compatible with 3.2 C compiler (and incompatible
									with previous compilers).
		<4>	10/9/90		JAL	Added SIQType and envMacIIfx.
							New style #Pragma Parameters for MPW 3.2 C
		<3>	03/07/90	JAL	Added support for Deferred Task.
** 1.2	CCH 12/15/1989 Updated SysEnvirons equates.
** 1.1	CCH 11/ 9/1988 Fixed headers and removed projector resource.
** 1.0	CCH 11/ 9/1988 Adding to EASE.

************************************************************/


#ifndef __OSUTILS__
#define __OSUTILS__

#ifndef __TYPES__
#include <Types.h>
#endif

enum {

 useFree = 0,
 useATalk = 1,
 useAsync = 2,
 useExtClk = 3,			/*Externally clocked*/
 useMIDI = 4,

/**** Environs Equates ****/
 curSysEnvVers = 2,		/*Updated to equal latest SysEnvirons version*/

/* Machine Types */
 envMac = -1,
 envXL = -2,
 envMachUnknown = 0,
 env512KE = 1,
 envMacPlus = 2,
 envSE = 3,
 envMacII = 4,
 envMacIIx = 5,
 envMacIIcx = 6,
 envSE30 = 7,
 envPortable = 8,
 envMacIIci = 9,
 envMacIIfx = 11,

/* CPU types */
 envCPUUnknown = 0
};
enum {
 env68000 = 1,
 env68010 = 2,
 env68020 = 3,
 env68030 = 4,
 env68040 = 5,

/* Keyboard types */
 envUnknownKbd = 0,
 envMacKbd = 1,
 envMacAndPad = 2,
 envMacPlusKbd = 3,
 envAExtendKbd = 4,
 envStandADBKbd = 5,
 envPrtblADBKbd = 6,
 envPrtblISOKbd = 7,
 envStdISOADBKbd = 8,
 envExtISOADBKbd = 9,
 false32b = 0,			/*24 bit addressing error*/
 true32b = 1,			/*32 bit addressing error*/

/* result types for RelString Call */
 sortsBefore = -1,		/*first string < second string*/
 sortsEqual = 0,		/*first string = second string*/
 sortsAfter = 1			/*first string > second string*/
};

enum {

/* Toggle results */
 toggleUndefined = 0,
 toggleOK = 1,
 toggleBadField = 2,
 toggleBadDelta = 3,
 toggleBadChar = 4,
 toggleUnknown = 5,
 toggleBadNum = 6,
 toggleOutOfRange = 7,				/*synonym for toggleErr3*/
 toggleErr3 = 7,
 toggleErr4 = 8,
 toggleErr5 = 9,

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

enum {eraField,yearField,monthField,dayField,hourField,minuteField,secondField,
 dayOfWeekField,dayOfYearField,weekOfYearField,pmField,res1Field,res2Field,
 res3Field};
typedef unsigned char LongDateField;

enum {dummyType,vType,ioQType,drvQType,evType,fsQType,sIQType,dtQType};
typedef unsigned short QTypes;

enum {OSTrap,ToolTrap};
typedef unsigned char TrapType;


struct SysParmType {
 char valid;
 char aTalkA;
 char aTalkB;
 char config;
 short portA;
 short portB;
 long alarm;
 short font;
 short kbdPrint;
 short volClik;
 short misc;
};

typedef struct SysParmType SysParmType;
typedef SysParmType *SysPPtr;

struct QElem {
 struct QElem *qLink;
 short qType;
 short qData[1];
};

typedef struct QElem QElem;
typedef QElem *QElemPtr;

struct QHdr {
 short qFlags;
 QElemPtr qHead;
 QElemPtr qTail;
};

typedef struct QHdr QHdr;
typedef QHdr *QHdrPtr;

typedef pascal void (*DTProcPtr)(void);

struct DeferredTask {
 QElemPtr qLink;
 short qType;
 short dtFlags;
 DTProcPtr dtAddr;
 long dtParam;
 long dtReserved;
};

typedef struct DeferredTask DeferredTask;
typedef DeferredTask *DeferredTaskPtr;

struct SysEnvRec {
 short environsVersion;
 short machineType;
 short systemVersion;
 short processor;
 Boolean hasFPU;
 Boolean hasColorQD;
 short keyBoardType;
 short atDrvrVersNum;
 short sysVRefNum;
};

typedef struct SysEnvRec SysEnvRec;

struct MachineLocation {
 Fract latitude;
 Fract longitude;
 union{
  char dlsDelta;					/*signed byte; daylight savings delta*/
  long gmtDelta;					/*must mask - see documentation*/
  }gmtFlags;
};

typedef struct MachineLocation MachineLocation;

struct DateTimeRec {
 short year;
 short month;
 short day;
 short hour;
 short minute;
 short second;
 short dayOfWeek;
};

typedef struct DateTimeRec DateTimeRec;


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

typedef short ToggleResults;

#ifdef __cplusplus
extern "C" {
#endif

pascal void LongDateToSeconds(const LongDateRec *lDate,LongDateTime *lSecs)
 = {0x2F3C,0x8008,0xFFF2,0xA8B5}; 
pascal void LongDate2Secs(const LongDateRec *lDate,LongDateTime *lSecs)
 = {0x2F3C,0x8008,0xFFF2,0xA8B5}; 
pascal void LongSecondsToDate(LongDateTime *lSecs,LongDateRec *lDate)
 = {0x2F3C,0x8008,0xFFF0,0xA8B5}; 
pascal void LongSecs2Date(LongDateTime *lSecs,LongDateRec *lDate)
 = {0x2F3C,0x8008,0xFFF0,0xA8B5}; 
pascal ToggleResults ToggleDate(LongDateTime *lSecs,LongDateField field,
 DateDelta delta,short ch,const TogglePB *params)
 = {0x2F3C,0x820E,0xFFEE,0xA8B5}; 

pascal short ValidDate(const LongDateRec *vDate,long flags,LongDateTime *newSecs)
 = {0x2F3C,0x820C,0xFFE4,0xA8B5}; 

pascal Boolean IsMetric(void)
 = {0x3F3C,0x0004,0xA9ED}; 
pascal Boolean IUMetric(void)		/* obsolete name */
 = {0x3F3C,0x0004,0xA9ED}; 


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

#define GetSysPPtr() ((SysPPtr) 0x01F8)
pascal void SysBeep(short duration)
 = 0xA9C8; 
#pragma parameter __D0 DTInstall(__A0)
pascal OSErr DTInstall(DeferredTaskPtr dtTaskPtr)
 = 0xA082; 
#define GetMMUMode() (* (char*) 0x0CB2)

#ifdef	Supports24Bit					// <SM1> CSS
	#pragma parameter SwapMMUMode(__A0)
	pascal void SwapMMUMode(char *mode)
	 = {0x1010,0xA05D,0x1080}; 
#else
	#define	SwapMMUMode(x)
#endif

#if SystemSixOrLater
#pragma parameter __D0 SysEnvirons(__D0,__A0)
pascal OSErr SysEnvirons(short versionRequested,SysEnvRec *theWorld)
 = 0xA090; 
#else
pascal OSErr SysEnvirons(short versionRequested,SysEnvRec *theWorld);
#endif
#pragma parameter Delay(__A0,__A1)
pascal void Delay(long numTicks,long *finalTicks)
 = {0xA03B,0x2280}; 
#pragma parameter __A0 GetTrapAddress(__D0)
pascal long GetTrapAddress(short trapNum)
 = 0xA146; 
#pragma parameter SetTrapAddress(__A0,__D0)
pascal void SetTrapAddress(long trapAddr,short trapNum)
 = 0xA047; 
pascal long NGetTrapAddress(short trapNum,TrapType tTyp); 
pascal void NSetTrapAddress(long trapAddr,short trapNum,TrapType tTyp); 
#pragma parameter __A0 GetOSTrapAddress(__D0)
pascal long GetOSTrapAddress(short trapNum)
 = 0xA346; 
#pragma parameter SetOSTrapAddress(__A0,__D0)
pascal void SetOSTrapAddress(long trapAddr,short trapNum)
 = 0xA247; 
#pragma parameter __A0 GetToolTrapAddress(__D0)
pascal long GetToolTrapAddress(short trapNum)
 = 0xA746; 
#pragma parameter SetToolTrapAddress(__A0,__D0)
pascal void SetToolTrapAddress(long trapAddr,short trapNum)
 = 0xA647; 
#pragma parameter __A0 GetToolboxTrapAddress(__D0)
pascal long GetToolboxTrapAddress(short trapNum)
 = 0xA746; 
#pragma parameter SetToolboxTrapAddress(__A0,__D0)
pascal void SetToolboxTrapAddress(long trapAddr,short trapNum)
 = 0xA647; 
pascal OSErr WriteParam(void); 
#pragma parameter Enqueue(__A0,__A1)
pascal void Enqueue(QElemPtr qElement,QHdrPtr qHeader)
 = 0xA96F; 
#pragma parameter __D0 Dequeue(__A0,__A1)
pascal OSErr Dequeue(QElemPtr qElement,QHdrPtr qHeader)
 = 0xA96E; 
long SetCurrentA5(void)
 = {0x200D,0x2A78,0x0904}; 
#pragma parameter __D0 SetA5(__D0)
long SetA5(long newA5)
 = 0xC18D; 
pascal void Environs(short *rom,short *machine); 
pascal OSErr HandToHand(Handle *theHndl); 
#pragma parameter __D0 PtrToXHand(__A0,__A1,__D0)
pascal OSErr PtrToXHand(const void *srcPtr,Handle dstHndl,long size)
 = 0xA9E2; 
pascal OSErr PtrToHand(const void *srcPtr,Handle *dstHndl,long size); 
#pragma parameter __D0 HandAndHand(__A0,__A1)
pascal OSErr HandAndHand(Handle hand1,Handle hand2)
 = 0xA9E4; 
#pragma parameter __D0 PtrAndHand(__A0,__A1,__D0)
pascal OSErr PtrAndHand(const void *ptr1,Handle hand2,long size)
 = 0xA9EF; 
#pragma parameter __D0 InitUtil
pascal OSErr InitUtil(void)
 = 0xA03F; 
pascal Boolean SwapInstructionCache(Boolean cacheEnable); 
pascal void FlushInstructionCache(void); 
pascal Boolean SwapDataCache(Boolean cacheEnable); 
pascal void FlushDataCache(void); 

pascal void ReadLocation(MachineLocation *loc)
 = {0x205F,0x203C,0x000C,0x00E4,0xA051}; 
pascal void WriteLocation(const MachineLocation *loc)
 = {0x205F,0x203C,0x000C,0x00E4,0xA052}; 

#ifdef __cplusplus
}
#endif

#endif
