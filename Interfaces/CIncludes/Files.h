/************************************************************

Created: Tuesday, July 30, 1991 at 3:46 PM
 Files.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved

	Change History (most recent first):

	   <SM3>	10/14/93	pdw		Changed CntrlParamBlockRec to use ParamBlockHeader instead of
									individual fields.
	   <SM2>	  8/5/93	JDR		Moved NumVersions to Types.h
		<43>	 7/30/91	JL		Updated Copyright. Restored comments.
		<42>	 6/14/91	JL		Checked in official MPW 3.2Ä version. Fixed Inline for
									PBSetFInfoSync and PBSetFInfoAsync calls. Adjusted some comment
									formats to match the DSG Database. Temporarily lost the updated
									copyright date; will be restored. Updated the creation date (3rd
									line of this file.)
		<41>	  2/5/91	dnf		stb, gs, Add VolMountInfoHeader.
		<40>	  2/5/91	stb		gs: change ioDirFlg back to its historical value
		<39>	  2/1/91	stb		dnf,dnf003: change the inlines to set the HFS bit (10 in the
									trap word) for all HFS calls which have a dirID (CatSearch,
									Get|SetForeignPrivs).
		<38>	 1/28/91	LN		Checked in Database Generated File from DSG. changed
									foreignprivParam branch of HParamBlock union to
									foreignPrivParam; changed ioDirFlg from 3 to 4;moved obsolete
									names to end of file
		<37>	 1/25/91	stb		JDR: remove MakeFSSpec
		<36>	 1/18/91	stb		& dnf; add Get/SetForeignPrivs; fix spelling on bHasBTreeMgr;
									add authentication constants; change to FSSpec *spec for
									MakeFSSpec
		<35>	 1/16/91	dnf		(dfh) Add fsUnixPriv
		<34>	 1/10/91	PP		(PWD) Remove AFPVolMountBlock structure since it should not be
									made public.
		<33>	  1/7/91	JDR		(dba) Adding the FSSpecArray type.
		<32>	  1/2/91	dba		(JDR) fix PBCloseWDAsync (wasnÕt asynchronous), and the trap
									number for AllocContig
		<30>	12/14/90	PP		(JSM) Remove duplicate definition of MediaType and
									AppleShareMediaType.
		<29>	12/14/90	dnf		(w/dba) Change ioDestNamePtr (in FIDParam), ioObjNamePtr (in
									ObjParam) and ioNewName and ioCopyName (in CopyParam) to
									StringPtr. This matches Pascal and is more correct.
		<28>	 12/6/90	JL		Fixed PBLockRange,PBUnlockRange,PBSetVInfo Sync and ASync inline
									code. Wasn't getting selector into A0 and was calling wrong trap
									numbers.
		<27>	 12/5/90	dba		<dnf> Fix inlines for PBHOpenDFSync and PBHOpenDFAsync. Add
									GetVolParmsInfoBuffer definition, definitions for desktop
									database icon types, and definitions for vMAttrib bits.
		<26>	11/29/90	JL		Put formal parameter names back.
		<25>	11/29/90	PP		(prp/JSM) Fix typos and struct names of VolumeMount equates.
		<24>	11/27/90	PWD		Add VolumeMount equates, three associated a060 traps
		<23>	 11/7/90	JL		Changed all #defines to anonymous enums
		<22>	 11/4/90	dba		fixed some scrambled comments; got rid of some extraneous
									parameter names; used constStr255Parameter; made some parameters
									void* instead of Ptr; added more use of const in parameters;
									used const FSSpec * instead of FSSpecPtr for calls that take
									input-only FSSpecs
	   	<21>	10/30/90	dnf		(dnf/ngk) moved FSpCreateResFile and FSpOpenResFile into Resources.h.  Added
	   								OpenDF and HOpenDF high-level glue.  Removed async parameter (and #pragma
									glue) for DTGetPath, DTCloseDown and DTOpenInform. (dnf/th) Changed FXInfo and
									DXInfo to add fdXFlags/frXFlags fields.
		<20>	10/21/90	gbm		(with dba) Made compatible with 3.2 C compiler (and incompatible
									with previous compilers).
		<20>	  10/10/90	JAL		Added Sync and ASync calls, New style #Pragma Parameters for MPW 3.2 C.
		<19>	  9/5/90	JNG		Update FXInfo and DXInfo
		<18>	 8/29/90	dnf		Add FSpExchangeFiles, Fix definition of FSpCreateResFile
		<17>	  8/6/90	dnf		Add inline code for _FSp traps
		<16>	  8/6/90	dnf		Add definitions of _FSp traps
		<15>	  6/2/90	dnf		Correct the length of CatPostionRec and the dirInfo record, Add
									definitions for FSP glue.
		<14>	  5/4/90	dnf		Add MakeFSSpec function prototype
		<13>	 4/25/90	dnf		Change filler length in DTPBRec
		<12>	 4/25/90	dnf		Fix DTPBRec param block
		<11>	 4/13/90	dnf		Add ioAPPLParID, ioDTLgLen and ioDTPyLen to DTParam.  Move it
									out of HParamBlockRec (since it's now too big) and rename it
									(since there's a different convention for things that aren't in
									HParamBlockRec).
	   								Move DTParam out of HParamBlockRec because it's now too big.
		<10>	 4/10/90	dnf		Change hFileInfo back to hfileInfo to remain consistent
									w/existing interfaces.
		 <9>	 3/16/90	dnf		Added FSSpec record and AltAccessParam. Changed DT call names to
									match latest from traps.a. Added OpenDF/HOpenDF and
									Get/SetAltAccess. Removed obsolete call names again and also
									removed non-existant high-level FileOpen calls.
		 <8>	  3/8/90	JAL		Changed changed hfileInfo to hFileInfo to stay consistent.
		 <7>	 2/25/90	dnf		Rename CSParam.ioQuant to ioSearchTime, positionRec to
									CatPositionRec. Remove obsolete call names.
		 <6>	 2/16/90	DNF		Add fsSBNegate
		 <2>	  1/9/90	dnf		Add fsSBFlParID
	   <1.4>	11/11/89	ngk		Added Desktop manger calls
	   <1.3>	  9/5/89	dnf		Added CatSearch equates
	   <1.2>	 7/31/89	EKN		Added FIDParam and FileIDs calls.
	   <1.1>	 11/9/88	CCH		Fixed headers and removed projector resource.
	   <1.0>	 11/9/88	CCH		Adding to EASE.

************************************************************/


#ifndef __FILES__
#define __FILES__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif

#ifndef __SEGLOAD__
#include <SegLoad.h>
#endif


enum {


/* Finder Constants */
 fsAtMark = 0,
 fOnDesk = 1,
 fsCurPerm = 0,
 fHasBundle = 8192,
 fsRdPerm = 1,
 fInvisible = 16384,
 fTrash = -3,
 fsWrPerm = 2,
 fDesktop = -2,
 fsRdWrPerm = 3,
 fDisk = 0,
 fsRdWrShPerm = 4,
 fsFromStart = 1,
 fsFromLEOF = 2,
 fsFromMark = 3,
 rdVerify = 64,
 ioDirFlg = 3,						/* see IM IV-125 */
 ioDirMask = 0x10,
 fsRtParID = 1,
 fsRtDirID = 2
};
enum {

/* CatSearch SearchBits Constants */
 fsSBPartialName = 1,
 fsSBFullName = 2,
 fsSBFlAttrib = 4,
 fsSBFlFndrInfo = 8,
 fsSBFlLgLen = 32,
 fsSBFlPyLen = 64,
 fsSBFlRLgLen = 128,
 fsSBFlRPyLen = 256,
 fsSBFlCrDat = 512,
 fsSBFlMdDat = 1024,
 fsSBFlBkDat = 2048,
 fsSBFlXFndrInfo = 4096,
 fsSBFlParID = 8192,
 fsSBNegate = 16384,
 fsSBDrUsrWds = 8,
 fsSBDrNmFls = 16,
 fsSBDrCrDat = 512,
 fsSBDrMdDat = 1024,
 fsSBDrBkDat = 2048,
 fsSBDrFndrInfo = 4096
};
enum {
 fsSBDrParID = 8192,

/* vMAttrib (GetVolParms) bit position constants */
 bLimitFCBs = 31,
 bLocalWList = 30,
 bNoMiniFndr = 29,
 bNoVNEdit = 28,
 bNoLclSync = 27,
 bTrshOffLine = 26,
 bNoSwitchTo = 25,
 bNoDeskItems = 20,
 bNoBootBlks = 19,
 bAccessCntl = 18,
 bNoSysDir = 17,
 bHasExtFSVol = 16,
 bHasOpenDeny = 15,
 bHasCopyFile = 14,
 bHasMoveRename = 13,
 bHasDesktopMgr = 12,
 bHasShortName = 11,
 bHasFolderLock = 10,
 bHasPersonalAccessPrivileges = 9
};
enum {
 bHasUserGroupList = 8,
 bHasCatSearch = 7,
 bHasFileIDs = 6,
 bHasBTreeMgr = 5,
 bHasBlankAccessPrivileges = 4,

/* Desktop Database icon Constants */
 kLargeIcon = 1,
 kLarge4BitIcon = 2,
 kLarge8BitIcon = 3,
 kSmallIcon = 4,
 kSmall4BitIcon = 5,
 kSmall8BitIcon = 6,

