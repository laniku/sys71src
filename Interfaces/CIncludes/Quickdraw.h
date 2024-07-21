/************************************************************

Created: Saturday, July 27, 1991 at 5:34 PM
 Quickdraw.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved


	Change History (most recent first):

		 <6>	 11/5/93	IH		Sync with Excelsior.
		<SM2>	11/16/92	CSS		Update from Reality:
									<27> 11/13/92 JDR	Updated QuickDraw.h to not use the dangerous pattern type.
		<SM1>	10/19/92	CSS		Directly call the traps for quickdraw.
		<26>	  7/6/92	KON		No longer need bits 5 and 6 in gdFlags. Move bit 4 to bit 6.
		<25>	 6/30/92	KON		Add three new gdFlags: Bit 4 hasAuxMenuBar, Bit 5
									pixelsAreSlewSlow, and Bit 6 whiteIsOff.
		<24>	 5/29/92	DCL		Moved StdText from QuickDraw to QuickDrawText.
		<23>	  5/5/92	DCL		For New Inside Mac: moved text-related calls from TextUtils &
									QuickDraw to QuickdrawText. Weeeeeeee!
		<22>	 4/15/92	DCL		For New Inside Mac: Moved many definitions from Script to
									TextUtils and QuickDraw. And added new synonyms. #1025005
		<21>	 2/18/92	MH		The new, and alternative old definition of Pattern which were
									developed for ETO 6 are added.  The new def prevents certain
									crashes on 68000 machines running code compiled with it.  In
									order to keep the BBS builds working, I have added a tempory
									#define of dangerousPattern, which causes the old def to be
									chosen.  The old def poses no danger to our system code.  The
									#define should be removed when producing interface files for
									external consumption.  Ideally, it should be removed from this
									file and added to {COptions} in the build script.
		<20>	11/11/91	MH		Add comment about the dangers of placing a Pattern at an odd
									alignment in a struct.
		<19>	 11/8/91	JL		Changed PatPtr from a pointer to the Pattern struct to a pointer
									to the same type as the Pattern struct. Pattern is an array and
									therefore a pointer to it would be a pointer to a pointer.
		<18>	 7/31/91	JL		Updated Copyright. Restored Comments.
		<17>	 6/14/91	JL		Moved gdDevType and burstDevice up to previous enum to match the
									DSG database.  Adjusted comments as well. Temporarily lost
									comments for ext32Device and burstDevice; will be restored
									later.  Also lost updated copyright date; will restore later.
		<16>	  2/5/91	stb		gs: add burstDevice and ext32Device
		<15>	 1/28/91	LN		Checked in Database Generated File from DSG. changed
									constPatternParameter to ConstPatternParam.
		<13>	12/14/90	KON		Change name of PICT2Header to OpenCPicParams.[smc]
		<12>	11/27/90	JL		Put formal parameter names back.
		<11>	 11/7/90	JL		Changed all #defines to anonymous enums
		<10>	 11/4/90	dba		created constPatternParameter since Pattern is an array in C;
									got rid of some extraneous parameter names; made some parameters
									void* instead of Ptr; added more use of const in parameters;
									added DisposePixMap, DisposePixPat, DisposeCTable,
									DisposeCCursor, DisposeCIcon, DisposeGDevice
		 <9>	10/21/90	gbm		(with dba) Made compatible with 3.2 C compiler (and incompatible
									with previous compilers).
		 <9>	10/10/90	JAL		New style #Pragma Parameters for MPW 3.2 C
		 <8>	 9/15/90	JSM		Add typedef struct PICT2Header PICT2Header.
		 <7>	 9/15/90	KON		Added equates for OpenCPicture, CopyDeepMask, and the
									CPictureHeader record.
		 <6>	 9/14/90	csd		Added interfaces for the DeviceLoop call.
		 <5>	  9/4/90	kaz		Adding grayishTextOr text mode
	<4>	03/09/90	JAL	Added dithercopy.
	<3>	03/02/90	JAL	Added adMax which is correct spelling.
************************************************************/


#ifndef __QUICKDRAW__
#define __QUICKDRAW__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __QUICKDRAWTEXT__
#include <QuickdrawText.h>  
#endif

#ifndef __ROMFastTrapsIncluded__
#include "ROMFastTraps.h"
#endif


enum {

 invalColReq = -1,					/*invalid color table request*/

/* transfer modes */
 srcCopy = 0,						/*the 16 transfer modes*/
 srcOr = 1,
 srcXor = 2,
 srcBic = 3,
 notSrcCopy = 4,
 notSrcOr = 5,
 notSrcXor = 6,
 notSrcBic = 7,
 patCopy = 8,
 patOr = 9,
 patXor = 10,
 patBic = 11,
 notPatCopy = 12,
 notPatOr = 13,
 notPatXor = 14,
 notPatBic = 15,

/* Special Text Transfer Mode */
 grayishTextOr = 49,

/* Arithmetic transfer modes */
 blend = 32,
 addPin = 33
};
enum {
 addOver = 34,
 subPin = 35,
 addMax = 37,
 adMax = 37,
 subOver = 38,
 adMin = 39,
 ditherCopy = 64,

/* Transparent mode constant */
 transparent = 36,

/* QuickDraw color separation constants */
 normalBit = 0,						/*normal screen mapping*/
 inverseBit = 1,					/*inverse screen mapping*/
 redBit = 4,						/*RGB additive mapping*/
 greenBit = 3,
 blueBit = 2,
 cyanBit = 8,						/*CMYBk subtractive mapping*/
 magentaBit = 7,
 yellowBit = 6,
 blackBit = 5,
 blackColor = 33,					/*colors expressed in these mappings*/
 whiteColor = 30,
 redColor = 205
};
enum {
 greenColor = 341,
 blueColor = 409,
 cyanColor = 273,
 magentaColor = 137,
 yellowColor = 69,

 picLParen = 0,						/*standard picture comments*/
 picRParen = 1,


 clutType = 0,						/*0 if lookup table*/
 fixedType = 1,						/*1 if fixed table*/
 directType = 2,					/*2 if direct values*/

