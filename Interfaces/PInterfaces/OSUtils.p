
{
Created: Saturday, July 27, 1991 at 10:15 PM
 OSUtils.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1992
  All rights reserved


	Dont use:
	-SetUpA5
	-RestoreA5
	Instead:
	SetUpA5 --> myA5 := SetCurrentA5
	RestoreA5 --> oldA5 := SetA5(myA5)

	Change History (most recent first):

		<21>	 6/26/92	DCL		Miner Formatting Changes. Digging deep for things to do. Getting
									the file ready for ETO 8.
		<20>	 5/29/92	DCL		Moved DateTime stuff from TextUtils to OSUtils.
		<19>	  5/7/92	DCL		NIIM: Movin date & time Stuff back from DateTime to OSUtils.
		<17>	 4/16/92	DCL		For New Inside Mac: Moved Read&WriteLocation from Script to
									OSUtils.
		<16>	 3/26/92	DCL		For New Inside Mac:  Moved all of the Date & Time stuff to the
									newly created DateTime include file.  Removed inclusion of
									TextUtils to remove the circular dependancies..   #1025005
		<15>	 3/12/92	DCL		For New Inside Mac Text volume: Moved KeyTrans, EqualString,
									RelString, Compare String, UprString, UpperString to the new
									TextUtils.[ph]
		<14>	 3/10/92	DCL		For New Improved Inside Mac: Added Call names without Abbrevs.:
									SecsToDate (Secs2Date) and DateToSecs (Date2Secs). Affected
									Files: OSUtils.[ph], SysEqu.a, Traps.[aph].
		<13>	 7/30/91	JL		Updated Copyright.
		<12>	 1/27/91	LN		Checked in Database generate file from DSG. Changed parameter
									names from s to secs in DatetoSecs and SecstoDate to match .h
									file.
		<11>	 11/4/90	dba		get rid of SetUpA5 and RestoreA5; add GetOSTrapAddress,
									SetOSTrapAddress, GetToolboxTrapAddress, SetToolboxTrapAddress,
									GetToolTrapAddress, and SetToolTrapAddress
		<10>	10/10/90	JL		Fixing Inline for GETSYSPPTR
		 <9>	 10/3/90	JAL		Removed Restart, Added Inline for GetSysPPtr, added envMacIIfx.
		 <8>	 8/29/90	dnf		Change AltAccessParam to ForeignPrivParam
		 <7>	 5/18/90	JAL		Added sIQType into QTypes set and updated curSysEnvVers.
		 <6>	 4/13/90	dnf		Remove DTParam
		 <5>	 3/16/90	dnf		Add AltAccessParam
		 <4>	 3/07/90	JAL		Added Deferred Task support.
** 1.3	CCH 12/15/1989 Updated SysEnvirons equates.
** 1.2	EKN 07/31/1989 Added FIDParam
** 1.1	ngk 05/31/1989  Added env68030, envMacIIx, useMIDI, and useExtClk
** 1.0	CCH 11/17/1988 Adding to EASE.
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT OSUtils;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingOSUtils}
{$SETC UsingOSUtils := 1}

{$I+}
{$SETC OSUtilsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := OSUtilsIncludes}

CONST
useFree = 0;
useATalk = 1;
useAsync = 2;
useExtClk = 3;							{Externally clocked}
useMIDI = 4;

{*** Environs Equates ***}
curSysEnvVers = 2;						{Updated to equal latest SysEnvirons version}

{ Machine Types }
envMac = -1;
envXL = -2;
envMachUnknown = 0;
env512KE = 1;
envMacPlus = 2;
envSE = 3;
envMacII = 4;
envMacIIx = 5;
envMacIIcx = 6;
envSE30 = 7;
envPortable = 8;
envMacIIci = 9;
envMacIIfx = 11;

{ CPU types }
envCPUUnknown = 0;
env68000 = 1;
env68010 = 2;
env68020 = 3;
env68030 = 4;
env68040 = 5;

{ Keyboard types }
envUnknownKbd = 0;
envMacKbd = 1;
envMacAndPad = 2;
envMacPlusKbd = 3;
envAExtendKbd = 4;
envStandADBKbd = 5;
envPrtblADBKbd = 6;
envPrtblISOKbd = 7;
envStdISOADBKbd = 8;
envExtISOADBKbd = 9;
false32b = 0;							{24 bit addressing error}
true32b = 1;							{32 bit addressing error}

