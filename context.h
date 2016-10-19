#ifndef CONTEXT
#define CONTEXT


#include <ucontext.h>

ucontext_t* makeContext(void *(*function)(void*));
ucontext_t* makeEmptyContext();

#endif