
/************************************************************

Created: Tuesday, August 13, 1991 at 4:25 PM
 ImageCompression.h
 C Interface to the Macintosh Libraries


 Copyright Apple Computer, Inc. 1991
 All rights reserved

************************************************************/


#ifndef __IMAGECOMPRESSION__
#define __IMAGECOMPRESSION__

#ifndef __QUICKDRAW__
#include <QuickDraw.h>
#endif

#ifndef __QDOFFSCREEN__
#include <QDOffscreen.h>
#endif

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __COMPONENTS__
#include <Components.h>
#endif

#ifndef __STANDARDFILE__
#include <StandardFile.h>
#endif


enum {


#define gestaltCompressionMgr 'icmp'

/* These are the bits that are set in the Component flags, and also in the codecInfo struct. */

#define codecInfoDoes1 (1L<<0)						/* codec can work with 1-bit pixels */
#define codecInfoDoes2 (1L<<1)						/* codec can work with 2-bit pixels */
#define codecInfoDoes4 (1L<<2)						/* codec can work with 4-bit pixels */
#define codecInfoDoes8 (1L<<3)						/* codec can work with 8-bit pixels */
#define codecInfoDoes16 (1L<<4)						/* codec can work with 16-bit pixels */
#define codecInfoDoes32 (1L<<5)						/* codec can work with 32-bit pixels */
#define codecInfoDoesDither (1L<<6)					/* codec can do ditherMode */
#define codecInfoDoesStretch (1L<<7)				/* codec can stretch to arbitrary sizes */
#define codecInfoDoesShrink (1L<<8)					/* codec can shrink to arbitrary sizes */
#define codecInfoDoesMask (1L<<9)					/* codec can mask to clipping regions */

#define codecInfoDoesTemporal (1L<<10)				/* codec can handle temporal redundancy */

#define codecInfoDoesDouble (1L<<11)				/* codec can stretch to double size exactly */
#define codecInfoDoesQuad (1L<<12)					/* codec can stretch to quadruple size exactly */
#define codecInfoDoesHalf (1L<<13)					/* codec can shrink to half size */
#define codecInfoDoesQuarter (1L<<14)				/* codec can shrink to quarter size */

#define codecInfoDoesRotate (1L<<15)				/* codec can rotate on decompress */
#define codecInfoDoesHorizFlip (1L<<16)				/* codec can flip horizontally on decompress */
#define codecInfoDoesVertFlip (1L<<17)				/* codec can flip vertically on decompress */
#define codecInfoDoesSkew (1L<<18)					/* codec can skew on decompress */
#define codecInfoDoesBlend (1L<<19)					/* codec can blend on decompress */
#define codecInfoDoesWarp (1L<<20)					/* codec can warp arbitrarily on decompress */
#define codecInfoDoesRecompress (1L<<21)			/* codec can recompress image without accumulating errors */
#define	codecInfoDoesSpool			(1L<<22)	/* codec can spool image data */

#define codecInfoDepth1 (1L<<0)						/* compressed data at 1 bpp depth available */
#define codecInfoDepth2 (1L<<1)						/* compressed data at 2 bpp depth available */
#define codecInfoDepth4 (1L<<2)						/* compressed data at 4 bpp depth available */
#define codecInfoDepth8 (1L<<3)						/* compressed data at 8 bpp depth available */
#define codecInfoDepth16 (1L<<4)					/* compressed data at 16 bpp depth available */
#define codecInfoDepth32 (1L<<5)					/* compressed data at 32 bpp depth available */
#define codecInfoDepth24 (1L<<6)					/* compressed data at 24 bpp depth available */
#define codecInfoDepth33 (1L<<7)					/* compressed data at 1 bpp monochrome depth  available */
#define codecInfoDepth34 (1L<<8)					/* compressed data at 2 bpp grayscale depth available */
#define codecInfoDepth36 (1L<<9)					/* compressed data at 4 bpp grayscale depth available */
#define codecInfoDepth40 (1L<<10)					/* compressed data at 8 bpp grayscale depth available */
#define codecInfoStoresClut (1L<<11)				/* compressed data can have custom cluts */
#define	codecInfoDoesLossless		(1L<<12)		/* compressed data can be stored in lossless format */

#define codecFlagUseImageBuffer (1L<<0)				/* (input) allocate buffer for whole image on decompress sequence */
#define codecFlagUseScreenBuffer (1L<<1)			/* (input) allocate buffer for screen on decompress sequence for faster updates */
#define codecFlagUpdatePrevious (1L<<2)				/* (input) udate previous buffer on compress sequence */
#define codecFlagNoScreenUpdate (1L<<3)				/* (input) dont update screen, but do update image buffer if allocated */
#define codecFlagWasCompressed (1L<<4)				/* (input) hint to compressor that image was previously compressed */
#define codecFlagDontOffscreen (1L<<5)				/* return error instead of automatically going offscreen */
#define codecFlagUpdatePreviousComp (1L<<6)			/* (input) udate previous buffer on compress sequence */
#define codecFlagForceKeyFrame (1L<<7)				/* when sent to CompressSequenceFrame, forces that frame to be a key frame */
#define	codecFlagOnlyScreenUpdate	(1L<<8)		/* (input) only update screen from */
#define	codecFlagLiveGrab			(1L<<9)		/* (input) data being compressed is from live source (speed is critical) */



#define	codecFlagUsedNewImageBuffer	(1L<<14)	/* (output) indicates that image buffer was first used on this decompress sequence */
#define codecFlagUsedImageBuffer (1L<<15)			/* (output) indicates that image buffer was used on this decompress sequence */

#define codecErr -8960								/* the codec returned an error */
#define noCodecErr -8961							/* the specified codec could not be found */
#define codecUnimpErr -8962							/* this feature is not implemented by the specified codec */
#define codecSizeErr -8963
#define codecScreenBufErr -8964						/* the screen buffer could not be allocated */
#define codecImageBufErr -8965						/* the image buffer could not be allocated */
#define codecSpoolErr -8966							/* the compressed data must be in memory (spooling did not work) */
#define codecAbortErr -8967							/* the operation was aborted by the progress proc */
#define codecWouldOffscreenErr -8968				/* an offscreen access would have been used, but wasn't allowed because codecFlagDontOffscreen was set */
#define codecBadDataErr -8969						/* compressed data was found to have inconsistencies */
#define codecDataVersErr -8970						/* compressed data was of a format version that codec couldn't handle */
#define	codecConditionErr	-8972					/* codec can not do requested operation */
#define	codecOpenErr		-8973					/* the codec  could not be opened */


