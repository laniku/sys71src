
/************************************************************

Created: Sunday, January 6, 1991 at 9:38 PM
    PPCToolBox.h
    C Interface to the Macintosh Libraries


        Copyright Apple Computer, Inc.    1989-1992
        All rights reserved

	Change History (most recent first):

		<35>	 6/26/92	DCL		Get Rid of constant ppcStoreAndForward. Miner Formatting
									Changes. Digging deep for things to do. Getting the file ready
									for ETO 8.
		<34>	 4/17/92	JSM		Don’t define gestaltPPCSupportsStoreAndForward or
									gestaltPPCVersionAttr.
		<33>	 4/15/92	JSM		Get rid of all the theFuture and CubeE conditionals, the future
									is the same as CubeE for now.
		<32>	 10/4/91	JSM		Change PsychoticFarmerOrLater conditionals to TheFuture.
		<31>	 9/29/91	DTY		For CubeE, add conditional use of resFlag instead of
									noAuthRequired.
		<30>	 7/24/91	JL		Fixed the build. PPCOpenPBRec's field noAuthRequired was
									resFlag.
		<29>	 7/24/91	JL		Updated Copyright. Restored comments.
		<28>	  6/4/91	EMT		Roll in StoreAndForward Revisions
		<27>	 1/30/91	JL		Checked in database generated file from DSG.
		<25>	 11/8/90	EMT		<stb>Get rid of loginCancelErr and use userCancelledErr
		<24>	 11/4/90	dba		got rid of some extraneous parameter names; changed some
									parameters from StringPtr to various string types; used
									constStr255Parameter and constStr32Parameter
		<23>	 11/1/90	DFH		Fixed PPCInit inline to have #pragma parameter __D0.
		<22>	10/24/90	EMT		Remove useless error codes, and add noUserNameErr.
		<21>	10/21/90	gbm		(with dba) Made compatible with 3.2 C compiler (and incompatible
									with previous compilers).
		<21>	10/10/90	JAL		New style #Pragma Parameters for MPW 3.2 C. Added Sync and Async calls.
		<20>	 9/25/90	EMT		Fix bug in StartSecureSession prototype.
		<19>	 9/18/90	EMT		Change noUserNameErr to the more appropriate noMachineNameErr
									nomenclature.
		<18>	 9/15/90	ngk		Change to new, way-cool constants and field names
	   								#### warning this was a major change ####
		<17>	 9/15/90	EMT		Flip bytes in PortInfo structure, required to maintain
	   								compatiblity with older versions on the same network.
		<16>	 9/15/90	EMT		oops, remove the reserved field (for now).
		<15>	 9/15/90	EMT		Add reserved field to LocName to make it big enough for future
									systems.
		<14>	 9/14/90	EMT		Change field location, and support opening with type only
		<13>	 9/14/90	JSM		Add theLocNBPType parameter to PPCBrowser().
		<12>	 3/20/90	S		No Change. Changed Some Comments.
		<11>	 3/20/90	S		To Include a reserved field and also include a new field called
									requestType in PPCInform Call.
		<10>	 3/19/90	JSM		PPCBrowser now returns PortInfo instead of PortName.
		 <8>	 2/27/90	S		To Remove authRequest from PPCOpen Call &  include
									guestNotAllowedErr.
		 <7>	 2/19/90	JSM		Add PPCBrowser interface.
		 <6>	 1/30/90	S		Added some Error Codes.
		 <5>	 1/23/90	S		Change New style comments to old style comments for LightSpeed C
									Compatiblity.
		 <4>	  1/9/90	S		Removed some Commented Definitions
	   <1.1>	11/28/89	CVC		Added the StartSecureSession call.
	   <1.0>	 11/1/89	CVC		First add the file to CInclude folder.

	   Old Revision History:

		07/25/89	Sangam 	Added portClosedErr and sessClosedErr codes
		08/10/89	Sangam	Made Changes to IPCListPorts call
		08/10/89    Sangam  Changed error code values (Now they are alloted to PPCToolBox !!)
		08/10/89	Sangam	userEntry filed in PPCRead and PPCWrite calls (RefCon for Multifinder)
		09/18/89    Sangam  Changed to new definition of PortName, Support for User Authentication
							browse by portType (Interface changes to PPCOpen PPCStart, PPCInform
							PPCWrite (to suppor 'more' flag) and IPCListPorts).
		09/28/89    Sangam  Added C++ compatible definitions
		10/09/89	Sangam  Changed constants for lookupType and portTypes,
							changed nameType in LocName structure to short.
		1/4/90      Sangam  Removed Pad byte in the PortName Type Definition
		1/5/90      Sangam  Changed the heade structre such that cmdCompletion and cmdResult
							to align with similar filed in driver. Some changes to error codes.(Capitalization)

************************************************************/


