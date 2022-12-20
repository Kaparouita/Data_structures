#include <stdio.h>
#include <stdlib.h>

#include "pss.h"

TreeInfo *TreeInfoConstractor(int tId, int ttm)
{
    TreeInfo *newTreeInfo = (TreeInfo *)malloc(sizeof(TreeInfo));
    newTreeInfo->tId = tId;
    newTreeInfo->ttm = ttm;
    newTreeInfo->next = NULL;
    newTreeInfo->tlc = NULL;
    newTreeInfo->trc = NULL;
    newTreeInfo->tp = NULL;
    return newTreeInfo;
}

TreeInfo *Insert_TI(TreeInfo *root, TreeInfo *new, TreeInfo *parent)
{
    if (root == NULL)
    {
        /*Otan einai mikrotero */
        if (parent->ttm > new->ttm)
        {
            TreeInfo *dummy = TreeInfoConstractor(new->tId, new->ttm);

            /*update childs*/
            new->tlc = dummy;
            new->trc = parent;
            /*update parents*/
            /*AN EINAI TO ROOT*/
            if (parent->tp != NULL)
                if (parent->tp->trc->ttm == parent->ttm)
                {
                    /*update list*/
                    parent->tp->tlc->next = dummy;
                    parent->tp->trc = new;
                }
                else
                    parent->tp->tlc = new;
            new->tp = parent->tp;
            parent->tp = new;
            dummy->tp = new;
            /*update list*/
            dummy->next = parent;
            return new;
        }
        else if (parent->ttm < new->ttm)
        {
            TreeInfo *dummy = TreeInfoConstractor(parent->tId, parent->ttm);
            /*update childs*/
            dummy->tlc = parent;
            dummy->trc = new;
            if (parent->tp != NULL)
                if (parent->tp->trc->ttm == parent->ttm)
                    parent->tp->trc = dummy;
                else
                    parent->tp->tlc = dummy;
            /*update parents*/
            dummy->tp = parent->tp;
            new->tp = dummy;
            parent->tp = dummy;
            /*update list*/
            parent->next = new;
            return dummy;
        }
    }
    if (root->ttm > new->ttm)
        new = Insert_TI(root->tlc, new, root);
    /*mikrotero aristera*/
    else if (root->ttm < new->ttm)
        new = Insert_TI(root->trc, new, root);
    if (new->tp == NULL)
        return new;
    return root;
}

TreeInfo *LookUp_IT(TreeInfo *root, int ttm)
{
    if (root == NULL || root->ttm == ttm)
        return root;
    if (root->ttm > ttm)
        LookUp_IT(root->tlc, ttm);
    else
        LookUp_IT(root->trc, ttm);
}

void printTree(TreeInfo *root)
{
    if (root != NULL)
    {
        printf("%d ", root->ttm);
        if (root->tlc != NULL)
            printf("-> (l:%d) ", root->tlc->ttm);
        if (root->trc != NULL)
            printf("-> (r:%d) ", root->trc->ttm);
        if (root->tp != NULL)
            printf("-> (p:%d) ", root->tp->ttm);
        printf("\n");

        printTree(root->tlc);
        printTree(root->trc);
    }
}

void printTreeID(TreeInfo *root)
{
    if (root != NULL)
    {
        printf("%d ", root->tId);
        if (root->tlc != NULL)
            printf("-> (l:%d) ", root->tlc->tId);
        if (root->trc != NULL)
            printf("-> (r:%d) ", root->trc->tId);
        if (root->tp != NULL)
            printf("-> (p:%d) ", root->tp->tId);
        printf("\n");

        printTreeID(root->tlc);
        printTreeID(root->trc);
    }
}
TreeInfo *GetListRoot(TreeInfo *root)
{
    while (root->tlc != NULL)
        root = root->tlc;
    return root;
}
/**
 * @brief return the last element(the most right one)
 *
 * @param root
 * @return TreeInfo*
 */
TreeInfo *PrintTreeList(TreeInfo *root)
{
    while (root->tlc != NULL)
        root = root->tlc;
    while (root->next != NULL)
    {
        printf("%d ,", root->tId);
        root = root->next;
    }
    printf("%d", root->tId);
    return root;
}
void pl(TreeInfo *root)
{
    while (root != NULL)
    {
        if (root->tlc == NULL && root->trc == NULL)
            printf("%d ,", root->ttm);
        root = root->next;
    }
}
/*
int main()
{
    TreeInfo *a = TreeInfoConstractor(1, 20);

    TreeInfo *first = Insert_TI(a, TreeInfoConstractor(2, 10), NULL);
    printTree(first);
    printf("---------\n");
    Insert_TI(first, TreeInfoConstractor(3, 15), NULL);
    printTree(first);
    printf("---------\n");
    Insert_TI(first, TreeInfoConstractor(4, 5), NULL);
    printTree(first);
    printf("---------\n");
    Insert_TI(first, TreeInfoConstractor(5, 3), NULL);
    printTree(first);
    printf("---------\n");
    Insert_TI(first, TreeInfoConstractor(6, 30), NULL);
    printTree(first);
    pl(GetListRoot(first));

    printf("\n%d\n", LookUp_IT(first, 4)->ttm);
}*/