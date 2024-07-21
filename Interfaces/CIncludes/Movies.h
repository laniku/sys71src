/*
	File:		Movies.h

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 10/8/92	DH		first checked in

*/

/************************************************************

Created: Friday, October 2, 1992 at 11:39 AM
 Movies.h
 C Interface to the Macintosh Libraries


 Copyright Apple Computer, Inc. 1991, 1992
 All rights reserved

************************************************************/

#ifndef __MOVIES__
#define __MOVIES__


#ifndef __QUICKDRAW__
#include <QuickDraw.h>
#endif

#ifndef __ALIASES__
#include <Aliases.h>
#endif

#ifndef __EVENTS__
#include <Events.h>
#endif

#ifndef __MENUS__
#include <Menus.h>
#endif

#ifndef __COMPONENTS__
#include <Components.h>
#endif

#ifndef __IMAGECOMPRESSION__
#include <ImageCompression.h>
#endif

#ifndef kFix1
	#define kFix1			(0x00010000)
#endif

#define gestaltQuickTime 'qtim'

#define MovieFileType 'MooV'

#define MediaHandlerType 'mhlr'
#define DataHandlerType 'dhlr'

#define VideoMediaType 'vide'
#define SoundMediaType 'soun'
#define TextMediaType 'text'
#define GenericMediaType 'gnrc'

#define DoTheRightThing 0L

#define kFullVolume 0x100			/* 8.8 format */
#define kNoVolume 0


	struct MovieRecord {
	 long data[1];
	};
	
	typedef struct MovieRecord MovieRecord;
	typedef MovieRecord *Movie;
	
	struct TrackRecord {
	 long data[1];
	};
	
	typedef struct TrackRecord TrackRecord;
	typedef TrackRecord *Track;
	
	struct MediaRecord {
	 long data[1];
	};
	
	typedef struct MediaRecord MediaRecord;
	typedef MediaRecord *Media;
	
	struct UserDataRecord {
	 long data[1];
	};
	
	typedef struct UserDataRecord UserDataRecord;
	typedef UserDataRecord *UserData;
	
	struct TrackEditStateRecord {
	 long data[1];
	};
	
	typedef struct TrackEditStateRecord TrackEditStateRecord;
	typedef TrackEditStateRecord *TrackEditState;
	
	struct MovieEditStateRecord {
	 long data[1];
	};
	
	typedef struct MovieEditStateRecord MovieEditStateRecord;
	typedef MovieEditStateRecord *MovieEditState;

struct SampleDescription {
	long descSize;
	long dataFormat;
	long resvd1;
	short resvd2;
	short dataRefIndex;
};

	typedef struct SampleDescription SampleDescription;
	typedef SampleDescription *SampleDescriptionPtr, **SampleDescriptionHandle;
	


struct SoundDescription {
	long	descSize;			/* total size of SoundDescription including extra data */
	long	dataFormat;			/*  */
	long	resvd1;				/* reserved for apple use */
	short 	resvd2;
	short 	dataRefIndex;
	short	version;			/* which version is this data */
	short	revlevel;			/* what version of that codec did this */
	long	vendor;				/* whose  codec compressed this data */
	short	numChannels;		/* number of channels of sound */
	short	sampleSize;			/* number of bits per sample */
	short	compressionID;		/* sound compression used, 0 if none */
	short	packetSize;			/* packet size for compression, 0 if no compression */
	Fixed	sampleRate;			/* sample rate sound is captured at */
};

typedef struct SoundDescription SoundDescription;
typedef SoundDescription *SoundDescriptionPtr, **SoundDescriptionHandle;

struct TextDescription {
	long	size;					// Total size of TextDescription
	long	type;					// 'text'

	long	resvd1;
	long	resvd2;

	long	displayFlags;			// see enum below for flag values

	long 	textJustification;		// Can be: teCenter,teFlush -Default,-Right,-Left
	
	RGBColor bgColor;				// Background color
	
	Rect	defaultTextBox;			// Location to place the text within the track bounds
    ScrpSTElement defaultStyle;		// Default style (struct defined in TextEdit.h)

};

typedef struct TextDescription TextDescription;
typedef TextDescription *TextDescriptionPtr, **TextDescriptionHandle;

enum {
	dfDontDisplay = 1<<0,			// Don't display the text
	dfDontAutoScale = 1<<1,			// Don't scale text as track bounds grows or shrinks
	dfClipToTextBox = 1<<2,			// Clip update to the textbox
	dfUseMovieBGColor = 1<<3,		// Set text background to movie's background color
	dfShrinkTextBoxToFit = 1<<4,	// Compute minimum box to fit the sample
	dfScrollIn = 1<<5,				// Scroll text in until last of text is in view 
	dfScrollOut = 1<<6,				// Scroll text out until last of text is gone (if both set, scroll in then out)
	dfHorizScroll = 1<<7,			// Scroll text horizontally (otherwise it's vertical)
	dfReverseScroll = 1<<8			// vert: scroll down rather than up; horiz: scroll backwards (justfication dependent)
	};


/* progress messages */

enum {
	movieProgressOpen = 0,
	movieProgressUpdatePercent = 1,
	movieProgressClose = 2
};

/* progress operations */
enum {
	progressOpFlatten = 1,
	progressOpInsertTrackSegment,
	progressOpInsertMovieSegment,
	progressOpPaste,
	progressOpAddMovieSelection,
	progressOpCopy,
	progressOpCut,
	progressOpLoadMovieIntoRam,
	progressOpLoadTrackIntoRam,
	progressOpLoadMediaIntoRam,
	progressOpImportMovie,
	progressOpExportMovie
};

enum {
	mediaQualityDraft = 0x0000,
	mediaQualityNormal = 0x0040,
	mediaQualityBetter = 0x0080,
	mediaQualityBest = 0x00C0
};

typedef pascal OSErr (*MovieRgnCoverProc)(Movie theMovie, RgnHandle changedRgn, long refcon);		
typedef pascal OSErr (*MovieProgressProcPtr)(Movie theMovie, short message, short whatOperation, Fixed percentDone, long refcon);		


typedef ComponentInstance MediaHandler,DataHandler;
typedef Component MediaHandlerComponent,DataHandlerComponent;
typedef ComponentResult HandlerError;

#ifndef kSmallestArray
	#define kSmallestArray	1
#endif

/* TimeBase equates */

typedef long TimeValue;
typedef long TimeScale;

#ifndef I64
#define I64
typedef struct
	{
	long hi;
	long lo;
	} Int64;
#endif I64


typedef Int64 CompTimeValue;

enum {
	loopTimeBase = 1,
	palindromeLoopTimeBase = 2
};
typedef unsigned long TimeBaseFlags;

	struct TimeBaseRecord {
	 long data[1];
	};
	
	typedef struct TimeBaseRecord TimeBaseRecord;
	typedef TimeBaseRecord *TimeBase;
	
	struct CallBackRecord {
	 long data[1];
	};
	
	typedef struct CallBackRecord CallBackRecord;
	typedef CallBackRecord *QTCallBack;

typedef struct TimeRecord
	{
	CompTimeValue value;	/* units */
	TimeScale scale;		/* units per second */
	TimeBase base;
	} TimeRecord;

/* CallBack equates */

 enum
	{
	triggerTimeFwd		= 0x0001,	/* when curTime exceeds triggerTime going forward */
	triggerTimeBwd		= 0x0002,	/* when curTime exceeds triggerTime going backwards */
	triggerTimeEither	= 0x0003,	/* when curTime exceeds triggerTime going either direction */
	triggerRateLT		= 0x0004,	/* when rate changes to less than trigger value */
	triggerRateGT		= 0x0008,	/* when rate changes to greater than trigger value */
	triggerRateEqual	= 0x0010,	/* when rate changes to equal trigger value */
	triggerRateLTE		= triggerRateLT | triggerRateEqual,
	triggerRateGTE		= triggerRateGT | triggerRateEqual,
	triggerRateNotEqual	= triggerRateGT | triggerRateEqual | triggerRateLT,
	triggerRateChange	= 0,
	triggerAtStart		= 0x0001,
	triggerAtStop		= 0x0002
	};
typedef unsigned short QTCallBackFlags;

enum
	{
	timeBaseBeforeStartTime = 1,
	timeBaseAfterStopTime = 2
	};
typedef unsigned long TimeBaseStatus;

enum
	{
	callBackAtTime = 1,
	callBackAtRate = 2,
	callBackAtTimeJump = 3,
	callBackAtExtremes = 4,
	callBackAtInterrupt = 0x8000
	};
typedef unsigned short QTCallBackType;

typedef pascal void (*QTCallBackProc)(QTCallBack cb, long refCon);

enum {
	qtcbNeedsRateChanges = 1,		/* wants to know about rate changes */
	qtcbNeedsTimeChanges = 2,		/* wants to know about time changes */
	qtcbNeedsStartStopChanges = 4	// wants to know when TimeBase start/stop is changed
};

	typedef struct QTCallBackHeader {
		long					callBackFlags;
		long					reserved1;
		char					qtPrivate[40];
	} QTCallBackHeader;


