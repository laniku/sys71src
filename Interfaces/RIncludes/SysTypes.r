/*
	File:		SysTypes.r

	Copyright:	© 1986-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM4>	 7/7/92		CSS		Update from Reality:
	   								<26> 6/24/92 DCL	Changed #ifndef __SYSTYPES.R__ to __SYSTYPES_R__  at the request
														of the MPW team (3.2.3 rez broke on the periods)
	   <SM3>	 6/11/92	CSS		Roll-in Reality Changes:
	   								<25> 3/30/92 PKE	#1022875,<ha>: Udate KSWP template to include RomanIfOthers
														action (corresponds to smKeyRoman KeyScript verb) that sets
														keyboard script to Roman if other scripts are also installed;
														otherwise it does nothing, and corresponding key combination is
														not stripped from event queue.
	   <SM2>	 5/17/92	kc		Roll in Horror changes. Comments follow:
		<H3>	 2/12/92	SWC		Added ‘accl’ definition, which describes mouse/trackball
									acceleration curves for new cursor code.
		<H2>	11/12/91	jmp		Added ‘pslt’ definition and equates from System Disk 7.0.1.
		<24>	10/28/91	SAM/KSM	Rolled in Regatta file.
	
	Regatta Change History:

		 <3>	 6/14/91	SAM		Added DAF's pslt definition.

	7.0 Change History:

		<23>	 9/25/91	PKE		For Cube-E (and Bruges): Add system flags (currently just line
									direction) to 'itlc' resource to save user prefs for global
									states that have some representation (such as TESysJust) outside
									the SMgrRecord.
		<22>	 7/30/91	PKE		Fix ‘itl1’ template by adding “align word” between tables in
									extended format.
		<21>	  1/3/91	JDR		(dba) Encode field of a snd is missing. It is the upper byte of
									the old baseFrequency INTEGER.
		<20>	12/15/90	PKE		(csd) Add RotateKybd constant for first field of ‘KSWP’.
		<19>	11/29/90	JDR		<KIP> Found a bug in the snd templete that I created since the
									Rez syntax is so obvious I'm surprised I didn't notice it
									before.
		<18>	11/14/90	JDR		Correcting interfaces to match the documentation.  Removed sound
									commands that cannot be used by a snd resource.
		<17>	11/10/90	JDR		Corrected the 'snd ' resource.  First, get rid of references to
									"note" to satisfy the Apple Legal.  Second, changed names of
									'snth' within the 'snd ' resource to properly match standard
									interfaces and documentation.  Third, corrected 22k sample rate.
		<16>	 9/18/90	PKE		Update 'itl2' and 'itl4' types.
		<15>	 9/18/90	dba		merge with 3.2b1
		<14>	 8/29/90	stb		define resf type so 7.0 can use it rather than FRSV
		<13>	 7/17/90	PKE		Changed reserved field in itlb to be optional itl5 id, fixed a
									comment.
		<12>	 6/22/90	PKE		Updated 'FONT' type to 1986 level: added optional width and
									height tables, per Charles Williams. Updated Script, Language,
									and Region defines to use new constant names.
		<11>	  6/3/90	csd		Added type declaration for FRSV -16493.
		<10>	 5/29/90	PKE		Added bytes for valid style and alias style to 'itlb' type.
									Added list of additional separators to 'itl1'.
		 <9>	 5/21/90	PKE		Added region code table to itlm type. Separated 'itl1' type from
									'INTL' (1), and modified it to permit an optional extension for
									abbreviated day/month names and a few other things. Added
									verArabic to Region list. Use smTradChinese and smSimpChinese
									instead of smChinese; use langTradChinese and langSimpChinese
									instead of langChinese.
		 <8>	  5/2/90	PKE		Rearranged 'itlm' resource format: Store pairs of <scriptcode,
									default langcode> in the order we would like scripts to sort,
									and pairs of <langcode, parent scriptcode> in the order we would
									like languages to sort. Added 'itlm' format code and maximum
									sizes for the internal tables that will be built from the 'itlm'
									resource.
		 <7>	 4/25/90	PKE		Added Script and Language defines. Added 'itlm' type:
									multiscript mapping/sorting data. Re-added BBS header.
		 <6>	 3/21/90	PKE		Updated itlb type: added field for script local record
		 							size; added fields for font/size info; changed resource
									ID fields from unsigned integer to integer.
		 <5>	 3/15/90	JSM		Add 'ppcc', PPC Browser configuration resource.
		 <4>	  2/1/90			Official MPW version. Blasted the header.
		 <3>	 1/17/90	PKE		Added field to itlc type for region code (preferred
		 							verXxx). Changed “Country” to “Region”.
		 <2>	 1/17/90	PKE		Added several more verXxx codes. Updated itlc resource
		 							type to MPW 3.1 level. Updated header to BBS format.

	10/08/87	- THT: fixed scrn, flags were in wrong order.
	10/08/87	- THT: changed FONT & FOND definitions to use labels.
	10/08/87	- THT: added 'snd ' resource.
	12/09/87	- THT: added verIreland through verThailand to Country.
	02/29/88	- THT: added more specific bit information to KSWP and
					   changed the array size definition so that it
					   would derez properly.
	04/18/88	- THT: added 'vers' resource definition.
	06/30/88	- THT: added synth values to 'snd '.
	09/20/88	- THT: added verIndia & verPakistan country codes.
	09/20/88	- THT: added 'itl2' & 'itl4' resource definitions.
	09/28/88	- THT: added 'mcky' and 'finf' resource definitions.
	11/09/88	- THT: updated 'snd ' according to new documentation.
	11/29/88	- THT: added replace bit to CommFlags of 'insc'.
	12/06/88	- THT: changed definition of 'itlb' and 'itlc'.
	02/03/89	- THT: changed 'FONT' to support pixel depths > 1 for NFNT
	02/08/89	- THT: change verGemany to verGermany
	03/20/89	- THT: added #ifndef __SYSTYPES.R__
	04/12/89	- THT: added fields to itlc for script icon
	04/12/89	- THT: added 'itlk' resource definition
	04/12/89	- THT: added new 'itl2' resource definition
	05/08/89	- THT: doctored up 'INTL' (0) with new constants: monYearDay,
					   dayYearMon, yearDayMon, and twelveHourZeroCycle.
	09/06/89	- THT: added Faroese, Farsi, and Cyrillic to Country list.
	01/11/90	- JAL: added Hindi, Poland, Hungary, Estonia, Latvia, Lapland, and Lithuania to Country list.
	01/12/90	- JAL: changed Farsi to Iran, Faroese to FaroeIsl and Cyrillic to Russia in Country list.
	01/12/90	- JAL: added 'mach' type
*/

#ifndef __SYSTYPES_R__
#define __SYSTYPES_R__

/*----------------------------pslt • Nubus psuedo-slot mapping constants------------------*/
#define	horizAscending		0			/* horizontal form factor, ascending slot order   */
#define	horizDescending		1			/* horizontal form factor, descending slot order  */
#define	vertAscending		2			/* vertical form factor, ascending slot order     */
#define	vertDescending		3			/* vertical form factor, descending slot order    */


/*----------------------------pslt • Nubus pseudo-slot mapping resource-------------------*/
type 'pslt' {
		integer = $$Countof(pSlotSpec);							/* # of slots 			  */
		integer;												/* Nubus orientation	  */							
		longint;												/* psltFlags, reserved    */
		wide array pSlotSpec {
				integer;										/* Nubus slot #			  */
				integer;										/* pseudo slot #		  */
		};
};


/*-------------------------------------Equates------------------------------------------*/
/*	The following are used to set characters used in INTL resources.
*/
#define	periodSymbol		"."
#define	commaSymbol			","
#define	semicolonSymbol		";"
#define	dollarsignSymbol	"$"
#define	slashSymbol			"/"
#define	colonSymbol			":"

#define Script		smRoman, smJapanese, smTradChinese, smKorean,		\
					smArabic, smHebrew, smGreek, smCyrillic, smRSymbol,	\
					smDevanagari, smGurmukhi, smGujarati, smOriya,		\
					smBengali, smTamil, smTelugu, smKannada,			\
					smMalayalam, smSinhalese, smBurmese, smKhmer,		\
					smThai, smLaotian, smGeorgian, smArmenian,			\
					smSimpChinese, smTibetan, smMongolian, smGeez,		\
					smSlavic, smVietnamese, smExtArabic, smUninterp		\

