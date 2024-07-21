/*
	File:		ATIPrimaryInit.c

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
*Name:		PrimaryInit.c
*Creator:	George D. Wilson Jr.
*Date:		4/23/92
*
*Purpose:	Main interface file for ATI video driver primary init.
*
*Category:	Macintosh driver
*File:		PrimaryInit.c
*
*Exports:	main	-	Main entry point for primary init.
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

#include		"ATIStdTypes.h"
#include		"ATI.h"
#include		"ATIDrvr.h"
#include		"ATIVideo.h"

/*-------------------------------------------------------------------------
*
*							Imported Procedures
*
*-----------------------------------------------------------------------*/
extern void PruneMonitors(UInt16 cardType, UInt8 theSlot);
extern UInt16 GetRowBytes(UInt8 monitorID,  UInt8 videoMode, UInt8 theSlot);
extern UInt16 GetNumLines(UInt8 monitorID,  UInt8 videoMode, UInt8 theSlot);

extern void DoProgramTiming(UInt32 slotNum, Ptr baseAddr, UInt8 monitorID, 
							UInt8 videoMode, UInt8 ourSlot, UInt16 rowBytes,
							Boolean enableInterrupts);
extern void DoEnableVideo(UInt32 theSlot);

/*-------------------------------------------------------------------------
*start
*
*Name:		SenseLineCheck
*Creator:	George D. Wilson Jr.
*Date:		5/21/92
*
*Purpose:	Returns the currently connected monitor code.
*
*Category:
*File:		PrimaryInit.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:		UInt8	-	Returns the sRsrc id of the monitor family connected.
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
*	9/28/93		George W.		Added default return of 13" display.
*
*stop
*-----------------------------------------------------------------------*/
UInt8
SenseLineCheck(UInt32 theSlot)
{

	UInt32		*SenseRegPtr;
	UInt32		senseLineVal1,senseLineVal2,senseLineVal3;

//	DebugStr("\pSenseLineCheck");


	return(kRGB1312Connected);							// еее ATI hack
	
	SenseRegPtr = (UInt32 *) (theSlot | kATISenseLineBase);
	senseLineVal1 = *SenseRegPtr;						// Read the sense lines
	senseLineVal1 &= kSenseLineMask;					// Mask off the sense line bits
	senseLineVal1 >= kSenseLineShift;
	switch ( senseLineVal1 ) {
		case kMonitorNotConnected:
			*SenseRegPtr = (kSenseLineAMask);					// Set all lines to ones
//			*SenseRegPtr = (kSenseLinesReg);					// Causes sense lines to be read
			senseLineVal1 = *SenseRegPtr;						// Read the sense lines
			senseLineVal1 &= kSenseLineMask;					// Mask off the sense line bits
			senseLineVal1 >= kSenseLineShift;					// Move bits to bottom
			
			*SenseRegPtr = (kSenseLineBMask);					// Set all lines to ones
//			*SenseRegPtr = (kSenseLinesReg);					// Causes sense lines to be read
			senseLineVal2 = *SenseRegPtr;						// Read the sense lines
			senseLineVal2 &= kSenseLineMask;					// Mask off the sense line bits
			senseLineVal2 >= kSenseLineShift;					// Move bits to bottom
			
			*SenseRegPtr = (kSenseLineCMask);					// Set all lines to ones
//			*SenseRegPtr = (kSenseLinesReg);					// Causes sense lines to be read
			senseLineVal3 = *SenseRegPtr;						// Read the sense lines
			senseLineVal3 &= kSenseLineMask;					// Mask off the sense line bits
			senseLineVal3 >= kSenseLineShift;					// Move bits to bottom

			if ( (senseLineVal1 == kSenseLineAMask) &&
				 (senseLineVal2 == kSenseLineBMask) &&
				 (senseLineVal3 == kSenseLineCMask) ) {
				return(kMonitorNotConnected);
			}

			if ( (senseLineVal1 == k16SenseACode) &&
				 (senseLineVal2 == k16SenseBCode) &&
				 (senseLineVal3 == k16SenseCCode) ) {
				return(kRGB16Connected);
			}
			return(kMonitorNotConnected);
			break;
		case kRGB1312:
			return(kRGB1312Connected);
			break;
		default: return(kMonitorNotConnected);
	}
	
} /* End of SenseLineCheck */


