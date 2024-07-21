/*
				File:		List.c
			
				Contains:	This file contains code for the CTE List functions.  
							These functions permit the caller to locate and act
							on test nodes.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
		 <1>	  9/4/90	SS		first checked in
			
				To Do:
*/

#include "List.h"


Node *InitNode(Node *theNode, ULONG key, void *contents)
{
		theNode->key = key ;
		theNode->contents = contents ;
		return(theNode) ;
}


void *GetNodeContents(Node *theNode)
{
		return(theNode->contents) ;
}


LONG GetNodeKey(Node *theNode)
{
		return(theNode->key) ;
}




List *InitList(List *theList)
{
		theList->head = (Node *)&theList->tail ;
		theList->tailPred = (Node *)&theList->head ;
		theList->tail = 0 ;
		theList->currentNode = (Node *)&theList->head ;
		return(theList) ;
}


Node *FindNextNode(List *theList)
{
		Node *theNextNode ;
		
		theNextNode = theList->currentNode->succ ;
		
		if((Node *)&theList->tail != theNextNode)
				theList->currentNode = theNextNode ;
		else
				theNextNode = NULL ;
				
		return(theNextNode) ;
}

Node *FindPrevNode(List *theList)
{
		Node *thePrevNode ;
		
		thePrevNode = theList->currentNode->pred ;
		
		if((Node *)&theList->head != thePrevNode)
				theList->currentNode = thePrevNode ;
		else
				thePrevNode = NULL ;
				
		return(thePrevNode) ;
}


Node *FindFirstNode(List *theList)
{
		Node *theFirstNode ;
				
		theFirstNode = theList->head ;
		
		if((Node *)&theList->tail == theFirstNode)
		{
				theList->currentNode = (Node *)&theList->head ;
				theFirstNode = NULL ;
		}else{
				theList->currentNode = theFirstNode ;
		}
		
		return(theFirstNode) ;
}


Node *FindLastNode(List *theList)
{
		Node *theLastNode ;
		
		theLastNode = theList->tailPred ;
		
		if((Node *)&theList->head != theLastNode)
				theList->currentNode = theLastNode ;
		else
				theLastNode = NULL ;
				
		return(theLastNode) ;
}


Node *FindKeyedNode(List *theList, LONG theKey)
{
		Node *keyedNode = NULL ;
		Node *n ;
		
		for(n = FindFirstNode(theList); n; n = FindNextNode(theList))
		{
				if(theKey == GetNodeKey(n))
				{
						keyedNode = n ;
						break ;
				}
		}
		
		return(keyedNode) ;
}


Node *InsertNode(List *theList, Node *theNode)
{
		theNode->pred = (Node *)&(theList->head) ;
		theNode->succ = theList->head ;
		theNode->pred->succ = theNode ;
		theNode->succ->pred = theNode ;
		
		/*
		printf("Node::insert\n") ;
		printf("\t&node = %p\n", theNode) ;
		printf("\tpred =  %p\n", theNode->pred) ;
		printf("\tsucc =  %p\n", theNode->succ) ;
		*/
		
		return(theNode) ;
}


Node *AppendNode(List *theList, Node* theNode)
{
		theNode->pred = theList->tailPred ;
		theNode->succ = (Node *)(&theList->tail) ;
		theNode->pred->succ = theNode ;
		theNode->succ->pred = theNode ;

		/*
		printf("Node::append\n") ;
		printf("\t&node = %p\n", theNode) ;
		printf("\tpred =  %p\n", theNode->pred) ;
		printf("\tsucc =  %p\n", theNode->succ) ;
		*/
		
		return(theNode) ;
}


Node *RemoveNode(Node *theNode)
{
		theNode->pred->succ = theNode->succ ;
		theNode->succ->pred = theNode->pred ;
		theNode->pred = NULL ;
		theNode->succ = NULL ;
		return(theNode) ;
}

