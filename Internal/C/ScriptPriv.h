/*
	File:		ScriptPriv.h

	Contains:	Private C definitions for Script Mgr (these assume System 7.0).

	Written by:	PKE	Peter Edberg
				SMB	Sue Bartalo
				YS	Yishai Steinhart

	Copyright:	© 1988-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<27>	  6/1/92	PKE		#1031279: Include all of the interface files this depends on (no
									effect on objects).
		<26>	 5/19/92	PKE		#1030321,<jh>: Add interface for private direct access to
									existing NFindScriptRun routine.
		<25>	 5/14/92	PKE		#1027061,<ha>: Add interface for private ScriptToRange routine
									that returns resource ID range for a script.
		<24>	  5/8/92	PKE		#1029395,<KST>: Add new FindScriptTable definition for scripts
									to use in Cube-E. Also, for bug #1026778: Define scriptID field
									in ScriptRecord (update ScriptRecord to match ScriptPriv.a
									version). Finally: Add definition of kUsingOldInputMethodVerb
									here (as in ScriptPriv.a).
		<23>	  4/8/92	PKE		#1026516,<cv>: Move SCxxx interfaces for some ScriptMgr routines
									from private interfaces (here) to public (Script.h).
		<22>	 12/6/91	PKE		#1017161: Make TestLetter available through private Script Mgr
									interface, for use by script systems.
		<21>	 12/3/91	PKE		Add interface for SCParseTable (the implementation already
									exists).
		<20>	10/28/91	PKE		Add interfaces for SCLowerText, SCStripText, SCCharByte,
									SCCharType, SCTransliterate, SCFindWord (the implementations
									already exist).
		<19>	 10/8/91	PKE		For Cube-E (and Bruges): Add interfaces for new (currently
									private) routines RealScript, Font2RealScript, SCUpperText,
									SCStripUpperText (needed for bugs #1013149, #1012949). Clean up
									some conditionals.
		<18>	 10/2/91	YS		changed 'smgrIntlMode' (in SMgrRecord) to 'smgrUnivInstalled'.
									(Ptr->Long) changed 'scriptReserved2' (in ScriptRecord) to
									'scriptQDPatches'.(Long->Ptr)
		<17>	  9/5/91	JH		Added #ifndef __SCRIPTPRIV__ , #define __SCRIPTPRIV__, #endif
		<16>	 8/27/91	JSM		Cleanup header.
		<15>	 1/14/91	PKE		(stb) Updated Itl2Header. Updated SMgrRecord from ScriptPriv.a
									with corrected comments and names for new fields. Added
									interface for Kevin’s private FindCharInSet routine to be called
									by Dialog Mgr & Finder.
		<14>	12/14/90	SMB		(csd) I forgot the approval signature for the previous change.
		<13>	12/14/90	SMB		Moving KeyScript verb, smKeyModalDialog, here and renaming it
									smKeyDisableAboutKybds. Also adding new KeyScript verb
									smKeyEnableAboutKybds.
		<12>	12/10/90	PKE		(VL) Add interface for private ReInitScripts routine to be
									called after net booting switches system files. It cleans up
									Script Mgr data structures based on resources in old file, then
									calls InitScripts to set up new structures based on current
									file. Also, renamed smgrIconFlag2 field (formerly reserved) of
									SMgrRecord to smgrKeyScriptResult, since we now use it to
									indicate KeyScript result.
		<11>	 11/4/90	dba		use (void) instead of ()
		<10>	10/30/90	PKE		(stb) Add C version of ScriptRecord for use by script systems
									(mostly per H-S. Kim).
		 <9>	 7/25/90	PKE		Add interfaces for private InitScriptApp and CleanupScriptApp
									routines that are called when apps are launched and closed in
									order to set up and delete the new application-specific script
									globals (which, for now, just contain the application itl
									cache).
		 <8>	 7/20/90	PKE		Removed sVectFixSMgrWorld2 field from SMgrRecord; we no longer
									need it.
		 <7>	 7/11/90	PKE		Added interface for private IsCmdChar routine - common code that
									tests for Command-key combinations in an international way
									(standard FilterProc will use this to check for Cmd-period).
		 <6>	 6/13/90	PKE		Added glue for private RebuildKeybdMenu routine called by Mover
									to inform Script Mgr that keyboard menu may need updating.
		 <5>	 5/31/90	PKE		Added glue for private AddScriptFonts and SetKbdMenuInfo
									routines.
		 <4>	 5/29/90	DDG		NEEDED FOR SIXPACK: Changed all the sixpack conditionals from
									six-point-oh-seven to six-point-oh-six.
		 <3>	  5/5/90	PKE		Added glue for private InitScripts() and InitKeybdMenu()
									routines used during initialization. Updated SMgrRecord.
		 <2>	 3/26/90	PKE		Update and clean up SMgrRecord structure. Define smgrSysVers and
									smgrROMVers conditionals. Update header to BBS format.
		 <1>	12/17/89	CCH		Adding for the first time into BBS. Updated file name references.

	(BBS versions above, EASE versions below)
	   <1.2>	 9/19/89	PKE		Delete NBreakTable and NBreakTablePtr definitions, since these
									are now in Script.h.
	   <1.1>	 9/15/89	PKE		Delete OldFindWord function.
	   <1.0>	  9/1/89	PKE		Private C header file for Script Mgr. Contains C versions of
									some of the data structures in {AIncludes}ScriptPriv.a.
				  9/1/89	pke		Add Itl2Header, SMgrRecord, OldFindWord
				 9/26/88	pke		Begin.

	To Do:
		Conditionalize SMgrRecord for different system/ROM versions?
*/

