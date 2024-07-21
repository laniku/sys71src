/*
	File:		PPCLoader.c

	Contains:	Code executed at patch install time.

	Copyright:	© 1989-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM6>	  3/9/93	PN		Remove ReQueueInformPB,Insert, Push,InitQueue, TraverseQueue
									which is no longer used
	   <SM5>	11/18/92	GMA		Set RomMapInsert to mapTrue before calling GetResource on 'ppci'
									-16409. we are trying to move these PACK9 resources into ROM
									eventually.
		<25>	 4/14/92	BBM		<JSM>: Remove unfinished PPC code that is under the contitional
									“TheFutute”, and remove the conditional “CubeE” since that is
									reality. Remove conditionals, since all they do is confuse.
		<24>	 10/4/91	JSM		Change PsychoticFarmerOrLater conditionals to TheFuture.
		<23>	 9/29/91	DTY		Conditionalize <21> and <22> out of CubeE.
		<22>	 6/10/91	EMT		Optimize code for size
		<21>	  6/4/91	EMT		Roll in StoreAndForward Revisions
		<20>	 1/22/91	EMT		VC: Move function initUserGroupFile to PPCInit.c.
		<19>	10/30/90	EMT		Modify the loader for the INITVERSION, to not kill the existing
									PPCToolBox for now, pre -B2 toolboxes choke bad when an unknown
									selector is given
		<18>	10/24/90	EMT		Add special case for init version to have the system version
									commit suicide, before superceeding
		<17>	10/11/90	EMT		Add conditionals around debug code
		<16>	 9/14/90	VC		Changed the typecast to "random" to an unsigned long.
									(nextUserRef is now an unsigned long).
	   <14+>	  9/4/90	EMT		Roll in Eric's changes
		<14>	 8/10/90	S		Made PPCToolBox name as resource.
		<13>	 7/10/90	dba		get rid of warnings for C
		<12>	 6/28/90	S		Improve dynamic allocation of ports and sessions.
		<11>	 6/12/90	JSM		Make PPC a linked patch:  can call Folder Mgr again, don't
									SetTrapAddress or install Gestalt and Shutdown routines here.
		<10>	  6/4/90	VC		Removed the call of initUserGroupFile.  Only set the refNum to
									0.  This will cause the B*Tree file called at the PPCInit time.
		 <9>	  6/1/90	VC		Added the FindFolder call in opening the User & Group file.
		 <8>	 4/25/90	S		To Measure memory consumption.
		 <7>	 4/18/90	JSM		No need to unlock configuration resource before releasing it,
									miscellaneous other code size reductions.
		 <6>	 4/17/90	JSM		Change initUserGroupFile interface to remove unused fields in
									BTFileInfo, #include String.h for definition of memset function,
									remove some local variables and #ifdef others in ppcLoader.
		 <5>	 4/11/90	S		To Fix Gestalt Function.
		 <4>	 4/10/90	S		Gestalt and PPC Global Check Box Support.
		 <3>	 3/21/90	S		To Get the Configuration from a resource.
	   <1.4>	10/30/89	csd		Remove the call of "SysEnvirons".
	   <1.3>	10/12/89	CCH		Fixed header
	  <•1.2>	10/12/89	CVC		Added Access control to the PPC toolbox
	   <1.1>	 9/25/89	ss		No Change from previous version.
	   <1.0>	 9/18/89	CVC		Adding PPC toolbox for the first time.

*/

#ifndef __PPCCOMMON__
#include  "PPCCommon.h"
#endif

#ifndef __GESTALTEQU__
#include <GestaltEqu.h>
#endif

#include <ShutDown.h>
#include <Resources.h>						// for mapTrue
#include <String.h>							// for memset definition

#define	ROMMapInsert	(* (short*) 0xB9E)	// <SM5><GMA>

/*---------------------------------------------------------------------------------------------------
	Prototypes of functions used only in this file.
---------------------------------------------------------------------------------------------------*/
STATIC void initAuth (PPCGlobalParamsPtr pGlobal);

/*----------------------------------------------------------------------------------------
	ppcLoader Performs first stage of PPCToolbox initialization.  We get our globals and
	initialize them.
----------------------------------------------------------------------------------------*/
void ppcLoader (void)
{
	Handle	configHdl;
	PPCGlobalParamsPtr globPtr;				// <23>
	PPCConfigInfo  *configPtr;
	
#ifdef INITVERSION	// Kill my brother, and take his place.
	{
		ProcPtr oldFunc;
		PPCRemove();
		ReplaceGestalt(gestaltPPCToolboxAttr,(ProcPtr)PPCGESTALTFUNCTION,&oldFunc);
	}
#endif

	if (globPtr = (PPCGlobalParamsPtr)setupGlobal(sizeof(PPCGlobalParams)))
	{
		memset(globPtr,0,sizeof(PPCGlobalParams));	// Clear our globals.
		
		ROMMapInsert = mapTrue;						// <SM5><GMA>
		if (( configHdl = GetResource ( 'ppci', -16409)) == NULL)
			return;
		configPtr = (PPCConfigInfo *)(*configHdl);
		configPtr->freeLocSessMin <<=1;
		configPtr->freeLocSessMax <<=1;

		BlockMove((Ptr)configPtr,(Ptr)&globPtr->configData,sizeof(PPCConfigInfo));
		ReleaseResource(configHdl);
		
		// This will be set in PPCInit by checking global flag
		globPtr->inited = false;			// <23>
		globPtr->allowIncommingRequests = false; // <23>
		Replenish(globPtr);					// Get Ports and Session Tables.
	
		initAuth(globPtr);					// <23>
	}
#ifdef DEBUG
	else
		Debugger(); // should not happen
#endif
}
	
/************************************************************************************
*			initAuth
************************************************************************************/
STATIC void initAuth (PPCGlobalParamsPtr pGlobal)
{
	long randnum;
	
	GetDateTime((unsigned long *)&randnum);
	if ((pGlobal->nextUserRef = (unsigned long)randnum) == 0)
		++pGlobal->nextUserRef;
}

