/*
	File:		ATIVideoROM.r

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
//Name:		ATIVideoROM.r
//Creator:	George D. Wilson Jr.
//Date:		9/19/92
//
//Purpose:	Declaration ROM for ATI system
//
//Category:	DeclROM
//File:		ATIVideoROM.r
//
//Detailed:	This file defines the declaration information for the ATI
//			mother board.  Currently this system defines only the video display
//			portion of the system.
//
//Note:
//
//History:
//
//	  Date		Programmer					Modification
//	--------	----------		-----------------------------------------
//	10/13/93	George W.		Cleaned up some not used resources.
//
//stop
//------------------------------------------------------------------------*/

#include 	"ROMLink.r"
#include	"Types.r"

#include 	"InternalOnlyEqu.r"				//skanky stuff
#include 	"DepVideoEqu.r"
#include	"ATIDefROM.r"					//Video driver equates

// 
//=====================================================================
//	BEGIN Declaration ROM
//=====================================================================

				
//*************************************************************
//Constants
//*************************************************************
  
#define TheBoardId		$0575					//the Board Id (Special ATI Mother board)

//-----------  sResource Directory				//<Id OF>
#define sRsrc_Board		1						//Board sResource {May be any number in [0..127]}
#define sRsrc_Video		128						//Video sResource {May be any number in [128..254]}

//=====================================================================
//		Directory 
//=====================================================================

resource 'sdir' (270, "_sRsrcATIDir") {{
	sRsrc_Board,   l{"_sRsrc_BdATI"};			//References the board sResource.
	sRsrc_VideoHR_ATI, a{"_sRsrc_VideoHR_ATI"};			//References the video sResource Hi-Res
	sRsrc_VideoHR_Diamond, a{"_sRsrc_VideoHR_Diamond"};			//References the video sResource Hi-Res
}};

//=============================================================
//	sRsrc_Board List - the Board sResource
//=============================================================

resource 'boar' (280, "_sRsrc_BdATI") {{
	sRsrcType,   l{"_BoardType"};					//References the sResource type
	sRsrcName,   c{"PCI Video"};					//Official product name
    sRsrcIcon,   a{"_VidICONCyclone"}; 				//A new icon
	boardId,     d{TheBoardId};						//The board Id.
	primaryInit, l{"_sPInitRec"};					//References the Primary init record.
	vendorInfo,  l{"_VendorInfo"};					//References the OPTIONAL Vendor information list.
}};

//=============================================================
//	_BoardType - Board type and category
//=============================================================
resource 'styp' (290, "_BoardType") {
  	catBoard,		//<Category>	CatBoard ALWAYS = $0001 for bd srsrc 
	typBoard,		//<Type>		TypBoard ALWAYS = $0000 for bd srsrc
	0,				//<DrvrSw>		CatBoard ALWAYS = $0000 for bd srsrc
	0				//<DrvrHw>		CatBoard ALWAYS = $0000 for bd srsrc
};

//=====================================================================
//			Primary Init Record 
//=====================================================================

resource 'node' (418, "_sPInitRec") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{110};}}};
}};

//=====================================================================
//			Vendor Info record 
//=====================================================================

resource 'vend' (420, "_VendorInfo") {{
	vendorId, c{"Apple Computer, Inc."};
	revLevel, c{"1.0D1x02"};
	partNum,  c{"0010"};
}};

//=====================================================================
//			Format/Header Block
//=====================================================================

resource 'form' (128, "Root") {
	l{"_sRsrcDir"},
	1,       // Should put "romRevision = 1" in ROMLink.r 
	appleFormat,
	0,
	$0F
};

