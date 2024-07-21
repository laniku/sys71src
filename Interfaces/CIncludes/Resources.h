/************************************************************

Created: Wednesday, July 31, 1991 at 7:55 AM
 Resources.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved


	Change History (most recent first):

		<13>	 3/10/93	JDR		Added two commonly used constants kResFileNotOpened and
									kSystemResFile.
		<12>	 4/21/92	DTY		#1018901,<gbm>: Add interface for GetNextFOND.
		<11>	 7/31/91	JL		Updated Copyright. Changed SystemSevenOrLater conditional to
									match database output.
		<10>	 7/26/91	stb		use inlines for HOpenResFile and HCreateResFile when
									SystemSevenOrLater
		 <9>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <8>	12/20/90	JL		changed constStr255Parameter to ConstStr255Param
		 <7>	 12/7/90	dba		<gbm> Add partial resource calls.
		 <6>	11/27/90	JL		Put formal parameter names back.
		 <5>	 11/7/90	JL		Changed all #defines to anonymous enums
		 <4>	 11/4/90	dba		used constStr255Parameter; got rid of some extraneous parameter
									names; get rid of excess _ in front of FSpCreateResFile; change
									FSSpecPtr to const FSSPec * for routines which take an FSSpec as
									input

************************************************************/


#ifndef __RESOURCES__
#define __RESOURCES__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __FILES__
#include <Files.h>
#endif


enum {

 resSysHeap = 64,		/*System or application heap?*/
 resPurgeable = 32,		/*Purgeable resource?*/
 resLocked = 16,		/*Load it in locked?*/
 resProtected = 8,		/*Protected?*/
 resPreload = 4,		/*Load in on OpenResFile?*/
 resChanged = 2,		/*Resource changed?*/
 mapReadOnly = 128,		/*Resource file read-only*/
 mapCompact = 64,		/*Compact resource file*/
 mapChanged = 32,		/*Write map out at updat*/

/* Values for setting RomMapInsert and TmpResLoad */
 mapTrue = 0xFFFF,		/*insert ROM map w/ TmpResLoad = TRUE.*/
 mapFalse = 0xFF00,		/*insert ROM map w/ TmpResLoad = FALSE.*/

 kResFileNotOpened = -1,/*ref num return as error when opening a resourc file*/
 kSystemResFile = 0		/*this is the default ref num to the system file*/

};

