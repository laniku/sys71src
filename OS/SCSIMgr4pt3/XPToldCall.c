/*
	File:		XPT.c

	Contains:	routines that implement the CAM Transport layer

	Old API Emulation Calls
		
		OSErr	SCSIReset (void)
		short	SCSIStat (void)
		OSErr	SCSIGet (void)
		OSErr	SCSISelect (short targetID)
		OSErr	SCSISelAtn (short targetID)
		OSErr	SCSICmd (Ptr buffer, short count)
		OSErr	SCSIRead (Ptr tibPtr)
		OSErr	SCSIRBlind (Ptr tibPtr)
		OSErr	SCSIWrite (Ptr tibPtr)
		OSErr	SCSIWBlind (Ptr tibPtr)
		OSErr	SCSIMsgIn (short *message)
		OSErr	SCSIMsgOut (short message)
		OSErr	SCSIComplete (short *stat, short *message, unsigned long wait)

	Written by:	Paul Wolf

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	   <ML2>	  1/5/94	pdw		Changed over to new SCSIGlobals format.
	  <SM19>	11/22/93	pdw		Rolling in from <MCxx>.
	   <MC6>	 11/8/93	pdw		Fixed a bug that, when SCSIGet was done during sync-unsafe time,
									we would set old-API busy and not clear it.
	   <MC5>	 11/5/93	pdw		Series of attempts and re-attempts to fix various VM/FileShare
									problems.
	  <SM18>	10/14/93	pdw		<MC> roll-in.
	   <MC4>	10/12/93	pdw		Fixed yet another bug - added return(noErr).
	   <MC3>	10/12/93	pdw		Added support for Synchronous data transfers, rewrote State
									Machine, message handling etc.
	   <MC2>	 9/26/93	pdw		Style and comment changes.
	  <SM17>	  9/9/93	pdw		Lots of little changes.  Name changes, temporary cache_bug
									stuff.
	  <SM16>	 7/17/93	pdw		Changed phz to phase.
	  <SM15>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
									stack switching mechanism.  Adding support for Cold Fusion.
									Rearranging HW/SW Init code. Some code optimizations. Resolving
									with my Ludwig sources.
	  <SM14>	 5/29/93	PW		Adding SCSIDebug.h to includes.
	  <SM13>	 5/25/93	DCB		(PW) Fixing up DebugStrs and trying to do something in those
									cases.
	  <SM12>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	  <LW11>	  5/1/93	PW		Getting rid of support for Ludwig A10's VirtualIDInfo structure
									(it was only meant to be in there for one build).
	   <LW9>	 3/26/93	PW		Removing aack_XPT in favor of DebugStrs.
	   <LW8>	  3/1/93	DCB		Fixed SCSIReset and changed SCSIComplete to use new timeout
									mechanism.
	   <LW7>	  3/1/93	PW		Worked around compiler "bug" in checking of scsiOldCallResult after
									issuing SCSI command - pulled assignment out of IF statement.
	   <LW6>	 2/18/93	DCB		Setting SIMNOQFREEZE to prevent hangs with SCSI Reset.
	   <LW5>	 2/17/93	PW		TIB is now put in scsiDataPtr instead of scsiHandshake.  Changed
									ittLess ROM w/1 bus case to start with no bus assigned to each
									virtual ID.
	   <LW4>	 1/27/93	PW		Added temporary hack to keep people's A10 drivers working.
	   <LW3>	 1/27/93	PW		Changed bogus to syncUnsafeCount.
	   <LW2>	12/18/92	PW		Added general SyncRequestsEnabled counter support to fix
									SCSIGets at VBL time bug.
	   <SM8>	 12/9/92	PW		Fixed HD Setup timeout on format bug by returning proper
									SCSIStat after an incomplete SCSICmd completes.
	   <SM7>	 12/5/92	PW		Added support for early return from SCSICmd. Removed phase check
									for data calls.
	   <SM6>	11/20/92	PW		Removed GetBusInfo func. Removed SIMQHead flag and added
									NoParityCk flag to old API calls. Added SCSIMsgIn, Out. Clear
									diReserved and LUN fields in GetVirtualIDInfo.
	   <SM5>	10/30/92	DCB		Changes to reflect new ACAM.h
	   <SM4>	10/14/92	PW		Added check for valid SCSI ID on SCSISelect calls.
	   <SM3>	 10/8/92	PW		Moved GetVirtualID stuff into here (from XPT.c).  Lots of
									trivial name changes.
	   <SM2>	 7/28/92	PW		Resolved differences between pdw and dcb sources.
	   <SM0>	 7/27/92	PW		Initial Check-in.

*/


