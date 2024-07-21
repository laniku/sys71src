/*
	File:		QuickTimeComponents.h

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM3>	 10/8/92	DH		Update to QuickTime 1.5 header.
	   <SM2>	  9/1/92	DH		Set back to Quicktime 1.0 header.

*/
/************************************************************

Created: Friday, October 2, 1992 at 11:40 AM
 QuickTimeComponents.h
 C Interface to the Macintosh Libraries


 Copyright Apple Computer, Inc. 1991, 1992
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


	#define clockComponentType 		'clok'
	#define systemTickClock 		'tick'			/* subtype: 60ths since boot		*/
	#define systemSecondClock		'seco'			/* subtype: seconds since 1904		*/
	#define systemMillisecondClock	'mill'			/* subtype: 1000ths since boot		*/
	#define systemMicrosecondClock	'micr'			/* subtype: 1000000ths since boot	*/
	
	enum {
		kClockRateIsLinear = 1,
		kClockImplementsCallBacks = 2
	};
	
	#define ClockGetTime GetClockTime


#ifdef __cplusplus
extern "C" {
#endif __cplusplus

/** These are Clock procedures **/

pascal ComponentResult ClockGetTime (ComponentInstance aClock, TimeRecord *out)  = {0x2F3C,0x4,0x1,0x7000,0xA82A};

pascal QTCallBack ClockNewCallBack (ComponentInstance aClock, TimeBase tb, short callBackType)  = {0x2F3C,0x6,0x2,0x7000,0xA82A};

pascal ComponentResult ClockDisposeCallBack (ComponentInstance aClock, QTCallBack cb)  = {0x2F3C,0x4,0x3,0x7000,0xA82A};

pascal ComponentResult ClockCallMeWhen (ComponentInstance aClock, QTCallBack cb, long param1, long param2, long param3)  = {0x2F3C,0x10,0x4,0x7000,0xA82A};

pascal ComponentResult ClockCancelCallBack (ComponentInstance aClock, QTCallBack cb)  = {0x2F3C,0x4,0x5,0x7000,0xA82A};

pascal ComponentResult ClockRateChanged (ComponentInstance aClock, QTCallBack cb)  = {0x2F3C,0x4,0x6,0x7000,0xA82A};

pascal ComponentResult ClockTimeChanged (ComponentInstance aClock, QTCallBack cb)  = {0x2F3C,0x4,0x7,0x7000,0xA82A};

pascal ComponentResult ClockSetTimeBase (ComponentInstance aClock, TimeBase tb)  = {0x2F3C,0x4,0x8,0x7000,0xA82A};

pascal ComponentResult ClockStartStopChanged (ComponentInstance aClock, QTCallBack cb, Boolean startChanged, Boolean stopChanged)  = {0x2F3C,0x8,0x9,0x7000,0xA82A};

pascal ComponentResult ClockGetRate (ComponentInstance aClock, Fixed *rate)  = {0x2F3C,0x4,0xA,0x7000,0xA82A};

#ifdef __cplusplus
}
#endif __cplusplus
enum {
	kClockGetTimeSelect = 0x1,
	kClockNewCallBackSelect = 0x2,
	kClockDisposeCallBackSelect = 0x3,
	kClockCallMeWhenSelect = 0x4,
	kClockCancelCallBackSelect = 0x5,
	kClockRateChangedSelect = 0x6,
	kClockTimeChangedSelect = 0x7,
	kClockSetTimeBaseSelect = 0x8,
	kClockStartStopChangedSelect = 0x9,
	kClockGetRateSelect = 0xA 
};

	/*
		General Sequence Grab stuff
	*/
	
	typedef ComponentInstance SeqGrabComponent;
	
	typedef ComponentInstance SGChannel;
	
	#define SeqGrabComponentType 'barg'
	#define SeqGrabChannelType 'sgch'
	#define SeqGrabPanelType 'sgpn'

	#define SeqGrabCompressionPanelType 'comp'
	#define SeqGrabSourcePanelType 'sour'

	enum {
		seqGrabToDisk = 1,
		seqGrabToMemory = 2,
		seqGrabDontUseTempMemory = 4,
		seqGrabAppendToFile = 8,
		seqGrabDontAddMovieResource = 16,
		seqGrabDontMakeMovie = 32,
		seqGrabPreExtendFile = 64
	};
	typedef unsigned long SeqGrabDataOutputEnum;

	enum {
		seqGrabRecord = 1,
		seqGrabPreview = 2,
		seqGrabPlayDuringRecord = 4
	};
	typedef unsigned long SeqGrabUsageEnum;

	enum {
		seqGrabHasBounds = 1,
		seqGrabHasVolume = 2,
		seqGrabHasDiscreteSamples = 4
	};
	typedef unsigned long SeqGrabChannelInfoEnum;

	typedef struct seqGrabFrameInfo {
		long		frameOffset;
		long		frameTime;
		long		frameSize;
		SGChannel	frameChannel;
		long		frameRefCon;
	} seqGrabFrameInfo;
	
	enum {
		grabPictOffScreen = 1,
		grabPictIgnoreClip = 2
	};
	#define sgFlagControlledGrab (1)

	typedef pascal OSErr (*SGDataProc)(SGChannel c, Ptr p, long len, long *offset, long chRefCon,
				TimeValue time, short writeType, long refCon);

	typedef struct SGDeviceName {
		Str63			name;
		Handle			icon;
		long			flags;
		long			refCon;
		long			reserved;		// zero
	} SGDeviceName;

	#define sgDeviceNameFlagDeviceUnavailable (1)

	typedef struct SGDeviceListRecord {
		short			count;
		short			selectedIndex;
		long			reserved;		// zero
		SGDeviceName	entry[1];
	} SGDeviceListRecord, *SGDeviceListPtr, **SGDeviceList;

	#define sgDeviceListWithIcons (1)
	#define sgDeviceListDontCheckAvailability (2)

	enum {
		seqGrabWriteAppend,
		seqGrabWriteReserve,
		seqGrabWriteFill
	};

	enum {
		seqGrabUnpause = 0,
		seqGrabPause = 1,
		seqGrabPauseForMenu = 3
	};
	enum {
		channelFlagDontOpenResFile = 2,
		channelFlagHasDependency = 4
	};

	typedef pascal Boolean (*SGModalFilterProcPtr)(DialogPtr theDialog, EventRecord *theEvent,
				short *itemHit, long refCon);

	enum {
		sgPanelFlagForPanel = 1
	};



	#define channelPlayNormal 0
	#define channelPlayFast 1
	#define channelPlayHighQuality 2
	#define channelPlayAllData 4

