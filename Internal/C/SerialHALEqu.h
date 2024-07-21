/*
	File:		SerialHALEqu.h

	Contains:	Serial Hardware Abstraction Layer equates

				The contents of this file are common to all serial hardware abstraction layers,
				whether they support a generic SCC, SCC with DMA, a dedicated I/O processor,
				or whatever architecture. For this reason, types and constants defined here
				may be freely used by any HAL, and by high level serial drivers as well. In
				fact, this file represents the interface between a high level driver and the
				HAL layer.

	Written by:	Craig Prouse

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	  <SM16>	11/10/93	fau		Update from SuperMunggio <SMG2>.
	  <SMG2>	 9/29/93	chp		Removed typedefs for unsigned types.
	  <SM15>	 5/27/93	chp		SuperMario = Ludwig FC1
	  <LW10>	 5/18/93	chp		Add selector halSyncRxHandshake. This makes the existing
									CheckRxHandshake function accessible to the driver.
	   <LW9>	 4/13/93	chp		Add flushFrequency variable to receive buffer descriptor.
	   <LW8>	 4/11/93	chp		Defined new IDs for the various types of HAL.
	   <LW7>	 3/26/93	chp		Clean up parameter block interface. Add comments.
	   <LW6>	  3/3/93	chp		Eliminated the cumbersome, confusing, and complicated
									TransmitBlock structure and designed a simpler interface for the
									HAL.
	   <LW5>	 1/21/93	chp		Added halTxCancel selector.
	   <LW4>	 1/13/93	chp		The parity error replacement character and its alternate are now
									stored in the CircularBuffer data structure.
	   <LW3>	  1/7/93	chp		Removed halError selector since special conditions are no longer
									handled by callback from the driver. Removed SpecialCondition
									codes since they are defined by other names in Serial.h.
	   <LW2>	12/29/92	chp		Added halSyncTxHandshake selector, which allows the driver
									client to update the HAL with respect to manual changes in the
									transmit handshaking status. Extended the CircularBuffer data
									structure to encapsulate handshaking thresholds.
	———————————————————————————————————————————————————————————————————————————————————————
							Pre-Ludwig ROM comments begin here.
	———————————————————————————————————————————————————————————————————————————————————————
	  <SM11>	 12/8/92	chp		ClkConfig struct extended to support a “direct” flag which
									effectively suppresses use of programmable baud rate generation.
									It specifies that the hardware clock pins are to be used
									directly as transmitter/receiver clocks.
	  <SM10>	 12/4/92	chp		HAL interface redefined (again); it is now essentially a
									register-based OS trap. An inline interface routine is provided.
									The ReceiveBlock structure has been eliminated in favor of a
									simple receive model. References to Mazda removed and references
									to AMIC added.
	   <SM9>	10/30/92	chp		HAL prototype made Pascal.
	   <SM8>	 10/8/92	chp		More additions to SHALParamBlock (to be cleaned up later) and
									removal of handshaking flags from TransmitBlock structure.
	   <SM7>	  9/8/92	chp		Added predefined constants for various flavors of HAL. These
									should correspond to ‘shal’ resource IDs.
	   <SM6>	 8/28/92	chp		Added HAL service to disable interrupts on transitions of the
									input handshake line. Added a field to the HAL parameter block
									for specification of an XOn/XOff character.
	   <SM5>	 8/13/92	chp		Discontinue the halRxBlock service. This is now handled
									automatically by the HAL’s primary receive interrupt handler.
	   <SM4>	 7/30/92	chp		Remove an unused field in the TransmitBlock data structure. This
									should have been axed before the last checkin, but the results
									were benign.
	   <SM3>	 7/17/92	chp		Add two new HAL services: halInputStatus and halTxPause. Renamed
									HAL service halSendXOn to halSendXChar since it is intended to
									send either XOn or XOff. Add constants for special receive
									conditions. Add handshaking support to the TransmitBlock data
									structure. Fix interrupt vector offset names for Ext/Sts
									interrupts and generally clean up the file.
	   <SM2>	  7/1/92	chp		Added external/status codes. Added a configuration variable
									specifying whether port is to be initialized as active or
									inactive.
	   <SM1>	 6/25/92	chp		first checked in
	———————————————————————————————————————————————————————————————————————————————————————
							Pre-SuperMario ROM comments begin here.
	———————————————————————————————————————————————————————————————————————————————————————
		 <7>	 6/20/92	chp		Added equates for three new HAL services. Reviewed and improved
									alignment/padding of data structures. Incorporated interrupt
									vector table equates and data structures as a component of the
									driver/HAL interface.
		 <6>	 6/11/92	chp		Increase sophistication of receive buffer representation. Add
									two new HAL services dealing with receive buffering.
		 <5>	 5/29/92	chp		Evolved concept of TransmitBlock for support of DMA, VM, and MDU
									architectures.
		 <4>	 5/22/92	chp		Add constants and data structures in support of receive.
									Gratuitously change some naming conventions.
		 <3>	 5/12/92	chp		Add types and constants to support data transfer operations in
									the HAL.
		 <2>	  5/4/92	chp		Added fields to clocking options data structure.
		 <1>	 4/29/92	chp		first checked in

*/


#ifndef	__SERIALHALEQU__
#define	__SERIALHALEQU__

#ifndef	__MEMORY__
#include	<Memory.h>
#endif

#ifndef __SERIAL__
#include	<Serial.h>
#endif



/* SHAL constants */