 codecMinimumDataSize = 32768						/* The minimum data size for spooling in or out data */


#define compressorComponentType 'imco'				/* the type for "Components" which compress images */
#define decompressorComponentType 'imdc'			/* the type for "Components" which decompress images */
};

typedef Component CompressorComponent;				/* a Component which compresses images */
typedef Component DecompressorComponent;			/* a Component which decompresses images */
typedef Component CodecComponent;					/* a Component which decompresses or compresses images */




#define anyCodec ((CodecComponent)0)				/* take first working codec of given type */
#define bestSpeedCodec ((CodecComponent)-1)			/* take fastest codec of given type */
#define bestFidelityCodec ((CodecComponent)-2)		/* take codec which is most accurate*/
#define bestCompressionCodec ((CodecComponent)-3)	/* take codec of given type that is most accurate */


typedef short sBoolean;								/* to make sure stack frames are right */

typedef long CodecType;								/* type descriptor for codecs i.e: 'appl','jpeg','rle ' */

typedef unsigned short CodecFlags;					/* flags for codec manager calls */

typedef unsigned long CodecQ;




#define codecLosslessQuality 0x400L
#define codecMaxQuality 0x3FFL
#define codecMinQuality 0x000L
#define codecLowQuality 0x100L
#define codecNormalQuality 0x200L
#define codecHighQuality 0x300L

