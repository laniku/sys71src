/*
	File:		PPCInit.c

	Copyright:	© 1989-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <6>	  7/2/93	IH		Reality Update: Change Gestalt call to use
									SelectorFunctionProcPtr.
		<62>	10/28/92	DTY		Use new Get/Set macros to access ExpandMem.
		<61>	  6/8/92	JSM		For TheFuture, check emProcessMgrExists global instead of
									calling Gestalt all the time in initUserGroupFile().
		<60>	 4/17/92	JSM		Don’t ever check to see whether to return
									gestaltPPCSupportsStoreAndForward in PPCGESTALTFUNCTION(), it
									will never happen for CubeE.
		<59>	 4/14/92	BBM		<JSM>: Remove unfinished PPC code that is under the contitional
									“TheFutute”, and remove the conditional “CubeE” since that is
									reality. Remove conditionals, since all they do is confuse.
		<58>	 10/4/91	JSM		Change PsychoticFarmerOrLater conditionals to TheFuture.
		<57>	 9/30/91	DTY		Dean’s in the dog house. The System build got derailed with that
									last change.
		<56>	 9/29/91	DTY		Conditionalize <54> and <55> out of CubeE.
		<55>	 6/10/91	EMT		Optimize code for size
		<54>	  6/4/91	EMT		Roll in StoreAndForward Revisions
		<53>	  2/1/91	EMT		VC: Fix bug <52> that calls MultiFinder Begin and End System
									mode without checking to see if it is implemented first. Also
									moved call to GetIndString after it has been determined that we
									need to open the users and groups b-tree.
		<52>	 1/27/91	csd		gbm: Begin and End System Mode around the call to OpenUGBT so
									that the Users & Groups Data File doesn’t get closed when the
									active process terminates.
		<51>	 1/25/91	EMT		VC: GSM-089, Fix problem that prevents PPC from opening the .MPP
									driver when the portable wakes up.
		<50>	 1/24/91	EMT		VC: Fix problem in startup that prevents PPC from allowing
									incomming requests.  Found and fixed problem that could lead to
									system hanging.
		<49>	 1/22/91	EMT		VC: Fix bug that prevents processing of Transition Event. Move
									initUserGroupFile from PPCLoader.c to this file, and fix bug in
									same procedure.
		<48>	  1/2/91	EMT		<VC> Fix bug that registers name, on name change event when PPC
									is not network enabled.
		<47>	12/14/90	EMT		<VC> Fix bug in examining of FlagShip attributes returned from
									gestalt.
		<46>	12/13/90	EMT		<JSM> Support FlagShip name changes.
		<45>	11/28/90	EMT		<VC> Update AtalkEvent procedure to work with the about to close
									event message. Remove obsolete GetMyAtalkZone procedure.
		<44>	11/15/90	EMT		<stb> Fix bug in PPCGetstaulFunction.
		<43>	 11/8/90	EMT		<stb> Fix KillUserSession and PPCCountAcceptedNetworkSessions to
									use the same string comparison routines as the BTreeManager.
		<42>	 11/6/90	EMT		use STATIC in place of static for link maps
		<41>	10/30/90	EMT		Fix EnableIncoming
		<40>	10/24/90	EMT		Change some calls to be an internal interface for enabling IAC
									and Disabling IAC. Found and fixed bug in Gestault.
		<39>	10/18/90	EMT		Change userName to machineName where needed
		<38>	10/11/90	EMT		Make changes to support the obsoleting CompletionGlue.a
	   								Changed how PPC works with Network Setup Control Pannel.
									PPC no-longer get gestault, since if MPP can't be open,
									the version number is wrong.  We will assume we are
									running with the correct version of AppleTalk.
		<37>	10/10/90	gbm		change ioCRefNum of ioRefNum
		<36>	 10/4/90	EMT		Temporary Hack, make SetupToolBoxName always check for other
									machines with objects in the same zone
		<35>	 10/4/90	EMT		Fix bug in ObjectInMyZone
		<34>	 10/4/90	EMT		Fix PPCCheckDupName so that it does not report duplicate name
									when self send is on, and the name exists on this machine. Also
									fix bug that caused name not to be registered when changed in
									the network setup control pannel.
		<33>	 9/21/90	EMT		Update constants, types, and field names as dictated by
									PPCToolBox.h
		<32>	 9/14/90	EMT		Add changes to re-register locnames with correct object when it
									changes
		<31>	  9/6/90	EMT		Fix bug in PPCInit that return's a bogas result code.
	    <30>	  9/4/90	EMT		Eric's Changes rolled in
		<29>	 8/21/90	EMT		Fix Shutdown bug for SE with router.
		<28>	 8/13/90	S		Bug Fix Related Checking Duplicate Network Name.
		<27>	 8/10/90	gbm		get rid of “unused local variable” warning in SetToolBoxName
		<26>	 8/10/90	gbm		fix power manager attribute test for sleep proc install
		<25>	 8/10/90	S		Change CountAcceptedNetworkSessions to pascal interface
		<24>	  8/8/90	S		Fixed Portable Problem & CountAcceptedSessions Problem.
		<23>	  8/6/90	S		Some more Bug Fixes.
		<22>	  8/6/90	S		Bug Fixes.
		<21>	 7/10/90	dba		get rid of C warnings
		<20>	  7/2/90	S		Fix a bug in Dynamic allocation for seeions.
		<19>	 6/28/90	S		To Improve Dynamic allocation and fix other bugs.
		<18>	 6/12/90	JSM		Make PPC a linked patch: OpenUGBT is back in PPCLoader.c.
		<17>	  6/4/90	VC		Make the OpenUGBT call if it is not already opened.
		<16>	 5/31/90	EMT		Support force ending of sessions that did not originate from
									host machine.
		<15>	 4/25/90	S		Implement Expansion and deletion of Port and Session Tables in
									PPCSystemTask.
		<14>	 4/24/90	S		To Include PPCSystemTask Procedure.
		<13>	 4/18/90	JSM		Add prototype for BTSEARCHPPC, use Gestalt instead of
									SysEnvirons to get AppleTalk version, fix bug in PPCSetup where
									err was checked before being initialized (it's unlikely this
									would ever have been hit), don't HLock things for BlockMove,
									miscellaneous other code size reductions.
		<12>	 4/11/90	S		To Fix Gestalt and add to ShutDown Que for Closing AppleTalk
									Driver.
		<11>	 4/10/90	S		Gestalt and Global PPC Check box support.
		<10>	 3/21/90	S		To use the configuration parameters.
		 <9>	 3/20/90	S		Bug Fix
		 <8>	 3/20/90	S		To Fix AppleTalk Inactive to active Transition work.
		 <7>	 2/13/90	S		Fix problem with AtalkEvent Checcking.
		 <6>	  2/8/90	S		Removed Debugger Statement from AtakEvent routine.
		 <5>	  2/7/90	S		Fix the zoneName, when getMyZone fails.
		 <4>	 1/23/90	S		Change Resource ID t0 -16413  to obtain Macintosh name for
									PPCLocation for ToolBox registration with NBP.
		<2+>	  1/5/90	S		Some Error Codes
		 <2>	12/28/89	dba		use quotes around the names of local header files, angle
									brackets around the names of header files from Interfaces or
									Internals
	   <1.6>	 11/7/89	CVC		Changed PPCInit to not register blank name
	   <1.5>	10/12/89	CCH		Fixed header
	  <•1.4>	10/12/89	CVC		Added access control stuff
	   <1.3>	 9/25/89	ss		Added netErr falg and changed err returned to LocalOnly
	   <1.2>	 9/18/89	CVC		no change from 1.1
	   <1.0>	 9/18/89	CVC		Adding PPC toolbox for the first time.

	   
	   Old Revision History:

		05/30/89 	Sangam	    New Today
		07/20/89    Sangam      1.0d2 release today!
		09/07/89	Sangam		Added Appletalk Phase2 Transition Routines
								so that Network can be switched dynamicallly.
		09/18/89    Sangam      Added netErr flag and changed err returned to LocalOnly
		09/27/89	Victor      Added 'initAuth' call to initialize the Authentication stuff.
		10/09/89	Sangam		Changes to handle the absence of bridge, call initauth when
								btree is not opened.
		10/12/89	Victor		Removed the 'initAuth' call.  moved it to ppcLoader.c

*/

