/*
	File:		DBDMA.h

	Contains:	public headers defining the Descriptor Based DMA standard

	Written by:	Craig Prouse

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	12/13/93	chp		Add TStat encodings.
		 <1>	11/10/93	fau		first checked in
	  <SMG3>	10/26/93	chp		Checking in the first “complete” version.
	  <SMG2>	 9/29/93	chp		Add channel control bits and channel commands. Prepare for
									littleEndian support by default.

*/

#ifndef __DBDMA__
#define __DBDMA__

#ifndef __M68K__
#include	<M68K.h>
#endif

#ifndef __ENDIANAWARE__
#include	<EndianAware.h>
#endif


// This structure defines the standard set of DB-DMA channel registers.

struct DBDMAChannelRegisters {
	unsigned long	channelControl;
	unsigned long	channelStatus;
	unsigned long	commandPtrHi;			// implementation optional
	unsigned long	commandPtrLo;
	unsigned long	dataPtrHi;				// implementation optional
	unsigned long	dataPtrLo;
	unsigned long	byteCount;

	unsigned long	reserved1;
	unsigned long	data2PtrHi;				// implementation optional
	unsigned long	data2PtrLo;				// implementation optional
	unsigned long	transferModes;			// implementation optional
	unsigned long	addressHi;				// implementation optional
	unsigned long	reserved2 [4];
	unsigned long	unimplemented [16];

	// This structure must remain fully padded to 256 bytes.
	unsigned long	undefined [32];
};
typedef struct DBDMAChannelRegisters DBDMAChannelRegisters;


// These constants define the DB-DMA channel control words and status flags.

enum {
	kdbdmaSetRun	= 0x80008000,
	kdbdmaClrRun	= 0x80000000,
	kdbdmaSetPause	= 0x40004000,
	kdbdmaClrPause	= 0x40000000,

	kdbdmaClrHalted	= 0x20000000,
	kdbdmaClrDead	= 0x10000000,
	kdbdmaSetActive	= 0x08000800,

	kdbdmaSetS3		= 0x00080008,
	kdbdmaClrS3		= 0x00080000,
	kdbdmaSetS2		= 0x00040004,
	kdbdmaClrS2		= 0x00040000,
	kdbdmaSetS1		= 0x00020002,
	kdbdmaClrS1		= 0x00020000,
	kdbdmaSetS0		= 0x00010001,
	kdbdmaClrS0		= 0x00010000,

	kdbdmaClrAll	= 0xF00F0000,

	kdbdmaHalted	= 0x2000,
	kdbdmaDead		= 0x1000,
	kdbdmaActive	= 0x0800,
	kdbdmaPaused	= 0x0400,

	kTStatMore		= 0x0000,
	kTStatDone		= 0x0100,
	kTStatDiff		= 0x0200,
	kTStatError		= 0x0300,
	kdbdmaTStatMask	= 0x0300,

	kdbdmaS3		= 0x0008,
	kdbdmaS2		= 0x0004,
	kdbdmaS1		= 0x0002,
	kdbdmaS0		= 0x0001
};


// This structure defines the DB-DMA channel command descriptor.

// *** WARNING:	Endian-ness issues must be considered when performing load/store! ***
// ***			DB-DMA specifies memory organization as quadlets so it is not correct
// ***			to think of either the operation or result field as two 16-bit fields.
// ***			This would have undesirable effects on the byte ordering within their
// ***			respective quadlets.

struct DBDMADescriptor {
	unsigned long	operation;					// MSW = command, LSW = reqCount
	unsigned long	address;
	unsigned long	data32;
	unsigned long	result;						// MSW = xferStatus, LSW = resCount
};
typedef struct DBDMADescriptor DBDMADescriptor, *DBDMADescriptorPtr;


// These constants define the DB-DMA channel command operations and modifiers.

enum {
	// Command.cmd operations
	OUTPUT_MORE			= 0x0000,
	OUTPUT_LAST			= 0x0100,
	INPUT_MORE			= 0x0200,
	INPUT_LAST			= 0x0300,
	STORE_QUAD			= 0x0400,
	LOAD_QUAD			= 0x0500,
	JUMP				= 0x0600,
	WAIT				= 0x0700,
	STOP				= 0x0800,
	kdbdmaCmdMask		= 0x0F00,

	// Command.test modifiers (choose all that apply)
	kTestMore			= 0x1000,
	kTestDone			= 0x2000,
	kTestDiff			= 0x4000,
	kTestError			= 0x8000,
	kdbdmaTestMask		= 0xF000,

