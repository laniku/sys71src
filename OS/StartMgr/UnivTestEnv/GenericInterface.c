/*
				File:		GenericInterface.c
			
				Contains:	These functions implement a generic interface between an
							'application' and the Common Test Environment Kernel.
							Tests and Subtests written to run under the Common Test
							Environment are completely insulated from the generic
							interface and should not be affected by changes to it.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).
		 <1>	 12/14/90	SS		first checked in
 		   
 */
//
//	GenericInterface.c
//
//	These functions implement a generic interface between an 'application' and
//	the Common Test Environment Kernel.  Tests and Subtests written to
//	run under the Common Test Environment are completely insulated from the 
//	generic interface and should not be affected by changes to it.
//

#include "CTETypes.h"
#include "GenericInterface.h"
#include "Heap.h"
#include "OtherSupport.h"


//
//	GI_InitInterface() - Initialize the CTE Generic Interface.
//
int GI_InitInterface(CTEGlobals *globs, long size)
{
	int err = noError ;
	
	InitHeap(globs, (void *)globs, size) ;
	if(NULL == AllocPermMem(globs, sizeof(CTEGlobals)))
	{
		err = CTE_Kernel_Err_CantAllocGlobals ;
		goto ErrorExit ;
	}
		
	// Initialize the version
	//	byte - first part of version number in BCD.
	//	byte - second and third parts of version number.
	//	byte - development=0x20, alpha=0x40, beta=0x60, release=0x80.
	//	byte - stage of pre-release version.
	*(ULONG *)&globs->version = kCTEversion ;
 
	// Initialize the support function jump table.
	globs->jumpTable.doSubtest = ExecuteSubtest ;
	globs->jumpTable.idle = CTEDoIdle ;
	globs->jumpTable.bitWalk8 = BitWalk8 ;
	globs->jumpTable.bitWalk16 = BitWalk16 ;
	globs->jumpTable.bitWalk32 = BitWalk32 ;
	globs->jumpTable.installExceptionHandler = InstallExceptionHandler ;
	globs->jumpTable.removeExceptionHandler = RemoveExceptionHandler ;
	globs->jumpTable.fakeExceptionCall = FakeExceptionCall ;
	globs->jumpTable.setInterruptLevel = SetInterruptLevel ;
	globs->jumpTable.getInterruptLevel = GetInterruptLevel ;
	globs->jumpTable.installExceptionVector = InstallExceptionVector ;
	globs->jumpTable.allocPermMem = AllocPermMem ;
	globs->jumpTable.allocTempMem = AllocTempMem ;
	
	
	globs->commentary = "v2.1 Rules! Long Live M. Appleman, S. Williams, A. Ludtke" ;
	
ErrorExit :
	return(err) ;
}


//
// GI_ExecuteDTM() - Execute a DTM.
//
int GI_ExecuteDTM(CTEInfo *kernelInfo, 
		CTEDTMExecutionOptions *execOpts,
		CTETestInfo *testInfo, 
		CTESubtestInfo *subtestInfo, 
		CTEDTMExecutionResults *execResults)
{
	return(ExecuteDTM(kernelInfo, execOpts, testInfo, subtestInfo, execResults)) ;
}



//
// GI_GetVersion() - Get the CTE Kernel version number.
//
NumVersion *GI_GetVersion(CTEGlobals *globs)
{
	return(&globs->version) ;
}

//
// GI_AllocPermMem() - Allocate a block of memory from the CTE Kernel's internal
//	permanent memory heap.  This block cannot be deallocated without reinitializing
//	the CTE Kernel.
//
void *GI_AllocPermMem(CTEGlobals *globs, int size)
{
	return(AllocPermMem(globs, size)) ;
}


//
// GI_AllocTempMem() - Allocate a block of memory from the CTE Kernel's internal
//	temporary memory heap.  All of the CTE Kernel's Temporary heap is deallocated 
//	with GI_FreeTempMem.  It is also all deallocated by calling GI_ExecuteTest
//	right befor the next test executes.
//
void *GI_AllocTempMem(CTEGlobals *globs, int size)
{
	return(AllocTempMem(globs, size)) ;
}


//
// GI_FreeTempMem() - Deallocate all of the CTE Kernel's temporary memory.
//	Remember that this is also done implicitly before each Test is
//	executed (by calling GI_ExecuteTest()).
//
void GI_FreeTempMem(CTEGlobals *globs)
{
	FreeTempMem(globs) ;
}


//
// GI_GetCommentary()
//
char *GI_GetCommentary(CTEGlobals *globs)
{
	return(globs->commentary) ;
}


//
// GI_UseDefaultExecutionOptions()
//
CTEDTMExecutionOptions GI_GetDefaultExecutionOptions(void)
{
	CTEDTMExecutionOptions execOptions ;
	
	execOptions.processorType = kCTEProcessorType68000 ;
	execOptions.executionMode = normalMode ;
	execOptions.testParams = NULL ;
	execOptions.testResultsOverride = NULL ;
	execOptions.subtestParamsOverride = NULL ;
	execOptions.subtestResultsOverride = NULL ;
	execOptions.idleMethod = NULL ;
	execOptions.idleMethodArg = NULL ;
	execOptions.userInfo = NULL ;
	
	return(execOptions) ;
}