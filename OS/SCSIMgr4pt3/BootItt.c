/*
	File:		BootItt.c

	Contains:	Code that loads in SCSI Drivers at boot time

	Entry points:	InitSCSIBoot
					IttBoot
					IsItt

	Written by:	Clinton Bauder

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SM36>	 1/28/94	chp		Move a local variable declaration inside a conditional
									compilation block so it won't generate a compiler warning when
									it is not used.
	  <SM35>	 1/25/94	DCB		Fixed a minor error in the way we interpret PRAM.  The code was
									assuming that SCSI ID 7 had a fixed unit table entry which is
									not true.  (only 0-6)
	  <SM34>	 1/13/94	chp		Adjust the usage of dNeedLock and dRAMBased, since the former
									local definitions were different than the constants defined in
									Inside Mac, and now in Devices.h.
	  <SM33>	 1/13/94	chp		Modify SOpenDriver to use new driver types in Devices.h.
	  <SM32>	11/22/93	pdw		Rolling in from <MCxx>.
	   <MC5>	 11/9/93	pdw		Fixed problem with almost-bootable floppies.  IttBoot now
									returns the refNum of the default disk whenever it sees it.  We
									also init SCSIDrvrs in here and call InitSCSIBoot from InitItt
									instead of from StartSearch.
	  <SM31>	10/29/93	DCB		Don't load SIMs from the SlotManager at INIT time.
	  <SM30>	10/14/93	pdw		<MC> roll-in.
	   <MC3>	 9/26/93	pdw		Fixed a little problem with the forceBoot stuff - should work
									just fine now.
	   <MC2>	 9/26/93	pdw		Added forceBoot ability, fixed CmdShOptDel, fixed multi-bus
									booting bugs, a couple of other little bug fixes/changes.
	  <SM29>	 9/12/93	pdw		Name changes.  Added start of check for VirtualID info for
									generating mask when running post-boot.
	  <SM28>	  9/9/93	pdw		Lots of little changes.  Name changes, temporary cache_bug
									stuff.
	  <SM27>	 8/23/93	pdw		Added support for LimitPRAMClear, IgnoreCmdOptShDel,
									LoadDefaultOnly - three options required for AIX security,
									enabled by setting bits in PRAM $76.
	  <SM26>	  7/8/93	pdw		Changed some shorts to longs.
	  <SM25>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
									stack switching mechanism.  Adding support for Cold Fusion.
									Rearranging HW/SW Init code. Some code optimizations.
	  <SM24>	 5/31/93	PW		Made references to block numbers in the DDM and the Partition
									map relative to the DDM.
	  <SM23>	 5/29/93	PW		Quoting instead of <> StandardGlue.h
	  <SM22>	 5/29/93	PW		Started putting in AIX boot stuff.  Added check for PRAM OSType
									instead of constant sbMac check.
	  <SM21>	 5/25/93	DCB		Rollin from Ludwig. (The next two items below)
	  <LW14>	 5/24/93	PW		Fixing "conflict with Figment" bug which is actually our failing
									to clear a parameter block before using it.
	  <LW13>	 5/21/93	PW		Using scsiMaxTarget in BusInquiry for highestSCSIID instead of
									figuring it out based on scsiBusWideXX characteristics.
	  <SM20>	 5/24/93	PW		Fixing "conflict with Figment" bug which is actually our failing
									to clear a parameter block before using it.
	  <SM19>	  5/5/93	PW		Converted names to meanies-friendly names.
	  <LW11>	 3/26/93	PW		Cleared parameter blocks before using them.
	  <SM17>	 3/20/93	PW		Included SysEqu.
	  <LW10>	 3/23/93	DCB		Fixed a bug which prevented bootable CDs from booting.  We need
									to ignore Data Run errors at least until we have read block
									zero.  For now we will ignore them completely.
	   <LW9>	 3/10/93	DCB		Fixed a shine-through problem (again) which caused the high
									nybble of D5 to get loaded with a weird value when loading
									drivers.
	   <LW8>	  3/8/93	DCB		Fixed bug where startup disk wouldn't boot if CMD_OPT_SHFT_DEL
									was released after nothing else booted.
	   <LW7>	  3/8/93	PW		Included SysEqu.
	   <LW6>	  3/1/93	DCB		Changed startup PRAM to match slot drivers. Also added code to
									scan for srsrcs of type SIM.
	   <LW5>	 2/17/93	PW		Got rid of TIB - no longer supported.
	   <LW4>	 2/13/93	PW		Moved SetLoadFlag macro from BootItt.h to a routine in BootItt.c
									for SCSIDrvrs lo-mem support.
	  <SM15>	  2/1/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <LW3>	 1/27/93	DCB		Added code for CmdOptShiftDel startup sequence to fix Radar Bug
									1051033.
	   <LW2>	 1/27/93	PW		Changed kSlow to scsiTransferPolled.
	  <SM14>	 12/9/92	PW		Removed scsiDoVirtualMap flag so I had to remove its use in
									BootItt.
	  <SM13>	 12/5/92	PW		Changed some names mostly.
	  <SM12>	 12/4/92	CB		Added Support for booting drives with a non-512 byte block size.
									(CD-ROMs, some MOs etc.)
	  <SM11>	11/24/92	PW		Narrowed check for same VID info to only same bus for old driver
									loading qualification.
	  <SM10>	11/20/92	DCB		Added explicit clear of the scsiCompletion field and setup of the
									length field for SCSIActions
	   <SM9>	10/30/92	DCB		Added a workaround for the Conner bug so that we can boot with
									those drives.
	   <SM8>	 10/8/92	DCB		Changed offset for new driver loading to 8 bytes. This gives
									driver writers greater flexibility.
	   <SM7>	 10/8/92	PW		(dcb) Added support for variable sized SCSI_IOs.  Lots of
									trivial name changes.
	   <SM6>	 9/17/92	PW		Changed SCSI_DriverPB to SCSI_Driver_PB.
	   <SM5>	 8/31/92	DCB		Fixed a problem with reading partition maps that had more than
									one driver entry which caused disks to not mount.
	   <SM4>	 8/20/92	DCB		Changed boot code so it no longer used Select w/Atn to solve a
									problem with Conner drives.
	   <SM3>	 7/28/92	PW		Resolve differences between pdw and (d)cb sources.
	   <SM2>	 7/28/92	PW		Added this comment.
		 <0>	 6/24/92	DCB		New Today 

*/