#include "PPCCommon.h"
#include <PPCPriv.h>
#include "UserGroup.h"

#include <Errors.h>
#include <GestaltEqu.h>
#include <ShutDown.h>
#include <Packages.h>
#include <Power.h>
#include <String.h>
#include <Folders.h>
#include <MFPrivate.h>																		/* <52> */

#if TheFuture
#include <ExpandMemPriv.h>																	/* <61> */
#endif

/*----------------------------------------------------------------------------------------
	Prototypes of functions used only in this file.
----------------------------------------------------------------------------------------*/
STATIC void EndAllNetworkSessions(PPCGlobalParamsPtr ppcglobPtr);
STATIC OSErr AtalkEvent(long theEvent, ATQEntry *qElem, StringPtr newName);
STATIC OSErr EnableIncoming(void);
STATIC OSErr DisableIncoming(void);
STATIC void initUserGroupFile(short *refNum);
STATIC void RemoveConnectionListeners(PPCGlobalParamsPtr ppcglobPtr);
STATIC OSErr SetUpToolBoxName(PPCGlobalParamsPtr ppcglobPtr);
STATIC OSErr RemoveToolBoxName(PPCGlobalParamsPtr ppcglobPtr);
STATIC OSErr SetUpConnectionListeners(PPCGlobalParamsPtr ppcglobPtr);
STATIC long PPCSleepEvent(void);
STATIC Boolean GetPPCGlobalFlag(PPCGlobalParamsPtr ppcglobPtr);

