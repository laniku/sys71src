/*
	File:		QTMemory.h

	Contains:	Memory Manager interface to support QuickTime 1.6 Component Manager

	Written by:	Peter Hoddie

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <6>	  8/5/93	BT		<BT, JC> We came, we saw, we initialed...
		 <5>	  7/7/93	BT		<EPT> Continuation of Radar #1095398. TrashMemoryRecord and
									RegisterProcParams needed to be in this file, not QTMemory.c
		 <4>	  6/8/93	BMC		StarTrek support - rearrange include statements.
		 <3>	 5/21/93	JC		Support for QuickTime 1.6 now works. Merged with Brian's
									changes.
		 <2>	 5/21/93	BT		Make these pigs work on PowerPC
		 <1>	 5/20/93	JC		first checked in
		 <5>	 3/26/93	PH		add some routines for system heap allocations
		 <4>	 3/15/93	PH		fix Think C build
		 <3>	 3/14/93	PH		new trap. changed interfaces.
		 <2>	 3/10/93	PH		first pass at trash memory routines
		 <1>	  2/2/93	PH		first checked in

*/

#ifndef	__QTMemory__
#define	__QTMemory__

#ifdef StarTrek
	#include <Errors.h>
	#include <Memory.h>
	#include <Process.h>
	#include <ToolUtil.h>
#else
	#include <Errors.h>
	#include <Memory.h>
	#include <Processes.h>
	#include <ToolUtils.h>
#endif

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


// Note: the zero element of a list is unused. However, the first long
//	contains a count of the number of elements.
//
static OSErr addTrashMemoryProc(TrashProcPtr proc, short priority, Boolean alwaysNotify);
static OSErr removeTrashMemoryProc(TrashProcPtr proc);

#define	InitQTMemory	INITQTMEMORY	/* so it can be linked to MemMgrBoot.a */
void InitQTMemory();
OSErr c_RegisterHandleTrashNotification(RegisterProcParams *params);
OSErr c_UnregisterHandleTrashNotification(TrashProcPtr proc);

void c_TrashZone(THz zone);
void c_TrashProcess(ProcessSerialNumber *psn);
void c_TrashMemoryArea(Ptr startAddr, Ptr endAddr);

// now have C style parameter passing
Handle	c_NewHandleSystemSafe(Size handleSize);
Ptr 	c_NewPtrSystemSafe(Size ptrSize);
Boolean	c_EnoughSystemHeapSlop(void);

//#define gTrashMemoryList (gQTSegGlobals->trashMemoryGlobal)
// we redefine it to be memory location 1E0C for now
#define gTrashMemoryList (*(TrashMemoryList*)(0x1E0C))		// after vFiggyVector

//# if defined(mac68k)
#if !defined(powerc) && !defined(StarTrek)
//
//	Useful fast versions of existing Memory Manager calls
//
#pragma parameter HLockQ(__A0)
pascal void HLockQ(Handle h) =
	{0x7000, 0xa0a4};

#pragma parameter HUnlockQ(__A0)
pascal void HUnlockQ(Handle h) =
	{0x7001, 0xa0a4};

#pragma parameter HPurgeQ(__A0)
pascal void HPurgeQ(Handle h) =
	{0x7002, 0xa0a4};

#pragma parameter HNoPurgeQ(__A0)
pascal void HNoPurgeQ(Handle h) =
	{0x7003, 0xa0a4};

#pragma parameter __D0 HGetStateQ(__A0)
pascal SignedByte HGetStateQ(Handle h) =
	{0x7004, 0xa0a4};

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
	{0x7008, 0xa0a4};
#pragma parameter __D0 UnregisterPtrTrashNotification(__A0,__A1)
pascal OSErr UnregisterPtrTrashNotification(TrashProcPtr tp, Ptr p) =
	{0x7009, 0xa0a4};
#endif // THINK_C

#pragma parameter TrashZone(__A0)
pascal void TrashZone(THz zone) =
	{0x700a, 0xa0a4};

//
// stuff not intended for public consumption in any way
//
#pragma parameter TrashMemoryArea(__A0, __A1)
pascal void TrashMemoryArea(Ptr startAddr, Ptr endAddr) =
	{0x700b, 0xa0a4};
pascal void TrashCurrentProcess(void) =
	{0x4288, 0x700c, 0xa0a4};
#pragma parameter TrashProcess(__A0)
pascal void TrashProcess(const ProcessSerialNumber *psn) =
	{0x700c, 0xa0a4};

//
// some cool routines for keeping the system heap happy
//
#pragma parameter __D0 EnoughSystemHeapSlop
pascal Boolean EnoughSystemHeapSlop(void) =
	{0x700e, 0xa0a4};

#pragma parameter __A0 NewHandleSystemSafe(__A0)
pascal Handle NewHandleSystemSafe(Size handleSize) =
	{0x700d, 0xa1a4};

#pragma parameter __A0 NewPtrSystemSafe(__A0)
pascal Ptr NewPtrSystemSafe(Size ptrSize) =
	{0x700f, 0xa1a4};
	
long PurgeSpaceSystemContiguous(void)
 = {0xA562, 0x2008};

#else
// get your comments from somewhere else...

extern pascal void HLockQ(Handle h);
extern pascal void HUnlockQ(Handle h);
extern pascal void HPurgeQ(Handle h);
extern pascal void HNoPurgeQ(Handle h);
extern pascal SignedByte HGetStateQ(Handle h);
extern pascal void HSetStateQ(Handle h, SignedByte flags);
extern pascal OSErr RegisterHandleTrashNotification(TrashProcPtr tp, short priority, Handle h);
extern pascal OSErr RegisterPtrTrashNotification(TrashProcPtr tp, short priority, Ptr p);
extern pascal OSErr UnregisterHandleTrashNotification(TrashProcPtr tp, Handle h);
extern pascal OSErr UnregisterPtrTrashNotification(TrashProcPtr tp, Ptr p);
extern pascal void TrashZone(THz zone);
extern pascal void TrashMemoryArea(Ptr startAddr, Ptr endAddr);
extern pascal void TrashCurrentProcess(void);
extern pascal void TrashProcess(const ProcessSerialNumber *psn);
extern pascal Boolean EnoughSystemHeapSlop(void);
extern pascal Handle NewHandleSystemSafe(Size handleSize);
extern pascal Ptr NewPtrSystemSafe(Size ptrSize);
extern long PurgeSpaceSystemContiguous(void);
#endif

#endif // __QTMemory__
