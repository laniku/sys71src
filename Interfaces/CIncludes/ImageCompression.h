/*
	File:		ImageCompression.h

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 10/8/92	DH		first checked in

*/

/************************************************************

Created: Friday, October 2, 1992 at 11:39 AM
 ImageCompression.h
 C Interface to the Macintosh Libraries

 Copyright Apple Computer, Inc. 1991, 1992
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


#define gestaltCompressionMgr 'icmp'


struct MatrixRecord {
	Fixed matrix[3][3];
};

typedef struct MatrixRecord MatrixRecord;
typedef MatrixRecord *MatrixRecordPtr;

typedef struct FixedPoint {
	Fixed x;
	Fixed y;
} FixedPoint;

typedef struct FixedRect {
	Fixed left;
	Fixed top;
	Fixed right;
	Fixed bottom;
} FixedRect;


#define	codecInfoDoes1				(1L<<0)
#define	codecInfoDoes2				(1L<<1)
#define	codecInfoDoes4				(1L<<2)
#define	codecInfoDoes8				(1L<<3)
#define	codecInfoDoes16				(1L<<4)
#define	codecInfoDoes32				(1L<<5)
#define	codecInfoDoesDither			(1L<<6)
#define	codecInfoDoesStretch		(1L<<7)
#define	codecInfoDoesShrink			(1L<<8)
#define	codecInfoDoesMask			(1L<<9)

#define	codecInfoDoesTemporal		(1L<<10)

#define	codecInfoDoesDouble			(1L<<11)
#define	codecInfoDoesQuad			(1L<<12)
#define	codecInfoDoesHalf			(1L<<13)
#define	codecInfoDoesQuarter		(1L<<14)

#define	codecInfoDoesRotate			(1L<<15)
#define	codecInfoDoesHorizFlip		(1L<<16)
#define	codecInfoDoesVertFlip		(1L<<17)
#define	codecInfoDoesSkew			(1L<<18)
#define	codecInfoDoesBlend			(1L<<19)
#define	codecInfoDoesWarp			(1L<<20)
#define	codecInfoDoesRecompress		(1L<<21)
#define	codecInfoDoesSpool			(1L<<22)
#define	codecInfoDoesRateConstrain	(1L<<23)

#define	codecInfoDepth1				(1L<<0)
#define	codecInfoDepth2				(1L<<1)
#define	codecInfoDepth4				(1L<<2)
#define	codecInfoDepth8				(1L<<3)
#define	codecInfoDepth16			(1L<<4)
#define	codecInfoDepth32			(1L<<5)
#define	codecInfoDepth24			(1L<<6)
#define	codecInfoDepth33			(1L<<7)
#define	codecInfoDepth34			(1L<<8)
#define	codecInfoDepth36			(1L<<9)
#define	codecInfoDepth40			(1L<<10)
#define	codecInfoStoresClut			(1L<<11)
#define	codecInfoDoesLossless		(1L<<12)
#define	codecInfoSequenceSensitive	(1L<<13)

#define	codecFlagUseImageBuffer		(1L<<0)
#define	codecFlagUseScreenBuffer	(1L<<1)
#define	codecFlagUpdatePrevious		(1L<<2)
#define	codecFlagNoScreenUpdate		(1L<<3)
#define	codecFlagWasCompressed		(1L<<4)
#define	codecFlagDontOffscreen		(1L<<5)
#define	codecFlagUpdatePreviousComp	(1L<<6)
#define	codecFlagForceKeyFrame		(1L<<7)
#define	codecFlagOnlyScreenUpdate	(1L<<8)
#define	codecFlagLiveGrab			(1L<<9)
#define	codecFlagDontUseNewImageBuffer (1L<<10)
#define	codecFlagInterlaceUpdate	 (1L<<11)


#define	codecFlagUsedNewImageBuffer	(1L<<14)
#define	codecFlagUsedImageBuffer	(1L<<15)

#define	codecErr					-8960
#define	noCodecErr					-8961
#define	codecUnimpErr				-8962
#define	codecSizeErr				-8963
#define	codecScreenBufErr			-8964
#define	codecImageBufErr			-8965
#define	codecSpoolErr				-8966
#define	codecAbortErr				-8967
#define	codecWouldOffscreenErr		-8968
#define	codecBadDataErr				-8969
#define	codecDataVersErr			-8970
#define	codecExtensionNotFoundErr	-8971
#define	codecConditionErr			-8972
#define	codecOpenErr				-8973
#define	codecMinimumDataSize		32768

#define	compressorComponentType			'imco'
#define	decompressorComponentType		'imdc'

typedef	Component		CompressorComponent;
typedef	Component		DecompressorComponent;
typedef	Component		CodecComponent;

#define	anyCodec				((CodecComponent)0)
#define	bestSpeedCodec			((CodecComponent)-1)
#define	bestFidelityCodec		((CodecComponent)-2)
#define	bestCompressionCodec	((CodecComponent)-3)

typedef	long		CodecType;

typedef	unsigned short	CodecFlags;

typedef	unsigned long	CodecQ;

#define	codecLosslessQuality		0x400L
#define	codecMaxQuality				0x3ffL
#define	codecMinQuality				0x000L
#define	codecLowQuality				0x100L
#define	codecNormalQuality			0x200L
#define	codecHighQuality			0x300L

typedef pascal OSErr (*DataProcPtr)(Ptr *dataP,long bytesNeeded,long refcon);

typedef pascal OSErr (*FlushProcPtr)(Ptr data,long bytesAdded,long refcon);

typedef pascal void (*CompletionProcPtr)(OSErr result,short flags,long refcon);

#define	codecCompletionSource		(1<<0)
#define	codecCompletionDest			(1<<1)

typedef pascal OSErr (*ProgressProcPtr)(short message,Fixed completeness,long refcon);

#define	codecProgressOpen			0
#define	codecProgressUpdatePercent	1
#define	codecProgressClose			2

typedef pascal void (*StdPixProcPtr)(PixMap *src,Rect *srcRect,MatrixRecord *matrix,short mode,
	RgnHandle mask,PixMap *matte,Rect *matteRect,short flags);

typedef	long ImageSequence;

typedef	struct {
	ProgressProcPtr	progressProc;
	long			progressRefCon;
} ProgressProcRecord;

typedef	ProgressProcRecord	*ProgressProcRecordPtr;

typedef	struct {
	CompletionProcPtr	completionProc;
	long				completionRefCon;
} CompletionProcRecord;

typedef	CompletionProcRecord	*CompletionProcRecordPtr;

typedef	struct {
	DataProcPtr		dataProc;
	long			dataRefCon;
} DataProcRecord;

typedef	DataProcRecord	*DataProcRecordPtr;

typedef	struct {
	FlushProcPtr	flushProc;
	long			flushRefCon;
} FlushProcRecord;

typedef	FlushProcRecord	*FlushProcRecordPtr;

typedef pascal void (*AlignmentProcPtr)(Rect *rp, long refcon);

typedef	struct {
	AlignmentProcPtr	alignmentProc;
	long				alignmentRefCon;
} AlignmentProcRecord;

typedef	AlignmentProcRecord	*AlignmentProcRecordPtr;

typedef struct {
	long	dataRate;
	long	dataOverrun;
	long	frameDuration;
	long	keyFrameRate;
	CodecQ	minSpatialQuality;
	CodecQ	minTemporalQuality;
} DataRateParams;

typedef	 DataRateParams *DataRateParamsPtr;

typedef struct ImageDescription {
	long		idSize;
	CodecType	cType;
	long		resvd1;
	short		resvd2;
	short		dataRefIndex;
	short		version;
	short		revisionLevel;
	long		vendor;
	CodecQ		temporalQuality;
	CodecQ		spatialQuality;
	short		width;
	short		height;
	Fixed		hRes;
	Fixed		vRes;
	long		dataSize;
	short		frameCount;
	char		name[32];
	short		depth;
	short		clutID;
} ImageDescription;

typedef	ImageDescription	*ImageDescriptionPtr;

typedef	ImageDescription	**ImageDescriptionHandle;

typedef struct CodecInfo {
	char 			typeName[32];
	short			version;
	short			revisionLevel;
	long			vendor;
	long 			decompressFlags;
	long 			compressFlags;
	long 			formatFlags;
	unsigned char	compressionAccuracy;
	unsigned char	decompressionAccuracy;
	unsigned short	compressionSpeed;
	unsigned short	decompressionSpeed;
	unsigned char	compressionLevel;
	char			resvd;
	short			minimumHeight;
	short			minimumWidth;
	short			decompressPipelineLatency;
	short			compressPipelineLatency;
	long			privateData;
} CodecInfo;

typedef	struct {
	CodecComponent		codec;
	CodecType		cType;
	char			typeName[32];
	Handle			name;
} CodecNameSpec;

typedef	struct {
	short			count;
	CodecNameSpec	list[1];
}CodecNameSpecList;

typedef	CodecNameSpecList *CodecNameSpecListPtr;

#define	defaultDither	0
#define	forceDither		1
#define	suppressDither	2

#ifdef __cplusplus
extern "C" {
#endif __cplusplus

pascal	OSErr
CodecManagerVersion(long *version)
	= {0x7000,0xAAA3};
	
pascal OSErr
GetCodecNameList(CodecNameSpecListPtr *list,short showAll)
	= {0x7001,0xAAA3};

pascal OSErr
DisposeCodecNameList(CodecNameSpecListPtr list)
	= {0x700F,0xAAA3};

pascal	OSErr
GetCodecInfo(CodecInfo *info,CodecType cType,CodecComponent codec)
	= {0x7003,0xAAA3};

pascal OSErr
GetMaxCompressionSize(PixMapHandle src,const Rect *srcRect, short colorDepth,CodecQ quality,
		CodecType cType,CompressorComponent codec,long *size)
	= {0x7004,0xAAA3};

pascal OSErr
GetCompressionTime(PixMapHandle src,const Rect *srcRect, short colorDepth,
		CodecType cType,CompressorComponent codec,
		CodecQ *spatialQuality,CodecQ *temporalQuality,unsigned long *compressTime)
	= {0x7005,0xAAA3};

pascal OSErr
CompressImage(PixMapHandle src,const Rect *srcRect,CodecQ quality,CodecType cType,
		ImageDescriptionHandle desc,Ptr data)
	= {0x7006,0xAAA3};

pascal OSErr
FCompressImage(PixMapHandle src,const Rect *srcRect, short colorDepth,
		CodecQ quality,CodecType cType,CompressorComponent codec,CTabHandle clut,
		CodecFlags flags,long bufferSize,
		FlushProcRecordPtr flushProc,ProgressProcRecordPtr progressProc, ImageDescriptionHandle desc,Ptr data)
	= {0x7007,0xAAA3};

pascal OSErr
DecompressImage(Ptr data,ImageDescriptionHandle desc,PixMapHandle dst,
		const Rect *srcRect,const Rect *dstRect,short mode,RgnHandle mask)
	= {0x7008,0xAAA3};

pascal OSErr
FDecompressImage(Ptr data,ImageDescriptionHandle desc,PixMapHandle dst,const Rect *srcRect,
		MatrixRecordPtr matrix,short mode,RgnHandle mask,
		PixMapHandle matte,const Rect *matteRect,
		CodecQ accuracy,DecompressorComponent codec,
		long bufferSize,DataProcRecordPtr dataProc,ProgressProcRecordPtr progressProc)
	= {0x7009,0xAAA3};

pascal OSErr
CompressSequenceBegin(ImageSequence *seqID,PixMapHandle src,PixMapHandle prev,
		const Rect *srcRect,const Rect *prevRect,short colorDepth,CodecType cType,CompressorComponent codec,
		CodecQ spatialQuality,CodecQ temporalQuality,long keyFrameRate,
		CTabHandle clut,CodecFlags flags,ImageDescriptionHandle desc)
	= {0x700A,0xAAA3};

pascal OSErr
CompressSequenceFrame(ImageSequence seqID,PixMapHandle src,const Rect *srcRect,
		CodecFlags flags,Ptr data,long *dataSize,
		unsigned char *similarity,CompletionProcRecordPtr asyncCompletionProc)
	= {0x700B,0xAAA3};

pascal OSErr
DecompressSequenceBegin(ImageSequence *seqID,ImageDescriptionHandle desc,
		CGrafPtr port,GDHandle gdh,const Rect *srcRect,MatrixRecordPtr matrix,
		short mode,RgnHandle mask,CodecFlags flags,CodecQ accuracy,DecompressorComponent codec)
	= {0x700D,0xAAA3};

pascal OSErr
DecompressSequenceFrame(ImageSequence seqID,Ptr data,
		CodecFlags inFlags,CodecFlags *outFlags,CompletionProcRecordPtr asyncCompletionProc)
	= {0x700E,0xAAA3};

pascal OSErr
DecompressSequenceFrameS(ImageSequence seqID,Ptr data,long dataSize,
		CodecFlags inFlags,CodecFlags *outFlags,CompletionProcRecordPtr asyncCompletionProc)
	= {0x203C,0x16,0x47,0xAAA3};

pascal OSErr
SetDSequenceMatrix(ImageSequence seqID,MatrixRecordPtr matrix)
	= {0x7010,0xAAA3};

pascal OSErr
SetDSequenceMatte(ImageSequence seqID,PixMapHandle matte,const Rect *matteRect)
	= {0x7011,0xAAA3};

pascal OSErr
SetDSequenceMask(ImageSequence seqID,RgnHandle mask)
	= {0x7012,0xAAA3};

pascal OSErr
SetDSequenceTransferMode(ImageSequence seqID,short mode,const RGBColor *opColor)
	= {0x7013,0xAAA3};

pascal OSErr
SetDSequenceDataProc(ImageSequence seqID,DataProcRecordPtr dataProc,long bufferSize)
	= {0x7014,0xAAA3};

pascal OSErr
SetDSequenceAccuracy(ImageSequence seqID,CodecQ accuracy)
	= {0x7034,0xAAA3};

pascal OSErr
SetDSequenceSrcRect(ImageSequence seqID,const Rect *srcRect)
	= {0x7035,0xAAA3};

pascal OSErr
GetDSequenceImageBuffer(ImageSequence seqID,GWorldPtr *gworld)
	= {0x7015,0xAAA3};

pascal OSErr
GetDSequenceScreenBuffer(ImageSequence seqID,GWorldPtr *gworld)
	= {0x7016,0xAAA3};

pascal OSErr
SetCSequenceQuality(ImageSequence seqID,CodecQ spatialQuality,CodecQ temporalQuality)
	= {0x7017,0xAAA3};

pascal OSErr
SetCSequencePrev(ImageSequence seqID,PixMapHandle prev,const Rect *prevRect)
	= {0x7018,0xAAA3};

pascal OSErr
SetCSequenceFlushProc(ImageSequence seqID,FlushProcRecordPtr flushProc,long bufferSize)
	= {0x7033,0xAAA3};

pascal OSErr
SetCSequenceKeyFrameRate(ImageSequence seqID,long keyframerate)
	= {0x7036,0xAAA3};

pascal OSErr
GetCSequenceKeyFrameRate(ImageSequence seqID,long *keyframerate)
	= {0x203C,0x8,0x4B,0xAAA3};

pascal OSErr
GetCSequencePrevBuffer(ImageSequence seqID,GWorldPtr *gworld)
	= {0x7019,0xAAA3};

pascal OSErr
CDSequenceBusy(ImageSequence seqID)
	= {0x701A,0xAAA3};

pascal OSErr
CDSequenceEnd(ImageSequence seqID)
	= {0x701B,0xAAA3};

pascal OSErr
GetCompressedImageSize(ImageDescriptionHandle desc,Ptr data,long bufferSize,
		DataProcRecordPtr dataProc,long *dataSize)
	= {0x701C,0xAAA3};

pascal OSErr
GetSimilarity(PixMapHandle src,const Rect *srcRect,ImageDescriptionHandle desc,Ptr data,Fixed *similarity)
	= {0x701D,0xAAA3};

pascal OSErr
GetImageDescriptionCTable(ImageDescriptionHandle desc,CTabHandle *ctable)
	= {0x701E,0xAAA3};

pascal OSErr
SetImageDescriptionCTable(ImageDescriptionHandle desc,CTabHandle ctable)
	= {0x701F,0xAAA3};

pascal OSErr
GetImageDescriptionExtension(ImageDescriptionHandle desc,Handle *extension,long type,long index)
	= {0x7020,0xAAA3};

pascal OSErr
SetImageDescriptionExtension(ImageDescriptionHandle desc,Handle extension, long type)
	= {0x7021,0xAAA3};

pascal OSErr
RemoveImageDescriptionExtension(ImageDescription **desc, long type, long index)
	= {0x203C,0xC,0x3A,0xAAA3};

pascal OSErr
CountImageDescriptionExtensionType(ImageDescription **desc, long type, long *count)
	= {0x203C,0xC,0x3B,0xAAA3};

pascal OSErr
GetNextImageDescriptionExtensionType(ImageDescription **desc, long *type)
	= {0x203C,0x8,0x3C,0xAAA3};

pascal OSErr
FindCodec(CodecType cType,CodecComponent specCodec,
		CompressorComponent *compressor,DecompressorComponent *decompressor)
	= {0x7023,0xAAA3};

pascal OSErr
CompressPicture(PicHandle srcPicture, PicHandle dstPicture,CodecQ quality,CodecType cType)
	= {0x7024,0xAAA3};

pascal OSErr
FCompressPicture(PicHandle srcPicture, PicHandle dstPicture,
		short colorDepth, CTabHandle clut,CodecQ quality,
		short doDither,short compressAgain,ProgressProcRecordPtr progressProc,
		CodecType cType,CompressorComponent codec)
	= {0x7025,0xAAA3};

pascal OSErr
CompressPictureFile(short srcRefNum, short dstRefNum,CodecQ quality,CodecType cType)
	= {0x7026,0xAAA3};

pascal OSErr
FCompressPictureFile(short srcRefNum, short dstRefNum,short colorDepth, CTabHandle clut,
	CodecQ quality, short doDither,short compressAgain,ProgressProcRecordPtr progressProc,
	CodecType cType,CompressorComponent codec)
	= {0x7027,0xAAA3};

pascal OSErr
GetPictureFileHeader(short refNum,Rect *frame,OpenCPicParams *header)
	= {0x7028,0xAAA3};

pascal OSErr
DrawPictureFile(short refNum,const Rect *frame,ProgressProcRecordPtr progressProc)
	= {0x7029,0xAAA3};

pascal OSErr
DrawTrimmedPicture(PicHandle srcPicture,const Rect *frame,RgnHandle trimMask,short doDither,
		ProgressProcRecordPtr progressProc)
	= {0x702E,0xAAA3};

pascal OSErr
DrawTrimmedPictureFile(short srcRefnum,const Rect *frame,RgnHandle trimMask,short doDither,
		ProgressProcRecordPtr progressProc)
	= {0x702F,0xAAA3};

pascal OSErr
MakeThumbnailFromPicture(PicHandle picture,short colorDepth,PicHandle thumbnail,
		ProgressProcRecordPtr progressProc)
	= {0x702A,0xAAA3};

pascal OSErr
MakeThumbnailFromPictureFile(short refNum,short colorDepth,PicHandle thumbnail,
		ProgressProcRecordPtr progressProc)
= {0x702B,0xAAA3};

pascal OSErr
MakeThumbnailFromPixMap(PixMapHandle src,const Rect *srcRect,short colorDepth,PicHandle thumbnail,
		ProgressProcRecordPtr progressProc)
= {0x702C,0xAAA3};

pascal OSErr
TrimImage(ImageDescriptionHandle desc,Ptr inData,long inBufferSize,DataProcRecordPtr dataProc,
		Ptr	outData,long outBufferSize,FlushProcRecordPtr flushProc,Rect *trimRect,
		ProgressProcRecordPtr progressProc)
	= {0x702D,0xAAA3};

pascal OSErr
ConvertImage(ImageDescriptionHandle srcDD,Ptr srcData,short colorDepth,CTabHandle clut,
		CodecQ accuracy,CodecQ quality,CodecType cType,CodecComponent codec,
		ImageDescriptionHandle dstDD,Ptr dstData)
	= {0x7030,0xAAA3};

pascal OSErr
GetCompressedPixMapInfo(PixMapPtr pix,ImageDescriptionHandle *desc,Ptr *data,long *bufferSize,
	DataProcRecord *dataProc,ProgressProcRecord *progressProc)
	= {0x7037,0xAAA3};

pascal OSErr
SetCompressedPixMapInfo(PixMapPtr pix,ImageDescriptionHandle desc,Ptr data,long bufferSize,
	DataProcRecordPtr dataProc,ProgressProcRecordPtr progressProc)
	= {0x7038,0xAAA3};

pascal void
StdPix(PixMapPtr src,const Rect *srcRect,MatrixRecordPtr matrix,short mode,
	RgnHandle mask,PixMapPtr matte,const Rect *matteRect,short flags)
	 = {0x700C,0xAAA3};

pascal OSErr
TransformRgn(MatrixRecordPtr matrix, RgnHandle rgn)
	= {0x7039,0xAAA3};

/***********
	preview stuff
***********/

