/*
	File:		MemMgrInternal.c

	Contains:	Internal Memory Manager Routines

	Written by:	Jeff Crawford, Brian Topping, Mike Wiese

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <159>	 1/26/94	BT		#1138909 <BT, WNM> PurgeAndMakeSpace would go off the deep end
									sometimes when searching the region it found while trimming the
									size if cumRelocSpace went negative due to a unsigned comparison
									problem. Pin cumRelocSpace to zero if it attempts to go
									negative.
	   <158>	 1/25/94	BT		#1137973 <BT, ewa> Fix SetBlockSize to mark the target block as
									busy when the grow space that is found is behind the target and
									the target is relocatable. Before, if there were zero or more
									relocatables followed by a free after the target and memory was
									low trying to relocate one of the blocks before the target, the
									target block would be relocated, blowing the reason to make
									space there in the first place.
	   <157>	 1/20/94	BT		#1137209 <BT, jrc> Fix PurgeMem to actually do the purge via
									PurgeAndMakeSpace. It never used to be called for this, so we
									need special consideration for PurgeMem.
	   <156>	12/20/93	BT		<BT, SL> #1131850, 1130089:  Third time's a charm.  Don't wanna
									call the GZ proc when the options to FindSpace have kDontCallGZ
									in them.
	   <155>	12/17/93	BT		<BT, SL> #1131850, #1131867:  Useless comment for Sam to make
									snide remarks about.
	   <154>	12/10/93	BT		<BT,ewa> #1130089:  The growzone was not getting called in
									situations where requested allocations where smaller than
									zcbFree and the all free blocks were discontigous _and_ smaller
									than the allocation, and the first relocatable block that was
									big enough to free up the space for the allocation was bigger
									than the space that could be freed by compaction.  The fix is in
									FindSpace≈ to find the largest contig free or relo space and use
									that to check before returning kJumpRelo in results.
	   <153>	11/29/93	BT		<BT, JRG>#1118963, fix SetBlockSize to calculate the
									lowestRemovableBlock properly when the next block is a free
									block and the resized block grows into it.
	   <152>	 11/9/93	BT		<BT, SL> 1114907 revisited, this is a better fix.
	   <151>	 11/5/93	BT		<BT, JRG> 1114907 revisited, this is a better fix.
	   <150>	10/14/93	BT		<BT, ewa> Radar 1117552; Change interfaces around. Radar
									1114117; fix MoveHHi.
	   <149>	 9/24/93	BT		<BT, qdg> #1114907, AllocateMoreMasters needs to use
									kDfltMasters when the number is less or equal to zero not just
									zero.
	   <148>	 8/30/93	BT		<BT, ewa> #1107995, Fix problem in MoveHHi not adjusting
									sizeDelta properly. Also changed other occurences of the fix to
									match new code.
	   <147>	 8/19/93	JC		<mlw> #1106373, Fix problem when nil is returned by FindHeap.
	   <146>	 8/17/93	JC		<mlw> #1104797, #1106652, Removed odd free MP lists from the
									internal_debug and shipping builds.
	   <145>	 8/11/93	JC		<BT> #1105806, Fixed ExtendApplLimit to check for the fact the
									new heap trailer can be above ApplLimit. This fixes Virex which
									hand rolls an application heap above BufPtr.
	   <144>	 8/10/93	JC		<ewa> #1102189, Fixed another ">" to be a ">=" in MoveBlockHi.
	   <143>	  8/9/93	JC		#1102189, Fixed a ">" to be a ">=" in MoveBlockHi.
	   <142>	  8/9/93	JC		<ewa> #1103834, fixed bug where we don't purge blocks in the
									System zone when the GZProc returns nil.
	   <141>	 7/29/93	JC		#1102189, #11022190, Fixed MoveBlockHigh to slide blocks up in
									certain situations.
	   <140>	 7/27/93	JC		#1100227, <mlw> Fixed size delta problem and removed
									kWorstCaseBlockOverhead to facilitate Claris XTND.
	   <139>	 7/26/93	JC		#1100694, commented out ChainedGZProc support.
	   <138>	 7/26/93	JC		#1098318, #1098401, Made changes to SetBlock size to fix several
									bugs found by Bill's test tool. SetBlockSize now goes through a
									MakeSpace loop to create more space if a handle cannot be sized
									larger.
	   <137>	 7/23/93	JC		#1098318, Changed a "<" to a "<=" in FindSpaceHigh to accomodate
									an exact fit when JumpRelocating blocks.
	   <136>	 7/23/93	JC		#1101604 fixed default MP block allocation to be more like the
									old MM.
	   <135>	 7/16/93	JC		#1100608, fixed bug in JumpRelocateRange and JumpRelocateBlock
									where they were trimming fat to to lower than kMimFreeBlockSize.
	   <134>	  7/7/93	JC		#1096767,1096744,1096911: Fixed PurgeSpace to calculate a more
									accurate value of contiguous purgable space.
	   <133>	 6/30/93	JC		#1089109: Removed fHeapIsDirty bit.
	   <132>	 6/22/93	JC		Fixed GZ proc to save and restore Register A5 to make Resolve &
									Wings work.
	   <131>	 6/16/93	JC		Added universal low memory getters and setters.
	   <130>	 6/10/93	JC		Added support for the heap is dirty bit again. It is not yet
									fully functional.
	   <129>	  6/9/93	BT		Change uppPurgeProcProcInfo to uppPurgeProcInfo for
									compatibility with universal headers.
	   <128>	  6/8/93	JC		Optimized setting of favoredFree in SlideBlocksUp and
									PurgeAndSlideBlocksDown.
	   <127>	  6/8/93	JC		Fixed MarkBlockAsPrivate.
	   <126>	  6/8/93	JC		Fixed more assorted comments.
	   <125>	  6/8/93	JC		Made change to SetBlockSize to support large freeBlockHeaders.
	   <124>	  6/7/93	JC		Made assorted comment changes.
	   <123>	  6/7/93	JC		Optimized SlideBlocksDown to move handleBlocks in chunks.
	   <122>	  6/4/93	JC		Sped up Stage 1 heap compaction by scanning for a range to
									slide.
	   <121>	  6/4/93	JC		Removed HeapID's from the non debug version. Fixed relative
									handle to be copied instead of recalculated. Fixed the
									calculation of bytes moved for accurate heap statistics.
	   <120>	  6/4/93	JC		Removed use of HeapIsDirty bit for now. Fixed all situations
									where JumpRelocateRange can move contents of endBlock.
	   <119>	  6/3/93	JC		Modified CompactHeap to respect the dirty bit during stage 1
									heap compactions only. Compact heap now returns the dummy free
									block instead of nil when the heap is completely full. Changed
									MakeSpaceLow. Removed call to DbgCheckHeap in
									PurgeAndSlideBlocksDown.  Made a small fix to PurgeAndMakeSpace
									where it was purging one more block than required.
	   <118>	  6/1/93	JC		Fixed MakeSpaceLow again to handle the JumpOrSlideBlocks path
									where endBlock was being trashed.
	   <117>	 5/24/93	JC		Changed XXX to DbgXXX for all debug routines.
	   <116>	 5/20/93	JC		Cleaned up call back procs.
	   <115>	 5/19/93	JC		Began changes as requested by the code review. Removed options
									parameter from AllocateMoreMasters. Fixed bug in FindSpaceLow
									where endBlock was not correct when passed to SlideBlocksDown
									after JumpRelocateRange had failed.
	   <114>	 5/18/93	JC		Fixed the “zero k available” bug. Yippee! This fix requires a
									new ProcessMgr to work completely. Also fixed Jim Gochees
									problem one more time in MakeSpaceLow.
	   <113>	 5/15/93	JC		Fixed PurgeAndMakeSpace to check for Ptr blocks first incase
									they are really busy handles. This should fix the Excel DebugStr
									message when running in low memory.  Also cleanup up
									SetBlockSize to be more readable.
	   <112>	 5/14/93	JC		Cleaned up implementation of GZRootPtr, GZRootHnd and GZMoveHnd.
	   <111>	  5/7/93	JC		Added support for GZRootHnd. Fixed obscure bug where
									JumpRelocateRange we would fail when we could still slide blocks
									up. Also fixed a bug in MakeSpaceLow to check against backLimit.
									Fixed similar bug in MakeSpaceHigh to check against
									lowestRemoveableBlock. Optimized AlignUp to be 4 assembly
									language instructions.
	   <110>	  5/2/93	JC		Put odd free master pointer list back in for any app that does
									not have its compatibility flags set. This odd list is used to
									catch clients who dispose of a block twice, or dispose a block
									then lock it (etc.). Also fixed an obscure bug in SetSize with
									lowest removable block. Also fixed sizeDelta tally problem.
	   <109>	 4/26/93	JC		Fixed bug in ExtendApplLimit where MPW subtly uses signed
									arithmetic where unsigned is desired.
	   <108>	 4/23/93	JC		Fix subtle bug in SetBlockSize (and ConsumeFreeSpaceHigh) where
									free blocks that we to small were being created.
	   <107>	 4/20/93	JC		Added ability to remove heaps from the heap tree when thier
									memory is being disposed. This should fix AfterDark and some MPW
									tools.
	   <106>	 4/18/93	JC		Changed #defines to more acurate descriptions. Changed
									small_block_headers to small_freeBlock_headers and linkedIn to
									linked_thinkc_app.   •• Brian & Sam take note.••
		 <1>	 6/10/92	JC		New Today

*/


#ifndef THINK_C
	#ifdef StarTrek
		#include <MacTypes.h>
		#include <MacMem.h>
		#include <SysEqu.h>
		#include <Errors.h>
		#include <OSUtils.h>
	#else
		#include <Types.h>
		#include <Memory.h>
		#include <Errors.h>
		#include <OSUtils.h>
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


#ifdef patchedIn
	/* This will overcome the 32k limit */
	#pragma segment Figment
#endif

#ifdef THINK_C
	/* This will overcome the 32k limit */
	#pragma segment Figment
#endif

/* kFirstRegionOnly & kContinueUntilRegionFound*/
typedef enum
{
	kFirstRegionOnly			= 0,
	kContinueUntilRegionFound	= 1
} FindSpaceOptions;


/* results returned by FindSpaceLow & FindSpaceHigh */
typedef enum
{
	kNoMovementRequired				= 1,
	kSlideBlocksUp	 				= 2,
	kSlideBlocksDown				= 3,
	kJumpRelocateBlocks 			= 4,
	kJumpRelocateOrSlideBlocks		= 5,
	kCantFindSpace					= 6
} FindSpaceResults;


	/****************************************************************/
	/* Inline routines												*/
	/****************************************************************/

	/****************************************************************/
	/* Non-inline routines											*/
	/****************************************************************/


/*
 *	Adds the block to the free chain or moves a block in the free chain. It does this
 *	by adding workblock in the free chain between prevBlock and nextBlock.
 */
#if 0
#define SetFreeChain(work, prev, next)										\
	{																		\
	/* warning: the debug checks below might fail with dummy free */		\
	IfIntDebugMsg(!IsFreeBlock(prev),"not a freeblock", prev);				\
	IfIntDebugMsg(!IsFreeBlock(next),"not a freeblock", next);				\
																			\
	((freeBlock*)work)->prevFree = (freeBlock*)prev;						\
	((freeBlock*)prev)->nextFree = (freeBlock*)work;						\
																			\
	((freeBlock*)work)->nextFree = (freeBlock*)next;						\
	((freeBlock*)next)->prevFree = (freeBlock*)work;						\
	}
#endif

static void SetFreeChain(freeBlock* workBlock, freeBlock* prevBlock, freeBlock* nextBlock);
static void SetFreeChain(freeBlock* workBlock, freeBlock* prevBlock, freeBlock* nextBlock)
	{
	/* note: Since the dummyFree block is part of the free chain, (dummyFree's
		nextFree & prevFree ptrs are really curHeap->firstFree & curHeap->lastFree)
		there is no need to adjust curHeap->firstFree or curHeap->lastFree.  They are 
		in effect, "self adjusting". Note: no stack frame needed for this function.
		*/
		
	IfIntDebugMsg(!IsFreeBlock(prevBlock),"not a freeblock", prevBlock);
	IfIntDebugMsg(!IsFreeBlock(nextBlock),"not a freeblock", nextBlock);

	workBlock->prevFree = prevBlock;
	prevBlock->nextFree = workBlock;
	
	workBlock->nextFree = nextBlock;
	nextBlock->prevFree = workBlock;
	}

/* removes a free block from the free chain and updates favoredFree */
static void RemoveFromFreeChain(freeBlock* usedUp, stdHeap* curHeap);
static void RemoveFromFreeChain(freeBlock* usedUp, stdHeap* curHeap)
	{
	freeBlock* prevFree = usedUp->prevFree;
	freeBlock* nextFree = usedUp->nextFree;

	IfIntDebugMsg(prevFree == nil, "prevFree is nil", usedUp);
	IfIntDebugMsg(nextFree == nil, "nextFree is nil", usedUp);

	prevFree->nextFree = nextFree;
	nextFree->prevFree = prevFree;
		
	IfIntDebugMsg(curHeap->firstFree > curHeap->lastFree, "bad free chain", curHeap);
	
	/* make an intelligent decision where to put the favoredFree */
	if (curHeap->favoredFree == usedUp)
		{
		if (nextFree->size > prevFree->size)
			curHeap->favoredFree = nextFree;
		else
			curHeap->favoredFree = prevFree;
		}
	}


/* find the heap zone given an empty handle (master pointer is nil). */
stdHeap* GetZoneFromNilMP(void* mpAddress)
	{
	stdHeap* curHeap;
	
	if (nil == (curHeap = FindHeap(mpAddress)))
		{
		/* Could not find a heap in the heap tree, we use TheZone instead */
		curHeap = LMGetTheZone();
		}
		
	return curHeap;
	}


/*
 *	Walks up the heap looking for the lowest block that is either free or a floating 
 *	handle.  If we made it to the end of the main fragment, we bail and return the last 
 *	block.
 */
stdBlock* WalkUpFindNewLowRemoveable(stdBlock* workBlock, stdHeap* curHeap)
	{
	stdBlock*	theEnd = curHeap->backLimit;
	
	do
		{
		if (IsHandleBlock(workBlock = GetNextBlock(workBlock)))
			{
			if (IsUnlockedHandle(workBlock))
				return workBlock;
			}
		else if (!IsPtrBlock(workBlock))
			{
			/* block is free, return it */
			return workBlock;
			}
		
		/* stop when we reached the end of the main fragment */	
		#ifdef implemented_discontiguous_heaps
			if (workBlock->mpFlags & deadBlockType+trailerBlockType)
				return workBlock;
		#else
			if (workBlock == theEnd)
				return workBlock;
		#endif
		}
	while (true);
	}

/*
 *	this block is free, occupy the entire block. This routine is used by internal routines
 *	to take this block out of the free chain so allcations wont take up this space.
 */
static void OccupyFreeSpace(freeBlock*	workBlock, stdHeap* curHeap);
static void OccupyFreeSpace(freeBlock*	workBlock, stdHeap* curHeap)
	{
	IfIntDebugMsg(!IsFreeBlock(workBlock),"block not free", workBlock);
	IfIntDebugMsg(curHeap->totalFree < 0, "bad free total", curHeap);

	curHeap->totalFree -= workBlock->size;
	RemoveFromFreeChain(workBlock, curHeap);

	/*
	 *	we need to set the size delta and heapID to keep the heap correct. This is
	 *	important when jump relocating a range of blocks and the grow zone gets
	 *	called.
	 *
	 *	set tags=ptrType, mpFlags=privBlockType, heapID=CurHeapID, sizeDelta=minDelta
	 */
	JamTagsFlagsAndSizeDelta(workBlock,
		((ulong)ptrType << 24) + ((ulong)privBlockType << 16) + kMinDelta);

	DbgSetBlockHeapID((stdBlock*)workBlock, curHeap);
	DbgCode(curHeap->freeBlocks--);
	}


/*
 *	Slides blocks down until the endSlide is hit. During this slide, a free block is
 *	bubbled up. newFreeBlock must point to a free block, endslide does not. This
 *	routine sets favoredFree. This return returns a pointer to the newly created
 *	freeBlock.
 *
 *	This routine slides blocks in "chunks". A chunk is a sequence of handle blocks.
 *
 *	note: No need to pass reqBlockSize into this routine. That should already be 
 *		determined by the caller.
 */
