/*
	File:		PPCAuth.c

	Copyright:	© 1989-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<36>	 4/14/92	BBM		<JSM>: Remove unfinished PPC code that is under the contitional
									“TheFutute”, and remove the conditional “CubeE” since that is
									reality. Remove conditionals, since all they do is confuse.
		<35>	 10/4/91	JSM		Change PsychoticFarmerOrLater conditionals to TheFuture.
		<34>	 9/29/91	DTY		Conditionalize <32> and <33> out of the CubeE build.
		<33>	 6/26/91	EMT		Fix length check on user name bug
		<32>	 6/10/91	EMT		Provide internal call to create userRefnums
		<31>	12/13/90	EMT		<JSM> Support 0 Length String to mean DefaultPrompt in
									StartSecureSession, changed default prompt to have smart quotes,
									and use ParamText for internationalization.
		<30>	11/13/90	EMT		<stb> Have StartSecureSession preflight for idiot error in the
									same fashion PPCStart does, and fix noUserNameBug, changed
									pGlobal to ppcglobptr, for consistency.
		<29>	 11/8/90	EMT		<stb>Fix bug in GetDefaultUser, change how userrefnums are
									handled, so that the limit is dynamic. Fixed bug so that user
									reference numbers are tied to Name/Password pair, not just Name.
		<28>	 11/6/90	EMT		minor bug fixes.
		<27>	10/24/90	EMT		Update error codes
		<26>	10/19/90	JSM		<EMT> Remove ppcPromptForUser(), no longer used.
		<25>	10/11/90	EMT		Make changes to obsolete CompletionGlue.a
		<24>	 9/21/90	EMT		Update constants, types, and field names as dictated by
									PPCToolBox.h
		<23>	 9/14/90	VC		Changed all reference to UserREf to an unsigned long.
		<22>	  9/4/90	EMT		Eric's Changes rolled in here!
		<21>	 8/23/90	VC		In PPCStartSecure after CheckLocName set the error code in the
									cmdResult field of the PB.
		<20>	 8/21/90	VC		In StartCesureSession added the extra check from the return of
									CheckLocName for error codes.
		<19>	 8/18/90	dba		get rid of code to center the PPCAlert alert, since the Window
									Mgr. does it; also simplify other code surrounding the call to
									the alert, including getting rid of the cursor adjusting code,
									since the standard dialog filter now does that
		<18>	 8/10/90	S		Included making a default string for login dialog.
		<17>	 6/28/90	S		Fixed login problem (guestnotAllowed Error) when actuallu name
									and password are nil.
		<16>	 6/11/90	S		Change Divide by 2 into Shift Operation in promptCallBack
									procedure.
		<15>	 6/11/90	S		Change promptCallBcak to promptCallBack.
		<14>	  6/1/90	VC		Addde mixupPswd to un-scramble password from the user record.
		<13>	 4/26/90	VC		Returning the proper selectItem from the callback routine
		<12>	 4/18/90	JSM		Include String.h for memset definition, add prototype for
									random, #ifdef some local variables for INIT version only, don't
									HLock things for BlockMove, and other miscellaneous code size
									reductions.
		<11>	 4/18/90	JSM		#ifdef openPPCRf for INIT version only.
		<10>	 4/10/90	S		Error Code Fix for LogIN Cancel.
		 <9>	 3/20/90	S		To Fix Some Error Codes.
		 <7>	 2/27/90	S		use new user&group.h file.
	   <2.1>	 1/22/90	CVC		Remove "STRATCALLBACK" and pass proc pointer when
	   								calling PromptForUser in PPcStartSecure.
		 <2>	12/28/89	dba		use quotes around the names of local header files, brackets
									around the names of header files from the Interfaces or
									Internals directories
	   <1.4>	 12/7/89	CVC		Added centering of the alert window.
	   <1.3>	11/28/89	CVC		Added ppcStartSecure call.
	   <1.2>	11/17/89	CVC		Added a conditioned-dompile in PPCPromptForUser.
	   <1.1>	 11/7/89	CVC		Changed PPCPromptForUser to allow specifying User names
	   <1.0>	10/12/89	CVC		Adding Access Control for the first time.

	   Old Revision History:

		9/20/89 	Victor	   Created.
		10/12/89	Victor	   Moved the initAuth call to ppcLoader.c

*/

