/*
	File:		MemMgrHeap.c

	Contains:	Memory Manager Heap Management Routines

	Written by:	Jeff Crawford

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<37>	10/15/93	BT		Well, the last change doesn't work.  We need to know when the
									subheap is a subheap of the PM heap and Knott set it in that
									case.
		<36>	10/14/93	BT		<BT, ewa> Radar 1117552; Change interfaces around. Radar
									1114117; fix MoveHHi.
		<35>	  9/2/93	BT		#1110427, add tag checking for heaps. This is a precautionary
									measure, as bus error handlers are proven most effective with a
									quick tag check.  I am checking this in now so Eric can review
									it for later.
		<34>	 8/19/93	BT		<BT, cam> Add "#ifdef hasFirstLevelFakeHandleTests" around
									remaining range checks.  This defined in MemMgr.h unless
									"cancelFigmentRangeChecking" is set true.
		<33>	 8/17/93	JC		Made a meaningless change to support client debug mode.
		<32>	  8/5/93	BT		<BT, JC> We came, we saw, we initialed...
		<31>	  8/4/93	JC		Fix bug with <29>. Was not walking the heap during CreateNewHeap
									in some situations.
		<30>	  8/2/93	JC		#1095953, now is FakeHandleRange instead of RealMemTop to permit
									clients to create heaps above RealMemTop
		<29>	 7/29/93	JC		#1101544,  Changed substantial portions of IsValidBlockInHeap,
									FindBlockInHeap, CreateNewHeap, and RemoveHeap to support OCE.
									They call InitZone 4 bytes into a memory block.
		<28>	 7/28/93	BT		<BT, JRG> Radar 1096298, 1102433. Finish QT
									HandleTrashNotification code. The Component Manager wasn't
									getting notified that memory was going away and would call dead
									space.
		<27>	 6/28/93	JC		Fixed the fSkipPurgeBeforeGZ bit to not be set until ProcessMgr
									launch time. This fixes the problem where some inits
									(WorldScript) would require blocks to be purged in the System
									Heap during the boot process.
		<26>	 6/16/93	JC		Added universal low memory getters and setters.
		<25>	 6/10/93	JC		Removed extra parameter to CreateNewHeap.
		<24>	  6/8/93	JC		Added debug check for duplicate heap added to heap tree.
		<23>	  6/4/93	JC		Removed HeapIDs from non debug version.
		<22>	 5/24/93	JC		Changed XXX to DbgXXX for all debug routines.
		<21>	 5/19/93	JC		Began changes as requested by the code review. Removed options
									parameter from AllocateMoreMasters.
		<20>	 5/18/93	JC		Fixed the “zero k available” bug. Yippee! This fix requires a
									new ProcessMgr to work completely.
		<19>	  5/2/93	JC		removed heapName field. Also added compatiblity flags word in
									the heap header.
		<18>	 4/23/93	JC		Fixed Jeff's heap tree prob when quitting apps that have a
									scrap.
		<17>	 4/21/93	JC		Fixed AfterDark problem where they dispose first Ptr in the
									heap. We fix this by setting the back ptr of the first block in
									the heap to point to the spoof block.
		<16>	 4/20/93	JC		Added ability to remove heaps from the heap tree when thier
									memory is being disposed. This should fix AfterDark and some MPW
									tools.
		<15>	 4/18/93	JC		Changed #defines to more acurate descriptions. Changed
									small_block_headers to small_freeBlock_headers and linkedIn to
									linked_thinkc_app.   •• Brian & Sam take note.••
		<14>	 4/18/93	JC		Fixed bug in CreateNewHeap. Previously all heaps were scanned
									from firstFree instead of favoredFree. Now, only the system heap
									is scanned from firstFree.
	   <12+>	 4/16/93	JC		Cleanup for Code Review
		 <1>	 6/10/92	JC		New Today

*/

#ifndef THINK_C
	#ifdef StarTrek
		#include <MacTypes.h>
		#include <MacMem.h>
		#include <Events.h>
	#else
		#include <Types.h>
		#include <Memory.h>
		#include <Events.h>
	#endif
