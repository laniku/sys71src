/*
	File:		HALc96PSC.c

	Contains:	routines that implement the PSC portion of the HAL

	Notes:
				
	Entry points:

	Written by:	Paul Wolf

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SM16>	11/10/93	chp		Fix some outdated and misleading comments warning of doom should
									certain parameters change.
	  <SM15>	10/14/93	pdw		<MC> roll-in.
	   <MC2>	 9/13/93	pdw		Roll-in from SuperMario.
	  <SM14>	 9/13/93	pdw		Changed the risky slash pattern.
	  <SM13>	  9/9/93	pdw		Lots of little changes.  Name changes, temporary cache_bug
									stuff.
	  <SM12>	 7/17/93	pdw		Made it PSC-specific (created HALc96AMIC.c also).
	  <SM11>	  7/8/93	pdw		Replaced ifdef with if to test for GPHYSICAL.
	  <SM10>	 6/29/93	pdw		Fixed up that little "optimization" that slowed things down
									immensely.
	   <SM9>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
									stack switching mechanism.  Adding support for Cold Fusion.
									Rearranging HW/SW Init code. Some code optimizations.
	   <SM8>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	  <LW11>	 4/14/93	DCB		Blocking interrupts around LockMemory/GetPhysical setup to
									prevent a re-select from causing this to happen twice or not at
									all.
	  <LW10>	 3/26/93	PW		Removed the generic DMA transfer routines from this file and put
									them into HALc96DMA.a.
	   <SM6>	 3/20/93	PW		Rolled in Ludwig changes.
	   <SM5>	 1/31/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <LW9>	  3/8/93	DCB		Increased the size of the locked down buffer. This helps the
									performance of old-API transactions.
	   <LW8>	  3/1/93	DCB		Added conditional compile for GetPhysical call. This aids
									performance testing.
	   <LW7>	 1/29/93	PW		Passing HALg into SetupIOPB function in order to check for
									HBAhasDMA.
	   <LW6>	 1/27/93	PW		Changed scsiDataPhys to Physical.
	   <LW5>	 1/27/93	DCB		Added workaround to a bug in the HWPriv.a GetPhysical. Seems
									that in cases where the logical range was not contiguous the
									logical address and count in the table were not updated
									correctly. The workaround reconstructs these fields manually so
									we don't get stuck in a loop.
	   <LW4>	 1/27/93	PW		Changed scsiScatterValid use to scsiDataType.
	   <LW3>	  1/6/93	DCB		Set kbUseDblBuffer bit in the SIMprivFlags if an address in the
									Parameter Block is in the ROM or above. This fixes the SCSI into
									NuBus bug. Radar Bug # 1059322. This prevents the PSC from doing
									DMA to addresses it can't handle by DMAing into a known locked
									down buffer and then blockmoving out to the NuBus address.
	   <LW2>	12/17/92	DCB		Fixed GetPhysical call which caused a user break in VM.
	   <SM4>	11/20/92	DCB		Removed unnecessary include
	   <SM3>	10/30/92	DCB		Added Setup and Teardown routines to support Direct DMA into a
									user
	   <SM2>	 7/28/92	PW		Resolved differences between Paul's and Clinton's sources.
	   <SM1>	 7/25/92	PW		Initial check-in.

*/

#include <Types.h>
#include <Memory.h>
#include <Errors.h>
#include <SCSI.h>
#include <SCSIStandard.h>

#include "SCSIDebug.h"
#include "ACAM.h"
#include "SIMCore.h"
#include "HALc96.h"
#include "SIMCorePriv.h"

#define MAX(a,b)  ((a)>=(b)?(a):(b))


/****** Function Prototypes For Inside only *******/


/****** Transfer Constants (Check HALc96DMA.a as well!) *******/
#define MIN_PSC_DMA_SIZE	0x200	// <LW9>


/*********************************************************************************
	InitHW_PSC	-	Initialize DMA Hardware 
*********************************************************************************/

// external
OSErr
InitHW_PSC( HALc96Globals *HALg)
{
#pragma unused (HALg)

	return (noErr);
}

/*********************************************************************************
	InitSW_PSC	-	Initialize Software stuff required for DMA support 
*********************************************************************************/

// external
OSErr
InitSW_PSC( HALc96Globals *HALg)
{
	OSErr		err;
	ulong		numBlocks, pageSize, bufferSize;
	void		*memStart, *pageStart;
	MemoryBlock				lockedBlock;
	LogicalToPhysicalTable	l2pTable;
	
	
	//*** WARNING:  The following code is Page Size Dependent !!! ***
	
	//*** WARNING:  Don't change these unless you change HALc96DMA.a as well
	pageSize = 8192;
	bufferSize = 1*pageSize;
	
	memStart = NewPtrSys( bufferSize+pageSize);	
	if (memStart==0) 
		return (memFullErr);
	
	pageStart = (void *)((((long)memStart-1) & ~(pageSize-1)) + pageSize);
	
	SetPtrSize( memStart, (long)pageStart + MAX(bufferSize,pageSize) - (long)memStart);
	
	err = LockMemory(pageStart, bufferSize);	
	if (err!=noErr) 
		return (err);
		
	lockedBlock.address = pageStart;
	lockedBlock.count   = bufferSize;
	
	l2pTable.logical = lockedBlock;
	numBlocks = 1;
	
	GetPhysical( &l2pTable, &numBlocks);
	
	HALg->physicalCopyBuffer = l2pTable.physical[0].address;
	HALg->logicalCopyBuffer = pageStart;
	HALg->minDMAsize = MIN_PSC_DMA_SIZE;

	return (noErr);
}