pascal void SFGetFilePreview(Point where,
                      ConstStr255Param prompt,
                      FileFilterProcPtr fileFilter,
                      short numTypes,
                      SFTypeList typeList,
                      DlgHookProcPtr dlgHook,
                      SFReply *reply)
 = {0x303C,0x41,0xAAA3};

pascal void SFPGetFilePreview(Point where,
                       ConstStr255Param prompt,
                       FileFilterProcPtr fileFilter,
                       short numTypes,
                       SFTypeList typeList,
                       DlgHookProcPtr dlgHook,
                       SFReply *reply,
                       short dlgID,
                       ModalFilterProcPtr filterProc)
 = {0x303C,0x42,0xAAA3};

pascal void StandardGetFilePreview(FileFilterProcPtr fileFilter,
                            short numTypes,
                            SFTypeList typeList,
                            StandardFileReply *reply)
 = {0x303C,0x43,0xAAA3};

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
 = {0x303C,0x44,0xAAA3};

pascal OSErr MakeFilePreview(short resRefNum, ProgressProcRecordPtr progress)
 = {0x303C,0x45,0xAAA3};

pascal OSErr AddFilePreview(short resRefNum, OSType previewType, Handle previewData)
 = {0x303C,0x46,0xAAA3};

#ifdef __cplusplus
}
#endif __cplusplus

