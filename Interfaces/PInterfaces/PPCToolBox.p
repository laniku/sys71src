
{
Created: Wednesday, July 24, 1991 at 3:40 PM
    PPCToolBox.p
    Pascal Interface to the Macintosh Libraries

        Copyright Apple Computer, Inc.    1989-1992
        All rights reserved

	Change History (most recent first):

		<28>	 6/26/92	DCL		Miner Formatting Changes. Digging deep for things to do.
		<27>	 4/17/92	JSM		Take out StoreAndForward revisions, those changes are not
									supported by PPC for CubeE.
		<26>	 7/24/91	JL		Fixed the build. PPCOpenPBRec's field noAuthRequired was
									resFlag.
		<25>	 7/24/91	JL		Updated Copyright.  Restored comments.  Roll in StoreAndForward
									Revisions
		<24>	 1/30/91	JL		Checked in database generated file from dsg.
		<23>	 11/8/90	EMT		<stb>Move error constants to Errors.p
		<22>	10/24/90	EMT		Fix Interface errors, Str32's should be used where Str255's are
									in some places
		<21>	10/18/90	JL		OOps checking in the file again.
		<20>	10/17/90	JL		Puting constants back in order for ease of use.
		<19>	10/10/90	JL		Fixing Inlines for Sync and Async calls.
		<18>	 10/3/90	JAL		Added Sync and Async calls and added inline for PPCInit. Cleaned up things
		<17>	 9/18/90	EMT		Change noUserNameErr to the more appropriate noMachineNameErr
									nomenclature.
		<16>	 9/15/90	ngk		Change to new, way-cool constants and field names
	   								#### warning this was a major change ####
									
		<15>	  4/7/90	ngk		Changed Size to LONGINT, since Memory.p is not auto-included.
		<14>	 3/20/90	S		Add requestType parameter to PPCInform call and Add reservedFlag
									fields to few calls.
		<13>	 3/19/90	JSM		PPCBrowser now returns PortInfo instead of PortName.
		<12>	 2/27/90	S		Remove authRequest parameter from PPCOpen Call & include
									guestNotAllowedErr.
		<11>	 2/19/90	EMT		Fixed syntax error in PPCBrowser interface.
		<10>	 2/19/90	JSM		Add PPCBrowser interface.
		 <7>	 1/30/90	S		Added Some Error Codes.
		 <6>	 1/10/90	S		Include Definition For StartSecureSession Function.
		 <5>	  1/9/90	S		Fixed Missing Colons.
		 <4>	  1/9/90	S		Changes in Parameter Blocks.
		 <4>	  1/9/90	S		Some Minor Fixes and Change in ParameteBlocks.
	   <1.1>	 11/3/89	ngk		Fixed bug in error codes.
	   <1.0>	 11/2/89	ngk		initial submission to EASE
	   
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT PPCToolBox;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingPPCToolBox}
{$SETC UsingPPCToolBox := 1}

{$I+}
{$SETC PPCToolBoxIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingAppleTalk}
{$I $$Shell(PInterfaces)AppleTalk.p}
{$ENDC}
{$IFC UNDEFINED UsingMemory}
{$I $$Shell(PInterfaces)Memory.p}
{$ENDC}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := PPCToolBoxIncludes}

TYPE
PPCServiceType = SignedByte;

CONST
ppcServiceRealTime = 1;

TYPE
PPCLocationKind = INTEGER;

CONST
ppcNoLocation = 0;                          { There is no PPCLocName }
ppcNBPLocation = 1;                         { Use AppleTalk NBP      }
ppcNBPTypeLocation = 2;                     { Used for specifying a location name type during PPCOpen only }

TYPE
PPCPortKinds = INTEGER;

CONST
ppcByCreatorAndType = 1;					{ Port type is specified as colloquial Mac creator and type }
ppcByString = 2;							{ Port type is in pascal string format }

TYPE
PPCSessionOrigin = SignedByte;              { Values returned for request field in PPCInform call }

CONST

{ Values returned for requestType field in PPCInform call }
ppcLocalOrigin = 1;                         { session originated from this machine }
ppcRemoteOrigin = 2;                        { session originated from remote machine }

TYPE
PPCPortRefNum = INTEGER;
PPCSessRefNum = LONGINT;

