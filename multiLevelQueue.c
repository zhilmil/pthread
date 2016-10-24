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
		//printf("queue 1 used for enque\n");
		enque(&P1q, input);
	}
	else
	{
		//printf("queue 2 used for enque\n");
		enque(&P2q, input);
	}
}

queueNode_t* mDeque(int failMeNot)
{
	stepCounter = (++stepCounter)%4;
	if(stepCounter == 0 || stepCounter == 1)
	{		
		//printf("queue 1 used for deque\n");
		if(getSize(&P1q) != 0)
		{
			return deque(&P1q);
		}
		else if(getSize(&P2q) != 0)
		{
			return deque(&P2q);
		}
		else
		{
			return NULL;
		}
	}
	else if(stepCounter == 2 || failMeNot >= 1)
	{
		if(getSize(&P2q) != 0)
		{
			return deque(&P2q);
		}
		else if(getSize(&P1q) != 0)
		{
			return deque(&P1q);
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		//printf("None dequeued\n");
		return NULL;
	}
}

void maintainenceCycle()
{
	//printf("maintainenceCycle Begun\n");
	queueIterator_t* qi = getIterator(&P2q);
	queueNode_t* qn = getNextNode(qi);
	while(qn != NULL)
	{
		my_pthread_t* thread = getThread(qn);
		incrementPriority(thread);
		int priority = getPriority(thread);
		if(priority < 3)
		{
			removeNode(qi, qn);
			mEnque(qn);
			//printf("Modifed priority for this node. Current Priority: %d\n", priority);
		}
		qn = getNextNode(qi);
	}
}

void initMQ()
{
	initQueue(&P1q);
	initQueue(&P2q);
	stepCounter = 0;
}