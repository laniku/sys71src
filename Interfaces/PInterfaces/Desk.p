
{
Created: Saturday, July 27, 1991 at 8:25 PM
 Desk.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <3>	 7/30/91	JL		Updated Copyright.
		 <2>	 1/27/91	LN		Checked in Database generate file from DSG.

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Desk;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingDesk}
{$SETC UsingDesk := 1}

{$I+}
{$SETC DeskIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingQuickdraw}
{$I $$Shell(PInterfaces)Quickdraw.p}
{$ENDC}
{$IFC UNDEFINED UsingEvents}
{$I $$Shell(PInterfaces)Events.p}
{$ENDC}
{$SETC UsingIncludes := DeskIncludes}

CONST
accEvent = 64;
accRun = 65;
accCursor = 66;
accMenu = 67;
accUndo = 68;
accCut = 70;
accCopy = 71;
accPaste = 72;
accClear = 73;
goodbye = -1;	{goodbye message}

FUNCTION OpenDeskAcc(deskAccName: Str255): INTEGER;
 INLINE $A9B6;
PROCEDURE CloseDeskAcc(refNum: INTEGER);
 INLINE $A9B7;
PROCEDURE SystemClick(theEvent: EventRecord;theWindow: WindowPtr);
 INLINE $A9B3;
FUNCTION SystemEdit(editCmd: INTEGER): BOOLEAN;
 INLINE $A9C2;
PROCEDURE SystemTask;
 INLINE $A9B4;
FUNCTION SystemEvent(theEvent: EventRecord): BOOLEAN;
 INLINE $A9B2;
PROCEDURE SystemMenu(menuResult: LONGINT);
 INLINE $A9B5;


{$ENDC} { UsingDesk }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

