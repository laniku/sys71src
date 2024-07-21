/*
	File:		HFSGlue.c

	Contains:	File Manager, Device Manager and Resource Manager glue for HFS

	Written by:	Darin Adler

	Copyright:	© 1990-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <7>	11/21/91	JL		Added inclusion of Memory.h for StripAddress.
		 <6>	11/21/91	JL		In HOpenResFile, called StripAddress for the fileName passed in
									the OpenRFPerm call. This gives support for System 6 running on
									the Mac Classic. This works around the known bug in the resource
									manager. Radar #106686.
		 <5>	 7/29/91	gbm		Avoid a naming problem created by making HOpenResFile and
									HCreateResFile in-lines
		 <4>	  8/6/90	dnf		Remove the FSp glue routines.
		 <3>	  8/6/90	dnf		Change the name of MakeFSSpec to FSMakeFSSpec since it's a high
									level call
		 <2>	  6/2/90	dnf		Add FSSpec versions for appropriate calls

	modified	10/18/88	dba		added interfaces for PBOpenFile, PBHOpenFile,
									PBOpenDriver, OpenFile, HOpenFile, OpenDriver;
									note that OpenDriver replaces an existing glue
									routine *** NO IMPLEMENTATION YET ***
	modified	10/18/88	dba		another crack at HOpenResFile
	modified	9/24/88		dba		HOpenResFile bug fixed
	created		8/3/88		dba

*/


#include <Types.h>
#include <Errors.h>
#include <Files.h>
#include <Resources.h>
#include <Traps.h>
#include <SysEqu.h>
#include <Memory.h>


/* trap numbers (remove when they are in Traps.h) */

#define _HOpenResFile 0xA81A
#define _HCreateResFile 0xA81B

/* this is needed for Resource Manager glue */

#define RESERR (* (OSErr *) ResErr)

/* this is needed to check if the new Resource Manager traps exist */

#define SYSVERSION (* (short *) SysVersion)


/* File Manager routines */


pascal OSErr HGetVol(StringPtr volName, short *vRefNum, long *dirID)
{
	OSErr	error;
	WDPBRec	pb;

	pb.ioNamePtr = volName;
	error = PBHGetVol(&pb, false);
	*vRefNum = pb.ioVRefNum;
	*dirID = pb.ioWDDirID;
	return(error);
}


pascal OSErr HSetVol(StringPtr volName, short vRefNum, long dirID)
{
	WDPBRec	pb;

	pb.ioNamePtr = volName;
	pb.ioVRefNum = vRefNum;
	pb.ioWDDirID = dirID;
	return(PBHSetVol(&pb, false));
}


pascal OSErr HOpen(short vRefNum, long dirID, const Str255 fileName, char permission, short *refNum)
{
	OSErr			error;
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = vRefNum;
	pb.fileParam.ioDirID = dirID;
	pb.ioParam.ioNamePtr = (StringPtr) fileName;
	pb.ioParam.ioVersNum = 0;
	pb.ioParam.ioPermssn = permission;
	pb.ioParam.ioMisc = nil;
	error = PBHOpen(&pb, false);
	*refNum = pb.ioParam.ioRefNum;
	return(error);
}

pascal OSErr HOpenDF(short vRefNum, long dirID, const Str255 fileName, char permission, short *refNum)
{
	OSErr			error;
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = vRefNum;
	pb.fileParam.ioDirID = dirID;
	pb.ioParam.ioNamePtr = (StringPtr) fileName;
	pb.ioParam.ioVersNum = 0;
	pb.ioParam.ioPermssn = permission;
	pb.ioParam.ioMisc = nil;
	error = PBHOpenDF(&pb, false);
	*refNum = pb.ioParam.ioRefNum;
	return(error);
}

pascal OSErr HOpenRF(short vRefNum, long dirID, const Str255 fileName, char permission, short *refNum)
{
	OSErr			error;
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = vRefNum;
	pb.fileParam.ioDirID = dirID;
	pb.ioParam.ioNamePtr = (StringPtr) fileName;
	pb.ioParam.ioVersNum = 0;
	pb.ioParam.ioPermssn = permission;
	pb.ioParam.ioMisc = nil;
	error = PBHOpenRF(&pb, false);
	*refNum = pb.ioParam.ioRefNum;
	return(error);
}

pascal OSErr AllocContig(short refNum, long *count)
{
	OSErr			error;
	ParamBlockRec	pb;

	pb.ioParam.ioRefNum = refNum;
	pb.ioParam.ioReqCount = *count;
	error = PBAllocContig(&pb, false);
	*count = pb.ioParam.ioActCount;
	return(error);
};


