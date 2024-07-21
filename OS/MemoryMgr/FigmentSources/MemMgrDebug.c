/*
	File:		MemMgrDebug.c

	Contains:	Memory Manager Debugging Routines

	Written by:	Jeff Crawford

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<27>	  8/5/93	BT		<BT, JC> We came, we saw, we initialed...
		<26>	 7/27/93	JC		<mlw> Removed kWorstCaseBlockOverhead.
		<25>	 6/30/93	JC		#1089109: Removed fHeapIsDirty bit.
		<24>	 6/25/93	BT		(Really JC with BT) Commented out extra call to
									_ValidateHeapIsClean inside of CheckHeap.
		<23>	 6/16/93	JC		Added universal low memory getters and setters.
		<22>	 6/10/93	JC		Added heap is dirty bit support.
		<21>	  6/3/93	JC		Modified checking routines to respect the new meaning of the
									HeapIsDirty flag.
		<20>	 5/24/93	JC		Changed XXX to DbgXXX for all debug routines.  Added extra
									check.
		<19>	 5/19/93	JC		Began changes as requested by the code review. Removed options
									parameter from AllocateMoreMasters.
		<18>	  5/2/93	JC		Use compatibility flags, change odd free MP strategy.
		<17>	 4/26/93	JC		Add Comment
		<16>	 4/23/93	JC		Fixed _FreeBlockCheck to check for a valid free block size.
		<15>	 4/21/93	JC		Fixed _MasterPointer to check to skip the ROZ.
		<14>	 4/20/93	JC		Added ability to remove heaps from the heap tree when thier
									memory is being disposed. This should fix AfterDark and some MPW
									tools.
		<13>	 4/19/93	JC		Changed CheckSize & CheckAlignment to be debug routines instead
									of macros.
		<12>	 4/18/93	JC		Changed #defines to more acurate descriptions. Changed
									small_block_headers to small_freeBlock_headers and linkedIn to
									linked_thinkc_app.   ¥¥ Brian & Sam take note.¥¥
		 <1>	 6/10/92	JC		New Today

*/

#ifndef THINK_C
	#ifdef StarTrek
		#include <MacTypes.h>
		#include <MacMem.h>
	#else
		#include <Types.h>
		#include <Memory.h>
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

#ifdef debugging		/* from here to #endif is undented*/

#ifdef patchedIn
	/* This will overcome the 32k limit */
	#pragma segment Figment
#endif

#ifdef THINK_C
	/* This will overcome the 32k limit */
	#pragma segment DebugFigment
#endif


void DbgCheckSize(ulong theSize)
	{
	#ifdef small_freeBlock_headers
		IfDbgMsg(theSize & (kAlignmentFactor-1), "misaligned size", theSize);
		//IfDbgMsg(theSize & 0xC0000000, "size too large", theSize);
	#else
		IfDbgMsg(theSize & (kAlignmentFactor-1), "misaligned size", theSize);
	#endif
	}
	
void DbgCheckAlignment(void* thePtr)
	{
	#ifdef small_freeBlock_headers
		IfDbgMsg((ulong)thePtr & (kAlignmentFactor-1), "misaligned ptr", thePtr);

		/* should not have any block ptr with the 2 high bits set */
		IfDbgMsg((ulong)thePtr & 0xC0000000, "ptr too large", thePtr);
	#else
		IfDbgMsg((ulong)thePtr & (kAlignmentFactor-1), "misaligned ptr", thePtr);
	#endif
	}




static void CopyBytes(const void* source, void* dest, long length);
static void CopyBytes(const void* source, void* dest, long length)
{
	char *src = (char*) source;
	char *dst = (char*) dest;

	while (--length >= 0)
		*dst++ = *src++;
}


void DbgMessage(const char *str, long data)
{
	char*	s = (char *)str;
	char	dataStr[256];
	long	count = 7, length;

	while (*s++); /* find end of c string */
	length = s - str;
	dataStr[0] = length + 9;
	CopyBytes(str, &dataStr[1], length);
	s = &dataStr[length];
	*s++ = ' ';
	*s++ = ' ';
	do {
		char c = (data >> (count << 2) & 0x0f) + '0';
		if( c > '9' )
			c += 'a' - '9' - 1;
		*s++ = c;
	} while (--count >= 0);
	DebugStr((void *) dataStr);
}


