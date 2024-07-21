
/************************************************************

Created: Saturday, July 27, 1991 at 6:16 PM
 Script.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1986-1992
  All rights reserved


	Change History (most recent first):

		<74>	10/23/92	HA		For New Inside Mac we want to add langSaamisk=29 as the
									preferred synonym for langLappish, based on some naming info we
									have from the Norwegian consulate. (per PKE)
		<73>	 9/25/92	DCL		Changed Get(Set)SMVariable to Get(Set)ScriptManagerVariable.
									(for NIIM)
		<72>	 8/28/92	DCL		Fixed enums with commas before the closing brace. MPW now
									complains.
		<71>	  7/2/92	SMB		#1029263: Added new flag, smsfSynchUnstyledTE, to the 'itlb'
									flags field to handle font & keyboard synchronization for
									unstyled TE.
		<70>	 5/29/92	DCL		Moved Intl resource constants to IntlResources. Moved Findword
									stuff to TextUtils.  Tweaked some comments to reflect new names.
		<69>	  5/7/92	DCL		NIIM: Attempting to blow away DateTime.
		<68>	  5/5/92	DCL		Typos. Damn those little commas. Keep tripping over 'em.
		<67>	  5/5/92	DCL		For New Inside Mac: removing 'sc' prefixes from some calls,
									moving some calls from script to TextUtils, and moving some from
									TextUtils & QuickDraw to QuickdrawText. Weeeeeeee!
		<66>	 4/20/92	DCL		Added typedef thingy for RuleBasedTrslRecord whachamacallit.
		<65>	 4/20/92	DCL		More stuff from before.
		<64>	 4/20/92	DCL		 #1027048 Added smCharBopomofo, smTransRuleBaseFormat,
									smTransHangulFormat, smTransPreDoubleByting,
									smTransPreLowerCasing, Itl5, RuleBasedTrslRecord.
		<63>	 4/16/92	DCL		For New Inside Mac: Added Get&SetSysDirection as synonyms for
									Get&SetSysJust. Moved Read&WriteLocation from Script to OSUtils.
		<62>	 4/15/92	DCL		For New Inside Mac: Moved GetDefFontSize, GetSysFont, and
									GetAppFont from Script to Fonts.
		<61>	 4/15/92	DCL		For New Inside Mac: Moved many definitions from Script to
									TextUtils. And  added new synonyms. #1025005
		<61>	 4/15/92	DCL		For New Inside Mac: Moved many definitions to TextUtils. And
									added new synonyms. #1025005
		<60>	  4/8/92	PKE		#1026516,<cv>: Move SCxxx interfaces for some ScriptMgr routines
									from private interfaces (ScriptPriv.h) to public (here).
		<59>	  4/3/92	gbm		Change smKeyDisabState to a kinder, gentler spelling.
									(smKeyDisableState)
		<58>	  4/3/92	DCL		PKE #1026378: Add CharType constants smCharContextualLR and
									smCharNonContextualLR; already used for Thai and Cyrillic.
		<57>	  4/3/92	DCL		For New Inside Mac: Moved declarations from Script.[aph] to
									TextUtils.[aph].  Moved Language Codes back into Script.
									#1025005
		<56>	 3/30/92	DCL		Moved IUGetItlTable to Script.[hap]
		<55>	 3/30/92	DCL		PKE 1022875, Add smKeyRoman verb for KeyScript (for use in KSWP)
									that sets keyboard script to Roman if multiple scripts are
									installed (otherwise KSWP key combination is not stripped from
									event queue).
		<54>	 3/30/92	DCL		For New Inside Mac: Added New Improved Better Names for the same
									old calls. #1025005
		<53>	 3/26/92	DCL		For New Inside Mac:  Moved all of the Date & Time stuff to the
									New DateTime include file.  And Included the new DateTime
									include file.  #1025005
		<52>	 3/20/92	DCL		#1025005,<KSM>:
									Included Language.h because: For New IM: Moved some declarations
									and routines from Packages.[ph] to Script.[ph] #1025005
		<51>	 3/19/92	DCL		For New IM: Moved date & time declarations declarations to
									Script.[ph]
		<50>	 2/28/92	DCL		Moved GetMBarHeight from Script.h to Menus.h
		<49>	 2/17/92	MH		change refs to extended to extended80
		<48>	 2/10/92	YS		1014691, added a flag 'smfUseAssocFontInfo' in smGenFlags.
		<47>	 1/13/92	PKE		1019369, add smKeyDisabState verb for GetEnvirons to get the
									current keyboard disable state.
		<46>	12/11/91	PKE		Define new public interfaces SCGetScriptRoutineAddr,
									SCSetScriptRoutineAddr, SCGetQDPatchAddr, SCSetQDPatchAddr which
									are implemented by one-byte script extension.
		<45>	 12/6/91	JTK		Add script code for latest member of the Federation.
		<44>	 12/2/91	PKE		Fix ValidDate interface (MPW bug #1016029): selector was wrong
									and first param is not VAR (should be const).
		<43>	11/25/91	PKE		Define new smScriptFlags bit smsfUnivExt. Define new KeyScript
									verbs smKeySetDirLeftRight, smKeySetDirRightLeft.
		<42>	 11/6/91	MH		positions parameter for FormatStatus from TripleInt * to
									TripleInt. Since TripleInt is an array, it is incorrect to
									specify the reference parameter as a pointer to it. A parameter
									of type TripleInt is already a pointer. The call was difficult
									if not impossible to use in its previous form. see K&R pg 28.
		<41>	 9/27/91	SMB		For Cube-E (and Bruges) - define system direction bit,
									itlcSysDirection, for itlcSysFlags and added bit definitions,
									itlcShowIcon and itlcDualCaret, for the itlcFlags.
		<40>	 9/25/91	PKE		For Cube-E (and Bruges): Add itlcSysFlags field to ItlcRecord.
		<39>	 8/20/91	KSM		pke,#Bruges: Added a new script code smAllScripts to indicate
									meaning no preference for script code or any script code.
		<38>	 7/31/91	JL		Updated Copyright. Restored Comments.
		<37>	 6/14/91	JL		Checked in official MPW 3.2ƒ version. Removed the comma after
									the constant declaration of smMiddleStyleRun. Lost updated
									copyright date but this will be resolved later.
		<36>	 1/30/91	LN		Checked in Database Generated File from DSG. removed unnecessary
									"struct" from FindScriptRun
		<35>	 1/28/91	PKE		bbm: Add constants for use with CharType and Transliterate on
									Chinese and Korean systems.
		<34>	 1/10/91	PKE		(csd) Change names for “ring” and “breve” constants (too
									ambiguous) to “ringMark” and “breveMark”.
		<33>	  1/2/91	PKE		(bbm) Updated comments and rearranged a few constants to match
									latest Inside Mac summary. Added tokenCaret as correct spelling
									for tokenCarat.
		<32>	12/20/90	JL		changed constStr255Parameter to ConstStr255Param
		<31>	12/15/90	PKE		(KSM) Update some new constants used with 2-byte script systems.
		<30>	12/14/90	SMB		(csd) I forgot the approval signature for the previous change.
		<29>	12/14/90	SMB		Moving KeyScript verb, smKeyModalDialog, to ScriptPriv.h.
		<28>	 11/7/90	JL		Changed all #defines to anonymous enums
		<27>	 11/4/90	dba		use constStr255Parameter
		<26>	10/30/90	dba		make smaller version of low-memory access routines
		<25>	 9/16/90	PKE		In NItl4Rec, rename ‘resHeader1’ field to ‘format’, since that
									is how we now use it.
		<24>	 9/10/90	PKE		Add smCurrentScript constant. Add more FIS constants from Joel
									Cannon.
		<23>	 8/31/90	SMB		Added new KeyScript verb for ModalDialogs so that the About
									Keyboards menu item can be disabled. Added new KeyScript verb to
									disable the keyboard switching when a KCHR is being moved into
									or out of the System file.
		<22>	 8/24/90	PKE		(per JT) Restored smFISClassXXX constants to original values
									(backed out of part of change <6>).
		<21>	  8/2/90	PKE		Added smSystem constant (meta-script code, designates the system
									script). Moved obsolete script codes to end of their section.
									Added constants for values of scriptRedraw field. Cleaned up
									negative KeyScript verbs: deleted smKeyLastScript synonym, added
									smKeyDisableKybds and smKeyEnableKybds, renumbered
									smKeyNextInputMethod and smKeySwapInputMethod.
		<20>	 7/17/90	PKE		Changed reserved field in ItlbRecord to itlbEncoding (contains
									ID of itl5, optional char encoding resource), and changed name
									of corresponding GetScript verb. Fixed a few comments.
		<19>	 6/22/90	PKE		Moved language codes to a new file, Language.h, and rearranged
									the new ones. Added smExtArabic as synonym for smSindhi,
									smEastEurRoman as synonym for smSlavic.
		<18>	 6/20/90	PKE		Changed tentative value for smCharFISHangul to eliminate
									conflict with Arabic/Hebrew; added smCharExtAscii and
									smCharBidirect. Added smEthiopic (synonym for smGeez) plus about
									80 new language codes covering most languages we are likely to
									handle; also added some synonyms for existing language codes.
									Changed resLength6 field in NItl4Rec to whtSpListLength.
		<17>	 6/12/90	PKE		Added new calendar code calPersian, per Hani Abdelazim. Added
									smKeySwapScript as synonym for smKeyLastScript (using new
									terminology), and added several new KeyScript verbs that may be
									implemented by script systems.
		<16>	 5/31/90	PKE		Added new GetScript verbs: smScriptValidStyles,
									smScriptAliasStyle. Added new fields to ItlbExtRecord:
									itlbValidStyles, itlbAliasStyle.
		<15>	 5/24/90	PKE		Added numer/denom scaling parameters to NPortionText, NDrawJust,
	   								NMeasureJust, NChar2Pixel, and NPixel2Char.
		<14>	 5/21/90	PKE		Added new tokens tokenEllipsis and tokenCenterDot. Fixed
									spelling of tokenTilde. Changed truncMarkOffset to
									whtSpListOffset in NItl4Rec. Added smfNameTagEnab constant for
									flag bit, enables script tag in Finder names.
		<13>	 5/11/90	PKE		Added new constants smTradChinese, smSimpChinese,
									langTradChinese, langSimpChinese. Deleted smMaldivian!
		<12>	  5/1/90	PKE		Added constants for negative KeyScript verbs and for
									TruncText/TruncString results.
		<11>	 3/23/90	PKE		Added smScriptAppFondSize and smScriptHelpFondSize verbs for
									GetScript/SetScript. Defined smsfAutoInit bit for script flags.
									Deleted special roman font equates that were new for 7.0, since
									we now get this information from a resource. Added ItlbExtRecord
									structure for new-format 'itlb' resource.
		<10>	 3/21/90	PKE		Rearranged the length fields in NItl4Rec to be correct.
		 <9>	  3/7/90	JAL		Official MPW version
		 <8>	  3/5/90	PKE		For MPW release: Updated the TruncString and TruncText
									interfaces to look like their NTruncXxx forms, then deleted the
									NTruncXxx forms. This change should put this file into
									releasable shape.
		 <7>	  3/4/90	PKE		Change new implementation of UprText to be UpperText so we can
									remove last conditionals. Add LowerText as synonym for LwrText.
									Changed StripUprText to StripUpperText. Removed all conditionals
									and bigBangEquates symbol. Still need to fix up TruncX/NTruncX
									variants.
		 <6>	  3/2/90	PKE		Removed version number constants: smgrVers (Script Mgr),
									romanVers (Roman script system). Removed conditionalized
									definitions of private constants: smLastEVerb, smLastSVerb.
									Corrected smFISClassXXX constants. Removed 7.0
									conditionalization in itlcRecord, and renamed the now-shortened
									reserved area from itlcReserved2 to itlcReserved3. Gave new name
									‘NItl4Rec’ to the extended version of Itl4Rec, and
									unconditionalized the old versions so they don’t change. Added
									corresponding NItl4Ptr and NItl4Handle. Removed all conditionals
									on bigBangEquates except implementation change for UprText; need
									to fix this by renaming the new one (also change trap opword).
		 <5>	 1/23/90	PKE		Moved IULDateString and IULTimeString interfaces from here to
									Packages.h, where they should have been all along. Removed
									auto-include of Packages.h, since it isn't necessary and it
									causes problems since we now need to auto-include Script.h in
									Packages.h (i.e., the other way around). Instead, auto-include
									OSUtils.h (which was previously included via Packages.h) to get
									definition of DateTimeRec.
		 <4>	 1/17/90	PKE		Added itlcRegionCode field to itlcRecord.
		 <3>	 1/17/90	PKE		Added new constants: smCyrillic as synonym for smRussian, new
									smRegionCode verb for GetEnvirons (and older smKCHRCache verb
									that was never in here), and several new langXxx constants.
		 <2>	 1/11/90	PKE		Added new interfaces: NPortionText, NDrawJust, NMeasureJust,
									NChar2Pixel, and NPixel2Char. Added smXxxStyleRun constants and
									JustStyleCode typedef used in new interfaces. Updated header to
									be in BBS format.
		 <1>	12/17/89	CCH		Adding for the first time into BBS.
	(BBS versions above, EASE versions below)
	   <2.1>	 11/8/89	PKE		Add temporary interfaces NTruncString and NTruncText for the
									new-style Trunc routines that expect a truncWhere parameter.
									Eventually, the standard Trunc routine interfaces will be
									changed to use this parameter. Add TruncCode type and related
									constants for truncWhere parameter.
	   <2.0>	 10/3/89	PKE		Changed bigbangEquates to bigBangEquates for consistency with
									Packages.h.
	   <1.9>	 9/22/89	PKE		Define bigBangEquates if SysVers is not defined, as in non
									System file builds.
	   <1.8>	 9/19/89	PKE		Added StripText and StripUprText, modified UprText to use
									_UprText trap (instead of _UprString) for localizability. Made
									bigBangEquates symbol actually depend on SysVers. Changed
									Itl4Rec: defined truncMarkOffset field (was resOffset6), added 8
									shorts at end for table/code lengths. Defined NBreakTable and
									NBreakTablePtr, made NFindWord use NBreakTablePtr. NOTE: The
									NBreakTable definition here matches the itl2 break table headers
									in the current Reality sources, which have changed since the D13
									build. Since no one is presently using the NBreakTable
									structure, this shouldn't cause any problems.
	   <1.7>	 9/17/89	PKE		Added langKorean. Added new Get/SetEnvirons verb smDoubleByte.
									Deleted smLastEVerb, smLastSVerb. Updated romanVers for 7.0.
	   <1.6>	 9/15/89	PKE		Actually, the NFindWord interface is useful as a direct call,
									even if it is not a replacement for the old FindWord interface,
									so put it back in. Also add interfaces for TruncText,
									TruncString, and ReplaceText.
	   <1.5>	  9/5/89	PKE		Get rid of NFindWord interface; it was a bad idea. The 7.0 glue
									code now routes calls with the old FindWord selector to the new
									FindWord when possible. Leave conditionals for future use.
	   <1.4>	  9/4/89	PKE		Add NFindWord for 7.0 testing. Eventually, FindWord will be a
									synonym for NFindWord, but for now we will keep them separate so
									that we can do 6.0.4 and 6.0.5 builds.
	   <1.3>	 6/23/89	PKE		For 7.0: Make Script Manager version 7.xx for Big Bang, add new
									GetScript/SetScript verbs for font info, add new font constants
									for Roman.
	   <1.2>	  6/6/89	PKE		Update from MPW 3.0 level to MPW 3.1 level. Mostly this just
									adds new constants, but there are some changes to what was
									already in the file: (1) Changed the value of smgrVers, (2)
									Corrected the value of smTransCase, (3) Changed the
									ToggleResults type from unsigned char (with enumerated values)
									to short (with values specified by #defines), (4) Converted some
									of the reserved space in ItlcRecord to named fields.
	   <1.1>	 11/9/88	CCH		Fixed headers and removed projector resource.
	   <1.0>	 11/9/88	CCH		Adding to EASE.

	To Do:

************************************************************/