typedef pascal OSErr (*DataProcPtr)(Ptr *dataP,long bytesNeeded,long refCon);  
typedef pascal OSErr (*FlushProcPtr)(Ptr data,long bytesAdded,long refCon);




#define codecCompletionSource (1<<0)		/* asynchronous codec is done with source data */
#define codecCompletionDest (1<<1)			/* asynchronous codec is done with destination data */

typedef pascal void (*CompletionProcPtr)(OSErr result,short flags,long refCon);

enum {

 codecProgressOpen = 0,
 codecProgressUpdatePercent = 1,
 codecProgressClose = 2
};

typedef pascal OSErr (*ProgressProcPtr)(short message,Fixed completeness,long refCon);

typedef long ImageSequence;

struct ProgressProcRecord {
 ProgressProcPtr progressProc;
 long progressRefCon;
};

typedef struct ProgressProcRecord ProgressProcRecord;
typedef ProgressProcRecord *ProgressProcRecordPtr;

struct CompletionProcRecord {
 CompletionProcPtr completionProc;
 long completionRefCon;
};

typedef struct CompletionProcRecord CompletionProcRecord;
typedef CompletionProcRecord *CompletionProcRecordPtr;

struct DataProcRecord {
 DataProcPtr dataProc;
 long dataRefCon;
};

typedef struct DataProcRecord DataProcRecord;
typedef DataProcRecord *DataProcRecordPtr;

struct FlushProcRecord {
 FlushProcPtr flushProc;
 long flushRefCon;
};

typedef struct FlushProcRecord FlushProcRecord;
typedef FlushProcRecord *FlushProcRecordPtr;

/* 
    The ImageDescription is private data which is produced when an image or sequence 
    is compressed. It fully describes the format of the compressed data.*/

struct ImageDescription {
 long idSize;										/* total size of ImageDescription including extra data ( CLUTs and other per sequence data */
 CodecType cType;									/* what kind of codec compressed this data */
 long resvd1;										/* reserved for apple use */
 short resvd2;										/* reserved for apple use */
 short dataRefIndex;								/* set to zero */
 short version;										/* which version is this data */
 short revisionLevel;								/* what version of that codec did this */
 long vendor;										/* whose  codec compressed this data */
 CodecQ temporalQuality;							/* what was the temporal quality factor          */
 CodecQ spatialQuality;								/* what was the spatial quality factor          */
 short width;										/* how many pixels wide is this data */
 short height;										/* how many pixels high is this data */
 Fixed hRes;										/* horizontal resolution */
 Fixed vRes;										/* vertical resolution */
 long dataSize;										/* if known, the size of data for this image descriptor */
 short frameCount;									/* number of frames this description applies to */
 char name[32];										/* name of codec ( in case not installed ) */
 short depth;										/* what depth is this data (1-32) or ( 33-40 grayscale ) */
 short clutID;										/* clut id or if 0 clut follows  or -1 if no clut */
};

typedef struct ImageDescription ImageDescription;
typedef ImageDescription *ImageDescriptionPtr, **ImageDescriptionHandle;

/* 
    The CodecInfo is the information returned as the codecInfo struct by a codec Component
    to the codec manager or to the caller. It is specific to the particular codec
    implementation and not to the codec type.*/