 gdDevType = 0,						/*0 = monochrome 1 = color*/
 burstDevice = 7
};
enum {
 roundedDevice = 5,					/* 1 if device has been “rounded” into the GrayRgn */
 hasAuxMenuBar = 6,					/* 1 if device has an aux menu bar on it */
 ext32Device = 8,
 ramInit = 10,						/*1 if initialized from 'scrn' resource*/
 mainScreen = 11,					/* 1 if main screen */
 allInit = 12,						/* 1 if all devices initialized */
 screenDevice = 13,					/*1 if screen device [not used]*/
 noDriver = 14,						/* 1 if no driver for this GDevice */
 screenActive = 15,					/*1 if in use*/

 hiliteBit = 7,						/*flag bit in HiliteMode (lowMem flag)*/
 pHiliteBit = 0,					/*flag bit in HiliteMode used with BitClr procedure*/

 defQDColors = 127,					/*resource ID of clut for default QDColors*/

/* pixel type */
 RGBDirect = 16,					/* 16 & 32 bits/pixel pixelType value */

/* pmVersion values */
 baseAddr32 = 4,					/*pixmap base address is 32-bit address*/

 rgnOverflowErr = -147,				/* Region accumulation failed. Resulting region may be currupt */
 insufficientStackErr = -149		/* QuickDraw could not complete the operation */
};




enum {frame,paint,erase,invert,fill};
typedef unsigned char GrafVerb;

enum {chunky,chunkyPlanar,planar};
typedef unsigned char PixelType;


typedef short Bits16[16];

/***************   IMPORTANT NOTE REGARDING PATTERN  **************************************
   The old array defintion of Pattern would cause 68000 based CPU's to crash in certain circum-
   stances. The new struct definition is safe, but may require source code changes to compile.
   Read the details in Appendix J of:
   		"MPW E.T.O. #6 Latest Libraries/Interfaces"
	If you decide that you are safe, and happier with the old definition, you may add
   "-d dangerousPattern" to your C command line to avoid compilation errors without changing
   your source code.
*********************************************************************************************/

#ifdef dangerousPattern
typedef unsigned char Pattern[8];
typedef const unsigned char *ConstPatternParam;
#else
struct Pattern{
   unsigned char pat[8];
};
typedef struct Pattern Pattern;
typedef const Pattern *ConstPatternParam;
#endif
typedef Pattern *PatPtr;
typedef PatPtr *PatHandle;

typedef char QDByte, *QDPtr, **QDHandle;

typedef short QDErr;

enum {singleDevicesBit = 0, dontMatchSeedsBit = 1, allDevicesBit = 2};
enum {singleDevices = 1 << singleDevicesBit, dontMatchSeeds = 1 << dontMatchSeedsBit,
 allDevices = 1 << allDevicesBit};
typedef unsigned long DeviceLoopFlags;


struct BitMap {
 Ptr baseAddr;
 short rowBytes;
 Rect bounds;
};

typedef struct BitMap BitMap;
typedef BitMap *BitMapPtr, **BitMapHandle;

struct Cursor {
 Bits16 data;
 Bits16 mask;
 Point hotSpot;
};

typedef struct Cursor Cursor;
typedef Cursor *CursPtr, **CursHandle;

struct PenState {
 Point pnLoc;
 Point pnSize;
 short pnMode;
 Pattern pnPat;
};

typedef struct PenState PenState;

struct Region {
 short rgnSize;						/*size in bytes*/
 Rect rgnBBox;						/*enclosing rectangle*/
};

typedef struct Region Region;
typedef Region *RgnPtr, **RgnHandle;

struct Picture {
 short picSize;
 Rect picFrame;
};

typedef struct Picture Picture;
typedef Picture *PicPtr, **PicHandle;

struct Polygon {
 short polySize;
 Rect polyBBox;
 Point polyPoints[1];
};

typedef struct Polygon Polygon;
typedef Polygon *PolyPtr, **PolyHandle;

struct QDProcs {
 Ptr textProc;
 Ptr lineProc;
 Ptr rectProc;
 Ptr rRectProc;
 Ptr ovalProc;
 Ptr arcProc;
 Ptr polyProc;
 Ptr rgnProc;
 Ptr bitsProc;
 Ptr commentProc;
 Ptr txMeasProc;
 Ptr getPicProc;
 Ptr putPicProc;
};

typedef struct QDProcs QDProcs;
typedef QDProcs *QDProcsPtr;

struct GrafPort {
 short device;
 BitMap portBits;
 Rect portRect;
 RgnHandle visRgn;
 RgnHandle clipRgn;
 Pattern bkPat;
 Pattern fillPat;
 Point pnLoc;
 Point pnSize;
 short pnMode;
 Pattern pnPat;
 short pnVis;
 short txFont;
 Style txFace;						/*txFace is unpacked byte but push as short*/
 char filler;
 short txMode;
 short txSize;
 Fixed spExtra;
 long fgColor;
 long bkColor;
 short colrBit;
 short patStretch;
 Handle picSave;
 Handle rgnSave;
 Handle polySave;
 QDProcsPtr grafProcs;
};

typedef struct GrafPort GrafPort;
typedef GrafPort *GrafPtr;


typedef GrafPtr WindowPtr;

struct RGBColor {
 unsigned short red;				/*magnitude of red component*/
 unsigned short green;				/*magnitude of green component*/
 unsigned short blue;				/*magnitude of blue component*/
};

typedef struct RGBColor RGBColor;


typedef pascal Boolean (*ColorSearchProcPtr)(RGBColor *rgb, long *position);
typedef pascal Boolean (*ColorComplementProcPtr)(RGBColor *rgb);

struct ColorSpec {
 short value;						/*index or other value*/
 RGBColor rgb;						/*true color*/
};

typedef struct ColorSpec ColorSpec;
typedef ColorSpec *ColorSpecPtr;


typedef ColorSpec CSpecArray[1];

struct ColorTable {
 long ctSeed;						/*unique identifier for table*/
 short ctFlags;						/*high bit: 0 = PixMap; 1 = device*/
 short ctSize;						/*number of entries in CTTable*/
 CSpecArray ctTable;				/*array [0..0] of ColorSpec*/
};

typedef struct ColorTable ColorTable;
typedef ColorTable *CTabPtr, **CTabHandle;

struct MatchRec {
 unsigned short red;
 unsigned short green;
 unsigned short blue;
 long matchData;
};

typedef struct MatchRec MatchRec;

