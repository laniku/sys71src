/*
	File:		SIMCore.c

	Contains:	routines that implement the core of the Apple SIM layer

	Entry points:
		XPT Calls to SIM
		
		void	InitSIM( Ptr SIMstaticPtr, long busID)
		
		Called by the XPT to initialize the SIMÕs state.  The SIM, in turn has the 
		responsibility of optionally initializing the HBA.
		
		void	SIMAction(SIM_IO *thePB, Ptr SIMstaticPtr)
		
		Called by the XPT whenever a SCSIAction call is received that needs to be
		serviced by the SIM.  The SIMstaticPtr parameter is a pointer to the previously
		allocated SIM static data area.
		
		HAL Calls to SIM
		
		ushort	SIMRegisterHAL (long HALentry, ulong staticSize, Ptr * HALstaticPtr)
		
		Called by a Hardware Abstraction Layer (HAL) to register itself (i.e. its bus)
		with the Apple standard SIM.  The SIM will in turn, register this new HBA with 
		the XPT and will return the BusID to the HAL.
		
		void	SIMDeregisterHAL (ushort busID)
		
		Called by a Hardware Abstraction Layer to deregister itself from the Apple 
		standard SIM.  The SIM will in turn, deregister this HBA with the XPT.
		
				

	Written by:	Paul Wolf

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SM29>	 1/31/94	DCB		Added a call to SIMDualIntPoll for the Old API case.  Also
									changed SIMDualIntPoll so that it will always wait for 2
									consecutive polls (1 on each bus) without an interrupt before
									exiting.
	  <SM28>	 1/29/94	DCB		Added SIMDualIntPoll which is called when we exit the SIMAction
									call.  This ensures that we don't forget about an interrupt that
									might have been cleared at the VIA for the other bus.
	  <SM27>	12/21/93	DCB		If CompAutoSense() detects that senseWaiting is non-zero and
									that no PBs are awaiting autosense it needs to clear sensePBBusy
									as well as senseWaiting.  Otherwise we hang the next time
									autosense is used.
	  <SM26>	11/21/93	pdw		Added support for dynamic supported-flags for scFlags, scIOFlags
									and scDataTypes.
	  <SM25>	10/14/93	pdw		<MC> roll-in.
	   <MC4>	10/12/93	pdw		Added support for Synchronous data transfers, rewrote State
									Machine, message handling etc.
	   <MC3>	 9/26/93	pdw		<SM24>
	  <SM24>	 9/16/93	DCB		Fixing ResetDevice so it doesn't validate a bogus parameter
									block and then return from the procedure with interrupts
									blocked.
	  <SM23>	 9/13/93	pdw		Changed the risky slash pattern.
	  <SM22>	 9/12/93	pdw		Added Reregister support. Split out common registration stuff
									into separate routine.
	  <SM21>	 7/17/93	pdw		Lots of little things.
	  <SM20>	  7/8/93	pdw		Added calls to RecordError.
	  <SM19>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
									stack switching mechanism.  Adding support for Cold Fusion.
									Rearranging HW/SW Init code. Some code optimizations.
	  <SM18>	 5/25/93	DCB		Rollin from Ludwig. (The next item below)
	  <LW13>	 5/21/93	PW		Adding SIMg parameter to ValidateDeviceIdent so that it can
									check HostID.
	  <SM17>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	  <LW12>	  5/1/93	PW		Changed one last name: SCSI_RegisterWithNewXPT.
	  <LW11>	 4/30/93	DCB		Added call to CallBusInquiry function so that we don't have to
									busy the HALAction routine.
	   <LW9>	 4/14/93	DCB		Added RegisterWithNewXPT action for the purpose of switching
									XPTs on the fly.
	   <LW8>	 3/26/93	PW		Moved VMDisableUserCode and Enable into SIMaction (from XPT).
	  <SM15>	 3/20/93	PW		Made ReleaseQ return noErr (bug introduced by removing
									finalStatus from CallCompRoutine).
	   <LW6>	  3/3/93	PW		Changed default disconnect action to false (don't disconnect).
	   <LW5>	  3/1/93	DCB		Fixed ResetDevice to match ResetBus. Also changed the parameters
									to callcomproutine.
	   <LW4>	 2/18/93	DCB		Changed Reset's behavior to match the documentation. Only those
									IOs actually started are dequeued after a reset.
	   <LW3>	 1/27/93	PW		Added support for register->SIMinit->HALinit way of
									initialization. Added SIMInterruptPoll routine.
	   <LW2>	12/17/92	DCB		Fixed a bug in the reset device,abort command and terminateIO
									features which caused a sync-wait hang.
	  <SM13>	 12/9/92	DCB		Fixed SyncWait problem for synchronous Reset Bus commands by
									returning a noErr after doing the reset.
	  <SM12>	 12/5/92	PW		Changed ValidateDI to return the appropriate error.
	  <SM11>	11/20/92	DCB		Added support for asynchronous abort, terminate, reset device
									and other functions
	  <SM10>	 11/1/92	DCB		Removed bogus validate check before doing BusInquiry.
	   <SM9>	10/30/92	DCB		Changed to reflect new ACAM.h
	   <SM8>	 10/8/92	PW		Added stuff needed for variable-sized SCSI_IO support and for
									new ioEvent field.
	   <SM7>	 9/17/92	PW		Added check for function code not supported.
	   <SM6>	 9/14/92	DCB		Added some parameter block validation
	   <SM5>	 9/11/92	DCB		Fixing Terminate and Abort IO and adding Reset Device
	   <SM4>	 8/31/92	DCB		Implementing Terminate/Abort IO
	   <SM3>	 8/20/92	DCB		Fixed SCSI Reset
	   <SM2>	  8/1/92	PW		Added comments, function headers and prototypes.

*/

#include <Types.h>
#include <Memory.h>
#include <Errors.h>
#include <SCSIStandard.h>
#include <SCSI.h>

