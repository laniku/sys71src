/*------------------------------------------------------------------------------

				File:		HFSDefs.h
			
				Contains:	HFS data structure definitions.
			
				Written by:	Bill Bruffey
			
				Copyright:	© 1986-1990 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
		 <2>	 6/16/90	PK		cleaning up
		 <1>	 6/14/90	PK		first checked in
				 29 May 90 	PK		Added BB_FNum and VAtrb_BB for sparing
 				 6 Jul 89 	EN		Added cdrFThdRec for FileIDs support for BigBang. (changed comments too)
 				10 May 86 	BB 		New today.
				
				To Do:
 ------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 Misc constants
------------------------------------------------------------------------------*/

#define	HFS_SigW	0x4244			/* HFS signature bytes */
#define	NxFreeFN	16				/* 1st free file number for user files */
#define	NxFreeDID	3				/* 1st free directory ID for user directories */
#define	FSRtDirID	2				/* directory ID fo root directory */
#define	AlBlkSize	512				/* default allocation block size (bytes) */
#define	ClpSize		(4*512)			/* default clump size (bytes) */

#define	MDB_FNum	1				/* file number representing the MDB */
#define	AMDB_FNum	-1				/* file number representing the alternate MDB */
#define	VBM_FNum	2				/* file number representing the volume bit map */
#define	Ext_FNum	3				/* file number for the Extent file */
#define	Cat_FNum	4				/* file number for the Catalog file */
#define	BB_FNum		5				/* file number for the Bad Block extents */
#define	MDB_BlkN	2				/* logical block number for the MDB */

#define	Vol_RefN	(-1)			/* refnum of volume being scavenged */
#define	Ext_RefN	0x02			/* extent file refnum */
#define	Cat_RefN	0x60			/* extent file refnum */
#define	Max_XKey	7				/* max extent file key length */
#define	Max_CKey	37				/* max catalog file key length */
#define	Max_VName	27				/* max volume name length */

#define	Max_ABSiz	0xFFFF			/* max allocation block size (64K - 1) */
#define	Max_ABlks	0xFFFF			/* max number of allocation blocks (64K - 1) */
#define	Blk_Size	512				/* size of a logical block */
#define	Num_CBufs	32				/* number of cache buffers */
#define	CBuf_Size	512				/* cache buffer size */

#define	VAtrb_Msk	0x7C7F			/* volume attribute mask - invalid bits */
#define	VAtrb_BB	0x0200			/* bad blocks have been spared */
#define	VAtrb_DFlt	0x0100			/* default volume attribute flags */
#define	VAtrb_Cons	0x0100			/* volume consistency flag */


/*------------------------------------------------------------------------------
 BTree data structures
------------------------------------------------------------------------------*/

/* misc BTree constants */

#define	BTNodeSize	512				/* default node size */
#define	BTMaxDepth	8				/* max tree depth */
#define	Num_HRecs	3				/* number of records in BTree Header node */
#define	Num_MRecs	1				/* number of records in BTree Map node */

/* the records in the BTree Header node are: */

#define HRec_BTH	1				/* record 1: the BTree header record */
#define	HRec_Unused	2				/* record 2: 128 unused 'user' bytes */
#define	HRec_Map	3				/* record 3: the initial 256 byte bitmap */


/*
 * Scavenger BTree Control Block (SBTCB) 
 */