static freeBlock*	SlideBlocksDown(freeBlock* curFree, stdBlock* endSlide, stdHeap* curHeap);
static freeBlock*	SlideBlocksDown(freeBlock* curFree, stdBlock* endSlide, stdHeap* curHeap)
	{
	handleBlock*	workBlock;
	freeBlock*		prevFree = curFree->prevFree;
	freeBlock*		nextFree = curFree->nextFree;
	freeBlock*		dummyFree = DummyFree(curHeap);	/* cache dummyFree for optimization */
	blockSize_t		cumFreeSize = curFree->size;
	blockSize_t		workTrailerSize;		/* size of the handle block that trails in front of work block */	
	handleBlock*	chunkStart;				/* start of range of handles to move */
	Boolean 		setFavoredFree;			/* true => favoredFree needs to be reset */
	Boolean			doExtraSlide;			/* true => have to slide a chunk that has not freeblock at the end */
	
	/* record the size of the handle block infront of the range */
	workTrailerSize = ((stdBlock*)(curFree->back))->size;

	/* is favored free inside this range? */
	setFavoredFree = (curHeap->favoredFree >= curFree && curHeap->favoredFree <= (freeBlock*)endSlide);

	/* check that the first block in the heap is free */	
	IfIntDebugMsg(!IsFreeBlock(curFree),"expected free block", curFree);
	IfIntDebugMsg(curFree == (freeBlock*)endSlide,"curFree == endFree", curFree);

	/* Special case for when there is a free block above endSlide */
		{
		/* reuse workBlock */
		workBlock = GetNextBlock(endSlide);
		if (IsFreeBlock(workBlock))
			{
			endSlide = (stdBlock*) workBlock;
			}
		}

	/* decide now whether to do an extra slide */		
	doExtraSlide = IsHandleBlock(endSlide);
	
	/* loop through all free blocks in the range */
	while (nextFree <= (freeBlock*)endSlide && nextFree != dummyFree)
		{
		workBlock = chunkStart = GetNextBlock(curFree);
		
		/* correct the backptr due to size differences between the free block and the workBlockTrailer */
		workBlock->back = (Ptr)workBlock->back + curFree->size - workTrailerSize;

		/* loop for this chunk */
		do
			{
			IfIntDebugMsg(IsFreeBlock(workBlock), "did not expect free block", workBlock);
			IfIntDebugMsg(IsFixedBlock(workBlock), "error, not allowed to slide immovable blocks", workBlock);

			workBlock->back = (char*)workBlock->back - cumFreeSize;
			
			/* reset MP to point to new location */
				{
				Handle pMP = (Handle) ((char*)workBlock->relHandle + (long)curHeap);
				*pMP -= cumFreeSize;
				}
			
			DbgAlertClientRelocateBlock((Ptr)workBlock->data, (Ptr)workBlock - cumFreeSize + kBlockHeaderSize, curHeap);
			DbgCode(curHeap->totalBlocksMoved++);

			workTrailerSize = workBlock->size;
			workBlock = GetNextBlock(workBlock);
			}
		while ((freeBlock*)workBlock < nextFree);

		/* move the chunk of handle blocks down */		
		MoveBytes(chunkStart, (Ptr)chunkStart - cumFreeSize, (Ptr)nextFree - (Ptr)chunkStart);
		
		/* update heap statistics */
		DbgCode(curHeap->bytesMoved += ((Ptr)nextFree - (Ptr)chunkStart));
		DbgCode(curHeap->bytesSlidDown += ((Ptr)nextFree - (Ptr)chunkStart));
		DbgCode(curHeap->freeBlocks--);
		
		curFree = nextFree;
		nextFree = nextFree->nextFree;	/* Advance to next free block */
		cumFreeSize += curFree->size;
		}
	
	if (doExtraSlide)
		{
		/* loop one more time for that last little chunk */
		workBlock = chunkStart = GetNextBlock(curFree);
		
		/* correct the backptr due to size differences between the free block and the workBlockTrailer */
		workBlock->back = (Ptr)workBlock->back + curFree->size - workTrailerSize;

		do
			{
			workBlock->back = (char*)workBlock->back - cumFreeSize;
			
			/* reset MP to point to new location */
				{
				Handle pMP = (Handle) ((char*)workBlock->relHandle + (long)curHeap);
				*pMP -= cumFreeSize;
				}
			
			DbgAlertClientRelocateBlock((Ptr)workBlock->data, (Ptr)workBlock - cumFreeSize + kBlockHeaderSize, curHeap);
			DbgCode(curHeap->totalBlocksMoved++);

			workTrailerSize = workBlock->size;
			workBlock = GetNextBlock(workBlock);
			}
		while (workBlock <= (handleBlock*)endSlide);
		
		MoveBytes(chunkStart, (Ptr)chunkStart - cumFreeSize, (Ptr)endSlide - (Ptr)chunkStart + endSlide->size);

		/* update heap statistics */
		DbgCode(curHeap->bytesMoved += ((Ptr)endSlide - (Ptr)chunkStart + endSlide->size));
		DbgCode(curHeap->bytesSlidDown += ((Ptr)endSlide - (Ptr)chunkStart + endSlide->size));
		}
	else
		{
		workBlock = GetNextBlock(workBlock);
		}
	
	/* calculate the location of this newly created freeBlock */
	curFree = (freeBlock*) ((Ptr)workBlock - cumFreeSize);
	
	/* reset back pointer for the block after the range */
	workBlock->back = curFree;

	/* fill in fields of newly created free block */
	curFree->back = (Ptr)curFree - workTrailerSize;	/* reset back for newly created freeBlock */
	curFree->size = cumFreeSize; 
	#ifndef small_freeBlock_headers
		((stdBlock3*)curFree)->tagsFlagsSizeDelta = 0; 	/* set tags, mpFlags, heapID, sizeDelta to 0 */
	#endif
	SetFreeChain(curFree, prevFree, nextFree);

	DbgGarbageFill(curHeap, curFree->data, cumFreeSize - kFreeBlockHeaderSize);
	IfIntDebugMsg(curHeap->favoredFree == nil, "didn’t expect nil favored free", curHeap);
	
	/* set favoredFree if we have to */
	if (setFavoredFree || cumFreeSize > curHeap->favoredFree->size)
		curHeap->favoredFree = curFree;
	
	/* since we moved blocks, we should flush the instruction cache */
	MarkCacheNeedsToBeFlushed(curHeap);
	
	return curFree;
	}


/*
 *	Slides blocks up by repeatedly swapping a freeBlock with a handeBlock, freeBlocks
 *	between the 2 bounds are coelesced.
 *
 *	note: No need to pass reqBlockSize into this routine. That should already be 
 *		determined by the caller.
 *
 *	As an optimization, this routine could slide blocks in chunks. However, this
 *		routine is not called nearly as often as SlideBlocksDown.
 */
static freeBlock* SlideBlocksUp(stdBlock* firstBlock, freeBlock* bubbleFree, stdHeap* curHeap);
static freeBlock* SlideBlocksUp(stdBlock* firstBlock, freeBlock* bubbleFree, stdHeap* curHeap)
	{
	stdBlock*		rangeEnd = GetNextBlock(bubbleFree);	/* the next block after the range */
	handleBlock*	workBlock = bubbleFree->back; 			/* first points to the blockToMove, later points to freeBlock */
	stdBlock*		destBlock;			/* block gets moved here */
	freeBlock*		prevFree = bubbleFree->prevFree;
	freeBlock*		nextFree = bubbleFree->nextFree;
	Boolean 		setFavoredFree;		/* true => must set favoredFree */

	/* is favored free inside this range? */
	setFavoredFree = (curHeap->favoredFree >= (freeBlock*)firstBlock && curHeap->favoredFree <= bubbleFree);
	
	/* bubbleFree starts as the top free block, it bubbles downward. */
	IfIntDebugMsg(!IsFreeBlock(bubbleFree),"end range is not free", bubbleFree);
	IfIntDebugMsg(firstBlock == nil,"firstBlock is nil", curHeap);
	
	/* if the block in front of the range is free, then set it as the boundary */	
	if (IsFreeBlock(firstBlock->back))
		firstBlock = firstBlock->back;
	
	/* loop,  slide relocatables up and letting the freeblock bubble down */	
	do
		{
		IfIntDebugMsg(!IsUnlockedBlock(workBlock), "workBlock not relocatable", workBlock);
		IfIntDebugMsg(IsFreeBlock(rangeEnd),"rangeEnd is free", rangeEnd);
		
		destBlock = (stdBlock*) ((char*)rangeEnd - workBlock->size); /* calculate destination */
		
		/* reset MP to point to new location */
			{
			Handle pMP = (Handle) (workBlock->relHandle + (long)curHeap);
			*pMP = (Ptr)((handleBlock*)destBlock)->data;
			}
		
		/* slide data, bubbleFree's header may now contain bad data */
		MoveBytes(workBlock, destBlock, workBlock->size);	
		rangeEnd->back = destBlock;							/* restore back pointer */

		/* update heap statistics */
		DbgCode(curHeap->bytesMoved += workBlock->size);
		DbgCode(curHeap->totalBlocksMoved++);
		DbgCode(curHeap->bytesSlidUp += workBlock->size);

		/* Are we going to coelesce with the next block below? */
		if (workBlock->back == (void*)prevFree)
			{
			workBlock = (handleBlock*)prevFree;
			prevFree = prevFree->prevFree;
			DbgCode(curHeap->freeBlocks--);
			}
	
		/* march pointers */
		rangeEnd = destBlock;
		bubbleFree = (freeBlock*)workBlock;
		workBlock = workBlock->back;
		}
	while ((stdBlock*)workBlock >= firstBlock);
	
	/* set up fields for the newly created block */
	bubbleFree->size = (char*)rangeEnd - (char*)bubbleFree;
	SetFreeChain(bubbleFree, prevFree, nextFree);
	#ifndef small_freeBlock_headers
	((stdBlock3*)bubbleFree)->tagsFlagsSizeDelta = 0; 	/* set tags, mpFlags, heapID, sizeDelta to 0 */
	#endif
	
	/* reset rangeEnd's back pointer */
	rangeEnd->back = bubbleFree;
	
	/* reset favored free if we have to */
	if (setFavoredFree || bubbleFree->size > curHeap->favoredFree->size)
		curHeap->favoredFree = bubbleFree;
	
	/* since we moved blocks, we should flush the instruction cache */
	MarkCacheNeedsToBeFlushed(curHeap);

	return bubbleFree;
	}


/*
 *	This checks to see if any fixed blocks between the free ranges provided. If a fixed 
 *	block is found, it returns true.
 */
Boolean FixedBlockInRange(freeBlock* rangeBottom, freeBlock* rangeTop)
	{
	stdBlock* workBlock = rangeTop->back;
	
	IfIntDebugMsg(rangeBottom > rangeTop, "rangeBottom > rangeTop", rangeBottom);
	IfIntDebugMsg(workBlock == (stdBlock*) rangeBottom, 
					"rangeBottom and rangeTop are next to each other",  workBlock);
	IfIntDebugMsg(workBlock > (stdBlock *) rangeTop, "corrupt heap",  workBlock);

	/* walk blocks down looking for a fixed block */
	do
		{
		if (IsFixedBlock(workBlock))
			return true;
		}
	while ((stdBlock*) rangeBottom < (workBlock = workBlock->back));
	
	IfIntDebugMsg(workBlock != (stdBlock*) rangeBottom, "corrupt heap", workBlock);
	return false;
	}
	
	
/*
 *	Jump relocates a single block by allocating a new one and disposing the old. This 
 *	routine is also used to change the size of a block by allocating a new one of a 
 *	different size. It is also used to move blocks high or low.
 *
 *	Note: routines that call JumpRelocateBlock to change the block size will have to 
 *	correct the incorrect block size.
 *
 *	SetHandleSize calls this routine to change the size of the block. MoveHHi and MoveHLow
 *	calls this routine to move a block.
 */
static handleBlock* JumpRelocateBlock(handleBlock* blockHeader, blockSize_t reqBlockSize, long options, stdHeap* curHeap);
static handleBlock* JumpRelocateBlock(handleBlock* blockHeader, blockSize_t reqBlockSize, long options, stdHeap* curHeap)
	{
	handleBlock*			newBlockHeader;
	Handle					theHandle = (Handle) (blockHeader->relHandle + (long)curHeap);
	blockSize_t				clientDataCopySize = blockHeader->size - kBlockHeaderSize;
	DbgCode(blockSize_t	orginalReqBlockSize = reqBlockSize);	/* need this for a size delta calculation */	

	IfIntDebugMsg(!IsHandleBlock(blockHeader),"not a handle block", blockHeader);
	IfIntDebugMsg(IsLockedHandle(blockHeader),"handle is locked", blockHeader);

	/* are we just moving a block? (are we not changing sizes?) */
	if (reqBlockSize == blockHeader->size)
		{
		/*
		 *	Time to trim some fat. If the block we are moving has some recoverable delta,
		 *	we can make the size of the new location smaller. This will reduce internal
		 *	fragmentation and prevent it from overflowing the 8 bit quantity in the sizeDelta field.
		 *
		 *	Note:	Must make sure not to shrink the block to be less than kMinBlockSize.
		 *			This happens without debugging, without small_FreeBlockHeaders
		 *			and with quadLongWordAligned. Ideally the test should be:
		 *				sizeDelta >= (kAlignmentFactor + kMagicSize + kBackPtrSize)
		 *								AND
		 *				physicalBlockSize >= kMinFreeBlockSize - kAlignmentFactor
		 *
		 *			Since the 2nd test implies sizeDelta is only a little larger than the 1st,  
		 *			we can simply compare against the larger even though it means we won't 
		 *			always be trimming optimally. So, to make the test fast, we just test for:
		 *				sizeDelta > (kAlignmentFactor + kMagicSize + kBackPtrSize)
		 *
		 *	Do we have some size delta we can recover?
		 */
		#ifdef small_freeBlock_headers
			if ((blockHeader->sizeDelta >= kAlignmentFactor + kMagicSize + kBackPtrSize))
		#else
			if ((blockHeader->sizeDelta > kAlignmentFactor + kMagicSize + kBackPtrSize))
		#endif
			{
			/* reduce internal fragmentation, of the relocated block. */
			reqBlockSize -= kAlignmentFactor;
			clientDataCopySize -= kAlignmentFactor; 
			}
		}

	/* we don't set GZMoveHnd because we aren't calling the GZ on a block-by-block */
	newBlockHeader = (handleBlock*)NewBlock(reqBlockSize, options, curHeap);

	if (newBlockHeader)
		{
		IfIntDebugMsg(*theHandle == nil, "*theHandle = nil", theHandle);

		/* note, since its a handle block, no need to check for lowestRemovableBlock */
		/* recover blockheader in case it moved */
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(*theHandle);
		
		/* update heap statistics */
		DbgCode(curHeap->bytesMoved += blockHeader->size);
		DbgCode(curHeap->totalBlocksMoved++);
		DbgCode(curHeap->bytesJumped += blockHeader->size);

		/*
		 *	copy contents of block to new location, we avoid copying the blockHeader to not disturb
		 *	the new size and back ptr of the destination block, which were filled in by NewBlock)
		 */
		MoveBytes(blockHeader->data, newBlockHeader->data, clientDataCopySize);

		/* copy tags, flags, heapID, sizeDelta to new location */
		((stdBlock3*)newBlockHeader)->tagsFlagsSizeDelta = ((stdBlock3*)blockHeader)->tagsFlagsSizeDelta;
		
		/* since the sizeDelta may have changed from old to new, we must correct it */
		/* 8/30/93 3:24:19 AM (BET): make this more readable (and more efficient) */
		newBlockHeader->sizeDelta += newBlockHeader->size - blockHeader->size;
			
		/* update the master pointer to point to new location */
		*theHandle = (Ptr)((handleBlock*)newBlockHeader)->data;
		
		/* update relative handle to point to the MP */
		newBlockHeader->relHandle = blockHeader->relHandle;

		/* adjust total purgable space */
		if (IsPurgableHandle(newBlockHeader))
			{
			if (blockHeader->size < newBlockHeader->size)	
				curHeap->totalPurgableSpace += newBlockHeader->size - blockHeader->size;
			else
				curHeap->totalPurgableSpace += blockHeader->size - newBlockHeader->size;
			}

		/* Debug Stuff */
		#ifdef debugging
			{
			/* if we are jump relocating to a new size and we are not actively changing
				the size of the block. If we are actively changing the size of the block,
				(SetHandleSize), we will correct the size delta later. */
			if ((blockHeader->size != newBlockHeader->size)	&& (orginalReqBlockSize == blockHeader->size))				
				{
				curHeap->totalDelta += newBlockHeader->sizeDelta - blockHeader->sizeDelta;
				}
			}
		#endif		

		/* remove the old block */
		KillBlock((stdBlock*)blockHeader, curHeap);
		
		/* since the block has moved, we should flush the instruction cache */
		MarkCacheNeedsToBeFlushed(curHeap);
		}

	return newBlockHeader;		/* return blockHeader or nil */
	}


/*
 *	Finds a range of relocatables that can be slide together this
 *	routine is called by CompactHeap.
 */
static freeBlock*	FindRangeToSlide(freeBlock*	workBlock);
static freeBlock*	FindRangeToSlide(freeBlock*	workBlock)
	{
	freeBlock* topFree = workBlock;
	
	/* walk blocks down looking for a fixed block */
	do
		{
		workBlock = GetNextBlock(workBlock);
		
		if (IsFreeBlock(workBlock))
			{
			topFree = workBlock;
			}
		else
			{
			if (IsFixedBlock(workBlock))
				break;
			}
		}
	while (true);
	
	return topFree;
	}


/*
 *	Compacts the heap until an adequate size is achieved. Returns a pointer to the largest 
 *	block available. If no freeblock exists, the dummy free block (size=0) is returned.
 *
 *	Compaction occurs in 2 stages. In stage 1, relocatable blocks slide down
 *	and free space is coelesced. In stage 2, the largest free block in the heap
 *	is made larger by relocating its neighbors.
 */
freeBlock* CompactHeap(blockSize_t reqBlockSize, stdHeap* curHeap)
	{
	freeBlock*	workBlock = curHeap->firstFree;		/* starts as first free, later it iterates */
	freeBlock* 	largestBlock = DummyFree(curHeap);	/* starts as DummyFree, later used as largestBlock */
	
	DbgCheckSize(reqBlockSize);
	DbgCode(curHeap->compactionCount++);
	
	/* Are there zero or 1 free blocks in the heap? */
	if (workBlock == curHeap->lastFree)				/* does (firstFree == lastFree) ? */
		{
		/*yes, we can bail early and not waste our time */
		
		if (workBlock == largestBlock)	/* does (firstFree == dummyFree) ? */
			{
			/* there are no free blocks in the heap. Only the dummy, we return it */
			return largestBlock;		/* return dummyFree */
			}
			
		/*
		 *	note: if we have exactly one free block in the heap. We goto
		 *	though to the stage 2 heap compaction cause the heap ain't dirty.
		 */
		largestBlock = workBlock;	/* set largest block to firstFree (favoredFree) */
		goto stage2;
		}


	/* stage 1, coelesce all free blocks that can slide together */
	do
		{
		freeBlock*	nextBlock;		/* someone convince MPW C to put this into a data register */

		/* debugging checks */
		IfIntDebugMsg(!IsFreeBlock(workBlock),"workBlock not free", workBlock);
		IfIntDebugMsg(workBlock == DummyFree(curHeap), "workBlock is dummyFree", workBlock);

		nextBlock = FindRangeToSlide(workBlock);
		
		/* did we find a range to slide? */
		if (nextBlock != workBlock)
			{
			/* YES, slide blocks down to coelesce all the free blocks. FavoredFree is set. */
			workBlock = SlideBlocksDown(workBlock, (stdBlock*)nextBlock, curHeap);
			}

		/* maintain largest block */
		if (workBlock->size > largestBlock->size)
			largestBlock = workBlock;

		/* advance to next free block */
		workBlock = workBlock->nextFree;
		}
	while(workBlock != DummyFree(curHeap));

	/* set favored free since it may not be set correctly in the above loop */
	curHeap->favoredFree = largestBlock;
		
		
	/*
	 *	For now, I choose to wait until the heap is stage 1 compacted before 
	 *	checking to see if we got enough space. Another option is to move this 
	 *	test into the stage 1 loop and return immediately after a large enough
	 *	block is found. Yet another possibility is to wait until after the 2nd
	 *	stage of the heap compaction before returning the largest block. 
	 *
	 *	Herb Derby has run some performance tests that indicate it is faster
	 *	to completely compact a heap first before checking for the requested
	 *	size. So we do it here, after the Stage 1 heap compaction.
	 */
	if (largestBlock->size >= reqBlockSize)
		{
		return largestBlock;
		}

	/*
	 *	Are there more than one free blocks in the heap?  We do this again since compaction
	 *	may have coelesced all free blocks.
	 */
	if (curHeap->firstFree == curHeap->lastFree)
		{
		IfIntDebugMsg(curHeap->favoredFree != largestBlock, "curHeap->favoredFree != largestBlock", largestBlock);
		return largestBlock;
		}

stage2:
	/* stage 2, jump relocate blocks out of the way to make more room for favFree */

	/* hog the largestFreeBlock so other blocks will jump relocate someplace else */
	OccupyFreeSpace(workBlock = largestBlock, curHeap);

	/* look up, see if we can move blocks out of the way */
	while (!(IsPtrBlock((workBlock = GetNextBlock(workBlock))) || IsLockedHandle(workBlock)))
		{
		blockSize_t	wbSize = workBlock->size;		/* cache workBlock size */
		
		/* can we move this block somewhere else? */
		if (JumpRelocateBlock((handleBlock*)workBlock, wbSize, kDontCompact, curHeap))
			{
			OccupyFreeSpace(workBlock, curHeap);	/* occupy this block too */
			largestBlock->size += wbSize;			/* largest block grows */
			}
		else
			{
			/* we failed to jump relocate the block, so we break out of the loop */
			break;
			}
		}
		
	workBlock->back = largestBlock;
	
	/* look down, see if we can move blocks out of the way */
	workBlock = largestBlock;
	while (!(IsPtrBlock((stdBlock*)(workBlock = workBlock->back)) || IsLockedHandle((stdBlock*)workBlock)))
		{
		if (JumpRelocateBlock((handleBlock*)workBlock, workBlock->size, kDontCompact, curHeap))
			{
			OccupyFreeSpace(workBlock, curHeap);	/* occupy this block too */
			workBlock->size += largestBlock->size;
			largestBlock = workBlock;
			}
		else
			{
			/* we failed to JumpRelocate, we move on and break out of the loop */
			workBlock = GetNextBlock(workBlock);
			break;
			}
		}
	
	/* reset the back pointer before nuking */
	workBlock = GetNextBlock(largestBlock);
	workBlock->back = largestBlock;
	KillBlock((stdBlock*)largestBlock, curHeap);
	
	IfIntDebugMsg(curHeap->favoredFree != largestBlock, "curHeap->favoredFree != largestBlock", largestBlock);
	return largestBlock;
	}
	

