/*
	File:		MemMgr.h

	Contains:	Memory Manager Internal Interfaces

	Written by:	Jeff Crawford

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
		
	  <SM19>	11/10/93	fau		Update from SuperMunggio <SMG2>.
	  <SMG2>	 9/29/93	chp		Removed typedefs for unsigned types. Put them in Types.h instead
									since lots of people use them.
	   <149>	10/14/93	BT		<BT, ewa> Radar 1117552; Change interfaces around. Radar
									1114117; fix MoveHHi.
	   <148>	  9/2/93	BT		<BT, ewa> #1110427, add tag checking for heaps. This is a
									precautionary measure, as bus error handlers are proven most
									effective with a quick tag check.
	   <147>	 8/19/93	BT		<BT, cam> Add "#ifdef hasFirstLevelFakeHandleTests" around
									remaining range checks.  This defined in here unless
									"cancelFigmentRangeChecking" is set true.
	   <146>	  8/5/93	BT		<BT, JC> We came, we saw, we initialed...
	   <145>	  8/4/93	JC		Made some minor modifications to support the linked in ThinkC
									test application.
	   <144>	  8/2/93	JC		#1095953 replaced LMGet/SetRealMemTop with LMGet/
									SetFakeHandleRange to permit heaps above RealMemTop.
	   <143>	 7/29/93	JC		#1101544, Changed interface to RemoveHeap to fix OCE bug.
	   <142>	 7/28/93	BT		<BT, JRG> Radar 1096298, 1102433. Finish QT
									HandleTrashNotification code. The Component Manager wasn't
									getting notified that memory was going away and would call dead
									space.
	   <141>	 7/27/93	JC		#1100227, Fixed Claris XTND and others who read the first
									longword out of a disposed block. We now move the prevFree link
									of a free block to be 12 bytes lower.
	   <140>	 7/26/93	JC		#1100694, Removed ChainedGZ support.
	   <139>	 7/26/93	JC		Changed enum tags for ptr blocks and handle blocks to be a more
									esoteric number so we can catch fake handles and fake pointers.
	   <138>	 7/20/93	JC		Spiffed up the client debug routines for Developer's CD version
									of Figment.
	   <137>	 7/12/93	BMC		StarTrek - no longer define lowmem macros for startrek - we have
									our own functions.
	   <136>	  7/7/93	JC		#1096767,1096744,1096911: Fixed internal routine for PurgeSpace
									to calculate a more accurate value of contiguous purgable space.
	   <135>	  7/2/93	BT		(With EPT) Radar #1095398. Fix internal Memory Manager calls to
									go thru the trap table interface. Moving DisposeProcPtr stuff to
									MasterInterfaces for Power.
	   <134>	  7/1/93	BT		Add code to define hasCacheTypeCPU if it is not already defined.
	   <133>	  7/1/93	BT		Changed "#ifdef hasCacheTypeCPU" to "#if …".  This way the make
									features in FeatureSet can do the right thing depending on 68K
									or RISC.
	   <132>	 6/30/93	BT		Change has_cache_type_cpu to hasCacheTypeCPU to more closely
									match SuperMario Feature Set conventions.
	   <131>	 6/30/93	JC		#1089109: Removed fHeapIsDirty bit.
	   <130>	 6/30/93	JC		Removed Get/SetPhysMemTop since it's not used. Added
									kREALMEMTOP, so we can test from ThinkC and StartTrek.  Added
									secondAndThirdLevelFakeHandleTests as an official #define.
	   <129>	 6/25/93	BT		PhysMemTop was the wrong value to be using, need to use
									RealMemTop. Add it back in.
	   <128>	 6/25/93	BT		Update a small oversight. LMSetPhysMemTop was setting on
									LMGetRealMemTop. Since we don't use this, it didn't affect
									things.
	   <127>	 6/25/93	BT		(with JC) Added range checking to handle calls so that the
									relative master pointer is checked to be within the bounds of
									available RAM.  More elaborate code is in here, but commented
									out because we don't want to use it.
	   <126>	 6/22/93	JC		Fixed GZ proc to save and restore Register A5 to make Resolve &
									Wings work.
	   <125>	 6/16/93	JC		Added universal low memory getters and setters.
	   <124>	 6/16/93	BMC		StarTrek - Spunging off of linked_thinkc_app low mem global
									(statics) till low mem access is "macrotized".
	   <123>	 6/10/93	JC		Added support for heap is dirty bit. Also added technical note
									on how it is maintained. Added 2 new debugging fields to track
									this bit.
	   <122>	  6/8/93	JC		Changed BlockMove to BlockMoveData.
	   <121>	  6/8/93	JC		Fixed MarkBlockAsPrivate paramter.
	   <120>	  6/8/93	JC		Changed kMaxSize to make MaxApplZone work with large freeBlock
									headers. Added useful comments.
	   <119>	  6/4/93	JC		Changed HeapID's to a debug feature only.
	   <118>	  6/2/93	JC		Cleaned up some comments.
	   <117>	  6/1/93	BMC		StarTrek support - MoveBytes & ClearBytes definitions
	   <116>	 5/25/93	BT		Change rdDisposeProcProcInfo to use kFourByteCode instead of the
									number 4.  This was stupid on my part.
	   <115>	 5/24/93	JC		Changed XXX to DbgXXX for all debug routines.
	   <114>	 5/24/93	JC		Fix MP block problem in the ProcessMgr heap.
	   <113>	 5/22/93	JC		Changed #define of MoveBytes to be _BlockMove for SuperMario and
									native PowerPC builds.
	   <112>	 5/20/93	JC		Cleaned up call back procs. Removed c_MoreMastersHi.  Added
									c_RegisterDisposeProc API for ProcessMgr.
	   <111>	 5/19/93	JC		Began changes as requested by the code review. Removed options
									parameter from AllocateMoreMasters.
	   <110>	 5/18/93	JC		Fixed the “zero k available” bug. Yippee! This fix requires a
									new ProcessMgr to work completely. Also fixed Jim Gochees
									problem one more time in MakeSpaceLow.
	   <109>	 5/14/93	JC		Finish adding support for GZRootHnd, GZRootPtr, and GZMoveHnd.
	   <108>	  5/7/93	JC		Added support for GZRootHnd. Fixed obscure bug where
									JumpRelocateRange we would fail when we could still slide blocks
									up. Also fixed a bug in MakeSpaceLow to check against backLimit.
									Fixed similar bug in MakeSpaceHigh to check against
									lowestRemoveableBlock. Otimized AlignUp to be 4 assembly
									instructions.
	   <107>	  5/2/93	JC		Removed heapName field. Rearranged the heap header to support
									the compatibility flags word for some Claris apps.
	   <106>	 4/23/93	JC		Fixed kMinFreeSplitSize one more time.
	   <105>	 4/23/93	JC		No changes changes made today.
	   <104>	 4/21/93	BT		<ewa> Update bitfields for Power compatibility, maybe more?
	   <103>	 4/18/93	JC		Changed #defines to more acurate descriptions. Changed
									small_block_headers to small_freeBlock_headers and linkedIn to
									linked_thinkc_app.   •• Brian & Sam take note.••
	  <101+>	 4/16/93	JC		Cleanup for Code Review
		 <1>	 6/10/92	JC		Old Today

*/