struct CodecInfo {
 char typeName[32];									/* name of the codec type i.e.: 'Apple Image Compression' */
 short version;										/* version of the codec data that this codec knows about */
 short revisionLevel;								/* revision level of this codec i.e: 0x00010001 (1.0.1) */
 long vendor;										/* Maker of this codec i.e: 'appl' */
 long decompressFlags;								/* codecInfo flags for decompression capabilities */
 long compressFlags;								/* codecInfo flags for compression capabilities */
 long formatFlags;									/* codecInfo flags for compression format details */
 unsigned char compressionAccuracy;					/* measure (1-255) of accuracy of this codec for compress (0 if unknown) */
 unsigned char decompressionAccuracy;				/* measure (1-255) of accuracy of this codec for decompress (0 if unknown) */
 unsigned short compressionSpeed;					/* ( millisecs for compressing 320x240 on base mac II) (0 if unknown) */
 unsigned short decompressionSpeed;					/* ( millisecs for decompressing 320x240 on mac II)(0 if unknown) */
 unsigned char compressionLevel;					/* measure (1-255) of compression level of this codec (0 if unknown) */
 char resvd;										/* pad */
 short minimumHeight;								/* minimum height of image (block size) */
 short minimumWidth;								/* minimum width of image (block size) */
 short decompressPipelineLatency;					/* in milliseconds ( for asynchronous codecs ) */
 short compressPipelineLatency;						/* in milliseconds ( for asynchronous codecs ) */
 long privateData;
};

typedef struct CodecInfo CodecInfo;

/* Table used for fast dithering. */
struct DitherTable {
 long tag;
 long seed;
 long reserved;
 char data[1];
};

typedef struct DitherTable DitherTable;
typedef DitherTable *DTabPtr, **DTabHandle;

/* Name list returned by GetCodecNameList. */
struct CodecNameSpec {
 CodecComponent codec;
 CodecType cType;
 char typeName[32];
 Handle name;
};

typedef struct CodecNameSpec CodecNameSpec;

struct CodecNameSpecList {
 short count;
 CodecNameSpec list[1];
};

typedef struct CodecNameSpecList CodecNameSpecList;
typedef CodecNameSpecList *CodecNameSpecListPtr;

/*  Matrix stuff  */
struct MatrixRecord {
 Fixed matrix[3][3];
};

typedef struct MatrixRecord  MatrixRecord;
typedef MatrixRecord  *MatrixRecordPtr;

#ifndef _FixedPoint_
#define _FixedPoint_
struct FixedPoint {
 Fixed x;
 Fixed y;
};

typedef struct FixedPoint FixedPoint;
#endif _FixedPoint_

#ifndef _FixedRect_
#define _FixedRect_
struct FixedRect {
 Fixed left;
 Fixed top;
 Fixed right;
 Fixed bottom;
};

typedef struct FixedRect FixedRect;
#endif _FixedRect_