/*
 *	Calculates the largest block size without compacting the heap. With the newer more
 *	complex heap compaction mechanism (stage 2), it is now very hard to predict what the 
 *	size of the largest block will be. For now, we take the wimpy way out and just
 *	return the largest block size of stage 1 heap compactions instead. This size is
 *	<= the real maximum block size so there should not be any "compactibility" problems. 
 *	Note: size returned is the blockSize and not the client size.
 */
blockSize_t CalcMaxBlockSize(stdHeap* curHeap)
	{
	freeBlock*	workBlock;
	freeBlock*	nextBlock;			/* next free block */
	freeBlock*	lastFree;			/* cache lastFree to save unnecessary dereference */
	blockSize_t	largestSize;
	blockSize_t curRegionSize;
	
	/* Are there 0 or 1 free blocks in the heap (firstFree == lastFree) ?*/	
	if ((workBlock = curHeap->firstFree) == (lastFree = curHeap->lastFree))
		{
		return curHeap->favoredFree->size;
		}

	largestSize = 0;
	curRegionSize = 0;

	/* walk the free list to find the largest free region */
	while (true)
		{
		nextBlock = workBlock->nextFree;
		
		/* debugging check */
		IfIntDebugMsg(workBlock == DummyFree(curHeap), "rangeBottom is dummyFree", workBlock);
		IfIntDebugMsg(nextBlock == DummyFree(curHeap), "rangeTop is dummyFree", nextBlock);

		/* accumulate the current free size into the region */
		curRegionSize += workBlock->size;

		/* Is there a sandbar between the 2 free blocks */
		if (FixedBlockInRange(workBlock, nextBlock))
			{
			if (curRegionSize > largestSize)
				{
				largestSize = curRegionSize;
				}
			curRegionSize = 0;
			}
		
		/* did we reach the end? */	
		if (nextBlock == lastFree)
			{
			/* yes. Add next block size to the current region */
			curRegionSize += nextBlock->size;
			
			/* return either the largest size or the current region size */
			return (curRegionSize > largestSize) ? curRegionSize : largestSize;
			}
		
		/* advance to next free block */
		workBlock = nextBlock;
		}
		
	}


/*
 *	This routine blindly extends the heap zone by raising its heapEnd. It can be called
 *	on any heap. Clients of this routine must do the check themselves.
 */
void ExtendHeapLimit(ptrBlock* newTrailBlock, stdHeap* curHeap)
	{
	ptrBlock*	oldTrailBlock = curHeap->backLimit;
	spoofBlockStruct* trailSpoofBlock;
	
	DbgCheckSize((Ptr)newTrailBlock - (Ptr)oldTrailBlock);
	IfIntDebugMsg(curHeap->fHeapFullyExtended, "heap is already extended", 0);
	
	/* fix size of old trailer block */	
	oldTrailBlock->size = (char*)newTrailBlock - (char*)oldTrailBlock;

	/* create new trail block */
	newTrailBlock->size = kOldHeaderSize;		/* offset to spoof trailer */
	newTrailBlock->back = oldTrailBlock;
	newTrailBlock->parent = curHeap;
	curHeap->backLimit = newTrailBlock;

	/* create spoof trailer block */
	trailSpoofBlock = (spoofBlockStruct*)(kTrailerSpoofOffset + (Ptr)newTrailBlock);		
	curHeap->oldBackLimit = trailSpoofBlock;	/* set up the old back limit to point to 16 bytes after backLimit */
	trailSpoofBlock->size = kOldTrailerSize;	/* 0x10 */
	trailSpoofBlock->tagsFlagsSizeDelta = 0;	/* aw, just stuff nothing so there's nothing bizarre there */
	
	/* 8/30/93 3:28:18 AM (BET): check this again after some sleep... */
	/* copy tags, flags, and size adjust from old to new */
	((stdBlock3*)newTrailBlock)->tagsFlagsSizeDelta = ((stdBlock3*)oldTrailBlock)->tagsFlagsSizeDelta;

	/* nuke the old heap trailer block, update heap statistics */
	KillBlock(oldTrailBlock, curHeap);
	}


/*
 *	This routine does some checking before calling the core routine to move heapEnd upwards.
 *
 *	Note:	This routine should be called for app heap zones only or for the ProcessMgr
 *			zone when its "maxed out" so it can be flipped upside down.
 */
Boolean ExtendApplLimit(blockSize_t sizeNeeded, stdHeap* curHeap)
	{
	ptrBlock*	newTrailBlock;

	IfIntDebugMsg(LMGetApplZone() != curHeap, "ApplZone != curHeap", curHeap);

	/* We need to calculate the new end of the heap */
	sizeNeeded += kExtraAmountToExtendApplLimit;
	DbgCheckSize(sizeNeeded);
	
	/*
	 *	take the lowest limit as the new trail block. Being very careful to use 
	 *	unsigned arithmetic.
	 */
	newTrailBlock = (ptrBlock*)
		MIN(((ulong)(curHeap->backLimit) + sizeNeeded), (ulong)(LMGetApplLimit() - kTrailerBlockSize));

	/*
	 *	Note: the below AlignDown may not be needed if apps now call SetApplLimit instead
	 *	of poking the lowmem global directly.
	 */
	newTrailBlock = (ptrBlock*) AlignDown(newTrailBlock);
	
	if (newTrailBlock <= curHeap->backLimit)
		{
		curHeap->fHeapFullyExtended = 1;
		return false;
		}

	LMSetHeapEnd( (Ptr) newTrailBlock);
	ExtendHeapLimit(newTrailBlock, curHeap);
	return true;
	}


/*
 *	Scans circular double linked list looking for a free block. Starts at favored free. 
 *	As a side effect, if a block is found, favoredFree is set to that block. 
 *	If no block is found, it returns nil.
 */
static freeBlock* FindFreeBlock(blockSize_t reqBlockSize, stdHeap* curHeap);
static freeBlock* FindFreeBlock(blockSize_t reqBlockSize, stdHeap* curHeap)
	{
	freeBlock *startBlock;

	DbgCheckSize(reqBlockSize);
	
	/* get start block */	
	if (curHeap->fUseFirstFree)
		startBlock = curHeap->firstFree;
	else
		startBlock = curHeap->favoredFree;
		
	/* check start block, is it large enough */
	if (startBlock->size >= reqBlockSize)
		return startBlock;
		
	/* if the size is not great enough, forget it and bail right away */
	if (curHeap->totalFree >= reqBlockSize)
		{
		blockSize_t	savedStartBlockSize;
		freeBlock	*workBlock;

		/*
		 *	In the loop below, typically we would do 2 compares, one to see if we reached the
		 *	end and one to see if the size is large enough. We reduce this to 1 compare by 
		 *	stuffing the startBlockSize with reqBlockSize and only comparing sizes.
		 */
		savedStartBlockSize = startBlock->size;		/* save start block size */
		startBlock->size = reqBlockSize;			/* stuff reqBlockSize so loop terminates */
		workBlock = startBlock->nextFree;			/* start scan at next free block */

		/* loop searching for a free block that large enough */
		while (workBlock->size < reqBlockSize) 
			{
			workBlock = workBlock->nextFree;
			}

		/* either we found a block or we reached the end of the circular list */
		startBlock->size = savedStartBlockSize;			/* restore start block size */

		/* did we search all the way around to startBlock? (did the search fail?) */
		if (workBlock == startBlock)
			return nil;
		else
			return curHeap->favoredFree = workBlock;
		}
	else
		return nil;
	}

#if 0
This slower version is not used
static freeBlock* FindFreeBlock(blockSize_t reqBlockSize, stdHeap* curHeap);
static freeBlock* FindFreeBlock(blockSize_t reqBlockSize, stdHeap* curHeap)
	{
	DbgCheckSize(reqBlockSize);

	/* if the size is not great enough, forget it and bail right away */
	if (curHeap->totalFree >= reqBlockSize)
		{
		freeBlock *startBlock;
		freeBlock *workBlock;
		
		/* set start block according to flag in heap header */
		if (curHeap->heapFlags & kUseFirstFree)
			startBlock = curHeap->firstFree;
		else
			startBlock = curHeap->favoredFree;
			
		workBlock = startBlock;
		
		do 
			{
			if (workBlock->size >= reqBlockSize)
				return curHeap->favoredFree = workBlock;
			} 
		while ((workBlock=workBlock->nextFree) != startBlock);
		}
	return nil;
	}
#endif


#if 0
	/*
	 *	Below is code to implement chained GZ procs and code to implement chained
	 *	dispose procs. These features are not implemented and are commented out.
	 *	There is also support code in MemMgr.c & MakeSpace that is commented out as well.
	 */
	static freeBlock*	LoopCompactAndPurge(blockSize_t reqBlockSize, callBackNodePtr listItem, stdHeap* curHeap);
	static freeBlock*	LoopCompactAndPurge(blockSize_t reqBlockSize, callBackNodePtr listItem, stdHeap* curHeap)
		{
		freeBlock*	workBlock;
		
		/* list item starts out as the first item in the list */
		/* loop calling any chained grow zone procs that exist */
		do
			{
			FlushCacheIfNeeded(curHeap);
			DbgCheckHeap(curHeap);
	
			/* note: in calling the client back, s/he can change anything, except
				curHeap & reqBlockSize */
			if (0 == (CALL_FNC_PTR_1(GrowZoneProcPtr,listItem->proc,uppGrowZoneProcInfo, reqBlockSize)))
				{
				if (listItem = LLGetNextItem(listItem))
					continue;	/* there is another chained gz proc to call */
				else
					break;		/* no more chained gz procs to call */
				}
			
			if (workBlock = FindFreeBlock(reqBlockSize, curHeap))
				return workBlock;
	
			workBlock = CompactHeap(reqBlockSize,curHeap);	
			if (workBlock->size >= reqBlockSize)
				return workBlock;
	
			/* Is there enough space to consider a check for purging? */
			if (curHeap->totalPurgableSpace + curHeap->totalFree >= reqBlockSize)
				{
				/* purge and compact here */
				if (nil != (workBlock = PurgeAndMakeSpace(reqBlockSize, curHeap, false)))
					return workBlock;
				}
			}
		while (true);
		
		return nil;
		}
#endif


/*
 *	Tries to make space in the heap for the size and options. This is the standard
 *	allocation path for handles and blocks that are being relocated.
 *
 * Here is the general strategy for making space:
 *
 *	1. Try to fulfill the request with the given free blocks.
 *	2. Compact the heap if memory changed, search again.
 *	3. Try to extend the app zone. This is the classic MM way of growing the zone to ApplLimit. 
 *			Compact heap again if memory changed.
 *	4. Purge and compact resources, & search if needed.
 *	5. (not implemented) If any heap fragments already exist, see if they can be grown to accommodate the request.
 *	6. (not implemented) Allocate a new chuck from the ProcessMgr Heap, create a heap fragment.
 * 		6.a. Shrink System Heap if needed.
 * 		6.b. Collapse discontiguous heap fragments from other heaps.
 *  7. Call any system chained grow zone proc before client GZ.
 *  8. Repeatedly call app's GrowZoneProc (and compact) until it returns no more memory.
 *  9. Call any system chained grow zone proc after client GZ.
 * 10. Return nil.
 */
static freeBlock* MakeSpace(blockSize_t reqBlockSize, long options, stdHeap* curHeap);
static freeBlock* MakeSpace(blockSize_t reqBlockSize, long options, stdHeap* curHeap)
	{
	freeBlock* workBlock;
	
	DbgCheckSize(reqBlockSize);

	/* Is there enough space possible to find? */
	if (curHeap->totalFree >= reqBlockSize)
		{
		/* find a block and return it if found */
		if (workBlock = FindFreeBlock(reqBlockSize, curHeap))
			return workBlock;
		
		/* if we can't compact then bail right away */
		if (options & kDontCompact)
			return nil;
	
		/* compact and return it if found */
		workBlock = CompactHeap(reqBlockSize,curHeap);	
		if (workBlock->size >= reqBlockSize)
			return workBlock;
		}
	else
		{
		/* if we can't compact then bail right away */
		if (options & kDontCompact)
			return nil;
		}
	
	/* is this heap the application zone? Can it be extended? */
	if ((curHeap == LMGetApplZone()) && (!(curHeap->fHeapFullyExtended)))
		{
		/* extend the app zone here */
		if (ExtendApplLimit(reqBlockSize,curHeap))
			{
			/* we were able to extend the app zone, lets compact for space */
			if (workBlock = FindFreeBlock(reqBlockSize, curHeap))
				return workBlock;

			workBlock = CompactHeap(reqBlockSize,curHeap);	
			if (workBlock->size >= reqBlockSize)
				return workBlock;
			}
		}

	/*
	 *	As an optimization, if curHeap is the system heap, then we skip the purge 
	 *	sequence and move on to the grow zone procs. This will help since blocks
	 *	wont be purged if the system heap grows into the process mgr zone.
	 *
	 *	is it ok to purge? (ie. Is it not the System Zone?)
	 */
	if ((!(options & kDontPurge)) && !curHeap->fSkipPurgeBeforeGZ)
		{
		/* Is there enough space to consider a check for purging? */
		if (curHeap->totalPurgableSpace + curHeap->totalFree >= reqBlockSize)
			{
			/* purge and compact here */
			if (nil != (workBlock = PurgeAndMakeSpace(reqBlockSize, curHeap, false)))
				return workBlock;
			}
		}
	
	if (options  &  (kDontCallGZ + kDontPurge))
		{
		/* the client of this routine as asked not to call the GZ, so we bail */
		return nil;
		}


	#ifdef implemented_discontiguous_heaps
	/* is it ok to grow the heap discontiguously? */
	if (!(options & kDontCreateFragment))
		{
		/* grow heap fragments */
		
		/* create new heap fragment */
		}
	#endif


	#if 0
	/* commented out, chained GZ procs arent a feature of Figment */
	/* Do any chained gz procs want to jump in before the users gz proc? */		
	if (curHeap->earlyChainedGZProc)
		{
		if (workBlock = LoopCompactAndPurge(reqBlockSize, curHeap->earlyChainedGZProc, curHeap))
			return workBlock;
		}
	#endif

	/* repeatedly call apps growzone proc here */
	if (curHeap->gzProc)
		{
		Boolean triedOnceAlready = false;		/* true => we looped once trying to make space */

		/* loop calling the clients growzone proc */
		do
			{
			ulong		savedRegisterA5;
			blockSize_t	sizeWeGot;
			
			/*
			 *	call clients grow zone procedure, we subtract the blockHeaderSize to give
			 *	the clientSize back to the client. Its not exactly what they asked for, 
			 *	but its close enough.
			 */
			FlushCacheIfNeeded(curHeap);
			DbgCheckHeap(curHeap);
			
			/* save emulated register A5 since Wings and Resolve will trash it */
			savedRegisterA5 = GetRegA5();

			/* warning: in calling the client back, s/he can change anything, except curHeap & reqBlockSize */
			sizeWeGot = CALL_FNC_PTR_1(GrowZoneProcPtr,curHeap->gzProc,uppGrowZoneProcInfo, reqBlockSize);	
				
			/* restore Register A5 since Resolve or Wings may have trashed it */
			SetRegA5(savedRegisterA5);

			if (0 == sizeWeGot)
				{
				/*
				 *	We did not get anything back from the grow zone proc, we bail. Unless
				 *	we still need to purge blocks in heap that have the fSkipPurgeBeforeGZ
				 *	bit set (System Heap).
				 */
				if ((!curHeap->fSkipPurgeBeforeGZ) || (triedOnceAlready))
					{
					/* calling gz proc has failed, we bail out of this loop */
					break;
					}
					
				/*
				 *	If we got here, the GZProc has returned 0, but we have not yet tried
				 *	purging (in the System Heap).
				 */
				}
			else
				{
				/* Growzone returned something */
				
				if (workBlock = FindFreeBlock(reqBlockSize, curHeap))
					return workBlock;
	
				workBlock = CompactHeap(reqBlockSize,curHeap);	
				if (workBlock->size >= reqBlockSize)
					return workBlock;
				}

			triedOnceAlready = true;

			/* Is there enough space to consider a check for purging? */
			if (curHeap->totalPurgableSpace + curHeap->totalFree >= reqBlockSize)
				{
				/* purge and compact here */
				if (nil != (workBlock = PurgeAndMakeSpace(reqBlockSize, curHeap, false)))
					return workBlock;
				}
			}
		while (true);
		}
		
	#if 0
	/* commented out, chained GZ procs arent a feature of Figment */
	/* do any chained gz proc want to jump in after the users gz proc? */
	if (curHeap->lateChainedGZProc)
		{
		if (workBlock = LoopCompactAndPurge(reqBlockSize, curHeap->lateChainedGZProc, curHeap))
			return workBlock;
		}
	#endif

	/* to late, were outa here */
	return nil;
	}


