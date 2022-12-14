/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr)
 * @Version 20-10-2020
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Implementation of the "pss.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */
#include <stdio.h>
#include <stdlib.h>

#include "pss.h"

SubInfo *first_sub; /*first sub*/
Group *G[MG];       /* Groups*/

void updateSubPointer(Subscription *Subscription, Info **info, int G_ID);

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(int m, int p)
{
    int i;
    /*init Groups*/
    for (i = 0; i < MG; i++)
    {
        G[i] = (Group *)malloc(sizeof(Group));
        G[i]->gId = i;
        G[i]->gsub = NULL;
        G[i]->gr = NULL;
    }
    /*init subs*/
    first_sub = NULL;
    return 1;
}

/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(void)
{
    if (freeGroups() || freeSubs())
        return 1;
    printf("FREE ALL SUCCESS");
    return 0;
}

/**
 * @brief Insert info
 *
 * @param iTM Timestamp of arrival
 *
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Insert_Info(int iTM, int iId, int *gids_arr, int size_of_gids_arr)
{

    int i = size_of_gids_arr;
    while (*gids_arr != -1 && i != 0)
    {
        /*an einai ektos oriwn skipareto*/
        if (*gids_arr < 0 || *gids_arr >= MG)
        {
            gids_arr++;
            i--;
            continue;
        }
        /*create the info*/
        Info *new_info = InfoConstractor(iTM, iId, gids_arr, size_of_gids_arr);
        /*if its the first info of the group*/
        if (G[*gids_arr]->gr == NULL)
        {
            G[*gids_arr]->gr = new_info;
            /*UPDATE IT*/
            updateSubPointer(G[*gids_arr]->gsub, &(G[*gids_arr]->gr), *gids_arr);
        }
        /*else insert the info*/
        else
            BST_insert(G[*gids_arr]->gr, new_info);
        /*Print the Group info*/
        printGroupInfo(G[*gids_arr]);
        gids_arr++;
        i--;
    }
    return 0;
}

/**
 * @brief if its the first insert change NULL pointer to first of group
 *
 * @param Subscription
 * @param info
 * @param G_ID
 */
void updateSubPointer(Subscription *Subscription, Info **info, int G_ID)
{
    while (Subscription != NULL)
    {
        /*find the sub via ID*/
        SubInfo *curr_sub;
        curr_sub = SL_LookUp(first_sub, Subscription->sId);
        curr_sub->sgp[G_ID] = *info;
        Subscription = Subscription->snext;
    }
}
/**
 * @brief Subsriber Registration
 *
 * @param sTM Timestamp of arrival
 * @param sId Identifier of subscriber
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Subscriber_Registration(int sTM, int sId, int *gids_arr, int size_of_gids_arr)
{

    int size = size_of_gids_arr;

    /*ADD SUB TO SUBINFO*/
    SubInfo *new_sub = SubInfoConstractor(sId, sTM, gids_arr, size);
    /*an einai to prwto*/
    if (first_sub == NULL)
    {
        first_sub = new_sub;
    }
    else if (Sub_Insert(&first_sub, new_sub))
        return 1;
    printSubs(&first_sub); /*print subs*/

    /*UPDATE SUBSCRIPTION LIST*/
    int i = size_of_gids_arr;
    while (*gids_arr != -1 && size != 0)
    {

        /*an einai ektos oriwn skipareto*/
        if (*gids_arr < 0 || *gids_arr >= MG)
        {
            gids_arr++;
            i--;
            continue;
        }
        /*EAN EINAI TO PRWTO*/
        if (G[*gids_arr]->gsub == NULL)
        {

            Subscription *subscription = (Subscription *)malloc(sizeof(Subscription));
            subscription->sId = sId;
            subscription->snext = NULL;
            G[*gids_arr]->gsub = subscription;
        }
        else
            S_insert(&G[*gids_arr]->gsub, sId);
        /*Print the Group subscription*/
        printGroupSubs(G[*gids_arr]);
        gids_arr++;
        size--;
    }

    return 0;
}

/**
 * @brief Prune Information from server and forward it to client
 *
 * @param tm Information timestamp of arrival
 * @return 0 on success
 *          1 on failure
 */
int Prune(int tm)
{
    return EXIT_SUCCESS;
}
/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(int sId)
{
    int i = 0;
    SubInfo *sub;
    sub = SL_LookUp(first_sub, sId);
    /*an den yparxei to sub*/
    if (isSubEmpty(sub))
        return 1;

    for (i; i < MG; i++)
    {
        /*an den einai ==1 kane consume*/
        if (sub->sgp[i] != (TreeInfo *)1)
        {
        }
        // consume_print(sub, i);
    }
    return 0;
}
/**
 * @brief helping fuction for consume
 *
 * @param sub
 * @param gID
 */
