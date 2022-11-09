#include <stdio.h>
#include <stdlib.h>

#include "pss.h"

/*
struct Info
{
    int iId;
    int itm;
    int igp[MG];
    struct Info *iprev;
    struct Info *inext;
};*/

/* @brief check if list is empty
 *
 * @param sub first sub
 * @return 0 if not empty
 *         1 otherwise
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

int I_Insert(Info **last_info, Info *new_info)
{

    if (isInfoEmpty(*last_info) || isInfoEmpty(new_info))
    {
        return 0;
    }
    *last_info->inext = new_info;
    new_info->iprev = *last_info;
    new_info->inext = NULL;
    *last_info = new_info;
    return 1;
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
    return 1;
}

int main()
{
    int a[6] = {31, 5, 6, 45, 1, -1};
    int b[6] = {57, 35, 6, 43, 1, -1};
    int c[6] = {63, 35, 6, 43, 1, -1};

    Group *g1 = malloc(sizeof(Group));
    g1->gId = 1;

    Info *info1 = InfoConstractor(4, 2000, a, 6);
    Info *info2 = InfoConstractor(5, 2001, b, 6);
    Info *info3 = InfoConstractor(6, 2003, c, 6);

    g1->gfirst = info1;
    g1->glast = info2;

    I_Insert(&info1, info2);
    /*
        SubInfo *sub3 = SubInfoConstractor(52, 1999, c);
        SubInfo *sub1 = SubInfoConstractor(5, 4000, b);
        SubInfo *sub2 = SubInfoConstractor(6, 2365, c);
    */

    printInfos(&g1->gfirst);

    // print_sgp(sub4);
    //  printSubs(&first_sub);

    return 0;
}
