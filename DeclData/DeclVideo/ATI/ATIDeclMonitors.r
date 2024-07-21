/*
	File:		ATIDeclMonitors.r

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 11/5/93	fau		first checked in
		 <1>	10/27/93	fau		first checked in
		 <1>	10/19/93	fau		first checked in

*/

//--------------------------------------------------------------------------
//start
//
//Name:		ATIDeclMonitors.r
//Creator:	George D. Wilson Jr.
//Date:		9/19/92
//
//Purpose:	Defintions for ATI monitors declaration ROM
//
//Category:	Gamma Tables
//File:		ATIDeclMonitors.r
//
//Detailed:	This file contains definitions for video modes for the ATI
//			VRAM PCI card.
//
//Note:
//
//History:
//
//	  Date		Programmer					Modification
//	--------	----------		-----------------------------------------
//
//stop
//------------------------------------------------------------------------*/

#include 	"ROMLink.r"
#include	"Types.r"

#include 	"InternalOnlyEqu.r"				//skanky stuff
#include	"ATIDefROM.r"

//=====================================================================
//	_VideoType
//=====================================================================
resource 'styp' (520, "_VideoType") {
	catDisplay,							//Video sResource :	<Category>
	typVideo,							//					<Type>
	drSwApple,							//					<DrvrSw>
	drHwATI								//					<DrvrHw>
};

//=====================================================================
//	_VideoName
//=====================================================================
resource 'cstr' (530, "_VideoName") {
  "Display_Video_Apple_ATI"
};

//=====================================================================
//				Driver directory
//=====================================================================
resource 'ddir' (530, "_VidDrvrDir") {{
	sMacOS68020, l{"_sATIDrvrDir"};	//References the Macintosh-OS 68020 driver.
}};

resource 'node' (535, "_sATIDrvrDir") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{112};}}};
}};

//=====================================================================
//	_sRsrc_VideoHR_ATI for Hi-Res monitor
//=====================================================================
resource 'srsc' (500, "_sRsrc_VideoHR_ATI") {{
	sRsrcType,    l{"_VideoType"};			//References the sResource Type.
	sRsrcName,    l{"_VideoName"};			//References the sResource Name.
	sRsrcDrvrDir, l{"_VidDrvrDir"};			//References the driver directory.
	sRsrcFlags,   d{6};
	sRsrcHWDevId, d{1};						//The hardware device Id.

	minorBaseOS,  long{defMinorBase};		//References the Minor Base Offset.
	minorLength,  long{defMinorLength};		//References the Minor Base Length.
	sGammaDir,    a{"_GammaDir_HR"};		//References the Gamma resource for 13"

	oneBitMode,   	l{"_EightBitModeHR1024"};	//References the first mode parameters.
}};

//=====================================================================
//	_sRsrc_VideoHR_Diamond for Hi-Res monitor for Diamond
//=====================================================================
resource 'srsc' (505, "_sRsrc_VideoHR_Diamond") {{
	sRsrcType,    l{"_VideoType"};			//References the sResource Type.
	sRsrcName,    l{"_VideoName"};			//References the sResource Name.
	sRsrcDrvrDir, l{"_VidDrvrDir"};			//References the driver directory.
	sRsrcFlags,   d{6};
	sRsrcHWDevId, d{1};						//The hardware device Id.

	minorBaseOS,  long{defMinorBase};		//References the Minor Base Offset.
	minorLength,  long{defMinorLength};		//References the Minor Base Length.
	sGammaDir,    a{"_GammaDir_HR"};		//References the Gamma resource for 13"

	oneBitMode,   l{"_EightBitModeHR640"};	//References the first mode parameters.
}};


//=====================================================================
//=====================================================================
//	Hi-Res vidParms records
//=====================================================================
//=====================================================================

//=====================================================================
//				Eight-Bit per pixel parameter list for Hi-Res
//=====================================================================

resource 'vmod' (550, "_EightBitModeHR1024") {{
	mVidParams,  l{"_EightVidParamsHR1024"};	//References the eight-bit mode parameter record.
	mPageCnt,    d{1};						//The page count.
	mDevType,    d{clutType};				//The device type.
}};

resource 'vdev' (550, "_EightVidParamsHR1024") {
	eightmBaseOffset,	
	1024,								//RowBytes
	{eightmBounds_THR,eightmBounds_LHR,eightmBounds_BHR,eightmBounds_RHR},
	eightVersion,						//bmVersion
	0,									//packType not used
	0,									//packSize not used
	eightmHRes,							//bmHRes
	eightmVRes,							//bmVRes
	eightPixelType,						//bmPixelType
	eightPixelSize,						//bmPixelSize
	eightCmpCount,						//bmCmpCount
	eightCmpSize,						//bmCmpSize
	eightmPlaneBytes					//bmPlaneBytes
};	

resource 'vmod' (555, "_EightBitModeHR640") {{
	mVidParams,  l{"_EightVidParamsHR640"};	//References the eight-bit mode parameter record.
	mPageCnt,    d{1};							//The page count.
	mDevType,    d{clutType};					//The device type.
}};

resource 'vdev' (555, "_EightVidParamsHR640") {
	eightmBaseOffset,	
	640,								//RowBytes
	{eightmBounds_THR,eightmBounds_LHR,eightmBounds_BHR,eightmBounds_RHR},
	eightVersion,						//bmVersion
	0,									//packType not used
	0,									//packSize not used
	eightmHRes,							//bmHRes
	eightmVRes,							//bmVRes
	eightPixelType,						//bmPixelType
	eightPixelSize,						//bmPixelSize
	eightCmpCount,						//bmCmpCount
	eightCmpSize,						//bmCmpSize
	eightmPlaneBytes					//bmPlaneBytes
};	

