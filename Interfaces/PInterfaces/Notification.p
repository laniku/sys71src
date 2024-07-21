
{
Created: Saturday, July 27, 1991 at 10:14 PM
 Notification.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1989-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <6>	 7/30/91	JL		Updated Copyright. Added NMProcPtr and used it to match C file.
		 <5>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <4>	 10/3/90	JAL		Updated to match CInclude.
		 <3>	 7/16/90	VL		Changed nmSIcon to nmIcon.
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Notification;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingNotification}
{$SETC UsingNotification := 1}

{$I+}
{$SETC NotificationIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingOSUtils}
{$I $$Shell(PInterfaces)OSUtils.p}
{$ENDC}
{$SETC UsingIncludes := NotificationIncludes}

CONST
nmType = 8;

TYPE
NMProcPtr = ProcPtr;

NMRecPtr = ^NMRec;
NMRec = RECORD
 qLink: QElemPtr;		{next queue entry}
 qType: INTEGER;		{queue type -- ORD(nmType) = 8}
 nmFlags: INTEGER;		{reserved}
 nmPrivate: LONGINT;	{reserved}
 nmReserved: INTEGER;	{reserved}
 nmMark: INTEGER;		{item to mark in Apple menu}
 nmIcon: Handle;		{handle to small icon}
 nmSound: Handle;		{handle to sound record}
 nmStr: StringPtr;		{string to appear in alert}
 nmResp: NMProcPtr;		{pointer to response routine}
 nmRefCon: LONGINT;		{for application use}
 END;


FUNCTION NMInstall(nmReqPtr: NMRecPtr): OSErr;
 INLINE $205F,$A05E,$3E80;
FUNCTION NMRemove(nmReqPtr: NMRecPtr): OSErr;
 INLINE $205F,$A05F,$3E80;


{$ENDC} { UsingNotification }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

