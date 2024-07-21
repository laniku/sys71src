/*
	File:		SIMCore.h

	Contains:	header stuff for the core of the Apple SIM layer

	Written by:	Paul Wolf

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SM25>	12/19/93	DCB		Added hdshkRemainder to the ioPB.   This is to help solve the
									handshake across scatter gather boundries problem.
	  <SM24>	11/22/93	pdw		Rolling in from <MCxx>.
	   <MC5>	 11/8/93	pdw		Added kHALselectedAsTargetFld error condition.
	  <SMG2>	 9/29/93	chp		Include some prerequisite headers if necessary.
	  <SM22>	10/29/93	DCB		<MC> roll-in.
	   <MC3>	10/28/93	pdw		Added equate for new action.  Adding some globals.
	  <SM21>	10/14/93	pdw		<MC> roll-in.
	   <MC2>	10/12/93	pdw		Added support for Synchronous data transfers, rewrote State
									Machine, message handling etc.
	  <SM20>	 9/12/93	pdw		Prototype maintenance.
	  <SM19>	  9/9/93	pdw		Lots of little changes.  Name changes, temporary cache_bug
									stuff.
	  <SM18>	 7/17/93	pdw		Lots of little things.
	  <SM17>	  7/8/93	pdw		Removing duplicate kMaxTransferType definition.
	  <SM16>	 5/25/93	DCB		Rollin from Ludwig. (The next item below)
	  <LW10>	 5/21/93	PW		Adding hwDescPtr field to HALinitInfo structure so HALinit can
									get to it.
	  <SM15>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	   <LW9>	 4/30/93	DCB		Adding a HalInfo entry point to the HALInitInfo record.
	   <LW8>	 4/29/93	DCB		Fixing Build - Sorry bout that.
	   <LW7>	 4/14/93	DCB		Added SetParity HALAction and the ParityError ioEvent
	   <LW6>	 3/26/93	PW		Added kWastePhase and deleted kRejectingMsg.
	   <LW5>	  3/1/93	DCB		Changed definition of IOEvents to be flags and removed
									scConnTimer because it isn't needed anymore.
	   <LW4>	 2/17/93	PW		Added GettingSCSIMsgIn state and savedResidLen field for fix to
									SCSIMsgIn not dropping ACK bug and for bitbucketing bug.
	  <SM12>	 1/31/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <LW3>	 1/27/93	PW		Added scsiDataType field support and fields in SIM_IO for storing
									ptrs to data and xfer routines. AddedSIMIntPoll routine support.
	   <LW2>	  1/6/93	DCB		Added kbUseDblBuffer bit to the SIMprivFlags field to fix SCSI
									into NuBus bug. Radar Bug # 1059322.
	  <SM11>	 12/5/92	PW		Added kMaxTransferTypes stuff.
	  <SM10>	11/20/92	DCB		Removed some include files to solve makefile dependency problems
	   <SM9>	10/30/92	DCB		Adding HAL privates to the SIM_IO structure
	   <SM8>	 10/8/92	PW		Added stuff needed for variable-sized SCSI_IO support.  Changed
									some prototypes.  Added support for the ioEvent field.
	   <SM7>	 9/14/92	DCB		Added some constants for SCSI ID range limits
	   <SM6>	 9/11/92	DCB		Mostly support for BusDeviceReset. Also added a WentBusFree
									state
	   <SM5>	 8/31/92	DCB		Added aborted and terminated ioStats.
	   <SM4>	 8/30/92	PW		Added kAssertATN to HALactions record.
	   <SM3>	 8/30/92	DCB		Added Immediate Queue to the globals for Terminate/Abort IO
	   <SM2>	 8/20/92	DCB		Fixed SCSI Bus Reset

*/

#ifndef __SIMCORE__
#define __SIMCORE__

#ifndef __MEMORY__
#include <Memory.h>
#endif

#ifndef __TIMER__
#include <Timer.h>
#endif

#ifndef __ACAM__
#include "ACAM.h"
#endif


/*********** HALaction operation selectors ************/

typedef enum {	kInitiate =0,			// 0
				kBitBucket,
				kDataIn,
				kDataOut,
				kAcceptMsg,				// 4
				kUnusedHALaction,
				kunusedMI,
				kSendMsgOut,
				kStatus,				// 8
				kComplete,			
				kSaveDataPointer,
				kModifyDataPointer,
				kRestorePointers,		// C
				kGetReconnectInfo,
				kGetSelectInfo,
				kSelect,
				kunused,				// $10
				kCommand,
				kSetParity,				// $12
				kHandleSelected,
			kNumHALaction,			// keep last - MAKE SURE you modify HAL's Equ.a too
			kHALactionsBogus =256	// force word length of enum
	} HALactions;


