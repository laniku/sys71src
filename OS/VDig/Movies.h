
/************************************************************

Created: Wednesday, August 14, 1991 at 12:23 PM
 Movies.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1991
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

#ifndef __COMPONENTS__
#include <Components.h>
#endif

#ifndef __IMAGECOMPRESSION__
#include <ImageCompression.h>
#endif


#define gestaltQuickTime 'qtim'

#define MovieFileType 'MooV'

#define VideoMediaType 'vide'
#define SoundMediaType 'soun'

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


typedef long TimeValue;
typedef long TimeScale;

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


struct Int64 {
 long hi;
 long lo;
};

typedef struct Int64 Int64;

struct TimeRecord {
 Int64 value;
 TimeScale scale;
 TimeBase base;
};

typedef struct TimeRecord TimeRecord;

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
 long descSize;
 long dataFormat;
 long resvd1;
 short resvd2;
 short dataRefIndex;
 short version;
 short revlevel;
 long vendor;
 short numChannels;
 short sampleSize;
 short compressionID;
 short packetSize;
 Fixed sampleRate;
};

typedef struct SoundDescription SoundDescription;
typedef SoundDescription *SoundDescriptionPtr, **SoundDescriptionHandle;


enum {movieProgressOpen = 0,movieProgressUpdatePercent = 1,movieProgressClose = 2};
typedef unsigned char movieProgressMessages;

enum {progressOpFlatten = 1,progressOpInsertTrackSegment = 2,progressOpInsertMovieSegment = 3,
 progressOpPaste = 4,progressOpAddMovieSelection = 5,progressOpCopy = 6,
 progressOpCut = 7,progressOpLoadMovieIntoRam = 8,progressOpLoadTrackIntoRam = 9,
	progressOpLoadMediaIntoRam = 10};
typedef unsigned char movieProgressOperations;

enum {mediaQualityDraft = 0x0000, mediaQualityNormal = 0x0040, mediaQualityBetter = 0x0080,
	mediaQualityBest = 0x00C0};


typedef pascal OSErr  (*MovieProgressProcPtr) (Movie m, short message, short whatOperation,
           Fixed percentDone, long refCon);        

typedef pascal OSErr (*MovieRgnCoverProc)(Movie m, RgnHandle changedRgn, long refcon);  

typedef Handle MediaInformationHandle;
typedef ComponentInstance MediaHandler;
typedef Component MediaHandlerComponent;
typedef ComponentInstance DataHandler;
typedef Component DataHandlerComponent;
typedef ComponentResult HandlerError;
typedef ComponentInstance MovieController;

typedef pascal void (*ErrorProcPtr)(OSErr theErr, long refcon);        

typedef pascal Boolean (*MoviePreviewCallOutProc)(long refcon);        


enum {newMovieActive = 1<<0,newMovieDontResolveDataRefs = 1<<1,newMovieDontAskUnresolvedDataRefs = 1<<2};
typedef unsigned char newMovieFlagsEnum;

enum {trackUsageInMovie = 1<<1,trackUsageInPreview = 1<<2,trackUsageInPoster = 1<<3};
typedef unsigned char trackUsageEnum;

enum {mediaSampleNotSync = 1};
typedef unsigned char mediaSampleFlagsEnum;

enum {nextTimeMediaSample = 1<<0,nextTimeMediaEdit = 1<<1,nextTimeTrackEdit = 1<<2,
 nextTimeSyncSample = 1<<3,nextTimeEdgeOK = 1<<14,nextTimeIgnoreActiveSegment = 1<<15};
typedef unsigned short nextTimeFlagsEnum;

enum {createMovieFileDeleteCurFile = 1L<<31,createMovieFileDontCreateMovie = 1L<<30,
 createMovieFileDontOpenFile = 1L<<29};
typedef unsigned long createMovieFileFlagsEnum;

enum {flattenAddMovieToDataFork = 1L<<0,flattenActiveTracksOnly = 1L<<2,
 flattenDontInterleaveFlatten = 1L<<3};
typedef unsigned char movieFlattenFlagsEnum;

enum {movieScrapDontZeroScrap = 1<<0,movieScrapOnlyPutMovie = 1<<1};
typedef unsigned char movieScrapFlagsEnum;

enum {hintsScrubMode = 1<<0};
typedef unsigned char playHintsEnum;






#ifdef __cplusplus
extern "C" {
#endif
/*  Initialization Routines  */
pascal OSErr EnterMovies(void)
 = {0x303C,0x1,0xAAAA}; 
pascal void ExitMovies(void)
 = {0x303C,0x2,0xAAAA}; 

/*  error Routines  */
pascal OSErr GetMoviesError(void)
 = {0x303C,0x3,0xAAAA}; 
pascal void ClearMoviesStickyError(void)
 = {0x303C,0xDE,0xAAAA}; 
pascal OSErr GetMoviesStickyError(void)
 = {0x303C,0x4,0xAAAA}; 

pascal void SetMoviesErrorProc(ErrorProcPtr errProc,long refcon)
 = {0x303C,0xEF,0xAAAA}; 

pascal ComponentResult GetTrackStatus(Track t)
 = {0x303C,0x172,0xAAAA}; 
pascal ComponentResult GetMovieStatus(Movie m,Track *firstProblemTrack)
 = {0x303C,0x173,0xAAAA}; 

/*  Playback Routines  */
pascal void MoviesTask(Movie m,long maxMilliSecToUse)
 = {0x303C,0x5,0xAAAA}; 

pascal void StartMovie(Movie m)
 = {0x303C,0xB,0xAAAA}; 
pascal void StopMovie(Movie m)
 = {0x303C,0xC,0xAAAA}; 
pascal void GoToBeginningOfMovie(Movie m)
 = {0x303C,0xD,0xAAAA}; 
pascal void GoToEndOfMovie(Movie m)
 = {0x303C,0xE,0xAAAA}; 
pascal Boolean IsMovieDone(Movie m)
 = {0x303C,0xDD,0xAAAA}; 

pascal Boolean GetMoviePreviewMode(Movie m)
 = {0x303C,0xF,0xAAAA}; 
pascal void SetMoviePreviewMode(Movie m,Boolean usePreview)
 = {0x303C,0x10,0xAAAA}; 
pascal void ShowMoviePoster(Movie m)
 = {0x303C,0x11,0xAAAA}; 

pascal void GetMovieGWorld(Movie m,CGrafPtr *port,GDHandle *gdh)
 = {0x303C,0x15,0xAAAA}; 
