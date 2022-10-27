#include <stdio.h>
#include "stack.c"
#include "queue.c"
#include <math.h>
// ginete arnhtiko num,k?
void ZigZag(Queue *Q, int k)
{
    enqueue(Q, -1);
    int tmp = k, num, n;
    while (k > 0)
    {
        if (front(Q) == -1)
        {
            n = tmp - k + 1;
            break;
        }
        enqueue(Q, dequeue(Q));
        k--;
    }
    num = front(Q);
    k = (int)fmin(num, tmp);
    while (front(Q) != -1)
    {
        enqueue(Q, dequeue(Q));
    }

    while (k > 0)
    {
    }
    printQ(Q);
}

int main()
{
    struct Queue *queue = createQueue(1000);

    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);

    printf("Front item is %d\n", front(queue));

    printf("Front item is %d\n", front(queue));

    ZigZag(queue, 5);

    return 0;
}