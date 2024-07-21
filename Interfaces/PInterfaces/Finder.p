
{
Created: Tuesday, November 26, 1991 at 11:43 AM
 Finder.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1990-1991
  All rights reserved

    This file is used in these builds: BigBang

	Change History (most recent first):

		 <3>	11/27/91	JL		Added Finder Flag definitions.
		 <2>	 7/23/91	JL		Checked in File from database. Took out Includes because they
									are not needed right now.
		 <2>	 1/23/91	PP		(FJS) Define kCustomIconResource constant.
		 <1>	 1/19/91	PP		first checked in
		 <0>	 1/18/91	PP		created from Internal:C:FinderPriv.h

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Finder;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingFinder}
{$SETC UsingFinder := 1}


CONST

{ make only the following consts avaiable to resource files that include this file }
kCustomIconResource = -16455;			{ Custom icon family resource ID }

kContainerFolderAliasType = 'fdrp';		{ type for folder aliases }
kContainerTrashAliasType = 'trsh';		{ type for trash folder aliases }
kContainerHardDiskAliasType = 'hdsk';	{ type for hard disk aliases }
kContainerFloppyAliasType = 'flpy';		{ type for floppy aliases }
kContainerServerAliasType = 'srvr';		{ type for server aliases }
kApplicationAliasType = 'adrp';			{ type for application aliases }
kContainerAliasType = 'drop';			{ type for all other containers }

{ type for Special folder aliases }
kSystemFolderAliasType = 'fasy';
kAppleMenuFolderAliasType = 'faam';
kStartupFolderAliasType = 'fast';
kPrintMonitorDocsFolderAliasType = 'fapn';
kPreferencesFolderAliasType = 'fapf';
kControlPanelFolderAliasType = 'fact';
kExtensionFolderAliasType = 'faex';

{ type for AppleShare folder aliases }
kExportedFolderAliasType = 'faet';
kDropFolderAliasType = 'fadr';
kSharedFolderAliasType = 'fash';
kMountedFolderAliasType = 'famn';


{Finder Flags}
kIsOnDesk = $1;
kColor = $E;

{kColorReserved = $10
kRequiresSwitchLaunch = $20}

kIsShared = $40;

{kHasNoINITs = $80}

kHasBeenInited = $100;

{kReserved = $200}

kHasCustomIcon = $400;
kIsStationary = $800;
kNameLocked = $1000;
kHasBundle = $2000;
kIsInvisible = $4000;
kIsAlias = $8000;



{$ENDC} { UsingFinder }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