/************************ Important global compiler definitions *******************
*
*	#define	linked_thinkc_app
*			Defined =>	Routines are linked together in a Think C project. Otherwise
*						the standard Macintosh operating environment is assumed.
*
*	#define patchedIn
*			Defined =>	Project is patched in by calling set trap address on all the 
*						Memory Manager routines. Useful for testing glue code.
*
*	#define	client_debugging
*			Defined =>	Check for heap validity on entry to the Memory Manager 
*
*	#define	internal_debugging
*			Defined =>	Internal debugging checks turned on. Heap validity checked
*						on exit from the memory manager.
*
*	#define	quadLongWordAligned
*			Defined =>	All blocks are quadlongword (16 bytes) aligned, instead of 
*						longword (4 byte) aligned. 
*
*	#define	small_freeBlock_headers
*			Defined =>	Free block headers are 16 bytes instead of 20 bytes. This is
*						done by combining the prevFree ptr field with the 
*						tags/flags/sizeAdjust longword. Turn off for full 32 bit 
*						addressing.
*
*	#define	hasCacheTypeCPU
*			(""==1) =>	This machine has a seperate instruction cache that needs to
*						be flushed if (potential) code has moved. The 040 and 603 &
*						620 fall in to this category.
*
*	#define	hasSecondAndThirdLevelFakeHandleTests
*			Defined =>	Go through extra handle validity checking on entry to handle
*						based calls.
*
*	#define implemented_discontiguous_heaps
*			Defined =>	Discontiguous application heaps are supported. See ERS for
*						details. Note, this feature not implemented yet.
*
*	#define powerc
*			Defined =>	Compiled for PowerPC platforms
*
*	#define StarTrek
*			Defined =>	Compiled for StarTrek platforms
*
************************************************************************************/


/************************** Some general code comments ********************************
*
*	1)	Below, low, bottom, pref, back, etc. refer to entities that are low in memory. That 
*		is they are closer to location $0. Above, high, top, next, etc. refer to entities 
*		that are high in memory, that is they are closer to location $FFFFFFFF.
*	2)	All block sizes are unsigned numbers. Special care has been taken to keep them 
*		that way.
*	3)	The old MM use to jam vectors start at $1E00 and $1F00 to support dual 24 bit
*		and 32 bit style heaps. Some system code in System 7.1 still patches MM traps by 
*		jamming values in some of these vectors. Since this new Heap Manager does not use
*		these vectors, these patches by the system soft are harmless, but should be removed.
*	3a)	This code needed some low memory. It uses $1E00 through $1E10. These memory
*		locations do not conflict with System 7.1 patches.
*	4)	cumXXXX is an accumulator that stands for "cumulative". Hence cumFreeSpace is 
*		cumulative free space. OK Andy?
*	5)	A fixed block is either a locked relocatable or non-relocatable block. It can
*		also be called a sandbar or and island.
*	6)	A range is an arbitrary area inside a heap.
*	7)	A region is an area between 2 fixed blocks.
*	8)	A busy block is a relocatable block whose ptr bit has been set becuase it needs to
*		be temporarily anchored down by the Memory Manager.
*	9)	Sliding blocks will not move them across fixed blocks. JumpRelocating blocks can
*		and will relocate blocks over fixed boundaries.
*	10)	Size terms like requestedSize are sizes used by a client. They could be considered a 
*		logical size.
*	11)	Sizes like reqBlockSize are size used by the memory manager internally. They could
*		be considered a physical size. They are not be confused in any way with virtual 
*		memory. The size field in a blockheader is a physical size.
*	12)	Routines that begin with Dbg are debugging routine. They will be compiled out
*		when the final non-debug version ships.
*	13)	Be very careful with the setting of the favoredFree block. Special care has been
*		taken to set it as little as possible. It should always point to a freeBlock.
*	14)	Special care has been taken to keep uniform coding conventions throughout the code.
*		Please follow them to keep the code consistent, even if they differ from your own
*		superior conventions.
*
************************************************************************************/

#include <MemoryMgrPriv.h>

/*************************** Important global constants ****************************/

#define kAppZoneSize		(0x1800)	/* same as process manager */
#define	kDfltMasters		(32)		/* for system heap, app heap is KDfltMasters * 2 */


/*
 *	Largest size of a block you can allocate. Must be careful with this value, since
 *	other numbers can be added to it causing a large positive number to become a 
 *	small positive number. As an example, trace through _MaxApplZone. This is left as an
 *	exercise to the reader.
 */
	#ifdef small_freeBlock_headers
		#define	kMaxSize			0x2FFFFFF0UL	/* the largest block possible */
	#else
		#define	kMaxSize			0x7FFFFFF0UL	/* the largest block possible */
	#endif


#if defined(linked_thinkc_app) || defined(StarTrek)
	/* mimimum amount to extend the appl zone */
	#define kExtraAmountToExtendApplLimit	(0x40)		/* The MM uses 0x400 */
	
	/* used by PMHeap/SysHeap interaction */
	#define EXTRA_SLOP_FOR_NEXT_TIME		(0x40)		/* The MM uses  (10*1024) */

	/* min free space required by the SystemHeap */
	#define GetExpandMemMinSysHeapFreeSpace()	(0x100)
#else
	#define kExtraAmountToExtendApplLimit	(0x400)
	#define EXTRA_SLOP_FOR_NEXT_TIME		(10*1024)
#endif /* linked_thinkc_app */

	/****************************************************************/
	/* if we don't want no stinkin range checks...					*/
	/****************************************************************/
#ifndef cancelFigmentRangeChecking
	#define hasFirstLevelFakeHandleTests TRUE
#else
	#if (!cancelFigmentRangeChecking)
		#define hasFirstLevelFakeHandleTests TRUE
	#endif
#endif

/************************* Important global constants *******************/