#define Language	langEnglish, langFrench, langGerman, langItalian,	\
					langDutch, langSwedish, langSpanish, langDanish,	\
					langPortuguese, langNorwegian, langHebrew,			\
					langJapanese, langArabic, langFinnish, langGreek,	\
					langIcelandic, langMaltese, langTurkish,			\
					langCroatian, langTradChinese, langUrdu,			\
					langHindi, langThai, langKorean, langLithuanian,	\
					langPolish, langHungarian, langEstonian,			\
					langLettish, langLappish, langFaeroese,				\
					langFarsi, langRussian, langSimpChinese,			\
					langFlemish, langIrish, langAlbanian, langRomanian,	\
					langCzech, langSlovak, langSlovenian, langYiddish,	\
					langSerbian, langMacedonian, langBulgarian,			\
					langUkrainian, langByelorussian, langUzbek,			\
					langKazakh, langAzerbaijani, langAzerbaijanAr,		\
					langArmenian, langGeorgian, langMoldavian,			\
					langKirghiz, langTajiki, langTurkmen,				\
					langMongolian, langMongolianCyr, langPashto,		\
					langKurdish, langKashmiri, langSindhi, langTibetan,	\
					langNepali, langSanskrit, langMarathi, langBengali,	\
					langAssamese, langGujarati, langPunjabi, langOriya,	\
					langMalayalam, langKannada, langTamil, langTelugu,	\
					langSinhalese, langBurmese, langKhmer, langLao,		\
					langVietnamese, langIndonesian, langTagalog,		\
					langMalayRoman, langMalayArabic, langAmharic,		\
					langTigrinya, langGalla, langSomali, langSwahili,	\
					langRuanda, langRundi, langChewa, langMalagasy,		\
					langEsperanto, langUnspecified = 32767				\

#define	Region		verUS, verFrance, verBritain, verGermany,			\
					verItaly, verNetherlands, verBelgiumLux,			\
					verFrBelgiumLux = 6, verSweden, verSpain,			\
					verDenmark, verPortugal, verFrCanada, verNorway,	\
					verIsrael, verJapan, verAustralia, verArabia,		\
					verArabic=16, verFinland, verFrSwiss, verGrSwiss,	\
					verGreece, verIceland, verMalta, verCyprus,			\
					verTurkey, verYugoslavia, verYugoCroatian = 25,		\
					verIndia = 33, verIndiaHindi = 33, verPakistan,		\
					verLithuania = 41, verPoland, verHungary,			\
					verEstonia, verLatvia, verLapland, verFaeroeIsl,	\
					verIran, verRussia, verIreland = 50, verKorea,		\
					verChina, verTaiwan, verThailand					\


/*		The following are used to set styles, simply add for desired style.
*/
#define	bold			1
#define italic			2
#define underline		4
#define outline 		8
#define shadow			16
#define condense		32
#define extend			64

/*-----------------------accl • Mouse Acceleration Tables ------------------------------*/
type 'accl' {
	literal longint						/* Device identifier or device class */
		classAbsolute,					/* A flat-response device */
		classMouse,						/* Mechanical or optical mouse */
		classTrackball,					/* Trackball */
		classScratchPad,				/* e. g. Midas */
		classJoystick,					/* e. g. HomeRow */
		classRelTablet;					/* Relative tablet */
		
	integer = $$CountOf(AcclTable);		/* Number of tables for this device */
	array AcclTable {					/* Entries sorted by first value; must have at least 0.0 and 1.0 tables */
		unsigned hex longint;			/* Acceleration provided by this table (Fixed) */
		
		integer = $$CountOf(AcclPoint);	/* Number of control points for this device */
		wide array AcclPoint {			/* Entries sorted by first value; implicit first entry (0.0, 0.0); at least one more entry required */
			unsigned hex longint;		/* Device speed (inches per second) (Fixed) */
			unsigned hex longint;		/* Cursor speed (inches per second) (Fixed) */
		};
	};
};

/*----------------------------DRVR • Driver---------------------------------------------*/
type 'DRVR' {
		boolean = 0;
		boolean			dontNeedLock, needLock;					/* lock drvr in memory	*/
		boolean			dontNeedTime, needTime;					/* for periodic	action	*/
		boolean			dontNeedGoodbye, needGoodbye;			/* call before heap reinit*/
		boolean			noStatusEnable, statusEnable;			/* responds to status	*/
		boolean			noCtlEnable, ctlEnable;					/* responds to control	*/
		boolean			noWriteEnable, writeEnable;				/* responds to write	*/
		boolean			noReadEnable, readEnable;				/* responds to read		*/
		byte = 0;
		integer;												/* driver delay			*/
		unsigned hex integer;									/* desk acc event mask	*/
		integer;												/* driver menu			*/
		unsigned hex integer;									/* offset to open		*/
		unsigned hex integer;									/* offset to prime		*/
		unsigned hex integer;									/* offset to control	*/
		unsigned hex integer;									/* offset to status		*/
		unsigned hex integer;									/* offset to close		*/
		pstring;												/* driver name			*/
		hex string;												/* driver code			*/
};
/*----------------------------finf • Font Family Description----------------------------*/
type 'finf' {
		integer = $$CountOf(Fonts);								/* # of fonts			*/
		array Fonts {
			integer;											/* Font Number			*/
			unsigned hex integer	plain;						/* 		Font Style		*/
			integer;											/* 		Font Size		*/
		};
};
/*----------------------------FOND • Font Family Description----------------------------*/
/* Note: this FOND resource definition only works when the tables at the end of the
		 resource are in this order:	1 - Family Character-Width Table
		 								2 - Style Mapping Table
										3 - Kerning Tables
*/
type 'FOND' {
		/* Flags Word */
		boolean		proportionalFont, fixedWidthFont;
		boolean		useFractWidthTable, dontUseFractWidthTable;
		boolean		computeFixedPointExtra, useIntegerExtra;
		boolean		useFractEnable, ignoreFractEnable;
		boolean		canAdjustCharSpacing, dontAdjustCharSpacing;
		unsigned hex bitstring[9] = 0;							/* Reserved				*/
		boolean		noCharWidthTable, hasCharWidthTable;
		boolean		noImageHeightTable, hasImageHeightTable;

		integer;												/* Family ID number		*/
	First:
		integer;												/* first char			*/
	Last:
		integer;												/* last char			*/
		integer;												/* Ascent				*/
		integer;												/* Descent				*/
		integer;												/* Leading				*/
		integer;												/* Width Max			*/
	WidthOffset:
		unsigned hex longint = WidthTable[1] >> 3;				/* Width table offset	*/
	KerningOffset:
		unsigned hex longint = KerningTable[1] >> 3;			/* Kerning table offset	*/
	StyleMapOffset:
		unsigned hex longint = StyleTable[1] >> 3;				/* Style map offset		*/
		integer;												/* reserved				*/
		integer;												/* ex wid bold			*/
		integer;												/* ex wid italic		*/
		integer;												/* ex wid underline		*/
		integer;												/* ex wid outline		*/
		integer;												/* ex wid shadow		*/
		integer;												/* ex wid condensed		*/
		integer;												/* ex wid extended		*/
		integer;												/* reserved				*/
		longint;												/* reserved for intl	*/
	Version:
		integer;												/* version				*/

		/* Font Association Table */
		integer = $$CountOf(FontEntries)-1; 					/* # of font entries	*/
		wide array FontEntries {
			integer;											/* Font size			*/
			unsigned hex integer	plain;						/* 		Font Style		*/
			integer;											/* Resource ID of FONT	*/
		};
		/*  */
		array [$$Word(Version) == 2] {
	OffsetTableStart:
			integer = $$CountOf(OffsetTable) - 1;
			array OffsetTable {
				longint = (BBoxStart[1] - OffsetTableStart[1]) >> 3;
			};
			/* Font Bounding Box Table */
	BBoxStart:
			integer = $$CountOf(BBoxTable) - 1;
			wide array BBoxTable {
				fill bit[9];									/* Reserved				*/
				Boolean		noExtendedStyle, EXTENDEDstyle;		/* Extended style		*/
				Boolean		noCondensedStyle, CONDENSEDstyle;	/* Condensed style		*/
				Boolean		noShadowStyle, SHADOWstyle;			/* Shadow style			*/
				Boolean		noOutlineStyle, OUTLINEstyle;		/* Outline style		*/
				Boolean		noUnderline, UNDERLINEstyle;		/* Underline style		*/
				Boolean		noItalicStyle, ITALICstyle;			/* Italic style			*/
				Boolean		noBoldStyle, BOLDstyle;				/* Bold style			*/
				Rect;
			};
		};

		/* Family Character-Width Table */
		/* This outer array below handles the case when the width table offset (WidthOffset:)
		   is zero. */
		array [$$Long(WidthOffset) != 0] {
	WidthTable:
			integer = $$CountOf(WidthTable) - 1;				/* # of width tables	*/
			wide array WidthTable {
				fill bit[9];									/* Reserved				*/
				Boolean		noExtendedStyle, EXTENDEDstyle;		/* Extended style		*/
				Boolean		noCondensedStyle, CONDENSEDstyle;	/* Condensed style		*/
				Boolean		noShadowStyle, SHADOWstyle;			/* Shadow style			*/
				Boolean		noOutlineStyle, OUTLINEstyle;		/* Outline style		*/
				Boolean		noUnderline, UNDERLINEstyle;		/* Underline style		*/
				Boolean		noItalicStyle, ITALICstyle;			/* Italic style			*/
				Boolean		noBoldStyle, BOLDstyle;				/* Bold style			*/

				wide array [$$Word(Last) - $$Word(First) + 3] {
					unsigned hex integer;						/* Width of character	*/
				};
			};
		};

		/* Style Mapping Table */
		/* This outer array below handles the case when the width table offset (WidthOffset:)
		   is zero. */
		array [$$Long(StyleMapOffset) != 0] {
	StyleTable:
			unsigned hex integer;								/* Font class			*/
	CharCodeOffset:
			unsigned hex longint =								/* Encoding table offset*/
				(CharCodeTable[1,1] - StyleTable[1]) / 8 * (CharCodeTable[1,1] != 0);
			fill long;											/* Reserved				*/
			array [48] {
				byte;
			};
			/* Style Name Table */
			integer = $$CountOf(StyleNames);					/* Number of strings	*/
			pstring;											/* Full base font name	*/
			array StyleNames {
				pstring;										/* Style suffix names	*/
			};

			/* Character Set Encoding Table */
			/* This outer array below handles the case when the character set encoding
			   offset is zero (CharCodeOffset:) */
			array [$$Long(CharCodeOffset[1]) != 0] {
	CharCodeTable:
				integer = $$CountOf(CharacterCodes);			/* Number of entries	*/
				wide array CharacterCodes {
					char;										/* Character code		*/
					pstring;									/* Char name string		*/
				};
			};
		};

		/* Kerning Tables */
		/* This outer array below handles the case when the kerning table offset
		   (KerningOffset:) is zero. */
		array [$$Long(KerningOffset) != 0] {
			/* Kerning Tables */
	KerningTable:
			integer = $$CountOf(KerningTables) - 1;				/* Number of tables		*/
			wide array KerningTables {
				fill bit[9];									/* Reserved				*/
				Boolean		noExtendedStyle, EXTENDEDstyle;		/* Extended style		*/
				Boolean		noCondensedStyle, CONDENSEDstyle;	/* Condensed style		*/
				Boolean		noShadowStyle, SHADOWstyle;			/* Shadow style			*/
				Boolean		noOutlineStyle, OUTLINEstyle;		/* Outline style		*/
				Boolean		noUnderline, UNDERLINEstyle;		/* Underline style		*/
				Boolean		noItalicStyle, ITALICstyle;			/* Italic style			*/
				Boolean		noBoldStyle, BOLDstyle;				/* Bold style			*/
				integer = $$CountOf(KerningTableEntry);			/* # of entries			*/
				wide array KerningTableEntry {
					char;										/* first char of pair	*/
					char;										/* second char of pair	*/
					unsigned hex integer;						/* kerning offset		*/
				};
			};
		};
};
/*----------------------------FONT • Font Description-----------------------------------*/
/* PROBLEMS: the offset to the offset/width table has been changed to a longint, with the
			 high word stored in the neg descent field (if its not -1).  Rez can't handle
			 this. */
