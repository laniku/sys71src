/*
	File:		I2C_Cyclone.c

	Contains:	This is the I2C component main code

	Written by:	Dan Hitchens

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM3>	 6/23/93	CSS		Fix to work with ComponentFunctionProcPtr's.
	   <SM2>	 6/14/93	kc		Roll in Ludwig.
	   <LW2>	 1/21/93	DH		Fix so routines will transfer  up to 256 bytes at a time until
									all bytes are transfered.

*/
#include <Memory.h>
#include <Components.h>
#include <QTComponents.h>
#include "I2C_Cyclone.h"
#include "EgretEqu.h"
#include "CycloneDigi.h"
#include "I2C.h"


#define FALSE 0
#define TRUE 1

/* Uncomment this #define _BreakTime_ to cause a break at the start of every routine */
//#define _BreakTime_

/* private prototypes */
pascal ComponentResult InitI2CComponent(ComponentInstance self);
pascal ComponentResult ExitI2CComponent(Handle storage,ComponentInstance self);
pascal ComponentResult CanDoI2CSelector(short selector);
pascal ComponentResult GetI2CVersion(short *version);
pascal ComponentResult TargetComponent(Handle storage,ComponentInstance captureInstance);
unsigned char CudaI2C(unsigned char noBytes, unsigned char slaveAddr, unsigned char subAddr, unsigned char *data);

pascal ComponentResult	SendIIC(Handle storage, unsigned char noBytes, unsigned char slaveAddr, unsigned char subAddr, unsigned char data);
pascal ComponentResult	SendI2C(Handle storage, unsigned char noBytes, unsigned char slaveAddr, unsigned char subAddr, unsigned char *data);
pascal ComponentResult	ReceiveI2C(Handle storage, unsigned char noBytes, unsigned char slaveAddr, unsigned char subAddr, unsigned char *data);


extern EgretGlu();
/* Implementation Section */

#define realComponent
#ifdef realComponent
pascal ComponentResult main( ComponentParameters *params, Handle storage )
#else
pascal ComponentResult I2CComponent( ComponentParameters *params, Handle storage )
#endif
	{

	short	selector;
		
		selector = params->what;

		if (selector < 0) {
			switch (selector) {
				case kComponentOpenSelect : 
					return CallComponentFunction(params, (ComponentFunctionProcPtr)InitI2CComponent );
				case kComponentCloseSelect : 
					return  CallComponentFunctionWithStorage(storage, params, (ComponentFunctionProcPtr)ExitI2CComponent);
				case kComponentCanDoSelect : 
					return CallComponentFunction(params, (ComponentFunctionProcPtr)CanDoI2CSelector);
				case kComponentVersionSelect : 
					return CallComponentFunction(params, (ComponentFunctionProcPtr)GetI2CVersion);
				case kComponentTargetSelect : 
					return CallComponentFunctionWithStorage(storage, params, (ComponentFunctionProcPtr)TargetComponent);

			}
		}
		else {
			switch (selector) {
				case kI2CReadSelect : 
					return CallComponentFunctionWithStorage(storage, params, (ComponentFunctionProcPtr)tI2CRead);
				case kI2CWriteSelect : 
					return CallComponentFunctionWithStorage(storage, params, (ComponentFunctionProcPtr)tI2CWrite);
				case kI2CReadWithSubAddrSelect : 
					return CallComponentFunctionWithStorage(storage, params, (ComponentFunctionProcPtr)tI2CReadWithSubAddr);
				case kI2CWriteWithSubAddrSelect : 
					return CallComponentFunctionWithStorage(storage, params, (ComponentFunctionProcPtr)tI2CWriteWithSubAddr);
			}
		};
	}

