/*
	File:		ATIVideo.h

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1993-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	  1/5/94	kc		Add Function ProtoTypes to prevent compiler warnings.
		 <1>	 11/5/93	fau		first checked in
		 <1>	10/27/93	fau		first checked in
		 <1>	10/19/93	fau		first checked in

*/

/*-------------------------------------------------------------------------
*start
*
*Name:		ATIVideo.h
*Creator:	George D. Wilson Jr.
*Date:		9/30/92
*
*Purpose:	Contains special definitions for the ATI video system.
*
*Category:	Header File
*File:		ATIVideo.h
*
*Detailed:
*
*Note:
*
*History:
*
*	  Date		Programmer					Modification
*	--------	----------		-----------------------------------------
*
*stop
*-----------------------------------------------------------------------*/

//#include "Nub601.h"


#define	kBaseAddress			0x00000000	// Base address of frame buffer for ATI


#define	k1bppEntries			0x01		// Number of CLUT entries for 1 bpp
#define	k2bppEntries			0x03		// Number of CLUT entries for 2 bpp
#define	k4bppEntries			0x0F		// Number of CLUT entries for 4 bpp
#define	k8bppEntries			0xFF		// Number of CLUT entries for 8 bpp
#define	k16bppEntries			0xFF		// Number of CLUT entries for 8 bpp
#define	k24bppEntries			0xFF		// Number of CLUT entries for 8 bpp

#define	kSenseLineShift			0x04		// ATI sense line shift amount

//==========================================================================
//	MMIC monitor values
//==========================================================================

#define	kMMIC15Code				0x01		// MMIC Video reg value for 15"
#define	kMMIC12Code				0x02		// MMIC Video reg value for 12"
#define	kMMIC13Code				0x06		// MMIC Video reg value for 13"
#define	kMMIC16Code				0x09		// MMIC Video reg value for 16"

//==========================================================================
//	Ariel bit depth values
//==========================================================================

#define	kArial1BPPCode				0x01		// MMIC Video reg value for 15"
#define	kArial2BPPCode				0x02		// MMIC Video reg value for 12"
#define	kArial4BPPCode				0x06		// MMIC Video reg value for 13"
#define	kArial8BPPCode				0x09		// MMIC Video reg value for 16"
#define	kArial16BPPCode				0x09		// MMIC Video reg value for 16"

//==========================================================================
//	ATI hardware video defines
//==========================================================================

#define	kDACBaseAddr			0xF9800000					// ACDC address
// #define	kADDCBaseAddr			(kMySuperSlot | kMazdaLowSpeedBase | 0x00400000)
#define	kArielBaseAddr			(kMySuperSlot | 0x00000000)
#define	kMMICBaseAddr			(kMySuperSlot | 0x00000000)

#define	kDACAddrReg				(kArielBaseAddr | 0x18)
#define	kDACDataReg				(kArielBaseAddr | 0x38)
#define	kDACConfigReg			(kArielBaseAddr | 0x58)
#define	kDACTestReg				(kArielBaseAddr | 0x78)

#define	kMMICBaseAddr			0x00000000
#define	kATISenseLineBase		(kMMICBaseAddr )

//==========================================================================
//	ATI Function ProtoTypes
//==========================================================================

void WaitForVBL(void);
OSErr SlamRegisters(UInt8);
