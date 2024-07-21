/*******************************************************************************

	File:		ACAM.h

	Contains:	
		This file contains constants and data structures that will be used by
		drivers to interface with the SCSI Manager 4.3.
						
	Written by:	
		Jonathan Abilay		Blue I/O
		Paul Wolf			MHD/Drivers NT
		Henry Kannapell		ARIOSO Dude
		Clinton Bauder		MHD/Drivers NT
		Matthew Nelson		RISC

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	  <SM22>	  2/2/94	DCB		Adding another bit to SCSIWeirdStuff - this time to indicate a
									need for scsiHandshaking.
	  <SM21>	  2/1/94	DCB		Added scsiBusErrorsUnsafe constant for the scsiWeirdStuff field.
	  <SM20>	11/22/93	pdw		Rolling in from <MCxx>.
	   <MC4>	11/11/93	pdw		Added scsiWeirdStuff field to BusInquiry along with its bits.
	   <MC3>	 11/9/93	pdw		Added scsiIdentifyMessageRejected error code.
	  <SMG2>	 9/29/93	chp		Standardized conditional inclusion and removed redundancies with
									Types.h, which is included.
	  <SM18>	10/14/93	pdw		Added scsiWrongDirection and scsibXXX flag enums.
	  <SM17>	 7/17/93	pdw		IMPORTANT!!! Changed the SCM to SIM in the comment about
									ReleaseQ (i.e. SIM Q vs. SCM Q).
	  <SM16>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
									stack switching mechanism.  Adding support for Cold Fusion.
									Rearranging HW/SW Init code. Some code optimizations.
	  <SM15>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	  <LW11>	  5/1/93	PW		Realigning tabs that got screwed up during massive name changes
									(on previous checkin).  Changing xxxResidualLength to
									xxxResidual.
	   <LW9>	 4/14/93	DCB		Fixed the glue for register bus and re-register bus.  Also added
									syncRenegotiateSense flags for third party SIMs.
	  <SM14>	 3/23/93	PW		Added scsiInitiateWide bit and reserved some async callback
									flags for 3rd-parties.
	   <LW8>	 3/26/93	PW		Making scsiDriver field a signed short instead of unsigned short.
									Changed busOldAPICapable to scsiBusOldCallCapable.
	  <SM13>	 3/20/93	PW		Rolled in Ludwig changes.
	   <LW7>	  3/1/93	DCB		Changed scsiConnectionTimeout to reserved since it isn't needed anymore.
	   <LW6>	  3/1/93	PW		Added LoadDrivers function code and removed some unnecessary
									flags from scsiScanFlags byte.
	   <LW5>	 2/17/93	PW		Added scsiBusNotFree bit to scsiResultFlags field.
	  <SM12>	  2/1/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <LW4>	 1/27/93	PW		Adding a couple of fields to Bus Inquiry.
	   <LW3>	 1/27/93	PW		Added temporary hack to keep people's A10 drivers working.
	   <LW2>	 1/27/93	PW		Removed enums on flags and added enum to A089 selectors.  Added
									a spare long to header and added scsiDataTypes field.
	  <SM11>	 12/9/92	PW		Rearranged error codes - broke them up into 3 ranges: execution
									failed, could not start and parameter error. Removed
									scsiDoVirtualMap flag.
	  <SM10>	 12/5/92	PW		Changed VUflags to IOflags and changed RefNum function names.
	   <SM9>	11/20/92	DCB		Adding support for interleaving, changed some #defines to enums
									and removed recorder stuff.
	   <SM8>	10/30/92	DCB		Moved completion routine to header
	   <SM7>	10/30/92	DCB		Various changes in to reflect the results of the SCSI Sync
									meeting
	   <SM6>	 10/8/92	PW		Whole loads of name changes (fields, flags and errors).  Some
									realignment and some new fields.
	   <SM5>	 9/17/92	PW		Slight changes to some names.  Removed much unused garbage.
	   <SM4>	 8/31/92	DCB		Added ioQ Field to the SCSI_IO parameter block to simplify Q
									management.
	   <SM3>	 8/30/92	DCB		Added pending IO field to SCSI_IO, also changed the names for
									Terminate, Abort and Reset Device.
	   <SM2>	 8/20/92	DCB		Added Select w/o Atn flag

		---------------------------------		SCSI Manager Header File
		--- S C S I   M A N A G E R   ---		Version 4.3
		---------------------------------		

*******************************************************************************/

#ifndef __ACAM__
#define __ACAM__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __TRAPS__
#include <Traps.h>
#endif


#define scsiVERSION 43

/********************************************************************/
// Defines for the SCSIMgr function codes
/********************************************************************/

enum 										// <SM9> changed to enums as per design review
{
//------------ Common Functions ------------

