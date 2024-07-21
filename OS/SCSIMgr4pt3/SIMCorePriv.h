/*
	File:		SIMCorePriv.h

	Contains:	private header stuff for the core of the Apple SIM layer

	Written by:	Paul Wolf

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	  <SM18>	 1/31/94	DCB		Changed prototype for SIMDualIntPoll
	  <SM17>	 1/29/94	DCB		Added otherSIMg to the SIM globals for better dual bus support.
	  <SM16>	11/22/93	pdw		Rolling in from <MCxx>.
	   <MC7>	11/11/93	pdw		Made the HALglobals 16-byte aligned relative to SIMglobals.
	   <MC6>	 11/8/93	pdw		Added some spares in the globals.
	  <SMG2>	 9/29/93	chp		Include some prerequisite headers if necessary.
	  <SM14>	10/29/93	DCB		<MC> roll-in.
	   <MC4>	10/28/93	pdw		Added some states used during Target mode.
	  <SM13>	10/14/93	pdw		<MC> roll-in.
	   <MC3>	10/12/93	pdw		Added a couple more states.
	   <MC2>	10/12/93	pdw		Added support for Synchronous data transfers, rewrote State
									Machine, message handling etc.
	  <SM12>	 9/12/93	pdw		Prototype maintenance.
	  <SM11>	  9/9/93	pdw		Lots of little changes.  Name changes, temporary cache_bug
									stuff.
	  <SM10>	 7/17/93	pdw		A few little things.
	   <SM9>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
									stack switching mechanism.  Adding support for Cold Fusion.
									Rearranging HW/SW Init code. Some code optimizations.
	   <SM8>	 5/25/93	DCB		Rollin from Ludwig. (The next item below)
	   <LW9>	 5/21/93	PW		Adding SIMg parameter to ValidateDeviceIdent so that it can
									check HostID.
	   <SM7>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	   <LW8>	 4/30/93	DCB		Added prototype for CallBusInquiry
	   <LW6>	 4/14/93	DCB		Added SIMInitInfo record to the SIM Globals so we would have it
									later when we re-register with a new XPT.
	   <LW5>	 3/26/93	PW		Moved CallCompRoutine into SIM from XPT.
	   <SM5>	 1/31/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <LW4>	 1/27/93	PW		Added defaultDisc boolean for optimization of non-concurrent
									environments. Added prototype for SIMIntPoll.
	   <LW3>	 1/12/93	DCB		Added an abort command parameter block to the globals for use in
									SIMTimerProc.
	   <LW2>	12/17/92	DCB		Got rid of a parameter in SetupResetPB which was no longer
									needed.
	   <SM4>	 12/5/92	PW		Changed ValidateDI prototype.
	   <SM3>	11/20/92	DCB		Async Abort,Terminate and Reset Device support plus I removed
									some include files
	   <SM2>	10/30/92	DCB		Changed to reflect new ACAM.h
		 <1>	 10/8/92	PW		first checked in

	Before SIMCore.h and SIMCorePriv.h split	
	   <sm7>	 9/14/92	DCB		Added some constants for SCSI ID range limits
	   <sm6>	 9/11/92	DCB		Mostly support for BusDeviceReset. Also added a WentBusFree
									state
	   <sm5>	 8/31/92	DCB		Added aborted and terminated ioStats.
	   <sm4>	 8/30/92	PW		Added kAssertATN to HALactions record.
	   <sm3>	 8/30/92	DCB		Added Immediate Queue to the globals for Terminate/Abort IO
	   <sm2>	 8/20/92	DCB		Fixed SCSI Bus Reset

*/

#ifndef __SIMCOREPRIV__
#define __SIMCOREPRIV__

#ifndef __SCSI__
#include <SCSI.h>
#endif

#ifndef __SIMCORE__
#include "SIMCore.h"
#endif


//**** SCSI State Machine states *****

