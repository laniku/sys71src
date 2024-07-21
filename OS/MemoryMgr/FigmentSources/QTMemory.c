/*
	File:		QTMemory.c

	Contains:	Memory Manager implementation to support QuickTime 1.6

	Written by:	Peter Hoddie

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<13>	10/14/93	BT		<BT, EPT> Radar 1117552; Change interfaces around.
		<12>	  8/5/93	BT		<BT, JC> We came, we saw, we initialed...
		<11>	 7/28/93	BT		<BT, JRG> Radar 1096298, 1102433. Finish QT
									HandleTrashNotification code. The Component Manager wasn't
									getting notified that memory was going away and would call dead
									space.
		<10>	  7/7/93	BT		<EPT> Continuation of Radar #1095398. I forgot to put in D1 trap
									parameter for native glue calling conventions some time back,
									now that it is used it needs to be there. This file needs the
									proper naming convention to do the right thing with this
									parameter.
		 <9>	  7/2/93	BT		(With EPT) Radar #1095398. Fix internal Memory Manager calls to
									go thru the trap table interface.
		 <8>	 6/25/93	BT		(with EPT) Back out last change, change occurences of MemError()
									to LMGetMemErr()
		 <7>	 6/25/93	BT		(Repairing damage from (EPT,JRG) Added LowMem.h
		 <6>	  6/8/93	BMC		StarTrek support - rearranged include statements & other rocket
									science.
		 <5>	 5/26/93	BT		Finish fixing this abomination for RISC alpha.
		 <4>	 5/25/93	BT		Blasted the file type somehow, this fixes it.
		 <3>	 5/25/93	BT		Change routine names "_Å" to "__Å".  This follows our naming
									conventions more closely for native routines.
		 <2>	 5/21/93	JC		Support for QuickTime 1.6 now works. Added initialization
									routine to support trash notification procs.
		 <1>	 5/20/93	JC		first checked in
		 <3>	 3/26/93	PH		stupid optimization
		 <2>	 3/14/93	PH		second path at trash memory routines
		 <1>	 3/10/93	PH		first checked in

*/

#ifdef StarTrek
	#include <MacMem.h>
	#include <Process.h>
	#include <SysEqu.h>
	#include <ToolUtil.h>
	#include <Errors.h>
#else
	#include <Errors.h>
	#include <Memory.h>
	#include <Processes.h>
	#include <SysEqu.h>
	#include <ToolUtils.h>
	
	//#ifdef FOR_POWER_PC_PEOPLE
	#include <ExpandMemPriv.h>
	#include <ProcessesPriv.h>
	#include <VMCallsPriv.h>
	//#endif
#endif

#if defined(powerc)
	#include <LowMem.h>
#endif

//#include "QTSegLoader.h"
#include "MemMgr.h"
#include "QTMemory.h"

void InitQTMemory()
	{
	gTrashMemoryList = (TrashMemoryList) NewHandleSysClear(10);
	}


OSErr addTrashMemoryProc(TrashProcPtr proc, short priority, Boolean alwaysNotify)
{
	TrashMemoryList list = gTrashMemoryList;
	long count = **(long **)list;	
	TrashMemoryPtr tp = *list + 1;
	TrashMemoryRecord localTrash;
	long index = 1;
	OSErr err;

	// search the list for an existing match
	while (count--) {
		if (tp->proc == proc) {
			// found a match, so bump the counter
			tp->count++;
			return noErr;
		}
		if (tp->priority > priority)
			break;

		tp++;
		index++;
	}

	// fill in the new element	
	localTrash.proc = proc;
	localTrash.count = 1;
	localTrash.priority = priority;
	localTrash.alwaysNotify = alwaysNotify;

	// insert the new element into the list
	Munger((Handle)list, index * sizeof(localTrash), nil, 0,
		(Ptr)&localTrash, sizeof(localTrash));
	if (err = LMGetMemErr()) return err;

	// remember that we have another element
	(**(long **)list)++;

	return noErr;
}

OSErr removeTrashMemoryProc(TrashProcPtr proc)
{
	TrashMemoryList list = gTrashMemoryList;
	long count = **(long **)list;	
	TrashMemoryPtr tp = *list + 1;

	// search the list for an existing match
	while (count--) {
		if (tp->proc == proc) {
			// found a match, so down the counter
			tp->count--;
			if (tp->count == 0) {
				// remove the entire element. no references to it left.
				Munger((Handle)list, (Ptr)tp - (Ptr)*list, nil, sizeof(TrashMemoryRecord),
						(void *)-1, 0);

				// one less element to worry about
				(**(long **)list)--;
			}
			return noErr;
		}
		tp++;
	}

	// element didn't exist in list. you suck.
#ifdef WARHOL_DEBUG
	DebugStr("\pZone/Memory tracking code confused.");
#endif
	return paramErr;
}

OSErr c_RegisterHandleTrashNotification(RegisterProcParams *params)
{
	return addTrashMemoryProc(params->proc, params->priority, (params->h == 0));
}

