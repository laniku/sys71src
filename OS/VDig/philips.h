/* Phillips chip set typedefs, constants, etc.  philips.h */

/* 
	File name: 	philips.h 
	Function:	Header file for the philips chip set stuff
	History:	3/13/91	New today
				
	To do:

*/

#ifndef _philips_
#define	_philips_


typedef struct {
	unsigned char	subAddr;
	unsigned char	reg0;
	unsigned char	reg1;
	unsigned char	reg2;
	unsigned char	reg3;
	unsigned char	reg4;
	unsigned char	reg5;
	unsigned char	reg6;
	unsigned char	reg7;
	unsigned char	reg8;
	unsigned char	reg9;
	unsigned char	regA;
	unsigned char	regB;
	unsigned char	regC;
	unsigned char	regD;
	unsigned char	regE;
	unsigned char	regF;
	unsigned char	reg10;
	unsigned char	reg11;
	unsigned char	reg12;
	unsigned char	reg13;
	unsigned char	reg14;
	unsigned char	reg15;
	unsigned char	reg16;
	unsigned char	reg17;
	unsigned char	reg18;
} DMSDRec;

typedef struct {
	unsigned char	subAddr;
	unsigned char	reg0;
	unsigned char	reg1;
	unsigned char	reg2;
	unsigned char	reg3;
	unsigned char	reg4;
	unsigned char	reg5;
	unsigned char	reg6;
	unsigned char	reg7;
	unsigned char	reg8;
	unsigned char	reg9;
	unsigned char	regA;
	unsigned char	regB;
	unsigned char	regC;
	unsigned char	regD;
	unsigned char	regE;
	unsigned char	regF;
} VDCRec;
#endif