pascal void SetMovieGWorld(Movie m,CGrafPtr port,GDHandle gdh)
 = {0x303C,0x16,0xAAAA}; 

pascal OSErr PrerollMovie(Movie m,TimeValue time,Fixed Rate)
 = {0x303C,0x6,0xAAAA}; 
pascal OSErr LoadMovieIntoRam(Movie m,TimeValue time,TimeValue duration,
 long flags)
 = {0x303C,0x7,0xAAAA}; 
pascal OSErr LoadTrackIntoRam(Track t,TimeValue time,TimeValue duration,
 long flags)
 = {0x303C,0x16E,0xAAAA}; 
pascal OSErr LoadMediaIntoRam(Media m,TimeValue time,TimeValue duration,
 long flags)
 = {0x303C,0x8,0xAAAA}; 

pascal void SetMovieActive(Movie m,Boolean active)
 = {0x303C,0x9,0xAAAA}; 
pascal Boolean GetMovieActive(Movie m)
 = {0x303C,0xA,0xAAAA}; 

pascal void PlayMoviePreview(Movie m,MoviePreviewCallOutProc callOutProc,
 long refcon)
 = {0x303C,0xF2,0xAAAA}; 

/*  Movie PICT Routines  */
pascal PicHandle GetMoviePict(Movie m,TimeValue time)
 = {0x303C,0x1D,0xAAAA}; 
pascal PicHandle GetTrackPict(Track t,TimeValue time)
 = {0x303C,0x1E,0xAAAA}; 

pascal PicHandle GetMoviePosterPict(Movie m)
 = {0x303C,0xF7,0xAAAA}; 

/*  movie TimeBase Routines  */
pascal TimeBase GetMovieTimeBase(Movie m)
 = {0x303C,0x12,0xAAAA}; 

pascal void SetMovieMasterTimeBase(Movie m,TimeBase tb,const TimeRecord *slaveZero)
 = {0x303C,0x167,0xAAAA}; 
pascal void SetMovieMasterClock(Movie m,Component clockMeister,const TimeRecord *slaveZero)
 = {0x303C,0x168,0xAAAA}; 

/*  spatial movie Routines  */
pascal void GetMovieBox(Movie m,Rect *boxRect)
 = {0x303C,0xF9,0xAAAA}; 
pascal void SetMovieBox(Movie m,const Rect *boxRect)
 = {0x303C,0xFA,0xAAAA}; 

/*  movie display clip  */
pascal RgnHandle GetMovieDisplayClipRgn(Movie m)
 = {0x303C,0xFC,0xAAAA}; 
pascal void SetMovieDisplayClipRgn(Movie m,RgnHandle theClip)
 = {0x303C,0xFD,0xAAAA}; 

/*  movie clip  */
pascal RgnHandle GetMovieClipRgn(Movie m)
 = {0x303C,0x100,0xAAAA}; 
pascal void SetMovieClipRgn(Movie m,RgnHandle theClip)
 = {0x303C,0x101,0xAAAA}; 

/*  track clip  */
pascal RgnHandle GetTrackClipRgn(Track t)
 = {0x303C,0x102,0xAAAA}; 
pascal void SetTrackClipRgn(Track t,RgnHandle theClip)
 = {0x303C,0x103,0xAAAA}; 

/*  bounds in display space  */
pascal RgnHandle GetMovieDisplayBoundsRgn(Movie m)
 = {0x303C,0xFB,0xAAAA}; 
pascal RgnHandle GetTrackDisplayBoundsRgn(Track t)
 = {0x303C,0x112,0xAAAA}; 

/*  bounds in movie space  */
pascal RgnHandle GetMovieBoundsRgn(Movie m)
 = {0x303C,0xFE,0xAAAA}; 
pascal RgnHandle GetTrackMovieBoundsRgn(Track t)
 = {0x303C,0xFF,0xAAAA}; 

/*  bounds in track space  */
pascal RgnHandle GetTrackBoundsRgn(Track t)
 = {0x303C,0x111,0xAAAA}; 

/*  movie poster box  */
pascal void GetPosterBox(Movie m,Rect *boxRect)
 = {0x303C,0x16F,0xAAAA}; 
pascal void SetPosterBox(Movie m,const Rect *boxRect)
 = {0x303C,0x170,0xAAAA}; 

/*  movie/track bounds over a range of time  */
pascal RgnHandle GetMovieSegmentDisplayBoundsRgn(Movie m,TimeValue time,
 TimeValue duration)
 = {0x303C,0x16C,0xAAAA}; 
pascal RgnHandle GetTrackSegmentDisplayBoundsRgn(Track t,TimeValue time,
 TimeValue duration)
 = {0x303C,0x16B,0xAAAA}; 

pascal void SetMovieCoverProcs(Movie m,MovieRgnCoverProc uncoverProc,MovieRgnCoverProc coverProc,
 long refCon)
 = {0x303C,0x179,0xAAAA}; 

/*  mattes - always in track space  */
pascal PixMapHandle GetTrackMatte(Track t)
 = {0x303C,0x115,0xAAAA}; 
pascal void SetTrackMatte(Track t,PixMapHandle theMatte)
 = {0x303C,0x116,0xAAAA}; 
pascal void DisposeMatte(PixMapHandle theMatte)
 = {0x303C,0x14A,0xAAAA}; 

/*  movie creation Routines  */
pascal OSErr NewMovieFromHandle(Movie *m,Handle h,short newMovieFlags,Boolean *dataRefWasChanged)
 = {0x303C,0xF1,0xAAAA}; 
pascal OSErr PutMovieIntoHandle(Movie m,Handle h)
 = {0x303C,0x22,0xAAAA}; 

pascal Movie NewMovie(long newMovieFlags)
 = {0x303C,0x187,0xAAAA}; 
pascal void DisposeMovie(Movie m)
 = {0x303C,0x23,0xAAAA}; 

/*  Movie Routines  */
pascal unsigned long GetMovieCreationTime(Movie m)
 = {0x303C,0x26,0xAAAA}; 
pascal unsigned long GetMovieModificationTime(Movie m)
 = {0x303C,0x27,0xAAAA}; 

pascal TimeScale GetMovieTimeScale(Movie m)
 = {0x303C,0x29,0xAAAA}; 
pascal void SetMovieTimeScale(Movie m,TimeScale timeScale)
 = {0x303C,0x2A,0xAAAA}; 

