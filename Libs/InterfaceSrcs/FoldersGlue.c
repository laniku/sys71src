/*
	File:		FoldersGlue.c

	Contains:	FindFolder (also known as Folder Manager) glue for 7.0 Apps
				that will allow them to run on 6.0 also.

	Written by:	Prashant Patel

	Copyright:	© 1990-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <4>	11/14/91	JL		Had to change ifndef of SystemSevenOrLater to If it was false
									because it's always defined in Types.h.
		 <3>	11/13/91	JL		Changed kSupportSysDir to kNoSupportsSysDir and changed logic to
									check for System Folder support. The 17th bit of vMAttrib is set
									if there is no support - the logic got confusing. This fixes the
									bug about not recognizing a System Folder on a drive that has
									one.
		 <2>	 11/4/91	JSM		Conditionalize glue for pre-System 7 only.
		 <1>	11/13/90	PP		(PP/dba) first checked in

*/


#include <Folders.h>
#include <GestaltEqu.h>
#include <SysEqu.h>
#include <Errors.h>
#include <Files.h>

/* Real FindFolder Trap in Sys 7.0. */
pascal OSErr
__FindFolder(short vRefNum, OSType, Boolean createFolder, short* foundVRefNum, long* foundDirID)
	= { 0x7000, 0xA823 };

#if !(SystemSevenOrLater)

/* need glue for FindFolder for pre-7.0 systems */

/* Global Reference number of system resource file (word) */
#define SYSMAP (* (short *) SysMap)

#define kNoSupportsSysDir (1<<17)  // Does volume support System Folder?  <3>

typedef struct 
	{ // GetVolParms buffer
	short	version;
	long	attributes;
	} VolParmsBuf;


pascal OSErr FindFolder(short vRefNum, 
						OSType folderType, 
						Boolean createFolder, 
						short* foundVRefNum, 
						long* foundDirID)
{
	OSErr		error;				// return code
	long		result;				// Gestalt result
	Boolean		findFolderPresent = false;
	HParamBlockRec  hpb;			// generic h Param Block
	VolParmsBuf		volumeParms;	// answer from GetVolParms
	
	/* Determine if real FindFolder is present or not. */
	error = Gestalt( gestaltFindFolderAttr, &result );
	if (error == noErr)
		{
		if (result & (1<<gestaltFindFolderPresent))
			findFolderPresent = true;
		}

	if (findFolderPresent)
		return (__FindFolder(vRefNum, folderType, createFolder, foundVRefNum, foundDirID));

	else
		{
		/* Folders that do not reside in System Folder are not valid for 6.0.  
		In such a case, return paramErr. 
		*/
		
		if (folderType != kSystemFolderType &&
			folderType != kTemporaryFolderType && 
			folderType != kPreferencesFolderType && 
			folderType != kExtensionFolderType &&
			folderType != kControlPanelFolderType &&
			folderType != kAppleMenuFolderType &&
			folderType != kStartupFolderType &&
			folderType != kPrintMonitorDocsFolderType)
				return (paramErr);
			
		hpb.fileParam.ioNamePtr = nil;		// not interested in name

		if (vRefNum == (short)kOnSystemDisk)  // vRefNum of Boot disk
			{
			/* Get vRefNum of the System disk.  HParamBlockRec mapped to FCBPBRec. */
			hpb.fileParam.ioFRefNum = SYSMAP;	// the system file's refNum
			hpb.fileParam.ioFDirIndex = 0;		// get file by refNum
			(*(FCBPBPtr)&hpb).ioFCBParID = fsRtDirID; // init in case of an MFS disk
			error = PBGetFCBInfoSync ((FCBPBPtr) &hpb);
			if (error != noErr)
				goto EXIT;

			/* cooked vRefNum is returned in ioFCBVRefNum. */
			hpb.volumeParam.ioVRefNum = (*(FCBPBPtr)&hpb).ioFCBVRefNum;
			} 
		else
			hpb.volumeParam.ioVRefNum = vRefNum;
				
		/* Get volume params for this disk, specially the attributes bits. */

		hpb.ioParam.ioReqCount = sizeof (VolParmsBuf);	// size of return buffer
		hpb.ioParam.ioBuffer = (Ptr) &volumeParms;	// pointer to return buffer
		error = PBHGetVolParmsSync (&hpb);

		if (error == paramErr || // just lack of PBHGetVolParms
		  	  (error == noErr && !(volumeParms.attributes & kNoSupportsSysDir))) // System Folder supported  <3>
			{
			/* Get cooked vRefNum and System Folder dirID by calling HGetVInfo. */
			hpb.volumeParam.ioVolIndex = 0;			// get info by vRefNum
			hpb.volumeParam.ioVFndrInfo[0] = 0;		// init in case of an MFS disk
			hpb.fileParam.ioDirID = 0;		// *** bug related to changing working Dir???
			error = PBHGetVInfoSync (&hpb);
			if (error != noErr)
				goto EXIT;
				
			if (hpb.volumeParam.ioVFndrInfo[0] != 0) // System Folder dirID on this disk
				{
				*foundVRefNum = hpb.volumeParam.ioVRefNum; // cooked vRefNum is returned
				*foundDirID = hpb.volumeParam.ioVFndrInfo[0]; // System Folder dirID on this disk
				} 
			else
				error = fnfErr;			
			} 
		else if (error == noErr)
			error = fnfErr;
						
		}

EXIT:

	return (error);
}

#endif