/*
	File:		SIMmachine.c

	Contains:	routines that implement the SCSI state machine

	Entry points:
		
				

	Written by:	Paul Wolf

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SM22>	12/19/93	DCB		Clear hdshkRemainder when we reconnect.  This is to help solve
									the handshake across scatter gather boundries problem.
	  <SM21>	11/22/93	pdw		Rolling in from <MCxx>.
	   <MC7>	 11/9/93	pdw		Fixed a problem with the CD300 rejecting an identify message.
									We now handle it and return an error.
	   <MC6>	 11/8/93	pdw		Added some handling of unexpected bus free.
	   <MC5>	 11/5/93	pdw		Series of attempts and re-attempts to fix various VM/FileShare
									problems.
	  <SM20>	10/29/93	DCB		<MC> roll-in.
	   <MC4>	10/28/93	pdw		Added a couple of states for use during Target mode.
	  <SM19>	10/14/93	pdw		<MC> roll-in.
	   <MC3>	10/12/93	pdw		Fixed some bugs in some messaging corner cases.
	   <MC2>	10/12/93	pdw		Added support for Synchronous data transfers, rewrote State
									Machine, message handling etc.
	  <SM18>	 8/13/93	pdw		Changing the message handling in DoComplete.
	  <SM17>	 7/17/93	pdw		Lots of little things.  A few big things.
	  <SM16>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
									stack switching mechanism.  Adding support for Cold Fusion.
									Rearranging HW/SW Init code. Some code optimizations. Resolving
									with my Ludwig sources.
	  <SM15>	 5/29/93	PW		Adding include of SCSIDebug.h
	  <SM14>	 5/25/93	DCB		Rollin from Ludwig. (The next item below)
	  <LW17>	 5/21/93	PW		Timeout bugs fixed.  DebugStr stuff.  Last minute target mode
									changes.
	  <SM13>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	  <LW16>	  5/1/93	PW		Changed xxxResidualLength to xxxResidual.
	  <LW15>	 4/30/93	DCB		Adding CallBusInquiry function so that we don't have to busy the
									HALAction routine.
	  <LW14>	 4/29/93	DCB		Fixing Build - Sorry bout that.
	  <LW13>	 4/14/93	DCB		Added calls the the SetParity HALAction for each reconnect and
									successful initiate.
	  <LW12>	 3/26/93	PW		Rolled in SuperMario changes. Removed useless RejectMsg stuff. A
									few little optimizations. Fixed bug in autosense that showed up
									when deferring completions and fixed bug in ResetDevice. Added
									kWastePhase to bit bucket an unknown phase.
	  <LW11>	 3/22/93	DCB		Adding code to reject an identify message from an unknown
									re-select to fix a test tool bug with the Seagate 400.
	  <SM12>	 3/20/93	PW		Moving CallCompRoutine into SIM so that it can call
									ExitingSIM/EnteringSIM instead of XPT.
	  <LW10>	 3/22/93	PW		Rolling in SuperMario changes. Removing useless RejectMsg stuff.
									Few little optimizations.
	   <LW9>	  3/1/93	DCB		Re-worked message handling. This included changing the use of
									the event field for better tracking of abort and terminate IO
									and fixing the message reject code.
	   <LW8>	 2/18/93	DCB		Added check for Bus Free phase before setting ATN to send a
									message. The c96 will bit bucket the next command after an
									illegal set of ATN causing a sync-wait hang.
	   <LW7>	 2/17/93	PW		Optimizations - Removed some unneeded "what" usages and got rid
									of halPtr in Machine. Also got rid of halPBptr parameter in
									SwitchPhase and Reconnect. Added check for status phz just after
									recon to avoid implied restore pointers (for IBM drives). Fixed
									DontDisconnect bug.
	  <SM10>	 1/31/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <LW6>	 1/27/93	PW		Fixed VM 'too many enables' bug by doing the 'double completion
									routine on autosense' stuff the right way - I call VMDisable and
									EnableUserCode at top and bottom of CompAutoSense.
	   <LW5>	 1/12/93	DCB		Fixed handling of IOevent so that timeouts were reported as
									timeouts rather than aborted commands.
	   <LW4>	  1/8/93	PW		Added RestorePointers call upon acceptance of Identify message
									during a reconnect.
	   <LW3>	  1/4/93	DCB		Fixed SetupResetPB so that it fills in the completion routine
									field.  The lack of the completion routine caused asynchronous
									ResetDevice calls to get stuck in a SyncWait.  This fixes Radar
									bug 1059424 .
	   <LW2>	12/17/92	DCB		Fixed a bug in the auto-request sense feature which caused a
									sync-wait hang.
	   <SM9>	 12/9/92	PW		Added check for invalid scsiIOFlags.
	   <SM8>	 12/5/92	PW		Changed ValidateDI to return appropriate error instead of
									Boolean.
	   <SM7>	11/20/92	DCB		Support for async Abort, Terminate and Reset Device
	   <SM6>	10/30/92	DCB		Added call to Teardown routines to support Direct DMA into a
									user buffer
	   <SM5>	 10/8/92	PW		(dcb) Added support for variable-sized SCSI_IO.  Fixed AbortCmd
									bug which required addition of an ioEvent field.
	   <SM4>	 9/14/92	DCB		Added some parameter block validation
	   <SM3>	 9/11/92	DCB		Made numerous changes to the state machine so that the bus
									wouldn't hang after a failed TerminateIO or Abort Command. Also
									added BusDeviceReset.
	   <SM2>	 8/31/92	DCB		Implementing Terminate/Abort IO

*/

#include <Types.h>
#include <Memory.h>
#include <Errors.h>
#include <SCSIStandard.h>
#include <SCSI.h>

#include "ACAM.h"
#include "XPT.h"
#include "XPTpriv.h"
#include "CUtils.h"
#include "SCSIGlue.h"

#include "SIMCore.h"
#include "SIMCorePriv.h"
#include "SIMQ.h"

#include "SCSIDebug.h"
#include "Recorder.h"


/********* External Function Prototypes **********/


/********* Internal-only Function Prototypes **********/

void	SwitchPhase( SIM_IO * ioPtr, SIMglobals * SIMg);
void	EarlySwitchPhase( SIM_IO * ioPtr, SIMglobals * SIMg);
void	WastePhase( SIM_IO * ioPtr, SIMglobals * SIMg);
void	Reconnect( SIMglobals * SIMg);
void	HandleEarlyMsgIn( SIM_IO * ioPtr, SIMglobals * SIMg);
void	HandleNoIdentifyMsg( SIM_IO * ioPtr, SIMglobals * SIMg);
void	HandleRejectedIdentify( SIM_IO * ioPtr, SIMglobals * SIMg);
void	HandleInitWErr( SIM_IO * ioPtr, SIMglobals * SIMg);

/*********************************************************************************
	Machine 	-	the actual SSM!
*********************************************************************************/
/*
	The SSM works with the HAL to transact a SCSI connection.  The communication
	between the SSM and HAL occur via a HALactionPB which is allocated in the 
	SIM's globals.  The same HALactionPB is used from the time of Initiation to
	Disconnection.
*/

