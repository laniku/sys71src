/*
	File:		DisplaysPriv.h

	Contains:	Private Headers for the Display Manager

	Written by:	Ian Hendry

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<14>	 11/5/93	IH		Sync with Excelsior.
	  <SM13>	10/10/93	IH		Sync with Excelsior for ROM build.
		<12>	 9/10/93	IH		Fix cursor bug in horror ROMs and SuperMario.
		<11>	 8/26/93	IH		#1108969 <KON>: Added some more debug defines. Added room for
									res-independent QD info into state record.
		<10>	 8/16/93	IH		#1099391 <KON>: Sync w/Reality. Fix apple event notification to
									procs ptrs. Update DisplayMgr globals struct to match
									DisplaysPriv.h
	   <SM9>	08-06-93	jmp		Updated the timing constants used by the Display Manager for
									non-intelligent displays.
		 <8>	  8/4/93	IH		#1101633,1098397,1101795,1101636,1102280 <KON>: Fix 1102280.
									Propagate DisplayState handles through more calls. Add trap for
									getting the decl rom info so it is easy to patch. Add Trap for
									animation. Make GetROMMultiModeTable a trap so I can patch it.
		 <7>	 6/25/93	IH		Fix DM_AddDisplay to include new parameters. Changed macros to
									use "_DisplayDispatch"
		 <6>	 6/22/93	IH		Fix multimode tables to have unsigned shorts.
		 <5>	  6/1/93	IH		Add private trap selector to get timing mode table.
		 <4>	 5/28/93	IH		#1081805,1086363: Reordered call selectors to make Finder calls
									private.
		 <3>	  4/8/93	IH		Add support for mode switching.  Added some prototypes for
									DisplayMgrUtils.c
		 <2>	 3/31/93	IH		Clean up for SuperMario.
		 <1>	 3/25/93	IH		first checked in
		 <5>	 3/24/93	IH		Add Prototype for RecalcMenuBar.  I may have added
									DMSetMainDisplay here too.  If so I will move it to Displays.h
									next time I check these files in (are not modal checkin windows
									great??).
		 <4>	 3/17/93	IH		Move private calls from Displays.h
		 <3>	  3/5/93	IH		Added more stuff.
		 <2>	 2/25/93	IH		Add new for desktop stuff
		 <1>	 2/23/93	IH		first checked in

*/
#pragma once

#ifndef __DISPLAYSPRIV__
#define __DISPLAYSPRIV__

//
// If the debug code is not defined to be on, then default to off
//
#ifndef DEBUG_DISPLAY_CODE
#define DEBUG_DISPLAY_CODE 0
#endif

#ifndef ENHANCE_DISPLAY_CODE
#define ENHANCE_DISPLAY_CODE 0
#endif

#ifndef __COMPONENTS__
#include <Components.h>
#endif

#ifndef __DISPLAYS__
#include <Displays.h>
#endif

#ifndef __EVENTS__
#include <Events.h>
#endif

#ifndef __LAYERS__
#include <Layers.h>
#endif

#ifndef __PROCESSES__
#include <Processes.h>
#endif

#ifndef __TRAPS__
#include <Traps.h>
#endif

#ifndef __VIDEO__
#include <Video.h>
#endif

#ifndef __WINDOWS__
#include <Windows.h>
#endif

// Make sure this is keep up with DisplaysPriv.a
enum {
	gestaltDMLatestVersion = 0x00000002,
	kDMConfigLatestVersion = 0x00000000
};

// At the moment, the mirroring code can only support two displays. 
//
#define kDMNumDisplaysSupportedByMirroring 2

#if DEBUG_DISPLAY_CODE
	#define AevtDebugPrint(x) { Str31 dbMsg; BuildMessage( dbMsg, "\p; aevt ~", (long)(x) ); DebugStr( dbMsg ); }
	#define AedescDebugPrint(x) { Str31 dbMsg; BuildMessage( dbMsg, "\p; aedesc ~", (long)(x) ); DebugStr( dbMsg ); }

	void BuildMessage( Str255 msg, Str255 pstr, long number, ... );

	#define DMDebugStr(x)	DebugStr(x)
	#define	DebugCntlDownNow()					(0 != (*((char  *)0x17b) & 0x08))
	#define	DebugCapsDownNow()					(0 != (*((char  *)0x17b) & 0x02))
	#define	Debug()					if (*((short *)0x17A) & 0x0002) Debugger()

