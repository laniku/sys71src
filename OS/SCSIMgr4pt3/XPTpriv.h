/*
	File:		XPTpriv.h

	Contains:	private header stuff for XPT

	Written by:	Paul Wolf

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SM21>	 1/31/94	DCB		Added a second version number for the SCSI Busy patch
	  <SM20>	 1/25/94	DCB		Added a version number for the SCSI Busy patch.
	   <ML3>	  1/9/94	pdw		Added busyPatchVers field.
	   <ML2>	  1/5/94	pdw		Changed SCSIGlobals constant to actually mean something.  Added
									SCSIBusy stuff.  Added a bunch of fields at end of
									SCSIGlobalsRec.
	  <SM18>	12/19/93	DCB		Added a couple of function prototypes
	  <SM17>	11/22/93	pdw		Rolling in from <MCxx>.
	   <MC7>	11/11/93	pdw		Got rid of inDebugger field from XPT globals structure since it
									wasn't the one being used.
	   <MC6>	 11/9/93	pdw		Added include of XPT.h.
	   <MC5>	 11/5/93	pdw		Series of attempts and re-attempts to fix various VM/FileShare
									problems.
	  <SMG2>	 9/29/93	chp		Include some prerequisite headers if necessary.
	  <SM15>	10/29/93	DCB		<MC> roll-in.
	   <MC4>	10/28/93	pdw		Got rid of unused variable and changed InitRecorder prototype.
	  <SM14>	10/14/93	pdw		<MC> roll-in.
	   <MC3>	10/12/93	pdw		Added support for Synchronous data transfers, rewrote State
									Machine, message handling etc.
	   <MC2>	 9/26/93	pdw		Added some debugging bits for BootItt.
	  <SM13>	  9/9/93	pdw		Lots of little changes.  Name changes, temporary cache_bug
									stuff.
	  <SM12>	 7/17/93	pdw		Pulled jvSelected out of here and put in HALglobals where it
									belongs.
	  <SM11>	  7/8/93	pdw		Added InitRecorder prototype.
	  <SM10>	 5/29/93	PW		Moving Include_Debugger_Names to SCSIDebug.h.
	   <SM9>	 5/25/93	DCB		Adding definition of IfDebugStr so we can turn Debugger Traps
									off. Also added
	   <LW8>	 5/20/93	DCB		Adding two fields to the XPT globals to support turning off
									deferred completion routines from inside debuggers.
	   <LW7>	 5/20/93	PW		Adding jump vector for target mode.
	   <SM8>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	   <LW5>	 4/14/93	DCB		Added a copy of the C0C^ SCSIGlobals from the old SCSI Manager.
									We are stealing these since we replace the old SCSI Manager.
	   <LW4>	 3/26/93	PW		Added deferred task record for deferring completion routines.
	   <SM5>	 1/31/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <LW3>	 1/30/93	PW		Added glue code for calling completion routines (saving
									registers that were getting trashed by File Manager).
	   <LW2>	 1/27/93	PW		Changed bogus to syncUnsafeCount.
	   <SM4>	 12/5/92	PW		Added nextInterleave field.
	   <SM3>	11/20/92	PW		Removed Includes and unused fields in BusInfo. Changed MaxBuses
									to 16. Removed hiBusNum and rearranged XPTgs.
	   <SM2>	10/30/92	DCB		Changes to reflect new ACAM.h
		 <1>	 10/8/92	PW		first checked in

*/

#ifndef __XPTPRIV__
#define __XPTPRIV__

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif

#ifndef __SCSISTANDARD__
#include <SCSIStandard.h>
#endif

#ifndef __XPT__
#include "XPT.h"
#endif


/******** BusInfo ********/

struct BusInfo {
	SIMinitInfo	initInfo;
};

typedef struct BusInfo BusInfo;



/****** XPT Globals *********/

#define kMaxBuses 16		// should handle most everyone's needs
#define kNumBusInfos 3

typedef struct  {
	DeviceIdent	DevID;		/* The device ID associated with a particular DRefNum */
	short	DRefNum;	/* The driver associated with this device ID */
	short	unused;		/* Keep everything long aligned */
} RefInfo;

typedef struct  {
	ulong	DrvrCnt;	/* The number of drivers registered with the XPT */
	RefInfo Drvr[];		/* A list of the drivers */
} DrvrList;