	SCSINop						= 0x00,  	// Execute nothing
	SCSIExecIO       	   		= 0x01,  	// Execute the specified IO
	SCSIBusInquiry      		= 0x03, 	// Get parameters for entire path of HBAs
	SCSIReleaseQ				= 0x04,		// Release the frozen SIM queue for particular LUN 
	SCSISetAsyncCallback		= 0x05,		// Set async event call back 

//------------ Control Functions 		------------

	SCSIAbortCommand			= 0x10,		// Abort the selected Control Block 
	SCSIResetBus				= 0x11,		// Reset the SCSI bus 
	SCSIResetDevice				= 0x12,		// Reset the SCSI device 
	SCSITerminateIO				= 0x13,		// Terminate any pending IO 

//------------ Target Mode Functions  	------------

	SCSIEnableLUN				= 0x30,		// Enable LUN, Target mode support
	SCSITargetIO				= 0x31,		// Execute the target IO request

//------------ Apple Added 				------------

	SCSIGetVirtualIDInfo		= 0x80,		// Find out which bus old ID is on							
	SCSIGenerateInterleaveID	= 0x81,		// Generate a new interleave factor		<SM9> pdw
	SCSILoadDriver				= 0x82,		// Load a driver for a device ident.	<LW6> DCB
	SCSIOldCall					= 0x84,		// XPT->SIM private call for old-API
	SCSICreateRefNumXref		= 0x85,		// Register a DeviceIdent to drvr RefNum xref
	SCSILookupRefNumXref		= 0x86,		// Get DeviceIdent to drvr RefNum xref
	SCSIRemoveRefNumXref		= 0x87,		// Remove a DeviceIdent to drvr RefNum xref
	SCSIRegisterWithNewXPT		= 0x88		// XPT has changed - SIM needs to re-register itself

//------------ 3rd-party Vendor Unique 	------------							

// 0xC0 thru 0xFF
};


/********************************************************************/
/*	SCSI Parameter Block Elements									*/
/********************************************************************/

typedef pascal void (*CallbackProc) (void * ioPtr);					//			<SM6> pdw


//————— Allocation length defines for some of the fields ————— <SM9>

#define		handshakeDataLength		8		// Handshake data length
#define		maxCDBLength			16     	// Space for the CDB bytes/pointer
#define		vendorIDLength			16      // ASCII string len for Vendor ID 


//————— Define DeviceIdent structure —————

typedef struct DeviceIdent 
{
	uchar		diReserved;			// reserved
	uchar		bus;				// SCSI - Bus #
	uchar		targetID;			// SCSI - Target SCSI ID
	uchar		LUN;				// SCSI - LUN 
} DeviceIdent;


//————— Command Descriptor Block structure —————

typedef union CDB
{
	uchar *		cdbPtr;						// ptr to the CDB bytes to send, or…
	uchar		cdbBytes[ maxCDBLength ];	// actual CDB to send					<SM6> pdw
} CDB, *CDBPtr;


//————— Scatter/gather list element —————

typedef	struct SGRecord 
{
	Ptr		SGAddr;
	ulong	SGCount;
} SGRecord;




/********************************************************************/
/*	SCSI Parameter Block Definitions								*/
/********************************************************************/

//====== Common SCSI PB header fields macro ======

#define SCSIPBHdr \
	struct SCSIHdr * qLink;				/* (internal) Q link to next PB 		*/ \
	short			scsiReserved1;		/* -> 	reserved for input				*/ \
	ushort			scsiPBLength;		/* -> Length of the entire PB			*/ \
	uchar			scsiFunctionCode;	/* -> function selector 				*/ \
	uchar			scsiReserved2;		/* <- 	reserved for output				*/ \
	OSErr			scsiResult;			/* <- Returned result 					*/ \
	DeviceIdent		scsiDevice;			/* -> Device Identifier (bus+target+lun)*/ \
	CallbackProc	scsiCompletion;		/* -> Callback on completion function  	*/ \
	ulong			scsiFlags;			/* -> assorted flags					*/ \
	uchar *			scsiDriverStorage;	/* <> Ptr for driver private use		*/ \
	Ptr				scsiXPTprivate;		/* private field for use in XPT			*/ \
	long			scsiReserved3;		/* reserved								*/
// end of SCSIPBHdr


//——————————————  SCSI PB Header  ——————————————

typedef struct SCSIHdr
{
	SCSIPBHdr
} SCSIHdr;

typedef struct SCSI_PB
{
	SCSIPBHdr
} SCSI_PB;


//——————————————  SCSI I/O Request PB  ——————————————		<SM6> pdw from prev <SM6>
																
