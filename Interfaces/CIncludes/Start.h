
/************************************************************

Created: Saturday, July 27, 1991 at 7:01 PM
 Start.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1987-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <5>	 7/31/91	JL		Updated Copyright.
		 <4>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <3>	10/21/90	gbm		(with dba) Made compatible with 3.2 C compiler (and incompatible
									with previous compilers).
		<3>		10/3/90		JAL		Added pragmas after code review of glue.
************************************************************/


#ifndef __START__
#define __START__

#ifndef __TYPES__
#include <Types.h>
#endif


struct SlotDev {
 char sdExtDevID;
 char sdPartition;
 char sdSlotNum;
 char sdSRsrcID;
};

typedef struct SlotDev SlotDev;

struct SCSIDev {
 char sdReserved1;
 char sdReserved2;
 short sdRefNum;
};

typedef struct SCSIDev SCSIDev;

union DefStartRec {
 SlotDev slotDev;
 SCSIDev scsiDev;
};

typedef union DefStartRec DefStartRec;
typedef DefStartRec *DefStartPtr;

struct DefVideoRec {
 char sdSlot;
 char sdsResource;
};

typedef struct DefVideoRec DefVideoRec;
typedef DefVideoRec *DefVideoPtr;

struct DefOSRec {
 char sdReserved;
 char sdOSType;
};

typedef struct DefOSRec DefOSRec;
typedef DefOSRec *DefOSPtr;


#ifdef __cplusplus
extern "C" {
#endif
#pragma parameter GetDefaultStartup(__A0)
pascal void GetDefaultStartup(DefStartPtr paramBlock)
 = 0xA07D; 
#pragma parameter SetDefaultStartup(__A0)
pascal void SetDefaultStartup(DefStartPtr paramBlock)
 = 0xA07E; 
#pragma parameter GetVideoDefault(__A0)
pascal void GetVideoDefault(DefVideoPtr paramBlock)
 = 0xA080; 
#pragma parameter SetVideoDefault(__A0)
pascal void SetVideoDefault(DefVideoPtr paramBlock)
 = 0xA081; 
#pragma parameter GetOSDefault(__A0)
pascal void GetOSDefault(DefOSPtr paramBlock)
 = 0xA084; 
#pragma parameter SetOSDefault(__A0)
pascal void SetOSDefault(DefOSPtr paramBlock)
 = 0xA083; 
pascal void SetTimeout(short count); 
pascal void GetTimeout(short *count); 
#ifdef __cplusplus
}
#endif

#endif
