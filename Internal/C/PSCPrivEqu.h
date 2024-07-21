/*
	File:		PSCPrivEqu.h

	Contains:	HAL private equates for accessing the Peripheral Subsystem Controller (PSC)

	Written by:	Craig Prouse

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	  <SM10>	11/10/93	fau		Update from SuperMunggio <SMG2>.
	  <SMG2>	 9/29/93	chp		Removed typedefs for unsigned types.
	   <SM9>	 4/29/93	chp		SuperMario = Ludwig B6
	   <LW5>	 4/13/93	chp		Remove unused fields from PSC_INT_TBL in conjunction with
									changes to PSCEqu.a.
	   <LW4>	 3/16/93	chp		Remove the definition of the PSCIntTbl lomem which has been
									superseded by an equivalent field in ExpandMem.
	   <LW3>	 2/24/93	chp		The TimeStamp structure was correct in <SM6> but the hardware
									was backwards. Fix the structure one last time to reflect the
									format of the UTSC in the final version of the PSC.
	   <LW2>	12/29/92	chp		The TimeStamp structure was not reversed; the code using it was
									reversed. The structure has been restored as it was in <SM5>.
	———————————————————————————————————————————————————————————————————————————————————————
							Pre-Ludwig ROM comments begin here.
	———————————————————————————————————————————————————————————————————————————————————————
	   <SM6>	 12/8/92	chp		The TimeStamp structure was reversed, causing externally clocked
									devices to hang the system.
	   <SM5>	 12/4/92	chp		PSC primitive functions moved here from SerialHALPSC.c. Channel
									direction constants removed.
	   <SM4>	 10/8/92	chp		Added structs and constants for accessing the Universal Time
									Stamp Counter (UTSC).
	   <SM3>	 8/13/92	chp		Support for PSC rev 1 (and all references to such support)
									permanently removed.
	   <SM2>	  7/1/92	chp		Updated change history for SuperMario.
	   <SM1>	 6/25/92	chp		first checked in
	———————————————————————————————————————————————————————————————————————————————————————
							Pre-SuperMario ROM comments begin here.
	———————————————————————————————————————————————————————————————————————————————————————
		 <5>	 6/24/92	chp		Eliminate compile-time conditionals for different PSC versions.
									Update PSC equates for consistency with changes in assembly
									definitions elsewhere.
		 <4>	 6/20/92	chp		Changed enum syntax slightly to satisfy the overly-retentive
									compiler from another famous Cupertino development tool
									provider. (It thinks an enumeration list can’t end with a
									comma.)
		 <3>	 6/11/92	chp		Add a few more PSC constants, including one to support prototype
									versions of the PSC. Use conditionals to permit building PSCHAL
									for various versions of the PSC.
		 <2>	 5/29/92	chp		Reimplemented fragments of the Universal info data structures to
									support base address retrieval using C idioms. Renamed a
									poorly-named data type. Completed implementation of PSC register
									offsets and named bits in control and status registers. Added
									support for multiple inclusion.
		 <1>	 5/12/92	chp		first checked in

*/


#ifndef	__PSCPRIVEQU__
#define	__PSCPRIVEQU__



/* duplicate enough "UniversalEqu" data structures to find the PSC base address */

enum {
	UnivInfoPtr = 0x0DD8				// low-memory global: type is (ProductInfo **)
};


struct ProductInfo {
	long	decoderInfoPtr;				// offset to address decoder info
	// there are several more fields here that are not interesting in this context
};
typedef struct ProductInfo ProductInfo;


struct DecoderInfo {
	void	*reserved [27];				// 27 base addresses precede the PSC in DecoderInfo
	void	*pscAddr;
};
typedef struct DecoderInfo DecoderInfo;



/* PSC Interrupt Handler equates and structures */

struct PSCPrimaryInterruptVector {
	void		(*hndlr) (void);		// address of interrupt handler
	long		parm;					// parameter passed to handler in register A1
};
typedef struct PSCPrimaryInterruptVector PSCPrimaryInterruptVector;


struct PSC_INT_TBL {
	// device level 3 interrupts
	PSCPrimaryInterruptVector	MACE;

	// device level 4 interrupts
	PSCPrimaryInterruptVector	SNDSTAT;
	PSCPrimaryInterruptVector	L4SCCA;
	PSCPrimaryInterruptVector	L4SCCB;

	// device level 5 interrupts
	PSCPrimaryInterruptVector	DSP;
	PSCPrimaryInterruptVector	FRMOVRN;

	// device level 6 interrupts
	PSCPrimaryInterruptVector	L660HZ;
	PSCPrimaryInterruptVector	L6SCCA;
	PSCPrimaryInterruptVector	L6SCCB;

