/*
	File:		ProcessesPriv.h

	Contains:	Subset of Private Process Mgr routines needed in C.

	Written by:	David Harrison

	Copyright:	© 1990-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 3/25/93	IH		first checked in
		<32>	 3/12/93	mgl		Add an othersToBack parameter to BringWindowToFrontLayer. This
									allows you to bring a window to the front layer while forcing
									all other windows in the front layer into the back layer.
		<31>	 3/10/93	mgl		Add new calls for MultiLayer Support.
		<30>	  3/9/93	DRF		Add some recent additions to _OSDispatch so people don’t have to
									“roll their own” prototypes.
		<29>	 2/23/93	mgl		Added toFront parameter to StopCurrentProcess and ResumeProcess
									to allow the debugger to control whether the incoming process
									will be switched to the front.
		<28>	 2/23/93	DTY		Renamed this file from MFPrivate.h to ProcessesPriv.h.
		<27>	12/21/92	JSM		Make function prototypes C++ studly, include GestaltPrivateEqu.h
									so we don't need to define gestaltGraphicsVersion here.
		<26>	12/19/92	mgl		Added StopCurrentProcess and ResumeProcess, as part of extended
									debugger support in the Process Manager.
		<25>	 3/30/92	DTY		#1025416,<DDG>: Define Gestalt selector for Skia. We’re putting
									it here because there’s no GestaltPrivate.h, and Process Manager
									is the only thing in the System that’s using this selector right
									now.
		<24>	 3/25/92	DTY		#1024114,<pvh>: Add inline for PEntryFromProcessSerialNumber
		<23>	 1/14/92	YK		Removed obsolete constant for the TSM.
		<22>	 1/11/92	YK		Two more calls for TSM. NewTSMLayerOwner to get the event for
									the floating window. RouteEventToSWM to do the bottom line
									input.
		<21>	 1/10/92	YK		Added definitions for supporting the Text Services Manager.
		<20>	 2/21/91	DFH		dba,#82504, #82681, #83168, #83182, #83207: Added
									SysZoneFloatSizes.
		<19>	 1/28/91	DFH		JSM,#81425:Add EnableSwitching and DisableSwitching calls.
		<18>	 1/21/91	DFH		(KSM) Removed Process Menu IDs, since they are now in
									MenuMgrPriv.h, as the Application Menu IDs.
		<17>	12/20/90	DFH		(dba) Added GetNextHighLevelEvent.
		<16>	12/14/90	DFH		Added SynchIdleTime.
		<15>	 11/4/90	dba		use (void) instead of (), also add some const to parameters
		<14>	 9/10/90	DFH		Changed iconHelpString to itemHelpString (wow!).
		<13>	 7/25/90	DFH		Added InitApplication, CleanupApplication, and SndAppDead.
		<12>	 7/19/90	DFH		Removed iconColor from AddAppleMenuItem.
		<11>	  6/8/90	DFH		Added ProcessMenuResourceID and ProcessMenuID.
		<10>	 5/20/90	ngk		Used VNProcPtr in volume Notification procs.
		 <9>	  5/7/90	DFH		Get/SetProcessTrapAddress use TrapType.
		 <8>	 4/16/90	DFH		Reorganized the file to group the call glue with the
									structures.  Now uses unsigned fields whenever possible.
									Fixed AddAppleMenuItem to use unsigned short for itemStyle
									(since Pascal and C don't agree on how to pass a byte).
		 <7>	 4/11/90	KSM		Added auxMenuHelpString to AuxMenuItemRec.
		 <6>	 3/20/90	DFH		Added iconColor and itemHelpString, and changed itemStyle to short
		 <5>	  2/8/90	DFH		Fixed this list (had comment ender on BEGIN EASE line).
		 <4>	  2/8/90	DFH		Copied projector revision comments to this file.
		 <3>	  2/5/90	DFH		Added enteredDebugger.
		 <2>	  1/3/90	DFH		Added itemStyle to AddAppleMenuItem.  Reversed order of GetProcessFromLayer parms.

*/

/***********************************************************
** BEGIN EASE MODIFICATION HISTORY
** 1.3	DFH 12/07/1989 Fixed up C++ friendship
** 1.2	CCH 12/07/1989 Made it C++ friendly
** 1.1	ngk 12/01/1989 Added System Debugger interfaces
** 1.0	CCH 10/16/1989 Adding to EASE.
** END EASE MODIFICATION HISTORY
************************************************************/


#ifndef __PROCESSESPRIV__
#define __PROCESSESPRIV__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __PACKAGES__
#include <Packages.h>
#endif

#ifndef __MENUS__
#include <Menus.h>
#endif

#ifndef __WINDOWS__
#include <Windows.h>
#endif

#ifndef __LAYERS__
#include <Layers.h>
#endif

