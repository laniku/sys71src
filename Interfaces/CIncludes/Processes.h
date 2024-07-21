
/************************************************************

Created: Wednesday, July 31, 1991 at 7:41 AM
 Processes.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1989-1991
  All rights reserved
    This file is used in these builds: BigBang

 
	Change History (most recent first):

		 <2>	 8/26/93	IH		#1108969 <KON>: Add modeDisplayManagerAware to size bits.
		<30>	 7/31/91	JL		Updated Copyright.
		<29>	 6/14/91	JL		Checked in official MPW 3.2Ä version. Put comments inside the
									enum declarations to match DSG Database.
		<28>	  2/1/91	DFH		stb,WS#DFH-910131c:Moved Process Mgr defined AppleEvent codes to
									AppleEvents.h under new names. Put old names in
									AppleEventsInternal.h since we don't want to break any compiles
									at this point.
		<27>	 1/30/91	JL		Checked in database generated file from DSG.
		<26>	 1/25/91	stb		JDR: change processSignature to OSType from unsigned long
		<25>	 1/16/91	JDR		(dba) Moved the Process Mgr error numbers into the Errors
									interface file.
		<24>	  1/2/91	DFH		Made sure routine parameter names match the Inside Mac Process
									Mgr chapter documentation.
		<22>	11/28/90	JL		Put formal parameter names back.
		<21>	11/19/90	DFH		Comment changes.
		<20>	 11/7/90	JL		Changed all #defines to anonymous enums
		<19>	 11/4/90	dba		add some const stuff for input-only parameters
		<18>	10/21/90	gbm		(with dba) Made compatible with 3.2 C compiler (and incompatible
									with previous compilers).
		<17>	10/19/90	DFH		Fixed LaunchApplication glue.  Was an inline that popped
									parameter, which is not C convention.  Now uses #pragma
									parameter and inline is plain trap number.
		<16>	  10/9/90	JAL		CPlusPlus compatability.
		<15>	  9/4/90	JT		Added modeUseTextEditServices to the list of process state
									flags.
		<14>	 8/28/90	DFH		Correct capitalization of highLongOfPSN and lowLongOfPSN
		<13>	 7/19/90	DFH		Removed launchIsAutomatic and modeAutomatic.
		<12>	 7/16/90	DFH		Launch, GetProcessInformation, and LaunchDeskAccessory now use
									FSSpec instead of name/vfrefnum/dirid.
		<11>	 4/16/90	DFH		Added AppleEvent definitions.  Changed Launch params to use
									unsigned fields, and made the constant for extended length
									be the actual value rather than a bias.
		<10>	 3/21/90	DFH		Renamed new mode flags to more closely match the SIZE flags.
		 <9>	 3/20/90	DFH		Added modeHLEventCompatible, modeNetHLEventCompatible, and
									modeStationeryAware.  Removed AppleEventMessage field from
									AppParameters.  No longer includes AppleEvents.h.
		 <8>	 3/12/90	DFH		Added AppParameters structure for launchAppParameters.
		 <6>	  2/8/90	DFH		Copied projector revision comments to this file.
		 <5>	  2/5/90	DFH		Added modeXxx defs for SIZE flags portion of the processMode.
		 <4>	  2/5/90	DFH		Renamed and recapitalized to match the MultiFinder 7.0 ERS.
		 <2>	  2/3/90	DFH		Added GetFrontProcess glue.  Renamed launch flags and process mode flags to match ERS.

************************************************************/


#ifndef __PROCESSES__
#define __PROCESSES__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __EVENTS__
#include <Events.h>
#endif

#ifndef __FILES__
#include <Files.h>
#endif


/* type for unique process identifier */
struct ProcessSerialNumber {
 unsigned long highLongOfPSN;
 unsigned long lowLongOfPSN;
};

typedef struct ProcessSerialNumber ProcessSerialNumber;
typedef ProcessSerialNumber *ProcessSerialNumberPtr;


enum {


/*************************************************************************
 *                            Process identifier.
 ************************************************************************
 Various reserved process serial numbers. */

 kNoProcess = 0,
 kSystemProcess = 1,
 kCurrentProcess = 2
};

/**********************************************************************************************************************************************
 *        Definition of the parameter block passed to _Launch.
 *************************************************************************

* Typedef and flags for launchControlFlags field */
typedef unsigned short LaunchFlags;

enum {


/*************************************************************************
 *        Definition of the parameter block passed to _Launch.
 *************************************************************************/

