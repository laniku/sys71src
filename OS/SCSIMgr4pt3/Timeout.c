/*
	File:		Timeout.c

	Contains:	routines that implement connection timeouts

	Entry points:

	Written by:	Clinton Bauder

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SM14>	10/14/93	pdw		<MC> roll-in.
	   <MC3>	10/12/93	pdw		Added support for Synchronous data transfers, rewrote State
									Machine, message handling etc.
	   <MC2>	 9/13/93	pdw		Roll in from SuperMario.
	  <SM13>	 9/13/93	pdw		Changed the risky slash pattern.
	  <SM12>	 7/17/93	pdw		Lots of little things.
	  <SM11>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
									stack switching mechanism.  Adding support for Cold Fusion.
									Rearranging HW/SW Init code. Some code optimizations.
	  <SM10>	 5/25/93	DCB		Rollin from Ludwig. (The next item below)
	   <SM9>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	   <SM8>	 3/20/93	PW		rolled in Ludwig changes.
	   <LW4>	  3/1/93	DCB		Got rid of connTimeouts and re-worked CAM timeouts so that they
									actually work. (Sorta took the best of the two) Now parameter
									blocks are only timed if they are either on the bus or the bus
									is free. This fixes the jerky mouse problem in the test tool.
	   <LW3>	 1/27/93	PW		Added #include <SCSIStandard.h>.
	   <LW2>	 1/12/93	DCB		Changed synchronous abort of PBs which timed out to be
									asynchronous.  This fixes a deadlock caused by earlier changes
									to the abort code.
	   <SM6>	 12/5/92	PW		Changed field names.  Added SCSI.h include.
	   <SM5>	11/20/92	PW		Added some Includes that were removed from headers.
	   <SM4>	 10/8/92	PW		Lots of trivial name changes.
	   <SM3>	 8/31/92	DCB		Added AbortCommand call to kill timed-out ios.
	   <SM2>	 8/20/92	DCB		Changed timeout value to the Time Manager convention of < 0 ==
									µS >0 == ms (From seconds)

*/

#include <Types.h>
#include <Packages.h>
#include <Memory.h>
#include <SCSIStandard.h>
#include <SCSI.h>

#include "ACAM.h"
#include "Recorder.h"
#include "SIMCore.h"
#include "SIMCorePriv.h"
#include "SIMQ.h"


/********* External Functions ************/

extern SIMTMTask* getTimerPB();
extern short	BlockInterrupts(void);
extern void		UnblockInterrupts( short oldSR);


/* Definition of Timeouts in ACAM	<LW4>
** 
** Since CAM is rather unclear on timeouts and what to do with them we have defined it
** as follows;  A parameter block has timed out if the total amount of time that it is
** on the bus OR was eligible to be on the bus (ie the bus was free) after initiation has
** exceeded the timeout value then the parameter block has timed out.  If this occurs an
** Abort Command message shall be sent to the device and its completion routine called.
*/


/*********************************************************************************
	StartTimer - This starts up the 1 second timer in the SIM
*********************************************************************************/

void 
StartTimer( SIMglobals* SIMg) 
{
	
	/* Assumes that SIMg is cleared to zero before use */	
	SIMg->mySIMTMTask.theTask.qLink = (QElemPtr) 'eada';	/* Magic VM "operate during page fault time" marker */
	SIMg->mySIMTMTask.theTask.tmAddr = (TimerProcPtr) SIMTimerProc;
	SIMg->mySIMTMTask.SIMg = (Ptr) SIMg;	/* Stuff globals into TMTask record for easy reference */
	/* How do I make this VM safe ? */
	
	InsXTime((QElemPtr)&SIMg->mySIMTMTask);
	PrimeTime((QElemPtr)&SIMg->mySIMTMTask,1000);	/* Once a second */
}

/*********************************************************************************
	SIMTimerProc - This is the actual time manger task itself.
*********************************************************************************/

#define MAX_SIMUL_TOUT 10

void 
SIMTimerProc( void) 
{
	SIMTMTask* theSIMTask;
	SIMglobals* SIMg;
	SIM_IO *	qPtr;
	SIM_IO *	tdOut[MAX_SIMUL_TOUT];
	int			i,index;
	short		oldSR;
	
	
	//IfRecordEvent( 0, (long)'SIMT');
	theSIMTask = (SIMTMTask *)getTimerPB();	/* Assembly language routine to return register a1 */
	
	/* Get the globals from the Time Manager Queue entry */
	SIMg = (SIMglobals *) theSIMTask->SIMg;
	index = 0;
	
	oldSR = BlockInterrupts();	//-> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> ->
	
// First check to see if a PB is currently on the bus.  If one is then its timer will 
//	be decremented and compared against the timeout value.  
//	!!!%%%_debugger! use a switch

	if(	SIMg->state != kIdle				&&
		SIMg->state != kInitiatingNormal	&&
		SIMg->state != kInitiatingSDTR		&&
		SIMg->state != kInitiatingAsyncMsg	&&
		SIMg->state != kInitiatingOldCall	&&
		SIMg->state != kGotR_selected		&&
		SIMg->state != kWentBusFree			&&
		SIMg->halPB.phase != kBusFreePhase) 
	{
		if( SIMg->halPB.ioPtr->scsiTimeout && 
				SIMg->halPB.ioPtr->ioQueue == &(SIMg->qHdr) &&
				((SIMg->halPB.ioPtr->scTimer)-- == 0 || SIMg->halPB.ioPtr->ioEvent & kmTimedOut) ) 
			tdOut[index++] = SIMg->halPB.ioPtr;		/* Remember that this timed out */		
	}
	else {
	
		// If the machine wasn't busy then walk the queue and look for parameter blocks that
		// are eligible to be on the bus and decrement their timers.

		for( qPtr = (SIM_IO *)SIMg->qHdr.qHead; qPtr ; qPtr = (SIM_IO *)qPtr->qLink ) {
			/* First check connection timeout for active paramter blocks */
			if( qPtr->ioStat != kPBidle ) {
				if( qPtr->scsiTimeout && 
						( (qPtr->scTimer)-- == 0 || qPtr->ioEvent & kmTimedOut) ) {		//<LW5>pdw
				if( index < MAX_SIMUL_TOUT )	/* if list full - wait til next interrupt */
					tdOut[index++] = qPtr;		/* Remember that this timed out */
				continue;						/* One kind of timeout per entry */
				}
			}
		}
	}
		
	/* Look through list for elements that timed out and Abort them.			<SM3> */
	for( i = 0; i < index; i+=1 ) {
		// The following is a bit of a hack.  We aren't keeping track of the completion
		// of the abort - so we can use the same AbortParameter block for multiple timeouts
		
		SIMg->abortPB.scsiFunctionCode = SCSIAbortCommand;
		SIMg->abortPB.scsiCompletion = 0;
		SIMg->abortPB.scsiDevice = tdOut[i]->scsiDevice;	// Not really used
		tdOut[i]->ioEvent |= kmTimedOut;		/* let the user know what happened 		<SM3> */
		tdOut[i]->pendingMsgPB = (Ptr) &SIMg->abortPB; /* Abort the Parameter block <LW2> */
		SwitchQ(tdOut[i],(QHdrPtr) &SIMg->immedQHdr);
	}

	UnblockInterrupts(oldSR);	//<- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- 

	if( index )
		NewIOStartMachine( SIMg);	/* Make sure Machine gets run */
	
	PrimeTime((QElemPtr)&SIMg->mySIMTMTask, 1000);	/* Once a second */
}
