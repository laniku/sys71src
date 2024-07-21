/*
	File:		Types.r

	Contains:	Type Declarations for Rez and DeRez

	Copyright:	© 1986-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM6>	 9/22/93	JDR		corrected misspelling of componentHasMultiplePlatforms
	   <SM5>	  9/1/93	JDR		update from Reality, added 'kind' and 'open', new version of
									'thng',
	   <SM4>	12-02-92	jmp		Upated the color-oriented resource definitions from ETO #8.
		<23>	 9/03/92	JDR		Added the 'thng' resource type for the Component Manager.
		<22>	 6/24/92	DCL		Changed #ifndef __TYPES.R__ to __TYPES_R__  at the request of
									the MPW team (3.2.3 rez broke on the periods)
		<21>	 11/8/91	JL		Took out aedt resource template because it's obsolete. As per Ed
									Lai.
		<20>	  1/7/91	JDR		(dba) Renaming old Switcher constants used in the SIZE resource
									to Reserved.
		<19>	12/16/90	KIP		<csd> If SystemSevenOrLater is undefined, define it to be zero.
		<18>	12/14/90	dba		<JDR> change SystemSevenOrBetter to SystemSevenOrLater
		<17>	 11/7/90	JNG		Change popupMenuCDEFproc to a #define <kaz>
		<16>	 10/24/90	JL		New MPW 3.2ß.  Also added movableDBoxProc to DLOG and WIND.
		<15>	 9/16/90	VL		Replaced old-style 'wctb' and 'cctb' with 7.0 extended ones.
		<14>	 9/15/90	PWD		Renamed popupUseCQD to popupReserved. <kaz> <crz>
		<13>	 8/31/90	JT		Added a bit in the MultiFinder SIZE resource that determines
									whether the inline text services are automatically used when the
									application uses TextEdit.
		<12>	 7/17/90	PKE		Deleted ‘kscn’ type (see <1.2>), since it is now superseded by
									keyboard icon suite (kcs#, etc. - see <8>).
		<11>	 6/21/90	DC		Put the align word in DLOG's and WIND's into the IF
									systemsevenorbetter.  Protected Pict definition with __PICT.R__
		<10>	  6/8/90	DC		Handled the case when SystemSevenOrBetter is not defined
		 <9>	  6/7/90	DC		Modified ALRT, DLOG and WIND templates to allow
									auto-positioning.
		 <8>	 5/12/90	SMB		Added new keyboard small icon types (KCN#, kcs#, kcl4, kcl8,
									kcs4, kcs8) for the Keyboard Menu since script systems' IDs for
									small icons (SICNs) can collide with applications IDs for SICNs
									- apps can use >= 128 and script systems' IDs can be anything >=
									0!
		 <7>	 3/22/90	RLC		Modify helpItem definition in 'DITL' type.
		 <6>	 3/20/90	ngk		Fixed comments
		 <5>	 3/20/90	ngk		New bits for SIZE type definition
		 <4>	 3/16/90	BBH		added constants for popupCDEF in the CNTL area
		 <3>	  3/5/90	csd		added type definitions for icl8, icl4, ics8, and ics4.
		<2.2>	01/12/90	JAL		added 'acur' type
		<2.1>	02/28/90	JAL		added dflg, qrsc, wstr, ppt#, ics#, and RECT types
		 <2>	12/19/89	JSM		Add Database Access Manager types.
	   <1.5>	11/20/89	RLC		Add in constants to HelpItem in 'DITL'.
	   <1.4>	11/20/89	RLC		Change the 'DITL' resource type to include the HelpItem type.
	   <1.3>	 10/3/89	dba		added 'ics#' template
	   <1.2>	 9/18/89	PKE		Added type 'kscn' (keyboard/script small icon) as 'SICN'.
	   <1.1>	 8/30/89	dba		improved Color QuickDraw-related templates so that fields are
									automatically filled in for values that can’t change in today’s
									version of CQD; this makes these resource definitions much
									easier to read; added #defines for ALRT stages and RGB colors;
									added a trial definition for ppt# that Rez can’t really handle
									yet
	   <1.0>	 8/21/89	CCH		Checking in from MPW 3.0 RIncludes.

	06/21/90	- JAL:  Added eppc definiton
	06/20/90	- JAL:  Added aedt definiton
	05/22/90	- JAL:  Changed color resources without PixMapRowBytes definiton
						which wouldn't work with DeRez
	04/13/90	- JAL:  Added acceptAppDiedEvents and ignoreAppDiedEvents synonym to
						the new SIZE resource for compatibility.
	04/10/90	- JAL:  Added old MPW 3.1 templates for derez compatibility
						and added synonyms for the new SIZE resource for compatibility.
	11/20/89	- RLC:  Add in constants to HelpItem in 'DITL'.
	11/20/89	- RLC:  Change the 'DITL' resource type to include the HelpItem
						type.
	10/03/89	- dba:  added 'ics#' template
	09/18/89	- PKE:  Added type 'kscn' (keyboard/script small icon) as 'SICN'.
	08/30/89	- dba: improved Color QuickDraw-related templates so that fields are automatically
						filled in for values that can’t change in today’s version of CQD; this makes these
						resource definitions much easier to read; added #defines for ALRT stages and RGB colors;
						added a trial definition for ppt# that Rez can’t really handle yet
	08/21/89	- CCH: Checking in from MPW 3.0 RIncludes.

	03/20/89	- THT: added #ifndef __TYPES.R__
	10/24/88	- THT: added is32BitCompatible to SIZE and changed the bitstring
					   of unused bits into separate booleans so next time
					   we define a new flag, we won't break exisiting SIZE
					   resources.
	06/09/88	- THT: added onlyBackground and getFrontClicks bits to SIZE.
	12/03/87	- THT: made length of PICT unsigned.
	12/02/87	- THT: changed SIZE resource so that it supports Switcher
					   and MultiFinder.
	10/12/87	- THT: changed SIZE resource to support new
					   MultiFinder flags.  It no longer
					   supports Switcher.
	08/14/87	- THT: changed 'cicn', 'ppat', 'crsr' to use labels.
*/

#ifndef __TYPES_R__
#define __TYPES_R__

#ifndef SystemSevenOrBetter
#define SystemSevenOrBetter 0
#endif

