/*
	Signal.h -- Signal handling
	
	Copyright Apple Computer,Inc.	1988, 1990-1991
	All rights reserved.
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <4>	  8/8/91	JL		Updated copyright

	To Do:
*/

#ifndef __SIGNAL__
#define __SIGNAL__


typedef int sig_atomic_t;


/*
 *	Special signal handlers, compatible with the second argument to signal()
 *	or, in the case of SIG_ERR, the return value from signal().
 */

#define SIG_DFL ((void (*)(int)) 1)
#define SIG_ERR ((void (*)(int)) -1)
#define SIG_IGN ((void (*)(int)) 0)
#define SIG_HOLD ((void (*)(int)) 3)
#define SIG_RELEASE ((void (*)(int)) 5)


/*
 *	Signal numbers for specific conditions.
 */

#define SIGABRT		(1<<0)	/* Abnormal termination e.g. by the abort() function */
#define SIGFPE		(1<<2)	/* Arithmetic exception -- not currently implemented */
#define SIGILL		(1<<3)	/* Illegal instruction -- not currently implemented */
#define SIGINT		(1<<1)	/* Interactive attention signal -- User interrupt via CMD-. */
#define SIGSEGV		(1<<4)	/* Segmentation violation -- not currently implemented */
#define SIGTERM		(1<<5)	/* Termination request -- not currently implemented */


#ifdef __cplusplus
extern "C" {
#endif

/*
 *	Specify a signal handling function.
 */

void (*signal (int sig, void (*func) (int))) (int);


/*
 *	Send a signal.
 */

int raise (int sig);

#ifdef __cplusplus
}
#endif

#endif
