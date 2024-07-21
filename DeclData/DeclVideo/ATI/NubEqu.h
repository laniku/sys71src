/*
	File:		NubEqu.h

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 11/5/93	fau		first checked in
		 <1>	10/27/93	fau		first checked in
		 <1>	10/19/93	fau		first checked in

*/


/*
	NubEqu.h
				Hurricane hardware addresses when accessed from a Nub card with
				the 0xE8C mapping PROM.
				
				Note that these addresses are lacking in the upper-nybble department!
				You need to OR in the superslot base address of whatever slot your
				Nub is plugged into.
				
				Anyplace you see an 's' refers to the slot number that your Nub board
				is plugged into.
				
				This is not a hack.
				
				
	History
	-------
				JFB			4-6-92			New today.
				JFB			4-15-92			Started Hurricane utility routine
											 define/typedef/prototype sections.
				gdw			4-21-92			Moved FlatlineBaseAddress for new Nub
				MRN			4-27-92			Added interrupt indexes to interrupt mask section
				
 */
 
 
/* ----------------------------------------------------------------------------------------------
 	Super Slot Base Addresses 
 */
  
#define		kSuper9					0x90000000
#define		kSuperA					0xA0000000
#define		kSuperB					0xB0000000
#define		kSuperC					0xC0000000
#define		kSuperD					0xD0000000
#define		kSuperE					0xE0000000

/* ----------------------------------------------------------------------------------------------
	Normal Slot Base Addresses
 */
 
#define	 	kSlot9					0x09000000
#define	 	kSlotA					0x0A000000
#define	 	kSlotB					0x0B000000
#define	 	kSlotC					0x0C000000
#define	 	kSlotD					0x0D000000
#define	 	kSlotE					0x0E000000
	
/* ----------------------------------------------------------------------------------------------
	Nub Soft Switches - * Note that these are in Normal Slot Space! *
 */
 
#define	 	kNMRQEnable				0xF0B00000		/* enable generation of Nubus NMRQ* from */
#define	 	kNMRQDisable			0xF0900000		/*   88110 INT* line					 */
 	
#define	 	kEXTRA_LOW				0xF0A80000		/* pull EXTRA_L low */
#define	 	kEXTRA_TRI				0xF0880000		/* tristate EXTRA_L */

/* ----------------------------------------------------------------------------------------------
	Base addresses for memory & peripherals on Hurricane.
	
	RAM is available from 0xs0000000 to 0xs9000000 when using the 0xE8C mapping PROM.
	
	Remember that you have to OR in the Super Slot base address to get the actual
	base address.
 */
 
#define	 	kRAMBase				0x00000000		/* Hurricane DRAM */
#define	 	kSashaBase				0x0A000000		/* Sasha & Swatch base address */
#define	 	kMazdaBase				0x0B000000		/* Mazda base address */
#define		kMazdaEEPROMBase		0x0C000000		/* Mazda EEPROM base addresss */
#define		kMazdaLowSpeedBase		0x0D000000		/* Mazda Low-Speed bus base address */
#define	 	kFlatlineBase			0x09000000		/* Flatline base address for 0x8C devices */
#define		kFlatlinePixNIntBase	0x0F000000		/* Flatline base address for 0x8F devices */
 	
/* ----------------------------------------------------------------------------------------------
	Register offsets.
	
	OR these offsets with the actual base address (which you built by OR'ing the Super Slot
	base address with the peripheral chip's base address) to get at a specific register
	in a specific peripheral chip.
 */
 
/* ----------------------------------------------------------------------------------------------
	Register offsets for Sasha & Swatch.
	
	OK, Sasha & Swatch are a little weird.  Unlike Mazda & Flatline, you don't just
	have a bunch of registers that you can write to directly.
	
	You access all of the registers in Sasha & Swatch via one register, namely the
	base register (kyourSuperSlot | kSashaBase).
	
	To actually get to a register inside Sasha & Swatch, you write a REGISTER SELECT
	number into the high byte of a 32-bit word.  Up to 24 bits of data can be written
	via the low 7 bytes.  For a write, you write the Register Select and the data
	to (kyourSuperSlot | kSashaBase).  For a read, first write the Register Select into 
	the LOW BYTE of the 24-bit data field (with Register Select = 0x00), then read
	back the data (i.e., writing 0x000000C0 & then reading would give you the contents
	of register 0xC0).
	
	It looks like this:
	
									0 x r r d d d d d d 
										\_/ \_________/
										 |       |
								   Register		Data
								   Select
								   
	The #define's below are Register Selects, that you can them OR into your own long!
 */

#define		kReadAddress			0x00000000		/* For reads, write the Register Select of the */
													/*  register you want in the low byte */
#define		kParityEnable			0x01000001		/* 0 = Parity OFF, 1 = Parity ON (default OFF) */
#define		kParityDisable			0x01000000		

#define		kDitherTruncate			0x02000000		/* 0 = Truncate, 1 = 2x2 Dither, 2 = 4x4 dither */
#define		kDither2x2				0x02000001		/*  no default */
#define		kDither4x4				0x02000002		
													
#define		kForceParityErr			0x03000000		/* 16 bits, a '1' in loc 'n' forces err in byte 'n' */
													/*  default = 0 */
#define		kParityErrReg			0x04000000		/* 16 bits, a '1' in loc 'n' records err in byte 'n' */
													/*  default = 0 */
#define		kNoParityErr			0x00000000

#define		kHVidTiming				0x80000000		/* Pulse length of Horizontal Front Porch */
#define		kHSyncPulse				0x81000000		/* Pulse length of Horizontal Sync Pulse */
#define		kHBreezeWay				0x82000000		/* Pulse length of Horizontal BreezeWay */
#define		kHBurstRst				0x83000000		/* Pulse length of Horizontal Burst */
#define		kHBackPorch				0x84000000		/* Pulse length of Horizontal Back Porch */
#define		kHActivePixel			0x85000000		/* Number of active Horizontal pixels in a scan line */
#define		kHHalfLine				0x86000000		/* Position of Half Line */
#define		kHPixels				0x87000000		/* Total number of Horizontal pixels */
#define		kVFrontPorch			0x88000000		/* Pulse length of Vertical Front Porch */
#define		kVFrontPorchEQ			0x89000000		/* Pulse length of Vertical Front Porch with EQ */
#define		kVSyncPulse				0x8A000000		/* Pulse length of Vertical Sync Pulse */
#define		kVBackPorchEQ			0x8B000000		/* Pulse length of Vertical Back Porch with EQ */
#define		kVBackPorch				0x8C000000		/* Pulse length of Vertical Back Porch */
#define		kVActiveLines			0x8D000000		/* Number of active Vertical scan lines */
#define		kVHalfLines				0x8E000000		/* Number of active half Vertical scan lines */
#define		kSerrationPulse			0x8F000000
#define		kEqualizePulse			0x90000000		/* For interlaced screens only */
#define		kSepHorizontal			0x91000000
#define		kSepVerticalSync		0x92000000
#define		kCounterTest			0x93000000		/* Value to load counters for testing purposes */

