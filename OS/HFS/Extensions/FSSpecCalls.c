/*
	File: 		FSSpecCalls.c

	Contains:	The FSp wrapper calls to the file system

	Written by:	Dave Feldman
	
	Copyright:	© 1990-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
			
		<11>	  4/4/92	FM		#1021881,<DTY>: Add two new calls to turn the ProcessMgr's file
									tracking on and off. SuspendFileTracking and ResumeFileTracking.
									These wil be internal calls for a while.
		<10>	 9/13/91	JSM		Cleanup header.
		 <9>	 1/13/91	dnf		(jdr) Add compatibility code for FSpExchangeFiles.
		 <8>	12/21/90	JL		changed constStrxxParameter to ConstStrxxxParam to match change
									in Types.h
		 <7>	12/14/90	dnf		(w/dba) Have FSpDirCreate use SetCatInfo instead of SetFInfo.
									Changed FSSpecPtr to use const on all calls except FSMakeFSSpec.
									Changed const StringPtr (which doesn't work) to
									constStr255Parameter (which does). Get the resource error with
									RESERR.
		 <6>	10/30/90	dnf		Set script code byte on create calls. Set ResErr on resource
									manager calls. Switch to PBxxxSync calls.
		 <5>	 10/2/90	JAL		Changed all occurances of .hfileInfo to .hFileInfo to match Interface change
		 <4>	 8/28/90	dnf		Add FSpExchangeFiles
		 <3>	  8/6/90	dnf		Rename implementation routines to use two underscores.
		 <2>	  8/6/90	dnf		Changed routine headers to match latest in files.h.
		 <1>	  8/6/90	dnf		first checked in

*/


#include <Types.h>
#include <Errors.h>
#include <Files.h>
#include <MFPrivate.h>	// <11>
#include <Resources.h>
#include <Traps.h>
#include <SysEqu.h>

/* this is needed for Resource Manager glue */

#define RESERR (* (OSErr *) ResErr)


/* Utility Routine */

/*	Munge a script manager style script code word into encoding used
	for Finder xInfo.
	
	In script manager-land, values 0-64 are defined and
	-1 and -2 are special marker values.  The Finder xInfo
	definition is that 0 implies "unused" and a high bit 
	set indicates that the byte is in use.  The script manager's
	-1 and -2 marker values have no meaning on disk, so this
	encoding works out.
*/
char	ConvertScriptCodeToDiskForm(ScriptCode scriptTag)
{
	char diskScriptCode;
	
	if (scriptTag >= 0)
		diskScriptCode = scriptTag | 0x80;		/* set high bit to mark valid */
	else
		diskScriptCode = 0;						/* garbage, so leave unused */
	return(diskScriptCode);

}

/* File Manager routines */

pascal OSErr __FSpOpenDF(const FSSpec* spec, char permission, short *refNum)
{
	OSErr			error;
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = spec -> vRefNum;
	pb.fileParam.ioDirID = spec -> parID;
	pb.ioParam.ioNamePtr = (StringPtr) &(spec -> name);
	pb.ioParam.ioVersNum = 0;
	pb.ioParam.ioPermssn = permission;
	pb.ioParam.ioMisc = nil;
	error = PBHOpenDFSync(&pb);
	*refNum = pb.ioParam.ioRefNum;
	return(error);
}

pascal OSErr __FSpOpenRF(const FSSpec* spec, char permission, short *refNum)
{
	OSErr			error;
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = spec -> vRefNum;
	pb.fileParam.ioDirID = spec -> parID;
	pb.ioParam.ioNamePtr = (StringPtr) &(spec -> name);
	pb.ioParam.ioVersNum = 0;
	pb.ioParam.ioPermssn = permission;
	pb.ioParam.ioMisc = nil;
	error = PBHOpenRFSync(&pb);
	*refNum = pb.ioParam.ioRefNum;
	return(error);
}

