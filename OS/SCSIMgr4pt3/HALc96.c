/*********************************************************************************

	File:		HALc96.c

	Contains:	routines that implement the HAL for 53c96 HBAs (Quadras)

	Notes:
		This HAL follows the rules for SCSI HALs.  That means it:
			¥	has 1 Action entry point
			¥	has 1 Bus Inquiry entry point
			
		It also has its own rules:
			¥	has 1 software and 1 hardware init entry point
			¥	these entry points expect a ptr to a CONSTANTs structure that contains addresses
				and characteristics of the HBA that it is responsible for.  This structure is
				called HBADesc_c96.
			¥	the 53c96 registers are offset $10 from one another (i.e. reg2 = $20+base)
				
	Entry points:

	Written by:	Paul Wolf

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SM24>	  2/2/94	DCB		Adding another bit to SCSIWeirdStuff - this time to indicate a
									need for scsiHandshaking.
	  <SM23>	  2/1/94	DCB		Added scsiBusErrorsUnsafe to BusInquiry on emulated pseudo-DMA
									machines.
	  <SM22>	 1/28/94	chp		Make TNT unconditionally oldCallCapable.
	  <SM21>	11/22/93	pdw		Rolling in from <MCxx>.
	  <SM20>	11/22/93	pdw		Added TNT debug flags around setting of oldCallCapable flag.
	  <SM19>	11/19/93	chp		Nothing to worry about. Just removed a commented-out line of TNT
									code.
	  <SMG3>	 9/29/93	chp		Clean up header. Remove unnecessary includes. Add a switch case
									to initialize the Grand Central HBA software.
	  <SMG2>	 9/22/93	chp		Classify the interrupt handler for Grand Central.
	  <SM17>	10/14/93	pdw		Added support for Synchronous data transfers, rewrote State
									Machine, message handling etc.
	  <SM16>	 9/12/93	pdw		Add ReInit (reregister) stuff.
	  <SM15>	  9/9/93	pdw		
	  <SM14>	 7/17/93	pdw		Lots of little things.
	  <SM13>	  7/8/93	pdw		Got rid of an unnecessary local variable somewhere.
	  <SM12>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
									stack switching mechanism.  Adding support for Cold Fusion.
									Rearranging HW/SW Init code. Some code optimizations.
	  <SM11>	 5/25/93	DCB		Rollin from Ludwig. (The next item below)
	   <LW9>	 5/21/93	PW		Fixed BusInquiry (we weren't filling everything in)
	  <SM10>	  5/5/93	PW		Converted names to meanies-friendly names.
	   <LW8>	 4/30/93	DCB		Adding entry point for BusInquiry.
	   <LW6>	 3/26/93	PW		Changed name of busOldAPICapable to scsiBusOldCallCapable. Wow!
	   <LW5>	  3/1/93	DCB		Added slot and srsrc fields to bus inquiry
	   <LW4>	 2/17/93	PW		Began to add dual-interrupt support for Quadras.
	   <SM7>	 1/31/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <LW3>	 1/27/93	PW		Changing busNoExtern to scsiBusInternalExternal.
	   <LW2>	 1/27/93	PW		Changed some fields in BusInquiry including scsiIOFlagsSupported
									and scsiFlagsSupported.
	   <SM6>	 12/5/92	PW		Changed some field names.
	   <SM5>	11/20/92	DCB		Minor changes to the data returned in BusInquiry
	   <SM4>	10/30/92	DCB		Changed to reflect new acam.h
	   <SM3>	 10/8/92	PW		Lots of trivial name changes.
	   <SM2>	 7/28/92	PW		Resolved differences in sources.
	   <SM1>	 7/26/92	PW		Initial check-in.

**********************************************************************************/

#include	<Errors.h>
#include	"SCSIGlue.h"
#include	"XPTpriv.h"
#include	"SIMCorePriv.h"
#include	"HALc96.h"


#define PRIVATE_STACK_SIZE 16*1024