void _PtrBlockCheck(void* block, stdHeap* curHeap)
{
	ptrBlock *blockHeader;

	IfDbgMsg(curHeap == nil, "nil heap", curHeap);
	IfDbgMsg(block == nil, "nil block", curHeap);
	blockHeader = (ptrBlock *) GetBlockHeaderFromPtr(block);;
	IfDbgMsg(!IsPtrBlock(blockHeader),"not a pointer block", blockHeader);
	IfDbgMsg(FindHeap(blockHeader) != curHeap, "Ptr block not in heap", block);
	IfDbgMsg(IsHandleBlock(blockHeader),"bad ptr block header", blockHeader);
	IfDbgMsg(blockHeader->sizeDelta > kMinFreeSplitSize + kAlignmentFactor + kMinDelta - 1, "delta too large", blockHeader->sizeDelta);
	IfDbgMsg(blockHeader->size < 0 || (char *) blockHeader + blockHeader->size >
		(char *) curHeap->backLimit, "bad dir block size", blockHeader->size);
		/* jeff, check the second part of the below test, remove it? */
	if ((!IsPrivateBlock(blockHeader)) && (blockHeader->size > kBlockHeaderSize))
		CheckMagic(block, blockHeader->size - blockHeader->sizeDelta - kPsuedoBlockSize);
	IfDbgMsg(blockHeader->heapID != curHeap->heapID, "heapIDs dont match", blockHeader);
		
	if (BACK(blockHeader) != nil)
		{
		/* check back pointer */
		ptrBlock*	prevBlock = BACK(blockHeader);
		IfDbgMsg( (char*)blockHeader != (char*)prevBlock + prevBlock->size, 
			"back pointer is set incorrectly", block);
		}
}


static Boolean IsMasterPointer(void* mpAddr, stdHeap* curHeap);
static Boolean IsMasterPointer(void* mpAddr, stdHeap* curHeap)
{
	handleBlock*	blockHeader = (handleBlock*)GetBlockHeaderFromPtr(*((void**)mpAddr));
	if ((void*) (blockHeader->relHandle + (long)curHeap) == mpAddr)
		return true;
	else
		return false;
}


void _HandleBlockCheck(void* block, stdHeap* curHeap)
{
	handleBlock*	blockHeader;
	Handle			masterPtr;

	IfDbgMsg(curHeap == nil, "nil heap", curHeap);
	IfDbgMsg(block == nil, "nil block", curHeap);
	blockHeader = (handleBlock*) GetBlockHeaderFromPtr(block);
	
	/* we do simple check to make sure were in the right ballpark */
	IfDbgMsg((block < curHeap->heapStart) || (block > (void*)curHeap->backLimit),"master pointer does not point inside heap",block);

	IfDbgMsg(FindHeap(blockHeader) != curHeap, "handle block not in heap", block);
	/* This line is commented out since the heap may be in transition (Jump Relocating) */
	/* IfDbgMsg(IsPtrBlock(blockHeader),"bad relocatable block header", blockHeader); */
	IfDbgMsg(blockHeader->sizeDelta > kMinFreeSplitSize + kAlignmentFactor + kMinDelta - 1, "delta too large", blockHeader->sizeDelta);
	IfDbgMsg((char*)blockHeader + blockHeader->size > (char*) curHeap->backLimit, "bad handle block size", blockHeader->size);

	/* jeff make this more stringent */
	IfDbgMsg(blockHeader->size < kBlockHeaderSize, "bad handle block size", blockHeader->size);
	CheckMagic(block, blockHeader->size - blockHeader->sizeDelta - kPsuedoBlockSize);
	masterPtr = (Handle) (blockHeader->relHandle + (long) curHeap);
	IfDbgMsg(FindHeap(masterPtr) != curHeap, "handle block master ptr not in heap", masterPtr);

	/* skip next test if a temporary block block (jump relocating) */
	if (!IsPtrBlock(blockHeader))
		{
		IfDbgMsg(IsMasterPointer(masterPtr, curHeap) == false, "relative handle does not point to handle", masterPtr);
		IfDbgMsg(*masterPtr != block, "handle block master ptr doesnÕt point to block", masterPtr);
		}
	IfDbgMsg(blockHeader->heapID != curHeap->heapID, "heapIDs dont match", blockHeader);
	
	if (BACK(blockHeader) != nil)
		{
		/* check back pointer */
		stdBlock*	prevBlock = BACK(blockHeader);
		IfDbgMsg( (char*)blockHeader != (char*)prevBlock + prevBlock->size, 
			"back pointer is set incorrectly", block);
		}
}


