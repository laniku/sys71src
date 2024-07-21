/*
	File:		backlight.c

	Contains:	driver for backlight.

	Written by:	Andy Gong  x6595

	Copyright:	© 1990-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM6>	12/13/93	PN		Roll in KAOs and Horror changes to support Malcom and AJ
									machines
	   <SM5>	 9/2/93		SKH		Update from Horror.
	   <SM4>	 2/11/93	CSS		Update from Horror. Comments follow <H5-H2>:
		<H5>	 11/9/92	ag		Corrected compare statement. The compiler generated a long
									compare, so we must type cast the value to avoid the mismatch in
									types.
		<H4>	 6/30/92	ag		Use cpu info tables for configuring cpu dependent information.
		<H3>	 4/24/92	ag		added support for error returns on hardware initialization.
									this will return an open error on unknown hardware.
	    <H2>	  8/5/91	SWC		Make InitPWMControls the default init choice in DRVROpen so that
									proc vectors are always initialized.
		<12>	 3/30/92	JSM		Rolled this file into SuperMario project.
		<11>	 3/24/92	JSM		Nuke boxFlag codenames.
		<10>	 3/23/92	JSM		OSEvents.h is obsolete, use Events.h.
		 <9>	10/28/91	SAM		Rolled in Regatta file.
		
									Regatta Change History:

									 <9>	 8/19/91	SAM		“unused” and unused local var in Prime.
									 <8>	 8/19/91	SAM		(ag) Removed async bit clear
									 <7>	  8/8/91	SAM		(ag) fixed backlight driver to handle new box flags.
									 <6>     7/30/91	SAM		(ag) fixed low power dimming code in software only controls.
									 <5>	 7/18/91	SAM		(ag) convert async calls to sync calls, use box flag to determine
																hardware.
									 <4>	 6/30/91	SAM		Merged from TERROR [<10><11><12><13>].
									 <3>	 6/14/91	SAM		(ag) added init of backlight in open. fixed initialization code.
																passin new initializtion value which will tell the hardware
																specific code to initialize. Changed low power handling code,
																and added version number function in status. Reduce power on
																non-flybywire controlled hardware during low power.
									 <1>	 5/15/91	SAM		Split off from TERRORProj.
								
									Terror Change History:
								
									<13>	 6/26/91	ag		added support for table change as a function of charger and
																voltage.
									<12>	 6/25/91	ag		removed unused local variables.
									<11>	 6/25/91	ag		cleaned up vbl task.
									<10>	 6/24/91	ag		Cleaned up low power handling.  Added support for version status
																call, and table switching call.
									 <9>	 6/11/91	ag		reduce power on non-flybywire controlled hardware during low
																power.
									 <8>	 6/10/91	ag		Changed low power handling code, and added version number
																function in status.
									 <7>	 5/10/91	ag		fixed initialization code. passin new initializtion value which
																will tell the hardware specific code to initialize.
									 <6>	 4/23/91	ag		added init of backlight in open.
									 <5>	  4/2/91	ag		restructed driver for hardware independence.
									 <4>	 3/19/91	ag		change id of portable from gestalt call to rombase call.
									 <3>	 3/19/91	ag		Changed pram location of backlight setting to match the new parm
																layout.
									 <2>	  3/3/91	ag		changed base of pram locations, cleaned up open code, set error
																on fly-by-wire illegal selectors.
									 <1>	 1/23/91	ag		first checked in
								   <19+>	12/18/90	ag		code cleanup

		 <2>	 8/19/91	JSM		Use PmgrBase defined in PowerMgr.h, replace some defines with
									ones already in Power.h.
	  	<19>	11/13/90	ag		fix for ROM power manager changes
		<17>	 11/9/90	ag		changed default value
		<16>	 11/9/90	ag		changed default to off
		<15>	 11/9/90	ag		fixed low power vbl stuff, changed multiplier in strobe routine.
		<14>	 11/8/90	ag		change the storage method for the backlight value.  the 5 bits
									will now store the value of the backlight +1.  the +1 offset
									allows us to detect the first boot condition.  on the first
									boot, the pram will be initialize to default conditions, which
									is 0 the backlight pram location.  the macros have been adjusted
									to handle the offset invisable to the routines.
		<13>	90/11/07	ag		fixed bug with precheck of ram disk (include current disk )
		<11>	 9/26/90	ag		added change to set pot at ABSOLUTE minimum if backlight is set
									to off.  added remove code to close call.
		<10>	 9/25/90	ag		added universal support for different version of the backlight.
		 <9>	 9/12/90	ag		Added support for addition Control and Status calls.  Now
									installs a shutdown task to turn off the backlight on showdown
									and restart.
		 <8>	 8/29/90	ag		added support for backlight table lookup instead of straight
									values.
		 <7>	 8/23/90	ag		fixed key equivalent bug in driver.
		 <6>	 8/22/90	ag		added status & control calls, added dynamic maximum handling
				90/08/22	ag	added additional control and status calls
								added dynamic maximum handling
		 <3>	 8/15/90	ag	adding range feature to status call
				90/08/01	ag	adjust for CCFL backlight, pot adjust from 0 - 62
				90/07/27	ag	changed for fit the 3.0 c compiler and include files
				90/07/20	ag	changed the name and sense of vbl semaphore (now vbl_ok)
								changed universal routines to macros		
				90/03/14	ag	new today
	To Do:
*/