{ result types for RelString Call }
sortsBefore = -1;						{first string < second string}
sortsEqual = 0;							{first string = second string}
sortsAfter = 1;							{first string > second string}

{ Toggle results }
toggleUndefined = 0;
toggleOK = 1;
toggleBadField = 2;
toggleBadDelta = 3;
toggleBadChar = 4;
toggleUnknown = 5;
toggleBadNum = 6;
toggleOutOfRange = 7;					{synonym for toggleErr3}
toggleErr3 = 7;
toggleErr4 = 8;
toggleErr5 = 9;

{ Date equates }
smallDateBit = 31;						{Restrict valid date/time to range of Time global}
togChar12HourBit = 30;					{If toggling hour by char, accept hours 1..12 only}
togCharZCycleBit = 29;					{Modifier for togChar12HourBit: accept hours 0..11 only}
togDelta12HourBit = 28;					{If toggling hour up/down, restrict to 12-hour range (am/pm)}
genCdevRangeBit = 27;					{Restrict date/time to range used by genl CDEV}
validDateFields = -1;
maxDateField = 10;
eraMask = $0001;
yearMask = $0002;
monthMask = $0004;
dayMask = $0008;
hourMask = $0010;
minuteMask = $0020;
secondMask = $0040;
dayOfWeekMask = $0080;
dayOfYearMask = $0100;
weekOfYearMask = $0200;
pmMask = $0400;
dateStdMask = $007F;					{default for ValidDate flags and ToggleDate TogglePB.togFlags}

TYPE
LongDateField = (eraField,yearField,monthField,dayField,hourField,minuteField,
 secondField,dayOfWeekField,dayOfYearField,weekOfYearField,pmField,res1Field,
 res2Field,res3Field);

QTypes = (dummyType,vType,ioQType,drvQType,evType,fsQType,sIQType,dtQType);

TrapType = (OSTrap,ToolTrap);

ParamBlkType = (IOParam,FileParam,VolumeParam,CntrlParam,SlotDevParam,MultiDevParam,
 AccessParam,ObjParam,CopyParam,WDParam,FIDParam,CSParam,ForeignPrivParam);


SysPPtr = ^SysParmType;
SysParmType = PACKED RECORD
 valid: Byte;
 aTalkA: Byte;
 aTalkB: Byte;
 config: Byte;
 portA: INTEGER;
 portB: INTEGER;
 alarm: LONGINT;
 font: INTEGER;
 kbdPrint: INTEGER;
 volClik: INTEGER;
 misc: INTEGER;
 END;

{QElemPtr = ^QElem;}

QElemPtr = ^QElem;

