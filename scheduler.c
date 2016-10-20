#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <ucontext.h>

#include "scheduler.h"
#include "common.h"
#include "timer.h"
#include "queue.h"
#include "my_pthread_t.h"
#include "threadStructure.h"



//Functions 

queue_t P1q; //higher priority queue
queue_t P2q; //lower priority queue
queue_t Wq; //wait queue

boolean initialized = false;
boolean pauseAlarms = false;
queueNode_t* currentlyExecuting = NULL;

void timeSliceExpired ()
{
	// Ugly hack to ensure we don't get interupted while switching contexts.
	if(pauseAlarms) return;
	// Pick the next node to execute
	queueNode_t* nextNodeToExecute = deque(&P1q);
	// check if the queue was empty.
	if(nextNodeToExecute == NULL)
 	{
 		return;
 	}
 	// Prepare to swap out the current context unless, you are instructed otherwise.
 	ucontext_t * currentContext;	 	
 	if(currentlyExecuting != NULL)
 	{	
		currentContext = ((my_pthread_t*)(currentlyExecuting->thread))->context;
		
	}
	else
	{
		currentContext = makeEmptyContext();
		my_pthread_t* currentThread = (my_pthread_t *)malloc(sizeof(my_pthread_t));
		populateThread(currentThread, currentContext);
		currentlyExecuting = createNode(currentThread);
		//getcontext(currentContext);
	}
	enque(&P1q, currentlyExecuting);
	currentlyExecuting = nextNodeToExecute;
	my_pthread_t* thread = (my_pthread_t *)(nextNodeToExecute->thread);
	// Do the swaping.
	swapcontext(currentContext, thread->context);
}

void loadNewThread()
{

	queueNode_t* nextNodeToExecute = deque(&P1q);
	// check if the queue was empty.
	if(nextNodeToExecute == NULL)
 	{
 		return;
 	}
 	// Make an empty context.
 	ucontext_t * currentContext = makeEmptyContext();
 	currentlyExecuting = nextNodeToExecute;
	my_pthread_t* thread = (my_pthread_t *)(nextNodeToExecute->thread);
	// Do the swaping.
	swapcontext(currentContext, thread->context);
}

void mySchedulerInit()
{	
	setTimer(&timeSliceExpired, 50);
	// As of for now, only working with high priority queue.
	initQueue(&P1q);
}

void scheduleForExecution(my_pthread_t* thread)
{
	if(!initialized)
	{
		// Todo: This is wrong. Figure out a thread safe way to prevent the scheduler from getting initialized twice.
		srand(time(0));	
		usleep((rand()%100));
		initialized = true;
		printf("Scheduler initialized\n");
		mySchedulerInit();
		//setcontext(&currentContext);
	}
	// Added a createNode function in queue.c that takes a thread and returns a queue node.
	queueNode_t * qn = createNode(thread);
	enque(&P1q, qn);
}

void abruptEnding()
{
	// Set the currently Executing to null so that it doesn't get rescheduled ever.
	// loadNewThread from the queue and start executing it.
	currentlyExecuting = NULL;
	pauseAlarms = false;
	// End the current time slice.
	loadNewThread();
}

void yield()
{
	// End the current time slice, so our thread gets swapped out.
	timeSliceExpired();
}