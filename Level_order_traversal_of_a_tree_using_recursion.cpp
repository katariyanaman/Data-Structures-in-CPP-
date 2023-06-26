/* The following C++ program implements the level order traversal
   of a binary tree by printing the nodes at each level from top to bottom. */

#include <iostream>
#include<stdio.h>
using namespace std;
struct node
{
    int info;
    struct node *left, *right;
};
class Tree
{
public:
    struct node *root;
    struct node  *createnode(int key);
    int heightoftree(struct node *newnode);
    void currentlevel(struct node *root, int level);
    Tree()
    {
        root = NULL;
    }
};

int main()
{   Tree b1;
    struct node *newnode = b1.createnode(25);
    newnode->left = b1.createnode(27);
    newnode->right = b1.createnode(19);
    newnode->left->left = b1.createnode(17);
    newnode->left->right = b1.createnode(91);
    newnode->right->left = b1.createnode(13);
    newnode->right->right = b1.createnode(55);

    cout<<"Level Order Traversal of Tree 1 is \n";
    int i;
    int height = b1.heightoftree(newnode);
    for(i = 1; i <= height; i++)
    {
        b1.currentlevel(newnode,i);
    }
 
    struct node *node = b1.createnode(1);
    node->left = b1.createnode(2);
    node->left->left = b1.createnode(3);
    node->left->left->left = b1.createnode(4);
    node->left->left->left->left = b1.createnode(5);

    cout<<"\n\nLevel Order Traversal of Tree 2 is \n";
    height = b1.heightoftree(node);
    for(i = 1; i <= height; i++)
    {
        b1.currentlevel(node,i);
    }
 
    struct node *root = b1.createnode(15);
 
    cout<<"\n\nLevel Order Traversal of Tree 3 is \n";
    height = b1.heightoftree(root);
    for(i = 1; i <= height; i++)
    {
        b1.currentlevel(root,i);
    }
    return 0;
}

struct node *Tree :: createnode(int key)
{
    struct node *newnode = new node;
    newnode->info = key;
    newnode->left = NULL;
    newnode->right = NULL;
    return(newnode);
}

int Tree :: heightoftree(struct node *root)
{
    int max;
    if (root!=NULL)
    {   
        int leftsubtree = heightoftree(root->left);
        int rightsubtree = heightoftree(root->right);
        if (leftsubtree > rightsubtree)
        {
            max = leftsubtree + 1;
            return max;
        }
        else
        {
            max = rightsubtree + 1;
            return max;
        }
    }
}

void Tree :: currentlevel(struct node *root, int level)
{
    if (root != NULL)
    {
        if (level == 1)
        {
            cout<<root->info<<"\t";
        }
        else if (level > 1)
        {
            currentlevel(root->left, level-1);
            currentlevel(root->right, level-1);
        }
    }
}