#include <Types.h>
#include <Packages.h>
#include <Memory.h>
#include <Traps.h>
#include <OSUtils.h>
#include <TrapsPrivate.h>
#include <SysEqu.h>
#include <SCSIStandard.h>
#include <SCSI.h>
#include <OSUtils.h>
#include <Devices.h>
#include <Slots.h>
#include <Start.h>

//#include "IPLRecord.h"

#include "SCSIDebug.h"
#include "CUtils.h"
#include "ACAM.h"
#include "XPT.h"
#include "XPTpriv.h"

#include "BootItt.h"


short	ScanDrive( DevInfo *, BootInfo *, Boolean * forceBootablePtr);
short	AttemptDriverLoad( DevInfo *, BootInfo *, Boolean * forceBootablePtr);
short	ScRead(DevInfo *, ulong, ulong,ushort, Ptr);
ulong	CheckSumDrvr( Ptr driver,ushort length );
void	SetLoadFlag( BootInfo * BInfo, DeviceIdent devIdent);
short	LoadDriver( DevInfo *, ulong, ulong, Boolean, Ptr, Ptr, Partition * );
Boolean	Ck4EjectableVolume( short drvrRefNum);
void	DummyOldCallRead( short scsiID);


#define	DONT_WAIT 1
#define	KEEP_WAITING 0


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
	ISITT 	-	
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

Boolean ISITT()
{
	return( NGetTrapAddress(SCSIATOM, OSTrap) != 
			NGetTrapAddress(UNIMPTRAP, ToolTrap) );
}

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
	INITSCSIBOOT 	-	
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

void INITSCSIBOOT( void )
{
	BootInfo 	*BInfo;
	ushort		numBuses, bus;
	XPTglobals 	*XPTg;				// We will store our globals with the XPTs globals
	SCSIBusInquiryPB		scPB;	// Info about the scsi buses
	SCSIGetVirtualIDInfoPB	vidPB;	// to determine (at init time) if we need to mask in SCSIDrvrs
	
#if ForROM
#if !forIttInit
	
	char		macIDpram;

// Since the XPT isn't loaded at PrimaryInit and since SecondaryInit is too late
// to load a SCSI Interface Module (SIM) we are going to try and help NuBus and
// PDS developers out by loading SIMs here at the start of StartSearch.  We do
// this by loading sRSRCs of Category CatIntBus and cType TypSIM. Slots are 
// searched for sRSRCs of this type and then loaded as a driver.
	
	SpBlock		tempSp;				// Slot Manager PB used to locate SIMs
	SpBlock		loadSp;				// Slot Manager PB used to load SIMs
	SEBlock		simSe;				// exec block that will be passed to each slot SIM

	/* Start with slot zero and look from there... */
	tempSp.spSlot =  0;		tempSp.spID = 0;		tempSp.spExtDev = 0;
	tempSp.spDrvrHW = 0;	tempSp.spHwDev = 0;
	tempSp.spTBMask = 3; /* don't pay attention to hardware or software vendors */
	tempSp.spCategory = CatIntBus;
	tempSp.spCType = TypSIM;
	tempSp.spDrvrSW = DrvrSwScsi43;
	
	while( SNextTypeSRsrc((SpBlockPtr)&tempSp) == noErr ) {	

		loadSp = tempSp;	/* Don't touch the original parameter block or SNext Loop will get
							   screwed up and will start at the begining again  */
		simSe.seSlot = loadSp.spSlot;
		simSe.sesRsrcId = loadSp.spID;
		loadSp.spsExecPBlk = (Ptr)&simSe;
		if (noErr == SGetDriver((SpBlockPtr)&loadSp)) {
			SOpenDriver((SpBlockPtr)&loadSp);
		}
	}
	
// Old SCSI Manager compatibility ÑÑÑÑ
//	Certain old applications and SCSI utilities use the SCSIDrvrs lo-mem.  We'll generate 
//	it's default value here by setting the host ID bit (found in byte 2 of PRAM).

	ReadXPRam( 1, 0x02, &macIDpram);		// read 1 byte at location 2
	SCSIDrvrs = 1 << ( macIDpram & 0x07 );	// set bit at host ID

#endif
#endif
	
	Clear( (char *)&scPB, sizeof(scPB));
	Clear( (char *)&vidPB, sizeof(vidPB));
	
// Find out how manuy buses there are in the sytem and alloc a BootInfo with that many IDmasks on the end

	scPB.scsiDevice.bus = -1;	// XPT=-1
	scPB.scsiFlags = 0;
	scPB.scsiFunctionCode = SCSIBusInquiry;
	scPB.scsiPBLength = sizeof(SCSIBusInquiryPB);		// <SM10>
	scPB.scsiCompletion = nil;							// <SM10>
	SCSIAction( (SCSI_PB *) &scPB );
	
	if ( scPB.scsiResult != noErr) {
		DebugStr("\pInitSCSIBoot:BusInquiry failed getting numBuses");
	}
	
	numBuses = scPB.scsiHiBusID + 1;		
	
	if( (BInfo = (BootInfo *)NewPtrSysClear(sizeof(BootInfo) + sizeof(ulong) * numBuses)) == nil )
		return;

// Get PRAM, Set up the BInfo and store it (in XPT's globals)

	GetDefaultStartup( &(BInfo->startPRAM));
	BInfo->BusCount = numBuses;
	BInfo->defltDrvrRefNum = KEEP_WAITING;
	
	XPTg = GetXPTg();
	XPTg->BootStorage = (Ptr)BInfo;
		
// Start with the mask so far of the drivers that we 
//	loaded at original boot time.  This is only needed
//	when we're running as an init or a patch (i.e. on Quadras).

	for (bus = 0; bus <= scPB.scsiHiBusID; bus+=1) {
		BInfo->IDmasks[bus] = SCSIDrvrs;	// change to check VirtualID!!!%%%_debugger

		vidPB.scsiDevice.bus = bus;
		vidPB.scsiDevice.targetID = 0;
		vidPB.scsiFlags = 0;
		vidPB.scsiFunctionCode = SCSIGetVirtualIDInfo;
		vidPB.scsiPBLength = sizeof(SCSIGetVirtualIDInfoPB);
		vidPB.scsiCompletion = nil;
		SCSIAction( (SCSI_PB *) &vidPB );
		
		if ( vidPB.scsiResult != noErr) {		// !!! _debugger WE NEED TO DO SOMETHING WITH THIS
		}
	}
}


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
	IttBoot 	-	
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

