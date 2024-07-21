/*
				File:		ExceptionSupport.h
			
				Contains:	This file is the include file for the ExceptionSupport
							source file.  This file contains data structures, etc.,
							which are needed by the routines in the CTE kernel which
							provide exception support to running subtests.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).
		 <1>	 12/14/90	SS		first checked in
 		   
 */
#ifndef _ExceptionSupport_
#define _ExceptionSupport_
//
//	ExceptionSupport.h
//

#include "GenericTypes.h"

#define	IntrLevelToVectorNum(intLevel)	(24 + intLevel)

//
//	ExceptionStackFrame
//
union ExceptionStackFrame
{
	struct
	{
		UWORD statusRegister ;
		ULONG programCounter ;
		UWORD vectorOffset ;
	} format0 ;
	
	struct
	{
		UWORD statusRegister ;
		ULONG programCounter ;
		UWORD vectorOffset ;
	} format1 ;
	
	struct
	{
		UWORD statusRegister ;
		ULONG programCounter ;
		UWORD vectorOffset ;
		ULONG instructionAddress ;
	} format2 ;
	
	struct
	{
		UWORD statusRegister ;
		ULONG programCounter ;
		UWORD vectorOffset ;
		ULONG effectiveAddress ;
	} format3 ;
	
	struct
	{
		UWORD statusRegister ;
		ULONG programCounter ;
		UWORD vectorOffset ;
		ULONG effectiveAddress ;
		UWORD specialStatusWord ;
		UWORD writeBack3Status ;
		UWORD writeBack2Status ;
		UWORD writeBack1Status ;
		ULONG faultAddress ;
		ULONG writeBack3Address ;
		ULONG writeBack3Data ;
		ULONG writeBack2Address ;
		ULONG writeBack2Data ;
		ULONG writeBack1Address ;
		union 
		{
			ULONG writeBack1Data ;
			ULONG pushDataLW0 ;
		} WB1D_PD0 ;
		ULONG pushDataLW1 ;
		ULONG pushDataLW2 ;
		ULONG pushDataLW3 ;
	} format7 ;
	
	struct
	{
		UWORD statusRegister ;
		ULONG programCounter ;
		UWORD vectorOffset ;
		ULONG instructionAddress ;
		UWORD internalRegisters[4] ;
	} format9 ;
	
	struct
	{
		UWORD statusRegister ;
		ULONG programCounter ;
		UWORD vectorOffset ;
		UWORD internalRegister1 ;
		UWORD specialStatusRegister ;
		UWORD instructionPipeStageC ;
		UWORD instructionPipeStageB ;
		ULONG dataCycleFaultAddress ;
		UWORD internalRegister2 ;
		UWORD internalRegister3 ;
		ULONG dataOutputBuffer ;
		UWORD internalRegister4 ;
		UWORD internalRegister5 ;
	} formatA ;
	
	struct
	{
		UWORD statusRegister ;
		ULONG programCounter ;
		UWORD vectorOffset ;
		UWORD internalRegister1 ;
		UWORD specialStatusRegister ;
		UWORD instructionPipeStageC ;
		UWORD instructionPipeStageB ;
		ULONG dataCycleFaultAddress ;
		UWORD internalRegister2 ;
		UWORD internalRegister3 ;
		ULONG dataOutputBuffer ;
		UWORD internalRegisters4[4] ;
		ULONG stageBAddress ;
		UWORD internalRegisters5[2] ;
		ULONG dataInputBuffer ;
		UWORD internalRegisters6[3] ;
		UWORD version ;
		UWORD internalRegisters7[18] ;
	} formatB ;

	struct
	{
		UWORD lowerAddress ;
		ULONG accessAddress ;
		UWORD instructionRegister ;
		UWORD statusRegister ;
		ULONG programCounter ;
	} format68K1;

	struct
	{
		UWORD statusRegister ;
		ULONG programCounter ;
	} format68K0 ;
} ;
#ifndef __cplusplus
typedef union ExceptionStackFrame ExceptionStackFrame ;
#endif __cplusplus


//
// The exception stack format types are enumerated as...
//
enum ExceptionStackFrameFormat
{
	frameFormat0,
	frameFormat1,
	frameFormat2,
	frameFormat3,
	frameFormat7 = 7,
	frameFormat9 = 9,
	frameFormatA,
	frameFormatB,
	frameFormat68K0 = 0x00010000,
	frameFormat68K1
} ;
#ifndef __cplusplus
typedef enum ExceptionStackFrameFormat ExceptionStackFrameFormat ;
#endif __cplusplus


//
// An installable C style exception handler.
//
typedef void ExceptionHandler(struct CTEGlobals *info, ULONG frameFormat,
					ExceptionStackFrame *theFrame, void *theArg) ;

//
// ExceptionInfo
//
struct ExceptionInfo
{
	UWORD instruction ;			// JSR instruction
	void *stubAddress ;			// stub address
	struct CTEGlobals *globs ;		// pointer to globals.
	ExceptionHandler *handler ;		// pointer to exception handler.
	void *argPtr ;				// pointer to SubtestInfo structure.
	void *oldVector ;			// vector from Exception Vector Table which
						//		was replaced when this handler was installed.
	struct ExceptionInfo *oldInfoPtr ;	// pointer from the ExceptionInfoPtrTable which
						//		was replaced when this handler was installed.
	unsigned short vectorNumber ;		// 
} ;
#ifndef __cplusplus
typedef struct ExceptionInfo ExceptionInfo ;
#endif __cplusplus


//
// Function prototypes.
//
#ifdef __cplusplus
extern "C" {
#endif __cplusplus

extern void InstallExceptionHandler(struct CTEGlobals *globs, 
				ExceptionInfo *exceptionInfo, 
				ExceptionHandler *handler,
				void *argPtr, int vectorNumber) ;
extern void RemoveExceptionHandler(struct CTEGlobals *globs, ExceptionInfo *exceptionInfo) ;
extern void ExceptionHandlerStub(void) ;
extern void FakeExceptionCall(int vectorNumber) ;

extern int SetInterruptLevel(int newLevel) ;
extern int GetInterruptLevel(void) ;
extern void *InstallExceptionVector(void *newHandler, int vectorNumber) ;

#ifdef __cplusplus
}	// close the extern "C" declaration
#endif __cplusplus

#endif _ExceptionSupport_