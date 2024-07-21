
{
Created: Tuesday, July 23, 1991 at 9:02 PM
 Packages.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: BigBang Sys606


	Change History (most recent first):

		<24>	  4/1/92	DCL		Un-Include StandardFile.
		<23>	 3/31/92	DCL		Re-Include StandardFile for now.
		<22>	 3/30/92	DCL		Moved IUGetItlTable to Script.[hap]  And ceased to include
									StandardFile.
		<21>	 3/26/92	DCL		For New IM: Moved many declarations and routines from
									Packages.[ph] to TextUtils.[ph]  And moved all of the Date &
									Time stuff to a new DateTime include file.  #1025005
		<20>	 3/20/92	DCL		#1025005,<KSM>:
									For New IM: Moved some declarations and routines from
									Packages.[ph] to Language.[ph]
		<19>	 3/19/92	DCL		For New IM: Moved declarations and routines to Script.[ph]
		<18>	 7/31/91	JL		Updated Copyright. Restored Comments.
		<17>	 1/27/91	LN		Checked in Database Generated file from DSG.
		<16>	  1/7/91	JDR		(dba) IUMagPString, IUMagIDPString, IUCompPString, and
									IUEqualPString use the parameter name itl2Handle. All other
									intlParams become intlHandle.
		<15>	  1/2/91	PKE		(bbm) Updated comments and rearranged a few constants to match
									latest Inside Mac summary.
		<14>	 11/4/90	dba		shorten the inline for IUDateString
		<13>	 8/29/90	PKE		Add iuWhiteSpaceList constant.
		<12>	 8/24/90	PKE		Add iuUnTokenTable constant.
		<11>	  7/2/90	PKE		Moved definition of LangCode into Types.p.
		<10>	 6/20/90	PKE		Added some verXxx synonyms that are less ambiguous than the old
									names.
		 <9>	 5/29/90	ngk		Move ScriptCode definition to Types.p
		 <8>	 5/11/90	PKE		Added verArabic as synonym for verArabia.
		 <7>	  3/2/90			Official MPW version.
		 <6>	  2/7/90	csd		Commented out the definition of colorPicker=12 because it was
									conflicting with UNIT ColorPicker. No one uses it anyway.
		 <5>	  2/7/90	ngk		Pull all StandardFile stuff out into a separate file -
									StandardFile.p
		 <4>	 1/23/90	PKE		Moved IULDateString and IULTimeString interfaces from Script.p
									to here, where they should have been all along. This requires
									auto-include of Script.p for definition of LongDateTime. Added
									INLINE implementation of several International Utilities
									routines (and removed them from Interfaces.o): IUGetIntl,
									IUSetIntl, IUDateString, IUDatePString, IUTimeString,
									IUTimePString, IUMetric, IUMagString, IUMagIdString. Moved glue
									for IUCompPString, IUEqualPString, and IUStringOrder into
									Interface.o and removed INLINE implementation here.
		 <3>	 1/17/90	PKE		Added several new verXxx codes.
		 <2>	  1/7/90	ngk		Changed auto-include from Alias.p to Aliases.p
		 <1>	12/17/89	CCH		Adding for the first time into BBS.
	(BBS versions above, EASE versions below)
	   <1.4>	10/14/89	ngk		Added new StandardFile calls.
	   <1.3>	 9/22/89	PKE		Defined more ScriptCode and LangCode values. Added interface and
									table selector constants for IUGetItlTable.
	   <1.2>	 9/18/89	PKE		Defined and used new ScriptCode and LangCode types for script
									and language sorting; rearranged parameters for IUStringOrder
									and IUTextOrder.
	   <1.1>	 9/15/89	PKE		Add interfaces and temporary glue for 7.0 procedure IUClearCache
									and functions IUMagPString, IUMagIDPString, IUCompPString,
									IUEqualPString, IUScriptOrder, IULangOrder, IUTextOrder,
									IUStringOrder. Also added bigBangEquates symbol to mark new
									stuff.
	   <1.0>	11/17/88	CCH		Adding to EASE.

}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Packages;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingPackages}
{$SETC UsingPackages := 1}

{$I+}
{$SETC PackagesIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := PackagesIncludes}

CONST
listMgr = 0;							{list manager}
dskInit = 2;							{Disk Initializaton}
stdFile = 3;							{Standard File}
flPoint = 4;							{Floating-Point Arithmetic}
trFunc = 5;								{Transcendental Functions}
intUtil = 6;							{International Utilities}
bdConv = 7;								{Binary/Decimal Conversion}
editionMgr = 11;						{Edition Manager}


PROCEDURE InitPack(packID: INTEGER);
 INLINE $A9E5;
PROCEDURE InitAllPacks;
 INLINE $A9E6;


{$ENDC} { UsingPackages }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

