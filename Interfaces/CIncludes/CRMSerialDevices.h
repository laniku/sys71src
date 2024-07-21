
/************************************************************

Created: Tuesday, July 23, 1991 at 5:45 PM
 CRMSerialDevices.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1988-1991
  All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <5>	 7/25/91	JL		Checked in database generated file from DSG.  Changed all
									#defines to anonymous enums.
		 <4>	 3/13/91	JL		MPW-ized the file.  Took off CPlusPlus conditional around struct
									typedefs.  (Not needed anymore.)
		 <3>	 10/3/90	kaz		Changing // comments for ANSI compatibility. <jng>
		 <2>	 10/2/90	kaz		Support for icon suites: deviceIcon is now a handle to a
									CRMIconRecord; bumped version #. <jng>
		 <1>	 3/12/90	BBH		first checked in

	To Do:
************************************************************/


#ifndef __CRMSERIALDEVICES__
#define __CRMSERIALDEVICES__

#ifndef __TYPES__
#include <Types.h>
#endif


enum {


/* 	for the crmDeviceType field of the CRMRec data structure	*/
 crmSerialDevice = 1,		


/*	version of the CRMSerialRecord below	*/
 curCRMSerRecVers = 1
};

/* Maintains compatibility w/ apps & tools that expect an old style icon	*/
struct CRMIconRecord {
	long		oldIcon[32];			/* ICN#	*/
	long		oldMask[32];
	Handle		theSuite;				/* Handle to an IconSuite	*/
	long		reserved;
};

typedef struct CRMIconRecord CRMIconRecord;
typedef CRMIconRecord *CRMIconPtr, **CRMIconHandle;

struct CRMSerialRecord {
	short			version;
	StringHandle	inputDriverName;
	StringHandle	outputDriverName;
	StringHandle	name;
	CRMIconHandle	deviceIcon;
	long			ratedSpeed;
	long			maxSpeed;
	long			reserved;
};

typedef struct CRMSerialRecord CRMSerialRecord;
typedef CRMSerialRecord *CRMSerialPtr;



#endif