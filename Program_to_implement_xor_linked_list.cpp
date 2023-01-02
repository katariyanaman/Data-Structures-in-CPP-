#include <iostream>
#include <cstdlib>
using namespace std;

struct node
{
    int data;
    struct node* npx;
}*head;

class xor_list
{
    public:
        node* XOR (struct node *a, struct node *b);
        void insert(struct node **head_ref, int data);
        void display (struct node *head);
        xor_list()
        {
            head = NULL;	
        }
};

int main()
{
    xor_list xl;
    int choice, item;
    while (1)
    {
        cout<<"\n-------------"<<endl;
        cout<<"Operations on XOR Linked List"<<endl;
        cout<<"\n-------------"<<endl;
        cout<<"1.Insert Element at First"<<endl;
        cout<<"2.Display List"<<endl;
        cout<<"3.Quit"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter value to be inserted: ";
            cin>>item;
            xl.insert(&head, item);
            break;
        case 2:
            xl.display (head);
            break;
        case 3:
            exit(1);
            break;
        default:
            cout<<"Wrong Choice"<<endl;
        }
    }
    return 0;
}

node *xor_list::XOR (struct node *a, struct node *b)
{
    return (node*) ((unsigned int) (a) ^ (unsigned int) (b));
}

void xor_list::insert(struct node **head_ref, int data)
{
    node *new_node  = new (struct node);
    new_node->data = data;
    new_node->npx = XOR (*head_ref, NULL);
    if (*head_ref != NULL)
    {
        node* next = XOR ((*head_ref)->npx,  NULL);
        (*head_ref)->npx = XOR (new_node, next);
    }
    *head_ref = new_node;
}
 
void xor_list::display (struct node *head)
{
    node *curr = head;
    node *prev = NULL;
    node *next;
    cout<<"Elements of XOR Linked List: "<<endl;
    while (curr != NULL)
    {
        cout<<curr->data<<" ";
        next = XOR (prev, curr->npx);
        prev = curr;
        curr = next;
    }
    cout<<endl;
}