Boolean		// freeTheMachine
TheMachine( OSErr * finalStatus, SIM_IO ** completedIO, SIMglobals * SIMg)
{
	HALresult		result;
	HALactions		halAct;
	SIM_IO *		ioPtr;
	uchar			targetID;
	uchar			LUN;
	

	ioPtr	 = 	SIMg->halPB.ioPtr;								// <SM2>
	targetID =	ioPtr->scsiDevice.targetID;

/********** STATE MACHINE **********/

	do 
	{
	result =	SIMg->halPB.result;

	/* If we are connected to an io which needs a message - assert ATN
	   SwitchPhase will figure out how to actually send it
	*/
	if (ioPtr) if (ioPtr->pendingMsgPB)			// guarantee that this is the first test of the if
	{
		if (SIMg->state != kIdle &&
			SIMg->state != kGotR_selected &&
			(ioPtr->ioEvent & kmMsgSent) == 0 &&					// <LW9>
			SIMg->halPB.phase != kBusFreePhase ) 
		{
			if (SIMg->halPB.phase == kStatusPhase) 
			{
				switch( ((SCSIHdr *)(ioPtr->pendingMsgPB))->scsiFunctionCode) {	// <SM7>
					
				case SCSITerminateIO:
					((SCSIHdr *)(ioPtr->pendingMsgPB))->scsiResult = scsiUnableToTerminate;
					IfRecordEvent( (long)ioPtr->pendingMsgPB, (long)'TrmC');
					CallCompRoutine( (SCSI_IO *)ioPtr->pendingMsgPB);
					(SCSI_IO *)ioPtr->pendingMsgPB = nil;
					break;
				case SCSIAbortCommand:
					((SCSIHdr *)(ioPtr->pendingMsgPB))->scsiResult = scsiUnableToAbort;
					IfRecordEvent( (long)ioPtr->pendingMsgPB, (long)'AbtC');
					CallCompRoutine( (SCSI_IO *)ioPtr->pendingMsgPB);
					(SCSI_IO *)ioPtr->pendingMsgPB = nil;
					break;
				case SCSIResetDevice:
					break;
				}															//	<SM7>
			}
			else {	// (not status phase)
				CallHALAssertATN( SIMg->HALinfo.HALstaticPtr);	
			}
		}
	}
	

	IfRecordEvent( (long)((SIMg->state<<16) + result), (long)'Mach');

	switch (SIMg->state) 
	{
	
//==== IDLE ====

	case kIdle:

		if (ioPtr->scsiFunctionCode != SCSIOldCall)		
		{
		//ÑÑÑÑ NEW API ÑÑÑÑÑÑ

			// Set up for sending an Identify message during Initiate
			//	depending on our default disc, we check the other Do/DonÕt flag to make sure

			if (SIMg->defaultDisc) {
				if ( ioPtr->scsiFlags & scsiDontDisconnect)	// if default=Do but client says DonÕt
					SIMg->halPB.msg[0] = IdentifyMsg( false, ioPtr->scsiDevice.LUN);
				else 
					SIMg->halPB.msg[0] = IdentifyMsg( true, ioPtr->scsiDevice.LUN);
			}
			else {
				if ( ioPtr->scsiFlags & scsiDoDisconnect)		// if default=DonÕt but client says Do
					SIMg->halPB.msg[0] = IdentifyMsg( true, ioPtr->scsiDevice.LUN);
				else
					SIMg->halPB.msg[0] = IdentifyMsg( false, ioPtr->scsiDevice.LUN);
			}

			if (SIMg->syncRAoffset[targetID]) {
				CallHALSyncConfig(	SIMg->syncRAoffset[targetID],
									SIMg->syncPeriod  [targetID], SIMg->HALinfo.HALstaticPtr );
			}
			SIMg->halPB.msgOutLen = 1;			// only 1 byte for now, Identify
			SIMg->halPB.sendCDB = true;

			SIMg->state = kInitiatingNormal;


			// Check to see if this is a forced reconnection for the purpose of 
			// issuing an abort, terminate io or reset device message

			if( ioPtr->pendingMsgPB ) 
			{
				switch( ((SCSI_PB *)ioPtr->pendingMsgPB)->scsiFunctionCode) {	//	<SM7>
					
				case SCSITerminateIO:
					SIMg->halPB.msg[1] = kTerminateIOProcessMsg;
					break;
				case SCSIAbortCommand:
					SIMg->halPB.msg[1] = kAbortMsg;
					break;
				case SCSIResetDevice:
					SIMg->halPB.msg[1] = kBusDeviceResetMsg;
					break;
				
				}
				SIMg->halPB.msgOutLen = 2;
				SIMg->halPB.sendCDB = false;

				ioPtr->ioEvent |= (kmMsgSent);		// we'll undo this if it fails

				SIMg->state = kInitiatingAsyncMsg;
			}
			else
			{
			// Check for need to perform Synchronous Data Transfer negotiation
			
				if ( (ioPtr->scsiFlags & (scsiInitiateSyncData | scsiDisableSyncData)) ||
					SIMg->needNegot[targetID] )
				{
					SIMg->halPB.msg[1] = 0x01;		// extended message
					SIMg->halPB.msg[2] = 0x03;		// length
					SIMg->halPB.msg[3] = 0x01;		// SDTR
					SIMg->halPB.msg[4] = SIMg->HALinfo.minPeriodFactor;	// transfer period
					if (ioPtr->scsiFlags & scsiDisableSyncData) {
						SIMg->halPB.msg[5] = 0;		// asynchronous
					}
					else {
						SIMg->halPB.msg[5] = SIMg->HALinfo.syncRAoffset; // REQ/ACK offset
					}
				SIMg->halPB.msgOutLen = 6;
				SIMg->halPB.sendCDB = false;

				SIMg->state = kInitiatingSDTR;
				}
			}
			// Start initiation process (this could come back w/ a recon)

			ioPtr->ioStat = kAttemptingInitiation;
			CallHALaction( kInitiate, &SIMg->halPB, SIMg);
		}

		else	// ioPtr->scsiFunctionCode == SCSIOldCall
		{
		//ÑÑÑÑ OLD API ÑÑÑÑÑÑ
			
			ioPtr->ioStat = kAttemptingInitiation;
			SIMg->state = kInitiatingOldCall;
			CallHALaction( kSelect, &SIMg->halPB, SIMg);
		}
		
		break;

		
//==== GotR_selected In Progress ====
	
	case kGotR_selected:	

		CallHALaction( kGetReconnectInfo, &SIMg->halPB, SIMg);	// always synchronous call
		if ( SIMg->halPB.result == kHALreselected) {	// really was a reconnect
			Reconnect( SIMg);
			ioPtr = SIMg->halPB.ioPtr;			// Reconnect can change which IO we're doing
			targetID = ioPtr->scsiDevice.targetID;
		}
		else if ( SIMg->halPB.result == kHALselectedAsTarget) {
			SIMg->state			= kHandlingSelected;
			SIMg->pushedState	= kFreeMachine;		// after select is done, free the machine
		}
		
		break;

		
//==== HandlingSelected In Progress ====
	
	case kHandlingSelected:	

		SIMg->r_selectWaiting = false;
		CallHALaction( kHandleSelected, &SIMg->halPB, SIMg);
		SIMg->state = SIMg->pushedState;
		
		break;

		
//==== INITIATE In Progress - Normal ====
	
	case kInitiatingNormal:	

		if (!result) //== noErr
		{
			ioPtr->ioStat = kSentCommand;
			SwitchPhase( ioPtr, SIMg);
		}
		else if (result == kHALreselected)
		{
			ioPtr->ioStat = kPBidle;			// go back to Idle for this one
			Reconnect( SIMg);
			ioPtr = SIMg->halPB.ioPtr;			// Reconnect can change which IO we're doing
			targetID = ioPtr->scsiDevice.targetID;
		}
		else 
		{
			HandleInitWErr( ioPtr, SIMg);
			ioPtr = SIMg->halPB.ioPtr;			// Reconnect can change which IO we're doing
			targetID = ioPtr->scsiDevice.targetID;
		}	
		break;

		

//==== INITIATE In Progress - SDTR ====
	
	case kInitiatingSDTR:	

		if (!result)
		{
			if (SIMg->halPB.msgInLen == 6) 
			{
				if ((SIMg->halPB.msg[1] == 0x01) && (SIMg->halPB.msg[3] == 0x01)) {
					SIMg->syncPeriod  [targetID] = SIMg->halPB.msg[4];	// transfer period
					SIMg->syncRAoffset[targetID] = SIMg->halPB.msg[5]; 	// REQ/ACK offset
	
					CallHALSyncConfig(	SIMg->syncRAoffset[ioPtr->scsiDevice.targetID],
										SIMg->syncPeriod  [ioPtr->scsiDevice.targetID], SIMg->HALinfo.HALstaticPtr );

					CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
				}
			}
			else  {
				SIMg->syncRAoffset[targetID] = 0;
				if ((SIMg->halPB.msgInLen == 1)  && (SIMg->halPB.msg[0] == kMsgRejectMsg))
				{
					CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
				}
			}
			EarlySwitchPhase( ioPtr, SIMg);
		}
		else if (result == kHALreselected)
		{
			ioPtr->ioStat = kPBidle;			// go back to Idle for this one
			Reconnect( SIMg);
			ioPtr = SIMg->halPB.ioPtr;			// Reconnect can change which IO we're doing
			targetID = ioPtr->scsiDevice.targetID;
		}
		else 
		{
			HandleInitWErr( ioPtr, SIMg);
			ioPtr = SIMg->halPB.ioPtr;			// Reconnect can change which IO we're doing
			targetID = ioPtr->scsiDevice.targetID;
		}	
			
		break;


//==== INITIATE In Progress - AsyncMsg ====
	
	case kInitiatingAsyncMsg:	

		if (!result)
		{
			if (SIMg->halPB.phase == kBusFreePhase) 
			{
				switch( ((SCSI_PB *)ioPtr->pendingMsgPB)->scsiFunctionCode) 
				{
				case SCSITerminateIO:
					ioPtr->ioEvent |= (kmTerminated | kmMsgSent);
					// Remove this IO from the Disconnected array since we aborted cmd
					SIMg->discIOs [targetID] [ioPtr->scsiDevice.LUN] = 0;
					SIMg->LUNstate[targetID] [ioPtr->scsiDevice.LUN] &= ~km_LUNdisconnected;
					break;
	
				case SCSIAbortCommand:
					ioPtr->ioEvent |= (kmAborted | kmMsgSent);	
					// Remove this IO from the Disconnected array since we aborted cmd
					SIMg->discIOs [targetID] [ioPtr->scsiDevice.LUN] = 0;
					SIMg->LUNstate[targetID] [ioPtr->scsiDevice.LUN] &= ~km_LUNdisconnected;
					break;
	
				case SCSIResetDevice:
					ioPtr->ioEvent |= (kmBDRSent | kmMsgSent);	
					for( LUN = 0; LUN < 8; LUN+=1 ) {
						SIMg->discIOs [targetID][LUN] = 0;
						SIMg->LUNstate[targetID][LUN] &= ~km_LUNdisconnected;
					}
					break;
				}
				*finalStatus = result;
				*completedIO = ioPtr;
				return (true);
			}
			else if ((SIMg->halPB.phase == kMessageInPhaseNACK) && (SIMg->halPB.msg[0] == kMsgRejectMsg))
			{
				CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
				SIMg->state = kAcceptingRejectedAsyncMsg;
				break;
			}	
			else {
				*finalStatus = scsiUnableToAbort;
				WastePhase( ioPtr, SIMg);
			}
		}
		else if (result == kHALreselected)
		{
			ioPtr->ioStat = kPBidle;			// go back to Idle for this one
			Reconnect( SIMg);
			ioPtr = SIMg->halPB.ioPtr;			// Reconnect can change which IO we're doing
			targetID = ioPtr->scsiDevice.targetID;
		}
		else
		{
			HandleInitWErr( ioPtr, SIMg);
			ioPtr = SIMg->halPB.ioPtr;			// Reconnect can change which IO we're doing
			targetID = ioPtr->scsiDevice.targetID;
		}	

		break;


//==== INITIATE In Progress - OldCall ====

	case kInitiatingOldCall:		
			
		ioPtr->scsiCurrentPhase = SIMg->halPB.phase;
		if (result == noErr) 
		{
			SIMg->state = kAwaitingOldCall;
			ioPtr->ioStat = kSelectComplete;
			ioPtr->scsiOldCallResult = noErr;
			return (false);
		}
		else if (result == kHALreselected) 	// i.e. we got reselected
		{
			ioPtr->ioStat = kPBidle;			// go back to Idle for this one
			Reconnect( SIMg);
			ioPtr = SIMg->halPB.ioPtr;			// Reconnect can change which IO we're doing
			targetID = ioPtr->scsiDevice.targetID;
			break;
		}
		else if (result == kHALselectedAsTarget) 	// we got selected
		{
			SIMg->state			= kHandlingSelected;
			SIMg->pushedState	= kIdle;		// after select is done, retry this IO initiation
			break;
		}
		else if (result == kHALselectFld) 
		{
			*finalStatus = scsiSelectTimeout;
		}
		else 
		{
			*finalStatus = result;
		}
		
		ioPtr->scsiOldCallResult = *finalStatus;
		
		if (SIMg->halPB.phase == kBusFreePhase)
		{
			*completedIO = ioPtr;
			return (true);
		}
		else {
			return (false);
		}
		break;


//==== Accepting Msg after Rejected Async Msg ====

	case kAcceptingRejectedAsyncMsg:

		if (SIMg->halPB.phase == kBusFreePhase)
		{
			ioPtr->ioEvent |= (kmMsgSent);	
			*finalStatus = scsiMessageRejectReceived;
			*completedIO = ioPtr;
			return (true);
		}
		WastePhase(ioPtr, SIMg);
		break;
		

//==== Accepting Msg after Rejected Identify Msg ====

	case kAcceptingRejectedIdentify:
	
		if (SIMg->halPB.phase == kMessageOutPhase)
		{
			SIMg->halPB.msg[0] = kAbortMsg;
			SIMg->halPB.msgOutLen = 1;
			SIMg->state = kAbortingRejectedIdentify;
			CallHALaction( kSendMsgOut, &SIMg->halPB, SIMg);
		
		} else if (SIMg->halPB.phase == kBusFreePhase)
		{
			*finalStatus = scsiIdentifyMessageRejected;
			*completedIO = ioPtr;
			return (true);
		}
		break;


//==== Aborting IO after Rejected Identify Msg ====

	case kAbortingRejectedIdentify:
	
		if (SIMg->halPB.phase == kBusFreePhase)
		{
			*finalStatus = scsiIdentifyMessageRejected;
			*completedIO = ioPtr;
			return (true);
		}
		else if (SIMg->halPB.phase == kMessageInPhaseNACK)
		{
			//if (SIMg->halPB.msg[0]==kMsgRejectMsg)	enough of this, just accept it
				CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
			SIMg->state = kEarlySwitchingPhase;
		}	
		break;


//==== RECONNECT - Accepting Identify Message ====

	case kReconAcceptingMsg:		

		if (ioPtr->ioStat == kDisconnected)	
		{
			// for IBM drives, that don't do SaveDataPointer on last data connection of a write
			if (SIMg->halPB.phase != kStatusPhase)
				CallHALaction( kRestorePointers, &SIMg->halPB, SIMg);
			SwitchPhase( ioPtr, SIMg);
		}
		else
			EarlySwitchPhase( ioPtr, SIMg);

		break;

	
//==== Sending Message ====

	case kSendingEarlyKillMsg:
	case kSendingKillMsg:		

		if (!result)
		{
			switch( ((SCSI_PB *)(ioPtr->pendingMsgPB))->scsiFunctionCode) {
				
			case SCSITerminateIO:
				ioPtr->ioEvent |= (kmTerminated | kmMsgSent);
				// Remove this IO from the Disconnected array since we aborted cmd
				SIMg->discIOs [targetID] [ioPtr->scsiDevice.LUN] = 0;
				SIMg->LUNstate[targetID] [ioPtr->scsiDevice.LUN] &= ~km_LUNdisconnected;
				break;

			case SCSIAbortCommand:
				ioPtr->ioEvent |= (kmAborted | kmMsgSent);	
				// Remove this IO from the Disconnected array since we aborted cmd
				SIMg->discIOs [targetID] [ioPtr->scsiDevice.LUN] = 0;
				SIMg->LUNstate[targetID] [ioPtr->scsiDevice.LUN] &= ~km_LUNdisconnected;
				break;

			case SCSIResetDevice:
				ioPtr->ioEvent |= (kmBDRSent | kmMsgSent);	
				for( LUN = 0; LUN < 8; LUN+=1 ) {
					SIMg->discIOs [targetID][LUN] = 0;
					SIMg->LUNstate[targetID][LUN] &= ~km_LUNdisconnected;
				}
				break;
			}
		}
		if (SIMg->halPB.phase == kBusFreePhase) {
			*finalStatus = result;
			*completedIO = ioPtr;
			return (true);
		}
		else {
			if (SIMg->state == kSendingEarlyKillMsg)
				EarlySwitchPhase( ioPtr, SIMg);
			else
				SwitchPhase( ioPtr, SIMg);
		}
		break;


//==== Sending Initiator Detected Error Msg ====

	case kSendingDetectedErrorMsg:		

		if (!result)
		{
			IfDebugStr("\pkSendingDetectedErrorMsg not supported");
		}
		break;
	

//==== Sending Command ====

	case kSendingCommand:		

		ioPtr->ioStat = kSentCommand;
		SwitchPhase( ioPtr, SIMg);
		break;

	
//==== Sending Message ====

	case kSendingMsg:		

		SwitchPhase( ioPtr, SIMg);
		break;

	
//==== Rejecting Early Message In ====

	case kRejectingEarlyMsg:		
	
		if (SIMg->halPB.phase == kMessageOutPhase) 
		{
			SIMg->state = kEarlySwitchingPhase;
			SIMg->halPB.msg[0] = kMsgRejectMsg;
			SIMg->halPB.msgOutLen = 1;
			CallHALaction( kSendMsgOut, &SIMg->halPB, SIMg);
		}
		else
			EarlySwitchPhase( ioPtr, SIMg);
		
		break;


//==== Accepting Early SDTR ====

	case kAcceptingEarlySDTR:		
	case kAcceptingSDTR:
	
		if (result)
		{
			SIMg->syncRAoffset[targetID] = 0; 	// Something went wrong - target is asynchronous
		}
		EarlySwitchPhase( ioPtr, SIMg);
		
		break;


//==== Rejecting a message ====

	case kReconRejectingMsg:	
	case kRejectingDataMsg:	
	
		switch( SIMg->halPB.phase ) {
		
		case kMessageInPhaseNACK:	// in case of multiple message-in bytes
			CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
			break;
		case kMessageOutPhase:
			SIMg->state = kSendingMsg;
			SIMg->halPB.msg[0] = kMsgRejectMsg;
			SIMg->halPB.msgOutLen = 1;
			CallHALaction( kSendMsgOut, &SIMg->halPB, SIMg);
			break;
		default:
			IfDebugStr("\pBogus phase while rejecting message!");
			SwitchPhase( ioPtr, SIMg);
			break;
		}
		break;
		

//==== Switching Phase ====

	case kSwitchingPhase:		
	
		SwitchPhase( ioPtr, SIMg);
		break;


//====  Doing Data ====

	case kDoingData:		
	
		if (!result) {
			SwitchPhase( ioPtr, SIMg);
		}
		else if (result == scsiWrongDirection) {
			ioPtr->scsiDataResidual = -ioPtr->scsiDataResidual;	
			ioPtr->SIMprivFlags |= kmDataDone;			// to get SwitchPhase to bitbucket
			ioPtr->firstError = scsiWrongDirection;	
			SwitchPhase( ioPtr, SIMg);
		}
		else if (result == scsiUnexpectedBusFree) {
			SIMg->state = kWentBusFree;
		}
		break;

	
//==== Early Switching Phase ====

	case kEarlySwitchingPhase:		
	
		EarlySwitchPhase( ioPtr, SIMg);
		break;

	
//==== Completing ====

	case kGettingStatus:		
	
		if (result == noErr)	// this means we got a status, msg and then bus free
		{
			*finalStatus = noErr;
			*completedIO = ioPtr;
			IfRecordEvent( (long)ioPtr, (long)'GtSt');
			return (true);
		}
		else
		{
			IfDebugStr("\pError while kGettingStatus");
			*finalStatus = result;
			*completedIO = ioPtr;
			IfRecordError( result);
			return (true);
		}
		break;


//==== Disconnecting Before Sending Command ====

	case kDisconnectingB4Command:		

		if (SIMg->halPB.phase == kBusFreePhase) {
			*finalStatus = 0;
			*completedIO = 0;
			return (true);
		}
		else {		// huh? we got a disconnect msg, I expected to disconnect!
			EarlySwitchPhase( ioPtr, SIMg);		// only diff between this and next
		}
		break;


//==== Disconnecting ====

	case kDisconnecting:		

		if (SIMg->halPB.phase == kBusFreePhase) {
			*finalStatus = 0;
			*completedIO = 0;
			return (true);
		}
		else {		// huh? we got a disconnect msg, I expected to disconnect!
			SwitchPhase( ioPtr, SIMg);
		}
		break;


//==== Went Bus Free Unexpectedly ====

// Error condition
//	This is used to return from an unexpected bus free

	case kWentBusFree:		
		*finalStatus = scsiUnexpectedBusFree;
		// fall thru

//==== Bus Free From WastePhase ====

	case kWastedToBusFree:		
		*completedIO = ioPtr;
		return (true);
		break;


//==== FreeMachine ====

	case kFreeMachine:		
		*finalStatus = noErr;
		*completedIO = 0;	// no IOpb was being worked on, none to complete		
		return (true);		// free the machine
		break;


//==== Returning from failed Select ====

// Error condition
//	Used by HandleInitWErr to return from an unexpected bus free

	case kFailingSelect:		
		*finalStatus = scsiSelectTimeout;
		*completedIO = ioPtr;
		return (true);
		break;


//==== AwaitingOldCall ====

	case kAwaitingOldCall:		
			
		SIMg->state = kPerformingOldCall;
		// 
		switch (ioPtr->scsiSelector)
		{			
		case kSCSICmd:
			if (ioPtr->scsiCurrentPhase != kCommandPhase) {
				result = scPhaseErr;
				break;
			}
			halAct = kCommand;
			break;
			
		case kSCSIComplete:
			halAct = kComplete;
			ioPtr->scTimer = ioPtr->scsiTimeout;	/* Start timer <LW9> */
			break;
			
		case kSCSIRead:
		case kSCSIRBlind:
			halAct = kDataIn;
			break;
			
		case kSCSIWrite:
		case kSCSIWBlind:
			halAct = kDataOut;
			break;
			
		case kSCSIMsgIn:
			if (ioPtr->scsiCurrentPhase != kMessageInPhase) {
				result = scPhaseErr;
				break;
			}
			// we autoMsgIn'd the message already so we just move it
			SIMg->halPB.msgInLen -= 1;
			ioPtr->scsiSCSImessage = SIMg->halPB.msg[0];
			// then we accept it, going to the next phase
			halAct = kAcceptMsg;
			break;
			
		case kSCSIMsgOut:			// need to get buffer set up in HALactionPB
			if (ioPtr->scsiCurrentPhase != kMessageOutPhase) {
				result = scPhaseErr;
				break;
			}
			SIMg->halPB.msg[0] = ioPtr->scsiSCSImessage;
			SIMg->halPB.msgOutLen = 1;
			halAct = kSendMsgOut;
			break;
		
		// These selectors should never get down to the SIM - the XPT handles them
		case kSCSIStat:		// data generated by XPT
		case kSCSIReset:	// sent as ResetBus request(s)
		case kSCSIGet:		// ignored
		case kSCSISelect:	// sent as Initiate
		case kSCSISelAtn:	// sent as Initiate
		default:
			IfDebugStr("\pUnknown old call selector in kAwaitingOldCall state");
			SysError( dsIOCoreErr);
			break;
		}
		
		CallHALaction( halAct, &SIMg->halPB, SIMg);

		break;


//==== PerformingOldCall ====

	case kPerformingOldCall:		
	
		if (SIMg->halPB.phase == kMessageInPhaseNACK) 
			ioPtr->scsiCurrentPhase = kMessageInPhase;	// convert (we already got the msg)
		else
			ioPtr->scsiCurrentPhase = SIMg->halPB.phase;
			
		SIMg->state = kAwaitingOldCall;
		*finalStatus = result;
		ioPtr->scsiOldCallResult = *finalStatus;
		
		if (SIMg->halPB.phase == kBusFreePhase)
		{
			*completedIO = ioPtr;
			return (true);	// return out of machine and DO free it
		}
		return (false);	// return out of machine but DON'T free it
		break;


//==== Getting SCSIMsgIn message ====

	case kGettingSCSIMsgIn:		

		SIMg->state = kPerformingOldCall;
		CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
		break;
		

//==== BitBucketing 1 phase ====

	case kWastingPhase:		

		WastePhase( ioPtr, SIMg);
		break;

		
//==== ? ====

	default:
		IfDebugStr("\pUnknown state");
		SIMg->state = SIMg->state;
		
	} //============ end of switch on SIMg->state =================

	} while (true);
}


