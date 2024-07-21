/*
	File:		Layers.h

	Contains:	Private interface to the layer manager.

	Written by:	Ed Tecot

	Copyright:	© 1989-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<18>	 7/28/92	DCL		Moved applicationFloatKind & systemFloatKind constants out of
									the public eye and into the private Layers header file. At the
									request of TechPubs, and with moral support from Dean, Greg and
									Kenny.
		<17>	 8/27/91	JSM		Cleanup header.
		<16>	  1/3/91	VL		(RLC) Add a new public call RedrawAll.
		<15>	  9/7/90	DFH		Changed SetLayerLock to GetDeskPort
		<14>	 7/23/90	EMT		Changed IsLayerLocked to WindowType.
		<13>	 5/30/90	DC		Added interface for GlobalPortRect
		<12>	 4/18/90	DC		Add a symbolic constant for the dialog centering divisor
		<11>	  4/2/90	EMT		Added interface for PaintOnePal.
		<10>	 3/16/90	DC		Added interface for CheckWindow
		 <9>	 3/14/90	DC		Added Error codes for SetWIndowState
		 <8>	  3/8/90	DC		Changed names of some window positioning constants
		 <7>	 2/27/90	EMT		No more AppLayer.
		 <5>	 2/23/90	HJR		Correct Build problem in that type Size is undefined.
		 <1>	 2/21/90	HJR		Moved from Interfaces:CIncludes to Internal.
		 <7>	 2/20/90	DC		Added PositionWindow, AutoPositionWindow, GetWindowState, SetWindowState
		 <6>	 2/15/90	EMT		Changed AuxCtlHndl to AuxCtlHandle to match I.M.
		 <5>	 2/15/90	JAL		Changed AuxWinHndl to AuxWinHandle to match I.M.
		 <4>	 2/14/90	EMT		Moved reserved2 bits here. Made constants for -1 and 0.
		 <2>	12/21/89	EMT		Changed interfaces to CheckUpdateIn and FrontWindowIn to use
									LayerPtr rather than LayerPeek.
	   <1.2>	12/11/89	EMT		Added CheckUpdateIn, FrontWindowIn and ActiveWindow.
	   <1.1>	12/11/89	EMT		Moved layer stuff in Windows.h to here.
	   <1.0>	 5/15/89	CCH		Adding from System project.

*/

#ifndef __LAYERS__
#define __LAYERS__

#ifndef __WINDOWS__
#include <Windows.h>
#endif

#ifndef __MEMORY__
#include <Memory.h>
#endif

enum {
 applicationFloatKind = 6,		/* floating window created by applications */
 systemFloatKind = 7			/* floating window belongs to text services */
};

#define lmDialogConstant 5

typedef enum {
	lcMainScreen,
	lcParentWindowScreen,
	lcParentWindow
} LocationControlValues;

typedef enum {
	hcNoHorizontalControl,
	hcCenter
} HorizontalControlValues;

typedef enum {
	vcNoVerticalControl,
	vcDocumentCenter,
	vcAlertCenter,
	vcStagger
} VerticalControlValues;

typedef enum {
	ccFrame,
	ccDragBar,
	ccContent
} CheckControlValues;

struct LayerRecord {
    GrafPort			port;
    short				windowKind;
    Boolean				visible;
    Boolean				reserved1;
    Boolean				neverActive;
    Boolean				reserved2;
    RgnHandle			strucRgn;
    RgnHandle			contRgn;
    RgnHandle			updateRgn;
    long				reserved3;
    struct LayerRecord	*parent;
    AuxWinHandle		auxWinHead;
    short				reserved4;
    AuxCtlHandle		auxCtlHead;
    WindowPeek			nextWindow;
    WindowPeek			subWindows;
    long				refCon;
};

#ifndef __cplusplus
typedef struct LayerRecord LayerRecord;
#endif

typedef LayerRecord *LayerPeek;

typedef GrafPtr LayerPtr;

#define	fLayerLocked	0x80	/* Bit in reserved2 which determines if this layer is locked. */
#define	fLayerBelow		0x40	/* Bit in reserved2 is set if there are any layers in this layer. */
#define	fLayerPUpdate	0x04	/* Bit in reserved2 if this layer needs a palette update. */
#define	fLayerPaint		0x02	/* Bit in reserved2 if this layer needs to be painted. */
#define	fLayerCalcVis	0x01	/* Bit in reserved2 if this layer needs to have visRgns calculated. */