#ifdef __cplusplus
extern "C" {
#endif __cplusplus
pascal ComponentResult SGInitialize (SeqGrabComponent s)  = {0x2F3C,0,0x1,0x7000,0xA82A};

pascal ComponentResult SGSetDataOutput (SeqGrabComponent s, FSSpec *movieFile, long whereFlags)  = {0x2F3C,0x8,0x2,0x7000,0xA82A};
	
pascal ComponentResult SGGetDataOutput (SeqGrabComponent s, FSSpec *movieFile, long *whereFlags)  = {0x2F3C,0x8,0x3,0x7000,0xA82A};

pascal ComponentResult SGSetGWorld (SeqGrabComponent s, CGrafPtr gp, GDHandle gd)  = {0x2F3C,0x8,0x4,0x7000,0xA82A};
pascal ComponentResult SGGetGWorld (SeqGrabComponent s, CGrafPtr *gp, GDHandle *gd)  = {0x2F3C,0x8,0x5,0x7000,0xA82A};

pascal ComponentResult SGNewChannel (SeqGrabComponent s, OSType channelType, SGChannel *ref)  = {0x2F3C,0x8,0x6,0x7000,0xA82A};
pascal ComponentResult SGDisposeChannel (SeqGrabComponent s, SGChannel c)  = {0x2F3C,0x4,0x7,0x7000,0xA82A};

pascal ComponentResult SGStartPreview (SeqGrabComponent s)  = {0x2F3C,0,0x10,0x7000,0xA82A};
pascal ComponentResult SGStartRecord (SeqGrabComponent s)  = {0x2F3C,0,0x11,0x7000,0xA82A};
pascal ComponentResult SGIdle (SeqGrabComponent s)  = {0x2F3C,0,0x12,0x7000,0xA82A};
pascal ComponentResult SGStop (SeqGrabComponent s)  = {0x2F3C,0,0x13,0x7000,0xA82A};

pascal ComponentResult SGPause (SeqGrabComponent s, Byte pause)  = {0x2F3C,0x2,0x14,0x7000,0xA82A};

pascal ComponentResult SGPrepare (SeqGrabComponent s, Boolean prepareForPreview, Boolean prepareForRecord)  = {0x2F3C,0x4,0x15,0x7000,0xA82A};
pascal ComponentResult SGRelease (SeqGrabComponent s)  = {0x2F3C,0,0x16,0x7000,0xA82A};

pascal Movie SGGetMovie (SeqGrabComponent s)  = {0x2F3C,0,0x17,0x7000,0xA82A};

pascal ComponentResult SGSetMaximumRecordTime (SeqGrabComponent s, unsigned long ticks)  = {0x2F3C,0x4,0x18,0x7000,0xA82A};
pascal ComponentResult SGGetMaximumRecordTime (SeqGrabComponent s, unsigned long *ticks)  = {0x2F3C,0x4,0x19,0x7000,0xA82A};

pascal ComponentResult SGGetStorageSpaceRemaining (SeqGrabComponent s, unsigned long *bytes)  = {0x2F3C,0x4,0x1A,0x7000,0xA82A};
pascal ComponentResult SGGetTimeRemaining (SeqGrabComponent s, long *ticksLeft)  = {0x2F3C,0x4,0x1B,0x7000,0xA82A};

pascal ComponentResult SGGrabPict (SeqGrabComponent s, PicHandle *p, const Rect *bounds,
				short offscreenDepth, long grabPictFlags)  = {0x2F3C,0xE,0x1C,0x7000,0xA82A};

pascal ComponentResult SGGetLastMovieResID (SeqGrabComponent s, short *resID)  = {0x2F3C,0x4,0x1D,0x7000,0xA82A};

pascal ComponentResult SGSetFlags (SeqGrabComponent s, long sgFlags)  = {0x2F3C,0x4,0x1E,0x7000,0xA82A};

pascal ComponentResult SGGetFlags (SeqGrabComponent s, long *sgFlags)  = {0x2F3C,0x4,0x1F,0x7000,0xA82A};

pascal ComponentResult SGSetDataProc (SeqGrabComponent s, SGDataProc proc, long refCon)  = {0x2F3C,0x8,0x20,0x7000,0xA82A};

pascal ComponentResult SGNewChannelFromComponent (SeqGrabComponent s, SGChannel *newChannel, Component sgChannelComponent)  = {0x2F3C,0x8,0x21,0x7000,0xA82A};

pascal ComponentResult SGDisposeDeviceList (SeqGrabComponent s, SGDeviceList list)  = {0x2F3C,0x4,0x22,0x7000,0xA82A};

pascal ComponentResult SGAppendDeviceListToMenu (SeqGrabComponent s, SGDeviceList list, MenuHandle mh)  = {0x2F3C,0x8,0x23,0x7000,0xA82A};

pascal ComponentResult SGSetSettings (SeqGrabComponent s, UserData ud, long flags)  = {0x2F3C,0x8,0x24,0x7000,0xA82A};

pascal ComponentResult SGGetSettings (SeqGrabComponent s, UserData *ud, long flags)  = {0x2F3C,0x8,0x25,0x7000,0xA82A};

pascal ComponentResult SGGetIndChannel (SeqGrabComponent s, short index, SGChannel *ref, OSType *chanType)  = {0x2F3C,0xA,0x26,0x7000,0xA82A};

pascal ComponentResult SGUpdate (SeqGrabComponent s, RgnHandle updateRgn)  = {0x2F3C,0x4,0x27,0x7000,0xA82A};

pascal ComponentResult SGGetPause (SeqGrabComponent s, Byte *paused)  = {0x2F3C,0x4,0x28,0x7000,0xA82A};

pascal ComponentResult SGSettingsDialog (SeqGrabComponent s, SGChannel c, short numPanels, Component *panelList, long flags, SGModalFilterProcPtr proc, long procRefNum)  = {0x2F3C,0x16,0x29,0x7000,0xA82A};

pascal ComponentResult SGGetAlignmentProc (SeqGrabComponent s, AlignmentProcRecordPtr alignmentProc)  = {0x2F3C,0x4,0x2A,0x7000,0xA82A};

pascal ComponentResult SGSetChannelSettings (SeqGrabComponent s, SGChannel c, UserData ud, long flags)  = {0x2F3C,0xC,0x2B,0x7000,0xA82A};

pascal ComponentResult SGGetChannelSettings (SeqGrabComponent s, SGChannel c, UserData *ud, long flags)  = {0x2F3C,0xC,0x2C,0x7000,0xA82A};



/*
	calls from Channel to seqGrab
*/

pascal ComponentResult SGWriteMovieData (SeqGrabComponent s, SGChannel c, Ptr p, long len, long *offset)  = {0x2F3C,0x10,0x100,0x7000,0xA82A};
pascal ComponentResult SGAddFrameReference (SeqGrabComponent s, seqGrabFrameInfo *frameInfo)  = {0x2F3C,0x4,0x101,0x7000,0xA82A};
pascal ComponentResult SGGetNextFrameReference (SeqGrabComponent s, seqGrabFrameInfo *frameInfo,
					TimeValue *frameDuration, long *frameNumber)  = {0x2F3C,0xC,0x102,0x7000,0xA82A};
pascal ComponentResult SGGetTimeBase (SeqGrabComponent s, TimeBase *tb)  = {0x2F3C,0x4,0x103,0x7000,0xA82A};
pascal ComponentResult SGSortDeviceList (SeqGrabComponent s, SGDeviceList list)  = {0x2F3C,0x4,0x104,0x7000,0xA82A};
pascal ComponentResult SGAddMovieData (SeqGrabComponent s, SGChannel c, Ptr p, long len, long *offset, long chRefCon, TimeValue time, short writeType)  = {0x2F3C,0x1A,0x105,0x7000,0xA82A};
pascal ComponentResult SGChangedSource (SeqGrabComponent s, SGChannel c)  = {0x2F3C,0x4,0x106,0x7000,0xA82A};


/*** Sequence Grab CHANNEL Component Stuff ***/

pascal ComponentResult SGSetChannelUsage (SGChannel c, long usage)  = {0x2F3C,0x4,0x80,0x7000,0xA82A};
pascal ComponentResult SGGetChannelUsage (SGChannel c, long *usage)  = {0x2F3C,0x4,0x81,0x7000,0xA82A};

pascal ComponentResult SGSetChannelBounds (SGChannel c, const Rect *bounds)  = {0x2F3C,0x4,0x82,0x7000,0xA82A};
pascal ComponentResult SGGetChannelBounds (SGChannel c, Rect *bounds)  = {0x2F3C,0x4,0x83,0x7000,0xA82A};

pascal ComponentResult SGSetChannelVolume (SGChannel c, short volume)  = {0x2F3C,0x2,0x84,0x7000,0xA82A};
pascal ComponentResult SGGetChannelVolume (SGChannel c, short *volume)  = {0x2F3C,0x4,0x85,0x7000,0xA82A};

pascal ComponentResult SGGetChannelInfo (SGChannel c, long *channelInfo)  = {0x2F3C,0x4,0x86,0x7000,0xA82A};

pascal ComponentResult SGSetChannelPlayFlags (SGChannel c, long playFlags)  = {0x2F3C,0x4,0x87,0x7000,0xA82A};
pascal ComponentResult SGGetChannelPlayFlags (SGChannel c, long *playFlags)  = {0x2F3C,0x4,0x88,0x7000,0xA82A};

pascal ComponentResult SGSetChannelMaxFrames (SGChannel c, long frameCount)  = {0x2F3C,0x4,0x89,0x7000,0xA82A};
pascal ComponentResult SGGetChannelMaxFrames (SGChannel c, long *frameCount)  = {0x2F3C,0x4,0x8A,0x7000,0xA82A};

pascal ComponentResult SGSetChannelRefCon (SGChannel c, long refCon)  = {0x2F3C,0x4,0x8B,0x7000,0xA82A};

pascal ComponentResult SGSetChannelClip (SGChannel c, RgnHandle theClip)  = {0x2F3C,0x4,0x8C,0x7000,0xA82A};

pascal ComponentResult SGGetChannelClip (SGChannel c, RgnHandle *theClip)  = {0x2F3C,0x4,0x8D,0x7000,0xA82A};

pascal ComponentResult SGGetChannelSampleDescription (SGChannel c, Handle sampleDesc)  = {0x2F3C,0x4,0x8E,0x7000,0xA82A};

pascal ComponentResult SGGetChannelDeviceList (SGChannel c, long selectionFlags, SGDeviceList *list)  = {0x2F3C,0x8,0x8F,0x7000,0xA82A};

pascal ComponentResult SGSetChannelDevice (SGChannel c, StringPtr name)  = {0x2F3C,0x4,0x90,0x7000,0xA82A};

pascal ComponentResult SGSetChannelMatrix (SGChannel c, const MatrixRecord *m)  = {0x2F3C,0x4,0x91,0x7000,0xA82A};

pascal ComponentResult SGGetChannelMatrix (SGChannel c, MatrixRecord *m)  = {0x2F3C,0x4,0x92,0x7000,0xA82A};

pascal ComponentResult SGGetChannelTimeScale (SGChannel c, TimeScale *scale)  = {0x2F3C,0x4,0x93,0x7000,0xA82A};

/*
	calls from seqGrab to Channel
*/

pascal ComponentResult SGInitChannel (SGChannel c, SeqGrabComponent owner)  = {0x2F3C,0x4,0x180,0x7000,0xA82A};
pascal ComponentResult SGWriteSamples (SGChannel c, Movie m, AliasHandle theFile)  = {0x2F3C,0x8,0x181,0x7000,0xA82A};
pascal ComponentResult SGGetDataRate (SGChannel c, long *bytesPerSecond)  = {0x2F3C,0x4,0x182,0x7000,0xA82A};
pascal ComponentResult SGAlignChannelRect (SGChannel c, Rect *r)  = {0x2F3C,0x4,0x183,0x7000,0xA82A};

/*
	Dorky dialog panel calls
*/

pascal ComponentResult SGPanelGetDitl (SeqGrabComponent s, Handle *ditl)  = {0x2F3C,0x4,0x200,0x7000,0xA82A};
pascal ComponentResult SGPanelGetTitle (SeqGrabComponent s, Str255 title)  = {0x2F3C,0x4,0x201,0x7000,0xA82A};
pascal ComponentResult SGPanelCanRun (SeqGrabComponent s, SGChannel c)  = {0x2F3C,0x4,0x202,0x7000,0xA82A};
pascal ComponentResult SGPanelInstall (SeqGrabComponent s, SGChannel c, DialogPtr d, short itemOffset)  = {0x2F3C,0xA,0x203,0x7000,0xA82A};
pascal ComponentResult SGPanelEvent (SeqGrabComponent s, SGChannel c, DialogPtr d, short itemOffset,
		EventRecord *theEvent, short *itemHit, Boolean *handled)  = {0x2F3C,0x16,0x204,0x7000,0xA82A};
pascal ComponentResult SGPanelItem (SeqGrabComponent s, SGChannel c, DialogPtr d, short itemOffset, short itemNum)  = {0x2F3C,0xC,0x205,0x7000,0xA82A};
pascal ComponentResult SGPanelRemove (SeqGrabComponent s, SGChannel c, DialogPtr d, short itemOffset)  = {0x2F3C,0xA,0x206,0x7000,0xA82A};
pascal ComponentResult SGPanelSetGrabber (SeqGrabComponent s, SeqGrabComponent sg)  = {0x2F3C,0x4,0x207,0x7000,0xA82A};
pascal ComponentResult SGPanelSetResFile (SeqGrabComponent s, short resRef)  = {0x2F3C,0x2,0x208,0x7000,0xA82A};
pascal ComponentResult SGPanelGetSettings (SeqGrabComponent s, SGChannel c, UserData *ud, long flags)  = {0x2F3C,0xC,0x209,0x7000,0xA82A};
pascal ComponentResult SGPanelSetSettings (SeqGrabComponent s, SGChannel c, UserData ud, long flags)  = {0x2F3C,0xC,0x20A,0x7000,0xA82A};
pascal ComponentResult SGPanelValidateInput (SeqGrabComponent s, Boolean *ok)  = {0x2F3C,0x4,0x20B,0x7000,0xA82A};
#ifdef __cplusplus
}
#endif __cplusplus


