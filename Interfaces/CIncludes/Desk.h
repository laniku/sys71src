
/************************************************************

Created: Saturday, July 27, 1991 at 2:53 PM
 Desk.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		<10>	 7/30/91	JL		Updated Copyright.
		 <9>	 1/30/91	JL		Grouped enums into groups of 20
		 <8>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <6>	12/12/90	JL		Put formal parameters back
		 <5>	 11/8/90	JL		Changed all #defines to anonymous enums
		 <4>	 11/4/90	dba		used constStr255Parameter; added more use of const in parameters

** 1.2	CCH 11/ 9/1988 Fixed Header.
** 1.1	CCH 11/ 9/1988 Fixed headers and removed projector resource.
** 1.0	CCH 11/ 9/1988 Adding to EASE.
************************************************************/


#ifndef __DESK__
#define __DESK__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif

#ifndef __EVENTS__
#include <Events.h>
#endif


enum {

 accEvent = 64,
 accRun = 65,
 accCursor = 66,
 accMenu = 67,
 accUndo = 68,
 accCut = 70,
 accCopy = 71,
 accPaste = 72,
 accClear = 73,
 goodbye = -1	/*goodbye message*/
};

#ifdef __cplusplus
extern "C" {
#endif
pascal short OpenDeskAcc(ConstStr255Param deskAccName)
 = 0xA9B6; 
pascal void CloseDeskAcc(short refNum)
 = 0xA9B7; 
pascal void SystemClick(const EventRecord *theEvent,WindowPtr theWindow)
 = 0xA9B3; 
pascal Boolean SystemEdit(short editCmd)
 = 0xA9C2; 
pascal void SystemTask(void)
 = 0xA9B4; 
pascal Boolean SystemEvent(const EventRecord *theEvent)
 = 0xA9B2; 
pascal void SystemMenu(long menuResult)
 = 0xA9B5; 
short opendeskacc(char *deskAccName); 
#ifdef __cplusplus
}
#endif

#endif