#ifndef privateMemMgrIncludes
	#define privateMemMgrIncludes
		
	#ifndef anyNumber
		#define anyNumber 1
	#endif
	
	#ifndef nil
		#define nil (void*) 0L
	#endif
	
	#ifndef hasCacheTypeCPU
		#define hasCacheTypeCPU 0
	#endif

	#define sizeField(structure, field)	sizeof(((structure*) 0)->field)
	#define offsetField(type, field)		((long) &((type*) 0)->field)

	typedef struct stdHeap stdHeap;
	typedef struct stdHeap2 stdHeap2;

	#if defined(linked_thinkc_app)
		/* not used BufPtr; */
		/* not used StkLowPt; */
		extern stdHeap*	THEZONE;
		extern Ptr		APPLLIMIT;
		extern stdHeap*	SYSZONE;
		extern stdHeap*	APPLZONE;
		extern Ptr		HEAPEND;
		extern Ptr		HIHEAPMARK;
		extern Handle	gGZROOTHND;
		extern Ptr		gGZROOTPTR;
		extern Handle	gGZMOVEHND;
		extern OSErr	gMEMERROR;
		extern void*	gFAKEHANDLERANGE;
		
		#define	kREALMEMTOP		((Ptr)(0x7FFFFFFF))				/* this is just a dummy constant */

		#define LMGetTheZone()		(THEZONE)					/* current zone start */
		#define LMSetTheZone(x)		(LMGetTheZone() = (x))
		
		#define LMGetApplLimit()	(APPLLIMIT)					/* limit of applzone */
		#define LMSetApplLimit(x)	(LMGetApplLimit() = (x))
		
		#define LMGetSysZone()		(SYSZONE)					/* syszone start */
		#define LMSetSysZone(x)		(LMGetSysZone() = (x))
		
		#define LMGetApplZone()		(APPLZONE)					/* applzone start */
		#define LMSetApplZone(x)	(LMGetApplZone() = (x))
		
		#define LMGetHeapEnd()		(HEAPEND)					/* current zone limit */
		#define LMSetHeapEnd(x)		(LMGetHeapEnd() = (x))
		
		#define LMGetHiHeapMark()	(HIHEAPMARK)				/* used as lower stack limit */
		#define LMSetHiHeapMark(x)	(LMGetHiHeapMark() = (x))
		
		#define LMGetGZRootHnd()	(gGZROOTHND)				/* GZRootHnd, for GZSaveHnd() */
		#define LMSetGZRootHnd(x)	(LMGetGZRootHnd() = (x))
		
		#define LMGetGZRootPtr()	(gGZROOTPTR)				/* GZRootPtr */
		#define LMSetGZRootPtr(x)	(LMGetGZRootPtr() = (x))
		
		#define LMGetGZMoveHnd()	(gGZMOVEHND)				/* GZMoveHnd */
		#define LMSetGZMoveHnd(x)	(LMGetGZMoveHnd() = (x))
		
		#define LMGetMemErr()		(gMEMERROR)					/* MemError */
		#define LMSetMemErr(x)		(LMGetMemErr() = (x))
		
		#ifdef hasFirstLevelFakeHandleTests
			#define LMGetFakeHandleRange()	(gFAKEHANDLERANGE)
			#define LMSetFakeHandleRange(x)	(LMGetFakeHandleRange() = (x))
		#endif
	#else

		/*
		 *	These are the new universal LoMemory getters and setters. Eventually they will
		 *	be replaced by a global header file somewhere else.
		 */
		#define LMGetTheZone()		(*(stdHeap**)(0x118))		/* current zone start */
		#define LMSetTheZone(x)		(LMGetTheZone() = (x))
		
		#define LMGetApplLimit()	(*(Ptr*)(0x130))			/* limit of applzone */
		#define LMSetApplLimit(x)	(LMGetApplLimit() = (x))
		
		#define LMGetSysZone()		(*(stdHeap**)(0x2A6))		/* syszone start */
		#define LMSetSysZone(x)		(LMGetSysZone() = (x))
		
		#define LMGetApplZone()		(*(stdHeap**)(0x2AA))		/* applzone start */
		#define LMSetApplZone(x)	(LMGetApplZone() = (x))
		
		#define LMGetHeapEnd()		(*(Ptr*)(0x114))			/* current zone limit */
		#define LMSetHeapEnd(x)		(LMGetHeapEnd() = (x))
		
		#define LMGetHiHeapMark()	(*(Ptr*)(0xBAE))			/* used as lower stack limit */
		#define LMSetHiHeapMark(x)	(LMGetHiHeapMark() = (x))
		
		#define LMGetGZRootHnd()	(*(Handle*)(0x328))			/* GZRootHnd, for GZSaveHnd() */
		#define LMSetGZRootHnd(x)	(LMGetGZRootHnd() = (x))
		
		#define LMGetGZRootPtr()	(*(Ptr*)(0x32C))			/* GZRootPtr */
		#define LMSetGZRootPtr(x)	(LMGetGZRootPtr() = (x))
		
		#define LMGetGZMoveHnd()	(*(Handle*)(0x330))			/* GZMoveHnd */
		#define LMSetGZMoveHnd(x)	(LMGetGZMoveHnd() = (x))
		
		#define LMGetMemErr()		(*(OSErr*)(0x220))			/* MemError */
		#define LMSetMemErr(x)		(LMGetMemErr() = (x))
		
		#ifdef hasFirstLevelFakeHandleTests
			#define LMGetFakeHandleRange()	(*(Ptr*)(0x1E10))
			#define LMSetFakeHandleRange(x)	(LMGetFakeHandleRange() = (x))
		#endif
	#endif /* linked_thinkc_app */


	#define	IsAppHeap(h)		((h) == LMGetApplZone())
	#define	IsSystemHeap(h)		((h) == LMGetSysZone())


	#define MIN(a,b)  (((a)<(b)) ? (a) : (b))
	#define MAX(a,b)  (((a)>(b)) ? (a) : (b))

	#define	kWorkOnCurHeap			0
	#define kSysTrapWordBit			(1 << 10)		/* Sys bit is bit 10 */
	#define kClearTrapWordBit		(1 << 9)		/* Clear bit is bit 9 */
	#define	OperateOnSysHeap(tw)	((tw) & kSysTrapWordBit)
	#define	ClearTheBlock(tw)		((tw) & kClearTrapWordBit)

	/* for calling function pointers */
#ifdef debugging
	#define CALL_FNC_PTR(fncType,fncPtr,fncArgs)	(*((fncType) fncPtr))fncArgs
	typedef pascal void (*RelocateProcPtr)(Ptr start, Ptr destination, stdHeap* curHeap);
#endif

#ifndef powerc
	typedef pascal void (*PurgeProcPtr)(Handle handle);
	typedef pascal void (*DisposeProcPtr)(Handle handle, THz zone);
	typedef pascal void (*TrashNotificationProcPtr)(Ptr startAddr, Ptr endAddr);
	#define CALL_FNC_PTR_1(fncType,fncPtr,procInfo,fncArg1)			(*((fncType) fncPtr))(fncArg1)
	#define CALL_FNC_PTR_2(fncType,fncPtr,procInfo,fncArg1,fncArg2)	(*((fncType) fncPtr))(fncArg1,fncArg2)
#else
	#define CALL_FNC_PTR_1(fncType,fncPtr,procInfo,fncArg1)			CallUniversalProc((UniversalProcPtr)fncPtr,(ProcInfoType)procInfo,fncArg1)
	#define CALL_FNC_PTR_2(fncType,fncPtr,procInfo,fncArg1,fncArg2)	CallUniversalProc((UniversalProcPtr)fncPtr,(ProcInfoType)procInfo,fncArg1,fncArg2)
#endif


/* these pseudo-routines are used to save and restore A5 when calling the GZProc */
#ifdef powerc
	/*
	 *	For PowerPC, we need to set the emulated regs since we might
	 *	have an emulated client.
	 */
	#define	GetRegA5()		GetEmulatorRegister(kRegisterA5)
	#define SetRegA5(x)		SetEmulatorRegister(kRegisterA5, x)
#elif StarTrek
	/* for StarTrek, we don't need to do it */
	#define	GetRegA5()		(0)
	#define SetRegA5(x)
#else
	/* for the 68k world, we save an restore reg A5 */
	pascal	ulong	GetRegA5(void) = 0x2E8D;		/*	Move.l	A5,(Sp)		*/
	pascal	void	SetRegA5(ulong val) = 0x2A5F;	/*	Move.l	(Sp)+,A5	*/
