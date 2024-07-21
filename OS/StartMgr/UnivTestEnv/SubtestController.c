/*
				File:		SubtestController.c
			
				Contains:	This file contains the subtest controller functions
							of the Common Test Environment, which control locating
							and executing subtests.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
		 <1>	  9/4/90	SS		first checked in

		 		To Do:
*/

#include "SubtestController.h"

SubtestNode *FindSubtest(CTEGlobals *globs, SubtestID id)
{
		return((SubtestNode *)FindKeyedNode(&globs->subtestList, id)) ;
}


SubtestErr DoSubtest(CTEGlobals *globs)
{
		SubtestNode *theSubtestNode ;
		Subtest *theSubtest ;
		SubtestErr err ;
		
		// Find the subtest node in the subtest list.
		if(NULL == (theSubtestNode = FindSubtest(globs, globs->subtestID)))
		{
				err = CTE_Kernel_Err_SubtestNotAvailable ;
				goto ErrorExit ;
		}
		
		theSubtest = theSubtestNode->subtestPtr ;
				
DoAgain :
		switch(globs->execMode)
		{
		case dontExecSubtestMode :
				err = CTE_Kernel_Err_SubtestNotExecuted ;
				break ;
		
		case normalMode :
				err = (*theSubtest)(globs, globs->subtestParams, globs->subtestResults) ;
				break ;
		
		default :
				err = CTE_Kernel_Err_UnknownExecMode ;
		}

ErrorExit :
		return(err) ;
}

