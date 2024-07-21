/*
	File:		IDDefs.h

	Contains:	This file contains the ID definitions for all ROM
				CTE tests and subtests.

	Written by:	Joe Smyth

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).

	To Do:
*/

#ifndef _IDDefs_
#define _IDDefs_

//
// Enumerate the Test IDs.  Don't use zero!
//
enum myTestIDs
{
	USTMainTest_ID = 1,
	SONIC_Test_ID
} ;

//
// Enumerate the Subtest IDs.  Don't use zero!
//
enum mySubtestIDs
{
	SONIC_BitMarch_ID = 0x9B,
	SONIC_CAMDMA_ID,
	SONIC_Loopback_ID,
} ;


//
// Declare the Tests function names.
//
extern Test2 SONIC_Test ;

//
// Declare the Subtest function names.
//
extern Subtest SONIC_BitMarch ;
extern Subtest SONIC_CAMDMA ;
extern Subtest SONIC_Loopback ;

#endif 