typedef struct SBTCB {
	unsigned char	BTCFlags;		/* flags */
	char			BTCResv;		/* reserved */
	short			BTCRefNum;		/* file refnum */
	ProcPtr			BTCKeyCR;		/* pointer to ext key compare routine */
	Ptr				BTCCQPtr;		/* pointer to cache queue */
	Ptr				BTCVarPtr;		/* pointer to BTree variables */
	short			BTCLevel;		/* current level */
	long			BTCNodeM;		/* current node mark */
	short			BTCIndexM;		/* current index mark */

/* this part of a BTCB is the memory resident portion of the BTH */

	short			BTCDepth;		/* current depth of tree */
	long			BTCRoot;		/* root node number */
	long			BTCNRecs;		/* number of leaf records in BTree */
	long			BTCFNode;		/* node number of 1st leaf node */
	long			BTCLNode;		/* node number of last leaf node */
	short			BTCNodeSize;	/* BTree node size in bytes */
	short			BTCKeyLen;		/* max key length */
	long			BTCNNodes;		/* total number of nodes */
	long			BTCFree;		/* number of free nodes */

/* Scavenger extensions to the HFS BTCB */

	Ptr 			BTCBMPtr;		/* pointer to scavenger BTree bit map */
	Ptr				BTCFCBAPtr;		/* pointer to scavenger FCB array */
	} SBTCB, *SBTCBPtr;

#define	LenBTCB		54				/* length of a HFS BTCB */
#define	LenSBTCB	62				/* length of a Scavenger BTCB */

/* BTCB flag definitions (contents of BTCFlags) */

#define	BTCDirty	128				/* dirty flag */
#define	BTCKeyUpd	64				/* index key update required */
#define	BTCNewIRec	32				/* new index record required */
#define	BTCDelIRec	16				/* index record delete required */


/*
 * BTree Header (BTH) on disk
 */
typedef struct BTH {
	short			BTHDepth;		/* current depth of tree */
	long			BTHRoot;		/* root node number */
	long			BTHNRecs;		/* number of leaf records in BTree */
	long			BTHFNode;		/* node number of 1st leaf node */
	long			BTHLNode;		/* node number of last leaf node */
	short			BTHNodeSize;	/* BTree node size in bytes */
	short			BTHKeyLen;		/* max key length */
	long			BTHNNodes;		/* total number of nodes */
	long			BTHFree;		/* number of free nodes */
	} BTH, *BTHPtr;
	
#define	LenMemBTH	30				/* length of memory resident portion of BTH */
#define	LenBTH		106				/* length of a BTH */


/*
 * Node Descriptor (prefix ND)
 */
typedef struct ND {
	long			NDFlink;		/* forward link */
	long			NDBlink;		/* backward link */
	char			NDType;			/* node type */
	char			NDNHeight;		/* node height */
	short			NDNRecs;		/* number of records */
	short			NDResv2;		/* reserved */
	} ND, *NDPtr;

#define	lenND	14					/* length of node descriptor */

/* node types (contents of NDType) */

#define	NDHdrNode	1				/* header node */
#define	NDMapNode	2				/* map node */
#define	NDIndxNode	0				/* index node */
#define	NDLeafNode	(-1)			/* leaf node */
	
/*
 * Scavenger BTree Path Record (STPR)
 */
typedef struct STPR {
	long			TPRNodeN;		/* node number */
	short			TPRRIndx;		/* record index */
	short			Unused;			/* not used - makes debugging easier */
	long			TPRLtSib;		/* node number of left sibling node */
	long			TPRRtSib;		/* node number of right sibling node */
	} STPR, *STPRPtr;
	
typedef	STPR SBTPT[BTMaxDepth]; 		/* BTree path table */
	
#define	LenSTPR	16					/* length of Tree Path Record */
#define	LenSBTPT	(LenSTPR*BTMaxDepth)	/* length of BTree Path Table */




/*------------------------------------------------------------------------------
 FXM (File Extents Manager) data structures
------------------------------------------------------------------------------*/

/*
 * ExtendFile option flags
 */
#define	EFContig	2				/* force contiguous allocation */
#define	EFAll		1				/* allocate all requested bytes or none */

/*
 * TruncateFile option flags
 */
#define	TFTrunExt	1				/* truncate to the extent containing new PEOF */

/*
 * extent key record (prefix xkr)
 */