/*page*/
/************************************/
/***  INCLUDE FILES DECLARATIONS  ***/


#include <SysEqu.h>
#include <Types.h>
#include <Memory.h>
#include <Events.h>
#include <Devices.h>
#include <Errors.h>
#include <Retrace.h>
#include <Strings.h>
#include <Shutdown.h>
#include <StdLib.h>

#include "PowerMgr.h"
#include "backlight.h"


/**************************************/
/***  PRAM routines   				***/

pascal void ReadXPram		(short			startbyte,
							 short			numBytes,
							 char			*buffer)
	= {0x205F,0x201F,0xA051};


pascal void WriteXPram		(short			startbyte,
							 short			numBytes,
							 char			*buffer)
	= {0x205F,0x201F,0xA052};

/**************************************/
/***  LOCAL STRUCTURE DECLARATIONS  ***/



#define Larger(x,y)			(x > y) ? x : y

/****************************************/
/***  FORWARD ROUTINES DECLARATIONS  ***/


void 			VBLEntry();

				PowerChange  (driverGlobalPtr	globalPtr, int currentLevel);
				UserAdjust  (driverGlobalPtr	globalPtr);
				

cpuDependentInfoPtr	GetBkltPrimInfo();

/*page
 ***************************************************************************************************
 *
 * The open routine
 *
 *	return:
 *		noErr
 *		openErr
 *
 *
 ***************************************************************************************************
 */

pascal OSErr DRVROpen(CntrlParam *ctlPB,DCtlPtr dCtl)				/* 'open' entry point */

{
#pragma	unused (ctlPB)
	register driverGlobalPtr	globalPtr;							/* pointer to globals */
	PmgrGlobals					**pmgrglobalhdl;					/* handle to power manager globals */
	OSErr						error;
	cpuDependentInfoType 		*cpuinfo;
	OSErr						(*openProc)();
	
	cpuinfo = GetBkltPrimInfo();
	if (!cpuinfo) return(openErr);

  	globalPtr	= (driverGlobalPtr) NewPtrSysClear(sizeof(driverGlobaltypes));	
	if (!globalPtr) return(openErr);								/* not enough memory, return error */

	pmgrglobalhdl				= (PmgrGlobals **) 0x0D18;			/* handle to power manager globals */
	dCtl->dCtlStorage 			= (Handle) globalPtr;				/* set context to my global data area */

/* setup variables */
	globalPtr->version			= DRIVERVERSION;					/* driver version number, in globals for easy patching */

	*((unsigned int *)(((int)&(globalPtr->version)) + sizeof(globalPtr->version))) =  cpuinfo->bkltinfo->flags;
	globalPtr->lowThreshold			= cpuinfo->bkltinfo->lowThreshold; 		/*low hysteresis threshold */
	globalPtr->hiThreshold			= cpuinfo->bkltinfo->hiThreshold;			/* high hysteresis threshold */
	globalPtr->userInputSampleRate 	= cpuinfo->bkltinfo->userInputSampleRate;	/* sample every 160ms */

	globalPtr->lastLevel		= (*pmgrglobalhdl)->LastLevel;		/* get current power level */
//	globalPtr->userRange		= 0;								/* allow full power level */
	globalPtr->powerRange		= Larger(globalPtr->lastLevel,globalPtr->userRange);

/* initialize tables */	
	globalPtr->maximumTable			= (short *) (cpuinfo->bkltroutines->maxTable);							
	globalPtr->settingTableLow		= (setTableType *) (cpuinfo->bkltroutines->lowTable); /* <H8> */						
	globalPtr->settingTableHigh		= (setTableType *) (cpuinfo->bkltroutines->hiTable);	/* <H8> */						
	globalPtr->settingTable			= globalPtr->settingTableHigh;							

/* initialize vectors */	
	globalPtr->setlevelproc			= (intFunction) (cpuinfo->bkltroutines->setProc);			/* proc to set level */						
	globalPtr->userInputProc		= (intFunction) (cpuinfo->bkltroutines->getProc);		/* proc to read user input */
	openProc						= (osFunction) (cpuinfo->bkltroutines->open);	/* routine to close pwm hardware */
	globalPtr->closeProc			= (intFunction) (cpuinfo->bkltroutines->close);	/* routine to close pwm hardware */
	globalPtr->controlProc			= (osFunction) (cpuinfo->bkltroutines->control);		/* passed control routine */
	globalPtr->statusProc			= (osFunction) (cpuinfo->bkltroutines->status);	/* passed status routine */
	globalPtr->hardwareDependentPtr = (Ptr) (cpuinfo->bkltroutines->hwDependentVar);
	globalPtr->tableProc 			= (voidFunction) (cpuinfo->bkltroutines->tableProc);	


/* call custom initialization routine */	
	if (openProc) 
		{
		error = (*openProc)(globalPtr);
		if (error)
			{
			DisposPtr((Ptr) globalPtr);									/* release memory */
			dCtl->dCtlStorage 	= NULL;	
			return(error);												/* clear out saved value for next open */
			};
		};



	globalPtr->brightnessVbl.globals 			= (Ptr) globalPtr;
	globalPtr->brightnessVbl.vblpb.qType 		= vType;
	globalPtr->brightnessVbl.vblpb.vblAddr 		= (VBLProcPtr) VBLEntry;	/* cvbl is the address of the C routine */
	globalPtr->brightnessVbl.vblpb.vblCount 	= globalPtr->userInputSampleRate;
	globalPtr->brightnessVbl.vblpb.vblPhase 	= 0;
	VInstall((QElemPtr) &globalPtr->brightnessVbl.vblpb);			/* install vbl task */

	return(noErr);													/* if "you are here", we completed without error */
}