#endif
 

	/*
	 *	The code below represents a very simple linked list used by registered callback 
	 *	routines. It is purposely kept simple since chain will not be very long (ie.- < 4 items)
	 */
	typedef struct callBackNodeItem 
		{
		struct callBackNodeItem*	next;		/* next link */
		ProcPtr						proc;		/* data */
		} callBackNodeItem, *callBackNodePtr;
		
	#define		LLGetFirstItem(list)	((callBackNodePtr) list)
	#define		LLGetNextItem(item)		(item->next)

	
	/* all block sizes are this type */
	typedef unsigned long blockSize_t;


	/* tags for private blocks */
	enum  /* all internal blocks are, ptrType */
	{
		freeBlockType		= 0x00,
		ptrType 			= 0x6B,			/* used to be 0x40 */
		relocatableType 	= 0xAB			/* used to be 0x80 */
	};
	
	
	#define kTagMask	(0xC0)		/* for masking block type (free, handle, ptr) */
	#define kPtrMask	(0xBF)		/* for ignoring ptr bit */
	
		/* mpFlags types */
		typedef enum
		{
			privBlockType		= 0x01,
			subHeapBlockType	= 0x02,
			deadBlockType		= 0x04,
			trailerBlockType	= 0x08,
			masterBlockType		= 0x10,
			resourceType 		= 0x20,			/* set for a resource */
			purgableType 		= 0x40,			/* set if purgable */
			lockedBlockType		= 0x80			/* set if locked */
		} blockFlags;

#if 0
		#define MMBlockHeader \
			void*			back;				/* pointer to previous block */\
			unsigned char	tags;				/* allocated,ptr, etc */\
			unsigned char	mpFlags;  			/* locked, purgeable, resource, etc*/\
			unsigned char	heapID;				\
			unsigned char	sizeDelta;			\
			blockSize_t		size;				/* could be as little as 20 */
#endif

	#define MMBlockHeader \
		void*			back;				/* pointer to previous block */\
		unsigned 		handleBit 		: 1;	\
		unsigned 		ptrBit			: 1;	\
		unsigned 		Unused1			: 6;	\
		unsigned 		lockBit			: 1;	\
		unsigned 		purgeBit		: 1;	\
		unsigned 		resourceBit		: 1;	\
		unsigned 		masterBit		: 1;	\
		unsigned 		trailerBit		: 1;	\
		unsigned 		deadBlockBit	: 1;	\
		unsigned 		subHeapBit		: 1;	\
		unsigned 		privBlockBit	: 1;	\
		unsigned 		heapID			: 8;	\
		unsigned 		sizeDelta		: 8;	\
		unsigned long	size;				/* block size including header */
	
	#define kBackPtrSize	4					/* sizeof the back ptr for each block */
	#define BACK(b) ((b)->back)					/* easy way to reference back ptr */


	typedef struct
	{
		MMBlockHeader
		void*			parent;				/* consider making this a heap* */
		long			data[anyNumber];
	} ptrBlock, stdBlock;

	/*
	 *	we redefine the block header this way incase we want to access some fields.
	 *	This definition allows for easy access to tags, flags and sizeDelta as a bytes.
	 */
	typedef struct
	{
		void*			back;				/* pointer to previous block */
		unsigned char	tags;				/* allocated,ptr, etc */
		unsigned char	mpFlags;  			/* locked, purgeable, resource, etc*/
		unsigned char	heapID;
		unsigned char	sizeDelta;
		blockSize_t		size;				/* could be as little as 20 */
		void*			parent;				/* consider making this a heap* */
	} stdBlock2;

	/*
	 *	yet another way to define the block header. This one allows for easy
	 *	access to the tags, flags, and sized adjust as a long word.
	 */
	typedef struct
	{
		void*			back;				/* pointer to previous block */
		unsigned long	tagsFlagsSizeDelta;	/* pointer to previous block */
		blockSize_t		size;				/* could be as little as 20 */
		void*			parent;				/* consider making this a heap* */
	} stdBlock3;

	typedef struct
	{
		MMBlockHeader
		long			relHandle;			/* warning this may be negative for block below the heap header */
		long			data[anyNumber];
	} handleBlock;

#ifdef small_freeBlock_headers
	typedef struct freeBlock
	{
		void*				back;
		struct freeBlock*	prevFree;
		blockSize_t			size;
		struct freeBlock*	nextFree;
		long				data[anyNumber];
	} freeBlock;
#else
	typedef struct freeBlock
	{
		MMBlockHeader
		struct freeBlock*	nextFree;
		void*				unused[3];			/* ••• for people who read from the beginning of disposed blocks */
		struct freeBlock*	prevFree;
		long				data[anyNumber];
	} freeBlock;
#endif



	/* alignment stuff */
#ifdef quadLongWordAligned	
	#define kAlignmentFactor	16		// quad-longwords are 16 bytes
#else
	#define kAlignmentFactor	4		// longwords are 4 bytes
#endif
	#define AlignDown(x)			(((ulong)x) & ~(kAlignmentFactor - 1))
	#define AlignUp(x)				(((ulong)x + (kAlignmentFactor - 1)) & ~(kAlignmentFactor - 1))
	#define AnotherOldAlignUp(x)	(-(-kAlignmentFactor & ~((ulong)x - 1)))
	#define OldAlignUp(x)			(((ulong)x) + (~(((ulong)x) - 1) & kAlignmentFactor - 1))		/* this is the old slow way */

	/* defines for determining block sizes */
	#define kBlockHeaderSize		(sizeof(stdBlock) - sizeField(stdBlock, data))					
	#define kFreeBlockHeaderSize	(sizeof(freeBlock) - sizeField(freeBlock, data))
	#define	kBlockOverhead			(kBlockHeaderSize + kMagicSize)								/* overhead for NON free blocks */
	#define kFreeBlockOverhead		(sizeof(freeBlock) - sizeField(freeBlock, data))			/* overhead for free blocks */

	#define kMinFreeBlockSize		AlignUp(sizeof(freeBlock) - sizeField(freeBlock, data))		/* smallest physical size of a free block */
	#define	kMinBlockSize			MAX( kMinFreeBlockSize, AlignUp(kBlockOverhead) )			/* smallest physical size of a zero sized block */
	#define	kOldHeaderSize			(12)

	#define	kPsuedoBlockSize		(kOldHeaderSize)		/* 12 */
	#define	kMinDelta				(kBackPtrSize + kMagicSize)
	#define kTrailerBlockSize		32						/* 32 because we have the trailer spoof block for Macsbug */
	#define kTrailerSpoofOffset		16
	#define kOldTrailerSize			16
	
	/* size of the original (pre Figment) MM heap */
	#define		kOriginalHeapHeaderSize			(52)		

	/* offset of first block in PM heap from the start of the fake zone start */
	#define kPMFakeHeapStartOffset		(kOriginalHeapHeaderSize - kBackPtrSize)

	/*
	 *	This is a guess at the number of MPs needed for the ProcessMgr zone.
	 *	The old PM memory management routines used (8*1024), but we use this
	 *	new number since BungeeFinder tends to use temp mem much more heavily.
	 */
	#define kZoneBytesPerMP 							(8*1024)
	
	/* fake values for the fake ProcessMgrHeap header */
	#define kFakePMPurgePtr			((stdBlock*)0x6a656666L)
	#define kFakePMNextUp			((stdHeap*)0x6d696b65L)
	#define kFakePMNextIn			((stdHeap*)0x616e6479L)
	#define kFakePMHeapStart		((void*)0x62726920L)
	#define kFakePMLowestRemovable	((void*)0x65726963)

