/*
	File:		XPT.c

	Contains:	routines that implement the CAM Transport layer

	Entry points:
		OSErr	SCSITrap (short scsiSelector, SCSI_PB *pbPtr )
			Single entry point (Jerry's _NewSCSI trap).  Uses scsiSelector to choose a routine
			from those shown below.
		
	Client Calls
		void	SCSIAction (SCSI_PB *, Boolean syncCall, void (*callback)())
		SCSI_PB *NewSCSI_PB (void)
		void	DisposeSCSI_PB (SCSI_PB *)
			
	OS Module Calls
			
		OSErr	InitSCSIMgr ()
		
		long	SCSIRegisterBus (SIMinitInfo * SIMinfo)
			Called to register a SCSI bus for use with the XPT. 
			Several characteristics of the Bus are specified as well as the software
			entry points and the number of bytes required for a static data space
			(for global variables).  The XPT returns a BusID that will be used for
			that Bus as well as a pointer to the allocated static space.
			SIMinitInfo is defined as shown:
			
			typedef struct { // directions are for SCSIRegisterBus call ( -> parm, <- result)
				long	staticSize;			// -> num bytes SIM needs for static vars
				void	(*SIMinit)();		// -> pointer to the SIM init routine
				void	(*SIMaction)();		// -> pointer to the SIM action routine
				Boolean	oldCallCapable;		// -> T if this SIM can handle old-API calls
				ushort	busID;				// <- bus number for the registered bus
				char *	SIMstaticPtr;		// <- alloc. ptr to the SIM's static vars
			} SIMinitInfo; 
			
		

		OSErr	SCSIDeregisterBus (ushort busID)
		
		void	SCSIAsyncEvent (long what, 
								ushort busID, 
								ushort targetID, 
								ushort lun, 
								long dataBfr, 
								long dataCnt)
		
	Written by:	Paul Wolf

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SM33>	  2/1/94	DCB		Making sure our busy patch version gets set.
	  <SM32>	 1/31/94	DCB		Fixed a bug in the way I checked the version number for the SCSI
									Busy patch.
	  <SM31>	 1/25/94	DCB		Getting rid of compiler warning.
	  <SM30>	 1/25/94	DCB		Don't block interrupts when polling since this screws up
									interrupt latency and besides we have the file system patches
									now.
	   <ML4>	  1/9/94	pdw		Added check for SCSIBusyPatch version number so that init can
									run and only patch when necessary.
	   <ML3>	  1/5/94	pdw		Converted SCSIGlobal uses to new format and rolled in new
	   								SCSIBusy Patch.
	   <ML2>	12/15/93	pdw		Checking in for the build.
	  <SM28>	12/19/93	DCB		Poll at all interrupt levels now since we might have a deferred
									task pending but not an interrupt.  Also block interrupts at
									level 2 if not already blocked so we don't get re-entered when
									we don't expect it.  This won't crash the SCSI Manager but could
									lead to calling a completion routine when syncUnsafe is non-zero
									which causes file system headaches until SCSI Busy gets fixed.
	  <SM27>	11/22/93	pdw		Rolling in from <MCxx>.
	   <MC7>	11/11/93	pdw		Added support back in for forceSyncAlways debugging.
	   <MC6>	11/10/93	pdw		Added forceSync functionality which is used only when inDebugger
									and interrupts are blocked.  This fixes the hang using Macsbug
									log which was caused by the FSCallAsync-always change to the
									File System.
	   <MC5>	 11/5/93	pdw		Series of attempts and re-attempts to fix various VM/FileShare
									problems.
	  <SM26>	10/29/93	DCB		<MC> roll-in.
	   <MC4>	10/28/93	pdw		Added fix: we didn't use to return the result in D0 in
									synchronous requests like we were supposed to.  Now we do.
	  <SM25>	10/14/93	pdw		<MC> roll-in.
	   <MC3>	10/12/93	pdw		Added support for Synchronous data transfers, rewrote State
									Machine, message handling etc.
	   <MC2>	 9/26/93	pdw		Had to add a header file because of changes elsewhere.
	  <SM24>	 9/12/93	pdw		Removed SIMRegisterHAL support. Check for nonzero staticSize
									before allocating globals for SIM. Fixed up the reregister stuff
									a bit - moved common register/reregister stuff into sepearate
									routine.  Added ability to alloc new SIM globals in Reregister.
	  <SM23>	  9/9/93	pdw		Lots of little changes.  Name changes, temporary cache_bug
									stuff.
	  <SM22>	 8/13/93	pdw		Added check for nonZeroStatus to see if CallComp should do a
									virtual ID mapping.
	  <SM21>	 7/17/93	pdw		Lots of little things.
	  <SM20>	  7/8/93	pdw		Adding record events around Inquiry, GetVirtualID and Create
									Xref calls.
	  <SM19>	  7/1/93	pdw		Fixed RemoveRefNum bug where it would always return an error.
									We now "return" after setting up the noErr return value.
	  <SM18>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
									stack switching mechanism.  Adding support for Cold Fusion.
									Rearranging HW/SW Init code. Some code optimizations.
	  <SM17>	 5/29/93	PW		Adding SCSIDebug.h to includes.
	  <SM16>	 5/25/93	DCB		Rollin from Ludwig. (The next item below)
	  <LW15>	 5/20/93	DCB		Added call to ciDebuggerPatch. This is a patch to _DebugUtil
									which prevents deferred completion routines from occuring when
									we are in a debugger.
	  <SM15>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	  <LW14>	  5/1/93	PW		Added check for non-zero QLink to allow clients to see if we
									support pre-linked requests. Changed one last name:
									SCSI_RegisterWithNewXPT.
	  <LW13>	 4/30/93	DCB		Remove InitXPTRecorder if recording is turned off.
	  <LW11>	 4/14/93	DCB		Added ReRegisterAll Sims and fixed several bugs in the
									re-register SIM call.  This allows us to install a new XPT at a
									later date.
	  <LW10>	 4/13/93	MB		(Really DCB) Fixing sign extension problem in GetRefNum.
	   <LW9>	 3/26/93	PW		Rolling in SuperMario changes. Removing useless RejectMsg stuff.
									Changed refNumXref stuff to use -1 in bus field instead of -1 in
									whole device ident as magic value.
	  <SM13>	 3/20/93	PW		Removing EnableUserCode/DisableUserCode calls from
									CallCompRoutine, SIMAction… - leaving it up to the SIM to do 
									these calls instead (if necessary for that SIM).
	   <LW8>	  3/1/93	DCB		Changed parameters to CallCompRoutine to make life easier for
									developers.
	   <LW7>	 2/17/93	PW		Adding forceSyncAlways stuff (from PDM) because it will be
									useful for running benchmarks.
	  <SM12>	  2/4/93	PW		Enabled BusInquiry on PDM.  Fixed forceSync stuff by making
									callback from XPTAction.
	  <SM11>	 1/31/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <LW6>	 1/30/93	PW		Added glue code for calling completion routines (saving
									registers that were getting trashed by File Manager).
	   <LW5>	 1/27/93	PW		Added clear of diReserved in GetRefNum.
	   <LW4>	 1/27/93	PW		Removed "fix" for 'double completion on autosense" bug. Fixed it
									a much better way in CompAutoSense (a way that works).
	   <LW3>	 1/12/93	DCB		Added enable and disable user code calls around calls to
									completion routines to allow page faults in the completion
									routines.
	   <LW2>	  1/8/93	PW		Adding Disable/Enable user code calls around call to completion
									routine to fix async comp -> old-API deadlock bug. Added ISRs 8
									through 0x0F to complete the set. Removed explicit Quadra int
									support from DispatchISR.
	  <SM10>	 12/9/92	PW		Got rid of selective DoVirtualMap stuff. Now we always do the
									mapping.
	   <SM9>	 12/5/92	PW		Handle returned fail from CallSIMaction. Added SetAsyncCallback
									partial support. Changed RefNum function names. Added
									InterleaveFactor support. Added check for invalid bus num in
									CallSIMaction.
	   <SM8>	11/20/92	PW		Added some Includes that were removed from headers. Changed
									InitXPT & XPTregBus to reflect change from linked list of
									BusInfos to array. Removed DItoBus macro. Added maxbuses (16)
									restriction to XPTregBus. Added error checking. Added init of
									new fn ptrs to SIMinfo.  Made Abort,Term,Reset async callbacks
									work. Changed sync from scSync flag to scComp=0. Removed
									EngineInq, Setup & DecodeDI. Removed calling of CompFn on XPT
									errs. Filled out XPT_ISR2 & 3.
	   <SM7>	 11/1/92	DCB		Fixed finalStatus length bug in CallCompRoutine that was
									stripping off the top byte of the scsiResult.
	   <SM6>	10/30/92	DCB		Changed over to multiple ISR routines for improved efficiency
	   <SM5>	 10/8/92	PW		Added variable-sized SCSI_IO support.  Lots of trivial name
									changes.
	   <SM4>	 9/17/92	PW		Added check for function code not supported.
	   <SM3>	 9/14/92	DCB		Added some Parameter Block validation.
	   <SM2>	  8/1/92	PW		Added comments.

*/