short
ITTBOOT( ulong onlyStartup, Boolean * forceBootPtr )
{
	SCSIGetVirtualIDInfoPB	getVIDPB;	/* for scanning for refNum-driven startup */
	SCSIBusInquiryPB		biPB;		/* Info about the scsi busses */
	BootInfo *	BInfo;
	SCSI_IO *	ioPtr;				/* Our SCSI Parameter block */
	uchar		busID;				/* Current scsi bus */
	char		hostSCSIID;			/* host Mac SCSI ID */
	char		highestSCSIID;		/* highest SCSI ID on this bus */
	char		scsiID;				/* Current target */
	DevInfo		device;				/* Current Device */
	DevInfo		fakeScanDevice;		/* Device ident used for fake scan of boot ID on higher priority buses */
	DevInfo		startdevice;		/* Startup Device */
	short		defRefNum = 0;		/* Default refnum for startup */
	short		forceBootRefNum =0;	/* Force boot (from specially marked ejectable media) */
	XPTglobals 	*XPTg;				/* We will store our globals with the XPTs globals */
	ulong		longPRAM;
	ushort		PRAMRefNum;
	char *		trashBlockPtr;
	ushort		maxSCPBSize;		// The largest PB we will need 				<SM7> pdw
	Boolean		foundBus;
	Boolean		csodKeysDown;
	Boolean		forcedBoot;
	Boolean		unknownPRAM;		// set when we figure out that we can't figure it out


//ÑÑÑ Initialization ÑÑÑ

	XPTg = GetXPTg();
	BInfo = (BootInfo *) XPTg->BootStorage;
	
	if ( (*(short *)(lm_KeyMap + 6) == (short) CmdShiftOptDel)  && !Ck4IgnoreCmdShOptDel()) {
		csodKeysDown = true;
		bset( kbCSOD, &(XPTg->flags));
	}
	else
		csodKeysDown = false;

// Initialize our 2 much-used PBs

	Clear( (char *)&biPB, sizeof(biPB));
	biPB.scsiFunctionCode = SCSIBusInquiry;
	biPB.scsiPBLength = sizeof(SCSIBusInquiryPB);
	
	Clear((char *)&getVIDPB, sizeof(getVIDPB));		
	getVIDPB.scsiFunctionCode = SCSIGetVirtualIDInfo;
	getVIDPB.scsiPBLength = sizeof(SCSIGetVirtualIDInfo);
				
// Find out just how big our ioPB needs to be

	biPB.scsiDevice.bus = -1;			// XPT (we're getting max size of all bus's PBs)
	SCSIAction( (SCSI_PB *) &biPB );
	if ( biPB.scsiResult != noErr) {
		IfDebugStr("\pIttBoot:BusInquiry failed getting maxSCPBSize");
		return (DONT_WAIT);
	}
	maxSCPBSize = biPB.scsiMaxIOpbSize;

// Initialize a 1 block trash buffer for our use

	if( (trashBlockPtr = NewPtrSysClear(0x200)) == nil ) 
		return (DONT_WAIT);		/* Try and boot with a driver that is already loaded... */

// Initialize a SCSI_IO parameter block for our use

	if( (ioPtr = (SCSI_IO *)NewPtrSysClear(maxSCPBSize)) == nil ) 
		return (DONT_WAIT);		/* Try and boot with a driver that is already loaded... */
	
	ioPtr->scsiPBLength = maxSCPBSize;

	device.ioPB = ioPtr;		/* Remember PB for later use */
	startdevice.ioPB = ioPtr;	/* Remember PB for later use */


//ÑÑÑ Deal with Default Boot Device first ÑÑÑ

// Determine the type of PRAM	

	unknownPRAM =false;
	
	//	If slot style PRAM... (new style)
	if( (BInfo->startPRAM.slotDev.sdSlotNum & 0xF0) == 0 ) {
	
		// Loop through Buses looking for one with this slot number and sRsrc ID

		foundBus = false;
		
		for( busID = 0; busID < BInfo->BusCount; busID+=1 ) {
			biPB.scsiDevice.bus = busID;
			SCSIAction( (SCSI_PB *) &biPB );	/* Get info for the internal (first) bus */
			if ( biPB.scsiResult != noErr)
				DebugStr("\pIttBoot:BusInquiry failed getting scsiHBAslotNumber");
			
			if( biPB.scsiHBAslotNumber == BInfo->startPRAM.slotDev.sdSlotNum &&
					biPB.scsiSIMsRsrcID == BInfo->startPRAM.slotDev.sdSRsrcID ) {
				device.DevIdent.diReserved	= 0;
				device.DevIdent.bus			= busID;
				device.DevIdent.targetID	= (BInfo->startPRAM.slotDev.sdExtDevID>>3) & 0x1f;		// upper 5 bits
				device.DevIdent.LUN			=  BInfo->startPRAM.slotDev.sdExtDevID     & 0x07;		// lower 3 bits

				if( device.DevIdent.LUN )	// Only do select w/atn + identify message for non-zero luns 
					device.IdentMsg = true;
				else
					device.IdentMsg = false;

				foundBus = true;
				break;	// from for loop
			}
		}
		
		if (!foundBus)
			defRefNum = DONT_WAIT;		// don't wait anymore
		else 
		{
			startdevice = device;
			
		// Don't load a driver from the startup device if CmdShiftOptDel keys are down
			
			if ( csodKeysDown ) {
				defRefNum = DONT_WAIT; 	// Tell WaitForInternal to stop trying
				bset( kbCSODatBoot, &(XPTg->flags));
			}
			else {
				// hit each device at this ID that might want higher priority VID mapping
				for( busID=0; busID<device.DevIdent.bus; busID+=1 ) {
					biPB.scsiDevice.bus = busID;
					SCSIAction( (SCSI_PB *) &biPB );
					fakeScanDevice = device;
					fakeScanDevice.DevIdent.LUN = 0;			// we just want to see if there's a device there
					if( biPB.scsiFeatureFlags & scsiBusOldCallCapable ) {
						/* Read block 0 of each device at this ID on other buses */
						fakeScanDevice.DevIdent.bus = busID;
						ScRead( &device, 0, 1, 512, trashBlockPtr );
					}
				}	
				// then try to load the driver for our specified boot device
				if( TestLoadFlag( BInfo, startdevice.DevIdent) )  {
					// we already hit the boot device, so we return that value
					defRefNum = BInfo->defltDrvrRefNum;	
				}
				else {
					defRefNum = AttemptDriverLoad( &startdevice, BInfo, forceBootPtr);
					BInfo->defltDrvrRefNum = defRefNum;
				}
			}
		}
	}
	
// if the PRAM is a fixed drefnum for a SCSI device... (old style)
	else 
	{
		startdevice.DevIdent.bus = -1;	// dummy value for now
		longPRAM = *(ulong *)&BInfo->startPRAM;
		PRAMRefNum = (ushort) (longPRAM & 0xFFFF);
		if( PRAMRefNum >= 0xFFD9 && PRAMRefNum <= 0xFFDF ) {
			device.IdentMsg = false;	// !!!
			device.DevIdent.diReserved	= 0;
			device.DevIdent.bus			= -1;	// dummy value for now
			device.DevIdent.targetID	= ~PRAMRefNum - 32;
			device.DevIdent.LUN			= 0;		/* Don't Scan LUNs */
		
		// If we have an old ID mapping already, we simply use that bus
		//	else, we need to scan all of the oldCallCapable buses until - 
		//	1. we find a device (getVID.scsiExists == true)  or,
		//	2. we run out of buses
		
			getVIDPB.scsiOldCallID = device.DevIdent.targetID;
			SCSIAction((SCSI_PB *) &getVIDPB);
			if ( getVIDPB.scsiResult != noErr) {
				IfDebugStr("\pIttBoot:getVID failed");
				return (DONT_WAIT);		// don't wait for it
			}

			if ( !getVIDPB.scsiExists )		// doesn't already exist? scan
			{
				// Scan OldCallCapable bus(es) until finding VID or running out of buses
				
				for ( busID = 0; busID<BInfo->BusCount; busID+=1 ) {
					biPB.scsiDevice.bus = busID;
					SCSIAction( (SCSI_PB *) &biPB );
					if( !(biPB.scsiFeatureFlags & scsiBusOldCallCapable))
						continue;
	
					DummyOldCallRead( device.DevIdent.targetID);
					
					// if old-ID mapping now exists, then no more scanning
					SCSIAction((SCSI_PB *) &getVIDPB);
					if ( getVIDPB.scsiExists )	{
						break;		// get out of loop
					}
				}
			}
			
			// after scan, if old-ID mapping now exists, this is the bus
			
			if (getVIDPB.scsiExists) 
			{
				device.DevIdent.bus = getVIDPB.scsiDevice.bus;
				startdevice = device;

				if( TestLoadFlag( BInfo, device.DevIdent) )  {
					// we already hit the boot device, so we return that value
					defRefNum = BInfo->defltDrvrRefNum;	
				}
				else if (csodKeysDown) {
					defRefNum = DONT_WAIT; 	// Don't WaitForInternal search keep trying
					bset( kbCSODatBoot, &(XPTg->flags));
				}
				else {
					defRefNum = AttemptDriverLoad( &device, BInfo, forceBootPtr);
					BInfo->defltDrvrRefNum = defRefNum;
				}
			}
			else
				defRefNum = KEEP_WAITING;	// no device yet - keep waiting
		}
		else  // unknown PRAM format
		{
			unknownPRAM = true;
			defRefNum = DONT_WAIT;		// don't wait anymore
		}
	}

// If we're not supposed to continue on and look for other disks, let's exit here

	if( onlyStartup || Ck4OnlyLoadFromDefault() ) {
		DisposPtr( (Ptr)ioPtr );
		DisposPtr( trashBlockPtr );
		return (defRefNum);
	}
	
	
//ÑÑÑ Scan all buses for other disks ÑÑÑ

	*forceBootPtr = false;	

	for( busID = 0; busID < BInfo->BusCount; busID+=1 ) {
		biPB.scsiDevice.bus = busID;
		SCSIAction( (SCSI_PB *) &biPB );	/* Get info for this bus */
	
		if ( biPB.scsiResult != noErr)
			DebugStr("\p IttBoot:BusInquiry failed getting scsiMaxTarget");

		highestSCSIID = biPB.scsiMaxTarget;
		hostSCSIID = biPB.scsiInitiatorID;
		
		for( scsiID = highestSCSIID; scsiID >= 0; scsiID-=1 ) {
			if (scsiID == hostSCSIID) {
				continue;
			}
			device.DevIdent.diReserved = 0;	
			device.DevIdent.bus = busID;
			device.DevIdent.targetID = scsiID;
			device.DevIdent.LUN = 0;	/* Don't Scan LUNs */
			device.IdentMsg = false;	// !!!
			if( TestLoadFlag(BInfo,device.DevIdent) ) {
				continue;	/* We have already made a decision on this */
			}
			if (unknownPRAM || !csodKeysDown) {
				forceBootRefNum = AttemptDriverLoad( &device, BInfo, &forcedBoot);
			}
			else if( device.DevIdent != startdevice.DevIdent) {
				bset( kbCSODatScan, &(XPTg->flags));
				forceBootRefNum = AttemptDriverLoad( &device, BInfo, &forcedBoot);
			}

		// If this last one was a force boot, remember that and its refNum
		
			if ( forcedBoot && forceBootRefNum<0)  {
				*forceBootPtr = true;	
				defRefNum = forceBootRefNum;
			}
		}
	}
	DisposPtr( (Ptr)ioPtr );
	DisposPtr( trashBlockPtr );
	
	return (defRefNum);
}

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
	AttemptDriverLoad 	-	
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