/*page
 ***************************************************************************************************
 *
 * The close routine.
 *		Release resources allocated and deinstall any install routines.
 *
 *	return:
 *		noErr
 *
 ***************************************************************************************************
 */

pascal OSErr DRVRClose(CntrlParam *ctlPB,DCtlPtr dCtl)			/* 'open' entry point */
{
#pragma	unused (ctlPB)
	register driverGlobalPtr	globalPtr;						/* pointer to driver globals */

	globalPtr			= (driverGlobalPtr) dCtl->dCtlStorage;	/* set context to my global data area */

	globalPtr->slewChange	= false;							/* always turn off slew during close <H6> */					
	VRemove((QElemPtr) &globalPtr->brightnessVbl.vblpb);		/* remove vbl task */
	if (globalPtr->closeProc != NULL) 							/* if hw close proc … */
		(*globalPtr->closeProc)(globalPtr);						/* … call close proc */
	DisposPtr((Ptr) globalPtr);									/* release memory */
	dCtl->dCtlStorage 	= NULL;									/* clear out saved value for next open */
	return(noErr);												/* exit without event */
}


/*page
 ***************************************************************************************************
 *
 * The prime routine…
 *
 *	return:
 *		ioErr
 *
 ***************************************************************************************************
 *
 */
pascal OSErr DRVRPrime(CntrlParam *ctlPB,DCtlPtr dCtl)			/* 'open' entry point */

{
#pragma	unused (ctlPB)
#pragma	unused (dCtl)
	return(ioErr);
}



/*page
 ***************************************************************************************************
 *
 * The control routine…
 *
 *	return:
 *		noErr		- task completed successfully
 *		controlErr	- illegal control selector
 *
 *
 ***************************************************************************************************
 */
pascal OSErr DRVRControl(CntrlParam *ctlPB,DCtlPtr dCtl)		/* 'open' entry point */

