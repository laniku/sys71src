
/************************************************************

Created: Tuesday, July 23, 1991 at 2:53 PM
 PictUtil.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1990-1991
  All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <7>	 7/23/91	JL		Checked in File from database. Changed #defines to enums.
									Adjusted comments. Moved PictInfoID typedef to the beginning of
									the Type declarations to match Pascal file.
		 <6>	 1/16/91	JDR		(dba) Renamed METHOD_SYSTEM to systemMethod, METHOD_POPULAR to
									popularMethod, and METHOD_MEDIAN to medianMethod
		 <5>	 10/9/90	JAL		CPlusPlus compatibility.
		 <4>	 9/21/90	gbm		(Actually DDG) Updating selectors to work with ProcHelper.
		 <3>	 9/19/90	DDG		Name changes for some of the parameters for a few of the
									routines.
		 <2>	 9/18/90	DDG		Fixed the header.
		 <1>	 9/18/90	DDG		first checked in

	To Do:
************************************************************/


#ifndef __PICTUTIL__
#define __PICTUTIL__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __PALETTES__
#include <Palettes.h>
#endif


enum {


/* verbs for the GetPictInfo, GetPixMapInfo, and NewPictInfo calls */

#define returnColorTable ((short) 0x0001)
#define returnPalette ((short) 0x0002)
#define recordComments ((short) 0x0004)
#define recordFontInfo ((short) 0x0008)
#define suppressBlackAndWhite ((short) 0x0010)

/* color pick methods */

 systemMethod = 0,					/*system color pick method*/
 popularMethod = 1,					/*method that chooses the most popular set of colors*/
 medianMethod = 2,					/*method that chooses a good average mix of colors*/

/* color bank types */
 ColorBankIsCustom = -1,
 ColorBankIsExactAnd555 = 0,
 ColorBankIs555 = 1
};

typedef long PictInfoID;

struct CommentSpec {
 short count;						/* number of occurrances of this comment ID */
 short ID;							/* ID for the comment in the picture */
};

typedef struct CommentSpec CommentSpec;
typedef CommentSpec *CommentSpecPtr, **CommentSpecHandle;

struct FontSpec {
 short pictFontID;					/* ID of the font in the picture */
 short sysFontID;					/* ID of the same font in the current system file */
 long size[4];						/* bit array of all the sizes found (1..127) (bit 0 means > 127) */
 short style;						/* combined style of all occurrances of the font */
 long nameOffset;					/* offset into the fontNamesHdl handle for the font’s name */
};

typedef struct FontSpec FontSpec;
typedef FontSpec *FontSpecPtr, **FontSpecHandle;

struct PictInfo {
 short version;						/* this is always zero, for now */
 long uniqueColors;					/* the number of actual colors in the picture(s)/pixmap(s) */
 PaletteHandle thePalette;			/* handle to the palette information */
 CTabHandle theColorTable;			/* handle to the color table */
 Fixed hRes;						/* maximum horizontal resolution for all the pixmaps */
 Fixed vRes;						/* maximum vertical resolution for all the pixmaps */
 short depth;						/* maximum depth for all the pixmaps (in the picture) */
 Rect sourceRect;					/* the picture frame rectangle (this contains the entire picture) */
 long textCount;					/* total number of text strings in the picture */
 long lineCount;					/* total number of lines in the picture */
 long rectCount;					/* total number of rectangles in the picture */
 long rRectCount;					/* total number of round rectangles in the picture */
 long ovalCount;					/* total number of ovals in the picture */
 long arcCount;						/* total number of arcs in the picture */
 long polyCount;					/* total number of polygons in the picture */
 long regionCount;					/* total number of regions in the picture */
 long bitMapCount;					/* total number of bitmaps in the picture */
 long pixMapCount;					/* total number of pixmaps in the picture */
 long commentCount;					/* total number of comments in the picture */
 long uniqueComments;				/* the number of unique comments in the picture */
 CommentSpecHandle commentHandle;	/* handle to all the comment information */
 long uniqueFonts;					/* the number of unique fonts in the picture */
 FontSpecHandle fontHandle;			/* handle to the FontSpec information */
 Handle fontNamesHandle;			/* handle to the font names */
 long reserved1;
 long reserved2;
};

typedef struct PictInfo PictInfo;
typedef PictInfo *PictInfoPtr, **PictInfoHandle;


#ifdef __cplusplus
extern "C" {
#endif
pascal OSErr GetPictInfo(PicHandle thePictHandle,
                         PictInfo *thePictInfo,
                         short verb,
                         short colorsRequested,
                         short colorPickMethod,
                         short version)
 = {0x303C,0x0800,0xA831}; 
pascal OSErr GetPixMapInfo(PixMapHandle thePixMapHandle,
                           PictInfo *thePictInfo,
                           short verb,
                           short colorsRequested,
                           short colorPickMethod,
                           short version)
 = {0x303C,0x0801,0xA831}; 
pascal OSErr NewPictInfo(PictInfoID *thePictInfoID,
                         short verb,
                         short colorsRequested,
                         short colorPickMethod,
                         short version)
 = {0x303C,0x0602,0xA831}; 
pascal OSErr RecordPictInfo(PictInfoID thePictInfoID,
                            PicHandle thePictHandle)
 = {0x303C,0x0403,0xA831}; 
pascal OSErr RecordPixMapInfo(PictInfoID thePictInfoID,
                              PixMapHandle thePixMapHandle)
 = {0x303C,0x0404,0xA831}; 
pascal OSErr RetrievePictInfo(PictInfoID thePictInfoID,
                              PictInfo *thePictInfo,
                              short colorsRequested)
 = {0x303C,0x0505,0xA831}; 
pascal OSErr DisposPictInfo(PictInfoID thePictInfoID)
 = {0x303C,0x0206,0xA831}; 
#ifdef __cplusplus
}
#endif

#endif
