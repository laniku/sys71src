
{
Created: Saturday, July 27, 1991 at 11:16 PM
 Retrace.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <6>	 7/31/91	JL		Updated Copyright.
		 <5>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <4>	12/14/90	dba		<JDR> INLINEs for SlotVInstall, SlotVRemove, AttachVBL,
									DoVBLTask, VInstall, VRemove
		 <3>	10/10/90	JL		Fixing GetVBLQHdr
		 <2>	 10/3/90	JAL		Added Inline for GetVBLQHdr.

}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Retrace;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingRetrace}
{$SETC UsingRetrace := 1}

{$I+}
{$SETC RetraceIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingOSUtils}
{$I $$Shell(PInterfaces)OSUtils.p}
{$ENDC}
{$SETC UsingIncludes := RetraceIncludes}

FUNCTION GetVBLQHdr: QHdrPtr;
 INLINE $2EBC,$0000,$0160;
FUNCTION SlotVInstall(vblBlockPtr: QElemPtr;theSlot: INTEGER): OSErr;
 INLINE $301F,$205F,$A06F,$3E80;
FUNCTION SlotVRemove(vblBlockPtr: QElemPtr;theSlot: INTEGER): OSErr;
 INLINE $301F,$205F,$A070,$3E80;
FUNCTION AttachVBL(theSlot: INTEGER): OSErr;
 INLINE $301F,$A071,$3E80;
FUNCTION DoVBLTask(theSlot: INTEGER): OSErr;
 INLINE $301F,$A072,$3E80;
FUNCTION VInstall(vblTaskPtr: QElemPtr): OSErr;
 INLINE $205F,$A033,$3E80;
FUNCTION VRemove(vblTaskPtr: QElemPtr): OSErr;
 INLINE $205F,$A034,$3E80;


{$ENDC} { UsingRetrace }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

