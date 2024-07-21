/*
	File:		SONIC_BitMarch.c

	Contains:	This is the source file for the SONIC Bit March subtest.
				This test performs a bit walk test on each of the SONIC
				registers.

	Written by:	Joe Smyth

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).

*/

//
//	 SONIC_BitMarch.c
//

#include <SupportFunctions.h>
#include <SONIC_BitMarch.h>
#include <SONIC_Common.h>

//
// This function sets up the parameter block for bitwalking a register which does not have any rules
// governing the way it is to be accessed
//

UWORD BitWalk_a_No_By_Law_register(CTEInfo *no_by_law_info, SONIC_BitMarch_Params *no_by_law_params,
					SONIC_BitMarch_Results *no_by_law_results,int no_by_law_i)
{
	no_by_law_results->Reg_under_test = no_by_law_i;
	no_by_law_results->bitWalk16Params.wordPtr = no_by_law_params->Sonic->regsArray[no_by_law_i];
	no_by_law_results->bitWalk16Params.dontWriteMask = 0xFFFF;
	no_by_law_results->bitWalk16Params.doWriteBits = 0x0000;
	no_by_law_results->bitWalk16Params.dontCareMask = 0xFFFF;
	no_by_law_results->bitWalk16Params.initialPattern = 0x0001;
	no_by_law_results->bitWalk16Params.finalValue = *(no_by_law_params->Sonic->regsArray[no_by_law_i]);
	no_by_law_results->bitWalk16Params.writeMethod = NULL;
	no_by_law_results->bitWalk16Params.readMethod = NULL;
	
	return(SUP_BitWalk16(no_by_law_info, &no_by_law_results->bitWalk16Params, &no_by_law_results->bitWalk16Results));
}

//
// This function sets up the parameter block for bitwalking a register which does not have any rules
// governing the way it is to be accessed
//

UWORD BitWalk_a_bit0_equals_0_register(CTEInfo *bit0_equals_0_info, SONIC_BitMarch_Params *bit0_equals_0_params,
					SONIC_BitMarch_Results *bit0_equals_0_results,int bit0_equals_0_i)
{
	bit0_equals_0_results->Reg_under_test = bit0_equals_0_i;
	bit0_equals_0_results->bitWalk16Params.wordPtr = bit0_equals_0_params->Sonic->regsArray[bit0_equals_0_i];
	bit0_equals_0_results->bitWalk16Params.dontWriteMask = 0xFFFE;
	bit0_equals_0_results->bitWalk16Params.doWriteBits = 0x0000;
	bit0_equals_0_results->bitWalk16Params.dontCareMask = 0xFFFF;
	bit0_equals_0_results->bitWalk16Params.initialPattern = 0x0001;
	bit0_equals_0_results->bitWalk16Params.finalValue = *(bit0_equals_0_params->Sonic->regsArray[bit0_equals_0_i]);
	bit0_equals_0_results->bitWalk16Params.writeMethod = NULL;
	bit0_equals_0_results->bitWalk16Params.readMethod = NULL;
	
	return(SUP_BitWalk16(bit0_equals_0_info, &bit0_equals_0_results->bitWalk16Params, &bit0_equals_0_results->bitWalk16Results));
}

//
// This function gets the contents of a register and inverts it.
// For use as the readMethod for the BitWalk_data_inverted_register function
//

UWORD Read_and_Invert(CTEInfo *info,UWORD *thereg)
{
	#pragma unused (info)
	return(~(*thereg));
}

//
// This function sets up the parameter block for bitwalking registers where the data 
// that is read back from the register is the inverse of the data written to it.
//

