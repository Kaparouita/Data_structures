#include <stdio.h>
#include <stdlib.h>

// Structure of each node of the tree
#include <stdio.h>
#include <stdlib.h>

// Structure of each node of the tree
typedef struct treenode treenode;

struct treenode
{
    int k;
    int val;
    struct treenode *children[];
};

Node *root;