
{
Created: Saturday, July 27, 1991 at 11:41 PM
 Slots.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1986-1991
  All rights reserved

	Change History (most recent first):

		 <8>	 3/23/92	JSM		OSEvents.p is obsolete, use Events.p instead.
		 <7>	 7/31/91	JL		Updated Copyright.
		 <6>	  2/4/91	JL		Change aSync param name to async.
		 <5>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <4>	 1/23/91	stb		BBM: change spParamData in SpBlock type from Ptr to a LONGINT
		 <3>	12/14/90	dba 	<JDR> use inlines for everything
		 <2> 	 10/3/90	JAL 	Updated to Match C Interface.
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Slots;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingSlots}
{$SETC UsingSlots := 1}

{$I+}
{$SETC SlotsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingEvents}
{$I $$Shell(PInterfaces)Events.p}
{$ENDC}
{$IFC UNDEFINED UsingOSUtils}
{$I $$Shell(PInterfaces)OSUtils.p}
{$ENDC}
{$IFC UNDEFINED UsingFiles}
{$I $$Shell(PInterfaces)Files.p}
{$ENDC}
{$SETC UsingIncludes := SlotsIncludes}

CONST
fCardIsChanged = 1;									{Card is Changed field in StatusFlags field of sInfoArray}
fCkForSame = 0;										{For SearchSRT. Flag to check for SAME sResource in the table. }
fCkForNext = 1;										{For SearchSRT. Flag to check for NEXT sResource in the table. }
fWarmStart = 2;										{If this bit is set then warm start else cold start.}

stateNil = 0;										{State}
stateSDMInit = 1;									{:Slot declaration manager Init}
statePRAMInit = 2;									{:sPRAM record init}
statePInit = 3;										{:Primary init}
stateSInit = 4;										{:Secondary init}