#ifndef __SCRIPT__
#define __SCRIPT__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif

#ifndef __INTLRESOURCES__
#include <IntlResources.h>
#endif


enum {


/* Script System constants */
 smSystemScript = -1,				/*designates system script.*/
 smCurrentScript = -2,				/*designates current font script.*/
 smAllScripts = -3,					/*designates any script	<39>*/

 smRoman = 0,						/*Roman*/
 smJapanese = 1,					/*Japanese*/
 smTradChinese = 2,					/*Traditional Chinese*/
 smKorean = 3,						/*Korean*/
 smArabic = 4,						/*Arabic*/
 smHebrew = 5,						/*Hebrew*/
 smGreek = 6,						/*Greek*/
 smCyrillic = 7,					/*Cyrillic*/
 smRSymbol = 8,						/*Right-left symbol*/
 smDevanagari = 9,					/*Devanagari*/
 smGurmukhi = 10,					/*Gurmukhi*/
 smGujarati = 11,					/*Gujarati*/
 smOriya = 12,						/*Oriya*/
 smBengali = 13,					/*Bengali*/
 smTamil = 14,						/*Tamil*/
 smTelugu = 15,						/*Telugu*/
 smKannada = 16,					/*Kannada/Kanarese*/
 smMalayalam = 17					/*Malayalam*/
};
enum {
 smSinhalese = 18,					/*Sinhalese*/
 smBurmese = 19,					/*Burmese*/
 smKhmer = 20,						/*Khmer/Cambodian*/
 smThai = 21,						/*Thai*/
 smLaotian = 22,					/*Laotian*/
 smGeorgian = 23,					/*Georgian*/
 smArmenian = 24,					/*Armenian*/
 smSimpChinese = 25,				/*Simplified Chinese*/
 smTibetan = 26,					/*Tibetan*/
 smMongolian = 27,					/*Mongolian*/
 smGeez = 28,						/*Geez/Ethiopic*/
 smEthiopic = 28,					/*Synonym for smGeez*/
 smEastEurRoman = 29,				/*Synonym for smSlavic*/
 smVietnamese = 30,					/*Vietnamese*/
 smExtArabic = 31,					/*extended Arabic*/
 smUninterp = 32,					/*uninterpreted symbols, e.g. palette symbols*/
 smKlingon = 32,					/*Klingon*/										/*<45>*/

/*Obsolete names for script systems (kept for backward compatibility)*/
 smChinese = 2,						/*(use smTradChinese or smSimpChinese)*/
 smRussian = 7,						/*(old name for smCyrillic)*/

/* smMaldivian = 25;         (no more smMaldivian!)*/
 smAmharic = 28,					/*(old name for smGeez)*/
 smSlavic = 29						/*(old name for smEastEurRoman)*/
};
enum {
 smSindhi = 31,						/*(old name for smExtArabic)*/


/* Language Codes */
 langEnglish = 0,			/* smRoman script */
 langFrench = 1,			/* smRoman script */
 langGerman = 2,			/* smRoman script */
 langItalian = 3,			/* smRoman script */
 langDutch = 4,				/* smRoman script */
 langSwedish = 5,			/* smRoman script */
 langSpanish = 6,			/* smRoman script */
 langDanish = 7,			/* smRoman script */
 langPortuguese = 8,		/* smRoman script */
 langNorwegian = 9,			/* smRoman script */
 langHebrew = 10,			/* smHebrew script */
 langJapanese = 11,			/* smJapanese script */
 langArabic = 12,			/* smArabic script */
 langFinnish = 13,			/* smRoman script */
 langGreek = 14,			/* smGreek script */
 langIcelandic = 15,		/* extended Roman script */
 langMaltese = 16,			/* extended Roman script */
 langTurkish = 17,			/* extended Roman script */
 langCroatian = 18,			/* Serbo-Croatian in extended Roman script */
 langTradChinese = 19		/* Chinese in traditional characters */
};
enum {
 langUrdu = 20,				/* smArabic script */
 langHindi = 21,			/* smDevanagari script */
 langThai = 22,				/* smThai script */
 langKorean = 23,			/* smKorean script */
 langLithuanian = 24,		/* smEastEurRoman script */
 langPolish = 25,			/* smEastEurRoman script */
 langHungarian = 26,		/* smEastEurRoman script */
 langEstonian = 27,			/* smEastEurRoman script */
 langLettish = 28,			/* smEastEurRoman script */
 langLatvian = 28,			/* Synonym for langLettish */
 langSaamisk = 29,			/* ext. Roman script, lang. of the Sami/Lapp people of Scand. */
 langLappish = 29,			/* Synonym for langSaamisk */
 langFaeroese = 30,			/* smRoman script */
 langFarsi = 31,			/* smArabic script */
 langPersian = 31,			/* Synonym for langFarsi */
 langRussian = 32,			/* smCyrillic script */
 langSimpChinese = 33,		/* Chinese in simplified characters */
 langFlemish = 34,			/* smRoman script */
 langIrish = 35,			/* smRoman script */
 langAlbanian = 36			/* smRoman script */
};
enum {
 langRomanian = 37,			/* smEastEurRoman script */
 langCzech = 38,			/* smEastEurRoman script */
 langSlovak = 39,			/* smEastEurRoman script */
 langSlovenian = 40,		/* smEastEurRoman script */
 langYiddish = 41,			/* smHebrew script */
 langSerbian = 42,			/* Serbo-Croatian in smCyrillic script */
 langMacedonian = 43,		/* smCyrillic script */
 langBulgarian = 44,		/* smCyrillic script */
 langUkrainian = 45,		/* smCyrillic script */
 langByelorussian = 46,		/* smCyrillic script */
 langUzbek = 47,			/* smCyrillic script */
 langKazakh = 48,			/* smCyrillic script */
 langAzerbaijani = 49,		/* Azerbaijani in smCyrillic script (USSR) */
 langAzerbaijanAr = 50,		/* Azerbaijani in smArabic script (Iran) */
 langArmenian = 51,			/* smArmenian script */
 langGeorgian = 52,			/* smGeorgian script */
 langMoldavian = 53,		/* smCyrillic script */
 langKirghiz = 54,			/* smCyrillic script */
 langTajiki = 55,			/* smCyrillic script */
 langTurkmen = 56			/* smCyrillic script */
};
enum {
 langMongolian = 57,		/* Mongolian in smMongolian script */
 langMongolianCyr = 58,		/* Mongolian in smCyrillic script */
 langPashto = 59,			/* smArabic script */
 langKurdish = 60,			/* smArabic script */
 langKashmiri = 61,			/* smArabic script */
 langSindhi = 62,			/* smExtArabic script */
 langTibetan = 63,			/* smTibetan script */
 langNepali = 64,			/* smDevanagari script */
 langSanskrit = 65,			/* smDevanagari script */
 langMarathi = 66,			/* smDevanagari script */
 langBengali = 67,			/* smBengali script */
 langAssamese = 68,			/* smBengali script */
 langGujarati = 69,			/* smGujarati script */
 langPunjabi = 70,			/* smGurmukhi script */
 langOriya = 71,			/* smOriya script */
 langMalayalam = 72,		/* smMalayalam script */
 langKannada = 73,			/* smKannada script */
 langTamil = 74,			/* smTamil script */
 langTelugu = 75,			/* smTelugu script */
 langSinhalese = 76			/* smSinhalese script */
};
enum {
 langBurmese = 77,			/* smBurmese script */
 langKhmer = 78,			/* smKhmer script */
 langLao = 79,				/* smLaotian script */
 langVietnamese = 80,		/* smVietnamese script */
 langIndonesian = 81,		/* smRoman script */
 langTagalog = 82,			/* smRoman script */
 langMalayRoman = 83,		/* Malay in smRoman script */
 langMalayArabic = 84,		/* Malay in smArabic script */
 langAmharic = 85,			/* smEthiopic script */
 langTigrinya = 86,			/* smEthiopic script */
 langGalla = 87,			/* smEthiopic script */
 langOromo = 87,			/* Synonym for langGalla */
 langSomali = 88,			/* smRoman script */
 langSwahili = 89,			/* smRoman script */
 langRuanda = 90,			/* smRoman script */
 langRundi = 91,			/* smRoman script */
 langChewa = 92,			/* smRoman script */
 langMalagasy = 93,			/* smRoman script */
 langEsperanto = 94,		/* extended Roman script */
 langWelsh = 128			/* smRoman script */
};
enum {
 langBasque = 129,			/* smRoman script */
 langCatalan = 130,			/* smRoman script */
 langLatin = 131,			/* smRoman script */
 langQuechua = 132,			/* smRoman script */
 langGuarani = 133,			/* smRoman script */
 langAymara = 134,			/* smRoman script */
 langTatar = 135,			/* smCyrillic script */
 langUighur = 136,			/* smArabic script */
 langDzongkha = 137,		/* (lang of Bhutan) smTibetan script */
 langJavaneseRom = 138,		/* Javanese in smRoman script */
 langSundaneseRom = 139,	/* Sundanese in smRoman script */

/* Obsolete names, kept for backward compatibility */
 langPortugese = 8,			/* old misspelled version, kept for compatibility */
 langMalta = 16,			/* old misspelled version, kept for compatibility */
 langYugoslavian = 18,		/* (use langCroatian, langSerbian, etc.) */
 langChinese = 19,			/* (use langTradChinese or langSimpChinese) */
 langLapponian = 29			/* Synonym for langSaamisk, not correct name */
};


