
/************************************************************

Created: Monday, July 22, 1991 at 4:45 PM
 Icons.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1990-1991
  All rights reserved

	Change History (most recent first):

		<24>	11/30/92	DTY		Turning on full warnings in the C compiler complains about the
									comment delimiters in the checkin comment for <14>. Do something
									about that.
		<23>	 6/11/92	DCL		Changed "Rect *textRect"
									to "const  Rect *textRect" in RectInIconID, RectInIconSuite,
									RectInIconMethod.
									Changed all uses of "alignment" in prototypes to "align" for
									consistancy within and between the c & h files.  Cleanup &
									formatting to match Interface Stacks. Happy Happy Joy Joy.
		<22>	  5/5/92	DCL		Added 'const' to '*iconRect' in prototypes of The PtInIcon__,
									RectInIcon__, Icon__ToRgn. OK, dave?
		<21>	 3/17/92	DC		imported all private routines and typedef's from IconUtilsPriv.h
									and cleaned up constants to be enums.
		<20>	 7/23/91	JL		Checked in File from database. Changed #defines to enums.
		<19>	 1/17/91	DC		csd - Add genericExtensionIconResource
		<18>	 1/16/91	JDR		(dba) Renamed spoolFolderIconResource into
									printMonitorFolderIconResource.
		<17>	  1/7/91	JDR		(dba) Removing private Icon Utilities routines.
		<16>	11/29/90	DC		ngk - Add interface for GetIconDevice.
		<15>	11/19/90	DC		ngk - Moved System Icon ID's from private to public and added
									interfaces for PlotIconHandle PlotSICNHandle and PlotCIconHandle
	   								interfaces for PlotIconHandle PlotSICNHandle and PlotCIconHandle
		<14>	 10/09/90	JAL		Don’t use C++ comment delimiters for Think C compatability.
		<13>	 9/19/90	DC		Changed names of some routines to be more descriptive
		<12>	 9/15/90	DC		Removed SetLabel from public interface
		<11>	  9/4/90	DC		Fixed interface to icon-to-region conversion routines
		<10>	 7/25/90	DC		added interface for Get/Set cache Procs/Data
		 <9>	 7/23/90	DC		Added interfaces for SetOneScreen, etc
		 <8>	 7/12/90	DC		Removed support for ttGhost
		 <7>	  7/5/90	DC		Added interfaces for all hit-testing and region-producing
									routines.
		 <6>	 6/29/90	DC		Add labeling transforms
		 <5>	 6/13/90	DC		changed terminateInterator to haltIterator
		 <4>	  6/7/90	ngk		Added type definitions for IconSelectorValue, IconAlignmentType,
									and IconTransformType
		 <3>	 5/31/90	DC		Minor interface cleanup
		 <2>	 5/30/90	DC		Fixed name of protection identifier from __ICONUTILS__ to
									__ICONS__
		 <1>	 5/30/90	DC		first checked in as Icons.h
		 <6>	 5/22/90	DC		Made IconCaches a subclass of iconsuites.
		 <5>	  5/4/90	DC		Added Interfaces for NewIconSuite, etc.  Added new transform
									ttGhost
		 <4>	 4/11/90	DC		Changed interfaces for transforms
		 <3>	 4/10/90	DC		Made PlotIconCache and PlotIconSuite into PlotBestIcon
		 <2>	  4/9/90	DC		Added new IconCache routines
		 <1>	  4/7/90	DC		first checked in

************************************************************/


#ifndef __ICONS__
#define __ICONS__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __QUICKDRAW__
#include <QuickDraw.h>
#endif

enum {


/* The following are icons for which there are both icon suites and SICNs. */
 genericDocumentIconResource = -4000,
 genericStationeryIconResource = -3985,
 genericEditionFileIconResource = -3989,
 genericApplicationIconResource = -3996,
 genericDeskAccessoryIconResource = -3991,

 genericFolderIconResource = -3999,
 privateFolderIconResource = -3994,

 floppyIconResource = -3998,
 trashIconResource = -3993,

/* The following are icons for which there are SICNs only. */
 desktopIconResource = -3992,
 openFolderIconResource = -3997,
 genericHardDiskIconResource = -3995,
 genericFileServerIconResource = -3972,
 genericSuitcaseIconResource = -3970,
 genericMoverObjectIconResource = -3969,

/* The following are icons for which there are icon suites only. */
 genericPreferencesIconResource = -3971,
 genericQueryDocumentIconResource = -16506,
 genericExtensionIconResource = -16415,

