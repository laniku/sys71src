{
	File:		MFPrivate.p

	Contains:	All private Process Manager constants and record definitions

	Written by:	David Harrison

	Copyright:	© 1989-1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<17>	 2/21/91	DFH		dba,#82504, #82681, #83168, #83182, #83207: Added
									SysZoneFloatSizes.
		<16>	 1/28/91	DFH		JSM,#81425:Added DisableSwitching and EnableSwitching.
		<15>	 1/21/91	DFH		(KSM) Remove Process Menu IDs, since they are now in
									MenuMgrPriv.p, as the Application Menu IDs.
		<14>	12/20/90	DFH		(dba) Added GetNextHighLevelEvent.
		<13>	12/14/90	DFH		Added SynchIdleTime.
		<12>	 9/10/90	DFH		Changed iconHelpString to itemHelpString (wow!).
		<11>	 7/25/90	DFH		Added InitApplication, CleanupApplication, and SndAppDead.
		<10>	 7/19/90	DFH		Removed iconColor from AddAppleMenuItem.
		 <9>	  6/8/90	DFH		Added ProcessMenuResourceID and ProcessMenuID.
		 <8>	 4/11/90	DFH		Reorganized the file to group the call glue with the
									structures.  Added definitions for Apple menu selection
									AppleEvent.
		 <7>	 4/11/90	KSM		Added auxMenuHelpString to AuxMenuItemRec.
		 <6>	 3/20/90	DFH		Added iconColor and itemHelpString to AddAppleMenuItem
		 <5>	 3/12/90	DFH		Added aeDebuggerNotify.
		 <4>	  2/8/90	DFH		Copied projector revision comments to this file.
		 <3>	  2/5/90	DFH		Added enteredDebugger.
		 <2>	  1/3/90	DFH		Added itemStyle to AddAppleMenuItem.  Reversed order of GetProcessFromLayer parms.

** BEGIN EASE MODIFICATION HISTORY
** 1.1	ngk 12/01/1989 Added System Debugger interfaces
** 1.0	ngk 10/16/1989 Initial Submission
** END EASE MODIFICATION HISTORY
}

{$IFC UNDEFINED UsingIncludes}
	{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
    UNIT MFPrivate;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingMFPrivate}
{$SETC UsingMFPrivate := 1}

