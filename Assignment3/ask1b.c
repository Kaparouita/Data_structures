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
typedef struct node Node;
struct node
{
    int val;
    struct node *left;
    struct node *right;
};

Node *root;

Node *nodeConstr(int val)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->val = val;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
// update childrens
treenode *tranform(Node *root)
{
    if (root == NULL)
        return NULL;
    treenode *new_node = (treenode *)malloc(sizeof(treenode));
    new_node->val = root->val;
    new_node->k = root.k;
    new_node->k = 0;
    // child
    Node *P = root->left;
    while (P != NULL)
    {
        treenode *new_child = (treenode *)malloc(sizeof(treenode));
        new_child->val = P->val;

        // Add the child
        new_node->children[new_node->k] = new_child;

        printf("Parent val :%d ,", root->val);
        printf("Child %d :%d\n", new_node->k, new_node->children[new_node->k]->val);

        // update the size
        new_node->k = (new_node->k + 1);
        P = P->right;
    }
    return new_node;
}
/*Time complexity O(n) afou diasxizw olo to tree
 Space complexity O(n) afou kanw copy ena tree*/
treenode *tranformTree(Node *R)
{
    int i = 0;
    if (R == NULL)
        return NULL;
    // kanw init ta paidia tou
    treenode *node = tranform(R);
    // proxwraw to root sta paidia
    R = R->left;
    while (R != NULL)
    {
        // to kanw sto prwto paidi
        node->children[i] = tranformTree(R);
        // gia kathe paidi
        R = R->right;
        i++;
    }
    return node;
}

//ask2b
void treenodeRight(treenode *root){
  int i=0;
  if(root==NULL)
     return;
   i=root->k-1;
   while(i>=0){
      printf("%d ,",root->children[i]->val);
      i--;
   }  
   i=root->k-1;
   while(i>=0){
     treenodeRight(root->children[i]);
     i--;
   } 
   
}
int main()
{
    root = (Node *)malloc(sizeof(Node));
    root->val = 1;
    root->left = nodeConstr(2);
    root->left->left = nodeConstr(4);
    root->left->right = nodeConstr(6);
    root->left->right->left = nodeConstr(7);
    root->left->right->left->left = nodeConstr(8);
    root->left->right->left->left->right = nodeConstr(9);
    root->left->right->left->left->left = nodeConstr(10);
    root->left->left->right = nodeConstr(5);
    root->left->left->right->left = nodeConstr(11);
    // Visit(root);
    // tranform(root);
    treenode *a = tranformTree(root);
    treenodeRight(a);
}