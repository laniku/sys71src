/*
	File:		Diamond.h

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 1/18/94	CP		first checked in

*/

/* Diamond.h */
/*
 * Diamond board with Weitek 9000 controller header file
 */

#define	NEGATIVE					0
#define	POSITIVE					1

#define	kDiamondCommandVal			(kMemoryAccess | kReadWaitCycle)

#define	kDiamondVendorID			0x100E
#define	kDiamondDeviceID			0x9001

#define	kDiamondIOBaseAddr			0x9000
#define	kDiamondIOAddr				(0x1 | kDiamondIOBaseAddr)
#define	kDiamondVRAMAddr			0xE0000000		// same place as ATI

#define kDiamondFBBase				(kDiamondVRAMAddr + (1 << 21))	// page 45 Direct frame buffer

#define	kDiamondRegBase				(kDiamondVRAMAddr + (0x2 << 19))// page 45 control registers
#define	kDiamondDrawRegBase			(kDiamondVRAMAddr + (0x3 << 19))// page 45 control registers

#define	kDiamondMemConfig			(kDiamondRegBase + (0x180 + (1 << 2)))

#define	kDiamondRefreshPeriod		(kDiamondRegBase + (0x180 + (2 << 2)))
#define kDiamondRasMax				(kDiamondRegBase + (0x180 + (4 << 2)))

#define	kDiamondSysConfig			(kDiamondRegBase + (0x1 << 2))
#define	kDiamondInterrupt			(kDiamondRegBase + (0x2 << 2))
#define	kDiamondInterruptEnable		(kDiamondRegBase + (0x3 << 2))

#define	kDiamondHorzCounter				(kDiamondRegBase + (0x100 + (1 << 2)))
#define	kDiamondHorzLength				(kDiamondRegBase + (0x100 + (2 << 2)))
#define	kDiamondHorzSyncRisingEdge		(kDiamondRegBase + (0x100 + (3 << 2)))
#define	kDiamondHorzBlankRisingEdge		(kDiamondRegBase + (0x100 + (4 << 2)))
#define	kDiamondHorzBlankFallingEdge	(kDiamondRegBase + (0x100 + (5 << 2)))
#define	kDiamondHorzCounterPreload		(kDiamondRegBase + (0x100 + (6 << 2)))

#define	kDiamondVertCounter				(kDiamondRegBase + (0x100 + (7 << 2)))
#define	kDiamondVertLength				(kDiamondRegBase + (0x100 + (8 << 2)))
#define	kDiamondVertSyncRisingEdge		(kDiamondRegBase + (0x100 + (9 << 2)))
#define	kDiamondVertBlankRisingEdge		(kDiamondRegBase + (0x100 + (10 << 2)))
#define	kDiamondVertBlankFallingEdge	(kDiamondRegBase + (0x100 + (11 << 2)))
#define	kDiamondVertCounterPreload		(kDiamondRegBase + (0x100 + (12 << 2)))

#define	kDiamondScreenRepaintAddress	(kDiamondRegBase + (0x100 + (13 << 2)))
#define	kDiamondScreenRepaintTiming		(kDiamondRegBase + (0x100 + (14 << 2)))

#define	kDiamondScreenRefreshTiming		(kDiamondRegBase + (0x100 + (15 << 2)))

#define	kDiamondStatus					(kDiamondDrawRegBase + 0x0)
#define	kDiamondStatusIssue_qbN			(1 << 31)
#define kDiamondStatusBusy				(1 << 30)
#define	kDiamondStatusPicked			(1 << 7)
#define	kDiamondStatusPixelSoftware		(1 << 6)
#define	kDiamondStatusBlitSoftware		(1 << 5)
#define	kDiamondStatusQuadSoftware		(1 << 4)
#define	kDiamondStatusQuadConcave		(1 << 3)
#define	kDiamondStatusQuadHidden		(1 << 2)
#define	kDiamondStatusQuadVisible		(1 << 1)
#define	kDiamondStatusQuadIntersects	(1 << 0)

#define	kDiamondForegroundColor			(kDiamondDrawRegBase + (0x200 + (0 << 2)))
#define	kDiamondBackgroundColor			(kDiamondDrawRegBase + (0x200 + (1 << 2)))
#define	kDiamondPlaneMask				(kDiamondDrawRegBase + (0x200 + (2 << 2)))
#define	kDiamondDrawMode				(kDiamondDrawRegBase + (0x200 + (3 << 2)))
#define	kDiamondPatternOriginX			(kDiamondDrawRegBase + (0x200 + (4 << 2)))
#define	kDiamondPatternOriginY			(kDiamondDrawRegBase + (0x200 + (5 << 2)))
#define	kDiamondRaster					(kDiamondDrawRegBase + (0x200 + (6 << 2)))
#define	kDiamondPixel8					(kDiamondDrawRegBase + (0x200 + (7 << 2)))
#define	kDiamondWindowMinimum			(kDiamondDrawRegBase + (0x200 + (8 << 2)))
#define	kDiamondWindowMaximum			(kDiamondDrawRegBase + (0x200 + (9 << 2)))
#define	kDiamondPattern0_1				(kDiamondDrawRegBase + (0x200 + (21<< 2)))
#define	kDiamondPattern2_3				(kDiamondDrawRegBase + (0x200 + (22<< 2)))
#define	kDiamondPattern4_5				(kDiamondDrawRegBase + (0x200 + (23<< 2)))
#define	kDiamondPattern6_7				(kDiamondDrawRegBase + (0x200 + (24<< 2)))
#define	kDiamondPattern8_9				(kDiamondDrawRegBase + (0x200 + (25<< 2)))
#define	kDiamondPattern10_11			(kDiamondDrawRegBase + (0x200 + (26<< 2)))
#define	kDiamondPattern12_13			(kDiamondDrawRegBase + (0x200 + (27<< 2)))
#define	kDiamondPattern14_15			(kDiamondDrawRegBase + (0x200 + (28<< 2)))

#define	kBT485Reg0			(kDiamondIOBaseAddr | 0xF2000402)
#define	kBT485Reg1			(kDiamondIOBaseAddr | 0xF2000800)
#define	kBT485Reg2			(kDiamondIOBaseAddr | 0xF2000801)
#define	kBT485Reg3			(kDiamondIOBaseAddr | 0xF2000802)
#define	kPixelMask			(0xF20003C6)
#define	kVgaMisc			(0xF20003C2)
#define	kVgaIndexRead		(0xF20003C4)
#define	kVgaIndexWrite		(0xF20003C5)
#define	kRamRead			(0xF20003C7)
#define	kRamWrite			(0xF20003C8)
#define	kPaletteData		(0xF20003C9)

void 			InitDiamond(void);
void			SetupDACDiamond(unsigned long, unsigned long);
unsigned char	ReadClockReg(void);
void			WriteClockReg(unsigned char whatever, unsigned char serialData, unsigned char serialClock);
void			SetupClockDiamond(unsigned long);
void			GoDiamond640x480x8VGA(UInt8);
void			GoDiamond640x480x8Apple(UInt8);