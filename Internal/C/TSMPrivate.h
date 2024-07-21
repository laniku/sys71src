/*
	File:		TSMPrivate.h

	Contains:	Text Services Manager's private header file

	Written by:	Kenny SC. Tung

	Copyright:	й 1991-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<44>	  8/4/92	DCL		Moved InformTSM out of the public eye and into TSMPrivate.
		<43>	 7/16/92	KST		#1034952 <Kda>: Added one new patchMask bit constant --
									kTSMEventBeenCalled.
		<42>	  7/8/92	KST		#1033475 <JH>: Added a new routine utScriptIsCCJKAndNeedsIM().
		<41>	  7/8/92	KST		<JH>: Changed the routine name utHasNoInputMethod() to
									utScriptIsNotCCJK() to be more descriptive.
		<40>	 6/26/92	KST		#1033450,1033456,1031316 <JH>: utCloseIM4Document() will now
									take an extra parameter to indicate if it should send
									HidePallete() command to input method. Only set it to true when
									called in SetDefaultInputMethod().
		<39>	 6/17/92	KST		#1030843 <JH>: Added one field in TSM global for
									__PopupMenuSelect patch. Also changed the function name from
									utaIsApplicationTSMAware to utaIsAppTSMAwareAndNotUsingIW to be
									more precise and descriptive.
		<38>	 6/16/92	KST		<JH>: Added one new patchMask bit constant and a new field in
									TSM document record.
		<37>	 6/14/92	KST		#1032463 <JH>: Changed utaRemoveDocumentID to return the number
									of TSM documents remained open by the application.
		<36>	 6/13/92	KST		#1032463 <JH>: Added 2 new function prototypes --
									utDeleteAppsMenu, utDeleteSysMenu.
		<35>	 6/10/92	KST		#1031142,1030881 <JH>: Added global tsmUseInputWindowDoc. Added
									a new private for SWM TSMEventFromSWM to solve the
									UseInputWindow problem.
		<34>	  6/2/92	pvh		Change MenuList to ApplicationMenuList since MenuList is already
									in SysMisc.h. Send John back to Japan.
		<33>	  6/2/92	JH		<KST>: Added global variable for original menuID of FEP menus.
		<32>	 5/19/92	KST		#1029247 <hsK>: Added prototype for a new routine: utBadSandL.
		<31>	 5/14/92	KST		#1025797,<JH>: Added one new message selector 'kMsgHelpHELPMgr'
									to InformTSM.
		<30>	  5/1/92	KST		#1027482,<JH>: Added a constant -- kSWMJustSetCursor.
		<29>	  5/1/92	KST		#1028301,<JH>: JH,#1028301: kMaxTSMSelector has changed because
									SetTSMDialogState, RestoreTSMDialogState.. etc has been removed.
		<28>	  5/1/92	JH		Added a byte field to globals that is used to set bit flags that
									our SetCursor patch will use.
		<27>	 4/10/92	KST		Adding more documentations.
		<26>	  4/9/92	KST		JH,Adding a control parameterblock for communicating with the
									swmdrvr. Adding 2 selectors for InformTSM. TSM global is now
									shared with SWM driver.
		<25>	 3/30/92	KST		JH, added a special TSM document signature --
									kTSMShadowDocumentSig to represent the document handle is temp.
									allocated (the real one has been deleted).
		<24>	 3/30/92	KST		JH, 1025008, 1025009. First attempt to solve the pallete/menu
									bar flickering problem. Also, we synchronize the keyboard menu
									with the script of the TSM document. Added 2 new calls:
									utForceDeactivateIM4Document and utSoftDeactivateIM4Document.
		<23>	 3/23/92	KST		Changed internal Assembly routine's name to "utaXXX".
		<22>	 3/16/92	KST		Removed DocumentID parameter from TSMEvent, TSMMenuSelect, and
									SetTSMCursor calls. It applies to the current active TSM
									document.
		<21>	 3/12/92	KST		We now store a refcon in each document record. Added refcon
									mapping cache in TSM globals.
		<20>	  3/4/92	KST		Added new fields "tsmSetCursorProc", and "tsmSavedCursorState"
									in TSM globals.
		<19>	  3/3/92	KST		kMaxTSMSelector is now 28.
		<18>	  3/2/92	KST		Included "Layers.h".
		<17>	  3/2/92	KST		Moved kMaxTSMSelector to TSMPrivate.h, and added a new private
									trap selector "NewTSMDocument4SWM".
		<16>	  3/2/92	KST		Added a private call "NewTSMDocument4SWM", which function the
									same as "NewTSMDocument" but will not activate input method.
		<15>	 2/28/92	KST		Added a new field "tsmSavedLayer" in TSM globals.
		<14>	 2/27/92	KST		Added a field "tsmKillApplicationP" in TSM globals. Added a new
									call "utDeleteMenu".
		<13>	 2/25/92	KST		Defined a new AE event ID: kCloseSWMWindow for closing SWM
									Window.
		<12>	 2/25/92	KST		Added more documentation about internal TSM data structures.
		<11>	 2/11/92	DCL		Changed the name of TSMEqu.[aph] to TextServices.[aph] for
									better read-ability.
		<10>	 2/10/92	KST		Adding prototypes for TSM calls.
		 <9>	 2/10/92	KST		Change the default input method resource format to save the FEP
									ID info for using old Japanese input method.
		 <8>	  2/3/92	KST		TSM needs a flag to tell if we are using the old Japanese Input
									Method when JIM is changed.
		 <7>	  2/1/92	KST		We don't have a global flag in TSM globals to indicate using
									bottom window. Change the byte to indicate the number of active
									text services for ease of debugging.
		 <6>	 1/29/92	KST		Moved default input method instance table out of TSM globals to
									Document record. Each document now owns their own instance of
									the IM.
		 <5>	 1/16/92	KST		Add a field to indicate if the menu for the default input method
									is in the menu bar.
		 <4>	 1/11/92	KST		TSM globals now has an input method table to store the open
									default input methods for CJK scripts.
		 <3>	 1/11/92	KST		The default input method is not opened for each document.
									Instead, it is always open and saved in TSM globals.
		 <2>	  1/9/92	KST		Adding a new call, utUpdateDocFlagInPSNTable.
		 <5>	12/31/91	KST		Moved from TextServiceMgr folder to Internal folder.
		 <4>	12/27/91	KST		Moved ComponentResult error codes to TSMEqu.h.
		 <3>	12/20/91	KST		Making progress.
		 <2>	12/10/91	KST		Check in the first time.

*/