#ifdef __cplusplus
extern "C" {
#endif
pascal OSErr CodecManagerVersion(long *version)
 = {0x7000,0xAAA3}; 
pascal OSErr GetCodecNameList(CodecNameSpecListPtr *list,sBoolean showAll)
 = {0x7001,0xAAA3};
pascal OSErr DisposeCodecNameList(CodecNameSpecListPtr list)
	= {0x700F,0xAAA3};
pascal OSErr GetCodecInfo(CodecInfo *info,CodecType cType,CodecComponent codec)
 = {0x7003,0xAAA3}; 
pascal OSErr GetMaxCompressionSize(PixMapHandle src,const Rect *srcRect,short colorDepth,
 CodecQ quality,CodecType cType,CompressorComponent codec,long *size)
 = {0x7004,0xAAA3}; 
pascal OSErr GetCompressionTime(PixMapHandle src,const Rect *srcRect,short colorDepth,
 CodecType cType,CompressorComponent codec,CodecQ *spatialQuality,CodecQ *temporalQuality,
 unsigned long *compressTime)
 = {0x7005,0xAAA3}; 
pascal OSErr CompressImage(PixMapHandle src,const  Rect *srcRect,CodecQ quality,
 CodecType cType,ImageDescriptionHandle desc,Ptr data)
 = {0x7006,0xAAA3}; 
pascal OSErr FCompressImage(PixMapHandle src,const  Rect *srcRect,short colorDepth,
 CodecQ quality,CodecType cType,CompressorComponent codec,CTabHandle clut,
 CodecFlags flags,long bufferSize,FlushProcRecordPtr flushProc,ProgressProcRecordPtr progressProc,
 ImageDescriptionHandle desc,Ptr data)
 = {0x7007,0xAAA3}; 
pascal OSErr DecompressImage(Ptr data,ImageDescriptionHandle desc,PixMapHandle dst,
 const Rect *srcRect,const  Rect *dstRect,short mode,RgnHandle mask)
 = {0x7008,0xAAA3}; 
pascal OSErr FDecompressImage(Ptr data,ImageDescriptionHandle desc,PixMapHandle dst,
 const  Rect *srcRect,MatrixRecordPtr matrix,short mode,RgnHandle mask,PixMapHandle matte,
 const  Rect *matteRect,CodecQ accuracy,DecompressorComponent codec,long bufferSize,
 DataProcRecordPtr dataProc,ProgressProcRecordPtr progressProc)
 = {0x7009,0xAAA3}; 
pascal OSErr CompressSequenceBegin(ImageSequence *seqID,PixMapHandle src,
 PixMapHandle prev,const Rect *srcRect,const  Rect *prevRect,short colorDepth,CodecType cType,
 CompressorComponent codec,CodecQ spatialQuality,CodecQ temporalQuality,
 long keyFrameRate,CTabHandle clut,CodecFlags flags,ImageDescriptionHandle desc)
 = {0x700A,0xAAA3}; 
pascal OSErr CompressSequenceFrame(ImageSequence seqID,PixMapHandle src,
 const Rect *srcRect,CodecFlags flags,Ptr data,long *dataSize,unsigned char *similarity,
 CompletionProcRecordPtr asyncCompletionProc)
 = {0x700B,0xAAA3}; 
pascal OSErr DecompressSequenceBegin(ImageSequence *seqID,ImageDescriptionHandle desc,
 CGrafPtr port,GDHandle gdh,const Rect *srcRect,MatrixRecordPtr matrix,short mode,
 RgnHandle mask,CodecFlags flags,CodecQ accuracy,DecompressorComponent codec)
 = {0x700D,0xAAA3}; 
pascal OSErr DecompressSequenceFrame(ImageSequence seqID,Ptr data,CodecFlags inFlags,
 CodecFlags *outFlags,CompletionProcRecordPtr asyncCompletionProc)
 = {0x700E,0xAAA3}; 
pascal OSErr SetDSequenceMatrix(ImageSequence seqID,MatrixRecordPtr matrix)
 = {0x7010,0xAAA3}; 
pascal OSErr SetDSequenceMatte(ImageSequence seqID,PixMapHandle matte,const Rect *matteRect)
 = {0x7011,0xAAA3}; 
pascal OSErr SetDSequenceMask(ImageSequence seqID,RgnHandle mask)
 = {0x7012,0xAAA3}; 
pascal OSErr SetDSequenceTransferMode(ImageSequence seqID,short mode,const RGBColor *opColor)
 = {0x7013,0xAAA3}; 
pascal OSErr SetDSequenceDataProc(ImageSequence seqID,DataProcRecordPtr dataProc,
 long bufferSize)
 = {0x7014,0xAAA3}; 
pascal OSErr SetDSequenceAccuracy(ImageSequence seqID,CodecQ accuracy)
 = {0x7034,0xAAA3}; 
pascal OSErr SetDSequenceSrcRect(ImageSequence seqID,const Rect *srcRect)
 = {0x7035,0xAAA3}; 
pascal OSErr GetDSequenceImageBuffer(ImageSequence seqID,GWorldPtr *gworld)
 = {0x7015,0xAAA3}; 
pascal OSErr GetDSequenceScreenBuffer(ImageSequence seqID,GWorldPtr *gworld)
 = {0x7016,0xAAA3}; 
pascal OSErr SetCSequenceQuality(ImageSequence seqID,CodecQ spatialQuality,
 CodecQ temporalQuality)
 = {0x7017,0xAAA3}; 
pascal OSErr SetCSequencePrev(ImageSequence seqID,PixMapHandle prev,const Rect *prevRect)
 = {0x7018,0xAAA3}; 
pascal OSErr SetCSequenceFlushProc(ImageSequence seqID,FlushProcRecordPtr flushProc,
 long bufferSize)
 = {0x7033,0xAAA3}; 
pascal OSErr SetCSequenceKeyFrameRate(ImageSequence seqID,long keyframerate)
 = {0x7036,0xAAA3}; 
pascal OSErr GetCSequencePrevBuffer(ImageSequence seqID,GWorldPtr *gworld)
 = {0x7019,0xAAA3}; 
pascal OSErr CDSequenceBusy(ImageSequence seqID)
 = {0x701A,0xAAA3}; 
pascal OSErr CDSequenceEnd(ImageSequence seqID)
 = {0x701B,0xAAA3}; 
pascal OSErr GetCompressedImageSize(ImageDescriptionHandle desc,Ptr data,
 long bufferSize,DataProcRecordPtr dataProc,long *dataSize)
 = {0x701C,0xAAA3}; 
pascal OSErr GetSimilarity(PixMapHandle src,const Rect *srcRect,ImageDescriptionHandle desc,
 Ptr data,Fixed *similarity)
 = {0x701D,0xAAA3}; 
pascal OSErr GetImageDescriptionCTable(ImageDescriptionHandle desc,CTabHandle *ctable)
 = {0x701E,0xAAA3}; 
pascal OSErr SetImageDescriptionCTable(ImageDescriptionHandle desc,CTabHandle ctable)
 = {0x701F,0xAAA3}; 
pascal OSErr GetImageDescriptionExtension(ImageDescriptionHandle desc,Handle *extension,
 long idType,long index)
 = {0x7020,0xAAA3}; 
pascal OSErr SetImageDescriptionExtension(ImageDescriptionHandle desc,Handle extension,
 long idType)
 = {0x7021,0xAAA3}; 
pascal OSErr FindCodec(CodecType cType,CodecComponent specCodec,CompressorComponent *compressor,
 DecompressorComponent *decompressor)
 = {0x7023,0xAAA3}; 
pascal OSErr CompressPicture(PicHandle srcPicture,PicHandle dstPicture,
 CodecQ quality,CodecType cType)
 = {0x7024,0xAAA3}; 
pascal OSErr FCompressPicture(PicHandle srcPicture,PicHandle dstPicture,
 short colorDepth,CTabHandle clut,CodecQ quality,sBoolean doDither,sBoolean compressAgain,
 ProgressProcRecordPtr progressProc,CodecType cType,CompressorComponent codec)
 = {0x7025,0xAAA3}; 
pascal OSErr CompressPictureFile(short srcRefNum,short dstRefNum,CodecQ quality,
 CodecType cType)
 = {0x7026,0xAAA3}; 
pascal OSErr FCompressPictureFile(short srcRefNum,short dstRefNum,short colorDepth,
 CTabHandle clut,CodecQ quality,sBoolean doDither,sBoolean compressAgain,
 ProgressProcRecordPtr progressProc,CodecType cType,CompressorComponent codec)
 = {0x7027,0xAAA3}; 
pascal OSErr GetPictureFileHeader(short refNum,Rect *frame,OpenCPicParams *header)
 = {0x7028,0xAAA3}; 
pascal OSErr DrawPictureFile(short refNum,const Rect *frame,ProgressProcRecordPtr progressProc)
 = {0x7029,0xAAA3}; 
pascal OSErr DrawTrimmedPicture(PicHandle srcPicture,const Rect *frame,RgnHandle trimMask,
 sBoolean doDither,ProgressProcRecordPtr progressProc)
 = {0x702E,0xAAA3}; 
pascal OSErr DrawTrimmedPictureFile(short srcRefnum,const Rect *frame,RgnHandle trimMask,
 sBoolean doDither,ProgressProcRecordPtr progressProc)
 = {0x702F,0xAAA3}; 
pascal OSErr MakeThumbnailFromPicture(PicHandle picture,short colorDepth,
 PicHandle thumbnail,ProgressProcRecordPtr progressProc)
 = {0x702A,0xAAA3}; 
pascal OSErr MakeThumbnailFromPictureFile(short refNum,short colorDepth,
 PicHandle thumbnail,ProgressProcRecordPtr progressProc)
 = {0x702B,0xAAA3}; 
pascal OSErr MakeThumbnailFromPixMap(PixMapHandle src,const Rect *srcRect,short colorDepth,
 PicHandle thumbnail,ProgressProcRecordPtr progressProc)
 = {0x702C,0xAAA3}; 
pascal OSErr TrimImage(ImageDescriptionHandle desc,Ptr inData,long inBufferSize,
 DataProcRecordPtr dataProc,Ptr outData,long outBufferSize,FlushProcRecordPtr flushProc,
 Rect *trimRect,ProgressProcRecordPtr progressProc)
 = {0x702D,0xAAA3}; 
pascal OSErr ConvertImage(ImageDescriptionHandle srcDD,Ptr srcData,short colorDepth,
 CTabHandle clut,CodecQ accuracy,CodecQ quality,CodecType cType,CodecComponent codec,
 ImageDescriptionHandle dstDD,Ptr dstData)
 = {0x7030,0xAAA3}; 
pascal OSErr MakeDitherTable(GDHandle gdev,DTabHandle *ditherTable)
 = {0x7031,0xAAA3}; 
pascal OSErr DisposeDitherTable(DTabHandle ditherTable)
 = {0x7032,0xAAA3}; 
 

pascal void 
StdPix(PixMapPtr src,const  Rect *srcRect,MatrixRecordPtr matrix,short mode,
	RgnHandle mask,PixMapPtr matte,const Rect *matteRect,short flags)
	 = {0x700C,0xAAA3};

pascal OSErr GetCompressedPixMapInfo(PixMapPtr pix,ImageDescriptionHandle *desc,
 Ptr *data,long *bufferSize,DataProcRecord *dataProc,ProgressProcRecord *progressProc)
 = {0x7037,0xAAA3}; 
pascal OSErr SetCompressedPixMapInfo(PixMapPtr pix,ImageDescriptionHandle desc,
 Ptr data,long bufferSize,DataProcRecordPtr dataProc,ProgressProcRecordPtr progressProc)
 = {0x7038,0xAAA3}; 
pascal OSErr TransformRgn(MatrixRecordPtr mp,RgnHandle r)
 = {0x7039,0xAAA3};
#ifdef __cplusplus
}
#endif
enum {
 identityMatrixType			= 0x00, 						/* result if matrix is identity */
 translateMatrixType		= 0x01, 						/* result if matrix translates */
 scaleMatrixType			= 0x02, 						/* result if matrix scales */
 scaleTranslateMatrixType	= 0x03, 						/* result if matrix scales and translates */
 linearMatrixType			= 0x04, 						/* result if matrix is general 2 x 2 */
 linearTranslateMatrixType	= 0x05, 						/* result if matrix is general 2 x 2 and translates */
 perspectiveMatrixType		= 0x06 							/* result if matrix is general 3 x 3 */
};
typedef unsigned char MatrixFlags;


