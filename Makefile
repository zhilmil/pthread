all: pthread queue
	gcc queue.o pthread.o demo.c -o pthread
queue:
	gcc -c queue.c -o queue.o
pthread: queue
	gcc -c my_pthread_t.c -o pthread.o

	