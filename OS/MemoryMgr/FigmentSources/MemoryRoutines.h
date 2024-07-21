/*
	File:		MemoryRoutines.h

	Contains:	Memory Manager Internal Interfaces

	Written by:	Jeff Crawford

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <8>	  8/5/93	BT		<BT, JC> We came, we saw, we initialed...
		 <7>	 7/12/93	BMC		StarTrek - no longer define lowmem macros for startrek - we have
									our own functions.
		 <6>	  6/4/93	JC		Fixed API to ReallocHandle.
		 <5>	  6/1/93	BMC		CompareFiles boondoggle - accidentally left SetZone defined
									twice. Duh.
		 <4>	  6/1/93	BMC		CompareFiles boondoggle - accidentally left PurgeSpaceSys
									defined twice.
		 <3>	  6/1/93	BMC		StarTrek support
		 <1>	 7/31/92	JC		Old Today

*/

#ifndef memoryRoutinesIncludes
#define memoryRoutinesIncludes


	#ifdef __cplusplus
	extern "C" {
	#endif

	/* Memory Manager public interfaces */
	void c_InitZone(GrowZoneProcPtr	pgrowZone, short cmoreMasters, void* limitPtr, void* startPtr);
	Ptr c_GetApplLimit(void);
	OSErr c_SetApplLimit(Ptr zoneLimit);
	OSErr c_MaxApplZone(void);
	OSErr c_MoreMasters(void);
	THz c_GetZone(void);
	OSErr c_SetZone(THz theZone);
	THz c_SystemZone(void);
	THz c_ApplicZone(void);
	OSErr c_NewHandle(Handle* theHandle, ushort trapWord, Size requestedSize);
	OSErr c_NewEmptyHandle(Handle* theHandle, ushort trapWord);
	OSErr c_DisposeHandle(Handle handle);
	Size c_GetHandleSize(const Handle handle);
	OSErr c_SetHandleSize(Handle handle, Size requestedSize);
	OSErr c_HandleZone(THz* theZone, Handle handle);
	Handle c_RecoverHandle(ushort trapWord, const Ptr doomedBlock);
	OSErr c_ReallocHandle(Handle handle, Size requestedSize);
	OSErr c_NewPtr(Ptr* thePtr, ushort trapWord, Size requestedSize);
	OSErr c_DisposePtr(Ptr block);
	Size c_GetPtrSize(const Ptr block);
	OSErr c_SetPtrSize(Ptr block, Size requestedSize);
	OSErr c_PtrZone(THz* theZone, Ptr thePtr);
	long c_FreeMem(ushort trapWord);
	Size c_MaxMem(ushort trapWord, Size *growSize);
	Size c_CompactMem(ushort trapWord, Size sizeNeeded);
	OSErr c_ReserveMem(ushort trapWord, Size sizeNeeded);
	OSErr c_PurgeMem(ushort trapWord, Size sizeNeeded);
	OSErr c_EmptyHandle(Handle handle);
	OSErr c_HLock(Handle handle);
	OSErr c_HUnlock(Handle handle);
	OSErr c_HPurge(Handle handle);
	OSErr c_HNoPurge(Handle handle);
	OSErr c_SetGrowZone(GrowZoneProcPtr theGrowZoneProc);
	Handle c_GZSaveHnd(void);
	Ptr c_TopMem(void);
	OSErr c_MoveHHi(Handle handle);
	OSErr c_MoveHLow(Handle handle);
	OSErr c_MemError(void);
	Size c_MaxBlock(ushort trapWord);
	Size c_PurgeSpace(ushort trapWord, Size* contig);	/* returns total as result */
	long c_StackSpace(void);
	OSErr c_HSetRBit(Handle handle);
	OSErr c_HClrRBit(Handle handle);
	unsigned char c_HGetState(Handle handle);
	OSErr c_HSetState(Handle handle, unsigned char flags);


	#ifdef StarTrek
pascal void InitZone(GrowZoneProcPtr	pgrowZone, short cmoreMasters, void* limitPtr, void* startPtr);
pascal void SetApplLimit(Ptr zoneLimit);
pascal void MaxApplZone(void);
pascal void MoreMasters(void);
pascal THz GetZone(void);
pascal void SetZone(THz hz);
pascal Handle NewHandle(Size requestedSize);
pascal Handle NewHandleSys(Size requestedSize);
pascal Handle NewHandleClear(Size requestedSize);
pascal Handle NewHandleSysClear(Size requestedSize);
pascal Handle NewEmptyHandle(void);
pascal Handle NewEmptyHandleSys(void);
#define DisposHandle(h)		DisposeHandle(h)
pascal void DisposeHandle(Handle theHandle);
pascal Size GetHandleSize(Handle theHandle);
pascal void SetHandleSize(Handle theHandle, Size requestedSize);
pascal THz HandleZone(Handle theHandle);
pascal Handle RecoverHandle(Ptr masterPointer);
pascal Handle RecoverHandleSys(Ptr masterPointer);
pascal void ReallocHandle(Handle handle, Size requestedSize);
pascal Ptr NewPtr(Size requestedSize);
pascal Ptr NewPtrSys(Size requestedSize);
pascal Ptr NewPtrClear(Size requestedSize);
pascal Ptr NewPtrSysClear(Size requestedSize);
pascal void DisposePtr(Ptr thePtr);
pascal Size GetPtrSize(Ptr thePtr);
pascal void SetPtrSize(Ptr thePtr, Size requestedSize);
pascal THz PtrZone(Ptr thePtr);
pascal long FreeMem(void);
pascal long FreeMemSys(void);
pascal Size MaxMem(Size *growSize);
pascal Size MaxMemSys(Size *growSize);
pascal Size CompactMem(Size sizeNeeded);
pascal Size CompactMemSys(Size sizeNeeded);
pascal void ReserveMem(Size sizeNeeded);
pascal void ReserveMemSys(Size sizeNeeded);
pascal void PurgeMem(Size sizeNeeded);
pascal void PurgeMemSys(Size sizeNeeded);
pascal void EmptyHandle(Handle handle);
pascal void HLock(Handle handle);
pascal void HUnlock(Handle handle);
pascal void HPurge(Handle handle);
pascal void HNoPurge(Handle handle);
pascal void SetGrowZone(GrowZoneProcPtr theGrowZoneProc);
pascal void MoveHHi(Handle theHandle);
pascal void MoveHLow(Handle theHandle);
pascal Size MaxBlock(void);
pascal void PurgeSpace(Size *total,Size *contig);
pascal void PurgeSpaceSys(Size *total,Size *contig);
pascal long StackSpace(void);
pascal void HSetRBit(Handle handle);
pascal void HClrRBit(Handle handle);
pascal char HGetState(Handle handle);
pascal void HSetState(Handle handle, char flags);
	
	#endif /* StarTrek */


	#ifdef __cplusplus
	}
	#endif


#endif