#ifndef SystemSevenOrLater					/* <19> KIP - Define to 0 if it is not defined */
#define SystemSevenOrLater 0
#endif


/*--------------------------------------------------------------------------------------*/

#define	PixMapHeight	( $$BitField(Bounds, 32, 16) /* bottom */			\
						- $$BitField(Bounds, 0, 16) /* top */ )
#define	PixMapWidth		( $$BitField(Bounds, 48, 16) /* right */			\
						- $$BitField(Bounds, 16, 16) /* left */ )
#define	PixMapBounds	integer = $$BitField(Bounds, 0, 16) /* top */;		\
						integer = $$BitField(Bounds, 16, 16) /* left */;	\
						integer = $$BitField(Bounds, 32, 16) /* bottom */;	\
						integer = $$BitField(Bounds, 48, 16) /* right */
#define	PixMapRowBytes	(((PixMapWidth * $$Word(PixelSize) + 15) / 16) * 2)
#define	BitMapRowBytes	(((PixMapWidth + 15) / 16) * 2)

#define	PixMapHeightIndexed		( $$BitField(Bounds[$$ArrayIndex(PixPatArray)], 32, 16) /* bottom */			\
								- $$BitField(Bounds[$$ArrayIndex(PixPatArray)], 0, 16) /* top */ )
#define	PixMapWidthIndexed		( $$BitField(Bounds[$$ArrayIndex(PixPatArray)], 48, 16) /* right */			\
								- $$BitField(Bounds[$$ArrayIndex(PixPatArray)], 16, 16) /* left */ )
#define	PixMapRowBytesIndexed	(((PixMapWidthIndexed * $$Word(PixelSize[$$ArrayIndex(PixPatArray)]) + 15) / 16) * 2)


/*-------------------------------------Equates------------------------------------------*/
/*		The following are used to set styles, simply add for desired style.
*/
#define	bold			1
#define italic			2
#define underline		4
#define outline 		8
#define shadow			16
#define condense		32
#define extend			64

/*----------------------------acur • Cursor Pointers -----------------------------------*/
type 'acur' {
       integer = $$CountOf(CursIdArray); /* Nbr of cursors                 */
       fill word;                        /* Next frame to show             */
       array CursIdArray {
           integer;                      /* 'CURS' resource id for a frame */
           fill word;                    /* Pad word to make longint       */
       };
};
#ifdef oldTemp
/*--------------------------actb • Alert Color old Lookup Table--------------------------*/
	type 'actb' {
			unsigned hex longint = 0;								/* ctSeed				*/
			integer = 0;											/* ctFlags				*/
			integer = $$Countof(ColorSpec) - 1;						/* ctSize				*/
			wide array ColorSpec {
					integer		wContentColor,						/* value				*/
								wFrameColor,
								wTextColor,
								wHiliteColor,
								wTitleBarColor,
								wHiliteLight,
								wHiliteDark,
								wTitleBarLight,
								wTitleBarDark,
								wDialogLight,
								wDialogDark,
								wTingeLight,
								wTingeDark;
					unsigned integer;								/* RGB:	red				*/
					unsigned integer;								/*		green			*/
					unsigned integer;								/*		blue			*/
			};
	};
#else
/*----------------------------actb • Alert Color Lookup Table----------------------------*/
	type 'actb' {
			unsigned hex longint = 0;								/* ctSeed				*/
			integer = 1;											/* ctFlags				*/
			integer = $$Countof(ColorSpec) - 1;						/* ctSize				*/
			wide array ColorSpec {
					integer		wContentColor,						/* value				*/
								wFrameColor,
								wTextColor,
								wHiliteColor,
								wTitleBarColor,
								wHiliteLight,
								wHiliteDark,
								wTitleBarLight,
								wTitleBarDark,
								wDialogLight,
								wDialogDark,
								wTingeLight,
								wTingeDark;
					unsigned integer;								/* RGB:	red				*/
					unsigned integer;								/*		green			*/
					unsigned integer;								/*		blue			*/
			};
	};
#endif
/*--------------------------aedt • Apple Events Template---------------------------------*/
/* Resource definition used for associating a value with an apple event */
/* This really only useful for general dispatching */

type 'aedt' {
	wide array {
	unsigned longint;	/* Event Class 	*/
	unsigned longint;	/* Event ID 	*/
	unsigned longint;	/* Value 	*/
	};
};
/*----------------------------ALRT • Alert Template-------------------------------------*/
type 'ALRT' {
		rect;													/* boundsRect			*/
		integer;												/* 'DITL' ID			*/

		/* NOTE: the stages are ordered 4, 3, 2, 1 */
		wide array [4] {
				boolean 				OK, Cancel; 			/* Bold Outline 		*/
				boolean 				invisible, visible; 	/* Draw Alert			*/
				unsigned bitstring[2]	silent = 0
								sound1, sound2, sound3; 		/* Beeps				*/
		};

	/*	The following are window positioning options ,usable in 7.0	*/
#if SystemSevenOrLater
		unsigned integer				noAutoCenter = 0x0000,
										centerMainScreen = 0x280a,
										alertPositionMainScreen = 0x300a,
										staggerMainScreen = 0x380a,
										centerParentWindow = 0xa80a,
										alertPositionParentWindow = 0xb00a,
										staggerParentWindow = 0xb80a,
										centerParentWindowScreen = 0x680a,
										alertPositionParentWindowScreen = 0x700a,
										staggerParentWindowScreen = 0x780a;
#endif
};
/*----------------------------BNDL • Bundle---------------------------------------------*/
type 'BNDL' {
		literal longint;										/* Signature			*/
		integer;												/* Version ID			*/
		integer = $$CountOf(TypeArray) - 1;
		array TypeArray {
				literal longint;								/* Type 				*/
				integer = $$CountOf(IDArray) - 1;
				wide array IDArray {
						integer;								/* Local ID 			*/
						integer;								/* Actual ID			*/
				};
		};
};
#ifdef oldTemp
/*--------------------------cctb • Control Color old Lookup Table----------------------*/
	type 'cctb' {
			unsigned hex longint;									/* CCSeed				*/
			integer;												/* ccReserved			*/
			integer = $$Countof(ColorSpec) - 1;						/* ctSize				*/
			wide array ColorSpec {
					integer		cFrameColor,						/* partcode				*/
								cBodyColor,
								cTextColor,
								cElevatorColor;
					unsigned integer;								/* RGB:	red				*/
					unsigned integer;								/*		green			*/
					unsigned integer;								/*		blue			*/
			};
	};