 launchContinue = 0x4000,
 launchNoFileFlags = 0x0800,
 launchUseMinimum = 0x0400,
 launchDontSwitch = 0x0200,
 launchAllow24Bit = 0x0100,
 launchInhibitDaemon = 0x0080
};

/* Format for first AppleEvent to pass to new process.  The size of the overall
 * buffer variable: the message body immediately follows the messageLength.
 */
struct AppParameters {
 EventRecord theMsgEvent;
 unsigned long eventRefCon;
 unsigned long messageLength;
};

typedef struct AppParameters AppParameters;
typedef AppParameters *AppParametersPtr;

/* Parameter block to _Launch */
struct LaunchParamBlockRec {
 unsigned long reserved1;
 unsigned short reserved2;
 unsigned short launchBlockID;
 unsigned long launchEPBLength;
 unsigned short launchFileFlags;
 LaunchFlags launchControlFlags;
 FSSpecPtr launchAppSpec;
 ProcessSerialNumber launchProcessSN;
 unsigned long launchPreferredSize;
 unsigned long launchMinimumSize;
 unsigned long launchAvailableSize;
 AppParametersPtr launchAppParameters;
};

typedef struct LaunchParamBlockRec LaunchParamBlockRec;
typedef LaunchParamBlockRec *LaunchPBPtr;


enum {


/* Set launchBlockID to extendedBlock to specify that extensions exist.
* Set launchEPBLength to extendedBlockLen for compatibility.*/





#define extendedBlock ((unsigned short)'LC')
#define extendedBlockLen (sizeof(LaunchParamBlockRec) - 12)

/*************************************************************************
 * Definition of the information block returned by GetProcessInformation
 ************************************************************************
 Bits in the processMode field */


 modeDeskAccessory = 0x00020000,
 modeMultiLaunch = 0x00010000,
 modeNeedSuspendResume = 0x00004000,
 modeCanBackground = 0x00001000,
 modeDoesActivateOnFGSwitch = 0x00000800,
 modeOnlyBackground = 0x00000400,
 modeGetFrontClicks = 0x00000200,
 modeGetAppDiedMsg = 0x00000100,
 mode32BitCompatible = 0x00000080,
 modeHighLevelEventAware = 0x00000040,
 modeLocalAndRemoteHLEvents = 0x00000020,
 modeStationeryAware = 0x00000010,
 modeUseTextEditServices = 0x00000008,
 modeDisplayManagerAware = 0x00000004
};

/* Record returned by GetProcessInformation */
struct ProcessInfoRec {
 unsigned long processInfoLength;
 StringPtr processName;
 ProcessSerialNumber processNumber;
 unsigned long processType;
 OSType processSignature;
 unsigned long processMode;
 Ptr processLocation;
 unsigned long processSize;
 unsigned long processFreeMem;
 ProcessSerialNumber processLauncher;
 unsigned long processLaunchDate;
 unsigned long processActiveTime;
 FSSpecPtr processAppSpec;
};

typedef struct ProcessInfoRec ProcessInfoRec;
typedef ProcessInfoRec *ProcessInfoRecPtr;


#ifdef __cplusplus
extern "C" {
#endif
#pragma parameter __D0 LaunchApplication(__A0)
pascal OSErr LaunchApplication(const LaunchParamBlockRec *LaunchParams)
 = 0xA9F2; 
pascal OSErr LaunchDeskAccessory(const FSSpec *pFileSpec,ConstStr255Param pDAName)
 = {0x3F3C,0x0036,0xA88F}; 
pascal OSErr GetCurrentProcess(ProcessSerialNumber *PSN)
 = {0x3F3C,0x0037,0xA88F}; 
pascal OSErr GetFrontProcess(ProcessSerialNumber *PSN)
 = {0x70FF,0x2F00,0x3F3C,0x0039,0xA88F}; 
pascal OSErr GetNextProcess(ProcessSerialNumber *PSN)
 = {0x3F3C,0x0038,0xA88F}; 
pascal OSErr GetProcessInformation(const ProcessSerialNumber *PSN,ProcessInfoRecPtr info)
 = {0x3F3C,0x003A,0xA88F}; 
pascal OSErr SetFrontProcess(const ProcessSerialNumber *PSN)
 = {0x3F3C,0x003B,0xA88F}; 
pascal OSErr WakeUpProcess(const ProcessSerialNumber *PSN)
 = {0x3F3C,0x003C,0xA88F}; 
pascal OSErr SameProcess(const ProcessSerialNumber *PSN1,const ProcessSerialNumber *PSN2,
 Boolean *result)
 = {0x3F3C,0x003D,0xA88F}; 
#ifdef __cplusplus
}
#endif

#endif
