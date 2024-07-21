/*
	File:		HALc96.h

	Contains:	header stuff for 53c96 HBAs (Quadras)

	Notes:		

	Written by:	Paul Wolf

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SM20>	  2/1/94	DCB		Added using601Emulator field to the hardware info record.
	  <SM19>	11/22/93	pdw		Rolling in from <MCxx>.
	  <SM18>	11/19/93	chp		Add IRQ primitive vectors to the HBADesc_53c9x structure.
	  <SMG3>	 9/29/93	chp		Add HAL fields to the HAL globals to represent a DB-DMA channel
									command list buffer, with both logical and physical addresses.
									Include a prerequisite header file. Add prototypes for Grand
									Central initialization routines. Make a simple name change since
									GrandCentral is so long.
	  <SMG2>	 9/22/93	chp		Add Grand Central support.
	  <SM16>	10/29/93	DCB		<MC> rollins.
	  <SM15>	10/14/93	pdw		<MC> roll-in.
	   <MC2>	10/12/93	pdw		Added support for Synchronous data transfers, rewrote State
									Machine, message handling etc.
	  <SM14>	 9/12/93	pdw		Prototype maintenance.
	  <SM13>	 7/20/93	pdw		Added intIRQbitNum and changed intDREQbitNum to a uchar.
	  <SM12>	 7/17/93	pdw		Lots of little things.
	  <SM11>	  7/8/93	pdw		Changed types of some pointers in HALc96Globals.
	  <SM10>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
									stack switching mechanism.  Adding support for Cold Fusion.
									Rearranging HW/SW Init code. Some code optimizations.
	   <SM9>	 5/25/93	DCB		Rollin from Ludwig. (The next item below)
	   <LW8>	 5/21/93	PW		Adding PRAM selectable Initiator ID stuff.
	   <SM8>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	   <SM7>	  4/8/93	DCB		Adding pdmaTypeBIOS type to the dma type enum.
	   <LW7>	 4/30/93	DCB		Make DoHalInfo a separate function so it can be stuffed into a
									vector.
	   <LW5>	 4/14/93	DCB		Synced up with SuperMario
	   <LW4>	 3/26/93	PW		Changed the hasPSC stuff to more generic dmaType and changed
									dreqIn32bit to dreqNeedsSwapMMU.
	   <LW3>	 2/17/93	PW		Began to add dual-interrupt support for Quadras.
	   <SM6>	 3/20/93	PW		Began to add dual-interrupt support for Quadras.
	   <SM5>	 1/31/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <LW2>	 1/27/93	PW		Added HALIntPoll routine to prototypes.
	   <SM4>	11/20/92	DCB		Removed several includes to fix makefile dependency problems
	   <SM3>	 10/8/92	PW		Realigned some fields.  See HALc96equ.a for more details.
	   <SM2>	 7/28/92	PW		Resolved differences in sources.
	   <SM1>	 7/26/92	PW		Initial check-in.

*/

#ifndef __HALC96__
#define __HALC96__

#ifndef __SIMCORE__
#include "SIMCore.h"
#endif


