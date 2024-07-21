/*
	File:		ATIDrvrImp.c

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	й 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 11/5/93	fau		first checked in
		 <1>	10/27/93	fau		first checked in
		 <1>	10/19/93	fau		first checked in

*/

/*-------------------------------------------------------------------------
*start
*
*Name:		ATIDrvrImp
*Creator:	George D. Wilson Jr.
*Date:		3/17/92
*
*Purpose:	Contains the implementations of the Quadra video driver routines.
*
*Category:
*File:		ATIDrvrImp.c
*
*Exports:	DoGetPages		-	Returns the number of video pages.
*			DoGrayCLUT
*			DoCheckMode
*			DoGetMode
*			DoGetEntries
*			DoGetBaseAddr
*			DoGetGray
*			DoGetInterrupt
*			DoGetGamma
*			DoGetDefaultMode
*			DoVideoReset
*			DoSetEntries
*			DoSetVideoMode
*			DoSetGamma
*			DoGrayPage
*			DoSetGray
*			DoSetInterrupt
*			DoDirectSetEntries
*			DoSetDefaultMode
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
#include		"ATI.h"
#include		"ATIDrvr.h"
#include		"ATIVideo.h"

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
extern UInt8 MonitorIDToSpID(UInt8 monitorId);
extern Ptr FindVideoTimingStruct(UInt8 monitorID, UInt8 theSlot);
extern Ptr GetTimingSBlock(UInt8 monitorID, UInt8 videoMode, UInt8 timingSelector, UInt8 ourSlot);
extern void PruneMonitors(UInt8 monitorID, UInt8 theSlot);
extern UInt16 od(UInt8 monitorID,  UInt8 videoMode, UInt8 theSlot);
extern UInt16 GetNumLines(UInt8 monitorID,  UInt8 videoMode, UInt8 theSlot);
extern UInt16 GetBitDepth(UInt8 monitorID,  UInt8 videoMode, UInt8 theSlot);

extern void DoProgramDAC(ColorSpecPtr ctPtr, UInt16 numEntries, UInt16 start, Boolean indexMode);
extern void DoProgramDACGamma(GammaTablePtr gammaPtr);
extern void DoBuildLinearRamp (ColorSpecPtr ctPtr);
extern void DoGammaCorrectCLUT(UInt16 numEntries, ColorSpecPtr orgCLUTPtr,
					ColorSpecPtr corrCLUTPtr,GammaTablePtr gammaPtr);
extern void DoEnableVideo(UInt32 theSlot);
extern void DoDisableVideo(UInt32 theSlot);

extern void DoProgramTiming (UInt32 slotNum, Ptr baseAddr, UInt8 monitorID, 
							UInt8 videoMode, UInt8 ourSlot, UInt16 rowBytes,
							Boolean enableInterrupts);
		
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
*Name:		DoGrayCLUT
*Creator:	George D. Wilson Jr.
*Date:		4/14/92
*
*Purpose:	Fills the CLUT with a gray color.
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
void DoGrayCLUT ()
{

	UInt32			i;
	UInt8			*clutAddrReg = 0;
	UInt8			*clutData;
//	UInt8			dummy;

	unsigned long	data;

//	DebugStr("\pDoGrayCLUT");
	
	IOLongWrite(0xF2800000, (0x2 << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x3;
	PerformPCIHack();
	
	IOLongWrite(0xF2800000, (0x2 << 12));
	data = LByteSwap(*(unsigned long *)0xF2C00000);					// Get Vendor ID

	if ( data == (0x1002 | (0x4158 << 16)) ) {	// look for ATI
		clutAddrReg = (UInt8 *) kDAC_W_INDEX;
		clutData = (UInt8 *) kDAC_DATA;					// Point to data register
		*clutAddrReg = 0;								// Point to first entry
		WaitForVBL();									// Wait for blanking
		for ( i = 0; i < kNumCLUTEntries; i++ ) {
			*clutData = kGrayCLUTValue;
			PerformPCIHack();
			*clutData = kGrayCLUTValue;
			PerformPCIHack();
			*clutData = kGrayCLUTValue;
			PerformPCIHack();
		}
	}
	else {
//	if ( data == (0x100E | (0x9001 << 16)) ) {	// look for Diamond
		clutAddrReg = (UInt8 *)(0xF20003C8);	// kRamWrite
		clutData = (UInt8 *)(0xF20003C9);	// kPaletteData
		*clutAddrReg = 0;								// Point to first entry
		WaitForVBL();									// Wait for blanking
		for ( i = 0; i < kNumCLUTEntries; i++ ) {
			*clutData = (unsigned char)i;
			PerformPCIHack();
			*clutData = (unsigned char)i;
			PerformPCIHack();
			*clutData = (unsigned char)i;
			PerformPCIHack();
		}
	}

	IOLongWrite(0xF2800000, (0x2 << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x2;
	PerformPCIHack();

} /* End of DoGrayCLUT */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoCheckMode
*Creator:	George D. Wilson Jr.
*Date:		4/14/92
*
*Purpose:	Returns true if the specified video mode is a valid video mode.
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
*	8/28/93		George W.		Only one mode for now.
*
*stop
*-----------------------------------------------------------------------*/
Boolean DoCheckMode (short theVideoMode)
{

//	DebugStr("\pDoCheckMode");
	
	if (theVideoMode == kFirstVideoMode) {
		return(true);
	} else {
		return(false);
	}
	
} /* End of DoCheckMode */


