/*
	File:		ProcessMgrHeap.c  (used to be ProcessMgr.c)

	Contains:	Internal and External routines to support the Process Manager

	Written by:	Jeff Crawford

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<34>	11/29/93	BT		#1126549 <BT,JRG> change InitProcessMgrZone to not set
									fSkipPurgeBeforeGZ if VM is on.
		<33>	10/14/93	BT		<BT, EPT> Radar 1117552; Change interfaces around.
		<32>	 8/31/93	BT		<BT, SL> #1101787; TempMaxMem was returning the amount of memory
									that included the purgeable space in the system zone, but this
									space could not be freed by the process manager grow zone proc.
									Since the space couldn't be made, the GZProc would return 0,
									then the code would bail. The fix is not to include the
									purgeable space in the Straddle Block portion of the system heap
									in the TempMaxMem calculation, which we really shouldn't be
									touching anyways.
		<31>	 8/19/93	BT		<BT, cam> Add "#ifdef hasFirstLevelFakeHandleTests" around
									remaining range checks.  This defined in MemMgr.h unless
									"cancelFigmentRangeChecking" is set true.
		<30>	 8/19/93	JC		Fixed ExtendSystemZone to grow more than kMinFree. This was
									uncovered while fixing the Timbuktu bug.
		<29>	 8/17/93	BT		<BT, bsp>  changed a typecast on LMGetFakeHandleRange()
		<28>	 8/10/93	JC		<mlw> Fixed range problem with VM on by setting fake handle
									range when the ProcessMgr zone is initialized.
		<27>	  8/9/93	JC		<ewa> #1101787, #1103834, Make minor changes to support ThinkC
									test app. Fetch size directly instead of calling GetHandleSize
									for more a accurate size. Fixed ShrinkProcessMgrZone to handle
									the zero size case. We now interpret MinSysHeapFreeSpace to be a
									physical block size.
		<26>	 7/16/93	JC		Made changes to support the linked Think C build.
		<25>	  7/2/93	BT		(With EPT) Radar #1095398. Fix internal Memory Manager calls to
									go thru the trap table interface.
		<24>	 6/28/93	JC		Fixed the fSkipPurgeBeforeGZ bit to not be set until ProcessMgr
									launch time. This fixes the problem where some inits
									(WorldScript) would require blocks to be purged in the System
									Heap during the boot process. Also made sure this bit is saved
									and restored across ShrinkSysHeap calls.
		<23>	 6/16/93	JC		Added universal low memory getters and setters.
		<22>	 6/16/93	BMC		StarTrek - adding MemPriv.h, removing call to VM_HoldSystemHeap.
		<21>	 6/10/93	JC		Added checks to make sure we move the Sys/PM zone boundary by at
									least kMinBlockSize.
		<20>	  6/9/93	JC		Cleaned up some comments.
		<19>	  6/8/93	JC		Add simple cast.
		<18>	  6/1/93	BMC		StarTrek support
		<17>	  6/1/93	BMC		StarTrek support - rename header files & extend conditionals to
									not include ExpandmemPriv.h & VMCallsPriv.h
		<16>	  6/1/93	JC		Added linked_thinkc_app conditional around ExpandMemPriv.h &
									VMCallsPriv.h.
		<15>	 5/26/93	BT		Remove the conditionals around including ExpandMemPriv.h and
									VMCallsPriv.h.
		<14>	 5/24/93	JC		Changed XXX to DbgXXX for all debug routines.
		<13>	 5/24/93	JC		Fix MP block problem in the ProcessMgr Heap.
		<12>	 5/19/93	JC		Began changes as requested by the code review. Removed options
									parameter from AllocateMoreMasters.
		<11>	 5/18/93	JC		Fixed the “zero k available” bug. Yippee! This fix requires a
									new ProcessMgr to work completely.
		<10>	 5/14/93	JC		Cleaned up implementation of GZRootPtr, GZRootHnd and GZMoveHnd.
		 <9>	  5/2/93	JC		Use zone compatibility flags.
		 <8>	 4/26/93	JC		Fix bug in ReclaimSpaceIfSysHeapLow.
		 <6>	 4/18/93	JC		Changed #defines to more acurate descriptions. Changed
									small_block_headers to small_freeBlock_headers and linkedIn to
									linked_thinkc_app.   •• Brian & Sam take note.••
		 <5>	 4/18/93	JC		Cleaned up for Code Review
		 <1>	 8/4/92		JC		New Today

*/