/*
 *	kMinFreeSplitSize......
 *	Minimum size required to create a new free block. Note that free blocks
 *	that are only the size of the header are quite useless and they make the heap structure
 *	less efficient. So in some case, we add an extra amount. These cases are marked with a "*". 	 
 *
 *	Here is our "Truth" table.
 *
 *	quad LongWord	small freeBlock		debugging	BlockHeader		FreeBlockHeader		kMagic		MinFree
 *	Aligned			headers							Size			Size				Size		SplitSize
 *	_____________________________________________________________________________________________________________
 *	no				no					no			16				20					0			20
 *	no				no					yes			16				20					4			20+4=24*
 *	no				yes					no			16				16					0			16+4=20*		
 *	no				yes					yes			16				16					4			20+4=24*
 *	yes				no					no			16				20					0			32
 *	yes				no					yes			16				20					4			32
 *	yes				yes					no			16				16					0			16+16=32*
 *	yes				yes					yes			16				16					4			32
 */

/* jeff & mike's last try. See comments above for description. */
#ifdef quadLongWordAligned
	#define	kMinFreeSplitSize	(32)
#else
	#ifdef	debugging
		#define	kMinFreeSplitSize	(24)
	#else
		#define	kMinFreeSplitSize	(20)
	#endif
#endif

	 
#if 0
	/* jeffs try, it does not work */
	#ifdef small_freeBlock_headers
		#ifdef quadLongWordAligned	
			#define kMinFreeSplitSize		(2*kMinBlockSize)
		#else
			#define kMinFreeSplitSize		(kMinBlockSize)
		#endif	
	#else
		#ifdef quadLongWordAligned	
			#define kMinFreeSplitSize		(kMinBlockSize)
		#else
			#define kMinFreeSplitSize		(kMinBlockSize)
		#endif	
	#endif
		
	/* mikes try, does not work either */
	#define kMinFreeSplitSize		AlignUp(kFreeBlockHeaderSize+kMagicSize+1)	// please be right!
