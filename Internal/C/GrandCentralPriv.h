/*
	File:		GrandCentralPriv.h

	Contains:	private headers for use with the Grand Central I/O Controller

	Written by:	Craig Prouse

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	 12/1/93	chp		Add serialization primitives to ensure correct operation of
									interrupt enable/disable/clear macros.
	   <SM1>	11/10/93	fau		first checked in
	  <SMG5>	10/26/93	chp		Slight macro name changes.
	  <SMG4>	 9/29/93	chp		Break out GCHandlerVector as its own data type.
	  <SMG3>	 8/30/93	chp		Add more macros and use nested macro substitution to make the
									macros more readable. Add a reserved field to the dispatch table
									structure to achieve more natural data alignment.
	  <SMG2>	 8/26/93	chp		Add macros for maintaining the Grand Central interrupt dispatch
									table, and for enabling and disabling Grand Central interrupt
									sources.

*/

#ifndef __GRANDCENTRALPRIV__
#define __GRANDCENTRALPRIV__

#ifndef __SYSEQU__
#include	<SysEqu.h>
#endif

#ifndef __M68K__
#include	<M68K.h>
#endif

#ifndef __EXPANDMEMPRIV__
#include	<ExpandMemPriv.h>
#endif


/* Grand Central controller register mappings */

#define gcInterruptEvents	0x00020					/* offset from Grand Central base address */
#define gcInterruptMask		0x00024
#define gcInterruptClear	0x00028
#define	gcInterruptLevels	0x0002C

// Grand Central interrupt flags
//
// Grand Central is a little-endian device. These constants correspond to 680x0 bit positions
// within a 32-bit Grand Central register, adjusted to avoid any need for byte swapping. For
// example, gcifIntMode is the most significant bit of the InterruptMask register, but it
// appears to the 680x0 emulator in bit 7.
enum {
	gcifDmaSCSI0 = 24,								// level 4
	gcifDmaFloppy,									// level 4
	gcifDmaEthTx,									// level 4
	gcifDmaEthRx,									// level 4
	gcifDmaSccATx,									// level 4
	gcifDmaSccARx,									// level 4
	gcifDmaSccBTx,									// level 4
	gcifDmaSccBRx,									// level 4
	gcifDmaAudOut = 16,								// level 4
	gcifDmaAudIn,									// level 4
	gcifDmaSCSI1,									// level 4

	gcifDevSCSI0,									// level 2
	gcifDevSCSI1,									// level 2
	gcifDevMACE,									// level 3
	gcifDevSccA = 23,								// level 4
	gcifDevSccB = 8,								// level 4
	gcifDevAudio,									// level 2
	gcifDevVia,										// level 1
	gcifDevSwim3,									// level 2

	gcifExtNMI,										// level 7

	gcifExtPci0,									// level 2
	gcifExtPci1,									// level 2
	gcifExtSlot0,									// level 2
	gcifExtSlot1 = 0,								// level 2
	gcifExtSlot2,									// level 2
	gcifExtSwatch0,									// level 2
	gcifExtSwatch1,									// level 2
	gcifExtJivi,									// level 2
	gcifExtGotham,									// level 2
	gcifExtSpare,									// level 2

	gcifIntMode,									// valid only in InterruptMask register
	gcifMode1Clear = 7								// valid only in InterruptClear register
};


/* Grand Central DMA channel register mappings (refer to DB-DMA documentation) */

#define kGCDMAChannelRegisterSpace		0x08000		/* offset from Grand Central base address */

// indexes into DB-DMA channel register array
enum {
	gcChannelSCSI0,
	gcChannelFloppy,
	gcChannelEnetTx,
	gcChannelEnetRx,
	gcChannelSCCATx,
	gcChannelSCCARx,
	gcChannelSCCBTx,
	gcChannelSCCBRx,
	gcChannelAudioOut,
	gcChannelAudioIn,
	gcChannelSCSI1
};


/* Grand Central device register mappings (refer to device-specific documentation) */

#define kGCDeviceRegisterSpace			0x10000		/* offset from Grand Central base address */

// indexes into DB-DMA device register array
enum {
	gcDeviceSCSI0,
	gcDeviceMACE,
	gcDeviceV0SCC,									// traditional SCC register mapping
	gcDeviceV1SCC,									// MacRISC SCC register mapping
	gcDeviceAudio,
	gcDeviceSWIM3,
	gcDeviceVIA,									// VIA uses the address space of two devices
	gcDeviceSCSI1 = 0x08,
	gcDeviceEnetPROM,
	gcDeviceGBus1,
	gcDeviceGBus2,
	gcDeviceGBus3,
	gcDeviceGBus4,
	gcDeviceGBus5,
	gcDeviceGBus6
};


/* Grand Central interrupt dispatch table (for 680x0 interrupt emulation only) */

struct GCHandlerVector {
	void 				(*gcVector) (void);
	void *				gcRefCon;
};
typedef struct GCHandlerVector GCHandlerVector;


struct GCInterruptDispatchTable {
	unsigned long		gcBaseAddr;
	unsigned long		reserved;

	GCHandlerVector		handlerVector [32];			// Grand Central has 32 interrupt sources.
};
typedef struct GCInterruptDispatchTable GCInterruptDispatchTable;


// Use this macro to express the Grand Central base address.

#define GCBaseAddr																				\
	(((GCInterruptDispatchTable *) GetExpandMemDMADispatchGlobals())->gcBaseAddr)

// This macro can be used to access an interrupt vector directly; it is intended
// to be used only as a building block for other macros defined below.

#define GCHandler(intSource)																	\
	(((GCInterruptDispatchTable *) GetExpandMemDMADispatchGlobals())->handlerVector[intSource])

// Use this macro to register an interrupt handler and a refCon (passed to the
// handler in register A1) for a Grand Central interrupt source specified by
// its interrupt flag (e.g. gcifDevMACE).

#define GCRegisterHandler(intSource, intHandler, refCon)										\
	(GCHandler(intSource).gcVector = (intHandler),												\
	GCHandler(intSource).gcRefCon = (refCon))

// Use this macro to unregister a Grand Central interrupt handler.

#define GCUnregisterHandler(intSource)															\
	(GCHandler(intSource).gcVector = *(void (**)(void)) BadIntVector,							\
	GCHandler(intSource).gcRefCon = 0)

// Use these macros to enable, disable, and clear Grand Central interrupt sources.

#define GCEnableInterruptSource(intSource)														\
	((*(unsigned long *) (GCBaseAddr + gcInterruptMask)) |= 1 << (intSource), NOP())

#define GCDisableInterruptSource(intSource)														\
	((*(unsigned long *) (GCBaseAddr + gcInterruptMask)) &= ~(1 << (intSource)), NOP())

#define GCClearInterruptSource(intSource)														\
	((*(unsigned long *) (GCBaseAddr + gcInterruptClear)) |= 1 << (intSource), NOP())


#endif __GRANDCENTRALPRIV__