typedef struct 
{
	Ptr			baseRegAddr;			// base addr of c9x registers (offset of $10 between regs
	Ptr			pdmaAddr;				// addr of Pseudo-dma access

	Ptr			pdmaNonSerlzdAddr;		// addr of Pseudo-dma in non-serialized space access
	Ptr			dreqAddr;				// addr of DAFB register with DREQ bit

	Ptr			intEnableSCSIAddr;		// addr of control register for SCSI interrupt
	Ptr			intFlagSCSIAddr;		// addr of status register for SCSI interrupt

	Ptr			dafbAddr;				// addr of DAFB that needs initialization
	Ptr			hbaUnusedL1;			// addr of 

	Ptr			dmaCntrlAddr;			// addr of true DMA control register(s)
	Ptr			dmaBaseAddr;			// addr of true DMA base register(s)

	void		(*jvClearSCSIIRQ) (void);	// hardware-specific primitive routine
	void		(*jvEnableSCSIIRQ) (void);	// hardware-specific primitive routine
	void		(*jvDisableSCSIIRQ) (void);	// hardware-specific primitive routine
	void		(*jvTestSCSIIE) (void);		// hardware-specific primitive routine

	Boolean		dreqNeedsSwapMMU;		// set if dreq status bit is in 32-bit space
	Boolean		HBAisFast;				// set if F9x part capable of Fast Synchronous (10MB/S)
	Boolean		HBAisDiff;				// set if c9x part capable of differential
	Boolean		usesThreshold8;			// 
	Boolean		needsDAFBinit;			// set if there's a DAFB that needs to be inited
	Boolean		using601Emulator;		// set if we are running emulated on a 601
	Boolean		hbaUnusedB2;			// set if 
	Boolean		hbaUnusedB3;			// set if 

	Boolean		HBAhasDMA;				// set if true DMA available
	Boolean		HBAhasPseudoDMA;		// set if Pseudo-DMA available
	Boolean		HBAhasHskPseudoDMA;		// set if handshaked Pseudo-DMA available
	Boolean		dmaCacheCoherent;		// set if DMA is fully cache coherent (no flushing needed)
	Boolean		hbaUnusedB4;			// set if 
	Boolean		hbaUnusedB5;			// set if 
	Boolean		hbaUnusedB6;			// set if 
	uchar		initiatorID;			// ID of Macintosh (Initiator) on this bus <LW8>

	uchar		testIRQenableValue;		// value to test SCSI IRQ enable
	uchar		enableIRQvalue;			// value to write to enable SCSI IRQ
	uchar		disableIRQvalue;		// value to write to disable SCSI IRQ
	uchar		clearIRQvalue;			// value to write to clear SCSI IRQ
	uchar		intIRQbitNum;			// bit to test for IRQ
	uchar		intDREQbitNum;			// bit to test for DREQ
	uchar		hbaUnusedC1;
	uchar		hbaUnusedC2;
	
	uchar		intTypeSCSI;			// type of interrupt control (shared VIA bit, etc.) 
	uchar		intSensSCSI;			// type of sensitivity (LEVEL, EDGE, STICKYBIT)
	uchar		intTypeDMA;				// type of interrupt control (shared VIA bit, etc.) 
	uchar		intSensDMA;				// type of sensitivity (LEVEL, EDGE, STICKYBIT)
	uchar		dmaType;				// type of programming model for DMA (PSC, AMIC,É)
	uchar		dmaAlignmentSize;		// alignment requirements (i.e. 8, 16 etc)
	uchar		hbaUnusedC4;			// 
	uchar		hbaUnusedC5;

	ushort		intOSNumberSCSI;		// OS registration number for the SCSI interrupt
	ushort		intOSNumberDMA;			// OS registration number for the DMA interrupt 
	ushort		hbaUnusedS1;
	ushort		hbaUnusedS2;
} HBADesc_53c9x;

enum {
	dmaTypeNone	=	0,
	dmaTypePSC	=	1,
	dmaTypeAMIC	=	2,
	pdmaTypeBIOS =	3,
	dmaTypeGC	=	4,
	 dmaTypeLimit
};

//----- Incomplete HAL globals ----- (the rest are in HALc96equ.a)

typedef struct  {
// Static description of bus
	HBADesc_53c9x	hwDesc;					// hwDesc: copy is made of structure that's passed in

	void *			SIMstaticPtr;			// ptr to SIM's globals (for SSM callbacks)
	void			(*XPT_ISRptr)();		// ptr to XPT's ISR, so we can install it
	void			(*unusedRPtr)();		// ptr to 
	void			(*ReconnectISRptr)();	// ptr to SIM's Reconnect ISR for us to call

	ushort			busID;					// bus ID of this HAL's bus
	ushort			rsrvdS2;				//									<SM3> pdw
	Ptr				cclPhysicalAddr;		// addr of DB-DMA channel command list buffer (physical)
	Ptr				cclLogicalAddr;			// addr of DB-DMA channel command list buffer (logical)
	Ptr				physicalCopyBuffer;		// physical address of locked/noncachable copy buffer
	Ptr				logicalCopyBuffer;		// logical address of copy buffer to DMA into/out of
	void *			otherHALg;				// other HAL's globals

	Ptr				privStackTop;			// top of our private stack		
	ulong			minDMAsize;				// transfer size crossover between polled and DMA
	long			supported_scFlags;
	short			supported_scIOFlags;
	short			supported_scDataTypes;

	ulong			unusedCA1[4];
	
} HALc96Globals;

