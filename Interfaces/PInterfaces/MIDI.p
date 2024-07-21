
{
Created: Saturday, July 27, 1991 at 9:48 PM
 MIDI.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1988-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <5>	11/27/91	MH		change MIDIPortInfo.cList and MIDIIDList.list from [1..100] to
									[1..1]
		 <4>	 7/30/91	JL		Updated Copyright.
		 <3>	 1/29/91	JL		updated MIDI Manager Routines comment.
		<3>		1/29/91		JL		updated MIDI Manager Routines comment.
		 <2>	 1/27/91	LN		Checked in Database generate file from DSG. added VAR to
									Str255's in MIDIGetClientName and MIDIGetPortName.

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT MIDI;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingMIDI}
{$SETC UsingMIDI := 1}

{$I+}
{$SETC MIDIIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := MIDIIncludes}

CONST
midiToolNum = 4;						{tool number of MIDI Manager for SndDispVersion call}
midiMaxNameLen = 31;					{maximum number of characters in port and client names}

{ Time formats }
midiFormatMSec = 0;						{milliseconds}
midiFormatBeats = 1;					{beats}
midiFormat24fpsBit = 2;					{24 frames/sec.}
midiFormat25fpsBit = 3;					{25 frames/sec.}
midiFormat30fpsDBit = 4;				{30 frames/sec. drop-frame}
midiFormat30fpsBit = 5;					{30 frames/sec.}
midiFormat24fpsQF = 6;					{24 frames/sec. longInt format }
midiFormat25fpsQF = 7;					{25 frames/sec. longInt format }
midiFormat30fpsDQF = 8;					{30 frames/sec. drop-frame longInt format }
midiFormat30fpsQF = 9;					{30 frames/sec. longInt format }
midiInternalSync = 0;					{internal sync}
midiExternalSync = 1;					{external sync}

{ Port types}
midiPortTypeTime = 0;					{time port}
midiPortTypeInput = 1;					{input port}
midiPortTypeOutput = 2;					{output port}
midiPortTypeTimeInv = 3;				{invisible time port}

{ OffsetTimes  }
midiGetEverything = $7FFFFFFF;			{get all packets, regardless of time stamps}
midiGetNothing = $80000000;				{get no packets, regardless of time stamps}
midiGetCurrent = $00000000;				{get current packets only}

{    MIDI data and messages are passed in MIDIPacket records (see below).
    The first byte of every MIDIPacket contains a set of flags
   
    bits 0-1    00 = new MIDIPacket, not continued
                     01 = begining of continued MIDIPacket
                     10 = end of continued MIDIPacket
                    11 = continuation
    bits 2-3     reserved
  
    bits 4-6      000 = packet contains MIDI data
   
                     001 = packet contains MIDI Manager message
   
    bit 7              0 = MIDIPacket has valid stamp
                        1 = stamp with current clock }
midiContMask = $03;
midiNoCont = $00;
midiStartCont = $01;
midiMidCont = $03;
midiEndCont = $02;
midiTypeMask = $70;
midiMsgType = $00;
midiMgrType = $10;
midiTimeStampMask = $80;
midiTimeStampCurrent = $80;
midiTimeStampValid = $00;

{    MIDI Manager MIDIPacket command words (the first word in the data field
    for midiMgrType messages) }
midiOverflowErr = $0001;
midiSCCErr = $0002;
midiPacketErr = $0003;
midiMaxErr = $00FF;						{all command words less than this value  are error indicators}

{ Valid results to be returned by readHooks }
midiKeepPacket = 0;
midiMorePacket = 1;
midiNoMorePacket = 2;