{
	int 						error;
	register driverGlobalPtr	globalPtr;
	int							tempvar;

	globalPtr	= (driverGlobalPtr) dCtl->dCtlStorage;			/* set context to my global data area */
	globalPtr->vbl_ok = false;		
	error	= noErr;
	switch(ctlPB->csCode) 
		{
		case kCdevActive:												
			globalPtr->disableHWinput = (ctlPB->csParam[0]) ? true : false;
			break;

		case kSetRange:												
			tempvar = ctlPB->csParam[0];						/* get the user range */
			PEG_TO_LIMITS(tempvar, kMaxRangeValue, kMinRangeValue); /* limit value to valid range */
			globalPtr->userRange		= tempvar;				/* set the user range */
			globalPtr->powerRange		= Larger(globalPtr->lastLevel,globalPtr->userRange); /* pick the higher range number */
			globalPtr->userBrightness	= (*globalPtr->setlevelproc)(globalPtr->userBrightness,globalPtr); /* adjust backlight with new range */
			break;

		case kSetTable:
			if (!globalPtr->dualTable) 
				{
				error = controlErr;
				break;					/* if only 1 table, nothing to do */
				};
			globalPtr->settingTable = (ctlPB->csParam[0])		/* set table lookup */
							? globalPtr->settingTableHigh		/* if non zero, use high value table */
							: globalPtr->settingTableLow;		/* if zero, use low value table */
			globalPtr->userBrightness	= (*globalPtr->setlevelproc)(globalPtr->userBrightness,globalPtr); /* adjust backlight with new range */
			break;
			
		default:
			error = (*globalPtr->controlProc)(ctlPB,globalPtr);	/* check for hw specific features */
		};
	globalPtr->vbl_ok = true;							

	return(error);
};


/*page
 ***************************************************************************************************
 *
 * The generic control routine …
 *
 *	return:
 *		controlErr	- illegal control selector
 *
 ***************************************************************************************************
 */
OSErr GenericControl(CntrlParam *ctlPB,driverGlobalPtr	globalPtr)

{
#pragma	unused (ctlPB,globalPtr)

	return(controlErr);
}


/*page
 ***************************************************************************************************
 *
 * The status routine…
 *
 *	return:
 *		noErr		- task completed successfully
 *		statusErr	- illegal control selector
 *
 ***************************************************************************************************
 */
pascal OSErr DRVRStatus(CntrlParam *ctlPB,DCtlPtr dCtl)			/* 'open' entry point */

{
#pragma	unused (dCtl)

	short 						error;							/* return value */
	register driverGlobalPtr	globalPtr;						/* pointer to driver global vars */


	error		= noErr;										/* start with no errors */
	globalPtr	= (driverGlobalPtr) dCtl->dCtlStorage;			/* set context to my global data area */

	globalPtr->vbl_ok = false;									/* disable vbl task */
	switch(ctlPB->csCode) 
		{
		case kGetUserInput:
			ctlPB->csParam[0] = globalPtr->
						userInputProc( globalPtr );				/* Get the button inputs	*/
			break;

		case KGetVersion:												
			ctlPB->csParam[0] = globalPtr->version;				/* return current driver version */
			break;

		case kGetScreenBrightness:								/* <H4> return current saved brightness */
			ctlPB->csParam[0] = globalPtr->userBrightness;
			break;

		case kGetBrightnessRange:								/* <H4> return range of brightness values */
			ctlPB->csParam[0] = globalPtr->settingTable->maximum;/* <H4> using new tables, return max setting */
			ctlPB->csParam[1] = globalPtr->settingTable->minimum;/* <H4> using new tables, return min setting */
			break;
		case kGetMaximum:										/* <H4> */
			ctlPB->csParam[0] = globalPtr->maximumTable[globalPtr->powerRange];
			break;

		default:
			error = (*globalPtr->statusProc)(ctlPB,globalPtr);
		};
	globalPtr->vbl_ok = true;							

	return(error);
}

/*page
 ***************************************************************************************************
 *
 * The generic status routine …
 *
 *	return:
 *		statusErr	- illegal control selector
 *
 ***************************************************************************************************
 */
OSErr GenericStatus(CntrlParam *ctlPB,driverGlobalPtr	globalPtr)

{
#pragma	unused (ctlPB,globalPtr)

	return(statusErr);
}

/*page
 ***************************************************************************************************
 *
 *	vbl task to periodically check for changes:
 *		1 - user input
 *		2 - power level changes
 *		3 - charger state changes
 *
 ***************************************************************************************************
 */
void VBL_Task(Ptr	pbPtr)

{

	PmgrGlobals					**pmgrglobalhdl;				/* handle to power manager globals */
	register driverGlobalPtr	globalPtr;						/* pointer to driver globals */
	int							currentPowerLevel;


	pmgrglobalhdl = (PmgrGlobals **) 0x0D18;					/* handle to power manager globals */
	globalPtr = (driverGlobalPtr) ( *(driverGlobalPtr *)(((unsigned long) pbPtr) - 4));
	globalPtr->brightnessVbl.vblpb.vblCount 	= globalPtr->userInputSampleRate;			/* reactivate the vbl element */

	if (globalPtr->vbl_ok == false) return;						/* if currently in use, don't touch */	

	/* check for charger change and table adjustment */
	if (globalPtr->tableProc) 
		(*globalPtr->tableProc)(globalPtr);						/* determine table based on current charger state */

	/* Check for hardware input */
	if (!globalPtr->disableHWinput)
		UserAdjust(globalPtr);									/* check for user adjustments */

	currentPowerLevel = (*pmgrglobalhdl)->LastLevel;				
	if ((currentPowerLevel != 2) && (globalPtr->lastLevel != currentPowerLevel)) 	/* check for power state change */
		PowerChange(globalPtr,currentPowerLevel);				/* adjust backlight to new power level */

	return;
};


