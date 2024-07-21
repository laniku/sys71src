
/************************************************************

Created: Saturday, July 27, 1991 at 3:06 PM
 ENET.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1990-1991
  All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <3>	 8/14/91	JL		Fixed EParamMisc2; it had two EParamHeaders.
		 <2>	 7/30/91	JL		Updated Copyright. Changed #defines to enums. Restored comments.
									Reformatted structs to match database.

	To Do:
************************************************************/


#ifndef __ENET__
#define __ENET__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif


enum {

 ENetSetGeneral = 253,		/*Set "general" mode*/
 ENetGetInfo = 252,			/*Get info*/
 ENetRdCancel = 251,		/*Cancel read*/
 ENetRead = 250,			/*Read*/
 ENetWrite = 249,			/*Write*/
 ENetDetachPH = 248,		/*Detach protocol handler*/
 ENetAttachPH = 247,		/*Attach protocol handler*/
 ENetAddMulti = 246,		/*Add a multicast address*/
 ENetDelMulti = 245,		/*Delete a multicast address*/

 eLenErr = -92,				/*Length error ddpLenErr*/
 eMultiErr = -91			/*Multicast address error ddpSktErr*/


#define EAddrRType 'eadr'	/*Alternate address resource type*/
};

#define EParamHeader \
 QElem *qLink;				/*General EParams*/\
 short qType;				/*queue type*/\
 short ioTrap;				/*routine trap*/\
 Ptr ioCmdAddr;				/*routine address*/\
 ProcPtr ioCompletion;		/*completion routine*/\
 OSErr ioResult;			/*result code*/\
 StringPtr ioNamePtr;		/*->filename*/\
 short ioVRefNum;			/*volume reference or drive number*/\
 short ioRefNum;			/*driver reference number*/\
 short csCode;				/*Call command code*/


struct EParamMisc1 {
 EParamHeader 				/*General EParams*/
 short eProtType;			/*Ethernet protocol type*/
 Ptr ePointer;
 short eBuffSize;			/*buffer size*/
 short eDataSize;			/*number of bytes read*/
};

typedef struct EParamMisc1 EParamMisc1;

struct EParamMisc2 {
 EParamMisc1 EParms1;
 char eMultiAddr[6];		/*Multicast Address*/
};

typedef struct EParamMisc2 EParamMisc2;

union EParamBlock {
 EParamMisc1 EParms1;
 EParamMisc2 EParms2;
};

typedef union EParamBlock EParamBlock;
typedef EParamBlock *EParamBlkPtr;


#ifdef __cplusplus
extern "C" {
#endif
pascal OSErr EWrite(EParamBlkPtr thePBptr,Boolean async); 
pascal OSErr EAttachPH(EParamBlkPtr thePBptr,Boolean async); 
pascal OSErr EDetachPH(EParamBlkPtr thePBptr,Boolean async); 
pascal OSErr ERead(EParamBlkPtr thePBptr,Boolean async); 
pascal OSErr ERdCancel(EParamBlkPtr thePBptr,Boolean async); 
pascal OSErr EGetInfo(EParamBlkPtr thePBptr,Boolean async); 
pascal OSErr ESetGeneral(EParamBlkPtr thePBptr,Boolean async); 
pascal OSErr EAddMulti(EParamBlkPtr thePBptr,Boolean async); 
pascal OSErr EDelMulti(EParamBlkPtr thePBptr,Boolean async); 
#ifdef __cplusplus
}
#endif

#endif
