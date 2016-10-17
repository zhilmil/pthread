#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#include "scheduler.h"
#include "common.h"
#include "timer.h"


//Functions 

queue_t P1q; //higher priority queue
queue_t P2q; //lower priority queue
queue_t Wq; //wait queue

boolean initialized = false;

void timeSliceExpired ()
{
 	printf("Timer fired\n");
}

void mySchedulerInit()
{
	// Todo: This is wrong. Figure out a thread safe way to prevent the scheduler from getting initialized twice.
	srand(time(0));	
	usleep((rand()%100));
	if(!initialized)
	{
		initialized = true;
		printf("Scheduler initialized\n");
	}

	setTimer(&timeSliceExpired, 50);
}