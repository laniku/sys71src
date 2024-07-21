
/************************************************************

Created: Saturday, July 27, 1991 at 7:31 PM
 Video.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1986-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606

			
	Change History (most recent first):
			
		 <6>	 11/5/93	IH		Sync with Excelsior.
	   <SM5>	08-06-93	jmp		Added more csDisplayTypes.
		 <4>	 6/22/93	IH		Change kHasSerialSense to kHasDirectConnect, added some
									constants, fixed some comments.
		 <3>	  6/1/93	IH		Add new control and status calls for Display Manager (including
									some already in Video.a).
		 <2>	  4/8/93	IH		Add SwitchMode record
		<12>	 7/31/91	JL		Updated Copyright.
		<11>	 1/29/91	JL		Grouped enums into bunches of 20 for maximum C++ efficiency.
		<10>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <9>	11/13/90	JL		Fixed up comments.
		 <8>	10/24/90	JL		Changed all #defines to anonymous enums.
		 <7>	 10/8/90	JAL		Cleaned things up to match mpw version.
		 <6>	 7/18/90	jmp		Added various equasts from CARDS & DRIVERS (2nd Edition) and
									from Video.a
		 <6>	 7/18/90	jmp		Added various equates from CARDS & DRIVERS (2nd Edition) and
									from Video.a.
		 <5>	  7/2/90	jmp		Cleaned up header inserted by BBS.
		 <4>	  7/2/90	jmp		Added VDGammaRecord (from CARDS & DRIVERS, 2nd Edition).
			
	To Do:
************************************************************/


#ifndef __VIDEO__
#define __VIDEO__

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif


enum {

 mBaseOffset = 1,			/*Id of mBaseOffset.*/
 mRowBytes = 2,				/*Video sResource parameter Id's */
 mBounds = 3,				/*Video sResource parameter Id's */
 mVersion = 4,				/*Video sResource parameter Id's */
 mHRes = 5,					/*Video sResource parameter Id's */
 mVRes = 6,					/*Video sResource parameter Id's */
 mPixelType = 7,			/*Video sResource parameter Id's */
 mPixelSize = 8,			/*Video sResource parameter Id's */
 mCmpCount = 9,				/*Video sResource parameter Id's */
 mCmpSize = 10,				/*Video sResource parameter Id's */
 mPlaneBytes = 11,			/*Video sResource parameter Id's */
 mVertRefRate = 14,			/*Video sResource parameter Id's */
 mVidParams = 1,			/*Video parameter block id.*/
 mTable = 2,				/*Offset to the table.*/
 mPageCnt = 3,				/*Number of pages*/
 mDevType = 4,				/*Device Type*/

 oneBitMode = 128,			/*Id of OneBitMode Parameter list.*/
 twoBitMode = 129,			/*Id of TwoBitMode Parameter list.*/
 fourBitMode = 130,			/*Id of FourBitMode Parameter list.*/
 eightBitMode = 131			/*Id of EightBitMode Parameter list.*/
};
enum {
 sixteenBitMode = 132,		/*Id of SixteenBitMode Parameter list.*/
 thirtyTwoBitMode = 133,	/*Id of ThirtyTwoBitMode Parameter list.*/

 firstVidMode = 128,		/*The new, better way to do the above. */
 secondVidMode = 129,		/* QuickDraw only supports six video */
 thirdVidMode = 130,		/* at this time.      */
 fourthVidMode = 131,
 fifthVidMode = 132,
 sixthVidMode = 133,

 spGammaDir = 64,
    spVidNamesDir = 65
};
 
 
// csTimingFormat values in VDTimingInfo
//
// look in the declartion rom for timing info
#define kDeclROMtables	'decl'


// csConnectFlags values in VDDisplayConnectInfo
//
enum {
	kAllModesValid = 0,						// All modes not trimmed by primary init are good close enough to try
	kAllModesSafe = 1,						// All modes not trimmed by primary init are know to be safe
	kReportsTagging = 2,					// Can detect tagged displays (to identify smart monitors)
	kHasDirectConnect = 3					// True implies that driver can talk directly to device (e.g. serial data link via sense lines)
};

