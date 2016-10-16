all: scheduler pthread queue 
	gcc queue.o scheduler.o pthread.o demo.c -o pthread 
queue:
	gcc -c queue.c -o queue.o
scheduler: queue
	gcc -c scheduler.c -o scheduler.o
pthread: queue scheduler
	gcc -c my_pthread_t.c -o pthread.o 

	