struct PixMap {
 Ptr baseAddr;						/*pointer to pixels*/
 short rowBytes;					/*offset to next line*/
 Rect bounds;						/*encloses bitmap*/
 short pmVersion;					/*pixMap version number*/
 short packType;					/*defines packing format*/
 long packSize;						/*length of pixel data*/
 Fixed hRes;						/*horiz. resolution (ppi)*/
 Fixed vRes;						/*vert. resolution (ppi)*/
 short pixelType;					/*defines pixel type*/
 short pixelSize;					/*# bits in pixel*/
 short cmpCount;					/*# components in pixel*/
 short cmpSize;						/*# bits per component*/
 long planeBytes;					/*offset to next plane*/
 CTabHandle pmTable;				/*color map for this pixMap*/
 long pmReserved;					/*for future use. MUST BE 0*/
};

typedef struct PixMap PixMap;
typedef PixMap *PixMapPtr, **PixMapHandle;

struct PixPat {
 short patType;						/*type of pattern*/
 PixMapHandle patMap;				/*the pattern's pixMap*/
 Handle patData;					/*pixmap's data*/
 Handle patXData;					/*expanded Pattern data*/
 short patXValid;					/*flags whether expanded Pattern valid*/
 Handle patXMap;					/*Handle to expanded Pattern data*/
 Pattern pat1Data;					/*old-Style pattern/RGB color*/
};

typedef struct PixPat PixPat;
typedef PixPat *PixPatPtr, **PixPatHandle;

struct CCrsr {
 short crsrType;					/*type of cursor*/
 PixMapHandle crsrMap;				/*the cursor's pixmap*/
 Handle crsrData;					/*cursor's data*/
 Handle crsrXData;					/*expanded cursor data*/
 short crsrXValid;					/*depth of expanded data (0 if none)*/
 Handle crsrXHandle;				/*future use*/
 Bits16 crsr1Data;					/*one-bit cursor*/
 Bits16 crsrMask;					/*cursor's mask*/
 Point crsrHotSpot;					/*cursor's hotspot*/
 long crsrXTable;					/*private*/
 long crsrID;						/*private*/
};

typedef struct CCrsr CCrsr;
typedef CCrsr *CCrsrPtr, **CCrsrHandle;

struct CIcon {
 PixMap iconPMap;					/*the icon's pixMap*/
 BitMap iconMask;					/*the icon's mask*/
 BitMap iconBMap;					/*the icon's bitMap*/
 Handle iconData;					/*the icon's data*/
 short iconMaskData[1];				/*icon's mask and BitMap data*/
};

typedef struct CIcon CIcon;
typedef CIcon *CIconPtr, **CIconHandle;

struct GammaTbl {
 short gVersion;					/*gamma version number*/
 short gType;						/*gamma data type*/
 short gFormulaSize;				/*Formula data size*/
 short gChanCnt;					/*number of channels of data*/
 short gDataCnt;					/*number of values/channel*/
 short gDataWidth;					/*bits/corrected value (data packed to next larger byte size)*/
 short gFormulaData[1];				/*data for formulas followed by gamma values*/
};

typedef struct GammaTbl GammaTbl;
typedef GammaTbl *GammaTblPtr, **GammaTblHandle;

struct ITab {
 long iTabSeed;						/*copy of CTSeed from source CTable*/
 short iTabRes;						/*bits/channel resolution of iTable*/
 unsigned char iTTable[1];			/*byte colortable index values*/
};

typedef struct ITab ITab;
typedef ITab *ITabPtr, **ITabHandle;

struct SProcRec {
 Handle nxtSrch;					/*SProcHndl Handle to next SProcRec*/
 ColorSearchProcPtr srchProc;		/*pointer to search procedure*/
};

typedef struct SProcRec SProcRec;
typedef SProcRec *SProcPtr, **SProcHndl;

struct CProcRec {
 Handle nxtComp;					/*CProcHndl Handle to next CProcRec*/
 ColorComplementProcPtr compProc;	/*pointer to complement procedure*/
};

typedef struct CProcRec CProcRec;
typedef CProcRec *CProcPtr, **CProcHndl;

struct GDevice {
 short gdRefNum;					/*driver's unit number*/
 short gdID;						/*client ID for search procs*/
 short gdType;						/*fixed/CLUT/direct*/
 ITabHandle gdITable;				/*Handle to inverse lookup table*/
 short gdResPref;					/*preferred resolution of GDITable*/
 SProcHndl gdSearchProc;			/*search proc list head*/
 CProcHndl gdCompProc;				/*complement proc list*/
 short gdFlags;						/*grafDevice flags word*/
 PixMapHandle gdPMap;				/*describing pixMap*/
 long gdRefCon;						/*reference value*/
 Handle gdNextGD;					/*GDHandle Handle of next gDevice*/
 Rect gdRect;						/* device's bounds in global coordinates*/
 long gdMode;						/*device's current mode*/
 short gdCCBytes;					/*depth of expanded cursor data*/
 short gdCCDepth;					/*depth of expanded cursor data*/
 Handle gdCCXData;					/*Handle to cursor's expanded data*/
 Handle gdCCXMask;					/*Handle to cursor's expanded mask*/
 long gdReserved;					/*future use. MUST BE 0*/
};

typedef struct GDevice GDevice;
typedef GDevice *GDPtr, **GDHandle;

struct GrafVars {
 RGBColor rgbOpColor;				/*color for addPin  subPin and average*/
 RGBColor rgbHiliteColor;			/*color for hiliting*/
 Handle pmFgColor;					/*palette Handle for foreground color*/
 short pmFgIndex;					/*index value for foreground*/
 Handle pmBkColor;					/*palette Handle for background color*/
 short pmBkIndex;					/*index value for background*/
 short pmFlags;						/*flags for Palette Manager*/
};

typedef struct GrafVars GrafVars;
typedef GrafVars *GVarPtr, **GVarHandle;

struct CQDProcs {
 Ptr textProc;
 Ptr lineProc;
 Ptr rectProc;
 Ptr rRectProc;
 Ptr ovalProc;
 Ptr arcProc;
 Ptr polyProc;
 Ptr rgnProc;
 Ptr bitsProc;
 Ptr commentProc;
 Ptr txMeasProc;
 Ptr getPicProc;
 Ptr putPicProc;
 Ptr opcodeProc;					/*fields added to QDProcs*/
 Ptr newProc1;
 Ptr newProc2;
 Ptr newProc3;
 Ptr newProc4;
 Ptr newProc5;
 Ptr newProc6;
};

