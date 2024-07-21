
{
Created: Saturday, July 27, 1991 at 9:41 PM
 Memory.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1992
  All rights reserved

	Change History (most recent first):

		<10>	10/16/92	DTY		Add BlockMoveData.
		 <9>	 7/30/91	JL		Updated Copyright.
		 <8>	  3/1/91	ngk		Fixed double semicolon syntax error that DSG refuses to fix.
		 <7>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <6>	12/14/90	dba		<JDR> add Translate24To32, low-level memory control routines,
									and debugger support routines; also use more UNIV
		 <5>	 11/5/90	DFH		Added new names for Temporary Memory calls.
		 <4>	 11/4/90	dba		add calls and spellings that were previously only in the C .h
									file: ApplicationZone, MaxBlockSys, NewEmptyHandleSys, HLockHi,
									TempNewHandle, CompactMemSys, PurgeMemSys, FreeMemSys,
									ReserveMem, ReserveMemSys, MaxMemSys, DisposePtr, DisposeHandle,
									ReallocateHandle
		<3>		 10/3/90	JAL		Added Inlines after extensive code review.
** 1.1	ngk 05/17/1989 Added NewHandleSys, NewPtrSys, etc interface
** 1.0	CCH 11/17/1988 Adding to EASE.
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Memory;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingMemory}
{$SETC UsingMemory := 1}

{$I+}
{$SETC MemoryIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := MemoryIncludes}

CONST
maxSize = $800000;	{Max data block size is 8 megabytes}
defaultPhysicalEntryCount = 8;

{ values returned from the GetPageState function }
kPageInMemory = 0;
kPageOnDisk = 1;
kNotPaged = 2;

TYPE
Size = LONGINT;		{ size of a block in bytes }

THz = ^Zone;
Zone = RECORD
 bkLim: Ptr;
 purgePtr: Ptr;
 hFstFree: Ptr;
 zcbFree: LONGINT;
 gzProc: ProcPtr;
 moreMast: INTEGER;
 flags: INTEGER;
 cntRel: INTEGER;
 maxRel: INTEGER;
 cntNRel: INTEGER;
 maxNRel: INTEGER;
 cntEmpty: INTEGER;
 cntHandles: INTEGER;
 minCBFree: LONGINT;
 purgeProc: ProcPtr;
 sparePtr: Ptr;
 allocPtr: Ptr;
 heapData: INTEGER;
 END;

MemoryBlock = RECORD
 address: Ptr;
 count: LONGINT;
 END;

LogicalToPhysicalTable = RECORD
 logical: MemoryBlock;
 physical: ARRAY [0..defaultPhysicalEntryCount - 1] OF MemoryBlock;
 END;


PageState = INTEGER;
StatusRegisterContents = INTEGER;

FUNCTION GetApplLimit: Ptr;
 INLINE $2EB8,$0130;
FUNCTION GetZone: THz;
 INLINE $A11A,$2E88;
FUNCTION SystemZone: THz;
 INLINE $2EB8,$02A6;
FUNCTION ApplicZone: THz;
 INLINE $2EB8,$02AA;
FUNCTION ApplicationZone: THz;
 INLINE $2EB8,$02AA;
FUNCTION NewHandle(byteCount: Size): Handle;
FUNCTION NewHandleSys(byteCount: Size): Handle;
FUNCTION NewHandleClear(byteCount: Size): Handle;
FUNCTION NewHandleSysClear(byteCount: Size): Handle;
FUNCTION HandleZone(h: Handle): THz;
FUNCTION RecoverHandle(p: Ptr): Handle;
FUNCTION NewPtr(byteCount: Size): Ptr;
FUNCTION NewPtrSys(byteCount: Size): Ptr;
FUNCTION NewPtrClear(byteCount: Size): Ptr;
FUNCTION NewPtrSysClear(byteCount: Size): Ptr;
FUNCTION PtrZone(p: Ptr): THz;
FUNCTION GZSaveHnd: Handle;
 INLINE $2EB8,$0328;
FUNCTION TopMem: Ptr;
 INLINE $2EB8,$0108;