#include "PPCCommon.h"
#include "UserGroup.h"
#include <QuickDraw.h>
#include <Controls.h>
#include <Windows.h>
#include <Dialogs.h>
#include <String.h>		// for memset definition
#include <Strings.h>
/*---------------------------------------------------------------------------------------------------
	Constants used only in this file
---------------------------------------------------------------------------------------------------*/
#define ppcErrStrings -16411
#define rPPCAlert -16411

/*---------------------------------------------------------------------------------------------------
	Prototypes used in this file only.
---------------------------------------------------------------------------------------------------*/
STATIC void GetUserCompletion(void);
STATIC Boolean UserRefNumCompare(UserEntryPtr theUserEntry,unsigned long userRef);
STATIC UserEntryPtr FindUserByNameAndPassword(StringPtr userName,StringPtr password);
STATIC UserEntryPtr GetFreeEntry(void);
STATIC OSErr promptCallBack (StringPtr password, StringPtr name, short method, PPCStartPBPtr pb);


long random();

extern pascal KeySched (char*, long*);
extern pascal Encode (long*, long, long **);


/*---------------------------------------------------------------------------------------------------
	mixupPswd
	This is a very silly routine to mix up passwords in the user and groups file.
	It has the sole advantage of making it hard to figure out the algorithm even
	if a large number of users have a blank password (I hope). Since this is an
	encryption routine the code is suitable cryptic.
---------------------------------------------------------------------------------------------------*/
void mixupPswd (char * PassBlk, long UserID, Boolean Encrypt)
{
	char * mask = "rpcgtprk";
	char key = (char)UserID;
	short i;
	
	if (Encrypt)
	{
		for (i=0; i<8; i++)
			PassBlk[i] = key = PassBlk[i] ^ mask[i] ^ key;
	}
	else
	{
		for (i=7; i>0; i--)
			PassBlk[i] ^= mask[i] ^ PassBlk[i-1];
			
		PassBlk[0] ^= mask[0] ^ key;
	}
}


/************************************************************************************
*			getUserRec
************************************************************************************/
getUserRec (UserRecPb *urec, int keyID, char *keyName, int (*ppcComplete)(), short refNum)
{
	urec->btPb.ioBTKeyPtr = (Ptr)&(urec->key);
	BldFSKey( keyID, keyName, urec->btPb.ioBTKeyPtr);	// make the key
	urec->btPb.ioBuffer= (Ptr)&(urec->u.record);	// set pointer to record
	urec->btPb.ioReqCount = sizeof (urec->u);
	urec->btPb.ioRefNum= refNum;
	urec->btPb.ioCompletion= (ProcPtr)GetUserCompletion;
	urec->btPb.ioBTHint1= 0;						// zero Hint field
	urec->usrCompletion= ppcComplete;				// set up completion routine
	BTSEARCHPPC( &urec->btPb, 1);						// dispatch the call
}

/************************************************************************************
*			GetUserCompletion
************************************************************************************/
STATIC void GetUserCompletion(void)

{
	UserRecPb *urec;
	long keyArray[32];
	long   *temp;
	
	urec = GetA0();
	// see if we found user, if we do generate a random number and encrypt
	// the random number.
	if (!urec->btPb.ioResult)

		{
		mixupPswd (urec->u.record.Password, urec->u.record.UserID, 0);
		urec->random[0]= urec->encryptedRandom[0]= random();
		urec->random[1]= urec->encryptedRandom[1]= random();
		KeySched(urec->u.record.Password, keyArray);
		temp = urec->encryptedRandom;
		Encode(keyArray, 8, &temp);
		}

	(*urec->usrCompletion) (urec);
	return;

}