#define SCSI_IO_Macro \
	SCSIPBHdr							/* Header information fields						*/ \
	ushort		scsiResultFlags;		/* <- Flags which modify the scsiResult field		*/ \
	ushort		scsiInterleaveID;		/* -> used to designate interleavability of request	*/ \
	uchar *		scsiDataPtr;			/* -> Pointer to the data buffer or the S/G list  	*/ \
	ulong		scsiDataLength;			/* -> Data transfer length							*/ \
	uchar *		scsiSensePtr;			/* -> Ptr to autosense data buffer  				*/ \
	uchar		scsiSenseLength;		/* -> size of the autosense buffer 					*/ \
	uchar		scsiCDBLength;			/* -> Number of bytes for the CDB  					*/ \
	ushort		scsiSGListCount;		/* -> num of scatter gather list entries  			*/ \
	ulong		scsiReserved4;			/* <- 	reserved for output							*/ \
	uchar		scsiSCSIstatus;			/* <- Returned scsi device status  					*/ \
	char		scsiSenseResidual;		/* <- Autosense residual length  					*/ \
	ushort		scsiReserved5;			/* <- 	reserved for output				 			*/ \
	long		scsiDataResidual;		/* <- Returned Transfer residual length  			*/ \
	CDB			scsiCDB;				/* -> Actual CDB or pointer to CDB  				*/ \
	long		scsiTimeout;			/* -> Timeout value (Time Mgr format) (CAM timeout) */ \
	uchar *		scsiMessagePtr;			/* -> Pointer to the message buffer -target md only	*/ \
	ushort		scsiMessageLen;			/* -> Num of bytes in the msg bfr	-target md only	*/ \
	ushort		scsiIOFlags;			/* -> additional I/O flags			   				*/ \
	uchar		scsiTagAction;			/* -> What to do for tag queuing   					*/ \
	uchar		scsiReserved6;			/* -> 	reserved for input			 				*/ \
	ushort		scsiReserved7;			/* -> 	reserved for input			 				*/ \
	ushort		scsiSelectTimeout;		/* -> Select timeout value 							*/ \
	uchar		scsiDataType;			/* -> Data description type (i.e. buffer, TIB, S/G)	*/ \
	uchar		scsiTransferType;		/* -> Transfer type (i.e. Blind vs Polled) 			*/ \
	ulong		scsiReserved8;			/* -> 	reserved for input		 					*/ \
	ulong		scsiReserved9;			/* -> 	reserved for input		 					*/ \
	ushort		scsiHandshake[handshakeDataLength];	/* -> handshaking points (null term'd)	*/ \
	ulong		scsiReserved10;			/* -> 	reserved for input		 					*/ \
	ulong		scsiReserved11;			/* ->   reserved for input							*/ \
	struct SCSI_IO *scsiCommandLink;	/* -> Ptr to the next PB in linked cmd chain 		*/ \
										\
	uchar		scsiSIMpublics[8];		/* -> 	reserved for input to 3rd-party SIMs		*/ \
	uchar		scsiAppleReserved6[8];	/* ->	reserved for input				  			*/ \
										\
/* XPT layer privates (for old-API emulation) */ \
										\
	ushort		scsiCurrentPhase;		/* <- phase upon completing old call  				*/ \
	short		scsiSelector;			/* -> selector specified in old calls  				*/ \
	OSErr		scsiOldCallResult;		/* <- result of old call  							*/ \
	uchar		scsiSCSImessage;		/* <- Returned scsi device message (for SCSIComplete)*/ \
	uchar		XPTprivateFlags;		/* <> various flags  				 				*/ \
	uchar		XPTextras[12];			/*  						  						*/

// end of SCSI_IO_Macro


typedef struct SCSI_IO
{
	SCSI_IO_Macro
} SCSI_IO;
//																<SM6> pdw from prev <SM6>
#define SCSIExecIOPB	SCSI_IO
	

	

//——————————————  Bus inquiry PB ——————————————
typedef struct SCSIBusInquiryPB
{
	SCSIPBHdr							// Header information fields
	ushort		scsiEngineCount;		// <- Number of engines on HBA
	ushort		scsiMaxTransferType;	// <- Number of transfer types for this HBA

	ulong		scsiDataTypes;			// <- which data types are supported by this SIM

	ushort		scsiIOpbSize;			// <- Size of SCSI_IO PB for this SIM/HBA		<SM6> pdw
	ushort		scsiMaxIOpbSize;		// <- Size of max SCSI_IO PB for all SIM/HBAs	<SM6> pdw
	
	ulong		scsiFeatureFlags;		// <- Supported features flags field

	uchar		scsiVersionNumber;		// <- Version number for the SIM/HBA
	uchar		scsiHBAInquiry;			// <- Mimic of INQ byte 7 for the HBA
	uchar		scsiTargetModeFlags;	// <- Flags for target mode support
	uchar		scsiScanFlags;			// <- Scan related feature flags

	ulong		scsiSIMPrivatesPtr;		// <- Ptr to SIM private data area
	ulong		scsiSIMPrivatesSize;	// <- Size of SIM private data area
	ulong		scsiAsyncFlags;			// <- Event cap. for Async Callback

	uchar		scsiHiBusID;			// <- Highest path ID in the subsystem 
	uchar		scsiInitiatorID;		// <- ID of the HBA on the SCSI bus
	ushort		scsiBIReserved0;

	ulong		scsiBIReserved1;		// <- 
	ulong		scsiFlagsSupported;		// <- which scsiFlags are supported

	ushort		scsiIOFlagsSupported;	// <- which scsiIOFlags are supported
	ushort	 	scsiWeirdStuff;			// <- 
	ushort		scsiMaxTarget;			// <- maximum Target number supported
	ushort		scsiMaxLUN;				// <- maximum Logical Unit number supported

	char		scsiSIMVendor[ vendorIDLength ];		// <- Vendor ID of SIM (or XPT if bus<FF)	<SM6> pdw
	char		scsiHBAVendor[ vendorIDLength ];		// <- Vendor ID of the HBA 				<SM6> pdw
	char		scsiControllerFamily[ vendorIDLength ];	// <- Family of SCSI Controller
	char		scsiControllerType[ vendorIDLength ];	// <- Specific Model of SCSI Controller used

	char		scsiXPTversion[4];		// <- version number of XPT
	char		scsiSIMversion[4];		// <- version number of SIM
	char		scsiHBAversion[4];		// <- version number of HBA
	
	uchar		scsiHBAslotType;		// <- type of "slot" that this HBA is in
	uchar		scsiHBAslotNumber;		// <- slot number of this HBA
	ushort		scsiSIMsRsrcID;			// <- resource ID of this SIM
	
	ushort	 	scsiBIReserved3;		// <- 
	ushort		scsiAdditionalLength;	// <- additional BusInquiry PB len
} SCSIBusInquiryPB;