pascal OSErr __FSpCreate(const FSSpec* spec, OSType creator, OSType fileType, ScriptCode scriptTag)
{
	OSErr			error;
	HFileInfo		pb;
	
	pb.ioVRefNum = spec -> vRefNum;
	pb.ioDirID = spec -> parID;
	pb.ioNamePtr = (StringPtr) &(spec -> name);
	pb.ioFVersNum = 0;
	((HParmBlkPtr) &pb) -> ioParam.ioVersNum = 0;
	error = PBHCreateSync((HParmBlkPtr) &pb);
	if (error == noErr) {
		pb.ioFDirIndex = 0;
		error = PBHGetFInfoSync((HParmBlkPtr) &pb);
		if (error == noErr) {
			pb.ioFlXFndrInfo.fdScript = ConvertScriptCodeToDiskForm(scriptTag);
			pb.ioFlFndrInfo.fdCreator = creator;
			pb.ioFlFndrInfo.fdType = fileType;
			pb.ioDirID = spec -> parID;			
			error = PBHSetFInfoSync((HParmBlkPtr)&pb);
		}
	}
	return(error);
}

pascal OSErr __FSpDirCreate(const FSSpec* spec,  ScriptCode scriptTag, long *createdDirID)
{
	OSErr			error;
	CInfoPBRec		cinfo;

	cinfo.dirInfo.ioVRefNum = spec -> vRefNum;
	cinfo.dirInfo.ioDrDirID = spec -> parID;
	cinfo.dirInfo.ioNamePtr = (StringPtr) &(spec -> name);
	error = PBDirCreateSync((HParmBlkPtr) &cinfo);
	*createdDirID = cinfo.dirInfo.ioDrDirID;
	if (error == noErr) {
		cinfo.dirInfo.ioFDirIndex = 0;
		cinfo.dirInfo.ioDrDirID = spec -> parID;
		error = PBGetCatInfoSync(&cinfo);
		if (error == noErr) {
			cinfo.dirInfo.ioDrFndrInfo.frScript = ConvertScriptCodeToDiskForm(scriptTag);
			cinfo.dirInfo.ioDrDirID = spec -> parID;			
			error = PBSetCatInfoSync(&cinfo);
		}
	}
	return(error);
}

pascal OSErr __FSpDelete(const FSSpec* spec)
{
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = spec -> vRefNum;
	pb.fileParam.ioDirID = spec -> parID;
	pb.ioParam.ioNamePtr = (StringPtr) &(spec -> name);
	pb.ioParam.ioVersNum = 0;
	return(PBHDeleteSync(&pb));
}

pascal OSErr __FSpGetFInfo(const FSSpec* spec, FInfo *fndrInfo)
{
	OSErr			error;
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = spec -> vRefNum;
	pb.fileParam.ioDirID = spec -> parID;
	pb.ioParam.ioNamePtr = (StringPtr) &(spec -> name);
	pb.ioParam.ioVersNum = 0;
	pb.fileParam.ioFDirIndex = 0;
	error = PBHGetFInfoSync(&pb);
	*fndrInfo = pb.fileParam.ioFlFndrInfo;
	return(error);
}

pascal OSErr __FSpSetFInfo(const FSSpec* spec, const FInfo *fndrInfo)
{
	OSErr			error;
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = spec -> vRefNum;
	pb.fileParam.ioDirID = spec -> parID;
	pb.ioParam.ioNamePtr = (StringPtr) &(spec -> name);
	pb.ioParam.ioVersNum = 0;
	pb.fileParam.ioFDirIndex = 0;
	error = PBHGetFInfoSync(&pb);
	if (error == noErr) {
		pb.fileParam.ioFlFndrInfo = *fndrInfo;
		pb.fileParam.ioDirID = spec -> parID;
		error = PBHSetFInfoSync(&pb);
	}
	return(error);
}