#include <Types.h>
#include <Memory.h>
#include <Errors.h>
#include <OSUtils.h>
#include <SCSIStandard.h>
#include <SCSI.h>

#include "ACAM.h"
#include "SCSIDebug.h"
#include "CUtils.h"
#include "Recorder.h"

#include "XPT.h"
#include "XPTpriv.h"


extern short	BlockInterrupts(void);
extern void		UnblockInterrupts( short oldSR);


/********* External Function Prototypes **********/

Boolean	TestFor_SCSI96_2Exists( void);


/********* Function Prototypes **********/

short	EnumPhaseToSCSIStat( SCSIphase inputPhase);
long	CallSIMNewOldCall(SCSI_IO *pbPtr, XPTglobals *XPTg);
void	OldCallWait(SCSI_IO *pbPtr, XPTglobals *XPTg);

		
/*********************************************************************************
	XlateOldSCSIGlobals	-	Get what data we need from the old SCSI Manager globals
*********************************************************************************/

void
XlateOldSCSIGlobals( XPTglobals *XPTg)
{
	uchar		devMap0, devMap1;
	short		id;

	if (TestFor_SCSI96_2Exists())
	{
		devMap0 = SCSIGlobals->G_SCSIDevMap0;
		devMap1 = SCSIGlobals->G_SCSIDevMap1;
		
		for (id = 7; id>=0; --id) {
			if ( btst(id, &devMap0) )
				XPTg-> oldIDBusNumber[id] = 0;		// on bus 0
				
			else if ( btst(id, &devMap1) )
				XPTg-> oldIDBusNumber[id] = 1;		// on bus 1
				
			else
				XPTg-> oldIDBusNumber[id] = -1;		// not seen on either bus yet
		}
	}
	else 
	{
// potential problem if oldCallCap NuBus card shows up and the already seen drives on
// motherboard bus (0) don't select and we have a device at that ID on the NuBus card
		for (id = 7; id>=0; --id) {									
			XPTg-> oldIDBusNumber[id] = -1;	// not seen on any bus yet
		}
	}
}


/*********************************************************************************
	NewXPTioPB	-	allocate and initialize SCSI_IO used for old API handling
*********************************************************************************/

OSErr
NewXPTioPB( ulong pbSize, XPTglobals *XPTg)
{
	SCSI_IO *	ioPtr;

	ioPtr = (SCSI_IO *) NewPtrSysClear( pbSize);
	if (ioPtr == 0)
		return (memFullErr);
	
	XPTg->xptIOptr = ioPtr;	
	XPTg->xptIOpbSize = pbSize;

	// we're always SCSIOldCall
	// we don't understand freezing
	// old API don't do parity
	// we're always TIBs
	
	ioPtr->scsiFunctionCode	= SCSIOldCall;
	ioPtr->scsiPBLength		= pbSize;
	ioPtr->scsiFlags		= scsiSIMQNoFreeze | scsiCDBIsPointer;
	ioPtr->scsiIOFlags		= scsiNoParityCheck;	
	ioPtr->scsiDataType		= scsiDataTIB;

	return (noErr);
}



/*********************************************************************************
	OldSCSICall	-	This is our new entry point for our old SCSI calls
*********************************************************************************/