#ifndef THINK_C
	#ifdef StarTrek
		#include <MacTypes.h>
		#include <MacMem.h>
		#include <Gestalt.h>
		#include <Errors.h>
		#include <OSUtils.h>
	#else
		#include <Types.h>
		#include <Memory.h>
		#include <GestaltEqu.h>
		#include <Errors.h>
		#include <OSUtils.h>
	#endif
#else
	/* we do this so we can compile this mess under Think C and have it call the right thing */
	#define GetHandleSize(x) c_GetHandleSize(x)
#endif

#ifdef StarTrek
	#include "MemDebug.h"
	#include "MemMgr.h"
	#include "MemRout.h"
	#include "MemPriv.h"
#else
	#include "MemMgrDebug.h"
	#include "MemMgr.h"
	#include "MemoryRoutines.h"
#endif


#if !defined(linked_thinkc_app) && !defined(StarTrek)
	#include <ExpandMemPriv.h>
	#include <VMCallsPriv.h>
#endif

#ifdef patchedIn
	/* This will overcome the 32k limit */
	#pragma segment Figment
#endif

#ifdef THINK_C
	/* This will overcome the 32k limit */
	#pragma segment Figment
#endif

/*
 *	Note: ProcessMgrHiNewHandle and ProcessMgrNewHandle are not implemented as part
 *	of these routines. They are implemented as part of the ProcessMgr instead. Their
 *	implementations are very simple.
 */

/*
 *	and a prototype for good cheer...
 */
Size GetSystemHiPurgeBytes(void);


/*
 *	Initializes the ProcessMgr heap to enable its flexible boundary with the system
 *	heap. On exit, the new heap's header will be above the memory of the heap. A 
 *	fake heap header is created down low to spoof any heap walkers like Macsbug.
 */