#endif

#ifdef StarTrek
	#include "MemDebug.h"
	#include "MemMgr.h"
	#include "MemRout.h"
#else
	#include "MemMgrDebug.h"
	#include "MemMgr.h"
	#include "MemoryRoutines.h"
#endif

#include "QTMemory.h"

#ifdef patchedIn
	/* This will overcome the 32k limit */
	#pragma segment Figment
#endif

#ifdef THINK_C
	/* This will overcome the 32k limit */
	#pragma segment Figment
#endif


/* This routine walks the heap tree to find the heap that contains the address. Note:
	this routine must be revised to support discontiguous heaps. If no heap found
	it returns nil. */
stdHeap* FindHeap(const void* address)
{
#ifdef patchedIn
	#pragma unused(newHeap)	
	#pragma unused(address)	
	return GetCurrentHeap();
#else
	stdHeap*	testHeap = LMGetSysZone();
	stdHeap*	parentHeap = nil;

	while (testHeap)
		{
		IfDbgMsg((void*)testHeap->backLimit <= testHeap->heapStart, "heap list is invalid", testHeap);

		/* Did we find the heap? */
		if (testHeap == address)
			{
			/* direct hit, lets bail */
			parentHeap = testHeap;
			break;
			}
		
		/* Is the heap address contained inside this heap? */
		if ((void*)testHeap->backLimit >= address  &&  address >= testHeap->heapStart)
			{
			parentHeap = testHeap;
			testHeap = testHeap->nextIn;
			continue;
			}
			
		/* advance to next heap */
		testHeap = testHeap->nextUp;
		}
	return parentHeap;
#endif /* patchedIn */
}


/* Adds a heap to the heap tree. Returns the parent heap. */
static stdHeap* AddHeapToHeapTree(stdHeap* newHeap);
static stdHeap* AddHeapToHeapTree(stdHeap* newHeap)
	{	
#ifdef patchedIn
	#pragma unused(newHeap)	
#else
	stdHeap*	testHeap = LMGetSysZone();
	stdHeap*	parentHeap = nil;				/* testHeap's parent */
	stdHeap*	priorHeap = nil;				/* previous heap, trails test heap */

	while (testHeap)
		{
		IfIntDebugMsg(testHeap == newHeap,"heap already in heap tree",testHeap);
		
		if ((char*)testHeap->heapStart > (char*)newHeap)
			break;
			
		if ((char*)testHeap->backLimit > (char*)newHeap)
			{
			parentHeap = testHeap;
			testHeap = testHeap->nextIn;
			priorHeap = nil;
			continue;
			}
			
		priorHeap = testHeap;
		testHeap = testHeap->nextUp;
		}
		
	DbgCode(if (parentHeap) parentHeap->subHeaps++);
	
	if (priorHeap)
		priorHeap->nextUp = newHeap;
	else
		{
		if (parentHeap)
			parentHeap->nextIn = newHeap; /* first sub heap */
		else
			LMSetSysZone(newHeap);		/* first heap in memory order */
		}
		
	if (testHeap)
		newHeap->nextUp = testHeap;
		
	return parentHeap;
#endif /* patchedIn */
	}


/*
 *	Finds a block in the given heap that contains the address. Returns a pointer to the blocks 
 *	header or nil. Since its faster to walk down than up, we walk down.
 *
 *	Assumption, the block we are looking for is not the last block in the heap (trailer block).
 */
stdBlock* FindBlockInHeap(const void* theAddress, stdHeap* curHeap)
	{
	stdBlock*	address = (stdBlock*) theAddress;
	stdBlock*	workBlock;

	/* set up initial conditions */
	workBlock = curHeap->backLimit->back;

	IfIntDebugMsg(address == nil,"address = nil", nil);
	IfIntDebugMsg(address < (stdBlock*)curHeap->heapStart || address > workBlock, "address not in heap range", address);
	
	do
		{
		/* is the address contained in workBlock */
		if (workBlock <= address)
			return workBlock;
		
		/* march pointer */
		workBlock = workBlock->back;	
		}
	while (workBlock);	/* loop until we reach the front of the heap */
	
	return nil;
	}
	
