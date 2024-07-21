/*
	File:	InitItt.c

	Contains:	routines that initializes Cousin Itt

	Entry points:

	Written by:	Paul Wolf

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SM40>	  2/2/94	DCB		My last change broke the INIT...
	  <SM39>	  2/2/94	DCB		Removed call INITSCSIBOOT and moved it into StartInit.a where it
									gets called after Slot Interrupts and ADB are initialized.
	  <SM38>	  2/1/94	chp		Remove some redundant initializations of fields in the TNT HDA
									descriptor.
	  <SM37>	  2/1/94	DCB		Set the using601Emulator field in the hardware description field
									if we are running on a 601.
	  <SM36>	 1/29/94	DCB		Added code to initialize SIMg->otherSIMg which is used on dual
									bus machines with one interrupt source.
	   <ML3>	  1/5/94	pdw		Converted SCSIGlobals usage to new format.
	  <SM34>	12/19/93	DCB		Only check for non-universal if we are being built as an INIT.
	  <SM33>	12/19/93	DCB		Un-Patch the Deferred Task Manager if patchIIciROM.a has
									installed the evil QuickMail patch which can cause the stack to
									grow in an unbounded fashion.  Also don't install on
									non-universal ROMs (Duh).
	  <SM32>	11/22/93	pdw		Rolling in from <MCxx>.
	  <SM31>	11/21/93	pdw		Removed reinitialization of interrupt function fields for second
									bus.
	  <SM30>	11/19/93	chp		Support new IRQ primitive vector initialization. Move TNT
									external SCSI to SCSI96_2 and support internal SCSI as SCSI96_1,
									which is a 53CF96.
	  <SMG4>	 9/29/93	chp		Fill in more vital statistics for TNT.
	  <SMG3>	 9/22/93	chp		Add support and vital information for TNT SCSI initialization.
	  <SM28>	10/29/93	DCB		<MC> roll-in.
	   <MC6>	10/28/93	pdw		Cleaned up forPDMProto stuff a little bit more.
	  <SM27>	10/14/93	pdw		<MC> roll-in.
	   <MC5>	10/12/93	pdw		Added support for Synchronous data transfers, rewrote State
									Machine, message handling etc.
	   <MC4>	 9/26/93	pdw		Got rid of ReplaceGestalt call.
	   <MC3>	 9/16/93	pdw		Added setting of HBAisFast for ColdFusion's FC96 bus and
									clearing of it (for default) for all second buses.  Fixes the
									initialization of Curio as an FC96 bug (which made boot SLOW).
	   <MC2>	 9/13/93	pdw		Roll-in from SuperMario.
	  <SM26>	 9/13/93	pdw		Changed the risky slash pattern.
	  <SM25>	 9/12/93	pdw		Added support for reregistration of buses for plugging in new
									replacement SIMs (i.e. from an Init on an IttFull ROM).
	  <SM24>	 8/23/93	DCB		Went back to checking for djMEMC since the TestFor works now.
	  <SM23>	 8/20/93	DCB		Fixing initialization problems for Wombats and possibly other
									(?) 040/c96 machines. Need to unblock interrupts before
									returning if we don't install. Also default to Wombat for now if
									we don't know what we are - I'll fix this soon I promise.
	  <SM22>	 8/13/93	pdw		Got rid of all that fake-gestalt stuff.  Went to local cpu var
									based on decoder types.
	  <SM21>	 7/28/93	pdw		Fixing Quadra ISR vector problem: Adding init of intIRQbitNum to
									3 into default values init area.
	  <SM20>	 7/20/93	pdw		Fixed up some Cold Fusion problems with IRQ bit numbers and some
									Quadra 9x0 problems with not initing the second DAFB.
	  <SM19>	  7/2/93	IH		Reality Update: Change Gestalt call to use
									SelectorFunctionProcPtr.
	  <SM18>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
									stack switching mechanism.  Adding support for Cold Fusion.
									Rearranging HW/SW Init code. Some code optimizations.
	  <SM17>	 5/30/93	PW		Fixed "doesn't run without Gibbly" bug by only dereferencing
									HALg0 and HALg1 when they are both valid.
	  <SM16>	 5/29/93	PW		Nothing really.
	  <SM15>	 5/25/93	DCB		Rollin from Ludwig. (The next item below)
	   <LW8>	 5/21/93	PW		Adding PRAM selectable Initiator ID stuff.
	  <SM14>	  5/5/93	PW		Making changes to get this to work in ROM on PDM EVT2.
	  <SM13>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	  <SM12>	  4/8/93	DCB		Added Initialization code for Wombat class machines.
	  <SM11>	 3/29/93	PW		Changed PDM's characteristic to hasDMA=true.
	   <LW7>	 4/30/93	DCB		Blocking interrupts around installation to prevent VBLs etc from
									stepping on us.
	   <LW5>	 4/14/93	DCB		Added AppleSim function to prevent installation of SIMs if they
									are already there.
	   <LW4>	 3/26/93	PW		Changed the names of some of the hw desc fields
									(dreqNeedsSwapMMU, dmaType etc). Slight rearrangement into
									default, special case.
	   <LW3>	 2/17/93	PW		Began adding dual-interrupt support for Quadras.
	  <SM10>	 3/22/93	PW		Removing DMA support for PDM because DMA reads kills DMA writes
									on all other channels.
	   <SM9>	 3/20/93	PW		Rolled back the fixed changes for <SM7>. Mostly for dual-bus
									support for Quadras and lots of little PDM things.
	   <SM8>	 3/17/93	DCB		Rolled out Changes for <SM7> which broke the build.
	   <SM7>	 3/16/93	PW		Began adding dual-interrupt support for Quadras.  Rearranged for
									easier universalization.
	   <SM6>	 1/31/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <LW2>	 1/27/93	PW		Starting to rewrite for Universalizing this blasted file.
	   <SM5>	11/20/92	DCB		Added Gestalt scsiSelector
	   <SM4>	 8/24/92	PN		Take out CycloneboxEVT1 stuff
	   <SM3>	 7/28/92	PW		Got rid of unused variable warning.
	   <SM2>	 7/28/92	PW		Removed blocking of interrupts because of a VM habit of
									rejecting LockMemory if ints are nonzero.  NOT the final
									solution.
	   <SM1>	 7/24/92	PW		New Today.

*/

