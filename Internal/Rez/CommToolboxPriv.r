/*
	File:		CommToolboxPriv.r

	Contains:	Res Privates for CTB

	Written by:	Byron Han

	Copyright:	© 1988-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<12>	 8/27/91	JSM		Cleanup header.
		<11>	 6/26/91	BH		move caps to CTBTypes.r
		<10>	 2/11/91	kaz		jng: Adding 'LATg' protocol value for the LAT Gateway tool
		 <9>	 1/10/91	kaz		<jng> Moving 'caps' resource definition from public interfaces.
		 <8>	  1/9/91	kaz		<jng> Changing ModemStringType and PrinterStringType to STR# to
									include driver names. Changing ChooseIDStrID from -32512 to
									-32510.
		 <7>	 11/1/90	fjs		add grautuitous equates for color icon types
		 <6>	 9/10/90	JNG		Add unavailable tool alert
		 <5>	 5/22/90	kaz		Changing NuLookup STR# to a PICT
		 <4>	 3/16/90	BBH		added CTB_Version
		 <3>	 3/15/90	BBH		fix typo
		 <2>	 3/14/90	BBH		added CTB_SysHeapMinType and ID for minimum system heap size
									after installation (this will go away when we do ptch's!)
		 <1>	 3/14/90	BBH		first checked in

*/

/*
===============================================================================
NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE

Any changes made here MUST be reflected also in 
	CommToolboxPriv.p
	CommToolboxPriv.a
	CommToolboxPriv.h
	CommToolboxPriv.r
NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE
===============================================================================
*/
//	This file contains the resource types and resource ID's to be used by the CommToolbox

/* the following 7 resources are temporary to be merged into ptch code */
#define		CTB_InstallType			'INIT'
#define		CTB_InstallID			29

#define		CTB_DispatcherType		'proc'			/* this used to be ctbd -32512 */
#define		CTB_DispatcherID		-32509

#define		CTB_GestaltProcType		'proc'			/* this used to be ctbg -32510 */
#define		CTB_GestaltProcID		-32508

#define		CTB_PatchType			'ctbp'			/* this used to be type ctb¶ */
#define		CTB_Patch1				-32512			/* allocate low memory */
#define		CTB_Patch2				-32511			/* register builtin ports */
#define		CTB_Patch3				-32510			/* perform gestalt installation */

/* end temporary */

#define		CTB_ConnectionMgrType	'cmtb'
#define		CTB_FileTransferMgrType	'cmtb'
#define		CTB_TerminalMgrType		'cmtb'
#define		CTB_CTBUtilitiesType	'cmtb'
#define		CTB_CommResourceMgrType	'cmtb'

#define		CTB_ConnectionMgrID		-32512
#define		CTB_FileTransferMgrID	-32511
#define		CTB_TerminalMgrID		-32510
#define		CTB_CTBUtilitiesID		-32509
#define		CTB_CommResourceMgrID	-32508

#define		CTB_VersionType			'ctb '			/* this used to be ctbv -32511 */
#define		CTB_VersionID			-32512

#define		CTB_KeyclickType		'snd '			/* this used to be ctb$ -32511 */
#define		CTB_KeyclickID			-32512

#define		CTB_ChooseType			'proc'			/* this used to be choo -32512 */
#define		CTB_ChooseID			-32512

#define		CTB_DITLPackType		'proc'			/* this used to be ditl -32512 */
#define		CTB_DITLPackID			-32511

#define		CTB_NuLookupType		'proc'			/* this used to be nlup -32510 */
#define		CTB_NuLookupID			-32510

#define		CTB_NuLookupParmsType	'flst'			/* this used to be parm -32510 */
#define		CTB_NuLookupParmsID		-32510

#define		CTB_ModemIconType		'ICN#'			/* this used to be ctbi -32512 */
#define		CTB_Modem4ColorIconType 'icl4'
#define		CTB_Modem8ColorIconType 'icl8'
#define		CTB_ModemIconID			-32512			

#define		CTB_PrinterIconType		  'ICN#'		/* this used to be ctbi -32511 */
#define		CTB_Printer4ColorIconType 'icl4'
#define		CTB_Printer8ColorIconType 'icl8'
#define		CTB_PrinterIconID		  -32511

#define 	CTB_ModemStringType		'STR#'			/* this used to be ctbs -32512 */
#define		CTB_ModemStringID		-32512

#define		CTB_PrinterStringType	'STR#'			/* this used to be ctbs -32511 */
#define		CTB_PrinterStringID		-32511

#define		CTB_CommFolderNameType	'STR '			/* this used to be ctbs -32510 */
#define		CTB_CommFolderNameID	-32510

#define		CTB_MarkerType			'ctb '			/* lets CTB6 installer scripts know CTB7 is installed */
#define		CTB_CTB6MarkerID		0
#define		CTB_CTB7MarkerID		1

#define		CTB_ChooseDLOGID		-32512
#define		CTB_ChoosehdlgID		-32512
#define		CTB_ChoosedctbID		-32512
#define		CTB_ChooseDITLID		-32512
#define		CTB_ChooseSTRsID		-32510
#define		CTB_ChooseLDEFID		-32512
#define		CTB_ChoosehmnuID		-32512
#define		CTB_ChoosefinfID		-32512
#define		CTB_ChooseflstID		-32512			/* preferred over finf */
#define		CTB_ChooseCNTLID		-32512			
#define		CTB_ChooseMENUID		-32512

#define		CTB_ChooseConfirmDLOGID	-32511
#define		CTB_ChooseConfirmDITLID	-32511

#define		CTB_ChooseUnavailableDLOGID	-32509
#define		CTB_ChooseUnavailableDITLID	-32509

#define		CTB_NulookuphdlgID		-32510
#define		CTB_NulookupDLOGID		-32510
#define		CTB_NulookupdctbID		-32510
#define		CTB_NulookupDITLID		-32510
#define		CTB_NulookupPICTID		-32510
#define		CTB_NulookupLDEFID		-32510

#define		CTB_PopupCDEFType		'CDEF'
#define		CTB_PopupCDEFID			63

/* added since CTB6 */
#define		CTB_PopupTriangleType	'PICT'
#define		CTB_PopupTriangleID		-8224		/* owned by cdef 63 */

#define		CTB_PopupExpandType		'proc'		/* this expands menuwidth */
#define		CTB_PopupExpandID		-8224		/* owned by cdef 63 */


