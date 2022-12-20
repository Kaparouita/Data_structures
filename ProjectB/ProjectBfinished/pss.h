/***************************************************************
 *
 * file: pss.h
 *
 * @Authors  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr), John Petropoulos (johnpetr@csd.uoc.gr)
 * @Version 30-11-2022
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Header file for the Public Subscribe System,
 * with the structures and function prototypes
 *
 ***************************************************************
 */

#ifndef pss_h
#define pss_h
#define MG 64

typedef struct Info Info;
typedef struct SubInfo SubInfo;
typedef struct TreeInfo TreeInfo;
typedef struct Subscription Subscription;
typedef struct Group Group;
typedef struct SymTable_S SymTable_S;

struct Info
{
    int iId;
    int itm;
    int igp[MG];
    struct Info *ilc;
    struct Info *irc;
    struct Info *ip;
};
struct Subscription
{
    int sId;
    struct Subscription *snext;
};
struct Group
{
    int gId;
    struct Subscription *gsub;
    struct Info *gr;
};
struct SubInfo
{
    int sId;
    int stm;
    struct TreeInfo *tgp[MG];
    struct TreeInfo *sgp[MG];
    struct SubInfo *snext;
};
struct TreeInfo
{
    int tId;
    int ttm;
    struct TreeInfo *tlc;
    struct TreeInfo *trc;
    struct TreeInfo *tp;
    struct TreeInfo *next;
};
struct SymTable_S
{
    SubInfo **Subs;
    int buckets;
    int length;
    unsigned hs; /*hash multiplier*/
};

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @param m Size of hash table
 * @param p Prime number for the universal hash function
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(int m, int p, SymTable_S **table);

/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(void);

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
int Insert_Info(int iTM, int iId, int *gids_arr, int size_of_gids_arr);

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
int Subscriber_Registration(int sTM, int sId, int *gids_arr, int size_of_gids_arr, SymTable_S *table);

/**
 * @brief Prune Information from server and forward it to client
 *
 * @param tm Information timestamp of arrival
 * @return 0 on success
 *          1 on failure
 */
int Prune(int tm, SymTable_S *table);

/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(int sId, SymTable_S *table);

/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(int sId, SymTable_S *table);

/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(SymTable_S *table);

/*=====================MYFUCTIONS==================*/
/**
 * @brief print Group | infolist given the group
 *
 * @param group
 */
void printGroupInfo(Group group[]);
/**
 * @brief print Group | Sublist
 * given a group
 *
 * @param group
 */
void printGroupSubs(Group group[]);
/**
 * @brief given the head of a list print ids of the subs
 *
 * @param sub
 */
void printSubscriptions(Subscription **sub);
/**
 * @brief Print all sub list given head (first_sub)
 * also returns the size of the sublist
 *
 * @param sub
 */
int printAllSubs(SymTable_S *table);
/**
 * @brief init the sgp of a sub
 *
 * @param sub
 * @param p_sgp
 * @param p_size
 */
void SubSgpINIT(SubInfo *sub, int *p_sgp, int p_size);

/*------------------------------INFO_LIST-------------------------*/

/**
 * @brief check if empty
 *
 * @param info
 * @return return 1 if empty
 */
int isInfoEmpty(Info *info);

/**
 * @brief Create an info given its attributes
 *
 * @param iTM
 * @param iId
 * @param gp
 * @param gp_size
 * @return Info*
 */
Info *InfoConstractor(int iTM, int iId, int *gp, int gp_size);

/**
 * @brief given the last info and a new
 *        add the new to the list
 *
 * @param last_info
 * @param new_info
 * @return int 1 if fails , 0 if succeed
 */
int I_Insert(Info **head_ref, Info *newInfo);

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
 * @return returns info
 */
Info *I_LookUp(Info *head, int ID);

void printInfos(Info **sub);

/*------------------------------SUBSCRIPTION-------------------------*/

/**
 * @brief checks if its empty
 *
 * @param sub
 * @return return 0 if not null
 */
int S_isEmpty(Subscription *sub);
/**
 * @brief look for a sub with the id
 *
 * @param head
 * @param id
 * @return the subscription or NULL if not found
 */
Subscription *search(Subscription *head, int id);

/**
 * @brief insert a new subscription with the new_ID
 *
 * @param head
 * @param new_ID
 * @return return 0 if succeed
 *         1 if fails
 */
int S_insert(Subscription **head, int new_ID);

/**
 * @brief Deletes a subscription
 *
 * @param head
 * @param ID
 * @return return 0 if succeed
 *         1 if fails
 */
int S_delete(Subscription **head, int ID);

/*------------------------------SUBLIST------------------------------*/

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

/*====================EXTRA PRINTS====================*/
void printSubs(SymTable_S *table);
void print_sgp(SubInfo *Sub);

void printGroups();

int consume_print(SubInfo *sub, int gID);

/*=====================FREE================*/

int FreeInfos(Info *head);
int freeSubs();
int freeGroups();

Info *BST_insert(Info *root, Info *new_info);
Info *BST_search(Info *root, int key);
Info *BST_delete(Info *root, Info *del);
void printBST(Info *root);
void printInorder(Info *node);

TreeInfo *Insert_TI(TreeInfo *root, TreeInfo *new, TreeInfo *parent);
TreeInfo *TreeInfoConstractor(int tId, int ttm);
void printTree(TreeInfo *root);
void printTreeID(TreeInfo *root);
void printInorderTree(TreeInfo *node);
TreeInfo *PrintTreeList(TreeInfo *root);

Info *getInfoForPrune(Info *root, int tm);
void SubTgpUpdate(int gId, Info *info, SymTable_S *table);
int SL_delete(SubInfo **head, SubInfo *sub);
void printSubsTgpInfo(SubInfo **sub);

static unsigned int SymTable_hash(int subinfo_ID, SymTable_S *table);
SymTable_S *SymTable_new(int BUCKETS, unsigned hs);
int SymTable_contains(SymTable_S *table, SubInfo *sub);
int SymTable_remove(SymTable_S *table, SubInfo *sub);
SubInfo *SymTable_get(SymTable_S *table, int sId);
int SymTable_insert(SymTable_S *table, SubInfo *subinfo);

#endif /* pss_h */
