#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>


#include "common.h"
#include "timer.h"

void setTimer(void (*handler)(), int interval)
{
	printf("setitimer\n");
	int intervalMicroSeconds = interval * 1000;
	struct sigaction sa;
	struct itimerval timer;

 	/* Install timer_handler as the signal handler for SIGVTALRM. */
 	memset (&sa, 0, sizeof (sa));
 	sa.sa_handler = handler;
 	sigaction (SIGVTALRM, &sa, NULL);


	 /* Configure the timer to expire after interval x 1000 msec... */
	 timer.it_value.tv_sec = 0;
	 timer.it_value.tv_usec = intervalMicroSeconds;
	 /* ... and also get the timer to periodically refire. */
	 timer.it_interval.tv_sec = 0;
	 timer.it_interval.tv_usec = intervalMicroSeconds;
	 /* Start a virtual timer. It counts down whenever this process is
	   executing. */
	 setitimer (ITIMER_VIRTUAL, &timer, NULL);

}