enum {
	keepInRam = 1<<0,				// load and make non-purgable
	unkeepInRam = 1<<1,				// mark as purgable
	flushFromRam = 1<<2,			// empty those handles
	loadForwardTrackEdits = 1<<3,	//	load track edits into ram for playing forward
	loadBackwardTrackEdits = 1<<4	//	load track edits into ram for playing in reverse
};

typedef pascal Boolean (*MoviePreviewCallOutProc)(long refcon);		

enum {
	newMovieActive = 1<<0,
	newMovieDontResolveDataRefs = 1<<1,
	newMovieDontAskUnresolvedDataRefs = 1<<2,
	newMovieDontAutoAlternates = 1<<3
	};
	
enum {						/* track usage bits */
	trackUsageInMovie = 1<<1,
	trackUsageInPreview = 1<<2,
	trackUsageInPoster = 1<<3
	};

enum {			/* Add/GetMediaSample flags */
	mediaSampleNotSync = 1<<0,		/* sample is not a sync sample (eg. is frame differenced */
	mediaSampleShadowSync = 1<<1	/* sample is a shadow sync */
	};

enum {
	pasteInParallel = 1
};

enum {
	nextTimeMediaSample = 1<<0,
	nextTimeMediaEdit = 1<<1,
	nextTimeTrackEdit = 1<<2,
	nextTimeSyncSample = 1<<3,
	nextTimeEdgeOK = 1<<14,
	nextTimeIgnoreActiveSegment = 1<<15};
typedef unsigned short nextTimeFlagsEnum;

enum {
	createMovieFileDeleteCurFile = 1L<<31,
	createMovieFileDontCreateMovie = 1L<<30,
	createMovieFileDontOpenFile = 1L<<29
};
typedef unsigned long createMovieFileFlagsEnum;

enum {
	flattenAddMovieToDataFork = 1L<<0,
	flattenActiveTracksOnly = 1L<<2,
	flattenDontInterleaveFlatten = 1L<<3
};
typedef unsigned long movieFlattenFlagsEnum;

enum {						
	movieInDataForkResID = -1		/* magic res ID */
	};

enum {
	mcTopLeftMovie = 1<<0,		/* usually centered */
	mcScaleMovieToFit = 1<<1,	/* usually only scales down */
	mcWithBadge = 1<<2,			/* give me a badge */
	mcNotVisible = 1<<3,		/* don't show controller */
	mcWithFrame = 1<<4			/* gimme a frame */
};

enum {
	movieScrapDontZeroScrap = 1<<0,
	movieScrapOnlyPutMovie = 1<<1
};

enum {
	dataRefSelfReference = 1<<0,
	dataRefWasNotResolved = 1<<1
};
typedef unsigned long dataRefAttributesFlags;

enum {
	hintsScrubMode	= 1<<0,		/* mask == && (if flags == scrub on, flags != scrub off) */ 
	hintsUseScreenBuffer = 1<<5,
	hintsAllowInterlace = 1<<6,
	hintsUseSoundLerp = 1<<7
	} ;
typedef unsigned long playHintsEnum;

enum {
	mediaHandlerFlagGenericClient = 1
};

typedef unsigned long mediaHandlerFlagsEnum;