/* Attempt to load a driver for this device
**
** First ask the SIM to try.  If the SIM doesn't know how to do this or
** if it fails then we look at the device and try to load a driver from
** the device.  Failing this we again ask the SIM to try.  This allows
** SIMs to either over-ride drivers on the device or only install an emergency
** "There wasn't any other driver to boot with" driver
*/

short // refNum
AttemptDriverLoad( 
	DevInfo		* devInfoPtr,
	BootInfo	* BInfo,
	Boolean		* forceBootablePtr )
{
	SCSILoadDriverPB 	LoadPB;		/* PB for Loading SIM Drivers */
	short				dRefNum;	/* The driver we loaded */
	OSErr 				err;
	
	Clear((char *)&LoadPB,sizeof(LoadPB));
	
	dRefNum = 0;		// 0 means we haven't found it but we haven't given up
	LoadPB.scsiDevice = devInfoPtr->DevIdent;
	LoadPB.scsiCompletion = 0;
	LoadPB.scsiDiskLoadFailed = 0;
	LoadPB.scsiPBLength = sizeof(LoadPB);
	LoadPB.scsiFunctionCode = SCSILoadDriver;
	err = SCSIAction( (SCSI_PB *) &LoadPB );
	if( err != 0 || LoadPB.scsiLoadedRefNum == 0 ) {
		dRefNum = ScanDrive( devInfoPtr, BInfo, forceBootablePtr);
		if( dRefNum == 0 ) {
			LoadPB.scsiDiskLoadFailed = 1;
			if( SCSIAction( (SCSI_PB *) &LoadPB ) == noErr )
				dRefNum = LoadPB.scsiLoadedRefNum;
		}
	}
	else {
		dRefNum = LoadPB.scsiLoadedRefNum;	// <LW16> DCB
	}
	return ( dRefNum );
}

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
	ScanDrive 	-	
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