#ifndef __SCRIPTPRIV__								//<JH>
#define __SCRIPTPRIV__								//<JH>

/************************************************************					<27>
*	Include necessary interfaces if not previously included
************************************************************/

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __EVENTS__
#include <Events.h>
#endif

#ifndef __MENUS__
#include <Menus.h>
#endif

#ifndef __SCRIPT__
#include <Script.h>
#endif

#ifndef __TEXTUTILS__
#include <TextUtils.h>
#endif

/************************************************************					<5>
*	Include MFPrivate.h if necessary for definition of AuxMenuItemRecPtr.
************************************************************/

#ifndef __MFPRIVATE__
#include <MFPrivate.h>
#endif

/************************************************************					<2>
*	We define smgrSysVers to use in conditionals, because SysVers is not
*	defined if NOT forRom. We also need to set up a separate smgrROMVers.
*
*	For example:	#if (smgrSysVers >= 0x606) || (smgrROMVers >= 1)
*
************************************************************/

#if ForROM

#define smgrSysVers 0				/* just so it isn't undefined		*/
#define smgrROMVers 1				/* IIci/fx/Erickson ROM				*/

#else

#define smgrSysVers (SysVers)		/* alway defined, unlike SysVers	*/
#define smgrROMVers 0				/* not a ROM build					*/

#endif


/************************************************************					<3>
*	Define a few of the feature symbols in ScriptPriv.a.
************************************************************/

#define ScriptMgrKeyboardMenu ((smgrSysVers >= 0x700) || (smgrROMVers >= 2))	/*<3>*/

/************************************************************
*	A few data types used in FindWord.c.
************************************************************/

typedef signed char SByte;
typedef unsigned char UByte;
typedef unsigned short UWord;
typedef unsigned long ULong;
typedef SByte *SBytePtr;
typedef UByte *UBytePtr;
typedef UWord *UWordPtr;

struct Itl2Header
	{
	short itl2InitHook;
	short itl2FetchHook;
	short itl2VernierHook;
	short itl2ProjectHook;
	short itl2Flags;
	short itl2ExitHook;
	short itl2TypeList;
	short itl2ClassArray;
	short itl2UpperList;
	short itl2LowerList;
	short itl2UpperNoMarkList;
	short itl2WordTable;
	short itl2WrapTable;
	short itl2NoMarkList;

	short itl2Version;
	short itl2Format;															/*<15>*/

	/* length fields */														/*added <15>*/
	short itl2InitHookLen;
	short itl2FetchHookLen;
	short itl2VernierHookLen;
	short itl2ProjectHookLen;
	short itl2Reserved2;
	short itl2ExitHookLen;
	short itl2TypeListLen;
	short itl2ClassArrayLen;
	short itl2UpperListLen;
	short itl2LowerListLen;
	short itl2UpperNoMarkListLen;
	short itl2WordTableLen;
	short itl2WrapTableLen;
	short itl2NoMarkListLen;

	/* offset/length pairs */												/*added <15>*/
	short itl2FindScriptTable;
	short itl2FindScriptTableLen;
	};
