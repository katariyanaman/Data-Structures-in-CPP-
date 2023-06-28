/* The following C++ program identifies and displays the back edges in a directed graph represented by an adjacency matrix. */

#include<iostream>
#include<conio.h>
using namespace std;
struct node_info
{
    int no;
}*q = NULL,*r = NULL;
struct node
{
    node_info *pt;
    node *next;
}*top = NULL,*p = NULL,*np = NULL;
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
void back_edges(int *v,int am[][7],int i,int k)
{
     cout<<"\n\nDISPLAYING BACK EDGES\n\n";
     q = new node_info;
     q->no = i;
     push(q);
     v[i] = 1;
     for (int j = 0; j < 7; j++)
     {
         if (am[i][j] == 1 && v[j] == 0)
         {
             c++;
             back_edges(v,am,j,i);
         }
         else if (am[i][j] == 0)
              continue;
         else if ((j == k) && (am[i][k] == 1 && v[j] == 1))
              continue;
         else
         {
             cout<<"Back edge present between "<<i<<" th node and "<<j<<" th node"<<endl;
             am[i][j] = 0;
             am[j][i] = 0;
             continue;
         }
     }
     r = pop();
     return;
}     
int main()
{
    int v[7],am[7][7];
    for (int i = 0; i < 7; i++)
        v[i] = 0;
    for (int i = 0; i < 7; i++)
    {
        cout<<"enter the values for adjacency matrix row:"<<i + 1<<endl;
        for(int j = 0; j < 7; j++)
        {
            cin>>am[i][j];
        }
    }
    back_edges(v,am,0,0);
    getch();
}
