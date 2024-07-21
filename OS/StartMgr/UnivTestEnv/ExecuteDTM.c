/*
 	File:	ExecuteDTM.c
 
 	Written by:	Mark Appleman 
 
 	Copyright:	й 1991-1992 by Apple Computer, Inc., all rights reserved.
 
 	Change History (most recent first):
 
		 <1>	 5/16/92	kc		first checked in
		 <1>	  3/6/92	AL		first checked in
                    <1>  10/15/91     SW   First checked in for CTE 2.1
 		   
 */
//
//	'ExecuteDTM.c'
//

#include "GenericInterface.h"
#include "Heap.h"

static void *AllocateBlock(CTEInfo *kernelInfo, void *blockPtr, ULONG blockSize) ;


//
// ExecuteDTM()
//
long ExecuteDTM(CTEInfo *kernelInfo, 
		CTEDTMExecutionOptions *executionOptions,
		CTETestInfo *testInfo, 
		CTESubtestInfo *subtestInfo, 
		CTEDTMExecutionResults *executionResults)
{
	long err ;
	
	// Free all temp heap storage.
	FreeTempMem(kernelInfo) ;
	
	kernelInfo->processorType = executionOptions->processorType ;
	
	// Record the location of the 
	//	CTEDTMExecutionInfo, CTETestInfo, and CTESubtestInfo structures
	//	in the CTE globals.
	kernelInfo->executionOptions = executionOptions ;
	kernelInfo->testInfo = testInfo ;
	kernelInfo->subtestInfo = subtestInfo ;
	kernelInfo->executionResults = executionResults ;
	
	executionResults->testParams = executionOptions->testParams ;
	
	// Allocate and clear storage for the Test results
	if(NULL == (executionResults->testResults = 
		AllocateBlock(kernelInfo, executionOptions->testResultsOverride, testInfo->resultsSize)))
	{
		err = CTE_Kernel_Err_CantAllocParamBlock ;
		goto ErrorExit ;
	}
	
	// Allocate and clear storage for the subtest parameters.
	if(NULL == (executionResults->subtestParams = 
			AllocateBlock(kernelInfo, executionOptions->subtestParamsOverride, subtestInfo->paramsSize)))
	{
		err = CTE_Kernel_Err_CantAllocParamBlock ;
		goto ErrorExit ;
	}

	// Allocate and clear storage for the subtest results.
	if(NULL == (executionResults->subtestResults =  
			AllocateBlock(kernelInfo, executionOptions->subtestResultsOverride, subtestInfo->resultsSize)))
	{
		err = CTE_Kernel_Err_CantAllocResultBlock ;
		goto ErrorExit ;
	}
		
	switch(executionOptions->executionMode)
	{
	case normalMode :
	case dontExecSubtestMode :
		err = (*testInfo->functionEntry)
				(kernelInfo, 
				executionResults->testParams, 
				executionResults->testResults,
				executionResults->subtestParams, 
				subtestInfo->id) ;
		break ;
		
	case dontExecTestMode :
		err = CTE_Kernel_Err_TestNotExecuted ;
		break ;
	
	default :
		err = CTE_Kernel_Err_UnknownExecMode ;
		break ;
	}

ErrorExit :
	return(executionResults->err = err) ;
}


//
// AllocateBlock()
//	Returns the address of a block of memory the size of blockSize.  
//	If blockPtr is NULL the block is allocated from CTE temporary memory.
//		
//	Otherwise, the block is assumed to have allready been allocated by
//		someone else.  In this case, the block is just cleared to zero.
static void *AllocateBlock(CTEInfo *kernelInfo, void *blockPtr, ULONG blockSize)
{
	void *returnPtr ;

	// If the location of the block is not NULL...
	if(blockPtr)
	{
		// Then, the shell has allocated space for the block.
		//	Just clear it to zero.
		// ееее TO DO: write a optimized memset() function to do this...(a future support function?).
		UBYTE *bufPtr = blockPtr ;
		ULONG byteCount = blockSize ;
		while(byteCount > 0)
		{
			*bufPtr++ = 0 ;
			byteCount-- ;
		}
		returnPtr = blockPtr ;
		
	}else{
		// Else, the Kernel needs to allocate space for the block. 
		//	Allocate it from CTE temporary memory.  
		//	Note that temporary memory is allready initialized to zero.
		returnPtr = AllocTempMem(kernelInfo, blockSize) ;
	}
	
	return(returnPtr) ;
}


//
// ExecuteSubtest()
//
SubtestErr ExecuteSubtest(CTEInfo *kernelInfo)
{
	SubtestErr err ;	
		
DoAgain :
	switch(kernelInfo->executionOptions->executionMode)
	{
	case dontExecSubtestMode :
		err = CTE_Kernel_Err_SubtestNotExecuted ;
		break ;
	
	case normalMode :
		err = (*(kernelInfo->subtestInfo->functionEntry))
				(kernelInfo, 
				kernelInfo->executionResults->subtestParams, 
				kernelInfo->executionResults->subtestResults) ;
		break ;
	
	default :
		err = CTE_Kernel_Err_UnknownExecMode ;
	}

ErrorExit :
	return(err) ;
}

