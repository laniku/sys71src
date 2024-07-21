//************************************************************************
//			EGRET Manager Equates
//
//	File:		EgretEqu.h
//
//	Contains:	Equate definitions used by EgretMgr
//
//	Written by:	Greg Shcroeder
//
//	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.
//
//   This file is used in these builds: Mac32
//
//
//	Change History (most recent first):
//
//		<P2>	 1/16/92	GS		Update Egret Equates to include equates for the Cuda Firmware.
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	  Pre-Pandora ROM comments begin here.
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//
//	To Do:
//
//************************************************************************

//
//				Egret parameter block
//
// Egret Manager Parameter Block  

typedef struct {
	Byte			pbCmdType;
	Byte			pbCmd;
	union	{
		 long	pblong;
		 short	pbword[2];
		 Byte	pbbyte[4];
	} pbParm;
	short			pbByteCnt;
	Ptr				pbBufPtr;
	Byte	pbFlags; /*Was unsigned Byte*/
	Byte	pbSpareFlags; /*Was unsigned Byte*/
	short			pbResult;
	Ptr				pbCompletion;
} EgretPB, *EgretPBPtr;

#define		EgretPBSize		sizeof(EgretPB)

//________________________________________________________________________________________________
//				Egret Globals

typedef	struct	{
	short		flags;					// Egret Manager state flags
	short		sendHdrCnt;				// # bytes in command header to send
	Ptr			sendHdrPtr;				// ptr into command header
	short		sendDataCnt;			// # data bytes to send for current cmd
	Ptr			sendDataPtr;			// ptr to next data byte to send
	short		rcvHdrCnt;				// # bytes to receive in response header
	short		rcvHdrIndex;			// current index into receive header buffer
	short		rcvDataCnt;				// # data bytes to receive
	long		rcvDataPtr;				// ptr into receive buffer
	Byte		rcvHeader[12];			// temp buffer for response packet
	Ptr			completion;				// ptr to completion routine for current packet
	Ptr			tickComp;				// tick packet completion routine
	Ptr			PDMComp;				// Eclipse PowerDown Message Handler Vector					
	Ptr			adbPb;					// ptr to ADB auto response param block
	Ptr			curPb;					// ptr to current param block
	Byte		workPb[EgretPBSize];	// local parameter block for unsolicited packets
	}	EgretGlobals, *EgretGlblPtr;		

#define		EgretGlobSize	sizeof(EgretGlobals)
//________________________________________________________________________________________________
//		Response Packet
//
typedef	struct	{						// record describing rcvHeader
	Byte		length;					// number of bytes in rcvHeader (4+data count)
	Byte		respType;				// packet type (0=ADB, 3=ticks)
	Byte		respFlag;				// flags
	Byte		respCmd;				// command
	Byte		respData[8];			// data bytes that came in (ticks, adb data)
		}	respPacket;

//________________________________________________________________________________________________
//		Record Descriptor for Response Packet Header
//
typedef struct	{						// record descriptor for Response packet Header			
	Byte		RespAttn;				// Attention Byte										
	Byte		RespPktType;			// Packet type											
	Byte		RespFlags;				// Flags byte											
	Byte		RespCmd;				// Command number										
	Byte		RespData[8];			// Data area for ADB or Time data						
		}	RespHeader;																		
			
//________________________________________________________________________________________________
//		Egret8 and Caboose Bit definitions

#define		xcvrSes  		3			// ADBu session 			PB3
#define		viaFull			4   		// Via full indicator 		PB4
#define		sysSes			5   		// System session is 		PB5

//________________________________________________________________________________________________
//		Cuda VIA Bit Definitions

#define		TReq			3				// CUDA transaction					PB3										
#define		vByteAck		4				// acknowledge byte transfer		PB4						
#define		TIP				5				// System transaction				PB5						

#define		ACRmode			%00001100		// shift reg mode			(input with ext clock)
#define		SRdir			4				// shift reg direction bit 	(0=input,  1=output)
											//							from Cuda, from System
#define		vShift			2				// shift reg interrupt bit

//
//_______________________________________________________________________
//					Egret Manager Flag Bit Definitions

#define		busy			0				// flag bit 0 means we're busy with a packet
#define		openData		1				// flag bit 1 means this is an open ended read response
#define		BadPkt			2				// flag bit 2 means 1= Error Packet in progress 			
#define		PBPending		3				// PB aborted and pending								

#define		IdleAckFlag		4				// flag bit 4 set means an IdleAck pkt expected (Cuda)	
//
//_______________________________________________________________________
//	Flag Bits in the ADB Status byte returned from the ADB processor

#define		EgSRQ			0				// bit 0, 1=SRQ asserted
#define		EgTimeOut		1				// bit 1, 1=Active device did not have data available
#define		EgSRQError		2				// bit 2, 1=Device asserted excessive SRQ period
#define		EgBusError		3				// bit 3, 1=Timing error in bit cell was detected
#define		EgAutoPoll		6				// bit 6, 1=Data is from an Auto Poll
#define		EgResponse		7				// bit 7, 1=Response packett in process


//________________________________________________________________________________________________
//				Elsie/Erickson DFAC initial settings
				
