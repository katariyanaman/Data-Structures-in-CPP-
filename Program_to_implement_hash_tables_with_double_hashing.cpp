/* The following C++ program implements double hashing as a collision resolution technique in a hash table,
   allowing operations to initialize the table size, insert elements, display the hash table, and rehash the 
   table if it becomes full. It provides a menu-driven interface for interacting with the hash table. */

#include <iostream>
#include <cstdlib>
#define MIN_TABLE_SIZE 10
using namespace std;

enum EntryType {Legitimate, Empty, Deleted};

struct HashNode
{
    int element;
    enum EntryType info;
};

struct HashTable
{
    int size;
    HashNode *table;
};

int HashFunc1(int key, int size)
{
    return key % size;
}

int HashFunc2(int key, int size)
{
    return (key * size - 1) % size;
}

HashTable *initializeTable(int size)
{
    HashTable *htable;
    if (size < MIN_TABLE_SIZE)
    {
        cout<<"Table Size Too Small"<<endl;
        return NULL;
    }
    htable = new HashTable;
    if (htable == NULL)
    {
        cout<<"Out of Space"<<endl;
        return NULL;
    }
    htable->size = size;
    htable->table = new HashNode [htable->size];
    if (htable->table == NULL)
    {
        cout<<"Table Size Too Small"<<endl;
        return NULL;
    }
    for (int i = 0; i < htable->size; i++)
    {
        htable->table[i].info = Empty;
        htable->table[i].element = NULL;
    }
    return htable;
}

int Find(int key, HashTable *htable)
{
    int hashVal= HashFunc1(key, htable->size);
    int stepSize= HashFunc2(key, htable->size);
    while (htable->table[hashVal].info != Empty &&
           htable->table[hashVal].element != key)
    {
        hashVal = hashVal + stepSize;
        hashVal = hashVal % htable->size;
    }
    return hashVal;
}

void Insert(int key, HashTable *htable)
{
    int pos = Find(key, htable);
    if (htable->table[pos].info != Legitimate )
    {
        htable->table[pos].info = Legitimate;
        htable->table[pos].element = key;
    }
}

HashTable *Rehash(HashTable *htable)
{
    int size = htable->size;
    HashNode *table = htable->table;
    htable = initializeTable(2 * size);
    for (int i = 0; i < size; i++)
    {
        if (table[i].info == Legitimate)
            Insert(table[i].element, htable);
    }
    free(table);
    return htable;
}

void Retrieve(HashTable *htable)
{
    for (int i = 0; i < htable->size; i++)
    {
        int value = htable->table[i].element;
        if (!value)
            cout<<"Position: "<<i + 1<<" Element: Null"<<endl;
        else
            cout<<"Position: "<<i + 1<<" Element: "<<value<<endl;
    }
 
}

int main()
{
    int value, size, pos, i = 1;
    int choice;
    HashTable *htable;
    while(1)
    {
        cout<<"\n----------------------"<<endl;
        cout<<"Operations on Double Hashing"<<endl;
        cout<<"\n----------------------"<<endl;
        cout<<"1.Initialize size of the table"<<endl;
        cout<<"2.Insert element into the table"<<endl;
        cout<<"3.Display Hash Table"<<endl;
        cout<<"4.Rehash The Table"<<endl;
        cout<<"5.Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter size of the Hash Table: ";
            cin>>size;
            htable = initializeTable(size);
            break;
        case 2:
            if (i > htable->size)
            {
                cout<<"Table is Full, Rehash the table"<<endl;
                continue;
            }
        	cout<<"Enter element to be inserted: ";
        	cin>>value;
            Insert(value, htable);
            i++;
            break;
        case 3:
            Retrieve(htable);
            break;
        case 4:
            htable = Rehash(htable);
            break;
        case 5:
            exit(1);
        default:
           cout<<"\nEnter correct option\n";
       }
    }
    return 0;
}