FUNCTION MaxBlock: LONGINT;
FUNCTION MaxBlockSys: LONGINT;
FUNCTION StackSpace: LONGINT;
FUNCTION NewEmptyHandle: Handle;
FUNCTION NewEmptyHandleSys: Handle;
PROCEDURE HLock(h: Handle);
 INLINE $205F,$A029;
PROCEDURE HUnlock(h: Handle);
 INLINE $205F,$A02A;
PROCEDURE HPurge(h: Handle);
 INLINE $205F,$A049;
PROCEDURE HNoPurge(h: Handle);
 INLINE $205F,$A04A;
PROCEDURE HLockHi(h: Handle);
 INLINE $205F,$A064,$A029;
FUNCTION StripAddress(theAddress: UNIV Ptr): Ptr;
{$IFC SystemSixOrLater }
 INLINE $201F,$A055,$2E80;
{$ENDC}
FUNCTION Translate24To32(addr24: UNIV Ptr): Ptr;
 INLINE $201F,$A091,$2E80;
FUNCTION TempNewHandle(logicalSize: Size;VAR resultCode: OSErr): Handle;
 INLINE $3F3C,$001D,$A88F;
FUNCTION TempMaxMem(VAR grow: Size): Size;
 INLINE $3F3C,$0015,$A88F;
FUNCTION TempFreeMem: LONGINT;
 INLINE $3F3C,$0018,$A88F;

{  Temporary Memory routines renamed, but obsolete, in System 7.0 and later.  }
PROCEDURE TempHLock(h: Handle;VAR resultCode: OSErr);
 INLINE $3F3C,$001E,$A88F;
PROCEDURE TempHUnlock(h: Handle;VAR resultCode: OSErr);
 INLINE $3F3C,$001F,$A88F;
PROCEDURE TempDisposeHandle(h: Handle;VAR resultCode: OSErr);
 INLINE $3F3C,$0020,$A88F;
FUNCTION TempTopMem: Ptr;
 INLINE $3F3C,$0016,$A88F;

{  Temporary Memory routines as they were known before System 7.0.  }
FUNCTION MFMaxMem(VAR grow: Size): Size;
 INLINE $3F3C,$0015,$A88F;
FUNCTION MFFreeMem: LONGINT;
 INLINE $3F3C,$0018,$A88F;
FUNCTION MFTempNewHandle(logicalSize: Size;VAR resultCode: OSErr): Handle;
 INLINE $3F3C,$001D,$A88F;
PROCEDURE MFTempHLock(h: Handle;VAR resultCode: OSErr);
 INLINE $3F3C,$001E,$A88F;
PROCEDURE MFTempHUnlock(h: Handle;VAR resultCode: OSErr);
 INLINE $3F3C,$001F,$A88F;
PROCEDURE MFTempDisposHandle(h: Handle;VAR resultCode: OSErr);
 INLINE $3F3C,$0020,$A88F;
FUNCTION MFTopMem: Ptr;
 INLINE $3F3C,$0016,$A88F;
PROCEDURE InitApplZone;
 INLINE $A02C;
PROCEDURE InitZone(pgrowZone: ProcPtr;cmoreMasters: INTEGER;limitPtr: UNIV Ptr;
 startPtr: UNIV Ptr);
PROCEDURE SetZone(hz: THz);
 INLINE $205F,$A01B;
FUNCTION CompactMem(cbNeeded: Size): Size;
FUNCTION CompactMemSys(cbNeeded: Size): Size;
PROCEDURE PurgeMem(cbNeeded: Size);
 INLINE $201F,$A04D;
PROCEDURE PurgeMemSys(cbNeeded: Size);
 INLINE $201F,$A44D;
FUNCTION FreeMem: LONGINT;
 INLINE $A01C,$2E80;
FUNCTION FreeMemSys: LONGINT;
 INLINE $A41C,$2E80;
PROCEDURE ResrvMem(cbNeeded: Size);
 INLINE $201F,$A040;
PROCEDURE ReserveMem(cbNeeded: Size);
 INLINE $201F,$A040;