enum {
	SHARED_VIA = 0,
	INDEPENDENT_VIA = 1,
	SECOND_SHARED_VIA = 2,
	GRAND_CENTRAL = 3
};

enum {
	EDGE		= 0,
	LEVEL		= 1,		// no clear necessary
	STICKBIT	= 2
};

/****** External Prototypes ********/

long	GetHalInfo( HALc96Globals *HALg, SCSIBusInquiryPB *infoPB );
Boolean	DoWeHaveFastSCSI( void * hwAddr);


/****** Function Prototypes For Inter-HAL *******/

// HALc96.c
long	HALinit( HALinitInfo * HALinfoPtr);
void *	Init53c9xSW( HBADesc_53c9x *hwDescPtr);
void *	ReInitHAL( HBADesc_53c9x *hwDescPtr, ushort busID);

// HALc96HWInit.a
long	Init53c9xHW( HBADesc_53c9x *hwDescPtr);

// HALc96.a
extern	long	SizeOfGlobals( void);					// HALc96.a
extern	long	HAL_SingleISR( HALc96Globals *HALg);		// HALc96Routines.a
extern	long	HAL_DualISR( HALc96Globals *HALg);		// HALc96Routines.a
extern	long	HALIntPoll( HALc96Globals *HALg);		// HALc96Routines.a
extern	void	Initc96Asm( HALc96Globals * HALg);		// HALc96.a
extern	void	HALaction( HALactionPB * halPBptr);		// HALc96.a
extern	void	HALResetBus( HALc96Globals * HALg);		// HALc96.a
extern	void	HALSyncConfig( long, long, HALc96Globals * HALg);		// HALc96.a
extern	void	HALAssertATN( HALc96Globals * HALg);		// HALc96.a
extern	void	HALTeardownIO( SIM_IO * ioPtr, uchar * HALg);	// HALc96.a
extern	void	HandleSelected( void);					// HALc96.a
extern	void	ReadInitiatorID( HBADesc_53c9x *hwDescPtr);	// HALc96.a
extern	uchar	GetInitiatorID( HBADesc_53c9x *hwDescPtr);	// HALc96.a

// HALc96PSC.c, HALc96AMIC.c, HALc96GC.c, etc.
OSErr	InitSW_PSC( HALc96Globals *HALg);
OSErr	InitHW_PSC( HALc96Globals *HALg);
OSErr	InitSW_AMIC( HALc96Globals *HALg);
OSErr	InitHW_AMIC( HALc96Globals *HALg);
OSErr	InitSW_GC( HALc96Globals *HALg);
OSErr	InitHW_GC( HALc96Globals *HALg);

// HALc96Routines.a
extern	void	ClearVIASCSIIRQ (void);
extern	void	EnableVIASCSIIRQ (void);
extern	void	DisableVIASCSIIRQ (void);
extern	void	TestVIASCSIIE (void);

// HALc96GC.a
extern	void	ClearGCSCSI0IRQ (void);
extern	void	ClearGCSCSI1IRQ (void);
extern	void	EnableGCSCSI0IRQ (void);
extern	void	EnableGCSCSI1IRQ (void);
extern	void	DisableGCSCSI0IRQ (void);
extern	void	DisableGCSCSI1IRQ (void);
extern	void	TestGCSCSI0IE (void);
extern	void	TestGCSCSI1IE (void);


#endif __HALC96__
