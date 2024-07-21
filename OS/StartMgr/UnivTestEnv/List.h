/*
				File:		List.h
			
				Contains:	This is the include file for the CTE "List" functions.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
		 <1>	  9/4/90	SS		first checked in
			
				To Do:
*/
#ifndef _List_
#define _List_

#include "GenericTypes.h"

//
// Node
//
struct Node
{
		struct Node *succ ;
		struct Node *pred ;
		ULONG key ;
		void *contents ;
} ;

#ifndef __cplusplus
typedef struct Node Node ;
#endif __cplusplus


//
// List
//
struct List
{
		Node *head ;
		Node *tail ;
		Node *tailPred ;
		Node *currentNode ;
} ;

#ifndef __cplusplus
typedef struct List List ;
#endif __cplusplus


#ifdef __cplusplus
extern "C" {
#endif __cplusplus

// Functions that operate on nodes.
Node *InitNode(Node *theNode, ULONG key, void *contents) ;
char *GetNodeContents(Node *theNode) ;
LONG GetNodeKey(Node *theNode) ;

// Functions that operate on lists.
List *InitList(List *theList) ;
Node *FindNextNode(List *theList) ;
Node *FindPrevNode(List *theList) ;
Node *FindFirstNode(List *theList) ;
Node *FindLastNode(List *theList) ;
Node *FindKeyedNode(List *theList, LONG theKey) ;
Node *InsertNode(List *theList, Node *n) ;
Node *AppendNode(List *theList, Node* n) ;
Node *RemoveNode(Node *n) ;

#ifdef __cplusplus
}		// close the extern "C" declaration
#endif __cplusplus

#endif _List_
