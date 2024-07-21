/*
	File:		MACEecfg.r

	Contains:	'ecfg' resource templates for MACE built-in ethernet systems

	Written by:	Mark A. Law

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	  6/7/93	kc		first checked in
	   <LW2>	 3/21/93	mal		Versioned MACE 'ecfg' rsrc record and removed 24-bit MACEBase
									field.

	To Do:
*/

Type 'ecfg'
{
	unsigned integer;			/* Record version						*/
	unsigned hex longint;		/* 32-bit MACE address					*/
	unsigned hex longint;		/* Ethernet PROM address				*/
	unsigned hex byte;			/* MACE transmit frame control			*/
	unsigned hex byte;			/* MACE receive frame control			*/
	unsigned hex byte;			/* MACE xmit/recv fifo config control	*/
	unsigned hex byte;			/* MACE MAC config control				*/
	hex string [6];				/* Alternate ethernet address			*/
	unsigned integer;			/* Alternate # transmit buffers			*/
	unsigned integer;			/* Alternate # receive buffers			*/
	unsigned integer;			/* Alternate # receive chains			*/
};


Resource 'ecfg' (43, "Cyclone33") {
	1,
	0x50F1C000,
	0x50F08000,
	0x1,
	0,
	0x2C,
	0x3,
	$"",
	0,
	0,
	0
};

Resource 'ecfg' (78, "Cyclone40") {
	1,
	0x50F1C000,
	0x50F08000,
	0x1,
	0,
	0x2C,
	0x3,
	$"",
	0,
	0,
	0
};

Resource 'ecfg' (60, "Tempest25") {
	1,
	0x50F1C000,
	0x50F08000,
	0x1,
	0,
	0x2C,
	0x3,
	$"",
	0,
	0,
	0
};

Resource 'ecfg' (79, "Tempest33") {
	1,
	0x50F1C000,
	0x50F08000,
	0x1,
	0,
	0x2C,
	0x3,
	$"",
	0,
	0,
	0
};