STATIC void EndAllNetworkSessions(PPCGlobalParamsPtr ppcglobPtr);
STATIC Boolean KillUserSession(CommonSessionParamsPtr sessPtr,unsigned char *userName);

STATIC OSErr ObjectInMyZone(Str32 Object);

STATIC void UnRegisterAllNBPNames(PPCGlobalParamsPtr ppcglobPtr);
STATIC void ReRegisterAllNBPNames(PPCGlobalParamsPtr ppcglobPtr);

/*----------------------------------------------------------------------------------------
	PPCSetUp is actually the code that is executed when PPCInit() call is made.
----------------------------------------------------------------------------------------*/

OSErr PPCSetUp(void)
{
	PPCGlobalParamsPtr		ppcglobPtr;
	PPCConfigInfo			*configPtr;	// <56>
	long					powerMgrAttrs;

	if (!(ppcglobPtr = (PPCGlobalParamsPtr)getGlobal()))
		return noGlobalsErr;

	if (!ppcglobPtr->inited)
	{
		ppcglobPtr->canLocal = true;	// This is always the case.
	    configPtr = (PPCConfigInfo  *)&(ppcglobPtr->configData); 

		ppcglobPtr->nextPortRefNum = 1;
		ppcglobPtr->nextSessRefNum = 1;
		ppcglobPtr->dspDrvrRef = 0;
		ppcglobPtr->listsessPtr = NULL;
		BlockMove(*GetResource('STR ', -16413), ppcglobPtr->machineName, sizeof(Str32));
		if(!MPPOpen())	// If AppleTalk is enabled.
		{
			ppcglobPtr->mppOpen = true;
			ppcglobPtr->canRemote = true;

			if(OpenADSPDriver(&ppcglobPtr->dspDrvrRef))
			{
				ppcglobPtr->dspDrvrRef = 0;
				ppcglobPtr->canRemote = false;
			}
			else if(GetPPCGlobalFlag(ppcglobPtr))
			{
				EnableIncoming();
			}
		}

		ppcglobPtr->trQEle.CallAddr = (ProcPtr)AtalkEvent;
		AddtoAtalkQ((Ptr)&(ppcglobPtr->trQEle));
		
		if (!Gestalt(gestaltPowerMgrAttr, &powerMgrAttrs))
		{
			if ((powerMgrAttrs & 1<<gestaltPMgrExists) &&						// <26>
				(powerMgrAttrs & 1<<gestaltPMgrCPUIdle))						// <26>
			{

				ppcglobPtr->sleepQEle.sleepQProc = (ProcPtr)PPCSleepEvent;
				ppcglobPtr->sleepQEle.sleepQType = SleepQueType;
				SleepQInstall((SleepQRecPtr)&ppcglobPtr->sleepQEle);
			}
		}
		ppcglobPtr->inited = true;
	}
	return(noErr);
} // PPCSetUp