typedef struct xkr {
	unsigned char	xkrKeyLen;		/* key length (byte) */
	unsigned char	xkrFkType;		/* fork type (byte) */
									/*	 $00 = data fork */
									/*	 $FF = resource fork */
	long			xkrFNum;		/* file number (long) */
	unsigned short	xkrFABN;		/* starting file allocation block number (word) */
	} xkr, *xkrPtr;

#define	Lenxkr		8				/* length of a xkr */

/*
 * extent entry (prefix ext)
 */
typedef struct ext {
	unsigned short	extStABN;		/* starting physical allocation block number (word) */
	unsigned short	extNumABlks;	/* number of allocation blocks (word) */
	} ext;

/*
 * extent data record (prefix xdr)
 */

#define	NumExts		3				/* number of extents per record */

typedef ext xdr[NumExts];			/* xdr = (3 extent entries) */




/*------------------------------------------------------------------------------
 CM (Catalog Manager) data structures
 ------------------------------------------------------------------------------*/

/*
 * Misc constants
 */
#define	CMMaxKey	37				/* max catalog key length */
#define	CMMaxCName	31				/* max CName length */
#define CMMaxDepth	64				/* max catalog depth */
#define	CMClpSize	20				/* catalog clump size */

/*
 * CNode types
 */
#define	CMDirCN		1				/* directory CNode */
#define	CMFilCN		2				/* file CNode */

/*
 * catalog key record (prefix ckr)
 */
typedef struct ckr {
	unsigned char	ckrKeyLen;		/* key length (byte) */
	char			ckrResrv1;		/* reserved (byte) */
	long			ckrParID;		/* parent directory ID (long) */
	unsigned char	ckrCName[32];	/* CNode name (str31) */
	} ckr, *ckrPtr;

#define	Lenckr		38				/* length of a ckr */

/*
 * catalog data record (prefix cdr)
 */
typedef struct cdr {
	char			cdrType;		/* record type (byte) */
	char			cdrResrv;		/* reserved (byte) */
	} cdr, *cdrPtr;
	
#define	cdrData		2				/* start of catalog record data */

/*
 * catalog directory record (prefix dir)
 */
typedef struct dir {
	char			cdrType;		/* record type (byte) */
	char			cdrResrv;		/* reserved (byte) */
	unsigned short	dirFlags;		/* flags (word) */
	short			dirVal;			/* valence (word) */
	long			dirDirID;		/* DirID for this directory (long) */
	unsigned long	dirCrDat;		/* date/time created (long) */
	unsigned long	dirMdDat;		/* date/time last modified (long) */
	unsigned long	dirBkDat;		/* date/time last backed up (long) */
	char			dirUsrInfo[16];	/* User info bytes (16 bytes) */
	FInfo			dirFndrInfo;	/* Finder Info bytes (16 bytes) */
	char			dirResrv[16];	/* reserved (16 bytes) */
	} dir;

#define	Lendir		70				/* length of a directory record */

/*
 * catalog thread record (prefix thd)
 */
typedef struct thd {
	char			cdrType;		/* record type (byte) */
	char			cdrResrv;		/* reserved (byte) */
	char			thdResrv[8];	/* reserved (8 bytes) */
	long			thdParID;		/* Parent ID for this directory (long) */
	unsigned char	thdCName[32];	/* CName for this directory (str31) */
	} thd;

#define	Lenthd		46				/* length of a thread record */

/*
 * catalog file record (prefix fil)
 */