THz c_InitProcessMgrHeap(THz oldHeap)
	{
	stdHeap*		newHeap;
	ushort			cMoreMasters;
	long			VMResult;
		
	IfIntDebugMsg(LMGetTheZone() != LMGetApplZone(),"TheZone != ApplZone", LMGetTheZone());
	IfIntDebugMsg(LMGetTheZone() != (stdHeap*) oldHeap,"TheZone != oldHeap", oldHeap);

	/*
	 *	First we move the heap header upwards above the memory it controls. We do it 
	 *	now while memory is simple and its easy of move it. The old version of 
	 *	ProcessMgr would move the heap header during requests of the system heap
	 *	or the ProcessMgr heap. This implementation is inefficient since it must update
	 *	the relative handle of each relocatable block in the zone. This new version
	 *	is lighter weight and will permit the boundary between the zones move more
	 *	quickly.
	 */
	newHeap = MoveHeapHeaderHigh((stdHeap*)oldHeap);
	/* header is moved high. The heap memory is below it. Everything else still works. */

	#ifdef hasFirstLevelFakeHandleTests
		/*
		 *	When VM is on, the FakeHandleRange can be set to low since it's initialized to
		 *	RealMemTop. When the ProcessMgrHeap is "reinitialized" its heap heap header 
		 *	becomes high, so we use it to set the new fake handle range.
		 */
		if (newHeap > (stdHeap *)LMGetFakeHandleRange()) /* are we creating a heap above the range? */
			LMSetFakeHandleRange((void*)newHeap);		/* yes, set new range. */
	#endif
	
	/*
	 *	allocate the "dummy" block down low. The dummy block will be use later to expand
	 *	the zone by calling SetPtrSize on it.
	 */
	{
		stdHeap*	fakeHeap;
		stdBlock3*	dummy;

		/*
		 *	Note: In order to fake client who like to walk the ProcessMgrHeap, (Macsbug HZ),
		 *	we create a fake heap header at the beginning of the PM heap. This header must be
		 *	directly after the System heap and its oldBackLimit must point to the spoof trailer
		 *	block. The Dummy block comes 4 bytes before the end of the fake heap header. For
		 *	the PM heap only, the Dummy block IS the Spoof block.
		 */

		/* allocate space for the fake PM heap header and the dummy block */	
		fakeHeap = (stdHeap*) NewBlock(kOriginalHeapHeaderSize + kOldHeaderSize, kAllocateLow, newHeap);

		/* Clear all fields (except the last one) in the fake heap header  */
		ClearBytes(fakeHeap, kPMFakeHeapStartOffset);
		
		/* set up fields to fake out people that walk the PM heap */
		fakeHeap->oldBackLimit = newHeap->oldBackLimit;
		fakeHeap->heapID = newHeap->heapID;
		fakeHeap->heapType = newHeap->heapType;
		fakeHeap->purgePtr = kFakePMPurgePtr;
		fakeHeap->nextUp = kFakePMNextUp;
		fakeHeap->nextIn = kFakePMNextIn;
		fakeHeap->heapStart = kFakePMHeapStart;
		fakeHeap->lowestRemovableBlock = kFakePMLowestRemovable;

		/* get the dummy block, use it so clients can walk the heap */
		dummy = (stdBlock3*) ((Ptr)fakeHeap + kPMFakeHeapStartOffset);
		
		/* Note: in this scenario, the dummy block IS the spoof block, they are the same */
		BACK(dummy) = nil;		
		dummy->size = 16; 		/* this offset gets us to the first real block */

		/* set fields in the dummy block */
		MarkBlockAsPrivate((stdBlock*)dummy, 0, newHeap);
		dummy->parent = newHeap;
		ResetNextGuysBackPtr(dummy);
		newHeap->lowestRemovableBlock = GetNextBlock(dummy);
		
		newHeap->heapStart = dummy;		/* dummy is now the first block in the heap */
	}

	/* establish link with system heap */
	LMGetSysZone()->nextUp = newHeap;

	/*
	 *	When allocating memory in the system heap, we want to expand the 
	 *	zone (into the PM heap) before we start purging blocks. This 
	 *	optimization will allow the Sys/PM heap boundary to "float" without 
	 *	unnecessary purging blocks in the system heap.
	 *
	 *	Note: Blocks can still be purged, but only after the growzone proc is called.
	 */
	/* 11/29/93 5:33:08 PM (BET): Change this so it only sets the bit if VM is off.  The
	 * SysHeap is always held in memory, we don't want the held allocation to grow over time,
	 * possibly eating up available physical RAM.
	 */
	#if !defined(linked_thinkc_app) && !defined(StarTrek)
	if (!((Gestalt(gestaltVMAttr,&VMResult) == noErr) && (VMResult & (1 << gestaltVMPresent))))
		LMGetSysZone()->fSkipPurgeBeforeGZ = 1;
	#endif

	/* Update appropriate lowmem locations to reflect new location */
	if (LMGetTheZone() == (stdHeap*)oldHeap)
		LMSetTheZone(newHeap);
	if (LMGetApplZone() == (stdHeap*)oldHeap)
		LMSetApplZone(newHeap);

	/* easy way to tell the world that this is the process manager heap */	
	newHeap->fHeapIsProcessMgrHeap = 1;

	/* Make a good guess for the number of master pointers for the heap */
	cMoreMasters = ((Ptr)newHeap->backLimit - (Ptr)newHeap->heapStart)/kZoneBytesPerMP;
	if (newHeap->MPCount < cMoreMasters)
		newHeap->MPCount = cMoreMasters;
		
	/* allocate MPBlock high so it won't interfere with the flexible boundary */
	AllocateMoreMasters(newHeap);

	DbgCheckHeap(newHeap);
	return (THz) newHeap;
	}
 
/* ShrinkSysHeap.  Try to shrink the system heap by exactly sizeNeeded bytes, but
 * ensure we don't leave less than a minimum sized free block at the top.
 * NOTE:  Have to disable the sys gz proc to stop it from trying to shrink the
 * Process Mgr heap, leading to an unwanted recursion.
 *
 * Returns the amount we were able to get (0 on failure).
 */
