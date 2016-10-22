#include <stdio.h>

#include "queue.h"
#include "multiLevelQueue.h"
#include "threadStructure.h"

queue_t P1q; //higher priority queue
queue_t P2q; //lower priority queue
int stepCounter;

void mEnque(queueNode_t* input)
{
	int priority = getPriority(getThread(input));
	if(priority < 3)
	{
		enque(&P1q, input);
	}
	else
	{
		enque(&P2q, input);
	}
}

queueNode_t* mDeque()
{
	stepCounter = (++stepCounter)%4;
	if(stepCounter == 0 || stepCounter == 1)
	{		
		return deque(&P1q);
	}
	else if(stepCounter == 2)
	{
		return deque(&P2q);
	}
	else
	{
		return NULL;
	}
}

void initMQ()
{
	initQueue(&P1q);
	initQueue(&P2q);
	stepCounter = 0;
}