#define		kStatus					0x97000000		/* Swatch Status - 13 bits: */
#define		kRevMask				0x00001E00
#define		kOddFieldStateMask		0x00000100		
#define		kHFrontPorchMask		0x00000080
#define		kHSyncMask				0x00000040
#define		kHBackPorchMask			0x00000020
#define		kActivePixelMask		0x00000010
#define		kVFrontPorchMask		0x00000008
#define		kVSyncMask				0x00000004
#define		kVBackPorchMask			0x00000002
#define		kActiveLineMask			0x00000001
												
#define		kVCNT					0xA0000000		/* Vertical Half Line Counter */
#define		kVLineIntMask			0xA1000000		/* Vertical line interrupt mask */
#define		kVLine0Int				0xA2000000		/* These are the vertical lines to cause an int on */
#define		kVLine1Int				0xA3000000
#define		kVLine2Int				0xA4000000
#define		kVLine3Int				0xA5000000
#define		kVLine4Int				0xA6000000
#define		kVLine5Int				0xA7000000
#define		kVLine6Int				0xA8000000
#define		kVLine7Int				0xA9000000

#define		kSwatchCtl1				0xB0000000		/* Swatch Ctl Reg 1 - 10 bits: */
#define		kHSYNCActiveHi			0x00000200
#define		kHSYNCActiveLo			0x00000000
#define		kVSYNCActiveHi			0x00000100
#define		kVSYNCActiveLo			0x00000000
#define		kLdHSepCNTTST			0x00000080		/* for testing ONLY */
#define		kHaltHSepCounter		0x00000040
#define		kLdVSepCNTTST			0x00000020		/* for testing ONLY */
#define		kHaltVSepCounter		0x00000010
#define		kLdHCNTTST				0x00000008		/* for testing ONLY */
#define		kHaltHCounter			0x00000004
#define		kLdVCNTTST				0x00000002		/* for testing ONLY */
#define		xHaltVCounter			0x00000001
												
#define		kSwatchCtl2				0xB1000000		/* Swatch Ctl Reg2 - 10 bits: */
#define		kInterlaceEnable		0x00000200
#define		kGENLOCKEnable			0x00000100
#define		kVIDCLKSync				0x00000080
												/* [6:4] - Horiz pipeline delay (match Swatch to video pipe) */
												/* [3:2] - Vertical line delay */
#define		kHalfLineAdjFld2		0x00000002
#define		kHalfLineAdjFld1		0x00000001
#define		kBillsPipeNLineNumber	0x00000024		/* this is from the old diagnostic setup code */

#define		kOutputCtl				0xB2000000		/* Output Control Reg - 5 bits, default 0x00: */
#define		kPixelDataOutEn			0x00000010
#define		kAcDcCSYNCEnable		0x00000008
#define		kAcDcCSYNCDisable		0x00000000
#define		kAcDcCBLANKEnable		0x00000004
#define		kAcDcCBLANKDisable		0x00000000
#define		kAcDcSYNCEnable			0x00000002
#define		kAcDcSYNCDisable		0x00000000
#define		kAcDcLoadClkEnable		0x00000001
#define		kAcDcLoadClkDisable		0x00000000

#define		kElmerCtl				0xB3000000		/* Elmer Control Reg - 9 bits: */
#define		kRAMInterfaceEnable		0x00000100		/* RAM Interface enable */
#define		kRAMInterfaceDisable	0x00000000		/* RAM Interface disable - video pipe black */
#define		kCrsrAntiAliasEnable	0x00000080
#define		kCrsrAntiAliasDisable	0x00000000
#define		kCrsrXOREnable			0x00000040
#define		kCrsrXORDisable			0x00000000
#define		kCrsrEnable				0x00000020
#define		kCrsrDisable			0x00000000
#define		kGreyScaleEnable		0x00000010		/* 8bpp only! */
#define		kGreyScaleDisable		0x00000000
#define		kNative16bppEnable		0x00000008
#define		kNative16bppDisable		0x00000000
#define		kLdSigAcDcVIDCLK		0x00000004		/* Load signal select for AC/DC */
#define		kLdSigAcDcLdClk			0x00000000
#define		k24bitIFtoAcDc			0x00000002		/* gotta be a better name for this */
#define		k2x16bitIFtoAcDc		0x00000000		/* ditto */
#define		kDithered16bppEnable	0x00000001
#define		kDithered16bppDisable	0x00000000

#define		kVideoPipeClockCtl		0xB4000000		/* Video Pipe Clock Control Reg - 3 bits, default 0x00: */
#define		kVidClkUsesVidClk		0x00000004
#define		kVidClkUsesSysClk		0x00000000
#define		kClockDivideEnable		0x00000002		/* half clock */
#define		kClockDivideDisable		0x00000000		/* full clock */
#define		kECLClock				0x00000001
#define		kTTLClock				0x00000000

#define		kCrsrXPos				0xB5000000
#define		kCrsrYPos				0xB6000000
#define		kCrsrHeight				0xB7000000
#define		kCrsrWidth				0xB8000000

#define		kRAMTestReg				0xBC000000

#define		kSenseLines				0xC0000000
#define		kSenseLinesReg			0x000000C0

#define		kSwatchSoftReset		0xD0000000
#define		kVidPipeReset			0xD1000000
#define		kReset					0x00000000		/* these work for both reset regs */
#define		kNormal					0x00000001

#define		kBurstlm				0xE0000000
#define		kBurstThreshold1		0xE1000000
#define		kBurstThreshold2		0xE2000000
#define		kStopThreshold			0xE3000000
#define		kCrsrXCnt				0xE4000000
#define		kScrnXCnt				0xE5000000
#define		kFIFOUnderflow			0xE6000000



/* ----------------------------------------------------------------------------------------------
	Register offsets for Mazda.
 */

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Channel Program control registers.
	
	CPP:		Channel Program Pointer
	CPCont:		Channel Program Continue
	CPAbort:	Channel Program Abort
	
	These are all in kMazdaBase space.
 */
 
#define		kCPPStillVidCh1			0x00000000
#define		kCPContStillVidCh1		0x00000008
#define		kCPAbortStillVidCh1		0x00000010

#define		kCPPStillVidCh2			0x00000020
#define		kCPContStillVidCh2		0x00000028
#define		kCPAbortStillVidCh2		0x00000030

#define		kCPPFloppy1				0x00000040
#define		kCPContFloppy1			0x00000048
#define		kCPAbortFloppy1			0x00000050

#define		kCPPFloppy2				0x00000060	
#define		kCPContFloppy2			0x00000068
#define		kCPAbortFloppy2			0x00000070

#define		kCPPEtherRcv			0x00000080
#define		kCPContEtherRcv			0x00000088
#define		kCPAbortEtherRcv		0x00000090

#define		kCPPEtherXmit			0x000000A0
#define		kCPContEtherXmit		0x000000A8
#define		kCPAbortEtherXmit		0x000000B0

#define		kCPPAudioLeftIn			0x000000C0
#define		kCPContAudioLeftIn		0x000000C8
#define		kCPAbortAudioLeftIn		0x000000D0

#define		kCPPAudioLeftOut		0x000000E0
#define		kCPContAudioLeftOut		0x000000E8
#define		kCPAbortAudioLeftOut	0x000000F0