/*	********************************************************************************
 *	File:	"TSMPrivate.h"
 *
 *	Written  by Kenny SC. Tung
 *
 *	Modification History:
 *	09Dec91		KSCT	New today.
 *
 *	е TSM is a simple piece of system software, what makes it complicated is the
 *	task to maintain keyboard and input method synchronization. Use or not to use 
 *	the input window. And of course, the support of SWM.
 *	е TSM has to be reentrant. There are many cases where TSM trap is called from
 *	within itself.
 *	******************************************************************************** */

#ifndef __TSMPrivate__
#define __TSMPrivate__

#include	<TextServices.h>
#include	<ExpandMemPriv.h>

#ifndef __FILES__
	#include <Files.h>
#endif

#ifndef __LAYERS__
#include <LAYERS.h>
#endif



/* AE event ID (used by SWM only ... */

#define		kCloseSWMWindow			((short)6001)					/* Close SWM Window */
#define 	kAppleEventParams		((short)6000)					/* pass SWM an AppleEvent */

typedef struct SWMparams {
	union {
		struct {
			AppleEvent	*IncomingAppleEvent;
			AppleEvent	*ReplyAppleEvent;
		} aeStruct;
		EventRecord		*event;
	} u;
} SWMparams;
		



#define		kNoSuchScript		(ScriptCode) 0xFFFF		/* there is no such script code */

#define 	ExpanMem			(*(ExpandMemRec **)(0x2B6))

#define		TSMTEInterfaceType	'tmTE'					/* private type for Japanese	<17Jun93 #39> */


/*	**********************************************************************************************	*/


/* messages to TSM ... */