#endif


	/* Routines for accesing flags in the block header */
	/* determines if a block is a handle, pointer or free*/
 	#ifdef small_freeBlock_headers	
		#define IsAllocatedBlock(b)			((((stdBlock*)(b))->ptrBit) || (((stdBlock*)(b))->handleBit))
		#define IsFreeBlock(b)				(!(((stdBlock*)(b))->handleBit) && !(((stdBlock*)(b))->ptrBit)) 
 	#else	
		#define IsAllocatedBlock(b)			(((stdBlock2*)((stdBlock*)(b)))->tags != 0)
		#define IsFreeBlock(b)				(((stdBlock2*)((stdBlock*)(b)))->tags == 0)
	#endif
	
	#define IsHandleBlock(b)			(((stdBlock*)(b))->handleBit)		/* note: will also work if handle is temporarily busy */
	#define IsPtrBlock(b)				(((stdBlock*)(b))->ptrBit)
	#define	kMPFlagsMask				(0xE0)		/* mask off LPR bits */
	#define	kPurgeFlagsMask				(0xC0)		/* mask off LP bits */

	/* For relocatable blocks, assumes its a valid handle */
	#define IsLockedHandle(b)			(((handleBlock*)(b))->lockBit)
	#define IsUnlockedHandle(b)			(!IsLockedHandle(b))
	#define IsResourceHandle(b)			(((handleBlock*)(b))->resourceBit)
	#define IsPurgableHandle(b)			(((handleBlock*)(b))->purgeBit)
	#define IsNonPurgableHandle(b)		(!IsPurgableHandle(b))
	#define IsUnlockedPurgableHandle(b)	(IsPurgableHandle(b) && IsUnlockedHandle(b))

	/* for relocatable blocks, does not assume the block is a handle */
	#define IsLockedBlock(b)			((IsHandleBlock(b)) && (IsLockedHandle(b)))
	#define IsUnlockedBlock(b)			((IsHandleBlock(b)) && (!IsLockedHandle(b)))
	#define IsResourceBlock(b)			((IsHandleBlock(b)) && (IsResourceHandle(b)))
	#define IsPurgableBlock(b)			((IsHandleBlock(b)) && (IsPurgableHandle(b)))
	#define IsNonPurgableBlock(b)		((IsHandleBlock(b)) && (!IsPurgableHandle(b)))
	#define IsUnlockedPurgableBlock(b)	(IsHandleBlock(b) && IsUnlockedPurgableHandle(b))

	/* true if block can't move, (ptr or locked handle) */
	#ifdef small_freeBlock_headers
	#define IsFixedBlock(b)  			(IsPtrBlock(b) || (IsHandleBlock(b) && IsLockedHandle(b)))
	#else
	#define IsFixedBlock(b)  			(IsPtrBlock(b) || IsLockedHandle(b))	/* Note: dont have to test for a handle  */
	#endif

	/* for accessing private MM blocks */
	#define IsPrivateBlock(b)  			((IsPtrBlock(b)) && (((stdBlock*)b)->privBlockBit))
	#define IsDeadBlock(b)				(((stdBlock*)b)->deadBlockBit)
	#define IsTrailerBlock(b)			(((stdBlock*)b)->trailerBit)
	#define IsMasterBlock(b)			(((stdBlock*)b)->masterBit)


	#define IsPrevBlockFree(b)			(IsFreeBlock((stdBlock*)(BACK(((stdBlock*) (b))))))	
	#define	IsNextBlockFree(b)			(IsFreeBlock((stdBlock*)((char*)(b) + (b)->size)))
	#define GetNextBlock(b)				((void*)((char*)(b) + (b)->size))

	/* Given a pointer a clients block (text), returns the block Header */
	#define	GetBlockHeaderFromPtr(mp)	((char*)(mp) - kBlockHeaderSize)

	#define GetHeapFromHandleBlock(hand, b)	((stdHeap*) ((char*)hand - (b)->relHandle))
	#define	JamTagsFlagsAndSizeDelta(b,v)	((stdBlock3*)(b))->tagsFlagsSizeDelta = (v)

		
	#if defined(linked_thinkc_app) || defined(StarTrek)
		#define IsBlockInROM(b)				(false)
	#else
		/* hopefully this will work, jeff */
		#define IsBlockInROM(b)				(((Ptr)b)  >  * (Ptr*) ROMBase)
	#endif

	#define IsAddressInHeap(addr, h)	((void*)(addr) <= (h)->heapStart || (stdBlock*)(addr) > (h)->backLimit)
	

	/* Debugging stuff */
	#ifdef debugging
		#define kMagicSize					4
		#define kMagicNumber				'jeff'

		#define MagicOffset(h,size)			(*(blockSize_t *)((blockSize_t)(h) + size + 1 & ~1L))
		#define DbgSetMagic(h,size)			MagicOffset(h,size) = kMagicNumber
		#define DbgSetBlockHeapID(b, z)		(b)->heapID = (z)->heapID
		#ifdef client_debugging
			#define DbgClientCheckForDisposedHandle(hand,str)	if ((ulong)(*hand) & 0x0000001) {DbgMessage(str, (long)hand);}
		#else
			#define DbgClientCheckForDisposedHandle(hand,str)
		#endif
	#else
		#define kMagicSize					0
		#define DbgSetMagic(h,size)
		#define DbgClientCheckForDisposedHandle(hand,str)	
		#define DbgSetBlockHeapID
	#endif /* debugging */


	/*
	 *	heap flags, note the "•" indicates that Figment checks this bit often.
	 *	Note:	MPW will generate TST.B instructions instead of BTST for bits 15 and 7.
	 *			Thus, those bits are the most often used flags.
	 */
	#define HeapFlagsAndMPCountHeader																								\
		unsigned 		MPCount						: 16;	/* # of new master pointers allocated at a go */						\
																																	\
		unsigned 		fCacheNeedsToBeFlushed		: 1;	/* • Instruction cache, cache type machines (68040) */					\
		unsigned 		fHeapIsAppHeap				: 1;	/* bit 14, these will probably go away, jeff */							\
		unsigned 		fHeapIsProcessMgrHeap		: 1;	/* bit 13 */															\
		unsigned 		fHeapIsSystemHeap			: 1;	/* bit 12 */															\
																																	\
		unsigned 		fSkipPurgeBeforeGZ			: 1;	/* bit 11, avoid purging blocks before calling grow zone proc (SysHeap, Portables) */	\
		unsigned 		fFastPointerAllocation		: 1;	/* bit 10, NewPtr uses same path as NewHandle (not implemented) */		\
		unsigned 		fCanBeDiscontiguous			: 1;	/* bit 9, heap can be discontiguous */									\
		unsigned 		fReadOnlyZone				: 1;	/* bit 8, Heap can't be disposed or emptied */							\
																																	\
		unsigned 		fHeapIsDirty				: 1;	/* bit 7, not used, used to be fRelAtEnd,  */			\
		unsigned 		fNotUsed3					: 1;	/* bit 6, used to be fNSelPurge */										\
		unsigned 		fUseFirstFree				: 1;	/* bit 5, •use first free in place of favored free, used to be fNoRvrAlloc,  */		\
		unsigned 		fNotUsed2					: 1;	/* bit 4, used to be fNSelCompct */										\
																																	\
		unsigned 		fUnused4					: 1;	/* bit 3, not used */													\
		unsigned 		fNotUsed1					: 1;	/* bit 2, not used */													\
		unsigned 		fHeapFullyExtended			: 1;	/* bit 1, ie.- client has called MaxApplZone (app heaps only) */		\
		unsigned 		fNotUsed5					: 1;	/* bit 0, not used */



	#define CompatibilityFlagsTypeAndID																				\
		unsigned		fDontMakeMPOdd				: 1;	/* for some Claris Apps */									\
		unsigned		otherCompatibilityFlags		: 15;	/* special hacks for skanky apps */						\
		unsigned		heapType					: 8;	/* for 32 bit mode, Figment mode, debug mode, etc */	\
		unsigned		heapID						: 8;	/* HeapID */

	/*
	 *	Slimy hack to jam a block into the zone header so that the zone header still 
	 *	has the same size and structure as a block in the old 32 bit MM.
	 */
	typedef struct spoofBlockStruct
		{
		unsigned long	tagsFlagsSizeDelta;	/* pointer to previous block */
		blockSize_t		size;				/* could be as little as 20 */
		void*			parent;				/* consider making this a heap* */
		} spoofBlockStruct;


	/*
	 *	This is the heap header data structure. It replaces the Zone struct for the old
	 *	32 bit MM.
	 */
	struct stdHeap
		{
		spoofBlockStruct* oldBackLimit;		/* old back limit for compatibility */
		stdBlock*		purgePtr;			/* pointer to first block to purge */
		Ptr*			firstFreeMP;		/* the first mp available for use */
		blockSize_t		totalFree;			/* sum of sizes of all free blocks */
		GrowZoneProcPtr	gzProc;  			/* clients growzone proc */
		HeapFlagsAndMPCountHeader			/* to be accessed as bit fields */
		void*			heapStart;			/* the first block where heap blocks can be allocated */
		CompatibilityFlagsTypeAndID			/* access as bit fields */
		struct stdHeap*	nextUp;				/* the next heap in memory that we know about
												Warning: MemMgrBoot.a depends on hard coded offset */
		struct stdHeap*	nextIn;				/* the next heap in this heap that we know about */
		PurgeProcPtr	purgeProc;			/* call back when purging */
		void*			lowestRemovableBlock; /* lowest free or relocatable in main fragment */
		void*			crud;				/* use to be favoredFree which used to be the ROVER
												warning: must be set to nil since it is used as a back ptr */
		spoofBlockStruct spoofBlock;		/* first block for clients who walk the heap, ** Offset must be at 52!! ** */
		stdBlock*		backLimit;			/* pointer to the heap trailer block */
		DisposeProcPtr	disposeProc;		/* call back when block is diposed,
												Warning: ProcessMgr depends on hard coded offset */
		freeBlock*		favoredFree;		/* the block from which new allocations come, the is also the start of the dummy free block */
	#ifdef small_freeBlock_headers
		freeBlock*		lastFree;			/* new master ptrs on the end eat into this */
		blockSize_t		dummyFreeSize;		/* dummyFreeSize must be zero */
		freeBlock*		firstFree;			/* the lowest free block */
		blockSize_t		totalPurgableSpace;
	#else
		blockSize_t		totalPurgableSpace;	/* also dummyFree tags, flags, sizeDelta */
		blockSize_t		dummyFreeSize;		/* dummyFreeSize must be zero */
		freeBlock*		firstFree;			/* the lowest free block */
		void*			unused[3];			/* ••• for people who read from the beginning of disposed blocks */
		freeBlock*		lastFree;			/* new master ptrs on the end eat into this */
	#endif /* small_freeBlock_headers */
		Ptr*			lastFreeMP;			/* not used */
		callBackNodePtr	earlyChainedGZProc;	/* not used, chained grow zone procs before user */
		callBackNodePtr	lateChainedGZProc;	/* not used, chained grow zone procs after user */
		void*			fragmentPtr;		/* not used, pointer to first fragment, for discontiguous heaps */
	#ifdef debugging
		long			validationFlags;	/* indicates what to validate during memory manager routines */
		long			freeBlocks;
		long			ptrBlocks;
		long			handleBlocks;
		long			favoredFreeHits;	/* number of times favoredFree is correct */
		long			checkCount;			/* the number of times this heap has been checked */
		long			bytesMoved;			/* total bytes moved */
		long			bytesJumped;		/* bytes jump relocated */
		long			bytesSlidUp;		/* by slide up block moves */
		long			bytesSlidDown;		/* by slide down block moves */
		long			totalDelta;
		long			totalBytesAllocated;
		long			totalBytesDisposed;
		long			totalBlocksAllocated;
		long			totalBlocksDisposed;
		long			totalBlocksMoved;
		RelocateProcPtr	relocateProc;		/* call back when block is relocated */
		long			holes;				/* for discontiguous heaps */
		long			subHeaps;
		long			compactionCount;	/* number heap compactions */
		long			heapCleanCount;		/* number of compaction where heap is clean */
	#endif /* debugging */
		};

	/*
	 *	this alternate heap structure is declared to make the heap flags, MPCount
	 *	compatibility flags, heapType, & heapID each accessable as individual 
	 *	quantities. Note: any changes here must also be done in stdHeap as well.
	 */
	struct stdHeap2
		{
		stdBlock*		backLimit;			/* pointer to the heap trailer block */
		stdBlock*		purgePtr;			/* pointer to first block to purge */
		Ptr*			firstFreeMP;		/* the first mp available for use */
		blockSize_t		totalFree;			/* sum of sizes of all free blocks */
		GrowZoneProcPtr	gzProc;  			/* clients growzone proc */
		ushort			MPCount;			/* # of new master pointers allocated at a go */
		ushort			heapFlags;			/* 16 bits of heap flags */
		void*			heapStart;			/* the first block where heap blocks can be allocated */
		ushort			compatibilityFlags;	/* special hacks for skanky apps */
		char			heapType;			/* for 32 bit, Figment, debug, etc */
		unsigned char	heapID;				/* HeapID */
		};


	/*
	 *	this macro returns the pointer to the dummy free block which is cleverly
	 *	hidden in the heap header.
	 */
	#define DummyFree(h)	((freeBlock*)(&((h)->favoredFree)))

	/* values for the heapType field of stdHeap */
	/* jeff, these will go away and become bit fields */
	typedef enum
	{
		kHeapIs32BitClean 		= 0x0001,	/* bit 0,  heap is 32 bit clean, always set */
		kHeapIsFigmentHeap		= 0x0002,	/* bit 1,  Always set */
		kHeapContainsDebugInfo	= 0x0004	/* bit 2, heap header contains debugging information */
	} heapTypes;
	
	#ifdef debugging
		#define heapDouJour					(kHeapIs32BitClean | kHeapIsFigmentHeap | kHeapContainsDebugInfo)
	#else
		#define heapDouJour					(kHeapIs32BitClean | kHeapIsFigmentHeap)
	#endif
	
	#ifndef debugNoTagChecking
		#define IsHeap(h)						((h)->heapType == heapDouJour)
	#else
		#define IsHeap(h)						1
	#endif
	
	
	/* defines for accessing heap flags */
	#define IsProcessMgrHeap(h)				((h)->fHeapIsProcessMgrHeap)
	#define IsHeapFullyExtended(h)			((h)->fHeapFullyExtended)
	#define	IsReadOnlyZone(h)				((h)->fReadOnlyZone)
	
	/* We make the assumption that the ROZ if the first subheap in the system heap */
	#define	ReadOnlyZone					(LMGetSysZone()->nextIn)
	
	#if hasCacheTypeCPU
		#define MarkCacheNeedsToBeFlushed(h)	((h)->fCacheNeedsToBeFlushed = 1);
		#ifdef linked_thinkc_app
			#define FlushCacheIfNeeded(h)		if ((h)->fCacheNeedsToBeFlushed)					\
													{												\
														(h)->fCacheNeedsToBeFlushed = 0;			\
													}
		#else
			#if ForROM
				#define FlushCacheIfNeeded(h)	if ((h)->fCacheNeedsToBeFlushed)					\
													{												\
														FlushInstructionCache();					\
														(h)->fCacheNeedsToBeFlushed = 0;			\
													}
			#else
				/* This is done to get it to link with Truth */
				pascal void FlushTheInstructionCache(void)
				 = {0x2078, 0x06F4,		/* MoveA	jCacheFlush,A0	*/
				 	0x4E90};			/* JSR		(A0)			*/
				#define FlushCacheIfNeeded(h)	if ((h)->fCacheNeedsToBeFlushed)					\
													{												\
														FlushTheInstructionCache();					\
														(h)->fCacheNeedsToBeFlushed = 0;			\
													}
			#endif
		#endif /* linked_thinkc_app */
	#else
		#define MarkCacheNeedsToBeFlushed(h)
		#define FlushCacheIfNeeded(h)
	#endif /* hasCacheTypeCPU */


	#define DbgCheckForProcessMgrHeap(h)	IfClientDebugMsg(IsProcessMgrHeap(curHeap),"This call not allowed on the ProcessMgrHeap, it may not work", h)

	#define CheckMagic(h,size)		IfDbgMsg(MagicOffset(h,size) != kMagicNumber, "memory corrupted by overwriting block end", (long) h)

	
	/*
	 *	Values to pass to NewBlock in the options field. The lower word of this field
	 *	passes the area of the heap to allocate.
	 */
	typedef enum
	{
		kAllocateFast = 0,		/* use first fit algorithm to find a free block (fast) */
		kAllocateLow = 1,		/* make space for allocation as low as possible */
		kAllocateHigh = 2,		/* make space as high as possible for allocation */
		
		kDontPurge			= 0x00010000,	/* dont purge the heap, need to set kDontCallGZ with this bit */
		kDontCreateFragment	= 0x00020000, 	/* dont grow the heap discontiguously */
		kDontCallGZ			= 0x00040000, 	/* dont call user's grow zone */
		kDontCompact		= 0x00080000, 	/* dont even compact */
	
		kDoFirstRegionOnly			= 0x00000000, 	/* search first region only */
		kDoContinueUntilRegionFound	= 0x01000000 	/* continue search until found */
	
	} NewBlockOptions;


	/* used for masking the directions field (high, low, or fast) for options
		passed to NewBlock() and its children. */
	#define	kDirectionMask			0x0000000FL

	/* used for getting the number to of regions to search for */
	#define	kNumberOfRegionsMask	0xFF000000L
	
	
	/* 10/13/93 8:12:18 PM (BET): moved from old local MemoryMgrPriv.h */
	#ifdef linked_thinkc_app
		#define InitProcessMgrHeap(z)					c_InitProcessMgrHeap(z)
		#define ShrinkSysHeap(s)						c_ShrinkSysHeap(s)
		#define LowerProcessMgrZoneBottom(s,z)			c_LowerProcessMgrZoneBottom(s,z)
		#define ShrinkProcessMgrZone(s,z)				c_ShrinkProcessMgrZone(s,z)
		#define ExtendSystemZone(s)						c_ExtendSystemZone(s)
		#define ReclaimSpaceIfSysHeapLow(h,pm)			c_ReclaimSpaceIfSysHeapLow(h,pm)
		#define StraddleBlockSize(low,high,b,saw,pm)	c_StraddleBlockSize(low,high,b,saw,pm)
		#define ProcessMgrMaxBlock(pm)					c_ProcessMgrMaxBlock(pm)
		#define GetProcessMgrLoFreeBytes(h, saw)		c_GetProcessMgrLoFreeBytes(h,saw)
		#define GetSystemHiFreeBytes(v)					c_GetSystemHiFreeBytes(v)
		
		#define RegisterDisposeProc(p,z)				c_RegisterDisposeProc(p,z)
		#define NewHandleHi(h,t,s)						c_NewHandleHi(h,t,s)
		#define GetNextBlockInHeap(b, z)				c_GetNextBlockInHeap(b,z)
		#define DisposeZone(z)							c_DisposeZone(z)
	#elif StarTrek
		#define InitProcessMgrHeap(z)					c_InitProcessMgrHeap(z)
		#define ShrinkSysHeap(s)						c_ShrinkSysHeap(s)
		#define LowerProcessMgrZoneBottom(s,z)			c_LowerProcessMgrZoneBottom(s,z)
		#define ShrinkProcessMgrZone(s,z)				c_ShrinkProcessMgrZone(s,z)
		#define ExtendSystemZone(s)						c_ExtendSystemZone(s)
		#define ReclaimSpaceIfSysHeapLow(h,pm)			c_ReclaimSpaceIfSysHeapLow(h,pm)
		#define StraddleBlockSize(low,high,b,saw,pm)	c_StraddleBlockSize(low,high,b,saw,pm)
		#define ProcessMgrMaxBlock(pm)					c_ProcessMgrMaxBlock(pm)
		#define GetProcessMgrLoFreeBytes(h, saw)		c_GetProcessMgrLoFreeBytes(h, saw)
		#define GetSystemHiFreeBytes()					c_GetSystemHiFreeBytes()
		
		#define RegisterDisposeProc(p,z)				c_RegisterDisposeProc(p,z)
		#define GetNextBlockInHeap(b,z)					c_GetNextBlockInHeap(b,z)
		#define DisposeZone(z)							c_DisposeZone(z)
	#endif /* linked_thinkc_app */

	/****************************************************************/
	/* MemMgrInternal routines called by other modules				*/
	/****************************************************************/
	
	/** From MemMgrInternal.c **/
	stdHeap* GetZoneFromNilMP(void* mpAddress);
	void MarkBlockPurgable(handleBlock* blockHeader, stdHeap* curHeap);
	void MarkBlockNonPurgable(handleBlock* blockHeader, stdHeap* curHeap);
	void DoEmpty(handleBlock* blockHeader, stdHeap* curHeap);

	Boolean FixedBlockInRange(freeBlock* rangeBottom, freeBlock* rangeTop);
	stdBlock* WalkUpFindNewLowRemoveable(stdBlock* block, stdHeap *curHeap);
	stdBlock* NewBlock(blockSize_t reqBlockSize, long options, stdHeap* curHeap);
	stdBlock* NewBlockFast(blockSize_t reqBlockSize, stdHeap* curHeap);
	freeBlock* KillBlock(stdBlock* block, stdHeap* curHeap);
	void MarkBlockAsPrivate(stdBlock *location, char aBlockType, stdHeap* curHeap);

	stdBlock* SetBlockSize(stdBlock* blockHeader, blockSize_t reqBlockSize, stdHeap* curHeap);
	OSErr AllocateMoreMasters(stdHeap *curHeap);

	void ExtendHeapLimit(ptrBlock* newTrailBlock, stdHeap* curHeap);
	Boolean ExtendApplLimit(blockSize_t sizeNeeded, stdHeap* curHeap);
	void ShrinkHeapLimit(blockSize_t sizeToReduce, stdHeap* curHeap);
	freeBlock* MakeSpaceLow(blockSize_t reqBlockSize, long options, stdHeap* curHeap);
	freeBlock* MakeSpaceHigh(blockSize_t reqBlockSize, long options, stdHeap* curHeap);
	freeBlock* CompactHeap(blockSize_t reqBlockSize, stdHeap* targetHeap);
	blockSize_t CalcMaxBlockSize(stdHeap* curHeap);
	
	void MoveBlockHigh(handleBlock* workBlock, stdHeap* curHeap);
	void MoveBlockLow(handleBlock* workBlock, stdHeap* curHeap);
	
	freeBlock* PurgeBlock(handleBlock* blockHeader, stdHeap* curHeap);
	freeBlock* PurgeAndMakeSpace(blockSize_t sizeNeeded, stdHeap* curHeap, Boolean killEverything);
	blockSize_t CalcLargestPurgeRegion(stdHeap* curHeap);
	freeBlock* PurgeAndCompactHeap(stdHeap* curHeap);
	
	/** From Heap.c **/
	stdHeap* FindHeap(const void *address);
	stdBlock* FindBlockInHeap(const void* address, stdHeap* curHeap);
	Boolean	IsValidBlockInHeap(stdBlock* blockHeader, stdHeap* curHeap);
	stdHeap* CreateNewHeap(GrowZoneProcPtr pgrowZone, short numMasters, Ptr limit, Ptr memory);
	void GrowHeap(void *newMemory, blockSize_t size);
	Boolean ShrinkHeap(void *oldMemory, blockSize_t size);
	stdHeap* MoveHeapHeaderHigh(stdHeap* oldHeap);
	void RemoveHeap(Ptr rangeStart, Ptr rangeEnd);

	/** From Utilities.c and Utilities.a **/
	#ifdef linked_thinkc_app
		#define MoveBytes		MOVEBYTES
		#define ClearBytes		CLEARBYTES
		void MoveBytes(const void *source, void *destination, ulong length);
		void ClearBytes(void* destination, ulong length);
	#elif powerc
		#define MoveBytes		BlockMoveData	/* call blockmove since its faster on the 601 */
		#define ClearBytes		CLEARBYTES
		void ClearBytes(void* destination, ulong length);
	#elif StarTrek
		#define MoveBytes		BlockMove	/* call blockmove since its faster */
		#define ClearBytes		CLEARBYTES
		void ClearBytes(void* destination, ulong length);
	#else
		#define MoveBytes		BlockMoveData	/* call blockmove since its faster on PDM */
		/*
		 *	On 040 machines this may be faster, but on PDMs, its faster to call
		 *	the _BlockMove trap. This is the interface to the old code. I keep
		 *	it here in case we decide to ship this code on an 68020 or 68040 machine.
		 *
		 *	#pragma parameter MoveBytes(__A0,__A1,__D0)
		 *	void MoveBytes(const void* theSource, void* theDestination, ulong length)
		 *			= {	0x4EB0, 0x81E1, 0x1E00};	//		([$1E00])	
		 */
		
		void ClearBytes(void* destination, ulong length)
				= {	0x4EB0, 0x81E1, 0x1E04};	/* JSR		([$1E04])	*/
	#endif
	void FillBytes(void* destination, long length, long pattern);
	
	/****************************************************************/
	/* Inline routines called by other modules						*/
	/****************************************************************/
	