/*
 *	returns true if the block is a valid block in the given heap. This routines does
 *	not walk the heap.
 */
Boolean	IsValidBlockInHeap(stdBlock* blockHeader, stdHeap* curHeap)
	{
	Boolean result = false;		/* assume is not OK */

	/* is the a ptr block? */
	if (((stdBlock2*)blockHeader)->tags == (uchar)ptrType)
			{
			/* double check heap reference */
			if (blockHeader->parent == curHeap)
				{
				/* we have a match */
				result = true;
				}
			}
	/* is this a locked handle? */
	else if ((((stdBlock2*)blockHeader)->tags == (uchar)relocatableType) && IsLockedHandle(blockHeader))
		{
		/* need to verify relative handle, get MP */
		Ptr*	masterPointer;
		
		/* get mp from heap and RelHandle */
		masterPointer = (Ptr*)((Ptr)curHeap + (((handleBlock*)blockHeader)->relHandle));

	#ifdef hasFirstLevelFakeHandleTests
		/* do a range check to validate the mp, is it ok? */
		if (masterPointer < (Ptr*)LMGetFakeHandleRange())
			{
			/* yes, deref mp to see if it points to data */
			if (*masterPointer == (Ptr)(blockHeader->data))
				{
				/* we have a match */
				result = true;
				}
			}
	#else
		if (*masterPointer == (Ptr)(blockHeader->data))
			{
			/* we have a match */
			result = true;
			}
	#endif
		}
		
	return result;
	}