Size c_ShrinkSysHeap(Size sizeNeeded)
	{
	stdHeap*		curHeap = LMGetSysZone();
	Size			realSizeNeeded;
	Boolean			savedPurgeBitState;

	/*
	 *	If size is really small, we force it to the minimum block size. This permits
	 *	LowerProcessMgrZone bottom to create a real free block when it lowers the zone.
	 */
	if (sizeNeeded < kMinBlockSize)
		sizeNeeded = kMinBlockSize;			/* already aligned */
	else
		sizeNeeded = AlignUp(sizeNeeded);	/* align it */

	DbgCheckSize(sizeNeeded);
	
	/* Don't even try if the amount is so big we overflow when trying to leave space */
	if ((realSizeNeeded = sizeNeeded + GetExpandMemMinSysHeapFreeSpace()) < sizeNeeded)
		return 0;
	
	realSizeNeeded = AlignUp(realSizeNeeded);

	/*
	 *	In order for the Sytem heap to shrink, we turn this optimizaition off for this
	 *	particular call to make space. We turn thit back on when we are done.
	 */
	savedPurgeBitState = curHeap->fSkipPurgeBeforeGZ;	/* save so we can restore later */
	curHeap->fSkipPurgeBeforeGZ = 0;					/* turn purging on in the System Heap */
	
	/* Try to make space at the very top of the System Heap */
	if (nil == MakeSpaceHigh(realSizeNeeded, kDoFirstRegionOnly+kAllocateHigh+kDontCallGZ+kDontCreateFragment, curHeap))
		{
		/* could not get enough space, return 0 */
		sizeNeeded = 0;
		}
	else
		{
		/* enough space has been made, return the size needed */
		ShrinkHeapLimit(sizeNeeded, curHeap);
		}
	
	curHeap->fSkipPurgeBeforeGZ = savedPurgeBitState;			/* turn purging back off in the System Heap */

	/* Cleanup and return */
	FlushCacheIfNeeded(curHeap);
	DbgCheckHeap(curHeap);

	return sizeNeeded;
	}


/* Lower the bottom of the Process Mgr heap by cbLower bytes, where
 * cbLower >= MINGROWTH.
 * Assumes A5 = PROCESSMGRGLOBALS
 * NOTE:  Have to handle case where old ptr had size correction.
 */
void	
c_LowerProcessMgrZoneBottom(Size amountToLower, THz thePMHeap)
	{
	stdHeap*	pmHeap = (stdHeap*) thePMHeap;
	long		VMResult;
	ptrBlock*	oldStart;
	ptrBlock*	newStart;
	freeBlock*	newFreeBlock;

	amountToLower = AlignUp(amountToLower);

	/* calculate old start block, new start block */
	oldStart = pmHeap->heapStart;
	newStart = (ptrBlock*) ((Ptr)oldStart - amountToLower);

	/* copy data of fake heap header to new location */
	MoveBytes((Ptr)oldStart - kPMFakeHeapStartOffset, (Ptr)newStart - kPMFakeHeapStartOffset, kPMFakeHeapStartOffset);

	/* create new private block at start of heap */
	BACK(newStart) = nil;
	newStart->size = kMinBlockSize;
	MarkBlockAsPrivate(newStart, 0, pmHeap);
	pmHeap->heapStart = newStart;

	/* get new free block location */	
	pmHeap->lowestRemovableBlock = newFreeBlock = (freeBlock*) ((Ptr)newStart + newStart->size);

	/* set up the new free block's header */
	BACK(newFreeBlock) = newStart;
	newFreeBlock->size =  amountToLower - newStart->size + oldStart->size;
	ResetNextGuysBackPtr(newFreeBlock);

	/* Now we kill, the space. KillBlock will fix up the heap headers for us */	
	KillBlock((stdBlock*)newFreeBlock, pmHeap);
	
	/* 
	 * Let VM know what happened.  VM needs to "hold down" the entire system heap.  Since
	 * we just shrank that heap, VM can reassess the heap, most likely unholding the area
	 * we removed.
	 */
	#if !defined(linked_thinkc_app) && !defined(StarTrek)
	if ((Gestalt(gestaltVMAttr,&VMResult) == noErr) && (VMResult & (1 << gestaltVMPresent)))
		(void) VM_HoldSystemHeap();
	#endif

	DbgCheckHeap(pmHeap);
	}