enum {
/* Regional version codes */
 verUS = 0,
 verFrance = 1,
 verBritain = 2,
 verGermany = 3,
 verItaly = 4,
 verNetherlands = 5,
 verFrBelgiumLux = 6,			/* French for Belgium & Luxembourg */
 verSweden = 7,
 verSpain = 8,
 verDenmark = 9,
 verPortugal = 10,
 verFrCanada = 11,
 verNorway = 12
};
enum {
 verIsrael = 13,
 verJapan = 14,
 verAustralia = 15,
 verArabic = 16,				/* synonym for verArabia */
 verFinland = 17,
 verFrSwiss = 18,				/* French Swiss */
 verGrSwiss = 19,				/* German Swiss */
 verGreece = 20,
 verIceland = 21,
 verMalta = 22,
 verCyprus = 23,
 verTurkey = 24,
 verYugoCroatian = 25,			/* Croatian system for Yugoslavia */
 verIndiaHindi = 33,			/* Hindi system for India */
 verPakistan = 34,
 verLithuania = 41,
 verPoland = 42,
 verHungary = 43,
 verEstonia = 44,
 verLatvia = 45
};
enum {
 verLapland = 46,
 verFaeroeIsl = 47,
 verIran = 48,
 verRussia = 49,
 verIreland = 50,				/* English-language version for Ireland */
 verKorea = 51,
 verChina = 52,
 verTaiwan = 53,
 verThailand = 54
};

