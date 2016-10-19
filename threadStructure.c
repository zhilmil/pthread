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
	//thread->currentlyYielded = false;
	thread->last_start_time = (long int)time(0);
}
