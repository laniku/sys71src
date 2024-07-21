
/************************************************************

Created: Friday, November 15, 1991 at 10:10 AM
 Power.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1989-1991
  All rights reserved

    This file is used in these builds: BigBang

	Change History (most recent first):

		<12>	11/19/91	JL		Changed 0x205F hex inlines in SleepQInstall to use the #pragma
									parameter (__A0) capabilities of the C compiler for better
									effeciency.
		<11>	 11/7/91	MH		add #pragma parameter __D0 to IdleUpdate and GetCPUSpeed to
									generate correct code.
		<10>	 7/31/91	JL		Updated Copyright.
		 <9>	 6/14/91	JL		Checked in official MPW 3.2Ä version. Switched order of the
									constants: sleepQType and slpQTyp. Temporarily lost updated
									copyright date; will be restored.
		 <8>	  2/5/91	stb		gs: add sleepQType
		 <7>	 1/30/91	JL		Checked in database generated file from dsg ; changed IdleUpdate
									- > BOff to Pascal functions.
		 <6>	 1/25/91	stb		JDR: add sleepRevoke and slpQType <5> 1/23/91 ag AG: Fixed
									function definitions defined by MSH!
		 <4>	 1/22/91	ag		MSH: Removed all Power Manager command definitions and the
									parameter block definition. Added interfaces to interface glue
									for modem, battery, and wakeup timer.
		 <3>	 1/18/91	ag		MSH - Removed private Power Manager equates.
		 <2>	 11/7/90	JL		Changed #defines to anonymous enums

	To Do:
************************************************************/


#ifndef __POWER__
#define __POWER__

#ifndef __TYPES__
#include <Types.h>
#endif


enum {


/* Bit positions for ModemByte */
 modemOnBit = 0,
 ringWakeUpBit = 2,
 modemInstalledBit = 3,
 ringDetectBit = 4,
 modemOnHookBit = 5,

/* masks for ModemByte */
 modemOnMask = 0x1,
 ringWakeUpMask = 0x4,
 modemInstalledMask = 0x8,
 ringDetectMask = 0x10,
 modemOnHookMask = 0x20,

/* bit positions for BatteryByte */
 chargerConnBit = 0,
 hiChargeBit = 1,
 chargeOverFlowBit = 2,
 batteryDeadBit = 3,
 batteryLowBit = 4,
 connChangedBit = 5,

/* masks for BatteryByte */
 chargerConnMask = 0x1,
 hiChargeMask = 0x2,
 chargeOverFlowMask = 0x4,
 batteryDeadMask = 0x8
};
enum {
 batteryLowMask = 0x10,
 connChangedMask = 0x20,

/* commands to SleepQRec sleepQProc */
 sleepRequest = 1,
 sleepDemand = 2,
 sleepWakeUp = 3,
 sleepRevoke = 4,

/* SleepQRec.sleepQFlags */
 noCalls = 1,
 noRequest = 2,

 slpQType = 16,
 sleepQType = 16
};

typedef char ModemByte;
typedef char BatteryByte;

typedef long PMResultCode;

struct SleepQRec {
 struct SleepQRec *sleepQLink;
 short sleepQType;		/*type = 16*/
 ProcPtr sleepQProc;	/*Pointer to sleep routine*/
 short sleepQFlags;
};

typedef struct SleepQRec SleepQRec;
typedef SleepQRec *SleepQRecPtr;


#ifdef __cplusplus
extern "C" {
#endif
pascal OSErr DisableWUTime(void); 
pascal OSErr GetWUTime(long *WUTime,Byte *WUFlag); 
pascal OSErr SetWUTime(long WUTime); 
pascal OSErr BatteryStatus(Byte *Status,Byte *Power); 
pascal OSErr ModemStatus(Byte *Status); 
#pragma parameter __D0 IdleUpdate
pascal long IdleUpdate(void)
 = 0xA285; 
#pragma parameter __D0 GetCPUSpeed
pascal long GetCPUSpeed(void)
 = {0x70FF,0xA485}; 
pascal void EnableIdle(void)
 = {0x7000,0xA485}; 
pascal void DisableIdle(void)
 = {0x7001,0xA485}; 
#pragma parameter SleepQInstall(__A0)
pascal void SleepQInstall(SleepQRecPtr qRecPtr)
 = 0xA28A; 
#pragma parameter SleepQRemove(__A0)
pascal void SleepQRemove(SleepQRecPtr qRecPtr)
 = 0xA48A; 
pascal void AOn(void)
 = {0x7004,0xA685}; 
pascal void AOnIgnoreModem(void)
 = {0x7005,0xA685}; 
pascal void BOn(void)
 = {0x7000,0xA685}; 
pascal void AOff(void)
 = {0x7084,0xA685}; 
pascal void BOff(void)
 = {0x7080,0xA685}; 
#ifdef __cplusplus
}
#endif

#endif