typedef struct CQDProcs CQDProcs;
typedef CQDProcs *CQDProcsPtr;

struct CGrafPort {
 short device;
 PixMapHandle portPixMap;			/*port's pixel map*/
 short portVersion;					/*high 2 bits always set*/
 Handle grafVars;					/*Handle to more fields*/
 short chExtra;						/*character extra*/
 short pnLocHFrac;					/*pen fraction*/
 Rect portRect;
 RgnHandle visRgn;
 RgnHandle clipRgn;
 PixPatHandle bkPixPat;				/*background pattern*/
 RGBColor rgbFgColor;				/*RGB components of fg*/
 RGBColor rgbBkColor;				/*RGB components of bk*/
 Point pnLoc;
 Point pnSize;
 short pnMode;
 PixPatHandle pnPixPat;				/*pen's pattern*/
 PixPatHandle fillPixPat;			/*fill pattern*/
 short pnVis;
 short txFont;
 Style txFace;						/*txFace is unpacked byte  push as short*/
 char filler;
 short txMode;
 short txSize;
 Fixed spExtra;
 long fgColor;
 long bkColor;
 short colrBit;
 short patStretch;
 Handle picSave;
 Handle rgnSave;
 Handle polySave;
 CQDProcsPtr grafProcs;
};

typedef struct CGrafPort CGrafPort;
typedef CGrafPort *CGrafPtr;


typedef CGrafPtr CWindowPtr;

struct ReqListRec {
 short reqLSize;					/*request list size*/
 short reqLData[1];					/*request list data*/
};

typedef struct ReqListRec ReqListRec;

struct OpenCPicParams {
 Rect srcRect;
 Fixed hRes;
 Fixed vRes;
 short version;
 short reserved1;
 long reserved2;
};

typedef struct OpenCPicParams OpenCPicParams;


typedef pascal void (*DeviceLoopDrawingProcPtr)(short depth, short deviceFlags, GDHandle targetDevice,  long userData);




extern struct  {
char privates[76];
long randSeed;
BitMap screenBits;
Cursor arrow;
Pattern dkGray;
Pattern ltGray;
Pattern gray;
Pattern black;
Pattern white;
GrafPtr thePort;
}qd;


