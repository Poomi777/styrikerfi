#include "scheduler.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct _QueueItem {
    /*
     * The data of this item.
     */
    int data;
    /*
     * The next item in the queue.
     * NULL if there is no next item.
     */
    struct _QueueItem *next;
} QueueItem;

typedef struct _Queue {
    /*
     * The first item of the queue.
     * NULL if the queue is empty.
     */
    QueueItem *head;
    /*
     * The last item of the queue.
     * undefined if the queue is empty.
     */
    QueueItem *tail;
} Queue;

typedef enum _ThreadState {
    STATE_UNUSED = 0, // This entry in the _threads array is unused.

    STATE_READY,      // The thread is ready and should be on a ready queue for
                      //   selection by the scheduler
    STATE_RUNNING,    // The thread is running and should not be on a ready queue
    STATE_WAITING     // The thread is blocked and should not be on a ready queue
} ThreadState;

typedef struct _Thread {
    int threadId;
    ThreadState state;
    /*
     * Range: 0 ... HIGHEST_PRIORITY (including)
     * HIGHEST_PRIORITY is highest priority
     */
    int priority;
} Thread;

Thread _threads[MAX_THREADS] = {{0}};

/* TODO: Add global variables if needed. */
Queue _readyQueue = {NULL, NULL};

/*
 * Adds a new, waiting thread.
 */
int startThread(int threadId, int priority)
{
    if (((threadId < 0) || (threadId >= MAX_THREADS) ||
        (_threads[threadId].state != STATE_UNUSED)) ||
        (priority < 0) || (priority > HIGHEST_PRIORITY)) {

        return -1;
    }

    _threads[threadId].threadId = threadId;
    _threads[threadId].state    = STATE_WAITING;
    _threads[threadId].priority = priority;
    return 0;
}

/*
 * Append to the tail of the queue.
 * Does nothing on error.
 */
void _enqueue(Queue *queue, int data)
{
    // TODO: Implement

    QueueItem *newItem = (QueueItem*) malloc(sizeof(QueueItem));
    newItem->data = data;
    newItem->next = NULL;

    if (queue->tail == NULL) {

        queue->head = newItem;
        queue->tail = newItem;
    }

    else {
        queue->tail->next = newItem;
        queue->tail = newItem;
    }
}

/*
 * Remove and get the head of the queue.
 * Return -1 if the queue is empty.
 */
int _dequeue(Queue *queue)
{

    // TODO: Implement
    if (queue->head == NULL){
        return -1;
    }

    int data = queue->head->data;

    QueueItem *temp = queue->head;
    queue->head = queue->head->next;

    if (queue->head == NULL){
        queue->tail = NULL;
    }

    free(temp);
    return data;
}

void initScheduler()
{
    // TODO: Implement if you need to initialize any global variables you added
}

/*
 * Called whenever a waiting thread gets ready to run.
 */
void onThreadReady(int threadId)
{
    // TODO: Implement
    _threads[threadId].state = STATE_READY;
    _enqueue(&_readyQueue, threadId);
}

/*
 * Called whenever a running thread needs to wait.
 */
void onThreadPreempted(int threadId)
{
    // TODO: Implement
    _threads[threadId].state = STATE_READY;
    _enqueue(&_readyQueue, threadId);
}

void onThreadWaiting(int threadId)
{
    // TODO: Implement
    _threads[threadId].state = STATE_WAITING;
}


/*
 * Gets the id of the next thread to run and sets its state to running.
 */
int scheduleNextThread()
{
    // TODO: Implement
    
    int theNextThread = _dequeue(&_readyQueue);
    if (theNextThread >= 0){
        _threads[theNextThread].state = STATE_RUNNING;
    }
    
    return theNextThread;

   
}


#if 0
int main() {
	// Initially empty queue (head and tail is NULL)
	Queue q = {NULL,NULL};

	_enqueue( &q, 42 );
	_enqueue( &q, 99 );
	int x = _dequeue( &q );
	printf("Expect: 42, and I got: %d\n", x);

	x = _dequeue( &q );
	printf("Expect: 99, and I got: %d\n", x);
}
#endif
