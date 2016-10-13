#include "my_pthread_t.h"
#include <stdio.h>
#include <unistd.h>

//Functions 

int my_pthread_create(pthread_t* thread, pthread_attr_t* attr,void *(*function)(void*),void* arg) {
		
}

int my_pthread_exit(void *value_ptr);

void my_pthread_yield();

int my_pthread_join(pthread_t thread,void **value_ptr);

void my_scheduler_init();

