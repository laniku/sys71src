
{
Created: Tuesday, July 30, 1991 at 12:27 PM
 AppleTalk.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: BigBang

	Change History (most recent first):

		 <9>	 10/1/91	MH		Remove bogus comment that crept into the definition of EntityPtr
									due to my error.
		 <8>	 7/30/91	JL		Updated Copyright. Restored Comments.
		 <7>	 1/29/91	JL		Changed socket parameter in DDPOpenSocket back to Byte because it was right.
		 <6>	 1/28/91	LN		Checked in Database Generated File from DSG. Changed socket
									parameter in DDPOpenSocket to INTEGER to match .h file. Changed
									first field in ATQEntry to an ATQEntryPtr to match .h file.
		 <5>	 1/25/91	stb		JDR: synch with .h
		 <4>	 1/19/91	mbs		(jg) Add AppleTalk transition queue event types.  Remove 4th
									parameter to ATPreflightEvent.
		 <3>	  1/3/91	JDR		(dba) Removed LAddAEQ, LRmvAEQ, PCancelATalkClosePrep,
									LAPGetATQ, RemoveHdlBlocks and added ATPKillAllGetReq, ATEvent,
									ATPreFlightEvent. Moved Str32 to Types.p and making it an
									unsigned char.
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT AppleTalk;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingAppleTalk}
{$SETC UsingAppleTalk := 1}

{$I+}
{$SETC AppleTalkIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingOSUtils}
{$I $$Shell(PInterfaces)OSUtils.p}
{$ENDC}
{$SETC UsingIncludes := AppleTalkIncludes}

CONST

{ Driver unit and reference numbers (ADSP is dynamic) }

mppUnitNum = 9;									{ MPP unit number }
atpUnitNum = 10;								{ ATP unit number }
xppUnitNum = 40;								{ XPP unit number }
mppRefNum = -10;								{ MPP reference number }
atpRefNum = -11;								{ ATP reference number }
xppRefNum = -41;								{ XPP reference number }

{ .MPP csCodes }

lookupReply = 242;								{ This command queued to ourself }
writeLAP = 243;									{ Write out LAP packet }
detachPH = 244;									{ Detach LAP protocol handler }
attachPH = 245;									{ Attach LAP protocol handler }
writeDDP = 246;									{ Write out DDP packet }
closeSkt = 247;									{ Close DDP socket }
openSkt = 248;									{ Open DDP socket }
loadNBP = 249;									{ Load NBP command-executing code }
lastResident = 249;								{ Last resident command }
confirmName = 250;								{ Confirm name }
lookupName = 251;								{ Look up name on internet }
removeName = 252;								{ Remove name from Names Table }
registerName = 253;								{ Register name in Names Table }
killNBP = 254;									{ Kill outstanding NBP request }
unloadNBP = 255;								{ Unload NBP command code }
setSelfSend = 256;								{ MPP: Set to allow writes to self }
SetMyZone = 257;								{ Set my zone name }
GetATalkInfo = 258;								{ get AppleTalk information }
ATalkClosePrep = 259;							{ AppleTalk close query }

{ .ATP csCodes }

nSendRequest = 248;								{ NSendRequest code }
relRspCB = 249;									{ Release RspCB }
closeATPSkt = 250;								{ Close ATP socket }
addResponse = 251;								{ Add response code | Require open skt }
sendResponse = 252;								{ Send response code }
getRequest = 253;								{ Get request code }
openATPSkt = 254;								{ Open ATP socket }
sendRequest = 255;								{ Send request code }
relTCB = 256;									{ Release TCB }
killGetReq = 257;								{ Kill GetRequest }
killSendReq = 258;								{ Kill SendRequest }
killAllGetReq = 259;							{ Kill all getRequests for a skt }

{ .XPP csCodes }

openSess = 255;									{ Open session }
closeSess = 254;								{ Close session }
userCommand = 253;								{ User command }
userWrite = 252;								{ User write }
getStatus = 251;								{ Get status }
afpCall = 250;									{ AFP command (buffer has command code) }
getParms = 249;									{ Get parameters }
abortOS = 248;									{ Abort open session request }
closeAll = 247;									{ Close all open sessions }
xCall = 246;									{ .XPP extended calls }