pascal TimeValue GetMovieDuration(Movie m)
 = {0x303C,0x2B,0xAAAA}; 

pascal Fixed GetMovieRate(Movie m)
 = {0x303C,0x2C,0xAAAA}; 
pascal void SetMovieRate(Movie m,Fixed rate)
 = {0x303C,0x2D,0xAAAA}; 

pascal Fixed GetMoviePreferredRate(Movie m)
 = {0x303C,0xF3,0xAAAA}; 
pascal void SetMoviePreferredRate(Movie m,Fixed rate)
 = {0x303C,0xF4,0xAAAA}; 

pascal short GetMoviePreferredVolume(Movie m)
 = {0x303C,0xF5,0xAAAA}; 
pascal void SetMoviePreferredVolume(Movie m,short volume)
 = {0x303C,0xF6,0xAAAA}; 

pascal short GetMovieVolume(Movie m)
 = {0x303C,0x2E,0xAAAA}; 
pascal void SetMovieVolume(Movie m,short volume)
 = {0x303C,0x2F,0xAAAA}; 

pascal void GetMovieMatrix(Movie m,MatrixRecord *matrix)
 = {0x303C,0x31,0xAAAA}; 
pascal void SetMovieMatrix(Movie m,const MatrixRecord *matrix)
 = {0x303C,0x32,0xAAAA}; 

pascal void GetMoviePreviewTime(Movie m,TimeValue *previewTime,TimeValue *previewDuration)
 = {0x303C,0x33,0xAAAA}; 
pascal void SetMoviePreviewTime(Movie m,TimeValue previewTime,TimeValue previewDuration)
 = {0x303C,0x34,0xAAAA}; 

pascal TimeValue GetMoviePosterTime(Movie m)
 = {0x303C,0x35,0xAAAA}; 
pascal void SetMoviePosterTime(Movie m,TimeValue posterTime)
 = {0x303C,0x36,0xAAAA}; 

pascal void GetMovieSelection(Movie m,TimeValue *selectionTime,TimeValue *selectionDuration)
 = {0x303C,0x37,0xAAAA}; 
pascal void SetMovieSelection(Movie m,TimeValue selectionTime,TimeValue selectionDuration)
 = {0x303C,0x38,0xAAAA}; 

pascal void SetMovieActiveSegment(Movie m,TimeValue startTime,TimeValue duration)
 = {0x303C,0x15C,0xAAAA}; 
pascal void GetMovieActiveSegment(Movie m,TimeValue *startTime,TimeValue *duration)
 = {0x303C,0x15D,0xAAAA}; 

pascal TimeValue GetMovieTime(Movie m,TimeRecord *currentTime)
 = {0x303C,0x39,0xAAAA}; 
pascal void SetMovieTime(Movie m,const TimeRecord *newtime)
 = {0x303C,0x3C,0xAAAA}; 
pascal void SetMovieTimeValue(Movie m,TimeValue newtime)
 = {0x303C,0x3D,0xAAAA}; 

pascal UserData GetMovieUserData(Movie m)
 = {0x303C,0x3E,0xAAAA}; 

pascal void SetMoviePlayHints(Movie movie,long flags,long flagsMask)
 = {0x303C,0x1A1,0xAAAA};

/*  Movie/Track/Media finding Routines  */
pascal long GetMovieTrackCount(Movie m)
 = {0x303C,0x3F,0xAAAA}; 
pascal Track GetMovieTrack(Movie m,long trackID)
 = {0x303C,0x40,0xAAAA}; 

pascal Track GetMovieIndTrack(Movie m,long index)
 = {0x303C,0x117,0xAAAA}; 

pascal long GetTrackID(Track t)
 = {0x303C,0x127,0xAAAA}; 

pascal Movie GetTrackMovie(Track t)
 = {0x303C,0xD0,0xAAAA}; 

pascal Media GetTrackMedia(Track t)
 = {0x303C,0x62,0xAAAA}; 
pascal Track GetMediaTrack(Media m)
 = {0x303C,0xC5,0xAAAA}; 

/*  Track creation Routines  */
pascal Track NewMovieTrack(Movie m,Fixed width,Fixed height,short trackVolume)
 = {0x303C,0x188,0xAAAA}; 
pascal void DisposeMovieTrack(Track t)
 = {0x303C,0x42,0xAAAA}; 

/*  Track Routines  */
pascal unsigned long GetTrackCreationTime(Track t)
 = {0x303C,0x43,0xAAAA}; 
pascal unsigned long GetTrackModificationTime(Track t)
 = {0x303C,0x44,0xAAAA}; 

pascal Boolean GetTrackEnabled(Track t)
 = {0x303C,0x45,0xAAAA}; 
pascal void SetTrackEnabled(Track t,Boolean isEnabled)
 = {0x303C,0x46,0xAAAA}; 

pascal long GetTrackUsage(Track t)
 = {0x303C,0x47,0xAAAA}; 
pascal void SetTrackUsage(Track t,long usage)
 = {0x303C,0x48,0xAAAA}; 

pascal TimeValue GetTrackDuration(Track t)
 = {0x303C,0x4B,0xAAAA}; 

pascal TimeValue GetTrackOffset(Track t)
 = {0x303C,0x4C,0xAAAA}; 
pascal void SetTrackOffset(Track t,TimeValue offset)
 = {0x303C,0x4D,0xAAAA}; 

pascal short GetTrackLayer(Track t)
 = {0x303C,0x50,0xAAAA}; 
pascal void SetTrackLayer(Track t,short layer)
 = {0x303C,0x51,0xAAAA}; 

pascal Track GetTrackAlternate(Track t)
 = {0x303C,0x52,0xAAAA}; 
pascal void SetTrackAlternate(Track t,Track alternateT)
 = {0x303C,0x53,0xAAAA}; 

pascal short GetTrackVolume(Track t)
 = {0x303C,0x54,0xAAAA}; 
pascal void SetTrackVolume(Track t,short volume)
 = {0x303C,0x55,0xAAAA}; 

pascal void GetTrackMatrix(Track t,MatrixRecord *matrix)
 = {0x303C,0x56,0xAAAA}; 
pascal void SetTrackMatrix(Track t,const MatrixRecord *matrix)
 = {0x303C,0x57,0xAAAA}; 

pascal void GetTrackDimensions(Track t,Fixed *width,Fixed *height)
 = {0x303C,0x5D,0xAAAA}; 
pascal void SetTrackDimensions(Track t,Fixed width,Fixed height)
 = {0x303C,0x5E,0xAAAA}; 

