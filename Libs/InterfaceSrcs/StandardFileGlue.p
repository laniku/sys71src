{
	File:		StandardFileGlue.p

	Contains:	Glue code for so apps can call StandardGetFile and StandardPutFile
				on all systems.
				
	Written by:	Nick Kledzik

	Copyright:	© 1989-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	  9/3/91	ngk		first checked in
		 <0>	 9/03/91	ngk		first created

	To Do:
		
		Test if glue works.
		
		Conditionalize StandardFile.[ph] so that the inline code for 
		StandardGetFile and StandardPutFile is only generated for 
		SystemSevenOrLater.
	
		Change the procedure names in this file to remove the leading x.
		
		Change the Interface.o make file to Lib in StandardFileGlue.p.o
		
}

UNIT StandardFileGlue;


INTERFACE

USES
	StandardFile, GestaltEqu;


	PROCEDURE xStandardPutFile(prompt: Str255;
							  defaultName: Str255;
							  VAR reply: StandardFileReply);
	
	PROCEDURE xStandardGetFile(fileFilter: FileFilterProcPtr;
							  numTypes: INTEGER;
							  typeList: SFTypeList;
							  VAR reply: StandardFileReply);
	


IMPLEMENTATION



	PROCEDURE xStandardGetFile;
	VAR
		response:	LONGINT;
		glueReply:	SFReply;
	
	BEGIN
		{ If StandardGetFile already implemented, then use trap }
		IF (Gestalt(gestaltStandardFileAttr,response) = noErr) & bTST(response, gestaltStandardFile58) THEN
		BEGIN
			StandardGetFile(fileFilter, numTypes, typeList, reply);
			EXIT(xStandardGetFile);
		END;
	
		{ StandardGetFile is not implemented on this system }
		{ Use original SFGetFile, then fill out new reply record. }
		
		SFGetFile(Point($00400040), '', fileFilter, numTypes, typeList, NIL, glueReply);
		
		{ fill out reply record based on info in glue reply record }
		reply.sfGood 		:= glueReply.good;
		reply.sfReplacing	:= FALSE;				{ what does SF do?}
		reply.sfType		:= glueReply.fType;		{ what does SF do?}
		
		{ convert WDRefNum to vRefNum/DirID
		err := GetWDInfo(glueReply.vRefNum, reply.sfFile.vRefNum, reply.sfFile.dirID, dummy); 
		reply.sfFile.name 	:= glueReply.fName;
		
		reply.sfScript		:= smSystemScript;
		reply.sfFlags		:= 0;					{ what does SF do?}
		reply.sfIsFolder	:= FALSE;
		reply.sfIsVolume	:= FALSE;
    
	
	END; { xStandardGetFile }





	PROCEDURE xStandardPutFile;
	VAR
		response:	LONGINT;
		glueReply:	SFReply;
		dummy:		LONGINT;
	BEGIN
		{ If StandardPutFile already implemented, then use trap }
		IF (Gestalt(gestaltStandardFileAttr,response) = noErr) & bTST(response, gestaltStandardFile58) THEN
		BEGIN
			StandardPutFile(prompt, defaultName, reply);
			EXIT(xStandardPutFile);
		END;
		
		
		{ StandardPutFile is not implemented on this system }
		{ Use original SFPutFile, then fill out new reply record. }
		
		SFPutFile(Point($00400040), prompt, defaultName, NIL, glueReply);
		
		{ fill out reply record based on info in glue reply record }
		reply.sfGood 		:= glueReply.good;
		reply.sfReplacing	:= glueReply.copy;		{ maybe we should check? }
		reply.sfType		:= glueReply.fType;		{ what does SF do?}
		
		{ convert WDRefNum to vRefNum/DirID
		err := GetWDInfo(glueReply.vRefNum, reply.sfFile.vRefNum, reply.sfFile.dirID, dummy); 
		reply.sfFile.name 	:= glueReply.fName;
		
		reply.sfScript		:= smSystemScript;
		reply.sfFlags		:= 0;					{ what does SF do?}
		reply.sfIsFolder	:= FALSE;
		reply.sfIsVolume	:= FALSE;
	
	END; { xStandardPutFile }
	



END.