{ Errors: }
midiNoClientErr = -250;					{no client with that ID found}
midiNoPortErr = -251;					{no port with that ID found}
midiTooManyPortsErr = -252;				{too many ports already installed in the system}
midiTooManyConsErr = -253;				{too many connections made}
midiVConnectErr = -254;					{pending virtual connection created}
midiVConnectMade = -255;				{pending virtual connection resolved}
midiVConnectRmvd = -256;				{pending virtual connection removed}
midiNoConErr = -257;					{no connection exists between specified ports}
midiWriteErr = -258;					{MIDIWritePacket couldn't write to all connected ports}
midiNameLenErr = -259;					{name supplied is longer than 31 characters}
midiDupIDErr = -260;					{duplicate client ID}
midiInvalidCmdErr = -261;				{command not supported for port type}

{     Driver calls: }
midiOpenDriver = 1;
midiCloseDriver = 2;

TYPE
MIDIPacketPtr = ^MIDIPacket;
MIDIPacket = PACKED RECORD
 flags: Byte;
 len: Byte;
 tStamp: LONGINT;
 data: PACKED ARRAY [0..248] OF Byte;
 END;

MIDIClkInfo = RECORD
 sync: INTEGER;							{synchronization external/internal}
 curTime: LONGINT;						{current value of port's clock}
 format: INTEGER;						{time code format}
 END;

MIDIIDRec = RECORD
 clientID: OSType;
 portID: OSType;
 END;

MIDIPortInfoPtr = ^MIDIPortInfo;
MIDIPortInfoHdl = ^MIDIPortInfoPtr;
MIDIPortInfo = RECORD
 portType: INTEGER;						{type of port}
 timeBase: MIDIIDRec;					{MIDIIDRec for time base}
 numConnects: INTEGER;					{number of connections}
 cList: ARRAY [1..1] OF MIDIIDRec;		{-r or $R- permits access to [1..numConnects] of MIDIIDRec}
 END;

MIDIPortParamsPtr = ^MIDIPortParams;
MIDIPortParams = RECORD
 portID: OSType;						{ID of port, unique within client}
 portType: INTEGER;						{Type of port - input, output, time, etc.}
 timeBase: INTEGER;						{refnum of time base, 0 if none}
 offsetTime: LONGINT;					{offset for current time stamps}
 readHook: Ptr;							{routine to call when input data is valid}
 refCon: LONGINT;						{refcon for port (for client use)}
 initClock: MIDIClkInfo;				{initial settings for a time base}
 name: Str255;							{name of the port, This is a real live string, not a ptr.}
 END;

MIDIIDListPtr = ^MIDIIDList;
MIDIIDListHdl = ^MIDIIDListPtr;
MIDIIDList = RECORD
 numIDs: INTEGER;
 list: ARRAY [1..1] OF OSType;			{ -r or $R- permits access to [1..numIDs] of OSType }
 END;


{
     Prototype Declarations for readHook and timeProc
    
     FUNCTION myReadHook(myPacket: MIDIPacketPtr; myRefCon: LONGINT) : INTEGER;
     PROCEDURE myTimeProc(curTime: LONGINT; myRefCon: LONGINT);
}

FUNCTION SndDispVersion(toolnum: INTEGER): LONGINT;
FUNCTION MIDISignIn(clientID: OSType;refCon: LONGINT;icon: Handle;name: Str255): OSErr;
 INLINE $203C,$0004,midiToolNum,$A800;
PROCEDURE MIDISignOut(clientID: OSType);
 INLINE $203C,$0008,midiToolNum,$A800;
FUNCTION MIDIGetClients: MIDIIDListHdl;
 INLINE $203C,$000C,midiToolNum,$A800;
PROCEDURE MIDIGetClientName(clientID: OSType;VAR name: Str255);
 INLINE $203C,$0010,midiToolNum,$A800;
PROCEDURE MIDISetClientName(clientID: OSType;name: Str255);
 INLINE $203C,$0014,midiToolNum,$A800;
FUNCTION MIDIGetPorts(clientID: OSType): MIDIIDListHdl;
 INLINE $203C,$0018,midiToolNum,$A800;
FUNCTION MIDIAddPort(clientID: OSType;BufSize: INTEGER;VAR refnum: INTEGER;
 init: MIDIPortParamsPtr): OSErr;
 INLINE $203C,$001C,midiToolNum,$A800;
FUNCTION MIDIGetPortInfo(clientID: OSType;portID: OSType): MIDIPortInfoHdl;
 INLINE $203C,$0020,midiToolNum,$A800;
FUNCTION MIDIConnectData(srcClID: OSType;srcPortID: OSType;dstClID: OSType;
 dstPortID: OSType): OSErr;
 INLINE $203C,$0024,midiToolNum,$A800;
FUNCTION MIDIUnConnectData(srcClID: OSType;srcPortID: OSType;dstClID: OSType;
 dstPortID: OSType): OSErr;
 INLINE $203C,$0028,midiToolNum,$A800;
FUNCTION MIDIConnectTime(srcClID: OSType;srcPortID: OSType;dstClID: OSType;
 dstPortID: OSType): OSErr;
 INLINE $203C,$002C,midiToolNum,$A800;
FUNCTION MIDIUnConnectTime(srcClID: OSType;srcPortID: OSType;dstClID: OSType;
 dstPortID: OSType): OSErr;
 INLINE $203C,$0030,midiToolNum,$A800;
PROCEDURE MIDIFlush(refnum: INTEGER);
 INLINE $203C,$0034,midiToolNum,$A800;
FUNCTION MIDIGetReadHook(refnum: INTEGER): ProcPtr;
 INLINE $203C,$0038,midiToolNum,$A800;
PROCEDURE MIDISetReadHook(refnum: INTEGER;hook: ProcPtr);
 INLINE $203C,$003C,midiToolNum,$A800;
PROCEDURE MIDIGetPortName(clientID: OSType;portID: OSType;VAR name: Str255);
 INLINE $203C,$0040,midiToolNum,$A800;
PROCEDURE MIDISetPortName(clientID: OSType;portID: OSType;name: Str255);
 INLINE $203C,$0044,midiToolNum,$A800;
PROCEDURE MIDIWakeUp(refnum: INTEGER;time: LONGINT;period: LONGINT;timeProc: ProcPtr);
 INLINE $203C,$0048,midiToolNum,$A800;
PROCEDURE MIDIRemovePort(refnum: INTEGER);
 INLINE $203C,$004C,midiToolNum,$A800;
FUNCTION MIDIGetSync(refnum: INTEGER): INTEGER;
 INLINE $203C,$0050,midiToolNum,$A800;
PROCEDURE MIDISetSync(refnum: INTEGER;sync: INTEGER);
 INLINE $203C,$0054,midiToolNum,$A800;
FUNCTION MIDIGetCurTime(refnum: INTEGER): LONGINT;
 INLINE $203C,$0058,midiToolNum,$A800;
PROCEDURE MIDISetCurTime(refnum: INTEGER;time: LONGINT);
 INLINE $203C,$005C,midiToolNum,$A800;
PROCEDURE MIDIStartTime(refnum: INTEGER);
 INLINE $203C,$0060,midiToolNum,$A800;
PROCEDURE MIDIStopTime(refnum: INTEGER);
 INLINE $203C,$0064,midiToolNum,$A800;
PROCEDURE MIDIPoll(refnum: INTEGER;offsetTime: LONGINT);
 INLINE $203C,$0068,midiToolNum,$A800;
FUNCTION MIDIWritePacket(refnum: INTEGER;packet: MIDIPacketPtr): OSErr;
 INLINE $203C,$006C,midiToolNum,$A800;
FUNCTION MIDIWorldChanged(clientID: OSType): BOOLEAN;
 INLINE $203C,$0070,midiToolNum,$A800;
FUNCTION MIDIGetOffsetTime(refnum: INTEGER): LONGINT;
 INLINE $203C,$0074,midiToolNum,$A800;
PROCEDURE MIDISetOffsetTime(refnum: INTEGER;offsetTime: LONGINT);
 INLINE $203C,$0078,midiToolNum,$A800;
FUNCTION MIDIConvertTime(srcFormat: INTEGER;dstFormat: INTEGER;time: LONGINT): LONGINT;
 INLINE $203C,$007C,midiToolNum,$A800;
FUNCTION MIDIGetRefCon(refnum: INTEGER): LONGINT;
 INLINE $203C,$0080,midiToolNum,$A800;
PROCEDURE MIDISetRefCon(refnum: INTEGER;refCon: LONGINT);
 INLINE $203C,$0084,midiToolNum,$A800;
FUNCTION MIDIGetClRefCon(clientID: OSType): LONGINT;
 INLINE $203C,$0088,midiToolNum,$A800;
PROCEDURE MIDISetClRefCon(clientID: OSType;refCon: LONGINT);
 INLINE $203C,$008C,midiToolNum,$A800;
FUNCTION MIDIGetTCFormat(refnum: INTEGER): INTEGER;
 INLINE $203C,$0090,midiToolNum,$A800;
PROCEDURE MIDISetTCFormat(refnum: INTEGER;format: INTEGER);
 INLINE $203C,$0094,midiToolNum,$A800;
PROCEDURE MIDISetRunRate(refnum: INTEGER;rate: INTEGER;time: LONGINT);
 INLINE $203C,$0098,midiToolNum,$A800;
FUNCTION MIDIGetClientIcon(clientID: OSType): Handle;
 INLINE $203C,$009C,midiToolNum,$A800;


{$ENDC} { UsingMIDI }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