typedef struct Itl2Header Itl2Header;

/************************************************************
*	FindScriptTable declaration (new format for Cube-E)							<24>
*************************************************************/

struct FindScriptTable {
	signed char flags1;
	signed char flags2;		/* must be negative to indicate new format */
	short version;
	short length;
	short classTableOffset;
	short auxCTableOffset;
	short stateTableOffset;
	short returnTableOffset;
	short reserved;
};

typedef struct FindScriptTable FindScriptTable;
typedef FindScriptTable *FindScriptTablePtr;

/************************************************************
*	structure for script resource ID range										<25>
*************************************************************/

struct ScriptRange {
 short min;
 short max;
};

typedef struct ScriptRange ScriptRange;

/************************************************************
*	SMgrRecord declaration.																<10>
*************************************************************/

#define smgrCount 65				/* number of script entries.					*/

struct SMgrRecord
	{
	short	smgrVersion;			/* Script Mgr version number.					*/	/*<15>*/
	short	smgrMunged;				/* Globals change count.						*/	/*<15>*/
	UByte	smgrEnabled;			/* Count of enabled scripts.					*/	/*<15>*/
	Boolean	smgrBidirect;			/* At least one bidirectional script.			*/	/*<2>*/

	Boolean	smgrFontForce;			/* force font flag.								*/	/*<2>*/
	Boolean	smgrIntlForce;			/* force intl flag.								*/	/*<2>*/
	Boolean	smgrForced;				/* Script was forced to system script.			*/	/*<2><15>*/
	Boolean	smgrDefault;			/* Script was defaulted to Roman script.		*/	/*<2><15>*/

	ULong	smgrGenFlags;			/* general flags long							*/
	ULong	smgrOverride;			/* script override flags						*/
	ULong	smgrRsvdOverride;		/* reserved for overriding						*/

	Ptr		smgrPrint;				/* printer action dispatcher.					*/	/*<2>*/
	ULong	smgrUnivInstalled;		/* if we have the universal init, what scripts it supports	*/	/*<18>*/
	Ptr		smgrCharByte;			/* CharByte vector.								*/	/*<2>*/
	Ptr		smgrCharType;			/* CharType vector.								*/	/*<2>*/

	short	smgrSysScript;			/* preferred system script.						*/
	short	smgrLastScript;			/* last keyboard script.						*/
	short	smgrKeyScript;			/* keyboard script.								*/

	Rect	smgrRect;				/* toggling rectangle.							*/	/*<2>*/
	short	smgrSysRef;				/* system file volRefNum.						*/
	Handle	smgrKeySwap;			/* Handle to current 'KSWP' resource			*/	/*<15>*/
	short	smgrCharPortion;		/* Ch vs Sp Extra proportion, 4.12 fixed		*/
	short	smgrReservedB;
	ULong	smgrReservedC;

	Ptr		smgrCSisPtr;			/* contextual SIS globals ptr					*/	/*<2>*/
	ULong	smgrCSisFlags;			/* flag bits for contextual SIS					*/
	Ptr		smgrNumRepPtr;			/* ptr to number rep dispatch list				*/	/*<2>*/
	Ptr		smgrDateRepPtr;			/* ptr to date rep dispatch list				*/	/*<2>*/

	Ptr		smgrDispTable;			/* ptr to SMgr dispatch table					*/	/*<2>*/
	short	smgrDispLow;			/* low selector value							*/
	short	smgrDispHigh;			/* high selector value							*/

	Boolean	smgrDoubleByte;			/* if T, at least one 2-byte script installed	*/	/*<2>*/
	SByte	smgrDisableKybds;		/* Disab kybds flag: -1 not Sys/Roman, 1 not act */	/*<2><15>*/
	short	smgrRegionCode;			/* region code (verXxx) from itlc				*/	/*<2>*/
	Handle	smgrClientLLRecHndl;	/* handle to line layout rec for PicComment		*/	/*<2><15>*/
	ULong	smgrReservedD;																/*<3><15>*/
	Ptr		smgrKeyboardMenuPtr;	/* ptr to keyboard menu							*/	/*<3>*/
	Boolean	smgrKbdMenuAvail;		/* if T, Keyboard Menu is avail					*/	/*<15>*/
	UByte	smgrReservedE[3];															/*<2><3><15>*/
	ULong	smgrDummy;				/* dummy field - all zero						*/	/*<2>*/

	Ptr		smgrEntry[smgrCount];	/* script global entries (ptrs to ScriptRecord).*/	/*<2>*/

	/* new stuff */

	Handle	smgrCurITLK;			/* handle to current itlk						*/	/*<2><15>*/
	short	dTabNegOffset;			/* negative offset for endParse's benefit		*/
	ULong	delimMap[4];			/* delimiter table								*/
	short	smgrIconOffset;			/* script icon offset (pixels)					*/
	UByte	smgrIconSideFlag;		/* script icon side (0=right,$ff=left)			*/
	Boolean	smgrKeyScriptResult;	/* T iff KeyScript verb caused some action		*/	/*<12><15>*/

	/* old vectors for patched routines (used by RAM version only) */

	Ptr		sVectInitApplZone;		/* old InitApplZone routine pointer				*/	/*<2>*/
	Ptr		sVectGetOSEvent;		/* old GetOSEvent routine pointer				*/	/*<2>*/
	Ptr		sVectKeyTrans;			/* old KeyTrans routine pointer					*/	/*<2>*/
	Ptr		sVectScriptUtil;		/* old ScriptUtil routine pointer				*/	/*<2>*/
	Ptr		sVectLwrString;			/* old LwrString routine pointer				*/	/*<2>*/
	Ptr		sVectInitMenus;			/* old InitMenus routine pointer				*/	/*<3><8>*/
	Ptr		sVectOldSystemMenu;		/* old SystemMenu routine pointer				*/	/*<3><8>*/
	Ptr		sVectRsvd1[5];																/*<2><3><8>*/

	/* vectors for internal routines (used by ROM version only) */

	/* …from ScriptMgrUtilNum.a */

	Ptr		sVectAppendSymbol;		/* AppendSymbol routine pointer					*/	/*<2>*/
	Ptr		sVectConvertToString;	/* ConvertToString routine pointer				*/	/*<2>*/
	Ptr		sVectExpHandling;		/* ExpHandling routine pointer					*/	/*<2>*/
	Ptr		sVectExpMatching;		/* ExpMatching routine pointer					*/	/*<2>*/
	Ptr		sVectCheckForDigits;	/* CheckForDigits routine pointer				*/	/*<2>*/
	Ptr		sVectMatchingSubstring;	/* MatchingSubstring routine pointer			*/	/*<2>*/
	Ptr		sVectCond;				/* Cond routine pointer							*/	/*<2>*/
	Ptr		sVectCheckForm;			/* CheckForm routine pointer					*/	/*<2>*/
	Ptr		sVectTackOnExp;			/* TackOnExp routine pointer					*/	/*<2>*/
	Ptr		sVectMakeExp;			/* MakeExp routine pointer						*/	/*<2>*/
	Ptr		sVectCheckPartsIntegrity;/* CheckPartsIntegrity routine pointer			*/	/*<2>*/
	Ptr		sVectRetrieveChar;		/* RetrieveChar routine pointer					*/	/*<2>*/
	Ptr		sVectIsSubstring;		/* IsSubstring routine pointer					*/	/*<2>*/

	/* …from elsewhere */

	Ptr		sVectSwapIcon;			/* SwapIcon routine pointer						*/	/*<2>*/
	Ptr		sVectSwapKybd;			/* SwapKybd routine pointer						*/	/*<2>*/
	Ptr		sVectFixSMgrWorld;		/* FixSMgrWorld routine pointer					*/	/*<2>*/

	/* vectors for communication between ptches, managers, etc. */

	Ptr		sVectSMgrCalcRect;		/* SMgrCalcRect routine pointer					*/	/*<2>*/
	Ptr		sVectSMgrInitFonts;		/* SMgrInitFonts routine pointer				*/	/*<2>*/
	Ptr		sVectSMgrPostMunging;	/* SMgrPostMunging routine pointer				*/	/*<2>*/
	Ptr		sVectCallInterface;															/*<2>*/
	Ptr		sVectInitKeyboardMenu;														/*<3>*/
	Ptr		sVectRsvd2[3];																/*<3>*/
	};

