/*
	File:		MemMgrDebug.h

	Contains:	Memory Manager Debug Interfaces

	Written by:	Jeff Crawford

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<38>	  8/5/93	BT		<BT, JC> We came, we saw, we initialed...
		<37>	 7/27/93	BT		Change "#if hasInternalFigmentDebugging == TRUE" to "#if
									hasFigmentInternalDebugging". The xlc compiler seems to find
									that TRUE != TRUE. We'll see who wins...
		<36>	 7/20/93	JC		Spiffed up the client debug routines for Developer's CD version
									of Figment.
		<35>	 7/19/93	BT		Radar #1100608. If hasFigmentInternalDebugging == TRUE then
									define internal_debugging.  This allows us to do
									internal_debugging from FeatureSet with minimum of changes as
									per JCM request.
		<34>	 6/30/93	JC		#1089109: Removed fHeapIsDirty bit.
		<33>	 5/24/93	JC		Changed XXX to DbgXXX for all debug routines.
		<32>	 5/21/93	BT		Add __TYPES__ wrapper to PowerPC code too.
		<31>	 5/21/93	BT		Change 'applec' to 'mac68k'.  'applec' is defined in the Power
									compiler also.
		<30>	 5/19/93	JC		Began changes as requested by the code review. Removed options
									parameter from AllocateMoreMasters.
		<29>	  5/5/93	BT		Change macros with dangling else statements to macros enclosed
									in braces ({}).  A little more compiler friendly.
		<28>	  5/2/93	JC		Fixed heap debugging bits. From now on, kUseOddMPs field in no
									longer needed.
		<27>	 4/19/93	JC		Changed CheckSize & CheckAlignment to be debug routines instead
									of macros.
		<26>	 4/18/93	JC		Changed #defines to more acurate descriptions. Changed
									small_block_headers to small_freeBlock_headers and linkedIn to
									linked_thinkc_app.   ¥¥ Brian & Sam take note.¥¥
		 <1>	 6/10/92	JC		New Today

*/

#ifndef memMgrDebugIncludes
	#define memMgrDebugIncludes
	#if	hasFigmentInternalDebugging
		#define internal_debugging 1
	#endif
	
	#ifdef internal_debugging
		#define debugging			/* load debugging code */
	#endif

	#ifdef client_debugging
		#define debugging			/* load debugging code */
		#define clientCheckHeapEnabled		/*	check heap that clients pass to MM routines */
	#endif


	#ifdef debugging
		#ifndef privateMemMgrIncludes
			#include "MemMgr.h"
		#endif

		#ifndef define_debugger_and_debugstr
			#define define_debugger_and_debugstr
			#ifndef __TYPES__
				#if defined(THINK_C) || defined(mac68k)
					typedef unsigned char debugChar;
					pascal void DebugStr(const debugChar *) = 0xABFF;
					pascal void Debugger(void) = 0xA9FF;
				#else
					typedef char debugChar;
					void DebugStr(const debugChar *);
					void Debugger(void);
				#endif
			#endif
		#endif


		typedef enum {
			checkHeapIn			= 0x01,		/* check heap on entry */
			checkHeap			= 0x02,		/* check heap on exit */
			useOddUnusedMPs		= 0x04,		/* make unused master pointers odd */
			fillFreeBlocks		= 0x08,		/* fill free blocks with garbage */
			checkBlocks			= 0x10,		/* check blocks when they are passed to the memory manager */
			scrambleBlocks		= 0x20,		/* not implemented -- perform heap scramble when allowed */
			checkSubHeaps		= 0x40		/* not implemented -- check all sub heaps */
		} memoryValidationFlags;


		long GetHeapValidation(stdHeap *source);
		void SetHeapValidation(stdHeap *target, long flags);
	
		void ValidateHeap(stdHeap* target, long flags);
		void ValidatePtr(void* block, stdHeap* curHeap);
		void ValidateHandle(void* block, stdHeap* curHeap);
		void ValidateMasterPointer(void* masterPointer, stdHeap* curHeap);
		void DbgValidateTrapWord(ushort trapWord);

		#define IfDbgMsg(a, b, c)	{ if (a) DbgMessage(b, (long)c); }

		void	DbgMessage(const char *msg, long data);
		void	_PtrBlockCheck(void* block, stdHeap* curHeap);
		void	_HandleBlockCheck(void* block, stdHeap* curHeap);
		void	_MasterPtrCheck(void* block, stdHeap* curHeap);
		void	_CheckHeap(stdHeap* curHeap);
		void	_AlertClientRelocateBlock(Ptr oldLocation, Ptr newLocation, stdHeap* curHeap);

		
		/* jeff, might want to check to see that the heap contains debugging info before checking validation flags */
		#define DbgCode(code)						code
		#define DbgPtrBlockCheck(block,h)			if ((h)->validationFlags & checkBlocks) _PtrBlockCheck(block, h)
		#define DbgHandleBlockCheck(block, h)		if ((h)->validationFlags & checkBlocks) _HandleBlockCheck(block, h)
		#define DbgMasterPtrCheck(block,h)			if ((h)->validationFlags & checkBlocks) _MasterPtrCheck(block, h)
		#define DbgCheckHeap(h)						if ((h)->validationFlags & checkHeap) _CheckHeap(h)
		#define DbgAlertClientRelocateBlock(o,n,h)	if ((h)->validationFlags & checkHeap) _AlertClientRelocateBlock(o,n,h)
		
		#ifdef clientCheckHeapEnabled
			#define DbgClientCheckHeap(h)			if( (h)->validationFlags & checkHeapIn ) _CheckHeap(h)
		#else
			#define DbgClientCheckHeap(h)
		#endif

		void DbgCheckSize(ulong theSize);
		void DbgCheckAlignment(void* thePtr);

		#define garbageData						0x50FF50FF 		/* Greg MariottÕs "new" (as of 4/29/93) offical number */
		#define DbgGarbageFill(h ,a, b)			if ((h)->validationFlags & fillFreeBlocks) FillBytes(a, b, garbageData)

	#else
		#define DbgCode(code)
		#define IfDbgMsg(a, b, c)
		#define DbgMessage(a, b)
		#define DbgPtrBlockCheck(block,heap)
		#define DbgHandleBlockCheck(block,heap)
		#define DbgMasterPtrCheck(block,heap)
		#define DbgCheckHeap(h)
		#define DbgAlertClientRelocateBlock(o,n,z)
		#define DbgClientCheckHeap(h)
		#define DbgCheckSize(x)
		#define DbgCheckAlignment(x)
		#define DbgValidateTrapWord(tw)
		#define DbgGarbageFill(h, a, b)
	#endif /* debugging */

	#ifdef internal_debugging
		#define IfIntDebugMsg(a, b, c)		{ if (a) DbgMessage(b, (long)c); }
	#else
		#define IfIntDebugMsg(a, b, c)
	#endif
	
	#ifdef client_debugging
		#define IfClientDebugMsg(a, b, c)	{ if (a) DbgMessage((b), (long)(c)); }
		#define	ClientDebugMsg(b, c)		DbgMessage((b), (long)(c))
	#else
		#define IfClientDebugMsg(a, b, c)
		#define	ClientDebugMsg(b, c)
	#endif

		
	
#endif /* memMgrDebugIncludes */
