// Version: 2.26
// Created: Wednesday, July 12, 1989 at 1:35:29 PM
//
// File: Quickdraw.a
//
// Assembler Interface to the Macintosh Libraries
// Copyright Apple Computer, Inc. 1984-1992
// All Rights Reserved
//
//   Change History (most recent first):
//
//      <SM3>     7/7/92     CSS     Roll in the following changes from reality and rename this
//                                   file from QuickEqu.a to QuickDraw.a per <23>.
//       <25>      7/6/92    KON     No longer need bits 5 and 6 in gdFlags. Move bit 4 to bit 6.
//       <24>     6/30/92    KON     Add three new gdFlags: Bit 4 hasAuxMenuBar, Bit 5
//                                   pixelsAreSlewSlow, and Bit 6 whiteIsOff.
//       <23>     6/30/92    DCL     This file is the replacement for the now obsolete QuickEqu.a.
//                                   Changed the 'including' name to match the new file name.
//      <SM2>      6/4/92    KW      (fau,P2) Added XColorSpec to support the alpha channel on
//                                   Cyclone.  KW commented out value,rgb to prevent warning
//       <22>     6/14/91    JL      Checked in official MPW 3.2ƒ version. Moved the color manager
//                                   equates; they were in the middle of GrafPort.
//       <21>     1/30/91    gbm     sab, #38: Change the ‘already including this file’ variable to
//                                   all uppercase (for security reasons)
//       <20>     1/20/91    JT      Removed the change to pnLocFixed since Peter was unhappy about
//                                   it. This fix will have to wait for some future release.
//       <19>     1/18/91    JT      Expand pnLocFixed into a full fixed-point number in the
//                                   QuickDraw globals area.
//       <18>    12/14/90    KON     Change name of PICT2Header to OpenCPicParams.[smc]
//       <17>     9/24/90    KON     Fix Pict2Header record.
//       <16>     9/15/90    KON     Added PICT2Header record.
//       <15>     9/14/90    csd     Added equates for the DeviceLoop call.
//       <14>     8/26/90    PKE     Deleted old names QDSmgrSlop and QDSmgrCharExtra.
//       <13>     8/23/90    PKE     (per JT) Renamed QDSmgrSlop and QDSmgrCharExtra to qdRunSlop and
//                                   qdChExtra. Keep old names too until we can update all relevant
//                                   sources.
//       <12>     8/17/90    dvb     Change grayishTextCopy to grayishTextOr
//       <11>      8/2/90    PKE     Claim two previously unused longs in fontData globals for Script
//                                   Mgr charExtra and slop.
//       <10>     7/17/90    DVB     Add "GrayishTextCopy" mode.
//        <9>     5/30/90    JT      Claimed the first word of the fontData globals for the
//                                   horizontal pen fraction.
//        <8>     5/15/90    KON     Add equates for RGBDirect, baseAddr32, ditherCopy.
//        <4>      2/2/90    BAL     Moved 32-bit addressing flag and Burst mode flag down one in bit
//                                   ordering since monitors is already using bit 9 for a swapped out
//                                   debugger screen.
//        <3>     1/30/90    DAF     Added GDFlag bit flag equates for 32-bit addressable frame
//                                   buffers and block transfer capabilities.
//        <2>     1/11/90    DVB     Add the equate "ctFlags", which is the correct name of the
//                                   obsolete "transIndex" field of a color table.
//        <1>    12/17/89    CCH     Adding for the first time into BBS.
//      <1.1>     6/10/89    CEL     Moved Private.a QuickDraw Equates into proper QuickDraw private
//                                   file (colorequ.a), got rid of QuickDraw nFiles dependencies and
//                                   fixed up necessary files…
//      <1.0>     11/9/88    CCH     Adding to EASE.
//     <•1.1>     9/14/88    CCH     Updated EASE with the current rev of this file.
//                8/25/87    KLH     MatchRec restored, it is used.
//                 7/7/87    KLH     MatchRec removed, no longer used.
//                 7/2/87    KLH     mainScrn & scrnActive changed to mainScreen & screenActive
//                 5/8/87    KLH     protect changed to protectBit
//                3/16/87    KLH     pmNewFlag is same offset as pmRowBytes in PixMap record.
//     <C621>     1/13/87    DAF     Moved BadEntry equate in for colormgr and renamed it
//                                   invalColReq.
//     <C533>    12/15/86    DAF     added gamma table format
//     <C387>     11/9/86    DAF     added request list structure
//                9/23/86    NSJ     new this date
//
//   To Do:
//__________________________________________________________________________________________________

