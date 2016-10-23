#ifndef CONTEXT
#define CONTEXT


#include <ucontext.h>

ucontext_t* makeContext(void *(*function)(void*), void* arg);
ucontext_t* makeEmptyContext();

#endif