
/************************************************************

Created: Sunday, January 27, 1991 at 8:21 PM
 Balloons.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1990-1991
  All rights reserved

    This file is used in these builds: BigBang



	Change History (most recent first):

		<26>	 7/30/91	JL		Updated Copyright. Restored Comments.
		<25>	 6/14/91	JL		Checked in official MPW 3.2Ä version. Adjusted enum grouping to
									match DSG Database. Removed Resource IDs comment to match Pascal
									file. Temporarily lost updated copyright date; will be restored.
		<24>	  2/1/91	stb		RC: add spacing to clarify that some constants are not included
									in the error range
		<23>	 1/28/91	LN		Checked in Database Generated File from DSG. changed
									alernateRect param in HMShowMenuBalloon from Rect * to RectPtr
									changed aHelpMsg param in HMBalloonRect and HMBalloonPict and
									HMShowBalloon to const HMMessageRecord *
		<22>	 1/24/91	stb		RC: return OSErr from functions. Change alternateRect param from
									Rect * to RectPtr. Change hmBalloonHelpVersion to 0x0002. Change
									coolPict from handle to PicHandle.
		<21>	12/14/90	dba		<JDR> include Menus.h so we can use MenuHandle without a
									compiler error
		<20>	12/10/90	RLC		<bkr> Fix the passage of HMMessageRecord structs in
									HMShowBalloon(), HMBalloonRect(), HMBalloonPict() interfaces.
									Pass HMMessageRecord as *aHelpMsg.
		<19>	 12/3/90	JL		Put formal parameter names back, put CPlusPlus conditional
									around functions.
		<18>	 11/4/90	dba		add a wrapper around the whole file and get rid of unecessary
									__cplusplus stuff; this file seems to pass structs directly
									instead of using const structName * ... this must be fixed
		<17>	 9/24/90	RLC		Fix the interface to HMGetIndHelpMsg to pass 0x1306 as the
									selector (not 0x1106) as there are 19 words of parameters (not
									17 as originally counted [I better go back to grade school]).
									This will result in a crash if this call is made as procHelper
									won't copy enuf parameters to & from the stack!
		<16>	 8/31/90	RLC		Update the interfaces again.
		<15>	 8/22/90	RLC		Sync the interfaces w/ Balloons.p.
	   <13+>	 8/17/90	RLC		Fix up some of the defines to match the CONST in balloons.p
	   <12+>	 7/24/90	RLC		Update HMShowBalloon(), remove HMMouseInApplRgn(), add
									HMGetIndHelpMsg().
	   <11+>	  6/6/90	RLC		Add HMGetBalloonWindow call to interface.
		<11>	 5/31/90	RLC		Put in inlines to HMGetHelpMenuHandle call.
		<10>	 4/30/90	RLC		Make this file 'ANSI' standard (whatever that is).
		 <9>	 4/24/90	RLC		New calling routine interfaces.
		<7+>	 4/17/90	RLC		Add reference to HMFillCitationString routine.
		<6+>	  4/5/90	RLC		Update to latest interfaces & add HMExtractHelpMsg intf.
		 <6>	  4/4/90	KSM		Included Traps.h and changed references to 'ourPackNum' to
									_Pack14.
		<3+>	 1/19/90	RLC		Update selectors and interfaces.
		 <3>	 1/11/90	RLC		Fix those silly typedef and include the right interfaces.
		<1+>	 1/10/90	RLC		Update defines and include new error codes.
	   <1.0>	11/30/89	RLC		Added back into EASE for those C programmersÉ
				  6/6/89	RLC		New Today!

************************************************************/


#ifndef __BALLOONS__
#define __BALLOONS__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif

#ifndef __MENUS__
#include <Menus.h>
#endif

#ifndef __TRAPS__
#include <Traps.h>
#endif


enum {

 hmBalloonHelpVersion = 0x0002,			/* The real version of the Help Manager */

/*Help Mgr error range: -850 to -874*/
 hmHelpDisabled = -850,					/* Show Balloons mode was off, call to routine ignored */
 hmBalloonAborted = -853,				/* Returned if mouse was moving or mouse wasn't in window port rect */
 hmSameAsLastBalloon = -854,			/* Returned from HMShowMenuBalloon if menu & item is same as last time */
 hmHelpManagerNotInited = -855,			/* Returned from HMGetHelpMenuHandle if help menu not setup */
 hmSkippedBalloon = -857,				/* Returned from calls if helpmsg specified a skip balloon */
 hmWrongVersion = -858,					/* Returned if help mgr resource was the wrong version */
 hmUnknownHelpType = -859,				/* Returned if help msg record contained a bad type */
 hmOperationUnsupported = -861,			/* Returned from HMShowBalloon call if bad method passed to routine */
 hmNoBalloonUp = -862,					/* Returned from HMRemoveBalloon if no balloon was visible when call was made */
 hmCloseViewActive = -863,				/* Returned from HMRemoveBalloon if CloseView was active */

