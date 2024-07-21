
/************************************************************

Created: Saturday, July 27, 1991 at 2:09 PM
 AppleEvents.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1989-1991
  All rights reserved
 
	This file is used in these builds: BigBang

	Change History (most recent first):

	   <SM2>	 8/26/93	IH		Added types for fixed and rect (used by Display Manager events).
		<18>	 7/30/91	JL		Updated Copyright.
		<17>	 6/14/91	JL		Checked in official MPW 3.2д version. Lined up parameter lists
									vertically to match pascal file. Adjusted comment formats to
									match Pascal file. Temporarily lost updated copyright date but
									this will be resolved later.
		<16>	  2/5/91	stb		eeh: add const ий* for non-VAR record parameters
		<15>	  2/1/91	DFH		stb,WS#DFH-910131c:Moved and renamed Process Mgr defined
									AppleEvent codes to this file. Put old names in
									AppleEventsInternal.h since we don't want to break any compiles
									at this point.
		<14>	 1/30/91	JL		Changed #defines to enums
		<13>	 1/25/91	stb		JDR: harmonize with AppleEvents.p
		<12>	 10/2/90	Lai		Matches AppleEvents.p.
		<11>	DFH	16 Apr 90		Changed saeOpenDocumentMsgID to 'odoc', saePrintDocumentMsgID
									to 'pdoc'.  Added saeLaunchedWithoutDocs, saeAnswer,
									aeErrorValueKeyword, and AppleEventReply.
		<10>	ngk 4/2/90			Renamed class field in HighLevelEventRecord
		 <9>	DFH	23 Mar 90		Corrected the majorVersion to be a short, as per ERS.
		 <8>	ngk	3/22/90			Changed AETFDescriptor AETFParameter in regular expr.
		 <7>	ngk	3/20/90			Change to new 7.0a8 format for message buffers. Removed
									constants and structs for non-standard appleevents
		 <6>	DFH	12 Mar 90		Added AppleEventMessage
		 <5>	DFH	12 Mar 90		Removed aeDebuggerNotify
		1.1		ngk 12/01/1989		Renamed aeUnexpectedQuit to aeApplicationDied, and
									refcon to amsRefCon
		1.0		ngk 11/01/1989		initial EASE release

	To Do:

************************************************************/


#ifndef __APPLEEVENTS__
#define __APPLEEVENTS__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __MEMORY__
#include <Memory.h>
#endif

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif

#ifndef __EVENTS__
#include <Events.h>
#endif

#ifndef __EPPC__
#include <EPPC.h>
#endif

#ifndef __NOTIFICATION__
#include <Notification.h>
#endif


enum {


#define typeBoolean 'bool'
#define typeChar 'TEXT'
#define typeSMInt 'shor'
#define typeInteger 'long'
#define typeSMFloat 'sing'
#define typeFloat 'doub'
#define typeLongInteger 'long'
#define typeShortInteger 'shor'
#define typeLongFloat 'doub'
#define typeShortFloat 'sing'
#define typeExtended 'exte'
#define typeComp 'comp'
#define typeMagnitude 'magn'
#define typeAEList 'list'
#define typeAERecord 'reco'
#define typeTrue 'true'
#define typeFalse 'fals'
#define typeAlias 'alis'
#define typeEnumerated 'enum'
#define typeType 'type'
#define typeAppParameters 'appa'
#define typeProperty 'prop'
#define typeFSS 'fss '
#define typeKeyword 'keyw'
#define typeSectionH 'sect'
#define typeWildCard '****'

// Imported from Apple Event CD
#define typeQDRectangle 'qdrt'
#define typeFixed 'fixd'

#define typeApplSignature 'sign'
#define typeSessionID 'ssid'
#define typeTargetID 'targ'
#define typeProcessSerialNumber 'psn '
#define typeNull 'null'					/*the type of null/nonexistent data*/

#define kCoreEventClass 'aevt'

#define kAEOpenApplication 'oapp'
#define kAEOpenDocuments 'odoc'
#define kAEPrintDocuments 'pdoc'
#define kAEQuitApplication 'quit'

#define kAECreatorType 'crea'
#define kAEQuitAll 'quia'
#define kAEShutDown 'shut'
#define kAERestart 'rest'
#define kAEApplicationDied 'obit'
#define keyProcessSerialNumber 'psn '

#define keyErrorNumber 'errn'
#define keyErrorString 'errs'

#define kAEAnswer 'ansr'

#define keyDirectObject '----'


/* keyword used in install special handler */
#define keyPreDispatch 'phac'			/* PreHandler Accessor Call */
#define keySelectProc 'selh'			/* More selector Call */

/* keywords used in attributes */
#define keyTransactionIDAttr 'tran'
#define keyReturnIDAttr 'rtid'
#define keyEventClassAttr 'evcl'
#define keyEventIDAttr 'evid'
#define keyAddressAttr 'addr'
#define keyOptionalKeywordAttr 'optk'
#define keyTimeoutAttr 'timo'
#define keyInteractLevelAttr 'inte'		/*this attribute is read only will be set in AESend*/
#define keyEventSourceAttr 'esrc'		/* this attribute is read only */
#define keyMissedKeywordAttr 'miss'		/* this attribute is read only */

/* constants for use in AESendMode */

