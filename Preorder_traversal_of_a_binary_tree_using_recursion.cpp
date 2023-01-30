#include<iostream>
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
        struct node *createnode(int key);
        void PreOrder(struct node *root);
        Tree()
        {
            root = NULL;
        }
};
struct node *Tree :: createnode(int key)
{
    struct node *newnode = new node;
    newnode->info = key;
    newnode->left = NULL;
    newnode->right = NULL;
    return(newnode);
}
void Tree :: PreOrder(struct node *root)
{
     if(root != NULL)
     {
          cout<<root->info<<" ";
          PreOrder(root->left);
          PreOrder(root->right);
     }
}

int main()
{
    Tree t;
    struct node *newnode = t.createnode(25);
    newnode->left = t.createnode(27);
    newnode->right = t.createnode(19);
    newnode->left->left = t.createnode(17);
    newnode->left->right = t.createnode(91);
    newnode->right->left = t.createnode(13);
    newnode->right->right = t.createnode(55);

    cout<<"PreOrder Traversal of  tree 1 is \n";
    t.PreOrder(newnode);
 
    struct node *node = t.createnode(1);
    node->right = t.createnode(2);
    node->right->right = t.createnode(3);
    node->right->right->right = t.createnode(4);
    node->right->right->right->right = t.createnode(5);

    cout<<"\n\nPreOrder Traversal  of tree 2 is\n" ;
    t.PreOrder(node);
 
    struct node *root = t.createnode(15);

    cout<<"\n\nPreOrder traversal of tree 3 is\n";
    t.PreOrder(root);
    return 0;
}