#ifdef __cplusplus
extern "C" {
#endif __cplusplus

/*************************
* Initialization Routines 
**************************/

pascal OSErr EnterMovies( void )
		= {0x303C,0x1,0xAAAA};
pascal void ExitMovies( void )
		= {0x303C,0x2,0xAAAA};

/*************************
* Error Routines 
**************************/

	typedef pascal void (*ErrorProcPtr)(OSErr theErr, long refcon);			


pascal OSErr GetMoviesError( void )
		= {0x303C,0x3,0xAAAA};
pascal void ClearMoviesStickyError( void )
		= {0x303C,0xDE,0xAAAA};
pascal OSErr GetMoviesStickyError( void )
		= {0x303C,0x4,0xAAAA};

pascal void SetMoviesErrorProc( ErrorProcPtr errProc, long refcon )
		= {0x303C,0xEF,0xAAAA};

/*************************
* Idle Routines 
**************************/

pascal void MoviesTask( Movie theMovie, long maxMilliSecToUse )
		= {0x303C,0x5,0xAAAA};
pascal OSErr PrerollMovie( Movie theMovie, TimeValue time, Fixed Rate )
		= {0x303C,0x6,0xAAAA};

pascal OSErr LoadMovieIntoRam( Movie theMovie, TimeValue time, TimeValue duration, long flags )
		= {0x303C,0x7,0xAAAA};
pascal OSErr LoadTrackIntoRam( Track theTrack, TimeValue time, TimeValue duration, long flags )
		= {0x303C,0x16E,0xAAAA};
pascal OSErr LoadMediaIntoRam( Media theMedia, TimeValue time, TimeValue duration, long flags )
		= {0x303C,0x8,0xAAAA};

pascal void SetMovieActive( Movie theMovie, Boolean active )
		= {0x303C,0x9,0xAAAA};
pascal Boolean GetMovieActive( Movie theMovie )
		= {0x303C,0xA,0xAAAA};

/*************************
* calls for playing movies, previews, posters
**************************/

pascal void StartMovie( Movie theMovie )
		= {0x303C,0xB,0xAAAA};
pascal void StopMovie( Movie theMovie )
		= {0x303C,0xC,0xAAAA};
pascal void GoToBeginningOfMovie( Movie theMovie )
		= {0x303C,0xD,0xAAAA};
pascal void GoToEndOfMovie( Movie theMovie )
		= {0x303C,0xE,0xAAAA};
pascal Boolean IsMovieDone( Movie theMovie )
		= {0x303C,0xDD,0xAAAA};

pascal Boolean GetMoviePreviewMode( Movie theMovie )
		= {0x303C,0xF,0xAAAA};
pascal void SetMoviePreviewMode( Movie theMovie, Boolean usePreview )
		= {0x303C,0x10,0xAAAA};
pascal void ShowMoviePoster( Movie theMovie )
		= {0x303C,0x11,0xAAAA};

pascal void PlayMoviePreview( Movie theMovie, MoviePreviewCallOutProc callOutProc, long refcon )
		= {0x303C,0xF2,0xAAAA};

/*************************
* calls for controlling movies & tracks which are playing
**************************/

pascal TimeBase GetMovieTimeBase( Movie theMovie )
		= {0x303C,0x12,0xAAAA};

pascal void SetMovieMasterTimeBase( Movie theMovie, TimeBase tb,
		const TimeRecord *slaveZero)
		= {0x303C,0x167,0xAAAA};
pascal void SetMovieMasterClock( Movie theMovie, Component clockMeister,
		const TimeRecord *slaveZero )
		= {0x303C,0x168,0xAAAA};

pascal void GetMovieGWorld( Movie theMovie, CGrafPtr *port, GDHandle *gdh )
		= {0x303C,0x15,0xAAAA};
pascal void SetMovieGWorld( Movie theMovie, CGrafPtr port, GDHandle gdh )
		= {0x303C,0x16,0xAAAA};

pascal PicHandle GetMoviePict ( Movie theMovie, TimeValue time )
		= {0x303C,0x1D,0xAAAA};
pascal PicHandle GetTrackPict ( Track theTrack, TimeValue time )
		= {0x303C,0x1E,0xAAAA};

pascal PicHandle GetMoviePosterPict ( Movie theMovie )
		= {0x303C,0xF7,0xAAAA};

pascal OSErr UpdateMovie( Movie theMovie )
		= {0x303C,0x1F,0xAAAA};	/* called between Begin & EndUpdate */


/**** spatial movie routines ****/

pascal void GetMovieBox( Movie theMovie, Rect *boxRect )
		= {0x303C,0xF9,0xAAAA};
pascal void SetMovieBox( Movie theMovie, const Rect *boxRect )
		= {0x303C,0xFA,0xAAAA};

/** movie display clip */
pascal RgnHandle GetMovieDisplayClipRgn( Movie theMovie )
		= {0x303C,0xFC,0xAAAA};
pascal void SetMovieDisplayClipRgn( Movie theMovie, RgnHandle theClip )
		= {0x303C,0xFD,0xAAAA};

/** movie src clip */
pascal RgnHandle GetMovieClipRgn( Movie theMovie )
		= {0x303C,0x100,0xAAAA};
pascal void SetMovieClipRgn( Movie theMovie, RgnHandle theClip )
		= {0x303C,0x101,0xAAAA};

/** track src clip */
pascal RgnHandle GetTrackClipRgn( Track theTrack )
		= {0x303C,0x102,0xAAAA};
pascal void SetTrackClipRgn( Track theTrack, RgnHandle theClip )
		= {0x303C,0x103,0xAAAA};

/** bounds in display space (not clipped by display clip) */
pascal RgnHandle GetMovieDisplayBoundsRgn( Movie theMovie )
		= {0x303C,0xFB,0xAAAA};
pascal RgnHandle GetTrackDisplayBoundsRgn( Track theTrack )
		= {0x303C,0x112,0xAAAA};

/** bounds in movie space */
pascal RgnHandle GetMovieBoundsRgn( Movie theMovie )
		= {0x303C,0xFE,0xAAAA};
pascal RgnHandle GetTrackMovieBoundsRgn( Track theTrack )
		= {0x303C,0xFF,0xAAAA};

/** bounds in track space */
pascal RgnHandle GetTrackBoundsRgn( Track theTrack )
		= {0x303C,0x111,0xAAAA};

/** mattes - always in track space */
pascal PixMapHandle GetTrackMatte( Track theTrack )
		= {0x303C,0x115,0xAAAA};
pascal void SetTrackMatte( Track theTrack, PixMapHandle theMatte)
		= {0x303C,0x116,0xAAAA};
pascal void DisposeMatte( PixMapHandle theMatte )
		= {0x303C,0x14A,0xAAAA};

/*************************
* calls for getting/saving movies
**************************/

pascal Movie NewMovie( long flags )
		= {0x303C,0x187,0xAAAA};

pascal OSErr PutMovieIntoHandle( Movie theMovie, Handle publicMovie )
		= {0x303C,0x22,0xAAAA};

pascal OSErr PutMovieIntoDataFork( Movie theMovie, short fRefNum, long offset, long maxSize )
		= {0x303C,0x1B4,0xAAAA};

pascal void DisposeMovie( Movie theMovie )
		= {0x303C,0x23,0xAAAA};

/*************************
* Movie State Routines
**************************/

pascal unsigned long GetMovieCreationTime( Movie theMovie )
		= {0x303C,0x26,0xAAAA};
pascal unsigned long GetMovieModificationTime( Movie theMovie )
		= {0x303C,0x27,0xAAAA};

pascal TimeScale GetMovieTimeScale( Movie theMovie )
		= {0x303C,0x29,0xAAAA};
pascal void SetMovieTimeScale( Movie theMovie, TimeScale timeScale )
		= {0x303C,0x2A,0xAAAA};

pascal TimeValue GetMovieDuration( Movie theMovie )
		= {0x303C,0x2B,0xAAAA};

pascal Fixed GetMovieRate( Movie theMovie )
		= {0x303C,0x2C,0xAAAA};
pascal void SetMovieRate( Movie theMovie, Fixed rate )
		= {0x303C,0x2D,0xAAAA};

pascal Fixed GetMoviePreferredRate( Movie theMovie )
		= {0x303C,0xF3,0xAAAA};
pascal void SetMoviePreferredRate( Movie theMovie, Fixed rate )
		= {0x303C,0xF4,0xAAAA};

pascal short GetMoviePreferredVolume( Movie theMovie )
		= {0x303C,0xF5,0xAAAA};
pascal void  SetMoviePreferredVolume( Movie theMovie, short volume )
		= {0x303C,0xF6,0xAAAA};
	
pascal short GetMovieVolume( Movie theMovie )
		= {0x303C,0x2E,0xAAAA};
pascal void  SetMovieVolume( Movie theMovie, short volume )
		= {0x303C,0x2F,0xAAAA};

pascal void GetMovieMatrix( Movie theMovie, MatrixRecord *matrix )
		= {0x303C,0x31,0xAAAA};
pascal void SetMovieMatrix( Movie theMovie, const MatrixRecord *matrix )
		= {0x303C,0x32,0xAAAA};

pascal void GetMoviePreviewTime( Movie theMovie, 
	TimeValue *previewTime, TimeValue *previewDuration )
		= {0x303C,0x33,0xAAAA};
pascal void SetMoviePreviewTime( Movie theMovie, 
	TimeValue previewTime, TimeValue previewDuration )
		= {0x303C,0x34,0xAAAA};

pascal TimeValue GetMoviePosterTime( Movie theMovie )
		= {0x303C,0x35,0xAAAA};
pascal void SetMoviePosterTime( Movie theMovie, TimeValue posterTime )
		= {0x303C,0x36,0xAAAA};

pascal void GetMovieSelection( Movie theMovie, 
	TimeValue *selectionTime, TimeValue *selectionDuration )
		= {0x303C,0x37,0xAAAA};
pascal void SetMovieSelection( Movie theMovie, 
	TimeValue selectionTime, TimeValue selectionDuration )
		= {0x303C,0x38,0xAAAA};

pascal void SetMovieActiveSegment(Movie theMovie, TimeValue startTime, TimeValue duration)
		= {0x303C,0x15C,0xAAAA};
pascal void GetMovieActiveSegment(Movie theMovie, TimeValue *startTime, TimeValue *duration)
		= {0x303C,0x15D,0xAAAA};

pascal TimeValue GetMovieTime( Movie theMovie, TimeRecord *currentTime )
		= {0x303C,0x39,0xAAAA};

pascal void SetMovieTime( Movie theMovie, const TimeRecord *newtime )
		= {0x303C,0x3C,0xAAAA};
pascal void SetMovieTimeValue( Movie theMovie, TimeValue newtime )
		= {0x303C,0x3D,0xAAAA};


pascal UserData GetMovieUserData( Movie theMovie )
		= {0x303C,0x3E,0xAAAA};


/*************************
* Track/Media finding routines
**************************/

pascal long GetMovieTrackCount( Movie theMovie )
		= {0x303C,0x3F,0xAAAA};
pascal Track GetMovieTrack( Movie theMovie, long trackID )
		= {0x303C,0x40,0xAAAA};

pascal Track GetMovieIndTrack( Movie theMovie, long index )
		= {0x303C,0x117,0xAAAA};

pascal long GetTrackID( Track theTrack )
		= {0x303C,0x127,0xAAAA};

pascal Movie GetTrackMovie( Track theTrack )
		= {0x303C,0xD0,0xAAAA};

/*************************
* Track creation routines
**************************/

pascal Track NewMovieTrack( Movie theMovie, Fixed width, Fixed height, short trackVolume)
		= {0x303C,0x188,0xAAAA};
pascal void DisposeMovieTrack( Track theTrack )
		= {0x303C,0x42,0xAAAA};

/*************************
* Track State routines
**************************/

pascal unsigned long GetTrackCreationTime( Track theTrack )
		= {0x303C,0x43,0xAAAA};
pascal unsigned long GetTrackModificationTime( Track theTrack )
		= {0x303C,0x44,0xAAAA};


pascal Boolean GetTrackEnabled( Track theTrack )
		= {0x303C,0x45,0xAAAA};
pascal void SetTrackEnabled( Track theTrack, Boolean isEnabled )
		= {0x303C,0x46,0xAAAA};

pascal long GetTrackUsage( Track theTrack )
		= {0x303C,0x47,0xAAAA};
pascal void SetTrackUsage( Track theTrack, long usage )
		= {0x303C,0x48,0xAAAA};

pascal TimeValue GetTrackDuration( Track theTrack )
		= {0x303C,0x4B,0xAAAA};

pascal TimeValue GetTrackOffset( Track theTrack )
		= {0x303C,0x4C,0xAAAA};
pascal void SetTrackOffset( Track theTrack, TimeValue movieOffsetTime )
		= {0x303C,0x4D,0xAAAA};

pascal short GetTrackLayer( Track theTrack )
		= {0x303C,0x50,0xAAAA};
pascal void SetTrackLayer( Track theTrack, short layer )
		= {0x303C,0x51,0xAAAA};

pascal Track GetTrackAlternate( Track theTrack )
		= {0x303C,0x52,0xAAAA};
pascal void SetTrackAlternate( Track theTrack, Track alternateT )
		= {0x303C,0x53,0xAAAA};

pascal void SetAutoTrackAlternatesEnabled(Movie theMovie, Boolean enable)
		= {0x303C,0x15E,0xAAAA};
pascal void SelectMovieAlternates(Movie theMovie)
		= {0x303C,0x15F,0xAAAA};

pascal short GetTrackVolume( Track theTrack )
		= {0x303C,0x54,0xAAAA};
pascal void SetTrackVolume( Track theTrack, short volume )
		= {0x303C,0x55,0xAAAA};

pascal void GetTrackMatrix( Track theTrack, MatrixRecord *matrix )
		= {0x303C,0x56,0xAAAA};
pascal void SetTrackMatrix( Track theTrack, const MatrixRecord *matrix )
		= {0x303C,0x57,0xAAAA};

pascal void GetTrackDimensions( Track theTrack, Fixed *width, Fixed *height )
		= {0x303C,0x5D,0xAAAA};
pascal void SetTrackDimensions( Track theTrack, Fixed width, Fixed height )
		= {0x303C,0x5E,0xAAAA};

pascal UserData GetTrackUserData( Track theTrack )
		= {0x303C,0x5F,0xAAAA};


/*************************
* get Media routines
**************************/

pascal Media NewTrackMedia( Track theTrack, OSType mediaType, TimeScale timeScale, 
		Handle dataRef, OSType dataRefType )
		= {0x303C,0x18E,0xAAAA};

pascal void DisposeTrackMedia( Media theMedia )
		= {0x303C,0x61,0xAAAA};

pascal Media GetTrackMedia( Track theTrack )
		= {0x303C,0x62,0xAAAA};
pascal Track GetMediaTrack( Media theMedia )
		= {0x303C,0xC5,0xAAAA};



/*************************
* Media State routines
**************************/

pascal unsigned long GetMediaCreationTime( Media theMedia )
		= {0x303C,0x66,0xAAAA};
pascal unsigned long GetMediaModificationTime( Media theMedia )
		= {0x303C,0x67,0xAAAA};

pascal TimeScale GetMediaTimeScale( Media theMedia )
		= {0x303C,0x68,0xAAAA};
pascal void SetMediaTimeScale( Media theMedia, TimeScale timeScale )
		= {0x303C,0x69,0xAAAA};

pascal TimeValue GetMediaDuration( Media theMedia )
		= {0x303C,0x6A,0xAAAA};

pascal short GetMediaLanguage( Media theMedia )
		= {0x303C,0x6B,0xAAAA};
pascal void SetMediaLanguage( Media theMedia, short language )
		= {0x303C,0x6C,0xAAAA};

pascal short GetMediaQuality( Media theMedia )
		= {0x303C,0x6D,0xAAAA};
pascal void SetMediaQuality( Media theMedia, short quality )
		= {0x303C,0x6E,0xAAAA};

pascal void GetMediaHandlerDescription( Media theMedia, OSType *mediaType, Str255 creatorName, OSType *creatorManufacturer )
		= {0x303C,0x6F,0xAAAA};

pascal UserData GetMediaUserData( Media theMedia )
		= {0x303C,0x70,0xAAAA};


/*************************
* Media Handler routines
**************************/

pascal MediaHandler GetMediaHandler( Media theMedia )
		= {0x303C,0x71,0xAAAA};

pascal OSErr SetMediaHandler( Media theMedia, MediaHandlerComponent mH )
		= {0x303C,0x190,0xAAAA};


/*************************
* Media's Data routines
**************************/

pascal OSErr BeginMediaEdits( Media theMedia )
		= {0x303C,0x72,0xAAAA};
pascal OSErr EndMediaEdits( Media theMedia )
		= {0x303C,0x73,0xAAAA};

pascal void GetMediaDataHandlerDescription( Media theMedia, short index, OSType *dhType, Str255 creatorName, OSType *creatorManufacturer )
		= {0x303C,0x19E,0xAAAA};

pascal DataHandler GetMediaDataHandler( Media theMedia, short index )
		= {0x303C,0x19F,0xAAAA};
pascal OSErr SetMediaDataHandler( Media theMedia, short index, DataHandlerComponent dataHandler )
		= {0x303C,0x1A0,0xAAAA};


/*************************
* Media Sample Table Routines
**************************/

pascal long GetMediaSampleDescriptionCount( Media theMedia )
		= {0x303C,0x77,0xAAAA};
pascal void GetMediaSampleDescription( Media theMedia, long index, SampleDescriptionHandle descH )
		= {0x303C,0x78,0xAAAA};
pascal OSErr SetMediaSampleDescription( Media theMedia, long index, SampleDescriptionHandle descH )
		= {0x303C,0x1D0,0xAAAA};

pascal long GetMediaSampleCount( Media theMedia )
		= {0x303C,0x79,0xAAAA};

pascal void SampleNumToMediaTime( Media theMedia, long logicalSampleNum, 
		TimeValue *sampleTime, TimeValue *sampleDuration )
		= {0x303C,0x7A,0xAAAA};

pascal void MediaTimeToSampleNum( Media theMedia, TimeValue time, 
		long *sampleNum, TimeValue *sampleTime, TimeValue *sampleDuration )
		= {0x303C,0x7B,0xAAAA};


pascal OSErr AddMediaSample( Media theMedia, Handle dataIn, long inOffset, unsigned long size,
	TimeValue durationPerSample,
	SampleDescriptionHandle sampleDescriptionH, 
	long numberOfSamples, short sampleFlags, TimeValue *sampleTime )
		= {0x303C,0x7C,0xAAAA};

pascal OSErr AddMediaSampleReference( Media theMedia, long dataOffset, unsigned long size,
	TimeValue durationPerSample,
	SampleDescriptionHandle sampleDescriptionH, 
	long numberOfSamples, short sampleFlags, TimeValue *sampleTime )
		= {0x303C,0x7D,0xAAAA}; 

pascal OSErr GetMediaSample( Media theMedia, Handle dataOut, long maxSizeToGrow, long *size,
	TimeValue time, TimeValue *sampleTime, TimeValue *durationPerSample,
	SampleDescriptionHandle sampleDescriptionH, long *sampleDescriptionIndex,
	long maxNumberOfSamples, long *numberOfSamples, short *sampleFlags )
		= {0x303C,0x7E,0xAAAA};	

pascal OSErr GetMediaSampleReference( Media theMedia, long *dataOffset, long *size, 
	TimeValue time, TimeValue *sampleTime, TimeValue *durationPerSample,
	SampleDescriptionHandle sampleDescriptionH, long *sampleDescriptionIndex, 
	long maxNumberOfSamples, long *numberOfSamples, short *sampleFlags )
		= {0x303C,0x7F,0xAAAA};	

pascal OSErr SetMediaShadowSync( Media theMedia, long frameDiffSampleNum, long syncSampleNum )
		= {0x303C,0x121,0xAAAA};	
pascal OSErr GetMediaShadowSync( Media theMedia, long frameDiffSampleNum, long *syncSampleNum )
		= {0x303C,0x122,0xAAAA};	





/*************************
* Editing Routines
**************************/

pascal OSErr InsertMediaIntoTrack( Track theTrack,
			TimeValue trackStart, 
			TimeValue mediaTime, TimeValue mediaDuration, 
			Fixed mediaRate )
		= {0x303C,0x183,0xAAAA};

pascal OSErr InsertTrackSegment( Track srcTrack, Track dstTrack,
			TimeValue srcIn, TimeValue srcDuration, TimeValue dstIn )
		= {0x303C,0x85,0xAAAA};
pascal OSErr InsertMovieSegment( Movie srcMovie, Movie dstMovie,
			TimeValue srcIn, TimeValue srcDuration, TimeValue dstIn )
		= {0x303C,0x86,0xAAAA};
pascal OSErr InsertEmptyTrackSegment( Track dstTrack,
			TimeValue dstIn, TimeValue dstDuration )
		= {0x303C,0x87,0xAAAA};
pascal OSErr InsertEmptyMovieSegment( Movie dstMovie,
			TimeValue dstIn, TimeValue dstDuration )
		= {0x303C,0x88,0xAAAA};
pascal OSErr DeleteTrackSegment( Track theTrack, TimeValue in, TimeValue duration )
		= {0x303C,0x89,0xAAAA};
pascal OSErr DeleteMovieSegment( Movie theMovie, TimeValue in, TimeValue duration )
		= {0x303C,0x8A,0xAAAA};
pascal OSErr ScaleTrackSegment( Track theTrack, TimeValue in, 
			TimeValue oldDuration, TimeValue newDuration )
		= {0x303C,0x8B,0xAAAA};
pascal OSErr ScaleMovieSegment( Movie theMovie, TimeValue in,  
			TimeValue oldDuration, TimeValue newDuration )
		= {0x303C,0x8C,0xAAAA};


/*************************
* Hi-level Editing Routines
**************************/

pascal Movie CutMovieSelection( Movie theMovie )
		= {0x303C,0x8D,0xAAAA};
pascal Movie CopyMovieSelection( Movie theMovie )
		= {0x303C,0x8E,0xAAAA};
pascal void PasteMovieSelection( Movie theMovie, Movie src )
		= {0x303C,0x8F,0xAAAA};
pascal void AddMovieSelection( Movie theMovie, Movie src )
		= {0x303C,0x152,0xAAAA};
pascal void ClearMovieSelection( Movie theMovie )
		= {0x303C,0xE1,0xAAAA};
pascal OSErr PasteHandleIntoMovie(Handle h, OSType handleType, Movie theMovie, long flags, ComponentInstance userComp)
		= {0x303C,0xCB,0xAAAA};
pascal OSErr PutMovieIntoTypedHandle(Movie theMovie, Track targetTrack, OSType handleType, Handle publicMovie,
				TimeValue start, TimeValue dur, long flags, ComponentInstance userComp)
		= {0x303C,0x1CD,0xAAAA};
pascal Component IsScrapMovie(Track targetTrack)
		= {0x303C,0xCC,0xAAAA};

/*************************
* Middle-level Editing Routines
**************************/

pascal OSErr CopyTrackSettings(Track srcTrack, Track dstTrack)
		= {0x303C,0x153,0xAAAA};
pascal OSErr CopyMovieSettings(Movie srcMovie, Movie dstMovie)
		= {0x303C,0x154,0xAAAA};

/*************************
* movie & track edit state routines
**************************/
pascal MovieEditState NewMovieEditState(Movie theMovie)
		= {0x303C,0x104,0xAAAA};
pascal OSErr UseMovieEditState(Movie theMovie, MovieEditState toState)
		= {0x303C,0x105,0xAAAA};
pascal OSErr DisposeMovieEditState(MovieEditState state)
		= {0x303C,0x106,0xAAAA};

pascal TrackEditState NewTrackEditState(Track theTrack)
		= {0x303C,0x107,0xAAAA};
pascal OSErr UseTrackEditState(Track theTrack, TrackEditState state)
		= {0x303C,0x108,0xAAAA};
pascal OSErr DisposeTrackEditState(TrackEditState state)
		= {0x303C,0x109,0xAAAA};

/*************************
* high level file conversion routines
**************************/
pascal OSErr ConvertFileToMovieFile(const FSSpec *inputFile, const FSSpec *outputFile,
		OSType creator, ScriptCode scriptTag, short *resID, long flags, ComponentInstance userComp,
		MovieProgressProcPtr proc, long refCon)
		= {0x303C,0x1CB,0xAAAA};
pascal OSErr ConvertMovieToFile(Movie theMovie, Track onlyTrack, const FSSpec *outputFile,
		OSType fileType, OSType creator, ScriptCode scriptTag, short *resID, long flags,
		ComponentInstance userComp)
		= {0x303C,0x1CC,0xAAAA};

/*************************
* Movie Timebase Conversion Routines
**************************/

pascal TimeValue TrackTimeToMediaTime( TimeValue value, Track theTrack )
		= {0x303C,0x96,0xAAAA};
pascal Fixed GetTrackEditRate(Track theTrack, TimeValue atTime)
		= {0x303C,0x123,0xAAAA};


/*************************
* Miscellaneous Routines
**************************/


pascal long GetMovieDataSize( Movie theMovie, TimeValue startTime, TimeValue duration )
		= {0x303C,0x98,0xAAAA};
pascal long GetTrackDataSize( Track theTrack, TimeValue startTime, TimeValue duration )
		= {0x303C,0x149,0xAAAA};
pascal long GetMediaDataSize( Media theMedia, TimeValue startTime, TimeValue duration)
		= {0x303C,0x99,0xAAAA};

pascal Boolean PtInMovie( Movie theMovie, Point pt )
		= {0x303C,0x9A,0xAAAA};
pascal Boolean PtInTrack( Track theTrack, Point pt )
		= {0x303C,0x9B,0xAAAA};


/*************************
* Group Selection Routines
**************************/


pascal void SetMovieLanguage( Movie theMovie, long language )
		= {0x303C,0x9C,0xAAAA};





/*************************
* User Data
**************************/


pascal OSErr GetUserData( UserData theUserData, Handle data, OSType udType, long index )
		= {0x303C,0x9E,0xAAAA};
pascal OSErr AddUserData( UserData theUserData, Handle data, OSType udType )
		= {0x303C,0x9F,0xAAAA};
pascal OSErr RemoveUserData( UserData theUserData, OSType udType, long index )
		= {0x303C,0xA0,0xAAAA};
pascal short CountUserDataType(UserData theUserData, OSType udType)
		= {0x303C,0x14B,0xAAAA};
pascal long GetNextUserDataType(UserData theUserData, OSType udType)
		= {0x303C,0x1A5,0xAAAA};
pascal OSErr GetUserDataItem(UserData theUserData, void *data, long size, OSType udType, long index )
		= {0x303C,0x126,0xAAAA};
pascal OSErr SetUserDataItem(UserData theUserData, void *data, long size, OSType udType, long index )
		= {0x303C,0x12E,0xAAAA};

pascal OSErr AddUserDataText(UserData theUserData, Handle data, OSType udType, long index,
				short itlRegionTag)
		= {0x303C,0x14C,0xAAAA};
pascal OSErr GetUserDataText(UserData theUserData, Handle data, OSType udType, long index,
				short itlRegionTag)
		= {0x303C,0x14D,0xAAAA};
pascal OSErr RemoveUserDataText(UserData theUserData, OSType udType, long index,
				short itlRegionTag)
		= {0x303C,0x14E,0xAAAA};

pascal OSErr NewUserData(UserData *theUserData)
		= {0x303C,0x12F,0xAAAA};
pascal OSErr DisposeUserData(UserData theUserData)
		= {0x303C,0x130,0xAAAA};
pascal OSErr NewUserDataFromHandle(Handle h, UserData *theUserData)
		= {0x303C,0x131,0xAAAA};
pascal OSErr PutUserDataIntoHandle(UserData theUserData, Handle h)
		= {0x303C,0x132,0xAAAA};

pascal void GetMediaNextInterestingTime( Media theMedia, short interestingTimeFlags, TimeValue time, Fixed rate,
		TimeValue *interestingTime, TimeValue *interestingDuration )
		= {0x303C,0x16D,0xAAAA};
pascal void GetTrackNextInterestingTime( Track theTrack, short interestingTimeFlags, TimeValue time, Fixed rate,
		TimeValue *interestingTime, TimeValue *interestingDuration )
		= {0x303C,0xE2,0xAAAA};
pascal void GetMovieNextInterestingTime( Movie theMovie, short interestingTimeFlags, 
		short numMediaTypes, const OSType *whichMediaTypes,
		TimeValue time, Fixed rate,
		TimeValue *interestingTime, TimeValue *interestingDuration )
		= {0x303C,0x10E,0xAAAA};


pascal OSErr CreateMovieFile( const FSSpec *fileSpec, OSType creator,
			ScriptCode scriptTag, long createMovieFileFlags, short *resRefNum, Movie *newmovie  )
		= {0x303C,0x191,0xAAAA};

pascal OSErr OpenMovieFile( const FSSpec *fileSpec, short *resRefNum, char perms )
		= {0x303C,0x192,0xAAAA};

pascal OSErr CloseMovieFile( short resRefNum )
		= {0x303C,0xD5,0xAAAA};

pascal OSErr DeleteMovieFile( const FSSpec *fileSpec )
		= {0x303C,0x175,0xAAAA};

pascal OSErr NewMovieFromFile( Movie *theMovie, short resRefNum, short *resId, StringPtr resName,
		 	short newMovieFlags, Boolean *dataRefWasChanged )
		= {0x303C,0xF0,0xAAAA};

pascal OSErr NewMovieFromHandle( Movie *theMovie, Handle h,
		 	short newMovieFlags, Boolean *dataRefWasChanged )
		= {0x303C,0xF1,0xAAAA};

pascal OSErr NewMovieFromDataFork( Movie *theMovie, short fRefNum, long fileOffset,
		 	short newMovieFlags, Boolean *dataRefWasChanged )
		= {0x303C,0x1B3,0xAAAA};

pascal OSErr AddMovieResource( Movie theMovie, short resRefNum, short *resId, const StringPtr resName )
		= {0x303C,0xD7,0xAAAA};

pascal OSErr UpdateMovieResource( Movie theMovie, short resRefNum, short resId, const StringPtr resName )
		= {0x303C,0xD8,0xAAAA};

pascal OSErr RemoveMovieResource( short resRefNum, short resId )
		= {0x303C,0x176,0xAAAA};

pascal Boolean HasMovieChanged( Movie theMovie )
		= {0x303C,0xD9,0xAAAA};
pascal void ClearMovieChanged( Movie theMovie )
		= {0x303C,0x113,0xAAAA};

pascal OSErr SetMovieDefaultDataRef(Movie theMovie, Handle dataRef, OSType dataRefType )
		= {0x303C,0x1C1,0xAAAA};
pascal OSErr GetMovieDefaultDataRef(Movie theMovie, Handle *dataRef, OSType *dataRefType)
		= {0x303C,0x1D2,0xAAAA};

pascal void FlattenMovie(Movie theMovie, long movieFlattenFlags, 
			const FSSpec *theFile, OSType creator, ScriptCode scriptTag,
			long createMovieFileFlags, short *resId, const StringPtr resName)
		= {0x303C,0x19B,0xAAAA};

pascal Movie FlattenMovieData(Movie theMovie, long movieFlattenFlags, 
			const FSSpec *theFile, OSType creator, ScriptCode scriptTag,
			long createMovieFileFlags)
		= {0x303C,0x19C,0xAAAA};

pascal void SetMovieProgressProc(Movie theMovie, MovieProgressProcPtr p, long refcon)
		= {0x303C,0x19A,0xAAAA};

/*************************
* Video Media routines
**************************/
pascal HandlerError GetVideoMediaGraphicsMode( MediaHandler mh,
						long *graphicsMode, RGBColor *opColor )
								= {0x2F3C,0x8,0x101,0x7000,0xA82A};
pascal HandlerError SetVideoMediaGraphicsMode( MediaHandler mh,
						long graphicsMode, const RGBColor *opColor )
								= {0x2F3C,0x8,0x102,0x7000,0xA82A};

/*************************
* Sound Media routines
**************************/

pascal HandlerError GetSoundMediaBalance( MediaHandler mh,
						short *balance )
								= {0x2F3C,0x4,0x101,0x7000,0xA82A};
pascal HandlerError SetSoundMediaBalance( MediaHandler mh,
						 short balance )
								= {0x2F3C,0x2,0x102,0x7000,0xA82A};


/*************************
* Text Media routines
**************************/

/* Return displayFlags for TextProc */
enum {
	txtProcDefaultDisplay = 0,	//	Use the media's default
	txtProcDontDisplay = 1,		//	Don't display the text
	txtProcDoDisplay = 2		//	Do display the text
	};

typedef pascal OSErr (*TextMediaProcPtr)(Handle theText, Movie theMovie, short *displayFlag, long refcon);		
	
pascal ComponentResult SetTextProc(MediaHandler mh, TextMediaProcPtr TextProc, long refcon)
								= {0x2F3C,0x8,0x101,0x7000,0xA82A};

pascal ComponentResult AddTextSample(MediaHandler mh, Ptr text, unsigned long size, 
	short fontNumber, short fontSize, Style textFace, RGBColor *textColor,
	RGBColor *backColor, short textJustification, Rect *textBox, long displayFlags, 
	TimeValue scrollDelay, short hiliteStart, short hiliteEnd, RGBColor *rgbHiliteColor, 
	TimeValue duration, TimeValue *sampleTime)
								= {0x2F3C,0x34,0x102,0x7000,0xA82A};

pascal ComponentResult AddTESample(MediaHandler mh, TEHandle hTE, RGBColor *backColor, 
	short textJustification, Rect *textBox, long displayFlags, TimeValue scrollDelay,
	short hiliteStart, short hiliteEnd, RGBColor *rgbHiliteColor, TimeValue duration, 
	TimeValue *sampleTime)
									= {0x2F3C,0x26,0x103,0x7000,0xA82A};

pascal ComponentResult AddHiliteSample(MediaHandler mh, short hiliteStart, short hiliteEnd, 
	RGBColor *rgbHiliteColor, TimeValue duration, TimeValue *sampleTime)
									= {0x2F3C,0x10,0x104,0x7000,0xA82A};

enum {
	findTextEdgeOK = 1<<0,			// Okay to find text at specified sample time
	findTextCaseSensitive = 1<<1,	// Case sensitive search
	findTextReverseSearch = 1<<2,	// Search from sampleTime backwards
	findTextWrapAround = 1<<3		// Wrap search when beginning or end of movie is hit
	};

pascal ComponentResult FindNextText(MediaHandler mh, Ptr text, long size, short findFlags, 
	TimeValue startTime, TimeValue *foundTime, TimeValue *foundDuration, long *offset)
									= {0x2F3C,0x1A,0x105,0x7000,0xA82A};

pascal ComponentResult HiliteTextSample(MediaHandler mh, TimeValue sampleTime, short hiliteStart, 
	short hiliteEnd, RGBColor *rgbHiliteColor)
									= {0x2F3C,0xC,0x106,0x7000,0xA82A};


pascal void GetPosterBox( Movie theMovie, Rect *boxRect )
		= {0x303C,0x16F,0xAAAA};
pascal void SetPosterBox( Movie theMovie, const Rect *boxRect )
		= {0x303C,0x170,0xAAAA};
pascal RgnHandle GetMovieSegmentDisplayBoundsRgn( Movie theMovie, TimeValue time, TimeValue duration )
		= {0x303C,0x16C,0xAAAA};
pascal RgnHandle GetTrackSegmentDisplayBoundsRgn( Track theTrack, TimeValue time, TimeValue duration )
		= {0x303C,0x16B,0xAAAA};

pascal void SetMovieCoverProcs(Movie theMovie, MovieRgnCoverProc uncoverProc, MovieRgnCoverProc coverProc, long refcon)
		= {0x303C,0x179,0xAAAA};

pascal ComponentResult GetTrackStatus(Track theTrack)
		= {0x303C,0x172,0xAAAA};
pascal ComponentResult GetMovieStatus(Movie theMovie, Track *firstProblemTrack)
		= {0x303C,0x173,0xAAAA};

/****
	Movie Controller support routines
****/

pascal ComponentInstance NewMovieController(Movie theMovie, const Rect *movieRect, long someFlags)
		= {0x303C,0x18A,0xAAAA};
pascal void DisposeMovieController(ComponentInstance mc)
		= {0x303C,0x18B,0xAAAA};

/*****
	Scrap routines
*****/

pascal OSErr PutMovieOnScrap(Movie theMovie, long movieScrapFlags)
		= {0x303C,0x18C,0xAAAA};
pascal Movie NewMovieFromScrap(long newMovieFlags)
		= {0x303C,0x18D,0xAAAA};


/*****
	DataRef routines
*****/


pascal OSErr GetMediaDataRef( Media theMedia, short index, Handle *dataRef, OSType *dataRefType, long *dataRefAttributes )
		= {0x303C,0x197,0xAAAA};
pascal OSErr SetMediaDataRef( Media theMedia, short index, Handle dataRef, OSType dataRefType)
		= {0x303C,0x1C9,0xAAAA};
pascal OSErr SetMediaDataRefAttributes( Media theMedia, short index, long dataRefAttributes)
		= {0x303C,0x1CA,0xAAAA};
pascal OSErr AddMediaDataRef( Media theMedia, short *index, Handle dataRef, OSType dataRefType )
		= {0x303C,0x198,0xAAAA};

pascal OSErr GetMediaDataRefCount( Media theMedia, short *count )
		= {0x303C,0x199,0xAAAA};

/*****
	Playback hint routines
*****/

pascal void SetMoviePlayHints( Movie theMovie, long flags, long flagsMask )
		= {0x303C,0x1A1,0xAAAA};
pascal void SetMediaPlayHints( Media theMedia, long flags, long flagsMask )
		= {0x303C,0x1A2,0xAAAA};


#ifdef __cplusplus
}
#endif __cplusplus


