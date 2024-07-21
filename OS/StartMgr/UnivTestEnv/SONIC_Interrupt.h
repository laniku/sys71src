/*
	File:		SONIC_Interrupt.h

	Contains:	This is the include file for the SONIC Interrupt subtest.

	Written by:	Joe Smyth

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).

*/

#ifndef _SONIC_Interrupt_
#define _SONIC_Interrupt_
//
//	SONIC_Interrupt.h
//

#include <CTETypes.h>
#include <SONIC_Common.h>

//
// SONIC_Interrupt error return values.
//
typedef enum SONIC_Interrupt_Err
{
	SONIC_Interrupt_Err_Ok,					// err = 0
	SONIC_Interrupt_Err_Unexpected,				// err = 1
	SONIC_Interrupt_Err_trying_to_execute_default,		// err = 2
	SONIC_Interrupt_Err_Receive_FIFO_Overrun,		// err = 3
	SONIC_Interrupt_Err_Transmit,				// err = 4
	SONIC_Interrupt_Err_Bus_Retry_Occurred,			// err = 5
	SONIC_Interrupt_Err_Frame_Alignment,			// err = 6
} ;
#ifndef __cplusplus
typedef enum SONIC_Interrupt_Err SONIC_Interrupt_Err ;
#endif __cplusplus


//
// SONIC_Interrupt status bit assignment
//
enum SONIC_Interrupt_values
{
	SONIC_Interrupt_Receive_FIFO_Overrun		=	0x0001,	
	SONIC_Interrupt_Missed_Pkt_Counter_Rollover	=	0x0002,
	SONIC_Interrupt_Frame_Alignment_Error		=	0x0004,
	SONIC_Interrupt_CRC_Tally_Counter_Rollover	=	0x0008,
	SONIC_Interrupt_Receive_Buffer_Area_Exceeded	=	0x0010,
	SONIC_Interrupt_Receive_Buffers_Exhausted	=	0x0020,
	SONIC_Interrupt_Receive_Descriptors_Exhausted	=	0x0040,
	SONIC_Interrupt_Timer_Complete			=	0x0080,			
	SONIC_Interrupt_Transmit_Error			=	0x0100,
	SONIC_Interrupt_Transmission_Done		=	0x0200,
	SONIC_Interrupt_Pkt_Received			=	0x0400,
	SONIC_Interrupt_Programmable			=	0x0800,
	SONIC_Interrupt_Load_CAM_Done			=	0x1000,
	SONIC_Interrupt_CD_Heartbeat_Lost		=	0x2000,
	SONIC_Interrupt_Bus_Retry_Occurred		=	0x4000,
} ;
#ifndef __cplusplus
typedef enum SONIC_Interrupt_Err SONIC_Interrupt_Err ;
#endif __cplusplus


// Function prototype for the Subtest.
#ifdef __cplusplus
extern "C" {
#endif __cplusplus

extern Subtest SONIC_Interrupt ;

#ifdef __cplusplus
}	// close the extern "C" declaration
#endif __cplusplus

void SONIC_InterruptHandler	(
				CTEInfo *info,
				ULONG frameFormat,
				ExceptionStackFrame *theFrame, 
				void *argPtr
				);

#endif _SONIC_Interrupt_