//——————————————  Abort SIM Request PB  ——————————————
typedef struct SCSIAbortCommandPB
{
	SCSIPBHdr							// Header information fields
	SCSI_IO * 	scsiIOptr;				// Pointer to the PB to abort
} SCSIAbortCommandPB;					// <SM3>


//——————————————  Terminate I/O Process Request PB  ——————————————
typedef struct SCSITerminateIOPB
{
	SCSIPBHdr							// Header information fields
	SCSI_IO * 	scsiIOptr;				// Pointer to the PB to terminate
} SCSITerminateIOPB;					// <SM3>


//——————————————  Reset SCSI Bus PB ——————————————
typedef struct SCSIResetBusPB
{
	SCSIPBHdr							// Header information fields
} SCSIResetBusPB;						// <SM3>


//——————————————  Reset SCSI Device PB  ——————————————
typedef struct SCSIResetDevicePB
{
	SCSIPBHdr							// Header information fields
} SCSIResetDevicePB;					// <SM3>


//——————————————  Release SIM Queue PB  ——————————————
typedef struct SCSIReleaseQPB
{
	SCSIPBHdr							// Header information fields
} SCSIReleaseQPB;


//——————————————  Set Async Event Callback PB  ——————————————
typedef struct SCSISetAsyncCallbackPB
{
	SCSIPBHdr							// Header information fields
	ulong		scsiEventFlags;			// -> events to be notified of
	void		(*scsiEventCallback)();	// -> routine to call when event occurs
	uchar *		scsiEventInfoPtr;		// -> ptr to buffer for additional info
	uchar		scsiEventInfoLen;		// -> length of buffer
	uchar		scsiReserved11;			// 
	ushort		scsiReserved12;			// 
} SCSISetAsyncCallbackPB;


//——————————————  SCSI Get Virtual ID Info PB  ——————————————									<SM6> pdw
typedef struct SCSIGetVirtualIDInfoPB
{
	SCSIPBHdr						// Header information fields 
	ushort		scsiOldCallID;		// -> SCSI ID of device in question
	Boolean		scsiExists;			// <- true if device exists
} SCSIGetVirtualIDInfoPB;


//——————————————  SCSI Generate Interleave ID PB  ——————————————									<SM6> pdw
typedef struct SCSIGenerateInterleaveIDPB
{
	SCSIPBHdr						// Header information fields 
	ushort		scsiInterleaveID;	// <- SCSI ID of device in question
	ushort		scsiReserved13;		// 
} SCSIGenerateInterleaveIDPB;


//——————————————  Create/Lookup/Remove RefNum for Device PB  ——————————————
typedef struct SCSI_Driver_PB
{
	SCSIPBHdr							// Header information fields
	short		scsiDriver;				// -> DriverRefNum, For SetDriver
										// <- For GetNextDriver
	ushort		scsiDriverFlags;		// <> Details of driver/device
	DeviceIdent	scsiNextDevice;			// <- DeviceIdent of the NEXT Item in the list 
} SCSI_Driver_PB;


//——————————————  Load Driver PB ——————————————	<LW6> DCB
typedef struct SCSILoadDriverPB
{
	SCSIPBHdr							// Header information fields
	short		scsiLoadedRefNum;		// <- SIM returns refnum of driver
	Boolean		scsiDiskLoadFailed;		// -> if true, indicates call after failure to load
} SCSILoadDriverPB;						//

//======================================================================

/******************************************************************************/
// Values for the fields in SCSI PBs
/******************************************************************************/

