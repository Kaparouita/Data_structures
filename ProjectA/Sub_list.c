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

/*IF EMPTY*/
int isEmpty(SubInfo *sub)
{
    if (sub == NULL)
        return 0;
    return 1;
}

SubInfo *SubInfoConstractor(int ID, int TM, int *p_index)
{
    SubInfo *newSub = (SubInfo *)malloc(sizeof(SubInfo));
    int i = 0;
    newSub->sId = ID;
    newSub->stm = TM;
    /*INIT OLA ME 1*/
    for (i; i < MG; i++)
    {
        newSub->sgp[i] = 1;
    }
    while (*p_index != -1)
    {
        /*INIT ME NULL GIA ARXH*/
        newSub->sgp[*p_index++] = NULL;
    }
    return newSub;
}

/*returns 1 if succed*/
int Sub_Insert(SubInfo **head_ref, SubInfo *newSub)
{
    SubInfo *current;

    /*IF EMPTY*/
    if (isEmpty(*head_ref) == 0 || isEmpty(newSub) == 0)
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
    newSub->snext = current->snext;
    current->snext = newSub;

    return 1;
}

void printSubs(SubInfo **sub)
{
    SubInfo *curr;
    curr = *sub;
    while (curr != NULL)
    {
        printf(" %d ", curr->sId);
        curr = curr->snext;
    }
    return;
}

void print_sgp(SubInfo *Sub)
{
    for (int i = 0; i < MG; i++)
    {
        printf("MG : %d  =  %d\n", i, Sub->sgp[i]);
    }
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
    return 0;
}