PPCPortPtr = ^PPCPortRec;
PPCPortRec = RECORD
 nameScript: ScriptCode;					{ script of name }
 name: Str32;								{ name of port as seen in browser }
 portKindSelector: PPCPortKinds;			{ which variant }
 CASE PPCPortKinds OF
   ppcByString:
  (portTypeStr: Str32);
   ppcByCreatorAndType:
  (portCreator: OSType;
  portType: OSType);
 END;

LocationNamePtr = ^LocationNameRec;
LocationNameRec = RECORD
 locationKindSelector: PPCLocationKind;		{ which variant }
 CASE PPCLocationKind OF
   ppcNBPLocation:
  (nbpEntity: EntityName);					{ NBP name entity }
   ppcNBPTypeLocation:
  (nbpType: Str32);							{ just the NBP type string, for PPCOpen }
 END;

PortInfoPtr = ^PortInfoRec;
PortInfoRec = RECORD
 filler1: SignedByte;
 authRequired: BOOLEAN;
 name: PPCPortRec;
 END;


PortInfoArrayPtr = ^PortInfoArray;
PortInfoArray = ARRAY [0..0] OF PortInfoRec;
{ Procedures you will need to write }
PPCFilterProcPtr = ProcPtr;					{ FUNCTION MyPortFilter(locationName: LocationNameRec; thePortInfo: PortInfoRec): BOOLEAN; }
PPCCompProcPtr = ProcPtr;					{ PROCEDURE MyCompletionRoutine(pb: PPCParamBlockPtr); }

PPCOpenPBPtr = ^PPCOpenPBRec;
PPCOpenPBRec = RECORD
    qLink:   Ptr;     						{ reserved }
    csCode:   INTEGER;    					{ reserved }
    intUse:   INTEGER;    					{ reserved }
    intUsePtr:  Ptr;     					{ reserved }
    ioCompletion: PPCCompProcPtr;
    ioResult:  OSErr;
    reserved:  ARRAY [1..5] OF LONGINT;		{ reserved }
    portRefNum:  PPCPortRefNum;   			{ 38 <--   Port Reference          }   
    filler1:  LONGINT;     
    serviceType: PPCServiceType;   			{ 44 -->   Bit field describing the requested port service  } 
    resFlag:  SignedByte;    				{ 45 -->   Must be set to 0          }
    portName:  PPCPortPtr;    				{ 46 -->   PortName for PPC           }
    locationName: LocationNamePtr;  		{ 50 -->   If NBP  Registration is required       }
    networkVisible: BOOLEAN;     			{ 54 -->   make this network visible on network      }
    nbpRegistered: BOOLEAN;     			{ 55 <--   The given location name was registered on the network }
   END;