#define		kCPPAudioRightIn		0x00000100
#define		kCPContAudioRightIn		0x00000108
#define		kCPAbortAudioRightIn	0x00000110
 
#define		kCPPAudioRightOut		0x00000120
#define		kCPContAudioRightOut	0x00000128
#define		kCPAbortAudioRightOut	0x00000130

#define		kCPPPhoneIn				0x00000140
#define		kCPContPhoneIn			0x00000148
#define		kCPAbortPhoneIn			0x00000150

#define		kCPPPhoneOut			0x00000160
#define		kCPContPhoneOut			0x00000168
#define		kCPAbortPhoneOut		0x00000170

#define		kCPPAudioLineIn			0x00000180
#define		kCPContAudioLineIn		0x00000188
#define		kCPAbortAudioLineIn		0x00000190

#define		kCPPAudioLineOut		0x000001A0
#define		kCPContAudioLineOut		0x000001A8
#define		kCPAbortAudioLineOut	0x000001B0

#define		kCPPISDNXmitD			0x000001C0
#define		kCPContISDNXmitD		0x000001C8
#define		kCPAbortISDNXmitD		0x000001D0

#define		kCPPISDNRcvD			0x000001E0
#define		kCPContISDNRcvD			0x000001E8
#define		kCPAbortISDNRcvD		0x000001F0

#define		kCPPSCC1OutA			0x00000200
#define		kCPContSCC1OutA			0x00000208
#define		kCPAbortSCC1OutA		0x00000210

#define		kCPPSCC1InA				0x00000220
#define		kCPContSCC1InA			0x00000228
#define		kCPAbortSCC1InA			0x00000230

#define		kCPPSCC1OutB			0x00000240
#define		kCPContSCC1OutB			0x00000248
#define		kCPAbortSCC1OutB		0x00000250

#define		kCPPSCC1InB				0x00000260
#define		kCPContSCC1InB			0x00000268
#define		kCPAbortSCC1InB			0x00000270

#define		kCPPISDNXmitBD			0x00000280
#define		kCPContISDNXmitBD		0x00000288
#define		kCPAbortISDNXmitBD		0x00000290

#define		kCPPISDNRcvBD			0x000002A0
#define		kCPContISDNRcvBD		0x000002A8
#define		kCPAbortISDNRcvBD		0x000002B0

#define		kCPPISDNXmitBE			0x000002C0
#define		kCPContISDNXmitBE		0x000002C8
#define		kCPAbortISDNXmitBE		0x000002D0

#define		kCPPISDNRcvBE			0x000002E0
#define		kCPContISDNRcvBE		0x000002E8
#define		kCPAbortISDNRcvBE		0x000002F0

#define		kCPPCudaXmitSyncRcv		0x00000300		/* Cuda Transmit & Synchronous Rcv */
#define		kCPContCudaXmitSyncRcv	0x00000308		/* Can anyone think of a better name for this? */
#define		kCPAbortCudaXmitSyncRcv 0x00000310

#define		kCPPCudaAsyncRcv		0x00000320
#define		kCPContCudaAsyncRcv		0x00000328
#define		kCPAbortCudaAsyncRcv	0x00000330

#define		kCPPDMAChanTask0		0x00000340
#define		kCPContDMAChanTask0		0x00000348
#define		kCPAbortDMAChanTask0	0x00000350

#define		kCPPAsyncEvents			0x00000360
#define		kCPContAsyncEvents		0x00000368
#define		kCPAbortAsyncEvents		0x00000370

#define		kCPPRateConvertIn		0x00000380		/* NOT IN THIS MAZDA!! */
#define		kCPContRateConvertIn	0x00000388
#define		kCPAbortRateConvertIn	0x00000390

#define		kCPPRateConvertOut		0x000003A0		/* NOT IN THIS MAZDA!! */
#define		kCPContRateConvertOut	0x000003A8
#define		kCPAbortRateConvertOut	0x000003B0

#define		kCPPSCSIDev0			0x000003C0	
#define		kCPContSCSIDev0			0x000003C8
#define		kCPAbortSCSIDev0		0x000003D0

#define		kCPPSCSIDev1			0x000003E0	
#define		kCPContSCSIDev1			0x000003E8
#define		kCPAbortSCSIDev1		0x000003F0

#define		kCPPSCSIDev2			0x00000400	
#define		kCPContSCSIDev2			0x00000408
#define		kCPAbortSCSIDev2		0x00000410

#define		kCPPSCSIDev3			0x00000420	
#define		kCPContSCSIDev3			0x00000428
#define		kCPAbortSCSIDev3		0x00000430

#define		kCPPSCSIDev4			0x00000440	
#define		kCPContSCSIDev4			0x00000448
#define		kCPAbortSCSIDev4		0x00000450

#define		kCPPSCSIDev5			0x00000460	
#define		kCPContSCSIDev5			0x00000468
#define		kCPAbortSCSIDev5		0x00000470

#define		kCPPSCSIDev6			0x00000480	
#define		kCPContSCSIDev6			0x00000488
#define		kCPAbortSCSIDev6		0x00000490

#define		kCPPSCSIDev7			0x000004A0	
#define		kCPContSCSIDev7			0x000004A8
#define		kCPAbortSCSIDev7		0x000004B0

#define		kCPPSCSIDev8			0x000004C0	
#define		kCPContSCSIDev8			0x000004C8
#define		kCPAbortSCSIDev8		0x000004D0

#define		kCPPSCSIDev9			0x000004E0	
#define		kCPContSCSIDev9			0x000004E8
#define		kCPAbortSCSIDev9		0x000004F0

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Channel Program Flags.
 */
 
#define		kCCReady				0x80
#define		kCCChain				0x40
#define		kCCUpdate				0x20
#define		kCCInterrupt			0x10
#define		kCCAbort				0x04
 
/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Channel Command Commands.
 */

#define		kReadDMA				0x00
#define		kWriteDMA				0x01
#define		kReadReg				0xF0
#define		kWriteReg				0xF1

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Channel Program IOM IDs.
 */

#define		kAudioLeftIn			0x1800			/* 0x0006 << 10 to get bits in right pos */
#define		kAudioLeftOut			0x1C00			/* 0x0007 << 10 to get bits in right pos */
#define		kAudioRightIn			0x2000			/* 0x0008 << 10 to get bits in right pos */
#define		kAudioRightOut			0x2400			/* 0x0009 << 10 to get bits in right pos */

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Mazda Interrupt control/status registers.
	
	Interrupt register bit assignments:
			
	These are all in kMazdaBase space.
 */
 
#define		kMazdaIRQUpMask0		0x00001000		/* Enable/Disable flags for the 64 interrupt */
#define		kMazdaIRQLoMask0		0x00001008		/* 	sources  */
#define		kMazdaIRQUpNew0			0x00001020		/* Clear interrupt flags for the 64 interrupt */
#define		kMazdaIRQLoNew0			0x00001028		/*	sources  */

#define		kAllIntsDisabled		0x00000000
#define		kAllIntsEnabled			0xFFFFFFFF
													/* Bit xy = Interrupt Source 					*/
													/* -------------------------					*/