/*********************************************************************************
	Reconnect 	-	
*********************************************************************************/
/*
	This is kind of tricky.  This routine can be called at various stages in the
	reconnect process to determine what to do next.  This can be thought of as 
	another state but is not a part of TheMachine to avoid code duplication.
	
	There are two possible ways to end up here - either by a Reconnect interrupt 
	causing the HAL to send a ReconnectISR call to the SSM or by the SSM receiving
	a Reconnect event in response to a HALinitiate or Select call.
	
	In the first case, the HAL will call the ReconnectISR entry point in the SSM
	which sets a flag and tries to start up the Machine.
	
	In the second case, the SSM will be kIdle and be working on a kNewIO event, 
	forming a new HALactionPB (in the SIM's globals) and issuing an Initiate request
	to the HAL.  If a reconnect occurs after the StartMachine() call is made by 
	SIMCore and before the arbitration of the bus has occurred, then the HAL ISR's
	call to ReconnectISR() will see that the Machine is busy, and return to the HAL  
	without starting up the Machine (it's already running with the Initiate).  The
	HAL will be in the middle of or shortly thereafter receiving the HALinitiate call.
	The HAL will respond to that call by placing the recon vals in the HALactionPB
	and calling Machine() which will call Reconnect() to complete the reconnection.
*/
	
