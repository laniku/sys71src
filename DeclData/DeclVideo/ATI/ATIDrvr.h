/*
	File:		ATIDrvr.h

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
*Name:		ATIDrvr.h
*Creator:	George D. Wilson Jr.
*Date:		3/17/92
*
*Purpose:	Contains structures and defines for the RISC video driver.
*
*Category:	Header File
*File:		ATIDrvr.h
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

#define	ATI						1			// Indicate we are for ATI hardware

#define	kNumPages				1			// Number of video pages
#define	kOurVidPage				0			// The video page we use  Always 0 on Quadra
#define	kVBLInterruptEnabled	0			// VBL interrupts enabled return value
#define	kVBLInterruptDisabled	1			// VBL interrupts disenabled return value
#define	kDAFBHWID				0x001C		// DAFB hardware device ID

#define	kRowBytes138bpp			0x400		// Apple 13" rowbytes 8bpp
// #define	kRowBytes1316bpp		0x500		// Apple 13" rowbytes 16bpp
// #define	kRowBytes1324bpp		0xA00		// Apple 13" rowbytes 24bpp

#define	kNumLines480			480			//

#define	kNumCLUTEntries			256			// Number of entries in the CLUT

#define	kSuper9					0x90000000
#define	kSuperA					0xA0000000
#define	kSuperB					0xB0000000
#define	kSuperC					0xC0000000
#define	kSuperD					0xD0000000
#define	kSuperE					0xE0200000

#define	 kSlot9					0x09000000
#define	 kSlotA					0x0A000000
#define	 kSlotB					0x0B000000
#define	 kSlotC					0x0C000000
#define	 kSlotD					0x0D000000
#define	 kSlotE					0x0E000000

#define	kMySlot					kSlotE		// Used to access ATI with Nub601

#ifdef ROM
#define	kMySlot8				0x00		// Used to access ATI sResource structs
#else
#define	kMySlot8				0x0E		// Used to access ATI with Nub601
#endif

#define	kMySuperSlot			kSuperE		// Used to access ATI with Nub601

#define	kFirstVideoMode			0x80
#define	kSecondVideoMode		0x81
#define	kThirdVideoMode			0x82
#define	kFourthVideoMode		0x83
#define	kFifthVideoMode			0x84 
#define	kSixthVideoMode			0x85

//===============================================================================
//	Below are the bit patterns to write into memory for each of the supported
//	bit depths.
//===============================================================================

#define	kOneBitPattern			0xAAAAAAAA
#define	kTwoBitPattern			0xCCCCCCCC
#define	kFourBitPattern			0xF0F0F0F0
#define	kEightBitPattern		0xFF00FF00
#define	kSixTeenBitPattern		0xFFFF0000
#define	kThirtyTwoBitPattern	0xFFFFFFFF

#define	kGrayCLUTValue			0x00808080	// Value to gray the CLUT

#define	kRedLumValue			0x4CCC
#define	kGreenLumValue			0x970A
#define	kBlueLumValue			0x1C29

//===============================================================================
//	The following definitions define the number of long word writes to
//	to do to fill one line of video on the 13" monitor.
//	This should be changed later to be monitor indepentent.
//===============================================================================
#define	kOneBitBytes			0x14		// Number of long writes for one bpp
#define	kTwoBitBytes			0x28		// Number of long writes for two bpp
#define	kFourBitBytes			0x50		// Number of long writes for four bpp
#define	kEightBitBytes			0xA0		// Number of long writes for eight bpp
#define	kSixTeenBitBytes		0x140		// Number of long writes for sixteen bpp
#define	kThirtyTwoBitBytes		0x280		// Number of long writes for thirty two bpp

#define	kMonoDevice				0x01		// Monochrome device
#define	kNonMonoDevice			0x00		// Non luminance mapping device

// #define	kNumLines				480			// Number of lines on a 13"

//==========================================================================
//	Sense line decode values
//==========================================================================
#define	kSenseLineReset			0x00000007	// Drives all lines low
#define	kSenseLineAMask			0x00000006	// Drives the A bit
#define	kSenseLineBMask			0x00000005	// Drives the B bit
#define	kSenseLineCMask			0x00000003	// Drives the C bit
#define	kSenseLineMask			0x00000070	// Only the first three bits are used

#define	kMonitorNotConnected	0x07		// No monitor or extended value

#define	kRGB21					0x00		// 21" RGB display 1152x870 100.0 MHz
#define	kFullPage				0x01		// Full page display 640x870 57.28 MHz
#define	kRGB12					0x02		// 12" RGB display 512x384 15.67 MHz
#define	kTwoPage				0x03		// Two page display 1152x870 100.0 MHz
#define	kNTSC					0x04		// NTSC display varxvar 12.27 MHz
#define	kRGB15					0x05		// 15" RGB display 640x870 57.28 MHz
#define	kRGB1312				0x06		// Hi-Res 13" & 12" displays 30.24 MHz

#define k16SenseACode			0x02		// Value received from A mask
#define k16SenseBCode			0x05		// Value received from B mask
#define k16SenseCCode			0x02		// Value received from C mask

//==========================================================================
//	Slot manager defines for the timing sResources
//==========================================================================
#define	kATIVidParmSpId	0x7E		// Resource id for the all ATI video systems

#define	kNoMonitorConnected		0xFF		// No Monitor connected to system
#define	kRGB1312Connected		0x80		// Hi-Res sRsrc ID
#define	kRGB16Connected			0x81		// 16" sRsrc ID
#define	kRGB21Connected			0x82		//  sRsrc ID
#define	kFullPageConnected		0x83		//  sRsrc ID
#define	kRGB12Connected			0x84		//  sRsrc ID
#define	kTwoPageConnected		0x85		//  sRsrc ID
#define	kNTSCConnected			0x86		//  sRsrc ID
#define	kRGB15Connected			0x87		//  sRsrc ID

#define	kEndeavorParmSpId		0x80		// Resource id of Endeavor SBlock
#define	kACDCParmSpId			0x81		// Resource id of ACDC SBlock
#define	kSwatchParmSpId			0x82		// Resource id of Swatch SBlock

//==========================================================================
//	Definition of default mode data structure
//==========================================================================
struct VDDefMode {
    UInt8 csID;
};

typedef struct VDDefMode VDDefMode;
typedef VDDefMode *VDDefModePtr, **VDDefModeHandle;

#define	kVDDefModeSize	(sizeof(VDDefMode))

//==========================================================================
//	Exported status routines
//==========================================================================
OSErr	DoGetBaseAddr(VDPgInfoPtr pgPtr, DCtlPtr dce);
OSErr	DoGetDefaultMode(VDDefModePtr dfPtr, DCtlPtr dce);
OSErr	DoGetEntries(VDSetEntryPtr pgPtr, DCtlPtr dce);
OSErr	DoGetGamma(VDGamRecPtr gPtr, DCtlPtr dce);
OSErr	DoGetGray(VDGrayPtr pgPtr, DCtlPtr dce);
OSErr	DoGetInterrupt(VDPgInfoPtr flgPtr, DCtlPtr dce);
OSErr	DoGetMode(VDPgInfoPtr pgPtr, DCtlPtr dce);
OSErr	DoGetPages(VDPgInfoPtr pgPtr, DCtlPtr dce);

//==========================================================================
//	Exported control routines
//==========================================================================
OSErr	DoVideoReset(VDPgInfoPtr pgPtr, DCtlPtr dce);
OSErr	DoSetVideoMode(VDPgInfoPtr pgPtr, DCtlPtr dce);
OSErr	DoSetEntries(VDSetEntryPtr pgPtr, DCtlPtr dce);
OSErr	DoSetGamma(VDGamRecPtr pgPtr, DCtlPtr dce);
OSErr	DoGrayPage(VDPgInfoPtr pgPtr, DCtlPtr dce);
OSErr	DoSetGray(VDGrayPtr pgPtr, DCtlPtr dce);
OSErr	DoSetInterrupt(VDPgInfoPtr pgPtr, DCtlPtr dce);
OSErr	DoDirectSetEntries(VDSetEntryPtr pgPtr, DCtlPtr dce);
OSErr	DoSetDefaultMode(VDDefModePtr dfPtr, DCtlPtr dce);

//==========================================================================
//	Definition of slot manager vendor PRAM data structure
//==========================================================================
struct SPRAMRecord {
    UInt16 boardID;
    UInt8 vendorUse1;
    UInt8 vendorUse2;
    UInt8 vendorUse3;
    UInt8 vendorUse4;
    UInt8 vendorUse5;
    UInt8 vendorUse6;
};

typedef struct SPRAMRecord SPRAMRecord;
typedef SPRAMRecord *SPRAMRecordPtr, **SPRAMRecordHandle;

#define	kSPRAMRecordSize	(sizeof(SPRAMRecord))

//==========================================================================
//	Definition of gamma table data structure
//==========================================================================
struct GammaTable {
    short gVersion;                     // gamma version number
    short gType;                        // gamma data type
    short gFormulaSize;                 // Formula data size
    short gChanCnt;                     // number of channels of data
    short gDataCnt;                     // number of values/channel
    short gDataWidth;                   // bits/corrected value (data packed to next larger byte size)
    char gFormulaData[255*3];			// data for formulas followed by gamma values
};

typedef struct GammaTable GammaTable;
typedef GammaTable *GammaTablePtr, **GammaTableHandle;

#define	kGammaTableSize	(sizeof(GammaTable))

struct ACDCVidParms {
	UInt8		pbcr0ValueFirstMode;
	UInt8		pbcr1ValueFirstMode;
	UInt8		pbcr0ValueSecondMode;
	UInt8		pbcr1ValueSecondMode;
	UInt8		pbcr0ValueThirdMode;
	UInt8		pbcr1ValueThirdMode;
};

typedef	struct	ACDCVidParms		ACDCVidParms;
typedef	struct	ACDCVidParms		*ACDCVidParmsPtr;
typedef	struct	ACDCVidParms		**ACDCVidParmsHdl;

#define	ACDCVIDPARMSSIZE		((UInt32) sizeof(ACDCVidParms))


struct endeavorVidParms {
	UInt8		MRegValue;
	UInt8		NRegValue;
};

typedef	struct	endeavorVidParms		endeavorVidParms;
typedef	struct	endeavorVidParms		*endeavorVidParmsPtr;
typedef	struct	endeavorVidParms		**endeavorVidParmsHdl;

#define	ENDEAVORVIDPARMSSIZE		((UInt32) sizeof(endeavorVidParms))


struct globals {
	GammaTablePtr	gGammaPtr;
	Ptr				gBaseAddr;
	Ptr				gFBBaseAddr;
	Boolean			gInterruptsEnabled;
	Boolean			gMonoOnly;
	Boolean			gLuminanceMode;
	Boolean			gDirectMode;
	UInt16			gNumLines;
	UInt16			gRowBytes;
	UInt16			gCurrentPage;
	UInt32			gBigSlotNum;
	UInt8			gMonitorID;
	UInt8			gSlotNum;
	UInt8			gCurrentMode;
	SlotIntQElement	qElem;
};

typedef	struct	globals		globals;
typedef	struct	globals		*globalsPtr;
typedef	struct	globals		**globalsH;

#define	GLOBALSSIZE		((UInt32) sizeof(globals))

//==========================================================================
//	Utility routines
//==========================================================================
void RemoveInterruptRoutine(DCtlPtr dce);
void InstallInterruptRoutine(DCtlPtr dce);

void DoDisableVideo(UInt32 theSlot);


/*-------------------------------------------------------------------------
*
*							End of Module
*
*-----------------------------------------------------------------------*/
