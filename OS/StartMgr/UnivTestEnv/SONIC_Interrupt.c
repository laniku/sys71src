/*
	File:		SONIC_Interrupt.c

	Contains:	This is the source file for the SONIC Interrupt handler.
				This interrupt handler is used by all SONIC subtests which
				generate and expect interrupts.

	Written by:	Joe Smyth

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).

*/


//
// SONIC interrupt exception handler
//

#include <SONIC_Loopback.h>
#include <SONIC_Interrupt.h>
#include <SONIC_Common.h>

void SONIC_InterruptHandler(CTEInfo *info, ULONG frameFormat, ExceptionStackFrame *theFrame, 
				void *argPtr)
{
	#pragma unused (info, frameFormat, theFrame, debugstring)
	ExceptionArg *exceptionArg = argPtr ;
	SONIC_Loopback_Params *params = exceptionArg->params ;
	SONIC_Loopback_Results *results = exceptionArg->results ;
	ULONG temp_data_address_scalar ;
	UWORD current_interrupts ;
	UWORD mask ;
	int i ;
//	char MMUModeValue  = true32b;
	char	debugstring[100] ;

//
// Jump to Macsbug if debug_mode is non-zero  
//

	#if defined (useMacsBug)
		if (params->debug_mode & 0x0200)
		{
			sprintf ( debugstring , "Now at start of Interrupt handler, Interrupt status:0x%4.4X",*(params->Sonic->regsArray[S_INTSTATUS])) ;
			DebugStr( c2pstr(debugstring) ) ;
		}
	#endif
	
//	SwapMMUMode( &MMUModeValue );	// put us into 32 bit addressing mode in case some other handler put us into 24bit mode for ci etc
	
	current_interrupts = *(params->Sonic->regsArray[S_INTSTATUS]) ; 
	
	results->interrupt_error = SONIC_Interrupt_Err_Unexpected ;

	for (i = 0; i < 15; i++)
	{
		mask = 0x0001 ;
		results->interrupt_source = (current_interrupts & (mask << i)) ;
	
		switch(results->interrupt_source)
		{ 
		
			case 0:
				break;
				
			case SONIC_Interrupt_Receive_FIFO_Overrun :
			
				results->interrupts_serviced |= SONIC_Interrupt_Receive_FIFO_Overrun ;	
				results->interrupt_error = SONIC_Interrupt_Err_Receive_FIFO_Overrun ;
				goto theEnd ;
				break ;
		
		
			case SONIC_Interrupt_Missed_Pkt_Counter_Rollover :
			
				results->interrupts_serviced |= SONIC_Interrupt_Missed_Pkt_Counter_Rollover ;		
				break ;
			
		
			case SONIC_Interrupt_Frame_Alignment_Error :
			
				results->interrupts_serviced |= SONIC_Interrupt_Frame_Alignment_Error ;		
				results->interrupt_error = SONIC_Interrupt_Err_Frame_Alignment ;
				goto theEnd ;
				break ;
		
		
			case SONIC_Interrupt_CRC_Tally_Counter_Rollover :
			
				results->interrupts_serviced |= SONIC_Interrupt_CRC_Tally_Counter_Rollover ;		
				break ;
		
		
			case SONIC_Interrupt_Receive_Buffer_Area_Exceeded :
			
				results->interrupts_serviced |= SONIC_Interrupt_Receive_Buffer_Area_Exceeded ;		
				break ;
		
		
			case SONIC_Interrupt_Receive_Buffers_Exhausted :
				
				temp_data_address_scalar = (ULONG)(&((*params->RRA_physical_ptr)[3].RXrsc_ptr0)) ;
				*(params->Sonic->regsArray[S_RWP]) = (UWORD)(temp_data_address_scalar & 0x0000FFFF) ;	// update Resource Write Pointer
				*(params->Sonic->regsArray[S_INTMASK]) &= ((UWORD)~SONIC_Interrupt_Receive_Buffers_Exhausted & 0x7FFF);	// Disable this interrupt, we can only handle it once		
				results->interrupts_serviced |= SONIC_Interrupt_Receive_Buffers_Exhausted ;		
				break ;
		
		
			case SONIC_Interrupt_Receive_Descriptors_Exhausted :
			

				params->RDA2_logical_ptr->RXpkt_link &= 0xFFFE ; 	// Set EOL Field to zero. The link is already pointing 
											// back to RDA1 which we will reuse.
				*(params->Sonic->regsArray[S_INTMASK]) &= ((UWORD)~SONIC_Interrupt_Receive_Descriptors_Exhausted & 0x7FFF) ;	// Disable this interrupt, we can only handle it once		
				results->interrupts_serviced |= SONIC_Interrupt_Receive_Descriptors_Exhausted ;		
				break ;
		
		
			case SONIC_Interrupt_Timer_Complete :
			
				results->interrupts_serviced |= SONIC_Interrupt_Timer_Complete ;		
				break ;
		
		
			case SONIC_Interrupt_Transmit_Error :
			
				results->interrupts_serviced |= SONIC_Interrupt_Transmit_Error ;		
				results->interrupt_error = SONIC_Interrupt_Err_Transmit ;
				goto theEnd ;
				break ;
		
		
			case SONIC_Interrupt_Transmission_Done :
			
				results->interrupts_serviced |= SONIC_Interrupt_Transmission_Done ;		
				break ;
		
		
			case SONIC_Interrupt_Pkt_Received :
			
				results->interrupts_serviced |= SONIC_Interrupt_Pkt_Received ;		
				break ;
		
		
			case SONIC_Interrupt_Programmable :
			
				results->interrupts_serviced |= SONIC_Interrupt_Programmable ;		
				break ;
		
		
			case SONIC_Interrupt_Load_CAM_Done :
			
				results->interrupts_serviced |= SONIC_Interrupt_Load_CAM_Done ;		
				break ;
		
		
			case SONIC_Interrupt_CD_Heartbeat_Lost :
			
				results->interrupts_serviced |= SONIC_Interrupt_CD_Heartbeat_Lost ;		
				break ;
		
		
			case SONIC_Interrupt_Bus_Retry_Occurred :
			
				results->interrupts_serviced |= SONIC_Interrupt_Bus_Retry_Occurred ;		
				results->interrupt_error = SONIC_Interrupt_Err_Bus_Retry_Occurred ;
				goto theEnd ;
				break ;
		
		
			default :
				results->interrupt_error = SONIC_Interrupt_Err_trying_to_execute_default ;
//				*(params->Sonic->regsArray[S_INTMASK]) = 0x0000 ;			// Disable all further interrupts	
				*(params->Sonic->regsArray[S_INTSTATUS]) = current_interrupts ;		// Clear the current interrupts	
				results->interrupt_source = current_interrupts ;
				goto theEnd ;
				break ;
			
		}
	}
	
	results->interrupt_error = SONIC_Interrupt_Err_Ok ;
	
theEnd :
	*(params->Sonic->regsArray[S_INTSTATUS]) = current_interrupts ;		// Clear the interrupts
	
//	SwapMMUMode( &MMUModeValue ); // Restore entry addressing mode for Ci etc

}


