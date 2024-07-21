
{
Created: Tuesday, July 30, 1991 at 11:02 AM
 ADSP.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1986-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <4>	 7/30/91	JL		Updated Copyright. Restored comments.
		 <3>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <2>	10/10/90	JL		Adding constants for consistency with C header.

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT ADSP;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingADSP}
{$SETC UsingADSP := 1}

{$I+}
{$SETC ADSPIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingAppleTalk}
{$I $$Shell(PInterfaces)AppleTalk.p}
{$ENDC}
{$SETC UsingIncludes := ADSPIncludes}

CONST

{ driver control ioResults }
errRefNum = -1280;							{ bad connection refNum }
errAborted = -1279;							{ control call was aborted }
errState = -1278;							{ bad connection state for this operation }
errOpening = -1277;							{ open connection request failed }
errAttention = -1276;						{ attention message too long }
errFwdReset = -1275;						{ read terminated by forward reset }
errDSPQueueSize = -1274;					{ DSP Read/Write Queue Too small }
errOpenDenied = -1273;						{ open connection request was denied }

{driver control csCodes}
dspInit = 255;								{ create a new connection end }
dspRemove = 254;							{ remove a connection end }
dspOpen = 253;								{ open a connection }
dspClose = 252;								{ close a connection }
dspCLInit = 251;							{ create a connection listener }
dspCLRemove = 250;							{ remove a connection listener }
dspCLListen = 249;							{ post a listener request }
dspCLDeny = 248;							{ deny an open connection request }
dspStatus = 247;							{ get status of connection end }
dspRead = 246;								{ read data from the connection }
dspWrite = 245;								{ write data on the connection }
dspAttention = 244;							{ send an attention message }
dspOptions = 243;							{ set connection end options }
dspReset = 242;								{ forward reset the connection }
dspNewCID = 241;							{ generate a cid for a connection end }

{ connection opening modes }
ocRequest = 1;								{ request a connection with remote }
ocPassive = 2;								{ wait for a connection request from remote }
ocAccept = 3;								{ accept request as delivered by listener }
ocEstablish = 4;							{ consider connection to be open }

{ connection end states }
sListening = 1;								{ for connection listeners }
sPassive = 2;								{ waiting for a connection request from remote }
sOpening = 3;								{ requesting a connection with remote }
sOpen = 4;									{ connection is open }
sClosing = 5;								{ connection is being torn down }
sClosed = 6;								{ connection end state is closed }

{ client event flags }
eClosed = $80;								{ received connection closed advice }
eTearDown = $40;							{ connection closed due to broken connection }
eAttention = $20;							{ received attention message }
eFwdReset = $10;							{ received forward reset advice }

{ miscellaneous constants }
attnBufSize = 570;							{ size of client attention buffer }
minDSPQueueSize = 100;						{ Minimum size of receive or send Queue }

TYPE
{ connection control block }
TPCCB = ^TRCCB;
TRCCB = PACKED RECORD
 ccbLink: TPCCB;							{ link to next ccb }
 refNum: INTEGER;							{ user reference number }
 state: INTEGER;							{ state of the connection end }
 userFlags: Byte;							{ flags for unsolicited connection events }
 localSocket: Byte;							{ socket number of this connection end }
 remoteAddress: AddrBlock;					{ internet address of remote end }
 attnCode: INTEGER;							{ attention code received }
 attnSize: INTEGER;							{ size of received attention data }
 attnPtr: Ptr;								{ ptr to received attention data }
 reserved: PACKED ARRAY [1..220] OF Byte;	{ adsp internal use }
 END;

{ ADSP CntrlParam ioQElement , driver control call parameter block}
DSPPBPtr = ^DSPParamBlock;
DSPParamBlock = PACKED RECORD
 qLink: QElemPtr;
 qType: INTEGER;
 ioTrap: INTEGER;
 ioCmdAddr: Ptr;
 ioCompletion: ProcPtr;
 ioResult: OSErr;
 ioNamePtr: StringPtr;
 ioVRefNum: INTEGER;
 ioCRefNum: INTEGER;						{ adsp driver refNum }
 csCode: INTEGER;							{ adsp driver control code }
 qStatus: LONGINT;							{ adsp internal use }
 ccbRefNum: INTEGER;						{ refnum of ccb }
 CASE INTEGER OF
   dspInit,dspCLInit:
  (ccbPtr: TPCCB;							{pointer to connection control block}
   userRoutine: ProcPtr;					{client routine to call on event}
   sendQSize: INTEGER;						{size of send queue (0..64K bytes)}
   sendQueue:  Ptr;							{client passed send queue buffer}
   recvQSize: INTEGER;						{size of receive queue (0..64K bytes)}
   recvQueue: Ptr;							{client passed receive queue buffer}
   attnPtr: Ptr;							{client passed receive attention buffer}
   localSocket: Byte;						{local socket number}
   filler1: Byte;							{filler for proper byte alignment}
    );
    dspOpen,dspCLListen,dspCLDeny:
   (localCID: INTEGER;						{local connection id}
    remoteCID: INTEGER;						{remote connection id}
    remoteAddress: AddrBlock;				{address of remote end}
    filterAddress: AddrBlock;				{address filter}
    sendSeq: LONGINT;						{local send sequence number}
    sendWindow: INTEGER;					{send window size}
    recvSeq: LONGINT;						{receive sequence number}
    attnSendSeq: LONGINT;					{attention send sequence number}
    attnRecvSeq: LONGINT;					{attention receive sequence number}
    ocMode: Byte;							{open connection mode}
    ocInterval: Byte;						{open connection request retry interval}
    ocMaximum: Byte;						{open connection request retry maximum}
    filler2: Byte;							{filler for proper byte alignment}
     );
     dspClose,dspRemove:
    (abort: Byte;							{abort connection immediately if non-zero}
     filler3: Byte;							{filler for proper byte alignment}
      );
      dspStatus:
     (statusCCB: TPCCB;						{pointer to ccb}
      sendQPending: INTEGER;				{pending bytes in send queue}
      sendQFree: INTEGER;					{available buffer space in send queue}
      recvQPending: INTEGER;				{pending bytes in receive queue}
      recvQFree: INTEGER;					{available buffer space in receive queue}
       );
       dspRead,dspWrite:
      (reqCount: INTEGER;					{requested number of bytes}
       actCount: INTEGER;					{actual number of bytes}
       dataPtr: Ptr;						{pointer to data buffer}
       eom: Byte;							{indicates logical end of message}
       flush: Byte;							{send data now}
        );
        dspAttention:
       (attnCode: INTEGER;					{client attention code}
        attnSize: INTEGER;					{size of attention data}
        attnData: Ptr;						{pointer to attention data}
        attnInterval: Byte;					{retransmit timer in 10-tick intervals}
        filler4: Byte;						{filler for proper byte alignment}
         );
         dspOptions:
        (sendBlocking: INTEGER;				{quantum for data packets}
         sendTimer: Byte;					{send timer in 10-tick intervals}
         rtmtTimer: Byte;					{retransmit timer in 10-tick intervals}
         badSeqMax: Byte;					{threshold for sending retransmit advice}
         useCheckSum: Byte;					{use ddp packet checksum}
          );
          dspNewCID:
         (newCID: INTEGER;					{new connection id returned}
           );
 END;



{$ENDC} { UsingADSP }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