#else
/*----------------------------cctb • Control Color Lookup Table-------------------------*/
	type 'cctb' {
		unsigned hex longint = 0;								/* CCSeed				*/
		integer = 0;											/* ccReserved			*/
		integer = $$Countof(ColorSpec) - 1;						/* ctSize				*/
		wide array ColorSpec {
				integer		cFrameColor,						/* partcode				*/
							cBodyColor,
							cTextColor,
							cElevatorColor,
							cFillPatColor,
							cArrowsLight,
							cArrowsDark,
							cThumbLight,
							cThumbDark,
							cHiliteLight,
							cHiliteDark,
							cTitleBarLight,
							cTitleBarDark,
							cTingeLight,
							cTingeDark;
				unsigned integer;								/* RGB:	red				*/
				unsigned integer;								/*		green			*/
				unsigned integer;								/*		blue			*/
		};
	};
#endif
#ifdef oldTemp
/*-----------------------cicn • Color Icon old template-------------------------------------*/
	type 'cicn' {
			/* IconPMap (pixMap) record */
			fill long;												/* Base address			*/
			unsigned bitstring[1] = 1;								/* New pixMap flag		*/
			unsigned bitstring[2] = 0;								/* Must be 0			*/
	pMapRowBytes:
			unsigned bitstring[13];									/* Offset to next row	*/
	Bounds:
			rect;													/* Bitmap bounds		*/
			integer;												/* pixMap vers number	*/
			integer	unpacked;										/* Packing format		*/
			unsigned longint;										/* Size of pixel data	*/
			unsigned hex longint;									/* h. resolution (ppi) (fixed) */
			unsigned hex longint;									/* v. resolution (ppi) (fixed) */
			integer			chunky, chunkyPlanar, planar;			/* Pixel storage format	*/
			integer;												/* # bits in pixel		*/
			integer;												/* # components in pixel*/
			integer;												/* # bits per field		*/
			unsigned longint;										/* Offset to next plane	*/
			unsigned longint;										/* Offset to color table*/
			fill long;												/* Reserved				*/

			/* IconMask (bitMap) record */
			fill long;												/* Base address			*/
	maskRowBytes:
			integer;												/* Row bytes			*/
			rect;													/* Bitmap bounds		*/

			/* IconBMap (bitMap) record */
			fill long;												/* Base address			*/
	iconBMapRowBytes:
			integer;												/* Row bytes			*/
			rect;													/* Bitmap bounds		*/

			fill long;												/* Handle placeholder	*/

			/* Mask data */
			hex string [$$Word(maskRowBytes) * PIXMAPHEIGHT];

			/* BitMap data */
			hex string [$$Word(iconBMapRowBytes) * PIXMAPHEIGHT];

			/* Color Table */
			unsigned hex longint;									/* ctSeed				*/
			integer;												/* ctFlags				*/
			integer = $$Countof(ColorSpec) - 1;						/* ctSize				*/
			wide array ColorSpec {
					integer;										/* value				*/
					unsigned integer;								/* RGB:	red				*/
					unsigned integer;								/*		green			*/
					unsigned integer;								/*		blue			*/
			};

			/* PixelMap data */
			hex string [$$BitField(pMapRowBytes, 0, 13) * PIXMAPHEIGHT];
	};
#else
/*----------------------------cicn • Color Icon-----------------------------------------*/
	type 'cicn' {
			/* IconPMap (pixMap) record */
			fill long;												/* Base address			*/
			unsigned bitstring[1] = 1;								/* New pixMap flag		*/
			unsigned bitstring[2] = 0;								/* Must be 0			*/
	pMapRowBytes:
			unsigned bitstring[13];									/* Offset to next row	*/
	Bounds:	rect;													/* Bitmap bounds		*/
			integer = 0;											/* pixMap vers number	*/
			integer = 0;											/* Packing format		*/
			fill long;												/* Size of pixel data	*/
			unsigned hex longint = $00480000;						/* h. resolution (ppi)  */
			unsigned hex longint = $00480000;						/* v. resolution (ppi)  */
			integer = 0 /* chunky */;								/* Pixel storage format	*/
	PixelSize:
			integer;												/* # bits in pixel		*/
			integer = 1;											/* # components in pixel*/
			integer = $$Word(PixelSize);							/* # bits per field		*/
			fill long;
			fill long;
			fill long;

			/* IconMask (bitMap) record */
			fill long;												/* Base address			*/
			integer = BitMapRowBytes;								/* Row bytes			*/
			PixMapBounds;											/* Bitmap bounds		*/

			/* IconBMap (bitMap) record */
			fill long;												/* Base address			*/
			integer = BitMapRowBytes;								/* Row bytes			*/
			PixMapBounds;											/* Bitmap bounds		*/

			fill long;												/* Handle placeholder	*/

			/* Mask data */
			hex string [BitMapRowBytes * PixMapHeight];

			/* BitMap data */
			hex string [BitMapRowBytes * PixMapHeight];

	ColorTable:
			unsigned hex longint = 0;								/* ctSeed				*/
			integer = 0;											/* ctFlags				*/
			integer = $$Countof(ColorSpec) - 1;						/* ctSize				*/
			wide array ColorSpec {
					integer = $$ArrayIndex(ColorSpec) - 1;			/* value				*/
					unsigned integer;								/* RGB:	red				*/
					unsigned integer;								/*		green			*/
					unsigned integer;								/*		blue			*/
			};

	PixelData:
			hex string [PixMapRowBytes * PixMapHeight];				/* more of the pixmap	*/
	};
#endif
#ifdef oldTemp
/*-------------------------- old clut • Generic Color Lookup Table----------------------*/
	type 'clut' {
			unsigned hex longint;									/* ctSeed				*/
			integer;												/* ctFlags				*/
			integer = $$Countof(ColorSpec) - 1;						/* ctSize				*/
			wide array ColorSpec {
					integer;										/* value				*/
					unsigned integer;								/* RGB:	red				*/
					unsigned integer;								/*		green			*/
					unsigned integer;								/*		blue			*/
			};
	};
