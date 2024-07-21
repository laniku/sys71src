/*
	File:		CrsrDevPriv.h

	Contains:	equates for new mouse/trackball/etc. acceleration code
				Ported to C from CrsrDevEqu.a

	Written by:	Ian Hendry

	Copyright:	© 1993-1994 by Apple Computer, Inc.  All rights reserved.


	Change History (most recent first):

	   <SM3>	  2/4/94	IH		Fix low mem defines.
		 <2>	 9/10/93	IH		Make it compile.  Correct Copyright date.
		 <1>	  9/9/93	IH		First ported from CrsrDevEqu.a (not even compiled yet I don't want to forget to check it in)
		
	To Do:
		Make UPP for SetCrsrDelayVector.
*/
#pragma once

#ifndef __CRSRDEVPRIV__
#define __CRSRDEVPRIV__

// --------- button operations  ---------

enum {
	btnNoOp			=	0,				// No action for this button
	btnSingleClick	=	1,				// Normal mouse button
	btnDoubleClick	=	2,				// Click-release-click when pressed
	btnClickLock	=	3,				// Click on press, release on next press
	btnCharStroke	=	4,				// A keystroke, data=(modifiers, char code)
	btnAppleScript	=	5,				// An AppleScript
	btnCustom		=	6				// Custom behavior, data=proc pointer
};

// --------- Device Classes ---------

enum {
	classAbsolute	=	0,				// a flat-response device
	classMouse		=	1,				// mechanical or optical mouse
	classTrackball	=	2,				// trackball
	classScratchPad	=	3,				// (midas)
	classJoystick	=	4,				// (homeRow)
	classRelTablet	=	5				// relative tablet
};




struct CrsrDevSegmentRec	{
	Fixed		devUnits;				// highest device speed for this segment
	Fixed		slope;					// multiplier for device speed (crsr speed/dev speed)
	Fixed		intercept;				// offset to produce cursor speed
};
typedef struct CrsrDevSegment CrsrDevSegment;


struct CrsrDevRec {
	struct CrsrDevRec*		nextCrsrDev;		// ptr to next record in linked list
	struct CrsrDataRec*		whichCursor;		// ptr to data for target cursor
	long					refCon;				// Application defined
	long					unused;				// reserved for future
			
	long					devID;				// device identifier (from ADB reg 1)
	long					resolution;			// units/inch  (orig. from ADB reg 1)
	char					devClass;			// device class		(from ADB reg 1)
	char					cntButtons;			// # of buttons		(from ADB reg 1)
	char					unused1;			// align
			
	char					buttons;			// state of all buttons
	char					buttonOp[8];		// action performed per button
	long					buttonTicks[8];		// ticks when button last went up (for debounce)
	long					buttonData[8];		// data for the button operation
	long					doubleClickTime;	// device-specific double click speed
	long					acceleration;		// current acceleration
			
	Ptr						accelPoints;		// Private: Ptr to array of (dev_delta, slope, intercept)
	long					deltaX;				// Private: accumulated deltas
	long					deltaY;				// Private: 		"
	long					errorX;				// Private: accumulated errors
	long					errorY;				// Private: 		"
	short					denom;				// Private: fraction of the errors to use next time
	short					spread;				// Private: Number of samples to spread errors over
	char					newData;			// Private: set when deltas are new
	char					unused2;			// align
};
typedef struct CrsrDevRec CrsrDevRec,*CrsrDevPtr;



struct CrsrDataRec {
	struct CrsrDataRec*		nextCrsrData;		// next in global list	
	Ptr						displayInfo;		// unused (FUTURE: display info for this cursor)
	Fixed					whereX;				// horizontal position
	Fixed					whereY;				// vertical position
	Point					where;				// the pixel position
	Boolean					isAbs;				// has been stuffed with absolute coords
	char					buttonCount;		// number of buttons currently pressed
	Fixed					screenRes;			// Pixels per inch on the current display
	short					screenDelay;		// minimum number of VBLs between subsequent crsr redraws	<H3>
	short					reserved;			// future expansion											<H3>
	Ptr						scrnDelayPtr;		// ptr to table of screen delay values						<H3>
	long					alsoreserved;		// future expansion											<H3>
	long					scrnDelayTbl[8];	// default tbl for <refnum><screen delay> pairs				<H3>
};
typedef struct CrsrDataRec CrsrDataRec, *CrsrDataPtr;

				
struct CrsrDevGlobalsRec {
	CrsrDevPtr				firstCrsrDev;		// head of the cursor device list
	CrsrDataPtr				firstCrsrData;		// points to THE ONLY cursor data record
	ProcPtr					SetCrsrDelayVector;	// points to routine that updates screen crsr delay			<H3>
	ProcPtr					DrawCrsrVBLVector;	// vectors final drawing stage of CrsrDevHandleVBL			<H3>
	char					crsrDevFlags;		// Flags													<SM3>
	char					MoreCrsrDevFlags;	// 															<SM3>
	long					reserved;			// future expansion											<H3>
};
typedef struct CrsrDevGlobalsRec CrsrDevGlobalsRec, *CrsrDevGlobalsPtr;


//
//	CrsrDevFlags bit definitions
//

enum {
	kSkipCrsrDrawBit = 0						// Force the CrsrDevHandleVBL to skip drawing the cursor 		<SM3>
};

	// jump entry for DrawCursor & EraseCursor
#define		DrawCrsrVector			0x1FB8
#define		EraseCrsrVector			0x1FBC

// Never tested these.  Make sure they work if you are the first one to use them.
#define		GetDrawCrsrVector()		(*(ProcPtr *)(DrawCrsrVector))
#define		SetDrawCrsrVector(x)	(*(ProcPtr *)(DrawCrsrVector) = (x))

#define		GetEraseCrsrVector()	(*(ProcPtr *)(EraseCrsrVector))
#define		SetEraseCrsrVector(x)	(*(ProcPtr *)(EraseCrsrVector) = (x))

				

//---------------------
// Misc. equates				
//
// Not needed in .h file but included for completeness
//---------------------
				
//#define mouseAddr		 = 03				// default address of mice (DEFINED ELSEWHERE
//
//enum {
//	extDevHand		 = 04,					// handler 04 = extended type mouse device
//	kDefaulFrameRate = 67					// 67 frames/sec
//};


#endif