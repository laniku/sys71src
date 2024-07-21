/************************************************************
	CTBUtilities.h
	C Interface to the CommToolBox Utilities

		Copyright Apple Computer, Inc. 1988-1991
		All rights reserved

	Change History (most recent first):

		<11>	 3/31/92	JSM		Include StandardFile.h instead of Packages.h.
		<10>	 8/28/91	CH		Updated interface headers for consistency.
		 <9>	 7/25/91	JL		Checked in database generated file from DSG. Changed all
									#defines to anonymous enums.
									Added names to already existing enums.
		 <8>	 6/25/91	JNG		Move DITL manipulation calls to Dialogs.h
		 <7>	 6/17/91	JL		Checked in official MPW 3.2Ä version. Restored function
									parameter names taken out by Darin. Added the word "extern" to
									the cplusplus conditional. Temporarily lost updated copyright
									date; will be restored. Updated header (first 6 lines of this
									file) to match shipped version.
		 <6>	 1/26/91	stb		dba: change LookupReply to NBPReply
		 <4>	 11/4/90	dba		got rid of some obsolete use of __cplusplus; used
									constStr255Parameter; got rid of some extraneous parameter names
		 <3>	 10/3/90	kaz		Changing // comments for ANSI compatibility <jng>
		 <2>	 9/15/90	PWD		Added _StandardNBP in prep for renaming _NuLookup.
		 <1>	 3/12/90	BBH		first checked in

************************************************************/


#ifndef __CTBUTILITIES__
#define __CTBUTILITIES__

#ifndef	__MEMORY__
#include <Memory.h>
#endif

#ifndef __STANDARDFILE__
#include <StandardFile.h>
#endif

#ifndef __APPLETALK__
#include <AppleTalk.h>
#endif


enum {


/*	version of Comm Toolbox Utilities	*/
 curCTBUVersion = 2,

/*    Error codes/types    */
 ctbuGenericError = -1,
 ctbuNoErr = 0
};

typedef		OSErr	CTBUErr;

enum {chooseDisaster = -2,chooseFailed,chooseAborted,chooseOKMinor,chooseOKMajor,
	chooseCancel};
typedef unsigned short ChooseReturnCode;

enum {nlOk,nlCancel,nlEject};
typedef unsigned short NuLookupReturnCode;

enum {nameInclude = 1,nameDisable,nameReject};
typedef unsigned short NameFilterReturnCode;

enum {zoneInclude = 1,zoneDisable,zoneReject};
typedef unsigned short ZoneFilterReturnCode;


enum {


/*	Values for hookProc items		*/
 hookOK = 1,
 hookCancel = 2,
 hookOutline = 3,
 hookTitle = 4,
 hookItemList = 5,
 hookZoneTitle = 6,
 hookZoneList = 7,
 hookLine = 8,
 hookVersion = 9,
 hookReserved1 = 10,
 hookReserved2 = 11,
 hookReserved3 = 12,
 hookReserved4 = 13,

/*	"virtual" hookProc items	*/
 hookNull = 100,
 hookItemRefresh = 101,
 hookZoneRefresh = 102,
 hookEject = 103,
 hookPreflight = 104,
 hookPostflight = 105,
 hookKeyBase = 1000
};


/*	NuLookup structures/constants	*/
struct NLTypeEntry {
	Handle hIcon;
	Str32 typeStr;
};

typedef struct NLTypeEntry NLTypeEntry;


typedef NLTypeEntry NLType[4];

struct NBPReply {
	EntityName	theEntity;
	AddrBlock	theAddr;
};

typedef struct NBPReply NBPReply;


typedef pascal short (*NameFilterProcPtr)(EntityName theEntity);
typedef pascal short (*ZoneFilterProcPtr)(Str32 theZone);

typedef NameFilterProcPtr nameFilterProcPtr;
typedef ZoneFilterProcPtr zoneFilterProcPtr;

#ifdef __cplusplus
extern "C" {
#endif
pascal CTBUErr	InitCTBUtilities(void);
pascal short 	CTBGetCTBVersion(void);


pascal short 	StandardNBP(Point where,ConstStr255Param prompt,short numTypes,
					NLType typeList,NameFilterProcPtr nameFilter,ZoneFilterProcPtr zoneFilter,
					DlgHookProcPtr hookProc,NBPReply *theReply);

pascal short 	CustomNBP(Point where,ConstStr255Param prompt,short numTypes,
					NLType typeList,NameFilterProcPtr nameFilter,ZoneFilterProcPtr zoneFilter,
					DlgHookProcPtr hookProc,long userData,short dialogID,ModalFilterProcPtr filterProc,
					NBPReply *theReply);

/*  Obsolete synonyms for above routines  */
pascal short 	NuLookup(Point where,ConstStr255Param prompt,short numTypes,
					NLType typeList,NameFilterProcPtr nameFilter,ZoneFilterProcPtr zoneFilter,
					DlgHookProcPtr hookProc,NBPReply *theReply);

pascal short 	NuPLookup(Point where,ConstStr255Param prompt,short numTypes,
					NLType typeList,NameFilterProcPtr nameFilter,ZoneFilterProcPtr zoneFilter,
					DlgHookProcPtr hookProc,long userData,short dialogID,ModalFilterProcPtr filterProc,
					NBPReply *theReply);
#ifdef __cplusplus
}
#endif

#endif