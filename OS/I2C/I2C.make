#
#	File:		I2C.make
#
#	Contains:	makefile for the I squared C componenet
#
#	Written by:	unknown people from the cyclone team
#
#	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#	   <SM2>	 6/14/93	kc		Roll in Ludwig.
#	   <LW2>	12/23/92	fau		Changed the code rsrc id to the MSAD-blessed one.
#
#


# Do not change the order of I2CCObjects.

I2CCObjects							=	"{ObjDir}I2CC.c.o"				¶
										"{ObjDir}IICA.a.o"


"{RsrcDir}I2CT.rsrc"				Ä	"{I2CDir}I2C_Cyclone.r"
	rez {StdROpts} -o "{Targ}" "{I2CDir}I2C_Cyclone.r"


"{RsrcDir}I2CC.rsrc"				Ä	{I2CCObjects}
	Link {StdLOpts} {StdAlign} -o "{Targ}" -rt code=-16730 -m MAIN {I2CCObjects}


"{ObjDir}I2CC.c.o" 				Ä 		"{I2CDir}I2C_Cyclone.c"		¶
										"{I2CDir}I2C.h"				¶
										"{I2CDir}I2C_Cyclone.h"		¶
										"{I2CDir}EgretEqu.h"
	C {StdCOpts} -o "{Targ}" {I2CDir}I2C_Cyclone.c -b2 


"{ObjDir}IICA.a.o" 				Ä	"{I2CDir}IICTest.a"
	Asm {StdAOpts} -o "{Targ}" "{I2CDir}IICTest.a"



