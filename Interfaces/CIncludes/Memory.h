/************************************************************

Created: Saturday, July 27, 1991 at 4:28 PM
 Memory.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1993
  All rights reserved

	Change History (most recent first):

	  <SM11>	 7/30/93	JDR		One more thrash at GetHandleSize: Create InlineGetHandleSize,
									which is used inline, and knows that an error will come back
									instead of 0.
	  <SM10>	 7/21/93	RC		Back Out <sm 8>
		<SM8>	  4/7/93	CSS		Re-disable the StripAddress and SwapMMUMode code when the
									Supports24Bit flag is off.
		<SM7>	 11/10/92	CSS		Added Fast trap options on last checkin (SM6).  Commented out
									Supports24Bit for now until we determine what to do about the
									SlotMgr which must be in 24 bit mode sometimes.
									Update from Reality:
									<21>	10/16/92	DTY		Add BlockMoveData.
		<20>	  7/8/92	DTY		Make GetHandleSize call the glue again because it’s documented
									as returning 0 to a high level language if an error occured.
		<19>	  7/8/92	DTY		Take out the last change for now. We’ll put it back in after
									Cube-E is done.
		<18>	  7/6/92	DTY		Make GetPtrSize an inline.
		<17>	 6/11/92	DTY		Change GetHandleSize into an inline.
		<16>	  3/2/92	DCL		Backing out a mistaken fix (from Radar) of Size from long to
									unsigned long. After futher discussion it was the wrong thing to
									do. Broke the build. #2
		<15>	  3/2/92	DCL		Changed "Size" from long to unsigned long.
		<14>	 7/30/91	JL		Updated Copyright.
		<13>	 1/27/91	LN		Checked in Database generate file from DSG.
		<12>	12/14/90	dba		<JDR> add Translate24To32, low-level memory control routines,
									and debugger support routines
		<11>	11/28/90	JL		Put formal parameter names back.
		<10>	 11/7/90	JL		Changed all #defines to anonymous enums
		 <9>	 11/5/90	DFH		Added new names for Temporary Memory calls.
		 <8>	 11/4/90	dba		use #define instead of inline for GetApplLimit, SystemZone,
									ApplicZone, GZSaveHnd, TopMem; add ApplicationZone,
									TempNewHandle, ReallocateHandle, got rid of some extraneous
									parameter names; made some parameters void* instead of Ptr;
									added more use of const in parameters
		 <7>	10/30/90	dba		make smaller version of MemError (with #define)
		 <6>	10/21/90	gbm		(with dba) Made compatible with 3.2 C compiler (and incompatible
									with previous compilers).
		 <6>	10/10/90	JAL		New style #Pragma Parameters for MPW 3.2 C
** 1.2	CCH 06/12/1989 Changed "short" in HGetState and HSetState to "char".
** 1.1	CCH 11/ 9/1988 Fixed headers and removed projector resource.
** 1.0	CCH 11/ 9/1988 Adding to EASE.
************************************************************/

// NOTE!!!!!!!!!!!
//
// Don’t change GetHandleSize and GetPtrSize into inlines.  They are documented as returning
// 0 in case of an error in Inside Mac, but the traps actually return an error code in D0.
// The glue sets D0 to 0 if an error occured.

#ifndef __MEMORY__
#define __MEMORY__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef	__ROMFastTrapsIncluded__
#include	"ROMFastTraps.h"
#endif

enum {

 maxSize = 0x800000,	/*Max data block size is 8 megabytes*/
 defaultPhysicalEntryCount = 8,

/* values returned from the GetPageState function */
 kPageInMemory = 0,
 kPageOnDisk = 1,
 kNotPaged = 2
};

typedef long Size;		/* size of a block in bytes */
typedef pascal long (*GrowZoneProcPtr)(Size cbNeeded);

struct Zone {
 Ptr bkLim;
 Ptr purgePtr;
 Ptr hFstFree;
 long zcbFree;
 GrowZoneProcPtr gzProc;
 short moreMast;
 short flags;
 short cntRel;
 short maxRel;
 short cntNRel;
 short maxNRel;
 short cntEmpty;
 short cntHandles;
 long minCBFree;
 ProcPtr purgeProc;
 Ptr sparePtr;
 Ptr allocPtr;
 short heapData;
};

typedef struct Zone Zone;
typedef Zone *THz;

struct MemoryBlock {
 void * address;
 unsigned long count;
};

typedef struct MemoryBlock MemoryBlock;

struct LogicalToPhysicalTable {
 MemoryBlock logical;
 MemoryBlock physical[defaultPhysicalEntryCount];
};