pascal UserData GetTrackUserData(Track t)
 = {0x303C,0x5F,0xAAAA}; 

/*  Media creation Routines  */
pascal Media NewTrackMedia(Track t,OSType mediaType,TimeScale timeScale,
 Handle dataRef,OSType dataRefType)
 = {0x303C,0x18E,0xAAAA}; 
pascal void DisposeTrackMedia(Media m)
 = {0x303C,0x61,0xAAAA}; 

/*  Media Routines  */
pascal unsigned long GetMediaCreationTime(Media m)
 = {0x303C,0x66,0xAAAA}; 
pascal unsigned long GetMediaModificationTime(Media m)
 = {0x303C,0x67,0xAAAA}; 

pascal TimeScale GetMediaTimeScale(Media m)
 = {0x303C,0x68,0xAAAA}; 
pascal void SetMediaTimeScale(Media m,TimeScale timeScale)
 = {0x303C,0x69,0xAAAA}; 

pascal TimeValue GetMediaDuration(Media m)
 = {0x303C,0x6A,0xAAAA}; 

pascal short GetMediaLanguage(Media m)
 = {0x303C,0x6B,0xAAAA}; 
pascal void SetMediaLanguage(Media m,short language)
 = {0x303C,0x6C,0xAAAA}; 

pascal short GetMediaQuality(Media m)
 = {0x303C,0x6D,0xAAAA}; 
pascal void SetMediaQuality(Media m,short quality)
 = {0x303C,0x6E,0xAAAA}; 

pascal UserData GetMediaUserData(Media m)
 = {0x303C,0x70,0xAAAA}; 

pascal void SetMediaPlayHints(Movie movie,long flags,long flagsMask)
 = {0x303C,0x1A2,0xAAAA};

/*  Media Handler Routines  */
pascal MediaHandler GetMediaHandler(Media m)
 = {0x303C,0x71,0xAAAA}; 
pascal OSErr SetMediaHandler(Media m,MediaHandlerComponent mH)
 = {0x303C,0x190,0xAAAA}; 

pascal void GetMediaHandlerDescription(Media m,OSType *mediaType, Str255 creatorName,
 OSType *creatorManufacturer)
 = {0x303C,0x6F,0xAAAA}; 

#ifdef __cplusplus
}
#endif
enum {dataRefSelfReference = 1<<0,dataRefWasNotResolved = 1<<1};
typedef unsigned char dataRefAttributesFlags;


