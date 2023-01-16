#include <iostream>
#include <cstdlib>
using namespace std;
  
class SBBSTNode
{
    public:
        int height, data;
        SBBSTNode *left, *right;
         SBBSTNode()
         {
             left = NULL;
             right = NULL;
             data = 0;
             height = 0;
         }
 
         SBBSTNode(int n)
         {
             left = NULL;
             right = NULL;
             data = n;
             height = 0;
         }
};

 
class SelfBalancingBinarySearchTree
{
    private:
        SBBSTNode *root;
    public:
         SelfBalancingBinarySearchTree()
         {
             root = NULL;
         }
 
         bool isEmpty()
         {
             return root == NULL;
         }
 
         void makeEmpty()
         {
             root = NULL;
         }
 
         void insert(int data)
         {
             root = insert(data, root);
         }
 
         int height(SBBSTNode *t)
         {
             return t == NULL ? -1 : t->height;
         }
 
         int max(int lhs, int rhs)
         {
             return lhs > rhs ? lhs : rhs;
         }
 
         SBBSTNode *insert(int x, SBBSTNode *t)
         {
             if (t == NULL)
                 t = new SBBSTNode(x);
             else if (x < t->data)
             {
                 t->left = insert(x, t->left);
                 if (height(t->left) - height(t->right) == 2)
                     if (x < t->left->data)
                         t = rotateWithLeftChild(t);
                     else
                         t = doubleWithLeftChild(t);
             }
             else if (x > t->data)
             {
                 t->right = insert(x, t->right);
                 if (height(t->right) - height(t->left) == 2)
                     if (x > t->right->data)
                         t = rotateWithRightChild(t);
                     else
                         t = doubleWithRightChild(t);
             }
             t->height = max(height(t->left), height(t->right)) + 1;
             return t;
         }
 
         SBBSTNode *rotateWithLeftChild(SBBSTNode* k2)
         {
             SBBSTNode *k1 = k2->left;
             k2->left = k1->right;
             k1->right = k2;
             k2->height = max(height(k2->left), height(k2->right)) + 1;
             k1->height = max(height(k1->left), k2->height) + 1;
             return k1;
         }
 
         SBBSTNode *rotateWithRightChild(SBBSTNode *k1)
         {
             SBBSTNode *k2 = k1->right;
             k1->right = k2->left;
             k2->left = k1;
             k1->height = max(height(k1->left), height(k1->right)) + 1;
             k2->height = max(height(k2->right), k1->height) + 1;
             return k2;
         }

         SBBSTNode *doubleWithLeftChild(SBBSTNode *k3)
         {
             k3->left = rotateWithRightChild(k3->left);
             return rotateWithLeftChild(k3);
         }
  
         SBBSTNode *doubleWithRightChild(SBBSTNode *k1)
         {
             k1->right = rotateWithLeftChild(k1->right);
             return rotateWithRightChild(k1);
         }
 
         int countNodes()
         {
             return countNodes(root);
         }
 
         int countNodes(SBBSTNode *r)
         {
             if (r == NULL)
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
 
         bool search(SBBSTNode *r, int val)
         {
             bool found = false;
             while ((r != NULL) && !found)
             {
                 int rval = r->data;
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
 
         void inorder(SBBSTNode *r)
         {
             if (r != NULL)
             {
                 inorder(r->left);
                 cout<<r->data<<"  ";
                 inorder(r->right);
             }
         }
 
         void preorder()
         {
             preorder(root);
         }
         void preorder(SBBSTNode *r)
         {
             if (r != NULL)
             {
                 cout<<r->data<<"  ";
                 preorder(r->left);
                 preorder(r->right);
             }
         }
 
         void postorder()
         {
             postorder(root);
         }
         void postorder(SBBSTNode *r)
         {
             if (r != NULL)
             {
                 postorder(r->left);
                 postorder(r->right);
                 cout<<r->data<<"  ";
             }
         }
};
 
int main()
{
    SelfBalancingBinarySearchTree sbbst;
    cout<<"SelfBalancingBinarySearchTree Test\n";
    int val;
    char ch;
    do
    {
        cout<<"\nSelfBalancingBinarySearchTree Operations\n";
        cout<<"1. Insert "<<endl;
        cout<<"2. Count nodes"<<endl;
        cout<<"3. Search"<<endl;
        cout<<"4. Check empty"<<endl;
        cout<<"5. Make empty"<<endl;
        int choice;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch (choice)
        {
        case 1 :
            cout<<"Enter integer element to insert: ";
            cin>>val;
            sbbst.insert(val);
            break;
        case 2 :
            cout<<"Nodes = " <<sbbst.countNodes()<<endl;
            break;
        case 3:
            cout<<"Enter integer element to search: ";
            cin>>val;
            if (sbbst.search(val))
                cout<<val<<" found in the tree"<<endl;
            else
                cout<<val<<" not found"<<endl;
            break;
        case 4 :
            cout<<"Empty status = ";
            if (sbbst.isEmpty())
                cout<<"Tree is empty"<<endl;
            else
                cout<<"Tree is non - empty"<<endl;
            break;
        case 5 :
            cout<<"\nTree cleared\n";
            sbbst.makeEmpty();
            break;
        default :
            cout<<"Wrong Entry \n ";
            break;
        }
 
        cout<<"\nPost order : ";
        sbbst.postorder();
        cout<<"\nPre order : ";
        sbbst.preorder();
        cout<<"\nIn order : ";
        sbbst.inorder();
        cout<<"\nDo you want to continue (Type y or n): ";
        cin>>ch;
    }
    while (ch == 'Y'|| ch == 'y');
    return 0;
}