#include <SysEqu.h>
#include <Memory.h>
#include <SCSIStandard.h>
#include <GestaltEqu.h>
#include <GestaltPrivateEqu.h>
#include <Start.h>
#include <SCSI.h>
#include <Slots.h>
#include <GrandCentralPriv.h>

#ifndef SCSI2Base
#define SCSI2Base 0x1FF0			/*[GLOBAL VAR]  (long) base address for 2nd SCSI chip read*/
#endif

#include "SCSIDebug.h"
#include "ACAM.h"
#include "XPT.h"
#include "SIMCore.h"
#include "BootItt.h"
#include "HALc96.h"
#include "SCSIGlue.h"
#include "XPTPriv.h" //!!! We need to move the SCSIGlobals struct to XPT.h!
#include "SIMCorePriv.h"


pascal	OSErr IttGestalt( OSType scsiSelector,long * response );	//	<SM5>
Boolean	AppleSIMS( void );

extern short	BlockInterrupts(void);
extern void		UnblockInterrupts( short oldSR);


/*********************************************************************************
	InitItt	-	initialize Cousin Itt
	
	See, the way it works is this.
		• InitItt initializes the XPT by calling InitXpt
		• InitItt initializes the HAL HW by calling Init53c9xHW
		• InitItt initializes the HAL SW by calling Init53c9xSW
			• The HAL actually has to register itself with SIMCore 
				it calls SIMRegisterHAL
				• SIMCore must register the new HBA with the XPT
					it calls SCSIRegisterBus
					• The XPT allocates all of the statics for both HAL and SIMCore
						The XPT returns to the SIM 
				• The SIM sets up its statics and returns to the HAL
			• The HAL sets up its statics and it's done and returns to InitItt
		• InitItt does the same for each HBA it knows about (i.e. motherboard buses)
		• InitItt calls NewGestalt to announce our arrival
		
*********************************************************************************/