//EASE$$$ READ ONLY COPY of file “QuickEqu.a”
// 1.1   CEL 06/10/1989 Moved Private.a QuickDraw Equates into proper QuickDraw
//       private file (colorequ.a), got rid of QuickDraw nFiles dependencies
//       and fixed up necessary files…
// 1.0   CCH 11/ 9/1988 Adding to EASE.
// END EASE MODIFICATION HISTORY 
//•1.1   CCH 9/14/1988 Updated EASE with the current rev of this file.
//
// Modification history
//
// <23sep86> NSJ new this date
// <C387/09Nov86> DAF added request list structure
// <C533/15Dec86> DAF added gamma table format
// <C621/13Jan87> DAF Moved BadEntry equate in for colormgr and renamed it invalColReq.
// 16 Mar 87 KLH pmNewFlag is same offset as pmRowBytes in PixMap record.
// 8 May 87 KLH protect changed to protectBit
// 2 Jul 87 KLH mainScrn & scrnActive changed to mainScreen & screenActive
// to agree w/ screenDevice
// *** MPW 2.0 ***
// 7 Jul 87 KLH MatchRec removed, no longer used.
// 25 Aug 87 KLH MatchRec restored, it is used.
//--------------------------------------------------------------------

#ifndef __INCLUDINGQUICKDRAW__
#define __INCLUDINGQUICKDRAW__ 1

// Transfer modes

#define srcCopy                  0
#define srcOr                    1
#define srcXor                   2
#define srcBic                   3
#define notSrcCopy               4
#define notSrcOr                 5
#define notSrcXor                6
#define notSrcBic                7
#define patCopy                  8
#define patOr                    9
#define patXor                   10
#define patBic                   11
#define notPatCopy               12
#define notPatOr                 13
#define notPatXor                14
#define notPatBic                15

// Arithmetic transfer modes
#define blend                    32
#define addPin                   33
#define addOver                  34
#define subPin                   35
#define adMax                    37
#define subOver                  38
#define adMin                    39

// Special text mode
#define grayishTextOr            49

#define ditherCopy               64                      //promote source to 32-bit and then dither down

// Flags passed to DeviceLoop

#define singleDevicesBit         0
#define dontMatchSeedsBit        1
#define allDevicesBit            2

#define singleDevices            1
#define dontMatchSeeds           2
#define allDevices               4

// Definitions for Font Style Bits (right to left)

#define boldBit                  0

// Transparent mode constant
#define transparent              36
#define italicBit                1
#define ulineBit                 2
#define outlineBit               3
#define shadowBit                4
#define condenseBit              5
#define extendBit                6


// FontInfo record

#define ascent                   0                       // ascent [word]
#define descent                  2                       // descent [word]
#define widMax                   4                       // maximum width [word]
#define leading                  6                       // leading [word]

// Rectangle structure

#define topLeft                  0                       // upper left corner [point]
#define botRight                 4                       // lower right corner [point]
#define top                      0                       // top coordinate [word]
#define left                     2                       // left coordinate [word]
#define bottom                   4                       // bottom coordinate [word]
#define right                    6                       // right coordinate [word]

// Bitmap Structure

#define baseAddr                 0                       // bitmap base address [pointer]
#define rowBytes                 4                       // row bytes (must be even) [word]
#define bounds                   6                       // bounding box [rectangle]
#define bitmapRec                14                      // size of a bitmap

// Cursor Structure

//#define data                     0                       // visible bits [32 bytes]
#define mask                     $20                     // mask bits [32 bytes]
#define hotSpot                  $40                     // relative origin [point]
#define cursRec                  68                      // size of a cursor

// PenState record

#define psLoc                    0                       // pen location [point]
#define psSize                   4                       // pen size [point]
#define psMode                   8                       // pen mode [word]
#define psPat                    10                      // pen [pattern]
#define psRec                    18                      // size of pen state

// Polygon record

#define polySize                 0                       // total bytes [word]
#define polyBBox                 2                       // bounding box [rectangle]
#define polyPoints               10                      // vertices [Points]

// Region Structure

#define rgnSize                  0                       // total bytes [word]
#define rgnBBox                  2                       // bounding box [rectangle]
#define rgnData                  10                      // region data [array]

// Picture Structure

#define picSize                  0                       // total bytes [word]
#define picFrame                 2                       // bounding box [rectangle]
#define picData                  10                      // picture byte codes [array]

