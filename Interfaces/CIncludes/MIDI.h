
/************************************************************

Created: Saturday, July 27, 1991 at 4:36 PM
 MIDI.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1988-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <8>	 7/30/91	JL		Updated Copyright.
		 <7>	 1/29/91	JL		C++ requires midiToolNum to be a #define if it's going to be
									used in the Inlines.
		 <6>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <4>	11/28/90	JL		Put formal parameter names back.
		 <3>	 11/7/90	JL		Changed all #defines to anonymous enums
		 <2>	 11/4/90	dba		used constStr255Parameter; got rid of erroneous const on some
									Str255 parameters that were output strings; got rid of some
									extraneous parameter names

************************************************************/


#ifndef __MIDI__
#define __MIDI__

#ifndef __TYPES__
#include <Types.h>
#endif


enum {


#define midiToolNum 4				/*tool number of MIDI Manager for SndDispVersion call*/

 midiMaxNameLen = 31,				/*maximum number of characters in port and client names*/

/* Time formats */
 midiFormatMSec = 0,				/*milliseconds*/
 midiFormatBeats = 1,				/*beats*/
 midiFormat24fpsBit = 2,			/*24 frames/sec.*/
 midiFormat25fpsBit = 3,			/*25 frames/sec.*/
 midiFormat30fpsDBit = 4,			/*30 frames/sec. drop-frame*/
 midiFormat30fpsBit = 5,			/*30 frames/sec.*/
 midiFormat24fpsQF = 6,				/*24 frames/sec. longInt format */
 midiFormat25fpsQF = 7,				/*25 frames/sec. longInt format */
 midiFormat30fpsDQF = 8,			/*30 frames/sec. drop-frame longInt format */
 midiFormat30fpsQF = 9,				/*30 frames/sec. longInt format */
 midiInternalSync = 0,				/*internal sync*/
 midiExternalSync = 1,				/*external sync*/

/* Port types*/
 midiPortTypeTime = 0,				/*time port*/
 midiPortTypeInput = 1,				/*input port*/
 midiPortTypeOutput = 2,			/*output port*/
 midiPortTypeTimeInv = 3,			/*invisible time port*/

/* OffsetTimes  */
 midiGetEverything = 0x7FFFFFFF,	/*get all packets, regardless of time stamps*/
 midiGetNothing = 0x80000000,		/*get no packets, regardless of time stamps*/
 midiGetCurrent = 0x00000000		/*get current packets only*/
};
enum {

/*    MIDI data and messages are passed in MIDIPacket records (see below).
    The first byte of every MIDIPacket contains a set of flags
   
    bits 0-1    00 = new MIDIPacket, not continued
                     01 = begining of continued MIDIPacket
                     10 = end of continued MIDIPacket
                    11 = continuation
    bits 2-3     reserved
  
    bits 4-6      000 = packet contains MIDI data
   
                     001 = packet contains MIDI Manager message
   
    bit 7              0 = MIDIPacket has valid stamp
                        1 = stamp with current clock */
 midiContMask = 0x03,
 midiNoCont = 0x00,
 midiStartCont = 0x01,
 midiMidCont = 0x03,
 midiEndCont = 0x02,
 midiTypeMask = 0x70,
 midiMsgType = 0x00,
 midiMgrType = 0x10,
 midiTimeStampMask = 0x80,
 midiTimeStampCurrent = 0x80,
 midiTimeStampValid = 0x00,

/*    MIDI Manager MIDIPacket command words (the first word in the data field
    for midiMgrType messages) */
 midiOverflowErr = 0x0001,
 midiSCCErr = 0x0002,
 midiPacketErr = 0x0003,
 midiMaxErr = 0x00FF,				/*all command words less than this value  are error indicators*/

/* Valid results to be returned by readHooks */
 midiKeepPacket = 0,
 midiMorePacket = 1,
 midiNoMorePacket = 2,

/* Errors: */
 midiNoClientErr = -250,			/*no client with that ID found*/
 midiNoPortErr = -251				/*no port with that ID found*/
};
enum {
 midiTooManyPortsErr = -252,		/*too many ports already installed in the system*/
 midiTooManyConsErr = -253,			/*too many connections made*/
 midiVConnectErr = -254,			/*pending virtual connection created*/
 midiVConnectMade = -255,			/*pending virtual connection resolved*/
 midiVConnectRmvd = -256,			/*pending virtual connection removed*/
 midiNoConErr = -257,				/*no connection exists between specified ports*/
 midiWriteErr = -258,				/*MIDIWritePacket couldn't write to all connected ports*/
 midiNameLenErr = -259,				/*name supplied is longer than 31 characters*/
 midiDupIDErr = -260,				/*duplicate client ID*/
 midiInvalidCmdErr = -261,			/*command not supported for port type*/

/*     Driver calls: */
 midiOpenDriver = 1,
 midiCloseDriver = 2
};