/*----------------------------------------------------------------------------------------
	AtalkEvent handle the AppleTalk Transition Queue.
----------------------------------------------------------------------------------------*/
STATIC OSErr AtalkEvent(long theEvent, ATQEntry *qElem, StringPtr newName)
{
#pragma unused(qElem)
	PPCGlobalParamsPtr   	ppcglobPtr;
	OSErr Result;

	ppcglobPtr = (PPCGlobalParamsPtr)getGlobal();

	if (theEvent == AOpenTask)			// MPP Driver is opening.
	{
		ppcglobPtr->mppOpen = true;
		ppcglobPtr->canRemote = true;
		if(OpenADSPDriver(&ppcglobPtr->dspDrvrRef))
		{
			ppcglobPtr->dspDrvrRef = 0;
			ppcglobPtr->canRemote = false;
			return(noErr);
		}
		else if(GetPPCGlobalFlag(ppcglobPtr))
		{
			EnableIncoming();
		}
	}
	else if (theEvent == ACloseAskTask)	// MPP Driver is about to close.
	{
		return(ppcglobPtr->RemSessQueue.qSize?1:0);	// Object if we are currently networking.
	}
  	else if (theEvent == ACloseTellTask)	// MPP Driver just closed.
	{
		if(ppcglobPtr->allowIncommingRequests)
			DisableIncoming();
		EndAllNetworkSessions(ppcglobPtr);
		ppcglobPtr->mppOpen = false;
		ppcglobPtr->canRemote = false;
		ppcglobPtr->dspDrvrRef = 0;
	}
	else if(theEvent == ANameChangeTellTask)	// Machine name changed.
	{
		BlockMove(newName, ppcglobPtr->machineName, sizeof(Str32));	// This is now our primary name.
		if(ppcglobPtr->allowIncommingRequests)
		{
			RemoveToolBoxName(ppcglobPtr);						// Remove the old PPCToolBox name.
			ppcglobPtr->whichName ^= 1;							// we switched names.
			ppcglobPtr->AltNameRegistered = false;				// alt name is now the primary.
			UnRegisterAllNBPNames(ppcglobPtr);					// Remove our clients alias names.
			ReRegisterAllNBPNames(ppcglobPtr);					// Register our clients alias names.
		}
	}
	else if (ppcglobPtr->allowIncommingRequests)	// Ignore Name events if we don't allow incoming requests.
	{
		if (theEvent == ANameChangeAskTask)	// Register the new name.
		{
			NBPparms NBPPB;

			Result =  RegisterName(newName,
								   ppcglobPtr->configData.ppctoolboxName,
								   "\p*",
								   ppcglobPtr->adspSocket,
								   false,		// Call Syncronously
								   nil,			// No Completion Routine
								   (Ptr)&ppcglobPtr->nteQEle[ppcglobPtr->whichName ^ 1], // ntePtr
								   &NBPPB); 	// PB for NBP call
	
			if(!Result)
				ppcglobPtr->AltNameRegistered = true;
			return(Result);
		}
		else if (theEvent == ACancelNameChange)
		{
			NBPparms NBPPB;
			if(ppcglobPtr->AltNameRegistered)
			{
				RemoveName((EntityName *)ppcglobPtr->nteQEle[ppcglobPtr->whichName ^ 1].nt.entityData,
						   false,
						   (ProcPtr)nil,
						   &NBPPB); 			// PB for NBP call
				
				ppcglobPtr->AltNameRegistered = false;	// Even if this fails, it should be OK to set this false.
			}
		}
	}
    return(noErr);
} // AtalkEvent


/*----------------------------------------------------------------------------------------
	EnableIncoming is called when in the Network Setup Control Pannel, the user enables
	IAC for incoming requests.  If the process fails, we will DisableIncoming.  NOTE:
	Sharing setup does not set the global flag before calling EnableIncoming.  For that
	reason we don't examine the flag here.  Be sure to call GetPPCGlobalFlag to find out
	if it is safe to call EnableIncoming.
----------------------------------------------------------------------------------------*/
OSErr EnableIncoming(void)
{
	PPCGlobalParamsPtr ppcglobPtr;
	OSErr Result;
	
	if (ppcglobPtr = getGlobal())
	{
		if(ppcglobPtr->allowIncommingRequests)	// An ounce of prevention is worth a beta cycle.
			return(noErr);	// Someone is confused about my state, but I will just humor them.
			
		if(ppcglobPtr->mppOpen)
		{
			initUserGroupFile(&ppcglobPtr->ugFile.refNum);
			if(ppcglobPtr->ugFile.refNum)	// Can we access the user group file
			{
				if(Result = SetUpConnectionListeners(ppcglobPtr))
				{
					DisableIncoming();			// <56>
					return(Result);				// <56>
				}		
				if(Result = SetUpToolBoxName(ppcglobPtr))
				{
					DisableIncoming();			// <56>
					return(Result);				// <56>
				}
				ppcglobPtr->allowIncommingRequests = true;
				ReRegisterAllNBPNames(ppcglobPtr);
			}
			else
			{
				DisableIncoming();
				return(noUserGroupErr);
			}
		}
		else // Driver isn't open, so we attempt to open it.
		{
			Result = MPPOpen();
		}
		return(Result);
	}
	else
		return(noGlobalsErr);
}

/*----------------------------------------------------------------------------------------
	DisableIncoming is called when in the Network Setup Control Pannel, the user disables
	IAC for incoming requests.
----------------------------------------------------------------------------------------*/
OSErr DisableIncoming(void)
{
	PPCGlobalParamsPtr ppcglobPtr;
	
	if (ppcglobPtr = getGlobal())
	{
		ppcglobPtr->allowIncommingRequests = false;
		RemoveToolBoxName(ppcglobPtr);			// Remove the default port location name.
		UnRegisterAllNBPNames(ppcglobPtr);		// Remove all alias port location names.
		RemoveConnectionListeners(ppcglobPtr);	// <56> Kill our connection listeners.
		PPCCloseUserSessions(NULL);				// <56> Kill any sessions we did not initiate.
		return(noErr);
	}
	else
		return(noGlobalsErr);
}

