/*
	File:		SONIC_CAMDMA.c

	Contains:	This is the source file for the SONIC CAMDMA subtest.

	Written by:	Joe Smyth

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).

*/

//
//	 SONIC_CAMDMA.c
//

#include <SupportFunctions.h>
#include <SONIC_CAMDMA.h>
#include <SONIC_Common.h>


SubtestErr SONIC_CAMDMA(CTEInfo *info, SONIC_CAMDMA_Params *params,
					SONIC_CAMDMA_Results *results)
{
	#pragma unused (debugstring)
	SONIC_CAMDMA_Err err = SONIC_CAMDMA_Err_Unexpected ;
	UWORD temp_register;
	void *temp_data_address;
	ULONG temp_data_address_scalar;
	int i;
	char	debugstring[100] ;

//
// Jump to Macsbug if debug_mode is non-zero
//

	#if defined (useMacsBug)
		if (params->debug_mode)
		{
			sprintf ( debugstring , "Now at start of CAMDMA Subtest") ;
			DebugStr( c2pstr(debugstring) ) ;
		}
	#endif

//
// Return the Silicon Revision to the Results block
//
	results->Silicon_Rev = *(params->Sonic->regsArray[S_VERSION]);	

	
	
	

//	
// Disable all interrupts
//
	*(params->Sonic->regsArray[S_INTMASK]) = 0x0000;			
	if(0 !=  *(params->Sonic->regsArray[S_INTMASK]))
	{
		err = SONIC_CAMDMA_Err_disabling_interrupts;
		goto ErrorExit ;
	}

//
// Put Sonic into software reset and disable reception
//	
	*(params->Sonic->regsArray[S_COMMAND]) = 0x0094 ;			
	if(*(params->Sonic->regsArray[S_COMMAND]) != 0x0094)		// Check that we are in reset
	{
		err = SONIC_CAMDMA_Err_on_Reset;
		goto ErrorExit ;
	}


//	
// Clear interrupt status register
//
	*(params->Sonic->regsArray[S_INTSTATUS]) = 0x7FFF;			
	if(0 !=  (*(params->Sonic->regsArray[S_INTSTATUS]) & 0xDFFF))	// Mask off the Heartbeat lost interrupt as it can occur at any time
	{
		err = SONIC_CAMDMA_Err_clearing_Interrupt_Status;
		goto ErrorExit ;
	}


//
// Initialise the Data Configuration register for DMA
// PO1,0 low when Sonic is busmaster,Sync STERM, Data Width depends on align flag, No wait states,
// empty fill DMA mode
//

//	if (params->align_flag)
//		*(params->Sonic->regsArray[S_DATACONFIG]) = 0x0320 ;
//	else
//		*(params->Sonic->regsArray[S_DATACONFIG]) = 0x0300 ;

		
// Set up new configuration register for revs greater than 3

	if (results->Silicon_Rev > 3)
	{
		*(params->Sonic->regsArray[S_DATACONFIG2]) = 0x0000 ;
		if (params->align_flag)
			*(params->Sonic->regsArray[S_DATACONFIG]) = 0x832C ;
		else
			*(params->Sonic->regsArray[S_DATACONFIG]) = 0x830C ;
			
	}
	else
	{
		if (params->align_flag)
			*(params->Sonic->regsArray[S_DATACONFIG]) = 0x032C ;
		else
			*(params->Sonic->regsArray[S_DATACONFIG]) = 0x030C ;
	}



//
// Prepare Sonic pointers for Load CAM instruction
//
	*(params->Sonic->regsArray[S_CAMDC]) = (UWORD)params->CAM_Data_logical_ptr->number_of_CAM_entries ;
	results->CAMDC_value = (UWORD)params->CAM_Data_logical_ptr->number_of_CAM_entries ;

	temp_data_address = params->CAM_Data_physical_ptr->CAM_data ;
	temp_data_address_scalar = (ULONG)temp_data_address;
	*(params->Sonic->regsArray[S_URRA]) = (UWORD)((temp_data_address_scalar & 0xFFFF0000)>>bitshift16) ;
	results->URRA_value = *(params->Sonic->regsArray[S_URRA]) ;
	
	temp_data_address = params->CAM_Data_physical_ptr->CAM_data ;
	temp_data_address_scalar = (ULONG)temp_data_address;
	*(params->Sonic->regsArray[S_CAMDP]) = (UWORD)(temp_data_address_scalar & 0x0000FFFF) ;
	results->CAMDP_value = *(params->Sonic->regsArray[S_CAMDP]) ;

//
// Issue load CAM command
//

	temp_register = *(params->Sonic->regsArray[S_COMMAND]) ;	
	*(params->Sonic->regsArray[S_COMMAND]) = (temp_register & 0xFF7F) ; // Clear reset

	temp_register = *(params->Sonic->regsArray[S_COMMAND]) ;			
	*(params->Sonic->regsArray[S_COMMAND]) = (temp_register | 0x0200) ; // Invoke load CAM

	
	
// Call the test specified Timeout Function.

	if (err = params->timeoutMethod(info,params->Sonic->regsArray[S_INTSTATUS], 0x1000, params->timeout_factor ))	// even though the status register is a UWORD because we pass it as a long we 
	{													// pick up the extra bits along the way. The 1 is the LCD (Load CAM Done)
		results->Interrupt_status = *(params->Sonic->regsArray[S_INTSTATUS]) ;				// bit of the interrupt status register. This is kept updated even though interrupts are
		err = SONIC_CAMDMA_Err_LCAM_timeout ;
		goto ErrorExit ;										// disabled.
	}
	results->Interrupt_status = *(params->Sonic->regsArray[S_INTSTATUS]);


//
// Put Sonic into software reset and disable reception as the CAM
// should only be read when SONIC is in reset mode.
//	
	*(params->Sonic->regsArray[S_COMMAND]) = 0x0094 ;			
	if(*(params->Sonic->regsArray[S_COMMAND]) != 0x0094)		// Check that we are in reset
	{
		err = SONIC_CAMDMA_Err_on_Reset;
		goto ErrorExit ;
	}

//
// Compare the data in the CAM with the expected data
//
	for (i = 0; i < params->CAM_Data_logical_ptr->number_of_CAM_entries; i++ )
	{
		*(params->Sonic->regsArray[S_CAMEP]) = params->CAM_Data_logical_ptr->CAM_data[i*4] ;	// tell SONIC which CAM cell entry (or row if we picture the CAM as a matrix)  we wish to read
		results->CAM_entry_pointer = params->CAM_Data_logical_ptr->CAM_data[i*4] ;	// tell SONIC which CAM cell entry (or row if we picture the CAM as a matrix)  we wish to read
		results->CAM_Addr_Port = 0 ;
		results->expected_data = params->CAM_Data_logical_ptr->CAM_data[(i*4)+1] ;
		results->actual_data = *(params->Sonic->regsArray[S_CAMAP0]) ;
		if (results->expected_data != results->actual_data)
		{
			err = SONIC_CAMDMA_Err_in_CAM_data_comparison ;
			goto ErrorExit ;
		}
	
		results->CAM_Addr_Port = 1 ;
		results->expected_data = params->CAM_Data_logical_ptr->CAM_data[(i*4)+2] ;
		results->actual_data = *(params->Sonic->regsArray[S_CAMAP1]) ;
		if (results->expected_data != results->actual_data)
		{
			err = SONIC_CAMDMA_Err_in_CAM_data_comparison ;
			goto ErrorExit ;
		}
	
	
		results->CAM_Addr_Port = 2 ;
		results->expected_data = params->CAM_Data_logical_ptr->CAM_data[(i*4)+3] ;
		results->actual_data = *(params->Sonic->regsArray[S_CAMAP2]) ;
		if (results->expected_data != results->actual_data)
		{
			err = SONIC_CAMDMA_Err_in_CAM_data_comparison ;
			goto ErrorExit ;
		}
	
	}
	
	
//
// If we get to here then all is OK, so return no error.
//
	err = SONIC_CAMDMA_Err_Ok;
	
	ErrorExit :
		return(err);
}

