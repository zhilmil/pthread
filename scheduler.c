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
#include "multiLevelQueue.h"
#include "my_pthread_t.h"
#include "threadStructure.h"
#include "queue.h"



//Functions 


queue_t Wq; //wait queue

boolean initialized = false;
boolean pauseAlarms = false;
queueNode_t* currentlyExecuting = NULL;
boolean abnormalEnding = false;
boolean yielded = false;

void timeSliceExpired ()
{
	//Some sort of a crappy issue with timers. Only the last set one is firing.
	static int counter = 0;
	counter = (++counter)%3;
	if(counter == 2)
	{
		maintainenceCycle();
	}
	//printf("Scheduler ran\n");
	// Ugly hack to ensure we don't get interupted while switching contexts.
	if(pauseAlarms) return;
	// Pick the next node to execute
	queueNode_t* nextNodeToExecute;
	if(!yielded)
		nextNodeToExecute = mDeque(0);
	else
		nextNodeToExecute = mDeque(1);	
	// check if the queue was empty.
	if(nextNodeToExecute == NULL)
 	{
 		return;
 	}
 	// Prepare to swap out the current context unless, you are instructed otherwise.
 	ucontext_t * currentContext;	 	
 	if(currentlyExecuting != NULL)
 	{	
 		my_pthread_t* thread = getThread(currentlyExecuting);
		currentContext = thread->context;
		if(!abnormalEnding)
		{
			decrementPriority(thread);
		}
		
	}
	else
	{
		currentContext = makeEmptyContext();
		my_pthread_t* currentThread = (my_pthread_t *)malloc(sizeof(my_pthread_t));
		populateThread(currentThread, currentContext);
		currentlyExecuting = createNode(currentThread);		
		//getcontext(currentContext);
	}
	mEnque(currentlyExecuting);
	currentlyExecuting = nextNodeToExecute;	
	my_pthread_t* thread = getThread(nextNodeToExecute);
	
	setStatus(thread, RUNNING);
	// Do the swaping.
	abnormalEnding = false;
	yielded = false;
	swapcontext(currentContext, thread->context);
}

void loadNewThread()
{

	queueNode_t* nextNodeToExecute = mDeque(1);
	// check if the queue was empty.
	if(nextNodeToExecute == NULL)
 	{
 		return;
 	}
 	// Make an empty context.
 	ucontext_t * currentContext = makeEmptyContext();
 	currentlyExecuting = nextNodeToExecute;
	my_pthread_t* thread = getThread(currentlyExecuting);
	// Do the swaping.
	swapcontext(currentContext, thread->context);
}

void mySchedulerInit()
{	
	setTimer(&timeSliceExpired, 50);
	initMQ();
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
	mEnque(qn);
}

void abruptEnding(void* output)
{
	// Set the currently Executing to null so that it doesn't get rescheduled ever.
	// loadNewThread from the queue and start executing it.
	
// Zhilmil added status change
	//printf("OLO%d %d\n", ((my_pthread_t*)currentlyExecuting->thread)->tid, ((my_pthread_t*)currentlyExecuting->thread)->last_start_time);
	if(output != NULL)
		getThread(currentlyExecuting)->retval = output;
	//(my_pthread_t*)currentlyExecuting->thread)->st = FINISHED;
	currentlyExecuting = NULL;
	pauseAlarms = false;

	// End the current time slice.
	loadNewThread();
}

void yield()
{
	// End the current time slice, so our thread gets swapped out.
	/*if(currentlyExecuting != NULL)
		setStatus(getThread(currentlyExecuting), WAITING);*/
	abnormalEnding = true;
	yielded = true;
	timeSliceExpired();
}



