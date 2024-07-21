/*
	File:		IconUtilsPrivTypes.r

	Contains:	Resource IDs for generic icons used by standard file, finder, and apps

				Finder uses entire families of icons
				Standard File LDEF uses the SICNs only

	Copyright:	© 1990-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <8>	11/19/91	JSM		Add #defines for model icons and systemSuitcaseIconResource.
		 <7>	 11/5/91	DTY		Add #define for fontsFolderIconResource
		 <6>	 8/28/91	JSM		Cleanup header.
		 <5>	 1/17/91	DC		csd - add genericExtensionIconResource (-16415)
		 <4>	12/27/90	csd		Added clipboardFileIconResource for the Clipboard Icon.
		 <3>	11/19/90	DC		ngk - Changed identifier names for generic icons to conform to
									new public names
		 <2>	10/31/90	csd		Added the generic query document icon, generic suitcase, and
									generic Mover object resource IDs.
		 <1>	 8/30/90	ngk		first checked in
		 <0>	 8/30/90	ngk		moved icons out of GenericIcons.r into here

*/

#ifndef __ICONUTILSPRIVTYPES.R__
#define __ICONUTILSPRIVTYPES.R__

// The genericIconBase is full! Do not add any more icons to this range. Instead,
// use assigned reserved resource IDs.

#define genericIconBase						-4000
#define popupMenuSymbolResource				-3990
#define standalonePopupMenuSymbolResource	-3986

#define genericMailboxIconResource			-3987	/* excise from 7.0 */
#define genericLetterIconResource			-3988	/* excise from 7.0 */

/* The following are icons for which there are both icon suites and SICNs. */

#define genericDocumentIconResource			-4000
#define genericStationeryIconResource		-3985
#define genericEditionFileIconResource		-3989
#define genericApplicationIconResource		-3996
#define genericDeskAccessoryIconResource	-3991

#define genericFolderIconResource			-3999
#define privateFolderIconResource			-3994

#define floppyIconResource					-3998
#define trashIconResource					-3993

/* The following are icons for which there are SICNs only. */

#define desktopIconResource					-3992
#define openFolderIconResource				-3997
#define genericHardDiskIconResource			-3995
#define genericFileServerIconResource		-3972
#define genericSuitcaseIconResource			-3970
#define genericMoverObjectIconResource		-3969

/* The following are icons for which there are icon suites only. */

#define genericPreferencesIconResource		-3971
#define genericQueryDocumentIconResource	-16506
#define genericExtensionIconResource		-16415
#define clipboardFileIconResource			-16509

#define systemFolderIconResource			-3983	
#define appleMenuFolderIconResource			-3982
#define startupFolderIconResource			-3981
#define ownedFolderIconResource				-3980
#define dropFolderIconResource				-3979
#define sharedFolderIconResource			-3978
#define mountedFolderIconResource			-3977
#define controlPanelFolderIconResource		-3976
#define spoolFolderIconResource				-3975
#define preferencesFolderIconResource		-3974
#define extensionsFolderIconResource		-3973
#define	fontsFolderIconResource				-3968

#define fullTrashIconResource				-3984

#define systemSuitcaseIconResource			-16494

/* The following are icons for the various Macintosh models. */

#define MacUnknownIconResource				3			/* unknown model or Macintosh XL */
#define MacPlusClassicIconResource			-16482		/* 128, 512, 512Ke, Plus, Classic, Classic II */
#define MacSEIconResource					-16483		/* SE, SE/30 */
#define MacPortableIconResource				-16484		/* Portable */
#define MacIIcxIIciIconResource				-16485		/* IIcx, IIci */
#define MacIIIconResource					-16486		/* II, IIx, IIfx */
#define MacIIsiIconResource					-16502		/* IIsi */
#define MacLCIconResource					-16503		/* LC */
#define Quadra900IconResource				-16504		/* Quadra 900 */
#define PowerBook140170IconResource			-16505		/* Powerbook 140, PowerBook 170 */
#define Quadra700IconResource				-16507		/* Quadra 700 */
#define PowerBook100IconResource			-16508		/* Powerbook 100 */

#endif __ICONUTILSPRIVTYPES.R__