#define		kWilsonIntMask			0x02000000		/* Bit 57 = Wilson								*/
													/* ... 											*/
#define		kVideoLineIntMask		0x00800000		/* Bit 55 = Video Line							*/
													/* ... 											*/
#define		kSystemTimerIntMask		0x00080000		/* Bit 51 = System Timer						*/
													/* ... 											*/
#define		kSCSI9IntMask			0x00000080		/* Bit 39 = SCSI 9 								*/
#define		kSCSI8IntMask			0x00000040		/* Bit 38 = SCSI 8 								*/
#define		kSCSI7IntMask			0x00000020		/* Bit 37 = SCSI 7 								*/
#define		kSCSI6IntMask			0x00000010		/* Bit 36 = SCSI 6 								*/
#define		kSCSI5IntMask			0x00000008		/* Bit 35 = SCSI 5 								*/
#define		kSCSI4IntMask			0x00000004		/* Bit 34 = SCSI 4 								*/
#define		kSCSI3IntMask			0x00000002		/* Bit 33 = SCSI 3 								*/
#define		kSCSI2IntMask			0x00000001		/* Bit 32 = SCSI 2 								*/
#define		kSCSI1IntMask			0x80000000		/* Bit 31 = SCSI 1 								*/
#define		kSCSI0IntMask			0x40000000		/* Bit 30 = SCSI 0 								*/
													/* ... 											*/
#define		kAsyncEventIntMask		0x08000000		/* Bit 27 = Asynchronous Event					*/
#define		kTask0DMAIntMask		0x04000000		/* Bit 26 = Wankel Task 0 DMA 					*/
#define		kCudaAsyncRcvIntMask	0x02000000		/* Bit 25 = Cuda Asynchronous Receive 			*/
#define		kCudaXmitSyncRcvIntMask	0x01000000		/* Bit 24 = Cuda Transmit/Synchronous Receive	*/
#define		kISDNRcvBEIntMask		0x00800000		/* Bit 23 = ISDN BE channel Receive 			*/
#define		kISDNXmitBEIntMask		0x00400000		/* Bit 22 = ISDN BE channel Transmit 			*/
#define		kISDNRcvBDIntMask		0x00200000		/* Bit 21 = ISDN BE channel Receive 			*/
#define		kISDNXmitBDIntMask		0x00100000		/* Bit 20 = ISDN BE channel Transmit 			*/
#define		kSCCBInputIntMask		0x00080000		/* Bit 19 = SCC Channel B input 				*/
#define		kSCCBOutputIntMask		0x00040000		/* Bit 18 = SCC Channel B output 				*/
#define		kSCCAInputIntMask		0x00020000		/* Bit 17 = SCC Channel A input 				*/
#define		kSCCAOutputIntMask		0x00010000		/* Bit 16 = SCC Channel A output 				*/
#define		kISDNRcvDIntMask		0x00008000		/* Bit 15 = ISDN D channel Receive 				*/
#define		kISDNXmitDIntMask		0x00004000		/* Bit 14 = ISDN D channel Transmit 			*/
#define		kAudioLineOutIntMask	0x00002000		/* Bit 13 = Audio Line Out 						*/
#define		kAudioLineInIntMask		0x00001000		/* Bit 12 = Audio Line In 						*/
#define		kPhoneCodecOutIntMask	0x00000800		/* Bit 11 = Analog Phone Codec Out 				*/
#define		kPhoneCodecInIntMask	0x00000400		/* Bit 10 = Analog Phone Codec In 				*/
#define		kAudioRightOutIntMask	0x00000200		/* Bit  9 = Audio Right Out 					*/
#define		kAudioRightInIntMask	0x00000100		/* Bit  8 = Audio Right In 						*/
#define		kAudioLeftOutIntMask	0x00000080		/* Bit  7 = Audio Left Out 						*/
#define		kAudioLeftInIntMask		0x00000040		/* Bit  6 = Audio Left In 						*/
#define		kEtherXmitIntMask		0x00000020		/* Bit  5 = Ethernet Transmit					*/
#define		kEtherRcvIntMask		0x00000010		/* Bit  4 = Ethernet Receive					*/
#define		kFloppy2IntMask			0x00000008		/* Bit  3 = Floppy channel #2					*/
#define		kFloppy1IntMask			0x00000004		/* Bit  2 = Floppy channel #1					*/

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	Interrupt register bit indexes:

 */

#define		kWilsonInt				57				/* Wilson								*/

#define		kVideoLineInt			55				/* Video Line							*/

#define		kSystemTimerInt			51				/* System Timer							*/

#define		kSCSI9Int				39				/* SCSI 9 								*/
#define		kSCSI8Int				38				/* SCSI 8 								*/
#define		kSCSI7Int				37				/* SCSI 7 								*/
#define		kSCSI6Int				36				/* SCSI 6 								*/
#define		kSCSI5Int				35				/* SCSI 5 								*/
#define		kSCSI4Int				34				/* SCSI 4 								*/
#define		kSCSI3Int				33				/* SCSI 3 								*/
#define		kSCSI2Int				32				/* SCSI 2 								*/
#define		kSCSI1Int				31				/* SCSI 1 								*/
#define		kSCSI0Int				30				/* SCSI 0 								*/

#define		kAsyncEventInt			27				/* Asynchronous Event					*/
#define		kTask0DMAInt			26				/* Wankel Task 0 DMA 					*/
#define		kCudaAsyncRcvInt		25				/* Cuda Asynchronous Receive 			*/
#define		kCudaXmitSyncRcvInt		24				/* Cuda Transmit/Synchronous Receive	*/
#define		kISDNRcvBEInt			23				/* ISDN BE channel Receive 				*/
#define		kISDNXmitBEInt			22				/* ISDN BE channel Transmit 			*/
#define		kISDNRcvBDInt			21				/* ISDN BE channel Receive 				*/
#define		kISDNXmitBDInt			20				/* ISDN BE channel Transmit 			*/
#define		kSCCBInputInt			19				/* SCC Channel B input 					*/
#define		kSCCBOutputInt			18				/* SCC Channel B output 				*/
#define		kSCCAInputInt			17				/* SCC Channel A input 					*/
#define		kSCCAOutputInt			16				/* SCC Channel A output 				*/
#define		kISDNRcvDInt			15				/* ISDN D channel Receive 				*/
#define		kISDNXmitDInt			14				/* ISDN D channel Transmit 				*/
#define		kAudioLineOutInt		13				/* Audio Line Out 						*/
#define		kAudioLineInInt			12				/* Audio Line In 						*/
#define		kPhoneCodecOutInt		11				/* Analog Phone Codec Out 				*/
#define		kPhoneCodecInInt		10				/* Analog Phone Codec In 				*/
#define		kAudioRightOutInt		9				/* Audio Right Out 						*/
#define		kAudioRightInInt		8				/* Audio Right In 						*/
#define		kAudioLeftOutInt		7				/* Audio Left Out 						*/
#define		kAudioLeftInInt			6				/* Audio Left In 						*/
#define		kEtherXmitInt			5				/* Ethernet Transmit					*/
#define		kEtherRcvInt			4				/* Ethernet Receive						*/
#define		kFloppy2Int				3				/* Floppy channel #2					*/
#define		kFloppy1Int				2				/* Floppy channel #1					*/