 kLargeIconSize = 256,
 kLarge4BitIconSize = 512,
 kLarge8BitIconSize = 1024,
 kSmallIconSize = 64,
 kSmall4BitIconSize = 128,
 kSmall8BitIconSize = 256,

/* Foreign Privilege Model Identifiers */
 fsUnixPriv = 1,

/* Version Release Stage Codes */
 developStage = 0x20,
 alphaStage = 0x40
};
enum {
 betaStage = 0x60,
 finalStage = 0x80,

/* Authentication Constants */
 kNoUserAuthentication = 1,
 kPassword = 2,
 kEncryptPassword = 3,
 kTwoWayEncryptPassword = 6
};

enum {hFileInfo,dirInfo};
typedef unsigned char CInfoType;


struct FInfo {
 OSType fdType;						/*the type of the file*/
 OSType fdCreator;					/*file's creator*/
 unsigned short fdFlags;			/*flags ex. hasbundle,invisible,locked, etc.*/
 Point fdLocation;					/*file's location in folder*/
 short fdFldr;						/*folder containing file*/
};

typedef struct FInfo FInfo;

struct FXInfo {
 short fdIconID;					/*Icon ID*/
 short fdUnused[3];					/*unused but reserved 6 bytes*/
 char fdScript;						/*Script flag and number*/
 char fdXFlags;						/*More flag bits*/
 short fdComment;					/*Comment ID*/
 long fdPutAway;					/*Home Dir ID*/
};

typedef struct FXInfo FXInfo;

struct DInfo {
 Rect frRect;						/*folder rect*/
 unsigned short frFlags;			/*Flags*/
 Point frLocation;					/*folder location*/
 short frView;						/*folder view*/
};

typedef struct DInfo DInfo;

struct DXInfo {
 Point frScroll;					/*scroll position*/
 long frOpenChain;					/*DirID chain of open folders*/
 char frScript;						/*Script flag and number*/
 char frXFlags;						/*More flag bits*/
 short frComment;					/*comment*/
 long frPutAway;					/*DirID*/
};

typedef struct DXInfo DXInfo;

struct GetVolParmsInfoBuffer {
 short vMVersion;					/*version number*/
 long vMAttrib;						/*bit vector of attributes (see vMAttrib constants)*/
 Handle vMLocalHand;				/*handle to private data*/
 long vMServerAdr;					/*AppleTalk server address or zero*/
 long vMVolumeGrade;				/*approx. speed rating or zero if unrated*/
 short vMForeignPrivID;				/*foreign privilege model supported or zero if none*/
};

typedef struct GetVolParmsInfoBuffer GetVolParmsInfoBuffer;

#define ParamBlockHeader \
 QElemPtr qLink;    				/*queue link in header*/\
 short qType;    					/*type byte for safety check*/\
 short ioTrap;    					/*FS: the Trap*/\
 Ptr ioCmdAddr;    					/*FS: address to dispatch to*/\
 ProcPtr ioCompletion;  			/*completion routine addr (0 for synch calls)*/\
 OSErr ioResult;    				/*result code*/\
 StringPtr ioNamePtr;  				/*ptr to Vol:FileName string*/\
 short ioVRefNum;   				/*volume refnum (DrvNum for Eject and MountVol)*/


struct IOParam {
 ParamBlockHeader 
 short ioRefNum;					/*refNum for I/O operation*/
 char ioVersNum;					/*version number*/
 char ioPermssn;					/*Open: permissions (byte)*/
 Ptr ioMisc;						/*Rename: new name (GetEOF,SetEOF: logical end of file) (Open: optional ptr to buffer) (SetFileType: new type)*/
 Ptr ioBuffer;						/*data buffer Ptr*/
 long ioReqCount;					/*requested byte count; also = ioNewDirID*/
 long ioActCount;					/*actual byte count completed*/
 short ioPosMode;					/*initial file positioning*/
 long ioPosOffset;					/*file position offset*/
};

typedef struct IOParam IOParam;

struct FileParam {
 ParamBlockHeader 
 short ioFRefNum;					/*reference number*/
 char ioFVersNum;					/*version number*/
 char filler1;
 short ioFDirIndex;					/*GetFInfo directory index*/
 unsigned char ioFlAttrib;			/*GetFInfo: in-use bit=7, lock bit=0*/
 unsigned char ioFlVersNum;			/*file version number*/
 FInfo ioFlFndrInfo;				/*user info*/
 unsigned long ioFlNum;				/*GetFInfo: file number; TF- ioDirID*/
 unsigned short ioFlStBlk;			/*start file block (0 if none)*/
 long ioFlLgLen;					/*logical length (EOF)*/
 long ioFlPyLen;					/*physical length*/
 unsigned short ioFlRStBlk;			/*start block rsrc fork*/
 long ioFlRLgLen;					/*file logical length rsrc fork*/
 long ioFlRPyLen;					/*file physical length rsrc fork*/
 unsigned long ioFlCrDat;			/*file creation date& time (32 bits in secs)*/
 unsigned long ioFlMdDat;			/*last modified date and time*/
};

typedef struct FileParam FileParam;

struct VolumeParam {
 ParamBlockHeader 
 long filler2;
 short ioVolIndex;					/*volume index number*/
 unsigned long ioVCrDate;			/*creation date and time*/
 unsigned long ioVLsBkUp;			/*last backup date and time*/
 unsigned short ioVAtrb;			/*volume attrib*/
 unsigned short ioVNmFls;			/*number of files in directory*/
 unsigned short ioVDirSt;			/*start block of file directory*/
 short ioVBlLn;						/*GetVolInfo: length of dir in blocks*/
 unsigned short ioVNmAlBlks;		/*GetVolInfo: num blks (of alloc size)*/
 long ioVAlBlkSiz;					/*GetVolInfo: alloc blk byte size*/
 long ioVClpSiz;					/*GetVolInfo: bytes to allocate at a time*/
 unsigned short ioAlBlSt;			/*starting disk(512-byte) block in block map*/
 unsigned long ioVNxtFNum;			/*GetVolInfo: next free file number*/
 unsigned short ioVFrBlk;			/*GetVolInfo: # free alloc blks for this vol*/
};

typedef struct VolumeParam VolumeParam;

struct CntrlParam {
	ParamBlockHeader 
	short	ioCRefNum;					/*refNum for I/O operation*/
	short	csCode;						/*word for control status code*/
	short	csParam[11];					/*operation-defined parameters*/
};

typedef struct CntrlParam CntrlParam;

struct SlotDevParam {
	ParamBlockHeader 
	short ioRefNum;
	char ioVersNum;
	char ioPermssn;
	Ptr ioMix;
	short ioFlags;
	char ioSlot;
	char ioID;
};

typedef struct SlotDevParam SlotDevParam;

struct MultiDevParam {
 ParamBlockHeader 
 short ioRefNum;
 char ioVersNum;
 char ioPermssn;
 Ptr ioMix;
 short ioFlags;
 Ptr ioSEBlkPtr;
};

typedef struct MultiDevParam MultiDevParam;

union ParamBlockRec {
 IOParam ioParam;
 FileParam fileParam;
 VolumeParam volumeParam;
 CntrlParam cntrlParam;
 SlotDevParam slotDevParam;
 MultiDevParam multiDevParam;
};

typedef union ParamBlockRec ParamBlockRec;
typedef ParamBlockRec *ParmBlkPtr;

struct HFileInfo {
 ParamBlockHeader 
 short ioFRefNum;
 char ioFVersNum;
 char filler1;
 short ioFDirIndex;
 char ioFlAttrib;
 char filler2;
 FInfo ioFlFndrInfo;
 long ioDirID;
 unsigned short ioFlStBlk;
 long ioFlLgLen;
 long ioFlPyLen;
 unsigned short ioFlRStBlk;
 long ioFlRLgLen;
 long ioFlRPyLen;
 unsigned long ioFlCrDat;
 unsigned long ioFlMdDat;
 unsigned long ioFlBkDat;
 FXInfo ioFlXFndrInfo;
 long ioFlParID;
 long ioFlClpSiz;
};

typedef struct HFileInfo HFileInfo;

struct DirInfo {
 ParamBlockHeader 
 short ioFRefNum;
 short filler1;
 short ioFDirIndex;
 char ioFlAttrib;
 char filler2;
 DInfo ioDrUsrWds;
 long ioDrDirID;
 unsigned short ioDrNmFls;
 short filler3[9];
 unsigned long ioDrCrDat;
 unsigned long ioDrMdDat;
 unsigned long ioDrBkDat;
 DXInfo ioDrFndrInfo;
 long ioDrParID;
};

