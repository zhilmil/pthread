all: scheduler pthread queue timer
	gcc queue.o scheduler.o pthread.o timer.o demo.c -o demo
timer:
	gcc -c timer.c -o timer.o
queue:
	gcc -c queue.c -o queue.o
scheduler: queue timer
	gcc -c scheduler.c -o scheduler.o
pthread: queue scheduler timer
	gcc -c my_pthread_t.c -o pthread.o 
clean:
	rm -rf *.o