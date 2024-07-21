/************************************************************

	Devices.h
	C Interface to the Macintosh Libraries

	Created: Saturday, July 27, 1991 at 2:55 PM

	Copyright Apple Computer, Inc.  1985-1991
	All rights reserved

	Change History (most recent first):

	   <SM4>	 1/16/94	pdw		Fixed PBControlSync in-line.
	   <SM3>	 1/13/94	chp		Added lots of types and constants defined in Inside Mac but
									always missing from the C headers. Fixed DrvrInstall prototypes.
	   <SM2>	10/14/93	pdw		<MC2>
	   <MC2>	 9/26/93	pdw		Rolled in a lot of Reality changes.  Made it bearable in spots
									and added DrvrGestalt stuff.
		<14>	 7/30/93	DTY		Sync up with NuReality again.
		<13>	  6/3/93	DTY		Sync up with NuReality version of this header.
		<12>	 7/30/91	JL		Updated Copyright.
		<11>	 1/30/91	JL		group enums into groups of 20.
		<10>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <9>	  1/7/91	JDR		(dba) Adding messages sent to the monitor function in the
									Control Panel.
		 <7>	12/12/90	JL		Put formal parameter names back.
		 <6>	 11/8/90	JL		Changed all #defines to anonymous enums
		 <5>	 11/4/90	dba		used constStr255Parameter; got rid of some extraneous parameter
									names; made some parameters void* instead of Ptr; added more use
									of const in parameters
		 <4>	10/21/90	gbm		(with dba) Made compatible with 3.2 C compiler (and incompatible
									with previous compilers).
				10/10/90	JAL		New style #Pragma Parameters for MPW 3.2 C
		1.1		11/9/88		CCH		Fixed headers and removed projector resource.
		1.0		11/9/88		CCH		Adding to EASE.

************************************************************/


#ifndef __DEVICES__
#define __DEVICES__

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif

#ifndef __FILES__
#include <Files.h>
#endif

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif



/* control panel message constants (Why are these in Devices.h?) */

enum {
	chooserID		= 1,
	initDev			= 0,		// Time for cdev to initialize itself
	hitDev			= 1,		// Hit on one of my items
	closeDev		= 2,		// Close yourself
	nulDev			= 3,		// Null event
	updateDev		= 4,		// Update event
	activDev		= 5,		// Activate event
	deactivDev		= 6,		// Deactivate event
	keyEvtDev		= 7,		// Key down/auto key
	macDev			= 8,		// Decide whether or not to show up
	undoDev			= 9,
	cutDev			= 10,
	copyDev			= 11,
	newSelMsg		= 12,
	fillListMsg		= 13,
	getSelMsg		= 14,
	selectMsg		= 15,
	deselectMsg		= 16,
	terminateMsg	= 17,
	buttonMsg		= 19,
	pasteDev		= 12,
	clearDev		= 13,
	cursorDev		= 14,
	cdevGenErr		= -1,		// General error; gray cdev w/o alert
	cdevMemErr		= 0,		// Memory shortfall; alert user please
	cdevResErr		= 1,		// Couldn't get a needed resource; alert
	cdevUnset		= 3			// cdevValue is initialized to this
};

/* Monitors control panel messages */

enum {
	initMsg			= 1,		// initialization
	okMsg			= 2,		// user clicked OK button
	cancelMsg		= 3,		// user clicked Cancel button
	hitMsg			= 4,		// user clicked control in Options dialog
	nulMsg			= 5,		// periodic event
	updateMsg		= 6,		// update event
	activateMsg		= 7,		// not used
	deactivateMsg	= 8,		// not used
	keyEvtMsg		= 9,		// keyboard event
	superMsg		= 10,		// show superuser controls
	normalMsg		= 11,		// show only normal controls
	startupMsg		= 12		// code has been loaded
};



/* Device Manager structures and constants */