#else
/*----------------------------clut • Generic Color Lookup Table-------------------------*/
	type 'clut' {
			unsigned hex longint = 0;								/* ctSeed				*/
			integer = 0;											/* ctFlags				*/
			integer = $$Countof(ColorSpec) - 1;						/* ctSize				*/
			wide array ColorSpec {
					integer = $$ArrayIndex(ColorSpec) - 1;			/* value				*/
					unsigned integer;								/* RGB:	red				*/
					unsigned integer;								/*		green			*/
					unsigned integer;								/*		blue			*/
			};
	};
#endif
/*----------------------------CNTL • Control Template-----------------------------------*/
type 'CNTL' {
		rect;													/* Bounds				*/
		integer;												/* Value				*/
		byte			invisible, visible; 					/* visible				*/
		fill byte;
		integer;												/* Max					*/
		integer;												/* Min					*/
		integer 		pushButProc,							/* ProcID				*/
						checkBoxProc,
						radioButProc,
						pushButProcUseWFont = 8,
						checkBoxProcUseWFont,
						radioButProcUseWFont,
						scrollBarProc = 16;
		longint;												/* RefCon				*/
		pstring;												/* Title				*/
};

#define	popupMenuCDEFproc		1008							/* ProcID 1008 = 16 * 63		*/

/* popup CDEF variation codes */
#define	popupFixedWidth			0x0001
#define	popupReserved			0x0002
#define	popupUseAddResMenu		0x0004
#define	popupUseWFont			0x0008

/* popup CDEF label characteristics */
#define	popupTitleBold			0x0100
#define	popupTitleItalic		0x0200
#define	popupTitleUnderline		0x0400
#define	popupTitleOutline		0x0800
#define	popupTitleShadow		0x1000
#define	popupTitleCondense		0x2000
#define	popupTitleExtend		0x4000
#define popupTitleNoStyle		0x8000

#define	popupTitleLeftJust		0x0000
#define	popupTitleCenterJust	0x0001
#define	popupTitleRightJust		0x00FF

#ifdef oldTemp
/*------------------------crsr • old Color Cursor template----------------------------------*/
	type 'crsr' {
			/* CCrsr record */
			hex unsigned integer	oldCursor   = $8000,			/* Type of cursor		*/
									colorCursor = $8001;
			unsigned longint = pixMap / 8;							/* Offset to pixMap		*/
			unsigned longint = pixelData / 8;						/* Offset to pixel data	*/
			fill long;												/* Expanded cursor data	*/
			fill word;												/* Expanded data depth	*/
			fill long;												/* Reserved				*/
			hex string [32];										/* One bit cursor data	*/
			hex string [32];										/* One bit cursor mask	*/
			point;													/* Hot spot 			*/
			fill long;												/* Table id				*/
			fill long;												/* id for cursor		*/

			/* IconPMap (pixMap) record */
	pixMap:
			fill long;												/* Base address			*/
			unsigned bitstring[1] = 1;								/* New pixMap flag		*/
			unsigned bitstring[2] = 0;								/* Must be 0			*/
			unsigned bitstring[13];									/* Offset to next row	*/
			rect;													/* Bitmap bounds		*/
			integer;												/* pixMap version number*/
			integer	unpacked;										/* Packing format		*/
			unsigned longint;										/* Size of pixel data	*/
			unsigned hex longint;									/* h. resolution (ppi) (fixed) */
			unsigned hex longint;									/* v. resolution (ppi) (fixed) */
			integer			chunky, chunkyPlanar, planar;			/* Pixel storage format	*/
			integer;												/* # bits in pixel		*/
			integer;												/* # components in pixel*/
			integer;												/* # bits per field		*/
			unsigned longint;										/* Offset to next plane	*/
			unsigned longint = colorTable / 8;						/* Offset to color table*/
			fill long;												/* Reserved				*/

	pixelData:
			hex string [(colorTable - pixelData) / 8];				/* Pixel data			*/

			/* Color Table */
	colorTable:
			unsigned hex longint;									/* ctSeed				*/
			integer;												/* ctFlags				*/
			integer = $$Countof(ColorSpec) - 1;						/* ctSize				*/
			wide array ColorSpec {
					integer;										/* value				*/
					unsigned integer;								/* RGB:	red				*/
					unsigned integer;								/*		green			*/
					unsigned integer;								/*		blue			*/
			};
	};
#else
/*----------------------------crsr • Color Cursor---------------------------------------*/
	type 'crsr' {
		/* CCrsr record */
		unsigned hex integer = $8001;							/* Type of cursor		*/
		unsigned longint = PixMap / 8;							/* Offset to pixMap		*/
		unsigned longint = PixelData / 8;						/* Offset to pixel data	*/
		fill long;												/* Expanded cursor data	*/
		fill word;												/* Expanded data depth	*/
		fill long;												/* Reserved				*/
		hex string [32];										/* One bit cursor data	*/
		hex string [32];										/* One bit cursor mask	*/
		point;													/* Hot spot 			*/
		fill long;												/* Table id				*/
		fill long;												/* id for cursor		*/

		/* PixMap record */
	PixMap:
		fill long;												/* Base address			*/
		unsigned bitstring[1] = 1;								/* New pixMap flag		*/
		unsigned bitstring[2] = 0;								/* Must be 0			*/
	pMapRowBytes:
		unsigned bitstring[13];									/* Offset to next row	*/

	Bounds:
		rect = { 0, 0, 16, 16 };								/* Bitmap bounds		*/
		integer = 0;											/* pixMap vers number	*/
		integer = 0;											/* Packing format		*/
		fill long;												/* Size of pixel data	*/
		unsigned hex longint = $00480000;						/* h. resolution (ppi)  */
		unsigned hex longint = $00480000;						/* v. resolution (ppi)  */
		integer = 0 /* chunky */;								/* Pixel storage format	*/

	PixelSize:
		integer;												/* # bits in pixel		*/
		integer = 1;											/* # components in pixel*/
		integer = $$Word(PixelSize);							/* # bits per field		*/
		fill long;
		unsigned longint = ColorTable / 8;
		fill long;

	PixelData:
		hex string [PixMapRowBytes * PixMapHeight];

	ColorTable:
		unsigned hex longint = 0;								/* ctSeed				*/
		integer = 0;											/* ctFlags				*/
		integer = $$Countof(ColorSpec) - 1;						/* ctSize				*/
		wide array ColorSpec {
				integer;										/* value				*/
				unsigned integer;								/* RGB:	red				*/
				unsigned integer;								/*		green			*/
				unsigned integer;								/*		blue			*/
		};
	};