/*
 *	This routine walks up the heap to check if it can make space as low as possible.
 *	If enough relocatables are found that jump-relocating them out of the way will make 
 *	space, then the routine returns kJumpRelocateBlocks and rangeEnd returns the 
 *	highestBlock to be jump relocated. 
 *	If enough freespace is found, such that blocks can be slide, then the routine 
 *	returns kSlideBlocksUp and rangeEnd points to the highest freeblock in the range. 
 *	If there is a non-relo followed by a freeBlock 
 *	large enough to satisfy the request, it returns kNoMovementRequired. I apologize for
 *	this nastiness but  I prefer to walk blocks as little as possible.  :(  :)
 * 	
 *	Note: lowestRemovableBlock is guarenteed to start in the main heap fragment for 
 *			discontiguous heaps. 
 *	
 *	Restated: This is the priority of heap configuation that this routine searches for: 
 *	
 *	1. A fixed block followed by a large enough free block.
 *	2. A fixed block followed by a continuous sequence of one or more blocks (free
 *		or floating) that can be successfully jump-relocated out of the way.
 *	3. A fixed block followed by a continuous sequence of blocks (free or floating)
 *		that can be slide up to make enough space low.
 *			
 *	If none of these 3 configurations exist, the routine returns nil and kCantFindSpace.
 */
static stdBlock* FindSpaceLow(stdBlock* startBlock, blockSize_t reqBlockSize, short* optionsOrResults, stdBlock** rangeEnd, stdHeap* curHeap);
static stdBlock* FindSpaceLow(	stdBlock*	workBlock,			/* start of search */
								blockSize_t	reqBlockSize, 
								short*		optionsOrResults,	/* options as an input, results as an output */
								stdBlock**	rangeEnd, 			/* end of range to relocate or slide */
								stdHeap*	curHeap)
	{
	stdBlock*		baseBlock = workBlock;		/* potential begining of area */
	blockSize_t		cumFreeSpace = 0;			/* accumulates freespace */
	blockSize_t		cumSpace = 0;				/* accumulates relocatable space + freeSpace */
	Boolean			afterFixedBlock = true;		/* true => this is a block after a fixed block */
	
	DbgCheckSize(reqBlockSize);
	*rangeEnd = workBlock;

	/* walk up to see if we have enough space */
	do
		{
		if (IsFixedBlock(workBlock))
			{
			/* make decision whether we can do it */
			IfIntDebugMsg(cumFreeSpace > reqBlockSize, 
				"cumFreeSpace > reqBlockSize, shouldn't be",cumFreeSpace);
			
			#ifdef implemented_discontiguous_heaps
			if (IsDeadBlock(workBlock) || IsTrailerBlock(workBlock))
			#else
			if (workBlock == curHeap->backLimit)
			#endif
				{
				/* end of main fragment reached, no luck, search has failed */
				*optionsOrResults = kCantFindSpace;
				return nil;
				}
			else
				{
				/* space was not good enough, move on to next region */
				if (*optionsOrResults)			/* (*optionsOrResults != kFirstRegionOnly) */
					{
					/* continue on */
					baseBlock = GetNextBlock(workBlock);
					cumFreeSpace = cumSpace = 0;
					}
				else
					{
					/* we scanned one region, not enough space found, lets bail */
					*optionsOrResults = kCantFindSpace;
					return nil;
					}
				}
			afterFixedBlock = true;
			}
		else
			{
			/* common code path for free blocks and relocatable blocks */
			
			/* is this block free? */
			if (!IsHandleBlock(workBlock))
				{
				/* accumulate free space now, we'll use it later */
				cumFreeSpace += workBlock->size;
				
				/* check for noMovementRequired */
				if (afterFixedBlock && workBlock->size >= reqBlockSize)
					{
					*optionsOrResults = kNoMovementRequired;
					return workBlock;
					}
				}
			
			/* add to cumSpace, do we have enough to satisfy the request? */
			if ((cumSpace += workBlock->size) >= reqBlockSize)
				{
				/*
				 *	To jump relocate blocks, the relocatable blocks in the range must 
				 *	have enough space to find a new home. Here's the algebra:
				 *
				 *  note: freeSpaceInRange = cumFreeSpace
				 *
				 *	totalFree - cumFreeSpace >= relocatableSpaceInRange
				 *	totalFree >= relocatableSpaceInRange + cumFreeSpace
				 *	totalFree >= (cumSpace - cumFreeSpace) + cumFreeSpace
				 *	totalFree >= cumSpace
				 */
				if (curHeap->totalFree >= cumSpace)
					{
					/* we now have enough space to relocate blocks */
					*rangeEnd = workBlock;
					*optionsOrResults = kJumpRelocateBlocks;

					/* is the block free? */
					if (!IsHandleBlock(workBlock))
						{
						/* did we find enough to satisfy the request? */
						if (cumFreeSpace >= reqBlockSize)
							{
							/*
							 *	At this point, we could either jump relocate blocks (preferred)
							 *	or slide them up. Since JumpRelocateRange can fail, we have an
							 *	alternative that is garenteed to work.
							 */
							*optionsOrResults = kJumpRelocateOrSlideBlocks;
							}
						}
					return baseBlock;
					}
				}

			/* is the block free? */
			if (!IsHandleBlock(workBlock))
				{
				/* did we find enough to satisfy the request? */
				if (cumFreeSpace >= reqBlockSize)
					{
					*rangeEnd = workBlock;
					*optionsOrResults = kSlideBlocksUp;
					return baseBlock;
					}
				}
			afterFixedBlock = false;
			}
		workBlock = GetNextBlock(workBlock);
		}
	while (true); 
	}


/* This routine does what it says. note: this routine does NOT set totalPurgableSpace */
static void PurgeAndOccupyBlock(handleBlock* workBlock, stdHeap* curHeap);
static void PurgeAndOccupyBlock(handleBlock* workBlock, stdHeap* curHeap)
	{
	Handle	pMP = (Handle) (workBlock->relHandle + (long)curHeap);

	/* call the classic purge warning proc */
	if (curHeap->purgeProc)
		{
		FlushCacheIfNeeded(curHeap);
		/*
		 *	warning: we make the assumption that the client will not allocate 
		 *	memory in the heap inside the purge procedure.
		 *
		 *	note: Cant do a DbgCheckHeap here since the heap is invalid.
		 */
		CALL_FNC_PTR_1(PurgeProcPtr,curHeap->purgeProc,uppPurgeProcInfo, pMP);
		}

	/* set MP to point to nil */
	*pMP = nil;

	DbgCode(curHeap->totalDelta -= (long) workBlock->sizeDelta);
	IfDbgMsg(curHeap->handleBlocks-- < 0,"corrupt header", curHeap);

	/*
	 *	we need to set the size delta and heapID to keep the heap correct. This is
	 *	important when jump relocating a range of blocks and the grow 
	 *	zone or purge proc gets called later on.
	 *
	 *	set tags=ptrType, mpFlags=privBlockType, heapID=CurHeapID, sizeDelta=kMinDelta;
	 */
	JamTagsFlagsAndSizeDelta(workBlock,
		((ulong)ptrType << 24) + ((ulong)privBlockType << 16) + kMinDelta);
	DbgSetBlockHeapID(workBlock, curHeap);
	
	/* since its now a ptrBlock */
	((ptrBlock*)workBlock)->parent = curHeap;
	}


/*
 *	Walks blocks in the range relocating them. Returns pointer to free space if blocks 
 *	moved out ok. It assumes there are no non relocatable blocks in the range.
 *
 *	It accomplishes this feat by marking all blocks in the range as busy. Then allocating
 *	a new block for each handle block in the range. This routine walks from the top of
 *	the range DOWN to the bottom by dereferencing each blocks back pointer. If this
 *	routine fails, some of the high blocks in the range will have already been relocated.
 *	Others will essentially be left untouched.
 *
 *	notes:
 *	1) Unlike his cousins (SlideBlocksUp and SlideBlocksDown), JumpRelocateRange
 *		can indeed fail.
 *	2) Unlike his brother (JumpRelocateBlock), JumpRelocateRange does not call
 *		the clients growzone proc. Callers of this routine must do that themselves.
 *	3) On entry, all blocks in the range must be either handleblocks or free blocks.
 *	4) No need to pass reqBlockSize into this routine. That should already be determined
 *		by the caller.
 *	5) Still have to pass options into this routine since some clients (MoveHHi) of this
 *		routine may want to purge blocks.
 *
 *	Warning:	This routine can change the contents of rangeEnd. Callers of this routine
 *				must not depend of rangeEnd being valid after this call.
 */
static freeBlock* JumpRelocateRange(stdBlock* rangeStart, stdBlock* rangeEnd, long options, stdHeap* curHeap);
static freeBlock* JumpRelocateRange(stdBlock* rangeStart, stdBlock* rangeEnd, long options, stdHeap* curHeap)
	{
	stdBlock*		workBlock;
	handleBlock*	destBlock;
	#ifdef debugging
	long			handleBlockCount;		/* record the number of blocks that get relocated */
	long			cumSizeDelta;
	#endif
	Boolean			canBePurged;			/* true => handle can be purged */
	
	IfIntDebugMsg(options & kDirectionMask != 0, "expecting kAllocateFastOption",options);
	
	/*
	 *	We dont want to call cleint's growzone. Why you ask? Because the heap could be in
	 *	transition when the growzone proc gets called. Inside the gzProc, a client could 
	 *	do anything like disposing of some of the blocks in the range, therebye destroying 
	 *	structure of the heap. As a result callees of this routine must code for the case
	 *	where this routine fails and call the growzone one thier own.
	 */
	options |= kDontCallGZ;

	/* since we will move blocks, we should flush the instruction cache */
	MarkCacheNeedsToBeFlushed(curHeap);

	#ifdef debugging
		cumSizeDelta = 0;
		handleBlockCount = 0;
	#endif

	/*
	 *	walk all the blocks in the range marking handle blocks as non relocatable and 
	 *	temporarily allocating free blocks to take them off the free list. Note, all
	 *	blocks in this range are free or relocatable.
	 */
	workBlock = rangeEnd;
	while (workBlock >= rangeStart)
		{
		IfIntDebugMsg(IsFixedBlock(workBlock), "not expecting non-reloc block", workBlock);

		if (IsHandleBlock(workBlock))
			{
			workBlock->ptrBit = 1;		/* mark handle as busy by setting the non-rel bit */
			
			/* decrease totalPurgableSpace since it wont be available for NewBlock() */
			if (IsUnlockedPurgableHandle(workBlock))
				curHeap->totalPurgableSpace -= workBlock->size;
			}
		else
			OccupyFreeSpace((freeBlock*)workBlock,curHeap);	/* take free block off the freelist */
			
		workBlock = workBlock->back;
		}
			
	/*
	 *	walk the range of blocks finding a new home for each one, the new destination for
	 *	the block is gaurenteed not to be in the range since there are no free blocks 
	 *	in the range and we use the kAllocateFast option to NewBlock
	 */
	workBlock = rangeEnd;
	while (workBlock >= rangeStart)
		{
		blockSize_t		newBlockSize;
		blockSize_t		clientDataCopySize;

		/* is this a block we want to jump relocate? */
		if (IsHandleBlock(workBlock))
			{
			/* calc newBlockSize and clientDataCopySize */
			clientDataCopySize = (newBlockSize = workBlock->size) - kBlockHeaderSize;
			
			/*
			 *	Time to trim some fat. If the block we are moving has some recoverable delta,
			 *	we can make the size of the new location smaller. This will reduce internal
			 *	fragmentation and prevent it from overflowing the 8 bit quantity in the sizeDelta field.
			 *
			 *	Note:	Must make sure not to shrink the block to be less than kMinBlockSize.
			 *			This happens without debugging, without small_FreeBlockHeaders
			 *			and with quadLongWordAligned. Ideally the test should be:
			 *				sizeDelta >= (kAlignmentFactor + kMagicSize + kBackPtrSize)
			 *								AND
			 *				physicalBlockSize >= kMinFreeBlockSize - kAlignmentFactor
			 *
			 *			Since the 2nd test implies sizeDelta is only a little larger than the 1st,  
			 *			we can simply compare against the larger even though it means we won't 
			 *			always be trimming optimally. So, to make the test fast, we just test for:
			 *				sizeDelta > (kAlignmentFactor + kMagicSize + kBackPtrSize)
			 *
			 *	Do we have some size delta we can recover?
			 */
			#ifdef small_freeBlock_headers
				if (workBlock->sizeDelta >= kAlignmentFactor + kMagicSize + kBackPtrSize)
			#else
				if (workBlock->sizeDelta > kAlignmentFactor + kMagicSize + kBackPtrSize)
			#endif
				{
				/* reduce internal fragmentation, of the relocated block. */
				newBlockSize -= kAlignmentFactor;
				clientDataCopySize -= kAlignmentFactor; 
				}
			
			/*
			 *	create new area, if we are making space for a purgable block, don't bother
			 *	purging other blocks to make space for it.
			 */
			canBePurged = IsPurgableHandle(workBlock) && IsUnlockedHandle(workBlock);
			
			/*
			 *	we call NewBlock, but suppress calls to the growzone proc. Also, if the block 
			 *	we are moving is purgable, dont purge other blocks to move it.
			 */
			destBlock = (handleBlock*)
				NewBlock(newBlockSize, canBePurged ? options | kDontPurge : options, curHeap);

			if (!destBlock)
				{
				if (canBePurged)
					{
					PurgeAndOccupyBlock((handleBlock*)workBlock, curHeap);
					
					workBlock = workBlock->back;
					continue;
					}
				else
					{
					/* error occured while jump relocating blocks, we now have to clean 
						up our mess (3 steps)  and get out */
					stdBlock* tempBlock = rangeEnd;
					
					/* step 1, clear all busy bits in the range for handles */
					while (tempBlock >= rangeStart)
						{
						if (IsHandleBlock(tempBlock))
							{
							tempBlock->ptrBit = 0;			/* mark non-busy, clear non-relo bit */
							
							/* are we adding a block back to total purgable space? */
							if (IsUnlockedPurgableHandle(tempBlock))
								curHeap->totalPurgableSpace += tempBlock->size;
							}
						tempBlock = tempBlock->back;
						}
						
					/* step 2, dispose of blocks that have already been relocated or temporarily
						allocated (using OccupyFreeSpace) */
					tempBlock = rangeEnd;
					while (tempBlock >= rangeStart)
						{
						if (tempBlock > workBlock || IsPtrBlock(tempBlock))
							{
							#ifdef debugging
								if (IsHandleBlock(tempBlock))
									{
									curHeap->handleBlocks--;
									curHeap->totalDelta -= tempBlock->sizeDelta;
									}
							#endif
							tempBlock = (stdBlock*) KillBlock(tempBlock, curHeap);
							}
						tempBlock = tempBlock->back;
						}
						
					/* step 3, get out with our tail between our legs */	
					return nil;
					}
				}
			
			/* record the fact that a handle is created */
			DbgCode(curHeap->handleBlocks++);
			DbgCode(handleBlockCount++);
			DbgCode(curHeap->totalDelta += workBlock->sizeDelta);
			DbgCode(cumSizeDelta += workBlock->sizeDelta);

			/* update heap statistics */
			DbgCode(curHeap->bytesMoved += newBlockSize);
			DbgCode(curHeap->totalBlocksMoved++);
			DbgCode(curHeap->bytesJumped += newBlockSize);

			/* copy contents from old block to new block */
			MoveBytes(workBlock->data,destBlock->data, clientDataCopySize);

			/* copy tags, flags, heapID, and sizeDelta to new location */
			((stdBlock3*)destBlock)->tagsFlagsSizeDelta = ((stdBlock3*)workBlock)->tagsFlagsSizeDelta;
		
			/* Since the sizeDelta may have changed from old to new, we must correct it */
			/* 8/30/93 3:24:19 AM (BET): make this more readable (and more efficient) */
			destBlock->sizeDelta += destBlock->size - workBlock->size;
				
			/* update the master pointer to point to new location */
				{
				Handle pMP = (Handle) (((handleBlock*) workBlock)->relHandle + (long) curHeap);
				*pMP = (Ptr) destBlock->data;
				}

			/* update destBlock's relative handle to point to the MP */
			destBlock->relHandle = ((handleBlock*)workBlock)->relHandle;
							
			/* clear busy bit of new block */
			destBlock->ptrBit = 0;
			
			if (canBePurged)
				{
				/* increment totalPurgableSpace for the newly created block */
				curHeap->totalPurgableSpace += destBlock->size;
				}

			/* Debug Stuff */
			#ifdef debugging
				{
				if (workBlock->size != destBlock->size)					
					{
					curHeap->totalDelta += destBlock->sizeDelta - workBlock->sizeDelta;
					}
				}
			#endif		
			}
		workBlock = workBlock->back;
		}
		
	/* we have now found a new home for all handle blocks in the range */
	/* We now create one large block and free it up */
	workBlock = GetNextBlock(rangeEnd);
	rangeStart->size = (char*)rangeEnd - (char*)rangeStart + rangeEnd->size;
	workBlock->back = rangeStart;
		
	#ifdef debugging
		/* we need to subtract how many handle blocks we are disposing from the heap */
		IfDbgMsg((curHeap->handleBlocks-= handleBlockCount) < 0,"corrupt handle block count", curHeap);
		curHeap->totalDelta -= cumSizeDelta;
	#endif
	
	/* adjust the total size delta for this block we dispose */
	return KillBlock(rangeStart, curHeap);
	}


/*
 *	This simple routine walks a range to find the endBlock such that SlideBlocks up 
 *	will work.
 *
 *	Assumption: the range is already large enough such that sliding blocks up will
 *	work correctly.
 */