/* Scan The partition map for a driver and try to load it 
**
** First Examine the driver map in block 0
** If it was valid Load in Block 1 and find out if it is a new partition map
** If not we load the driver and assume it is of type "Apple_Driver"
** If it is a new map we scan for a Driver Partition Map which matches the
** Entry in the driver map (Block 0) and the first HFS Partition
** If all of that succeeds we attempt to load the driver.  "Apple_Driver43"s get
** a device Ident in d5 while older "Apple_Drivers" get a SCSI ID.
*/

short 
ScanDrive( 
	DevInfo 	* devInfoPtr,
	BootInfo 	* BInfo,
	Boolean		* forceBootablePtr )
{

	Block0		*realBlock0;	/* a buffer for block zero (Physical) */
	Partition	*curBlock;		/* the current block we are working on */
	Partition	*HFSBlock;		/* first HFS Partition map entry */
	Partition	*drvrBlock;		/* Driver's Partition map entry */
	ddMap		*bootDrvr;		/* Scratch */
	ushort		d;				/* driver index (for scanning DDM) */
	ulong		drvrBlockStart;	/* The starting block number of the driver */
	ushort		drvrSize;		/* The size (in blocks) of the driver */
	ulong		b;				/* partition block number index */
	Boolean		drvrIs43;		/* false if old, true if new (4pt3) */
	short		dRefNum;		/* The driver we loaded */
	short		partMapCount;	/* Length of partition map */
	ulong		DDMBlockNum;	/* block number of DDM */
	uchar		osType;			/* OS Type read from PRAM */
	

// Initialize and alloc needed memory 

	dRefNum = KEEP_WAITING;					/* don't have it yet - haven't given up */
	HFSBlock = drvrBlock = curBlock = nil;	/* Nobody home yet - needed for cleanup */
	
	if( (realBlock0 = (Block0 *) NewPtrSysClear(512)) == nil )
		goto Cleanup;	/* Punt */
		
	if( (curBlock = (Partition *) NewPtrSysClear(512)) == nil )
		goto Cleanup;	/* Punt */

// Read block 0 and see if it is a DDM or an IPLRecord or neither

	if( ScRead( devInfoPtr, 0, 1, 512, (Ptr) realBlock0) )	/* Get block 0 (DDM/IPLRecord?) */
		goto Cleanup;	
	
	if( realBlock0->sbSig == sbSIGWord ) {	// udoublet at 0
		DDMBlockNum = 0;
	}
	else if( ( (ipl_rec_area *)realBlock0 )->IPL_record_id == IPLRECID) { // uquadlet at 0
		DDMBlockNum = ( (ipl_rec_area *)realBlock0 )->boot_prg_start;
		if( ScRead( devInfoPtr, DDMBlockNum, 1, 512, (Ptr) realBlock0) )	
			goto Cleanup;	
	}
	else {
		SetLoadFlag(BInfo,devInfoPtr->DevIdent);	/* Don't try me again! */
		goto Cleanup;
	}

// Scan through drivers in DDM to find one that matches our OSType

	ReadXPRam( 1, 0x77, &osType);
	for( drvrBlockStart = 0, bootDrvr = (ddMap *)&realBlock0->ddBlock, d = 0 ; d < realBlock0->sbDrvrCount ; d+=1 ) {
		if( bootDrvr[d].ddType == osType) {
			drvrBlockStart = bootDrvr[d].ddBlock + DDMBlockNum;
			drvrSize = bootDrvr[d].ddSize;
			break;
		}
	}
	if( drvrBlockStart == 0 ) {	/* No Drivers in ddm */
		SetLoadFlag(BInfo,devInfoPtr->DevIdent);	/* Don't try me again! */
		dRefNum = DONT_WAIT;
		goto Cleanup;
	}

// Read first block of part map to determine if it's valid and to find part map length

	if( ScRead( devInfoPtr, DDMBlockNum+1,1,512,(Ptr)curBlock) ) {	
		SetLoadFlag(BInfo,devInfoPtr->DevIdent);	/* Don't try me again! */
		goto Cleanup;
	}
	
	if( curBlock->pmSig != newPMSigWord ) {	/* Old Style PMap or one we don't recognize */
		/* Be friendly and try to boot it anyway */
		if( TestLoadFlag(BInfo,devInfoPtr->DevIdent) == 0 )
			dRefNum = LoadDriver(devInfoPtr,drvrBlockStart,drvrSize,false, (Ptr)realBlock0,(Ptr)curBlock, 0);	// <SM12> 
		SetLoadFlag(BInfo,devInfoPtr->DevIdent);
		goto Cleanup;	
	}

// Scan through part map to find HFS and driver partitions

	for( b=1, drvrIs43 = 0, partMapCount = curBlock->pmMapBlkCnt ; b <= partMapCount ; b+=1 ) {
		
		if( ScRead( devInfoPtr, DDMBlockNum+b, 1, 512, (Ptr)curBlock) ) {
			SetLoadFlag( BInfo, devInfoPtr->DevIdent);	/* Don't try me again! */
			goto Cleanup;
		}
		if(	drvrBlock == 0 &&
				*(long *) &curBlock->pmParType[0] == 'Appl' &&
				*(long *) &curBlock->pmParType[4] == 'e_Dr' &&
				*(long *) &curBlock->pmParType[8] == 'iver' ) {
			
			if( curBlock->pmPyPartStart != drvrBlockStart - DDMBlockNum)								//	<SM5>
				continue;	/* Whoops, not the driver from the DDM! */			//  <SM5>
			
			drvrIs43 = (*(short *)&(curBlock->pmParType[12]) == '43') ? true : false;	//	<SM7>
			*forceBootablePtr = (*(long *)&(curBlock->pmParType[28]) == 'pdm!') ? true : false;

			drvrBlock = curBlock;
			
			if( (curBlock = (Partition *) NewPtrSysClear(512)) == nil )
				goto Cleanup;	/* Punt */
				
		}
		else if( HFSBlock == 0 &&
				*(long *) &curBlock->pmParType[0] == 'Appl' &&
				*(long *) &curBlock->pmParType[4] == 'e_HF' &&
						   curBlock->pmParType[8] == 'S' ) {
			HFSBlock = curBlock;
			if( (curBlock = (Partition *) NewPtrSysClear(512)) == nil )
				goto Cleanup;	/* Punt */
		}
		
		if( drvrBlock && HFSBlock )
			break;																// <SM5>
	}

// Load the driver whether we found an HFS partition or not		 <SM5>

	if( HFSBlock) {
		if( TestLoadFlag( BInfo, devInfoPtr->DevIdent) == 0 ) {
			dRefNum = LoadDriver( devInfoPtr, drvrBlockStart, drvrSize, drvrIs43, (Ptr)realBlock0, (Ptr)HFSBlock, drvrBlock );	// <SM12> 
			SetLoadFlag( BInfo, devInfoPtr->DevIdent);
		}
	}
	
	if (*forceBootablePtr)
		*forceBootablePtr = Ck4EjectableVolume( dRefNum);
		
Cleanup:
	if( realBlock0 )
		DisposPtr((Ptr) realBlock0);
	if( curBlock )
		DisposPtr((Ptr) curBlock);
	if( HFSBlock )
		DisposPtr((Ptr) HFSBlock);
	if( drvrBlock )
		DisposPtr((Ptr) drvrBlock);
	
	return (dRefNum);
}


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
	LoadDriver 	-	
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