#else
	#define AevtDebugPrint(x)
	#define AedescDebugPrint(x)
	
	#define DMDebugStr(x)
	#define	DebugCntlDownNow()					(false)
	#define	DebugCapsDownNow()					(false)
	#define	Debug()
#endif


#define FixCloseView 1			// Closeview breaks if menubar display size changes
#define FixFalseDMAwareBits 1	// Some applications set formerly reserved size bits

#define STOP_HERE	Debugger


// Desktop Components definitions

#define		kTableclothComponentType		'UDtc'
#define		kPlacematComponentType			'UDpm'
#define		kDrawProcComponentType			'UDdr'		// knows how to draw a proc

#define stacksizeof(a)	((sizeof(a)+1) & (-2) )

enum TableclothMessagesType
{
	kTableclothInit,
	kGetDrawComponentSubtype,
	kCountTableclothThumbnails,
	kGetIndexedDrawComponent,
//	kGetDrawObject,							// The Draw component gets

	kTableclothPostMessage					// Figure the real messages end at (kTableclothPostMessage - 1)
};
typedef short TableclothMessagesType;

enum DrawComponentMessagesType
{
	kDrawComponentInit,
	kDrawComponentRender,
	kDrawComponentGetRestoreData,			// Tablecloth should return a handle that can be used to re-init it after restart
	kDrawComponentRestoreComponent,			// Tablecloth should return a handle that can be used to re-init it after restart

	kDrawComponentPostMessage				// Figure the real messages end at (kTableclothPostMessage - 1)
};
typedef short DrawComponentMessagesType;


struct DrawParamBlockRec {
	RgnHandle		fullRgn;
	RgnHandle		drawRgn;
	Boolean			isThumbNail;
	Boolean			isAnimate;
	short			drawFlags;				// Future expansion (zeroed now)
	CGrafPtr		drawPort;				// grafport in which to draw
};
typedef struct DrawParamBlockRec DrawParamBlockRec, *DrawParamBlockPtr, **DrawParamBlockHdl;


pascal ComponentResult GetDrawComponentSubtype(ComponentInstance theTablecloth,OSType *drawComponentSubtype)
		= ComponentCallNow(kGetDrawComponentSubtype, stacksizeof(OSType *));

pascal ComponentResult CountThumbnails(ComponentInstance theTablecloth,short *thumbnailCount)
		= ComponentCallNow(kCountTableclothThumbnails, stacksizeof(short *));

pascal ComponentResult GetIndexedDrawComponent(ComponentInstance theTablecloth,short componentIndex,Boolean isThumbnail,Rect *intendedRect,ComponentInstance *theDrawComponent)
		= ComponentCallNow(kGetIndexedDrawComponent, stacksizeof(short )+stacksizeof(Boolean )+stacksizeof(Rect *)+stacksizeof(ComponentInstance *));


// Draw Component Calls


// This one call is known between the picker and the draw component.
// I could roll this call together with the RestoreTableCloth -- we should check this at a code review
//
// pascal ComponentResult InitTableCloth(ComponentInstance theTablecloth,long restoreVersion, Handle restoreInfo)
//		= ComponentCallNow(kDrawComponentInit, stacksizeof(long)+stacksizeof(Handle ));

pascal ComponentResult RenderTablecloth(ComponentInstance theTablecloth,DrawParamBlockPtr drawParams)
		= ComponentCallNow(kDrawComponentRender, stacksizeof(DrawParamBlockPtr));

pascal ComponentResult GetTableClothRestoreData(ComponentInstance theTablecloth,long* restoreVersion, Handle *restoreInfo)
		= ComponentCallNow(kDrawComponentGetRestoreData, stacksizeof(long*)+stacksizeof(Handle *));

pascal ComponentResult RestoreTableCloth(ComponentInstance theTablecloth,ComponentDescription *savedByInfo,long restoreVersion, Handle restoreInfo)
		= ComponentCallNow(kDrawComponentRestoreComponent, stacksizeof(ComponentDescription *)+stacksizeof(long)+stacksizeof(Handle));



enum {
	// Display Communications
	// Messages for displays components.
	
	kDMComponentSelectorCheckMode = 1,
	kDMComponentSelectorGetTag,
	kDMComponentSelectorSetTag,
	kDMComponentSelectorAssociateID

};

enum {
	// Notification Messages for extended call back routines
	
	kDMNotifyInstalled = 1,					// At install time
	kDMNotifyEvent = 2,						// Post change time
	kDMNotifyRemoved = 3,					// At remove time
	kDMNotifyPrep = 4,						// Pre change time