pascal OSErr __FSpSetFLock(const FSSpec* spec)
{
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = spec -> vRefNum;
	pb.fileParam.ioDirID = spec -> parID;
	pb.ioParam.ioNamePtr = (StringPtr) &(spec -> name);
	pb.ioParam.ioVersNum = 0;
	return(PBHSetFLockSync(&pb));
}

pascal OSErr __FSpRstFLock(const FSSpec* spec)
{
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = spec -> vRefNum;
	pb.fileParam.ioDirID = spec -> parID;
	pb.ioParam.ioNamePtr = (StringPtr) &(spec -> name);
	pb.ioParam.ioVersNum = 0;
	return(PBHRstFLockSync(&pb));
}

pascal OSErr __FSpRename(const FSSpec* spec, ConstStr255Param newName)
{
	HParamBlockRec	pb;

	pb.ioParam.ioVRefNum = spec -> vRefNum;
	pb.fileParam.ioDirID = spec -> parID;
	pb.ioParam.ioNamePtr = (StringPtr) &(spec -> name);
	pb.ioParam.ioVersNum = 0;
	pb.ioParam.ioMisc = (Ptr) newName;
	return(PBHRenameSync(&pb));
}

pascal OSErr __FSpCatMove(const FSSpec* source, const FSSpec* dest)
{
	CMovePBRec	pb;

	if (source -> vRefNum != dest -> vRefNum)
		return(paramErr);
	pb.ioNamePtr = (StringPtr) &(source -> name);
	pb.ioVRefNum = source -> vRefNum;
	pb.ioDirID = source -> parID;
	pb.ioNewDirID = dest -> parID;
	pb.ioNewName = (StringPtr) &(dest -> name);
	return(PBCatMoveSync(&pb));
}

pascal short __FSpOpenResFile(const FSSpec* spec, char permission)
{
	return(HOpenResFile(spec -> vRefNum, spec -> parID, &(spec -> name), permission));
}

pascal void __FSpCreateResFile(const FSSpec* spec, OSType creator, OSType fileType, ScriptCode scriptTag)
{
	OSErr			error;
	HFileInfo		pb;

	HCreateResFile(spec -> vRefNum, spec -> parID, &(spec -> name));
	if (RESERR == noErr) {
		pb.ioVRefNum = spec -> vRefNum;
		pb.ioDirID = spec -> parID;
		pb.ioNamePtr = (StringPtr) &(spec -> name);
		((HParmBlkPtr) &pb) -> ioParam.ioVersNum = 0;
		pb.ioFDirIndex = 0;
		error = PBHGetFInfoSync((HParmBlkPtr) &pb);
		if (error == noErr) {
			pb.ioFlXFndrInfo.fdScript = ConvertScriptCodeToDiskForm(scriptTag);
			pb.ioFlFndrInfo.fdCreator = creator;
			pb.ioFlFndrInfo.fdType = fileType;
			pb.ioDirID = spec -> parID;			
			error = PBHSetFInfoSync((HParmBlkPtr) &pb);
		}
		RESERR = error;
	}
}

pascal OSErr __FSMakeFSSpec( short vRefNum, long dirID, ConstStr255Param fileName, FSSpec* spec)
{
	HParamBlockRec		pb;
	
	pb.fileParam.ioNamePtr = fileName;
	pb.fileParam.ioVRefNum = vRefNum;
	pb.fileParam.ioDirID = dirID;
	pb.ioParam.ioMisc = (Ptr) spec;
	return(PBMakeFSSpecSync(&pb));
}

// This one isn’t in the interfaces anywhere, but is in the dispatcher.
// We dreamed it up for use by FSpExchangeFiles, but it’s a bit late 
// to make it into Inside Mac.  Feel free to add this call later.
pascal OSErr __FSpGetCatInfo(const FSSpec* spec, CInfoPBPtr cinfo)
{
	cinfo -> hFileInfo.ioVRefNum = spec -> vRefNum;
	cinfo -> hFileInfo.ioFDirIndex = 0;
	cinfo -> hFileInfo.ioNamePtr = (StringPtr) &(spec -> name);
	cinfo -> hFileInfo.ioDirID = spec -> parID;
	return(PBGetCatInfoSync(cinfo));
}