{ Transition Queue transition types }
ATTransOpen = 0;								{AppleTalk has opened}
ATTransClose = 2;								{AppleTalk is about to close}
ATTransClosePrep = 3;							{Is it OK to close AppleTalk ?}
ATTransCancelClose = 4;							{Cancel the ClosePrep transition}

afpByteRangeLock = 1;							{AFPCall command codes}
afpVolClose = 2;								{AFPCall command codes}
afpDirClose = 3;								{AFPCall command codes}
afpForkClose = 4;								{AFPCall command codes}
afpCopyFile = 5;								{AFPCall command codes}
afpDirCreate = 6;								{AFPCall command codes}
afpFileCreate = 7;								{AFPCall command codes}
afpDelete = 8;									{AFPCall command codes}
afpEnumerate = 9;								{AFPCall command codes}
afpFlush = 10;									{AFPCall command codes}
afpForkFlush = 11;								{AFPCall command codes}
afpGetDirParms = 12;							{AFPCall command codes}
afpGetFileParms = 13;							{AFPCall command codes}
afpGetForkParms = 14;							{AFPCall command codes}
afpGetSInfo = 15;								{AFPCall command codes}
afpGetSParms = 16;								{AFPCall command codes}
afpGetVolParms = 17;							{AFPCall command codes}
afpLogin = 18;									{AFPCall command codes}
afpContLogin = 19;								{AFPCall command codes}
afpLogout = 20;									{AFPCall command codes}
afpMapID = 21;									{AFPCall command codes}
afpMapName = 22;								{AFPCall command codes}
afpMove = 23;									{AFPCall command codes}
afpOpenVol = 24;								{AFPCall command codes}
afpOpenDir = 25;								{AFPCall command codes}
afpOpenFork = 26;								{AFPCall command codes}
afpRead = 27;									{AFPCall command codes}
afpRename = 28;									{AFPCall command codes}
afpSetDirParms = 29;							{AFPCall command codes}
afpSetFileParms = 30;							{AFPCall command codes}
afpSetForkParms = 31;							{AFPCall command codes}
afpSetVolParms = 32;							{AFPCall command codes}
afpWrite = 33;									{AFPCall command codes}
afpGetFlDrParms = 34;							{AFPCall command codes}
afpSetFlDrParms = 35;							{AFPCall command codes}
afpDTOpen = 48;									{AFPCall command codes}
afpDTClose = 49;								{AFPCall command codes}
afpGetIcon = 51;								{AFPCall command codes}
afpGtIcnInfo = 52;								{AFPCall command codes}
afpAddAPPL = 53;								{AFPCall command codes}
afpRmvAPPL = 54;								{AFPCall command codes}
afpGetAPPL = 55;								{AFPCall command codes}
afpAddCmt = 56;									{AFPCall command codes}
afpRmvCmt = 57;									{AFPCall command codes}
afpGetCmt = 58;									{AFPCall command codes}
afpAddIcon = 192;								{Special code for ASP Write commands}

xppLoadedBit = 5;								{ XPP bit in PortBUse }
scbMemSize = 192;								{ Size of memory for SCB }
xppFlagClr = 0;									{ Cs for AFPCommandBlock }
xppFlagSet = 128;								{ StartEndFlag & NewLineFlag fields. }

lapSize = 20;
ddpSize = 26;
nbpSize = 26;
atpSize = 56;

atpXOvalue = 32;								{ATP exactly-once bit }
atpEOMvalue = 16;								{ATP End-Of-Message bit }
atpSTSvalue = 8;								{ATP Send-Transmission-Status bit }
atpTIDValidvalue = 2;							{ATP trans. ID valid bit }
atpSendChkvalue = 1;							{ATP send checksum bit }

zipGetLocalZones = 5;
zipGetZoneList = 6;
zipGetMyZone = 7;

LAPMgrPtr = $B18;								{Entry point for LAP Manager}
LAPMgrCall = 2;									{Offset to LAP routines}
LAddAEQ = 23;									{LAPAddATQ routine selector}
LRmvAEQ = 24;									{LAPRmvATQ routine selector}

