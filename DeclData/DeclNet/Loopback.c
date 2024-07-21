/*
	File:		Loopback.c

	Contains:	Ethernet loopback test code

	Written by:	Sean Findley

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 10/6/92	GDW		New location for ROMLink tool.
	   <SM5>	 6/22/92	mal		Modified so ptr and size to loopback test data is passed from
									the driver since shared by Sonic and Mace drivers.
		<SM1>	 6/11/92	CS		Roll-in changes from Reality:
									<2>	  6/1/92	DTY		Include TextUtils.h for the new home of EqualString.
		 													TextUtils now contains the EqualString prototype, so include it.
		 <3>	 3/26/92	FM		Rolled into reality
		 <2>	 2/11/92	RB		Use the real EqualString to avoid having to link old C libraries
									with this code.
		 <2>	 4/21/91	CCH		Rolled in Sean Findley's changes.
		 <1>	12/14/90	JK		Added to build

	To Do:
*/

#include			<TextUtils.h>

#include			"memory.h"
#include			"devices.h"
#include			"files.h"
#include			"appletalk.h"
#include			"OSUtils.h"

typedef struct
{
	char Addr[6];
} Enet;

typedef struct
{
	Enet			Destination;							/* Ethernet destination */
	Enet			Source;									/* Ethernet source */
	unsigned short	EProtocoltype;							/* Ethernet protocol type */
	char			testdata[255];
} LBpacket;

typedef union												/* parameter block for calling .ENET */
{
	CntrlParam		ctl;									/* for ctl calls */
	struct
	{
		char		filler[28];
		unsigned short EprotType;
		Ptr			EBuffPtr;
		unsigned short EBuffSize;
		unsigned short EDataSize;
	} info;
	MPPParamBlock	ecall;
} Edrvrparms;

#define				Ehandler	DDP.DDPptrs.listener
#define				EWdsPointer DDP.DDPptrs.wdsPointer
#define				EKillQEl	EBuffPtr

#define				ERdCancel	251
#define				ERead		250
#define				EWrite		249
#define				EDetachPH	248
#define				EAttachPH	247

#define				Ethhdrsz	14

Boolean cmpdata(char *p1, char *p2, short len)	/* true = data equal, false = data not equal */
{
short i;
	for(i=0;i<len;i++)
	{
		if(p1[i] != p2[i])
			return(false);
	}
	return(true);
}

killtest(Edrvrparms *pbw, Edrvrparms *pb)
{
	pbw->ctl.csCode = ERdCancel;
	pbw->info.EKillQEl = (Ptr) pb;
	PBControl((ParmBlkPtr) pbw,false);
	pbw->ctl.csCode = EDetachPH;
	PBControl((ParmBlkPtr) pbw,false);
}

Boolean	LOOPBACKTEST(short refnum,Enet *enetaddr, int AppleData, short AppleDataSz)
{
LBpacket			LBPR,LBPW;
Edrvrparms			pb,pbw;
WDSElement			wds[2];
unsigned long		secs1,secs2;

	pb.ctl.ioCRefNum = refnum;
	pb.ctl.ioCompletion = nil;
	
	pb.ctl.csCode = EAttachPH;
	pb.info.EprotType = 0x809B;
	pb.ecall.Ehandler = nil;
	
	if (PBControl((ParmBlkPtr) &pb,false))	/* attach special protocol using default handler */
		return(false);
		
	pb.ctl.csCode = ERead;
	pb.info.EBuffPtr = (Ptr) &LBPR;
	pb.info.EBuffSize = sizeof(LBpacket);
	
	if (PBControl((ParmBlkPtr) &pb,true))	/* setup a read using default handler */
	{
		pb.ctl.csCode = EDetachPH;
		PBControl((ParmBlkPtr) &pb,false);
		return(false);
	}
	
	pbw = pb;
	wds[0].entryLength = Ethhdrsz + AppleDataSz;
	wds[0].entryPtr = (Ptr) &LBPW;
	wds[1].entryLength = 0;
	LBPW.Destination = *enetaddr;
	LBPW.Source = *enetaddr;
	LBPW.EProtocoltype = 0x809B;
	BlockMove((Ptr)AppleData,LBPW.testdata,AppleDataSz);
	pbw.ecall.EWdsPointer = (Ptr) wds;
	pbw.ctl.csCode = EWrite;
	
	if (PBControl((ParmBlkPtr) &pbw,false))	/* write a packet to ourself */
	{
		killtest(&pbw,&pb);
		return(false);
	}
	
	GetDateTime(&secs1);
	while (pb.ctl.ioResult == 1)	/* wait for default read to complete or timeout */
	{
		GetDateTime(&secs2);
		if (secs2 - secs1 > 3)
		{
			killtest(&pbw,&pb);
			return(false);
		}
	}
	
	pbw.ctl.csCode = EDetachPH;
	PBControl((ParmBlkPtr) &pbw,false);
	
	if (!cmpdata(LBPR.testdata,LBPW.testdata,AppleDataSz))	/* check data looped back */
		return(false);
		
	return(true);
}
