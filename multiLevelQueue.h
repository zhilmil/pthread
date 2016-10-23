#ifndef MULTILEVELQUEUE
#define MULTILEVELQUEUE

#include "queue.h"

void mEnque(queueNode_t* input);
queueNode_t* mDeque();
void initMQ();
void maintainenceCycle();
#endif