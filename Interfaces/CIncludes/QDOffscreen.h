
/************************************************************

Created: Saturday, July 27, 1991 at 5:33 PM
 QDOffscreen.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606



	Change History (most recent first):

		<13>	 7/31/91	JL		Updated Copyright. Restored Comments.
		<12>	 1/29/91	JL		Changed parameter name of PixMap32Bit to from offscrrenPixMap to
									pmHandle.
		<11>	 1/28/91	LN		Checked in Database generate file from DSG. Grouping enums into
									groups of 20.
		<10>	 1/25/91	stb		JDR: add const on non-VAR parameters
		 <9>	 1/15/91	KON		Change useMFTempBit to UseTempMemBit. [csd]
		 <8>	11/28/90	JL		Put formal parameter names back.
		 <7>	 11/4/90	dba		shortened inline for OffscreenVersion; use (void) instead of ();
									got rid of some extraneous parameter names
		 <6>	  10/990	JAL		Changed __Safe_Link to _CPlusPlus.
		 <5>	  9/1/90	dvb		Beautify.
		 <4>	 3/29/90	KON		Put parameter size (in bytes) in high word of d0, trap selector
									in low word.
		 <3>	 3/27/90	KON		Added useMFTemp flag, keepLocal flag, and prototypes for
									selectors 19-23.

************************************************************/


#ifndef __QDOFFSCREEN__
#define __QDOFFSCREEN__

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif


enum {


/* New error codes */
 cDepthErr = -157	/*invalid pixel depth*/
};

enum {
 pixPurgeBit = 0,
 noNewDeviceBit = 1,
 useTempMemBit = 2,
 keepLocalBit = 3,
 pixelsPurgeableBit = 6,
 pixelsLockedBit = 7,
 mapPixBit = 16,
 newDepthBit = 17,
 alignPixBit = 18,
 newRowBytesBit = 19,
 reallocPixBit = 20,
 clipPixBit = 28,
 stretchPixBit = 29,
 ditherPixBit = 30,
 gwFlagErrBit = 31
 };

enum {
 pixPurge = 1 << pixPurgeBit,
 noNewDevice = 1 << noNewDeviceBit,
 useTempMem = 1 << useTempMemBit,
 keepLocal = 1 << keepLocalBit,
 pixelsPurgeable = 1 << pixelsPurgeableBit,
 pixelsLocked = 1 << pixelsLockedBit,
 mapPix = 1 << mapPixBit,
 newDepth = 1 << newDepthBit,
 alignPix = 1 << alignPixBit,
 newRowBytes = 1 << newRowBytesBit,
 reallocPix = 1 << reallocPixBit,
 clipPix = 1 << clipPixBit,
 stretchPix = 1 << stretchPixBit,
 ditherPix = 1 << ditherPixBit,
 gwFlagErr = 1 << gwFlagErrBit
 };

typedef unsigned long GWorldFlags;


/* Type definition of a GWorldPtr */
typedef CGrafPtr GWorldPtr;

#ifdef __cplusplus
extern "C" {
#endif
pascal QDErr NewGWorld(GWorldPtr *offscreenGWorld,short PixelDepth,const Rect *boundsRect,
 CTabHandle cTable,GDHandle aGDevice,GWorldFlags flags)
 = {0x203C,0x0016,0x0000,0xAB1D}; 
pascal Boolean LockPixels(PixMapHandle pm)
 = {0x203C,0x0004,0x0001,0xAB1D}; 
pascal void UnlockPixels(PixMapHandle pm)
 = {0x203C,0x0004,0x0002,0xAB1D}; 
pascal GWorldFlags UpdateGWorld(GWorldPtr *offscreenGWorld,short pixelDepth,
 const Rect *boundsRect,CTabHandle cTable,GDHandle aGDevice,GWorldFlags flags)
 = {0x203C,0x0016,0x0003,0xAB1D}; 
pascal void DisposeGWorld(GWorldPtr offscreenGWorld)
 = {0x203C,0x0004,0x0004,0xAB1D}; 
pascal void GetGWorld(CGrafPtr *port,GDHandle *gdh)
 = {0x203C,0x0008,0x0005,0xAB1D}; 
pascal void SetGWorld(CGrafPtr port,GDHandle gdh)
 = {0x203C,0x0008,0x0006,0xAB1D}; 
pascal void CTabChanged(CTabHandle ctab)
 = {0x203C,0x0004,0x0007,0xAB1D}; 
pascal void PixPatChanged(PixPatHandle ppat)
 = {0x203C,0x0004,0x0008,0xAB1D}; 
pascal void PortChanged(GrafPtr port)
 = {0x203C,0x0004,0x0009,0xAB1D}; 
pascal void GDeviceChanged(GDHandle gdh)
 = {0x203C,0x0004,0x000A,0xAB1D}; 
pascal void AllowPurgePixels(PixMapHandle pm)
 = {0x203C,0x0004,0x000B,0xAB1D}; 
pascal void NoPurgePixels(PixMapHandle pm)
 = {0x203C,0x0004,0x000C,0xAB1D}; 
pascal GWorldFlags GetPixelsState(PixMapHandle pm)
 = {0x203C,0x0004,0x000D,0xAB1D}; 
pascal void SetPixelsState(PixMapHandle pm,GWorldFlags state)
 = {0x203C,0x0008,0x000E,0xAB1D}; 
pascal Ptr GetPixBaseAddr(PixMapHandle pm)
 = {0x203C,0x0004,0x000F,0xAB1D}; 
pascal QDErr NewScreenBuffer(const Rect *globalRect,Boolean purgeable,GDHandle *gdh,
 PixMapHandle *offscreenPixMap)
 = {0x203C,0x000E,0x0010,0xAB1D}; 
pascal void DisposeScreenBuffer(PixMapHandle offscreenPixMap)
 = {0x203C,0x0004,0x0011,0xAB1D}; 
pascal GDHandle GetGWorldDevice(GWorldPtr offscreenGWorld)
 = {0x203C,0x0004,0x0012,0xAB1D}; 
pascal Boolean QDDone(GrafPtr port)
 = {0x203C,0x0004,0x0013,0xAB1D}; 
pascal long OffscreenVersion(void)
 = {0x7014,0xAB1D}; 
pascal QDErr NewTempScreenBuffer(const Rect *globalRect,Boolean purgeable,
 GDHandle *gdh,PixMapHandle *offscreenPixMap)
 = {0x203C,0x000E,0x0015,0xAB1D}; 
pascal Boolean PixMap32Bit(PixMapHandle pmHandle)
 = {0x203C,0x0004,0x0016,0xAB1D}; 
pascal PixMapHandle GetGWorldPixMap(GWorldPtr offscreenGWorld)
 = {0x203C,0x0004,0x0017,0xAB1D}; 
#ifdef __cplusplus
}
#endif

#endif