#endif
/*----------------------------CURS • Cursor---------------------------------------------*/
type 'CURS' {
		hex string [32];										/* Data 				*/
		hex string [32];										/* Mask 				*/
		point;													/* Hot spot 			*/
};
/*----------------------------dctb • Dialog Color Lookup Table--------------------------*/
type 'dctb' as 'actb';
/*----------------------------DITL • Dialog Item List-----------------------------------*/
type 'DITL' {
		integer = $$CountOf(DITLarray) - 1; 					/* Array size			*/
		wide array DITLarray {
				fill long;
				rect;											/* Item bounds			*/
				switch {

				case HelpItem:									/* Help Mgr type item */
						boolean 		enabled,disabled;		/* Enable flag			*/
						key bitstring[7] = 1;					/* this is a new type = 1 */

						switch {
							case HMScanhdlg:
								byte = 4;						/* sizeola				*/
								key int = 1;					/* key value 			*/
								integer;						/* resource ID			*/

							case HMScanhrct:
								byte = 4;						/* sizeola				*/
								key int = 2;					/* key value 			*/
								integer;						/* resource ID			*/

							case HMScanAppendhdlg:
								byte = 6;						/* sizeola				*/
								key int = 8;					/* key value 			*/
								integer;						/* resource ID			*/
								integer;						/* offset (zero based)	*/
						};
				case Button:
						boolean 		enabled,disabled;		/* Enable flag			*/
						key bitstring[7] = 4;
						pstring;								/* Title				*/

				case CheckBox:
						boolean 		enabled,disabled;		/* Enable flag			*/
						key bitstring[7] = 5;
						pstring;								/* Title				*/

				case RadioButton:
						boolean 		enabled,disabled;		/* Enable flag			*/
						key bitstring[7] = 6;
						pstring;								/* Title				*/

				case Control:
						boolean 		enabled,disabled;		/* Enable flag			*/
						key bitstring[7] = 7;
						byte = 2;
						integer;								/* 'CTRL' ID			*/

				case StaticText:
						boolean 		enabled,disabled;		/* Enable flag			*/
						key bitstring[7] = 8;
						pstring;								/* Text 				*/

				case EditText:
						boolean 		enabled,disabled;		/* Enable flag			*/
						key bitstring[7] = 16;
						pstring;								/* Text 				*/

				case Icon:
						boolean 		enabled,disabled;		/* Enable flag			*/
						key bitstring[7] = 32;
						byte = 2;
						integer;								/* 'ICON' ID			*/

				case Picture:
						boolean 		enabled,disabled;		/* Enable flag			*/
						key bitstring[7] = 64;
						byte = 2;
						integer;								/* 'PICT' ID			*/

				case UserItem:
						boolean 		enabled,disabled;		/* Enable flag			*/
						key bitstring[7] = 0;
						byte = 0;
				};
				align word;
		};
};
/*----------------------------DLOG • Dialog Template------------------------------------*/
type 'DLOG' {
		rect;													/* boundsRect			*/
		integer 		documentProc,							/* procID				*/
						dBoxProc,
						plainDBox,
						altDBoxProc,
						noGrowDocProc,
						movableDBoxProc,
						zoomDocProc = 8,
						zoomNoGrow = 12,
						rDocProc = 16;
		byte			invisible, visible; 					/* visible				*/
		fill byte;
		byte			noGoAway, goAway;						/* goAway				*/
		fill byte;
		unsigned hex longint;									/* refCon				*/
		integer;												/* 'DITL' ID			*/
		pstring;												/* title				*/
	/*	The following are window positioning options ,usable in 7.0	*/
#if SystemSevenOrLater
		align word;
		unsigned integer				noAutoCenter = 0x0000,
										centerMainScreen = 0x280a,
										alertPositionMainScreen = 0x300a,
										staggerMainScreen = 0x380a,
										centerParentWindow = 0xa80a,
										alertPositionParentWindow = 0xb00a,
										staggerParentWindow = 0xb80a,
										centerParentWindowScreen = 0x680a,
										alertPositionParentWindowScreen = 0x700a,
										staggerParentWindowScreen = 0x780a;
#endif
};
/*----------------------------------------eppc -----------------------------------------*/
type 'eppc' {
	unsigned longint;	/* flags word	*/
	unsigned longint;	/* reserved 	*/
	unsigned integer;	/* scriptCode	*/
	pstring[32];
};
/*----------------------------fctb • Font Color Lookup Table----------------------------*/
type 'fctb' as 'clut';
/*----------------------------FREF • File Reference-------------------------------------*/
type 'FREF' {
		literal longint;										/* File Type			*/
		integer;												/* Icon ID				*/
		pstring;												/* Filename 			*/
};
/*----------------------------ICON • Icon-----------------------------------------------*/
type 'ICON' {
		hex string[128];										/* Icon data			*/
};
/*----------------------------ICN# • Icon List------------------------------------------*/
type 'ICN#' {
		array {
				hex string[128];								/* Icon data			*/
		};
};
type 'KCN#' as 'ICN#';											/* Keyboard Icon data <8>*/
/*----------------------------kind • Custom kind strings --------------------------------*/
type 'kind' {
		literal longint;										/* app signature		 */
		integer;												/* region code of kind string localizations */
		integer = 0;
		integer = $$CountOf(kindArray);		 					/* Array size			*/
		wide array kindArray {
				literal longint;								/* File Type			*/
				pstring;										/* custom kind strings	*/
				align	word;
		};
};
/*----------------------------MENU • Menu-----------------------------------------------*/
type 'MENU' {
		integer;												/* Menu ID				*/
		fill word[2];
		integer 		textMenuProc = 0;						/* ID of menu def proc	*/
		fill word;
		unsigned hex bitstring[31]
						allEnabled = 0x7FFFFFFF;				/* Enable flags 		*/
		boolean 		disabled, enabled;						/* Menu enable			*/
		pstring 		apple = "\0x14";						/* Menu Title			*/
		wide array {
				pstring;										/* Item title			*/
				byte			noIcon; 						/* Icon number			*/
				char			noKey = "\0x00",				/* Key equivalent or	*/
								hierarchicalMenu = "\0x1B";		/* hierarchical menu	*/
				char			noMark = "\0x00",				/* Marking char or id	*/
								check = "\0x12";				/* of hierarchical menu	*/
				fill bit;
				unsigned bitstring[7]
								plain;							/* Style				*/
		};
		byte = 0;
};
/*----------------------------MBAR • Menu Bar-------------------------------------------*/
type 'MBAR' {
		integer = $$CountOf(MenuArray); 						/* Number of menus		*/
		wide array MenuArray{
				integer;										/* Menu resource ID 	*/
		};
};
/*----------------------------mctb • Menu Color Lookup Table----------------------------*/
type 'mctb' {
		integer = $$CountOf(MCTBArray); 						/* Color table count	*/
		wide array MCTBArray {
			integer				mctbLast = -99;					/* Menu resource ID 	*/
			integer;											/* Menu Item 			*/
			wide array [4] {
					unsigned integer;							/* RGB: red				*/
					unsigned integer;							/*		green			*/
					unsigned integer;							/*		blue			*/
			};
			fill word;											/* Reserved word		*/
		};
};
/*----------------------------open • FileTypes an app can open--------------------------*/
type 'open' {
		literal longint;										/* app signature		*/
		integer = 0;
		integer = $$CountOf(typeArray);		 					/* Array size			*/
		wide array typeArray {									/* FileTypes that app can open */
				literal longint;								/* FileType				*/
		};
};
/*----------------------------PAT  • Quickdraw Pattern----------------------------------*/
type 'PAT ' {
		hex string[8];											/* Pattern				*/
};
/*----------------------------PAT# • Quickdraw Pattern List-----------------------------*/
type 'PAT#' {
		integer = $$Countof(PatArray);
		array PatArray {
				hex string[8];									/* Pattern				*/
		};
};
#ifndef __PICT_R__
/*----------------------------PICT • Quickdraw Picture----------------------------------*/
type 'PICT' {
		unsigned integer;										/* Length				*/
		rect;													/* Frame				*/
		hex string; 											/* Data 				*/
};
#endif __PICT_R__
/*----------------------------pltt • Color Palette--------------------------------------*/
type 'pltt' {
		integer = $$CountOf(ColorInfo); 						/* Color table count	*/
		fill long;												/* Reserved				*/
		fill word;												/* Reserved				*/
		fill long;												/* Reserved				*/
		fill long;												/* Reserved				*/
		wide array ColorInfo {
			unsigned integer;									/* RGB: red				*/
			unsigned integer;									/*		green			*/
			unsigned integer;									/* 		blue			*/
			integer		pmCourteous, pmDithered, pmTolerant,	/* Color usage			*/
						pmAnimated = 4, pmExplicit = 8;
			integer;											/* Tolerance value		*/
			fill word;											/* Private flags		*/
			fill long;											/* Private				*/
		};
};
#ifdef oldTemp
/*------------------------ppat • Pixel Pattern old template---------------------------------*/
	type 'ppat' {
			/* PixPat record */
			integer		oldPattern,									/* Pattern type			*/
						newPattern,
						ditherPattern;
			unsigned longint = PixMap / 8;							/* Offset to pixmap		*/
			unsigned longint = PixelData / 8;						/* Offset to data		*/
			fill long;												/* Expanded pixel image	*/
			fill word;												/* Pattern valid flag	*/
			fill long;												/* expanded pattern		*/
			hex string [8];											/* old-style pattern	*/

			/* PixMap record */
	PixMap:
			fill long;												/* Base address			*/
			unsigned bitstring[1] = 1;								/* New pixMap flag		*/
			unsigned bitstring[2] = 0;								/* Must be 0			*/
			unsigned bitstring[13];									/* Offset to next row	*/
			rect;													/* Bitmap bounds		*/
			integer;												/* pixMap vers number	*/
			integer		unpacked;									/* Packing format		*/
			unsigned longint;										/* size of pixel data	*/
			unsigned hex longint;									/* h. resolution (ppi) (fixed) */
			unsigned hex longint;									/* v. resolution (ppi) (fixed) */
			integer			chunky, chunkyPlanar, planar;			/* Pixel storage format	*/
			integer;												/* # bits in pixel		*/
			integer;												/* # components in pixel*/
			integer;												/* # bits per field		*/
			unsigned longint;										/* Offset to next plane	*/
			unsigned longint = ColorTable / 8;						/* Offset to color table*/
			fill long;												/* Reserved				*/

	PixelData:
			hex string [(ColorTable - PixelData) / 8];

	ColorTable:
			unsigned hex longint;									/* ctSeed				*/
			integer;												/* ctFlags				*/
			integer = $$Countof(ColorSpec) - 1;						/* ctSize				*/
			wide array ColorSpec {
					integer;										/* value				*/
					unsigned integer;								/* RGB:	red				*/
					unsigned integer;								/*		green			*/
					unsigned integer;								/*		blue			*/
			};
	};
