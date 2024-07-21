/*
	File:		HALc96AMIC.c

	Contains:	routines that setup/teardown DMA buffers for AMIC

	Notes:
				
	Entry points:

	Written by:	Paul Wolf

	Copyright:	╘ 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	   <SM8>	11/22/93	pdw		Rolling in from <MCxx>.
	   <SM7>	11/10/93	chp		Fix a DebugStr string.
	   <SM6>	10/15/93	pdw		Fixing "Cold Fusion EVT2/VM" bug by always calling LockMemory on
									our permanent copy buffer.
	   <SM5>	10/14/93	pdw		Added support for Synchronous data transfers, rewrote State
									Machine, message handling etc.
	   <SM4>	 9/13/93	pdw		Changed the risky slash pattern.
	   <SM3>	  9/9/93	pdw		Lots of little changes.  Name changes, temporary cache_bug
									stuff.
	   <SM2>	 8/13/93	pdw		TEMPORARY: Reverted to 200 as MIN_DMA_SIZE and now I always call
									LockMemory - not just when VM is on.
		 <1>	 7/17/93	pdw		first checked in

*/

// NOTE: The following five symbols are mutually exclusive 
//			- only set one of them to 1 at a time
#define	COPYBACK		0
#define	NONCACHEABLE	1
#define	WRITE_THROUGH	0
// these two must be tied in with dbl-buffering also (push/flush must happen before DMA)
#define	COPYBACK_PUSH	0
#define	COPYBACK_FLUSH	0


#include <Types.h>
#include <Traps.h>
#include <TrapsPrivate.h>
#include <Memory.h>
#include <Errors.h>
#include <SCSI.h>
#include <SCSIStandard.h>

#include "SCSIDebug.h"
#include "Recorder.h"
#include "ACAM.h"
#include "SIMCore.h"
#include "HALc96.h"
#include "SIMCorePriv.h"
#include "SCSIGlue.h"

#define MAX(a,b)  ((a)>=(b)?(a):(b))


/****** Function Prototypes For Inside only *******/


/****** Transfer Constants (Check HALc96PSC.a as well!) *******/
#define MIN_AMIC_DMA_SIZE	0x200	// 20


/*********************************************************************************
	InitAMIC	-	Initialize DMA Hardware 
*********************************************************************************/

// external
OSErr
InitHW_AMIC( HALc96Globals *HALg)
{
#pragma unused (HALg)

	return (noErr);
}

/*********************************************************************************
	InitSW_AMIC	-	Initialize Software stuff required for DMA support 
*********************************************************************************/

// external
OSErr
InitSW_AMIC( HALc96Globals *HALg)
{
	long		err;
	ulong		numBlocks, pageSize, bufferSize;
	void		*memStart, *pageStart;
	MemoryBlock				lockedBlock;
	LogicalToPhysicalTable	l2pTable;
	
	
	//*** WARNING:  The following code is Page Size Dependent !!! ***
	
//*** WARNING:  Don't change these unless you change HALc96DMA.a as well
	pageSize = 4*1024;
//*** WARNING:  Don't change this unless you change HALc96DMA.a as well
	bufferSize = 1*pageSize;	// must be a multiple of pageSize
	
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
	HALg->minDMAsize = MIN_AMIC_DMA_SIZE;

	return (noErr);
}


/*********************************************************************************
SetupIOAMIC	-	LockMemory on user buffers as necessary
*********************************************************************************/