static stdBlock* RecoverEndBlock(stdBlock* workBlock, blockSize_t reqBlockSize);
static stdBlock* RecoverEndBlock(stdBlock* workBlock, blockSize_t reqBlockSize)
	{
	/* on entry, workBlock is at the beginning of the range, on exit, its at the end */
	blockSize_t	cumFreeSpace = 0;
	
	do
		{
		if (IsFreeBlock(workBlock))
			{
			if ((cumFreeSpace += workBlock->size) > reqBlockSize)
				break;
			}
		
		/* there should be enough space in this region */
		IfIntDebugMsg(IsFixedBlock(workBlock), "reached fixed block, did not expect it", workBlock);

		workBlock = GetNextBlock(workBlock);
		}
	while (true);
	
	return workBlock;
	}

	
/*
 *	Make space low in the heap as possible using the requested size. In general this 
 *	is a two step process. Find the right space to use, create the space by moving
 *	others out of the way.
 */
freeBlock* MakeSpaceLow(blockSize_t reqBlockSize, long options, stdHeap* curHeap)
	{
	stdBlock*	workBlock = curHeap->lowestRemovableBlock;
	stdBlock*	endBlock;
	short		result;
	Boolean		calledMakeSpaceOnce = false;
	Boolean		calledGZProc = false;
	
	DbgCheckSize(reqBlockSize);
	IfIntDebugMsg(!((options & kDirectionMask) == kAllocateLow),
		"kAllocateLow option not set", options);

	while (true)
		{
		result = kContinueUntilRegionFound;	/* tell FindSpaceLow to keep on searching */
		if (nil == (workBlock = (stdBlock*) FindSpaceLow(workBlock, reqBlockSize, &result, &endBlock, curHeap)))
			{
			/*
			 *	Unable to find enough space in the heap. We call MakeSpace here to 
			 *	get more space through these possiblities, 1) heap compaction,
			 *	2) extending the heap limit, 4) create heap fragment, 5) calling
			 *	the client's grow zone proc.
			 */
			FlushCacheIfNeeded(curHeap);
			DbgCheckHeap(curHeap);
			if (!calledMakeSpaceOnce)
				{
				/* 10/14/93 1:25:27 PM (BET): Can't clear other flags by '&'ing with kDirectionMask */
				if (MakeSpace(reqBlockSize, options, curHeap))
					{
					/*
					 *	we got enough space, let's restart the scan from the bottom. A less
					 *	sophisticated memory manager could return the space from MakeSpace, 
					 *	but this free block is not necessarily low.
					 */
					workBlock = curHeap->lowestRemovableBlock;
					calledMakeSpaceOnce = true;
					continue;
					}
				}

			/* can't find enough space, we bail */
			return nil;
			}
		
		/* this switch can be tuned */
		switch (result)
			{
			case kNoMovementRequired:
					return (freeBlock*)workBlock;
					break;
	
			case kSlideBlocksUp:
					return SlideBlocksUp(workBlock, (freeBlock*)endBlock, curHeap);
					break;
	
			case kJumpRelocateBlocks:
			case kJumpRelocateOrSlideBlocks:
					{
					stdBlock*	savedWorkBlock = workBlock;		/* in case JumpRelocateRange fails */
					
					options &= ~kDirectionMask;					/* options = kAllocateFast plus other options */
					if (workBlock = (stdBlock*)JumpRelocateRange(workBlock, endBlock, options, curHeap))
						{
						/* we successfully moved blocks out of the way */
						return (freeBlock*) workBlock;
						}
					else
						{
						if (result == kJumpRelocateOrSlideBlocks)
							{
							/*
							 *	since JumpRelocateRange can change endBlock, we need to 
							 *	recover it now to pass it to SlideBlocksUp. Since
							 *	JumpRelocateRange could have moved endBlock (by coelescing 
							 *	freeblocks), we need to walk the range and get it back.
							 *
							 *	note: an alternative way to solve this problem is to 
							 *	return yet another parameter from FindSpaceHigh (that 
							 *	would be endBlockToUseWhenSliding). But since this particular
							 *	code path almost never taken, we walk the range again
							 *	and find it manually.
							 */
							endBlock = RecoverEndBlock(savedWorkBlock, reqBlockSize);

							/* SlideBlocksUp always works so we do it now since JumpRelocateRange failed. */
							return SlideBlocksUp(savedWorkBlock, (freeBlock*)endBlock, curHeap);
							}
						/*
						 *	could not relocate blocks, continue search again after the
						 *	current range. Lets advance to the next boundary.
						 */
						workBlock = savedWorkBlock;
						
						/* scan until a fixed block is found */
						do
							{
							workBlock = GetNextBlock(workBlock);
							}
						while(!IsFixedBlock(workBlock));
						
						/* Did we scan all the way back to the end of the heap? */
						/* 12/16/93 7:25:07 PM (BET): if so, and we keep getting jumpRelo, call the GZ first. */
						if (workBlock == curHeap->backLimit) {							
							if (calledGZProc || (options & kDontCallGZ))
								return nil;
							else {
								ulong		savedRegisterA5;
								blockSize_t	sizeWeGot;
								
								calledGZProc = true;
								
								/* save emulated register A5 since Wings and Resolve will trash it */
								savedRegisterA5 = GetRegA5();
					
								/* warning: in calling the client back, s/he can change anything, except curHeap & reqBlockSize */
								sizeWeGot = CALL_FNC_PTR_1(GrowZoneProcPtr,curHeap->gzProc,uppGrowZoneProcInfo, reqBlockSize);	
									
								/* restore Register A5 since Resolve or Wings may have trashed it */
								SetRegA5(savedRegisterA5);
								
								if (!sizeWeGot)
									return nil;
									
								/* start over on the search, we might find something way low now */
								workBlock = curHeap->lowestRemovableBlock;
								}
							}
						}
					}
					break;
					
			#ifdef internal_debugging	
			default:
					Debugger();
			#endif
			}
		}
	}


/*
 *	Similar to FindSpaceLow. Finds the highest available space for a requested size.
 *	This routine walks blocks down starting high, (ie.- from the top of the heap)
 *
 *	Restated: This is the priority of heap configurations that this routine searches for: 
 *	
 *	1. A fixed block preceded by a large enough free block.
 *	2. A fixed block preceded by a continuous sequence of blocks (free or floating)
 *	that can be slide down to make enough space high.
 *	3. A fixed block preceded by a continuous sequence of one or more blocks (free
 *		or floating) that can be successfully jump-relocated out of the way.
 *		
 *	If none of these 3 configurations exist, the routine returns nil and kCantFindSpace.
 *	
 *	Part of the reason that differs from its counterpart (FindSpaceLow) is that it tries to 
 *	slide blocks before jump relocating them.
 *
 *	note: this routine is called by ShrinkSysHeap to lower the Sys/PM heap boundary
 */
static stdBlock* FindSpaceHigh(stdBlock* startBlock, blockSize_t reqBlockSize, short* optionsOrResults, stdBlock** rangeEnd, stdHeap* curHeap);
static stdBlock* FindSpaceHigh(	stdBlock*	workBlock,	/* search starts here */
								blockSize_t	reqBlockSize, 
								short*		optionsOrResults, 
								stdBlock**	rangeEnd, 	/* end of range to slide or relocate */
								stdHeap*	curHeap)
	{
	stdBlock*		rangeBegin = workBlock;		/* beginning of range for jump relocating blocks */
	blockSize_t		cumFreeSpace = 0;			/* accumulates freespace */
	blockSize_t		cumSpace = 0;				/* accumulates relocatable space + freeSpace */
	Boolean			afterFixedBlock = true;		/* true => the block above was locked */
	Boolean			okToRelocate = false;		/* true => we found enough space to jump relocate */
	
	DbgCheckSize(reqBlockSize);
	
	*rangeEnd = workBlock;

	/* walk down to see if we have enough space */
	do
		{
		if (IsFixedBlock(workBlock))
			{
			/* make decision whether we can do it */
			IfIntDebugMsg (cumFreeSpace > reqBlockSize, 
				"cumFreeSpace > reqBlockSize, shoudn't be",cumFreeSpace);
			
			if (okToRelocate)
				{
				/*
				 *	We have found enough relocatable space to make way for a new block.
				 *	Now is there enough extra free space to find a new home for the 
				 *	relocatable space?  See algebra in FindSpaceLow for this calculation.
				 *
				 *	We also check to see if we are scanning for the first region only.
				 *	Since the totalFree test does not include purgable space. This
				 *	test enables the ShrinkSysHeap feature to work with purgable blocks.
				 */
				if ( (curHeap->totalFree >= ((char*)*rangeEnd - (char*)rangeBegin + (*rangeEnd)->size)) ||
						(*optionsOrResults == kFirstRegionOnly) )
					{
					/* yes there is enough space, tell caller to relocate blocks */
					*optionsOrResults = kJumpRelocateBlocks;
					return rangeBegin;
					}
				}
			
			/* have we reached the start of the heap? */
			if (workBlock == curHeap->heapStart)
				{
				/* front of heap reached, no luck, search has failed */
				*optionsOrResults = kCantFindSpace;
				return nil;
				}
			else
				{
				if (*optionsOrResults)			/* (*optionsOrResults != kFirstRegionOnly) */
					{
					/* continue on with next region */
					*rangeEnd = workBlock->back;
					cumFreeSpace = cumSpace = 0;
					}
				else
					{
					/* we scanned just one region, can't find space, we bail */
					*optionsOrResults = kCantFindSpace;
					return nil;
					}
				}
			afterFixedBlock = true;
			IfIntDebugMsg((void*)workBlock < curHeap->heapStart, "walked past the front of the heap", workBlock);
			}
		else
			{
			/* common code path for free blocks and relocatable blocks */
			
			/* add cumSpace, do we have enough to satisfy the request? */
			if (((cumSpace += workBlock->size) >= reqBlockSize) && (!okToRelocate))
				{
				/* we now have enough space to relocate blocks */
				/* this becomes the end of the range if kJumpRelocateBlocks is returned */
				rangeBegin = workBlock;
				okToRelocate = true;
				}

			/* is this block free? */
			if (!IsHandleBlock(workBlock))
				{
				if (afterFixedBlock && workBlock->size >= reqBlockSize)
					{
					*optionsOrResults = kNoMovementRequired;
					return workBlock;
					}
					
				/* add cumFreeSpace, did we find enough to satisfy the request? */
				if ((cumFreeSpace += workBlock->size) >= reqBlockSize)
					{
					*optionsOrResults = kSlideBlocksDown;
					return workBlock;
					}
				}
				
			afterFixedBlock = false;
			}
		
		workBlock = workBlock->back;	/* march workBlock down */
		}
	while (true);
	}


/*
 *	Similar to MakeSpaceLow. Will make the highest available space to 
 *	put block. It will slide blocks or relocated them if needed.
 */
freeBlock* MakeSpaceHigh(blockSize_t reqBlockSize, long options, stdHeap* curHeap)
	{
	stdBlock*	workBlock = curHeap->backLimit->back;
	stdBlock*	endBlock;
	short		findSpaceResult;
	Boolean		calledMakeSpaceOnce = false;
	Boolean		calledGZProc = false;
	
	DbgCheckSize(reqBlockSize);
	IfIntDebugMsg(!((options & kDirectionMask) == kAllocateHigh),
		"kAllocateHigh option not set", options);

	while (true)
		{
		/* convert searching options into FindSpace options */
		findSpaceResult = (options & kNumberOfRegionsMask) >> 24;
		if ((workBlock = (stdBlock*) FindSpaceHigh(	workBlock,
													reqBlockSize, 
													&findSpaceResult, 
													&endBlock, 
													curHeap)) == nil)
			{
			/*	Unable to find enough space in the heap. Check to see that we want to 
			 *	search only once. This happens when the ProcessMgr is shrinking the 
			 *	system heap.
			 */
			if (!(options & kDoContinueUntilRegionFound))
				return nil;

			/*	We call MakeSpace here to get more space through these possiblities, 
			 *	1) heap compaction, 2) extending the heap limit, 4) create heap fragment,
			 *	5) calling the client's grow zone proc.
			 */
			FlushCacheIfNeeded(curHeap);
			DbgCheckHeap(curHeap);
			if (!calledMakeSpaceOnce)
				{
				/* 10/14/93 1:25:27 PM (BET): Can't clear other flags by '&'ing with kDirectionMask */
				if (MakeSpace(reqBlockSize, options, curHeap))
					{
					/*
					 *	we got enough space, let's restart the scan from the top. A less
					 *	sophisticated memory manager could return the space from MakeSpace, 
					 *	but this free block is not necessarily high.
					 */
					workBlock = curHeap->backLimit->back;
					calledMakeSpaceOnce = true;
					continue;
					}
				}
				
			/* can't get enough space, we bail */
			return nil;
			}
		
		/* this switch can be tuned */
		switch (findSpaceResult)
			{
			case kNoMovementRequired:
					return (freeBlock*)workBlock;
					break;
	
			case kSlideBlocksDown:
					return SlideBlocksDown((freeBlock*)workBlock, endBlock, curHeap);
					break;
	
			case kJumpRelocateBlocks:
					{
					stdBlock*	savedWorkBlock = workBlock;			/* in case JumpRelocateRange fails */

					options &= ~kDirectionMask;						/* options = kAllocateFast plus other options */
					if (workBlock = (stdBlock*)JumpRelocateRange(workBlock, endBlock, options, curHeap))
						return (freeBlock*) workBlock;
					else
						{
						/* could not relocate blocks, continue search again after
							current range. Lets find the next boundary. */
						workBlock = savedWorkBlock;
						
						/* scan until a fixed block is found */
						do
							{
							workBlock = workBlock->back;
							}
						while(!IsFixedBlock(workBlock));
						
						/*
						 *	Did we scan all the way back to the end of the heap?
						 *	note: there is always a fixed block at the beginning of the heap.
						 */
						/* 12/16/93 7:25:07 PM (BET): if so, and we keep getting jumpRelo, call the GZ first. */
						if (workBlock == ((stdBlock*)curHeap->lowestRemovableBlock)->back) {							
							if (calledGZProc || (options & kDontCallGZ))
								return nil;
							else {
								ulong		savedRegisterA5;
								blockSize_t	sizeWeGot;
								
								calledGZProc = true;
								
								/* save emulated register A5 since Wings and Resolve will trash it */
								savedRegisterA5 = GetRegA5();
					
								/* warning: in calling the client back, s/he can change anything, except curHeap & reqBlockSize */
								sizeWeGot = CALL_FNC_PTR_1(GrowZoneProcPtr,curHeap->gzProc,uppGrowZoneProcInfo, reqBlockSize);	
									
								/* restore Register A5 since Resolve or Wings may have trashed it */
								SetRegA5(savedRegisterA5);
								
								if (!sizeWeGot)
									return nil;
									
								/* start over on the search, we might find something way low now */
								workBlock = curHeap->backLimit->back;
								}
							}
						}
					break;
					}
					
			#ifdef internal_debugging	
			default:
					Debugger();
			#endif
			}
		}
	}


/*
 *	Shrinks a heap by lowering curHeap->backLimit. Currently does not set HEAPEND. 
 *	This routine depends on the next to last block being free and large enough
 *	to shrink the heap.
 */
void ShrinkHeapLimit(blockSize_t sizeToReduce, stdHeap* curHeap)
	{
	freeBlock*	topFreeBlock = curHeap->backLimit->back;
	ptrBlock*	deadBlock;
	spoofBlockStruct* trailSpoofBlock;

	/* Danger Will Robinson: since this routine is only call to shrink the system
		heap, the top free block will be more than adequate. But if the top free
		block is just big enough such that it now need to be removed, we have 
		problems. */
	DbgCheckSize(sizeToReduce);
	IfIntDebugMsg(!IsFreeBlock(topFreeBlock),"top block not free",topFreeBlock);
	IfIntDebugMsg(topFreeBlock->size <= sizeToReduce,"top block not large enough",topFreeBlock);
	
	/* topFreeBlock points to a free block at the (almost) very top of the system
	 * zone, and the block size is at least as big as caller asked for.  Reduce that
	 * free block by the surplus, and create a new zone trailer block immediately
	 * following it.  Update zone header appropriately.
	 */
	topFreeBlock->size -= sizeToReduce;
	deadBlock = curHeap->backLimit = GetNextBlock(topFreeBlock);

	trailSpoofBlock = (spoofBlockStruct*)(kTrailerSpoofOffset + (Ptr)deadBlock);		/* maintain oldbackLimit */
	curHeap->oldBackLimit = trailSpoofBlock;	/* set up the old back limit to point to 16 bytes after backLimit */
	
	trailSpoofBlock->size = kOldTrailerSize;	/* 0x10 */
	trailSpoofBlock->tagsFlagsSizeDelta = 0;	/* aw, just stuff nothing so there's nothing bizarre there */
	
	deadBlock->size = kOldHeaderSize;		/* offset to spoof trailer */

	deadBlock->back = topFreeBlock;
	MarkBlockAsPrivate(deadBlock, trailerBlockType, curHeap);
	curHeap->totalFree -= sizeToReduce;
	}


/*
 *	We consume the amount of space needed. If there is none left over, we consume the
 *	whole thing. If there is space left over, we eat the low space and leave the 
 *	rest free.
 */
static stdBlock* ConsumeFreeSpaceLow(freeBlock* oldFreeBlock, blockSize_t newBlockSize, stdHeap* curHeap);
static stdBlock* ConsumeFreeSpaceLow(	freeBlock*		oldFreeBlock,
										blockSize_t		newBlockSize, 
										stdHeap*			curHeap)
	{
	blockSize_t remainder;

	DbgCheckSize(newBlockSize);
	IfIntDebugMsg(!IsFreeBlock(oldFreeBlock),"block not free", oldFreeBlock);
	IfIntDebugMsg(newBlockSize > oldFreeBlock->size,"did not find large enough block", oldFreeBlock);

	if ((remainder = oldFreeBlock->size - newBlockSize) >= kMinFreeSplitSize)
		{
		/* split available space into 2 blocks */
		freeBlock*	newFreeBlock;
		
		DbgCheckSize(remainder);
		newFreeBlock = (freeBlock*) ((Ptr)oldFreeBlock + newBlockSize);
		SetFreeChain(newFreeBlock, oldFreeBlock->prevFree, oldFreeBlock->nextFree);
		newFreeBlock->back = oldFreeBlock;
		newFreeBlock->size = remainder;
		
		#ifndef small_freeBlock_headers
		/* set tags, mpFlags, heapID, sizeDelta to 0 */
		((stdBlock3*)newFreeBlock)->tagsFlagsSizeDelta = 0; 
		#endif
		
		oldFreeBlock->size = newBlockSize;
		
		/* mike's better way of doing it */
		BACK((stdBlock*)GetNextBlock(newFreeBlock)) = newFreeBlock;
		if (oldFreeBlock == curHeap->favoredFree)
			curHeap->favoredFree = newFreeBlock;
		}
	else 
		{  
		/* this free block is replaced entirely by the allocated block */
		DbgCheckSize(remainder);
		newBlockSize = oldFreeBlock->size;
		RemoveFromFreeChain(oldFreeBlock, curHeap);		/* favoredFree is set */
		DbgCode(curHeap->freeBlocks--);
		}
	
	/* fix up heap header */
	curHeap->totalFree -= newBlockSize;

	/* note: heap totalFree invalid until caller sets the new block's type non-free */
	IfIntDebugMsg(curHeap->totalFree < 0, "bad free total", curHeap);
	DbgCode(curHeap->totalBytesAllocated += newBlockSize);
	
	return (stdBlock*)oldFreeBlock;
	}