pascal OSErr HCreate(short vRefNum, long dirID, const Str255 fileName, OSType creator, OSType fileType)
{
	OSErr			error;
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = vRefNum;
	pb.fileParam.ioDirID = dirID;
	pb.ioParam.ioNamePtr = (StringPtr) fileName;
	pb.ioParam.ioVersNum = 0;
	error = PBHCreate(&pb, false);
	if (error == noErr) {
		pb.fileParam.ioFDirIndex = 0;
		error = PBHGetFInfo(&pb, false);
		if (error == noErr) {
			pb.fileParam.ioFlFndrInfo.fdCreator = creator;
			pb.fileParam.ioFlFndrInfo.fdType = fileType;
			pb.fileParam.ioDirID = dirID;
			error = PBHSetFInfo(&pb, false);
		}
	}
	return(error);
}

pascal OSErr DirCreate(short vRefNum, long parentDirID, const Str255 directoryName, long *createdDirID)
{
	OSErr			error;
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = vRefNum;
	pb.fileParam.ioDirID = parentDirID;
	pb.ioParam.ioNamePtr = (StringPtr) directoryName;
	error = PBDirCreate(&pb, false);
	*createdDirID = pb.fileParam.ioDirID;
	return(error);
}


pascal OSErr HDelete(short vRefNum, long dirID, const Str255 fileName)
{
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = vRefNum;
	pb.fileParam.ioDirID = dirID;
	pb.ioParam.ioNamePtr = (StringPtr) fileName;
	pb.ioParam.ioVersNum = 0;
	return(PBHDelete(&pb, false));
}

pascal OSErr HGetFInfo(short vRefNum, long dirID, const Str255 fileName, FInfo *fndrInfo)
{
	OSErr			error;
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = vRefNum;
	pb.fileParam.ioDirID = dirID;
	pb.ioParam.ioNamePtr = (StringPtr) fileName;
	pb.ioParam.ioVersNum = 0;
	pb.fileParam.ioFDirIndex = 0;
	error = PBHGetFInfo(&pb, false);
	*fndrInfo = pb.fileParam.ioFlFndrInfo;
	return(error);
}


pascal OSErr HSetFInfo(short vRefNum, long dirID, const Str255 fileName, const FInfo *fndrInfo)
{
	OSErr			error;
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = vRefNum;
	pb.fileParam.ioDirID = dirID;
	pb.ioParam.ioNamePtr = (StringPtr) fileName;
	pb.ioParam.ioVersNum = 0;
	pb.fileParam.ioFDirIndex = 0;
	error = PBHGetFInfo(&pb, false);
	if (error == noErr) {
		pb.fileParam.ioFlFndrInfo = *fndrInfo;
		pb.fileParam.ioDirID = dirID;
		error = PBHSetFInfo(&pb, false);
	}
	return(error);
}


pascal OSErr HSetFLock(short vRefNum, long dirID, const Str255 fileName)
{
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = vRefNum;
	pb.fileParam.ioDirID = dirID;
	pb.ioParam.ioNamePtr = (StringPtr) fileName;
	pb.ioParam.ioVersNum = 0;
	return(PBHSetFLock(&pb, false));
}


pascal OSErr HRstFLock(short vRefNum, long dirID, const Str255 fileName)
{
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = vRefNum;
	pb.fileParam.ioDirID = dirID;
	pb.ioParam.ioNamePtr = (StringPtr) fileName;
	pb.ioParam.ioVersNum = 0;
	return(PBHRstFLock(&pb, false));
}


pascal OSErr HRename(short vRefNum, long dirID, const Str255 oldName, const Str255 newName)
{
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = vRefNum;
	pb.fileParam.ioDirID = dirID;
	pb.ioParam.ioNamePtr = (StringPtr) oldName;
	pb.ioParam.ioVersNum = 0;
	pb.ioParam.ioMisc = (Ptr) newName;
	return(PBHRename(&pb, false));
}

pascal OSErr CatMove(short vRefNum, long dirID, const Str255 oldName, long newDirID, const Str255 newName)
{
	CMovePBRec	pb;

	pb.ioNamePtr = (StringPtr) oldName;
	pb.ioVRefNum = vRefNum;
	pb.ioDirID = dirID;
	pb.ioNewDirID = newDirID;
	pb.ioNewName = (StringPtr) newName;
	return(PBCatMove(&pb, false));
}


pascal OSErr OpenWD(short vRefNum, long dirID, long procID, short *wdRefNum)
{
	OSErr	error;
	WDPBRec	pb;

	pb.ioVRefNum = vRefNum;
	pb.ioWDDirID = dirID;
	pb.ioWDProcID = procID;
	pb.ioNamePtr = nil;
	error = PBOpenWD(&pb, false);
	*wdRefNum = pb.ioVRefNum;
	return(error);
}


pascal OSErr CloseWD(short wdRefNum)
{
	WDPBRec	pb;

	pb.ioVRefNum = wdRefNum;
	return(PBCloseWD(&pb, false));
}