/*
 * ShrinkProcessMgrZone.  Try to shrink the Process Mgr heap by sizeNeeded bytes.  Works
 * by growing the dummy block up (with the GZ proc disabled!), then moving the zone
 * header up to the end of it.
 *
 * NOTE: Does not adjust the system zone!  When we return to caller, there is a
 * vacuum between the two zones that should caller should fix with ExtendZone.
 *
 */
Size
c_ShrinkProcessMgrZone(Size sizeNeeded, THz oldPMHeap)
	{
	stdHeap*		pmHeap = (stdHeap*)oldPMHeap;
	ptrBlock*		dummyPtr;
	Ptr				oldHeap;

	/*
	 *	If size is really small, we force it to the minimum block size. This permits
	 *	ExtendSystemZone to create a real free block when it makes more space.
	 */
	if (sizeNeeded < kMinBlockSize)
		{
		/* one simple check to see if we are shrinking by zero bytes */
		if (0 == sizeNeeded)
			return sizeNeeded;
		
		sizeNeeded = kMinBlockSize;			/* already aligned */
		}
	else
		sizeNeeded = AlignUp(sizeNeeded);	/* align it */
		
	DbgCheckSize(sizeNeeded);
		
	dummyPtr = (ptrBlock*) pmHeap->heapStart;
	oldHeap = (Ptr)dummyPtr - kPMFakeHeapStartOffset;
	
	/* Try to grow the dummy block to desired size, making sure that
	 * the ProcessMgrZone GZ proc is temporarily disabled.
	 */
	{
		GrowZoneProcPtr	savedGZ;
		
		savedGZ = pmHeap->gzProc;
		pmHeap->gzProc = nil;
		
		/* grow the zone up by calling SetPtrSize */
		dummyPtr = SetBlockSize(dummyPtr, sizeNeeded + kMinBlockSize, pmHeap);
		
		/* restore the growzone proc */
		pmHeap->gzProc = savedGZ;
	}

	if (!dummyPtr)
		{
		/* Not enough memory ... oh well! */
		sizeNeeded = 0;			/* we return this */
		}
	else
		{
		stdBlock*		nextBlock;

		/* create a dummy block in the upper part of the old one */
		nextBlock = GetNextBlock(dummyPtr);
		dummyPtr = (ptrBlock*) ((Ptr) dummyPtr + sizeNeeded);	/* get new location of new dummyPtr */
		dummyPtr->back = 0;										/* fill in header contents */
	
		dummyPtr->size = (Ptr) nextBlock - (Ptr) dummyPtr;
		MarkBlockAsPrivate(dummyPtr, 0, pmHeap);
	
		nextBlock->back = dummyPtr;			/* reset back link */
	
		/* fix the heap header changes */	
		pmHeap->heapStart = dummyPtr;
		pmHeap->lowestRemovableBlock = WalkUpFindNewLowRemoveable(dummyPtr, pmHeap);
		
		/* Copy the contents of the fake heap ptr to the new location */
		MoveBytes(oldHeap, (Ptr)dummyPtr - kPMFakeHeapStartOffset, kPMFakeHeapStartOffset);
		}
	
	FlushCacheIfNeeded(pmHeap);
	DbgCheckHeap(pmHeap);

	/* tell caller how much we got */
	return sizeNeeded;
	}


void
c_ExtendSystemZone(Size sizeNeeded)
	{
	sizeNeeded = AlignUp(sizeNeeded);

	/* make sure size is large enough block so we can dispose it */
	if (sizeNeeded < kMinFreeBlockSize)
		sizeNeeded = kMinFreeBlockSize;
	
	ExtendHeapLimit((ptrBlock*)((char*) LMGetSysZone()->backLimit + sizeNeeded), LMGetSysZone());
	
	DbgCheckHeap(LMGetSysZone());
	}

