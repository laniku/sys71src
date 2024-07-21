/*
	File:		ATIDrvr.c

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
*Name:		ATIDriver.c
*Creator:	George D. Wilson Jr.
*Date:		8/15/93
*
*Purpose:	Main interface file for ATI video driver.
*
*Category:	Macintosh driver
*File:		ATIDrvr.c
*
*Exports:	OpenDRVR	-	Handles initialization of driver.
*			CloseDRVR	-	Handles shutdown of driver.
*			ControlDRVR	-	Handles driver control calls.
*			StatusDRVR	-	Handles driver status calls.
*			WaitForVBL	-	Returns when vertical blanking is active.
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
#include		<Retrace.h>

#include		"ATIStdTypes.h"
#include		"ATI.h"
#include		"ATIDrvr.h"
#include		"ATIVideo.h"

#include		"NubEqu.h"

/*-------------------------------------------------------------------------
*
*							Imported Procedures
*
*-----------------------------------------------------------------------*/
extern UInt16 GetRowBytes(UInt8 monitorID,  UInt8 videoMode, UInt8 theSlot);

extern void IntHandlerNuBus();

/*-------------------------------------------------------------------------
*
*							Exported Procedures
*
*-----------------------------------------------------------------------*/
UInt16 OpenDRVR (CntrlParam *pb, AuxDCEPtr dce);
UInt16 CloseDRVR (CntrlParam *pb, DCtlPtr dce);
UInt16 ControlDRVR (CntrlParam *pb, DCtlPtr dce);
UInt16 StatusDRVR (CntrlParam *pb, DCtlPtr dce);

/*-------------------------------------------------------------------------
*
*					Beginning of Procedure Definitions
*
*-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
*start
*
*Name:		WaitForVBL
*Creator:	George D. Wilson Jr.
*Date:		3/20/92
*
*Purpose:
*
*Category:
*File:
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
void	WaitForVBL()
{
	short i=0;
	
	i = i+1;
//	DebugStr("\pWaitForVBL");
	
	
} /* End of WaitForVBL */

/*-------------------------------------------------------------------------
*start
*
*Name:		InstallInterruptRoutine
*Creator:	George D. Wilson Jr.
*Date:		3/20/92
*
*Purpose:
*
*Category:
*File:
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
void InstallInterruptRoutine(DCtlPtr dce)
{

//	OSErr			err;
	globalsPtr		g;
//	UInt32			intHi;

//	DebugStr("\pInstallInterruptRoutine");

	g = (globalsPtr) *(dce->dCtlStorage);

//	RegisterNubInt(kVideoLineInt,(InterruptHdlr) IntHandlerNuBus,(long) dce);

	g->gInterruptsEnabled = kVBLInterruptEnabled;
	
} /* End of InstallInterruptRoutine */