void
Reconnect( SIMglobals * SIMg)
{	
	SIMg->r_selectWaiting = false;

	// for c96
	if (SIMg->halPB.phase == kMessageInPhaseNACK)	// got Identify, need a MsgAccept
	{
		SIMg->reconTargetID	=	SIMg->halPB.selectorID;
		SIMg->reconLUN		=	IdentifyToLUN( SIMg->halPB.msg[0]);
		
		
		// Get the IO that was talking to this Target/LUN
	
		SIMg->halPB.ioPtr = SIMg->discIOs[SIMg->reconTargetID][SIMg->reconLUN];
		
		// If unknown, reject, if known accept and complete the reconnection
		
		if ( SIMg->halPB.ioPtr == 0)
		{
			// this is apparently an unknown IO, we'll reject the Identify		
			// should do a message reject message (i.e. setAtn, send MsgRej) (per SCSI-2?)

			// !!! We need to fill in the ioPtr field in the HalActionPB so that if
			// we need to do anything other than reject the message we won't explode!

			SIMg->state = kReconRejectingMsg;
			CallHALAssertATN( SIMg->HALinfo.HALstaticPtr);
			CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
		}
		else	// we have an IO to reconnect to
		{
			ReconnectIO( SIMg->reconTargetID, SIMg->reconLUN);
			
			CallHALSyncConfig(	SIMg->syncRAoffset[SIMg->halPB.ioPtr->scsiDevice.targetID],
								SIMg->syncPeriod  [SIMg->halPB.ioPtr->scsiDevice.targetID], SIMg->HALinfo.HALstaticPtr );

			SIMg->state = kReconAcceptingMsg;
			SIMg->halPB.ioPtr->hdshkRemainder = 0;				// Handshake gets re-started on a reconnect...
			CallHALaction( kSetParity, &SIMg->halPB, SIMg);
			CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
		}
	}
	
	else if (SIMg->halPB.phase == kMessageInPhase)				// need to get Identify
	{	
		IfDebugStr("\pMessageInPhase after reconnect");
		SysError( dsIOCoreErr);
	}
	
	else 	// not message phase at all
	{
		IfDebugStr("\pNot message phase after reconnect");
		SysError( dsIOCoreErr);
	}
				
	return;
}