typedef struct  {
	BusInfo *	BusInfoPtr[kMaxBuses];	// pointers to BusInfos (handles 99.99965% of cases)
	long		OldSyncWait;
	short		numBuses;
	short		syncUnsafeCount;
	uchar		flags;
	uchar		unusedC2;						// 
	uchar		unusedC0;
	uchar		unusedC1;
	Ptr			debugPatch;						// address of our _DebugUtil Patch
	short		oldIDBusNumber[8];				// one for each SCSI ID
	OldCallStates	oldAPIstate;
	SCSIphase	latestOldCallPhase;
	short		unusedX;
	ushort		nextInterleave;
	SCSI_IO *	xptIOptr;
	ushort		xptIOpbSize;					// size of currently allocated SCSI_IO (for old API)
	ushort		maxIOpbSize;					// size of largest required SCSI_IO (for all SIMs)
	DrvrList *	Drivers;						// A list of drivers
	Ptr			BootStorage;					// used by the boot code
	BusInfo		TopBusInfos[kNumBusInfos];		// start with room for 3 BusInfo elements
	DeferredTask	completionDT;
} XPTglobals;


// scsXPTprivate is defined in ACAM.h but we'll be more specific for our code
#define savedA5 scsiXPTprivate


//****** For XPTg.flags field ********

#define kbOldAPIBusy	0 
#define kbInOldCall		1

#define kbCSOD			4
#define kbCSODatBoot	5
#define kbCSODatScan	6

#define kbResetFromSync	7

//***** For XPTprivateFlags field *******

#define kbTIB	0 
#define kmTIB	1


/******** SCSIStat word bit equates ********/

#define kmStatATN	0x0200
#define kmStatACK	0x0100

#define kmStatRST	0x0080
#define kmStatBSY	0x0040
#define kmStatREQ	0x0020
#define kmStatMSG	0x0010

#define kmStatC_D	0x0008
#define kmStatI_O	0x0004
#define kmStatSEL	0x0002
#define kmStatDBP	0x0001


/******** Function Prototypes ********/

#define GetXPTg()	(*(XPTglobals **)(*((Ptr *)0xC0C)+0x1B4))

//#pragma parameter __D0	getCurrentA5()			/* move.l	A5, D0 */
//Ptr						getCurrentA5(void)			= {0x2005}; 

long	SCSIAtomic(void);

BusInfo *	GetBusInfo( ushort busID, XPTglobals *XPTg);
void	SetXPTg( XPTglobals *XPTg);
void	SetTempXPTg( XPTglobals *XPTg);
OSErr	SCSITrap( short scsiSelector, SCSI_PB *pbPtr);
void	CheckInterrupts ( XPTglobals *XPTg);
void	Clear( void * where, short len);
void	aack_XPT( ushort val);
OSErr	CallSIMaction( void * pbPtr, XPTglobals * XPTg);
void	GetVirtualIDInfo( SCSIGetVirtualIDInfoPB *pbPtr, XPTglobals *XPTg);
Ptr		getCurrentA5();
void	restoreCurrentA5( Ptr );
Ptr		ciDebuggerPatch( Ptr );
Ptr		ciBusyPatch( Ptr );

void	DispatchISR ( void);
void	Init_SCSIXlate( void);
void	InitXPTAsm( void);
OSErr	NewXPTioPB( ulong pbSize, XPTglobals *XPTg);
void	XlateOldSCSIGlobals( XPTglobals *XPTg);
void	InitSyncWait( XPTglobals *XPTg);
void	InitCompletionStuff( XPTglobals *XPTg);
void	RemoveSyncWait( XPTglobals *XPTg);
void	CallCompRoutineGlue( void *fn, void *ioPtr);
ushort	SetIntsAt2( void);
ushort	InterruptLevel( void);
void	RestoreInts( ushort );
void	InitRecorder( void);

#define SCSIDebugStr(a)  //DebugStr(a)

#define UNIMPTRAP	0x9F
#define	SCSIATOM	0x89

#define SCSIGlobals (*((SCSIGlobalsRec **)0x0C0C))      /* (long) ptr for SCSI mgr locals*/

#define	kbusyPatchVers	'cb'	// WAY WAY important!  If you change the busyPatch code change this value!

// I'm not sure that this belongs here - but here it is. 
// It is here as a reference and to access those
// fields we co-opted.