type 'FONT' {
		/* Font Type Flags */
FontType:
		boolean = 1;											/* Reserved				*/
		boolean		doExpandFont, dontExpandFont;
		boolean		proportionalFont, fixedWidthFont;
		boolean = 1;											/* Reserved				*/
		unsigned bitstring[2] = 0;								/* Reserved				*/
		boolean		blackFont, colorFont;
		boolean		notSynthetic, isSynthetic;
		boolean		nofctbRsrc, hasfctbRsrc;
		unsigned bitstring[3] = 0;								/* Reserved				*/
		unsigned bitstring[2]	oneBit, twoBit,					/* Font depth			*/
								fourBit, eightBit;
		boolean		noCharWidthTable, hasCharWidthTable;
		boolean		noImageHeightTable, hasImageHeightTable;

	FirstChar:
		integer;												/* first char			*/
	LastChar:
		integer;												/* last char			*/
		integer;												/* width max			*/
		integer;												/* kern max				*/
		integer;												/* neg descent			*/
		integer;												/* font rect width		*/
	Height:
		integer;												/* font rect height		*/
	Offset:
		unsigned integer = ((WidthTable-Offset)/16);			/* offset to off/wid tab*/
		integer;												/* ascent				*/
		integer;												/* descent				*/
		integer;												/* leading				*/
	RowWords:
		integer;												/* row width (in words)	*/

		/* Tables */
		/* Bit image */
		hex string [($$Word(RowWords) <<($$BitField(FontType, 12, 2)
			& 3) + 1) * $$Word(Height)];

		/* Location Table */
		array [$$Word(LastChar) - $$Word(FirstChar) + 3] {
			integer;
		};

		/* Offset/Width Table */
	WidthTable:
		array [$$Word(LastChar) - $$Word(FirstChar) + 3] {
			integer;
		};

		/* Optional Character Width Table */
		Array [($$Word(FontType) & 0x0002) != 0] {
			array [$$Word(LastChar) - $$Word(FirstChar) + 3] {
				integer;
			};
		};

		/* Optional Image Height Table */
		Array [($$Word(FontType) & 0x0001) != 0] {
			array [$$Word(LastChar) - $$Word(FirstChar) + 3] {
				integer;
			};
		};
};
/*----------------------------FWID • Font Width Table-----------------------------------*/
type 'FWID' {
		unsigned hex integer;									/* Font type			*/
		integer;												/* first char			*/
		integer;												/* last char			*/
		integer;												/* width max			*/
		integer;												/* kern max				*/
		integer;												/* neg descent			*/
		integer;												/* font rect width		*/
		integer;												/* font rect height		*/
		unsigned hex integer;									/* offset to off/wid tab*/
		integer;												/* ascent				*/
		integer;												/* descent				*/
		integer;												/* leading				*/
		integer;												/* row width (in words)	*/
		wide array {											/* offset/width table	*/
			byte;												/* char offset			*/
			byte;												/* char width			*/
		};
};
/*----------------------------gmcd • Guard Mechanism for Compression/Decompression------*/
type 'gmcd' {
		integer = $$Countof(TypeIDArray);
		array TypeIDArray {
			literal longint;									/* resource type */
			integer;											/* resource ID */
		};
};
/*----------------------------insc • Installer Script-----------------------------------*/
#define	CommFlags 																		   \
		boolean		noDelRemove, delRemove;				/* Remove file if remove clicked*/ \
		boolean		noDelInstall, delInstall;			/* Delete target before copy	*/ \
		boolean		noCopy, copy;						/* Copy file to destination		*/ \
		fill bit[3];									/* Reserved						*/ \
		boolean		doReplace, dontReplace;				/* Replace						*/ \
		fill bit[1];									/* Reserved						*/ \
		boolean		old, noOld;							/* Type & creator need not match*/ \
		boolean		noUpdateOnly, updateOnly			/* Only update if target exists	*/

#define	FileSpecFlags																	   \
		CommFlags;																		   \
		boolean		noRsrcFork, rsrcFork;				/* Apply operation to rsrc fork */ \
		boolean		noDataFork, dataFork;				/* Apply operation to data fork	*/ \
		boolean		needExist, needNotExist;			/* File need not exist			*/ \
		boolean		noCrDate, crDate;					/* Creation date must match		*/ \
		boolean		noTypeCr, typeCr;					/* Type and creator must match	*/ \
		bitstring[1] = 1								/* Indicates file specification	*/

#define	RsrcSpecFlags																	   \
		CommFlags;																		   \
		fill bit;										/* Reserved						*/ \
		boolean		noEvenIf, evenIf;					/* Do it even if rsrc protected */ \
		boolean		needExist, needNotExist;			/* Rsrc need not exist			*/ \
		fill bit;										/* Reserved						*/ \
		boolean noByID, byID;							/* Use name or id to find rsrc	*/ \
		bitstring[1] = 0								/* Indicates rsrc specification	*/

