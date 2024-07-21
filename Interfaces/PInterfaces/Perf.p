
{
Created: Monday, January 22, 1990 at 9:18 PM
	Perf.p
	Pascal Interface to the Macintosh Libraries

	Copyright Apple Computer, Inc.	1986-1991
	All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <2>	  8/8/91	JL		Update copyright

	To Do:
	
	DESCRIPTION
	Provides for PC-sampling of User code resources, ROM code, and RAM (misses).
	Produces output text file suitable for input to PerformReport.
	
	Design objectives:
	Language independent, i.e. works with Pascal, C, and Assembly.
	Covers user resources as well as ROM code.
	Memory model independent, i.e. works for Desk Accessories and drivers.
	Uses TimeManager on new ROMs, Vertical Blanking interrupt on 64 K ROMs.
	
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT Perf;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingPerf}
{$SETC UsingPerf := 1}

{$I+}
{$SETC PerfIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := PerfIncludes}

TYPE

PLongs = ^ALongs;
ALongs = ARRAY [1..8000] OF LONGINT;

PInts = ^AInts;
HInts = ^PInts;

AInts = ARRAY [1..8000] OF INTEGER;

{ PerfGlobals are declared as a record, so main program can allocate
as globals, desk accessory can add to globals allocated via pointer,
print driver can allocate via low memory, etc. }


TP2PerfGlobals = ^TPerfGlobals;
TPerfGlobals = RECORD
	startROM: LONGINT;			{ROM Base}
	romHits: LONGINT;			{used if MeasureROM is false}
	misses: LONGINT;			{count of PC values outside measured memory}
	segArray: PLongs;			{array of segment handles}
	sizeArray: PLongs;			{array of segment sizes}
	idArray: HInts; 			{array of segment rsrc IDs}
	baseArray: PLongs;			{array of offsets to counters for each segment}
	samples: PLongs;			{samples buffer}
	buffSize: LONGINT;			{size of samples buffer in bytes}
	timeInterval: INTEGER;		{number of clock intervals between interrupts}
	bucketSize: INTEGER;		{size of buckets power of 2}
	log2buckSize: INTEGER;		{used in CvtPC}
	pcOffset: INTEGER;			{offset to the user PC at interrupt time.}
	numMeasure: INTEGER;		{# Code segments (w/o jump table)- ROM etc.}
	firstCode: INTEGER; 		{index of first Code segment}
	takingSamples: BOOLEAN; 	{true if sampling is enabled}
	measureROM: BOOLEAN;
	measureCode: BOOLEAN;
	ramSeg: INTEGER;			{index of "segment" record to cover RAM > 0 if RAM (misses) are to be bucketed.}
	ramBase: LONGINT;			{beginning of RAM being measured.}
	measureRAMbucketSize: INTEGER;
	measureRAMlog2buckSize: INTEGER;
	romVersion: INTEGER;
	vRefNum: INTEGER;			{Volume where the report file is to be created}
	volumeSelected: BOOLEAN;	{True if user selects the report file name}
	rptFileName: Str255;		{Report file name}
	rptFileCreator: Str255; 	{Report File Creator}
	rptFileType: Str255;		{Report File type}
	getResType: ResType;		{Resource type}
	END;



FUNCTION InitPerf(VAR thePerfGlobals: TP2PerfGlobals;timerCount: INTEGER;
	codeAndROMBucketSize: INTEGER;doROM: BOOLEAN;doAppCode: BOOLEAN;appCodeType: Str255;
	romID: INTEGER;romName: Str255;doRAM: BOOLEAN;ramLow: LONGINT;ramHigh: LONGINT;
	ramBucketSize: INTEGER): BOOLEAN;
{ called once to setup Performance monitoring
 }

PROCEDURE TermPerf(thePerfGlobals: TP2PerfGlobals);
{ if InitPerf succeeds then TermPerf must be called before terminating program.
 }

FUNCTION PerfControl(thePerfGlobals: TP2PerfGlobals;turnOn: BOOLEAN): BOOLEAN;
{ Call this to turn off/on measuring.
 Returns previous state.
 }

FUNCTION PerfDump(thePerfGlobals: TP2PerfGlobals;reportFile: Str255;doHistogram: BOOLEAN;
	rptFileColumns: INTEGER): INTEGER;
{ Call this to dump the statistics into a file. }


{$ENDC}    { UsingPerf }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

