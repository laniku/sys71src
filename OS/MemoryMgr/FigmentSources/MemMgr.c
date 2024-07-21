/*
	File:			MemMgr.c

	Contains:	Memory Manager External Routines

	Written by:	Jeff Crawford, Brian Topping, Mike Wiese

	Copyright:	й 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <180>	 1/20/94	BT		#1137209 <BT, jrc> Fix PurgeMem to actually do the purge via
									PurgeAndMakeSpace. It never used to be called for this, so we
									need special consideration for PurgeMem.
	   <179>	 1/19/94	BT		#1135848 <BT, JRG> Weaken tag checks some to accept handles with
									the ptr bit set. There is a conflict that the ptr bit is used to
									mark a busy block in a purge cycle, but this stops the ResMgr
									from getting access to the type since it uses HGetState.
									HGetState bails when the tag check fails. This fixes all cases
									of a handle tag check.
	   <178>	  1/6/94	BT		<BT, jrc> #1134929 PurgeMem is changed to not do a compaction if
									the normal purge cannot get the space it needs. Old IM documents
									this as not moving memory.
	   <177>	10/15/93	BT		Duh, one of those nights.
	   <176>	10/14/93	BT		Looks like a new bug from the ashes, a type was wrong now that
									prototypes are enforced.
	   <175>	10/14/93	BT		<BT, ewa> Radar 1117552; Change interfaces around. Radar
									1114117; fix MoveHHi.
	   <174>	 9/28/93	BT		<BT, ewa> #1114712, MaxApplZone needs to operate on ApplZone,
									not TheZone.
	   <173>	  9/9/93	BT		<ewa, BT> #1110965 Added a fix to SetApplLimit to clear
									curHeap->fHeapIsFullyExtended.  This field is an optimization so
									the growzone doesn't get called if it won't help, but the field
									wasn't getting cleared when the limit was extended.
	   <172>	  9/2/93	BT		<BT, ewa> #1110427, add tag checking for heaps. This is a
									precautionary measure, as bus error handlers are proven most
									effective with a quick tag check.
	   <171>	 8/23/93	BT		<BT, DRF> #ifndef'd tag checks to exercise the bus error
									handlers.  This is a benign check in.
	   <170>	 8/19/93	BT		<BT, cam> Add "#ifdef hasFirstLevelFakeHandleTests" around
									remaining range checks.  This defined in MemMgr.h unless
									"cancelFigmentRangeChecks" is set true.
	   <169>	 8/19/93	JC		<mlw> #1106373, Fix problem when nil is returned by FindHeap.
	   <168>	 8/17/93	BT		<BT, bps> Changed a typecast on LMGetFakeHandleRange().
	   <167>	 8/17/93	JC		<mlw> #1104797, #1106652, Removed odd free MP lists from the
									internal_debug and shipping builds.
	   <166>	 8/12/93	JC		<DRF> #1106070, Fixed HSetState to mask the correct bits to
									protect against unruly clients.
	   <165>	  8/6/93	BT		<BT, BKJ> Radar 1011917: DISKLOCK v2.1.2: Crashes after locking
									disk when idle with Figment on. DiskLock was doing a SetZone
									with a bad value, then doing a MaxBlock. Adding heap checks to
									MaxBlock fixed this instance, although we may want these in
									other places.
	   <164>	  8/5/93	BT		<BT, JC> We came, we saw, we initialed...
	   <163>	  8/4/93	JC		Backed out change <152>, this problem currently breaks, Claris
									CAD, MacDraw II, and MacDraw Pro. #1101865 fixed PurgeMem to
									check to see if the ptr it got back is nil. This fixes the
									MacDraw II problem seen in A3. Made some minor mods to support
									the linked in ThinkC test application.
	   <162>	  8/2/93	JC		#1095953 replaced LMGet/SetRealMemTop with LMGet/
									SetFakeHandleRange to permit heaps above RealMemTop. Modified
									InitZone to raise FakeHandleRange for this situation.
	   <161>	 7/30/93	JC		<mlw> Move ClientDebug routines to be after validity checking in
									DisposePtr. This is attributed to the tag block fix.
	   <160>	 7/29/93	JC		#1102189, #11022190, Fixed MoveHHi to slide blocks up in certain
									situations.
	   <159>	 7/29/93	JC		#1103403, #1103608. Fixed c_PurgeMem to purge all blocks if
									PurgeAndSlideBlocksDown comes up empty.
	   <158>	 7/29/93	JC		Change interface to RemoveHeap to fix OCE bug.
	   <157>	 7/28/93	BT		<BT, JRG> Emergency fix an ugly bug that causes native Figment
									to crash your machine after using Component aware apps. Can't
									use the same interfaces for the "┼Q" calls as the non-dispatched
									until MM is stripping selectors. Added glue for these calls
									here.
	   <156>	 7/27/93	JC		#1100227, Fixed Claris XTND and others who read the first
									longword out of a disposed block. We now move the prevFree link
									of a free block to be 12 bytes lower. Fixed size delta problem
									and removed kWorstCaseBlockOverhead to facilitate this change.
	   <155>	 7/26/93	JC		Commented out ChainedGZProc support code since its never called.
	   <154>	 7/26/93	JC		#1100714 and others. Added fake handle and fake ptr checking by
									comparing tag fields to many common routines. This fixes Digital
									Darkroom and others that pass the range check. Also changed
									SetPtrSize to behave like the old MM when passed a nil ptr
									(crash).
	   <153>	 7/23/93	JC		#1101604 fixed default MP block allocation to be more like the
									old MM.
	   <152>	 7/23/93	JC		Fix bug where we are not creating an MP block during InitZone.
									Unfortunately, I had to special case out the ROZ because it
									already has a corrupted heap that won't work with this change.
	   <151>	 7/21/93	JC		<mw> Fixed bug with A-Train where they disposing a Ptr block
									twice and the block was being backwards coelesced. Also added
									commented out code to call AllocateMoreMasters at the end of
									InitZone. Could not add this code due to a corruption with the
									ROZ.
	   <150>	 7/20/93	JC		Spiffed up the client debug routines for Developer's CD version
									of Figment.
	   <149>	 7/19/93	BT		Even more Radar #1095398. Add fake parameter temporarily to
									strip off the selector that is being passed in from broken
									MixedMode.
	   <148>	 7/16/93	JC		Made changes to support the linked Think C build.
	   <147>	 7/12/93	BMC		StarTrek - adding support for lowmem accessor functions.
	   <146>	  7/7/93	JC		#1096767,1096744,1096911: Fixed FreeMem to not return negative
									values when the heap is full. Fixed PurgeSpace to calculate a
									more accurate value of contiguous purgable space.
	   <145>	  7/7/93	BT		<JRG> Added a trapWord param to PurgeSpaceSystemContiguous when
									I shouldn't have.  Put this back to "void" like it was
									originally.
	   <144>	  7/7/93	BT		BTW - <EPT> initialed the last change.
	   <143>	  7/7/93	BT		Continuation of Radar #1095398. I Forgot to put in D1 trap
									parameter for native glue calling conventions some time back,
									now that it is used it needs to be there.
	   <142>	  7/3/93	BT		This change must not have stayed put. Need to change
									rdDisposeProcProcInfo to uppDisposeProcInfo. Eric did this
									already before change control, I am going to do it again here.
	   <141>	  7/2/93	BT		(With EPT) Radar #1095398. Fix internal Memory Manager calls to
									go thru the trap table interface.
	   <140>	 6/30/93	JC		#1089109: Removed fHeapIsDirty bit.
	   <139>	 6/30/93	JC		Added kREALMEMTOP, so we can test from ThinkC and StartTrek.
									Removed Get/SetPhysMemTop since its not used. Cleaned up
									SecondAndThirdLevelFakeHandleTests by localizing testBlock.
	   <138>	 6/25/93	BT		(with JRG)  Change LMGetPhysMemTop to LMGetRealMemTop.  This
									works with VM.  Also verify that the return values from all the
									routines are getting propageted up properly.
	   <137>	 6/25/93	BT		(with EPT) Backed out last change in favor of changing all
									occurences of MemError() to LMGetMemErr().
	   <136>	 6/25/93	BT		(with EPT) Add LowMem.h to includes for power.
	   <135>	 6/25/93	BT		Fix some typecasting for anal IBM compilers.
	   <134>	 6/25/93	BT		(with JC) Added range checking to handle calls so that the
									relative master pointer is checked to be within the bounds of
									available RAM.  More elaborate code is in here, but commented
									out because we don't want to use it.
	   <133>	 6/17/93	JC		Fixed DisposeHandle, ReallocHandle, EmptyHandle and HGetState to
									echo the old MM when passed a nil or empty (MP=nil) handle.
	   <132>	 6/16/93	JC		Added universal low memory getters and setters.
	   <131>	 6/16/93	BMC	StarTrek - delete SystemZone & ApplicZone since we resolve them
									elsewhere.  Also spunging off of linked_thinkc_app low mem
									global (statics) till low mem access is "macrotized".
	   <130>	 6/15/93	JC		<JRG, JC> Fix __NewHandleHI to conform to new c_NewHandleHI
									calling conventions. Also added NewHandleHi to StarTrek
									interface.
	   <129>	 6/10/93	JC		Added support again for the heap is dirty bit. Removed extra
									parameter to CreateNewHeap.
	   <128>	  6/8/93	JC		Fixed LLInsert to mark block as private.
	   <127>	  6/8/93	JC		Erased some comments.
	   <126>	  6/4/93	JC		Cleaned up internal API for ReallocHandle.
	   <125>	  6/4/93	JC		Changed HeapID's to be a debug feature only.
	   <124>	  6/4/93	JC		Removed use of HeapIsDirty bit for now.
	   <123>	  6/3/93	JC		Fixed routines that call CompactHeap to respect that it can
									return the dummyFree instead of nil.
	   <122>	 5/28/93	BMC	StarTrek glue fixes
		<121>	 5/28/93	BMC	Failed to enter change history comment (hacked in by hand after 
									the fact.
	   <120>	 5/26/93	BT		Added native glue for StraddleBlockSize.
	   <119>	 5/26/93	BT		Finish PowerPC glue and native HeapDispatch.
	   <118>	 5/25/93	BT		Added PowerPC glue for NewHandleHi.
	   <117>	 5/24/93	JC		Changed XXX to DbgXXX for all debug routines.
	   <116>	 5/24/93	JC		Fixed DisposePtr to check to see if the block is already freed.
	   <115>	 5/21/93	BT		Change native glue names to conform to new conventions
	   <114>	 5/20/93	JC		Cleaned up call back procs. Removed c_MoreMastersHi.  Added
									c_RegisterDisposeProc API for ProcessMgr.
	   <113>	 5/19/93	JC		Began changes as requested by the code review. Removed options
									parameter from AllocateMoreMasters.
	   <112>	 5/14/93	JC		Modified ReallocHandle to save pass GZRootHnd on to the grow
									zone proc. Considered an alternate version of ReallocHandle that
									would not empty a the handle before allocating a new one.
									However,  removed this this version before checking it in to
									mimic the old MM.
	   <111>	 5/14/93	JC		Cleaned up implementation of GZRootPtr, GZRootHnd and GZMoveHnd.
	   <110>	  5/7/93	JC		Added support for GZRootHnd. Fixed obscure bug where
									JumpRelocateRange we would fail when we could still slide blocks
									up. Also fixed a bug in MakeSpaceLow to check against backLimit.
									Fixed similar bug in MakeSpaceHigh to check against
									lowestRemoveableBlock. Otimized AlignUp to be 4 assembly
									instructions.
	   <109>	  5/5/93	BT		Whoops, forgot to compile on 68K first, changed a variable name
									in ReallocHandle that follows different naming conventions.
									Something needs to be done about the references to handles as
									master pointers, this is very confusing...
	   <108>	  5/5/93	BT		Some entry points that take handles were not checking for the
									odd master pointer still. The comments implied that they should,
									so I added them.  This fixed another quitting problem in Canvas
									on PDM.
	   <107>	  5/2/93	JC		Put odd free master pointer list back in for any app that does
									not have its compatibility flags set. This odd list is used to
									catch clients who dispose of a block twice, or dispose a block
									then lock it (etc.). When this situation occurs, the call
									returns with memWZErr. I also think I fixed a prob with
									ReallocHandle in debug mode only, but I can't remember.
	   <106>	 4/23/93	JC		Fixed Jeff's heap tree prob when quitting apps that have a
									scrap.
	   <105>	 4/21/93	JC		Fixed AfterDark problem where they dispose first Ptr in the
									heap. Also fixed ProcessMgr problem where it calls SetHandleSize
									when nuking a heap.
	   <104>	 4/21/93	JC		Disabled c_DisposeZone since we now remove the heap from the
									heap tree in DisposeHandle and DisposePtr.
	   <103>	 4/20/93	JC		Added ability to remove heaps from the heap tree when thier
									memory is being disposed.
	   <102>	 4/18/93	JC		Changed #defines to more acurate descriptions. Changed
									small_block_headers to small_freeBlock_headers and linkedIn to
									linked_thinkc_app.   ее Brian & Sam take note.ее
		 <1>	 6/10/92	JC			New Today

*/

#ifndef THINK_C
	#ifdef StarTrek
		#include <MacTypes.h>
		#include <MacMem.h>
		#include <Resource.h>
		#include <SysEqu.h>
		#include <Errors.h>
		#include <OSUtils.h>
	#else
		#include <Types.h>
		#include <Memory.h>
		#include <Resources.h>
		#include <SysEqu.h>
		#include <Errors.h>
		#include <OSUtils.h>
	#endif
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


#ifdef patchedIn
	/* This will overcome the 32k limit */
	#pragma segment Figment
#endif

#ifdef THINK_C
	/* This will overcome the 32k limit */
	#pragma segment Figment
#endif

#ifdef powerc
	#include "QTMemory.h"
#endif

/*
 *	if we are linking in as a Think C project, then declare the global variables here.
 *	Otherwise we define them as Macintosh low mem globals in MemMgr.h.
 */
#if defined(linked_thinkc_app)
	stdHeap*	THEZONE;
	Ptr		APPLLIMIT;
	stdHeap*	SYSZONE;
	stdHeap*	APPLZONE;
	Ptr		HEAPEND;
	Ptr		HIHEAPMARK;
	Handle	gGZROOTHND;				/* put a "g" in front so we don't clash with interface.o */
	Ptr		gGZROOTPTR;				/* put a "g" in front so we don't clash with interface.o */
	Handle	gGZMOVEHND;				/* put a "g" in front so we don't clash with interface.o */
	OSErr		gMEMERROR;				/* put a "g" in front so we don't clash with interface.o */
	void*	gFAKEHANDLERANGE;
#endif /* linked_thinkc_app */


/* Used by StackSpace & Core_IAZ */
#if !defined(powerc) && !defined(StarTrek)
	static pascal  ulong   GetSP(void) = {0x2E8F};		/*	Move.l	A7,(Sp)		*/
#else
	/* 2/16/93 1:44:33 PM (BET): don't have anything for power yet. */
	ulong GetSP()
	{
		long foobar;
		
		return ((ulong)&foobar);
	}
#endif


#if ForROM
	/* this is for the hack used by the Font Manager */
	extern pascal void		DiskCachePurgeProcedure(Handle purgeableHandle);
#endif


	/****************************************************************/
	/* Inline routines															 */
	/****************************************************************/

#define MarkBlockPurgable(block, heap)															\
	{																										\
	IfIntDebugMsg(IsFreeBlock(block), "blockHeader is free", block);					\
	IfIntDebugMsg(block == nil, "blockHeader is nil", block);							\
																											\
	/* If we are marking the block as purable and its not locked, then add it to 	\
		purable space */																				\
	if (IsNonPurgableHandle(block) && IsUnlockedHandle(block))							\
		heap->totalPurgableSpace += block->size;												\
																											\
	block->purgeBit = 1;			/* set purge bit */											\
	}

	