// csDisplayType values in VDDisplayConnectInfo
//
enum {
	kUnknownConnect = 1,						// Not sure how we’ll use this, but seems like a good idea.
	kPanelConnect = 2,							// For use with fixed-in-place LCD (TFT, aka “Active Matrix”) panels.
	kPanelTFTConnect = 2,						// Alias for kPanelConnect (because some ROM have already GM’d that way).
	kFixedModeCRTConnect = 3,					//  For use with fixed-mode (i.e., very limited range) displays.
	kMultiModeCRT1Connect = 4,					// 320x200 maybe, 12" maybe, 13" (default), 16" certain, 19" maybe, 21" maybe
	kMultiModeCRT2Connect = 5,					// 320x200 maybe, 12" maybe, 13" certain, 16" (default), 19" certain, 21" maybe
	kMultiModeCRT3Connect = 6,					// 320x200 maybe, 12" maybe, 13" certain, 16" certain, 19" default, 21" certain
	kMultiModeCRT4Connect = 7,					// Expansion to large multi mode (not yet used)
	kModelessConnect = 8,						// Expansion to modeless model (not yet used)
	kFullPageConnect = 9,						// 640x818 (to get 8bpp in 512K case) and 640x870 (these two only)
	kVGAConnect = 10,							// 640x480 VGA default -- question everything else
	kNTSCConnect = 11,							// NTSC ST (default), FF, STconv, FFconv
	kPALConnect = 12,							// PAL ST (default), FF, STconv, FFconv
	kHRConnect = 13,							// 640x400 (to get 8bpp in 256K case) and 640x480 (these two only)
	kPanelFSTNConnect = 14						// For use with fixed-in-place LCD FSTN (aka “Supertwist”) panels.
	
};

// csTimingFlags values in VDTimingInfoRec
// also low word is returned by ROM timing tables.
//
enum {
	kModeSafe = 0,							// This mode does not need confirmation
	kModeDefault = 1						// This is the default mode for this type of connection
};



enum {
/* Control Codes */
 cscReset = 0,
 cscKillIO = 1,
 cscSetMode = 2,
 cscSetEntries = 3,
 cscSetGamma = 4,
 cscGrayPage = 5,
 cscGrayScreen = 5,
 cscSetGray = 6,
 cscSetInterrupt = 7,
 cscDirectSetEntries = 8,
 cscSetDefaultMode = 9,
 cscSwitchMode = 10,
 cscSetSync = 11
};

enum {
/* Status Codes */
 cscGetMode = 2,
 cscGetEntries = 3,
 cscGetPageCnt = 4,
 cscGetPages = 4,			/* This is what C&D 2 calls it. */
 cscGetPageBase = 5,
 cscGetBaseAddr = 5,		/* This is what C&D 2 calls it. */
 cscGetGray = 6,
 cscGetInterrupt = 7,
 cscGetGamma = 8,
 cscGetDefaultMode = 9,
 cscGetCurMode = 10,
 cscGetSync = 11,
 cscGetConnection = 12,						/* Return information about the connection to the display */
 cscGetModeTiming = 13						/* Return timing info for a mode */

};

struct VPBlock {
 long vpBaseOffset;			/*Offset to page zero of video RAM (From minorBaseOS).*/
 short vpRowBytes;			/*Width of each row of video memory.*/
 Rect vpBounds;				/*BoundsRect for the video display (gives dimensions).*/
 short vpVersion;			/*PixelMap version number.*/
 short vpPackType;
 long vpPackSize;
 long vpHRes;				/*Horizontal resolution of the device (pixels per inch).*/
 long vpVRes;				/*Vertical resolution of the device (pixels per inch).*/
 short vpPixelType;			/*Defines the pixel type.*/
 short vpPixelSize;			/*Number of bits in pixel.*/
 short vpCmpCount;			/*Number of components in pixel.*/
 short vpCmpSize;			/*Number of bits per component*/
 long vpPlaneBytes;			/*Offset from one plane to the next.*/
};

typedef struct VPBlock VPBlock;
typedef VPBlock *VPBlockPtr;

struct VDEntryRecord {
 Ptr csTable;				/*(long) pointer to color table entry=value, r,g,b:INTEGER*/
};

typedef struct VDEntryRecord VDEntryRecord;
typedef VDEntryRecord *VDEntRecPtr;

/* Parm block for SetGray control call */
struct VDGrayRecord {
 Boolean csMode;			/*Same as GDDevType value (0=mono, 1=color)*/
};

typedef struct VDGrayRecord VDGrayRecord;
typedef VDGrayRecord *VDGrayPtr;