short
OldSCSICall( short selector, long parm1, long parm2, long parm3)
{
	XPTglobals	*XPTg;
	short		busID;
	short		result;
	Boolean		wasInOldCall, wasBusy, busFound;
	SCSI_IO *	ioPtr;
	SCSIResetBusPB rstPB;	// <LW8>
	
	result = noErr;			// assume no error
	
	XPTg = GetXPTg();
	
	ioPtr = XPTg->xptIOptr;

//==== if SCSIReset, ====
	
	if( selector == kSCSIReset ) {
		XPTg->oldAPIstate = kNotConnected;
		
		for( busID = 0 ; busID < XPTg->numBuses ; busID+=1 ) {
			if( XPTg->BusInfoPtr[busID] == nil )
				continue;	/* Not a valid bus */
				
			if( XPTg->BusInfoPtr[busID]->initInfo.oldCallCapable) {
				Clear( &rstPB, sizeof(rstPB));
				rstPB.scsiFunctionCode = SCSIResetBus;
				rstPB.scsiPBLength = sizeof(rstPB);
				rstPB.scsiFlags = (scsiSIMQNoFreeze);		// Old API doesn't understand freezing
				rstPB.scsiDevice.bus = busID;
				
				CallSIMaction( &rstPB, XPTg);
			}
		}
		return(0);
	}
	

//==== if SCSIStat, ====

	if (selector == kSCSIStat)
	{
		switch (XPTg->oldAPIstate) 
		{
		case kNotConnected:
		
			if ( btst(kbOldAPIBusy, &XPTg->flags) || XPTg->syncUnsafeCount) {
				return ( kmStatBSY);		// = bus is busy
			}
			else
				return ( 0);				// = bus free phase				
				
		case kGotGet:
		
			return ( kmStatBSY+kmStatSEL);	// = arbitrate successful phase

		case kSelectInProgress:
		
			return ( kmStatSEL);			// = select in progress

		case kSCSICmdInProgress:
		
			if ( ioPtr->scsiOldCallResult == scsiRequestInProgress)
				return ( EnumPhaseToSCSIStat( kCommandPhase - kmStatREQ));
	
			//else (i.e. if SCSICmd completed) fall thru to kConnected case
			XPTg->oldAPIstate = kConnected;
			XPTg->latestOldCallPhase = ioPtr->scsiCurrentPhase;
					
		case kConnected:
		
			return ( EnumPhaseToSCSIStat( XPTg->latestOldCallPhase));
			
		}
	}

//---- Check if we are currently working on an old call

	wasInOldCall = bset(kbInOldCall, &XPTg->flags);
	if (wasInOldCall)
		return( scSequenceErr);
		
		
//==== if SCSIGet, we shouldn't be busy ====

	if (selector == kSCSIGet) 
	{
		wasBusy = bset(kbOldAPIBusy, &XPTg->flags);
		if (wasBusy || XPTg->syncUnsafeCount) {
			result = scMgrBusyErr;
			if (wasBusy) {
				IfRecordError( (long)'busy');
			}
			else {
				bclr(kbOldAPIBusy, &XPTg->flags);				// we're no longer busy
				IfRecordError( (long)'unsf');
			}
		}
		else
		{
			XPTg->oldAPIstate = kGotGet;
			XPTg->latestOldCallPhase = 0;
			ioPtr->scsiOldCallResult = 0;
			result = noErr;
		}
		bclr(kbInOldCall, &XPTg->flags);
		return (result);
	}

//==== if SCSISelect, we need to do an Arbitrate/Select on the appropriate bus ====

	if (selector == kSCSISelect || selector == kSCSISelAtn)
	{
		bset(kbOldAPIBusy, &XPTg->flags);		// for SCSIEvaluator (no SCSIGet-ugh)
		XPTg->oldAPIstate = kSelectInProgress;
		
		//---- Is the SCSI ID valid?											<SM4> pdw
		
		if ( parm1<0 || parm1>6) 
		{
			result = scBadParmsErr;
			bclr(kbInOldCall, &XPTg->flags);
			bclr(kbOldAPIBusy, &XPTg->flags);				// we're no longer busy
			XPTg->oldAPIstate = kNotConnected;				// nor are we connected
			return (result);
		}
		
		//---- Do we know which Bus to use?

		if ( (busID = XPTg->oldIDBusNumber[parm1]) < 0)
		{
			//---- If not, we must do a select on each bus and create a mapping if possible
	
			busFound = false;		// assume not found
			
			//---- For each bus, attempt a select, if request_completed then we found the bus
		
			for (busID = 0; busID<XPTg->numBuses && !busFound; busID+=1)
			{
				//---- only check buses that are oldCallCapable
			
				if ( XPTg->BusInfoPtr[busID]->initInfo.oldCallCapable)
				{
RetrySelect1:
					ioPtr->scsiDevice.bus = busID;
					ioPtr->scsiDevice.targetID = parm1;
					
					//---- CALL SIM ACTION ----
			
					ioPtr->scsiSelector = selector;		// may be Select w/Atn
					CallSIMaction( ioPtr, XPTg);
					OldCallWait( ioPtr, XPTg);

					if (ioPtr->scsiOldCallResult == noErr)
					{
						busFound = true;
						break;
					}
					else if (ioPtr->scsiOldCallResult == scsiSelectTimeout)
						;
					else {
						IfDebugStr("\poldCallResult!=scsiSelTimeout or noErr");
						goto RetrySelect1;
					}
				}
			}
			
			//---- if we did find the bus, remember the mapping for all time (until reboot)
			if (busFound)
			{
				XPTg->oldIDBusNumber[parm1] = busID;
				result = noErr;
			}
			//---- if we didn't find the bus, return error
			else
			{
				result = scCommErr;
			}
		}
		
	//---- if we already had a mapping, just do a select on that bus
	
		else
		{
RetrySelect2:
			ioPtr->scsiDevice.bus = busID;
			ioPtr->scsiDevice.targetID = parm1;
			
		//---- CALL SIM ACTION ----
		
			ioPtr->scsiSelector = selector;
			CallSIMaction( ioPtr, XPTg);
			OldCallWait( ioPtr, XPTg);
			
			if (ioPtr->scsiOldCallResult == noErr)
				;
			else if (ioPtr->scsiOldCallResult == scsiSelectTimeout)
			{
				result = scCommErr;
			}
			//else if (ioPtr->scsiOldCallResult == privErrSelected) 
			//{
			//	goto RetrySelect2;
			//}
			else {
				IfDebugStr( "\poldCallResult !=scsiSelTimeout,16 or noErr");
				goto RetrySelect2;
			}
		}
		
	//=== Check results:
	
		if (result == noErr) 
		{
			XPTg->latestOldCallPhase = ioPtr->scsiCurrentPhase;
			XPTg->oldAPIstate = kConnected;
		}
		//----  if we got error, NotConnected so clear busy flag
		else
		{
			XPTg->oldAPIstate = kNotConnected;
		}
		
		if (ioPtr->scsiResult != scsiRequestInProgress)		// if io is done
			bclr(kbOldAPIBusy, &XPTg->flags);				// we're no longer busy
			
		bclr(kbInOldCall, &XPTg->flags);
		
		return (result);
	}


//==== All other calls (besides Get, Select and Stat) ====

//---- if not busy, return an error

	if ( !btst( kbOldAPIBusy, &XPTg->flags))
	{
		bclr(kbInOldCall, &XPTg->flags);
		return (scSequenceErr);
	}

//---- wait until the previous call completes

	OldCallWait( ioPtr, XPTg);
	XPTg->latestOldCallPhase = ioPtr->scsiCurrentPhase;
	XPTg->oldAPIstate = kConnected;

//---- dispatch to appropriate routine handler

	switch (selector) 
	{
	
 //ÑÑÑÑ SCSICmd ( buffer, count) ÑÑÑÑ
	
	case kSCSICmd:	
		if (XPTg->latestOldCallPhase != kCommandPhase) {
			result = scPhaseErr;
			break;
		}
		ioPtr->scsiCDB.cdbPtr = (uchar *)parm1;
		ioPtr->scsiCDBLength = parm2;

		//---- CALL SIM ACTION ----
	
		ioPtr->scsiSelector = selector;
		CallSIMNewOldCall( ioPtr, XPTg);

		result = ioPtr->scsiOldCallResult;										// <LW7> pdw
		if (result != scsiRequestInProgress) {
			XPTg->latestOldCallPhase = ioPtr->scsiCurrentPhase;
		} 
		else {
			XPTg->oldAPIstate = kSCSICmdInProgress;
			result = noErr;
		}
		break;
		
 //ÑÑÑÑ SCSIDataIn ( tibPtr) ÑÑÑÑ
	
	case kSCSIRead:	
		ioPtr->scsiTransferType = scsiTransferPolled;
		goto commonReadCalls;
	case kSCSIRBlind:	
		ioPtr->scsiTransferType = scsiTransferBlind;
		
commonReadCalls:
		ioPtr->scsiFlags &= ~scsiDirectionMask;
		ioPtr->scsiFlags |= scsiDirectionIn;
		
		goto commonDataCalls;
		
		
 //ÑÑÑÑ SCSIDataOut ( tibPtr) ÑÑÑÑ
	
	case kSCSIWrite:	
		ioPtr->scsiTransferType = scsiTransferPolled;
		goto commonWriteCalls;
	case kSCSIWBlind:	
		ioPtr->scsiTransferType = scsiTransferBlind;
		
commonWriteCalls:
		ioPtr->scsiFlags &= ~scsiDirectionMask;
		ioPtr->scsiFlags |= scsiDirectionOut;
		
commonDataCalls:
		ioPtr->scsiDataPtr = (uchar *)parm1;		// put TIB into scData
		ioPtr->scsiDataLength = 0;
		bset( kbTIB, &ioPtr->XPTprivateFlags);


 //==== Common SIM calling code ====
	
commonCallSIM:
		//---- CALL SIM ACTION ----
	
		ioPtr->scsiSelector = selector;
		CallSIMNewOldCall( ioPtr, XPTg);
		OldCallWait( ioPtr, XPTg);

		result = ioPtr->scsiOldCallResult;
		XPTg->latestOldCallPhase = ioPtr->scsiCurrentPhase;
			
		break;
		
		
 //ÑÑÑÑ SCSIMsgIn ( msgPtr) ÑÑÑÑ												//<SM6> pdw
	
	case kSCSIMsgIn:	
		ioPtr->scsiSCSImessage = 0;

		//---- CALL SIM ACTION ----
	
		ioPtr->scsiSelector = selector;
		CallSIMNewOldCall( ioPtr, XPTg);
		OldCallWait( ioPtr, XPTg);

		result = ioPtr->scsiOldCallResult;
		XPTg->latestOldCallPhase = ioPtr->scsiCurrentPhase;
		*(short *)parm1 = ioPtr->scsiSCSImessage;
			
		break;
	
		
 //ÑÑÑÑ SCSIMsgOut ( msg) ÑÑÑÑ													//<SM6> pdw
	
	case kSCSIMsgOut:	
		ioPtr->scsiSCSImessage = parm1;
		goto commonCallSIM;
	
		
 //ÑÑÑÑ SCSIComplete ( statPtr, msgPtr, wait) ÑÑÑÑ
	
	case kSCSIComplete:	
	
		/* Convert parm3 to seconds */
		ioPtr->scsiTimeout = parm3 * 60;

		//---- CALL SIM ACTION ----
	
		ioPtr->scsiSelector = selector;
		CallSIMNewOldCall( ioPtr, XPTg);
		OldCallWait( ioPtr, XPTg);

		XPTg->latestOldCallPhase = ioPtr->scsiCurrentPhase;
			
		*(short *)parm1 = ioPtr->scsiSCSIstatus;
		*(short *)parm2 = ioPtr->scsiSCSImessage;
		
		XPTg->oldAPIstate = kNotConnected;		// we should check for bus free b4 doing this
		break;
		
	}
	
	if (ioPtr->scsiResult != scsiRequestInProgress)		// if io is done
		bclr(kbOldAPIBusy, &XPTg->flags);				// we're no longer busy
		
	bclr(kbInOldCall, &XPTg->flags);
	
	return (result);
}