#include <Types.h>
#include <Memory.h>
#include <OSUtils.h>
#include <Errors.h>
#include <SCSIStandard.h>
#include <SCSI.h>
#include <Slots.h>
#include <Start.h>


#include "CUtils.h"

#include "ACAM.h"
#include "SCSIDebug.h"
#include "SCSIGlue.h"
#include "BootItt.h"			// for IsItt

#include "XPT.h"
#include "XPTpriv.h"

#include "Recorder.h"

#ifdef TESTGLOBALS
extern short	testGlobal3;
extern short	testGlobal2;
extern short	testGlobal1;
#endif

#define GetVBLQHdr() ((QHdrPtr) 0x0160)
#define inVBL 6

// ************ Internal-only Function Prototypes **************

void	SetRefNum( SCSI_Driver_PB *, XPTglobals * );
void	GetRefNum( SCSI_Driver_PB *, XPTglobals * );
void 	RemoveRefNum( SCSI_Driver_PB *, XPTglobals * );

OSErr	ReRegisterAllSIMs( XPTglobals *);
OSErr	XPTRegisterBus( SIMinitInfo * SIMinfo, XPTglobals *XPTg );
OSErr	XPTDeregisterBus( ushort busID, XPTglobals *XPTg );
OSErr	XPTReregisterBus( SIMinitInfo * SIMinfoPtr, XPTglobals *XPTg);
void	XPTRegisterCommon( SIMinitInfo * SIMinfoPtr);
OSErr	XPTKillXPT( XPTglobals *XPTg);

void	SyncWait( SCSI_PB *pbPtr, XPTglobals *XPTg );

void	TryToRecover ( XPTglobals *XPTg);
OSErr	XPTAction( SCSI_PB *pbPtr, XPTglobals *XPTg );
Boolean OldSCSIExists( void);

void	InitXPTRecorder( long sizeOfTape );

void	XPT_ISR0(void);
void	XPT_ISR1(void);
void	XPT_ISR2(void);
void	XPT_ISR3(void);
void	XPT_ISR4(void);
void	XPT_ISR5(void);
void	XPT_ISR6(void);
void	XPT_ISR7(void);
void	XPT_ISR8(void);
void	XPT_ISR9(void);
void	XPT_ISRa(void);
void	XPT_ISRb(void);
void	XPT_ISRc(void);
void	XPT_ISRd(void);
void	XPT_ISRe(void);
void	XPT_ISRf(void);


/*********************************************************************************
	InitXPT	-	Initialize XPT Globals and stuff
*********************************************************************************/