typedef struct {												// <SM7> \/ 

	// Leftovers from the old SCSI Manager

	ulong			jvReset;		// SCSIReset vector
	ulong			jvGet;			// SCSIGet vector
	ulong			jvSelect;		// SCSISelect vector
	ulong			jvCmd;			// SCSICmd vector
	ulong			jvComplete;		// SCSIComplete vector
	ulong			jvRead;			// SCSIRead vector
	ulong			jvWrite;		// SCSIWrite vector
	ulong			jvInstall;		// SCSI installation vector (for debugging purposes)
	ulong			jvRBlind;		// SCSIRBlind vector
	ulong			jvWBlind;		// SCSIWBlind vector
	ulong			jvStat;			// SCSIStat vector
	ulong			jvSelAtn;		// SCSISelAtn vector
	ulong			jvSMsgIn;		// SCSIMsgIn vector
	ulong			jvSMsgOut;		// SCSIMsgOut vector
	ulong			firstPrivate;	// Ptr to SCSI Mgr private storage record circularly linked list
	ulong			nextPrivate;	// Ptr to next available SCSI Mgr private storage record
	ulong			base5380;		// SCSI read base address
	ulong			pdma5380;		// SCSI pseudo-DMA read base addr
	ulong			hhsk5380;		// SCSI hardware-handshaked read base addr
	ushort			wrOffset;		// write offset relative to "base5380"
	ushort			scsiQFlags;		// flags for SCSI request queue
	ulong			scsiQHead;		// Ptr to head of SCSI request queue
	ulong			scsiQTail;		// Ptr to tail of SCSI request queue
	ulong			activeReq;		// Ptr to currently active SCSI request
	ulong			timeout;		// next timeout should occur at this time
	uchar			G_ID;			// initiator's SCSI ID mask
	uchar			G_State;		// SCSI Mgr state (free/busy)
	ushort			G_Async;		// unused - $62
	ulong			G_Reserved0;	// box number in high byte. HW flags in low bytes 
	ulong			G_Reserved1;	// used for storing timer value
	ulong			G_Reserved2;		// machine-specific storage

// Cool stuff for the new SCSI Manager
	
	Ptr				unused0; 			// 70:

	Ptr				berr_halg0;			// 74: Saved HAL globals for internal bus (used by the Bus Error Handler)
	Ptr				berr_halg1;			// 78: Ditto for external bus. (I know, its a hack but justifiable because
										// we are the only ones with xfer routines that cause bus errors.)
	ulong			jvUnusedXL1;		// 7c: jv called when we're selected as target

	uchar			numBEHs;			// 80: Number of Bus Error Handlers installed
	uchar			inDebugger;			// 81:
	uchar			unused1[2];			// 82:

	XPTglobals	*	tempXPTGGlobals;	// 84: Used for "transitioning" from one XPT to another	<SM8>
	ulong			tempXPTGInUse;		// 88: Set to 'xptg' if we have two XPTs active			<SM8>

	ulong			unused2; 			// 8c:

	ulong			recordBreak0;		// 90: gets checked for match against all events recorded
	ulong			recordBreak4;		// 94:

	ulong			busyPatch;			// 98:
	uchar			ciBusyPending;		// 9c: Used by the ciSCSIBusy patch to keep track of deferred jvSCSIFreeHook Calls
	uchar			unused3;			// 9d: 
	ushort			busyPatchVers;		// 9e:

	ulong			recCurrent;			// a0: debugging event recorder - current pointer
	ulong			recSize;			// a4: debugging event recorder - size of buffer
	ulong			recStartLog;		// a8: logical start of buffer
	ulong			recStartPhys;		// ac: physical start of buffer

	ushort			newBusyPatchVers;	//  
	ushort			completionQHdr;		// b2: high byte = flag indicating deferred task is enqd
	ulong			completionQHead;	// b4: Q used to call completion routines from our
	ulong			completionQTail;	// b8:	deferred task (XPT.a).

// ÑÑÑÊOLD ÑÑÑ

	ushort			unusedW2;			//
	QHdr			privDTQueue;		// used for the private deferred task manager
	Ptr				oldjDisptch;		// the old jDisptch vector we patched out
	ulong			ci_jDisptchVers;	// version tag for our patch

	ulong			jvVFWO;				//  virtual fast writes	(hhsk)
	ulong			jvCSO;				//  virtual slow compare	("p" bit redefined to mean "compare")
	ulong			jvUnused3;			//  unused
	ulong			jvCFO;				//  virtual fast compare	("p" bit redefined to mean "compare")
	ulong			jvUnused4;			//  unused
	ulong			jvInvalidIn;		//  Invalid Message In
	ulong			jvIdentifyIn;		//  Identify Message In
	ulong			jvCmdComplete;		//  Command Complete
	ulong			jvExtendedMsg;		//  Extended Message
	ulong			jvSaveDataPtr;		//  Save Data Pointer
	ulong			jvRestorePtrs;		//  Restore Pointers
	ulong			jvDisconnect;		//  Disconnect
	ulong			jvMsgRejIn;			//  Message Reject In
	ulong			jvLCCF;				//  Linked Command Complete with (or without) flag
	ulong			sdmStack;			//  SCSIDiskMode stack global for DB Lite 
	ulong			base5380_1;			//  SCSI read base address (internal)
	ulong			pdma5380_1;			//  SCSI pseudo-DMA read base addr (internal)	
	ulong			hhsk5380_1;			//  SCSI hardware-handshaked read base addr (internal)
	ulong			base5380_2;			//  SCSI read base address (external)
	ulong			pdma5380_2;			//  SCSI pseudo-DMA read base addr (external)
	ulong			hhsk5380_2;			//  SCSI hardware-handshaked read base addr (external)
	ulong			jvIdentifyOut;		//  Identify Message Out
	ulong			jvMsgRejOut;		//  Message Reject Out
	ulong			jvInvalidOut;		//  Invalid Message Out
	ulong			jvKillIO;			//  Kill I/O
	ulong			jvNoOp;				//  No Operation
	ulong			jvBusDevRstOut;		//  Bus Device Reset Out								<v1.3>
	ulong			G_SCSIDREQ;			//  SCSI DREQ base address
	ulong			G_TargetID;			//  Target ID	
	ulong			G_FakeStat;			//  Fake state
	ulong			G_OldTrapAdrs;		//  contains the old SCSIMgr address
	ulong			G_OldIntHnd;		//  contains old intrp level 2 handler
	ulong			G_IntrpCount;		//  counts total # of intrps
	ulong			G_IntrpStat;		//  Status read by Intrp routine
	ulong			GxState96;			//  Bits to make c96 backwards compatible
	ulong			BootCfgFlags;		//  copy of d2 passed to InitHW_SCSI96 at boot (used by jvInitHW) 
	uchar			G_bitDREQ;			//  Bit position at DREQ location
	uchar			jvUnused32;			//  Future expansion
	ushort			jvUnused33;			//  Future expansion
	ulong			jvIntHnd;			//  24-entry jump table -- interrupt handler
	ulong			jvMessage;			//  Send a message to the deferred task
	ulong			jvClearIRQ;			//  Clear the SCSI interrupt (and VIA, if necessary)
	ulong			jvDisEnable;		//  Enable/disable interrupts routine
	ulong			jvLogError;			//  Record error for the PB
	ulong			jvSCSIDT;			//  Deferred Task for all other interrupts
	ulong			jvFind;				//  Find a request to process
	ulong			jvSetup;			//  Setup active request
	ulong			jvPreflight;		//  Preflight the parameter block
	ulong			jvEnDequeue;		//  Enqueue/dequeue a parameter block
	ulong			jvArb;				//  Arbitrate for the SCSI bus
	ulong			jvSel;				//  Select a SCSI device
	ulong			jvDelay22;			//  Delay 2.2 microseconds
	ulong			jvClearState;		//  Remove the current request
	ulong			jvTransfer;			//  Transfer data using the primitive routines
	ulong			jvSetTimer;			//  Set the timer
	ulong			jvResetBus;			//  Reset SCSI bus and kill all requests
	ulong			jvClearBus;			//  Clear the SCSI bus
	ulong			jvBusErr;			//  Bus error handler
	ulong			jvDataDMA;			//  DMA-related data-chaining interpreter

// ÑÑÑÊNEW ÑÑÑ
	ulong			xptGlobals;			// 1b4: pointer to Cousin Itt's XPT globals 

// ÑÑÑÊOLD ÑÑÑ
	ulong			blindBusTO;			// 1b8: number of ticks to wait for blind transfer bytes (after 1st byte)
	ushort			transferType;		// 1bc: Type of data transfer to perform (used in Transfer_96, BusError)
	uchar			lastINTread;		// 1be: Value of rINT at last valid interrupt read
	uchar			lastSTAread;		// 1bf: Value of rSTA at last valid interrupt read
// ÑÑÑÊNEW and OLD ÑÑÑ
	ulong			yeOldeBusErrVct;	// 1c0: temp storage while we insert our buserr handler 	<T10> pdw
	ulong			base539x0;			// 1c4: 539x base address, bus0								<T3><T4>
	ulong			base539x1;			// 1c8: 539x base address, bus1								<T3><T4>
	uchar			G_SCSIDevMap0;		// 1cc: Device Map for the Internal SCSI Bus					<T3>
	uchar			fill1[3];
	uchar			G_SCSIDevMap1;		// 1d0: Device Map for the External SCSI Bus					<T3>
	uchar			fill2[3];
	
} SCSIGlobalsRec;


#define tempXPT 	'xptg'			// value for tempXPTGInUse


#endif //__XPTPRIV__