#define OpenCPicParams    0
#define OpenCPicParams_srcRect     0
#define OpenCPicParams_hRes        8
#define OpenCPicParams_vRes        12
#define OpenCPicParams_version     16
#define OpenCPicParams_reserved1   18
#define OpenCPicParams_reserved2   20
// endr OpenCPicParams
            
// QDProcs structure

#define textProc                 0                       // [pointer]
#define lineProc                 4                       // [pointer]
#define rectProc                 8                       // [pointer]
#define rRectProc                $C                      // [pointer]
#define ovalProc                 $10                     // [pointer]
#define arcProc                  $14                     // [pointer]
#define polyProc                 $18                     // [pointer]
#define rgnProc                  $1C                     // [pointer]
#define bitsProc                 $20                     // [pointer]
#define commentProc              $24                     // [pointer]
#define txMeasProc               $28                     // [pointer]
#define getPicProc               $2C                     // [pointer]
#define putPicProc               $30                     // [pointer]
#define qdProcsRec               $34                     // size of QDProcs record

// GrafPort Structure

#define device                   $0                      // device code [word]
#define portBits                 $2                      // port's bitmap [bitmap]
#define portBounds               $8                      // bounding box of bitmap [rect]
#define portRect                 $10                     // port's rectangle [rect]
#define visRgn                   $18                     // visible region [handle]
#define clipRgn                  $1C                     // clipping region [handle]
#define bkPat                    $20                     // background [pattern]
#define fillPat                  $28                     // fill [pattern]
#define pnLoc                    $30                     // pen location [point]
#define pnSize                   $34                     // pen size [point]
#define pnMode                   $38                     // pen mode [word]
#define pnPat                    $3A                     // pen [pattern]
#define pnVis                    $42                     // pen visible [word]
#define txFont                   $44                     // text font [word]
#define txFace                   $46                     // text face [word]
#define txMode                   $48                     // text mode [word]
#define txSize                   $4A                     // text size [word]
#define spExtra                  $4C                     // space extra [fixed]
#define fgColor                  $50                     // foreground color mask [long]
#define bkColor                  $54                     // background color mask [long]
#define colrBit                  $58                     // color bit [word]
#define patStretch               $5A                     // pattern stretch [word]
#define picSave                  $5C                     // picture being saved [handle]
#define rgnSave                  $60                     // region being saved [handle]
#define polySave                 $64                     // polygon being saved [handle]
#define grafProcs                $68                     // QDProcs array [pointer]
#define portRec                  $6C                     // size of grafport


// QuickDraw Global Variables


#define GrafGlobals              0                       // A5 offset to globptr
#define thePort                  0                       //GrafPtr
#define white                    (thePort-8)               //Pattern
#define black                    (white-8)                 //Pattern
#define gray                     (black-8)                 //Pattern
#define ltGray                   (gray-8)                  //Pattern
#define dkGray                   (ltGray-8)                //Pattern
#define arrow                    (dkGray-68)               //Cursor
#define screenBits               (arrow-14)                //BitMap
#define randSeed                 (screenBits-4)            //LONGINT

// color manager equates

// RGBColor structure

#define red                      $0                      //red channel intensity [short]
#define green                    $2                      //green channel intensity[short]
#define blue                     $4                      //blue channel intensity [short]
#define rgbColor                 $6                      //size of record

// ColorSpec structure

#define value                    $0                      //value field [short]
#define rgb                      $2                      //rgb values [rgbColor]
#define colorSpecSize            $8                      //size of record

// XColorSpec structure                              value,rgb commented out to prevent  <SM2>
                                                    //warning                            <SM2>

//value          EQU         $0                      ;value field [short]                <SM2>
//rgb            EQU         $2                      ;rgb values [rgbColor]              <SM2>
#define alpha                    $8
#define xColorSpecSize           $a                      //size of record                     <SM2>

// MatchRec structure

//red EQU $0 ;defined in RGBColor
//green EQU $2 ;defined in RGBColor
//blue EQU $4 ;defined in RGBColor
#define matchData                $6                      // [long]
#define matchRecSize             $A

// Color Separation

#define normalBit                0                       // normal screen mapping
#define inverseBit               1                       // inverse screen mapping
#define redBit                   4                       // RGB additive mapping
#define greenBit                 3                       // for photos from screen
#define blueBit                  2
#define cyanBit                  8                       // CMYBk subtractive mapping
#define yellowBit                6
#define magentaBit               7                       // for ink jet printer
#define blackBit                 5
#define blackColor               33
#define whiteColor               30
#define redColor                 205
#define greenColor               341
#define blueColor                409
#define cyanColor                273
#define magentaColor             137
#define yellowColor              69


