/*
	File:		VMCalls.h

	Contains:	external calls for VM (called via MemoryDispatch)

	Written by:	Phil Goldman, Rick Daley, Darin Adler, Joe Buczek

	Copyright:	© 1989 by Apple Computer, Inc., all rights reserved.

	Change History:

	   <SM1>	  5/2/92	kc		Roll in Horror. Comments follow:
		7/28/89		jb		add DebugUtil trap
		7/24/89		jb		add debugger support functions
		5/3/89		dba		get rid of SystemMemoryInfo
		4/7/89		dba		change name of registerA0 parameter
		4/4/89		jb		add deferred user functions
		3/30/89		dba		add error codes
		3/24/89		dba		get rid of bits field
		3/24/89		dba		new today

	To Do:
*/

#include <Types.h>

typedef short PageState;
typedef short StatusRegisterContents;

/* values for PageState */

#define kPageInMemory  0
#define kPageOnDisk    1
#define kNotPaged      2

/* trap number of MemoryDispatch */

#define _MemoryDispatch				0xA05C

/* trap number of DeferUserFn */

#define	_DeferUserFn				0xA08F

/* trap number of DebugUtil */

#define	_DebugUtil					0xA08D

/* error codes */

#define notEnoughMemoryErr			(-620)		/* insufficient physical memory */
#define notHeldErr					(-621)		/* specified range of memory is not held */
#define cannotMakeContiguousErr		(-622)		/* cannot make specified range contiguous */
#define notLockedErr				(-623)		/* specified range of memory is not locked */
#define interruptsMaskedErr			(-624)		/* don’t call with interrupts masked */
#define	cannotDeferErr				(-625)		/* unable to defer additional user functions */

/* data structures for VM calls */

struct MemoryBlock
	{
	void*			address;				/* start of block */
	unsigned long	count;					/* size of block */
	};

#ifndef __cplusplus
typedef struct MemoryBlock MemoryBlock;
#endif

#define defaultPhysicalEntryCount	8		/* default number of physical blocks in table */

struct LogicalToPhysicalTable
	{
	MemoryBlock		logical;				/* logical block */
	MemoryBlock		physical[defaultPhysicalEntryCount];	/* equivalent physical blocks */
	};

#ifndef __cplusplus
typedef struct LogicalToPhysicalTable LogicalToPhysicalTable;
#endif

/* VM calls */

pascal OSErr HoldMemory(void* address, unsigned long count);
	/* keep pages in memory */
pascal OSErr UnholdMemory(void* address, unsigned long count);
	/* allow pages to swap to backing store */

pascal OSErr LockMemory(void* address, unsigned long count);
	/* lock pages to physical memory */
pascal OSErr LockMemoryContiguous(void* address, unsigned long count);
	/* lock pages to contiguous physical memory */
pascal OSErr UnlockMemory(void* address, unsigned long count);
	/* allow pages to re-map to physical memory */

pascal OSErr GetPhysical(LogicalToPhysicalTable* addresses, unsigned long* physicalEntryCount);
	/* map a logical block to physical blocks */

pascal OSErr DeferUserFn(ProcPtr, void* argument);
	/* delay execution of a procedure until page faulting is safe */

/* debugger support functions */

pascal long DebuggerGetMax(void);
	/* return the highest function number supported */
pascal void DebuggerEnter(void);
	/* enter the debugging state */
pascal void DebuggerExit(void);
	/* exit the debugging state */
pascal long DebuggerPoll(void);
	/* keyboard polling without interrupts */

pascal PageState GetPageState(void* address);
	/* return the state of the page containing the address */

pascal Boolean PageFaultFatal(void);
	/* determine if a page fault would currently be fatal */

pascal OSErr DebuggerLockMemory(void* address, unsigned long count);
	/* lock memory but do not disable cacheing of data */
pascal OSErr DebuggerUnlockMemory(void* address, unsigned long count);
	/* undo the effects of DebuggerLockMemory */

pascal StatusRegisterContents EnterSupervisorMode(void);
	/* explicitly enter supervisor mode */