static void _FreeBlockCheck(freeBlock* blockHeader, stdHeap* curHeap);
static void _FreeBlockCheck(freeBlock* blockHeader, stdHeap* curHeap)
	{
	freeBlock*	spare;
	
	IfDbgMsg((char*)blockHeader + blockHeader->size > (char*) curHeap->backLimit, "bad free block size", blockHeader->size);
	IfDbgMsg(blockHeader->size < kMinFreeBlockSize, "bad free block size", blockHeader->size);
	#ifndef small_freeBlock_headers
	IfDbgMsg(((stdBlock2*)blockHeader)->sizeDelta != 0,"bad free size delta", blockHeader);
	IfDbgMsg(((stdBlock2*)blockHeader)->heapID != 0,"bad heapID", blockHeader);
	IfDbgMsg(((stdBlock2*)blockHeader)->tags != 0,"tags are not 0", blockHeader);
	IfDbgMsg(((stdBlock2*)blockHeader)->mpFlags != 0,"mpFlags are not 0", blockHeader);
	#endif
	if (spare = blockHeader->prevFree)
		{
		IfDbgMsg(spare->nextFree != blockHeader,"bad free chain", blockHeader);
		IfDbgMsg (spare >= blockHeader && spare != DummyFree(curHeap),"bad free chain", blockHeader);
		}
	else
		{
		DbgMessage("nil prevFree pointer", (long)blockHeader);
		}
	
	if (spare = blockHeader->nextFree)
		{
		IfDbgMsg(spare->prevFree != blockHeader,"bad free chain", blockHeader);
		IfDbgMsg (spare <= blockHeader && spare != DummyFree(curHeap),"bad free chain", blockHeader);
		}
	else
		DbgMessage("nil nextFree pointer", (long) blockHeader);

	if (BACK(blockHeader) != nil)
		{
		/* check back pointer */
		stdBlock*	prevBlock = BACK(blockHeader);
		
		IfDbgMsg( (char*)blockHeader != (char*)prevBlock + prevBlock->size, 
			"back pointer is set incorrectly",  blockHeader);
		}
	else
		IfDbgMsg((void*)blockHeader != curHeap->heapStart,"free block back ptr is nil", (long) blockHeader);
		
	}


void _MasterPtrCheck(void* mp, stdHeap* curHeap)
{
	IfDbgMsg(curHeap == nil, "nil heap",  curHeap);
	IfDbgMsg(mp == nil, "nil mp", 0);
	
	/* blocks in the ROZ will fail these checks */
	if (!IsReadOnlyZone(curHeap))
		{
		/* we do simple check to make sure were in the right ballpark */
		IfDbgMsg((mp < curHeap->heapStart) || (mp > (void*)curHeap->backLimit),"master pointer not in heap",mp);
		
		IfDbgMsg(FindHeap(mp) != curHeap, "master ptr not in heap", mp);
		IfDbgMsg(IsMasterPointer(mp, curHeap) == false, "master ptr not in master ptr block", mp);
		_HandleBlockCheck(*(void **) mp, curHeap);
		}
}


static void SimulateHeapScramble(stdHeap *curHeap);
static void SimulateHeapScramble(stdHeap *curHeap)
{
	if (curHeap->validationFlags & scrambleBlocks)
		{
		/* needs to be implemented, jeff */
		}
}


#define IS_HANDLE_IN_ZONE(theHdl, heap) (((Ptr)(theHdl) > (Ptr)(heap->heapStart)) && ((Ptr)(theHdl) < (Ptr)(heap)->backLimit))

/* Check that all (free) MPs in this zone fall within this zone */
static void CheckZoneForBadFreeMPs(stdHeap* curHeap);
static void CheckZoneForBadFreeMPs(stdHeap* curHeap)
	{
	Ptr*	pMP;
	
	for (pMP = curHeap->firstFreeMP; pMP  != nil; pMP = UnmaskMPBit(*pMP))
		{
		if (!(IS_HANDLE_IN_ZONE(pMP, curHeap)))
			{
			IfDbgMsg(true, "Bad free MP list in given zone", *pMP);
			}
		}
	}


