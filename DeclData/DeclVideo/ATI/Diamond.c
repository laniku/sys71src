/*
	File:		Diamond.c

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 1/18/94	CP		first checked in

*/

/* Diamond.c */
/*
 * C Source Code to drive Diamond board
 */

#include <Types.h>
#include <Quickdraw.h>

#include		<Types.h>
#include		<Errors.h>
#include		<OSUtils.h>

#include		"ATIStdTypes.h"
#include		"ATI.h"

//	vclk = 0x4F349B;		// supposedly the value for 39.5 MHz (wrong!)
//	vclk = 0x47BCB4;		// for a (pre-non-divided) dotclock of 30.24 MHz
//	vclk = 0x47BC34;		// for a (pre-non-divided) dotclock of 60.48 MHz
//	vclk = 0x4D8527;		// for a (pre-non-divided) dotclock of 17.457 MHz

void GoDiamond640x480x8VGA(UInt8 devID)
{
	unsigned long memSize	= 0x2000001;					// bing
	unsigned long depth 	= 8;							// bing
	unsigned long rowBytes	= (depth >> 3) * 640;			// bing

#if 0
	// For now, enable slot D on Bandit 0
	*(unsigned long *)0xF2800000 	= LByteSwap(0x0848);	// Tell Bandit which device
	PerformPCIHack();

	*(unsigned long *)0xF2C00000 = LByteSwap(0x6000000C);	// Set VRAM address in PCI base reg
	PerformPCIHack();
#endif

	IOLongWrite(0xF2800000, (devID << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x3;
	PerformPCIHack();
	
	IOLongWrite(0xF2800000, (devID << 12) | 0x10);
	IOLongWrite(0xF2C00000, kDiamondVRAMAddr);

	IOLongWrite(0xF2800000, (devID << 12) | 0x14);
	IOLongWrite(0xF2C00000, kDiamondIOAddr);

	IOLongWrite(kDiamondInterruptEnable,		0x80);	// disable interrupts
	IOLongWrite(kDiamondRefreshPeriod,			0x186);	// rfperiod
	IOLongWrite(kDiamondRasMax,					0xFA);	// rlmax

	IOLongWrite(kDiamondMemConfig, 0x2);					// bing
	IOLongWrite(kDiamondSysConfig, 0x563000);				// bing

	SetupDACDiamond(0x45A8BCD0, depth);						// bing

	// vga 13"
	IOLongWrite(kDiamondHorzLength,				0xC7);		// bing
	IOLongWrite(kDiamondHorzSyncRisingEdge,		0x17);		// bing
	IOLongWrite(kDiamondHorzBlankRisingEdge,	0x21);		// bing
	IOLongWrite(kDiamondHorzBlankFallingEdge,	0xC1);		// bing

	IOLongWrite(kDiamondHorzCounterPreload,		0x00);		// bing

	IOLongWrite(kDiamondVertLength,				0x20D);		// bing
	IOLongWrite(kDiamondVertSyncRisingEdge,		0x01);		// bing
	IOLongWrite(kDiamondVertBlankRisingEdge,	0x19);		// bing
	IOLongWrite(kDiamondVertBlankFallingEdge,	0x1F9);		// bing

// apple timings
#if 0
	IOLongWrite(kDiamondHorzLength,				199);		// bing
	IOLongWrite(kDiamondHorzSyncRisingEdge,		22);		// bing
	IOLongWrite(kDiamondHorzBlankRisingEdge,	34);		// bing
	IOLongWrite(kDiamondHorzBlankFallingEdge,	193);		// bing

	IOLongWrite(kDiamondHorzCounterPreload,		0x00);		// bing

	IOLongWrite(kDiamondVertLength,				525);		// bing
	IOLongWrite(kDiamondVertSyncRisingEdge,		2);			// bing
	IOLongWrite(kDiamondVertBlankRisingEdge,	34);		// bing
	IOLongWrite(kDiamondVertBlankFallingEdge,	514);		// bing
#endif

	IOLongWrite(kDiamondVertCounterPreload,		0x00);		// bing

	IOLongWrite(kDiamondScreenRepaintTiming, 	0x1E5);		// bing

	// Enable sync's out the connector
	*(unsigned char *)(0xF20003C4) = 0x12;	// for 0x03C5, offset 0x12
	*(unsigned char *)(0xF20003C5) |= 0x10;	// bit 4

	IOLongWrite(kDiamondPlaneMask, 				0xFF);
	IOLongWrite(kDiamondDrawMode, 				0xA);

	// write X and Y minimum (both equal 0)
	IOLongWrite(kDiamondWindowMinimum, 0);
	// write X maximum (rowBytes - 1) and Y maximum (memSize/rowBytes - 1)
	IOLongWrite(kDiamondWindowMaximum, 
		((rowBytes - 1) << 16) | ((memSize / rowBytes) - 1));

	IOLongWrite(0xF2800000, (devID << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x02;
	PerformPCIHack();
}

void GoDiamond640x480x8Apple(UInt8 devID)
{
	unsigned long memSize	= 0x2000001;					// bing
	unsigned long depth 	= 8;							// bing
	unsigned long rowBytes	= (depth >> 3) * 640;			// bing

#if 0
	// For now, enable slot D on Bandit 0
	*(unsigned long *)0xF2800000 	= LByteSwap(0x0848);	// Tell Bandit which device
	PerformPCIHack();

	*(unsigned long *)0xF2C00000 = LByteSwap(0x6000000C);	// Set VRAM address in PCI base reg
	PerformPCIHack();
#endif

	IOLongWrite(0xF2800000, (devID << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x3;
	PerformPCIHack();
	
	IOLongWrite(0xF2800000, (devID << 12) | 0x10);
	IOLongWrite(0xF2C00000, kDiamondVRAMAddr);

	IOLongWrite(0xF2800000, (devID << 12) | 0x14);
	IOLongWrite(0xF2C00000, kDiamondIOAddr);

	SetupDACDiamond(0x47BCB4D0, depth);						// bing

	IOLongWrite(kDiamondMemConfig, 0x2);					// bing
	IOLongWrite(kDiamondSysConfig, 0x563000);				// bing

	// apple 13"
	IOLongWrite(kDiamondHorzSyncRisingEdge,		15);		// bing
	IOLongWrite(kDiamondHorzBlankRisingEdge,	39);		// bing
	IOLongWrite(kDiamondHorzBlankFallingEdge,	199);		// bing
	IOLongWrite(kDiamondHorzLength,				215);		// bing

	IOLongWrite(kDiamondHorzCounterPreload,		0x00);		// bing

	IOLongWrite(kDiamondVertSyncRisingEdge,		3);			// bing
	IOLongWrite(kDiamondVertBlankRisingEdge,	42);		// bing
	IOLongWrite(kDiamondVertBlankFallingEdge,	522);		// bing
	IOLongWrite(kDiamondVertLength,				525);		// bing

	IOLongWrite(kDiamondVertCounterPreload,		0x00);		// bing

	IOLongWrite(kDiamondScreenRepaintTiming, 	0x1E5);		// bing

	IOLongWrite(kDiamondDrawMode, 				0xA);
	IOLongWrite(kDiamondPlaneMask, 				0xFF);

	// write X and Y minimum (both equal 0)
	IOLongWrite(kDiamondWindowMinimum, 0);
	// write X maximum (rowBytes - 1) and Y maximum (memSize/rowBytes - 1)
	IOLongWrite(kDiamondWindowMaximum, 
		((rowBytes - 1) << 16) | ((memSize / rowBytes) - 1));

	IOLongWrite(0xF2800000, (devID << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x02;
	PerformPCIHack();
}

static void SetupDACDiamond(unsigned long vclk, unsigned long depth)
{
	short			i;
	unsigned char	*writeReg;
	unsigned char	*dataReg;
	unsigned char	cursorCmd;
	unsigned char	vp, hp;		// vertical/horizontal sync polarity
	unsigned char 	getThisDone;

	*(unsigned char *)(kBT485Reg0) = 0x82;	// 8 bit operation (intead of 6)
	PerformPCIHack();

	*(unsigned char *)(kBT485Reg2) = 0x30;	// PCLK1; data from 32 bit port
	PerformPCIHack();

	*(unsigned char *)(kRamWrite) = 0x01;	// enable command register 3 access
	PerformPCIHack();

	cursorCmd = (vclk & 0x20) ? 0x08 : 0;
	*(unsigned char *)(kBT485Reg3) = cursorCmd;	
	PerformPCIHack();

	switch(depth) {
		case 8:
			// set DAC into 8 bits per pixel
			*(unsigned char *)(kBT485Reg1) = 0x40;	
		break;
		case 16:
			// set DAC into 16 bits per pixel
			*(unsigned char *)(kBT485Reg1) = 0x30;	
		break;
		case 24:
		case 32:
			// set DAC into 24/32 bits per pixel
			*(unsigned char *)(kBT485Reg1) = 0x10;	
		break;
	}
	PerformPCIHack();

	*(unsigned char *)(kPixelMask) = 0xFF;	// pixel mask register
	PerformPCIHack();

	// setup up clock bits
	vp = (vclk & 0x80) ? NEGATIVE : POSITIVE;
	hp = (vclk & 0x40) ? NEGATIVE : POSITIVE;

	// Enable sync's out the connector
	*(unsigned char *)(0xF20003C4) = 0x12;	// for 0x03C5, offset 0x12
	getThisDone = *(unsigned char *)0xF20003C5;
	PerformPCIHack();
	*(unsigned char *)(0xF20003C5) = getThisDone | 0x10;

	SetupClockDiamond(vclk >> 8);
#if 0
	SetupClockDiamond(0x65D83D);					// mem clock = 25Mhz
	SetupClockDiamond(0x67B83C);
#endif
	SetupClockDiamond(vclk >> 8);

#if 0
	*(unsigned char *)(0xF20003C2) = (ReadClockReg()) | (hp << 6) | (vp << 7);
#endif
	// a magic number: set bits 6 and 7 to 0 for negative sync polarity
	*(unsigned char *)(0xF20003C2) = 0xC;
	PerformPCIHack();

	if (depth == 8) {
		writeReg = (unsigned char *)(0xF20003C8);	// kRamWrite
		dataReg = (unsigned char *)(0xF20003C9);	// kPaletteData
	
		*writeReg = 0;
		PerformPCIHack();
		for (i = 0; i < 256; i++) {
			*dataReg = i;	// red
			PerformPCIHack();
			*dataReg = i;	// green
			PerformPCIHack();
			*dataReg = i;	// blue
			PerformPCIHack();
		}
	}

}

unsigned char ReadClockReg(void)
{
	unsigned char	*ClockSelReg = (unsigned char *)(0xF20003C2);
	unsigned char	ret;
	
	ret = (*(ClockSelReg + 0xA));		// 0x03C2 is really read from 0x03CC
	PerformPCIHack();

	return ret;
}

void WriteClockReg(unsigned char whatever, unsigned char serialData, unsigned char serialClock)
{
	unsigned char	*ClockSelReg = (unsigned char *)(0xF20003C2);
	
	*ClockSelReg = (whatever | (serialData << 3) | (serialClock << 2));
	PerformPCIHack();
}

void SetupClockDiamond(unsigned long vclk)
{
	short			x;
	unsigned char	whatever;

	// Read the current clock reg value to save off bits [7..4] and [1..0]
	whatever = ReadClockReg() & 0xF3;

	// unlock the clock chip
	WriteClockReg(whatever, 1, 1);				// Raise the Data bit and the clock bit

	for (x = 0; x < 5; x++)
	{
		WriteClockReg(whatever, 1, 0);			// Lower the clock
		WriteClockReg(whatever, 1, 1);			// Raise the clock
	}
	
	// Finish Unlocking
	WriteClockReg(whatever, 1, 0);
	WriteClockReg(whatever, 0, 0);
	WriteClockReg(whatever, 0, 1);

	// Start bits
	WriteClockReg(whatever, 0, 0);				// Clock:  hi-lo
	WriteClockReg(whatever, 0, 1);				// Clock:  lo-hi

	// Manchester encoding:
	//   Set SerialData to !vclk[0];  Drop SerialClk to 0; Set SerialData to vclk; Set SerialClock to 1
	for (x = 0; x < 24; x++)
	{
		// write out the inverse of the vclk bit
		WriteClockReg(whatever, (vclk & 1) ? 0 : 1, 1);
		WriteClockReg(whatever, (vclk & 1) ? 0 : 1, 0);

		// write out the vclk bit
		WriteClockReg(whatever, (vclk & 1) , 0);
		WriteClockReg(whatever, (vclk & 1) , 1);
				
		vclk >>= 1;
	}

	// Stop bits
	WriteClockReg(whatever, 1, 1);
	WriteClockReg(whatever, 1, 0);
	WriteClockReg(whatever, 1, 1);
}

void GoDiamond640x480x8AppleOld(UInt8 devID);
void GoDiamond640x480x8AppleOld(UInt8 devID)
{
	unsigned char *clutData;
	unsigned char *clutAddrReg;
	unsigned char cursorCmd;
	int	i;

	IOLongWrite(0xF2800000, (devID << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x3;
	PerformPCIHack();
	
	IOLongWrite(0xF2800000, (devID << 12) | 0x10);
	IOLongWrite(0xF2C00000, kDiamondVRAMAddr);

	IOLongWrite(0xF2800000, (devID << 12) | 0x14);
	IOLongWrite(0xF2C00000, kDiamondIOAddr);

	// Configure memory space appropriately
	IOLongWrite( kDiamondMemConfig, 0x2);
//		IOLongWrite( kDiamondSysConfig, (0x6 << 17) | (1 << 13) | (1 << 12));
	IOLongWrite( kDiamondSysConfig, (0x563000));	// RowBytes of 640 hardcoded

	// Draw Engine parameters
	IOLongWrite( kDiamondWindowMinimum, 0);
	IOLongWrite( kDiamondWindowMaximum, (639 << 16) | ((0x2000001 / 640) - 1));

	IOLongWrite( kDiamondScreenRepaintTiming,	0x1E5);

	*(unsigned char *)(0xF2009800) = 0x40;	// set DAC into 8 bits per pixel
											// set to 0x30 for 16 bpp
											// set to 0x10 for 32 bpp
	PerformPCIHack();

	*(unsigned char *)(0xF2009402) = 0x82;	// 8 bit operation (instead of 6)
	PerformPCIHack();

	*(unsigned char *)(0xF2009801) = 0x32;	// PCLK1; data from 32 bit port
	PerformPCIHack();

	*(unsigned char *)(0xF20003C6) = 0xFF;	// pixel mask register
	PerformPCIHack();

	cursorCmd = 0x04 & !0x08;									// 64x64 bit cursor;
																// disable 2 times clock	
	*(unsigned char *)(0xF20003C8) = 0x01;						// enable command register 3 access
	PerformPCIHack();

	*(unsigned char *)(0xF2009802) = cursorCmd;	
	PerformPCIHack();

	clutAddrReg = (UInt8 *)(0xF20003C8);	// Point to write-index register
	clutData = (UInt8 *)(0xF20003C9);		// Point to data register

	*clutAddrReg = 0;								// Point to the first entry
	for ( i = 0; i < 256; i++ ) {
		*clutData = i;
		PerformPCIHack();
		*clutData = i;
		PerformPCIHack();
		*clutData = i;
		PerformPCIHack();
	}
	
//		SetupClockW9000();
	{
		unsigned long	data = 0x47BCB4;		// for a (pre-non-divided) dotclock of 30.24 MHz
		short			x;
		unsigned char	whatever;	

		// Read the current clock reg value to save off bits [7..4] and [1..0]
		whatever = ReadClockReg() & 0xF3;
	
		// unlock the clock chip
		WriteClockReg(whatever, 1, 1);				// Raise the Data bit and the clock bit
	
		for (x = 0; x < 5; x++)
		{
			WriteClockReg(whatever, 1, 0);			// Lower the clock
			WriteClockReg(whatever, 1, 1);			// Raise the clock
		}
		
		// Finish Unlocking
		WriteClockReg(whatever, 1, 0);
		WriteClockReg(whatever, 0, 0);
		WriteClockReg(whatever, 0, 1);
	
		// Start bits
		WriteClockReg(whatever, 0, 0);				// Clock:  hi-lo
		WriteClockReg(whatever, 0, 1);				// Clock:  lo-hi
	
		// Manchester encoding:
		//   Set SerialData to !data[0];  Drop SerialClk to 0; Set SerialData to data; Set SerialClock to 1
		for (x = 0; x < 24; x++)
		{
			// write out the inverse of the data bit
			WriteClockReg(whatever, (data & 1) ? 0 : 1, 1);
			WriteClockReg(whatever, (data & 1) ? 0 : 1, 0);
	
			// write out the data bit
			WriteClockReg(whatever, (data & 1) , 0);
			WriteClockReg(whatever, (data & 1) , 1);
					
			data >>= 1;
		}
	
		// Stop bits
		WriteClockReg(whatever, 1, 1);
		WriteClockReg(whatever, 1, 0);
		WriteClockReg(whatever, 1, 1);
		
		// Enable sync's out the connector
		*(unsigned char *)(0xF20003C4) = 0x12;		// for 0x03C5, offset 0x12
		*(unsigned char *)(0xF20003C5) |= 0x10;		// bit 4
	}

	IOLongWrite( kDiamondHorzSyncRisingEdge,	15);
	IOLongWrite( kDiamondHorzBlankRisingEdge,	39);
	IOLongWrite( kDiamondHorzBlankFallingEdge,	199);
	IOLongWrite( kDiamondHorzLength,			215);

	IOLongWrite( kDiamondVertSyncRisingEdge,	3);
	IOLongWrite( kDiamondVertBlankRisingEdge,	42);
	IOLongWrite( kDiamondVertBlankFallingEdge,	522);
	IOLongWrite( kDiamondVertLength,			525);

	IOLongWrite(0xF2800000, (devID << 12) | 4);
	*(unsigned char *)(0xF2C00000) = 0x2;
	PerformPCIHack();
}