/*----------------------------------------------------------------------------------------
	initUserGroupFile opens the user's and groups data file.  The file name is now kept
	in a resource so that it can be internationalized.
----------------------------------------------------------------------------------------*/
STATIC void initUserGroupFile(short *refNum)
{
	Str255	fname;
	short	vRefNum;
	long	dirID;
	
	if (!*refNum)	// If the file is not open, then open it.
	{
		GetIndString(fname, -16410, 1);														/* <53> */
		if (!FindFolder(0, kPreferencesFolderType, false, &vRefNum, &dirID))
		{
			Boolean	MultiFinderRunning;														/* <53> */

#if TheFuture
			// check ExpandMem to see if ProcessMgr is running								   <61>
			MultiFinderRunning = (Boolean)(GetExpandMemProcessMgrExists());
#else
			long OSFlags;																	/* <53> */
			MultiFinderRunning = !Gestalt(gestaltOSAttr,&OSFlags);							/* <53> */
#endif
			if(MultiFinderRunning)															/* <53> */
				BeginSystemMode();															/* <52> */
			OpenUGBT( vRefNum, dirID, fname, fsRdWrShPerm, refNum);
			if(MultiFinderRunning)															/* <53> */
				EndSystemMode();															/* <52> */
		}
	}
}

/*---------------------------------------------------------------------------------------------------
	Removes all connection listeners.
---------------------------------------------------------------------------------------------------*/
STATIC void RemoveConnectionListeners(PPCGlobalParamsPtr ppcglobPtr)
{
	DSPParamBlock dsp;
	
	dsp.ccbRefNum = ppcglobPtr->dspListener.dsp1.ccbRefNum;
	dsp.ioCRefNum = ppcglobPtr->dspDrvrRef;
	RemoveConnectionListener(true, false, nil, &dsp);
}

/*----------------------------------------------------------------------------------------
	SetUpToolBoxName registers the <MachineName>:<PPCToolBox>@<*>.  It gets the machine
	name from a string resource that Network setup maintains.  It gets the PPCToolBox
	name from the 'ppci' resource.  This has changes the name that is registered, the
	Str32 in the PPCGlobals, and changes the netErr value.
----------------------------------------------------------------------------------------*/
STATIC OSErr SetUpToolBoxName(PPCGlobalParamsPtr ppcglobPtr)
{
	Handle machineName;
	OSErr Result;
	long flagShipAttributes;
	
	if (ppcglobPtr->configData.ppctoolboxName[0] == '\0')
		return noToolboxNameErr;

	if (!(machineName = GetResource('STR ', -16413)))
		return noMachineNameErr;

	BlockMove(*machineName, ppcglobPtr->machineName, sizeof(Str32));

	Result = noMachineNameErr;	// Assume the worst for now.
	if(!Gestalt(gestaltFlagshipAttr,&flagShipAttributes))	// If flagship exists
	{
		if((flagShipAttributes & 0x03) == 0x03)
		{
			NBPparms NBPPB;
			Result =  RegisterName(ppcglobPtr->machineName,
								   ppcglobPtr->configData.ppctoolboxName,
								   "\p*",
								   ppcglobPtr->adspSocket,
								   false,	// Call Syncronously
								   nil,		// No Completion Routine
								   (Ptr)&ppcglobPtr->nteQEle[ppcglobPtr->whichName], // ntePtr
								   &NBPPB); // PB for NBP call
		}
	}		
	return(Result);
}

/*----------------------------------------------------------------------------------------
	RemoveToolBoxName un-registers the PPCToolBox default NBP name.
----------------------------------------------------------------------------------------*/

STATIC OSErr RemoveToolBoxName(PPCGlobalParamsPtr ppcglobPtr)
{
	NBPparms nbpPB;

	return RemoveName((EntityName *)ppcglobPtr->nteQEle[ppcglobPtr->whichName].nt.entityData,
			   false,
			   (ProcPtr)nil,
			   &nbpPB); // PB for NBP call
}

/*----------------------------------------------------------------------------------------
	SetUpConnectionListeners performs everything necessary to recieve network requests.
----------------------------------------------------------------------------------------*/

