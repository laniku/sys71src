/*
	File:		SIMQ.c

	Contains:	routines that implement the Queueing mechainism of the SIM layer
				for the Apple SIM Core 

	Entry points:

	Written by:	Paul Wolf

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SM19>	12/19/93	DCB		Clear hdshkRemainder in the PB when we enqueue it.  This is to
									help solve the handshake across scatter gather boundries
									problem.
	  <SM18>	11/22/93	pdw		Rolling in from <MCxx>.
	   <MC4>	 11/8/93	pdw		Cleared firstError upon entry.  Changed comments.
	  <SM17>	10/14/93	pdw		<MC> roll-in.
	   <MC3>	10/12/93	pdw		Added support for Synchronous data transfers, rewrote State
									Machine, message handling etc.
	   <MC2>	 9/13/93	pdw		Roll-in from SuperMario.
	  <SM16>	 9/13/93	pdw		Changed the risky slash pattern.  Fixed ResetDevice bug by
									reverting to previous criteria in SwitchQ.  It will now only
									switch those IOs that are not idle.
	  <SM15>	 9/12/93	pdw		Changed EnQIO to reflect name change of EnqueueHead to
									CEnqueueHead (to avoid conflict with new ROM routine).
	  <SM14>	 7/17/93	pdw		Lots of little things.  Also changed ResetQueues to treat
									idle/non-idle pbs a little differently.
	  <SM13>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
									stack switching mechanism.  Adding support for Cold Fusion.
									Rearranging HW/SW Init code. Some code optimizations.
	  <SM12>	 5/29/93	PW		Adding include of SCSIDebug.h
	  <SM11>	 5/25/93	DCB		Rollin from Ludwig. (The next item below)
	   <LW9>	 5/21/93	PW		Adding SIMg parameter to ValidatePB so that it can check hostID.
	  <SM10>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	   <LW7>	  3/8/93	PW		Eliminated an ==0 to get rid of 3 instructions.
	   <LW6>	  3/3/93	PW		Added line to change defaultDisc when EnQing with an item
									already in Q.
	   <LW5>	  3/1/93	DCB		Added an ID parameter to the ResetQ function so that it could be
									used for ResetDevice as well as ResetBus. Also moved the timer
									setup into EnQIO.
	   <LW4>	 2/18/93	DCB		Changed Reset Queue's behavior to match the documentation. Only
									those IOs actually started are dequeued after a reset.
	   <LW3>	 1/27/93	PW		Removed silly DItoTarget/LUN stuff.
	   <LW2>	12/17/92	DCB		Added a parameter block clear in EnQIO.
	   <SM7>	 12/5/92	PW		Added SCSI.h include.
	   <SM6>	11/20/92	DCB		Support for async Abort, Terminate and Reset Device
	   <SM5>	10/30/92	DCB		Added initial value set for SIMprivFlags
	   <SM4>	 10/8/92	PW		Lots of name changes.
	   <SM3>	 9/11/92	DCB		Added queue support for the (singular) ResetDevice Parameter
									block.
	   <SM2>	 8/31/92	DCB		Added FindIO PB function for Terminate and Abort PB. Also
									changed DeQIO to use the ioQueue field that I added to the
									SCSI_IO parameter block. Finally - added SwitchQ to move a
									single ioPB from one Q to another.

*/


#include <Types.h>
#include <Memory.h>
#include <Errors.h>
#include <SCSIStandard.h>
#include <SCSI.h>
#include <OSUtils.h>

#include "ACAM.h"
#include "CUtils.h"
#include "QueueUtils.h"
#include "XPT.h"
#include "XPTpriv.h"

#include "SIMCore.h"
#include "SIMCorePriv.h"
#include "SIMQ.h"

#include "SCSIDebug.h"
#include "Recorder.h"


/********* External Function Prototypes **********/


/*********************************************************************************
	EnQIO 	-	
*********************************************************************************/