/* ReclaimSpaceIfSysHeapLow.  Check whether, after the allocation of the specified handle,
 * the space available to the system heap is below our predefined threshold.  If it is,
 * we try to grow the system heap to get the emMinSysHeapFreeSpace, or at least as much
 * as we can.
 */
 /* weirdness with theNewHandle, is it a "Handle" or a "Handle*" */
void
c_ReclaimSpaceIfSysHeapLow(Handle *theNewHandle, THz pmHeap)
	{
	Boolean			handleInStraddle;
	Size			lowPM, highSys, roomInPM;

	/* Make dirtcheap check first to avoid expensive scan of the more popular heap. */
	if (GetProcessMgrLoFreeBytes(nil, nil) >= GetExpandMemMinSysHeapFreeSpace())
			return;
	
	/*
	 * Just leave if there is sufficient memory or if the handle is not in the bottom
	 * part of the Process Mgr heap where it can be usefully reclaimed.
	 */
	if ( (StraddleBlockSize(&lowPM, &highSys, *theNewHandle, &handleInStraddle, pmHeap) != 0) ||
		(handleInStraddle == false) )
		return;
		
	/*
	 * We can get more if we dispose the new handle first.  Bound sys heap growth to the
	 * emMinSysHeapFreeSpace, since freeing the block may give us more than we need.
	 *
	 * roomInPM = lowPM + blockSize;
	 */
	roomInPM = lowPM + ((stdBlock*)GetBlockHeaderFromPtr(**theNewHandle))->size;
	
	if (highSys + roomInPM > GetExpandMemMinSysHeapFreeSpace())
		roomInPM = GetExpandMemMinSysHeapFreeSpace() - highSys;
	
	#ifdef linked_thinkc_app	
		c_DisposeHandle(*theNewHandle);
	#else
		DisposeHandle(*theNewHandle);
	#endif
	
	/* shrink pm zone, extend system zone */
	if ((roomInPM = ShrinkProcessMgrZone(roomInPM, pmHeap)) != 0)
		ExtendHeapLimit((ptrBlock*)((char*) LMGetSysZone()->backLimit + roomInPM), LMGetSysZone());
		
	LMSetMemErr(memFullErr);
	*theNewHandle = nil;
	}


/* StraddleBlockSize.  Calculate the number of free/purgeable bytes in the area of
 * memory shared by the System and Process Mgr heaps.  Size returned is a physical
 * block size.
 */
Size
c_StraddleBlockSize(Size *lowPMStorage, Size *highSysStorage, Handle blockOfInterest, Boolean *sawInterestingBlock, THz pmHeap)
	{
#pragma unused(pmHeap)			/* This parameter not needed */
	blockSize_t	blockSize;
	
	IfIntDebugMsg(lowPMStorage == nil, "lowPMStorage == nil", 0);

	/* Figure out how much we can get from the top of the system heap, and
	 * add in what we can get from the bottom of the Process Mgr heap.
	 */
	blockSize = GetSystemHiFreeBytes();
	if (highSysStorage != nil)
		*highSysStorage = blockSize;
	blockSize += *lowPMStorage = GetProcessMgrLoFreeBytes(blockOfInterest, sawInterestingBlock);

	/* Allow for the fact that we must leave space at the top of the system heap */
	if (blockSize < GetExpandMemMinSysHeapFreeSpace())
		blockSize = 0;
	else
		blockSize -= GetExpandMemMinSysHeapFreeSpace();
	
	return blockSize;
	}


/*
 *	GetProcessMgrHiMaxBlock.  Do like MaxBlock() on the Process Mgr zone, but ignore
 *	the straddle area part. Better stated: Calculate largest block above the straddle 
 *	area. Returns 0 if no such block is found. Note: returns a logical size.
 */
