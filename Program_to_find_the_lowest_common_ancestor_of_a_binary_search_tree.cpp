/* The following C++ program is implementing the Lowest Common Ancestor (LCA) algorithm
   in a binary search tree (BST) to find the lowest common ancestor of two given nodes. */

#include<conio.h>
#include <stdio.h>
#include<iostream>
using namespace std;
struct node
{
    int data;
    struct node *left, *right;
};

class BST
{
public:
    struct node *lca(struct node *root, int node_1, int node_2)
    {
        if (root != NULL)
        {
            if (root->data > node_1 && root->data > node_2)
            {
                return lca(root->left, node_1, node_2);
            }
            if (root->data < node_1 && root->data < node_2)
            {
                return lca(root->right, node_1, node_2);
            }
            return root;
        }
    }
    struct node *newNode(int data)
    {
        struct node *p = NULL;
        p = new node;
        p->data = data;
        p->left = p->right = NULL;
        return(p);
    }
};
int main()
{
    BST b1;
    struct node *root = b1.newNode(20);
    root->left = b1.newNode(8);
    root->right = b1.newNode(22);
    root->left->left = b1.newNode(4);
    root->left->right = b1.newNode(12);
    root->left->right->left = b1.newNode(10);
    root->left->right->right = b1.newNode(14);
   
    int node_1 = 10, node_2 = 14;
    struct node *t = b1.lca(root, node_1, node_2);
    printf("LCA of %d and %d is %d \n", node_1, node_2, t->data);
    node_1 = 14, node_2 = 8;
    t = b1.lca(root, node_1, node_2);
    printf("LCA of %d and %d is %d \n", node_1, node_2, t->data);
    node_1 = 10, node_2 = 22;
    t = b1.lca(root, node_1, node_2);
    printf("LCA of %d and %d is %d \n", node_1, node_2, t->data);
    getch();
}
