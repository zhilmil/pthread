#include <ucontext.h>
#include "my_pthread_t.h"

int currThreadID = 0;
void populateThread(my_pthread_t* thread, ucontext_t * newContext)
{
	static unsigned currThreadID=0;
	thread->st = READY;
	thread->context = newContext;
	thread->tid = ++currThreadID;
	thread->priority = 1;
	thread->retval = 0;
	//thread->currentlyYielded = false;
	thread->last_start_time = (long int)time(0);
}

void setStatus(my_pthread_t* thread, STATE newState)
{
	thread->st = newState;
}

STATE getStatus(my_pthread_t* thread)
{
	return thread->st;
}

void incrementPriority(my_pthread_t* thread)
{
	if(thread->priority > 1)
	{
		thread->priority--;
	}
}

void decrementPriority(my_pthread_t* thread)
{
	if(thread->priority < 4)
	{
		thread->priority++;
	}
}

int getPriority(my_pthread_t* thread)
{
	return thread->priority;
}

void setPriority(my_pthread_t* thread, int priority)
{
	thread->priority = priority;
}

