/*
	File:		ROMLink.r

	Contains:	Definitions for use with the ROMLink tool.

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	  <SM11>	  1/4/94	PN		Add fDimMinAt1.
	  <SM10>	12/13/93	PN		Roll in KAOs and Horror changes to support Malcom and AJ
									machines
	   <SM9>	11/10/93	fau		Update from SuperMunggio <SMG2>.
	  <SMG2>	10/27/93	fau		Added a temporary drHwATI equate, until we get the official one.
	   <SM8>	 6/14/93	kc		Roll in Ludwig.
	   <LW6>	 4/30/93	fau		Added an sUndefinedID for the picture.
	   <SM7>	 5/28/93	IH		Added sDebugger and sAuxVidParams to constants.
	   <SM6>	  4/5/93	chp		Synchronize with Ludwig.
	   <LW4>	 3/24/93	mal		Added block xfer defines.
	   <LW3>	 3/22/93	fau		Added a temporary TempestBrdID until DTS gives us an official
									one.
	   <LW2>	 2/24/93	fau		Added the catIntBus, typXPT and typSIM for the SCSI sresources
									(DTS-blessed).
	   <SM5>	01-12-93	jmp		Added initial support for CSC.
	   <SM4>	01-11-93	jmp		Changed drHWDBLite to drHWGSC.
	   <SM3>	10-17-92	jmp		Added support for PDM.
	   <SM2>	10-17-92	jmp		Had to conditionalize the 'SINL' resource.
*/

#ifndef __RL_ROMLINK_R__
#define __RL_ROMLINK_R__ 1

// Symbolic constants for ROMLink opcodes.
#define __RL_OP_CSTRING              0x80
#define __RL_OP_INCLUDE              0x81
#define __RL_OP_BEGIN                0x82
#define __RL_OP_END                  0x83
#define __RL_OP_BLOCKSIZE            0x84
#define __RL_OP_ROMLENGTH            0x86
#define __RL_OP_ROMCRC               0x87
#define __RL_OP_TREESIZE             0x88
#define __RL_OP_ALIGN                0x89
#define __RL_OP_ANCHOR               0x8a
#define __RL_OP_KEY                  0xfe
#define __RL_OP_COMMENT              0xff

// Symbolic constants for ROMLink resource pattern selectors.
#define __RL_SEL_FILENAME             1
#define __RL_SEL_NAME                 2
#define __RL_SEL_TYPE                 3
#define __RL_SEL_ID                   4
#define __RL_SEL_LOCAL                5

// Symbolic constants for sResource type categories.
#define __RL_STYPE_CATEGORY_ENUMS\
  catBoard=0x1,\
  catTest=0x2,\
  catDisplay=0x3,\
  catNetwork=0x4,\
  catScanner=0x8,\
  catCPU=0xa,\
  catIntBus=0x0c,\
  catDock=0x20;

// Symbolic constants for sResource type ctypes.
#define __RL_STYPE_CTYPE_ENUMS\
  typBoard=0x0,\
  typApple=0x1,\
  typVideo=0x1,\
  typEtherNet=0x1,\
  typStation=0x1,\
  typXPT=0xb,\
  typSIM=0xc,\
  typDesk=0x2,\
  typDSP=0x4,\
  typ68000=0x2,\
  typ68020=0x3,\
  typ68030=0x4,\
  type68040=0x5,\
  typAppleII=0x15;

// Symbolic constants for sResource type DrSw.
#define __RL_STYPE_DRSW_ENUMS\
  drSwMacCPU=0x0,\
  drSwApple=0x1,\
  drSwAppleIIe=0x1,\
  drSwAppleBOM=0x1;

// Symbolic constants for sResource type DrHw.
#define __RL_STYPE_DRHW_ENUMS\
  drHwTFB=0x1,\
  drHw3Com=0x1,\
  drHwGemini=0x1,\
  drHwDeskBar=0x1,\
  drHwATT3210=0x1,\
  drHwBSC=0x3,\
  drHwJMFB=0x19,\
  drHWMacII=0x1,\
  drHwMacIIx=0x2,\
  drHWSE30=0x3,\
  drHwMacIIcx=0x4,\
  drHWMacIIfx=0x5,\
  drHWF19=0x5,\
  drHwRBV=0x18,\
  drHwElsie=0x1a,\
  drHwTim=0x1b,\
  drHwDAFB=0x1c,\
  drHwGSC=0x1e,\
  drHwDAFBPDS=0x1f,\
  drHWVSC=0x20,\
  drHwApollo=0x21,\
  drHwSonora=0x22,\
  drHwReserved2=0x23,\
  drHwColumbia=0x24,\
  drHwCivic=0x25,\
  drHwCSC=0x28,\
  drHwATI=0x55,\
  drHwSonic=0x110,\
  drHwMace=0x114,\
  drHwDblExp=0x1;