/*page
 ***************************************************************************************************
 *
 *	procedure to check for user input.  calls hardware proc to read user input.  calls hardware proc to
 *	set level to user desired level.
 *
 ***************************************************************************************************
 */
UserAdjust  (driverGlobalPtr	globalPtr)
{
	int							userinput;						/* hardware control setting */
	int							oldBrightness;					/* current backlight setting */
	CntrlParam					controlpb;						/* iopb */

	oldBrightness	= globalPtr->userBrightness;				/* save the old value for comparison */
	userinput		= (*globalPtr->userInputProc)(globalPtr);	/* get user intput */
	globalPtr->userBrightness = (*globalPtr->setlevelproc)(userinput,globalPtr); /* set to level to user input */
		
	if (!globalPtr->flyByWire && (globalPtr->userBrightness != oldBrightness))	/* check for save of update */
		{
		controlpb.csCode = kSaveScreenBrightness;				/* save the setting in pram */
		(*globalPtr->controlProc)(&controlpb,globalPtr);		/* call hw save routine */
		};
};

/*page
 ***************************************************************************************************
 *
 *	procedure to handle changes in power levels.  if the power level is in reserved or if software 
 *	is artificially reducing the range of levels, this routine handles the initial change.
 *
 ***************************************************************************************************
 */
PowerChange  (driverGlobalPtr	globalPtr, int currentPowerLevel)

{
	int							userInput;						/* current user input setting */
	Boolean						lowerPower;						/* current power lower than last reading */

	lowerPower 	= (globalPtr->lastLevel < currentPowerLevel);	/* is the new power state lower than before */
	globalPtr->lastLevel 	= currentPowerLevel;				/* save the current level */
	globalPtr->powerRange	= Larger(globalPtr->lastLevel,globalPtr->userRange);
	
	userInput = (*globalPtr->userInputProc)(globalPtr);			/* get adjusted user input */
	if (lowerPower && currentPowerLevel)						/* if power down and maximum changed , take action */
		{
		if (!globalPtr->flyByWire && userInput)					/* if only software controls and backlight on */
			{
			userInput >>= 1;									/* reduce power by 1/2 */
			if (!userInput) userInput = 1;						/* insure at least on */
			};
		};
	globalPtr->userBrightness 	= (*globalPtr->setlevelproc)(userInput,globalPtr);
};

/*page
 ***************************************************************************************************
 *
 *
 ***************************************************************************************************
 */

/*page
 ***************************************************************************************************
 *
 *
 ***************************************************************************************************
 */
unsigned int LowTable  (driverGlobalPtr	globalPtr)

{
	PmgrGlobals					**pmgrglobalhdl;				/* handle to power manager globals */
	Boolean						wasLowTable;					/* current table being used */
	Boolean						hiTable;						/* use hi level table  now */

	pmgrglobalhdl 	= (PmgrGlobals **) 0x0D18;					/* handle to power manager globals */

	wasLowTable		= globalPtr->lowTable;						/* current table */
	hiTable 		= false;									/* assume low table */
	if ((wasLowTable && ((*pmgrglobalhdl)->BatAvg >= globalPtr->hiThreshold)) ||
		(!wasLowTable && ((*pmgrglobalhdl)->BatAvg >= globalPtr->lowThreshold)))
		{
		hiTable = (*pmgrglobalhdl)->Charger & 0x01;				/* qualify table with charger */
		};
	return(hiTable ? 0 : 1);									/* return 1 if low table, 0 if high */
};

/*page
 ***************************************************************************************************
 *
 *
 ***************************************************************************************************
 */
void ChargerAdjust  (driverGlobalPtr	globalPtr)
{		
	unsigned int				oldTable;

	oldTable			= globalPtr->lowTable;					/* save the current table being used */
	globalPtr->lowTable =  LowTable(globalPtr);					/* get the new table to use */
	if (globalPtr->lowTable == oldTable) return;				/* are we changing tables ???, no exit */

	globalPtr->slewChange		= true;							/* if change, set tmp slew on */					
	globalPtr->settingTable		= globalPtr->lowTable ? globalPtr->settingTableLow :globalPtr->settingTableHigh ;							
};

