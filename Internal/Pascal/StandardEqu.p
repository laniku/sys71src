{
	File:		StandardEqu.p

	Contains:	This must be USESed as the first unit.  It auto-includes
				all the common PInterfaces files and produces a ~400K symbol
				table stored in its resource fork.  This will significantly
				speed up future compiles.  
				
				If you make changes to this file, be sure to update the 
				makefile dependencies for StanardEqu.p

	Written by:	Nick Kledzik

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <3>	 3/23/92	JSM		OSEvents.p is obsolete, use Events.p instead.
		 <2>	  4/7/90	ngk		Fixed comments.
		 <1>	  4/7/90	ngk		First checked in.

	To Do:
}


UNIT StandardEqu;

INTERFACE

{$I+}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingAppleTalk}
{$I AppleTalk.p}
{$ENDC}
{$IFC UNDEFINED UsingControls}
{$I Controls.p}
{$ENDC}
{$IFC UNDEFINED UsingDevices}
{$I Devices.p}
{$ENDC}
{$IFC UNDEFINED UsingDialogs}
{$I Dialogs.p}
{$ENDC}
{$IFC UNDEFINED UsingDiskInit}
{$I DiskInit.p}
{$ENDC}
{$IFC UNDEFINED UsingDisks}
{$I Disks.p}
{$ENDC}
{$IFC UNDEFINED UsingEPPC}
{$I EPPC.p}
{$ENDC}
{$IFC UNDEFINED UsingErrors}
{$I Errors.p}
{$ENDC}
{$IFC UNDEFINED UsingEvents}
{$I Events.p}
{$ENDC}
{$IFC UNDEFINED UsingFiles}
{$I Files.p}
{$ENDC}
{$IFC UNDEFINED UsingFolders}
{$I Folders.p}
{$ENDC}
{$IFC UNDEFINED UsingFonts}
{$I Fonts.p}
{$ENDC}
{$IFC UNDEFINED UsingGestaltEqu}
{$I GestaltEqu.p}
{$ENDC}
{$IFC UNDEFINED UsingLists}
{$I Lists.p}
{$ENDC}
{$IFC UNDEFINED UsingMemory}
{$I Memory.p}
{$ENDC}
{$IFC UNDEFINED UsingMenus}
{$I Menus.p}
{$ENDC}
{$IFC UNDEFINED UsingOSUtils}
{$I OSUtils.p}
{$ENDC}
{$IFC UNDEFINED UsingPackages}
{$I Packages.p}
{$ENDC}
{$IFC UNDEFINED UsingPaletteMgr}
{$I PaletteMgr.p}
{$ENDC}
{$IFC UNDEFINED UsingPalettes}
{$I Palettes.p}
{$ENDC}
{$IFC UNDEFINED UsingPPCToolBox}
{$I PPCToolBox.p}
{$ENDC}
{$IFC UNDEFINED UsingProcesses}
{$I Processes.p}
{$ENDC}
{$IFC UNDEFINED UsingQuickdraw}
{$I Quickdraw.p}
{$ENDC}
{$IFC UNDEFINED UsingResources}
{$I Resources.p}
{$ENDC}
{$IFC UNDEFINED UsingROMDefs}
{$I ROMDefs.p}
{$ENDC}
{$IFC UNDEFINED UsingSANE}
{$I SANE.p}
{$ENDC}
{$IFC UNDEFINED UsingScrap}
{$I Scrap.p}
{$ENDC}
{$IFC UNDEFINED UsingScript}
{$I Script.p}
{$ENDC}
{$IFC UNDEFINED UsingSCSI}
{$I SCSI.p}
{$ENDC}
{$IFC UNDEFINED UsingSegLoad}
{$I SegLoad.p}
{$ENDC}
{$IFC UNDEFINED UsingSound}
{$I Sound.p}
{$ENDC}
{$IFC UNDEFINED UsingSysEqu}
{$I SysEqu.p}
{$ENDC}
{$IFC UNDEFINED UsingTextEdit}
{$I TextEdit.p}
{$ENDC}
{$IFC UNDEFINED UsingToolUtils}
{$I ToolUtils.p}
{$ENDC}
{$IFC UNDEFINED UsingTraps}
{$I Traps.p}
{$ENDC}
{$IFC UNDEFINED UsingTypes}
{$I Types.p}
{$ENDC}
{$IFC UNDEFINED UsingWindows}
{$I Windows.p}
{$ENDC}
{$SETC UsingIncludes := 0}

END. { StandardEqu }


