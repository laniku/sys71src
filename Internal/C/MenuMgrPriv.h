/*
	File:		MenuMgrPriv.h

	Contains:	Private interface to the Menu Manager.

	Written by:	Kevin S. MacDonell

	Copyright:	й 1989-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <4>	 3/31/93	IH		Add CalcMenuBar call for Display Manager.
		 <6>	 11/5/92	JSM		Add interfaces to more private routines, add SavedBitsRecord and
									OffscreenBufferRecord, although we can't really represent the
									latter in C the way it's defined in assembly.
		 <5>	 9/16/92	JSM		SaveBits takes a Rect*, not a Rect.
		 <4>	  2/5/91	stb		gs: move in SaveBits, RestoreBits, DiscardBits
		 <3>	 1/21/91	DFH		(KSM) Added System Menu constants from MenuMgrPriv.a.
		 <2>	  6/8/90	KSM		Add IsSystemMenu call.
		 <1>	 5/21/90	KSM		New today.
*/

#ifndef __MENUMGRPRIV__
#define __MENUMGRPRIV__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __MENUS__
#include <Menus.h>
#endif

/* System Menu IDs as we know them */
#define kLoSystemMenuRange			((short) 0xB000)		/* This is -20480 (the lowest value) */
#define kHiSystemMenuRange			((short) 0xBFFF)		/* This is -16385 (the highest value) */

#define kApplicationMenuID			((short) 0xBF97)		/* -16489: The application menu ID */
#define kHelpMenuID					((short) 0xBF96)		/* -16490: The help menu ID */
#define kScriptMenuID				((short) 0xBF95)		/* -16491: The keyboard menu ID */

/* Save/RestoreBits data structures */

struct SavedBitsRecord {
	Rect			rectangle;				// the rectangle
	PixMapHandle	pixMap;					// the pixMap handle
};

typedef struct SavedBitsRecord SavedBitsRecord;
typedef SavedBitsRecord *SavedBitsRecordPtr, **SavedBitsRecordHandle;
typedef SavedBitsRecordHandle SavedBits;					/* For Save/Restore/Discard Bits calls */

struct OffscreenBufferRecord {
	Rect			rectangle;				// the rectangle (local coordinates)
	PixMapHandle	bufferPixMap;			// the pixMap of the buffer
	GDHandle		bufferGDevice;			// the gDevice for drawing in the buffer
	BitMap			savedPortBits;			// the old bitmap of the port (for B&W)
											// еее in assembly, the following two fields are ORGed
											// to start at savedPortBits, since we never use both
											// at once
//	PixMapHandle	savedPortPixMap;		// the old pixMap of the port
	GDHandle		savedGDevice;			// the old gDevice for the port
};

typedef struct OffscreenBufferRecord OffscreenBufferRecord;
typedef OffscreenBufferRecord *OffscreenBufferRecordPtr, **OffscreenBufferRecordHandle;
typedef OffscreenBufferRecordHandle OffscreenBuffer;		/* For Begin/EndDrawingOffscreen calls */

/* Private routines */

pascal OSErr GetMenuTitleRect(short menuID, Rect* theRect)
	= {0x303C,0x04FF,0xA825};

pascal OSErr GetMBARRect(Rect* theRect)
	= {0x303C,0x04FE,0xA825};

pascal OSErr GetAppMenusRect(Rect* theRect)
	= {0x303C,0x04FD,0xA825};

pascal OSErr GetSysMenusRect(Rect* theRect)
	= {0x303C,0x04FC,0xA825};

pascal OSErr DrawMBARString(char* bannerMsg,short scriptID, short teJust)
	= {0x303C,0x08FB,0xA825};

pascal OSErr IsSystemMenu(short menuID, Boolean *isSys)
	= {0x303C,0x03FA,0xA825};

pascal OSErr CalcMenuBar(short menuID)
    = {0x303C,0x01F5,0xA825}; 

pascal OSErr SaveBits(Rect* saveRect, Boolean purgeable, SavedBits *bits)
    = {0x303C,0x0501,0xA81E}; 

pascal OSErr RestoreBits(SavedBits bits)
    = {0x303C,0x0202,0xA81E}; 

pascal OSErr DiscardBits(SavedBits bits)
    = {0x303C,0x0203,0xA81E}; 

pascal OSErr BeginDrawingOffscreen(Rect *bufferRect, OffscreenBuffer *buffer)
    = {0x303C,0x0404,0xA81E}; 

pascal OSErr EndDrawingOffscreen(OffscreenBuffer buffer)
    = {0x303C,0x0205,0xA81E}; 

pascal OSErr NewOffscreenBuffer(Rect *bufferRect, Boolean purgeable, OffscreenBuffer *buffer)
    = {0x303C,0x0506,0xA81E}; 

pascal OSErr AttachOffscreenBuffer(OffscreenBuffer buffer)
    = {0x303C,0x0207,0xA81E}; 

pascal OSErr DetachOffscreenBuffer(OffscreenBuffer buffer)
    = {0x303C,0x0208,0xA81E}; 

pascal OSErr DisposeOffscreenBuffer(OffscreenBuffer buffer)
    = {0x303C,0x0209,0xA81E}; 

#endif __MENUMGRPRIV__