PROCEDURE ReserveMemSys(cbNeeded: Size);
 INLINE $201F,$A440;
FUNCTION MaxMem(VAR grow: Size): Size;
FUNCTION MaxMemSys(VAR grow: Size): Size;
PROCEDURE SetGrowZone(growZone: ProcPtr);
 INLINE $205F,$A04B;
PROCEDURE SetApplLimit(zoneLimit: UNIV Ptr);
 INLINE $205F,$A02D;
PROCEDURE MoveHHi(h: Handle);
 INLINE $205F,$A064;
PROCEDURE DisposPtr(p: Ptr);
 INLINE $205F,$A01F;
PROCEDURE DisposePtr(p: Ptr);
 INLINE $205F,$A01F;
FUNCTION GetPtrSize(p: Ptr): Size;
PROCEDURE SetPtrSize(p: Ptr;newSize: Size);
PROCEDURE DisposHandle(h: Handle);
 INLINE $205F,$A023;
PROCEDURE DisposeHandle(h: Handle);
 INLINE $205F,$A023;
FUNCTION GetHandleSize(h: Handle): Size;
PROCEDURE SetHandleSize(h: Handle;newSize: Size);
PROCEDURE EmptyHandle(h: Handle);
 INLINE $205F,$A02B;
PROCEDURE ReallocHandle(h: Handle;byteCount: Size);
PROCEDURE ReallocateHandle(h: Handle;byteCount: Size);
PROCEDURE HSetRBit(h: Handle);
 INLINE $205F,$A067;
PROCEDURE HClrRBit(h: Handle);
 INLINE $205F,$A068;
PROCEDURE MoreMasters;
 INLINE $A036;
PROCEDURE BlockMove(srcPtr: UNIV Ptr;destPtr: UNIV Ptr;byteCount: Size);
PROCEDURE BlockMoveData(srcPtr: UNIV Ptr;destPtr: UNIV Ptr;byteCount: Size);
FUNCTION MemError: OSErr;
 INLINE $3EB8,$0220;
PROCEDURE PurgeSpace(VAR total: LONGINT;VAR contig: LONGINT);
FUNCTION HGetState(h: Handle): SignedByte;
PROCEDURE HSetState(h: Handle;flags: SignedByte);
PROCEDURE SetApplBase(startPtr: UNIV Ptr);
 INLINE $205F,$A057;
PROCEDURE MaxApplZone;
 INLINE $A063;
FUNCTION HoldMemory(address: UNIV Ptr;count: LONGINT): OSErr;
FUNCTION UnholdMemory(address: UNIV Ptr;count: LONGINT): OSErr;
FUNCTION LockMemory(address: UNIV Ptr;count: LONGINT): OSErr;
FUNCTION LockMemoryContiguous(address: UNIV Ptr;count: LONGINT): OSErr;
FUNCTION UnlockMemory(address: UNIV Ptr;count: LONGINT): OSErr;
FUNCTION GetPhysical(VAR addresses: LogicalToPhysicalTable;VAR physicalEntryCount: LONGINT): OSErr;
FUNCTION DeferUserFn(userFunction: ProcPtr;argument: UNIV Ptr): OSErr;
FUNCTION DebuggerGetMax: LONGINT;
 INLINE $7000,$A08D,$2E80;
PROCEDURE DebuggerEnter;
 INLINE $7001,$A08D;
PROCEDURE DebuggerExit;
 INLINE $7002,$A08D;
PROCEDURE DebuggerPoll;
 INLINE $7003,$A08D;
FUNCTION GetPageState(address: UNIV Ptr): PageState;
 INLINE $205F,$7004,$A08D,$3E80;
FUNCTION PageFaultFatal: BOOLEAN;
 INLINE $7005,$A08D,$1E80;
FUNCTION DebuggerLockMemory(address: UNIV Ptr;count: LONGINT): OSErr;
FUNCTION DebuggerUnlockMemory(address: UNIV Ptr;count: LONGINT): OSErr;
FUNCTION EnterSupervisorMode: StatusRegisterContents;
 INLINE $7008,$A08D,$3E80;


{$ENDC} { UsingMemory }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