void RampCLUT (UInt8 devID, UInt16 cardType)
{
	UInt32			i;
	UInt8			*clutAddrReg;
	UInt8			*clutData;
//	UInt32			dummy;

//	DebugStr("\pRampClut");

	IOLongWrite(0xF2800000, (devID << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x3;
	PerformPCIHack();

	if (cardType == kATIVendorID) {

		clutAddrReg = (UInt8 *) kDAC_W_INDEX;
		clutData = (UInt8 *) kDAC_DATA;					// Point to data register
		*clutAddrReg = 0;								// Point to the first entry
		PerformPCIHack();
		for ( i = 0; i < 256; i++ ) {
			*clutData = kGrayCLUTValue;
			PerformPCIHack();
			*clutData = kGrayCLUTValue;
			PerformPCIHack();
			*clutData = kGrayCLUTValue;
			PerformPCIHack();
		}
	}

	if (cardType == kDiamondVendorID) {
		unsigned char	*writeReg;
		unsigned char	*dataReg;

		writeReg = (unsigned char *)(0xF20003C8);	// kRamWrite
		dataReg = (unsigned char *)(0xF20003C9);	// kPaletteData

		*writeReg = 0;
		PerformPCIHack();
		for (i = 0; i < 256; i++) {
			*dataReg = (unsigned char)i;	// red
			PerformPCIHack();
			*dataReg = (unsigned char)i;	// green
			PerformPCIHack();
			*dataReg = (unsigned char)i;	// blue
			PerformPCIHack();
		}
	}

	IOLongWrite(0xF2800000, (devID << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x2;
	PerformPCIHack();
} /* End of RampClut */

/*-------------------------------------------------------------------------
*start
*
*Name:		GrayPage
*Creator:	George D. Wilson Jr.
*Date:		3/30/92
*
*Purpose:	
*
*Category:
*File:		PrimaryInit.c
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
OSErr	GrayPage(Ptr baseAddr, UInt16 rowBytes, UInt8 depth, UInt16 numLines)
{

	UInt32			grayPattern;
	UInt32			numWrites;
	Ptr				linePtr;
	UInt32			*dumbPtr;
	UInt16			i,j;
#if 0
	Ptr				myPtr;
	UInt16			k, huh, huh1;
#endif

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
	
	linePtr = (Ptr) baseAddr;
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

// code to dump the DACs into the frame buffer.
// 16x16 rectangles each with a different pixel value.
#if 0
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
#endif

	return(noErr);

} /* End of GrayPage */


void CalcSlotBaseAddr (UInt8 slot, UInt32 *baseAddr32, UInt32 *baseAddrFB32)
{

	UInt8	slotNum;
	
	slotNum = slot;
	*baseAddr32 = ((UInt32) (0x0F0 | slotNum) << 24);
	*baseAddrFB32 = (UInt32) ((0x0F00 | (slotNum << 4) | slotNum) << 20);

}

/*-------------------------------------------------------------------------
*start
*
*Name:		REALMAIN
*Creator:	George D. Wilson Jr.
*Date:		5/21/92
*
*Purpose:	Main entry point for the ATI primary init.
*
*Category:	Entry Point
*File:		PrimaryInit.c
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
*Note:
*
*History:
*
*	  Date		Programmer					Modification
*	--------	----------		-----------------------------------------
*	5/21/92		George W.		Added sense line logic.
*
*stop
*-----------------------------------------------------------------------*/
void REALMAIN (SEBlock		*aSEBlockPtr)
{

	Ptr				baseAddr=0;
	Ptr				baseAddrFB;
	UInt16			rowBytes;
	UInt32			slotNum;
	UInt8			slot;
	UInt8			mmuMode;
	UInt8			theMonitorID;
	SpBlock			spPb;
	OSErr			err;
	SPRAMRecord		sPRAM;
	UInt8			videoMode=0;
	UInt16			numLines;
	UInt16			depth;
	UInt16			cardType;
	
	mmuMode = true32b;
	SwapMMUMode(&mmuMode);
	slot = aSEBlockPtr->seSlot;						// Get out slot number
	slotNum = kMySuperSlot;

#if 0
	PruneMonitors(theMonitorID,slot);
	if ( (theMonitorID < kRGB1312Connected) ||
		 (theMonitorID > kRGB16Connected) ) {		// We only support 13"
		aSEBlockPtr->seStatus = -1;
		return;										// All done get out
	}
	
//	CalcSlotBaseAddr(slot,&baseAddr,&baseAddrFB);
	baseAddr = (Ptr) (kBaseAddress | kMySuperSlot);
	baseAddrFB = (Ptr) (kBaseAddress | kMySlot | 0xF0000000);
	
	videoMode = kFirstVideoMode;

	spPb.spSlot = slot;
	spPb.spResult = &sPRAM;
	err = SReadPRAMRec(&spPb);
	if ( err == noErr ) {								// Did we get our PRAM?
		if ( sPRAM.vendorUse4 != theMonitorID ) {		// Is this the same monitor as last time?
			sPRAM.vendorUse4 = theMonitorID;			// No save the monitor ID
			spPb.spsPointer = (Ptr) &sPRAM;				// Heres the PRAM record to save
			err = SPutPRAMRec(&spPb);					// Save it for ever
		} else {										// Yes
			if ( (sPRAM.vendorUse1 >= kFirstVideoMode) ||	// Range check mode value
				(sPRAM.vendorUse1 >= kFifthVideoMode) ) {
				videoMode = sPRAM.vendorUse1;			// If mode value is funny save default.
			}
		}
	}
	rowBytes = GetRowBytes(theMonitorID,videoMode,slot);
	numLines = GetNumLines(theMonitorID,videoMode,slot);
	DoProgramTiming(kMySuperSlot,(Ptr) kBaseAddress,
					theMonitorID,videoMode,slot, rowBytes,false);
	depth = GetBitDepth(theMonitorID,videoMode,slot);
	GrayPage(baseAddrFB,rowBytes,8,numLines);
 	RampCLUT();
	DoEnableVideo(slotNum);
	
#else

	//====================================================
	// New funky code for ATI card
	//====================================================
	
	slot = FindPCICard(&cardType);							// Search some slots for ATI
	if ( slot == 0x00 ) {
		aSEBlockPtr->seStatus = -1;
		return;										// All done get out
	}
	err = EnableIOAccess(slot, true, cardType);
	if ( err != noErr ) {
		aSEBlockPtr->seStatus = -1;
		return;										// All done get out
	}

{
	OSErr			err;
	SpBlock			spPb;
	char			*p;
	short			i;

	p = (char *) &spPb;
	for ( i = 0; i < sizeof(SpBlock); i++ ) *p++ = 0;
	
	spPb.spSlot = 0x00;	
	
	if ( cardType == kATIVendorID) {		// look for ATI
		spPb.spID = 0x90;					// id of board sRsrc to delete
	}

	if ( cardType == kDiamondVendorID) {	// look for Diamond
		spPb.spID = 0x80;					// The id of the board sRsrc
	}

	err = SDeleteSRTRec(&spPb);
}

	theMonitorID = SenseLineCheck(slotNum);
	if ( theMonitorID == kNoMonitorConnected ) {	// No monitor
		aSEBlockPtr->seStatus = -1;
		return;										// All done get out
	}

	videoMode = kFirstVideoMode;

	spPb.spSlot = slot;
	spPb.spResult = &sPRAM;
#if 0
	err = SReadPRAMRec(&spPb);
	if ( err == noErr ) {								// Did we get our PRAM?
		if ( sPRAM.vendorUse4 != theMonitorID ) {		// Is this the same monitor as last time?
			sPRAM.vendorUse4 = theMonitorID;			// No save the monitor ID
			spPb.spsPointer = (Ptr) &sPRAM;				// Heres the PRAM record to save
			err = SPutPRAMRec(&spPb);					// Save it for ever
		} else {										// Yes
			if ( (sPRAM.vendorUse1 >= kFirstVideoMode) ||	// Range check mode value
				(sPRAM.vendorUse1 >= kFifthVideoMode) ) {
				videoMode = sPRAM.vendorUse1;			// If mode value is funny save default.
			}
		}
	}
#endif
	if (cardType == kATIVendorID) {
		UInt32			data;
		UInt16			*ioReg;

		ioReg = (UInt16 *) kMEM_CFG;					// Memory config IO register
		data = WByteSwap(*ioReg);						// Get existing data
		data |= (kATIVRAMAddr >> 16) | k4MegAperture;	// Set the VRAM base address
		data &= 0x0000FFFF;
		*ioReg = WByteSwap(data);						// Write new stuff
		PerformPCIHack();

		ioReg = (UInt16 *) kLOCAL_CNTL;					//
		*ioReg = WByteSwap(0x00A2);						// Write new stuff
		PerformPCIHack();
		
		baseAddr = (Ptr) kATIVRAMAddr;					// should equal kDiamondFBBase
		baseAddrFB = (Ptr) kATIVRAMAddr;
		depth = 8;										// Default for now is 8bpp
		rowBytes = 1024;
		numLines = 480;

		GrayPage(baseAddrFB,rowBytes,depth,numLines);
		RampCLUT(slot,kATIVendorID);
		SlamRegisters(slot);
	}
	else {
		baseAddr = (Ptr) kDiamondFBBase;				// should equal kATIVRAMAddr
		baseAddrFB = (Ptr) kDiamondFBBase;
		depth = 8;										// Default for now is 8bpp
		rowBytes = 640;
		numLines = 480;

		GoDiamond640x480x8Apple(slot);
		GrayPage(baseAddrFB,rowBytes,depth,numLines);
	}

#endif

	aSEBlockPtr->seStatus = noErr;
	SwapMMUMode(&mmuMode);
	
}