PPCInformPBPtr = ^PPCInformPBRec;
PPCInformPBRec = RECORD
 qLink: Ptr;								{ reserved }
 csCode: INTEGER;							{ reserved }
 intUse: INTEGER;							{ reserved }
 intUsePtr: Ptr;							{ reserved }
 ioCompletion: PPCCompProcPtr;
 ioResult: OSErr;
 reserved: ARRAY [1..5] OF LONGINT;			{ reserved }
 portRefNum: PPCPortRefNum;					{ 38 -->   Port Identifier }
 sessRefNum: PPCSessRefNum;					{ 40 <--   Session Reference }
 serviceType: PPCServiceType;				{ 44 <--   Status Flags for type of session, local, remote }
 autoAccept: BOOLEAN;						{ 45 -->   if true session will be accepted automatically }
 portName: PPCPortPtr;						{ 46 -->   Buffer for Source PPCPortRec }
 locationName: LocationNamePtr;				{ 50 -->   Buffer for Source LocationNameRec }
 userName: StringPtr;						{ 54 -->   Buffer for Soure user's name trying to link. }
 userData: LONGINT;							{ 58 <--   value included in PPCStart's userData }
 requestType: PPCSessionOrigin;				{ 62 <--   Local or Network }
 END;

PPCStartPBPtr = ^PPCStartPBRec;
PPCStartPBRec = RECORD
 qLink: Ptr;								{ reserved }
 csCode: INTEGER;							{ reserved }
 intUse: INTEGER;							{ reserved }
 intUsePtr: Ptr;							{ reserved }
 ioCompletion: PPCCompProcPtr;
 ioResult: OSErr;
 reserved: ARRAY [1..5] OF LONGINT;			{ reserved }
 portRefNum: PPCPortRefNum;					{ 38 -->   Port Identifier }
 sessRefNum: PPCSessRefNum;					{ 40 <--   Session Reference }
 serviceType: PPCServiceType;				{ 44 <--   Actual service method (realTime) }
 resFlag: SignedByte;						{ 45 -->   Must be set to 0  }
 portName: PPCPortPtr;						{ 46 -->   Destination portName }
 locationName: LocationNamePtr;				{ 50 -->   NBP or NAS style service location name }
 rejectInfo: LONGINT;						{ 54 <--   reason for rejecting the session request }
 userData: LONGINT;							{ 58 -->   Copied to destination PPCInform parameter block }
 userRefNum: LONGINT;						{ 62 -->   userRefNum (obtained during login process)  }
 END;

PPCAcceptPBPtr = ^PPCAcceptPBRec;
PPCAcceptPBRec = RECORD
 qLink: Ptr;								{ reserved }
 csCode: INTEGER;							{ reserved }
 intUse: INTEGER;							{ reserved }
 intUsePtr: Ptr;							{ reserved }
 ioCompletion: PPCCompProcPtr;
 ioResult: OSErr;
 reserved: ARRAY [1..5] OF LONGINT;			{ reserved }
 filler1: INTEGER;
 sessRefNum: PPCSessRefNum;					{ 40 -->   Session Reference }
 END;

PPCRejectPBPtr = ^PPCRejectPBRec;
PPCRejectPBRec = RECORD
 qLink: Ptr;								{ reserved }
 csCode: INTEGER;							{ reserved }
 intUse: INTEGER;							{ reserved }
 intUsePtr: Ptr;							{ reserved }
 ioCompletion: PPCCompProcPtr;
 ioResult: OSErr;
 reserved: ARRAY [1..5] OF LONGINT;			{ reserved }
 filler1: INTEGER;
 sessRefNum: PPCSessRefNum;					{ 40 -->   Session Reference }
 filler2: INTEGER;
 filler3: LONGINT;
 filler4: LONGINT;
 rejectInfo: LONGINT;						{ 54 -->   reason for rejecting the session request  }
 END;

PPCWritePBPtr = ^PPCWritePBRec;
PPCWritePBRec = RECORD
 qLink: Ptr;								{ reserved }
 csCode: INTEGER;							{ reserved }
 intUse: INTEGER;							{ reserved }
 intUsePtr: Ptr;							{ reserved }
 ioCompletion: PPCCompProcPtr;
 ioResult: OSErr;
 reserved: ARRAY [1..5] OF LONGINT;			{ reserved }
 filler1: INTEGER;
 sessRefNum: PPCSessRefNum;					{ 40 -->   Session Reference }
 bufferLength: Size;						{ 44 -->   Length of the message buffer }
 actualLength: Size;						{ 48 <--   Actual Length Written }
 bufferPtr: Ptr;							{ 52 -->   Pointer to message buffer }
 more: BOOLEAN;								{ 56 -->   if more data in this block will be written }
 filler2: SignedByte;
 userData: LONGINT;							{ 58 -->   Message block userData Uninterpreted by PPC }
 blockCreator: OSType;						{ 62 -->   Message block creator Uninterpreted by PPC }
 blockType: OSType;							{ 66 -->   Message block type Uninterpreted by PPC }
 END;

PPCReadPBPtr = ^PPCReadPBRec;
PPCReadPBRec = RECORD
 qLink: Ptr;								{ reserved }
 csCode: INTEGER;							{ reserved }
 intUse: INTEGER;							{ reserved }
 intUsePtr: Ptr;							{ reserved }
 ioCompletion: PPCCompProcPtr;
 ioResult: OSErr;
 reserved: ARRAY [1..5] OF LONGINT;			{ reserved }
 filler1: INTEGER;
 sessRefNum: PPCSessRefNum;					{ 40 -->   Session Reference }
 bufferLength: Size;						{ 44 -->   Length of the message buffer }
 actualLength: Size;						{ 48 <--   Actual length read }
 bufferPtr: Ptr;							{ 52 -->   Pointer to message buffer }
 more: BOOLEAN;								{ 56 <--   if true more data in this block to be read }
 filler2: SignedByte;
 userData: LONGINT;							{ 58 <--   Message block userData Uninterpreted by PPC }
 blockCreator: OSType;						{ 62 <--   Message block creator Uninterpreted by PPC }
 blockType: OSType;							{ 66 <--   Message block type Uninterpreted by PPC }
 END;

PPCEndPBPtr = ^PPCEndPBRec;
PPCEndPBRec = RECORD
 qLink: Ptr;								{ reserved }
 csCode: INTEGER;							{ reserved }
 intUse: INTEGER;							{ reserved }
 intUsePtr: Ptr;							{ reserved }
 ioCompletion: PPCCompProcPtr;
 ioResult: OSErr;
 reserved: ARRAY [1..5] OF LONGINT;			{ reserved }
 filler1: INTEGER;
 sessRefNum: PPCSessRefNum;					{ 40 -->   Session Reference }
 END;

PPCClosePBPtr = ^PPCClosePBRec;
PPCClosePBRec = RECORD
 qLink: Ptr;								{ reserved }
 csCode: INTEGER;							{ reserved }
 intUse: INTEGER;							{ reserved }
 intUsePtr: Ptr;							{ reserved }
 ioCompletion: PPCCompProcPtr;
 ioResult: OSErr;
 reserved: ARRAY [1..5] OF LONGINT;			{ reserved }
 portRefNum: PPCPortRefNum;					{ 38 -->   Port Identifier }
 END;

IPCListPortsPBPtr = ^IPCListPortsPBRec;
IPCListPortsPBRec = RECORD
 qLink: Ptr;								{ reserved }
 csCode: INTEGER;							{ reserved }
 intUse: INTEGER;							{ reserved }
 intUsePtr: Ptr;							{ reserved }
 ioCompletion: PPCCompProcPtr;
 ioResult: OSErr;
 reserved: ARRAY [1..5] OF LONGINT;			{ reserved }
 filler1: INTEGER;
 startIndex: INTEGER;						{ 40 -->   Start Index }
 requestCount: INTEGER;						{ 42 -->   Number of entries to be returned }
 actualCount: INTEGER;						{ 44 <--   Actual Number of entries to be returned }
 portName: PPCPortPtr;						{ 46 -->   PortName Match }
 locationName: LocationNamePtr;				{ 50 -->   NBP or NAS type name to locate the Port Location }
 bufferPtr: PortInfoArrayPtr;				{ 54 -->   Pointer to a buffer requestCount*sizeof(PortInfo) bytes big }
 END;

PPCParamBlockPtr = ^PPCParamBlockRec;
PPCParamBlockRec = RECORD
     CASE Integer OF
      0: (openParam:   PPCOpenPBRec);
      1: (informParam: PPCInformPBRec);
      2: (startParam:  PPCStartPBRec);
      3: (acceptParam: PPCAcceptPBRec);
      4: (rejectParam: PPCRejectPBRec);
      5: (writeParam:  PPCWritePBRec);
      6: (readParam:   PPCReadPBRec);
      7: (endParam:  PPCEndPBRec);
      8: (closeParam:  PPCClosePBRec);
      9: (listPortsParam: IPCListPortsPBRec);
    END;



{  PPC Calling Conventions  }
FUNCTION PPCInit: OSErr;
 INLINE $7000,$A0DD,$3E80;
FUNCTION PPCOpen(pb: PPCOpenPBPtr;async: BOOLEAN): OSErr;
FUNCTION PPCOpenSync(pb: PPCOpenPBPtr): OSErr;
 INLINE $205F,$7001,$A0DD,$3E80;
FUNCTION PPCOpenAsync(pb: PPCOpenPBPtr): OSErr;
 INLINE $205F,$7001,$A4DD,$3E80;
FUNCTION PPCInform(pb: PPCInformPBPtr;async: BOOLEAN): OSErr;
FUNCTION PPCInformSync(pb: PPCInformPBPtr): OSErr;
 INLINE $205F,$7003,$A0DD,$3E80;
FUNCTION PPCInformAsync(pb: PPCInformPBPtr): OSErr;
 INLINE $205F,$7003,$A4DD,$3E80;
FUNCTION PPCStart(pb: PPCStartPBPtr;async: BOOLEAN): OSErr;
FUNCTION PPCStartSync(pb: PPCStartPBPtr): OSErr;
 INLINE $205F,$7002,$A0DD,$3E80;
FUNCTION PPCStartAsync(pb: PPCStartPBPtr): OSErr;
 INLINE $205F,$7002,$A4DD,$3E80;
FUNCTION PPCAccept(pb: PPCAcceptPBPtr;async: BOOLEAN): OSErr;
FUNCTION PPCAcceptSync(pb: PPCAcceptPBPtr): OSErr;
 INLINE $205F,$7004,$A0DD,$3E80;
FUNCTION PPCAcceptAsync(pb: PPCAcceptPBPtr): OSErr;
 INLINE $205F,$7004,$A4DD,$3E80;
FUNCTION PPCReject(pb: PPCRejectPBPtr;async: BOOLEAN): OSErr;
FUNCTION PPCRejectSync(pb: PPCRejectPBPtr): OSErr;
 INLINE $205F,$7005,$A0DD,$3E80;
FUNCTION PPCRejectAsync(pb: PPCRejectPBPtr): OSErr;
 INLINE $205F,$7005,$A4DD,$3E80;
FUNCTION PPCWrite(pb: PPCWritePBPtr;async: BOOLEAN): OSErr;
FUNCTION PPCWriteSync(pb: PPCWritePBPtr): OSErr;
 INLINE $205F,$7006,$A0DD,$3E80;
FUNCTION PPCWriteAsync(pb: PPCWritePBPtr): OSErr;
 INLINE $205F,$7006,$A4DD,$3E80;
FUNCTION PPCRead(pb: PPCReadPBPtr;async: BOOLEAN): OSErr;
FUNCTION PPCReadSync(pb: PPCReadPBPtr): OSErr;
 INLINE $205F,$7007,$A0DD,$3E80;
FUNCTION PPCReadAsync(pb: PPCReadPBPtr): OSErr;
 INLINE $205F,$7007,$A4DD,$3E80;
FUNCTION PPCEnd(pb: PPCEndPBPtr;async: BOOLEAN): OSErr;
FUNCTION PPCEndSync(pb: PPCEndPBPtr): OSErr;
 INLINE $205F,$7008,$A0DD,$3E80;
FUNCTION PPCEndAsync(pb: PPCEndPBPtr): OSErr;
 INLINE $205F,$7008,$A4DD,$3E80;
FUNCTION PPCClose(pb: PPCClosePBPtr;async: BOOLEAN): OSErr;
FUNCTION PPCCloseSync(pb: PPCClosePBPtr): OSErr;
 INLINE $205F,$7009,$A0DD,$3E80;
FUNCTION PPCCloseAsync(pb: PPCClosePBPtr): OSErr;
 INLINE $205F,$7009,$A4DD,$3E80;
FUNCTION IPCListPorts(pb: IPCListPortsPBPtr;async: BOOLEAN): OSErr;
FUNCTION IPCListPortsSync(pb: IPCListPortsPBPtr): OSErr;
 INLINE $205F,$700A,$A0DD,$3E80;
FUNCTION IPCListPortsAsync(pb: IPCListPortsPBPtr): OSErr;
 INLINE $205F,$700A,$A4DD,$3E80;
FUNCTION DeleteUserIdentity(userRef: LONGINT): OSErr;
FUNCTION GetDefaultUser(VAR userRef: LONGINT;
                        VAR userName: Str32): OSErr;
FUNCTION StartSecureSession(pb: PPCStartPBPtr;
                            VAR userName: Str32;
                            useDefault: BOOLEAN;
                            allowGuest: BOOLEAN;
                            VAR guestSelected: BOOLEAN;
                            prompt: Str255): OSErr;
FUNCTION PPCBrowser(prompt: Str255;
                    applListLabel: Str255;
                    defaultSpecified: BOOLEAN;
                    VAR theLocation: LocationNameRec;
                    VAR thePortInfo: PortInfoRec;
                    portFilter: PPCFilterProcPtr;
                    theLocNBPType: Str32): OSErr;
 INLINE $303C,$0D00,$A82B;


{$ENDC} { UsingPPCToolBox }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

