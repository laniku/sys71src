/*
	File:		SONIC_Loopback.c

	Contains:	This is the source file for the SONIC Loopback subtest.
				This test performs a loopback test of the SONIC in a variety
				of modes, as determined by the test modifier.  This test can
				operate in either a polled or interrupt driven mode, as determined
				by the subtest modifier.

	Written by:	Joe Smyth

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).

*/

//
//	 SONIC_Loopback.c
//
//
// 4/16/91 SW	Changed the last byte of the DATACONFIG register from a C to a 9 per the instructions of
// 		Jano Banks and Sean Findley -- Sean
//

#include <SupportFunctions.h>
#include <SONIC_Loopback.h>
#include <SONIC_Common.h>




SubtestErr SONIC_Loopback(	CTEInfo *info, 
				SONIC_Loopback_Params *params,
				SONIC_Loopback_Results *results)
{
	#pragma unused (debugstring)
	SONIC_Loopback_Err err = SONIC_Loopback_Err_Unexpected ;
	UWORD temp_register ;
	UWORD NumOfCollisions ;
	UWORD *handy_pointer ;
	ULONG temp_data_address_scalar ;
	int i;
	ExceptionInfo exceptionInfo ;
	ExceptionArg exceptionArg ;
	int originalInterruptLevel ;
	char	debugstring[100] ;

	#if defined (useMacsBug)
		if (params->debug_mode)
		{
			sprintf ( debugstring , "Now at start of Loopback Subtest") ;
			DebugStr( c2pstr(debugstring) ) ;
		}
	
		sprintf ( debugstring , "Now at start of Bitwalk Subtest") ;
		DebugStr( c2pstr(debugstring) ) ;
	#endif





//
// Return the Silicon Revision to the Results block
//
	results->Silicon_Rev = *(params->Sonic->regsArray[S_VERSION]);	



//
// Put Sonic into software reset and disable reception
//	
	*(params->Sonic->regsArray[S_COMMAND]) = 0x0094 ;			
	if(*(params->Sonic->regsArray[S_COMMAND]) != 0x0094)		// Check that we are in reset
	{
		err = SONIC_Loopback_Err_on_Reset;
		goto ErrorExit ;
	}


		
		
// Set up new configuration register for revs greater than 3
// I changed the last byte of the S_DATACONFIG register from C to 9 according to instrutions from 
// HW guys -- Sean

	if (results->Silicon_Rev > 3)
	{
		*(params->Sonic->regsArray[S_DATACONFIG2]) = 0x0000 ;
		if (params->align_flag)
			*(params->Sonic->regsArray[S_DATACONFIG]) = 0x8329 ;
		else
			*(params->Sonic->regsArray[S_DATACONFIG]) = 0x8309 ;
			
	}
	else
	{
		if (params->align_flag)
			*(params->Sonic->regsArray[S_DATACONFIG]) = 0x0329 ;
		else
			*(params->Sonic->regsArray[S_DATACONFIG]) = 0x0309 ;
	}

//	
// Clear interrupt status register and disable the interrupts
//
	*(params->Sonic->regsArray[S_INTMASK]) = 0x0000 ;				// Disable all interrupts		
	if(0 !=  *(params->Sonic->regsArray[S_INTMASK]))
	{
		err = SONIC_Loopback_Err_disabling_interrupts;
		goto ErrorExit ;
	}
	
	*(params->Sonic->regsArray[S_INTSTATUS]) = 0x7FFF ;			
	if(0 !=  *(params->Sonic->regsArray[S_INTSTATUS]))
	{
		err = SONIC_Loopback_Err_clearing_Interrupt_Status ;
		goto ErrorExit ;
	}
	


//
// If we want to install interrupts then do it here 
//

	if (params->interrupt_mode)
	{
		exceptionArg.params = params ;				
		exceptionArg.results = results ;
		originalInterruptLevel = SUP_SetInterruptLevel(info,7) ;
		params->interrupt_install_function(info, &exceptionInfo, &exceptionArg) ;	// Install the interrupt handler.
		SUP_SetInterruptLevel(info, params->interrupt_level - 1) ;			// set interrupt mask to SONIC level -1. Interrupts will be 
												// serviced now if generated.
		*(params->Sonic->regsArray[S_INTMASK]) = 0x7FFF ;				// Enable all SONIC interrupts	

		
		*(params->Sonic->regsArray[S_TXCONTROL]) &= 0x7FFF ;				// Clear the PINT bit
		*(params->Sonic->regsArray[S_TXCONTROL]) |= 0x8000 ;				// Set the PINT bit thus generating a programmable interrupt
	}

//
// Clear reset
//

	temp_register = *(params->Sonic->regsArray[S_COMMAND]) ;	
	*(params->Sonic->regsArray[S_COMMAND]) = (temp_register & 0xFF7F) ; // Clear reset

//
// Initialise the End of buffer word count register to maximum packet size: 760 words
//

	*(params->Sonic->regsArray[S_EOBC]) = 0x02F8 ; 


//
// Initialise the first Receive Descriptor Area and the Upper Receive Descriptor Address
//

	temp_data_address_scalar = (ULONG)params->RDA1_physical_ptr ;
	*(params->Sonic->regsArray[S_URDA]) = (UWORD)((temp_data_address_scalar & 0xFFFF0000)>>bitshift16) ;
	results->URDA_value = *(params->Sonic->regsArray[S_URDA]) ;

	temp_data_address_scalar = (ULONG)params->RDA1_physical_ptr ;
	*(params->Sonic->regsArray[S_CRDA]) = (UWORD)(temp_data_address_scalar & 0x0000FFFF) ;
	results->CRDA_value = *(params->Sonic->regsArray[S_CRDA]) ;

	temp_data_address_scalar = (ULONG)params->RDA2_physical_ptr ;
	params->RDA1_logical_ptr->RXpkt_link = (temp_data_address_scalar & 0x0000FFFE) ;	// initialise RXpkt.link/EOL EOL = 0, there is another RDA
	params->RDA1_logical_ptr->RXpkt_in_use = 0xFFFF ;					// avail the RDA to Sonic: RXpkt_in_use -> non-zero
	params->RDA1_logical_ptr->RXpkt_status = 0 ; 						// The rest of the RDA is initialised to zero as it will be filled in by SONIC
	params->RDA1_logical_ptr->RXpkt_byte_count = 0 ;					// as it receives a packet
	params->RDA1_logical_ptr->RXpkt_ptr0 = 0 ; 	
	params->RDA1_logical_ptr->RXpkt_ptr1 = 0 ; 	
	params->RDA1_logical_ptr->RXpkt_seq_no = 0 ; 	
	
//
// Initialise the second Receive Descriptor Area
//

	temp_data_address_scalar = (ULONG)params->RDA3_physical_ptr ;
	params->RDA2_logical_ptr->RXpkt_link = ((temp_data_address_scalar & 0x0000FFFF) | 0x00000001);	// initialise RXpkt.link/EOL EOL = 1, this is the last RDA until we get the RDE
													// interrupt at which time we will allow SONIC to reuse RDA1.
	params->RDA2_logical_ptr->RXpkt_in_use = 0xFFFF ;						// avail the RDA to Sonic: RXpkt_in_use -> non-zero
	params->RDA2_logical_ptr->RXpkt_status = 0 ; 							// The rest of the RDA is initialised to zero as it will be filled in by SONIC
	params->RDA2_logical_ptr->RXpkt_byte_count = 0 ;						// as it receives a packet
	params->RDA2_logical_ptr->RXpkt_ptr0 = 0 ; 	
	params->RDA2_logical_ptr->RXpkt_ptr1 = 0 ; 	
	params->RDA2_logical_ptr->RXpkt_seq_no = 0 ; 	

	
//
// Initialise the third Receive Descriptor Area
//

	temp_data_address_scalar = (ULONG)params->RDA1_physical_ptr ;
	params->RDA3_logical_ptr->RXpkt_link = ((temp_data_address_scalar & 0x0000FFFF) | 0x00000001);	// initialise RXpkt.link/EOL EOL = 1, this is the last RDA 
													
	params->RDA3_logical_ptr->RXpkt_in_use = 0xFFFF ;						// avail the RDA to Sonic: RXpkt_in_use -> non-zero
	params->RDA3_logical_ptr->RXpkt_status = 0 ; 							// The rest of the RDA is initialised to zero as it will be filled in by SONIC
	params->RDA3_logical_ptr->RXpkt_byte_count = 0 ;						// as it receives a packet
	params->RDA3_logical_ptr->RXpkt_ptr0 = 0 ; 	
	params->RDA3_logical_ptr->RXpkt_ptr1 = 0 ; 	
	params->RDA3_logical_ptr->RXpkt_seq_no = 0 ; 	

//
// Initialise the Receive Resource Area
//

	temp_data_address_scalar = (ULONG)params->RRA_physical_ptr ;
	*(params->Sonic->regsArray[S_URRA]) = (UWORD)((temp_data_address_scalar & 0xFFFF0000)>>bitshift16) ;	// load upper Receive Resource Address

	temp_data_address_scalar = (ULONG)params->RRA_physical_ptr ;
	*(params->Sonic->regsArray[S_RSA]) = (UWORD)(temp_data_address_scalar & 0x0000FFFF) ;	// load Receive Resource Start Address
	*(params->Sonic->regsArray[S_RRP]) = (UWORD)(temp_data_address_scalar & 0x0000FFFF) ;	// load Receive Resource Read Pointer
		
	temp_data_address_scalar = (ULONG)params->RRA_physical_ptr ;
	*(params->Sonic->regsArray[S_REA]) = (UWORD)((temp_data_address_scalar + sizeof(Receive_Resource_Area)) & 0x0000FFFF) ;	// load Receive Resource End Address

	temp_data_address_scalar = (ULONG)(&((*params->RRA_physical_ptr)[2].RXrsc_ptr0)) ;
	*(params->Sonic->regsArray[S_RWP]) = (UWORD)(temp_data_address_scalar & 0x0000FFFF) ;	// load Resource Write Pointer

//
// Load the Receive Buffer information into the RRA
//

// First for the Receive Buffer Area 1

	temp_data_address_scalar = (ULONG)params->RBA1_physical_ptr ;
	(*params->RRA_logical_ptr)[0].RXrsc_ptr1 = ((temp_data_address_scalar & 0xFFFF0000)>>bitshift16) ;	// Store the RXrsrc.buff_ptr1 for RBA1 in the RRA

	temp_data_address_scalar = (ULONG)params->RBA1_physical_ptr ;
	(*params->RRA_logical_ptr)[0].RXrsc_ptr0 = (temp_data_address_scalar & 0x0000FFFF) ;	// Store the RXrsrc.buff_ptr0 for RBA1 in the RRA

	(*params->RRA_logical_ptr)[0].RXrsc_wc0 = 800 ; // Our buffer size is 800 words
	(*params->RRA_logical_ptr)[0].RXrsc_wc1 = 0 ;

// And for Receive Buffer Area 2

	temp_data_address_scalar = (ULONG)params->RBA2_physical_ptr ;
	(*params->RRA_logical_ptr)[1].RXrsc_ptr1 = ((temp_data_address_scalar & 0xFFFF0000)>>bitshift16) ;	// Store the RXrsrc.buff_ptr1 for RBA2 in the RRA

	temp_data_address_scalar = (ULONG)params->RBA2_physical_ptr ;
	(*params->RRA_logical_ptr)[1].RXrsc_ptr0 = (temp_data_address_scalar & 0x0000FFFF) ;	// Store the RXrsrc.buff_ptr0 for RBA2 in the RRA

	(*params->RRA_logical_ptr)[1].RXrsc_wc0 = 800 ; // Our buffer size is 800 words
	(*params->RRA_logical_ptr)[1].RXrsc_wc1 = 0 ;

// And finally for Receive Buffer Area 3

	temp_data_address_scalar = (ULONG)params->RBA3_physical_ptr ;
	(*params->RRA_logical_ptr)[2].RXrsc_ptr1 = ((temp_data_address_scalar & 0xFFFF0000)>>bitshift16) ;	// Store the RXrsrc.buff_ptr1 for RBA3 in the RRA

	temp_data_address_scalar = (ULONG)params->RBA3_physical_ptr ;
	(*params->RRA_logical_ptr)[2].RXrsc_ptr0 = (temp_data_address_scalar & 0x0000FFFF) ;	// Store the RXrsrc.buff_ptr0 for RBA3 in the RRA

	(*params->RRA_logical_ptr)[2].RXrsc_wc0 = 800 ; // Our buffer size is 800 words.
	(*params->RRA_logical_ptr)[2].RXrsc_wc1 = 0 ;



//
// Load the first block of RRA data into the Sonic Registers by invoking the Read RRA command
// This is subsequently done automatically by SONIC as receive buffers are exhausted, until the RRA is 
// empty.
// Note :This is the first DMA of the loopback DTM.
//

	temp_register = *(params->Sonic->regsArray[S_COMMAND]) ;	
	*(params->Sonic->regsArray[S_COMMAND]) = (temp_register & 0xFF7F) ; // Clear the Sonic Software reset

	temp_register = *(params->Sonic->regsArray[S_COMMAND]) ;			
	*(params->Sonic->regsArray[S_COMMAND]) = (temp_register | 0x0100) ; // Invoke Read RRA


	results->CRBA0_value = *(params->Sonic->regsArray[S_CRBA0]) ;	// Report what we actually loaded
	results->CRBA1_value = *(params->Sonic->regsArray[S_CRBA1]) ;
	results->RBWC0_value = *(params->Sonic->regsArray[S_RBWC0]) ;
	results->RBWC1_value = *(params->Sonic->regsArray[S_RBWC1]) ;



//
// Initialise the receive buffers
//

	for ( i = 0; i < sizeof(bufferArea); i++)
	{
		(*params->RBA1_logical_ptr)[i] = InitialData1;

		(*params->RBA2_logical_ptr)[i] = InitialData2;
	}

//
// Initialise the Transmit Descriptor Areas
//

// First pkt1TDA

	temp_data_address_scalar = (ULONG)params->TDA_physical_ptr ;
	*(params->Sonic->regsArray[S_UTDA]) = (UWORD)((temp_data_address_scalar & 0xFFFF0000)>>bitshift16) ;

	temp_data_address_scalar = (ULONG)params->TDA_physical_ptr ;
	*(params->Sonic->regsArray[S_CTDA]) = (UWORD)(temp_data_address_scalar & 0x0000FFFF) ;

	params->TDA_logical_ptr->pkt1TDA.TXpkt_status = 0 ;
	params->TDA_logical_ptr->pkt1TDA.TXpkt_config = 0x0000 ;	// configure the SONIC Transmitter with Programmable Interrupt, CRC on
									// and "Out of Window Collision Timer" begins at first bit of Preamble
	params->TDA_logical_ptr->pkt1TDA.TXpkt_size = 1500 ;
	params->TDA_logical_ptr->pkt1TDA.TXpkt_frag_count = 1 ;
	
	temp_data_address_scalar = (ULONG)params->TBA1_physical_ptr ;
	params->TDA_logical_ptr->pkt1TDA.TXpkt_frag_ptr0 = (temp_data_address_scalar & 0x0000FFFF) ;
	
	temp_data_address_scalar = (ULONG)params->TBA1_physical_ptr ;
	params->TDA_logical_ptr->pkt1TDA.TXpkt_frag_ptr1 = ((temp_data_address_scalar & 0xFFFF0000)>>bitshift16) ;

	params->TDA_logical_ptr->pkt1TDA.TXpkt_frag_size = 1500 ;
	
	temp_data_address_scalar = (ULONG)(&(params->TDA_physical_ptr->pkt2TDA.TXpkt_status)) ;
	if (params->loopback_mode == MACMode)
		temp_data_address_scalar = (temp_data_address_scalar | 0x00000001) ;	// If its MAC loopback mode only transmit 1 packet ie make this the last TDA
	else
		temp_data_address_scalar = (temp_data_address_scalar & 0x0000FFFE) ;	// Otherwise tell SONIC there's another to follow. This is because MAC loopback
											// is too fast for the receive cct to keep up with multiple packets.	
		
	params->TDA_logical_ptr->pkt1TDA.TXpkt_link = (UWORD)(temp_data_address_scalar & 0x0000FFFF) ;
	
// and now pkt2TDA

	params->TDA_logical_ptr->pkt2TDA.TXpkt_status = 0 ;
	params->TDA_logical_ptr->pkt2TDA.TXpkt_config = 0x0000 ;	// configure the SONIC Transmitter with Programmable Interrupt, CRC on
									// and "Out of Window Collision Timer" begins at first bit of Preamble
	params->TDA_logical_ptr->pkt2TDA.TXpkt_size = 1500 ;
	params->TDA_logical_ptr->pkt2TDA.TXpkt_frag_count = 2 ;
	
	temp_data_address_scalar = (ULONG)params->TBA2_physical_ptr ;
	params->TDA_logical_ptr->pkt2TDA.TXpkt_frag1_ptr0 = (temp_data_address_scalar & 0x0000FFFF) ;
	
	temp_data_address_scalar = (ULONG)params->TBA2_physical_ptr ;
	params->TDA_logical_ptr->pkt2TDA.TXpkt_frag1_ptr1 = ((temp_data_address_scalar & 0xFFFF0000)>>bitshift16) ;

	params->TDA_logical_ptr->pkt2TDA.TXpkt_frag1_size = 750 ;

	
	temp_data_address_scalar = (ULONG)(&((*params->TBA2_physical_ptr)[800])) ;
	params->TDA_logical_ptr->pkt2TDA.TXpkt_frag2_ptr0 = (temp_data_address_scalar & 0x0000FFFF) ;
	
	temp_data_address_scalar = (ULONG)(&((*params->TBA2_physical_ptr)[800])) ;
	params->TDA_logical_ptr->pkt2TDA.TXpkt_frag2_ptr1 = ((temp_data_address_scalar & 0xFFFF0000)>>bitshift16) ;

	params->TDA_logical_ptr->pkt2TDA.TXpkt_frag2_size = 750 ;

	temp_data_address_scalar = (ULONG)(&(params->TDA_physical_ptr->pkt1TDA.TXpkt_status)) ;
	params->TDA_logical_ptr->pkt2TDA.TXpkt_link = ((temp_data_address_scalar & 0x0000FFFF) | 0x00000001) ;	// This is the last TDA, so EOL  = 1
	
	
//
// Initialise the transmit buffer data, but only the used fragments
//

	for ( i = 0; i < 1500; i++)
		(*params->TBA1_logical_ptr)[i] = ExpectedData1 ;
	
	for ( i = 1500; i < 1600; i++)
		(*params->TBA1_logical_ptr)[i] = 0 ;

	for ( i = 0; i < 750; i++)
		(*params->TBA2_logical_ptr)[i] = ExpectedData2 ;

	for ( i = 750; i < 800; i++)
		(*params->TBA2_logical_ptr)[i] = 0 ;

	for ( i = 800; i < 1550; i++)
		(*params->TBA2_logical_ptr)[i] = ExpectedData3 ;

	for ( i = 1550; i < 1600; i++)
		(*params->TBA2_logical_ptr)[i] = 0 ;
		

//
// Prepare Sonic pointers for Load CAM instruction
//
	*(params->Sonic->regsArray[S_CAMDC]) = (UWORD)params->CAM_Data_logical_ptr->number_of_CAM_entries ;
	
	temp_data_address_scalar = (ULONG)params->CAM_Data_physical_ptr->CAM_data;
	*(params->Sonic->regsArray[S_URRA]) = (UWORD)((temp_data_address_scalar & 0xFFFF0000)>>bitshift16) ;
	
	temp_data_address_scalar = (ULONG)params->CAM_Data_physical_ptr->CAM_data;
	*(params->Sonic->regsArray[S_CAMDP]) = (UWORD)(temp_data_address_scalar & 0x0000FFFF) ;

//
// Issue load CAM command
//

	temp_register = *(params->Sonic->regsArray[S_COMMAND]) ;	
	*(params->Sonic->regsArray[S_COMMAND]) = (temp_register & 0xFF7F) ; // Clear reset
	

	temp_register = *(params->Sonic->regsArray[S_COMMAND]) ;			
	*(params->Sonic->regsArray[S_COMMAND]) = (temp_register | 0x0200) ; // Invoke load CAM
	
	
// Call the test specified Timeout Function.

	if (params->interrupt_mode ? handy_pointer = &results->interrupts_serviced : handy_pointer = params->Sonic->regsArray[S_INTSTATUS]) ;
	if (err = params->timeoutMethod(info,handy_pointer, 0x1000,params->timeout_factor ))
	{	
		err = SONIC_Loopback_Err_LCAM_timeout ;
		results->interrupt_status = *(params->Sonic->regsArray[S_INTSTATUS]);
		goto ErrorExit ;
	}
	results->interrupt_status = *(params->Sonic->regsArray[S_INTSTATUS]);

	if (results->interrupt_error)
	{
		err = SONIC_Loopback_Err_Interrupt ;
		goto ErrorExit ;
	}


//
// Configure the receive control register
//

	switch( params->loopback_mode )
	{
		case MACMode:
			*(params->Sonic->regsArray[S_RXCONTROL]) = 0xFA00 ;
			break;
			
		case ENDECMode:
			*(params->Sonic->regsArray[S_RXCONTROL]) = 0xFC00 ;
			break;
			
		case TransceiverMode:
			*(params->Sonic->regsArray[S_RXCONTROL]) = 0xFE00 ;
			break;
		
		default:
			err = SONIC_Loopback_Err_no_loopback_mode_specified ;
			goto ErrorExit;
			break;
	}

//
// Enable receiver
//

	*(params->Sonic->regsArray[S_COMMAND]) = 0x0008 ;
	
//
// Start transmission
//

	*(params->Sonic->regsArray[S_COMMAND]) = 0x000A ;

//
// Call the test specified Timeout Function for the 1st packet.
//
	results->CRBA0_value = *(params->Sonic->regsArray[S_CRBA0]) ;	// Report what receive buffer is been used
	results->CRBA1_value = *(params->Sonic->regsArray[S_CRBA1]) ;
	results->RBWC0_value = *(params->Sonic->regsArray[S_RBWC0]) ;
	results->RBWC1_value = *(params->Sonic->regsArray[S_RBWC1]) ;
	results->pkt_number = 1 ;

	handy_pointer = (UWORD *)(&(params->RDA1_logical_ptr->RXpkt_status)) ;
	if (err = params->timeoutMethod(info,handy_pointer, 0x0002, params->timeout_factor ))	// The mask 2 is the LBK (loopback packet received) 
	{											// bit of the RDA status register.  
		err = SONIC_Loopback_Err_timeout_receiving_1st_pkt ;
		results->Pkt1_Receive_Status = (UWORD)(params->RDA1_logical_ptr->RXpkt_status) ;
		results->Pkt1_Transmit_Status = (UWORD)(params->TDA_logical_ptr->pkt1TDA.TXpkt_status) ;

		goto ErrorExit ;										
	}
	results->Pkt1_Receive_Status = (UWORD)(params->RDA1_logical_ptr->RXpkt_status) ;		// Only lower word is valid
//
// Check for other errors
//
	results->Pkt1_Transmit_Status = (UWORD)(params->TDA_logical_ptr->pkt1TDA.TXpkt_status) ;	// Only lower word is valid
	if (results->Pkt1_Transmit_Status & 0x044E)							// Check only error bits
	{															
		err = SONIC_Loopback_Err_transmitting_1st_pkt ;
		goto ErrorExit ;										
	}
	

	if (results->Pkt1_Receive_Status & 0x000C)							// Check only error bits
	{															
		err = SONIC_Loopback_Err_receiving_1st_pkt ;	
		goto ErrorExit ;										
	}


//
// Compare received data with transmitted data for the first packet
//

	for (i = 0; i < 1500; i++)
	{
		results->transmitted_data = (*params->TBA1_logical_ptr)[i] ;
		results->received_data = (*params->RBA1_logical_ptr)[i];
		
		results->offset_of_byte_in_err = i ;
		
		if ((results->received_data != results->transmitted_data) || (results->received_data == 0) || (results->transmitted_data == 0))	// Sanity check, make sure we`re not transmitting and receiving zero`s
		{
			err = SONIC_Loopback_Err_in_1st_pkt_data ;
			goto ErrorExit ;
		}
	}
		
//
// If we are doing a MAC loopback then end here
//
	if (params->loopback_mode == MACMode)
		goto MAC_Loopback_Exit ;
	
	
//
// Call the test specified Timeout Function for 2nd packet.
//

	results->CRBA0_value = *(params->Sonic->regsArray[S_CRBA0]) ;	// Report what receive buffer is been used
	results->CRBA1_value = *(params->Sonic->regsArray[S_CRBA1]) ;
	results->RBWC0_value = *(params->Sonic->regsArray[S_RBWC0]) ;
	results->RBWC1_value = *(params->Sonic->regsArray[S_RBWC1]) ;
	results->pkt_number = 2 ;
	results->offset_of_byte_in_err = 0 ;		// reset values for second packet
	results->transmitted_data = 0 ;
	results->received_data = 0 ;
	
	handy_pointer = (UWORD *)(&(params->RDA2_logical_ptr->RXpkt_status)) ;
	if (err = params->timeoutMethod(info,handy_pointer, 0x0002, params->timeout_factor ))	// The mask 2 is the LBK (loopback packet received) 
	{											// bit of the TDA status register.  
		err = SONIC_Loopback_Err_timeout_receiving_2nd_pkt ;	
		results->Pkt2_Receive_Status = (UWORD)(params->RDA2_logical_ptr->RXpkt_status) ;
		results->Pkt2_Transmit_Status = (UWORD)(params->TDA_logical_ptr->pkt2TDA.TXpkt_status) ;
		goto ErrorExit ;										
	}


//
// Check for other errors in 2nd pkt
//
	results->Pkt2_Receive_Status = (UWORD)(params->RDA2_logical_ptr->RXpkt_status) ;
	results->Pkt2_Transmit_Status = (UWORD)(params->TDA_logical_ptr->pkt2TDA.TXpkt_status) ;

	if (results->Pkt2_Transmit_Status & 0x044E)
	{															
		err = SONIC_Loopback_Err_transmitting_2nd_pkt ;
		goto ErrorExit ;										
	}


	if (results->Pkt2_Receive_Status & 0x000C)
	{															
		err = SONIC_Loopback_Err_receiving_2nd_pkt ;
		goto ErrorExit ;										
	}

//
// Compare received data with transmitted data for the second packet
//

	for (i = 0; i < 750; i++)
	{
		results->transmitted_data = (*params->TBA2_logical_ptr)[i] ;
		results->received_data = (*params->RBA2_logical_ptr)[i] ;
		
		results->offset_of_byte_in_err = i ;

		if ((results->received_data != results->transmitted_data) || (results->received_data == 0) || (results->transmitted_data == 0))
		{
			err = SONIC_Loopback_Err_in_2nd_pkt_1st_fragment_data ;
			goto ErrorExit ;
		}
	}
	

	for (i = 750; i < 1500; i++)
	{
		results->transmitted_data = (*params->TBA2_logical_ptr)[i + 50] ;	// Fragment 2 begins at location 800 in the TBA, thus the offset of 50
		results->received_data = (*params->RBA2_logical_ptr)[i] ;

		results->offset_of_byte_in_err = i ;

		if ((results->received_data != results->transmitted_data) || (results->received_data == 0) || (results->transmitted_data == 0))
		{
			err = SONIC_Loopback_Err_in_2nd_pkt_2nd_fragment_data ;
			goto ErrorExit ;
		}
	}
	
	
// 
// Prepare the first TDA for another transmission so we can generate an RBA Exceeded interrupt
// then link TDA2 back to it by setting  the EOL bit of the link field to 0. 
// TDA2 link already points to TDA1 from the initial set up.
//

	if ((params->interrupt_mode) & (params->loopback_mode != MACMode))
	{
		params->TDA_logical_ptr->pkt1TDA.TXpkt_status = 0 ;
		params->TDA_logical_ptr->pkt1TDA.TXpkt_link   |= 0x0001 ;	// Make the TDA1 the last one in the list 

		params->TDA_logical_ptr->pkt2TDA.TXpkt_link   &= 0xFFFE ;	// enable TDA2 to link back to TDA1
		*(params->Sonic->regsArray[S_COMMAND]) = 0x000A ;		// Start Transmission

		results->CRBA0_value = *(params->Sonic->regsArray[S_CRBA0]) ;	// Report what receive buffer is been used
		results->CRBA1_value = *(params->Sonic->regsArray[S_CRBA1]) ;
		results->RBWC0_value = *(params->Sonic->regsArray[S_RBWC0]) ;
		results->RBWC1_value = *(params->Sonic->regsArray[S_RBWC1]) ;

	}


//
// If we get to here then all is OK, so return no error.
//
	MAC_Loopback_Exit :
		err = SONIC_Loopback_Err_Ok;
		
//		
// Do a final check that there were no interrupt errors and that we got all the interrupts we expected
//
	if (params->interrupt_mode)
	{
		SUP_SetInterruptLevel(info,7) ;			// Disable external interrupts.
		*(params->Sonic->regsArray[S_INTMASK]) = 0x0000 ;				// Disable all SONIC interrupts		
		params->interrupt_remove_function(info, &exceptionInfo, &exceptionArg) ;
		SUP_SetInterruptLevel(info,originalInterruptLevel) ;			// Enable external interrupts.

		if (results->interrupt_error)
		{	
			err = SONIC_Loopback_Err_Interrupt ;
			goto ErrorExit ;
		}
	
		switch( params->loopback_mode )
		{
			case MACMode:
				temp_register = results->interrupts_serviced ;
				if (!(temp_register &= 0x1E00)) 			// Only check for what we really are sure of.
				{
					err = SONIC_Loopback_Err_Expected_Interrupt_not_received ;
					goto ErrorExit ;
				}
				break;
				
			case ENDECMode:
			case TransceiverMode:
				temp_register = results->interrupts_serviced ;
				if (!(temp_register  &= 0x1E60))			// Only check for what we really are sure of.
				{
					err = SONIC_Loopback_Err_Expected_Interrupt_not_received ;
					goto ErrorExit ;
				}
				break;
				
			default:
				err = SONIC_Loopback_Err_no_loopback_mode_specified ;
				goto ErrorExit;
				break;
		}
		
	
	}
	
	ErrorExit :
	
// Fill the Collision Count into the NumOfCollisionsDetected result field
		NumOfCollisions = (results->Pkt1_Transmit_Status & 0xF800) ;
		results->NumOfCollisionsDetected  = (NumOfCollisions >> 11) ;			// Only bits 11 thru 15 are valid
	
		NumOfCollisions = (results->Pkt2_Transmit_Status & 0xF800) ;
		results->NumOfCollisionsDetected  += (NumOfCollisions >> 11) ;			// Only bits 11 thru 15 are valid

// If we installed an interrupt handler earlier, now would be a good time to remove it.

	if ((err) && (params->interrupt_mode))	// if there is no error then it is already removed
	{
		SUP_SetInterruptLevel(info,7) ;			// Disable external interrupts.
		*(params->Sonic->regsArray[S_INTMASK]) = 0x0000 ;				// Disable all SONIC interrupts		
		params->interrupt_remove_function(info, &exceptionInfo, &exceptionArg) ;
		SUP_SetInterruptLevel(info,originalInterruptLevel) ;			// Enable external interrupts.
	}
		


		return(err);
}

