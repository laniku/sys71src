/*
	File:		ConditionalMacros.h
	
	Contains:	Compile time feature switches to achieve platform independent sources.
	
	Written by:	Dean Yu
	
	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved
	
	Change History (most recent first):
	
		 <2>	  6/7/93	EPT		More ProcPtr/UPP work.
		 <1>	 4/15/93	DTY		first checked in
*/	

#ifndef __CONDITIONALMACROS__
#define __CONDITIONALMACROS__

/*
	Defaults
*/

#ifndef SystemSevenOrLater
#define SystemSevenOrLater 0
#endif

#ifndef SystemSixOrLater
#define SystemSixOrLater SystemSevenOrLater
#endif

#ifndef USES68KINLINES
#define USES68KINLINES 1
#endif

#ifndef USES601INLINES
#define USES601INLINES 0
#endif

#ifndef USESx86INLINES
#define USESx86INLINES 0
#endif

#ifndef USESROUTINEDESCRIPTORS
#define USESROUTINEDESCRIPTORS !USES68KINLINES
#endif

#ifndef USESCODEFRAGMENTS
#define USESCODEFRAGMENTS !USES68KINLINES
#endif

/*
	The following macros isolate the use of inlines from the routine prototypes.
	A routine prototype will always be followed by on of these inline macros with
	a list of the opcodes to be inlined.  On the 68K side, the appropriate inline
	code will be generated.  On platforms that use code fragments, the macros are
	essentially NOPs.
*/

//#pragma push
//#pragma skipping on
#if USES68KINLINES & !USESCODEFRAGMENTS

#define ONEWORDINLINE(trapNum) = trapNum;
#define TWOWORDINLINE(firstWord, secondWord) = {firstWord, secondWord};
#define THREEWORDINLINE(firstWord, secondWord, thirdWord)	= {firstWord,			\
																secondWord,			\
																thirdWord};
#define FOURWORDINLINE(firstWord, secondWord, thirdWord, fourthWord) = {firstWord,	\
																		secondWord,	\
																		thirdWord,	\
																		fourthWord};
#define FIVEWORDINLINE(firstWord, secondWord, thirdWord, fourthWord, fifthWord) =	\
																		{firstWord,	\
																		secondWord,	\
																		thirdWord,	\
																		fourthWord,	\
																		fifthWord};
#define SIXWORDINLINE(firstWord, secondWord, thirdWord, fourthWord, fifthWord, sixthWord) =	\
																		{firstWord,	\
																		secondWord,	\
																		thirdWord,	\
																		fourthWord,	\
																		fifthWord,	\
																		sixthWord};
#define SEVENWORDINLINE(firstWord, secondWord, thirdWord, fourthWord, fifthWord, sixthWord, seventhWord) =	\
																		{firstWord,	\
																		secondWord,	\
																		thirdWord,	\
																		fourthWord,	\
																		fifthWord,	\
																		sixthWord,	\
																		seventhWord};
#define EIGHTWORDINLINE(firstWord, secondWord, thirdWord, fourthWord, fifthWord, sixthWord, seventWord, eighthWord) =	\
																		{firstWord,	\
																		secondWord,	\
																		thirdWord,	\
																		fourthWord,	\
																		fifthWord,	\
																		sixthWord,	\
																		seventhWord,	\
																		eighthWord};
#else
#define ONEWORDINLINE(trapNum) ;
#define TWOWORDINLINE(firstWord, secondWord) ;
#define THREEWORDINLINE(firstWord, secondWord, thirdWord) ;
#define FOURWORDINLINE(firstWord, secondWord, thirdWord, fourthWord) ;
#define FIVEWORDINLINE(firstWord, secondWord, thirdWord, fourthWord, fifthWord) ;
#define SIXWORDINLINE(firstWord, secondWord, thirdWord, fourthWord, fifthWord, sixthWord) ;
#define SEVENWORDINLINE(firstWord, secondWord, thirdWord, fourthWord, fifthWord, sixthWord, seventWord) ;
#define EIGHTWORDINLINE(firstWord, secondWord, thirdWord, fourthWord, fifthWord, sixthWord, seventWord, eighthWord) ;
#endif
//#pragma pop

#endif