#define	FileSpec																		   \
		FileSpecFlags;									/* FileSpec Flags				*/ \
		literal longint;								/* File Type					*/ \
		literal longint;								/* File Creator					*/ \
		unsigned hex longint;							/* Creation Date, use			   \
														   $$DateToLongInt() to read in	   \
														   the date.					*/ \
		fill long[3];									/* Handle, FDelSize, FAddSize	*/ \
		pstring;										/* File Name					*/ \
		align word

type 'insc' {
		switch {
			case format0:
				key integer = 0;								/* Script Format		*/
				hex integer = 0;								/* Script Flags			*/
				pstring;										/* Script Name			*/
				align word;
				wstring;										/* Script Help			*/
				align word;
				unsigned integer = $$CountOf(FileList);			/* File List			*/
				wide array FileList {
					FileSpec;									/* File Spec			*/
				};
				unsigned integer = $$CountOf(ResFileList);		/* Resource File List	*/
				wide array ResFileList {
					FileSpec;									/* Target File Spec		*/
					integer = $$CountOf(SrcFileList);			/* Source File List		*/
					wide array SrcFileList {
						FileSpec;								/* Source File Spec		*/
						unsigned integer = $$CountOf(ResList);	/* Resource List		*/
						wide array ResList {
							RsrcSpecFlags;						/* Resource Spec Flags	*/
							literal longint;					/* Resource Type		*/
							integer;							/* Source ID			*/
							integer;							/* Target ID			*/
							fill word[2];						/* CRC/Version, Filler1	*/
							fill long[3];						/* Filler2, RDelSize,
																	RAddSize			*/
							pstring;							/* Resource Name		*/
							align word;
							integer = 0;						/* Previous CRC List	*/
						};
					};
				};
				integer = 0;									/* Disk Blocks			*/

			case format1:
				key integer = 1;								/* Script Format		*/
				hex integer = 0;								/* Script Flags			*/
				pstring;										/* Script Name			*/
				align word;
				wstring;										/* Script Help			*/
				align word;
				unsigned integer = $$CountOf(FileList);			/* File List			*/
				wide array FileList {
					FileSpec;									/* File Spec			*/
				};
				unsigned integer = $$CountOf(ResFileList);		/* Resource File List	*/
				wide array ResFileList {
					FileSpec;									/* Target File Spec		*/
					integer = $$CountOf(SrcFileList);			/* Source File List		*/
					wide array SrcFileList {
						FileSpec;								/* Source File Spec		*/
						unsigned integer = $$CountOf(ResList);	/* Resource List		*/
						wide array ResList {
							RsrcSpecFlags;						/* Resource Spec Flags	*/
							literal longint;					/* Resource Type		*/
							integer;							/* Source ID			*/
							integer;							/* Target ID			*/
							fill word[2];						/* CRC/Version, Filler1	*/
							fill long[3];						/* Filler2, RDelSize,
																   RAddSize				*/
							pstring;							/* Resource Name		*/
							align word;
							integer = 0;						/* Previous CRC List	*/
						};
					};
				};
				unsigned integer;								/* Boot Block Version	*/
				unsigned integer;								/* Number of Open Files	*/
				unsigned integer;								/* Number of Events		*/
				unsigned hex longint;							/* Sys Heap Size 128K	*/
				unsigned hex longint;							/* Sys Heap Size 256K	*/
				unsigned hex longint;							/* Sys Heap Size 512K	*/
		  };
};
/*----------------------------INTL (0) • International Formatting Information-----------*/
type 'INTL' (0) {
		char		period = periodSymbol;						/* decimal pt sep		*/
		char		comma = commaSymbol;						/* thousands sep		*/
		char		semicolon = semicolonSymbol;				/* list sep				*/
		char		dollarsign = dollarsignSymbol;				/* currSym1				*/
		char;													/* currSym2				*/
		char;													/* currSym3				*/

		/* currFmt */
		boolean		noLeadZero, leadingZero;					/* leading unit zero	*/
		boolean		noTrailingZero, trailingZero;				/* trailing dec zero	*/
		boolean		paren, minusSign;							/* negative rep			*/
		boolean		trails, leads;								/* curr sym position	*/
		fill bit[4];											/* not used				*/
		byte		monDayYear, dayMonYear, yearMonDay,			/* dateOrder			*/
					monYearDay, dayYearMon, yearDayMon;

		/* shrtDateFmt */
		boolean		noCentury, century;							/* century incl			*/
		boolean		noMonthLeadZero, monthLeadZero;				/* mon lead zero		*/
		boolean		noDayLeadZero, dayLeadZero;					/* day lead zero		*/
		fill bit[5];											/* filler				*/
		char		slash = slashSymbol;						/* date sep				*/
		byte		twentyFourHour, twelveHourZeroCycle,		/* timeCycle			*/
					twelveHour = 255;

		/* timeFmt */
		boolean		noHoursLeadZero, hoursLeadZero;				/* hours lead zero		*/
		boolean		noMinutesLeadZero, minutesLeadZero;			/* min lead zero		*/
		boolean		noSecondsLeadZero, secondsLeadZero;			/* sec lead zero		*/
		fill bit[5];											/* filler				*/
		string[4];												/* mornStr				*/
		string[4];												/* eveStr				*/
		char;													/* timeSep				*/
		char;													/* time1Stuff			*/
		char;													/* time2Stuff			*/
		char;													/* time3Stuff			*/
		char;													/* time4Stuff			*/
		char;													/* time5Stuff			*/
		char;													/* time6Stuff			*/
		char;													/* time7Stuff			*/
		char;													/* time8Stuff			*/
		byte		standard, metric = 255;						/* metricSys			*/
		byte		Region;										/* INTL0 region			*/
		byte;													/* version				*/
};
/*----------------------------itl0 • International Formatting Information---------------*/
type 'itl0' as 'INTL' (0);
/*----------------------------INTL (1) • International Date/Time Information------------*/
type 'INTL' (1) {
		/* Day names */
		array [7] {
			pstring[15];										/* Sunday, Monday...	*/
		};

		/* Month names */
		array [12] {
			pstring[15];										/* January, February...	*/
		};

		byte		dayName, none=255;							/* suppressDay			*/
		byte		dayMonYear, monDayYear = 255;				/* longDate format		*/
		byte		noDayLeadZero, dayLeadZero = 255;			/* dayLeading0			*/
		byte;													/* abbrLen				*/
		string[4];												/* st0					*/
		string[4];												/* st1					*/
		string[4];												/* st2					*/
		string[4];												/* st3					*/
		string[4];												/* st4					*/
		byte		Region;										/* INTL1 region 		*/
		byte;													/* version				*/
		hex string	DefaultReturn = "\$4E\$75";					/* local routine - If
									  							   you have one, use
																   $$Resource to insert
																   code here.  Otherwise,
																   you must have a 68000
																   return instruction.
																   Use DefaultReturn.	*/
};
/*----------------------------itl1 • International Date/Time Information----------------*/
/* This is separated out because it is changed for 7.0 to be different than 'INTL' (1).	*/
/* The old INTL (1) format had a local routine field at the end. This was to be used	*/
/* for localized string sorting code. However, for the last 4 years, string sorting has	*/
/* been handled with the 'itl2' resource, and the local routine field has been ignored.	*/
/* In most 'itl1' resources, it just contains a single RTS instruction (hex $4E75).		*/
/* This field is now used to flag the 7.0 extensions. If it is $4E75, the old format is	*/
/* assumed. If it is $A89F, the new format is assumed: $A89F is unimplemented trap,		*/
/* which would never have occurred as the first instruction in a local routine. Old		*/
/* 'itl1' resources with a local routine will be handled correctly by the code, but can	*/
/* not be Rezzed or DeRezzed with this template. They should be updated to either have	*/
/* $4E75 in the local routine field, with nothing else following, or to have $A89F in	*/
/* the local routine filed, followed by extended data in the format given below. The	*/
/* version field was not used to mark this change because various current 'itl1'		*/
/* resources use very different version numbers, including 0, 1, and 128.				*/