short
LoadDriver(
	DevInfo 	* devInfoPtr,
	ulong 		DrvrStart,
	ulong 		DrvrLength,
	Boolean 	NewDrvr,
	Ptr 		BZero,	// <SM12> 
	Ptr 		HFSBlock,
	Partition 	* drvrBlock )
{
#pragma unused (drvrBlock)
	Ptr				theDrvr;
	short			dRefNum;
	SCSI_Driver_PB	myPB;
	SCSIGetVirtualIDInfoPB	myVIDpb;

//--- Check to see if it's OK to load and install the driver

	Clear((char *)&myPB, sizeof(myPB));
	Clear((char *)&myVIDpb, sizeof(myVIDpb));

	if( NewDrvr) {  	//--- Driver43 ---
	
		myPB.scsiDevice = devInfoPtr->DevIdent;
		myPB.scsiCompletion = nil;
		myPB.scsiPBLength = sizeof(SCSI_Driver_PB);
		myPB.scsiFunctionCode = SCSILookupRefNumXref;
		SCSIAction((SCSI_PB *) &myPB);
		
		dRefNum = myPB.scsiDriver;
		
		if( dRefNum != 0 )
			return (dRefNum);		/* Already installed */
	}
	else {				//--- Old style driver --- 	<SM10>

		//--- Don't load old driver if SCSI ID is 7 or higher
		if( devInfoPtr->DevIdent.targetID >= 7)
			return (DONT_WAIT);
			
		//--- Don't load old driver if device doesn't match VirtualIDInfo
		myVIDpb.scsiOldCallID = devInfoPtr->DevIdent.targetID;
		myVIDpb.scsiFunctionCode = SCSIGetVirtualIDInfo;
		SCSIAction((SCSI_PB *) &myVIDpb);		// get the info about this ID
		
		if (myVIDpb.scsiExists && myVIDpb.scsiDevice.bus != devInfoPtr->DevIdent.bus)	//<SM11> pdw
			return (DONT_WAIT);
		
		//--- Don't load it if a driver is already installed at the static drvr slot for this ID
		dRefNum = ~(devInfoPtr->DevIdent.targetID + 32);	/* Convert SCSI ID to DRefNum */
		if( GetDCtlEntry(dRefNum) != nil )
			return (DONT_WAIT);	
	}

//--- Now try to load the driver and do a checksum on it

	if( (theDrvr = NewPtrSys(DrvrLength * ((Block0 *)BZero)->sbBlkSize)) == nil )	// <SM12>
		return (DONT_WAIT);	/* No memory - give up */
		
	if( ScRead( devInfoPtr, DrvrStart, DrvrLength, ((Block0 *)BZero)->sbBlkSize, theDrvr) ) {
		DisposPtr(theDrvr);
		return (KEEP_WAITING);
	}

	FlushInstructionCache();
	FlushDataCache();

	if( drvrBlock && *(long *)drvrBlock->pmPartName == 'Maci' ) {
		/* !!! Why do a long comparison when the checksum routine returns a short ?
		   I don't have any idea - but this is the way the original SCSIBoot.a file
		   did it so I will continue to do it the same way until further notice. -DCB
		*/
		if( (ulong) drvrBlock->pmBootCksum != CheckSumDrvr( theDrvr,drvrBlock->pmBootSize ) ) {
			DisposPtr(theDrvr);
			return (DONT_WAIT);
		}
	}

//--- Jump to driver

	if( NewDrvr ) {  //--- Driver43 (NOTE! Driver43s start at Driver + 8 bytes!!!
		JmpToDrvr( *(ulong *)&devInfoPtr->DevIdent, theDrvr + 8, BZero, HFSBlock);		// <SM8>
		
		/* Find out where the driver installed itself */	
		myPB.scsiDevice = devInfoPtr->DevIdent;
		myPB.scsiCompletion = nil;
		myPB.scsiPBLength = sizeof(SCSI_Driver_PB);
		myPB.scsiFunctionCode = SCSILookupRefNumXref;
		SCSIAction((SCSI_PB *) &myPB);
		
		return (myPB.scsiDriver);
	}
	else {			//--- Old style driver
		JmpToDrvr( devInfoPtr->DevIdent.targetID, theDrvr, (Ptr) BZero, HFSBlock);	//!!! Add At_App_Time
		dRefNum = ~(devInfoPtr->DevIdent.targetID + 32);	/* Convert SCSI ID to DRefNum */
		if( GetDCtlEntry(dRefNum) == nil )
			return (DONT_WAIT);		/* Something went wrong - didn't install */
		
		/* Ok, it installed - register it with the SCSI Manager */
		myPB.scsiDevice = devInfoPtr->DevIdent;
		myPB.scsiPBLength = sizeof(SCSI_Driver_PB);
		myPB.scsiDriver = dRefNum;
		myPB.scsiFunctionCode = SCSICreateRefNumXref;
		SCSIAction((SCSI_PB *) &myPB);
		return (dRefNum);
	}
}


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
	SetLoadFlag 	-	
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

