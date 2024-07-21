
{
Created: Saturday, July 27, 1991 at 8:49 PM
 Events.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1992
  All rights reserved

	Change History (most recent first):

		<10>	  5/6/92	DCL		NIIM: Moved KeyTrans back from TextUtils to Events and added
									synonym KeyTranslate.
		 <9>	 3/26/92	JSM		Rolled this file into SuperMario project.
		 <8>	 2/27/92	DCL		Moved OSEvents into Events.p for NIIM (New Improved Inside Mac).
		 <7>	 7/30/91	JL		Updated Copyright. Restored comments.
		 <6>	 1/28/91	LN		Checked in Database Generated File from DSG. Took out an Inside
									Mac comment. Matched parameter names to .h file.
		 <5>	11/12/90	DFH		Add highLevelEventMask, remove childDiedMessage. Isolate
									obsolete equates.
		 <4>	10/19/90	gbm		Fix Dave’s mistake. Actually, his REAL mistake was checking in a
									file that he hadn’t compiled... if he had, then he would have
									noticed the missing semi-colon!
		 <3>	10/19/90	DFH		Added convertClipboardFlag.
		 <2>	10/19/90	DFH		Added resumeFlag.
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Events;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingEvents}
{$SETC UsingEvents := 1}

{$I+}
{$SETC EventsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingQuickdraw}
{$I $$Shell(PInterfaces)Quickdraw.p}
{$ENDC}
{$IFC UNDEFINED UsingOSUtils}
{$I $$Shell(PInterfaces)OSUtils.p}
{$ENDC}
{$SETC UsingIncludes := EventsIncludes}

CONST
nullEvent = 0;
mouseDown = 1;
mouseUp = 2;
keyDown = 3;
keyUp = 4;
autoKey = 5;
updateEvt = 6;
diskEvt = 7;
activateEvt = 8;
osEvt = 15;

{ event mask equates }
mDownMask = 2;
mUpMask = 4;
keyDownMask = 8;
keyUpMask = 16;
autoKeyMask = 32;
updateMask = 64;
diskMask = 128;
activMask = 256;
highLevelEventMask = 1024;
osMask = -32768;
everyEvent = -1;

{ event message equates }
charCodeMask = $000000FF;
keyCodeMask = $0000FF00;
adbAddrMask = $00FF0000;
osEvtMessageMask = $FF000000;

{ OS event messages.  Event (sub)code is in the high byte of the message field. }
mouseMovedMessage = $FA;
suspendResumeMessage = $01;

resumeFlag = 1;				{ Bit 0 of message indicates resume vs suspend }
convertClipboardFlag = 2;	{ Bit 1 in resume message indicates clipboard change }

{ modifiers }
activeFlag = 1;				{ Bit 0 of modifiers for activateEvt and mouseDown events }
btnState = 128;				{ Bit 7 of low byte is mouse button state }
cmdKey = 256;				{ Bit 0 }
shiftKey = 512;				{ Bit 1 }
alphaLock = 1024;			{ Bit 2 }
optionKey = 2048;			{ Bit 3 of high byte }
controlKey = 4096;

{ obsolete equates }
networkEvt = 10;
driverEvt = 11;
app1Evt = 12;
app2Evt = 13;
app3Evt = 14;
app4Evt = 15;
networkMask = 1024;
driverMask = 2048;
app1Mask = 4096;
app2Mask = 8192;
app3Mask = 16384;
app4Mask = -32768;

TYPE
EventRecord = RECORD
 what: INTEGER;
 message: LONGINT;
 when: LONGINT;
 where: Point;
 modifiers: INTEGER;
 END;


KeyMap = PACKED ARRAY [0..127] OF BOOLEAN;

FUNCTION GetNextEvent(eventMask: INTEGER;VAR theEvent: EventRecord): BOOLEAN;
 INLINE $A970;
FUNCTION WaitNextEvent(eventMask: INTEGER;VAR theEvent: EventRecord;sleep: LONGINT;
 mouseRgn: RgnHandle): BOOLEAN;
 INLINE $A860;
FUNCTION EventAvail(eventMask: INTEGER;VAR theEvent: EventRecord): BOOLEAN;
 INLINE $A971;
PROCEDURE GetMouse(VAR mouseLoc: Point);
 INLINE $A972;
FUNCTION Button: BOOLEAN;
 INLINE $A974;
FUNCTION StillDown: BOOLEAN;
 INLINE $A973;
FUNCTION WaitMouseUp: BOOLEAN;
 INLINE $A977;
PROCEDURE GetKeys(VAR theKeys: KeyMap);
 INLINE $A976;
FUNCTION KeyTranslate(transData: Ptr;keycode: INTEGER;VAR state: LONGINT): LONGINT;
 INLINE $A9C3;
FUNCTION KeyTrans(transData: Ptr;keycode: INTEGER;VAR state: LONGINT): LONGINT;
 INLINE $A9C3;
FUNCTION TickCount: LONGINT;
 INLINE $A975;
FUNCTION GetDblTime: LONGINT;
 INLINE $2EB8,$02F0;
FUNCTION GetCaretTime: LONGINT;
 INLINE $2EB8,$02F4;

FUNCTION PostEvent(eventNum: INTEGER;eventMsg: LONGINT): OSErr;
FUNCTION PPostEvent(eventCode: INTEGER;eventMsg: LONGINT;VAR qEl: EvQElPtr): OSErr;
FUNCTION OSEventAvail(mask: INTEGER;VAR theEvent: EventRecord): BOOLEAN;
FUNCTION GetOSEvent(mask: INTEGER;VAR theEvent: EventRecord): BOOLEAN;
PROCEDURE FlushEvents(whichMask: INTEGER;stopMask: INTEGER);
 INLINE $201F,$A032;
PROCEDURE SetEventMask(theMask: INTEGER);
 INLINE $31DF,$0144;
FUNCTION GetEvQHdr: QHdrPtr;
 INLINE $2EBC,$0000,$014A;



{$ENDC} { UsingEvents }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