typedef struct DirInfo DirInfo;

union CInfoPBRec {
 HFileInfo hFileInfo;
 DirInfo dirInfo;
};

typedef union CInfoPBRec CInfoPBRec;
typedef CInfoPBRec *CInfoPBPtr;

struct HIOParam {
 ParamBlockHeader 
 short ioRefNum;
 char ioVersNum;
 char ioPermssn;
 Ptr ioMisc;
 Ptr ioBuffer;
 long ioReqCount;
 long ioActCount;
 short ioPosMode;
 long ioPosOffset;
 short filler1;
};

typedef struct HIOParam HIOParam;

struct HFileParam {
 ParamBlockHeader 
 short ioFRefNum;
 char ioFVersNum;
 char filler1;
 short ioFDirIndex;
 char ioFlAttrib;
 char ioFlVersNum;
 FInfo ioFlFndrInfo;
 long ioDirID;
 unsigned short ioFlStBlk;
 long ioFlLgLen;
 long ioFlPyLen;
 unsigned short ioFlRStBlk;
 long ioFlRLgLen;
 long ioFlRPyLen;
 unsigned long ioFlCrDat;
 unsigned long ioFlMdDat;
};

typedef struct HFileParam HFileParam;

struct HVolumeParam {
 ParamBlockHeader 
 long filler2;
 short ioVolIndex;
 unsigned long ioVCrDate;
 unsigned long ioVLsMod;
 short ioVAtrb;
 unsigned short ioVNmFls;
 short ioVBitMap;
 short ioAllocPtr;
 unsigned short ioVNmAlBlks;
 long ioVAlBlkSiz;
 long ioVClpSiz;
 short ioAlBlSt;
 long ioVNxtCNID;
 unsigned short ioVFrBlk;
 unsigned short ioVSigWord;
 short ioVDrvInfo;
 short ioVDRefNum;
 short ioVFSID;
 unsigned long ioVBkUp;
 unsigned short ioVSeqNum;
 long ioVWrCnt;
 long ioVFilCnt;
 long ioVDirCnt;
 long ioVFndrInfo[8];
};

typedef struct HVolumeParam HVolumeParam;

struct AccessParam {
 ParamBlockHeader 
 short filler3;
 short ioDenyModes;					/*access rights data*/
 short filler4;
 char filler5;
 char ioACUser;						/*access rights for directory only*/
 long filler6;
 long ioACOwnerID;					/*owner ID*/
 long ioACGroupID;					/*group ID*/
 long ioACAccess;					/*access rights*/
};

typedef struct AccessParam AccessParam;

struct ObjParam {
 ParamBlockHeader 
 short filler7;
 short ioObjType;					/*function code*/
 StringPtr ioObjNamePtr;			/*ptr to returned creator/group name*/
 long ioObjID;						/*creator/group ID*/
 long ioReqCount;					/*size of buffer area*/
 long ioActCount;					/*length of vol parms data*/
};

typedef struct ObjParam ObjParam;

struct CopyParam {
 ParamBlockHeader 
 short ioDstVRefNum;				/*destination vol identifier*/
 short filler8;
 StringPtr ioNewName;				/*ptr to destination pathname*/
 StringPtr ioCopyName;				/*ptr to optional name*/
 long ioNewDirID;					/*destination directory ID*/
 long filler14;
 long filler15;
 long ioDirID;						/*same as in FileParam*/
};

typedef struct CopyParam CopyParam;

struct WDParam {
 ParamBlockHeader 
 short filler9;
 short ioWDIndex;
 long ioWDProcID;
 short ioWDVRefNum;
 short filler10;
 long filler11;
 long filler12;
 long filler13;
 long ioWDDirID;
};

typedef struct WDParam WDParam;

struct FIDParam {
 ParamBlockHeader 
 long filler1;
 StringPtr ioDestNamePtr;			/* dest file name */
 long filler2;
 long ioDestDirID;					/* dest file's directory id */
 long filler3;
 long filler4;
 long ioSrcDirID;					/* source file's directory id */
 short filler5;
 long ioFileID;						/* file ID */
};

typedef struct FIDParam FIDParam;

/* Catalog position record */
struct CatPositionRec {
 long initialize;
 short priv[6];
};

typedef struct CatPositionRec CatPositionRec;

struct FSSpec {
 short vRefNum;
 long parID;
 Str63 name;
};

typedef struct FSSpec FSSpec;
typedef FSSpec *FSSpecPtr, **FSSpecHandle;


typedef FSSpecPtr FSSpecArrayPtr;	/* pointer to array of FSSpecs */
/* The following are structures to be filled out with the _GetVolMountInfo call
 and passed back into the _VolumeMount call for external file system mounts. */

typedef OSType VolumeType;			/* the "signature" of the file system */




#define AppleShareMediaType 'afpm'	/* the signature for AppleShare */

struct VolMountInfoHeader {
 short length;						/* length of location data (including self) */
 VolumeType media;					/* type of media.  Variable length data follows */
};

typedef struct VolMountInfoHeader VolMountInfoHeader;
typedef VolMountInfoHeader *VolMountInfoPtr;

struct AFPVolMountInfo {
 short length;						/* length of location data (including self) */
 VolumeType media;					/* type of media */
 short flags;						/* bits for no messages, no reconnect */
 char nbpInterval;					/* NBP Interval parameter (IM2, p.322) */
 char nbpCount;						/* NBP Interval parameter (IM2, p.322) */
 short uamType;						/* User Authentication Method */
 short zoneNameOffset;				/* short positive offset from start of struct to Zone Name */
 short serverNameOffset;			/* offset to pascal Server Name string */
 short volNameOffset;				/* offset to pascal Volume Name string */
 short userNameOffset;				/* offset to pascal User Name string */
 short userPasswordOffset;			/* offset to pascal User Password string */
 short volPasswordOffset;			/* offset to pascal Volume Password string */
 char AFPData[144];					/* variable length data may follow */
};

typedef struct AFPVolMountInfo AFPVolMountInfo;
typedef AFPVolMountInfo *AFPVolMountInfoPtr;

struct CSParam {
 ParamBlockHeader 
 FSSpecPtr ioMatchPtr;				/* match array */
 long ioReqMatchCount;				/* maximum allowable matches */
 long ioActMatchCount;				/* actual match count */
 long ioSearchBits;					/* search criteria selector */
 CInfoPBPtr ioSearchInfo1;			/* search values and range lower bounds */
 CInfoPBPtr ioSearchInfo2;			/* search values and range upper bounds */
 long ioSearchTime;					/* length of time to run search */
 CatPositionRec ioCatPosition;		/* current position in the catalog */
 Ptr ioOptBuffer;					/* optional performance enhancement buffer */
 long ioOptBufSize;					/* size of buffer pointed to by ioOptBuffer */
};

typedef struct CSParam CSParam;
typedef CSParam *CSParamPtr;

struct DTPBRec {
 ParamBlockHeader 
 short ioDTRefNum;					/* desktop refnum */
 short ioIndex;
 long ioTagInfo;
 Ptr ioDTBuffer;
 long ioDTReqCount;
 long ioDTActCount;
 char ioFiller1;
 char ioIconType;
 short ioFiller2;
 long ioDirID;
 OSType ioFileCreator;
 OSType ioFileType;
 long ioFiller3;
 long ioDTLgLen;
 long ioDTPyLen;
 short ioFiller4[14];
 long ioAPPLParID;
};

typedef struct DTPBRec DTPBRec;
typedef DTPBRec *DTPBPtr;

struct ForeignPrivParam {
 ParamBlockHeader 
 long ioFiller1;
 long ioFiller2;
 Ptr ioForeignPrivBuffer;
 long ioForeignPrivActCount;
 long ioForeignPrivReqCount;
 long ioFiller3;
 long ioForeignPrivDirID;
 long ioForeignPrivInfo1;
 long ioForeignPrivInfo2;
 long ioForeignPrivInfo3;
 long ioForeignPrivInfo4;
};

typedef struct ForeignPrivParam ForeignPrivParam;
typedef ForeignPrivParam *ForeignPrivParamPtr;

union HParamBlockRec {
 HIOParam ioParam;
 HFileParam fileParam;
 HVolumeParam volumeParam;
 AccessParam accessParam;
 ObjParam objParam;
 CopyParam copyParam;
 WDParam wdParam;
 FIDParam fidParam;
 CSParam csParam;
 ForeignPrivParam foreignPrivParam;
};

typedef union HParamBlockRec HParamBlockRec;
typedef HParamBlockRec *HParmBlkPtr;

struct CMovePBRec {
 QElemPtr qLink;
 short qType;
 short ioTrap;
 Ptr ioCmdAddr;
 ProcPtr ioCompletion;
 OSErr ioResult;
 StringPtr ioNamePtr;
 short ioVRefNum;
 long filler1;
 StringPtr ioNewName;
 long filler2;
 long ioNewDirID;
 long filler3[2];
 long ioDirID;
};

