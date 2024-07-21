/************************************************************

Created: Friday, September 27, 1991 10:04:39 AM
 ImageCodec.r
 Rez Interface to the Macintosh Libraries


 Copyright Apple Computer, Inc. 1991
 All rights reserved

************************************************************/

/*
type 'thng' {
	hex longint	type;
	hex longint	subType;
	hex longint	manufacturere;
	hex	longint	flags;
	hex	longint flagsMask;
	hex longint	thingResType;	
	int thingResID;
	hex longint  thingNameResType;
	int thingNameResID;
	hex longint  thingInfoResType;
	int thingInfoResID;
	hex longint  thingIconResType;
	int thingIconResID;
};
*/

#define	codecInfoDoes1				1			/* codec can work with 1-bit pixels */
#define	codecInfoDoes2				2			/* codec can work with 2-bit pixels */
#define	codecInfoDoes4				4			/* codec can work with 4-bit pixels */
#define	codecInfoDoes8				8			/* codec can work with 8-bit pixels */
#define	codecInfoDoes16				0x10		/* codec can work with 16-bit pixels */
#define	codecInfoDoes32				0x20		/* codec can work with 32-bit pixels */
#define	codecInfoDoesDither			0x40		/* codec can do ditherMode */
#define	codecInfoDoesStretch		0x80		/* codec can stretch to arbitrary sizes */
#define	codecInfoDoesShrink			0x100		/* codec can shrink to arbitrary sizes */
#define	codecInfoDoesMask			0x200		/* codec can mask to clipping regions */
			
#define	codecInfoDoesTemporal		0x400		/* codec can handle temporal redundancy */

#define	codecInfoDoesDouble			0x800		/* codec can stretch to double size exactly */
#define	codecInfoDoesQuad			0x1000		/* codec can stretch to quadruple size exactly */
#define	codecInfoDoesHalf			0x2000		/* codec can shrink to half size */
#define	codecInfoDoesQuarter		0x4000		/* codec can shrink to quarter size */

#define	codecInfoDoesRotate			0x8000		/* codec can rotate on decompress */
#define	codecInfoDoesHorizFlip		0x10000		/* codec can flip horizontally on decompress */
#define	codecInfoDoesVertFlip		0x20000		/* codec can flip vertically on decompress */
#define	codecInfoDoesSkew			0x40000		/* codec can skew on decompress */
#define	codecInfoDoesBlend			0x80000		/* codec can blend on decompress */
#define	codecInfoDoesWarp			0x100000	/* codec can warp arbitrarily on decompress */
#define	codecInfoDoesRecompress		0x200000	/* codec can recompress image without accumulating errors */
#define	codecInfoDoesSpool			0x400000	/* codec can spool image data */
#define	codecInfoDoesRateConstrain	0x800000	/* codec can data rate constrain */


#define	codecInfoDepth1				1			/* compressed data at 1 bpp depth available */
#define	codecInfoDepth2				2			/* compressed data at 2 bpp depth available */
#define	codecInfoDepth4				4			/* compressed data at 4 bpp depth available */
#define	codecInfoDepth8				8			/* compressed data at 8 bpp depth available */
#define	codecInfoDepth16			0x10		/* compressed data at 16 bpp depth available */
#define	codecInfoDepth32			0x20		/* compressed data at 32 bpp depth available */
#define	codecInfoDepth24			0x40		/* compressed data at 24 bpp depth available */
#define	codecInfoDepth33			0x80		/* compressed data at 1 bpp monochrome depth  available */
#define	codecInfoDepth34			0x100		/* compressed data at 2 bpp grayscale depth available */
#define	codecInfoDepth36			0x200		/* compressed data at 4 bpp grayscale depth available */
#define	codecInfoDepth40			0x400		/* compressed data at 8 bpp grayscale depth available */
#define	codecInfoStoresClut			0x800		/* compressed data can have custom cluts */
#define	codecInfoDoesLossless		0x1000		/* compressed data can be stored in lossless format */
#define	codecInfoSequenceSensitive	0x2000		/* compressed data is sensitive to out of sequence decoding */


type 'cdci' {
	pstring[31];
	hex integer	version;
	hex integer	revlevel;
	hex longint	vendor;
	hex longint	decompressFlags;
	hex longint	compressFlags;
	hex longint	formatFlags;
	byte		compressionAccuracy;
	byte		decompressionAccuracy;
	integer		compressionSpeed;
	integer		decompressionSpeed;
	byte		compressionLevel;
	byte		resvd;
	integer		minimumHeight;
	integer		minimumWidth;
	integer		decompressPipelineLatency;
	integer		compressPipelineLatency;
	longint		privateData;
};



#define	compressorComponentType			'imco'
#define	decompressorComponentType		'imdc'