typedef struct fil {
	char			cdrType;		/* record type (byte) */
	char			cdrResrv;		/* reserved (byte) */
	unsigned char	filFlags;		/* bit 7=1 (used), bit 0=file lock flag, bit 1=file thread flag */
	char			filTyp;			/* file type (used as a name extension) */
	char			filUsrWds[16];	/* user words for file. (16 bytes) */
	long			filFlNum;		/* file number */

	short			filStBlk;		/* Start file block (alloc blk size)(0000 if none) */
	long			filLgLen;		/* File logical length in bytes (EOF) */
	long			filPyLen;		/* File physical length in bytes */

	short			filRStBlk;		/* Start file block, resource fork (0000 if none) */
	long			filRLgLen;		/* File logical length (EOF), resource fork */
	long			filRPyLen;		/* File physical length, resource fork */

	unsigned long	filCrDat;		/* date/time created (long) */
	unsigned long	filMdDat;		/* date/time last modified (long) */
	unsigned long	filBkDat;		/* date/time last backed up (long) */
	char			filFndrInfo[16]; /* Additional finder info for file (16 bytes) */
	short			filClpSize;		/* file clump size (word) */
	xdr				filExtRec;		/* First 3 data fork extents (12 bytes) */
	xdr				filRExtRec;		/* First 3 resource fork extents (12 bytes) */
	long			filResrv;		/* reserved (4 bytes) */
	} fil;

#define	Lenfil		102 			/* length of a file record */
#define	Lencdr		Lenfil			/* max length of a catalog data record */

/* catalog data record types (varients) */

#define	cdrDirRec	CMDirCN 		/* directory record (directory CNode type) */
#define	cdrFilRec	CMFilCN 		/* file record (file CNode type) */
#define	cdrThdRec	3				/* thread record */
#define	cdrFThdRec	4				/* file thread record */

	
/*
 * Scavenger Directory Path Record (SDPR)
 */
typedef struct SDPR {
	long			DirID;			/* directory ID */
	short			OffIndx;		/* offspring index */
	long			DirHint;		/* BTree hint for directory record */
	long			ThdHint;		/* BTree hint for thread record */
	long			ParID;			/* parent directory ID */
	unsigned char	DirCName[32];	/* directory CName */
	} SDPR;
	
typedef	SDPR SDPT[CMMaxDepth]; 		/* directory path table */
	
#define	LenSDPR	50					/* length of Directory Path Record */
#define	LenSDPT	(LenSDPR*CMMaxDepth)	/* length of Tree Path Table */





/*------------------------------------------------------------------------------
 Scavenger VCB (SVCB)
------------------------------------------------------------------------------*/

