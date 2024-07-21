
/************************************************************

Created: Monday, January 28, 1991 at 12:55 PM
 Aliases.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1989-1991
  All rights reserved
    This file is used in these builds: BigBang



	Change History (most recent first):

		<19>	 7/30/91	JL		Updated Copyright.
		<18>	  2/5/91	stb		gs: fix casing
		<17>	 1/30/91	JL		Grouped enums into groups of 20
		<16>	  1/7/91	JDR		(dba) Changing FSSpecPtr into FSSpecArrayPtr to match the pascal
									documentation.
		<14>	 12/3/90	JL		Put formal parameter names back, added CPlusPlus conditional
									around functions.
		<13>	 11/8/90	JL		Changed all #defines to anonymous enums
		<12>	 11/4/90	dba		use constStr31Parameter, constStr32Parameter, and use a void* in
									place of a Ptr when appropriate
		<11>	  8/6/90	PP		zoneName in MinimalFullpathAlias is Str32 and not Str31.
		<10>	  7/2/90	PP		Add ResolveAliasFile.
		 <9>	 6/28/90	PP		Convert CanonicalFileSpec into FSSpec.
		 <8>	 6/15/90	PP		Remove SelectAlias.
		 <7>	 4/10/90	PP		Add kARMnoUI bit for rules mask.
		 <6>	  4/5/90	PP		Add kARMsearchRelFirst to MatchAlias rulesMask. Rename
									"callbackPtr" to "yourDataPtr".
		 <5>	 3/20/90	PP		userType field is OSType and not ResType.
		 <4>	  3/8/90	PP		Add minimal alias support.  toFile is now target.
** 2.0	prp 12/15/1989 Fix parameter variable names.
** 1.9	prp 11/16/1989 Slash-slash type comments are changed to regular form of
**		slash-star.
** 1.8	prp 10/02/1989 Added 'GetAliasInfo' routine.
** 1.7	prp 09/18/1989 SelectAlias, MatchAlias and UpdateAlias has API changes
**		with additional parameters.
** 1.6	prp 09/06/1989 Added DisposeAlias back until DPMgr is in sync.
** 1.5	prp 09/06/1989 Changes from CodeReview.
** 1.4	prp 08/07/1989 Added SelectAlias routine as an external interface.
** 1.3	prp 06/12/1989 Cleaned up IFNDEFs. Took out emphasize relative path
**		rules bit.
** 1.2	prp 06/08/1989 Alias Manager Trap # changed from $A825 to $A823
** 1.1	prp 05/31/1989 Fixed the comment header.
** 1.0	prp 05/31/1989 Initial Release.

************************************************************/


#ifndef __ALIASES__
#define __ALIASES__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __APPLETALK__
#include <AppleTalk.h>
#endif

#ifndef __FILES__
#include <Files.h>
#endif


enum {


#define rAliasType 'alis'											/* Aliases are stored as resources of this type */

/* define alias resolution action rules mask */

 kARMMountVol = 0x00000001,											/* mount the volume automatically */
 kARMNoUI = 0x00000002,												/* no user interface allowed during resolution */
 kARMMultVols = 0x00000008,											/* search on multiple volumes */
 kARMSearch = 0x00000100,											/* search quickly */
 kARMSearchMore = 0x00000200,										/* search further */
 kARMSearchRelFirst = 0x00000400,									/* search target on a relative path first */

/* define alias record information types */
 asiZoneName = -3,													/* get zone name */
 asiServerName = -2,												/* get server name */
 asiVolumeName = -1,												/* get volume name */
 asiAliasName = 0,													/* get aliased file/folder/volume name */
 asiParentName = 1													/* get parent folder name */

};

/* define the alias record that will be the blackbox for the caller */
struct AliasRecord {
 OSType userType;													/* appl stored type like creator type */
 unsigned short aliasSize;											/* alias record size in bytes, for appl usage */
};

typedef struct AliasRecord AliasRecord;
typedef AliasRecord *AliasPtr, **AliasHandle;


typedef short AliasInfoType;										/* alias record information type */
typedef pascal Boolean (*AliasFilterProcPtr) (CInfoPBPtr cpbPtr,	/*I*/
Boolean *quitFlag,													/*O*/
Ptr yourDataPtr);													/*I*/

#ifdef __cplusplus
extern "C" {
#endif
/*  create a new alias between fromFile-target and return alias record handle  */
pascal OSErr NewAlias(const FSSpec *fromFile,
                      const FSSpec *target,
                      AliasHandle *alias)
 = {0x7002,0xA823}; 
/* create a minimal new alias for a target and return alias record handle */
pascal OSErr NewAliasMinimal(const FSSpec *target,
                             AliasHandle *alias)
 = {0x7008,0xA823}; 
/* create a minimal new alias from a target fullpath (optional zone and server name) and return alias record handle  */
pascal OSErr NewAliasMinimalFromFullPath(short fullPathLength,
                                         const unsigned char *fullPath,
                                         ConstStr32Param zoneName,
                                         ConstStr31Param serverName,
                                         AliasHandle *alias)
 = {0x7009,0xA823}; 
#define NewAliasMinimalFromFullpath NewAliasMinimalFromFullPath

/* given an alias handle and fromFile, resolve the alias, update the alias record and return aliased filename and wasChanged flag. */
pascal OSErr ResolveAlias(const FSSpec *fromFile,
                          AliasHandle alias,
                          FSSpec *target,
                          Boolean *wasChanged)
 = {0x7003,0xA823}; 
/* given an alias handle and an index specifying requested alias information type, return the information from alias record as a string. */
pascal OSErr GetAliasInfo(const AliasHandle alias,
                          AliasInfoType index,
                          Str63 theString)
 = {0x7007,0xA823}; 

/* 
  given a file spec, return target file spec if input file spec is an alias.
  It resolves the entire alias chain or one step of the chain.  It returns
  info about whether the target is a folder or file; and whether the input
  file spec was an alias or not. 
*/

pascal OSErr ResolveAliasFile(FSSpec *theSpec,
                              Boolean resolveAliasChains,
                              Boolean *targetIsFolder,
                              Boolean *wasAliased)
 = {0x700C,0xA823}; 

/* 
   Low Level Routines 
 given an alias handle and fromFile, match the alias and return aliased filename(s) and needsUpdate flag
*/

pascal OSErr MatchAlias(const FSSpec *fromFile,
                        unsigned long rulesMask,
                        const AliasHandle alias,
                        short *aliasCount,
                        FSSpecArrayPtr aliasList,
                        Boolean *needsUpdate,
                        AliasFilterProcPtr aliasFilter,
                        void *yourDataPtr)
 = {0x7005,0xA823}; 
/* given a fromFile-target pair and an alias handle, update the lias record pointed to by alias handle to represent target as the new alias. */
pascal OSErr UpdateAlias(const FSSpec *fromFile,
                         const FSSpec *target,
                         AliasHandle alias,
                         Boolean *wasChanged)
 = {0x7006,0xA823}; 
#ifdef __cplusplus
}
#endif

#endif