enum {
	sfpItemPreviewAreaUser = 11,
	sfpItemPreviewStaticText = 12,
	sfpItemPreviewDividerUser = 13,
	sfpItemCreatePreviewButton = 14,
	sfpItemShowPreviewButton = 15
};

typedef struct {
	unsigned long	modDate;
	short			version;
	OSType			resType;
	short			resID;
} PreviewResourceRecord;
typedef PreviewResourceRecord *PreviewResourcePtr,  **PreviewResource;

#ifdef __cplusplus
extern "C" {
#endif __cplusplus

pascal void
AlignScreenRect(Rect *rp, AlignmentProcRecordPtr alignmentProc)
	= {0x203C,0x8,0x4C,0xAAA3};

pascal void
AlignWindow(WindowPtr wp, Boolean front, const Rect *alignmentRect, AlignmentProcRecordPtr alignmentProc)
	= {0x203C,0xE,0x4D,0xAAA3};

pascal void
DragAlignedWindow(WindowPtr wp, Point startPt, Rect *boundsRect, Rect *alignmentRect, AlignmentProcRecordPtr alignmentProc)
	= {0x203C,0x14,0x4E,0xAAA3};

pascal long
DragAlignedGrayRgn(RgnHandle theRgn, Point startPt, Rect *boundsRect,
	Rect *slopRect, short axis, ProcPtr actionProc, Rect *alignmentRect, AlignmentProcRecordPtr alignmentProc)
	= {0x203C,0x1E,0x4F,0xAAA3};

pascal OSErr
SetCSequenceDataRateParams(ImageSequence seqID,DataRateParamsPtr params)
	= {0x203C,0x8,0x50,0xAAA3};

pascal OSErr
SetCSequenceFrameNumber(ImageSequence seqID, long frameNumber)
	= {0x203C,0x8,0x51,0xAAA3};

pascal QDErr
NewImageGWorld(GWorldPtr *gworld,ImageDescription **idh,GWorldFlags flags)
	= {0x203C,0xC,0x52,0xAAA3};

pascal OSErr
GetCSequenceDataRateParams(ImageSequence seqID,DataRateParamsPtr params)
	= {0x203C,0x8,0x53,0xAAA3};

pascal OSErr
GetCSequenceFrameNumber(ImageSequence seqID,long *frameNumber)
	= {0x203C,0x8,0x54,0xAAA3};

pascal OSErr
GetBestDeviceRect(GDHandle *gdh, Rect *rp)
	= {0x203C,0x8,0x55,0xAAA3};

#ifdef __cplusplus
}
#endif __cplusplus