/************************************************************************************
*			GetAuthInfo
************************************************************************************/
Boolean GetAuthInfo(long *authInfo, unsigned long refNum)
{
	long                keyArray[32];
	UserEntryPtr        uEntry;
	char				tempPassword[9];
	char				password[8];


   if ((uEntry = findUserByRef(refNum)) == nil)
   	  return false;

	/* Use the entrey addrfess as the key to scramble the string. */
	memset(tempPassword,0, 9);
	scramble (kPassWordKey, uEntry->password, tempPassword);
	BlockMove( &tempPassword[1], password, 8);

	KeySched(password, keyArray);
	Encode(keyArray, 8, &authInfo);
	return true;
}

/************************************************************************************
*			random
************************************************************************************/
long random()

{
	long randnum;
	
	GetDateTime((unsigned long *)&randnum);
	return randnum;
}

/************************************************************************************
*			checkInit
************************************************************************************/
OSErr checkInit ()
{
PPCGlobalParamsPtr ppcglobPtr;

if (((ppcglobPtr = (PPCGlobalParamsPtr)getGlobal()) == nil) || !ppcglobPtr->inited)
	return notInitErr;
else return 0;
}

/*---------------------------------------------------------------------------------------------------
	ppcStartSecure is the entry point for StartSecureSession.
---------------------------------------------------------------------------------------------------*/
OSErr ppcStartSecure (StartSecureParam *pu)

{
	Handle  	userName;
	short		selectedItem, loginMethod;
	char		password[10];
	Str32		name;
	OSErr 		result;
	PPCGlobalParamsPtr ppcglobPtr;
	OSErr		err;
	char        *logTempStr;
	PPCStartPBPtr startPB;
	
	if (result = checkInit())
		return result;
	
	ppcglobPtr = (PPCGlobalParamsPtr)getGlobal();
	startPB = pu->startPb;

		 if (!ValidPortName(startPB->portName))
	{
		return(startPB->ioResult = badPortNameErr);
	}
	else if (startPB->serviceType != ppcServiceRealTime)
	{
		return(startPB->ioResult = badServiceMethodErr);
	}
	else if (!PortRefNumtoPtr(startPB->portRefNum, ppcglobPtr))
	{
		return(startPB->ioResult = noPortErr);
	}
	else if (result = VerifyLocNameFormat(startPB->locationName))
	{
		return(startPB->ioResult = result);
	}
	
	if(LocationNameLocal(pu->startPb->locationName))
	{
		// user wants to make a local session
		startPB->userRefNum = 0;
		return PPCStart(startPB, false);
	}
	
	if ((pu->useDefault) && !(err = GetDefaultUser( &(pu->startPb)->userRefNum, name)))
	{
		/* Got the default user ref. Make the PPCStart call.  Return if no error or if
		 * the error code is not authFailErr, or userRejectErr.
		 */
		err = PPCStart(startPB, false);
		if (!err)
		{
			BlockMove(name, pu->userName,sizeof(Str32));
			return noErr;
		}
	
		else if (err != userRejectErr && err != authFailErr)
			return err;
	}
	
	selectedItem = 7;
	loginMethod = 3;
	password [0] = 0;
	
	if (!(char)(*pu->userName))
	{
		if (!(userName = GetResource('STR ', -16096)))
		{
			*pu->userName = 0;
			selectedItem = 5;
		}
		else
		{
			/* no need to lock userName for BlockMove */
			BlockMove(*userName, pu->userName, 32);
		}
	}
	
	ppcglobPtr->ppcIcon = GetResource( 'ICN#', (short)-16411);
	MoveHHi ( ppcglobPtr->ppcIcon);
	HLock( ppcglobPtr->ppcIcon);
	
	if (pu->prompt && pu->prompt[0])	// If their exists a prompt, and of length > 0 then.
		logTempStr = pu->prompt; // user has supplied a string
	else
	{
		logTempStr = NULL;	// Use default prompt, parameter text.
		ParamText(startPB->portName->name,startPB->locationName->u.nbpEntity.objStr,NULL,NULL);
	}

	result = PromptForUser (logTempStr, ppcglobPtr->ppcIcon, pu->userName, password, selectedItem,
						pu->allowGuest, &loginMethod, (ProcPtr)promptCallBack, startPB);
	HUnlock(ppcglobPtr->ppcIcon);
	
	if (result)
		return (startPB->ioResult = userCanceledErr);
	
	if (loginMethod == 1)
		*pu->guestSelected = 1;
	else
		*pu->guestSelected = 0;
	
	return (startPB->ioResult);
}

