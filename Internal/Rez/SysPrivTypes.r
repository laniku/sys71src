/*
	File:		SysPrivTypes.r

	Contains:	templates for System file resources

	Copyright:	© 1983-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM3>	 12/1/92	RB		Added the declaration for the 'rovm' resource to override some
									system resources which we want used from ROM since the ROM
									versions are up to date.
		 <1>	  2/6/92	DTY		first checked in
*/

	type 'dbex' { integer=0; };		// nothing

//_______________________________________________________________________________________
// CPU Gibbly templates

	type 'gbly' {
		integer	GibblyVersion1 = 1;			// 'gbly' version
		longint;							// Gibbly timestamp
		integer = $$CountOf(BoxFlags);		// Number of CPUs supported
		array BoxFlags {
			integer;						// BoxFlag of supported CPU
		};
	};
	
	type 'ptbl' {
		integer PatchTableVersion1 = 1;		// 'ptbl' version
		integer = $$CountOf(PatchRanges) - 1;	// # of ranges to load
		wide array PatchRanges {
			integer;						// Start of range to load
			integer;						// End of range to load (inclusive)
		};
	};


//_______________________________________________________________________________________
// ROM Gibbly system override resource

type 'rovm' {
	integer = $$CountOf(OverrideResources);
	array OverrideResources {
		literal longint;
		integer;
	};
};

	
//_______________________________________________________________________________________
// PPC Toolbox templates

	type 'ppci'
	{
		byte;		// freePortMin
		byte;		// freePortMax
		byte;		// freeLocSessMin
		byte;		// freeLocSessMax
		byte;		// freeRemSessMin
		byte;		// freeRemSessMax
		byte;		// freeIPMSessMin
		byte;		// freeIPMSessMax
		byte;		// ADSP time out (6 = 1 sec)
		byte;		// ADSP Retries
		byte;		// NBP time out interval 8-tick units
		byte;		// NBP retries
		pstring;	// NBP Type of PPC Toolbox.
	};