//———————————————————————————————————————————————————————————————————————————————————
// Defines for the scsiTransferType field
//———————————————————————————————————————————————————————————————————————————————————

enum {
		scsiTransferBlind = 0,
		scsiTransferPolled
};	

//———————————————————————————————————————————————————————————————————————————————————
// Defines for the scsiDataType field
//———————————————————————————————————————————————————————————————————————————————————

enum {
		scsiDataBuffer 	= 0,		// single contiguous buffer supplied 
		scsiDataTIB 	= 1,		// TIB supplied (ptr in scsiDataPtr)
		scsiDataSG 		= 2			// scatter/gather list supplied 
};	

//———————————————————————————————————————————————————————————————————————————————————
// Defines for the SCSIMgr scsiResult field in the PB header.
//  $E100 thru  E1FF
// -$1EFF thru -1E00
// -#7935 thru -7681 
//———————————————————————————————————————————————————————————————————————————————————

#define		scsiErrorBase		-7936					// = 0xE100 

enum {												// <SM9> changed to enums
	scsiRequestInProgress		= 1,					// 1	 = PB request is in progress

// Execution failed  00-2F
	scsiRequestAborted			= (scsiErrorBase+0x02),	// -7934 = PB request aborted by the host
	scsiUnableToAbort			= (scsiErrorBase+0x03),	// -7933 = Unable to Abort PB request
	scsiNonZeroStatus			= (scsiErrorBase+0x04),	// -7932 = PB request completed with an err
	scsiUnused05				= (scsiErrorBase+0x05),	// -7931 = 
	scsiUnused06				= (scsiErrorBase+0x06),	// -7930 = 
	scsiUnused07				= (scsiErrorBase+0x07),	// -7929 = 
	scsiUnused08				= (scsiErrorBase+0x08),	// -7928 = 
	scsiUnableToTerminate		= (scsiErrorBase+0x09),	// -7927 = Unable to Terminate I/O PB req
	scsiSelectTimeout			= (scsiErrorBase+0x0A),	// -7926 = Target selection timeout
	scsiCommandTimeout			= (scsiErrorBase+0x0B),	// -7925 = Command timeout 
	scsiIdentifyMessageRejected	= (scsiErrorBase+0x0C),	// -7924 = 
	scsiMessageRejectReceived	= (scsiErrorBase+0x0D),	// -7923 = Message reject received 
	scsiSCSIBusReset			= (scsiErrorBase+0x0E),	// -7922 = SCSI bus reset sent/received
	scsiParityError				= (scsiErrorBase+0x0F),	// -7921 = Uncorrectable parity error occured
	scsiAutosenseFailed			= (scsiErrorBase+0x10),	// -7920 = Autosense: Request sense cmd fail
	scsiUnused11				= (scsiErrorBase+0x11),	// -7919 = 
	scsiDataRunError			= (scsiErrorBase+0x12),	// -7918 = Data overrun/underrun error 
	scsiUnexpectedBusFree		= (scsiErrorBase+0x13),	// -7917 = Unexpected BUS free 
	scsiSequenceFailed			= (scsiErrorBase+0x14),	// -7916 = Target bus phase sequence failure
	scsiWrongDirection			= (scsiErrorBase+0x15),	// -7915 = Data phase was in unexpected direction
	scsiUnused16				= (scsiErrorBase+0x16),	// -7914 = 
	scsiBDRsent					= (scsiErrorBase+0x17),	// -7913 = A SCSI BDR msg was sent to target
	scsiTerminated				= (scsiErrorBase+0x18),	// -7912 = PB request terminated by the host
	scsiNoNexus					= (scsiErrorBase+0x19),	// -7911 = Nexus is not established
	scsiCDBReceived				= (scsiErrorBase+0x1A),	// -7910 = The SCSI CDB has been received

// Couldn't begin execution  30-3F
	scsiTooManyBuses			= (scsiErrorBase+0x30),	// -7888 = Register failed because we're full
	scsiBusy					= (scsiErrorBase+0x31),	// -7887 = SCSI subsystem is busy
	scsiProvideFail				= (scsiErrorBase+0x32),	// -7886 = Unable to provide requ. capability
	scsiDeviceNotThere			= (scsiErrorBase+0x33),	// -7885 = SCSI device not installed/there 
	scsiNoHBA					= (scsiErrorBase+0x34),	// -7884 = No HBA detected Error
	scsiDeviceConflict			= (scsiErrorBase+0x35),	// -7883 = sorry, max 1 refNum per DeviceIdent
	scsiNoSuchXref				= (scsiErrorBase+0x36),	// -7882 = no such RefNum xref
	scsiQLinkInvalid			= (scsiErrorBase+0x37),	// -7881 = pre-linked PBs not supported	// <LW14> pdw Fß

// Parameter errors  40-7F
	scsiPBLengthError			= (scsiErrorBase+0x40),	// -7872 = length (scsiPBLength) is insuf'ct/invalid
	scsiFunctionNotAvailable	= (scsiErrorBase+0x41),	// -7871 = The requ. func is not available 
	scsiRequestInvalid			= (scsiErrorBase+0x42),	// -7970 = PB request is invalid
	scsiBusInvalid				= (scsiErrorBase+0x43),	// -7969 = Bus ID supplied is invalid 
	scsiTIDInvalid				= (scsiErrorBase+0x44),	// -7868 = Target ID supplied is invalid
	scsiLUNInvalid				= (scsiErrorBase+0x45),	// -7867 = LUN supplied is invalid 
	scsiIIDInvalid				= (scsiErrorBase+0x46),	// -7866 = The initiator ID is invalid 
	scsiDataTypeInvalid			= (scsiErrorBase+0x47),	// -7865 = scsiDataType requested is not supported
	scsiTransferTypeInvalid		= (scsiErrorBase+0x48),	// -7864 = scsiTransferType field is too high
	scsiCDBLengthInvalid		= (scsiErrorBase+0x49)	// -7863 = scsiCDBLength field is too big
};

