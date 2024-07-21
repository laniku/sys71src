
{
Created: Sunday, July 28, 1991 at 12:14 AM
 Timer.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <5>	 7/31/91	JL		Updated Copyright.
		 <4>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <3>	 12/3/90	JDR		<dba> Use inlines.
		<2>		 10/3/90	JAL		Added to Longs to end of TMTask record.
									and added InsXTime.
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Timer;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingTimer}
{$SETC UsingTimer := 1}

{$I+}
{$SETC TimerIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingOSUtils}
{$I $$Shell(PInterfaces)OSUtils.p}
{$ENDC}
{$SETC UsingIncludes := TimerIncludes}

TYPE
TMTaskPtr = ^TMTask;
TMTask = RECORD
 qLink: QElemPtr;
 qType: INTEGER;
 tmAddr: ProcPtr;
 tmCount: LONGINT;
 tmWakeUp: LONGINT;
 tmReserved: LONGINT;
 END;


PROCEDURE InsTime(tmTaskPtr: QElemPtr);
 INLINE $205F,$A058;
PROCEDURE InsXTime(tmTaskPtr: QElemPtr);
 INLINE $205F,$A458;
PROCEDURE PrimeTime(tmTaskPtr: QElemPtr;count: LONGINT);
 INLINE $201F,$205F,$A05A;
PROCEDURE RmvTime(tmTaskPtr: QElemPtr);
 INLINE $205F,$A059;


{$ENDC} { UsingTimer }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

