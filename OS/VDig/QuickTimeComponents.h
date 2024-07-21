
/************************************************************

Created: Saturday, August 17, 1991 at 10:03 AM
 QuickTimeComponents.h
 C Interface to the Macintosh Libraries


 Copyright Apple Computer, Inc. 1991
 All rights reserved



************************************************************/


#ifndef __QUICKTIMECOMPONENTS__
#define __QUICKTIMECOMPONENTS__

#ifndef __COMPONENTS__
#include <Components.h>
#endif

#ifndef __IMAGECOMPRESSION__
#include <ImageCompression.h>
#endif

#ifndef __MOVIES__
#include <Movies.h>
#endif

#ifndef __QUICKDRAW__
#include <QuickDraw.h>
#endif

#ifndef __VIDEO__
#include <Video.h>
#endif


enum {


/*****

 Clock Component

*****/

#define clockComponentType 'clok'
#define systemTickClock 'tick'			/* subtype: 60ths since boot */
#define systemMicrosecondClock 'micr'	/* subtype: 1000000ths since boot */


 kClockRateIsLinear = 1,
 kClockImplementsCallBacks = 2

};

enum {kClockGetClockTimeSelect = 1,kClockSetClockTimeSelect = 2,kClockNewCallBackSelect,
 kClockDisposeCallBackSelect,kClockCallMeWhenSelect,kClockCancelCallBackSelect,
 kClockRateChangedSelect,kClockTimeChangedSelect,kClockSetTimeBaseSelect};
typedef unsigned  ClockComponentSelectors;


#ifdef __cplusplus
extern "C" {
#endif
pascal ComponentResult GetClockTime(ComponentInstance aClock,TimeRecord *out)
 = {0x2F3C,0x4,0x1,0x7000,0xA82A}; 
pascal QTCallBack ClockNewCallBack(ComponentInstance aClock,TimeBase tb,
 short callBackType)
 = {0x2F3C,0x6,0x1,0x7000,0xA82A}; 
pascal ComponentResult ClockDisposeCallBack(ComponentInstance aClock,QTCallBack cb)
 = {0x2F3C,0x4,0x1,0x7000,0xA82A}; 
pascal ComponentResult ClockCallMeWhen(ComponentInstance clock,QTCallBack cb,
 long param1,long param2,long param3)
 = {0x2F3C,0x10,0x1,0x7000,0xA82A}; 
pascal ComponentResult ClockCancelCallBack(ComponentInstance clock,QTCallBack cb)
 = {0x2F3C,0x4,0x1,0x7000,0xA82A}; 
pascal ComponentResult ClockRateChanged(ComponentInstance clock,QTCallBack cb)
 = {0x2F3C,0x4,0x1,0x7000,0xA82A}; 
pascal ComponentResult ClockTimeChanged(ComponentInstance clock,QTCallBack cb)
 = {0x2F3C,0x4,0x1,0x7000,0xA82A}; 
pascal ComponentResult ClockSetTimeBase(ComponentInstance clock,TimeBase tb)
 = {0x2F3C,0x4,0x1,0x7000,0xA82A}; 

#ifdef __cplusplus
}
#endif
enum {


/*
 Video Digitizer Component


  Standard type for video digitizers */

 videoDigitizerComponentType = 'vdig',
 vdigInterfaceRev = 2L,


/* Input Format Standards */

 ntscIn = 0	,						/* ntsc input format */
 palIn = 1	,						/* pal input format */
 secamIn = 2,							/* secam input format */


/* Input Formats */
 compositeIn = 0	,					/* input is composite format */
 sVideoIn = 1	,					/* input is sVideo format */
 rgbComponentIn = 2		,			/* input is rgb component format */
	

/* Video Digitizer PlayThru States */
 vdPlayThruOff = 0,
 vdPlayThruOn = 1,


/* Input Color Space Modes */
 vdDigitizerBW = 0	,				/* black and white */
 vdDigitizerRGB = 1	,				/* rgb color */


/* Phase Lock Loop Modes */
 vdBroadcastMode = 0,					/* Broadcast / Laser Disk video mode */
 vdVTRMode = 1		,				/* VCR / Magnetic media mode */

/* Field Select Options */
 vdUseAnyField = 0,
 vdUseOddField = 1,
 vdUseEvenField = 2,

/* vdig types */
 vdTypeBasic = 0,						/* basic, no clipping */
 vdTypeAlpha = 1,						/* supports clipping with alpha channel */
 vdTypeMask = 2	,					/* supports clipping with mask plane */
 vdTypeKey = 3	,					/* supports clipping with key color(s) */


/* Digitizer Error Codes */

 digiUnimpErr = -2201,				/* feature unimplemented */
 qtParamErr = -2202	,			/* bad input parameter ( out of range, etc ) */
 matrixErr = -2203	,				/* bad matrix, digitizer did nothing */
 notExactMatrix = -2204	,		/* warning of bad matrix, digitizer did its best */
 noMoreKeyColors = -2205,			/* all key indexes in use */
 notExactSize = -2206	,			/* Can’t do exact size requested */
 badDepth = -2207,					/* Can’t digitize into this depth */
 noDMA = -2208	,					/* Can’t do DMA digitizing ( i.e. can't go to requested dest) */
 badCallOrder = -2209,			/* Usually due to a status call being called prior to being setup first */


/* Digitizer Input Capability/Current Flags */
 digiInDoesNTSC= (1L<<0),			/* digitizer supports NTSC input format */
 digiInDoesPAL= (1L<<1)	,		/* digitizer supports PAL input format */
 digiInDoesSECAM= (1L<<2),			/* digitizer supports SECAM input format */
 digiInDoesGenLock= (1L<<7)	,	/* digitizer does genlock */