#define scsiExecutionErrors		scsiErrorBase
#define scsiNotExecutedErrors	scsiTooManyBuses
#define scsiParameterErrors		scsiPBLengthError

//———————————————————————————————————————————————————————————————————————————————————
//  Defines for the scsiResultFlags field
//———————————————————————————————————————————————————————————————————————————————————

#define	scsiSIMQFrozen			0x0001	// The SIM queue is frozen w/this err
#define	scsiAutosenseValid		0x0002	// Autosense data valid for target 
#define	scsiBusNotFree			0x0004	// At time of callback, SCSI bus is not free 


//———————————————————————————————————————————————————————————————————————————————————
// Defines for the scsiFlags field in the PB header for the SCSIExecIO function
//———————————————————————————————————————————————————————————————————————————————————

enum
{
// 1st Byte

	scsibDisableAutosense		= 29,	// Disable auto sense feature
	scsibFlagReservedA			= 28,	// 
	
	scsibFlagReserved0			= 27,	// 
	scsibCDBLinked				= 26,	// The PB contains a linked CDB
	scsibQEnable				= 25,	// Target queue actions are enabled
	scsibCDBIsPointer			= 24,	// The CDB field contains a pointer
	
// 2nd Byte
	
	scsibFlagReserved1			= 23,	// 
	scsibInitiateSyncData		= 22,	// Attempt Sync data xfer and SDTR
	scsibDisableSyncData		= 21,	// Disable sync, go to async
	scsibSIMQHead				= 20,	// Place PB at the head of SIM Q
	
	scsibSIMQFreeze				= 19,	// Return the SIM Q to frozen state
	scsibSIMQNoFreeze			= 18,	// Disallow SIM Q freezing
	scsibDoDisconnect			= 17,	// Definitely do disconnect
	scsibDontDisconnect			= 16,	// Definitely don't disconnect
	
// 3rd Byte
	
	scsibFlagReserved3			= 15,	// 
	scsibDataDMAready			= 14,	// Data buffer(s) are ready for DMA
	scsibDataPhysical			= 13,	// SG/Buffer data ptrs are physical
	scsibSensePhysical			= 12,	// Autosense buffer ptr is physical
	
	scsibFlagReserved5			= 11,	// 
	scsibFlagReserved6			= 10,	// 
	scsibFlagReserved7			= 9,	// 
	scsibFlagReserved8			= 8,	// 
	
// 4th Byte - Target Mode Flags
	
	scsibDataBufferValid		= 7,	// Data buffer valid
	scsibStatusBufferValid		= 6,	// Status buffer valid 
	scsibMessageBufferValid		= 5,	// Message buffer valid
	scsibFlagReserved9			= 4,	// 
	
	scsibTargetPhaseMode		= 3,	// The SIM will run in phase mode
	scsibTargetPBAvail			= 2,	// Target PB available 
	scsibDisableAutoDisconnect	= 1,	// Disable autodisconnect
	scsibDisableAutoSaveRestore	= 0		// Disable autosave/restore ptrs
};


// 1st Byte

#define	scsiDirectionMask		0xC0000000	// Data direction mask

#define scsiDirectionNone		0xC0000000	// Data direction (11: no data)
#define	scsiDirectionReserved	0x00000000	// Data direction (00: reserved)
#define	scsiDirectionOut		0x80000000	// Data direction (10: DATA OUT)
#define	scsiDirectionIn			0x40000000	// Data direction (01: DATA IN)
#define	scsiDisableAutosense	0x20000000	// Disable auto sense feature
#define	scsiFlagReservedA		0x10000000	// 

#define	scsiFlagReserved0		0x08000000	// 
#define	scsiCDBLinked			0x04000000	// The PB contains a linked CDB
#define	scsiQEnable				0x02000000	// Target queue actions are enabled
#define	scsiCDBIsPointer		0x01000000	// The CDB field contains a pointer

