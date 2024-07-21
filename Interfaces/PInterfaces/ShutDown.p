
{
Created: Saturday, July 27, 1991 at 11:41 PM
 ShutDown.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1987-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606

	Change History (most recent first):

		 <3>	 7/31/91	JL		Updated Copyright.
		 <2>	 1/27/91	LN		Checked in Database generate file from DSG.

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT ShutDown;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingShutDown}
{$SETC UsingShutDown := 1}

{$I+}
{$SETC ShutDownIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := ShutDownIncludes}

CONST
sdOnPowerOff = 1;		{call procedure before power off.}
sdOnRestart = 2;		{call procedure before restart.}
sdOnUnmount = 4;		{call procedure before unmounting.}
sdOnDrivers = 8;		{call procedure before closing drivers.}
sdRestartOrPower = 3;	{call before either power off or restart.}

PROCEDURE ShutDwnPower;
 INLINE $3F3C,$0001,$A895;
PROCEDURE ShutDwnStart;
 INLINE $3F3C,$0002,$A895;
PROCEDURE ShutDwnInstall(shutDownProc: ProcPtr;flags: INTEGER);
 INLINE $3F3C,$0003,$A895;
PROCEDURE ShutDwnRemove(shutDownProc: ProcPtr);
 INLINE $3F3C,$0004,$A895;


{$ENDC} { UsingShutDown }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

