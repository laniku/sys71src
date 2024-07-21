
/************************************************************

Created: Saturday, July 27, 1991 at 6:42 PM
 Serial.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

	   <SM2>	 1/13/94	chp		Add lots of useful constants previously missing. The csCodes
									need new names since a few differ from function names only in
									case.
		 <7>	 7/31/91	JL		Updated Copyright.
		 <6>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <5>	 11/7/90	JL		Changed all #defines to anonymous enums

	To Do:
************************************************************/


#ifndef __SERIAL__
#define __SERIAL__

#ifndef __TYPES__
#include <Types.h>
#endif


enum {
	baud300 = 380,
	baud600 = 189,
	baud1200 = 94,
	baud1800 = 62,
	baud2400 = 46,
	baud3600 = 30,
	baud4800 = 22,
	baud7200 = 14,
	baud9600 = 10,
	baud19200 = 4,
	baud38400 = 1,
	baud57600 = 0,

	stop10 = 16384,
	stop15 = -32768,
	stop20 = -16384,

	noParity = 0,
	oddParity = 4096,
	evenParity = 12288,

	data5 = 0,
	data6 = 2048,
	data7 = 1024,
	data8 = 3072
};

enum {
	ctsEvent = 32,
	breakEvent = 128,
	xOffWasSent = 128,
	dtrNegated = 64,

	ainRefNum = -6,				/*serial port A input*/
	aoutRefNum = -7,			/*serial port A output*/
	binRefNum = -8,				/*serial port B input*/
	boutRefNum = -9,			/*serial port B output*/

	swOverrunErr = 1,			/*serial driver error masks*/
	breakErr = 8,				/*serial driver error masks*/
	parityErr = 16,				/*serial driver error masks*/
	hwOverrunErr = 32			/*serial driver error masks*/
};


// csCodes for Control routines
enum {
	serReset			= 8,
	serSetBuf			= 9,
	serHShake			= 10,
	serClrBrk			= 11,
	serSetBrk			= 12,
	serSetBaud			= 13,
	serHShakeDTR		= 14,
	serSetMIDI			= 15,
	serSetMisc			= 16,
	serSetDTR			= 17,
	serClrDTR			= 18,

	serSetPEChar		= 19,
	serSetPECharAlt		= 20,

	serSetXOff			= 21,
	serClrXOff			= 22,
	serSendXOnCond		= 23,
	serSendXOn			= 24,
	serSendXOffCond		= 25,
	serSendXOff			= 26,

	serChanReset		= 27,

	serSet230KBaud		= 'JF',
	serSetPollWrite 	= 'jf',
	serSetFlushCount	= 'FC'
};


// csCodes for Status routines
enum {
	serGetBuf			= 2,
	serStatus			= 8,
	serGetVers			= 9,
	serGetVersSys		= 0x8000
};



// miscellaneous options for the serSetMisc control function (csCode 16)
enum {
	OPT_CLOCK_EXTERNAL	= 0x40,
	OPT_PRESERVE_DTR	= 0x80
};


enum {sPortA,sPortB};
typedef unsigned char SPortSel;


struct SerShk {
	char fXOn;				/*XOn flow control enabled flag*/
	char fCTS;				/*CTS flow control enabled flag*/
	unsigned char xOn;		/*XOn character*/
	unsigned char xOff;		/*XOff character*/
	char errs;				/*errors mask bits*/
	char evts;				/*event enable mask bits*/
	char fInX;				/*Input flow control enabled flag*/
	char fDTR;				/*DTR input flow control flag*/
};

typedef struct SerShk SerShk;

struct SerStaRec {
	char cumErrs;
	char xOffSent;
	char rdPend;
	char wrPend;
	char ctsHold;
	char xOffHold;
};

typedef struct SerStaRec SerStaRec;


#ifdef __cplusplus
extern "C" {
#endif

pascal OSErr SerReset(short refNum,short serConfig);
pascal OSErr SerSetBuf(short refNum,Ptr serBPtr,short serBLen);
pascal OSErr SerHShake(short refNum,const SerShk *flags);
pascal OSErr SerSetBrk(short refNum);
pascal OSErr SerClrBrk(short refNum);
pascal OSErr SerGetBuf(short refNum,long *count);
pascal OSErr SerStatus(short refNum,SerStaRec *serSta);

#ifdef __cplusplus
}
#endif

#endif
