/*
	File:		TrapsPrivate.h

	Contains:	Private System traps, not for public consumption.

	Written by:	Jim Reekes

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM6>	11/10/93	fau		Fixed the includes so we can build.
	   <SM5>	 9/12/93	pdw		Removing EnqueueHead.
	   <SM4>	 9/12/93	pdw		Added EnqueueHead.
	   <SM3>	  9/9/93	pdw		Added Time Manager (Microseconds), PRAM and Nanokernel sections.
		 <2>	 6/14/93	JDR		Moved Get/SetTrapWordAddress into TrapsPrivate.h
		 <1>	 7/22/92	JDR		first checked in


	Notes:		This file contains the traps allocated by the System, but
				are not for use by the public and therefore not for use
				by developers.  At the time of this writing (the first
				check in) all of the private traps are scattered throughout
				the source files.  The hope in creating this file is that
				all of these private traps will be collected into this file.
				If you add a new trap, keep this file in trap number order
				just like the public Traps.h.  Also, it would be helpful
				if you add a comment about what the trap is used for.
*/


#ifndef __TRAPSPRIVATE__
#define __TRAPSPRIVATE__

#ifndef __TRAPS__
	#include <Traps.h>
#endif

#ifndef __OSUTILS__
	#include <OSUtils.h>
#endif

//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
// Trap Dispatcher

#define _GetTrapWordAddress 0xA546		// used by the Link Patch Loader
#define _SetTrapWordAddress 0xA447		// used by the Link Patch Loader


//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
// Memory Manager traps

#define _MoveHLow 0xA09D


//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
// Sound Manager traps

// SndAppDead is called by InitApplZone which vectors to jIAZInit, which then
// vectors to jSoundDead.  This is done by the ROMs on Apple Sound Chip machines,
// for some reason that has been lost in history (probably due to the pre-MultiFinder
// assumptions).  It is also called by CleanupApplication.  So we've got them
// coming and going, but we really only want this trap to be called once a
// process is going away.

#define _SndAppDead 0xA0B8


//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
// Process Manager traps

#define _InitApplication	0xAAFA
#define _CleanupApplication	0xAAFB
#define _SynchIdleTime		0xABF7


//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
// Time Manager traps

#define _Microseconds	0xA193

#ifdef __cplusplus
extern "C" {
#endif

unsigned long			Microseconds(void)	= {_Microseconds}; 

#ifdef __cplusplus
}
#endif



//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
// PRAM manipulations

#ifdef __cplusplus
extern "C" {
#endif

#pragma parameter __D0	ReadXPRam(		__D0, 			__D1, 			__A0)
OSErr					ReadXPRam(short numBytes, short whichByte, void *dest)	= {0x4840, 0x3001, _ReadXPRam}; 
/*	0x4840		swap	d0   		*/
/*	0x3001		move.w	d1,d0		*/
/*				_ReadXPRam			*/

#pragma parameter __D0	WriteXPRam(		__D0, 			__D1, 			__A0)
OSErr					WriteXPRam(short numBytes, short whichByte, void *src)	= {0x4840, 0x3001, _WriteXPRam}; 
/*	0x4840		swap	d0   		*/
/*	0x3001		move.w	d1,d0		*/
/*				_WriteXPRam			*/

#ifdef __cplusplus
}
#endif



//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
// NanoKernel traps
// The dispatch selectors to the PowerPC nano-Kernel

#define  _KernelVMDispatch		0xFE0A		// NanoKernel VMDispatch d0/a0/a1/d1 <- params, d0 <- result
#define  _ToolBoxCoprocessorNop	0xFC00		// NOP if Toolbox Coprocessor Exists, else F-Trap

//	Accelerations of the SANE Floating Point Package

#define  _DecodeSANEop			0xFC01
#define  _ExitSANEop			0xFC02
#define  _LoadArg1Extended		0xFC03
#define  _LoadArg2Convert		0xFC04
#define  _CopyArg2ToArg1		0xFC05
#define  _CheckResultArg1		0xFC06
#define  _StoreArg1Extended		0xFC07
#define  _StoreArg1Double		0xFC08
#define  _StoreArg1Single		0xFC09
#define  _FloatAdd				0xFC0A
#define  _FloatSub				0xFC0B
#define  _FloatMul				0xFC0C
#define  _FloatDiv				0xFC0D
#define  _FloatRem				0xFC0E
#define  _FloatSqrt				0xFC0F


//	Accelerations of the return/exit path of the OS A-Trap dispatcher.

