
{
Created: Saturday, July 27, 1991 at 11:56 PM
 Start.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1987-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606

	
	Change History (most recent first):

		 <5>	 7/31/91	JL		Updated Copyright.
		 <4>	 6/14/91	JL		Checked in official MPW 3.2Ä version. Added and removed blank
									lines to match output of DSG database.
		 <3>	 1/27/91	LN		Checked in Database generate file from DSG.
		<2>		10/3/90		JAL		Added Inlines for function.

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Start;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingStart}
{$SETC UsingStart := 1}

{$I+}
{$SETC StartIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := StartIncludes}

TYPE
DefStartType = (slotDev,scsiDev);


DefStartPtr = ^DefStartRec;
DefStartRec = RECORD
 CASE DefStartType OF
   slotDev:
  (sdExtDevID: SignedByte;
  sdPartition: SignedByte;
  sdSlotNum: SignedByte;
  sdSRsrcID: SignedByte);
   scsiDev:
  (sdReserved1: SignedByte;
  sdReserved2: SignedByte;
  sdRefNum: INTEGER);
 END;

DefVideoPtr = ^DefVideoRec;
DefVideoRec = RECORD
 sdSlot: SignedByte;
 sdsResource: SignedByte;
 END;

DefOSPtr = ^DefOSRec;
DefOSRec = RECORD
 sdReserved: SignedByte;
 sdOSType: SignedByte;
 END;


PROCEDURE GetDefaultStartup(paramBlock: DefStartPtr);
 INLINE $205F,$A07D;
PROCEDURE SetDefaultStartup(paramBlock: DefStartPtr);
 INLINE $205F,$A07E;
PROCEDURE GetVideoDefault(paramBlock: DefVideoPtr);
 INLINE $205F,$A080;
PROCEDURE SetVideoDefault(paramBlock: DefVideoPtr);
 INLINE $205F,$A081;
PROCEDURE GetOSDefault(paramBlock: DefOSPtr);
 INLINE $205F,$A084;
PROCEDURE SetOSDefault(paramBlock: DefOSPtr);
 INLINE $205F,$A083;
PROCEDURE SetTimeout(count: INTEGER);
PROCEDURE GetTimeout(VAR count: INTEGER);


{$ENDC} { UsingStart }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

