#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdlib.h>

// RETURN STATUS of APIs
typedef enum {
	OK = 0,
	ERROR = -1
} STATUS;

// Node structure for a queue
typedef struct queueNode {
	void* thread;
	struct queueNode* prev;
	struct queueNode* next;
} queueNode_t;

// Queue Data Structure which contains head, tail
// of type queueNode
typedef struct queue {
	queueNode_t* head;
	queueNode_t* tail;
	unsigned int size;
} queue_t;


// Initializes queue
void initQueue(queue_t* q);

// Enqueue a node
// Returns OK or ERROR
STATUS enque(queue_t* q, queueNode_t* node);

// Dequeue a node
// Returns OK or ERROR
queueNode_t* deque(queue_t* q);

// Creates a queue node
queueNode_t* createNode();

#endif // _QUEUE_H