enum {
	firstMoviesError = -2000,

	couldNotResolveDataRef = -2000,
	badImageDescription = -2001,
	badPublicMovieAtom = -2002,
	cantFindHandler = -2003,
	cantOpenHandler = -2004,
	badComponentType = -2005,
	noMediaHandler = -2006,
	noDataHandler = -2007,
	invalidMedia = -2008,
	invalidTrack = -2009,
	invalidMovie = -2010,
	invalidSampleTable = -2011,
	invalidDataRef = -2012,
	invalidHandler = -2013,
	invalidDuration = -2014,
	invalidTime = -2015,
	cantPutPublicMovieAtom = -2016,
	badEditList = -2017,
	mediaTypesDontMatch = -2018,
	progressProcAborted = -2019,
	movieToolboxUninitialized = -2020,
	wfFileNotFound = -2021,
	cantCreateSingleForkFile = -2022,			/* happens when file already exists */
	invalidEditState = -2023,
	nonMatchingEditState = -2024,
	staleEditState = -2025,
	userDataItemNotFound = -2026,
	maxSizeToGrowTooSmall = -2027,
	badTrackIndex = -2028,
	trackIDNotFound = -2029,
	trackNotInMovie = -2030,
	timeNotInTrack = -2031,
	timeNotInMedia = -2032,
	badEditIndex = -2033,
	internalQuickTimeError = -2034,
	cantEnableTrack = -2035,
	invalidRect = -2036,
	invalidSampleNum = -2037,
	invalidChunkNum = -2038,
	invalidSampleDescIndex = -2039,
	invalidChunkCache = -2040,
	invalidSampleDescription = -2041,
	
/* this should probably be in its own range for data handlers */
	dataNotOpenForRead = -2042,	
	dataNotOpenForWrite = -2043,	
	dataAlreadyOpenForWrite = -2044,
	dataAlreadyClosed = -2045,
	endOfDataReached = -2046,
	dataNoDataRef = -2047,

/* private errors */
	noMovieFound = -2048,				
	
