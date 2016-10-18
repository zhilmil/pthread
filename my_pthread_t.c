
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <ucontext.h>

#include "queue.h"
#include "my_pthread_t.h"
#include "common.h"
#include "scheduler.h"
#include "context.h"


void my_pthread_create(my_pthread_t* thread, pthread_attr_t* attr,void *(*function)(void*),void* arg)
{
	printf("Asd1");
	populateThread(thread, makeContext(function));
	printf("Asd5");
	
	setcontext(thread->context);
	
	//scheduleForExecution(thread);
}

void populateThread(my_pthread_t* thread, ucontext_t * newContext)
{
	static unsigned currThreadID=0;
	thread->st = READY;
	thread->context = newContext;
	thread->tid = ++currThreadID;
	thread->priority = 1;
	thread->last_start_time = (long int)time(0);
	printf("ads\n");
}




