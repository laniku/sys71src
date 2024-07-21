/*
	File:		PWM.c

	Contains:	This file contains the hardware specific routines to control a PWM-based
				interface found on Asahi, TIM, DB-Lite.

	Written by:	Andy Gong  x6595

	Copyright:	© 1990-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	   <SM3>	 2/11/93	CSS		Update from Horror.  Comments follow:
	   <H10>	 6/30/92	ag		Moved cpu depended initialization code to cpu.c file, input
									routines to input.c, and table routines to backlight.c file.
		<H9>	 5/26/92	ag		Added write to PONTI to turnoff backlight through PONTI bit.
		<H8>	  5/7/92	ag		Use new table record for min/max limits. Added new entry for
									Dartanian.
		<H7>	 4/24/92	ag		set default to single table operation except on TIM (LC). added
									new vector for custom input control to handle hardware
									dependencies.
		<H6>	12/17/91	SWC		Added boxDBLiteLC to the list in InitPWMControls. Grouped boxTIM
									and boxDartanian since their code is identical.
		<H5>	12/16/91	HJR		Added boxDartanian to the list.
		<H4>	 9/10/91	SWC		Changed Get_AtoD to get the current setting of the up/down
									buttons.
		<H3>	 8/27/91	SWC		Changed references to get/set contrast to use get/set brightness
									on machines other than TIM. On TIM, they used the contrast
									command to control screen brightness. Added PWM table for
									DB-Lite.
		<H2>	  8/5/91	SWC		Changed Get_AtoD to use GetScreenCmd to get the current contrast
									instead of reading from the A-D if not on TIM.
		 <3>	 3/24/92	JSM		Nuke boxFlag codenames.
		 <2>	 3/23/92	JSM		OSEvents.h is obsolete, use Events.h.
		 <1>	10/24/91	SAM/KSM	Rolled in Regatta file.

									Regatta Change History:
								
									 <6>	 8/29/91	SAM		(ag) changed power manager call "BatteryStatusImmCmd" for more
																responsiveness.
									 <5>	 7/18/91	SAM		(ag) changed initialization code.  converted to table only brightness
																levels.
									 <4>	 6/30/91	SAM		Merged from TERROR [<4><5><6><7><8>].
									 <3>	 6/14/91	SAM		(ag) Turnoff backlight at close. Changed low power handling
																code, to rescale pot to lower range.
									 <1>	 5/15/91	SAM		Split off from TERRORProj.
								
									Terror Change History:
								
									 <8>	 6/27/91	ag		fixed bug with init powerbook 100, initialize table based data
																only on table based hardware.
									 <7>	 6/27/91	ag		centralize table determination code "LowTable".
									 <6>	 6/27/91	ag		code clean up.
									 <5>	 6/26/91	ag		added support for table change as a function of charger and
																voltage.
									 <4>	 6/24/91	ag		Changed look up table size to byte elements.  Added software
																scale control.  Added software setting controls.  Added software
																table control.
									 <3>	 6/10/91	ag		Changed low power handling code, to rescale pot to lower range.
									 <2>	  6/5/91	ag		turnoff backlight at close
*/

/*page*/
/************************************/
/***  INCLUDE FILES DECLARATIONS  ***/


#include <SysEqu.h>
#include <types.h>
#include <memory.h>
#include <Events.h>
#include <devices.h>
#include <errors.h>
#include <retrace.h>
#include <Shutdown.h>
#include <stdlib.h>

#include "PowerMgr.h"
#include "backlight.h"

/*page
 ***************************************************************************************************
 ** PWM software ***********************************************************************************
 ***************************************************************************************************
 */

OSErr InitPWMControls(driverGlobalPtr	globalPtr)

{
	unsigned int	startvalue;

	/* initialize dual table variables */
	if (globalPtr->dualTable) 
		{
		globalPtr->slewLimit		= true;				/* maximum change per/accrun */
		(*globalPtr->tableProc)(globalPtr);				/* determine table based on current charger state */
		};

	/* initialize backlight hardware */	
	startvalue 						= (*globalPtr->userInputProc)(globalPtr);				/* <H8> */
	globalPtr->userBrightness 		= -1;
	globalPtr->userBrightness 		= (*globalPtr->setlevelproc)(startvalue,globalPtr);		/* <H8> */
	
	return(noErr);
};

/*
 ***************************************************************************************************
 *
 *
 ***************************************************************************************************
 */
int PWMCloseRoutine (driverGlobalPtr	globalPtr)

{
	(*globalPtr->setlevelproc)(globalPtr->settingTable->minimum,globalPtr);
	return(0);
};

/*page
 ***************************************************************************************************
 *
 * The control routineÉ
 *
 *	return:
 *		noErr		- task completed successfully
 *		controlErr	- illegal control selector
 *
 *
 ***************************************************************************************************
 */
OSErr PWMControl(CntrlParam *ctlPB,driverGlobalPtr	globalPtr)		/* 'open' entry point */

{
	int 		error;
	int			tempvalue;

	error	= noErr;

	if (!globalPtr->disableHWinput)						/* if hardware not disabled, error */
		error = controlErr;
	else
		switch(ctlPB->csCode) 
			{
			case kSetScreenBrightness:					/* set brightness level */
				tempvalue = ctlPB->csParam[0];
				globalPtr->userBrightness 	= (*globalPtr->setlevelproc)(tempvalue,globalPtr);
				break;
				
			default:
				error = controlErr;
			};

	return(error);
};

/*
 ***************************************************************************************************
 *
 *
 ***************************************************************************************************
 */

int SetPWM(int	new,driverGlobalPtr	globalPtr)
{
	PMgrPBlock		pb;									/* power manager pb */
	unsigned char	val;								/* hardware value setting */
	
	PEG_TO_LIMITS(new, globalPtr->maximumTable[globalPtr->powerRange], globalPtr->settingTable->minimum);	/* <H8> use new tables */				/* limit value to valid range */
	val = globalPtr->settingTable->table[new];					/* look up value from table */

	if ((globalPtr->userBrightness >= 0) && (val == globalPtr->lastHWSetting)) return(new);/* nothing to do; 90/05/15 just turn on; 90/07/02 avoid touching */
	if (globalPtr->slewChange)
		{
		if (abs(globalPtr->lastHWSetting - val) > globalPtr->slewLimit)
			val = globalPtr->lastHWSetting + ((globalPtr->lastHWSetting > val) ? -globalPtr->slewLimit : globalPtr->slewLimit);
		else
			globalPtr->slewChange = false;
		};
	globalPtr->lastHWSetting	= val;					/* save the new hardware setting */

	pb.pmgrCmd					= SetBrightnessCmd;		/*  everyone else uses "set brightness" */
	pb.pmgrCnt					= 1;
	pb.pmgrXPtr 				= &val;
	pb.pmgrRPtr 				= nil;
	PMgr(&pb);											/* set the pwm */

	return(new);										/* return the current value */
};