#ifndef __PPCTOOLBOX__
#define __PPCTOOLBOX__

#ifndef __APPLETALK__
#include <AppleTalk.h>
#endif

#ifndef __MEMORY__
#include <Memory.h>
#endif

#ifndef __TYPES__
#include <Types.h>
#endif

typedef unsigned char PPCServiceType;

enum {

    ppcServiceRealTime = 1
};

typedef short PPCLocationKind;

enum {

    ppcNoLocation = 0,                          /* There is no PPCLocName */
    ppcNBPLocation = 1,                         /* Use AppleTalk NBP      */
    ppcNBPTypeLocation = 2                      /* Used for specifying a location name type during PPCOpen only */
};

typedef short PPCPortKinds;

enum {

 ppcByCreatorAndType = 1,					/* Port type is specified as colloquial Mac creator and type */
 ppcByString = 2							/* Port type is in pascal string format */
};

typedef unsigned char PPCSessionOrigin;         /* Values returned for request field in PPCInform call */

enum {


/* Values returned for requestType field in PPCInform call */
    ppcLocalOrigin = 1,                         /* session originated from this machine */
    ppcRemoteOrigin = 2                         /* session originated from remote machine */
};

typedef short PPCPortRefNum;
typedef long PPCSessRefNum;

struct PPCPortRec {
    ScriptCode nameScript;                      /* script of name */
    Str32 name;                                 /* name of port as seen in browser */
    PPCPortKinds portKindSelector;              /* which variant */
    union {
        Str32 portTypeStr;                      /* pascal type string */
        struct {
            OSType creator;
            OSType type;
            } port;
        } u;
};

typedef struct PPCPortRec PPCPortRec;
typedef PPCPortRec *PPCPortPtr;

struct LocationNameRec {
    PPCLocationKind locationKindSelector;       /* which variant */
    union {
        EntityName nbpEntity;                   /* NBP name entity */
        Str32 nbpType;                          /* just the NBP type string, for PPCOpen */
        } u;
};

typedef struct LocationNameRec LocationNameRec;
typedef LocationNameRec *LocationNamePtr;

struct PortInfoRec {
    unsigned char filler1;
    Boolean authRequired;
    PPCPortRec name;
};

typedef struct PortInfoRec PortInfoRec;
typedef PortInfoRec *PortInfoPtr;


typedef PortInfoRec *PortInfoArrayPtr;
typedef pascal Boolean (*PPCFilterProcPtr)(LocationNamePtr, PortInfoPtr);
/* Procedures you will need to write */
/* ex:  void    MyCompletionRoutine(PPCParamBlkPtr pb) */
/* ex:  pascal Boolean MyPortFilter(LocationNamePtr, PortInfoPtr) */
typedef ProcPtr PPCCompProcPtr;


#define PPCHeader \
     Ptr    		qLink;   				/* PPC's Internal Use */\
     unsigned short csCode;   				/* Requested PPC command */\
     unsigned short intUse;   				/* Internal Use */\
     Ptr    		intUsePtr;  			/* Internal Use */\
											/* 12 --> */\
	 PPCCompProcPtr ioCompletion; 			/* Completion Routine */\
											/* 16 <-- */\
	 OSErr   		ioResult;  				/* Command Result Code */\
     unsigned long	Reserved[5]; 			/* Reserved for PPC, Don't use */

