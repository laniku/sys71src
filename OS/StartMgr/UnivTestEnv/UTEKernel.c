/*
				File:		UTEKernel.c
			
				Contains:	This file simply includes all the sources for the Universal
							Test Environment routines.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Removed the List.c, SubtestController.c and TestController.c
									#include statements because they were no longer needed for the
									old CTE (pre - 2.1) and are therefore no longer needed for
									Horror. Also, added the #include for OtherSupport.c because it
									is needed for CTE v2.1.
		 <2>	 8/31/90	SS		Filled in header information
		 <1>	 8/31/90	SS		first checked in
			
				To Do:
			*/

#include	"BitWalk.c"
#include	"ExceptionSupport.c"
#include	"ExecuteDTM.c"
#include	"GenericInterface.c"
#include	"Heap.c"
#include	"OtherSupport.c"