// Standard Picture Comments

#define picLParen                0
#define picRParen                1

// QuickDraw verbs

#define frame                    0
#define paint                    1
#define erase                    2
#define invert                   3
#define fill                     4

// QuickDraw private global variables

#define wideOpen                 (randSeed-4)              //RgnHandle
#define wideMaster               (wideOpen-4)              //RgnPtr
#define wideData                 (wideMaster-10)           //Fake Region
#define rgnBuf                   (wideData-4)              //PointsHandle
#define rgnIndex                 (rgnBuf-2)                //INTEGER
#define rgnMax                   (rgnIndex-2)              //INTEGER
#define playPic                  (rgnMax-4)                //Long
#define qdSpare0                 (playPic-2)               //unused word
#define thePoly                  (qdSpare0-4)              //POLYHANDLE
#define polyMax                  (thePoly-2)               //INTEGER
#define patAlign                 (polyMax-4)               //Point
#define fontAdj                  (patAlign-4)              //Fixed Point
#define fontPtr                  (fontAdj-4)               //long, ^FMOutput record
#define playIndex                (fontPtr-4)               //long
#define pnLocFixed               (playIndex-2)             //word, horizontal pen fraction          <9>
#define qdRunSlop                (pnLocFixed-4)            //fixed point, Script Mgr run slop       <11><13>
#define qdChExtra                (qdRunSlop-4)             //fixed point, Script Mgr char extra     <11><13>
#define fontData                 (qdChExtra-12)            //unused words                           <9><11><13>
#define lastGrafGlob             (fontData)
#define grafSize                 (4-lastGrafGlob)          //total size in bytes

// A record version of the Quickdraw globals
// It is here rather than with the complementary equates because it needs other equates
// ...(bitmapRec, grafSize, cursRec)


//*********** THESE VALUES ARE WRONG. DON'T USE ///
//#define QDGlobals             0,DECREMENT
//#define QDGlobals_thePort         0
//#define QDGlobals_white           4
//#define QDGlobals_black           12
//#define QDGlobals_gray            20
//#define QDGlobals_ltGray          28
//#define QDGlobals_dkGray          36
//***CONFUSED***:arrow           DS.B        cursRec
//***CONFUSED***:screenBits      DS.B        bitmapRec
//#define QDGlobals_randSeed        44
//***CONFUSED***:                ORG         -grafSize
// endr QDGlobals
//*********************************************

//************** FROM HERE TO THE ENDIF IS ALL THE NEW STUFF FOR COLOR QUICKDRAW *************

#define hiliteBit                7                       // flag bit in HiliteMode (lowMem flag)

// Equates for resource ID's

#define defQDColors              127                     // resource ID of clut for default QDColors

//
// PixMap field offsets

#define pmBaseAddr               $0                      // [long]
#define pmNewFlag                $4                      // [1 bit] upper bit of rowbytes is flag
#define pmRowBytes               $4                      // [word]
#define pmBounds                 $6                      // [rect]
#define pmVersion                $E                      // [word] pixMap version number
#define pmPackType               $10                     // [word] defines packing format
#define pmPackSize               $12                     // [long] size of pixel data
#define pmHRes                   $16                     // [fixed] h. resolution (ppi)
#define pmVRes                   $1A                     // [fixed] v. resolution (ppi)
#define pmPixelType              $1E                     // [word] defines pixel type
#define pmPixelSize              $20                     // [word] # bits in pixel
#define pmCmpCount               $22                     // [word] # components in pixel
#define pmCmpSize                $24                     // [word] # bits per field
#define pmPlaneBytes             $26                     // [long] offset to next plane
#define pmTable                  $2A                     // [long] color map
#define pmReserved               $2E                     // [long] MUST BE 0
#define pmRec                    $32                     // size of pixMap record

// pixel types

#define chunky                   0
#define chunkyPlanar             1
#define planar                   2
#define RGBDirect                16

//
// pmVersion values

#define baseAddr32               4                       // pixmap base address is 32-bit address

// PixPat field offsets
//

#define patType                  $0                      // [word] type of pattern
#define patMap                   $2                      // [long] handle to pixmap
#define patData                  $6                      // [long] handle to data
#define patXData                 $A                      // [long] handle to expanded pattern data
#define patXValid                $E                      // [word] flags whether expanded pattern valid
#define patXMap                  $10                     // [long] handle to expanded pattern data
#define pat1Data                 $14                     // [8 bytes] old-style pattern/RGB color
#define ppRec                    $1C                     // size of pixPat record


