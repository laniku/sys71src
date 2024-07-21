
{
Created: Wednesday, July 31, 1991 at 7:43 AM
 Processes.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1989-1991
  All rights reserved
    This file is used in these builds: Mac32 HcMac MacPP


	Change History (most recent first):

		<33>	 7/31/91	JL		Updated Copyright.
	   <31+>	 6/14/91	JL		Checked in official MPW 3.2Ä version. Moved Const and Type
									reserved words to before the preceeding comment to match the
									database. Moved "Process identifier." comment to after type
									declaration to be consistent with C header.
		<31>	  2/1/91	DFH		stb,WS#DFH-910131c:Renamed Process Mgr defined AppleEvent codes
									and moved them to AppleEvents.p.
		<30>	 1/30/91	JL		Checked in database generated file from DSG. (No change)
		<29>	 1/16/91	JDR		(dba) Moved the Process Mgr error numbers into the Errors
									interface file.
		<28>	  1/2/91	DFH		Made sure routine parameter names match the Inside Mac Process
									Mgr chapter documentation.
		<27>	11/14/90	DFH		Re-entered revision 25.
		<26>	11/13/90	gbm		Change <25> was garbled... I'm going back to the way it was in
									<24> until Dave can figure out what went wrong...
		<25>	11/13/90	DFH		File param to LaunchDeskAccessory is now FSSpecPtr so that
									caller can pass nil.
		<24>	11/13/90	DFH		Remove VAR from LaunchDeskAccessory. Correct casing for
									launchParams.
		<23>	 9/25/90	DFH		Fixed LaunchDeskAccessory param list.
		<22>	  9/4/90	JT		Added modeUseTextEditServices to the list of process state
									flags.
		<21>	 7/19/90	DFH		Removed launchIsAutomatic and modeAutomatic.
		<20>	 7/18/90	DFH		Uses FSSpecPtr (now that it exists) instead of ^FSSpec, in
									ProcessInfoRec and LaunchParamBlockRec
		<19>	 7/16/90	RLC		Fix LaunchDeskAccessory() interface. (per DFH)
		<18>	 7/16/90	DFH		LaunchApplication, LaunchDeskAccessory, and
									GetProcessInformation now use an FSSpecPtr instead of
									name/vrefnum/dirid.
		<17>	 4/16/90	DFH		Added AppleEvent definitions.  Changed Launch param
									constant for extended length to be the actual value
									rather than a bias.
		<16>	  4/7/90	ngk		Changed Size to LONGINT, since Memory.p is not auto-included.
		<15>	 3/21/90	HJR		Fix Header.
		<14>	 3/21/90	DFH		Renamed new process modes to more closely match SIZE flags
		<13>	  3/2/90	DFH		Added modeHLEventCompatible, modeNetHLEventCompatible, and modeStationeryAware
		<12>	 3/20/90	ngk		Remove AppleEvent dependency.
		<10>	 3/13/90	DFH		Fixed LaunchParamBlockRec.  launchControlFlags was missing
									and launchFileFlags had the wrong type.
		 <9>	 3/12/90	ngk		Defined AppParameters.
		 <8>	 3/12/90	DFH 	Added launchAppParameters field and AppParameters record.
		 <7>	  2/8/90	DFH 	Copied projector revision comments to this file.
		 <5>	  2/5/90	DFH		Added modeXxx defs for SIZE flags portion of the processMode.
		 <4>	  2/5/90	DFH 	Renamed and recapitalized to match the MultiFinder 7.0 ERS.
		 <2>	  1/3/90	DFH		Added GetFrontProcess glue.  Renamed launch flags and process mode flags to match ERS.
	** 1.2	 	12/07/1989	CCH		Added LaunchApplication
	** 1.1	 	12/01/1989	ngk		Added new error codes
	** 1.0	 	10/16/1989	ngk		Initial submission
	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Processes;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingProcesses}
{$SETC UsingProcesses := 1}

{$I+}
{$SETC ProcessesIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingEvents}
{$I $$Shell(PInterfaces)Events.p}
{$ENDC}
{$IFC UNDEFINED UsingFiles}
{$I $$Shell(PInterfaces)Files.p}
{$ENDC}
{$SETC UsingIncludes := ProcessesIncludes}

TYPE
{ type for unique process identifier }
ProcessSerialNumberPtr = ^ProcessSerialNumber;
ProcessSerialNumber = RECORD
 highLongOfPSN: LONGINT;
 lowLongOfPSN: LONGINT;
 END;


CONST

{************************************************************************
 *                            Process identifier.
 ************************************************************************
 Various reserved process serial numbers. }

kNoProcess = 0;
kSystemProcess = 1;
kCurrentProcess = 2;

