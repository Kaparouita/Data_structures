#include <stdio.h>
#include <stdlib.h>
#include "pss.h"
#include "SubAndInfo.h"

/**
 * @brief check if empty
 *
 * @param info
 * @return 1 if empty
 */
int isInfoEmpty(Info *info)
{
    if (info == NULL)
        return 1;
    return 0;
}

/**
 * @brief Create an info given its attributes
 *
 * @param iTM
 * @param iId
 * @param gp
 * @param gp_size
 * @return Info*
 */
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
        if (*gp >= 0 && *gp < MG)
            newInfo->igp[*gp] = 1;
        gp++;
        gp_size--;
    }
    return newInfo;
}

/**
 * @brief given the head info and a new
 *        add the new to the list
 *
 * @param head_ref
 * @param new_info
 * @return int 1 if fails , 0 if succeed
 */
int I_Insert(Info **head_ref, Info *newInfo)
{
    Info *curr;
    /*EAN YPARXEI*/
    if (I_LookUp(*head_ref, newInfo->iId) != NULL)
        return 0;
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
        curr = curr->inext;

    /*an den einai to teleuteo kai to itm yparxei hdh*/
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
            return 1; /*didnt find the element*/

        else if (temp->iId == sub->iId)
        {
            /*delete*/
            temp->iprev->inext = temp->inext;
            if (temp->inext != NULL)
                temp->inext->iprev = temp->iprev;
            free(temp);
            return 0;
        }
        else
            temp = temp->inext;
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
            return curr; /*return if found*/
        curr = curr->inext;
    }
    return NULL;
}
/**
 * @brief print id enws info list
 *
 * @param info
 */
void printInfos(Info **info)
{
    Info *curr;
    curr = *info;
    printf("<");
    while (curr != NULL)
    {
        /*gia na mhn exei extra komma*/
        if (curr->inext)
            printf(" %d ,", curr->iId);
        else
            printf(" %d ", curr->iId);
        curr = curr->inext;
    }
    printf(">");

    return;
}

/*------------------------------SUBSCRIPTION-------------------------*/

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

/**
 * @brief find a subscription with id=id else return NULL
 *
 * @param head
 * @param id
 * @return Subscription*
 */
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

/**
 * @brief Given the head of a list delete the subscription with ID
 *
 * @param head
 * @param ID
 * @return return 1 if fails
 *         return 0 if succeed
 */
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
    /*find it*/
    while (temp != NULL)
    {
        /*delete*/
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

/**
 * @brief given the head of a list print ids of the subs
 *
 * @param sub
 */
void printSubscriptions(Subscription **sub)
{
    Subscription *curr;
    curr = *sub;
    printf("<");
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

/*
int main()
{
    int a[6] = {31, 5, 6, 45, 1, -1};
    int b[6] = {57, 35, 6, 43, 1, -1};
    int c[6] = {63, 35, 6, 43, 1, -1};

    // first = InfoConstractor(2, 4, a, 6);
    initialize();

    // printGroups();

    // printInfos(&first);

    Subscription *s1 = (Subscription *)malloc(sizeof(Subscription));

    s1->sId = 1;

    S_insert(&s1, 3);
    S_insert(&s1, 4);
    S_insert(&s1, 5);
    S_insert(&s1, 6);

    printSubscriptions(&s1);

    S_delete(&s1, 6);
    printSubscriptions(&s1);

    return 0;
}
*/