#else
/*----------------------------ppat • Pixel Pattern--------------------------------------*/
	type 'ppat' {
			/* PixPat record */
			integer = 1 /* newPattern */;							/* Pattern type			*/
			unsigned longint = PixMap / 8;							/* Offset to pixmap		*/
			unsigned longint = PixelData / 8;						/* Offset to data		*/
			fill long;												/* Expanded pixel image	*/
			fill word;												/* Pattern valid flag	*/
			fill long;												/* expanded pattern		*/
			hex string [8];											/* old-style pattern	*/

			/* PixMap record */
	PixMap:
			fill long;												/* Base address			*/
			unsigned bitstring[1] = 1;								/* New pixMap flag		*/
			unsigned bitstring[2] = 0;								/* Must be 0			*/
	pMapRowBytes:
			unsigned bitstring[13];									/* Offset to next row	*/
	Bounds:	rect;													/* Bitmap bounds		*/
			integer = 0;											/* pixMap vers number	*/
			integer = 0;											/* Packing format		*/
			fill long;												/* Size of pixel data	*/
			unsigned hex longint = $00480000;						/* h. resolution (ppi)  */
			unsigned hex longint = $00480000;						/* v. resolution (ppi)  */
			integer = 0 /* chunky */;								/* Pixel storage format	*/
	PixelSize:
			integer;												/* # bits in pixel		*/
			integer = 1;											/* # components in pixel*/
			integer = $$Word(PixelSize);							/* # bits per field		*/
			fill long;
			unsigned longint = ColorTable / 8;
			fill long;

	PixelData:
			hex string [PixMapRowBytes * PixMapHeight];

	ColorTable:
			unsigned hex longint = 0;								/* ctSeed				*/
			integer = 0;											/* ctFlags				*/
			integer = $$Countof(ColorSpec) - 1;						/* ctSize				*/
			wide array ColorSpec {
					integer = $$ArrayIndex(ColorSpec) - 1;			/* value				*/
					unsigned integer;								/* RGB:	red				*/
					unsigned integer;								/*		green			*/
					unsigned integer;								/*		blue			*/
			};
	};