/*********************************************************************************
	EarlySwitchPhase 	-	we've sent the Identify but not yet the Command
*********************************************************************************/

void
EarlySwitchPhase( SIM_IO * ioPtr, SIMglobals * SIMg)
{
	Boolean		assertATN;

	IfRecordEvent( (long)(SIMg->halPB.phase), (long)'ESwP');

	switch (SIMg->halPB.phase) {
	
	case kDataInPhase:
	case kDataOutPhase:
	
		SIMg->state = kEarlySwitchingPhase;
		CallHALaction( kBitBucket, &SIMg->halPB, SIMg);
		break;
				
	case kMessageInPhaseNACK:
		
		assertATN = false;
		
		switch ( SIMg->halPB.msg[0] )
		{
		case kDisconnectMsg:
			ioPtr->ioStat = kDisconnectedB4Command;
			DisconnectIO(	ioPtr->scsiDevice.targetID, 
							ioPtr->scsiDevice.LUN, 		ioPtr);
			SIMg->state = kDisconnectingB4Command;
			CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
			break;
			
		case kMsgRejectMsg:	// Apparently the target didn't like our identify message
			HandleRejectedIdentify( ioPtr, SIMg);
			break;
			
		case kExtendedMsg:
#if 0
			if (SIMg->halPB.msgInLen >= 4)
			{
				if (SIMg->halPB.msg[2] == 0x01)		// SDTR message
				{
					if ((SIMg->halPB.msgInLen == 6) && (SIMg->halPB.msg[2] == 0x03)) 
					{
						SIMg->halPB.msg[4] = MAX( 	SIMg->HALinfo.minPeriodFactor,
														SIMg->halPB.msg[4]		);

						SIMg->halPB.msg[5] = MIN(	SIMg->HALinfo.syncRAoffset,
														SIMg->halPB.msg[5]		);

						SIMg->syncPeriod  [ioPtr->scsiDevice.targetID] = SIMg->halPB.msg[4];	// transfer period
						SIMg->syncRAoffset[ioPtr->scsiDevice.targetID] = SIMg->halPB.msg[5]; 	// REQ/ACK offset
	
						CallHALSyncConfig(	SIMg->syncRAoffset[ioPtr->scsiDevice.targetID],
											SIMg->syncPeriod  [ioPtr->scsiDevice.targetID], SIMg->HALinfo.HALstaticPtr );
			
						CallHALAssertATN( SIMg->HALinfo.HALstaticPtr);	
						CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
						if (SIMg->halPB.phase == kMessageOutPhase) 
						{
							SIMg->state = kAcceptingEarlySDTR;
							SIMg->halPB.msgOutLen = 6;
							CallHALaction( kSendMsgOut, &SIMg->halPB, SIMg);
						}
						else 	// no msg out phase - target async
						{
							SIMg->state = kEarlySwitchingPhase;
							SIMg->syncRAoffset[ioPtr->scsiDevice.targetID] = 0; 	// asynchronous
						}
						break;
					}
					else 		// something wrong with format of SDTR
					{
						SIMg->syncRAoffset[ioPtr->scsiDevice.targetID] = 0; 	// asynchronous
					}
				}
			}
#endif
			// extended message that we don't care about
			SIMg->state = kRejectingEarlyMsg;
			CallHALAssertATN( SIMg->HALinfo.HALstaticPtr);	
			CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
			break;

		default:
			CallHALAssertATN( SIMg->HALinfo.HALstaticPtr);	
			CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
		}
		break;
		
	case kStatusPhase:
	
		SIMg->state = kGettingStatus;
		CallHALaction( kStatus, &SIMg->halPB, SIMg);
		break;
		
	case kMessageOutPhase:					// we should only be here because we asserted ATN
	
		SIMg->state = kSendingEarlyKillMsg;
		
		if( !ioPtr->pendingMsgPB ) {
			if( ioPtr->ioEvent & kmBadParity )
				SIMg->halPB.msg[0] = kInitiatorDetectedErrorMsg;
			else
				SIMg->halPB.msg[0] = kNoOperationMsg;	// NOP since we don't know what is going on!
		}
		else {
			switch( ((SCSI_PB *)(ioPtr->pendingMsgPB))->scsiFunctionCode) {
				
			case SCSITerminateIO:
				SIMg->halPB.msg[0] = kTerminateIOProcessMsg;
				ioPtr->ioEvent |= (kmTerminated | kmMsgSent);
				break;
			case SCSIAbortCommand:
				SIMg->halPB.msg[0] = kAbortMsg;
				ioPtr->ioEvent |= (kmAborted | kmMsgSent);	
				break;
			case SCSIResetDevice:
				SIMg->halPB.msg[0] = kBusDeviceResetMsg;
				ioPtr->ioEvent |= (kmBDRSent | kmMsgSent);	
				break;
			}
		}
		SIMg->halPB.msgOutLen = 1;
				
		CallHALaction( kSendMsgOut, &SIMg->halPB, SIMg);
		break;
		
	case kCommandPhase:
	
		CallHALaction( kCommand, &SIMg->halPB, SIMg);
		SIMg->state = kSendingCommand;
		break;
		
	case kBusFreePhase:
		
		SIMg->state = kWentBusFree;
		break;
		
	default:
	
		IfDebugStr("\pUnknown phase in EarlySwitchPhase");
		SysError( dsIOCoreErr);
	}
	
	return;


}