OSErr	
InitXPT( void )
{
	XPTglobals	*XPTg;

	
#ifdef TESTGLOBALS
	short	testG;
	testG = testGlobal3;
	testG = testGlobal1;
#endif

	InitRecorder();

// This gets a bit complicated if there is already a XPT installed.  If there is
// then we need to manage the transition from the old one to the new one.  This
// is accomplished by the routine ReRegisterAllSIMs:
//

// Allocate room for XPT globals and store XPTg ptr in magic spot in SCSIGlobals

	XPTg = (XPTglobals *) NewPtrSysClear( sizeof(XPTglobals));		//&&&& NewPtrSysClear
	if (XPTg == nil)
		return (memFullErr);

// Build Driver List (for RefNum to DeviceIdent cross-ref)
	
	XPTg->Drivers = (DrvrList *) NewPtrSysClear( sizeof(DrvrList));

	if ( XPTg->Drivers == nil ) {
		DisposPtr( (Ptr)XPTg);
		return (memFullErr);
	}
	
	XPTg->Drivers->DrvrCnt = 0;

// Initialize static fields in the completionDT

	XPTg->completionDT.qType = dtQType;
	XPTg->completionDT.dtAddr = DeferredCall;
	
	if ( ISITT() ) {
		// Let the old instantiation of KillXPT know what version of busyPatch we currently use.
		// It will compare this against its own linked in value and remove its patch if they
		// aren't the same.
		SCSIGlobals->newBusyPatchVers = kbusyPatchVers;
	
		if( ReRegisterAllSIMs(XPTg) )
			return(memFullErr);
	}
	else if ( OldSCSIExists() ) {
		XlateOldSCSIGlobals( XPTg );	// if New is replacing Old SCSI Mgr, xlate old's globals
	}

	Init_SCSIXlate();
	InitXPTAsm();
	
	if( (XPTg->debugPatch = ciDebuggerPatch( (Ptr) NGetTrapAddress( _DebugUtil, OSTrap ))) != nil )
		NSetTrapAddress( (long) XPTg->debugPatch, _DebugUtil, OSTrap );
	
	if (SCSIGlobals->busyPatchVers != kbusyPatchVers) {
		if( (SCSIGlobals->busyPatch = ciBusyPatch( (Ptr) NGetTrapAddress( _SCSIDispatch, ToolTrap ))) != nil ) {
			NSetTrapAddress( (long) SCSIGlobals->busyPatch, _SCSIDispatch, ToolTrap );
			SCSIGlobals->busyPatchVers = kbusyPatchVers;	
		}
	}
	
	SetXPTg( XPTg);
	
	InitSyncWait( XPTg );
	
	// Setup the A089 Trap
	NSetTrapAddress ( (long)SCSIAtomic, 0x89, OSTrap );

	return (0);
}


/*————————————————————————————————————————————————————————————————————————
	OldSCSIExists 	-	
————————————————————————————————————————————————————————————————————————*/

Boolean OldSCSIExists( void)
{
	return( NGetTrapAddress(0xA815, ToolTrap) != 
			NGetTrapAddress(UNIMPTRAP, ToolTrap) );
}

/*********************************************************************************
	GetXPTg, SetXPTg	-	store and retrieve the XPT globals pointer
*********************************************************************************/

#if 0
XPTglobals *
GetXPTg( void )
{
	return(*(XPTglobals **)(*((Ptr *)0xC0C) + 0x1B4) );
}
#endif

void
SetXPTg( XPTglobals *XPTg )
{
	*(XPTglobals **)(*((Ptr *)0xC0C) + 0x1B4) = XPTg;
	SCSIGlobals->tempXPTGInUse = 0;	// Remember that we are using the real globals

}

void
SetTempXPTg( XPTglobals *XPTg )
{
	SCSIGlobals->tempXPTGGlobals = XPTg;	// Save the globals in a temporary spot
	SCSIGlobals->tempXPTGInUse = tempXPT;	// Remember that we did this
}


/*********************************************************************************
	SCSITrap	-	This is our NewSCSI trap entry point
*********************************************************************************/

OSErr
SCSITrap( short scsiSelector, void * pbPtr )
{
	XPTglobals	*XPTg;
	ushort		busID;
	
	XPTg = GetXPTg();
	
	if (scsiSelector == xptSCSIAction) {						// Do a SCSI_PB action
		return (XPTAction( (SCSI_PB *)pbPtr, XPTg));
	}

	switch (scsiSelector) {

	case xptSCSIRegisterBus:	
		return (XPTRegisterBus( (SIMinitInfo *)pbPtr, XPTg));
		break;

	case xptSCSIDeregisterBus:
		busID = ((SCSI_PB *)pbPtr)->scsiDevice.bus;
		return ( XPTDeregisterBus( busID, XPTg) );
		break;

	case xptSCSIReregisterBus:
		return (XPTReregisterBus( (SIMinitInfo *)pbPtr, XPTg));
		break;

	case xptSCSIKillXPT:
		return ( XPTKillXPT( XPTg) );
		break;

	default:
		return (scsiFunctionNotAvailable);
		break;
	}
}

		
/*********************************************************************************
	XPTRegisterBus	-	Register new SIM/HBA with Xpt
*********************************************************************************/

OSErr	
XPTRegisterBus (SIMinitInfo * SIMinfoPtr, XPTglobals *XPTg)
{
	ushort		busID;
	uchar *		busG;
	BusInfo		*thisBusInfoPtr;
	
	
// Get next bus number and see if this one would be one too many

	if (XPTg->numBuses == kMaxBuses) {
		return( scsiTooManyBuses);
	}
	
	if (XPTg->numBuses > kMaxBuses) {
		IfDebugStr("\pWay too many bus registrations");
		return( scsiTooManyBuses);
	}

// Allocate memory for SIM's static vars

	if (SIMinfoPtr->staticSize) {		// if SIM wants some statics
		busG = (uchar *) NewPtrSysClear((Size)SIMinfoPtr->staticSize);
		if (busG == 0) {
			IfDebugStr("\pCouldn't allocate bus statics");
			return( memFullErr);
		}
	}
	
// Get a BusInfo structure for this Bus's info
//		there are some BusInfos that are allocated in the XPT's globals already so
//		we try there first, if no room then we NewPtrSysClear another BusInfo spot.

	if (XPTg->numBuses < kNumBusInfos) {
		thisBusInfoPtr = &(XPTg->TopBusInfos[ XPTg->numBuses]);
	}
	else {
		thisBusInfoPtr = (BusInfo *)NewPtrSysClear(sizeof(BusInfo));
		if (thisBusInfoPtr == 0) {
			return( memFullErr);
		}
	}


// At this point, we've got everything a registration needs so we can consider
//		it a done deal.  We will now increment the number of buses.
//		and find an empty bus number for this SIM.

	XPTg->numBuses+=1;
	for( busID = 0; busID < XPTg->numBuses; busID+=1 ) {
		if( XPTg->BusInfoPtr[busID] == nil )
			break;
	}
	
		
// We must put this pointer in XPT's BusInfoPtrs

	XPTg->BusInfoPtr[busID] = thisBusInfoPtr;
	
	
// Set up the return values in the SIMinitInfo
	
	SIMinfoPtr->busID = busID;				// -> bus number for the registered bus
	SIMinfoPtr->SIMstaticPtr = busG;		// -> alloc. ptr to the SIM's static vars


//	Do all the common stuff - sticking our values in the SIM's init pb
	
	XPTRegisterCommon( SIMinfoPtr);
	

// Set up the XPT's BusInfo with what's known about the HBA so far

	thisBusInfoPtr->initInfo = *SIMinfoPtr;
	
	
// If we need to, allocate a new SCSI_IO for old API emulation.

	if ((SIMinfoPtr->ioPBSize > XPTg->xptIOpbSize) && SIMinfoPtr->oldCallCapable)
	{
		if (XPTg->xptIOpbSize)			// if not first time thru, dispose old one
			DisposPtr( (char *)(XPTg->xptIOptr));
			
		if (NewXPTioPB( SIMinfoPtr->ioPBSize, XPTg))
			return (memFullErr);
	}

// If we need to, adjust the maxIOpbSize field

	if (SIMinfoPtr->ioPBSize > XPTg->maxIOpbSize)
		XPTg->maxIOpbSize = SIMinfoPtr->ioPBSize;


// If we got this far, call the SIMinit routine and return it's result as our result

	return ( (SIMinfoPtr->SIMinit) (SIMinfoPtr) );
}