typedef struct CMovePBRec CMovePBRec;
typedef CMovePBRec *CMovePBPtr;

struct WDPBRec {
 QElemPtr qLink;
 short qType;
 short ioTrap;
 Ptr ioCmdAddr;
 ProcPtr ioCompletion;
 OSErr ioResult;
 StringPtr ioNamePtr;
 short ioVRefNum;
 short filler1;
 short ioWDIndex;
 long ioWDProcID;
 short ioWDVRefNum;
 short filler2[7];
 long ioWDDirID;
};

typedef struct WDPBRec WDPBRec;
typedef WDPBRec *WDPBPtr;

struct FCBPBRec {
 QElemPtr qLink;
 short qType;
 short ioTrap;
 Ptr ioCmdAddr;
 ProcPtr ioCompletion;
 OSErr ioResult;
 StringPtr ioNamePtr;
 short ioVRefNum;
 short ioRefNum;
 short filler;
 short ioFCBIndx;
 short filler1;
 long ioFCBFlNm;
 short ioFCBFlags;
 unsigned short ioFCBStBlk;
 long ioFCBEOF;
 long ioFCBPLen;
 long ioFCBCrPs;
 short ioFCBVRefNum;
 long ioFCBClpSiz;
 long ioFCBParID;
};

typedef struct FCBPBRec FCBPBRec;
typedef FCBPBRec *FCBPBPtr;

struct VCB {
 QElemPtr qLink;
 short qType;
 short vcbFlags;
 unsigned short vcbSigWord;
 unsigned long vcbCrDate;
 unsigned long vcbLsMod;
 short vcbAtrb;
 unsigned short vcbNmFls;
 short vcbVBMSt;
 short vcbAllocPtr;
 unsigned short vcbNmAlBlks;
 long vcbAlBlkSiz;
 long vcbClpSiz;
 short vcbAlBlSt;
 long vcbNxtCNID;
 unsigned short vcbFreeBks;
 Str27 vcbVN;
 short vcbDrvNum;
 short vcbDRefNum;
 short vcbFSID;
 short vcbVRefNum;
 Ptr vcbMAdr;
 Ptr vcbBufAdr;
 short vcbMLen;
 short vcbDirIndex;
 short vcbDirBlk;
 unsigned long vcbVolBkUp;
 unsigned short vcbVSeqNum;
 long vcbWrCnt;
 long vcbXTClpSiz;
 long vcbCTClpSiz;
 unsigned short vcbNmRtDirs;
 long vcbFilCnt;
 long vcbDirCnt;
 long vcbFndrInfo[8];
 unsigned short vcbVCSize;
 unsigned short vcbVBMCSiz;
 unsigned short vcbCtlCSiz;
 unsigned short vcbXTAlBlks;
 unsigned short vcbCTAlBlks;
 short vcbXTRef;
 short vcbCTRef;
 Ptr vcbCtlBuf;
 long vcbDirIDM;
 short vcbOffsM;
};

typedef struct VCB VCB;

struct DrvQEl {
 QElemPtr qLink;
 short qType;
 short dQDrive;
 short dQRefNum;
 short dQFSID;
 unsigned short dQDrvSz;
 unsigned short dQDrvSz2;
};

typedef struct DrvQEl DrvQEl;
typedef DrvQEl *DrvQElPtr;


