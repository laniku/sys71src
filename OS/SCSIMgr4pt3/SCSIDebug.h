/*
	File:		SCSIDebug.h

	Contains:	header stuff for various debugging stuff

	Written by:	Paul Wolf

	Copyright:	╘ 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	   <SM4>	11/22/93	pdw		Rolling in from <MCxx>.
	   <SM3>	10/14/93	pdw		<MC> roll-in.
	   <MC2>	 9/26/93	pdw		Added forIttInit default.
	   <SM2>	 6/29/93	pdw		Adding a few and prettying it up a bit.
		 <1>	 5/27/93	PW		first checked in

*/

#ifndef __SCSIDebug__
#define __SCSIDebug__ 1


//ииииии Include_Debugger_Names ииииии routine names in .a  / IfDebugXXX shows up in .c

#ifndef Include_Debugger_Names
#define Include_Debugger_Names 0
#endif

#if Include_Debugger_Names
#define IfDebugger()  Debugger()
#define IfDebugStr( a ) DebugStr(a)
#else
#define IfDebugger()
#define	IfDebugStr( a )
#endif


//ииииии forceSyncAlways ииииии force all IOs to be handled synchronously

#ifndef forceSyncAlways
#define forceSyncAlways 0
#endif


//ииииии GPHYSICAL ииииии I don't know what this is

#ifndef GPHYSICAL
#define GPHYSICAL 1
#endif


//ииииии RECORD_ON ииииии turns recording of SCSI events on

#ifndef RECORD_ON
#define RECORD_ON 1
#endif

//ииииии ERR_RECORD_ON ииииии turns recording of SCSI events on

#ifndef ERR_RECORD_ON
#define ERR_RECORD_ON 1
#endif

//ииииии forIttInit ииииии building an Init

#ifndef forIttInit
#define forIttInit 0
#endif


#endif	// __SCSIDebug__