#define minCountry verUS
#define maxCountry verThailand

/*Obsolete region code names, kept for backward compatibility*/

enum {
 verBelgiumLux = 6,				/* (use verFrBelgiumLux instead, less ambiguous) */
 verArabia = 16,
 verYugoslavia = 25,			/* (use verYugoCroatian instead, less ambiguous) */
 verIndia = 33,					/* (use verIndiaHindi instead, less ambiguous) */



/* Calendar Codes */
 calGregorian = 0,
 calArabicCivil = 1,
 calArabicLunar = 2,
 calJapanese = 3,
 calJewish = 4,
 calCoptic = 5,
 calPersian = 6,

/* Integer Format Codes */
 intWestern = 0,
 intArabic = 1,
 intRoman = 2,
 intJapanese = 3,
 intEuropean = 4,
 intOutputMask = 0x8000,

/* CharByte byte types */
 smSingleByte = 0,
 smFirstByte = -1,
 smLastByte = 1,
 smMiddleByte = 2,

/* CharType field masks */
 smcTypeMask = 0x000F,
 smcReserved = 0x00F0
};
enum {
 smcClassMask = 0x0F00,
 smcOrientationMask = 0x1000,		/*two-byte script glyph orientation*/
 smcRightMask = 0x2000,
 smcUpperMask = 0x4000,
 smcDoubleMask = 0x8000,

/* Basic CharType character types */
 smCharPunct = 0x0000,
 smCharAscii = 0x0001,
 smCharEuro = 0x0007,
 smCharExtAscii = 0x0007,			/* More correct synonym for smCharEuro */

/* Additional CharType character types for script systems */
 smCharKatakana = 0x0002,			/*Japanese Katakana*/
 smCharHiragana = 0x0003,			/*Japanese Hiragana*/
 smCharIdeographic = 0x0004,		/*Hanzi, Kanji, Hanja*/
 smCharTwoByteGreek = 0x0005,		/*2-byte Greek in Far East systems*/
 smCharTwoByteRussian = 0x0006,		/*2-byte Cyrillic in Far East systems*/
 smCharBidirect = 0x0008,			/*Arabic/Hebrew*/
 smCharContextualLR = 0x0009,		/*Contextual left-right: Thai, Indic scripts*/		/*<58>*/
 smCharNonContextualLR = 0x000A,	/*Non-contextual left-right: Cyrillic, Greek*/		/*<58>*/
 smCharHangul = 0x000C,				/*Korean Hangul*/
 smCharJamo = 0x000D,				/*Korean Jamo*/
 smCharBopomofo = 0x000E,			/*Chinese Bopomofo*/	
    
/* old names for some of above, for backward compatibility */
 smCharFISKana = 0x0002,			/*Katakana*/
 smCharFISGana = 0x0003,			/*Hiragana*/
 smCharFISIdeo = 0x0004				/*Hanzi, Kanji, Hanja*/
};
enum {
 smCharFISGreek = 0x0005,			/*2-byte Greek in Far East systems*/
 smCharFISRussian = 0x0006,			/*2-byte Cyrillic in Far East systems*/

/* CharType classes for punctuation (smCharPunct) */
 smPunctNormal = 0x0000,
 smPunctNumber = 0x0100,
 smPunctSymbol = 0x0200,
 smPunctBlank = 0x0300,

/* Additional CharType classes for punctuation in two-byte systems */
 smPunctRepeat = 0x0400,			/* repeat marker */
 smPunctGraphic = 0x0500,			/* line graphics */

/* CharType Katakana and Hiragana classes for two-byte systems */
 smKanaSmall = 0x0100,				/*small kana character*/
 smKanaHardOK = 0x0200,				/*can have dakuten*/
 smKanaSoftOK = 0x0300,				/*can have dakuten or han-dakuten*/

/* CharType Ideographic classes for two-byte systems */
 smIdeographicLevel1 = 0x0000,		/*level 1 char*/
 smIdeographicLevel2 = 0x0100,		/*level 2 char*/
 smIdeographicUser = 0x0200,		/*user char*/

/* old names for above, for backward compatibility */
 smFISClassLvl1 = 0x0000,			/*level 1 char*/
 smFISClassLvl2 = 0x0100,			/*level 2 char*/
 smFISClassUser = 0x0200,			/*user char*/

/* CharType Jamo classes for Korean systems */
 smJamoJaeum = 0x0000,				/*simple consonant char*/
 smJamoBogJaeum = 0x0100,			/*complex consonant char*/
 smJamoMoeum = 0x0200				/*simple vowel char*/
};
enum {
 smJamoBogMoeum = 0x0300,			/*complex vowel char*/

/* CharType glyph orientation for two-byte systems */
 smCharHorizontal = 0x0000,			/* horizontal character form, or for both */
 smCharVertical = 0x1000,			/* vertical character form */

/* CharType directions */
 smCharLeft = 0x0000,
 smCharRight = 0x2000,

/* CharType case modifers */
 smCharLower = 0x0000,
 smCharUpper = 0x4000,

/* CharType character size modifiers (1 or multiple bytes). */
 smChar1byte = 0x0000,
 smChar2byte = 0x8000,

/* TransliterateText target types for Roman */
 smTransAscii = 0,					/*convert to ASCII*/
 smTransNative = 1,					/*convert to font script*/
 smTransCase = 0xFE,				/*convert case for all text*/
 smTransSystem = 0xFF,				/*convert to system script*/

/* TransliterateText target types for two-byte scripts */
 smTransAscii1 = 2,					/*1-byte Roman*/
 smTransAscii2 = 3,					/*2-byte Roman*/
 smTransKana1 = 4,					/*1-byte Japanese Katakana*/
 smTransKana2 = 5					/*2-byte Japanese Katakana*/
};
enum {
 smTransGana2 = 7,					/*2-byte Japanese Hiragana (no 1-byte Hiragana)*/
 smTransHangul2 = 8,				/*2-byte Korean Hangul*/
 smTransJamo2 = 9,					/*2-byte Korean Jamo*/
 smTransBopomofo2 = 10,				/*2-byte Chinese Bopomofo*/

/* TransliterateText target modifiers */
 smTransLower = 0x4000,				/*target becomes lowercase*/
 smTransUpper = 0x8000,				/*target becomes uppercase*/

/* TransliterateText resource format numbers */
 smTransRuleBaseFormat = 1,			/*Rule based trsl resource format */
 smTransHangulFormat = 2,			/*Table based Hangul trsl resource format*/

/* TransliterateText property flags */
 smTransPreDoubleByting = 1,		/*Convert all text to double byte before transliteration*/
 smTransPreLowerCasing = 2,			/*Convert all text to lower case before transliteration*/
  
/* TransliterateText source mask - general */
 smMaskAll = 0xFFFFFFFF,			/*Convert all text*/

/* TransliterateText source masks */
 smMaskAscii = 0x00000001,			/*2^smTransAscii*/
 smMaskNative = 0x00000002,			/*2^smTransNative*/

/* TransliterateText source masks for two-byte scripts */
 smMaskAscii1 = 0x00000004,			/*2^smTransAscii1*/
 smMaskAscii2 = 0x00000008,			/*2^smTransAscii2*/
 smMaskKana1 = 0x00000010,			/*2^smTransKana1*/
 smMaskKana2 = 0x00000020,			/*2^smTransKana2*/
 smMaskGana2 = 0x00000080,			/*2^smTransGana2*/
 smMaskHangul2 = 0x00000100,		/*2^smTransHangul2*/
 smMaskJamo2 = 0x00000200,			/*2^smTransJamo2*/
 smMaskBopomofo2 = 0x00000400,		/*2^smTransBopomofo2*/

/* Result values from GetScriptManagerVariable and SetScriptManagerVariable calls. */
 smNotInstalled = 0,				/*routine not available in script*/
 smBadVerb = -1,					/*Bad verb passed to a routine*/
 smBadScript = -2					/*Bad script code passed to a routine*/
};
enum {

/* Values for script redraw flag. */
 smRedrawChar = 0,					/*Redraw character only*/
 smRedrawWord = 1,					/*Redraw entire word (2-byte systems)*/
 smRedrawLine = -1,					/*Redraw entire line (bidirectional systems)*/

/* GetScriptManagerVariable and SetScriptManagerVariable verbs */
 smVersion = 0,						/*Script Manager version number*/
 smMunged = 2,						/*Globals change count*/
 smEnabled = 4,						/*Count of enabled scripts, incl Roman*/
 smBidirect = 6,					/*At least one bidirectional script*/
 smFontForce = 8,					/*Force font flag*/
 smIntlForce = 10,					/*Force intl flag*/
 smForced = 12,						/*Script was forced to system script*/
 smDefault = 14,					/*Script was defaulted to Roman script*/
 smPrint = 16,						/*Printer action routine*/
 smSysScript = 18,					/*System script*/
 smLastScript = 20,					/*Last keyboard script*/
 smKeyScript = 22,					/*Keyboard script*/
 smSysRef = 24,						/*System folder refNum*/
 smKeyCache = 26,					/*obsolete*/
 smKeySwap = 28,					/*Swapping table handle*/
 smGenFlags = 30,					/*General flags long*/
 smOverride = 32					/*Script override flags*/
};
enum {
 smCharPortion = 34,				/*Ch vs SpExtra proportion*/

/* New for System 7.0: */
 smDoubleByte = 36,					/*Flag for double-byte script installed*/
 smKCHRCache = 38,					/*Returns pointer to KCHR cache*/
 smRegionCode = 40,					/*Returns current region code (verXxx)*/
 smKeyDisableState = 42,			/*Returns current keyboard disable state*/			/*<47>*/

/* GetScriptVariable and SetScriptVariable verbs.
Note: Verbs private to script systems are negative, while
those general across script systems are non-negative. */
 smScriptVersion = 0,				/*Script software version*/
 smScriptMunged = 2,				/*Script entry changed count*/
 smScriptEnabled = 4,				/*Script enabled flag*/
 smScriptRight = 6,					/*Right to left flag*/
 smScriptJust = 8,					/*Justification flag*/
 smScriptRedraw = 10,				/*Word redraw flag*/
 smScriptSysFond = 12,				/*Preferred system font*/
 smScriptAppFond = 14,				/*Preferred Application font*/
 smScriptBundle = 16,				/*Beginning of itlb verbs*/
 smScriptNumber = 16,				/*Script itl0 id*/
 smScriptDate = 18,					/*Script itl1 id*/
 smScriptSort = 20,					/*Script itl2 id*/
 smScriptFlags = 22,				/*flags word*/
 smScriptToken = 24,				/*Script itl4 id*/
 smScriptEncoding = 26,				/*id of optional itl5, if present*/
 smScriptLang = 28					/*Current language for script*/
};
enum {
 smScriptNumDate = 30,				/*Script Number/Date formats.*/
 smScriptKeys = 32,					/*Script KCHR id*/
 smScriptIcon = 34,					/*ID # of SICN or kcs#/kcs4/kcs8 suite*/
 smScriptPrint = 36,				/*Script printer action routine*/
 smScriptTrap = 38,					/*Trap entry pointer*/
 smScriptCreator = 40,				/*Script file creator*/
 smScriptFile = 42,					/*Script file name*/
 smScriptName = 44,					/*Script name*/

/* There is a hole here for old Kanji private verbs 46-76 

 New for System 7.0: */
 smScriptMonoFondSize = 78,			/*default monospace FOND (hi) & size (lo)*/
 smScriptPrefFondSize = 80,			/*preferred FOND (hi) & size (lo)*/
 smScriptSmallFondSize = 82,		/*default small FOND (hi) & size (lo)*/
 smScriptSysFondSize = 84,			/*default system FOND (hi) & size (lo)*/
 smScriptAppFondSize = 86,			/*default app FOND (hi) & size (lo)*/
 smScriptHelpFondSize = 88,			/*default Help Mgr FOND (hi) & size (lo)*/
 smScriptValidStyles = 90,			/*mask of valid styles for script*/
 smScriptAliasStyle = 92,			/*style (set) to use for aliases*/

/* Special script code values for International Utilities */
 iuSystemScript = -1,				/* <obsolete>  system script */
 iuCurrentScript = -2,				/* <obsolete>  current script (for font of grafPort) */

/* Negative verbs for KeyScript */
 smKeyNextScript = -1,				/* Switch to next available script */
 smKeySysScript = -2,				/* Switch to the system script */
 smKeySwapScript = -3,				/* Switch to previously-used script */

/* New for System 7.0: */
 smKeyNextKybd = -4					/* Switch to next keyboard in current keyscript */
};
enum {
 smKeySwapKybd = -5,				/* Switch to previously-used keyboard in current keyscript */

