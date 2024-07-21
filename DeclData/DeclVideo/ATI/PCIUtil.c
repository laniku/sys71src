/*
	File:		PCIUtil.c

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 11/5/93	fau		first checked in
		 <1>	10/27/93	fau		first checked in
		 <1>	10/19/93	fau		first checked in

*/

/*-------------------------------------------------------------------------
*start
*
*Name:		PrimaryInit.c
*Creator:	George D. Wilson Jr.
*Date:		4/23/92
*
*Purpose:	Main interface file for ATI video driver primary init.
*
*Category:	Macintosh driver
*File:		PrimaryInit.c
*
*Exports:	main	-	Main entry point for primary init.
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

/*-------------------------------------------------------------------------
*
*								Includes
*
*-----------------------------------------------------------------------*/

#include		<Types.h>
#include		<Errors.h>
#include		<OSUtils.h>

#include		"ATIStdTypes.h"
#include		"ATI.h"

/*-------------------------------------------------------------------------
*
*							Imported Procedures
*
*-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
*
*					Beginning of Procedure Definitions
*
*-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
*start
*
*Name:		PerformPCIHack
*Creator:	George D. Wilson Jr.
*Date:		9/22/93
*
*Purpose:	Does a read of the CPU ID for the PCI IO problem.
*
*Category:
*File:		PCIUtil.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:		void
*
*Detailed:
*
*Algorithm:
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
void
PerformPCIHack()
{

	UInt8					*ioReg;
	volatile UInt8			dumb;

//	DebugStr("\pPerformPCIHack");
	
	ioReg = (UInt8 *) kCPUIDReg;
	dumb = *ioReg;					// Read CPU ID for PCI hack
	dumb = *ioReg;					// Read CPU ID for PCI hack
	
} /* End of PerformPCIHack */

/*-------------------------------------------------------------------------
*start
*
*Name:		LByteSwap
*Creator:	George D. Wilson Jr.
*Date:		9/13/93
*
*Purpose:	Does bytes swapping for endianess of 32 bits
*
*Category:
*File:		PCIUtil.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:		UInt32
*
*Detailed:
*
*Algorithm:
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
UInt32
LByteSwap(UInt32 theLong)
{

	UInt32		Temp;

//	DebugStr("\pLByteSwap");
	
	Temp = ((theLong & 0x000000ff) << 24);
	Temp += (((theLong >> 8) & 0x000000ff) << 16);
	Temp += (((theLong >> 16) & 0x000000ff) << 8);
	Temp += ((theLong >> 24) & 0x000000ff);
	return(Temp);

} /* End of LByteSwap */

/*-------------------------------------------------------------------------
*start
*
*Name:		WByteSwap
*Creator:	George D. Wilson Jr.
*Date:		9/13/93
*
*Purpose:	Does bytes swapping for endianess of 16 bits
*
*Category:
*File:		PCIUtil.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:		UInt16
*
*Detailed:
*
*Algorithm:
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
UInt16
WByteSwap(UInt16 theWord)
{

	UInt16		Temp;

//	DebugStr("\pWByteSwap");
	
	Temp = ((theWord & 0x00ff) << 8);
	Temp += ((theWord >> 8) & 0x00ff);
	return(Temp);

} /* End of WByteSwap */


/*-------------------------------------------------------------------------
*start
*
*Name:		IOByteWrite
*Creator:	George D. Wilson Jr.
*Date:		9/13/93
*
*Purpose:	Writes a byte to the specified IO register.
*
*Category:
*File:		PCIUtil.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:		void
*
*Detailed:
*
*Algorithm:
*
*Note:
*
*History:
*
*	  Date		Programmer					Modification
*	--------	----------		-----------------------------------------
*	9/22/93		George W.		Added PCI IO hack
*
*stop
*-----------------------------------------------------------------------*/
void
IOByteWrite(UInt32 theReg, UInt8 theByte)
{

	UInt8			*ioReg;

//	DebugStr("\pIOByteWrite");
	
	ioReg = (UInt8 *) theReg;
	*ioReg = theByte;
	
	PerformPCIHack();
	
} /* End of IOByteWrite */