#define MarkBlockNonPurgable(block, heap)														\
	{																										\
	IfIntDebugMsg(IsFreeBlock(block), "blockHeader is free", block);					\
	IfIntDebugMsg(block == nil, "blockHeader is nil", block);							\
																											\
	/* If we are marking the block as not purgable and it is unlocked, then subtract \
		it from purable space */																	\
	if (IsPurgableHandle(block) && IsUnlockedHandle(block))								\
		heap->totalPurgableSpace -= block->size;												\
																											\
	block->purgeBit = 0;			/* clear purge bit */										\
	}


	/****************************************************************/
	/* Non-inline routines														 */
	/****************************************************************/


/*
 *	Note: SetApplBase and InitApplZone are part of the system bootup process. They are not
 *	implemented in C as part of Figment. However, some small changes to the assembly language
 *	routines have been made to load Figment.
 */

void  c_InitZone(GrowZoneProcPtr pGrowZone, short numMasters, void* limitPtr, void* startPtr)
	{
	stdHeap* newZone;

#ifdef hasFirstLevelFakeHandleTests
	/* <162 JC>
	 *	If we are initializing a heap high in ram (ie.- NuBus space), then the fake handle
	 *	range check would fail for that heap. We therefore check the limit, and if it's higher,
	 *	we move the fake handle range check higher so clients can still do normal operations
	 *	on the new heap.
	 */
	if (limitPtr > (void *)LMGetFakeHandleRange())		/* are we creating a heap above the range? */
		LMSetFakeHandleRange(limitPtr);			/* yes, set new range. */
#endif

	/* initializ the new zone and set TheZone to it */
	LMSetTheZone(newZone = CreateNewHeap(pGrowZone, numMasters, limitPtr, startPtr));

	#ifndef patchedIn
		{
		stdHeap*	curHeap;
		
		if (!IsHeap(curHeap = LMGetTheZone())) {
			ClientDebugMsg("Bad heap from LowMem", curHeap);
			LMSetMemErr(memAZErr);
			return;
			}

		if (IsAppHeap(curHeap))
			{
			Ptr limit;
			/* is the new heap limit above HiHeapMark? */
			if (LMGetHiHeapMark() < (limit = (char*)curHeap->backLimit + curHeap->backLimit->size))
				LMSetHiHeapMark(limit);
			}
		}
	#endif
	
	/* <152 JC>
	 *	Allocate the master pointer block as per Inside Mac. 
	 *
	 *	Special note: The Rom Read Only Zone is really messed up. All memory blocks
	 *	in ROM have hard coded relative handles. The means that the offset of the 
	 *	MP with respect the the heap header cannont change. Adding the MP block
	 *	at the start of the heap disrupts the heap enough that MP pointing to ROM
	 *	are written over important block headers. To avoid this problem, we don't
	 *	create an MP in the ROZ untill a handle is created. When the ROZ if fixed,
	 *	remove this code.
	 */
	if (ReadOnlyZone != newZone)
		{
		/* this is not the ROZ, create a MP block */
		AllocateMoreMasters((stdHeap*) startPtr);
		}
	
	/*
	 *	This is for the stupid font manager patch that rolled into SuperMario
	 *	so the Font Manager can set the purge proc.
	 */
	#ifndef patchedIn
		#ifndef linked_thinkc_app
			#if ForROM
				((stdHeap*) startPtr)->purgeProc = DiskCachePurgeProcedure;
			#endif
		#endif
	#endif
	
	LMSetMemErr(noErr);
	}


#if defined(linked_thinkc_app)
/* Not in ROM */
Ptr c_GetApplLimit(void)
	{
	return LMGetApplLimit();
	}
#endif


OSErr c_SetApplLimit(Ptr zoneLimit)
	{
	#ifdef linked_thinkc_app
		ulong		justAValue = 0x400;			/* some value */
		ulong*	DefltStack = &justAValue;
	#elif StarTrek
		ulong		justAValue = 0x6000;			/* some value */
		ulong*	DefltStack = &justAValue;
	#endif
	Ptr	defaultLimit = (Ptr) ((GetSP() - (*(ulong*)DefltStack)));
	
	zoneLimit = (Ptr) AlignDown(MIN(zoneLimit, defaultLimit));
	
	if ((Ptr)(LMGetApplZone())->backLimit > zoneLimit)
		{
		/* note: in the ProcessMgr comments, it complains that there is a bug in the old
			SetApplLimit where it sets ApplLimit if an error is returned. This code
			fixes that bug by exiting before an error is returned. */
		return LMSetMemErr(memFullErr);
		}

	/* if we are extending ApplLimit, clear fHeapFullyExtended */
	if (LMGetApplLimit() < zoneLimit)
		{
		stdHeap*	curHeap;
		if (!IsHeap(curHeap = LMGetTheZone()))
			{
			ClientDebugMsg("Bad heap from LowMem", curHeap);
			return LMSetMemErr(memAZErr);
			}
		curHeap->fHeapFullyExtended = 0;
		}

	LMSetHiHeapMark(LMSetApplLimit(zoneLimit));
	return LMSetMemErr(noErr);
	}
	

OSErr c_MaxApplZone(void)
	{
	stdHeap*	curHeap;
	
	if (!IsHeap(curHeap = LMGetApplZone())) {
		ClientDebugMsg("Bad heap from LowMem", curHeap);
		return LMSetMemErr(memAZErr);
		}
	
	if (!(curHeap->fHeapFullyExtended))
		{		
		LMSetHiHeapMark(LMGetApplLimit());
		
		ExtendApplLimit(kMaxSize,curHeap);	/* sets HEAPEND */
		
		/* Set flag in tell allocation algorithm not to extend the heap zone */
		curHeap->fHeapFullyExtended = 1;
		}
	return (LMSetMemErr(noErr));
	}


OSErr c_MoreMasters(void)
	{
	stdHeap*	curHeap;
	OSErr		theErr;
	
	if (!IsHeap(curHeap = LMGetTheZone())) {
		ClientDebugMsg("Bad heap from LowMem", curHeap);
		return LMSetMemErr(memAZErr);
		}

	theErr = AllocateMoreMasters(curHeap);
	
	FlushCacheIfNeeded(curHeap);
	DbgClientCheckHeap(curHeap);
	return LMSetMemErr(theErr);
	}
	

THz c_GetZone(void)
	{
	LMSetMemErr(noErr);
	return (THz) LMGetTheZone();
	}


OSErr c_SetZone(THz theZone)
	{
	LMSetTheZone((stdHeap*)theZone);
	return LMSetMemErr(noErr);
	}


#ifdef linked_thinkc_app
/* Not in ROM */
THz c_SystemZone(void)
	{
	return (THz) LMGetSysZone();
	}
#endif
	

#ifdef linked_thinkc_app
/* Not in ROM */
THz c_ApplicZone(void)
	{
	return (THz) LMGetApplZone();
	}
#endif
	

OSErr c_NewHandle(Handle* theHandle, ushort trapWord, Size requestedSize)
	{
	stdHeap*			curHeap;
	handleBlock*	newBlock;
	Handle			newMasterPtr;
	blockSize_t		reqBlockSize;

	DbgValidateTrapWord(trapWord);
	if (!IsHeap(curHeap = OperateOnSysHeap(trapWord) ? LMGetSysZone() : LMGetTheZone())) {
		ClientDebugMsg("Bad heap from LowMem", curHeap);
		return LMSetMemErr(memAZErr);
		}
	
	DbgClientCheckHeap(curHeap);
	
	/* allocate more masters if we need too, bail if we failed */
	if (curHeap->firstFreeMP == 0)
		{
		OSErr theErr;
		
		/* allocate a master pointer block, if we are in the ProcessMgrHeap, allocate them
			high. Did we get an error? */
		if (noErr != (theErr = AllocateMoreMasters(curHeap)))
			{
			FlushCacheIfNeeded(curHeap);
			DbgCheckHeap(curHeap);
			*theHandle = nil;
			return LMSetMemErr(theErr);
			}
		}
	
	/* Align the requested size up to a nice multiple */
	reqBlockSize = AlignUp(requestedSize + kBlockOverhead);
	
	/* make sure size is large enough block so we can dispose it */
	if (reqBlockSize < kMinFreeBlockSize)
		reqBlockSize = kMinFreeBlockSize;

	/* allocate new block, bail if we failed */
	if (nil == (newBlock = (handleBlock *) NewBlockFast(reqBlockSize, curHeap)))
		{
		FlushCacheIfNeeded(curHeap);
		DbgCheckHeap(curHeap);
		*theHandle = nil;
		return LMSetMemErr(memFullErr);
		}
	else 
		{
		/* we got the mem, assign the fields */
		newMasterPtr = curHeap->firstFreeMP;
		
		/* advance firstFreeMP to next unused mp, mask off odd bit if desired */
		#ifdef client_debugging
			curHeap->firstFreeMP = UnmaskMPBit(*newMasterPtr);
		#else
			curHeap->firstFreeMP = (Ptr*)*newMasterPtr; 
		#endif
		*newMasterPtr = (Ptr)newBlock->data;
	
		/* set up the blocks relative handle */
		newBlock->relHandle = (long)newMasterPtr - (long)curHeap;

		/* set tags=relocatableType, mpFlags=0, heapID=heapID, sizeDelta=sizeDelta */
		JamTagsFlagsAndSizeDelta(newBlock,
			((ulong)relocatableType << 24) + 
			newBlock->size - requestedSize - kPsuedoBlockSize);
			
		DbgSetBlockHeapID(newBlock, curHeap);

		/* Clear the block if client desires, otherwise, fill it with garbage (debugging) */
		if (ClearTheBlock(trapWord))
			ClearBytes(newBlock->data, reqBlockSize - kBlockHeaderSize);
		else
			DbgGarbageFill(curHeap, newBlock->data, requestedSize);
			
		/* debug stuff */		
		IfDbgMsg(curHeap->handleBlocks++ < 0,"corrupt header", curHeap);
		DbgSetMagic(newBlock->data, requestedSize);
		DbgCode(curHeap->totalDelta += newBlock->sizeDelta);
		
		FlushCacheIfNeeded(curHeap);
		DbgCheckHeap(curHeap);
		*theHandle = newMasterPtr;
		return LMSetMemErr(noErr);
		}
	}


OSErr c_NewEmptyHandle(Handle* theHandle, ushort trapWord)
	{
	stdHeap*		curHeap;
	Handle		newMasterPtr;

	DbgValidateTrapWord(trapWord);
	if (!IsHeap(curHeap = OperateOnSysHeap(trapWord) ? LMGetSysZone() : LMGetTheZone())) {
		ClientDebugMsg("Bad heap from LowMem", curHeap);
		return LMSetMemErr(memAZErr);
		}
	
	DbgClientCheckHeap(curHeap);
	
	/* allocate more masters if we need too, bail if we failed */
	if (curHeap->firstFreeMP == 0)
		{
		OSErr theErr;
		
		if (noErr != (theErr = AllocateMoreMasters(curHeap)))
			{
			FlushCacheIfNeeded(curHeap);
			DbgCheckHeap(curHeap);
			*theHandle = nil;
			return LMSetMemErr(theErr);
			}
		}
	
	/* Set up master pointer */
	newMasterPtr = curHeap->firstFreeMP;
	
	/* advance firstFreeMP to next unused mp, mask off odd bit if desired */
	#ifdef client_debugging
		curHeap->firstFreeMP = UnmaskMPBit(*newMasterPtr);
	#else
		curHeap->firstFreeMP = (Ptr*)*newMasterPtr; 
	#endif
	*newMasterPtr = nil;

	FlushCacheIfNeeded(curHeap);
	DbgCheckHeap(curHeap);
	*theHandle = newMasterPtr;
	return LMSetMemErr(noErr);
	}


OSErr c_NewHandleHi(Handle* theHandle, ushort trapWord, Size requestedSize)
	{
	stdHeap*			curHeap;
	handleBlock*	newBlock;
	Handle			newMasterPtr;
	blockSize_t		reqBlockSize;

	DbgValidateTrapWord(trapWord);
	if (!IsHeap(curHeap = OperateOnSysHeap(trapWord) ? LMGetSysZone() : LMGetTheZone())) {
		ClientDebugMsg("Bad heap from LowMem", curHeap);
		return LMSetMemErr(memAZErr);
		}
	
	DbgClientCheckHeap(curHeap);
	
	/* allocate more masters if we need too, bail if we failed */
	if (curHeap->firstFreeMP == 0)
		{
		/* need a new master pointer block */		
		/* If the heap is the ProcessMgr heap, then we want to allocate master 
			pointer blocks high in the heap otherwise allocate low. Sorry if this is not 
			readable, but I save 2 local variables. Hey its C in it's purist form. */
		if (noErr != AllocateMoreMasters(curHeap))
			{
			FlushCacheIfNeeded(curHeap);
			DbgCheckHeap(curHeap);
			*theHandle = nil;
			return LMSetMemErr(memFullErr);
			}
		}
	
	/* Align the requested size up to a nice multiple */
	reqBlockSize = AlignUp(requestedSize + kBlockOverhead);
	
	/* make sure size is large enough block so we can dispose it */
	if (reqBlockSize < kMinFreeBlockSize)
		reqBlockSize = kMinFreeBlockSize;

	/* allocate new block, bail if we failed */
	if (nil == (newBlock = (handleBlock *) NewBlock(reqBlockSize, kAllocateHigh, curHeap)))
		{
		FlushCacheIfNeeded(curHeap);
		DbgCheckHeap(curHeap);
		*theHandle = (Handle) newBlock;				/* return nil for the handle */
		return LMSetMemErr(memFullErr);
		}
	else 
		{
		/* we got the mem, assign the fields */
		newMasterPtr = curHeap->firstFreeMP;
		
		/* advance firstFreeMP to next unused mp, mask off odd bit */
		#ifdef client_debugging
			curHeap->firstFreeMP = UnmaskMPBit(*newMasterPtr);
		#else
			curHeap->firstFreeMP = (Ptr*)*newMasterPtr; 
		#endif
		*newMasterPtr = (Ptr)newBlock->data;
	
		/* set up the blocks relative handle */
		newBlock->relHandle = (long)newMasterPtr - (long)curHeap;

		/* set tags=relocatableType, mpFlags=0, heapID=heapID, sizeDelta=sizeDelta */
		JamTagsFlagsAndSizeDelta(newBlock,
			((ulong)relocatableType << 24) + 
			newBlock->size - requestedSize - kPsuedoBlockSize);
		DbgSetBlockHeapID(newBlock, curHeap);

		/* Clear the block if client desires, otherwise, fill it with garbage (debugging) */
		if (ClearTheBlock(trapWord))
			ClearBytes(newBlock->data, reqBlockSize - kBlockHeaderSize);
		else
			DbgGarbageFill(curHeap, newBlock->data, requestedSize);
			
		/* debug stuff */		
		IfDbgMsg(curHeap->handleBlocks++ < 0,"corrupt header", curHeap);
		DbgSetMagic(newBlock->data, requestedSize);
		DbgCode(curHeap->totalDelta += newBlock->sizeDelta);
				
		FlushCacheIfNeeded(curHeap);
		DbgCheckHeap(curHeap);
		*theHandle = newMasterPtr;
		return LMSetMemErr(noErr);
		}
	}