 smKeyDisableKybds = -6,			/* Disable keyboards not in system or Roman script */
 smKeyEnableKybds = -7,				/* Re-enable keyboards for all enabled scripts */
 smKeyToggleInline = -8,			/* Toggle inline input for current keyscript */
 smKeyToggleDirection = -9,			/* Toggle default line direction (TESysJust) */
 smKeyNextInputMethod = -10,		/* Switch to next input method in current keyscript */
 smKeySwapInputMethod = -11,		/* Switch to last-used input method in current keyscript */

 smKeyDisableKybdSwitch = -12,		/* Disable switching from the current keyboard */

smKeySetDirLeftRight = -15,			/* Set default line dir to left-right, align left */	/*<43>*/
smKeySetDirRightLeft = -16,			/* Set default line dir to right-left, align right */	/*<43>*/
smKeyRoman = -17,					/* Set keyscript to Roman. Does nothing if Roman-only
										system, unlike KeyScript(smRoman) which forces
										an update to current default Roman keyboard */		/*<55>*/


/* Bits in the smScriptFlags word
(bits above 8 are non-static) */
 smsfIntellCP = 0,					/*Script has intelligent cut & paste*/
 smsfSingByte = 1,					/*Script has only single bytes*/
 smsfNatCase = 2,					/*Native chars have upper & lower case*/
 smsfContext = 3,					/*Script is contextual*/
 smsfNoForceFont = 4,				/*Script will not force characters*/
 smsfB0Digits = 5,					/*Script has alternate digits at B0-B9*/
 smsfAutoInit = 6,					/*Auto initialize the script*/
 smsfUnivExt = 7,					/*Script is handled by universal extension*/			/*<43>*/
 smsfSynchUnstyledTE = 8,			/*Script synchronizes for unstyled TE*/
 smsfForms = 13,					/*Uses contextual forms for letters*/
 smsfLigatures = 14,				/*Uses contextual ligatures*/
 smsfReverse = 15,					/*Reverses native text, right-left*/

/* Bits in the smGenFlags long.
First (high-order) byte is set from itlc flags byte. */
 smfShowIcon = 31,					/*Show icon even if only one script*/
 smfDualCaret = 30,					/*Use dual caret for mixed direction text*/
 smfNameTagEnab = 29,				/*Reserved for internal use*/
 smfUseAssocFontInfo = 28			/*Use the associated font info for FontMetrics calls */	/*<48>*/

};
enum {

/* Roman script constants 

 The following are here for backward compatibility, but should not be used. 
 This information should be obtained using GetScript. */
 romanSysFond = 0x3FFF,				/*system font id number*/
 romanAppFond = 3,					/*application font id number*/
 romanFlags = 0x0007,				/*roman settings*/

/* Script Manager font equates. */
 smFondStart = 0x4000,				/*start from 16K*/
 smFondEnd = 0xC000,				/*past end of range at 48K*/

/* Miscellaneous font equates. */
 smUprHalfCharSet = 0x80,			/*first char code in top half of std char set*/

/* Character Set Extensions */
 diaeresisUprY = 0xD9,
 fraction = 0xDA,
 intlCurrency = 0xDB,
 leftSingGuillemet = 0xDC,
 rightSingGuillemet = 0xDD,
 fiLigature = 0xDE,
 flLigature = 0xDF,
 dblDagger = 0xE0,
 centeredDot = 0xE1,
 baseSingQuote = 0xE2,
 baseDblQuote = 0xE3,
 perThousand = 0xE4,
 circumflexUprA = 0xE5
};
enum {
 circumflexUprE = 0xE6,
 acuteUprA = 0xE7,
 diaeresisUprE = 0xE8,
 graveUprE = 0xE9,
 acuteUprI = 0xEA,
 circumflexUprI = 0xEB,
 diaeresisUprI = 0xEC,
 graveUprI = 0xED,
 acuteUprO = 0xEE,
 circumflexUprO = 0xEF,
 appleLogo = 0xF0,
 graveUprO = 0xF1,
 acuteUprU = 0xF2,
 circumflexUprU = 0xF3,
 graveUprU = 0xF4,
 dotlessLwrI = 0xF5,
 circumflex = 0xF6,
 tilde = 0xF7,
 macron = 0xF8,
 breveMark = 0xF9
};
enum {
 overDot = 0xFA,
 ringMark = 0xFB,
 cedilla = 0xFC,
 doubleAcute = 0xFD,
 ogonek = 0xFE,
 hachek = 0xFF,


/* TokenType values */
 tokenIntl = 4,						/*the itl resource number of the tokenizer*/
 tokenEmpty = -1					/*used internally as an empty flag*/
};
enum {
 tokenUnknown = 0,					/*chars that do not match a defined token type*/
 tokenWhite = 1,					/*white space*/
 tokenLeftLit = 2,					/*literal begin*/
 tokenRightLit = 3,					/*literal end*/
 tokenAlpha = 4,					/*alphabetic*/
 tokenNumeric = 5,					/*numeric*/
 tokenNewLine = 6,					/*new line*/
 tokenLeftComment = 7,				/*open comment*/
 tokenRightComment = 8,				/*close comment*/
 tokenLiteral = 9,					/*literal*/
 tokenEscape = 10,					/*character escape (e.g. '\' in "\n", "\t")*/
 tokenAltNum = 11,					/*alternate number (e.g. $B0-B9 in Arabic,Hebrew)*/
 tokenRealNum = 12,					/*real number*/
 tokenAltReal = 13,					/*alternate real number*/
 tokenReserve1 = 14,				/*reserved*/
 tokenReserve2 = 15,				/*reserved*/
 tokenLeftParen = 16,				/*open parenthesis*/
 tokenRightParen = 17,				/*close parenthesis*/
 tokenLeftBracket = 18,				/*open square bracket*/
 tokenRightBracket = 19				/*close square bracket*/
};
enum {
 tokenLeftCurly = 20,				/*open curly bracket*/
 tokenRightCurly = 21,				/*close curly bracket*/
 tokenLeftEnclose = 22,				/*open guillemet*/
 tokenRightEnclose = 23,			/*close guillemet*/
 tokenPlus = 24,
 tokenMinus = 25,
 tokenAsterisk = 26,				/*times/multiply*/
 tokenDivide = 27,
 tokenPlusMinus = 28,				/*plus or minus symbol*/
 tokenSlash = 29,
 tokenBackSlash = 30,
 tokenLess = 31,					/*less than symbol*/
 tokenGreat = 32,					/*greater than symbol*/
 tokenEqual = 33,
 tokenLessEqual2 = 34,				/*less than or equal, 2 characters (e.g. <=)*/
 tokenLessEqual1 = 35,				/*less than or equal, 1 character*/
 tokenGreatEqual2 = 36,				/*greater than or equal, 2 characters (e.g. >=)*/
 tokenGreatEqual1 = 37,				/*greater than or equal, 1 character*/
 token2Equal = 38,					/*double equal (e.g. ==)*/
 tokenColonEqual = 39				/*colon equal*/
};
enum {
 tokenNotEqual = 40,				/*not equal, 1 character*/
 tokenLessGreat = 41,				/*less/greater, Pascal not equal (e.g. <>)*/
 tokenExclamEqual = 42,				/*exclamation equal, C not equal (e.g. !=)*/
 tokenExclam = 43,					/*exclamation point*/
 tokenTilde = 44,					/*centered tilde*/
 tokenComma = 45,
 tokenPeriod = 46,
 tokenLeft2Quote = 47,				/*open double quote*/
 tokenRight2Quote = 48,				/*close double quote*/
 tokenLeft1Quote = 49,				/*open single quote*/
 tokenRight1Quote = 50,				/*close single quote*/
 token2Quote = 51,					/*double quote*/
 token1Quote = 52,					/*single quote*/
 tokenSemicolon = 53,
 tokenPercent = 54,
 tokenCaret = 55,
 tokenUnderline = 56,
 tokenAmpersand = 57,
 tokenAtSign = 58,
 tokenBar = 59						/*vertical bar*/
};
enum {
 tokenQuestion = 60,
 tokenPi = 61,						/*lower-case pi*/
 tokenRoot = 62,					/*square root symbol*/
 tokenSigma = 63,					/*capital sigma*/
 tokenIntegral = 64,				/*integral sign*/
 tokenMicro = 65,
 tokenCapPi = 66,					/*capital pi*/
 tokenInfinity = 67,
 tokenColon = 68,
 tokenHash = 69,					/*e.g. #*/
 tokenDollar = 70,
 tokenNoBreakSpace = 71,			/*non-breaking space*/
 tokenFraction = 72,
 tokenIntlCurrency = 73,
 tokenLeftSingGuillemet = 74,
 tokenRightSingGuillemet = 75,
 tokenPerThousand = 76,
 tokenEllipsis = 77,
 tokenCenterDot = 78,
 tokenNil = 127
};
enum {
 delimPad = -2,

/* obsolete, misspelled token names kept for backward compatibility */
 tokenTilda = 44,
 tokenCarat = 55

};

