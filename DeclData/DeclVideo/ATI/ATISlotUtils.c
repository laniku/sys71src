/*
	File:		ATISlotUtils.c

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 11/5/93	fau		first checked in
		 <1>	10/27/93	fau		first checked in
		 <1>	10/19/93	fau		first checked in

*/

/*-------------------------------------------------------------------------
*start
*
*Name:		ATISlotUtils.c
*Creator:	George D. Wilson Jr.
*Date:		6/19/92
*
*Purpose:	Contains routines to works with video slot resources
*
*Category:
*File:		ATISlotUtils.c
*
*Exports:	MonitorIDToSpID
*			FindVideoTimingStruct
*			GetTimingSBlock
*			GetBitDepth
*			GetRowBytes
*			GetNumLines
*			PruneMonitors
*
*Locals:
*
*Detailed:
*
*Note:
*
*History:
*
*	  Date		Programmer					Modification
*	--------	----------		-----------------------------------------
*
*stop
*-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
*
*								Includes
*
*-----------------------------------------------------------------------*/

#include		<Types.h>
#include		<Video.h>
#include		<Devices.h>
#include		<Errors.h>
#include		<OSUtils.h>
#include		<Slots.h>
#include		<Memory.h>

#include		"NubEqu.h"
#include		"ATIStdTypes.h"
#include		"ATIDrvr.h"

/*-------------------------------------------------------------------------
*
*							Imported Variables
*
*-----------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
*
*							Imported Procedures
*
*-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
*
*						Local Typedefs and Defines
*
*-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
*
*							Exported Variables
*
*-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
*
*							Exported Procedures
*
*-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
*
*							Local Variables
*
*-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
*
*					Beginning of Procedure Definitions
*
*-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
*start
*
*Name:		MonitorIDToSpID
*Creator:	George D. Wilson Jr.
*Date:		6/12/92
*
*Purpose:	Transforms a monitor id into the appropriate slot resource id.
*
*Category:
*File:		ATISlotUtils.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:		UInt8
*
*Detailed:
*
*Algorithm:
*
*Note:		Today the monitor identification is the slot manager spId.
*			You must be careful not get the header file used here out of
*			sync with the declaration ROM assembler file.
*
*			We only have values for the 13" RGB currently.
*
*History:
*
*	  Date		Programmer					Modification
*	--------	----------		-----------------------------------------
*
*stop
*-----------------------------------------------------------------------*/
UInt8
MonitorIDToSpID(UInt8 monitorId)
{

//	UInt8		spId;

//	DebugStr("\pMonitorIDToSpID");

	return(monitorId);
	
} /* End of MonitorIDToSpID */


/*-------------------------------------------------------------------------
*start
*
*Name:		GetNumLines
*Creator:	George D. Wilson Jr.
*Date:		6/22/92
*
*Purpose:	Returns the number of vertical lines for the specified monitor/mode.
*
*Category:
*File:		ATISlotUtils.c
*
*Calls:
*
*Called By:
*
*Entry:		rowBytes	-	If the video parameters structure couldn't be
*							located zero is returned.  Otherwise a 16 bit
*							value indicating the number of vertical lines
*							is returned.
*
*Alters:
*
*Exit:		UInt16
*
*Detailed:
*
*Algorithm:
*
*Note:
*
*History:
*
*	  Date		Programmer					Modification
*	--------	----------		-----------------------------------------
*
*stop
*-----------------------------------------------------------------------*/
UInt16
GetNumLines(UInt8 monitorID,  UInt8 videoMode, UInt8 theSlot)
{

	OSErr			err;
//	UInt8			spId;
	SpBlock			spPb;
	char			*p;
	short			i;
	VPBlockPtr		vpPtr;
	Rect			bounds;

//	DebugStr("\pGetNumLines");

	return(kNumLines480);
	
	p = (char *) &spPb;
	for ( i = 0; i < sizeof(SpBlock); i++ ) *p++ = 0;
	
	spPb.spSlot = theSlot;
	spPb.spID = MonitorIDToSpID(monitorID);		// The id of the monitor sRsrc
	err = SRsrcInfo(&spPb);						// Find it, it better be there
	if ( err != noErr ) return(0);				// Something bad has happened
	
	spPb.spID = videoMode;						// Find the structure for the mode
	err = SFindStruct(&spPb);					// Go find it
	if ( err != noErr ) return(0);				// Couldn't structure

	spPb.spID = mVidParams;						// Get the video mode structure
	err = SGetBlock(&spPb);
	if ( err != noErr ) return(0);				// Couldn't structure
	
	vpPtr = (VPBlockPtr) spPb.spResult;
	bounds = vpPtr->vpBounds;					// Save screen bounds value
	DisposPtr((Ptr) spPb.spResult);
	return(bounds.bottom-bounds.top);
	
} /* End of GetNumLines */


