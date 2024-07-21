/************************************************************

Created: Thursday, September 7, 1989 at 7:47 PM
	Strings.h
	C Interface to the Macintosh Libraries


	Copyright Apple Computer, Inc.	1985-1991
	All rights reserved
    This file is used in these builds: ROM System



	Change History (most recent first):

		 <3>	  8/8/91	JL		Updated copyright

	To Do:
************************************************************/


#ifndef __STRINGS__
#define __STRINGS__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
StringPtr c2pstr(char *aStr);
pascal StringPtr C2PStr(Ptr cString);
char *p2cstr(StringPtr aStr);
pascal Ptr P2CStr(StringPtr pString);
#ifdef __cplusplus
}
#endif

#endif
