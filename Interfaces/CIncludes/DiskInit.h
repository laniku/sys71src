
/************************************************************

Created: Saturday, July 27, 1991 at 3:00 PM
 DiskInit.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc.  1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <7>	 7/30/91	JL		Updated Copyright.
		 <6>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <4>	 11/4/90	dba		use constStr255Parameter

** 1.1	CCH 11/ 9/1988 Fixed headers and removed projector resource.
** 1.0	CCH 11/ 9/1988 Adding to EASE.
************************************************************/


#ifndef __DISKINIT__
#define __DISKINIT__

#ifndef __TYPES__
#include <Types.h>
#endif


struct HFSDefaults {
 char sigWord[2];	/* signature word*/
 long abSize;		/* allocation block size in bytes*/
 long clpSize;		/* clump size in bytes*/
 long nxFreeFN;		/* next free file number*/
 long btClpSize;	/* B-Tree clump size in bytes*/
 short rsrv1;		/* reserved*/
 short rsrv2;		/* reserved*/
 short rsrv3;		/* reserved*/
};

typedef struct HFSDefaults HFSDefaults;


#ifdef __cplusplus
extern "C" {
#endif
pascal void DILoad(void); 
pascal void DIUnload(void); 
pascal short DIBadMount(Point where,long evtMessage); 
OSErr dibadmount(Point *where,long evtMessage); 
pascal OSErr DIFormat(short drvNum); 
pascal OSErr DIVerify(short drvNum); 
pascal OSErr DIZero(short drvNum,ConstStr255Param volName); 
OSErr dizero(short drvnum,char *volName); 
#ifdef __cplusplus
}
#endif

#endif
