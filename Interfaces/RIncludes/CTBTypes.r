/************************************************************
	CTBTypes.r
	Resource types for the Communications Toolbox

	Written by:	Byron Han

		Copyright Apple Computer, Inc. 1988-1992
		All rights reserved

	Change History (most recent first):

		<12>	 6/24/92	DCL		Changed #ifndef __CTBTYPES.R__ to __CTBTYPES_R__  at the request
									of the MPW team (3.2.3 rez broke on the periods)
		<11>	 8/28/91	CH		Updated interface headers for consistency.
		<10>	 8/20/91	BH		added XTI definition for caps
		 <9>	  7/3/91	BH		added faps and taps resources
		 <8>	 6/26/91	BH		fixed typo. sorry
		 <7>	 6/26/91	BH		oops - i messed up the cbnd definition.  now fixed. sorry
		 <6>	 6/26/91	BH		move caps here and include new extensions to caps
		 <5>	 1/10/91	kaz		<jng> Moving 'caps' resource definition to Internal.
		 <4>	  7/2/90	kaz		Fixed 'flst' definition to even out the structure for odd-length
									font names.
		 <3>	 5/22/90	kaz		Updated 'flst' to include a textMode
		 <2>	 3/16/90	BBH		add flst resource type
		 <1>	 3/14/90	BBH		first checked in to BBS

	To Do:
************************************************************/

#ifndef __CTBTYPES_R__
#define __CTBTYPES_R__


/*----------------------------cbnd ¥ Tool resource bundle list ------------------*/
/*----------------------------fbnd ¥ Tool resource bundle list ------------------*/
/*----------------------------tbnd ¥ Tool resource bundle list ------------------*/
type 'cbnd' {
		integer = $$CountOf(TypeArray) - 1;
		array TypeArray {
				literal longint;								/* Type 				*/
				integer = $$CountOf(IDArray) - 1;
				wide array IDArray {
						integer;								/* Local ID 			*/
						integer;								/* Actual ID			*/
				};
		};
};


type 'fbnd' as 'cbnd';

type 'tbnd' as 'cbnd';

/*----------------------------flst ¥ Font Family List----------------------------*/
type 'flst' {
		integer = $$CountOf(Fonts);								/* # of fonts			*/
		array Fonts {
			pstring;											/* 		Font NAME		*/
			align word;
			unsigned hex integer	plain;						/* 		Font Style		*/
			integer;											/*		Font Size		*/
			integer;											/* 		Font Mode		*/
		};
};


/*----------------------------caps ¥ Connection tool capabilities list-----------*/

/* Define flags for "Channels" field of 'caps' resource */
#define cmData				(1 << 0)
#define cmCntl				(1 << 1)
#define cmAttn				(1 << 2)

#define	cmDataNoTimeout	 	(1 << 4)
#define	cmCntlNoTimeout 	(1 << 5)
#define cmAttnNoTimeout 	(1 << 6)

#define cmDataClean			(1 << 8)
#define cmCntlClean			(1 << 9)
#define cmAttnClean			(1 << 10)

//	for end of message field of caps resource
#define cmFlagsEOM			(1 << 0);

