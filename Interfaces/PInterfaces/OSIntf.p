{
	File: OSIntf.p

	As of MPW 3.0, interface files were reorganized to more closely
	match "Inside Macintosh" reference books and be more consistant
	from language to language.
	
	Interfaces for the Operating System calls are now found in the
	files included below. This file is provided for compatibility
	with old sources.

	Pascal Interface to the Macintosh Libraries
	Copyright Apple Computer, Inc. 1988
	All Rights Reserved
}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT OSIntf;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingOSIntf}
{$SETC UsingOSIntf := 1}

{$I+}
{$SETC OSIntfIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingEvents}
{$I $$Shell(PInterfaces)Events.p}
{$ENDC}
{$IFC UNDEFINED UsingOSUtils}
{$I $$Shell(PInterfaces)OSUtils.p}
{$ENDC}
{$IFC UNDEFINED UsingFiles}
{$I $$Shell(PInterfaces)Files.p}
{$ENDC}
{$IFC UNDEFINED UsingDevices}
{$I $$Shell(PInterfaces)Devices.p}
{$ENDC}
{$IFC UNDEFINED UsingDeskBus}
{$I $$Shell(PInterfaces)DeskBus.p}
{$ENDC}
{$IFC UNDEFINED UsingDiskInit}
{$I $$Shell(PInterfaces)DiskInit.p}
{$ENDC}
{$IFC UNDEFINED UsingDisks}
{$I $$Shell(PInterfaces)Disks.p}
{$ENDC}
{$IFC UNDEFINED UsingErrors}
{$I $$Shell(PInterfaces)Errors.p}
{$ENDC}
{$IFC UNDEFINED UsingMemory}
{$I $$Shell(PInterfaces)Memory.p}
{$ENDC}
{$IFC UNDEFINED UsingRetrace}
{$I $$Shell(PInterfaces)Retrace.p}
{$ENDC}
{$IFC UNDEFINED UsingSegLoad}
{$I $$Shell(PInterfaces)SegLoad.p}
{$ENDC}
{$IFC UNDEFINED UsingSerial}
{$I $$Shell(PInterfaces)Serial.p}
{$ENDC}
{$IFC UNDEFINED UsingShutDown}
{$I $$Shell(PInterfaces)ShutDown.p}
{$ENDC}
{$IFC UNDEFINED UsingSlots}
{$I $$Shell(PInterfaces)Slots.p}
{$ENDC}
{$IFC UNDEFINED UsingSound}
{$I $$Shell(PInterfaces)Sound.p}
{$ENDC}
{$IFC UNDEFINED UsingStart}
{$I $$Shell(PInterfaces)Start.p}
{$ENDC}
{$IFC UNDEFINED UsingTimer}
{$I $$Shell(PInterfaces)Timer.p}
{$ENDC}
{$SETC UsingIncludes := OSIntfIncludes}

{$ENDC}    { UsingOSIntf }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

