/*
	File:		SONIC_CAMDMA.h

	Contains:	This is the include file for the SONIC CAMDMA subtest.

	Written by:	Joe Smyth

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).

*/

#ifndef _SONIC_CAMDMA_
#define _SONIC_CAMDMA_
//
//	SONIC_CAMDMA.h
//

#include <CTETypes.h>
#include <SONIC_Common.h>


//
// SONIC_CAMDMA error return values.
//
typedef enum SONIC_CAMDMA_Err
{
	SONIC_CAMDMA_Err_Ok,				// err = 0
	SONIC_CAMDMA_Err_Unexpected,			// err = 1
	SONIC_CAMDMA_Err_disabling_interrupts,		// err = 2
	SONIC_CAMDMA_Err_on_Reset,			// err = 3
	SONIC_CAMDMA_Err_clearing_Interrupt_Status,	// err = 4
	SONIC_CAMDMA_Err_LCAM_timeout,			// err = 5
	SONIC_CAMDMA_Err_in_CAM_data_comparison		// err = 6
} ;
#ifndef __cplusplus
typedef enum SONIC_CAMDMA_Err SONIC_CAMDMA_Err ;
#endif __cplusplus


//
// SONIC_CAMDMA parameter block.
//
struct SONIC_CAMDMA_Params
{
	SONIC_Registers_Union *Sonic;		// ptr to the start of the Sonic register union, ie sonic base address
	int align_flag;				// indicates 16/32 bit alignment, 0 for 16 bit, 1 for 32 bit
	int debug_mode ;		// If non-zero, the subtest will jump to Macsbug at start of test
	CAM_data_struct *CAM_Data_logical_ptr;
	CAM_data_struct *CAM_Data_physical_ptr;
	SONICTest_Err (*timeoutMethod)(struct CTEGlobals *timeoutInfo, UWORD *timeoutParameter, UWORD relevant_bits_mask, long timeout_count) ;
	long timeout_factor ;
} ;

#ifndef __cplusplus
typedef struct SONIC_CAMDMA_Params SONIC_CAMDMA_Params ;
#endif __cplusplus


//
// SONIC_CAMDMA result block.
//
struct SONIC_CAMDMA_Results
{
	int Silicon_Rev ;			// Silicon Revision of the Sonic under test
	int CAM_Addr_Port;			// number of the CAM Address Port been accessed
	long CAM_entry_pointer ;		// number of the CAM entry been addressed
	UWORD expected_data;			// Data written to CAM
	UWORD actual_data;			// Data read from CAM
	UWORD Interrupt_status;			// Interrupt status at time of failure
	UWORD CAMDC_value;			// number of CAM entries to be loaded
	UWORD URRA_value;			// Upper half of CAM data physical address
	UWORD CAMDP_value;			// lower half of CAM data physical address
} ;
#ifndef __cplusplus
typedef struct SONIC_CAMDMA_Results SONIC_CAMDMA_Results ;
#endif __cplusplus


// Function prototype for the Subtest.
#ifdef __cplusplus
extern "C" {
#endif __cplusplus

extern Subtest SONIC_CAMDMA ;

#ifdef __cplusplus
}	// close the extern "C" declaration
#endif __cplusplus

#endif _SONIC_CAMDMA_