STATIC OSErr SetUpConnectionListeners(PPCGlobalParamsPtr ppcglobPtr)
{
	OSErr result;
	
	if ((result =CreateConnectionListener((Ptr)&(ppcglobPtr->dspListener.ce),
												&ppcglobPtr->dspListener.dsp1,
												ppcglobPtr->dspDrvrRef,
											    ppcglobPtr->adspSocket = 0,
												false, // No Async
												nil  // No Completion
												) == noErr))
	{
		ppcglobPtr->adspSocket = ppcglobPtr->dspListener.dsp1.u.initParams.localSocket;
		ppcglobPtr->dspListener.dsp2.ccbRefNum = ppcglobPtr->dspListener.dsp1.ccbRefNum;
		ppcglobPtr->dspListener.dsp2.ioCRefNum = ppcglobPtr->dspDrvrRef;

		if ((result = ListenConnectionRequest(&(ppcglobPtr->dspListener.dsp1),
												true,             // Async
												(ProcPtr)ConnectionRequestCompletion // No Completion
												)) == noErr)
		result = ListenConnectionRequest(&(ppcglobPtr->dspListener.dsp2),
												true,             // Async
												(ProcPtr)ConnectionRequestCompletion  // No Completion
												);
	}
	return result;
} // SetUpConnectionListeners

/*----------------------------------------------------------------------------------------
	PPCSleepEvent handles sleep events from the portable.  We will deny sleep requests
	if we have any network sessions.
----------------------------------------------------------------------------------------*/
STATIC long PPCSleepEvent(void)
{
	PPCGlobalParamsPtr   	ppcglobPtr;
	short sleepEvent;
	
	sleepEvent = GetD0();
	ppcglobPtr = getGlobal();
	if(sleepEvent == sleepRequest)
	{
		return(ppcglobPtr->RemSessQueue.qSize?1:0);	// Object if we are currently networking.
	}
	else if(sleepEvent == sleepDemand)
	{
		if(ppcglobPtr->allowIncommingRequests)
			DisableIncoming();
		EndAllNetworkSessions(ppcglobPtr);
		ppcglobPtr->mppOpen = false;
		ppcglobPtr->canRemote = false;
		ppcglobPtr->dspDrvrRef = 0;
	}
	else if (sleepEvent == WakeupCall)
	{
		MPPOpen(); // I will just open the driver. Rest will take care of itself.
	}
	return(0);
}

/*----------------------------------------------------------------------------------------
	EndAllNetworkSessions ends all network sessions.
----------------------------------------------------------------------------------------*/
STATIC void EndAllNetworkSessions(PPCGlobalParamsPtr ppcglobPtr)
{
	CommonSessionParamsPtr  theSess;
	while(theSess = ServeQueue(&ppcglobPtr->RemSessQueue))
		EndNetworkSession(nil,(NetIPCParamsPtr)theSess);
}

/*----------------------------------------------------------------------------------------
	KillUserSession determines if the session qualifies to be ended.  If it qualifies,
	the session is ended.  A NULL pointer for userName qualifies all network sessions
	that this machine did not start.  Otherwise if the userName matches any sessions we
	did not start, they are ended.
----------------------------------------------------------------------------------------*/

STATIC Boolean KillUserSession(CommonSessionParamsPtr sessPtr,unsigned char *userName)
{
	Boolean Killit;
	
	Killit = false;
	if (!sessPtr->originator)
	{
		if(userName)
		{
			if(EqualString(((NetIPCParams *)sessPtr)->userName,userName,false,true))
				Killit = true;
		}
		else
			Killit = true;
	}
	if(Killit)
		EndNetworkSession(nil,(NetIPCParamsPtr) sessPtr);
	return(Killit);
}

/*----------------------------------------------------------------------------------------
	Closes all network sessions that originated external to this machine by userName.  If
	userName is a NULL pointer, all network sessions are ended that were not originated
	here.  This can be called from the Network setup control pannel.
----------------------------------------------------------------------------------------*/
OSErr PPCCloseUserSessions(unsigned char *userName)
{
	PPCGlobalParamsPtr   	ppcglobPtr;
	short saveint;

	if (!(ppcglobPtr = (PPCGlobalParamsPtr)getGlobal()))
		return noGlobalsErr;
	
	saveint = spl(kNoInterrupts);
	DeleteMultiple(&ppcglobPtr->RemSessQueue,(unsigned long)userName,(SearchFuncPtr)KillUserSession);
	spl(saveint);
	return noErr;
}

