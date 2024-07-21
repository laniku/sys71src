/*
	File:		PPCUtilities.c
			
	Contains:	General routines for supporting PPC.
			
	Written by:	Eric M. Trehus
			
	Copyright:	© 1990-1993 by Apple Computer, Inc., all rights reserved.
			
	Change History (most recent first):
			
	   <SM5>	  3/9/93	PN		Remove ReQueueInformPB,Insert, Push,InitQueue, TraverseQueue
									which is no longer used
		<10>	 4/14/92	BBM		<JSM>: Remove unfinished PPC code that is under the contitional
									“TheFutute”, and remove the conditional “CubeE” since that is
									reality. Remove conditionals, since all they do is confuse.
		 <9>	 10/4/91	JSM		Change PsychoticFarmerOrLater conditionals to TheFuture.
		 <8>	 9/29/91	DTY		Conditionalize out <6> and <7> for CubeE.
		 <7>	 6/12/91	EMT		Remove code that references the number of pending messages
		 <6>	  6/4/91	EMT		Roll in StoreAndForward Revisions
		 <5>	 11/6/90	EMT		use STATIC in place of static for link maps
		 <4>	10/18/90	EMT		Remove some un-referenced/ifdefed out procedures.
		 <3>	10/11/90	EMT		remove #define DEBUG
		 <2>	  9/5/90	EMT		Make this file C3.0 Friendly
			
*/

#include "PPCCommon.h"
#include <AppleTalk.h>
#include <ADSP.h>
#include <String.h>
#include <stdarg.h>

/*---------------------------------------------------------------------------------------------------
	Prototypes of functions used only in this file.
---------------------------------------------------------------------------------------------------*/
STATIC void AddNew(QUEUE *theQueue,int number,int len);
STATIC void RemOld(QUEUE *theQueue,int number);

/*---------------------------------------------------------------------------------------------------
	Pointer Compare is a utility SearchFunc for use with many QUEUE routines.
---------------------------------------------------------------------------------------------------*/

Boolean PointerCompare(void *ptr,unsigned long Value)
{
	return((unsigned long)ptr == Value);
}


#ifdef DEBUG
Boolean InQueue(void *PB,QUEUE *Queue)
{
	return (PB == SearchQueue(Queue,(unsigned long)PB,PointerCompare,1));
}
#endif

/*---------------------------------------------------------------------------------------------------
	EnQueue places Element at the end of the Queue.
---------------------------------------------------------------------------------------------------*/

void EnQueue(void *Element,QUEUE *Queue)
ELEMENT *Element;
{
	short p;

#ifdef DEBUG
	if(!Element)
		DebugStr("\pElement is NULL");
	if(!Queue)
		DebugStr("\pQueue is NULL");
	if(InQueue(Element,Queue))
		DebugStr("\pElement already in Queue");
#endif

	p = spl(kNoInterrupts);
	Element->Next = NULL;					/* Make our list NULL ended */
	if(Queue->qSize)
	{
		Queue->Tail->Next = Element;		/* Link in the new Element */
		Queue->Tail = Element;				/* Update Tail */
	}
	else									/* The Queue is empty */
	{
		Queue->Head = Element;				/* Head and Tail is the same Element */
		Queue->Tail = Element;
	}
	Queue->qSize++;							/* Show that the Queue has grown */
	spl(p);
}

/*---------------------------------------------------------------------------------------------------
	ServeQueue removes an element from the from of the Queue, otherwise returns NULL.
---------------------------------------------------------------------------------------------------*/

void *ServeQueue(QUEUE *Queue)
{
	ELEMENT *ptr;
	short p;
	
#ifdef DEBUG
	if(!Queue)
		DebugStr("\pQueue is NULL");
#endif
	p = spl(kNoInterrupts);
	if(Queue->qSize)
	{
		ptr = Queue->Head;					/* FIFO */
		Queue->Head = ptr->Next;			/* Update Head to point to Next Element */
		Queue->qSize--;						/* show that the Queue has shrunken */
	}
	else
		ptr = NULL;							/* No Elements in the Queue */
	spl(p);
	return(ptr);
}

/*---------------------------------------------------------------------------------------------------
	SearchQueue looks for Value using SearchFunc to compare Value with each element
	in the queue.  When the Nth element is found a pointer to that queue element is
	returned.
---------------------------------------------------------------------------------------------------*/
void *SearchQueue(QUEUE *Queue,unsigned long Value,SearchFuncPtr SearchFunc,int Nth)
{
	ELEMENT *ptr;
	int i;
	unsigned short p;
	
#ifdef DEBUG
	if(!Queue)
		DebugStr("\pQueue is NULL");
#endif
	p = spl(kNoInterrupts);
	ptr = Queue->Head;
	for(i=0;i<Queue->qSize;i++)
	{
		if((*SearchFunc)(ptr,Value))
		{
			--Nth;
			if(!Nth)
				goto Done;
		}
		ptr = ptr->Next;
	}
	ptr = NULL;
Done:
	spl(p);
	return(ptr);
}


/*---------------------------------------------------------------------------------------------------
	DeleteFromQueue removes an Element from the Queue
---------------------------------------------------------------------------------------------------*/

