
/************************************************************

Created: Saturday, July 27, 1991 at 4:01 PM
 Folders.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1989-1992
  All rights reserved


	Change History (most recent first):

		<14>	 6/26/92	DCL		Miner Formatting Changes. Digging deep for things to do. Getting
									the file ready for ETO 8.
		<13>	 5/12/92	DTY		Add type for Fonts folder.
		<12>	 7/30/91	JL		Updated Copyright.
		<11>	 1/27/91	LN		Checked in Database generate file from DSG.
		<10>	12/14/90	dba		<JDR> change SystemSevenOrBetter to SystemSevenOrLater
		 <9>	11/13/90	PP		(PP/ngk) FindFolder has glue for 6.0 support.
		 <8>	  10/9/90	JAL		Official MPW version.
		 <7>	  5/3/90	PP		Change kSpoolFolderType to kPrintMonitorDocsFolderType.
		 <6>	 3/20/90	PP		Remove obsolete folder types.
		<3+>	 2/19/90	PP		Add equate for "Control Panels" folder and remove equate for
									kINITFolderType.

** 1.2	prp 10/02/1989 Added Finder "Extension Folder" as kExtensionFolderType.
** 1.1	prp 06/08/1989 Alias Manager Trap # changed from $A825 to $A823
** 1.0	prp 06/02/1989 Initial release. Folder manager now part of alias
************************************************************/


#ifndef __FOLDERS__
#define __FOLDERS__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __FILES__
#include <Files.h>
#endif


enum {

 kOnSystemDisk = 0x8000


#define kCreateFolder true
#define kDontCreateFolder false

#define kSystemFolderType				'macs'		/* the system folder */
#define kDesktopFolderType				'desk'		/* the desktop folder; objects in this folder show on the desk top. */
#define kTrashFolderType				'trsh'		/* the trash folder; objects in this folder show up in the trash */
#define kWhereToEmptyTrashFolderType	'empt'		/* the "empty trash" folder; Finder starts empty from here down */

#define kPrintMonitorDocsFolderType		'prnt'		/* Print Monitor documents */

#define kStartupFolderType				'strt'		/* Finder objects (applications, documents, DAs, aliases, to...) to open at startup go here */
#define kAppleMenuFolderType			'amnu'		/* Finder objects to put into the Apple menu go here */
#define kControlPanelFolderType 		'ctrl'		/* Control Panels go here (may contain INITs) */
#define kExtensionFolderType			'extn'		/* Finder extensions go here */
#define	kFontsFolderType				'font'		/* Fonts go here */
#define kPreferencesFolderType			'pref'		/* preferences for applications go here */
#define kTemporaryFolderType			'temp'		/* temporary files go here (deleted periodically, but don't rely on it.) */
};

#ifdef __cplusplus
extern "C" {
#endif
#if SystemSevenOrLater
pascal OSErr FindFolder(short vRefNum,OSType folderType,Boolean createFolder,
 short *foundVRefNum,long *foundDirID)
 = {0x7000,0xA823}; 
#else
pascal OSErr FindFolder(short vRefNum,OSType folderType,Boolean createFolder,
 short *foundVRefNum,long *foundDirID);
#endif
#ifdef __cplusplus
}
#endif

#endif