// 2nd Byte

#define	scsiFlagReserved1		0x00800000	// 
#define	scsiInitiateSyncData	0x00400000	// Attempt Sync data xfer and SDTR
#define	scsiDisableSyncData		0x00200000	// Disable sync, go to async
#define	scsiSIMQHead			0x00100000	// Place PB at the head of SIM Q

#define	scsiSIMQFreeze			0x00080000	// Return the SIM Q to frozen state
#define	scsiSIMQNoFreeze		0x00040000	// Disallow SIM Q freezing
#define	scsiDoDisconnect		0x00020000	// Definitely do disconnect
#define	scsiDontDisconnect		0x00010000	// Definitely don't disconnect

// 3rd Byte

#define	scsiFlagReserved3		0x00008000	// 
#define	scsiDataDMAready		0x00004000	// Data buffer(s) are ready for DMA
#define	scsiDataPhysical		0x00002000	// SG/Buffer data ptrs are physical
#define	scsiSensePhysical		0x00001000	// Autosense buffer ptr is physical

#define	scsiFlagReserved5		0x00000800	// 
#define	scsiFlagReserved6		0x00000400	// 
#define	scsiFlagReserved7		0x00000200	// 
#define	scsiFlagReserved8		0x00000100	// 

// 4th Byte - Target Mode Flags

#define	scsiDataBufferValid			0x00000080	// Data buffer valid
#define	scsiStatusBufferValid		0x00000040	// Status buffer valid 
#define	scsiMessageBufferValid		0x00000020	// Message buffer valid
#define	scsiFlagReserved9			0x00000010	// 

#define	scsiTargetPhaseMode			0x00000008	// The SIM will run in phase mode
#define	scsiTargetPBAvail			0x00000004	// Target PB available 
#define	scsiDisableAutoDisconnect	0x00000002	// Disable autodisconnect
#define	scsiDisableAutoSaveRestore	0x00000001	// Disable autosave/restore ptrs

#define	scsiTargetModeFlagsMask		0x000000FF	// all of the target mode bits



//————————————————————————————————————————
// scsiIOFlags
//————————————————————————————————————————

#define	scsiNoParityCheck			0x0002	// disable parity checking 
#define	scsiDisableSelectWAtn		0x0004	// disable select w/Atn 
#define	scsiSavePtrOnDisconnect		0x0008	// do SaveDataPointer upon Disconnect msg
#define	scsiNoBucketIn				0x0010	// don’t bit bucket in during this I/O
#define	scsiNoBucketOut				0x0020	// don’t bit bucket out during this I/O
#define	scsiDisableWide				0x0040	// disable wide transfer negotiation
#define	scsiInitiateWide			0x0080	// initiate wide transfer negotiation
#define	scsiRenegotiateSense		0x0100	// renegotiate sync/wide before issuing autosense

#define	scsiIOFlagReserved0080		0x0080	// 
#define	scsiIOFlagReserved8000		0x8000	// 


//——————————————————————————————————————————————————————————————————————
// Defines for the SIM/HBA queue actions.  These values are used in the
// SCSIExecIOPB, for the queue action field. [These values should match the
// defines from some other include file for the SCSI message phases.  We may
// not need these definitions here. ]

enum {
	scsiSimpleQTag			= 0x20,		// Tag for a simple queue
	scsiHeadQTag			= 0x21,		// Tag for head of queue 
	scsiOrderedQTag			= 0x22 		// Tag for ordered queue 
};

//——————————————————————————————————————————————————————————————————————
// Defines for the Bus Inquiry PB fields.
//——————————————————————————————————————————————————————————————————————

// scsiHBAInquiry field bits

#define	scsiBusMDP				0x80	// Supports Modify Data Pointer message
#define	scsiBusWide32			0x40	// Supports 32 bit wide SCSI
#define	scsiBusWide16			0x20	// Supports 16 bit wide SCSI
#define	scsiBusSDTR				0x10	// Supports Sync Data Transfer Req message
#define	scsiBusLinkedCDB		0x08	// Supports linked CDBs
#define	scsiBusTagQ				0x02	// Supports tag queue message 
#define	scsiBusSoftReset		0x01	// Supports soft reset


// scsiDataTypes field bits 
//	bits 0->15 Apple-defined, 16->30 3rd-party unique, 31 = reserved

#define scsiBusDataTIB			(1<<scsiDataTIB)		// TIB supplied (ptr in scsiDataPtr)
#define scsiBusDataBuffer		(1<<scsiDataBuffer)	// single contiguous buffer supplied 
#define scsiBusDataSG			(1<<scsiDataSG)		// scatter/gather list supplied 

#define scsiBusDataReserved		0x80000000	//  


// scsiTargetModeFlags field bits

#define scsiBusTargetMdProcessor	0x80	// Target mode processor mode 
#define scsiBusTargetMdPhase		0x40	// Target mode phase cog. mode


// scsiScanFlags field bits