void _CheckHeap(stdHeap* curHeap)
	{
	if(curHeap->validationFlags & checkHeap)
		{
		long			freeBlocks = 0;
		long			ptrBlocks = 0;
		long			handleBlocks = 0;
		ptrBlock*		workBlock = curHeap->heapStart;
		stdBlock*		lastBlock = curHeap->backLimit;
		freeBlock*		largestFreeBlock = curHeap->firstFree;
		blockSize_t		totalFree = 0;
		blockSize_t		totalPurgable = 0;
		long			sizeDelta = 0;
		long			totalDelta = 0;
		long			usedMasterPtrs = 0;
		long			holes = 0;
		Boolean			foundFavored = false;
		Boolean			foundTrailer = false;
		Boolean			foundFreeBlock = false;
		Boolean			foundLastFree = false;
		Boolean			foundLowestRemovable = false;
		
		while ((char*)workBlock <= (char*)lastBlock)
			{
			IfDbgMsg(foundTrailer, "unexpected block after trailer", workBlock);
			if (IsHandleBlock(workBlock))
				{
				_HandleBlockCheck(workBlock->data, curHeap);
				handleBlocks++;
					
				if (!IsPtrBlock(workBlock) && IsUnlockedPurgableHandle(workBlock))
					{
					totalPurgable += workBlock->size;
					}
					
				/* check if foundLowestRemovable and the handle is not temp busy, and it is not
					locked. */
				if ((!foundLowestRemovable) && (!IsPtrBlock(workBlock)) && (!(IsLockedHandle(workBlock))))
					{
					foundLowestRemovable = true;
					IfDbgMsg((char*)workBlock != (char*)curHeap->lowestRemovableBlock,
						"LowestRemovableBlock is bad", workBlock);
					}
				}
			else if (IsPtrBlock(workBlock)) 
				{
				if (IsPrivateBlock(workBlock))
					{									
					if (IsDeadBlock(workBlock))
						{
						holes++;
						}
					else if (IsMasterBlock(workBlock))
						{	
							/* find something better to do here */
						}
					else if (IsTrailerBlock(workBlock))
						{
						foundTrailer = true;
						}
					}
				else 
					{
					_PtrBlockCheck(workBlock->data, curHeap);
					ptrBlocks++;
					}
				} 
			else if (IsFreeBlock(workBlock))
				{
				_FreeBlockCheck((freeBlock*)workBlock, curHeap);
				freeBlocks++;
				totalFree += workBlock->size;
				foundFavored |= (freeBlock*)workBlock == curHeap->favoredFree;
				if (!foundFreeBlock)
					{
					foundFreeBlock = true;
					IfDbgMsg(curHeap->firstFree != (freeBlock*)workBlock,
						"first free does not agree with header", workBlock);
					}
				
				if (!foundLastFree)
					{
					if ((freeBlock*)workBlock == curHeap->lastFree)
						{
						foundLastFree = true;
						}
					}
				else
					DbgMessage("found free block after last free", (long) workBlock);
					
				if (!foundLowestRemovable)
					{
					foundLowestRemovable = true;
					IfDbgMsg((char*)workBlock != (char*)curHeap->lowestRemovableBlock,
						"LowestRemovableBlock is bad", workBlock);
					}
					
				/* check to see if we found the largest free block */
				if (workBlock->size > largestFreeBlock->size)
					largestFreeBlock = (freeBlock*) workBlock;
				}
			else
				DbgMessage("undetermined block", (long) workBlock);
			
			if (IsAllocatedBlock(workBlock))
				{
				totalDelta += (sizeDelta = workBlock->sizeDelta);
				}
			
			IfDbgMsg(workBlock > curHeap->backLimit, "walked workBlock past end of heap", workBlock);
			workBlock = GetNextBlock(workBlock);
			}	/* while */
						
		CheckZoneForBadFreeMPs(curHeap);
		IfDbgMsg(foundLowestRemovable == false && curHeap->lowestRemovableBlock != curHeap->backLimit, "cant find lowestRemovableBlock", curHeap);
		IfDbgMsg(foundTrailer == false, "missing trailer", curHeap);
		IfDbgMsg(foundFavored == false && curHeap->favoredFree != DummyFree(curHeap), "favored free in header bad", curHeap);
		IfDbgMsg(foundFreeBlock == false && curHeap->firstFree != DummyFree(curHeap), "first free in header bad", curHeap);
		IfDbgMsg(foundLastFree == false && curHeap->lastFree != DummyFree(curHeap), "last free in header bad", curHeap);
		IfDbgMsg(freeBlocks != curHeap->freeBlocks, "bad free count", freeBlocks);
		IfDbgMsg(ptrBlocks != curHeap->ptrBlocks, "bad ptrBlock count", ptrBlocks);
		IfDbgMsg(handleBlocks != curHeap->handleBlocks, "bad handleBlock count", handleBlocks);
		IfDbgMsg(holes != curHeap->holes, "bad hole count", holes);
		IfDbgMsg(totalFree != curHeap->totalFree, "bad totalFree", totalFree);
		IfDbgMsg(totalPurgable != curHeap->totalPurgableSpace, "bad totalPurgableSpace", totalPurgable);
		IfDbgMsg(totalDelta != curHeap->totalDelta, "bad total delta", totalDelta);
		IfDbgMsg(curHeap->firstFree == nil, "firstFree = nil", curHeap);
		IfDbgMsg(curHeap->lastFree == nil, "lastFree = nil", curHeap);
		IfDbgMsg(curHeap->fCacheNeedsToBeFlushed,"kCacheNeedsToBeFlushed flag still set", curHeap);
		++curHeap->checkCount;

		/* Does favored free point to the largest free block? */		
		if (largestFreeBlock == curHeap->favoredFree)
			++curHeap->favoredFreeHits;
		}	/* if checkHeap */
	SimulateHeapScramble(curHeap);
	}