#include "ACAM.h"
#include "XPT.h"
#include "CUtils.h"

#include "SIMCore.h"
#include "SIMCorePriv.h"
#include "SIMQ.h"
#include "SCSIGlue.h"
#include "HALc96.h"

#include "SCSIDebug.h"
#include "Recorder.h"


//ÑÑÑÑ Prototypes for functions used only within this file ÑÑÑÑ

void	ResetDevice( SCSIResetDevicePB *resetPtr, SIMglobals * SIMg);
void	TerminateIO( SCSITerminateIOPB *termPtr, SIMglobals * SIMg);
void	AbortCommand( SCSIAbortCommandPB *abortPtr, SIMglobals * SIMg);
void	SIMaction( SIM_IO *ioPtr, SIMglobals * SIMg);
Boolean	StartMachine( SIMglobals * SIMg);
void	SetupSensePB( SIM_IO * ioPtr, SIMglobals * SIMg );
Boolean CheckErrors( OSErr finalStatus, SIM_IO * ioPtr, SIMglobals * SIMg );
pascal	void CompAutoSense( SIM_IO *ioPtr );
pascal	void CompResetDevice( SIM_IO *ioPtr );
void	FreeMachine( OSErr finalStatus, SIM_IO * ioPtr, SIMglobals * SIMg);
SIMinitInfo *	SIMRegisterCommon( HALinitInfo *HALinfoPtr);


/*********************************************************************************
	SIMRegisterHAL	-	register a HAL for the SIMCore
*********************************************************************************/

OSErr
SIMRegisterHAL( HALinitInfo *HALinfoPtr)
{
	SIMinitInfo		* SIMinfoPtr;

// Fill in our entry points

	SIMinfoPtr = SIMRegisterCommon( HALinfoPtr);
	
// Make call ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ (which in turn calls SIMinit)

	return ( SCSIRegisterBus( SIMinfoPtr) );
}


/*********************************************************************************
	SIMRegisterHAL	-	register a HAL for the SIMCore
*********************************************************************************/

OSErr
SIMReregisterHAL( HALinitInfo *HALinfoPtr)
{
	OSErr		err;
	SIMinitInfo	* SIMinfoPtr;

// Fill in our entry points

	SIMinfoPtr = SIMRegisterCommon( HALinfoPtr);

// Make call ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ (which doesn't call SIMinit)

	SIMinfoPtr->busID = HALinfoPtr->busID;
	err = SCSIReRegisterBus( SIMinfoPtr);
	
	if (err) return(err);
	
	return ( SIMinit( SIMinfoPtr));
}


/*********************************************************************************
	SIMRegisterCommon	-	
*********************************************************************************/

SIMinitInfo *
SIMRegisterCommon( HALinitInfo *HALinfoPtr)
{
	SIMinitInfo		* SIMinfoPtr;

// Set up SIMinfoPtr for call to SCSIRegisterBus

	if( 0==(SIMinfoPtr = (SIMinitInfo *) NewPtrSysClear(sizeof(SIMinitInfo)))) 	// We need to keep this around for re-registration
		return (SIMinfoPtr);

															// -> num bytes SIM needs for static vars
	SIMinfoPtr->staticSize = sizeofSIMGlobals + HALinfoPtr->staticSize;
	SIMinfoPtr->SIMinit = SIMinit;								// -> SIM init routine
	SIMinfoPtr->SIMaction = SIMaction;							// -> SIM action routine
	SIMinfoPtr->NewOldCall = NewOldCall;						// -> SIM NewOldCall routine
	SIMinfoPtr->SIM_ISR = SIM_ISR;								// -> SIM int-> service routine
	SIMinfoPtr->SIMInterruptPoll = SIMDualIntPoll;				// -> SIM int-> poll routine
	SIMinfoPtr->ioPBSize = sizeof(SIM_IO);						// -> size of IO PB needed
	SIMinfoPtr->oldCallCapable = HALinfoPtr->oldCallCapable;	// -> capable of old calls
	
	SIMinfoPtr->simInternalUse = (long)HALinfoPtr;				// -> so SIMinit knows

	return (SIMinfoPtr);
}


/*********************************************************************************
	SIMinit	-	
*********************************************************************************/

OSErr
SIMinit (SIMinitInfo * SIMinfoPtr)
{
	SIMglobals *	SIMg;
	HALinitInfo *	HALinfoPtr;
	OSErr			err;

//--- Get results out of SIMinfo and put in SIMglobals and in HALInfo

	// <- get G ptr from ptr allocated by XPT and copy entire SIMinfo over there	
	SIMg = (SIMglobals *)SIMinfoPtr->SIMstaticPtr;		
	
	HALinfoPtr = (HALinitInfo *)SIMinfoPtr->simInternalUse;

	// give HAL its staticPtr which should point just past SIM's globals
	HALinfoPtr->HALstaticPtr = (uchar *)SIMg + sizeofSIMGlobals;
	
	// give HAL the SIMCore's global ptr also, for callbacks to SSM
	HALinfoPtr->SIMstaticPtr = (uchar *)SIMg;

	// and the addresses for callbacks to SSM
	HALinfoPtr->ReconnectISR	= ReconnectISR;

	// The XPT gives the SIM its ISR so that it can install it - give it to the HAL instead
	HALinfoPtr->XPT_ISR	= SIMinfoPtr->XPT_ISR;

	// <- busID returned - store it
	HALinfoPtr->busID = SIMinfoPtr->busID;

	// Store all of the HALinfo for later reference
	SIMg->HALinfo = *HALinfoPtr;
	
	SIMg->MakeCallback = SIMinfoPtr->MakeCallback;

	
//--- Set up various state things  (that shouldn't be init'd at zero)

	SIMg->state = kIdle;	
	SIMg->defaultDisc = false;
	
	SIMg->initInfo = SIMinfoPtr;	// Save this for re-registration
	
	StartTimer(	SIMg );
	
//--- Make call to HALinit then get what we need from HAL

	if( err=(HALinfoPtr->HALinit)(HALinfoPtr) )
		return (err);
	
	SIMg->hostID = GetInitiatorID( (HBADesc_53c9x *)(HALinfoPtr->HALstaticPtr));

//--- Initialize fields in HALActionPB that will never change

	SIMg->halPB.HALstaticPtr = SIMg->HALinfo.HALstaticPtr;
	
	return ( noErr);
}