#ifdef __cplusplus
extern "C" {
#endif

pascal void InitGraf(void *globalPtr)
 = {__GenToolboxTrapCode(0xA86E)}; 
pascal void OpenPort(GrafPtr port)
 = {__GenToolboxTrapCode(0xA86F)}; 
pascal void InitPort(GrafPtr port)
 = {__GenToolboxTrapCode(0xA86D)}; 
pascal void ClosePort(GrafPtr port)
 = {__GenToolboxTrapCode(0xA87D)}; 
pascal void SetPort(GrafPtr port)
 = {__GenToolboxTrapCode(0xA873)}; 
pascal void GetPort(GrafPtr *port)
 = {__GenToolboxTrapCode(0xA874)}; 
pascal void GrafDevice(short device)
 = {__GenToolboxTrapCode(0xA872)}; 
pascal void SetPortBits(const BitMap *bm)
 = {__GenToolboxTrapCode(0xA875)}; 
pascal void PortSize(short width,short height)
 = {__GenToolboxTrapCode(0xA876)}; 
pascal void MovePortTo(short leftGlobal,short topGlobal)
 = {__GenToolboxTrapCode(0xA877)}; 
pascal void SetOrigin(short h,short v)
 = {__GenToolboxTrapCode(0xA878)}; 
pascal void SetClip(RgnHandle rgn)
 = {__GenToolboxTrapCode(0xA879)}; 
pascal void GetClip(RgnHandle rgn)
 = {__GenToolboxTrapCode(0xA87A)}; 
pascal void ClipRect(const Rect *r)
 = {__GenToolboxTrapCode(0xA87B)}; 
pascal void BackPat(ConstPatternParam pat)
 = {__GenToolboxTrapCode(0xA87C)}; 
pascal void InitCursor(void)
 = {__GenToolboxTrapCode(0xA850)}; 
pascal void SetCursor(const Cursor *crsr)
 = {__GenToolboxTrapCode(0xA851)}; 
pascal void HideCursor(void)
 = {__GenToolboxTrapCode(0xA852)}; 
pascal void ShowCursor(void)
 = {__GenToolboxTrapCode(0xA853)}; 
pascal void ObscureCursor(void)
 = {__GenToolboxTrapCode(0xA856)}; 
pascal void HidePen(void)
 = {__GenToolboxTrapCode(0xA896)}; 
pascal void ShowPen(void)
 = {__GenToolboxTrapCode(0xA897)}; 
pascal void GetPen(Point *pt)
 = {__GenToolboxTrapCode(0xA89A)}; 
pascal void GetPenState(PenState *pnState)
 = {__GenToolboxTrapCode(0xA898)}; 
pascal void SetPenState(const PenState *pnState)
 = {__GenToolboxTrapCode(0xA899)}; 
pascal void PenSize(short width,short height)
 = {__GenToolboxTrapCode(0xA89B)}; 
pascal void PenMode(short mode)
 = {__GenToolboxTrapCode(0xA89C)}; 
pascal void PenPat(ConstPatternParam pat)
 = {__GenToolboxTrapCode(0xA89D)}; 
pascal void PenNormal(void)
 = {__GenToolboxTrapCode(0xA89E)}; 
pascal void MoveTo(short h,short v)
 = {__GenToolboxTrapCode(0xA893)}; 
pascal void Move(short dh,short dv)
 = {__GenToolboxTrapCode(0xA894)}; 
pascal void LineTo(short h,short v)
 = {__GenToolboxTrapCode(0xA891)}; 
pascal void Line(short dh,short dv)
 = {__GenToolboxTrapCode(0xA892)}; 
pascal void ForeColor(long color)
 = {__GenToolboxTrapCode(0xA862)}; 
pascal void BackColor(long color)
 = {__GenToolboxTrapCode(0xA863)}; 
pascal void ColorBit(short whichBit)
 = {__GenToolboxTrapCode(0xA864)}; 
pascal void SetRect(Rect *r,short left,short top,short right,short bottom)
 = {__GenToolboxTrapCode(0xA8A7)}; 
pascal void OffsetRect(Rect *r,short dh,short dv)
 = {__GenToolboxTrapCode(0xA8A8)}; 
pascal void InsetRect(Rect *r,short dh,short dv)
 = {__GenToolboxTrapCode(0xA8A9)}; 
pascal Boolean SectRect(const Rect *src1,const Rect *src2,Rect *dstRect)
 = {__GenToolboxTrapCode(0xA8AA)}; 
pascal void UnionRect(const Rect *src1,const Rect *src2,Rect *dstRect)
 = {__GenToolboxTrapCode(0xA8AB)}; 
pascal Boolean EqualRect(const Rect *rect1,const Rect *rect2)
 = {__GenToolboxTrapCode(0xA8A6)}; 
pascal Boolean EmptyRect(const Rect *r)
 = {__GenToolboxTrapCode(0xA8AE)}; 
pascal void FrameRect(const Rect *r)
 = {__GenToolboxTrapCode(0xA8A1)}; 
pascal void PaintRect(const Rect *r)
 = {__GenToolboxTrapCode(0xA8A2)}; 
pascal void EraseRect(const Rect *r)
 = {__GenToolboxTrapCode(0xA8A3)}; 
pascal void InvertRect(const Rect *r)
 = {__GenToolboxTrapCode(0xA8A4)}; 
pascal void FillRect(const Rect *r,ConstPatternParam pat)
 = {__GenToolboxTrapCode(0xA8A5)}; 
pascal void FrameOval(const Rect *r)
 = {__GenToolboxTrapCode(0xA8B7)}; 
pascal void PaintOval(const Rect *r)
 = {__GenToolboxTrapCode(0xA8B8)}; 
pascal void EraseOval(const Rect *r)
 = {__GenToolboxTrapCode(0xA8B9)}; 
pascal void InvertOval(const Rect *r)
 = {__GenToolboxTrapCode(0xA8BA)}; 
pascal void FillOval(const Rect *r,ConstPatternParam pat)
 = {__GenToolboxTrapCode(0xA8BB)}; 
pascal void FrameRoundRect(const Rect *r,short ovalWidth,short ovalHeight)
 = {__GenToolboxTrapCode(0xA8B0)}; 
pascal void PaintRoundRect(const Rect *r,short ovalWidth,short ovalHeight)
 = {__GenToolboxTrapCode(0xA8B1)}; 
pascal void EraseRoundRect(const Rect *r,short ovalWidth,short ovalHeight)
 = {__GenToolboxTrapCode(0xA8B2)}; 
pascal void InvertRoundRect(const Rect *r,short ovalWidth,short ovalHeight)
 = {__GenToolboxTrapCode(0xA8B3)}; 
pascal void FillRoundRect(const Rect *r,short ovalWidth,short ovalHeight,
 ConstPatternParam pat)
 = {__GenToolboxTrapCode(0xA8B4)}; 
pascal void FrameArc(const Rect *r,short startAngle,short arcAngle)
 = {__GenToolboxTrapCode(0xA8BE)}; 
pascal void PaintArc(const Rect *r,short startAngle,short arcAngle)
 = {__GenToolboxTrapCode(0xA8BF)}; 
pascal void EraseArc(const Rect *r,short startAngle,short arcAngle)
 = {__GenToolboxTrapCode(0xA8C0)}; 
pascal void InvertArc(const Rect *r,short startAngle,short arcAngle)
 = {__GenToolboxTrapCode(0xA8C1)}; 
pascal void FillArc(const Rect *r,short startAngle,short arcAngle,ConstPatternParam pat)
 = {__GenToolboxTrapCode(0xA8C2)}; 
pascal RgnHandle NewRgn(void)
 = {__GenToolboxTrapCode(0xA8D8)}; 
pascal void OpenRgn(void)
 = {__GenToolboxTrapCode(0xA8DA)}; 
pascal void CloseRgn(RgnHandle dstRgn)
 = {__GenToolboxTrapCode(0xA8DB)}; 
pascal OSErr BitMapToRegionGlue(RgnHandle region,const BitMap *bMap); 
pascal OSErr BitMapToRegion(RgnHandle region,const BitMap *bMap)
 = {__GenToolboxTrapCode(0xA8D7)}; 
pascal void DisposeRgn(RgnHandle rgn)
 = {__GenToolboxTrapCode(0xA8D9)}; 
pascal void CopyRgn(RgnHandle srcRgn,RgnHandle dstRgn)
 = {__GenToolboxTrapCode(0xA8DC)}; 
pascal void SetEmptyRgn(RgnHandle rgn)
 = {__GenToolboxTrapCode(0xA8DD)}; 
pascal void SetRectRgn(RgnHandle rgn,short left,short top,short right,short bottom)
 = {__GenToolboxTrapCode(0xA8DE)}; 
pascal void RectRgn(RgnHandle rgn,const Rect *r)
 = {__GenToolboxTrapCode(0xA8DF)}; 
pascal void OffsetRgn(RgnHandle rgn,short dh,short dv)
 = {__GenToolboxTrapCode(0xA8E0)}; 
pascal void InsetRgn(RgnHandle rgn,short dh,short dv)
 = {__GenToolboxTrapCode(0xA8E1)}; 
pascal void SectRgn(RgnHandle srcRgnA,RgnHandle srcRgnB,RgnHandle dstRgn)
 = {__GenToolboxTrapCode(0xA8E4)}; 
pascal void UnionRgn(RgnHandle srcRgnA,RgnHandle srcRgnB,RgnHandle dstRgn)
 = {__GenToolboxTrapCode(0xA8E5)}; 
pascal void DiffRgn(RgnHandle srcRgnA,RgnHandle srcRgnB,RgnHandle dstRgn)
 = {__GenToolboxTrapCode(0xA8E6)}; 
pascal void XorRgn(RgnHandle srcRgnA,RgnHandle srcRgnB,RgnHandle dstRgn)
 = {__GenToolboxTrapCode(0xA8E7)}; 
pascal Boolean RectInRgn(const Rect *r,RgnHandle rgn)
 = {__GenToolboxTrapCode(0xA8E9)}; 
pascal Boolean EqualRgn(RgnHandle rgnA,RgnHandle rgnB)
 = {__GenToolboxTrapCode(0xA8E3)}; 
pascal Boolean EmptyRgn(RgnHandle rgn)
 = {__GenToolboxTrapCode(0xA8E2)}; 
pascal void FrameRgn(RgnHandle rgn)
 = {__GenToolboxTrapCode(0xA8D2)}; 
pascal void PaintRgn(RgnHandle rgn)
 = {__GenToolboxTrapCode(0xA8D3)}; 
pascal void EraseRgn(RgnHandle rgn)
 = {__GenToolboxTrapCode(0xA8D4)}; 
pascal void InvertRgn(RgnHandle rgn)
 = {__GenToolboxTrapCode(0xA8D5)}; 
pascal void FillRgn(RgnHandle rgn,ConstPatternParam pat)
 = {__GenToolboxTrapCode(0xA8D6)}; 
pascal void ScrollRect(const Rect *r,short dh,short dv,RgnHandle updateRgn)
 = {__GenToolboxTrapCode(0xA8EF)}; 
pascal void CopyBits(const BitMap *srcBits,const BitMap *dstBits,const Rect *srcRect,
 const Rect *dstRect,short mode,RgnHandle maskRgn)
 = {__GenToolboxTrapCode(0xA8EC)}; 
pascal void SeedFill(const void *srcPtr,void *dstPtr,short srcRow,short dstRow,
 short height,short words,short seedH,short seedV)
 = {__GenToolboxTrapCode(0xA839)}; 
pascal void CalcMask(const void *srcPtr,void *dstPtr,short srcRow,short dstRow,
 short height,short words)
 = {__GenToolboxTrapCode(0xA838)}; 
pascal void CopyMask(const BitMap *srcBits,const BitMap *maskBits,const BitMap *dstBits,
 const Rect *srcRect,const Rect *maskRect,const Rect *dstRect)
 = {__GenToolboxTrapCode(0xA817)}; 
pascal PicHandle OpenPicture(const Rect *picFrame)
 = {__GenToolboxTrapCode(0xA8F3)}; 
pascal void PicComment(short kind,short dataSize,Handle dataHandle)
 = {__GenToolboxTrapCode(0xA8F2)}; 
pascal void ClosePicture(void)
 = {__GenToolboxTrapCode(0xA8F4)}; 
pascal void DrawPicture(PicHandle myPicture,const Rect *dstRect)
 = {__GenToolboxTrapCode(0xA8F6)}; 
pascal void KillPicture(PicHandle myPicture)
 = {__GenToolboxTrapCode(0xA8F5)}; 
pascal PolyHandle OpenPoly(void)
 = {__GenToolboxTrapCode(0xA8CB)}; 
pascal void ClosePoly(void)
 = {__GenToolboxTrapCode(0xA8CC)}; 
pascal void KillPoly(PolyHandle poly)
 = {__GenToolboxTrapCode(0xA8CD)}; 
pascal void OffsetPoly(PolyHandle poly,short dh,short dv)
 = {__GenToolboxTrapCode(0xA8CE)}; 
pascal void FramePoly(PolyHandle poly)
 = {__GenToolboxTrapCode(0xA8C6)}; 
pascal void PaintPoly(PolyHandle poly)
 = {__GenToolboxTrapCode(0xA8C7)}; 
pascal void ErasePoly(PolyHandle poly)
 = {__GenToolboxTrapCode(0xA8C8)}; 
pascal void InvertPoly(PolyHandle poly)
 = {__GenToolboxTrapCode(0xA8C9)}; 
pascal void FillPoly(PolyHandle poly,ConstPatternParam pat)
 = {__GenToolboxTrapCode(0xA8CA)}; 
pascal void SetPt(Point *pt,short h,short v)
 = {__GenToolboxTrapCode(0xA880)}; 
pascal void LocalToGlobal(Point *pt)
 = {__GenToolboxTrapCode(0xA870)}; 
pascal void GlobalToLocal(Point *pt)
 = {__GenToolboxTrapCode(0xA871)}; 
pascal short Random(void)
 = {__GenToolboxTrapCode(0xA861)}; 
pascal void StuffHex(void *thingPtr,ConstStr255Param s)
 = {__GenToolboxTrapCode(0xA866)}; 
pascal Boolean GetPixel(short h,short v)
 = {__GenToolboxTrapCode(0xA865)}; 
pascal void ScalePt(Point *pt,const Rect *srcRect,const Rect *dstRect)
 = {__GenToolboxTrapCode(0xA8F8)}; 
pascal void MapPt(Point *pt,const Rect *srcRect,const Rect *dstRect)
 = {__GenToolboxTrapCode(0xA8F9)}; 
pascal void MapRect(Rect *r,const Rect *srcRect,const Rect *dstRect)
 = {__GenToolboxTrapCode(0xA8FA)}; 
pascal void MapRgn(RgnHandle rgn,const Rect *srcRect,const Rect *dstRect)
 = {__GenToolboxTrapCode(0xA8FB)}; 
pascal void MapPoly(PolyHandle poly,const Rect *srcRect,const Rect *dstRect)
 = {__GenToolboxTrapCode(0xA8FC)}; 
pascal void SetStdProcs(QDProcs *procs)
 = {__GenToolboxTrapCode(0xA8EA)}; 
pascal void StdRect(GrafVerb verb,const Rect *r)
 = {__GenToolboxTrapCode(0xA8A0)}; 
pascal void StdRRect(GrafVerb verb,const Rect *r,short ovalWidth,short ovalHeight)
 = {__GenToolboxTrapCode(0xA8AF)}; 
pascal void StdOval(GrafVerb verb,const Rect *r)
 = {__GenToolboxTrapCode(0xA8B6)}; 
pascal void StdArc(GrafVerb verb,const Rect *r,short startAngle,short arcAngle)
 = {__GenToolboxTrapCode(0xA8BD)}; 
pascal void StdPoly(GrafVerb verb,PolyHandle poly)
 = {__GenToolboxTrapCode(0xA8C5)}; 
pascal void StdRgn(GrafVerb verb,RgnHandle rgn)
 = {__GenToolboxTrapCode(0xA8D1)}; 
pascal void StdBits(const BitMap *srcBits,const Rect *srcRect,const Rect *dstRect,
 short mode,RgnHandle maskRgn)
 = {__GenToolboxTrapCode(0xA8EB)}; 
pascal void StdComment(short kind,short dataSize,Handle dataHandle)
 = {__GenToolboxTrapCode(0xA8F1)}; 
pascal void StdGetPic(void *dataPtr,short byteCount)
 = {__GenToolboxTrapCode(0xA8EE)}; 
pascal void StdPutPic(const void *dataPtr,short byteCount)
 = {__GenToolboxTrapCode(0xA8F0)}; 
pascal void AddPt(Point src,Point *dst)
 = {__GenToolboxTrapCode(0xA87E)}; 
void subpt(Point *src,Point *dst); 
pascal Boolean EqualPt(Point pt1,Point pt2)
 = {__GenToolboxTrapCode(0xA881)}; 
pascal Boolean PtInRect(Point pt,const Rect *r)
 = {__GenToolboxTrapCode(0xA8AD)}; 
pascal void Pt2Rect(Point pt1,Point pt2,Rect *dstRect)
 = {__GenToolboxTrapCode(0xA8AC)}; 
pascal void PtToAngle(const Rect *r,Point pt,short *angle)
 = {__GenToolboxTrapCode(0xA8C3)}; 
pascal Boolean PtInRgn(Point pt,RgnHandle rgn)
 = {__GenToolboxTrapCode(0xA8E8)}; 
pascal void StdLine(Point newPt)
 = {__GenToolboxTrapCode(0xA890)}; 
pascal void OpenCPort(CGrafPtr port)
 = {__GenToolboxTrapCode(0xAA00)}; 
pascal void InitCPort(CGrafPtr port)
 = {__GenToolboxTrapCode(0xAA01)}; 
pascal void CloseCPort(CGrafPtr port)
 = {__GenToolboxTrapCode(0xA87D)}; 
pascal PixMapHandle NewPixMap(void)
 = {__GenToolboxTrapCode(0xAA03)}; 
pascal void DisposPixMap(PixMapHandle pm)
 = {__GenToolboxTrapCode(0xAA04)}; 
pascal void DisposePixMap(PixMapHandle pm)
 = {__GenToolboxTrapCode(0xAA04)}; 
pascal void CopyPixMap(PixMapHandle srcPM,PixMapHandle dstPM)
 = {__GenToolboxTrapCode(0xAA05)}; 
pascal PixPatHandle NewPixPat(void)
 = {__GenToolboxTrapCode(0xAA07)}; 
pascal void DisposPixPat(PixPatHandle pp)
 = {__GenToolboxTrapCode(0xAA08)}; 
pascal void DisposePixPat(PixPatHandle pp)
 = {__GenToolboxTrapCode(0xAA08)}; 
pascal void CopyPixPat(PixPatHandle srcPP,PixPatHandle dstPP)
 = {__GenToolboxTrapCode(0xAA09)}; 
pascal void PenPixPat(PixPatHandle pp)
 = {__GenToolboxTrapCode(0xAA0A)}; 
pascal void BackPixPat(PixPatHandle pp)
 = {__GenToolboxTrapCode(0xAA0B)}; 
pascal PixPatHandle GetPixPat(short patID)
 = {__GenToolboxTrapCode(0xAA0C)}; 
pascal void MakeRGBPat(PixPatHandle pp,const RGBColor *myColor)
 = {__GenToolboxTrapCode(0xAA0D)}; 
pascal void FillCRect(const Rect *r,PixPatHandle pp)
 = {__GenToolboxTrapCode(0xAA0E)}; 
pascal void FillCOval(const Rect *r,PixPatHandle pp)
 = {__GenToolboxTrapCode(0xAA0F)}; 
pascal void FillCRoundRect(const Rect *r,short ovalWidth,short ovalHeight,
 PixPatHandle pp)
 = {__GenToolboxTrapCode(0xAA10)}; 
pascal void FillCArc(const Rect *r,short startAngle,short arcAngle,PixPatHandle pp)
 = {__GenToolboxTrapCode(0xAA11)}; 
pascal void FillCRgn(RgnHandle rgn,PixPatHandle pp)
 = {__GenToolboxTrapCode(0xAA12)}; 
pascal void FillCPoly(PolyHandle poly,PixPatHandle pp)
 = {__GenToolboxTrapCode(0xAA13)}; 
pascal void RGBForeColor(const RGBColor *color)
 = {__GenToolboxTrapCode(0xAA14)}; 
pascal void RGBBackColor(const RGBColor *color)
 = {__GenToolboxTrapCode(0xAA15)}; 
pascal void SetCPixel(short h,short v,const RGBColor *cPix)
 = {__GenToolboxTrapCode(0xAA16)}; 
pascal void SetPortPix(PixMapHandle pm)
 = {__GenToolboxTrapCode(0xAA06)}; 
pascal void GetCPixel(short h,short v,RGBColor *cPix)
 = {__GenToolboxTrapCode(0xAA17)}; 
pascal void GetForeColor(RGBColor *color)
 = {__GenToolboxTrapCode(0xAA19)}; 
pascal void GetBackColor(RGBColor *color)
 = {__GenToolboxTrapCode(0xAA1A)}; 
pascal void SeedCFill(const BitMap *srcBits,const BitMap *dstBits,const Rect *srcRect,
 const Rect *dstRect,short seedH,short seedV,ColorSearchProcPtr matchProc,
 long matchData)
 = {__GenToolboxTrapCode(0xAA50)}; 
pascal void CalcCMask(const BitMap *srcBits,const BitMap *dstBits,const Rect *srcRect,
 const Rect *dstRect,const RGBColor *seedRGB,ColorSearchProcPtr matchProc,
 long matchData)
 = {__GenToolboxTrapCode(0xAA4F)}; 
pascal PicHandle OpenCPicture(const OpenCPicParams *newHeader)
 = {__GenToolboxTrapCode(0xAA20)}; 
pascal void OpColor(const RGBColor *color)
 = {__GenToolboxTrapCode(0xAA21)}; 
pascal void HiliteColor(const RGBColor *color)
 = {__GenToolboxTrapCode(0xAA22)}; 
pascal void DisposCTable(CTabHandle cTable)
 = {__GenToolboxTrapCode(0xAA24)}; 
pascal void DisposeCTable(CTabHandle cTable)
 = {__GenToolboxTrapCode(0xAA24)}; 
pascal CTabHandle GetCTable(short ctID)
 = {__GenToolboxTrapCode(0xAA18)}; 
pascal CCrsrHandle GetCCursor(short crsrID)
 = {__GenToolboxTrapCode(0xAA1B)}; 
pascal void SetCCursor(CCrsrHandle cCrsr)
 = {__GenToolboxTrapCode(0xAA1C)}; 
pascal void AllocCursor(void)
 = {__GenToolboxTrapCode(0xAA1D)}; 
pascal void DisposCCursor(CCrsrHandle cCrsr)
 = {__GenToolboxTrapCode(0xAA26)}; 
pascal void DisposeCCursor(CCrsrHandle cCrsr)
 = {__GenToolboxTrapCode(0xAA26)}; 
pascal CIconHandle GetCIcon(short iconID)
 = {__GenToolboxTrapCode(0xAA1E)}; 
pascal void PlotCIcon(const Rect *theRect,CIconHandle theIcon)
 = {__GenToolboxTrapCode(0xAA1F)}; 
pascal void DisposCIcon(CIconHandle theIcon)
 = {__GenToolboxTrapCode(0xAA25)}; 
pascal void DisposeCIcon(CIconHandle theIcon)
 = {__GenToolboxTrapCode(0xAA25)}; 
pascal void SetStdCProcs(CQDProcs *procs)
 = {__GenToolboxTrapCode(0xAA4E)}; 
pascal GDHandle GetMaxDevice(const Rect *globalRect)
 = {__GenToolboxTrapCode(0xAA27)}; 
pascal long GetCTSeed(void)
 = {__GenToolboxTrapCode(0xAA28)}; 
pascal GDHandle GetDeviceList(void)
 = {__GenToolboxTrapCode(0xAA29)}; 
pascal GDHandle GetMainDevice(void)
 = {__GenToolboxTrapCode(0xAA2A)}; 
pascal GDHandle GetNextDevice(GDHandle curDevice)
 = {__GenToolboxTrapCode(0xAA2B)}; 
pascal Boolean TestDeviceAttribute(GDHandle gdh,short attribute)
 = {__GenToolboxTrapCode(0xAA2C)}; 
pascal void SetDeviceAttribute(GDHandle gdh,short attribute,Boolean value)
 = {__GenToolboxTrapCode(0xAA2D)}; 
pascal void InitGDevice(short qdRefNum,long mode,GDHandle gdh)
 = {__GenToolboxTrapCode(0xAA2E)}; 
pascal GDHandle NewGDevice(short refNum,long mode)
 = {__GenToolboxTrapCode(0xAA2F)}; 
pascal void DisposGDevice(GDHandle gdh)
 = {__GenToolboxTrapCode(0xAA30)}; 
pascal void DisposeGDevice(GDHandle gdh)
 = {__GenToolboxTrapCode(0xAA30)}; 
pascal void SetGDevice(GDHandle gd)
 = {__GenToolboxTrapCode(0xAA31)}; 
pascal GDHandle GetGDevice(void)
 = {__GenToolboxTrapCode(0xAA32)}; 
pascal long Color2Index(const RGBColor *myColor)
 = {__GenToolboxTrapCode(0xAA33)}; 
pascal void Index2Color(long index,RGBColor *aColor)
 = {__GenToolboxTrapCode(0xAA34)}; 
pascal void InvertColor(RGBColor *myColor)
 = {__GenToolboxTrapCode(0xAA35)}; 
pascal Boolean RealColor(const RGBColor *color)
 = {__GenToolboxTrapCode(0xAA36)}; 
pascal void GetSubTable(CTabHandle myColors,short iTabRes,CTabHandle targetTbl)
 = {__GenToolboxTrapCode(0xAA37)}; 
pascal void MakeITable(CTabHandle cTabH,ITabHandle iTabH,short res)
 = {__GenToolboxTrapCode(0xAA39)}; 
pascal void AddSearch(ColorSearchProcPtr searchProc)
 = {__GenToolboxTrapCode(0xAA3A)}; 
pascal void AddComp(ColorComplementProcPtr compProc)
 = {__GenToolboxTrapCode(0xAA3B)}; 
pascal void DelSearch(ColorSearchProcPtr searchProc)
 = {__GenToolboxTrapCode(0xAA4C)}; 
pascal void DelComp(ColorComplementProcPtr compProc)
 = {__GenToolboxTrapCode(0xAA4D)}; 
pascal void SubPt(Point src,Point *dst)
 = {__GenToolboxTrapCode(0xA87F)}; 
pascal void SetClientID(short id)
 = {__GenToolboxTrapCode(0xAA3C)}; 
pascal void ProtectEntry(short index,Boolean protect)
 = {__GenToolboxTrapCode(0xAA3D)}; 
Boolean equalpt(Point *pt1,Point *pt2); 
pascal void ReserveEntry(short index,Boolean reserve)
 = {__GenToolboxTrapCode(0xAA3E)}; 
pascal void SetEntries(short start,short count,CSpecArray aTable)
 = {__GenToolboxTrapCode(0xAA3F)}; 
Boolean ptinrect(Point *pt,const Rect *r); 
pascal void SaveEntries(CTabHandle srcTable,CTabHandle resultTable,ReqListRec *selection)
 = {__GenToolboxTrapCode(0xAA49)}; 
pascal void RestoreEntries(CTabHandle srcTable,CTabHandle dstTable,ReqListRec *selection)
 = {__GenToolboxTrapCode(0xAA4A)}; 
void pt2rect(Point *pt1,Point *pt2,const Rect *destRect); 
pascal short QDError(void)
 = {__GenToolboxTrapCode(0xAA40)}; 
pascal void CopyDeepMask(const BitMap *srcBits,const BitMap *maskBits,const BitMap *dstBits,
 const Rect *srcRect,const Rect *maskRect,const Rect *dstRect,short mode,
 RgnHandle maskRgn)
 = {__GenToolboxTrapCode(0xAA51)}; 
pascal void DeviceLoop(RgnHandle drawingRgn,DeviceLoopDrawingProcPtr drawingProc,
 long userData,DeviceLoopFlags flags)
 = {__GenToolboxTrapCode(0xABCA)}; 
#pragma parameter __A0 GetMaskTable
pascal Ptr GetMaskTable(void)
 = {__GenToolboxTrapCode(0xA836)}; 
void pttoangle(const Rect *r,Point *pt,short *angle); 
Boolean ptinrgn(Point *pt,RgnHandle rgn); 
void stdline(Point *newPt); 
void drawstring(char *s); 
void addpt(Point *src,Point *dst); 
void stuffhex(Ptr thingPtr,char *s); 
short stringwidth(char *s);


#ifdef __cplusplus
}
#endif

#endif