#define		kIRQIn					0x00001040		/* External interrupt line status (there are */
													/*	32 external interrupt sources available, */
													/*	and their interrupt lines' states are */
													/* 	reflected in this register, regardless of */
													/* 	the Mask bit settings.  Note that there is */
													/* 	no similar "upstream view" of the 32 */
													/*	INTERNAL interrupt sources */

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	System Timer registers.
	
	The System Timer is a free-running 40-bit counter that runs at 1/4 of the system clock
	speed.  It is initialized to 0 at reset.
	
	Mazda generates a System Timer interrupt when the value of the counter = the value of the
	comparison register (and System Timer interrupts are enabled).

	These are all in kMazdaBase space.
 */

#define		kSysTimerUpr			0x00001058		/* Upper 8 bits of System Timer */
#define		kSysTimerLwr			0x00001060		/* Lower 32 bits of System Timer */
#define		kSysTimerCntUpr			0x00001068		/* Upper 8 bits of comparison value */
#define		kSysTimerCntLwr			0x00001070		/* Lower 32 bits of comparison value */
 
/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Miscellaneous Mazda registers.

	These are all in kMazdaBase space.
 */
 
#define		kMemReady				0x00001048		/* 1-bit flag that indicates that XJS memory */
													/* 	is ready & has been sized & initialized */
													
/* ==============================================================================================
	Low-speed Bus devices.

	All accesses to devices on the Low-speed Bus must be 32- or 64-bit accesses, and they
	must be on EVEN 32-bit word addresses (e.g., [A2:A0] = 000).

	Bits 4-3 of an access address indicate how many wait states should be inserted for each 
	access to the Low-speed device:
	
							[A4:A3]		Low Speed Bus Cycle
							------- 	-------------------
							ÊÊÊ0		120ns (6 20ns clocks)
				ÊÊÊ			ÊÊÊ1		160ns (8 20ns clocks)
				ÊÊÊ			ÊÊÊ2		200ns (10 20ns clocks)
				ÊÊÊ			ÊÊÊ3		240ns (12 20ns clocks)
					
	Bits 23-21 of an access address select which one of the 8 Low-speed devices to access.
	
	Note that these special bit groups in the address CHANGE POSITION in Mazda II.
	
 */
 
/* ..............................................................................................
	System EEPROM.
	
	See above for special characteristics of Low-speed Bus device accesses.
		
	This device begins at kMazdaEEPROMBase.
 */

#define		kMazdaROMBase			kMazdaEEPROMBase
#define		kMazdaROMTop			kMazdaEEPROMBase + 0x00FFFFFF
 
/* ..............................................................................................
	Device 1 - Endeavor.
 */
 
#define		kEndeavorMReg			0x00200018
#define		kEndeavorNReg			0x00200038

#define		kEndeavorClkSelect		0x00200058
#define		kCLKA					0x00000000
#define		kCLKB					0x00000080

/* ..............................................................................................
	Alternate Device 1 - NS8531.
 */

#define		kNS8531NHCnt0			0x00200018		/* Are we actually going to use this part? */
#define		kNS8531NHCnt1			0x00200038		/* 	If so, maybe some better names for these */
#define		kNS8531NHCnt2			0x00200058		/*  registers could be thought up. */
#define		kNS8531NHCnt3			0x00200078

#define		kNS8531RCnt0			0x00200098
#define		kNS8531RCnt1			0x002000B8
#define		kNS8531RCnt2			0x002000D8

#define		kNS8531SCnt				0x002000F8

#define		kNS8531LCnt				0x00200118

#define		kNS8531PCnt				0x00200138

#define		kNS8531ClkLPFSel		0x00200158

#define		kNS8531NHSEnables		0x00200178

#define		kNS8531VCOIRING			0x00200198

#define		kNS8531LRClkEnables		0x002001B8

#define		kNS8531SDLY				0x002001D8

#define		kNS8531GDLY				0x002001F8

/* ..............................................................................................
	Device 2 - AC/DC.
	
	There are known bugs in accessing AC/DC.  Dummy reads must be done after writing to PBCR0
	and PBCR1.
 */
 
#define		kAcDcWriteAddr			0x00400018
#define		kAcDcWriteRGBCLUT		0x00400038
#define		kAcDcWritePixelCtl		0x00400058
#define		kAcDcWriteRGBTest		0x00400078

#define		kAcDcReadAddr			0x00400018
#define		kAcDcReadRGBCLUT		0x00400038
#define		kAcDcReadPixelCtl		0x00400058
#define		kAcDcReadRGBTest		0x00400078

#define		kPBCR0					0x00000000
#define		kPBCR1					0x00000001

/* ..............................................................................................
	Device 3 - Genlock.
 */
 
		/* NOT IN THIS MAZDA!! */

/* ..............................................................................................
	Device 4 - Ethernet ROM.
 */
 
#define		kEtherROM0				0x00800018		/* Address byte 0 (LSB) */
#define		kEtherROM1				0x00800038		/* Address byte 1 */
#define		kEtherROM2				0x00800058		/* Address byte 2 */
#define		kEtherROM3				0x00800078		/* Address byte 3 */
#define		kEtherROM4				0x00800098		/* Address byte 4 */
#define		kEtherROM5				0x008000B8		/* Address byte 5 (MSB) */
 
/* ..............................................................................................
	Device 5 - Unused.
 */

#define		kLowSpeedDev5			0x00A00000
 
/* ..............................................................................................
	Device 6 - Unused.
 */

#define		kLowSpeedDev6			0x00C00000

/* ..............................................................................................
	Device 7 - Unused.
 */

#define		kLowSpeedDev7			0x00E00000
 

/* ----------------------------------------------------------------------------------------------
	Register offsets for Flatline.
 */
 
/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	RRSR Control Registers.
 */
 
/* ..............................................................................................
	Channel 0.
 */

#define		kSAP0					0x00000000		/* [31:12]	Source Address Page 	*/ 
#define		kSA0					0x00000008		/* [11:0]	Source Address 			*/
#define		kSPriorNStride0			0x00000010		/* [17:14]	Write Priority 			*/
													/* [13:0]	Stride 					*/
#define		kSRPriorNWidth0			0x00000018		/* [17:14]	Read Priority			*/
													/* [13:0]	Width 					*/
#define		kSLength0				0x00000020		/* [23:0]	Length 					*/
#define		kSWidthCount0			0x00000028		/* [13:0]	WidthCount 				*/
#define		kSCtlBits0				0x00000030		/* [4:3] 	Pixel Size 				*/
													/* [2]		Global					*/
													/* [1]		IntPage					*/
													/* [0]		IntLength				*/
#define		kSActive0				0x00000038		/* [31]		Channel Active			*/
#define		kSourceBitAddr0			0x00000040		/* [2:0]	Select a bit from a 	*/
													/*			 byte when in 1bpp mode */
#define		kSIVectNDestPort0		0x00000048		/* [15:12]	Interrupt Vector		*/
													/* [11:0]	Destination Port		*/
