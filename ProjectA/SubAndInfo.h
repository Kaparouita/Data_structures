#ifndef SubAndInfo_h
#define SubAndInfo_h
#include "pss.h"

/*                  INFO LIST                   */
/**
 * @brief check if empty
 *
 * @param info
 * @return int
 */
int isInfoEmpty(Info *info);

Info *InfoConstractor(int iTM, int iId, int *gp, int gp_size);

/**
 * @brief given the last info and a new
 *        add the new to the list
 *
 * @param last_info
 * @param new_info
 * @return int 1 if fails , 0 if succeed
 */
int I_Insert(Group *group, Info *newInfo);

/**
 * @brief delete an info from the list
 *
 * @param head
 * @param sub
 * @return 0 if succeed , 1 if fails
 */
int I_delete(Info **head, Info *sub);

/**
 * @brief look for a specific ID info
 *
 * @param head
 * @param ID
 * @return Info*
 */
Info *I_LookUp(Info *head, int ID);

void printInfos(Info **sub);

/*                    SUB  LIST                  */

int isSubEmpty(SubInfo *sub);
/**
 * @brief creates a SubInfo
 *
 * @param ID
 * @param TM
 * @param p_index an array with the MG values sub wants to follow
 * @return SubInfo* if succed
 *         NULL if not
 */
SubInfo *SubInfoConstractor(int ID, int TM, int *p_index, int p_size);
/**
 * @brief Instert a new sub to the list
 *
 * @param head_ref first sub
 * @param newSub   new sub
 * @return 0 if succeed
 *         else returns 1
 */
int Sub_Insert(SubInfo **head_ref, SubInfo *newSub);
/**
 * @brief deletes the sub from the list
 *
 * @param headref first sub
 * @param sub     sub to delete
 * @return 0 if succeed
 *         1 if fails
 */
int SL_delete(SubInfo **head, SubInfo *sub);
/**
 * @brief Given the ID return the SubInfo owner of the ID
 *
 * @param head
 * @param ID
 * @return SubInfo*
 *         NULL if its not in the list
 */
SubInfo *SL_LookUp(SubInfo *head, int ID);
/**
 * @brief prints all subs
 *
 * @param sub first sub
 */
void printSubs(SubInfo **sub);

void printGroups();
#endif
