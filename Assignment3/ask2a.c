#include <stdio.h>
#include <stdlib.h>

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
/*find depth given root and key of the node iam looking for*/
int NodeDepth(Node *root, int key, int depth)
{
    int left, right;
    if (root == NULL)
        return 0;
    /*otan vreis to val kane return*/
    if (root->val == key)
        return depth;
    /*tsekare aristera*/
    left = NodeDepth(root->left, key, depth + 1);
    if (left != 0)
        return left;

    right = NodeDepth(root->right, key, depth + 1);
    if (right != 0)
        return right;

    return 0;
}
/*find height of a node*/
int Nodeheight(Node *root)
{
    int l, r;
    if (root == NULL)
        return -1;
    l = Nodeheight(root->left);
    r = Nodeheight(root->right);

    if (l > r)
        return (l + 1);
    else
        return (r + 1);
}
/**
 * @brief find out if there is a node witch height==depth
 *
 * @param root
 * @return 1 if true else 0
 */
int DepthEqualHeight(Node *cur_root, Node *root)
{
    if (cur_root == NULL)
        return 0;
    if (NodeDepth(root, cur_root->val, 0) == Nodeheight(cur_root))
    {
        printf("%d\n", cur_root->val);
        printf("%d  %d\n", Nodeheight(cur_root), NodeDepth(root, cur_root->val, 0));
        return 1;
    }
    return DepthEqualHeight(cur_root->left, root) || DepthEqualHeight(cur_root->right, root);
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
    // root->left->right->left->left->left->right = nodeConstr(11);

    root->left->left->right = nodeConstr(5);
    root->left->left->right->left = nodeConstr(11);

    // inorderTraversal(root);
    postorderTraversal(root);
    printf("\n");
    printf("%d  %d\n", Nodeheight(root->left->right), NodeDepth(root, 6, 0));
    printf("%d", DepthEqualHeight(root, root));
}