/*
 *	Similar to ConsumeFreeSpaceLow, except it takes space out of the upper portion of the
 *	free block instead of the lower portion.
 */
static stdBlock* ConsumeFreeSpaceHigh(freeBlock* oldFreeBlock, blockSize_t newBlockSize, stdHeap* curHeap);
static stdBlock* ConsumeFreeSpaceHigh(	freeBlock*		oldFreeBlock,
										blockSize_t		newBlockSize, 
										stdHeap*		curHeap)
	{
	blockSize_t remainder;
	stdBlock*	newBlock;

	DbgCheckSize(newBlockSize);
	IfIntDebugMsg(!IsFreeBlock(oldFreeBlock),"block not free", oldFreeBlock);
	IfIntDebugMsg(newBlockSize > oldFreeBlock->size,"did not find large enough block", oldFreeBlock);

	if ((remainder = oldFreeBlock->size - newBlockSize) >= kMinFreeSplitSize)
		{
		/* split available space into 2 blocks, don't set favoredFree */
		DbgCheckSize(remainder);
		oldFreeBlock->size = remainder;
		newBlock = GetNextBlock(oldFreeBlock);
		newBlock->back = oldFreeBlock;
		newBlock->size = newBlockSize;
		((stdBlock*)GetNextBlock(newBlock))->back = newBlock;	/* reset back ptr */
		}
	else 
		{  
		/* this free block is replaced entirely by the allocated block */
		DbgCheckSize(remainder);
		newBlockSize = oldFreeBlock->size;
		RemoveFromFreeChain(oldFreeBlock, curHeap);		/* favoredFree is set here */
		newBlock = (stdBlock *) oldFreeBlock;
 		newBlock->size = newBlockSize;
		DbgCode(curHeap->freeBlocks--);
		}

	/* fix up heap header */
	curHeap->totalFree -= newBlockSize;
	IfIntDebugMsg(curHeap->totalFree < 0, "bad free total", curHeap);

	/* note: heap totalFree invalid until caller sets the new block's type non-free */
	DbgCode(curHeap->totalBytesAllocated += newBlockSize);
		
	return newBlock;
	}


/*
 *	Creates a new block of the given block size. NewBlock expects an adjusted
 *	size passed to it. It fills in the backPtr & size fields but it is up to 
 *	the client to fill in the others. Options for NewBlock are listed as 
 *	NewBlockOptions in the header files. Clients that call NewBlock
 *	must take care to maintain the lowestRemovableBlock.
 *
 *	note: creates a new NON free block. Caller MUST set tag bits
 */
stdBlock* NewBlock(blockSize_t reqBlockSize, long options, stdHeap* curHeap)
	{
	freeBlock*		workBlock;
	stdBlock*		newBlock;

	DbgCheckSize(reqBlockSize);

	switch (options & kDirectionMask)
		{
		case kAllocateFast:
				if (nil == (workBlock = MakeSpace(reqBlockSize, options, curHeap)))
					return nil;
				DbgCode(curHeap->totalBlocksAllocated++);
				newBlock = ConsumeFreeSpaceLow(workBlock, reqBlockSize, curHeap);
				break;
				
		case kAllocateLow:
				if (nil == (workBlock = MakeSpaceLow(reqBlockSize, options, curHeap)))
					return nil;
				DbgCode(curHeap->totalBlocksAllocated++);
				newBlock = ConsumeFreeSpaceLow(workBlock, reqBlockSize, curHeap);
				break;
				
		case kAllocateHigh:
				options |= kDoContinueUntilRegionFound;	/* search all of heap */
				if (nil == (workBlock = MakeSpaceHigh(reqBlockSize, options, curHeap)))
					return nil;
				DbgCode(curHeap->totalBlocksAllocated++);
				newBlock = ConsumeFreeSpaceHigh(workBlock, reqBlockSize, curHeap);
				break;
		
		#ifdef internal_debugging	
		default:
				Debugger();
		#endif
				
		}
	
	return newBlock;
	}


/*
 *	Similar to NewBlock, except that it always takes the fast case. NewBlock has the
 *	same functionality but a whole lot move. However this version is smaller and lighter
 *	and excutes 90% of the time.
 */
stdBlock* NewBlockFast(blockSize_t reqBlockSize, stdHeap* curHeap)
	{
	freeBlock*		workBlock;

	DbgCheckSize(reqBlockSize);

	if (nil == (workBlock = MakeSpace(reqBlockSize, kAllocateFast, curHeap)))
		return nil;
		
	DbgCode(curHeap->totalBlocksAllocated++);
	
	return ConsumeFreeSpaceLow(workBlock, reqBlockSize, curHeap);
	}


/*	Fills in tags, flags, heapID, sizeDelta and parent fields of blockheader */
void MarkBlockAsPrivate(stdBlock* privBlock, char mpFlags, stdHeap* curHeap)
{
 	/* set tags=ptrType, mpFlags=aBlockType, heapID=heapID, sizeDelta=0; */
	JamTagsFlagsAndSizeDelta(privBlock,
		((ulong)ptrType << 24) + 
		((ulong)(mpFlags | privBlockType) << 16));
	DbgSetBlockHeapID(privBlock, curHeap);
	privBlock->parent = curHeap;
}


/*
 *	This routine creates new master pointer blocks for use. Unused MPs are stored in a 
 *	singly link free list. If requested, the LSB is set in unused mp to catch clients who 
 *	dispose a handle twice.
 */
OSErr AllocateMoreMasters(stdHeap *curHeap)
	{
	blockSize_t	mpBlockSize;	/* first a count, then a size */
	blockSize_t	reqBlockSize;
	ptrBlock*	blockHeader;
	ulong*		mp;
	ulong*		mpTrail;
	Ptr			boundaryPtr;	/* used as a begining boudary, and later as an end boundary */

	/* get master pointer count from heap */
	if (((short)((stdHeap2*)curHeap)->MPCount) > 0)
		{
		mpBlockSize = (short)((stdHeap2*)curHeap)->MPCount;
		}
	else
		{
		/* MP count is zero, use default */
		mpBlockSize = kDfltMasters;
		}
	
	/* multiply by 4 to convert count to size */
	mpBlockSize <<= 2;
	
	reqBlockSize = AlignUp(mpBlockSize + kBlockOverhead);
	
	/* make sure size is large enough block so we can dispose it */
	if (reqBlockSize < kMinFreeBlockSize)
		reqBlockSize = kMinFreeBlockSize;

	/*	
	 *	round requested size up to take full advantage of block memory. If we are 
	 *	in the ProcessMgr heap, we allocate the MP block high in the heap.
	 */
	blockHeader = (ptrBlock*)NewBlock(reqBlockSize, IsProcessMgrHeap(curHeap) ? kAllocateHigh : kAllocateLow, curHeap);

	if (blockHeader == nil)
		return memFullErr;
	
	MarkBlockAsPrivate(blockHeader, masterBlockType, curHeap);
	blockHeader->sizeDelta = blockHeader->size - mpBlockSize - kPsuedoBlockSize;
	DbgCode(curHeap->totalDelta += blockHeader->sizeDelta);
	
	/* reset lowestRemoveableBlock */
	if (curHeap->lowestRemovableBlock == blockHeader)
		curHeap->lowestRemovableBlock = WalkUpFindNewLowRemoveable(blockHeader, curHeap);

	/* set boundaryPtr to point to the beginning of the mp block */
	boundaryPtr = (char*)blockHeader + kBlockHeaderSize;

	mpTrail = (ulong*)boundaryPtr;				/* trailer starts at the beginning */
	mp = (ulong*)(boundaryPtr + 4);				/* mp starts ahead of the trailer */
	*mpTrail = (ulong)curHeap->firstFreeMP;		/* fill in trailer */

	/* set boundaryPtr to point to end of mp block */
	boundaryPtr = (char*)boundaryPtr + mpBlockSize;
	
	/*
	 *	Set up the free master pointer chain in the MP block. Make the chain
	 *	odd if needed.
	 */
	#ifdef client_debugging
		while((char*)mp < boundaryPtr)
			{
			/* set LSB, to catch nasty clients */			
			*mp++ = (ulong)MaskMPBitOdd(mpTrail++);		
			}
	#else
		while((char*)mp < boundaryPtr)
			{
			/* some apps can't handle odd MPs */
			*mp++ = (ulong)mpTrail++;				
			}
	#endif

	curHeap->firstFreeMP = (Ptr*)mpTrail;	/* set the heap first MP to be the end of this list */
	DbgSetMagic(blockHeader->data, mpBlockSize);
	return noErr;
	}


/*
 *	Removes a block in the heap. This routine assumes that the block is not the
 *	first or last block in the heap. Internal routines may call this on a block
 *	that is marked free.
 */
freeBlock* KillBlock(stdBlock* blockHeader, stdHeap* curHeap)
	{
	freeBlock*	adjacentBlock;		/* either block above blockHeader or block below */
	Boolean		foundFree = false;
	
	DbgCode(curHeap->totalBlocksDisposed++);
	DbgCode(curHeap->totalBytesDisposed += blockHeader->size);
	curHeap->totalFree += blockHeader->size;
	
	/* look up,  coelesce */
	adjacentBlock = GetNextBlock(blockHeader);
	if (IsFreeBlock(adjacentBlock))
		{
		IfIntDebugMsg(adjacentBlock->size < kMinFreeBlockSize, "block too small", adjacentBlock);

		SetFreeChain((freeBlock*)blockHeader, adjacentBlock->prevFree, adjacentBlock->nextFree);
		blockHeader->size += adjacentBlock->size;
		
		#ifndef small_freeBlock_headers
		((stdBlock3*)blockHeader)->tagsFlagsSizeDelta = 0; 	/* set tags, mpFlags, heapID, sizeDelta to 0 */
		#endif
		
		ResetNextGuysBackPtr((stdBlock*)blockHeader);
		DbgGarbageFill(curHeap, adjacentBlock, kFreeBlockHeaderSize);
		if (curHeap->favoredFree == adjacentBlock) 
			curHeap->favoredFree = (freeBlock*)blockHeader;
		foundFree = true;
		}
	
	IfIntDebugMsg(blockHeader->back == nil, "KillBlock: previous block is zero", blockHeader);

	/* look down, colesce */
	adjacentBlock = blockHeader->back;
	if (IsFreeBlock(adjacentBlock))
		{
		IfIntDebugMsg(adjacentBlock->size < kMinFreeBlockSize, "block too small", adjacentBlock);
		if (foundFree)
			SetFreeChain(adjacentBlock, adjacentBlock->prevFree, ((freeBlock*)blockHeader)->nextFree);
		/* else just merge with the previous block, free-chain unaffected */
		adjacentBlock->size += blockHeader->size;
		ResetNextGuysBackPtr((stdBlock*)adjacentBlock);
		
		DbgGarbageFill(curHeap, blockHeader, kFreeBlockHeaderSize);
		DbgCode(if(foundFree) curHeap->freeBlocks--);
		
		if (curHeap->favoredFree == (freeBlock*)blockHeader) 
			curHeap->favoredFree = adjacentBlock;
		blockHeader = (stdBlock*)adjacentBlock;
		foundFree = true;
		}
	
	if (!foundFree)
		{
		/* neither prev block nor the next block is free */
		
		/* check to see if we are below the lowest free block or no free blocks at all */
		if (((char*)blockHeader < (char*)curHeap->firstFree) || (curHeap->firstFree == DummyFree(curHeap)))
			{
			SetFreeChain((freeBlock*)blockHeader, DummyFree(curHeap), curHeap->firstFree);
			}
		else
			{
			/* scan downward until a free block is found */
			freeBlock* workBlock = (freeBlock*)blockHeader;
			
			do
				{
				workBlock = workBlock->back;
				IfIntDebugMsg(workBlock <= (freeBlock*)(BACK(((stdBlock*)(curHeap->lowestRemovableBlock)))),
											"we reached front of heap", workBlock);
				}
			while (!IsFreeBlock(workBlock));
			
			SetFreeChain((freeBlock*)blockHeader, workBlock, workBlock->nextFree);
			}
		/* blockHeader->size & blockHeader->back stay the same */
		#ifndef small_freeBlock_headers
		((stdBlock3*)blockHeader)->tagsFlagsSizeDelta = 0; 	/* set tags, mpFlags, heapID, sizeDelta to 0 */
		#endif
		DbgCode(curHeap->freeBlocks++);
		}
		
	DbgGarbageFill(curHeap, ((freeBlock*)blockHeader)->data, blockHeader->size - kFreeBlockHeaderSize);
	IfIntDebugMsg(blockHeader->back && IsPrevBlockFree(blockHeader),"previous block is free", blockHeader);
	IfIntDebugMsg(IsNextBlockFree(blockHeader),"next block is free", blockHeader);

	/* now make an intelligent decision where to put the favored free */
	if (blockHeader->size >= curHeap->favoredFree->size)
		{
		curHeap->favoredFree = (freeBlock*)blockHeader;
		}
	return((freeBlock*)blockHeader);
	}	
	

/*
 *	Internal mega-routine to change the size of a block.
 *
 *	Here is the basic strategy for handling this operation....
 *	1.	Are the adjusted blocks sizes the same? If so, its easy!
 *	2.	Are we shrinking the new block? If so shrink and create new block if needed.
 *	3.	If the block is a handle and its small, then we jump relocate it.
 *	4.	Is there enough total size in the heap? call MakeSpace to make more room in the heap.
 *	5.	Is the block small, if so skip to step 11.
 *	6.	Call FindSpaceLow for the area above the handle.
 *	7.	Is there enough free space above the block in question?
 *		 If so, slide blocks up making room for the handle to grow.
 *		 If blocks can't slide, relocate them elsewhere
 *	8.	If we are setting a pointer size or locked handle, we bail now.
 *	9.	Is the enough space below the block in question?
 *		 If so, slide blocks down making room for the handle to grow.
 *		 If blocks can't slide, relocate them elsewhere
 *	10.	If we have not yet called MakeSpace, do so now, and goto Step 6.
 *	11. Call NewBlock to see if we can find a new home.
 *	12.Return nil.
 *
 *	Warning:This routine may not work correctly for zones that are not fully
 *			expanded (MaxApplZone), since JumpRelocateRange can fail and it
 *			does not call the growzone.
 */
