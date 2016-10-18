#include "my_pthread_t.h"
#include <ucontext.h>

#define STACKSIZE 64000

void* func(void * value) {
	while(1)
	printf("Thread 1\n");
}

void* func2(void * value) {
	while(1)
	printf("Thread 2\n");
}

void* func3(void * value) {
	while(1)
	printf("Thread 3\n");
}
int main()
{
	
	printf("Main initialized\n");
	my_pthread_t t1, t2, t3;
	my_pthread_create(&t1,NULL, &func, NULL);
	my_pthread_create(&t2,NULL, &func2, NULL);
	my_pthread_create(&t3,NULL, &func3, NULL);
	while(1);
}