/* Parm block for SetEntries control call */
struct VDSetEntryRecord {
 ColorSpec *csTable;		/*Pointer to an array of color specs*/
 short csStart;				/*Which spec in array to start with, or -1*/
 short csCount;				/*Number of color spec entries to set*/
};

typedef struct VDSetEntryRecord VDSetEntryRecord;
typedef VDSetEntryRecord *VDSetEntryPtr;

/* Parm block for SetGamma control call */
struct VDGammaRecord {
 Ptr csGTable;				/*pointer to gamma table*/
};

typedef struct VDGammaRecord VDGammaRecord;
typedef VDGammaRecord *VDGamRecPtr;

struct VDSwitchInfoRec {
 unsigned short	csMode;		/*(word) mode depth*/
 unsigned long	csData;		/*(long) functional sResource of mode*/
 unsigned short	csPage;		/*(word) page to switch in*/
 Ptr			csBaseAddr;	/*(long) base address of page (return value)*/
 unsigned long	csReserved;	/*(long) Reserved (set to 0) */
};

typedef struct VDSwitchInfoRec VDSwitchInfoRec;
typedef VDSwitchInfoRec *VDSwitchInfoPtr;


struct VDTimingInfoRec	{
 unsigned long	csTimingMode;							// LONGINT - (long) timing mode (a la InitGDevice)
 unsigned long	csTimingReserved;      					// LONGINT - (long) reserved
 unsigned long	csTimingFormat;							// LONGINT - (long) what format is the timing info
 unsigned long	csTimingData;       					// LONGINT - (long) data supplied by driver
 unsigned long	csTimingFlags;      					// LONGINT - (long) mode within device
};
typedef struct VDTimingInfoRec VDTimingInfoRec;
typedef VDTimingInfoRec *VDTimingInfoPtr;

struct VDDisplayConnectInfoRec	{
 unsigned short	csDisplayType;      					// INTEGER - (word) Type of display connected
 unsigned short	csConnectTagged;      					// INTEGER - (word) Display is currently "it" (tagged to identify component)
 unsigned long	csConnectFlags;      					// LONGINT - (long) tell us about the connection
 unsigned long	csDisplayComponent;      				// LONGINT - (long) if the card has a direct connection to the display, it returns the display component here (FUTURE)
 unsigned long	csConnectReserved;      				// LONGINT - (long) reserved
};
typedef struct VDDisplayConnectInfoRec VDDisplayConnectInfoRec;
typedef VDDisplayConnectInfoRec *VDDisplayConnectInfoPtr;


struct VDPageInfo {
 short csMode;				/*(word) mode within device*/
 long csData;				/*(long) data supplied by driver*/
 short csPage;				/*(word) page to switch in*/
 Ptr csBaseAddr;			/*(long) base address of page*/
};

typedef struct VDPageInfo VDPageInfo;
typedef VDPageInfo *VDPgInfoPtr;

struct VDSizeInfo {
 short csHSize;				/*(word) desired/returned h size*/
 short csHPos;				/*(word) desired/returned h position*/
 short csVSize;				/*(word) desired/returned v size*/
 short csVPos;				/*(word) desired/returned v position*/
};

typedef struct VDSizeInfo VDSizeInfo;
typedef VDSizeInfo *VDSzInfoPtr;

struct VDSettings {
 short csParamCnt;			/*(word) number of params*/
 short csBrightMax;			/*(word) max brightness*/
 short csBrightDef;			/*(word) default brightness*/
 short csBrightVal;			/*(word) current brightness*/
 short csCntrstMax;			/*(word) max contrast*/
 short csCntrstDef;			/*(word) default contrast*/
 short csCntrstVal;			/*(word) current contrast*/
 short csTintMax;			/*(word) max tint*/
 short csTintDef;			/*(word) default tint*/
 short csTintVal;			/*(word) current tint*/
 short csHueMax;			/*(word) max hue*/
 short csHueDef;			/*(word) default hue*/
 short csHueVal;			/*(word) current hue*/
 short csHorizDef;			/*(word) default horizontal*/
 short csHorizVal;			/*(word) current horizontal*/
 short csHorizMax;			/*(word) max horizontal*/
 short csVertDef;			/*(word) default vertical*/
 short csVertVal;			/*(word) current vertical*/
 short csVertMax;			/*(word) max vertical*/
};

typedef struct VDSettings VDSettings;
typedef VDSettings *VDSettingsPtr;



#endif