#endif
/*----------------------------SICN • Small Icon-----------------------------------------*/
type 'SICN' {
		array {
				hex string[32]; 								/* SICN data			*/
		};
};
/*----------------------------SIZE • MultiFinder Size Information-----------------------*/
#define	ignoreAppDiedEvents			ignoreChildDiedEvents
#define	acceptAppDiedEvents			acceptChildDiedEvents
#define	needsActivateOnFGSwitch		notMultiFinderAware			/* for compatibility	*/
#define	doesActivateOnFGSwitch		multiFinderAware			/* for compatibility	*/
#define	dontSaveScreen				reserved					/* for compatibility	*/
#define	saveScreen					true						/* for compatibility	*/
#define	enableOptionSwitch			reserved					/* for compatibility	*/
#define	disableOptionSwitch			true						/* for compatibility	*/

type 'SIZE' {
		boolean					reserved;
		boolean 				ignoreSuspendResumeEvents,		/* suspend-resume		*/
								acceptSuspendResumeEvents;
		boolean					reserved;
		boolean					cannotBackground,
								canBackground;					/* Can properly use back-
																   ground null events	*/
		boolean					needsActivateOnFGSwitch,		/* activate/deactivate	*/
								doesActivateOnFGSwitch;			/* on resume/suspend	*/
		boolean					backgroundAndForeground,		/* Application does not	*/
								onlyBackground;					/* have a user interface*/
		boolean					dontGetFrontClicks,				/* Get mouse down/up	*/
								getFrontClicks;					/* when suspended		*/
		boolean					ignoreAppDiedEvents,			/* Apps use this.		*/
								acceptAppDiedEvents;			/* Debuggers use this.	*/
		boolean					not32BitCompatible,				/* Works with 24bit addr*/
								is32BitCompatible;				/* Works with 24 or 32	*/
																/* bit addresses		*/
/* next four bits are new for system 7.0 */
		boolean					notHighLevelEventAware,
								isHighLevelEventAware;			/* does Post/AcceptHighLevelEvent */
		boolean					onlyLocalHLEvents,				/* paranoid users' flag */
								localAndRemoteHLEvents;
		boolean					notStationeryAware,				/* checks stationery bit */
								isStationeryAware;				/* when opening documents */
		boolean					dontUseTextEditServices,		/* can use text services */
								useTextEditServices;			/* through TextEdit.     */

#undef reserved
		boolean					reserved;						/* These 3 bits are 	*/
		boolean					reserved;						/* reserved.  Set them	*/
		boolean					reserved;						/* to "reserved". When	*/
																/* we decide to define	*/
																/* a new flag, your		*/
																/* old resource will 	*/
																/* still compile.		*/

		/* Memory sizes are in bytes */
		unsigned longint;										/* preferred mem size	*/
		unsigned longint;										/* minimum mem size		*/

		// If we ever define one of the four reserved bits above, the "reserved"
		// enumeration wouldn't appear on the newly defined bit.  By defining "reserved"
		// below, old resource SIZE declarations will still compile.
#define	reserved		false
};
/*----------------------------STR  • Pascal-Style String--------------------------------*/
type 'STR ' {
		pstring;												/* String				*/
};
/*----------------------------STR# • Pascal-Style String List---------------------------*/
type 'STR#' {
		integer = $$Countof(StringArray);
		array StringArray {
				pstring;										/* String				*/
		};
};
/*----------------------------thng  • Component Manager thing----------------------------------*/
#ifndef UseExtendedThingResource
#define UseExtendedThingResource 0
#endif

#define cmpWantsRegisterMessage 			(1<<31)				/* bits for conponent flags */

#define componentDoAutoVersion 				(1<<0)				/* bits for registration flags  */
#define componentWantsUnregister			(1<<1)
#define componentAutoVersionIncludeFlags	(1<<2)
#define componentHasMultiplePlatforms		(1<<3)

type 'thng' {
		literal longint;										/* Type */
		literal longint;										/* Subtype */
		literal longint;										/* Manufacturer */
		unsigned hex longint; 									/* conponent flags */
		unsigned hex longint	kAnyComponentFlagsMask = 0;		/* conponent flags Mask */
		literal longint;										/* Code Type */
		integer;												/* Code ID */
		literal longint;										/* Name Type */
		integer;												/* Name ID */
		literal longint;										/* Info Type */
		integer;												/* Info ID */
		literal longint;										/* Icon Type */
		integer;												/* Icon ID */
#if UseExtendedThingResource
		unsigned hex longint;									/* version of Component */
		longint;												/* registration flags */
		integer;												/* resource id of Icon Family */
		longint = $$CountOf(ComponentPlatformInfo);
		wide array ComponentPlatformInfo {
			unsigned hex longint; 								/* conponent flags */
			literal longint;									/* Code Type */
			integer;											/* Code ID */
			integer platform68k = 1, platformPowerPC = 2;		/* platform type (response from gestaltSysArchitecture) */
		};
#endif
};
/*----------------------------wctb • Window Color Lookup Table--------------------------*/
type 'wctb' as 'actb';
/*----------------------------WIND • Window Template------------------------------------*/
type 'WIND' {
		rect;													/* boundsRect			*/
		integer 		documentProc,							/* procID				*/
						dBoxProc,
						plainDBox,
						altDBoxProc,
						noGrowDocProc,
						movableDBoxProc,
						zoomDocProc = 8,
						zoomNoGrow = 12,
						rDocProc = 16;
		byte			invisible, visible; 					/* visible				*/
		fill byte;
		byte			noGoAway, goAway;						/* goAway				*/
		fill byte;
		unsigned hex longint;									/* refCon				*/
		pstring 		Untitled = "Untitled";					/* title				*/
	/*	The following are window positioning options ,usable in 7.0	*/
#if SystemSevenOrLater
		align word;
		unsigned integer				noAutoCenter = 0x0000,
										centerMainScreen = 0x280a,
										alertPositionMainScreen = 0x300a,
										staggerMainScreen = 0x380a,
										centerParentWindow = 0xa80a,
										alertPositionParentWindow = 0xb00a,
										staggerParentWindow = 0xb80a,
										centerParentWindowScreen = 0x680a,
										alertPositionParentWindowScreen = 0x700a,
										staggerParentWindowScreen = 0x780a;
#endif
};
/*--------------------------------------------------------------------------------------*/