#define __RL_RESTRICTED_FIELD_CASES \
  case byte: \
    byte=__RL_OP_KEY; key byte=0x0; \
    byte=1; byte; \
  case int8: \
    byte=__RL_OP_KEY; key byte=0x0; \
    byte=1; byte; \
  case char: \
    byte=__RL_OP_KEY; key byte=0x0; \
    byte=1; byte; \
  case bytes: \
    byte=__RL_OP_KEY; key byte=0x1; \
    array{byte=1;byte;}; \
  case int8s: \
    byte=__RL_OP_KEY; key byte=0x1; \
    array{byte=1;byte;}; \
  case chars: \
    byte=__RL_OP_KEY; key byte=0x1; \
    array{byte=1;byte;}; \
  case word: \
    byte=__RL_OP_KEY; key byte=0x2; \
    byte=2; integer; \
  case int16: \
    byte=__RL_OP_KEY; key byte=0x2; \
    byte=2; integer; \
  case short: \
    byte=__RL_OP_KEY; key byte=0x2; \
    byte=2; integer; \
  case words: \
    byte=__RL_OP_KEY; key byte=0x3; \
    array{byte=2;integer;}; \
  case int16s: \
    byte=__RL_OP_KEY; key byte=0x3; \
    array{byte=2;integer;}; \
  case shorts: \
    byte=__RL_OP_KEY; key byte=0x3; \
    array{byte=2;integer;}; \
  case int24: \
    byte=__RL_OP_KEY; key byte=0x4; \
    byte=3;bitstring[24]; \
  case int24s: \
    byte=__RL_OP_KEY; key byte=0x5; \
    array{byte=3;bitstring[24];}; \
  case long: \
    byte=__RL_OP_KEY; key byte=0x6; \
    byte=4; longint; \
  case int32: \
    byte=__RL_OP_KEY; key byte=0x6; \
    byte=4; longint; \
  case longword: \
    byte=__RL_OP_KEY; key byte=0x6; \
    byte=4; longint; \
  case longs: \
    byte=__RL_OP_KEY; key byte=0x7; \
    array{byte=4; longint;}; \
  case int32s: \
    byte=__RL_OP_KEY; key byte=0x7; \
    array{byte=4; longint;}; \
  case longwords: \
    byte=__RL_OP_KEY; key byte=0x7; \
    array{byte=4; longint;}; \
  case cstring: \
    byte=__RL_OP_KEY; key byte=0x8; \
    byte=__RL_OP_CSTRING; cstring; \
  case c: \
    byte=__RL_OP_KEY; key byte=0x8; \
    byte=__RL_OP_CSTRING; cstring; \
  case romlength: \
    byte=__RL_OP_KEY; key byte=0x9; \
    byte=__RL_OP_ROMLENGTH; \
  case romcrc: \
    byte=__RL_OP_KEY; key byte=0xa; \
    byte=__RL_OP_ROMCRC; \
  case blocksize: \
    byte=__RL_OP_KEY; key byte=0xb; \
    byte=__RL_OP_BLOCKSIZE; \
  case treesize: \
    byte=__RL_OP_KEY; key byte=0xc; \
    byte=__RL_OP_TREESIZE; \
  case vidmodename: \
    byte=__RL_OP_KEY; key byte=0xd; \
    byte=__RL_OP_BLOCKSIZE; \
    byte=2; integer;  \
    byte=__RL_OP_CSTRING; cstring; \
    byte=__RL_OP_ALIGN; byte=2; \
  case v: \
    byte=__RL_OP_KEY; key byte=0xd; \
    byte=__RL_OP_BLOCKSIZE; \
    byte=2; integer;  \
    byte=__RL_OP_CSTRING; cstring; \
    byte=__RL_OP_ALIGN; byte=2; \
  case type: \
    byte=__RL_OP_KEY; key byte=0xe; \
    byte=8; \
    integer __RL_STYPE_CATEGORY_ENUMS \
    integer __RL_STYPE_CTYPE_ENUMS \
    integer __RL_STYPE_DRSW_ENUMS \
    integer __RL_STYPE_DRHW_ENUMS \
  case t: \
    byte=__RL_OP_KEY; key byte=0xe; \
    byte=8; \
    integer __RL_STYPE_CATEGORY_ENUMS \
    integer __RL_STYPE_CTYPE_ENUMS \
    integer __RL_STYPE_DRSW_ENUMS \
    integer __RL_STYPE_DRHW_ENUMS \

