/* 
	File name: 	I2C_Cyclone.h 
	Function:	Header file for the I2C Component
	History:	10/26/92	New for Cyclone (code was orginally from Touchstone Project.)
*/


/* globals */
typedef struct I2CShadow
	{
	unsigned char	gDMSDRec[25];	/* DMSD array */
	unsigned char	gVDCRec[17];	/* VDC array */
	};

typedef struct I2CShadow I2CShadow;
typedef I2CShadow *I2CShadowPtr;

typedef struct {
	ComponentInstance	gSelf;			/* Saved component instance */
	Handle				gShadowHandle;	/* Saved handle to shadow registers */
	I2CShadowPtr		gShadowPtr;		/* Pointer to the shadow registers */

//	unsigned char		gDMSDRec[25];	/* DMSD array */
//	unsigned char		gVDCRec[17];	/* VDC array */
} I2CGlobals;

/* i2c Interface */

#define ki2cSelectors					4


pascal ComponentResult tI2CRead(Handle storage, unsigned short slaveAddr, short byteCount, unsigned char *dataBuf);

pascal ComponentResult tI2CWrite(Handle storage, unsigned short slaveAddr, short byteCount, unsigned char *dataBuf);
	
pascal ComponentResult tI2CReadWithSubAddr(Handle storage, unsigned short slaveAddr, unsigned short subAddr, short byteCount, unsigned char *dataBuf);
	
pascal ComponentResult tI2CWriteWithSubAddr(Handle storage, unsigned short slaveAddr, unsigned short subAddr, short byteCount, unsigned char *dataBuf);