/*********************************************************************************
	SIMaction	-	The main SIMCore entry point
*********************************************************************************/

void
SIMaction( SIM_IO *ioPtr, SIMglobals * SIMg)
{
	VMDisableUserCode();		// disable user code (so page faults won't happen)	

	// What do we need to do?
	
	// I moved this here because ALL of these routines are now considered to be
	// asynchronous - not just those that are enqueued into the IOQ.		<SM11> DCB
	ioPtr->scsiResult = scsiRequestInProgress;

	if (ioPtr->scsiFunctionCode == SCSIExecIO || ioPtr->scsiFunctionCode == SCSIOldCall)
	{
		if( ValidatePB(ioPtr, SIMg)) {
			EnQIO( ioPtr, SIMg);
			NewIOStartMachine( SIMg);
		}
	}
	else
	{
		switch (ioPtr->scsiFunctionCode) 
		{
		case SCSIReleaseQ:
		
			if( ioPtr->scsiResult = ValidateDeviceIdent( ioPtr->scsiDevice, SIMg)) {
				CallCompRoutine( (SCSI_IO *)ioPtr); 
			}
			else {
				DefrostLUN( ioPtr->scsiDevice.targetID, ioPtr->scsiDevice.LUN );
				NewIOStartMachine( SIMg);
				ioPtr->scsiResult = noErr;
				CallCompRoutine( (SCSI_IO *) ioPtr); 
			}
			break;
		case SCSIBusInquiry:			// SIM	
			((SCSIBusInquiryPB *)ioPtr)->scsiSIMPrivatesPtr = SIMg; 
			((SCSIBusInquiryPB *)ioPtr)->scsiSIMPrivatesSize = sizeofSIMGlobals; 
			((SCSIBusInquiryPB *)ioPtr)->scsiIOpbSize = sizeof(SIM_IO); 
			CallBusInquiry( ioPtr, SIMg);
			ioPtr->scsiResult = noErr;
			CallCompRoutine( (SCSI_IO *) ioPtr); 
			break;

		case SCSIResetBus:				// SIM
			ResetSIM( SIMg );
			ioPtr->scsiResult = noErr;
			IfRecordEvent( (long)ioPtr, (long)'RsOC');
			CallCompRoutine( (SCSI_IO *)ioPtr);	// <SM13>
			break;
		case SCSIResetDevice:			// SIM
			ResetDevice( (SCSIResetDevicePB *) ioPtr, SIMg);
			break;
		case SCSIAbortCommand:			// SIM
			AbortCommand( (SCSIAbortCommandPB *) ioPtr, SIMg);
			break;
		case SCSITerminateIO:			// SIM
			TerminateIO( (SCSITerminateIOPB *) ioPtr, SIMg);
			break;
		case SCSIRegisterWithNewXPT:
			ioPtr->scsiResult = SCSIReRegisterBus( SIMg->initInfo );
			break;
		default:
			ioPtr->scsiResult = scsiFunctionNotAvailable;
			IfRecordError( (long)'FC?C');
			IfRecordEvent( (long)ioPtr, (long)ioPtr->scsiFunctionCode);
			CallCompRoutine( (SCSI_IO *)ioPtr); 
			break;
		}
	}
	
	// If this was a Quadra 900 then we want to check to see if any interrupts
	// for the other bus have occured and been cleared...
	if( SIMg->otherSIMg )
		SIMDualIntPoll(SIMg);
	
	VMEnableUserCode();			// enable user code (allow page faults)
}


/*********************************************************************************
	NewOldCall 	-	
*********************************************************************************/

void
NewOldCall( SIM_IO * ioPtr, SIMglobals * SIMg)
{
	VMDisableUserCode();		// disable user code (so page faults won't happen)	

	ioPtr->scsiResult = scsiRequestInProgress;
	ioPtr->scsiOldCallResult = scsiRequestInProgress;
	CallMachine( SIMg);

	// If this was a Quadra 900 then we want to check to see if any interrupts
	// for the other bus have occured and been cleared...
	if( SIMg->otherSIMg )
		SIMDualIntPoll(SIMg);

	VMEnableUserCode();			// enable user code (allow page faults)
}


/*********************************************************************************
	SIM_ISR	-	
*********************************************************************************/
#if 0
long
SIM_ISR (SIMglobals * SIMg)
{
	return (((SIMg->HALinfo).HAL_ISR)((SIMg->HALinfo).HALstaticPtr));
}
#endif


/*********************************************************************************
	SIMIntPoll	-	
*********************************************************************************/

long
SIMIntPoll (SIMglobals * SIMg)
{
	return (((SIMg->HALinfo).HALIntPoll)((SIMg->HALinfo).HALstaticPtr));
}

/*********************************************************************************
	SIMDualIntPoll	-	
*********************************************************************************/

long
SIMDualIntPoll (SIMglobals * SIMg)
{
	SIMglobals * AltSIMg;
	ulong		 GotInt;
	
	if( SIMg->otherSIMg == nil )
		return(SIMIntPoll(SIMg));
	
	AltSIMg = SIMg;
	
	do {
//		IfRecordEvent((long)AltSIMg, (long)'SItp');
		GotInt = SIMIntPoll(AltSIMg);
		AltSIMg = (SIMglobals *) AltSIMg->otherSIMg;
		
		if( GotInt )
			continue;
		
//		IfRecordEvent((long)AltSIMg, (long)'SItp');
		GotInt = SIMIntPoll(AltSIMg);
		AltSIMg = (SIMglobals *) AltSIMg->otherSIMg;
		
	} while( GotInt );	// Repeat until 2 in a row didn't handle an interrupt
	
	
	return(0);	// !!! nobody is paying attention to this currently
}