/*** Sequence Grab VIDEO CHANNEL Component Stuff ***/

/*
	Video stuff
*/

	typedef struct SGCompressInfo {
		Ptr				buffer;
		unsigned long	bufferSize;
		unsigned char	similarity;
		unsigned char	reserved;
	} SGCompressInfo;

typedef pascal ComponentResult (*GrabProc)(SGChannel c, short bufferNum, long refCon);
typedef pascal ComponentResult (*GrabCompleteProc)(SGChannel c, short bufferNum, Boolean *done, long refCon);

typedef pascal ComponentResult (*DisplayProc)(SGChannel c, short bufferNum, MatrixRecord *mp, RgnHandle clipRgn, long refCon);

typedef pascal ComponentResult (*CompressProc)(SGChannel c, short bufferNum, long refCon);
typedef pascal ComponentResult (*CompressCompleteProc)(SGChannel c, short bufferNum,
										Boolean *done, SGCompressInfo *ci, long refCon);

typedef pascal ComponentResult (*AddFrameProc)(SGChannel c, short bufferNum, TimeValue atTime, TimeScale scale,
							const SGCompressInfo *ci, long refCon);

typedef pascal ComponentResult (*TransferFrameProc)(SGChannel c, short bufferNum, MatrixRecord *mp, RgnHandle clipRgn, long refCon);

typedef pascal ComponentResult (*GrabCompressCompleteProc)(SGChannel c, Boolean *done, SGCompressInfo *ci, TimeRecord *t, long refCon);
typedef pascal ComponentResult (*DisplayCompressProc)(SGChannel c, Ptr dataPtr, ImageDescriptionHandle desc, MatrixRecord *mp, RgnHandle clipRgn, long refCon);

	struct VideoBottles {
		short						procCount;
		GrabProc					grabProc;
		GrabCompleteProc			grabCompleteProc;
		DisplayProc					displayProc;
		CompressProc				compressProc;
		CompressCompleteProc		compressCompleteProc;
		AddFrameProc				addFrameProc;
		TransferFrameProc			transferFrameProc;
		GrabCompressCompleteProc	grabCompressCompleteProc;
		DisplayCompressProc			displayCompressProc;
	};
	typedef struct VideoBottles VideoBottles;


#ifdef __cplusplus
extern "C" {
#endif __cplusplus

pascal ComponentResult SGGetSrcVideoBounds (SGChannel c, Rect *r)  = {0x2F3C,0x4,0x100,0x7000,0xA82A};
pascal ComponentResult SGSetVideoRect (SGChannel c, Rect *r)  = {0x2F3C,0x4,0x101,0x7000,0xA82A};
pascal ComponentResult SGGetVideoRect (SGChannel c, Rect *r)  = {0x2F3C,0x4,0x102,0x7000,0xA82A};

pascal ComponentResult SGGetVideoCompressorType (SGChannel c, OSType *compressorType)  = {0x2F3C,0x4,0x103,0x7000,0xA82A};
pascal ComponentResult SGSetVideoCompressorType (SGChannel c, OSType compressorType)  = {0x2F3C,0x4,0x104,0x7000,0xA82A};

pascal ComponentResult SGSetVideoCompressor (SGChannel c, short depth, CompressorComponent compressor,
			CodecQ spatialQuality, CodecQ temporalQuality, long keyFrameRate)  = {0x2F3C,0x12,0x105,0x7000,0xA82A};
pascal ComponentResult SGGetVideoCompressor (SGChannel c, short *depth, CompressorComponent *compressor,
			CodecQ *spatialQuality, CodecQ *temporalQuality, long *keyFrameRate)  = {0x2F3C,0x14,0x106,0x7000,0xA82A};

pascal ComponentInstance SGGetVideoDigitizerComponent (SGChannel c)  = {0x2F3C,0,0x107,0x7000,0xA82A};
pascal ComponentResult SGSetVideoDigitizerComponent (SGChannel c, ComponentInstance vdig)  = {0x2F3C,0x4,0x108,0x7000,0xA82A};
pascal ComponentResult SGVideoDigitizerChanged (SGChannel c)  = {0x2F3C,0,0x109,0x7000,0xA82A};

pascal ComponentResult SGSetVideoBottlenecks (SGChannel c, VideoBottles *vb)  = {0x2F3C,0x4,0x10A,0x7000,0xA82A};
pascal ComponentResult SGGetVideoBottlenecks (SGChannel c, VideoBottles *vb)  = {0x2F3C,0x4,0x10B,0x7000,0xA82A};

pascal ComponentResult SGGrabFrame (SGChannel c, short bufferNum)  = {0x2F3C,0x2,0x10C,0x7000,0xA82A};
pascal ComponentResult SGGrabFrameComplete (SGChannel c, short bufferNum, Boolean *done)  = {0x2F3C,0x6,0x10D,0x7000,0xA82A};
pascal ComponentResult SGDisplayFrame (SGChannel c, short bufferNum, MatrixRecord *mp, RgnHandle clipRgn)  = {0x2F3C,0xA,0x10E,0x7000,0xA82A};

pascal ComponentResult SGCompressFrame (SGChannel c, short bufferNum)  = {0x2F3C,0x2,0x10F,0x7000,0xA82A};
pascal ComponentResult SGCompressFrameComplete (SGChannel c, short bufferNum, Boolean *done, SGCompressInfo *ci)  = {0x2F3C,0xA,0x110,0x7000,0xA82A};

pascal ComponentResult SGAddFrame (SGChannel c, short bufferNum, TimeValue atTime, TimeScale scale, const SGCompressInfo *ci)  = {0x2F3C,0xE,0x111,0x7000,0xA82A};

pascal ComponentResult SGTransferFrameForCompress (SGChannel c, short bufferNum, MatrixRecord *mp, RgnHandle clipRgn)  = {0x2F3C,0xA,0x112,0x7000,0xA82A};

pascal ComponentResult SGSetCompressBuffer (SGChannel c, short depth, const Rect *compressSize)  = {0x2F3C,0x6,0x113,0x7000,0xA82A};

pascal ComponentResult SGGetCompressBuffer (SGChannel c, short *depth, Rect *compressSize)  = {0x2F3C,0x8,0x114,0x7000,0xA82A};

pascal ComponentResult SGGetBufferInfo (SGChannel c, short bufferNum, 
					PixMapHandle *bufferPM, Rect *bufferRect,
					GWorldPtr *compressBuffer, Rect *compressBufferRect)  = {0x2F3C,0x12,0x115,0x7000,0xA82A};

pascal ComponentResult SGSetUseScreenBuffer (SGChannel c, Boolean useScreenBuffer)  = {0x2F3C,0x2,0x116,0x7000,0xA82A};

pascal ComponentResult SGGetUseScreenBuffer (SGChannel c, Boolean *useScreenBuffer)  = {0x2F3C,0x4,0x117,0x7000,0xA82A};

pascal ComponentResult SGGrabCompressComplete (SGChannel c, Boolean *done, SGCompressInfo *ci, TimeRecord *tr)  = {0x2F3C,0xC,0x118,0x7000,0xA82A};
pascal ComponentResult SGDisplayCompress (SGChannel c, Ptr dataPtr, ImageDescriptionHandle desc, MatrixRecord *mp, RgnHandle clipRgn)  = {0x2F3C,0x10,0x119,0x7000,0xA82A};

pascal ComponentResult SGSetFrameRate (SGChannel c, Fixed frameRate)  = {0x2F3C,0x4,0x11A,0x7000,0xA82A};

pascal ComponentResult SGGetFrameRate (SGChannel c, Fixed *frameRate)  = {0x2F3C,0x4,0x11B,0x7000,0xA82A};
#ifdef __cplusplus
}
#endif __cplusplus


/*** Sequence Grab SOUND CHANNEL Component Stuff ***/


/*
	Sound stuff
*/