#define	skipChildren	700		/* For WindowAction, but could be used generically. */
#define	haltIterator	701		/* For WindowAction, but could be used generically. */
#define badWindowType	702		/* For SetWindowState - zoom a non-zommable window.	*/
#define badVersNo		703		/* For SetWindowState - wrong version of structure.	*/
#define badWindPos		704		/* For SetWindowState - window too obscured.		*/

typedef pascal OSErr	WindowAction(WindowPeek window, LayerPeek parent, void *privateData);

#define	firstWindow		((WindowPeek) -1)	/* Used in NewWindow, GetNewWindow, EachWindow. */
#define	afterLastWindow	((WindowPeek) 0)	/* Used in NewWindow, GetNewWindow, EachWindow. */
#define	afterLastLayer	((WindowPeek) -1)	/* Used as stop parameter in EachWindow. */

/* Window "types" */
#define isWindow		1
#define	isLayer			0
#define	isLockedLayer	-1

/* Private routines */
pascal OSErr		InitLayers(void)
	= {0x7000,0xA829};
pascal LayerPtr		GetRootLayer(void)
	= {0x70FF,0xA829};
pascal WindowPtr	ActiveWindow(void)
	= {0x70FE,0xA829};
pascal WindowPtr	FrontWindowIn(LayerPtr inLayer)
	= {0x70FD,0xA829};
pascal Boolean		CheckUpdateIn(EventRecord *event, LayerPtr inLayer)
	= {0x70FC,0xA829};
pascal OSErr		GetDeskPort(GrafPtr *)
	= {0x70FB,0xA829};
pascal short		WindowType(WindowPtr window)
	= {0x70FA,0xA829};
pascal LayerPeek	GetParent(WindowPtr window)
	= {0x70F9,0xA829};
pascal OSErr		EachWindow(WindowPeek start, WindowPeek stop, LayerPeek parent, WindowAction *action, void *privateData)
	= {0x70F8,0xA829};
pascal void			PaintOnePal(WindowPeek window, RgnHandle clobberedRgn)
	= {0x70F7,0xA829};
pascal void			GlobalPortRect(WindowPtr window, Rect *portRect)
	= {0x70F6,0xA829};

/* "Public" routines */
pascal OSErr		NewLayer(LayerPtr *layer, Boolean visible, Boolean neverActive, WindowPtr behind, long refCon)
	= {0x7001,0xA829};
pascal Boolean		IsLayer(WindowPtr window)
	= {0x7002,0xA829};
pascal LayerPtr		GetCurLayer(void)
	= {0x7003,0xA829};
pascal void			SetCurLayer(LayerPtr layer)
	= {0x7004,0xA829};
pascal LayerPtr		SwapCurLayer(LayerPtr layer)
	= {0x7005,0xA829};
pascal WindowPeek	GetSubWindows(LayerPtr layer)
	= {0x7006,0xA829};
pascal short		FindLayer(Point thePoint, WindowPtr *theWindow)
	= {0x7007,0xA829};
pascal void			PositionWindow(WindowPtr whichWindow,const Rect *referenceRect,
								Boolean findScreen,
								HorizontalControlValues horizontalControl,
								VerticalControlValues verticalControl)
	= {0x7008,0xA829};
pascal void			AutoPositionWindow(WindowPtr whichWindow, LocationControlValues where,
								HorizontalControlValues horizontalControl,
								VerticalControlValues verticalControl)
	= {0x7009,0xA829};
pascal OSErr		GetWindowState(WindowPtr whichWindow, Handle windState, Size *infoSize)
	= {0x700A,0xA829};
pascal OSErr		SetWindowState(WindowPtr whichWindow, Handle windState)
	= {0x700B,0xA829};
pascal Boolean		CheckWindow(WindowPtr whichWindow,
								CheckControlValues checkControl,
								Boolean entirelyOnScreen)
	= {0x700C,0xA829};
pascal void		RedrawAll(void)
	= {0x700D,0xA829};

#endif __LAYERS__