// Pattern types
//

#define oldPat                   0                       // foreground/background pattern
#define newPat                   1                       // self-contained color pattern
#define ditherPat                2                       // rgb value to be dithered
#define oldCrsrPat               $8000                   // old-style cursor
#define cCrsrPat                 $8001                   // new-style cursor


// additional offsets in a color GrafPort
//

#define portPixMap               (portBits)                // [long] pixelMap handle
#define portVersion              (portPixMap+4)            // [word] port version number
#define grafVars                 (portVersion+2)           // [long] handle to more fields
#define chExtra                  (grafVars+4)              // [word] character extra
#define pnLocHFrac               (chExtra+2)               // [word] pen fraction
#define bkPixPat                 (bkPat)                   // [long] handle to bk pattern
#define rgbFgColor               (bkPixPat+4)              // [6 bytes] RGB components of fg color
#define rgbBkColor               (rgbFgColor+6)            // [6 bytes] RGB components of bk color
#define pnPixPat                 (pnPat)                   // [long] handle to pen's pattern
#define fillPixPat               (pnPixPat+4)              // [long] handle to fill pattern 


// GDevice field offsets
//

#define gdRefNum                 $0                      // [word] unitNum of driver
#define gdID                     $2                      // [word] client ID for search procs
#define gdType                   $4                      // [word] fixed/CLUT/direct
#define gdITable                 $6                      // [long] handle to inverse table
#define gdResPref                $A                      // [word] preferred resolution for inverse tables
#define gdSearchProc             $C                      // [long] search proc (list?) pointer
#define gdCompProc               $10                     // [long] complement proc (list?) pointer
#define gdFlags                  $14                     // [word] grafDevice flags word
#define gdPMap                   $16                     // [long] handle to pixMap describing device
#define gdRefCon                 $1A                     // [long] reference value
#define gdNextGD                 $1E                     // [long] handle of next gDevice
#define gdRect                   $22                     // [rect] device's bounds in global coordinates
#define gdMode                   $2A                     // [long] device's current mode
#define gdCCBytes                $2E                     // [word] depth of expanded cursor data
#define gdCCDepth                $30                     // [word] depth of expanded cursor data
#define gdCCXData                $32                     // [long] handle to cursor's expanded data
#define gdCCXMask                $36                     // [long] handle to cursor's expanded mask
#define gdReserved               $3A                     // [long] MUST BE 0
#define gdRec                    $3E                     // size of GrafDevice record

// VALUES FOR GDType

#define clutType                 0                       // 0 if lookup table
#define fixedType                1                       // 1 if fixed table
#define directType               2                       // 2 if direct values

// BIT ASSIGNMENTS FOR GDFlags

#define gdDevType                0                       // 0 = monochrome; 1 = color
#define hasAuxMenuBar            06                      // 1 if device has an Aux menu bar on it
#define BurstDevice              07                      // 1 if this device support burst xfer
#define ext32Device              08                      // 1 if this device must be accessed in 32-bit mode
#define frozenDevice             09                      // reserved for future use
#define ramInit                  10                      // 1 if initialized from 'scrn' resource
#define mainScreen               11                      // 1 if main screen
#define allInit                  12                      // 1 if all devices initialized
#define screenDevice             13                      // 1 if screen device [not used]
#define noDriver                 14                      // 1 if no driver for this GDevice
#define screenActive             15                      // 1 if in use

// CCrsr (Color Cursor) field offsets
//
// NOTE THAT THE FIRST FOUR FIELDS ARE PARALLEL TO THE FIRST FOUR FIELDS
// OF A PATTERN SO THAT PATCONVERT CAN BE USED TO EXPAND A CURSOR
//

#define crsrType                 0                       //[WORD] CURSOR TYPE
#define crsrMap                  (crsrType+2)              //[LONG] HANDLE TO CURSOR'S PIXMAP
#define crsrData                 (crsrMap+4)               //[LONG] HANDLE TO CURSOR'S COLOR DATA
#define crsrXData                (crsrData+4)              //[LONG] HANDLE TO EXPANDED DATA
#define crsrXValid               (crsrXData+4)             //[WORD] DEPTH OF EXPANDED DATA (0 IF NONE)
#define crsrXHandle              (crsrXValid+2)            //[LONG] HANDLE FOR FUTURE USE
#define crsr1Data                (crsrXHandle+4)           //[16 WORDS] ONE-BIT DATA
#define crsrMask                 (crsr1Data+32)            //[16 WORDS] ONE-BIT MASK
#define crsrHotSpot              (crsrMask+32)             //[POINT] HOT-SPOT FOR CURSOR
#define crsrXTable               (crsrHotSpot+4)           //[LONG] TABLE ID FOR EXPANDED DATA
#define crsrID                   (crsrXTable+4)            //[LONG] ID FOR CURSOR
#define crsrRec                  (crsrID+4)                //SIZE OF CURSOR SAVE AREA


