{
	File: PickerIntf.p

	As of MPW 3.0, interface files were reorganized to more closely
	match "Inside Macintosh" reference books and be more consistant
	from language to language.
	
	Interfaces for the Color Picker are now found in Picker.p.
	This file, which includes Picker.p, is provided for compatibility
	with old sources.

	Pascal Interface to the Macintosh Libraries
	Copyright Apple Computer, Inc. 1988
	All Rights Reserved
}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT PickerIntf;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingPickerIntf}
{$SETC UsingPickerIntf := 1}

{$I+}
{$SETC PickerIntfIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingPicker}
{$I $$Shell(PInterfaces)Picker.p}
{$ENDC}
{$SETC UsingIncludes := PickerIntfIncludes}

{$ENDC}    { UsingPickerIntf }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