stdHeap* CreateNewHeap(GrowZoneProcPtr pgrowZone, short numMasters, Ptr limit, Ptr start)
{
#pragma unused(parentHeap)
	stdHeap*		heapPtr = (stdHeap*)start;
	blockSize_t		heapSize;
	freeBlock*		firstRealBlock;
	stdBlock*		trailBlock;

	/*
	 *	There is the possibility that a client may want quadlongword aligned heaps, but
	 *	did not pass a pointer that was quadlongword aligned. In this case, the heap
	 *	header will not be quadlongword aligned, but all blocks in the heap will be
	 *	(quad)longword aligned.
	 */
	firstRealBlock = (freeBlock*) AlignUp((Ptr)heapPtr + sizeof(stdHeap));	

	/* (quad)longword align the trailer block */
	trailBlock = (stdBlock*) AlignDown(limit - kTrailerBlockSize);

	IfClientDebugMsg((Ptr)trailBlock - (Ptr)firstRealBlock < 2 * kMinBlockSize, "heap too small", limit-start);
		
	/* Subtract off space occupied by the header and trailer */
	heapSize = (Ptr)trailBlock - (Ptr)firstRealBlock;

	/* clear out heap header and the block header of the next free block */
	FillBytes(heapPtr, (Ptr)firstRealBlock - (Ptr)heapPtr + kFreeBlockHeaderSize, 0);

	/* fill in data structures for freeblock and trailerblock */
	/* note: this is done by FillBytes */
	/* firstRealBlock->sizeDelta = 0; */
	
	firstRealBlock->back = nil;
	firstRealBlock->prevFree = DummyFree(heapPtr);
	firstRealBlock->nextFree = DummyFree(heapPtr);

	/* Danger Will Robinson, heap validation flags may not have been set */
	DbgGarbageFill(heapPtr, firstRealBlock->data, heapSize - kFreeBlockHeaderSize);

	heapPtr->heapStart = firstRealBlock;
	heapPtr->firstFree = firstRealBlock;
	heapPtr->lastFree = firstRealBlock;
	heapPtr->favoredFree = firstRealBlock;
	heapPtr->lowestRemovableBlock = firstRealBlock;
	heapPtr->gzProc = pgrowZone;
	heapPtr->heapType = heapDouJour;
	
	#ifdef debugging
		heapPtr->heapID = TickCount();			/* use lower char as heap ID */
	#endif

	/* Jam the stuff for the "spoof" block into the heap zone header */
	{
		spoofBlockStruct* spoofPtr = &(heapPtr->spoofBlock);	/* pointer to spoof block */
	
		/*
		 *	We use this size to "spoof" heap walkers like Macsbug so they walk the heap 
		 *	correctly. They usually start at 52 bytes into the heap and expect the old 32 bit
		 *	block header structure of the first block. From there heap walkers will fish out
		 *	the size of each block to advance to the next block.
		 *
		 *	we want &heapPtr->spoofBlock + spoofBlock.size to point to first REAL block for heapwalkers
		 */
		spoofPtr->parent = heapPtr;
		spoofPtr->size = kBackPtrSize + (ulong)firstRealBlock - (ulong)spoofPtr;
		spoofPtr->tagsFlagsSizeDelta = (ulong)ptrType << 24;	/* set ptr bit */

		/*
		 *	reset the back link to be the spoof pointer so clients (AfterDark) can 
		 *	dispose of the first block in the heap. 
		 */
		firstRealBlock->back = (void*)((Ptr)spoofPtr - kBackPtrSize);
	}
	
	/* note: since we filled the heap header with zeros, all other fields are zero */
	
	#if ForROM
	if (LMGetSysZone() == (stdHeap*)(-1))		/* are we initializing the system zone? */
	#else
	if (heapPtr == LMGetSysZone())				/* are we initializing the system zone? */
	#endif
		{
		/* We are initializing the SystemZone */
		
		/*
		 *	Start searches at first free, sans favored free. This allows us to allocate 
		 *	blocks as low in the System heap as possible to prevent blocks from being 
		 *	locked up high. This will allow the sys/pm heap boundary to float.
		 */
		heapPtr->fUseFirstFree = 1;		
		}
	else
		{
		/* system zone initialized, add heap to the chain */
		stdBlock*	theBlock;		/* a "potential" block that contains the heap */
		stdHeap*	daddyHeap;		/* the new heaps parent */

		/*
		 *	Note: Some 3rd party software like AfterDark create heaps outside thier application
		 *	partitions. Others like MPW create heaps and dispose of them. Since there is no
		 *	"DisposeZone" API, we need to track when heaps in memory are being disposed.
		 *	So when a heap is created, it is in a valid MM block, then we mark the block
		 *	using the subheap bit. Later when the block is disposed, we will remove
		 *	the heap from the heap tree.
		 */

		/* maintain heap tree, get daddy heap, did we find our daddy? */
		/* if we are in a subheap, do some things, something like that. */
		if (daddyHeap = AddHeapToHeapTree(heapPtr))
			{
			/* we found dad, make him pay child support */
			
			/* if this heap is contained in a memory mgr block, we need to mark it's subheap bit */
			theBlock = (stdBlock*)((Ptr)heapPtr - kBlockHeaderSize);	/* get potential block ptr */
			
			/* perform a simple heap size check to see if it's a valid block */
			if ( (theBlock->size - kBlockHeaderSize >= ((Ptr)limit - (Ptr)start)) &&
				 (IsValidBlockInHeap(theBlock, daddyHeap)) )
				{
				theBlock->subHeapBit = 1;	/* this block contains a subheap */
				}
			else
				{
				/*
				 *	Since we could not find the valid block that contained the heap, we have to
				 *	walk blocks in daddyHeap until we find the block that contains the subheap.
				 */
				if (theBlock = FindBlockInHeap(heapPtr, daddyHeap))
					{
					if (IsValidBlockInHeap(theBlock, daddyHeap))
						{
						theBlock->subHeapBit = 1;	/* this block contains a subheap */
						}
					}
				}
			}
		
		#ifdef client_debugging
			/*
			 *	We set up the heap to write garbage data when block are disposed.
			 *	We do this to catch clients executing or reading out of disposed blocks. 
			 *	Note: We don't do this during the boot process since many   
			 *	INITs and other software entities read and execute out of free blocks.
			 *
			 *	Have we already initialized the ProcessMgrZone?
			 */
			
			#if 0
				This is commented out since it makes client debug mode to slow
				if ((LMGetSysZone()->nextUp) && (IsProcessMgrHeap(LMGetSysZone()->nextUp)))
					{
					/* yes, then we set this heap to fill free blocks on dispose calls */
					heapPtr->validationFlags |= fillFreeBlocks;
					}
			#endif
		#endif
		}

	/* note: heapPtr->heapFlags = 0 => start searches at favoredFree */
	heapPtr->totalFree = heapSize;		/* remaining bytes are owned by a free block */
	firstRealBlock->size = heapSize;
	heapPtr->purgePtr = heapPtr->backLimit = trailBlock;

	/*
	 *	When clients like QuickMail walk the heap, they generally stop walking when the block
	 *	they are walking equals oldBackLimit. We use a second spoof block and oldBackLimit to 
	 *	trick clients into thinking they have reached the end of the heap.
	 */
	{
		spoofBlockStruct* trailSpoofBlock;			/* spoof block trailer */

		trailSpoofBlock = (spoofBlockStruct*)(kTrailerSpoofOffset + (Ptr)trailBlock);		
		heapPtr->oldBackLimit = trailSpoofBlock;	/* set up the old back limit to point to 16 bytes after backLimit */
		
		trailSpoofBlock->size = kOldTrailerSize;
		trailSpoofBlock->tagsFlagsSizeDelta = 0;	/* aw, just stuff nothing so there's nothing bizarre there */
	}

	MarkBlockAsPrivate(trailBlock, trailerBlockType, heapPtr);
	/* jeff, need to fix size delta */
	/* note: size delta for trailer does not include kMagicSize or kBackPtrSize */
	trailBlock->back = firstRealBlock;
	trailBlock->size = 12;						/* offset to spoof trailer */
	((stdHeap2*)heapPtr)->MPCount = numMasters;
#ifdef debugging
	/* alert the world we have debugging information in this header */
	heapPtr->freeBlocks = 1;
	DbgCheckHeap(heapPtr);
#endif
	return heapPtr;
}