/*-------------------------------------------------------------------------
*start
*
*Name:		RemoveInterruptRoutine
*Creator:	George D. Wilson Jr.
*Date:		3/20/92
*
*Purpose:
*
*Category:
*File:
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
void RemoveInterruptRoutine(DCtlPtr dce)
{

//	OSErr			err;
	globalsPtr		g;

//	DebugStr("\pRemoveInterruptRoutine");

	g = (globalsPtr) *(dce->dCtlStorage);
	if ( g->gInterruptsEnabled ) {
		WaitForVBL();
		if ( *(long*)(kMySlot | kNMRQDisable) );
//		RemoveNubInt(kVideoLineInt);
		g->gInterruptsEnabled = kVBLInterruptDisabled;
	}

}

/*-------------------------------------------------------------------------
*start
*
*Name:		OpenDRVR
*Creator:	George D. Wilson Jr.
*Date:		3/20/92
*
*Purpose:
*
*Category:
*File:
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
UInt16 OpenDRVR (CntrlParam *pb, AuxDCEPtr dce)
{

#pragma	unused(pb)

	globalsPtr		g;
	Handle			globs;
	UInt16			i;
	SpBlock			spPb;
//	OSErr			err;
	SPRAMRecord		sPRAM;
	UInt8			videoMode;

//	DebugStr("\pOpenDRVR");
	
	globs = nil;
	ResrvMem(GLOBALSSIZE);
	globs = NewHandleSysClear(GLOBALSSIZE);
	if ( globs == nil ) return(openErr);
	
	dce->dCtlStorage = globs;
	HLock(globs);
	g = (globalsPtr) *(globs);

	//==========================================================================
	// Zero all global data stuff
	//==========================================================================
	g->gGammaPtr = nil;
	g->gCurrentPage = kOurVidPage;
	g->gCurrentMode = kFirstVideoMode;			// 8 bpp Fix this later еее
	g->gBaseAddr = (Ptr) (kATIVRAMAddr);
	g->gFBBaseAddr = (Ptr) (kATIVRAMAddr);
	g->gInterruptsEnabled = kVBLInterruptEnabled;
	g->gMonoOnly = false;						// Device supports color еее
	g->gLuminanceMode = false;					// Current mode is color еее
	g->gDirectMode = false;
	g->gNumLines = kNumLines480;					// 13" is 480 еее
	g->gBigSlotNum = dce->dCtlSlot;				
	g->gSlotNum = dce->dCtlSlot;
	
	videoMode = kFirstVideoMode;

	spPb.spSlot = g->gSlotNum;
	spPb.spResult = &sPRAM;
#if 0
	err = SReadPRAMRec(&spPb);
	if ( err == noErr ) {							// Did we get our PRAM?
		g->gMonitorID = sPRAM.vendorUse4;			// No save the monitor ID
		g->gCurrentMode = sPRAM.vendorUse1;			// Use the first video mode
		if ( g->gCurrentMode > kFirstVideoMode ) {
			g->gDirectMode = true;
		}
	}
#else
	g->gDirectMode = false;
	g->gMonitorID = kRGB1312;						// No save the monitor ID
	g->gCurrentMode = kFirstVideoMode;
#endif
	g->gRowBytes = GetRowBytes(g->gMonitorID,g->gCurrentMode,g->gSlotNum);

	//==========================================================================
	// Get or build gamma table
	//==========================================================================
	g->gGammaPtr = (GammaTablePtr) NewPtrSysClear(sizeof(GammaTable));
	if ( g->gGammaPtr ) {
		g->gGammaPtr->gFormulaSize = 0; 
		g->gGammaPtr->gChanCnt = 1;
		g->gGammaPtr->gDataCnt = 3;
		g->gGammaPtr->gDataCnt = 256;
		g->gGammaPtr->gDataWidth = 0x0008;
		for ( i = 0; i < kNumCLUTEntries; i++ ) {
			g->gGammaPtr->gFormulaData[i] = i;
		}
	}
#ifndef ROM
//	InitNubInts();
//	InitNubIntMgr();
#endif
//	InstallInterruptRoutine(dce);

#ifdef ROM
//	err = AttachVBL(0x0E);
#endif

	return(noErr);							// Say open was successful
	
}

/*-------------------------------------------------------------------------
*start
*
*Name:		CloseDRVR
*Creator:	George D. Wilson Jr.
*Date:		3/20/92
*
*Purpose:
*
*Category:
*File:
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
UInt16 CloseDRVR (CntrlParam *pb, DCtlPtr dce)
{
#pragma	unused(pb)
	globalsPtr		g;
	UInt8			mmuMode;

//	DebugStr("\pCloseDRVR");

	g = (globalsPtr) *(dce->dCtlStorage);
	mmuMode = true32b;
	SwapMMUMode(&mmuMode);
	DoDisableVideo(g->gBigSlotNum);			// Turn the video system off
	if ( g->gGammaPtr ) {					// If we have a gamma table
		DisposPtr((Ptr) (g->gGammaPtr));	// Release the memory
	}

	if ( g->gInterruptsEnabled ) {			// If cursor interrupts are enabled
//		RemoveInterruptRoutine(dce);		// Disable them
	}
	
	SwapMMUMode(&mmuMode);
	DisposHandle(dce->dCtlStorage);			// Release driver globals storage
	return(noErr);							// Say open was successful

}

/*-------------------------------------------------------------------------
*start
*
*Name:		ControlDRVR
*Creator:	George D. Wilson Jr.
*Date:		3/20/92
*
*Purpose:
*
*Category:
*File:
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
UInt16 ControlDRVR (CntrlParam *pb, DCtlPtr dce)
{
	Int16			message;				// The control call being made
	OSErr			err;
	globalsPtr		g;
	UInt8			mmuMode;
	
//	DebugStr("\pControlDRVR");

	g = (globalsPtr) *(dce->dCtlStorage);
	mmuMode = true32b;
	SwapMMUMode(&mmuMode);
	message = pb->csCode;
	
	switch ( message )  {
	   	case cscReset:
			err = DoVideoReset((VDPgInfoPtr)  *((UInt32 *) &(pb->csParam[0])), dce);
			break;
//	   	case cscKillIO:
//			err = DoKillIO((VDPgInfoPtr) *((UInt32 *) &(pb->csParam[0])), dce);
//			break;
	   	case cscSetMode:
			err = DoSetVideoMode((VDPgInfoPtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;
	   	case cscSetEntries:
			err = DoSetEntries((VDSetEntryPtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;
	   	case cscSetGamma:
			err = DoSetGamma((VDGamRecPtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;
	   	case cscGrayScreen:
			err = DoGrayPage((VDPgInfoPtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;
	   	case cscSetGray:
			err = DoSetGray((VDGrayPtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;
	   	case cscSetInterrupt:
			err = DoSetInterrupt((VDPgInfoPtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;
	   	case cscDirectSetEntries:
			err = DoDirectSetEntries((VDSetEntryPtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;
	   	case cscSetDefaultMode:
			err = DoSetDefaultMode((VDDefModePtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;		
		case 200:
			err = noErr;
			break;
		default: err = controlErr;
	
	} // End switch
	pb->ioResult = err;
	SwapMMUMode(&mmuMode);
	return(err);
}

/*-------------------------------------------------------------------------
*start
*
*Name:		StatusDRVR
*Creator:	George D. Wilson Jr.
*Date:		3/20/92
*
*Purpose:
*
*Category:
*File:
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
UInt16 StatusDRVR (CntrlParam *pb, DCtlPtr dce)
{

	Int16			message;				// The control call being made
	OSErr			err;					// Error code returned from routine
	globalsPtr		g;
	UInt8			mmuMode;
	
//	DebugStr("\pStatusDRVR");

	g = (globalsPtr) *(dce->dCtlStorage);
	mmuMode = true32b;
	SwapMMUMode(&mmuMode);
	message = pb->csCode;
	err = statusErr;									// Standard error code
	
	switch ( message )  {
	   	case cscGetMode:
			err = DoGetMode((VDPgInfoPtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;
	   	case cscGetEntries:
			err = DoGetEntries((VDSetEntryPtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;
	   	case cscGetPageCnt:
			err = DoGetPages((VDPgInfoPtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;
		case cscGetBaseAddr:
			err = DoGetBaseAddr((VDPgInfoPtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;
	   	case cscGetGray:
			err = DoGetGray((VDGrayPtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;
	   	case cscGetInterrupt:
			err = DoGetInterrupt((VDPgInfoPtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;
	   	case cscGetGamma:
			err = DoGetGamma((VDGamRecPtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;
	   	case cscGetDefaultMode:
			err = DoGetDefaultMode((VDDefModePtr) *((UInt32 *) &(pb->csParam[0])), dce);
			break;		
	} // End switch
	pb->ioResult = err;									// Pass result code on
	SwapMMUMode(&mmuMode);
	return(err);

}

/*-------------------------------------------------------------------------
*
*							End of Module
*
*-----------------------------------------------------------------------*/