struct DCtlEntry {
	Ptr			dCtlDriver;
	short		dCtlFlags;
	QHdr		dCtlQHdr;
	long		dCtlPosition;
	Handle		dCtlStorage;
	short		dCtlRefNum;
	long		dCtlCurTicks;
	WindowPtr	dCtlWindow;
	short		dCtlDelay;
	short		dCtlEMask;
	short		dCtlMenu;
};
typedef struct DCtlEntry DCtlEntry, *DCtlPtr, **DCtlHandle;

struct AuxDCE {
	Ptr			dCtlDriver;
	short		dCtlFlags;
	QHdr		dCtlQHdr;
	long		dCtlPosition;
	Handle		dCtlStorage;
	short		dCtlRefNum;
	long		dCtlCurTicks;
	GrafPtr		dCtlWindow;
	short		dCtlDelay;
	short		dCtlEMask;
	short		dCtlMenu;
	char		dCtlSlot;
	char		dCtlSlotId;
	long		dCtlDevBase;
	Ptr			dCtlOwner;
	char		dCtlExtDev;
	char		fillByte;
};
typedef struct AuxDCE AuxDCE, *AuxDCEPtr, **AuxDCEHandle;

struct DriverHeader {
	short			drvrFlags;
	short			drvrDelay;
	short			drvrEMask;
	short			drvrMenu;
	short			drvrOpen;
	short			drvrPrime;
	short			drvrCtl;
	short			drvrStatus;
	short			drvrClose;
	unsigned char	drvrName [1];
};
typedef struct DriverHeader DriverHeader, *DriverHeaderPtr, **DriverHeaderHandle;


// miscellaneous Device Manager constants

enum {
	ioInProgress	= 1,	// predefined value of ioResult while I/O is pending

	aRdCmd			= 2,	// low byte of ioTrap for Read calls
	aWrCmd			= 3,	// low byte of ioTrap for Write calls

	/* trap word modifiers */
	asyncTrpBit		= 10,
	noQueueBit		= 9,

	/* special csCodes */
	goodBye			= -1,
	killCode		= 1,
	accRun			= 65
};


// old dCtlFlags bit definitions (treated as bytes)

enum {
							// Set if driver...

	/* driver flags in high byte [IM II-188] */
	dReadEnable		= 0,	// can respond to Read calls
	dWritEnable		= 1,	// can respond to Write calls
	dCtlEnable		= 2,	// can respond to Control calls
	dStatEnable		= 3,	// can respond to Status calls
	dNeedGoodBye	= 4,	// needs to be called before the application heap is reinitialized
	dNeedTime		= 5,	// needs time for performing a periodic action
	dNeedLock		= 6,	// will be locked in memory as soon as it’s opened
							//	(always set for ROM drivers)

	/* DCE flags in low byte [IM II-190] */
	dOpened			= 5,	// is open
	dRAMBased		= 6,	// dCtlDriver is a resource handle
	drvrActive		= 7		// has pending I/O
};

// new dCtlFlags bit definitions (treated as word)

enum {
	Is_AppleTalk			= 0,
	Is_Agent				= 1,
	FollowsNewRules			= 2,		// New DRVR Rules Bit
	unused3					= 3,

	unused4					= 4,
	Is_Open					= 5,
	Is_Ram_Based			= 6,
	Is_Active				= 7,

	Read_Enable				= 8,
	Write_Enable			= 9,
	Control_Enable			= 10,
	Status_Enable			= 11,

	Needs_Goodbye			= 12,
	Needs_Time				= 13,
	Needs_Lock				= 14,
	unused15				= 15
};

#define Is_AppleTalk_Mask		(1 << Is_AppleTalk)
#define Is_Agent_Mask			(1 << Is_Agent)
#define FollowsNewRules_Mask	(1 << FollowsNewRules)
#define Is_Open_Mask			(1 << Is_Open)
#define Is_Ram_Based_Mask		(1 << Is_Ram_Based)
#define Is_Active_Mask			(1 << Is_Active)
#define Read_Enable_Mask		(1 << Read_Enable)
#define Write_Enable_Mask		(1 << Write_Enable)
#define Control_Enable_Mask		(1 << Control_Enable)
#define Status_Enable_Mask		(1 << Status_Enable)
#define Needs_Goodbye_Mask		(1 << Needs_Goodbye)
#define Needs_Time_Mask			(1 << Needs_Time)
#define Needs_Lock_Mask			(1 << Needs_Lock)



