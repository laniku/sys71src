
{
Created: Saturday, July 27, 1991 at 10:14 PM
 OSEvents.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1992
  All rights reserved

	Change History (most recent first):

		 <7>	 3/26/92	JSM		Rolled this file into SuperMario project.
		 <6>	 2/27/92	DCL		Moving OSEvents into Events.p for NIIM (New Improved Inside
									Mac).
		 <5>	 7/30/91	JL		Updated Copyright.
		 <4>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <3>	10/10/90	JL		Fixing Inline for GetEvQHdr
		 <2>	 10/3/90	JAL		Added Inline for GetEvQHdr.
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT OSEvents;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingOSEvents}
{$SETC UsingOSEvents := 1}

{$I+}
{$SETC OSEventsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingEvents}
{$I $$Shell(PInterfaces)Events.p}
{$ENDC}
{$SETC UsingIncludes := OSEventsIncludes}


{$ENDC} { UsingOSEvents }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

