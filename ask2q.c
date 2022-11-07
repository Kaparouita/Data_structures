#include <stdio.h>
#include "stack.c"
#include "queue.c"
#include <math.h>
// ginete arnhtiko num,k?
void ZigZag(Queue *Q1, int k)
{
    Queue *Q2 = createQueue(100);
    if (isEmpty(Q1))
    {
        return; /*q is empty*/
    }
    int num, n = get_Q_size(Q1, Q2);
    /*get the item value*/
    num = get_Q_item(Q2, Q1, k);

    if (n < k)
    {
        num = n - num;
    }
    printQ(Q1);
}

int get_Q_size(Queue *Q1, Queue *Q2)
{
    int i = 1;
    while (!isEmpty(Q1))
    {
        enqueue(Q2, dequeue(Q1));
        i++;
    }
    return i;
}
int get_Q_item(Queue *Q1, Queue *Q2, int index)
{
    int tmp;
    while (index > 0)
    {
        if (isEmpty(Q1))
        {
            break;
        }
        tmp = dequeue(Q1);
        enqueue(Q2, tmp); /*remove the item from first list and put it on the tempory list*/
        index--;
    }
    while (!isEmpty(Q1))
        enqueue(Q2, dequeue(Q1));
    return tmp;
}

int main()
{
    struct Queue *queue = createQueue(1000);

    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);

    printf("Front item is %d\n", front(queue));

    ZigZag(queue, 5);

    return 0;
}