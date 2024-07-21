/*
	File:		ATIVideoImp.c

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
*Name:		ATIVideoImp.c
*Creator:	George D. Wilson Jr.
*Date:		6/19/92
*
*Purpose:	Contains ATI specific video routines.
*
*Category:	Video Hardware Implementation
*File:		ATIVideoImp.c
*
*Exports:	DoProgramDAC
*			DoProgramDACGamma
*			DoBuildLinearRamp
*			DoGammaCorrectCLUT
*			DoProgramEndeavor
*			DoProgramACDC
*			DoProgramSwatch
*			DoEnableVideo
*			DoDisableVideo
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
extern Ptr FindVideoTimingStruct(UInt8 monitorID, UInt8 theSlot);
extern Ptr GetTimingSBlock(UInt8 monitorID, UInt8 videoMode, UInt8 timingSelector, UInt8 ourSlot);
extern void PruneMonitors(UInt8 monitorID, UInt8 theSlot);

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
*Name:		DoProgramDAC
*Creator:	George D. Wilson Jr.
*Date:		5/28/92
*
*Purpose:	Sends the specified CLUT to the hardware CLUT.
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
DoProgramDAC(ColorSpecPtr ctPtr, UInt16 numEntries, UInt16 start, Boolean indexMode)
{

	UInt32			i;
	UInt32			*clutReg;
	UInt32			*clutAddrReg;
	UInt32			dummy;

//	DebugStr("\pDoProgramDAC");
	
// bogus code
return;
	clutAddrReg = (UInt32 *) kDACAddrReg;
	clutReg = (UInt32 *) kDACDataReg;					// Point to data register

	if ( indexMode ) {									// Fill specific CLUT entries
		WaitForVBL();
		for ( i = 0; i < numEntries; i++ ) {
			*clutAddrReg = ctPtr[i].value;				// Point to specific CLUT entry
			dummy = *clutAddrReg;						// HW funnies.
			*clutReg = ctPtr[i].rgb.red;
			*clutReg = ctPtr[i].rgb.green;
			*clutReg = ctPtr[i].rgb.blue;
		}
	} else {											// Fill the CLUT sequencially
		*clutAddrReg = start;							// Goto the proper clut entry
		dummy = *clutAddrReg;							// HW funnies.
		WaitForVBL();
		for ( i = 0; i < numEntries; i++ ) {
			*clutReg = ctPtr[i].rgb.red;
			*clutReg = ctPtr[i].rgb.green;
			*clutReg = ctPtr[i].rgb.blue;
		}
	}
} /* End of DoProgramDAC */


/*-------------------------------------------------------------------------
*start
*
*Name:		DoProgramDACGamma
*Creator:	George D. Wilson Jr.
*Date:		5/28/92
*
*Purpose:	Programs the specified gamma table into the CLUT DAC.
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
DoProgramDACGamma(GammaTablePtr gammaPtr)
{

	char			*redGammaPtr;
	UInt32			i;
	UInt32			*clutReg;
	UInt32			*clutAddrReg;
	UInt32			dummy;
	UInt16			numEntries;

//	DebugStr("\pDoProgramDACGamma");

// bogus
return;

	clutAddrReg = (UInt32 *) kDACAddrReg;
	clutReg = (UInt32 *) kDACDataReg;					// Point to data register
 	*clutAddrReg = 0;									// Point to first CLUT entry
	dummy = *clutAddrReg;								// HW funnies.

	redGammaPtr = gammaPtr->gFormulaData;
	redGammaPtr += gammaPtr->gFormulaSize;
	numEntries = gammaPtr->gDataCnt;

	WaitForVBL();
	for ( i = 0; i < numEntries; i++ ) {
		*clutReg = redGammaPtr[i];
		*clutReg = redGammaPtr[i];
		*clutReg = redGammaPtr[i];
	}
	
} /* End of DoProgramDACGamma */