/*********************************************************************************
	CallBusInquiry 	-	call HAL to get info on the bus
*********************************************************************************/

Boolean		// completed Synchronously
CallBusInquiry( SIM_IO * ioPtr, SIMglobals * SIMg)
{
// Call HAL and return result
	return ((SIMg->HALinfo.HALBusInquiry)( SIMg->HALinfo.HALstaticPtr, (SCSIBusInquiryPB *)ioPtr ));
}


/*********************************************************************************
	ResetSIM	-	It's the end of the world as we know it...
					And I feel fine.
*********************************************************************************/

void
ResetSIM( SIMglobals * SIMg)
{
	int LUN,id;
	SIM_IO *	qPtr;
	
	SIMg->SIMBusy = true;		// Don't start IOs until we are done.
	
	/* Reset Bus, Most of the chip, and go bus free */
	CallHALResetBus( SIMg->HALinfo.HALstaticPtr );	/* Say goodbye to Hollywood */
	
	for( id = 0; id < 7; id+=1 ) {
		for( LUN = 0; LUN < 8; LUN+=1 ) {
			SIMg->discIOs[id][LUN] = 0;	/* Reset should have gotten rid of connected ios */
			SIMg->LUNstate[id][LUN] = 0;
		}
	}
		
	SIMg->state = kIdle;
	SIMg->SSMflags = 0;
	SIMg->senseWaiting = 0;
	
	/* Don't send any reset device messages <SM11> */
	while( qPtr = (SIM_IO *)SIMg->resetPBQ.qHead ) {				// <SM11>
		qPtr->scsiResult = scsiSCSIBusReset;
		IfRecordEvent( (long)qPtr, (long)'RstC');
		CallCompRoutine( (SCSI_IO *) qPtr);
		Dequeue( (QElemPtr) qPtr,&SIMg->resetPBQ);
	}
	
	ResetQueues( SIMg, 0xFF );	/* Move the IO Q into the Reset Q */
	while( qPtr = (SIM_IO *)SIMg->resetHdr.qHead ) { /* CompleteIO will dequeue each entry	<LW4> <TOP> */
		if( (qPtr->scsiFlags & scsiSIMQNoFreeze) || qPtr->scsiFunctionCode == SCSIOldCall ) {
			DefrostLUN( qPtr->scsiDevice.targetID, qPtr->scsiDevice.LUN);
		}
		else {
			FreezeLUN( qPtr->scsiDevice.targetID, qPtr->scsiDevice.LUN);
			qPtr->scsiResultFlags |= scsiSIMQFrozen;
		}
		CompleteIO( scsiSCSIBusReset, (SIM_IO *) qPtr, SIMg);
	} /*																					<LW4> <BOTTOM> */
	
	SIMg->SIMBusy = false;		// Allow IOs again
	
	NewIOStartMachine(SIMg);	// Make sure Machine gets run
}


/*********************************************************************************
	ResetDevice	 - Reset a particular SCSI device with a ResetDevice Message <SM5>
*********************************************************************************/

void
ResetDevice( SCSIResetDevicePB *resetPtr, SIMglobals * SIMg)
{
	SIM_IO		*ioPtr, *qPtr;
	ushort		oldSR;
	Boolean		usedExisting = false;
	uchar		targetID;

	if( resetPtr->scsiResult = ValidateDeviceIdent( resetPtr->scsiDevice, SIMg)) {
		IfRecordEvent( (long)resetPtr, (long)'RsDC');
		CallCompRoutine( (SCSI_IO *)resetPtr); 
		return;
	}

	oldSR = BlockInterrupts();	//-> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> ->
	

	targetID = (resetPtr->scsiDevice).targetID;

	IfRecordEvent( (long)targetID, (long)'RstD');

	ioPtr = FindIOFromID( targetID, SIMg);
	
	
//ÉÉÉ If we are already connected to the device - then we can use the existing 
//		connection.  If not we will have to use the one in the globals.

	if( ioPtr && ioPtr->ioStat != kPBidle ) {
		ioPtr->pendingMsgPB = (Ptr)resetPtr;				// <SM11> DCB
		SwitchQ(ioPtr, &SIMg->immedQHdr);
		usedExisting = true;
	}


//ÉÉÉ Get rid of ALL other PBs for this guy that haven't been started

	ResetQueues( SIMg, targetID );
	
	
//ÉÉÉ For each IO in resetQ, freeze the LUN's Q if it's a new-API request w/o the NoFreeze bit set

	while( qPtr = (SIM_IO *)SIMg->resetHdr.qHead ) { 		// CompleteIO will dequeue each entry
		if( (qPtr->scsiFlags & scsiSIMQNoFreeze) || qPtr->scsiFunctionCode == SCSIOldCall ) {
			DefrostLUN( qPtr->scsiDevice.targetID, qPtr->scsiDevice.LUN);
		}
		else 
		{
			// Do actual freezing of LUN then indicate that it is so in the SCSI_IO PB
			FreezeLUN( qPtr->scsiDevice.targetID, qPtr->scsiDevice.LUN);
			qPtr->scsiResultFlags |= scsiSIMQFrozen;
		}
		CompleteIO( scsiBDRsent, (SIM_IO *) qPtr, SIMg);
	} 																				//<LW5> <BOTTOM>
		
//ÉÉÉ ResetDevice should have gotten rid of in-progress IOs - clear them from table

	if( !usedExisting ) {
		if( SIMg->resetPBQ.qHead == 0 ) { 			/* The global Reset PB is free */
			SetupResetPB( targetID , SIMg);
			EnQIO(&SIMg->resetDevPB,SIMg);
			SIMg->resetDevPB.pendingMsgPB = (Ptr) resetPtr;		/* Remember who started this <LW2> */
		}
		Enqueue((QElemPtr)resetPtr, &SIMg->resetPBQ);
	}
	
	UnblockInterrupts(oldSR); //<- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- 
	
	NewIOStartMachine(SIMg);	/* Make sure Machine gets run */

}


