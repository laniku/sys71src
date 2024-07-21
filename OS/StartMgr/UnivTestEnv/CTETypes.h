/*
				File:		CTETypes.h
			
				Contains:	This file contains definitions for data types used in
							the Common Test Environment.
			
				Written by:	Mark Appleman
			
				Copyright:	й 1990, 1992 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).
		 <1>	 12/14/90	SS		first checked in
 		   
 */
#ifndef _CTETypes_
#define _CTETypes_
//
//	CTETypes.h
//

#include "GenericTypes.h"
#include "BitWalk.h"
#include "ExceptionSupport.h"
#include <Files.h>

// CTE release version --- 2.1 release
//	byte - first part of version number in BCD.
//	byte - second and third parts of version number.
//	byte - development=0x20, alpha=0x40, beta=0x60, release=0x80.
//	byte - stage of pre-release version.
#define kCTEversion 0x02108000 ;

typedef ULONG SubtestID ;
typedef ULONG TestID ;

typedef LONG CTEError ;
typedef CTEError SubtestErr ;
typedef CTEError TestErr ;


//
// Processor Type.
//
typedef enum CTEProcessorType
{
	kCTEProcessorType68000 = 1,
	kCTEProcessorType68010 = 2,
	kCTEProcessorType68020 = 3,
	kCTEProcessorType68030 = 4,
	kCTEProcessorType68040 = 5,
	cteProcessorTypePad = 0x7fffffff
} CTEProcessorType ;


//
// DTM execution modes supported by the CTE Kernel.
//
typedef enum CTEExecutionMode
{
	normalMode = 0,
	dontExecSubtestMode,
	dontExecTestMode,
	cteExecModePad = 0x7fffffff
} CTEExecutionMode ;

typedef CTEExecutionMode ExecMode ;	// Obsolete, stop using. Use CTEExecutionMode instead!


//
// Error codes retured by the CTE Kernel.
//
typedef enum CTEKernelErrorCodes
{
	noError = 0,
	CTE_Kernel_Err_NoError = 0,
	CTE_Kernel_Err_UnknownExecMode = -1,
	CTE_Kernel_Err_SubtestNotExecuted = -2,
	CTE_Kernel_Err_TestNotExecuted = -3,
	CTE_Kernel_Err_TestNotAvailable = -4,
	CTE_Kernel_Err_SubtestNotAvailable = -5,
	CTE_Kernel_Err_CantAllocGlobals = -6,
	CTE_Kernel_Err_CantAllocTestNode = -7,
	CTE_Kernel_Err_CantAllocSubtestNode = -8,
	CTE_Kernel_Err_CantAllocParamBlock = -9,
	CTE_Kernel_Err_CantAllocResultBlock = -10,
	CTE_Kernel_Err_UnknownRequest = -11,
	CTE_Kernel_Err_RequestFailed = -12,
	CTE_Kernel_Err_DontKnowSubtest = -13,
	CTE_Kernel_Err_InvalidModifier = -14
} CTEKernelErrorCodes ;


//
// The jump table used for accessing the CTE Kernel's Support Functions.
//	It is initialized in GI_InitInterface().
//
typedef struct CTEJumpTable
{
	// Internal Common Test Environment Functions.
	SubtestErr (*doSubtest)(struct CTEGlobals *globs) ;
	
	void (*idle)(struct CTEGlobals *globs) ;
	
	// ееее Obsolete and unused.
	void *unused1 ;
	void *unused2 ;
	
	// Walking Bit Test Functions.
	UBYTE (*bitWalk8)(struct CTEGlobals *globs, BitWalk8_PB *params, BitWalk8_RB *results) ;
	UWORD (*bitWalk16)(struct CTEGlobals *globs, BitWalk16_PB *params, BitWalk16_RB *results) ;
	ULONG (*bitWalk32)(struct CTEGlobals *globs, BitWalk32_PB *params, BitWalk32_RB *results) ;
	
	// Exception Support Functions.
	void (*installExceptionHandler)(struct CTEGlobals *globs, ExceptionInfo *exceptionInfo, ExceptionHandler *handler, void *argPtr, int vectorNumber) ;
	void (*removeExceptionHandler)(struct CTEGlobals *globs, ExceptionInfo *exceptionInfo) ;
	void (*fakeExceptionCall)(int vectorNumber) ;
	int (*setInterruptLevel)(int newLevel) ;
	int (*getInterruptLevel)(void) ;
	void *(*installExceptionVector)(void *newHandler, int vectorNumber) ;
	void *(*allocPermMem)(struct CTEGlobals *globs, int size) ;
	void *(*allocTempMem)(struct CTEGlobals *globs, int size) ;

} CTEJumpTable ;


typedef SubtestErr Subtest(struct CTEGlobals *info, void *subtestParams, void *subtestResults) ;
typedef TestErr Test(struct CTEGlobals *info, void *subtestParams, ULONG modifier, SubtestID subtestID) ;
typedef TestErr Test2(struct CTEGlobals *info, void *testParams, 
				void *testResults, void *subtestParams, SubtestID subtestID) ;

typedef struct CTESubtestInfo
{
	void *userInfo ;
	SubtestID id ;
	Subtest *functionEntry ;
	long paramsSize ;
	long resultsSize ;
} CTESubtestInfo ;

typedef struct CTETestInfo
{
	void *userInfo ;
	TestID id ;
	Test2 *functionEntry ;
	long paramsSize ;
	long resultsSize ;
} CTETestInfo ;

typedef struct CTEDTMExecutionOptions
{
	void *userInfo ;
	CTEProcessorType processorType ;
	CTEExecutionMode executionMode ;
	void *testParams ;
	void *testResultsOverride ;
	void *subtestParamsOverride ;
	void *subtestResultsOverride ;
	void (*idleMethod)(void *idleMethodArg) ;
	void *idleMethodArg ;
} CTEDTMExecutionOptions ; 

typedef struct CTEDTMExecutionResults
{
	CTEError err ;
	void *testParams ;
	void *testResults ;
	void *subtestParams ;
	void *subtestResults ;
} CTEDTMExecutionResults ;



//
// The CTE globals.
//	Yes you guessed it, a pointer to a CTEInfo type points to the CTE Kernel's
//	globals, but NEVER, EVER dereference it to access the Kernel's globals 
//	directly because it is subject to change without notice!  You have been
//	warned!
//
struct CTEGlobals
{
	NumVersion version ;	// the version number of the CTE Kernel.
	CTEProcessorType processorType ;
	CTEDTMExecutionOptions *executionOptions ;
	CTETestInfo *testInfo ;
	CTESubtestInfo *subtestInfo ;
	CTEDTMExecutionResults *executionResults ;
	void *heapBottom ;	// points to the lowest address in the heap.
	void *heapTop ;		// points to the highest address in the heap + 1.
	long heapSize ;		// the size of the heap in bytes.
	void *heapPermPtr ;	// points to the next available byte in perm. heap storage.
				//	Perm. heap storage grows from heapBottom towards heapTop.
	void *heapTempPtr ;	// points to the next available byte + 1 in temp. heap storage.
				//	Temp. heap storage grows from heapTop towards heapBottom.
	CTEJumpTable jumpTable ; // the Support Function jump table.
	ExceptionInfo *exceptionInfoPtrTable[256] ; // the Exception Info pointer table.
	char *commentary ;	// points to a hopefully relavent message.
} ;
typedef struct CTEGlobals CTEGlobals ;
typedef struct CTEGlobals CTEInfo ;


#endif _CTETypes_