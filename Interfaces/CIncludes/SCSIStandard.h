/*
	File:		SCSIStandard.h

	Contains:	Commonly used structures and values from SCSI standard

	Written by:	Paul Wolf

	Copyright:	© 1990-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM4>	11/10/93	fau		Update from SuperMunggio <SMG2>.
	  <SMG2>	 9/29/93	chp		Fix up header and conditional inclusion.
	   <SM3>	10/14/93	pdw		Got rid of the 'code' following ExtendedMsg.
	   <SM2>	 7/17/93	pdw		Changed phz to phas in all of the SCSIPhase enums.
	   <SM1>	 1/27/93	PW		first checked in

*/

#ifndef __SCSISTANDARD__
#define __SCSISTANDARD__


/********************************************************************/
// General SCSI stuff
/********************************************************************/

// SCSI status

#define	scsiStatGood			0x00		// Good Status
#define	scsiStatCheckCondition	0x02		// Check Condition
#define scsiStatConditionMet	0x04		// Condition Met
#define	scsiStatBusy			0x08		// Busy
#define scsiStatIntermediate	0x10		// Intermediate
#define scsiStatIntermedMet		0x14		// Intermediate - Condition Met
#define scsiStatResvConflict	0x18		// Reservation conflict
#define scsiStatTerminated		0x20		// Command terminated
#define scsiStatQFull			0x28		// Queue full


// SCSI messages

typedef enum {	kCmdCompleteMsg = 0,
				kExtendedMsg,					// 0x01
				kSaveDataPointerMsg,			// 0x02
				kRestorePointersMsg,			// 0x03
				kDisconnectMsg,					// 0x04
				kInitiatorDetectedErrorMsg,		// 0x05
				kAbortMsg,						// 0x06
				kMsgRejectMsg,					// 0x07
				kNoOperationMsg,				// 0x08
				kMsgParityErrorMsg,				// 0x09
				kLinkedCmdCompleteMsg,			// 0x0a
				kLinkedCmdCompleteWithFlagMsg,	// 0x0b
				kBusDeviceResetMsg,				// 0x0c
				kAbortTagMsg,					// 0x0d
				kClearQueueMsg,					// 0x0e
				kInitiateRecoveryMsg,			// 0x0f
				kReleaseRecoveryMsg,			// 0x10
				kTerminateIOProcessMsg,			// 0x11
				kSimpleQueueTag =  0x20,		// 0x20
				kHeadOfQueueTagMsg,				// 0x21
				kOrderedQueueTagMsg,			// 0x22
				kIgnoreWideResidueMsg			// 0x23
	} SCSI1stMsg;
				

// SCSI Phases	- 1st 8 phases (thru MessageInPhase) are straight off the chip's phase bits

typedef enum {	kDataOutPhase,			// 0
				kDataInPhase,			// 1
				kCommandPhase,			// 2
				kStatusPhase,			// 3
				kPhaseIllegal0,
				kPhaseIllegal1,
				kMessageOutPhase,		// 6
				kMessageInPhase,		// 7
				
				kBusFreePhase,			// 8
				kArbitratePhase,		// 9
				kSelectPhase,			// 0xA
				kMessageInPhaseNACK,	// 0xB
			kSCSIphaseBogus = 256
	} SCSIphase;


#endif __SCSISTANDARD__
