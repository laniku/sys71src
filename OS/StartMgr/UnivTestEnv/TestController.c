/*
				File:		TestController.c
			
				Contains:	This file contains the test controller functions for the
							Common Test Environment.  These functions let the caller
							locate and execute a test.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
		 <1>	  9/4/90	SS		first checked in

		 		To Do:
*/

#include "TestController.h"
#include <Stdio.h>

TestNode *FindTest(CTEGlobals *globs, TestID id)
{
		return((TestNode *)FindKeyedNode(&globs->testList, id)) ;
}


TestErr DoTest(CTEGlobals *globs, TestID testID, SubtestID subtestID,
				ULONG modifier, ExecMode execMode)
{
		TestNode *theTestNode = NULL ;
		SubtestNode *theSubtestNode = NULL ;
		void *subtestParams = NULL ;
		int subtestParamsSize = 0 ;
		void *subtestResults = NULL ;
		int subtestResultsSize = 0 ;
		TestErr err ;
		
		// Free all temp heap storage.
		FreeTempMem(globs) ;
		
		// Find the test node in the test list.
		if(NULL == (theTestNode = FindTest(globs, testID)))
		{
				err = CTE_Kernel_Err_TestNotAvailable ;
				goto ErrorExit ;
		}
		
		// Save some of the info from the Test node in the CTE globals.
		globs->testID = testID ;
		globs->modifier = modifier ;
		globs->execMode = execMode ;
		
		// Find the subtest node in the subtest list.
		if(NULL == (theSubtestNode = FindSubtest(globs, subtestID)))
		{
				err = CTE_Kernel_Err_SubtestNotAvailable ;
				goto ErrorExit ;
		}
		
		// Allocate and clear storage for the subtest parameters.
		subtestParamsSize = theSubtestNode->pbSize ;
		if(NULL == (subtestParams = AllocTempMem(globs, subtestParamsSize)))
		{
				err = CTE_Kernel_Err_CantAllocParamBlock ;
				goto ErrorExit ;
		}
		
		// Allocate and clear storage for the subtest results.
		subtestResultsSize = theSubtestNode->rbSize ;
		if(NULL == (subtestResults = AllocTempMem(globs, subtestResultsSize)))
		{
				err = CTE_Kernel_Err_CantAllocResultBlock ;
				goto ErrorExit ;
		}
				
		// Save some of the info from the Subtest node in the CTE globals.
		globs->subtestID = subtestID ;
		globs->subtestParams = subtestParams ;
		globs->subtestParamsSize = subtestParamsSize ;
		globs->subtestResults = subtestResults ;
		globs->subtestResultsSize = subtestResultsSize ;
		
		switch(globs->execMode)
		{
		case normalMode :
		case dontExecSubtestMode :
				err = (*theTestNode->testPtr)(globs, globs->subtestParams, globs->modifier, globs->subtestID) ;
				break ;
				
		case dontExecTestMode :
				err = CTE_Kernel_Err_TestNotExecuted ;
				break ;
		
		default :
				err = CTE_Kernel_Err_UnknownExecMode ;
				break ;
		}

ErrorExit :
		return(err) ;
}


