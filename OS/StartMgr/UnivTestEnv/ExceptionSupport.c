/*
				File:		ExceptionSupport.c
			
				Contains:	This file is the ExceptionSupport source file.  It contains
							the routines which are used by subtests running
							in the CTE environment.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).
		 <1>	 12/14/90	SS		first checked in
 		   
 */
//
//	ExceptionSupport.c
//

#include "CTETypes.h"
#include "ExceptionSupport.h"
#include "GenericInterface.h"
#include "68KOpCodes.h"

#define	jsrOpCode	(UWORD)0x4eb9

//
// CPUSHStubVector()
//
//	NOTE: This #pragma had to be redeclared under the old MPW C syntax, without the
//		__ for A0. The Horror ROM uses MPW 3.0 tools (not 3.2), so this needs
//		to be changed back if the ROM starts using 3.2 final (or later).
//
//		AARON	AARON	AARON
//
//#pragma parameter CPUSHStubVector(__A0)
static void CPUSHStubVector(void *lineAddress) = 
{
	0xF4E8,	// CPUSHL <BothCaches>,(a0) 
	0x5488, // ADDQ #2, a0
	0xF4E8,	// CPUSHL <BothCaches>,(a0) 
	0x5488, // ADDQ #2, a0
	0xF4E8	// CPUSHL <BothCaches>,(a0) 
};

//
//	InstallExceptionHandler()
//
void InstallExceptionHandler(struct CTEGlobals *globs, ExceptionInfo *exceptionInfo, 
		ExceptionHandler *handler, void *argPtr, int vectorNumber)
{	
	// Initialize the ExceptionInfo structure.
	exceptionInfo->instruction = jsrOpCode ;
	exceptionInfo->stubAddress = ExceptionHandlerStub ;
	exceptionInfo->globs = globs ;
	exceptionInfo->handler = handler ;
	exceptionInfo->argPtr = argPtr ;
	exceptionInfo->vectorNumber = vectorNumber ;
	
	// If the processor is a MC68040, push the instruction and stubAddress
	//	from the data cache.
	if(kCTEProcessorType68040 == globs->processorType)
		CPUSHStubVector(&exceptionInfo->instruction) ;
	
	// replace the entry in the ExceptionInfoPtrTable, saving the old one.
	exceptionInfo->oldInfoPtr = globs->exceptionInfoPtrTable[vectorNumber] ;
	globs->exceptionInfoPtrTable[vectorNumber] = exceptionInfo ;
		
	// replace the entry in the Exception Vector Table with a pointer to a stub,
	// saveing the old one.
	exceptionInfo->oldVector = 
		InstallExceptionVector(exceptionInfo, vectorNumber) ;	
}

//
//	RemoveExceptionHandler()
//
void RemoveExceptionHandler(struct CTEGlobals *globs, ExceptionInfo *exceptionInfo)
{
	unsigned short vectorNumber ;
	
	// get the vector number.
	vectorNumber = exceptionInfo->vectorNumber ;
	
	// replace the saved entry in the Exception Vector Table.
	InstallExceptionVector(exceptionInfo->oldVector, vectorNumber) ;
	
	// replace the saved entry in the ExceptionInfoPtrTable.
	globs->exceptionInfoPtrTable[vectorNumber] = exceptionInfo->oldInfoPtr ;
}