#define	kMsgNoOP				0			// no op						(parameter is ignored)
#define	kMsgBkgAppsPSN			1			// background application's PSN (parameter = SWM's ProcessSerialNumberPtr)
#define	kMsgKillTSMApp			2			// kill TSM aware application	(parameter = ProcessSerialNumberPtr)
#define	kMsgChangeToOldJIM		3			// switch to old Japanese Input Method (parameter = scriptID record pointer)
#define	kMsgSuspendApp			4			// a non-TSM aware app got suspended
#define	kMsgResumeApp			5			// resume a non-TSM aware app
#define	kMsgHelpHELPMgr			6			// open Component's resource file for Help Mgr


typedef struct {							/* parameter for kMsgChangeToOldJIM */
	ScriptCode		sidScript;				/* script of this old input method  */
	short			sidFEPID;				/* FEP ID */
}	ScriptIDRecord, *ScriptIDRecordPtr;

#define	kMaxMsgNumber			kMsgHelpHELPMgr


#define	kTSMSuspend				0			// suspend the app
#define	kTSMResume				0xFFFF		// resume  the app


/*	Private TSM traps ...
	The last selector is kFindServiceWindow = 23 as defined in TextServices.h ...	*/
	
#define	kInformTSM				22			// inform TSM
#define	kNewTSMDocument4SWM		24			// create new TSM aware document but don't activate input method <#17> <#19>
#define	kTSMEventFromSWM		25			// TSM event called by SWM					<#35>


#define	kMaxTSMSelector			kTSMEventFromSWM				//						<#35>

pascal OSErr NewTSMDocument4SWM(short numOfInterface, OSType supportedInterfaceTypes[], TSMDocumentID *idocID)
= { 0x303C,kNewTSMDocument4SWM, TSMTrapNum };

pascal Boolean TSMEventFromSWM(EventRecord *eventPtr)			// new call for SWM		<#35>
= { 0x303C,kTSMEventFromSWM, TSMTrapNum };

pascal OSErr InformTSM(short msgNumber, void *msgParamPtr)	 			// clean up TSM aware app.
= { 0x303C, kInformTSM, TSMTrapNum };


/*	ее ******************************************* ее  */




/* resource type for default input method saved in System file */
/* (if you change something in here, be sure to change TSMPrivate.a too !) */

#define	kTSMDefInputMethodType		kInputMethodService
#define	kTSMDefInputMethodID		-8192

#define	kSavedDefaultIMCount		4					/* CCJK, 4 scripts */
#define	kINPMresourceSig			'tsmr'				/* signature of the saved default IM resource in system file */

#define		kUseOldJapaneseIM			-1000			// moved from public to private


/*	Each saved input method has a record with the following info ... */
/*	if imUseOldInputMethodP is true,  then imOldInputMethodID contains the FEPID,	-- <06Feb92 #9>
	if imUseOldInputMethodP is false, then imOldInputMethodID is undefined.			-- <06Feb92 #9>
	If imValidP == true, and imUseOldInputMethodP == false, then imCDRec contains a valid CD.		*/

typedef struct {
	Boolean					imValidP;					/* true if record contains valid info */
	Boolean					imUseOldInputMethodP;		/* true if user wants to use old input method as the default <#9> */
	short					imOldInputMethodFEPID;		/* if imUseOldInputMethodP is true, then this is its FEP ID	 <#9> */
	LangCode				imLanguage;					/* language code for the script */
	ComponentDescription	imCDRec;					/* component description */
} IMSRecord;


/* default input method information resource */

typedef struct {
	long			defRsrcSignature;						/* TSM resource signature = 'tsmr' */
	Boolean			defUseFloatWindow;						/* global falg - not used anymore! */
	char			defReserved;							/* not used (should be 0) */
	short			defIMCount;								/* number of input methods saved = 4 scipts */
	IMSRecord		defIMRecordArray[kSavedDefaultIMCount];	/* array of IM. Script records */
} DefIMRecord, *DefIMRecordPtr, **DefIMRecordHandle;
/*	**********************************************************************************************	*/


/* default IM's Component and menu */
typedef struct {
	Component		gComponent;
	MenuHandle		gMenuHandle;
} ComponentMenuRec;

/* constants (mask) for our patch flags */

#define	kIMJustSetCursor			(0x01)
#define	kSWMJustSetCursor			(0x02)
#define	kInTSMEventCall				(0x04)				// set when inside of TSMEvent call
#define	kInTSMPopUpMenuSelectCall	(0x08)				// set when inside of popupmenuselect call
#define	kTSMEventBeenCalled			(0x10)				// set by _ModalDialogPatch in SWM, reset in TSMEvent