/*********************************************************************************
	TerminateIO	-	
*********************************************************************************/

void
TerminateIO( SCSITerminateIOPB *termPtr, SIMglobals * SIMg)		// <SM4>
{
	SIM_IO *	ioPtr;
	ushort oldSR;
	Boolean restartMachine = false;
	
	oldSR = BlockInterrupts();	//-> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> ->

	ioPtr = (SIM_IO *)(termPtr->scsiIOptr);
	
	IfRecordEvent( (long)ioPtr, (long)'TmIO');

	if( FindIO( ioPtr, SIMg) == 0 ) {	
		termPtr->scsiResult = scsiUnableToTerminate;
		IfRecordEvent( (long)termPtr, (long)'Tm1C');
		CallCompRoutine( (SCSI_IO *)termPtr);		/* Dang - PB not in queue <LW5> */
		goto exit;
	}
	if( ioPtr->ioStat == kPBidle ) {				/* If it hasn't been started - just de-queue it */
		CompleteIO( scsiTerminated, (SIM_IO *) ioPtr, SIMg );
		goto exit;
	}
	
	/* If it has been started let Machine() deal with it */
	if( ioPtr->pendingMsgPB ) {
		termPtr->scsiResult = scsiUnableToTerminate;
		IfRecordEvent( (long)termPtr, (long)'Tm2C');
		CallCompRoutine( (SCSI_IO *)termPtr);
	}
	ioPtr->pendingMsgPB = (Ptr)termPtr;				// <SM11> DCB
	
	restartMachine = true;
	SwitchQ(ioPtr, &SIMg->immedQHdr);
	

exit:
	UnblockInterrupts( oldSR); //<- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- 

	if( restartMachine )
		NewIOStartMachine( SIMg);	/* Make sure Machine gets run */
}


/*********************************************************************************
	AbortCommand	-	
*********************************************************************************/

void
AbortCommand( SCSIAbortCommandPB *abortPtr, SIMglobals * SIMg)	// <SM4>
{
	SIM_IO * ioPtr;
	ushort oldSR;
	Boolean restartMachine = false;
	
	oldSR = BlockInterrupts();	//-> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> ->
	
	ioPtr = (SIM_IO *)(abortPtr->scsiIOptr);
	
	IfRecordEvent( (long)ioPtr, (long)'Abt ');

	if( FindIO( ioPtr, SIMg) == 0 ) {	
		abortPtr->scsiResult = scsiUnableToAbort;
		IfRecordEvent( (long)abortPtr, (long)'Ab1C');
		CallCompRoutine( (SCSI_IO *)abortPtr);		/* Dang - PB not in queue <LW2> */
		goto exit;
	}
	if( ioPtr->ioStat == kPBidle ) {				/* If it hasn't been started - just de-queue it */
		CompleteIO( scsiTerminated, (SIM_IO *) ioPtr, SIMg);
		goto exit;
	}
	
	/* If it has been started let Machine() deal with it */
	if( ioPtr->pendingMsgPB ) {
		abortPtr->scsiResult = scsiUnableToAbort;
		IfRecordEvent( (long)abortPtr, (long)'Ab2C');
		CallCompRoutine( (SCSI_IO *)abortPtr);
	}
	ioPtr->pendingMsgPB = (Ptr)abortPtr;				// <SM11> DCB
	
	restartMachine = true;
	SwitchQ(ioPtr,(QHdrPtr) &SIMg->immedQHdr);

exit:
	UnblockInterrupts( oldSR); // <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- 

	if( restartMachine )
		NewIOStartMachine( SIMg);	/* Make sure Machine gets run */
}


/*********************************************************************************
	ValidatePB 	-	Makes sure the PB is "right with GOD" (Us)
					Errors with precedence should appear at the bottom in case
					there is more than one thing wrong with the PB
*********************************************************************************/

Boolean
ValidatePB( SIM_IO * ioPtr, SIMglobals * SIMg )
{
	OSErr finalStatus = noErr;
	
	if( ioPtr->scsiPBLength < sizeof(SIM_IO) ) {
		finalStatus = scsiPBLengthError;	/* Not enough room for SIM and HAL privates <SM5> */
		goto FinalCheck;
	}
	
	if( ioPtr->scsiFlags & (0xffffffff - SIMg->HALinfo.supported_scFlags) ) {
		finalStatus = scsiProvideFail;
		goto FinalCheck;
	}
	
	if( ioPtr->scsiIOFlags & (0xffff - SIMg->HALinfo.supported_scIOFlags) ) {
		finalStatus = scsiProvideFail;
		goto FinalCheck;
	}
	
	if( finalStatus = ValidateDeviceIdent( ioPtr->scsiDevice, SIMg)) {
		if (finalStatus == scsiTIDInvalid)
			ioPtr->scsiOldCallResult = scsiSelectTimeout;
		goto FinalCheck;
	}
		
	if( ioPtr->scsiCDBLength > 12 ) {
		finalStatus = scsiCDBLengthInvalid;	/* We can't handle CDB's longer than 12 bytes */
		goto FinalCheck;
	}

//	if( ioPtr->scsiFunctionCode != SCSIOldCall ) {
//		if( ioPtr->scsiDataType == kTib )
//			finalStatus = scsiProvideFail;		/* TIBs not supported */
//			goto FinalCheck;
//	}
	
	if( !( (1<<(ioPtr->scsiDataType)) & SIMg->HALinfo.supported_scDataTypes) ) {
		finalStatus = scsiDataTypeInvalid;		/* data type not supported */
		goto FinalCheck;
	}
		
	if( ioPtr->scsiTransferType > kMaxTransferType ) {
		finalStatus = scsiTransferTypeInvalid;		/* xfer type too high */
		goto FinalCheck;
	}
		
		
FinalCheck:		
	if( finalStatus != noErr ) {
		ioPtr->scsiResult = finalStatus;
		IfRecordEvent( (long)ioPtr, (long)'InvC');
		CallCompRoutine( (SCSI_IO *)ioPtr);	/* Whoops, not a valid PB */
		return(false);
	}
	return(true);
}


