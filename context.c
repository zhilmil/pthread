#include <stdio.h>
#include <unistd.h>
#include <ucontext.h>

#include "context.h"
#include "scheduler.h"
#define STACKSIZE 64000

void * wrapper(void *(*function)(void*))
{
	function(NULL);
	abruptEnding();
}

ucontext_t* makeContext(void *(*function)(void*))
{
	ucontext_t * newContext = (ucontext_t*)malloc(sizeof(ucontext_t));
	newContext->uc_link = 0;
	newContext->uc_stack.ss_sp = malloc(STACKSIZE);
	newContext->uc_stack.ss_size = STACKSIZE;
	newContext->uc_stack.ss_flags = 0;
	getcontext(newContext);
	makecontext(newContext, (void(*)(void))wrapper, 1, function);
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


