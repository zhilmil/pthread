#ifndef TIMER
#define TIMER

//Calls the handler function periodically. Interval specifies the interval in milliseconds.
void setTimer(void (*handler)(), int interval);

#endif