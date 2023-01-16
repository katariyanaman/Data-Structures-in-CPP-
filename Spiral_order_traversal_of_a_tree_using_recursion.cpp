#include<iostream>
using namespace std;
struct node
{
    int info;
    struct node* left, *right;
}*root;
 
class Tree
{
    public:
        struct node* createnode(int key);
        int heightoftree(struct node* root);
        void left_to_right(struct node* root, int level);
        void right_to_left(struct node *root, int level);
        Tree()
        {
            root = NULL;
        }
};
struct node* Tree :: createnode(int key)
{
    struct node* newnode = new node;
    newnode->info = key;
    newnode->left = NULL;
    newnode->right = NULL;
 
    return(newnode);
}

 
int Tree :: heightoftree(struct node* root)
{
    int maximum;
 
    if (root!=NULL)
    {
        int leftsubtree = heightoftree(root->left);
 
        int rightsubtree = heightoftree(root->right);  
 
 
        if (leftsubtree > rightsubtree)
        {
            maximum = leftsubtree + 1;
            return maximum;
        }
        else
        {
            maximum = rightsubtree + 1;
            return maximum;
        }
    }
}
 
void Tree :: left_to_right(struct node* root, int level)
{
    if (root != NULL)
    {
        if (level == 1)
        {
            cout<<root->info<<"\t";
        }
 
        else if (level > 1)
        {
            left_to_right(root->left, level-1);
            left_to_right(root->right, level-1);
        }
    }
 
}
 
void Tree :: right_to_left(struct node *root, int level)
{
    if(root!=NULL)
    {
        if(level==1)
        {
            cout<<root->info<<"\t";
        }
        else
        {
            right_to_left(root->right, level-1);
            right_to_left(root->left, level-1);
        }
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

 
    cout<<"Spiral traversal of a tree 1 is \n";
 
    int i, flag=0;
    int height = t.heightoftree(newnode);
    for(i = 1; i <= height; i++)
    {
        if(i%2 != 0)
        {   
            flag=1;
            t.left_to_right(newnode,i);
        }
 
        if(i%2 == 0)
        {
            flag=0;
            t.right_to_left(newnode,i);
        }
    }
 
    struct node *node = t.createnode(1);
    node->right = t.createnode(2);
    node->right->right = t.createnode(3);
    node->right->right->right = t.createnode(4);
    node->right->right->right->right = t.createnode(5);
    node->left = t.createnode(13);
 
 
    cout<<"\n\nSpiral traversal of tree 2 is\n" ;
 
    height = t.heightoftree(node);
    for(i = 1; i <= height; i++)
    {
        if(i%2 != 0)
        {    
            flag=1;
            t.left_to_right(node,i);
        }
 
        if(i%2 == 0)
        {  
            flag=0;
            t.right_to_left(node,i);
        }
    }
  
    struct node *root = t.createnode(15);
 
    cout<<"\n\nSpiral traversal of tree 3 is\n";
 
    height = t.heightoftree(root);
    for(i = 1; i <= height; i++)
    {
        if(i%2 != 0)
        {    
            flag=1;
            t.left_to_right(root,i);
        }
 
        if(i%2 == 0)
        {  
            flag=0;
            t.right_to_left(root,i);
        }
    }
 
 
    return 0;
}
