
{
Created: Saturday, July 27, 1991 at 8:31 PM
 DiskInit.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc.  1985-1991
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
 UNIT DiskInit;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingDiskInit}
{$SETC UsingDiskInit := 1}

{$I+}
{$SETC DiskInitIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := DiskInitIncludes}

TYPE
HFSDefaults = RECORD
 sigWord: PACKED ARRAY [0..1] OF Byte;	{ signature word}
 abSize: LONGINT;						{ allocation block size in bytes}
 clpSize: LONGINT;						{ clump size in bytes}
 nxFreeFN: LONGINT;						{ next free file number}
 btClpSize: LONGINT;					{ B-Tree clump size in bytes}
 rsrv1: INTEGER;						{ reserved}
 rsrv2: INTEGER;						{ reserved}
 rsrv3: INTEGER;						{ reserved}
 END;


PROCEDURE DILoad;
PROCEDURE DIUnload;
FUNCTION DIBadMount(where: Point;evtMessage: LONGINT): INTEGER;
FUNCTION DIFormat(drvNum: INTEGER): OSErr;
FUNCTION DIVerify(drvNum: INTEGER): OSErr;
FUNCTION DIZero(drvNum: INTEGER;volName: Str255): OSErr;


{$ENDC} { UsingDiskInit }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