	// Command.i modifiers (choose one)
	kIntError			= 0x0000,				// default modifier
	kIntErrorDiff		= 0x0040,
	kIntErrorDiffDone	= 0x0080,
	kIntAll				= 0x00C0,
	kdbdmaIMask			= 0x00C0,

	// Command.h modifiers (choose one)
	kHaltError			= 0x0000,				// default modifier
	kHaltErrorDiff		= 0x0010,
	kHaltErrorDiffDone	= 0x0020,
	kHaltNone			= 0x0030,
	kdbdmaHMask			= 0x0030,

	// Command.cdep.key modifiers (choose one for INPUT, OUTPUT, LOAD, and STORE operations)
	KEY_STREAM0			= 0x0000,				// default modifier
	KEY_STREAM1			= 0x0001,
	KEY_STREAM2			= 0x0002,
	KEY_STREAM3			= 0x0003,
	KEY_REGS			= 0x0005,
	KEY_SYSTEM			= 0x0006,
	KEY_DEVICE			= 0x0007,
	kdbdmaKeyMask		= 0x0007,

	// Command.cdep.cond modifiers (choose all that apply for JUMP and WAIT operations)
	kFailZerosFailOnes	= 0x0001,
	kFailZerosPassOnes	= 0x0002,
	kPassZerosFailOnes	= 0x0004,
	kPassZerosPassOnes	= 0x0008,
	kdbdmaCondMask		= 0x000F
};


//	void MakeCCDescriptor (DBDMADescriptor *descPtr, unsigned short cmd,
//		unsigned short count, unsigned long addr);
#define MakeCCDescriptor(descPtr,cmd,count,addr)												\
	((descPtr)->result = 0,																		\
	(descPtr)->data32 = 0,																		\
	(descPtr)->address = EndianSwap32(addr),													\
	NOP(),																						\
	(descPtr)->operation = EndianSwap32((cmd) << 16 | ((count) & 0x0000FFFF)),					\
	NOP())

//	void MakeData32CCDescriptor (DBDMADescriptor *descPtr, unsigned short cmd,
//		unsigned short count, unsigned long addr, unsigned long data);
#define MakeData32CCDescriptor(descPtr,cmd,count,addr,data)										\
	((descPtr)->result = 0,																		\
	(descPtr)->data32 = EndianSwap32(data),														\
	(descPtr)->address = EndianSwap32(addr),													\
	NOP(),																						\
	(descPtr)->operation = EndianSwap32((cmd) << 16 | ((count) & 0x0000FFFF)),					\
	NOP())

//	unsigned short GetCCCmd (DBDMADescriptor *descPtr)
#define GetCCCmd(descPtr)																		\
	((unsigned short) (EndianSwap32((descPtr)->operation) >> 16))

//	unsigned short GetCCReqCount (DBDMADescriptor *descPtr)
#define GetCCReqCount(descPtr)																	\
	((unsigned short) (EndianSwap32((descPtr)->operation)  & 0x0000FFFF))

//	unsigned long GetCCAddress (DBDMADescriptor *descPtr);
#define GetCCAddress(descPtr)																	\
	(EndianSwap32((descPtr)->address))

//	unsigned long GetCCData32 (DBDMADescriptor *descPtr);
#define GetCCData32(descPtr)																	\
	(EndianSwap32((descPtr)->data32))

//	unsigned short GetCCXferStatus (DBDMADescriptor *descPtr);
#define GetCCXferStatus(descPtr)																\
	((unsigned short) (EndianSwap32((descPtr)->result) >> 16))

//	unsigned short GetCCResCount (DBDMADescriptor *descPtr);
#define GetCCResCount(descPtr)																	\
	((unsigned short) (EndianSwap32((descPtr)->result)  & 0x0000FFFF))

//	void SetChannelControl (DBDMAChannelRegisters *registerSetPtr, unsigned long ctlValue);
#define SetChannelControl(registerSetPtr, ctlValue)												\
	((registerSetPtr)->channelControl = EndianSwap32(ctlValue), NOP())

//	unsigned long GetChannelStatus (DBDMAChannelRegisters *registerSetPtr);
#define GetChannelStatus(registerSetPtr)														\
	(EndianSwap32((registerSetPtr)->channelStatus))

//	unsigned long GetCommandPtr (DBDMAChannelRegisters *registerSetPtr);
#define GetCommandPtr(registerSetPtr)															\
	(EndianSwap32((registerSetPtr)->commandPtrLo))

//	void SetCommandPtr (DBDMAChannelRegisters *registerSetPtr, unsigned long cclPtr);
#define SetCommandPtr(registerSetPtr,cclPtr)													\
	((registerSetPtr)->commandPtrLo = EndianSwap32(cclPtr), NOP())


#endif __DBDMA__