	invalidDataRefContainer = -2049,
	badDataRefIndex = -2050,
	noDefaultDataRef = -2051,

	couldNotUseAnExistingSample = -2052,
	
	featureUnsupported = -2053,
	unsupportedAuxiliaryImportData = -2057,
	lastMoviesError,
	noRecordOfApp = movieToolboxUninitialized			/* replica */
	};




#define MovieControllerComponentType 'play'

typedef ComponentInstance MovieController;

enum {
	mcActionIdle = 1,						// no param
	mcActionDraw = 2,						// param is WindowPtr
	mcActionActivate = 3,					// no param
	mcActionDeactivate = 4,					// no param
	mcActionMouseDown = 5,					// param is pointer to EventRecord
	mcActionKey = 6,						// param is pointer to EventRecord
	mcActionPlay = 8,						// param is Fixed, play rate
	mcActionGoToTime = 12,					// param is TimeRecord
	mcActionSetVolume = 14,					// param is a short
	mcActionGetVolume = 15,					// param is pointer to a short
	mcActionStep = 18,						// param is number of steps (short)
	mcActionSetLooping = 21,				// param is Boolean
	mcActionGetLooping = 22,				// param is pointer to a Boolean
	mcActionSetLoopIsPalindrome = 23,		// param is Boolean
	mcActionGetLoopIsPalindrome = 24,		// param is pointer to a Boolean
	mcActionSetGrowBoxBounds = 25,			// param is a Rect
	mcActionControllerSizeChanged = 26,		// no param
	mcActionSetSelectionBegin = 29,			// param is TimeRecord
	mcActionSetSelectionDuration = 30,		// param is TimeRecord, action only taken on set-duration
	mcActionSetPosterTime = 31,				// param is TimeRecord
	mcActionSetKeysEnabled = 32,			// param is Boolean
	mcActionGetKeysEnabled = 33,			// param is pointer to Boolean
	mcActionSetPlaySelection = 34,			// param is Boolean
	mcActionGetPlaySelection = 35,			// param is pointer to Boolean
	mcActionSetUseBadge = 36,				// param is Boolean
	mcActionGetUseBadge = 37,				// param is pointer to Boolean
	mcActionSetFlags = 38,					// param is long of flags
	mcActionGetFlags = 39,					// param is pointer to a long of flags
	mcActionSetPlayEveryFrame = 40,			// param is Boolean
	mcActionGetPlayEveryFrame = 41,			// param is pointer to Boolean
	mcActionGetPlayRate = 42,				// param is pointer to Fixed
	mcActionShowBalloon = 43,				// param is a pointer to a boolean. set to false to stop balloon
	mcActionBadgeClick = 44,				// param is pointer to Boolean. set to false to ignore click
	mcActionMovieClick = 45,				// param is pointer to event record. change ÒwhatÓ to nullEvt to kill click
	mcActionSuspend = 46,					// no param
	mcActionResume = 47						// no param
};
typedef short mcAction;