#define __RL_OFFSET_RESTRICTED_FIELD_CASES \
  case byte: \
    byte=__RL_OP_KEY; key byte=0x80; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=1; byte; \
    byte=__RL_OP_END; \
  case int8: \
    byte=__RL_OP_KEY; key byte=0x80; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=1; byte; \
    byte=__RL_OP_END; \
  case char: \
    byte=__RL_OP_KEY; key byte=0x80; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=1; byte; \
    byte=__RL_OP_END; \
  case bytes: \
    byte=__RL_OP_KEY; key byte=0x81; \
    byte=__RL_OP_BEGIN; byte=24; \
    array{byte=1;byte;}; \
    byte=__RL_OP_END; \
  case int8s: \
    byte=__RL_OP_KEY; key byte=0x81; \
    byte=__RL_OP_BEGIN; byte=24; \
    array{byte=1;byte;}; \
    byte=__RL_OP_END; \
  case chars: \
    byte=__RL_OP_KEY; key byte=0x81; \
    byte=__RL_OP_BEGIN; byte=24; \
    array{byte=1;byte;}; \
    byte=__RL_OP_END; \
  case word: \
    byte=__RL_OP_KEY; key byte=0x82; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=2; integer; \
    byte=__RL_OP_END; \
  case int16: \
    byte=__RL_OP_KEY; key byte=0x82; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=2; integer; \
    byte=__RL_OP_END; \
  case short: \
    byte=__RL_OP_KEY; key byte=0x82; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=2; integer; \
    byte=__RL_OP_END; \
  case words: \
    byte=__RL_OP_KEY; key byte=0x83; \
    byte=__RL_OP_BEGIN; byte=24; \
    array{byte=2;integer;}; \
    byte=__RL_OP_END; \
  case int16s: \
    byte=__RL_OP_KEY; key byte=0x83; \
    byte=__RL_OP_BEGIN; byte=24; \
    array{byte=2;integer;}; \
    byte=__RL_OP_END; \
  case shorts: \
    byte=__RL_OP_KEY; key byte=0x83; \
    byte=__RL_OP_BEGIN; byte=24; \
    array{byte=2;integer;}; \
    byte=__RL_OP_END; \
  case int24: \
    byte=__RL_OP_KEY; key byte=0x84; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=3;bitstring[24]; \
    byte=__RL_OP_END; \
  case int24s: \
    byte=__RL_OP_KEY; key byte=0x85; \
    byte=__RL_OP_BEGIN; byte=24; \
    array{byte=3;bitstring[24];}; \
    byte=__RL_OP_END; \
  case long: \
    byte=__RL_OP_KEY; key byte=0x86; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=4; longint; \
    byte=__RL_OP_END; \
  case int32: \
    byte=__RL_OP_KEY; key byte=0x86; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=4; longint; \
    byte=__RL_OP_END; \
  case longword: \
    byte=__RL_OP_KEY; key byte=0x86; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=4; longint; \
    byte=__RL_OP_END; \
  case longs: \
    byte=__RL_OP_KEY; key byte=0x87; \
    byte=__RL_OP_BEGIN; byte=24; \
    array{byte=4; longint;}; \
    byte=__RL_OP_END; \
  case int32s: \
    byte=__RL_OP_KEY; key byte=0x87; \
    byte=__RL_OP_BEGIN; byte=24; \
    array{byte=4; longint;}; \
    byte=__RL_OP_END; \
  case longwords: \
    byte=__RL_OP_KEY; key byte=0x87; \
    byte=__RL_OP_BEGIN; byte=24; \
    array{byte=4; longint;}; \
    byte=__RL_OP_END; \
  case cstring: \
    byte=__RL_OP_KEY; key byte=0x88; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=__RL_OP_CSTRING; cstring; \
    byte=__RL_OP_END; \
  case c: \
    byte=__RL_OP_KEY; key byte=0x88; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=__RL_OP_CSTRING; cstring; \
    byte=__RL_OP_END; \
  case romlength: \
    byte=__RL_OP_KEY; key byte=0x89; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=__RL_OP_ROMLENGTH; \
    byte=__RL_OP_END; \
  case romcrc: \
    byte=__RL_OP_KEY; key byte=0x8a; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=__RL_OP_ROMCRC; \
    byte=__RL_OP_END; \
  case blocksize: \
    byte=__RL_OP_KEY; key byte=0x8b; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=__RL_OP_BLOCKSIZE; \
    byte=__RL_OP_END; \
  case treesize: \
    byte=__RL_OP_KEY; key byte=0x8c; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=__RL_OP_TREESIZE; \
    byte=__RL_OP_END; \
  case vidmodename: \
    byte=__RL_OP_KEY; key byte=0x8d; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=__RL_OP_BLOCKSIZE; \
    byte=2; integer;  \
    byte=__RL_OP_CSTRING; cstring; \
    byte=__RL_OP_ALIGN; byte=2; \
    byte=__RL_OP_END; \
  case v: \
    byte=__RL_OP_KEY; key byte=0x8d; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=__RL_OP_BLOCKSIZE; \
    byte=2; integer;  \
    byte=__RL_OP_CSTRING; cstring; \
    byte=__RL_OP_ALIGN; byte=2; \
    byte=__RL_OP_END; \
  case type: \
    byte=__RL_OP_KEY; key byte=0x8e; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=8; \
    integer __RL_STYPE_CATEGORY_ENUMS \
    integer __RL_STYPE_CTYPE_ENUMS \
    integer __RL_STYPE_DRSW_ENUMS \
    integer __RL_STYPE_DRHW_ENUMS \
    byte=__RL_OP_END; \
  case t: \
    byte=__RL_OP_KEY; key byte=0x8e; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=8; \
    integer __RL_STYPE_CATEGORY_ENUMS \
    integer __RL_STYPE_CTYPE_ENUMS \
    integer __RL_STYPE_DRSW_ENUMS \
    integer __RL_STYPE_DRHW_ENUMS \
    byte=__RL_OP_END; \