TYPE
ABCallType = (tLAPRead,tLAPWrite,tDDPRead,tDDPWrite,tNBPLookup,tNBPConfirm,
 tNBPRegister,tATPSndRequest,tATPGetRequest,tATPSdRsp,tATPAddRsp,tATPRequest,
 tATPResponse);

ABProtoType = (lapProto,ddpProto,nbpProto,atpProto);


ABByte = 1..127;


LAPAdrBlock = PACKED RECORD
 dstNodeID: Byte;
 srcNodeID: Byte;
 lapProtType: ABByte;
 END;

ATQEntryPtr = ^ATQEntry;
ATQEntry = RECORD
 qLink: ATQEntryPtr;							{next queue entry}
 qType: INTEGER;								{queue type}
 CallAddr: ProcPtr;								{pointer to your routine}
 END;

AddrBlock = PACKED RECORD
 aNet: INTEGER;
 aNode: Byte;
 aSocket: Byte;
 END;

{ Real definition of EntityName is 3 PACKED strings of any length (32 is just an example). No
offests for Asm since each String address must be calculated by adding length byte to last string ptr.
In Pascal, String(32) will be 34 bytes long since fields never start on an odd byte unless they are 
only a byte long. So this will generate correct looking interfaces for Pascal and C, but they will not
be the same, which is OK since they are not used. }
EntityPtr = ^EntityName;
EntityName = RECORD
 objStr: Str32;
 typeStr: Str32;
 zoneStr: Str32;
 END;

RetransType = PACKED RECORD
 retransInterval: Byte;
 retransCount: Byte;
 END;

BDSElement = RECORD
 buffSize: INTEGER;
 buffPtr: Ptr;
 dataSize: INTEGER;
 userBytes: LONGINT;
 END;


BDSType = ARRAY [0..7] OF BDSElement;
BDSPtr = ^BDSType;
BitMapType = PACKED ARRAY [0..7] OF BOOLEAN;

ABRecPtr = ^ABusRecord;
ABRecHandle = ^ABRecPtr;
ABusRecord = RECORD
 abOpcode: ABCallType;
 abResult: INTEGER;
 abUserReference: LONGINT;
 CASE ABProtoType OF
   lapProto:
  (lapAddress: LAPAdrBlock;
  lapReqCount: INTEGER;
  lapActCount: INTEGER;
  lapDataPtr: Ptr);
   ddpProto:
  (ddpType: Byte;
  ddpSocket: Byte;
  ddpAddress: AddrBlock;
  ddpReqCount: INTEGER;
  ddpActCount: INTEGER;
  ddpDataPtr: Ptr;
  ddpNodeID: Byte);
   nbpProto:
  (nbpEntityPtr: EntityPtr;
  nbpBufPtr: Ptr;
  nbpBufSize: INTEGER;
  nbpDataField: INTEGER;
  nbpAddress: AddrBlock;
  nbpRetransmitInfo: RetransType);
   atpProto:
  (atpSocket: Byte;
  atpAddress: AddrBlock;
  atpReqCount: INTEGER;
  atpDataPtr: Ptr;
  atpRspBDSPtr: BDSPtr;
  atpBitmap: BitMapType;
  atpTransID: INTEGER;
  atpActCount: INTEGER;
  atpUserData: LONGINT;
  atpXO: BOOLEAN;
  atpEOM: BOOLEAN;
  atpTimeOut: Byte;
  atpRetries: Byte;
  atpNumBufs: Byte;
  atpNumRsp: Byte;
  atpBDSSize: Byte;
  atpRspUData: LONGINT;
  atpRspBuf: Ptr;
  atpRspSize: INTEGER);
 END;

AFPCommandBlock = PACKED RECORD
 cmdByte: Byte;
 startEndFlag: Byte;
 forkRefNum: INTEGER;
 rwOffset: LONGINT;
 reqCount: LONGINT;
 newLineFlag: Byte;
 newLineChar: CHAR;
 END;

