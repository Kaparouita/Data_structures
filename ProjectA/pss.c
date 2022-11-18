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

void updateSubPointer(Subscription *Subscription, Info **info, int G_ID);
int consume_print(SubInfo *sub, int gID);

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(void)
{
<<<<<<< HEAD
    int i;
    /*init Groups*/
    for (i = 0; i < MG; i++)
    {
        G[i] = (Group *)malloc(sizeof(Group));
        G[i]->gId = i;
        G[i]->ggsub = NULL;
        G[i]->gfirst = NULL;
        G[i]->glast = NULL;
    }
    return 1;
=======
    return EXIT_SUCCESS;
>>>>>>> c375b1d0cb72dfdee1e6d35d734c92ecc9bb7735
}

/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(void)
{
    return EXIT_SUCCESS;
}

/**
 * @brief Insert info
 *
 * @param iTM Timestamp of arrival
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Insert_Info(int iTM, int iId, int *gids_arr, int size_of_gids_arr)
{
<<<<<<< HEAD

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
        if (G[*gids_arr]->gfirst == NULL)
        {
            G[*gids_arr]->gfirst = new_info;
            /*UPDATE IT*/
            updateSubPointer(G[*gids_arr]->ggsub, &(G[*gids_arr]->gfirst), *gids_arr);
        }
        /*else insert the info*/
        else if (I_Insert(&G[*gids_arr]->gfirst, new_info))
            return 1; /*if error return 1*/
                      /*Print the Group info*/
        printGroupInfo(G[*gids_arr]);
        gids_arr++;
        i--;
    }
    return 0;
=======
    return EXIT_SUCCESS;
>>>>>>> c375b1d0cb72dfdee1e6d35d734c92ecc9bb7735
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
<<<<<<< HEAD

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
        if (G[*gids_arr]->ggsub == NULL)
        {

            Subscription *subscription = (Subscription *)malloc(sizeof(Subscription));
            subscription->sId = sId;
            subscription->snext = NULL;
            G[*gids_arr]->ggsub = subscription;
        }
        else
            S_insert(&G[*gids_arr]->ggsub, sId);
        /*Print the Group subscription*/
        printGroupSubs(G[*gids_arr]);
        gids_arr++;
        size--;
    }

    return 0;
=======
    return EXIT_SUCCESS;
>>>>>>> c375b1d0cb72dfdee1e6d35d734c92ecc9bb7735
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
        if (sub->sgp[i] != (Info *)1)
            consume_print(sub, i);
    }
    return 0;
}
/**
 * @brief helping fuction for consume
 *
 * @param sub
 * @param gID
 */
int consume_print(SubInfo *sub, int gID)
{
    printf("   GROUPID = <%d>,", gID);
    printf("INFOLIST = <");
    Info *curr_info = sub->sgp[gID], *prev = curr_info;
    /*Ean deixnei se NULL(To group den exei info)*/
    if (curr_info == NULL)
    {
        printf("%p>,", curr_info);
        printf("NEWSGP = <");
        printf("%p>\n", curr_info);
        return 0;
    }
    while (curr_info != NULL)
    {
        prev = curr_info; /*keep prev pointer*/
        printf(" %d ,", curr_info->iId);
        curr_info = curr_info->inext;
    }
    printf(">,NEWSGP = <");
    /*update sgp pointer*/
    sub->sgp[gID] = prev;
    printf("%d>\n", sub->sgp[gID]->iId);
    return 0;
}
/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(int sId)
{
<<<<<<< HEAD
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
        Subscription *s = search(G[i]->ggsub, sId);
        if (s != NULL)
        {
            /*delete from each group if the sub had subscribe*/
            S_delete(&G[i]->ggsub, sId);
            /*print the result after delete*/
            printGroupSubs(G[i]);
        }
    }
    return 0;
=======
    return EXIT_SUCCESS;
>>>>>>> c375b1d0cb72dfdee1e6d35d734c92ecc9bb7735
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
    printAllSubs(&first_sub);

    return 0;
}
<<<<<<< HEAD

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
        printInfos(&G[i]->gfirst);
        printf(",SUBLIST : ");
        printSubscriptions(&G[i]->ggsub);
    }
}
/**
 * @brief print Group | infolist given the group
 *
 * @param group
 */
void printGroupInfo(Group group[])
{
    printf("   GROUPID :  <%d> , INFOLIST : ", group->gId);
    printInfos(&group->gfirst);
    /*print_igp(G[i]->gfirst);*/
    printf("\n");

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
    printSubscriptions(&group->ggsub);
    return;
}

/*
int main()
{
    int a[6] = {31, 5, 60, 45, 1, -1};
    int b[6] = {57, 35, 60, 43, 1, -1};
    int c[6] = {63, 35, 60, 43, 1, -1};
    int d[7] = {1, 8, 2, 3, 4, 45, -1};

    initialize();
    Subscriber_Registration(2005, 3, d, 6);
    Subscriber_Registration(2004, 4, a, 5);
    Subscriber_Registration(2003, 3, d, 6);
    Subscriber_Registration(2001, 6, b, 5);

    // Insert_Info(2005, 3, d, 6);
    //  Insert_Info(2005, 4, a, 5);
    //   Insert_Info(2001, 6, b, 5);
    //   Insert_Info(2003, 7, c, 5);

    // printInfos(&G[1]->gfirst);
    // printGroup(G[60]);

    // printGroups();
}
*/
=======
>>>>>>> c375b1d0cb72dfdee1e6d35d734c92ecc9bb7735