#define		kSRate0					0x00000050		/* [15:0]	Transfer Rate 			*/
#define		kSRateCount0			0x00000058		/* [15:0]	Rate Count				*/

/* ..............................................................................................
	Channel 1.
 */
 
#define		kSAP1					0x00000080		/* [31:12]	Source Address Page 	*/ 
#define		kSA1					0x00000088		/* [11:0]	Source Address 			*/
#define		kSPriorNStride1			0x00000090		/* [17:14]	Write Priority 			*/
													/* [13:0]	Stride 					*/
#define		kSRPriorNWidth1			0x00000098		/* [17:14]	Read Priority			*/
													/* [13:0]	Width 					*/
#define		kSLength1				0x000000A0		/* [23:0]	Length 					*/
#define		kSWidthCount1			0x000000A8		/* [13:0]	WidthCount 				*/
#define		kSCtlBits1				0x000000B0		/* [4:3] 	Pixel Size 				*/
													/* [2]		Global					*/
													/* [1]		IntPage					*/
													/* [0]		IntLength				*/
#define		kSActive1				0x000000B8		/* [31]		Channel Active			*/
#define		kSourceBitAddr1			0x000000C0		/* [2:0]	Select a bit from a 	*/
													/*			 byte when in 1bpp mode */
#define		kSIVectNDestPort1		0x000000C8		/* [15:12]	Interrupt Vector		*/
													/* [11:0]	Destination Port		*/
#define		kSRate1					0x000000D0		/* [15:0]	Transfer Rate 			*/
#define		kSRateCount1			0x000000D8		/* [15:0]	Rate Count				*/

/* ..............................................................................................
	Channel 2.
 */
 
#define		kSAP2					0x00000100		/* [31:12]	Source Address Page 	*/ 
#define		kSA2					0x00000108		/* [11:0]	Source Address 			*/
#define		kSPriorNStride2			0x00000110		/* [17:14]	Write Priority 			*/
													/* [13:0]	Stride 					*/
#define		kSRPriorNWidth2			0x00000118		/* [17:14]	Read Priority			*/
													/* [13:0]	Width 					*/
#define		kSLength2				0x00000120		/* [23:0]	Length 					*/
#define		kSWidthCount2			0x00000128		/* [13:0]	WidthCount 				*/
#define		kSCtlBits2				0x00000130		/* [4:3] 	Pixel Size 				*/
													/* [2]		Global					*/
													/* [1]		IntPage					*/
													/* [0]		IntLength				*/
#define		kSActive2				0x00000138		/* [31]		Channel Active			*/
#define		kSourceBitAddr2			0x00000140		/* [2:0]	Select a bit from a 	*/
													/*			 byte when in 1bpp mode */
#define		kSIVectNDestPort2		0x00000148		/* [15:12]	Interrupt Vector		*/
													/* [11:0]	Destination Port		*/
#define		kSRate2					0x00000150		/* [15:0]	Transfer Rate 			*/
#define		kSRateCount2			0x00000158		/* [15:0]	Rate Count				*/

/* ..............................................................................................
	Channel 3.
 */
 
#define		kSAP3					0x00000180		/* [31:12]	Source Address Page 	*/ 
#define		kSA3					0x00000188		/* [11:0]	Source Address 			*/
#define		kSPriorNStride3			0x00000190		/* [17:14]	Write Priority 			*/
													/* [13:0]	Stride 					*/
#define		kSRPriorNWidth3			0x00000198		/* [17:14]	Read Priority			*/
													/* [13:0]	Width 					*/
#define		kSLength3				0x000001A0		/* [23:0]	Length 					*/
#define		kSWidthCount3			0x000001A8		/* [13:0]	WidthCount 				*/
#define		kSCtlBits3				0x000001B0		/* [4:3] 	Pixel Size 				*/
													/* [2]		Global					*/
													/* [1]		IntPage					*/
													/* [0]		IntLength				*/
#define		kSActive3				0x000001B8		/* [31]		Channel Active			*/
#define		kSourceBitAddr3			0x000001C0		/* [2:0]	Select a bit from a 	*/
													/*			 byte when in 1bpp mode */
#define		kSIVectNDestPort3		0x000001C8		/* [15:12]	Interrupt Vector		*/
													/* [11:0]	Destination Port		*/
#define		kSRate3					0x000001D0		/* [15:0]	Transfer Rate 			*/
#define		kSRateCount3			0x000001D8		/* [15:0]	Rate Count				*/

/* ..............................................................................................
	Channel 4.
 */
 
#define		kSAP4					0x00000200		/* [31:12]	Source Address Page 	*/ 
#define		kSA4					0x00000208		/* [11:0]	Source Address 			*/
#define		kSPriorNStride4			0x00000210		/* [17:14]	Write Priority 			*/
													/* [13:0]	Stride 					*/
#define		kSRPriorNWidth4			0x00000218		/* [17:14]	Read Priority			*/
													/* [13:0]	Width 					*/
#define		kSLength4				0x00000220		/* [23:0]	Length 					*/
#define		kSWidthCount4			0x00000228		/* [13:0]	WidthCount 				*/
#define		kSCtlBits4				0x00000230		/* [4:3] 	Pixel Size 				*/
													/* [2]		Global					*/
													/* [1]		IntPage					*/
													/* [0]		IntLength				*/
#define		kSActive4				0x00000238		/* [31]		Channel Active			*/
#define		kSourceBitAddr4			0x00000240		/* [2:0]	Select a bit from a 	*/
													/*			 byte when in 1bpp mode */
#define		kSIVectNDestPort4		0x00000248		/* [15:12]	Interrupt Vector		*/
													/* [11:0]	Destination Port		*/
#define		kSRate4					0x00000250		/* [15:0]	Transfer Rate 			*/
#define		kSRateCount4			0x00000258		/* [15:0]	Rate Count				*/

/* ..............................................................................................
	Channel 5.
 */
 
#define		kSAP5					0x00000280		/* [31:12]	Source Address Page 	*/ 
#define		kSA5					0x00000288		/* [11:0]	Source Address 			*/
#define		kSPriorNStride5			0x00000290		/* [17:14]	Write Priority 			*/
													/* [13:0]	Stride 					*/
#define		kSRPriorNWidth5			0x00000298		/* [17:14]	Read Priority			*/
													/* [13:0]	Width 					*/
#define		kSLength5				0x000002A0		/* [23:0]	Length 					*/
#define		kSWidthCount5			0x000002A8		/* [13:0]	WidthCount 				*/
#define		kSCtlBits5				0x000002B0		/* [4:3] 	Pixel Size 				*/
													/* [2]		Global					*/
													/* [1]		IntPage					*/
													/* [0]		IntLength				*/
#define		kSActive5				0x000002B8		/* [31]		Channel Active			*/
#define		kSourceBitAddr5			0x000002C0		/* [2:0]	Select a bit from a 	*/
													/*			 byte when in 1bpp mode */
#define		kSIVectNDestPort5		0x000002C8		/* [15:12]	Interrupt Vector		*/
													/* [11:0]	Destination Port		*/
