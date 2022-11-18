#include <stdio.h>
#include <stdlib.h>
#include "pss.h"

SubInfo *first_sub;
Group GROUPS[MG];

/*
struct SubInfo
{
    int sId;
    int stm;
    struct Info *sgp[MG];
    struct SubInfo *snext;
};*/

void print_sgp(SubInfo *Sub);
int is_MG_limits(int id);
/**
 * @brief check if list is empty
 *
 * @param sub first sub
 * @return 0 if not empty
 *         1 otherwise
 */
int isEmpty(SubInfo *sub)
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
SubInfo *SubInfoConstractor(int ID, int TM, int *p_index)
{
    int i = 0;
    SubInfo *newSub = (SubInfo *)malloc(sizeof(SubInfo));
    if (p_index == NULL)
    {
        return NULL;
    }
    newSub->sId = ID;
    newSub->stm = TM;
<<<<<<< HEAD
    newSub->snext = NULL;
    SubSgpINIT(newSub, p_index, p_size);
    return newSub;
}
/**
 * @brief init the sgp of a sub
 *
 * @param sub
 * @param p_sgp
 * @param p_size
 */
void SubSgpINIT(SubInfo *sub, int *p_sgp, int p_size)
{
    int i = 0;
=======
>>>>>>> c375b1d0cb72dfdee1e6d35d734c92ecc9bb7735
    /*INIT OLA ME 1*/
    for (i = 0; i < MG; i++)
    {
        sub->sgp[i] = (Info *)1;
    }
<<<<<<< HEAD
    while (*p_sgp != -1 && p_size > 0)
    {
        /*if out of limits skip*/
        if (!is_MG_limits(*p_sgp))
            sub->sgp[*p_sgp] = G[*p_sgp]->gfirst;

        *p_sgp++;
        p_size--;
=======
    while (*p_index != -1)
    {
        /*INIT ME NULL GIA ARXH*/
        newSub->sgp[*p_index++] = NULL;
>>>>>>> c375b1d0cb72dfdee1e6d35d734c92ecc9bb7735
    }
}

/**
 * @brief check if the id is between 0-MG
 *
 * @param id
 * @return return 0 if true ,else 1
 */
int is_MG_limits(int id)
{
    if (id < 0 || id >= MG)
        return 1;
    return 0;
}
/**
 * @brief Instert a new sub to the list
 *
 * @param head_ref first sub
 * @param newSub   new sub
 * @return 1 if succeed
 *         else returns 0
 */
int Sub_Insert(SubInfo **head_ref, SubInfo *newSub)
{
    SubInfo *current;

    /*IF EMPTY*/
    if (isEmpty(*head_ref) || isEmpty(newSub))
        return 0;
    current = *head_ref;
    /*CHECK IF ITS THE FIRST ELEMENT*/
    if (newSub->stm < first_sub->stm)
    {
        newSub->snext = *head_ref;
        *head_ref = newSub;
        return 1;
    }
    while (current->snext != NULL && current->snext->stm < newSub->stm)
    {
        current = current->snext;
    }
<<<<<<< HEAD
    /*ean yparxei*/
    if (current->snext != NULL && current->snext->sId == newSub->sId)
        return 0;
=======
>>>>>>> c375b1d0cb72dfdee1e6d35d734c92ecc9bb7735
    newSub->snext = current->snext;
    current->snext = newSub;

    return 1;
}

/**
 * @brief deletes the sub from the list
 *
 * @param headref first sub
 * @param sub     sub to delete
 * @return 1 if succeed
 *         0 if fails
 */
int SL_delete(SubInfo **head, SubInfo *sub)
{
    SubInfo *temp;
    SubInfo *prev;
    temp = *head;
    prev = *head;

    if (isEmpty(*head) || isEmpty(sub))
        return 0; /*fails if empty*/

    /*an einai to prwto stoixeio*/
    if (temp->sId == sub->sId)
    {
        *head = (*head)->snext;
        free(temp);
        return 1;
    }
    temp = temp->snext;

    while (temp != NULL)
    {
        if (temp->stm > sub->stm)
<<<<<<< HEAD
            return 1; /*didnt find the element*/
=======
        {
            return 0; /*didnt find the element*/
        }
>>>>>>> c375b1d0cb72dfdee1e6d35d734c92ecc9bb7735

        else if (temp->sId == sub->sId)
        {
            prev->snext = temp->snext;
            free(temp);
            return 1;
        }
        else
        {
            prev = temp;
            temp = temp->snext;
        }
    }
    return 0;
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
    if (isEmpty(head))
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
void printSubsInfo(SubInfo **sub)
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

/**
 * @brief Print Subscriberlist ids
 *
 * @param sub
 */
void printSubs(SubInfo **sub)
{
    SubInfo *curr;
    curr = *sub;
    printf("   SUBSCRIBERELIST = <");
    while (curr != NULL)
    {
        if (curr->snext == NULL)
            printf(" %d ", curr->sId);
        else
            printf(" %d ,", curr->sId);
        curr = curr->snext;
    }
    printf(">\n");

    return;
}

/**
 * @brief Print all sub list given head (first_sub)
 *
 * @param sub
 */
void printAllSubs(SubInfo **sub)
{
    SubInfo *curr;
    curr = *sub;
    while (curr != NULL)
    {
        printf("   SUBSCRIBERERID = <%d> ,", curr->sId);
        print_sgp(curr);
        printf("\n");
        curr = curr->snext;
    }
    printf(">\n");

    return;
}

/**
 * @brief print Grouplist of a sub
 *
 * @param Sub
 */
void print_sgp(SubInfo *Sub)
{
    int i;
    printf("GROUPLIST = <");
    for (i = 0; i < MG; i++)
    {
        if (Sub->sgp[i] != (Info *)1)
        {
            printf(" %d ,", i);
        }
    }
    printf(">");
}

int Subscriber_Registration(int sTM, int sId, int *gids_arr, int size_of_gids_arr)
{
    SubInfo *new_sub = SubInfoConstractor(sId, sTM, gids_arr);
    if (first_sub == NULL)
        return 0;
    Sub_Insert(&first_sub, new_sub);
    return 1;
}

int main()
{
    int a[6] = {31, 5, 6, 45, 1, -1};
    int b[6] = {57, 35, 6, 43, 1, -1};
    int c[6] = {63, 35, 6, 43, 1, -1};

    SubInfo *sub = SubInfoConstractor(4, 2000, a);
    first_sub = sub;

    SubInfo *sub3 = SubInfoConstractor(52, 1999, c);
    SubInfo *sub1 = SubInfoConstractor(5, 4000, b);
    SubInfo *sub2 = SubInfoConstractor(6, 2365, c);

    // print_sgp(sub);
    Sub_Insert(&first_sub, sub1);
    Sub_Insert(&first_sub, sub2);
    Sub_Insert(&first_sub, sub3);

    // print_sgp(sub);
    printSubs(&first_sub);
    SubInfo *sub4;
    sub4 = SL_LookUp(first_sub, 6);
    printf("sub4 : %d \n", sub4->sId);
    // print_sgp(sub4);
    //  printSubs(&first_sub);

    return 0;
}