type 'itl1' {
		/* Day names */
		array [7] {
			pstring[15];										/* Sunday, Monday...	*/
		};

		/* Month names */
		array [12] {
			pstring[15];										/* January, February...	*/
		};

		byte		dayName, none=255;							/* suppressDay			*/
		byte		dayMonYear, monDayYear = 255;				/* longDate format		*/
		byte		noDayLeadZero, dayLeadZero = 255;			/* dayLeading0			*/
		byte;													/* abbrLen				*/
		string[4];												/* st0					*/
		string[4];												/* st1					*/
		string[4];												/* st2					*/
		string[4];												/* st3					*/
		string[4];												/* st4					*/
		byte		Region;										/* region code	 		*/
		byte;													/* version				*/
		switch	{
			case oldFormat:
				key hex integer = $4E75;						/* old format key		*/
			case extFormat:
				key hex integer = $A89F;						/* extended format key	*/
				hex integer;									/* version				*/
				hex integer;									/* format				*/
				integer;										/* calendar code		*/
				unsigned longint = extraDays >> 3;							/* offset to extraDays table	*/
				unsigned longint = (endExtraDays - extraDays) >> 3;			/* length of extraDays table	*/
				unsigned longint = extraMonths >> 3;						/* offset to extraMonths table	*/
				unsigned longint = (endExtraMonths - extraMonths) >> 3;		/* length of extraMonths table	*/
				unsigned longint = abbrevDays >> 3;							/* offset to abbrevDays table	*/
				unsigned longint = (endAbbrevDays - abbrevDays) >> 3;		/* length of abbrevDays table	*/
				unsigned longint = abbrevMonths >> 3;						/* offset to abbrevMonths table	*/
				unsigned longint = (endAbbrevMonths - abbrevMonths) >> 3;	/* length of abbrevMonths table	*/
				unsigned longint = extraSeparators >> 3;					/* offset to extraSeparators table	*/	/*<10>*/
				unsigned longint = (endExtraSeparators - extraSeparators) >> 3;	/* len of extraSeparators table	*/	/*<10>*/
extraDays:
				integer = $$CountOf(extraDaysArray);			/* number of extra days	*/
				array extraDaysArray {							/* array of extra names		*/
					pstring;									/* extra day name string	*/
				};
				align word;																			/*<22>*/
endExtraDays:
extraMonths:
				integer = $$CountOf(extraMonthArray);			/* number of extra months	*/
				array extraMonthArray {							/* array of extra names		*/
					pstring;									/* extra month name string	*/
				};
				align word;																			/*<22>*/
endExtraMonths:
abbrevDays:
				integer = $$CountOf(abbrevDaysArray);			/* number of abbrev days	*/
				array abbrevDaysArray {							/* array of abbrev names	*/
					pstring;									/* abbrev day name string	*/
				};
				align word;																			/*<22>*/
endAbbrevDays:
abbrevMonths:
				integer = $$CountOf(abbrevMonthArray);			/* number of abbrev months	*/
				array abbrevMonthArray {						/* array of abbrev names	*/
					pstring;									/* abbrev month name string	*/
				};
				align word;																			/*<22>*/
endAbbrevMonths:
extraSeparators:
				integer = $$CountOf(extraSeparatorsArray);		/* number of extra separators	*/	/*<10>*/
				array extraSeparatorsArray {					/* array of separator strings	*/	/*<10>*/
					pstring;									/* separator string				*/	/*<10>*/
				};
				align word;																			/*<22>*/
endExtraSeparators:
		};
};
/*----------------------------itl2 • International String Comparison Package Hooks-----*/
/*
 * Note that this type assumes a particular ordering of code and tables, although
 * that order is not required in order for the resource to be used correctly by
 * the code.
 *
 * There is some ugly stuff at the end, because
 * 1. The itl2 resource has several different formats.
 * 2. The offset to the FindScriptTable is only present in one format: when length
 *    fields exist.
 * 3. Even in that format, the FindScriptTable itself is optional; if it is not
 *    present, the offset to it is 0.
 * 4. The optional FindScriptTable is preceded by the variable-length wrapTable.
 *    To determine the wrapTable length when DeRezzing, we need to use the offset
 *    to FindScriptTable if the offset exists and is nonzero. Otherwise, wrapTable
 *    extends to the end of the resource.
 * The single hex string at the end of the wrapTable is actually represented in
 * three different arrays whose dimensions are logical expressions. For a given
 * format, one of the arrays will have a dimension 1, and the others will have a
 * dimension 0.
 */