 kAENoReply = 0x00000001,				/* Sender doesn't want a reply to event */
 kAEQueueReply = 0x00000002,			/* Sender wants a reply but won't wait */
 kAEWaitReply = 0x00000003,				/* Sender wants a reply and will be waiting */

 kAENeverInteract = 0x00000010,			/* Server should not interact with user */
 kAECanInteract = 0x00000020,			/* Server may try to interact with user */
 kAEAlwaysInteract = 0x00000030,		/* Server should always interact with user where appropriate */

 kAECanSwitchLayer = 0x00000040,		/* Interaction may switch layer */

 kAEDontReconnect = 0x00000080,			/* don't reconnect if there is a sessClosedErr from PPCToolbox */


#define kAEWantReceipt nReturnReceipt	/* Send wants a receipt of message */

/* constants to be used in AESendPriority */

 kAENormalPriority = 0x00000000,		/* Post message at the end of event queue */

#define kAEHighPriority nAttnMsg		/* Post message at the front of the event queue */

/* special constants in generating events */

 kAnyTransactionID = 0,					/* no transaction is in use */
 kAutoGenerateReturnID = -1,			/* AECreateAppleEvent will generate a session-unique ID */

/* constant for use AESend */
 kAEDefaultTimeout = -1,				/* timeout value determined by AEM */
 kNoTimeOut = -2,						/* wait until reply comes back, however long it takes */

/* dispatch parameter to AEResumeTheCurrentEvent takes a pointer to a dispatch
table, or one of these two constants */
 kAENoDispatch = 0,
 kAEUseStandardDispatch = -1,

/* Error messages in response to reading and writing event contents */
 errAECoercionFail = -1700,
 errAEDescNotFound = -1701,
 errAECorruptData = -1702,
 errAEWrongDataType = -1703,
 errAENotAEDesc = -1704
};
enum {
 errAEBadListItem = -1705,				/* Specified list item does not exist */
 errAENewerVersion = -1706,				/* Need newer version of AppleEvent Manager */
 errAENotAppleEvent = -1707,			/* The event is not in AppleEvent format */

/* Error messages in response to sending/receiving a message */
 errAEEventNotHandled = -1708,			/* The AppleEvent was not handled by any handler */
 errAEReplyNotValid = -1709,			/* AEResetTimer was passed an invalid reply parameter */
 errAEUnknownSendMode = -1710,			/* Mode wasn't NoReply, WaitReply, or QueueReply;  or Interaction level is unknown */
 errAEWaitCanceled = -1711,				/* In AESend, User cancelled out of wait loop for  reply or receipt */
 errAETimeout = -1712,					/* AppleEvent timed out */

 errAENoUserInteraction = -1713,		/* no user interaction allowed */
 errAENotASpecialFunction = -1714,		/* there is no special function with this keyword */
 errAEParamMissed = -1715,				/* a required parameter was not accessed */

 errAEUnknownAddressType = -1716,		/* The target address type is not known */
 errAEHandlerNotFound = -1717,			/* No handler in the dispatch tables fits the parameters to
             AEGetEventHandler or AEGetCoercionHandler */

 errAEReplyNotArrived = -1718,			/* the contents of the reply you are accessing have not arrived yet */
 errAEIllegalIndex = -1719				/* Index is out of range in a put operation */
};

typedef unsigned long AEKeyword;
typedef unsigned long AEEventClass;
typedef unsigned long AEEventID;
typedef ResType DescType;