extern	long	HAL_NoISR(HALc96Globals *HALg);
void	HALInitCommon( HBADesc_53c9x *hwDescPtr, HALinitInfo * HALinfoPtr);


/*********************************************************************************
	Init53c9xHW	-	Initialize HBA 
	
		Initialize 53c96
		PSC?
		VIA int?
		
		NOTE:  For now (3/2/92) I will assume that HW was init'd by InitSCSIMgrHW
*********************************************************************************/

#if 0
long
Init53c9xHW(HBADesc_53c9x *hwDesc)
{
	ClearSCSIIRQ(hwDesc);
	EnableSCSIInt();
	return (0);
}
#endif

/*********************************************************************************
	Init53c9xSW	-	Initialize HAL for 53c96 
	
		Register HBA with SIMCore (which will then register with XPT)
*********************************************************************************/

void *	// HALg
Init53c9xSW(HBADesc_53c9x *hwDescPtr)
{
	HALinitInfo		HALinfo;

	HALc96Globals	* HALg;

// Put our values into registration parameter block

	HALInitCommon( hwDescPtr, &HALinfo);
	
	HALinfo.supported_scFlags		= SUPPORTED_scFlags;
	HALinfo.supported_scIOFlags		= SUPPORTED_scIOFlags;
	HALinfo.supported_scDataTypes	= SUPPORTED_scDataTypes;

// Make call then get HALg from pb

	if (SIMRegisterHAL( &HALinfo))
		return (0);

	HALg = (HALc96Globals *)HALinfo.HALstaticPtr;	
	
	return (HALg);
}


/*********************************************************************************
	ReInitHAL	-	Initialize HAL for 53c96 
	
		Reregister HBA with SIMCore (which will then reregister with XPT)
*********************************************************************************/

void *	// HALg
ReInitHAL(HBADesc_53c9x *hwDescPtr, ushort busID)
{
	HALinitInfo		HALinfo;

	HALc96Globals	* HALg;

// Put our values into registration parameter block

	HALInitCommon( hwDescPtr, &HALinfo);

	HALinfo.busID = busID;
	HALinfo.supported_scFlags		= SUPPORTED_scFlags;
	HALinfo.supported_scIOFlags		= SUPPORTED_scIOFlags;
	HALinfo.supported_scDataTypes	= SUPPORTED_scDataTypes;

// Make call then get HALg from pb

	if (SIMReregisterHAL( &HALinfo))
		return (0);

	HALg = (HALc96Globals *)HALinfo.HALstaticPtr;	
	
	return (HALg);
}



/*********************************************************************************
	HALInitCommon 
	
		ReRegister HBA with SIMCore (which will then reregister with XPT)
*********************************************************************************/

