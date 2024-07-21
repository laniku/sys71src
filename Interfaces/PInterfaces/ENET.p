
{
Created: Saturday, July 27, 1991 at 8:36 PM
 ENET.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1990-1991
  All rights reserved
	Change History (most recent first):

		 <2>	 7/30/91	JL		Updated Copyright. Changed Boolean to BOOLEAN.

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT ENET;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingENET}
{$SETC UsingENET := 1}

{$I+}
{$SETC ENETIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingOSUtils}
{$I $$Shell(PInterfaces)OSUtils.p}
{$ENDC}
{$SETC UsingIncludes := ENETIncludes}

CONST
ENetSetGeneral = 253;						{Set "general" mode}
ENetGetInfo = 252;							{Get info}
ENetRdCancel = 251;							{Cancel read}
ENetRead = 250;								{Read}
ENetWrite = 249;							{Write}
ENetDetachPH = 248;							{Detach protocol handler}
ENetAttachPH = 247;							{Attach protocol handler}
ENetAddMulti = 246;							{Add a multicast address}
ENetDelMulti = 245;							{Delete a multicast address}

eLenErr = -92;								{Length error ddpLenErr}
eMultiErr = -91;							{Multicast address error ddpSktErr}

EAddrRType = 'eadr';						{Alternate address resource type}

TYPE
EParamBlkPtr = ^EParamBlock;
EParamBlock = PACKED RECORD
 qLink: QElemPtr;        					{next queue entry}
 qType: INTEGER;         					{queue type}
 ioTrap: INTEGER;        					{routine trap}
 ioCmdAddr: Ptr;         					{routine address}
 ioCompletion: ProcPtr;       				{completion routine}
 ioResult: OSErr;        					{result code}
 ioNamePtr: StringPtr;       				{->filename}
 ioVRefNum: INTEGER;        				{volume reference or drive number}
 ioRefNum: INTEGER;        					{driver reference number}
 csCode: INTEGER;        					{call command code AUTOMATICALLY set}
 CASE INTEGER OF
   ENetWrite,ENetAttachPH,ENetDetachPH,ENetRead,ENetRdCancel,ENetGetInfo,ENetSetGeneral:
  (eProtType: INTEGER;      				{Ethernet protocol type}
  ePointer: Ptr;
  eBuffSize: INTEGER;       				{buffer size}
  eDataSize: INTEGER);       				{number of bytes read}
   ENetAddMulti,ENetDelMulti:
  (eMultiAddr: ARRAY [0..5] of char);   	{Multicast Address}
 END;


FUNCTION EWrite(thePBptr: EParamBlkPtr;async: BOOLEAN): OSErr;
FUNCTION EAttachPH(thePBptr: EParamBlkPtr;async: BOOLEAN): OSErr;
FUNCTION EDetachPH(thePBptr: EParamBlkPtr;async: BOOLEAN): OSErr;
FUNCTION ERead(thePBptr: EParamBlkPtr;async: BOOLEAN): OSErr;
FUNCTION ERdCancel(thePBptr: EParamBlkPtr;async: BOOLEAN): OSErr;
FUNCTION EGetInfo(thePBptr: EParamBlkPtr;async: BOOLEAN): OSErr;
FUNCTION ESetGeneral(thePBptr: EParamBlkPtr;async: BOOLEAN): OSErr;
FUNCTION EAddMulti(thePBptr: EParamBlkPtr;async: BOOLEAN): OSErr;
FUNCTION EDelMulti(thePBptr: EParamBlkPtr;async: BOOLEAN): OSErr;


{$ENDC} { UsingENET }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