/* tagged data, the standard AppleEvent data type */
struct AEDesc {
 DescType descriptorType;
 Handle dataHandle;
};

typedef struct AEDesc AEDesc;


typedef AEDesc AEAddressDesc;			/* an AEDesc which contains addressing data */
typedef AEDesc AEDescList;				/* a list of AEDesc is a special kind of AEDesc */
typedef AEDescList AERecord;			/* AERecord is a list of keyworded AEDesc */
typedef AERecord AppleEvent;			/* an AERecord that contains an AppleEvent */
typedef long AESendMode;				/* Type of parameter to AESend */
typedef short AESendPriority;			/* Type of priority param of AESend */

enum {kAEInteractWithSelf,kAEInteractWithLocal,kAEInteractWithAll};
typedef unsigned char AEInteractAllowed;

enum {kAEUnknownSource,kAEDirectCall,kAESameProcess,kAELocalProcess,kAERemoteProcess};
typedef unsigned char AEEventSource;


/* types for AppleEvent Array support 

 Basic data type of attibutes & parameters*/
struct AEKeyDesc {
 AEKeyword descKey;
 AEDesc descContent;
};

typedef struct AEKeyDesc AEKeyDesc;


enum {kAEDataArray,kAEPackedArray,kAEHandleArray,kAEDescArray,kAEKeyDescArray};
typedef unsigned char AEArrayType;


/* Array routines support these different types of elements*/
union AEArrayData {
 short AEDataArray[1];
 char AEPackedArray[1];
 Handle AEHandleArray[1];
 AEDesc AEDescArray[1];
 AEKeyDesc AEKeyDescArray[1];
};

typedef union AEArrayData AEArrayData;
typedef AEArrayData *AEArrayDataPointer;



typedef ProcPtr EventHandlerProcPtr;
typedef ProcPtr IdleProcPtr;
typedef ProcPtr EventFilterProcPtr;

