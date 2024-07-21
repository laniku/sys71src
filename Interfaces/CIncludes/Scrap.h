
/************************************************************

Created: Saturday, July 27, 1991 at 6:16 PM
 Scrap.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606 Warhol


	Change History (most recent first):

		 <4>	 7/31/91	JL		Updated Copyright.
		 <3>	 1/27/91	LN		Checked in Database generate file from DSG.

	To Do:
************************************************************/


#ifndef __SCRAP__
#define __SCRAP__

#ifndef __TYPES__
#include <Types.h>
#endif


struct ScrapStuff {
 long scrapSize;
 Handle scrapHandle;
 short scrapCount;
 short scrapState;
 StringPtr scrapName;
};

typedef struct ScrapStuff ScrapStuff;
typedef ScrapStuff *PScrapStuff;


#ifdef __cplusplus
extern "C" {
#endif
pascal PScrapStuff InfoScrap(void)
 = 0xA9F9; 
pascal long UnloadScrap(void)
 = 0xA9FA; 
pascal long LoadScrap(void)
 = 0xA9FB; 
pascal long GetScrap(Handle hDest,ResType theType,long *offset)
 = 0xA9FD; 
pascal long ZeroScrap(void)
 = 0xA9FC; 
pascal long PutScrap(long length,ResType theType,Ptr source)
 = 0xA9FE; 
#ifdef __cplusplus
}
#endif

#endif