/*********************************************************************************
	XPTReregisterBus	-	Re-Register existing SIM/HBA with XPT
*********************************************************************************/

OSErr	
XPTReregisterBus (SIMinitInfo * SIMinfoPtr, XPTglobals *XPTg)
{
	ushort		busID;
	BusInfo		*thisBusInfoPtr;
	
	// If we are in the transition from one XPT to another then use the
	// temporary XPT globals
	if( SCSIGlobals->tempXPTGInUse == tempXPT )
		XPTg = SCSIGlobals->tempXPTGGlobals;
	

// Allocate memory for SIM's static vars

	if (SIMinfoPtr->SIMstaticPtr == 0) {	// if the SIM wants new globals
		if (SIMinfoPtr->staticSize) {		// and if SIM wants more than 0
			SIMinfoPtr->SIMstaticPtr = (uchar *) NewPtrSysClear((Size)SIMinfoPtr->staticSize);
			if (SIMinfoPtr->SIMstaticPtr == 0) {
				IfDebugStr("\pCouldn't allocate bus statics");
				return( memFullErr);
			}
		}
	}
	
// Get the bus ID

	busID = SIMinfoPtr->busID;
	
//	Do all the common stuff - sticking our values in the SIM's init pb
	
	XPTRegisterCommon( SIMinfoPtr);


// If we don't have a BusInfo structure for this Bus's info then go get one
//		there are some BusInfos that are allocated in the XPT's globals already so
//		we try there first, if no room then we NewPtrSysClear another BusInfo spot.

	if( XPTg->BusInfoPtr[busID] == nil ) {
		if (XPTg->numBuses < kNumBusInfos) {
			thisBusInfoPtr = &(XPTg->TopBusInfos[XPTg->numBuses]);
		}
		else {
			thisBusInfoPtr = (BusInfo *)NewPtrSysClear(sizeof(BusInfo));
			if (thisBusInfoPtr == 0) {
				return( memFullErr);
			}
		}
		XPTg->numBuses+=1;
		XPTg->BusInfoPtr[busID] = thisBusInfoPtr;
	}

// Copy SIMinitInfo data into XPT's BusInfoPtr

	XPTg->BusInfoPtr[busID]->initInfo = *SIMinfoPtr;
	
	
// If we need to, allocate a new SCSI_IO for old API emulation.

	if ((SIMinfoPtr->ioPBSize > XPTg->xptIOpbSize) && SIMinfoPtr->oldCallCapable)
	{
		if (XPTg->xptIOptr)				// if not first time thru, dispose old one
			DisposPtr( (char *)(XPTg->xptIOptr));
			
		if (NewXPTioPB( SIMinfoPtr->ioPBSize, XPTg))
			return (memFullErr);
	}


// If we need to, adjust the maxIOpbSize field

	if (SIMinfoPtr->ioPBSize > XPTg->maxIOpbSize)
		XPTg->maxIOpbSize = SIMinfoPtr->ioPBSize;


// We do not call the SIM's Initialization routine on reregister.  Instead,
//	the SIM will get the data out upon return
	
	return ( noErr);
}

		
/*********************************************************************************
	XPTRegisterCommon	-	Common between Register and Reregister code
*********************************************************************************/

void	
XPTRegisterCommon( SIMinitInfo * SIMinfoPtr)
{
	
// Set up the return values in the SIMinitInfo
	
	SIMinfoPtr->MakeCallback = XPTCallCompRoutine;
	SIMinfoPtr->EnteringSIM	 = VMDisableUserCode;
	SIMinfoPtr->ExitingSIM	 = VMEnableUserCode;
	
	switch ( SIMinfoPtr->busID) 
	{
	case 0:
		SIMinfoPtr->XPT_ISR = XPT_ISR0;		// -> ptr to the XPT's ISR (so SIM can install it)
		break;
	case 1:
		SIMinfoPtr->XPT_ISR = XPT_ISR1;			
		break;
	case 2:
		SIMinfoPtr->XPT_ISR = XPT_ISR2;			
		break;
	case 3:
		SIMinfoPtr->XPT_ISR = XPT_ISR3;			
		break;
	case 4:
		SIMinfoPtr->XPT_ISR = XPT_ISR4;			
		break;
	case 5:
		SIMinfoPtr->XPT_ISR = XPT_ISR5;			
		break;
	case 6:
		SIMinfoPtr->XPT_ISR = XPT_ISR6;			
		break;
	case 7:
		SIMinfoPtr->XPT_ISR = XPT_ISR7;	
		break;
	case 8:
		SIMinfoPtr->XPT_ISR = XPT_ISR8;	
		break;
	case 9:
		SIMinfoPtr->XPT_ISR = XPT_ISR9;	
		break;
	case 0x0a:
		SIMinfoPtr->XPT_ISR = XPT_ISRa;	
		break;
	case 0x0b:
		SIMinfoPtr->XPT_ISR = XPT_ISRb;	
		break;
	case 0x0c:
		SIMinfoPtr->XPT_ISR = XPT_ISRc;	
		break;
	case 0x0d:
		SIMinfoPtr->XPT_ISR = XPT_ISRd;	
		break;
	case 0x0e:
		SIMinfoPtr->XPT_ISR = XPT_ISRe;	
		break;
	case 0x0f:
		SIMinfoPtr->XPT_ISR = XPT_ISRf;	
		break;
	}
}
	