#define __RL_SELECTORS \
  array { \
    switch { \
      case file:  key byte=__RL_SEL_FILENAME; pstring; \
      case name:  key byte=__RL_SEL_NAME;     pstring; \
      case type:  key byte=__RL_SEL_TYPE;     longint; \
      case id:    key byte=__RL_SEL_ID;       integer; \
      case local: key byte=__RL_LOCAL; \
    }; \
  } \

#define __RL_NODE_CASES \
  case loc: \
    byte=__RL_OP_KEY; key byte=0x19; \
    byte=__RL_OP_INCLUDE; \
    byte=__RL_SEL_LOCAL; \
    byte=__RL_SEL_NAME; pstring; \
    byte=0; \
  case l: \
    byte=__RL_OP_KEY; key byte=0x19; \
    byte=__RL_OP_INCLUDE; \
    byte=__RL_SEL_LOCAL; \
    byte=__RL_SEL_NAME; pstring; \
    byte=0; \
  case ext: \
    byte=__RL_OP_KEY; key byte=0x1a; \
    byte=__RL_OP_INCLUDE; \
    byte=__RL_SEL_FILENAME; pstring; \
    byte=__RL_SEL_NAME;     pstring; \
    byte=0; \
  case e: \
    byte=__RL_OP_KEY; key byte=0x1a; \
    byte=__RL_OP_INCLUDE; \
    byte=__RL_SEL_FILENAME; pstring; \
    byte=__RL_SEL_NAME;     pstring; \
    byte=0; \
  case any: \
    byte=__RL_OP_KEY; key byte=0x1b; \
    byte=__RL_OP_INCLUDE; \
    byte=__RL_SEL_NAME;     pstring; \
    byte=0; \
  case a: \
    byte=__RL_OP_KEY; key byte=0x1b; \
    byte=__RL_OP_INCLUDE; \
    byte=__RL_SEL_NAME;     pstring; \
    byte=0; \
  case match: \
    byte=__RL_OP_KEY; key byte=0x1c; \
    byte=__RL_OP_INCLUDE; \
    __RL_SELECTORS; \
    byte=0; \
  case node: \
    byte=__RL_OP_KEY; key byte=0x1d; \
    array{switch{__RL_RESTRICTED_FIELD_CASES};}; \
  __RL_RESTRICTED_FIELD_CASES \

#define __RL_OFFSET_NODE_CASES \
  case loc: \
    byte=__RL_OP_KEY; key byte=0x99; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=__RL_OP_INCLUDE; \
    byte=__RL_SEL_LOCAL; \
    byte=__RL_SEL_NAME; pstring; \
    byte=0; \
    byte=__RL_OP_END; \
  case l: \
    byte=__RL_OP_KEY; key byte=0x99; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=__RL_OP_INCLUDE; \
    byte=__RL_SEL_LOCAL; \
    byte=__RL_SEL_NAME; pstring; \
    byte=0; \
    byte=__RL_OP_END; \
  case ext: \
    byte=__RL_OP_KEY; key byte=0x9a; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=__RL_OP_INCLUDE; \
    byte=__RL_SEL_FILENAME; pstring; \
    byte=__RL_SEL_NAME;     pstring; \
    byte=0; \
    byte=__RL_OP_END; \
  case e: \
    byte=__RL_OP_KEY; key byte=0x9a; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=__RL_OP_INCLUDE; \
    byte=__RL_SEL_FILENAME; pstring; \
    byte=__RL_SEL_NAME;     pstring; \
    byte=0; \
    byte=__RL_OP_END; \
  case any: \
    byte=__RL_OP_KEY; key byte=0x9b; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=__RL_OP_INCLUDE; \
    byte=__RL_SEL_NAME;     pstring; \
    byte=0; \
    byte=__RL_OP_END; \
  case a: \
    byte=__RL_OP_KEY; key byte=0x9b; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=__RL_OP_INCLUDE; \
    byte=__RL_SEL_NAME;     pstring; \
    byte=0; \
    byte=__RL_OP_END; \
  case match: \
    byte=__RL_OP_KEY; key byte=0x9c; \
    byte=__RL_OP_BEGIN; byte=24; \
    byte=__RL_OP_INCLUDE; \
    __RL_SELECTORS; \
    byte=0; \
    byte=__RL_OP_END; \
  case node: \
    byte=__RL_OP_KEY; key byte=0x9d; \
    byte=__RL_OP_BEGIN; byte=24; \
    array{switch{__RL_RESTRICTED_FIELD_CASES};}; \
    byte=__RL_OP_END; \
  __RL_OFFSET_RESTRICTED_FIELD_CASES \

