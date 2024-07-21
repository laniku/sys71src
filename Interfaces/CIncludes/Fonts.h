
/************************************************************

Created: Monday, January 28, 1991 at 5:47 PM
 Fonts.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved


	Change History (most recent first):

		<11>	 4/15/92	DCL		For New Inside Mac: Moved GetDefFontSize, GetSysFont, and
									GetAppFont from Script to Fonts.
		<10>	 7/30/91	JL		Updated Copyright.
		 <9>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <8>	  1/5/91	JDR		(dba) Changed useSpline to outlinePreferred, glyphCount to
									byteCount and turnOffLineHeight to preserveGlyph.
		 <6>	12/14/90	dba		<JDR> add calls for outline fonts
		 <5>	11/28/90	JL		Put formal parameter names back.
		 <4>	 11/7/90	JL		Changed all #defines to anonymous enums
		 <3>	 11/4/90	dba		use constStr255Parameter

************************************************************/


#ifndef __FONTS__
#define __FONTS__

#ifndef __TYPES__
#include <Types.h>
#endif


enum {

 systemFont = 0,
 applFont = 1,
 newYork = 2,
 geneva = 3,
 monaco = 4,
 venice = 5,
 london = 6,
 athens = 7,
 sanFran = 8,
 toronto = 9,
 cairo = 11,
 losAngeles = 12,
 times = 20,
 helvetica = 21,
 courier = 22,
 symbol = 23,
 mobile = 24,
 commandMark = 17,
 checkMark = 18,
 diamondMark = 19
};
enum {
 appleMark = 20,
 propFont = 36864,
 prpFntH = 36865,
 prpFntW = 36866,
 prpFntHW = 36867,
 fixedFont = 45056,
 fxdFntH = 45057,
 fxdFntW = 45058,
 fxdFntHW = 45059,
 fontWid = 44208
};

struct FMInput {
 short family;
 short size;
 Style face;
 Boolean needBits;
 short device;
 Point numer;
 Point denom;
};

typedef struct FMInput FMInput;

struct FMOutput {
 short errNum;
 Handle fontHandle;
 unsigned char boldPixels;
 unsigned char italicPixels;
 unsigned char ulOffset;
 unsigned char ulShadow;
 unsigned char ulThick;
 unsigned char shadowPixels;
 char extra;
 unsigned char ascent;
 unsigned char descent;
 unsigned char widMax;
 char leading;
 char unused;
 Point numer;
 Point denom;
};

typedef struct FMOutput FMOutput;
typedef FMOutput *FMOutPtr;

struct FontRec {
 short fontType;		/*font type*/
 short firstChar;		/*ASCII code of first character*/
 short lastChar;		/*ASCII code of last character*/
 short widMax;			/*maximum character width*/
 short kernMax;			/*negative of maximum character kern*/
 short nDescent;		/*negative of descent*/
 short fRectWidth;		/*width of font rectangle*/
 short fRectHeight;		/*height of font rectangle*/
 short owTLoc;			/*offset to offset/width table*/
 short ascent;			/*ascent*/
 short descent;			/*descent*/
 short leading;			/*leading*/
 short rowWords;		/*row width of bit image / 2 */
};

typedef struct FontRec FontRec;

struct FMetricRec {
 Fixed ascent;			/*base line to top*/
 Fixed descent;			/*base line to bottom*/
 Fixed leading;			/*leading between lines*/
 Fixed widMax;			/*maximum character width*/
 Handle wTabHandle;		/*handle to font width table*/
};

typedef struct FMetricRec FMetricRec;

struct WidEntry {
 short widStyle;		/*style entry applies to*/
};

typedef struct WidEntry WidEntry;

struct WidTable {
 short numWidths;		/*number of entries - 1*/
};

typedef struct WidTable WidTable;

struct AsscEntry {
 short fontSize;
 short fontStyle;
 short fontID;			/*font resource ID*/
};

typedef struct AsscEntry AsscEntry;

struct FontAssoc {
 short numAssoc;		/*number of entries - 1*/
};

typedef struct FontAssoc FontAssoc;

struct StyleTable {
 short fontClass;
 long offset;
 long reserved;
 char indexes[48];
};

typedef struct StyleTable StyleTable;

struct NameTable {
 short stringCount;
 Str255 baseFontName;
};

typedef struct NameTable NameTable;