OSErr c_DisposeHandle(Handle handle)
	{
	stdHeap*			curHeap;
	handleBlock*	blockHeader;	/* client's text pointer, or blockHeader */

	if (handle == nil)
		{
		return LMSetMemErr(noErr);		/* bail right away */
		}

	/* get pointer to client's text, is it nil? */
	if (nil == (blockHeader = (void*)(*handle)))
		{
		/* Since the block header does not exist, can't get heap header the easy way */
		if (!IsHeap(curHeap = GetZoneFromNilMP(handle))) {
			ClientDebugMsg("Bad heap from Nil MP", curHeap);
			return LMSetMemErr(memAZErr);
			}

		DbgClientCheckHeap(curHeap);

		if (IsReadOnlyZone(curHeap))
			{
			return LMSetMemErr(memROZWarn);
			}

		/* add the mp to the front of the free mp list */
		if (curHeap->firstFreeMP != nil)
			{
			#ifdef client_debugging
				*handle = MaskMPBitOdd(curHeap->firstFreeMP);			/* to catch double disposing clients */
			#else
				*handle = (Ptr)(curHeap->firstFreeMP);
			#endif
			}
		else
			*handle = nil;
		curHeap->firstFreeMP = handle;

		return LMSetMemErr(noErr);
		}
	else
		{
		#ifdef client_debugging
			if (IsOddMP(blockHeader))	/* at this point, blockheader is the handle */
				{
				/*
				 *	the client has most likely disposed of a handle twice. We return 
				 *	right away with an error. This makes apps like PixelPaint work.
				 * This mechanism will hopefully replace the bus error hander mechanism
				 * of the old MM (I hope). Note: now we rely on tag & range checking.
				 */
				DbgClientCheckForDisposedHandle(handle,"MP is odd, are you diposing twice?");
				return LMSetMemErr(memWZErr);
				}
		#endif
		
		/* get the blockheader from the clients text pointer */
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(blockHeader);
		if (!IsHeap(curHeap = GetHeapFromHandleBlock(handle, blockHeader))) {
			ClientDebugMsg("Bad heap from handle block", curHeap);
			return LMSetMemErr(memAZErr);
			}
		
		#ifndef debugNoTagChecking
			/* tag field check for fake handle */
			if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
				{
				if (curHeap != ReadOnlyZone)
					{
					ClientDebugMsg("Bad handle, are you disposing a fake handle?", handle);
					return LMSetMemErr(memWZErr);
					}
				}
		#endif

#ifdef hasFirstLevelFakeHandleTests
		/* range check for fake handle */
		if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you disposing a fake handle?", handle);
			return LMSetMemErr(memWZErr);
			}
#endif

#ifdef hasSecondAndThirdLevelFakeHandleTests
		{
		stdBlock*		testBlock;

		/* double check to see that backLimit points back to this heap */
		if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you disposing a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
			
		if (testBlock->parent != curHeap)
			{
			ClientDebugMsg("Bad handle, are you disposing a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
		}
#endif

		if (IsReadOnlyZone(curHeap))
			{
			/*
			 *	note: we could set the MP to nil here but we choose not to. This is part
			 *	of our mechanism to keep the ROZ a static data structure. Nothing in the
			 *	heap will change.
			 */
			return LMSetMemErr(memROZWarn);
			}

		DbgClientCheckHeap(curHeap);
		DbgMasterPtrCheck(handle, curHeap);
		
		/* call the dispose procedure. ProcessMgr will use it to track temp mem. Other
			clients will want to use it also. */
		if (curHeap->disposeProc)
			{
			FlushCacheIfNeeded(curHeap);
			DbgCheckHeap(curHeap);
			CALL_FNC_PTR_2(DisposeProcPtr,curHeap->disposeProc,uppDisposeProcInfo,handle,(THz)curHeap);
			
			#if 0
				{
				callBackNodePtr	listItem = curHeap->disposeProc;
				/*
				 *	This code will be turned on when the ProcessMgr is revved to call RegisterDisposeProc
				 *	to track temporary memory instead of jamming it itself. Also have to fix
				 *	c_RegisterDisposeProc before making this change.
				 */
				 
				 do 
				 	{
					CALL_FNC_PTR_2(DisposeProcPtr,curHeap->disposeProc,uppDisposeProcInfo,handle,(THz)curHeap);
					if (listItem = LLGetNextItem(listItem))
						continue;	/* there is another dispose proc to call */
					else
						break;		/* no more dispose procs to call */
					}
				while(true);
				}
			#endif
			}

		/* add the mp to the front of the free mp list */
		if (curHeap->firstFreeMP != nil)
			{
			#ifdef client_debugging
				*handle = MaskMPBitOdd(curHeap->firstFreeMP);			/* to catch double disposing clients */
			#else
				*handle = (Ptr)(curHeap->firstFreeMP);
			#endif
			}
		else
			*handle = nil;

		curHeap->firstFreeMP = handle;
		
		DbgCode(curHeap->totalDelta -= (long) blockHeader->sizeDelta);

		/* reset lowestRemovableBlock if needed */
		if (((void*)blockHeader < curHeap->lowestRemovableBlock) &&
			(IsLockedHandle(blockHeader)) &&
				((void*)blockHeader > (void*)(curHeap->heapStart)))
			{
			curHeap->lowestRemovableBlock = blockHeader;
			}
		
		if (IsPurgableHandle(blockHeader) && IsUnlockedBlock(blockHeader))
			{
			curHeap->totalPurgableSpace -= blockHeader->size;
			}
		
		/* are we are disposing of a subHeap? */
		if (blockHeader->subHeapBit)
			{
			/*
			 *	note: This does not happen when disposing app partitions. ProcessMgr
			 *	makes an explicit call to c_DisposeZone since it may not dispose of the
			 *	memory but SetHandleSize on it instead.
			 */
			/* Remove the subheap from the heap tree */
			//RemoveHeap((stdHeap*)(blockHeader->data));
			RemoveHeap((Ptr)blockHeader->data, (Ptr)blockHeader + blockHeader->size);
			}
	
		KillBlock((stdBlock*)blockHeader, curHeap);
		IfDbgMsg(curHeap->handleBlocks-- < 0,"corrupt header", curHeap);
	
		DbgCheckHeap(curHeap);
		return LMSetMemErr(noErr);
		}
	}


/*
 *	note: since this call returns positive results (a size if the trap worked) 
 *	and negative results (and error code if the trap failed), this trap is only
 *	31 bit clean.
 */
Size c_GetHandleSize(const Handle handle)
	{
	handleBlock*	blockHeader;	/* client's text pointer, or blockHeader */

	if (handle == nil)
		{
		return LMSetMemErr(nilHandleErr);		/* bail right away */
		}

	/* get client's text pointer, is it nil? */
	if (nil == (blockHeader = (void*)(*handle)))
		{
		/* we return the sign extended result code here, the MPW glue code will
			force the size to be zero if the result code is negative. It does this
			to make Inside Mac correct. This also applies to the memWZErr check. */
		return LMSetMemErr(nilHandleErr);
		}
	else
		{
		stdHeap*			curHeap;
		blockSize_t		theSize;
		
		#ifdef client_debugging
			if (IsOddMP(blockHeader))	/* at this point, blockheader is the handle */
				{
				/*
				 *	the client has most likely disposed of this handle already. If we are debugging
				 *	the client, we alert them of their foolishness. Otherwise, we return with
				 *	a "block is free" error. This mechanism should replace the bus error handler
				 *	mechism in the old MM (I hope). Note: now we rely on tag & range checking.
				 */
				DbgClientCheckForDisposedHandle(handle,"MP is odd, are getting size of a disposed handle?");
				return LMSetMemErr(memWZErr);
				}
		#endif

		/* get block header from client's text pointer */
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(blockHeader);
		if (!IsHeap(curHeap = GetHeapFromHandleBlock(handle, blockHeader))) {
			ClientDebugMsg("Bad heap from handle block", curHeap);
			return LMSetMemErr(memAZErr);
			}
		
		#ifndef debugNoTagChecking
			/* tag field check for fake handle */
			if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
				{
				if (curHeap != ReadOnlyZone)
					{
					ClientDebugMsg("Bad handle, are you getting size of a fake handle?", handle);
					return LMSetMemErr(memWZErr);
					}
				}
		#endif

#ifdef hasFirstLevelFakeHandleTests
		/* range check for fake handle */
		if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you getting size of a fake handle?", handle);
			return LMSetMemErr(memWZErr);
			}
#endif
			
#ifdef hasSecondAndThirdLevelFakeHandleTests
		{
		stdBlock*		testBlock;

		/* double check to see that backLimit points back to this heap */
		if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you getting size of a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
			
		if (testBlock->parent != curHeap)
			{
			ClientDebugMsg("Bad handle, are you getting size of a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
		}
#endif
	
		DbgMasterPtrCheck(handle, curHeap);
		DbgClientCheckHeap(curHeap);
		
		theSize = blockHeader->size - blockHeader->sizeDelta - kPsuedoBlockSize;
		
		LMSetMemErr(noErr);
		return theSize;
		}
	}


OSErr c_SetHandleSize(Handle handle, Size requestedSize)
	{
	handleBlock*	blockHeader;	/* client's text pointer, or blockHeader */
	
	if (handle == nil)
		{
		return LMSetMemErr(nilHandleErr);		/* bail right away */
		}
	
	/* get clients text pointer, is it nil? */
	if ((blockHeader = (void*)(*handle)) == nil)
		{
		return LMSetMemErr(nilHandleErr);
		}
	else
		{
		stdHeap*			curHeap;
		blockSize_t		reqBlockSize;
		Boolean			blockIsPurgable;
		DbgCode(short sizeDelta);

		#ifdef client_debugging
			if (IsOddMP(blockHeader))	/* at this point, blockheader is the handle */
				{
				/*
				 *	the client has most likely disposed of a handle twice. We return 
				 *	right away with an error. This makes apps like PixelPaint work.
				 * This mechanism will hopefully replace the bus error hander mechanism
				 * of the old MM (I hope). Note: now we rely on tag & range checking.
				 */
				DbgClientCheckForDisposedHandle(handle,"MP is odd, are you setting size twice?");
				return LMSetMemErr(memWZErr);
				}
		#endif		

		/* get block header from client's text pointer */
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(blockHeader);
		if (!IsHeap(curHeap = GetHeapFromHandleBlock(handle, blockHeader))) {
			ClientDebugMsg("Bad heap from handle block", curHeap);
			return LMSetMemErr(memAZErr);
			}

		DbgCode(sizeDelta = blockHeader->sizeDelta);

		#ifndef debugNoTagChecking
			/* tag field check for fake handle */
			if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
				{
				if (curHeap != ReadOnlyZone)
					{
					ClientDebugMsg("Bad handle, are you setting size of a fake handle?", handle);
					return LMSetMemErr(memWZErr);
					}
				}
		#endif

#ifdef hasFirstLevelFakeHandleTests
		/* range check for fake handle */
		if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you setting size of a fake handle?", handle);
			return LMSetMemErr(memWZErr);
			}
#endif
			
#ifdef hasSecondAndThirdLevelFakeHandleTests
		{
		stdBlock*		testBlock;

		/* double check to see that backLimit points back to this heap */
		if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you setting size of a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
			
		if (testBlock->parent != curHeap)
			{
			ClientDebugMsg("Bad handle, are you setting size of a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
		}
#endif	
	
		DbgMasterPtrCheck(handle, curHeap);
		DbgClientCheckHeap(curHeap);
		
	/* Align the requested size up to a nice multiple */
		reqBlockSize = AlignUp(requestedSize + kBlockOverhead);
		
		/* make sure size is large enough block so we can dispose it */
		if (reqBlockSize < kMinFreeBlockSize)
			reqBlockSize = kMinFreeBlockSize;

		/* can the change in size be absorbed in the delta alone? */
		if (reqBlockSize == blockHeader->size)
			{
			/* we take the cheap way out */
			blockHeader->sizeDelta = blockHeader->size - requestedSize - kPsuedoBlockSize;
			DbgCode(curHeap->totalDelta += blockHeader->sizeDelta - sizeDelta);
			DbgSetMagic(blockHeader->data, requestedSize);
			return LMSetMemErr(noErr);
			}

		/* jeff, just check for roz */
		/* are we shrinking a block in the ROZ? */
		if (IsReadOnlyZone(curHeap) && reqBlockSize < blockHeader->size)
			{
			return LMSetMemErr(memROZWarn);
			}

		/* If the block is purgable, mark it as non-purgable so it wont be 
			purged during the move. Later, we will restore the block. */
		if (blockIsPurgable = IsUnlockedPurgableHandle(blockHeader))
			MarkBlockNonPurgable(blockHeader, curHeap)

		/* call SetBlockSize to change the size of the block */		
		LMSetGZRootHnd(handle);		/* incase growzone proc gets called */
		LMSetGZRootPtr(*handle);	/* because the ptr exists (as opposed to reallocating it */
		blockHeader = (handleBlock*) SetBlockSize((stdBlock*)blockHeader, reqBlockSize, curHeap);
		LMSetGZRootHnd(nil);
		LMSetGZRootPtr(nil);
		
		if (blockHeader)
			{
			blockHeader->sizeDelta = blockHeader->size - requestedSize - kPsuedoBlockSize;

			DbgCode(curHeap->totalDelta += blockHeader->sizeDelta - sizeDelta);
			DbgSetMagic(blockHeader->data, requestedSize);
			if (blockIsPurgable)
				MarkBlockPurgable(blockHeader, curHeap);
			FlushCacheIfNeeded(curHeap);
			DbgCheckHeap(curHeap);
			return LMSetMemErr(noErr);
			}
		else
			{
			if (blockIsPurgable)
				{
				blockHeader = (handleBlock*) GetBlockHeaderFromPtr(*handle);	/* re-aquire blockHeader */
				MarkBlockPurgable(blockHeader, curHeap);
				}
			FlushCacheIfNeeded(curHeap);
			DbgCheckHeap(curHeap);
			return LMSetMemErr(memFullErr);
			}
		}
	}


OSErr c_HandleZone(THz* theZone, Handle handle)
	{
	stdHeap*			curHeap;
	handleBlock*	blockHeader;	/* client's text pointer, or blockHeader */

	if (handle == nil)
		{
		*theZone = (THz) LMGetTheZone();
		return LMSetMemErr(noErr);		/* bail right away */
		}

	/* get clients text pointer, is it not nil? */
	if (blockHeader = (void*)(*handle))
		{
		#ifdef client_debugging
			if (IsOddMP(blockHeader))	/* at this point, blockheader is the handle */
				{
				/*
				 *	the client has most likely disposed of a handle twice. We return 
				 *	right away with an error. This makes apps like PixelPaint work.
				 * This mechanism will hopefully replace the bus error hander mechanism
				 * of the old MM (I hope). Note: now we rely on tag & range checking.
				 */
				DbgClientCheckForDisposedHandle(handle,"MP is odd, are you working on a disposed handle?");
				return LMSetMemErr(memWZErr);
				}
		#endif
		
		/* note: no special case code needed for the 32 bit read only zone */
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(blockHeader);
		if (!IsHeap(curHeap = GetHeapFromHandleBlock(handle, blockHeader))) {
			ClientDebugMsg("Bad heap from handle block", curHeap);
			return LMSetMemErr(memAZErr);
			}

		#ifndef debugNoTagChecking
			/* tag field check for fake handle */
			if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
				{
				if (curHeap != ReadOnlyZone)
					{
					ClientDebugMsg("Bad handle, are you calling HandleZone on a fake handle?", handle);
					return LMSetMemErr(memWZErr);
					}
				}
		#endif

#ifdef hasFirstLevelFakeHandleTests
		/* range check for fake handle */
		if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you calling HandleZone on a fake handle?", handle);
			return LMSetMemErr(memWZErr);
			}
#endif
			
#ifdef hasSecondAndThirdLevelFakeHandleTests
		{
		stdBlock*		testBlock;

		/* double check to see that backLimit points back to this heap */
		if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you calling HandleZone on a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
			
		if (testBlock->parent != curHeap)
			{
			ClientDebugMsg("Bad handle, are you calling HandleZone on a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
		}
#endif	
	
		DbgClientCheckHeap(curHeap);

		*theZone = (THz)curHeap;
		return LMSetMemErr(noErr);
		}
	else
		{
		/* Since the block header does not exist, can't get heap header the easy way */
		/* *warning*, this deviates from the old MM which would return TheZone */
		if (!IsHeap((stdHeap*)(*theZone = (THz)GetZoneFromNilMP(handle)))) {
			ClientDebugMsg("Bad heap from nil MP", curHeap);
			return LMSetMemErr(memAZErr);
			}

		return LMSetMemErr(noErr);
		}
	}


/*
 *	RecoverHandle notes....
 *
 *	note: recover handle needs special case code to handle the ROZ
 *
 *	Another note: Since the heap tree is real reliable, we ignor the SYS bit in 
 *	the trap word and call FindHeap instead.
 *
 *	The author of this code wishes to expres his opinions here. This code would be
 *	much easier if handle blocks had direct pointers to the zone instead of 
 *	relative handles. Thankyou. Now back to your regularly scheduled program...
 */
Handle c_RecoverHandle(ushort trapWord, const Ptr textPtr)
{
#pragma unused(trapWord)			/* this is no longer used, should remove it */
	stdHeap*			curHeap;
	handleBlock*	blockHeader;

	DbgValidateTrapWord(trapWord);
	IfClientDebugMsg(textPtr == nil, "textPtr is nil", textPtr);

	blockHeader = (handleBlock*) GetBlockHeaderFromPtr(textPtr);
	
	/* are we recovering a handle in ROM? */
	if (IsBlockInROM(blockHeader))
		{
		/* set up for ReadOnlyZone */
		if (!IsHeap(curHeap = ReadOnlyZone)) {
			ClientDebugMsg("Bad heap from ROZ", curHeap);
			LMSetMemErr(memAZErr);
			return nil;
			}
		LMSetMemErr(memROZWarn);
		}
	else
		{
		if (nil == (curHeap = FindHeap(textPtr)))
			{
			/*
			 *	We could not find a heap in the heap tree, this is real bad. Since
			 *	we have nothing better to return, we wimp out and just return theZone.
			 */
			curHeap = LMGetTheZone();
			}
			
		if (!IsHeap(curHeap)) {
			ClientDebugMsg("Bad heap from FindHeap or LowMem", curHeap);
			LMSetMemErr(memAZErr);
			return nil;
			}

		/* debug stuff */
		DbgClientCheckHeap(curHeap);
		IfClientDebugMsg(blockHeader->relHandle > ((long)curHeap->backLimit - (long)curHeap->heapStart),
				"Warning: relative handle offset too big", blockHeader->relHandle);
		DbgHandleBlockCheck(textPtr, curHeap);
		
		LMSetMemErr(noErr);
		}
		
	return (Handle)(blockHeader->relHandle + (long)curHeap);
}


/*
 * API notes on ReallocHandle:
 *
 *	1. Inside Mac states that "In case of an error, no new block is allocated and the
 *		handle h is left unchanged." Be very careful when reading this statement. When
 *		they say the handle h is left unchanged, they mean that: "the 32 bit quantity h
 *		remains unchanged."
 *
 *	2.	If ReallocHandle fails with memFullErr, then h remains the same, but the block
 *		header and all it contents are disposed and the master pointer is set to nil.
 *		But hey, h is still unchanged.
 */
OSErr c_ReallocHandle(Handle theHandle, Size requestedSize)
	{
	stdHeap*			curHeap;
	handleBlock*	blockHeader;
	blockSize_t		reqBlockSize;
	Handle			pMP;			/* pointer to the master pointer */

	if (theHandle == nil)
		{
		return LMSetMemErr(noErr);		/* bail right away */
		}

	/* Align the requested size up to a nice multiple */
	reqBlockSize = AlignUp(requestedSize + kBlockOverhead);
	
	/* make sure size is large enough block so we can dispose it */
	if (reqBlockSize < kMinFreeBlockSize)
		reqBlockSize = kMinFreeBlockSize;

	/* if the handle is not empty we must empty it first */
	if (*(pMP = theHandle))
		{
		#ifdef client_debugging
			if (IsOddMP(*pMP))
				{
				/*
				 *	the client has most likely disposed of a handle twice. We return 
				 *	right away with an error. This makes apps like PixelPaint work.
				 * This mechanism will hopefully replace the bus error hander mechanism
				 * of the old MM (I hope). Note: now we rely on tag & range checking.
				 */
				DbgClientCheckForDisposedHandle(pMP,"MP is odd, are you reallocating a disposed handle?");
				return LMSetMemErr(memWZErr);
				}
		#endif
		
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(*pMP);
		if (!IsHeap(curHeap = GetHeapFromHandleBlock(pMP, blockHeader))) {
			ClientDebugMsg("Bad heap from handle block", curHeap);
			return LMSetMemErr(memAZErr);
			}

		#ifndef debugNoTagChecking
			/* tag field check for fake handle */
			if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
				{
				if (curHeap != ReadOnlyZone)
					{
					ClientDebugMsg("Bad handle, are you reallocating a fake handle?", pMP);
					return LMSetMemErr(memWZErr);
					}
				}
		#endif

#ifdef hasFirstLevelFakeHandleTests
		/* range check for fake handle */
		if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you reallocating a fake handle?", pMP);
			return LMSetMemErr(memWZErr);
			}
#endif
			
#ifdef hasSecondAndThirdLevelFakeHandleTests
		{
		stdBlock*		testBlock;

		/* double check to see that backLimit points back to this heap */
		if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you reallocating a fake handle?", pMP);
			return LMSetMemErr(memAZErr);
			}
			
		if (testBlock->parent != curHeap)
			{
			ClientDebugMsg("Bad handle, are you reallocating a fake handle?", pMP);
			return LMSetMemErr(memAZErr);
			}
		}
#endif
	
		if (IsReadOnlyZone(curHeap))
			{
			/* note: the old MM used to check for (reqBlockSize > blockHeader->size)
				but returned the same error code (memROZError = memROZWarn). We dont
				do the check at all. */
			return LMSetMemErr(memROZWarn);
			}

		DbgMasterPtrCheck(pMP, curHeap);
		DbgClientCheckHeap(curHeap);

		if (IsLockedHandle(blockHeader))
			{
			return LMSetMemErr(memPurErr);	/* purr like a cat */
			}
		
		*pMP = nil;								/* set the mp to nil */
		DoEmpty(blockHeader, curHeap);
		}
	else
		{
		/* Since the block header does not exist, can't get heap header the easy way */
		if (!IsHeap(curHeap = GetZoneFromNilMP(pMP))) {
			ClientDebugMsg("Bad heap from nil MP", curHeap);
			return LMSetMemErr(memAZErr);
			}

		DbgClientCheckHeap(curHeap);
		}

	/* incase growzone proc gets called so we dont lose the allocated MP */
	/* don't set the root ptr because we are reallocating here */
	LMSetGZRootHnd(pMP);
	blockHeader = (handleBlock *) NewBlockFast(reqBlockSize, curHeap);
	LMSetGZRootHnd(nil);
	
	/* allocate new block, bail if we failed */
	if (nil == blockHeader)
		{
		//*theHandle = nil;						/* return nil for the handle */
		FlushCacheIfNeeded(curHeap);
		DbgCheckHeap(curHeap);
		return LMSetMemErr(memFullErr);
		}
	else 
		{
		/* we got the mem, assign the fields */
	
		/* set up the blocks relative handle */
		blockHeader->relHandle = (long)pMP - (long)curHeap;

		*pMP = (Ptr) blockHeader->data;	/* point the MP to the clients text */

		/* set tags=relocatableType, mpFlags=0, heapID=0, sizeDelta=sizeDelta */
		JamTagsFlagsAndSizeDelta(blockHeader,
			((ulong)relocatableType << 24) + 
			blockHeader->size - requestedSize - kPsuedoBlockSize);
		DbgSetBlockHeapID(blockHeader, curHeap);

		IfDbgMsg(curHeap->handleBlocks++ < 0,"corrupt header", curHeap);
		DbgGarbageFill(curHeap, blockHeader->data, requestedSize);
		DbgSetMagic(blockHeader->data, requestedSize);
		DbgCode(curHeap->totalDelta += blockHeader->sizeDelta);
	
		FlushCacheIfNeeded(curHeap);
		DbgCheckHeap(curHeap);
		return LMSetMemErr(noErr);
		}
	}


OSErr c_NewPtr(Ptr* thePtr, ushort trapWord, Size requestedSize)
	{
	stdHeap*		curHeap;
	ptrBlock*	newBlock;
	blockSize_t	reqBlockSize;

	/* Align the requested size up to a nice multiple */
	reqBlockSize = AlignUp(requestedSize + kBlockOverhead);
	
	/* make sure size is large enough block so we can dispose it */
	if (reqBlockSize < kMinFreeBlockSize)
		reqBlockSize = kMinFreeBlockSize;

	DbgValidateTrapWord(trapWord);
	if (!IsHeap(curHeap = OperateOnSysHeap(trapWord) ? LMGetSysZone() : LMGetTheZone())) {
		ClientDebugMsg("Bad heap from LowMem", curHeap);
		return LMSetMemErr(memAZErr);
		}

	DbgCheckForProcessMgrHeap(curHeap);
	DbgClientCheckHeap(curHeap);
	
	/* allocate the block, if we are in the process mgr heap, allocate the block high */
	if (nil == (newBlock = NewBlock(reqBlockSize, kAllocateLow, curHeap)))
		{
		/* allocation failed */

		FlushCacheIfNeeded(curHeap);
		DbgCheckHeap(curHeap);
		*thePtr = nil;
		return LMSetMemErr(memFullErr);
		}
	else 
		{
		/* allocation worked */
		newBlock->parent = curHeap;
		
		/* set tags=ptrType, mpFlags=0, heapID=0, sizeDelta=sizeDelta */
		JamTagsFlagsAndSizeDelta(newBlock,
			((ulong)ptrType << 24) + 
			newBlock->size - requestedSize - kPsuedoBlockSize);
		DbgSetBlockHeapID(newBlock, curHeap);

		/* reset lowestRemovableBlock */
		if (curHeap->lowestRemovableBlock == newBlock)
			curHeap->lowestRemovableBlock = WalkUpFindNewLowRemoveable(newBlock, curHeap);

		/* Clear the block if client desires, otherwise, fill it with garbage (debugging) */
		if (ClearTheBlock(trapWord))
			ClearBytes(newBlock->data, reqBlockSize - kBlockHeaderSize);
		else
			DbgGarbageFill(curHeap, newBlock->data, requestedSize);
			
		DbgSetMagic(newBlock->data, requestedSize);
		DbgCode(curHeap->totalDelta += newBlock->sizeDelta);
		IfDbgMsg(curHeap->ptrBlocks++ < 0,"corrupt header", curHeap);
		
		FlushCacheIfNeeded(curHeap);
		DbgCheckHeap(curHeap);
		*thePtr = (Ptr)newBlock->data;
		return LMSetMemErr(noErr);
		}
	}


OSErr c_DisposePtr(Ptr block)
	{
	if (block)
		{
		ptrBlock*	blockHeader = (ptrBlock*)GetBlockHeaderFromPtr(block);
		stdHeap*		curHeap;
		freeBlock*	lowBlockFreed;

		if (!IsHeap(curHeap = blockHeader->parent)) {
			ClientDebugMsg("Bad heap from block header", curHeap);
			return LMSetMemErr(memAZErr);
			}
	
		/* is this block already free */
		if (IsFreeBlock(blockHeader))
			{
			/*
			 *	PageMaker has a translator (for MS Word) that calls DisposePtr
			 *	twice on the same block of memory.
			 */
			ClientDebugMsg("Bad ptr block, are you disposing a free block?", block);
			return LMSetMemErr(memWZErr);
			}

		#ifndef debugNoTagChecking
			/* tag field check for fake ptr */
			if (((stdBlock2*)blockHeader)->tags != (uchar)ptrType)
				{
				ClientDebugMsg("Bad ptr block, are you disposing a fake pointer?", block);
				return LMSetMemErr(memWZErr);
				}
		#endif

		if (IsReadOnlyZone(curHeap))
			{
			return LMSetMemErr(memROZWarn);
			}

		DbgCheckForProcessMgrHeap(curHeap);
		DbgClientCheckHeap(curHeap);
		DbgPtrBlockCheck(block, curHeap);
		DbgCode(curHeap->totalDelta -= (long) blockHeader->sizeDelta);
		
		/* are we are disposing of a subHeap? */
		if (blockHeader->subHeapBit)
			{
			/* Remove the subheap from the heap tree */
			//RemoveHeap((stdHeap*)block);
			RemoveHeap((Ptr)blockHeader->data, (Ptr)blockHeader + blockHeader->size);
			}
	
		lowBlockFreed = KillBlock(blockHeader, curHeap);
		
		/*
		 *	This is a fix for the wierd case where clients are disposing a ptr
		 *	twice AND the the block is backwards coelesced. We saw this with the
		 *	ever popular app, A-Train.
		 */
		((stdBlock2*)blockHeader)->tags = 0;		/* old blockheader is now a free block */
		
		/* are we disposing a block lower than the lowestRemovableBlock in the main fragment? */
		#ifndef implemented_discontiguous_heaps
			if ((void*)lowBlockFreed < curHeap->lowestRemovableBlock)
				curHeap->lowestRemovableBlock = lowBlockFreed;
		#else
			if (((void*)lowBlockFreed < curHeap->lowestRemovableBlock) && ((void*)lowBlockFreed >= (void*)(curHeap->heapStart)))
				curHeap->lowestRemovableBlock = lowBlockFreed;
		#endif
	
		IfDbgMsg(--curHeap->ptrBlocks < 0,"corrupt header", curHeap);
		DbgCheckHeap(curHeap);
		}
	return LMSetMemErr(noErr);
	}


/*
 *	Note: since the original call returns positive results through D0 and negative
 *	results through D0, this trap is only 31 bit clean.
 *
 *	Note2: if this routine returns and error, the glue in Interface.o will force
 *	D0 to be zero.  So we don't need to do it here lest we mess things up for
 *	assembly language programmers who are depending on the error code being in D0.
 *
 *	Note3: no special case code needed for the 32 bit read only zone.
 */
Size c_GetPtrSize(const Ptr block)
	{
	ptrBlock*	blockHeader = (ptrBlock*)GetBlockHeaderFromPtr(block);
	#ifdef debugging
	stdHeap*		curHeap = blockHeader->parent;
	#endif

	IfClientDebugMsg(block == nil, "GetPtrSize on a nil ptr", 0);

	/* is this block already free */
	if (IsFreeBlock(blockHeader))
		{
		ClientDebugMsg("Bad ptr block, are you getting size of a free block?", block);
		return LMSetMemErr(memWZErr);
		}

	#ifndef debugNoTagChecking
		/* tag field check for fake ptr */
		if (((stdBlock2*)blockHeader)->tags != (uchar)ptrType)
			{
			ClientDebugMsg("Bad ptr block, are you getting size of a fake pointer?", block);
			return LMSetMemErr(memAZErr);
			}
	#endif

	DbgCheckForProcessMgrHeap(curHeap);
	DbgClientCheckHeap(curHeap);
	DbgPtrBlockCheck(block, curHeap);
	
	LMSetMemErr(noErr);
	return blockHeader->size - kPsuedoBlockSize - blockHeader->sizeDelta;
	}


OSErr c_SetPtrSize(Ptr block, Size requestedSize)
	{
	ptrBlock*		blockHeader = (ptrBlock*) GetBlockHeaderFromPtr(block);
	stdHeap*			curHeap;
	blockSize_t		reqBlockSize;
	OSErr				theErr;
	Boolean			setLRB; /* true => must set lowestRemovableBlock */
	#ifdef debugging
	short sizeDelta = blockHeader->sizeDelta;
	#endif
	
	if (!IsHeap(curHeap = blockHeader->parent)) {
		ClientDebugMsg("Bad heap from block header", curHeap);
		return LMSetMemErr(memAZErr);
		}
	
	IfClientDebugMsg(block == nil, "SetPtrSize on a nil ptr", 0);

	/* is this block already free */
	if (IsFreeBlock(blockHeader))
		{
		ClientDebugMsg("Bad ptr block, are you setting size of a free block?", block);
		return LMSetMemErr(memWZErr);
		}

	#ifndef debugNoTagChecking
		/* tag field check for fake ptr */
		if (((stdBlock2*)blockHeader)->tags != (uchar)ptrType)
			{
			ClientDebugMsg("Bad ptr block, are you setting size of a fake pointer?", block);
			return LMSetMemErr(memAZErr);
			}
	#endif

	DbgCheckForProcessMgrHeap(curHeap);
	DbgClientCheckHeap(curHeap);
	DbgPtrBlockCheck(block, curHeap);

	/* Align the requested size up to a nice multiple */
	reqBlockSize = AlignUp(requestedSize + kBlockOverhead);
	
	/* make sure size is large enough block so we can dispose it */
	if (reqBlockSize < kMinFreeBlockSize)
		reqBlockSize = kMinFreeBlockSize;

	/* can the change in size be absorbed in the delta alone? */
	if (reqBlockSize == blockHeader->size)
		{
		/* we take the cheap way out */
		blockHeader->sizeDelta = blockHeader->size - requestedSize - kPsuedoBlockSize;

		DbgCode(curHeap->totalDelta += blockHeader->sizeDelta - sizeDelta);
		DbgSetMagic(blockHeader->data, requestedSize);
		return LMSetMemErr(noErr);
		}
	
	/* are we shrinking a block in the ROZ? */
	if (IsReadOnlyZone(curHeap) && reqBlockSize < blockHeader->size)
		{
		return LMSetMemErr(memROZWarn);
		}
	
	setLRB = (curHeap->lowestRemovableBlock == GetNextBlock(blockHeader));
	
	/* call SetBlockSize to change the size of the block */		
	LMSetGZRootPtr(block);		/* incase growzone proc gets called */
	blockHeader = SetBlockSize(blockHeader, reqBlockSize, curHeap);
	LMSetGZRootPtr(nil);
	
	if (blockHeader)
		{
		blockHeader->sizeDelta = blockHeader->size - requestedSize - kPsuedoBlockSize;
		if (setLRB)
			curHeap->lowestRemovableBlock = WalkUpFindNewLowRemoveable(blockHeader, curHeap);

		DbgCode(curHeap->totalDelta += blockHeader->sizeDelta - sizeDelta);
		DbgSetMagic(blockHeader->data, requestedSize);
		theErr = noErr;
		}
	else
		{
		theErr = memFullErr;
		}
	
	FlushCacheIfNeeded(curHeap);
	DbgCheckHeap(curHeap);
	return LMSetMemErr(theErr);
	}


OSErr c_PtrZone(THz* theZone, Ptr thePtr)
	{
	ptrBlock*	blockHeader = (ptrBlock*) GetBlockHeaderFromPtr(thePtr);
	stdHeap*		curHeap;

	if (!IsHeap(curHeap = blockHeader->parent)) {
		ClientDebugMsg("Bad heap from block header", curHeap);
		return LMSetMemErr(memAZErr);
		}
	
	IfClientDebugMsg(thePtr == nil,"PtrZone on a nil ptr",0);

	/* is this block already free */
	if (IsFreeBlock(blockHeader))
		{
		ClientDebugMsg("Bad ptr block, are you calling PtrZone on a free block?", thePtr);
		return LMSetMemErr(memWZErr);
		}

	#ifndef debugNoTagChecking
		/* tag field check for fake ptr */
		if (((stdBlock2*)blockHeader)->tags != (uchar)ptrType)
			{
			ClientDebugMsg("Bad ptr block, are you calling PtrZone on a fake pointer?", thePtr);
			return LMSetMemErr(memAZErr);
			}
	#endif

	DbgCheckForProcessMgrHeap(curHeap);
	DbgClientCheckHeap(curHeap);

	*theZone = (THz)curHeap;
	return LMSetMemErr(noErr);
	}


long c_FreeMem(ushort trapWord)
	{
	stdHeap*	curHeap;
	
	/*
	 *	This returns the physical block size (clientSize + header + sizeDelta) instead of
	 *	logical size. As stupid as this sounds, that is exactly what the old MM returns. 
	 *	Although the new blockHeader sizes are now 16 bytes as opposed to 12, I don't think 
	 *	this will break anyone. An alternative way to fix this is to walk all the free blocks 
	 *	and accumulate the logical free size. I choose not to do this. Yet anthother way to 
	 *	get the right size is to convert physical to logical size inside all the internal 
	 *	routines that set curHeap->totalFree. I choose not to this since it takes to much 
	 *	time. So the best thing to do is to return the not quite correct physical free size 
	 *	of the heap instead of the logical size. 
	
	 *	Just for more safety, I subtract  off the block header size to make the figure
	 *	a little more closer to reality.
	 */
	
	DbgValidateTrapWord(trapWord);
	curHeap = OperateOnSysHeap(trapWord) ? LMGetSysZone() : LMGetTheZone();
	DbgClientCheckHeap(curHeap);
	LMSetMemErr(noErr);
	return curHeap->totalFree ? (curHeap->totalFree - kBlockOverhead) : 0;
	}

	
Size c_MaxMem(ushort trapWord, Size *growSize)
	{
	stdHeap*		curHeap;
	freeBlock*	free;

	DbgValidateTrapWord(trapWord);
	curHeap = OperateOnSysHeap(trapWord) ? LMGetSysZone() : LMGetTheZone();
	DbgClientCheckHeap(curHeap);
	
	free = PurgeAndCompactHeap(curHeap);
	
	if (IsAppHeap(curHeap))
		{
		/* jeff, warning, the old MM returns the MIN(ApplLimit,(SP-MinStack))
			might want to consider this feature. */
		*growSize = LMGetApplLimit() - (Ptr) curHeap->backLimit - curHeap->backLimit->size;
		}
	else
		*growSize = 0;

	FlushCacheIfNeeded(curHeap);
	DbgCheckHeap(curHeap);
	LMSetMemErr(noErr);
	
	return free->size ? (free->size - kBlockOverhead) : 0;
	}
	

Size c_CompactMem(ushort trapWord, Size sizeNeeded)
	{
	stdHeap*		curHeap;
	blockSize_t	reqBlockSize;
	freeBlock*	largestBlock;
	
	/* Align the sizeNeeded size up to a nice multiple */
	reqBlockSize = AlignUp(sizeNeeded + kBlockOverhead);
	
	/* make sure size is large enough block so we can dispose it */
	if (reqBlockSize < kMinFreeBlockSize)
		reqBlockSize = kMinFreeBlockSize;

	DbgValidateTrapWord(trapWord);
	curHeap = OperateOnSysHeap(trapWord) ? LMGetSysZone() : LMGetTheZone();
	DbgClientCheckHeap(curHeap);

	LMSetMemErr(noErr);
	
	largestBlock = CompactHeap(reqBlockSize, curHeap);
	
	FlushCacheIfNeeded(curHeap);
	DbgCheckHeap(curHeap);
		
	return largestBlock->size ? (largestBlock->size - kBlockOverhead) : 0;
	}


OSErr c_ReserveMem(ushort trapWord, Size sizeNeeded)
	{
	stdHeap*		curHeap;
	blockSize_t	reqBlockSize ;
	freeBlock*	free;
	OSErr			theErr;
	
	/* Align the sizeNeeded size up to a nice multiple */
	reqBlockSize = AlignUp(sizeNeeded + kBlockOverhead);
	
	/* make sure size is large enough block so we can dispose it */
	if (reqBlockSize < kMinFreeBlockSize)
		reqBlockSize = kMinFreeBlockSize;

	DbgValidateTrapWord(trapWord);
	curHeap = OperateOnSysHeap(trapWord) ? LMGetSysZone() : LMGetTheZone();
	DbgCheckForProcessMgrHeap(curHeap);
	DbgClientCheckHeap(curHeap);
	
	/* allocate more masters if we need too, bail if we failed */
	if (curHeap->firstFreeMP == 0)
		{
		/* allocate a master pointer block, if we are in the ProcessMgrHeap, allocate them
			high. Did we get an error? */
		if (noErr != (theErr = AllocateMoreMasters(curHeap)))
			{
			FlushCacheIfNeeded(curHeap);
			DbgCheckHeap(curHeap);
			return LMSetMemErr(theErr);
			}
		}

	if (nil == (free = MakeSpaceLow(reqBlockSize, kAllocateLow, curHeap)))
		{
		theErr = LMSetMemErr(memFullErr);
		}
	else
		{
		curHeap->favoredFree = free;
		theErr = LMSetMemErr(noErr);
		}
	
	FlushCacheIfNeeded(curHeap);
	DbgCheckHeap(curHeap);
	return theErr;
	}


OSErr c_PurgeMem(ushort trapWord, Size sizeNeeded)
	{
	stdHeap*		curHeap;
	freeBlock*	free;
	OSErr			theErr;

	DbgValidateTrapWord(trapWord);
	curHeap = OperateOnSysHeap(trapWord) ? LMGetSysZone() : LMGetTheZone();
	DbgClientCheckHeap(curHeap);

	/* Align the sizeNeeded size up to a nice multiple */
	sizeNeeded = AlignUp(sizeNeeded + kBlockOverhead);
	
	/* make sure size is large enough block so we can dispose it */
	if (sizeNeeded < kMinFreeBlockSize)
		sizeNeeded = kMinFreeBlockSize;

	free = PurgeAndMakeSpace(sizeNeeded, curHeap, true);
	if (free->size >= sizeNeeded)
		theErr = LMSetMemErr(noErr);
	else
		theErr = LMSetMemErr(memFullErr);
	
	FlushCacheIfNeeded(curHeap);
	DbgCheckHeap(curHeap);
	
	return theErr;
	}
	

OSErr c_EmptyHandle(Handle handle)
	{
	stdHeap*			curHeap;
	handleBlock*	blockHeader;	/* client's text pointer, or blockHeader */
	
	if (handle == nil)
		{
		return LMSetMemErr(noErr);		/* bail right away */
		}

	/* get client's text pointer, is it not nil? */
	if (blockHeader = (void*)(*handle))
		{
		#ifdef client_debugging
			if (IsOddMP(blockHeader))	/* at this point, blockheader is the handle */
				{
				/*
				 *	the client has most likely disposed of a handle twice. We return 
				 *	right away with an error. This makes apps like PixelPaint work.
				 * This mechanism will hopefully replace the bus error hander mechanism
				 * of the old MM (I hope). Note: now we rely on tag & range checking.
				 */
				DbgClientCheckForDisposedHandle(handle,"MP is odd, are you emptying a disposed handle?");
				return LMSetMemErr(memWZErr);
				}
		#endif		

		/* get block header from clients text pointer */
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(blockHeader);
		if (!IsHeap(curHeap = GetHeapFromHandleBlock(handle, blockHeader))) {
			ClientDebugMsg("Bad heap from block header", curHeap);
			return LMSetMemErr(memAZErr);
			}

		#ifndef debugNoTagChecking
			/* tag field check for fake handle */
			if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
				{
				if (curHeap != ReadOnlyZone)
					{
					ClientDebugMsg("Bad handle, are you emptying a fake handle?", handle);
					return LMSetMemErr(memWZErr);
					}
				}
		#endif

#ifdef hasFirstLevelFakeHandleTests
		/* range check for fake handle */
		if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you emptying a fake handle?", handle);
			return LMSetMemErr(memWZErr);
			}
#endif
			
#ifdef hasSecondAndThirdLevelFakeHandleTests
		{
		stdBlock*		testBlock;

		/* double check to see that backLimit points back to this heap */
		if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you emptying a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
			
		if (testBlock->parent != curHeap)
			{
			ClientDebugMsg("Bad handle, are you emptying a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
		}
#endif	
	
		DbgMasterPtrCheck(handle, curHeap);
		DbgClientCheckHeap(curHeap);

		if (IsLockedHandle(blockHeader))
			{
			return LMSetMemErr(memPurErr);
			}
			
		if (IsReadOnlyZone(curHeap))
			{
			*handle = nil;						/* zero the master pointer */
			return LMSetMemErr(noErr);
			}

		*handle = nil;		/* set the mp to nil */
		DoEmpty(blockHeader, curHeap);
	
		DbgCheckHeap(curHeap);
		return LMSetMemErr(noErr);
		}
	else
		{
		return LMSetMemErr(noErr);
		}
	}
	
	
OSErr c_HLock(Handle handle)
	{
	stdHeap*			curHeap;
	handleBlock*	blockHeader;	/* client's text pointer, or blockHeader */

	if (handle == nil)
		{
		return LMSetMemErr(nilHandleErr);		/* bail right away */
		}

	/* get client's text pointer, is it not nil? */
	if (blockHeader = (void*)(*handle))
		{
		#ifdef client_debugging
			if (IsOddMP(blockHeader))	/* at this point, blockheader is the handle */
				{
				/*
				 *	the client has most likely disposed of this handle already. If we are debugging
				 *	the client, we alert them of their foolishness. Otherwise, we return with
				 *	a "block is free" error. This mechanism should replace the bus error handler
				 *	mechism in the old MM (I hope). Note: now we rely on tag & range checking.
				 */
				DbgClientCheckForDisposedHandle(handle,"MP is odd, are you locking a disposed handle?");
				return LMSetMemErr(memWZErr);
				}
		#endif

		/* get block header from client's text pointer */
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(blockHeader);
		if (!IsHeap(curHeap = GetHeapFromHandleBlock(handle, blockHeader))) {
			ClientDebugMsg("Bad heap from block header", curHeap);
			return LMSetMemErr(memAZErr);
			}
	
		#ifndef debugNoTagChecking
			/* tag field check for fake handle */
			if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
				{
				if (curHeap != ReadOnlyZone)
					{
					ClientDebugMsg("Bad handle, are you locking a fake handle?", handle);
					return LMSetMemErr(memWZErr);
					}
				}
		#endif

#ifdef hasFirstLevelFakeHandleTests
		/* range check for fake handle */
		if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you locking a fake handle?", handle);
			return LMSetMemErr(memWZErr);
			}
#endif
			
#ifdef hasSecondAndThirdLevelFakeHandleTests
		{
		stdBlock*		testBlock;

		/* double check to see that backLimit points back to this heap */
		if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you locking a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
			
		if (testBlock->parent != curHeap)
			{
			ClientDebugMsg("Bad handle, are you locking a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
		}
#endif	
	
		if (IsReadOnlyZone(curHeap))
			{
			/* ResourceMgr likes to lock the resource map in the Read Only Zone */
			if (IsBlockInROM(blockHeader))
				return LMSetMemErr(noErr);
			}

		IfClientDebugMsg(IsPtrBlock(blockHeader),"not a valid handle", handle);
		DbgClientCheckHeap(curHeap);

		/* if client is locking a purgable block, adjust totalPurgableSpace */
		if (IsPurgableHandle(blockHeader) && IsUnlockedHandle(blockHeader))
			curHeap->totalPurgableSpace -= blockHeader->size;

		blockHeader->lockBit = 1;			/* set locked bit */

		/* reset lowestRemovableBlock */
		if (curHeap->lowestRemovableBlock == blockHeader)
			curHeap->lowestRemovableBlock = WalkUpFindNewLowRemoveable((stdBlock*)blockHeader, curHeap);

		return LMSetMemErr(noErr);
		}
	else
		{
		return LMSetMemErr(nilHandleErr);
		}
	}


OSErr c_HUnlock(Handle handle)
	{
	stdHeap*			curHeap;
	handleBlock*	blockHeader;	/* client's text pointer, or blockHeader */

	if (handle == nil)
		{
		return LMSetMemErr(nilHandleErr);		/* bail right away */
		}

	/* get client's text pointer, is it not nil? */
	if (blockHeader = (void*)(*handle))
		{
		#ifdef client_debugging
			if (IsOddMP(blockHeader))	/* at this point, blockheader is the handle */
				{
				/*
				 *	the client has most likely disposed of this handle already. If we are debugging
				 *	the client, we alert them of their foolishness. Otherwise, we return with
				 *	a "block is free" error. This mechanism should replace the bus error handler
				 *	mechism in the old MM (I hope). Note: now we rely on tag & range checking.
				 */
				DbgClientCheckForDisposedHandle(handle,"MP is odd, are you unlocking a disposed handle?");
				return LMSetMemErr(memWZErr);
				}
		#endif

		/* get block header from client's text pointer */
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(blockHeader);
		if (!IsHeap(curHeap = GetHeapFromHandleBlock(handle, blockHeader))) {
			ClientDebugMsg("Bad heap from block header", curHeap);
			return LMSetMemErr(memAZErr);
			}

		#ifndef debugNoTagChecking
			/* tag field check for fake handle */
			if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
				{
				if (curHeap != ReadOnlyZone)
					{
					ClientDebugMsg("Bad handle, are you unlocking a fake handle?", handle);
					return LMSetMemErr(memWZErr);
					}
				}
		#endif

#ifdef hasFirstLevelFakeHandleTests
		/* range check for fake handle */
		if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you unlocking a fake handle?", handle);
			return LMSetMemErr(memWZErr);
			}
#endif
			
#ifdef hasSecondAndThirdLevelFakeHandleTests
		{
		stdBlock*		testBlock;

		/* double check to see that backLimit points back to this heap */
		if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you unlocking a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
			
		if (testBlock->parent != curHeap)
			{
			ClientDebugMsg("Bad handle, are you unlocking a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
		}
#endif	
	
		if (IsReadOnlyZone(curHeap))
			{
			return LMSetMemErr(noErr);
			}

		IfClientDebugMsg(IsPtrBlock(blockHeader),"not a valid handle", handle);
		DbgClientCheckHeap(curHeap);

		/* if client is unlocking a purgable block, adjust totalPurgableSpace */
		if (IsPurgableHandle(blockHeader) && IsLockedHandle(blockHeader))
			curHeap->totalPurgableSpace += blockHeader->size;

		blockHeader->lockBit = 0;			/* clear locked bit */		

		/* resest lowestRemoveableBlock */
		if (((void*)blockHeader < curHeap->lowestRemovableBlock) && ((void*)blockHeader > (void*)(curHeap->heapStart)))
			curHeap->lowestRemovableBlock = blockHeader;

		return LMSetMemErr(noErr);
		}
	else
		{
		return LMSetMemErr(nilHandleErr);
		}
	}


OSErr c_HPurge(Handle handle)
	{
	stdHeap*			curHeap;
	handleBlock*	blockHeader;	/* client's text pointer, or blockHeader */

	if (handle == nil)
		{
		return LMSetMemErr(nilHandleErr);		/* bail right away */
		}

	/* get client's text pointer, is it not nil? */
	if (blockHeader = (void*)(*handle))
		{
		#ifdef client_debugging
			if (IsOddMP(blockHeader))	/* at this point, blockheader is the handle */
				{
				/*
				 *	the client has most likely disposed of this handle already. If we are debugging
				 *	the client, we alert them of their foolishness. Otherwise, we return with
				 *	a "block is free" error. This mechanism should replace the bus error handler
				 *	mechism in the old MM (I hope). Note: now we rely on tag & range checking.
				 */
				DbgClientCheckForDisposedHandle(handle,"MP is odd, are you HPurging a disposed handle?");
				return LMSetMemErr(memWZErr);
				}
		#endif

		/* get block header from client's text pointer */
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(blockHeader);
		if (!IsHeap(curHeap = GetHeapFromHandleBlock(handle, blockHeader))) {
			ClientDebugMsg("Bad heap from block header", curHeap);
			return LMSetMemErr(memAZErr);
			}

		#ifndef debugNoTagChecking
			/* tag field check for fake handle */
			if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
				{
				if (curHeap != ReadOnlyZone)
					{
					ClientDebugMsg("Bad handle, are you HPurging a fake handle?", handle);
					return LMSetMemErr(memWZErr);
					}
				}
		#endif

#ifdef hasFirstLevelFakeHandleTests
		/* range check for fake handle */
		if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you HPurging a fake handle?", handle);
			return LMSetMemErr(memWZErr);
			}
#endif
			
#ifdef hasSecondAndThirdLevelFakeHandleTests
		{
		stdBlock*		testBlock;

		/* double check to see that backLimit points back to this heap */
		if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you HPurging a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
			
		if (testBlock->parent != curHeap)
			{
			ClientDebugMsg("Bad handle, are you HPurging a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
		}
#endif	
	
		if (IsReadOnlyZone(curHeap))
			{
			return LMSetMemErr(noErr);
			}

		IfClientDebugMsg(IsPtrBlock(blockHeader),"not a valid handle", handle);
		DbgClientCheckHeap(curHeap);

		MarkBlockPurgable(blockHeader,curHeap);

		return LMSetMemErr(noErr);
		}
	else
		{
		return LMSetMemErr(nilHandleErr);
		}
	
	}
	

OSErr c_HNoPurge(Handle handle)
	{
	stdHeap*			curHeap;
	handleBlock*	blockHeader;	/* client's text pointer, or blockHeader */

	if (handle == nil)
		{
		return LMSetMemErr(nilHandleErr);		/* bail right away */
		}

	/* get client's text pointer, is it not nil? */
	if (blockHeader = (void*)(*handle))
		{
		#ifdef client_debugging
			if (IsOddMP(blockHeader))	/* at this point, blockheader is the handle */
				{
				/*
				 *	the client has most likely disposed of this handle already. If we are debugging
				 *	the client, we alert them of their foolishness. Otherwise, we return with
				 *	a "block is free" error. This mechanism should replace the bus error handler
				 *	mechism in the old MM (I hope). Note: now we rely on tag & range checking.
				 */
				DbgClientCheckForDisposedHandle(handle,"MP is odd, are you HNopurging a disposed handle?");
				return LMSetMemErr(memWZErr);
				}
		#endif

		/* get block header from client's text pointer */
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(blockHeader);
		if (!IsHeap(curHeap = GetHeapFromHandleBlock(handle, blockHeader))) {
			ClientDebugMsg("Bad heap from block header", curHeap);
			return LMSetMemErr(memAZErr);
			}

		#ifndef debugNoTagChecking
			/* tag field check for fake handle */
			if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
				{
				if (curHeap != ReadOnlyZone)
					{
					ClientDebugMsg("Bad handle, are you HNopurging a fake handle?", handle);
					return LMSetMemErr(memWZErr);
					}
				}
		#endif

#ifdef hasFirstLevelFakeHandleTests
		/* range check for fake handle */
		if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you HNopurging a fake handle?", handle);
			return LMSetMemErr(memWZErr);
			}
#endif
			
#ifdef hasSecondAndThirdLevelFakeHandleTests
		{
		stdBlock*		testBlock;

		/* double check to see that backLimit points back to this heap */
		if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you HNopurging a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
			
		if (testBlock->parent != curHeap)
			{
			ClientDebugMsg("Bad handle, are you HNopurging a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
		}
#endif	
	
		if (IsReadOnlyZone(curHeap))
			{
			return LMSetMemErr(noErr);
			}

		IfClientDebugMsg(IsPtrBlock(blockHeader),"not a valid handle", handle);
		DbgClientCheckHeap(curHeap);

		MarkBlockNonPurgable(blockHeader,curHeap);

		return LMSetMemErr(noErr);
		}
	else
		{
		return LMSetMemErr(nilHandleErr);
		}
	}
	

/*
 *	ProcessMgr patches the old SetGrowZone routine so 1) It can save the gzProc as 
 *	part of the app's pcb chain it to its own gzProc. 2) so apps can not change the 
 *	gzProc for the system heap or the processMgr heap and 3) to prevent apps from 
 *	restoring the ProcessMgr gzProc.
 */
OSErr c_SetGrowZone(GrowZoneProcPtr theGrowZoneProc)
	{
	stdHeap* curHeap;
	
	/* ProcessMgr prevents apps from setting the grow zone of the system heap. This is to
		stop skanky apps that want to hang off the system grow zone proc. */
	if ( (curHeap = LMGetTheZone()) != LMGetSysZone())
		curHeap->gzProc = theGrowZoneProc;
		
	return LMSetMemErr(noErr);
	}
	

#if defined(linked_thinkc_app)
/* Not in ROM */
Handle c_GZSaveHnd(void)
	{
	return gGZROOTHND;
	}
#endif


/*
	Figment does not implement BlockMove()
*/


#if defined(linked_thinkc_app)
/* not in ROM */
Ptr c_TopMem(void)
	{
	return nil; /* jeff, figure what to return here */
	}
#endif


/*
 *	Moves a handle high. Currently, the new implementation of MoveHHi differs from the old
 *	one in that moves that handle to the top of the heap instead of the top of the current
 *	region. This implementation is much slower. I'm still investigating it.
 */
OSErr c_MoveHHi(Handle handle)
	{
	stdHeap*			curHeap;
	handleBlock*	blockHeader;	/* client's text pointer, or blockHeader */

	if (handle == nil)
		{
		return LMSetMemErr(nilHandleErr);		/* bail right away */
		}

	/* get client's text pointer, is it nil? */
	if ((blockHeader = (void*)(*handle)) == nil)
		{
		return LMSetMemErr(nilHandleErr);
		}
		
	#ifdef client_debugging
		if (IsOddMP(blockHeader))	/* at this point, blockheader is the handle */
			{
			/*
			 *	the client has most likely disposed of a handle twice. We return 
			 *	right away with an error. This makes apps like PixelPaint work.
			 * This mechanism will hopefully replace the bus error hander mechanism
			 * of the old MM (I hope). Note: now we rely on tag & range checking.
			 */
			DbgClientCheckForDisposedHandle(handle,"MP is odd, are you moving high a disposed handle?");
			return LMSetMemErr(memWZErr);
			}
	#endif

	/* get block header from client's text pointer */
	blockHeader = (handleBlock*) GetBlockHeaderFromPtr(blockHeader);
	if (!IsHeap(curHeap = GetHeapFromHandleBlock(handle, blockHeader))) {
		ClientDebugMsg("Bad heap from block header", curHeap);
		return LMSetMemErr(memAZErr);
		}

	#ifndef debugNoTagChecking
		/* tag field check for fake handle */
		if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
			{
			if (curHeap != ReadOnlyZone)
				{
				ClientDebugMsg("Bad handle, are you moving high a fake handle?", handle);
				return LMSetMemErr(memWZErr);
				}
			}
	#endif

#ifdef hasFirstLevelFakeHandleTests
	/* range check for fake handle */
	if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you moving high a fake handle?", handle);
			return LMSetMemErr(memWZErr);
			}
#endif
			
#ifdef hasSecondAndThirdLevelFakeHandleTests
	{
	stdBlock*		testBlock;

	/* double check to see that backLimit points back to this heap */
	if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
		{
		ClientDebugMsg("Bad handle, are you moving high a fake handle?", handle);
		return LMSetMemErr(memAZErr);
		}
		
	if (testBlock->parent != curHeap)
		{
		ClientDebugMsg("Bad handle, are you moving high a fake handle?", handle);
		return LMSetMemErr(memAZErr);
		}
	}
#endif	

	DbgClientCheckHeap(curHeap);

	/* Blocks are never moved in the ROZ, no need to check for it. */
	
	if (IsLockedHandle(blockHeader))
		{
		return LMSetMemErr(memLockedErr);
		}
	else
		{
		Boolean		blockIsPurgable;
		
		/* If the block is purgable, mark it as non-purgable so it wont be 
			purged during the move. Later, we will restore the block. */
		if (blockIsPurgable = IsUnlockedPurgableHandle(blockHeader))
			MarkBlockNonPurgable(blockHeader, curHeap);
			
		/* 10/13/93 11:55:08 AM (BET): it was previously thought that the MoveHnd was the one
				being moved high; MoveHnd is really the currently modified handle _while we are
				compacting_.  This means we should be setting RootHnd and RootPtr to this block
				and setting MoveHnd to each block we shuffle to comply with this request. */
		LMSetGZRootHnd(handle);
		LMSetGZRootPtr(*handle);
		
		/* is the block in the system heap or has the zone been fully extended (MaxApplZone)? */
		if (IsSystemHeap(curHeap))
			{
			/* moving the block high makes the worse, so we move it low */
			MoveBlockLow(blockHeader, curHeap);
			}
		else
			{
			MoveBlockHigh(blockHeader, curHeap);
			}
		LMSetGZRootHnd(nil);
		LMSetGZRootPtr(nil);

		/* note: at this point blockHeader has moved, so we can not use it */
	
		/* do we need to restore purgability to the block */
		if (blockIsPurgable)
			{
			/* reclaim block header */
			blockHeader = (handleBlock*) GetBlockHeaderFromPtr(*handle);
			MarkBlockPurgable(blockHeader, curHeap);
			}

		FlushCacheIfNeeded(curHeap);
		DbgCheckHeap(curHeap);
		return LMSetMemErr(noErr);
		}
	}


OSErr c_MoveHLow(Handle handle)
	{
	stdHeap*			curHeap;
	handleBlock*	blockHeader;	/* client's text pointer, or blockHeader */

	if (handle == nil)
		{
		return LMSetMemErr(nilHandleErr);		/* bail right away */
		}

	/* get client's text pointer, is it not nil? */
	if (blockHeader = (void*)(*handle))
		{
		#ifdef client_debugging
			if (IsOddMP(blockHeader))	/* at this point, blockheader is the handle */
				{
				/*
				 *	the client has most likely disposed of a handle twice. We return 
				 *	right away with an error. This makes apps like PixelPaint work.
				 * This mechanism will hopefully replace the bus error hander mechanism
				 * of the old MM (I hope). Note: now we rely on tag & range checking.
				 */
				DbgClientCheckForDisposedHandle(handle,"MP is odd, are you moving a disposed handle?");
				return LMSetMemErr(memWZErr);
				}
		#endif

		/* get block header from client's text pointer */
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(blockHeader);
		if (!IsHeap(curHeap = GetHeapFromHandleBlock(handle, blockHeader))) {
			ClientDebugMsg("Bad heap from block header", curHeap);
			return LMSetMemErr(memAZErr);
			}

		#ifndef debugNoTagChecking
			/* tag field check for fake handle */
			if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
				{
				if (curHeap != ReadOnlyZone)
					{
					ClientDebugMsg("Bad handle, are you moving a fake handle?", handle);
					return LMSetMemErr(memWZErr);
					}
				}
		#endif

#ifdef hasFirstLevelFakeHandleTests
		/* range check for fake handle */
		if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you moving a fake handle?", handle);
			return LMSetMemErr(memWZErr);
			}
#endif
			
#ifdef hasSecondAndThirdLevelFakeHandleTests
		{
		stdBlock*		testBlock;

		/* double check to see that backLimit points back to this heap */
		if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you moving a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
			
		if (testBlock->parent != curHeap)
			{
			ClientDebugMsg("Bad handle, are you moving a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
		}
#endif	
	
		DbgClientCheckHeap(curHeap);

		/* Blocks are never moved in the Read Only Zone */
		
		if (IsLockedHandle(blockHeader))
			{
			return LMSetMemErr(memLockedErr);
			}
		else
			{
			Boolean	blockIsPurgable;

			/* If the block is purgable, mark it as non-purgable so it wont be 
				purged during the move. Later, we will restore the block. */
			if (blockIsPurgable = IsUnlockedPurgableHandle(blockHeader))
				MarkBlockNonPurgable(blockHeader, curHeap);

			/* 10/13/93 11:55:08 AM (BET): it was previously thought that the MoveHnd was the one
					being moved high; MoveHnd is really the currently modified handle _while we are
					compacting_.  This means we should be setting RootHnd and RootPtr to this block
					and setting MoveHnd to each block we shuffle to comply with this request. */
			LMSetGZRootHnd(handle);
			LMSetGZRootPtr(*handle);
		
			MoveBlockLow(blockHeader, curHeap);
		
			LMSetGZRootHnd(handle);
			LMSetGZRootPtr(*handle);

			/* note: at this point blockHeader has moved, so we can't use it */
			/* do we need to restore purgability to the block */
			if (blockIsPurgable)
				{
				/* reclaim block header */
				blockHeader = (handleBlock*) GetBlockHeaderFromPtr(*handle);
				MarkBlockPurgable(blockHeader, curHeap);
				}

			FlushCacheIfNeeded(curHeap);
			DbgCheckHeap(curHeap);
			return LMSetMemErr(noErr);
			}
		}
	else
		{
		return LMSetMemErr(nilHandleErr);
		}
	}


#if defined(linked_thinkc_app)
OSErr c_MemError(void)
	{
	return LMGetMemErr();
	}
#endif


Size c_MaxBlock(ushort trapWord)
	{
	stdHeap*		curHeap;
	blockSize_t	sizeWeGot;
	
	DbgValidateTrapWord(trapWord);
	curHeap = OperateOnSysHeap(trapWord) ? LMGetSysZone() : LMGetTheZone();
	DbgClientCheckHeap(curHeap);

	#ifdef hasFirstLevelFakeHandleTests
		{
		stdBlock*	testBlock;
			/*
			 * This is for DiskLock v. 2.12, which tries to set the zone to a heap it finds pointed to by
			 * SysZone->oldBackLimit->parent.  This fails on the old memory manager too, but the bus error
			 * handlers grab it and return an error.  I can only assume that Shayer is doing this to see if
			 * is in some kind of boot time heap so as to do the right thing.
			 *
			 * Since the heap pointer is in real memory space but simply off by 4 bytes, we are going to have
			 * to follow a circular path back to this point to check that this is indeed a heap.
			 */
			/* range check for bad heap */
			if (curHeap > (stdHeap*)LMGetFakeHandleRange())
				{
				ClientDebugMsg("Bad current heap", curHeap);
				return LMSetMemErr(memAZErr);
				}
				
			/* now range check the backLimit */
			if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
				{
				ClientDebugMsg("Bad backLimit in poseur heap", curHeap);
				return LMSetMemErr(memAZErr);
				}
				
			if (testBlock->parent != curHeap)
				{
				ClientDebugMsg("Bad heap consistency via backLimit block check", curHeap);
				return LMSetMemErr(memAZErr);
				}
			/* End DiskLock hack		
			*********************************/
		}
	#endif
	
	LMSetMemErr(noErr);

	sizeWeGot = CalcMaxBlockSize(curHeap);

	/* calculate the maximum block size, subtract off for the header */
	return sizeWeGot ? sizeWeGot - kBlockOverhead: 0;
	}


Size c_PurgeSpace(ushort trapWord, Size* contig)
	{
	stdHeap* curHeap;
	blockSize_t	total;
	
	DbgValidateTrapWord(trapWord);
	curHeap = OperateOnSysHeap(trapWord) ? LMGetSysZone() : LMGetTheZone();
	DbgClientCheckHeap(curHeap);
	
	if (*contig =  CalcLargestPurgeRegion(curHeap))
		{
		/* subtract block overhead if we got something back */
		*contig -= kBlockOverhead;
		}
	
	/* calculate total now */
	if (total = curHeap->totalFree + curHeap->totalPurgableSpace)
		{
		/* subtract block overhead if we got something back */
		total -= kBlockOverhead;
		}
	
	LMSetMemErr(noErr);
	return total;
	}


long c_StackSpace(void)
	{
	ulong	theSize;
	
	/* note: since heapEnd really points to the zone trailer block and 
		kBlockHeaderSize <= zoneTrailerSize <= kBlockHeaderSize*2 then we
		have to consider that value in the fudge factor. The actual value
		may be more since we will pop a stack frame off before returning 
		to the caller. */; 
	
	theSize = GetSP() + 2*kBlockHeaderSize; /* get Stack pointer + fudge factor */
	theSize = AlignDown(theSize);
	LMSetMemErr(noErr);
	return theSize - (ulong)LMGetHiHeapMark();
	}


/* Although not documented, the old HSetRBit code calls the handle prologue routine
	which checks for memWZErr. So we do too. */
OSErr c_HSetRBit(Handle handle)
	{
	stdHeap*			curHeap;
	handleBlock*	blockHeader;	/* client's text pointer, or blockHeader */

	if (handle == nil)
		{
		return LMSetMemErr(nilHandleErr);		/* bail right away */
		}

	/* get client's text pointer, is it not nil? */
	if (blockHeader = (void*)(*handle))
		{
		#ifdef client_debugging
			if (IsOddMP(blockHeader))	/* at this point, blockheader is the handle */
				{
				/*
				 *	the client has most likely disposed of a handle twice. We return 
				 *	right away with an error. This makes apps like PixelPaint work.
				 * This mechanism will hopefully replace the bus error hander mechanism
				 * of the old MM (I hope). Note: now we rely on tag & range checking.
				 */
				DbgClientCheckForDisposedHandle(handle,"MP is odd, are you setting the resource bit on a disposed handle?");
				return LMSetMemErr(memWZErr);
				}
		#endif

		/* get block header from client's text pointer */
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(blockHeader);
		if (!IsHeap(curHeap = GetHeapFromHandleBlock(handle, blockHeader))) {
			ClientDebugMsg("Bad heap from block header", curHeap);
			return LMSetMemErr(memAZErr);
			}

		#ifndef debugNoTagChecking
			/* tag field check for fake handle */
			if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
				{
				if (curHeap != ReadOnlyZone)
					{
					ClientDebugMsg("Bad handle, are you setting the resource bit on a fake handle?", handle);
					return LMSetMemErr(memWZErr);
					}
				}
		#endif

#ifdef hasFirstLevelFakeHandleTests
		/* range check for fake handle */
		if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you setting the resource bit on a fake handle?", handle);
			return LMSetMemErr(memWZErr);
			}
#endif
			
#ifdef hasSecondAndThirdLevelFakeHandleTests
		{
		stdBlock*		testBlock;

		/* double check to see that backLimit points back to this heap */
		if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you setting the resource bit on a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
			
		if (testBlock->parent != curHeap)
			{
			ClientDebugMsg("Bad handle, are you setting the resource bit on a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
		}
#endif
	
		/* Note: this operation never occurs in the Read Only Zone */

		IfClientDebugMsg(IsPtrBlock(blockHeader),"not a valid handle", handle);
		DbgClientCheckHeap(curHeap);

		blockHeader->resourceBit = 1;			/* set resource bit */

		return LMSetMemErr(noErr);
		}
	else
		{
		return LMSetMemErr(nilHandleErr);
		}
	}
	

/* Although not documented, the old HSetRBit code calls the handle prologue routine
	which checks for memWZErr. So we do too. */
OSErr c_HClrRBit(Handle handle)
	{
	stdHeap*			curHeap;
	handleBlock*	blockHeader;	/* client's text pointer, or blockHeader */

	if (handle == nil)
		{
		return LMSetMemErr(nilHandleErr);		/* bail right away */
		}

	/* get client's text pointer, is it not nil? */
	if (blockHeader = (void*)(*handle))
		{
		#ifdef client_debugging
			if (IsOddMP(blockHeader))	/* at this point, blockheader is the handle */
				{
				/*
				 *	the client has most likely disposed of a handle twice. We return 
				 *	right away with an error. This makes apps like PixelPaint work.
				 * This mechanism will hopefully replace the bus error hander mechanism
				 * of the old MM (I hope). Note: now we rely on tag & range checking.
				 */
				DbgClientCheckForDisposedHandle(handle,"MP is odd, are you clearing the resource bit a disposed handle?");
				return LMSetMemErr(memWZErr);
				}
		#endif

		/* get block header from client's text pointer */
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(blockHeader);
		if (!IsHeap(curHeap = GetHeapFromHandleBlock(handle, blockHeader))) {
			ClientDebugMsg("Bad heap from block header", curHeap);
			return LMSetMemErr(memAZErr);
			}

		#ifndef debugNoTagChecking
			/* tag field check for fake handle */
			if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
				{
				if (curHeap != ReadOnlyZone)
					{
					ClientDebugMsg("Bad handle, are you clearing the resource bit on a fake handle?", handle);
					return LMSetMemErr(memWZErr);
					}
				}
		#endif

#ifdef hasFirstLevelFakeHandleTests
		/* range check for fake handle */
		if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you clearing the resource bit on a fake handle?", handle);
			return LMSetMemErr(memWZErr);
			}
#endif
			
#ifdef hasSecondAndThirdLevelFakeHandleTests
		{
		stdBlock*		testBlock;

		/* double check to see that backLimit points back to this heap */
		if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you clearing the resource bit on a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
			
		if (testBlock->parent != curHeap)
			{
			ClientDebugMsg("Bad handle, are you clearing the resource bit on a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
		}
#endif	
	
		DbgClientCheckHeap(curHeap);

		if (IsReadOnlyZone(curHeap))
			{
			return LMSetMemErr(noErr);
			}

		IfClientDebugMsg(IsPtrBlock(blockHeader),"not a valid handle", handle);

		blockHeader->resourceBit = 0;			/* clear resource bit */

		return LMSetMemErr(noErr);
		}
	else
		{
		return LMSetMemErr(nilHandleErr);
		}
	}
	

/*
 *	note:		No special case code needed for the 32 bit read only zone.
 *
 *	note2:	Since this routine can return an error, we might want to consider
 *				having this routine return a 2 byte value rather than 1 byte value.
 */
unsigned char c_HGetState(Handle handle)
	{
	stdHeap*			curHeap;
	handleBlock*	blockHeader;	/* client's text pointer, or blockHeader */

	if (handle == nil)
		{
		/*
		 *	warning: in this code path, the old MM returns nilHandleErr (2 bytes) back
		 *	to the client instead of the state (1 byte). However, it is sign extended.
		 */
		return LMSetMemErr(nilHandleErr);
		}

	/* get client's text pointer, is it not nil? */
	if (blockHeader = (void*)(*handle))
		{
		#ifdef client_debugging
			if (IsOddMP(blockHeader))	/* at this point, blockheader is the handle */
				{
				/*
				 *	the client has most likely disposed of a handle twice. We return 
				 *	right away with an error. This makes apps like PixelPaint work.
				 * This mechanism will hopefully replace the bus error hander mechanism
				 * of the old MM (I hope). Note: now we rely on tag & range checking.
				 */
				DbgClientCheckForDisposedHandle(handle,"MP is odd, are you getting state on a disposed handle?");
				return LMSetMemErr(memWZErr);
				}
		#endif

		/* get block header from client's text pointer */
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(blockHeader);
		if (!IsHeap(curHeap = GetHeapFromHandleBlock(handle, blockHeader))) {
			ClientDebugMsg("Bad heap from block header", curHeap);
			return LMSetMemErr(memAZErr);
			}

		#ifndef debugNoTagChecking
			/* tag field check for fake handle */
			if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
				{
				if (curHeap != ReadOnlyZone)
					{
					ClientDebugMsg("Bad handle, are you getting state on a fake handle?", handle);
					return LMSetMemErr(memWZErr);
					}
				}
		#endif

#ifdef hasFirstLevelFakeHandleTests
		/* range check for fake handle */
		if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you getting state on a fake handle?", handle);
			return LMSetMemErr(memWZErr);
			}
#endif
			
#ifdef hasSecondAndThirdLevelFakeHandleTests
		{
		stdBlock*		testBlock;

		/* double check to see that backLimit points back to this heap */
		if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you getting state on a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
			
		if (testBlock->parent != curHeap)
			{
			ClientDebugMsg("Bad handle, are you getting state on a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
		}
#endif	
	
		DbgClientCheckHeap(curHeap);

		LMSetMemErr(noErr);
		return ((stdBlock2*)blockHeader)->mpFlags & kMPFlagsMask;		/* mask off private bits */
		}
	else
		{
		/*
		 *	warning: in this code path, the old MM returns nilHandleErr (2 bytes) back
		 *	to the client instead of the state (1 byte). However, it is sign extended. 
		 */
		return LMSetMemErr(nilHandleErr);
		}
	}


/* This routine becomes a pain because clients can use this routine to in place of:
	HPurge, HNoPurge, HLock, HUnlock, HSetResource, HClrResource.  This routine is
	sufficiently complicated that a state table is needed.
HSetState Notes:

Lock bit				Purge bit		Purge bit		Total Purgable		LowestRemovableBlock
Start/End State	Start State		End State		Space Change		Action

Unlocked => Unlocked
						NonPurgable	->	NonPurgable		No change			No change
						NonPurgable	->	Purgable			+						No change
						Purgable		->	NonPurgable		-						No change
						Purgable		->	Purgable			No change			No change

Unlocked => Locked
						NonPurgable	->	NonPurgable		No change			WalkUp
						NonPurgable	->	Purgable			No change			WalkUp
						Purgable		->	NonPurgable		-						WalkUp
						Purgable		->	Purgable			-						WalkUp

Locked => Unlocked
						NonPurgable	->	NonPurgable		No change			Set to blockHeader
						NonPurgable	->	Purgable			+						Set to blockHeader
						Purgable		->	NonPurgable		No change			Set to blockHeader
						Purgable		->	Purgable			+						Set to blockHeader

Locked => Locked
						NonPurgable	->	NonPurgable		No change			No change
						NonPurgable	->	Purgable			No change			No change
						Purgable		->	NonPurgable		No change			No change
						Purgable		->	Purgable			No change			No change
*/
OSErr c_HSetState(Handle handle, unsigned char newFlags)
	{
	stdHeap*			curHeap;
	handleBlock*	blockHeader;	/* client's text pointer, or blockHeader */
	unsigned char	oldFlags;

	if (handle == nil)
		{
		return LMSetMemErr(nilHandleErr);		/* bail right away */
		}

	/* get client's text pointer, is it not nil? */
	if (blockHeader = (void*)(*handle))
		{
		#ifdef client_debugging
			if (IsOddMP(blockHeader))	/* at this point, blockheader is the handle */
				{
				/*
				 *	the client has most likely disposed of a handle twice. We return 
				 *	right away with an error. This makes apps like PixelPaint work.
				 * This mechanism will hopefully replace the bus error hander mechanism
				 * of the old MM (I hope). Note: now we rely on tag & range checking.
				 */
				DbgClientCheckForDisposedHandle(handle,"MP is odd, are you setting state on a disposed handle?");
				return LMSetMemErr(memWZErr);
				}
		#endif

		/* get block header from client's text pointer */
		blockHeader = (handleBlock*) GetBlockHeaderFromPtr(blockHeader);
		if (!IsHeap(curHeap = GetHeapFromHandleBlock(handle, blockHeader))) {
			ClientDebugMsg("Bad heap from block header", curHeap);
			return LMSetMemErr(memAZErr);
			}

		#ifndef debugNoTagChecking
			/* tag field check for fake handle */
			if ((((stdBlock2*)blockHeader)->tags & kPtrMask) != (uchar)relocatableType)
				{
				if (curHeap != ReadOnlyZone)
					{
					ClientDebugMsg("Bad handle, are you setting state on a fake handle?", handle);
					return LMSetMemErr(memWZErr);
					}
				}
		#endif

#ifdef hasFirstLevelFakeHandleTests
		/* range check for fake handle */
		if (curHeap > (stdHeap*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you setting state on a fake handle?", handle);
			return LMSetMemErr(memWZErr);
			}
#endif
			
#ifdef hasSecondAndThirdLevelFakeHandleTests
		{
		stdBlock*		testBlock;

		/* double check to see that backLimit points back to this heap */
		if ((testBlock = curHeap->backLimit) > (stdBlock*)LMGetFakeHandleRange())
			{
			ClientDebugMsg("Bad handle, are you setting state on a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
			
		if (testBlock->parent != curHeap)
			{
			ClientDebugMsg("Bad handle, are you setting state on a fake handle?", handle);
			return LMSetMemErr(memAZErr);
			}
		}
#endif

		if (IsReadOnlyZone(curHeap))
			{
			return LMSetMemErr(noErr);
			}

		DbgClientCheckHeap(curHeap);

		oldFlags = ((stdBlock2*)blockHeader)->mpFlags;

		IfClientDebugMsg(IsPtrBlock(blockHeader),"not a valid handle", handle);

		if (newFlags & lockedBlockType)
			{
			if (oldFlags & lockedBlockType)
				{
				/* locked => locked, nothing changes here */
				}
			else
				{
				/* unlocked => locked */

				/* set LRB if needed */				
				if (curHeap->lowestRemovableBlock == blockHeader)
					curHeap->lowestRemovableBlock = WalkUpFindNewLowRemoveable((stdBlock*)blockHeader, curHeap);

				/* was the orginal block purgable? */
				if (oldFlags & purgableType)
					{
					curHeap->totalPurgableSpace -= blockHeader->size;
					}
				}
			}
		else
			{
			if (oldFlags & lockedBlockType)
				{
				/* locked => unlocked */

				/* reset LRB if needed */				
				if (((void*)blockHeader < curHeap->lowestRemovableBlock) && ((void*)blockHeader > (void*)(curHeap->heapStart)))
					curHeap->lowestRemovableBlock = blockHeader;

				/* increment total purgable space if the new block is purgable */
				if (newFlags & purgableType)
					curHeap->totalPurgableSpace += blockHeader->size;
				}
			else
				{
				/* unlocked => unlocked */

				if (oldFlags & purgableType)
					{
					if (!(newFlags & purgableType))
						{
						/* purgable -> nonPurgable */
						curHeap->totalPurgableSpace -= blockHeader->size;
						}
					}
				else
					{
					if (newFlags & purgableType)
						{
						/* nonPurgable -> purgable */
						curHeap->totalPurgableSpace += blockHeader->size;
						}
					}
				}
			}

		/* warning: next line also clears other MP flags (subHeapBlockType, privBlockType, etc) */
		((stdBlock2*)blockHeader)->mpFlags = newFlags & kMPFlagsMask;
		DbgCheckHeap(curHeap);
		return LMSetMemErr(noErr);
		}
	else
		{
		return LMSetMemErr(nilHandleErr);
		}
	}
						

/*
 *	Returns the next block in the heap, skips over private blocks including master
 *	pointer blocks and the dead block. If the end of the heap is reached, then it
 *	returns nil. Warning, don't make other calls that move memory while iterating
 *	the heap.
 */
Ptr c_GetNextBlockInHeap(Ptr theBlock, THz theHeap)
	{
	stdHeap*		curHeap = (stdHeap*)theHeap;
	stdBlock*	workBlock;
	
	if (theBlock)
		workBlock = (stdBlock*) GetBlockHeaderFromPtr(theBlock);
	else
		workBlock = curHeap->heapStart;
	
	do
		{
		workBlock = GetNextBlock(workBlock);
		
		if (workBlock == curHeap->backLimit)
			return nil;
		}
	while (IsPrivateBlock(workBlock));
	
	LMSetMemErr(noErr);
	return (Ptr) workBlock + kBlockHeaderSize;
	}

/* This get called by the Process Manager can presumable any new Figment aware
	clients that might want to dispose of thier zone. */
OSErr c_DisposeZone(THz theZone)
	{
	stdBlock*	blockHeader;
	stdHeap*		parentHeap;
	
	/* first we need to see if the heap is contained by a heap in the client header */
	blockHeader = (stdBlock*) GetBlockHeaderFromPtr(theZone);
	
	/* does this potential block have a parent heap? */
	if (parentHeap = FindHeap(blockHeader))
		{
		if (IsValidBlockInHeap(blockHeader, parentHeap))
			blockHeader->subHeapBit = 0;	/* mark the block as no longer containing a heap */
		}

	//RemoveHeap((stdHeap*) theZone);
	RemoveHeap(((stdHeap*)theZone)->heapStart, (Ptr)((stdHeap*)theZone)->backLimit);

	return LMSetMemErr(noErr);
	}


/* this is a way for ProcessMgr inform the heap manager of special compatibility hacks */
OSErr c_SetZoneCompatibilityFlags(THz theZone, ushort theFlags)
	{
	((stdHeap2*)theZone)->compatibilityFlags = theFlags;
	return noErr;
	}


/* this is a way for ProcessMgr inform the heap manager of special compatibility hacks */
ushort c_GetZoneCompatibilityFlags(THz theZone)
	{
	return ((stdHeap2*)theZone)->compatibilityFlags;
	}


#if 0
	/*
	 *	Below is code to implement chained GZ procs and code to implement chained
	 *	dispose procs. These features are not implemented and are commented out.
	 *	There is also support code in MemMgrInternal.c that is commented out as well.
	 */
	
	/* Used to register call back procs */
	static OSErr LLInsert(ProcPtr theProc, callBackNodePtr* listHead);
	static OSErr LLInsert(ProcPtr theProc, callBackNodePtr* listHead)
		{
		callBackNodePtr	trail;
		callBackNodePtr	curr;
		callBackNodePtr	newItem;
	
		/* create new list node */
		c_NewPtr((Ptr*)&newItem, 0xA11E, sizeof(callBackNodeItem));		/* call newptr through internal API */
		if (!newItem)
			return LMGetMemErr();
	
		/* Mark the block as "private" */
		((stdBlock*)GetBlockHeaderFromPtr(newItem))->privBlockBit = 1;
		
		/* Since its private, the MM does not consider it a ptrBlock */
		DbgCode(LMGetTheZone()->ptrBlocks--);
	
		curr = *listHead;
		trail = nil;
	
		/* walk down the list to add entry at the end */	
		while (curr)
			{
			trail = curr;
			curr = curr->next;
			}
		
		/* fill in items */		
		newItem->next = nil;
		newItem->proc = theProc;
		
		if (trail)
			{
			/* add it to the list */
			trail->next = newItem;
			}
		else
			{
			/* add to the head of the list */
			*listHead = newItem;
			}
		return noErr;
		}
	
	
	/* Used to unregister call back procs */
	/* returns true if item was found */	
	static Boolean LLDelete(ProcPtr theProc, callBackNodePtr* listHead);
	static Boolean LLDelete(ProcPtr theProc, callBackNodePtr* listHead)
		{
		callBackNodePtr	curr;
		callBackNodePtr	trail = nil;
	
		/* scan the list looking for the right item */	
		curr = *listHead;
		while (curr->proc != theProc)
			{
			trail = curr;
			curr = curr->next;
			
			/* did we reach the end of the list? */
			if (curr == nil)
				return false;	/* we didn't find anything */
			}
		
		/* we have found the proc to remove, do it */
		if (trail)
			{
			trail->next = curr->next;
			}
		else
			{
			/* removing first item */
			*listHead = curr->next;
			}
			
		DisposePtr((Ptr)curr);
		return true;
		}
	
	
	OSErr c_RegisterChainedGrowZoneProc(GrowZoneProcPtr theProc, Boolean beforeUsersProc)
		{
		stdHeap*	curHeap = LMGetTheZone();
		
		return LLInsert((ProcPtr) theProc, 
						(beforeUsersProc) ? &curHeap->earlyChainedGZProc : &curHeap->lateChainedGZProc
						);
		}
		
	
	OSErr c_UnregisterChainedGrowZoneProc(GrowZoneProcPtr theProc)
		{
		stdHeap*	curHeap = LMGetTheZone();
	
		/* can we delete it from the early chain?, then do so */
		if (!LLDelete((ProcPtr) theProc, &curHeap->earlyChainedGZProc))
			{
			/* delete it from the late chain */		
			LLDelete((ProcPtr) theProc, &curHeap->lateChainedGZProc);
			}
			
		return noErr;
		}
#endif  /* commented out code */

	
#if USESROUTINEDESCRIPTORS
OSErr	c_RegisterDisposeProc(DisposeUPP theProc, THz theZone)
#else
OSErr	c_RegisterDisposeProc(DisposeProcPtr theProc, THz theZone)
#endif
	{
	stdHeap*	curHeap = (stdHeap*)theZone;
	
	// we use this code after the Process Manager starts calling this 
	// trap instead of jamming the heap field directly
	//return LLInsert((ProcPtr) theProc, &curHeap->disposeProc);
	
	// this code will be removed after ProcessMgr revs
	curHeap->disposeProc = (DisposeProcPtr)theProc;
	return noErr;
	}



#ifdef StarTrek

/*
 *	This is "high level glue" to so the Figment API can be called from high level code
 *	but still use the same API as the existing MM.
 */
	
	pascal void InitZone(GrowZoneProcPtr	pgrowZone, short cmoreMasters, void* limitPtr, void* startPtr)
		{
		c_InitZone(pgrowZone, cmoreMasters, limitPtr, startPtr);
		}

	pascal void SetApplLimit(Ptr zoneLimit)
		{
		c_SetApplLimit(zoneLimit);
		}
		
	pascal void MaxApplZone(void)
		{
		c_MaxApplZone();
		}
		
	pascal void MoreMasters(void)
		{
		c_MoreMasters();
		}
		
	pascal THz GetZone(void)
		{
		return c_GetZone();
		}
		
	pascal void SetZone(THz hz)
		{
		c_SetZone(hz);
		}
		
	pascal Handle NewHandle(Size requestedSize)
		{
		Handle theHandle;
		
		c_NewHandle(&theHandle, kWorkOnCurHeap, requestedSize);
		return theHandle;
		}
		
	pascal Handle NewHandleSys(Size requestedSize)
		{
		Handle theHandle;
		
		c_NewHandle(&theHandle, kSysTrapWordBit, requestedSize);
		return theHandle;
		}
		
	pascal Handle NewHandleClear(Size requestedSize)
		{
		Handle theHandle;
		
		c_NewHandle(&theHandle, kClearTrapWordBit, requestedSize);
		return theHandle;
		}
		
	pascal Handle NewHandleSysClear(Size requestedSize)
		{
		Handle theHandle;
		
		c_NewHandle(&theHandle, kClearTrapWordBit+kClearTrapWordBit, requestedSize);
		return theHandle;
		}
		
	pascal Handle NewEmptyHandle(void)
		{
		Handle theHandle;
		
		c_NewEmptyHandle(&theHandle, kWorkOnCurHeap);
		return theHandle;
		}
		
	pascal Handle NewEmptyHandleSys(void)
		{
		Handle theHandle;
		
		c_NewEmptyHandle(&theHandle, kSysTrapWordBit);
		return theHandle;
		}
		
	pascal void DisposeHandle(Handle theHandle)
		{
		c_DisposeHandle(theHandle);
		}
		
	pascal Size GetHandleSize(Handle theHandle)
		{
		return c_GetHandleSize(theHandle);
		}
	
	pascal void SetHandleSize(Handle theHandle, Size requestedSize)
		{
		c_SetHandleSize(theHandle, requestedSize);
		}
		
	pascal THz HandleZone(Handle theHandle)
		{
		THz 	theZone;
		
		c_HandleZone(&theZone, theHandle);
		return theZone;
		}
		
	pascal Handle RecoverHandle(Ptr masterPointer)
		{
		return c_RecoverHandle(kWorkOnCurHeap, masterPointer);
		}
		
	pascal Handle RecoverHandleSys(Ptr masterPointer)
		{
		return c_RecoverHandle(kSysTrapWordBit, masterPointer);
		}
		
	pascal void ReallocHandle(Handle handle, Size requestedSize)
		{
		c_ReallocHandle(handle, requestedSize);
		}

	pascal Ptr NewPtr(Size requestedSize)
		{
		Ptr thePtr;
		
		c_NewPtr(&thePtr, kWorkOnCurHeap, requestedSize);
		return thePtr;
		}
		
	pascal Ptr NewPtrSys(Size requestedSize)
		{
		Ptr thePtr;
		
		c_NewPtr(&thePtr, kSysTrapWordBit, requestedSize);
		return thePtr;
		}
		
	pascal Ptr NewPtrClear(Size requestedSize)
		{
		Ptr thePtr;
		
		c_NewPtr(&thePtr, kClearTrapWordBit, requestedSize);
		return thePtr;
		}
		
	pascal Ptr NewPtrSysClear(Size requestedSize)
		{
		Ptr thePtr;
			
		c_NewPtr(&thePtr, kClearTrapWordBit+kClearTrapWordBit, requestedSize);
		return thePtr;
		}
		
	pascal void DisposePtr(Ptr thePtr)
		{
		c_DisposePtr(thePtr);
		}

	pascal Size GetPtrSize(Ptr thePtr)
		{
		return c_GetPtrSize(thePtr);
		}
	
	pascal void SetPtrSize(Ptr thePtr, Size requestedSize)
		{
		c_SetPtrSize(thePtr, requestedSize);
		}

	pascal THz PtrZone(Ptr thePtr)
		{
		THz	theZone;
		
		c_PtrZone(&theZone, thePtr);
		return theZone;
		}

	pascal long FreeMem(void)
		{
		return c_FreeMem(kWorkOnCurHeap);
		}

	pascal long FreeMemSys(void)
		{
		return c_FreeMem(kSysTrapWordBit);
		}

	pascal Size MaxMem(Size *growSize)
		{
		return c_MaxMem(kWorkOnCurHeap, growSize);
		}

	pascal Size MaxMemSys(Size *growSize)
		{
		return c_MaxMem(kSysTrapWordBit, growSize);
		}

	pascal Size CompactMem(Size sizeNeeded)
		{
		return c_MaxMem(kWorkOnCurHeap, &sizeNeeded);
		}

	pascal Size CompactMemSys(Size sizeNeeded)
		{
		return c_CompactMem(kSysTrapWordBit, sizeNeeded);
		}

	#define	ResrvMem(s)		ReserveMem(s)
	pascal void ReserveMem(Size sizeNeeded)
		{
		c_ReserveMem(kWorkOnCurHeap, sizeNeeded);
		}

	pascal void ReserveMemSys(Size sizeNeeded)
		{
		c_ReserveMem(kSysTrapWordBit, sizeNeeded);
		}

	pascal void PurgeMem(Size sizeNeeded)
		{
		c_PurgeMem(kWorkOnCurHeap, sizeNeeded);
		}

	pascal void PurgeMemSys(Size sizeNeeded)
		{
		c_PurgeMem(kSysTrapWordBit, sizeNeeded);
		}
	
	pascal void EmptyHandle(Handle handle)
		{
		c_EmptyHandle(handle);
		}

	pascal void HLock(Handle handle)
		{
		c_HLock(handle);
		}

	pascal void HUnlock(Handle handle)
		{
		c_HUnlock(handle);
		}

	pascal void HPurge(Handle handle)
		{
		c_HPurge(handle);
		}

	pascal void HNoPurge(Handle handle)
		{
		c_HNoPurge(handle);
		}

	pascal void SetGrowZone(GrowZoneProcPtr theGrowZoneProc)
		{
		c_SetGrowZone(theGrowZoneProc);
		}

	pascal void MoveHHi(Handle theHandle)
		{
		c_MoveHHi(theHandle);
		}

	pascal void MoveHLow(Handle theHandle)
		{
		c_MoveHLow(theHandle);
		}

	pascal Size MaxBlock(void)
		{
		return c_MaxBlock(kWorkOnCurHeap);
		}
	
	pascal Size MaxBlockSys(void)
		{
		return c_MaxBlock(kSysTrapWordBit);
		}

	pascal void PurgeSpace(Size *total,Size *contig) 
		{
		*total = c_PurgeSpace(kWorkOnCurHeap, contig);
		}
	
	pascal void PurgeSpaceSys(Size *total,Size *contig) 
		{
		*total = c_PurgeSpace(kSysTrapWordBit, contig);
		}
	
	pascal long StackSpace(void)
		{
		return c_StackSpace();
		}
		
	pascal void HSetRBit(Handle handle)
		{
		c_HSetRBit(handle);
		}

	pascal void HClrRBit(Handle handle)
		{
		c_HClrRBit(handle);
		}

	pascal char HGetState(Handle handle)
		{
		return c_HGetState(handle);
		}

	pascal void HSetState(Handle handle, char flags)
		{
		c_HSetState(handle, flags);
		}

	pascal Handle NewHandleHi(Size requestedSize)
		{
		Handle theHandle;
		
		c_NewHandleHi(&theHandle, kWorkOnCurHeap, requestedSize);
		return theHandle;
		}
		
#endif /* StarTrek */


