
/************************************************************

Created: Saturday, July 27, 1991 at 5:05 PM
 Notification.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1989-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <7>	 7/30/91	JL		Updated Copyright.
		 <6>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <5>	 11/7/90	JL		Changed all #defines to anonymous enums
		 <4>	 10/9/90	JAL		Checked in MPW version.
		 <3>	 8/31/90	VL		Changed the switch __ALLNU__ to __NOTIFICATION__.
		 <2>	 7/16/90	VL		Changed nmSIcon to nmIcon and fixed the prototyping of the
									interface routines.
************************************************************/


#ifndef __NOTIFICATION__
#define __NOTIFICATION__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif


enum {

 nmType = 8
};

typedef pascal void (*NMProcPtr)(struct NMRec *);

struct NMRec {
 QElemPtr qLink;	/*next queue entry*/
 short qType;		/*queue type -- ORD(nmType) = 8*/
 short nmFlags;		/*reserved*/
 long nmPrivate;	/*reserved*/
 short nmReserved;	/*reserved*/
 short nmMark;		/*item to mark in Apple menu*/
 Handle nmIcon;		/*handle to small icon*/
 Handle nmSound;	/*handle to sound record*/
 StringPtr nmStr;	/*string to appear in alert*/
 NMProcPtr nmResp;	/*pointer to response routine*/
 long nmRefCon;		/*for application use*/
};

typedef struct NMRec NMRec;
typedef NMRec *NMRecPtr;


#ifdef __cplusplus
extern "C" {
#endif
pascal OSErr NMInstall(NMRecPtr nmReqPtr)
 = {0x205F,0xA05E,0x3E80}; 
pascal OSErr NMRemove(NMRecPtr nmReqPtr)
 = {0x205F,0xA05F,0x3E80}; 
#ifdef __cplusplus
}
#endif

#endif
