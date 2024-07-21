
{
Created: Saturday, July 27, 1991 at 8:37 PM
 EPPC.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1988-1991
  All rights reserved
    This file is used in these builds: BigBang

	Change History (most recent first):

		<14>	 7/30/91	JL		Updated Copyright.
		<13>	  2/4/91	JL		change parameter names from pPSN to PSN.  Deleted
									registerOnNetwork.
		<12>	 1/28/91	LN		Checked in Database Generated File from DSG. RegisterOnNetwork
									came back because their was no note on its removal.
		<11>	 1/25/91	stb		JDR: change systemOptionMask to systemOptionsMask
		<10>	12/14/90	JWM		do some beautification of the header file
		 <9>	12/13/90	JWM		New error code, noUserInteractionAllowed (-610) for
									PostHighLevelEvent which is returned if we are establishing a
									remote connection and the application is not frontmost or is
									being coerced.
		 <8>	 9/27/90	ngk		Define GetSpecificFilterProcPtr type.
		 <7>	 9/27/90	ngk		Changed "VAR params: LONGINT" to "yourDataPtr: UNIV Ptr" in
									GetSpecificHighLevelEvent
		 <6>	 9/15/90	ngk		update to new ppctoolbox namesPortName -> PPCPortRec,
									LocationName -> LocationNameRec
		 <5>	 4/10/90	JWM		add GetPortNameFromProcessSerialNumber interface and remove two
									postingOptions that will not be implemented.
		 <4>	 3/20/90	JM		changing API for (hopefully) the last time before beta. See
									comments in the file.

		** 3.0  jwm 03/20/1990 updated for 7.0a8 changes to the API.	
		** 1.2	ngk 11/07/1989  Added registerOnNetwork and authenticateNetRequest
		** 1.1	ngk 11/04/1989 fixed GetPSNfromPort
		** 1.0	ngk 11/02/1989 initial EASE submission


	To Do: 
	
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT EPPC;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingEPPC}
{$SETC UsingEPPC := 1}

{$I+}
{$SETC EPPCIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingPPCToolbox}
{$I $$Shell(PInterfaces)PPCToolbox.p}
{$ENDC}
{$IFC UNDEFINED UsingProcesses}
{$I $$Shell(PInterfaces)Processes.p}
{$ENDC}
{$IFC UNDEFINED UsingEvents}
{$I $$Shell(PInterfaces)Events.p}
{$ENDC}
{$SETC UsingIncludes := EPPCIncludes}

CONST
kHighLevelEvent = 23;

{ postOptions currently supported }
receiverIDMask = $0000F000;
receiverIDisPSN = $00008000;
receiverIDisSignature = $00007000;
receiverIDisSessionID = $00006000;
receiverIDisTargetID = $00005000;

systemOptionsMask = $00000F00;
nReturnReceipt = $00000200;

priorityMask = $000000FF;
nAttnMsg = $00000001;


{ error returns from Post and Accept }

bufferIsSmall = -607;
noOutstandingHLE = -608;
connectionInvalid = -609;
noUserInteractionAllowed = -610;		{ no user interaction allowed }

{ constant for return receipts }

HighLevelEventMsgClass = 'jaym';
rtrnReceiptMsgID = 'rtrn';
msgWasPartiallyAccepted = 2;
msgWasFullyAccepted = 1;
msgWasNotAccepted = 0;

TYPE
TargetIDPtr = ^TargetID;
TargetIDHdl = ^TargetIDPtr;
TargetID = RECORD
 sessionID: LONGINT;
 name: PPCPortRec;
 location: LocationNameRec;
 recvrName: PPCPortRec;
 END;


SenderID = TargetID;
SenderIDPtr = ^SenderID;

HighLevelEventMsgPtr = ^HighLevelEventMsg;
HighLevelEventMsgHdl = ^HighLevelEventMsgPtr;
HighLevelEventMsg = RECORD
 HighLevelEventMsgHeaderLength: INTEGER;
 version: INTEGER;
 reserved1: LONGINT;
 theMsgEvent: EventRecord;
 userRefcon: LONGINT;
 postingOptions: LONGINT;
 msgLength: LONGINT;
 END;


FUNCTION PostHighLevelEvent(theEvent: EventRecord;
                            receiverID: Ptr;
                            msgRefcon: LONGINT;
                            msgBuff: Ptr;
                            msgLen: LONGINT;
                            postingOptions: LONGINT): OSErr;
 INLINE $3F3C,$0034,$A88F;
FUNCTION AcceptHighLevelEvent(VAR sender: TargetID;
                              VAR msgRefcon: LONGINT;
                              msgBuff: Ptr;
                              VAR msgLen: LONGINT): OSErr;
 INLINE $3F3C,$0033,$A88F;
FUNCTION GetProcessSerialNumberFromPortName(portName: PPCPortRec;VAR PSN: ProcessSerialNumber): OSErr;
 INLINE $3F3C,$0035,$A88F;
FUNCTION GetPortNameFromProcessSerialNumber(VAR portName: PPCPortRec;PSN: ProcessSerialNumber): OSErr;
 INLINE $3F3C,$0046,$A88F;

TYPE
GetSpecificFilterProcPtr = ProcPtr;		{ FUNCTION MyFilter(yourDataPtr: Ptr;    }
        								{     msgBuff: HighLevelEventMsgPtr; }
        								{     sender: TargetID): Boolean;  }

FUNCTION GetSpecificHighLevelEvent(aFilter: GetSpecificFilterProcPtr;yourDataPtr: UNIV Ptr;
 VAR err: OSErr): BOOLEAN;
 INLINE $3F3C,$0045,$A88F;


{$ENDC} { UsingEPPC }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