 kHMHelpMenuID = -16490,				/* Resource ID and menu ID of help menu */
 kHMAboutHelpItem = 1,					/* help menu item number of About Balloon HelpÉ */
 kHMShowBalloonsItem = 3,				/* help menu item number of Show/Hide Balloons */

 kHMHelpID = -5696,						/* ID of various Help Mgr package resources (in Pack14 range) */
 kBalloonWDEFID = 126,					/* Resource ID of the WDEF proc used in standard balloons */

/* Dialog item template type constant */
 helpItem = 1,							/* key value in DITL template that corresponds to the help item */

/* Options for Help Manager resources in 'hmnu', 'hdlg', 'hrct', 'hovr', & 'hfdr' resources */
 hmDefaultOptions = 0,					/* default options for help manager resources */
 hmUseSubID = 1,						/* treat resID's in resources as subID's of driver base ID (for Desk Accessories) */
 hmAbsoluteCoords = 2					/* ignore window port origin and treat rectangles as absolute coords (local to window) */
};
enum {
 hmSaveBitsNoWindow = 4,				/* don't create a window, just blast bits on screen. No update event is generated */
 hmSaveBitsWindow = 8,					/* create a window, but restore bits behind window when window goes away & generate update event */
 hmMatchInTitle = 16,					/* for hwin resources, match string anywhere in window title string */

/* Constants for Help Types in 'hmnu', 'hdlg', 'hrct', 'hovr', & 'hfdr' resources */
 kHMStringItem = 1,						/* pstring used in resource */
 kHMPictItem = 2,						/* 'PICT' ResID used in resource */
 kHMStringResItem = 3,					/* 'STR#' ResID & index used in resource */
 kHMTEResItem = 6,						/* Styled Text Edit ResID used in resource ('TEXT' & 'styl') */
 kHMSTRResItem = 7,						/* 'STR ' ResID used in resource */
 kHMSkipItem = 256,						/* don't display a balloon */
 kHMCompareItem = 512,					/* Compare pstring in menu item w/ PString in resource item ('hmnu' only) */
 kHMNamedResourceItem = 1024,			/* Use pstring in menu item to get 'STR#', 'PICT', or 'STR ' resource ('hmnu' only) */
 kHMTrackCntlItem = 2048,				/* Reserved */

/* Constants for hmmHelpType's when filling out HMMessageRecord */
 khmmString = 1,						/* help message contains a PString */
 khmmPict = 2,							/* help message contains a resource ID to a 'PICT' resource */
 khmmStringRes = 3,						/* help message contains a res ID & index to a 'STR#' resource */
 khmmTEHandle = 4,						/* help message contains a Text Edit handle */
 khmmPictHandle = 5,					/* help message contains a Picture handle */
 khmmTERes = 6,							/* help message contains a res ID to 'TEXT' & 'styl' resources */
 khmmSTRRes = 7,						/* help message contains a res ID to a 'STR ' resource */

/* ResTypes for Styled TE Handles in Resources */

#define kHMTETextResType 'TEXT'			/* Resource Type of text data for styled TE record w/o style info */
#define kHMTEStyleResType 'styl'		/* Resource Type of style information for styled TE record */

/* Generic defines for the state parameter used when extracting 'hmnu' & 'hdlg' messages */

 kHMEnabledItem = 0						/* item is enabled, but not checked or control value = 0 */
};
enum {
 kHMDisabledItem = 1,					/* item is disabled, grayed in menus or disabled in dialogs */
 kHMCheckedItem = 2,					/* item is enabled, and checked or control value = 1 */
 kHMOtherItem = 3,						/* item is enabled, and control value > 1 */

/* Resource Types for whichType parameter used when extracting 'hmnu' & 'hdlg' messages */

#define kHMMenuResType 'hmnu'			/* ResType of help resource for supporting menus */
#define kHMDialogResType 'hdlg'			/* ResType of help resource for supporting dialogs */
#define kHMWindListResType 'hwin'		/* ResType of help resource for supporting windows */
#define kHMRectListResType 'hrct'		/* ResType of help resource for rectangles in windows */
#define kHMOverrideResType 'hovr'		/* ResType of help resource for overriding system balloons */
#define kHMFinderApplResType 'hfdr'		/* ResType of help resource for custom balloon in Finder */

/* Method parameters to pass to HMShowBalloon */