/*-------------------------------------------------------------------------
*start
*
*Name:		IOWordWrite
*Creator:	George D. Wilson Jr.
*Date:		9/13/93
*
*Purpose:	Writes a word to the specified IO register.
*
*Category:
*File:		PCIUtil.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:		void
*
*Detailed:
*
*Algorithm:
*
*Note:
*
*History:
*
*	  Date		Programmer					Modification
*	--------	----------		-----------------------------------------
*	9/22/93		George W.		Added PCI IO hack
*
*stop
*-----------------------------------------------------------------------*/
void
IOWordWrite(UInt32 theReg, UInt16 theWord)
{

	UInt16			*ioReg;

//	DebugStr("\pIOWordWrite");
	
	ioReg = (UInt16 *) theReg;
	*ioReg = WByteSwap(theWord);
	
	PerformPCIHack();


} /* End of IOWordWrite */

void IOLongWrite(unsigned long theReg, unsigned long bogus)
{
	unsigned long			*ioReg;

	ioReg 	= (unsigned long *) theReg;
	*ioReg 	= LByteSwap(bogus);
	
	PerformPCIHack();
}

/*-------------------------------------------------------------------------
*start
*
*Name:		FindPCICard
*Creator:	George D. Wilson Jr.
*Date:		9/13/93
*
*Purpose:	Searches all PCI slots for the ATI graphics card.
*
*Category:
*File:		PCIUtil.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:		UInt8
*
*Detailed:
*
*Algorithm:
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
UInt8
FindPCICard(UInt16 *type)
{
	UInt32			*configRegPtr;
	UInt32			*dataRegPtr;
	UInt32			data;
	UInt32			someValue;

//	DebugStr("\pFindPCICard");

	configRegPtr = (UInt32 *) kConfigAddressReg;
	dataRegPtr = (UInt32 *) kConfigDataReg;

	someValue = kPCIVendorIDOffset | (kSecondPCISlot << 12);
	*configRegPtr = LByteSwap(someValue);			// Tell Bandit which device
	data = LByteSwap(*dataRegPtr);					// Get Vendor ID

	if ( data == (kATIVendorID | (kATIDeviceID << 16)) ) {
		*type = kATIVendorID;
		return(kSecondPCISlot);
	}

	if ( data == (kDiamondVendorID | (kDiamondDeviceID << 16)) ) {
		*type = kDiamondVendorID;
		return(kSecondPCISlot);
	}

	return(0);										// No card found
	
} /* End of FindPCICard */


/*-------------------------------------------------------------------------
*start
*
*Name:		EnableIOAccess
*Creator:	George D. Wilson Jr.
*Date:		9/13/93
*
*Purpose:	Enables or disables PCI IO/Mem access for a specific PCI card.
*
*Category:
*File:		PCIUtil.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:		OSErr
*
*Detailed:
*
*Algorithm:
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
OSErr
EnableIOAccess(UInt8 devID, Boolean enable, UInt16 type)
{
#pragma unused (enable)

	UInt32			*configRegPtr;
	UInt8			*dataByteRegPtr;
	UInt32			*dataLongRegPtr;
	UInt32			someValue;

//	DebugStr("\pEnableIOAccess");
	
	configRegPtr = (UInt32 *) kConfigAddressReg;
	dataByteRegPtr = (UInt8 *) kConfigDataReg;
	dataLongRegPtr = (UInt32 *) kConfigDataReg;
	
	someValue = (devID << 12) | kPCICommandOffset;	// Set the PCI device

	*configRegPtr = LByteSwap(someValue);			// Tell Bandit which device
	*dataByteRegPtr = 0x03;							// Enable Memory accesses

	if (type == kATIVendorID) {
		someValue = (devID << 12) | kPCIBaseReg1Offset;	// Set the PCI base address reg
		*configRegPtr = LByteSwap(someValue);			// Tell Bandit which device
		*dataLongRegPtr = LByteSwap(kATIVRAMAddr);		// Set VRAM address in PCI base reg
	}

	if (type == kDiamondVendorID) {
		someValue = (devID << 12) | kPCIBaseReg1Offset;	// Set the PCI base address reg
		*configRegPtr = LByteSwap(someValue);			// Tell Bandit which device
		*dataLongRegPtr = LByteSwap(kDiamondVRAMAddr);	// Set VRAM address in PCI base reg

		someValue = (devID << 12) | kPCIBaseReg2Offset;	// Set the PCI base address reg

		*configRegPtr = LByteSwap(someValue);			// Tell Bandit which device
		*dataLongRegPtr = LByteSwap(kDiamondIOAddr);	// Set IO base address in PCI base reg
	}

	return(noErr);
	
} /* End of EnableIOAccess */


