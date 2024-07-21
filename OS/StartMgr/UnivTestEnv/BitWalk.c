/*
				File:		BitWalk.c
			
				Contains:	This file contains the routines which perform parameterized
							bitwalk operations at a specified address.  These routines
							are available for use by subtests running in the CTE.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).
		 <1>	 12/14/90	SS		first checked in
 		   
 */
//
//	BitWalk.c
//

#include "GenericTypes.h"
#include "BitWalk.h"
#include "68KOpCodes.h"


//
//	BitWalk8()
//
UBYTE BitWalk8(struct CTEGlobals *globs, BitWalk8_PB *params, BitWalk8_RB *results)
{	
	// Do once for true pattern phase, once for inverted pattern phase.
	for(results->phase = 0; results->phase <= 1; results->phase++)
	{
		results->pattern = (results->phase == 0 ? params->initialPattern : ~params->initialPattern) ;
		
		// Do for each shift of pattern.
		for(results->shiftCount = 0; results->shiftCount < 8; results->shiftCount++)
		{
			// Calculate the pattern to write to the port.
			// writeValue = (~dontWriteMask & doWriteBits) | (dontWriteMask & pattern) 
			results->writeValue = (~params->dontWriteMask & params->doWriteBits) 
							| (params->dontWriteMask & results->pattern) ;
			
			// Write the pattern.
			if(params->writeMethod)
				params->writeMethod(globs, params->bytePtr, results->writeValue) ;
			else
				*params->bytePtr = results->writeValue ;
			
			// Read back.
			if(params->readMethod)
				results->readValue = params->readMethod(globs, params->bytePtr) ;
			else
				results->readValue = *params->bytePtr ;
				
			// Eor with writeValue, mask don't cares.
			results->failedBits = params->dontCareMask & 
					(results->writeValue ^ results->readValue) ;
			
			// If result is not zero the there's an error.
			if(0 != results->failedBits)
				goto ErrorExit ;
			
			// Next pattern.
			results->pattern = ROL_B(results->pattern, 1) ;
		}
	}
	
	// Leave the byte being tested with a known value.
	if(params->writeMethod)
		params->writeMethod(globs, params->bytePtr, params->finalValue) ;
	else
		*params->bytePtr = params->finalValue ;
	
ErrorExit :
	return(results->failedBits) ;
}

//
//	BitWalk16()
//
UWORD BitWalk16(struct CTEGlobals *globs, BitWalk16_PB *params, BitWalk16_RB *results)
{
	// Do once for true pattern phase, once for inverted pattern phase.
	for(results->phase = 0; results->phase <= 1; results->phase++)
	{
		results->pattern = (results->phase == 0 ? params->initialPattern : ~params->initialPattern) ;
		
		// Do for each shift of pattern.
		for(results->shiftCount = 0; results->shiftCount < 16; results->shiftCount++)
		{
			// Calculate the pattern to write to the port.
			// writeValue = (~dontWriteMask & doWriteBits) | (dontWriteMask & pattern) 
			results->writeValue = (~params->dontWriteMask & params->doWriteBits) 
							| (params->dontWriteMask & results->pattern) ;
			
			// Write the pattern.
			if(params->writeMethod)
				params->writeMethod(globs, params->wordPtr, results->writeValue) ;
			else
				*params->wordPtr = results->writeValue ;
			
			// Read back.
			if(params->readMethod)
				results->readValue = params->readMethod(globs, params->wordPtr) ;
			else
				results->readValue = *params->wordPtr ;
				
			// Eor with writeValue, mask don't cares.
			results->failedBits = params->dontCareMask & 
					(results->writeValue ^ results->readValue) ;
			
			// If result is not zero the there's an error.
			if(0 != results->failedBits)
				goto ErrorExit ;
			
			// Next pattern.
			results->pattern = ROL_W(results->pattern, 1) ;
		}
	}

	// Leave the word being tested with a known value.
	if(params->writeMethod)
		params->writeMethod(globs, params->wordPtr, params->finalValue) ;
	else
		*params->wordPtr = params->finalValue ;
	
ErrorExit :
	return(results->failedBits) ;
}

//
//	BitWalk32()
//
ULONG BitWalk32(struct CTEGlobals *globs, BitWalk32_PB *params, BitWalk32_RB *results)
{
	// Do once for true pattern phase, once for inverted pattern phase.
	for(results->phase = 0; results->phase <= 1; results->phase++)
	{
		results->pattern = (results->phase == 0 ? params->initialPattern : ~params->initialPattern) ;
		
		// Do for each shift of pattern.
		for(results->shiftCount = 0; results->shiftCount < 32; results->shiftCount++)
		{
			// Calculate the pattern to write to the port.
			// writeValue = (~dontWriteMask & doWriteBits) | (dontWriteMask & pattern) 
			results->writeValue = (~params->dontWriteMask & params->doWriteBits) 
							| (params->dontWriteMask & results->pattern) ;
			
			// Write the pattern.
			if(params->writeMethod)
				params->writeMethod(globs, params->longPtr, results->writeValue) ;
			else
				*params->longPtr = results->writeValue ;
			
			// Read back.
			if(params->readMethod)
				results->readValue = params->readMethod(globs, params->longPtr) ;
			else
				results->readValue = *params->longPtr ;
				
			// Eor with writeValue, mask don't cares.
			results->failedBits = params->dontCareMask & 
					(results->writeValue ^ results->readValue) ;
			
			// If result is not zero the there's an error.
			if(0 != results->failedBits)
				goto ErrorExit ;
			
			// Next pattern.
			results->pattern = ROL_L(results->pattern, 1) ;
		}
	}

	// Leave the longword being tested with a known value.
	if(params->writeMethod)
		params->writeMethod(globs, params->longPtr, params->finalValue) ;
	else
		*params->longPtr = params->finalValue ;
	
ErrorExit :
	return(results->failedBits) ;
}
