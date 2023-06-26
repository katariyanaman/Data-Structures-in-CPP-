/* The following C++ program creates a binary tree, performs an
   inorder traversal of the tree, and prints the nodes in ascending order. */

#include<iostream>
using namespace std;
#include<conio.h>
struct tree
{
    tree *l, *r;
    int data;
}*root = NULL, *p = NULL, *s = NULL;
struct node
{
    tree *pt;
    node *next;
}*q = NULL, *top = NULL, *np = NULL;       
void create()
{
    int value ,c = 0;      
    while (c < 6)
    {
        if (root == NULL)
        {
            root = new tree;
            cout<<"enter value of root node\n";
            cin>>root->data;
            root->r = NULL;
            root->l = NULL;
        }
        else
        {
            p = root;
            cout<<"enter value of node\n";
            cin>>value;
            while(true)
            {
                if(value < p->data)
                {
                    if (p->l == NULL)
                    {
                        p->l = new tree;
                        p = p->l;
                        p->data = value;
                        p->l = NULL;
                        p->r = NULL;
                        cout<<"value entered in left\n";
                        break;
                    }
                    else if (p->l != NULL)
                    {
                        p = p->l;
                    }
                }
               else if (value > p->data)
               {
                    if (p->r == NULL)
                    {
                        p->r = new tree;
                        p = p->r;
                        p->data = value;
                        p->l = NULL;
                        p->r = NULL;
                        cout<<"value entered in right\n";
                        break;
                    }
                    else if(p->r != NULL)
                    {
                       p = p->r;
                    }
                }
            }
        }
    c++;
    }
}
void push(tree *ptr)
{
    np = new node;
    np->pt = ptr;
    np->next = NULL;
    if (top == NULL)
    {
        top = np;
    }
    else
    {
        q = top;
        top = np;
        np->next = q;
    }
}
tree *pop()
{
    if (top == NULL)
    {
        cout<<"underflow\n";
    }
    else
    {
        q = top;
        top = top->next;
        return(q->pt);
        delete(q);
    }
}
void traverse(tree *p)
{
    push(p);
    while (top != NULL)
    {
        while (p != NULL)
        {
            push(p);
            p = p->l;
        }
        if (top != NULL && p == NULL)
        {
            p = pop();
            cout<<p->data<<endl;
            p = p->r;
        }
    }
}
int main()
{
    int val;
    create();
    cout<<"printing traversal in inorder\n";
    traverse(root);                 
    getch();
}