/*-------------------------------------------------------------------------
*start
*
*Name:		SlamRegisters
*Creator:	George D. Wilson Jr.
*Date:		9/13/93
*
*Purpose:	Set all needed ATI graphics registers.
*
*Category:
*File:		PCIUtil.c
*
*Calls:
*
*Called By:
*
*Entry:
*
*Alters:
*
*Exit:		OSErr
*
*Detailed:
*
*Algorithm:
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
OSErr
SlamRegisters(UInt8 devID)
{
	IOLongWrite(0xF2800000, (devID << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x3;
	PerformPCIHack();
	
	IOByteWrite(PCI_CNTL,		0xFC);
	IOByteWrite(kAPERTURE_CNTL,	0x4C);

	IOByteWrite(kADVFUNC_CNTL,	0x01);

	IOWordWrite(kMISC_OPTIONS,	0x70A8);
	IOByteWrite(kADVFUNC_CNTL,	0x01);
	IOWordWrite(kEXT_GE_CONFIG,	0x4010);

	IOWordWrite(kSUBSYS_CNTL, 			kRESET_GE);
	IOWordWrite(kSUBSYS_CNTL, 			kNORMAL_GE);

	ATIWaitForIdle();

	IOWordWrite(kCLOCK_SEL,		0x1251);

	ATIReset68800();
	ATIWaitForIdle();

	//====================================
	// DAC Stuff
	//====================================
//	IOWordWrite(kEXT_GE_CONFIG,0x1000);
//	IOWordWrite(kDAC_MASK,0x03);
//	IOWordWrite(kEXT_GE_CONFIG,0x2000);
//	IOWordWrite(kDAC_R_INDEX,0x00);
//	IOWordWrite(kEXT_GE_CONFIG,0x3000);
//	IOWordWrite(kDAC_W_INDEX,0x2D);
//	IOWordWrite(kEXT_GE_CONFIG,0x0000);
//	IOWordWrite(kDAC_MASK,0xFF);
#if 0
	IOByteWrite(kH_TOTAL,0x63);
	IOByteWrite(kH_DISP,0x4F);
	IOByteWrite(kH_SYNC_STRT,0x52);
	IOByteWrite(kH_SYNC_WID,0x2C);
	IOWordWrite(kV_TOTAL,0x0418);
	IOWordWrite(kV_DISP,0x03BF);
	IOWordWrite(kV_SYNC_STRT,0x03DF);
	IOWordWrite(kV_SYNC_WID,0x0022);
#endif

	ATISetSyncRegisters();
	ATIWaitForIdle();

	IOByteWrite(kDISP_CNTL,0x23);	// 0x22

	IOWordWrite(kHORIZONTAL_OVERSCAN, 		0);
	IOWordWrite(kVERTICAL_OVERSCAN, 		0);
	IOWordWrite(kOVERSCAN_COLOR_8_BLUE, 	0);
	IOWordWrite(kOVERSCAN_COLOR_GREEN_RED, 	0);

	IOByteWrite(kSHADOW_CTL,				0x7F);
	IOByteWrite(kSHADOW_SET,				0);

	IOWordWrite(kMULTIFUNC_CNTL,	kSCISSOR_TOP | 0);
	IOWordWrite(kMULTIFUNC_CNTL,	kSCISSOR_LEFT | 0);
	IOWordWrite(kMULTIFUNC_CNTL,	kSCISSOR_BOTTOM | 0x5FF);
	IOWordWrite(kMULTIFUNC_CNTL,	kSCISSOR_RIGHT | 0x5FF);

	IOWordWrite(kSRC_Y_DIR,			1);
	IOWordWrite(kWRT_MASK,			0xFFFF);
	IOWordWrite(kDEST_CMP_FN,		0);

	IOWordWrite(kDP_CONFIG,			kDP_CONFIG_WRITE |
									kDP_CONFIG_POLY_FILL_DISABLE |
									kDP_CONFIG_READ_MODE_COLOR_DATA |
									kDP_CONFIG_ENABLE_DRAW |
									kDP_CONFIG_MONO_SRC_ALWAYS1 |
									kDP_CONFIG_BG_COLOR_SRC_BG |
									kDP_CONFIG_DATA_WIDTH_16 |
									kDP_CONFIG_MSB_FIRST |
									kDP_CONFIG_FG_COLOR_SRC_FG);

	IOWordWrite(kFRGD_MIX,			kCOLOR_SRC_FG |
									kMIX_FN_S);

//	IOWordWrite(0x7AEE + ATIIOBase,0x4010);

	IOLongWrite(0xF2800000, (devID << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x2;
	PerformPCIHack();
	
	return(noErr);
	
} /* End of SlamRegisters */