/*-------------------------------------------------------------------------
*start
*
*Name:		DoBuildLinearRamp
*Creator:	George D. Wilson Jr.
*Date:		5/28/92
*
*Purpose:	Sets the specified color spec array to a linear ramp.
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
DoBuildLinearRamp (ColorSpecPtr ctPtr)
{

	UInt16			i;

//	DebugStr("\pDoBuildLinearRamp");
	
	for ( i = 0; i < kNumCLUTEntries; i++ ) {
		ctPtr[i].value = i;
		ctPtr[i].rgb.red = ctPtr[i].rgb.green = ctPtr[i].rgb.blue = i << 8;
	}
	
} /* End of DoBuildLinearRamp */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoGammaCorrectCLUT
*Creator:	George D. Wilson Jr.
*Date:		5/27/92
*
*Purpose:	Applies the specified gamma table to the CLUT passed.
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
DoGammaCorrectCLUT(UInt16 numEntries, ColorSpecPtr orgCLUTPtr,
					ColorSpecPtr corrCLUTPtr,GammaTablePtr gammaPtr)
{

	char			*redGammaPtr;
	char			*greenGammaPtr;
	char			*blueGammaPtr;
	UInt16			red,green,blue;
	UInt16			i;

//	DebugStr("\pDoGammaCorrectCLUT");
	
	for ( i = 0; i < numEntries; i++ ) {			// Copy all the needed entries
		corrCLUTPtr[i].value = orgCLUTPtr[i].value;
		corrCLUTPtr[i].rgb.red = orgCLUTPtr[i].rgb.red;
		corrCLUTPtr[i].rgb.green = orgCLUTPtr[i].rgb.green;
		corrCLUTPtr[i].rgb.blue = orgCLUTPtr[i].rgb.blue;
	}
	redGammaPtr = gammaPtr->gFormulaData;
	redGammaPtr += gammaPtr->gFormulaSize;
	if ( gammaPtr->gChanCnt == 1 ) {				// If single channel gamma table
		greenGammaPtr = redGammaPtr;				// Point all other channels to red
		blueGammaPtr = redGammaPtr;
	}
	if ( gammaPtr->gChanCnt == 3 ) {				// If triple channel gamma table
		greenGammaPtr = redGammaPtr + gammaPtr->gDataCnt;
		blueGammaPtr = greenGammaPtr + gammaPtr->gDataCnt;
	}
	for ( i = 0; i < numEntries; i++ ) {			// Gamma correct each entry
		red = corrCLUTPtr[i].rgb.red;
		red >>= 8;									// Rotate high order bits down
		if ( corrCLUTPtr[i].rgb.red & 0x0080 ) {	// If low order high bit was set
			if ( red != 0x00FF ) red += 1;			// If we won't overflow add one
		}
		green = corrCLUTPtr[i].rgb.green;
		green >>= 8;								// Rotate high order bits down
		if ( corrCLUTPtr[i].rgb.green & 0x0080 ) {	// If low order high bit was set
			if ( green != 0x00FF ) green += 1;		// If we won't overflow add one
		}
		blue = corrCLUTPtr[i].rgb.blue;
		blue >>= 8;									// Rotate high order bits down
		if ( corrCLUTPtr[i].rgb.blue & 0x0080 ) {	// If low order high bit was set
			if ( blue != 0x00FF ) blue += 1;		// If we won't overflow add one
		}
		corrCLUTPtr[i].rgb.red = redGammaPtr[red];
		corrCLUTPtr[i].rgb.green = greenGammaPtr[green];
		corrCLUTPtr[i].rgb.blue = blueGammaPtr[blue];
	}
	
} /* End of DoGammaCorrectCLUT */

//===========================================================================
//	Hardware specific routines.
//===========================================================================


/*-------------------------------------------------------------------------
*start
*
*Name:		DoProgramTiming
*Creator:	George D. Wilson Jr.
*Date:		4/16/92
*
*Purpose:	Programs the Arial and MMIC hardware for the ATI video system.
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
void DoProgramTiming (UInt32 slotNum, Ptr baseAddr, UInt8 monitorID, 
						UInt8 videoMode, UInt8 ourSlot, UInt16 rowBytes,
						Boolean enableInterrupts)
{
#pragma unused (baseAddr, ourSlot, rowBytes, enableInterrupts)

	UInt8			*DACRegPtr;
	UInt8			*MMICRegPtr;
	UInt8			DACValue;
	UInt8			MMICValue;

//	DebugStr("\pDoProgramTiming");
// bogus
return;

	DACRegPtr = (UInt8 *) (slotNum | kArielBaseAddr);
	MMICRegPtr = (UInt8 *) (slotNum | kMMICBaseAddr);
	
	switch ( videoMode ) {
		case kFirstVideoMode: DACValue = kArial1BPPCode; break;
		case kSecondVideoMode: DACValue = kArial2BPPCode; break;
		case kThirdVideoMode: DACValue = kArial4BPPCode; break;
		case kFourthVideoMode: DACValue = kArial8BPPCode; break;
		case kFifthVideoMode: DACValue = kArial16BPPCode; break;
	}
	
	switch ( monitorID ) {
		case kRGB1312Connected: MMICValue = kMMIC13Code; break;
		case kRGB16Connected: MMICValue = kMMIC16Code; break;
		case kRGB15Connected: MMICValue = kMMIC15Code; break;
		case kRGB12Connected: MMICValue = kMMIC12Code; break;
	}

	*DACRegPtr = DACValue;
	*MMICRegPtr = MMICValue;

} /* End of DoProgramTiming */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoEnableVideo
*Creator:	George D. Wilson Jr.
*Date:		4/17/92
*
*Purpose:	Turns the video curcuitry on for ATI hardware.
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
void DoEnableVideo(UInt32 theSlot)
{
	UInt32		*SashaRegPtr;
	
//	DebugStr("\pDoEnableVideo");

// bogus
return;

	SashaRegPtr = (UInt32 *) (theSlot | kSashaBase);
	
	*SashaRegPtr = (kOutputCtl | kPixelDataOutEn |
					kAcDcCSYNCEnable | kAcDcCBLANKEnable |
					kAcDcSYNCEnable | kAcDcLoadClkEnable);
							
	*SashaRegPtr = (kSwatchSoftReset | kNormal);
							
	*SashaRegPtr = (kVidPipeReset | kNormal);

} /* End of DoEnableVideo */

/*-------------------------------------------------------------------------
*start
*
*Name:		DoDisableVideo
*Creator:	George D. Wilson Jr.
*Date:		4/17/92
*
*Purpose:	Turns the video curcuitry off for ATI hardware.
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
void DoDisableVideo(UInt32 theSlot)
{
	UInt32		*SashaRegPtr;
	
//	DebugStr("\pDoDisableVideo");
	
// bogus
return;

	SashaRegPtr = (UInt32 *) (theSlot | kSashaBase);
	
	*SashaRegPtr = (kOutputCtl |
					kAcDcCSYNCDisable | kAcDcCBLANKDisable |
					kAcDcSYNCDisable | kAcDcLoadClkDisable);
							
	*SashaRegPtr = (kSwatchSoftReset | kNormal);
							
	*SashaRegPtr = (kVidPipeReset | kNormal);

} /* End of DoDisableVideo */

/*-------------------------------------------------------------------------
*
*							End of Module
*
*-----------------------------------------------------------------------*/