/* ее TSM globals ...
 *
 * (if you change something in here, be sure to change TSMPrivate.a too !)
 * tsmPreviousDocID  -- contains the TSM doc ID which we just deactivated, but its pallete/menu has not been removed.
 * tsmPreviousScript -- contains the script when we deactivated the document above. If tsmPreviousDocID is nil, then
 *						the value of tsmPreviousScript is undefined.
 * For a TSM aware application, usually tsmUseInputWindowDoc = tsmActiveDocID = current active document,
 * but if this app calls UseInputWindow, then	tsmUseInputWindowDoc = current active document, and
 *												tsmActiveDocID		 = SWM's document.
 */

#define	kDebugSignature			0x4B534354				// for debugging

typedef short (*doAppleEventCallBack)( short refnum, AppleEvent *theAppleEvent,AppleEvent *theReply);
typedef OSErr (*doCloseSWMWindowCallBack)(short refnum, Boolean flushBufferP);

typedef struct {										// ее TSM globals
	short						tsmRecSize;				// short
	Ptr							tsmIAPSNTablePtr;		// ptr to table of TSM aware application process serial numbers
														// defined in TSMPrivate.a and accessed thru Assembly code only
	ScriptLanguageRecord		tsmCurrentSLRec;		// current Script/Language
	TSMDocumentID				tsmPreviousDocID;		// previous deactivated doc ID, which pallete has not been removed	<#24>
	ScriptCode					tsmPreviousScript;		// the script which is running when we deactivate the ID above		<#24>
	TSMDocumentID				tsmActiveDocID;			// the current active TSM document if non-nil
	TSMDocumentID				tsmUseInputWindowDocID;	// the current document which is using the input window		<#35>
	unsigned char				tsmActiveTSCount;		// number of active text services for ease of debugging.	<#7>
	Boolean						tsmPMgrActiveP;			// true if Process Manager is active
	Boolean						tsmUseOldJInputMethodP;	// true if we are using the old Japanese Input Method
	Boolean						tsmKillApplicationP;	// true if we are killing the TSM aware application (set by InformTSM)
	ProcessSerialNumber			tsmSWMsPSNRecord; 		// background app's (SWM) PSN
	ProcessSerialNumber			tsmCurrentPSNRecord; 	// current app's PSN										<#26>
	ComponentMenuRec			tsmDefIMInfoTable[kSavedDefaultIMCount];	// current default I.M. of the system
	ComponentInstance			tsmCacheInstance;		// this instance map ...									<#21>
	long						tsmCacheRefcon;			// ... to this refcon										<#21>

	short						tsmSWMDrvrRefNum;		// RefNum of driver, this is set by DoubleTalk INIT
	doAppleEventCallBack		tsmSendAEProc;			// send appleevents to SWM driver, set by the driver itself
	doCloseSWMWindowCallBack	tsmCloseSWMWindowProc;	// tell driver to close its window, set by the driver itself	
	unsigned char				tsmPatchFlags;
	char						tsmFiller;				// word align
	short						tsmRealSystemMenuID;	// IM menu ID before we map to -16500						<#34>
	long						tsmUserProc;			//															<#34>

	long						tsmPopUpReturnAddr;		// save return address for PopupMenuSelect					<#39>
	unsigned char				tsmMajorVersion;		// major version number										<#35>
	unsigned char				tsmMinorVersion;		// minor version number										<#35>
	long						tsmDebugSignature;

} TSMVarsRec;
/*	**********************************************************************************************	*/


struct CIListRec {									// for each open component, we have ...
	struct CIListRec		*ciNextCIListRec;
	Component				ciTheComponent;			// a saved component
	ComponentInstance		ciTS;					// a component instance
	ScriptLanguageRecord	ciSLRecord;				// the primary script/language
	Boolean					ciTakeActiveInputP;		// set if take active input
	Boolean					ciMenuVisibleP;			// true if the menu is visible
	MenuHandle				ciServiceMenu;			// an associated menu or nil
};
typedef struct CIListRec CIListRec;