/*********************************************************************************
	WastePhase 	-	we're really confused, do what we need to to clear the bus
*********************************************************************************/

void
WastePhase( SIM_IO * ioPtr, SIMglobals * SIMg)
{
	IfRecordEvent( (long)'DUMP', (long)'Err!');
	SIMg->state = kWastingPhase;

	switch (SIMg->halPB.phase) {
	
	case kDataInPhase:
	case kDataOutPhase:
	
		CallHALaction( kBitBucket, &SIMg->halPB, SIMg);
		break;
				
	case kMessageInPhaseNACK:
		
		CallHALAssertATN( SIMg->HALinfo.HALstaticPtr);	
		CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
		break;
		
	case kStatusPhase:
	
		SIMg->state = kGettingStatus;
		CallHALaction( kStatus, &SIMg->halPB, SIMg);
		break;
		
	case kMessageOutPhase:					// we should only be here because we asserted ATN
	
		SIMg->state = kSendingEarlyKillMsg;
		
		if( !ioPtr->pendingMsgPB ) {
			if( ioPtr->ioEvent & kmBadParity )
				SIMg->halPB.msg[0] = kInitiatorDetectedErrorMsg;
			else
				SIMg->halPB.msg[0] = kNoOperationMsg;	// NOP since we don't know what is going on!
		}
		else {
			switch( ((SCSI_PB *)(ioPtr->pendingMsgPB))->scsiFunctionCode) {
				
			case SCSITerminateIO:
				SIMg->halPB.msg[0] = kTerminateIOProcessMsg;
				ioPtr->ioEvent |= (kmTerminated | kmMsgSent);
				break;
			case SCSIAbortCommand:
				SIMg->halPB.msg[0] = kAbortMsg;
				ioPtr->ioEvent |= (kmAborted | kmMsgSent);	
				break;
			case SCSIResetDevice:
				SIMg->halPB.msg[0] = kBusDeviceResetMsg;
				ioPtr->ioEvent |= (kmBDRSent | kmMsgSent);	
				break;
			}
		}
		SIMg->halPB.msgOutLen = 1;
				
		CallHALaction( kSendMsgOut, &SIMg->halPB, SIMg);
		break;
		
	case kCommandPhase:
	
		CallHALaction( kCommand, &SIMg->halPB, SIMg);
		SIMg->state = kSendingCommand;
		break;
		
	case kBusFreePhase:
		
		SIMg->state = kWastedToBusFree;
		break;
		
	default:
	
		IfDebugStr("\pUnknown phase in WastePhase");
		SysError( dsIOCoreErr);
	}
	
	return;


}


