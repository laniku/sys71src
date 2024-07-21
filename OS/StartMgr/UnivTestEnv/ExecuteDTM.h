/*
 	File:	ExecuteDTM.h
 
 	Written by:	Mark Appleman 
 
 	Copyright:	© 1991-1992 by Apple Computer, Inc., all rights reserved.
 
 	Change History (most recent first):
 
		 <1>	 5/16/92	kc		first checked in
		 <1>	  3/6/92	AL		first checked in
 		   
 */
#ifndef _ExecuteDTM_
#define _ExecuteDTM_
//
//	'ExecuteDTM.h'
//

LONG ExecuteDTM(CTEInfo *kernelInfo, 
		CTEDTMExecutionOptions *executionOptions,
		CTETestInfo *testInfo, 
		CTESubtestInfo *subtestInfo, 
		CTEDTMExecutionResults *executionResults) ;
SubtestErr ExecuteSubtest(CTEInfo *kernelInfo) ;

#endif _ExecuteDTM_