#ifdef __cplusplus
extern "C" {
#endif
pascal short GetMatrixType(MatrixRecordPtr m)
 = {0x7014,0xABC2}; 
pascal void CopyMatrix(MatrixRecordPtr m1,MatrixRecord *m2)
 = {0x7020,0xABC2}; 
pascal Boolean EqualMatrix(MatrixRecordPtr m1,MatrixRecordPtr m2)
 = {0x7021,0xABC2}; 
pascal void SetIdentityMatrix(MatrixRecord *matrix)
 = {0x7015,0xABC2}; 
pascal void TranslateMatrix(MatrixRecord *m,Fixed deltaH,Fixed deltaV)
 = {0x7019,0xABC2}; 
pascal void RotateMatrix(MatrixRecord *m,Fixed degrees,Fixed aboutX,Fixed aboutY)
 = {0x7016,0xABC2}; 
pascal void ScaleMatrix(MatrixRecord *m,Fixed scaleX,Fixed scaleY,Fixed aboutX,
 Fixed aboutY)
 = {0x7017,0xABC2}; 
pascal void SkewMatrix(MatrixRecord *m,Fixed skewX,Fixed skewY,Fixed aboutX,
 Fixed aboutY)
 = {0x7018,0xABC2}; 
pascal OSErr TransformFixedPoints(MatrixRecordPtr m,FixedPoint *fpt,long count)
 = {0x7022,0xABC2}; 
pascal OSErr TransformPoints(MatrixRecordPtr mp,Point *pt1,long count)
 = {0x7023,0xABC2}; 
pascal Boolean TransformFixedRect(MatrixRecordPtr m,FixedRect *fr,FixedPoint *fpp)
 = {0x7024,0xABC2}; 
pascal Boolean TransformRect(MatrixRecordPtr m,Rect *r,FixedPoint *fpp)
 = {0x7025,0xABC2}; 
pascal Boolean InverseMatrix(MatrixRecordPtr m,MatrixRecord *im)
 = {0x701C,0xABC2}; 
pascal void ConcatMatrix(MatrixRecordPtr a,MatrixRecord *b)
 = {0x701B,0xABC2}; 
pascal void RectMatrix(MatrixRecord *matrix,Rect *srcRect,Rect *dstRect)
 = {0x701E,0xABC2}; 
pascal void MapMatrix(MatrixRecord *matrix,Rect *fromRect,Rect *toRect)
 = {0x701D,0xABC2}; 
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*  Standard Preview */

pascal void SFGetFilePreview(Point where,
                      ConstStr255Param prompt,
                      FileFilterProcPtr fileFilter,
                      short numTypes,
                      SFTypeList typeList,
                      DlgHookProcPtr dlgHook,
                      SFReply *reply)
 = {0x303C,65,0xAAA3}; 

pascal void SFPGetFilePreview(Point where,
                       ConstStr255Param prompt,
                       FileFilterProcPtr fileFilter,
                       short numTypes,
                       SFTypeList typeList,
                       DlgHookProcPtr dlgHook,
                       SFReply *reply,
                       short dlgID,
                       ModalFilterProcPtr filterProc)
 = {0x303C,66,0xAAA3}; 

pascal void StandardGetFilePreview(FileFilterProcPtr fileFilter,
                            short numTypes,
                            SFTypeList typeList,
                            StandardFileReply *reply)
 = {0x303C,67,0xAAA3}; 

pascal void CustomGetFilePreview(FileFilterYDProcPtr fileFilter,
                          short numTypes,
                          SFTypeList typeList,
                          StandardFileReply *reply,
                          short dlgID,
                          Point where,
                          DlgHookYDProcPtr dlgHook,
                          ModalFilterYDProcPtr filterProc,
                          short *activeList,
                          ActivateYDProcPtr activateProc,
                          void *yourDataPtr)
 = {0x303C,68,0xAAA3}; 

pascal OSErr MakeFilePreview(short resRefNum, ProgressProcRecordPtr progress)
 = {0x303C,69,0xAAA3}; 

pascal OSErr AddFilePreview(short resRefNum, OSType previewType, Handle previewData)
 = {0x303C,70,0xAAA3}; 

#ifdef __cplusplus
}
#endif

enum {
    sfpItemPreviewAreaUser = 11,
    sfpItemPreviewStaticText = 12,
    sfpItemPreviewDividerUser = 13,
    sfpItemCreatePreviewButton = 14,
    sfpItemShowPreviewButton = 15
};

struct PreviewResourceRecord {
	unsigned long	modDate;
	short			version;
	OSType			resType;
	short			resID;
};

typedef struct PreviewResourceRecord PreviewResourceRecord;
typedef PreviewResourceRecord *PreviewResourcePtr, **PreviewResource;

#endif