long	
InitItt()
{
	long					err;
	HBADesc_53c9x *			hwDescPtr;
	//SelectorFunctionProcPtr	oldGestalt;
	HALc96Globals *			halg0;
	HALc96Globals *			halg1;
	SIMglobals *			simg0;
	SIMglobals *			simg1;
	XPTglobals *			xptg;
	ushort					oldSR;
	Boolean					reregister;
	enum					{kPDM, kCyclone, kRealQuadra, kWombat, kTNT} cpu;
	long					gstlt;
#if forPDMProto
	Boolean					onPDM_EVT1;
#endif
	
#if forIttInit

	// Don't install on non-universal machines
	// Should I check for Gestalt being implemented?
	if( Gestalt('hdwr', &gstlt) )
		return(-1);

	if( (gstlt & (1 << gestaltHasUniversalROM)) == 0 )
		return(-1);

#endif
	if ( ! TestFor_SCSI96_1Exists())	// At least one 53c96?
		return (-1);					//   no- exit w/err

	oldSR = BlockInterrupts();	//-> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> ->
	
	if ( TestFor_HMCDecoder() ) {
		cpu = kPDM;
#if forPDMProto
		if (*(char *)0xcb3 == 0x44)
			onPDM_EVT1 = true;
		else
			onPDM_EVT1 = false;
#endif
	}
	else if ( TestFor_PSCExists()) {
		cpu = kCyclone;
	}
	else if ( TestFor_OrwellExists()) {
		cpu = kRealQuadra;
	}
	else if ( TestFor_djMEMCExists()) {
		cpu = kWombat;
	}
	else if ( TestFor_GrandCentralExists()) {
		cpu = kTNT;
	}
	else {
		UnblockInterrupts( oldSR); 		//<- <- <- <- <- <- 
		return (-1);
	}
		
	if (err = InitXPT()) {			// always need to init the XPT first
		IfDebugStr("\pInitXPT failed");
		UnblockInterrupts( oldSR); 		//<- <- <- <- <- <- 
		return (-1);
	}
	
#if forIttInit

// First we need to fix a bug in the deferred task manager.  The System 7
// link patch "fixes" a QuickMail server bug by adding code to reduce interrupts
// everytime we attempt do dispatch tasks - even if if the DTQueue is busy and
// we aren't going to do anything this go-round.  If an interrupt is pending at
// this point it is happens even though we haven't RTE'd from the interrupt we
// were just completing.  If this happens back to back to ... then we fill up the
// stack with interrupt stack frames until we collide with the heap.
// SuperMario ROMs do not do this so I assume CE fixed their bug long ago.  Since
// the "fix" for them makes it impossible for me to use the Deferred Task Manager
// I am stuffing the original ROM vector back in so it won't lower interupts prior
// to doing the RTE.

#define	jDisptch	0x6e4	// Low mem vector for deferred task manager

{
	ushort	*instr;
	
	instr = *(ushort **)jDisptch;
	
	// Check to see if the patch is installed
	if( instr[0] == 0x4eb9 &&	// jsr 4080a1ee (_DTInstall + 1e)
		instr[1] == 0x4080 &&
		instr[2] == 0xa1ee &&
		instr[3] == 0x027c &&	// andi.w #f8ff, sr
		instr[4] == 0xf8ff &&
		instr[5] == 0x4e75 )	// rts
	{
		// Stuff the old vector back in.  This address is correct for
		// all IIci based ROMs.  Note that if this isn't a IIci based
		// ROM then the above patch wouldn't call 0x4080a1ee.
		*(ulong *)jDisptch = 0x4080a1ee;
	
	}
		// else leave it alone

}
#endif


	reregister = AppleSIMS();	// if our SIMs are already there, do a REregister instead
	
	hwDescPtr = (HBADesc_53c9x *) NewPtrSysClear( sizeof(HBADesc_53c9x));		//&&&& NewPtrSysClear

	if (hwDescPtr==0) {
		IfDebugStr("\pCan’t allocate hwDesc");
		UnblockInterrupts( oldSR); 		//<- <- <- <- <- <- 
		return (-1);
	}	


//……………… Prep for Initializing First Bus ………………

//--- Default Values (except addresses)

	hwDescPtr-> baseRegAddr = *(Ptr *)SCSIBase;	// base addr of c9x registers (offset of $10 between regs
	hwDescPtr-> pdmaAddr = hwDescPtr->baseRegAddr+0x100;	// addr of Pseudo-dma access
	hwDescPtr-> pdmaNonSerlzdAddr = hwDescPtr->pdmaAddr;	// default to no non-serialized space
	hwDescPtr-> jvClearSCSIIRQ = ClearVIASCSIIRQ;
	hwDescPtr-> jvEnableSCSIIRQ = EnableVIASCSIIRQ;
	hwDescPtr-> jvDisableSCSIIRQ = DisableVIASCSIIRQ;
	hwDescPtr-> jvTestSCSIIE = TestVIASCSIIE;
	hwDescPtr-> HBAisFast = false;				// set if c9x part capable of Fast Synchronous (10MB/S)
	hwDescPtr-> HBAisDiff = false;				// set if c9x part capable of differential
	hwDescPtr-> intOSNumberSCSI = 0;			// OS registration number for the SCSI interrupt
	hwDescPtr-> intSensSCSI = LEVEL;			// EDGE vs LEVEL vs STICKYBIT sensitive int
	hwDescPtr-> intOSNumberDMA = 0;				// OS registration number for the DMA interrupt 
	hwDescPtr-> intTypeDMA = SHARED_VIA;		// type of interrupt control (shared VIA bit, etc.) 
	hwDescPtr-> intSensDMA = LEVEL;				// EDGE vs LEVEL vs STICKYBIT sensitive int
	hwDescPtr-> intDREQbitNum = 0;				// 
	hwDescPtr-> intIRQbitNum		= 3;		// IRQ = bit 3
	hwDescPtr-> enableIRQvalue		= (1<<3)+0x80;
	hwDescPtr-> disableIRQvalue		= (1<<3);
	hwDescPtr-> testIRQenableValue	= (1<<3);
	hwDescPtr-> clearIRQvalue		= (1<<3)+0x80;
	hwDescPtr-> dreqNeedsSwapMMU = false;		// set if dreq status bit is in DAFB register
	hwDescPtr-> HBAhasDMA = false;				// set if true DMA available
	hwDescPtr-> HBAhasPseudoDMA = true;			// set if Pseudo-DMA available
	hwDescPtr-> HBAhasHskPseudoDMA = true;		// set if handshaked pseudo-DMA available
	hwDescPtr-> intTypeSCSI = INDEPENDENT_VIA;	// type of interrupt control (shared VIA bit, etc.) 
	hwDescPtr-> dmaType = dmaTypeNone;			// type of DMA controller
	hwDescPtr-> usesThreshold8 = false;			// doesn't use threshold 8 mode
	
	if( Gestalt('cput',&gstlt) == noErr && gstlt == gestaltCPU601  )
		hwDescPtr-> using601Emulator = true;	// running emulated
	else
		hwDescPtr-> using601Emulator = false;	// running native 68K


//--- Fields specific to different CPUs 
	
	switch (cpu) {
	case kPDM:
		hwDescPtr-> dreqAddr = (Ptr)0x50F26003;
		hwDescPtr-> intEnableSCSIAddr = (Ptr)0x50f26013;
		hwDescPtr-> intFlagSCSIAddr = (Ptr)0x50f26003;
		hwDescPtr-> HBAhasDMA = true;
		hwDescPtr-> HBAhasPseudoDMA = true;
		hwDescPtr-> HBAhasHskPseudoDMA = true;
		hwDescPtr-> intTypeSCSI = INDEPENDENT_VIA;
		hwDescPtr-> dmaType = dmaTypeAMIC;
		hwDescPtr-> dmaAlignmentSize = 8;
		hwDescPtr-> usesThreshold8 = true;

#if forPDMProto
		if (onPDM_EVT1) {
			hwDescPtr-> HBAhasPseudoDMA = true;		// pseudo-DMA is supported on old AMIC
			hwDescPtr-> HBAhasHskPseudoDMA = false;	// but, handshaked pseudo-DMA isn't
			hwDescPtr-> HBAhasDMA = true;			// true DMA available kinda
		}
#endif		
		if ( TestFor_SCSI96_2Exists()) {			// if 2 buses, this is the FC96 NOT the Curio
			hwDescPtr-> dmaCntrlAddr = (Ptr)0x50F32009;
			hwDescPtr-> dmaBaseAddr = (Ptr)0x50F32004;
			hwDescPtr-> HBAisFast = true;
			hwDescPtr-> intIRQbitNum		= 6;			// IRQ = bit 6
			hwDescPtr-> enableIRQvalue		= (1<<6)+0x80;
			hwDescPtr-> disableIRQvalue		= (1<<6);
			hwDescPtr-> testIRQenableValue	= (1<<6);
			hwDescPtr-> clearIRQvalue		= (1<<6)+0x80;
			hwDescPtr-> intDREQbitNum = 2;					// DRQ = bit 2
		}
		else {				// if just 1 bus, this is the Curio - MAKE SURE 2nd VERSION CHANGES !
			hwDescPtr-> dmaCntrlAddr = (Ptr)0x50F32008;
			hwDescPtr-> dmaBaseAddr = (Ptr)0x50F32000;
			hwDescPtr-> intIRQbitNum		= 3;			// IRQ = bit 3
			hwDescPtr-> enableIRQvalue		= (1<<3)+0x80;
			hwDescPtr-> disableIRQvalue		= (1<<3);
			hwDescPtr-> testIRQenableValue	= (1<<3);
			hwDescPtr-> clearIRQvalue		= (1<<3)+0x80;
			hwDescPtr-> intDREQbitNum = 0;					// DRQ = bit 0
		}
	
		break;

	case kRealQuadra:
		// Pseudo-dma non-serialized access (non-decoded in HW, different page table entry)
		hwDescPtr-> pdmaNonSerlzdAddr = hwDescPtr->pdmaAddr+0x40000;
		hwDescPtr-> dafbAddr = (Ptr)0xF9800024;				// addr of dafb register to init
		hwDescPtr-> dreqAddr = hwDescPtr->dafbAddr + 2;		// addr of dafb register with DREQ bit
		hwDescPtr-> intEnableSCSIAddr = (Ptr)0x50f03c13;
		hwDescPtr-> intFlagSCSIAddr = (Ptr)0x50f03a03;
		hwDescPtr-> intSensSCSI = EDGE;
		hwDescPtr-> dreqNeedsSwapMMU = true;
		hwDescPtr-> intDREQbitNum = 1;
		hwDescPtr-> needsDAFBinit = true;					// Quadras need their DAFB inited
		hwDescPtr-> HBAhasDMA = false;
		hwDescPtr-> HBAhasPseudoDMA = true;
		hwDescPtr-> HBAhasHskPseudoDMA = true;
		if ( TestFor_SCSI96_2Exists()) 
			hwDescPtr-> intTypeSCSI = SHARED_VIA;		// if 2 buses, this is a shared via bit for int
		else
			hwDescPtr-> intTypeSCSI = INDEPENDENT_VIA;	// if 1 bus, this is an independent bit in via
	
		break;

	case kWombat:
		hwDescPtr-> dreqAddr = (Ptr)0x50f03a00;
		hwDescPtr-> intEnableSCSIAddr = (Ptr)0x50f03c13;
		hwDescPtr-> intFlagSCSIAddr = (Ptr)0x50f03a03;
		hwDescPtr-> intSensSCSI = EDGE;
		hwDescPtr-> dmaType = pdmaTypeBIOS;
	
		break;
		
	case kCyclone:
		hwDescPtr-> pdmaAddr = (Ptr)0;
		hwDescPtr-> pdmaNonSerlzdAddr = (Ptr)0;
		hwDescPtr-> dreqAddr = (Ptr)0x50f03a00;
		hwDescPtr-> intEnableSCSIAddr = (Ptr)0x50f03c00;
		hwDescPtr-> intFlagSCSIAddr = (Ptr)0x50f03a00;
		hwDescPtr-> HBAhasDMA = true;
		hwDescPtr-> HBAhasPseudoDMA = false;
		hwDescPtr-> HBAhasHskPseudoDMA = false;
		hwDescPtr-> intTypeSCSI = INDEPENDENT_VIA;
		hwDescPtr-> dmaType = dmaTypePSC;
		hwDescPtr-> dmaAlignmentSize = 16;
			
		break;
		
	case kTNT:
		// SCSI96_1 is by convention the internal bus (53CF96)
		// This bus is known in the Grand Central literature as SCSI1.
		hwDescPtr-> pdmaAddr = (Ptr)0x5FFF8001;				// ain’t no such thing
		hwDescPtr-> pdmaNonSerlzdAddr = (Ptr)0x5FFF8001;	// ain’t no such thing
		hwDescPtr-> dreqAddr = (Ptr)0xF301A000;				// in Generic Board Register (Proto2)
		hwDescPtr-> intEnableSCSIAddr = (Ptr)0xF3000024;	// 32-bit access only!
		hwDescPtr-> intFlagSCSIAddr = (Ptr)0xF300002C;		// 32-bit access only!
		hwDescPtr-> dmaCntrlAddr = (Ptr)0xF3008A00;			// 32-bit access only!
		hwDescPtr-> jvClearSCSIIRQ = ClearGCSCSI1IRQ;
		hwDescPtr-> jvEnableSCSIIRQ = EnableGCSCSI1IRQ;
		hwDescPtr-> jvDisableSCSIIRQ = DisableGCSCSI1IRQ;
		hwDescPtr-> jvTestSCSIIE = TestGCSCSI1IE;
		hwDescPtr-> HBAisFast = true;
		hwDescPtr-> HBAhasDMA = true;						// got the old DB-DMA thing
		hwDescPtr-> HBAhasPseudoDMA = false;
		hwDescPtr-> HBAhasHskPseudoDMA = false;
		hwDescPtr-> intIRQbitNum = gcifDevSCSI1;
		hwDescPtr-> intDREQbitNum = 7;
		hwDescPtr-> intOSNumberSCSI = gcifDevSCSI1;
		hwDescPtr-> intTypeSCSI = GRAND_CENTRAL;
		hwDescPtr-> intOSNumberDMA = gcifDmaSCSI1;
		hwDescPtr-> intTypeDMA = GRAND_CENTRAL;
		hwDescPtr-> dmaType = dmaTypeGC;					// type of DMA controller
		hwDescPtr-> dmaAlignmentSize = 1;					// no alignment restrictions
		
		break;
	}


//……………… Do Initialization of first bus ………………

	ReadInitiatorID(hwDescPtr);				// read Initiator ID into hwDesc
	if (err = Init53c9xHW(hwDescPtr)) {		// will want to see if TERROR already did this init
		IfDebugStr("\pInit53c9xHW 1 failed");
		UnblockInterrupts( oldSR); 		//<- <- <- <- <- <- 
		return (-1);
	}	

	if (reregister)
		halg0 = (HALc96Globals *)ReInitHAL(hwDescPtr, 0);	// re-init the HAL at bus #0
	else
		halg0 = (HALc96Globals *)Init53c9xSW(hwDescPtr);	// init the HAL

	if (halg0 == 0) {
		IfDebugStr("\pInit53c9xSW 1 failed");
		UnblockInterrupts( oldSR); 		//<- <- <- <- <- <- 
		return (-1);
	}	

	SCSIGlobals->numBEHs = 0;
	SCSIGlobals->berr_halg0 = (Ptr)halg0;
	

	
//……………… Prep for Initializing external HBA for Dual-Bus Machines ………………
	
	if ( TestFor_SCSI96_2Exists()) 
	{
		hwDescPtr-> baseRegAddr = *(Ptr *)SCSI2Base;		// base addr of c9x registers (offset of $10 between regs
		hwDescPtr-> pdmaAddr = hwDescPtr->baseRegAddr+0x100;	// addr of Pseudo-dma access
		hwDescPtr-> pdmaNonSerlzdAddr = hwDescPtr->pdmaAddr;	// default to no-nonserialized access
		hwDescPtr-> HBAisFast = false;

		switch (cpu) {
		case kPDM:				// if 2 buses, this is the Curio NOT the FC96 
			hwDescPtr-> dmaCntrlAddr = (Ptr)0x50F32008;
			hwDescPtr-> dmaBaseAddr = (Ptr)0x50F32000;
			hwDescPtr-> intIRQbitNum		= 3;			// IRQ = bit 3
			hwDescPtr-> enableIRQvalue		= (1<<3)+0x80;
			hwDescPtr-> disableIRQvalue		= (1<<3);
			hwDescPtr-> testIRQenableValue	= (1<<3);
			hwDescPtr-> clearIRQvalue		= (1<<3)+0x80;
			hwDescPtr-> intDREQbitNum = 0;					// DRQ = bit 0
			
			break;
		
		case kRealQuadra:		// Quadra 9x0
			hwDescPtr-> pdmaNonSerlzdAddr = hwDescPtr->pdmaAddr+0x40000;
			hwDescPtr-> dafbAddr = (Ptr)0xF9800028;				// addr of dafb register to init
			hwDescPtr-> dreqAddr = hwDescPtr->dafbAddr + 2;		// addr of dafb register with DREQ bit
			hwDescPtr-> intTypeSCSI = SHARED_VIA;
			
			break;

		case kTNT:
			// SCSI96_2 is by convention the external bus (CURIO 53C94 cell)
			// This bus is known in the Grand Central literature as SCSI0.
			hwDescPtr-> pdmaAddr = (Ptr)0x5FFF8001;				// ain’t no such thing
			hwDescPtr-> pdmaNonSerlzdAddr = (Ptr)0x5FFF8001;	// ain’t no such thing
			hwDescPtr-> dreqAddr = (Ptr)0xF301A000;				// in Generic Board Register (Proto2)
			hwDescPtr-> intEnableSCSIAddr = (Ptr)0xF3000024;	// 32-bit access only!
			hwDescPtr-> intFlagSCSIAddr = (Ptr)0xF300002C;		// 32-bit access only!
			hwDescPtr-> dmaCntrlAddr = (Ptr)0xF3008000;			// 32-bit access only!
			hwDescPtr-> jvClearSCSIIRQ = ClearGCSCSI0IRQ;
			hwDescPtr-> jvEnableSCSIIRQ = EnableGCSCSI0IRQ;
			hwDescPtr-> jvDisableSCSIIRQ = DisableGCSCSI0IRQ;
			hwDescPtr-> jvTestSCSIIE = TestGCSCSI1IE;
			hwDescPtr-> HBAhasDMA = true;						// got the old DB-DMA thing
			hwDescPtr-> HBAhasPseudoDMA = false;
			hwDescPtr-> HBAhasHskPseudoDMA = false;
			hwDescPtr-> intIRQbitNum = gcifDevSCSI0;
			hwDescPtr-> intDREQbitNum = 6;
			hwDescPtr-> intOSNumberSCSI = gcifDevSCSI0;
			hwDescPtr-> intTypeSCSI = GRAND_CENTRAL;
			hwDescPtr-> intOSNumberDMA = gcifDmaSCSI0;
			hwDescPtr-> intTypeDMA = GRAND_CENTRAL;
			hwDescPtr-> dmaType = dmaTypeGC;					// type of DMA controller
			hwDescPtr-> dmaAlignmentSize = 1;					// no alignment restrictions
			
			break;
		}


	//……………… Do Initialization of second bus ………………

		ReadInitiatorID(hwDescPtr);				// read Initiator ID into hwDesc
		if (err = Init53c9xHW(hwDescPtr)) {		// will want to see if TERROR already did this init
			IfDebugStr("\pInit53c9xHW 2 failed");
			UnblockInterrupts( oldSR); 		//<- <- <- <- <- <- 
			return (-1);
		}	

		if (reregister)
			halg1 = (HALc96Globals *)ReInitHAL(hwDescPtr, 1);	// re-init the HAL at bus #1
		else
			halg1 = (HALc96Globals *)Init53c9xSW(hwDescPtr);	// init the HAL

		if (halg1 == 0) {
			IfDebugStr("\pInit53c9xSW 2 failed");
			UnblockInterrupts( oldSR); 		//<- <- <- <- <- <- 
			return (-1);
		}	
			
		SCSIGlobals->berr_halg1 = (Ptr) halg1;
	
		halg0->otherHALg = (void *)halg1;
		halg1->otherHALg = (void *)halg0;
		
		xptg = GetXPTg();	// From the SCSIGlobals
		
			
		// Just like the HAL the SIM needs to know about the other bus	
		simg0 = (SIMglobals *)(((xptg->BusInfoPtr[0])->initInfo).SIMstaticPtr);
		simg1 = (SIMglobals *)(((xptg->BusInfoPtr[1])->initInfo).SIMstaticPtr);
		
		simg0->otherSIMg = (Ptr)simg1;			
		simg1->otherSIMg = (Ptr)simg0;			
		
		
	}
	
	UnblockInterrupts( oldSR); //<- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- <- 
	
	if( NewGestalt(gestaltSCSI,IttGestalt) ) {
		// if there is already one there, we need to get the old values and change only
		//	those feature bits that change because of this new (apparently) RAM resident Itt code
		//	then we need to replaceGestalt it.		** But for now, nothing changes **
		//ReplaceGestalt(gestaltSCSI,IttGestalt,&oldGestalt );
	}
#if forIttInit
	INITSCSIBOOT();
#endif
		
	return (0);
}