pascal ComponentResult InitI2CComponent(ComponentInstance self) {
#pragma unused(self)
long		Inst_Count,A5Value;
short		ErrorNo;
Handle h,hs;
I2CGlobals	*g;
//long	refCon;
ComponentInstance	t,Search_Inst;
ComponentDescription i2cThing;
long			defType 	= 'i2c ';
long			defSubType 	= 'm3tv';
long			defManu 	= 'appl';

#ifdef _BreakTime_
	DebugStr("\pEntered InitI2CComponent ");
#endif

/* allocate some private storage and lock it down */
	h = NewHandle(sizeof(I2CGlobals));
	if(h==nil) return(MemError());
	MoveHHi(h);
	HLock(h);

/* Initialize these fields to someComponent for now */
	g = (I2CGlobals *)(*h);

	g->gSelf = self; /*Save instance of self (incase we want to call ourself)*/
	
	SetComponentInstanceStorage(self,h);

	Inst_Count = CountComponentInstances((Component)self);
	if(Inst_Count == 1)
		{
			/* Allocate storage for the Shadow Registers */
			hs = NewHandleSys(sizeof(I2CShadow));
			if(hs==nil) {
				ErrorNo = MemError();
				DisposeHandle(h);
				return(ErrorNo);
				}
			MoveHHi(hs);
			HLock(hs);
			g->gShadowHandle = hs;
			g->gShadowPtr = (I2CShadowPtr)*hs;
			SetComponentRefcon((Component)self, (long)hs); /*Set the refcon to the handle to the shadow registers */
		} else {
/*If there are already instances open, then we need to find the refcon from one that wasn't cloned */ 

		/* First find an i2c thing and open it */	  	
			i2cThing.componentType = defType;
			i2cThing.componentSubType = defSubType;
			i2cThing.componentManufacturer = defManu;
			i2cThing.componentFlags = 0x00L;
			i2cThing.componentFlagsMask = 0x00L;
	
			Search_Inst = 0x0L; /*Start by searching all */
			do	{
				(Component)t = FindNextComponent((Component)Search_Inst,&i2cThing);
				A5Value = GetComponentInstanceA5((ComponentInstance)t);
				Search_Inst = t;
				}
			while ((A5Value != 0) && (t!=0));
			/*Now suck down the RefCon (This is all for just incase we were cloned) */
			(long)(g->gShadowHandle) = GetComponentRefcon((Component)t);
			g->gShadowPtr = (I2CShadowPtr)*(g->gShadowHandle);
			
		}


	return (0);		
}

pascal ComponentResult ExitI2CComponent(Handle storage,ComponentInstance self ) {
long	Inst_Count;
I2CGlobals	*g;
#pragma unused(self)

#ifdef _BreakTime_
	DebugStr("\pEntered ExitI2CComponent ");
#endif
	g = (I2CGlobals *)(*storage);

	Inst_Count = CountComponentInstances((Component)self);
	if(Inst_Count == 1) DisposeHandle(g->gShadowHandle);
	
	
	DisposHandle(storage);
	
	
	return(0);
}

pascal ComponentResult CanDoI2CSelector(short selector) {
long error = 0;
	
	switch (selector)
		{
			case kComponentOpenSelect:
			case kComponentCloseSelect:
			case kComponentCanDoSelect:
			case kComponentVersionSelect:
			case kComponentTargetSelect:
			
			case kI2CReadSelect : 
			case kI2CWriteSelect : 
			case kI2CReadWithSubAddrSelect : 
			case kI2CWriteWithSubAddrSelect : 
				error = 1;
			
		}
		
	return (error);
}
pascal ComponentResult GetI2CVersion(short *version) {

	*version = 0;
	return (0);
}
pascal ComponentResult TargetComponent(Handle storage,ComponentInstance captureInstance) {
long			error = 0;
I2CGlobals		*g;
#ifdef _BreakTime_
	DebugStr("\pEntered I2C TargetComponent");
#endif

	g = (I2CGlobals *)(*storage);
	g->gSelf = captureInstance;
	
	return(error);
}

MakePString(short length, char *Source, char *Dest){
int		j;
	for (j=0; j<length; ++j) {
		Dest[j] = Source[j];	
		}
	return;
	}

pascal ComponentResult tI2CRead (Handle storage, unsigned short slaveAddr, short byteCount, unsigned char *dataBuf) {
long			error = 0;
I2CGlobals		*g;
unsigned char	*theBuffer;
short			trans,transfered;
unsigned char	myPString[257];

#ifdef _BreakTime_
	DebugStr("\pEntered tI2CRead ");
#endif

	g = (I2CGlobals *)(*storage);
//	myPString[0] = 1; /*Set length of p-string to 1*/


/* NOTE: This will only return a maximum of one byte */
//	error = ReceiveI2C(storage, 1, slaveAddr, 0, &myPString[0]);
//	*dataBuf = myPString[0];

/*First make a P-string to use for ReceiveI2C call with the first byte equal to the max. no. of bytes to receive */
//	if(byteCount==256) myPString[0] = 0; else myPString[0] = byteCount;

//	error = ReceiveI2C(storage, 1, slaveAddr, 0, &myPString[0]);
/* Now copy the data out of the p-string back to the dataBuf */
//	MakePString(byteCount,&myPString[1],dataBuf);



	theBuffer = dataBuf;
	transfered = byteCount;
	do {
		if(transfered >= 256) {
			myPString[0] = 0; /*transfer 256 bytes*/
			trans = 256;
			} 
		else {
			myPString[0] = transfered;
			trans = transfered;
			}

	transfered -= 256;
			
	error = ReceiveI2C(storage, 1, slaveAddr, 0, &myPString[0]);
	MakePString(trans, &myPString[1], theBuffer);
	theBuffer +=256;
 
	} while ((error==0) && (transfered>0)); /*Do until an error occurs or weve transferred all the data 256 bytes at a time*/


	
	return(error);
}