struct PPCOpenPBRec {
 PPCHeader 
 PPCPortRefNum portRefNum;					/* 38 <--   Port Reference */
 long filler1;
 PPCServiceType serviceType;				/* 44 -->    Bit field describing the requested port service */
 unsigned char resFlag;                     /* Must be set to 0 */
 PPCPortPtr portName;						/* 46 -->   PortName for PPC */
 LocationNamePtr locationName;				/* 50 -->   If NBP Registration is required */
 Boolean networkVisible;					/* 54 -->   make this network visible on network */
 Boolean nbpRegistered;						/* 55 <--   The given location name was registered on the network */
};

typedef struct PPCOpenPBRec PPCOpenPBRec;
typedef PPCOpenPBRec *PPCOpenPBPtr;

struct PPCInformPBRec {
 PPCHeader
 PPCPortRefNum portRefNum;					/* 38 -->   Port Identifier */
 PPCSessRefNum sessRefNum;					/* 40 <--   Session Reference */
 PPCServiceType serviceType;				/* 44 <--   Status Flags for type of session, local, remote */
 Boolean autoAccept;						/* 45 -->   if true session will be accepted automatically */
 PPCPortPtr portName;						/* 46 -->   Buffer for Source PPCPortRec */
 LocationNamePtr locationName;				/* 50 -->   Buffer for Source LocationNameRec */
 StringPtr userName;						/* 54 -->   Buffer for Soure user's name trying to link. */
 unsigned long userData;					/* 58 <--   value included in PPCStart's userData */
 PPCSessionOrigin requestType;				/* 62 <--   Local or Network */
};

typedef struct PPCInformPBRec PPCInformPBRec;
typedef PPCInformPBRec *PPCInformPBPtr;

struct PPCStartPBRec {
 PPCHeader
 PPCPortRefNum portRefNum;					/* 38 -->   Port Identifier */
 PPCSessRefNum sessRefNum;					/* 40 <--   Session Reference */
 PPCServiceType serviceType;				/* 44 <--   Actual service method (realTime) */
 unsigned char resFlag;						/* 45 -->   Must be set to 0  */
 PPCPortPtr portName;						/* 46 -->   Destination portName */
 LocationNamePtr locationName;				/* 50 -->   NBP or NAS style service location name */
 unsigned long rejectInfo;					/* 54 <--   reason for rejecting the session request */
 unsigned long userData;					/* 58 -->   Copied to destination PPCInform parameter block */
 unsigned long userRefNum;					/* 62 -->   userRefNum (obtained during login process)  */
};

typedef struct PPCStartPBRec PPCStartPBRec;
typedef PPCStartPBRec *PPCStartPBPtr;

struct PPCAcceptPBRec {
 PPCHeader
 short filler1;
 PPCSessRefNum sessRefNum;					/* 40 -->   Session Reference */
};

typedef struct PPCAcceptPBRec PPCAcceptPBRec;
typedef PPCAcceptPBRec *PPCAcceptPBPtr;

struct PPCRejectPBRec {
 PPCHeader
 short filler1;
 PPCSessRefNum sessRefNum;					/* 40 -->   Session Reference */
 short filler2;
 long filler3;
 long filler4;
 unsigned long rejectInfo;					/* 54 -->   reason for rejecting the session request  */
};

typedef struct PPCRejectPBRec PPCRejectPBRec;
typedef PPCRejectPBRec *PPCRejectPBPtr;

struct PPCWritePBRec {
 PPCHeader
 short filler1;
 PPCSessRefNum sessRefNum;					/* 40 -->   Session Reference */
 Size bufferLength;							/* 44 -->   Length of the message buffer */
 Size actualLength;							/* 48 <--   Actual Length Written */
 Ptr bufferPtr;								/* 52 -->   Pointer to message buffer */
 Boolean more;								/* 56 -->   if more data in this block will be written */
 unsigned char filler2;
 unsigned long userData;					/* 58 -->   Message block userData Uninterpreted by PPC */
 OSType blockCreator;						/* 62 -->   Message block creator Uninterpreted by PPC */
 OSType blockType;							/* 66 -->   Message block type Uninterpreted by PPC */
};

typedef struct PPCWritePBRec PPCWritePBRec;
typedef PPCWritePBRec *PPCWritePBPtr;

