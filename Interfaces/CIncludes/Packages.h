
/************************************************************

Created: Tuesday, July 23, 1991 at 6:40 PM
 Packages.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1992
  All rights reserved
    This file is used in these builds: BigBang Sys606



	Change History (most recent first):

		<26>	 8/28/92	DCL		Fixed enums with commas before the closing brace. MPW now
									complains.
		<25>	  4/1/92	DCL		Un-Include StandardFile.
		<24>	 3/31/92	DCL		Re-Include StandardFile for now.
		<23>	 3/30/92	DCL		Moved IUGetItlTable to Script.[hap]   And ceased to include
									StandardFile.h
		<22>	 3/26/92	DCL		For New IM: Moved many declarations and routines from
									Packages.[ph] to TextUtils.[ph]  And moved all of the Date &
									Time stuff to a new DateTime include file.  #1025005
		<21>	 3/20/92	DCL		#1025005,<KSM>:
									For New IM: Moved some declarations and routines from
									Packages.[ph] to Language.[ph] Radar #1025005
		<20>	 3/19/92	DCL		For New IM: Moved date & time formatting declarations to
									Script.[ph]
		<19>	 7/31/91	JL		Updated Copyright. Restored Comments.
		<18>	 1/27/91	LN		Checked in Database generate file from DSG. Temporarily losing
									comments. will be returned.
		<17>	  1/7/91	JDR		(dba) IUMagPString, IUMagIDPString, IUCompPString, and
									IUEqualPString use the parameter name itl2Handle. All other
									intlParams become intlHandle.
		<16>	  1/2/91	PKE		(bbm) Updated comments and rearranged a few constants to match
									latest Inside Mac summary.
		<15>	12/20/90	JL		changed constStr255Parameter to ConstStr255Param
		<14>	 11/7/90	JL		Changed all #defines to anonymous enums
		<13>	 11/4/90	dba		shorten the inline for IUDateString got rid of some extraneous
									parameter names; made some parameters void* instead of Ptr; used
									constStr255Parameter
		<12>	 10/9/90	JAL		changed SafeLink to CPlusPlus.
		<11>	 8/29/90	PKE		Add iuWhiteSpaceList constant.
		<10>	 8/24/90	PKE		Add iuUnTokenTable constant.
		 <9>	  7/2/90	PKE		Moved definition of LangCode into Types.h.
		 <8>	 6/20/90	PKE		Added C-string versions of new interfaces. Added some verXxx
									synonyms that are less ambiguous than the old names.
		 <7>	 5/29/90	ngk		Moved definition of ScriptCode into Types.h
		 <6>	 5/11/90	PKE		Added verArabic as synonym for verArabia.
		 <5>	  3/2/90			Official MPW version
		 <4>	  2/7/90	ngk		Move StandardFile stuff into StandardFile.h. Removed
									“bigBangEquates” flag, since MPW 3.1 is released
		 <3>	 1/23/90	PKE		Moved IULDateString and IULTimeString interfaces from Script.h
									to here, where they should have been all along. This requires
									auto-include of Script.h for definition of LongDateTime. Added
									INLINE implementation of several International Utilities
									routines (and removed them from Interfaces.o): IUGetIntl,
									IUSetIntl, IUDateString, IUDatePString, IUTimeString,
									IUTimePString, IUMetric, IUMagString, IUMagIdString. Moved glue
									for IUCompPString, IUEqualPString, and IUStringOrder into
									Interface.o and removed INLINE implementation here.
		 <2>	 1/17/90	PKE		Added several new verXxx codes. Updated header to BBS format.
		 <1>	12/17/89	CCH		Adding for the first time into BBS.

	   <1.6>	10/14/89	ngk		Added NewStandardFile stuff
	   <1.5>	 10/3/89	PAT		Fixed problem with the “bigBangEquates” flag - changed: #define
									bigbangEquates 1 -> #define bigBangEquates 1
	   <1.4>	 9/22/89	PKE		Defined more ScriptCode and LangCode values; parenthesized them
									to avoid problems. Added interface and table selector constants
									for IUGetItlTable.
	   <1.3>	 9/18/89	PKE		Defined and used new ScriptCode and LangCode types for script
									and language sorting; rearranged parameters for IUStringOrder
									and IUTextOrder.
	   <1.2>	 9/15/89	PKE		Add interfaces and temporary glue for 7.0 functions
									IUClearCache, IUMagPString, IUMagIDPString, IUCompPString,
									IUEqualPString, IUScriptOrder, IULangOrder, IUTextOrder,
									IUStringOrder. Also added bigBangEquates symbol to mark new
									stuff.
	   <1.1>	 11/9/88	CCH		Fixed headers and removed projector resource.
	   <1.0>	 11/9/88	CCH		Adding to EASE.

************************************************************/


#ifndef __PACKAGES__
#define __PACKAGES__

#ifndef __TYPES__
#include <Types.h>
#endif



enum {

 listMgr = 0,					/*list manager*/
 dskInit = 2,					/*Disk Initializaton*/
 stdFile = 3,					/*Standard File*/
 flPoint = 4,					/*Floating-Point Arithmetic*/
 trFunc = 5,					/*Transcendental Functions*/
 intUtil = 6,					/*International Utilities*/
 bdConv = 7,					/*Binary/Decimal Conversion*/
 editionMgr = 11				/*Edition Manager*/
};




#ifdef __cplusplus
extern "C" {
#endif
pascal void InitPack(short packID)
 = 0xA9E5; 
pascal void InitAllPacks(void)
 = 0xA9E6; 

#ifdef __cplusplus
}
#endif

#endif