/* resource containing a single rectangle */

	type 'RECT' { rect; };

/* stages for ALRT */

	#define silentStage OK, visible, silent
	#define silentStages { silentStage; silentStage; silentStage; silentStage; }

	#define beepStage OK, visible, sound1
	#define beepStages { beepStage; beepStage; beepStage; beepStage; }

/* RGB colors */

	#define whiteRGB $FFFF, $FFFF, $FFFF
	#define blackRGB 0, 0, 0

/* colors for 'crsr' resources */

	#define transparentRGB $FFFF, $FFFF, $FFFF
	#define invertRGB 0, 0, 0

/* small icons with masks */

	type 'ics#' {
		array [2] {
			hex string[32];
		};
	};
	type 'kcs#' as 'ics#';								/* Keyboard small icon <8> */

/* mini icons with masks */

	type 'icm#' {
		array [2] {
			hex string[24];
		};
	};

/* 8-bit color mini icon--no mask, no color table */

	type 'icm8' {
		hex string[192];
	};

/* 4-bit color mini icon--no mask, no color table */

	type 'icm4' {
		hex string[96];
	};

/* 8-bit color icon--no mask, no color table */

	type 'icl8' {
		hex string[1024];
	};
	type 'kcl8' as 'icl8';								/* Keyboard 8-bit color icon <8> */

/* 4-bit color icon--no mask, no color table */

	type 'icl4' {
		hex string[512];
	};
	type 'kcl4' as 'icl4';								/* Keyboard 4-bit color icon <8> */

/* 8-bit color small icon--no mask, no color table */

	type 'ics8' {
		hex string[256];
	};
	type 'kcs8' as 'ics8';								/* Keyboard 8-bit small color icon <8> */

/* 4-bit color small icon--no mask, no color table */

	type 'ics4' {
		hex string[128];
	};
	type 'kcs4' as 'ics4';								/* Keyboard 4-bit small color icon <8> */

/* a list of pixpats; Rez can’t yet handle this correctly */

	type 'ppt#' {
			/* PixPat offsets (calculate them some day!?!) */
			integer = $$CountOf(OffsetArray);
			array OffsetArray /* [$$CountOf(PixPatArray)] */ {
				unsigned longint /* = PixPat[$$ArrayIndex(OffsetArray)] / 8 */;
			};

		array PixPatArray {
PixPat:
			/* PixPat record */
			integer = 1 /* newPattern */;							/* Pattern type			*/
			unsigned longint = PixMap[$$ArrayIndex(PixPatArray)] / 8;	/* Offset to pixmap		*/
			unsigned longint = PixelData[$$ArrayIndex(PixPatArray)] / 8;	/* Offset to data		*/
			fill long;												/* Expanded pixel image	*/
			fill word;												/* Pattern valid flag	*/
			fill long;												/* expanded pattern		*/
			hex string [8];											/* old-style pattern	*/

			/* PixMap record */
PixMap:
			fill long;												/* Base address			*/
			unsigned bitstring[1] = 1;								/* New pixMap flag		*/
			unsigned bitstring[2] = 0;								/* Must be 0			*/
pMapRowBytesIndexed:
			unsigned bitstring[13];									/* Offset to next row	*/
Bounds:		rect;													/* Bitmap bounds		*/
			integer = 0;											/* pixMap vers number	*/
			integer = 0;											/* Packing format		*/
			fill long;												/* Size of pixel data	*/
			unsigned hex longint = $00480000;						/* h. resolution (ppi)  */
			unsigned hex longint = $00480000;						/* v. resolution (ppi)  */
			integer = 0 /* chunky */;								/* Pixel storage format	*/
PixelSize:
			integer;												/* # bits in pixel		*/
			integer = 1;											/* # components in pixel*/
			integer = $$Word(PixelSize[$$ArrayIndex(PixPatArray)]);	/* # bits per field		*/
			fill long;
			unsigned longint = ColorTable[$$ArrayIndex(PixPatArray)] / 8;
			fill long;

PixelData:
			hex string [PixMapRowBytesIndexed * PixMapHeightIndexed];

ColorTable:
			unsigned hex longint = 0;								/* ctSeed				*/
			integer = 0;											/* ctFlags				*/
			integer = $$Countof(ColorSpec[$$ArrayIndex(PixPatArray)]) - 1;						/* ctSize				*/
			wide array ColorSpec {
					integer = $$ArrayIndex(ColorSpec[$$ArrayIndex(PixPatArray)]) - 1;			/* value				*/
					unsigned integer;								/* RGB:	red				*/
					unsigned integer;								/*		green			*/
					unsigned integer;								/*		blue			*/
			};
		};
	};

/* types for the Database Access Manager */

/* 'wstr' - Word Length String Resource */
type 'wstr' {
		wstring;												/* string with word length spec. */
};

/* 'qrsc' - Query Resource */
type 'qrsc' {
		integer;												/* version */

		integer;												/* 'qdef' ID */

		integer;												/* STR# ID for ddevName, host,
											  						 user, password, connstr */

		integer;												/* current query */

		/* array of IDs of 'wstr' resources containing queries */
		integer = $$CountOf(QueryArray);						/* array size */
		wide array QueryArray {
			integer;											/* id of 'wstr' resource */
		};

		/* array of types and IDs for other resources for query */
		integer = $$CountOf(ResArray);							/* array size */
		wide array ResArray {
			literal longint;									/* resource type */
			integer;											/* resource ID */
		};
};

/* 'dflg' - ddev Flags */
type 'dflg' {
		longint;												/* version */

		unsigned bitstring[32]									/* ddev flags */
			asyncNotSupp, asyncSupp;
};

/*--------------------------------------------------------------------------------------*/

#endif __TYPES_R__