// CIcon (Color Icon) field offsets
//

#define iconPMap                 0                       //[PIXMAP] ICON'S PIXMAP
#define iconMask                 (iconPMap+pmRec)          //[BITMAP] 1-BIT VERSION OF ICON ONE-BIT MASK FOR ICON
#define iconBMap                 (iconMask+bitmapRec)      //[BITMAP] 1-BIT VERSION OF ICON
#define iconData                 (iconBMap+bitmapRec)      //[LONG] HANDLE TO PIXMAP DATA
//FOLLOWED BY BMAP AND MASK DATA
#define iconRec                  (iconData+4)              //SIZE OF ICON HEADER

//
// Gamma Table format
//
#define gVersion                 0                       // [word] gamma version number
#define gType                    (gVersion+2)              // [word] gamma data type
#define gFormulaSize             (gType+2)                 // [word] Formula data size
#define gChanCnt                 (gFormulaSize+2)          // [word] number of channels of data
#define gDataCnt                 (gChanCnt+2)              // [word] number of values/channel
#define gDataWidth               (gDataCnt+2)              // [word] bits/corrected value (data packed to next larger byte size)
#define gFormulaData             (gDataWidth+2)            // [array] data for formulas, followed by gamma values


// EXTENSIONS TO THE QDPROCS RECORD
//

#define opcodeProc               $34                     // [pointer]
#define newProc1                 $38                     // [pointer]
#define newProc2                 $3C                     // [pointer]
#define newProc3                 $40                     // [pointer]
#define newProc4                 $44                     // [pointer]
#define newProc5                 $48                     // [pointer]
#define newProc6                 $4C                     // [pointer]
#define cqdProcsRec              $50                     // size of QDProcs record

// OFFSETS WITHIN GRAFVARS:
//
#define rgbOpColor               0                       // [6 bytes] color for addPin, subPin and average
#define rgbHiliteColor           (rgbOpColor+6)            // [6 bytes] color for hiliting
#define pmFgColor                (rgbHiliteColor+6)        // [4 bytes] palette handle for foreground color
#define pmFgIndex                (pmFgColor+4)             // [2 bytes] index value for foreground
#define pmBkColor                (pmFgIndex+2)             // [4 bytes] palette handle for background color
#define pmBkIndex                (pmBkColor+4)             // [2 bytes] index value for background
#define pmFlags                  (pmBkIndex+2)             // [2 bytes] flags for Palette Manager
#define grafVarRec               (pmFlags+2)               // size of grafVar record

// ColorTable field offsets

#define ctSeed                   0                       // [long] id number for table
#define transIndex               (ctSeed+4)                // [word] index of transparent pixel (obsolete)
#define ctFlags                  (ctSeed+4)                // [word] hibh bit: 0 = PixMap; 1 = device
#define ctSize                   (ctFlags+2)               // [word] number of entries in CTTable
#define ctTable                  (ctSize+2)                // [variant] array of color spec
#define ctRec                    (ctTable)                 // size of record without color table
#define ctEntrySize              8                       // size of each entry in table
#define minSeed                  1023                    // minimum seed value (< minSeed reserved for rsrc ID's)
#define protectBit               7                       // protect bit in device color table
#define reserveBit               6                       // reserve bit in device color table
#define invalColReq              (-1)                      // invalid color table request

// CProcRec structure

#define nxtComp                  $0                      //link to next proc [pointer]
#define compProc                 $4                      //pointer to routine [pointer]
#define cProcSize                8                       // size of CProcRec
// SProcRec structure

#define nxtSrch                  $0                      //[pointer] link to next proc
#define srchproc                 $4                      //[pointer] pointer to routine
#define sProcSize                8                       // size of SProcRec

// request List structure

#define reqLSize                 0                       // request list size [word]
#define reqLData                 2                       // request list data [words]


// Point structure

#define v                        0                       // vertical coordinate [word]
#define h                        2                       // horizontal coordinate [word]

#endif   // ...already included 