// Symbolic constants for data{} construct.
#define __RL_DATA_VALUE_ENUMS\
  clutType=0x0,\
  fixedType=0x1,\
  directType=0x2,\
  MIIBoardId=0x10,\
  ciVidBoardID=0x1f,\
  CX16VidBoardID=0x20,\
  MIIxBoardId=0x21,\
  SE30BoardID=0x22,\
  MIIcxBoardId=0x23,\
  MIIfxBoardId=0x24,\
  EricksonBoardID=0x28,\
  ElsieBoardID=0x29,\
  TIMBoardID=0x2a,\
  EclipseBoardID=0x2b,\
  SpikeBoardID=0x33,\
  DBLiteBoardID=0x35,\
  ZydecoBrdID=0x36,\
  ApolloBoardID=0x38,\
  PDMBrdID=0x39,\
  VailBoardID=0x3a,\
  WombatBrdID=0x3b,\
  ColumbiaBrdID=0x3c,\
  CycloneBrdID=0x3d,\
  CompanionBrdID=0x3e,\
  DartanianBoardID=0x40,\
  DartExtVidBoardID=0x46,\
  CSCBoardID=0x4a,\
  EscherBoardID=0x4a,\
  TempestBrdID=0x50,\
  BlackBirdBdID=0x58,\
  BBExtVidBdID=0x59,\
  YeagerBoardID=0x5a,\
  BoardIDDblExp=0x2f,\
  DAFBPDSBoardID=0x37;

#define __RL_LIST_ENTRY_CASES \
  case data: \
    byte=__RL_OP_KEY; key byte=0x32; \
    byte=3; \
    bitstring[24] __RL_DATA_VALUE_ENUMS \
  case d: \
    byte=__RL_OP_KEY; key byte=0x32; \
    byte=3; \
    bitstring[24] __RL_DATA_VALUE_ENUMS \
  case offset: \
    byte=__RL_OP_KEY; key byte=0x33; \
    switch{__RL_OFFSET_NODE_CASES}; \
  case include: \
    byte=__RL_OP_KEY; key byte=0x34; \
    switch{__RL_NODE_CASES}; \
  __RL_OFFSET_NODE_CASES \

#define __RL_FIELD_CASES \
  __RL_RESTRICTED_FIELD_CASES \
  case align: \
    byte=__RL_OP_KEY; key byte=0x4b; \
    byte=__RL_OP_ALIGN; byte; \
  case begin: \
    byte=__RL_OP_KEY; key byte=0x4c; \
    byte=__RL_OP_BEGIN; byte=24; \
  case begin32: \
    byte=__RL_OP_KEY; key byte=0x4d; \
    byte=__RL_OP_BEGIN; byte=32; \
  case end: \
    byte=__RL_OP_KEY; key byte=0x4e; \
    byte=__RL_OP_END; \
  case include: \
    byte=__RL_OP_KEY; key byte=0x4f; \
    switch{__RL_NODE_CASES}; \
  case offset: \
    byte=__RL_OP_KEY; key byte=0x50; \
    byte=__RL_OP_BEGIN; byte=24; \
    switch{__RL_NODE_CASES}; \
    byte=__RL_OP_END; \
  case offset32: \
    byte=__RL_OP_KEY; key byte=0x51; \
    byte=__RL_OP_BEGIN; byte=32; \
    switch{__RL_NODE_CASES}; \
    byte=__RL_OP_END; \
  case anchor: \
    byte=__RL_OP_KEY; key byte=0x52; \
    byte=__RL_OP_ANCHOR; longint; \
  case begin_bump: \
    byte=__RL_OP_KEY; key byte=0x53; \
    byte=__RL_OP_BEGIN; byte=128|24;longint; \
  case begin32_bump: \
    byte=__RL_OP_KEY; key byte=0x54; \
    byte=__RL_OP_BEGIN; byte=128|32;longint; \
  case offset_bump: \
    byte=__RL_OP_KEY; key byte=0x55; \
    byte=__RL_OP_BEGIN; byte=128|24;longint; \
    switch{__RL_NODE_CASES}; \
    byte=__RL_OP_END; \
  case offset32_bump: \
    byte=__RL_OP_KEY; key byte=0x56; \
    byte=__RL_OP_BEGIN; byte=128|32;longint; \
    switch{__RL_NODE_CASES}; \
    byte=__RL_OP_END; \