enum
	{
	mcFlagSuppressMovieFrame = 1<<0,
	mcFlagSuppressStepButtons = 1<<1,
	mcFlagSuppressSpeakerButton = 1<<2,
	mcFlagsUseWindowPalette = 1<<3
};


enum {
	mcPositionDontInvalidate = 1<<5
};

typedef unsigned long mcFlags;
typedef pascal Boolean (*MCActionFilter)(MovieController mc, short *action, void *params);
typedef pascal Boolean (*MCActionFilterWithRefCon)(MovieController mc, short action, void *params, long refCon);

/*
	menu related stuff
*/
enum {
	mcInfoUndoAvailable = 1<<0,
	mcInfoCutAvailable = 1<<1,
	mcInfoCopyAvailable = 1<<2,
	mcInfoPasteAvailable = 1<<3,
	mcInfoClearAvailable = 1<<4,
	mcInfoHasSound = 1<<5,
	mcInfoIsPlaying = 1<<6,
	mcInfoIsLooping = 1<<7,
	mcInfoIsInPalindrome = 1<<8,
	mcInfoEditingEnabled = 1<<9
};

// menu item codes
enum {
	mcMenuUndo = 1,
	mcMenuCut = 3,
	mcMenuCopy = 4,
	mcMenuPaste = 5,
	mcMenuClear = 6
};

