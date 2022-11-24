#include <stdio.h>
#include <stdlib.h>

// Structure of each node of the tree
typedef struct node Node;
struct node
{
    int val;
    struct node *left;
    struct node *right;
};

Node *root;

// Postorder traversal
void postorderTraversal(struct node *root)
{
    if (root == NULL)
        return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ->", root->val);
}
// Inorder traversal
void inorderTraversal(struct node *root)
{
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ->", root->val);
    inorderTraversal(root->right);
}

Node *nodeConstr(int val)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->val = val;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

// ASK1.a
/*Xronikh polyplokothta O(n) afou prepei na episkeftoume n komvous
  Xwrikh  polyplokothta O(h) opou h to upsos tou dentrou */
Node *clone(Node *root)
{
    if (root == NULL)
        return NULL;
    // copy the root
    Node *new_root = (Node *)malloc(sizeof(Node));
    new_root->val = root->val;
    // anadromika copy ta left kai right
    new_root->left = clone(root->left);
    new_root->right = clone(root->right);

    return new_root;
}

int main()
{
    root = (Node *)malloc(sizeof(Node));
    root->val = 1;
    root->left = nodeConstr(2);
    root->right = nodeConstr(3);
    root->left->left = nodeConstr(4);
    root->left->right = nodeConstr(6);
    root->right->right = nodeConstr(12);
    root->right->left = nodeConstr(10);
    Node *new_root = clone(root);
    inorderTraversal(root);
    // postorderTraversal(root);
    printf("\n");
    inorderTraversal(new_root);
}