enum {
	identityMatrixType			= 0x00,		/* result if matrix is identity */
	translateMatrixType			= 0x01,		/* result if matrix translates */
	scaleMatrixType 			= 0x02,		/* result if matrix scales */
	scaleTranslateMatrixType	= 0x03,		/* result if matrix scales and translates */
	linearMatrixType			= 0x04,		/* result if matrix is general 2 x 2 */
	linearTranslateMatrixType	= 0x05,		/* result if matrix is general 2 x 2 and translates */
	perspectiveMatrixType		= 0x06		/* result if matrix is general 3 x 3 */
};
typedef unsigned short MatrixFlags;



#ifdef __cplusplus
extern "C" {
#endif __cplusplus
pascal short	GetMatrixType(MatrixRecord *m)
		= {0x7014,0xABC2};
pascal void		CopyMatrix(MatrixRecord *m1, MatrixRecord *m2)
		= {0x7020,0xABC2};
pascal Boolean	EqualMatrix(const MatrixRecord *m1, const MatrixRecord *m2)
		= {0x7021,0xABC2};

pascal void		SetIdentityMatrix( MatrixRecord *matrix )
		= {0x7015,0xABC2};
pascal void		TranslateMatrix( MatrixRecord *m, Fixed deltaH, Fixed deltaV )
		= {0x7019,0xABC2};
pascal void		RotateMatrix( MatrixRecord *m, Fixed degrees, Fixed aboutX, Fixed aboutY )
		= {0x7016,0xABC2};
pascal void		ScaleMatrix( MatrixRecord *m, Fixed scaleX, Fixed scaleY, Fixed aboutX, Fixed aboutY )
		= {0x7017,0xABC2};
pascal void		SkewMatrix(MatrixRecord *m, Fixed skewX, Fixed skewY, Fixed aboutX, Fixed aboutY)
		= {0x7018,0xABC2};

pascal OSErr	TransformFixedPoints(MatrixRecord *m, FixedPoint *fpt, long count)
		= {0x7022,0xABC2};
pascal OSErr	TransformPoints( MatrixRecord *mp, Point *pt1, long count )
		= {0x7023,0xABC2};
pascal Boolean	TransformFixedRect(MatrixRecord *m, FixedRect *fr, FixedPoint *fpp)
		= {0x7024,0xABC2};
pascal Boolean	TransformRect(MatrixRecord *m, Rect *r, FixedPoint *fpp)
		= {0x7025,0xABC2};

pascal Boolean	InverseMatrix(MatrixRecord *m, MatrixRecord *im)
		= {0x701C,0xABC2};
pascal void		ConcatMatrix(MatrixRecord *a, MatrixRecord *b)
		= {0x701B,0xABC2};

pascal void		RectMatrix(MatrixRecord *matrix,Rect *srcRect,Rect *dstRect)
		= {0x701E,0xABC2};
pascal void		MapMatrix(MatrixRecord *matrix,Rect *fromRect,Rect *toRect)
		= {0x701D,0xABC2};

#ifdef __cplusplus
}
#endif __cplusplus


#endif __IMAGECOMPRESSION__
