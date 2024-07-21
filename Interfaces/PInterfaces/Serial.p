
{
Created: Saturday, July 27, 1991 at 11:40 PM
 Serial.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606

	Change History (most recent first):

		 <4>	 7/31/91	JL		Updated Copyright.
		 <3>	 1/27/91	LN		Checked in Database generate file from DSG.
		<2>		10/3/90		JAL		Removed RAMSDOpen and RAMSDClose. Obsolete.

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Serial;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingSerial}
{$SETC UsingSerial := 1}

{$I+}
{$SETC SerialIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := SerialIncludes}

CONST
baud300 = 380;
baud600 = 189;
baud1200 = 94;
baud1800 = 62;
baud2400 = 46;
baud3600 = 30;
baud4800 = 22;
baud7200 = 14;
baud9600 = 10;
baud19200 = 4;
baud57600 = 0;
stop10 = 16384;
stop15 = -32768;
stop20 = -16384;
noParity = 0;
oddParity = 4096;
evenParity = 12288;
data5 = 0;
data6 = 2048;
data7 = 1024;
data8 = 3072;
ctsEvent = 32;
breakEvent = 128;
xOffWasSent = 128;
dtrNegated = 64;
ainRefNum = -6;		{serial port A input}
aoutRefNum = -7;	{serial port A output}
binRefNum = -8;		{serial port B input}
boutRefNum = -9;	{serial port B output}

TYPE
SPortSel = (sPortA,sPortB);


SerShk = PACKED RECORD
 fXOn: Byte;		{XOn flow control enabled flag}
 fCTS: Byte;		{CTS flow control enabled flag}
 xOn: CHAR;			{XOn character}
 xOff: CHAR;		{XOff character}
 errs: Byte;		{errors mask bits}
 evts: Byte;		{event enable mask bits}
 fInX: Byte;		{Input flow control enabled flag}
 fDTR: Byte;		{DTR input flow control flag}
 END;

SerStaRec = PACKED RECORD
 cumErrs: Byte;
 xOffSent: Byte;
 rdPend: Byte;
 wrPend: Byte;
 ctsHold: Byte;
 xOffHold: Byte;
 END;


FUNCTION SerReset(refNum: INTEGER;serConfig: INTEGER): OSErr;
FUNCTION SerSetBuf(refNum: INTEGER;serBPtr: Ptr;serBLen: INTEGER): OSErr;
FUNCTION SerHShake(refNum: INTEGER;flags: SerShk): OSErr;
FUNCTION SerSetBrk(refNum: INTEGER): OSErr;
FUNCTION SerClrBrk(refNum: INTEGER): OSErr;
FUNCTION SerGetBuf(refNum: INTEGER;VAR count: LONGINT): OSErr;
FUNCTION SerStatus(refNum: INTEGER;VAR serSta: SerStaRec): OSErr;


{$ENDC} { UsingSerial }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