void
HALInitCommon( HBADesc_53c9x *hwDescPtr, HALinitInfo * HALinfoPtr)
{

// Set up HALinfo for call to SIMRegisterHAL

	// -> num bytes HAL needs for static vars
	HALinfoPtr->staticSize = SizeOfGlobals();
	HALinfoPtr->HALstaticPtr = 0;
	
	HALinfoPtr->HALinit			= HALinit;			// -> ptr to HAL init routine
	HALinfoPtr->HALaction		= HALaction;		// -> ptr to HAL action routine
	HALinfoPtr->HALBusInquiry	= GetHalInfo;		// -> ptr to BusInquiry routine
	HALinfoPtr->HALIntPoll		= HALIntPoll;		// -> ptr to HAL interrupt polling routine
	HALinfoPtr->HALResetBus		= HALResetBus;		// -> ptr to HAL ResetBus routine
	HALinfoPtr->HALAssertATN	= HALAssertATN;		// -> ptr to HAL AssertATN routine
	HALinfoPtr->HALTeardownIO	= HALTeardownIO;	// -> ptr to HAL TeardownIO routine
	HALinfoPtr->HALSyncConfig	= HALSyncConfig;	// -> ptr to HAL SyncConfig routine
	
	// -> ptr to HAL interrupt service routine
	switch (hwDescPtr->intTypeSCSI) {
	case SHARED_VIA:
		HALinfoPtr->HAL_ISR = HAL_DualISR;	
		break;
	case INDEPENDENT_VIA:
		HALinfoPtr->HAL_ISR = HAL_SingleISR;	
		break;
	case SECOND_SHARED_VIA:
		HALinfoPtr->HAL_ISR = HAL_NoISR;
		break;
	case GRAND_CENTRAL:
		HALinfoPtr->HAL_ISR = HAL_SingleISR;
		break;
	}
	
	// -> true if this HAL can handle old-API calls
	HALinfoPtr->oldCallCapable = true;

// Set up synchronous parameters
	
	HALinfoPtr->HBAisSync = true;
	HALinfoPtr->HBAisFast = hwDescPtr->HBAisFast;	
	
	if (hwDescPtr->usesThreshold8)
		HALinfoPtr->syncRAoffset = 7;
	else
		HALinfoPtr->syncRAoffset = 15;

	if (hwDescPtr->HBAisFast)
		HALinfoPtr->minPeriodFactor = 25;
	else
		HALinfoPtr->minPeriodFactor = 50;


// -- put hwDescPtr in HALinfo so that HALinit can get at it 

	HALinfoPtr->hwDescPtr = hwDescPtr;
}



/*********************************************************************************
	HALinit	-	
*********************************************************************************/

long
HALinit( HALinitInfo * HALinfoPtr)
{
	HALc96Globals	* HALg;
	HBADesc_53c9x	* hwDescPtr;
	Ptr				privateStack;
	OSErr			err;
	
// Get results out of HALinfo and put them in HALglobals

	// get HALg ptr from static ptr allocated by SIM	
	HALg = (HALc96Globals *)(HALinfoPtr->HALstaticPtr);		

	hwDescPtr = HALinfoPtr->hwDescPtr;
	
	// store entire HWDesc into our globals
	HALg->hwDesc	= *hwDescPtr;			
	
	// If DMA is used, call the Init DMA routine
	switch (hwDescPtr->dmaType)
	{
	case dmaTypePSC:
		if (err = InitSW_PSC( HALg))
			return (err);
		break;
		
	case dmaTypeAMIC:
		if (err = InitSW_AMIC( HALg))
			return (err);
		break;
		
	case dmaTypeGC:
		if (err = InitSW_GC( HALg))
			return (err);
		break;
		
	case dmaTypeNone:
		break;
	}
		
	HALg->supported_scFlags		= HALinfoPtr->supported_scFlags;
	HALg->supported_scIOFlags	= HALinfoPtr->supported_scIOFlags;
	HALg->supported_scDataTypes	= HALinfoPtr->supported_scDataTypes;

	// store busID as returned from register
	HALg->busID	= HALinfoPtr->busID;		
	
	// store SIMstaticPtr for use in callbacks to SIMCore
	HALg->SIMstaticPtr	= HALinfoPtr->SIMstaticPtr;
	
	HALg->ReconnectISRptr	= HALinfoPtr->ReconnectISR;
	HALg->XPT_ISRptr		= HALinfoPtr->XPT_ISR;

	// Allocate our private stack
	
	privateStack = NewPtrSysClear( PRIVATE_STACK_SIZE);
	
	if (! privateStack )
		return (memFullErr);

	HALg->privStackTop = privateStack+PRIVATE_STACK_SIZE;
	
	*(--(long *)(HALg->privStackTop)) = 0xDEADFACE;
	
	// initialize Asm stuff
	Initc96Asm( HALg);
			
	return (0);
}


/*********************************************************************************
	HAL_NoISR
*********************************************************************************/

long
HAL_NoISR( HALc96Globals *HALg)
{
#pragma unused(HALg)
	return (0);
}


/*********************************************************************************
	GetHalInfo	-	fill in info parameter block
*********************************************************************************/