FInfo = RECORD
 fdType: OSType;						{the type of the file}
 fdCreator: OSType;						{file's creator}
 fdFlags: INTEGER;						{flags ex. hasbundle,invisible,locked, etc.}
 fdLocation: Point;						{file's location in folder}
 fdFldr: INTEGER;						{folder containing file}
 END;

VCB = RECORD
 qLink: QElemPtr;
 qType: INTEGER;
 vcbFlags: INTEGER;
 vcbSigWord: INTEGER;
 vcbCrDate: LONGINT;
 vcbLsMod: LONGINT;
 vcbAtrb: INTEGER;
 vcbNmFls: INTEGER;
 vcbVBMSt: INTEGER;
 vcbAllocPtr: INTEGER;
 vcbNmAlBlks: INTEGER;
 vcbAlBlkSiz: LONGINT;
 vcbClpSiz: LONGINT;
 vcbAlBlSt: INTEGER;
 vcbNxtCNID: LONGINT;
 vcbFreeBks: INTEGER;
 vcbVN: Str27;
 vcbDrvNum: INTEGER;
 vcbDRefNum: INTEGER;
 vcbFSID: INTEGER;
 vcbVRefNum: INTEGER;
 vcbMAdr: Ptr;
 vcbBufAdr: Ptr;
 vcbMLen: INTEGER;
 vcbDirIndex: INTEGER;
 vcbDirBlk: INTEGER;
 vcbVolBkUp: LONGINT;
 vcbVSeqNum: INTEGER;
 vcbWrCnt: LONGINT;
 vcbXTClpSiz: LONGINT;
 vcbCTClpSiz: LONGINT;
 vcbNmRtDirs: INTEGER;
 vcbFilCnt: LONGINT;
 vcbDirCnt: LONGINT;
 vcbFndrInfo: ARRAY [1..8] OF LONGINT;
 vcbVCSize: INTEGER;
 vcbVBMCSiz: INTEGER;
 vcbCtlCSiz: INTEGER;
 vcbXTAlBlks: INTEGER;
 vcbCTAlBlks: INTEGER;
 vcbXTRef: INTEGER;
 vcbCTRef: INTEGER;
 vcbCtlBuf: Ptr;
 vcbDirIDM: LONGINT;
 vcbOffsM: INTEGER;
 END;

DrvQElPtr = ^DrvQEl;
DrvQEl = RECORD
 qLink: QElemPtr;
 qType: INTEGER;
 dQDrive: INTEGER;
 dQRefNum: INTEGER;
 dQFSID: INTEGER;
 dQDrvSz: INTEGER;
 dQDrvSz2: INTEGER;
 END;

ParmBlkPtr = ^ParamBlockRec;
ParamBlockRec = RECORD
 qLink: QElemPtr;
 qType: INTEGER;
 ioTrap: INTEGER;
 ioCmdAddr: Ptr;
 ioCompletion: ProcPtr;
 ioResult: OSErr;
 ioNamePtr: StringPtr;
 ioVRefNum: INTEGER;
 CASE ParamBlkType OF
   IOParam:
  (ioRefNum: INTEGER;
  ioVersNum: SignedByte;
  ioPermssn: SignedByte;
  ioMisc: Ptr;
  ioBuffer: Ptr;
  ioReqCount: LONGINT;
  ioActCount: LONGINT;
  ioPosMode: INTEGER;
  ioPosOffset: LONGINT);
   FileParam:
  (ioFRefNum: INTEGER;
  ioFVersNum: SignedByte;
  filler1: SignedByte;
  ioFDirIndex: INTEGER;
  ioFlAttrib: SignedByte;
  ioFlVersNum: SignedByte;
  ioFlFndrInfo: FInfo;
  ioFlNum: LONGINT;
  ioFlStBlk: INTEGER;
  ioFlLgLen: LONGINT;
  ioFlPyLen: LONGINT;
  ioFlRStBlk: INTEGER;
  ioFlRLgLen: LONGINT;
  ioFlRPyLen: LONGINT;
  ioFlCrDat: LONGINT;
  ioFlMdDat: LONGINT);
   VolumeParam:
  (filler2: LONGINT;
  ioVolIndex: INTEGER;
  ioVCrDate: LONGINT;
  ioVLsBkUp: LONGINT;
  ioVAtrb: INTEGER;
  ioVNmFls: INTEGER;
  ioVDirSt: INTEGER;
  ioVBlLn: INTEGER;
  ioVNmAlBlks: INTEGER;
  ioVAlBlkSiz: LONGINT;
  ioVClpSiz: LONGINT;
  ioAlBlSt: INTEGER;
  ioVNxtFNum: LONGINT;
  ioVFrBlk: INTEGER);
   CntrlParam:
  (ioCRefNum: INTEGER;
  csCode: INTEGER;
  csParam: ARRAY [0..10] OF INTEGER);
   SlotDevParam:
  (filler3: LONGINT;
  ioMix: Ptr;
  ioFlags: INTEGER;
  ioSlot: SignedByte;
  ioID: SignedByte);
   MultiDevParam:
  (filler4: LONGINT;
  ioMMix: Ptr;
  ioMFlags: INTEGER;
  ioSEBlkPtr: Ptr);
 END;

EvQElPtr = ^EvQEl;
EvQEl = RECORD
 qLink: QElemPtr;
 qType: INTEGER;
 evtQWhat: INTEGER;						{this part is identical to the EventRecord as...}
 evtQMessage: LONGINT;					{defined in ToolIntf}
 evtQWhen: LONGINT;
 evtQWhere: Point;
 evtQModifiers: INTEGER;
 END;

VBLTask = RECORD
 qLink: QElemPtr;
 qType: INTEGER;
 vblAddr: ProcPtr;
 vblCount: INTEGER;
 vblPhase: INTEGER;
 END;

DeferredTask = RECORD
 qLink: QElemPtr;						{next queue entry}
 qType: INTEGER;						{queue type}
 dtFlags: INTEGER;						{reserved}
 dtAddr: ProcPtr;						{pointer to task}
 dtParm: LONGINT;						{optional parameter}
 dtReserved: LONGINT;					{reserved--should be 0}
 END;

QElem = RECORD
 CASE QTypes OF
   dtQType:
  (dtQElem: DeferredTask);				{deferred}
   vType:
  (vblQElem: VBLTask);					{vertical blanking}
   ioQType:
  (ioQElem: ParamBlockRec);				{I/O parameter block}
   drvQType:
  (drvQElem: DrvQEl);					{drive}
   evType:
  (evQElem: EvQEl);						{event}
   fsQType:
  (vcbQElem: VCB);						{volume control block}
 END;

QHdrPtr = ^QHdr;
QHdr = RECORD
 qFlags: INTEGER;
 qHead: QElemPtr;
 qTail: QElemPtr;
 END;

SysEnvRec = RECORD
 environsVersion: INTEGER;
 machineType: INTEGER;
 systemVersion: INTEGER;
 processor: INTEGER;
 hasFPU: BOOLEAN;
 hasColorQD: BOOLEAN;
 keyBoardType: INTEGER;
 atDrvrVersNum: INTEGER;
 sysVRefNum: INTEGER;
 END;

MachineLocation = RECORD
 latitude: Fract;
 longitude: Fract;
 CASE INTEGER OF
   0:
  (dlsDelta: SignedByte);     			{signed byte; daylight savings delta}
   1:
  (gmtDelta: LONGINT);					{must mask - see documentation}
 END;

DateTimeRec = RECORD
 year: INTEGER;
 month: INTEGER;
 day: INTEGER;
 hour: INTEGER;
 minute: INTEGER;
 second: INTEGER;
 dayOfWeek: INTEGER;
 END;


LongDateTime = comp;

LongDateCvt = RECORD
 CASE INTEGER OF
   0:
  (c: Comp);
   1:
  (lHigh: LONGINT;
  lLow: LONGINT);
 END;

LongDateRec = RECORD
 CASE INTEGER OF
   0:
  (era: INTEGER;
  year: INTEGER;
  month: INTEGER;
  day: INTEGER;
  hour: INTEGER;
  minute: INTEGER;
  second: INTEGER;
  dayOfWeek: INTEGER;
  dayOfYear: INTEGER;
  weekOfYear: INTEGER;
  pm: INTEGER;
  res1: INTEGER;
  res2: INTEGER;
  res3: INTEGER);
   1:
  (list: ARRAY [0..13] OF INTEGER);		{Index by LongDateField!}
   2:
  (eraAlt: INTEGER;
  oldDate: DateTimeRec);
 END;


DateDelta = SignedByte;

TogglePB = RECORD
 togFlags: LONGINT;						{caller normally sets low word to dateStdMask=$7F}
 amChars: ResType;						{from 'itl0', but uppercased}
 pmChars: ResType;						{from 'itl0', but uppercased}
 reserved: ARRAY [0..3] OF LONGINT;
 END;


ToggleResults = INTEGER;

PROCEDURE LongDateToSeconds(lDate: LongDateRec;VAR lSecs: LongDateTime);
 INLINE $2F3C,$8008,$FFF2,$A8B5;
PROCEDURE LongDate2Secs(lDate: LongDateRec;VAR lSecs: LongDateTime);
 INLINE $2F3C,$8008,$FFF2,$A8B5;
PROCEDURE LongSecondsToDate(VAR lSecs: LongDateTime;VAR lDate: LongDateRec);
 INLINE $2F3C,$8008,$FFF0,$A8B5;
PROCEDURE LongSecs2Date(VAR lSecs: LongDateTime;VAR lDate: LongDateRec);
 INLINE $2F3C,$8008,$FFF0,$A8B5;
FUNCTION ToggleDate(VAR lSecs: LongDateTime;field: LongDateField;delta: DateDelta;
 ch: INTEGER;params: TogglePB): ToggleResults;
 INLINE $2F3C,$820E,$FFEE,$A8B5;
FUNCTION ValidDate(vDate: LongDateRec;flags: LONGINT;VAR newSecs: LongDateTime): INTEGER;
 INLINE $2F3C,$820C,$FFE4,$A8B5;
FUNCTION IsMetric: BOOLEAN;
 INLINE $3F3C,$0004,$A9ED;
FUNCTION IUMetric: BOOLEAN;
 INLINE $3F3C,$0004,$A9ED;
FUNCTION ReadDateTime(VAR time: LONGINT): OSErr;
PROCEDURE GetDateTime(VAR secs: LONGINT);
FUNCTION SetDateTime(time: LONGINT): OSErr;
PROCEDURE SetTime(d: DateTimeRec);
PROCEDURE GetTime(VAR d: DateTimeRec);
PROCEDURE DateToSeconds(d: DateTimeRec;VAR secs: LONGINT);
PROCEDURE Date2Secs(d: DateTimeRec;VAR secs: LONGINT);
PROCEDURE SecondsToDate(secs: LONGINT;VAR d: DateTimeRec);
PROCEDURE Secs2Date(secs: LONGINT;VAR d: DateTimeRec);
FUNCTION GetSysPPtr: SysPPtr;
 INLINE $2EBC,$0000,$01F8;
PROCEDURE SysBeep(duration: INTEGER);
 INLINE $A9C8;
FUNCTION DTInstall(dtTaskPtr: QElemPtr): OSErr;
FUNCTION GetMMUMode: SignedByte;
PROCEDURE SwapMMUMode(VAR mode: SignedByte);
FUNCTION SysEnvirons(versionRequested: INTEGER;VAR theWorld: SysEnvRec): OSErr;
PROCEDURE Delay(numTicks: LONGINT;VAR finalTicks: LONGINT);
FUNCTION GetTrapAddress(trapNum: INTEGER): LONGINT;
PROCEDURE SetTrapAddress(trapAddr: LONGINT;trapNum: INTEGER);
FUNCTION NGetTrapAddress(trapNum: INTEGER;tTyp: TrapType): LONGINT;
PROCEDURE NSetTrapAddress(trapAddr: LONGINT;trapNum: INTEGER;tTyp: TrapType);
FUNCTION GetOSTrapAddress(trapNum: INTEGER): LONGINT;
PROCEDURE SetOSTrapAddress(trapAddr: LONGINT;trapNum: INTEGER);
FUNCTION GetToolTrapAddress(trapNum: INTEGER): LONGINT;
PROCEDURE SetToolTrapAddress(trapAddr: LONGINT;trapNum: INTEGER);
FUNCTION GetToolboxTrapAddress(trapNum: INTEGER): LONGINT;
PROCEDURE SetToolboxTrapAddress(trapAddr: LONGINT;trapNum: INTEGER);
FUNCTION WriteParam: OSErr;
PROCEDURE Enqueue(qElement: QElemPtr;qHeader: QHdrPtr);
FUNCTION Dequeue(qElement: QElemPtr;qHeader: QHdrPtr): OSErr;
FUNCTION SetCurrentA5: LONGINT;
 INLINE $2E8D,$2A78,$0904;
FUNCTION SetA5(newA5: LONGINT): LONGINT;
 INLINE $2F4D,$0004,$2A5F;
PROCEDURE Environs(VAR rom: INTEGER;VAR machine: INTEGER);
FUNCTION HandToHand(VAR theHndl: Handle): OSErr;
FUNCTION PtrToXHand(srcPtr: Ptr;dstHndl: Handle;size: LONGINT): OSErr;
FUNCTION PtrToHand(srcPtr: Ptr;VAR dstHndl: Handle;size: LONGINT): OSErr;
FUNCTION HandAndHand(hand1: Handle;hand2: Handle): OSErr;
FUNCTION PtrAndHand(ptr1: Ptr;hand2: Handle;size: LONGINT): OSErr;
FUNCTION InitUtil: OSErr;
 INLINE $A03F,$3E80;
FUNCTION SwapInstructionCache(cacheEnable: BOOLEAN): BOOLEAN;
PROCEDURE FlushInstructionCache;
FUNCTION SwapDataCache(cacheEnable: BOOLEAN): BOOLEAN;
PROCEDURE FlushDataCache;
PROCEDURE ReadLocation(VAR loc: MachineLocation);
 INLINE $205F,$203C,$000C,$00E4,$A051;
PROCEDURE WriteLocation(loc: MachineLocation);
 INLINE $205F,$203C,$000C,$00E4,$A052;


{$ENDC} { UsingOSUtils }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