/*----------------------------------------------------------------------------------------
	PPCCountAcceptedNetworkSessions is called from the Network setup control panel to
	find out how many sessions originated on other machines.
----------------------------------------------------------------------------------------*/
short PPCCountAcceptedNetworkSessions(unsigned char *userName)
{
	PPCGlobalParamsPtr   	ppcglobPtr;
	CommonSessionParamsPtr  sessPtr;
	short numberOfNetworkSessionsAccepted = 0;
	short saveint;

	if (!(ppcglobPtr = (PPCGlobalParamsPtr)getGlobal()))
		return 0;
	
	saveint = spl(kNoInterrupts);
	FOREACHELEMENT(sessPtr,&ppcglobPtr->RemSessQueue)
	{
		if (!sessPtr->originator)
		{
			if(userName)
			{
				if(EqualString(((NetIPCParams *)sessPtr)->userName,userName,false,true))
					++numberOfNetworkSessionsAccepted;
			}
			else
				++numberOfNetworkSessionsAccepted;
		}	
	}
	spl(saveint);
	return numberOfNetworkSessionsAccepted;
}

/*---------------------------------------------------------------------------------------------------
	PPCCheckDupNBPName is called to find out if some one has a machine name the same as the one we
	want.  It is called from the Network Setup control pannel.
	
	This procedure is now obsolete, and does nothing now.  This procedure is going away before B4.
---------------------------------------------------------------------------------------------------*/
OSErr PPCCheckDupNBPName(void)
{
	return(noErr);
}

/*----------------------------------------------------------------------------------------
	PPCGESTALTFUNCTION returns the attributs about PPC.
----------------------------------------------------------------------------------------*/
pascal OSErr PPCGESTALTFUNCTION(long selector, long *myResp)
{
	PPCGlobalParamsPtr   	ppcglobPtr;

 	if (selector == gestaltPPCToolboxAttr)
	{
		*myResp = gestaltPPCToolboxPresent;
		if (ppcglobPtr = getGlobal())
		{
			if (ppcglobPtr->inited)
				*myResp += gestaltPPCSupportsRealTime;
			if (ppcglobPtr->canRemote)
			{
				*myResp +=  gestaltPPCSupportsOutGoing;
				if (ppcglobPtr->allowIncommingRequests)
					*myResp +=  gestaltPPCSupportsIncoming;
			}
		}
		return noErr;
	}
	return gestaltUnknownErr;
} // PPCGestaltFunction

/*----------------------------------------------------------------------------------------
	This call examines the usergroup BTree and returns true if we are currently allowing
	incoming requests.
----------------------------------------------------------------------------------------*/
STATIC Boolean GetPPCGlobalFlag(PPCGlobalParamsPtr ppcglobPtr)
{
	UserRecPb	urec;
	char        keyName[32];

	initUserGroupFile(&ppcglobPtr->ugFile.refNum);
	if(ppcglobPtr->ugFile.refNum)
	{
		keyName[0] = 0;
		urec.btPb.ioBTKeyPtr = (Ptr)&(urec.key);
		BldFSKey( 0, keyName, urec.btPb.ioBTKeyPtr);	// make the key
		urec.btPb.ioBuffer= (Ptr)&(urec.u.record);		// set pointer to record
		urec.btPb.ioReqCount = sizeof (urec.u);
		urec.btPb.ioRefNum= ppcglobPtr->ugFile.refNum;
		urec.btPb.ioCompletion= 0;						// assembly glue completion
		urec.btPb.ioBTHint1= 0;							// zero Hint field
		urec.usrCompletion= nil;						// set up completion routine
		if (BTSEARCHPPC( &(urec.btPb), 0) ==  noErr)	// dispatch the call
		{
			if (urec.u.ulRecord.ServerFlags & IACGlobalEnabled)
				return true;
		}
	}
	return false;
} // GetPPCGlobalFlag

/*----------------------------------------------------------------------------------------
	PPCSHUTDOWN is called when the computer is being shut down.  Just kill all network things.
----------------------------------------------------------------------------------------*/
pascal void PPCSHUTDOWN(void)
{
	PPCGlobalParamsPtr ppcglobPtr;

	ppcglobPtr = (PPCGlobalParamsPtr)getGlobal();
	DisableIncoming();
	EndAllNetworkSessions(ppcglobPtr);
	ppcglobPtr->mppOpen = false;
	ppcglobPtr->canRemote = false;
	ppcglobPtr->dspDrvrRef = 0;
} // PPCSHUTDOWN


/*----------------------------------------------------------------------------------------
	PPCSystemTask is called every time through system task, and we make sure we have enough
	supplies.
----------------------------------------------------------------------------------------*/
OSErr PPCSystemTask(void)
{
	PPCGlobalParamsPtr ppcglobPtr;

	if (!(ppcglobPtr = (PPCGlobalParamsPtr)getGlobal()))
		return noGlobalsErr;
	
	Replenish(ppcglobPtr);					// Make sure we have plenty of resources
	Excess(ppcglobPtr);						// Make sure we don't have too many
}


