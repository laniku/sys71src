/*
	File:		input.c

	Contains:	This file contains the hardware specific user input routines for backlight control.

	Written by:	Andy Gong  x6595

	Copyright:	© 1991-1992 by Apple Computer, Inc.  All rights reserved.

    This file is used in these builds: ROM

	Change History (most recent first):

	   <SM1>	  2/11/93	CSS		Checked in from Horror.
		 <1>	  6/30/92	ag		new today
*/

/*page*/
/************************************/
/***  INCLUDE FILES DECLARATIONS  ***/


#include <SysEqu.h>
#include <types.h>
#include <errors.h>

#include "PowerMgr.h"
#include "backlight.h"



#define	READ_ATOD_CHANNEL	0xD8
#define	READ_BUTTON_VALUE	0xD9

extern short			PotInputRangeShiftTblPWM[];

/*page
 ***************************************************************************************************
 *
 *
 ***************************************************************************************************
 */

unsigned char Get_AtoD(int	channel)
{
	PMgrPBlock		pb;									/* power manager pb */
	char			atodChannel;						/* a to d channel to read [0-8] */
	unsigned char	value;								/* return value */
	OSErr			error;								/* pmgr error */


	atodChannel	= channel;								/* load channel value into buffer */

	pb.pmgrCmd	= READ_ATOD_CHANNEL;					/* load read channel command */
	pb.pmgrCnt	= 1;									/* transmit buffer count is 1 byte */
	pb.pmgrXPtr = &atodChannel;							/* pointer to transmit buffer */
	pb.pmgrRPtr = &value;								/* pointer to receive buffer */
	
	error = PMgr(&pb);

	return( (error) ? 0 : value);
};

/*page
 ***************************************************************************************************
 *
 *
 ***************************************************************************************************
 */

unsigned char Get_PGEButton(int	channel)
{
	PMgrPBlock		pb;									/* power manager pb */
	char			atodChannel;						/* a to d channel to read [0-8] */
	unsigned char	value;								/* return value */
	OSErr			error;								/* pmgr error */


	atodChannel	= channel;								/* load channel value into buffer */

	pb.pmgrCmd	= READ_BUTTON_VALUE;					/* load read channel command */
	pb.pmgrCnt	= 1;									/* transmit buffer count is 1 byte */
	pb.pmgrXPtr = &atodChannel;							/* pointer to transmit buffer */
	pb.pmgrRPtr = &value;								/* pointer to receive buffer */
	
	error = PMgr(&pb);

	return( (error) ? 0 : value);
};

/*page
 ***************************************************************************************************
 *
 *
 ***************************************************************************************************
 */
unsigned char GetPortableValues(int	parameter)
{

	PMgrPBlock		pb;									/* power manager pb */
	OSErr			err;								/* power manager error */
	unsigned char	rbuf[3];							/* buffer for send command */

	pb.pmgrCmd = BatteryStatusImmCmd;					/* on old pmgr, read battery status (immediate not averaged) */
	pb.pmgrCnt = 0;
	pb.pmgrXPtr = nil;
	pb.pmgrRPtr = rbuf;

	err = PMgr(&pb);
	return( (err) ? 0 : rbuf[parameter]);				/* return 0 if error, else read value */
}

/*page
 ***************************************************************************************************
 *
 *
 ***************************************************************************************************
 */
int PotControl (driverGlobalPtr	globalPtr)

{
#pragma	unused (globalPtr)

	unsigned int	potvalue;
	
	potvalue = (* (intFunction)(globalPtr->hardwareDependentPtr))();

	if (abs(globalPtr->lastatod - potvalue) <= 5) 		/* was the change less than 100mv */
		potvalue = globalPtr->lastatod;					/* is less than, the use old value */

	globalPtr->lastatod = potvalue;						/* update last a to d value */
	potvalue >>= 3;										/* scale to 0 to 31 */
	if (potvalue)										/* if non-zero, check for subrange limiting */
		{
		potvalue >>= PotInputRangeShiftTblPWM[globalPtr->powerRange]; /* rescale in low power levels */
		if (!potvalue) potvalue = 1;					/* make sure we don't change the backlight state */
		};
	return(potvalue);
};