/*
 *	Moves the zone header high in the heap so the lower limit can be flexible. It
 *	assumes there is a zone header, a free block, and a zone trailer only. This
 *	on the ProcessMgr zone only. Clients must remember to change APPLZONE and 
 *	any other globals that depend on this heap.  As a side effect, if the first
 *	block in the zone is a master pointer block, it is deleted.
 *
 *	warning: clients must remember to set TheZone, ApplZone & pNullProcess->p_zone.
 */
stdHeap* MoveHeapHeaderHigh(stdHeap* oldHeap)
	{
	stdHeap*			newHeap;
	ptrBlock*			newTrailer;
	freeBlock*			newFree;
	spoofBlockStruct*	trailSpoofBlock;
	
	/* get new heap start */
	newHeap = (stdHeap*) ((Ptr)oldHeap->backLimit + oldHeap->backLimit->size - sizeof(stdHeap));

	IfIntDebugMsg((Ptr)oldHeap + sizeof(oldHeap) > (Ptr)newHeap,"heap overlap", newHeap);

	/* copy important information */
	BlockMove((Ptr)oldHeap, (Ptr)newHeap, sizeof(stdHeap));

	/* get new heap trailer, new free block */
	newTrailer = (ptrBlock*) (AlignDown((Ptr)newHeap - kTrailerBlockSize));	
	newFree = (freeBlock*) AlignUp(oldHeap);

	/* initialize free block and heap trailer block */
	newTrailer->size = kOldHeaderSize;		/* offset to spoof trailer */

	MarkBlockAsPrivate(newTrailer, trailerBlockType, newHeap);
	newTrailer->back = newFree;
	newFree->back = 0;
	newFree->prevFree = DummyFree(newHeap);
	newFree->nextFree = DummyFree(newHeap);
	newFree->size = (Ptr) newTrailer - (Ptr) newFree;
	
	#ifndef small_freeBlock_headers
		/* set tags=0, mpFlags=0, heapID=0, sizeDelta=0 */
		((stdBlock3*)newFree)->tagsFlagsSizeDelta = 0;	
	#endif
	
	/* finish adding new heap information */
	newHeap->heapStart = newFree;
	newHeap->firstFree = newFree;
	newHeap->lastFree = newFree;
	newHeap->favoredFree = newFree;
	newHeap->lowestRemovableBlock = newFree;
	newHeap->purgePtr = (stdBlock*)newFree;
	newHeap->totalFree = newFree->size;
	newHeap->backLimit = newTrailer;
	
	/* create the spoof trailer block to be after the new trailer */
	trailSpoofBlock = (spoofBlockStruct*)(kTrailerSpoofOffset + (Ptr)newTrailer);
	trailSpoofBlock->size = kOldTrailerSize;
	trailSpoofBlock->tagsFlagsSizeDelta = 0;	/* just like the old MM */

	/* set up the old back limit to point to 16 bytes after backLimit */
	newHeap->oldBackLimit = trailSpoofBlock;
	
	/* we want &newHeap->spoofBlock + spoofBlock.size to point to first REAL block for heapwalkers */
	(newHeap->spoofBlock).size = kBackPtrSize + (ulong)newFree - (ulong)&newHeap->spoofBlock;

	newHeap->firstFreeMP = 0;
	#ifdef implemented_discontiguous_heaps
		newHeap->fragmentPtr = 0;
	#endif
	newHeap->disposeProc = 0;
	
	LMSetTheZone(newHeap);
	
	#ifdef debugging
		/*
		 *	clear all dubugging fields except the validation flags. Validation
		 *	flags are already copied over from the oldHeap header.
		 */
		FillBytes(&newHeap->freeBlocks, sizeof(stdHeap) - offsetField(stdHeap, freeBlocks), 0);	
	
		newHeap->freeBlocks = 1;
		DbgCheckHeap(newHeap);
	#endif /* debugging */
	
	return newHeap;
	}


