#include "my_pthread_t.h"
#include <ucontext.h>

#define STACKSIZE 64000

void* func(void * value) 
{
	while(1)
		printf("Thread 1\n");
}

void* func2(void * value) 
{
		printf("Thread 2\n");
}

void* func3(void * value) 
{	
	printf("Before yield");
	my_pthread_yield();
	printf("After yield");
	while(1)
		printf("Thread 3\n");
}
my_pthread_mutex_t mut;
void* func4(void * value)
{

	printf("Before entering critical section thread 4\n");
	int i = 0;
	my_pthread_mutex_lock(&mut);
	while(i<50)
	{
		i++;
		printf("Critical zone! Thread 4\n");
	}
	my_pthread_mutex_unlock(&mut);

}

void* func5(void * value)
{

	
	printf("Before entering critical section thread 5\n");
	int i = 0;
	my_pthread_mutex_lock(&mut);
	while(i<50)
	{	
		i++;
		printf("Critical zone! Thread 5\n");
	}
	my_pthread_mutex_unlock(&mut);

}

void* func6(void *value)
{
	
	int i=0;
	while(i<50)
	{
		i++;
		printf("In function 6");
	}

}

void* func7(void *value)
{
	int i=0;
	while(i<50)
	{
		i++;
		printf("in function 7");
	}	
}

int main()
{	
	my_pthread_mutex_init(&mut, NULL);
	printf("Main initialized\n");
	my_pthread_t t1, t2, t3, t4, t5,t6,t7;
	/*my_pthread_create(&t1,NULL, &func, NULL);
	my_pthread_create(&t2,NULL, &func2, NULL);
	my_pthread_create(&t3,NULL, &func3, NULL);*/
	
//	my_pthread_create(&t5, NULL, &func5, NULL);
//	my_pthread_create(&t4, NULL, &func4, NULL);
	my_pthread_create(&t6,NULL,&func6,NULL);
	my_pthread_create(&t7,NULL,&func7,NULL);
	printf("status %d",t7.st);
	printf("status %d",t6.st);	
	my_pthread_join(t7, NULL);
	my_pthread_join(t6,NULL);
	while(1)
	{
		//printf("Main thread\n");
	}
}
