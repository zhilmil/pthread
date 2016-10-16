#include "my_pthread_t.h"

static void* func(void * value) {
	int a = (int) value;
	printf("Oh yeah!! from %d\n", a);
}
int main()
{
	printf("Main initialized\n");
	my_pthread_t t1;
	my_pthread_create(&t1,NULL, &func, NULL);
	/* don't let this parent thread terminate */
	while(1);
	return 0;
}

