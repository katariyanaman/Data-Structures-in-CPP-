/* The following C++ program implements a Leftist Heap data structure, which is a type of priority
   queue. It provides operations to insert elements, merge two heaps, delete the minimum element, and clone heaps. */

#include <iostream>
#include <cstdlib>
using namespace std;

class LeftistNode
{
    public:
        int element;
        LeftistNode *left;
        LeftistNode *right;
        int npl;
        LeftistNode(int & element, LeftistNode *lt = NULL,
                    LeftistNode *rt = NULL, int np = 0)
        {
            this->element = element;
            right = rt;
            left = lt,
            npl =  np;
        }
};

class LeftistHeap
{
    public:
        LeftistHeap();
        LeftistHeap(LeftistHeap &rhs);
        ~LeftistHeap();
        bool isEmpty();
        bool isFull();
        int &findMin();
        void Insert(int &x);
        void deleteMin();
        void deleteMin(int &minItem);
        void makeEmpty();
        void Merge(LeftistHeap &rhs);
        LeftistHeap & operator=(LeftistHeap &rhs);
    private:
        LeftistNode *root;
        LeftistNode *Merge(LeftistNode *h1, LeftistNode *h2);
        LeftistNode *Merge1(LeftistNode *h1, LeftistNode *h2);
        void swapChildren(LeftistNode * t);
        void reclaimMemory(LeftistNode * t);
        LeftistNode *clone(LeftistNode *t);
};

LeftistHeap::LeftistHeap()
{
    root = NULL;
}

LeftistHeap::LeftistHeap(LeftistHeap &rhs)
{
    root = NULL;
    *this = rhs;
}

LeftistHeap::~LeftistHeap()
{
    makeEmpty( );
}

void LeftistHeap::Merge(LeftistHeap &rhs)
{
    if (this == &rhs)
        return;
    root = Merge(root, rhs.root);
    rhs.root = NULL;
}

LeftistNode *LeftistHeap::Merge(LeftistNode * h1, LeftistNode * h2)
{
    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;
    if (h1->element < h2->element)
        return Merge1(h1, h2);
    else
        return Merge1(h2, h1);
}

LeftistNode *LeftistHeap::Merge1(LeftistNode * h1, LeftistNode * h2)
{
    if (h1->left == NULL)
        h1->left = h2;
    else
    {
        h1->right = Merge(h1->right, h2);
        if (h1->left->npl < h1->right->npl)
            swapChildren(h1);
        h1->npl = h1->right->npl + 1;
    }
    return h1;
}

void LeftistHeap::swapChildren(LeftistNode * t)
{
    LeftistNode *tmp = t->left;
    t->left = t->right;
    t->right = tmp;
}

void LeftistHeap::Insert(int &x)
{
    root = Merge(new LeftistNode(x), root);
}

int &LeftistHeap::findMin()
{
    return root->element;
}

void LeftistHeap::deleteMin()
{
    LeftistNode *oldRoot = root;
    root = Merge(root->left, root->right);
    delete oldRoot;
}

void LeftistHeap::deleteMin(int &minItem)
{
    if (isEmpty())
    {
        cout<<"Heap is Empty"<<endl;
        return;
    }
    minItem = findMin();
    deleteMin();
}

bool LeftistHeap::isEmpty()
{
    return root == NULL;
}

bool LeftistHeap::isFull()
{
    return false;
}

void LeftistHeap::makeEmpty()
{
    reclaimMemory(root);
    root = NULL;
}

LeftistHeap &LeftistHeap::operator=(LeftistHeap & rhs)
{
    if (this != &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
    }
    return *this;
}

void LeftistHeap::reclaimMemory(LeftistNode * t)
{
    if (t != NULL)
    {
        reclaimMemory(t->left);
        reclaimMemory(t->right);
        delete t;
    }
}

LeftistNode *LeftistHeap::clone(LeftistNode * t)
{
    if (t == NULL)
        return NULL;
    else
        return new LeftistNode(t->element, clone(t->left), clone(t->right), t->npl);
}
 
int main()
{
    LeftistHeap h;
    LeftistHeap h1;
    LeftistHeap h2;
    for (int i = 0; i < 20; i++)
    {
        if (i % 2 == 0)
        {
            h.Insert(i);
            cout<<"Element"<<i<<" inserted in Heap 1"<<endl;
        }
        else
        {
            h1.Insert(i);
            cout<<"Element"<<i<<" inserted in Heap 2"<<endl;
        }
    }
    h.Merge(h1);
    h2 = h;
    for (int i = 0; i < 20; i++)
    {
        int x;
        h2.deleteMin(x);
        cout<<"Element "<<x<<" Deleted"<<endl;
        if (h2.isEmpty())
        {
            cout<<"The Heap is Empty"<<endl;
            break;
        }
    }
    return 0;
}