void
SetupIOAMIC( SIM_IO *ioPtr)
{
	int		i;
	SGRecord *sgList;
	Ptr		firstAddr = nil;
	ulong	firstLen = 0;
	ulong	cnt = 1;
	Ptr		pageStart;
	long	err;
	Ptr		addr;
	ulong	count;
		


// Have we already done it ?  If so, return
//	(this could happen if we started it then got a reselect and then retried this one again)
		
	if( ioPtr->SIMprivFlags & (1 << kbSetupComplete) )
		return;	
		
	IfRecordEvent( (long)ioPtr, (long)'suIO');

// Note that we don't do TIB's because we would have to pre-interpret them nor do we do 
//	anything with scsiDataPhysical ranges because they should be taken care of by client 
//	(at least they're supposed to).  We won't get here with a TIB since old-API transactions
//	are handled by DoSelect not DoInitiate (which is where the call to SetupIO happens).
	
	if ( ioPtr->scsiFlags & scsiDataPhysical ) 
		return;

//ииииииииииииииииииии Scatter/Gather List ииииииииииииииииииии

	if ( ioPtr->scsiDataType == scsiDataSG ) 
	{
		sgList = (SGRecord *) ioPtr->scsiDataPtr;
		
		for( i = 0; i < ioPtr->scsiSGListCount; i+=1 ) 
		{
			/* No sense fooling with small transfers due to lock memory overhead
			   The data xfer routine will know that the buffer is not locked down and
			   will use the old routine instead of direct DMA.  (DMA to known locked buffer
			   and then BlockMove)
			*/
			if( (count = sgList[i].SGCount) <= MIN_AMIC_DMA_SIZE )
				continue;	/* Don't bother */
			
			if( (ulong)(addr = (Ptr)(sgList[i].SGAddr)) >= 0x40000000 ) { // Up in ROM or NuBus Land
				ioPtr->SIMprivFlags |= (1 << kbUseDblBuffer);
				break;
			}

			if (VMRunning()) 
			{											// <SM2> pdw
				if( noErr != LockMemory( addr, count) ) {
					ioPtr->SIMprivFlags |= (1 << kbUseDblBuffer);
					break;
				}
				else {
					ioPtr->SIMprivFlags |= (1 << kbSetupComplete);	
					if( !firstAddr ) {
						firstAddr = addr;
						firstLen = count;
					}
				}
			}
			else // VM not running
			{
#if WRITE_THROUGH
				pageStart = (Ptr)( (ulong)addr & (0xFFFFF000));
				do {
					err = nkMakePageWriteThrough( (Ptr)((long)pageStart>>12));
					if (err<0)
						DebugStr("\p nkMakePageWriteThrough failed");
					pageStart += 0x1000;
				} while ( pageStart < addr+count);
				
				ioPtr->SIMprivFlags |= (1 << kbSetupComplete);
#elif NONCACHEABLE
				pageStart = (Ptr)( (ulong)addr & (0xFFFFF000));
				do {
					err = nkMakePageNonCacheable( (Ptr)((long)pageStart>>12));
					if (err<0)
						DebugStr("\p nkMakePageNonCacheable failed");
					pageStart += 0x1000;
				} while ( pageStart < addr+count);
				
				ioPtr->SIMprivFlags |= (1 << kbSetupComplete);
#elif COPYBACK_PUSH
				err = nkPushCacheRange(addr, count);
				if (err<0)
					DebugStr("\p nkPushCacheRange failed");
#elif COPYBACK_FLUSH
				err = nkFlushCacheRange(addr, count);
				if (err<0)
					DebugStr("\p nkFlushCacheRange failed");
#endif
				firstAddr = addr;
				firstLen = count;
			}
		}
	}
	
//ииииииииииииииииииии else Address/Count ииииииииииииииииииии

	else {	
		/* Don't bother with small buffers */
		if( (firstLen = ioPtr->scsiDataLength) <= MIN_AMIC_DMA_SIZE )
			return;
				
		if( (ulong)(firstAddr = ioPtr->scsiDataPtr) >= 0x40000000 ) { // Up in ROM or NuBus Land
			ioPtr->SIMprivFlags |= (1 << kbUseDblBuffer);
		}
		else {
			if (VMRunning()) {											// <SM2> pdw
				IfRecordEvent( (long)firstAddr, (long)'LkMm');
				if( err = LockMemory( firstAddr, firstLen) != noErr ) 
					ioPtr->SIMprivFlags |= (1 << kbUseDblBuffer);
				else {
					ioPtr->SIMprivFlags |= (1 << kbSetupComplete);
				IfRecordEvent( (long)firstLen, (long)err);
				}
			}
			else // VM not running
			{
#if WRITE_THROUGH
				pageStart = (Ptr)( (ulong)firstAddr & (0xFFFFF000));
				do {
					err = nkMakePageWriteThrough( (Ptr)((long)pageStart>>12));
					if (err<0)
						DebugStr("\p nkMakePageWriteThrough failed");
					pageStart += 0x1000;
				} while ( pageStart < firstAddr+firstLen);
				
				ioPtr->SIMprivFlags |= (1 << kbSetupComplete);
#elif NONCACHEABLE
				pageStart = (Ptr)( (ulong)firstAddr & (0xFFFFF000));
				do {
					err = nkMakePageNonCacheable( (Ptr)((long)pageStart>>12));
					if (err<0)
						DebugStr("\p nkMakePageWriteThrough failed");
					pageStart += 0x1000;
				} while ( pageStart < firstAddr+firstLen);
				
				ioPtr->SIMprivFlags |= (1 << kbSetupComplete);
#elif COPYBACK_PUSH
				err = nkPushCacheRange(firstAddr, firstLen);
				if (err<0)
					DebugStr("\p nkPushCacheRange failed");
#elif COPYBACK_FLUSH
				err = nkFlushCacheRange(firstAddr, firstLen);
				if (err<0)
					DebugStr("\p nkFlushCacheRange failed");
#endif
			}
		}
	}
	
//ииииииииииииииииииии Do an initial GetPhysical ииииииииииииииииииии

	if( (ioPtr->SIMprivFlags & (1 << kbUseDblBuffer)) == 0 && firstAddr && firstLen ) {
		ioPtr->logical.address = firstAddr;
		ioPtr->logical.count = firstLen;
		if( GetPhysical( (LogicalToPhysicalTable *)&ioPtr->logical, &cnt) )
			ioPtr->SIMprivFlags |= (1 << kbUseDblBuffer);
		else 
		{
			// Check to see if the bug in GetPhysical caught us.
			// If it did we need to setup logical.address and logical.count
			// the way they are supposed to be.
			if( ioPtr->logical.address == firstAddr ) {
				(char *)ioPtr->logical.address += ioPtr->physical.count;
				ioPtr->logical.count -= ioPtr->physical.count;
			}
			ioPtr->transLogEnd = firstAddr + ioPtr->physical.count;
		}
	}
}

