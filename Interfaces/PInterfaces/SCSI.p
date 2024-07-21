
{
Created: Saturday, July 27, 1991 at 11:38 PM
 SCSI.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1986-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <4>	 7/31/91	JL		Updated Copyright.
		 <3>	 1/27/91	LN		Checked in Database generate file from DSG.
		<2>		10/3/90		JAL		Added Inline Code.

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT SCSI;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingSCSI}
{$SETC UsingSCSI := 1}

{$I+}
{$SETC SCSIIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := SCSIIncludes}

CONST
scInc = 1;
scNoInc = 2;
scAdd = 3;
scMove = 4;
scLoop = 5;
scNop = 6;
scStop = 7;
scComp = 8;
scCommErr = 2;									{communications error, operation timeout}
scArbNBErr = 3;									{arbitration timeout waiting for not BSY}
scBadParmsErr = 4;								{bad parameter or TIB opcode}
scPhaseErr = 5;									{SCSI bus not in correct phase for attempted operation}
scCompareErr = 6;								{data compare error}
scMgrBusyErr = 7;								{SCSI Manager busy }
scSequenceErr = 8;								{attempted operation is out of sequence}
scBusTOErr = 9;									{CPU bus timeout}
scComplPhaseErr = 10;							{SCSI bus wasn't in Status phase}
sbSIGWord = $4552;
pMapSIG = $504D;

TYPE
Block0 = PACKED RECORD
 sbSig: INTEGER;								{unique value for SCSI block 0}
 sbBlkSize: INTEGER;							{block size of device}
 sbBlkCount: LONGINT;							{number of blocks on device}
 sbDevType: INTEGER;							{device type}
 sbDevId: INTEGER;								{device id}
 sbData: LONGINT;								{not used}
 sbDrvrCount: INTEGER;							{driver descriptor count}
 ddBlock: LONGINT;								{1st driver's starting block}
 ddSize: INTEGER;								{size of 1st driver (512-byte blks)}
 ddType: INTEGER;								{system type (1 for Mac+)}
 ddPad: ARRAY [0..242] OF INTEGER;				{ARRAY[0..242] OF INTEGER; not used}
 END;

Partition = PACKED RECORD
 pmSig: INTEGER;								{unique value for map entry blk}
 pmSigPad: INTEGER;								{currently unused}
 pmMapBlkCnt: LONGINT;							{# of blks in partition map}
 pmPyPartStart: LONGINT;						{physical start blk of partition}
 pmPartBlkCnt: LONGINT;							{# of blks in this partition}
 pmPartName: PACKED ARRAY [0..31] OF CHAR;		{ASCII partition name}
 pmParType: PACKED ARRAY [0..31] OF CHAR;		{ASCII partition type}
 pmLgDataStart: LONGINT;						{log. # of partition's 1st data blk}
 pmDataCnt: LONGINT;							{# of blks in partition's data area}
 pmPartStatus: LONGINT;							{bit field for partition status}
 pmLgBootStart: LONGINT;						{log. blk of partition's boot code}
 pmBootSize: LONGINT;							{number of bytes in boot code}
 pmBootAddr: LONGINT;							{memory load address of boot code}
 pmBootAddr2: LONGINT;							{currently unused}
 pmBootEntry: LONGINT;							{entry point of boot code}
 pmBootEntry2: LONGINT;							{currently unused}
 pmBootCksum: LONGINT;							{checksum of boot code}
 pmProcessor: PACKED ARRAY [0..15] OF CHAR;		{ASCII for the processor type}
 pmPad: ARRAY [0..187] OF INTEGER;				{512 bytes long currently unused}
 END;

SCSIInstr = RECORD
 scOpcode: INTEGER;
 scParam1: LONGINT;
 scParam2: LONGINT;
 END;


FUNCTION SCSIReset: OSErr;
 INLINE $4267,$A815;
FUNCTION SCSIGet: OSErr;
 INLINE $3F3C,$0001,$A815;
FUNCTION SCSISelect(targetID: INTEGER): OSErr;
 INLINE $3F3C,$0002,$A815;
FUNCTION SCSICmd(buffer: Ptr;count: INTEGER): OSErr;
 INLINE $3F3C,$0003,$A815;
FUNCTION SCSIRead(tibPtr: Ptr): OSErr;
 INLINE $3F3C,$0005,$A815;
FUNCTION SCSIRBlind(tibPtr: Ptr): OSErr;
 INLINE $3F3C,$0008,$A815;
FUNCTION SCSIWrite(tibPtr: Ptr): OSErr;
 INLINE $3F3C,$0006,$A815;
FUNCTION SCSIWBlind(tibPtr: Ptr): OSErr;
 INLINE $3F3C,$0009,$A815;
FUNCTION SCSIComplete(VAR stat: INTEGER;VAR message: INTEGER;wait: LONGINT): OSErr;
 INLINE $3F3C,$0004,$A815;
FUNCTION SCSIStat: INTEGER;
 INLINE $3F3C,$000A,$A815;
FUNCTION SCSISelAtn(targetID: INTEGER): OSErr;
 INLINE $3F3C,$000B,$A815;
FUNCTION SCSIMsgIn(VAR message: INTEGER): OSErr;
 INLINE $3F3C,$000C,$A815;
FUNCTION SCSIMsgOut(message: INTEGER): OSErr;
 INLINE $3F3C,$000D,$A815;


{$ENDC} { UsingSCSI }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

