#include <stdio.h>
#include <unistd.h>
#include <ucontext.h>

#include "context.h"

ucontext_t* makeContext(void *(*function)(void*))
{
	ucontext_t * newContext = (ucontext_t*)malloc(sizeof(ucontext_t));
	makecontext(newContext,(void(*)(void))&function,0);	
}