void
EnQIO( SIM_IO *ioPtr, SIMglobals * SIMg)
{	
	ioPtr->ioStat = kPBidle;
	ioPtr->scsiOldCallResult = scsiRequestInProgress;
	ioPtr->ioEvent = 0;			/* No messages yet <LW5> */
	ioPtr->firstError = 0;
	ioPtr->savedResult = 0;
	ioPtr->SIMg = (Ptr)SIMg;	/* Save this for the autosense/device reset completion routine */
	ioPtr->pendingMsgPB = nil;	/* <SM6> */
	ioPtr->SIMprivFlags = 0;	/* <SM5> */
	ioPtr->scsiResultFlags = 0;	/* <SM6> */	
	ioPtr->ioQueue = (Ptr)&SIMg->qHdr;		// Everything gets added to the IOq first <SM2>
	ioPtr->hdshkRemainder = 0;	/* <SM19> */
	
	/* Convert format to seconds and start timer <LW5> */
	if( !ioPtr->scsiTimeout )
		ioPtr->scTimer = 0;
	else if( ioPtr->scsiTimeout < 0 )	/* µSeconds -> 1 second */
		ioPtr->scTimer = 1;			/* !!! This actually could be longer than a second! */
	else
		ioPtr->scTimer = (ioPtr->scsiTimeout >> 10) + 1;	/* Close enough to seconds...*/

	ioPtr->scsiSCSIstatus = 0;	// <LW2>
	
	if (SIMg->qHdr.qHead)
		SIMg->defaultDisc = true;
		
	if ( ioPtr->scsiFlags & scsiSIMQHead)
	{
		IfRecordEvent( (long)ioPtr, (long)'EnQH');
		CEnqueueHead((QElemPtr)ioPtr, &SIMg->qHdr);
	}
	else
	{
		IfRecordEvent( (long)ioPtr, (long)'EnQT');
		Enqueue((QElemPtr)ioPtr, &SIMg->qHdr);
	}
	
}

/*********************************************************************************
	DeQIO 	-	
*********************************************************************************/

void
DeQIO( SIM_IO *ioPtr, SIMglobals * SIMg)		// <SM2>
{
	QHdrPtr IOQHdr;
	
	IOQHdr = (QHdrPtr)ioPtr->ioQueue;			// <SM2>
	
	IfRecordEvent( (long)ioPtr, (long)'DeQ ');
	
	if( !IOQHdr->qHead )
		return;	/* Sorry - no queue */
	
// In case of CompleteIO before getting sense (i.e. from ResetX, AbortCmd or TermIO)
	if( ioPtr->ioStat == kNeedsSense )	
		SIMg->senseWaiting -=1;
	
	if (Dequeue((QElemPtr)ioPtr, IOQHdr)) {
		IfDebugStr("\pDequeue in DeQIO failed");
		SysError( dsIOCoreErr);
	}
}


/*********************************************************************************
	GetNextReadyIO 	-	scan Q for next available IO
*********************************************************************************/

SIM_IO *
GetNextReadyIO( SIMglobals * SIMg)
{
	SIM_IO *	qPtr;
	
	if( SIMg->SIMBusy )
		return(0);	/* Even if we reject a PB the XPT might attempt to restart the machine */
	
	// First look in the immediate queue
	
	qPtr = (SIM_IO *)SIMg->immedQHdr.qHead;
	
	while (qPtr != 0) {
		if (qPtr->pendingMsgPB != nil && !(qPtr->ioEvent & kmMsgSent))
			break;
		qPtr = (SIM_IO *)(qPtr->qLink);			
	}

	if( !qPtr || (qPtr->ioEvent & kmMsgSent) ) {	// <LW5> If we already sent a message...
	
		qPtr = (SIM_IO *)SIMg->qHdr.qHead;
		
		while (qPtr) {
			if (qPtr->ioStat == kPBidle)
			{
				if ( !FindUsedLUN( qPtr->scsiDevice.targetID, qPtr->scsiDevice.LUN)) 
					break;
			}
			qPtr = (SIM_IO *)(qPtr->qLink);	
		}
	}
	
	IfRecordEvent( (long)qPtr, (long)'GtIO');
	return (qPtr);
}