type 'itl2' {
		switch {
			case pre604:
				integer = initHook1 >> 3;							/* init hook offset			*/
				integer = fetchHook1 >> 3;							/* fetch hook offset		*/
				integer = vernierHook1 >> 3;						/* vernier hook offset		*/
				integer = projectHook1 >> 3;						/* project hook offset		*/
				bitstring[15] = rsvd1Hook1 >> 4;
				key boolean = 0;
				integer = rsvd2Hook1 >> 3;							/* rsvd2 hook offset		*/
	initHook1:
				hex string [(fetchHook1 - initHook1) >> 3];			/* initHook code			*/
	fetchHook1:
				hex string [(vernierHook1 - fetchHook1) >> 3];		/* fetchHook code			*/
	vernierHook1:
				hex string [(projectHook1 - vernierHook1) >> 3];	/* vernierHook code			*/
	projectHook1:
				hex string [(rsvd1Hook1 - projectHook1) >> 3];		/* projectHook code			*/
	rsvd1Hook1:
				hex string [(rsvd2Hook1 - rsvd1Hook1) >> 3];		/* rsvd1Hook code			*/
	rsvd2Hook1:
				hex string;											/* rsvd2Hook/exitHook code	*/
			case atLeast604:
				integer = initHook2 >> 3;							/* init hook offset			*/
				integer = fetchHook2 >> 3;							/* fetch hook offset		*/
				integer = vernierHook2 >> 3;						/* vernier hook offset		*/
				integer = projectHook2 >> 3;						/* project hook offset		*/
				bitstring[15] = -1;
				key boolean = 1;
				integer = rsvd2Hook2 >> 3;							/* rsvd2 hook offset		*/
				integer = typeList >> 3;							/* TypeList offset			*/
				integer = classArray >> 3;							/* ClassArray offset		*/
				integer = upperList >> 3;							/* UpperList offset			*/
				integer = lowerList >> 3;							/* LowerList offset			*/
				integer = upperNoMarkList >> 3;						/* UpperNoMarkList offset	*/
				integer = wordTable >> 3;							/* WordTable offset			*/
				integer = wrapTable >> 3;							/* WrapTable offset			*/
				integer = noMarkList >> 3;							/* NoMarkList offset		*/
				unsigned hex integer;								/* version number			*/
	formatCode:
				switch {
					case noLengthFields:
						key integer = 0;							/* format code				*/
	extraHdr:
						hex string [(initHook2 - extraHdr) >> 3];	/* extra header, if any		*/
					case haveLengthFields:
						key integer = 1;							/* format code				*/
						wide array [14] {
							integer;								/* length fields			*/
						};
	findScriptTableOffset:
						integer = findScriptTable[1,1] >> 3;		/* findScriptTable offset	*/
						integer;									/* findScriptTable length	*/
				};
	initHook2:
				hex string [(fetchHook2 - initHook2) >> 3];			/* initHook code 			*/
	fetchHook2:
				hex string [(vernierHook2 - fetchHook2) >> 3];		/* fetchHook code 			*/
	vernierHook2:
				hex string [(projectHook2 - vernierHook2) >> 3];	/* vernierHook code 		*/
	projectHook2:
				hex string [(rsvd2Hook2 - projectHook2) >> 3];		/* projectHook code 		*/
	rsvd2Hook2:
				hex string [(classArray - rsvd2Hook2) >> 3];		/* rsvd2Hook/exitHook code	*/													/* code */
	classArray:
				hex string [(typeList - classArray) >> 3];			/* classArray table			*/
	typeList:
				hex string [(upperList - typeList) >> 3];			/* typeList table			*/
	upperList:
				hex string [(lowerList - upperList) >> 3];			/* upperList table			*/
	lowerList:
				hex string [(upperNoMarkList - lowerList) >> 3];	/* lowerList table			*/
	upperNoMarkList:
				hex string [(noMarkList - upperNoMarkList) >> 3];	/* upperNoMarkList table	*/
	noMarkList:
				hex string [(wordTable - noMarkList) >> 3];			/* noMarkList table			*/
	wordTable:
				switch {
					case tupleFormat:
						key boolean = 0;
						hex bitstring[7];							/* class for null			*/
						hex string [255];							/* class for other chars	*/
						integer = $$CountOf(WordTuples) - 1;
						wide array WordTuples {						/* packed tuple defns		*/
							hex unsigned integer;
						};
					case stateFormat:
						key boolean = 1;
						bitstring[15];								/* flags & format			*/
						unsigned hex integer;						/* version					*/
						integer = (wordClass - wordTable) >> 3;		/* offset to class table	*/
						integer = (wordAux - wordTable) >> 3;		/* offset to aux class tbl	*/
						integer = (wordBackwd - wordTable) >> 3;	/* offset to back state tbl	*/
						integer = (wordForwd - wordTable) >> 3;		/* offset to forw state tbl	*/
						integer;									/* doBackupMin				*/
	wordLength:
						integer;									/* length					*/
	wordClass:
						hex string [(wordAux - wordClass) >> 3];	/* class table				*/
	wordAux:
						hex string [(wordBackwd - wordAux) >> 3];	/* aux class table			*/
	wordBackwd:
						hex string [(wordForwd - wordBackwd) >> 3];	/* state table for backup	*/
	wordForwd:
						hex string [$$Word(wordLength) - ((wordForwd - wordTable) >> 3)]; /* tbl */
				};
	endWordTable:
				hex string [(wrapTable - endWordTable) >> 3];		/* extra stuff, if any		*/
	wrapTable:
				switch {
					case tupleFormat:
						key boolean = 0;
						hex bitstring[7];							/* class for null			*/
						hex string [255];							/* class for other chars	*/
						integer = $$CountOf(WrapTuples) - 1;
						wide array WrapTuples {						/* packed tuple defns		*/
							hex unsigned integer;
						};
					case stateFormat:
						key boolean = 1;
						bitstring[15];								/* flags & format			*/
						unsigned hex integer;						/* version					*/
						integer = (wrapClass - wrapTable) >> 3;		/* offset to class table	*/
						integer = (wrapAux - wrapTable) >> 3;		/* offset to aux class tbl	*/
						integer = (wrapBackwd - wrapTable) >> 3;	/* offset to back state tbl	*/
						integer = (wrapForwd - wrapTable) >> 3;		/* offset to forw state tbl	*/
						integer;									/* doBackupMin				*/
	wrapLength:
						integer;									/* length					*/
	wrapClass:
						hex string [(wrapAux - wrapClass) >> 3];	/* class table				*/
	wrapAux:
						hex string [(wrapBackwd - wrapAux) >> 3];	/* aux class table			*/
	wrapBackwd:
						hex string [(wrapForwd - wrapBackwd) >> 3];	/* state table for backup	*/
	wrapForwd:
						hex string [$$Word(wrapLength) - ((wrapForwd - wrapTable) >> 3)]; /* tbl */
				};
	endWrapTable:
				array [$$Word(formatCode) == 0] {
					hex string;										/* extra stuff, if any		*/
				};
				array [$$Word(formatCode) == 1] {
					array [$$Word(findScriptTableOffset) == 0] {
						hex string;									/* extra stuff, if any		*/
					};
					array [$$Word(findScriptTableOffset) != 0] {
						hex string [(findScriptTable[1,1] - endWrapTable) >> 3]; /* xtra stuff?	*/
					};
				};
				array [$$Word(formatCode) == 1] {
					array [$$Word(findScriptTableOffset) != 0] {
	findScriptTable:
						hex string;									/* findScriptTable			*/
					};
				};
		};
};
/*----------------------------itl4 • International Tokenizer----------------------------*/
type 'itl4' {
		unsigned hex integer;										/* flags					*/
		literal longint = 'itl4';									/* resource type			*/
		integer;													/* resource ID				*/
		unsigned hex integer;										/* version number			*/
	formatCode:
		switch {
			case noLengthFields:
				key integer = 0;									/* format code				*/
				integer = 0;										/* reserved					*/
				longint = 0;										/* reserved					*/
				integer = 8;										/* # of table entries		*/
				unsigned longint = mapCharTable >> 3;				/* MapChar offset			*/
				unsigned longint = stringCopyCode >> 3;				/* stringCopy offset		*/
				unsigned longint = extendFetchCode >> 3;			/* extendFetch offset		*/
				unsigned longint = unTokenTable >> 3;				/* unToken offset			*/
				unsigned longint = defaultPartsTable >> 3;			/* defaultParts offset		*/
				unsigned longint = whiteSpaceList[1] >> 3;			/* whiteSpaceList offset	*/
				unsigned longint = 0;								/* reserved offset			*/
				unsigned longint = 0;								/* reserved offset			*/
			case haveLengthFields:
				key integer = 1;									/* format code				*/
				integer = 0;										/* reserved					*/
				longint = 0;										/* reserved					*/
				integer = 8;										/* # of table entries		*/
				unsigned longint = mapCharTable >> 3;				/* MapChar offset			*/
				unsigned longint = stringCopyCode >> 3;				/* stringCopy offset		*/
				unsigned longint = extendFetchCode >> 3;			/* extendFetch offset		*/
				unsigned longint = unTokenTable >> 3;				/* unToken offset			*/
				unsigned longint = defaultPartsTable >> 3;			/* defaultPartsTable offset	*/
				unsigned longint = whiteSpaceList[1] >> 3;			/* whiteSpaceList offset	*/
				unsigned longint = 0;								/* reserved offset			*/
				unsigned longint = 0;								/* reserved offset			*/
				integer;											/* MapChar length			*/
				integer;											/* StringCopy length		*/
				integer;											/* extendFetch length		*/
				integer;											/* unToken length			*/
				integer;											/* defaultPartsTable length	*/
				integer;											/* whiteSpaceList length	*/
				integer = 0;										/* reserved length			*/
				integer = 0;										/* reserved length			*/
		};


		unsigned longint;											/* extendFetch abort offset	*/
		longint = $$CountOf(MapChar);
	mapCharTable:
		array MapChar {
			byte;
		};

	extendFetchCode:
		hex string [(stringCopyCode - extendFetchCode) >> 3];		/* extendFetch code			*/
	stringCopyCode:
		hex string [(unTokenTable - stringCopyCode) >> 3];			/* stringCopy code			*/
	unTokenTable:
		integer = (defaultPartsTable - unTokenTable) >> 3;			/* unToken table size		*/
	unTokenCount:
		integer = $$CountOf(unTokenStringOffsets) - 1;
		array unTokenStringOffsets {
			integer;												/* offset to token strings	*/
		};
		array [$$Word(unTokenCount) + 1] {
			pstring;												/* token strings			*/
			align word;
		};

	defaultPartsTable:
		integer;													/* version number			*/
		wide array [31] {
			unsigned byte;
			char;
		};
		integer;													/* size						*/
		wide array [10] {
			unsigned byte;
			char;
		};
		integer;													/* size						*/
		wide array [10] {
			unsigned byte;
			char;
		};
		integer;													/* size						*/
		wide array [10] {
			unsigned byte;
			char;
		};
		integer;													/* size						*/
		wide array [10] {
			unsigned byte;
			char;
		};
		hex string [20] = "";

		array [$$BitField(formatCode,30*8,32) != 0] {
	whiteSpaceList:
			integer = (whiteSpaceListEnd[1] - whiteSpaceList[1]) >> 3; /* whiteSpaceList size	*/
	whiteSpaceListCount:
			integer = $$CountOf(whiteSpaceStringOffsets);
			array whiteSpaceStringOffsets {
				integer;											/* offset to string			*/
			};
			array [$$Word(whiteSpaceListCount[1])] {
				pstring;											/* whitespace string		*/
				align word;
			};
	whiteSpaceListEnd:
		};
};
/*----------------------------itlb • International Script Bundle------------------------*/
type 'itlb' {
		integer;												/* itl0 id number		*/				/*<6>*/
		integer;												/* itl1 id number		*/				/*<6>*/
		integer;												/* itl2 id number		*/				/*<6>*/
		unsigned hex integer;									/* script flags - see
																   smScriptFlags info
																   in ScriptEqu.a		*/
		integer;												/* itl4 id number		*/				/*<6>*/
		integer;												/* id number of optional itl5, or 0	*/	/*<13>*/
		unsigned integer;										/* Script language		*/
		unsigned integer;										/* high byte - number
																   representation code,
																   low byte - date
																   representation code	*/
		integer;												/* KCHR id number		*/				/*<6>*/
		integer;												/* id no. of SICN or kcs#,kcs4,kcs8	*/	/*<6>*/
		unsigned longint;										/* size of script's local record	*/	/*<6>*/
		integer;												/* default monospace FOND ID		*/	/*<6>*/
		unsigned integer;										/* default monospace font size		*/	/*<6>*/
		integer;												/* preferred FOND ID				*/	/*<6>*/
		unsigned integer;										/* preferred font size				*/	/*<6>*/
		integer;												/* default small FOND ID			*/	/*<6>*/
		unsigned integer;										/* default small font size			*/	/*<6>*/
		integer;												/* default system FOND ID			*/	/*<6>*/
		unsigned integer;										/* default system font size			*/	/*<6>*/
		integer;												/* default application FOND ID		*/	/*<6>*/
		unsigned integer;										/* default application font size	*/	/*<6>*/
		integer;												/* default Help Mgr FOND ID			*/	/*<6>*/
		unsigned integer;										/* default Help Mgr font size		*/	/*<6>*/
		hex byte;												/* valid styles for script				/*<10>*/
		hex byte;												/* alias style for script			*/	/*<10>*/
};
/*----------------------------itlc • International Configuration------------------------*/
type 'itlc' {
		unsigned integer;										/* system script code	*/
		unsigned integer;										/* keyboard cache size	*/
		byte			noFontForce, fontForce = 255;			/* font force flag		*/
		byte			noIntlForce, intlForce = 255;			/* intl force flag		*/
		byte			noOldKeyboard, oldKeyboard = 255;		/* old keyboard			*/
		unsigned hex byte;										/* general flags - see
																   smGenFlags info in
																   ScriptEqu.a			*/
		integer;												/* script icon offset	(not used in Sys 7 ) */
		byte			rightOffset, leftOffset = 255;			/* menu side for offset	(not used in Sys 7 ) */
		byte;													/* icon data (rsvd)		(not used in Sys 7 ) */
		unsigned integer Region;								/* pref. region code	*/
		
		/* system flags */
		boolean			directionLeftRight, directionRightLeft;	/* to set TESysJust		*/	/*<23>*/
		fill bit[15];											/* reserved				*/	/*<23>*/
		
		/* for future expansion */
		hex string [32];										/* reserved				*/	/*<23>*/
};
/*----------------------------itlk • Keyboard-dependent Remapping-----------------------*/
type 'itlk' {
		integer = $$CountOf(RemapItemArray);
		wide array RemapItemArray {
			integer;											/* keyboard type		*/
			hex byte;											/* old modifier bits	*/
			byte;												/* old key code			*/
			hex byte;											/* modifier bits mask	*/
			byte;												/* key code mask		*/
			hex byte;											/* new modifier bits	*/
			byte;												/* new key code			*/
		};
};
/*----------------------------itlm • Multiscript mapping/sorting-----------------------*/
type 'itlm' {
		unsigned hex integer;									/* version number					*/
		unsigned hex integer;									/* format code						*/
		unsigned integer = 3;									/* number of offset/length pairs	*/
		unsigned longint = scriptData >> 3;						/* offset to scriptData table		*/
		unsigned longint = (endScriptData - scriptData) >> 3;	/* length of scriptData table		*/
		unsigned longint = langData >> 3;						/* offset to langData table			*/
		unsigned longint = (endLangData - langData) >> 3;		/* length of langData table			*/
		unsigned longint = regionData >> 3;						/* offset to regionData table		*/
		unsigned longint = (endRegionData - regionData) >> 3;	/* length of regionData table		*/

scriptData:
		integer Script;								/* max script code for script->lang mapping		*/
		integer Language;							/* default lang code for scripts not in table	*/
		integer = $$CountOf(scriptArray);			/* number of entries in table					*/
		array scriptArray {							/* entries are ordered by script sort order		*/
			integer Script;							/* script code									*/
			integer Language;						/* default language code for script				*/
		};
endScriptData:

langData:
		integer Language;							/* max lang code for lang->script mapping		*/
		integer Script;								/* default script code for langs not in table	*/
		integer = $$CountOf(langArray);				/* number of entries in table					*/
		array langArray {							/* entries are ordered by lang sort order		*/
			integer Language;						/* language code								*/
			integer Script;							/* code	of script to which this lang belongs	*/
		};
endLangData:

regionData:
		integer Region;								/* max region code for region->lang mapping		*/
		integer Language;							/* default lang code for regions not in table	*/
		integer = $$CountOf(regionArray);			/* number of entries in table					*/
		array regionArray {							/* entries are ordered by region sort order		*/
			integer Region;							/* region code									*/
			integer Language;						/* parent language code for region				*/
		};
endRegionData:
};

