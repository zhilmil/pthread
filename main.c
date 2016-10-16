#include "my_pthread_t.h"

static void* func(void * value) {
	//do nothing
}
int main()
{
	printf("Main initialized");
	my_pthread_t t1;
	my_pthread_create(&t1,NULL, &func, NULL);
	return 0;
}