// General purpose node builder, when no convenient template exists.
type 'node' {array{switch{__RL_FIELD_CASES};};};

// Format block.
type 'form' {
  byte=1; byte=0;
  switch{__RL_LIST_ENTRY_CASES};  // Offset to sResource directory
  byte=__RL_OP_ROMLENGTH;
  byte=__RL_OP_ROMCRC;
  byte=8;
  byte;                         // Revision level
  byte                          // Format
    appleFormat=1;
  longint=0x5A932BC7;           // Test pattern
  byte;                         // Reserved (set to 0)
  byte;                         // ByteLanes
};

// Extended Format block.
type 'xfrm' {
  byte=1; byte=$$Byte(fhFormat);
  switch{__RL_LIST_ENTRY_CASES};  // Offset to superInit sExecBlock
  byte=1; byte=0xfe;
  switch{__RL_LIST_ENTRY_CASES};  // Offset to superDirectory.
  byte=4; longint=0xFF000000;   // List terminator
  byte=4; longint=0x5A932BC7;   // Test pattern
  byte=1; byte=0;
  switch{__RL_LIST_ENTRY_CASES};  // Offset to sResource directory
  byte=__RL_OP_ROMLENGTH;
  byte=__RL_OP_ROMCRC;
  byte=8;
  byte;                         // Revision level
 fhFormat:
  byte                          // Format
    appleFormat=1;
  longint=0x5A932BC7;           // Test pattern
  byte;                         // Reserved (set to 0)
  byte;                         // ByteLanes
};

// CString
type 'cstr' {
  byte=__RL_OP_CSTRING; cstring;
};

// Long
type 'long' {
  byte=4; longint;
};

// sResource type node
type 'styp' {
  byte=8;
  integer __RL_STYPE_CATEGORY_ENUMS  // Category
  integer __RL_STYPE_CTYPE_ENUMS     // cType
  integer __RL_STYPE_DRSW_ENUMS      // drSW
  integer __RL_STYPE_DRHW_ENUMS      // DrHW
};

// sExec blocks
type 'exec' {
  byte=__RL_OP_BLOCKSIZE;
  byte=8;
  byte                         //Revision level
    sExec2=2;
  byte                         //CPU id
    sCPU68000=1,
    sCPU68020=2,
    sCPU68030=3,
    sCPU68040=4;
  integer;                     //Reserved
  longint=4;                   //Offset to code
  switch{__RL_NODE_CASES}; //Code
};

// Primary Inits
type 'pini' as 'exec';

// Secondary Inits
type 'sini' as 'exec';

// Video Device Reocrd
type 'vdev' {
  byte=__RL_OP_BLOCKSIZE;
  byte=42;
  longint;          /* vpBaseOffset */
  integer;          /* vpRowBytes */
  rect;             /* vpBounds */
  integer;          /* vpVersion */
  integer;          /* vpPackType */
  longint;          /* vpPacksize */
  longint;          /* vpHRes */
  longint;          /* vpVRes */
  integer;          /* vpPixelType */
  integer;          /* vpPixelSize */
  integer;          /* vpCmpCount */
  integer;          /* vpCmpSize */
  longint;          /* vpPlaneBytes */
};

// sPRAMInitRecord
type 'pram' {
  byte=12;
  longint=12;     //Physical block size
  byte=0; byte=0; //Unused
  byte;           //Byte 1
  byte;           //Byte 2
  byte;           //Byte 3
  byte;           //Byte 4
  byte;           //Byte 5
  byte;           //Byte 6
};

// Video Mode Name sBlock
type 'vmna' {
  byte=__RL_OP_BLOCKSIZE;
  byte=2;
  integer;        //localization resID
  byte=__RL_OP_CSTRING;
  cstring;        //name
  byte=__RL_OP_ALIGN; byte=2;
};


#define fLCDScreen	      0
#define fBuiltInDisplay   1
#define fDefaultColor	  2
#define fActiveBlack	  3
#define fDimMinAt1	  	  4

#define fOpenAtStart      1
#define f32BitMode        2