#define		kSRate5					0x000002D0		/* [15:0]	Transfer Rate 			*/
#define		kSRateCount5			0x000002D8		/* [15:0]	Rate Count				*/

/* ..............................................................................................
	Channel 6.
 */
 
#define		kSAP6					0x00000300		/* [31:12]	Source Address Page 	*/ 
#define		kSA6					0x00000308		/* [11:0]	Source Address 			*/
#define		kSPriorNStride6			0x00000310		/* [17:14]	Write Priority 			*/
													/* [13:0]	Stride 					*/
#define		kSRPriorNWidth6			0x00000318		/* [17:14]	Read Priority			*/
													/* [13:0]	Width 					*/
#define		kSLength6				0x00000320		/* [23:0]	Length 					*/
#define		kSWidthCount6			0x00000328		/* [13:0]	WidthCount 				*/
#define		kSCtlBits6				0x00000330		/* [4:3] 	Pixel Size 				*/
													/* [2]		Global					*/
													/* [1]		IntPage					*/
													/* [0]		IntLength				*/
#define		kSActive6				0x00000338		/* [31]		Channel Active			*/
#define		kSourceBitAddr6			0x00000340		/* [2:0]	Select a bit from a 	*/
													/*			 byte when in 1bpp mode */
#define		kSIVectNDestPort6		0x00000348		/* [15:12]	Interrupt Vector		*/
													/* [11:0]	Destination Port		*/
#define		kSRate6					0x00000350		/* [15:0]	Transfer Rate 			*/
#define		kSRateCount6			0x00000358		/* [15:0]	Rate Count				*/

/* ..............................................................................................
	Channel 7.
 */
 
#define		kSAP7					0x00000380		/* [31:12]	Source Address Page 	*/ 
#define		kSA7					0x00000388		/* [11:0]	Source Address 			*/
#define		kSPriorNStride7			0x00000390		/* [17:14]	Write Priority 			*/
													/* [13:0]	Stride 					*/
#define		kSRPriorNWidth7			0x00000398		/* [17:14]	Read Priority			*/
													/* [13:0]	Width 					*/
#define		kSLength7				0x000003A0		/* [23:0]	Length 					*/
#define		kSWidthCount7			0x000003A8		/* [13:0]	WidthCount 				*/
#define		kSCtlBits7				0x000003B0		/* [4:3] 	Pixel Size 				*/
													/* [2]		Global					*/
													/* [1]		IntPage					*/
													/* [0]		IntLength				*/
#define		kSActive7				0x000003B8		/* [31]		Channel Active			*/
#define		kSourceBitAddr7			0x000003C0		/* [2:0]	Select a bit from a 	*/
													/*			 byte when in 1bpp mode */
#define		kSIVectNDestPort7		0x000003C8		/* [15:12]	Interrupt Vector		*/
													/* [11:0]	Destination Port		*/
#define		kSRate7					0x000003D0		/* [15:0]	Transfer Rate 			*/
#define		kSRateCount7			0x000003D8		/* [15:0]	Rate Count				*/

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	RRDR Control Registers.
 */
 
/* ..............................................................................................
	Channel 0.
 */

#define		kDAP0					0x00001000		/* [31:12]	Destination Addr Page	*/
#define		kDA0					0x00001008		/* [11:0]	Destination Address		*/
#define		kDPriorNStride0			0x00001010		/* [17:14]	Priority				*/
													/* [3:0]	Stride					*/
#define		kDPixTypeNWidth0		0x00001018		/* [17:16]	Receive Pixel Type		*/
													/* [15:14]	Output Pixel Type		*/
													/* [13:0]	Width					*/
#define		kDLength0				0x00001020		/* [23:0]	Length					*/
#define		kDDithTogNWidthCnt0		0x00001028		/* [14]		Dither Toggle			*/
													/* [13:0]	Width Count				*/
#define		kDCtlBits0				0x00001030		/* [11]		Toggle at line end		*/
													/* [10]		Toggle status			*/
													/* [9:6]	Interrupt vector		*/
													/* [5]		Clip alpha = 0 pixels	*/
													/* [4]		Store Intensity			*/
													/* [3]		Store Alpha				*/
													/* [2]		Global XJS transactions	*/
													/* [1]		Int on page crossing	*/
													/* [0]		Int on Length = 0		*/	
#define		kDActiveNFlush0			0x00001038		/* [31]		Channel Active			*/
													/* [30]		Flush channel buffers	*/
 
/* ..............................................................................................
	Channel 1.
 */
 
#define		kDAP1					0x00001080		/* [31:12]	Destination Addr Page	*/
#define		kDA1					0x00001088		/* [11:0]	Destination Address		*/
#define		kDPriorNStride1			0x00001090		/* [17:14]	Priority				*/
													/* [3:0]	Stride					*/
#define		kDPixTypeNWidth1		0x00001098		/* [17:16]	Receive Pixel Type		*/
													/* [15:14]	Output Pixel Type		*/
													/* [13:0]	Width					*/
#define		kDLength1				0x000010A0		/* [23:0]	Length					*/
#define		kDDithTogNWidthCnt1		0x000010A8		/* [14]		Dither Toggle			*/
													/* [13:0]	Width Count				*/
#define		kDCtlBits1				0x000010B0		/* [11]		Toggle at line end		*/
													/* [10]		Toggle status			*/
													/* [9:6]	Interrupt vector		*/
													/* [5]		Clip alpha = 0 pixels	*/
													/* [4]		Store Intensity			*/
													/* [3]		Store Alpha				*/
													/* [2]		Global XJS transactions	*/
													/* [1]		Int on page crossing	*/
													/* [0]		Int on Length = 0		*/	
#define		kDActiveNFlush1			0x000010B8		/* [31]		Channel Active			*/
													/* [30]		Flush channel buffers	*/
 
/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Mu Ports.
 */
 
/* ..............................................................................................
	Splicer Control Registers.
 */

#define		kSpliceDestPort			0x00002000		/*	[11:0]	Destination port		*/
#define		kSpliceCtlRegs			0x00002008		/*	[11:8]	Priority				*/
													/*	[7]		Double					*/
													/*	[6]		Stream #1 only			*/
													/*	[5:3]	Stream #2 format		*/
													/*	[2:0]	Stream #1 format		*/
#define		kSpliceFlush			0x00002010		/*	[3]		Flush Stream #2, Ch 1	*/
													/*	[2]		Flush Stream #1, Ch 1	*/
													/*	[1]		Flush Stream #2, Ch 0	*/
													/*	[0]		Flush Stream #1, Ch 0	*/
#define		kSpliceClutEntries		0x00002800		/*	[23:0]	Clut Entries			*/

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Flatline Interrupt Control Registers.
	
	The 4-bit interrupt vector value in the RRSR/RRDR IVECT registers selects which of
	the 16 interrupts that device sources.
	
	RRSR Read Error interrupts are hard-coded to interrupt bit 0.
	
	A write to the range 0x8fffff0x - 0x8ffffffx will generate an interrupt.  The interrupt
	bit used is selected by the high nybble of the low byte of the address.
 */
 