	// Notification Flags
	
	kExtendedNotificationProc = (1<<16)
};

// Misc constants
enum {
	kDefaultTitleBarHeight = 0x14,
	kNever = -1L,
	kFirstDisplayID = 0x100
};


#pragma procname DMExtendedNotification
typedef pascal void (*DMExtendedNotificationProcPtr)(void* userData,short theMessage,void* notifyData);



struct GDInfoRec {
	unsigned long		tickStamp;
	unsigned long		nextCall;
	ComponentInstance	tableclothInstance;
};
typedef struct GDInfoRec GDInfoRec, **GDInfoHdl;


struct DisplayInfoRec {
	DisplayIDType		displayID;
	ComponentInstance	displayComponent;				// For smart displays
	GDHandle			displayDevice;
	unsigned long		displayFlags;
	unsigned long		displayReserved;
	GDHandle			mirroredDevice;					// Link to device THIS one is mirroring (nil otherwise).
	Rect				unMirroredRect;					// Original dimensions of THIS device.
	Ptr					unMirroredBaseAddr;				// Original PixMap baseAddress of THIS device.
};
typedef struct DisplayInfoRec DisplayInfoRec, *DisplayInfoPtr, **DisplayInfoHdl;


struct MultiModeTableRec {
	unsigned short		displayConnection;
	short				offset;
};
typedef struct MultiModeTableRec MultiModeTableRec,*MultiModeTablePtr;


struct MultiModeNodeRec {
	unsigned short		timingMode;
	unsigned short		timingFlags;
};
typedef struct MultiModeNodeRec MultiModeNodeRec,*MultiModeNodePtr;


struct DisplayConfigRec {
	unsigned long		configVersion;				// Set to 0
	unsigned long		configFlags;				// Reserved
	unsigned long		configReserved;				// Reserved

	DisplayIDType		displayID;
	ComponentInstance	displayComponent;				// For smart displays
	GDHandle			displayDevice;
	unsigned long		displayFlags;
	unsigned long		displayMode;				// Functional sResource (for NuBus)
	unsigned long		displayModeReserved;		// Reserved mode info
	unsigned long		displayReserved;

	// Information about the display state
	//
	unsigned short		deviceFlags;				// Reserved
	unsigned long		deviceDepthMode;			// Video mode (from InitGDevice)
	Rect				deviceRect;					// Global position (72 dpi)
	
	// Pixmap info
	Rect				pixMapRect;					// Global position (screen dpi)
	Fixed				pixMapHResolution;			// QD resolution
	Fixed				pixMapVResolution;			// QD resolution
	long				pixMapAlignment;			// be ready for res-ind QD
	long				pixMapResReserved;			// be ready for res-ind QD
	short				pixMapPixelType;				// Chunky
	short				pixMapPixelSize;				// QD depth
	short				pixMapCmpCount;				// QD depth
	short				pixMapCmpSize;				// QD depth
	short				pixMapReserved;
	unsigned long		pixMapColorTableSeed;
};
typedef struct DisplayConfigRec DisplayConfigRec, *DisplayConfigPtr, **DisplayConfigHdl;


struct DMProcPtrRegistrationRec {
	ProcessSerialNumber		registrationPSN;
	DMNotificationProcPtr	registrationProc;
	unsigned long			registrationFlags;
	void*					registrationUserData;
};
typedef struct DMProcPtrRegistrationRec DMProcPtrRegRec,*DMProcPtrRegPtr,**DMProcPtrRegHdl;

struct DisplayManagerGlobalsRec {
	CGrafPtr			fDrawingPort;
	CGrafPort			fPortStorage;
	RgnHandle			fWorkingDeskRectRgn;
	RgnHandle			fWorkingDeskFullRgn;
	RgnHandle			fWorkingUpdateRgn;
	RgnHandle			fDeskIconRgn;
	RgnHandle			fDesktopCacheRgn;
	RgnHandle			fAnimationCacheRgn;
	
	ProcessSerialNumber	fAnimatePSN;
	unsigned long		fAnimateA5;						// Used for debugging when Display Manager is built into an application
	Ptr					fSavedDMGlobals;				// Used for debugging when Display Manager is built into an application

	unsigned long		fNextAnimateTime;
	Boolean				fIconRgnInvalid;				// T => desktop icon region has changed
	unsigned char		fDeskDrawNest;					// 0 => FillRgn and FillCRgn patches should call Display Manager (otherwise just call through) --  (unused in ROM)

