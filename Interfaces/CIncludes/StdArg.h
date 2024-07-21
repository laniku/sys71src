/*
	StdArg.h -- Variable arguments
	
	Copyright Apple Computer,Inc.	1987, 1990-1991
	All rights reserved.
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <4>	  8/8/91	JL		Updated copyright

	To Do:
*/


#ifndef __STDARG__
#define __STDARG__

#ifndef __va_list__
#define __va_list__
typedef char *va_list;
#endif

#define va_start(ap, parmN) ap = (va_list) ((char *)&parmN + sizeof (parmN))
#define va_arg(ap, type) ((type *)(ap += sizeof (type)))[-1]
#define va_end(ap)	/* do nothing */


#endif