WDSElement = RECORD
 entryLength: INTEGER;
 entryPtr: Ptr;
 END;

NamesTableEntry = RECORD
 qLink: QElemPtr;
 nteAddress: AddrBlock;
 nteData: PACKED ARRAY [1..100] OF CHAR;
 END;

MPPParmType = (LAPWriteParm,AttachPHParm,DetachPHParm,OpenSktParm,CloseSktParm,
 WriteDDPParm,OpenATPSktParm,CloseATPSktParm,SendRequestParm,GetRequestParm,
 SendResponseParm,AddResponseParm,RelTCBParm,RelRspCBParm,RegisterNameParm,
 LookupNameParm,ConfirmNameParm,RemoveNameParm,SetSelfSendParm,NSendRequestParm,
 KillSendReqParm,KillGetReqParm,KillNBPParm,GetAppleTalkInfoParm,KillAllGetReqParm,
 ATalkClosePrepParm,CancelATalkClosePrepParm);

MPPPBPtr = ^MPPParamBlock;
MPPParamBlock = PACKED RECORD
 qLink: QElemPtr;								{next queue entry}
 qType: INTEGER;								{queue type}
 ioTrap: INTEGER;								{routine trap}
 ioCmdAddr: Ptr;								{routine address}
 ioCompletion: ProcPtr;							{completion routine}
 ioResult: OSErr;								{result code}
 ioNamePtr: StringPtr;							{->filename}
 ioVRefNum: INTEGER;							{volume reference or drive number}
 ioRefNum: INTEGER;								{driver reference number}
 csCode: INTEGER;								{call command code AUTOMATICALLY set}
 CASE MPPParmType OF
   LAPWriteParm:
  (filler0: INTEGER;
  wdsPointer: Ptr);								{->Write Data Structure}
   AttachPHParm,DetachPHParm:
  (protType: Byte;								{ALAP Protocol Type}
  filler1: Byte;
  handler: Ptr);								{->protocol handler routine}
   OpenSktParm,CloseSktParm,WriteDDPParm:
  (socket: Byte;								{socket number}
  checksumFlag: Byte;							{checksum flag}
  listener: Ptr);								{->socket listener routine}
   RegisterNameParm,LookupNameParm,ConfirmNameParm,RemoveNameParm:
  (interval: Byte;								{retry interval}
  count: Byte;									{retry count}
  entityPtr: Ptr;								{->names table element or ->entity name}
  CASE MPPParmType OF
    RegisterNameParm:
   (verifyFlag: Byte;							{set if verify needed}
   filler3: Byte);
    LookupNameParm:
   (retBuffPtr: Ptr;							{->return buffer}
   retBuffSize: INTEGER;						{return buffer size}
   maxToGet: INTEGER;							{matches to get}
   numGotten: INTEGER);							{matched gotten}
    ConfirmNameParm:
   (confirmAddr: AddrBlock;						{->entity}
   newSocket: Byte;								{socket number}
   filler4: Byte));
   SetSelfSendParm:
  (newSelfFlag: Byte;							{self-send toggle flag}
  oldSelfFlag: Byte);							{previous self-send state}
   KillNBPParm:
  (nKillQEl: Ptr);								{ptr to Q element to cancel}
   GetAppleTalkInfoParm:
  (version: INTEGER;							{requested info version}
  varsPtr: Ptr;									{pointer to well known MPP vars}
  DCEPtr: Ptr;									{pointer to MPP DCE}
  portID: INTEGER;								{port number [0..7]}
  configuration: LONGINT;						{32-bit configuration word}
  selfSend: INTEGER;							{non zero if SelfSend enabled}
  netLo: INTEGER;								{low value of network range}
  netHi: INTEGER;								{high value of network range}
  ourAddr: LONGINT;								{our 24-bit AppleTalk address}
  routerAddr: LONGINT;							{24-bit address of (last) router}
  numOfPHs: INTEGER;							{max. number of protocol handlers}
  numOfSkts: INTEGER;							{max. number of static sockets}
  numNBPEs: INTEGER;							{max. concurrent NBP requests}
  nTQueue: Ptr;									{pointer to registered name queue}
  LAlength: INTEGER;							{length in bytes of data link addr}
  linkAddr: Ptr;								{data link address returned}
  zoneName: Ptr);								{zone name returned}
   ATalkClosePrepParm:
  (appName: Ptr);								{pointer to application name in buffer}
 END;

