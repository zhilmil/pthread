#include "my_pthread_t.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#define STACKSIZE 64000
#include "queue.h"

unsigned currThreadID=0;
//Functions 

queue_t P1q; //higher priority queue
queue_t P2q; //lower priority queue
queue_t Wq; //wait queue

void my_pthread_create(my_pthread_t* thread, pthread_attr_t* attr,void *(*function)(void*),void* arg) {
	my_scheduler_init();
	//Initializing thread node
	queueNode_t* node = createNode();
	
	//Initialzing thread variables
	thread->st = READY;
	ucontext_t * newcontext = (ucontext_t*)malloc(sizeof(ucontext_t));
	thread->context = newcontext;
	thread->context->uc_link = 0;
	thread->stack = malloc(STACKSIZE);
	thread->context->uc_stack.ss_sp = thread->stack;
	thread->context->uc_stack.ss_size = STACKSIZE;
	thread->context->uc_stack.ss_flags = 0;
	
	currThreadID++;
	thread->tid = currThreadID;
	thread->priority = 1;
	node->thread = thread;
	
	long int t = (long int)time(0);
	thread->last_start_time = t;
	
	printf("enqueuing generated node\n");
	enque(&P1q,node);

	printf("Making context\n");
	makecontext(thread->context,(void(*)(void))&function,0);
	printf("thread created%d \n",thread->tid); 
//	return 0;
}

int my_pthread_exit(void *value_ptr);

void my_pthread_yield();

int my_pthread_join(pthread_t thread,void **value_ptr);

void my_scheduler_init();

void scheduler() {

}