/*********************************************************************************
	HandleInitWErr 	-	
*********************************************************************************/

void
HandleInitWErr( SIM_IO * ioPtr, SIMglobals * SIMg)
{
	OSErr	result;

	result = SIMg->halPB.result;
	
	IfRecordEvent( (long)( (SIMg->halPB.sendCDB<<24) + (SIMg->halPB.phase<<16) + (SIMg->halPB.msgInLen<<8) + SIMg->halPB.msgOutLen),
				(long)'IErr');
				
	IfRecordEvent( (long)( (result<<16) + SIMg->halPB.action),
				(long)'Err!');
				
	if (result == kHALreselected)
	{
		ioPtr->ioStat = kPBidle;			// go back to Idle for this one
		Reconnect( SIMg);
	}
	else if (result == kHALpartialMsgOut) 	
	{
		if (SIMg->halPB.msgOutLen == 0) {
			HandleNoIdentifyMsg( ioPtr, SIMg);
		}
		else if (SIMg->halPB.msgOutLen == 1) {
			if ((SIMg->halPB.phase == kMessageInPhaseNACK) && (SIMg->halPB.msg[0] == kMsgRejectMsg)) {
				HandleRejectedIdentify( ioPtr, SIMg);
			}
			else
				EarlySwitchPhase( ioPtr, SIMg);
		}
		else 	// 2 or more msg bytes went out
		{
			if (SIMg->state == kInitiatingSDTR) {
				SIMg->syncRAoffset[ioPtr->scsiDevice.targetID] = 0;
			}	
			else {	// kInitiatingAsyncMsg
				if ((SIMg->halPB.phase == kMessageInPhaseNACK) && (SIMg->halPB.msg[0] == kMsgRejectMsg)) {
					ioPtr->firstError = scsiKillMsgRejected;
				}
			}
			EarlySwitchPhase( ioPtr, SIMg);
		}
	}
	else if (result == kHALnoCommand) 
	{
		EarlySwitchPhase( ioPtr, SIMg);
	}
	else if (result == kHALpartialCommand) 
	{
		ioPtr->ioStat = kSentCommand;			// pretend like we got no error	
		SwitchPhase( ioPtr, SIMg);	
	}
	else if (result == kHALselectedAsTarget)	// we got selected
	{
		SIMg->state			= kHandlingSelected;
		SIMg->pushedState	= kIdle;				// retry this IO initiation
	}
	else if (result == kHALselectedAsTargetFld)
	{
		SIMg->state			= kIdle;				// retry this IO initiation
	}
	else if (result == kHALselectFld)
	{
		SIMg->state = kFailingSelect;
	}
	else if (result == scsiUnexpectedBusFree)
	{
		SIMg->state = kWentBusFree;
	}
	else
	{
		IfDebugStr("\pUnknown result in HandleInitWErr");
		SysError( dsIOCoreErr);
	}
}



/*********************************************************************************
	HandleRejectedIdentify 	-	
*********************************************************************************/

void
HandleRejectedIdentify( SIM_IO * ioPtr, SIMglobals * SIMg)
{
#pragma unused (ioPtr)
	CallHALAssertATN( SIMg->HALinfo.HALstaticPtr);	
	CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
	ioPtr->firstError = scsiIdentifyMessageRejected;	
	SIMg->state = kAcceptingRejectedIdentify;
}


/*********************************************************************************
	HandleEarlyMsgIn 	-	
*********************************************************************************/

void
HandleEarlyMsgIn( SIM_IO * ioPtr, SIMglobals * SIMg)
{
	EarlySwitchPhase( ioPtr, SIMg);
}


/*********************************************************************************
	HandleNoIdentifyMsg 	-	
*********************************************************************************/

void
HandleNoIdentifyMsg( SIM_IO * ioPtr, SIMglobals * SIMg)
{
	if (SIMg->halPB.phase == kCommandPhase)
		EarlySwitchPhase( ioPtr, SIMg);
	else // if (SIMg->halPB.phase == kMessageInPhaseNACK)
		EarlySwitchPhase( ioPtr, SIMg);
}


/*********************************************************************************
	SwitchPhase 	-	
*********************************************************************************/