#ifdef __cplusplus
extern "C" {
#endif
pascal OSErr PBOpen(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBOpenSync(__A0)
pascal OSErr PBOpenSync(ParmBlkPtr paramBlock)
 = 0xA000; 
#pragma parameter __D0 PBOpenAsync(__A0)
pascal OSErr PBOpenAsync(ParmBlkPtr paramBlock)
 = 0xA400; 
pascal OSErr PBClose(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBCloseSync(__A0)
pascal OSErr PBCloseSync(ParmBlkPtr paramBlock)
 = 0xA001; 
#pragma parameter __D0 PBCloseAsync(__A0)
pascal OSErr PBCloseAsync(ParmBlkPtr paramBlock)
 = 0xA401; 
pascal OSErr PBRead(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBReadSync(__A0)
pascal OSErr PBReadSync(ParmBlkPtr paramBlock)
 = 0xA002; 
#pragma parameter __D0 PBReadAsync(__A0)
pascal OSErr PBReadAsync(ParmBlkPtr paramBlock)
 = 0xA402; 
pascal OSErr PBWrite(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBWriteSync(__A0)
pascal OSErr PBWriteSync(ParmBlkPtr paramBlock)
 = 0xA003; 
#pragma parameter __D0 PBWriteAsync(__A0)
pascal OSErr PBWriteAsync(ParmBlkPtr paramBlock)
 = 0xA403; 
pascal OSErr PBGetVInfo(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBGetVInfoSync(__A0)
pascal OSErr PBGetVInfoSync(ParmBlkPtr paramBlock)
 = 0xA007; 
#pragma parameter __D0 PBGetVInfoAsync(__A0)
pascal OSErr PBGetVInfoAsync(ParmBlkPtr paramBlock)
 = 0xA407; 
pascal OSErr PBGetVol(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBGetVolSync(__A0)
pascal OSErr PBGetVolSync(ParmBlkPtr paramBlock)
 = 0xA014; 
#pragma parameter __D0 PBGetVolAsync(__A0)
pascal OSErr PBGetVolAsync(ParmBlkPtr paramBlock)
 = 0xA414; 
pascal OSErr PBSetVol(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBSetVolSync(__A0)
pascal OSErr PBSetVolSync(ParmBlkPtr paramBlock)
 = 0xA015; 
#pragma parameter __D0 PBSetVolAsync(__A0)
pascal OSErr PBSetVolAsync(ParmBlkPtr paramBlock)
 = 0xA415; 
pascal OSErr PBFlushVol(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBFlushVolSync(__A0)
pascal OSErr PBFlushVolSync(ParmBlkPtr paramBlock)
 = 0xA013; 
#pragma parameter __D0 PBFlushVolAsync(__A0)
pascal OSErr PBFlushVolAsync(ParmBlkPtr paramBlock)
 = 0xA413; 
pascal OSErr PBCreate(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBCreateSync(__A0)
pascal OSErr PBCreateSync(ParmBlkPtr paramBlock)
 = 0xA008; 
#pragma parameter __D0 PBCreateAsync(__A0)
pascal OSErr PBCreateAsync(ParmBlkPtr paramBlock)
 = 0xA408; 
pascal OSErr PBDelete(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDeleteSync(__A0)
pascal OSErr PBDeleteSync(ParmBlkPtr paramBlock)
 = 0xA009; 
#pragma parameter __D0 PBDeleteAsync(__A0)
pascal OSErr PBDeleteAsync(ParmBlkPtr paramBlock)
 = 0xA409; 
pascal OSErr PBOpenDF(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBOpenDFSync(__A0)
pascal OSErr PBOpenDFSync(ParmBlkPtr paramBlock)
 = {0x701A,0xA060}; 
#pragma parameter __D0 PBOpenDFAsync(__A0)
pascal OSErr PBOpenDFAsync(ParmBlkPtr paramBlock)
 = {0x701A,0xA460}; 
pascal OSErr PBOpenRF(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBOpenRFSync(__A0)
pascal OSErr PBOpenRFSync(ParmBlkPtr paramBlock)
 = 0xA00A; 
#pragma parameter __D0 PBOpenRFAsync(__A0)
pascal OSErr PBOpenRFAsync(ParmBlkPtr paramBlock)
 = 0xA40A; 
pascal OSErr PBRename(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBRenameSync(__A0)
pascal OSErr PBRenameSync(ParmBlkPtr paramBlock)
 = 0xA00B; 
#pragma parameter __D0 PBRenameAsync(__A0)
pascal OSErr PBRenameAsync(ParmBlkPtr paramBlock)
 = 0xA40B; 
pascal OSErr PBGetFInfo(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBGetFInfoSync(__A0)
pascal OSErr PBGetFInfoSync(ParmBlkPtr paramBlock)
 = 0xA00C; 
#pragma parameter __D0 PBGetFInfoAsync(__A0)
pascal OSErr PBGetFInfoAsync(ParmBlkPtr paramBlock)
 = 0xA40C; 
pascal OSErr PBSetFInfo(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBSetFInfoSync(__A0)
pascal OSErr PBSetFInfoSync(ParmBlkPtr paramBlock)
 = 0xA00D; 
#pragma parameter __D0 PBSetFInfoAsync(__A0)
pascal OSErr PBSetFInfoAsync(ParmBlkPtr paramBlock)
 = 0xA40D; 
pascal OSErr PBSetFLock(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBSetFLockSync(__A0)
pascal OSErr PBSetFLockSync(ParmBlkPtr paramBlock)
 = 0xA041; 
#pragma parameter __D0 PBSetFLockAsync(__A0)
pascal OSErr PBSetFLockAsync(ParmBlkPtr paramBlock)
 = 0xA441; 
pascal OSErr PBRstFLock(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBRstFLockSync(__A0)
pascal OSErr PBRstFLockSync(ParmBlkPtr paramBlock)
 = 0xA042; 
#pragma parameter __D0 PBRstFLockAsync(__A0)
pascal OSErr PBRstFLockAsync(ParmBlkPtr paramBlock)
 = 0xA442; 
pascal OSErr PBSetFVers(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBSetFVersSync(__A0)
pascal OSErr PBSetFVersSync(ParmBlkPtr paramBlock)
 = 0xA043; 
#pragma parameter __D0 PBSetFVersAsync(__A0)
pascal OSErr PBSetFVersAsync(ParmBlkPtr paramBlock)
 = 0xA443; 
pascal OSErr PBAllocate(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBAllocateSync(__A0)
pascal OSErr PBAllocateSync(ParmBlkPtr paramBlock)
 = 0xA010; 
#pragma parameter __D0 PBAllocateAsync(__A0)
pascal OSErr PBAllocateAsync(ParmBlkPtr paramBlock)
 = 0xA410; 
pascal OSErr PBGetEOF(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBGetEOFSync(__A0)
pascal OSErr PBGetEOFSync(ParmBlkPtr paramBlock)
 = 0xA011; 
#pragma parameter __D0 PBGetEOFAsync(__A0)
pascal OSErr PBGetEOFAsync(ParmBlkPtr paramBlock)
 = 0xA411; 
pascal OSErr PBSetEOF(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBSetEOFSync(__A0)
pascal OSErr PBSetEOFSync(ParmBlkPtr paramBlock)
 = 0xA012; 
#pragma parameter __D0 PBSetEOFAsync(__A0)
pascal OSErr PBSetEOFAsync(ParmBlkPtr paramBlock)
 = 0xA412; 
pascal OSErr PBGetFPos(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBGetFPosSync(__A0)
pascal OSErr PBGetFPosSync(ParmBlkPtr paramBlock)
 = 0xA018; 
#pragma parameter __D0 PBGetFPosAsync(__A0)
pascal OSErr PBGetFPosAsync(ParmBlkPtr paramBlock)
 = 0xA418; 
pascal OSErr PBSetFPos(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBSetFPosSync(__A0)
pascal OSErr PBSetFPosSync(ParmBlkPtr paramBlock)
 = 0xA044; 
#pragma parameter __D0 PBSetFPosAsync(__A0)
pascal OSErr PBSetFPosAsync(ParmBlkPtr paramBlock)
 = 0xA444; 
pascal OSErr PBFlushFile(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBFlushFileSync(__A0)
pascal OSErr PBFlushFileSync(ParmBlkPtr paramBlock)
 = 0xA045; 
#pragma parameter __D0 PBFlushFileAsync(__A0)
pascal OSErr PBFlushFileAsync(ParmBlkPtr paramBlock)
 = 0xA445; 
#pragma parameter __D0 PBMountVol(__A0)
pascal OSErr PBMountVol(ParmBlkPtr paramBlock)
 = 0xA00F; 
#pragma parameter __D0 PBUnmountVol(__A0)
pascal OSErr PBUnmountVol(ParmBlkPtr paramBlock)
 = 0xA00E; 
#pragma parameter __D0 PBEject(__A0)
pascal OSErr PBEject(ParmBlkPtr paramBlock)
 = 0xA017; 
#pragma parameter __D0 PBOffLine(__A0)
pascal OSErr PBOffLine(ParmBlkPtr paramBlock)
 = 0xA035; 

pascal OSErr PBCatSearch(CSParamPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBCatSearchSync(__A0)
pascal OSErr PBCatSearchSync(CSParamPtr paramBlock)
 = {0x7018,0xA260}; 
#pragma parameter __D0 PBCatSearchAsync(__A0)
pascal OSErr PBCatSearchAsync(CSParamPtr paramBlock)
 = {0x7018,0xA660}; 

pascal void AddDrive(short drvrRefNum,short drvNum,DrvQElPtr qEl); 
pascal OSErr FSOpen(ConstStr255Param fileName,short vRefNum,short *refNum); 
pascal OSErr OpenDF(ConstStr255Param fileName,short vRefNum,short *refNum); 
OSErr fsopen(char *fileName,short vRefNum,short *refNum); 
pascal OSErr FSClose(short refNum); 
pascal OSErr FSRead(short refNum,long *count,void *buffPtr); 
pascal OSErr FSWrite(short refNum,long *count,const void *buffPtr); 
pascal OSErr GetVInfo(short drvNum,StringPtr volName,short *vRefNum,long *freeBytes); 
OSErr getvinfo(short drvNum,char *volName,short *vRefNum,long *freeBytes); 
pascal OSErr GetFInfo(ConstStr255Param fileName,short vRefNum,FInfo *fndrInfo); 
OSErr getfinfo(char *fileName,short vRefNum,FInfo *fndrInfo); 
pascal OSErr GetVol(StringPtr volName,short *vRefNum); 
OSErr getvol(char *volName,short *vRefNum); 
pascal OSErr SetVol(StringPtr volName,short vRefNum); 
OSErr setvol(char *volName,short vRefNum); 
pascal OSErr UnmountVol(StringPtr volName,short vRefNum); 
OSErr unmountvol(char *volName,short vRefNum); 
pascal OSErr Eject(StringPtr volName,short vRefNum); 
OSErr eject(char *volName,short vRefNum); 
pascal OSErr FlushVol(StringPtr volName,short vRefNum); 
OSErr flushvol(char *volName,short vRefNum); 
pascal OSErr Create(ConstStr255Param fileName,short vRefNum,OSType creator,
 OSType fileType); 
OSErr create(char *fileName,short vRefNum,OSType creator,OSType fileType); 
pascal OSErr FSDelete(ConstStr255Param fileName,short vRefNum); 
OSErr fsdelete(char *fileName,short vRefNum); 
pascal OSErr OpenRF(ConstStr255Param fileName,short vRefNum,short *refNum); 
OSErr openrf(char *fileName,short vRefNum,short *refNum); 
pascal OSErr Rename(ConstStr255Param oldName,short vRefNum,ConstStr255Param newName); 
OSErr fsrename(char *oldName,short vRefNum,char *newName); 
pascal OSErr SetFInfo(ConstStr255Param fileName,short vRefNum,const FInfo *fndrInfo); 
OSErr setfinfo(char *fileName,short vRefNum,FInfo *fndrInfo); 
pascal OSErr SetFLock(ConstStr255Param fileName,short vRefNum); 
OSErr setflock(char *fileName,short vRefNum); 
pascal OSErr RstFLock(ConstStr255Param fileName,short vRefNum); 
OSErr rstflock(char *fileName,short vRefNum); 
pascal OSErr Allocate(short refNum,long *count); 
pascal OSErr GetEOF(short refNum,long *logEOF); 
pascal OSErr SetEOF(short refNum,long logEOF); 
pascal OSErr GetFPos(short refNum,long *filePos); 
pascal OSErr SetFPos(short refNum,short posMode,long posOff); 
pascal OSErr GetVRefNum(short fileRefNum,short *vRefNum); 

pascal OSErr PBOpenWD(WDPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBOpenWDSync(__A0)
pascal OSErr PBOpenWDSync(WDPBPtr paramBlock)
 = {0x7001,0xA260}; 
#pragma parameter __D0 PBOpenWDAsync(__A0)
pascal OSErr PBOpenWDAsync(WDPBPtr paramBlock)
 = {0x7001,0xA660}; 
pascal OSErr PBCloseWD(WDPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBCloseWDSync(__A0)
pascal OSErr PBCloseWDSync(WDPBPtr paramBlock)
 = {0x7002,0xA260}; 
#pragma parameter __D0 PBCloseWDAsync(__A0)
pascal OSErr PBCloseWDAsync(WDPBPtr paramBlock)
 = {0x7002,0xA660}; 
pascal OSErr PBHSetVol(WDPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHSetVolSync(__A0)
pascal OSErr PBHSetVolSync(WDPBPtr paramBlock)
 = 0xA215; 
#pragma parameter __D0 PBHSetVolAsync(__A0)
pascal OSErr PBHSetVolAsync(WDPBPtr paramBlock)
 = 0xA615; 
pascal OSErr PBHGetVol(WDPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHGetVolSync(__A0)
pascal OSErr PBHGetVolSync(WDPBPtr paramBlock)
 = 0xA214; 
#pragma parameter __D0 PBHGetVolAsync(__A0)
pascal OSErr PBHGetVolAsync(WDPBPtr paramBlock)
 = 0xA614; 
pascal OSErr PBCatMove(CMovePBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBCatMoveSync(__A0)
pascal OSErr PBCatMoveSync(CMovePBPtr paramBlock)
 = {0x7005,0xA260}; 
#pragma parameter __D0 PBCatMoveAsync(__A0)
pascal OSErr PBCatMoveAsync(CMovePBPtr paramBlock)
 = {0x7005,0xA660}; 
pascal OSErr PBDirCreate(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDirCreateSync(__A0)
pascal OSErr PBDirCreateSync(HParmBlkPtr paramBlock)
 = {0x7006,0xA260}; 
#pragma parameter __D0 PBDirCreateAsync(__A0)
pascal OSErr PBDirCreateAsync(HParmBlkPtr paramBlock)
 = {0x7006,0xA660}; 
pascal OSErr PBGetWDInfo(WDPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBGetWDInfoSync(__A0)
pascal OSErr PBGetWDInfoSync(WDPBPtr paramBlock)
 = {0x7007,0xA260}; 
#pragma parameter __D0 PBGetWDInfoAsync(__A0)
pascal OSErr PBGetWDInfoAsync(WDPBPtr paramBlock)
 = {0x7007,0xA660}; 
pascal OSErr PBGetFCBInfo(FCBPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBGetFCBInfoSync(__A0)
pascal OSErr PBGetFCBInfoSync(FCBPBPtr paramBlock)
 = {0x7008,0xA260}; 
#pragma parameter __D0 PBGetFCBInfoAsync(__A0)
pascal OSErr PBGetFCBInfoAsync(FCBPBPtr paramBlock)
 = {0x7008,0xA660}; 
pascal OSErr PBGetCatInfo(CInfoPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBGetCatInfoSync(__A0)
pascal OSErr PBGetCatInfoSync(CInfoPBPtr paramBlock)
 = {0x7009,0xA260}; 
#pragma parameter __D0 PBGetCatInfoAsync(__A0)
pascal OSErr PBGetCatInfoAsync(CInfoPBPtr paramBlock)
 = {0x7009,0xA660}; 
pascal OSErr PBSetCatInfo(CInfoPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBSetCatInfoSync(__A0)
pascal OSErr PBSetCatInfoSync(CInfoPBPtr paramBlock)
 = {0x700A,0xA260}; 
#pragma parameter __D0 PBSetCatInfoAsync(__A0)
pascal OSErr PBSetCatInfoAsync(CInfoPBPtr paramBlock)
 = {0x700A,0xA660}; 

pascal OSErr PBAllocContig(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBAllocContigSync(__A0)
pascal OSErr PBAllocContigSync(ParmBlkPtr paramBlock)
 = 0xA210; 
#pragma parameter __D0 PBAllocContigAsync(__A0)
pascal OSErr PBAllocContigAsync(ParmBlkPtr paramBlock)
 = 0xA610; 
pascal OSErr PBLockRange(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBLockRangeSync(__A0)
pascal OSErr PBLockRangeSync(ParmBlkPtr paramBlock)
 = {0x7010,0xA260}; 
#pragma parameter __D0 PBLockRangeAsync(__A0)
pascal OSErr PBLockRangeAsync(ParmBlkPtr paramBlock)
 = {0x7010,0xA660}; 
pascal OSErr PBUnlockRange(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBUnlockRangeSync(__A0)
pascal OSErr PBUnlockRangeSync(ParmBlkPtr paramBlock)
 = {0x7011,0xA260}; 
#pragma parameter __D0 PBUnlockRangeAsync(__A0)
pascal OSErr PBUnlockRangeAsync(ParmBlkPtr paramBlock)
 = {0x7011,0xA660}; 
pascal OSErr PBSetVInfo(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBSetVInfoSync(__A0)
pascal OSErr PBSetVInfoSync(HParmBlkPtr paramBlock)
 = {0x700B,0xA260}; 
#pragma parameter __D0 PBSetVInfoAsync(__A0)
pascal OSErr PBSetVInfoAsync(HParmBlkPtr paramBlock)
 = {0x700B,0xA660}; 
pascal OSErr PBHGetVInfo(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHGetVInfoSync(__A0)
pascal OSErr PBHGetVInfoSync(HParmBlkPtr paramBlock)
 = 0xA207; 
#pragma parameter __D0 PBHGetVInfoAsync(__A0)
pascal OSErr PBHGetVInfoAsync(HParmBlkPtr paramBlock)
 = 0xA607; 
pascal OSErr PBHOpen(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHOpenSync(__A0)
pascal OSErr PBHOpenSync(HParmBlkPtr paramBlock)
 = 0xA200; 
#pragma parameter __D0 PBHOpenAsync(__A0)
pascal OSErr PBHOpenAsync(HParmBlkPtr paramBlock)
 = 0xA600; 
pascal OSErr PBHOpenRF(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHOpenRFSync(__A0)
pascal OSErr PBHOpenRFSync(HParmBlkPtr paramBlock)
 = 0xA20A; 
#pragma parameter __D0 PBHOpenRFAsync(__A0)
pascal OSErr PBHOpenRFAsync(HParmBlkPtr paramBlock)
 = 0xA60A; 
pascal OSErr PBHOpenDF(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHOpenDFSync(__A0)
pascal OSErr PBHOpenDFSync(HParmBlkPtr paramBlock)
 = {0x701A,0xA260}; 
#pragma parameter __D0 PBHOpenDFAsync(__A0)
pascal OSErr PBHOpenDFAsync(HParmBlkPtr paramBlock)
 = {0x701A,0xA660}; 

pascal OSErr PBHCreate(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHCreateSync(__A0)
pascal OSErr PBHCreateSync(HParmBlkPtr paramBlock)
 = 0xA208; 
#pragma parameter __D0 PBHCreateAsync(__A0)
pascal OSErr PBHCreateAsync(HParmBlkPtr paramBlock)
 = 0xA608; 
pascal OSErr PBHDelete(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHDeleteSync(__A0)
pascal OSErr PBHDeleteSync(HParmBlkPtr paramBlock)
 = 0xA209; 
#pragma parameter __D0 PBHDeleteAsync(__A0)
pascal OSErr PBHDeleteAsync(HParmBlkPtr paramBlock)
 = 0xA609; 
pascal OSErr PBHRename(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHRenameSync(__A0)
pascal OSErr PBHRenameSync(HParmBlkPtr paramBlock)
 = 0xA20B; 
#pragma parameter __D0 PBHRenameAsync(__A0)
pascal OSErr PBHRenameAsync(HParmBlkPtr paramBlock)
 = 0xA60B; 
pascal OSErr PBHRstFLock(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHRstFLockSync(__A0)
pascal OSErr PBHRstFLockSync(HParmBlkPtr paramBlock)
 = 0xA242; 
#pragma parameter __D0 PBHRstFLockAsync(__A0)
pascal OSErr PBHRstFLockAsync(HParmBlkPtr paramBlock)
 = 0xA642; 
pascal OSErr PBHSetFLock(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHSetFLockSync(__A0)
pascal OSErr PBHSetFLockSync(HParmBlkPtr paramBlock)
 = 0xA241; 
#pragma parameter __D0 PBHSetFLockAsync(__A0)
pascal OSErr PBHSetFLockAsync(HParmBlkPtr paramBlock)
 = 0xA641; 
pascal OSErr PBHGetFInfo(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHGetFInfoSync(__A0)
pascal OSErr PBHGetFInfoSync(HParmBlkPtr paramBlock)
 = 0xA20C; 
#pragma parameter __D0 PBHGetFInfoAsync(__A0)
pascal OSErr PBHGetFInfoAsync(HParmBlkPtr paramBlock)
 = 0xA60C; 
pascal OSErr PBHSetFInfo(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHSetFInfoSync(__A0)
pascal OSErr PBHSetFInfoSync(HParmBlkPtr paramBlock)
 = 0xA20D; 
#pragma parameter __D0 PBHSetFInfoAsync(__A0)
pascal OSErr PBHSetFInfoAsync(HParmBlkPtr paramBlock)
 = 0xA60D; 

pascal OSErr PBMakeFSSpec(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBMakeFSSpecSync(__A0)
pascal OSErr PBMakeFSSpecSync(HParmBlkPtr paramBlock)
 = {0x701B,0xA260}; 
#pragma parameter __D0 PBMakeFSSpecAsync(__A0)
pascal OSErr PBMakeFSSpecAsync(HParmBlkPtr paramBlock)
 = {0x701B,0xA660}; 

pascal void FInitQueue(void)
 = 0xA016; 
#define GetFSQHdr() ((QHdrPtr) 0x0360)
#define GetDrvQHdr() ((QHdrPtr) 0x0308)
#define GetVCBQHdr() ((QHdrPtr) 0x0356)
pascal OSErr HGetVol(StringPtr volName,short *vRefNum,long *dirID); 
pascal OSErr HSetVol(StringPtr volName,short vRefNum,long dirID); 
pascal OSErr HOpen(short vRefNum,long dirID,ConstStr255Param fileName,char permission,
 short *refNum); 
pascal OSErr HOpenDF(short vRefNum,long dirID,ConstStr255Param fileName,
 char permission,short *refNum); 
pascal OSErr HOpenRF(short vRefNum,long dirID,ConstStr255Param fileName,
 char permission,short *refNum); 
pascal OSErr AllocContig(short refNum,long *count); 
pascal OSErr HCreate(short vRefNum,long dirID,ConstStr255Param fileName,
 OSType creator,OSType fileType); 
pascal OSErr DirCreate(short vRefNum,long parentDirID,ConstStr255Param directoryName,
 long *createdDirID); 
pascal OSErr HDelete(short vRefNum,long dirID,ConstStr255Param fileName); 
pascal OSErr HGetFInfo(short vRefNum,long dirID,ConstStr255Param fileName,
 FInfo *fndrInfo); 
pascal OSErr HSetFInfo(short vRefNum,long dirID,ConstStr255Param fileName,
 const FInfo *fndrInfo); 
pascal OSErr HSetFLock(short vRefNum,long dirID,ConstStr255Param fileName); 
pascal OSErr HRstFLock(short vRefNum,long dirID,ConstStr255Param fileName); 
pascal OSErr HRename(short vRefNum,long dirID,ConstStr255Param oldName,
 ConstStr255Param newName); 
pascal OSErr CatMove(short vRefNum,long dirID,ConstStr255Param oldName,
 long newDirID,ConstStr255Param newName); 
pascal OSErr OpenWD(short vRefNum,long dirID,long procID,short *wdRefNum); 
pascal OSErr CloseWD(short wdRefNum); 
pascal OSErr GetWDInfo(short wdRefNum,short *vRefNum,long *dirID,long *procID); 
/*  shared environment  */
pascal OSErr PBHGetVolParms(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHGetVolParmsSync(__A0)
pascal OSErr PBHGetVolParmsSync(HParmBlkPtr paramBlock)
 = {0x7030,0xA260}; 
#pragma parameter __D0 PBHGetVolParmsAsync(__A0)
pascal OSErr PBHGetVolParmsAsync(HParmBlkPtr paramBlock)
 = {0x7030,0xA660}; 
pascal OSErr PBHGetLogInInfo(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHGetLogInInfoSync(__A0)
pascal OSErr PBHGetLogInInfoSync(HParmBlkPtr paramBlock)
 = {0x7031,0xA260}; 
#pragma parameter __D0 PBHGetLogInInfoAsync(__A0)
pascal OSErr PBHGetLogInInfoAsync(HParmBlkPtr paramBlock)
 = {0x7031,0xA660}; 
pascal OSErr PBHGetDirAccess(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHGetDirAccessSync(__A0)
pascal OSErr PBHGetDirAccessSync(HParmBlkPtr paramBlock)
 = {0x7032,0xA260}; 
#pragma parameter __D0 PBHGetDirAccessAsync(__A0)
pascal OSErr PBHGetDirAccessAsync(HParmBlkPtr paramBlock)
 = {0x7032,0xA660}; 
pascal OSErr PBHSetDirAccess(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHSetDirAccessSync(__A0)
pascal OSErr PBHSetDirAccessSync(HParmBlkPtr paramBlock)
 = {0x7033,0xA260}; 
#pragma parameter __D0 PBHSetDirAccessAsync(__A0)
pascal OSErr PBHSetDirAccessAsync(HParmBlkPtr paramBlock)
 = {0x7033,0xA660}; 
pascal OSErr PBHMapID(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHMapIDSync(__A0)
pascal OSErr PBHMapIDSync(HParmBlkPtr paramBlock)
 = {0x7034,0xA260}; 
#pragma parameter __D0 PBHMapIDAsync(__A0)
pascal OSErr PBHMapIDAsync(HParmBlkPtr paramBlock)
 = {0x7034,0xA660}; 
pascal OSErr PBHMapName(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHMapNameSync(__A0)
pascal OSErr PBHMapNameSync(HParmBlkPtr paramBlock)
 = {0x7035,0xA260}; 
#pragma parameter __D0 PBHMapNameAsync(__A0)
pascal OSErr PBHMapNameAsync(HParmBlkPtr paramBlock)
 = {0x7035,0xA660}; 
pascal OSErr PBHCopyFile(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHCopyFileSync(__A0)
pascal OSErr PBHCopyFileSync(HParmBlkPtr paramBlock)
 = {0x7036,0xA260}; 
#pragma parameter __D0 PBHCopyFileAsync(__A0)
pascal OSErr PBHCopyFileAsync(HParmBlkPtr paramBlock)
 = {0x7036,0xA660}; 
pascal OSErr PBHMoveRename(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHMoveRenameSync(__A0)
pascal OSErr PBHMoveRenameSync(HParmBlkPtr paramBlock)
 = {0x7037,0xA260}; 
#pragma parameter __D0 PBHMoveRenameAsync(__A0)
pascal OSErr PBHMoveRenameAsync(HParmBlkPtr paramBlock)
 = {0x7037,0xA660}; 
pascal OSErr PBHOpenDeny(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHOpenDenySync(__A0)
pascal OSErr PBHOpenDenySync(HParmBlkPtr paramBlock)
 = {0x7038,0xA260}; 
#pragma parameter __D0 PBHOpenDenyAsync(__A0)
pascal OSErr PBHOpenDenyAsync(HParmBlkPtr paramBlock)
 = {0x7038,0xA660}; 
pascal OSErr PBHOpenRFDeny(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBHOpenRFDenySync(__A0)
pascal OSErr PBHOpenRFDenySync(HParmBlkPtr paramBlock)
 = {0x7039,0xA260}; 
#pragma parameter __D0 PBHOpenRFDenyAsync(__A0)
pascal OSErr PBHOpenRFDenyAsync(HParmBlkPtr paramBlock)
 = {0x7039,0xA660}; 

pascal OSErr PBExchangeFiles(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBExchangeFilesSync(__A0)
pascal OSErr PBExchangeFilesSync(HParmBlkPtr paramBlock)
 = {0x7017,0xA260}; 
#pragma parameter __D0 PBExchangeFilesAsync(__A0)
pascal OSErr PBExchangeFilesAsync(HParmBlkPtr paramBlock)
 = {0x7017,0xA660}; 
pascal OSErr PBCreateFileIDRef(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBCreateFileIDRefSync(__A0)
pascal OSErr PBCreateFileIDRefSync(HParmBlkPtr paramBlock)
 = {0x7014,0xA260}; 
#pragma parameter __D0 PBCreateFileIDRefAsync(__A0)
pascal OSErr PBCreateFileIDRefAsync(HParmBlkPtr paramBlock)
 = {0x7014,0xA660}; 
pascal OSErr PBResolveFileIDRef(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBResolveFileIDRefSync(__A0)
pascal OSErr PBResolveFileIDRefSync(HParmBlkPtr paramBlock)
 = {0x7016,0xA260}; 
#pragma parameter __D0 PBResolveFileIDRefAsync(__A0)
pascal OSErr PBResolveFileIDRefAsync(HParmBlkPtr paramBlock)
 = {0x7016,0xA660}; 
pascal OSErr PBDeleteFileIDRef(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDeleteFileIDRefSync(__A0)
pascal OSErr PBDeleteFileIDRefSync(HParmBlkPtr paramBlock)
 = {0x7015,0xA260}; 
#pragma parameter __D0 PBDeleteFileIDRefAsync(__A0)
pascal OSErr PBDeleteFileIDRefAsync(HParmBlkPtr paramBlock)
 = {0x7015,0xA660}; 

pascal OSErr PBGetForeignPrivs(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBGetForeignPrivsSync(__A0)
pascal OSErr PBGetForeignPrivsSync(HParmBlkPtr paramBlock)
 = {0x7060,0xA260}; 
#pragma parameter __D0 PBGetForeignPrivsAsync(__A0)
pascal OSErr PBGetForeignPrivsAsync(HParmBlkPtr paramBlock)
 = {0x7060,0xA660}; 
pascal OSErr PBSetForeignPrivs(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBSetForeignPrivsSync(__A0)
pascal OSErr PBSetForeignPrivsSync(HParmBlkPtr paramBlock)
 = {0x7061,0xA260}; 
#pragma parameter __D0 PBSetForeignPrivsAsync(__A0)
pascal OSErr PBSetForeignPrivsAsync(HParmBlkPtr paramBlock)
 = {0x7061,0xA660}; 
/*  Desktop Manager  */
#pragma parameter __D0 PBDTGetPath(__A0)
pascal OSErr PBDTGetPath(DTPBPtr paramBlock)
 = {0x7020,0xA260}; 
#pragma parameter __D0 PBDTCloseDown(__A0)
pascal OSErr PBDTCloseDown(DTPBPtr paramBlock)
 = {0x7021,0xA260}; 
pascal OSErr PBDTAddIcon(DTPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDTAddIconSync(__A0)
pascal OSErr PBDTAddIconSync(DTPBPtr paramBlock)
 = {0x7022,0xA260}; 
#pragma parameter __D0 PBDTAddIconAsync(__A0)
pascal OSErr PBDTAddIconAsync(DTPBPtr paramBlock)
 = {0x7022,0xA660}; 
pascal OSErr PBDTGetIcon(DTPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDTGetIconSync(__A0)
pascal OSErr PBDTGetIconSync(DTPBPtr paramBlock)
 = {0x7023,0xA260}; 
#pragma parameter __D0 PBDTGetIconAsync(__A0)
pascal OSErr PBDTGetIconAsync(DTPBPtr paramBlock)
 = {0x7023,0xA660}; 
pascal OSErr PBDTGetIconInfo(DTPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDTGetIconInfoSync(__A0)
pascal OSErr PBDTGetIconInfoSync(DTPBPtr paramBlock)
 = {0x7024,0xA260}; 
#pragma parameter __D0 PBDTGetIconInfoAsync(__A0)
pascal OSErr PBDTGetIconInfoAsync(DTPBPtr paramBlock)
 = {0x7024,0xA660}; 
pascal OSErr PBDTAddAPPL(DTPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDTAddAPPLSync(__A0)
pascal OSErr PBDTAddAPPLSync(DTPBPtr paramBlock)
 = {0x7025,0xA260}; 
#pragma parameter __D0 PBDTAddAPPLAsync(__A0)
pascal OSErr PBDTAddAPPLAsync(DTPBPtr paramBlock)
 = {0x7025,0xA660}; 
pascal OSErr PBDTRemoveAPPL(DTPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDTRemoveAPPLSync(__A0)
pascal OSErr PBDTRemoveAPPLSync(DTPBPtr paramBlock)
 = {0x7026,0xA260}; 
#pragma parameter __D0 PBDTRemoveAPPLAsync(__A0)
pascal OSErr PBDTRemoveAPPLAsync(DTPBPtr paramBlock)
 = {0x7026,0xA660}; 
pascal OSErr PBDTGetAPPL(DTPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDTGetAPPLSync(__A0)
pascal OSErr PBDTGetAPPLSync(DTPBPtr paramBlock)
 = {0x7027,0xA260}; 
#pragma parameter __D0 PBDTGetAPPLAsync(__A0)
pascal OSErr PBDTGetAPPLAsync(DTPBPtr paramBlock)
 = {0x7027,0xA660}; 
pascal OSErr PBDTSetComment(DTPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDTSetCommentSync(__A0)
pascal OSErr PBDTSetCommentSync(DTPBPtr paramBlock)
 = {0x7028,0xA260}; 
#pragma parameter __D0 PBDTSetCommentAsync(__A0)
pascal OSErr PBDTSetCommentAsync(DTPBPtr paramBlock)
 = {0x7028,0xA660}; 
pascal OSErr PBDTRemoveComment(DTPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDTRemoveCommentSync(__A0)
pascal OSErr PBDTRemoveCommentSync(DTPBPtr paramBlock)
 = {0x7029,0xA260}; 
#pragma parameter __D0 PBDTRemoveCommentAsync(__A0)
pascal OSErr PBDTRemoveCommentAsync(DTPBPtr paramBlock)
 = {0x7029,0xA660}; 
pascal OSErr PBDTGetComment(DTPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDTGetCommentSync(__A0)
pascal OSErr PBDTGetCommentSync(DTPBPtr paramBlock)
 = {0x702A,0xA260}; 
#pragma parameter __D0 PBDTGetCommentAsync(__A0)
pascal OSErr PBDTGetCommentAsync(DTPBPtr paramBlock)
 = {0x702A,0xA660}; 
pascal OSErr PBDTFlush(DTPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDTFlushSync(__A0)
pascal OSErr PBDTFlushSync(DTPBPtr paramBlock)
 = {0x702B,0xA260}; 
#pragma parameter __D0 PBDTFlushAsync(__A0)
pascal OSErr PBDTFlushAsync(DTPBPtr paramBlock)
 = {0x702B,0xA660}; 
pascal OSErr PBDTReset(DTPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDTResetSync(__A0)
pascal OSErr PBDTResetSync(DTPBPtr paramBlock)
 = {0x702C,0xA260}; 
#pragma parameter __D0 PBDTResetAsync(__A0)
pascal OSErr PBDTResetAsync(DTPBPtr paramBlock)
 = {0x702C,0xA660}; 
pascal OSErr PBDTGetInfo(DTPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDTGetInfoSync(__A0)
pascal OSErr PBDTGetInfoSync(DTPBPtr paramBlock)
 = {0x702D,0xA260}; 
#pragma parameter __D0 PBDTGetInfoAsync(__A0)
pascal OSErr PBDTGetInfoAsync(DTPBPtr paramBlock)
 = {0x702D,0xA660}; 
#pragma parameter __D0 PBDTOpenInform(__A0)
pascal OSErr PBDTOpenInform(DTPBPtr paramBlock)
 = {0x702E,0xA060}; 
pascal OSErr PBDTDelete(DTPBPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBDTDeleteSync(__A0)
pascal OSErr PBDTDeleteSync(DTPBPtr paramBlock)
 = {0x702F,0xA060}; 
#pragma parameter __D0 PBDTDeleteAsync(__A0)
pascal OSErr PBDTDeleteAsync(DTPBPtr paramBlock)
 = {0x702F,0xA460}; 
/*  VolumeMount traps  */
#pragma parameter __D0 PBGetVolMountInfoSize(__A0)
pascal OSErr PBGetVolMountInfoSize(ParmBlkPtr paramBlock)
 = {0x703F,0xA260}; 
#pragma parameter __D0 PBGetVolMountInfo(__A0)
pascal OSErr PBGetVolMountInfo(ParmBlkPtr paramBlock)
 = {0x7040,0xA260}; 
#pragma parameter __D0 PBVolumeMount(__A0)
pascal OSErr PBVolumeMount(ParmBlkPtr paramBlock)
 = {0x7041,0xA260}; 
/*  FSp traps  */
pascal OSErr FSMakeFSSpec(short vRefNum,long dirID,ConstStr255Param fileName,
 FSSpecPtr spec)
 = {0x303C,0x0001,0xAA52}; 
pascal OSErr FSpOpenDF(const FSSpec *spec,char permission,short *refNum)
 = {0x303C,0x0002,0xAA52}; 
pascal OSErr FSpOpenRF(const FSSpec  *spec,char permission,short *refNum)
 = {0x303C,0x0003,0xAA52}; 
pascal OSErr FSpCreate(const FSSpec  *spec,OSType creator,OSType fileType,
 ScriptCode scriptTag)
 = {0x303C,0x0004,0xAA52}; 
pascal OSErr FSpDirCreate(const FSSpec *spec,ScriptCode scriptTag,long *createdDirID)
 = {0x303C,0x0005,0xAA52}; 
pascal OSErr FSpDelete(const FSSpec *spec)
 = {0x303C,0x0006,0xAA52}; 
pascal OSErr FSpGetFInfo(const FSSpec *spec,FInfo *fndrInfo)
 = {0x303C,0x0007,0xAA52}; 
pascal OSErr FSpSetFInfo(const FSSpec *spec,const FInfo *fndrInfo)
 = {0x303C,0x0008,0xAA52}; 
pascal OSErr FSpSetFLock(const FSSpec *spec)
 = {0x303C,0x0009,0xAA52}; 
pascal OSErr FSpRstFLock(const FSSpec *spec)
 = {0x303C,0x000A,0xAA52}; 
pascal OSErr FSpRename(const FSSpec *spec,ConstStr255Param newName)
 = {0x303C,0x000B,0xAA52}; 
pascal OSErr FSpCatMove(const FSSpec *source,const FSSpec *dest)
 = {0x303C,0x000C,0xAA52}; 
pascal OSErr FSpExchangeFiles(const FSSpec *source,const FSSpec *dest)
 = {0x303C,0x000F,0xAA52}; 
/* Obsoolete names for PBGetForeignPrivs and PBSetForeignPrivs */
pascal OSErr PBGetAltAccess(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBGetAltAccessSync(__A0)
pascal OSErr PBGetAltAccessSync(HParmBlkPtr paramBlock)
 = {0x7060,0xA060}; 
#pragma parameter __D0 PBGetAltAccessAsync(__A0)
pascal OSErr PBGetAltAccessAsync(HParmBlkPtr paramBlock)
 = {0x7060,0xA460}; 
pascal OSErr PBSetAltAccess(HParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 PBSetAltAccessSync(__A0)
pascal OSErr PBSetAltAccessSync(HParmBlkPtr paramBlock)
 = {0x7061,0xA060}; 
#pragma parameter __D0 PBSetAltAccessAsync(__A0)
pascal OSErr PBSetAltAccessAsync(HParmBlkPtr paramBlock)
 = {0x7061,0xA460}; 
#ifdef __cplusplus
}
#endif

#endif