/*********************************************************************************
	EnumPhaseToSCSIStat	-	translate enum SCSIphase to SCSIStat type result
*********************************************************************************/

short
EnumPhaseToSCSIStat( SCSIphase inputPhase)
{
	if (inputPhase < kBusFreePhase)
		return( kmStatBSY + kmStatREQ + (inputPhase<<2));
		
	switch (inputPhase)
	{
	case kBusFreePhase:
		return (0);
		
	case kArbitratePhase:
		return (kmStatBSY);
		
	case kSelectPhase:
		return (kmStatSEL);
		
	case kMessageInPhaseNACK:
		return ( EnumPhaseToSCSIStat(kMessageInPhase) - kmStatREQ + kmStatACK);
	}
}


/*********************************************************************************
	CallSIMNewOldCall	-	perform an Action (either XPT or pass it to SIM)
*********************************************************************************/

long
CallSIMNewOldCall(SCSI_IO *ioPtr, XPTglobals *XPTg)
{
	BusInfo		*busInfoPtr;
	
	busInfoPtr = XPTg->BusInfoPtr[ioPtr->scsiDevice.bus];

	(busInfoPtr->initInfo.NewOldCall) (ioPtr, (busInfoPtr->initInfo).SIMstaticPtr);

	return ( 0);
}


