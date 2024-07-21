/*
	File:		HALc96GC.c

	Contains:	Grand Central SCSI HBA

	Written by:	Craig Prouse

	Copyright:	╘ 1993-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	 1/12/94	chp		Comment out pipeline mode initialization.
	  <SMG2>	10/26/93	chp		Remove ATI bringup hack.

*/

#include	"SIMCorePriv.h"
#include	"HALc96.h"



// Should match MIN_AMIC_DMA_SIZE in order to reuse Setup/Teardown routines.
#define		MIN_GC_DMA_SIZE		0x0200



/*	ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии
	InitHW_GC:

	Vestigial.
	ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии
*/

OSErr InitHW_GC (HALc96Globals *HALg)
{
	#pragma unused (HALg)

	// Grand Central doesnуt require any particular channel hardware initialization.

	/*
	 *	It is assumed that HammerHead is previously programmed to allow the system
	 *	to run in pipeline mode. During bringup, this programming was effected here.
	 *	Pipeline mode is now enabled by TNT HardwareInit, before the emulator runs.
	 */

//	*(unsigned long *) 0xF80001D0 = 0x04000000;		/* ChipExpress HammerHead */
//	*(unsigned long *) 0xF8000090 = 0x04000000;		/* TI HammerHead */

	return noErr;
}



/*	ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии
	InitSW_GC:

	Allocate memory for double-buffered DMA and the DB-DMA Channel Command List.

	Both structures are contiguously locked physical buffers. They are allocated
	together on a page boundary and extend for an integral number of whole pages
	in order to avoid any other data structures sharing the same physical pages.

	*** WARNING:	The following code is page-size dependent and hard codes both
					the page size of the machine and the DMA buffer size. While
					not strictly kosher, this is consistent with other DMA HBAs.
	ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии
*/

OSErr InitSW_GC (HALc96Globals *HALg)
{
	OSErr			err;
	Ptr				memStart;
	void *			pageStart;
	unsigned long	needSize, peCount;

	const unsigned long pageSize = 4096;
	const unsigned long bufferSize = 1 * pageSize;		// must be a multiple of pageSize
	const unsigned long cclSize = 1 * pageSize;			// must be a multiple of pageSize

	LogicalToPhysicalTable	mappingTable;


	// Allocate a block with some extra slop for page alignment.

	needSize = bufferSize + cclSize;
	memStart = NewPtrSys(needSize + pageSize);
	if (memStart == nil) {
		err = MemError();
		goto failNewPtrSys;
	}

	// Calculate the first page boundary within the allocated block.
	// Scale back the allocation as much as possible.

	pageStart = (void *) ((unsigned long) memStart + (pageSize - 1) & ~(pageSize - 1));
	SetPtrSize(memStart, needSize + ((unsigned long) pageStart - (unsigned long) memStart));

	// Lock the buffers contiguously with respect to VM and calculate physical addresses.

	err = LockMemoryContiguous(pageStart, needSize);
	if (err)
		goto failLockMemoryContiguous;

	peCount = 1;
	mappingTable.logical.address = pageStart;
	mappingTable.logical.count = needSize;
	err = GetPhysical(&mappingTable, &peCount);
	if (err)
		goto failGetPhysical;

	// Record buffer addresses (logical and physical) in the HAL globals.

	HALg->physicalCopyBuffer = mappingTable.physical[0].address;
	HALg->logicalCopyBuffer = pageStart;

	HALg->cclPhysicalAddr = HALg->physicalCopyBuffer + bufferSize;
	HALg->cclLogicalAddr = (Ptr) ((unsigned long) pageStart + bufferSize);

	HALg->minDMAsize = MIN_GC_DMA_SIZE;

	return noErr;


	// Failure handlers:

	failGetPhysical:
		UnlockMemory(pageStart, needSize);

	failLockMemoryContiguous:
		DisposePtr(memStart);

	failNewPtrSys:
		return err;
}



/*	ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии
	SetupIOGC:

	Inspection shows that the PSC and AMIC versions of this routine are nearly
	identical. No major changes are yet required for TNT. Rather than copy and
	paste (again), just call the existing version.

	Some minor changes may be required eventually. But perhaps these would best
	be implemented by adding double buffer criteria to the HwDesc table rather
	than hard coding them. Many HBAs could share the bulk of this routine.
	ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии
*/

void SetupIOGC (SIM_IO *ioPtr)
{
	extern void SetupIOAMIC (SIM_IO *ioPtr);


	SetupIOAMIC(ioPtr);
}



/*	ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии
	TeardownIOGC:

	See the notes on SetupIOGC above.
	ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии
*/

void TeardownIOGC (SIM_IO *ioPtr, HALc96Globals *HALg)
{
	extern void TeardownIOAMIC (SIM_IO *ioPtr, HALc96Globals *HALg);


	TeardownIOAMIC(ioPtr, HALg);
}