static Size GetProcessMgrHiMaxBlock(stdHeap* pmHeap);
static Size GetProcessMgrHiMaxBlock(stdHeap* pmHeap)
	{
	stdBlock*		workBlock;
	Size			blockSize, hiMaxBlock, thisRangeFree;
	Boolean			aboveStraddle;

	aboveStraddle = false;
	thisRangeFree = 0;
	hiMaxBlock = 0;

	/* Skip dummy block */
	workBlock = pmHeap->heapStart;
	workBlock = GetNextBlock(workBlock);

	/* Walk the heap */
	while (workBlock < pmHeap->backLimit)
		{
		blockSize = workBlock->size;	/* cache work block size */

		/* Count this block in if it is free or purgeable.  Reset the counter if the
		 * if the block is non-relocatable, relocatable but locked, or of some unknown
		 * new type, since we're looking for memory *between* such blocks.
		 */
		if (workBlock->handleBit == 1)
			{
			if (workBlock->lockBit == 1)
				{
				/* locked handle */
				if ((thisRangeFree > hiMaxBlock) && (aboveStraddle))
					hiMaxBlock = thisRangeFree;
				aboveStraddle = true;
				thisRangeFree = 0;
				}
			else if (workBlock->purgeBit == 1)
				{
				thisRangeFree += blockSize;
				}
			}
		else if (workBlock->ptrBit == 1)
			{
			/* block is a pointer block */
			if ((thisRangeFree > hiMaxBlock) && (aboveStraddle))
				hiMaxBlock = thisRangeFree;
			aboveStraddle = true;
			thisRangeFree = 0;
			}
		else
			{
			/* block is free */
			thisRangeFree += blockSize;
			}

		/* march workblock */
		workBlock = (stdBlock*) ((char*)workBlock + blockSize);
		}

	return hiMaxBlock ? hiMaxBlock - kBlockOverhead: 0;
	}


/* ProcessMgrMaxBlock.  Act like a MaxBlock() on the Process Mgr heap, except that we
 * count purgeable space. Size returned is a logical size.
 */
Size
c_ProcessMgrMaxBlock(THz pmHeap)
	{
	Size		straddleBlockSize, hiMaxBlock, junk, headerBytes;

	/* Calculate largest block above the straddle area. */
	hiMaxBlock = GetProcessMgrHiMaxBlock((stdHeap*)pmHeap);

	/* Calculate amount that we can get by combining the top of the system heap
	 * with the bottom of the Process Mgr zone.  StraddleBlockSize() result is a
	 * physical block size.  ProcessMgrMaxBlock returns the maximum *logical* block size
	 * that could be requested of TempNewHandle.
	 */
	straddleBlockSize = StraddleBlockSize(&junk, nil, nil, nil, pmHeap);
	
	/* This value contains the amount that the system heap has marked as purgeable also.
	 * Unless we expect to purge the system heap when we move the boundary, we are not going
	 * to be able to recover all of this.  Since we would have to teach either GetSystemHiFreeBytes()
	 * about purgeable blocks (no good because it is exported to the system GZProc who needs this info)
	 * or StraddleBlockSize itself about this, which is also no good because it would degenerate the
	 * PM's view of the world, we will subtract the purgeable blocks within the Straddle Block in the 
	 * system heap here now.
	 *
	 * The other option is to have the process manager heap GZProc purge blocks from the system heap,
	 * but this is not very family oriented (i.e. very incestuous).  Oh, and the reason for all this
	 * is for TempNewHandle trying to allocate everything we tell it is available, which would just
	 * make the system re-load everything that we purged out.
	 */
	straddleBlockSize -= GetSystemHiPurgeBytes();
	
	/*
	 *	Subtract off a block header to convert to logical size. We also subtract off an 
	 *	additional blockHeader as slop so (TempNewHandle(TempMaxMem)) will work will work
	 *	correctly.
	 */
	headerBytes = AlignUp(2*(kBlockHeaderSize + kMagicSize));
	if (straddleBlockSize > headerBytes)
		straddleBlockSize -= headerBytes;
	else
		straddleBlockSize = 0;
		
	/* Result is the larger of the two regions. */
	return((straddleBlockSize > hiMaxBlock) ? straddleBlockSize : hiMaxBlock);
	}