 digiInDoesComposite= (1L<<8),		/* digitizer supports composite input type */
 digiInDoesSVideo = (1L<<9)	,	/* digitizer supports S-Video input type */
 digiInDoesComponent = (1L<<10)	,/* digitizer supports component (rgb) input type */
 digiInVTR_Broadcast = (1L<<11),/* digitizer can differentiate between the two */

 digiInDoesColor = (1L<<12)	,	/* digitizer supports color */
 digiInDoesBW = (1L<<13)	,		/* digitizer supports black & white */


/* Digitizer Input Current Flags (these are valid only during active operating conditions) */
 digiInSignalLock = (1L<<31),		/* digitizer detects input signal is locked - this bit = horiz lock || vertical lock */


/* Digitizer Output Capability/Current Flags */
 digiOutDoes1 = (1L<<0)	,		/* digitizer supports 1 bit pixels */
 digiOutDoes2 = (1L<<1)	,		/* digitizer supports 2 bit pixels */
 digiOutDoes4 = (1L<<2)	,		/* digitizer supports 4 bit pixels */
 digiOutDoes8 = (1L<<3)	,		/* digitizer supports 8 bit pixels */
 digiOutDoes16 = (1L<<4)	,		/* digitizer supports 16 bit pixels */
 digiOutDoes32 = (1L<<5)	,		/* digitizer supports 32 bit pixels */
 digiOutDoesDither = (1L<<6),		/* digitizer dithers in indexed modes */
 digiOutDoesStretch = (1L<<7),		/* digitizer can arbitrarily stretch */
 digiOutDoesShrink = (1L<<8),		/* digitizer can arbitrarily shrink */
 digiOutDoesMask = (1L<<9)	,		/* digitizer can mask to clipping regions */

 digiOutDoesDouble = (1L<<11),		/* digitizer can stretch to exactly double size */
 digiOutDoesQuad = (1L<<12)		,/* digitizer can stretch exactly quadruple size */
 digiOutDoesQuarter = (1L<<13)	,	/* digitizer can shrink to exactly quarter size */
 digiOutDoesSixteenth = (1L<<14),	/* digitizer can shrink to exactly sixteenth size */

 digiOutDoesRotate = (1L<<15)	,	/* digitizer supports rotate transformations */
 digiOutDoesHorizFlip = (1L<<16),	/* digitizer supports horizontal flips Sx < 0 */
 digiOutDoesVertFlip = (1L<<17),	/* digitizer supports vertical flips Sy < 0 */
 digiOutDoesSkew = (1L<<18)		,/* digitizer supports skew (shear, twist) */
 digiOutDoesBlend = (1L<<19),
 digiOutDoesWarp = (1L<<20),

 digiOutDoesHW_DMA = (1L<<21)	,	/* digitizer not constrained to local device */
 digiOutDoesHWPlayThru = (1L<<22),	/* digitizer doesn't need time to play thru */
 digiOutDoesILUT = (1L<<23)		,	/* digitizer does inverse LUT for index modes */
 digiOutDoesKeyColor = (1L<<24)	,	/* digitizer does key color functions too */
 digiOutDoesAsyncGrabs = (1L<<25)	/* digitizer supports async grabs */

};

typedef ComponentInstance VideoDigitizerComponent;
typedef ComponentResult VideoDigitizerError;

/* Types */
struct DigitizerInfo {
 short vdigType;
 long inputCapabilityFlags;
 long outputCapabilityFlags;
 long inputCurrentFlags;
 long outputCurrentFlags;
 short slot;							/* temporary for connection purposes */
 GDHandle gdh;							/* temporary for digitizers that have preferred screen */
 GDHandle maskgdh;						/* temporary for digitizers that have mask planes */
 short minDestHeight;					/* Smallest resizable height */
 short minDestWidth;					/* Smallest resizable width */
 short maxDestHeight;					/* Largest resizable height */
 short maxDestWidth;					/* Largest resizable height */
 short blendLevels;						/* Number of blend levels supported (2 if 1 bit mask) */
 long Private;							/* reserved */
};

typedef struct DigitizerInfo DigitizerInfo;

typedef struct {
	PixMapHandle	dest;
	Point			location;
	long			reserved;
} VdigBufferRec;

struct VdigBufferRecList {
	short			count;
	MatrixRecordPtr	matrix;
	RgnHandle		mask;
	VdigBufferRec	list[1];
};

typedef struct VdigBufferRecList VdigBufferRecList;
typedef VdigBufferRecList *VdigBufferRecListPtr, **VdigBufferRecListHandle;
typedef pascal void (*VdigIntProc)(long flags, long refcon);

enum {


/* Video Digitizer Interface */
 kSelectVDGetMaxSrcRect = 1,
 kSelectVDGetActiveSrcRect = 2,
 kSelectVDSetDigitizerRect = 3,
 kSelectVDGetDigitizerRect = 4,
 kSelectVDGetVBlankRect = 5,
 kSelectVDGetMaskPixMap = 6,

/* 1 available selector here */

 kSelectVDGetPlayThruDestination = 8,
 kSelectVDUseThisCLUT = 9,
 kSelectVDSetInputGammaValue = 10,
 kSelectVDGetInputGammaValue = 11,
 kSelectVDSetBrightness = 12,
 kSelectVDGetBrightness = 13,
 kSelectVDSetContrast = 14,
 kSelectVDSetHue = 15,
 kSelectVDSetSharpness = 16,
 kSelectVDSetSaturation = 17,
 kSelectVDGetContrast = 18,
 kSelectVDGetHue = 19,
 kSelectVDGetSharpness = 20
};
enum {
 kSelectVDGetSaturation = 21,
 kSelectVDGrabOneFrame = 22,
 kSelectVDGetMaxAuxBuffer = 23,

/* 1 available selector here */

