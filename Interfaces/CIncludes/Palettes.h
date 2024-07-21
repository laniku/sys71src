/************************************************************

Created: Tuesday, January 8, 1991 at 9:43 AM
    Palettes.h
    C Interface to the Macintosh Libraries


        Copyright Apple Computer, Inc.    1987-1990
        All rights reserved

    This file is used in these builds: BigBang

	Change History (most recent first):

		<11>	 9/17/91	MH		change inline value in GetGray from 0x1219 to 0x0C19 which is
									correct
		<10>	 1/30/91	JL		checked in database generated file from DSG.
		 <9>	 1/25/91	stb		JDR: add const where pointers aren’t VARs.
		 <8>	  1/9/91	dvb		Change return type of HasDepth to short.
		 <7>	12/13/90	dvb		Make .h and .p and .a files consistent.
		 <6>	 11/7/90	JL		Added pmInhibit equates.  Changes all #defines to anonymous
									enums
		 <5>	 9/15/90	DC		added GetGray
		 <4>	 7/23/90	DC		Added an interface for CheckColors
		 <3>	 6/19/90	DVB		Add the latest PMgr dispatches

	To Do:
************************************************************/


#ifndef __PALETTES__
#define __PALETTES__

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif

#ifndef __WINDOWS__
#include <Windows.h>
#endif


enum {

    pmCourteous = 0,        /*Record use of color on each device touched.*/
    pmTolerant = 0x0002,    /*render ciRGB if ciTolerance is exceeded by best match.*/
    pmAnimated = 0x0004,    /*reserve an index on each device touched and render ciRGB.*/
    pmExplicit = 0x0008,    /*no reserve, no render, no record; stuff index into port.*/

    pmWhite = 0x0010,
    pmBlack = 0x0020,

    pmInhibitG2 = 0x0100,
    pmInhibitC2 = 0x0200,
    pmInhibitG4 = 0x0400,
    pmInhibitC4 = 0x0800,
    pmInhibitG8 = 0x1000,
    pmInhibitC8 = 0x2000,


/* NSetPalette Update Constants */
    pmNoUpdates = 0x8000,   /*no updates*/
    pmBkUpdates = 0xA000,   /*background updates only*/
    pmFgUpdates = 0xC000,   /*foreground updates only*/
    pmAllUpdates = 0xE000   /*all updates*/
};

struct ColorInfo {
    RGBColor ciRGB;         /*true RGB values*/
    short ciUsage;          /*color usage*/
    short ciTolerance;      /*tolerance value*/
    short ciDataFields[3];  /*private fields*/
};

typedef struct ColorInfo ColorInfo;

struct Palette {
    short pmEntries;        /*entries in pmTable*/
    short pmDataFields[7];  /*private fields*/
    ColorInfo pmInfo[1];
};

typedef struct Palette Palette;
typedef Palette *PalettePtr, **PaletteHandle;


#ifdef __cplusplus
extern "C" {
#endif
pascal void InitPalettes(void)
    = 0xAA90; 
pascal PaletteHandle NewPalette(short entries,CTabHandle srcColors,short srcUsage,
    short srcTolerance)
    = 0xAA91; 
pascal PaletteHandle GetNewPalette(short PaletteID)
    = 0xAA92; 
pascal void DisposePalette(PaletteHandle srcPalette)
    = 0xAA93; 
pascal void ActivatePalette(WindowPtr srcWindow)
    = 0xAA94; 
pascal void SetPalette(WindowPtr dstWindow,PaletteHandle srcPalette,Boolean cUpdates)
    = 0xAA95; 
pascal void NSetPalette(WindowPtr dstWindow,PaletteHandle srcPalette,short nCUpdates)
    = 0xAA95; 
pascal PaletteHandle GetPalette(WindowPtr srcWindow)
    = 0xAA96; 
pascal void CopyPalette(PaletteHandle srcPalette,PaletteHandle dstPalette,
    short srcEntry,short dstEntry,short dstLength)
    = 0xAAA1; 
pascal void PmForeColor(short dstEntry)
    = 0xAA97; 
pascal void PmBackColor(short dstEntry)
    = 0xAA98; 
pascal void AnimateEntry(WindowPtr dstWindow,short dstEntry,const RGBColor *srcRGB)
    = 0xAA99; 
pascal void AnimatePalette(WindowPtr dstWindow,CTabHandle srcCTab,short srcIndex,
    short dstEntry,short dstLength)
    = 0xAA9A; 
pascal void GetEntryColor(PaletteHandle srcPalette,short srcEntry,RGBColor *dstRGB)
    = 0xAA9B; 
pascal void SetEntryColor(PaletteHandle dstPalette,short dstEntry,const RGBColor *srcRGB)
    = 0xAA9C; 
pascal void GetEntryUsage(PaletteHandle srcPalette,short srcEntry,short *dstUsage,
    short *dstTolerance)
    = 0xAA9D; 
pascal void SetEntryUsage(PaletteHandle dstPalette,short dstEntry,short srcUsage,
    short srcTolerance)
    = 0xAA9E; 
pascal void CTab2Palette(CTabHandle srcCTab,PaletteHandle dstPalette,short srcUsage,
    short srcTolerance)
    = 0xAA9F; 
pascal void Palette2CTab(PaletteHandle srcPalette,CTabHandle dstCTab)
    = 0xAAA0; 
pascal long Entry2Index(short entry)
    = {0x7000,0xAAA2}; 
pascal void RestoreDeviceClut(GDHandle gd)
    = {0x7002,0xAAA2}; 
pascal void ResizePalette(PaletteHandle p,short size)
    = {0x7003,0xAAA2}; 
pascal void SaveFore(ColorSpec *c)
    = {0x303C,0x040D,0xAAA2}; 
pascal void SaveBack(ColorSpec *c)
    = {0x303C,0x040E,0xAAA2}; 
pascal void RestoreFore(const ColorSpec *c)
    = {0x303C,0x040F,0xAAA2}; 
pascal void RestoreBack(const ColorSpec *c)
    = {0x303C,0x0410,0xAAA2}; 
pascal OSErr SetDepth(GDHandle gd,short depth,short whichFlags,short flags)
    = {0x303C,0x0A13,0xAAA2}; 
pascal short HasDepth(GDHandle gd,short depth,short whichFlags,short flags)
    = {0x303C,0x0A14,0xAAA2}; 
pascal short PMgrVersion(void)
    = {0x7015,0xAAA2}; 
pascal void SetPaletteUpdates(PaletteHandle p,short updates)
    = {0x303C,0x0616,0xAAA2}; 
pascal short GetPaletteUpdates(PaletteHandle p)
    = {0x303C,0x0417,0xAAA2}; 
pascal Boolean GetGray(GDHandle device,const RGBColor *backGround,RGBColor *foreGround)
    = {0x303C,0x0C19,0xAAA2}; 
#ifdef __cplusplus
}
#endif

#endif