pascal ComponentResult tI2CWrite (Handle storage, unsigned short slaveAddr, short byteCount, unsigned char *dataBuf){
long			error = 0;
I2CGlobals		*g;
unsigned char	*theBuffer;
short			trans,transfered;
unsigned char	myPString[257];

#ifdef _BreakTime_
	DebugStr("\pEntered tI2CWrite ");
#endif

	g = (I2CGlobals *)(*storage);

	theBuffer = dataBuf;
	transfered = byteCount;
	do {
		if(transfered >= 256) {
			myPString[0] = 0; /*transfer 256 bytes*/
			trans = 256;
			} 
		else {
			myPString[0] = transfered;
			trans = transfered;
			}

	transfered -= 256;
			
	MakePString(trans, theBuffer, &myPString[1]);
	error = SendI2C(storage, 1, slaveAddr, 0, &myPString);
	theBuffer +=256;
 
	} while ((error==0) && (transfered>0)); /*Do until an error occurs or weve transferred all the data 256 bytes at a time*/
	
	return(error);
}
	
pascal ComponentResult tI2CReadWithSubAddr (Handle storage, unsigned short slaveAddr, unsigned short subAddr, short byteCount, unsigned char *dataBuf) {
long			error = 0;
I2CGlobals		*g;
unsigned char	*theBuffer;
short			trans,transfered;
unsigned short	XSubAddr;
unsigned char	myPString[257];

#ifdef _BreakTime_
	DebugStr("\pEntered tI2CReadWithSubAddr ");
#endif

	g = (I2CGlobals *)(*storage);

/*First make a P-string to use for ReceiveI2C call with the first byte equal to the max. no. of bytes to receive */
//	if(byteCount==256) myPString[0] = 0; else myPString[0] = byteCount;

//	error = ReceiveI2C(storage, 2, slaveAddr, subAddr, &myPString[0]);
/* Now copy the data out of the p-string back to the dataBuf */
//	MakePString(byteCount,&myPString[1],dataBuf);

	theBuffer = dataBuf;
	transfered = byteCount;
	XSubAddr = subAddr;
	do {
		if(transfered >= 256) {
			myPString[0] = 0; /*transfer 256 bytes*/
			trans = 256;
			} 
		else {
			myPString[0] = transfered;
			trans = transfered;
			}

	transfered -= 256;
			
	error = ReceiveI2C(storage, 2, slaveAddr, XSubAddr, &myPString[0]);
	MakePString(trans, &myPString[1], theBuffer);
	theBuffer +=256;
	XSubAddr +=256;
 
	} while ((error==0) && (transfered>0)); /*Do until an error occurs or weve transferred all the data 256 bytes at a time*/

	
	return(error);
}
	
pascal ComponentResult tI2CWriteWithSubAddr (Handle storage, unsigned short slaveAddr, unsigned short subAddr, short byteCount, unsigned char *dataBuf) {
long			error = 0;
I2CGlobals		*g;
unsigned char	*theBuffer;
short			trans,transfered;
unsigned short	XSubAddr;
unsigned char	myPString[257];

#ifdef _BreakTime_
	DebugStr("\pEntered tI2CWriteWithSubAddr ");
#endif

	g = (I2CGlobals *)(*storage);
	
	theBuffer = dataBuf;
	transfered = byteCount;
	XSubAddr = subAddr;
	do {
		if(transfered >= 256) {
			myPString[0] = 0; /*transfer 256 bytes*/
			trans = 256;
			} 
		else {
			myPString[0] = transfered;
			trans = transfered;
			}

	transfered -= 256;
			
	MakePString(trans, theBuffer, &myPString[1]);
	error = SendI2C(storage, 2, slaveAddr, XSubAddr, &myPString);
	theBuffer +=256;
	XSubAddr +=256;
 
	} while ((error==0) && (transfered>0)); /*Do until an error occurs or weve transferred all the data 256 bytes at a time*/
	
	return(error);
}







