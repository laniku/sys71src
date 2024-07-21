/*
	File:		Displays.h

	Contains:	Display Manager Headers

	Written by:	Ian Hendry

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<10>	 11/5/93	IH		Sync with Excelsior.
	   <SM9>	10/10/93	IH		Sync with Excelsior.
		 <8>	 8/26/93	IH		#1108969 <KON>: Move Display Manager apple event constants to
									this file.
		 <7>	 8/16/93	IH		#1099391 <KON>: Sync w/Reality. Get rid of a bunch of
									preliminary data structures that are not used in DM 1.0.
		 <6>	  8/4/93	IH		#1101633,1098397,1101795,1101636,1102280 <KON>: Move Display
									Manager gestalt definitions to gestalt headers. Changed
									prototypes to use display state handles.
		 <5>	 6/25/93	IH		Clean up header and fix DMAddDisplay to include new parameters.
									Added a couple new calls to handle smart monitor components.
		 <4>	  6/1/93	IH		
		 <3>	 5/28/93	IH		#1081805,1086363: Add activeOnly booleans for
									DMGetFirstScreenDevice and DMGetNextScreenDevice. Synch
									w/Reality. Change gestaltDisplayManagerAttr so that old versions
									of bungee would ignore display manager w/different parameters.
									Rearrange the selectors to make Finder calls private.
		 <2>	  4/8/93	IH		Add support for mode switching.
		 <1>	 3/25/93	IH		first checked in
		 <5>	 3/24/93	IH		Add DMSetMainDisplay trap call.
		 <4>	 3/17/93	IH		Move private calls to DisplaysPriv.h
		 <3>	  3/5/93	IH		Move more stuff to DisplaysPriv.h
		 <2>	 2/25/93	IH		Add new for desktop stuff and cleaned up header (removed unused
									data structures).  Made it work with ThinkC environment.
		 <1>	 2/23/93	IH		first checked in

*/

// DisplayManager.h
#pragma once
#ifndef __DISPLAYS__
#define __DISPLAYS__

#ifndef __APPLEEVENTS__
#include <AppleEvents.h>
#endif

#ifndef __WINDOWS__
#include <Windows.h>
#endif

#ifndef __COMPONENTS__
#include <Components.h>
#endif

#ifndef __EVENTS__
#include <Events.h>
#endif

#ifndef __PROCESSES__
#include <Processes.h>
#endif

#ifndef _DisplayDispatch
#define _DisplayDispatch			0xABEB
#endif

// AppleEvents Core Suite
#define		kAESystemConfigNotice	'cnfg'

// Core Suite types
#define		kAEDisplayNotice		'dspl'


#define keyDMConfigVersion			'∂cvr'
#define keyDMConfigFlags			'∂cfg'
#define keyDMConfigReserved			'∂crs'
#define keyDisplayID				'∂did'
#define keyDisplayComponent			'∂dcp'
#define keyDisplayDevice			'∂dev'
#define keyDisplayFlags				'∂dfg'
#define keyDisplayMode				'∂dm '
#define keyDisplayModeReserved		'∂dmr'
#define keyDisplayReserved			'∂ddr'

#define keyDeviceFlags				'∂∂fg'
#define keyDeviceDepthMode			'∂∂dm'
#define keyDeviceRect				'∂∂re'

#define keyPixMapRect				'∂pre'
#define keyPixMapHResolution		'∂phr'
#define keyPixMapVResolution		'∂pvr'
#define keyPixMapPixelType			'∂ppt'
#define keyPixMapPixelSize			'∂pps'
#define keyPixMapCmpCount			'∂pcc'
#define keyPixMapCmpSize			'∂pcs'
#define keyPixMapAlignment			'∂ppa'
#define keyPixMapResReserved		'∂pp®'
#define keyPixMapReserved			'∂ppr'
#define keyPixMapColorTableSeed		'∂pct'


#define keyDisplayOldConfig			'dold'
#define keyDisplayNewConfig			'dnew'


typedef unsigned long DisplayIDType;


enum {			//	Switch Flags
	kNoSwitchConfirmBit = 0,				// Flag indicating that there is no need to confirm a switch to this mode
	kDepthNotAvailableBit
};