	unsigned short		fDisplayEntrySize;				// Initialized to be sizeof(DisplayInfoRec)
	DisplayIDType		fDisplayNextID;

	unsigned short		fDisplayCount;					// How many displays in display table
	DisplayInfoHdl		fDisplayTable;					// Table of information about displays (FUTURE: should I sort and binary search?)
	
	unsigned short		fNotificationCount;				// How many displays in display table
	DMProcPtrRegHdl		fNotificationTable;				// 

	GDHandle			fRemovedDevices;				// List of removed devices that point to the device list

// ¥¥¥ Warning ¥¥¥
//
//	  The BlackBird/Yeager mirroring code currently accesses these globals directly.  So, donÕt move them
//	  without updating that code as well.
//
// ¥¥¥
//
	Boolean				fDevicesOverLap,				// If true, *some* gDevices are overlapped (partically or fully).
						fDevicesMirrored,				// If true, all gDevices are fully overlapped, smallest gDevice determines rectangle for all devices.
						fMirroringBlocked;				// If true, mirroring has been ÒartificallyÓ blocked (several 3rd-parties asked for this).
	unsigned char		fUnused1Byte4;					//
	
//	
// Back to normal variables
//
	Ptr					fQDA5World;						// Points to fQDGlobals
	Ptr					fQDGlobals;						//
	unsigned long		fUnused1;						//
	unsigned long		fUnused2;						//
	unsigned long		fUnused3;						//
	unsigned long		fUnused4;						//
};
typedef struct DisplayManagerGlobalsRec DisplayManagerGlobalsRec, *DisplayManagerGlobalsPtr, **DisplayManagerGlobalsHdl;

// Since globals contain a port (and there will be a port somewhere) we will have to allocate a pointer
// And given that we will allocate a pointer, we may as well put everything in it.
// Therefore GetExpandMemDisplayManagerGlobals() will contain a pointer to the globals
// #define GetDMGlobalsHdl()	((DisplayManagerGlobalsHdl )(GetExpandMemDisplayManagerGlobals()))
// #define GetDMGlobalsPtr()	(*(DisplayManagerGlobalsHdl )(GetExpandMemDisplayManagerGlobals()))

#define GetDMGlobalsPtr()	((DisplayManagerGlobalsPtr )(GetExpandMemDisplayManagerGlobals()))


#define kMaxBlocks			20
#define kMaxDevices			20

#define DM__IsColorPort(GPtr)	((GPtr) && ( 0 > (short )((CGrafPtr )GPtr)->portVersion) )


struct DMDeviceBlockRec {
	short				deviceCount;
	RgnHandle			blockRgn;
	GDHandle			devices[kMaxDevices];			// GHandle
	Point				deviceOffset[kMaxDevices];		// Amount that this device must be moved
};
typedef struct DMDeviceBlockRec DMDeviceBlockRec,*DMDeviceBlockPtr,**DMDeviceBlockHdl;


struct DMDisplayBlocksRec {
	short				blockCount;
	short				unused;							// Keep the world long aligned
	DMDeviceBlockHdl	displayBlocks[kMaxBlocks];
};
typedef struct DMDisplayBlocksRec DMDisplayBlocksRec,*DMDisplayBlocksPtr;


struct MyDeviceLoopRec {
	DrawParamBlockPtr	drawingParams;
	RgnHandle			updateRgn;
};
typedef struct MyDeviceLoopRec MyDeviceLoopRec,*MyDeviceLoopPtr;

struct DisplaysStateRec {
	unsigned long		flags;
	short				nesting;				// Keep track of number of nexting of begin and end update calls
	RgnHandle			oldGrayRgn;				// Not needed?
	DisplayIDType		oldMainDisplayID;		// What was the main device when the call started
	
	short				displayCount;
	DisplayConfigHdl	displayConfigs;
};
typedef struct DisplaysStateRec DisplaysStateRec,*DisplaysStatePtr,**DisplaysStateHdl;


struct AppCompatibilityRec {
	DisplaysStateHdl	displaysState;
	LayerPeek			appLayer;
};
typedef struct AppCompatibilityRec AppCompatibilityRec,*AppCompatibilityPtr;


// Timing mode constants for Display Manager MultiMode support
// Corresponding	.h equates are in DisplaysPriv.h
//					.a equates are in DepVideoEqu.a
//					.r equates are in DepVideoEqu.r