/*********************************************************************************
	ValidateDeviceIdent -	Makes sure the target ID is valid
*********************************************************************************/

OSErr
ValidateDeviceIdent( DeviceIdent devIdent, SIMglobals * SIMg )
{

	if( devIdent.targetID > kHighestTarget )/*  Make Sure ID is in range <SM4>*/
		return( scsiTIDInvalid);
		
	if( devIdent.targetID == SIMg->hostID )	/* Can't allow Mac's id 	 <SM4>*/
		return( scsiTIDInvalid);
		
	if( devIdent.LUN > 7 )	/* Allow all 8 LUNs */
		return( scsiLUNInvalid);
		
	return( noErr );
}


/*********************************************************************************
	StartMachine 	-	if SSM isn't already running, start machine if there
						is a ready IO or R_select waiting
*********************************************************************************/

Boolean
StartMachine( SIMglobals * SIMg)
{
	Boolean			wasBusy;
	ushort			oldSR;
	
	wasBusy = bset(kbSSMBusy, &SIMg->SSMflags);

	if (wasBusy)
		return( false);		// didn't get the state machine this time

	oldSR = BlockInterrupts();	//-> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> ->
	
		
		if ( SIMg->r_selectWaiting)
		{
			SIMg->state = kGotR_selected;
		}
		else if ( 0!=( SIMg->halPB.ioPtr= GetNextReadyIO(SIMg) ))
		{
			SIMg->state = kIdle;
		}
		else
		{
			(void) bclr(kbSSMBusy, &SIMg->SSMflags);
			UnblockInterrupts( oldSR); 
			return( false);				// nothing to do so don't start machine
		}
	
	UnblockInterrupts( oldSR); //<- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- 

	SIMg->halPB.result = noErr;	
	
	return( true);		// we did get the machine and we do have something to do
}



/*********************************************************************************
	NewIOStartMachine 	-	if SSM isn't already running, start it
*********************************************************************************/

void
NewIOStartMachine(SIMglobals * SIMg)
{
	IfRecordEvent( sp(), (long)'NwIO');

	if (StartMachine( SIMg))
		CallMachine( SIMg);
}



/*********************************************************************************
	ReconnectISR 	-	
*********************************************************************************/

void
ReconnectISR( SIMglobals * SIMg)
{
	SIMg->r_selectWaiting = true;

	if (StartMachine( SIMg))
		CallMachine( SIMg);
}



/*********************************************************************************
	FreeMachine 	-	free up SSM so that another connection can use it
*********************************************************************************/

void
FreeMachine( OSErr finalStatus, SIM_IO * ioPtr, SIMglobals * SIMg)
{
	Boolean			doingAutosense;

	if (ioPtr) 
	{
	//ÉÉÉ this is order-critical - we should free up the machine before calling comprtn in case of a sync req
	//		from the comprtn
	
		doingAutosense = CheckErrors( finalStatus, ioPtr, SIMg);					
		SIMg->state = kIdle;
		(void) bclr(kbSSMBusy, &SIMg->SSMflags);
		if( !doingAutosense )
			CompleteIO( finalStatus, ioPtr, SIMg);					
	}
	else {
		SIMg->state = kIdle;
		(void) bclr(kbSSMBusy, &SIMg->SSMflags);
	}

	if (StartMachine( SIMg))
		CallMachine( SIMg);
}



/*********************************************************************************
	CompleteIO 	-	
*********************************************************************************/

void
CompleteIO( OSErr finalStatus, SIM_IO * ioPtr, SIMglobals * SIMg )
{
	
	IfRecordEvent( (long)(ioPtr), (long)'CpIO');
	
	DeQIO( ioPtr, SIMg );									// <SM2>
	
//--- if we don't yet have an error reported on this IO request,  
//		check for data run problem or a non-zero SCSI status

	if ( finalStatus==noErr ) {
		if ( ioPtr->scsiSCSIstatus!=0 ) {
			finalStatus = scsiNonZeroStatus;
			IfRecordError(finalStatus);
		}
		else if ( ioPtr->firstError) {
			finalStatus = ioPtr->firstError;
			IfRecordError(finalStatus);
		}
		else if ( ioPtr->scsiDataResidual != 0 || ( ioPtr->SIMprivFlags & kmBitBucketed) ) {
			finalStatus = scsiDataRunError;
			IfRecordError(finalStatus);
		}
	}
	else {
		IfRecordError(finalStatus);
	}
	
//--- If we tried to send a message (abort, TermIO etc) we need to figure out what happened to it
//		and call the completion routine for the control parameter block that was responsible for the message
//		Note that even if multiple events happened we can only report one in an error message... <LW9>

// %%%!!! Move this elsewhere - we don't need to check for a parity error on every I/O
	if( ioPtr->ioEvent & kmBadParity )
		finalStatus = scsiParityError;
	else if( ioPtr->pendingMsgPB ) {
		if( ioPtr->ioEvent & kmTimedOut ) 						// <SM7>
			finalStatus = scsiCommandTimeout;
		else if( ioPtr->ioEvent & kmAborted ) 
				finalStatus = (ioPtr->ioEvent & kmMsgRejected ) ? scsiUnableToAbort : scsiRequestAborted;
		else if( ioPtr->ioEvent & kmTerminated ) 
				finalStatus = (ioPtr->ioEvent & kmMsgRejected ) ? scsiUnableToTerminate : scsiTerminated;
		else if( ioPtr->ioEvent & kmBDRSent ) 
				finalStatus = (ioPtr->ioEvent & kmMsgRejected ) ? scsiMessageRejectReceived : scsiBDRsent;
		((SCSIHdr *)((SIM_IO *)ioPtr->pendingMsgPB))->scsiResult = noErr;
		IfRecordEvent( (long)ioPtr->pendingMsgPB, (long)'PndC');
		CallCompRoutine( (SCSI_IO *)ioPtr->pendingMsgPB);
	}
	
	/* unlock the user's buffers if necessary				  <SM6> DCB */
	if( (ioPtr->SIMprivFlags & (1 << kbSetupComplete)) != 0 )
	{
		CallHALTeardownIO( ioPtr, SIMg->HALinfo.HALstaticPtr);
	}
	
	ioPtr->scsiResult = finalStatus;
	CallCompRoutine( (SCSI_IO *)ioPtr);
}