/*----------------------------KCAP • Physical Layout of Keyboard------------------------*/
type 'KCAP' {
		rect;													/* boundsRect			*/
		rect;													/* textRect				*/
		integer = $$CountOf(MainArray);
		array MainArray {
			integer = $$CountOf(ShapeArray) - 1;
			wide array ShapeArray {
				point;											/* shapePoint			*/
			};
			integer = $$CountOf(KeyArray) - 1;
			wide array KeyArray {
				byte;											/* mask					*/
				boolean				or, and;
				bitstring[7];									/* keyCode				*/
				integer;										/* dv					*/
				integer;										/* dh					*/
			};
		};
};
/*----------------------------KCHR • ASCII Mapping (software)---------------------------*/
type 'KCHR' {
		integer;												/* Version				*/
		wide array [$100] {										/* Indexes				*/
			byte;
		};
		integer = $$CountOf(TableArray);
		array TableArray {
			wide array [$80] {									/* ASCII characters		*/
				char;
			};
		};
		integer = $$CountOf(DeadArray);
		array DeadArray {
			byte;												/* Table number			*/
			byte;												/* Virtual keycode		*/
			integer = $$CountOf(CompletorArray);
			wide array CompletorArray {
				char;											/* Completor char		*/
				char;											/* Substituting char	*/
			};
			char;												/* No match char		*/
			char;												/* 16-bits for the times
																   when 8 isn't enough	*/
		};
};
/*----------------------------KMAP • Keyboard Mapping (hardware)------------------------*/
type 'KMAP' {
		integer;												/* ID					*/
		integer;												/* Version				*/
		wide array [$80] {										/* Raw to virtual		*/
			byte;												/*  keycode map			*/
		};
		integer = $$CountOf(ExceptionArray);
		wide array ExceptionArray {
			byte;												/* Raw keycode			*/
			boolean			noXor, Xor;
			fill bit[3];
			bitstring[4];										/* ADB op				*/
			pstring;
		};
};
/*----------------------------KSWP • Keyboard Swapping----------------------------------*/
type 'KSWP' {
		/* The expression below that calculates the number of elements in the
		   array is complicated because of the way that $$ResourceSize works.
		   $$ResourceSize returns the size of the resource.  When derez'ing a
		   resource, the size of the resource is known from the start.  When
		   rez'ing a resource, however, the size starts out at zero and is
		   incremented each time a field is appended to the resource data.  In
		   other words, while rez'ing, $$ResourceSize rarely returns the final
		   size of the resource.  When rez'ing a KSWP, the array size expression
		   is not evaluated until all of the array elements have been parsed.
		   Since each array element is 4 bytes long (if you add up all the fields),
		   the number of array elements is the size of the resource at that point
		   divided by four.  Since the preprocessor value of "DeRez" is zero when
		   Rez'ing, the expression is equivalent to $$ResourceSize / 4.  When
		   derez'ing a KSWP, the value of $$ResourceSize is constant: always the
		   total size of the resource, in bytes.  Since the resource contains 4
		   bytes of fill at the end (which happens to be the size of an array
		   element), we have to take that in consideration when calculating the
		   size of the array.  Note that the preprocessor value of "DeRez" is one,
		   when derez'ing.
		*/
		wide array [$$ResourceSize / 4 - DeRez]{
			hex integer		Roman, Japanese, Chinese, Korean,	/* script code or verb	*/
							Arabic, Hebrew, Greek,
							Rotate = -1, System = -2,
							Alternate = -3, RotateKybd = -4,	/* <20> */
							ToggleDirection = -9,
							SetDirLeftRight = -15,
							SetDirRightLeft = -16,
							RomanIfOthers = -17;				/* <25> */
			unsigned byte;										/* virtual key code		*/
			/* Modifiers */
			fill bit;											/* rControlOn,rControlOff*/
			fill bit;											/* rOptionOn,rOptionOff	*/
			fill bit;											/* rShiftOn,rShiftOff	*/
			boolean		controlOff, controlOn;
			boolean		optionOff, optionOn;
			fill bit;											/* capsLockOn,capsLockOff*/
			boolean		shiftOff, shiftOn;
			boolean		commandOff, commandOn;
		};
		fill long;
};
/*----------------------------mach • cdev filtering-------------------------------------*/
type 'mach' {
		unsigned hex integer;												/* Softmask	*/
		unsigned hex integer;												/* Hardmask	*/
};
/*----------------------------mcky • Mouse Tracking-------------------------------------*/
type 'mcky' {
		array [8] {
			unsigned byte;
		};
};
/*----------------------------mppc • MPP Configuration Resource-------------------------*/
type 'mppc' {
		unsigned hex longint;									/* Info passed to drvr	*/
		byte;													/* Override version #	*/
		fill byte;												/* Reserved				*/
};
/*----------------------------NFNT • Font Description-----------------------------------*/
type 'NFNT' as 'FONT';
/*----------------------------nrct • Rectangle List-------------------------------------*/
type 'nrct' {
		integer = $$CountOf(RectArray);							/* Number of rectangles	*/
		array RectArray {
			rect;
		};
};

