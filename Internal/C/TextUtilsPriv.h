/*
	File:		TextUtilsPriv.h

	Contains:	Private Text Utility routines

	Written by:	Dean Yu

	Copyright:	1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 8/17/93	JDR		first checked in
		 <2>	  8/2/93	DTY		Define __TEXTUTILSPRIV__.
		 <1>	 7/30/93	DTY		first checked in

*/

#ifndef __TEXTUTILSPRIV__
#define __TEXTUTILSPRIV__

#ifdef __cplusplus
extern "C" {
#endif

#pragma parameter __D0 InlineEqualString(__A0, __A1, __D0, __D1)
pascal Boolean InlineEqualString(void *str1, void *str2, unsigned long firstStringLength,
 unsigned long secondStringLength)
 = {0x4841, 0x8081, 0xA03C, 0x0A00, 0x0001};
#pragma parameter __D0 MarkSensitiveEqualString(__A0, __A1, __D0, __D1)
pascal Boolean MarkSensitiveEqualString(void *str1, void *str2,
 unsigned long firstStringLength, unsigned long secondStringLength)
 = {0x4841, 0x8081, 0xA23C, 0x0A00, 0x0001};
#pragma parameter __D0 CaseSensitiveEqualString(__A0, __A1, __D0, __D1)
pascal Boolean CaseSensitiveEqualString(void *str1, void *str2,
 unsigned long firstStringLength, unsigned long secondStringLength)
 = {0x4841, 0x8081, 0xA43C, 0x0A00, 0x0001};
#pragma parameter __D0 CaseAndMarkSensitiveEqualString(__A0, __A1, __D0, __D1)
pascal Boolean CaseAndMarkSensitiveEqualString(void *str1, void *str2,
 unsigned long firstStringLength, unsigned long secondStringLength)
 = {0x4841, 0x8081, 0xA63C, 0x0A00, 0x0001};

#ifdef __cplusplus
}
#endif

#endif
