
/************************************************************

Created: Saturday, July 27, 1991 at 3:22 PM
 Events.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		<SM1>	 10/26/92	CSS		Changes to support direct calling of traps rather than using the
									trap dispatcher.
		<13>	 6/11/92	DCL		Cleanup minor formatting to match Interface Stacks. Happy Happy
									Joy Joy.
		<12>	  5/6/92	DCL		NIIM: Moved KeyTrans back from TextUtils to Events and added
									synonym KeyTranslate.
		<11>	 3/26/92	JSM		Rolled this file into SuperMario project.
		<10>	 2/27/92	DCL		Combined Events.h and OSEvents.h (into Events.h) for NIIM (New
									Improved Inside Mac).
		 <9>	 7/30/91	JL		Updated Copyright. Restored comments.
		 <8>	 1/28/91	LN		Checked in Database generate file from DSG. Grouping enums into
									groups of 20. Put formal parameter names back. Put
									childDiedMessage back temporarily for compatiblity.
		 <7>	11/12/90	DFH		Removed childDiedMessage since it only applied to MultiFinder
									6.1, which was not officially released.
		 <6>	 11/9/90	DFH		Add highLevelEventMask
		 <5>	10/30/90	dba		make smaller versions of GetDblTime and GetCaretTime (with
									#define)
		 <4>	10/19/90	DFH		Added convertClipboardFlag.
		 <3>	10/19/90	DFH		Added resumeFlag.

************************************************************/


#ifndef __EVENTS__
#define __EVENTS__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif

#ifndef	__ROMFastTrapsIncluded__
#include "ROMFastTraps.h"
#endif

enum {

 nullEvent = 0,
 mouseDown = 1,
 mouseUp = 2,
 keyDown = 3,
 keyUp = 4,
 autoKey = 5,
 updateEvt = 6,
 diskEvt = 7,
 activateEvt = 8,
 osEvt = 15,

/* event mask equates */
 mDownMask = 2,
 mUpMask = 4,
 keyDownMask = 8,
 keyUpMask = 16,
 autoKeyMask = 32,
 updateMask = 64,
 diskMask = 128,
 activMask = 256,
 highLevelEventMask = 1024,
 osMask = -32768
};
enum {
 everyEvent = -1,

/* event message equates */
 charCodeMask = 0x000000FF,
 keyCodeMask = 0x0000FF00,
 adbAddrMask = 0x00FF0000,
 osEvtMessageMask = 0xFF000000,

/* OS event messages.  Event (sub)code is in the high byte of the message field. */
 mouseMovedMessage = 0xFA,
 suspendResumeMessage = 0x01,

 resumeFlag = 1,			/* Bit 0 of message indicates resume vs suspend */
 convertClipboardFlag = 2,	/* Bit 1 in resume message indicates clipboard change */

/* modifiers */
 activeFlag = 1,			/* Bit 0 of modifiers for activateEvt and mouseDown events */
 btnState = 128,			/* Bit 7 of low byte is mouse button state */
 cmdKey = 256,				/* Bit 0 */
 shiftKey = 512,			/* Bit 1 */
 alphaLock = 1024,			/* Bit 2 */
 optionKey = 2048,			/* Bit 3 of high byte */
 controlKey = 4096,

/* obsolete equates */
 networkEvt = 10,
 driverEvt = 11,
 app1Evt = 12,
 app2Evt = 13
};
enum {
 app3Evt = 14,
 app4Evt = 15,
 networkMask = 1024,
 driverMask = 2048,
 app1Mask = 4096,
 app2Mask = 8192,
 app3Mask = 16384,
 app4Mask = -32768
};

struct EventRecord {
 short what;
 long message;
 long when;
 Point where;
 short modifiers;
};

typedef struct EventRecord EventRecord;


typedef long KeyMap[4];


struct EvQEl {
 QElemPtr qLink;
 short qType;
 short evtQWhat;	/*this part is identical to the EventRecord as...*/
 long evtQMessage;	/*defined in ToolIntf*/
 long evtQWhen;
 Point evtQWhere;
 short evtQModifiers;
};

typedef struct EvQEl EvQEl;
typedef EvQEl *EvQElPtr;



#ifdef __cplusplus
extern "C" {
#endif

pascal Boolean GetNextEvent(short eventMask,EventRecord *theEvent)
 = {__GenToolboxTrapCode(0xA970)}; 
pascal Boolean WaitNextEvent(short eventMask,EventRecord *theEvent,unsigned long sleep,
 RgnHandle mouseRgn)
 = {__GenToolboxTrapCode(0xA860)}; 
pascal Boolean EventAvail(short eventMask,EventRecord *theEvent)
 = {__GenToolboxTrapCode(0xA971)}; 
pascal void GetMouse(Point *mouseLoc)
 = {__GenToolboxTrapCode(0xA972)}; 
pascal Boolean Button(void)
 = {__GenToolboxTrapCode(0xA974)}; 
pascal Boolean StillDown(void)
 = {__GenToolboxTrapCode(0xA973)}; 
pascal Boolean WaitMouseUp(void)
 = {__GenToolboxTrapCode(0xA977)}; 
pascal void GetKeys(KeyMap theKeys)
 = {__GenToolboxTrapCode(0xA976)}; 
pascal long KeyTranslate(const void *transData,short keycode,long *state)
 = {__GenToolboxTrapCode(0xA9C3)}; 
pascal long KeyTrans(const void *transData,short keycode,long *state)
 = {__GenToolboxTrapCode(0xA9C3)}; 
pascal unsigned long TickCount(void)
 = {__GenToolboxTrapCode(0xA975)}; 
#define GetDblTime() (* (unsigned long*) 0x02F0)
#define GetCaretTime() (* (unsigned long*) 0x02F4)

#pragma parameter __D0 PostEvent(__A0,__D0)
pascal OSErr PostEvent(short eventNum,long eventMsg)
 = {__GenOSTrapCode(0xA02F)}; 

#pragma parameter __D0 PPostEvent(__A0,__D0,__A1)
pascal OSErr PPostEvent(short eventCode,long eventMsg,EvQElPtr *qEl)
 = {__GenOSTrapCode(0xA12F),0x2288}; 

#pragma parameter __D0 OSEventAvail(__D0,__A0)
pascal Boolean OSEventAvail(short mask,EventRecord *theEvent)
 = {__GenOSTrapCode(0xA030),0x5240}; 

#pragma parameter __D0 GetOSEvent(__D0,__A0)
pascal Boolean GetOSEvent(short mask,EventRecord *theEvent)
 = {__GenOSTrapCode(0xA031),0x5240}; 

pascal void FlushEvents(short whichMask,short stopMask)
 = {0x201F,__GenOSTrapCode(0xA032)}; 
#pragma parameter SetEventMask(__D0)
pascal void SetEventMask(short theMask)
 = {0x31C0,0x0144}; 
#define GetEvQHdr() ((QHdrPtr) 0x014A)
#ifdef __cplusplus
}
#endif

#endif
