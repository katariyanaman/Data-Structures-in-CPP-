/* The following C++ program is solving the Tower of Hanoi problem by printing
   the sequence of moves required to solve the problem for a given number of disks. */

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