pascal OSErr GetWDInfo(short wdRefNum, short *vRefNum, long *dirID, long *procID)
{
	OSErr	error;
	WDPBRec	pb;

	pb.ioVRefNum = wdRefNum;
	pb.ioWDIndex = 0;
	pb.ioNamePtr = nil;
	error = PBGetWDInfo(&pb, false);
	*vRefNum = pb.ioWDVRefNum;
	*dirID = pb.ioWDDirID;
	*procID = pb.ioWDProcID;
	return(error);
}


/* Resource Manager routines */


pascal short ROMHOpenResFile(short vRefNum, long dirID, const Str255 fileName, char permission)
	= _HOpenResFile;


/* This module gets renamed to HOpenResFile in the lib statement in the Interface.Make file */
pascal short HOpenResFileGlue(short vRefNum, long dirID, const Str255 fileName, char permission)
{
	if ((SYSVERSION >= 0x0600) && (GetTrapAddress(_Unimplemented) != NGetTrapAddress(_HOpenResFile, ToolTrap)))
		return(ROMHOpenResFile(vRefNum, dirID, fileName, permission));
	else {
		OSErr	error;
		short	refNum;
		short	openRFRefNum;
		short	savedVRefNum;
		long	savedDirID;
		short	parsedVRefNum;
		long	parsedDirID;
		long	parsedProcID;
		OSErr	setVolError;

		refNum = -1;
		error = HOpenRF(vRefNum, dirID, fileName, permission, &openRFRefNum);
		if (error == noErr)
			error = FSClose(openRFRefNum);
		if ((error == noErr) || (error == opWrErr)) {
			error = HGetVol(nil, &savedVRefNum, &savedDirID);
			if (error == noErr) {

				/* determine if the default volume was a wdRefNum */

				error = GetWDInfo(savedVRefNum, &parsedVRefNum, &parsedDirID, &parsedProcID);
				if (error == noErr) {
					error = HSetVol(nil, vRefNum, dirID);
					if (error == noErr) {
						refNum = OpenRFPerm((StringPtr)StripAddress((Ptr)fileName), 0, permission);
						error = ResError();
					}

					/* if the default volume was a wdRefNum, the dirID that we
						parsed out of it will be something other than the root
						(which indicates a vRefNum). We should use a regular
						SetVol call if it was a wdRefNum, and an HSetVol if it
						was a vRefNum (possibly with a dirID). */

					if (parsedDirID == fsRtDirID)
						setVolError = HSetVol(nil, savedVRefNum, savedDirID);
					else
						setVolError = SetVol(nil, savedVRefNum);
					if (error == noErr)
						error = setVolError;
				}
			}
		}
		RESERR = error;
		return(refNum);
	}
}

pascal void ROMHCreateResFile(short vRefNum, long dirID, const Str255 fileName)
	= _HCreateResFile;

/* This module gets renamed to HCreateResFile in the lib statement in the Interface.Make file */
pascal void HCreateResFileGlue(short vRefNum, long dirID, const Str255 fileName)
{
	if ((SYSVERSION >= 0x0600) && (GetTrapAddress(_Unimplemented) != NGetTrapAddress(_HCreateResFile, ToolTrap)))
		ROMHCreateResFile(vRefNum, dirID, fileName);
	else {
		OSErr	error;
		short	refNum;
		short	savedVRefNum;
		long	savedDirID;
		short	parsedVRefNum;
		long	parsedDirID;
		long	parsedProcID;
		OSErr	setVolError;

		error = HOpenRF(vRefNum, dirID, fileName, fsCurPerm, &refNum);
		if (error == noErr)
			error = FSClose(refNum);
		if (error == fnfErr) {
			error = HCreate(vRefNum, dirID, fileName, 0, 0);
		}
		if (error == noErr) {
			error = HGetVol(nil, &savedVRefNum, &savedDirID);
			if (error == noErr) {

				/* determine if the default volume was a wdRefNum */

				error = GetWDInfo(savedVRefNum, &parsedVRefNum, &parsedDirID, &parsedProcID);
				if (error == noErr) {
					error = HSetVol(nil, vRefNum, dirID);
					if (error == noErr) {
						CreateResFile(fileName);
						error = ResError();
					}

					/* if the default volume was a wdRefNum, the dirID that we
						parsed out of it will be something other than the root
						(which indicates a vRefNum). We should use a regular
						SetVol call if it was a wdRefNum, and an HSetVol if it
						was a vRefNum (possibly with a dirID). */

					if (parsedDirID == fsRtDirID)
						setVolError = HSetVol(nil, savedVRefNum, savedDirID);
					else
						setVolError = SetVol(nil, savedVRefNum);
					if (error == noErr)
						error = setVolError;
				}
			}
		}
		RESERR = error;
	}
}

/* put more implementations here */

pascal OSErr PBOpenDriver(ParmBlkPtr paramBlock);
pascal OSErr OpenDriver(const Str255 driverName, short *refNum);