#ifdef __cplusplus
extern "C" {
#endif
/*  Media dataRef Routines  */
pascal OSErr GetMediaDataRef(Media m,short index,Handle *dataRef,OSType *dataRefType,
 long *dataRefAttributes)
 = {0x303C,0x197,0xAAAA}; 
pascal OSErr AddMediaDataRef(Media m,short *index,Handle dataRef,OSType dataRefType)
 = {0x303C,0x198,0xAAAA}; 

pascal OSErr GetMediaDataRefCount(Media m,short *count)
 = {0x303C,0x199,0xAAAA}; 

/*  Media data handler Routines  */
pascal DataHandler GetMediaDataHandler(Media m,short index)
 = {0x303C,0x19F,0xAAAA}; 
pascal OSErr SetMediaDataHandler(Media m,short index,DataHandlerComponent dataHandler)
 = {0x303C,0x1A0,0xAAAA}; 

pascal void GetMediaDataHandlerDescription(Media m,short index,OSType *dhType,
 Str255 creatorName,OSType *creatorManufacturer)
 = {0x303C,0x19E,0xAAAA}; 

/*  Media sample Routines  */
pascal long GetMediaSampleDescriptionCount(Media m)
 = {0x303C,0x77,0xAAAA}; 
pascal void GetMediaSampleDescription(Media m,long index,SampleDescriptionHandle descH)
 = {0x303C,0x78,0xAAAA}; 
pascal long GetMediaSampleCount(Media m)
 = {0x303C,0x79,0xAAAA}; 
pascal void SampleNumToMediaTime(Media m,long logicalSampleNum,TimeValue *sampleTime,
 TimeValue *sampleDuration)
 = {0x303C,0x7A,0xAAAA}; 
pascal void MediaTimeToSampleNum(Media m,TimeValue time,long *sampleNum,
 TimeValue *sampleTime,TimeValue *sampleDuration)
 = {0x303C,0x7B,0xAAAA}; 

pascal OSErr AddMediaSample(Media m,Handle dataIn,long inOffset,unsigned long size,
 TimeValue durationPerSample,SampleDescriptionHandle sampleDescriptionH,
 long numberOfSamples,short sampleFlags,TimeValue *sampleTime)
 = {0x303C,0x7C,0xAAAA}; 
pascal OSErr AddMediaSampleReference(Media m,long dataOffset,unsigned long size,
 TimeValue durationPerSample,SampleDescriptionHandle sampleDescriptionH,
 long numberOfSamples,short sampleFlags,TimeValue *sampleTime)
 = {0x303C,0x7D,0xAAAA}; 
pascal OSErr GetMediaSample(Media m,Handle dataOut,long maxSizeToGrow,long *size,
 TimeValue time,TimeValue *sampleTime,TimeValue *durationPerSample,SampleDescriptionHandle sampleDescriptionH,
 long *sampleDescriptionIndex,long maxNumberOfSamples,long *numberOfSamples,
 short *sampleFlags)
 = {0x303C,0x7E,0xAAAA}; 
pascal OSErr GetMediaSampleReference(Media m,long *dataOffset,long *size,
 TimeValue time,TimeValue *sampleTime,TimeValue *durationPerSample,SampleDescriptionHandle sampleDescriptionH,
 long *sampleDescriptionIndex,long maxNumberOfSamples,long *numberOfSamples,
 short *sampleFlags)
 = {0x303C,0x7F,0xAAAA}; 

/*  High level editing Routines  */
pascal Movie CutMovieSelection(Movie m)
 = {0x303C,0x8D,0xAAAA}; 
pascal Movie CopyMovieSelection(Movie m)
 = {0x303C,0x8E,0xAAAA}; 
pascal void PasteMovieSelection(Movie m,Movie src)
 = {0x303C,0x8F,0xAAAA}; 
pascal void AddMovieSelection(Movie m,Movie src)
 = {0x303C,0x152,0xAAAA}; 
pascal void ClearMovieSelection(Movie m)
 = {0x303C,0xE1,0xAAAA}; 

/*  Middle-level Editing Routines  */
pascal OSErr InsertTrackSegment(Track srcTrack,Track dstTrack,TimeValue srcIn,
 TimeValue srcDuration,TimeValue dstIn)
 = {0x303C,0x85,0xAAAA}; 
pascal OSErr InsertMovieSegment(Movie srcMovie,Movie dstMovie,TimeValue srcIn,
 TimeValue srcDuration,TimeValue dstIn)
 = {0x303C,0x86,0xAAAA}; 
pascal OSErr InsertEmptyTrackSegment(Track dstTrack,TimeValue dstIn,TimeValue dstDuration)
 = {0x303C,0x87,0xAAAA}; 
pascal OSErr InsertEmptyMovieSegment(Movie dstMovie,TimeValue dstIn,TimeValue dstDuration)
 = {0x303C,0x88,0xAAAA}; 
pascal OSErr DeleteTrackSegment(Track t,TimeValue dstIn,TimeValue duration)
 = {0x303C,0x89,0xAAAA}; 
pascal OSErr DeleteMovieSegment(Movie m,TimeValue dstIn,TimeValue duration)
 = {0x303C,0x8A,0xAAAA}; 
pascal OSErr ScaleTrackSegment(Track t,TimeValue dstIn,TimeValue oldDuration,
 TimeValue newDuration)
 = {0x303C,0x8B,0xAAAA}; 
pascal OSErr ScaleMovieSegment(Movie m,TimeValue dstIn,TimeValue oldDuration,
 TimeValue newDuration)
 = {0x303C,0x8C,0xAAAA}; 

pascal OSErr CopyTrackSettings(Track srcTrack,Track dstTrack)
 = {0x303C,0x153,0xAAAA}; 
pascal OSErr CopyMovieSettings(Movie srcMovie,Movie dstMovie)
 = {0x303C,0x154,0xAAAA}; 

/*  low-level Editing Routines  */
pascal OSErr InsertMediaIntoTrack(Track t,TimeValue trackStart,TimeValue mediaTime,
 TimeValue mediaDuration,Fixed mediaRate)
 = {0x303C,0x183,0xAAAA}; 

pascal OSErr BeginMediaEdits(Media m)
 = {0x303C,0x72,0xAAAA}; 
pascal OSErr EndMediaEdits(Media m)
 = {0x303C,0x73,0xAAAA}; 

/*  movie & track edit state Routines  */
pascal MovieEditState NewMovieEditState(Movie m)
 = {0x303C,0x104,0xAAAA}; 
pascal OSErr UseMovieEditState(Movie m,MovieEditState toState)
 = {0x303C,0x105,0xAAAA}; 
pascal OSErr DisposeMovieEditState(MovieEditState state)
 = {0x303C,0x106,0xAAAA}; 

pascal TrackEditState NewTrackEditState(Track t)
 = {0x303C,0x107,0xAAAA}; 
pascal OSErr UseTrackEditState(Track t,TrackEditState state)
 = {0x303C,0x108,0xAAAA}; 
pascal OSErr DisposeTrackEditState(TrackEditState state)
 = {0x303C,0x109,0xAAAA}; 

/*  Miscellaneous Routines  */
pascal TimeValue TrackTimeToMediaTime(TimeValue value,Track t)
 = {0x303C,0x96,0xAAAA}; 

pascal long GetMovieDataSize(Movie m,TimeValue startTime,TimeValue duration)
 = {0x303C,0x98,0xAAAA}; 
pascal long GetTrackDataSize(Track t,TimeValue startTime,TimeValue duration)
 = {0x303C,0x149,0xAAAA}; 
pascal long GetMediaDataSize(Media m,TimeValue startTime,TimeValue duration)
 = {0x303C,0x99,0xAAAA}; 

pascal Boolean PtInMovie(Movie m,Point pt)
 = {0x303C,0x9A,0xAAAA}; 
pascal Boolean PtInTrack(Track t,Point pt)
 = {0x303C,0x9B,0xAAAA}; 

pascal OSErr UpdateMovie(Movie m)
 = {0x303C,0x1F,0xAAAA}; 

/*  Alternate Group Selection Routines  */
pascal void SetMovieLanguage(Movie m,long language)
 = {0x303C,0x9C,0xAAAA}; 

pascal void SetAutoTrackAlternatesEnabled(Movie m,Boolean enable)
 = {0x303C,0x15E,0xAAAA}; 
pascal void SelectMovieAlternates(Movie m)
 = {0x303C,0x15F,0xAAAA}; 

/*  UserData Routines  */
pascal OSErr GetUserData(UserData u,Handle data, OSType udType,long index)
 = {0x303C,0x9E,0xAAAA}; 
pascal OSErr AddUserData(UserData u,Handle data,OSType udType)
 = {0x303C,0x9F,0xAAAA}; 
pascal OSErr RemoveUserData(UserData u,OSType udType,long index)
 = {0x303C,0xA0,0xAAAA}; 
pascal OSType GetNextUserDataType(UserData u, OSType udType)
 = {0x303C,0x1A5,0xAAAA}; 
pascal short CountUserDataType(UserData u,OSType udType)
 = {0x303C,0x14B,0xAAAA}; 
pascal OSErr AddUserDataText(UserData u,Handle data,OSType udType,long index,
 short itlRegionTag)
 = {0x303C,0x14C,0xAAAA}; 
pascal OSErr GetUserDataText(UserData u,Handle data,OSType udType,long index,
 short itlRegionTag)
 = {0x303C,0x14D,0xAAAA}; 
pascal OSErr RemoveUserDataText(UserData u,OSType udType,long index,short itlRegionTag)
 = {0x303C,0x14E,0xAAAA}; 

/*  interesting time Routines  */
pascal void GetMediaNextInterestingTime(Media m,short interestingTimeFlags,
 TimeValue time,Fixed rate,TimeValue *interestingTime,TimeValue *interestingDuration)
 = {0x303C,0x16D,0xAAAA}; 
pascal void GetTrackNextInterestingTime(Track t,short interestingTimeFlags,
 TimeValue time,Fixed rate,TimeValue *interestingTime,TimeValue *interestingDuration)
 = {0x303C,0xE2,0xAAAA}; 
pascal void GetMovieNextInterestingTime(Movie m,short interestingTimeFlags,
 short numMediaTypes,const OSType *whichMediaTypes,TimeValue time,Fixed rate,
 TimeValue *interestingTime,TimeValue *interestingDuration)
 = {0x303C,0x10E,0xAAAA}; 

/*  movie file Routines  */
pascal OSErr CreateMovieFile(const FSSpec *fileSpec,OSType creator,ScriptCode scriptTag,
 long createMovieFileFlags,short *resRefNum,Movie *newMovie)
 = {0x303C,0x191,0xAAAA}; 
pascal OSErr DeleteMovieFile(const FSSpec *fileSpec)
 = {0x303C,0x175,0xAAAA}; 

pascal OSErr OpenMovieFile(const FSSpec *fileSpec,short *resRefNum, char perms)
 = {0x303C,0x192,0xAAAA}; 
pascal OSErr CloseMovieFile(short resRefNum)
 = {0x303C,0xD5,0xAAAA}; 
#ifdef __cplusplus
}
#endif
enum {

