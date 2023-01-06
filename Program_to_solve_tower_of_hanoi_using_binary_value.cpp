#include<stdio.h> 
#include<conio.h>
#include<iostream>
using namespace std;
int main()
{
    int n, x;
    cout<<"\nEnter the No. of Disks: ";
    cin>>n;
    for (x = 1; x < (1 << n); x++)
    {
        printf("\nMove from Peg %i to Peg %i", (x&x-1)%3+1, ((x|x-1)+1)%3+1);
    }
    cout<<"\n";
    getch();
}