UWORD BitWalk_data_inverted_register(CTEInfo *data_inverted_info, SONIC_BitMarch_Params *data_inverted_params,
					SONIC_BitMarch_Results *data_inverted_results,int data_inverted_i)
{
	data_inverted_results->Reg_under_test = data_inverted_i;
	data_inverted_results->bitWalk16Params.wordPtr = data_inverted_params->Sonic->regsArray[data_inverted_i];
	data_inverted_results->bitWalk16Params.dontWriteMask = 0xFFFF;
	data_inverted_results->bitWalk16Params.doWriteBits = 0x0000;
	data_inverted_results->bitWalk16Params.dontCareMask = 0xFFFF;
	data_inverted_results->bitWalk16Params.initialPattern = 0x0001;
	data_inverted_results->bitWalk16Params.finalValue = Read_and_Invert(data_inverted_info, data_inverted_params->Sonic->regsArray[data_inverted_i]);
	data_inverted_results->bitWalk16Params.writeMethod = NULL;
	data_inverted_results->bitWalk16Params.readMethod = Read_and_Invert;
	
	return(SUP_BitWalk16(data_inverted_info, &data_inverted_results->bitWalk16Params, &data_inverted_results->bitWalk16Results));
}

//
// This function gets the contents of a register and inverts it.
// For use as the readMethod for the BitWalk_data_shifted_register function
//

UWORD Read_and_shift_left_once(CTEInfo *info,UWORD *thereg)
{
	#pragma unused (info)
	return((*thereg) << 1);
}


//
// This function gets the contents of a register and inverts it.
// For use as the readMethod for the BitWalk_data_shifted_register function
//

UWORD Read_and_shift_left_twice(CTEInfo *info,UWORD *thereg)
{
	#pragma unused (info)
	return((*thereg) << 2);
}

//
// This function sets up the parameter block for bitwalking registers where the data 
// that is written to the register is shifted right once in 16 bit mide and twice in 32 bit mode
//

UWORD BitWalk_data_shifted_register(CTEInfo *data_shifted_info, SONIC_BitMarch_Params *data_shifted_params,
					SONIC_BitMarch_Results *data_shifted_results,int data_shifted_i)
{
	data_shifted_results->Reg_under_test = data_shifted_i;
	data_shifted_results->bitWalk16Params.wordPtr = data_shifted_params->Sonic->regsArray[data_shifted_i];
	data_shifted_results->bitWalk16Params.dontWriteMask = 0xFFFF;
	data_shifted_results->bitWalk16Params.doWriteBits = 0x0000;
	data_shifted_results->bitWalk16Params.dontCareMask = data_shifted_params->align_flag ? 0xFFFC : 0xFFFE;
	data_shifted_results->bitWalk16Params.initialPattern = 0x0001;
	data_shifted_results->bitWalk16Params.finalValue = (*(data_shifted_params->Sonic->regsArray[data_shifted_i]) << (data_shifted_params->align_flag + 1));
	data_shifted_results->bitWalk16Params.writeMethod = NULL;
	data_shifted_results->bitWalk16Params.readMethod = data_shifted_params->align_flag ? Read_and_shift_left_twice : Read_and_shift_left_once;
	
	return(SUP_BitWalk16(data_shifted_info, &data_shifted_results->bitWalk16Params, &data_shifted_results->bitWalk16Results));
}



  