#ifndef __GESTALTPRIVEQU__
#include <GestaltPrivateEqu.h>
#endif

#ifndef __PROCESSES__
#include <Processes.h>
#endif

/*************************************************************************
 *						Application Menu.
 *************************************************************************/

/* Item numbers */
#define HIDE_APP_ITEM			(1)
#define HIDE_OTHERS_ITEM		(2)
#define SHOW_ALL_ITEM			(3)
#define APPLICATION_MENU_COUNT	(4)

/*************************************************************************
 *						Auxiliary menu item data.
 *************************************************************************/

/* Information record returned by GetAuxMenuItem */
struct AuxMenuItemRec {
	Handle				auxMenuIconHandle;
	unsigned short		auxMenuIconSize;
	unsigned short		auxMenuIconGray;
	unsigned short		auxMenuScript;
	StringHandle		auxMenuHelpString;
};

#ifndef __cplusplus
typedef struct AuxMenuItemRec AuxMenuItemRec;
#endif __cplusplus
typedef AuxMenuItemRec *AuxMenuItemRecPtr;

#ifdef __cplusplus
extern "C" {
#endif

pascal OSErr GetAuxMenuItem(MenuHandle theMenu, unsigned char *pItemEntry, AuxMenuItemRecPtr theStorage, unsigned long recLength)
    = {0x3F3C,0x003E,0xA88F};

#ifdef __cplusplus
}
#endif

/*************************************************************************
 *						Volume notification interface.
 *************************************************************************/

/* Typedef and values for the VNBNotice field. */
typedef unsigned short	VolumeNotice;
#define VNMounted				(0)
#define VNAboutToGoOffline		(1)
#define VNOffline				(2)
#define VNAboutToUnmount		(3)
#define VNUnmount				(4)

/* Definition of the volume notification parameter block */
struct VolumeNoticeBlk {
	unsigned long		VNBLength;
	VolumeNotice		VNBNotice;
	unsigned short		VNBVolume;
	unsigned long		VNBRefCon;
	OSErr				VNBResult;
};

#ifndef __cplusplus
typedef struct VolumeNoticeBlk VolumeNoticeBlk;
#endif __cplusplus
typedef VolumeNoticeBlk *VolumeNoticeBlkPtr;

/* Prototype of the notification routine. */
typedef pascal OSErr (*VNProcPtr)(VolumeNoticeBlkPtr pParams);