 movieInDataForkResID = -1			/* magic res ID */

};

#ifdef __cplusplus
extern "C" {
#endif
pascal OSErr NewMovieFromFile(Movie *m,short resRefNum,short *resId, StringPtr resName,
 short newMovieFlags,Boolean *dataRefWasChanged)
 = {0x303C,0xF0,0xAAAA}; 

pascal OSErr AddMovieResource(Movie m,short resRefNum,short *resId,const StringPtr resName)
 = {0x303C,0xD7,0xAAAA}; 
pascal OSErr RemoveMovieResource(short resRefNum,short resId)
 = {0x303C,0x176,0xAAAA}; 
pascal OSErr UpdateMovieResource(Movie m,short resRefNum,short resId,const StringPtr resName)
 = {0x303C,0xD8,0xAAAA}; 

pascal Boolean HasMovieChanged(Movie m)
 = {0x303C,0xD9,0xAAAA}; 
pascal void ClearMovieChanged(Movie m)
 = {0x303C,0x113,0xAAAA}; 

pascal void FlattenMovie(Movie m,long movieFlattenFlags,const FSSpec *theFile,
 OSType creator,ScriptCode scriptTag,long createMovieFileFlags,short *resId,
 const StringPtr resName)
 = {0x303C,0x19B,0xAAAA}; 
pascal Movie FlattenMovieData(Movie m,long movieFlattenFlags,const FSSpec *theFile,
 OSType creator,ScriptCode scriptTag,long createMovieFileFlags)
 = {0x303C,0x19C,0xAAAA}; 
pascal void SetMovieProgressProc(Movie m,MovieProgressProcPtr p,long refCon)
 = {0x303C,0x19A,0xAAAA}; 

pascal OSErr PutMovieOnScrap(Movie m,long movieScrapFlags)
 = {0x303C,0x18C,0xAAAA}; 
pascal Movie NewMovieFromScrap(long newMovieFlags)
 = {0x303C,0x18D,0xAAAA}; 

/*  Video Media Routines  */
pascal HandlerError GetVideoMediaGraphicsMode(MediaHandler mh,long *graphicsMode,
 RGBColor *opColor)
 = {0x2F3C,0x8,0x101,0x7000,0xA82A}; 
pascal HandlerError SetVideoMediaGraphicsMode(MediaHandler mh,long graphicsMode,
 const RGBColor *opColor)
 = {0x2F3C,0x8,0x102,0x7000,0xA82A}; 

/*  Sound Media Routines  */
pascal HandlerError GetSoundMediaBalance(MediaHandler mh,short *balance)
 = {0x2F3C,0x4,0x101,0x7000,0xA82A}; 
pascal HandlerError SetSoundMediaBalance(MediaHandler mh,short balance)
 = {0x2F3C,0x2,0x102,0x7000,0xA82A}; 

#ifdef __cplusplus
}
#endif


enum {

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
 progressProcAborted = -2019
};
enum {
 movieToolboxUnitialized = -2020,
 wfFileNotFound = -2021,
 cantCreateSingleForkFile = -2022,
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
 invalidSampleDescIndex = -2039
};
enum {
 invalidChunkCache = -2040,
 invalidSampleDescription = -2041,
 dataNotOpenForRead = -2042,
 dataNotOpenForWrite = -2043,
 dataAlreadyOpenForWrite = -2044,
 dataAlreadyClosed = -2045,
 endOfDataReached = -2046,
 dataNoDataRef = -2047,
 noMovieFound = -2048,
 invalidDataRefContainer = -2049,
 badDataRefIndex = -2050,
 noDefaultDataRef = -2051,
 couldNotUseAnExistingSample = -2052,
 featureUnsupported = -2053
};

/* TimeBase Routines */
enum {loopTimeBase = 1, palindromeLoopTimeBase = 2};
typedef unsigned char TimeBaseFlags;

enum {
 triggerTimeFwd       = 0x0001,  	/* when curTime exceeds triggerTime going forward */
 triggerTimeBwd       = 0x0002,  	/* when curTime exceeds triggerTime going backwards */
 triggerTimeEither    = 0x0003,  	/* when curTime exceeds triggerTime going either direction */
 triggerRateLT        = 0x0004,  	/* when rate changes to less than trigger value */
 triggerRateGT        = 0x0008,  	/* when rate changes to greater than trigger value */
 triggerRateEqual     = 0x0010,  	/* when rate changes to equal trigger value */
 triggerRateLTE       = triggerRateLT | triggerRateEqual,
 triggerRateGTE       = triggerRateGT | triggerRateEqual,
 triggerRateNotEqual  = triggerRateGT | triggerRateEqual | triggerRateLT,
 triggerRateChange    = 0
};
typedef unsigned char QTCallBackFlags;

enum {timeBaseBeforeStartTime = 1,timeBaseAfterStopTime = 2};
typedef unsigned char TimeBaseStatus;

enum {callBackAtTime = 1,callBackAtRate = 2,callBackAtTimeJump = 3,callBackAtInterrupt = 0x8000};
typedef unsigned short QTCallBackType;


typedef pascal void (*QTCallBackProc)(QTCallBack cb,long refCon);

enum {

 qtcbNeedsRateChanges = 1,
 qtcbNeedsTimeChanges = 2
};

/* CallBack equates */
struct QTCallBackHeader {
 long callBackFlags;
 long reserved1;
 char qtPrivate[40];
};

typedef struct QTCallBackHeader QTCallBackHeader;