typedef struct SMgrRecord SMgrRecord;

/************************************************************
*	ScriptRecord declaration.																<10>
*************************************************************/

struct	ScriptRecord
	{
	short		scriptVersion;			// script version number.
	short		scriptMunged;			// script globals change count.
	Boolean		scriptEnabled;			// script enabled flag.
	Boolean		scriptRight;			// right to left flag.
	Boolean		scriptJust;				// justification flag.
	Boolean		scriptRedraw;			// word redraw flag.

	short		scriptSysFond;			// preferred system font.
	short		scriptAppFond;			// preferred application font.

	ItlbRecord	scriptBundle;			// bundle

	Ptr			scriptPrint;			// printer action vector.
	Ptr			scriptTrap;				// ScriptUtil trap vector.

	OSType		scriptCreator;			// script creator signature.
	Ptr			scriptFile;				// script file
	Ptr			scriptName;				// script name

	ULong		scriptXFlags;			// 'X'tra flags for
	ULong		scriptOverRide1;		// for overriding
	ULong		scriptOverRide2;		// for overriding

	Ptr			scriptDispTable;		// ptr to script dispatch table
	short		scriptDispLow;			// low selector value
	short		scriptDispHigh;			// high selector value

	long		scriptMonoFondSize;		// default monospace FOND (hi) & size (lo)
	long		scriptPrefFondSize;		// preferred FOND (hi) & size (lo)
	long		scriptSmallFondSize;	// default small FOND (hi) & size (lo)
	long		scriptSysFondSize;		// default system FOND (hi) & size (lo)
	long		scriptAppFondSize;		// default app FOND (hi) & size (lo)
	long		scriptHelpFondSize;		// default Help Mgr FOND (hi) & size (lo)

	SByte		scriptKeysItemNum;		// default KCHR menu item number
	UByte		scriptKCHRCount;		// count of # of enabled KCHRs

	UByte		scriptValidStyles;		// Style- set of all valid styles for script
	UByte		scriptAliasStyle;		// Style- alias style for script
	Boolean		scriptInItlm;			// true iff this script has 'itlm' entry
	UByte		scriptID;				// this script's scriptcode.				<24>
	UByte		scriptReserved2[2];		// reserved.								<24>
	Ptr			scriptAvail;			// Avail routine vector, or 0 if unused
	Ptr			scriptAddFonts;			// AddFonts routine vector, or 0 if unused
	Ptr			scriptQDPatches;		// the qd routines dispatch table.(universal init) <18>
	};