/* Sets the back pointer of the next block. Assumes that there is a next block */
#define ResetNextGuysBackPtr(blockHeader)								\
	{																	\
	stdBlock*	nextBlock;												\
																		\
	nextBlock = (stdBlock*) GetNextBlock(blockHeader);					\
																		\
	BACK(nextBlock) = blockHeader;										\
	}


/*
 *	Set the free master pointer to be odd so client who try to dereference
 *	free master pointers will run into problems immediately, instead of 
 *	subtley. This is most apparent when a client disposes of the handle
 *	twice.
 */

#define	IsOddMP(mp)			((ulong)(mp) & 0x0000001UL)
#define MaskMPBitOdd(mp)	((Ptr)((ulong)(mp) | 0x00000001UL))
#define UnmaskMPBit(mp)		((Ptr*)((ulong)(mp) & 0xFFFFFFFEUL))


	/****************************************************************/
	/* PowerPC support												*/
	/****************************************************************/
#ifdef powerc
	/* used for PowerPC high level interfaces */
	typedef struct InitZoneParamBlock
	{
		#pragma align=mac68k
	
		void*			startPtr;
		void*			limitPtr;
		short 			cMoreMasters;
		GrowZoneUPP		pGrowZoneProc;
	} InitZoneParamBlock;
#endif

#endif