void
SetLoadFlag( BootInfo * BInfo, DeviceIdent devIdent)
{
	SCSIGetVirtualIDInfoPB	getVIDPB;
	
	Clear((char *)&getVIDPB, sizeof(getVIDPB));
	
	BInfo->IDmasks[ devIdent.bus] |= (1 << devIdent.targetID);
	
	getVIDPB.scsiOldCallID = devIdent.targetID;
	getVIDPB.scsiFunctionCode = SCSIGetVirtualIDInfo;
	SCSIAction((SCSI_PB *) &getVIDPB);		// get the info about this ID
		
	if ( getVIDPB.scsiExists && (getVIDPB.scsiDevice.bus == devIdent.bus))
		SCSIDrvrs |= 1<<devIdent.targetID;
}


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
	ScRead 	-	
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

short	/* !!! OSErr? */
ScRead( 
	DevInfo *devInfoPtr,
	ulong	block,
	ulong	length,
	ushort	blocklen,	// <SM12> 
	uchar 	*buffer )
{
	uchar 		*cmd;

	cmd = (uchar *)&(devInfoPtr->ioPB->scsiCDB);
	
	/* 10 byte commands are easier but the @#$%^&*! Connor 40s don't return real data from
       the FIRST 10 byte command after a reset or power on.  Therefore we issue 6 byte commands
	   unless the data requested exceeds the addressing capacity of a 6 byte command.
	   
	   <SM9>
	*/
	
	if( (block & 0xFFE00000) || (length & 0xFFFFFF00) ) {						// <SM9>
	
		cmd[0] = 0x28;				/* Properly pumped up 10 byte scsi command */
		cmd[1] = 0;					/* !!! Add support for embedded luns? */
		
		cmd[2] = block>>24;	
		cmd[3] = block>>16;
		cmd[4] = block>>8;
		cmd[5] = block;
	
		cmd[6] = 0;					/* reserved */
		
		cmd[7] = length>>8;
		cmd[8] = length;
		cmd[9] = 0;					/* reserved */
		devInfoPtr->ioPB->scsiCDBLength = 10;
	}
	else {
		cmd[0] = 0x8;				/* Wimpy 6 byte command */
		
		cmd[1] = block>>16 & 0x1f;	/* !!! Add support for embedded luns? */
		cmd[2] = block>>8;
		cmd[3] = block;
		
		cmd[4] = length;
		cmd[5] = 0;					/* reserved */
		devInfoPtr->ioPB->scsiCDBLength = 6;
	}

	devInfoPtr->ioPB->scsiDataPtr = buffer;
	devInfoPtr->ioPB->scsiDataLength = length * blocklen;			/* <SM12> */

	devInfoPtr->ioPB->scsiFlags = scsiDirectionIn | scsiSIMQNoFreeze | scsiDisableAutosense;
	devInfoPtr->ioPB->scsiIOFlags = scsiNoParityCheck;	

	if( devInfoPtr->IdentMsg == 0 )
		devInfoPtr->ioPB->scsiIOFlags |= scsiDisableSelectWAtn;

	devInfoPtr->ioPB->scsiDevice = devInfoPtr->DevIdent;
	devInfoPtr->ioPB->scsiFunctionCode = SCSIExecIO;
	devInfoPtr->ioPB->scsiCompletion = nil;
		
	devInfoPtr->ioPB->scsiTransferType = scsiTransferPolled;

	SCSIAction( (SCSI_PB *) devInfoPtr->ioPB);
	
	if( devInfoPtr->ioPB->scsiSCSIstatus )	// status will be cleared upon entry to SIMAction
		SCSIAction( (SCSI_PB *) devInfoPtr->ioPB);	/* Retry, to clear out unit attention */
	
	if( devInfoPtr->ioPB->scsiResult == scsiDataRunError )	// Not all drives are 512/block <LW10>
		devInfoPtr->ioPB->scsiResult = noErr;				// We don't discover this until after we load block zero

	return( !(devInfoPtr->ioPB->scsiResult == noErr && devInfoPtr->ioPB->scsiSCSIstatus == 0) );
}


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
	SOpenDriver 	-	
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

