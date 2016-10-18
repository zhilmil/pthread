#include "my_pthread_t.h"
#include <ucontext.h>

#define STACKSIZE 64000

void* func(void * value) {
	printf("Hello from the other side");
}
int main()
{
	
	printf("Main initialized\n");
	my_pthread_t t1;
	my_pthread_create(&t1,NULL, &func, NULL);
	//while(1);
}