OSErr c_UnregisterHandleTrashNotification(TrashProcPtr proc)
{
	return removeTrashMemoryProc(proc);
}

void c_TrashZone(THz zone)
{
	TrashMemoryArea((Ptr)zone, *(Ptr *)zone);
}

#define	UnimplementedTrap	0xA89F
#define	JugglerTrap		0xA88F

void c_TrashProcess(ProcessSerialNumber *psn)
{
#ifndef StarTrek
//	Boolean processMgrExists = (GetToolTrapAddress(JugglerTrap) != GetToolTrapAddress(UnimplementedTrap));
	Boolean processMgrExists = *(long *)0x103c != *(long *)0x107c;			// cheaper

	if ((*(short *)SysVersion < 0x0700) || !processMgrExists) {
		// system 6 world, or somewhere (strange) in the boot process
		Ptr zoneBegin, zoneEnd;

		zoneBegin = (Ptr)ApplicZone();
		if (zoneBegin != (Ptr)SystemZone()) {
			if (!processMgrExists)
				zoneEnd = *(Ptr *)BufPtr;
			else {
				unsigned long temp;

				temp = *(long *)(zoneBegin-8);
				if ((temp >> 24) == 0x80)								/* does it look like a 24-bit block header? */
					zoneEnd = zoneBegin + (temp&0xffffff);
				else if ((*(unsigned long *)(zoneBegin-12)>>16) == 0x8080)	/* does it look like a 32-bit block header? */
					zoneEnd = zoneBegin + temp;
				else
					zoneEnd = *(Ptr *)zoneBegin;						/* no, use the blocklim */
			}
			TrashMemoryArea(zoneBegin, zoneEnd);
		}
	}
	else {
#endif	/* !StarTrek */
		ProcessSerialNumber thisPSN;

		if (psn || (GetCurrentProcess(&thisPSN) == noErr)) {
			ProcessInfoRec info;

			info.processInfoLength = sizeof(ProcessInfoRec);
			info.processName = nil;
			info.processAppSpec = nil;
			if (!psn) psn = &thisPSN;
			if (GetProcessInformation(psn, &info) == noErr)
				TrashMemoryArea(info.processLocation, info.processLocation + info.processSize);
		}
#ifndef StarTrek
	}
#endif	/* !StarTrek */
}

void c_TrashMemoryArea(Ptr startAddr, Ptr endAddr)
{
	TrashMemoryList list = gTrashMemoryList;
	long index = 1;

	// walk the list. call each proc in the list with the given address range.
	while (index <= **(long **)list) {					// the number of items may change during the loop
		TrashMemoryPtr tp = *list + index;				// point to the next record
		TrashMemoryRecord localTP = *tp;				// make a copy of the current record
		long oldCount = **(long **)list;				// remember current number of records
		long countDelta;

		// bump the counter on this element so it won't get completely removed
		tp->count++;

		// call the proc
		CALL_FNC_PTR_2(TrashNotificationProcPtr, tp->proc, uppTrashNotificationProcInfo, startAddr, endAddr);

		// down the counter again
		tp = *list + index;
		if (tp->count == 1)
			removeTrashMemoryProc(tp->proc);									// no other ref's. kill it.
		else
			tp->count--;														// more clients. just fix count.

		// nextÉ taking into account possible list growth/shrinking
		countDelta = oldCount - **(long **)list;
		if (countDelta >= 0)
			index = index + 1 - countDelta;					// list shrunk or stayed same size
		else
			index = 1;										// by some miracle, it grew. start over.
	}
}


//#ifdef FOR_POWER_PC_PEOPLE
Handle c_NewHandleSystemSafe(Size handleSize)
{
	Handle h = NewHandleSys(handleSize);

	if (h) {
		if (!EnoughSystemHeapSlop()) {
			DisposHandle(h);
			h = nil;
			*(OSErr *)MemErr = memFullErr;
		}
	}

	return h;
}

Ptr c_NewPtrSystemSafe(Size ptrSize)
{
	Ptr p = NewPtrSys(ptrSize);

	if (p) {
		if (!EnoughSystemHeapSlop()) {
			DisposPtr(p);
			p = nil;
			*(OSErr *)MemErr = memFullErr;
		}
	}

	return p;
}

Boolean c_EnoughSystemHeapSlop(void)
{
	long			neededContigSpace;

	neededContigSpace = GetExpandMemMinSysHeapFreeSpace();

	if ( GetExpandMemProcessMgrExists() )
	{
		unsigned long	hiSysRoom;
		unsigned long	lowTempRoom;

		if (SysZoneFloatSizes(nil, &lowTempRoom) != noErr)
			lowTempRoom = 0;
		if (lowTempRoom < neededContigSpace)
		{
			if (SysZoneFloatSizes(&hiSysRoom, nil) != noErr)
				hiSysRoom = 0;
			if ((hiSysRoom + lowTempRoom) < neededContigSpace)
			{
				return false;
			}
		}
	}
	else if (PurgeSpaceSystemContiguous() < neededContigSpace)
	{
		return false;
	}
	return true;
}

//#endif








