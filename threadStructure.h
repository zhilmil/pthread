#ifndef THREADSTRUCTURE
#define THREADSTRUCTURE
#include <ucontext.h>
#include "my_pthread_t.h"


void populateThread(my_pthread_t* thread, ucontext_t * newContext);

#endif