//--------------------------------------------------------------------- 	start	<LW4>
// sResource: sBlockTransferInfo, mBlockTransferInfo bit defines
//---------------------------------------------------------------------
#define fIsMaster			31
#define fMstrLockedXfer		30
#define fMstrXferSz16		19
#define fMstrXferSz8 		18
#define fMstrXferSz4		17
#define fMstrXferSz2		16
#define fIsSlave			15
#define fSlvXferSz16		3
#define fSlvXferSz8 		2
#define fSlvXferSz4			1
#define fSlvXferSz2			0
																		//	end		<LW4>

//Generic List
type 'list' {
  array{
    byte = 1;
    byte
      sRsrcType            = 0x1,
      sRsrcName            = 0x2,
      sRsrcIcon            = 0x3,
      sRsrcDrvrDir         = 0x4,
      sRsrcLoadRec         = 0x5,
      sRsrcBootRec         = 0x6,
      sRsrcFlags           = 0x7,
      sRsrcHWDevId         = 0x8,
      minorBaseOS          = 0xa,
      minorLength          = 0xb,
      majorBaseOS          = 0xc,
      majorLength          = 0xd,
      sRsrcTest            = 0xe,
      sRsrcCIcon           = 0xf,
      sRsrcIcl8            = 0x10,
      sRsrcIcl4            = 0x11,
      sGammaDir            = 0x40,
      sRsrcVidNames        = 0x41,
      sRsrcDock            = 0x50,
      sDiagRec             = 0x55,
      sVidAuxParams        = 0x7b,			// Change this name to something better                                            
      sDebugger		       = 0x7c,
      sVidAttributes       = 0x7d,
      sVidParmDir          = 0x7e,
      boardId              = 0x20,
      pRAMInitData         = 0x21,
      primaryInit          = 0x22,
      timeOutConst         = 0x23,
      vendorInfo           = 0x24,
      boardFlags           = 0x25,
      secondaryInit        = 0x26,
      MajRAMSp             = 0x81,
      MinROMSp             = 0x82,
      vendorId             = 0x1,
      serialNum            = 0x2,
      revLevel             = 0x3,
      partNum              = 0x4,
      Date                 = 0x5,
      testByte             = 0x20,
      testWord             = 0x21,
      testLong             = 0x22,
      testString           = 0x23,
      sMacOS68000          = 0x1,
      sMacOS68020          = 0x2,
      sMacOS68030          = 0x3,
      sMacOS68040          = 0x4,
      oneBitMode           = 0x80,
      twoBitMode           = 0x81,
      fourBitMode          = 0x82,
      eightBitMode         = 0x83,
      sixteenBitMode       = 0x84,
      thirtyTwoBitMode     = 0x85,
      firstVidMode         = 0x80,
      secondVidMode        = 0x81,
      thirdVidMode         = 0x82,
      fourthVidMode        = 0x83,
      fifthVidMode         = 0x84,
      sixthVidMode         = 0x85,
      spGammaDir           = 0x40,
      spVidNamesDir        = 0x41,
      mVidParams           = 0x1,
      mTable               = 0x2,
      mPageCnt             = 0x3,
      mDevType             = 0x4;
    switch{__RL_LIST_ENTRY_CASES};
  };
  byte=4; longint = 0xFF000000;       // Terminator
};

//SuperDirectory
type 'spdr' {
  array{
    byte = 1;
    byte;
    switch{__RL_LIST_ENTRY_CASES};
  };
  byte=4; longint = 0xFF000000;       // Terminator
};

//sResource directory
type 'sdir' {
  array{
    byte = 1;
    byte;
    switch{__RL_LIST_ENTRY_CASES};
  };
  byte=4; longint = 0xFF000000;       // Terminator
};

//Board sResource
type 'boar' {
  array{
    byte = 1;
    byte
      sRsrcType            = 0x1,
      sRsrcName            = 0x2,
      sRsrcIcon            = 0x3,
      sRsrcDrvrDir         = 0x4,
      sRsrcLoadRec         = 0x5,
      sRsrcBootRec         = 0x6,
      sRsrcFlags           = 0x7,
      sRsrcHWDevId         = 0x8,
      minorBaseOS          = 0xa,
      minorLength          = 0xb,
      majorBaseOS          = 0xc,
      majorLength          = 0xd,
      sRsrcTest            = 0xe,
      sRsrcCIcon           = 0xf,
      sRsrcIcl8            = 0x10,
      sRsrcIcl4            = 0x11,
	  sBlockTransferInfo   = 0x14,		// <LW4>
 	  sMaxLockedTransferCount = 0x15,	// <LW4>
      sGammaDir            = 0x40,
      sRsrcVidNames        = 0x41,
      sRsrcDock            = 0x50,
      sDiagRec             = 0x55,
      sVidAuxParams        = 0x7b,			// Change this name to something better                                            
      sDebugger		       = 0x7c,
      sVidAttributes       = 0x7d,
      sVidParmDir          = 0x7e,
	  sUndefinedID		   = 0xb6,		// <LW6>
      boardId              = 0x20,
      pRAMInitData         = 0x21,
      primaryInit          = 0x22,
      timeOutConst         = 0x23,
      vendorInfo           = 0x24,
      boardFlags           = 0x25,
      secondaryInit        = 0x26;
    switch{__RL_LIST_ENTRY_CASES};
  };
  byte=4; longint = 0xFF000000;       // Terminator
};

