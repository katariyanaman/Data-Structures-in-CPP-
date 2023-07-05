/* The following C++ program is implementing a Pairing Heap data structure, which is a type
   of heap that supports insertion, deletion of the minimum element, and decreasing the key of an element. */

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class PairNode
{
    public:
        int element;
        PairNode *leftChild;
        PairNode *nextSibling;
        PairNode *prev;
        PairNode(int element)
        {
            this->element = element;
            leftChild = NULL;
            nextSibling = NULL;
            prev = NULL;
        }
};

class PairingHeap
{
    private:
        PairNode *root;
        void reclaimMemory(PairNode *t);
        void compareAndLink(PairNode * &first, PairNode *second);
        PairNode *combineSiblings(PairNode *firstSibling);
        PairNode *clone(PairNode *t);
    public:
        PairingHeap();
        PairingHeap(PairingHeap &rhs);
        ~PairingHeap();
        bool isEmpty();
        bool isFull();
        int &findMin();
        PairNode *Insert(int &x);
        void deleteMin();
        void deleteMin(int &minItem);
        void makeEmpty();
        void decreaseKey(PairNode *p, int &newVal );
        PairingHeap &operator=(PairingHeap &rhs);
};
 
PairingHeap::PairingHeap()
{
    root = NULL;
}
 
PairingHeap::PairingHeap(PairingHeap & rhs)
{
    root = NULL;
    *this = rhs;
}

PairingHeap::~PairingHeap()
{
    makeEmpty();
}

PairNode *PairingHeap::Insert(int &x)
{
    PairNode *newNode = new PairNode(x);
    if (root == NULL)
        root = newNode;
    else
        compareAndLink(root, newNode);
    return newNode;
}

int &PairingHeap::findMin()
{
    return root->element;
}

void PairingHeap::deleteMin()
{
    PairNode *oldRoot = root;
    if (root->leftChild == NULL)
        root = NULL;
    else
        root = combineSiblings(root->leftChild);
    delete oldRoot;
}

void PairingHeap::deleteMin(int &minItem)
{
    if (isEmpty())
    {
        cout<<"The Heap is Empty"<<endl;
        return;
    }
    minItem = findMin();
    deleteMin();
    cout<<"Minimum Element: "<<minItem<<" deleted"<<endl;
}

bool PairingHeap::isEmpty()
{
    return root == NULL;
}

bool PairingHeap::isFull()
{
    return false;
}

void PairingHeap::makeEmpty()
{
    reclaimMemory(root);
    root = NULL;
}

PairingHeap &PairingHeap::operator=(PairingHeap & rhs)
{
    if (this != &rhs)
    {
        makeEmpty( );
        root = clone(rhs.root);
    }
    return *this;
}

void PairingHeap::reclaimMemory(PairNode * t)
{
    if (t != NULL)
    {
        reclaimMemory(t->leftChild);
        reclaimMemory(t->nextSibling);
        delete t;
    }
}

void PairingHeap::decreaseKey(PairNode *p, int &newVal)
{
    if (p->element < newVal)
        return;
    p->element = newVal;
    if (p != root)
    {
        if (p->nextSibling != NULL)
            p->nextSibling->prev = p->prev;
        if (p->prev->leftChild == p)
            p->prev->leftChild = p->nextSibling;
        else
            p->prev->nextSibling = p->nextSibling;
            p->nextSibling = NULL;
            compareAndLink(root, p);
    }
}

void PairingHeap::compareAndLink(PairNode * &first, PairNode *second)
{
    if (second == NULL)
        return;
    if (second->element < first->element)
    {
        second->prev = first->prev;
        first->prev = second;
        first->nextSibling = second->leftChild;
        if (first->nextSibling != NULL)
            first->nextSibling->prev = first;
        second->leftChild = first;
        first = second;
    }
    else
    {
        second->prev = first;
        first->nextSibling = second->nextSibling;
        if (first->nextSibling != NULL)
            first->nextSibling->prev = first;
        second->nextSibling = first->leftChild;
        if (second->nextSibling != NULL)
            second->nextSibling->prev = second;
        first->leftChild = second;
    }
}

PairNode *PairingHeap::combineSiblings(PairNode *firstSibling)
{
    if (firstSibling->nextSibling == NULL)
        return firstSibling;
    static vector<PairNode *> treeArray(5);
    int numSiblings = 0;
    for (; firstSibling != NULL; numSiblings++)
    {
        if (numSiblings == treeArray.size())
            treeArray.resize(numSiblings * 2);
        treeArray[numSiblings] = firstSibling;
        firstSibling->prev->nextSibling = NULL;
        firstSibling = firstSibling->nextSibling;
    }
    if (numSiblings == treeArray.size())
        treeArray.resize(numSiblings + 1);
    treeArray[numSiblings] = NULL;
    int i = 0;
    for (; i + 1 < numSiblings; i += 2)
        compareAndLink(treeArray[i], treeArray[i + 1]);
    int j = i - 2;
    if (j == numSiblings - 3)
        compareAndLink (treeArray[j], treeArray[j + 2]);
    for (; j >= 2; j -= 2)
        compareAndLink(treeArray[j - 2], treeArray[j] );
    return treeArray[0];
}

PairNode *PairingHeap::clone(PairNode * t)
{
    if (t == NULL)
        return NULL;
    else
    {
        PairNode *p = new PairNode(t->element);
        if ((p->leftChild = clone( t->leftChild)) != NULL)
            p->leftChild->prev = p;
        if ((p->nextSibling = clone( t->nextSibling)) != NULL)
            p->nextSibling->prev = p;
        return p;
    }
}

int main()
{
    int choice, num, pos;
    char ch;
    PairingHeap h;
    PairNode * pn;
    while (1)
    {
        cout<<"-----------------"<<endl;
        cout<<"Operations on Pairing Heap"<<endl;
        cout<<"-----------------"<<endl;
        cout<<"1.Insert Element and Decrease key"<<endl;
        cout<<"2.Delete Minimum Element "<<endl;
        cout<<"3.Quit"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter the number to be inserted : ";
            cin>>num;
            pn = h.Insert(num);
            cout<<"Want to decrease the key:(Y = Yes | N = No) ";
            cin>>ch;
            if (ch == 'Y')
            {
                cout<<"Enter new key value: ";
                cin>>pos;
                h.decreaseKey(pn, pos);
            }
            break;
        case 2:
            h.deleteMin(num);
            break;
        case 3:
            exit(1);
        default:
            cout<<"Wrong choice"<<endl;
        }
    }
    return 0;
}