#ifdef __cplusplus
extern "C" {
#endif
/*  TimeBase Routines  */
pascal TimeBase NewTimeBase(void)
 = {0x303C,0xA5,0xAAAA}; 
pascal void DisposeTimeBase(TimeBase tb)
 = {0x303C,0xB6,0xAAAA}; 

pascal TimeValue GetTimeBaseTime(TimeBase tb,TimeScale s,TimeRecord *out)
 = {0x303C,0xA6,0xAAAA}; 
pascal void SetTimeBaseTime(TimeBase tb,const TimeRecord *tr)
 = {0x303C,0xA7,0xAAAA}; 
pascal void SetTimeBaseValue(TimeBase tb,TimeValue t,TimeScale s)
 = {0x303C,0xA8,0xAAAA}; 

pascal Fixed GetTimeBaseRate(TimeBase tb)
 = {0x303C,0xA9,0xAAAA}; 
pascal void SetTimeBaseRate(TimeBase tb,Fixed r)
 = {0x303C,0xAA,0xAAAA}; 

pascal TimeValue GetTimeBaseStartTime(TimeBase tb,TimeScale s,TimeRecord *out)
 = {0x303C,0xAB,0xAAAA}; 
pascal void SetTimeBaseStartTime(TimeBase tb,const TimeRecord *tr)
 = {0x303C,0xAC,0xAAAA}; 
pascal TimeValue GetTimeBaseStopTime(TimeBase tb,TimeScale s,TimeRecord *out)
 = {0x303C,0xAD,0xAAAA}; 
pascal void SetTimeBaseStopTime(TimeBase tb,const TimeRecord *tr)
 = {0x303C,0xAE,0xAAAA}; 

pascal long GetTimeBaseFlags(TimeBase tb)
 = {0x303C,0xB1,0xAAAA}; 
pascal void SetTimeBaseFlags(TimeBase tb,long timeBaseFlags)
 = {0x303C,0xB2,0xAAAA}; 

pascal void SetTimeBaseMasterTimeBase(TimeBase slave,TimeBase master,const TimeRecord *slaveZero)
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

pascal void SetTimeBaseZero(TimeBase tb,TimeRecord *zero)
 = {0x303C,0x128,0xAAAA}; 

/*  CallBack Routines  */
pascal QTCallBack NewCallBack(TimeBase tb,short cbType)
 = {0x303C,0xEB,0xAAAA}; 

pascal void DisposeCallBack(QTCallBack qtCall)
 = {0x303C,0xEC,0xAAAA}; 

pascal short GetCallBackType(QTCallBack qtCall)
 = {0x303C,0xED,0xAAAA}; 
pascal TimeBase GetCallBackTimeBase(QTCallBack qtCall)
 = {0x303C,0xEE,0xAAAA}; 

pascal OSErr CallMeWhen(QTCallBack qtCall,QTCallBackProc callBackProc,long refCon,
 long param1,long param2,long param3)
 = {0x303C,0xB8,0xAAAA}; 

pascal void CancelCallBack(QTCallBack cb)
 = {0x303C,0xB9,0xAAAA}; 

/*  Clock CallBack support Routines  */
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
#endif



/* Movie Controller Routines */

#define MovieControllerComponentType 'play'

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
	mcActionBadgeClick = 44					// no param
};
typedef unsigned short mcAction;

enum {mcFlagSuppressMovieFrame = 1<<0,mcFlagSuppressStepButtons = 1<<1,
 mcFlagSuppressSpeakerButton = 1<<2,mcFlagsUseWindowPalette = 1<<3};


typedef pascal Boolean (*MCActionFilter)(MovieController mc,short *action,long param);

enum {mcTopLeftMovie = 1<<0,mcScaleMovieToFit = 1<<1,mcWithBadge = 1<<2,
 mcNotVisible = 1<<3,mcWithFrame = 1<<4};
typedef unsigned char mcCreationFlagsEnum;

enum {mcInfoUndoAvailable = 1<<0,mcInfoCutAvailable = 1<<1,mcInfoCopyAvailable = 1<<2,
 mcInfoPasteAvailable = 1<<3,mcInfoClearAvailable = 1<<4,mcInfoHasSound = 1<<5,
 mcInfoIsPlaying = 1<<6,mcInfoIsLooping = 1<<7,mcInfoIsInPalindrome = 1<<8,
 mcInfoEditingEnabled = 1<<9};
typedef unsigned short mcInfoFlagsEnum;