typedef struct ScriptRecord ScriptRecord;


/************************************************************					<3>
*	Glue for private InitScripts() and InitKeybdMenu() routines
*	used during initialization. InitScripts is called by
*	StartSystem code, and InitKeybdMenu is called by Process
*	Mgr (a.k.a. MultiFinder).
*
*	Add glue for AddScriptFonts(), which is called by StartSystem,				<5>
*	and SetKbdMenuInfo(), which is called by Process Mgr.
*
*	Add glue for RebuildKeybdMenu(), which is called by Mover					<6>
*	to notify us that keyboards have been moved into or out of
*	the System and the keyboard menu may need updating.
*
*	Add glue for Boolean IsCmdKey(EventRecord keyEvent, short testChar),		<7>
*	which provides common code that tests for Command-key combinations
*	in an international way (standard FilterProc will use this to check
*	for Cmd-period).
*
*	Added glue for InitScriptApp and CleanupScriptApp.							<9>
*
*	Added glue for ReInitScripts.												<12>
*
************************************************************					<15>
* FUNCTION FindCharInSet(textPtr: Ptr; textLen: LongInt; charSet: StringPtr;
*						table: CharByteTable): LongInt;
*
*	The textPtr and textLen parameters specify a string to be searched for any
*	of the characters in charSet. If any are found, the offset where the
*	character was found is returned; otherwise, the function returns -1.
*
*	The table parameter is obtained from the Script Mgr ParseTable routine.
*	The caller  must set the txFont of the port to a font in the script being
*	handled, then call ParseTable to get the table.
*
*	This routine is used by Dialog Mgr and Finder (and Help Mgr?).
*	Written by Kevin S. MacDonell.
************************************************************/