 kSelectVDGetDigitizerInfo = 25,
 kSelectVDGetCurrentFlags = 26,
 kSelectVDSetKeyColor = 27,
 kSelectVDGetKeyColor = 28,
 kSelectVDAddKeyColor = 29,
 kSelectVDGetNextKeyColor = 30,
 kSelectVDSetKeyColorRange = 31,
 kSelectVDGetKeyColorRange = 32,
 kSelectVDSetDigitizerUserInterrupt = 33,
 kSelectVDSetInputColorSpaceMode = 34,
 kSelectVDGetInputColorSpaceMode = 35,
 kSelectVDSetClipState = 36,
 kSelectVDGetClipState = 37,
 kSelectVDSetClipRgn = 38,
 kSelectVDClearClipRgn = 39,
 kSelectVDGetCLUTInUse = 40
};
enum {
 kSelectVDSetPLLFilterType = 41,
 kSelectVDGetPLLFilterType = 42,
 kSelectVDGetMaskandValue = 43,
 kSelectVDSetMasterBlendLevel = 44,
 kSelectVDSetPlayThruDestination = 45,
 kSelectVDSetPlayThruOnOff = 46,
 kSelectVDSetFieldPreference = 47,
 kSelectVDGetFieldPreference = 48,

/* 1 available selectors here */

 kSelectVDPreflightDestination = 50,
 kSelectVDPreflightGlobalRect = 51,
 kSelectVDSetPlayThruGlobalRect = 52,
 kSelectVDSetInputGammaRecord = 53,
 kSelectVDGetInputGammaRecord = 54,
 kSelectVDSetBlackLevelValue = 55,
 kSelectVDGetBlackLevelValue = 56,
 kSelectVDSetWhiteLevelValue = 57,
 kSelectVDGetWhiteLevelValue = 58,
 kSelectVDGetVideoDefaults = 59,
 kSelectVDGetNumberOfInputs = 60
};
enum {
 kSelectVDGetInputFormat = 61,
 kSelectVDSetInput = 62,
 kSelectVDGetInput = 63,
 kSelectVDSetInputStandard = 64,
 kSelectVDSetupBuffers = 65,
 kSelectVDGrabOneFrameAsync = 66,
 kSelectVDDone = 67,

 kvdigSelectors = 67
};