	// DMA channel interrupts (also interrupting at level 4)
	PSCPrimaryInterruptVector	SCSI;
	PSCPrimaryInterruptVector	MACE_RECV;
	PSCPrimaryInterruptVector	MACE_XMIT;
	PSCPrimaryInterruptVector	FDC;
	PSCPrimaryInterruptVector	SCCA;
	PSCPrimaryInterruptVector	SCCB;
	PSCPrimaryInterruptVector	SCCATx;

	// DSP level 2 sound interrupt emulation vector
	PSCPrimaryInterruptVector	DSPL2;
};
typedef struct PSC_INT_TBL PSC_INT_TBL;



/* PSC register offsets and structures */

enum {
	L3IR		= 0x0130,		// offset to Level 3 Interrupt Register
	L3IER		= 0x0134,		// offset to Level 3 Interrupt Enable Register
		MACE	= 0,

	L4IR		= 0x0140,		// offset to Level 4 Interrupt Register
	L4IER		= 0x0144,		// offset to Level 4 Interrupt Enable Register
		SNDSTAT	= 0,
		L4SCCA	= 1,
		L4SCCB	= 2,
		DMA		= 3,

	L5IR		= 0x0150,		// offset to Level 5 Interrupt Register
	L5IER		= 0x0154,		// offset to Level 5 Interrupt Enable Register
		DSP		= 0,
		FRMOVRN	= 1,

	L6IR		= 0x0160,		// offset to Level 6 Interrupt Register
	L6IER		= 0x0164,		// offset to Level 6 Interrupt Enable Register
		L660HZ	= 0,
		L6SCCA	= 1,
		L6SCCB	= 2,

	PSC_UTSC	= 0x0300,		// offset to Universal Time-Stamp Counter (48 of 64 bits)

	PSC_BERRIE	= 0x0800,		// offset to Bus Error Interrupt Enable Register
		BERRIE	= 0,

	PSC_ISR		= 0x0804,		// offset to DMA Interrupt Status Register array

	PSC_CNTRL	= 0x0C00,		// offset to DMA Channel Overall Control Register array

	PSC_SET		= 0x1000		// offset to DMA Channel Register Set array
};


enum PSCChannel {
	// DMA channel numbers
	chanSCSI	= 0,
	chanENetRd	= 1,
	chanENetWr	= 2,
	chanFDC		= 3,
	chanSCCA	= 4,
	chanSCCB	= 5,
	chanSCCATx	= 6
};
typedef enum PSCChannel PSCChannel;


enum {
	// DMA channel CMDSTAT register bit offsets
	SETMASK		= 0xFF,
	IF			= 8,
	DIR			= 9,
	TERMCNT		= 10,
	ENABLED		= 11,
	IE			= 12,

	// DMA channel CNTRL register bit offsets
	CIRQ		= 8,
	DMAFLUSH	= 9,
	PAUSE		= 10,
	SWRESET		= 11,
	CIE			= 12,
	BERR		= 13,
	FROZEN		= 14,

	// VIA-style sense bit offsets
	SENSE7		= 7,			// bit 7 is the sense bit for 8-bit registers
	SENSE15		= 15			// bit 15 is the sense bit for 16-bit registers
};


struct PSCDMACntrl {
	short	cntrl;
	char	reserved [16 - sizeof(short)];										// pad to 16 bytes
};
typedef struct PSCDMACntrl PSCDMACntrl;


struct PSCDMASet {
	void	*addr;
	ulong	cnt;
	short	cmdStat;
	char	reserved [16 - (sizeof(void *) + sizeof(ulong) + sizeof(short))];	// pad to 16 bytes
};
typedef struct PSCDMASet PSCDMASet;


typedef struct TimeStamp {
	ulong	lo;					// low 32 bits of 48-bit UTSC register
	ulong	hi;					// high 16 bits of 48-bit UTSC register (16 MSB read as 0)
};
typedef struct TimeStamp TimeStamp;



/* PSC primitive functions */

#if m68k

#pragma parameter __A0 PSCGetCntrl (__A0, __D0)
short *PSCGetCntrl (void *pscBase, PSCChannel pscChan) =
{
	0xD0FC, PSC_CNTRL,		//		ADDA.W	#PSC_CNTRL,A0
	0xE988,					//		LSL.L	#4,D0
	0xD1C0					//		ADDA.L	D0,A0
};


#pragma parameter __A0 PSCGetSets (__A0, __D0)
PSCDMASet *PSCGetSets (void *pscBase, PSCChannel pscChan) =
{
	0xD0FC, PSC_SET,		//		ADDA.W	#PSC_SET,A0
	0xEB88,					//		LSL.L	#5,D0
	0xD1C0					//		ADDA.L	D0,A0
};

#endif m68k

#endif __PSCPRIVEQU__