/* Connection tool capabilities resource */
type 'caps' {
	integer = $$CountOf (PairsArray);
	
	array PairsArray {

		switch {
			case Abort:
				key literal longint 	= 'ABRT';
				literal longint
					supported 		= 1,
					notSupported 	= 0;
	
			case AppleTalkBased:
				key literal longint		= 'ATLK';
				longint	appletalkBased		=	1,
						notAppletalkBased	=	0;
						
			case Break:
				key literal longint 	= 'BRK ';
				literal longint
					synchronousOnly 	= 'SYNC',
					asynchronousOnly 	= 'ASYN',
					both 				= 'BOTH',
					notSupported 		= 0;
					
			case Channels:
				key literal longint 	= 'CHAN';
				hex longint;
					
			case Close:
				key literal longint 	= 'CLOS';
				literal longint
					synchronousOnly 	= 'SYNC',
					asynchronousOnly 	= 'ASYN',
					both 				= 'BOTH',
					notSupported 		= 0;
					
			case EndOfMessage:
				key literal longint 	= 'EOM ';
				hex longint;
				
			case Kill:
				key literal longint 	= 'KILL';
				literal longint
					supported 		= 1,
					notSupported 	= 0;
					
			case Listen:
				key literal longint 	= 'LSTN';
				literal longint
					synchronousOnly 	= 'SYNC',
					asynchronousOnly 	= 'ASYN',
					both 				= 'BOTH',
					notSupported 		= 0;
					
			case LowLevelIO:
				key literal longint 	= 'LLIO';
				literal longint
					supported 		= 1,
					notSupported 	= 0;
					
			case MinimumMemory:
				key literal longint 	= 'MEMM';
				hex longint;
					
			case Open:
				key literal longint 	= 'OPEN';
				literal longint
					synchronousOnly 	= 'SYNC',
					asynchronousOnly 	= 'ASYN',
					both 				= 'BOTH',
					notSupported 		= 0;
					
			case Order:
				key literal longint 	= 'ORDR';
				longint guaranteed 		= 1, 
						notGuaranteed 	= 0;
				
			case Protocol:
				key literal longint 	= 'PROT';
				literal longint
					ISDN	= 'ISDN',
					TCP 	= 'TCP ',
					ADSP 	= 'ADSP',
					NSP 	= 'NSP ',
					LAT 	= 'LAT ',
					NSPg 	= 'NSPg',
					LATg 	= 'LATg',
					Serial 	= 'SERD',
					Modem	= 'MODM',
					MacPAD 	= 'PAD ';
					
			case Read:
				key literal longint 	= 'READ';
				literal longint
					synchronousOnly 	= 'SYNC',
					asynchronousOnly 	= 'ASYN',
					both 				= 'BOTH',
					notSupported 		= 0;
					
			case RecommendedMemory:
				key literal longint 	= 'MEMR';
				hex longint;
					
			case Reliability:
				key literal longint 	= 'RELY';
				longint guaranteed 		= 1, 
						notGuaranteed 	= 0;
				
			case Service:
				key literal longint 	= 'SERV';
				literal longint
					Datagram 			= 'DGRM',
					Stream 				= 'STRM';
			
			case Timeout:
				key literal longint 	= 'TOUT';
				literal longint
					supported 		= 1,
					notSupported 	= 0;
					
			case Write:
				key literal longint 	= 'WRIT';
				literal longint
					synchronousOnly 	= 'SYNC',
					asynchronousOnly 	= 'ASYN',
					both 				= 'BOTH',
					notSupported = 0;
					
			case XTI:								/* reserved for Apple for nowÉ */
				key literal longint 	= 'XTI ';
				literal longint
					notSupported = 0;
					
		};
	};
};

/*----------------------------faps ¥ File Transfer tool capabilities list-----------*/
type 'faps' {
	integer = $$CountOf (PairsArray);
	
	array PairsArray {
		switch {
			case BatchTransfers:					/* i.e. support for FTSend/FTReceive */
				key literal longint		= 'BXFR';
				literal longint
					supported			= 	1,
					notSupported		= 	0;
	
			case FileTypesSupported:				/* types of files that can be transferred */
				key literal longint		= 'TYPE';
				literal longint
					textOnly			=	'TEXT',
					allTypes			=	'????';
				
			case TransferModes:						/* send/receive or both */
				key literal longint 	= 'MODE';
				literal longint
					sendOnly			= 	'SEND',
					receiveOnly			=	'RECV',
					sendAndReceive	 	= 	'BOTH',
					notSupported 		= 	0;
		};
	};
};

/*----------------------------taps ¥ Terminal tool capabilities list-----------*/
type 'taps' {
	integer = $$CountOf (PairsArray);
	
	array PairsArray {
		switch {
			case TerminalSearching:					/* i.e. support for TMAddSearch */
				key literal longint		= 'SRCH';
				literal longint
					supported			= 	1,
					notSupported		= 	0;
	
			case TerminalType:				/* types of files that can be transferred */
				key literal longint		= 'TYPE';
				literal longint
					graphicsTerminal	=	'GRFX',
					textTerminal		=	'TEXT',
					both				=	'BOTH';
				
		};
	};
};

#endif __CTBTYPES_R__