/*********************************************************************************
TeardownIOAMIC	-	UnlockMemory user buffers as necessary
*********************************************************************************/

void
TeardownIOAMIC( SIM_IO * ioPtr, HALc96Globals * HALg)
{
#pragma unused(HALg)

	Ptr			pageStart;
	int			i;
	SGRecord 	* sgList;
	Ptr			addr;
	ulong		count;
	long		err;

// We don't need to check whether we should be here or not because the flag 
//	kbSetupComplete (in ioPtr->SIMprivFlags) will be set only if LockMemory or other
//	undo-required things were done in SetupIO, and that flag is checked
//	before this routine is called (optimization).

	/* Scatter/Gather List */
	
	if ( ioPtr->scsiDataType == scsiDataSG ) 
	{
		sgList = (SGRecord *) ioPtr->scsiDataPtr;
		
		for( i = 0; i < ioPtr->scsiSGListCount; i+=1 ) 
		{
			/* Don't bother with small buffers */
			if( (count = sgList[i].SGCount) <= MIN_AMIC_DMA_SIZE )
				continue;
		
			if( (ulong)(addr = (Ptr)(sgList[i].SGAddr)) >= 0x40000000 )	// Up in ROM or NuBus Land
				break;
			
			IfRecordEvent( (long)addr, (long)'UnLk');
			err = UnlockMemory( addr, count);	// Can't do anything about errors
			IfRecordEvent( (long)count, (long)err);

		}
	}
	
	/* Address/Count */
	
	else 
	{	
		if (VMRunning()) 
		{
			IfRecordEvent( (long)ioPtr->scsiDataPtr, (long)'UnLk');
			err = UnlockMemory(ioPtr->scsiDataPtr, ioPtr->scsiDataLength);
			IfRecordEvent( (long)ioPtr->scsiDataLength, (long)err);
		}
		else 
		{ // VM not running
#if WRITE_THROUGH | NONCACHEABLE
			pageStart = (Ptr)( (ulong)(addr=ioPtr->scsiDataPtr) & (0xFFFFF000));
			do {
				IfRecordEvent( (long)pageStart, (long)'MPgC');
				err = nkMakePageCacheable( (Ptr)((long)pageStart>>12));
				if (err<0)
					DebugStr("\p nkMakePageCacheable failed");
				pageStart += 0x1000;
			} while ( pageStart < addr+ioPtr->scsiDataLength);
#else
			IfRecordEvent( (long)ioPtr->scsiDataPtr, (long)'UnL2');
			err = UnlockMemory( ioPtr->scsiDataPtr, ioPtr->scsiDataLength);
			IfRecordEvent( (long)ioPtr->scsiDataLength, (long)err);
#endif
		}
	}
}