 kHMRegularWindow = 0,					/* Create a regular window floating above all windows */
 kHMSaveBitsNoWindow = 1,				/* Just save the bits and draw (for MDEF calls) */
 kHMSaveBitsWindow = 2					/* Regular window, save bits behind, AND generate update event */
};

struct HMStringResType {
 short hmmResID;
 short hmmIndex;
};

typedef struct HMStringResType HMStringResType;

struct HMMessageRecord {
 short hmmHelpType;
 union {
  char hmmString[256];
  short hmmPict;
  Handle hmmTEHandle;
  HMStringResType hmmStringRes;
  short hmmPictRes;
  Handle hmmPictHandle;
  short hmmTERes;
  short hmmSTRRes;
  } u;
};

typedef struct HMMessageRecord HMMessageRecord;
typedef HMMessageRecord *HMMessageRecPtr;


#ifdef __cplusplus
extern "C" {
#endif
/*  Public Interfaces  */
pascal OSErr HMGetHelpMenuHandle(MenuHandle *mh)
 = {0x303C,0x0200,_Pack14}; 
pascal OSErr HMShowBalloon(const HMMessageRecord *aHelpMsg,
                           Point tip,
                           RectPtr alternateRect,
                           Ptr tipProc,
                           short theProc,
                           short variant,
                           short method)
 = {0x303C,0x0B01,_Pack14}; 
pascal OSErr HMRemoveBalloon(void)
 = {0x303C,0x0002,_Pack14}; 
pascal Boolean HMGetBalloons(void)
 = {0x303C,0x0003,_Pack14}; 
pascal OSErr HMSetBalloons(Boolean flag)
 = {0x303C,0x0104,_Pack14}; 
pascal OSErr HMShowMenuBalloon(short itemNum,
                               short itemMenuID,
                               long itemFlags,
                               long itemReserved,
                               Point tip,
                               RectPtr alternateRect,
                               Ptr tipProc,
                               short theProc,
                               short variant)
 = {0x303C,0x0E05,_Pack14}; 
pascal OSErr HMGetIndHelpMsg(ResType whichType,
                             short whichResID,
                             short whichMsg,
                             short whichState,
                             long *options,
                             Point *tip,
                             Rect *altRect,
                             short *theProc,
                             short *variant,
                             HMMessageRecord *aHelpMsg,
                             short *count)
 = {0x303C,0x1306,_Pack14}; 
pascal Boolean HMIsBalloon(void)
 = {0x303C,0x0007,_Pack14}; 
pascal OSErr HMSetFont(short font)
 = {0x303C,0x0108,_Pack14}; 
pascal OSErr HMSetFontSize(short fontSize)
 = {0x303C,0x0109,_Pack14}; 
pascal OSErr HMGetFont(short *font)
 = {0x303C,0x020A,_Pack14}; 
pascal OSErr HMGetFontSize(short *fontSize)
 = {0x303C,0x020B,_Pack14}; 
pascal OSErr HMSetDialogResID(short resID)
 = {0x303C,0x010C,_Pack14}; 
pascal OSErr HMSetMenuResID(short menuID,
                            short resID)
 = {0x303C,0x020D,_Pack14}; 
pascal OSErr HMBalloonRect(const HMMessageRecord *aHelpMsg,
                           Rect *coolRect)
 = {0x303C,0x040E,_Pack14}; 
pascal OSErr HMBalloonPict(const HMMessageRecord *aHelpMsg,
                           PicHandle *coolPict)
 = {0x303C,0x040F,_Pack14}; 
pascal OSErr HMScanTemplateItems(short whichID,
                                 short whichResFile,
                                 ResType whichType)
 = {0x303C,0x0410,_Pack14}; 
pascal OSErr HMExtractHelpMsg(ResType whichType,short whichResID,short whichMsg,
 short whichState,HMMessageRecord *aHelpMsg)
 = {0x303C,0x0711,_Pack14}; 
pascal OSErr HMGetDialogResID(short *resID)
 = {0x303C,0x0213,_Pack14}; 
pascal OSErr HMGetMenuResID(short menuID,short *resID)
 = {0x303C,0x0314,_Pack14}; 
pascal OSErr HMGetBalloonWindow(WindowPtr *window)
 = {0x303C,0x0215,_Pack14}; 
#ifdef __cplusplus
}
#endif

#endif