enum {
	timingInvalid			= 0,			// Unknown timingÉ force user to confirm.
	timingApple12			= 130,			//  512x384 (60 Hz) Rubik timing.
	timingApple12x			= 135,			//  560x384 (60 Hz) Rubik-560 timing.
	timingApple13			= 140,			//  640x480 (67 Hz) HR timing.
	timingApple13x			= 145,			//  640x400 (67 Hz) HR-400 timing.
	timingAppleVGA			= 150,			//  640x480 (60 Hz) VGA timing.
	timingApple15			= 160,			//  640x870 (75 Hz) FPD timing.
	timingApple15x			= 165,			//  640x818 (75 Hz) FPD-818 timing.
	timingApple16			= 170,			//  832x624 (75 Hz) GoldFish timing.
	timingAppleSVGA			= 180,			//  800x600 (56 Hz) SVGA timing.
	timingApple1Ka			= 190,			// 1024x768 (60 Hz) VESA 1K-60Hz timing.
	timingApple1Kb			= 200,			// 1024x768 (70 Hz) VESA 1K-70Hz timing.
	timingApple19			= 210,			// 1024x768 (75 Hz) Apple 19" RGB.
	timingApple21			= 220,			// 1152x870 (75 Hz) Apple 21" RGB.
	timingAppleNTSC_ST		= 230,			//  512x384 (60 Hz, interlaced, non-convolved).
	timingAppleNTSC_FF		= 232,			//  640x480 (60 Hz, interlaced, non-convolved).
	timingAppleNTSC_STconv	= 234,			//  512x384 (60 Hz, interlaced, convolved).
	timingAppleNTSC_FFconv	= 236,			//  640x480 (60 Hz, interlaced, convolved).
	timingApplePAL_ST		= 238,			//  640x480 (50 Hz, interlaced, non-convolved).
	timingApplePAL_FF		= 240,			//  768x576 (50 Hz, interlaced, non-convolved).
	timingApplePAL_STconv	= 242,			//  640x480 (50 Hz, interlaced, non-convolved).
	timingApplePAL_FFconv	= 244			//  768x576 (50 Hz, interlaced, non-convolved).
};

//
// Internal Routines
//
pascal void		DrawDeskPattern(RgnHandle deskRgnToFill);
void			RecalcMenuBar(void);
pascal void		CalcMBHeight(void);
pascal void		DrawMBar(void);
pascal void		GetMenuRgn(RgnHandle mBarRgn);
pascal void		DM_RedrawAll(RgnHandle clobberedRgn);
Boolean			DM_HideCursor(void);
void			DM_ShowCursor(Boolean cursorHidden);

void 			FixLowMem(GDHandle oldMainDevice, GDHandle newMainDevice, short deviceOffsetX, short deviceOffsetY);
void 			FixPorts(GDHandle newMainDevice, Boolean alwaysRestoreColors, Rect* newMainRect, PixMapHandle newMainPixMap,
						 Rect* oldMainRect, Ptr oldBaseAddress, CTabHandle oldCTable);
void			FixWindowMgrPorts(GDHandle newMainDevice);

pascal void		DisplayMgrInstall(void);
pascal OSErr	DM__GestaltProc(OSType selector, long* response);

// Warning:		DM_GetDisplayInfoByGDevice and DM_GetDisplayInfoByDisplayID() return a pointer into an unlocked handle,
//			 		so do not rely on them across call that might move memory.
DisplayInfoPtr	DM_GetDisplayInfoByGDevice(GDHandle displayDevice,Boolean failToMain);
DisplayInfoPtr	DM_GetDisplayInfoByDisplayID(DisplayIDType displayID,Boolean failToMain);

OSErr			DM_DeleteDisplayInfoByDisplayID(DisplayIDType displayID);
OSErr			DM_SetDisplayInfoByDisplayID(DisplayInfoPtr newDisplayInfo);

pascal void		DM_InitQDWorld(DisplayManagerGlobalsPtr dmGlobals);

OSErr			PrepImmediateUpdate(OSErr currentError, DisplaysStateHdl *displayState,THz *savedZone);
OSErr			FinishImmediateUpdate(OSErr currentError, DisplaysStateHdl displayState,THz savedZone);
Boolean			IsProcessMgrOkay(void);
OSErr			CallAllProcesses(ProcPtr theProc,Ptr userData);
pascal void		InterProcessChangeMainDevice(GDHandle newMainDevice);
pascal void		InterProcessChangedModes(GDHandle changedDevice);