SubtestErr SONIC_BitMarch(CTEInfo *info, SONIC_BitMarch_Params *params,
					SONIC_BitMarch_Results *results)
{
	#pragma unused (debugstring)
	SONIC_BitMarch_Error err = SONIC_BitMarch_Err_Unexpected;
	int	i; 		// General purpose loop counter
	UWORD temp_reg_data;
	char	debugstring[100] ;

//
// Jump to Macsbug if debug_mode is non-zero
//

	#if defined (useMacsBug)
		if (params->debug_mode)
		{
			sprintf ( debugstring , "Now at start of Bitwalk Subtest") ;
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
	results->Reg_under_test = S_COMMAND;
	*(params->Sonic->regsArray[S_COMMAND]) = 0x0094;			
	if(*(params->Sonic->regsArray[S_COMMAND]) != 0x0094)		// Check that we are in reset
	{
		err = SONIC_BitMarch_Err_on_Reset;
		goto ErrorExit ;
	}
//	
// Test the data configuration register
//
/*	results->Reg_under_test = S_DATACONFIG;
	results->bitWalk16Params.wordPtr =  params->Sonic->regsStruct.Data_Config;
	results->bitWalk16Params.dontWriteMask = 0x3CFF;
	results->bitWalk16Params.doWriteBits = 0x0300;
	results->bitWalk16Params.dontCareMask = 0xFCFF;
	results->bitWalk16Params.initialPattern = 0x0001;
	results->bitWalk16Params.finalValue = *(params->Sonic->regsArray[S_DATACONFIG]);
	results->bitWalk16Params.writeMethod = NULL;
	results->bitWalk16Params.readMethod = NULL;
	
	if ( 0 != SUP_BitWalk16(info, &results->bitWalk16Params, &results->bitWalk16Results) ) 
	{	
		err = SONIC_BitMarch_Err_in_bitWalk ;
		goto ErrorExit ;
	}
Don't bit march the data configuration register, results are too unpredictable */

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
// Disable all interrupts
//
	*(params->Sonic->regsArray[S_INTMASK]) = 0x0000;			
	if(0 != (results->bitWalk16Results.failedBits = *(params->Sonic->regsArray[S_INTMASK])))
	{
		results->Reg_under_test = S_INTMASK;
		err = SONIC_BitMarch_Err_disabling_interrupts;
		goto ErrorExit ;
	}


//
// Test the receive control register
//
	results->Reg_under_test = S_RXCONTROL;
	results->bitWalk16Params.wordPtr =  params->Sonic->regsStruct.Rx_Control;
	results->bitWalk16Params.dontWriteMask = 0xFE00;
	results->bitWalk16Params.doWriteBits = 0x0000;
	results->bitWalk16Params.dontCareMask = 0xFE00;
	results->bitWalk16Params.initialPattern = 0x0001;
	results->bitWalk16Params.finalValue = *(params->Sonic->regsArray[S_RXCONTROL]);
	results->bitWalk16Params.writeMethod = NULL;
	results->bitWalk16Params.readMethod = NULL;
	
	if ( 0 != SUP_BitWalk16(info, &results->bitWalk16Params, &results->bitWalk16Results) ) 
	{	
		err = SONIC_BitMarch_Err_in_bitWalk ;
		goto ErrorExit ;
	}

//	
// Test the transmit control register
//
	results->Reg_under_test = S_TXCONTROL;
	results->bitWalk16Params.wordPtr =  params->Sonic->regsStruct.Tx_Control;
	results->bitWalk16Params.dontWriteMask = 0xF000;
	results->bitWalk16Params.doWriteBits = 0x0000;
	results->bitWalk16Params.dontCareMask = 0xF000;
	results->bitWalk16Params.initialPattern = 0x0001;
	results->bitWalk16Params.finalValue = *(params->Sonic->regsArray[S_TXCONTROL]);
	results->bitWalk16Params.writeMethod = NULL;
	results->bitWalk16Params.readMethod = NULL;
	
	if ( 0 != SUP_BitWalk16(info, &results->bitWalk16Params, &results->bitWalk16Results) ) 
	{	
		err = SONIC_BitMarch_Err_in_bitWalk ;
		goto ErrorExit ;
	}

//
// Test the interrupt status register
//
	results->Reg_under_test = S_INTSTATUS;
	results->bitWalk16Params.wordPtr =  params->Sonic->regsStruct.Int_Status;
	results->bitWalk16Params.dontWriteMask = 0x0000;
	results->bitWalk16Params.doWriteBits = 0x7FFF;
	results->bitWalk16Params.dontCareMask = 0x7FFF;
	results->bitWalk16Params.initialPattern = 0x0001;
	results->bitWalk16Params.finalValue = 0x0000;
	results->bitWalk16Params.writeMethod = NULL;
	results->bitWalk16Params.readMethod = NULL;
	
	*(params->Sonic->regsArray[S_INTSTATUS]) = 0x7FFF;			
	if ( 0 != *(params->Sonic->regsArray[S_INTSTATUS])) 
	{	
		err = SONIC_BitMarch_Err_in_bitWalk ;
		goto ErrorExit ;
	}

//	
// Test the Upper and Current transmit descriptor address registers
//
	for( i = S_UTDA; i < (S_CTDA + 1); i++)
	{
		if ( 0 != BitWalk_a_No_By_Law_register(info, params, results,i)) 

		{	
			err = SONIC_BitMarch_Err_in_bitWalk ;
			goto ErrorExit ;
		}
	}

//
// Test the Transmit Packet Size Register 
// The data that is read from this register is the inversion of what has been written to it
//

	if ( 0 != BitWalk_data_inverted_register(info, params, results,S_TPS)) 

	{	
		err = SONIC_BitMarch_Err_in_bitWalk ;
		goto ErrorExit ;
	}


//	
// Test the Transmit Fragment Count and the Transmit Start Adress 0 and 1 registers
//
	for( i = S_TFC; i < (S_TSA1+1); i++)
	{
		if ( 0 != BitWalk_a_No_By_Law_register(info, params, results,i)) 

		{	
			err = SONIC_BitMarch_Err_in_bitWalk ;
			goto ErrorExit ;
		}
	}


//
// Test the Transmit Fragment Size Register 
// The data that is written to this register is shifted right once in 16 bit mode and twice in  32 bit mode
//
	temp_reg_data = *(params->Sonic->regsArray[S_DATACONFIG]);
	temp_reg_data = params->align_flag ? temp_reg_data | 0x0020 : temp_reg_data & 0xFFDF; /* Set up the data configuration register
												  to reflect the data width configuration */
	*(params->Sonic->regsArray[S_DATACONFIG]) = temp_reg_data ;
	
	if ( 0 != BitWalk_data_shifted_register(info, params, results,S_TFS)) 

	{	
		err = SONIC_BitMarch_Err_in_bitWalk ;
		goto ErrorExit ;
	}


//
// Test the Upper Receive descriptor address,current receive descriptor address,
// current receive buffer address 0 and 1,remaining buffer word addres 0 and 1 registers
// 
	for( i = S_URDA; i < (S_RBWC1+1); i++)
	{
		if ( 0 != BitWalk_a_No_By_Law_register(info, params, results,i)) 

		{	
			err = SONIC_BitMarch_Err_in_bitWalk ;
			goto ErrorExit ;
		}
	}


//	
// Test the End of byte count register
// Bit zero always equals zero
//
	
	i = S_EOBC;
	if ( 0 != BitWalk_a_bit0_equals_0_register(info, params, results,i) ) 
	{	
		err = SONIC_BitMarch_Err_in_bitWalk ;
		goto ErrorExit ;
	}


//
// Test the upper receive resource address register.
// 

	i = S_URRA;
	if ( 0 != BitWalk_a_No_By_Law_register(info, params, results,i)) 

	{	
		err = SONIC_BitMarch_Err_in_bitWalk ;
		goto ErrorExit ;
	}


//	
// Test the resource start address,resource end address,resource read pointer,
// and the resource write pointer registers
// Bit zero always equals zero
//
	
	for( i = S_RSA; i < (S_RWP+1); i++)
	{
		if ( 0 != BitWalk_a_bit0_equals_0_register(info, params, results,i) ) 
		{	
			err = SONIC_BitMarch_Err_in_bitWalk ;
			goto ErrorExit ;
		}
	}



//
// Test the temporary receive buffer address 0 and 1 registers and 
// the temporary buffer word count 0 and 1 registers
// Note that bit 0 of the temporary buffer word count 0 register always equals zero
// 
	for( i = S_TRBA0; i < (S_TBWC1+1); i++)
	{
		if ( 0 != ( i == S_TBWC0) ? BitWalk_a_bit0_equals_0_register(info, params, results,i) : BitWalk_a_No_By_Law_register(info, params, results,i)) 

		{	
			err = SONIC_BitMarch_Err_in_bitWalk ;
			goto ErrorExit ;
		}
	}


//	
// Test address generator 0 and 1 registers
// Bit zero always equals zero
//
	
	for( i = S_AG0; i < (S_AG1+1); i++)
	{
		if ( 0 != BitWalk_a_bit0_equals_0_register(info, params, results,i) ) 
		{	
			err = SONIC_BitMarch_Err_in_bitWalk ;
			goto ErrorExit ;
		}
	}


//
// Test the Last Link Field address register.
// 

	for( i = S_LLFA; i < (S_TTDA+1); i++)
	{
		if ( 0 != BitWalk_a_No_By_Law_register(info, params, results,i)) 
	
		{	
			err = SONIC_BitMarch_Err_in_bitWalk ;
			goto ErrorExit ;
		}
	}

//
// Test the CAM entry pointer register.
// This is a 4 bit register.
// 
	results->Reg_under_test = S_CAMEP;
	results->bitWalk16Params.wordPtr =  params->Sonic->regsStruct.CAM_Entry_Ptr;
	results->bitWalk16Params.dontWriteMask = 0x000F;
	results->bitWalk16Params.doWriteBits = 0x0000;
	results->bitWalk16Params.dontCareMask = 0x000F;
	results->bitWalk16Params.initialPattern = 0x0001;
	results->bitWalk16Params.finalValue = *(params->Sonic->regsArray[S_CAMEP]);
	results->bitWalk16Params.writeMethod = NULL;
	results->bitWalk16Params.readMethod = NULL;
	
	if ( 0 != SUP_BitWalk16(info, &results->bitWalk16Params, &results->bitWalk16Results) ) 
	{	
		err = SONIC_BitMarch_Err_in_bitWalk ;
		goto ErrorExit ;
	}

//
// In case your wondering the CAM address ports form a gateway to a memory block
// in SONIC called the Contents Addressable Memory. This can only be accessed 
// by means of a DMA operation. The purpose of this area is to allow SONIC to do 
// complete ethernet address filtering. For further info refer to the SONIC data book.
// The reason this is here, is that the CAM address ports are the next registers in line
// but these will be tested by the CAM DMA routine.
//



//
// Test the CAM enable register.
// 

	i = S_CAMENABLE;
	if ( 0 != BitWalk_a_No_By_Law_register(info, params, results,i)) 

	{	
		err = SONIC_BitMarch_Err_in_bitWalk ;
		goto ErrorExit ;
	}



//	
// Test the CAM descriptor pointer.
// Bit zero always equals zero
//
	
	i = S_CAMDP;
	if ( 0 != BitWalk_a_bit0_equals_0_register(info, params, results,i) ) 
	{	
		err = SONIC_BitMarch_Err_in_bitWalk ;
		goto ErrorExit ;
	}


//
// Test the CAM descriptor count register.
// This is a 5 bit register.
// 
	results->Reg_under_test = S_CAMDC;
	results->bitWalk16Params.wordPtr =  params->Sonic->regsStruct.CAM_Desc_Ptr ;
	results->bitWalk16Params.dontWriteMask = 0x001F ;
	results->bitWalk16Params.doWriteBits = 0x0000 ;
	results->bitWalk16Params.dontCareMask = 0x001F ;
	results->bitWalk16Params.initialPattern = 0x0001 ;
	results->bitWalk16Params.finalValue = *(params->Sonic->regsArray[S_CAMDC]) ;
	results->bitWalk16Params.writeMethod = NULL ;
	results->bitWalk16Params.readMethod = NULL ;
	
	if ( 0 != SUP_BitWalk16(info, &results->bitWalk16Params, &results->bitWalk16Results) ) 
	{	
		err = SONIC_BitMarch_Err_in_bitWalk ;
		goto ErrorExit ;
	}


//
// Test the watchdog timer 0 and 1 registers and the 
// receive sequence counter register
// 
	for( i = S_WDOG0; i < (S_RSC+1); i++)
	{
		if ( 0 != BitWalk_a_No_By_Law_register(info, params, results,i)) 

		{	
			err = SONIC_BitMarch_Err_in_bitWalk ;
			goto ErrorExit ;
		}
	}


//
// Test the CRC, Frame alignment and missed packet tally registers. 
// The data that is read from this register is the inversion of what has been written to it
//
	for( i = S_CRCERROR; i < (S_MISSEDPKT+1); i++)
	{
		if ( 0 != BitWalk_data_inverted_register(info, params, results,i)) 
	
		{	
			err = SONIC_BitMarch_Err_in_bitWalk ;
			goto ErrorExit ;
		}
	}


// If we get to here then all is OK, so return no error.
	err = SONIC_BitMarch_Err_Ok;
	
	ErrorExit :
		return(err);
}