/**** error codes ******/
enum {
	cannotMoveAttachedController = -9999,
	controllerHasFixedHeight = -9998,
	cannotSetWidthOfAttachedController = -9997,
	controllerBoundsNotExact = -9996,
	editingNotAllowed = -9995,
	badControllerHeight = -9994
};


#ifdef __cplusplus
extern "C" {
#endif __cplusplus
/* target management */
pascal ComponentResult MCSetMovie (MovieController mc, Movie m, WindowPtr movieWindow, Point where)  = {0x2F3C,0xC,0x2,0x7000,0xA82A};

pascal Movie MCGetMovie(MovieController mc)   = {0x4267,0x2F3C,0x2,0x5,0x7000,0xA82A};

pascal ComponentResult MCRemoveMovie (MovieController mc) = {0x2F3C,0,0x6,0x7000,0xA82A};

/* event handling etc. */
pascal ComponentResult MCIsPlayerEvent (MovieController mc, const EventRecord *e)  = {0x2F3C,0x4,0x7,0x7000,0xA82A};

/* obsolete. use MCSetActionFilterWithRefCon instead. */
pascal ComponentResult MCSetActionFilter (MovieController mc, MCActionFilter blob)  = {0x2F3C,0x4,0x8,0x7000,0xA82A};

/*
	proc is of the form:
		Boolean userPlayerFilter(MovieController mc, short *action, void *params) =
	proc returns TRUE if it handles the action, FALSE if not
	action is passed as a VAR so that it could be changed by filter (ick)
	this is consistent with the current dialog manager stuff
	params is any potential parameters that go with the action <triple ick> 
		such as set playback rate to xxx.
*/
pascal ComponentResult MCDoAction (MovieController mc, short action, void *params)  = {0x2F3C,0x6,0x9,0x7000,0xA82A};

/* state type things */
pascal ComponentResult MCSetControllerAttached (MovieController mc, Boolean attach)  = {0x2F3C,0x2,0xA,0x7000,0xA82A};

pascal ComponentResult MCIsControllerAttached (MovieController mc) = {0x2F3C,0,0xB,0x7000,0xA82A};

pascal ComponentResult MCSetControllerPort (MovieController mc, CGrafPtr gp)  = {0x2F3C,0x4,0xC,0x7000,0xA82A};

pascal CGrafPtr MCGetControllerPort (MovieController mc)  = {0x2F3C,0,0xD,0x7000,0xA82A};

pascal ComponentResult MCSetVisible (MovieController mc, Boolean visible)  = {0x2F3C,0x2,0xE,0x7000,0xA82A};

pascal ComponentResult MCGetVisible (MovieController mc)  = {0x2F3C,0,0xF,0x7000,0xA82A};

pascal ComponentResult MCGetControllerBoundsRect (MovieController mc, Rect *bounds)  = {0x2F3C,0x4,0x10,0x7000,0xA82A};

pascal ComponentResult MCSetControllerBoundsRect (MovieController mc, const Rect *bounds)  = {0x2F3C,0x4,0x11,0x7000,0xA82A};

pascal RgnHandle MCGetControllerBoundsRgn (MovieController mc)  = {0x2F3C,0,0x12,0x7000,0xA82A};

pascal RgnHandle MCGetWindowRgn (MovieController mc, WindowPtr w)  = {0x2F3C,0x4,0x13,0x7000,0xA82A};


/* other stuff */
pascal ComponentResult MCMovieChanged (MovieController mc, Movie m)  = {0x2F3C,0x4,0x14,0x7000,0xA82A};
				

/*
	called when the app has changed thing about the movie (like bounding rect) or rate. So that we
		can update our graphical (and internal) state accordingly.
*/
pascal ComponentResult MCSetDuration (MovieController mc, TimeValue duration)  = {0x2F3C,0x4,0x15,0x7000,0xA82A};

/*
	duration to use for time slider -- will be reset next time MCMovieChanged is called
		or MCSetMovie is called
*/
pascal TimeValue MCGetCurrentTime (MovieController mc, TimeScale *scale)  = {0x2F3C,0x4,0x16,0x7000,0xA82A};

/*
	returns the time value and the time scale it is on. if there are no movies, the
		time scale is passed back as 0. scale is an optional parameter

*/
pascal ComponentResult MCNewAttachedController (MovieController mc, Movie m, WindowPtr w, Point where)  = {0x2F3C,0xC,0x17,0x7000,0xA82A};

/*
	makes m the only movie attached to the controller. makes the controller visible.
	the window and where parameters are passed a long to MCSetMovie and behave as
	described there
*/

pascal ComponentResult MCDraw (MovieController mc, WindowPtr w)  = {0x2F3C,0x4,0x18,0x7000,0xA82A};

pascal ComponentResult MCActivate (MovieController mc, WindowPtr w, Boolean activate)  = {0x2F3C,0x6,0x19,0x7000,0xA82A};

pascal ComponentResult MCIdle (MovieController mc)  = {0x2F3C,0,0x1A,0x7000,0xA82A};

pascal ComponentResult MCKey (MovieController mc, char key, long modifiers)  = {0x2F3C,0x6,0x1B,0x7000,0xA82A};

pascal ComponentResult MCClick (MovieController mc, WindowPtr w, Point where, long when, long modifiers)  = {0x2F3C,0x10,0x1C,0x7000,0xA82A};


/*
	calls for editing
*/
pascal ComponentResult MCEnableEditing (MovieController mc, Boolean enabled)  = {0x2F3C,0x2,0x1D,0x7000,0xA82A};

pascal long MCIsEditingEnabled (MovieController mc)  = {0x2F3C,0,0x1E,0x7000,0xA82A};

pascal Movie MCCopy (MovieController mc)  = {0x2F3C,0,0x1F,0x7000,0xA82A};

pascal Movie MCCut (MovieController mc)  = {0x2F3C,0,0x20,0x7000,0xA82A};

pascal ComponentResult MCPaste (MovieController mc, Movie srcMovie)  = {0x2F3C,0x4,0x21,0x7000,0xA82A};

pascal ComponentResult MCClear (MovieController mc)  = {0x2F3C,0,0x22,0x7000,0xA82A};

pascal ComponentResult MCUndo (MovieController mc)  = {0x2F3C,0,0x23,0x7000,0xA82A};


/*
 *	somewhat special stuff
 */
pascal ComponentResult MCPositionController (MovieController mc, const Rect *movieRect, const Rect *controllerRect, long someFlags)  = {0x2F3C,0xC,0x24,0x7000,0xA82A};


pascal ComponentResult MCGetControllerInfo (MovieController mc, long *someFlags)  = {0x2F3C,0x4,0x25,0x7000,0xA82A};




pascal ComponentResult MCSetClip (MovieController mc, RgnHandle theClip, RgnHandle movieClip)  = {0x2F3C,0x8,0x28,0x7000,0xA82A};

pascal ComponentResult MCGetClip (MovieController mc, RgnHandle *theClip, RgnHandle *movieClip)  = {0x2F3C,0x8,0x29,0x7000,0xA82A};


pascal ComponentResult MCDrawBadge (MovieController mc, RgnHandle movieRgn, RgnHandle *badgeRgn)  = {0x2F3C,0x8,0x2A,0x7000,0xA82A};

pascal ComponentResult MCSetUpEditMenu (MovieController mc, long modifiers, MenuHandle mh)  = {0x2F3C,0x8,0x2B,0x7000,0xA82A};

pascal ComponentResult MCGetMenuString (MovieController mc, long modifiers, short item, Str255 aString)  = {0x2F3C,0xA,0x2C,0x7000,0xA82A};

pascal ComponentResult MCSetActionFilterWithRefCon (MovieController mc, MCActionFilterWithRefCon blob, long refCon)  = {0x2F3C,0x8,0x2D,0x7000,0xA82A};

#ifdef __cplusplus
}
#endif __cplusplus
enum {
	kMCSetMovieSelect = 0x2,
	kMCRemoveMovieSelect = 0x6,
	kMCIsPlayerEventSelect = 0x7,
	kMCSetActionFilterSelect = 0x8,
	kMCDoActionSelect = 0x9,
	kMCSetControllerAttachedSelect = 0xA,
	kMCIsControllerAttachedSelect = 0xB,
	kMCSetControllerPortSelect = 0xC,
	kMCGetControllerPortSelect = 0xD,
	kMCSetVisibleSelect = 0xE,
	kMCGetVisibleSelect = 0xF,
	kMCGetControllerBoundsRectSelect = 0x10,
	kMCSetControllerBoundsRectSelect = 0x11,
	kMCGetControllerBoundsRgnSelect = 0x12,
	kMCGetWindowRgnSelect = 0x13,
	kMCMovieChangedSelect = 0x14,
	kMCSetDurationSelect = 0x15,
	kMCGetCurrentTimeSelect = 0x16,
	kMCNewAttachedControllerSelect = 0x17,
	kMCDrawSelect = 0x18,
	kMCActivateSelect = 0x19,
	kMCIdleSelect = 0x1A,
	kMCKeySelect = 0x1B,
	kMCClickSelect = 0x1C,
	kMCEnableEditingSelect = 0x1D,
	kMCIsEditingEnabledSelect = 0x1E,
	kMCCopySelect = 0x1F,
	kMCCutSelect = 0x20,
	kMCPasteSelect = 0x21,
	kMCClearSelect = 0x22,
	kMCUndoSelect = 0x23,
	kMCPositionControllerSelect = 0x24,
	kMCGetControllerInfoSelect = 0x25,
	kMCSetClipSelect = 0x28,
	kMCGetClipSelect = 0x29,
	kMCDrawBadgeSelect = 0x2A,
	kMCSetUpEditMenuSelect = 0x2B,
	kMCGetMenuStringSelect = 0x2C,
	kMCSetActionFilterWithRefConSelect = 0x2D 
};




