
{
Created: Monday, July 22, 1991 at 7:01 PM
 Language.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1986-1992
  All rights reserved


	Change History (most recent first):

		 <5>	  4/3/92	DCL		Moved all of the Language codes back into Script.[aph]. Yeah,
									it's gonna be big. But it's all part of the global village.
		 <4>	 3/20/92	DCL		#1025005,<KSM>:
									For New IM: Moved some declarations and routines from
									Packages.[ph] to Language.[ph]
		 <3>	 7/23/91	JL		Checked in File from database. Adjusted comments.
		 <2>	  1/2/91	PKE		(bbm) Updated comments and rearranged a few constants to match
									latest Inside Mac summary.
		 <1>	 6/22/90	PKE		New file, separated out from Script.p. Rearranged all of the
									new language codes (34 and up).

	Relevant change history from Script.p:

		<x20>	 6/20/90	PKE		Added about 80 new language codes covering most languages we
									are likely to handle; also added some synonyms for existing
									language codes.
		<x15>	 5/11/90	PKE		Added new constants langTradChinese, langSimpChinese.
		 <x3>	 1/17/90	PKE		Add new constants: several new langXxx constants.
	   <x1.7>	 9/17/89	PKE		Added langKorean.

	To Do:

}

{All of the Language Codes Have been moved into Script.p }

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Language;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingLanguage}
{$SETC UsingLanguage := 1}


{$ENDC} { UsingLanguage }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