/*-------------------------------------------------------------------------
*start
*
*Name:		DoGetPages
*Creator:	George D. Wilson Jr.
*Date:		3/17/92
*
*Purpose:	Returns the number of video pages.
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
OSErr	DoGetPages(VDPgInfoPtr pgPtr, DCtlPtr dce)
{
#pragma	unused(dce)

//	DebugStr("\pDoGetPages");
	
	pgPtr->csPage = kNumPages;
	return(noErr);

} /* End of DoGetPages */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoGetMode
*Creator:	George D. Wilson Jr.
*Date:		3/17/92
*
*Purpose:	Returns the video page, baseAddr, and mode.
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
*	9/9/92		George W.		Return wrong base address.
*
*stop
*-----------------------------------------------------------------------*/
OSErr	DoGetMode(VDPgInfoPtr pgPtr, DCtlPtr dce)
{

	globalsPtr		g;

//	DebugStr("\pDoGetMode");
	
	g = (globalsPtr) *(dce->dCtlStorage);
	pgPtr->csPage = g->gCurrentPage;
	pgPtr->csMode = g->gCurrentMode;
//	pgPtr->csBaseAddr = g->gFBBaseAddr;
	pgPtr->csBaseAddr = g->gBaseAddr;
	return(noErr);

} /* End of DoGetMode */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoGetEntries
*Creator:	George D. Wilson Jr.
*Date:		3/17/92
*
*Purpose:	Returns the CLUT entries.
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
*
*Detailed:
*
*Algorithm:
*
*Note:		If gamma correction is enabled the values returned may not be
*			the same as the values passed to SetEntries.
*
*History:
*
*	  Date		Programmer					Modification
*	--------	----------		-----------------------------------------
*
*stop
*-----------------------------------------------------------------------*/
OSErr	DoGetEntries(VDSetEntryPtr pgPtr, DCtlPtr dce)
{

	UInt16			numEntries;
	UInt8			*clutData;
	UInt8			*clutAddrReg = 0;
	UInt32			red, green, blue;
	short			i;
	short			startEntry;
	ColorSpecPtr	cpPtr;
//	UInt8			dummy;
	globalsPtr		g;
	unsigned long	data;

//	DebugStr("\pDoGetEntries");
	
	IOLongWrite(0xF2800000, (0x2 << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x3;
	PerformPCIHack();
	
	IOLongWrite(0xF2800000, (0x2 << 12));
	data = LByteSwap(*(unsigned long *)0xf2c00000);					// Get Vendor ID

	if ( pgPtr->csTable == nil ) {
		return(statusErr);
	}
	
	g = (globalsPtr) *(dce->dCtlStorage);

	switch ( g->gCurrentMode ) {
		case kFirstVideoMode: numEntries = k8bppEntries; break;
		case kSecondVideoMode: numEntries = k2bppEntries; break;
		case kThirdVideoMode: numEntries = k4bppEntries; break;
		case kFourthVideoMode: numEntries = k8bppEntries; break;
		case kFifthVideoMode: numEntries = k16bppEntries; break;
	}
	
	if ( pgPtr->csCount > numEntries ) return(statusErr);

	cpPtr = pgPtr->csTable;
	numEntries = pgPtr->csCount + 1;

	if ( data == (0x1002 | (0x4158 << 16)) ) {	// look for ATI
		clutAddrReg = (UInt8 *) kDAC_R_INDEX;
		clutData = (UInt8 *) kDAC_DATA;
	}
	else {
//	if ( data == (0x100E | (0x9001 << 16)) ) {	// look for Diamond
		clutAddrReg = (UInt8 *)(0xF20003C7);	// kRamRead
		clutData = (UInt8 *)(0xF20003C9);		// kPaletteData
	}
	
	if (!clutAddrReg){
		IOLongWrite(0xF2800000, (0x2 << 12) | 4);
		*(unsigned char *)(0xF2C00000) = 0x2;
		PerformPCIHack();
	
		return(noErr);
	}

	if ( pgPtr->csStart == -1 ) {
		WaitForVBL();
		for ( i = 0; i < numEntries; i++ ) {
			*clutAddrReg = pgPtr->csTable[i].value;
			PerformPCIHack();
			red = *clutData; PerformPCIHack();
			green = *clutData; PerformPCIHack();
			blue = *clutData; PerformPCIHack();
			cpPtr[i].rgb.red = red;
			cpPtr[i].rgb.green = green;
			cpPtr[i].rgb.blue = blue;
		}
	}
	
	if ( pgPtr->csStart >= 0 ) {
		startEntry = pgPtr->csStart;
		*clutAddrReg = startEntry;
		PerformPCIHack();
		WaitForVBL();
		for ( i = 0; i < numEntries; i++ ) {
			red = *clutData; PerformPCIHack();
			green = *clutData; PerformPCIHack();
			blue = *clutData; PerformPCIHack();
			cpPtr[i].rgb.red = red;
			cpPtr[i].rgb.green = green;
			cpPtr[i].rgb.blue = blue;
		}
	}
	
	IOLongWrite(0xF2800000, (0x2 << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x2;
	PerformPCIHack();
	
	return(noErr);
	
} /* End of DoGetEntries */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoGetBaseAddr
*Creator:	George D. Wilson Jr.
*Date:		3/17/92
*
*Purpose:	Returns the base address of the frame buffer.
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
OSErr	DoGetBaseAddr(VDPgInfoPtr pgPtr, DCtlPtr dce)
{

	globalsPtr		g;

//	DebugStr("\pDoGetBaseAddr");
	
	g = (globalsPtr) *(dce->dCtlStorage);
	pgPtr->csBaseAddr = nil;				// Default is no page address
	if ( pgPtr->csPage == kOurVidPage ) {	// If they ask for our only page
//		pgPtr->csBaseAddr = g->gFBBaseAddr;
		pgPtr->csBaseAddr = g->gBaseAddr;
		return(noErr);						// Everything ok
	}
	return(statusErr);						// Return error indicating unsupported page
} /* End of DoGetBaseAddr */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoGetGray
*Creator:	George D. Wilson Jr.
*Date:		3/17/92
*
*Purpose:	Returns whether the driver is in color mode or grayscale mode.
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
OSErr	DoGetGray(VDGrayPtr pgPtr, DCtlPtr dce)
{

	globalsPtr		g;

//	DebugStr("\pDoGetGray");
	
	g = (globalsPtr) *(dce->dCtlStorage);
	if ( g->gLuminanceMode ) {
		pgPtr->csMode = 1;
	} else {
		pgPtr->csMode = 0;
	}
	return(noErr);
	
} /* End of DoGetGray */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoGetInterrupt
*Creator:	George D. Wilson Jr.
*Date:		3/17/92
*
*Purpose:	Returns the status of VBL interrupts enabled.
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
OSErr	DoGetInterrupt(VDPgInfoPtr flgPtr, DCtlPtr dce)
{

	globalsPtr		g;

//	DebugStr("\pDoGetInterrupt");
	
	g = (globalsPtr) *(dce->dCtlStorage);
	if ( g->gInterruptsEnabled ) {
		flgPtr->csMode = kVBLInterruptEnabled;
	} else {
		flgPtr->csMode = kVBLInterruptDisabled;
	}
	return(noErr);
	
} /* End of DoGetInterrupt */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoGetGamma
*Creator:	George D. Wilson Jr.
*Date:		3/17/92
*
*Purpose:	Returns a pointer to the current gamma table.
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
OSErr	DoGetGamma(VDGamRecPtr gPtr, DCtlPtr dce)
{

	globalsPtr		g;

//	DebugStr("\pDoGetGamma");
	
	g = (globalsPtr) *(dce->dCtlStorage);
	gPtr->csGTable = nil;							// Default is no gamma table
	if ( g->gGammaPtr ) {							// If a table exists
		gPtr->csGTable = (Ptr) (g->gGammaPtr);		// Return a the tables pointer
	}
	return(noErr);
	
} /* End of DoGetGamma */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoGetDefaultMode
*Creator:	George D. Wilson Jr.
*Date:		3/17/92
*
*Purpose:	Returns the current default value of a video sResource's spID entry.
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
OSErr	DoGetDefaultMode(VDDefModePtr dfPtr, DCtlPtr dce)
{
#pragma unused(dce)

	globalsPtr		g;
	SpBlock			spPb;
	OSErr			err;
	SPRAMRecord		sPRAM;

//	DebugStr("\pDoGetDefaultMode");
	
	g = (globalsPtr) *(dce->dCtlStorage);
	spPb.spSlot = g->gSlotNum;
	spPb.spResult = &sPRAM;
	err = SReadPRAMRec(&spPb);
	if ( err == noErr ) {							// Did we get our PRAM?
		dfPtr->csID = sPRAM.vendorUse4;
		return(noErr);
	}

	return(statusErr);
	
} /* End of DoGetDefaultMode */

//========================================================================
//	Driver Control routines
//========================================================================

/*-------------------------------------------------------------------------
*start
*
*Name:		DoVideoReset
*Creator:	George D. Wilson Jr.
*Date:		3/30/92
*
*Purpose:	
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
OSErr	DoVideoReset(VDPgInfoPtr pgPtr, DCtlPtr dce)
{
#pragma unused(pgPtr)
#pragma unused(dce)

//	DebugStr("\pDoVideoReset");
	
	return(noErr);
	
} /* End of DoVideoReset */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoSetVideoMode
*Creator:	George D. Wilson Jr.
*Date:		3/30/92
*
*Purpose:	
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
OSErr
DoSetVideoMode(VDPgInfoPtr pgPtr, DCtlPtr dce)
{

	globalsPtr		g;

//	DebugStr("\pDoSetVideoMode");
	
	if ( !DoCheckMode(pgPtr->csMode) ) return(controlErr);
	if ( pgPtr->csPage != kOurVidPage ) return(controlErr);

	g = (globalsPtr) *(dce->dCtlStorage);
	g->gCurrentMode = pgPtr->csMode;			// Remember new video mode
	if ( g->gCurrentMode == kFirstVideoMode ) {
		g->gDirectMode = false;
	} else {
		g->gDirectMode = true;
	}
	
	g->gRowBytes = GetRowBytes(g->gMonitorID,g->gCurrentMode,g->gSlotNum);
//	pgPtr->csBaseAddr = g->gFBBaseAddr;			// Always return base address
	pgPtr->csBaseAddr = g->gBaseAddr;			// Always return base address
	DoGrayCLUT();								// Fill the CLUT with all gray
//	IOWordWrite(kEXT_GE_CONFIG,0x4010);
//	DoProgramTiming(g->gBigSlotNum,(Ptr) kBaseAddress,
//					g->gMonitorID,g->gCurrentMode,g->gSlotNum,
//					g->gRowBytes,g->gInterruptsEnabled);
//	DoEnableVideo(g->gBigSlotNum);
	return(noErr);
	
} /* End of DoSetVideoMode */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoSetEntries
*Creator:	George D. Wilson Jr.
*Date:		3/30/92
*
*Purpose:	
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
*	9/21/92		George W.		Shift lum for grays bug fix.
*
*stop
*-----------------------------------------------------------------------*/
OSErr	DoSetEntries(VDSetEntryPtr pgPtr, DCtlPtr dce)
{

	volatile UInt8			*clutData;
	volatile UInt8			*clutAddrReg = 0;
//	char					*redGammaPtr;
//	char					*greenGammaPtr;
//	char					*blueGammaPtr;
//	GammaTablePtr			gammaPtr;
	short					i;
//	short					j,index;
	UInt32					red,green,blue;
	UInt32					lum;
	ColorSpecPtr			cpPtr;
//	volatile	UInt8		dummy;
	ColorSpec				tmpCTable[256];
	UInt16					start;
	globalsPtr				g;
	short					numEntries;
	unsigned long			data;

//	DebugStr("\pDoSetEntries");

	IOLongWrite(0xF2800000, (0x2 << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x3;
	PerformPCIHack();

	g = (globalsPtr) *(dce->dCtlStorage);
	if ( g->gDirectMode ) return(controlErr);			// Only supported in index modes
	if ( pgPtr->csTable == nil ) return(controlErr);

	start = pgPtr->csStart;
	cpPtr = pgPtr->csTable;
	
	numEntries = pgPtr->csCount + 1;					// Get the number of entries passed

	if (start > 255) {
		return controlErr;
	}
	if (start + numEntries > 256) {
		numEntries = 256 - start;
	}
	
	if ( g->gLuminanceMode ) {							// Create a gray ramp out of entries
		for ( i = 0; i < numEntries; i++ ) {			// Look at each entry to create ramp
			red = cpPtr[i].rgb.red * kRedLumValue;
			green = cpPtr[i].rgb.green * kGreenLumValue;
			blue = cpPtr[i].rgb.blue * kBlueLumValue;
			lum = red + green + blue;
			lum >>= 16;
			tmpCTable[i].value = cpPtr[i].value;
			tmpCTable[i].rgb.red = lum;
			tmpCTable[i].rgb.green = lum;
			tmpCTable[i].rgb.blue = lum;
		}
		if ( g->gGammaPtr != nil ) {					// If we have a gamma table correct things
			DoGammaCorrectCLUT(numEntries,tmpCTable,tmpCTable,g->gGammaPtr);
		}
	} else {
		if ( g->gGammaPtr != nil ) {					// If we have a gamma table correct things
			DoGammaCorrectCLUT(numEntries,cpPtr,tmpCTable,g->gGammaPtr);
		}
		else {
			if (start >= 0) {
				for (i = 0; i < numEntries; i++) {
					tmpCTable[start+i] = cpPtr[start+i];
				}
			}

			if (start == -1) {
				for (i = 0; i < numEntries; i++) {
					tmpCTable[i] = cpPtr[i];
				}
			}
		}
	}
	
	IOLongWrite(0xF2800000, (0x2 << 12));
	data = LByteSwap(*(unsigned long *)0xF2C00000);					// Get Vendor ID

	if ( data == (0x1002 | (0x4158 << 16)) ) {	// look for ATI
		clutAddrReg = (UInt8 *) kDAC_W_INDEX;
		clutData = (UInt8 *) kDAC_DATA;						// Point to data register
	}
	else {
//	if ( data == (0x100E | (0x9001 << 16)) ) {	// look for Diamond
		clutAddrReg = (unsigned char *)(0xF20003C8);
		clutData = (unsigned char *)(0xF20003C9);
	}
	
	if (!clutAddrReg) {
		IOLongWrite(0xF2800000, (0x2 << 12) | 4);
		*(unsigned char *)(0xF2C00000) = 0x2;
		PerformPCIHack();

		clutAddrReg = (unsigned char *)(0xF20003C8);
		clutData = (unsigned char *)(0xF20003C9);
//		return(noErr);
	}

	if ( start >= 0 ) {									// Standard fill CLUT
		*clutAddrReg = start; PerformPCIHack();			// Goto the proper clut entry
		WaitForVBL();
		for ( i = 0; i < numEntries; i++ ) {
			*clutData = tmpCTable[i].rgb.red;
			PerformPCIHack();
			*clutData = tmpCTable[i].rgb.green;
			PerformPCIHack();
			*clutData = tmpCTable[i].rgb.blue;
			PerformPCIHack();
		}
	}
	
	if ( start == -1 ) {								// Fill specific CLUT entries
		WaitForVBL();
		for ( i = 0; i < numEntries; i++ ) {
			*clutAddrReg = tmpCTable[i].value;			// Point to specific CLUT entry
 			PerformPCIHack();
			*clutData = tmpCTable[i].rgb.red;
			PerformPCIHack();
			*clutData = tmpCTable[i].rgb.green;
			PerformPCIHack();
			*clutData = tmpCTable[i].rgb.blue;
			PerformPCIHack();
		}
	}

	IOLongWrite(0xF2800000, (0x2 << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x2;
	PerformPCIHack();

	return(noErr);

} /* End of DoSetEntries */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoSetGamma
*Creator:	George D. Wilson Jr.
*Date:		3/30/92
*
*Purpose:	
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
OSErr	DoSetGamma(VDGamRecPtr pgPtr, DCtlPtr dce)
{

	GammaTablePtr		gammaPtr;
	GammaTablePtr		ourGammaPtr;
	UInt16				i;
	globalsPtr			g;
	UInt16				numBytes;


//	DebugStr("\pDoSetGamma");
	
	g = (globalsPtr) *(dce->dCtlStorage);
	if ( pgPtr->csGTable == nil ) {			// If nil pointer build linear ramp
		if ( g->gGammaPtr == nil ) {		// We couldn't allocate table earlier
			return(controlErr);				// bad error
		}
		
		//========================================================================
		//	Build linear gamma table of gChanCnt channels.
		//========================================================================
		ourGammaPtr = g->gGammaPtr;
		ourGammaPtr->gVersion = 0;				// Always version 0
		ourGammaPtr->gType = 0;
		ourGammaPtr->gFormulaSize = 0;
		ourGammaPtr->gChanCnt = 1;
		ourGammaPtr->gDataCnt = 256;			// Generate a single channel table
		ourGammaPtr->gDataWidth = 0x0008;
		for ( i = 0; i < kNumCLUTEntries; i++ ) {
			ourGammaPtr->gFormulaData[i] = i;
		}
	} else {									// They supplied a table
		gammaPtr = (GammaTablePtr) pgPtr->csGTable;
		if ( gammaPtr->gVersion != 0 ) return(controlErr);
		
		if ( gammaPtr->gType == 0 ) {
		}

		if ( g->gGammaPtr == nil ) return(controlErr);
		
		ourGammaPtr = g->gGammaPtr;
		ourGammaPtr->gVersion = gammaPtr->gVersion;
		ourGammaPtr->gType = gammaPtr->gType;
		ourGammaPtr->gFormulaSize = gammaPtr->gFormulaSize;
		ourGammaPtr->gChanCnt = gammaPtr->gChanCnt;
		ourGammaPtr->gDataCnt = gammaPtr->gDataCnt;
		ourGammaPtr->gDataWidth = gammaPtr->gDataWidth;
		numBytes = gammaPtr->gDataCnt * gammaPtr->gChanCnt;
		for ( i = 0; i < numBytes; i++ ) {
			ourGammaPtr->gFormulaData[i] = gammaPtr->gFormulaData[i];
		}
	}
	if ( g->gDirectMode ) {
		DoProgramDACGamma(ourGammaPtr);
	}

	return(noErr);
	
} /* End of DoSetGamma */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoGrayPage
*Creator:	George D. Wilson Jr.
*Date:		3/30/92
*
*Purpose:	
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
OSErr	DoGrayPage(VDPgInfoPtr pgPtr, DCtlPtr dce)
{

	UInt32			grayPattern;
	UInt16			numLines;
	UInt32			numWrites;
	Ptr				linePtr;
	UInt32			*dumbPtr;
	UInt16			i,j;
	globalsPtr		g;
	UInt16			rowBytes;
	UInt16			depth;
	ColorSpec		tmpCTable[256];

//	DebugStr("\pDoGrayPage");
	
	if ( pgPtr->csPage != kOurVidPage ) {	// If asked to gray some other page error
		return(controlErr);
	}
	
	g = (globalsPtr) *(dce->dCtlStorage);

	depth = GetBitDepth(g->gMonitorID,pgPtr->csMode,g->gSlotNum);
	rowBytes = GetRowBytes(g->gMonitorID,pgPtr->csMode,g->gSlotNum);
	numLines = GetNumLines(g->gMonitorID,pgPtr->csMode,g->gSlotNum);
	numWrites = rowBytes / 4;
//	linePtr = g->gFBBaseAddr;
	linePtr = g->gBaseAddr;

	switch ( depth ) {
		case 1: grayPattern = kOneBitPattern; break;
		case 2: grayPattern = kTwoBitPattern; break;
		case 4: grayPattern = kFourBitPattern; break;
		case 8: grayPattern = kEightBitPattern; break;
		case 16: grayPattern = kSixTeenBitPattern; break;
		case 32: grayPattern = kThirtyTwoBitPattern; break;
	}

	if ( depth == 32 ) {
		for ( i = 0; i < numLines; i++ ) {
			dumbPtr = (UInt32 *) linePtr;
			for ( j = 0; j < numWrites; j++ ) {
				*dumbPtr++ = grayPattern;
				grayPattern = ~grayPattern;
			}
			linePtr += rowBytes;
			grayPattern = ~grayPattern;
		}
	} else {
		for ( i = 0; i < numLines; i++ ) {
			dumbPtr = (UInt32 *) linePtr;
			for ( j = 0; j < numWrites; j++ ) {
				*dumbPtr++ = grayPattern;
			}
			linePtr += rowBytes;
			grayPattern = ~grayPattern;
		}
	}

	if ( g->gDirectMode ) {
		DoBuildLinearRamp(tmpCTable);
		if ( g->gGammaPtr != nil ) {
			DoGammaCorrectCLUT(kNumCLUTEntries,tmpCTable,tmpCTable,g->gGammaPtr);
		}
		DoProgramDAC(tmpCTable,kNumCLUTEntries,0,false);
	}

	return noErr;
	
} /* End of DoGrayPage */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoSetGray
*Creator:	George D. Wilson Jr.
*Date:		3/30/92
*
*Purpose:	
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
*	5/26/92		George W.		Fixed 'C' equals bug.
*
*stop
*-----------------------------------------------------------------------*/
OSErr	DoSetGray(VDGrayPtr pgPtr, DCtlPtr dce)
{

	globalsPtr		g;

//	DebugStr("\pDoSetGray");
	
	// Is this a mono only montor.  Do something different еее
	
	g = (globalsPtr) *(dce->dCtlStorage);
	if ( g->gDirectMode ) {
		g->gLuminanceMode = true;
		return(noErr);
	}
	
	if ( !g->gMonoOnly ) {
		if ( pgPtr->csMode == kMonoDevice ) {
			g->gLuminanceMode = true;
		} else {
			g->gLuminanceMode = false;
		}
	}
	return(noErr);
	
} /* End of DoSetGray */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoSetInterrupt
*Creator:	George D. Wilson Jr.
*Date:		3/30/92
*
*Purpose:	
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
OSErr	DoSetInterrupt(VDPgInfoPtr pgPtr, DCtlPtr dce)
{

	globalsPtr		g;

//	DebugStr("\pDoSetInterrupt");

	g = (globalsPtr) *(dce->dCtlStorage);
	if ( pgPtr->csMode == 0 ) {						// Disable interrupts
		if ( g->gInterruptsEnabled == kVBLInterruptEnabled ) {
//			RemoveInterruptRoutine(dce);
		}
		return(noErr);
	}
	
	if ( pgPtr->csMode == 1 ) {						// Enable interrupts
		if ( g->gInterruptsEnabled == kVBLInterruptDisabled ) {
//			InstallInterruptRoutine(dce);
		}
		return(noErr);
	}
	return(controlErr);
	
	
} /* End of DoSetInterrupt */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoDirectSetEntries
*Creator:	George D. Wilson Jr.
*Date:		3/30/92
*
*Purpose:	
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
OSErr	DoDirectSetEntries(VDSetEntryPtr pgPtr, DCtlPtr dce)
{

	ColorSpecPtr	cpPtr;
	UInt8			*clutData;
	UInt8			*clutAddrReg = 0;
	short			i;
	UInt16			start;
//	UInt8			dummy;
	globalsPtr		g;
	ColorSpec		tmpCTable[256];
	UInt16			numEntries;
unsigned long data;

//	DebugStr("\pDoDirectSetEntries");
	
	IOLongWrite(0xF2800000, (0x2 << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x3;
	PerformPCIHack();

	IOLongWrite(0xF2800000, (0x2 << 12));
	data = LByteSwap(*(unsigned long *)0xf2c00000);					// Get Vendor ID

	g = (globalsPtr) *(dce->dCtlStorage);
	if ( !g->gDirectMode ) return(controlErr);		// Only supported in 16bpp and 32 bpp
	if ( pgPtr->csTable == nil ) return(controlErr);
	
	cpPtr = pgPtr->csTable;
	start = pgPtr->csStart;
	numEntries = pgPtr->csCount + 1;

	if ( g->gGammaPtr != nil ) {					// If we have a gamma table correct things
		DoGammaCorrectCLUT(numEntries,cpPtr,tmpCTable,g->gGammaPtr);
	}

	if ( data == (0x1002 | (0x4158 << 16)) ) {	// look for ATI
		clutAddrReg = (UInt8 *) kDAC_W_INDEX;
		clutData = (UInt8 *) kDAC_DATA;					// Point to data register
	}
	else {
//	if ( data == (0x100E | (0x9001 << 16)) ) {	// look for Diamond
		clutAddrReg = (UInt8 *) 0xF20003C8;
		clutData = (UInt8 *) 0xF20003C9;			// Point to data register
	}
	
	if (!clutAddrReg) {
		IOLongWrite(0xF2800000, (0x2 << 12) | 4);
		*(unsigned char *)(0xF2C00000) = 0x2;
		PerformPCIHack();
	
		return(controlErr);					// Always return err for now еее
	}

	if ( start >= 0 ) {								// Standard fill CLUT
		*clutAddrReg = start;						// Goto the proper clut entry
		PerformPCIHack();
//		dummy = *clutAddrReg;						// HW funnies.
		WaitForVBL();
		for ( i = 0; i < numEntries; i++ ) {
			*clutData = tmpCTable[i].rgb.red;
			PerformPCIHack();
			*clutData = tmpCTable[i].rgb.green;
			PerformPCIHack();
			*clutData = tmpCTable[i].rgb.blue;
			PerformPCIHack();
		}
	}
	
	if ( start == -1 ) {							// Fill specific CLUT entries
		WaitForVBL();
		for ( i = 0; i < numEntries; i++ ) {
			*clutAddrReg = tmpCTable[i].value;		// Point to specific CLUT entry
			PerformPCIHack();
//			dummy = *clutAddrReg;					// HW funnies.
			*clutData = tmpCTable[i].rgb.red;
			PerformPCIHack();
			*clutData = tmpCTable[i].rgb.green;
			PerformPCIHack();
			*clutData = tmpCTable[i].rgb.blue;
			PerformPCIHack();
		}
	}

	IOLongWrite(0xF2800000, (0x2 << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x2;
	PerformPCIHack();

	return(controlErr);					// Always return err for now еее
	
} /* End of DoDirectSetEntries */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoSetDefaultMode
*Creator:	George D. Wilson Jr.
*Date:		3/30/92
*
*Purpose:	
*
*Category:
*File:		ATIDrvrImp.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:
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
OSErr	DoSetDefaultMode(VDDefModePtr dfPtr, DCtlPtr dce)
{
#pragma unused(dce)

	globalsPtr		g;
	SpBlock			spPb;
	OSErr			err;
	SPRAMRecord		sPRAM;

//	DebugStr("\pDoSetDefaultMode");
	
	g = (globalsPtr) *(dce->dCtlStorage);
	spPb.spSlot = g->gSlotNum;
	spPb.spResult = &sPRAM;
	err = SReadPRAMRec(&spPb);
	if ( err == noErr ) {							// Did we get our PRAM?
		sPRAM.vendorUse4 = dfPtr->csID;
		spPb.spsPointer = (Ptr) &sPRAM;				// Heres the PRAM record to save
		err = SPutPRAMRec(&spPb);					// Save it for ever
		return(err);
	}
	
	return(controlErr);

} /* End of DoSetDefaultMode */

/*-------------------------------------------------------------------------
*
*							End of Module
*
*-----------------------------------------------------------------------*/
#if 0
void	DACDisplay(Ptr baseAddr, UInt16 rowBytes, UInt8 depth, UInt16 numLines)
{

	UInt32			grayPattern;
	UInt32			numWrites;
	Ptr				linePtr;
	UInt32			*dumbPtr;
	Ptr				myPtr;
	UInt16			i,j, k, huh, huh1;

//	DebugStr("\pGrayPage");
	
	switch ( depth ) {
		case 1: grayPattern = kOneBitPattern; break;
		case 2: grayPattern = kTwoBitPattern; break;
		case 4: grayPattern = kFourBitPattern; break;
		case 8: grayPattern = kEightBitPattern; break;
		case 16: grayPattern = kSixTeenBitPattern; break;
		case 32: grayPattern = kThirtyTwoBitPattern; break;
	}
	numWrites = rowBytes / 4;
	
	huh = 0;
	for (i = 0; i < numLines; i++) {
		linePtr = (Ptr) baseAddr + (i * rowBytes);
		myPtr = linePtr;
		huh1 = huh;
		for (j = 0; j < 16; j++) {
			for (k = 0; k < 40; k++) {
				*myPtr = huh1;
				myPtr++;
			}
			huh1++;
		}
		if (i % 30 == 0 && i > 0) {
			huh += 16;
		}
	}
} /* End of DACDisplay */

#endif
