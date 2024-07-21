/*
	File:		PowerMgr.h

	Contains:	Portable Macintosh Control Panel
				Power Manager Interim Equates

	Written by:	Andy Gong  x6595

	Copyright:	© 1991, 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	 2/11/93	CSS		Update from Horror.  Comments follow <H4-H2>:
		<H4>	 6/30/92	ag		Added new PowerManager command.
		<H3>	 8/26/91	SWC		Fixed <2> (conflict with procedure name in driver).
		<H2>	 8/26/91	SWC		Added definitions for the get/set brightness commands.
		 <6>	10/30/91	JSM		Add a few more comments, remove some power manager commands,
									misc. macros, and definition of Sleep(), none of which are used.
		 <5>	10/29/91	SAM		Removed stuff not used by the backlight driver.  Reincluded
									Power.h from 7.0 change <2>.
		 <4>	10/28/91	SAM		Rolled in Regatta file.

	Regatta History (most recent first):

		 <3>	 8/29/91	SAM		(ag) added BatteryStatusImmCmd for non-filtered values. This was
									a problem with asahi input (samples 1 second averaged).
		 <2>	 6/30/91	SAM		Merged from TERROR [<2>].
		 <1>	 5/15/91	SAM		Split off from TERRORProj.

	Terror Change History:

		 <2>	 6/26/91	ag		changed global values to unsigned char.
		 <1>	 1/23/91	ag		first checked in

	7.0 Change History:

		 <2>	 8/19/91	JSM		Include public Power.h, remove stuff that’s in Power.h (except
									for BOnIgnoreModem(), which for some reason isn’t there), remove
									other stuff that doesn’t appear to be used in the backlight
									driver at all. An interesting result of this: all the PowerMgr
									routines defined here were C functions, when they are actually
									Pascal functions (as defined in Power.h). This fixed a bug in
									DRVROpen() in backlight.c which calls SleepQInstall() and was
									mistakenly cleaning up too much on the stack. This really wasn't
									a problem, though, since it happened just before an unlink which
									fixed up the stack correctly.
		 <1>	 2/22/91	ag		roll 1.0 backlight driver into 7.0

*/

#include <retrace.h>
#include <Power.h>

/* Power Manager globals from InternalOnlyEqu.a */
typedef struct {
	char		SleepTime;
	char		HDTimeout;
	struct QHdr	SleepQHdr;
	char		SysTaskFlag;
	char		LastLevel;
	char		SaveSpeedo;
	char		Charger;
	char		SleepFlags;
	char		TimeOutdirtyFlag;
	Ptr			WakeVector;
	Ptr			HDvector;
	int			LastAct;
	int			LastHd;
	unsigned char		LowWarn;						/* <t2> ag this is an unsigned value */
	unsigned char		Cutoff;							/* <t2> ag this is an unsigned value */
	Ptr			BNmQEntry[9];
	char		BatQ[8];
	char		lpMSGvalid;
	char		IdleFlagCnt;
	unsigned char		BatAvg;							/* <t2> ag this is an unsigned value */
	char		NTSCcopy;
	char		pmfree[2];
	Ptr			RAMwatchPtr;
	Ptr			ROMwatchPtr;
	char		watchCrsr;
	char		BatQIndex;
	Ptr			SleepNetHook;
	Ptr			vBatInt;
	Ptr			vEnvInt;
	char		WakeWarn;
	char		Level4Cnt;
	Handle		lpSICNHndl;
	Str255		*(lpSTRPtr[4]);
	VBLTask		BatVBLTask;
	VBLTask		SwVBLTask;
	} PmgrGlobals;


/* MachineType returned by SysEnvirons for Portable */
#define		envPortable		8

/* Power Manager commands */
#define		PowerControlCmd	0x10
#define		PowerStatusCmd	0x18
#define		ModemSetCmd		0x50
#define		ScreenSetCmd	0x40
#define		SetBrightnessCmd 0x41
#define		GetScreenCmd	0x48
#define		GetBrightnessCmd 0x49
#define		ModemStatusCmd	0x58
#define		BatteryStatusCmd 0x68
#define		BatteryStatusImmCmd 0x69										/* <H4> command to read immediate not averaged values */
#define		SetWTimeCmd		0x80
#define		DisableWTimeCmd	0x82
#define		ReadWTimeCmd	0x88

/* Masks for ModemStatusCmd and ModemSetCmd */
#define		kModemOn			0x01
#define		kModemPortA			0x02
#define		kModemWakeup		0x04
#define		kModemInstalled		0x08
#define		kModemRingDetect	0x10
#define		kModemOnHook		0x20

/* Parameter block for PMgr calls */
typedef struct {
	short	pmgrCmd, pmgrCnt;
	Ptr 	pmgrXPtr, pmgrRPtr;
} PMgrPBlock;
typedef  PMgrPBlock *PMgrPBPtr;

/* Glue for PMgr calls */
pascal OSErr PMgr(PMgrPBPtr pbp)={0x205F,0xA085,0x3E80};
/*
	move.l	(sp)+,a0
	_PMgrOp
	move	d0,(sp)
*/

pascal OSErr Sleep()={0x7002,0xA08A};
/*
	moveq	#2,d0
	_Sleep
*/

/* access to Power Manager's local variables */
#define		PMgrLBase		0xd18
#define		PMgrLocal(offset) (*((char *)(*((long *)PMgrLBase)+(offset))))
#define		TOdirtyFlag		0x11
/* #define		BatAvg			0x52 */