#define  _ATrapOSExit			0xFC10		// accelerated return path of normal OS A-trap
#define  _ATrapOSNoA0Exit		0xFC11		// accelerated return path of No A0 OS A-trap


//	Accelerations for BlockMove.

#define  _MoveBytes				0xFC12		// accelerate BlockMove, use DCBZ for writes
#define  _MoveBytesNoDCBZ		0xFC13		// accelerate BlockMove, don't use DCBZ instruction

#define  _RiscCoprocessorNop	0xFE00		// NOP if RISC Coprocessor Exists, else F-Trap
#define  _ExecuteRiscContext	0xFE03		// (a7) points to NativeContextBlock

//	Move From/To Emulator Control Register (ECR)

#define  _MoveFromECR			0xFE04		// d0 <- Register Number, A0 <- Register Value
#define  _MoveToECR				0xFE05		// d0 <- Register Number, A0 <- Register Value

#define  _VMDispatch			0xFE0A		// d0/a0/a1/d1 <- params, d0 <- result
#define  _HandleMixedModeFault	0xFE07		// Handle Mixed Mode Interrupts and Page Faults
#define  _ReadTimeBase32		0xFE08		// d0 <- lower 32 bits of 64 bit time base
#define  _ReadTimeBase64		0xFE09		// a0 <- upper 32 bits, d0 <- lower 32 bits
#define  _MixedMode				0xFEED		// Suspend Emulation, Call Mixed Mode Switcher


//	KernelVMDispatch Routine Selectors

enum {
	mmuInit								= 0,		// selector for mmuInit
	mmuUnInit							= 1,		// selector for mmuUnInit
	mmuFinalInit						= 2,		// selector for mmuFinalInit
	
	mmuIsResident						= 3,		// selector for mmuIsResident
	mmuIsUnmodified						= 4,		// selector for mmuIsUnmodified
	mmuIsInited							= 5,		// selector for mmuIsInited
	mmuShouldClean						= 6,		// selector for mmuShouldClean
	mmuMarkResident						= 7,		// selector for mmuMarkResident
	mmuMarkBacking						= 8,		// selector for mmuMarkBacking
	mmuMarkCleanUnused					= 9,		// selector for mmuMarkCleanUnused
	mmuGetPhysicalPage					= 10,		// selector for mmuGetPhysicalPage
	mmuGetPhysicalAddress				= 11,		// selector for mmuGetPhysicalAddress
	
	mmuExchangePages					= 12,		// selector for mmuExchangePages
	mmuReload							= 13,		// selector for mmuReload
	mmuFlushAddressTranslationCache		= 14,		// selector for mmuFlushAddressTranslationCache
	mmuFlushDataCache					= 15,		// selector for mmuFlushDataCache
	mmuFlushCodeCache					= 16,		// selector for mmuFlushCodeCache
	mmuMakePageCacheable				= 17,		// selector for mmuMakePageCacheable
	mmuMakePageNonCacheable				= 18,		// selector for mmuMakePageNonCacheable
	
	getPTEntryGivenPage					= 19,		// selector for _GetPTEntryGivenPage
	setPTEntryGivenPage					= 20,		// selector for _SetPTEntryGivenPage
	
	mmuPTest							= 21,		// selector for mmuPTest
	mmuLRU								= 22,
	mmuMarkUndefined					= 23,
	mmuMakePageWriteThrough				= 24,
	mmuAllocateMemory					= 25		// (Page:A0, Count:A1, BusAlignMask:D1)
};

//__________________________________________

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ulong
#define ulong	unsigned long
#endif

#pragma parameter __D0	nkAllocateMemory( __A0, __A1, __D1)
unsigned long			nkAllocateMemory( Ptr, ulong, ulong)	= { 0x7000+mmuAllocateMemory, _VMDispatch};

#pragma parameter __D0	nkMakePageCacheable( __A0)
unsigned long			nkMakePageCacheable( Ptr)		= { 0x7000+mmuMakePageCacheable, _VMDispatch};

#pragma parameter __D0	nkMakePageNonCacheable( __A0)
unsigned long			nkMakePageNonCacheable( Ptr)	= { 0x7000+mmuMakePageNonCacheable, _VMDispatch};

#pragma parameter __D0	nkMakePageWriteThrough( __A0)
unsigned long			nkMakePageWriteThrough( Ptr)	= { 0x7000+mmuMakePageWriteThrough, _VMDispatch};



#ifdef __cplusplus
}
#endif

//____________________________________________________________________________________________


#endif	// already included...