/*** Driver Gestalt Structures ***/

#define	driverGestaltCode	43

// Currently defined drvrGestalt selectors

#define	driverGestaltSync			'sync' 	// True if driver only behaves synchronously.
#define	driverGestaltPrefetch		'prft'	// The prefetch buffer characteristics (size and time to prefetch)
#define	driverGestaltBoot			'boot'	// value to place in PRAM for this drive (long)


// Structures for currently defined drvrGestalt selectors

typedef struct
{
	Boolean		behavesSynchronously;
} driverGestaltSyncResponse;


typedef struct
{
	unsigned char	extDev;			//  Packed target (upper 5 bits) LUN (lower 3 bits)
	unsigned char	partition;		//  Unused
	unsigned char	SIMSlot;		//  Slot
	unsigned char	SIMsRSRC		//  sRsrcID
} driverGestaltBootResponse;


typedef union
{
	driverGestaltSyncResponse		sync;
	driverGestaltBootResponse		boot;
} driverGestaltInfo;


// status parameter block for drvrGestalt calls

typedef struct DriverGestaltParam {
	ParamBlockHeader
	short			ioCRefNum;				// refNum for I/O operation
	short			csCode;					//	== driverGestaltCode
	OSType			driverGestaltSelector;
	driverGestaltInfo *	driverGestaltResponse;
} DriverGestaltParam;



#ifdef __cplusplus
extern "C" {
#endif

pascal DCtlHandle GetDCtlEntry(short refNum);

pascal Boolean SetChooserAlert(Boolean f);

pascal OSErr OpenDriver(ConstStr255Param name,short *drvrRefNum);

OSErr opendriver(char *driverName,short *refNum);

pascal OSErr CloseDriver(short refNum);

pascal OSErr Control(short refNum,short csCode,const void *csParamPtr);

pascal OSErr Status(short refNum,short csCode,void *csParamPtr);

pascal OSErr KillIO(short refNum);

pascal OSErr PBControl(ParmBlkPtr paramBlock,Boolean async);

pascal OSErr PBStatus(ParmBlkPtr paramBlock,Boolean async);

pascal OSErr PBKillIO(ParmBlkPtr paramBlock,Boolean async);

#pragma parameter __D0	DrvrInstall(__A0,__D0)
pascal OSErr			DrvrInstall(DriverHeaderPtr drvrPtr, short refNum) = 0xA03D;

#pragma parameter __D0	DrvrInstallResrvMem(__A0, __D0)
pascal OSErr			DrvrInstallResrvMem(DriverHeaderPtr drvrPtr, short refNum) = 0xA43D;

#pragma parameter __D0	DrvrRemove(__D0)
pascal OSErr			DrvrRemove(short refNum)				= 0xA03E;

#pragma parameter __D0	PBControlSync(__A0)
pascal OSErr			PBControlSync(ParmBlkPtr paramBlock)	= 0xA004;

#pragma parameter __D0	PBControlAsync(__A0)
pascal OSErr			PBControlAsync(ParmBlkPtr paramBlock)	= 0xA404;

#pragma parameter __D0	PBStatusSync(__A0)
pascal OSErr			PBStatusSync(ParmBlkPtr paramBlock)		= 0xA005;

#pragma parameter __D0	PBStatusAsync(__A0)
pascal OSErr			PBStatusAsync(ParmBlkPtr paramBlock)	= 0xA405;

#pragma parameter __D0	PBKillIOSync(__A0)
pascal OSErr			PBKillIOSync(ParmBlkPtr paramBlock)		= 0xA006;

#pragma parameter __D0	PBKillIOAsync(__A0)
pascal OSErr			PBKillIOAsync(ParmBlkPtr paramBlock)	= 0xA406;

#ifdef __cplusplus
}
#endif

#endif