//
// Trap Routines
//
pascal OSErr	DM_InitDisplayManager(void);
pascal OSErr	DM_InstallDisplayManager(void);
pascal OSErr	DM_KillDisplayManager(void);
pascal void		DM_DrawDesktopRect(Rect *drawRect);
pascal void		DM_DrawDesktopRegion(RgnHandle drawRgn);
pascal OSErr	DM_SetDesktopIconRgn(RgnHandle iconRgn);
pascal OSErr	DM_GetDesktopIconRgn(RgnHandle *iconRgn);
pascal void		DM_ChangedDesktopIconRgn(void);
pascal Boolean	DM_DeskClick(EventRecord* theEvent);
pascal OSErr	DM_KeepWindowOnscreen(WindowPeek theWindow,RgnHandle oldGrayRgn);
pascal OSErr	DM_NotifyAllProcesses(DisplaysStateHdl displayState);
pascal OSErr	DM_GetROMMultiModeTable(MultiModeTablePtr* multiModeTable);
pascal OSErr	DM_GiveDeskTime(void);
pascal OSErr	DM_GetBestDepthModeInfo(GDHandle theDevice,VDSwitchInfoPtr modeInfo,unsigned long depthMode,short* bestDepth, Rect* modeRect);
pascal OSErr	DM_PrivateBeginConfigureDisplays(DisplaysStateHdl *displayState,Boolean internalCall);
pascal OSErr	DM_RemoveCurrentProcessProcs(void);

pascal GDHandle DM_GetFirstScreenDevice(Boolean activeOnly);
pascal GDHandle DM_GetNextScreenDevice(GDHandle theDevice,Boolean activeOnly);

pascal OSErr	DM_NewDisplay(GDHandle* newDevice,short driverRefNum,unsigned long mode,unsigned long reserved,DisplayIDType displayID,ComponentInstance displayComponent,DisplaysStateHdl displayState);
pascal OSErr	DM_DisposeDisplay(GDHandle disposeDevice,DisplaysStateHdl displayState);

pascal OSErr	DM_AddDisplay(GDHandle newDevice,short driver,unsigned long mode, unsigned long reserved,DisplayIDType displayID,ComponentInstance displayComponent,DisplaysStateHdl displayState);
pascal OSErr	DM_MoveDisplay(GDHandle moveDevice,short x,short y,DisplaysStateHdl displayState);
pascal OSErr	DM_EnableDisplay(GDHandle addDevice,DisplaysStateHdl displayState);
pascal OSErr	DM_DisableDisplay(GDHandle disableDevice,DisplaysStateHdl displayState);
pascal OSErr	DM_RemoveDisplay(GDHandle removeDevice,DisplaysStateHdl displayState);

pascal OSErr	DM_GetComponentAnimateTicks(ComponentInstance animationComponent,unsigned long *goodDelay,unsigned long *maxDelay);
pascal OSErr	DM_SetComponentAnimateTicks(ComponentInstance animationComponent,unsigned long goodDelay,unsigned long maxDelay);
pascal OSErr	DM_GetNextAnimateTime(unsigned long *nextAnimateTime);
pascal OSErr	DM_SetAnimateProcess(const ProcessSerialNumberPtr animateProcess);
pascal OSErr	DM_GetDeskRegion(RgnHandle* desktopRegion);

pascal OSErr	DM_GetGDeviceTablecloth(GDHandle displayDevice,ComponentInstance *tableclothInstance);
pascal OSErr	DM_SetGDeviceTablecloth(GDHandle displayDevice,ComponentInstance tableclothInstance);

pascal OSErr	DM_SetMainDisplay(GDHandle newMainDevice,DisplaysStateHdl displayState);
pascal OSErr	DM_SetDisplayMode(GDHandle theDevice,unsigned long mode,unsigned long *depthMode,VDSwitchInfoPtr switchModeInfo,DisplaysStateHdl displayState);

pascal OSErr	DM_BeginConfigureDisplays(DisplaysStateHdl *displayState);
pascal OSErr	DM_EndConfigureDisplays(DisplaysStateHdl displayState);

pascal OSErr	DM_RegisterNotifyProc(DMNotificationProcPtr notifyProc,ProcessSerialNumberPtr animateProcess);
pascal OSErr	DM_RegisterExtendedNotifyProc(DMExtendedNotificationProcPtr notifyProc,void* notifyUserData,unsigned short nofifyFlags,ProcessSerialNumberPtr notifyProcess);
pascal OSErr	DM_RemoveNotifyProc(DMNotificationProcPtr notifyProc,ProcessSerialNumberPtr animateProcess);