typedef enum {	kIdle =0, 				// 0
				kInitiatingNormal, 
				kInitiatingSDTR, 
				kInitiatingAsyncMsg, 
				kInitiatingOldCall, 	// 4
				kReconGettingMsg, 
				kReconAcceptingMsg,
				kReconRejectingMsg,
				kAcceptingDataMsg,		// 8
				kRejectingDataMsg,
				kSendingMsg,
				kGettingDataMsg,
				kSendingCommand,		// C
				kSwitchingPhase,		
				kGettingStatus,
				kBitBucketing,
				kSelecting,				// $10
				kAwaitingOldCall,
				kPerformingOldCall,
				kWentBusFree,
				kGettingSCSIMsgIn,		// $14
				kWastingPhase,
				kDoingData,
				kGotR_selected,
				kAcceptingRejectedIdentify,	// $18
				kAbortingRejectedIdentify,
				kSendingKillMsg,
				kSendingEarlyKillMsg,
				kSendingCommand,			// $1c
				kAcceptingSDTR,
				kAcceptingEarlySDTR,
				kRejectingSDTR,
				kSendingDetectedErrorMsg,	// $20
				kRejectingEarlyMsg,
				kEarlySwitchingPhase,
				kDisconnecting,
				kDisconnectingB4Command,	// $24
				kFailingSelect,
				kWastedToBusFree,
				kAcceptingRejectedAsyncMsg,
				kHandlingSelected,			// $28
				kFreeMachine,
			kNumSSMstate
	} SSMstate;


/********** GLOBALS **************/

typedef struct  {

// Static description of bus

	HALinitInfo	HALinfo;		// copy of HALinitInfo, made after registration

// Dynamic description of bus

	short		unusedS1;		// to align qHdr
	QHdr		qHdr;			// q header for the SCSI_Exec_IO pbs

	short		unusedS2;		// to align qHdr
	QHdr		resetHdr;		// q header for pbs which have been cancelled by a reset

	short		unusedS3;		// to align qHdr
	QHdr		immedQHdr;		// q header for immediate actions (Abort, reset etc.) <sm3>

	short		pushedState;	// to align qHdr
	QHdr		resetPBQ;		// a queue of ResetDevice parameter blocks

	uchar		SSMflags;		// 8 flags for SCSI state machine
	uchar		Qflags;			// 8 flags for SCSI Q
	Boolean		flag2;			// 
	Boolean		flag4;			// 
	Boolean		r_selectWaiting;// set by R_selectISR and cleared by StartMachine (+others)
	Boolean		sensePBBusy;	// set whenever autosense IOpb is in use
	Boolean		SIMBusy;		// 
	Boolean		flag5;			// 
	
	short		state;			// current state of State Machine
	uchar		reconTargetID;	// ID of target that just reconnected
	uchar		reconLUN;		// LUN of target ...

	HALactionPB	halPB;			// action PB for speaking at the HAL
	SIM_IO *	currIOptr;		// current IO PB that the SSM is talking about

	ushort		senseWaiting;	// Total number of parmeter blocks waiting for autosense
	SCSIInstr 	senseTIB[2];	// The TIB for autosense ($a * 2 = $14)

	void		(*MakeCallback)();	// pointer to the XPT layer’s MakeCallback routine
	Boolean		defaultDisc;	// true if we should default to disconnect allowed
	uchar		hostID;			// Macintosh's (initiator's) SCSI ID on this bus
	char		unusedC8;
	char		unusedC9;
	
	Boolean		needNegot[8];	// array of flags (per target): needs negotiation
	uchar		syncRAoffset[8];// REQ/ACK offset (per target)
	uchar		syncPeriod[8];	// Transfer period factor (per target)

	SIM_IO *	discIOs[8][8];	// array of pointers to PBs that are disconnected
	uchar		LUNstate[8][8];	// array of flags for the state of a particular LUN (Disconnected, Frozen etc)

	SIMTMTask	mySIMTMTask;	// time manager task queue entry (for timeouts)
	
	SIMinitInfo * initInfo;		// Saved SIM Init Info for re-registration
	
	Ptr			otherSIMg;		// used on dual bus machines

	long		spares[19];		// extras to make patching easier
	
// SIM_IOs (should be at end to make Macsbugging easier)
	
	SIM_IO		sensePB;		// A Parameter block to be used for a request sense
	SIM_IO		resetDevPB;		//
	SCSIAbortCommandPB abortPB;	// A parameter block to timeout parameter blocks

} SIMglobals;

#define sizeofSIMGlobals (((sizeof(SIMglobals)-1)/16+1)*16)


//====== Bit definitions for SSMFlags field ======

#define kbSSMBusy			0


/******** Bit definitions for LUNstate field ********/

#define	km_LUNdisconnected	0x01	/* LUN has disconnected */
#define	km_LUNfrozen		0x02	/* LUN has been frozen  */


/******** Fake Functions **********/

#define IdentifyMsg(a,b) (0x80+(a<<6)+(b))