void *DeleteFromQueue(QUEUE *Queue,unsigned long Value,SearchFuncPtr SearchFunc)
{
	ELEMENT *ptr;
	int i;
	ELEMENT *RemElm;
	short p;
	
#ifdef DEBUG
	if(!Queue)
		DebugStr("\pQueue is NULL");
#endif
	p = spl(kNoInterrupts);
	RemElm = NULL;
	ptr = (ELEMENT *)&Queue->Head;				/* The Head may change */
	for(i=0;i<Queue->qSize;i++)
	{
		if((*SearchFunc)(ptr->Next,Value))
		{
			RemElm = ptr->Next;
			ptr->Next = ptr->Next->Next;
			if(RemElm == Queue->Tail)
				Queue->Tail = ptr;
			Queue->qSize--;
			break;
		}
		ptr = ptr->Next;
	}
	spl(p);
	return(RemElm);					/* Client must free the memory itself */
}

/*---------------------------------------------------------------------------------------------------
	DeleteMultiple removes multiple Element from the Queue.
	NOTE:	DeleteMultiple removes each element from the Queue before calling DoProc.
	If DoProc returns false, DeleteMultiple places the element back into the Queue,
	otherwise it assumes that the element is no longer needed.	This algorithm may
	create little windows of oppertunity for bugs to appear since elements that are
	not to be deleted are temporarily out of their queue.
---------------------------------------------------------------------------------------------------*/

void DeleteMultiple(QUEUE *Queue,unsigned long Value,SearchFuncPtr DoProc)
{
	int i;
	ELEMENT *theElement;
	
#ifdef DEBUG
	if(!Queue)
		DebugStr("\pQueue is NULL");
#endif
	for(i=Queue->qSize;i;i--)
	{
		if(theElement = ServeQueue(Queue))
		{
			if(!(*DoProc)(theElement,Value))
				EnQueue(theElement,Queue);
		}
	}
}



void *NewMem(long len)
{
	return NewPtrSysClear(len);
}

void DisposeMem(void *Mem)
{
	DisposPtr(Mem);
}

STATIC void AddNew(QUEUE *theQueue,int number,int len)
{
	void *Mem;
	
	while(number--)
	{
		if(Mem = NewMem(len))
			EnQueue(Mem,theQueue);
		else
			break;
	}
}

STATIC void RemOld(QUEUE *theQueue,int number)
{
	void *Mem;
	
	while(number--)
	{
		if(Mem = ServeQueue(theQueue))
			DisposeMem(Mem);
		else
			break;
	}
}

void Replenish(PPCGlobalParamsPtr ppcglobPtr)
{	
	if(ppcglobPtr->freePortQueue.qSize < ppcglobPtr->configData.freePortMin)
		AddNew(&ppcglobPtr->freePortQueue,ppcglobPtr->configData.freePortMin - ppcglobPtr->freePortQueue.qSize,sizeof(PPCPortEntry));
	
	if(ppcglobPtr->freeLocationQueue.qSize < ppcglobPtr->configData.freePortMin)
		AddNew(&ppcglobPtr->freeLocationQueue,ppcglobPtr->configData.freePortMin - ppcglobPtr->freeLocationQueue.qSize,sizeof(PortLocationTable));

	if(ppcglobPtr->freeLocSessQueue.qSize < ppcglobPtr->configData.freeLocSessMin)
		AddNew(&ppcglobPtr->freeLocSessQueue,ppcglobPtr->configData.freeLocSessMin - ppcglobPtr->freeLocSessQueue.qSize,sizeof(LocalIPCParams));
		
	if(ppcglobPtr->freeRemSessQueue.qSize < ppcglobPtr->configData.freeRemSessMin)
		AddNew(&ppcglobPtr->freeRemSessQueue,ppcglobPtr->configData.freeRemSessMin - ppcglobPtr->freeRemSessQueue.qSize,sizeof(NetIPCParams));
}

void Excess(PPCGlobalParamsPtr ppcglobPtr)
{	
	if(ppcglobPtr->freePortQueue.qSize > ppcglobPtr->configData.freePortMax)
		RemOld(&ppcglobPtr->freePortQueue,ppcglobPtr->freePortQueue.qSize - ppcglobPtr->configData.freePortMax);
		
	if(ppcglobPtr->freeLocationQueue.qSize > ppcglobPtr->configData.freePortMax)
		RemOld(&ppcglobPtr->freeLocationQueue,ppcglobPtr->freeLocationQueue.qSize - ppcglobPtr->configData.freePortMax);

	if(ppcglobPtr->freeLocSessQueue.qSize > ppcglobPtr->configData.freeLocSessMax)
		RemOld(&ppcglobPtr->freeLocSessQueue,ppcglobPtr->freeLocSessQueue.qSize - ppcglobPtr->configData.freeLocSessMax);
		
	if(ppcglobPtr->freeRemSessQueue.qSize > ppcglobPtr->configData.freeRemSessMax)
		RemOld(&ppcglobPtr->freeRemSessQueue,ppcglobPtr->freeRemSessQueue.qSize - ppcglobPtr->configData.freeRemSessMax);
}