#ifdef __cplusplus
extern "C" {
#endif __cplusplus

pascal ComponentResult SGSetSoundInputDriver (SGChannel c, const Str255 driverName)  = {0x2F3C,0x4,0x100,0x7000,0xA82A};
pascal long SGGetSoundInputDriver (SGChannel c)  = {0x2F3C,0,0x101,0x7000,0xA82A};
pascal ComponentResult SGSoundInputDriverChanged (SGChannel c)  = {0x2F3C,0,0x102,0x7000,0xA82A};

pascal ComponentResult SGSetSoundRecordChunkSize (SGChannel c, long seconds)  = {0x2F3C,0x4,0x103,0x7000,0xA82A};
pascal long SGGetSoundRecordChunkSize (SGChannel c)  = {0x2F3C,0,0x104,0x7000,0xA82A};

pascal ComponentResult SGSetSoundInputRate (SGChannel c, Fixed rate)  = {0x2F3C,0x4,0x105,0x7000,0xA82A};
pascal Fixed SGGetSoundInputRate (SGChannel c)  = {0x2F3C,0,0x106,0x7000,0xA82A};

pascal ComponentResult SGSetSoundInputParameters (SGChannel c, short sampleSize, short numChannels,
						OSType compressionType)  = {0x2F3C,0x8,0x107,0x7000,0xA82A};
pascal ComponentResult SGGetSoundInputParameters (SGChannel c, short *sampleSize, short *numChannels,
						OSType *compressionType)  = {0x2F3C,0xC,0x108,0x7000,0xA82A};
#ifdef __cplusplus
}
#endif __cplusplus


#define sgChannelAtom 'chan'

#define sgChannelSettingsAtom 'ctom'
#define sgChannelDescription 'cdsc'
#define sgChannelSettings 'cset'

#define sgDeviceNameType 'name'
#define sgUsageType 'use '
#define sgPlayFlagsType 'plyf'
#define sgClipType 'clip'
#define sgMatrixType 'mtrx'
#define sgVolumeType 'volu'

#define sgPanelSettingsAtom 'ptom'
#define sgPanelDescription 'pdsc'
#define sgPanelSettings 'pset'

#define sgcSoundCompressionType 'scmp'
#define sgcSoundSampleRateType 'srat'
#define sgcSoundChannelCountType 'schn'
#define sgcSoundSampleSizeType 'ssiz'
#define sgcSoundInputType 'sinp'
#define sgcSoundGainType 'gain'

#define sgcVideoHueType 'hue '
#define sgcVideoSaturationType 'satr'
#define sgcVideoContrastType 'trst'
#define sgcVideoSharpnessType 'shrp'
#define sgcVideoBrigtnessType 'brit'
#define sgcVideoBlackLevelType 'blkl'
#define sgcVideoWhiteLevelType 'whtl'

#define sgcVideoInputType 'vinp'
#define sgcVideoFormatType 'vstd'
#define sgcVideoFilterType 'vflt'

#define sgcVideoRectType 'vrct'
#define sgVideoDigitizerType 'vdig'

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
	kSGGetStorageSpaceRemainingSelect = 0x1A,
	kSGGetTimeRemainingSelect = 0x1B,
	kSGGrabPictSelect = 0x1C,
	kSGGetLastMovieResIDSelect = 0x1D,
	kSGSetFlagsSelect = 0x1E,
	kSGGetFlagsSelect = 0x1F,
	kSGSetDataProcSelect = 0x20,
	kSGNewChannelFromComponentSelect = 0x21,
	kSGDisposeDeviceListSelect = 0x22,
	kSGAppendDeviceListToMenuSelect = 0x23,
	kSGSetSettingsSelect = 0x24,
	kSGGetSettingsSelect = 0x25,
	kSGGetIndChannelSelect = 0x26,
	kSGUpdateSelect = 0x27,
	kSGGetPauseSelect = 0x28,
	kSGSettingsDialogSelect = 0x29,
	kSGGetAlignmentProcSelect = 0x2A,
	kSGSetChannelSettingsSelect = 0x2B,
	kSGGetChannelSettingsSelect = 0x2C,
	kSGWriteMovieDataSelect = 0x100,
	kSGAddFrameReferenceSelect = 0x101,
	kSGGetNextFrameReferenceSelect = 0x102,
	kSGGetTimeBaseSelect = 0x103,
	kSGSortDeviceListSelect = 0x104,
	kSGAddMovieDataSelect = 0x105,
	kSGChangedSourceSelect = 0x106,
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
	kSGCGetChannelMaxFramesSelect = 0x8A,
	kSGCSetChannelRefConSelect = 0x8B,
	kSGCSetChannelClipSelect = 0x8C,
	kSGCGetChannelClipSelect = 0x8D,
	kSGCGetChannelSampleDescriptionSelect = 0x8E,
	kSGCGetChannelDeviceListSelect = 0x8F,
	kSGCSetChannelDeviceSelect = 0x90,
	kSGCSetChannelMatrixSelect = 0x91,
	kSGCGetChannelMatrixSelect = 0x92,
	kSGCGetChannelTimeScaleSelect = 0x93,
	kSGCInitChannelSelect = 0x180,
	kSGCWriteSamplesSelect = 0x181,
	kSGCGetDataRateSelect = 0x182,
	kSGCAlignChannelRectSelect = 0x183,
	kSGCPanelGetDitlSelect = 0x200,
	kSGCPanelGetTitleSelect = 0x201,
	kSGCPanelCanRunSelect = 0x202,
	kSGCPanelInstallSelect = 0x203,
	kSGCPanelEventSelect = 0x204,
	kSGCPanelItemSelect = 0x205,
	kSGCPanelRemoveSelect = 0x206,
	kSGCPanelSetGrabberSelect = 0x207,
	kSGCPanelSetResFileSelect = 0x208,
	kSGCPanelGetSettingsSelect = 0x209,
	kSGCPanelSetSettingsSelect = 0x20A,
	kSGCPanelValidateInputSelect = 0x20B,
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
	kSGCSetVideoBottlenecksSelect = 0x10A,
	kSGCGetVideoBottlenecksSelect = 0x10B,
	kSGCGrabFrameSelect = 0x10C,
	kSGCGrabFrameCompleteSelect = 0x10D,
	kSGCDisplayFrameSelect = 0x10E,
	kSGCCompressFrameSelect = 0x10F,
	kSGCCompressFrameCompleteSelect = 0x110,
	kSGCAddFrameSelect = 0x111,
	kSGCTransferFrameForCompressSelect = 0x112,
	kSGCSetCompressBufferSelect = 0x113,
	kSGCGetCompressBufferSelect = 0x114,
	kSGCGetBufferInfoSelect = 0x115,
	kSGCSetUseScreenBufferSelect = 0x116,
	kSGCGetUseScreenBufferSelect = 0x117,
	kSGCGrabCompressCompleteSelect = 0x118,
	kSGCDisplayCompressSelect = 0x119,
	kSGCSetFrameRateSelect = 0x11A,
	kSGCGetFrameRateSelect = 0x11B,
	kSGCSetSoundInputDriverSelect = 0x100,
	kSGCGetSoundInputDriverSelect = 0x101,
	kSGCSoundInputDriverChangedSelect = 0x102,
	kSGCSetSoundRecordChunkSizeSelect = 0x103,
	kSGCGetSoundRecordChunkSizeSelect = 0x104,
	kSGCSetSoundInputRateSelect = 0x105,
	kSGCGetSoundInputRateSelect = 0x106,
	kSGCSetSoundInputParametersSelect = 0x107,
	kSGCGetSoundInputParametersSelect = 0x108 
};

/* Standard type for video digitizers */

#define	videoDigitizerComponentType		'vdig'		
#define vdigInterfaceRev				2L

/* Input Format Standards */

#define	ntscIn			0				/* current input format */
#define	currentIn		0				/* ntsc input format */
#define	palIn			1				/* pal input format */
#define	secamIn			2				/* secam input format */
#define	ntscReallyIn	3				/* ntsc input format */

/* Input Formats */

#define	compositeIn		0				/* input is composite format */
#define	sVideoIn		1				/* input is sVideo format */
#define rgbComponentIn	2				/* input is rgb component format */

/* Video Digitizer PlayThru States */

#define vdPlayThruOff		0
#define vdPlayThruOn		1

/* Input Color Space Modes */

#define vdDigitizerBW		0			/* black and white */
#define vdDigitizerRGB		1			/* rgb color */

/* Phase Lock Loop Modes */

#define vdBroadcastMode		0			/* Broadcast / Laser Disk video mode */
#define vdVTRMode			1			/* VCR / Magnetic media mode */

/* Field Select Options */
#define vdUseAnyField 0					/* Digitizers choice on field use */
#define vdUseOddField 1					/* Use odd field for half size vert and smaller */
#define vdUseEvenField 2				/* Use even field for half size vert and smaller */

/* vdig types */

#define vdTypeBasic			0			/* basic, no clipping */
#define vdTypeAlpha			1			/* supports clipping with alpha channel */
#define vdTypeMask			2			/* supports clipping with mask plane */
#define vdTypeKey			3			/* supports clipping with key color(s) */

/* Digitizer Error Codes */

#define	digiUnimpErr	-2201 			/* feature unimplemented */
#define	qtParamErr		-2202			/* bad input parameter (out of range, etc) */
#define	matrixErr		-2203			/* bad matrix, digitizer did nothing */
#define	notExactMatrix	-2204			/* warning of bad matrix, digitizer did its best */
#define	noMoreKeyColors	-2205			/* all key indexes in use */
#define	notExactSize	-2206			/* Can’t do exact size requested */
#define	badDepth		-2207			/* Can’t digitize into this depth */
#define	noDMA			-2208			/* Can’t do DMA digitizing (i.e. can't go to requested dest */
#define badCallOrder	-2209			/* Usually due to a status call being called prior to being setup first */

/* Digitizer Input Capability/Current Flags	*/

#define	digiInDoesNTSC		(1L<<0)		/* digitizer supports NTSC input format */
#define	digiInDoesPAL		(1L<<1)		/* digitizer supports PAL input format */
#define	digiInDoesSECAM		(1L<<2)		/* digitizer supports SECAM input format */
#define digiInDoesGenLock	(1L<<7)		/* digitizer does genlock */

#define	digiInDoesComposite	(1L<<8)		/* digitizer supports composite input type */
#define	digiInDoesSVideo	(1L<<9)		/* digitizer supports S-Video input type */
#define digiInDoesComponent (1L<<10)	/* digitizer supports component (rgb) input type */
#define	digiInVTR_Broadcast	(1L<<11)	/* digitizer can differentiate between the two */