typedef struct SVCB {
	struct QElem *qLink;			/* link to next VCB */ 
	short			qType;			/* queue type */
	unsigned short	VCBFlags;		/* VCB flags */ 
	unsigned short	VCBSigWord;		/* signature word */
	unsigned long	VCBCrDate;		/* Creation date */ 
	unsigned long	VCBLsMod;		/* last backup date */
	unsigned short	VCBAtrb;		/* volume attributes. bit 15=write(locked=1) */
	unsigned short	VCBNmFls;		/* number files in root directory */ 
	short			VCBVBMSt;		/* starting sector of allocation map (overlaps) */ 
	unsigned short	VCBAllocPtr;	/* Start of next allocation search */ 
	unsigned short	VCBNmAlBlks;	/* number of blocks (of alloc size) this volume */ 
	long			VCBAlBlkSiz;	/* min num of bytes to allocate (must be 512 mult) */
	long			VCBClpSiz;		/* num of bytes to try to alloc as a clump */
	short			VCBAlBlSt;		/* starting diskette (512-byte) block in block map */
	long			VCBNxtCNID;		/* Next CNode identifier */ 
	unsigned short 	VCBFreeBks;		/* number of free blocks on this volume */ 
	unsigned char	VCBVN[Max_VName+1];	/* volume name (including name length) */ 
	short			VCBDrvNum;		/* drive number for this VCB */ 
	short			VCBDRefNum;		/* driver refnum for this VCB */ 
	short			VCBFSID;		/* ID of file system handling this volume */ 
	short			VCBVRefNum;		/* unique refnum for this VCB */ 
	Ptr				VCBMAdr;		/* volume map address (MFS volume) */ 
	Ptr				VCBBufAdr;		/* volume buffer address */ 
	short			VCBMLen; 		/* length of voume map (MFS volume) */
	short			VCBDirIndex;	/* directory index and block number */ 
	short			VCBDirBlk; 		/*  (used by GetFileInfo searches by index) */

/* VCB extensions for HFS (copied from the MDB) */

	unsigned long	VCBVolBkup;		/* date volume was last backed up */ 
	short			VCBVSeqNum;		/* index of volume in backup set */ 
	unsigned long	VCBWrCnt;		/* volume write count */ 
	long			VCBXTClpSiz;	/* extent file clump size */ 
	long			VCBCTClpSiz;	/* catalog file clump size */ 
	short			VCBNmRtDirs;	/* number of directories in root */ 
	long			VCBFilCnt;		/* total number of files on volume */ 
	long			VCBDirCnt;		/* total number of directories on volume */ 
	char			VCBFndrInfo[32]; /* Finder info for volume */ 
	short			VCBVCSize;		/* Volume cache size in blocks */ 
	short			VCBVBMCSize;	/* volume bitmap cache size in blocks */ 
	short			VCBCtlCSize;	/* control (BTree) cache size in blocks */
	
/* VCB extensions for HFS (not copied from the MDB) */

	short			VCBXTAlBlks;	/* size of extent BTree in alloc blocks */ 
	short			VCBCTAlBlks;	/* size of catalog BTree in alloc blocks */ 
	short			VCBXTRef;		/* file refnum for extent file */ 
	short			VCBCTRef;		/* file refnum for catalog file */ 
	Ptr				VCBCtlBuf;		/* pointer to control (BTree) cache */ 
	long			VCBDirIDM;		/* directory last searched ( 0 if invalid) */ 
	short			VCBOffsM;		/* offspring index at last search */
	
/* Scavenger extensions to the HFS VCB */

	short			VCBRWErr;		/* last read/write error on volume */
	Ptr 			VCBBMPtr;		/* pointer to scavenger volume bit map */
	Ptr				VCBFCBAPtr;		/* pointer to scavenger FCB array */
	} SVCB, *SVCBPtr;

#define	LenSVCB		188				/* length of a Scavenger VCB */



/*------------------------------------------------------------------------------
Master Directory Block (MDB) on disk 
------------------------------------------------------------------------------*/

typedef struct MDB {
	unsigned short	DrSigWord;		/* signature word */
	unsigned long	DrCrDate;		/* Creation date */
	unsigned long	DrLsMod;		/* last backup date */
	unsigned short	DrAtrb;			/* volume attributes. bit 15=write(locked=1) */
	unsigned short	DrNmFls;		/* number files in root directory */
	short			DrVBMSt;		/* starting sector of allocation map (overlaps) */
	short			DrAllocPtr;		/* Start of next allocation search */
	unsigned short	DrNmAlBlks;		/* number of blocks (of alloc size) this volume */
	long			DrAlBlkSiz;		/* min num of bytes to allocate (must be 512 mult) */
	long			DrClpSiz;		/* num of bytes to try to alloc as a clump */
	short			DrAlBlSt;		/* starting diskette (512-byte) block in block map */
	long			DrNxtCNID;		/* Next CNode identifier */
	unsigned short	DrFreeBks;		/* number of free blocks on this volume */
	unsigned char	DrVN[Max_VName+1];	/* volume name (including name length) */
	
/* Master Directory Block extensions for HFS */

 	unsigned long	DrVolBkup;		/* Date of last volume backup */
	short			DrVSeqNum;		/* Sequence number of volume within backup set */
	unsigned long	DrWrCnt;		/* Volume write count */
	long			DrXTClpSiz;		/* extent B*-Tree clump size */
	long			DrCTClpSiz;		/* Catalog B*-Tree clump size */
	short			DrNmRtDirs;		/* Number of subdirectories in the root */
	long			DrFilCnt;		/* Total number of files in volume */
	long			DrDirCnt;		/* Total number of directories in volume */
	char			DrFndrInfo[32];	/* Finder info for volume */
	short			DrVCSize;		/* Volume cache size */
	short			DrVBMCSize;		/* Volume Bitmap cache size */
	short			DrCtlCSize;		/* Size of common volume cache */
	
/* Information not copied into VCB */

	long			DrXTFlSize;		/* Length of extent B*-Tree (LEOF and PEOF) */
	xdr				DrXTExtRec;		/* First (and only) extent-tree extent record */
	long			DrCTFlSize;		/* Length of catalog B*-Tree (LEOF and PEOF) */
	xdr				DrCTExtRec;		/* First catalog extent record */
	char			reserved[94];	/* reserved */
	char			DrUsrInfo[256];	/* User information for volume */
	
	} MDB, *MDBPtr;
	