#ifdef __cplusplus
extern "C" {
#endif

pascal OSErr RequestVolumeNotification(VNProcPtr pRoutine, unsigned long refCon)
    = {0x3F3C,0x0042,0xA88F};

pascal OSErr DeclineVolumeNotification(VNProcPtr pRoutine, unsigned long refCon)
    = {0x3F3C,0x0043,0xA88F};

/*************************************************************************
 *							Shell support
 *************************************************************************/

/* AppleEvent sent to app launched from FINDERNAME at boot time */
#define aeStartup						'boot'

/* AppleEvent and routines to customize the Apple menu */
#define aeAppleMenuItemSelect			'amis'
#define aeAppleMenuItemKeyword			'amis'

pascal OSErr AddAppleMenuItem(StringPtr itemName, ScriptCode itemScript, unsigned short itemStyle, Handle itemIcon, unsigned short itemMark, StringPtr itemHelpString, unsigned long itemRefCon)
    = {0x3F3C,0x0031,0xA88F};

#define DELETE_ALL_ITEMS (0)
pascal OSErr DeleteAppleMenuItem(unsigned long itemRefCon)
    = {0x3F3C,0x0032,0xA88F};

/* Routine to allocate a layer to implement the desktop */
pascal OSErr NewDesktopLayerOwner(LayerPtr *ppNewLayer)
    = {0x3F3C,0x0014,0xA88F};

// Routine to get a PEntry from a Process Serial Number
pascal Ptr PEntryFromProcessSerialNumber(ProcessSerialNumberPtr pPSN)
	= {0x3F3C,0x004F,0xA88F};

/*************************************************************************
 *							System Debugger Support
 *************************************************************************/

/* System error generated when user types the debugger key combination. */
#define enterDebugger			(110)

/* Identifier of AppleEvent notifying debugger that debuggee now not frontmost */
#define aeDebuggerNotify		'dbrk'

pascal OSErr RegisterDebugger(const ProcessSerialNumber *, Ptr entryRoutine, Ptr exitRoutine, Ptr toAppRoutine, unsigned short debugKey)
    = {0x3F3C,0x0030,0xA88F};

pascal OSErr GetProcessTrapAddress(const ProcessSerialNumber *, Ptr *trapAddr, TrapType trapType, unsigned short trapNum)
    = {0x3F3C,0x002C,0xA88F};

pascal OSErr SetProcessTrapAddress(const ProcessSerialNumber *, Ptr trapAddr, TrapType trapType, unsigned short trapNum)
    = {0x3F3C,0x002D,0xA88F};

pascal OSErr ReadWriteProcessMemory(const ProcessSerialNumber *, Ptr procMemPtr, unsigned long byteCount, Ptr callerMemPtr, Boolean doRead)
    = {0x3F3C,0x002E,0xA88F};

pascal OSErr ReadWriteProcessFPURegs(const ProcessSerialNumber *, Ptr callerMemPtr, Boolean doRead)
    = {0x3F3C,0x002F,0xA88F};

pascal OSErr KillProcess(const ProcessSerialNumber *)
    = {0x3F3C,0x0044,0xA88F};

/*************************************************************************
 *							Extended Debugger Support
 *************************************************************************/
 
pascal OSErr StopCurrentProcess(ProcessSerialNumberPtr switchToProc, Boolean toFront)
    = {0x3F3C,0x0051,0xA88F};

pascal OSErr ResumeProcess(ProcessSerialNumberPtr pPSN, Boolean toFront)
    = {0x3F3C,0x0052,0xA88F};

 /*************************************************************************
 *					Support for (as yet) unpublished Layer Manager.
 *************************************************************************/

pascal OSErr GetProcessFromLayer(ProcessSerialNumberPtr, LayerPtr)
    = {0x3F3C,0x0039,0xA88F};

 /*************************************************************************
 *							Multi Layer Support.
 *************************************************************************/
	
pascal OSErr BringWindowToFrontLayer(WindowPtr window, Boolean othersToBack)
    = {0x3F3C,0x0057,0xA88F};

pascal OSErr MergeProcessLayers(Boolean toFront)
    = {0x3F3C,0x0058,0xA88F};

pascal WindowPtr GetNextWindow(WindowPtr window)
	= {0x3F3C,0x0059,0xA88F};

 /*************************************************************************
 *					Support for application resource tracking.
 *************************************************************************/

pascal void InitApplication(void)
	= {0xAAFA};

pascal void SynchIdleTime(void)
	= {0xABF7};

pascal void CleanupApplication(void)
	= {0xAAFB};

pascal void SndAppDead(void)
	= {0xA0B8};

pascal OSErr GetSystemClientProcess(ProcessSerialNumberPtr)
    = {0x3F3C,0x003F,0xA88F};

pascal OSErr BeginSystemMode(void)
    = {0x3F3C,0x0040,0xA88F};

pascal OSErr EndSystemMode(void)
    = {0x3F3C,0x0041,0xA88F};

 /*************************************************************************
 *			Support for high level event checking from the system.
 *************************************************************************/

pascal Boolean GetNextHighLevelEvent(short, EventRecord *, Boolean)
    = {0x3F3C,0x0012,0xA88F};

 /*************************************************************************
 *			Scheduler control.
 *************************************************************************/

pascal void
DisableSwitching(void)
    = {0x3F3C,0x0019,0xA88F};
		
pascal void
EnableSwitching(void)
    = {0x3F3C,0x001A,0xA88F};

/*************************************************************************
 *			Bonus Temporary Memory vs System Heap information.
 *************************************************************************/

pascal OSErr
SysZoneFloatSizes(unsigned long *hiSysRoom, unsigned long *lowTempRoom)
    = {0x3F3C,0x0047,0xA88F};

/*************************************************************************
 *			Support for the Text Services Manager.
 *************************************************************************/

pascal OSErr
NewFloatLayer(LayerPtr *layer)
    = {0x3F3C,0x0048,0xA88F};

pascal OSErr
DisposeFloatLayer(LayerPtr *layer)
    = {0x3F3C,0x0049,0xA88F};

pascal OSErr
PostFakeKeyDown(EventRecord *theEvent)
    = {0x3F3C,0x004A,0xA88F};

pascal OSErr
PostText(Ptr textPtr,short len)
    = {0x3F3C,0x004B,0xA88F};

pascal Boolean
InlineAware( const ProcessSerialNumber *pPSN, Boolean aware)
    = {0x3F3C,0x004C,0xA88F};

pascal OSErr
NewTSMLayerOwner( const ProcessSerialNumber *pPSN)
    = {0x3F3C,0x004D,0xA88F};

pascal Boolean
RouteEventToSWM( Boolean doRoute)
    = {0x3F3C,0x004E,0xA88F};


/*************************************************************************
 *			Support for the Drag Manager, etc.
 *************************************************************************/

pascal OSErr CallProcInProcess( const ProcessSerialNumber *PSNToCall,
									ProcPtr theProc,
									Ptr params,			// ptr to struct w/reverse order params
									unsigned short paramSize)
	= {0x3F3C,0x0053, 0xA88F};

pascal OSErr GetDesktopLayerOwner(ProcessSerialNumber *pPSN)
	= {0x3F3C,0x0056,0xA88F};

#ifdef __cplusplus
}
#endif

#endif