TYPE
{*********************************************************************************************************************************************
 *        Definition of the parameter block passed to _Launch.
 *************************************************************************

* Typedef and flags for launchControlFlags field }
LaunchFlags = INTEGER;

CONST

{************************************************************************
 *        Definition of the parameter block passed to _Launch.
 ************************************************************************}

launchContinue = $4000;
launchNoFileFlags = $0800;
launchUseMinimum = $0400;
launchDontSwitch = $0200;
launchAllow24Bit = $0100;
launchInhibitDaemon = $0080;

TYPE
{ Format for first AppleEvent to pass to new process.  The size of the overall
 * buffer variable: the message body immediately follows the messageLength.
 }
AppParametersPtr = ^AppParameters;
AppParameters = RECORD
 theMsgEvent: EventRecord;
 eventRefCon: LONGINT;
 messageLength: LONGINT;
 messageBuffer: ARRAY [0..0] OF SignedByte;
 END;

{ Parameter block to _Launch }
LaunchPBPtr = ^LaunchParamBlockRec;
LaunchParamBlockRec = RECORD
 reserved1: LONGINT;
 reserved2: INTEGER;
 launchBlockID: INTEGER;
 launchEPBLength: LONGINT;
 launchFileFlags: INTEGER;
 launchControlFlags: LaunchFlags;
 launchAppSpec: FSSpecPtr;
 launchProcessSN: ProcessSerialNumber;
 launchPreferredSize: LONGINT;
 launchMinimumSize: LONGINT;
 launchAvailableSize: LONGINT;
 launchAppParameters: AppParametersPtr;
 END;


CONST

{ Set launchBlockID to extendedBlock to specify that extensions exist.
* Set launchEPBLength to extendedBlockLen for compatibility.}




extendedBlock = $4C43;	{ 'LC' }
extendedBlockLen = (sizeof(LaunchParamBlockRec) - 12);

{************************************************************************
 * Definition of the information block returned by GetProcessInformation
 ************************************************************************
 Bits in the processMode field }

modeDeskAccessory = $00020000;
modeMultiLaunch = $00010000;
modeNeedSuspendResume = $00004000;
modeCanBackground = $00001000;
modeDoesActivateOnFGSwitch = $00000800;
modeOnlyBackground = $00000400;
modeGetFrontClicks = $00000200;
modeGetAppDiedMsg = $00000100;
mode32BitCompatible = $00000080;
modeHighLevelEventAware = $00000040;
modeLocalAndRemoteHLEvents = $00000020;
modeStationeryAware = $00000010;
modeUseTextEditServices = $00000008;

TYPE
{ Record returned by GetProcessInformation }
ProcessInfoRecPtr = ^ProcessInfoRec;
ProcessInfoRec = RECORD
 processInfoLength: LONGINT;
 processName: StringPtr;
 processNumber: ProcessSerialNumber;
 processType: LONGINT;
 processSignature: OSType;
 processMode: LONGINT;
 processLocation: Ptr;
 processSize: LONGINT;
 processFreeMem: LONGINT;
 processLauncher: ProcessSerialNumber;
 processLaunchDate: LONGINT;
 processActiveTime: LONGINT;
 processAppSpec: FSSpecPtr;
 END;


FUNCTION LaunchApplication(LaunchParams:LaunchPBPtr):OSErr;
 INLINE $205F,$A9F2,$3E80;
FUNCTION LaunchDeskAccessory(pFileSpec: FSSpecPtr;pDAName: StringPtr): OSErr;
 INLINE $3F3C,$0036,$A88F;
FUNCTION GetCurrentProcess(VAR PSN: ProcessSerialNumber): OSErr;
 INLINE $3F3C,$0037,$A88F;
FUNCTION GetFrontProcess(VAR PSN: ProcessSerialNumber): OSErr;
 INLINE $70FF,$2F00,$3F3C,$0039,$A88F;
FUNCTION GetNextProcess(VAR PSN: ProcessSerialNumber): OSErr;
 INLINE $3F3C,$0038,$A88F;
FUNCTION GetProcessInformation(PSN: ProcessSerialNumber;VAR info: ProcessInfoRec): OSErr;
 INLINE $3F3C,$003A,$A88F;
FUNCTION SetFrontProcess(PSN: ProcessSerialNumber): OSErr;
 INLINE $3F3C,$003B,$A88F;
FUNCTION WakeUpProcess(PSN: ProcessSerialNumber): OSErr;
 INLINE $3F3C,$003C,$A88F;
FUNCTION SameProcess(PSN1: ProcessSerialNumber;PSN2: ProcessSerialNumber;
 VAR result: BOOLEAN): OSErr;
 INLINE $3F3C,$003D,$A88F;


{$ENDC} { UsingProcesses }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

