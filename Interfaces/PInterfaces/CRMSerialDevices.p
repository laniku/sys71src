
{
Created: Tuesday, July 23, 1991 at 8:14 PM
 CRMSerialDevices.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1988-1991
  All rights reserved
    This file is used in these builds: ROM System

	Change History (most recent first):

		 <3>	 7/25/91	JL		Checked in database generated file from DSG.  Reordered file to
									match C file.
		 <3>	 7/25/91	JL		Checked in database generated file from DSG.
		 <2>	 10/2/90	kaz		Support for icon suites: deviceIcon is now a handle to a
									CRMIconRecord; bumped version #. <jng>
		 <1>	 3/14/90	BBH		first checked in

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT CRMSerialDevices;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingCRMSerialDevices}
{$SETC UsingCRMSerialDevices := 1}

{$I+}
{$SETC CRMSerialDevicesIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := CRMSerialDevicesIncludes}

CONST

{    for the crmDeviceType field of the CRMRec data structure }
crmSerialDevice		=	1;
				

{  version of the CRMSerialRecord below }
curCRMSerRecVers 	= 	1;

TYPE
{ Maintains compatibility w/ apps & tools that expect an old style icon    }
CRMIconPtr		= ^CRMIconRecord;
CRMIconHandle	= ^CRMIconPtr;
CRMIconRecord	= RECORD
	oldIcon: ARRAY [0..31] OF LONGINT;		{ ICN#    }
	oldMask: ARRAY [0..31] OF LONGINT;
	theSuite: Handle;						{ Handle to an IconSuite    }
	reserved: LONGINT;
 END;

CRMSerialPtr = ^CRMSerialRecord;
CRMSerialRecord = RECORD
	version: INTEGER;
	inputDriverName: StringHandle;
	outputDriverName: StringHandle;
	name: StringHandle;
	deviceIcon: CRMIconHandle;
	ratedSpeed: LONGINT;
	maxSpeed: LONGINT;
	reserved: LONGINT;
 END;



{$ENDC} { UsingCRMSerialDevices }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

