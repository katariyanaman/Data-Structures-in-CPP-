/* The following C++ program demonstrates the creation and
   manipulation of binary trees by creating the mirror image of each tree
   and performing level order traversal before and after the mirror image transformation. */

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
        void mirrorimage(struct node *root);
        int heightoftree(struct node *root);
        void currentlevel(struct node *root, int level);
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

void Tree :: mirrorimage(struct node *root)
{
  if (root != NULL)
    {
        struct node *temp;
        mirrorimage(root->left);
        mirrorimage(root->right);     
        temp = root->left;         
         
        root->left  = root->right;  
        root->right = temp;
    }
}

int Tree :: heightoftree(struct node *root)
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
   
    cout<<"Level Order Traversal of Tree 1 before creating its mirror image is";
    cout<<endl;
    int i;
    int height = t.heightoftree(newnode);
    for(i = 1; i <= height; i++)     
    {
        t.currentlevel(newnode,i);
    }
    cout<<"\n\nLevel Order Traversal of Tree 1 after creating its mirror image is";
    cout<<endl;
    height = t.heightoftree(newnode);
    t.mirrorimage(newnode);
    for(i = 1; i <= height; i++)      
    {
        t.currentlevel(newnode,i);
    }
     struct node *node = t.createnode(1);
    node->right = t.createnode(2);
    node->right->right = t.createnode(3);
    node->right->right->right = t.createnode(4);
    node->right->right->right->right = t.createnode(5);
   
    cout<<endl;
    cout<<"\nLevel Order Traversal of Tree 2 before creating its mirror image is";
    cout<<endl;
    height = t.heightoftree(node);
    for(i = 1; i <= height; i++) 
    {
        t.currentlevel(node,i);
    }
    cout<<endl;
    cout<<"\nLevel Order Traversal of Tree 2 after creating its mirror image is";
    cout<<endl;
    height = t.heightoftree(node);
    t.mirrorimage(node);
    for(i = 1; i <= height; i++) 
    {
        t.currentlevel(node,i);
    }
 
    struct node *root = t.createnode(15);
   
    cout<<endl;
    cout<<"\nLevel Order Traversal of Tree 3 before creating its mirror image is";
    cout<<endl;
    height = t.heightoftree(root);
    for(i = 1; i <= height; i++) 
    {
        t.currentlevel(root,i);
    }
    cout<<endl;
    cout<<"\nLevel Order Traversal of Tree 3 after creating its mirror image is";
    cout<<endl;
    height = t.heightoftree(root);
    t.mirrorimage(root);
    for(i = 1; i <= height; i++) 
    {
        t.currentlevel(root,i);
    }
    return 0;
}