pascal OSErr	DM_GetDisplayMgrA5World(unsigned long* dmA5);
pascal OSErr	DM_MoveCursor(const Point* newMouse,const long* cursorDev);					// cursorDev should be nil for now
pascal OSErr	DM_SwapDevices(GDHandle device1, GDHandle device2);
pascal OSErr	DM_GetDisplayIDByGDevice(GDHandle displayDevice, DisplayIDType *displayID, Boolean failToMain);
pascal OSErr	DM_GetGDeviceByDisplayID(DisplayIDType displayID, GDHandle* displayDevice, Boolean failToMain);

pascal OSErr	DM_QDIsMirroringCapable(Boolean *qdIsMirroringCapable);
pascal OSErr	DM_CanMirrorNow(Boolean *canMirrorNow);
pascal OSErr	DM_IsMirroringOn(Boolean *isMirroringOn);
pascal OSErr	DM_MirrorDevices(GDHandle gD1, GDHandle gD2, DisplaysStateHdl displayState);
pascal OSErr	DM_UnmirrorDevice(GDHandle gDevice, DisplaysStateHdl displayState);
pascal OSErr	DM_GetNextMirroredDevice(GDHandle gDevice, GDHandle *mirroredDevice);
pascal OSErr	DM_BlockMirroring(void);
pascal OSErr	DM_UnblockMirroring(void);

pascal OSErr	DM_SetDisplayComponent(GDHandle theDevice,ComponentInstance displayComponent);
pascal OSErr	DM_GetDisplayComponent(GDHandle theDevice,ComponentInstance *displayComponent);

pascal OSErr	DM_SetDisplayID(GDHandle theDevice,DisplayIDType displayID);


// Utility Routines
GDHandle		FindMaxCoverageDevice(const Rect* windowRect);
GDHandle		FindClosestDevice(const Rect* windowRect);
Boolean			IsActiveScreenDevice(GDHandle theDevice,Boolean activeOnly);
unsigned short	GetActiveScreenDeviceCount(Boolean activeOnly);
void			GetWindowGlobalRegion(WindowPeek theWindow,RgnHandle windowRgn,Point *structOffset, Boolean isMovable,Boolean hasStructRgn);
Rect*			LocalPinRectToRect(Rect *r,Rect *pinRect);
OSErr			CheckExpandMem(Boolean allocateIfNeeded);
Boolean			DisplayHasMenu(GDHandle aDevice);
void			FindBestDepthMode(short theSlot,VDSwitchInfoPtr modeInfo,short desiredDepth);
pascal void		UpdateScreenBits(GDHandle newMainDevice);
OSErr			GetDeviceSlotInfo(GDHandle theDevice, unsigned short* theSlot,unsigned short* theID, unsigned short* theExtDev);

OSErr			GetTimingFromDecl(GDHandle theDevice,short displayType,VDTimingInfoPtr declTiming);
OSErr			DisplayManagerCloseViewCompatibility(GDHandle theGDevice,Rect* newDeviceRect,short newDepth);
OSErr			DisplayManagerAwareBitCompatibility(ProcessInfoRec *processInfo);

void			GetDisplayConfig(GDHandle displayDevice,DisplayConfigPtr displayConfig);
OSErr			BuildNotificationAppleEvent(DisplaysStateHdl displayState,AERecord *notifyRecord);
OSErr			BuildDisplayConfigHandle(DisplayConfigHdl *displayConfigs,short *displayCount);
void			InitAEDesc(AEDesc* theDesc);

// Boolean		TestFlagBit(unsigned long flagLong,short flagBit);
// void			SetFlagBit(unsigned long *flagLong,short flagBit);

OSErr			GetGDeviceVideoMode(GDHandle theDevice,VDSwitchInfoPtr videoMode,Boolean* driverHasGetCurMode);
OSErr			SwitchVideoMode(GDHandle theDevice,VDSwitchInfoPtr newMode);
OSErr			GetDisplayConnection(GDHandle theDevice,VDDisplayConnectInfoPtr connectInfo);
OSErr			GetTimingMode(GDHandle theDevice,VDTimingInfoPtr timingInfo);
void			InitNewDisplayInfo(	DisplayIDType displayID, ComponentInstance	displayComponent, GDHandle displayDevice, unsigned long displayFlags, unsigned long displayReserved, DisplayInfoPtr newdisplayInfo);