/*********************************************************************************
	OldCallWait	-	wait for an old call request to be completed
*********************************************************************************/

void
OldCallWait(SCSI_IO *ioPtr, XPTglobals *XPTg)
{
	do {
		CheckInterrupts( XPTg);
	} while (ioPtr->scsiOldCallResult == scsiRequestInProgress);
}


/*********************************************************************************
	GetVirtualIDInfo	-	handle this request
*********************************************************************************/

void
GetVirtualIDInfo(SCSIGetVirtualIDInfoPB *pbPtr, XPTglobals *XPTg)
{
	uchar 		oldID;
	short		busNum;

	oldID = pbPtr->scsiOldCallID;

	if( oldID > 6 || oldID < 0 ) {		// Old IDs are ONLY 0-6!
		pbPtr->scsiResult = scsiTIDInvalid;
		return;
	}
	
	busNum = XPTg-> oldIDBusNumber[ oldID];
	if (busNum != -1)
	{
		pbPtr->scsiExists = true;
		pbPtr->scsiDevice.diReserved	= 0;
		pbPtr->scsiDevice.bus		= busNum;
		pbPtr->scsiDevice.targetID	= oldID;
		pbPtr->scsiDevice.LUN		= 0;						//<SM6> pdw
	}
	else
	{
		pbPtr->scsiExists = false;
		*(long *)&(pbPtr->scsiDevice) = -1;
	}
}