/*
 *	Removes a heap from the heap tree. Note: on entry, doomedHeap must point
 *	to a valid heap. Note2: Does not dispose of any memory.
 */
void RemoveHeap(Ptr rangeStart, Ptr rangeEnd) 
	{
#ifdef patchedIn
	#pragma unused(doomedHeap);
#else
	stdHeap*	testHeap = LMGetSysZone();
	stdHeap*	parentHeap = nil;				/* testHeap's parent */
	stdHeap*	priorHeap = nil;				/* previous heap, trails test heap */

	/* search for heap, set up testHeap and prior heap along the way */
	while (testHeap)
		{
		/* does the range completely contain testHeap? */
		if ((rangeStart <= (Ptr)testHeap->heapStart) && (rangeEnd >= (Ptr)testHeap->backLimit))
			{
			/* we have a match */
			break;
			}
		else
			{
			/* no match, is there overlap? */
			if (rangeStart > (Ptr)testHeap->backLimit)
				{
				/* no, move on to the next heap (if it exists) */
				priorHeap = testHeap;
				testHeap = testHeap->nextUp;
				}
			else
				{
				/* yes, move into a sub heap (if it exists) */
				parentHeap = testHeap;
				priorHeap = nil;
				testHeap = testHeap->nextIn;
				}
			}

		}
	
	IfIntDebugMsg(testHeap == nil,"could not find heap in heap tree",testHeap);
	
	if (testHeap)
		{
		/* we found a heap, need to remove it from the heap tree */
		
		#ifndef linked_thinkc_app
			/* alert QuickTime clients that a heap is going away */
			TrashMemoryArea(testHeap->heapStart, (Ptr)testHeap->backLimit);
		#endif

		/* remove this heap from the heap list */
		if (priorHeap)
			priorHeap->nextUp = testHeap->nextUp;
		else
			{
			parentHeap->nextIn = testHeap->nextUp;	/* first sub heap */
			}
		}
#endif /* patchedIn */
	}
	

void GrowHeap(void *newMemory, blockSize_t size)
{
#pragma unused(newMemory)
#pragma unused(size)
}


Boolean ShrinkHeap(void *oldMemory, blockSize_t size)
{
#pragma unused(oldMemory)
#pragma unused(size)
	/*** move any existing blocks out of the area to be shrunk */
	/* This is not trivial */
	return false;
	
}