/*********************************************************************************
	CallCompRoutine 	-	
*********************************************************************************/

void
CallCompRoutine( SCSI_IO * ioPtr )		// <SM7>
{
	VMEnableUserCode();						// we're safe now
	
	XPTCallCompRoutine( ioPtr);		// MAKE CALLBACK	
	
	VMDisableUserCode();					// and now we're not safe again	
}


/*********************************************************************************
	CheckErrors 	-	check for errors and do queue maintenance
*********************************************************************************/

Boolean 
CheckErrors( OSErr finalStatus, SIM_IO * ioPtr, SIMglobals * SIMg )
{
	SIM_IO *	originalPB;
	ushort		oldSR;
	
// If this was a return from an autosense ÉÉÉÉÉÉÉÉÉÉÉÉ
	
	if( ioPtr == &SIMg->sensePB ) {
	
		originalPB = (SIM_IO *)ioPtr->scsiDriverStorage;	/* We stuffed it here earlier */
		
		if( finalStatus == noErr )	/* Request Sense succeeded */
			originalPB->scsiResultFlags |= scsiAutosenseValid;

		originalPB->ioEvent |= kmAutoSense;	// Remember that we did autosense

		CheckErrors( originalPB->savedResult, originalPB, SIMg );	/* Freeze LUN if necessary */

		return(false);	/* Now do CompleteIO for the Request Sense which will 
						   do a CompleteIO for the original Parameter block
						*/

	}

	/* Check if there was a check condition
			If check condition and autosense
				If the autosense PB is available
					Fill in the autosense PB
						Set the "Enqueue at Head" bit
						use ioPB's autosense buffer
					Enqueue autosense PB
				else
					remember that we are in line for autosense
				Remember the final status for later
			return;		That is let the autosense's instance of CheckErrors worry about the queue
	*/
	   
// if we're being called before autosense ÉÉÉÉÉÉÉÉÉÉÉÉ

	if ( !(ioPtr->ioEvent & kmAutoSense) ) 	// Just because it isn't valid doesn't mean we didn't try...
	{
		// if we need to do an autosense
		if ( ioPtr->scsiSCSIstatus == scsiStatCheckCondition
				 && !(ioPtr->scsiFlags & scsiDisableAutosense)
				 && (ioPtr->scsiSenseLength) )
		{
			oldSR = BlockInterrupts();	//-> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> ->
			SIMg->senseWaiting+=1;
			ioPtr->ioStat = kNeedsSense;
			ioPtr->savedResult = finalStatus;
			if ( ! SIMg->sensePBBusy ) {
				SIMg->sensePBBusy = true;
				SetupSensePB(ioPtr,SIMg);	/* Sets the "Enqueue at head" bit */
				EnQIO(&SIMg->sensePB,SIMg);
			}
			UnblockInterrupts( oldSR); //<- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- 

			/* Return true so completeIO doesn't get called */
			return(true);	/* SwitchPhase is next up - should startup the autosense */
		}
	}
	
	/*	If (there was an error - or we were supposed to freeze the queue)
		AND it is OK to freeze the queue - then freeze it.
	*/
	if( (finalStatus != noErr
			|| ioPtr->scsiSCSIstatus != 0
			|| (ioPtr->scsiFlags & scsiSIMQFreeze))
			&& (ioPtr->scsiFlags & scsiSIMQNoFreeze) == 0 ) {
		FreezeLUN( ioPtr->scsiDevice.targetID, ioPtr->scsiDevice.LUN);
		ioPtr->scsiResultFlags |= scsiSIMQFrozen;
	}
	
	return(false);
}


/*********************************************************************************
	SetupSensePB 	-	setup the parameter block for an automatic request sense
*********************************************************************************/