stdBlock* SetBlockSize(stdBlock* blockHeader, blockSize_t reqBlockSize, stdHeap* curHeap)
{
	blockSize_t	growSize;
	blockSize_t	oldSize;
	Handle		theHandle;				/* original handle */
	Boolean		blockIsFixed;			/* true => block cannot move */
	Boolean		calledMakeSpaceOnce;	/* true => we called MakeSpace already */

	DbgCheckSize(reqBlockSize);

	IfIntDebugMsg(reqBlockSize == blockHeader->size,"size is the same",blockHeader);	
	
	/* is the new block smaller than the old one? */	
	if (reqBlockSize < (oldSize=blockHeader->size))
		{
		growSize = oldSize - reqBlockSize;
		DbgGarbageFill(curHeap, (char *) blockHeader + reqBlockSize, growSize);
		if (growSize >= kMinFreeSplitSize)
			{	
  			/* create a fake block and dispose it to properly allocate free memory */
  			stdBlock *fake = (stdBlock*) ((char*)blockHeader + reqBlockSize);
			
			/* note: KillBlock does not depend on flags, tags or sizeDelta */
			fake->size = growSize;
			fake->back = blockHeader;
			ResetNextGuysBackPtr(fake);
			blockHeader->size = reqBlockSize;
			
			/*
			 *	bizzare subtlety: if this new free block is the lowestRemovableBlock
			 *	in the heap, we must adjust the pointer. This only happens when 
			 *	SetBlockSize is called on a fixed block to make it smaller and we are 
			 *	in the main heap fragment.
			 */
			#ifdef implemented_discontiguous_heaps
			if (((void*)fake < curHeap->lowestRemovableBlock) && ((void*)fake > (void*)(curHeap->heapStart)))
				curHeap->lowestRemovableBlock = fake;
			#else
			if ((void*)fake < curHeap->lowestRemovableBlock)
				curHeap->lowestRemovableBlock = fake;
			#endif
			
			KillBlock(fake, curHeap);

			/* KillBlock unfairly increments these, so we decrement them */
			DbgCode(curHeap->totalBlocksDisposed--);
			DbgCode(curHeap->totalBytesDisposed -= growSize);
			return blockHeader;
			}
		else 
			{
			/* The client has asked for a smaller block, but not by much */
			/* The sizeDelta can be changed by a client routine */
			/* note: this code path not take for certain compiler defs
				(ie. quadLongWordAligned and small_freeBlock_headers). */
			return blockHeader;
			} 
		}
		
	/*
	 *	If we got here, the client is increasing the blocks size beyond the sizeDelta.
	 *	Darn, we have to do real work.
	 */
	growSize = reqBlockSize - oldSize;
	if (IsFixedBlock(blockHeader))
		blockIsFixed = true;
	else
		{
		/* save the handle in case it moves */
		theHandle = (Handle) (((handleBlock*) blockHeader)->relHandle + (long) curHeap);
		blockIsFixed = false;
		}
	calledMakeSpaceOnce = false;

	/* is there enough size in the heap to accomodate the request? */
	if (curHeap->totalFree < growSize)
		{
		/*
		 *	we try to make space the old fashioned way, we earn it....
		 *	Call standard allocation function to make space. That might give us a 
		 *	saint's chance in hell of trying to grow the block. But there are 
		 *	no guarantees.
		 */
		calledMakeSpaceOnce = true;

		/*
		 *	note: considered passing reqBlockSize instead of growSize, but I elected
		 *	not to do this because we could be sizing a very large handle.
		 *
		 *	go ahead an make more space in the heap. Do we have enough?
		 */
		if (nil == (MakeSpace(growSize, 0, curHeap)))
			{
			/* we bail right away since things are hopeless */
			return nil;
			}
			
		if (!blockIsFixed)
			{
			/* recover blockHeader in case it moved */
			blockHeader = (stdBlock*) GetBlockHeaderFromPtr(*theHandle);
			}
		}
		
	
	/*
	 *	one last performance enhancing check. If the block is a "small" handle, then it 
	 *	is probably easier to jump relocate it rather than slide blocks around.
	 *	By "small" we essentially mean the block is smaller than it's neighbors.
	 *
	 *	One small caveat, if its neighbors are free blocks, it is probably easier to 
	 *	eat thier free space instead of jump relocating.
	 */
	if (!blockIsFixed)
		{
		stdBlock*	adjacentBlock = GetNextBlock(blockHeader);	/* get block after blockHeader */
		
		/* is the block after blockHeader not free and is it larger than blockheader? */
		if (!IsFreeBlock(adjacentBlock) && oldSize < adjacentBlock->size)
			{
			adjacentBlock = blockHeader->back;					/* get block before blockHeader */
			
			/* is the block before blockHeader not free and is it large enough */
			if (!IsFreeBlock(adjacentBlock) && oldSize < adjacentBlock->size)
				{
				/* handle is small, we jump relocate it, if it fails we bail right away */
				return ((stdBlock*)
					JumpRelocateBlock((handleBlock*)blockHeader, reqBlockSize, kAllocateFast, curHeap));
				}
			}
		}
	
	/*
	 *	Now lets get down to the nitty gritty and expand the block. We loop twice. If we
	 *	find nothing on the second try, we bail.
	 */
	while(true)
		{
		stdBlock*	newSpaceAbove = GetNextBlock(blockHeader);
		stdBlock*	endBlock;		/* end of range found */
		short		results;		/* from find space routines */
		
		results = kFirstRegionOnly;
		newSpaceAbove = FindSpaceLow(newSpaceAbove, growSize, &results, &endBlock, curHeap);
		
		switch (results)
			{
			case kNoMovementRequired :
				{
				#ifndef small_freeBlock_headers
					/*
					 *	warning: growSize can be really small (< a BlockHeader), when using
					 *	20 byte freeBlock headers. This causes problems with ConsumeFreeSpaceLow
					 *	because it can't handle allocations smaller than kMinBlockSize. So
					 *	we force growSize to be at least kMinBlockSize. This gives the client
					 *	a larger than expect size delta. Big Deal. Actually this might even be
					 *	prefered since some clients tend to continually size the same handles
					 *	to be larger.
					 */
					if (growSize < kMinBlockSize)
						{
						growSize = kMinBlockSize;
						}
				#endif
				ConsumeFreeSpaceLow((freeBlock*)newSpaceAbove, growSize, curHeap);
				blockHeader->size += newSpaceAbove->size;
				ResetNextGuysBackPtr(blockHeader);
				/* 11/17/93 6:14:56 PM (BET): Also adjust lowestRemovableBlock  */
				if (curHeap->lowestRemovableBlock == newSpaceAbove) {
					curHeap->lowestRemovableBlock = WalkUpFindNewLowRemoveable(blockHeader, curHeap);
					}
			
				return blockHeader;
				}
				
			case kSlideBlocksUp :
				{
				/* space can be created by sliding blocks up */
				SlideBlocksUp(newSpaceAbove, (freeBlock*)endBlock, curHeap);
				ConsumeFreeSpaceLow((freeBlock*)newSpaceAbove, growSize, curHeap);
				blockHeader->size += newSpaceAbove->size;
				ResetNextGuysBackPtr(blockHeader);
				return blockHeader;
				}
				
			case kJumpRelocateBlocks :
			case kJumpRelocateOrSlideBlocks :
				{
				uchar		savedTags;
	
				/* since blockHeader can move during JumpRelocateRange, we need to anchor it down */
				savedTags = ((stdBlock2*)blockHeader)->tags;		/* save tags */
				blockHeader->ptrBit = 1;							/* mark block as busy */
				
				/* space can be created by moving blocks out of the way */
				if (nil != JumpRelocateRange(newSpaceAbove, endBlock, kAllocateFast, curHeap))
					{
					/* space has been found */
					/* note, newSpaceAbove wont be changed by JumpRelocateRange */
					((stdBlock2*)blockHeader)->tags = savedTags;	/* restore tags */
	
					ConsumeFreeSpaceLow((freeBlock*)newSpaceAbove, growSize, curHeap);
					blockHeader->size += newSpaceAbove->size;
					ResetNextGuysBackPtr(blockHeader);
					return blockHeader;			
					}
				else
					{
					((stdBlock2*)blockHeader)->tags = savedTags;	/* restore tags */
	
					/* can we still slide blocks? */
					if (results == kJumpRelocateOrSlideBlocks)
						{
						/*
						 *	We slide blocks up since JumpRelocateRange failed.
						 *
						 *	since JumpRelocateRange can change endBlock, we need to 
						 *	recover it now to pass it to SlideBlocksUp. Since
						 *	JumpRelocateRange could have moved endBlock (by coelescing 
						 *	freeblocks), we need to walk the range and get it back.
						 *
						 *	note: an alternative way to solve this problem is to 
						 *	return yet another parameter from FindSpaceHigh (that 
						 *	would be endBlockToUseWhenSliding). But since this particular
						 *	code path almost never taken, we walk the range again
						 *	and find it manually.
						 */
						endBlock = RecoverEndBlock(newSpaceAbove, growSize);
						
						/* space can be created by sliding blocks up */
						SlideBlocksUp(newSpaceAbove, (freeBlock*)endBlock, curHeap);
						ConsumeFreeSpaceLow((freeBlock*)newSpaceAbove, growSize, curHeap);
						blockHeader->size += newSpaceAbove->size;
						ResetNextGuysBackPtr(blockHeader);
						return blockHeader;
						}
					}
				}
			}

			
		/*
		 *	One case that is not handled here, we should probably slide blocks up above
		 *	blockHeader to create more space above it. This is an optimization that 
		 *	wont get done.
		 */
			
		/* now lets look at space below the block to see if we can slide the block down */
		if (!blockIsFixed)
			{
			stdBlock*	newSpaceBelow = blockHeader->back;
			blockSize_t	lowGrowSize;
			Boolean		freeAbove;
			
			newSpaceAbove = GetNextBlock(blockHeader);
			IfIntDebugMsg(nil == newSpaceAbove,"newSpaceAbove is nil", blockHeader);
			
			/* did we find some space above?, if so, we will need it */			
			if (freeAbove = IsFreeBlock(newSpaceAbove))
				lowGrowSize = growSize - newSpaceAbove->size;
			else
				lowGrowSize = growSize;
			
			results = kFirstRegionOnly;
			newSpaceBelow = FindSpaceHigh(newSpaceBelow, lowGrowSize, &results, &endBlock, curHeap);
			
			switch (results)
				{
				case kJumpRelocateBlocks :
					{
					uchar		savedTags;
		
					/* temp allocate block so blocks wont go there */
					if (freeAbove)
						OccupyFreeSpace((freeBlock*)newSpaceAbove, curHeap);
						
					/* since blockHeader can move during JumpRelocateRange, we need to anchor it down */
					savedTags = ((stdBlock2*)blockHeader)->tags;							/* save tags */
					blockHeader->ptrBit = 1;												/* mark block as busy */
					newSpaceBelow = (stdBlock*) JumpRelocateRange(newSpaceBelow, endBlock, kAllocateFast, curHeap);
					((stdBlock2*)blockHeader)->tags = savedTags;							/* restore tags */

					if (!newSpaceBelow)
						{
						if (freeAbove)
							KillBlock(newSpaceAbove, curHeap);
						break;	/* only if we cant find blocks */
						}
						
					if (freeAbove)
						KillBlock(newSpaceAbove, curHeap);
						
					/* fall thu to slide blocks down case */
					}
						
				case kNoMovementRequired :
				case kSlideBlocksDown:
					{
					/* we now have space both below and above, slide blocks down (including blockheader) */
					/* if the block above is free we slide the block along with it */
					if (freeAbove)
						endBlock = newSpaceAbove;
					else
						endBlock = blockHeader;
						
					/* slide blocks down including blockHeader */
					newSpaceBelow = (stdBlock*) SlideBlocksDown((freeBlock*)newSpaceBelow, endBlock, curHeap);
					
					/* get blockHeader back since it may have moved */
					blockHeader = (stdBlock*) GetBlockHeaderFromPtr(*theHandle);
					
					/* we can now increase the size of the block, reset newSpaceAbove */
					newSpaceAbove = GetNextBlock(blockHeader);
					
					/* just like in the other places, lets go for it */
					ConsumeFreeSpaceLow((freeBlock*)newSpaceAbove, growSize, curHeap);
					blockHeader->size += newSpaceAbove->size;
					ResetNextGuysBackPtr(blockHeader);
					return blockHeader;
					}
				}		
			}
			
		/*
		 *	In the case of fixedBlock, we have not succeeded in making space above it. In the
		 *	case of a movable block, we have not suceeded in making space both above and 
		 *	below the block.
		 */
		if (calledMakeSpaceOnce)
			break;		/* break out of loop, unable to make space to grow the block */
		else
			{
			freeBlock*	makeSpaceResult;

			/*
			 *	we try to make space the old fashioned way, we earn it....
			 *	Call standard allocation function to make space. That might give us a 
			 *	saint's chance in hell of trying to grow the block. But there are 
			 *	no guarantees.
			 */
			calledMakeSpaceOnce = true;
				
			/*
			 *	note: considered passing reqBlockSize instead of growSize, but I elected
			 *	not to do this because we could be sizing a very large handle.
			 *
			 *	go ahead an make more space in the heap.
			 */
			makeSpaceResult = MakeSpace(growSize, 0, curHeap);
				
			if (!blockIsFixed)
				{
				/* recover blockHeader in case it moved */
				blockHeader = (stdBlock*) GetBlockHeaderFromPtr(*theHandle);
				}
				
			if (nil == makeSpaceResult)
				break;			/* we didn't get enough space, quit trying */
			}
				
		}	/* end of while loop */
		

	if (blockIsFixed)
		return nil;		/* were at the end of the road, bail */

	/*
	 *	playing games will knott help, our last recorse is to jump relocate the block. 
	 *	Doing so calls the standard allocation function to allocate space, purge, or 
	 *	create discontinuous heaps or call clients growZoneProc. This last 
	 */
	return ((stdBlock*)
		JumpRelocateBlock((handleBlock*)blockHeader, reqBlockSize, kAllocateFast, curHeap));
}


/*
 *	Loop until top of region (fixed block) is found. Along the way this rouine
 *	accumulates free space and return the lowest free block in the region.
 *	Note: topOfRange is the block below the fixed block.
 */
blockSize_t CalcFreeSpaceAndFindRegionTop(handleBlock* workBlock, freeBlock** lowFree, stdBlock** topOfRange);
blockSize_t CalcFreeSpaceAndFindRegionTop(handleBlock* workBlock, freeBlock** lowFree, stdBlock** topOfRange)
	{
	blockSize_t cumFreeSpace = 0;
	Boolean		foundFree = false;
	
	while (true)
		{
		if (IsHandleBlock(workBlock))
			{
			/*
			 *	note: since this routine is not called from an internal routine.
			 *	We do not have to check for the handle being busy.
			 */
			if (IsLockedHandle(workBlock))
				{
				goto fixedBlock;
				}
			}
		else if (IsPtrBlock(workBlock))
			{
			fixedBlock:
				*topOfRange = workBlock->back;
				return cumFreeSpace;
			}
		else
			{
			if (!foundFree)
				{
				*lowFree = (freeBlock*) workBlock;
				foundFree = true;
				}
				
			/* block is free */
			cumFreeSpace += workBlock->size;
			}
		
		workBlock = GetNextBlock(workBlock);
		}
	}
	
	
/*
 *	Moves a block high in the heap if its not already high. It moves it by jump 
 *	relocating the block.
 */
void MoveBlockHigh(handleBlock* blockHeader, stdHeap* curHeap)
	{
	stdBlock*		topBlock;			/* block above blockHeader or top block in range */
	freeBlock*		lowFree;
	
	/* do a quick check to see if the block is already high */
	topBlock = GetNextBlock(blockHeader);
	if (IsFixedBlock(topBlock))
		return;			/* just return with out moving */

	/* from here on out top block is the top block of the range, do we have enough space? */
	if (CalcFreeSpaceAndFindRegionTop(blockHeader, &lowFree, &topBlock) >= blockHeader->size)
		{
		/* we have enough space in the given range to move the block high */

		/* do we have enough room that we can just do a one shot move? */
		if (!(IsFreeBlock(topBlock) && (topBlock->size >= blockHeader->size)))
			{
			/* NO we dont, we must slide blocks down to make space high */
			topBlock = (stdBlock*) SlideBlocksDown(lowFree, topBlock, curHeap);
			}
		
		topBlock = ConsumeFreeSpaceHigh((freeBlock*)topBlock, blockHeader->size, curHeap);
		
		/* update heap statistics */
		DbgCode(curHeap->bytesMoved += blockHeader->size);
		DbgCode(curHeap->totalBlocksMoved++);

		MoveBytes(blockHeader->data, topBlock->data, blockHeader->size - kBlockHeaderSize);

		/* copy tags, flags, heapID, sizeDelta to new location */
		((stdBlock3*)topBlock)->tagsFlagsSizeDelta = ((stdBlock3*)blockHeader)->tagsFlagsSizeDelta;
		
		/* 8/30/93 3:11:41 AM (BET): Need to make sure that we didn't change the slop factor here */
		((stdBlock2*)topBlock)->sizeDelta += topBlock->size - blockHeader->size;
		
		/* update the master pointer to point to new location */
			{
			Handle pMP = (Handle) (blockHeader->relHandle + (long)curHeap);
			*pMP = (Ptr)((handleBlock*)topBlock)->data;
			}
		
		/* update relative handle to point to the MP */
		((handleBlock*)topBlock)->relHandle = blockHeader->relHandle;
		
		/* remove the old block */
		KillBlock((stdBlock*)blockHeader, curHeap);

		/* since the block has moved, we should flush the instruction cache */
		MarkCacheNeedsToBeFlushed(curHeap);

		return;
		}
	else
		{
		if ((topBlock->back == blockHeader) && (IsFreeBlock(topBlock)))
			{
			/*
			 *	We have a special case where we can slide blockHeader up directly and 
			 *	effectively swap places with topBlock.
			 */
			SlideBlocksUp((stdBlock*)blockHeader, (freeBlock*)topBlock, curHeap);
			
			return;
			}
		
		/*
		 *	Nothing else better to do here we we bail. We could do a variety of things.
		 *	But they would probably be very expensive for what people consider to be a 
		 *	lightweight operation.  Here is a list of things considered but rejected:
		 *
		 *	1) Call JumpRelocateBlock(kDontPurge+kDontCallGZ+kAllocateHigh)
		 * 		Performance tests have show this operation to be slow.
		 *	2) Perform a 2 shot move using the stack (old MM)
		 *		This has potential to be a real slow operation
		 *	3) Perform a 2 shot move using favoredFree
		 *		Ugly code, does not work for all cases
		 * 	
		 *	Instead we just return and let the heap become fragmented. This should not
		 *	be a great big problem since most calls to MoveHHi are followed by 
		 *	HLock/HUnlock pairs.
		 */
		 
		/*
		 *	Sorry.  If the code asks for the block to be moved up, it means it.  We
		 *	can't be second guessing the client as to whether we have to honor the request
		 *	to move high, we just have to get it done.  Plan 1 above looks pretty industrial
		 *	strength, if all else fails let's give it a go...
		 */
		 
		 blockHeader = JumpRelocateBlock(blockHeader, blockHeader->size, kDontPurge+kDontCallGZ+kAllocateHigh, curHeap);
		 return;
		}

	}
	

/*
 *	Moves a block low in the heap if its not already low. It moves it by jump relocating
 *	the block.
 */
void MoveBlockLow(handleBlock* blockHeader, stdHeap* curHeap)
	{
	stdBlock*	prevBlock;
	
	IfIntDebugMsg(!IsHandleBlock(blockHeader),"blockHeader no a handle", blockHeader);
	IfIntDebugMsg(IsFixedBlock(blockHeader),"blockHeader is fixed", blockHeader);
	
	prevBlock = blockHeader->back;

	/* check to see if block below is locked, */
	if (IsFixedBlock(prevBlock))
		return;
		
	/* need to do a simple check to see if we can slide the block down one instead 
		of jump relocating it. */
	if (IsFreeBlock(prevBlock) && (IsFixedBlock(prevBlock->back)))
		{
		SlideBlocksDown((freeBlock*)prevBlock, (stdBlock*)blockHeader, curHeap);
		return;
		}
	
	/* find a new home */
	JumpRelocateBlock(blockHeader, blockHeader->size, 
				kDontPurge+kDontCallGZ+kAllocateLow, curHeap);
	}


/*
 *	Returns the largest region that can be obtained by purging.
 *
 *	note: you can probably get more space due to stage 2 heap compactions.
 *
 *	note2: the Size returned is a physical block size.
 */
blockSize_t CalcLargestPurgeRegion(stdHeap* curHeap)
	{
	blockSize_t cumRegionSpace = 0;
	blockSize_t largestRegionSpace = 0;
	stdBlock*	workBlock = curHeap->backLimit;						/* scan starts here */
	stdBlock*	scanBottom = BACK(((stdBlock*)(curHeap->lowestRemovableBlock)));	/* scan ends here */

	/* we walk down because its faster */	
	do
		{
		workBlock = workBlock->back;
		
		if (IsHandleBlock(workBlock))
			{
			/*
			 *	note: since this routine is not called from an internal routine.
			 *	We do not have to check for the handle being busy.
			 */
			if (IsLockedHandle(workBlock))
				{
				goto CalcPurgeFixedBlock;
				}
			else if (IsPurgableHandle(workBlock))
				{
				cumRegionSpace += workBlock->size;
				}
			}
		else if (IsPtrBlock(workBlock))
			{
			CalcPurgeFixedBlock :
			
			/* common path for fixed blocks */
			if (cumRegionSpace > largestRegionSpace)
				largestRegionSpace = cumRegionSpace;
				
			/* end of region, at it to total space */
			cumRegionSpace = 0;		/* on to the next region */
			}
		else
			{
			/* block is free */
			cumRegionSpace += workBlock->size;
			}
		}
	while (scanBottom != workBlock);
	
	return largestRegionSpace;
	}
	
	
/*
 *	This routine does NOT change totalPurgableSpace. It does, however, empty
 *	the handle and call the heap's purge warning procedure.
 */
