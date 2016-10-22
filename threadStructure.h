#ifndef THREADSTRUCTURE
#define THREADSTRUCTURE

#include <ucontext.h>
#include "my_pthread_t.h"


void populateThread(my_pthread_t* thread, ucontext_t * newContext);
void statusChange(STATE newState);
void setStatus(my_pthread_t* thread, STATE newState);
STATE getStatus(my_pthread_t* thread);
int getPriority(my_pthread_t* thread);
void incrementPriority(my_pthread_t* thread);
void decrementPriority(my_pthread_t* thread);

#endif