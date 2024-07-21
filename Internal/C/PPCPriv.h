/*
	File:		PPCPriv.h

	Contains:	Calls used by Sharing Setup Control Panel and other places

	Written by:	Eric M. Trehus

	Copyright:	© 1990-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<11>	 4/15/92	JSM		Get rid of all the theFuture and CubeE conditionals, the future
									is the same as CubeE for now.
		<10>	 10/4/91	JSM		Change PsychoticFarmerOrLater conditionals to TheFuture.
		 <9>	 9/29/91	DTY		Conditionalize out <7> and <8> for CubeE.
		 <8>	 8/27/91	JSM		Cleanup header.
		 <7>	 6/10/91	EMT		Optimize code for size
		 <6>	 1/22/91	EMT		VC: Add an internal error code for use by the Sharing setup
									extension
		 <5>	10/24/90	EMT		Add prototypes for PPCEnable and PPCDisable
		 <4>	 9/15/90	JSM		PPCCheckDupNBPName is a C routine, not Pascal.
		 <3>	 8/10/90	S		Change internal interface to C.
		 <2>	  8/6/90	S		Included PPCCheckDupNBPName definition.
		 <1>	 5/30/90	EMT		2 new calls to aid the Network setup window in abolishing
									connections with the undesirables

*/

#ifndef __PPCPRIV__
#define __PPCPRIV__

#ifndef __TYPES__
#include <Types.h>
#endif

#define	noUserGroupErr -901	// Couldn't enable PPC because the user group file couldn't be opened.

/*---------------------------------------------------------------------------------------------------
	PPCCloseUserSessions will close all session for a particular user, for guest, the
	string is <Guest>, for all users that established a session, pass NULL.
---------------------------------------------------------------------------------------------------*/

OSErr PPCCloseUserSessions(unsigned char *userName);

/*---------------------------------------------------------------------------------------------------
	PPCCountAcceptedNetworkSessions has same calling conventions as PPCCloseUserSessions, but
	it provides a count of the number of sessions that will be affected.
---------------------------------------------------------------------------------------------------*/

short PPCCountAcceptedNetworkSessions(unsigned char *userName);

/*---------------------------------------------------------------------------------------------------
	PPCCheckDupNBPName determins if another machine in our zone has the same object name as our
	machine name
---------------------------------------------------------------------------------------------------*/
OSErr PPCCheckDupNBPName(void);

/*---------------------------------------------------------------------------------------------------
	PPCEnable tells PPC to enable the incomming requests if possible.  This could return a possible
	error of noUserGroupErr.
---------------------------------------------------------------------------------------------------*/
OSErr PPCEnable(void);

/*---------------------------------------------------------------------------------------------------
	PPCDisable tells PPC to disable the incomming requests if possible.  This also
	performs the PPCCloseUserSessions call above as an added bonus.
---------------------------------------------------------------------------------------------------*/
OSErr PPCDisable(void);

#endif // End of wrapper.