/*
	File:		input.c

	Contains:	This file contains the hardware specific user input routines for backlight control.

	Written by:	Andy Gong  x6595

	Copyright:	© 1991-1993 by Apple Computer, Inc.  All rights reserved.

    This file is used in these builds: ROM

	Change History (most recent first):

		 <1>	12/14/93	PN		first checked in
		<K2>	 7/27/93	ag		removed unused code.
		 <1>	 7/27/93	ag		first checked in
		 <1>	  6/30/92	ag		new today
*/

/*page*/
/************************************/
/***  INCLUDE FILES DECLARATIONS  ***/


#include <SysEqu.h>
#include <types.h>
#include <memory.h>
#include <OSEvents.h>
#include <devices.h>
#include <errors.h>
#include <retrace.h>
#include <Strings.h>
#include <Shutdown.h>
#include <stdlib.h>

#include "PowerMgr.h"
#include "backlight.h"



#define	READ_ATOD_CHANNEL	0xD8
#define	READ_BUTTON_VALUE	0xD9

#define Larger(x,y)			(x > y) ? x : y



/*page
 ***************************************************************************************************
 *
 * The generic control routine É
 *
 *	return:
 *		controlErr	- illegal control selector
 *
 ***************************************************************************************************
 */
OSErr BkltGenericControl(CntrlParam *ctlPB,driverGlobalPtr	globalPtr)

{
#pragma	unused (ctlPB,globalPtr)

	return(controlErr);
}

/*page
 ***************************************************************************************************
 *
 * The generic status routine É
 *
 *	return:
 *		statusErr	- illegal control selector
 *
 ***************************************************************************************************
 */
OSErr BkltGenericStatus(CntrlParam *ctlPB,driverGlobalPtr	globalPtr)

{
#pragma	unused (ctlPB,globalPtr)

	return(statusErr);
}