//Function sResource
type 'srsc' {
  array{
    byte = 1;
    byte
      sRsrcType            = 0x1,
      sRsrcName            = 0x2,
      sRsrcIcon            = 0x3,
      sRsrcDrvrDir         = 0x4,
      sRsrcLoadRec         = 0x5,
      sRsrcBootRec         = 0x6,
      sRsrcFlags           = 0x7,
      sRsrcHWDevId         = 0x8,
      minorBaseOS          = 0xa,
      minorLength          = 0xb,
      majorBaseOS          = 0xc,
      majorLength          = 0xd,
      sRsrcTest            = 0xe,
      sRsrcCIcon           = 0xf,
      sRsrcIcl8            = 0x10,
      sRsrcIcl4            = 0x11,
      sGammaDir            = 0x40,
      sRsrcVidNames        = 0x41,
      sRsrcDock            = 0x50,
      sDiagRec             = 0x55,
      sVidAttributes       = 0x7d,
      sVidParmDir          = 0x7e,
      MajRAMSp             = 0x81,
      MinROMSp             = 0x82,
      testByte             = 0x20,
      testWord             = 0x21,
      testLong             = 0x22,
      testString           = 0x23,
      oneBitMode           = 0x80,
      twoBitMode           = 0x81,
      fourBitMode          = 0x82,
      eightBitMode         = 0x83,
      sixteenBitMode       = 0x84,
      thirtyTwoBitMode     = 0x85,
      firstVidMode         = 0x80,
      secondVidMode        = 0x81,
      thirdVidMode         = 0x82,
      fourthVidMode        = 0x83,
      fifthVidMode         = 0x84,
      sixthVidMode         = 0x85,
      spGammaDir           = 0x40,
      spVidNamesDir        = 0x41;
    switch{__RL_LIST_ENTRY_CASES};
  };
  byte=4; longint = 0xFF000000;       // Terminator
};

//Driver directory
type 'ddir' {
  array{
    byte = 1;
    byte
      sMacOS68000          = 0x1,
      sMacOS68020          = 0x2,
      sMacOS68030          = 0x3,
      sMacOS68040          = 0x4;
    switch{__RL_LIST_ENTRY_CASES};
  };
  byte=4; longint = 0xFF000000;       // Terminator
};

//Gamma directory
type 'gdir' {
  array{
    byte = 1;
    byte;
    switch{__RL_LIST_ENTRY_CASES};
  };
  byte=4; longint = 0xFF000000;       // Terminator
};

//Video Mode Names directory
type 'vdir' {
  array{
    byte = 1;
    byte;
    switch{__RL_LIST_ENTRY_CASES};
  };
  byte=4; longint = 0xFF000000;       // Terminator
};

//Vendor Info record
type 'vend' {
  array{
    byte = 1;
    byte
      vendorId             = 0x1,
      serialNum            = 0x2,
      revLevel             = 0x3,
      partNum              = 0x4,
      Date                 = 0x5;
    switch{__RL_LIST_ENTRY_CASES};
  };
  byte=4; longint = 0xFF000000;       // Terminator
};

//Video Mode Info
type 'vmod' {
  array{
    byte = 1;
    byte
      mVidParams           = 0x1,
      mTable               = 0x2,
      mPageCnt             = 0x3,
      mDevType             = 0x4;
    switch{__RL_LIST_ENTRY_CASES};
  };
  byte=4; longint = 0xFF000000;       // Terminator
};

#ifndef _NO_SINL_
// Control resource to tell ROMLink which resource types denote
// ROMLink-encoded resources.
type 'SINL' { array{longint;}; };
resource 'SINL' (32767, "SINL Resource for ROMLink-defined templates.") {{
  'node';
  'form';
  'xfrm';
  'cstr';
  'long';
  'styp';
  'exec';
  'pini';
  'sini';
  'vdev';
  'pram';
  'vmna';
  'list';
  'spdr';
  'sdir';
  'boar';
  'srsc';
  'ddir';
  'gdir';
  'vdir';
  'vend';
  'vmod';
}};
#endif

// ROML resources declare configuration information that modifies ROMLink's
// behavior.

type 'roml' {
  array {
    switch {
      case endRom: key longint='endr'; longint;
    };
  };
};

#endif // already included
