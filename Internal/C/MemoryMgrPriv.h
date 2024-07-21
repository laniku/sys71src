/*
	File:		MemoryMgrPriv.h

	Contains:	Private interfaces to the Memory Manager.

	Written by:	Dean Yu

	Copyright:	© 1991, 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	10/15/93	BT		Need to add some figment defines.
		 <1>	11/25/91	DTY		first checked in
	To Do:
*/

#ifndef __MEMORYMGRPRIV__
#define	__MEMORYMGRPRIV__

#ifndef __TYPES__
#include <Types.h>
#endif

#pragma parameter MoveHLow(__A0)
pascal void MoveHLow(Handle h)
 = 0xA09D; 

/****************************************************************************
	New Heap Manager prototypes
****************************************************************************/
typedef pascal void (*DisposeProcPtr)(Handle handle, THz zone);
typedef pascal void (*TrashNotificationProcPtr)(Ptr startAddr, Ptr endAddr);

/* local prototypes */
	/* These memory routines are called by the ProcessMgr to implement some its routines. */
		
	THz c_InitProcessMgrHeap(THz processMgrZone);
	
	/* for moving the boundary down, (ProcessMgrGZProc) */
	Size c_ShrinkSysHeap(Size cbNeeded);
	void c_LowerProcessMgrZoneBottom(Size cbLower, THz oldProcessMgrZone);
	
	/* for moving the boundary up, (SystemHeapGZProc) */
	Size c_ShrinkProcessMgrZone(Size sizeNeeded, THz processMgrZone);
	void c_ExtendSystemZone(Size sizeNeeded);
	

	/* From MemoryMgrPatches.c */
	void c_ReclaimSpaceIfSysHeapLow(Handle *theNewHandle, THz pmHeap);
	Size c_StraddleBlockSize(Size* lowPMStorage, Size* highSysStorage, Handle blockOfInterest, Boolean *sawInterestingBlock, THz pmHeap);
	Size c_ProcessMgrMaxBlock(THz processMgrZone);
	
	/* From MemoryMgrXXPatches.c where XX = 24 Xor 32 */
	Size c_GetProcessMgrLoFreeBytes(Handle handleOfInterest, Boolean *sawInterestingBlock);
	Size c_GetSystemHiFreeBytes(void);

	/*
	 *	additional routines that are used by the ProcessMgr but could be used by
	 *	other entities as well.
	 */
	OSErr c_NewHandleHi(Handle* theHandle, unsigned short trapWord, Size requestedSize);	/* especially useful */
	Ptr c_GetNextBlockInHeap(Ptr currentBlock, THz theZone);
	OSErr c_DisposeZone(THz theZone);
	OSErr c_SetZoneCompatibilityFlags(THz theZone, unsigned short theFlags);
	unsigned short c_GetZoneCompatibilityFlags(THz theZone);
	
	/* useful routines that can be used by system entities */
	OSErr c_RegisterChainedGrowZoneProc(GrowZoneProcPtr theProc, Boolean beforeUsersProc);
	OSErr c_UnregisterChainedGrowZoneProc(GrowZoneProcPtr theProc);
	OSErr c_RegisterDisposeProc(DisposeProcPtr theProc, THz theZone);


/*  _HeapDispatch prototypes */

	#pragma procname TrashNotification
	typedef pascal void (*TrashNotificationProcPtr)(Ptr startAddr, Ptr endAddr);
	
/**********************************************************************
 **** Defined in FigmentMemory.h (Thanks, Jim!)
 
	#pragma parameter TrashMemoryArea(__A0, __A1)
	pascal void TrashMemoryArea(Ptr startAddr, Ptr endAddr) =
		{0x700b, 0xa0a4};
	
	#pragma parameter __D0 EnoughSystemHeapSlop
	pascal Boolean EnoughSystemHeapSlop(void) =
		{0x700e, 0xa0a4};
**********************************************************************/
	
		#pragma parameter __D0 InitProcessMgrHeap(__A0)
		pascal THz InitProcessMgrHeap(THz processMgrZone)
		 = {0x7010,0xA0A4}; 
		
		#pragma parameter __D0 ShrinkSysHeap(__A0)
		pascal Size ShrinkSysHeap(Size cbNeeded)
		 = {0x7011,0xA0A4}; 

		#pragma parameter __D0 LowerProcessMgrZoneBottom(__A0, __A1)
		pascal void LowerProcessMgrZoneBottom(Size cbLower, THz oldProcessMgrZone)
		 = {0x7012,0xA0A4}; 
		
		#pragma parameter __D0 ShrinkProcessMgrZone(__A0, __A1)
		pascal Size ShrinkProcessMgrZone(Size sizeNeeded, THz processMgrZone)
		 = {0x7013,0xA0A4}; 
		
		#pragma parameter __D0 ExtendSystemZone(__A0)
		pascal void ExtendSystemZone(Size sizeNeeded)
		 = {0x7014,0xA0A4}; 
		
		#pragma parameter __D0 ReclaimSpaceIfSysHeapLow(__A0, __A1)
		pascal void ReclaimSpaceIfSysHeapLow(Handle *theNewHandle, THz pmHeap)
		 = {0x7015,0xA0A4}; 
		
		#pragma parameter __D0 StraddleBlockSize
		pascal Size StraddleBlockSize(Size* lowPMStorage, Size* highSysStorage, Handle blockOfInterest, Boolean *sawInterestingBlock, THz pmHeap)
		 = {0x204F,			/* MOVEA.L    	A7,A0		*/
			0x7016,			/* MOVEQ		$16,D0		*/
			0xA0A4,			/* _HeapDispatch			*/
			0x4FEF, 0x0014	/* LEA			$14(SP),SP	*/
			}; 

		#pragma parameter __D0 ProcessMgrMaxBlock(__A0)
		pascal Size ProcessMgrMaxBlock(THz processMgrZone)
		 = {0x7017,0xA0A4}; 
		
		#pragma parameter __D0 GetProcessMgrLoFreeBytes(__A0, __A1)
		pascal Size GetProcessMgrLoFreeBytes(Handle handleOfInterest, Boolean *sawInterestingBlock)
		 = {0x7018,0xA0A4}; 

		#pragma parameter __D0 GetSystemHiFreeBytes
		pascal Size GetSystemHiFreeBytes(void)
		 = {0x7019,0xA0A4}; 
	
		#pragma parameter __A0 NewHandleHi(__A0)
		pascal Handle NewHandleHi(Size requestedSize)
		 = {0x701A,0xA1A4}; 

		#pragma parameter __D0 GetNextBlockInHeap(__A0, __A1)
		pascal Ptr GetNextBlockInHeap(Ptr currentBlock, THz theZone)
		 = {0x701B,0xA0A4}; 

		#pragma parameter __D0 RegisterDisposeProc(__A0, __A1)
		pascal OSErr RegisterDisposeProc(DisposeProcPtr theProc, THz theZone)
		 = {0x701C,0xA0A4}; 
		
		#pragma parameter __D0 DisposeZone(__A0)
		pascal OSErr DisposeZone(THz theZone)
		 = {0x701D,0xA0A4}; 
		 
		#define	kDontUseOddFreeMPs	(0x8000)
		#pragma parameter __D0 SetZoneCompatibilityFlags(__A0,__A1)
		pascal OSErr SetZoneCompatibilityFlags(THz theZone, unsigned short flags)
		 = {0x701E,0xA0A4};
		
		#pragma parameter __D0 GetZoneCompatibilityFlags(__A0)
		pascal unsigned short GetZoneCompatibilityFlags(THz theZone)
		 = {0x701F,0xA0A4};
#endif