long GetHeapValidation(stdHeap* sourceHeap)
	{
	IfDbgMsg(sourceHeap == nil, "cannot get heap validation for a nil heap", 0);
	return sourceHeap->validationFlags;
	}


void SetHeapValidation(stdHeap* targetHeap, long flags)
	{
	IfDbgMsg(targetHeap == nil, "cannot set heap validation for a nil heap", 0);
	targetHeap->validationFlags = flags;
	}


/* This routine will call back a client if s/he so desires. Warning: the client
	cannot call any other MM call in response to this call back. It is for debugging
	purposes only. */
void _AlertClientRelocateBlock(Ptr oldLocation, Ptr newLocation, stdHeap* curHeap)
	{
	/* call purge warning proc */
	if (curHeap->relocateProc)
		{
		CALL_FNC_PTR(RelocateProcPtr, curHeap->relocateProc, (oldLocation, newLocation, curHeap));
		}
	}

void ValidateHeap(stdHeap* target, long tempFlags)
	{
	long	saveFlags = target->validationFlags;

	IfDbgMsg(target == nil, "target heap to validate is nil", 0);

	target->validationFlags = tempFlags;
	_CheckHeap((stdHeap*)target);
	target->validationFlags = saveFlags;
	}


void ValidatePtr(void* block, stdHeap* curHeap)
	{
	_PtrBlockCheck(block, curHeap);
	}


void ValidateHandle(void* block, stdHeap* curHeap)
	{
	_HandleBlockCheck(block, curHeap);
	}


void ValidateMasterPointer(void* block, stdHeap* curHeap)
	{
	_HandleBlockCheck(*(void **) block, curHeap);
	}


/* this function can be removed once the glue for each trap is verified */
void DbgValidateTrapWord(ushort trapWord)
	{
	#ifndef linked_thinkc_app
	IfDbgMsg(trapWord < 0xA000 || trapWord > 0xA800, "bad trap word", trapWord);
	#endif	
	}


/* Same as FindFreeBlock, except that it skips the favored free block */
static freeBlock* FindOtherFreeBlock(blockSize_t reqBlockSize, stdHeap* curHeap);
static freeBlock* FindOtherFreeBlock(blockSize_t reqBlockSize, stdHeap* curHeap)
	{
	DbgCheckSize(reqBlockSize);

	/* if the size is not great enough, forget it and bail right away */
	if (curHeap->totalFree >= reqBlockSize)
		{
		freeBlock *favoredFree;
		freeBlock *workBlock;
		
		/* cache favoredFree */
		favoredFree = curHeap->favoredFree;
		
		/* start search at block past favoredFree */	
		workBlock = favoredFree->nextFree;
		
		/* look looking for a free block of the right size */
		do 
			{
			if (workBlock->size >= reqBlockSize)
				return workBlock;
			} 
		while ((workBlock=workBlock->nextFree) != favoredFree);
		}
	return nil;
	}

#else	/* debugging */

#if 0
	long GetHeapValidation(heap *sourceHeap) { return 0; }
	void SetHeapValidation(heap *targetHeap, long flags) {}
	void ValidateHeap(heap *target, long tempFlags) {}
	void ValidatePtr(void *block) {}
	void ValidateHandle(void *block) {}
	void ValidateMasterPointer(void *block) {}
#endif

#endif	/* debugging */