OSErr SOpenDriver(SpBlockPtr sp)
{
	OSErr				err;
	short 				refnum;
	unsigned int		count;
	AuxDCEHandle		myDCE;
	DriverHeaderHandle	driver;
	unsigned char		name [32];
	ParamBlockRec		ioPB;
	
	driver = (DriverHeaderHandle) sp->spResult;
	HLock((Handle) driver);

	/* copy the driver name out of the driver header */
	BlockMove((**driver).drvrName, name, 1 + (**driver).drvrName[0]);
	
	for( count = 48; count < *(ulong *)UnitNtryCnt ; count+=1 ) {
		refnum = ~count;
		if( GetDCtlEntry(refnum) == 0 )
			break;	/* Use the first empty spot we find */
	}

	if( (err = DrvrInstallResrvMem(*driver, refnum)) != noErr )
		return(err);
	
	myDCE = (AuxDCE**)GetDCtlEntry(refnum);
	
	(**myDCE).dCtlDriver = (Ptr)driver;
	(**driver).drvrFlags |= 1 << dNeedLock << 8 | 1 << dRAMBased;
	(**myDCE).dCtlFlags = (**driver).drvrFlags;
	(**myDCE).dCtlDelay = (**driver).drvrDelay;
	(**myDCE).dCtlEMask = (**driver).drvrEMask;
	(**myDCE).dCtlMenu = (**driver).drvrMenu;
	(**myDCE).dCtlSlot = sp->spSlot;
	(**myDCE).dCtlSlotId = sp->spID;
	(**myDCE).dCtlExtDev = sp->spExtDev;
	
	ioPB.slotDevParam.ioVRefNum = 0;		
	ioPB.slotDevParam.ioFlags = 0;
	ioPB.slotDevParam.ioPermssn = 0;		
	ioPB.slotDevParam.ioCompletion = 0;
	ioPB.slotDevParam.ioMix = (Ptr)0;
	ioPB.slotDevParam.ioNamePtr = name;
	ioPB.slotDevParam.ioSlot = sp->spSlot;
	ioPB.slotDevParam.ioID = sp->spID;
	PBOpenSync(&ioPB);
	if( ioPB.slotDevParam.ioResult < 0 ) {
	
	   DisposeHandle((Handle) driver);		/* dispose the driver */
	   DisposeHandle((Handle) myDCE); 		/* dispose the DCE */
	   ((long *)(*(long *)UTableBase))[count] = nil;	/* clear the unit table entry */
	}
	return(ioPB.slotDevParam.ioResult);

}


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
	Ck4EjectableVolume 	-	
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

Boolean
Ck4EjectableVolume( short drvrRefNum)
{
	DrvQEl	*	qElPtr;
	char		diskType;
	
	qElPtr = (DrvQEl *)(GetDrvQHdr()->qHead);
	
	while (qElPtr)
	{
		if (qElPtr->dQRefNum == drvrRefNum) {
			diskType = *(( (char *)qElPtr )-3);
			if ( diskType ==1 || diskType ==2)
				return (true);
		}
		qElPtr = (DrvQEl *)(qElPtr->qLink);
	}
	return (false);
}


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
	DummyOldCallRead 	-	
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

void
DummyOldCallRead( short scsiID)
{
	char		cdb[6];
	SCSIInstr	tib[2];
	char		data[0x200];
	short		stat, msg;
	
	tib[0].scOpcode = scInc;
	tib[0].scParam1 = &data;
	tib[0].scParam2 = 0x200;
	
	tib[1].scOpcode = scStop;
	tib[1].scParam1 = 0;
	tib[1].scParam2 = 0;
	
	cdb[0] = 0x08;
	cdb[1] = 0x00;
	cdb[2] = 0x00;
	cdb[3] = 0x00;
	cdb[4] = 0x01;
	cdb[5] = 0x00;

	
	SCSIGet();
	
	if (SCSISelect( scsiID))
		return;
		
	if (!SCSICmd( cdb, 6))
		SCSIRead( (Ptr)tib);
	
	SCSIComplete( &stat, &msg, 60*60);
}