void
SwitchPhase( SIM_IO * ioPtr, SIMglobals * SIMg)
{	
	Boolean		assertATN;

	IfRecordEvent( (long)(SIMg->halPB.phase), (long)'SwPz');

	switch (SIMg->halPB.phase) {
	
	case kDataInPhase:
	
		if ( ioPtr->scsiDataResidual <= 0 || ( ioPtr->SIMprivFlags & kmDataDone) ) {
			ioPtr->SIMprivFlags |= kmBitBucketed;
			if ( ioPtr->scsiIOFlags & scsiNoBucketIn) {
				ioPtr->scsiResultFlags |= scsiBusNotFree;
				CompleteIO( scsiDataRunError, ioPtr, SIMg);					
			}
			else {
				SIMg->state = kSwitchingPhase;
				CallHALaction( kBitBucket, &SIMg->halPB, SIMg);
			}
			break;
		}
		
		SIMg->state = kDoingData;
		CallHALaction( kDataIn, &SIMg->halPB, SIMg);
		break;
		
	case kDataOutPhase:
	
		if ( ioPtr->scsiDataResidual <= 0 || ( ioPtr->SIMprivFlags & kmDataDone) ) {
			ioPtr->SIMprivFlags |= kmBitBucketed;
			if ( ioPtr->scsiIOFlags & scsiNoBucketOut) {
				ioPtr->scsiResultFlags |= scsiBusNotFree;
				CompleteIO( scsiDataRunError, ioPtr, SIMg);					
			}
			else {
				SIMg->state = kSwitchingPhase;
				CallHALaction( kBitBucket, &SIMg->halPB, SIMg);
			}
			break;
		}
		
		SIMg->state = kDoingData;
		CallHALaction( kDataOut, &SIMg->halPB, SIMg);
		break;
		
		
	case kMessageInPhaseNACK:
		
		assertATN = false;
		
		switch ( SIMg->halPB.msg[0] )
		{
		case kSaveDataPointerMsg:		// TAKEN CARE OF IN HAL NOW
			CallHALaction( kSaveDataPointer, &SIMg->halPB, SIMg);	// is this perSCSI2? (or after accept)
			SIMg->state = kSwitchingPhase;
			break;
			
		case kRestorePointersMsg:		// TAKEN CARE OF IN HAL NOW
			CallHALaction( kRestorePointers, &SIMg->halPB, SIMg);	// is this perSCSI2? (or after accept)
			SIMg->state = kSwitchingPhase;
			break;
			
		case kDisconnectMsg:
			ioPtr->ioStat = kDisconnected;
			
			// if SavePtrOnDisc flag is set, we should do that now
			if (ioPtr->scsiIOFlags & scsiSavePtrOnDisconnect)
				CallHALaction( kSaveDataPointer, &SIMg->halPB, SIMg);

			SIMg->state = kDisconnecting;
			DisconnectIO(	ioPtr->scsiDevice.targetID, 
							ioPtr->scsiDevice.LUN, 		ioPtr);
			break;
			
		case kMsgRejectMsg:	// Apparently the target didn't like our message
			((SCSIHdr *)((SIM_IO *)ioPtr->pendingMsgPB))->scsiResult = scsiMessageRejectReceived;
			IfRecordEvent( (long)ioPtr->pendingMsgPB, (long)'RejC');
			CallCompRoutine( (SCSI_IO *)ioPtr->pendingMsgPB);
			ioPtr->ioEvent |= kmMsgRejected;
			break;
			
		case kCmdCompleteMsg:
			break;

		case kExtendedMsg:
#if 0
			if (SIMg->halPB.msgInLen >= 4)
			{
				if (SIMg->halPB.msg[2] == 0x01)		// SDTR message
				{
					if ((SIMg->halPB.msgInLen == 6) && (SIMg->halPB.msg[2] == 0x03)) 
					{
						SIMg->halPB.msg[4] = MAX( 	SIMg->HALinfo.minPeriodFactor,
														SIMg->halPB.msg[4]		);

						SIMg->halPB.msg[5] = MIN(	SIMg->HALinfo.syncRAoffset,
														SIMg->halPB.msg[5]		);

						SIMg->syncPeriod  [ioPtr->scsiDevice.targetID] = SIMg->halPB.msg[4];	// transfer period
						SIMg->syncRAoffset[ioPtr->scsiDevice.targetID] = SIMg->halPB.msg[5]; 	// REQ/ACK offset
	
						CallHALSyncConfig(	SIMg->syncRAoffset[ioPtr->scsiDevice.targetID],
											SIMg->syncPeriod  [ioPtr->scsiDevice.targetID], SIMg->HALinfo.HALstaticPtr );
			
						CallHALAssertATN( SIMg->HALinfo.HALstaticPtr);	
						CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
						if (SIMg->halPB.phase == kMessageOutPhase) 
						{
							SIMg->state = kAcceptingSDTR;
							SIMg->halPB.msgOutLen = 6;
							CallHALaction( kSendMsgOut, &SIMg->halPB, SIMg);
						}
						else 	// no msg out phase - target async
						{
							SIMg->state = kSwitchingPhase;
							SIMg->syncRAoffset[ioPtr->scsiDevice.targetID] = 0; 	// asynchronous
						}
						break;
					}
					else 		// something wrong with format of SDTR
					{
						SIMg->syncRAoffset[ioPtr->scsiDevice.targetID] = 0; 	// asynchronous
					}
				}
			}
#endif
			// extended message that we don't care about
			SIMg->state = kRejectingDataMsg;
			CallHALAssertATN( SIMg->HALinfo.HALstaticPtr);	
			CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
			break;

		default:
			SIMg->state = kRejectingDataMsg;
			assertATN = true;
		}
		
		if (!assertATN)
		{
			CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
		}
		else
		{
			CallHALAssertATN( SIMg->HALinfo.HALstaticPtr);	
			CallHALaction( kAcceptMsg, &SIMg->halPB, SIMg);
		}
		break;
		
	case kStatusPhase:
	
		SIMg->state = kGettingStatus;
		CallHALaction( kStatus, &SIMg->halPB, SIMg);
		break;
		
	case kMessageOutPhase:			// we should only be here because we (or c96) asserted ATN
	
		if( !ioPtr->pendingMsgPB ) {
			if( ioPtr->ioEvent & kmBadParity ) {		// did c96 assert ATN for parity error?
				SIMg->halPB.msg[0] = kInitiatorDetectedErrorMsg;
				SIMg->state = kSendingDetectedErrorMsg;
			}
			else
				SIMg->halPB.msg[0] = kNoOperationMsg;	// NOP since we don't know what is going on!
		}
		else {
			SIMg->state = kSendingKillMsg;
		
			switch( ((SCSI_PB *)(ioPtr->pendingMsgPB))->scsiFunctionCode) {	// <SM7>
				
			case SCSITerminateIO:
				SIMg->halPB.msg[0] = kTerminateIOProcessMsg;
				break;
			case SCSIAbortCommand:
				SIMg->halPB.msg[0] = kAbortMsg;
				break;
			case SCSIResetDevice:
				SIMg->halPB.msg[0] = kBusDeviceResetMsg;
				break;
			}															//	<SM7>
		}
		SIMg->halPB.msgOutLen = 1;
				
		CallHALaction( kSendMsgOut, &SIMg->halPB, SIMg);
		break;
		
	case kCommandPhase:
	
		ioPtr->scsiResult = scsiSequenceFailed;
		SIMg->state = kWastingPhase;
		CallHALaction( kBitBucket, &SIMg->halPB, SIMg);
		break;
		
	case kBusFreePhase:
		
		/* Note that this section no longer calls FreeMachine and StartMachine!
		   BusFreePhase during a Switch Phase is an error or the result of an abort
		   type message only!  We shouldn't get here during a normal IO				<SM3>
		*/
		SIMg->state = kWentBusFree;
		break;
		
	default:
	
		IfDebugStr("\pUnknown phase in SwitchPhase");
		SysError( dsIOCoreErr);
	}
	
	return;
}