#ifdef __cplusplus
extern "C" {
#endif __cplusplus

/****************************************
*										*
*  		T  I  M  E  B  A  S  E			*
*										*
****************************************/

pascal TimeBase NewTimeBase(void)
		= {0x303C,0xA5,0xAAAA};
pascal void DisposeTimeBase(TimeBase tb)
		= {0x303C,0xB6,0xAAAA};

pascal TimeValue GetTimeBaseTime(TimeBase tb,TimeScale s, TimeRecord *tr)
		= {0x303C,0xA6,0xAAAA};
pascal void SetTimeBaseTime(TimeBase tb,const TimeRecord *tr)
		= {0x303C,0xA7,0xAAAA};
pascal void SetTimeBaseValue(TimeBase tb,TimeValue t,TimeScale s)
		= {0x303C,0xA8,0xAAAA};

pascal Fixed GetTimeBaseRate(TimeBase tb)
		= {0x303C,0xA9,0xAAAA};
pascal void SetTimeBaseRate(TimeBase tb, Fixed r)
		= {0x303C,0xAA,0xAAAA};

pascal TimeValue GetTimeBaseStartTime(TimeBase tb,TimeScale s,TimeRecord *tr)
		= {0x303C,0xAB,0xAAAA};
pascal void SetTimeBaseStartTime(TimeBase tb,const TimeRecord *tr)
		= {0x303C,0xAC,0xAAAA};
pascal TimeValue GetTimeBaseStopTime(TimeBase tb,TimeScale s,TimeRecord *tr)
		= {0x303C,0xAD,0xAAAA};
pascal void SetTimeBaseStopTime(TimeBase tb,const TimeRecord *tr)
		= {0x303C,0xAE,0xAAAA};

pascal long GetTimeBaseFlags(TimeBase tb)
		= {0x303C,0xB1,0xAAAA};
pascal void SetTimeBaseFlags(TimeBase tb,long timeBaseFlags)
		= {0x303C,0xB2,0xAAAA};

pascal void SetTimeBaseMasterTimeBase(TimeBase slave,TimeBase master,
		const TimeRecord *slaveZero)
		= {0x303C,0xB4,0xAAAA};
pascal TimeBase GetTimeBaseMasterTimeBase(TimeBase tb)
		= {0x303C,0xAF,0xAAAA};
pascal void SetTimeBaseMasterClock(TimeBase slave,Component clockMeister,
		const TimeRecord *slaveZero)
		= {0x303C,0xB3,0xAAAA};
pascal ComponentInstance GetTimeBaseMasterClock(TimeBase tb)
		= {0x303C,0xB0,0xAAAA};

pascal void ConvertTime(TimeRecord *inout,TimeBase newBase)
		= {0x303C,0xB5,0xAAAA};
pascal void ConvertTimeScale(TimeRecord *inout,TimeScale newScale)
		= {0x303C,0xB7,0xAAAA};
pascal void AddTime(TimeRecord *dst,const TimeRecord *src)
		= {0x303C,0x10C,0xAAAA};
pascal void SubtractTime(TimeRecord *dst,const TimeRecord *src)
		= {0x303C,0x10D,0xAAAA};

pascal long GetTimeBaseStatus(TimeBase tb,TimeRecord *unpinnedTime)
		= {0x303C,0x10B,0xAAAA};

pascal void SetTimeBaseZero(TimeBase tb, TimeRecord *zero)
		= {0x303C,0x128,0xAAAA};
pascal Fixed GetTimeBaseEffectiveRate(TimeBase tb)
		= {0x303C,0x124,0xAAAA};


/****************************************
*										*
*  		C  A  L  L  B  A  C  K 			*
*										*
****************************************/

pascal QTCallBack NewCallBack(TimeBase tb, short cbType)
		= {0x303C,0xEB,0xAAAA};

pascal void DisposeCallBack(QTCallBack cb)
		= {0x303C,0xEC,0xAAAA};

pascal short GetCallBackType(QTCallBack cb)
		= {0x303C,0xED,0xAAAA};
pascal TimeBase GetCallBackTimeBase(QTCallBack cb)
		= {0x303C,0xEE,0xAAAA};

pascal OSErr CallMeWhen(QTCallBack cb, QTCallBackProc callBackProc, long refCon,
						long param1, long param2, long param3)
		= {0x303C,0xB8,0xAAAA};

pascal void CancelCallBack(QTCallBack cb)
		= {0x303C,0xB9,0xAAAA};


/****************************************
*										*
*  		C L O C K   C A L L B A C K  	*
*  		      S U P P O R T  			*
*										*
****************************************/

pascal OSErr AddCallBackToTimeBase(QTCallBack cb)
		= {0x303C,0x129,0xAAAA};
pascal OSErr RemoveCallBackFromTimeBase(QTCallBack cb)
		= {0x303C,0x12A,0xAAAA};
pascal QTCallBack GetFirstCallBack(TimeBase tb)
		= {0x303C,0x12B,0xAAAA};
pascal QTCallBack GetNextCallBack(QTCallBack cb)
		= {0x303C,0x12C,0xAAAA};
pascal void ExecuteCallBack(QTCallBack cb)
		= {0x303C,0x12D,0xAAAA};
#ifdef __cplusplus
}
#endif __cplusplus

#endif __MOVIES__