/*---------------------------------------------------------------------------------------------------
	promptCallBack is called by the StartSecureSession dialog when it is time to start a secure
	session.
---------------------------------------------------------------------------------------------------*/
STATIC OSErr promptCallBack (StringPtr password, StringPtr name, short method, PPCStartPBPtr pb)
{
	UserEntry	*theUserEntry;
	OSErr		err;
	Str255		message;
	short		selectedItem;
	Boolean		createdNewRefNum;
	
	createdNewRefNum = false;
	if (method == 1)	// Do we attempt to log in as a guest?
	{
		pb->userRefNum = 0;
		err = PPCStart(pb,false);
	}
	else if (name[0])					// Use this else for CubeE
	{
		if (!(theUserEntry = FindUserByNameAndPassword(name,password)))
		{
			if (!(theUserEntry = GetFreeEntry ()))
			{
				pb->ioResult = noUserRefErr;
				return 0;
			}
			else	// Create a new UserEntry
			{
				createdNewRefNum = true;
				scramble (kNameKey, name, theUserEntry->name);
				scramble (kPassWordKey, password, theUserEntry->password);
			}
		}
		pb->userRefNum = theUserEntry->ref;
		err = PPCStart(pb,false);

		if(err && createdNewRefNum)
			ppcDeleteUser(&theUserEntry->ref);
	}
	else	// User didn't fill in the user name.
		goto GetName;
	
	
	if (err == authFailErr)
	{
		selectedItem = 7;
		GetIndString(message, ppcErrStrings, 1);
	}
	else if(err == userRejectErr || err == noUserNameErr)
	{
GetName:
		selectedItem = 5;
		GetIndString(message, ppcErrStrings, 2);
	}
	else
		return(noErr);	// This is not necessarly the error in the startPB.

	ParamText(message, nil, nil, nil);
	StopAlert( rPPCAlert, nil);
	ParamText(pb->portName->name,pb->locationName->u.nbpEntity.objStr,NULL,NULL);
	return selectedItem;
}

/*---------------------------------------------------------------------------------------------------
	UserRefNumCompare is compares a userreference number and a UserEntry->ref to see if they are the
	same.
---------------------------------------------------------------------------------------------------*/
STATIC Boolean UserRefNumCompare(UserEntryPtr theUserEntry,unsigned long userRef)
{
	return(theUserEntry->ref == userRef);
}

/*---------------------------------------------------------------------------------------------------
	ppcDeleteUser, deletes a user by his reference number.  It returns the result of the operation,
	either noErr or noUserRecErr.  This is the entry point to DeleteUserIdentity.
---------------------------------------------------------------------------------------------------*/
OSErr ppcDeleteUser (unsigned long *userRef)
{
	PPCGlobalParamsPtr ppcglobPtr;
	UserEntryPtr theUserEntry;
	
	ppcglobPtr = getGlobal();
	if(theUserEntry = DeleteFromQueue(&ppcglobPtr->UserEntryQueue,*userRef,UserRefNumCompare))
	{
		DisposeMem(theUserEntry);
		return(noErr);
	}
	else
		return(noUserRecErr);
}

/*---------------------------------------------------------------------------------------------------
	ppcGetDefaultUser returns the user reference number, and the machine owners name if it alread 
	exists.  This is the entry point to GetDefaultUser.
---------------------------------------------------------------------------------------------------*/
OSErr ppcGetDefaultUser (GetDefaultParam *pu)

