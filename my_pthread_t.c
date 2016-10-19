
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <ucontext.h>

#include "queue.h"
#include "my_pthread_t.h"
#include "common.h"
#include "scheduler.h"
#include "context.h"
#include "threadStructure.h"

void my_pthread_create(my_pthread_t* thread, pthread_attr_t* attr,void *(*function)(void*),void* arg)
{	
	populateThread(thread, makeContext(function));
	
	scheduleForExecution(thread);
}

void my_pthread_yield()
{
	yield();
}

int my_pthread_exit(void *value_ptr)
{
	abruptEnding();
}