#pragma procname DMNotification
typedef pascal void (*DMNotificationProcPtr)(AppleEvent* theEvent);


// Display Manager Error Codes
//	Should be moved to Errors.h
// Display Manager Owns Error codes from -6220 to -6269
enum{
	kDMGenErr = -6220,						// J---- H. C----, what when wrong!

// Mirroring-Specific Errors
	kDMMirroringOnAlready = -6221,			// Returned by all calls that need mirroring to be off to do their thing.
	kDMWrongNumberOfDisplays = -6222,		// Can only handle 2 displays for now.
	kDMMirroringBlocked = -6223,			// DMBlockMirroring() has been called.
	kDMCantBlock = -6224,					// Mirroring is already on, can’t Block now (call DMUnMirror() first).
	kDMMirroringNotOn = -6225,				// Returned by all calls that need mirroring to be on to do their thing.

// Other Errors
	kSysSWTooOld = -6226,					// Missing critical pieces of System Software.
	kDMSWNotInitializedErr = -6227,			// Required software not initialized (eg windowmanager or display mgr).
	kDMDriverNotDisplayMgrAwareErr = -6228,	// Video Driver does not support display manager.
	kDMDisplayNotFoundErr = -6229,			// Could not find item.
	kDMDisplayAlreadyInstalledErr = -6230	// Attempt to add an already installed display.
};