/*-------------------------------------------------------------------------
*start
*
*Name:		GetBitDepth
*Creator:	George D. Wilson Jr.
*Date:		6/22/92
*
*Purpose:	Returns the bit depth for the specified monitor/mode.
*
*Category:
*File:		ATISlotUtils.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:		UInt16
*
*Detailed:
*
*Algorithm:
*
*Note:
*
*History:
*
*	  Date		Programmer					Modification
*	--------	----------		-----------------------------------------
*
*stop
*-----------------------------------------------------------------------*/
UInt16
GetBitDepth(UInt8 monitorID,  UInt8 videoMode, UInt8 theSlot)
{

	OSErr			err;
//	UInt8			spId;
	SpBlock			spPb;
	char			*p;
	short			i;
	VPBlockPtr		vpPtr;
	UInt16			depth;

//	DebugStr("\pGetBitDepth");
	
	return(8);
	
	p = (char *) &spPb;
	for ( i = 0; i < sizeof(SpBlock); i++ ) *p++ = 0;
	
	spPb.spSlot = theSlot;
	spPb.spID = MonitorIDToSpID(monitorID);		// The id of the monitor sRsrc
	err = SRsrcInfo(&spPb);						// Find it, it better be there
	if ( err != noErr ) return(0);				// Something bad has happened
	
	spPb.spID = videoMode;						// Find the structure for the mode
	err = SFindStruct(&spPb);					// Go find it
	if ( err != noErr ) return(0);				// Couldn't structure

	spPb.spID = mVidParams;						// Get the video mode structure
	err = SGetBlock(&spPb);
	if ( err != noErr ) return(0);				// Couldn't structure
	
	vpPtr = (VPBlockPtr) spPb.spResult;
	depth = vpPtr->vpPixelSize;					// Save depth
	DisposPtr((Ptr) spPb.spResult);
	return(depth);
	
} /* End of GetBitDepth */


/*-------------------------------------------------------------------------
*start
*
*Name:		GetRowBytes
*Creator:	George D. Wilson Jr.
*Date:		6/22/92
*
*Purpose:	Returns the rowBytes value for the specified monitor and mode.
*
*Category:
*File:		ATISlotUtils.c
*
*Calls:
*
*Called By:
*
*Entry:		rowBytes	-	If the video parameters structure couldn't be
*							located zero is returned.  Otherwise a 16 bit
*							value indicating the rowbytes for the mode is
*							returned.
*
*Alters:
*
*Exit:		UInt16
*
*Detailed:
*
*Algorithm:
*
*Note:
*
*History:
*
*	  Date		Programmer					Modification
*	--------	----------		-----------------------------------------
*
*stop
*-----------------------------------------------------------------------*/
UInt16
GetRowBytes(UInt8 monitorID,  UInt8 videoMode, UInt8 theSlot)
{

	OSErr			err;
//	UInt8			spId;
	SpBlock			spPb;
	char			*p;
	short			i;
	VPBlockPtr		vpPtr;
	UInt16			rowBytes;
	unsigned long	data;

	IOLongWrite(0xF2800000, 0x02 << 12);
	data = LByteSwap(*(unsigned long *)0xF2C00000);					// Get Vendor ID

	if ( data == (0x1002 | (0x4158 << 16)) ) {	// look for ATI
		return(1024);
	}

	if ( data == (0x100E | (0x9001 << 16)) ) {	// look for Diamond
		return(640);
	}
	
	return(640);
	
	p = (char *) &spPb;
	for ( i = 0; i < sizeof(SpBlock); i++ ) *p++ = 0;
	
	spPb.spSlot = theSlot;
	spPb.spID = MonitorIDToSpID(monitorID);		// The id of the monitor sRsrc
	err = SRsrcInfo(&spPb);						// Find it, it better be there
	if ( err != noErr ) return(0);				// Something bad has happened
	
	spPb.spID = videoMode;						// Find the structure for the mode
	err = SFindStruct(&spPb);					// Go find it
	if ( err != noErr ) return(0);				// Couldn't structure

	spPb.spID = mVidParams;						// Get the video mode structure
	err = SGetBlock(&spPb);
	if ( err != noErr ) return(0);				// Couldn't structure
	
	vpPtr = (VPBlockPtr) spPb.spResult;
	rowBytes = vpPtr->vpRowBytes;				// Save rowBytes value
	DisposPtr((Ptr) spPb.spResult);
	return(rowBytes);
	
} /* End of GetRowBytes */