enum {
/* Table selectors for GetItlTable */
 smWordSelectTable = 0,			/* get word select break table from 'itl2' */
 smWordWrapTable = 1,			/* get word wrap break table from 'itl2' */
 smNumberPartsTable = 2,		/* get default number parts table from 'itl4' */
 smUnTokenTable = 3,			/* get unToken table from 'itl4' */
 smWhiteSpaceList = 4,			/* get white space list from 'itl4' */

 iuWordSelectTable = 0,			/* <obsolete>  get word select break table from 'itl2' */
 iuWordWrapTable = 1,			/* <obsolete>  get word wrap break table from 'itl2' */
 iuNumberPartsTable = 2,		/* <obsolete>  get default number parts table from 'itl4' */
 iuUnTokenTable = 3,			/* <obsolete>  get unToken table from 'itl4' */
 iuWhiteSpaceList = 4			/* <obsolete>  get white space list from 'itl4' */
};

/* end of stuff moved from Packages.h */

enum {tokenOK,tokenOverflow,stringOverflow,badDelim,badEnding,crash};
typedef unsigned char TokenResults;


typedef char CharByteTable[256];


typedef short TokenType;
typedef TokenType DelimType[2];
typedef TokenType CommentType[4];

struct TokenRec {
 TokenType theToken;
 Ptr position;						/*pointer into original source*/
 long length;						/*length of text in original source*/
 StringPtr stringPosition;			/*Pascal/C string copy of identifier*/
};