struct PPCReadPBRec {
 PPCHeader
 short filler1;
 PPCSessRefNum sessRefNum;					/* 40 -->   Session Reference */
 Size bufferLength;							/* 44 -->   Length of the message buffer */
 Size actualLength;							/* 48 <--   Actual length read */
 Ptr bufferPtr;								/* 52 -->   Pointer to message buffer */
 Boolean more;								/* 56 <--   if true more data in this block to be read */
 unsigned char filler2;
 unsigned long userData;					/* 58 <--   Message block userData Uninterpreted by PPC */
 OSType blockCreator;						/* 62 <--   Message block creator Uninterpreted by PPC */
 OSType blockType;							/* 66 <--   Message block type Uninterpreted by PPC */
};

typedef struct PPCReadPBRec PPCReadPBRec;
typedef PPCReadPBRec *PPCReadPBPtr;

struct PPCEndPBRec {
 PPCHeader
    short filler1;
 PPCSessRefNum sessRefNum;					/* 40 -->   Session Reference */
};

typedef struct PPCEndPBRec PPCEndPBRec;
typedef PPCEndPBRec *PPCEndPBPtr;

struct PPCClosePBRec {
 PPCHeader
 PPCPortRefNum portRefNum;					/* 38 -->   Port Identifier */
};

typedef struct PPCClosePBRec PPCClosePBRec;
typedef PPCClosePBRec *PPCClosePBPtr;

struct IPCListPortsPBRec {
 PPCHeader
 short filler1;
 unsigned short startIndex;					/* 40 -->   Start Index */
 unsigned short requestCount;				/* 42 -->   Number of entries to be returned */
 unsigned short actualCount;				/* 44 <--   Actual Number of entries to be returned */
 PPCPortPtr portName;						/* 46 -->   PortName Match */
 LocationNamePtr locationName;				/* 50 -->   NBP or NAS type name to locate the Port Location */
 PortInfoArrayPtr bufferPtr;				/* 54 -->   Pointer to a buffer requestCount*sizeof(PortInfo) bytes big */
};

typedef struct IPCListPortsPBRec IPCListPortsPBRec;
typedef IPCListPortsPBRec *IPCListPortsPBPtr;

union PPCParamBlockRec {
        PPCOpenPBRec        openParam;
        PPCInformPBRec           informParam;
        PPCStartPBRec        startParam;
        PPCAcceptPBRec         acceptParam;
        PPCRejectPBRec         rejectParam;
        PPCWritePBRec        writeParam;
        PPCReadPBRec        readParam;
        PPCEndPBRec              endParam;
        PPCClosePBRec        closeParam;
        IPCListPortsPBRec    listPortsParam;
};

typedef union PPCParamBlockRec PPCParamBlockRec;
typedef  PPCParamBlockRec  *PPCParamBlockPtr;


