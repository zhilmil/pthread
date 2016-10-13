#include "my_pthread_t.h"


int main()
{
	pthread_t t1;
	my_pthread_create(&t1, NULL, NULL, NULL);
	return 0;
}