/* a record to save the open default input method. Used in TSM document record... */
typedef struct {
	Component				openedDefIMComponent;		// a saved input method component
	ComponentInstance		openedDefIMCInstance;		// a saved input method component instance for the open component
	MenuHandle				openedDefIMServiceMenuHdl;	// an associated menu handle or nil
	Boolean					openedDefIMMenuVisibleP;	// true if the menu is displayed in the menu bar
	Boolean					openedDefIMActiveP;			// true if the IM is active
	short					openedDefIMReserved;		// so that the record total size is 16 bytes
} DefIMInstanceRecord;



/* TSM document record, this handle is used as TSM document ID */
/* (if you change something in here, be sure to change TSMPrivate.a too !) */

typedef struct {
	long					iDocSignature;				// signature for verifying the ID
	short					iDocOpenTextServiceN;		// number of open text services (excluding input methods)
	CIListRec				*iDocCIHead;				// list of open text service Component Instances
	ProcessSerialNumber		iDocPSNRecord;
	Boolean					iDocActiveP;				// true if document is active
	Boolean					iDocUseInputWindowP;		// true if this doc is using Input Window (local flag)
	long					iDocRefcon;					// refcon									<#21>
	ScriptCode				iDocUseThisScript;			// the script used by this document			<#24>
	long					iDocGhostSignature;			// for TSM aware app. that has no document	<#38>
	DefIMInstanceRecord		iDocDefIMInstanceArray[kSavedDefaultIMCount];	// see def. above
	short					iDocInterfaceN;				// number of supported interface types
	OSType					iDocOSTypeArray[1];			// more than 1 record might follow
} TSMDocRecord, *TSMDocRecordPtr, **TSMDocRecordHandle;

#define	kTSMDocumentSignature	'TDOC'					// valid  document ID signature
#define	kTSMShadowDocumentSig	'SDOC'					// shadow document ID signature (a temp copy for utCleanUpPreviousDoc)
#define	kTSMGhostSignature		'GHOS'					// ghost  signature (used by SWM)			<#38>

/* used in "xDeleteTSMDocument", the meaning of a shadow ID are:
 *	1. The real ID has been deleted.
 *	2. This handle is from system heap. And is just a copy of the real ID.
 *	3. Instance has been closed, openedDefIMCInstance does not mean anything even it is not nil !!!
 *	4. The size of the handle is always the sizeof(TSMDocRecord).
 */
 

/*	**********************************************************************************************	*/



/* one record for each TSM aware application ... */

typedef struct {
	ProcessSerialNumber	psnIDRecord;				// long (OH! How I hated to use 64 bits PSN)
	Boolean				psnAppUseInputWindowP;		// byte, set if app should use floating input window
	Boolean				psnDocUseInputWindowP;		// byte, set if current document is using floating input window
	Boolean				psnTSMCalledUseIWP;			// byte, true if TSM called UseInputWindow when there is no ducument	<#39>
	Boolean				psnOldUseIWGlobalState;		// byte, the global state before TSM called UseInputWindow				<#39>
	Ptr					psnDocsTablePtr;			// long, open documents table pointer (to DocumentTable)
} TSMAppsRecord;




/* table of open documents stored in TSM's PSN table */

typedef struct {
	short			docIDCount; 			// (word) number of IDs recorded
	short			docTableEntryN; 		// (word) total number of entries (size) of the table
	TSMDocumentID	docIDStart[1];			// (long) start of doc IDs
} DocumentTable;



/*	**********************************************************************************************	*/