/* int consume_print(SubInfo *sub, int gID)
{
    printf("   GROUPID = <%d>,", gID);
    printf("INFOLIST = <");
    Info *curr_info = sub->sgp[gID];
    //Ean deixnei se NULL(To group den exei info)
    if (curr_info == NULL)
    {
        printf("%p>,", curr_info);
        printf("NEWSGP = <");
        printf("%p>\n", curr_info);
        return 0;
    }
    while (curr_info != NULL)
    {
        printf(" %d ,", curr_info->iId);
        curr_info = curr_info->inext;
    }
    printf(">,NEWSGP = <");
    //update sgp pointer
    //sub->sgp[gID] = prev;
    sub->sgp[gID] = G[gID]->glast;
    printf("%d>\n", sub->sgp[gID]->iId);
    return 0;
}*/
/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(int sId)
{
    int i;
    SubInfo *tmp = SL_LookUp(first_sub, sId);
    if (tmp == NULL)
        return 1;
    /*delete the sub*/
    if (SL_delete(&first_sub, tmp))
        return 1;
    /*print if succed*/
    printSubs(&first_sub);
    printf("\n");
    for (i = 0; i < MG; i++)
    {
        Subscription *s = search(G[i]->gsub, sId);
        if (s != NULL)
        {
            /*delete from each group if the sub had subscribe*/
            S_delete(&G[i]->gsub, sId);
            /*print the result after delete*/
            printGroupSubs(G[i]);
        }
    }
    return 0;
}
/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(void)
{
    int i;

    printGroups();
    printf("\n");
    printSubs(&first_sub);
    printf("\n");
    i = printAllSubs(&first_sub);
    printf("   NO_GROUPS = <%d> ,NO_SUBSCRIBERS <%d>\n", MG, i);

    return 0;
}

/**
 * @brief print igp given info
 *
 * @param info
 */
void print_igp(Info *info)
{
    int i;
    /*ean einai empty*/
    if (isInfoEmpty(info) == 1)
    {
        printf("\n");
        return;
    }
    for (i = 0; i < MG; i++)
    {
        if (info->igp[i] == 1)
            printf("MG:%d=%d ,", i, info->igp[i]);
    }
    printf("\n\n");
}

/**
 * @brief Print Groups | Infolist
 * from 0-MG
 *
 */
void printGroups()
{
    int i;
    for (i = 0; i < MG; i++)
    {
        printf("   GROUPID :  <%d>, INFOLIST : ", G[i]->gId);
        // printInfos(&G[i]->gfirst);
        printf(",SUBLIST : ");
        printSubscriptions(&G[i]->gsub);
    }
}
/**
 * @brief print Group | infolist given the group
 *
 * @param group
 */
void printGroupInfo(Group group[])
{
    printf("   GROUPID :  <%d> , INFOLIST : < ", group->gId);
    // printInfos(&group->gfirst);
    printInorder(group->gr);
    /*print_igp(G[i]->gfirst);*/
    printf(">\n");

    return;
}
/**
 * @brief print Group | Sublist
 * given a group
 *
 * @param group
 */
void printGroupSubs(Group group[])
{
    printf("   GROUPID :  <%d> , SUBLIST : ", group->gId);
    printSubscriptions(&group->gsub);
    return;
}

int is_MG_limits(int id);
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
    int i = 0;
    SubInfo *newSub = (SubInfo *)malloc(sizeof(SubInfo));
    if (p_index == NULL)
    {
        return NULL;
    }
    newSub->sId = ID;
    newSub->stm = TM;
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
    /*INIT OLA ME 1*/
    for (i = 0; i < MG; i++)
    {
        sub->sgp[i] = (TreeInfo *)1;
        sub->tgp[i] = (TreeInfo *)1;
    }
    while (*p_sgp != -1 && p_size > 0)
    {
        /*if out of limits skip*/
        if (!is_MG_limits(*p_sgp))
        {
            sub->sgp[*p_sgp] = NULL;
            sub->tgp[*p_sgp] = NULL; // G[*p_sgp]->gr?
        }

        *p_sgp++;
        p_size--;
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
        return 0;
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
            return 1; /*didnt find the element*/

        else if (temp->sId == sub->sId)
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

void print_sgp(SubInfo *Sub);
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
 * also returns the size of the sublist
 *
 * @param sub
 */
int printAllSubs(SubInfo **sub)
{
    int size = 0;
    SubInfo *curr;
    curr = *sub;
    while (curr != NULL)
    {
        printf("   SUBSCRIBERERID = <%d> ,", curr->sId);
        print_sgp(curr);
        printf("\n");
        curr = curr->snext;
        size++;
    }

    return size;
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
        if (Sub->sgp[i] != (TreeInfo *)1)
        {
            printf(" %d ,", i);
        }
    }
    printf(">");
}

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
/*============================FREE=============================*/

int freeSubs()
{
    SubInfo *curr, *next = first_sub;
    if (isSubEmpty(first_sub))
        return 1;
    while (next != NULL)
    {
        curr = next;
        next = next->snext;
        free(curr);
    }
    return 0;
}
/*int FreeInfos(Info *head)
{
    int i = 0;
    Info *curr = head;
    if (isInfoEmpty(head))
        return 1;
    while (head != NULL)
    {
        curr = head;
        head = head->inext;
        free(curr);
    }
    return 0;
}*/
int freeGroups()
{
    int i = 0;
    for (i; i < MG; i++)
    {
        Info *test = G[i]->gr;
        // FreeInfos(G[i]->gfirst);
        free(G[i]);
    }
    return 0;
}

/*
int main()
{
    int a[6] = {31, 5, 60, 45, 1, -1};
    int b[6] = {57, 35, 60, 43, 1, -1};
    int c[6] = {63, 35, 60, 43, 1, -1};
    int d[7] = {1, 8, 2, 3, 4, 45, -1};

    initialize();
    Insert_Info(2000, 1, a, 6);
    Insert_Info(2001, 2, b, 6);
    Insert_Info(2000, 3, c, 6);

    printf("FINISHED INSERT\n\n");
    if (G[60]->glast != NULL)
        printf("LAST : %d", G[60]->glast->iId);
    else
        printf("null\n");
}
*/