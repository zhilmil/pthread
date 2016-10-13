#include "queue.h"

// Initialize
void initQueue(queue_t* q)
{
	q->size = 0;
	q->head = NULL;
	q->tail = NULL;
}


// Enqueus at tail
STATUS enque(queue_t* q, queueNode_t* node)
{
	if(!q)
		return ERROR;

	// Empty queue
	if(q->head == NULL && q->tail == NULL)
	{
		q->head = node;
		q->tail = node;
		q->size = 1;
		return OK;
	}
	else
	{
		// Update tail
		q->tail->next = node;
		node->prev = q->tail;
		
		q->tail = node;

		// Increment the size
		(q->size)++;
	}

	return OK;
}

queueNode_t* deque(queue_t* q)
{
	if(!q || !(q->head) || q->size == 0)
		return NULL;

	// Single node
	if(q->head == q->tail)
	{
		queueNode_t* node = q->head;
		q->head = NULL;
		q->tail = NULL;
		q->size = 0;
		return node;
	}
	else
	{
		queueNode_t* node = NULL;
		node = q->head;
		// Advance head
		q->head = q->head->next;
		node->next = NULL;
		q->head->prev = NULL;

		// Decrement size
		(q->size)--;

		return node;
	}
}

queueNode_t* createNode()
{
	queueNode_t* node = NULL;
	node = (queueNode_t*)malloc(sizeof(queueNode_t));

	if(!node)
		return NULL;
	node->prev = NULL;
	node->next = NULL;
	node->thread = NULL;

	// TODO: Test code
	//node->thread = (int*)malloc(sizeof(int));

	/*
	if(!(node->thread))
	{
		free(node);
		return NULL;
	}
	*/

	//*(int*)(node->thread) = val;
	return node;
}

// TODO: Test code
/*
void printListFromHead(queue_t* q)
{
	queueNode_t* head = q->head;
	while(head)
	{
		printf("%d=>",*(int*)(head->thread));
		head = head->next;
	}
	printf("\n");
}
*/

// TODO: Test code
/*
void printListFromTail(queue_t* q)
{
	queueNode_t* tail = q->tail;
	while(tail)
	{
		printf("%d=>",*(int*)(tail->thread));
		tail = tail->prev;
	}
	printf("\n");
}
*/

/*
int main()
{
	queue_t q1;
	initQueue(&q1);
	printf("Q size: %d\n", q1.size);

	queueNode_t* n1 = createNode(10);
	printf("Enque: %d\n", enque(&q1, n1));
	printf("Q size: %d\n", q1.size);

	queueNode_t* n2 = createNode(20);
	printf("Enque: %d\n", enque(&q1, n2));
	printf("Q size: %d\n", q1.size);

	printListFromHead(&q1);
	printListFromTail(&q1);

	queueNode_t* tmp = deque(&q1);
	printf("Deque: %d\n", *(int*)tmp->thread);
	printf("Q size: %d\n", q1.size);

	printListFromHead(&q1);
	printListFromTail(&q1);

	tmp = deque(&q1);
	printf("Deque: %d\n", *(int*)tmp->thread);
	printf("Q size: %d\n", q1.size);

	printListFromHead(&q1);
	printListFromTail(&q1);
	return 0;

}
*/