/* How input methods are synchronized with the keyboard menu .....

TSM global	->	+---------------------------+	(tsmDefIMTable)
				| S. Chinese IM	Component	|	Updated by 'SetDefaultInputMethod'
				|---------------------------|
				| Japanese   IM Component	|	Updated by 'SetDefaultInputMethod'
				|---------------------------|
				| T. Chinese IM	Component	|	Updated by 'SetDefaultInputMethod'
				|---------------------------|
				| Korean	 IM	Component	|	Updated by 'SetDefaultInputMethod'
				|---------------------------|
				| tsmCacheInstance			|	cached instance
				|---------------------------|
				| tsmCacheRefcon			|	cached refcon
				+---------------------------+
				| Current Script/Language	|	Updated by 'SetTextServiceLanguage' & 'SetDefaultInputMethod'
				+---------------------------+
	+---------	| tsmIAPSNTablePtr			|	Points to a table of TSM aware applications
	|			+---------------------------+
	|			| Other TSM globals			|
	|			+---------------------------+
	|
	|		(User selected default input methods for CJK script)
	|		(A copy of this data is also saved on disk in 'inpm' resource)
	|
	|
	|
	|
	+-------->	+---------------------------+
				| iaAppCount				|	number of Inline aware application registered
				+---------------------------+
				| iaTableEntryN				|	total number of entries (size) of the table
-+----------+--	+---------------------------+
 ^			|	| psnHighID					|	long, (OH! How I hated to use 64 bits PSN)
 |			|	|---------------------------|
 |			|	| psnLowID					|	long, process serial number
one			|	|---------------------------|
application	|	| psnAppUseInputWindowP		|	byte, set if app should use floating input window
space		|	|---------------------------|
 |			|	| psnDocUseInputWindowP		|	byte, set if current document is using floating input window
 |			|	|---------------------------|
 |			|	| psnTSMCalledUseIWP		|
 |			|	|---------------------------|
 |			|	| psnOldUseIWGlobalState	|
 |			|	|---------------------------|
 |	+-------+-	| psnDocsTablePtr (or NIL)	|	long, open documents table pointer (table of document IDs)
 v	|		|	| (initially nil)			|	(this table can be nil, so check it before use. Once allocated, will be reused)
-+--|-------+--	+---------------------------+
	|		|	| psn record 2				|	recorded when an app calls InitTSMAwareApplication
	|		+--	+---------------------------+
	|		|	| psn records ....			|
	|		+--	+---------------------------+
	|			
	|
	+-------->	+---------------------------+
				| docIDCount				|	number of documents created by this app
				+---------------------------+
				| docTableEntryN			|	total number of entries (size) of the table
				+---------------------------+
				| TSMDocumentID 1			|	recorded document ID
				+---------------------------+
				| TSMDocumentID .....		|	
				+---------------------------+
				| TSMDocumentID N			|	recorded document ID
				+---------------------------+




TSM document record :

	DocID	-->	+---------------------------+
				| iDocSignature				|	signature to verify the ID
				+---------------------------+
				| iDocOpenTextServiceN		|	number of open text services (excluding input methods)
				+---------------------------+
		+-----	| iDocCIHead				|	pointer to a list of open text services
		|		+---------------------------+
		|		| iDocPSNRecord				|	process which created this document
		|		+---------------------------+
		|		| iDocActiveP				|	true if the document is active
		|		+---------------------------+
		|		| iDocUseInputWindowP		|	true if this doc is using Input Window
		|		+---------------------------+
		|		| iDocRefcon				|	refcon								<#24>
		|		+---------------------------+
		|		| iDocUseThisScript			|	script used by this document		<#24>
		|		+---------------------------+
		|		| S. Chinese IM	Component	|	this must matches with TSM global when the document is activated ...
		|		| Component Instance 		|	= nil if Component is not open
		|		| Menu Handel & flags		|	Handle = nil if IM has no menu
		|		+---------------------------+
		|		| Japanese  IM Component	|
		|		| Component Instance 		|	Opened when the document is activated and the current keyscript is Japanese
		|		| Menu Handel & flags		|
		|		+---------------------------+
		|		| T. Chinese IM	Component	|
		|		| Component Instance 		|
		|		| Menu Handel & flags		|
		|		+---------------------------+
		|		| Korean	IM	Component	|
		|		| Component Instance 		|
		|		| Menu Handel & flags		|
		|		+---------------------------+
		|		| iDocInterfaceN			|	number of supported interface types
		|		+---------------------------+
		|		| iDocOSTypeArray			|	interface types
		|		+---------------------------+
		|
		|	(Currently opened input methods used by the document)
		|
		|
		|
		|
		+---->	+---------------------------+			+-------------------+
				| ciNextCIListRec			|	----->	| next CIListRec	|	---> ..... ---> ||
				|---------------------------|			+-------------------+
				| ciTheComponent			|	a saved component of the text service
				|---------------------------|
				| ciTS						|	the component instance
				|---------------------------|
				| ciSLRecord				|	the primary script/language
				|---------------------------|
				| ciTakeActiveInputP		|	set if take active input
				|---------------------------|
				| ciMenuVisibleP			|	true if the menu is visible
				|---------------------------|
				| ciServiceMenu				|	an associated menu or nil
				+---------------------------+
	
			(document ID is a handle to decument record. In the record,
			 I keep a linked list of open text services. Input method is not in the list)




	ее When do we call RouteEventToSWM?
	
		We call RouteEventToSWM in 4 places: 
				TSMUtility.c		--	xSetTextServiceLanguage, xSetDefaultInputMethod, 
				TSMInternalUtils.c	--	utChangeToOldJIM, utInformPMgr.

		RouteEventToSWM(false) tells Process Manager do not send events to SWM.
		This may because:
			a. The current app is TSM aware, or
			b. The current script does not need input method, or
			c. The current script is Japanese but we are using old JIM.
		
		The corresponding flag used by Process Manager is called "routeEvent".
			

	**********************************************************************************************	*/