{$I+}
{$SETC MFPrivateIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
	{$I Types.p}
{$ENDC}
{$IFC UNDEFINED UsingPackages}
	{$I Packages.p}
{$ENDC}
{$IFC UNDEFINED UsingMenus}
	{$I Menus.p}
{$ENDC}
{$IFC UNDEFINED UsingLayers}
	{$I Layers.p}
{$ENDC}
{$IFC UNDEFINED UsingProcesses}
	{$I Processes.p}
{$ENDC}
{$SETC UsingIncludes := MFPrivateIncludes}
	
{*************************************************************************
 *						Application Menu.
 *************************************************************************}

{ Item numbers }
CONST
	HIDE_APP_ITEM			=	1;
	HIDE_OTHERS_ITEM		=	2;
	SHOW_ALL_ITEM			=	3;
	APPLICATION_MENU_COUNT	=	4;
	
{*************************************************************************
 *						Auxiliary menu item data.
 *************************************************************************}

{ Information record returned by GetAuxMenuItem }
TYPE
	AuxMenuItemRec	=	RECORD
							auxMenuIconHandle:	Handle;
							auxMenuIconSize:	INTEGER;
							auxMenuIconGray:	INTEGER;
							auxMenuScript:		INTEGER;
							auxMenuHelpString:	StringHandle;
						END;
	
FUNCTION GetAuxMenuItem(theMenu: MenuHandle; pItemEntry: Ptr; VAR theStorage: AuxMenuItemRec; recLength: Size): OSErr;
	INLINE $3F3C, $003E, $A88F;
						
{*************************************************************************
 *						Volume notification interface.
 *************************************************************************}

{ values for the VNBNotice field. }
CONST
	VNMounted			=	0;
	VNAboutToGoOffline	=	1;
	VNOffline			=	2;
	VNAboutToUnmount	=	3;
	VNUnmount			=	4;

{ Definition of the volume notification parameter block }
TYPE
	VolumeNotice		=	INTEGER;
	VolumeNoticeBlkPtr	=	^VolumeNoticeBlk;
	VolumeNoticeBlk		=	RECORD
								VNBLength:	LONGINT;
								VNBNotice:	VolumeNotice;
								VNBVolume:	INTEGER;
								VNBRefCon:	LONGINT;
								VNBResult:	OSErr;
							END;
						
	VNProcPtr	=	ProcPtr; { FUNCTION Notify(pb: VolumeNoticeBlkPtr): OSErr; }

	
FUNCTION RequestVolumeNotification(pRoutine: VNProcPtr; refCon: LONGINT): OSErr;
	INLINE $3F3C, $0042, $A88F;
	
FUNCTION DeclineVolumeNotification(pRoutine: VNProcPtr; refCon: LONGINT): OSErr;
	INLINE $3F3C, $0043, $A88F;

{*************************************************************************
 *							Shell support
 *************************************************************************}

{ AppleEvent sent to app launched from FINDERNAME at boot time }
CONST
aeStartup						=	'boot';

{ AppleEvent and routines to customize the Apple menu }
CONST
aeAppleMenuItemSelect			=	'amis';
aeAppleMenuItemKeyword			=	'amis';
DELETE_ALL_ITEMS				=	0;
	
FUNCTION AddAppleMenuItem(itemName: StringPtr; itemScript: ScriptCode; itemStyle: Style; itemIcon: Handle; itemMark: INTEGER; itemHelpString: StringPtr; itemRefCon: LONGINT): OSErr;
	INLINE $3F3C, $0031, $A88F;
	
FUNCTION DeleteAppleMenuItem(itemRefCon: LONGINT): OSErr;
	INLINE $3F3C, $0032, $A88F;
	
{ Routine to allocate a layer to implement the desktop }
FUNCTION NewDesktopLayerOwner(VAR ppNewLayer: LayerPtr): OSErr;
	INLINE $3F3C, $0014, $A88F;

{*************************************************************************
 *							System Debugger Support.
 *************************************************************************}

{ system error generated when user types the debugger key combination. }
CONST
	enterDebugger				=	110;

{ Identifier of AppleEvent notifying debugger that debuggee now not frontmost }
CONST
	aeDebuggerNotify			=	'dbrk';

FUNCTION RegisterDebugger(PSN: ProcessSerialNumber; entryRoutine: Ptr; exitRoutine: Ptr; toAppRoutine: Ptr; debugKey: INTEGER): OSErr;
    INLINE $3F3C, $0030, $A88F;

FUNCTION GetProcessTrapAddress(PSN: ProcessSerialNumber; VAR trapAddr: Ptr; trapKind: TrapType; trapNum: INTEGER): OSErr;
    INLINE $3F3C, $002C, $A88F;

FUNCTION SetProcessTrapAddress(PSN: ProcessSerialNumber; trapAddr: Ptr; trapKind: TrapType; trapNum: INTEGER): OSErr;
    INLINE $3F3C, $002D, $A88F;

FUNCTION ReadWriteProcessMemory(PSN: ProcessSerialNumber; procMemPtr: Ptr; byteCount: LONGINT; callerMemPtr: Ptr; doRead: BOOLEAN): OSErr;
    INLINE $3F3C, $002E, $A88F;

FUNCTION ReadWriteProcessFPURegs(PSN: ProcessSerialNumber; callerMemPtr: Ptr; doRead: BOOLEAN): OSErr;
    INLINE $3F3C, $002F, $A88F;

FUNCTION KillProcess(PSN: ProcessSerialNumber): OSErr;
    INLINE $3F3C, $0044, $A88F;	

{*************************************************************************
 *					Support for (as yet) unpublished Layer Manager.
 *************************************************************************}

FUNCTION GetProcessFromLayer(VAR PSN: ProcessSerialNumber; pLayer: LayerPtr): OSErr;
	INLINE $3F3C, $0039, $A88F;

{*************************************************************************
 *					Support for application resource tracking.
 *************************************************************************}

PROCEDURE InitApplication;
	INLINE $AAFA;

PROCEDURE SynchIdleTime;
	INLINE $ABF7;

PROCEDURE CleanupApplication;
	INLINE $AAFA;
	
PROCEDURE SndAppDead;
	INLINE $A0B8;
	
FUNCTION GetSystemClientProcess(VAR PSN: ProcessSerialNumber): OSErr;
	INLINE $3F3C, $003F, $A88F;
	
FUNCTION BeginSystemMode: OSErr;
	INLINE $3F3C, $0040, $A88F;
	
FUNCTION EndSystemMode: OSErr;
	INLINE $3F3C, $0041, $A88F;

{*************************************************************************
 *			Support for high level event checking from the system.
 *************************************************************************}

FUNCTION GetNextHighLevelEvent(eventMask: INTEGER;VAR theEvent: EventRecord;yankIt: BOOLEAN): BOOLEAN;
	INLINE $3F3C, $0012, $A88F;

{*************************************************************************
 *			Scheduler control.
 *************************************************************************}

PROCEDURE DisableSwitching;
	INLINE $3F3C, $0019, $A88F;

PROCEDURE EnableSwitching;
	INLINE $3F3C, $001A, $A88F;

{*************************************************************************
 *			Bonus Temporary Memory vs System Heap information.
 *************************************************************************}

FUNCTION SysZoneFloatSizes(VAR hiSysRoom: Size; VAR lowTempRoom: Size): OSErr;
	INLINE $3F3C, $0047, $A88F;

{$ENDC}    { UsingMFPrivate }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}
