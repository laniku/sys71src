/************************************************************

	String.h
	String handling
	
	Copyright Apple Computer,Inc.  1987-1991
	All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <4>	  8/8/91	JL		Updated copyright

	To Do:
************************************************************/


#ifndef __STRING__
#define __STRING__

#ifndef __size_t__
#define __size_t__
typedef unsigned int size_t;
#endif

#define NULL 0

/*
 *	Copying functions
 */

#ifdef __cplusplus
extern "C" {
#endif

void *memcpy (void *s1, const void *s2, size_t n);
void *memmove (void *s1, const void *s2, size_t n);
char *strcpy (char *s1, const char *s2);
char *strncpy (char *s1, const char *s2, size_t n);

#ifndef __STDC__
void *memccpy(void *s1, const void *s2, int c, size_t n);
#endif

/*
 *	Concatenation functions
 */

char *strcat (char *s1, const char *s2);
char *strncat (char *s1, const char *s2, size_t n);

/*
 *	Comparison functions
 */

int memcmp (const void *s1, const void *s2, size_t n);
int strcmp (const char *s1, const char *s2);
int strcoll (const char *s1, const char *s2);
int strncmp (const char *s1, const char *s2, size_t n);
size_t strxfrm (char *s1, const char *s2, size_t n);


/*
 *	Search functions
 */

void *memchr (const void *s, int c, size_t n);
char *strchr (const char *s, int c);
size_t strcspn (const char *s1, const char *s2);
char * strpbrk (const char *s1, const char *s2);
char *strrchr (const char *s, int c);
size_t strspn (const char *s1, const char *s2);
char *strstr (const char *s1, const char *s2);
char *strtok (char *s1, const char *s2);


/*
 *	Miscellaneous functions
 */

void *memset (void *s, int c, size_t n);
char *strerror (int errnum);
size_t strlen (const char *s);

#ifdef __cplusplus
}
#endif

#endif