/*********************************************************************************
	XPTDeregisterBus	-	Remove registration of SIM/HBA
*********************************************************************************/

OSErr
XPTDeregisterBus (ushort busID, XPTglobals *XPTg)
{
#pragma unused (busID)
#pragma unused (XPTg)

	return (scsiFunctionNotAvailable);
}


/*********************************************************************************
	XPTKillXPT	-	Render XPT and its stuff inoperative (might be used for patching)
*********************************************************************************/

OSErr
XPTKillXPT ( XPTglobals *XPTg)
{
	ulong	* oldPatch;
	
	RemoveSyncWait(XPTg);				// Get rid of our patch to syncWait
	
	// Disable patch by changing the enabled variable in the patch
	// this variable is embedded in the code 4 bytes before the 
	// actual beginning of the code.
	oldPatch = (ulong *)(XPTg->debugPatch);
	*(--oldPatch) = 0;	// disable the  patch
	
	// Ditto for the SCSIBusy Patch if it changed.
	if( SCSIGlobals->newBusyPatchVers != kbusyPatchVers ) {
		// Let the new XPT know that there isn't a SCSI Busy patch.
		SCSIGlobals->busyPatchVers = 0;
		oldPatch = (ulong *)(SCSIGlobals->busyPatch);
		*(--oldPatch) = 0;	// disable the  patch
	}
	
	DisposPtr( (char *)(XPTg->xptIOptr));
	DisposPtr((Ptr)XPTg);				// Get rid of our globals
										// Anything else I missed? !!!
	return (noErr);
}


#if 0
/*********************************************************************************
	XPTAsyncEvent	-	notifies clients of event that they had registered for
*********************************************************************************/

OSErr	
XPTAsyncEvent (SCSI_PB *pbPtr, XPTglobals *XPTg)
{

/*SCSIAsyncEvent (long what, 
						ushort busID, 
						ushort targetID, 
						ushort lun, 
						long dataBfr, 
						long dataCnt)*/
						
	return (scsiFunctionNotAvailable);
}
#endif

/*********************************************************************************
	XPTAction	-	perform an Action (either XPT or pass it to SIM)
*********************************************************************************/

