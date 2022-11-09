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
#include "SubAndInfo.h"

SubInfo *first_sub;
Group GROUPS[MG];

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(void)
{
    /*init Groups*/
    for (int i = 0; i < MG; i++)
    {
        G[i] = (Group *)malloc(sizeof(Group));
        G[i]->gId = i;
        G[i]->ggsub = NULL;
        G[i]->gfirst = NULL;
        G[i]->glast = NULL;
    }
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
    Info *new_info = InfoConstractor(iTM, iId, gids_arr, size_of_gids_arr);
    if (first_info == NULL)
    {
        first_info = new_info;
        return 0;
    }
    if (I_Insert(&first_info, new_info) == 0)
        return 0;
    return 1;
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
    SubInfo *new_sub = SubInfoConstractor(sId, sTM, gids_arr, size_of_gids_arr);
    if (first_sub == NULL)
    {
        first_sub = new_sub;
        return 0;
    }
    if (Sub_Insert(&first_sub, new_sub) == 0)
        return 0;
    return 1;
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
    return EXIT_SUCCESS;
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
    SubInfo *tmp = SL_LookUp(first_sub, sId);
    if (SL_delete(&first_sub, tmp) == 0)
        return 0;
    return 1;
}
/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(void)
{
    return EXIT_SUCCESS;
}