struct MIDIPacket {
 unsigned char flags;
 unsigned char len;
 long tStamp;
 unsigned char data[249];
};

typedef struct MIDIPacket MIDIPacket;
typedef MIDIPacket *MIDIPacketPtr;

struct MIDIClkInfo {
 short sync;						/*synchronization external/internal*/
 long curTime;						/*current value of port's clock*/
 short format;						/*time code format*/
};

typedef struct MIDIClkInfo MIDIClkInfo;

struct MIDIIDRec {
 OSType clientID;
 OSType portID;
};

typedef struct MIDIIDRec MIDIIDRec;

struct MIDIPortInfo {
 short portType;					/*type of port*/
 MIDIIDRec timeBase;				/*MIDIIDRec for time base*/
 short numConnects;					/*number of connections*/
 MIDIIDRec cList[1];				/*ARRAY [1..numConnects] of MIDIIDRec*/
};

typedef struct MIDIPortInfo MIDIPortInfo;
typedef MIDIPortInfo *MIDIPortInfoPtr, **MIDIPortInfoHdl;

struct MIDIPortParams {
 OSType portID;						/*ID of port, unique within client*/
 short portType;					/*Type of port - input, output, time, etc.*/
 short timeBase;					/*refnum of time base, 0 if none*/
 long offsetTime;					/*offset for current time stamps*/
 Ptr readHook;						/*routine to call when input data is valid*/
 long refCon;						/*refcon for port (for client use)*/
 MIDIClkInfo initClock;				/*initial settings for a time base*/
 Str255 name;						/*name of the port, This is a real live string, not a ptr.*/
};

typedef struct MIDIPortParams MIDIPortParams;
typedef MIDIPortParams *MIDIPortParamsPtr;

struct MIDIIDList {
 short numIDs;
 OSType list[1];
};

typedef struct MIDIIDList MIDIIDList;
typedef MIDIIDList *MIDIIDListPtr, **MIDIIDListHdl;


