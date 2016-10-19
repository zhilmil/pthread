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
queueNode_t* currentlyExecuting = NULL;

void timeSliceExpired ()
{

	
 	//Grab the next node to execute. Check if it is null.  
 	//If it is, then keep executing the one you are currently executing.
 	queueNode_t* nextNodeToExecute = deque(&P1q);	
 	if(nextNodeToExecute == NULL)
 	{
 		return;
 	}
 	if(currentlyExecuting!= NULL)
		enque(&P1q, currentlyExecuting);
	currentlyExecuting = nextNodeToExecute;
	my_pthread_t* thread = (my_pthread_t *)(nextNodeToExecute->thread);
 	const ucontext_t* context = thread->context; 	
 	setcontext(context);
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
	printf("AA\n");
	queueNode_t * qn = createNode(thread);
	enque(&P1q, qn);
}

void abruptEnding()
{
	currentlyExecuting = NULL;
	timeSliceExpired();
}