// These 2 routines were needed by Akiko for opening dictionary files.			<11>
// Right now they just call BeginSysMode and EndSysMode. Hopefully in the		<11>
// future we will be able to release these calls to developers, but for 		<11>
// now they are internal only.


// Prevent files opened from being closed when the current process
// quits!

pascal OSErr __SuspendProcessMgrFileTracking(void)	// <11>
{
	OSErr	err;
	
	err = BeginSystemMode();
	
	return err;
}

// Now any files opened will close when the current process
// quits…

pascal OSErr __ResumeProcessMgrFileTracking(void)		// <11>
{
	OSErr	err;
	
	err = EndSystemMode();
	
	return err;
}

OSErr IsFile(const FSSpec* spec)
{
	CInfoPBRec		cinfo;
	OSErr			error;
	
	if (error = __FSpGetCatInfo(spec, &cinfo))
		return(error);
	if (cinfo.hFileInfo.ioFlAttrib & ioDirMask)
		return(notAFileErr);
	else
		return(noErr);
}

OSErr GenerateUniqueName(short volume, long *startSeed, long dir1, long dir2, StringPtr uniqueName)
{
	OSErr			error = noErr;
	long			i;
	CInfoPBRec		cinfo;
	
	cinfo.hFileInfo.ioVRefNum = volume;
	cinfo.hFileInfo.ioFDirIndex = 0;
	cinfo.hFileInfo.ioNamePtr = uniqueName;

	while (error != fnfErr) {
		(*startSeed)++;		
		cinfo.hFileInfo.ioNamePtr[0] = 8;
		for (i = 1; i <= 8; i++)
			cinfo.hFileInfo.ioNamePtr[i] = "0123456789ABCDEF"[((*startSeed >> ((8-i)*4)) & 0xf)];
		cinfo.hFileInfo.ioDirID = dir1;
		error = fnfErr;
		for (i = 1; i <= 2; i++) {
			error = error &  PBGetCatInfoSync(&cinfo);
			cinfo.hFileInfo.ioDirID = dir2;
			if ((error != fnfErr) && (error != noErr))
				return(error);
		}
	}
	return(noErr);
}

