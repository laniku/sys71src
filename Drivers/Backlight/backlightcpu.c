/*
	File:		cpu.c

	Contains:	This file contains the hardware specific routines to control a PWM-based
				interface found on Asahi, TIM, DB-Lite.

	Written by:	Andy Gong  x6595

	Copyright:	© 1991-1992 by Apple Computer, Inc.  All rights reserved.

    This file is used in these builds: ROM

	Change History (most recent first):

	   <SM1>	 2/11/93	CSS		Checked in from Horror.
		 <1>	  6/5/91	ag		Moved data
*/

/*page*/
/************************************/
/***  INCLUDE FILES DECLARATIONS  ***/


#include <SysEqu.h>
#include <types.h>
#include <errors.h>

#include "PowerMgr.h"
#include "backlight.h"

#define	BACKLIGHT_POT_CHANNEL	0
#define STATUS					0
#define POWERBYTE				1
#define TEMPBYTE				2

/*page
 ===================================================================================================
 == asahi software =================================================================================
 ===================================================================================================
 */
 
/*page
 ***************************************************************************************************
 *
 *
 ***************************************************************************************************
 */
unsigned char	PortableBacklightValue()
{
	return(GetPortableValues(TEMPBYTE));
};

/*page
 ===================================================================================================
 == TIM software ===================================================================================
 ===================================================================================================
 */

OSErr InitTimControls(driverGlobalPtr	globalPtr)

{

	/* setup default values */
	if ((*JAWS_SPEED_FSTN_REG_PTR & JAWS_FSTN) == 0)
		globalPtr->dualTable = true;			/* support  high/low table */

	
	return(InitPWMControls(globalPtr));
};

/*page
 ***************************************************************************************************
 *
 *
 ***************************************************************************************************
 */
unsigned char	PowerMgrPot()
{
	return(Get_AtoD(BACKLIGHT_POT_CHANNEL));
};

/*page
 ===================================================================================================
 == DB software ====================================================================================
 ===================================================================================================
 */
/*page
 ***************************************************************************************************
 *
 *
 ***************************************************************************************************
 */
unsigned char	PGE_button()
{
	return(Get_PGEButton(BACKLIGHT_POT_CHANNEL));
};


/*page
 ===================================================================================================
 == Dart software  =================================================================================
 ===================================================================================================
 */

extern setTableType		BacklightTblDart;

/*page
 ***************************************************************************************************
 *
 *	SetDart - <H8> backlight set routine for Dartanian with Ponti ACIC
 *
 *
 ***************************************************************************************************
 */
int SetDart(int	new,driverGlobalPtr	globalPtr)
{
		unsigned char	newvalue;
		unsigned char	oldvalue;
		
		PEG_TO_LIMITS(new, globalPtr->maximumTable[globalPtr->powerRange], globalPtr->settingTable->minimum);	/* <H8> use new tables */				/* limit value to valid range */
		newvalue = globalPtr->settingTable->table[new];					/* shift bits into the correct position */
		if ((globalPtr->lastHWSetting) == newvalue) return (new);
		globalPtr->lastHWSetting = newvalue;

		newvalue <<= PONTILMPMUX0;										/* shift bits into the correct position */
		oldvalue = PONTILMPCTLREG;
		oldvalue &= ~(0x03 << PONTILMPMUX0 | 0x01 << PONTILMPON);		/* mask out lamp values */

		newvalue 			|= oldvalue;								/* or in the other bits into the new value */
		if (new) newvalue 	|=  (1 << PONTILMPON);						

		PONTILMPCTLREG = newvalue;
		
		return (new);
};

/*page
 ***************************************************************************************************
 *
 *	GetDart - backlight get routine for Dartanian with Ponti ACIC
 *
 ***************************************************************************************************
 */
int GetDart (driverGlobalPtr	globalPtr)
{
	int		userinput;
	
	switch(globalPtr->powerRange)
		{
		case 1:
		case 2:		userinput = 2; break;

		case 3:		userinput = 1; break;

		case 4:		userinput = 0; break;

		default:	userinput = 3;
		};
	return(userinput);
}

OSErr InitDartControls(driverGlobalPtr	globalPtr)

{

	/* setup default values */
	PONTILMPCTLREG |= 0x01 << PONTILMPON;					/* turn on backlight to enable sense bit */
	if (PONTILMPCTLREG & (0x01 << PONTILMPHWCTL))			/* check for hardare controls */
		{
		SetPWM(29,globalPtr);								/* kludge for orca based units */
		globalPtr->setlevelproc				= SetDart;		/* proc to set level */						
		globalPtr->userInputProc			= GetDart;		/* proc to read user input */
		};
	
	return(InitPWMControls(globalPtr));
};

