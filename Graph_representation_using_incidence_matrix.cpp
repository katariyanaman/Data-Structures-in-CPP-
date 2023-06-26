/* The following C++ program takes inputs for a graph's number
   of vertices and determines the adjacency between vertices. It then
   constructs and prints the incidence matrix representation of the graph. */

#include<iostream>
#include<iomanip>
 
using namespace std;
 
void PrintMat(int mat[][20], int n, int count)
{
	int i, j;
 
	cout<<"\n\n"<<setw(6)<<"";
	for(i = 0; i < n; i++)
		cout<<setw(6)<<"V("<<i+1<<")";
	cout<<"\n\n";
 
	for(i = 0; i < count; i++)
	{
		cout<<setw(6)<<"E("<<i+1<<")";
 
		for(j = 0; j < n; j++)
		{
			cout<<setw(6)<<mat[i][j];
		}
 
		cout<<"\n\n";
	}
}
 
int main()
{
	int i, j, v, k, count = 0, n, incimat[100][20];
 
	cout<<"Enter the number of vertexes: ";
	cin>>v;
 
	for(i = 0; i < v; i++)
	{
		for(j = i+1; j < v; j++)
		{
			cout<<"\nEnter 1 if the vertex "<<i+1<<" is adjacent to "<<j+1<<", otherwise 0: ";
			cin>>n;
			if(n == 1)
			{
				for(k = 0; k < v; k++)
				{
					if(k == i || k == j)
						incimat[count][k] = 1;
					else
						incimat[count][k] = 0;
				}
				count++;
				cout<<"\t\tIt is edge E("<<count<<").";
			}
		}
	}
 
	PrintMat(incimat, v, count);
}