typedef struct TokenRec TokenRec;
typedef TokenRec *TokenRecPtr;

struct TokenBlock {
 Ptr source;						/*pointer to stream of characters*/
 long sourceLength;					/*length of source stream*/
 Ptr tokenList;						/*pointer to array of tokens*/
 long tokenLength;					/*maximum length of TokenList*/
 long tokenCount;					/*number tokens generated by tokenizer*/
 Ptr stringList;					/*pointer to stream of identifiers*/
 long stringLength;					/*length of string list*/
 long stringCount;					/*number of bytes currently used*/
 Boolean doString;					/*make strings & put into StringList*/
 Boolean doAppend;					/*append to TokenList rather than replace*/
 Boolean doAlphanumeric;			/*identifiers may include numeric*/
 Boolean doNest;					/*do comments nest?*/
 TokenType leftDelims[2];
 TokenType rightDelims[2];
 TokenType leftComment[4];
 TokenType rightComment[4];
 TokenType escapeCode;				/*escape symbol code*/
 TokenType decimalCode;
 Handle itlResource;				/*handle to itl4 resource of current script*/
 long reserved[8];					/*must be zero!*/
};

typedef struct TokenBlock TokenBlock;
typedef TokenBlock *TokenBlockPtr;

#ifdef __cplusplus
extern "C" {
#endif
pascal short FontScript(void)
 = {0x2F3C,0x8200,0x0000,0xA8B5}; 
pascal short IntlScript(void)
 = {0x2F3C,0x8200,0x0002,0xA8B5}; 
pascal void KeyScript(short code)
 = {0x2F3C,0x8002,0x0004,0xA8B5}; 
pascal short CharByte(Ptr textBuf,short textOffset)
 = {0x2F3C,0x8206,0x0010,0xA8B5}; 
pascal short CharType(Ptr textBuf,short textOffset)
 = {0x2F3C,0x8206,0x0012,0xA8B5}; 
pascal OSErr Transliterate(Handle srcHandle,Handle dstHandle,short target,
 long srcMask)
 = {0x2F3C,0x820E,0x0018,0xA8B5}; 
pascal Boolean ParseTable(CharByteTable table)
 = {0x2F3C,0x8204,0x0022,0xA8B5}; 
#define GetSysDirection() (* (short*) 0x0BAC)
#define GetSysJust() (* (short*) 0x0BAC)
pascal void SetSysDirection(short newDirection)
 = {0x31DF,0x0BAC}; 
pascal void SetSysJust(short newJust)
 = {0x31DF,0x0BAC}; 

pascal TokenResults IntlTokenize(TokenBlockPtr tokenParam)
 = {0x2F3C,0x8204,0xFFFA,0xA8B5}; 


pascal short FontToScript(short fontNumber)
 = {0x2F3C,0x8202,0x0006,0xA8B5}; 
pascal short Font2Script(short fontNumber)
 = {0x2F3C,0x8202,0x0006,0xA8B5}; 
pascal long GetScriptManagerVariable(short selector)
 = {0x2F3C,0x8402,0x0008,0xA8B5}; 
pascal long GetEnvirons(short verb)
 = {0x2F3C,0x8402,0x0008,0xA8B5}; 
pascal OSErr SetScriptManagerVariable(short selector,long param)
 = {0x2F3C,0x8206,0x000A,0xA8B5}; 
pascal OSErr SetEnvirons(short verb,long param)
 = {0x2F3C,0x8206,0x000A,0xA8B5}; 
pascal long GetScriptVariable(short script,short selector)
 = {0x2F3C,0x8404,0x000C,0xA8B5}; 
pascal long GetScript(short script,short verb)
 = {0x2F3C,0x8404,0x000C,0xA8B5}; 
pascal OSErr SetScriptVariable(short script,short selector,long param)
 = {0x2F3C,0x8208,0x000E,0xA8B5}; 
pascal OSErr SetScript(short script,short verb,long param)
 = {0x2F3C,0x8208,0x000E,0xA8B5}; 



/*  New for 7.1  */																	/*<46>*/

pascal Ptr GetScriptUtilityAddress(short selector,Boolean Before,ScriptCode script)
    = {0x2F3C,0xC404,0x0038,0xA8B5}; 

pascal void SetScriptUtilityAddress(short selector,Boolean Before,Ptr routineAddr,ScriptCode script)
    = {0x2F3C,0xC008,0x003A,0xA8B5}; 

pascal Ptr GetScriptQDPatchAddress(short trapNum,Boolean Before,Boolean forPrinting,ScriptCode script)
    = {0x2F3C,0xC406,0x003C,0xA8B5}; 

pascal void SetScriptQDPatchAddress(short trapNum,Boolean Before,Boolean forPrinting,Ptr routineAddr,ScriptCode script)
    = {0x2F3C,0xC00A,0x003E,0xA8B5}; 



pascal short CharacterByteType(Ptr textBuf,short textOffset,ScriptCode script)				/*<60>*/
 = {0x2F3C,0xC206,0x0010,0xA8B5}; 

pascal short CharacterType(Ptr textBuf,short textOffset,ScriptCode script)				/*<60>*/
 = {0x2F3C,0xC206,0x0012,0xA8B5}; 

pascal OSErr TransliterateText(Handle srcHandle,Handle dstHandle,short target,
 long srcMask,ScriptCode script)													/*<60>*/
 = {0x2F3C,0xC20E,0x0018,0xA8B5}; 

pascal Boolean FillParseTable(CharByteTable table,ScriptCode script)					/*<60>*/
 = {0x2F3C,0xC204,0x0022,0xA8B5}; 

/* moved from Packages.h */

pascal Handle GetIntlResource(short theID)
 = {0x3F3C,0x0006,0xA9ED}; 
pascal Handle IUGetIntl(short theID)		/* obsolete name */
 = {0x3F3C,0x0006,0xA9ED}; 
pascal void IUSetIntl(short refNum,short theID,Handle intlHandle)		/* obsolete name */
 = {0x3F3C,0x0008,0xA9ED}; 
pascal void ClearIntlResourceCache(void)
 = {0x3F3C,0x0018,0xA9ED}; 
pascal void IUClearCache(void)		/* obsolete name */
 = {0x3F3C,0x0018,0xA9ED}; 

pascal void GetIntlResourceTable(ScriptCode script,short tableCode,Handle *itlHandle,
 long *offset,long *length)
 = {0x3F3C,0x0024,0xA9ED}; 
pascal void IUGetItlTable(ScriptCode script,short tableCode,Handle *itlHandle,		/* obsolete name */
 long *offset,long *length)
 = {0x3F3C,0x0024,0xA9ED}; 



#ifdef __cplusplus
}
#endif

#endif