#ifdef __cplusplus
extern "C" {
#endif
/* 
    
         Prototype Declarations for readHook and timeProc
        
         extern pascal short myReadHook(MIDIPacketPtr myPacket, long myRefCon);
         extern pascal void myTimeProc(long curTime, long myRefCon);
        
         MIDI Manager Routines
*/

pascal long SndDispVersion(short toolnum); 
pascal OSErr MIDISignIn(OSType clientID,long refCon,Handle icon,ConstStr255Param name)
 = {0x203C,0x0004,midiToolNum,0xA800}; 
pascal void MIDISignOut(OSType clientID)
 = {0x203C,0x0008,midiToolNum,0xA800}; 
pascal MIDIIDListHdl MIDIGetClients(void)
 = {0x203C,0x000C,midiToolNum,0xA800}; 
pascal void MIDIGetClientName(OSType clientID,Str255 name)
 = {0x203C,0x0010,midiToolNum,0xA800}; 
pascal void MIDISetClientName(OSType clientID,ConstStr255Param name)
 = {0x203C,0x0014,midiToolNum,0xA800}; 
pascal MIDIIDListHdl MIDIGetPorts(OSType clientID)
 = {0x203C,0x0018,midiToolNum,0xA800}; 
pascal OSErr MIDIAddPort(OSType clientID,short BufSize,short *refnum,MIDIPortParamsPtr init)
 = {0x203C,0x001C,midiToolNum,0xA800}; 
pascal MIDIPortInfoHdl MIDIGetPortInfo(OSType clientID,OSType portID)
 = {0x203C,0x0020,midiToolNum,0xA800}; 
pascal OSErr MIDIConnectData(OSType srcClID,OSType srcPortID,OSType dstClID,
 OSType dstPortID)
 = {0x203C,0x0024,midiToolNum,0xA800}; 
pascal OSErr MIDIUnConnectData(OSType srcClID,OSType srcPortID,OSType dstClID,
 OSType dstPortID)
 = {0x203C,0x0028,midiToolNum,0xA800}; 
pascal OSErr MIDIConnectTime(OSType srcClID,OSType srcPortID,OSType dstClID,
 OSType dstPortID)
 = {0x203C,0x002C,midiToolNum,0xA800}; 
pascal OSErr MIDIUnConnectTime(OSType srcClID,OSType srcPortID,OSType dstClID,
 OSType dstPortID)
 = {0x203C,0x0030,midiToolNum,0xA800}; 
pascal void MIDIFlush(short refnum)
 = {0x203C,0x0034,midiToolNum,0xA800}; 
pascal ProcPtr MIDIGetReadHook(short refnum)
 = {0x203C,0x0038,midiToolNum,0xA800}; 
pascal void MIDISetReadHook(short refnum,ProcPtr hook)
 = {0x203C,0x003C,midiToolNum,0xA800}; 
pascal void MIDIGetPortName(OSType clientID,OSType portID,Str255 name)
 = {0x203C,0x0040,midiToolNum,0xA800}; 
pascal void MIDISetPortName(OSType clientID,OSType portID,ConstStr255Param name)
 = {0x203C,0x0044,midiToolNum,0xA800}; 
pascal void MIDIWakeUp(short refnum,long time,long period,ProcPtr timeProc)
 = {0x203C,0x0048,midiToolNum,0xA800}; 
pascal void MIDIRemovePort(short refnum)
 = {0x203C,0x004C,midiToolNum,0xA800}; 
pascal short MIDIGetSync(short refnum)
 = {0x203C,0x0050,midiToolNum,0xA800}; 
pascal void MIDISetSync(short refnum,short sync)
 = {0x203C,0x0054,midiToolNum,0xA800}; 
pascal long MIDIGetCurTime(short refnum)
 = {0x203C,0x0058,midiToolNum,0xA800}; 
pascal void MIDISetCurTime(short refnum,long time)
 = {0x203C,0x005C,midiToolNum,0xA800}; 
pascal void MIDIStartTime(short refnum)
 = {0x203C,0x0060,midiToolNum,0xA800}; 
pascal void MIDIStopTime(short refnum)
 = {0x203C,0x0064,midiToolNum,0xA800}; 
pascal void MIDIPoll(short refnum,long offsetTime)
 = {0x203C,0x0068,midiToolNum,0xA800}; 
pascal OSErr MIDIWritePacket(short refnum,MIDIPacketPtr packet)
 = {0x203C,0x006C,midiToolNum,0xA800}; 
pascal Boolean MIDIWorldChanged(OSType clientID)
 = {0x203C,0x0070,midiToolNum,0xA800}; 
pascal long MIDIGetOffsetTime(short refnum)
 = {0x203C,0x0074,midiToolNum,0xA800}; 
pascal void MIDISetOffsetTime(short refnum,long offsetTime)
 = {0x203C,0x0078,midiToolNum,0xA800}; 
pascal long MIDIConvertTime(short srcFormat,short dstFormat,long time)
 = {0x203C,0x007C,midiToolNum,0xA800}; 
pascal long MIDIGetRefCon(short refnum)
 = {0x203C,0x0080,midiToolNum,0xA800}; 
pascal void MIDISetRefCon(short refnum,long refCon)
 = {0x203C,0x0084,midiToolNum,0xA800}; 
pascal long MIDIGetClRefCon(OSType clientID)
 = {0x203C,0x0088,midiToolNum,0xA800}; 
pascal void MIDISetClRefCon(OSType clientID,long refCon)
 = {0x203C,0x008C,midiToolNum,0xA800}; 
pascal short MIDIGetTCFormat(short refnum)
 = {0x203C,0x0090,midiToolNum,0xA800}; 
pascal void MIDISetTCFormat(short refnum,short format)
 = {0x203C,0x0094,midiToolNum,0xA800}; 
pascal void MIDISetRunRate(short refnum,short rate,long time)
 = {0x203C,0x0098,midiToolNum,0xA800}; 
pascal Handle MIDIGetClientIcon(OSType clientID)
 = {0x203C,0x009C,midiToolNum,0xA800}; 
#ifdef __cplusplus
}
#endif

#endif