/*-------------------------------------------------------------------------
*start
*
*Name:		FindVideoTimingStruct
*Creator:	George D. Wilson Jr.
*Date:		6/12/92
*
*Purpose:	Locates the proper sRsrc for the given monitor.
*
*Category:
*File:		ATISlotUtils.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:		Ptr
*
*Detailed:
*
*Algorithm:
*
*Note:
*
*History:
*
*	  Date		Programmer					Modification
*	--------	----------		-----------------------------------------
*
*stop
*-----------------------------------------------------------------------*/
Ptr
FindVideoTimingStruct(UInt8 monitorID, UInt8 theSlot)
{
	OSErr			err;
//	UInt8			spId;
	SpBlock			spPb;
	char			*p;
	short			i;

//	DebugStr("\pFindVideoTimingStruct");

	p = (char *) &spPb;
	for ( i = 0; i < sizeof(SpBlock); i++ ) *p++ = 0;
	
	spPb.spSlot = theSlot;
#ifdef ROM
	spPb.spID = 0x11;							// The id of the board sRsrc
#else 
	spPb.spID = 0x01;
#endif
	err = SRsrcInfo(&spPb);						// Find it, it better be there
	if ( err != noErr ) return(nil);			// Something bad has happened
	
	spPb.spID = kATIVidParmSpId;				// So far we only know about this one
	err = SFindStruct(&spPb);					// Go find it
	if ( err != noErr ) return(nil);			// Couldn't locate ATI video tree
	
	spPb.spID = MonitorIDToSpID(monitorID);		// Point to a specific monitor timimg set
	err = SFindStruct(&spPb);					// Go find it
	if ( err != noErr ) return(nil);			// There is no monitor of that type
	return((Ptr) spPb.spsPointer);				// Return slot pointer
	
} /* End of FindVideoTimingStruct */


/*-------------------------------------------------------------------------
*start
*
*Name:		GetTimingSBlock
*Creator:	George D. Wilson Jr.
*Date:		6/12/92
*
*Purpose:	Returns a pointer to the SBlock with all timing parameters.
*
*Category:
*File:		ATISlotUtils.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:		Ptr		-	If the proper SBlock is located a pointer to the
*						block of data is returned.  If the block chould
*						not be located nil is returned.
*
*Detailed:	It is the responsibility of the caller of this routine to
*			dispose of the pointer returned.
*
*Algorithm:
*
*Note:
*
*History:
*
*	  Date		Programmer					Modification
*	--------	----------		-----------------------------------------
*
*stop
*-----------------------------------------------------------------------*/
Ptr
GetTimingSBlock(UInt8 monitorID, UInt8 videoMode, UInt8 timingSelector, UInt8 ourSlot)
{

	OSErr			err;
	Ptr				vidParmPtr;
	SpBlock			spPb;
	char			*p;
	short			i;

//	DebugStr("\pGetTimingSBlock");
	
	p = (char *) &spPb;
	for ( i = 0; i < sizeof(SpBlock); i++ ) *p++ = 0;

	vidParmPtr = FindVideoTimingStruct(monitorID,ourSlot);
	if ( vidParmPtr ) {
		spPb.spsPointer = vidParmPtr;
		spPb.spID = timingSelector;
		if ( timingSelector == kSwatchParmSpId ) {
			spPb.spID = kSwatchParmSpId;
			err = SFindStruct(&spPb);
			if ( err != noErr ) return(nil);
			spPb.spID = videoMode;
		}
		err = SGetBlock(&spPb);
		if ( err == noErr ) {
			return((Ptr) spPb.spResult);
		}
	}
	return(nil);
	
} /* End of GetTimingSBlock */

/*-------------------------------------------------------------------------
*start
*
*Name:		PruneMonitors
*Creator:	George D. Wilson Jr.
*Date:		6/19/92
*
*Purpose:	Removes the unused monitors timing sResources
*
*Category:
*File:		ATISlotUtils.c
*
*Calls:
*
*Called By:
*
*Entry:		monitorID	-	The monitor identifer to keep around.
*
*			theSlot		-	The slot we are operating out of
*
*Alters:
*
*Exit:		void
*
*Detailed:
*
*Algorithm:
*
*Note:
*
*History:
*
*	  Date		Programmer					Modification
*	--------	----------		-----------------------------------------
*
*stop
*-----------------------------------------------------------------------*/
void
PruneMonitors(UInt16 cardType, UInt8 theSlot)
{

	OSErr			err;
//	UInt8			spId;
	SpBlock			spPb;
	char			*p;
	short			i;

	p = (char *) &spPb;
	for ( i = 0; i < sizeof(SpBlock); i++ ) *p++ = 0;
	
	spPb.spSlot = theSlot;	// should be 0x00
	
	if ( cardType == 0x1002) {	// look for ATI
		spPb.spID = 0x90;
	}

	if ( cardType == 0x100E) {	// look for Diamond
		spPb.spID = 0x80;				// The id of the board sRsrc
	}

	err = SDeleteSRTRec(&spPb);
	
} /* End of PruneMonitors */

/*-------------------------------------------------------------------------
*
*							End of Module
*
*-----------------------------------------------------------------------*/