#define		kFlatIRQMask			0x00005000		/* [15:0]	Interrupt Mask			*/
#define		kFlatIRQUpstream		0x00005010		/* [15:0]	Raw interrupt bits		*/
#define		kFlatIRQPend			0x00005020		/* [15:0]	Masked Interrupt bits	*/

#define		kFlatWriteInt0			0x00FFFF00		/* Write to generate interrupt 0	*/
#define		kFlatWriteInt1			0x00FFFF10		/* Write to generate interrupt 1	*/
#define		kFlatWriteInt2			0x00FFFF20		/* Write to generate interrupt 2	*/
#define		kFlatWriteInt3			0x00FFFF30		/* Write to generate interrupt 3	*/
#define		kFlatWriteInt4			0x00FFFF40		/* Write to generate interrupt 4	*/
#define		kFlatWriteInt5			0x00FFFF50		/* Write to generate interrupt 5	*/
#define		kFlatWriteInt6			0x00FFFF60		/* Write to generate interrupt 6	*/
#define		kFlatWriteInt7			0x00FFFF70		/* Write to generate interrupt 7	*/
#define		kFlatWriteInt8			0x00FFFF80		/* Write to generate interrupt 8	*/
#define		kFlatWriteInt9			0x00FFFF90		/* Write to generate interrupt 9	*/
#define		kFlatWriteInt10			0x00FFFFA0		/* Write to generate interrupt 10	*/
#define		kFlatWriteInt11			0x00FFFFB0		/* Write to generate interrupt 11	*/
#define		kFlatWriteInt12			0x00FFFFC0		/* Write to generate interrupt 12	*/
#define		kFlatWriteInt13			0x00FFFFD0		/* Write to generate interrupt 13	*/
#define		kFlatWriteInt14			0x00FFFFE0		/* Write to generate interrupt 14	*/
#define		kFlatWriteInt15			0x00FFFFF0		/* Write to generate interrupt 15	*/

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	XJS Control Registers.
 */

#define		kXJSCtl					0x00007000		/* [3]		Deadlock Enable 		*/
													/* [2:0]	XJS Priority			*/

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Debug Control Registers.
 */

#define		kDebugCtlRegs			0x00008000		/* [15]		Soft Reset RRSR			*/
													/* [14]		Soft Reset RRDR			*/
													/* [13]		Soft Reset Splicer		*/
													/* [12]		Soft Reset BLT 			*/
													/* [8]		Debug Mode				*/
													/* [7:5]	Debug Unit Select		*/
													/* [4:0]	Debug Signal Select		*/

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	System Control Registers.
 */
 
#define		kScrnAddr				0x00009000		/* [22:0]	Screen base address		*/
#define		kCrsrAddr				0x00009008		/* [25:0]	Cursor address reg		*/
#define		kScrnRowBytes			0x00009010		/* [12:0]	Screen RowBytes			*/
#define		kCrsrRowBytes			0x00009018		/* [12:0]	Cursor RowBytes			*/
#define		kDRAMCtlRegs			0x00009020		/* [13]		Video Xfer Size			*/
													/* [12:10]	DRAM Max Refresh Reg	*/
													/* [9:0]	DRAM Refresh Count		*/

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Pixel Ports.
 */
 
#define		kRRDR01Base				0x00FFE000		/* RRDR Ports 0-1					*/
#define		kSplicerPort03Base		0x00FFE100		/* Mu Ports 0-3 (Splicer)			*/


/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Hurricane Utility Space.
	
	Put #defines, typedefs, and prototypes for your utility routines here!
	
	History
	-------
			JFB			4-15-92			Added Memory Management utils info.
 */	
 		
/* ----------------------------------------------------------------------------------------------
	Defines used by the Hurricane memory management routines.
 */

#define		kAddrUnreachable		0xFFFFFFFF		/* used by Native2Nub to indicate that */
													/*  the specified address does not map */
													/*  to a Nub-reachable address.		   */

#define		kNumMasters				100				/* Number of Master Pointers initially */
													/*  allocated to this Heap Zone */
										
#define		kUpperLimit				0xE0400000		/* Highest address in this Heap Zone (4 Megs)	*/
													/*  (jed's pseudo-ROM starts here 				*/
													/*  (we can move this up after we see how much 	*/
													/*   room he really needs) 						*/
													
#define		kStartAddr				0xE0200100		/* Start of this Heap Zone (this ensures 		*/
													/*  that there is enuf room for a 24 bpp 		*/
													/*  goldfish (832x624) starting @ 0) 			*/

#define		kValidHeaps				0xE0200000		/* Signature to signal that memory Manager has been inited 		*/
#define		kNextHeap				0xE0200004		/* Pointer to allocate the next heap zone 		*/
#define		kHeapLock				0xE0200008		/* Locking semaphore to make Memory Manager re-entrant 		*/

#define		kValidInts				0xE020000C		/* Signature to signal that interrupt Manager has been inited 		*/
#define		kIntTable				0xE0200010		/* Pointer to the interrupt vector table 		*/
#define		kIntSlotQueue			0xE0200014		/* Pointer to the interrupt slot queue element 		*/

/* ----------------------------------------------------------------------------------------------
	Hurricane Data Types.
 */

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Channel Command Data Structures.
 */
 
typedef Ptr CCPtr;									/* Pointer to a Channel Command buffer */

typedef struct dmaCC {
					char	command;
					char	flags;
					int		count;
					long	address;
					} dmaCC, *dmaCCPtr;
					
typedef struct regCC {
					char	command;
					char	flags;
					int		reg;
					long	data;
					} regCC, *regCCPtr;

/* ----------------------------------------------------------------------------------------------
	Utility routine prototypes.
 */

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Routines to initialize & use Hurricane memory via a Mac-style heap.
 */
 
//void InitHurricaneMemMgr( void );
 										
//THz InitHurricaneHeap(unsigned short numMasters, unsigned long heapSize);	/* Set up a heap that the Mac Mem Mgr can use */

//CCPtr NewCCPtr(unsigned short numCCsDesired);		/* Get a pointer to a 64-bit aligned hunk of mem */

//void DisposCCPtr(CCPtr theBuf);						/* Free a pointer to a 64-bit aligned hunk of mem */

//unsigned long Nub2Native(unsigned long NubAddr);		/* Translate a Nub address to a Hurricane address */

//unsigned long Native2Nub(unsigned long NativeAddr);		/* Translate a Hurricane address to a Nub address */

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Routines to write/read an IOM register via a single Mazda Channel Command.
 */
 										
void IOMWriteReg(unsigned short IOMID, char Flags, unsigned short RegAddr, 
											unsigned short ByteCount, long Data, long *theCCP);
 
long IOMReadReg(unsigned short IOMID, char Flags, unsigned short RegAddr, 
											unsigned short ByteCount, long *theCCP);

/* ----------------------------------------------------------------------------------------------
	Miscellaneous addresses that you may want to change.
 */
 
#define		kScrnBase				0x00200000
#define		kRowBytes8				0x00000280
#define		kRowBytes16				0x00000500
#define		kRowBytes24				0x00000A00

#define		k8bpp					0
#define		k16bpp					1
#define		k24bpp					2
 	


	
	
	
 	