{ flags for spParamData }
fall = 0;											{ bit 0: set=search enabled/disabled sRsrc's }
foneslot = 1;										{    1: set=search sRsrc's in given slot only }
fnext = 2;											{    2: set=search for next sRsrc }

TYPE
SQElemPtr = ^SlotIntQElement;
SlotIntQElement = RECORD
 sqLink: Ptr;										{ptr to next element}
 sqType: INTEGER;									{queue type ID for validity}
 sqPrio: INTEGER;									{priority}
 sqAddr: ProcPtr;									{interrupt service routine}
 sqParm: LONGINT;									{optional A1 parameter}
 END;

SpBlockPtr = ^SpBlock;
SpBlock = PACKED RECORD
 spResult: LONGINT;									{FUNCTION Result}
 spsPointer: Ptr;									{structure pointer}
 spSize: LONGINT;									{size of structure}
 spOffsetData: LONGINT;								{offset/data field used by sOffsetData}
 spIOFileName: Ptr;									{ptr to IOFile name for sDisDrvrName}
 spsExecPBlk: Ptr;									{pointer to sExec parameter block.}
 spParamData: LONGINT;								{misc parameter data (formerly spStackPtr).}
 spMisc: LONGINT;									{misc field for SDM.}
 spReserved: LONGINT;								{reserved for future expansion}
 spIOReserved: INTEGER;								{Reserved field of Slot Resource Table}
 spRefNum: INTEGER;									{RefNum}
 spCategory: INTEGER;								{sType: Category}
 spCType: INTEGER;									{Type}
 spDrvrSW: INTEGER;									{DrvrSW}
 spDrvrHW: INTEGER;									{DrvrHW}
 spTBMask: SignedByte;								{type bit mask bits 0..3 mask words 0..3}
 spSlot: SignedByte;								{slot number}
 spID: SignedByte;									{structure ID}
 spExtDev: SignedByte;								{ID of the external device}
 spHwDev: SignedByte;								{Id of the hardware device.}
 spByteLanes: SignedByte;							{bytelanes from card ROM format block}
 spFlags: SignedByte;								{standard flags}
 spKey: SignedByte;									{Internal use only}
 END;

SInfoRecPtr = ^SInfoRecord;
SInfoRecord = PACKED RECORD
 siDirPtr: Ptr;										{Pointer to directory}
 siInitStatusA: INTEGER;							{initialization E}
 siInitStatusV: INTEGER;							{status returned by vendor init code}
 siState: SignedByte;								{initialization state}
 siCPUByteLanes: SignedByte;						{0=[d0..d7] 1=[d8..d15]}
 siTopOfROM: SignedByte;							{Top of ROM= $FssFFFFx: x is TopOfROM}
 siStatusFlags: SignedByte;							{bit 0 - card is changed}
 siTOConst: INTEGER;								{Time Out C for BusErr}
 siReserved: PACKED ARRAY [0..1] OF SignedByte;		{reserved}
 siROMAddr: Ptr;									{ addr of top of ROM }
 siSlot: CHAR;										{ slot number }
 siPadding: PACKED ARRAY [0..2] OF SignedByte;		{ reserved }
 END;

SDMRecord = PACKED RECORD
 sdBEVSave: ProcPtr;								{Save old BusErr vector}
 sdBusErrProc: ProcPtr;								{Go here to determine if it is a BusErr}
 sdErrorEntry: ProcPtr;								{Go here if BusErrProc finds real BusErr}
 sdReserved: LONGINT;								{Reserved}
 END;

FHeaderRecPtr = ^FHeaderRec;
FHeaderRec = PACKED RECORD
 fhDirOffset: LONGINT;								{offset to directory}
 fhLength: LONGINT;									{length of ROM}
 fhCRC: LONGINT;									{CRC}
 fhROMRev: SignedByte;								{revision of ROM}
 fhFormat: SignedByte;								{format - 2}
 fhTstPat: LONGINT;									{test pattern}
 fhReserved: SignedByte;							{reserved}
 fhByteLanes: SignedByte;							{ByteLanes}
 END;

SEBlock = PACKED RECORD
 seSlot: SignedByte;								{Slot number.}
 sesRsrcId: SignedByte;								{sResource Id.}
 seStatus: INTEGER;									{Status of code executed by sExec.}
 seFlags: SignedByte;								{Flags}
 seFiller0: SignedByte;								{Filler, must be SignedByte to align on odd boundry}
 seFiller1: SignedByte;								{Filler}
 seFiller2: SignedByte;								{Filler}
 seResult: LONGINT;									{Result of sLoad.}
 seIOFileName: LONGINT;								{Pointer to IOFile name.}
 seDevice: SignedByte;								{Which device to read from.}
 sePartition: SignedByte;							{The partition.}
 seOSType: SignedByte;								{Type of OS.}
 seReserved: SignedByte;							{Reserved field.}
 seRefNum: SignedByte;								{RefNum of the driver.}
 seNumDevices: SignedByte;							{ Number of devices to load.}
 seBootState: SignedByte;							{State of StartBoot code.}
 END;



{  Principle  }
FUNCTION SReadByte(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7000,$A06E,$3E80;
FUNCTION SReadWord(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7001,$A06E,$3E80;
FUNCTION SReadLong(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7002,$A06E,$3E80;
FUNCTION SGetCString(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7003,$A06E,$3E80;
FUNCTION SGetBlock(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7005,$A06E,$3E80;
FUNCTION SFindStruct(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7006,$A06E,$3E80;
FUNCTION SReadStruct(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7007,$A06E,$3E80;


{  Special  }
FUNCTION SReadInfo(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7010,$A06E,$3E80;
FUNCTION SReadPRAMRec(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7011,$A06E,$3E80;
FUNCTION SPutPRAMRec(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7012,$A06E,$3E80;
FUNCTION SReadFHeader(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7013,$A06E,$3E80;
FUNCTION SNextSRsrc(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7014,$A06E,$3E80;
FUNCTION SNextTypeSRsrc(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7015,$A06E,$3E80;
FUNCTION SRsrcInfo(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7016,$A06E,$3E80;
FUNCTION SCkCardStat(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7018,$A06E,$3E80;
FUNCTION SReadDrvrName(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7019,$A06E,$3E80;
FUNCTION SFindDevBase(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$701B,$A06E,$3E80;
FUNCTION SFindBigDevBase(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$701C,$A06E,$3E80;


{  Advanced  }
FUNCTION InitSDeclMgr(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7020,$A06E,$3E80;
FUNCTION SPrimaryInit(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7021,$A06E,$3E80;
FUNCTION SCardChanged(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7022,$A06E,$3E80;
FUNCTION SExec(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7023,$A06E,$3E80;
FUNCTION SOffsetData(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7024,$A06E,$3E80;
FUNCTION SInitPRAMRecs(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7025,$A06E,$3E80;
FUNCTION SReadPBSize(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7026,$A06E,$3E80;
FUNCTION SCalcStep(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7028,$A06E,$3E80;
FUNCTION SInitSRsrcTable(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7029,$A06E,$3E80;
FUNCTION SSearchSRT(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$702A,$A06E,$3E80;
FUNCTION SUpdateSRT(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$702B,$A06E,$3E80;
FUNCTION SCalcSPointer(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$702C,$A06E,$3E80;
FUNCTION SGetDriver(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$702D,$A06E,$3E80;
FUNCTION SPtrToSlot(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$702E,$A06E,$3E80;
FUNCTION SFindSInfoRecPtr(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$702F,$A06E,$3E80;
FUNCTION SFindSRsrcPtr(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7030,$A06E,$3E80;
FUNCTION SDeleteSRTRec(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7031,$A06E,$3E80;

FUNCTION OpenSlot(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION OpenSlotSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A200,$3E80;
FUNCTION OpenSlotAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A600,$3E80;


{  Device Manager Slot Support  }
FUNCTION SIntInstall(sIntQElemPtr: SQElemPtr;theSlot: INTEGER): OSErr;
 INLINE $301F,$205F,$A075,$3E80;
FUNCTION SIntRemove(sIntQElemPtr: SQElemPtr;theSlot: INTEGER): OSErr;
 INLINE $301F,$205F,$A076,$3E80;

FUNCTION SVersion(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7008,$A06E,$3E80;
FUNCTION SetSRsrcState(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$7009,$A06E,$3E80;
FUNCTION InsertSRTRec(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$700A,$A06E,$3E80;
FUNCTION SGetSRsrc(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$700B,$A06E,$3E80;
FUNCTION SGetTypeSRsrc(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$700C,$A06E,$3E80;
FUNCTION SGetSRsrcPtr(spBlkPtr: SpBlockPtr): OSErr;
 INLINE $205F,$701D,$A06E,$3E80;


{$ENDC} { UsingSlots }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

