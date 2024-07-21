/*
	File:		AMICPrivEqu.h

	Contains:	HAL private equates for accessing the DMA Controler in PDM (AMIC)

	Written by:	Rich Collyer

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM3>	11/10/93	fau		Update from SuperMunggio <SMG2>.
	  <SMG2>	 9/29/93	chp		Removed typedefs for unsigned types.
	   <SM2>	 4/30/93	RC		Major changes due to changes in B4 version of high level driver
									and due to new hardware.
	   <SM1>	  3/4/93	RC		first checked in - Duplicate PSC HAL and made changes to work on AMIC (PDM)

*/


#ifndef	__AMICPRIVEQU__
#define	__AMICPRIVEQU__


/* duplicate enough "UniversalEqu" data structures to find the AMIC base address */

enum {
	UnivInfoPtr = 0x0DD8				// low-memory global: type is (ProductInfo **)
};

enum {
	PhysBase = 0x61000000
};


struct ProductInfo {
	long	decoderInfoPtr;				// offset to address decoder info
	// there are several more fields here that are not interesting in this context
};
typedef struct ProductInfo ProductInfo;


struct DecoderInfo {
	void	*reserved [2];				// 2 base addresses precede the VIA1 in DecoderInfo
	char	*VIA1Addr;
	void	*reserved1 [33];				// 32 base addresses precede the AMIC in DecoderInfo
	void	*AMICAddr;
};
typedef struct DecoderInfo DecoderInfo;



/* AMIC register offsets and structures */
enum AMICChannel{
	AMIC_SCC		=	0x1080,		// offset to DMA SCC
	
	AMIC_SCCTxA		=	0x00,		// offset to DMA SCC port A Transmit Buffer Address Register
	AMIC_SCCRxA		=	0x10,		// offset to DMA SCC port A Transmit Buffer Address Register
	AMIC_SCCTxB		=	0x20,		// offset to DMA SCC port A Transmit Buffer Address Register
	AMIC_SCCRxB		=	0x30,		// offset to DMA SCC port A Transmit Buffer Address Register

	AMIC_Count		=	0x04,		// offset to Count register off of Addr Reg
	AMIC_Cmd		=	0x08,		// offset to Command register off of Addr Reg
	
	AMIC_TopOfBuf	=	0x2000		// DMA buffers for Serial are 8K big
};
typedef enum AMICChannel AMICChannel;


enum {
	// DMA channel SCC Control register bit offsets
	RST			= 0,
	RUN			= 1,
	CONT		= 2,
	IE			= 3,
	PAUSE		= 4,
	FROZEN		= 5,
	RELOAD		= 6,
	IF			= 7
};


struct AMICDMASet {
	void	*addr;
	ushort	*cnt;
	ushort	reserved;
	char	*cmdStat;
};
typedef struct AMICDMASet AMICDMASet;


struct AMICTailSet {
	void	*addrPhys;
	void	*addrLog;
};
typedef struct AMICTailSet AMICTailSet;

#endif __AMICPRIVEQU__