 systemFolderIconResource = -3983,
 appleMenuFolderIconResource = -3982
};
enum {
 startupFolderIconResource = -3981,
 ownedFolderIconResource = -3980,
 dropFolderIconResource = -3979,
 sharedFolderIconResource = -3978,
 mountedFolderIconResource = -3977,
 controlPanelFolderIconResource = -3976,
 printMonitorFolderIconResource = -3975,
 preferencesFolderIconResource = -3974,
 extensionsFolderIconResource = -3973,

 fullTrashIconResource = -3984


#define large1BitMask 'ICN#'
#define large4BitData 'icl4'
#define large8BitData 'icl8'
#define small1BitMask 'ics#'
#define small4BitData 'ics4'
#define small8BitData 'ics8'
#define mini1BitMask 'icm#'
#define mini4BitData 'icm4'
#define mini8BitData 'icm8'
};

/*  alignment type values  */

enum {
atNone = 0x0,
atVerticalCenter = 0x1,
atTop = 0x2,
atBottom = 0x3,
atHorizontalCenter = 0x4,
atAbsoluteCenter = (atVerticalCenter | atHorizontalCenter),
atCenterTop = (atTop | atHorizontalCenter),
atCenterBottom = (atBottom | atHorizontalCenter),
atLeft = 0x8,
atCenterLeft = (atVerticalCenter | atLeft),
atTopLeft = (atTop | atLeft),
atBottomLeft = (atBottom | atLeft),
atRight = 0xC,
atCenterRight = (atVerticalCenter | atRight),
atTopRight = (atTop | atRight),
atBottomRight = (atBottom | atRight)
};
typedef short IconAlignmentType;


/*  transform type values  */
enum {
ttNone = 0x0,
ttDisabled = 0x1,
ttOffline = 0x2,
ttOpen = 0x3,
ttLabel1 = 0x0100,
ttLabel2 = 0x0200,
ttLabel3 = 0x0300,
ttLabel4 = 0x0400,
ttLabel5 = 0x0500,
ttLabel6 = 0x0600,
ttLabel7 = 0x0700,
ttSelected = 0x4000,
ttSelectedDisabled = (ttSelected | ttDisabled),
ttSelectedOffline = (ttSelected | ttOffline),
ttSelectedOpen = (ttSelected | ttOpen)
};
typedef short IconTransformType;


/*  Selector mask values  */
enum {
svLarge1Bit = 0x00000001,
svLarge4Bit = 0x00000002,
svLarge8Bit = 0x00000004,
svSmall1Bit = 0x00000100,
svSmall4Bit = 0x00000200,
svSmall8Bit = 0x00000400,
svMini1Bit = 0x00010000,
svMini4Bit = 0x00020000,
svMini8Bit = 0x00040000,
svAllLargeData = 0x000000ff,
svAllSmallData = 0x0000ff00,
svAllMiniData = 0x00ff0000,
svAll1BitData = (svLarge1Bit | svSmall1Bit | svMini1Bit),
svAll4BitData = (svLarge4Bit | svSmall4Bit | svMini4Bit),
svAll8BitData = (svLarge8Bit | svSmall8Bit | svMini8Bit),
svAllAvailableData = 0xffffffff
};
typedef unsigned long IconSelectorValue;	

typedef pascal OSErr (*IconAction)(ResType theType, Handle *theIcon, void *yourDataPtr);
typedef pascal Handle (*IconGetter)(ResType theType, void *yourDataPtr);