pascal OSErr InitScripts(void)													/*<3>*/
	= {0x2F3C,0x8200,0xFFDA,0xA8B5};

pascal OSErr InitKeybdMenu(void)												/*<3>*/
	= {0x2F3C,0x8200,0xFFD8,0xA8B5};

pascal OSErr AddScriptFonts(void)												/*<5>*/
	= {0x2F3C,0x8200,0xFFD6,0xA8B5};

pascal OSErr SetKbdMenuInfo(MenuHandle, short menuItem, AuxMenuItemRecPtr)		/*<5>*/
	= {0x2F3C,0x820A,0xFFD4,0xA8B5};

pascal OSErr RebuildKeybdMenu(void)												/*<6>*/
	= {0x2F3C,0x8200,0xFFD2,0xA8B5};

pascal Boolean IsCmdChar(const EventRecord *, short test)						/*<7>*/
	= {0x2F3C,0x8206,0xFFD0,0xA8B5};

pascal OSErr InitScriptApp(void)												/*<9>*/
	= {0x2F3C,0x8200,0xFFCE,0xA8B5};

pascal OSErr CleanupScriptApp(void)												/*<9>*/
	= {0x2F3C,0x8200,0xFFCC,0xA8B5};

pascal OSErr ReInitScripts(void)												/*<12>*/
	= {0x2F3C,0x8200,0xFFCA,0xA8B5};

pascal long FindCharInSet(Ptr textPtr,long textLen,StringPtr charSet,CharByteTable table)	/*<15>*/
	= {0x2F3C,0x8410,0xFFC8,0xA8B5};


pascal short RealScript(void)													/*<19>*/
	= {0x2F3C,0x8200,0xFFBA,0xA8B5}; 

pascal short Font2RealScript(short fontNumber)									/*<19>*/
	= {0x2F3C,0x8202,0xFFB8,0xA8B5}; 

pascal Boolean TestLetter(short testChar)										/*<22>*/
	= {0x2F3C,0x8202,0xFFB4,0xA8B5}; 

pascal ScriptRange ScriptToRange(ScriptCode script)								/*<25>*/
	= {0x2F3C,0x8402,0xFFB2,0xA8B5}; 

pascal ScriptRunStatus NFindScriptRun(Ptr textPtr,long textLen,long *lenUsed,
										FindScriptTablePtr fsTablePtr)			/*<26>*/
	= {0x2F3C,0x8210,0xFFB0,0xA8B5}; 


/* Moved these KeyScript verbs here since adding smKeyEnableAboutKybds after the 7.0 interfaces have
   frozen. (and we also don't believe a developer will ever want them!)									<13>
*/
enum {smKeyDisableAboutKybds = -13};		/* Disable ‘About…’ menu item since another dialog is up	<13>*/
enum {smKeyEnableAboutKybds = -14};			/* Enable ‘About…’ menu item							 	<13>*/

/* for input methods (add from ScriptPriv.a) */
#define kUsingOldInputMethodVerb (-1000)	/* Secret verb which is used for checking on input method type. */	/*<24>*/

#endif   //<JH>
