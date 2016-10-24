#include <stdio.h>
#include <unistd.h>
#include <ucontext.h>

#include "context.h"
#include "scheduler.h"
#define STACKSIZE 64000

void * wrapper(void *(*function)(void*), void* arg)
{
	void* returnValue = function(arg);
	printf("\n%d returan value\n", *((int *)returnValue));
	abruptEnding(returnValue);
}

ucontext_t* makeContext(void *(*function)(void*), void* arg)
{
	ucontext_t * newContext = (ucontext_t*)malloc(sizeof(ucontext_t));
	newContext->uc_link = 0;
	newContext->uc_stack.ss_sp = malloc(STACKSIZE);
	newContext->uc_stack.ss_size = STACKSIZE;
	newContext->uc_stack.ss_flags = 0;
	getcontext(newContext);
	makecontext(newContext, (void(*)(void*))wrapper, 2, function, arg);
	//getcontext(newContext);
	return newContext;
}

ucontext_t* makeEmptyContext()
{
	ucontext_t * currentContext = (ucontext_t*)malloc(sizeof(ucontext_t));
	currentContext->uc_link = 0;
	currentContext->uc_stack.ss_sp = malloc(STACKSIZE);
	currentContext->uc_stack.ss_size = STACKSIZE;
	currentContext->uc_stack.ss_flags = 0;
	return currentContext;
}


