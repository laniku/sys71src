/*
	File:		IconUtilsPriv.h

	Contains:	Private C Interface for color icon plotting utilities

	Written by:	David Collins

	Copyright:	© 1990-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<27>	  9/3/92	DCL		Moved noMaskFound from private to public interfaces.  And
									removed haltIterator.  Nobody used it anyway.  And the same name
									is being used in Layers.h (with a different value).
		<26>	 3/20/92	DC		Added UpdateIconGlobals to private interfaces
		<25>	 3/19/92	DC		Changed the printerPortCache field in the GlobalIconData
									structure so that the structure would not change (and Radius
									products will not break)
		<24>	 3/17/92	DC		Exported all routines to icons.h except get and set icon device
									and SetLabel.
		<23>	10/29/91	DC		Conditionalized last change to protect CubeE
		<22>	 8/30/91	DC		Added printerPortCache to the globals to allow improved printing
									case check.
		<21>	 8/27/91	JSM		Cleanup header.
		<20>	  3/6/91	DC		RLC, #83132: Ammending check-in comments for version 19 -
									Changed labelColorBase from 128 to -16392
		<19>	  3/6/91	DC		RLC, #83132:  Replaced definition of labelColorBase with
									#include of IconUtilsPriv.h
		<18>	  1/7/91	JDR		(dba) Removing private Icon Utilities routines from the public
									interfaces and adding them here.
		<17>	12/21/90	LN		change constStrxxxParameter to ConstStrxxxParam as per change in
									Types.h
		<16>	11/19/90	DC		ngk - Moved definitions of generic icon ids from private to
									public
		<15>	 11/4/90	dba		use constStr255Parameter and make RGBColor an input parameter
									for SetLabel
		<14>	 9/15/90	DC		changed setlabel to live here
		<13>	  9/6/90	DC		Fixed the definition of icon global structure for selected cluts
		<12>	 7/25/90	DC		Added definition of my ExpandMem structure, mostly for
									parallelism with IconUtilsPriv.a
		<11>	 7/23/90	DC		Changed structure of IconSuite to have a refCon and a default
									label (refCon may not last)
		<10>	 6/29/90	DC		Added constants for icon clut and label resources
		 <9>	  6/6/90	ngk		Added generic icon resource IDs
		 <8>	 5/22/90	DC		Made IconCache a subclass of IconSuite.
		 <7>	  5/8/90	DC		Added some curDesiredFamily field to IconCache's
		 <6>	  5/4/90	DC		More minor changes
		 <5>	 4/18/90	DC		Minor changes to private interface
		 <4>	 4/10/90	DC		Merged PlotIconSuite and PlotIconCache into one routine
		 <3>	  4/9/90	DC		Added IconCache routines
		 <1>	  4/7/90	DC		first checked in

*/

#ifndef __ICONUTILSPRIV__
#define __ICONUTILSPRIV__

#define labelColorBase	-16392

#ifndef REZ

#ifndef __ICONS__
#include <Icons.h>
#endif

#define genericIconBase						-4000
#define popupMenuSymbolResource				-3990
#define standalonePopupMenuSymbolResource	-3986

#define genericMailboxIconResource			-3987	/* excise from 7.0 */
#define genericLetterIconResource			-3988	/* excise from 7.0 */


#define SUITE	0
#define CACHE	1

enum
{
	largeIcon1 = 0,
	largeIcon4,
	largeIcon8,
	smallIcon1,
	smallIcon4,
	smallIcon8,
	miniIcon1,
	miniIcon4,
	miniIcon8,
	aCIcon = 128
};

typedef unsigned short IconType;

#define IconSpace (miniIcon8 + 1)
#define IconDepthSpace (smallIcon1 - largeIcon1)
#define IconSizeSpace (IconSpace / IconDepthSpace)

#define	transformMask 0x3
#define labelMask 0x0f00
#define labelShift 8

typedef struct
{
	unsigned short	type;
	unsigned short	label;
	Handle			table[IconSpace];
} IconSuite;

typedef IconSuite *IconSuitePtr;
typedef IconSuitePtr *IconSuiteHandle;

typedef struct
{
	IconSuite		theSuite;
	void			*userPtr;
	IconGetter		userMethod;
} IconCache;

typedef	IconCache *IconCachePtr;
typedef	IconCachePtr *IconCacheHandle;

#define Labels 		8
#define Sets		8

typedef struct
{
	GDHandle		theDevice;
	long			theSeed;
	unsigned long	checkMask,
					checkResults,
					disabledCheckMask,
					disabledCheckResults;
} DeviceCheck;

typedef Handle Strings[Labels];

typedef struct
{
	Strings				labelStrings;
	long				seeds[Labels * Sets];
	CTabHandle			colorTables[Labels * Sets],
						originals[2];
	RGBColor			labelColors[Labels];
	unsigned char		**indexLists[2];
	GDHandle			virtualScreen;
	long				deviceListSize;
	DeviceCheck			deviceCheckList[0];
} GlobalIconData;

typedef GlobalIconData	*GlobalIconDataPtr;
typedef GlobalIconDataPtr *GlobalIconDataHandle;

#ifdef __cplusplus
extern "C" {
#endif

pascal void SetIconDevice(GDHandle theScreen)
	= {0x303C, 0x0218, 0xABC9};
		
pascal void GetIconDevice(GDHandle *theScreen)
	= {0x303C, 0x0220, 0xABC9};
	
pascal OSErr SetLabel(short labelNumber, const RGBColor *, ConstStr255Param)
	= {0x303C, 0x050C, 0xABC9};
	
#if TheFuture
pascal OSErr UpdateIconGlobals(void)
	= {0x303C, 0x0021, 0xABC9};
#endif

#ifdef __cplusplus
}
#endif

#endif	/*	#ifndef REZ	*/
#endif	/*	#ifndef __ICONUTILSPRIV__	*/