ATPPBPtr = ^ATPParamBlock;
ATPParamBlock = PACKED RECORD
 qLink: QElemPtr;								{next queue entry}
 qType: INTEGER;								{queue type}
 ioTrap: INTEGER;								{routine trap}
 ioCmdAddr: Ptr;								{routine address}
 ioCompletion: ProcPtr;							{completion routine}
 ioResult: OSErr;								{result code}
 userData: LONGINT;								{ATP user bytes}
 reqTID: INTEGER;								{request transaction ID}
 ioRefNum: INTEGER;								{driver reference number}
 csCode: INTEGER;								{Call command code automatically set}
 atpSocket: Byte;								{currBitMap or socket number}
 CASE MPPParmType OF
   SendRequestParm, SendResponseParm, GetRequestParm, AddResponseParm, KillSendReqParm:
  (atpFlags: Byte;								{control information}
  addrBlock: AddrBlock;							{source/dest. socket address}
  reqLength: INTEGER;							{request/response length}
  reqPointer: Ptr;								{-> request/response data}
  bdsPointer: Ptr;								{-> response BDS}
  CASE MPPParmType OF
    SendRequestParm:
   (numOfBuffs: Byte;							{number of responses expected}
   timeOutVal: Byte;							{timeout interval}
   numOfResps: Byte;							{number of responses actually received}
   retryCount: Byte;							{number of retries}
   intBuff: INTEGER;							{used internally for NSendRequest}
   TRelTime: Byte);								{TRelease time for extended send request}
    SendResponseParm:
   (filler0: Byte;								{numOfBuffs}
   bdsSize: Byte;								{number of BDS elements}
   transID: INTEGER);							{transaction ID}
    GetRequestParm:
   (bitMap: Byte;								{bit map}
   filler1: Byte);
    AddResponseParm:
   (rspNum: Byte;								{sequence number}
   filler2: Byte);
    KillSendReqParm:
   (aKillQEl: Ptr));							{ptr to Q element to cancel}
 END;

XPPPrmBlkType = (XPPPrmBlk,ASPSizeBlk,ASPAbortPrm,XCallParam);

XPPSubPrmType = (ASPOpenPrm,ASPSubPrm);

XPPEndPrmType = (AFPLoginPrm,ASPEndPrm);

XPPParmBlkPtr = ^XPPParamBlock;
XPPParamBlock = PACKED RECORD
 qLink: QElemPtr;								{next queue entry}
 qType: INTEGER;								{queue type}
 ioTrap: INTEGER;								{routine trap}
 ioCmdAddr: Ptr;								{routine address}
 ioCompletion: ProcPtr;							{completion routine}
 ioResult: OSErr;								{result code}
 cmdResult: LONGINT;							{command result (ATP user bytes)}
 ioVRefNum: INTEGER;							{volume reference or drive number}
 ioRefNum: INTEGER;								{driver reference number}
 csCode: INTEGER;								{call command code}
 CASE XPPPrmBlkType OF
   ASPAbortPrm:
  (abortSCBPtr: Ptr);							{SCB pointer for AbortOS}
   ASPSizeBlk:
  (aspMaxCmdSize: INTEGER;						{for SPGetParms}
  aspQuantumSize: INTEGER;						{for SPGetParms}
  numSesss: INTEGER);							{for SPGetParms}
   XPPPrmBlk:
  (sessRefnum: INTEGER;							{offset to session refnum}
  aspTimeout: Byte;								{timeout for ATP}
  aspRetry: Byte;								{retry count for ATP}
  CASE XPPSubPrmType OF
    ASPOpenPrm:
   (serverAddr: AddrBlock;						{server address block}
   scbPointer: Ptr;								{SCB pointer}
   attnRoutine: Ptr);							{attention routine pointer}
    ASPSubPrm:
   (cbSize: INTEGER;							{command block size}
   cbPtr: Ptr;									{command block pointer}
   rbSize: INTEGER;								{reply buffer size}
   rbPtr: Ptr;									{reply buffer pointer}
   CASE XPPEndPrmType OF
     AFPLoginPrm:
    (afpAddrBlock: AddrBlock;					{address block in AFP login}
    afpSCBPtr: Ptr;								{SCB pointer in AFP login}
    afpAttnRoutine: Ptr);						{Attn routine pointer in AFP login}
     ASPEndPrm:
    (wdSize: INTEGER;							{write data size}
    wdPtr: Ptr;									{write data pointer}
    ccbStart: ARRAY [0..295] OF Byte)));		{afpWrite max size = 296, else 150}
   XCallParam:
  (xppSubCode: INTEGER;
  xppTimeout: Byte;								{retry interval (seconds)}
  xppRetry: Byte;								{retry count}
  filler1: INTEGER;								{word space for rent.  see the super.}
  zipBuffPtr: Ptr;								{pointer to buffer (must be 578 bytes)}
  zipNumZones: INTEGER;							{no. of zone names in this response}
  zipLastFlag: Byte;							{non-zero if no more zones}
  filler2: Byte;								{filler}
  zipInfoField: PACKED ARRAY [1..70] OF Byte);	{on initial call, set first word to zero}
 END;


