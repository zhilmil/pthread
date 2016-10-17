#ifndef CONTEXT
#define CONTEXT


#include <ucontext.h>

ucontext_t* makeContext(void *(*function)(void*))

#endif