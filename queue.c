// C program for array implementation of queue
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue Queue;
// A structure to represent a queue
struct Queue
{
    int front;
    int size;
    unsigned capacity;
    char *array;
};

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
Queue *createQueue(unsigned capacity)
{
    Queue *queue = (Queue *)malloc(
        sizeof(Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->size = 0;

    // This is important, see the enqueue
    queue->array = (int *)malloc(
        queue->capacity * sizeof(int));
    return queue;
}

void printQ(Queue *q)
{

    for (int i = 0; i < q->size; i++)
    {
        printf(" %d ,", q->array[i]);
    }
}

// Queue is full when size becomes
// equal to the capacity
int isFull(Queue *queue)
{
    return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty(Queue *queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue.
void enqueue(Queue *Q, int item)
{
    if (isFull(Q))
        return;
    else
    {
        Q->size = Q->size + 1;
        (Q->array)[(Q->front + Q->size - 1) % Q->capacity] = item;
        printf("%d enqueued to queue\n", item);
    }
}
// Function to remove an item from queue.
// It changes front and size
int dequeue(Queue *queue)
{
    if (isEmpty(queue))
        return '0';
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to get front of queue
int front(Queue *queue)
{
    if (isEmpty(queue))
        return '0';
    return queue->array[queue->front];
}