// currently-defined flavors of HAL (corresponding to universal info and Gestalt)
enum {
	SHAL_PSC	= 1,			// Cyclone, Tempest
	SHAL_AMIC	= 2				// PDM
};


// service codes - SHAL supported functions
enum SHALService {
	halGetVarsSize,				// return size of HAL variables for channel

	halConstruct,				// initialize HAL (not including hardware)
	halDestruct,				// undo actions of halConstruct

	halReconfigure,				// use new serial configuration

	halSetHandshakeDescriptor,	// register driver handshake descriptor with HAL
	halSetStatusDescriptor,		// register driver status descriptor with HAL
	halSetRxBuffer,				// register driver receive buffer descriptor with HAL

	halTxBlock,					// send a block of characters
	halTxCancel,				// immediately terminate any asynchronous transmission
	halRxFlush,					// immediately return all available receive characters

	halSetBrkState,				// set or clear break condition on the serial line
	halSetDTRState,				// assert or negate the DTR output on the serial connector
	halSendXChar,				// send the specified character outside the normal data flow
	halChannelReset,			// completely reset the low-level serial hardware

	halSyncTxHandshake,			// synchronize handshaking logic with handshake descriptor
	halSyncRxHandshake			// synchronize handshaking logic with input buffer state
};
typedef enum SHALService SHALService;


// channel codes - SHAL supported I/O channels
enum SHALChannel {
	halChannelA = 0,
	halChannelB = 1
};
typedef enum SHALChannel SHALChannel;


// common types of parity checking
enum Parity {
	parityNone,
	parityEven,
	parityOdd,
	parityMark,								// not supported by Z8530
	paritySpace								// not supported by Z8530
};
typedef enum Parity Parity;



/* SHAL receive buffering and port configuration structures */

// circular buffer descriptor
struct CircularBuffer {
	char		*bufAddr;					// pointer to the input buffer
	ulong		bufSize;					// size of the local input buffer
	ulong		bufIndex;					// index into buffer (for inserts)
	ulong		bufOutdex;					// index into buffer (for removes)
	ulong		loMark;						// buffer fill start threshold
	ulong		hiMark;						// buffer fill stop threshold
	char		peChar;						// parity error replacement character
	char		altChar;					// parity error alternate replacement character
	short		flushFrequency;				// frequency (in ticks) to flush the receive hardware
	long		reserved;					// [pad for alignment]
};
typedef struct CircularBuffer CircularBuffer;


struct ClkConfig {
	Boolean		internal;					// internal clocks are 3.672M and PCLK
	Boolean		primary;					// primary clocks are 3.672M and GPi
	short		multiplier;
	Boolean		direct;						// use hardware clock directly (forced for CTS)
	short		reserved;					// [pad for alignment]
	ulong		extFreq1;
	ulong		extFreq2;
};
typedef struct ClkConfig ClkConfig;


struct ChanConfig {
	ulong				baudRate;
	Fixed				stopBits;
	ClkConfig			clkOpts;
	short				txBits;
	short				rxBits;
	Parity				parity;
	Boolean				portActive;
	Boolean				dtrPreserved;		// used only when portActive == false
};
typedef struct ChanConfig ChanConfig;



/* status conditions */

// external/status condition codes
enum ExternStatus {
	extGPi			= 0x0008,
	extHskI			= 0x0020,
	extBreak		= 0x0080
};
typedef enum ExternStatus ExternStatus;



/* serial HAL prototype and parameter block */

// This parameter block is passed to the Serial
// HAL dispatcher for all Serial HAL services.
struct SHALParamBlock {
	void			*halVars;
	long			halService;

	long			halReply;

	union {
		SHALChannel		channel;			// for halGetVarsSize, halConstruct

		MemoryBlock		txBlock;			// for halTxBlock
		CircularBuffer	*rxBuffer;			// for halSetRxBuffer

		ChanConfig		*config;			// for halReconfigure
		SerShk			*hShake;			// for halSetHandshakeDescriptor
		SerStaRec		*serStat;			// for halSetStatusDescriptor

		Boolean			state;				// for halSetBrkState, halSetDTRState
		char			xChar;				// for halSendXChar

	}				halParam;
};
typedef struct SHALParamBlock SHALParamBlock;


// the prototype of a Serial HAL (SHALParamBlock passed in A0)
typedef OSErr SHAL (void);



/* interrupt vector tables and offsets */

// an interrupt handler takes no formal parameters and returns an OSErr result
typedef OSErr IntHndProc (void), (*IntHndProcPtr) (void);

// Level-2 Secondary Interrupt Vector Table [IM II-198]
typedef IntHndProcPtr SecondaryIntVectTable [];

enum {
	vTxB,
	vESB,
	vRxB,
	vSCB,
	vTxA,
	vESA,
	vRxA,
	vSCA
};

// Level-2 External/Status Interrupt Vector Table [IM II-199]
typedef IntHndProcPtr ESIntVectTable [];

enum {
	vComIntB,
	mouseVInt,
	vComIntA,
	mouseHInt
};



/* HAL interface */

// This should probably be in Traps.h
#define		_AsyncPatch		0xA0BE

enum {
	vAsyncPatch = 0x06F8
};


#pragma parameter __D0 SerialHALDispatch (__A0)
OSErr SerialHALDispatch (SHALParamBlock *halPB) =
{
	0x4EB0, 0x01E1, vAsyncPatch		//		JSR		([vAsyncPatch])
};

#endif __SERIALHALEQU__