typedef enum {	kHALnoErr =0,
				kHALselectFld, 			// initiate, select, select w/atn
				kHALreselected,			// we were reselected (maybe during an initiate)
				kHALselectedAsTarget,	// we were selected (maybe during an initiate)
				kHALselectedAsTargetFld,// curio bug - they tried to select us and we hung
				kHALnoCommand,			// initiate
				kHALpartialCommand,		// initiate, command
				kHALpartialMsgIn,		// MsgIn
				kHALmsgInDisconnected,	// MsgIn
				kHALpartialDataIn,		// DataIn
				kHALpartialDataOut,		// DataOut
				kHALpartialMsgOut,		// MsgOut
				kHALmsgOutDisconnected,	// MsgOut
				kHALreselectBogus,		// GetReconnectInfo
			kNumHALresult,
			kHALresultBogus =256
	} HALresult;


typedef enum {	kPBidle = 0,				// 0: in the queue, nothing yet
				kAttemptingInitiation,		// 1: arb-sel-identify in progress
				kNexusEstablished,			// 2: identify msg sent and received
				kSentCommand,				// 3: cdb sent
				kDisconnected,				// 4: cdb sent, disconnected
				kCompleted,					// 5: received status 
				kSelectComplete,			// 6: SCSISelect complete
				kNeedsSense,				// 7: Waiting for the autosense parameter block
				kGotSense,					// 8: No Longer waiting for autosense parameter block
				kDisconnectedB4Command,		// 9: cdb sent, disconnected
			kIOStatBogus = 256
	} IOStat;


// A list of ioEvents which could affect the interpretation of errors in CompleteIO <LW5> 

#define		kmAborted			0x0001				// PB was aborted by an AbortCommand
#define		kmTerminated		0x0002				// Hasta la Vista Baby!
#define		kmBDRSent			0x0004				// Bus Device Reset was sent to the target
#define		kmTimedOut			0x0008				// timed out
#define		kmMsgSent			0x0010				// message was delivered to the target
#define		kmMsgRejected		0x0020				// message rejected by target
#define		kmBadParity			0x0040				// bad parity detected by initiator
#define		kmAutoSense			0x0080				// Autosense has been executed


// Private error codes in ACAM defined range of error codes

enum {	
	privErrSelected			= (scsiErrorBase+0x80),	// -7808 = 
	scsiKillMsgRejected		= (scsiErrorBase+0x81),	// -7807 = Abort/Term/BDR msg rejected
		lastPrivErr
};



// SIM layer privates in SCSI_IO PB - 
//		one big mega PB including the SCSI_IO from ACAM + the SIM's per-IO vars

typedef struct SIM_IO
{
	SCSI_IO_Macro					// the ACAM-specified SCSI_IO pb
	
	Ptr 		SIMg;				// ptr to SIM globals (needed for autosense compl. function)
	ulong		scTimer;			// Timer current value (in seconds)
	ushort		hdshkRemainder;		// Leftover handshake from previous SG element
	uchar		hdshkIndex;			// The handshake element that the above remainder refers to 
	uchar		rsrvd6;				// reserved
	ushort		ioStat;				// intermed. status of this guy
	ushort		ioEvent;			// additional status to explain misc asynchronous events <SM??>
	uchar		firstError;			// first error detected (saved for later use by CompleteIO)
	uchar		SIMprivFlags;		// SIM private flags (for this PB)
	ushort		rsrvd7;				// reserved											<SM5?>
	Ptr			pendingMsgPB;		// ParameterBlock for an Async operation to be undertaken ASAP <SM10>
	Ptr			currentSGptr;		// current data ptr (to SG entry)
	ulong		currentSGcount;		// current count (withing SG entry)
	Ptr			savedSGptr;			// saved data ptr (to SG entry)
	ulong		savedSGcount;		// saved count (withing SG entry)
	Ptr			ioQueue;			// the queue that this PB has been enqueued in		<SM4>
	OSErr		savedResult;		// the final result of the PB (placed in scsiResult only after autosense has been executed)
	ushort		rsrvd8;
	MemoryBlock	logical;			// The logical address of the current user buffer	<SM9>
	MemoryBlock	physical;			// The physical address of the current user buffer	<SM9>
	long		dataRoutine;		// data desc interp. routine to use for this I/O
	long		xferRoutine;		// data transfer routine to use for this I/O
	long		savedResidLen;		// saved (not current) residual length
	ulong		transLogEnd;		// end of cached translation (logical addr)
} SIM_IO;



