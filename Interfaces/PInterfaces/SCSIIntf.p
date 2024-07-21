{
	File: SCSIIntf.p

	As of MPW 3.0, interface files were reorganized to more closely
	match "Inside Macintosh" reference books and be more consistant
	from language to language.
	
	Interfaces for the SCSI Manager are now found in SCSI.p.
	This file, which includes SCSI.p, is provided for compatibility
	with old sources.

	Pascal Interface to the Macintosh Libraries
	Copyright Apple Computer, Inc. 1988
	All Rights Reserved
}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT SCSIIntf;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingSCSIIntf}
{$SETC UsingSCSIIntf := 1}

{$I+}
{$SETC SCSIIntfIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingSCSI}
{$I $$Shell(PInterfaces)SCSI.p}
{$ENDC}
{$SETC UsingIncludes := SCSIIntfIncludes}

{$ENDC}    { UsingSCSIIntf }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