/*----------------------------ROv# • ROM Resource Override------------------------------*/
type 'ROv#' {
		unsigned hex integer;									/* Version # of ROM		*/
		integer = $$CountOf(typeList) - 1;						/* Number of resources	*/
		wide array typeList {
			literal longint;									/* Resource type		*/
			integer;											/* Resource id			*/
		};
};
/*----------------------------scrn • Screen Configuration-------------------------------*/
type 'scrn' {
		integer = $$CountOf(Device);							/* Number of displays	*/
		wide array Device {
			unsigned hex integer;								/* sRsrc Type			*/
			integer;											/* Slot number			*/
			unsigned hex longint;								/* dCtlDevBase			*/
			integer;											/* sRsrcID for mode		*/
			integer = $77FE;									/* Flag mask			*/
			Boolean			inactive, active;					/* Device active flag	*/
			fill bit[3]; 										/* reserved 			*/
			Boolean			auxillaryScreen, mainScreen;		/* Main screen flag		*/
			unsigned bitstring[10] = 0;							/* reserved				*/
			Boolean			monochrome, color;					/* Device type			*/
			integer;											/* Rsrc ID of 'clut'	*/
			integer;											/* Rsrc ID of 'gama'	*/
			Rect;												/* Device's global rect	*/
			integer = $$CountOf(ControlCalls);					/* # of control calls	*/
			wide array ControlCalls {
				integer;										/* csCode for this call	*/
				wstring;										/* param block data		*/
				align word;

			};
		};
};
/*----------------------------snd  • Sound----------------------------------------------*/
type 'snd ' {
		switch {
			case FormatOne:
				key unsigned integer = $0001;
				unsigned integer = $$CountOf(Synthesizers);
				wide array Synthesizers {
					/* Resource ID of synthesizer/modifer */
					integer		squareWaveSynth		= $0001,
								waveTableSynth		= $0003,
								sampledSynth		= $0005;
					longint;									/* init parameter		*/
				};

			case FormatTwo:
				key unsigned integer = $0002;
				integer		free = 0, keepInMemory = 256+1;		/* Space for refe count	*/
		};
		unsigned integer = $$CountOf(SoundCmnds);
		wide array SoundCmnds {
			boolean		noData, hasData;
			switch {
				case nullCmd:
					key bitstring[15] = 0;
					fill word;									/* Param 1 = nil		*/
					fill long;									/* Param 2 = nil		*/
				case quietCmd:
					key bitstring[15] = 3;
					fill word;									/* Param 1 = nil		*/
					fill long;									/* Param 2 = nil		*/
				case flushCmd:
					key bitstring[15] = 4;
					fill word;									/* Param 1 = nil		*/
					fill long;									/* Param 2 = nil		*/
				case waitCmd:
					key bitstring[15] = 10;
					integer		oneSecond = 2000;				/* Duration				*/
					fill long;									/* Param 2 = nil		*/
				case pauseCmd:
					key bitstring[15] = 11;
					fill word;									/* Param 1 = nil		*/
					fill long;									/* Param 2 = nil		*/
				case resumeCmd:
					key bitstring[15] = 12;
					fill word;									/* Param 1 = nil		*/
					fill long;									/* Param 2 = nil		*/
				case callBackCmd:
					key bitstring[15] = 13;
					integer;									/* User-defined			*/
					longint;									/* User-defined			*/
				case syncCmd:
					key bitstring[15] = 14;
					integer;									/* Count				*/
					longint;									/* Identifier			*/
				case emptyCmd:
					key bitstring[15] = 15;
					fill word;									/* Param 1 = nil		*/
					fill long;									/* Param 2 = nil		*/
				case freqDurationCmd:
					key bitstring[15] = 40;
					integer		oneSecond = 2000;				/* Duration				*/
					longint;									/* frequency			*/
				case restCmd:
					key bitstring[15] = 41;
					integer		oneSecond = 2000;				/* Duration				*/
					fill long;									/* Param 2 = nil		*/
				case freqCmd:
					key bitstring[15] = 42;
					fill word;									/* Param 1 = nil		*/
					longint;									/* Frequency			*/
				case ampCmd:
					key bitstring[15] = 43;
					integer;									/* Amplitude			*/
					fill long;									/* Param 2				*/
				case timbreCmd:
					key bitstring[15] = 44;
					integer		sineWave, squareWave = 255;		/* Timbre				*/
					fill long;									/* Param 2				*/
				case waveTableCmd:
					key bitstring[15] = 60;
					unsigned integer;							/* Length				*/
					longint;									/* Pointer to table		*/
				case phaseCmd:
					key bitstring[15] = 61;
					integer;									/* Shift				*/
					longint;									/* chanPtr				*/
				case soundCmd:
					key bitstring[15] = 80;
					fill word;									/* Param 1 = nil		*/
					longint;									/* Pointer to sound		*/
				case bufferCmd:
					key bitstring[15] = 81;
					fill word;									/* Param 1 = nil		*/
					longint;									/* Pointer to buffer	*/
				case rateCmd:
					key bitstring[15] = 82;
					fill word;									/* Param 1 = nil		*/
					longint;									/* Rate					*/
			};
		};
		array DataTables {
	DataTable:
			fill long;											/* Pointer to data		*/
	SampleCnt:
			unsigned longint;									/* # of sound samples	*/
			unsigned hex longint
					Rate22K = $56EE8BA3;						/* Sampling rate		*/
			unsigned longint;									/* Start of loop		*/
			unsigned longint;									/* End of loop			*/
			hex byte;											/* encode (header type)	*/
			hex byte;											/* baseFrequency		*/
			hex string [$$Long(SampleCnt[$$ArrayIndex(DataTables)])];
		};
};
/*----------------------------vers • Version--------------------------------------------*/
type 'vers' {
		hex byte;												/* Major revision in BCD*/
		hex byte;												/* Minor vevision in BCD*/
		hex byte	development = 0x20,							/* Release stage		*/
					alpha = 0x40,
					beta = 0x60,
					final = 0x80, /* or */ release = 0x80;
		hex byte;												/* Non-final release #	*/
		integer		Region;										/* Region code			*/
		pstring;												/* Short version number	*/
		pstring;												/* Long version number	*/
};
/*--------------------------------------------------------------------------------------*/

/* FRSV and resf • reserved fonts */

	type 'FRSV' {
		integer = $$CountOf(ReservedFontArray);
		wide array ReservedFontArray {
			unsigned bitstring[9]	Chicago = 0, Geneva = 3, Monaco = 4;	// font family
			unsigned bitstring[7];											// font size
		};
	};

	type 'resf' {
		integer = $$CountOf(FamilyArray);
		array FamilyArray {
			pstring;
			align word;
			integer = $$CountOf(FontRecord);
			array FontRecord {
				integer;						// point size
				integer plain;					// style
			};
		};
	};

/* fld# • list of folder names for Folder Mgr */

	type 'fld#' {
		array {
			literal		longint;				// folder type
			integer		inSystemFolder = 0;		// version
			fill byte;							// high byte of data length
			pstring;							// folder name
			align word;
		};
	};

/* mitq • default queue sizes for MakeITable */

	type 'mitq' {				// default MakeITable queue sizes
		wide array [3] {
			unsigned longint;	// queue size for 3, 4, and 5 bit inverse tables
		};
	};

/* ppcc • PPC Browser Configuration Resource */

	type 'ppcc' {
		unsigned byte;	// NBP lookup interval
		unsigned byte;	// NBP lookup count
		integer;		// NBP maximum lives an entry has before deletion
		integer;		// NBP maximum number of entities
		integer;		// NBP idle time in ticks between lookups
		integer;		// PPC maximum number of ports
		integer;		// PPC idle time in ticks between list ports
	};

/*--------------------------------------------------------------------------------------*/

#endif __SYSTYPES_R__

