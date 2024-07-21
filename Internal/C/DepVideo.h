/*
	File:		DepVideo.h

 	Contains:	These are the configuration ROM equates that are specific only to 
 				built-in video.  This includes mode information, sResource IDs,
 				etc., etc….

	Written by:	Fernando Urbina

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	  6/9/93	kc		first checked in
	   <LW7>	 4/29/93	fau		#1082085:  Added a bit to the Cyclone slotPRAM flags to indicate
									whether the "Boot on composite" should be NTSC or PAL.
	   <LW6>	 4/14/93	fau		Added the renumbered private control codes for Civic, plus some
									new structures.
	   <LW5>	 4/13/93	ejb		add the commas
	   <LW4>	 4/13/93	ejb		uncomment the new spFalgs bits for sound settings
	   <LW3>	  4/9/93	fau		Moved the spOpenComponent to 3 (from 6) and added the SpParams
									structure.
	   <LW2>	  4/5/93	fau		Changed the Cyclone-specific calls from the public area to the
									private area.  Added the definition of structures that were in
									the VDig .
		 <1>	  1/4/93	fau		first checked in

*/

enum {
 
 	/* SpFlags byte of Slot 0 PRAM for Civic-based CPU's */
	
 	spVideoIn = 0,
	spCompOut = 1,
	spCompOutPAL = 2,																			// <LW7>
	spOpenComponent = 3,
	
	/* Note:  The Built-in sound sifter uses bits 4-7 of the SP_Flags byte for Slot 0 PRAM.
			  
		Bit5	Bit4
		  0		  0			Selects sample rate of 24 KHz.
		  0       1         Selects sample rate of 48 KHz.
		  1       0			Selects sample rate of 22.05 KHz.
		  1       1         Selects sample rate of 44.1 KHz.
		  
		Bit6	  0         Sound Playthrough OFF
		  		  1         Sound Playthrough ON
				  
	 	Bit7	  0			Sound Input Source is External Mike/Line Input
		  		  1			Sound Input Source is Internal CD.
				  	
	*/

	spSampleRate = 4,		
	spClockRate = 5,			
	spPlayThrough = 6,		
	spMikeOrCDInput = 7,		

/* Additional Control Codes */

	cscSetCompositeOut	=		133,			/* Used by CivicDriver for setting/clearing the PRAM flag for composite out */ 
	cscSetRGBBypass		=		135,			/* Used by CivicDriver for bypassing RGB outputs (enabling composite-out) on Civic. */
	cscSetVidInMode		=		137,			/* Used by CivicDriver for selecting the video-in mode. */
	cscSetVidInRect		=		138,			/* Used by CivicDriver for specifying the destination Rect for Video-in. */
	
	cscGetCompositeOut	=		133,			/* Used by CivicDriver for getting the status of the PRAM flag for composite out */ 
	cscGetRGBBypass		=		135,			/* Used by CivicDriver for getting the status of the RGB outputs. */ 
	cscGetVideoIn		=		136,			/* Used by CivicDriver for getting the video-in status. */
	cscGetVidInMode		=		137,			/* Used by CivicDriver for getting the video-in mode. */
	cscGetVidInRect		=		138,			/* Used by CivicDriver for getting the destination Rect for Video-in. */
	cscGetCompCapab		=		139				/* Used by CivicDriver for getting the available composite capabilities for the current monitor */

};

typedef	struct ScrnRecord {
	short		srDrvrHW;
	short		srSlot;
	long		srDCtlDevBase;
	short		srMode;
	short		srFlagMask;
	short		srFlags;
	short		srColorTable;
	short		srGammaTable;
	Rect		srRect;
	short		srCtlCount;
};
typedef struct ScrnRecord ScrnRecord;
typedef ScrnRecord *ScrnRecordPtr;

typedef struct ScrnRsrc {
	short		count;
	ScrnRecord	scrnRecs[6];
};

typedef struct ScrnRsrc	ScrnRsrc;
typedef ScrnRsrc *ScrnRsrcPtr, **ScrnRsrcHandle;
typedef struct VDVidInRect
	{
	Rect	csRect;
	short	csPage;
	long	csBaseAddr;
	};
		
typedef struct VDVidInRect VDVidInRect;
typedef VDVidInRect *VDVidInRectPtr;	


typedef struct VDFlag
{
	unsigned char		csMode;

};

typedef struct VDFlag VDFlag;
typedef struct VDFlag *VDFlagPtr;

typedef struct VDInternalInfo
{
	Boolean		csMode;
	Byte		csNTSCID;
	Byte		csNTSCIDConv;
	Byte		csPALID;
	Byte		csPALIDConv
};

typedef struct VDInternalInfo VDInternalInfo;
typedef VDInternalInfo *VDInternalInfoPtr;

typedef	struct SpParams
{
	unsigned short	SpBoardID;		// Board ID
	unsigned char	SpDepth;		// spID of Depth (mode)
	unsigned char	SpLastConfig;	// spID of last boot-up Configuration
	unsigned char	SpDfltConfig;	// spID of default configuration
	unsigned char	SpMonID;		// Sense Code of last display
	unsigned char	SpFlags;		// Miscellaneous flags
	unsigned char	SpAltSense;		// Alternate senseID byte
};

typedef struct SpParams SpParams;
typedef SpParams *SpParamsPtr;