typedef struct LogicalToPhysicalTable LogicalToPhysicalTable;


typedef short PageState;
typedef short StatusRegisterContents;

#ifdef __cplusplus
extern "C" {
#endif
#define GetApplLimit() (* (Ptr*) 0x0130)
#pragma parameter __A0 GetZone
pascal THz GetZone(void)
 = 0xA11A; 
#define SystemZone() (* (THz*) 0x02A6)
#define ApplicZone() (* (THz*) 0x02AA)
#define ApplicationZone() (* (THz*) 0x02AA)
#pragma parameter __A0 NewHandle(__D0)
pascal Handle NewHandle(Size byteCount)
 = {__GenOSTrapCode(0xA122)}; 
#pragma parameter __A0 NewHandleSys(__D0)
pascal Handle NewHandleSys(Size byteCount)
 = {__GenOSTrapCode(0xA522)}; 
#pragma parameter __A0 NewHandleClear(__D0)
pascal Handle NewHandleClear(Size byteCount)
 = {__GenOSTrapCode(0xA322)};
#pragma parameter __A0 NewHandleSysClear(__D0)
pascal Handle NewHandleSysClear(Size byteCount)
 = {__GenOSTrapCode(0xA722)}; 
#pragma parameter __A0 HandleZone(__A0)
pascal THz HandleZone(Handle h)
 = {__GenOSTrapCode(0xA126)}; 
#pragma parameter __A0 RecoverHandle(__A0)
pascal Handle RecoverHandle(Ptr p)
 = {__GenOSTrapCode(0xA128)}; 
#pragma parameter __A0 RecoverHandleSys(__A0)
pascal Handle RecoverHandleSys(Ptr p)
 = {__GenOSTrapCode(0xA528)}; 
#pragma parameter __A0 NewPtr(__D0)
pascal Ptr NewPtr(Size byteCount)
 = {__GenOSTrapCode(0xA11E)}; 
#pragma parameter __A0 NewPtrSys(__D0)
pascal Ptr NewPtrSys(Size byteCount)
 = {__GenOSTrapCode(0xA51E)};
#pragma parameter __A0 NewPtrClear(__D0)
pascal Ptr NewPtrClear(Size byteCount)
 = {__GenOSTrapCode(0xA31E)}; 
#pragma parameter __A0 NewPtrSysClear(__D0)
pascal Ptr NewPtrSysClear(Size byteCount)
 = {__GenOSTrapCode(0xA71E)}; 
#pragma parameter __A0 PtrZone(__A0)
pascal THz PtrZone(Ptr p)
 = 0xA148; 
#define GZSaveHnd() (* (Handle*) 0x0328)
#define TopMem() (* (Ptr*) 0x0108)
#pragma parameter __D0 MaxBlock
pascal long MaxBlock(void)
 = 0xA061; 
#pragma parameter __D0 MaxBlockSys
pascal long MaxBlockSys(void)
 = 0xA461; 
#pragma parameter __D0 StackSpace
pascal long StackSpace(void)
 = 0xA065; 
#pragma parameter __A0 NewEmptyHandle
pascal Handle NewEmptyHandle(void)
 = 0xA166; 
#pragma parameter __A0 NewEmptyHandleSys
pascal Handle NewEmptyHandleSys(void)
 = 0xA566; 
#pragma parameter HLock(__A0)
pascal void HLock(Handle h)
 = {__GenOSTrapCode(0xA029)};
#pragma parameter HUnlock(__A0)
pascal void HUnlock(Handle h)
 = {__GenOSTrapCode(0xA02A)};
#pragma parameter HPurge(__A0)
pascal void HPurge(Handle h)
 = 0xA049; 
#pragma parameter HNoPurge(__A0)
pascal void HNoPurge(Handle h)
 = 0xA04A; 
#pragma parameter HLockHi(__A0)
pascal void HLockHi(Handle h)
 = {0xA064,0xA029}; 

#ifdef	Supports24Bit
	#if SystemSixOrLater
	#pragma parameter __D0 StripAddress(__D0)
	pascal Ptr StripAddress(void *theAddress)
	 = 0xA055; 
	#else
	pascal Ptr StripAddress(void *theAddress);
	#endif
#else
	#define	StripAddress(x)   (x)
#endif

#pragma parameter __D0 Translate24To32(__D0)
pascal Ptr Translate24To32(void *addr24)
 = 0xA091; 
pascal Handle TempNewHandle(Size logicalSize,OSErr *resultCode)
 = {0x3F3C,0x001D,0xA88F}; 
pascal Size TempMaxMem(Size *grow)
 = {0x3F3C,0x0015,0xA88F}; 
pascal long TempFreeMem(void)
 = {0x3F3C,0x0018,0xA88F}; 
/*  Temporary Memory routines renamed, but obsolete, in System 7.0 and later.  */
pascal void TempHLock(Handle h,OSErr *resultCode)
 = {0x3F3C,0x001E,0xA88F}; 
pascal void TempHUnlock(Handle h,OSErr *resultCode)
 = {0x3F3C,0x001F,0xA88F}; 
pascal void TempDisposeHandle(Handle h,OSErr *resultCode)
 = {0x3F3C,0x0020,0xA88F}; 
pascal Ptr TempTopMem(void)
 = {0x3F3C,0x0016,0xA88F}; 
/*  Temporary Memory routines as they were known before System 7.0.  */
pascal Size MFMaxMem(Size *grow)
 = {0x3F3C,0x0015,0xA88F}; 
pascal long MFFreeMem(void)
 = {0x3F3C,0x0018,0xA88F}; 
pascal Handle MFTempNewHandle(Size logicalSize,OSErr *resultCode)
 = {0x3F3C,0x001D,0xA88F}; 
pascal void MFTempHLock(Handle h,OSErr *resultCode)
 = {0x3F3C,0x001E,0xA88F}; 
pascal void MFTempHUnlock(Handle h,OSErr *resultCode)
 = {0x3F3C,0x001F,0xA88F}; 
pascal void MFTempDisposHandle(Handle h,OSErr *resultCode)
 = {0x3F3C,0x0020,0xA88F}; 
pascal Ptr MFTopMem(void)
 = {0x3F3C,0x0016,0xA88F}; 
pascal void InitApplZone(void)
 = 0xA02C; 
pascal void InitZone(GrowZoneProcPtr pgrowZone,short cmoreMasters,void *limitPtr,
 void *startPtr); 
#pragma parameter SetZone(__A0)
pascal void SetZone(THz hz)
 = 0xA01B; 
#pragma parameter __D0 CompactMem(__D0)
pascal Size CompactMem(Size cbNeeded)
 = 0xA04C; 
#pragma parameter __D0 CompactMemSys(__D0)
pascal Size CompactMemSys(Size cbNeeded)
 = 0xA44C; 
#pragma parameter PurgeMem(__D0)
pascal void PurgeMem(Size cbNeeded)
 = 0xA04D; 
#pragma parameter PurgeMemSys(__D0)
pascal void PurgeMemSys(Size cbNeeded)
 = 0xA44D; 
#pragma parameter __D0 FreeMem
pascal long FreeMem(void)
 = 0xA01C; 
#pragma parameter __D0 FreeMemSys
pascal long FreeMemSys(void)
 = 0xA41C; 
#pragma parameter ResrvMem(__D0)
pascal void ResrvMem(Size cbNeeded)
 = 0xA040; 
#pragma parameter ReserveMem(__D0)
pascal void ReserveMem(Size cbNeeded)
 = 0xA040; 
#pragma parameter ReserveMemSys(__D0)
pascal void ReserveMemSys(Size cbNeeded)
 = 0xA440; 
#pragma parameter __D0 MaxMem(__A1)
pascal Size MaxMem(Size *grow)
 = {0xA11D,0x2288}; 
#pragma parameter __D0 MaxMemSys(__A1)
pascal Size MaxMemSys(Size *grow)
 = {0xA51D,0x2288}; 
#pragma parameter SetGrowZone(__A0)
pascal void SetGrowZone(GrowZoneProcPtr growZone)
 = 0xA04B; 
#pragma parameter SetApplLimit(__A0)
pascal void SetApplLimit(void *zoneLimit)
 = 0xA02D; 
#pragma parameter MoveHHi(__A0)
pascal void MoveHHi(Handle h)
 = 0xA064; 
#pragma parameter DisposPtr(__A0)
pascal void DisposPtr(Ptr p)
 = {__GenOSTrapCode(0xA01F)}; 
#pragma parameter DisposePtr(__A0)
pascal void DisposePtr(Ptr p)
 = {__GenOSTrapCode(0xA01F)}; 
pascal Size GetPtrSize(Ptr p); 
#pragma parameter SetPtrSize(__A0,__D0)
pascal void SetPtrSize(Ptr p,Size newSize)
 = {__GenOSTrapCode(0xA020)}; 
#pragma parameter DisposHandle(__A0)
pascal void DisposHandle(Handle h)
 = {__GenOSTrapCode(0xA023)}; 
#pragma parameter DisposeHandle(__A0)
pascal void DisposeHandle(Handle h)
 = {__GenOSTrapCode(0xA023)}; 
#pragma parameter SetHandleSize(__A0,__D0)
pascal void SetHandleSize(Handle h,Size newSize)
 = 0xA024; 
pascal Size GetHandleSize(Handle h);
#pragma parameter __D0 InlineGetHandleSize(__A0)
pascal Size InlineGetHandleSize(Handle h)
 = 0xA025;
#pragma parameter ReallocHandle(__A0,__D0)
pascal void ReallocHandle(Handle h,Size byteCount)
 = 0xA027; 
#pragma parameter ReallocateHandle(__A0,__D0)
pascal void ReallocateHandle(Handle h,Size byteCount)
 = 0xA027; 
#pragma parameter EmptyHandle(__A0)
pascal void EmptyHandle(Handle h)
 = 0xA02B; 
#pragma parameter HSetRBit(__A0)
pascal void HSetRBit(Handle h)
 = 0xA067; 
#pragma parameter HClrRBit(__A0)
pascal void HClrRBit(Handle h)
 = 0xA068; 
pascal void MoreMasters(void)
 = 0xA036; 
#pragma parameter BlockMove(__A0,__A1,__D0)
pascal void BlockMove(const void *srcPtr,void *destPtr,Size byteCount)
 = {__GenOSTrapCode(0xA02E)}; 
#pragma parameter BlockMoveData(__A0,__A1,__D0)
pascal void BlockMoveData(const void *srcPtr,void *destPtr,Size byteCount)
 = {__GenOSTrapCode(0xA22E)}; 
#define MemError() (* (OSErr*) 0x0220)
pascal void PurgeSpace(long *total,long *contig); 
#pragma parameter __D0 HGetState(__A0)
pascal char HGetState(Handle h)
 = {__GenOSTrapCode(0xA069)}; 
#pragma parameter HSetState(__A0,__D0)
pascal void HSetState(Handle h,char flags)
 = {__GenOSTrapCode(0xA06A)}; 
#pragma parameter SetApplBase(__A0)
pascal void SetApplBase(void *startPtr)
 = 0xA057; 
pascal void MaxApplZone(void)
 = 0xA063; 
#pragma parameter __D0 HoldMemory(__A0,__A1)
pascal OSErr HoldMemory(void *address,unsigned long count)
 = {0x7000,0xA05C}; 
#pragma parameter __D0 UnholdMemory(__A0,__A1)
pascal OSErr UnholdMemory(void *address,unsigned long count)
 = {0x7001,0xA05C}; 
#pragma parameter __D0 LockMemory(__A0,__A1)
pascal OSErr LockMemory(void *address,unsigned long count)
 = {0x7002,0xA05C}; 
#pragma parameter __D0 LockMemoryContiguous(__A0,__A1)
pascal OSErr LockMemoryContiguous(void *address,unsigned long count)
 = {0x7004,0xA05C}; 
#pragma parameter __D0 UnlockMemory(__A0,__A1)
pascal OSErr UnlockMemory(void *address,unsigned long count)
 = {0x7003,0xA05C}; 
pascal OSErr GetPhysical(LogicalToPhysicalTable *addresses,unsigned long *physicalEntryCount); 
#pragma parameter __D0 DeferUserFn(__A0,__D0)
pascal OSErr DeferUserFn(ProcPtr userFunction,void *argument)
 = 0xA08F; 
#pragma parameter __D0 DebuggerGetMax
pascal long DebuggerGetMax(void)
 = {0x7000,0xA08D}; 
pascal void DebuggerEnter(void)
 = {0x7001,0xA08D}; 
pascal void DebuggerExit(void)
 = {0x7002,0xA08D}; 
pascal void DebuggerPoll(void)
 = {0x7003,0xA08D}; 
#pragma parameter __D0 GetPageState(__A0)
pascal PageState GetPageState(const void *address)
 = {0x7004,0xA08D}; 
#pragma parameter __D0 PageFaultFatal
pascal Boolean PageFaultFatal(void)
 = {0x7005,0xA08D}; 
#pragma parameter __D0 DebuggerLockMemory(__A0,__A1)
pascal OSErr DebuggerLockMemory(void *address,unsigned long count)
 = {0x7006,0xA08D}; 
#pragma parameter __D0 DebuggerUnlockMemory(__A0,__A1)
pascal OSErr DebuggerUnlockMemory(void *address,unsigned long count)
 = {0x7007,0xA08D}; 
#pragma parameter __D0 EnterSupervisorMode
pascal StatusRegisterContents EnterSupervisorMode(void)
 = {0x7008,0xA08D}; 
#ifdef __cplusplus
}
#endif

#endif