freeBlock* PurgeBlock(handleBlock* blockHeader, stdHeap* curHeap)
	{
	Handle	pMP = (Handle) (blockHeader->relHandle + (long)curHeap);
	
	IfIntDebugMsg(IsLockedHandle(blockHeader), "block is locked", blockHeader);
	/*
	 *	note: don't debug check for purgable handle since the old MM permited
	 *	purging of non purgable handles.
	 */
		
	/* call the classic purge warning proc */
	if (curHeap->purgeProc)
		{
		FlushCacheIfNeeded(curHeap);
		/*
		 *	warning: we make the assumption that the client will not allocate 
		 *	memory in the heap inside the purge procedure.
		 *
		 *	note: Cant do a DbgCheckHeap here since the heap is invalid.
		 */
		CALL_FNC_PTR_1(PurgeProcPtr,curHeap->purgeProc,uppPurgeProcInfo, pMP);
		}

	/* set MP to point to nil */
	*pMP = nil;
	
	DbgCode(curHeap->totalDelta -= (long) blockHeader->sizeDelta);
	IfDbgMsg(curHeap->handleBlocks-- < 0,"corrupt header", curHeap);
	return KillBlock((stdBlock*)blockHeader, curHeap);
	}


/* Empties a handle contents, called by both EmptyHandle and ReallocHandle */
void DoEmpty(handleBlock* blockHeader, stdHeap* curHeap)
	{
	IfIntDebugMsg(IsLockedHandle(blockHeader),"block is locked", blockHeader);
	IfIntDebugMsg(IsFreeBlock(blockHeader),"block is already free", blockHeader);

	/* the old MM did not check to see if this block is purgable. So neither do we. */
	/* also note: a block does not have to be a resource to be purgable. */
	/* Since the the block is already a unlocked handle, no need to set the 
		lowestRemovableBlock */
	
	if (IsPurgableHandle(blockHeader))
		{
		curHeap->totalPurgableSpace -= blockHeader->size;
		}

	PurgeBlock(blockHeader, curHeap);
	}


/*
 *	Very similar to SlideBlocksDown. Coelesces and purges from from destBlock to endSlide inclusive. 
 *	These routines will prevent us from have to walk the range twice. destBlock must be either free 
 *	or a purgable handle for this routine to work. 
 *
 *	Danger Will Robinson: heap not in a consistent state when purge proc called. May have to compact,
 *	then purge each block instead. I think we can get away with this assumption.
 */
static freeBlock* PurgeAndSlideBlocksDown(freeBlock* destBlock, stdBlock* endSlide, stdHeap* curHeap);
static freeBlock* PurgeAndSlideBlocksDown(freeBlock* destBlock, stdBlock* endSlide, stdHeap* curHeap)
	{

	IfIntDebugMsg(!(IsFreeBlock(destBlock) || (IsPurgableBlock(destBlock))),
		"expected free or purgable block", destBlock);

	if (IsPurgableBlock(destBlock))
		{
		/* make the first block free so we can start sliding blocks */
		curHeap->totalPurgableSpace -= destBlock->size;
		destBlock = PurgeBlock((handleBlock*)destBlock, curHeap);
		
		/* did we run past the end of the range while purging? */
		if ((stdBlock*)GetNextBlock(destBlock) > endSlide)
			return destBlock;		/* yippie, we can get out of here early */
		}
	
	/* one last check. The loop below wont work if destBlock == endSlide. */
	if (destBlock == (freeBlock*)endSlide)
		return destBlock;
	else
		{
		/* now that destBlock is set up correctly, we can begin sliding */
		handleBlock*	workBlock = GetNextBlock(destBlock);
		freeBlock*		prevFree = destBlock->prevFree;
		freeBlock*		nextFree = destBlock->nextFree;
		long 			prevBlock = (long)(destBlock->back);/* trails dest block, put in data register */
		blockSize_t		destBlockSize = destBlock->size;	/* destination free block size */
		blockSize_t		sizeOfWorkBlock;					/* 1) get size before workBlock header is trashed
																2) cache workBlock->size for optimization */
		Handle			theHandle;
		Boolean 		setFavoredFree;

		/* is favored free inside this range? */
		setFavoredFree = (curHeap->favoredFree >= destBlock && curHeap->favoredFree <= (freeBlock*)endSlide);

		/* walk the heap coelescing free blocks */
		do
			{	
			IfIntDebugMsg(IsFreeBlock(workBlock), "did not expect free block", workBlock);
			IfIntDebugMsg(IsFixedBlock(workBlock), "error, not allowed to slide immovable blocks", workBlock);
			
			/* loop purging all contiguous purgable blocks starting at workBlock */
			while (IsPurgableHandle(workBlock) && ((void*)workBlock <= (void*)endSlide))
				{
				
				/* The block is purgable, must purge it first */
				IfIntDebugMsg(IsLockedHandle(workBlock), "block is locked", workBlock);
				IfIntDebugMsg(!IsPurgableHandle(workBlock), "block is not purgable", workBlock);
				
				/* get blocks handle from relative handle */
				theHandle = (Handle) (workBlock->relHandle + (long)curHeap);
				
				/* call the classic purge warning proc */
				if (curHeap->purgeProc)
					{
					FlushCacheIfNeeded(curHeap);
					/*
					 *	warning: we make the assumption that the client will not allocate 
					 *	memory in the heap inside the purge procedure.
					 *
					 *	note: Cant do a DbgCheckHeap here since the heap is invalid.
					 */
					CALL_FNC_PTR_1(PurgeProcPtr,curHeap->purgeProc,uppPurgeProcInfo, theHandle);
					}
					
				/* set MP to point to nil */
				*theHandle = nil;
				
				sizeOfWorkBlock = workBlock->size;		/* cache workBlock->size */
				curHeap->totalPurgableSpace -= sizeOfWorkBlock;
				curHeap->totalFree += sizeOfWorkBlock;
				destBlockSize += sizeOfWorkBlock;			/* add new space to destination block */
				
				/* debug stuff */
				DbgCode(curHeap->totalDelta -= (long) workBlock->sizeDelta);
				IfDbgMsg(curHeap->handleBlocks-- < 0,"corrupt header", curHeap);
				DbgCode(curHeap->totalBlocksDisposed++);
				DbgCode(curHeap->totalBytesDisposed += workBlock->size);
				DbgGarbageFill(curHeap, workBlock, sizeOfWorkBlock);
				
				workBlock = (handleBlock*) ((char*)workBlock + sizeOfWorkBlock);	/* march workBlock again */

				/* are we going to coelesce with the next free block? */
				if ((freeBlock*)workBlock == nextFree)
					{
					destBlockSize += (sizeOfWorkBlock = workBlock->size);
					workBlock = (handleBlock*) ((char*)workBlock + sizeOfWorkBlock);	/* march workBlock again */
					nextFree = nextFree->nextFree;			/* set next free for setting free chain */
					DbgCode(curHeap->freeBlocks--);
					}
				}

			/* did we run past the end of the range while purging? */
			if ((stdBlock*)workBlock > endSlide)
				break;
	
			/* commence slide */
			IfIntDebugMsg(IsFreeBlock(workBlock),"block is free", workBlock);
			IfIntDebugMsg(IsPurgableHandle(workBlock),"block is purgable", workBlock);
			
			sizeOfWorkBlock = workBlock->size;				/* get size before its trashed */

			/* reset MP to point to new location */	
			theHandle = (Handle) (workBlock->relHandle + (long) curHeap);
			*theHandle = (Ptr)((handleBlock*)destBlock)->data;
			
			/* slide data & header, workBlock's block header may now contain bad data */
			MoveBytes(workBlock, destBlock, sizeOfWorkBlock);	
			destBlock->back = (void*)prevBlock;					/* restore back pointer */
	
			/* update heap statistics */
			DbgCode(curHeap->bytesMoved += sizeOfWorkBlock);
			DbgCode(curHeap->totalBlocksMoved++);
			DbgCode(curHeap->bytesSlidDown += sizeOfWorkBlock);
	
			/* march pointers */
			prevBlock = (long) destBlock;
			destBlock = (freeBlock*) ((char*)destBlock + sizeOfWorkBlock);
			workBlock = (handleBlock*) ((char*)workBlock + sizeOfWorkBlock);
	
			/* are we going to coelesce with the next free block? */
			if ((freeBlock*)workBlock == nextFree)
				{
				destBlockSize += (sizeOfWorkBlock = workBlock->size);
				workBlock = (handleBlock*) ((char*)workBlock + sizeOfWorkBlock);	/* march workBlock again */
				nextFree = nextFree->nextFree;		/* set next free for setting free chain */
				DbgCode(curHeap->freeBlocks--);
				}
				 
			IfIntDebugMsg((char*) workBlock > (char*)curHeap->backLimit, "end of heap reached", workBlock);
			DbgGarbageFill(curHeap, destBlock->data, destBlockSize - kFreeBlockHeaderSize);
			} 
		while ((void*) workBlock <= (void*) endSlide);
		
		/* reset back pointer for the block after the range */
		workBlock->back = destBlock;
	
		/* fill in fields of newly created free block */
		destBlock->back = (void*)prevBlock;		/* reset back for newly created freeBlock */
		destBlock->size = destBlockSize;
		#ifndef small_freeBlock_headers
		((stdBlock3*)destBlock)->tagsFlagsSizeDelta = 0; 	/* set tags, mpFlags, heapID, sizeDelta to 0 */
		#endif
		SetFreeChain(destBlock, prevFree, nextFree);
	
		IfIntDebugMsg(curHeap->favoredFree == nil, "didn’t expect nil favored free", curHeap);
		
		/* set favoredFree if we have to */
		if (setFavoredFree || destBlockSize > curHeap->favoredFree->size)
			curHeap->favoredFree = destBlock;
		}
		
	return destBlock;
	}


/*
 *	finds the purge rover as fast as possible. If only one scan above the purge
 *	pointer is needed, this routine returns false for scanAgain.
 */
stdBlock* LocatePurgePtr(stdHeap* curHeap, Boolean* scanAgain);
stdBlock* LocatePurgePtr(stdHeap* curHeap, Boolean* scanAgain)
	{
	freeBlock*	workBlock;		/* not always a free block */
	freeBlock*	nextBlock;		/* next block while scanning down */
	void*		cachedPurgePtr = curHeap->purgePtr;
	
	/* is the purge rover above the area to scan? */
	if (cachedPurgePtr > (void*)curHeap->backLimit)
		{
		/* we only want to scan the heap once, start at top */
		*scanAgain = false;
		#ifdef implemented_discontiguous_heaps
			workBlock = curHeap->heapStart;
		#else
			workBlock = curHeap->lowestRemovableBlock;
		#endif
		}
	else
		{		
		*scanAgain = true;

		/* can we cheat by scanning the free list first? */
		if (((freeBlock*)cachedPurgePtr > curHeap->firstFree) && (curHeap->firstFree != curHeap->lastFree))
			{
			workBlock = curHeap->firstFree;
			while (cachedPurgePtr < (void*)(nextBlock = workBlock->nextFree) && 
					(nextBlock != DummyFree(curHeap)))
				{
				workBlock = nextBlock;
				}
			}
		else
			{
			/* no, we can't cheat, must scan from the bottom. */
			#ifdef implemented_discontiguous_heaps
				workBlock = curHeap->heapStart;
			#else
				workBlock = curHeap->lowestRemovableBlock;
			#endif
			}
		
		/* linearly scan to get past the purgePtr */
		while ( (freeBlock*)cachedPurgePtr > (workBlock = GetNextBlock(workBlock)));
		}

	return (stdBlock*) workBlock;
	}


/*
 *	Makes space of a given size by purging, and returns it. This routine 
 *	first scans to find the purge rover. From the purge rover it scans
 *	up looking for enough purgable space. If not enough purgable space is found it 
 *	then scans the space from the bottom of the heap up to the the purge rover looking for 
 *	more space. If the purge rover is at the top of the heap, then the scan loop is only
 *	called once. Once a space has been successfully found, it calls 
 *	PurgeAndSlideBlocksDown to make space. 
 *
 *	Note: clients should perform some preflight checks to prevent wasted CPU cycles.
 *			For example: curHeap->totalPurgableSpace + curHeap->totalFree >= reqBlockSize
 */
freeBlock* PurgeAndMakeSpace(blockSize_t sizeNeeded, stdHeap* curHeap, Boolean killEverything)
	{
	stdBlock*	workBlock;
	stdBlock*	scanLimit;			/* scan up this point */
	stdBlock*	regionStart;		/* purge region start */
	blockSize_t	cumRelocSpace;		/* total amount of free and purgable space */
	Boolean		scanAgain;
	Boolean		spaceFound = false;

	scanLimit = curHeap->backLimit;
	curHeap->purgePtr = regionStart = workBlock = LocatePurgePtr(curHeap, &scanAgain);
	
	/*
	 *	Must loop twice (typically), once below scanning space above the purge rover, 
	 *	once for scanning space below.
	 */
	do
		{
		cumRelocSpace = 0;			/* total amount of free and purgable space */

		/* begin scan for purge space. This scan starts at workBlock and walks up 
			to scanLimit. */
		do
			{
			/*
			 *	note: have to check for ptr block first incase the block is
			 *	temporarily busy (handle block with ptr bit set).
			 */
			
			if (IsPtrBlock(workBlock))
				{
				/* ptr block, start next region */
				regionStart = GetNextBlock(workBlock);
				cumRelocSpace = 0;
				}
			else if (IsHandleBlock(workBlock))
				{
				if (IsLockedHandle(workBlock))
					{
					/* locked handle, start next region */
					regionStart = GetNextBlock(workBlock);
					cumRelocSpace = 0;
					}
				else if (IsPurgableHandle(workBlock))
					{
					blockSize_t thisBlockSize = workBlock->size;
					
					if (killEverything) {
						curHeap->totalPurgableSpace -= workBlock->size;
						workBlock = (stdBlock*) PurgeBlock((handleBlock*)workBlock, curHeap);
						}
						
					if ( (cumRelocSpace += thisBlockSize) >= sizeNeeded )
						{
						spaceFound = true;
						break;
						}
					}
				}
			else
				{
				/* block is free */
				if ( (cumRelocSpace += workBlock->size) >= sizeNeeded )
					{
					spaceFound = true;
					break;
					}
				}
			}
		while (scanLimit > (workBlock = GetNextBlock(workBlock)));
		
		if (spaceFound)
			break;
			
		if (scanAgain)
			{
			/* set up scanLimit to be the first fixed block after the purge ptr, note:
				we reuse workBlock here to do the scan, then assign it to scanLimit.
				Hopefully the compiler will put scanLimit into a data register since its
				never dereferenced as an address. Lame MPW does not. */
			workBlock = curHeap->purgePtr;
			
			/* scan to find non-relocatable after purge ptr */
			while (!IsFixedBlock(workBlock))
				{
				workBlock = GetNextBlock(workBlock);
				}
			scanLimit = workBlock;

			/* set up parameters for next scan */
			#ifdef implemented_discontiguous_heaps
				regionStart = workBlock = curHeap->heapStart;
			#else
				regionStart = workBlock = curHeap->lowestRemovableBlock;
			#endif
			scanAgain = false;
			}
		else
			break;
		}
	while (true);
	
	if (!spaceFound)
		{
		/* we ran through the whole heap but did not find enough space. lets bail. */
		return nil;
		}

	curHeap->purgePtr = workBlock;


	/*
	 *	PurgeAndSlideBlocksDown needs to start at a free or purgable block. We walk to 
	 *	regionStart up to find it.
	 */
	do
		{
		if (IsHandleBlock(regionStart))
			{
			if (IsPurgableHandle(regionStart))
				break;
			else 
				regionStart = GetNextBlock(regionStart);
			}
		else
			{
			/* block is free */
			break;
			}
		}
	while (true);

	/*
	 *	We have now found an area big enough to purge. To make sure we don't purge any
	 *	more blocks than we have to, we trim region start. In other words, we move region
	 *	start up to it at all possible. This will help for the situation where there are 
	 *	several small blocks followed by a large block. We could them skip over the 
	 *	smaller blocks in favor of purging the larger block.
	 *
	 *	note:	the first parameter to PurgeAndSlideBlocksDown must be a free or purable
	 *			block.
	 *
	 *	note 2: save region start, we reuse scanLimit since its not used for the rest of 
	 *			this routine.
	 */
	scanLimit = regionStart;
	
	do
		{
		if (IsHandleBlock(regionStart))
			{
			if (IsPurgableHandle(regionStart))
				{
				cumRelocSpace = (cumRelocSpace >= regionStart->size ? cumRelocSpace-regionStart->size : 0);
				if (cumRelocSpace > sizeNeeded)
					{
					/* we can sucessfully skip purging this block */
					}
				else
					{
					scanLimit = regionStart;	/* start purge here */
					break;
					}
				}
			}
		else
			{
			/* block is free */
			cumRelocSpace = (cumRelocSpace >= regionStart->size ? cumRelocSpace-regionStart->size : 0);
			if (cumRelocSpace > sizeNeeded)
				{
				/* we can sucessfully skip over this block */
				}
			else
				{
				scanLimit = regionStart;	/* start purge here */
				break;
				}
			}
		regionStart = GetNextBlock(regionStart);
		}
	while (true);
	
	
	return PurgeAndSlideBlocksDown((freeBlock*)scanLimit, workBlock, curHeap);
	}
	
	
/*
 *	Compacts and purges the heap completely, returns the largest size block that
 *	was created. This routine takes the wimpy way out, it scans once purging all blocks.
 *	Then it compacts the heap. A more efficient algorithm would purge and compact
 *	in one scan like the routine above. For now, I choose the simple solution to avoid 
 *	a nasty complex algorithm.
 *
 *	Note: CompactHeap can return the dummy free block (size=0). So can we.
 */
freeBlock* PurgeAndCompactHeap(stdHeap* curHeap)
	{
	stdBlock*	workBlock;
	stdBlock*	scanLimit;

	#ifdef implemented_discontiguous_heaps
		if (curHeap->fragmentPtr)
			workBlock = curHeap->heapStart;
		else
			workBlock = curHeap->lowestRemovableBlock;
	#else
		workBlock = curHeap->lowestRemovableBlock;
	#endif


	scanLimit = curHeap->backLimit;	

	do
		{
		if (IsUnlockedPurgableBlock(workBlock))
			{
			curHeap->totalPurgableSpace -= workBlock->size;
			workBlock = (stdBlock*) PurgeBlock((handleBlock*)workBlock, curHeap);
			}
		}
	while (scanLimit > (workBlock = GetNextBlock(workBlock)));	/* can terminate when workBlock = 0 */
	
	return CompactHeap(kMaxSize,curHeap);
	}
