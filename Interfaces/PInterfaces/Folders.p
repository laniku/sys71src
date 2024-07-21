
{
Created: Saturday, July 27, 1991 at 9:18 PM
 Folders.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1989-1991
  All rights reserved


	Change History (most recent first):

		<11>	 5/12/92	DTY		Add kFontsFolderType.
		<10>	 7/30/91	JL		Updated Copyright.
		 <9>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <8>	12/14/90	dba		<JDR> change SystemSevenOrBetter to SystemSevenOrLater
		 <7>	11/13/90	PP		(PP/ngk) FindFolder has glue for 6.0 support.
		 <6>	  5/3/90	PP		Change kSpoolFolderType to kPrintMonitorDocsFolderType.
		 <5>	 3/20/90	PP		Remove obsolete folder types.
		 <4>	 2/19/90	PP		Add equate for "Control Panels" folder and remove equate for
									kINITFolderType.

** 1.2	prp 10/02/1989 Added Finder "Extension Folder" as kExtensionFolderType.
** 1.1	prp 06/08/1989 Alias Manager Trap # changed from $A825 to $A823
** 1.0	prp 06/02/1989 Initial release. Folder manager now part of alias
**		manager.
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Folders;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingFolders}
{$SETC UsingFolders := 1}

{$I+}
{$SETC FoldersIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingFiles}
{$I $$Shell(PInterfaces)Files.p}
{$ENDC}
{$SETC UsingIncludes := FoldersIncludes}

CONST
kOnSystemDisk = $8000;

kCreateFolder = TRUE;
kDontCreateFolder = FALSE;

kSystemFolderType = 'macs';				{the system folder}
kDesktopFolderType = 'desk';			{the desktop folder; objects in this folder show on the desk top.}
kTrashFolderType = 'trsh';				{the trash folder; objects in this folder show up in the trash}
kWhereToEmptyTrashFolderType = 'empt';	{the "empty trash" folder; Finder starts empty from here down}

kPrintMonitorDocsFolderType = 'prnt';	{ Print Monitor documents }

kStartupFolderType = 'strt';			{Finder objects (applications, documents, DAs, aliases, to...) to open at startup go here}
kAppleMenuFolderType = 'amnu';			{Finder objects to put into the Apple menu go here}
kControlPanelFolderType = 'ctrl';		{Control Panels go here (may contain INITs)}
kExtensionFolderType = 'extn';			{Finder extensions go here}
kFontsFolderType = 'font';				{Fonts go here}

kPreferencesFolderType = 'pref';		{preferences for applications go here}
kTemporaryFolderType = 'temp';			{temporary files go here (deleted periodically, but don't rely on it.)}

FUNCTION FindFolder(vRefNum: INTEGER;folderType: OSType;createFolder: BOOLEAN;
 VAR foundVRefNum: INTEGER;VAR foundDirID: LONGINT): OSErr;
{$IFC SystemSevenOrLater }
 INLINE $7000,$A823;
{$ENDC}


{$ENDC} { UsingFolders }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

