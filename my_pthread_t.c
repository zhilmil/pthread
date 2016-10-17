
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#define STACKSIZE 64000

#include "queue.h"
#include "my_pthread_t.h"
#include "common.h"
#include "scheduler.h"
#include "context.h"


void my_pthread_create(my_pthread_t* thread, pthread_attr_t* attr,void *(*function)(void*),void* arg)
{
	populateThread(thread, makeContext(function));
	scheduleForExecution(thread);
}

void populateThread(my_pthread_t* thread, ucontext_t * newContext)
{
	static unsigned currThreadID=0;
	thread->st = READY;
	thread->context = newContext;
	thread->context->uc_link = 0;
	thread->stack = malloc(STACKSIZE);
	thread->context->uc_stack.ss_sp = thread->stack;
	thread->context->uc_stack.ss_size = STACKSIZE;
	thread->context->uc_stack.ss_flags = 0;
	thread->tid = ++currThreadID;
	thread->priority = 1;
	thread->last_start_time = (long int)time(0);
}

int my_pthread_exit(void *value_ptr);

void my_pthread_yield();

int my_pthread_join(pthread_t thread,void **value_ptr);

void my_scheduler_init();

void scheduler() {

}

