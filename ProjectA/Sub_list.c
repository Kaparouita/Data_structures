#include <stdio.h>
#include <stdlib.h>
#include "pss.h"
#include "SubAndInfo.h"

/**
 * @brief check if list is empty
 *
 * @param sub first sub
 * @return 0 if not empty
 *         1 otherwise
 */
int isSubEmpty(SubInfo *sub)
{
    if (sub == NULL)
        return 1;
    return 0;
}

/**
 * @brief creates a SubInfo
 *
 * @param ID
 * @param TM
 * @param p_index an array with the MG values sub wants to follow
 * @return SubInfo* if succed
 *         NULL if not
 */
SubInfo *SubInfoConstractor(int ID, int TM, int *p_index, int p_size)
{
    SubInfo *newSub = (SubInfo *)malloc(sizeof(SubInfo));
    if (p_index == NULL)
    {
        return NULL;
    }
    int i = 0;
    newSub->sId = ID;
    newSub->stm = TM;
    newSub->snext = NULL;
    /*INIT OLA ME 1*/
    for (i; i < MG; i++)
    {
        newSub->sgp[i] = 1;
    }
    while (*p_index != -1 && p_size > 0)
    {
        /*INIT ME NULL GIA ARXH*/
        newSub->sgp[*p_index++] = NULL;
        p_size--;
    }
    return newSub;
}

/**
 * @brief Instert a new sub to the list
 *
 * @param head_ref first sub
 * @param newSub   new sub
 * @return 0 if succeed
 *         else returns 1
 */
int Sub_Insert(SubInfo **head_ref, SubInfo *newSub)
{
    SubInfo *current;

    /*IF EMPTY*/
    if (isSubEmpty(*head_ref) || isSubEmpty(newSub))
        return 1;
    current = *head_ref;
    /*CHECK IF ITS THE FIRST ELEMENT*/
    if (newSub->stm < first_sub->stm)
    {
        newSub->snext = *head_ref;
        *head_ref = newSub;
        return 0;
    }
    while (current->snext != NULL && current->snext->stm < newSub->stm)
    {
        current = current->snext;
    }
    /*ean yparxei*/
    if (current->snext != NULL && current->snext->sId == newSub->sId)
        return 1;
    newSub->snext = current->snext;
    current->snext = newSub;

    return 0;
}

/**
 * @brief deletes the sub from the list
 *
 * @param headref first sub
 * @param sub     sub to delete
 * @return 0 if succeed
 *         1 if fails
 */
int SL_delete(SubInfo **head, SubInfo *sub)
{
    SubInfo *temp;
    SubInfo *prev;
    temp = *head;
    prev = *head;

    if (isSubEmpty(*head) || isSubEmpty(sub))
        return 1; /*fails if empty*/

    /*an einai to prwto stoixeio*/
    if (temp->sId == sub->sId)
    {
        *head = (*head)->snext;
        free(temp);
        return 0;
    }
    temp = temp->snext;

    while (temp != NULL)
    {
        if (temp->stm > sub->stm)
        {
            return 1; /*didnt find the element*/
        }

        if (temp->sId == sub->sId)
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
/**
 * @brief Given the ID return the SubInfo owner of the ID
 *
 * @param head
 * @param ID
 * @return SubInfo*
 *         NULL if its not in the list
 */
SubInfo *SL_LookUp(SubInfo *head, int ID)
{
    SubInfo *curr;
    curr = head;
    if (isSubEmpty(head))
    {
        return NULL;
    }
    while (curr != NULL)
    {
        if (curr->sId == ID)
            return curr;
        curr = curr->snext;
    }
    return NULL;
}
/**
 * @brief prints all subs
 *
 * @param sub first sub
 */
void printSubs(SubInfo **sub)
{
    SubInfo *curr;
    curr = *sub;
    while (curr != NULL)
    {
        printf(" %d ,", curr->sId);
        curr = curr->snext;
    }
    printf("\n\n");

    return;
}

void print_sgp(SubInfo *Sub)
{
    for (int i = 0; i < MG; i++)
    {
        printf("MG : %d  =  %p\n", i, Sub->sgp[i]);
    }
    printf("\n\n");
}
/*
int main()
{
    int a[6] = {31, 5, 6, 45, 1, -1};
    int b[6] = {57, 35, 6, 43, 1, -1};
    int c[6] = {63, 35, 6, 43, 1, -1};

    SubInfo *sub = SubInfoConstractor(4, 2000, a, 6);

    Subscriber_Registration(30, 10, b, 3);
    Subscriber_Registration(32, 1, c, 6);
    Subscriber_Registration(31, 2, a, 6);
    Subscriber_Registration(31, 6, b, 6);

    printSubs(&first_sub);

    // print_sgp(sub4);
    //  printSubs(&first_sub);

    return 0;
}
*/
