/*
	File:		SONIC_Test.h

	Contains:	This is the include file for the SONIC test.

	Written by:	Joe Smyth

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).
		<1.01>    1/9/92     KL  Added support for Carnation

	To Do:
*/

#ifndef _CTEFool_SONIC_Test2_
#define _CTEFool_SONIC_Test2_
//
//	CTEFool_SONIC_Test2.h
//

#ifndef _CTETypes_
#include <CTETypes.h>
#endif _CTETypes_

#include <TestParameters.h>

#include "SONIC_Common.h"


// Masks for the testParams->modifier
#define SONIC_NoOSCallsMask		0x80000000	// If the high bit of the modifier is set, then don't do OS calls.


// I had to add this because wasn't defined in the Gestalt.h file that is
//	in Horror or anywhere else (it is defined in various .a files)
//	AARON	AARON
#define gestaltCarnation		28


#define kindOfGestaltBuccaneer		90		// Sean's hacked gestalt define for bucky
#define kindOfGestaltCiPDS		91		// Sean's hacked gestalt define for ciPDScard
#define kindOfGestaltCiPDSold		92		// Sean's hacked gestalt define for ciPDScard old PAL version


#define	Eclipse_Sonic_base		0x50F0A000	// Eclipse and Spike
#define	Spike_Sonic_base		0x50F0A000	// Spike
#define	Buccaneer_Sonic_base		0x50F2A000	// Buccaneer Sonic Base address
#define	ci_PDS_Sonic_base		0x50F32100	// ci PDS card new pals
#define	ci_PDS_old_Sonic_base		0x53000000	// ci PDS card old pals
#define	Carnation_Sonic_base		0x5000A000	// Carnation


#define ci_PDS_SONIC_Interrupt_Level	3		// ci PDS card modified scheme
#define Eclipse_SONIC_Interrupt_Level	3		// Eclipse SONIC interrupt level -> under A/UX mode interrupts (See Note below)
#define Spike_SONIC_Interrupt_Level	3		// Spike SONIC interrupt level -> under A/UX mode interrupts (See Note below)
#define Carnation_SONIC_Interrupt_Level	3		// Carnation interrupt level

//
// CTEFool_SONIC_Test2 error return values.
//
enum CTEFool_SONIC_Test2_Error
{
	CTEFool_SONIC_Test2_Err_Ok,
	CTEFool_SONIC_Test2_Err_Unexpected = 0x10000,
	CTEFool_SONIC_Test2_Unknown_Machine,

} ;
typedef enum CTEFool_SONIC_Test2_Error CTEFool_SONIC_Test2_Error ;

//
// CTEFool_SONIC_Test2 parameter block.
//
typedef StdTestParams CTEFool_SONIC_Test2_Params ;

//
// CTEFool_SONIC_Test2 result block.
//
struct CTEFool_SONIC_Test2_Results
{
	LONG dummy ;
} ;
typedef struct CTEFool_SONIC_Test2_Results CTEFool_SONIC_Test2_Results ;


// Function prototype for the Test.
Test2 SONIC_Test ;

#endif _CTEFool_SONIC_Test2_