pascal OSErr __FSpExchangeFiles(const FSSpec* source, const FSSpec* dest)
{
	HParamBlockRec			pb;
	CInfoPBRec				catInfoSource, catInfoDest;
	OSErr					error, error2;
	Str31					unique1, unique2;			// our strings are never more than 11 characters long
	StringPtr				unique1Ptr, unique2Ptr, swapola;
	GetVolParmsInfoBuffer	volInfo;
	long					theSeed, temp;

	if (source -> vRefNum != dest -> vRefNum)
		return(paramErr);
	pb.fidParam.ioNamePtr = (StringPtr) &(source -> name);
	pb.fidParam.ioVRefNum = source -> vRefNum;
	pb.fidParam.ioDestNamePtr = (StringPtr) &(dest -> name);
	pb.fidParam.ioDestDirID = dest -> parID;
	pb.fidParam.ioSrcDirID = source -> parID;

	error = PBExchangeFilesSync(&pb);

	// note that the compatibility case won't work for files with Btree control blocks.
	// Right now only system-like files use btrees
	if (error) {

		pb.ioParam.ioNamePtr = nil;
		pb.ioParam.ioBuffer = (Ptr) &volInfo;
		pb.ioParam.ioReqCount = sizeof(volInfo);
		error2 = PBHGetVolParmsSync(&pb);
		
		// continue if volume has no fileID support (or no GetVolParms support)
		if ((error2 == noErr) && (volInfo.vMAttrib & (1<<bHasFileIDs)))
			return(error);

		// make sure both files are really files
		if ((error = IsFile(source)) || (error = IsFile(dest)))
			return(error);

		// generate 2 filenames that are unique in both directories
		theSeed = 0x64666364;						// a fine unlikely filename
		unique1Ptr = &unique1;
		unique2Ptr = &unique2;
		
		if (error = GenerateUniqueName(source -> vRefNum, &theSeed, source -> parID, dest -> parID, unique1Ptr))
			return(error);

		if (error = GenerateUniqueName(source -> vRefNum, &theSeed, source -> parID, dest -> parID, unique2Ptr))
			return(error);

		// get the catalog info for each file
		if (error = __FSpGetCatInfo(source, &catInfoSource))
			return(error);
		if (error = __FSpGetCatInfo(dest, &catInfoDest))
			return(error);

		// rename source to unique1
		pb.fileParam.ioNamePtr = (StringPtr) &(source -> name);
		pb.ioParam.ioMisc = (Ptr) unique1Ptr;
		if (error = PBHRenameSync(&pb))
			return(error);		
		
		// rename dest to unique2
		pb.ioParam.ioMisc = (Ptr) unique2Ptr;
		pb.fileParam.ioNamePtr = (StringPtr) &(dest -> name);
		pb.fileParam.ioDirID = dest -> parID;
		if (error = PBHRenameSync(&pb))
			goto error2;
		
		// move source file to dest directory
		pb.copyParam.ioNamePtr = unique1Ptr;
		pb.copyParam.ioNewName = nil;
		pb.copyParam.ioNewDirID = dest -> parID;
		pb.copyParam.ioDirID = source -> parID;
		if (error = PBCatMoveSync((CMovePBPtr) &pb))
			goto error1;

		// move dest file to source directory
		pb.copyParam.ioNamePtr = unique2Ptr;
		pb.copyParam.ioNewDirID = source -> parID;
		pb.copyParam.ioDirID = dest -> parID;
		if (error = PBCatMoveSync((CMovePBPtr) &pb)) {
			// life is very bad.  We'll at least try to move source back
			pb.copyParam.ioNamePtr = unique1Ptr;
			pb.copyParam.ioNewName = nil;
			pb.copyParam.ioNewDirID = source -> parID;
			pb.copyParam.ioDirID = dest -> parID;
			PBCatMoveSync((CMovePBPtr) &pb);		// ignore errors
		} else {
			// make unique1 point to file in dest
			swapola = unique1Ptr;
			unique1Ptr = unique2Ptr;
			unique2Ptr = swapola;
		}

		// swap the catalog info by re-aiming the CInfoPB's
		catInfoSource.hFileInfo.ioNamePtr = unique2Ptr;
		catInfoDest.hFileInfo.ioNamePtr = unique1Ptr;
		
		catInfoSource.hFileInfo.ioDirID = dest -> parID;
		catInfoDest.hFileInfo.ioDirID = source -> parID;
		
		// leave original mod dates w/each file
		temp = catInfoSource.hFileInfo.ioFlMdDat;
		catInfoSource.hFileInfo.ioFlMdDat = catInfoDest.hFileInfo.ioFlMdDat;
		catInfoDest.hFileInfo.ioFlMdDat = temp;
		
		// ignore errors
		PBSetCatInfoSync(&catInfoSource); 
		PBSetCatInfoSync(&catInfoDest);
		
		// rename unique2 back to dest
error1:
		pb.ioParam.ioMisc = (Ptr) &(dest -> name);
		pb.fileParam.ioNamePtr = unique2Ptr;
		pb.fileParam.ioDirID = dest -> parID;
		PBHRenameSync(&pb); // ignore errors

		// rename unique1 back to source
error2:
		pb.ioParam.ioMisc = (Ptr) &(source -> name);
		pb.fileParam.ioNamePtr = unique1Ptr;
		pb.fileParam.ioDirID = source -> parID;
		PBHRenameSync(&pb); // ignore errors
	}
	return(error);
}