{
	PPCGlobalParamsPtr ppcglobPtr;
	Handle			userName;
	UserEntryPtr	theUserEntry;
	OSErr			result;
	char			UserPassword[9];
	
	if ((result = checkInit()) == noErr)
	{
		ppcglobPtr = getGlobal();
		
		if (!(userName = GetResource('STR ', -16096)))
		{
			result = noDefaultUserErr;
		}
		else
		{
			{	// The following block of code is just to get the password out.
				BTioParam		btPb;								// PB for B-Tree calls
				UserAcRecord	theUserRecord;
				BTKey theKey;
				
				BldFSKey(0,*userName,(Ptr) &theKey);					// make the key
				btPb.ioBTKeyPtr = (Ptr)&theKey;
				btPb.ioBuffer= (Ptr)&theUserRecord;				// set pointer to record
				btPb.ioReqCount = sizeof (UserAcRecord);
				btPb.ioRefNum= ppcglobPtr->ugFile.refNum;
				btPb.ioBTHint1= 0;								// zero Hint field
				result = BTSEARCHPPC(&btPb,false);				// dispatch the call
				mixupPswd (theUserRecord.Password, theUserRecord.UserID, 0);	// unscramble the password.
				BlockMove(theUserRecord.Password,UserPassword,8);	// Copy the password.
				UserPassword[8] = 0;								// Force Termination.
				c2pstr(UserPassword);								// Convert it to a pascal string.
			}

			if (!(theUserEntry = FindUserByNameAndPassword(*userName,UserPassword)))
			{
				result = notLoggedInErr;
			}
			else
			{
				*pu->userRef = theUserEntry->ref;
				if(pu->userName)
					BlockMove(*userName,pu->userName,sizeof(Str32));
			}
		}
	}
	return result;
}

/*---------------------------------------------------------------------------------------------------
	FindUserByNameAndPassword will locate a user by his name and password.  If NULL is passed as the
	password, the search is only done by name.
---------------------------------------------------------------------------------------------------*/
STATIC UserEntryPtr FindUserByNameAndPassword(StringPtr userName,StringPtr password)
{
	PPCGlobalParamsPtr ppcglobPtr;
	UserEntryPtr theUserEntry;
	Str32	unscrambledName;
	char	unscrambledpassword[9];

	ppcglobPtr = getGlobal();
	FOREACHELEMENT(theUserEntry,&ppcglobPtr->UserEntryQueue)
	{
		scramble(kNameKey,theUserEntry->name,unscrambledName);	// unscramble the users name.
		if (EqualString(unscrambledName,userName,false,true))
		{
			if(password)
			{
				scramble(kPassWordKey,theUserEntry->password,unscrambledpassword);	// unscramble the password.
				if(!memcmp(unscrambledpassword,password,unscrambledpassword[0]))
					break;
			}
			else
				break;
		}
	}
	return(theUserEntry);
}

/*---------------------------------------------------------------------------------------------------
	findUserByRef will locate a user by his reference number.
---------------------------------------------------------------------------------------------------*/
UserEntryPtr findUserByRef (unsigned long ref)

{
	PPCGlobalParamsPtr ppcglobPtr;
	UserEntryPtr theUserEntry;
	
	ppcglobPtr = getGlobal();
	FOREACHELEMENT(theUserEntry,&ppcglobPtr->UserEntryQueue)
	{
		if(theUserEntry->ref == ref)
			break;
	}
	return(theUserEntry);
}

/*---------------------------------------------------------------------------------------------------
	GetFreeEntry allocates a new user entry
---------------------------------------------------------------------------------------------------*/
STATIC UserEntryPtr GetFreeEntry(void)

{
	PPCGlobalParamsPtr ppcglobPtr;
	UserEntryPtr theUserEntry;
	
	ppcglobPtr = getGlobal();
	if(theUserEntry = NewMem(sizeof(UserEntry)))
	{
		theUserEntry->ref = ppcglobPtr->nextUserRef++;
		if (ppcglobPtr->nextUserRef == 0)
			++ppcglobPtr->nextUserRef;
		EnQueue(theUserEntry,&ppcglobPtr->UserEntryQueue);
	}
	return(theUserEntry);
}


/*---------------------------------------------------------------------------------------------------
	Scramble is used to mutate a string in such a way as to be unrecognizable in memory.  This
	procedure is not the most secure, but it should work just fine.
---------------------------------------------------------------------------------------------------*/
void scramble( unsigned char key, StringPtr pSrc, StringPtr pDest)
{
	short		len;

	if(pDest)	// make sure it is not a null pointer.
	{
		len = *pSrc++;
		*pDest++ = len;
		while (len)
			{
			*pDest++ = *pSrc++ ^ key;
			--len;
			}
	}
}