/*********************************************************************************
SetupIOPB	-	LockMemory on user buffers as necessary
*********************************************************************************/

void
SetupIOPSC( SIM_IO *ioPtr)
{
	int		i;
	SGRecord *sgList;
	Ptr		firstAddr = nil;
	ulong	firstLen = 0;
	ulong	cnt = 1;
	ushort	oldSR;
	
	
	// Have we already done it ?  If so, return
	//	(this could happen if we started it then got a reselect and then retried this one again)
		
	if( ioPtr->SIMprivFlags & (1 << kbSetupComplete) )
		return;	
		
	// Note that we don't do TIB's, Windows or CPM-86
	
	if ( (ioPtr->scsiFlags & scsiDataPhysical) || ioPtr->scsiFunctionCode == SCSIOldCall ) 
		return;

	oldSR = BlockInterrupts();	//-> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> ->

	if ( ioPtr->scsiDataType == scsiDataSG ) {	/* Scatter/Gather List */
		sgList = (SGRecord *) ioPtr->scsiDataPtr;
		for( i = 0; i < ioPtr->scsiSGListCount; i+=1 ) {
			/* No sense fooling with small transfers due to lock memory overhead
			   The data xfer routine will know that the buffer is not locked down and
			   will use the old routine instead of direct DMA.  (DMA to known locked buffer
			   and then BlockMove)
			*/
			if( sgList[i].SGCount <= MIN_PSC_DMA_SIZE )
				continue;	/* Don't bother */
			
			if( sgList[i].SGAddr >= 0x40000000 ) {				// Up in ROM or NuBus Land
				ioPtr->SIMprivFlags |= (1 << kbUseDblBuffer);	// <LW3>
				break;
			}
			
			if( LockMemory((Ptr)sgList[i].SGAddr,sgList[i].SGCount) != noErr ) {
				ioPtr->SIMprivFlags |= (1 << kbUseDblBuffer);	// <LW3>
				break;
			}
			else {
				ioPtr->SIMprivFlags |= (1 << kbSetupComplete);	
				if( !firstAddr ) {
					firstAddr = (Ptr)sgList[i].SGAddr;
					firstLen = sgList[i].SGCount;
				}
			}
		}
	}
	else {	/* else Address/Count */
		/* Don't bother with small buffers */
		if( ioPtr->scsiDataLength <= MIN_PSC_DMA_SIZE )
			goto exit;
				
		if( ioPtr->scsiDataPtr >= 0x40000000 ) {				// Up in ROM or NuBus Land
			ioPtr->SIMprivFlags |= (1 << kbUseDblBuffer);	// <LW3>
		}
		else {
			if( LockMemory(ioPtr->scsiDataPtr,ioPtr->scsiDataLength) != noErr ) 
				ioPtr->SIMprivFlags |= (1 << kbUseDblBuffer);
			else {
				ioPtr->SIMprivFlags |= (1 << kbSetupComplete);
				firstAddr = (Ptr)ioPtr->scsiDataPtr;
				firstLen = ioPtr->scsiDataLength;
			}
		}
	}

	if( (ioPtr->SIMprivFlags & (1 << kbUseDblBuffer)) == 0 && firstAddr && firstLen ) {		// <LW2>
		ioPtr->logical.address = firstAddr;
		ioPtr->logical.count = firstLen;
		if( GetPhysical((LogicalToPhysicalTable *)&ioPtr->logical,&cnt) )
			ioPtr->SIMprivFlags |= (1 << kbUseDblBuffer);	// <LW3>
		else 
		{
			// Check to see if the bug in GetPhysical caught us. <LW5> 
			// If it did we need to setup logical.address and logical.count
			// the way they are supposed to be.
			if( ioPtr->logical.address == firstAddr ) {
				(char *)ioPtr->logical.address += ioPtr->physical.count;
				ioPtr->logical.count -= ioPtr->physical.count;
			}
			ioPtr->transLogEnd = firstAddr + ioPtr->physical.count;
		}
	}

exit:
	UnblockInterrupts( oldSR); //<- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- 
}


/*********************************************************************************
TeardownIOPSC	-	UnlockMemory user buffers as necessary
*********************************************************************************/

void
TeardownIOPSC( SIM_IO * ioPtr, HALc96Globals * HALg)
{
#pragma unused(HALg)

	int i;
	SGRecord *sgList;

	/* Note that we don't do TIB's, Windows or CPM-86 */
	if( (ioPtr->scsiFlags & scsiDataPhysical) || ioPtr->scsiFunctionCode == SCSIOldCall ) 
		return;	/* Nothing more to do */

	if ( ioPtr->scsiDataType == scsiDataSG ) {	/* Scatter/Gather List */
		sgList = (SGRecord *) ioPtr->scsiDataPtr;
		for( i = 0; i < ioPtr->scsiSGListCount; i+=1 ) {
			/* Don't bother with small buffers */
			if( sgList[i].SGCount <= MIN_PSC_DMA_SIZE )
				continue;
		
			if( sgList[i].SGAddr >= 0x40000000 )				// Up in ROM or NuBus Land
				break;											// <LW3>
			
			UnlockMemory((Ptr)sgList[i].SGAddr,sgList[i].SGCount);	// Can't do anything about errors <LW3>
		}
	}
	else {	/* Address/Count */
		/* Don't bother with small buffers */
		if( ioPtr->scsiDataLength <= MIN_PSC_DMA_SIZE )
			return;

		if( ioPtr->scsiDataPtr < 0x40000000 ) 					// Up in ROM or NuBus Land <LW3>
			UnlockMemory(ioPtr->scsiDataPtr,ioPtr->scsiDataLength);	// Can't do anything about errors <LW3>
	}
}