/*********************************************************************************
	ResetQueues -	Moves all non-idle IOs from ExecIO Q to the resetQ that
					match the target ID (an ID of 0xFF means all devices).
					This allows us to continue accepting new IOs while
					dispensing with all of those currently in the queue. The 
					reason that we don't discriminate on a LUN basis is because 
					both Reset Bus and Reset Device affect an entire device.
*********************************************************************************/

void
ResetQueues( SIMglobals * SIMg, uchar ID ) 	// <LW5> <Whole Routine...>
{
	ushort			oldSR;
	SIM_IO			* qPtr;
	
	oldSR = BlockInterrupts();	//-> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> ->
	
	IfRecordEvent( (long)0, (long)'RsQu');

	qPtr = (SIM_IO *)SIMg->qHdr.qHead;
	while( qPtr ) {
		if ( qPtr->ioStat !=kIdle &&
			(ID==0xFF || qPtr->scsiDevice.targetID == ID ) )
		{
			Dequeue((QElemPtr)qPtr,(QHdrPtr) &SIMg->qHdr);
			Enqueue((QElemPtr)qPtr,(QHdrPtr) &SIMg->resetHdr);
			qPtr->ioQueue = (Ptr)&SIMg->resetHdr; 	// remember that we moved this queue element <SM2>
		}
		qPtr = (SIM_IO *) qPtr->qLink;
	}
	UnblockInterrupts( oldSR); //<- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- 
}


/*********************************************************************************
	GetNextAutoSense 	-	scan Q for next IO which is waiting for autosense
*********************************************************************************/

SIM_IO *
GetNextAutoSense( SIMglobals * SIMg)
{
	SIM_IO *	qPtr;
	
	qPtr = (SIM_IO *)SIMg->qHdr.qHead;
	
	while (qPtr) {
		if (qPtr->ioStat == kNeedsSense)
			break;
		qPtr = (SIM_IO *)(qPtr->qLink);			
	}
	
	IfRecordEvent( (long)qPtr, (long)'GtAS');
	return (qPtr);
}


/*********************************************************************************
	FindIO 	-	scan Q for a particular IO
*********************************************************************************/

SIM_IO *	// <SM2>
FindIO( SIM_IO * ioPtr, SIMglobals * SIMg)
{
	SIM_IO *	qPtr;
	
	qPtr = (SIM_IO *)SIMg->qHdr.qHead;
	
	while (qPtr) {
		if ( qPtr == ioPtr ) 
			break;
		qPtr = (SIM_IO *)(qPtr->qLink);			
	}
	
	return (qPtr);
}

/*********************************************************************************
	SwitchQ 	-	Move an ioPB from one queue to another
*********************************************************************************/

void	// <SM2>
SwitchQ( SIM_IO * ioPB, QHdrPtr newQ)
{	
	if ( Dequeue((QElemPtr)ioPB, (QHdrPtr)ioPB->ioQueue) ) {
		IfDebugStr("\pDequeue failed in SwitchQ");
	}
	Enqueue( (QElemPtr)ioPB, newQ);
	ioPB->ioQueue = (Ptr) newQ;
	
	IfRecordEvent( (long)ioPB, (long)'SwQ ');

	return;
}


/*********************************************************************************
	FindIOFromID 	-	scan Q for the first IO associated with a SCSI device
*********************************************************************************/

SIM_IO *	// <SM2>
FindIOFromID( uchar TargetID, SIMglobals * SIMg)
{
	SIM_IO *	qPtr;
	
	qPtr = (SIM_IO *)SIMg->qHdr.qHead;
	
	while (qPtr) {
		if( (qPtr->scsiDevice).targetID == TargetID ) 
			break;
		qPtr = (SIM_IO *)(qPtr->qLink);			
	}
	IfRecordEvent( (long)qPtr, (long)'ioID');
	
	return (qPtr);
}