#ifdef __cplusplus
extern "C" {
#endif
/*  PPC Calling Conventions  */
#pragma parameter __D0 PPCInit
pascal OSErr PPCInit(void)
    = {0x7000,0xA0DD}; 
pascal OSErr PPCOpen(PPCOpenPBPtr pb,Boolean async); 
#pragma parameter __D0 PPCOpenSync(__A0)
pascal OSErr PPCOpenSync(PPCOpenPBPtr pb)
    = {0x7001,0xA0DD}; 
#pragma parameter __D0 PPCOpenAsync(__A0)
pascal OSErr PPCOpenAsync(PPCOpenPBPtr pb)
    = {0x7001,0xA4DD}; 
pascal OSErr PPCInform(PPCInformPBPtr pb,Boolean async); 
#pragma parameter __D0 PPCInformSync(__A0)
pascal OSErr PPCInformSync(PPCInformPBPtr pb)
    = {0x7003,0xA0DD}; 
#pragma parameter __D0 PPCInformAsync(__A0)
pascal OSErr PPCInformAsync(PPCInformPBPtr pb)
    = {0x7003,0xA4DD}; 
pascal OSErr PPCStart(PPCStartPBPtr pb,Boolean async); 
#pragma parameter __D0 PPCStartSync(__A0)
pascal OSErr PPCStartSync(PPCStartPBPtr pb)
    = {0x7002,0xA0DD}; 
#pragma parameter __D0 PPCStartAsync(__A0)
pascal OSErr PPCStartAsync(PPCStartPBPtr pb)
    = {0x7002,0xA4DD}; 
pascal OSErr PPCAccept(PPCAcceptPBPtr pb,Boolean async); 
#pragma parameter __D0 PPCAcceptSync(__A0)
pascal OSErr PPCAcceptSync(PPCAcceptPBPtr pb)
    = {0x7004,0xA0DD}; 
#pragma parameter __D0 PPCAcceptAsync(__A0)
pascal OSErr PPCAcceptAsync(PPCAcceptPBPtr pb)
    = {0x7004,0xA4DD}; 
pascal OSErr PPCReject(PPCRejectPBPtr pb,Boolean async); 
#pragma parameter __D0 PPCRejectSync(__A0)
pascal OSErr PPCRejectSync(PPCRejectPBPtr pb)
    = {0x7005,0xA0DD}; 
#pragma parameter __D0 PPCRejectAsync(__A0)
pascal OSErr PPCRejectAsync(PPCRejectPBPtr pb)
    = {0x7005,0xA4DD}; 
pascal OSErr PPCWrite(PPCWritePBPtr pb,Boolean async); 
#pragma parameter __D0 PPCWriteSync(__A0)
pascal OSErr PPCWriteSync(PPCWritePBPtr pb)
    = {0x7006,0xA0DD}; 
#pragma parameter __D0 PPCWriteAsync(__A0)
pascal OSErr PPCWriteAsync(PPCWritePBPtr pb)
    = {0x7006,0xA4DD}; 
pascal OSErr PPCRead(PPCReadPBPtr pb,Boolean async); 
#pragma parameter __D0 PPCReadSync(__A0)
pascal OSErr PPCReadSync(PPCReadPBPtr pb)
    = {0x7007,0xA0DD}; 
#pragma parameter __D0 PPCReadAsync(__A0)
pascal OSErr PPCReadAsync(PPCReadPBPtr pb)
    = {0x7007,0xA4DD}; 
pascal OSErr PPCEnd(PPCEndPBPtr pb,Boolean async); 
#pragma parameter __D0 PPCEndSync(__A0)
pascal OSErr PPCEndSync(PPCEndPBPtr pb)
    = {0x7008,0xA0DD}; 
#pragma parameter __D0 PPCEndAsync(__A0)
pascal OSErr PPCEndAsync(PPCEndPBPtr pb)
    = {0x7008,0xA4DD}; 
pascal OSErr PPCClose(PPCClosePBPtr pb,Boolean async); 
#pragma parameter __D0 PPCCloseSync(__A0)
pascal OSErr PPCCloseSync(PPCClosePBPtr pb)
    = {0x7009,0xA0DD}; 
#pragma parameter __D0 PPCCloseAsync(__A0)
pascal OSErr PPCCloseAsync(PPCClosePBPtr pb)
    = {0x7009,0xA4DD}; 
pascal OSErr IPCListPorts(IPCListPortsPBPtr pb,Boolean async); 
#pragma parameter __D0 IPCListPortsSync(__A0)
pascal OSErr IPCListPortsSync(IPCListPortsPBPtr pb)
    = {0x700A,0xA0DD}; 
#pragma parameter __D0 IPCListPortsAsync(__A0)
pascal OSErr IPCListPortsAsync(IPCListPortsPBPtr pb)
    = {0x700A,0xA4DD}; 

pascal OSErr DeleteUserIdentity(unsigned long userRef); 
pascal OSErr GetDefaultUser(unsigned long *userRef,
                            Str32 userName); 
pascal OSErr StartSecureSession(PPCStartPBPtr pb,
                                Str32 userName,
                                Boolean useDefault,
                                Boolean allowGuest,
                                Boolean *guestSelected,
                                ConstStr255Param prompt); 
pascal OSErr PPCBrowser(ConstStr255Param prompt,
                        ConstStr255Param applListLabel,
                        Boolean defaultSpecified,
                        LocationNameRec *theLocation,
                        PortInfoRec *thePortInfo,
                        PPCFilterProcPtr portFilter,
                        ConstStr32Param theLocNBPType)
    = {0x303C,0x0D00,0xA82B}; 
#ifdef __cplusplus
}
#endif

#endif