#ifdef __cplusplus
extern "C" {
#endif
pascal short InitResources(void)
 = 0xA995;
pascal void RsrcZoneInit(void)
 = 0xA996;
pascal void CloseResFile(short refNum)
 = 0xA99A;
pascal short ResError(void)
 = 0xA9AF;
pascal short CurResFile(void)
 = 0xA994;
pascal short HomeResFile(Handle theResource)
 = 0xA9A4;
pascal void CreateResFile(ConstStr255Param fileName)
 = 0xA9B1;
pascal short OpenResFile(ConstStr255Param fileName)
 = 0xA997;
pascal void UseResFile(short refNum)
 = 0xA998;
pascal short CountTypes(void)
 = 0xA99E;
pascal short Count1Types(void)
 = 0xA81C;
pascal void GetIndType(ResType *theType,short index)
 = 0xA99F;
pascal void Get1IndType(ResType *theType,short index)
 = 0xA80F;
pascal void SetResLoad(Boolean load)
 = 0xA99B;
pascal short CountResources(ResType theType)
 = 0xA99C;
pascal short Count1Resources(ResType theType)
 = 0xA80D;
pascal Handle GetIndResource(ResType theType,short index)
 = 0xA99D;
pascal Handle Get1IndResource(ResType theType,short index)
 = 0xA80E;
pascal Handle GetResource(ResType theType,short theID)
 = 0xA9A0;
pascal Handle Get1Resource(ResType theType,short theID)
 = 0xA81F;
pascal Handle GetNamedResource(ResType theType,ConstStr255Param name)
 = 0xA9A1;
pascal Handle Get1NamedResource(ResType theType,ConstStr255Param name)
 = 0xA820;
pascal void LoadResource(Handle theResource)
 = 0xA9A2;
pascal void ReleaseResource(Handle theResource)
 = 0xA9A3;
pascal void DetachResource(Handle theResource)
 = 0xA992;
pascal short UniqueID(ResType theType)
 = 0xA9C1;
pascal short Unique1ID(ResType theType)
 = 0xA810;
pascal short GetResAttrs(Handle theResource)
 = 0xA9A6;
pascal void GetResInfo(Handle theResource,short *theID,ResType *theType,
 Str255 name)
 = 0xA9A8;
pascal void SetResInfo(Handle theResource,short theID,ConstStr255Param name)
 = 0xA9A9;
pascal void AddResource(Handle theResource,ResType theType,short theID,
 ConstStr255Param name)
 = 0xA9AB;
pascal long SizeResource(Handle theResource)
 = 0xA9A5;
pascal long MaxSizeRsrc(Handle theResource)
 = 0xA821;
pascal long RsrcMapEntry(Handle theResource)
 = 0xA9C5;
pascal void SetResAttrs(Handle theResource,short attrs)
 = 0xA9A7;
pascal void ChangedResource(Handle theResource)
 = 0xA9AA;
pascal void RmveResource(Handle theResource)
 = 0xA9AD;
pascal void UpdateResFile(short refNum)
 = 0xA999;
Handle getnamedresource(ResType theType,char *name);
pascal void WriteResource(Handle theResource)
 = 0xA9B0;
pascal void SetResPurge(Boolean install)
 = 0xA993;
Handle get1namedresource(ResType theType,char *name);
pascal short GetResFileAttrs(short refNum)
 = 0xA9F6;
pascal void SetResFileAttrs(short refNum,short attrs)
 = 0xA9F7;
pascal short OpenRFPerm(ConstStr255Param fileName,short vRefNum,char permission)
 = 0xA9C4;
pascal Handle RGetResource(ResType theType,short theID)
 = 0xA80C;
#if SystemSevenOrLater
pascal short HOpenResFile(short vRefNum,long dirID,ConstStr255Param fileName,
 char permission)
 = 0xA81A;
#else
pascal short HOpenResFile(short vRefNum,long dirID,ConstStr255Param fileName,
 char permission);
#endif
#if SystemSevenOrLater
pascal void HCreateResFile(short vRefNum,long dirID,ConstStr255Param fileName)
 = 0xA81B;
#else
pascal void HCreateResFile(short vRefNum,long dirID,ConstStr255Param fileName);
#endif

pascal short FSpOpenResFile(const FSSpec *spec,SignedByte permission)
 = {0x303C,0x000D,0xAA52};
pascal void FSpCreateResFile(const FSSpec *spec,OSType creator,OSType fileType,
 ScriptCode scriptTag)
 = {0x303C,0x000E,0xAA52};
/*  partial resource calls  */
pascal void ReadPartialResource(Handle theResource,long offset,void *buffer,
 long count)
 = {0x7001,0xA822};
pascal void WritePartialResource(Handle theResource,long offset,const void *buffer,
 long count)
 = {0x7002,0xA822};
pascal void SetResourceSize(Handle theResource,long newSize)
 = {0x7003,0xA822};
pascal Handle GetNextFOND(Handle fondHandle)
 = {0x700A,0xA822};

short openrfperm(char *fileName,short vRefNum,char permission);
short openresfile(char *fileName);
void createresfile(char *fileName);
void getresinfo(Handle theResource,short *theID,ResType *theType,char *name);
void setresinfo(Handle theResource,short theID,char *name);
void addresource(Handle theResource,ResType theType,short theID,char *name);
#ifdef __cplusplus
}
#endif

#endif