/*********************************************************************************
	IttGestalt 	-	
*********************************************************************************/

pascal OSErr 
IttGestalt( 
	OSType scsiSelector,
	long * response )
{
#pragma unused(scsiSelector);

	*(ulong *)response = 1<<gestaltAsyncSCSI;
	
#if ForROM
#if !forIttInit
	*(ulong *)response |= (1<<gestaltAsyncSCSIINROM) + (1<<gestaltSCSISlotBoot);
#endif
#endif
	return(0);
}


/*********************************************************************************
	AppleSIMS 	-	
*********************************************************************************/

Boolean
AppleSIMS( void )
{
	SCSIBusInquiryPB scPB;

	Clear((char *)&scPB,sizeof(scPB));
	scPB.scsiFunctionCode = SCSIBusInquiry;
	scPB.scsiPBLength = sizeof(SCSIBusInquiryPB);
	scPB.scsiCompletion = nil;
	if (SCSIAction( (SCSI_PB *) &scPB ))	// Get info for the internal (first) bus
		return(false);
	
	if( *(long *)&scPB.scsiSIMVendor == 'Appl' &&
			*(long *)&scPB.scsiSIMVendor[4] == 'e Co' &&
			*(long *)&scPB.scsiSIMVendor[8] == 'mput' )
		return(true);
	else
		return(false);
}

