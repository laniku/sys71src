/*
   SetJmp.h

   Copyright Apple Computer, Inc.	1986-1991
   All rights reserved.

    This file is used in these builds: ROM System

	Change History (most recent first):

		 <5>	  8/8/91	JL		Updated copyright
		 <4>	 6/17/91	JL		Checked in MPW 3.2Ä version.  Changed __safe_link to
									__cplusplus.  Changed jmp_buf type from int to long.

	To Do:
 */

#ifndef __SETJMP__
#define __SETJMP__


typedef long *jmp_buf[12];		/*	D2-D7,PC,A2-A4,A6,SP  */

#ifdef __cplusplus
extern "C" {
#endif

int __setjmp(jmp_buf env);
#define setjmp(env) __setjmp(env)
void longjmp(jmp_buf, int);

#ifdef __cplusplus
}
#endif

#endif