struct KernPair {
 char kernFirst;		/*1st character of kerned pair*/
 char kernSecond;		/*2nd character of kerned pair*/
 short kernWidth;		/*kerning in 1pt fixed format*/
};

typedef struct KernPair KernPair;

struct KernEntry {
 short kernLength;		/*length of this entry*/
 short kernStyle;		/*style the entry applies to*/
};

typedef struct KernEntry KernEntry;

struct KernTable {
 short numKerns;		/*number of kerning entries*/
};

typedef struct KernTable KernTable;

struct WidthTable {
 Fixed tabData[256];	/*character widths*/
 Handle tabFont;		/*font record used to build table*/
 long sExtra;			/*space extra used for table*/
 long style;			/*extra due to style*/
 short fID;				/*font family ID*/
 short fSize;			/*font size request*/
 short face;			/*style (face) request*/
 short device;			/*device requested*/
 Point inNumer;			/*scale factors requested*/
 Point inDenom;			/*scale factors requested*/
 short aFID;			/*actual font family ID for table*/
 Handle fHand;			/*family record used to build up table*/
 Boolean usedFam;		/*used fixed point family widths*/
 unsigned char aFace;	/*actual face produced*/
 short vOutput;			/*vertical scale output value*/
 short hOutput;			/*horizontal scale output value*/
 short vFactor;			/*vertical scale output value*/
 short hFactor;			/*horizontal scale output value*/
 short aSize;			/*actual size of actual font used*/
 short tabSize;			/*total size of table*/
};

typedef struct WidthTable WidthTable;

struct FamRec {
 short ffFlags;			/*flags for family*/
 short ffFamID;			/*family ID number*/
 short ffFirstChar;		/*ASCII code of 1st character*/
 short ffLastChar;		/*ASCII code of last character*/
 short ffAscent;		/*maximum ascent for 1pt font*/
 short ffDescent;		/*maximum descent for 1pt font*/
 short ffLeading;		/*maximum leading for 1pt font*/
 short ffWidMax;		/*maximum widMax for 1pt font*/
 long ffWTabOff;		/*offset to width table*/
 long ffKernOff;		/*offset to kerning table*/
 long ffStylOff;		/*offset to style mapping table*/
 short ffProperty[9];	/*style property info*/
 short ffIntl[2];		/*for international use*/
 short ffVersion;		/*version number*/
};

typedef struct FamRec FamRec;


#ifdef __cplusplus
extern "C" {
#endif
pascal void InitFonts(void)
 = 0xA8FE; 
pascal void GetFontName(short familyID,Str255 name)
 = 0xA8FF; 
pascal void GetFNum(ConstStr255Param name,short *familyID)
 = 0xA900; 
pascal Boolean RealFont(short fontNum,short size)
 = 0xA902; 
pascal void SetFontLock(Boolean lockFlag)
 = 0xA903; 
pascal FMOutPtr FMSwapFont(const FMInput *inRec)
 = 0xA901; 
pascal void SetFScaleDisable(Boolean fscaleDisable)
 = 0xA834; 
pascal void FontMetrics(const FMetricRec *theMetrics)
 = 0xA835; 
pascal void SetFractEnable(Boolean fractEnable); 
pascal Boolean IsOutline(Point numer,Point denom)
 = {0x7000,0xA854}; 
pascal void SetOutlinePreferred(Boolean outlinePreferred)
 = {0x7001,0xA854}; 
pascal Boolean GetOutlinePreferred(void)
 = {0x7009,0xA854}; 
pascal OSErr OutlineMetrics(short byteCount,const void *textPtr,Point numer,
 Point denom,short *yMax,short *yMin,FixedPtr awArray,FixedPtr lsbArray,
 RectPtr boundsArray)
 = {0x7008,0xA854}; 
pascal void SetPreserveGlyph(Boolean preserveGlyph)
 = {0x700A,0xA854}; 
pascal Boolean GetPreserveGlyph(void)
 = {0x700B,0xA854}; 
pascal OSErr FlushFonts(void)
 = {0x700C,0xA854}; 
void getfnum(char *theName,short *familyID); 
void getfontname(short familyID,char *theName); 

pascal short GetDefFontSize(void)
 = {0x3EB8,0x0BA8,0x6604,0x3EBC,0x000C}; 
#define GetSysFont() (* (short*) 0x0BA6)
#define GetAppFont() (* (short*) 0x0984)

#ifdef __cplusplus
}
#endif

#endif