#ifdef __cplusplus
extern "C" {
#endif

pascal OSErr PlotIconID(const Rect *theRect,
							IconAlignmentType align,
							IconTransformType transform,
							short theResID)
	= {0x303C, 0x0500, 0xABC9};
	
pascal OSErr NewIconSuite(Handle *theIconSuite)
	= {0x303C, 0x0207, 0xABC9};
	
pascal OSErr AddIconToSuite(Handle theIconData,
							Handle theSuite,
							ResType theType)
	= {0x303C, 0x0608, 0xABC9};
	
pascal OSErr GetIconFromSuite(Handle *theIconData,
							Handle theSuite,
							ResType theType)
	= {0x303C, 0x0609, 0xABC9};
	
pascal OSErr ForEachIconDo(Handle theSuite,
							IconSelectorValue selector,
							IconAction action,
							void *yourDataPtr)
	= {0x303C, 0x080A, 0xABC9};
	
pascal OSErr GetIconSuite(Handle *theIconSuite,
							short theResID,
							IconSelectorValue selector)
	= {0x303C, 0x0501, 0xABC9};
	
pascal OSErr DisposeIconSuite(Handle theIconSuite,
							Boolean disposeData)
	= {0x303C, 0x0302, 0xABC9};
	
pascal OSErr PlotIconSuite(const Rect *theRect,
							IconAlignmentType align,
							IconTransformType transform,
							Handle theIconSuite)
	= {0x303C, 0x0603, 0xABC9};
	
pascal OSErr MakeIconCache(Handle *theHandle,
							IconGetter makeIcon,
							void *yourDataPtr)
	= {0x303C, 0x0604, 0xABC9};
	
pascal OSErr LoadIconCache(const Rect *theRect,
							IconAlignmentType align,
							IconTransformType transform,
							Handle theIconCache)
	= {0x303C, 0x0606, 0xABC9};

pascal OSErr PlotIconMethod(const Rect *theRect,
							IconAlignmentType align,
							IconTransformType transform,
							IconGetter theMethod,
							void *yourDataPtr)
	= {0x303C, 0x0805, 0xABC9};
	
pascal OSErr GetLabel(short labelNumber,
							RGBColor *labelColor,
							Str255 labelString)
	= {0x303C, 0x050B, 0xABC9};
	
pascal Boolean PtInIconID(Point testPt,
							const Rect *iconRect,				/* <22> */
							IconAlignmentType align,
							short iconID)
	= {0x303C, 0x060D, 0xABC9};
	
pascal Boolean PtInIconSuite(Point testPt,
							const Rect *iconRect,				/* <22> */
							IconAlignmentType align,
							Handle theIconSuite)
	= {0x303C, 0x070E, 0xABC9};
	
pascal Boolean PtInIconMethod(Point testPt,
							const Rect *iconRect,				/* <22> */
							IconAlignmentType align,
							IconGetter theMethod,
							void *yourDataPtr)
	= {0x303C, 0x090F, 0xABC9};
	
pascal Boolean RectInIconID(const Rect *testRect,
							const Rect *iconRect,				/* <22> */
							IconAlignmentType align,
							short iconID)
	= {0x303C, 0x0610, 0xABC9};
	
pascal Boolean RectInIconSuite(const Rect *testRect,
							const Rect *iconRect,				/* <22> */
							IconAlignmentType align,
							Handle theIconSuite)
	= {0x303C, 0x0711, 0xABC9};
	
pascal Boolean RectInIconMethod(const Rect *testRect,
							const Rect *iconRect,				/* <22> */
							IconAlignmentType align,
							IconGetter theMethod,
							void *yourDataPtr)
	= {0x303C, 0x0912, 0xABC9};
	
pascal OSErr IconIDToRgn(RgnHandle theRgn,
							const Rect *iconRect,				/* <22> */
							IconAlignmentType align,
							short iconID)
	= {0x303C, 0x0613, 0xABC9};
	
pascal OSErr IconSuiteToRgn(RgnHandle theRgn,
							const Rect *iconRect,				/* <22> */
							IconAlignmentType align,
							Handle theIconSuite)
	= {0x303C, 0x0714, 0xABC9};
	
pascal OSErr IconMethodToRgn(RgnHandle theRgn,
							const Rect *iconRect,				/* <22> */
							IconAlignmentType align,
							IconGetter theMethod,
							void *yourDataPtr)
	= {0x303C, 0x0915, 0xABC9};
	
pascal OSErr SetSuiteLabel(Handle theSuite, short theLabel)
	= {0x303C, 0x0316, 0xABC9};

pascal short GetSuiteLabel(Handle theSuite)
	= {0x303C, 0x0217, 0xABC9};

pascal OSErr GetIconCacheData(Handle theCache, void **theData)
	= {0x303C, 0x0419, 0xABC9};
		
pascal OSErr SetIconCacheData(Handle theCache, void *theData)
	= {0x303C, 0x041A, 0xABC9};
		
pascal OSErr GetIconCacheProc(Handle theCache, IconGetter *theProc)
	= {0x303C, 0x041B, 0xABC9};
		
pascal OSErr SetIconCacheProc(Handle theCache, IconGetter theProc)
	= {0x303C, 0x041C, 0xABC9};
	
pascal OSErr PlotIconHandle(const Rect *theRect,
							IconAlignmentType align,
							IconTransformType transform,
							Handle theIcon)
	= {0x303C, 0x061D, 0xABC9};
	
pascal OSErr PlotSICNHandle(const Rect *theRect,
							IconAlignmentType align,
							IconTransformType transform,
							Handle theSICN)
	= {0x303C, 0x061E, 0xABC9};
	
pascal OSErr PlotCIconHandle(const Rect *theRect,
							IconAlignmentType align,
							IconTransformType transform,
							CIconHandle theCIcon)
	= {0x303C, 0x061F, 0xABC9};
	
#ifdef __cplusplus
}
#endif

#endif