#define		ElsieDFAC		0x0057
#define		EricksonDFAC	0x0000
#define		EclipseDFAC		0x0010			// initial dfac values for Eclipse and Spike					<t3> djw
#define		SpikeDFAC		0x0010


//________________________________________________________________________________________________
//						Packet types


#define		adbPkt			0x0000			// ADB request packet type
#define		pseudoPkt		0x0001			// pseudo commands packet type
#define		errorPkt		0x0002			// error packets type
#define		tickPkt			0x0003			// Egret 1 second tick packet type
#define		PDMPkt			0x0004			// PowerDown Message Packet (From Egret)						<T2>
#define		PDMVectPkt		0x00FE			// Eclipse Init PowerDown Message vector						<T2>
#define		specialPkt		0x00FF			// used to install ADB handler/pb

//________________________________________________________________________________________________
// The following equates are ShutDown Initiator codes.
//

#define		FrmChassisSw	 		0x01				// Initiate ShutDown from Chassis Power Switch
#define		FrmKeyBdSw		 		0x02				// Initiate ShutDown from KeyBoard Switch
#define		FrmKeySw		 		0x03				// Initiate ShutDown from Chassis Power Switch

//
//________________________________________________________________________________________________
//						Pseudo commands

#define		NopCmd			 		0x00
#define		APoll			 		0x01				// start/stop autopoll
#define		Rd6805addr		 		0x02				// read 6805 address
#define		RdTime			 		0x03				// read real time clock pseudo commmand
#define		RdRomSize		 		0x04				// get romsize command
#define		RdRomBase		 		0x05				// get rom base address
#define		RdRomHeader		 		0x06				// get rom header address
#define		RdPram			 		0x07				// read parameter ram
#define		Wr6805Addr		 		0x08				// write 6805 address
#define		WrTime			 		0x09				// write time command
#define		PwrDown			 		0x0A				// Erickson powerdown command
#define		WrPwrupTime		 		0x0B				// Erickson set powerup time
#define		WrPram			 		0x0C				// write parameter ram
#define		MonoReset		 		0x0D				// Monostable reset
#define		WrDFAC			 		0x0E				// write DFAC
#define		WrIIC			 		0x0E				// write IIC
#define		Egretdiags		 		0x0F				// run egret diagnostics
#define		RdCtlPanel		 		0x10				// Sense control panel enable
#define		RdBattery		 		0x10				// Sense if battery was changed							<P1>
#define		ResetEgret		 		0x11				// Egret Cold start command
#define		EnDisVpp		 		0x12				// ELSIE enable/disabe VPP
#define		SetIPL			 		0x12				// Set IPL level											<P1>
#define		EnDisFiles		 		0x13				// enable/disable file server flag
#define		SetAutopoll		 		0x14				// set autopoll rate
#define		RdPramSize		 		0x15				// get parameter ram size
#define		RdAutoRate		 		0x16				// get autopoll rate
#define		WrBusDelay		 		0x17				// set bus delay constant
#define		RdBusDelay		 		0x18				// get busdelay constant
#define		WrDevList		 		0x19				// set ADB device list
#define		RdDevList		 		0x1A				// get ADB device list
#define		Wr1SecMode		 		0x1B				// set 1 second interrupt mode
#define		EnDisKbdNmi		 		0x1C				// enable/disable keyboard NMI
#define		EnDisParse		 		0x1D				// enable/disable post parse R2 A2
#define		WrHangTout		 		0x1E				// set hang threshold
#define		RdHangTout		 		0x1F				// get hang threshold
#define		SetDefDFAC		 		0x20				// Set Default DFAC String 								<T2>
#define		EnDisPDM		 		0x21				// Enable/Disable PowerDown Message						<T2>
#define		DFACorIIC		 		0x22				// Std DFAC or IIC Support								<P1>
#define		WakeUpMode		 		0x23				// Enable/Disable WakeUpMode								<P1>
#define		TimerTickle		 		0x24				// ShutDown Timer Tickle									<P1>
#define		MaxPseudoCmd	 		TimerTickle		// largest possible pseudo command number				<P1>

//
//__________________________________________________________________________________________________
//					MISC Equates
					

#define		InvPseudo		 		0x0202			// Invalid Pseudo packet <6>
#define		InvPkt			 		0x0201			// Invalid Packet type <6>

#define		Enable			 		0x00FF			// Nonzero to enable Egret functions							<T2>
#define		Disable			 		0x0000			// Zero to disable Egret functions							<T2>
#define		MaxRetries		 		0x0100			// 256 Retries to communicate with Egret in SendEgretCmd<9>
#define		MaxTout			 		0x2000			// timeout waiting for Vsr irq from Egret 10millsecs<9>
#define		DelayCnt		 		0x0068			// count for register base delay100us routine
#define		EclipseDelay	 		00025			// Extra delay required for Eclipse							<T2>
#define		PollStackSize	 		0x0020			// 32 byte buffer for SCC Poll data
#define		Mode3Clock		 		0x0003			// Mode 3 packets for clock data
#define		MRUAddr			 		0x00B3			// MRU address in Egret/Caboose							<10>
#define		LRUAddr			 		0x00B4			// LRU address in Egret/Caboose							<10>
#define		CMRUAddr		 		0x00B2			// MRU address in Cuda									<P1>
#define		CLRUAddr		 		0x00B3			// LRU address in Cuda									<P1>
