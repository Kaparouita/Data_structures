#include <stdio.h>
#include <stdlib.h>

#include "pss.h"

void BST_copy(Info *info, Info *copy);

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
    newInfo->itm = iId;
    newInfo->itm = iTM;
    newInfo->ilc = NULL;
    newInfo->irc = NULL;
    newInfo->ip = NULL;
    /*INIT OLA ME 0*/
    for (i = 0; i < MG; i++)
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
 * @brief
 *
 * @param root
 * @return
 */
Info *BST_insert(Info *root, Info *new_info)
{
    if (root == NULL)
        return new_info;
    /*keep the parent*/
    new_info->ip = root;
    /*an einai megalytero deksia*/
    if (root->itm > new_info->itm)
        root->ilc = BST_insert(root->ilc, new_info);
    /*mikrotero aristera*/
    else if (root->itm < new_info->itm)
        root->irc = BST_insert(root->irc, new_info);
    return root;
}

Info *BST_search(Info *root, int key)
{
    if (root == NULL || root->itm == key)
        return root;
    if (root->itm > key)
        return BST_search(root->ilc, key);
    return BST_search(root->irc, key);
}

Info *minValueNode(Info *node)
{
    Info *current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->ilc != NULL)
        current = current->ilc;

    return current;
}

int *BST_delete(Info *root, Info *del)
{
    Info *child, *tmp_p;
    /*AN EINAI FYLLO*/
    if (del->irc == NULL && del->ilc == NULL)
    {
        /*an einai diaforo tou root*/
        if (del != root)
        {
            tmp_p = del->ip;
            if (tmp_p->irc == del)
                tmp_p->irc = NULL;
            else
                tmp_p->ilc = NULL;
        }
        else
            root = NULL;
        free(del);
        return 0;
    }
    /*AN EXEI ENA PAIDI*/
    else if (del->ilc == NULL || del->irc == NULL)
    {
        /*vres to paidi p den einai NULL*/
        child = (del->irc) ? del->irc : del->ilc;
        if (del != root)
        {
            tmp_p = del->ip;
            if (tmp_p->irc == del)
            {
                tmp_p->irc = child;
                child->ip = tmp_p;
            }
            else
            {
                tmp_p->ilc = child;
                child->ip = tmp_p;
            }
        }
        else
            root = child;
        free(del);
    }
    /*AN EXEI 2 PAIDIA*/
    else
    {
        /*vres me to pio mikro gia na to antikatasthsw*/
        child = minValueNode(del->irc);
        /*krata ena copy tou min value*/
        tmp_p = InfoConstractor(child->itm, child->iId, child->igp, MG);
        /*kane del to min value*/
        BST_delete(root, child);
        BST_copy(del, tmp_p);
    }
}

/**
 * @brief copy info values to another w/o changing its pointers
 *
 * @param info
 * @param copy
 * @return void
 */
void BST_copy(Info *info, Info *copy)
{
    int i = 0;
    for (i = 0; i < MG; i++)
    {
        info->igp[i] = copy->igp[i];
    }
    info->itm = copy->itm;
    info->itm = copy->itm;
}

void printBST(Info *root)
{
    if (root != NULL)
    {
        printf("%d ", root->itm);
        if (root->ilc != NULL)
            printf("-> (l:%d) ", root->ilc->itm);
        if (root->irc != NULL)
            printf("-> (r:%d) ", root->irc->itm);
        if (root->ip != NULL)
            printf("-> (p:%d) ", root->ip->itm);
        printf("\n");

        printBST(root->ilc);
        printBST(root->irc);
    }
}

void printInorder(Info *node)
{
    if (node == NULL)
        return;

    /* first recur on left child */
    printInorder(node->ilc);

    /* then print the data of node */
    printf("%d , ", node->itm);

    /* now recur on right child */
    printInorder(node->irc);
}

/*int main()
{
    int a[6] = {31, 5, 6, 45, 1, -1};
    int b[6] = {57, 35, 6, 43, 1, -1};
    int c[6] = {63, 35, 6, 43, 1, -1};

    Info *first = InfoConstractor(1000, 8, a, 6);
    BST_insert(first, InfoConstractor(1002, 12, c, 6));
    BST_insert(first, InfoConstractor(1002, 9, a, 6));
    BST_insert(first, InfoConstractor(1002, 10, a, 6));
    BST_insert(first, InfoConstractor(1003, 3, a, 6));
    BST_insert(first, InfoConstractor(1010, 15, c, 6));
    BST_insert(first, InfoConstractor(1001, 5, b, 6));
    BST_insert(first, InfoConstractor(1001, 5, b, 6));

    printBST(first);

    BST_delete(first, BST_search(first, 8));
    printf("-----------\n");
    printBST(first);
    // printf("\n%d", copy->iId);

    return 0;
}*/