/*********** HALaction Parameter Block ************/

typedef struct {		// note: '->' == to HAL,    '<-' == from HAL to SSM
				// The first two fields remain constant throughout the connection
	uchar *		HALstaticPtr;		// -> alloc. ptr to the HAL's static vars
	SIM_IO *	ioPtr;				// -> primarily for Initiate

	short		action;				// -> what to do
	OSErr		result;				// <- error
	ushort		selectorID;			// <- used for reconnect
	short		unused;

	Boolean		sendCDB;			// -> flag = send CDB during initiate
	uchar		phase;				// <- current phase
	uchar		msgInLen;			// <> number of msg in bytes
	uchar		msgOutLen;			// <> number of msg out bytes

	uchar		msg[8];				// <> spot to store 8 byte msg in/out

} HALactionPB;


// Flags for HALactionPB flags field 



// Flags for SIMprivFlags field

enum {
	kbDataDone			= 0,	// scatter/gather list has been exhausted
	kbSetupComplete		= 1,	// buffer(s) in this PB are setup for DMA
	kbUseDblBuffer		= 2,	// buffer was not lockable/DMAable (NuBus Space)
	kbBitBucketed		= 3,	// we were forced to bit bucket
	kbUseDirectDMA		= 4		// use direct DMA during data transfer
};
#define kmDataDone			(1<<kbDataDone)
#define kmSetupComplete		(1<<kbSetupComplete)
#define kmUseDblBuffer		(1<<kbUseDblBuffer)
#define kmBitBucketed		(1<<kbBitBucketed)
#define kmUseDirectDMA		(1<<kbUseDirectDMA)


// Assorted defines

#define dtQElSize 20


/*********** SIMRegisterHAL parameter block ************/

typedef struct {			// directions (<->) are for SIMRegisterHAL call
	uchar *		HALstaticPtr;		// <- alloc. ptr to the HAL's static vars
	long		staticSize;			// -> num bytes HAL needs for static vars
	long		(*HALinit)();		// -> pointer to the HAL init routine
	void		(*HALaction)(HALactionPB * halPBptr);	// -> pointer to the HAL action routine

	long		(*HAL_ISR)();		// -> pointer to the HAL ISR routine
	long		(*HALIntPoll)();	// -> pointer to the HAL interrupt poll routine
	long		(*HALBusInquiry)();	// -> pointer to the HAL Info routine
	void		(*HALResetBus)(void * HALg);	// -> pointer to the HAL ResetBus routine

	void		(*HALAssertATN)(void * HALg);
	void		(*HALTeardownIO)(SIM_IO * ioPtr, uchar * HALg);
	void		(*HALSyncConfig)(long, long, void * HALg);
	void		(*unusedV)(void * HALg);

	uchar		syncRAoffset;			// -> REQ/ACK offset to use for sync negotiation
	uchar		minPeriodFactor;		// -> min transfer period to request in SDTR
	Boolean		HBAisSync;				// -> 
	Boolean		HBAisFast;				// -> 
	Boolean		oldCallCapable;			// -> true if this HAL can handle old-API calls
	Boolean		usesThreshold8;			// -> 
	ushort		busID;					// <- bus number for the registered bus
	void		(*ReconnectISR)();		// <- to make ReconnectISR call 
	void		(*XPT_ISR)();			// <- ptr to the XPT ISR

	uchar *		SIMstaticPtr;			// <- so SSM callback has its globals
	void *		hwDescPtr;				// -- for use by HAL only
	long		supported_scFlags;		//
	short		supported_scIOFlags;	//
	short		supported_scDataTypes;	//		

} HALinitInfo; 


/******** Function Prototypes - Entry Points (called by XPT directly) ********/

OSErr	SIMRegisterHAL (HALinitInfo *HALinfo);
OSErr	SIMReregisterHAL (HALinitInfo *HALinfo);
void	SIMDeregisterHAL (ushort busID);


/********** Timeout Stuff **********/

typedef struct simtmtask {
	TMTask theTask;
	Ptr SIMg;
} SIMTMTask;


#endif __SIMCORE__