#define	LenMDB		162 			/* length of full MDB */	
#define	LenMFSMDB	64				/* length of VCB data from MDB (MFS) */
#define	LenHFSMDB	66				/* length of additional VCB data from MDB (HFS) */



/*------------------------------------------------------------------------------
	Scavenger File Control Block (SFCB) in memory 
------------------------------------------------------------------------------*/

typedef struct SFCB {
	long			FCBFlNm; 		/* FCB file number. Non-zero marks FCB used */
	unsigned char	FCBFlags;		/* FCB flags */
	unsigned char	FCBTypByt;		/* file type byte */
	short			FCBSBlk; 		/* File start block (in alloc size blks) */
	long			FCBEOF;			/* logical length or EOF in bytes */
	long			FCBPLen;		/* Physical file length in bytes */
	long			FCBCrPs;		/* current position within file */
	SVCBPtr			FCBVPtr;		/* Absolute pointer to the corresponding VCB */
	Ptr				FCBBfAdr;		/* file's buffer address */
	short			FCBFlPos;		/* directory block this file is in */

/* FCB Extensions for HFS */

 	long			FCBClmpSize;	/* Number of bytes per clump */
	SBTCBPtr		FCBBTCBPtr;		/* pointer to B*-Tree control block for this file */
	xdr				FCBExtRec;		/* First 3 file extents */
	long			FCBFType;		/* file's 4 Finder Type bytes */
	long			FCBCatPos;		/* Catalog hint for use on Close */
	long			FCBDirID;		/* Parent Directory ID */
	unsigned char	FCBCName[32];	/* CName of open file Str(31) */
	
	} SFCB, *SFCBPtr;

#define	LenSFCB		94				/* length of a SFCB */

/* FCB flag definitions (contents of FCBFlags) */

#define FCBModBit	128				/* dirty bit for FCB entry */
#define	FCBRscBit	2				/* 1 if this is resource fork */




/*------------------------------------------------------------------------------
 Low-level File System Error codes 
------------------------------------------------------------------------------*/

/* Cache errors */

#define	ChNoBuf		1				/* no free cache buffers (all in use) */
#define	ChInUse		2				/* requested block in use */
#define	Chnotfound	3				/* requested block not found */
#define	ChNotInUse	4				/* block being released was not in use */

/* FXM Internal error codes */

#define	FXRangeErr	16				/* file position beyond mapped range */
#define	FXOvFlErr	17				/* extents file overflow */

/* BTree error codes */

#define	BTnotfound	32				/* record not found	 */
#define	BTexists	33				/* record already exists */
#define	BTnospace	34				/* no available space */
#define	BTnoFit		35				/* record doesn't fit in node */
#define	BTbadNode	36				/* bad node detected */
#define	BTbadHdr	37				/* bad BTree header record detected */
#define	dsBadRotate	64				/* bad BTree rotate */

/* CM error codes */

#define	CMnotfound	48				/* CNode not found */
#define	CMexists	49				/* CNode already exists */
#define	CMnotempty	50				/* directory CNode not empty (valence = 0) */
#define	CMRootCN	51				/* invalid reference to root CNode */
#define	CMbadnews	52				/* detected bad catalog structure */
