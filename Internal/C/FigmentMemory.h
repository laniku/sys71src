/*
	File:		FigmentMemory.h

	Contains:	interfaces for Figment Manager

	Written by:	QuickTime

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 6/13/93	JDR		first checked in

*/

#ifndef	__FIGMENTMemory__
#define	__FIGMENTMemory__

#include <Errors.h>
#include <Memory.h>
#include <Processes.h>
#include <ToolUtils.h>

#ifdef WARHOL_NOSEGS
// implies 68000
#define CallQTMem(selector,needsA1) {0x303c,selector,0xa0a4+needsA1}
#pragma	processor 68000
#else
#define CallQTMem(selector,needsA1) {0x7000+selector,0xa0a4+needsA1}
#endif


typedef pascal void (*TrashProcPtr)(Ptr startAddr, Ptr endAddr);

typedef struct {
	TrashProcPtr	proc;
	Boolean			alwaysNotify;
	Boolean			pad;
	unsigned short	count;
	short			priority;
}TrashMemoryRecord, *TrashMemoryPtr, **TrashMemoryList;

typedef struct {
	Handle			h;
	short			priority;
	TrashProcPtr	proc;
} RegisterProcParams;


//
//	Useful fast versions of existing Memory Manager calls
//
#pragma parameter HLockQ(__A0)
pascal void HLockQ(Handle h) =
	{0x7000,0xa0a4};

#pragma parameter HUnlockQ(__A0)
pascal void HUnlockQ(Handle h) =
	{0x7001,0xa0a4};

#pragma parameter HPurgeQ(__A0)
pascal void HPurgeQ(Handle h) =
	{0x7002,0xa0a4};

#pragma parameter HNoPurgeQ(__A0)
pascal void HNoPurgeQ(Handle h) =
	{0x7003,0xa0a4};

#pragma parameter __D0 HGetStateQ(__A0)
pascal SignedByte HGetStateQ(Handle h) =
	{0x7004,0xa0a4};

#pragma parameter HSetStateQ(__A0, __D0)
pascal void HSetStateQ(Handle h, SignedByte flags) =
	{0x3240, 0x7005, 0xa0a4};


//
// strange and wonderful new calls for dealing with flying heaps
//

#ifndef THINK_C
#pragma parameter __D0 RegisterHandleTrashNotification
pascal OSErr RegisterHandleTrashNotification(TrashProcPtr tp, short priority, Handle h) =
	{0x204f, 0x7006, 0xa0a4, 0x4fef, 10};
#pragma parameter __D0 RegisterPtrTrashNotification
pascal OSErr RegisterPtrTrashNotification(TrashProcPtr tp, short priority, Ptr p) =
	{0x204f, 0x7007, 0xa0a4, 0x4fef, 10};

#pragma parameter __D0 UnregisterHandleTrashNotification(__A0,__A1)
pascal OSErr UnregisterHandleTrashNotification(TrashProcPtr tp, Handle h) =
	CallQTMem(8,0);
#pragma parameter __D0 UnregisterPtrTrashNotification(__A0,__A1)
pascal OSErr UnregisterPtrTrashNotification(TrashProcPtr tp, Ptr p) =
	CallQTMem(9,0);
#endif THINK_C

#pragma parameter TrashZone(__A0)
pascal void TrashZone(THz zone) =
	CallQTMem(10,0);

//
// stuff not intended for public consumption in any way
//
#pragma parameter TrashMemoryArea(__A0, __A1)
pascal void TrashMemoryArea(Ptr startAddr, Ptr endAddr) =
	CallQTMem(11,0);
pascal void TrashCurrentProcess(void) =
#ifdef WARHOL_NOSEGS
	{0x4288, 0x700c, 0xa0a4};
#else
	{0x4288, 0x303c,12, 0xa0a4};
#endif

#pragma parameter TrashProcess(__A0)
pascal void TrashProcess(const ProcessSerialNumber *psn) =
	CallQTMem(12,0);

#pragma parameter SetTrashMemoryList(__A0)
pascal void SetTrashMemoryList(void *) =
	CallQTMem(16,0);
#pragma parameter __A0 GetTrashMemoryList
pascal TrashMemoryList GetTrashMemoryList(void) =
	CallQTMem(17,0x0100);
//
// random numbers to keep things from disappearing too early.
//	smaller numbers go away earlier.
//
enum {
	kQTSegLoadPriority = 4000,
	kComponentManagerPriority = 3000,
	kICMPriority = 2000,
	kMovieToolboxPriority = 1000
};


//
// some cool routines for keeping the system heap happy
//
#pragma parameter __D0 EnoughSystemHeapSlop
pascal Boolean EnoughSystemHeapSlop(void) =
	CallQTMem(14,0);

#pragma parameter __A0 NewHandleSystemSafe(__A0)
pascal Handle NewHandleSystemSafe(Size handleSize) =
	CallQTMem(13,0x0100);

#pragma parameter __A0 NewPtrSystemSafe(__A0)
pascal Ptr NewPtrSystemSafe(Size ptrSize) =
	CallQTMem(15,0x0100);

#endif __FIGMENTMemory__