FUNCTION OpenXPP(VAR xppRefnum: INTEGER): OSErr;
FUNCTION ASPOpenSession(thePBptr: XPPParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION ASPCloseSession(thePBptr: XPPParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION ASPAbortOS(thePBptr: XPPParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION ASPGetParms(thePBptr: XPPParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION ASPCloseAll(thePBptr: XPPParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION ASPUserWrite(thePBptr: XPPParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION ASPUserCommand(thePBptr: XPPParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION ASPGetStatus(thePBptr: XPPParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION AFPCommand(thePBptr: XPPParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION GetLocalZones(thePBptr: XPPParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION GetZoneList(thePBptr: XPPParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION GetMyZone(thePBptr: XPPParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PAttachPH(thePBptr: MPPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PDetachPH(thePBptr: MPPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PWriteLAP(thePBptr: MPPPBPtr;async: BOOLEAN): OSErr;
FUNCTION POpenSkt(thePBptr: MPPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PCloseSkt(thePBptr: MPPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PWriteDDP(thePBptr: MPPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PRegisterName(thePBptr: MPPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PLookupName(thePBptr: MPPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PConfirmName(thePBptr: MPPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PRemoveName(thePBptr: MPPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PSetSelfSend(thePBptr: MPPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PKillNBP(thePBptr: MPPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PGetAppleTalkInfo(thePBptr: MPPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PATalkClosePrep(thePBptr: MPPPBPtr;async: BOOLEAN): OSErr;
FUNCTION POpenATPSkt(thePBptr: ATPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PCloseATPSkt(thePBPtr: ATPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PSendRequest(thePBPtr: ATPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PGetRequest(thePBPtr: ATPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PSendResponse(thePBPtr: ATPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PAddResponse(thePBPtr: ATPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PRelTCB(thePBPtr: ATPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PRelRspCB(thePBPtr: ATPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PNSendRequest(thePBPtr: ATPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PKillSendReq(thePBPtr: ATPPBPtr;async: BOOLEAN): OSErr;
FUNCTION PKillGetReq(thePBPtr: ATPPBPtr;async: BOOLEAN): OSErr;
FUNCTION ATPKillAllGetReq(thePBPtr: ATPPBPtr;async: BOOLEAN): OSErr;
PROCEDURE BuildLAPwds(wdsPtr: Ptr;dataPtr: Ptr;destHost: INTEGER;prototype: INTEGER;
 frameLen: INTEGER);
PROCEDURE BuildDDPwds(wdsPtr: Ptr;headerPtr: Ptr;dataPtr: Ptr;netAddr: AddrBlock;
 ddpType: INTEGER;dataLen: INTEGER);
PROCEDURE NBPSetEntity(buffer: Ptr;nbpObject: Str32;nbpType: Str32;nbpZone: Str32);
PROCEDURE NBPSetNTE(ntePtr: Ptr;nbpObject: Str32;nbpType: Str32;nbpZone: Str32;
 socket: INTEGER);
FUNCTION GetBridgeAddress: INTEGER;
FUNCTION BuildBDS(buffPtr: Ptr;bdsPtr: Ptr;buffSize: INTEGER): INTEGER;
FUNCTION MPPOpen: OSErr;
FUNCTION MPPClose: OSErr;
FUNCTION LAPOpenProtocol(theLAPType: ABByte;protoPtr: Ptr): OSErr;
FUNCTION LAPCloseProtocol(theLAPType: ABByte): OSErr;
FUNCTION LAPWrite(abRecord: ABRecHandle;async: BOOLEAN): OSErr;
FUNCTION LAPRead(abRecord: ABRecHandle;async: BOOLEAN): OSErr;
FUNCTION LAPRdCancel(abRecord: ABRecHandle): OSErr;
FUNCTION LAPAddATQ(theATQEntry: ATQEntryPtr): OSErr;
FUNCTION LAPRmvATQ(theATQEntry: ATQEntryPtr): OSErr;
FUNCTION DDPOpenSocket(VAR theSocket: Byte;sktListener: Ptr): OSErr;
FUNCTION DDPCloseSocket(theSocket: Byte): OSErr;
FUNCTION DDPRead(abRecord: ABRecHandle;retCksumErrs: BOOLEAN;async: BOOLEAN): OSErr;
FUNCTION DDPWrite(abRecord: ABRecHandle;doChecksum: BOOLEAN;async: BOOLEAN): OSErr;
FUNCTION DDPRdCancel(abRecord: ABRecHandle): OSErr;
FUNCTION ATPLoad: OSErr;
FUNCTION ATPUnload: OSErr;
FUNCTION ATPOpenSocket(addrRcvd: AddrBlock;VAR atpSocket: Byte): OSErr;
FUNCTION ATPCloseSocket(atpSocket: Byte): OSErr;
FUNCTION ATPSndRequest(abRecord: ABRecHandle;async: BOOLEAN): OSErr;
FUNCTION ATPRequest(abRecord: ABRecHandle;async: BOOLEAN): OSErr;
FUNCTION ATPReqCancel(abRecord: ABRecHandle;async: BOOLEAN): OSErr;
FUNCTION ATPGetRequest(abRecord: ABRecHandle;async: BOOLEAN): OSErr;
FUNCTION ATPSndRsp(abRecord: ABRecHandle;async: BOOLEAN): OSErr;
FUNCTION ATPAddRsp(abRecord: ABRecHandle): OSErr;
FUNCTION ATPResponse(abRecord: ABRecHandle;async: BOOLEAN): OSErr;
FUNCTION ATPRspCancel(abRecord: ABRecHandle;async: BOOLEAN): OSErr;
FUNCTION NBPRegister(abRecord: ABRecHandle;async: BOOLEAN): OSErr;
FUNCTION NBPLookup(abRecord: ABRecHandle;async: BOOLEAN): OSErr;
FUNCTION NBPExtract(theBuffer: Ptr;numInBuf: INTEGER;whichOne: INTEGER;
 VAR abEntity: EntityName;VAR address: AddrBlock): OSErr;
FUNCTION NBPConfirm(abRecord: ABRecHandle;async: BOOLEAN): OSErr;
FUNCTION NBPRemove(abEntity: EntityPtr): OSErr;
FUNCTION NBPLoad: OSErr;
FUNCTION NBPUnload: OSErr;
FUNCTION GetNodeAddress(VAR myNode: INTEGER;VAR myNet: INTEGER): OSErr;
FUNCTION IsMPPOpen: BOOLEAN;
FUNCTION IsATPOpen: BOOLEAN;
PROCEDURE ATEvent(event: LONGINT;infoPtr: Ptr);
FUNCTION ATPreFlightEvent(event: LONGINT;cancel: LONGINT;infoPtr: Ptr): OSErr;


{$ENDC} { UsingAppleTalk }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

