#include <stdio.h>
#include <stdlib.h>
#include "pss.h"
#include "SubAndInfo.h"

/*
struct Info
{
    int iId;
    int itm;
    int igp[MG];
    struct Info *iprev;
    struct Info *inext;
};*/

/**
 * @brief check if empty
 *
 * @param info
 * @return 0 if empty
 */
int isInfoEmpty(Info *info)
{
    if (info == NULL)
        return 1;
    return 0;
}

Info *InfoConstractor(int iTM, int iId, int *gp, int gp_size)
{
    Info *newInfo = (Info *)malloc(sizeof(Info));
    if (gp == NULL)
    {
        return NULL;
    }
    int i = 0;
    newInfo->iId = iId;
    newInfo->itm = iTM;
    newInfo->inext = NULL;
    newInfo->iprev = NULL;
    /*INIT OLA ME 0*/
    for (i; i < MG; i++)
    {
        newInfo->igp[i] = 0;
    }
    while (*gp != -1 && gp_size > 0)
    {
        /*INIT ME 1 AN SYSXETIZETE ME THN OMADA i*/
        newInfo->igp[*gp++] = 1;
        gp_size--;
    }
    return newInfo;
}

/**
 * @brief given the last info and a new
 *        add the new to the list
 *
 * @param last_info
 * @param new_info
 * @return int 1 if fails , 0 if succeed
 */
int I_Insert(Info **head_ref, Info *newInfo)
{
    Info *curr;
    /*IF EMPTY*/
    if (isInfoEmpty(*head_ref) || isInfoEmpty(newInfo))
        return 1;
    curr = *head_ref;
    /*CHECK IF ITS THE FIRST ELEMENT*/
    if (newInfo->itm < curr->itm)
    {
        newInfo->inext = curr;
        curr->iprev = newInfo;
        newInfo->iprev = NULL;
        *head_ref = newInfo;
        return 0;
    }
    while (curr->inext != NULL && curr->inext->itm < newInfo->itm)
    {
        curr = curr->inext;
    }
    /*an den einai to teleuteo kai to itm yparxei hdh*/
    if (curr->inext != NULL && curr->inext->itm == newInfo->itm)
        return 1;
    newInfo->inext = curr->inext;
    newInfo->iprev = curr;
    curr->inext = newInfo;
    if (newInfo->inext != NULL)
        newInfo->inext->iprev = newInfo;

    return 0;
}

/**
 * @brief delete an info from the list
 *
 * @param head
 * @param sub
 * @return returns 0 if succeed , 1 if fails
 */
int I_delete(Info **head, Info *sub)
{
    Info *temp;
    temp = *head;

    if (isInfoEmpty(*head) || isInfoEmpty(sub))
        return 1; /*fails if empty*/
    /*an einai to prwto stoixeio*/
    if (temp->iId == sub->iId)
    {
        temp->inext->iprev = NULL;
        *head = (*head)->inext;
        free(temp);
        return 0;
    }
    temp = temp->inext;
    while (temp != NULL)
    {
        if (temp->itm > sub->itm)
        {
            return 1; /*didnt find the element*/
        }

        if (temp->iId == sub->iId)
        {
            temp->iprev->inext = temp->inext;
            if (temp->inext != NULL)
                temp->inext->iprev = temp->iprev;
            free(temp);
            return 0;
        }
        else
        {
            temp = temp->inext;
        }
    }
    return 1;
}

/**
 * @brief look for a specific ID info
 *
 * @param head
 * @param ID
 * @return Info*
 */
Info *I_LookUp(Info *head, int ID)
{
    Info *curr;
    curr = head;
    if (isInfoEmpty(head))
    {
        return NULL;
    }
    while (curr != NULL)
    {
        if (curr->iId == ID)
            return curr;
        curr = curr->inext;
    }
    return NULL;
}
void printInfos(Info **sub)
{
    Info *curr;
    curr = *sub;
    while (curr != NULL)
    {
        printf(" %d ,", curr->iId);
        curr = curr->inext;
    }
    printf("\n\n");

    return;
}
void pprintInfos(Info **sub)
{
    Info *curr;
    curr = *sub;
    while (curr != NULL)
    {
        printf(" %d ,", curr->iId);
        curr = curr->iprev;
    }
    printf("\n\n");

    return;
}

void printGroups()
{

    for (int i = 0; i < MG; i++)
    {
        printf("ID : %d , INFOS : ", G[i]->gId);
        printInfos(&G[i]->gfirst);
    }
    printf("\n");

    return;
}

/*
int main()
{
    int a[6] = {31, 5, 6, 45, 1, -1};
    int b[6] = {57, 35, 6, 43, 1, -1};
    int c[6] = {63, 35, 6, 43, 1, -1};
    Info *first;

    Insert_Info(2005, 4, a, 6);
    Insert_Info(2001, 6, b, 6);
    Insert_Info(2003, 7, c, 6);
    Insert_Info(2000, 1, a, 6);
    Insert_Info(1999, 10, a, 6);

    initialize();

    // printGroups();

    printInfos(&first_info);

    return 0;
}*/
