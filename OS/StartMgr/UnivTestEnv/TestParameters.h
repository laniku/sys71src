/*
 	File:	TestParameters.h
 
 	Written by:	Mark Appleman 
 
 	Copyright:	© 1991-1992 by Apple Computer, Inc., all rights reserved.
 
 	Change History (most recent first):
 
		 <1>	 5/16/92	kc		first checked in
		 <1>	  3/6/92	AL		first checked in
 		   
 */
#ifndef _TestParameters_
#define _TestParameters_
//
//	TestParameters.h
//

#include <GenericTypes.h>
#include <CTETypes.h>

typedef LONG CTEMachineType ;

typedef struct StdTestParams
{
	ULONG modifier ;
	CTEMachineType machineType ;
} StdTestParams ;

extern struct FormatItem Standard_Test_Params_Format[] ;

#endif _TestParameters_