void
SetupSensePB( SIM_IO * ioPtr, SIMglobals * SIMg )
{
	uchar *cmd;
	
	cmd = (uchar *)&SIMg->sensePB.scsiCDB;

	SIMg->sensePB.scsiResult = scsiRequestInProgress;	// EnqIO doesn't do this anymore... <SM10> 

	cmd[0] = 0x03;		/* Request Sense */
	cmd[1] = (ioPtr->scsiDevice.LUN) << 5;	/* Fill in LUN */
	
	cmd[2] = 0;		
	cmd[3] = 0;		
	cmd[4] = ioPtr->scsiSenseLength;	
	cmd[5] = 0;		

	SIMg->sensePB.scsiCDBLength = 6;
	
	SIMg->sensePB.scsiPBLength = sizeof(SIM_IO);

	SIMg->sensePB.scsiDataPtr = ioPtr->scsiSensePtr;
	SIMg->sensePB.scsiDataLength = ioPtr->scsiSenseLength;

	if ( (ioPtr->scsiIOFlags & scsiRenegotiateSense) && SIMg->syncRAoffset[ioPtr->scsiDevice.targetID])
		SIMg->sensePB.scsiFlags = scsiInitiateSyncData;

	SIMg->sensePB.scsiFlags |= scsiDirectionIn | scsiSIMQHead |		/* MUST enqueue at the head!!! */
			(ioPtr->scsiFlags & (
				scsiDoDisconnect	|
				scsiDontDisconnect));

	SIMg->sensePB.scsiIOFlags = scsiNoParityCheck | 
			(ioPtr->scsiIOFlags & (
				scsiDisableSelectWAtn	|
				scsiSavePtrOnDisconnect));
				
	SIMg->sensePB.scsiDevice = ioPtr->scsiDevice;
		
	SIMg->sensePB.scsiDriverStorage = (uchar *) ioPtr;
	SIMg->sensePB.scsiCompletion = CompAutoSense;
	
	SIMg->sensePB.scsiTransferType = scsiTransferPolled;

	SIMg->sensePB.scsiFunctionCode = SCSIExecIO;

}


/*********************************************************************************
	SetupResetPB 	-	setup the parameter block for a reset device <SM3>
*********************************************************************************/

void
SetupResetPB( uchar TargetID, SIMglobals * SIMg )
{
	uchar *cmd;
	
	cmd = (uchar *)&SIMg->sensePB.scsiCDB;

	cmd[0] = 0x00;		/* TUR - Something Safe */
	cmd[1] = 0;	
	cmd[2] = 0;		
	cmd[3] = 0;		
	cmd[4] = 0;	
	cmd[5] = 0;		

	SIMg->resetDevPB.scsiPBLength = sizeof(SIM_IO);

	SIMg->resetDevPB.scsiCDBLength = 6;

	SIMg->resetDevPB.scsiFlags = scsiDirectionNone | scsiSIMQHead;	/* enqueue at the head */
	SIMg->resetDevPB.scsiDevice.targetID = TargetID;		/* Entire device will get reset */
		
	SIMg->resetDevPB.scsiDriverStorage = 0;
	SIMg->resetDevPB.scsiCompletion = CompResetDevice;								// <LW3>
	
	SIMg->resetDevPB.scsiFunctionCode = SCSIExecIO;

}


/*********************************************************************************
	CompAutoSense 	-	autosense PB completion routine 
*********************************************************************************/

pascal void
CompAutoSense( SIM_IO * senseIOPtr )
{
	SIM_IO *	nextSense;
	SIM_IO *	originalIOPtr;
	SIMglobals	* SIMg;	
	ushort		oldSR;

	VMDisableUserCode();
	
	// Get stuff from autosense PB that we need for original request and get SIMg 	

	originalIOPtr = (SIM_IO *)senseIOPtr->scsiDriverStorage;
	SIMg = (SIMglobals *)senseIOPtr->SIMg;
	originalIOPtr->scsiSenseResidual = senseIOPtr->scsiDataResidual;
	originalIOPtr->ioStat = kGotSense;	// Don't decrement senseWaiting in Dequeue

	// Get the next PB which is waiting with Check Condition
	
	oldSR = BlockInterrupts();	//-> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> ->
	if ( --(SIMg->senseWaiting) > 0 ) {
		nextSense = GetNextAutoSense( SIMg);
		if (!nextSense) {
			IfDebugStr("\psenseWaiting !=0 but none say kNeedsSense");
			SIMg->senseWaiting = 0;
			SIMg->sensePBBusy = 0;
		} 
		else {
			SetupSensePB( nextSense, SIMg);
			EnQIO( senseIOPtr, SIMg);
			NewIOStartMachine( SIMg);			/* Kick it off */
		}
	}
	else {
		SIMg->sensePBBusy = false;
	}
	UnblockInterrupts( oldSR); //<- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- 
	
	//  call the original PB's completion routine <SM10>
	CompleteIO( originalIOPtr->savedResult, originalIOPtr, SIMg);

	VMEnableUserCode();
}


/*********************************************************************************
	CompResetDevice 	-	reset device PB completion routine 
*********************************************************************************/

pascal void
CompResetDevice( SIM_IO * ioPtr )								// <SM3>
{
	int				TargetID;
	SIMglobals *	SIMg;
	SCSI_PB *		oldRDPtr;
	SCSI_PB *		newRDPtr;
	
	SIMg = (SIMglobals *)ioPtr->SIMg;
	
//	oldRDPtr = ioPtr->pendingMsgPB;			// this is what we want to move to
	oldRDPtr = (SCSI_PB *)(SIMg->resetPBQ.qHead);					// <LW3> removed call to comp routine
	if ( !oldRDPtr)  {
		IfDebugStr("\pNo qHead in CompResetDevice");
		SysError( dsIOCoreErr);
	}
	else if ( oldRDPtr != ioPtr->pendingMsgPB) {
		IfDebugStr("\pqHead != ioPtr->pendingMsgPB  (in CompResetDevice)");
		SysError( dsIOCoreErr);
	}
	else
		Dequeue( (QElemPtr)oldRDPtr, &SIMg->resetPBQ);
	
	/* Get the next Device which needs to be reset */
	
	newRDPtr = (SCSI_PB *)(SIMg->resetPBQ.qHead);
	if ( newRDPtr ) 
	{
		TargetID = newRDPtr->scsiDevice.targetID;
		SetupResetPB( TargetID, SIMg);
		EnQIO( &(SIMg->resetDevPB), SIMg);
		SIMg->resetDevPB.pendingMsgPB = (Ptr) newRDPtr;		/* Remember who started this <LW2> */
		NewIOStartMachine( SIMg);			/* Kick it off */
	}
}