/*	********************************************************************************
 *	This constant is temporarily defined, nobody knows its exact definition yet.
 *	********************************************************************************/
#define	kTextServiceKind			(0x4000)


#define kTSMSystemMenuID			(16500)

enum {
	ApplicationMenuList = 0xA1C,
	SystemMenuList = 0x286
};
#define	kComponentNameLength		256






/* *********************************************************************************************	*/

/* prototypes ... */

// TSMFunctions.c ....

pascal OSErr	xNewTSMDocument(short numOfInterface, OSType supportedInterfaceTypes[], TSMDocumentID *idocID, long refcon);
pascal OSErr	xDeleteTSMDocument(TSMDocumentID idocID);
pascal OSErr	xDeactivateTSMDocument(TSMDocumentID idocID);
pascal OSErr	xActivateTSMDocument(TSMDocumentID idocID);
pascal Boolean	xTSMEvent(EventRecord *eventPtr);
pascal Boolean	xTSMMenuSelect(long menuResult);
pascal OSErr	xFixTSMDocument(TSMDocumentID idocID);
pascal Boolean	xSetTSMCursor(Point mousePos);
pascal OSErr	xGetServiceList(short numOfInterface, OSType supportedInterfaceTypes[], 
				TextServiceListHandle *serviceInfo, long *seedValue);
pascal OSErr	xOpenTextService(TSMDocumentID idocID, Component aComp, ComponentInstance *aCompInstance);
pascal OSErr	xCloseTextService(TSMDocumentID idocID, ComponentInstance aCompInstance);
pascal OSErr	xSendAEtoClient(AppleEvent	*theAppleEvent, AppleEvent		*reply, 
						AESendMode			sendMode,		AESendPriority	sendPriority,
						long				timeOutInTicks,	IdleProcPtr		idleProc,
						EventFilterProcPtr	filterProc );


// TSMUtility ...

pascal OSErr	xSetDefaultInputMethod ( Component aComp,	ScriptLanguageRecord *slRecPtr );
pascal OSErr	xGetDefaultInputMethod ( Component *ts,		ScriptLanguageRecord *slRecPtr );
pascal OSErr	xSetTextServiceLanguage( ScriptLanguageRecord *slRecPtr );
pascal OSErr	xGetTextServiceLanguage( ScriptLanguageRecord *slRecPtr );
pascal OSErr	xUseInputWindow( TSMDocumentID idocID,		Boolean useFloatWindow );
pascal OSErr	xNewServiceWindow(void				*wStorage,
								const Rect			*boundsRect,
								ConstStr255Param	title,
								Boolean				visible,
								short				theProcID,
								WindowPtr			behind,
								Boolean				goAwayFlag,
								ComponentInstance	ts,
								WindowPtr			*window );
pascal OSErr	xCloseServiceWindow(WindowPtr window );
pascal OSErr	xGetFrontServiceWindow(WindowPtr *window );
pascal short	xFindServiceWindow(Point thePoint,WindowPtr *theWindow);

OSErr utJustDeactivateIM4Document( TSMDocumentID theDocID,	ScriptCode	theScript, Boolean	stillActiveP );


// TSMDispatch.a (functions start with "uta") ...

OSErr			utaRecordDocumentID();
OSErr			utaRemoveDocumentID();							/* remove the ID */
void			utaUpdatePSNTable();
void			utaUpdateDocFlagInPSNTable();
OSErr			utaUpdateAppFlagInPSNTable();

