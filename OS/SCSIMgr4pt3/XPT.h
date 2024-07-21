/*
	File:		XPT.h

	Contains:	header stuff for XPT

	Entry points:

	Written by:	Paul Wolf

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	   <ML2>	  1/5/94	pdw		Added SCSIBusy to OldSCSICalls even though it's not used in
									XPTOldCall.c.
	  <SMG2>	 9/29/93	chp		Include ACAM.h if necessary.
	  <SM12>	10/14/93	pdw		<MC> roll-in.
	   <MC2>	10/12/93	pdw		Added support for Synchronous data transfers, rewrote State
									Machine, message handling etc.
	  <SM11>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
									stack switching mechanism.  Adding support for Cold Fusion.
									Rearranging HW/SW Init code. Some code optimizations.
	  <SM10>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	   <LW4>	 3/26/93	PW		Changing the name of CallCompRoutine to XPTCallCompRoutine as
									part of moving all EnteringSIM/ExitingSIM calls into SIM.
	   <LW3>	  3/1/93	DCB		Changed prototype to CallCompRoutine to make life easier for
									developers.
	   <LW2>	 1/27/93	PW		Removed DItoLUN/Target macros and moved some prototypes to
									XPTpriv.h
	   <SM6>	 12/5/92	PW		Added kSCSICmdInProgress state for support of returning from
									SCSICmd before REQ for next phase.
	   <SM5>	11/20/92	PW		Removed DItoBus macro and added InitXPT prototype.
	   <SM4>	 11/1/92	DCB		Changed final status to OSErr so that CallCompRoutine won't
									truncate the result.
	   <SM3>	10/30/92	DCB		Changes to reflect new ACAM.h
	   <SM2>	 10/8/92	PW		Added globals needed for variable-sized SCSI_IO support.

*/

#ifndef __XPT__
#define __XPT__

#ifndef __ACAM__
#include "ACAM.h"
#endif


/******** Old Call Enumerators ********/

typedef enum {	kSCSIReset =0,			// 0
				kSCSIGet,
				kSCSISelect,
				kSCSICmd,
				kSCSIComplete,			// 4
				kSCSIRead,
				kSCSIWrite,
				kSCSIunused,
				kSCSIRBlind,			// 8
				kSCSIWBlind,
				kSCSIStat,
				kSCSISelAtn,
				kSCSIMsgIn,				// C
				kSCSIMsgOut,
				kSCSIBusy,
			kNumOldSCSICalls,
			kOldSCSICallsBogus =256
	} OldSCSICalls;


/******** Old Call States ********/

typedef enum {	kNotConnected =0,			// 0
				kGotGet,
				kSelectInProgress,
				kConnected,
				kSCSICmdInProgress,
			kNumOldCallStates,
			kOldCallStatesBogus =256
	} OldCallStates;


/************ Function Prototypes **************/

void	XPTCallCompRoutine( SCSI_IO * ioPtr);			// <LW3>
OSErr	InitXPT();
pascal void	DeferredCall(void);						// called by DeferredTaskMgr


/************ Inlines **************/

#pragma parameter __D0	sp(__D0)		/* move.l   sp, D0 */
long					sp(void)			= {0x200f}; 


#endif __XPT__
