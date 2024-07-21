/*
	StdLib.h -- General utilities

	Copyright Apple Computer,Inc.	1987, 1990-1991
	All rights reserved.
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <4>	  8/8/91	JL		Updated copyright

	To Do:
*/

#ifndef __STDLIB__
#define __STDLIB__

#ifndef __size_t__
#define __size_t__
typedef unsigned int size_t;
#endif

#ifndef __wchar_t__
#define __wchar_t__
typedef short wchar_t;
#endif

typedef struct {
	int quot;			/* quotient */
	int rem;			/* remainder */
} div_t;

typedef struct {
	long int quot;		/* quotient */
	long int rem;		/* remainder */
} ldiv_t;


#define NULL 0

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX 32767

#define MB_CUR_MAX 1

#ifdef __cplusplus
extern "C" {
#endif

/*
 *	String conversion functions
 */

double atof (const char *nptr);
int atoi (const char *nptr);
long int atol (const char *nptr);
double strtod (const char *nptr, char **endptr);
long int strtol (const char *nptr, char **endptr, int base);
unsigned long int strtoul (const char *nptr, char **endptr, int base);


/*
 *	Pseudo-random sequence generation functions
 */

int rand (void);
void srand (unsigned int seed);


/*
 *	Memory management functions
 */

void *calloc (size_t nmemb, size_t size);
void free (void *ptr);
void *malloc (size_t size);
void *realloc (void *ptr, size_t size);


/*
 *	Communication with the environment
 */

void abort (void);
int atexit (void (*func)(void));
void exit (int status);
char *getenv (const char *name);
int system (const char *string);


/*
 *	Searching and sorting utilities
 */

void *bsearch (const void *key, const void *base,
			   size_t nmemb, size_t size,
			   int (*compar)(const void *, const void *));
void qsort (void *base, size_t nmemb, size_t size,
			int (*compar)(const void *, const void *));


/*
 *	Integer arithmetic functions
 */

int abs (int j);
div_t div (int numer, int denom);
long int labs (long int j);
ldiv_t ldiv (long int numer, long int denom);


/*
 *	Multibyte functions
 */

int mblen (const char *s, size_t n);
int mbtowc (wchar_t *pwc, const char *s, size_t n);
int wctomb (char *s, wchar_t wchar);
size_t mbstowcs (wchar_t *pwcs, const char *s, size_t n);
size_t wcstombs (char *s, const wchar_t *pwcs, size_t n);


#ifdef __cplusplus
}
#endif

#endif