#ifdef __cplusplus
extern "C" {
#endif
/*  target management  */
pascal MovieController NewMovieController(Movie m,const Rect *movieRect,
 long controllerCreationFlags)
 = {0x303C,0x18A,0xAAAA}; 
pascal void DisposeMovieController(MovieController mc)
 = {0x303C,0x18B,0xAAAA}; 

pascal ComponentResult MCSetMovie(MovieController mc,Movie m,WindowPtr movieWindow,
 Point where)
 = {0x2F3C,0xC,0x2,0x7000,0xA82A}; 
pascal Movie MCGetMovie(MovieController mc)
 = {0x4267,0x2F3C,0x2,0x5,0x7000,0xA82A}; 
pascal ComponentResult MCRemoveMovie(MovieController mc)
 = {0x2F3C,0x0,0x6,0x7000,0xA82A}; 

/*  event handling etc.  */
pascal ComponentResult MCIsPlayerEvent(MovieController mc,const EventRecord *e)
 = {0x2F3C,0x4,0x7,0x7000,0xA82A}; 
pascal ComponentResult MCSetActionFilter(MovieController mc,MCActionFilter filter)
 = {0x2F3C,0x4,0x8,0x7000,0xA82A}; 
pascal ComponentResult MCDoAction(MovieController mc,short action,void *params)
 = {0x2F3C,0x6,0x9,0x7000,0xA82A}; 

/*  state type things  */
pascal ComponentResult MCSetControllerAttached(MovieController mc,Boolean attach)
 = {0x2F3C,0x2,0xA,0x7000,0xA82A}; 
pascal ComponentResult MCIsControllerAttached(MovieController mc)
 = {0x2F3C,0x0,0xB,0x7000,0xA82A}; 
pascal ComponentResult MCSetControllerPort(MovieController mc,CGrafPtr gp)
 = {0x2F3C,0x4,0xC,0x7000,0xA82A}; 
pascal CGrafPtr MCGetControllerPort(MovieController mc)
 = {0x2F3C,0x0,0xD,0x7000,0xA82A}; 

pascal ComponentResult MCSetVisible(MovieController mc,Boolean show)
 = {0x2F3C,0x2,0xE,0x7000,0xA82A}; 
pascal ComponentResult MCGetVisible(MovieController mc)
 = {0x2F3C,0x0,0xF,0x7000,0xA82A}; 

pascal ComponentResult MCGetControllerBoundsRect(MovieController mc,Rect *bounds)
 = {0x2F3C,0x4,0x10,0x7000,0xA82A}; 
pascal ComponentResult MCSetControllerBoundsRect(MovieController mc,const Rect *bounds)
 = {0x2F3C,0x4,0x11,0x7000,0xA82A}; 
pascal RgnHandle MCGetControllerBoundsRgn(MovieController mc)
 = {0x2F3C,0x0,0x12,0x7000,0xA82A}; 
pascal RgnHandle MCGetWindowRgn(MovieController mc,WindowPtr w)
 = {0x2F3C,0x4,0x13,0x7000,0xA82A}; 

/*  other stuff  */
pascal ComponentResult MCMovieChanged(MovieController mc,Movie m)
 = {0x2F3C,0x4,0x14,0x7000,0xA82A}; 
pascal ComponentResult MCSetDuration(MovieController mc,TimeValue duration)
 = {0x2F3C,0x4,0x15,0x7000,0xA82A}; 
pascal TimeValue MCGetCurrentTime(MovieController mc,TimeScale *scale)
 = {0x2F3C,0x4,0x16,0x7000,0xA82A}; 
pascal ComponentResult MCNewAttachedController(MovieController mc,Movie m,
 WindowPtr w,Point where)
 = {0x2F3C,0xC,0x17,0x7000,0xA82A}; 
pascal ComponentResult MCPositionController(MovieController mc,Rect *movieRect,
 Rect *controllerRect,long controllerCreationFlags)
 = {0x2F3C,0xC,0x24,0x7000,0xA82A}; 

/*  direct event handlers  */
pascal ComponentResult MCDraw(MovieController mc,WindowPtr w)
 = {0x2F3C,0x4,0x18,0x7000,0xA82A}; 
pascal ComponentResult MCActivate(MovieController mc,WindowPtr w,Boolean activate)
 = {0x2F3C,0x6,0x19,0x7000,0xA82A}; 
pascal ComponentResult MCIdle(MovieController mc)
 = {0x2F3C,0x0,0x1A,0x7000,0xA82A}; 
pascal ComponentResult MCKey(MovieController mc,char key,long modifiers)
 = {0x2F3C,0x6,0x1B,0x7000,0xA82A}; 
pascal ComponentResult MCClick(MovieController mc,WindowPtr w,Point where,
 long when,long modifiers)
 = {0x2F3C,0x10,0x1C,0x7000,0xA82A}; 

/*   calls for editing  */
pascal ComponentResult MCEnableEditing(MovieController mc,Boolean enabled)
 = {0x2F3C,0x2,0x1D,0x7000,0xA82A}; 
pascal long MCIsEditingEnabled(MovieController mc)
 = {0x2F3C,0x0,0x1E,0x7000,0xA82A}; 
pascal Movie MCCopy(MovieController mc)
 = {0x2F3C,0x0,0x1F,0x7000,0xA82A}; 
pascal Movie MCCut(MovieController mc)
 = {0x2F3C,0x0,0x20,0x7000,0xA82A}; 
pascal ComponentResult MCPaste(MovieController mc,Movie srcMovie)
 = {0x2F3C,0x4,0x21,0x7000,0xA82A}; 
pascal ComponentResult MCClear(MovieController mc)
 = {0x2F3C,0x0,0x22,0x7000,0xA82A}; 
pascal ComponentResult MCUndo(MovieController mc)
 = {0x2F3C,0x0,0x23,0x7000,0xA82A}; 

/*  menu related stuff  */
pascal ComponentResult MCGetControllerInfo(MovieController mc,long *mcInfoFlags)
 = {0x2F3C,0x4,0x25,0x7000,0xA82A}; 

pascal ComponentResult MCSetClip(MovieController mc, RgnHandle theClip, RgnHandle movieClip)
= {0x2F3C,8,40,0x7000,0xA82A};
pascal ComponentResult MCGetClip(MovieController mc, RgnHandle *theClip, RgnHandle *movieClip)
= {0x2F3C,8,41,0x7000,0xA82A};

pascal ComponentResult MCDrawBadge(MovieController mc, RgnHandle movieRgn, RgnHandle *badgeRgn)
= {0x2F3C,8,42,0x7000,0xA82A};

#ifdef __cplusplus
}
#endif
enum {


/* movie controller error codes */
 cannotMoveAttachedController = -9999,
 controllerHasFixedHeight = -9998,
 cannotSetWidthOfAttachedController = -9997,
 controllerBoundsNotExact = -9996,
 editingNotAllowed = -9995,
 badControllerHeight = -9994
};

enum {
	kMCSetMovieSelect = 2,
	kMCRemoveMovieSelect = 3,
	kMCIsPlayerEventSelect = 7,
	kMCSetActionFilterSelect = 8,
	kMCDoActionSelect = 9,
	kMCSetControllerAttachedSelect = 10,
	kMCIsControllerAttachedSelect = 11,
	kMCSetControllerPortSelect = 12,
	kMCGetControllerPortSelect = 13,
	kMCGetVisibleSelect = 14,
	kMCSetVisibleSelect = 15,
	kMCGetControllerBoundsRectSelect = 16,
	kMCSetControllerBoundsRectSelect = 17,
	kMCGetControllerBoundsRgnSelect = 18,
	kMCGetWindowRgnSelect = 19,
	kMCMovieChangedSelect = 20,
	kMCSetDurationSelect = 21,
	kMCGetCurrentTimeSelect = 22,
	kMCNewAttachedControllerSelect = 23,
	kMCDrawSelect = 24,
	kMCActivateSelect = 25,
	kMCIdleSelect = 26,
	kMCKeySelect = 27,
	kMCClickSelect = 28,
	kMCEnableEditingSelect = 29,
	kMCIsEditingEnabledSelect = 30,
	kMCCopySelect = 31,
	kMCCutSelect = 32,
	kMCPasteSelect = 33,
	kMCClearSelect = 34,
	kMCUndoSelect = 35,
	kMCPositionControllerSelect = 36,
	kMCGetControllerInfoSelect = 37,
	kMCNewControllerFromFileSelect = 38,
	kMCSetBadgePictSelect = 39,
	kMCSetClipSelect = 40,
	kMCGetClipSelect = 41,
	kMCDrawBadgeSelect = 42
};

#endif
