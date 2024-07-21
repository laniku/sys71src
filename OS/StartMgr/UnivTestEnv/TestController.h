/*
				File:		TestController.h
			
				Contains:	This is the include file for the test controller section
							of the Common Test Environment.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
		 <1>	  9/4/90	SS		first checked in

		 		To Do:
*/
#ifndef _TestController_
#define _TestController_

#include "CTETypes.h"
#include "List.h"
#include "Heap.h"
#include "SubtestController.h"

struct TestNode
{
	Node node ;
	Test *testPtr ;
	int testSize ;
	char *name ;
} ;
#ifndef __cplusplus
typedef struct TestNode TestNode ;
#endif __cplusplus

#ifdef __cplusplus
extern "C" {
#endif __cplusplus

extern TestNode *InstallTest(CTEGlobals *globs, TestID id, Test *theTest, int codeSize, char *name) ;
extern TestNode *FindTest(CTEGlobals *globs, TestID id) ;
extern TestErr DoTest(CTEGlobals *globs, TestID testID, SubtestID subtestID,
		ULONG modifier, ExecMode execMode) ;

#ifdef __cplusplus
}	// close the extern "C" declaration
#endif __cplusplus

#endif _TestController_
