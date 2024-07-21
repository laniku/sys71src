/************************************************************

	CType.h
	Character handling
	
	Copyright American Telephone & Telegraph
	Used with permission, Apple Computer Inc.	1985-1991.
    This file is used in these builds: ROM System

	All Rights Reserved.

	Change History (most recent first):

		 <4>	  8/8/91	JL		Update copyright

	To Do:
************************************************************/


#ifndef __CTYPE__
#define __CTYPE__

/* 	  @(#)ctype.h		2.1  */
/* 	  3.0 SID # 		1.2	  */
#define _U		 01
#define _L		 02
#define _N		 04
#define _S		 010
#define _P		 020
#define _C		 040
#define _B		 0100
#define _X		 0200

extern char * const __p_CType;

#ifdef __cplusplus
extern "C" {
#endif

int isalnum (int c);
#define isalnum(c)		((__p_CType)[c]&(_U|_L|_N))
int isalpha (int c);
#define isalpha(c)		((__p_CType)[c]&(_U|_L))
int iscntrl (int c);
#define iscntrl(c)		((__p_CType)[c]&_C)
int isdigit (int c);
#define isdigit(c)		((__p_CType)[c]&_N)
int isgraph (int c);
#define isgraph(c)		((__p_CType)[c]&(_P|_U|_L|_N))
int islower (int c);
#define islower(c)		((__p_CType)[c]&_L)
int isprint (int c);
#define isprint(c)		((__p_CType)[c]&(_P|_U|_L|_N|_B))
int ispunct (int c);
#define ispunct(c)		((__p_CType)[c]&_P)
int isspace (int c);
#define isspace(c)		((__p_CType)[c]&_S)
int isupper (int c);
#define isupper(c)		((__p_CType)[c]&_U)
int isxdigit (int c);
#define isxdigit(c)		((__p_CType)[c]&_X)

int tolower (int c);
int toupper (int c);

#ifndef __STDC__

int isascii (int c);
#define isascii(c)		((unsigned char)(c)<=0177)

#define __tolower(c)	((c)-'A'+'a')
#define __toupper(c)	((c)-'a'+'A')
int toascii (int c);
#define toascii(c)		((c)&0177)

#endif

#ifdef __cplusplus
}
#endif

#endif