/*----------------------------------------------------------------------------------------
	UnRegisterAllNBPNames will for each port that has an NBP location registered with it un-register
	the name from the network.
----------------------------------------------------------------------------------------*/
STATIC void UnRegisterAllNBPNames(PPCGlobalParamsPtr ppcglobPtr)
{
	PPCPortEntryPtr portPtr;

	FOREACHELEMENT(portPtr,&ppcglobPtr->OpenPortQueue)
	{
		if (portPtr->nbpRegistered) 		// PortName was registered with nbp
		{
			PortLocationTablePtr locInfo;
			
			locInfo = portPtr->locationInfo;
			RemoveName((EntityName *)locInfo->nteQEle.nt.entityData,
					   false,
					   (ProcPtr)nil,
					   &locInfo->nbpPB); 	// PB for NBP call
			portPtr->nbpRegistered = false;
		}
	}
}

/*----------------------------------------------------------------------------------------
	ReRegisterAllNBPNames will for each port registered with an NBP location name
	re-register the name on the network.  It is assumed that the NBPName is currently
	un-registered at this point.
----------------------------------------------------------------------------------------*/
STATIC void ReRegisterAllNBPNames(PPCGlobalParamsPtr ppcglobPtr)
{
	PPCPortEntryPtr portPtr;
	
	FOREACHELEMENT(portPtr,&ppcglobPtr->OpenPortQueue)
	{
		if (portPtr->locationInfo) 			// if port has a location name, re-register it
		{
			PortLocationTablePtr locInfo;
			OSErr result;
			
			locInfo = portPtr->locationInfo;
			result = RegisterName(ppcglobPtr->machineName,
								  locInfo->typeStr,
								  "\p*",
								  ppcglobPtr->adspSocket,
								  false, 					// Call Syncronously
								  NULL,						// NBPCompletion
								  (Ptr)&locInfo->nteQEle,	// ntePtr
								  &locInfo->nbpPB);			// PB for NBP call
			if(!result)
				portPtr->nbpRegistered = true;
		}
	}
}

/*----------------------------------------------------------------------------------------
	Return the PPC is here, but supports nothing.
----------------------------------------------------------------------------------------*/
STATIC pascal OSErr PPCDEADGESTAULT(OSType selector, long *myResp)
{
#pragma unused(selector)
	*myResp = 0;	// We are dead.
	return noErr;
}

/*----------------------------------------------------------------------------------------
	KillPPC takes the steps to remove PPCToolBox from the system.  Once called PPC is dead, and
	a new one must be installed.
----------------------------------------------------------------------------------------*/
OSErr KillPPC(void)
{
	PPCGlobalParamsPtr ppcglobPtr;
	SelectorFunctionProcPtr oldFunc;
	long powerMgrAttrs;
	void *p;

	ppcglobPtr = (PPCGlobalParamsPtr)getGlobal();
	ReplaceGestalt(gestaltPPCToolboxAttr,PPCDEADGESTAULT,&oldFunc);
	
	if(ppcglobPtr->inited)
	{
		RemoveToolBoxName(ppcglobPtr);
		RmvfromAtalkQ((Ptr)&(ppcglobPtr->trQEle));
		EndAllNetworkSessions(ppcglobPtr);
		ShutDwnRemove(PPCSHUTDOWN);
		if (!Gestalt(gestaltPowerMgrAttr, &powerMgrAttrs))
		{
			if ((powerMgrAttrs & 1<<gestaltPMgrExists) &&
				(powerMgrAttrs & 1<<gestaltPMgrCPUIdle))
			{
				SleepQRemove((SleepQRecPtr)&ppcglobPtr->sleepQEle);
			}
		}
		while(p = ServeQueue(&ppcglobPtr->OpenPortQueue))
			DisposeMem(p);
		
		while(p = ServeQueue(&ppcglobPtr->LocSessQueue))
			DisposeMem(p);
		
		while(p = ServeQueue(&ppcglobPtr->RemSessQueue))
			DisposeMem(p);
		
		while(p = ServeQueue(&ppcglobPtr->IPMSessQueue))
			DisposeMem(p);

		while(p = ServeQueue(&ppcglobPtr->ListSessQueue))
			DisposeMem(p);
		
		while(p = ServeQueue(&ppcglobPtr->UserEntryQueue))
			DisposeMem(p);
			
		if(ppcglobPtr->listsessPtr)
			DisposeMem(ppcglobPtr->listsessPtr);
	}
	memset((Ptr)&ppcglobPtr->configData,0,sizeof(PPCConfigInfo));	// Clear configuration.
	Excess(ppcglobPtr);	// Remove free ports and sessions.
	DisposeMem((Ptr)ppcglobPtr);
	return(noErr);
}