#define scsiBusScansDevices			0x80	// Bus scans for and maintains device list
#define scsiBusScansOnInit			0x40	// Bus scans performed at power-up/reboot
#define scsiBusLoadsROMDrivers		0x20	// may load ROM drivers to support targets


// scsiFeatureFlags field bits

#define scsiBusInternalExternalMask		0x000000C0	// bus internal/external mask
#define scsiBusInternalExternalUnknown	0x00000000	// not known whether bus is inside or outside
#define scsiBusInternalExternal			0x000000C0	// bus goes inside and outside the box
#define scsiBusInternal					0x00000080	// bus goes inside the box
#define scsiBusExternal					0x00000040	// bus goes outside the box

#define scsiBusCacheCoherentDMA			0x00000020	// DMA is cache coherent
#define scsiBusOldCallCapable			0x00000010	// SIM is old call capable

#define scsiBusDifferential				0x00000004	// Single Ended (0) or Differential (1)
#define scsiBusFastSCSI					0x00000002	// HBA supports fast SCSI
#define scsiBusDMAavailable				0x00000001	// DMA is available


// scsiWeirdStuff field bits

#define scsiOddDisconnectUnsafeRead1	0x0001	// 
#define scsiOddDisconnectUnsafeWrite1	0x0002	// 
#define	scsiBusErrorsUnsafe				0x0004	//
#define	scsiRequiresHandshake			0x0008	//
#define scsiTargetDrivenSDTRSafe		0x0010	// 



//———————————————————————————————————————————————————————————————————————————————————
//  Defines for the scsiDriverFlags field (in SCSI_Driver_PB)
//———————————————————————————————————————————————————————————————————————————————————

#define	scsiDeviceSensitive			0x0001	// Only driver should access this device
#define	scsiDeviceNoOldCallAccess	0x0002	// no old call access to this device



//——————————————————————————————————————————————————————————————————————
//  SIMinitInfo
//——————————————————————————————————————————————————————————————————————

typedef struct {			// directions are for SCSIRegisterBus call ( -> parm, <- result)
	uchar *		SIMstaticPtr;		// <- alloc. ptr to the SIM's static vars
	long		staticSize;			// -> num bytes SIM needs for static vars
	OSErr		(*SIMinit)();		// -> pointer to the SIM init routine
	void		(*SIMaction)();		// -> pointer to the SIM action routine
	long		(*SIM_ISR)();		// -> pointer to the SIM ISR routine
	long		(*SIMInterruptPoll)();	// -> pointer to the SIM interrupt poll routine
	void		(*NewOldCall)();	// -> pointer to the SIM NewOldCall routine
	ushort		ioPBSize;			// -> size of SCSI_IO_PBs required for this SIM		<SM6> pdw
	Boolean		oldCallCapable;		// -> true if this SIM can handle old-API calls
	uchar		simInfoUnused1;		// ->
	long		simInternalUse;		// xx not affected or viewed by XPT
	void		(*XPT_ISR)();		// <- ptr to the XPT ISR
	void		(*EnteringSIM)();	// <- ptr to the EnteringSIM routine
	void		(*ExitingSIM)();	// <- ptr to the ExitingSIM routine
	void		(*MakeCallback)();	// <- pointer to the XPT layer’s MakeCallback routine
	ushort		busID;				// <- bus number for the registered bus
	ushort		simInfoUnused3;		// <- 
	long		simInfoUnused4;		// <- 
} SIMinitInfo; 



/********* Glue between SCSI calls and SCSITrap format ***********/

enum {
	xptSCSIAction			= 0x0001,
	xptSCSIRegisterBus		= 0x0002,
	xptSCSIDeregisterBus	= 0x0003,
	xptSCSIReregisterBus	= 0x0004,
	xptSCSIKillXPT			= 0x0005	// kills Mini-XPT after transition 
};

#ifdef __cplusplus
extern "C" {
#endif

#pragma parameter __D0	SCSIAction(__A0)			/* moveq #kSCSIx, D0;  _SCSIAtomic */
OSErr					SCSIAction(SCSI_PB *)			= {0x7001, _SCSIAtomic}; 

#pragma parameter __D0	SCSIRegisterBus(__A0)
OSErr					SCSIRegisterBus(SIMinitInfo *)	= {0x7002, _SCSIAtomic}; 

#pragma parameter __D0	SCSIDeregisterBus(__A0)
OSErr					SCSIDeregisterBus(SIMinitInfo *)	= {0x7003, _SCSIAtomic}; 

#pragma parameter __D0	SCSIReRegisterBus(__A0)
OSErr					SCSIReRegisterBus(SIMinitInfo *)	= {0x7004, _SCSIAtomic}; 

#pragma parameter __D0	SCSIKillXPT(__A0)
OSErr					SCSIKillXPT(SIMinitInfo *)	= {0x7005, _SCSIAtomic}; 

#ifdef __cplusplus
}
#endif



#endif __ACAM__