/*-------------------------------------------------------------------------
*
*							End of Module
*
*-----------------------------------------------------------------------*/

void ATIReset68800 (void)
{
	IOWordWrite(kCRT_OFFSET_LOW, 			0);
	IOWordWrite(kCRT_OFFSET_HIGH, 			0);
	IOWordWrite(kCRT_PITCH, 				0x80);
	IOWordWrite(kGE_OFFSET_LOW, 			0);
	IOWordWrite(kGE_OFFSET_HIGH, 			0);
	IOWordWrite(kGE_PITCH, 					0x80);
	IOWordWrite(kHORIZONTAL_OVERSCAN, 		0);
	IOWordWrite(kVERTICAL_OVERSCAN, 		0);
	IOWordWrite(kOVERSCAN_COLOR_8_BLUE, 	0);
	IOWordWrite(kOVERSCAN_COLOR_GREEN_RED, 	0);
	IOWordWrite(kCURSOR_OFFSET_HIGH, 		0);
	IOWordWrite(kDAC_MASK, 					0xFF);
}

void ATISetSyncRegisters (void)
{
#if 0
	IOByteWrite(kH_TOTAL,0x63);
	IOByteWrite(kH_DISP,0x4F);
	IOByteWrite(kH_SYNC_STRT,0x52);
	IOByteWrite(kH_SYNC_WID,0x2C);
	IOWordWrite(kV_TOTAL,0x0418);
	IOWordWrite(kV_DISP,0x03BF);
	IOWordWrite(kV_SYNC_STRT,0x03DF);
	IOWordWrite(kV_SYNC_WID,0x0022);
#endif

	IOByteWrite(kH_TOTAL,				0x63);
	IOByteWrite(kH_DISP,				0x4F);
	IOByteWrite(kH_SYNC_STRT,			0x52);
	IOByteWrite(kH_SYNC_WID,			0x2C);
	
	IOWordWrite(kV_TOTAL,				0x0418);
	IOWordWrite(kV_DISP,				0x03BF);
	IOWordWrite(kV_SYNC_STRT,			0x03DF); // 0x03D6
	IOWordWrite(kV_SYNC_WID,			0x0022);
}

void ATIFix688111Bug (void)
{
	unsigned char	clockSelect;
	short			cx;

	clockSelect = *(unsigned char *)kCLOCK_SELECT;
	clockSelect |= 1;
	IOByteWrite(kCLOCK_SELECT,			clockSelect);

	ATIWaitForIdle();

	/* set all pixel clock values to fix bug in 18811 clock chip */
	for (cx = 0; cx < 16; cx++) {
		clockSelect = (cx << 2) | 0x1;
		IOByteWrite(kCLOCK_SELECT,			clockSelect);
	}

	IOWordWrite(kCLOCK_SELECT,			
								kCLOCK_SELECT_ENABLE_8514 |
								kCLOCK_SELECT_FREQ(4) |
								kCLOCK_SELECT_DIV_2 |
								kCLOCK_SELECT_FIFO_DEPTH(2) |
								kCLOCK_SELECT_COMPOSITE_SYNC);
}

long ATIWaitForIdle (void)
{
	unsigned long	loopCount;
	unsigned char	fifoBusy;
	unsigned char	geBusy;

	loopCount = 0xFFFF;
	fifoBusy = *(unsigned char *)kEXT_FIFO_STATUS;
	while (loopCount > 0 && fifoBusy & 1) {
		fifoBusy = *(unsigned char *)kEXT_FIFO_STATUS;
		loopCount--;
	}

	if (loopCount == 0) {
		return 0;
	}

	loopCount = 0xFFFF;
	geBusy = *(unsigned char *)kGE_STAT_BUSY;
	while (loopCount > 0 && geBusy & kGE_BUSY) {
		geBusy = *(unsigned char *)kGE_STAT_BUSY;
		loopCount--;
	}

	if (loopCount == 0) {
		return 0;
	}
	
	return 1;
}