pascal	OSErr	utaIsAppTSMAwareAndNotUsingIW(ProcessSerialNumber	*PSNRecord);
pascal	OSErr	utaGetTSMAwareDocTable  	(ProcessSerialNumber	*PSNRecord, DocumentTable	**docTablePtr);
pascal	OSErr	utaGetAppsUseInputWindowFlag(ProcessSerialNumber	*PSNRecord, Boolean			*UseInputWindowPtr);
pascal	OSErr	utaGetTSMAppRecordPtr		(ProcessSerialNumber	*PSNRecord, TSMAppsRecord	**appRecordPtr);

// TSMInternalUtil.c ...


OSErr	utVerifyTSMDocID		(TSMDocumentID			idocID);
void	utAppendTS2Document		(TSMDocRecord 			*idocRecPtr,	CIListRec		*theListRecPtrToAppend);
OSErr	utMakeRoom4SInfoHandle	(TextServiceListHandle	serviceInfoHandle, int			pos);
OSErr	utActivateIM4Document	(TSMDocumentID			theDocID,		ScriptCode		theScript);
OSErr	utDeactivateIMforDocument(TSMDocumentID			theDocID,		ScriptCode		theScript,	Boolean		theHideFlag);
OSErr	utCloseIM4Document		(TSMDocumentID			theDocID,		ScriptCode		theScript,	Boolean		theHideFlag);
OSErr	utOpenIM4Document		(TSMDocumentID			theDocID,		Component		theComponent,
								 ScriptCode				theScript,		Boolean			activateP);
OSErr	utOpenActivateDefaultIM	(TSMDocumentID			activeDocID,	Boolean			activateP);
OSErr	utActivateThisDocsInputMethod(TSMDocumentID		idocID);
Boolean	utSupportedSL			(ScriptLanguageRecord	*slRecPtr);
Boolean	utScriptIsNotCCJK		(ScriptCode				script);
Boolean	utScriptIsCCJKAndNeedsIM(ScriptCode				script);
void	utInformPMgr();
Boolean	utDocNeedsInputMethod	(ScriptCode				script,			ProcessSerialNumber		*PSNRecordPtr);
OSErr	utGetTSMDefaultInputMethod(ComponentDescription	*cdPtr,			ScriptLanguageRecord	*slRecPtr);
OSErr	utUpdateDefaultInputMethodResource (Component	aComp,			ScriptLanguageRecord	*slRecPtr);
int		utGetScriptIndex		(ScriptCode				script);
unsigned long	utSLRec2CompFlag(ScriptLanguageRecord	*slRecPtr);
OSErr	utChangeToOldJIM		(ScriptIDRecordPtr		sidrecptr);
OSErr	utAddTSMResource		(DefIMRecordHandle		*theHandlePtr);
void	utCloseSWMWindow		(Boolean				FlushBufferP);							/* 24Jun92 */

void	utDeleteMenu(short menuID);
void	utDeleteAppsMenu(short menuID);
void	utDeleteSysMenu(short menuID,					long	systemScript);
void	utFixDocumentAndCloseSWMWindow(ScriptCode		deactivateScript);
void	utCleanUpPreviousDoc(TSMDocumentID				theNewDocID,	ScriptCode				theNewScript);

OSErr	utSuspendResumeApp	(short	flag);
THz		utSwapZone( THz zone );
Boolean utBadSandL(ScriptLanguageRecord	*slRecPtr);		/* <#32> */



/* ****************************************************************************	*
 * Macro:  utSoftDeactivateIM4Document											*
 *		Deactivate the input method of the current script for this document.	*
 *		Only deactivate the instance. The instance is not closed.				*
 *		And pallete/menu are not removed.										*
 * Macro:  utForceDeactivateIM4Document											*
 *		Deactivate the input method of the current script for this document.	*
 *		Only deactivate the instance. The instance is not closed.				*
 *		And pallete/menu will be removed.										*
 * ее	Warning:1. No error checking on the doc ID !!							*
 *				2. theScript is one of the CCJK scripts.						*
 * ****************************************************************************	*/
#define	utForceDeactivateIM4Document(id, script)		utDeactivateIMforDocument(id, script, true)
#define	utSoftDeactivateIM4Document(id,  script)		utDeactivateIMforDocument(id, script, false)


#endif