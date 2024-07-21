/*
	File:		ATIStdTypes.h

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 11/5/93	fau		first checked in
		 <1>	10/27/93	fau		first checked in
		 <1>	10/19/93	fau		first checked in

*/


//==================================================================================
//
//    File:    ATIStdTypes
//
//    Description:  This file defines standard types, constants and macros that can
//        be used to produce portable C code.  The following is a list of suggested 
//        coding style guidelines:
//
//        ¥ Precede constant names with a "k": kMyConstant
//        ¥ Precede global names with a "g": gMyGlobal
//        ¥ Capitalize macro names:  MY_NEAT_MACRO 
//        ¥ Capitalize the first letter of each word in typedefs, filenames and 
//            subroutines:  MyTypedef, MyFile.c, MySuperSubroutine()
//        ¥ Capitalize the first letter of each word except the first in variables:
//            myWindowPtr
//        ¥ Avoid using C's ambiguous intrinsic types like "int", use these instead:
//            Uint8, Int32, etc., or define your own for clarity
//        ¥ Include a copyright notice (see below)
//        ¥ Define function prototypes and include argument names in prototypes:
//            void MyFooBar(Int32 refCon, const Ptr string, Boolean *success);
//        ¥ Use enums for a set of constants:
//            typedef enum { kRed = 1, kGreen = 2, kBlue = 3 } ColorComponent;
//        ¥ Ensure that header files cannot be included more than once, so use:
//            #ifndef __MYHEADERFILE__
//            #define __MYHEADERFILE__
//                    header body
//            #endif __MYHEADERFILE__
//
//        ¥ Put clear headers at the top of every file and before every subroutine
//        ¥ Write in ANSI C!  (only caveat - it's okay to use // for comments)
//
//    Creator:    Brian Heaney 
//
//    Copyright:  © 1992-1993 by Apple Computer, Inc., all rights reserved.
//
//    Change History (most recent first):
//
//        Date        Programmer                        Modification
//       -------      ----------        -----------------------------------------------
//       5/5/92	      B. Heaney         Created file
//
//==================================================================================

#ifndef __StdTypes__
#define __StdTypes__

#ifndef __TYPES__
#include <Types.h>                            // Just to make sure we get the basics 
#endif 

//==================================================================================
//
//                        Substitutes for Instrinsic Types
//
//==================================================================================

typedef char              Int8;          // Signed 8-bit integer
typedef short             Int16;         // Signed 16-bit integer
typedef long              Int32;         // Signed 32-bit integer

typedef unsigned char     UInt8;         // Unsigned 8-bit integer
typedef unsigned short    UInt16;        // Unsigned 16-bit integer
typedef unsigned long     UInt32;        // Unsigned 32-bit integer

typedef float             Float32;      // Single-precision floating point
typedef double            Float64;      // Double-precision floating point

typedef Int8              *Int8Ptr, **Int8Handle;
typedef Int16             *Int16Ptr, **Int16Handle;
typedef Int32             *Int32Ptr, **Int32Handle;
typedef UInt8             *UInt8Ptr, **UInt8Handle;
typedef UInt16            *UInt16Ptr, **UInt16Handle;
typedef UInt32            *UInt32Ptr, **UInt32Handle;
typedef Float32           *Float32Ptr, **Float32Handle;
typedef Float64           *Float64Ptr, **Float64Handle;


//==================================================================================
//
//                        Useful Constants
//
//==================================================================================

typedef enum { kIsOk = false, kNotOk = true };
typedef enum { kSuccess = 0, kFailure = -1 };                // Function return codes


//==================================================================================
//
//                        Range limits of each type of integer
//
//==================================================================================

#define kMinInt8      ((Int8) (1<<7))
#define kMaxInt8      (~kMinInt8)
#define kMaxUInt8     ((UInt8) -1)

#define kMinInt16     ((Int16) (1<<15))
#define kMaxInt16     (~kMinInt8)
#define kMaxUInt16    ((UInt16) -1)

#define kMinInt32     ((Int32) (1<<31))
#define kMaxInt32     (~kMinInt8)
#define kMaxUInt32    ((UInt32) -1)


//==================================================================================
//
//                        Useful Arithmetic Macros
//
//==================================================================================

#define ABS(x)             ( (x) < 0 ? -(x) : (x) )
#define MAX(x,y)           ( (x) > (y) ? (x) : (y) )
#define MIN(x,y)           ( (x) < (y) ? (x) : (y) )
#define SQR(x)             ( (x) * (x) )
#define CLAMP(x,min,max)   ( ((x) > (max)) ? (max) : ((x) < (min)) ? (min) : (x) )

            // ASR(operand,shift):  Arithmetic Shift Right Macro
            //            C does not guarrantee that '>>' on a negative operaand will 
            //            perform an arithmetic shift (i.e., preserve the sign bit).
            //            Note:  "shift" must be positive.
            
#define ASR(operand,shift)    ( ((operand) >= 0) ? ((operand) >> (shift)) : \
                                                   (~((~(operand)) >> (shift))) )
 

//==================================================================================
//
//                        Useful Bit-Field Macros
//
//                        Note that the "bit" argument refers to a bit number and
//                        he "mask" argument refers to a maskword, ie.,
//                            #define kDMADoneBit			7  
//                            #define kDMADoneMask		1<<kDMADoneBit
//
//==================================================================================

#define MAKEMASK(bit)             ( 1<<(bit) )
#define ANDMASK(word,mask)        ( (word) & (mask) )
#define ANDBIT(word,bit)          ( ANDMASK(word,MAKEMASK(bit)) )
#define SETMASK(word,mask)        ( (word) | (mask) )
#define SETBIT(word,bit)          ( SETMASK(word,MAKEMASK(bit)) )
#define CLEARMASK(word,mask)      ( (word) & ~(mask) )
#define CLEARBIT(word,bit)        ( CLEARMASK(word,MAKEMASK(bit)) )

#define LSB(mask,bit)		{ \
							for (bit=0; !ANDBIT(mask,bit) && bit < 31; bit++ ) ;  \
							}
							
#define MSB(mask,bit)      	{ \
							for (bit=31; !ANDBIT(mask,bit) && bit > 0; bit-- ) ;  \
							}


#endif __StdTypes__
