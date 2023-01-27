#include<iostream>
#include<conio.h>
using namespace std;
struct node_info
{
    int no;
    int lv_time,st_time;
}*q = NULL, *r = NULL;
struct node
{
    node_info *pt;
    node *next;
}*top = NULL, *p = NULL, *np = NULL;
struct node1
{
    node1 *link;
    node_info *pt1;
}*head = NULL, *m = NULL, *n = NULL, *np1 = NULL;
int c = 0;
void push(node_info *ptr)
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
        np->next = top;
        top = np;
    }
}
node_info *pop()
{
    if (top == NULL)
    {
        cout<<"underflow\n";
    }
    else
    {
        p = top;
        top = top->next;
        return(p->pt);
        delete(p);
    }
}
void store(node_info *ptr1)
{
    np1 = new node1;
    np1->pt1 = ptr1;
    np1->link = NULL;
    if (c == 0)
    {
        head = np1;
        m = head;
        m->link = NULL;
        c++;
    }
    else
    {
        m = head;
        np1->link = m;
        head = np1;
    }
}
int search(int j)
{
    node1 *t = head;
    while (t != NULL)
    {
        if ((t->pt1)->no == j)
        {
            break;
        }
        else
        {
            t = t->link;
            continue;
        }
    }
    return (t->pt1)->lv_time;
}             
int present_in_stack(int j)
{
    int flag = 0;
    p = top;
    while (p != NULL)
    {
        if ((p->pt)->no == j)
        {
            flag = 1;
            return flag;
        }
        p = p->next;
    }
    return flag;
}
void topo(int *v,int am[][8],int i)
{
    q = new node_info;
    q->no = i;
    q->st_time = c;
    push(q);
    v[i] = 1;
    for (int j = 0; j < 8; j++)
    {
        if (am[i][j] == 0)
            continue;
        else if ((am[i][j] == 1 && v[j] == 1))
        {
            if (!present_in_stack(j) && q->st_time > search(j))
            {
                cout<<"Cross edge between "<<i<<" and "<<j<<endl;
            }
            continue;
        }
        else if(am[i][j] == 1 && v[j] == 0)
        {
            c++;
            topo(v,am,j);
        }
    }
    c++;
    q = pop();
    q->lv_time = c;
    store(q);
    return;
}
int main()
{
    int v[8], am[8][8];
    for (int i = 0; i < 8; i++)
        v[i] = 0;
    for (int i = 0; i < 8; i++)
    {
        cout<<"enter the values for adjacency matrix row:"<<i + 1<<endl;
        for(int j = 0; j < 8; j++)
        {
            cin>>am[i][j];
        }
    }
    topo(v,am,0);
    getch();
}