/* GetProcessMgrLoFreeBytes.  Find out how many free or purgeable bytes there are below
 * the lowest immovable block in the Process Mgr heap.  Size returned is physical byte
 * count.  As a side benefit, this routine also tells the caller whether the specified
 * handle was encountered in this low range.  Finding the block implies that freeing or
 * shrinking it would donate free space area of the Process Mgr heap into which the
 * system heap can grow. The routine returns a physical block size.
 *
 * Note: this routine aquires the pm heap from the System Heap Header
 */
Size
c_GetProcessMgrLoFreeBytes(Handle handleOfInterest, Boolean *sawInterestingBlock)
	{
	stdHeap*		pmHeap = LMGetSysZone()->nextUp;
	stdBlock*		workBlock;
	stdBlock*		blockOfInterest;
	blockSize_t		loFreeBytes;
	blockSize_t		workBlockSize;

	/* Convert Handle to physical block address.  This works fine even if the handle
	 * has been purged (physical address will not be found in the loop), but of course
	 * we are never called with a purged handle, anyway.
	 */
	if (handleOfInterest != nil)
		{
		blockOfInterest = (stdBlock*) GetBlockHeaderFromPtr(*handleOfInterest);
		*sawInterestingBlock = false;
		}
	else
		blockOfInterest = nil;

	/* Skip dummy block */
	workBlock = pmHeap->heapStart;
	workBlock = GetNextBlock(workBlock);
	loFreeBytes = 0;

	/* Walk the heap. Use infinite for loop instead of while loop, since we are guaranteed
	 * to find at least one non-relocatable block (e.g. a master pointer block).
	 */
	do
		{
		workBlockSize = workBlock->size;

		/* Are we looking at the interesting block? */
		if (workBlock == blockOfInterest)
			*sawInterestingBlock = true;

		/* Count this block in if it is free or purgeable.  Else, stop walking. */
		if (IsFreeBlock(workBlock))
			loFreeBytes += workBlockSize;
		else if (IsHandleBlock(workBlock))
			{
			if (IsLockedHandle(workBlock))
				break;
			else if (IsPurgableHandle(workBlock))
				loFreeBytes += workBlockSize;
			}
		else
			break;

		workBlock = (stdBlock*) ((Ptr)workBlock + workBlockSize);
		}
	while (true);

	return loFreeBytes;
	}


/* GetSystemHiFreeBytes.  Find out how many free or purgeable bytes there are above
 * the highest fixed block in the system heap.  Size returned is physical block size.
 */
Size
c_GetSystemHiFreeBytes(void)
	{
	stdBlock*	workBlock = LMGetSysZone()->backLimit;
	blockSize_t	cumSpace = 0;		/* free and purgable space */
	
	do
		{
		
		workBlock = BACK(workBlock);
		
		if (workBlock->handleBit == 1)
			{
			if (workBlock->lockBit == 1)
				{
				return cumSpace;	/* locked handle, get out */
				}
			else if (workBlock->purgeBit == 1)
				{
				cumSpace += workBlock->size;
				}
			}
		else if (workBlock->ptrBit == 1)
			{
			return cumSpace;	/* block is a pointer, get out */
			}
		else
			{
			/* block is free */
			cumSpace += workBlock->size;
			}
		}
	while (true);
	}
	
	
/* GetSystemHiPurgeBytes.  Find out how many purgeable bytes there are above
 * the highest fixed block in the system heap.  Size returned is physical block size.
 */
Size
GetSystemHiPurgeBytes(void)
	{
	stdBlock*	workBlock = LMGetSysZone()->backLimit;
	blockSize_t	cumSpace = 0;		/* free and purgable space */
	
	do
		{
		
		workBlock = BACK(workBlock);
		
		if (workBlock->handleBit == 1)
			{
			if (workBlock->lockBit == 1)
				{
				return cumSpace;	/* locked handle, get out */
				}
			else if (workBlock->purgeBit == 1)
				{
				cumSpace += workBlock->size;
				}
			}
		else if (workBlock->ptrBit == 1)
			{
			return cumSpace;	/* block is a pointer, get out */
			}
		}
	while (true);
	}

