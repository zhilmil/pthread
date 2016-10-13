#include <stdio.h>
#include <unistd.h>
#include <ucontext.h>

typedef struct thread {
	unsigned int tid;
	ucontext_t context;
	long long last_start_time;
	state st;
	unsigned int priority;
	void* stack;
} my_pthread_t;

//status of a thread

typedef enum {
	READY = 1;
	WAITING = 2;
	RUNNING = 3;
	FINISHED = 4;
} state;

//Functions 
int my_pthread_create(pthread_t* thread, pthread_attr_t* attr,void *(*function)(void*),void* arg);

int my_pthread_exit(void *value_ptr);

void my_pthread_yield();

int my_pthread_join(pthread_t thread,void **value_ptr);

void my_scheduler_init();