long
GetHalInfo( HALc96Globals * HALg, SCSIBusInquiryPB * infoPB )
{	
	ulong HalFeatures;
	

	HalFeatures = scsiBusOldCallCapable;
	
	// if we've got 2 buses and this is bus 0 then it's an Internal only bus.
	
	if (TestFor_SCSI96_2Exists() ) {
		if (HALg->busID == 0)
			HalFeatures |= scsiBusInternal;
		else
			HalFeatures |= scsiBusInternalExternal;
	}
	else
		HalFeatures = scsiBusInternalExternal;
	
	if( HALg->hwDesc.HBAhasDMA )
		HalFeatures |= scsiBusDMAavailable;
		
	if( HALg->hwDesc.HBAisFast && (HALg->supported_scFlags & scsiInitiateSyncData) )
		HalFeatures |= scsiBusFastSCSI;
		
	if( HALg->hwDesc.HBAisDiff )
		HalFeatures |= scsiBusDifferential;
		
	infoPB->scsiFeatureFlags = HalFeatures;
	
	infoPB->scsiFlagsSupported = HALg->supported_scFlags;
	infoPB->scsiIOFlagsSupported = HALg->supported_scIOFlags;

	infoPB->scsiWeirdStuff = scsiTargetDrivenSDTRSafe;
	if ( HALg->hwDesc.usesThreshold8) {
		infoPB->scsiWeirdStuff |= scsiOddDisconnectUnsafeWrite1;
	}
	
	if( HALg->hwDesc.using601Emulator == true && HALg->hwDesc.HBAhasDMA == false ) {
		infoPB->scsiWeirdStuff |= scsiBusErrorsUnsafe;
	}
	
	if(  HALg->hwDesc.HBAhasDMA == false ) {
		infoPB->scsiWeirdStuff |= scsiRequiresHandshake;
	}

	infoPB->scsiMaxTransferType = kMaxTransferType;	
	infoPB->scsiDataTypes = HALg->supported_scDataTypes;

	infoPB->scsiVersionNumber = scsiVERSION;	
	infoPB->scsiHBAInquiry = scsiBusSoftReset + 0;
	infoPB->scsiTargetModeFlags = 0;
	infoPB->scsiScanFlags = 0;	// !!! ?

	infoPB->scsiHBAslotNumber = 0;						// Motherboard Bus
	infoPB->scsiSIMsRsrcID = infoPB->scsiDevice.bus; 	// We don't have an srsrc so we use bus ID

	infoPB->scsiEngineCount = 0;
	infoPB->scsiAsyncFlags = 0;

	infoPB->scsiSIMPrivatesPtr = 0;
	infoPB->scsiSIMPrivatesSize = 0;

	infoPB->scsiMaxTarget = 7;
	infoPB->scsiMaxLUN = 7;
	infoPB->scsiInitiatorID = GetInitiatorID( (HBADesc_53c9x *)HALg);
	
	// If anybody cares about this version stuff then we should put the 
	// version number in a public header somewhere.  Otherwise...
	
	infoPB->scsiSIMversion[0] = 0;
	infoPB->scsiSIMversion[1] = 1;	// version = 1.00
	infoPB->scsiSIMversion[2] = 0;
	infoPB->scsiSIMversion[3] = 0;
	
	infoPB->scsiHBAversion[0] = 0;
	infoPB->scsiHBAversion[1] = 1;	// version = 1.00
	infoPB->scsiHBAversion[2] = 0;
	infoPB->scsiHBAversion[3] = 0;
	
	BlockMove("Apple Computer \0",infoPB->scsiSIMVendor,16);
	BlockMove("Apple Computer \0",infoPB->scsiHBAVendor,16);
	BlockMove("NCR 53c96      \0",infoPB->scsiControllerFamily,16);
	BlockMove("Unknown...     \0",infoPB->scsiControllerType,16);
	
	infoPB->scsiAdditionalLength = 0;
	
	return(0);
}