#ifdef __cplusplus
extern "C" {
#endif

/* 
   *********************************************************************
 The following calls apply to any AEDesc. Every result descriptor is created for you,
 so you will be responsible for memory management of the descriptors so created.
 Purgeable descriptor data is not supported: the AEM does not call LoadResource.  
*/

pascal OSErr AECreateDesc(DescType typeCode,
                          Ptr dataPtr,
                          Size dataSize,
                          AEDesc *result)
 = {0x303C,0x0825,0xA816}; 
pascal OSErr AECoercePtr(DescType typeCode,
                         Ptr dataPtr,
                         Size dataSize,
                         DescType toType,
                         AEDesc *result)
 = {0x303C,0x0A02,0xA816}; 
pascal OSErr AECoerceDesc(const AEDesc *theAEDesc,
                          DescType toType,
                          AEDesc *result)
 = {0x303C,0x0603,0xA816}; 
pascal OSErr AEDisposeDesc(AEDesc *theAEDesc)
 = {0x303C,0x0204,0xA816}; 
pascal OSErr AEDuplicateDesc(const AEDesc *theAEDesc,AEDesc *result)
 = {0x303C,0x0405,0xA816}; 

/* 
 *********************************************************************
  The following calls apply to AEDescList.
   Since AEDescList is a subtype of AEDesc, the calls in the previous
   section can also be used for AEDescList. All list and array indices are 1-based.
   If the data was greater than maximumSize in the routines below, then actualSize will
   be greater than maximumSize, but only maximumSize bytes will actually be retrieved.
*/

pascal OSErr AECreateList(Ptr factoringPtr,
                          Size factoredSize,
                          Boolean isRecord,
                          AEDescList *resultList)
 = {0x303C,0x0706,0xA816}; 
pascal OSErr AECountItems(const AEDescList *theAEDescList,
                          long *theCount)
 = {0x303C,0x0407,0xA816}; 
pascal OSErr AEPutPtr(const AEDescList *theAEDescList,
                      long index,
                      DescType typeCode,
                      Ptr dataPtr,
                      Size dataSize)
 = {0x303C,0x0A08,0xA816}; 
pascal OSErr AEPutDesc(const AEDescList *theAEDescList,
                       long index,
                       const AEDesc *theAEDesc)
 = {0x303C,0x0609,0xA816}; 
pascal OSErr AEGetNthPtr(const AEDescList *theAEDescList,
                         long index,
                         DescType desiredType,
                         AEKeyword *theAEKeyword,
                         DescType *typeCode,
                         Ptr dataPtr,
                         Size maximumSize,
                         Size *actualSize)
 = {0x303C,0x100A,0xA816}; 
pascal OSErr AEGetNthDesc(const AEDescList *theAEDescList,
                          long index,
                          DescType desiredType,
                          AEKeyword *theAEKeyword,
                          AEDesc *result)
 = {0x303C,0x0A0B,0xA816}; 
pascal OSErr AESizeOfNthItem(const AEDescList *theAEDescList,
                             long index,
                             DescType *typeCode,
                             Size *dataSize)
 = {0x303C,0x082A,0xA816}; 
pascal OSErr AEGetArray(const AEDescList *theAEDescList,
                        AEArrayType arrayType,
                        AEArrayDataPointer arrayPtr,
                        Size maximumSize,
                        DescType *itemType,
                        Size *itemSize,
                        long *itemCount)
 = {0x303C,0x0D0C,0xA816}; 
pascal OSErr AEPutArray(const AEDescList *theAEDescList,
                        AEArrayType arrayType,
                        AEArrayDataPointer arrayPtr,
                        DescType itemType,
                        Size itemSize,
                        long itemCount)
 = {0x303C,0x0B0D,0xA816}; 
pascal OSErr AEDeleteItem(const AEDescList *theAEDescList,
                          long index)
 = {0x303C,0x040E,0xA816}; 

/* 
 *********************************************************************
 The following calls apply to AERecord.
   Since AERecord is a subtype of AEDescList, the calls in the previous
   sections can also be used for AERecord
   an AERecord can be created by using AECreateList with isRecord set to true 
*/

pascal OSErr AEPutKeyPtr(const AERecord *theAERecord,
                         AEKeyword theAEKeyword,
                         DescType typeCode,
                         Ptr dataPtr,
                         Size dataSize)
 = {0x303C,0x0A0F,0xA816}; 
pascal OSErr AEPutKeyDesc(const AERecord *theAERecord,
                          AEKeyword theAEKeyword,
                          const AEDesc *theAEDesc)
 = {0x303C,0x0610,0xA816}; 
pascal OSErr AEGetKeyPtr(const AERecord *theAERecord,
                         AEKeyword theAEKeyword,
                         DescType desiredType,
                         DescType *typeCode,
                         Ptr dataPtr,
                         Size maximumSize,
                         Size *actualSize)
 = {0x303C,0x0E11,0xA816}; 
pascal OSErr AEGetKeyDesc(const AERecord *theAERecord,
                          AEKeyword theAEKeyword,
                          DescType desiredType,
                          AEDesc *result)
 = {0x303C,0x0812,0xA816}; 
pascal OSErr AESizeOfKeyDesc(const AERecord *theAERecord,
                             AEKeyword theAEKeyword,
                             DescType *typeCode,
                             Size *dataSize)
 = {0x303C,0x0829,0xA816}; 
pascal OSErr AEDeleteKeyDesc(const AERecord *theAERecord,
                             AEKeyword theAEKeyword)
 = {0x303C,0x0413,0xA816}; 

/* 
 
  *********************************************************************
  The following calls are used to pack and unpack parameters from records of
  type AppleEvent. Since AppleEvent is a subtype of AERecord, the calls in the previous
  sections can also be used for variables of type AppleEvent. The next six calls
  are in fact identical to the six calls for AERecord.
*/

pascal OSErr AEPutParamPtr(const AppleEvent *theAppleEvent,
                           AEKeyword theAEKeyword,
                           DescType typeCode,
                           Ptr dataPtr,
                           Size dataSize)
 = {0x303C,0x0A0F,0xA816}; 
pascal OSErr AEPutParamDesc(const AppleEvent *theAppleEvent,
                            AEKeyword theAEKeyword,
                            const AEDesc *theAEDesc)
 = {0x303C,0x0610,0xA816}; 
pascal OSErr AEGetParamPtr(const AppleEvent *theAppleEvent,
                           AEKeyword theAEKeyword,
                           DescType desiredType,
                           DescType *typeCode,
                           Ptr dataPtr,
                           Size maximumSize,
                           Size *actualSize)
 = {0x303C,0x0E11,0xA816}; 
pascal OSErr AEGetParamDesc(const AppleEvent *theAppleEvent,
                            AEKeyword theAEKeyword,
                            DescType desiredType,
                            AEDesc *result)
 = {0x303C,0x0812,0xA816}; 
pascal OSErr AESizeOfParam(const AppleEvent *theAppleEvent,
                           AEKeyword theAEKeyword,
                           DescType *typeCode,
                           Size *dataSize)
 = {0x303C,0x0829,0xA816}; 
pascal OSErr AEDeleteParam(const AppleEvent *theAppleEvent,
                           AEKeyword theAEKeyword)
 = {0x303C,0x0413,0xA816}; 

/* 
 *********************************************************************
 The following calls also apply to type AppleEvent.  Message attributes are far more restricted, and
 can only be accessed through the following 5 calls. The various list and record routines cannot be used
 to access the attributes of an event. 
*/

pascal OSErr AEGetAttributePtr(const AppleEvent *theAppleEvent,
                               AEKeyword theAEKeyword,
                               DescType desiredType,
                               DescType *typeCode,
                               Ptr dataPtr,
                               Size maximumSize,
                               Size *actualSize)
 = {0x303C,0x0E15,0xA816}; 
pascal OSErr AEGetAttributeDesc(const AppleEvent *theAppleEvent,
                                AEKeyword theAEKeyword,
                                DescType desiredType,
                                AEDesc *result)
 = {0x303C,0x0826,0xA816}; 
pascal OSErr AESizeOfAttribute(const AppleEvent *theAppleEvent,
                               AEKeyword theAEKeyword,
                               DescType *typeCode,
                               Size *dataSize)
 = {0x303C,0x0828,0xA816}; 
pascal OSErr AEPutAttributePtr(const AppleEvent *theAppleEvent,
                               AEKeyword theAEKeyword,
                               DescType typeCode,
                               Ptr dataPtr,
                               Size dataSize)
 = {0x303C,0x0A16,0xA816}; 
pascal OSErr AEPutAttributeDesc(const AppleEvent *theAppleEvent,
                                AEKeyword theAEKeyword,
                                const AEDesc *theAEDesc)
 = {0x303C,0x0627,0xA816}; 

/* 
 *********************************************************************
  The next four calls are basic routines used to create, send, and process AppleEvents. 
*/

pascal OSErr AECreateAppleEvent(AEEventClass theAEEventClass,
                                AEEventID theAEEventID,
                                const AEAddressDesc *target,
                                short returnID,
                                long transactionID,
                                AppleEvent *result)
 = {0x303C,0x0B14,0xA816}; 
pascal OSErr AESend(const AppleEvent *theAppleEvent,
                    AppleEvent *reply,
                    AESendMode sendMode,
                    AESendPriority sendPriority,
                    long timeOutInTicks,
                    IdleProcPtr idleProc,
                    EventFilterProcPtr filterProc)
 = {0x303C,0x0D17,0xA816}; 
pascal OSErr AEProcessAppleEvent(const EventRecord *theEventRecord)
 = {0x303C,0x021B,0xA816}; 

/* 
 During event processing, an event handler may realize that it is likely
 to exceed the client's timeout limit. Passing the reply to this
 routine causes a wait event to be generated to ask the client for more time. 
*/

pascal OSErr AEResetTimer(const AppleEvent *reply)
 = {0x303C,0x0219,0xA816}; 

/* 
   *********************************************************************
 The following four calls are available for applications which need more sophisticated control
 over when and how events are processed. Applications which implement multi-session servers or 
 which implement their own internal event queueing will probably be the major clients of these
 routines.  
 
  Can be called from within a handler to prevent the AEM from disposing of
 the AppleEvent when the handler returns. Can be used to asynchronously process the 
 event (as in MacApp).
*/

pascal OSErr AESuspendTheCurrentEvent(const AppleEvent *theAppleEvent)
 = {0x303C,0x022B,0xA816}; 

/* 
 
   Tells the AppleEvent manager that processing is either about to resume or has
  been completed on a previously suspended event. The procPtr passed in as the
  dispatcher parameter will be called to attempt to redispatch the event. Several
  constants for the dispatcher parameter allow special behavior. They are:
  - kAEUseStandardDispatch means redispatch as if the event was just received, using the
   standard AppleEvent Dispatcher.
  - kAENoDispatch means ignore the parameter.
   Use this in the case where no redispatch is needed, and the event has been handled.
  - non nil means call the routine which dispatcher points to.
*/

pascal OSErr AEResumeTheCurrentEvent(const AppleEvent *theAppleEvent,
                                     const AppleEvent *reply,
                                     EventHandlerProcPtr dispatcher,
                                     long handlerRefcon)
 = {0x303C,0x0818,0xA816}; 
/* Allows application to examine the currently executing event */
pascal OSErr AEGetTheCurrentEvent(AppleEvent *theAppleEvent)
 = {0x303C,0x021A,0xA816}; 
/* Set the current event to the parameter */
pascal OSErr AESetTheCurrentEvent(const AppleEvent *theAppleEvent)
 = {0x303C,0x022C,0xA816}; 

/* 
 
  *********************************************************************
   The following three calls are used to allow applications to behave courteously 
  when a user interaction such as a dialog box is needed. 
*/

pascal OSErr AEGetInteractionAllowed(AEInteractAllowed *level)
 = {0x303C,0x021D,0xA816}; 
pascal OSErr AESetInteractionAllowed(AEInteractAllowed level)
 = {0x303C,0x011E,0xA816}; 
pascal OSErr AEInteractWithUser(long timeOutInTicks,
                                NMRecPtr nmReqPtr,
                                IdleProcPtr idleProc)
 = {0x303C,0x061C,0xA816}; 

/* 
  *********************************************************************
  These calls are used to set up and modify the event dispatch table  }
  
 { Add an AppleEvent Handler 
*/

pascal OSErr AEInstallEventHandler(AEEventClass theAEEventClass,
                                   AEEventID theAEEventID,
                                   EventHandlerProcPtr handler,
                                   long handlerRefcon,
                                   Boolean isSysHandler)
 = {0x303C,0x091F,0xA816}; 
/*  Remove an AppleEvent Handler  */
pascal OSErr AERemoveEventHandler(AEEventClass theAEEventClass,
                                  AEEventID theAEEventID,
                                  EventHandlerProcPtr handler,
                                  Boolean isSysHandler)
 = {0x303C,0x0720,0xA816}; 
/*  Get the corresponding AppleEvent Handler  */
pascal OSErr AEGetEventHandler(AEEventClass theAEEventClass,
                               AEEventID theAEEventID,
                               EventHandlerProcPtr *handler,
                               long *handlerRefcon,
                               Boolean isSysHandler)
 = {0x303C,0x0921,0xA816}; 

/* 
  *********************************************************************
  These calls are used to set up and modify the coercion dispatch table  
*/

pascal OSErr AEInstallCoercionHandler(DescType fromType,
                                      DescType toType,
                                      ProcPtr handler,
                                      long handlerRefcon,
                                      Boolean fromTypeIsDesc,
                                      Boolean isSysHandler)
 = {0x303C,0x0A22,0xA816}; 
/*  Remove a Coercion Handler  */
pascal OSErr AERemoveCoercionHandler(DescType fromType,
                                     DescType toType,
                                     ProcPtr handler,
                                     Boolean isSysHandler)
 = {0x303C,0x0723,0xA816}; 
/*  Get the corresponding Coercion Handler  */
pascal OSErr AEGetCoercionHandler(DescType fromType,
                                  DescType toType,
                                  ProcPtr *handler,
                                  long *handlerRefcon,
                                  Boolean *fromTypeIsDesc,
                                  Boolean isSysHandler)
 = {0x303C,0x0B24,0xA816}; 

/* 
 
    *********************************************************************
  These calls are used to set up and modify special hooks into the AppleEvent Manager.
 
  Install the special handler named by the Keyword  
*/

pascal OSErr AEInstallSpecialHandler(AEKeyword functionClass,
                                     ProcPtr handler,
                                     Boolean isSysHandler)
 = {0x303C,0x0500,0xA816}; 
/*  Remove the special handler named by the Keyword  */
pascal OSErr AERemoveSpecialHandler(AEKeyword functionClass,
                                    ProcPtr handler,
                                    Boolean isSysHandler)
 = {0x303C,0x0501,0xA816}; 
/*  Get the special handler named by the Keyword  */
pascal OSErr AEGetSpecialHandler(AEKeyword functionClass,
                                 ProcPtr *handler,
                                 Boolean isSysHandler)
 = {0x303C,0x052D,0xA816}; 
#ifdef __cplusplus
}
#endif

#endif
