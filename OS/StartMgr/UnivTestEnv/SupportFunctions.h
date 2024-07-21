/*
	File:		SupportFunctions.h
	
	Contains:	CTE supprt functions equates.
	
	Copyright:	© 1991-1992 by Apple Computer, Inc., all rights reserved.
	
	Change History (most recent first):
	
	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).
 		   
 */
#ifndef _SupportFunctions_
#define _SupportFunctions_
//
//	SupportFunctions.h
//

#include <CTETypes.h>
#include <ExecuteDTM.h>
#include <ExceptionSupport.h>
#include <BitWalk.h>
#include <Heap.h>
#include <OtherSupport.h>

// Internal Common Test Environment Functions.
#define SUP_DoSubtest(info)	(info->jumpTable.doSubtest(info))

// Walking Bit Test Functions.
#define SUP_BitWalk8(info, p, r) \
				(info->jumpTable.bitWalk8(info, p, r))
#define SUP_BitWalk16(info, p, r) \
				(info->jumpTable.bitWalk16(info, p, r))
#define SUP_BitWalk32(info, p, r) \
				(info->jumpTable.bitWalk32(info, p, r))

// Exception Support Functions.
#define SUP_InstallExceptionHandler(info, excInfo, handler, arg, vec) \
				(info->jumpTable.installExceptionHandler \
						(info, excInfo, handler, arg, vec))
#define SUP_RemoveExceptionHandler(info, excInfo) \
				(info->jumpTable.removeExceptionHandler(info, excInfo))
#define SUP_FakeExceptionCall(info, vec) \
				(info->jumpTable.fakeExceptionCall(vec))
#define SUP_SetInterruptLevel(info, lev) \
				(info->jumpTable.setInterruptLevel(lev))
#define SUP_GetInterruptLevel(info) \
				(info->jumpTable.getInterruptLevel())
#define SUP_InstallExceptionVector(info, handler, vecNum) \
				(info->jumpTable.installExceptionVector(handler, vecNum))

// Memory Allocation Functions
#define SUP_AllocPermMem(info, size) \
				(info->jumpTable.allocPermMem(info, size))
#define SUP_AllocTempMem(info, size) \
				(info->jumpTable.allocTempMem(info, size))

// Others...
#define SUP_GetProcessorType(info) \
				(info->processorType)
#define SUP_GetSubtestParameters(info) \
				(info->executionResults->subtestParams)
#define SUP_GetSubtestResults(info) \
				(info->executionResults->subtestResults)
#define SUP_GetTestParameters(info) \
				(info->executionResults->testParams)
#define SUP_GetTestResults(info) \
				(info->executionResults->testResults)

#define SUP_Idle(info)		(info->jumpTable.idle(info))

#endif
