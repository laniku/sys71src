
{
Created: Saturday, July 27, 1991 at 8:31 PM
 Disks.p
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
 UNIT Disks;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingDisks}
{$SETC UsingDisks := 1}

{$I+}
{$SETC DisksIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingOSUtils}
{$I $$Shell(PInterfaces)OSUtils.p}
{$ENDC}
{$SETC UsingIncludes := DisksIncludes}

TYPE
DriveKind = (sony,hard20);


DrvSts = RECORD
 track: INTEGER;			{current track}
 writeProt: SignedByte;		{bit 7 = 1 if volume is locked}
 diskInPlace: SignedByte;	{disk in drive}
 installed: SignedByte;		{drive installed}
 sides: SignedByte;			{-1 for 2-sided, 0 for 1-sided}
 driveQLink: QElemPtr;		{next queue entry}
 driveQVers: INTEGER;		{1 for HD20}
 dQDrive: INTEGER;			{drive number}
 dQRefNum: INTEGER;			{driver reference number}
 dQFSID: INTEGER;			{file system ID}
 CASE DriveKind OF
   sony:
  (twoSideFmt: SignedByte;	{after 1st rd/wrt: 0=1 side, -1=2 side}
  needsFlush: SignedByte;	{-1 for MacPlus drive}
  diskErrs: INTEGER);		{soft error count}
   hard20:
  (driveSize: INTEGER;		{drive block size low word}
  driveS1: INTEGER;			{drive block size high word}
  driveType: INTEGER;		{1 for HD20}
  driveManf: INTEGER;		{1 for Apple Computer, Inc.}
  driveChar: SignedByte;	{230 ($E6) for HD20}
  driveMisc: SignedByte);	{0 -- reserved}
 END;


FUNCTION DiskEject(drvNum: INTEGER): OSErr;
FUNCTION SetTagBuffer(buffPtr: Ptr): OSErr;
FUNCTION DriveStatus(drvNum: INTEGER;VAR status: DrvSts): OSErr;


{$ENDC} { UsingDisks }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

