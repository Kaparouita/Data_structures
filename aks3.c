#include <stdio.h>
#include "linked_list.c"

Node *RemovePairs(Node *L, int k)
{
    Node *curr = L, *prevL = L, *prevC = L, *delete = NULL, *head = L;
    while (curr->next != NULL)
    {
        if ((curr->data + L->data) == k)
        {
            delete = curr;
            curr = curr->next;
            // an einai dipla
            if (curr == L)
            {
                if (curr->next == NULL)
                {
                    prevC->next = NULL;
                    break;
                }
                curr = curr->next;
            }
            // an einai to prwto stoixeio
            if (delete == prevC)
            {
                head = curr; // move head
                delete->next = NULL;
                free(delete);
            }
            else /*Break the first link*/
                prevC->next = curr;
            // An einai to teleutaio
            if (L->next == NULL)
            {
                delete = L;
                prevL->next = NULL;
                free(delete);
            }
            else /*Break the second link*/
                prevL->next = L->next;

            L = curr;
            prevL = L;
            L = L->next;
            continue;
        }
        /*ean eftasa sto telos*/
        if (L->next == NULL)
        {
            prevC = curr;
            curr = curr->next;
            L = curr;
        }
        prevL = L;
        L = L->next;
    }
    return head;
}

int main()
{

    Node *L = NULL, *c;
    push(&L, 5);

    push(&L, 2);

    push(&L, -1);
    push(&L, 6);

    push(&L, 8);

    push(&L, 9);

    push(&L, -10);
    push(&L, 15);
    push(&L, 3);

    c = RemovePairs(L, 8);

    // printList(L);
    // printf("\n%d", c->data);
    printList(c);

    // printf("Iam removing %d and %d\n", curr->data, L->data);

    // printf("Curr : %d , PrevC : %d , L : %d , PrevL %d\n", curr->data, prevC->data, L->data, prevL->data);
}