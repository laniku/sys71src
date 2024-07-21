/*
	File:		I2C.h

	Contains:	Header file for I2C component routines.

	Written by:	Gary Woodcock

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM3>	 12/9/92	DH		Changed file creator to 'MPS '
	   <SM2>	 12/9/92	DH		Changed to using QTComponents.h because it was causing file not
									founds because path name were too long.
*/

//-----------------------------------------------------------------------
// Includes

#ifndef	_I2C_
#define	_I2C_

#include <QTComponents.h>

//-----------------------------------------------------------------------
// Constants

// I2C component type
#define i2cComponentType	'i2c '

// I2C component interface version
enum
{
	i2cComponentInterfaceVersion = 0x0002
};

// I2C component selectors
enum
{
	kI2CReadSelect = 1,
	kI2CWriteSelect,
	kI2CReadWithSubAddrSelect,
	kI2CWriteWithSubAddrSelect
};

//-----------------------------------------------------------------------
// Types

typedef ComponentInstance I2CComponent;

//-----------------------------------------------------------------------
// Prototypes

pascal ComponentResult
I2CRead (I2CComponent i2cInstance, unsigned short slaveAddr, short byteCount, void *dataBuf)
	= ComponentCallNow (kI2CReadSelect, 0x08);

pascal ComponentResult
I2CWrite (I2CComponent i2cInstance, unsigned short slaveAddr, short byteCount, void *dataBuf)
	= ComponentCallNow (kI2CWriteSelect, 0x08);
	
pascal ComponentResult
I2CReadWithSubAddr (I2CComponent i2cInstance, unsigned short slaveAddr,
	unsigned short subAddr, short byteCount, void *dataBuf)
	= ComponentCallNow (kI2CReadWithSubAddrSelect, 0x0A);
	
pascal ComponentResult
I2CWriteWithSubAddr (I2CComponent i2cInstance, unsigned short slaveAddr,
	unsigned short subAddr, short byteCount, void *dataBuf)
	= ComponentCallNow (kI2CWriteWithSubAddrSelect, 0x0A);
	
//-----------------------------------------------------------------------

#endif _I2C_

//-----------------------------------------------------------------------