#define IdentifyToLUN(a)  ((a)&0x7)

#define FindUsedLUN(a,b)	(SIMg->LUNstate[a][b])

#define ReconnectIO(a,b)	{SIMg->discIOs[a][b] = 0 ; SIMg->LUNstate[a][b] &= ~km_LUNdisconnected;}
#define DisconnectIO(a,b,c)	{SIMg->discIOs[a][b] = (c); SIMg->LUNstate[a][b] |= km_LUNdisconnected;}

#define DefrostLUN(a,b)		SIMg->LUNstate[a][b] &= ~km_LUNfrozen;
#define FreezeLUN(a,b)		SIMg->LUNstate[a][b] |= km_LUNfrozen;

#define CallHALaction( a, p, s)						do {	\
	(p)->action = (a);								\
	((SIMg->HALinfo.HALaction)(p) );				} while (false)

#define CallHALResetBus( a)							do {	\
	((SIMg->HALinfo.HALResetBus)(a) );				} while (false)

#define CallHALSyncConfig(o,p,h)					do {	\
	((SIMg->HALinfo.HALSyncConfig)(o,p,h) );		} while (false)

#define CallHALAssertATN( a)						do {	\
	((SIMg->HALinfo.HALAssertATN)(a) );				} while (false)

#define CallHALTeardownIO( i, h)					do {	\
	((SIMg->HALinfo.HALTeardownIO)((i),(h)));		} while (false)

/******** Some Basic Constants *********/

#define kHighestTarget	7														// <sm7>
#define kHighestLUN		7														// <sm7>

#define kHostID		7															// <sm7>
#define kMaxTransferType	1

#define SUPPORTED_scFlags	( 		\
			scsiDirectionMask		| \
			scsiDisableAutosense	| \
			scsiCDBIsPointer		| \
			scsiDisableSyncData		| \
			scsiSIMQHead			| \
			scsiSIMQFreeze			| \
			scsiSIMQNoFreeze		| \
			scsiDoDisconnect		| \
			scsiDontDisconnect		| \
			scsiDataDMAready )

#define SUPPORTED_scIOFlags  ( 		\
			scsiNoParityCheck		| \
			scsiDisableSelectWAtn	| \
			scsiSavePtrOnDisconnect	| \
			scsiNoBucketIn			| \
			scsiNoBucketOut ) 

#define SUPPORTED_scDataTypes  (	\
			scsiBusDataTIB			| \
			scsiBusDataBuffer		| \
			scsiBusDataSG ) 

/******** Function Prototypes - Entry Points (called by XPT via SIMinitInfo) ********/

OSErr	SIMinit (SIMinitInfo * SIMinfoPtr);
long	SIM_ISR (SIMglobals * SIMg);
long	SIMIntPoll (SIMglobals * SIMg);
void	SIMaction (SIM_IO *ioPtr, SIMglobals * SIMg);
void	NewOldCall( SIM_IO * ioPtr, SIMglobals * SIMg);
long	SIMDualIntPoll(SIMglobals *SIMg);

/******** Function Prototypes - Internal to SIM ********/

void	CallCompRoutine( SCSI_IO * ioPtr);
void	ResetSIM( SIMglobals * SIMg);
void	ReconnectEvent( HALactionPB * reconPBptr);
void	ReconStartMachine( SIMglobals * SIMg);
void	NewIOStartMachine( SIMglobals * SIMg);
void	ReconnectISR( SIMglobals * SIMg);
Boolean	TheMachine( OSErr * finalStatus, SIM_IO ** completedIO, SIMglobals * SIMg);
void	StartTimer( SIMglobals * SIMg);
void	SIMTimerProc( void);
Boolean	CallBusInquiry( SIM_IO * ioPtr, SIMglobals * SIMg);
void	CompleteIO( OSErr finalStatus, SIM_IO * ioPtr, SIMglobals * SIMg);
short	BlockInterrupts(void);
void	UnblockInterrupts( short oldSR);
void	SetupResetPB( uchar TargetID, SIMglobals * SIMg );
OSErr	ValidateDeviceIdent( DeviceIdent TargetID, SIMglobals * SIMg );
Boolean ValidatePB( SIM_IO *ioPtr, SIMglobals * SIMg );
void	CallMachine(SIMglobals * SIMg);
extern SIM_IO * GetNextAutoSense( SIMglobals * SIMg);


#endif __SIMCOREPRIV__
