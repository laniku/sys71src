{
	File: VideoIntf.p

	As of MPW 3.0, interface files were reorganized to more closely
	match "Inside Macintosh" reference books and be more consistant
	from language to language.
	
	Interfaces for the VideoIntf are now found in Video.p.
	This file, which includes Video.p, is provided for compatibility
	with old sources.

	Pascal Interface to the Macintosh Libraries
	Copyright Apple Computer, Inc. 1988
	All Rights Reserved
}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT VideoIntf;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingVideoIntf}
{$SETC UsingVideoIntf := 1}

{$I+}
{$SETC VideoIntfIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingVideo}
{$I $$Shell(PInterfaces)Video.p}
{$ENDC}
{$SETC UsingIncludes := VideoIntfIncludes}

{$ENDC}    { UsingVideoIntf }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

