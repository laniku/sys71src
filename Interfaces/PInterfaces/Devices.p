
{
Created: Saturday, July 27, 1991 at 8:26 PM
 Devices.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc.  1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <7>	 7/30/91	JL		Updated Copyright.
		 <6>	 1/28/91	JL		Changed aSync parameter to async
		 <5>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <4>	  1/7/91	JDR		(dba) Adding messages sent to the monitor function in the
									Control Panel.
		 <3>	12/14/90	dba		<JDR> add cursorDev
		<2>		10/8/90		JAL		Added Sync and ASync calls to get around glue.
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Devices;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingDevices}
{$SETC UsingDevices := 1}

{$I+}
{$SETC DevicesIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingOSUtils}
{$I $$Shell(PInterfaces)OSUtils.p}
{$ENDC}
{$IFC UNDEFINED UsingFiles}
{$I $$Shell(PInterfaces)Files.p}
{$ENDC}
{$IFC UNDEFINED UsingQuickdraw}
{$I $$Shell(PInterfaces)Quickdraw.p}
{$ENDC}
{$SETC UsingIncludes := DevicesIncludes}

CONST
newSelMsg = 12;
fillListMsg = 13;
getSelMsg = 14;
selectMsg = 15;
deselectMsg = 16;
terminateMsg = 17;
buttonMsg = 19;
chooserID = 1;
initDev = 0;		{Time for cdev to initialize itself}
hitDev = 1;			{Hit on one of my items}
closeDev = 2;		{Close yourself}
nulDev = 3;			{Null event}
updateDev = 4;		{Update event}
activDev = 5;		{Activate event}
deactivDev = 6;		{Deactivate event}
keyEvtDev = 7;		{Key down/auto key}
macDev = 8;			{Decide whether or not to show up}
undoDev = 9;
cutDev = 10;
copyDev = 11;
pasteDev = 12;
clearDev = 13;
cursorDev = 14;
cdevGenErr = -1;	{General error; gray cdev w/o alert}
cdevMemErr = 0;		{Memory shortfall; alert user please}
cdevResErr = 1;		{Couldn't get a needed resource; alert}
cdevUnset = 3;		{ cdevValue is initialized to this}

{ Monitors control panel messages }
initMsg = 1;		{initialization}
okMsg = 2;			{user clicked OK button}
cancelMsg = 3;		{user clicked Cancel button}
hitMsg = 4;			{user clicked control in Options dialog}
nulMsg = 5;			{periodic event}
updateMsg = 6;		{update event}
activateMsg = 7;	{not used}
deactivateMsg = 8;	{not used}
keyEvtMsg = 9;		{keyboard event}
superMsg = 10;		{show superuser controls}
normalMsg = 11;		{show only normal controls}
startupMsg = 12;	{code has been loaded}

TYPE
DCtlPtr = ^DCtlEntry;
DCtlHandle = ^DCtlPtr;
DCtlEntry = RECORD
 dCtlDriver: Ptr;
 dCtlFlags: INTEGER;
 dCtlQHdr: QHdr;
 dCtlPosition: LONGINT;
 dCtlStorage: Handle;
 dCtlRefNum: INTEGER;
 dCtlCurTicks: LONGINT;
 dCtlWindow: WindowPtr;
 dCtlDelay: INTEGER;
 dCtlEMask: INTEGER;
 dCtlMenu: INTEGER;
 END;

AuxDCEPtr = ^AuxDCE;
AuxDCEHandle = ^AuxDCEPtr;
AuxDCE = PACKED RECORD
 dCtlDriver: Ptr;
 dCtlFlags: INTEGER;
 dCtlQHdr: QHdr;
 dCtlPosition: LONGINT;
 dCtlStorage: Handle;
 dCtlRefNum: INTEGER;
 dCtlCurTicks: LONGINT;
 dCtlWindow: GrafPtr;
 dCtlDelay: INTEGER;
 dCtlEMask: INTEGER;
 dCtlMenu: INTEGER;
 dCtlSlot: Byte;
 dCtlSlotId: Byte;
 dCtlDevBase: LONGINT;
 dCtlOwner: Ptr;
 dCtlExtDev: Byte;
 fillByte: Byte;
 END;


FUNCTION GetDCtlEntry(refNum: INTEGER): DCtlHandle;
FUNCTION SetChooserAlert(f: BOOLEAN): BOOLEAN;
FUNCTION OpenDriver(name: Str255;VAR drvrRefNum: INTEGER): OSErr;
FUNCTION CloseDriver(refNum: INTEGER): OSErr;
FUNCTION Control(refNum: INTEGER;csCode: INTEGER;csParamPtr: Ptr): OSErr;
FUNCTION Status(refNum: INTEGER;csCode: INTEGER;csParamPtr: Ptr): OSErr;
FUNCTION KillIO(refNum: INTEGER): OSErr;
FUNCTION PBControl(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBControlSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A004,$3E80;
FUNCTION PBControlAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A404,$3E80;
FUNCTION PBStatus(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBStatusSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A005,$3E80;
FUNCTION PBStatusAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A405,$3E80;
FUNCTION PBKillIO(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBKillIOSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A006,$3E80;
FUNCTION PBKillIOAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A406,$3E80;


{$ENDC} { UsingDevices }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

