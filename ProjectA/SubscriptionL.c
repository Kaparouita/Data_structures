#include <stdio.h>
#include <stdlib.h>
#include "pss.h"
#include "SubAndInfo.h"

/**
 * @brief checks if its empty
 *
 * @param sub
 * @return return 0 if not null
 */
int S_isEmpty(Subscription *sub)
{
    if (sub == NULL)
        return 1;
    return 0;
}

/**
 * @brief insert a new subscription with the new_ID
 *
 * @param head
 * @param new_ID
 * @return return 0 if succeed
 *         1 if fails
 */
int S_insert(Subscription **head, int new_ID)
{

    if (S_isEmpty(*head))
        return 1;

    Subscription *new_sub = (Subscription *)malloc(sizeof(Subscription));
    new_sub->sId = new_ID;
    new_sub->snext = (*head);
    (*head) = new_sub;
    return 0;
}

Subscription *search(Subscription *head, int id)
{
    Subscription *curr = head;
    while (curr != NULL)
    {
        if (curr->sId == id)
            return curr;
        curr = curr->snext;
    }
    return NULL;
}

int S_delete(Subscription **head, int ID)
{
    Subscription *temp;
    Subscription *prev;
    temp = *head;
    prev = *head;
    if (S_isEmpty(*head))
        return 1; /*fails if empty*/

    /*an einai to prwto stoixeio*/
    if (temp->sId == ID)
    {
        *head = (*head)->snext;
        free(temp);
        return 0;
    }
    temp = temp->snext;
    while (temp != NULL)
    {
        if (temp->sId == ID)
        {
            prev->snext = temp->snext;
            free(temp);
            return 0;
        }
        else
        {
            prev = temp;
            temp = temp->snext;
        }
    }
    return 1;
}

void printSubscriptions(Subscription **sub)
{
    Subscription *curr;
    curr = *sub;
    while (curr != NULL)
    {
        printf(" %d ,", curr->sId);
        curr = curr->snext;
    }
    printf("\n\n");

    return;
}

/*
int main()
{
    Subscription *s1 = (Subscription *)malloc(sizeof(Subscription));

    s1->sId = 1;

    S_insert(&s1, 3);
    S_insert(&s1, 4);
    S_insert(&s1, 5);
    S_insert(&s1, 6);

    printSubscriptions(&s1);

    S_delete(&s1, 6);
    printSubscriptions(&s1);
}
*/