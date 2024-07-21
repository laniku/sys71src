
/************************************************************

Created: Saturday, July 27, 1991 at 6:14 PM
 Retrace.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <5>	 7/31/91	JL		Updated Copyright.
		 <4>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <3>	10/21/90	gbm		(with dba) Made compatible with 3.2 C compiler (and incompatible
									with previous compilers).
	<3>		10/10/90	JAL	New style #Pragma Parameters for MPW 3.2 C

************************************************************/


#ifndef __RETRACE__
#define __RETRACE__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif


typedef pascal void (*VBLProcPtr)(void);

struct VBLTask {
 QElemPtr qLink;
 short qType;
 VBLProcPtr vblAddr;
 short vblCount;
 short vblPhase;
};

typedef struct VBLTask VBLTask;


#ifdef __cplusplus
extern "C" {
#endif
#define GetVBLQHdr() ((QHdrPtr) 0x0160)
#pragma parameter __D0 SlotVInstall(__A0,__D0)
pascal OSErr SlotVInstall(QElemPtr vblBlockPtr,short theSlot)
 = 0xA06F; 
#pragma parameter __D0 SlotVRemove(__A0,__D0)
pascal OSErr SlotVRemove(QElemPtr vblBlockPtr,short theSlot)
 = 0xA070; 
#pragma parameter __D0 AttachVBL(__D0)
pascal OSErr AttachVBL(short theSlot)
 = 0xA071; 
#pragma parameter __D0 DoVBLTask(__D0)
pascal OSErr DoVBLTask(short theSlot)
 = 0xA072; 
#pragma parameter __D0 VInstall(__A0)
pascal OSErr VInstall(QElemPtr vblTaskPtr)
 = 0xA033; 
#pragma parameter __D0 VRemove(__A0)
pascal OSErr VRemove(QElemPtr vblTaskPtr)
 = 0xA034; 
#ifdef __cplusplus
}
#endif

#endif
