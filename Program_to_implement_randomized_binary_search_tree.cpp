/* The following C++ program implements a Randomized Binary Search Tree (RBST) data structure
   with operations such as insertion, search, counting nodes, checking if the tree is empty, and clearing
   the tree. It also provides traversal methods (in-order, pre-order, and post-order) to display the elements in the tree. */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>   
#define MAX_VALUE 65536
using namespace std;

class RBSTNode
{  
    public: 
        RBSTNode *left, *right;
        int priority, element;  
        RBSTNode()
        {
            this->element = 0;
            this->left = this;
            this->right = this;
            this->priority = MAX_VALUE;         
        }    
        RBSTNode(int ele)
        {
            RBSTNode(ele, NULL, NULL);         
        } 
        RBSTNode(int ele, RBSTNode *left, RBSTNode *right)         
        {
            this->element = ele;
            this->left = left;
            this->right = right;
            this->priority = rand() % 100 + 1;
        }    
};

class RandomizedBinarySearchTree
{
    private: 
        RBSTNode *root;
        RBSTNode *nil;
    public:
         RandomizedBinarySearchTree()
         {
             root = nil;
         }
         bool isEmpty()
         {
             return root == nil;
         }
         void makeEmpty()
         {
             root = nil;
         }
 
         void insert(int X)
         {
             root = insert(X, root);
         }
         RBSTNode *insert(int X, RBSTNode *T)\
         {
             if (T == nil)
                 return new RBSTNode(X, nil, nil);
             else if (X < T->element)
             {
                 T->left = insert(X, T->left);
                 if (T->left->priority < T->priority)
                 {
                      RBSTNode *L = T->left;
                      T->left = L->right;
                      L->right = T;
                      return L;
                  }    
             }
             else if (X > T->element)
             {
                 T->right = insert(X, T->right);
                 if (T->right->priority < T->priority)
                 {
                     RBSTNode *R = T->right;
                     T->right = R->left;
                     R->left = T;
                     return R;
                 }
             }
             return T;
         }
         
         int countNodes()
         {
             return countNodes(root);
         }
 
         int countNodes(RBSTNode *r)
         {
             if (r == nil)
                 return 0;
             else
             {
                 int l = 1;
                 l += countNodes(r->left);
                 l += countNodes(r->right);
                 return l;
             }
         }
       
         bool search(int val)
         {
             return search(root, val);
         }
         bool search(RBSTNode *r, int val)
         {
             bool found = false;
             while ((r != nil) && !found)
             {
                 int rval = r->element;
                 if (val < rval)
                     r = r->left;
                 else if (val > rval)
                     r = r->right;
                 else
                 {
                     found = true;
                     break;
                 }
                 found = search(r, val);
             }
             return found;
         }
 
         void inorder()
         {
             inorder(root);
         }
 
         void inorder(RBSTNode *r)
         {
             if (r != nil)
             {
                 inorder(r->left);
                 cout<<r->element <<"  ";
                 inorder(r->right);
             }
         }
         
         void preorder()
         {
             preorder(root);
         }
         void preorder(RBSTNode *r)
         {
             if (r != nil)
             {
                 cout<<r->element <<"  ";
                 preorder(r->left);             
                 preorder(r->right);
             }
         }
 
         void postorder()
         {
             postorder(root);
         }
         void postorder(RBSTNode *r)
         {
             if (r != nil)
             {
                 postorder(r->left);             
                 postorder(r->right);
                 cout<<r->element <<"  ";
             }
         }         
};     

int main()
{            
    RandomizedBinarySearchTree rbst; 
    cout<<"Randomized Binary SearchTree Test\n";          
    char ch;
    int choice, item;
   
    do    
    {
        cout<<"\nRandomized Binary SearchTree Operations\n";
        cout<<"1. Insert "<<endl;
        cout<<"2. Search "<<endl;
        cout<<"3. Count Nodes "<<endl;
        cout<<"4. Check Empty"<<endl;
        cout<<"5. Clear"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;            
        switch (choice)
        {
        case 1: 
            cout<<"Enter integer element to insert: ";
            cin>>item;
            rbst.insert(item);                     
            break;                          
        case 2: 
            cout<<"Enter integer element to search: ";
            cin>>item;
            if (rbst.search(item))
                cout<<"Element "<<item<<" found in the Tree"<<endl;
            else
                cout<<"Element "<<item<<" not found in the Tree"<<endl;
            break;                                          
        case 3: 
            cout<<"Nodes = "<<rbst.countNodes()<<endl;
            break;     
        case 4:
            if (rbst.isEmpty()) 
                cout<<"Tree is Empty"<<endl;
            else
                cout<<"Tree is not Empty"<<endl;
            break;
        case 5: 
            cout<<"\nRandomizedBinarySearchTree Cleared"<<endl;
            rbst.makeEmpty();
            break;            
        default: 
            cout<<"Wrong Entry \n ";
            break;   
        }
 
        cout<<"\nPost order : ";
        rbst.postorder();
        cout<<"\nPre order : ";
        rbst.preorder();    
        cout<<"\nIn order : ";
        rbst.inorder();
        cout<<"\nDo you want to continue (Type y or n) \n";
        cin>>ch;                  
    } 
    while (ch == 'Y'|| ch == 'y');               
    return 0;
}
