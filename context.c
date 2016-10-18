#include <stdio.h>
#include <unistd.h>
#include <ucontext.h>

#include "context.h"
#define STACKSIZE 64000

ucontext_t* makeContext(void *(*function)(void*))
{
	ucontext_t * newContext = (ucontext_t*)malloc(sizeof(ucontext_t));
	newContext->uc_link = 0;
	newContext->uc_stack.ss_sp = malloc(STACKSIZE);
	newContext->uc_stack.ss_size = STACKSIZE;
	newContext->uc_stack.ss_flags = 0;
	getcontext(newContext);
	makecontext(newContext,(void(*)(void))function,0);
	//getcontext(newContext);
	return newContext;
}


