/************************************************************
	CommResources.h
	C Interface to the Communications Resource Manager

		Copyright Apple Computer, Inc. 1988-1991
		All rights reserved
  
    This file is used in these builds: ROM System

	Change History (most recent first):

		<14>	 8/28/91	CH		Updated interface headers for consistency.
		<13>	 8/20/91	BH		move CRMReserveRF into public interfaces
		<12>	 8/14/91	JL		Added comment to match pascal file.
		<11>	  8/9/91	JNG		Moved CRMReleaseRF into main interfaces
		<10>	 7/25/91	JL		Checked in database generated file from DSG.  Changed all
									#defines to anonymous enums.
									Moved declaration of CRMErr and error constants to match Pascal
									file.
		 <9>	  7/9/91	BH		add CRMGetToolNamedResource
		 <8>	  7/3/91	BH		added CRMParseCAPSResource
		 <7>	 6/25/91	JNG		Added CRMIsDriverOpen
		 <6>	 6/18/91	JL		Restoring parameter types of ConstStr255Param to replace const
									str255 types.
		 <5>	 6/17/91	JL		Checked in official MPW 3.2Ä version. Restored function
									parameter names taken out by Darin. Temporarily changed
									parameter types with ConstStr255Param to const str255 to make
									the file match the shipped version. Changed parameter name of
									the functions: CRMInstall, CRMRemove, CRMSearch from crmRecPtr
									to crmReqPtr to match Pascal file. Added the word "extern" to
									the cplusplus conditional. Updated header (first 6 lines of this
									file) to match shipped version. Changed parameter names of
									CRMReleaseResource, CRMReleaseToolResource and CRMGetIndex from
									theResource to theHandle to match pascal file. Temporarily
									changed first param type of CRMGetIndToolName from a ResType to
									an OSType to match shipped version.
		 <3>	 11/4/90	dba		correct the use of __cplusplus and __safe_link; use
									constStr255Parameter for parameters; get rid of some extraneous
									parameter names
		 <2>	 10/3/90	kaz		Changing comment style for ANSI compatibility <jng>
		 <1>	 3/12/90	BBH		first checked in
************************************************************/


#ifndef __COMMRESOURCES__
#define __COMMRESOURCES__

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif


enum {


/*	version of the Comm Resource Manager	*/
	curCRMVersion = 2,

/*	tool classes (also the tool file types)	*/

#define				classCM				'cbnd'
#define				classFT				'fbnd'
#define				classTM				'tbnd'

/* constants general to the use of the Communications Resource Manager */

	crmType = 9,			/* queue type	*/
	crmRecVersion = 1,		/* version of queue structure */

/*	error codes */
	crmGenericError = -1,
	crmNoErr = 0
};

/* data structures general to the use of the Communications Resource Manager */
typedef				OSErr	CRMErr;

struct CRMRec {
 QElemPtr qLink;		/*reserved*/
 short qType;			/*queue type -- ORD(crmType) = 9*/
 short crmVersion;		/*version of queue element data structure*/
 long crmPrivate;		/*reserved*/
 short crmReserved;		/*reserved*/
 long crmDeviceType;	/*type of device, assigned by DTS*/
 long crmDeviceID;		/*device ID; assigned when CRMInstall is called*/
 long crmAttributes;	/*pointer to attribute block*/
 long crmStatus;		/*status variable - device specific*/
 long crmRefCon;		/*for device private use*/
};

typedef struct CRMRec CRMRec;
typedef CRMRec *CRMRecPtr;


#ifdef __cplusplus
extern "C" {
#endif
pascal CRMErr 	InitCRM(void);
pascal QHdrPtr 	CRMGetHeader(void);
pascal void 	CRMInstall(QElemPtr crmReqPtr);
pascal OSErr 	CRMRemove(QElemPtr crmReqPtr);
pascal QElemPtr CRMSearch(QElemPtr crmReqPtr);
pascal short 	CRMGetCRMVersion(void);

pascal Handle 	CRMGetResource(ResType theType,short theID);
pascal Handle 	CRMGet1Resource(ResType theType,short theID);
pascal Handle 	CRMGetIndResource(ResType theType,short index);
pascal Handle 	CRMGet1IndResource(ResType theType,short index);
pascal Handle 	CRMGetNamedResource(ResType theType,ConstStr255Param name);
pascal Handle 	CRMGet1NamedResource(ResType theType,ConstStr255Param name);
pascal void 	CRMReleaseResource(Handle theHandle);
pascal Handle 	CRMGetToolResource(short procID,ResType theType,short theID);
pascal Handle 	CRMGetToolNamedResource(short procID,ResType theType,ConstStr255Param name);
pascal void   	CRMReleaseToolResource(short procID,Handle theHandle);
pascal long 	CRMGetIndex(Handle theHandle);

pascal short 	CRMLocalToRealID(ResType bundleType,short toolID,ResType theType,
 short localID);
pascal short 	CRMRealToLocalID(ResType bundleType,short toolID,ResType theType,
 short realID);

pascal OSErr	CRMGetIndToolName(OSType bundleType,short index,Str255 toolName);

pascal OSErr 	CRMFindCommunications(short *vRefNum,long *dirID);

pascal Boolean	CRMIsDriverOpen(ConstStr255Param driverName);

pascal CRMErr	CRMParseCAPSResource(Handle theHandle,ResType selector,unsigned long *value);

pascal OSErr	CRMReserveRF(short refNum);
pascal OSErr	CRMReleaseRF(short refNum);
#ifdef __cplusplus
}
#endif

#endif