#define	digiInDoesColor		(1L<<12)	/* digitizer supports color */
#define	digiInDoesBW		(1L<<13)	/* digitizer supports black & white */

/* Digitizer Input Current Flags (these are valid only during active operating conditions)	*/

#define	digiInSignalLock	(1L<<31)	/* digitizer detects input signal is locked */
										/* this bit = horiz lock || vertical lock */

/* Digitizer Output Capability/Current Flags */

#define	digiOutDoes1			(1L<<0)		/* digitizer supports 1 bit pixels */
#define	digiOutDoes2			(1L<<1)		/* digitizer supports 2 bit pixels */
#define	digiOutDoes4			(1L<<2)		/* digitizer supports 4 bit pixels */
#define	digiOutDoes8			(1L<<3)		/* digitizer supports 8 bit pixels */
#define	digiOutDoes16			(1L<<4)		/* digitizer supports 16 bit pixels */
#define	digiOutDoes32			(1L<<5)		/* digitizer supports 32 bit pixels */
#define	digiOutDoesDither		(1L<<6)		/* digitizer dithers in indexed modes */
#define	digiOutDoesStretch		(1L<<7)		/* digitizer can arbitrarily stretch */
#define	digiOutDoesShrink		(1L<<8)		/* digitizer can arbitrarily shrink */
#define	digiOutDoesMask			(1L<<9)		/* digitizer can mask to clipping regions */

#define	digiOutDoesDouble		(1L<<11)	/* digitizer can stretch to exactly double size */
#define	digiOutDoesQuad			(1L<<12)	/* digitizer can stretch exactly quadruple size */
#define	digiOutDoesQuarter		(1L<<13)	/* digitizer can shrink to exactly quarter size */
#define	digiOutDoesSixteenth	(1L<<14)	/* digitizer can shrink to exactly sixteenth size */

#define	digiOutDoesRotate		(1L<<15)	/* digitizer supports rotate transformations */
#define	digiOutDoesHorizFlip	(1L<<16)	/* digitizer supports horizontal flips Sx < 0 */
#define	digiOutDoesVertFlip		(1L<<17)	/* digitizer supports vertical flips Sy < 0 */
#define	digiOutDoesSkew			(1L<<18)	/* digitizer supports skew (shear,twist) */
#define	digiOutDoesBlend		(1L<<19)
#define	digiOutDoesWarp			(1L<<20)

#define	digiOutDoesHW_DMA		(1L<<21)	/* digitizer not constrained to local device */
#define digiOutDoesHWPlayThru	(1L<<22)	/* digitizer doesn't need time to play thru */
#define	digiOutDoesILUT			(1L<<23)	/* digitizer does inverse LUT for index modes */
#define	digiOutDoesKeyColor		(1L<<24)	/* digitizer does key color functions too */
#define digiOutDoesAsyncGrabs	(1L<<25)	/* digitizer supports async grabs */
#define digiOutDoesUnreadableScreenBits (1L<<26)	/* playthru doesn't generate readable bits on screen*/
#define digiOutDoesCompress		(1L<<27)	/* supports alternate output data types */
#define digiOutDoesCompressOnly	(1L<<28)	/* can't provide raw frames anywhere */
#define digiOutDoesPlayThruDuringCompress (1L<<29)	/* digi can do playthru while providing compressed data */

/* Types */

typedef ComponentInstance VideoDigitizerComponent;
typedef ComponentResult VideoDigitizerError;

typedef struct {
	short		vdigType;
	long 		inputCapabilityFlags;
	long 		outputCapabilityFlags;	
	long 		inputCurrentFlags;
	long 		outputCurrentFlags;
	short		slot;					/* temporary for connection purposes */
	GDHandle	gdh;					/* temporary for digitizers that have preferred screen */
	GDHandle	maskgdh;				/* temporary for digitizers that have mask planes */
	short		minDestHeight;			/* Smallest resizable height */		
	short		minDestWidth;			/* Smallest resizable width */
	short		maxDestHeight;			/* Largest resizable height */
	short		maxDestWidth;			/* Largest resizable height */
	short		blendLevels;			/* Number of blend levels supported (2 if 1 bit mask) */
	long		reserved;				/* reserved */
} DigitizerInfo;

typedef struct {
	long		type;
	long		reserved;
} VdigType;

typedef struct {
	short		count;
	VdigType	list[1];
} VdigTypeList;

typedef struct {
	PixMapHandle	dest;
	Point			location;
	long			reserved;
} VdigBufferRec;

typedef struct {
	short			count;
	MatrixRecordPtr	matrix;
	RgnHandle		mask;
	VdigBufferRec	list[1];
} VdigBufferRecList;

typedef VdigBufferRecList *VdigBufferRecListPtr, **VdigBufferRecListHandle;

typedef pascal void (*VdigIntProc)(long flags, long refcon);

typedef struct VDCompressionList {
	CodecComponent		codec;
	CodecType			cType;
	Str63				typeName;
	Str63				name;
	long				formatFlags;
	long				compressFlags;
	long				reserved;
} VDCompressionList, *VDCompressionListPtr, **VDCompressionListHandle;

enum {
	dmaDepth1 = 1,
	dmaDepth2 = 2,
	dmaDepth4 = 4 ,
	dmaDepth8 = 8,
	dmaDepth16 = 16,
	dmaDepth32 = 32,
	dmaDepth2Gray = 64,
	dmaDepth4Gray = 128,
	dmaDepth8Gray = 256
};



// number of vdig calls
enum {
	kvdigSelectors = 82
};

