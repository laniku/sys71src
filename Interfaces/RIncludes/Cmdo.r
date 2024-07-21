/*
	File:		Cmdo.r

	CMDO.R    - Resource description file for building Commando resources.

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <2>	 6/24/92	DCL		Changed #ifndef __CMDO.R__ to __CMDO_R__  at the request of the
									MPW team (3.2.3 rez broke on the periods)

*/


#ifndef __CMDO_R__
#define __CMDO_R__

#define	FilesID						0
#define	MultiFilesID				1
#define	CheckOptionID				2
#define	RadioButtonsID				3
#define	RegularEntryID				4
#define	MultiRegularEntryID			5
#define	BoxID						6
#define	TextBoxID					7
#define	PopUpID						8
#define	NestedDialogID				9
#define	TextTitleID					10
#define	RedirectionID				11
#define	EditPopUpID					12
#define	TriStateButtonsID			13
#define	ListID						14
#define	PictOrIconID				15
#define	DummyID						16
#define	DoItButtonID				17
#define	VersionDialogID				18

#define	CMDOVersion					8

/*		The following are used to set styles, simply add for desired style.
*/
#define bold			1
#define italic			2
#define underline		4
#define outline 		8
#define shadow			16
#define condense		32
#define extend			64

type 'cmdo' {
  integer = CMDOVersion;									/* Version number */
  integer = $$CountOf(dialogs);								/* # of dialogs, at least 1 */
  array dialogs {
	integer;												/* height of the dialog */
	cstring;												/* text displayed in help window */
	align word;

	integer = $$CountOf(itemArray);							/* # of items */
	
	/* The order in which Commando writes out the options is the same order in which the
	   items in this array are entered in your resource declaration.  This is important
	   for those commands which have position dependent parameters. */
	   
	wide array itemArray {
		switch {
			case NotDependent:
				key int = 0;
			
			case Or:
				key byte = 1;
				byte = $$CountOf(OrArray);
				wide array OrArray {
					int;									/* item number dependent upon */
				};
			
			case And:
				key byte = 2;
				byte = $$CountOf(AndArray);
				wide array AndArray {
					int;									/* item number dependent upon */
				};
		};
		switch {
			case Files:
				key byte = FilesID;
				byte	InputFile,							/* These types require the  */
						InputFileOrDir,						/* 'Additional' case below. */
						InputOrOutputFile,
						InputOrOutputOrDir,
						
						OutputFile,							/* These types require the  */
						OutputFileOrDir,					/* 'NoMore' case below.     */
						DirOnly;
				switch {
					case OptionalFile:
						/* Using this case makes a popup with two or three items.
						   This first item is used to select a default file or to
						   select no file.  The second (and third) item(s) are used
						   to select input or output files. */
						key int = 0;
						rect;								/* bounds of title */
						rect;								/* bounds of display box */
						cstring;							/* title */
						cstring;							/* default file */
						cstring;							/* option to return before file */
						cstring;							/* If this item is dependent upon
															   another Files item, an extension
															   can be specified here to be added
															   to the dependents file. */
						cstring;							/* help text for popup */
						byte		dim, dontDim;			/* Normally, dependent items are
															   dimmed if the parent is disabled,
															   if this field is "dontDim", then
															   this item won't be dimmed */
						/* These next three strings are the strings displayed in the popup.  Most
						   of the file types have only two strings but InputOrOutputFile and 
						   InputOrOutputOrDir require three strings.  If a string is set to "",
						   Commando will use a built-in default. */
						cstring;							/* popup item #1 */
						cstring;							/* popup item #2 */
						cstring;							/* popup item #3 */
				
					case RequiredFile:
						/* Using this case makes a button that goes directly to standard
						   file.  Use this case when a file is required and the user doesn't
						   have the choice of a default file or no file. */
						key int = 1;
						rect;								/* bounds of button */
						cstring;							/* title of button */
						cstring;							/* option to return before file */
						cstring;							/* help text for button */
				};
				
				/* Some file types take additional information.  See the comment next to the
				   file types to find out which case to choose here. */
				switch {
					case Additional:
						key	byte = 0;
						cstring;									/* For InputOrOutputFile, an option
																	   can be specified when a new
																	   (or output) file is chosen. */
						cstring	FilterTypes = ":";					/* preferred file extension (i.e. ".c") 
																	   If null, no radio buttons will be
																	   displayed.  If FilterTypes is used,
																	   the radio buttons will toggle
																	   between showing files only with
																	   the types below and all files */
						cstring;									/* title of only files button */
						cstring;									/* title of all files button */
						byte = $$CountOf(TypesArray);				/* up to 4 types may be specified */
						align word;
						array TypesArray {
							literal longint		text = 'TEXT',		/* desired input file type, specify */
												obj  = 'OBJ ',		/* no type for all types */
												appl = 'APPL',
												da   = 'DFIL',
												tool = 'MPST';
						};

					case NoMore:
						key	byte = 1;
				};

			case MultiFiles:
				key byte = MultiFilesID;
				cstring;									/* button title */
				cstring;									/* help text for button */
				align word;
				rect;										/* bounds of button */
				cstring;									/* message like " Source files to compile: " */
				cstring;									/* option returned before each 
															   filename. Can be null */
				switch {
					case MultiInputFiles:
						key byte = 0;
						byte = $$CountOf(MultiTypesArray);			/* up to 4 types may be specified */
						align word;
						array MultiTypesArray {
							literal longint		text = 'TEXT',		/* desired input file type, specify no type */
												obj  = 'OBJ ',		/* for all types */
												appl = 'APPL',
												da   = 'DFIL',
												tool = 'MPST';
						};
						cstring	FilterTypes = ":";					/* preferred file extension (i.e. ".c") 
																	   If null, no radio buttons will be
																	   displayed.  If FilterTypes is used,
																	   the radio buttons will toggle
																	   between showing files only with
																	   the types below and all files */
						cstring;									/* title of only files button */
						cstring;									/* title of all files button */
			
					case MultiDirs:
						key byte = 1;

					case MultiInputFilesAndDirs:
						key byte = 2;

					case MultiOutputFiles:
						key byte = 3;
				};

			case CheckOption:
				key byte = CheckOptionID;
				byte	NotSet, Set;						/* whether button is set or not */
				rect;										/* bounds */
				cstring;									/* title */
				cstring;									/* option returned */
				cstring;									/* help text for button */
			
			case RadioButtons:
				key byte = RadioButtonsID;
				byte = $$CountOf(radioArray);				/* # of buttons */
				wide array radioArray {
					rect;									/* bounds */
					cstring;								/* title */
					cstring;								/* option returned */
					byte	NotSet, Set;					/* whether button is set or not */
					cstring;								/* help text for button */
					align word;
				};
			
			case RegularEntry:
				key byte = RegularEntryID;
				cstring;									/* title */
				align word;
				rect;										/* bounds of title */
				rect;										/* bounds of input box */
				cstring;									/* default value */
				byte		ignoreCase, keepCase;			/* the default value is never displayed
															   in the commando window.  If what the
															   user types in the textedit window
															   matches the default value, then that
															   value isn't displayed.  This flag
															   tells Commando whether to ignore case
															   when comparing the contents of the textedit
															   window with the default value. */
				cstring;									/* option returned */
				cstring;									/* help text for entry */

			case MultiRegularEntry:	/* For scrollable, lists of an option */
				key byte = MultiRegularEntryID;
				cstring;									/* title */
				align word;
				rect;										/* bounds of title */
				rect;										/* bounds of input list */
				byte = $$CountOf(DefEntryList);
				array DefEntryList {
					cstring;								/* default values */
				};
				cstring;									/* option returned. Each value
															   will be preceded with this
															   option */
				cstring;									/* help text for entry */

			case Box:		/* Can be used to draw lines too */
				key byte = BoxID;
				byte			black, gray;				/* color of object */
				rect;										/* bounds of box or line */
				
			case TextBox:	/* Draws a box with title in upper-left */
				key byte = TextBoxID;
				byte			black, gray;				/* color of object */
				rect;										/* bounds of box or line */
				cstring;									/* title */
				
			case TextTitle:
				key byte = TextTitleID;
				byte		plain;							/* style of text */			
				rect;										/* bounds of title */
				int			systemFont;						/* font number to use */
				int			systemSize;						/* font size to use */
				cstring;									/* the text to display */
			
			case PopUp:
				key byte = PopUpID;
				byte		Window, Alias, Font, Set;		/* popup type */
				rect;										/* bounds of title */
				rect;										/* bounds of popup line */
				cstring;									/* title */
				cstring;									/* option returned */
				cstring;									/* help text for popup */
				byte		noDefault, hasDefault;			/* hasDefault if first item is "Default Value" */

			case EditPopUp:
				key byte = EditPopUpID;
				/* For MenuItem, this EditPopUp must be dependent upon another EditPopUp
				   of the MenuTitle type so that the control knows whose menu items to
				   display.
				   
				   For FontSize, this EditPopUp must be dependent upon a PopUp of the
				   Font type so that the control knows what sizes of the font exist. */
				   
				byte 	MenuTitle, MenuItem,				/* Type of editable pop-up */
						FontSize, Alias, Set;
				rect;										/* bounds of title */
				rect;										/* bounds of text edit area */
				cstring;									/* title */
				cstring;									/* option to return */
				cstring;									/* help text for textedit part */
				cstring;									/* help text for popup part */
				
			case NestedDialog:
				key	byte = NestedDialogID;
				byte;										/* the number of the dialog
															   to call.  It must be greater
															   than the current dialog */
				rect;										/* bounds of button */
				cstring;									/* button's title */
				cstring;									/* help text for button */
			
			case Redirection:
				key byte = RedirectionID;
				byte	StandardOutput, DiagnosticOutput,	/* the type of redirection */
						StandardInput;
				point;										/* upper-left point of the whole contraption */

			case TriStateButtons:
				key byte = TriStateButtonsID;
				byte = $$CountOf(threeStateArray);			/* # of buttons */
				cstring;									/* option returned */
				wide array threeStateArray {
					align word;
					rect;									/* bounds */
					cstring;								/* title */
					cstring;								/* string for Clear state */
					cstring;								/* string for DontTouch state */
					cstring;								/* string for Set state */
					cstring;								/* help text for button */
				};

			case List:		/* Puts up a list of "things" and allows multiple selections */
				key byte = ListID;
				byte		Volumes, ShellVars,
							Windows, Aliases;				/* what to display in the list */
				cstring;									/* option to return before each "thing" */
				cstring;									/* title */
				align word;
				rect;										/* bounds of title */
				rect;										/* bounds of list selection box */
				cstring;									/* help text for selection box */

			case PictOrIcon:
				key byte = PictOrIconID;
				byte	Icon, Picture;						/* display a picture or icon */
				int;										/* resource id of icon/picture */
				rect;										/* display bounds */

			case Dummy:
				key byte = DummyID;

			case DoItButton:								/* Allows the 'do it' button to be dependent */
				key byte = DoItButtonID;

			case VersionDialog:								/* Display a dialog when the version # is clicked */
				key byte = VersionDialogID;
				switch {
					case VersionString:						/* Version string embedded right here */
						key byte = 0;
						cstring;							/* Version string of tool (e.g. V2.0) */
					
					case VersionResource:					/* Versions string comes from another resource */
						key byte = 1;
						literal longint;					/* resource type of pascal string containing version string */
						integer;							/* resource id of version string */
				};
				cstring;									/* Version text for help window */
				align word;
				integer		noDialog;						/* Rsrc id of 'DLOG' */
					/* NOTE ¥1: if there is no modal dialog to display when the version
					   string is clicked, set the rsrc id to zero (noDialog).

					   NOTE ¥2: if the version string comes from another resource (VersionResource),
					   the string must be the first thing in the resource and the string must be 
					   a pascal-style string.  A 'STR ' resource is an example of a resource that
					   fits the bill.
					   
					   NOTE ¥3: if the modal dialog is to have a filter proc, the proc
					   must be linked as a 'fltr' resource with the same resource id
					   as the dialog. */
		};
		align word;
	};
	align word;
  };
};

#endif __CMDO_R__