OSErr	
XPTAction (SCSI_PB *pbPtr, XPTglobals *XPTg)
{
	Boolean		needSyncWait = false;	// assume that the call won't need syncWait
	OSErr		result = noErr;			// error returned synchronously (result in D0)
	BusInfo		*busInfoPtr;
	Boolean		forceSync = false;
	pascal void	(*oldCompletion)(SCSI_IO *);
	
	if (pbPtr->qLink) {											// <LW14> pdw Fß TOP
		pbPtr->scsiResult = scsiQLinkInvalid;
		return ( pbPtr->scsiResult);
	}															// <LW14> pdw Fß BOT
	
	// We have to see if the Function code is handled by the XPT or by the SIM

	switch (pbPtr->scsiFunctionCode) {
	
	case SCSIExecIO:				// SIM
	case SCSIResetBus:				// SIM						// <SM8> pdw
	case SCSIResetDevice:			// SIM						// <SM8> pdw
	case SCSIReleaseQ:				// SIM						// <SM8> pdw
	case SCSIAbortCommand:			// SIM						// <SM8> pdw
	case SCSITerminateIO:			// SIM						// <SM8> pdw

#if forceSyncAlways		// will poll always (not just when int level high)
		{
#else
		if (SCSIGlobals->inDebugger && InterruptLevel() >1 ) {
#endif
			forceSync = true;
			oldCompletion = pbPtr->scsiCompletion;
			pbPtr->scsiCompletion = 0;
		}

		((SCSI_IO *)pbPtr)->savedA5 = getCurrentA5();
		if( pbPtr->scsiCompletion == 0)							// <SM8> pdw
			needSyncWait = true;

		if( needSyncWait && XPTg->syncUnsafeCount ) {
			pbPtr->scsiResult = scsiBusy;
			return ( pbPtr->scsiResult);
		}

		if ( (((SCSI_PB *)pbPtr)->scsiDevice).bus >= XPTg->numBuses) {
			pbPtr->scsiResult = scsiBusInvalid;
			return ( pbPtr->scsiResult);
		}
		
		busInfoPtr = XPTg->BusInfoPtr[ (((SCSI_PB *)pbPtr)->scsiDevice).bus];
	
		if( busInfoPtr )
			(busInfoPtr->initInfo.SIMaction) (pbPtr, (busInfoPtr->initInfo).SIMstaticPtr);
		else{
			pbPtr->scsiResult = scsiBusInvalid;
			return ( pbPtr->scsiResult);
		}
		
		if ( needSyncWait) {
			SyncWait( pbPtr, XPTg);
			if (forceSync) {
				if (oldCompletion!=0) {
					pbPtr->scsiCompletion = oldCompletion;
					XPTCallCompRoutine( (SCSI_IO *)pbPtr );
					return (noErr);
				}
			}
			return (pbPtr->scsiResult);				// return the error! (unlike Cyclone)
		}
		
		break;
		
	case SCSIBusInquiry:			// SIM
		IfRecordEvent( *(long *)&pbPtr->scsiDevice, (long)'Inq-');
		pbPtr->scsiResult = noErr;
		if ( pbPtr->scsiPBLength < sizeof(SCSIBusInquiryPB)) {
			pbPtr->scsiResult = scsiPBLengthError;
		}	
		else if ( pbPtr->scsiDevice.bus == 0xff) {
			((SCSIBusInquiryPB *)pbPtr)->scsiIOpbSize = sizeof(SCSI_IO); 
			((SCSIBusInquiryPB *)pbPtr)->scsiMaxIOpbSize = XPTg->maxIOpbSize; 
			((SCSIBusInquiryPB *)pbPtr)->scsiHiBusID = XPTg->numBuses - 1;
			BlockMove("Apple Computer \0",((SCSIBusInquiryPB *)pbPtr)->scsiSIMVendor,16);
		}
		else if ( pbPtr->scsiDevice.bus >= XPTg->numBuses) {
			pbPtr->scsiResult = scsiBusInvalid;
		}
		else {
			((SCSIBusInquiryPB *)pbPtr)->scsiIOpbSize = sizeof(SCSI_IO); 
			((SCSIBusInquiryPB *)pbPtr)->scsiMaxIOpbSize = XPTg->maxIOpbSize; 
			((SCSIBusInquiryPB *)pbPtr)->scsiHiBusID = XPTg->numBuses - 1;
			pbPtr->scsiResult = CallSIMaction( pbPtr, XPTg);
		}
		IfRecordEvent( (long)(pbPtr->scsiResult), (long)'-Inq');
		return ( pbPtr->scsiResult);
		break;
		
	case SCSISetAsyncCallback:		// XPT & SIM
		result = CallSIMaction( pbPtr, XPTg);
		break;

	case SCSIGetVirtualIDInfo:		// XPT
		IfRecordEvent( *(long *)(&(((SCSIGetVirtualIDInfoPB *)pbPtr)->scsiOldCallID)), (long)'Vid-');
		GetVirtualIDInfo( (SCSIGetVirtualIDInfoPB *) pbPtr, XPTg);
		IfRecordEvent( *(long *)(&(((SCSIGetVirtualIDInfoPB *)pbPtr)->scsiOldCallID)), *(long *)&(pbPtr->scsiDevice));
		break;
		
	case SCSICreateRefNumXref:		// XPT
		IfRecordEvent( *(long *)(&(((SCSI_Driver_PB *)pbPtr)->scsiDevice)), (long)'Xrf-');
		SetRefNum( (SCSI_Driver_PB *) pbPtr, XPTg);
		IfRecordEvent( *(long *)(&(((SCSI_Driver_PB *)pbPtr)->scsiDriver)), (long)(pbPtr->scsiResult));
		break;
		
	case SCSILookupRefNumXref:		// XPT
		GetRefNum( (SCSI_Driver_PB *) pbPtr, XPTg);
		break;
		
	case SCSIRemoveRefNumXref:		// XPT
		RemoveRefNum( (SCSI_Driver_PB *) pbPtr, XPTg);
		break;

	case SCSIGenerateInterleaveID:	// XPT
		((SCSIGenerateInterleaveIDPB *) pbPtr)->scsiInterleaveID = XPTg->nextInterleave++;
		break;

	case SCSINop:					// XPT
		break;

	default:
		result = CallSIMaction( pbPtr, XPTg);
		break;
		
	}
	
	return (result);
}


/*********************************************************************************
	CallSIMaction	-	perform an Action (either Xpt or pass it to SIM)
*********************************************************************************/

OSErr
CallSIMaction( void * pbPtr, XPTglobals * XPTg)
{
	BusInfo		*busInfoPtr;
	
	if ( (((SCSI_PB *)pbPtr)->scsiDevice).bus >= XPTg->numBuses)
		return (scsiBusInvalid);
		
	busInfoPtr = XPTg->BusInfoPtr[ (((SCSI_PB *)pbPtr)->scsiDevice).bus];

	if( busInfoPtr ) {
		(busInfoPtr->initInfo.SIMaction) (pbPtr, (busInfoPtr->initInfo).SIMstaticPtr);
		return ( noErr);
	}
	return(scsiBusInvalid);
}


/*********************************************************************************
	SyncWait	-	wait for a synchronous request to be completed
*********************************************************************************/

void
SyncWait( SCSI_PB *pbPtr, XPTglobals *XPTg)
{
	IfRecordEvent( (long)(pbPtr), (long)'Xsyw');
	
	do {
		CheckInterrupts( XPTg);
	} while (pbPtr->scsiResult == scsiRequestInProgress);
}


/*********************************************************************************
	CheckInterrupts	-	
*********************************************************************************/

void
CheckInterrupts (XPTglobals	* XPTg)
{
#if forceSyncAlways		// will poll always (not just when int level high)
	DispatchISR();
#else
	// GROSS Hack Alert!
	//
	// In theory the private DT Queue is a SIM private since it is only used by the
	// pseudo DMA machines.  However if I actually poll all SIMs at all interrupt 
	// levels the overhead is such that basic operations that depend on syncwait start
	// to slow down.  To get around this I only poll when I _have_ to which means if 
	// there is something in our private deferred task queue or if it is busy (we are
	// working on soemthing and hadn't blocked ints at the VIA yet.)
	if (InterruptLevel() > 1 || SCSIGlobals->privDTQueue.qHead || SCSIGlobals->privDTQueue.qFlags ) 
	{
		if (bset(inVBL, (char *)&((GetVBLQHdr()->qFlags))))	// make VBL busy: was it already?
			DispatchISR();									// yes: check interrupt sources
		else {
			DispatchISR();									// no: check interrupt sources
			bclr(inVBL, (char *)&((GetVBLQHdr()->qFlags)));	//  and clr busy bit (return to prev value)
		}
	}
#endif
	
	if ( bclr( kbResetFromSync, &XPTg->flags ))
		TryToRecover( XPTg);
}


/*********************************************************************************
	TryToRecover	-	
*********************************************************************************/

void
TryToRecover ( XPTglobals *XPTg)
{
#pragma unused (XPTg)

	SCSIResetBusPB	rstPB;
	
	Clear( &rstPB, sizeof(rstPB));
	rstPB.scsiDevice.bus = 0;
	SCSIAction( (SCSI_PB *)&rstPB);

	rstPB.scsiDevice.bus = 1;
	SCSIAction( (SCSI_PB *)&rstPB);
}


/*********************************************************************************
	DispatchISR	-	
*********************************************************************************/

void
DispatchISR ( void)
{
	short			i;
	XPTglobals *	XPTg;
	BusInfo *		busInfoPtr;
	
	
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	XPTg = GetXPTg();

	for (i=0; i< XPTg->numBuses; i+=1)
	{
		busInfoPtr = XPTg->BusInfoPtr[i];		
		((busInfoPtr->initInfo).SIMInterruptPoll) ( (busInfoPtr->initInfo).SIMstaticPtr);
	}

	VMEnableUserCode();			// enable user code (allow page faults)
}



/*********************************************************************************
	SetRefNum, GetNextRefNum, RemoveRefNum	-	
*********************************************************************************/

void
SetRefNum( SCSI_Driver_PB * pbPtr, XPTglobals * XPTg)
{
	ulong	index;
	Ptr 	temp;
	ulong 	size;
	
	pbPtr->scsiDevice.diReserved = 0;
	
	for ( index = 0; index < XPTg->Drivers->DrvrCnt; index+=1 ) {
		if ( pbPtr->scsiDevice == XPTg->Drivers->Drvr[index].DevID ) {
			pbPtr->scsiResult = scsiDeviceConflict;
			return;
		}
	}
	size = sizeof(DrvrList) + sizeof(RefInfo) * (index + 1);
	temp = NewPtrSysClear(size);
	if ( temp ) {
		BlockMove(XPTg->Drivers,temp,size - sizeof(RefInfo));
		DisposPtr((Ptr)XPTg->Drivers);
		XPTg->Drivers = (DrvrList *)temp;
	}
	else {
		pbPtr->scsiResult = memFullErr;
		return;
	}
	XPTg->Drivers->DrvrCnt+=1;
	XPTg->Drivers->Drvr[index].DevID = pbPtr->scsiDevice;
	XPTg->Drivers->Drvr[index].DRefNum = pbPtr->scsiDriver;
	pbPtr->scsiResult = noErr;
}

void
GetRefNum( SCSI_Driver_PB * pbPtr, XPTglobals * XPTg)
{
	ulong index;
	
	pbPtr->scsiResult = noErr;	/* Can't Fail */

	if ( pbPtr->scsiDevice.bus == 0xFF ) {	/* Marker for Give me the first in the list */
		pbPtr->scsiDriver = 0;	/* Not a driver */
		if ( XPTg->Drivers->DrvrCnt ) 
			pbPtr->scsiNextDevice = XPTg->Drivers->Drvr[0].DevID;	/* First one in the list */
		else 
			pbPtr->scsiNextDevice.bus = 0xFF ;	/* Nobody home */
		return;
	}

	pbPtr->scsiDevice.diReserved = 0;	/* Get rid of "unused" byte which might have
											   (like the installer's setting of the high
											   bit) extraneaous stuff in it!  */
	for ( index = 0; index < XPTg->Drivers->DrvrCnt; index+=1 ) {
		if ( pbPtr->scsiDevice == XPTg->Drivers->Drvr[index].DevID ) {
			pbPtr->scsiDriver = XPTg->Drivers->Drvr[index].DRefNum;
			if ( index + 1 == XPTg->Drivers->DrvrCnt )
				pbPtr->scsiNextDevice.bus = 0xFF ;	/* Nobody home */
			else
				pbPtr->scsiNextDevice = XPTg->Drivers->Drvr[index + 1].DevID;
			return;
		}
	}
	pbPtr->scsiDriver =	0;		/* Not a driver */
	pbPtr->scsiNextDevice.bus = 0xFF ;	/* Nobody home */
}

void
RemoveRefNum( SCSI_Driver_PB * pbPtr, XPTglobals * XPTg)
{
	ulong index,remainder;
	
	pbPtr->scsiDevice.diReserved = 0;
	
	for ( index = 0; index < XPTg->Drivers->DrvrCnt; index+=1 ) {
		if ( pbPtr->scsiDevice == XPTg->Drivers->Drvr[index].DevID ) {
			for ( remainder = index; remainder < XPTg->Drivers->DrvrCnt - 1; remainder+=1 ) 
				XPTg->Drivers->Drvr[remainder] = XPTg->Drivers->Drvr[remainder + 1];
			XPTg->Drivers->DrvrCnt -= 1;
			pbPtr->scsiResult = noErr;	/* Removed it */
			return;															//<SM19>pdw
		}
	}
	pbPtr->scsiResult = scsiNoSuchXref;
}


/*********************************************************************************
	XPTCallCompRoutine 	-	Called by the SIM's CompleteIO
*********************************************************************************/

void
XPTCallCompRoutine( SCSI_IO * ioPtr )		// <SM7>
{
	pascal void	(*fn)(SCSI_IO *);
	// Ptr			oldA5;
	XPTglobals *	XPTg;
	
//--- If we need to do virtual ID mapping, and result==noErr then do it		// <SM10> pdw

	XPTg = GetXPTg();
	if (XPTg->oldIDBusNumber[ioPtr->scsiDevice.targetID]<0) {
		if ( ioPtr->scsiFunctionCode == SCSIExecIO)							// <LW14> pdw Fß
			if ( ioPtr->scsiResult==noErr || ioPtr->scsiResult==scsiNonZeroStatus || ioPtr->scsiResult==scsiDataRunError )
				if( XPTg->BusInfoPtr[ioPtr->scsiDevice.bus]->initInfo.oldCallCapable)
					XPTg->oldIDBusNumber[ioPtr->scsiDevice.targetID] = ioPtr->scsiDevice.bus;
	}

	ioPtr->qLink = 0;	// set qLink back to NIL in case pb is reused		// <LW14> pdw Fß
	
//--- Call the completion routine (with proper A5) as long as routine ptr isn't NIL

	// scsiCompletion was moved into the header - therefore we can call it for any pb <SM8>
	if( (fn=ioPtr->scsiCompletion) != nil ) {
		// oldA5 = getCurrentA5(); now it's done in CallCompRoutineGlue
		IfRecordEvent( (long)(ioPtr), (long)'xcC-');
		CallCompRoutineGlue( ioPtr, &(XPTg->completionDT));		// MAKE CALLBACK	
		IfRecordEvent( (long)(fn), (long)'-xcC');
	}
}


/*********************************************************************************
	ReRegisterAllSIMs	-	
*********************************************************************************/

OSErr
ReRegisterAllSIMs( XPTglobals *XPTg )
{
	long 			OldXPT;
	Boolean			*oldSIMs;
	ulong			id;
	SCSIGetVirtualIDInfoPB dIdent;	
	SCSI_Driver_PB 	drvrPB;
	SCSIBusInquiryPB scPB;
	uchar			busID;
	uchar			highBusID;
	SCSI_PB			reRegister;

// Setup our globals in a temporary spot so we don't step on any existing globals
// Use GetVirtualID to build up a list of virtual IDs
// Use BusInquiry to build up a list of existing SIMs
// SetTrapAddress to the new XPT and remember the address of the old one.
// Use the old XPT to send a ReRegisterSIM call to each SIM
// Call KillXPT to get rid of the old XPT (Note Kill XPT can't call SetTrapAddress!!!)
// Put our Globals in the normal spot
// Install any patches (such as vSyncWait) that we will use (this MUST be done AFTER KillXPT)
// If the normal internal SIMs didn't already exist then tell InitItt to install them

	SetTempXPTg( XPTg);

// Use the old XPT to find all of the virtual IDs

	Clear((char *)&dIdent,sizeof(dIdent));
	
	for( id = 0; id < 7; id+=1 ) {
		dIdent.scsiOldCallID = id;
		dIdent.scsiFunctionCode = SCSIGetVirtualIDInfo;
		dIdent.scsiCompletion = nil;
		dIdent.scsiPBLength = sizeof(SCSIGetVirtualIDInfoPB);
		SCSIAction((SCSI_PB *) &dIdent);
		if( dIdent.scsiExists )
			XPTg->oldIDBusNumber[id] = dIdent.scsiDevice.bus;
		else
			XPTg->oldIDBusNumber[id] = -1;
	}

// Now go get all of the existing Drivers which have been registered
	
	Clear((char *)&drvrPB,sizeof(drvrPB));
	
	/* Get the devIdent of the first driver registered with Itt */
	drvrPB.scsiDevice.bus = 0xff;				/* Give us the first one in the list */
	drvrPB.scsiPBLength = sizeof(drvrPB);
	drvrPB.scsiFunctionCode = SCSILookupRefNumXref;
	SCSIAction( (SCSI_PB *) &drvrPB );
	drvrPB.scsiDevice = drvrPB.scsiNextDevice;		/* Get The first one in the list */

	while( drvrPB.scsiDevice.bus != 0xff ) {
		SCSIAction( (SCSI_PB *) &drvrPB );
		SetRefNum(&drvrPB,XPTg);					/* Register with the new set of globals */
		drvrPB.scsiDevice = drvrPB.scsiNextDevice;	/* Get The next one in the list */
	} 

// Look for existing SIMs

	Clear((char *)&scPB,sizeof(scPB));
	
	*(long *)&(scPB.scsiDevice) = 0xff;	// XPT Inquiry
	scPB.scsiFunctionCode = SCSIBusInquiry;
	scPB.scsiPBLength = sizeof(SCSIBusInquiryPB);
	SCSIAction( (SCSI_PB *) &scPB );		// Get info for the XPT
	
	highBusID = scPB.scsiHiBusID;
	if( (oldSIMs = (Boolean *)NewPtrSysClear(sizeof(Boolean) * (highBusID + 1))) == 0 ) {
		IfDebugStr("\pNot enough memory to switch XPTs");	// Yikes, this would be really bad...
		return(memFullErr);
	}

	for( busID = 0; busID <= highBusID; busID+=1 ) {
		scPB.scsiDevice.bus = busID;
		scPB.scsiFunctionCode = SCSIBusInquiry;
		scPB.scsiPBLength = sizeof(SCSIBusInquiryPB);
		if( SCSIAction( (SCSI_PB *) &scPB ) == noErr)
			oldSIMs[busID] = true;
	}

// Remember the old TrapAddress and setup the new one

	OldXPT = NGetTrapAddress(SCSIATOM, OSTrap);
	NSetTrapAddress ( (long)SCSIAtomic, 0x89, OSTrap );
	
// And... Re-Register all existing SIMs

	Clear((char *)&reRegister,sizeof(reRegister));
	
	for( busID = 0; busID <= highBusID; busID+=1 ) {
		if( oldSIMs[busID] ) {
			reRegister.scsiPBLength = sizeof(reRegister);
			reRegister.scsiDevice.bus = busID;
			reRegister.scsiFunctionCode = SCSIRegisterWithNewXPT;
			CallOldXPT( &reRegister,xptSCSIAction,OldXPT );
		}
	}
	
// Get rid of the old XPT and get out of here
	CallOldXPT(0, xptSCSIKillXPT, OldXPT);
	
	SetXPTg(XPTg);		// Put the real XPT Globals in place
	
	DisposPtr((Ptr)oldSIMs);
}


/*********************************************************************************
	XPT_ISR0	-	
*********************************************************************************/
#if 0
void
XPT_ISR0 (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[0];		
	((busInfoPtr->initInfo).SIM_ISR)( (busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}

void
XPT_ISR1 (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[1];		
	((busInfoPtr->initInfo).SIM_ISR)((busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}
#endif

void
XPT_ISR2 (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[2];		
	((busInfoPtr->initInfo).SIM_ISR)((busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}

void
XPT_ISR3 (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[3];		
	((busInfoPtr->initInfo).SIM_ISR)((busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}

void
XPT_ISR4 (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[4];		
	((busInfoPtr->initInfo).SIM_ISR)((busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}

void
XPT_ISR5 (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[5];		
	((busInfoPtr->initInfo).SIM_ISR)((busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}

void
XPT_ISR6 (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[6];		
	((busInfoPtr->initInfo).SIM_ISR)((busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}

void
XPT_ISR7 (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[7];		
	((busInfoPtr->initInfo).SIM_ISR)((busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}

void
XPT_ISR8 (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[8];		
	((busInfoPtr->initInfo).SIM_ISR)((busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}

void
XPT_ISR9 (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[9];		
	((busInfoPtr->initInfo).SIM_ISR)((busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}

void
XPT_ISRa (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[0x0a];		
	((busInfoPtr->initInfo).SIM_ISR)((busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}

void
XPT_ISRb (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[0x0b];		
	((busInfoPtr->initInfo).SIM_ISR)((busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}

void
XPT_ISRc (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[0x0c];		
	((busInfoPtr->initInfo).SIM_ISR)((busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}

void
XPT_ISRd (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[0x0d];		
	((busInfoPtr->initInfo).SIM_ISR)((busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}

void
XPT_ISRe (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[0x0e];		
	((busInfoPtr->initInfo).SIM_ISR)((busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}

void
XPT_ISRf (void)
{
	BusInfo *		busInfoPtr;
		
	VMDisableUserCode();		// disable user code (so page faults won't happen)

	//									vv
	busInfoPtr = GetXPTg()->BusInfoPtr[0x0f];		
	((busInfoPtr->initInfo).SIM_ISR)((busInfoPtr->initInfo).SIMstaticPtr);

	VMEnableUserCode();			// enable user code (allow page faults)
}