#ifdef __cplusplus
extern "C" {
#endif
pascal VideoDigitizerError VDGetMaxSrcRect(VideoDigitizerComponent ci,short inputStd,
 Rect *maxSrcRect)
 = {0x2F3C,0x6,0x1,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetActiveSrcRect(VideoDigitizerComponent ci,short inputStd,
 Rect *activeSrcRect)
 = {0x2F3C,0x6,0x2,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetDigitizerRect(VideoDigitizerComponent ci,Rect *digitizerRect)
 = {0x2F3C,0x4,0x3,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetDigitizerRect(VideoDigitizerComponent ci,Rect *digitizerRect)
 = {0x2F3C,0x4,0x4,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetVBlankRect(VideoDigitizerComponent ci,short inputStd,
 Rect *vBlankRect)
 = {0x2F3C,0x6,0x5,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetMaskPixMap(VideoDigitizerComponent ci,PixMapHandle maskPixMap)
 = {0x2F3C,0x4,0x6,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetPlayThruDestination(VideoDigitizerComponent ci,
 PixMapHandle *dest,Rect *destRect,MatrixRecord *m,RgnHandle *mask)
 = {0x2F3C,0x10,0x8,0x7000,0xA82A}; 
pascal VideoDigitizerError VDUseThisCLUT(VideoDigitizerComponent ci,CTabHandle colorTableHandle)
 = {0x2F3C,0x4,0x9,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetInputGammaValue(VideoDigitizerComponent ci,
 Fixed channel1,Fixed channel2,Fixed channel3)
 = {0x2F3C,0xC,0xA,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetInputGammaValue(VideoDigitizerComponent ci,
 Fixed *channel1,Fixed *channel2,Fixed *channel3)
 = {0x2F3C,0xC,0xB,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetBrightness(VideoDigitizerComponent ci,unsigned short *brightness)
 = {0x2F3C,0x4,0xC,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetBrightness(VideoDigitizerComponent ci,unsigned short *brightness)
 = {0x2F3C,0x4,0xD,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetContrast(VideoDigitizerComponent ci,unsigned short *contrast)
 = {0x2F3C,0x4,0xE,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetHue(VideoDigitizerComponent ci,unsigned short *hue)
 = {0x2F3C,0x4,0xF,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetSharpness(VideoDigitizerComponent ci,unsigned short *sharpness)
 = {0x2F3C,0x4,0x10,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetSaturation(VideoDigitizerComponent ci,unsigned short *saturation)
 = {0x2F3C,0x4,0x11,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetContrast(VideoDigitizerComponent ci,unsigned short *contrast)
 = {0x2F3C,0x4,0x12,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetHue(VideoDigitizerComponent ci,unsigned short *hue)
 = {0x2F3C,0x4,0x13,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetSharpness(VideoDigitizerComponent ci,unsigned short *sharpness)
 = {0x2F3C,0x4,0x14,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetSaturation(VideoDigitizerComponent ci,unsigned short *saturation)
 = {0x2F3C,0x4,0x15,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGrabOneFrame(VideoDigitizerComponent ci)
 = {0x2F3C,0x0,0x16,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetMaxAuxBuffer(VideoDigitizerComponent ci,PixMapHandle *pm,
 Rect *r)
 = {0x2F3C,0x8,0x17,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetDigitizerInfo(VideoDigitizerComponent ci,DigitizerInfo *info)
 = {0x2F3C,0x4,0x19,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetCurrentFlags(VideoDigitizerComponent ci,long *inputCurrentFlag,
 long *outputCurrentFlag)
 = {0x2F3C,0x8,0x1A,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetKeyColor(VideoDigitizerComponent ci,long index)
 = {0x2F3C,0x4,0x1B,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetKeyColor(VideoDigitizerComponent ci,long *index)
 = {0x2F3C,0x4,0x1C,0x7000,0xA82A}; 
pascal VideoDigitizerError VDAddKeyColor(VideoDigitizerComponent ci,long *index)
 = {0x2F3C,0x4,0x1D,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetNextKeyColor(VideoDigitizerComponent ci,long index)
 = {0x2F3C,0x4,0x1E,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetKeyColorRange(VideoDigitizerComponent ci,RGBColor *minRGB,
 RGBColor *maxRGB)
 = {0x2F3C,0x8,0x1F,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetKeyColorRange(VideoDigitizerComponent ci,RGBColor *minRGB,
 RGBColor *maxRGB)
 = {0x2F3C,0x8,0x20,0x7000,0xA82A}; 
pascal VideoDigitizerError	VDSetDigitizerUserInterrupt(VideoDigitizerComponent ci,
 long flags, VdigIntProc userInterruptProc, long refcon)
 = {0x2F3C,0xC,0x21,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetInputColorSpaceMode(VideoDigitizerComponent ci,
 short colorSpaceMode)
 = {0x2F3C,0x2,0x22,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetInputColorSpaceMode(VideoDigitizerComponent ci,
 short *colorSpaceMode)
 = {0x2F3C,0x4,0x23,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetClipState(VideoDigitizerComponent ci,short clipEnable)
 = {0x2F3C,0x2,0x24,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetClipState(VideoDigitizerComponent ci,short *clipEnable)
 = {0x2F3C,0x4,0x25,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetClipRgn(VideoDigitizerComponent ci,RgnHandle clipRegion)
 = {0x2F3C,0x4,0x26,0x7000,0xA82A}; 
pascal VideoDigitizerError VDClearClipRgn(VideoDigitizerComponent ci,RgnHandle clipRegion)
 = {0x2F3C,0x4,0x27,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetCLUTInUse(VideoDigitizerComponent ci,CTabHandle *colorTableHandle)
 = {0x2F3C,0x4,0x28,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetPLLFilterType(VideoDigitizerComponent ci,short pllType)
 = {0x2F3C,0x2,0x29,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetPLLFilterType(VideoDigitizerComponent ci,short *pllType)
 = {0x2F3C,0x4,0x2A,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetMaskandValue(VideoDigitizerComponent ci,unsigned short blendLevel,
 long *mask,long *value)
 = {0x2F3C,0xA,0x2B,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetMasterBlendLevel(VideoDigitizerComponent ci,
 unsigned short *blendLevel)
 = {0x2F3C,0x4,0x2C,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetPlayThruDestination(VideoDigitizerComponent ci,
 PixMapHandle dest,Rect *destRect,MatrixRecord *m,RgnHandle mask)
 = {0x2F3C,0x10,0x2D,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetPlayThruOnOff(VideoDigitizerComponent ci,short state)
 = {0x2F3C,0x2,0x2E,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetFieldPreference(VideoDigitizerComponent ci,short fieldFlag)
 = {0x2F3C,0x2,0x2F,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetFieldPreference(VideoDigitizerComponent ci,short *fieldFlag)
 = {0x2F3C,0x4,0x30,0x7000,0xA82A}; 

/* 1 available selectors here */

pascal VideoDigitizerError VDPreflightDestination(VideoDigitizerComponent ci,
 Rect *digitizerRect,PixMapHandle dest,Rect *destRect,MatrixRecord *m)
 = {0x2F3C,0x10,0x32,0x7000,0xA82A}; 
pascal VideoDigitizerError VDPreflightGlobalRect(VideoDigitizerComponent ci,
 GrafPtr theWindow,Rect *globalRect)
 = {0x2F3C,0x8,0x33,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetPlayThruGlobalRect(VideoDigitizerComponent ci,
 GrafPtr theWindow,Rect *globalRect)
 = {0x2F3C,0x8,0x34,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetInputGammaRecord(VideoDigitizerComponent ci,
 VDGamRecPtr inputGammaPtr)
 = {0x2F3C,0x4,0x35,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetInputGammaRecord(VideoDigitizerComponent ci,
 VDGamRecPtr *inputGammaPtr)
 = {0x2F3C,0x4,0x36,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetBlackLevelValue(VideoDigitizerComponent ci,
 unsigned short *blackLevel)
 = {0x2F3C,0x4,0x37,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetBlackLevelValue(VideoDigitizerComponent ci,
 unsigned short *blackLevel)
 = {0x2F3C,0x4,0x38,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetWhiteLevelValue(VideoDigitizerComponent ci,
 unsigned short *whiteLevel)
 = {0x2F3C,0x4,0x39,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetWhiteLevelValue(VideoDigitizerComponent ci,
 unsigned short *whiteLevel)
 = {0x2F3C,0x4,0x3A,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetVideoDefaults(VideoDigitizerComponent ci,unsigned short *blackLevel,
 unsigned short *whiteLevel,unsigned short *brightness,unsigned short *hue,
 unsigned short *saturation,unsigned short *contrast,unsigned short *sharpness)
 = {0x2F3C,0x1C,0x3B,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetNumberOfInputs(VideoDigitizerComponent ci,short *inputs)
 = {0x2F3C,0x4,0x3C,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetInputFormat(VideoDigitizerComponent ci,short input,
 short *format)
 = {0x2F3C,0x6,0x3D,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetInput(VideoDigitizerComponent ci,short input)
 = {0x2F3C,0x2,0x3E,0x7000,0xA82A}; 
pascal VideoDigitizerError VDGetInput(VideoDigitizerComponent ci,short *input)
 = {0x2F3C,0x4,0x3F,0x7000,0xA82A}; 
pascal VideoDigitizerError VDSetInputStandard(VideoDigitizerComponent ci,short inputStandard)
 = {0x2F3C,0x2,0x40,0x7000,0xA82A}; 
pascal VideoDigitizerError	VDSetupBuffers(VideoDigitizerComponent ci, VdigBufferRecListHandle bufferList)
 = {0x2F3C,0x4,0x41,0x7000,0xA82A}; 
pascal VideoDigitizerError	VDGrabOneFrameAsync(VideoDigitizerComponent ci, short buffer)
 = {0x2F3C,0x2,0x42,0x7000,0xA82A}; 
pascal long	VDDone(VideoDigitizerComponent ci, short buffer)
 = {0x2F3C,0x2,0x43,0x7000,0xA82A}; 
#ifdef __cplusplus
}
#endif
/* Sequence Grab Component */
typedef ComponentInstance SeqGrabComponent;
typedef ComponentInstance SGChannel;




#define SeqGrabComponentType 'barg'
#define SeqGrabChannelType 'sgch'

#define grabPictOffScreen (1)
#define sgFlagControlledGrab (1)

#define channelPlayNormal 0
#define channelPlayFast 1
#define channelPlayHighQuality 2
#define channelPlayAllData 4

enum {seqGrabToDisk = 1,seqGrabToMemory = 2,seqGrabDontUseTempMemory = 4,
 seqGrabAppendToFile = 8,seqGrabDontAddMovieResource = 16};
typedef unsigned char SeqGrabDataOutputEnum;

enum {seqGrabRecord = 1,seqGrabPreview = 2,seqGrabPlayDuringRecord = 4};
typedef unsigned char SeqGrabUsageEnum;

enum {seqGrabHasBounds = 1,seqGrabHasVolume = 2, seqGrabHasDiscreteSamples = 4};
typedef unsigned char SeqGrabChannelInfoEnum;


struct SeqGrabFrameInfo {
 long frameOffset;
 long frameTime;
 long frameSize;
 SGChannel frameChannel;
 long frameRefCon;
};

enum {
 noDeviceForChannel = -9400,
 grabTimeComplete = -9401,
 cantDoThatInCurrentMode = -9402,
 notEnoughMemoryToGrab = -9403,
 notEnoughDiskSpaceToGrab = -9404,
 couldntGetRequiredComponent = -9405,
 badSGChannel = -9406,
 seqGrabInfoNotAvailable = -9407,
 deviceCantMeetRequest = -9408
};

typedef struct SeqGrabFrameInfo SeqGrabFrameInfo;


#ifdef __cplusplus
extern "C" {
#endif
pascal ComponentResult SGInitialize(SeqGrabComponent s)
 = {0x2F3C,0x0,0x1,0x7000,0xA82A}; 

pascal ComponentResult SGSetDataOutput(SeqGrabComponent s,FSSpec *movieFile,
 long whereFlags)
 = {0x2F3C,0x8,0x2,0x7000,0xA82A}; 
pascal ComponentResult SGGetDataOutput(SeqGrabComponent s,FSSpec *movieFile,
 long *whereFlags)
 = {0x2F3C,0x8,0x3,0x7000,0xA82A}; 

pascal ComponentResult SGSetGWorld(SeqGrabComponent s,CGrafPtr gp,GDHandle gd)
 = {0x2F3C,0x8,0x4,0x7000,0xA82A}; 
pascal ComponentResult SGGetGWorld(SeqGrabComponent s,CGrafPtr *gp,GDHandle *gd)
 = {0x2F3C,0x8,0x5,0x7000,0xA82A}; 

pascal ComponentResult SGNewChannel(SeqGrabComponent s,OSType channelType,
 SGChannel *ref)
 = {0x2F3C,0x8,0x6,0x7000,0xA82A}; 
pascal ComponentResult SGDisposeChannel(SeqGrabComponent s,SGChannel c)
 = {0x2F3C,0x4,0x7,0x7000,0xA82A}; 

pascal ComponentResult SGStartPreview(SeqGrabComponent s)
 = {0x2F3C,0x0,0x10,0x7000,0xA82A}; 
pascal ComponentResult SGStartRecord(SeqGrabComponent s)
 = {0x2F3C,0x0,0x11,0x7000,0xA82A}; 
pascal ComponentResult SGIdle(SeqGrabComponent s)
 = {0x2F3C,0x0,0x12,0x7000,0xA82A}; 
pascal ComponentResult SGStop(SeqGrabComponent s)
 = {0x2F3C,0x0,0x13,0x7000,0xA82A}; 

pascal ComponentResult SGPause(SeqGrabComponent s,Boolean pause)
 = {0x2F3C,0x2,0x14,0x7000,0xA82A}; 

pascal ComponentResult SGPrepare(SeqGrabComponent s,Boolean prepareForPreview,
 Boolean prepareForRecord)
 = {0x2F3C,0x4,0x15,0x7000,0xA82A}; 
pascal ComponentResult SGRelease(SeqGrabComponent s)
 = {0x2F3C,0x0,0x16,0x7000,0xA82A}; 

pascal Movie SGGetMovie(SeqGrabComponent s)
 = {0x2F3C,0x0,0x17,0x7000,0xA82A}; 

pascal ComponentResult SGSetMaximumRecordTime(SeqGrabComponent s,unsigned long ticks)
 = {0x2F3C,0x4,0x18,0x7000,0xA82A}; 
pascal ComponentResult SGGetMaximumRecordTime(SeqGrabComponent s,unsigned long *ticks)
 = {0x2F3C,0x4,0x19,0x7000,0xA82A}; 

pascal ComponentResult SGGetStorageSpaceRemaining(SeqGrabComponent s,unsigned long *bytes)
 = {0x2F3C,0x4,0x1A,0x7000,0xA82A}; 
pascal ComponentResult SGGetTimeRemaining(SeqGrabComponent s,long *ticksLeft)
 = {0x2F3C,0x4,0x1B,0x7000,0xA82A}; 
pascal ComponentResult SGGrabPict(SeqGrabComponent s, PicHandle *p, const Rect *bounds,
 short offscreenDepth, long grabPictFlags) =
 {0x2F3C,0xE,0x1C,0x7000,0xA82A};

pascal ComponentResult SGGetLastMovieResID(SeqGrabComponent s, short *resID) =
 {0x2F3C,0x4,0x1D,0x7000,0xA82A};

pascal ComponentResult SGSetFlags(SeqGrabComponent s, long sgFlags) =
 {0x2F3C,0x4,0x1E,0x7000,0xA82A};

pascal ComponentResult SGGetFlags(SeqGrabComponent s, long *sgFlags) =
 {0x2F3C,0x4,0x1F,0x7000,0xA82A};


/*   General Channel Routines   */
pascal ComponentResult SGSetChannelUsage(SGChannel c,long usage)
 = {0x2F3C,0x4,0x80,0x7000,0xA82A}; 
pascal ComponentResult SGGetChannelUsage(SGChannel c,long *usage)
 = {0x2F3C,0x4,0x81,0x7000,0xA82A}; 

pascal ComponentResult SGSetChannelBounds(SGChannel c,Rect *bounds)
 = {0x2F3C,0x4,0x82,0x7000,0xA82A}; 
pascal ComponentResult SGGetChannelBounds(SGChannel c,const Rect *bounds)
 = {0x2F3C,0x4,0x83,0x7000,0xA82A}; 

pascal ComponentResult SGSetChannelVolume(SGChannel c,short volume)
 = {0x2F3C,0x2,0x84,0x7000,0xA82A}; 
pascal ComponentResult SGGetChannelVolume(SGChannel c,short *volume)
 = {0x2F3C,0x4,0x85,0x7000,0xA82A}; 

pascal ComponentResult SGGetChannelInfo(SGChannel c,long *channelInfo)
 = {0x2F3C,0x4,0x86,0x7000,0xA82A}; 

pascal ComponentResult SGSetChannelPlayFlags(SGChannel c, long playFlags)
 = {0x2F3C,0x4,0x87,0x7000,0xA82A}; 
pascal ComponentResult SGGetChannelPlayFlags(SGChannel c, long *playFlags)
 = {0x2F3C,0x4,0x88,0x7000,0xA82A}; 

pascal ComponentResult SGSetChannelMaxFrames(SGChannel c, long frameCount)
 = {0x2F3C,0x4,0x89,0x7000,0xA82A}; 
pascal ComponentResult SGGetChannelMaxFrames(SGChannel c, long *frameCount)
 = {0x2F3C,0x4,0x8A,0x7000,0xA82A}; 

pascal ComponentResult SGSetChannelRefCon(SGChannel c, long refCon)
 = {0x2F3C,0x4,0x8B,0x7000,0xA82A}; 

#ifdef __cplusplus
}
#endif
/* Video Routines */

struct SGCompressInfo {
	Ptr				buffer;
	unsigned long	bufferSize;
	unsigned char	similarity;
	unsigned char	reserved;
};
typedef struct SGCompressInfo SGCompressInfo;

typedef pascal ComponentResult (*GrabProc)(SGChannel c, short bufferNum, long refCon);
typedef pascal ComponentResult (*GrabCompleteProc)(SGChannel c, short bufferNum, Boolean *done, long refCon);
typedef pascal ComponentResult (*DisplayProc)(SGChannel c, short bufferNum, MatrixRecord *mp, RgnHandle clipRgn, long refCon);
typedef pascal ComponentResult (*CompressProc)(SGChannel c, short bufferNum, long refCon);
typedef pascal ComponentResult (*CompressCompleteProc)(SGChannel c, short bufferNum,
										Boolean *done, SGCompressInfo *ci, long refCon);
typedef pascal ComponentResult (*AddFrameProc)(SGChannel c, short bufferNum, TimeValue atTime, TimeScale scale,
							const SGCompressInfo *ci, long refCon);
typedef pascal ComponentResult (*TransferFrameProc)(SGChannel c, short bufferNum, MatrixRecord *mp, RgnHandle clipRgn, long refCon);

struct VideoBottles {
 short procCount;
 GrabProc grabProc;
 GrabCompleteProc grabCompleteProc;
 DisplayProc displayProc;
 CompressProc compressProc;
 CompressCompleteProc compressCompleteProc;
 AddFrameProc addFrameProc;
 TransferFrameProc transferFrameProc;
};

typedef struct VideoBottles VideoBottles;


#ifdef __cplusplus
extern "C" {
#endif
pascal ComponentResult SGGetSrcVideoBounds(SGChannel c,Rect *r)
 = {0x2F3C,0x4,0x100,0x7000,0xA82A}; 
pascal ComponentResult SGSetVideoRect(SGChannel c,Rect *r)
 = {0x2F3C,0x4,0x101,0x7000,0xA82A}; 
pascal ComponentResult SGGetVideoRect(SGChannel c,Rect *r)
 = {0x2F3C,0x4,0x102,0x7000,0xA82A}; 

pascal ComponentResult SGGetVideoCompressorType(SGChannel c,OSType *compressorType)
 = {0x2F3C,0x4,0x103,0x7000,0xA82A}; 
pascal ComponentResult SGSetVideoCompressorType(SGChannel c,OSType compressorType)
 = {0x2F3C,0x4,0x104,0x7000,0xA82A}; 

pascal ComponentResult SGSetVideoCompressor(SGChannel c,short depth,CompressorComponent compressor,
 CodecQ spatialQuality,CodecQ temporalQuality,long keyFrameRate)
 = {0x2F3C,0x12,0x105,0x7000,0xA82A}; 
pascal ComponentResult SGGetVideoCompressor(SGChannel c,short *depth,CompressorComponent *compressor,
 CodecQ *spatialQuality,CodecQ *temporalQuality,long *keyFrameRate)
 = {0x2F3C,0x14,0x106,0x7000,0xA82A}; 

pascal ComponentInstance SGGetVideoDigitizerComponent(SGChannel c) 
 = {0x2F3C,0,263,0x7000,0xA82A};
pascal ComponentResult SGSetVideoDigitizerComponent(SGChannel c, ComponentInstance vdig)
 = {0x2F3C,4,264,0x7000,0xA82A};
pascal ComponentResult SGVideoDigitizerChanged(SGChannel c)
 = {0x2F3C,0,265,0x7000,0xA82A};

pascal ComponentResult SGSetVideoBottlenecks(SGChannel c, VideoBottles *vb)
 = {0x2F3C,4,266,0x7000,0xA82A};
pascal ComponentResult SGGetVideoBottlenecks(SGChannel c, VideoBottles *vb)
 = {0x2F3C,4,267,0x7000,0xA82A};

pascal ComponentResult SGGrabFrame(SGChannel c, short bufferNum)
 = {0x2F3C,2,268,0x7000,0xA82A};
pascal ComponentResult SGGrabFrameComplete(SGChannel c, short bufferNum, Boolean *done)
 = {0x2F3C,6,269,0x7000,0xA82A};

pascal ComponentResult SGDisplayFrame(SGChannel c, short bufferNum, MatrixRecord *mp, 
 RgnHandle clipRgn)
 = {0x2F3C,10,270,0x7000,0xA82A};

pascal ComponentResult SGCompressFrame(SGChannel c, short bufferNum)
 = {0x2F3C,2,271,0x7000,0xA82A};
pascal ComponentResult SGCompressFrameComplete(SGChannel c, short bufferNum, 
 Boolean *done, SGCompressInfo *ci)
 = {0x2F3C,10,272,0x7000,0xA82A};

pascal ComponentResult SGAddFrame(SGChannel c, short bufferNum, TimeValue atTime, 
 TimeScale scale, const SGCompressInfo *ci)
 = {0x2F3C,14,273,0x7000,0xA82A};

pascal ComponentResult SGTransferFrameForCompress(SGChannel c, short bufferNum, 
 MatrixRecord *mp, RgnHandle clipRgn)
 = {0x2F3C,10,274,0x7000,0xA82A};

pascal ComponentResult SGSetCompressBuffer(SGChannel c, short depth, const Rect *compressSize)
 = {0x2F3C,6,275,0x7000,0xA82A};

pascal ComponentResult SGGetCompressBuffer(SGChannel c, short *depth, Rect *compressSize)
 = {0x2F3C,8,276,0x7000,0xA82A};

pascal ComponentResult SGGetBufferInfo(SGChannel c, short bufferNum, 
 PixMapHandle *bufferPM, Rect *bufferRect,GWorldPtr *compressBuffer,
 Rect *compressBufferRect) 
 = {0x2F3C,18,277,0x7000,0xA82A};

/*   Sound Routines   */
pascal ComponentResult SGSetSoundInputDriver(SGChannel c,const Str255 driverName)
 = {0x2F3C,0x4,0x100,0x7000,0xA82A}; 
pascal long SGGetSoundInputDriver(SGChannel c)
 = {0x2F3C,0x0,0x101,0x7000,0xA82A}; 
pascal ComponentResult SGSoundInputDriverChanged(SGChannel c)
 = {0x2F3C,0x0,0x102,0x7000,0xA82A}; 

pascal ComponentResult SGSetSoundRecordChunkSize(SGChannel c,long seconds)
 = {0x2F3C,0x4,0x103,0x7000,0xA82A}; 
pascal long SGGetSoundRecordChunkSize(SGChannel c)
 = {0x2F3C,0x0,0x104,0x7000,0xA82A}; 

pascal ComponentResult SGSetSoundInputRate(SGChannel c,Fixed rate)
 = {0x2F3C,0x4,0x105,0x7000,0xA82A}; 
pascal Fixed SGGetSoundInputRate(SGChannel c)
 = {0x2F3C,0x0,0x106,0x7000,0xA82A}; 

/*   calls from seqGrab to Channel   */
pascal ComponentResult SGInitChannel(SGChannel c,SeqGrabComponent owner)
 = {0x2F3C,0x4,0x180,0x7000,0xA82A}; 
pascal ComponentResult SGWriteSamples(SGChannel c,Movie m,AliasHandle theFile)
 = {0x2F3C,0x8,0x181,0x7000,0xA82A}; 
pascal ComponentResult SGGetDataRate(SGChannel c,long *bytesPerSecond)
 = {0x2F3C,0x4,0x182,0x7000,0xA82A}; 

/*   calls from Channel to seqGrab   */
pascal ComponentResult SGWriteMovieData(SeqGrabComponent s,SGChannel c,
 Ptr p,long len,long *offset)
 = {0x2F3C,0x10,0x100,0x7000,0xA82A}; 
pascal ComponentResult SGAddFrameReference(SeqGrabComponent s,SeqGrabFrameInfo *frameInfo)
 = {0x2F3C,0x4,0x101,0x7000,0xA82A}; 
pascal ComponentResult SGGetNextFrameReference(SeqGrabComponent s,SeqGrabFrameInfo *frameInfo,
 TimeValue *frameDuration,long *frameNumber)
 = {0x2F3C,0xC,0x102,0x7000,0xA82A}; 
pascal ComponentResult SGGetTimeBase(SeqGrabComponent s,TimeBase *tb)
 = {0x2F3C,0x4,0x103,0x7000,0xA82A}; 
#ifdef __cplusplus
}
#endif

enum {
kSGInitializeSelect = 0x1,
kSGSetDataOutputSelect = 0x2,
kSGGetDataOutputSelect = 0x3,
kSGSetGWorldSelect = 0x4,
kSGGetGWorldSelect = 0x5,
kSGNewChannelSelect = 0x6,
kSGDisposeChannelSelect = 0x7,
kSGStartPreviewSelect = 0x10,
kSGStartRecordSelect = 0x11,
kSGIdleSelect = 0x12,
kSGStopSelect = 0x13,
kSGPauseSelect = 0x14,
kSGPrepareSelect = 0x15,
kSGReleaseSelect = 0x16,
kSGGetMovieSelect = 0x17,
kSGSetMaximumRecordTimeSelect = 0x18,
kSGGetMaximumRecordTimeSelect = 0x19,
kSGGetStorageSpaceRemainingSelect = 0x1a,
kSGGetTimeRemainingSelect = 0x1b,
kSGGrabPictSelect = 0x1c,
kSGGetLastMovieResIDSelect = 0x1d,
kSGSetFlagsSelect = 0x1e,
kSGGetFlagsSelect = 0x1f,

kSGCSetChannelUsageSelect = 0x80,
kSGCGetChannelUsageSelect = 0x81,
kSGCSetChannelBoundsSelect = 0x82,
kSGCGetChannelBoundsSelect = 0x83,
kSGCSetChannelVolumeSelect = 0x84,
kSGCGetChannelVolumeSelect = 0x85,
kSGCGetChannelInfoSelect = 0x86,
kSGCSetChannelPlayFlagsSelect = 0x87,
kSGCGetChannelPlayFlagsSelect = 0x88,
kSGCSetChannelMaxFramesSelect = 0x89,
kSGCGetChannelMaxFramesSelect = 0x8a,
kSGCSetChannelRefConSelect = 0x8b,

kSGCGetSrcVideoBoundsSelect = 0x100,
kSGCSetVideoRectSelect = 0x101,
kSGCGetVideoRectSelect = 0x102,
kSGCGetVideoCompressorTypeSelect = 0x103,
kSGCSetVideoCompressorTypeSelect = 0x104,
kSGCSetVideoCompressorSelect = 0x105,
kSGCGetVideoCompressorSelect = 0x106,
kSGCGetVideoDigitizerComponentSelect = 0x107,
kSGCSetVideoDigitizerComponentSelect = 0x108,
kSGCVideoDigitizerChangedSelect = 0x109,
kSGCSetVideoBottlenecksSelect = 0x10a,
kSGCGetVideoBottlenecksSelect = 0x10b,
kSGCGrabFrameSelect = 0x10c,
kSGCGrabFrameCompleteSelect = 0x10d,
kSGCDisplayFrameSelect = 0x10e,
kSGCCompressFrameSelect = 0x10f,
kSGCCompressFrameCompleteSelect = 0x110,
kSGCAddFrameSelect = 0x111,
kSGCTransferFrameForCompressSelect = 0x112,
kSGCSetCompressBufferSelect = 0x113,
kSGCGetCompressBufferSelect = 0x114,
kSGCGetBufferInfoSelect = 0x115,

kSGCSetSoundInputDriverSelect = 0x100,
kSGCGetSoundInputDriverSelect = 0x101,
kSGCSoundInputDriverChangedSelect = 0x102,
kSGCSetSoundRecordChunkSizeSelect = 0x103,
kSGCGetSoundRecordChunkSizeSelect = 0x104,
kSGCSetSoundInputRateSelect = 0x105,
kSGCGetSoundInputRateSelect = 0x106,

kSGCInitChannelSelect = 0x180,
kSGCWriteSamplesSelect = 0x181,
kSGCGetDataRateSelect = 0x182,

kSGWriteMovieDataSelect = 0x100,
kSGAddFrameReferenceSelect = 0x101,
kSGGetNextFrameReferenceSelect = 0x102,
kSGGetTimeBaseSelect = 0x103
};

#endif