#ifdef __cplusplus
extern "C" {
#endif __cplusplus
pascal VideoDigitizerError VDGetMaxSrcRect(VideoDigitizerComponent ci, short inputStd, Rect *maxSrcRect) 	= {0x2F3C,0x6,0x1,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetActiveSrcRect(VideoDigitizerComponent ci, short inputStd, Rect *activeSrcRect) 	= {0x2F3C,0x6,0x2,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetDigitizerRect(VideoDigitizerComponent ci, Rect *digitizerRect) 	= {0x2F3C,0x4,0x3,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetDigitizerRect(VideoDigitizerComponent ci, Rect *digitizerRect) 	= {0x2F3C,0x4,0x4,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetVBlankRect(VideoDigitizerComponent ci, short inputStd, Rect *vBlankRect) 	= {0x2F3C,0x6,0x5,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetMaskPixMap(VideoDigitizerComponent ci, PixMapHandle maskPixMap) 	= {0x2F3C,0x4,0x6,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetPlayThruDestination(VideoDigitizerComponent ci, PixMapHandle *dest, Rect *destRect,
			 MatrixRecord *m, RgnHandle *mask) 	= {0x2F3C,0x10,0x8,0x7000,0xA82A};
	
pascal VideoDigitizerError VDUseThisCLUT(VideoDigitizerComponent ci, CTabHandle colorTableHandle) 	= {0x2F3C,0x4,0x9,0x7000,0xA82A};		
	
pascal VideoDigitizerError VDSetInputGammaValue(VideoDigitizerComponent ci, Fixed channel1, Fixed channel2, Fixed channel3) 	= {0x2F3C,0xC,0xA,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetInputGammaValue(VideoDigitizerComponent ci, Fixed *channel1, Fixed *channel2, Fixed *channel3) 	= {0x2F3C,0xC,0xB,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetBrightness(VideoDigitizerComponent ci, unsigned short *brightness) 	= {0x2F3C,0x4,0xC,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetBrightness(VideoDigitizerComponent ci, unsigned short *brightness) 	= {0x2F3C,0x4,0xD,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetContrast(VideoDigitizerComponent ci, unsigned short *contrast) 	= {0x2F3C,0x4,0xE,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetHue(VideoDigitizerComponent ci, unsigned short *hue) 	= {0x2F3C,0x4,0xF,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetSharpness(VideoDigitizerComponent ci, unsigned short *sharpness) 	= {0x2F3C,0x4,0x10,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetSaturation(VideoDigitizerComponent ci, unsigned short *saturation) 	= {0x2F3C,0x4,0x11,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetContrast(VideoDigitizerComponent ci, unsigned short *contrast) 	= {0x2F3C,0x4,0x12,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetHue(VideoDigitizerComponent ci, unsigned short *hue) 	= {0x2F3C,0x4,0x13,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetSharpness(VideoDigitizerComponent ci, unsigned short *sharpness) 	= {0x2F3C,0x4,0x14,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetSaturation(VideoDigitizerComponent ci, unsigned short *saturation) 	= {0x2F3C,0x4,0x15,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGrabOneFrame(VideoDigitizerComponent ci) 	= {0x2F3C,0,0x16,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetMaxAuxBuffer(VideoDigitizerComponent ci, PixMapHandle *pm, Rect *r) 	= {0x2F3C,0x8,0x17,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetDigitizerInfo(VideoDigitizerComponent ci, DigitizerInfo *info) 	= {0x2F3C,0x4,0x19,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetCurrentFlags(VideoDigitizerComponent ci, long *inputCurrentFlag, long *outputCurrentFlag) 	= {0x2F3C,0x8,0x1A,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetKeyColor(VideoDigitizerComponent ci, long index) 	= {0x2F3C,0x4,0x1B,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetKeyColor(VideoDigitizerComponent ci, long *index) 	= {0x2F3C,0x4,0x1C,0x7000,0xA82A};
	
pascal VideoDigitizerError VDAddKeyColor(VideoDigitizerComponent ci, long *index) 	= {0x2F3C,0x4,0x1D,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetNextKeyColor(VideoDigitizerComponent ci, long index) 	= {0x2F3C,0x4,0x1E,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetKeyColorRange(VideoDigitizerComponent ci, RGBColor *minRGB, RGBColor *maxRGB) 	= {0x2F3C,0x8,0x1F,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetKeyColorRange(VideoDigitizerComponent ci, RGBColor *minRGB, RGBColor *maxRGB) 	= {0x2F3C,0x8,0x20,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetDigitizerUserInterrupt(VideoDigitizerComponent ci, long flags, VdigIntProc userInterruptProc, long refcon) 	= {0x2F3C,0xC,0x21,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetInputColorSpaceMode(VideoDigitizerComponent ci, short colorSpaceMode) 	= {0x2F3C,0x2,0x22,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetInputColorSpaceMode(VideoDigitizerComponent ci, short *colorSpaceMode) 	= {0x2F3C,0x4,0x23,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetClipState(VideoDigitizerComponent ci, short clipEnable) 	= {0x2F3C,0x2,0x24,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetClipState(VideoDigitizerComponent ci, short *clipEnable) 	= {0x2F3C,0x4,0x25,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetClipRgn(VideoDigitizerComponent ci, RgnHandle clipRegion) 	= {0x2F3C,0x4,0x26,0x7000,0xA82A};
	
pascal VideoDigitizerError VDClearClipRgn(VideoDigitizerComponent ci, RgnHandle clipRegion) 	= {0x2F3C,0x4,0x27,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetCLUTInUse(VideoDigitizerComponent ci, CTabHandle *colorTableHandle) 	= {0x2F3C,0x4,0x28,0x7000,0xA82A};		
	
pascal VideoDigitizerError VDSetPLLFilterType(VideoDigitizerComponent ci, short pllType) 	= {0x2F3C,0x2,0x29,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetPLLFilterType(VideoDigitizerComponent ci, short *pllType) 	= {0x2F3C,0x4,0x2A,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetMaskandValue(VideoDigitizerComponent ci, unsigned short blendLevel, long *mask, long *value ) 	= {0x2F3C,0xA,0x2B,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetMasterBlendLevel(VideoDigitizerComponent ci, unsigned short *blendLevel) 	= {0x2F3C,0x4,0x2C,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetPlayThruDestination(VideoDigitizerComponent ci, PixMapHandle dest, Rect *destRect,
								MatrixRecord *m, RgnHandle mask) 	= {0x2F3C,0x10,0x2D,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetPlayThruOnOff(VideoDigitizerComponent ci, short state) 	= {0x2F3C,0x2,0x2E,0x7000,0xA82A};

pascal VideoDigitizerError VDSetFieldPreference(VideoDigitizerComponent ci, short fieldFlag) 	= {0x2F3C,0x2,0x2F,0x7000,0xA82A};

pascal VideoDigitizerError VDGetFieldPreference(VideoDigitizerComponent ci, short *fieldFlag) 	= {0x2F3C,0x4,0x30,0x7000,0xA82A};
	
pascal VideoDigitizerError VDPreflightDestination(VideoDigitizerComponent ci, Rect *digitizerRect, PixMap **dest, 
								Rect *destRect, MatrixRecord *m) 	= {0x2F3C,0x10,0x32,0x7000,0xA82A};
	
pascal VideoDigitizerError VDPreflightGlobalRect(VideoDigitizerComponent ci, GrafPtr theWindow, Rect *globalRect) 	= {0x2F3C,0x8,0x33,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetPlayThruGlobalRect(VideoDigitizerComponent ci, GrafPtr theWindow, Rect *globalRect) 	= {0x2F3C,0x8,0x34,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetInputGammaRecord(VideoDigitizerComponent ci, VDGamRecPtr inputGammaPtr) 	= {0x2F3C,0x4,0x35,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetInputGammaRecord(VideoDigitizerComponent ci, VDGamRecPtr *inputGammaPtr) 	= {0x2F3C,0x4,0x36,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetBlackLevelValue(VideoDigitizerComponent ci, unsigned short *blackLevel) 	= {0x2F3C,0x4,0x37,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetBlackLevelValue(VideoDigitizerComponent ci, unsigned short *blackLevel) 	= {0x2F3C,0x4,0x38,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetWhiteLevelValue(VideoDigitizerComponent ci, unsigned short *whiteLevel) 	= {0x2F3C,0x4,0x39,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetWhiteLevelValue(VideoDigitizerComponent ci, unsigned short *whiteLevel) 	= {0x2F3C,0x4,0x3A,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetVideoDefaults(VideoDigitizerComponent ci, 
		unsigned short *blackLevel, unsigned short *whiteLevel,
		unsigned short *brightness, unsigned short *hue, unsigned short *saturation,
		unsigned short *contrast, unsigned short *sharpness) 	= {0x2F3C,0x1C,0x3B,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetNumberOfInputs(VideoDigitizerComponent ci, short *inputs) 	= {0x2F3C,0x4,0x3C,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetInputFormat(VideoDigitizerComponent ci, short input, short *format) 	= {0x2F3C,0x6,0x3D,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetInput(VideoDigitizerComponent ci, short input) 	= {0x2F3C,0x2,0x3E,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGetInput(VideoDigitizerComponent ci, short *input) 	= {0x2F3C,0x4,0x3F,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetInputStandard(VideoDigitizerComponent ci, short inputStandard) 	= {0x2F3C,0x2,0x40,0x7000,0xA82A};
	
pascal VideoDigitizerError VDSetupBuffers(VideoDigitizerComponent ci, VdigBufferRecListHandle bufferList) 	= {0x2F3C,0x4,0x41,0x7000,0xA82A};
	
pascal VideoDigitizerError VDGrabOneFrameAsync(VideoDigitizerComponent ci, short buffer) 	= {0x2F3C,0x2,0x42,0x7000,0xA82A};
	
pascal VideoDigitizerError VDDone(VideoDigitizerComponent ci, short buffer) 	= {0x2F3C,0x2,0x43,0x7000,0xA82A};

pascal VideoDigitizerError VDSetCompression(VideoDigitizerComponent ci, OSType compressType, short depth, Rect *bounds,
			CodecQ spatialQuality, CodecQ temporalQuality, long keyFrameRate) 	= {0x2F3C,0x16,0x44,0x7000,0xA82A};

pascal VideoDigitizerError VDCompressOneFrameAsync(VideoDigitizerComponent ci ) 	= {0x2F3C,0,0x45,0x7000,0xA82A};

pascal VideoDigitizerError VDCompressDone(VideoDigitizerComponent ci, Boolean *done, Ptr *theData, long *dataSize, unsigned char *similarity, TimeRecord *t) 	= {0x2F3C,0x14,0x46,0x7000,0xA82A};

pascal VideoDigitizerError VDReleaseCompressBuffer(VideoDigitizerComponent ci, Ptr bufferAddr) 	= {0x2F3C,0x4,0x47,0x7000,0xA82A};

pascal VideoDigitizerError VDGetImageDescription(VideoDigitizerComponent ci, ImageDescriptionHandle desc) 	= {0x2F3C,0x4,0x48,0x7000,0xA82A};

pascal VideoDigitizerError VDResetCompressSequence(VideoDigitizerComponent ci ) 	= {0x2F3C,0,0x49,0x7000,0xA82A};

pascal VideoDigitizerError VDSetCompressionOnOff(VideoDigitizerComponent ci, Boolean state) 	= {0x2F3C,0x2,0x4A,0x7000,0xA82A};

pascal VideoDigitizerError VDGetCompressionTypes(VideoDigitizerComponent ci, VDCompressionListHandle h) 	= {0x2F3C,0x4,0x4B,0x7000,0xA82A};

pascal VideoDigitizerError VDSetTimeBase(VideoDigitizerComponent ci, TimeBase t) 	= {0x2F3C,0x4,0x4C,0x7000,0xA82A};

pascal VideoDigitizerError VDSetFrameRate(VideoDigitizerComponent ci, Fixed framesPerSecond) 	= {0x2F3C,0x4,0x4D,0x7000,0xA82A};

pascal VideoDigitizerError VDGetDataRate(VideoDigitizerComponent ci, long *milliSecPerFrame, Fixed *framesPerSecond, long *bytesPerSecond) 	= {0x2F3C,0xC,0x4E,0x7000,0xA82A};

pascal VideoDigitizerError VDGetSoundInputDriver(VideoDigitizerComponent ci, Str255 soundDriverName) 	= {0x2F3C,0x4,0x4F,0x7000,0xA82A};

pascal VideoDigitizerError VDGetDMADepths(VideoDigitizerComponent ci, long *depthArray, long *preferredDepth) 	= {0x2F3C,0x8,0x50,0x7000,0xA82A};

pascal VideoDigitizerError VDGetPreferredTimeScale(VideoDigitizerComponent ci, TimeScale *preferred) 	= {0x2F3C,0x4,0x51,0x7000,0xA82A};

pascal VideoDigitizerError VDReleaseAsyncBuffers(VideoDigitizerComponent ci) 	= {0x2F3C,0,0x52,0x7000,0xA82A};

#ifdef __cplusplus
}
#endif __cplusplus

enum {
	kSelectVDGetMaxSrcRect = 0x1,
	kSelectVDGetActiveSrcRect = 0x2,
	kSelectVDSetDigitizerRect = 0x3,
	kSelectVDGetDigitizerRect = 0x4,
	kSelectVDGetVBlankRect = 0x5,
	kSelectVDGetMaskPixMap = 0x6,
	kSelectVDGetPlayThruDestination = 0x8,
	kSelectVDUseThisCLUT = 0x9,		
	kSelectVDSetInputGammaValue = 0xA,
	kSelectVDGetInputGammaValue = 0xB,
	kSelectVDSetBrightness = 0xC,
	kSelectVDGetBrightness = 0xD,
	kSelectVDSetContrast = 0xE,
	kSelectVDSetHue = 0xF,
	kSelectVDSetSharpness = 0x10,
	kSelectVDSetSaturation = 0x11,
	kSelectVDGetContrast = 0x12,
	kSelectVDGetHue = 0x13,
	kSelectVDGetSharpness = 0x14,
	kSelectVDGetSaturation = 0x15,
	kSelectVDGrabOneFrame = 0x16,
	kSelectVDGetMaxAuxBuffer = 0x17,
	kSelectVDGetDigitizerInfo = 0x19,
	kSelectVDGetCurrentFlags = 0x1A,
	kSelectVDSetKeyColor = 0x1B,
	kSelectVDGetKeyColor = 0x1C,
	kSelectVDAddKeyColor = 0x1D,
	kSelectVDGetNextKeyColor = 0x1E,
	kSelectVDSetKeyColorRange = 0x1F,
	kSelectVDGetKeyColorRange = 0x20,
	kSelectVDSetDigitizerUserInterrupt = 0x21,
	kSelectVDSetInputColorSpaceMode = 0x22,
	kSelectVDGetInputColorSpaceMode = 0x23,
	kSelectVDSetClipState = 0x24,
	kSelectVDGetClipState = 0x25,
	kSelectVDSetClipRgn = 0x26,
	kSelectVDClearClipRgn = 0x27,
	kSelectVDGetCLUTInUse = 0x28,		
	kSelectVDSetPLLFilterType = 0x29,
	kSelectVDGetPLLFilterType = 0x2A,
	kSelectVDGetMaskandValue = 0x2B,
	kSelectVDSetMasterBlendLevel = 0x2C,
	kSelectVDSetPlayThruDestination = 0x2D,
	kSelectVDSetPlayThruOnOff = 0x2E,
	kSelectVDSetFieldPreference = 0x2F,
	kSelectVDGetFieldPreference = 0x30,
	kSelectVDPreflightDestination = 0x32,
	kSelectVDPreflightGlobalRect = 0x33,
	kSelectVDSetPlayThruGlobalRect = 0x34,
	kSelectVDSetInputGammaRecord = 0x35,
	kSelectVDGetInputGammaRecord = 0x36,
	kSelectVDSetBlackLevelValue = 0x37,
	kSelectVDGetBlackLevelValue = 0x38,
	kSelectVDSetWhiteLevelValue = 0x39,
	kSelectVDGetWhiteLevelValue = 0x3A,
	kSelectVDGetVideoDefaults = 0x3B,
	kSelectVDGetNumberOfInputs = 0x3C,
	kSelectVDGetInputFormat = 0x3D,
	kSelectVDSetInput = 0x3E,
	kSelectVDGetInput = 0x3F,
	kSelectVDSetInputStandard = 0x40,
	kSelectVDSetupBuffers = 0x41,
	kSelectVDGrabOneFrameAsync = 0x42,
	kSelectVDDone = 0x43,
	kSelectVDSetCompression = 0x44,
	kSelectVDCompressOneFrameAsync = 0x45,
	kSelectVDCompressDone = 0x46,
	kSelectVDReleaseCompressBuffer = 0x47,
	kSelectVDGetImageDescription = 0x48,
	kSelectVDResetCompressSequence = 0x49,
	kSelectVDSetCompressionOnOff = 0x4A,
	kSelectVDGetCompressionTypes = 0x4B,
	kSelectVDSetTimeBase = 0x4C,
	kSelectVDSetFrameRate = 0x4D,
	kSelectVDGetDataRate = 0x4E,
	kSelectVDGetSoundInputDriver = 0x4F,
	kSelectVDGetDMADepths = 0x50,
	kSelectVDGetPreferredTimeScale = 0x51,
	kSelectVDReleaseAsyncBuffers = 0x52 
};
#define	StandardCompressionType		'scdi'
#define	StandardCompressionSubType	'imag'


typedef pascal Boolean (*SCModalFilterProcPtr)(DialogPtr theDialog,
	EventRecord *theEvent, short *itemHit, long refcon);

typedef pascal short (*SCModalHookProcPtr)(DialogPtr theDialog,
	short itemHit, void *params, long refcon);


//	Preference flags.

#define	scListEveryCodec		(1L<<1)
#define	scAllowZeroFrameRate	(1L<<2)
#define	scAllowZeroKeyFrameRate	(1L<<3)
#define	scShowBestDepth			(1L<<4)
#define	scUseMovableModal		(1L<<5)


//	Possible test flags for setting test image.

#define	scPreferCropping			(1<<0)
#define	scPreferScaling				(1<<1)
#define scPreferScalingAndCropping	(scPreferScaling + scPreferCropping)


//	Dimensions of the image preview box.

#define	scTestImageWidth	80
#define	scTestImageHeight	80


//	Possible items returned by hookProc.

#define	scOKItem				1
#define	scCancelItem			2
#define	scCustomItem			3

//	Result returned when user cancelled.

#define	scUserCancelled			1


// Component selectors

#define	scPositionRect				2
#define	scPositionDialog			3
#define	scSetTestImagePictHandle	4
#define	scSetTestImagePictFile		5
#define	scSetTestImagePixMap		6
#define	scGetBestDeviceRect			7

#define	scRequestImageSettings		10
#define	scCompressImage				11
#define	scCompressPicture			12
#define	scCompressPictureFile		13
#define	scRequestSequenceSettings	14
#define	scCompressSequenceBegin		15
#define	scCompressSequenceFrame		16
#define	scCompressSequenceEnd		17
#define	scDefaultPictHandleSettings	18
#define	scDefaultPictFileSettings	19
#define	scDefaultPixMapSettings		20
#define	scGetInfo					21
#define	scSetInfo					22
#define	scNewGWorld					23


//	Get/SetInfo structures.

typedef struct {
	CodecType		codecType;
	CodecComponent	codec;
	short			depth;
	CodecQ			spatialQuality;
} SCSpatialSettings;

typedef struct {
	CodecQ			temporalQuality;
	Fixed			frameRate;
	long			keyFrameRate;
} SCTemporalSettings;

typedef struct {
	long			dataRate;
	long			frameDuration;
	CodecQ			minSpatialQuality;
	CodecQ			minTemporalQuality;
} SCDataRateSettings;

typedef struct {
	SCModalFilterProcPtr	filterProc;
	SCModalHookProcPtr		hookProc;
	long					refcon;
	Str31					customName;
} SCExtendedProcs;


//	Get/SetInfo selectors

#define	scSpatialSettingsType	'sptl'		// pointer to SCSpatialSettings struct
#define	scTemporalSettingsType	'tprl'		// pointer to SCTemporalSettings struct
#define	scDataRateSettingsType	'drat'		// pointer to SCDataRateSettings struct
#define	scColorTableType		'clut'		// pointer to CTabHandle
#define	scProgressProcType		'prog'		// pointer to ProgressRecord struct
#define	scExtendedProcsType		'xprc'		// pointer to SCExtendedProcs struct
#define	scPreferenceFlagsType	'pref'		// pointer to long
#define	scSettingsStateType		'ssta'		// pointer to Handle
#define	scSequenceIDType		'sequ'		// pointer to ImageSequence
#define	scWindowPositionType	'wndw'		// pointer to Point
#define	scCodecFlagsType		'cflg'		// pointer to CodecFlags


//	Result returned by Get/SetInfo when type cannot be found.

#define	scTypeNotFoundErr		-8971		// same number as codecExtensionNotFoundErr



#ifdef __cplusplus
extern "C" {
#endif

pascal ComponentResult
SCPositionRect(ComponentInstance ci,Rect *rp,Point *where)
	= {0x2F3C,0x8,0x2,0x7000,0xA82A};

pascal ComponentResult
SCPositionDialog(ComponentInstance ci,short id,Point *where)
	= {0x2F3C,0x6,0x3,0x7000,0xA82A};

pascal ComponentResult
SCSetTestImagePictHandle(ComponentInstance ci, PicHandle testPict, Rect *testRect, short testFlags)
	= {0x2F3C,0xA,0x4,0x7000,0xA82A};

pascal ComponentResult
SCSetTestImagePictFile(ComponentInstance ci, short testFileRef, Rect *testRect, short testFlags)
	= {0x2F3C,0x8,0x5,0x7000,0xA82A};

pascal ComponentResult
SCSetTestImagePixMap(ComponentInstance ci, PixMapHandle testPixMap, Rect *testRect, short testFlags)
	= {0x2F3C,0xA,0x6,0x7000,0xA82A};

pascal ComponentResult
SCGetBestDeviceRect(ComponentInstance ci, Rect *r) 
 	= {0x2F3C,0x4,0x7,0x7000,0xA82A};



pascal ComponentResult
SCRequestImageSettings(ComponentInstance ci)
	= {0x2F3C,0,0xA,0x7000,0xA82A};

pascal ComponentResult
SCCompressImage(ComponentInstance ci,PixMapHandle src,Rect *srcRect,ImageDescriptionHandle *desc,Handle *data)
	= {0x2F3C,0x10,0xB,0x7000,0xA82A};

pascal ComponentResult
SCCompressPicture(ComponentInstance ci,PicHandle srcPicture,PicHandle dstPicture)
	= {0x2F3C,0x8,0xC,0x7000,0xA82A};

pascal ComponentResult
SCCompressPictureFile(ComponentInstance ci,short srcRefNum,short dstRefNum)
	= {0x2F3C,0x4,0xD,0x7000,0xA82A};

pascal ComponentResult
SCRequestSequenceSettings(ComponentInstance ci)
	= {0x2F3C,0,0xE,0x7000,0xA82A};

pascal ComponentResult
SCCompressSequenceBegin(ComponentInstance ci,PixMapHandle src,Rect *srcRect,ImageDescriptionHandle *desc)
	= {0x2F3C,0xC,0xF,0x7000,0xA82A};

pascal ComponentResult
SCCompressSequenceFrame(ComponentInstance ci,PixMapHandle src,Rect *srcRect,Handle *data,long *dataSize,short *notSyncFlag)
	= {0x2F3C,0x14,0x10,0x7000,0xA82A};

pascal ComponentResult
SCCompressSequenceEnd(ComponentInstance ci)
	= {0x2F3C,0,0x11,0x7000,0xA82A};

pascal ComponentResult
SCDefaultPictHandleSettings(ComponentInstance ci,PicHandle srcPicture, short motion)
	= {0x2F3C,0x6,0x12,0x7000,0xA82A};

pascal ComponentResult
SCDefaultPictFileSettings(ComponentInstance ci,short srcRef, short motion)
	= {0x2F3C,0x4,0x13,0x7000,0xA82A};

pascal ComponentResult
SCDefaultPixMapSettings(ComponentInstance ci,PixMapHandle src, short motion)
	= {0x2F3C,0x6,0x14,0x7000,0xA82A};

pascal ComponentResult
SCGetInfo(ComponentInstance ci,OSType type,void *info)
	= {0x2F3C,0x8,0x15,0x7000,0xA82A};

pascal ComponentResult
SCSetInfo(ComponentInstance ci,OSType type,void *info)
	= {0x2F3C,0x8,0x16,0x7000,0xA82A};

pascal ComponentResult
SCNewGWorld(ComponentInstance ci,GWorldPtr *gwp,Rect *rp,GWorldFlags flags)
	= {0x2F3C,0xC,0x17,0x7000,0xA82A};

#ifdef __cplusplus
}
#endif





// For compatibility with earlier linked StdCompression.

typedef struct {
	long			flags;
	CodecType		theCodecType;
	CodecComponent	theCodec;
	CodecQ			spatialQuality;
	CodecQ			temporalQuality;
	short			depth;
	Fixed			frameRate;
	long			keyFrameRate;
	long			reserved1;
	long			reserved2;
} SCParams;


#define	scGetCompression		1

#define	scShowMotionSettings	(1L<<0)

#define	scSettingsChangedItem	-1


#ifdef __cplusplus
extern "C" {
#endif

pascal ComponentInstance OpenStdCompression(void);

pascal ComponentResult
SCGetCompressionExtended(ComponentInstance ci,SCParams *params,Point where,
	SCModalFilterProcPtr filterProc,SCModalHookProcPtr hookProc,long refcon,StringPtr customName)
	= {0x2F3C,0x18,0x1,0x7000,0xA82A};

pascal ComponentResult
SCGetCompression(ComponentInstance ci,SCParams *params,Point where)
	= {0x42A7,0x42A7,0x42A7,0x42A7,0x2F3C,0x18,0x1,0x7000,0xA82A};

#ifdef __cplusplus
}
#endif




typedef ComponentInstance MovieImportComponent, MovieExportComponent;

#define MovieImportType 'eat '
#define MovieExportType 'spit'

enum {
	canMovieImportHandles = 1,
	canMovieImportFiles = 2,
	hasMovieImportUserInterface = 4,
	canMovieExportHandles = 8,
	canMovieExportFiles = 16,
	hasMovieExportUserInterface = 32,
	dontAutoFileMovieImport = 64
};

enum {
	kMovieImportExportOpenSelect = kComponentOpenSelect,
	kMovieImportExportCloseSelect = kComponentCloseSelect,
	kMovieImportExportCanDoSelect = kComponentCanDoSelect,
	kMovieImportExportVersionSelect = kComponentVersionSelect, 

	kMovieImportHandleSelect = 1,
	kMovieImportFileSelect = 2,
	kMovieImportSetFrameDurationSelect = 3,
	kMovieImportSetSampleDescriptionSelect = 4,
	kMovieImportSetMediaFileSelect = 5,
	kMovieImportSetDimensionsSelect = 6,
	kMovieImportSetChunkSizeSelect = 7,
	kMovieImportSetProgressProcSelect = 8,
	kMovieImportSetAuxiliaryDataSelect = 9,
	kMovieImportSetFromScrapSelect = 10,
	kMovieImportDoUserDialogSelect = 11,
	kMovieImportSetDurationSelect = 12,
	
	kMovieExportToHandleSelect = 128,
	kMovieExportToFileSelect = 129,
	kMovieExportDoUserDialogSelect = 130,
	kMovieExportGetAuxiliaryDataSelect = 131,
	kMovieExportSetProgressProcSelect = 132
};

enum {
	movieImportCreateTrack = 1,
	movieImportInParallel = 2,
	movieImportMustUseTrack = 4
};

enum {
	movieImportResultUsedMultipleTracks = 8
};

#ifdef __cplusplus
extern "C" {
#endif __cplusplus

pascal ComponentResult MovieImportHandle(MovieImportComponent ci, Handle dataH,
		Movie theMovie, Track targetTrack, Track *usedTrack, TimeValue atTime, TimeValue *addedDuration,
		long inFlags, long *outFlags) = {0x2F3C,0x20,0x1,0x7000,0xA82A};

pascal ComponentResult MovieImportFile(MovieImportComponent ci, const FSSpec *theFile,
		Movie theMovie, Track targetTrack, Track *usedTrack, TimeValue atTime, TimeValue *addedDuration,
		long inFlags, long *outFlags) = {0x2F3C,0x20,0x2,0x7000,0xA82A};

pascal ComponentResult MovieImportSetSampleDuration(MovieImportComponent ci, TimeValue duration, TimeScale scale) = {0x2F3C,0x8,0x3,0x7000,0xA82A};

pascal ComponentResult MovieImportSetSampleDescription(MovieImportComponent ci, SampleDescriptionHandle desc, OSType mediaType) = {0x2F3C,0x8,0x4,0x7000,0xA82A};

pascal ComponentResult MovieImportSetMediaFile(MovieImportComponent ci, AliasHandle alias) = {0x2F3C,0x4,0x5,0x7000,0xA82A};

pascal ComponentResult MovieImportSetDimensions(MovieImportComponent ci, Fixed width, Fixed height) = {0x2F3C,0x8,0x6,0x7000,0xA82A};

pascal ComponentResult MovieImportSetChunkSize(MovieImportComponent ci, long chunkSize) = {0x2F3C,0x4,0x7,0x7000,0xA82A};

pascal ComponentResult MovieImportSetProgressProc(MovieImportComponent ci, MovieProgressProcPtr proc, long refcon) = {0x2F3C,0x8,0x8,0x7000,0xA82A};

pascal ComponentResult MovieImportSetAuxiliaryData(MovieImportComponent ci, Handle data, OSType handleType) = {0x2F3C,0x8,0x9,0x7000,0xA82A};

pascal ComponentResult MovieImportSetFromScrap(MovieImportComponent ci, Boolean fromScrap) = {0x2F3C,0x2,0xA,0x7000,0xA82A};

pascal ComponentResult MovieImportDoUserDialog(MovieImportComponent ci, const FSSpec *theFile, Handle theData, Boolean *canceled) = {0x2F3C,0xC,0xB,0x7000,0xA82A};

pascal ComponentResult MovieImportSetDuration(MovieImportComponent ci, TimeValue duration) = {0x2F3C,0x4,0xC,0x7000,0xA82A};


pascal ComponentResult MovieExportToHandle(MovieExportComponent ci, Handle dataH, Movie theMovie, Track onlyThisTrack, TimeValue startTime,
	TimeValue duration) = {0x2F3C,0x14,0x80,0x7000,0xA82A};

pascal ComponentResult MovieExportToFile(MovieExportComponent ci, const FSSpec *theFile, Movie theMovie, Track onlyThisTrack, TimeValue startTime,
	TimeValue duration) = {0x2F3C,0x14,0x81,0x7000,0xA82A};

pascal ComponentResult MovieExportDoUserDialog(MovieExportComponent ci, const FSSpec *theFile, Handle theData, Boolean *canceled) = {0x2F3C,0xC,0x82,0x7000,0xA82A};

pascal ComponentResult MovieExportGetAuxiliaryData(MovieExportComponent ci, Handle dataH, OSType *handleType) = {0x2F3C,0x8,0x83,0x7000,0xA82A};

pascal ComponentResult MovieExportSetProgressProc(MovieExportComponent ci, MovieProgressProcPtr proc, long refcon) = {0x2F3C,0x8,0x84,0x7000,0xA82A};

#ifdef __cplusplus
}
#endif __cplusplus

/***************

	File Preview Components

***************/

typedef ComponentInstance pnotComponent;

enum {
	pnotComponentWantsEvents = 1,
	pnotComponentNeedsNoCache = 2
};

enum {
	kPreviewOpenSelector = 0,
	kPreviewCloseSelector = -1,
	kPreviewCanDoSelector = -2,
	kPreviewVersionSelector = -3, 

	kPreviewShowDataSelector = 1,
	kPreviewMakePreviewSelector = 2,
	kPreviewMakePreviewReferenceSelector = 3,
	kPreviewEventSelector = 4
};

#define ShowFilePreviewComponentType 'pnot'
#define CreateFilePreviewrComponentType 'pmak'

#ifdef __cplusplus
extern "C" {
#endif __cplusplus

pascal ComponentResult PreviewShowData(pnotComponent p, OSType dataType, Handle data,
		const Rect *inHere) = {0x2F3C,0xC,0x1,0x7000,0xA82A};

pascal ComponentResult PreviewMakePreview(pnotComponent p, OSType *previewType, Handle *previewResult,
			const FSSpec *sourceFile, ProgressProcRecordPtr progress) = {0x2F3C,0x10,0x2,0x7000,0xA82A};

pascal ComponentResult PreviewMakePreviewReference(pnotComponent p, OSType *previewType, short *resID,
			const FSSpec *sourceFile) = {0x2F3C,0xC,0x3,0x7000,0xA82A};

pascal ComponentResult PreviewEvent(pnotComponent p, EventRecord *e, Boolean *handledEvent) = {0x2F3C,0x8,0x4,0x7000,0xA82A};
#ifdef __cplusplus
}
#endif __cplusplus
#endif __QUICKTIMECOMPONENTS__