// Display Component Calls
//

pascal ComponentResult DisplayComponentCheckDisplayMode(ComponentInstance displayComponent,GDHandle theDevice, VDDisplayConnectInfoPtr connectInfo,VDTimingInfoPtr modeTiming,unsigned short theDepth,unsigned long* switchFlags,unsigned long reserved,Boolean* modeValid)
		= ComponentCallNow(kDMComponentSelectorCheckMode, stacksizeof(VDDisplayConnectInfoPtr )+stacksizeof(VDTimingInfoPtr )+stacksizeof(unsigned short)+stacksizeof(unsigned long *)+ stacksizeof(unsigned long)+stacksizeof(Boolean *));

pascal ComponentResult DisplayComponentGetTagDisplayState(ComponentInstance displayComponent, short* isTagged)
		= ComponentCallNow(kDMComponentSelectorGetTag, stacksizeof(short *));

pascal ComponentResult DisplayComponentSetTagDisplayState(ComponentInstance displayComponent, short  isTagged)
		= ComponentCallNow(kDMComponentSelectorSetTag, stacksizeof(short ));

pascal ComponentResult DisplayComponentSetDisplayID(ComponentInstance displayComponent, DisplayIDType displayID)
		= ComponentCallNow(kDMComponentSelectorAssociateID, stacksizeof(DisplayIDType ));




// Trap Interfaces
//

pascal OSErr DMInstallDisplayManager(void)
    = {0x70FF,_DisplayDispatch}; 

pascal OSErr DMInitDisplayManager(void)
    = {0x70FE,_DisplayDispatch}; 

pascal OSErr DMKillDisplayManager(void)
    = {0x70FD,_DisplayDispatch}; 

pascal OSErr DMSetDesktopIconRgn(RgnHandle iconRgn)
    = {0x303C,0x02FC,_DisplayDispatch}; 

pascal OSErr DMGetDesktopIconRgn(RgnHandle* iconRgn)
    = {0x303C,0x02FB,_DisplayDispatch}; 

// DMKeepWindowOnscreen Used in NuMonitors.p -- do not change here without changing there too
pascal OSErr DMKeepWindowOnscreen(WindowPeek theWindow,RgnHandle oldGrayRgn)
    = {0x303C,0x04FA,_DisplayDispatch}; 

pascal OSErr DMNotifyAllProcesses(DisplaysStateHdl displayState)
    = {0x303C,0x02F9,_DisplayDispatch}; 

pascal OSErr DMSetAnimateProcess(const ProcessSerialNumberPtr animateProcess)
    = {0x303C,0x02F8,_DisplayDispatch};

// Used in Bungee Finder -- API FROZEN => do not change here without changing there too
pascal OSErr DMChangedDesktopIconRgn(void)
    = {0x70F7,_DisplayDispatch}; 

// Used in Bungee Finder -- API FROZEN => do not change here without changing there too
pascal Boolean DMDeskClick(const EventRecord* theEvent)
    = {0x303C,0x02F6,_DisplayDispatch}; 

pascal OSErr DMGetROMMultiModeTable(MultiModeTablePtr* multiModeTable)
    = {0x303C,0x02F5,_DisplayDispatch}; 

pascal OSErr DMGiveDeskTime(void)
    = {0x70F4,_DisplayDispatch}; 

pascal OSErr DMGetBestDepthModeInfo(GDHandle theDevice,VDSwitchInfoPtr modeInfo,unsigned long depthMode,short* bestDepth,Rect* modeRect)
    = {0x303C,0x0AF3,_DisplayDispatch}; 

pascal OSErr DMPrivateBeginConfigureDisplays(DisplaysStateHdl *displayState,Boolean internalCall)
    = {0x303C,0x03F2,_DisplayDispatch}; 

pascal OSErr DMRemoveCurrentProcessProcs(void)
    = {0x70F1,_DisplayDispatch}; 

pascal OSErr DMMoveCursor(Point* where, long* curDev)
    = {0x303C,0x04F0,_DisplayDispatch}; 

pascal OSErr DMRegisterExtendedNotifyProc(DMExtendedNotificationProcPtr notifyProc,void* notifyUserData,unsigned short nofifyFlags,ProcessSerialNumberPtr whichPSN)
    = {0x303C,0x07EF,_DisplayDispatch};

pascal OSErr DMSetDisplayID(GDHandle theDevice,DisplayIDType displayID)
    = {0x303C,0x04EE,_DisplayDispatch};

#endif