pascal ComponentResult	SendIIC(Handle storage, unsigned char noBytes, unsigned char slaveAddr, unsigned char subAddr, unsigned char data){
I2CGlobals		*g;
Str255		myPString;
long		error;
	g = (I2CGlobals *)(*storage);
	myPString[0] = 1;
	myPString[1] = data;

	error = SendI2C(storage, noBytes, slaveAddr, subAddr, &myPString);
	return(error);
	
}

pascal ComponentResult	SendI2C(Handle storage, unsigned char noBytes, unsigned char slaveAddr, unsigned char subAddr, unsigned char *data){
I2CGlobals			*g;
short			i,sub;
short		 	len;

	g = (I2CGlobals *)(*storage);
	

	CudaI2C(noBytes, slaveAddr, subAddr, data); /* Call cuda to actually send the data */ 

	len = data[0]; /*gets the length*/
	if (len == 0) len = 256;
	sub = subAddr;

/*Now shadow the value */
	if ((slaveAddr == kDMSD_Chip)&&(subAddr <= 0x18)) {
		for (i=1; i<len+1; ++i) {
			g->gShadowPtr->gDMSDRec[sub] = data[i];
			++sub;
			}
	} 
	if ((slaveAddr == kVDC_Chip) && (subAddr <= 0x10)) {
		for (i=1; i<len+1; ++i) {
			g->gShadowPtr->gVDCRec[sub] = data[i];
			++sub;
			}
	}
	return(0);

}
pascal ComponentResult	ReceiveI2C(Handle storage, unsigned char noBytes, unsigned char slaveAddr, unsigned char subAddr, unsigned char *data){
I2CGlobals		*g;
short			i,sub;
short		 	len;

	g = (I2CGlobals *)(*storage);
	
#ifdef _BreakTime_
	DebugStr("\pEntered ReceiveI2c Routine, LOOK OuTTTTTTTTT ;hc ");
#endif

	len = data[0]; /*gets the length*/
	if (len == 0) len = 256;
	sub = subAddr;

/*Now see if its one of our shadowed the value */
	if ((slaveAddr == kDMSD_Chip) && (noBytes ==2) && (subAddr <= 0x18)) {
		if(len>0x19) len = 0x19; 
		for (i=1; i<len+1; ++i) {
			data[i] = g->gShadowPtr->gDMSDRec[sub];
			++sub;
			}
		data[0]=len;
		return(0);
		}
		 
	if ((slaveAddr == kVDC_Chip) && (noBytes ==2) && (subAddr <= 0x0f)) {  
		if(len>0x10) len = 0x10; 
		for (i=1; i<len+1; ++i) {
			data[i] = g->gShadowPtr->gVDCRec[sub];
			++sub;
			}
		data[0]=len;
		return(0);
		}
		
	CudaI2C(noBytes,slaveAddr, subAddr, data); /* Receive i2c block */
	

	return(0);

}

//*****************************************************************************************
//	CudaI2C
//
//	Send Cmd to Cuda FW to begin to send/receive I2C Data to/from Slave
//*****************************************************************************************
//
unsigned char CudaI2C(unsigned char noBytes, unsigned char slaveAddr, unsigned char subAddr, unsigned char *data) 
{
	EgretPB			myCudaPB;		/* Cuda parameter block */


	myCudaPB.pbCmdType 	= pseudoPkt;			//	CmdType
	myCudaPB.pbCmd 		= 0x22;					//	Cmd -> Write IIC data (was WrIIc ddh)
	myCudaPB.pbParm.pbbyte[0] = slaveAddr;		//	Slave Addr -> IIC (send I2c if even, receive if odd)
	myCudaPB.pbParm.pbbyte[1] = subAddr;		//	Slave Reg -> IIC

	myCudaPB.pbParm.pbbyte[2] = 0;				//	Data -> IIC (was data ddh)
	myCudaPB.pbParm.pbbyte[3] = 0;				//	clr
	myCudaPB.pbByteCnt = noBytes;				//	Number of bytes to send
	myCudaPB.pbBufPtr = data;					// (Was zero, DDH)

/* Make sure these are all zero */
	myCudaPB.pbFlags = 0;
	myCudaPB.pbSpareFlags = 0;
	myCudaPB.pbResult = 0;
	myCudaPB.pbCompletion = 0;

/*	Debugger();*/
	EgretGlu(&myCudaPB);
// NOTE: data is now returned in the passed p-string area, not as a returned parameter. DDH
	return(myCudaPB.pbResult); /* return error if any*/
}