#ifdef __cplusplus
extern "C" {
#endif

pascal GDHandle DMGetFirstScreenDevice(Boolean activeOnly)
    = {0x7000,_DisplayDispatch}; 

pascal GDHandle DMGetNextScreenDevice(GDHandle theDevice,Boolean activeOnly)
    = {0x7001,_DisplayDispatch}; 

pascal void DMDrawDesktopRect(Rect* globalRect)
    = {0x7002,_DisplayDispatch}; 

pascal void DMDrawDesktopRegion(RgnHandle globalRgn)
    = {0x7003,_DisplayDispatch}; 

pascal OSErr DMGetGDeviceTablecloth(GDHandle displayDevice,ComponentInstance *tableclothInstance)
    = {0x303C,0x0404,_DisplayDispatch};

pascal OSErr DMSetGDeviceTablecloth(GDHandle displayDevice,ComponentInstance tableclothInstance)
    = {0x303C,0x0405,_DisplayDispatch};

pascal OSErr DMBeginConfigureDisplays(Handle* displayState)
    = {0x303C,0x0206,_DisplayDispatch};

pascal OSErr DMEndConfigureDisplays(Handle displayState)
    = {0x303C,0x0207,_DisplayDispatch};



pascal OSErr DMAddDisplay(GDHandle newDevice,short driver,unsigned long mode,unsigned long reserved,unsigned long displayID,ComponentInstance displayComponent,Handle displayState)
    = {0x303C,0x0D08,_DisplayDispatch}; 

pascal OSErr DMMoveDisplay(GDHandle moveDevice,short x,short y,Handle	displayState)
    = {0x303C,0x0609,_DisplayDispatch}; 

pascal OSErr DMDisableDisplay(GDHandle disableDevice,Handle displayState)
    = {0x303C,0x040A,_DisplayDispatch}; 

pascal OSErr DMEnableDisplay(GDHandle enableDevice,Handle displayState)
    = {0x303C,0x040B,_DisplayDispatch}; 

pascal OSErr DMRemoveDisplay(GDHandle removeDevice,Handle displayState)
    = {0x303C,0x040C,_DisplayDispatch}; 


pascal OSErr DMGetComponentAnimateTicks(ComponentInstance animationComponent,unsigned long *goodDelay,unsigned long *maxDelay)
    = {0x303C,0x060D,_DisplayDispatch}; 

pascal OSErr DMSetComponentAnimateTicks(ComponentInstance animationComponent,unsigned long goodDelay,unsigned long maxDelay)
    = {0x303C,0x060E,_DisplayDispatch}; 

pascal OSErr DMGetNextAnimateTime(unsigned long *nextAnimateTime)
    = {0x303C,0x020F,_DisplayDispatch};

pascal OSErr DMSetMainDisplay(GDHandle newMainDevice,Handle displayState)
    = {0x303C,0x0410,_DisplayDispatch};

pascal OSErr DMSetDisplayMode(GDHandle theDevice,unsigned long mode, unsigned long* depthMode, unsigned long reserved,Handle displayState)
    = {0x303C,0x0A11,_DisplayDispatch};

pascal OSErr DMCheckDisplayMode(GDHandle theDevice,unsigned long mode, unsigned long depthMode, unsigned long* switchFlags, unsigned long reserved,Boolean* modeOk)
    = {0x303C,0x0C12,_DisplayDispatch};

pascal OSErr DMGetDeskRegion(RgnHandle* desktopRegion)
    = {0x303C,0x0213,_DisplayDispatch};

pascal OSErr DMRegisterNotifyProc(DMNotificationProcPtr notificationProc,ProcessSerialNumberPtr whichPSN)
    = {0x303C,0x0414,_DisplayDispatch};

pascal OSErr DMRemoveNotifyProc(DMNotificationProcPtr notificationProc,ProcessSerialNumberPtr whichPSN)
    = {0x303C,0x0415,_DisplayDispatch};


pascal OSErr DMQDIsMirroringCapable(Boolean *qdIsMirroringCapable)
    = {0x303C,0x0216,_DisplayDispatch};

pascal OSErr DMCanMirrorNow(Boolean *canMirrorNow)
	= {0x303C,0x0217,_DisplayDispatch};
	
pascal OSErr DMIsMirroringOn(Boolean *isMirroringOn)
	= {0x303C,0x0218,_DisplayDispatch};
		
pascal OSErr DMMirrorDevices(GDHandle gD1, GDHandle gD2, Handle displayState)
	= {0x303C,0x0619,_DisplayDispatch};

pascal OSErr DMUnmirrorDevice(GDHandle gDevice, Handle displayState)
	= {0x303C,0x041A,_DisplayDispatch};
	
pascal OSErr DMGetNextMirroredDevice(GDHandle gDevice, GDHandle *mirroredDevice)
	= {0x303C,0x041B,_DisplayDispatch};
	
pascal OSErr DMBlockMirroring(void)
	= {0x701C,_DisplayDispatch};
	
pascal OSErr DMUnblockMirroring(void)
	= {0x701D,_DisplayDispatch};

pascal OSErr DMGetDisplayMgrA5World(unsigned long* dmA5)
    = {0x303C,0x021E,_DisplayDispatch};

pascal OSErr DMGetDisplayIDByGDevice(GDHandle displayDevice, DisplayIDType *displayID, Boolean failToMain)
    = {0x303C,0x051F,_DisplayDispatch};

pascal OSErr DMGetGDeviceByDisplayID(DisplayIDType displayID, GDHandle* displayDevice, Boolean failToMain)
    = {0x303C,0x0520,_DisplayDispatch};

pascal OSErr DMSetDisplayComponent(GDHandle theDevice,ComponentInstance displayComponent)
    = {0x303C,0x0421,_DisplayDispatch};

pascal OSErr DMGetDisplayComponent(GDHandle theDevice,ComponentInstance *displayComponent)
    = {0x303C,0x0422,_DisplayDispatch};

pascal OSErr DMNewDisplay(GDHandle* newDevice,short driverRefNum,unsigned long mode,unsigned long reserved,DisplayIDType displayID,ComponentInstance displayComponent, Handle displayState)
    = {0x303C,0x0D23,_DisplayDispatch};
	
pascal OSErr DMDisposeDisplay(GDHandle disposeDevice, Handle displayState)
    = {0x303C,0x0424,_DisplayDispatch};


#if 0
//pascal OSErr DMResolveDisplayComponents(void)
//    = {0x303C,????,_DisplayDispatch};

//pascal OSErr DMSetDisplayQDResolution(GDHandle theDevice,Fixed hResolution,Fixed vResolution)
//    = {0x303C,????,_DisplayDispatch};

//pascal OSErr DMGetDisplayQDResolution(GDHandle theDevice,Fixed *hResolution,Fixed *vResolution)
//    = {0x303C,????,_DisplayDispatch};
#endif


// See ERS
// GetIndScreenResource()
//		save PRAM w/screen rsrc -- force reboot -- nah?
// GetIndScreenMode()
// GetIndScreenResource()
//
	
#ifdef __cplusplus
}
#endif


#endif
